import pytest
import json
from plumbum import local, ProcessExecutionError
from beartype import beartype
from dataclasses import dataclass
from beartype.typing import Optional, Tuple, List, Any
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from pathlib import Path
import subprocess
from pydantic import BaseModel, Field
import json
import plumbum
from py_scriptutils.script_logging import pprint_to_file, to_debug_json
import conf_test_common as tconf


@beartype
@dataclass
class GTestParams():
    class_name: str
    test_name: str
    binary_path: Path
    gtest_run_name: str
    gsuite_name: Optional[str] = None
    parameter_name: Optional[str] = None
    test_params: Optional[dict] = None
    coverage_out_dir: Optional[Path] = None

    def get_test_kwargs(self) -> dict:
        """
        Return optional 'kwargs' field from the JSON dump of the parameter description. GTest test dump
        can have an optional field `value_params` with string dump of the parametrized value, which in case
        of the parametric google tests for the org corpus is used for JSON representation of the parameter.
        See [[code:corpusrunner.cpp:TestParams::PrintToImpl]]
        """
        if self.test_params and "kwargs" in self.test_params:
            return self.test_params["kwargs"]

        else:
            return dict()

    def get_source_file(self) -> str:
        if self.test_params and "loc" in self.test_params:
            test_absolute = Path(self.test_params["loc"]["path"])
            return str(test_absolute.relative_to(get_haxorg_repo_root_path()))

        else:
            return ""

    def get_source_line(self) -> Optional[int]:
        if self.test_params and "loc" in self.test_params:
            return self.test_params["loc"]["line"]

        else:
            return None

    def group_name(self):
        return self.class_name

    def item_name(self):
        return self.parameter_name or self.test_name

    def gtest_params(self):
        result = [f"--gtest_filter={self.gtest_run_name}"]
        result.append("--gtest_brief=1")
        result.append("--hax_vscode_run")

        return result

    def fullname(self):
        if self.parameter_name:
            return f"{self.class_name}/{self.test_name}.{self.parameter_name}"
        else:
            return f"{self.class_name}.{self.test_name}"


class GTestClassMethod(BaseModel, extra="forbid"):
    name: str
    file: str
    line: int
    value_param: Optional[str] = None


class GTestClassModel(BaseModel, extra="forbid"):
    name: str
    tests: int
    testsuite: List[GTestClassMethod]


class GTestsuiteModel(BaseModel, extra="forbid"):
    tests: int
    name: str
    testsuites: List[GTestClassModel]


@beartype
def parse_google_tests(binary_path: Path) -> list[GTestParams]:
    assert binary_path.exists(), binary_path
    cmd = plumbum.local[binary_path]
    report_file = Path(f"/tmp/report_{binary_path.name}.json")
    cmd.run([
        "--gtest_list_tests",
        f"--gtest_output=json:{report_file}",
    ])

    model = GTestsuiteModel.model_validate(json.loads(report_file.read_text()))

    print("----")
    # print(result.stdout)
    print(binary_path)
    tests = []

    for suite in model.testsuites:
        for method in suite.testsuite:
            if method.value_param:
                gsuite_name, gclass_name = suite.name.split("/")
                gtest_name, gparam_name = method.name.split("/")
                tests.append(
                    GTestParams(
                        class_name=gclass_name,
                        test_name=gtest_name,
                        binary_path=binary_path,
                        test_params=json.loads(method.value_param),
                        parameter_name=gparam_name,
                        gtest_run_name=
                        f"{gsuite_name}/{gclass_name}.{gtest_name}/{gparam_name}",
                        gsuite_name=gsuite_name,
                    ))

            else:
                tests.append(
                    GTestParams(
                        gtest_run_name=f"{suite.name}.{method.name}",
                        class_name=suite.name,
                        test_name=method.name,
                        binary_path=binary_path,
                    ))

    pprint_to_file(to_debug_json(tests), f"/tmp/gtest_parse_{binary_path.name}.py")

    return tests


class GTestClass(pytest.Class):

    def __init__(self, coverage_out_dir: Path, name, parent):
        super().__init__(name, parent)
        self.tests: list[GTestParams] = []
        self.coverage_out_dir = coverage_out_dir
        self.add_marker(pytest.mark.test_gtest_class(name, []))

    def add_test(self, test: GTestParams):
        self.tests.append(test)

    def collect(self):
        for test in self.tests:
            yield GTestItem.from_parent(
                self,
                gtest=test,
                name=test.item_name(),
                callobj=lambda: None,
                coverage_out_dir=self.coverage_out_dir,
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
            result.append(self.shell_error.stderr())

        return "\n".join(result)


class GTestItem(pytest.Function):

    def __init__(self, gtest: GTestParams, coverage_out_dir: Path, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.gtest = gtest
        self.coverage_out_dir = coverage_out_dir
        self.add_marker(pytest.mark.test_gtest())
        self.add_marker(pytest.mark.test_gtest_function(gtest.item_name(), []))
        if "tags" in gtest.get_test_kwargs():
            for tag in gtest.get_test_kwargs()["tags"]:
                self.add_marker(pytest.mark.test_gtest_tag(tag))

    def runtest(self):
        test = Path(self.gtest.binary_path)

        try:
            tconf.runtest(
                test,
                self.gtest.gtest_params(),
                coverage_out_dir=self.coverage_out_dir,
                uniq_name=self.gtest.fullname(),
                class_name=self.gtest.class_name,
                test_name=self.gtest.test_name,
                parameter_desc=self.gtest.test_params,
            )

        except plumbum.ProcessExecutionError as e:
            raise GTestRunError(e, self)

    def _getobj(self):
        # Return a dummy function
        return lambda: None


class GTestFile(pytest.Module):

    def __init__(self, binary_path: Path, coverage_out_dir: Path, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.test_classes: List[GTestClass] = []
        class_tests = {}
        for test in parse_google_tests(binary_path):
            class_tests.setdefault(test.group_name(), []).append(test)

        for class_name, tests in class_tests.items():
            gtest_class = GTestClass.from_parent(
                self,
                name=class_name,
                coverage_out_dir=coverage_out_dir,
            )
            for test in tests:
                gtest_class.add_test(test)

            self.test_classes.append(gtest_class)

    def collect(self):
        for it in self.test_classes:
            yield it
