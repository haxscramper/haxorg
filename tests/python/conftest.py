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
from tests.python.conf_gtest import GTestFile
from tests.python.conf_test_common import summarize_cookies
from plumbum import local
from py_scriptutils.script_logging import pprint_to_file, to_debug_json, log
from py_scriptutils.tracer import TraceCollector
from beartype.typing import List, Any, Generator, Optional
from asteval import Interpreter
import ast
from py_scriptutils.repo_files import get_haxorg_build_path
import warnings
from py_scriptutils.script_logging import log
import copy

CAT = "conftest"

trace_collector: TraceCollector = None


def pytest_configure(config: Any) -> None:
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
def trace_session() -> Generator[None, Any, Any]:
    get_trace_collector().push_complete_event("session", "test-session")

    yield

    get_trace_collector().pop_complete_event()
    get_trace_collector().export_to_json(Path("/tmp/haxorg_py_tests.json"))
    coverage_env = os.getenv("HAX_COVERAGE_OUT_DIR")
    if coverage_env:
        coverage = Path(coverage_env)
        summary = summarize_cookies(coverage)
        log(CAT).info(
            f"Finalized session with {len(summary.runs)} cxx coverage-enabled test executions"
        )
        respath = coverage.joinpath("test-summary.json")
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


def pytest_collect_file(parent: Module, path: str) -> Optional[GTestFile]:
    test = Path(path)

    def debug(it: Any, file: str) -> None:
        pprint_to_file(to_debug_json(it), file + ".json")

    coverage = os.getenv("HAX_COVERAGE_OUT_DIR")

    if test.name.startswith("test_integrate_cxx"):
        log(CAT).info(f"File '{test.name}' integrates execution of the cxx binary")
        if test.name.endswith("_cxx_org.py"):
            binary_path_str = "haxorg/tests_org"

        else:
            binary_path_str = "haxorg/tests_hstd"

        binary_path = get_haxorg_build_path().joinpath(binary_path_str)

        assert binary_path.exists(), f"{binary_path} {test.name}"

        result = GTestFile.from_parent(
            parent,
            path=test,
            coverage_out_dir=coverage and Path(coverage),
            binary_path=binary_path,
        )

        if test.name.endswith("_cxx_hstd.py"):
            debug(result, "/tmp/google_tests_cxx_hstd")

        return result

    else:
        return None


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
    parsed_ast = ast.parse(expression, mode='eval')
    extractor = FunctionNameExtractor()
    extractor.visit(parsed_ast)
    return extractor.function_names


