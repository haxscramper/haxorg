from py_repository.gen_coverage_cxx import ProfdataCookie, ProfdataFullProfile
from beartype import beartype
from pathlib import Path
from beartype.typing import List, Optional
import plumbum
from py_scriptutils.script_logging import log

CAT = "conftest"

COOKIE_SUFFIX = ".profdata-cookie"


@beartype
def get_profile_base(coverage: Path, test_name: str) -> Path:
    return coverage.joinpath(test_name.replace("/", "_").replace(".", "_"))


@beartype
def get_profraw_path(coverage: Path, test_name: str) -> Path:
    return get_profile_base(coverage, test_name).with_suffix(".profraw")


cookie_list: List[ProfdataCookie] = []


def summarize_cookies(coverage: Path) -> ProfdataFullProfile:
    result = ProfdataFullProfile(runs=cookie_list)
    return result


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

    env = run_env or {}

    def run(env: Optional[dict] = None) -> tuple[int, str, str]:
        cmd = plumbum.local[test]
        if env:
            cmd = cmd.with_env(**env)

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
        cookie_list.append(cookie)
        return result

    else:
        return run(env)
