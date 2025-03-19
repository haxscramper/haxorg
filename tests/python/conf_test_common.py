from py_repository.gen_coverage_cxx import ProfdataCookie, ProfdataFullProfile
from beartype import beartype
from pathlib import Path
from beartype.typing import List, Optional
import plumbum
from py_scriptutils.script_logging import log
from py_scriptutils.repo_files import (
    HaxorgConfig,
    get_haxorg_repo_root_config,
    HaxorgCoverageCookiePattern,
    HaxorgCoverageAggregateFilter,
)
import re

CAT = "conftest"

COOKIE_SUFFIX = ".profdata-cookie"


@beartype
def get_profile_base(coverage: Path, test_name: str) -> Path:
    return coverage.joinpath(test_name.replace("/", "_").replace(".", "_"))


@beartype
def get_profraw_path(coverage: Path, test_name: str) -> Path:
    return get_profile_base(coverage, test_name).with_suffix(".profraw")


cookie_list: List[ProfdataCookie] = []


def filter_cookies(
        cookies: List[ProfdataCookie],
        aggregate_filter: HaxorgCoverageAggregateFilter) -> List[ProfdataCookie]:
    if not aggregate_filter.whitelist_patterns:
        return []

    filtered_cookies = []

    for cookie in cookies:
        # Check whitelist
        if any(
                matches_pattern(cookie, pattern)
                for pattern in aggregate_filter.whitelist_patterns):
            # Check blacklist
            if not any(
                    matches_pattern(cookie, pattern)
                    for pattern in aggregate_filter.blacklist_patterns):
                filtered_cookies.append(cookie)

    return filtered_cookies


def matches_pattern(cookie: ProfdataCookie, pattern: HaxorgCoverageCookiePattern) -> bool:
    if pattern.binary_pattern and not re.search(pattern.binary_pattern,
                                                cookie.test_binary):
        return False

    if pattern.name_pattern and not re.search(pattern.name_pattern, cookie.test_name):
        return False

    if pattern.class_pattern:
        if cookie.test_class is None:
            return False
        if not re.search(pattern.class_pattern, cookie.test_class):
            return False

    return True


def summarize_cookies(coverage: Path) -> ProfdataFullProfile:
    conf: HaxorgConfig = get_haxorg_repo_root_config()
    result = ProfdataFullProfile()
    if conf.aggregate_filters:
        result.runs = filter_cookies(cookie_list, conf.aggregate_filters)

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
        cookie_list.append(cookie)
        return result

    else:
        return run(env)
