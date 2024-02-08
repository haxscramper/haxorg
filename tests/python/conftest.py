import pytest
from pathlib import Path
from py_scriptutils.repo_files import get_haxorg_repo_root_path
import subprocess
import re
from beartype.typing import Tuple, Optional
from beartype import beartype
from dataclasses import dataclass
import json
from plumbum import local, ProcessExecutionError

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


@beartype
@dataclass
class GTestParams():
    class_name: str
    test_name: str
    parameter_name: Optional[str] = None
    parameter_desc: Optional[dict] = None

    def get_source_file(self) -> str:
        if self.parameter_desc and "loc" in self.parameter_desc:
            test_absolute = Path(self.parameter_desc["loc"]["path"])
            return str(test_absolute.relative_to(get_haxorg_repo_root_path()))

        else:
            return ""

    def get_source_line(self) -> Optional[int]:
        if self.parameter_desc and "loc" in self.parameter_desc:
            return self.parameter_desc["loc"]["line"]

        else:
            return None

    def group_name(self):
        if self.parameter_name:
            return f"{self.class_name}/{self.test_name}"

        else:
            return self.class_name

    def item_name(self):
        return self.parameter_name or self.test_name
    
    def gtest_params(self):
        if self.parameter_name:
            result = [f"--gtest_filter={self.class_name}.{self.test_name}/{self.parameter_name}"]
        else:
            result = [f"--gtest_filter={self.class_name}.{self.test_name}"]

        result.append("--gtest_brief=1")
        result.append("--hax_vscode_run")

        return result
        
    def fullname(self):
        if self.parameter_name:
            return f"{self.class_name}/{self.test_name}.{self.parameter_name}"
        else:
            return f"{self.class_name}.{self.test_name}"


def parse_google_tests(binary_path: str) -> list[GTestParams]:
    result = subprocess.run(
        [binary_path, "--gtest_list_tests"],
        capture_output=True,
        text=True,
    )
    tests = []
    current_suite = None

    for line in result.stdout.splitlines():
        if line.endswith('.'):
            current_suite = line[:-1]
        else:
            test_name = line.strip().split(' ')[0]
            if "/" in test_name:
                main_name, parameter_name = test_name.split("/")
                tests.append(
                    GTestParams(
                        class_name=current_suite,
                        test_name=main_name,
                        parameter_name=parameter_name,
                        parameter_desc=json.loads(
                            line.strip().split('# GetParam() = ')[1]),
                    ))

            else:
                tests.append(GTestParams(class_name=current_suite, test_name=test_name))

    return tests


binary_path: str = str(
    get_haxorg_repo_root_path().joinpath("build/haxorg_debug/tests_org"))


def pytest_collect_file(parent, path):
    if path.basename == "test_integrate_cxx_org.py":
        return GTestFile.from_parent(parent, fspath=path)


class GTestClass(pytest.Class):

    def __init__(self, name, parent):
        super().__init__(name, parent)
        self.tests: list[GTestParams] = []

    def add_test(self, test: GTestParams):
        self.tests.append(test)

    def collect(self):
        for test in self.tests:
            yield GTestItem.from_parent(
                self,
                gtest=test,
                name=test.item_name(),
                callobj=lambda: None,
            )

    def _getobj(self):
        # Return a dummy class object
        return type(self.name, (object,), {})


@dataclass
class GTestRunError(Exception):
    shell_error: ProcessExecutionError
    item: 'GTestItem'

    def __str__(self):
        result = []
        result.append("error message: " + " ".join(self.item.gtest.gtest_params()))
        if self.shell_error.stdout:
            result.append(self.shell_error.stdout)

        if self.shell_error.stderr:
            result.append(self.shell_error.stderr)

        return "\n".join(result)

# def pytest_exception_interact(node, call, report):
#     if report.failed and isinstance(call.excinfo.value, GTestRunError):
#         # Modify the report's long representation (longrepr) to only include the desired output
#         report.longrepr = str(call.excinfo.value.shell_error.stderr)

class GTestItem(pytest.Function):

    def __init__(self, gtest: GTestParams, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.gtest = gtest

    def runtest(self):
        try:
            local[binary_path](*self.gtest.gtest_params())

        except ProcessExecutionError as e:
            raise GTestRunError(e, self) from None


    @property
    def location(self) -> Tuple[str, Optional[int], str]:
        # vscode python plugin has a check for `if testfunc and fullname != testfunc + parameterized:`
        return (self.gtest.get_source_file(), self.gtest.get_source_line(),
                self.gtest.fullname())

    def _getobj(self):
        # Return a dummy function
        return lambda: None


class GTestFile(pytest.Module):

    def collect(self):
        class_tests = {}
        for test in parse_google_tests(binary_path):
            class_tests.setdefault(test.group_name(), []).append(test)

        for class_name, tests in class_tests.items():
            gtest_class = GTestClass.from_parent(self, name=class_name)
            for test in tests:
                gtest_class.add_test(test)

            yield gtest_class
