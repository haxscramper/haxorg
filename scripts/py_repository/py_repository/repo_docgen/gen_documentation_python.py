from dataclasses import dataclass
from pathlib import Path

from beartype import beartype
from beartype.typing import Any, Dict, List, Optional, Tuple
from py_repository.repo_tasks.command_execution import (
    get_uv_develop_env_flags,
    get_uv_develop_sync_flags,
    run_command,
)
from py_repository.repo_tasks.common import (
    ensure_clean_dir,
    get_build_root,
    get_script_root,
)
from py_repository.repo_tasks.workflow_utils import TaskContext
from py_scriptutils.script_logging import log
from pydantic import BaseModel, ConfigDict, Field

CAT = __name__


class SphinxJsonPage(BaseModel, extra="forbid"):
    """Sphinx JSON builder output schema (`.fjson` files)"""

    body: str = Field(description="HTML body content of the page")

    title: Optional[str] = Field(default=None,
                                 description="HTML-formatted page title with markup")

    title_string: Optional[str] = Field(
        default=None,
        description="Plain text version of the page title without HTML markup")

    toc: Optional[str] = Field(default=None,
                               description="HTML table of contents for the current page")

    current_page_name: Optional[str] = Field(
        default=None, description="Name or identifier of the current page")

    next: Optional[Dict[str, str]] = Field(
        default=None,
        description=
        "Dictionary containing 'link' and 'title' keys for the next page in sequence")

    prev: Optional[Dict[str, str]] = Field(
        default=None,
        description=
        "Dictionary containing 'link' and 'title' keys for the previous page in sequence")

    parents: Optional[List[Dict[str, str]]] = Field(
        default=None,
        description=
        "List of parent pages in the documentation hierarchy, each with 'link' and 'title' keys"
    )

    meta: Optional[Dict[str, Any]] = Field(
        default=None,
        description="Metadata dictionary containing arbitrary page-level metadata")

    sourcename: Optional[str] = Field(
        default=None, description="Original source file name (e.g., 'index.rst')")

    pagename: Optional[str] = Field(
        default=None,
        description="Page name/path without extension, used for referencing")

    display_toc: Optional[bool] = Field(
        default=None,
        description="Flag indicating whether to display the table of contents")

    toctree: Optional[List[str]] = Field(
        default=None,
        description="List of page names/paths included in this page's toctree directive")


@beartype
@dataclass
class _DocsPythonSetup():
    "Sphinx documentation setup directories"
    root: Path
    "Root path for the source code to index"
    template_dir: Path
    "Path to jinja template directory"
    docs_dir: Path
    "Root directory for auto-generated `.rst` and HTML files"
    source_dir: Path
    "Path to temporary directory to write `.rst` files to"
    build_dir: Path
    "Final directory to put the HTML files to"
    packages: List[Tuple[str, str]]
    "List of packages found in the repository"


def _docs_python_setup(ctx: TaskContext) -> _DocsPythonSetup:
    """Common setup: create directories, conf.py, index.rst and discover packages"""
    import tomllib

    root = get_script_root(ctx)
    template_dir = get_script_root(ctx) / "docs/templates"
    docs_dir = get_build_root(ctx) / "docs" / "python"
    source_dir = docs_dir / "source"
    build_dir = docs_dir / "_build"

    ensure_clean_dir(ctx, docs_dir)
    ensure_clean_dir(ctx, source_dir)

    pyproject = root / "pyproject.toml"
    if not pyproject.exists():
        log(CAT).error("pyproject.toml not found")
        raise FileNotFoundError("pyproject.toml not found")

    config = tomllib.loads(pyproject.read_text())

    members = config.get("tool", {}).get("uv", {}).get("workspace", {}).get("members", [])
    if not members:
        log(CAT).error("No workspace members found")
        raise ValueError("No workspace members found")

    packages = []
    for pattern in members:
        for path in root.glob(pattern):
            if not path.is_dir():
                continue
            pkg_toml = path / "pyproject.toml"
            if not pkg_toml.exists():
                continue
            pkg_config = tomllib.loads(pkg_toml.read_text())
            name = pkg_config.get("project", {}).get("name")
            if name:
                pkg_src = path / "src" if (path / "src").exists() else path
                packages.append((name.replace("-", "_"), str(pkg_src)))

    if not packages:
        log(CAT).warning("No packages found to document")
        raise ValueError("No packages found to document")

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

    index_rst = source_dir / "index.rst"
    toc = "\n".join(f"   api/{name}/index" for name, _ in packages)
    index_rst.write_text(f"""\
UV workspace packages documentation
===================================

.. toctree::
    :maxdepth: 4

{toc}
""")

    return _DocsPythonSetup(
        root=root,
        template_dir=template_dir,
        docs_dir=docs_dir,
        source_dir=source_dir,
        build_dir=build_dir,
        packages=packages,
    )


