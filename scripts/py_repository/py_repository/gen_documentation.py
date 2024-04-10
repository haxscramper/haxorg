#!/usr/bin/env python

from py_scriptutils.files import get_haxorg_repo_root_path
from pathlib import Path
from beartype import beartype
from beartype.typing import List, Dict, Optional, Union, Iterable, TypeVar, Tuple
from py_scriptutils.script_logging import log
from dataclasses import dataclass
from pydantic import BaseModel, Field, SerializeAsAny
import dominate.tags as tags
from dominate import document
import dominate.util as util
from py_scriptutils.toml_config_profiler import options_from_model, BaseModel, apply_options, get_cli_model
import rich_click as click
import py_repository.run_coverage as coverage
import concurrent.futures
import py_repository.gen_documentation_cxx as cxx
import py_repository.gen_documentation_python as py
from beartype.typing import Type

T = TypeVar("T")


def dropnan(values: Iterable[Optional[T]]) -> Iterable[T]:
    return (it for it in values if it)


CAT = "docgen"


class DocTextFile(BaseModel, extra="forbid"):
    RelPath: Path
    Text: str = ""


class DocDirectory(BaseModel, extra="forbid"):
    RelPath: Path
    CodeFiles: List[Union[
        cxx.DocCodeCxxFile,
    ]] = Field(default_factory=list)
    TextFiles: List[DocTextFile] = Field(default_factory=list)
    Subdirs: List["DocDirectory"] = Field(default_factory=list)


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
def get_html_path(entry: Union[DocDirectory, cxx.DocCodeCxxFile, DocTextFile],
                  html_out_path: Path) -> Path:
    match entry:
        case DocDirectory():
            return html_out_path.joinpath(entry.RelPath)

        case cxx.DocCodeCxxFile() | DocTextFile():
            return html_out_path.joinpath(entry.RelPath).with_suffix(".html")


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
def generate_tree_sidebar(directory: DocDirectory, html_out_path: Path) -> SidebarRes:
    directory_list = tags.ul(cls="sidebar-directory")
    directory_total_entries: int = 0
    directory_documented_entries: int = 0

    for subdir in directory.Subdirs:
        subdir_res = generate_tree_sidebar(subdir, html_out_path)
        link = tags.a(href=get_html_path(subdir, html_out_path=html_out_path))
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
        link = tags.a(href=get_html_path(code_file, html_out_path=html_out_path))
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
                       href=get_html_path(text_file, html_out_path=html_out_path)),
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
            "docs",
            "code",
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
def generate_html_for_directory(directory: "DocDirectory", html_out_path: Path) -> None:
    sidebar_res = generate_tree_sidebar(directory, html_out_path=html_out_path)
    sidebar = tags.div(sidebar_res.tag, _class="sidebar-directory-root")
    css_path = get_haxorg_repo_root_path().joinpath(
        "scripts/py_repository/py_repository/gen_documentation.css")

    js_path = get_haxorg_repo_root_path().joinpath(
        "scripts/py_repository/py_repository/gen_documentation.js")

    def aux(directory: DocDirectory, html_out_path: Path) -> None:
        for subdir in directory.Subdirs:
            aux(subdir, html_out_path)

        for code_file in directory.CodeFiles:
            path = get_html_path(code_file, html_out_path=html_out_path)
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
            main.add(cxx.get_html_code_div(code_file))
            main.add(cxx.get_html_docs_div(code_file))
            container.add(main)
            doc.add(container)

            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(doc.render())

        for text_file in directory.TextFiles:
            path = get_html_path(text_file, html_out_path=html_out_path)
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
    src_path: Path = Field(description="Root directory for input source code")
    tests_path: Optional[Path] = Field(
        description="Root directory for the tests",
        default=None,
    )


def cli_options(f):
    return apply_options(f, options_from_model(DocGenerationOptions))


@beartype
def get_coverage_data_single(
        file) -> Tuple[coverage.ProfdataCookie, coverage.TestRunCoverage]:
    cookie = coverage.ProfdataCookie.model_validate_json(file.read_text())
    model = coverage.get_profile_model(cookie)
    return (cookie, model)


@beartype
def get_full_coverage_data_all(
        files: Iterable[Path],
        max_workers=5) -> List[Tuple[
            coverage.ProfdataCookie,
            coverage.TestRunCoverage,
        ]]:

    results = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=max_workers) as executor:
        future_to_file = {
            executor.submit(get_coverage_data_single, file): file for file in files
        }

        for future in concurrent.futures.as_completed(future_to_file):
            result = future.result()
            results.append(result)

    return results


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

    @beartype
    def aux_dir(dir: Path) -> DocDirectory:
        result = DocDirectory(RelPath=dir.relative_to(conf.src_path))
        for file in sorted(dir.glob("*")):
            if file.name == "base_lexer_gen.cpp":
                continue

            match file.suffix:
                case ".hpp" | ".py":
                    try:
                        if file.suffix == ".hpp":
                            code_file = cxx.convert_cxx_tree(
                                cxx.parse_cxx(file),
                                RootPath=conf.src_path,
                                AbsPath=file.absolute(),
                            )

                        else: 
                            code_file = py.convert_py_tree(
                                py.parse_py(file),
                                RootPath=conf.src_path,
                                AbsPath=file.absolute(),
                            )

                    except Exception as e:
                        e.add_note(str(file))
                        raise e from None

                    rel_path_to_code_file[code_file.RelPath] = code_file
                    result.CodeFiles.append(code_file)

                case "*.org":
                    result.TextFiles.append(DocTextFile(Text=file.read_text()))

                case _ if file.is_dir():
                    result.Subdirs.append(aux_dir(file))

        return result

    result = aux_dir(conf.src_path)

    if False:
        coverage_meta = get_full_coverage_data_all([
            file for file in coverage.get_profile_root().glob("*" +
                                                              coverage.COOKIE_SUFFIX)
            if "AllNodeCoverage" not in str(file)
        ])

        for cookie, model in coverage_meta:
            for entry in model.coverage.data:
                for file in entry.files:
                    try:
                        rel_covered = Path(file.filename).relative_to(conf.src_path)
                    except ValueError:
                        continue

                    doc_file = rel_path_to_code_file.get(rel_covered, None)
                    if doc_file:
                        for segment in file.segments:
                            segment_line_idx = segment.line - 1

                            if not doc_file.Lines[segment_line_idx].Coverage:
                                doc_file.Lines[
                                    segment_line_idx].Coverage = DocCodeCxxCoverage()

                            doc_file.Lines[segment_line_idx].Coverage.Call.append(
                                DocCodeRunCall(
                                    Count=segment.count,
                                    CalledBy=cookie.test_name,
                                ))

    if conf.json_out_path:
        conf.json_out_path.write_text(result.model_dump_json(indent=2))

    generate_html_for_directory(result, html_out_path=conf.html_out_path)


if __name__ == "__main__":
    cli()
