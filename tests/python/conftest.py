#!/usr/bin/env python

import os
import subprocess
import time
from pathlib import Path

import pytest
from _pytest.config import Config
from _pytest.config.argparsing import Parser
from _pytest.main import Session
from _pytest.nodes import Item
from _pytest.python import Module
from _pytest.runner import CallInfo
from beartype import beartype
from conf_gtest import GTestFile, summarize_cookies
from conf_qtest import GUI_SCREEN_DISPLAY, QTestFile
from plumbum import local
from py_scriptutils.script_logging import pprint_to_file, to_debug_json
from py_scriptutils.tracer import TraceCollector
from beartype.typing import List
from asteval import Interpreter
import logging
import ast

trace_collector: TraceCollector = None


def get_trace_collector():
    global trace_collector
    if not trace_collector:
        trace_collector = TraceCollector()

    return trace_collector


def check_gui_application_on_display(app_command: str, display: str):
    env = os.environ.copy()
    env['DISPLAY'] = display

    try:
        process = subprocess.Popen(app_command,
                                   env=env,
                                   stdout=subprocess.PIPE,
                                   stderr=subprocess.PIPE)
        time.sleep(2)
        if process.poll() is not None:
            stdout, stderr = process.communicate()
            raise Exception(f"""
Application failed to start:"
STDOUT: {stdout.decode()}
STDERR: {stderr.decode()}
                """)

        else:
            process.terminate()
    except Exception as e:
        print(f"Failed to start the application: {str(e)}")


@beartype
def is_ci() -> bool:
    return bool(os.getenv("INVOKE_CI"))


@pytest.fixture(scope="session", autouse=True)
def trace_session():
    get_trace_collector().push_complete_event("session", "test-session")

    if not is_ci():
        xvfb = local["Xvfb"]
        xvfb_process = xvfb.popen(
            args=[GUI_SCREEN_DISPLAY, "-srceen", "0", "1280x1024x24"])

        if xvfb_process.poll() is not None:  # None means still running
            output, errors = xvfb_process.communicate()
            raise Exception(f"Xvfb failed to start: {errors.decode()} {output.decode()}")

        check_gui_application_on_display("xev", GUI_SCREEN_DISPLAY)

    yield

    if not is_ci():
        xvfb_process.terminate()
        xvfb_process.wait()

    get_trace_collector().pop_complete_event()
    get_trace_collector().export_to_json(Path("/tmp/haxorg_py_tests.json"))
    coverage = os.getenv("HAX_COVERAGE_OUT_DIR")
    if coverage:
        coverage = Path(coverage)
        summary = summarize_cookies(coverage)
        coverage.joinpath("test-summary.json").write_text(
            summary.model_dump_json(indent=2))


@pytest.fixture(scope="module", autouse=True)
def trace_module(request):
    module_name = request.module.__name__
    get_trace_collector().push_complete_event(module_name, "test-file")
    yield
    get_trace_collector().pop_complete_event()


@pytest.fixture(autouse=True)
def trace_test(request):
    test_name = request.node.name
    get_trace_collector().push_complete_event(test_name, "test")
    yield
    get_trace_collector().pop_complete_event()


def pytest_collect_file(parent: Module, path: str):
    test = Path(path)

    def debug(it, file):
        pprint_to_file(to_debug_json(it), file + ".json")

    if test.name == "test_integrate_cxx_org.py":
        coverage = os.getenv("HAX_COVERAGE_OUT_DIR")
        result = GTestFile.from_parent(
            parent,
            path=test,
            coverage_out_dir=coverage and Path(coverage),
        )

        debug(result, "/tmp/google_tests")
        return result

    elif test.name == "test_integrate_qt.py":
        if not is_ci():
            result = QTestFile.from_parent(parent, path=test)
            debug(result, "/tmp/qt_tests")
            return result


def pytest_collection_modifyitems(session: Session, config: Config,
                                  items: List[Item]) -> None:
    for item in items:
        if "unstable" in item.keywords:
            item.add_marker(pytest.mark.xfail(reason="This test is known to be unstable"))


def pytest_runtest_makereport(item: Item, call: CallInfo) -> pytest.TestReport:
    if "unstable" in item.keywords:
        if call.excinfo is not None and call.excinfo.typename == "Failed":
            rep = pytest.TestReport.from_item_and_call(item, call)
            rep.outcome = "xfailed"
            rep.wasxfail = "reason: This test is known to be unstable"
            return rep


class FunctionNameExtractor(ast.NodeVisitor):

    def __init__(self):
        self.function_names = []

    def visit_Call(self, node: ast.Call):
        if isinstance(node.func, ast.Name):
            self.function_names.append(node.func.id)
        self.generic_visit(node)


def get_function_names(expression: str) -> List[str]:
    parsed_ast = ast.parse(expression, mode='eval')
    extractor = FunctionNameExtractor()
    extractor.visit(parsed_ast)
    return extractor.function_names


def pytest_collection_modifyitems(config: pytest.Config,
                                  items: List[pytest.Item]) -> None:
    filter = config.getoption("--markfilter")

    if filter:
        selected_items: List[pytest.Item] = []
        deselected_items: List[pytest.Item] = []

        aeval = Interpreter()

        for item in items:
            def has_params(mark: pytest.Mark, *args: list, **kwargs: dict) -> bool:
                print(f"{mark.name} {args} {kwargs} // {mark.args} {mark.kwargs}")
                if len(mark.args) < len(args):
                    return False

                if len(mark.kwargs) < len(mark.kwargs):
                    return False

                for idx, positional in enumerate(args):
                    if positional != mark.args[idx]:
                        return False

                for key, value in kwargs.items():
                    if key not in mark.kwargs or mark.kwargs[key] != value:
                        return False

                return True

            def has_marker(name: str, *args: list, **kwargs: dict) -> bool:
                return any(
                    has_params(mark, *args, **kwargs)
                    for mark in item.iter_markers()
                    if mark.name == name)

            names = get_function_names(filter)
            for name in names:
                def impl(*args, **kwargs):
                    return has_marker(name, *args, **kwargs)

                aeval.symtable[name] = impl

            keep: bool = aeval(filter)

            if keep:
                selected_items.append(item)
            else:
                deselected_items.append(item)

        if deselected_items:
            config.hook.pytest_deselected(items=deselected_items)
        items[:] = selected_items