def _docs_python_generate_api(ctx: TaskContext, setup: _DocsPythonSetup) -> None:
    """Generate API documentation using sphinx-apidoc"""
    api_root = setup.source_dir / "api"

    for pkg_name, pkg_path in setup.packages:
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
                str(setup.template_dir),
                "--tocfile",
                "index",
                "-o",
                str(out_dir),
                pkg_path,
            ],
            stdout_debug=get_build_root(ctx).joinpath(f"sphinx_apidoc_{pkg_name}.log"),
            stderr_debug=get_build_root(ctx).joinpath(f"sphinx_apidoc_{pkg_name}.err"),
        )


def _docs_python_build_html(ctx: TaskContext, source_dir: Path, build_dir: Path) -> Path:
    """Build HTML documentation"""
    html_dir = build_dir / "html"

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
            str(html_dir),
        ],
        stdout_debug=get_build_root(ctx).joinpath("sphinx_build_stdout.log"),
        stderr_debug=get_build_root(ctx).joinpath("sphinx_build_stderr.log"),
    )

    log(CAT).info(f"Completed Python docs build at {html_dir}")
    return html_dir


def _docs_python_build_json(ctx: TaskContext, source_dir: Path,
                            build_dir: Path) -> List[Path]:
    """Build JSON documentation and return list of generated JSON file paths"""
    json_dir = build_dir / "json"
    json_dir.mkdir(parents=True, exist_ok=True)

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
            "json",
            str(source_dir),
            str(json_dir),
        ],
        stdout_debug=get_build_root(ctx).joinpath("sphinx_json_build_stdout.log"),
        stderr_debug=get_build_root(ctx).joinpath("sphinx_json_build_stderr.log"),
    )

    json_files = sorted(json_dir.rglob("*.fjson"))

    if not json_files:
        log(CAT).warning(f"No .fjson files found in {json_dir}")
    else:
        log(CAT).info(
            f"Generated {len(json_files)} JSON documentation files at {json_dir}")

    return json_files


def gen_docs(ctx: TaskContext, build_html: bool = True, build_json: bool = False) -> dict:
    "Build documentation for the Python workspace using Sphinx"
    import json

    result = {}
    setup = _docs_python_setup(ctx)
    _docs_python_generate_api(ctx, setup)

    if build_html:
        result["html_path"] = _docs_python_build_html(ctx, setup.source_dir,
                                                      setup.build_dir)

    if build_json:
        json_paths = _docs_python_build_json(ctx, setup.source_dir, setup.build_dir)
        result["json_paths"] = json_paths

        if json_paths:
            try:
                first_file = json_paths[0]
                data = json.loads(first_file.read_text())
                SphinxJsonPage.model_validate(data)
                log(CAT).debug(f"JSON schema validation passed for {first_file.name}")
            except Exception as e:
                log(CAT).warning(f"JSON schema validation failed: {e}")

    return result
