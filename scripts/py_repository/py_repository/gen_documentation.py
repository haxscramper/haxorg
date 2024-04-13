#!/usr/bin/env python

import concurrent.futures
from dataclasses import dataclass
from pathlib import Path

import dominate.tags as tags
import dominate.util as util
import py_repository.gen_documentation_cxx as cxx
import py_repository.gen_documentation_data as docdata
import py_repository.gen_documentation_python as py
import py_repository.gen_documentation_utils as docutils
import py_repository.gen_coverage_python as cov_docpy
from sqlalchemy.orm import Session
import rich_click as click
from beartype import beartype
from beartype.typing import (Dict, Iterable, List, Optional, Tuple, Type, TypeVar, Union)
from dominate import document
from py_scriptutils.files import get_haxorg_repo_root_path
from py_scriptutils.script_logging import log
from py_scriptutils.toml_config_profiler import (BaseModel, apply_options, get_cli_model,
                                                 options_from_model)
from pydantic import BaseModel, Field, SerializeAsAny

T = TypeVar("T")


def dropnan(values: Iterable[Optional[T]]) -> Iterable[T]:
    return (it for it in values if it)


CAT = "docgen"


def lerp_html_color(
    value: float,
    start: Tuple[float, float, float],
    end: Tuple[float, float, float],
) -> str:

    interpolated = tuple(
        int(255 * (r * (1 - value) + g * value))
        for r, g in zip([float(n) for n in start], [float(n) for n in end]))

    return f"#{interpolated[0]:02x}{interpolated[1]:02x}{interpolated[2]:02x}"


@beartype
@dataclass
class SidebarRes():
    tag: tags.ul
    total_entries: int
    documented_entries: int


@beartype
def get_doc_ratio(total: int, documented: int) -> tags.b:
    doc_coverage = tags.b(style="color:{}".format(
        lerp_html_color(
            float(documented) / float(total),
            (1, 0, 0),
            (0, 1, 0),
        ) if total != 0 else "yellow"))

    doc_coverage.add(util.text(f"{documented}/{total}"))

    return doc_coverage


@beartype
def generate_tree_sidebar(directory: docdata.DocDirectory,
                          html_out_path: Path) -> SidebarRes:
    directory_list = tags.ul(cls="sidebar-directory")
    directory_total_entries: int = 0
    directory_documented_entries: int = 0

    for subdir in directory.Subdirs:
        subdir_res = generate_tree_sidebar(subdir, html_out_path)
        link = tags.a(href=docdata.get_html_path(subdir, html_out_path=html_out_path))
        link.add(subdir.RelPath.name)
        link.add(" ")
        link.add(get_doc_ratio(
            subdir_res.total_entries,
            subdir_res.documented_entries,
        ))
        directory_list.add(tags.li(link, subdir_res.tag))

        directory_total_entries += subdir_res.total_entries
        directory_documented_entries += subdir_res.documented_entries

    for code_file in directory.CodeFiles:
        total_entries: int = 0
        documented_entries: int = 0

        def aux_docs(entry: cxx.DocCxxEntry):
            nonlocal total_entries
            nonlocal documented_entries

            total_entries += 1
            if entry.Doc and entry.Doc.Text:
                documented_entries += 1

            match entry:
                case cxx.DocCxxRecord():
                    for sub in entry.Nested:
                        aux_docs(sub)

                case cxx.DocCxxFunction():
                    for arg in entry.Arguments:
                        aux_docs(arg)

                case cxx.DocCxxEnum():
                    for field in entry.Fields:
                        aux_docs(field)

        for entry in code_file.Content:
            aux_docs(entry)

        item = tags.li(_class="sidebar-code")
        link = tags.a(href=docdata.get_html_path(code_file, html_out_path=html_out_path))
        link.add(util.text(code_file.RelPath.name))
        link.add(util.text(" "))
        link.add(get_doc_ratio(total_entries, documented_entries))
        item.add(link)
        directory_list.add(item)

        directory_total_entries += total_entries
        directory_documented_entries += documented_entries

    for text_file in directory.TextFiles:
        directory_list.add(
            tags.li(
                tags.a("Text File",
                       href=docdata.get_html_path(text_file,
                                                  html_out_path=html_out_path)),
                _class="sidebar-text",
            ))

    return SidebarRes(
        tag=directory_list,
        documented_entries=directory_documented_entries,
        total_entries=directory_total_entries,
    )


@beartype
def get_html_page_tabs() -> tags.div:
    div = tags.div(_class="page-tab-row")
    for idx, name in enumerate([
            "code",
            "docs",
    ]):
        button_opts = dict(
            _class="page-tab-link",
            onclick=f"openPage('page-{name}')",
        )

        if idx == 0:
            button = tags.button(**button_opts, id="page-tab-link-default")

        else:
            button = tags.button(**button_opts)

        button.add(util.text(name))
        div.add(button)

    return div


