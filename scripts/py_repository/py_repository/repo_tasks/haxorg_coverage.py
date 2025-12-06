from shutil import rmtree
from beartype import beartype
from beartype.typing import List, Optional
import re
from pathlib import Path
import os

import plumbum
from py_ci.util_scripting import get_threading_count
from py_repository.coverage_collection.gen_coverage_cookies import ProfdataCookie, ProfdataFullProfile, ProfdataParams
from py_repository.repo_tasks.workflow_utils import TaskContext, haxorg_task
from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.common import ensure_clean_file, get_build_root, get_component_build_dir
from py_repository.repo_tasks.config import HaxorgCoverageAggregateFilter, HaxorgCoverageCookiePattern
from py_repository.repo_tasks.haxorg_base import get_llvm_root
from py_repository.repo_tasks.haxorg_build import build_haxorg
from py_scriptutils.script_logging import log

CAT = __name__


@beartype
def filter_cookies(
    cookies: List[ProfdataCookie],
    aggregate_filter: HaxorgCoverageAggregateFilter | None,
) -> List[ProfdataCookie]:
    if not aggregate_filter or not aggregate_filter.whitelist_patterns:
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


@beartype
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


@beartype
def binary_coverage(ctx: TaskContext, test: Path) -> None:
    dir = test.parent
    tools = get_llvm_root() / "bin"
    # Remove `.profdata` files
    for file in dir.glob("*.profdata"):
        file.unlink()

    assert dir.exists()
    run_command(ctx, test, [], allow_fail=True, cwd=str(dir))


@haxorg_task(dependencies=[build_haxorg])
def run_profdata_coverrage(
    ctx: TaskContext,
    binary: str,
    arg: List[str] = [],
    report_path: Optional[str] = None,
) -> None:
    "Generate profdata coverage information for binary @arg binary"
    tools = get_llvm_root("bin")
    if Path(binary).is_absolute():
        bin_path = Path(binary)

    else:
        bin_path = get_component_build_dir(ctx.config, "haxorg").joinpath(binary)

    for file in bin_path.parent.glob("*.profdata"):
        file.unlink()

    for file in bin_path.parent.rglob("*.gcda"):
        file.unlink()

    dir = get_build_root().joinpath("profile")
    dir.mkdir(parents=True, exist_ok=True)
    current = Path().cwd()

    run_command(ctx, bin_path, args=arg)
    print(bin_path.parent)

    default_profraw = current / "default.profraw"
    result_profdata = dir / "bench.profdata"

    assert default_profraw.exists()

    run_command(ctx, tools / "llvm-profdata", [
        "merge",
        "-output=" + str(result_profdata),
        default_profraw,
    ])

    if report_path:
        report_dir = Path(report_path)

    else:
        report_dir = dir / bin_path.name

    if report_dir.exists():
        rmtree(report_dir)

    report_dir.mkdir(parents=True, exist_ok=True)

    run_command(ctx, tools / "llvm-cov", [
        "show",
        bin_path,
        "-instr-profile=" + str(result_profdata),
        "-format=html",
        "-output-dir=" + str(report_dir),
    ])


@beartype
def xray_coverage(ctx: TaskContext, test: Path) -> None:
    dir = test.parent
    tools = get_llvm_root("bin")

    # Remove existing XRay log and profdata files
    for file in dir.glob(f"xray-log.{test.stem}.*"):
        file.unlink()

    for file in dir.glob("*.profdata"):
        file.unlink()

    log(CAT).info(f"Running XRAY log agregation for directory {dir}")
    run_command(
        ctx,
        test, [],
        env={"XRAY_OPTIONS": "patch_premain=true xray_mode=xray-basic verbosity=1"},
        allow_fail=True,
        capture=True,
        cwd=dir)

    # Find the latest XRay log file
    log_files = sorted(dir.glob(f"xray-log.{test.stem}.*"),
                       key=os.path.getmtime,
                       reverse=True)
    if log_files:
        log(CAT).info(f"Latest XRay log file '{log_files[0]}'")
        logfile = log_files[0]

        # Process log file with llvm-xray and llvm-profdata
        run_command(ctx, tools / "llvm-xray", [
            "convert",
            "--symbolize",
            "--instr_map=" + str(test),
            "--output-format=trace_event",
            "--output=" + str(dir / "trace_events.json"),
            logfile,
        ])

        run_command(ctx, tools / "llvm-xray", [
            "graph",
            "--instr_map=" + str(test),
            "--output=" + str(dir / "trace_events.dot"),
            logfile,
        ])

        run_command(ctx, tools / "llvm-profdata", [
            "merge",
            "-output=" + str(dir / "bench.profdata"),
            dir / "default.profraw",
        ])

        run_command(ctx, tools / "llvm-cov", [
            "show",
            test,
            "-instr-profile=" + str(dir / "bench.profdata"),
            "-format=html",
            "-output-dir=" + str(dir / "coverage_report"),
        ])
    else:
        raise RuntimeError(
            f"No XRay log files found in '{dir}', xray coverage enabled in settings {ctx.config.instrument.xray}"
        )


