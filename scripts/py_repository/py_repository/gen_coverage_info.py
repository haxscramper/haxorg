from beartype.typing import List, Optional, Union, Dict
from pydantic import BaseModel
from beartype import beartype
from plumbum import local
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from pathlib import Path


@beartype
def get_profile_file(test_binary: Path) -> Path:
    return Path(f"{test_binary.parent}/default.profraw")


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
    profraw = get_profile_file(test_binary)
    if profraw.exists():
        profdata = profraw.with_suffix(".profdat")
        llvm_profdata = local[tools_dir.joinpath("llvm-profdata")]
        llvm_profdata.run([
            "merge",
            "-output=" + str(profdata),
            str(profraw),
        ])

        llvm_cov = local[tools_dir.joinpath("llvm-cov")]

        llvm_cov.run([
            "show",
            str(test_binary),
            "-ignore-filename-regex",
            ".*/(_?deps|thirdparty)/.*",
            "-instr-profile=" + str(profdata),
            "-format=text",
            "-output-dir=" + str(coverage_out_dir),
        ])

    else:
        raise RuntimeError(
            f"{profraw} does not exist after running test binary {test_binary}")
