import pytest
import json
from plumbum import local, ProcessExecutionError
from beartype import beartype
from dataclasses import dataclass
from beartype.typing import Optional, Tuple, List
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from pathlib import Path
import subprocess
import os


@beartype
@dataclass
class QTestParams():
    test_name: str
    meth_name: str

    def class_name(self):
        return self.test_name.replace(" ", "")

    def item_name(self):
        return self.meth_name.replace("test_", "")

    def qtest_params(self):
        result = [f"{self.test_name}::{self.meth_name}"]
        return result

    def fullname(self):
        return f"{self.class_name()}.{self.item_name()}"


def parse_qt_tests(binary_path: str) -> list[QTestParams]:
    dbg = open("/tmp/debug", "w")
    print("1", file=dbg)
    cmd = local[binary_path]
    cmd = cmd.with_cwd(str(get_haxorg_repo_root_path()))
    print("2", file=dbg)
    print(binary_path)
    print("3", file=dbg)

    for key in sorted(os.environ.keys()):
        print(key, os.getenv(key), file=dbg)

    code, stdout, stderr = cmd.run(["-functions"])
    print(binary_path, file=dbg)
    print(stdout, file=dbg)
    print(stderr, file=dbg)
    print(code, file=dbg)
    assert (code == 0, f"{stdout}\n{stderr}")
    tests = []

    line: str
    for line in stderr.splitlines():
        if "QML debugging" in line:
            continue

        else:
            class_name, test_name = line.strip().split('::')
            test_name = test_name.replace("()", "")
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
                qtest=test,
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
        result.append("error message: " + " ".join(self.item.qtest.qtest_params()))
        if self.shell_error.stdout:
            result.append(self.shell_error.stdout)

        if self.shell_error.stderr:
            result.append(self.shell_error.stderr)

        return "\n".join(result)


class QTestItem(pytest.Function):

    def __init__(self, qtest: QTestParams, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.qtest = qtest

    def runtest(self):
        try:
            local[binary_path](*self.qtest.qtest_params())

        except ProcessExecutionError as e:
            raise QTestRunError(e, self) from None

    @property
    def location(self) -> Tuple[str, Optional[int], str]:
        # vscode python plugin has a check for `if testfunc and fullname != testfunc + parameterized:`
        return ("location", None, self.qtest.fullname())

    def _getobj(self):
        # Return a dummy function
        return lambda: None


class QTestFile(pytest.Module):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.test_classes: List[QTestClass] = []
        class_tests = {}
        for test in parse_qt_tests(binary_path):
            class_tests.setdefault(test.class_name(), []).append(test)

        for class_name, tests in class_tests.items():
            test_class: QTestClass = QTestClass.from_parent(self, name=class_name)
            for test in tests:
                test_class.add_test(test)

            self.test_classes.append(test_class)
        

    def collect(self):
        for it in self.test_classes:
            yield it

