#!/usr/bin/env python

import ast
import logging
import os
import subprocess
import sys
import time
import warnings
from pathlib import Path

import pytest
from _pytest.config import Config
from _pytest.main import Session
from _pytest.nodes import Item
from _pytest.runner import CallInfo
from beartype import beartype
from beartype.typing import Any, Generator, List, Optional
from conf_test_common import summarize_cookies  # type: ignore
from py_scriptutils.script_logging import log
from py_scriptutils.tracer import TraceCollector

CAT = "conftest"

trace_collector: TraceCollector = None


def pytest_configure(config: Any) -> None:
    "nodoc"
    for logger_name in [
        "plumbum.local",
        "matplotlib.font_manager",
        "graphviz._tools",
        "matplotlib",
        "asyncio",
        "git.cmd",
        "git.util",
    ]:
        logger = logging.getLogger(logger_name)
        logger.disabled = True

    warnings.filterwarnings(
        "ignore",
        category=DeprecationWarning,
        module="pydantic._internal._config",
    )
    warnings.filterwarnings(
        "ignore",
        category=UserWarning,
        module="pydantic._internal._config",
    )
    warnings.filterwarnings(
        "ignore",
        category=pytest.PytestRemovedIn9Warning,
        module="tests.python.conftest",
    )
    warnings.filterwarnings(
        "ignore",
        category=DeprecationWarning,
        module="dominate.dom_tag",
    )


def get_trace_collector() -> TraceCollector:
    global trace_collector
    if not trace_collector:
        trace_collector = TraceCollector()

    return trace_collector


def check_gui_application_on_display(app_command: str, display: str) -> None:
    env = os.environ.copy()
    env["DISPLAY"] = display

    try:
        process = subprocess.Popen(
            app_command, env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE
        )
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


@pytest.fixture(scope="session", autouse=True)
def trace_session() -> Generator[None, Any, Any]:
    get_trace_collector().push_complete_event("session", "test-session")

    yield

    get_trace_collector().pop_complete_event()
    get_trace_collector().export_to_json(Path("/tmp/haxorg_py_tests.json"))
    coverage_env = os.getenv("HAX_COVERAGE_OUT_DIR")
    if coverage_env:
        coverage = Path(coverage_env)
        summary = summarize_cookies(coverage)
        respath = coverage.joinpath("test-summary.json")
        log(CAT).info(
            f"Finalized session with {len(summary.runs)} cxx coverage-enabled test executions, writing to {respath}"
        )
        respath.parent.mkdir(parents=True, exist_ok=True)
        respath.write_text(summary.model_dump_json(indent=2))


@pytest.fixture(scope="module", autouse=True)
def trace_module(request: pytest.FixtureRequest) -> Generator[None, Any, Any]:
    module_name = request.module.__name__
    get_trace_collector().push_complete_event(module_name, "test-file")
    yield
    get_trace_collector().pop_complete_event()


@pytest.fixture(autouse=True)
def trace_test(request: pytest.FixtureRequest) -> Generator[None, Any, Any]:
    test_name = request.node.name
    get_trace_collector().push_complete_event(test_name, "test")
    yield
    get_trace_collector().pop_complete_event()


def pytest_collection_modifyitems(
    session: Session,
    config: Config,
    items: List[Item],
) -> None:
    for item in items:
        if "unstable" in item.keywords:
            item.add_marker(pytest.mark.xfail(reason="This test is known to be unstable"))


def pytest_runtest_makereport(item: Item, call: CallInfo) -> Optional[pytest.TestReport]:
    if "unstable" in item.keywords:
        if call.excinfo is not None and call.excinfo.typename == "Failed":
            rep = pytest.TestReport.from_item_and_call(item, call)
            rep.outcome = "xfailed"  # type: ignore
            rep.wasxfail = "reason: This test is known to be unstable"
            return rep

    return None


class FunctionNameExtractor(ast.NodeVisitor):
    def __init__(self) -> None:
        self.function_names: List[str] = []

    def visit_Call(self, node: ast.Call) -> None:
        if isinstance(node.func, ast.Name):
            self.function_names.append(node.func.id)
        self.generic_visit(node)


def get_function_names(expression: str) -> List[str]:
    parsed_ast = ast.parse(expression, mode="eval")
    extractor = FunctionNameExtractor()
    extractor.visit(parsed_ast)
    return extractor.function_names


@pytest.fixture
def cpp_debugger(request: Any) -> dict[str, bool]:

    @beartype
    def run_under_lldb() -> None:
        test_path = str(request.node.fspath)
        test_name = request.node.Name

        lldb_script_content = """breakpoint set -E C++
breakpoint set -n __cxa_throw
breakpoint set -n abort
breakpoint set -n std::terminate
run
bt
continue
"""

        script_path = Path("/tmp/debug.lldb")
        script_path.write_text(lldb_script_content)

        pytest_cmd = [
            sys.executable,
            "-m",
            "pytest",
            f"{test_path}::{test_name}",
            "-v",
            "-s",
            "--tb=line",
        ]

        lldb_cmd = ["lldb", "--source", str(script_path), "--"] + pytest_cmd

        try:
            subprocess.run(lldb_cmd)
        finally:
            script_path.unlink()

    @beartype
    def finalizer() -> None:
        if hasattr(request.node, "rep_call") and request.node.rep_call.failed:
            run_under_lldb()

    request.addfinalizer(finalizer)
    return {"debug_enabled": True}


@pytest.hookimpl(hookwrapper=True)
def pytest_runtest_makereport(item: Any, call: Any) -> Any:
    outcome = yield
    rep = outcome.get_result()
    setattr(item, f"rep_{rep.when}", rep)