@beartype
def generate_html_for_directory(directory: docdata.DocDirectory,
                                html_out_path: Path) -> None:
    sidebar_res = generate_tree_sidebar(directory, html_out_path=html_out_path)
    sidebar = tags.div(sidebar_res.tag, _class="sidebar-directory-root")
    css_path = get_haxorg_repo_root_path().joinpath(
        "scripts/py_repository/py_repository/gen_documentation.css")

    js_path = get_haxorg_repo_root_path().joinpath(
        "scripts/py_repository/py_repository/gen_documentation.js")

    def aux(directory: docdata.DocDirectory, html_out_path: Path) -> None:
        for subdir in directory.Subdirs:
            aux(subdir, html_out_path)

        for code_file in directory.CodeFiles:
            path = docdata.get_html_path(code_file, html_out_path=html_out_path)
            doc = document(title=str(code_file.RelPath))
            doc.head.add(tags.link(rel="stylesheet", href=css_path))
            doc.head.add(tags.script(src=str(js_path)))

            container = tags.div(_class="container")
            sidebar_div = tags.div()
            sidebar_div.add(
                get_doc_ratio(sidebar_res.total_entries, sidebar_res.documented_entries))
            sidebar_div.add(tags.div(sidebar, _class="sidebar"))
            container.add(sidebar_div)
            main = tags.div(_class="main")
            main.add(get_html_page_tabs())

            match code_file:
                case cxx.DocCodeCxxFile():
                    main.add(cxx.get_html_code_div(code_file))
                    main.add(cxx.get_html_docs_div(code_file))

                case py.DocCodePyFile():
                    main.add(py.get_html_code_div(code_file))
                    main.add(py.get_html_docs_div(code_file))

                case _:
                    raise TypeError(type(code_file))

            container.add(main)
            doc.add(container)

            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(doc.render())
            path.with_suffix(".json").write_text(code_file.model_dump_json(indent=2))

        for text_file in directory.TextFiles:
            path = docdata.get_html_path(text_file, html_out_path=html_out_path)
            doc = document(title=str(text_file.RelPath))
            doc.head.add(tags.link(rel="stylesheet", href=css_path))
            doc.add(tags.div(sidebar, _class="sidebar"))
            main = tags.div(_class="main")
            main.add(tags.pre(text_file.Text))

            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(doc.render())

    aux(directory, html_out_path)


class DocGenerationOptions(BaseModel, extra="forbid"):
    html_out_path: Path = Field(description="Root directory to output generated HTML to")

    json_out_path: Optional[Path] = Field(
        description="Path to write JSON data for the documentation model",
        default=None,
    )

    root_path: Path = Field(description="Root directory for the whole code")

    src_file: List[Path] = Field(
        description="List of standalone files to be added to the documentation",
        default_factory=list,
    )

    src_path: List[Path] = Field(
        description="List of directories for code processing",
        default_factory=list,
    )

    tests_path: Optional[Path] = Field(
        description="Root directory for the tests",
        default=None,
    )

    coverage_path: Optional[Path] = Field(
        description=".coverage file generated by the coverage.py",
        default=None,
    )


def cli_options(f):
    return apply_options(f, options_from_model(DocGenerationOptions))


@beartype
def parse_code_file(
    file: Path,
    conf: DocGenerationOptions,
    rel_path_to_code_file: Dict[Path, cxx.DocCodeCxxFile],
    py_coverage_session: Optional[Session],
) -> docdata.DocCodeFile:
    try:
        if file.suffix == ".hpp":
            code_file = cxx.convert_cxx_tree(
                cxx.parse_cxx(file),
                RootPath=conf.root_path,
                AbsPath=file.absolute(),
            )

        else:
            tree = py.parse_py(file)
            code_file = py.convert_py_tree(
                tree,
                RootPath=conf.root_path,
                AbsPath=file.absolute(),
                py_coverage_session=py_coverage_session,
            )

    except Exception as e:
        e.add_note(str(file))
        raise e from None

    rel_path_to_code_file[code_file.RelPath] = code_file
    return code_file


@beartype
def parse_text_file(file: Path) -> docdata.DocTextFile:
    return docdata.DocTextFile(Text=file.read_text())


@beartype
def parse_dir(
    dir: Path,
    conf: DocGenerationOptions,
    rel_path_to_code_file: Dict[Path, cxx.DocCodeCxxFile],
    py_coverage_session: Optional[Session],
) -> docdata.DocDirectory:
    result = docdata.DocDirectory(RelPath=dir.relative_to(conf.root_path))
    for file in sorted(dir.glob("*")):
        if file.name in [
                "base_lexer_gen.cpp",
                "__init__.py",
                "__pycache__",
        ] or file.name.startswith("."):
            continue

        match file.suffix:
            case ".hpp" | ".py":
                result.CodeFiles.append(
                    parse_code_file(
                        file,
                        conf,
                        rel_path_to_code_file=rel_path_to_code_file,
                        py_coverage_session=py_coverage_session,
                    ))

            case "*.org":
                result.TextFiles.append(parse_text_file(file))

            case _ if file.is_dir():
                result.Subdirs.append(
                    parse_dir(
                        file,
                        conf,
                        rel_path_to_code_file=rel_path_to_code_file,
                        py_coverage_session=py_coverage_session,
                    ))

    return result


@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@cli_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs) -> None:
    conf = get_cli_model(ctx, DocGenerationOptions, kwargs=kwargs, config=config)
    rel_path_to_code_file: Dict[Path, cxx.DocCodeCxxFile] = {}

    py_coverage_session: Optional[Session] = None
    if conf.coverage_path:
        py_coverage_session = cov_docpy.open_coverage(conf.coverage_path)

    full_root = docdata.DocDirectory(RelPath=conf.root_path.relative_to(conf.root_path))
    for subdir in conf.src_path:
        full_root.Subdirs.append(
            parse_dir(
                subdir,
                conf,
                rel_path_to_code_file=rel_path_to_code_file,
                py_coverage_session=py_coverage_session,
            ))

    if conf.json_out_path:
        conf.json_out_path.write_text(full_root.model_dump_json(indent=2))

    generate_html_for_directory(full_root, html_out_path=conf.html_out_path)


if __name__ == "__main__":
    cli()
