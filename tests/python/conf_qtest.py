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

GUI_SCREEN_DISPLAY = ":14"


@beartype
@dataclass
class QTestParams():
    test_name: Optional[str]
    meth_name: str

    def class_name(self) -> Optional[str]:
        return self.test_name and self.test_name.replace(" ", "")

    def item_name(self):
        return self.meth_name.replace("test_", "")

    def qtest_params(self):
        if self.test_name:
            return [f"{self.test_name}::{self.meth_name}"]

        else:
            return [self.meth_name]

    def fullname(self):
        if self.test_name:
            return f"{self.class_name()}.{self.item_name()}"

        else:
            return self.item_name()


def parse_qt_tests(binary_path: str,
                   in_class_name: Optional[str] = None) -> list[QTestParams]:
    dbg = open("/tmp/debug", "w")
    print("1", file=dbg)
    cmd = local[binary_path]
    cmd = cmd.with_cwd(str(get_haxorg_repo_root_path()))
    print("2", file=dbg)
    print(binary_path, file=dbg)
    print("3", file=dbg)

    code, stdout, stderr = cmd.run(["-functions"])
    print(binary_path, file=dbg)
    print(stdout, file=dbg)
    print(stderr, file=dbg)
    print(code, file=dbg)
    assert code == 0, f"{stdout}\n{stderr}"
    tests = []

    line: str
    for line in stdout.splitlines():
        if "QML debugging" in line:
            continue

        else:
            if "::" in line:
                class_name, test_name = line.strip().split('::')

            else:
                class_name = in_class_name
                test_name = line

            test_name = test_name.replace("()", "")
            tests.append(QTestParams(test_name=class_name, meth_name=test_name))

    return tests


binary_path: str = str(
    get_haxorg_repo_root_path().joinpath("build/haxorg/src/editor/editor_test"))


class QTestClass(pytest.Class):

    def __init__(self, name, parent):
        super().__init__(name or "QtGui", parent)
        self.tests: list[QTestParams] = []

    def add_test(self, test: QTestParams):
        self.tests.append(test)

    def collect(self):
        for test in self.tests:
            test_item = QTestItem.from_parent(
                self,
                qtest=test,
                name=test.item_name(),
                callobj=lambda: None,
            )

            test_item.add_marker("x11")

            if test_item.name in [
                    "testParagraphMovements",
            ]:
                test_item.add_marker("unstable")

            yield test_item

    def _getobj(self):
        # Return a dummy class object
        return type(self.name, (object,), {})


@dataclass
class QTestRunError(Exception):
    shell_error: ProcessExecutionError
    item: 'QTestItem'

    def __str__(self):
        result = []
        result.append("")
        result.append(f"command: {self.shell_error.argv}")
        result.append("error message:\n" + " ".join(self.item.qtest.qtest_params()))
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
            local[binary_path].with_env(DISPLAY=GUI_SCREEN_DISPLAY)(
                *self.qtest.qtest_params())

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
        qt_test_config = json.loads(get_haxorg_repo_root_path().joinpath(
            "src/editor/editor_test/test_config.json").read_text())

        self.test_classes: List[QTestClass] = []
        class_tests = {}
        for binary in qt_test_config:
            for test in parse_qt_tests(
                    binary_path=get_haxorg_repo_root_path().joinpath(
                        "build/haxorg/src/editor").joinpath(binary["class_name"] + "_test"),
                    in_class_name=binary["class_name"],
            ):
                class_tests.setdefault(test.class_name(), []).append(test)

        for class_name, tests in class_tests.items():
            test_class: QTestClass = QTestClass.from_parent(self, name=class_name)
            for test in tests:
                test_class.add_test(test)

            self.test_classes.append(test_class)

    def collect(self):
        for it in self.test_classes:
            yield it
