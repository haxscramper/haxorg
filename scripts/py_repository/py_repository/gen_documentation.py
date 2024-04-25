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
import py_repository.gen_coverage_cxx as cov_docxx
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
import more_itertools

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

        if not code_file.IsTest:
            for entry in code_file.Content:
                aux_docs(entry)

        item = tags.li(_class="sidebar-code")
        link = tags.a(href=docdata.get_html_path(code_file, html_out_path=html_out_path))
        link.add(util.text(code_file.RelPath.name))
        if not code_file.IsTest:
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
def get_html_page_tabs(tab_order: List[str]) -> tags.div:
    div = tags.div(_class="page-tab-row")
    for idx, name in enumerate(tab_order):
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


css_path = get_haxorg_repo_root_path().joinpath(
    "scripts/py_repository/py_repository/gen_documentation.css")

js_path = get_haxorg_repo_root_path().joinpath(
    "scripts/py_repository/py_repository/gen_documentation.js")


@beartype
def generate_html_for_directory(directory: docdata.DocDirectory,
                                html_out_path: Path) -> None:
    sidebar_res = generate_tree_sidebar(directory, html_out_path=html_out_path)
    sidebar = tags.div(sidebar_res.tag, _class="sidebar-directory-root")

    def aux(directory: docdata.DocDirectory, html_out_path: Path) -> None:
        for subdir in directory.Subdirs:
            aux(subdir, html_out_path)

        for code_file in directory.CodeFiles:
            path = docdata.get_html_path(code_file, html_out_path=html_out_path)
            # log(CAT).info(f"HTML for Code {code_file.RelPath} -> {path}")

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

            if code_file.IsTest:
                main.add(get_html_page_tabs(["code"]))
            else:
                main.add(get_html_page_tabs(["docs", "code"]))

            match code_file:
                case cxx.DocCodeCxxFile():
                    main.add(cxx.get_html_code_div(code_file))
                    if not code_file.IsTest:
                        main.add(cxx.get_html_docs_div(code_file))

                case py.DocCodePyFile():
                    main.add(py.get_html_code_div(code_file))
                    if not code_file.IsTest:
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


