#!/usr/bin/env python

import pytest
from pathlib import Path
from py_scriptutils.tracer import TraceCollector
from conf_gtest import GTestFile, summarize_cookies
from conf_qtest import QTestFile
from beartype import beartype
import pytest
from py_scriptutils.script_logging import pprint_to_file, to_debug_json

from _pytest.config import Config
from _pytest.config.argparsing import Parser
from _pytest.nodes import Item
from _pytest.python import Module
import os

trace_collector: TraceCollector = None


def get_trace_collector():
    global trace_collector
    if not trace_collector:
        trace_collector = TraceCollector()

    return trace_collector


@pytest.fixture(scope="session", autouse=True)
def trace_session():
    get_trace_collector().push_complete_event("session", "test-session")
    yield
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
        result = QTestFile.from_parent(parent, path=test)
        debug(result, "/tmp/qt_tests")
        return result
