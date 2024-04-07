from beartype.typing import List, Optional, Union, Dict
from pydantic import BaseModel, root_validator, ValidationError
from beartype import beartype
from plumbum import local
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from pathlib import Path
import hashlib
from py_scriptutils.files import IsNewInput

from py_scriptutils.script_logging import log
import warnings

warnings.filterwarnings("ignore", category=DeprecationWarning)

CAT = "cxx-coverager"
COOKIE_SUFFIX = ".prfdata-cookie"


@beartype
def get_profile_root() -> Path:
    path = get_haxorg_repo_root_path().joinpath("build/profdata")
    path.mkdir(parents=True, exist_ok=True)
    return path


@beartype
def get_profile_base(test_name: str) -> Path:
    return get_profile_root().joinpath(test_name.replace("/", "_"))


@beartype
def get_profraw_path(test_name: str) -> Path:
    return get_profile_base(test_name).with_suffix(".profraw")


@beartype
def get_profdata_path(test_name: str) -> Path:
    return get_profile_base(test_name).with_suffix(".profdata")


@beartype
def get_prof_export_path(test_name: str) -> Path:
    return get_profile_base(test_name).with_suffix(".json")


@beartype
def get_prof_html_path(test_name: str) -> Path:
    return get_profile_base(test_name).with_suffix(".html.d")


class ProfdataCookie(BaseModel, extra="forbid"):
    test_binary: str
    test_name: str


@beartype
def write_profdata_cookie(test_binary: Path, test_name: str):
    get_profile_base(test_name).with_suffix(COOKIE_SUFFIX).write_text(
        ProfdataCookie(
            test_binary=str(test_binary),
            test_name=test_name,
        ).model_dump_json())


class LLVMSegment(BaseModel):
    line: int
    column: int
    count: int
    has_count: bool
    in_region_entry: bool
    is_gap_region: bool

    @root_validator(pre=True)
    def parse_list_to_fields(cls, values):
        if isinstance(values, list):
            return {
                'line': values[0],
                'column': values[1],
                'count': values[2],
                'has_count': values[3],
                'in_region_entry': values[4],
                'is_gap_region': values[5]
            }

        else:
            return values


class LLVMBranch(BaseModel):
    line_start: int
    column_start: int
    line_end: int
    column_end: int
    count: int
    file_id: int
    expanded_file_id: int
    kind: int

    @root_validator(pre=True)
    def parse_list_to_fields(cls, values):
        if isinstance(values, list):
            return {
                'line_start': values[0],
                'column_start': values[1],
                'line_end': values[2],
                'column_end': values[3],
                'count': values[4],
                'file_id': values[5],
                'expanded_file_id': values[6],
                'kind': values[7],
            }

        else:
            return values


class LLVMCoverSummary(BaseModel):
    count: int
    covered: int
    percent: float
    notcovered: Optional[int] = None


class LLVMFileCoverageSummary(BaseModel):
    branches: LLVMCoverSummary
    functions: LLVMCoverSummary
    instantiations: LLVMCoverSummary
    lines: LLVMCoverSummary
    regions: LLVMCoverSummary


class LLVMFileCov(BaseModel):
    branches: List[LLVMBranch]
    expansions: List
    filename: str
    segments: List[LLVMSegment]
    summary: LLVMFileCoverageSummary


class LLVMFunctionCov(BaseModel):
    branches: List[List[int]]
    count: int
    filenames: List[str]
    name: str
    regions: List[List[int]]


class LLVMCovInner(BaseModel):
    files: List[LLVMFileCov]
    functions: List[LLVMFunctionCov]


class LLVMCovData(BaseModel):
    type: str
    version: str
    data: List[LLVMCovInner]


class TestRunCoverage(BaseModel, extra="forbid"):
    coverage: LLVMCovData


@beartype
def get_profile_model(
    cookie: ProfdataCookie,
    tools_dir: Path = get_haxorg_repo_root_path().joinpath("toolchain/llvm/bin"),
) -> TestRunCoverage:
    profraw = get_profraw_path(cookie.test_name)
    if profraw.exists():
        profdata = get_profdata_path(cookie.test_name)
        json_path = get_prof_export_path(cookie.test_name)
        json_clean = json_path.with_stem(json_path.name + "clean")
        json_model = json_path.with_stem(json_path.name + "model")

        should_rebuild_model = False

        if not profdata.exists():
            llvm_profdata = local[tools_dir.joinpath("llvm-profdata")]
            llvm_profdata.run([
                "merge",
                "-output=" + str(profdata),
                str(profraw),
            ])

        if json_model.exists():
            try:
                log(CAT).info(f"JSON model dump exists {json_model}")
                model = TestRunCoverage.model_validate_json(json_model.read_text())
                return model

            except ValidationError as err:
                log(CAT).info(f"Model format changed {err}")
                should_rebuild_model = True

        else:
            log(CAT).info(f"JSON model file is missing {json_model}")
            should_rebuild_model = True

        if should_rebuild_model:
            if not json_path.exists():
                cmd = local[tools_dir.joinpath("llvm-cov")][
                    "export",
                    str(cookie.test_binary),
                    "--ignore-filename-regex=.*?thirdparty.*?",
                    "-format=text",
                    "--line-coverage-gt=0",
                    "--region-coverage-gt=0",
                    f"-instr-profile={profdata}",
                ] > str(json_path)

                cmd.run()

            if not get_prof_html_path(cookie.test_binary).exists():
                html = local[tools_dir.joinpath("llvm-cov")][
                    "show",
                    str(cookie.test_binary),
                    f"-instr-profile={profdata}",
                    "-ignore-filename-regex",
                    ".*/(_?deps|thirdparty)/.*",
                    "-format=html",
                    f"-output-dir={get_prof_html_path(cookie.test_binary)}",
                ]

                html.run()

            if IsNewInput(
                    input_path=[
                        json_path,
                        get_haxorg_repo_root_path().joinpath(
                            "scripts/py_repository/py_repository/cxx_coverage.jq"),
                    ],
                    output_path=[json_clean],
            ):
                jq_run = (local["jq"][
                    f"include \"cxx_coverage\"; . | filter_raw_json",
                    "-L",
                    get_haxorg_repo_root_path().
                    joinpath("scripts/py_repository/py_repository"),
                ] < str(json_path)) > str(json_clean)

                jq_run.run()

            log(CAT).info(f"Loading base JSON coverage data from {json_clean}")
            model = TestRunCoverage(
                coverage=LLVMCovData.model_validate_json(json_clean.read_text()))

            json_model.write_text(model.model_dump_json())

            return model

    else:
        raise RuntimeError(
            f"{profraw} does not exist after running test binary {cookie.test_binary}")