@beartype
def generate_html_for_tests(full_root: docdata.DocDirectory, html_out_path: Path):
    test_entries: List[Tuple[py.DocPyFunction, cov_docpy.TestName]] = []
    flat_files: List[py.DocCodePyFile] = []

    def find_test_entries(dir: docdata.DocDirectory):
        for file in dir.CodeFiles:
            if file.IsTest:
                for entry in file.Content:
                    if isinstance(entry, (cxx.DocCxxFunction, py.DocPyFunction)):
                        if entry.Name.startswith("test_"):
                            test_name: str = entry.Name[5:]

                            test_entries.append((
                                entry,
                                cov_docpy.TestName(
                                    rel_path=str(file.RelPath),
                                    test_name=test_name,
                                    subname="run",
                                ),
                            ))

            else:
                flat_files.append(file)

        for subdir in dir.Subdirs:
            find_test_entries(subdir)

    find_test_entries(full_root)

    for test_entry, test_name in test_entries:
        out_dir = html_out_path.joinpath(test_name.rel_path).with_suffix(".d")
        out_dir.mkdir(parents=True, exist_ok=True)
        out_file = out_dir.joinpath(test_name.test_name).with_suffix(".html")
        doc = document()
        covered_blocks: List[tags.div] = []
        for code_file in flat_files:
            if isinstance(code_file, py.DocCodePyFile):
                covered_lines: List[py.DocCodePyLine] = []
                for line in code_file.Lines:
                    if line.TestCoverage and any(it.test_name == test_name.test_name and
                                                 it.rel_path == test_name.rel_path
                                                 for it in line.TestCoverage.CoveredBy):
                        covered_lines.append(line)

                if covered_lines:
                    block = tags.div(_class="test-cover")
                    block.add(tags.span(util.text(str(code_file.RelPath)),
                                        _class="title"))

                    for adj_lines in more_itertools.split_when(
                            iterable=covered_lines,
                            pred=lambda lhs, rhs: lhs.Index + 1 != rhs.Index,
                    ):
                        adj_group = tags.div(_class="adjacent-lines")
                        for line in adj_lines:
                            full_span = tags.span(_class="code-line")
                            num_span, line_span = docdata.get_code_line_span(
                                line=line,
                                highilght_lexer=py.PythonLexer(),
                                decl_locations={},
                                get_docs_fragment=lambda it: "",
                            )
                            full_span.add(num_span)
                            full_span.add(line_span)
                            adj_group.add(full_span)

                        block.add(adj_group)

                    covered_blocks.append(block)

        if covered_blocks:
            log(CAT).info(f"{out_file}")
            doc.add(tags.h1(util.text(test_name.test_name)))
            doc.add(covered_blocks)
            doc.head.add(tags.link(rel="stylesheet", href=css_path))
            doc.head.add(tags.script(src=str(js_path)))
            out_file.write_text(doc.render())


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

    test_path: List[Path] = Field(
        description="Root directory for the tests",
        default_factory=list,
    )

    py_coverage_path: Optional[Path] = Field(
        description=".coverage file generated by the coverage.py",
        default=None,
    )

    cxx_coverage_path: Optional[Path] = Field(
        description="Merged coverage data sqlite",
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
    cxx_coverage_session: Optional[Session],
    is_test: bool,
) -> docdata.DocCodeFile:
    try:
        if file.suffix in [".hpp", ".cpp"]:
            code_file = cxx.convert_cxx_tree(
                cxx.parse_cxx(file),
                RootPath=conf.root_path,
                AbsPath=file.absolute(),
                coverage_session=cxx_coverage_session,
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
    code_file.IsTest = is_test
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
    cxx_coverage_session: Optional[Session],
    is_test: bool,
) -> docdata.DocDirectory:
    result = docdata.DocDirectory(RelPath=dir.relative_to(conf.root_path))
    for file in sorted(dir.glob("*")):
        if file.name in [
                "base_lexer_gen.cpp",
                "profdata_merger.cpp",
                "pyhaxorg.cpp",
                "__init__.py",
                "__pycache__",
        ] or file.name.startswith("."):
            continue

        match file.suffix:
            case ".hpp" | ".py" | ".cpp":
                result.CodeFiles.append(
                    parse_code_file(
                        file,
                        conf,
                        rel_path_to_code_file=rel_path_to_code_file,
                        py_coverage_session=py_coverage_session,
                        cxx_coverage_session=cxx_coverage_session,
                        is_test=is_test or file.suffix == ".cpp", # FIXME replace `is_test` with `is_impl`
                    ))

            case "*.org":
                result.TextFiles.append(parse_text_file(file))

            case _ if file.is_dir():
                subdir = parse_dir(
                    file,
                    conf,
                    rel_path_to_code_file=rel_path_to_code_file,
                    py_coverage_session=py_coverage_session,
                    cxx_coverage_session=cxx_coverage_session,
                    is_test=is_test,
                )

                if subdir.CodeFiles or subdir.TextFiles or subdir.Subdirs:
                    result.Subdirs.append(subdir)

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
    if conf.py_coverage_path:
        py_coverage_session = cov_docpy.open_coverage(conf.py_coverage_path)

    cxx_coverage_session: Optional[Session] = None
    if conf.cxx_coverage_path:
        cxx_coverage_session = cov_docxx.open_coverage(conf.cxx_coverage_path)

    full_root = docdata.DocDirectory(RelPath=conf.root_path.relative_to(conf.root_path))
    for subdir in conf.test_path:
        full_root.Subdirs.append(
            parse_dir(
                subdir,
                conf,
                rel_path_to_code_file=rel_path_to_code_file,
                py_coverage_session=None,
                cxx_coverage_session=None,
                is_test=True,
            ))

    for subdir in conf.src_path:
        full_root.Subdirs.append(
            parse_dir(
                subdir,
                conf,
                rel_path_to_code_file=rel_path_to_code_file,
                py_coverage_session=py_coverage_session,
                cxx_coverage_session=cxx_coverage_session,
                is_test=False,
            ))

    if conf.json_out_path:
        conf.json_out_path.write_text(full_root.model_dump_json(indent=2))

    generate_html_for_directory(full_root, html_out_path=conf.html_out_path)
    generate_html_for_tests(
        full_root=full_root,
        html_out_path=conf.html_out_path.joinpath("test_coverage"),
    )


if __name__ == "__main__":
    cli()