def pytest_collection_modifyitems(config: pytest.Config,
                                  items: List[pytest.Item]) -> None:
    try:
        filter = config.getoption("--markfilter")
        debug = config.getoption("--markfilter-debug")

    except ValueError:
        return

    if debug:
        dbg_file = open("/tmp/pytest_debug.txt", "w")

    if filter:
        selected_items: List[pytest.Item] = []
        deselected_items: List[pytest.Item] = []

        aeval = Interpreter()

        def dbg(msg: str) -> None:
            if debug:
                print(msg, file=dbg_file)

        dbg("Running custom filter")

        test_limit_counter = 0

        for item in items:
            dbg(f"name:{item.name}")
            for mark in item.iter_markers():
                dbg(f"  > {mark.name}({mark.args}, {mark.kwargs})")

        for item in items:

            def has_params(mark: pytest.Mark, *args: list, **kwargs: dict) -> bool:
                """
                Check if a specified marker has all parameters listed in the `args` and `kwargs`. 
                It might have more parameters, these will be ignored. 
                """
                dbg(f"    > has_params {mark.name}({mark.args}, {mark.kwargs})")
                if len(mark.args) < len(args):
                    dbg(f"    > len(mark.args = {len(mark.args)}) < len(args = {len(args)})"
                       )
                    return False

                if len(mark.kwargs) < len(mark.kwargs):
                    dbg(f"    > len(mark.kwargs = {len(mark.kwargs)}) < len(kwargs = {len(kwargs)})"
                       )
                    return False

                for idx, positional in enumerate(args):
                    if positional != mark.args[idx]:
                        dbg(f"    > (args[{idx}] = {positional}) != (mark.args[{idx}] = {mark.args[idx]})"
                           )
                        return False

                for key, value in kwargs.items():
                    if key not in mark.kwargs or mark.kwargs[key] != value:
                        dbg(f"    > (kwargs[{key}] = {value}) != (mark.kwargs[{key}] = {mark.kwargs[key]})"
                           )
                        return False

                return True

            def has_marker_impl(name: str, *args: list, **kwargs: dict) -> bool:
                dbg(f"    > has_marker_name({name}) in {[mark.name for mark in item.iter_markers()]}"
                   )
                return any(
                    has_params(mark, *args, **kwargs)
                    for mark in item.iter_markers()
                    if mark.name == name)

            class HasMarker():
                """
                Implementation function wrapper to hold the copy of `name` context
                from the for loop. 
                """

                def __init__(self, name: str) -> None:
                    self.name = copy.deepcopy(name)

                def __call__(self, *args: Any, **kwargs: Any) -> str:
                    dbg(f"  >> {self.name}({args}, {kwargs}) has marker ...")
                    result = has_marker_impl(self.name, *args, **kwargs)
                    dbg(f"  >> {self.name} -> {result}")
                    return result

            def test_first_n(max_count: int) -> bool:
                """
                Limit the number of filtered tests to N max. All calls after N calls to this function
                will return `False`, so it is best put as `cond() and cond() and test_first_n()` as
                it would clamp down on the number of otherwise accepted elements. 
                """
                nonlocal test_limit_counter
                result = test_limit_counter < max_count
                test_limit_counter += 1
                return result

            names = get_function_names(filter)
            for name in names:
                aeval.symtable[name] = HasMarker(name)

            aeval.symtable["test_first_n"] = test_first_n

            dbg(f"running eval on names {names}")
            keep: bool = aeval(filter)
            dbg(f"{filter} -> {keep}")
            dbg("")

            if keep:
                selected_items.append(item)
            else:
                deselected_items.append(item)

        if deselected_items:
            config.hook.pytest_deselected(items=deselected_items)
        items[:] = selected_items

    if debug:
        dbg_file.close()


@pytest.fixture
def stable_test_dir(request: pytest.FixtureRequest) -> Path:
    import hashlib
    import shutil
    from pathlib import Path

    # Get test file path relative to tests directory
    test_file_path = Path(request.path)
    tests_root = None

    # Find the 'tests' directory in the path
    for parent in test_file_path.parents:
        if parent.name == 'tests':
            tests_root = parent
            break

    if tests_root is None:
        raise ValueError(f"Could not find 'tests' directory in path: {test_file_path}")

    # Get relative path from tests directory, without .py extension
    rel_path = test_file_path.relative_to(tests_root).with_suffix('')

    # Build base directory path
    base_dir = Path("/tmp/haxorg/test_out") / rel_path

    # Add test function name
    test_name = request.node.name

    # Handle parametrized tests
    if hasattr(request.node, "callspec") and request.node.callspec.params:
        params_items = sorted(request.node.callspec.params.items())
        params_str = "_".join(f"{k}={v}" for k, v in params_items)

        if len(params_str) <= 32:
            # Use parameters as-is if short enough
            final_dir = base_dir / test_name / params_str
        else:
            # Use first 24 chars + hex digest for long parameters
            params_prefix = params_str[:24]
            params_hash = hashlib.md5(params_str.encode()).hexdigest()[:8]
            final_dir = base_dir / test_name / f"{params_prefix}_{params_hash}"
    else:
        final_dir = base_dir / test_name

    # Clean and create directory
    if final_dir.exists():
        shutil.rmtree(final_dir)

    final_dir.mkdir(parents=True, exist_ok=True)

    return final_dir
