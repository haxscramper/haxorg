from beartype.typing import List, Optional, Union, Dict
from pydantic import BaseModel, root_validator
from beartype import beartype
from plumbum import local
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from pathlib import Path
import hashlib

from py_scriptutils.script_logging import log

CAT = "cxx-coverager"


@beartype
def get_profraw_path(test_binary: Path) -> Path:
    return Path(f"{test_binary.parent}/default.profraw")


@beartype
def get_profdata_path(test_binary: Path) -> Path:
    return get_profraw_path(test_binary).with_suffix(".profdata")


@beartype
def get_prof_export_path(test_binary: Path) -> Path:
    return get_profraw_path(test_binary).with_suffix(".json")


@beartype
def get_prof_html_path(test_binary: Path) -> Path:
    return get_profraw_path(test_binary).with_suffix("").joinpath(
        test_binary.name).with_suffix(".d")


@beartype
def prepare_directory_for_run(test_binary: Path):
    for file in test_binary.parent.glob("*.profdata"):
        file.unlink()


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
    # Profiling information conversion is expensive
    # and unless there is a change in the profraw *content* new file writes are cached.
    profraw_digest: str


@beartype
def get_file_digest(file: Path) -> str:
    hash_md5 = hashlib.md5()

    with open(file, "rb") as f:
        for chunk in iter(lambda: f.read(4096), b""):
            hash_md5.update(chunk)

    return hash_md5.hexdigest()


@beartype
def convert_profile_information(
        test_binary: Path,
        coverage_out_dir: Path,
        tools_dir: Path = get_haxorg_repo_root_path().joinpath("toolchain/llvm/bin"),
):
    profraw = get_profraw_path(test_binary)
    if profraw.exists():
        profdata = get_profdata_path(test_binary)
        json_path = get_prof_export_path(test_binary)
        json_clean = json_path.with_name(json_path.name + "clean")
        json_model = json_path.with_name(json_path.name + "model")

        should_rebuild_model = False
        profraw_digest = get_file_digest(profraw)

        if json_model.exists():
            model = TestRunCoverage.model_validate_json(json_model.read_text())
            if model.profraw_digest != profraw_digest:
                log(CAT).info(f"Profdata digest changed {model.profraw_digest} != {profraw_digest}")
                should_rebuild_model = True

        else:
            log(CAT).info(f"JSON model file is missing {json_model}")
            should_rebuild_model = True

        if should_rebuild_model:
            llvm_profdata = local[tools_dir.joinpath("llvm-profdata")]
            llvm_profdata.run([
                "merge",
                "-output=" + str(profdata),
                str(profraw),
            ])

            cmd = local[tools_dir.joinpath("llvm-cov")][
                "export",
                str(test_binary),
                "--ignore-filename-regex=.*?thirdparty.*?",
                "-format=text",
                "--line-coverage-gt=0",
                "--region-coverage-gt=0",
                f"-instr-profile={profdata}",
            ] > str(json_path)

            cmd.run()

            html = local[tools_dir.joinpath("llvm-cov")][
                "show",
                str(test_binary),
                f"-instr-profile={profdata}",
                "-ignore-filename-regex",
                ".*/(_?deps|thirdparty)/.*",
                "-format=html",
                f"-output-dir={get_prof_html_path(test_binary)}",
            ]

            html.run()

            jq_run = (local["jq"][
                f"include \"cxx_coverage\"; . | filter_raw_json",
                "-L",
                get_haxorg_repo_root_path().joinpath("scripts/py_repository/py_repository"
                                                    ),
            ] < str(json_path)) > str(json_clean)

            jq_run.run()

            model = TestRunCoverage(
                profraw_digest=profraw_digest,
                coverage=LLVMCovData.model_validate_json(json_clean.read_text()),
            )

            json_model.write_text(model.model_dump_json(indent=2))

    else:
        raise RuntimeError(
            f"{profraw} does not exist after running test binary {test_binary}")
