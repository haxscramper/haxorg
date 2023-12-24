#!/usr/bin/env python

import rich_click as click
import py_scriptutils.toml_config_profiler as conf_provider
from py_codegen.refl_extract import (
    TuOptions,
    PathMapping,
    CompileCommand,
    TuWrap,
    expand_input,
)

from beartype.typing import (
    Dict,
    List,
    Optional,
    cast,
)

from py_scriptutils.tracer import GlobCompleteEvent, GlobExportJson

CONFIG_FILE_NAME = "tu_collector.toml"


def model_options(f):
    return conf_provider.apply_options(f, conf_provider.options_from_model(TuOptions))


@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@model_options
@click.pass_context
def run(ctx: click.Context, config: str, **kwargs):
    config_base = conf_provider.run_config_provider(
        ([config] if config else
         conf_provider.find_default_search_locations(CONFIG_FILE_NAME)), True)
    conf: TuOptions = cast(
        TuOptions, conf_provider.merge_cli_model(ctx, config_base, kwargs, TuOptions))

    paths: List[PathMapping] = expand_input(conf.input, conf.path_suffixes,
                                            conf.directory_root and
                                            Path(conf.directory_root))  # [:10]
    wraps: List[TuWrap] = []

    with GlobCompleteEvent("Load compilation database", "config"):
        commands: List[CompileCommand] = [
            CompileCommand.model_validate(d)
            for d in json.load(open(conf.compilation_database))
        ]

    out_map: Dict[Path, Path] = {}

    with GlobCompleteEvent("Run reflection collector", "read"):
        mapping: PathMapping
        for mapping in paths:
            if any([cmd.file == str(mapping.path) for cmd in commands]):
                with GlobCompleteEvent("Run collector", "read",
                                       {"path": str(mapping.path)}):
                    wrap = run_collector_for_path(conf, mapping, commands)
                    if wrap:
                        wraps.append(wrap)
                        out_map[wrap.original] = wrap.mapping

            else:
                log.warning(f"No compile commands for {mapping.path}")

    with GlobCompleteEvent("Merge graph information", "build"):
        graph: GenGraph = GenGraph()
        for wrap in wraps:
            graph.add_unit(wrap)

        log.info("Finished conversion")

    with GlobCompleteEvent("Build graph edges", "build"):
        graph.connect_usages()

    with GlobCompleteEvent("Group connected files", "build"):
        graph.group_connected_files()

    with GlobCompleteEvent("Generate graphviz image", "write"):
        graph.to_graphviz("/tmp/output.dot", drop_zero_degree=True)
        graph.to_csv("/tmp/nodes.csv", "/tmp/edges.csv")

    graph.graph.write_graphml("/tmp/output.graphml")

    def get_out_path(path: Path):
        return out_map[path]

    with GlobCompleteEvent("Write wrapper output", "write"):
        for sub in graph.subgraphs:
            with GlobCompleteEvent("Single file wrap", "write",
                                   {"original": str(sub.original)}):
                code: Optional[str] = gen_nim.to_nim(graph=graph,
                                                     sub=sub,
                                                     conf=conf.nim,
                                                     get_out_path=get_out_path,
                                                     output_directory=Path(
                                                         conf.output_directory))

                if code:
                    result = get_out_path(sub.original)
                    with open(str(result), "w") as file:
                        file.write(code)

                else:
                    log.warning(f"No declarations found for {sub.original}")

    with GlobCompleteEvent("Write translation unit information", "write"):
        for sub in graph.subgraphs:
            with GlobCompleteEvent("Write subgraph information", "write",
                                   {"original": str(sub.original)}):
                with GlobCompleteEvent("Collect declaration info", "write"):
                    info = graph.to_decl_info(sub)

                result = get_out_path(sub.original)
                result = result.with_stem(result.stem + "-tu").with_suffix(".json")

                with GlobCompleteEvent("Write JSON information for file", "write"):
                    with open(str(result), "w") as file:
                        file.write(json.dumps(info.model_dump(), indent=2))

    GlobExportJson(conf.execution_trace)
    log.info("Done all")


if __name__ == "__main__":
    run()
