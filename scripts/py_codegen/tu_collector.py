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
        # return
        pass

    tool = local[conf.indexing_tool]

    tmp_output = tmp.joinpath(md5(str(output).encode("utf-8")).hexdigest() + ".pb")
    target_files = tmp_output.with_suffix(".json")
    with open(str(target_files), "w") as file:
        file.write(json.dumps([str(input)], indent=2))

    flags = [
        f"-p={conf.compilation_database}",
        f"--compilation-database={conf.compilation_database}",
        f"--out={str(tmp_output)}",
        f"--toolchain-include={conf.toolchain_include}",
        f"--target-files={target_files}",
        str(input),
    ]

    res_code, res_stdout, res_stderr = cast(Tuple[int, str, str], tool.run(flags, retcode=None))

    if res_code != 0:
        if res_stdout:
            print(res_stdout)

        if res_stderr:
            print(res_stderr)

        print(" \\ \n".join([conf.indexing_tool] + ["    " + f for f in flags]))

    else:
        if res_stdout:
            print(res_stdout)

        if res_stderr:
            print(res_stderr)

        tu = conv_proto_file(str(tmp_output))
        with open(output, "w") as file:
            pprint(tu, width=200, stream=file)

        refl[str(input)] = time.time()
        with open(conf.reflect_cache, "w") as file:
            file.write(json.dumps(refl, indent=2))

        return tu


