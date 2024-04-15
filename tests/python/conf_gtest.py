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

COOKIE_SUFFIX = ".profdata-cookie"


@beartype
def get_profile_base(coverage: Path, test_name: str) -> Path:
    return coverage.joinpath(test_name.replace("/", "_").replace(".", "_"))


@beartype
def get_profraw_path(coverage: Path, test_name: str) -> Path:
    return get_profile_base(coverage, test_name).with_suffix(".profraw")


class ProfdataCookie(BaseModel, extra="forbid"):
    test_binary: str
    test_name: str
    test_class: Optional[str] = None
    test_profile: str
    test_params: Any = None


class ProfdataFullProfile(BaseModel, extra="forbid"):
    runs: List[ProfdataCookie] = Field(default_factory=list)


def summarize_cookies(coverage: Path) -> ProfdataFullProfile:
    result = ProfdataFullProfile()
    for path in coverage.glob("*" + COOKIE_SUFFIX):
        result.runs.append(ProfdataCookie.model_validate(json.loads(path.read_text())))

    return result


@beartype
@dataclass
class GTestParams():
    class_name: str
    test_name: str
    parameter_name: Optional[str] = None
    parameter_desc: Optional[dict] = None
    coverage_out_dir: Optional[Path] = None

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
            result = [
                f"--gtest_filter={self.class_name}.{self.test_name}/{self.parameter_name}"
            ]
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


binary_path: str = str(get_haxorg_repo_root_path().joinpath("build/haxorg/tests_org"))


class GTestClass(pytest.Class):

    def __init__(self, coverage_out_dir: Path, name, parent):
        super().__init__(name, parent)
        self.tests: list[GTestParams] = []
        self.coverage_out_dir = coverage_out_dir

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
            result.append(self.shell_error.stderr)

        return "\n".join(result)


class GTestItem(pytest.Function):

    def __init__(self, gtest: GTestParams, coverage_out_dir: Path, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.gtest = gtest
        self.coverage_out_dir = coverage_out_dir

    def runtest(self):
        test = Path(binary_path)

        def run(env: Optional[dict] = None):
            try:
                cmd = local[test]
                if env:
                    cmd = cmd.with_env(**env)

                cmd.run(self.gtest.gtest_params())

            except ProcessExecutionError as e:
                raise GTestRunError(e, self) from None

        if self.coverage_out_dir:
            uniq_name = self.gtest.fullname()
            profraw = get_profraw_path(self.coverage_out_dir, test_name=uniq_name)
            cookie = ProfdataCookie(
                test_binary=str(test),
                test_class=self.gtest.class_name,
                test_name=self.gtest.test_name,
                test_profile=str(profraw),
            )

            run({"LLVM_PROFILE_FILE": str(profraw)})

            cookie_path = get_profile_base(
                self.coverage_out_dir,
                uniq_name,
            ).with_suffix(COOKIE_SUFFIX)

            cookie_path.write_text(cookie.model_dump_json(indent=2))

        else:
            run()

    @property
    def location(self) -> Tuple[str, Optional[int], str]:
        # vscode python plugin has a check for `if testfunc and fullname != testfunc + parameterized:`
        return (self.gtest.get_source_file(), self.gtest.get_source_line(),
                self.gtest.fullname())

    def _getobj(self):
        # Return a dummy function
        return lambda: None


class GTestFile(pytest.Module):

    def __init__(self, coverage_out_dir: Path, *args, **kwargs):
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
