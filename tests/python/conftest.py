import pytest
from pathlib import Path
from py_scriptutils.repo_files import get_haxorg_repo_root_path
import subprocess
import re
from beartype.typing import Tuple, Optional
from beartype import beartype
from dataclasses import dataclass

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


binary_path: str = str(get_haxorg_repo_root_path().joinpath("build/haxorg_debug/tests_org"))

def pytest_collect_file(parent, path):
    if path.basename == "test_integrate_cxx_org.py":
        return GTestFile.from_parent(parent, fspath=path)


@beartype
@dataclass
class GTestParams():
    class_name: str
    test_name: str

    def fullname(self):
        return f"{self.class_name}.{self.test_name}"


class GTestClass(pytest.Class):
    def __init__(self, name, parent):
        super().__init__(name, parent)
        self.tests: list[GTestParams] = []

    def add_test(self, test: GTestParams):
        self.tests.append(test)

    def collect(self):
        for test in self.tests:
            yield GTestItem.from_parent(self, gtest=test, name=test.test_name, callobj=lambda: None)

    def _getobj(self):
        # Return a dummy class object
        return type(self.name, (object,), {})



class GTestItem(pytest.Function):
    def __init__(self, gtest: GTestParams, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.gtest = gtest

    def runtest(self):
        subprocess.run([binary_path, f"--gtest_filter={self.gtest.fullname()}"])

    @property
    def location(self) -> Tuple[str, Optional[int], str]:
        # vscode python plugin has a check for `if testfunc and fullname != testfunc + parameterized:`
        return ("", None, self.gtest.fullname())

    def _getobj(self):
        # Return a dummy function
        return lambda: None

class GTestFile(pytest.Module):
    def collect(self):
        class_tests = {}
        for test in parse_google_tests(binary_path):
            class_name, test_name = test.split('.', 1)
            class_tests.setdefault(class_name, []).append(test_name)

        for class_name, tests in class_tests.items():
            gtest_class = GTestClass.from_parent(self, name=class_name)
            for test_name in tests:
                gtest_class.add_test(GTestParams(class_name, test_name))

            yield gtest_class

