import pytest
from pathlib import Path
from py_scriptutils.tracer import TraceCollector
from conf_gtest import GTestFile
from conf_qtest import QTestFile
from beartype import beartype
from py_scriptutils.script_logging import pprint_to_file, to_debug_json

from _pytest.config import Config
from _pytest.config.argparsing import Parser
from _pytest.nodes import Item
from _pytest.python import Module

trace_collector: TraceCollector = None


def get_trace_collector():
    global trace_collector
    if not trace_collector:
        trace_collector = TraceCollector()

    return trace_collector


def pytest_addoption(parser: Parser) -> None:
    parser.addoption(
        "--coverage-out-dir",
        action="store",
        default=None,
        help="CXX code coverage output location",
    )


@pytest.fixture(scope="session", autouse=True)
def trace_session():
    get_trace_collector().push_complete_event("session", "test-session")
    yield
    get_trace_collector().pop_complete_event()
    get_trace_collector().export_to_json(Path("/tmp/haxorg_py_tests.json"))


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
        coverage = parent.config.getoption("--coverage-out-dir")
        result = GTestFile.from_parent(
            parent,
            path=test,
            coverage_out_dir=coverage and Path(coverage),
        )

        debug(result, "/tmp/google_tests")
        return result

    elif test.name == "test_integrate_qt.py":
        pass
        # result = QTestFile.from_parent(parent, path=path)
        # debug(result, "/tmp/qt_tests")
        # # return result
