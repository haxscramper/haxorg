import pytest
import json
from plumbum import local, ProcessExecutionError
from beartype import beartype
from dataclasses import dataclass
from beartype.typing import Optional, Tuple
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from pathlib import Path
import subprocess


@beartype
@dataclass
class QTestParams():
    test_name: str
    meth_name: str

    def class_name(self):
        return self.test_name.replace(" ", "_")
    
    def item_name(self):
        return self.meth_name

    def qtest_params(self):
        result = [f"{self.test_name}::{self.meth_name}"]
        return result

    def fullname(self):
        return f"{self.class_name()}::{self.item_name()}"


def parse_qt_tests(binary_path: str) -> list[QTestParams]:
    cmd = local[binary_path]
    print(binary_path)
    code, stdout, stderr = cmd.run(["-functions"])
    assert(code == 0, f"{stdout}\n{stderr}")
    tests = []

    for line in stderr.splitlines():
        if "QML debugging" in line:
            continue

        else:
            class_name, test_name = line.strip().split('::')
            test_name.strip("()")
            tests.append(QTestParams(test_name=class_name, meth_name=test_name))

    return tests


binary_path: str = str(
    get_haxorg_repo_root_path().joinpath("build/haxorg_debug/src/editor/gui_tests"))


class QTestClass(pytest.Class):

    def __init__(self, name, parent):
        super().__init__(name, parent)
        self.tests: list[QTestParams] = []

    def add_test(self, test: QTestParams):
        self.tests.append(test)

    def collect(self):
        for test in self.tests:
            yield QTestItem.from_parent(
                self,
                Qtest=test,
                name=test.item_name(),
                callobj=lambda: None,
            )

    def _getobj(self):
        # Return a dummy class object
        return type(self.name, (object,), {})


@dataclass
class QTestRunError(Exception):
    shell_error: ProcessExecutionError
    item: 'QTestItem'

    def __str__(self):
        result = []
        result.append("error message: " + " ".join(self.item.Qtest.Qtest_params()))
        if self.shell_error.stdout:
            result.append(self.shell_error.stdout)

        if self.shell_error.stderr:
            result.append(self.shell_error.stderr)

        return "\n".join(result)


class QTestItem(pytest.Function):

    def __init__(self, Qtest: QTestParams, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.Qtest = Qtest

    def runtest(self):
        try:
            local[binary_path](*self.Qtest.Qtest_params())

        except ProcessExecutionError as e:
            raise QTestRunError(e, self) from None

    def _getobj(self):
        # Return a dummy function
        return lambda: None


class QTestFile(pytest.Module):

    def collect(self):
        class_tests = {}
        for test in parse_qt_tests(binary_path):
            class_tests.setdefault(test.class_name(), []).append(test)

        for class_name, tests in class_tests.items():
            test_class = QTestClass.from_parent(self, name=class_name)
            for test in tests:
                test_class.add_test(test)

            yield test_class