@haxorg_task(dependencies=[build_haxorg])
def run_org_test_performance() -> None:
    """Generate performance sampling profile for tests"""

    tests = str(get_build_root("haxorg") / "tests_org")
    run = plumbum.local["perf"]

    try:
        run["record", "--call-graph", "dwarf", tests] & plumbum.FG
    except plumbum.ProcessExecutionError:
        pass


@beartype
def get_cxx_coverage_dir() -> Path:
    return get_build_root("coverage_artifacts")


@beartype
def get_cxx_profdata_params_path() -> Path:
    return get_cxx_coverage_dir().joinpath("profile-collect.json")


HELP_profdata_file = {
    "profdata-file-whitelist":
        f"List of blacklist regexps to allow in the coverage database.",
    "profdata-file-blacklist":
        f"List of regexps to disallow in the coverage database."
}

HELP_coverage_file = {
    "coverage-file-whitelist": "List of regexps to allow in the final HTML output.",
    "coverage-file-blacklist": "List of regexps to filter out fo the final HTML output",
}


@beartype
def get_cxx_profdata_params(ctx: TaskContext) -> ProfdataParams:
    coverage_dir = get_cxx_coverage_dir()
    stored_summary_collection = coverage_dir.joinpath("test-summary.json")
    summary_data: ProfdataFullProfile = ProfdataFullProfile.model_validate_json(
        stored_summary_collection.read_text())
    filtered_summary = ProfdataFullProfile(
        runs=filter_cookies(summary_data.runs, ctx.config.aggregate_filters))
    filtered_summary_collection = coverage_dir.joinpath("test-summary-filtered.json")
    filtered_summary_collection.write_text(filtered_summary.model_dump_json(indent=2))
    return ProfdataParams(
        coverage=str(filtered_summary_collection),
        coverage_db=str(coverage_dir.joinpath("coverage.sqlite")),
        # perf_trace=str(coverage_dir.joinpath("coverage_merge.pftrace")),
        debug_file=str(coverage_dir.joinpath("coverage_debug.json")),
        file_whitelist=ctx.config.profdata_file_whitelist,
        file_blacklist=ctx.config.profdata_file_blacklist,
        run_group_batch_size=get_threading_count(),
    )


HELP_coverage_mapping_dump = {
    "coverage_mapping_dump":
        "Directory to dump JSON information for every processed coverage mapping object"
}


@beartype
def configure_cxx_merge(
    ctx: TaskContext,
    coverage_mapping_dump: Optional[str] = None,
):
    if ctx.config.instrument.coverage:
        profile_path = get_cxx_profdata_params_path()
        log(CAT).info(
            f"Profile collect options: {profile_path} coverage_mapping_dump = {coverage_mapping_dump}"
        )
        profile_path.parent.mkdir(parents=True, exist_ok=True)
        model = get_cxx_profdata_params()
        if coverage_mapping_dump:
            Path(coverage_mapping_dump).mkdir(exist_ok=True)
            model.coverage_mapping_dump = coverage_mapping_dump

        profile_path.write_text(model.model_dump_json(indent=2))


@haxorg_task(dependencies=[build_haxorg])
def run_cxx_coverage_merge(ctx: TaskContext, coverage_mapping_dump: Optional[str] = None,) -> None:
    configure_cxx_merge(coverage_mapping_dump,)
    coverage_dir = get_cxx_coverage_dir()

    profile_path = get_cxx_profdata_params_path()
    run_command(
        ctx,
        "build/haxorg/profdata_merger",
        [
            profile_path,
        ],
        stderr_debug=ensure_clean_file(
            coverage_dir.joinpath("profdata_merger_stderr.txt")),
        stdout_debug=ensure_clean_file(
            coverage_dir.joinpath("profdata_merger_stdout.txt")),
    )


@haxorg_task()
def cxx_target_coverage(
    pytest_filter: Optional[str] = None,
    coverage_file_whitelist: List[str] = [".*"],
    coverage_file_blacklist: List[str] = [],
    out_dir: str = "/tmp/docs_out_targeted",
    run_tests: bool = True,
    run_merge: bool = True,
    run_docgen: bool = True,
    coverage_mapping_dump: Optional[str] = None,
    allow_test_fail: bool = False,
):
    """
    Run full cycle of the code coverage generation. 
    """

    if run_tests:
        if pytest_filter:
            run_self(
                [
                    run_py_tests,
                    f"--arg=--markfilter",
                    f"--arg={pytest_filter}",
                    "--arg=--markfilter-debug=True",
                ],
                allow_fail=allow_test_fail,
            )

        else:
            run_self(
                [run_py_tests],
                allow_fail=allow_test_fail,
            )

    if run_merge:
        if coverage_mapping_dump:
            run_self([
                run_cxx_coverage_merge,
                f"--coverage-mapping-dump={coverage_mapping_dump}",
            ])
        else:
            run_self([
                run_cxx_coverage_merge,
            ])

    if run_docgen:
        run_self([
            build_custom_docs,
            f"--out-dir={out_dir}",
        ])
