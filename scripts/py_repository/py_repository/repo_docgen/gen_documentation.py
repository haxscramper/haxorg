#!/usr/bin/env python

import concurrent.futures
from dataclasses import dataclass
from pathlib import Path

import dominate.tags as tags
import dominate.util as util
import py_repository.repo_docgen.gen_documentation_cxx as cxx
import py_repository.repo_docgen.gen_documentation_data as docdata
import py_repository.repo_docgen.gen_documentation_python as py
import py_repository.repo_docgen.gen_documentation_utils as docutils
import py_repository.coverage_collection.gen_coverage_python as cov_docpy
import py_repository.coverage_collection.gen_coverage_cxx as cov_docxx
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
from py_scriptutils.tracer import GlobExportJson, GlobCompleteEvent
import py_scriptutils.tracer
import re
import json
import concurrent.futures
import functools
import traceback
import multiprocessing
import sys
from py_ci.util_scripting import get_threading_count

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
def generate_tree_sidebar(directory: docdata.DocDirectory,
                          html_out_path: Path) -> SidebarRes:
    directory_list = tags.ul(cls="sidebar-directory")
    directory_total_entries: int = 0
    directory_documented_entries: int = 0

    for subdir in directory.Subdirs:
        subdir_res = generate_tree_sidebar(subdir, html_out_path)
        link = tags.a(href=docdata.get_html_path(subdir, html_out_path=html_out_path))
        link.add(subdir.RelPath.name)
        directory_list.add(tags.li(link, subdir_res.tag))

        directory_total_entries += subdir_res.total_entries
        directory_documented_entries += subdir_res.documented_entries

    for code_file in directory.CodeFiles:
        total_entries: int = 0
        documented_entries: int = 0

        item = tags.li(_class="sidebar-code")
        link = tags.a(href=docdata.get_html_path(code_file, html_out_path=html_out_path))
        link.add(util.text(code_file.RelPath.name))
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


