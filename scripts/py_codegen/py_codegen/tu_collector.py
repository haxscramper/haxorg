#!/usr/bin/env python

import rich_click as click
import py_scriptutils.toml_config_profiler as conf_provider
from py_codegen.refl_extract import (
    TuOptions,
    PathMapping,
    CompileCommand,
    TuWrap,
    expand_input,
    run_collector_for_path,
    GenGraph,
    read_compile_cmmands,
)

from beartype.typing import (
    Dict,
    List,
    Optional,
    cast,
    Any,
)

from py_scriptutils.script_logging import log
from py_scriptutils.tracer import GlobExportJson, TraceCollector
from pathlib import Path
import py_codegen.wrapper_gen_nim as gen_nim
import json

CONFIG_FILE_NAME = "tu_collector.toml"


def model_options(f) -> None:
    return conf_provider.apply_options(f, conf_provider.options_from_model(TuOptions))


def run_wrap_for_config(
    conf: TuOptions,
    wrap_time_trace: Optional[TraceCollector] = None,
) -> None:
    paths: List[PathMapping] = expand_input(conf)  # [:10]
    wraps: List[TuWrap] = []

    if not wrap_time_trace:
        wrap_time_trace = TraceCollector()

    out_dir = Path(conf.output_directory)
    if not out_dir.exists():
        log().info(f"Make directory {out_dir}")
        out_dir.mkdir(parents=True)

    with wrap_time_trace.complete_event("Load compilation database", "config"):
        commands: List[CompileCommand] = read_compile_cmmands(conf)

    out_map: Dict[Path, Path] = {}

    with wrap_time_trace.complete_event("Run reflection collector", "read"):
        mapping: PathMapping
        for mapping in paths:
            if any([cmd.file == str(mapping.path) for cmd in commands]):
                with wrap_time_trace.complete_event("Run collector", "read",
                                                    {"path": str(mapping.path)}):
                    wrap = run_collector_for_path(conf, mapping, commands)
                    if wrap:
                        wraps.append(wrap)
                        out_map[wrap.original] = wrap.mapping

            else:
                log("refl.cli.read").warning(f"No compile commands for {mapping.path}")

    with wrap_time_trace.complete_event("Merge graph information", "build"):
        graph: GenGraph = GenGraph()
        for wrap in wraps:
            graph.add_unit(wrap)

        log("refl.cli.read").info("Finished conversion")

    with wrap_time_trace.complete_event("Build graph edges", "build"):
        graph.connect_usages()

    with wrap_time_trace.complete_event("Group connected files", "build"):
        graph.group_connected_files()

    with wrap_time_trace.complete_event("Generate graphviz image", "write"):
        graph.to_graphviz("/tmp/output.dot", drop_zero_degree=True)
        graph.to_csv("/tmp/nodes.csv", "/tmp/edges.csv")

    graph.graph.write_graphml("/tmp/output.graphml")

    def get_out_path(path: Path) -> None:
        return out_map[path]

    def get_header_path(path: Path) -> str:
        return "<" + str(path.relative_to(Path(conf.header_root))) + ">"

    with wrap_time_trace.complete_event("Write wrapper output", "write"):
        for sub in graph.subgraphs:
            with wrap_time_trace.complete_event("Single file wrap", "write",
                                                {"original": str(sub.original)}):
                code: Optional[str] = gen_nim.to_nim(
                    graph=graph,
                    sub=sub,
                    conf=conf.nim.model_copy(
                        update=dict(path_resolution_impl=conf.nim.path_resolution_impl or
                                    get_header_path)),
                    get_out_path=get_out_path,
                    output_directory=Path(conf.output_directory),
                ).content

                if code:
                    result = get_out_path(sub.original)
                    with open(str(result), "w") as file:
                        file.write(code)

                else:
                    log().warning(f"No declarations found for {sub.original}")

    with wrap_time_trace.complete_event("Write translation unit information", "write"):
        for sub in graph.subgraphs:
            with wrap_time_trace.complete_event("Write subgraph information", "write",
                                                {"original": str(sub.original)}):
                with wrap_time_trace.complete_event("Collect declaration info", "write"):
                    info = graph.to_decl_info(sub)

                result = get_out_path(sub.original)
                result = result.with_stem(result.stem + "-tu").with_suffix(".json")

                with wrap_time_trace.complete_event("Write JSON information for file",
                                                    "write"):
                    with open(str(result), "w") as file:
                        file.write(json.dumps(info.model_dump(), indent=2))

    log("refl.cli.read").info("Done all")


@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@model_options
@click.pass_context
def run(ctx: click.Context, config: str, **kwargs: Any) -> None:
    assert Path(config).exists()
    config = str(Path(config).resolve())
    config_base = conf_provider.run_config_provider(
        ([config] if config else
         conf_provider.find_default_search_locations(CONFIG_FILE_NAME)), True)
    conf: TuOptions = cast(
        TuOptions, conf_provider.merge_cli_model(ctx, config_base, kwargs, TuOptions))

    run_wrap_for_config(conf)


if __name__ == "__main__":
    run()
