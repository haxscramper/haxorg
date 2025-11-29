from beartype.typing import List

from py_repository.repo_tasks.config import get_config
from py_repository.repo_tasks.haxorg_coverage import get_cxx_profdata_params
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.common import get_build_root, get_list_cli_pass, get_script_root
from py_scriptutils.script_logging import log
from pathlib import Path

CAT = __name__


@haxorg_task()
def docs_doxygen():
    "Build docunentation for the project using doxygen"
    out_dir = get_script_root("/tmp/doxygen")
    # if out_dir.exists():
    #     shutil.rmtree(out_dir)

    out_dir.mkdir(parents=True, exist_ok=True)

    run_command(
        "doxygen",
        [str(get_script_root("docs/Doxyfile"))],
        stdout_debug=get_build_root().joinpath("doxygen_stdout.log"),
        stderr_debug=get_build_root().joinpath("doxygen_stderr.log"),
        # run_mode="bg",
    )
    log(CAT).info("Completed CXX docs build")


@haxorg_task()
def build_custom_docs(ctx: TaskContext):
    """Build documentation for the project using custom script"""
    conf = get_config()
    out_dir = Path(conf.custom_docs_conf.out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)

    if conf.instrument.coverage:
        args = [
            "run",
            get_script_root("scripts/py_repository/py_repository/gen_documentation.py"),
            f"--html_out_path={out_dir}",
            f"--root_path={get_script_root()}",
            f"--src_path={get_script_root('src')}",
            f"--src_path={get_script_root('scripts')}",
            f"--py_coverage_path={get_script_root('.coverage')}",
            f"--test_path={get_script_root('tests')}",
            f"--profile_out_path={out_dir.joinpath('profile.json')}",
            *get_list_cli_pass("coverage_file_whitelist", conf.custom_docs_conf.coverage_file_whitelist),
            *get_list_cli_pass("coverage_file_blacklist", conf.custom_docs_conf.coverage_file_blacklist),
        ]

        prof_params = get_cxx_profdata_params()
        if Path(prof_params.coverage_db).exists():
            args.append(f"--cxx_coverage_path={prof_params.coverage_db}")
            log(CAT).info(f"Using coveage database from {prof_params.coverage_db}")
        else:
            log(CAT).info(
                f"No coverage database generated, {prof_params.coverage_db} does not exist")

        run_command("poetry", args)