def hash_qual_type(t: QualType) -> int:
    parts: List[str] = []
    if t.func:
        parts.append(hash_qual_type(t.func.ReturnTy))
        for T in t.func.Args:
            parts.append(hash_qual_type(T))

    elif t.isArray:
        parts.append(hash("<c-array>"))

    else:
        parts.append(hash(t.name))
        for param in t.Parameters:
            parts.append(hash_qual_type(param))

    assert parts != [0], pformat(t)

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

    def id_from_hash(self, hashed: int) -> int:
        if hashed not in self.id_map:
            self.id_map[hashed] = len(self.id_map)

        return self.id_map[hashed]

    def id_from_entry(self,
                      entry: Union[GenTuFunction, GenTuStruct, GenTuEnum, GenTuTypedef],
                      parent: Optional[QualType] = None) -> int:
        if isinstance(entry, GenTuStruct):
            return self.id_from_hash(hash_qual_type(entry.name))

        elif isinstance(entry, GenTuEnum):
            return self.id_from_hash(hash_qual_type(entry.name))

        elif isinstance(entry, GenTuTypedef):
            return self.id_from_hash(hash_qual_type(entry.name))

        else:
            assert False

    def use_type(self, _id: int, Type: QualType, dbg_from: str = ""):
        _type = self.id_from_hash(hash_qual_type(Type))
        if _type == len(self.graph.vs):
            self.graph.add_vertex()
            self.graph.vs[_type]["label"] = Type.format()
            self.graph.vs[_type]["dbg_origin"] = Type.dbg_origin

        if not self.graph.are_connected(_id, _type):
            self.graph.add_edge(_id, _type)
            self.graph.es[self.graph.get_eid(
                _id, _type)]["dbg_origin"] = f"{dbg_from} -> {Type.format()}"

    def merge_structs(self, stored: GenTuStruct, added: GenTuStruct):
        pass

    def merge_enums(self, stored: GenTuEnum, added: GenTuEnum):
        pass

    def add_entry(self, entry: Union[GenTuStruct, GenTuEnum, GenTuTypedef],
                  sub: Sub) -> int:
        _id = self.id_from_entry(entry)
        if _id not in self.id_to_entry:
            self.id_to_entry[_id] = deepcopy(entry)

        sub.nodes.add(_id)
        if len(self.graph.vs) <= _id:
            self.graph.add_vertex()

        return _id

    def add_struct(self, struct: GenTuStruct, sub: Sub):
        _id = self.add_entry(struct, sub)

        merge = self.id_to_entry[_id]
        self.merge_structs(merge, struct)

        self.graph.vs[_id]["label"] = struct.name.format()
        self.graph.vs[_id]["dbg_origin"] = struct.name.dbg_origin
        self.graph.vs[_id]["color"] = "green"

        for field in struct.fields:
            self.use_type(_id, field.type, dbg_from=struct.name.format())

    def add_enum(self, enum: GenTuEnum, sub: Sub):
        _id = self.add_entry(enum, sub)

        merge = self.id_to_entry[_id]
        self.merge_enums(merge, enum)

        self.graph.vs[_id]["label"] = enum.name.format()
        self.graph.vs[_id]["dbg_origin"] = enum.name.dbg_origin
        self.graph.vs[_id]["color"] = "red"

    def add_typedef(self, typedef: GenTuTypedef, sub: Sub):
        _id = self.add_entry(typedef, sub)
        merge = self.id_to_entry[_id]

        self.graph.vs[_id]["label"] = typedef.name.format()
        self.graph.vs[_id]["dbg_origin"] = typedef.name.dbg_origin
        self.graph.vs[_id]["color"] = "blue"

    def add_unit(self, wrap: TuWrap):
        sub = GenGraph.Sub(wrap.name)
        self.subgraphs.append(sub)
        for struct in wrap.tu.structs:
            self.add_struct(struct, sub)

        for enum in wrap.tu.enums:
            self.add_enum(enum, sub)

        for typedef in wrap.tu.typedefs:
            self.add_typedef(typedef, sub)

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
                    c.node(f'{sub.name}_{node}',
                           **{attr: g.vs[node][attr] for attr in g.vs.attributes()})
                    added_nodes.add(node)
                    if node in parent_tus and 1 < len(parent_tus[node]):
                        for target in parent_tus[node]:
                            if target != sub.name:
                                dot.edge(f"{target}_{node}", f"{sub.name}_{node}")

        # Add top-level nodes
        for node in range(len(g.vs)):
            if node not in added_nodes:
                dot.node(str(node),
                         **{attr: g.vs[node][attr] for attr in g.vs.attributes()})

        # Add edges
        for edge in g.es:
            source, target = edge.tuple

            source_subs = [sub.name for sub in self.subgraphs if source in sub.nodes]
            target_subs = [sub.name for sub in self.subgraphs if target in sub.nodes]

            attrs = {
                attr: g.es[g.get_eid(source, target)][attr] for attr in g.es.attributes()
            }

            if source_subs and target_subs:
                # Find subgraphs of source and target
                dot.edge(f'{source_subs[0]}_{source}', f'{target_subs[0]}_{target}',
                         **attrs)

            elif source_subs:
                dot.edge(f'{source_subs[0]}_{source}', f'{target}', **attrs)

            elif target_subs:
                dot.edge(f'{source}', f'{target_subs[0]}_{target}', **attrs)

            else:
                dot.edge(str(source), str(target), **attrs)

        # Render the graph to a file
        dot.render(output_file)


def model_options(f):
    return conf_provider.apply_options(f, conf_provider.options_from_model(TuOptions))


class CompileCommand(BaseModel):
    directory: str
    command: str
    file: str
    output: Optional[str] = None


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

    
    commands: List[CompileCommand] = [CompileCommand.model_validate(d) for d in json.load(open(conf.compilation_database))]

    for path in paths:
        if any([cmd.file == str(path) for cmd in commands]):
            log.info(path)
            tu: ConvTu = run_collector(conf, path, path.with_suffix(".py"))
            if tu is not None:
                wraps.append(TuWrap(name=path.stem, tu=tu))

        else:
            log.warnin(f"No compile commands for {path}")

    graph: GenGraph = GenGraph()
    for wrap in wraps:
        graph.add_unit(wrap)

    log.info("Finished conversion")

    graph.graph["rankdir"] = "LR"
    graph.to_graphviz("/tmp/output.dot")


if __name__ == "__main__":
    run()
