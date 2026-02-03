from pathlib import Path

from beartype.typing import List
from beartype.typing import Optional
from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.common import check_path_exists
from py_repository.repo_tasks.common import get_build_root
from py_repository.repo_tasks.common import get_list_cli_pass
from py_repository.repo_tasks.common import get_script_root
from py_repository.repo_tasks.haxorg_coverage import get_cxx_profdata_params
from py_repository.repo_tasks.workflow_utils import haxorg_task
from py_repository.repo_tasks.workflow_utils import TaskContext
from py_scriptutils.script_logging import log

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
    from py_repository.repo_docgen.gen_documentation import DocGenerationOptions
    from py_repository.repo_docgen.gen_documentation import generate_documentation

    assert check_path_exists(ctx, Path(
        get_cxx_profdata_params(ctx).output)), get_cxx_profdata_params(ctx).output

    generate_documentation(conf=DocGenerationOptions(
        html_out_path=out_dir_path,
        root_path=get_script_root(ctx),
        src_path=[
            get_script_root(ctx, "src"),
            get_script_root(ctx, "scripts"),
        ],
        py_coverage_path=get_script_root(ctx, ".coverage"),
        test_path=[get_script_root(ctx, "tests")],
        profile_out_path=out_dir_path.joinpath("profile.json"),
        coverage_file_whitelist=ctx.config.coverage_conf.coverage_html_whitelist,
        coverage_file_blacklist=ctx.config.coverage_conf.coverage_html_blacklist,
        cxx_coverage_path=get_cxx_profdata_params(ctx).output,
    ))