class DocGenerationOptions(BaseModel, extra="forbid"):
    html_out_path: Path = Field(description="Root directory to output generated HTML to")

    profile_out_path: Optional[Path] = Field(
        default=None,
        description="Write performance profiline to the output path",
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

    cxx_coverage_path: Path = Field(
        description="Merged coverage data sqlite",
        default=None,
    )

    coverage_file_whitelist: List[str] = Field(
        description=
        "List of regular expressions to whitelist absolute file paths for coverage",
        default_factory=lambda: [".*"],
    )

    coverage_file_blacklist: List[str] = Field(
        description=
        "List of regular expressions to blacklist absolute file paths for coverage",
        default_factory=list,
    )


def cli_options(f):
    return apply_options(f, options_from_model(DocGenerationOptions))


@beartype
@dataclass
class FileGenParams():
    file: docdata.DocCodeFile
    html_out_path: Path


@beartype
@dataclass
class FileGenResult():
    trace: List[py_scriptutils.tracer.TraceEvent]


def worker_decorator(func):

    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        try:
            return func(*args, **kwargs)
        except Exception as e:
            print(
                f"Exception in worker process {multiprocessing.current_process().name}: {e}"
            )
            sys.excepthook(*sys.exc_info())
            raise

    return wrapper


@beartype
@worker_decorator
def generate_code_file(
    gen: FileGenParams,
    opts: DocGenerationOptions,
) -> FileGenResult:
    py_scriptutils.tracer.GlobRestart()
    cxx_coverage_session = cov_docxx.open_coverage(opts.cxx_coverage_path)
    path = docdata.get_html_path(gen.file, html_out_path=gen.html_out_path)
    with GlobCompleteEvent("Get annotated files",
                           "cov",
                           args=dict(path=str(gen.file.RelPath))):
        file = cov_docxx.get_annotated_files_for_session(
            session=cxx_coverage_session,
            root_path=opts.root_path,
            abs_path=opts.root_path.joinpath(gen.file.RelPath),
            use_highlight=False,
        )

    with GlobCompleteEvent("Generate annotated file",
                           "cov",
                           args=dict(path=str(gen.file.RelPath))):
        data = cov_docxx.get_file_annotation_html(file)
        doc = document(title=str(gen.file.RelPath))
        doc.head.add(tags.link(rel="stylesheet", href=cov_docxx.css_path))
        doc.head.add(tags.script(src=str(cov_docxx.js_path)))
        json_dump = tags.script(
            type="application/json",
            id="segment-coverage",
        )

        with GlobCompleteEvent("Get execution for all segments", "cov"):
            executions = file.getExecutionsModelForAllSegments(data.coverage_indices)

        with GlobCompleteEvent("Dump execution model", "cov"):
            json_dump.add_raw_string(executions.model_dump_json(indent=2))

        doc.head.add(json_dump)

        doc.add(data.body)

        path.parent.mkdir(exist_ok=True, parents=True)
        with GlobCompleteEvent("Render HTML", "cov"):
            path.write_text(doc.render())

        with GlobCompleteEvent("Dump JSON", "cov"):
            path.with_suffix(".json").write_text(file.model_dump_json(indent=2))

        with GlobCompleteEvent("Dump Debug", "cov"):
            path.with_suffix(".txt").write_text(file.get_debug())

    log(CAT).info(f"Building HTML for {gen.file.RelPath} -> {path}")
    return FileGenResult(trace=py_scriptutils.tracer.GlobGetEvents())


@beartype
def generate_html_for_directory(
    directory: docdata.DocDirectory,
    html_out_path: Path,
    opts: DocGenerationOptions,
) -> None:
    sidebar_res = generate_tree_sidebar(directory, html_out_path=html_out_path)
    sidebar = tags.div(sidebar_res.tag, _class="sidebar-directory-root")
    coverage_whitelist: List[re.Pattern] = [
        re.compile(it) for it in opts.coverage_file_whitelist
    ]
    coverage_blacklist: List[re.Pattern] = [
        re.compile(it) for it in opts.coverage_file_blacklist
    ]

    @beartype
    def is_path_allowed(path: Path) -> bool:
        path = str(path)
        return any(it.match(path) for it in coverage_whitelist) and not any(
            it.match(path) for it in coverage_blacklist)

    target_code_files: List[FileGenParams] = []

    def aux(directory: docdata.DocDirectory, html_out_path: Path) -> None:
        with GlobCompleteEvent("Subdir", "cov", args=dict(path=str(directory.RelPath))):
            for subdir in directory.Subdirs:
                aux(subdir, html_out_path)

            for code_file in directory.CodeFiles:
                path = docdata.get_html_path(code_file, html_out_path=html_out_path)
                if not is_path_allowed(path):
                    continue

                target_code_files.append(
                    FileGenParams(html_out_path=html_out_path, file=code_file))

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

    with concurrent.futures.ProcessPoolExecutor(max_workers=get_threading_count()) as executor:
        futures = [
            executor.submit(
                functools.partial(
                    generate_code_file,
                    opts=opts,
                ),
                item,
            ) for item in target_code_files
        ]

        for future in futures:
            py_scriptutils.tracer.GlobAddEvents(future.result().trace)


@beartype
def parse_code_file(
    file: Path,
    conf: DocGenerationOptions,
    rel_path_to_code_file: Dict[Path, docdata.DocCodeFile],
    is_test: bool,
) -> docdata.DocCodeFile:
    code_file = docdata.DocCodeFile(RelPath=file.relative_to(conf.root_path))

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
    rel_path_to_code_file: Dict[Path, docdata.DocCodeFile],
    py_coverage_session: Optional[Session],
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
            case ".hpp" | ".py" | ".cpp" | ".tcc":
                result.CodeFiles.append(
                    parse_code_file(
                        file,
                        conf,
                        rel_path_to_code_file=rel_path_to_code_file,
                        is_test=is_test or
                        file.suffix == ".cpp",  # FIXME replace `is_test` with `is_impl`
                    ))

            case "*.org":
                result.TextFiles.append(parse_text_file(file))

            case _ if file.is_dir():
                subdir = parse_dir(
                    file,
                    conf,
                    rel_path_to_code_file=rel_path_to_code_file,
                    py_coverage_session=py_coverage_session,
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
    py_scriptutils.tracer.GlobNameThisProcess("Main")
    py_scriptutils.tracer.GlobIndexThisProcess(0)
    conf = get_cli_model(ctx, DocGenerationOptions, kwargs=kwargs, config=config)
    rel_path_to_code_file: Dict[Path, docdata.DocCodeFile] = {}

    py_coverage_session: Optional[Session] = None
    if conf.py_coverage_path:
        py_coverage_session = cov_docpy.open_coverage(conf.py_coverage_path)

    log(CAT).info(f"Loading code coverage from {conf.cxx_coverage_path}")

    with GlobCompleteEvent("Get file tree", "cov"):
        full_root = docdata.DocDirectory(
            RelPath=conf.root_path.relative_to(conf.root_path))
        for subdir in conf.test_path:
            full_root.Subdirs.append(
                parse_dir(
                    subdir,
                    conf,
                    rel_path_to_code_file=rel_path_to_code_file,
                    py_coverage_session=None,
                    is_test=True,
                ))

        for subdir in conf.src_path:
            full_root.Subdirs.append(
                parse_dir(
                    subdir,
                    conf,
                    rel_path_to_code_file=rel_path_to_code_file,
                    py_coverage_session=py_coverage_session,
                    is_test=False,
                ))

    with GlobCompleteEvent("Generate HTML for root", "cov"):
        generate_html_for_directory(
            full_root,
            html_out_path=conf.html_out_path,
            opts=conf,
        )

    if conf.profile_out_path:
        GlobExportJson(Path(conf.profile_out_path))
        log(CAT).info(f"Wrote profile to {conf.profile_out_path}")


if __name__ == "__main__":
    cli()
