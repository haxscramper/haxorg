#!/usr/bin/env python

from beartype import beartype
from beartype.typing import List, cast, Any, Tuple, Union, Dict, Set
from pydantic import BaseModel, Field
from pprint import pprint, pformat
from plumbum import local
from hashlib import md5
from gen_tu_cpp import *
from copy import deepcopy
import json
import time
import os
from pathlib import Path
import igraph as ig
import graphviz as gv

from py_scriptutils.script_logging import log
import py_scriptutils.toml_config_profiler as conf_provider
from refl_read import conv_proto_file, ConvTu

import rich_click as click

CONFIG_FILE_NAME = "tu_collector.toml"


class TuOptions(BaseModel):
    input: List[str] = Field(description="List of input files, directories or globs")
    indexing_tool: str = Field(description="Path to the TU index generator tool")
    compilation_database: str = Field(description="Path to the compilation database")
    binary_tmp: str = Field(description="Path to store temporary binary artifacts",
                            default="/tmp/tu_collector")
    toolchain_include: str = Field(
        description="Path to the toolchain that was used to compile indexing tool")
    reflect_cache: str = Field(description="Store last reflection convert timestamps",
                               default="/tmp/tu_collector/runs.json")
    path_suffixes: List[str] = Field(
        description="List of file suffixes used for dir list filtering",
        default=[".hpp", ".cpp", ".h", ".c", ".cxx"],
        alias="path-suffixes")


@beartype
def expand_input(input: List[str], path_suffixes: List[str]) -> List[Path]:
    result: List[str] = []
    for item in input:
        path = Path(item)
        if path.is_file():
            result.append(item)

        elif path.is_dir():
            for sub in path.rglob("*"):
                if sub.suffix in path_suffixes:
                    result.append(sub)

        else:
            for sub in Path().glob(item):
                result.append(sub)

    return result


@beartype
def run_collector(conf: TuOptions, input: Path, output: Path) -> Optional[ConvTu]:
    assert input.exists()
    if not output.parent.exists():
        output.parent.mkdir(parents=True)

    tmp = Path(conf.binary_tmp)
    if not tmp.exists():
        tmp.mkdir(parents=True)

    refl = {}
    if Path(conf.reflect_cache).exists():
        with open(conf.reflect_cache, "r") as file:
            refl = json.load(file)

    if (str(input) in refl) and (max(input.stat().st_mtime,
                                     Path(conf.indexing_tool).stat().st_mtime)
                                 < refl[str(input)]) and (output.exists()):
        log.info(f"{input} has already been converted to {output}")
        # return
        pass

    tool = local[conf.indexing_tool]

    tmp_output = tmp.joinpath(md5(str(output).encode("utf-8")).hexdigest() + ".pb")
    target_files = tmp_output.with_suffix(".json")
    with open(str(target_files), "w") as file:
        file.write(json.dumps([str(input)], indent=2))

    res_code, res_stdout, res_stderr = cast(
        Tuple[int, str, str],
        tool.run((
            f"-p={conf.compilation_database}",
            f"--compilation-database={conf.compilation_database}",
            f"--out={str(tmp_output)}",
            f"--toolchain-include={conf.toolchain_include}",
            f"--target-files={target_files}",
            str(input),
        ),
                 retcode=None))

    if res_code != 0:
        if res_stdout:
            print(res_stdout)

        if res_stderr:
            print(res_stderr)

    else:
        if res_stdout:
            print(res_stdout)

        if res_stderr:
            print(res_stderr)

        tu = conv_proto_file(str(tmp_output))
        with open(output, "w") as file:
            pprint(tu, width=200, stream=file)

        log.info(f"Converted TU file to {output}")
        refl[str(input)] = time.time()
        with open(conf.reflect_cache, "w") as file:
            file.write(json.dumps(refl, indent=2))

        return tu


def hash_qual_type(t: QualType) -> int:
    parts: List[str] = []
    parts.append(hash(t.name))
    for param in t.Parameters:
        parts.append(hash_qual_type(param))

    return hash(tuple(parts))


@dataclass
class TuWrap:
    name: str
    tu: ConvTu


