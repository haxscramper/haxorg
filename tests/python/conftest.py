import pytest
from pathlib import Path
from py_scriptutils.repo_files import get_haxorg_repo_root_path
import os
import subprocess

from py_scriptutils.tracer import TraceCollector

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

def parse_google_tests(binary_path: str) -> list[str]:
    result = subprocess.run([binary_path, "--gtest_list_tests"],
                            capture_output=True, text=True)
    tests = []
    current_suite = None

    for line in result.stdout.splitlines():
        if line.endswith('.'):
            current_suite = line[:-1]
        else:
            test_name = line.strip().split(' ')[0]
            tests.append(f"{current_suite}.{test_name}")

    return tests


binary_path = get_haxorg_repo_root_path().joinpath("build/haxorg_debug/tests_org") 

def pytest_collect_file(parent, path):
    if path.basename == "test_integrate_cxx_org.py":
        return GTestFile.from_parent(parent, fspath=path)


class GTestFile(pytest.File):
    def collect(self):
        for test in parse_google_tests(binary_path):
            yield GTestItem.from_parent(self, name=test)


class GTestItem(pytest.Item):
    def __init__(self, name, parent):
        super(GTestItem, self).__init__(name, parent)

    def runtest(self):
        subprocess.run([binary_path, f"--gtest_filter={self.name}"])

    def repr_failure(self, exception):
        return f"Google Test failed: {exception.value}"

