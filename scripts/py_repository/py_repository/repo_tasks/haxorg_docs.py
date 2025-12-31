from beartype.typing import Optional, List

from py_repository.repo_tasks.haxorg_coverage import get_cxx_profdata_params
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.common import get_build_root, get_list_cli_pass, get_script_root
from py_scriptutils.script_logging import log
from pathlib import Path

CAT = __name__


@haxorg_task()
def docs_doxygen(ctx: TaskContext) -> None:
    "Build docunentation for the project using doxygen"
    out_dir = get_script_root(ctx, "/tmp/doxygen")
    # if out_dir.exists():
    #     shutil.rmtree(out_dir)

    out_dir.mkdir(parents=True, exist_ok=True)

    run_command(
        ctx,
        "doxygen",
        [str(get_script_root(ctx, "docs/Doxyfile"))],
        stdout_debug=get_build_root(ctx).joinpath("doxygen_stdout.log"),
        stderr_debug=get_build_root(ctx).joinpath("doxygen_stderr.log"),
        # run_mode="bg",
    )
    log(CAT).info("Completed CXX docs build")


@haxorg_task()
def build_custom_docs(ctx: TaskContext, out_dir: Optional[str] = None) -> None:
    """Build documentation for the project using custom script"""
    if out_dir:
        out_dir_path = Path(out_dir)
    else:
        out_dir_path = Path(ctx.config.custom_docs_conf.out_dir)
    out_dir_path.mkdir(parents=True, exist_ok=True)

    if ctx.config.instrument.coverage:
        args: List[str] = [
            "run",
            str(
                get_script_root(
                    ctx, "scripts/py_repository/py_repository/gen_documentation.py")),
            f"--html_out_path={out_dir_path}",
            f"--root_path={get_script_root(ctx)}",
            f"--src_path={get_script_root(ctx, 'src')}",
            f"--src_path={get_script_root(ctx, 'scripts')}",
            f"--py_coverage_path={get_script_root(ctx, '.coverage')}",
            f"--test_path={get_script_root(ctx, 'tests')}",
            f"--profile_out_path={out_dir_path.joinpath('profile.json')}",
        ]
        args.extend(
            get_list_cli_pass("coverage_file_whitelist",
                              ctx.config.custom_docs_conf.coverage_file_whitelist))
        args.extend(
            get_list_cli_pass("coverage_file_blacklist",
                              ctx.config.custom_docs_conf.coverage_file_blacklist))

        prof_params = get_cxx_profdata_params(ctx)
        if Path(prof_params.coverage_db).exists():
            args.append(f"--cxx_coverage_path={prof_params.coverage_db}")
            log(CAT).info(f"Using coveage database from {prof_params.coverage_db}")
        else:
            log(CAT).info(
                f"No coverage database generated, {prof_params.coverage_db} does not exist"
            )

        run_command(ctx, "poetry", args)