@beartype
@dataclass
class GenGraph:

    @beartype
    @dataclass
    class Sub:
        name: str
        nodes: Set[int] = field(default_factory=set)

    id_to_entry: Dict[int, Union[GenTuFunction, GenTuStruct,
                                 GenTuEnum]] = field(default_factory=dict)
    graph: ig.Graph = field(default_factory=lambda: ig.Graph())
    subgraphs: List[Sub] = field(default_factory=list)

    id_map: Dict[int, int] = field(default_factory=dict)

    def id_from_entry(self,
                        entry: Union[GenTuFunction, GenTuStruct, GenTuEnum],
                        parent: Optional[QualType] = None) -> int:
        hashed: int = 0
        if isinstance(entry, GenTuStruct):
            hashed = hash_qual_type(entry.qual_name)

        else:
            assert False

        if hashed not in self.id_map:
            self.id_map[hashed] = len(self.id_map)

        return self.id_map[hashed]

    def merge_structs(self, stored: GenTuStruct, added: GenTuStruct):
        pass

    def add_struct(self, struct: GenTuStruct, sub: Sub):
        _id = self.id_from_entry(struct)
        if _id not in self.id_to_entry:
            self.id_to_entry[_id] = deepcopy(struct)

        merge = self.id_to_entry[_id]
        self.merge_structs(merge, struct)
        sub.nodes.add(_id)
        if len(self.graph.vs) <= _id:
            self.graph.add_vertex()
            self.graph.vs[_id]["label"] = struct.qual_name.name
        

    def add_unit(self, wrap: TuWrap):
        sub = GenGraph.Sub(wrap.name)
        self.subgraphs.append(sub)
        for struct in wrap.tu.structs:
            self.add_struct(struct, sub)

    def to_graphviz(self, output_file: str):
        dot = gv.Digraph(format='dot')
        dot.attr(rankdir="LR")
        dot.attr("node", shape="rect")
        g = self.graph

        # Track which nodes have been added to subgraphs
        added_nodes = set()


        parent_tus: Dict[int, List[str]] = {}
        for node in g.vs:
            for sub in self.subgraphs:
                if node.index in sub.nodes:
                    if node.index not in parent_tus:
                        parent_tus[node.index] = [sub.name]

                    else:
                        parent_tus[node.index].append(sub.name)


        # Add nodes to subgraphs
        for sub in self.subgraphs:
            with dot.subgraph(name=f'cluster_{sub.name}') as c:
                c.attr(label=sub.name)
                for node in sub.nodes:
                    c.node(f'{sub.name}_{node}', **{attr: g.vs[node][attr] for attr in g.vs.attributes()})
                    added_nodes.add(node)
                    if node in parent_tus and 1 < len(parent_tus[node]):
                        for target in parent_tus[node]:
                            if target != sub.name:
                                dot.edge(f"{target}_{node}", f"{sub.name}_{node}")

        

        # Add top-level nodes
        for node in range(len(g.vs)):
            if node not in added_nodes:
                dot.node(str(node), **{attr: g.vs[node][attr] for attr in g.vs.attributes()})

        # Add edges
        for edge in g.es:
            source, target = edge.tuple
            
            # Check if nodes are in subgraphs and link accordingly
            source_in_subgraph = source in added_nodes
            target_in_subgraph = target in added_nodes

            if source_in_subgraph and target_in_subgraph:
                # Find subgraphs of source and target
                source_subs = [sub.name for sub in self.subgraphs if source in sub.nodes]
                target_subs = [sub.name for sub in self.subgraphs if target in sub.nodes]
                
                for s_sub in source_subs:
                    for t_sub in target_subs:
                        dot.edge(f'{s_sub}_{source}', f'{t_sub}_{target}')
            else:
                dot.edge(str(source), str(target))

        # Render the graph to a file
        dot.render(output_file)


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
    conf: TuOptions = cast(TuOptions,
                           conf_provider.merge_cli_model(ctx, config_base, TuOptions))

    paths: List[Path] = expand_input(conf.input, conf.path_suffixes)
    wraps: List[TuWrap] = []

    for path in paths[:5]:
        tu: ConvTu = run_collector(conf, path, path.with_suffix(".py"))
        if tu is not None:
            wraps.append(TuWrap(name=path.stem, tu=tu))

    graph: GenGraph = GenGraph()
    for wrap in wraps:
        graph.add_unit(wrap)

    log.info("Finished conversion")

    graph.graph["rankdir"] = "LR"
    graph.to_graphviz("/tmp/output.dot")


if __name__ == "__main__":
    run()
