from pathlib import Path

from beartype.typing import List, Optional
from py_repository.repo_tasks.command_execution import (
    get_uv_develop_env_flags,
    get_uv_develop_sync_flags,
    run_command,
)
from py_repository.repo_tasks.common import (
    check_path_exists,
    get_build_root,
    get_list_cli_pass,
    get_script_root,
)
from py_repository.repo_tasks.haxorg_coverage import get_cxx_profdata_params
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
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
def docs_python(ctx: TaskContext) -> None:
    "Build documentation for the Python workspace using Sphinx"
    from pathlib import Path
    import tomllib

    root = get_script_root(ctx)
    template_dir = get_script_root(ctx) / "docs/templates"
    docs_dir = get_build_root(ctx) / "docs" / "python"
    source_dir = docs_dir / "source"
    build_dir = docs_dir / "_build"

    docs_dir.mkdir(parents=True, exist_ok=True)
    source_dir.mkdir(exist_ok=True)

    pyproject = root / "pyproject.toml"
    if not pyproject.exists():
        log(CAT).error("pyproject.toml not found")
        return

    with open(pyproject, "rb") as f:
        config = tomllib.load(f)

    members = config.get("tool", {}).get("uv", {}).get("workspace", {}).get("members", [])
    if not members:
        log(CAT).error("No workspace members found")
        return

    packages = []
    for pattern in members:
        for path in root.glob(pattern):
            if not path.is_dir():
                continue
            pkg_toml = path / "pyproject.toml"
            if not pkg_toml.exists():
                continue
            with open(pkg_toml, "rb") as f:
                pkg_config = tomllib.load(f)
            name = pkg_config.get("project", {}).get("name")
            if name:
                pkg_src = path / "src" if (path / "src").exists() else path
                packages.append((name.replace("-", "_"), str(pkg_src)))

    if not packages:
        log(CAT).warning("No packages found to document")
        return

    # Create minimal Sphinx configuration if missing
    conf_py = source_dir / "conf.py"
    conf_content = "import os\nimport sys\n"
    for _, pkg_path in packages:
        conf_content += f"sys.path.insert(0, os.path.abspath({repr(pkg_path)}))\n"
    conf_content += """
project = "Python API"
extensions = ["sphinx.ext.autodoc", "sphinx.ext.napoleon", "sphinx.ext.viewcode", "sphinx.ext.autosummary",]
html_theme = "furo"
autodoc_mock_imports = ["lldb", "py_textlayout_cpp"]
autosummary_generate = True

autodoc_default_options = {
    "members": True,
    "show-inheritance": True,
    "member-order": "bysource",
    "autosummary": True,
}

autodoc_typehints = "description"
"""
    conf_py.write_text(conf_content)

    # Create index.rst if missing
    index_rst = source_dir / "index.rst"
    toc = "\n".join(f"   api/{name}/index" for name, _ in packages)
    index_rst.write_text(f"""\
UV workspace packages documentation
===================================

.. toctree::
    :maxdepth: 4

{toc}
""")

    api_root = source_dir / "api"

    for pkg_name, pkg_path in packages:
        out_dir = api_root / pkg_name

        run_command(
            ctx,
            "uv",
            [
                "run",
                *get_uv_develop_sync_flags(ctx),
                *get_uv_develop_env_flags(ctx),
                "--with",
                "sphinx",
                "--with",
                "furo",
                "sphinx-apidoc",
                "-f",
                "-e",
                "-M",
                "-d",
                "4",
                "--templatedir",
                str(template_dir),
                "--tocfile",
                "index",
                "-o",
                str(out_dir),
                pkg_path,
            ],
            stdout_debug=get_build_root(ctx).joinpath(f"sphinx_apidoc_{pkg_name}.log"),
            stderr_debug=get_build_root(ctx).joinpath(f"sphinx_apidoc_{pkg_name}.err"),
        )

    # Build HTML documentation
    run_command(
        ctx,
        "uv",
        [
            "run",
            *get_uv_develop_sync_flags(ctx),
            *get_uv_develop_env_flags(ctx),
            "--with",
            "sphinx",
            "--with",
            "furo",
            "sphinx-build",
            "-b",
            "html",
            str(source_dir),
            str(build_dir / "html"),
        ],
        stdout_debug=get_build_root(ctx).joinpath("sphinx_build_stdout.log"),
        stderr_debug=get_build_root(ctx).joinpath("sphinx_build_stderr.log"),
    )

    log(CAT).info(f"Completed Python docs build at {build_dir / 'html'}")


@haxorg_task()
def build_custom_docs(ctx: TaskContext, out_dir: Optional[str] = None) -> None:
    """Build documentation for the project using custom script"""
    if out_dir:
        out_dir_path = Path(out_dir)
    else:
        out_dir_path = Path(ctx.config.custom_docs_conf.out_dir)
    out_dir_path.mkdir(parents=True, exist_ok=True)
    from py_repository.repo_docgen.gen_documentation import (
        DocGenerationOptions,
        generate_documentation,
    )

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
