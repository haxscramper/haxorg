from pathlib import Path

from beartype import beartype
from beartype.typing import List, Optional
import plumbum
from py_repository.code_analysis.gen_coverage_cxx import (
    ProfdataCookie,
    ProfdataFullProfile,
)
from py_scriptutils.script_logging import log
import pytest

CAT = "conftest"

COOKIE_SUFFIX = ".profdata-cookie"


@beartype
def get_profile_base(coverage: Path, test_name: str) -> Path:
    return coverage.joinpath(test_name.replace("/", "_").replace(".", "_"))


@beartype
def get_profraw_path(coverage: Path, test_name: str) -> Path:
    return get_profile_base(coverage, test_name).with_suffix(".profraw")


def _get_cookie_list() -> List[ProfdataCookie]:
    """Get or create the cookie list from pytest's shared state"""
    if not hasattr(pytest, '_haxorg_cookie_list'):
        pytest._haxorg_cookie_list = []  # type: ignore
    return pytest._haxorg_cookie_list  # type: ignore


def summarize_cookies(coverage: Path) -> ProfdataFullProfile:
    log(CAT).info(f"Summarizing full count of summaries is {len(_get_cookie_list())}")
    return ProfdataFullProfile(runs=_get_cookie_list())


@beartype
def runtest(
    test: Path,
    args: List[str],
    uniq_name: str,
    class_name: str,
    test_name: str,
    run_env: Optional[dict] = None,
    parameter_desc: Optional[dict] = None,
    coverage_out_dir: Optional[Path] = None,
) -> tuple[int, str, str]:
    global cookie_list

    env = run_env or {}

    def run(env: Optional[dict] = None) -> tuple[int, str, str]:
        cmd = plumbum.local[test]
        if env:
            cmd = cmd.with_env(**env, LD_PRELOAD="")

        else:
            cmd = cmd.with_env(LD_PRELOAD="")

        return cmd.run(args)

    if coverage_out_dir:
        profraw = get_profraw_path(coverage_out_dir, test_name=uniq_name)
        cookie = ProfdataCookie(
            test_binary=str(test),
            test_class=class_name,
            test_name=test_name,
            test_profile=str(profraw),
            test_params=parameter_desc,
        )

        if profraw.exists():
            profraw.unlink()

        result = run(dict(**env, LLVM_PROFILE_FILE=str(profraw)))
        _get_cookie_list().append(cookie)
        log(CAT).info(
            f"Test {cookie.test_class}::{cookie.test_name} result {cookie.test_profile}, full count of summaries is {len(_get_cookie_list())}"
        )
        return result

    else:
        return run(env)
