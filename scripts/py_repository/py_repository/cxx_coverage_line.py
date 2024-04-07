from beartype.typing import List, Optional, Union, Dict
from pydantic import BaseModel
from beartype import beartype
from plumbum import local
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from pathlib import Path

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


@beartype
def convert_profile_information(
        test_binary: Path,
        coverage_out_dir: Path,
        tools_dir: Path = get_haxorg_repo_root_path().joinpath("toolchain/llvm/bin"),
):
    profraw = get_profraw_path(test_binary)
    if profraw.exists():
        profdata = get_profdata_path(test_binary)
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
        ] > str(get_prof_export_path(test_binary))

        log(CAT).info(get_prof_export_path(test_binary))
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

    else:
        raise RuntimeError(
            f"{profraw} does not exist after running test binary {test_binary}")
