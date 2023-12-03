#!/usr/bin/env python

from beartype import beartype
from beartype.typing import (
    List,
    cast,
    Any,
    Tuple,
    Union,
    Dict,
    Set,
    Optional,
    TypeAlias,
    NewType,
)
from pydantic import BaseModel, Field
from pprint import pprint, pformat
from plumbum import local
from hashlib import md5
import re
from gen_tu_cpp import (GenTuStruct, GenTuFunction, GenTuEnum, QualType, GenTuTypedef,
                        GenTuEnumField, QualTypeKind, GenTuField)
from dataclasses import dataclass, field
from copy import deepcopy
import json
import time
import os
import math
from pathlib import Path
import igraph as ig
import graphviz as gv
from py_scriptutils.tracer import GlobCompleteEvent, GlobExportJson
import astbuilder_nim as nim
from py_textlayout.py_textlayout import TextLayout, TextOptions
import deal
import shutil
import itertools

from py_scriptutils.script_logging import log
from py_scriptutils.files import IsNewInput
import py_scriptutils.toml_config_profiler as conf_provider
from refl_read import conv_proto_file, ConvTu, open_proto_file

import rich_click as click

from typing import TYPE_CHECKING

CONFIG_FILE_NAME = "tu_collector.toml"

if TYPE_CHECKING:
    from py_textlayout.py_textlayout import BlockId
else:
    BlockId = NewType('BlockId', int)


def file_relpath(base: Path, target: Path) -> str:
    if base.parent == target.parent:
        return "./" + target.name

    else:
        dir_source = os.path.dirname(base.resolve())

        # Compute the relative path
        relative_path = os.path.relpath(target.resolve(), dir_source)

        # Ensure the path starts with "./" if it doesn't go up in the hierarchy
        if not relative_path.startswith(("..", "/")):
            relative_path = f"./{relative_path}"

        return relative_path

class WrapRenameRule(BaseModel):
    original: str = Field(description="Regex pattern for input text matching")
    renamed: str = Field(description="Replacement pattern")


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

    execution_trace: str = Field(description="Output path for the execution trace json",
                                 default="/tmp/tu_collector_trace.json")

    output_directory: str = Field(description="Directory to write output wrapped files")

    convert_failure_log_dir: str = Field(
        default="/tmp/tu_collector/converter_fails",
        description=
        "Directory to dump debug information about failed translation unit converter runs"
    )

    universal_import: List[str] = Field(default=[],
                                        description="Import added to all generated files")

    function_renames: List[WrapRenameRule] = Field(default=[], description="List of renaming rules for generated wrappers")

def apply_rename(name: str, renames: List[WrapRenameRule]) -> str:
    for rule in renames:
        if re.match(rule.original, name):
            return re.sub(rule.original, rule.renamed, name)

    return name

@beartype
@dataclass
class PathMapping:
    path: Path
    root: Optional[Path] = None


@beartype
def expand_input(input: List[str], path_suffixes: List[str]) -> List[PathMapping]:
    result: List[PathMapping] = []
    for item in input:
        path = Path(item)
        if path.is_file():
            result.append(PathMapping(item))

        elif path.is_dir():
            for sub in path.rglob("*"):
                if sub.suffix in path_suffixes:
                    result.append(PathMapping(sub, path))

        else:
            for sub in Path().glob(item):
                result.append(PathMapping(sub))

    return result


@beartype
class TranslationUnitLocations(BaseModel):
    # Information about external dependencies of a translation unit -- `Name` of the dependency
    # library/package and the relative path inside of this library.
    Name: str = Field(description="Name of the translation unit group", default="")
    Files: List[Path] = Field(
        description="Paths relative to the root directory of this translation unit group")


@beartype
class TranslationUnitInfo(BaseModel):
    Defines: List[QualType] = Field(
        description="List of types defined in the translation module",
        default_factory=list)
    Depends: List[TranslationUnitLocations] = Field(
        description="Dependencies on translation units from other external locations",
        default_factory=list)


@beartype
@dataclass
class CollectorRunResult:
    conv_tu: Optional[ConvTu]
    pb_path: Optional[Path]
    success: bool
    res_stdout: str
    res_stderr: str
    flags: List[str] = field(default_factory=list)


@beartype
def run_collector(conf: TuOptions, input: Path,
                  output: Path) -> Optional[CollectorRunResult]:
    # Execute reflection data collector binary, producing a new converted translation
    # unit or an empty result of conversion has failed.
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

    # Create a temporary list of files content will be added to the dumped translation
    # unit.
    tmp_output = tmp.joinpath(md5(str(output).encode("utf-8")).hexdigest() + ".pb")
    target_files = tmp_output.with_suffix(".json")

    flags = [
        f"-p={conf.compilation_database}",
        f"--compilation-database={conf.compilation_database}",
        f"--out={str(tmp_output)}",
        f"--toolchain-include={conf.toolchain_include}",
        f"--target-files={target_files}",
        str(input),
    ]

    if IsNewInput([str(input), conf.indexing_tool], tmp_output):
        with open(str(target_files), "w") as file:
            file.write(json.dumps([str(input)], indent=2))

        log.info(f"Running collector on {input}")

        res_code, res_stdout, res_stderr = cast(Tuple[int, str, str],
                                                tool.run(flags, retcode=None))

    else:
        res_code = 0
        res_stdout = ""
        res_stderr = ""

    if res_code != 0:
        log.warning(f"Failed to run collector for {input}")
        return CollectorRunResult(
            None,
            None,
            success=False,
            res_stdout=res_stdout,
            res_stderr=res_stderr,
            flags=flags,
        )

    else:
        tu = conv_proto_file(str(tmp_output))
        refl[str(input)] = time.time()
        with open(conf.reflect_cache, "w") as file:
            file.write(json.dumps(refl, indent=2))

        return CollectorRunResult(
            tu,
            tmp_output,
            success=True,
            res_stdout=res_stdout,
            res_stderr=res_stderr,
            flags=flags,
        )


@beartype
def hash_qual_type(t: QualType) -> int:
    # Generate a hashed value for qualified type, ignoring constant qualifiers,
    # pointers and other elements. This function is primarily used to map
    # declared entries to some simpler value for ID.
    parts: List[str] = [hash(t.Kind)]
    match t.Kind:
        case QualTypeKind.FunctionPtr:
            parts.append(hash_qual_type(t.func.ReturnTy))
            for T in t.func.Args:
                parts.append(hash_qual_type(T))

        case QualTypeKind.Array:
            pass

        case QualTypeKind.RegularType:
            parts.append(hash(t.name))
            for param in t.Parameters:
                parts.append(hash_qual_type(param))

    assert parts != [0], pformat(t)

    return hash(tuple(parts))


@dataclass
class TuWrap:
    name: str
    tu: ConvTu
    original: Path
    mapping: Path


@beartype
@dataclass
class ConvRes:
    # Result of the single entry conversion: main declaration and
    # additional wrapper structures and procedures accompanying it.
    procs: List[nim.FunctionParams] = field(default_factory=list)
    types: List[Union[nim.EnumParams, nim.ObjectParams,
                      nim.TypedefParams]] = field(default_factory=list)


GenTuUnion: TypeAlias = Union[GenTuStruct, GenTuEnum, GenTuTypedef, GenTuFunction]


@beartype
@dataclass
class GenGraph:

    @beartype
    @dataclass
    class Sub:
        name: str
        original: Path
        nodes: Set[int] = field(default_factory=set)

    id_to_entry: Dict[int, Union[GenTuFunction, GenTuStruct,
                                 GenTuEnum]] = field(default_factory=dict)
    graph: ig.Graph = field(default_factory=lambda: ig.Graph(directed=True))
    subgraphs: List[Sub] = field(default_factory=list)

    id_map: Dict[int, int] = field(default_factory=dict)

    out_map: Dict[Path, Path] = field(default_factory=dict)

    def get_out_path(self, path: Path) -> Path:
        return self.out_map[path]

    def get_sub(self, _id: int) -> Optional[Sub]:
        matching: List[GenGraph.Sub] = []
        for sub in self.subgraphs:
            if _id in sub.nodes:
                matching.append(sub)

        assert len(matching) <= 1, [
            f"{m.name}, {m.original}, id: {_id}, entry: {self.id_to_entry[_id].format()}"
            for m in matching
        ]
        if len(matching) == 1:
            return matching[0]

        else:
            return None

    def get_declared_sub(self, typ: QualType) -> Optional[Sub]:
        _id = self.id_from_hash(hash_qual_type(typ))
        if not (typ.isPrimitive() or typ.isArray() or
                typ.isFunction()) and _id not in self.id_to_entry:
            log.warning(f"No known declaration of the [red]{typ.format()}[/red]")

        return self.get_sub(_id)

    # Generate import from file placed in `result` to the content defined in `sub`
    def gen_file_import(self, import_source: Path,
                        import_target: Path) -> Optional[nim.ImportParams]:
        if import_target.resolve() != import_source.resolve():
            return nim.ImportParams([
                nim.ImportParamsFile(file_relpath(import_source, import_target),
                                     "From gen file")
            ],
                                    FormatMode=nim.ImportParamsMode.Single)

    def to_nim_imports(self, sub: Sub) -> nim.ImportParams:
        external: Set[int] = set()
        for _id in sub.nodes:
            for out in self.graph.incident(_id, mode="out"):
                target = self.graph.es[out].target
                if target not in sub.nodes:
                    external.add(target)

        target_groups = [
            sub for sub in self.subgraphs if 0 < len(sub.nodes.intersection(external))
        ]
        result = nim.ImportParams(QuoteImport=True,
                                  FormatMode=nim.ImportParamsMode.Single)
        for target in target_groups:
            import_source = self.get_out_path(sub.original)
            import_target = self.get_out_path(target.original)
            if import_source.resolve() != import_target.resolve():
                result.Imported.append(
                    nim.ImportParamsFile(Name=file_relpath(import_source, import_target)))

        return result

    def id_from_hash(self, hashed: int) -> int:
        if hashed not in self.id_map:
            self.id_map[hashed] = len(self.id_map)

        return self.id_map[hashed]

    def id_from_entry(self, entry: GenTuUnion, parent: Optional[QualType] = None) -> int:
        match entry:
            case GenTuStruct():
                return self.id_from_hash(hash_qual_type(entry.name))

            case GenTuEnum():
                return self.id_from_hash(hash_qual_type(entry.name))

            case GenTuTypedef():
                return self.id_from_hash(hash_qual_type(entry.name))

            case GenTuFunction():
                return self.id_from_hash(
                    hash(
                        tuple([
                            hash_qual_type(entry.result),
                            hash(entry.name),
                        ] + [hash_qual_type(t.type) for t in entry.arguments])))

            case _:
                assert False

    def use_type(self, _id: int, Type: QualType, dbg_from: str = ""):
        _type = self.id_from_hash(hash_qual_type(Type))
        if _type == len(self.graph.vs):
            self.graph.add_vertex()
            self.graph.vs[_type]["label"] = Type.format()
            self.graph.vs[_type]["dbg_origin"] = Type.dbg_origin
            self.graph.vs[_type]["is_builtin"] = Type.isBuiltin or Type.name in [
                "size_t", "uint32_t", "uint16_t", "int32_t"
            ]

        if not self.graph.are_connected(_id, _type):
            self.graph.add_edge(_id, _type)
            self.graph.es[self.graph.get_eid(
                _id, _type)]["dbg_origin"] = f"{dbg_from} -> {Type.format()}"

    @deal.post(lambda result: not any([it is None for it in result]))
    def get_used_type(self, decl: GenTuUnion) -> List[QualType]:
        result: List[QualType] = []

        def use_rec_type(t: QualType):
            match t.Kind:
                case QualTypeKind.RegularType:
                    result.append(t)
                    for p in t.Parameters:
                        use_rec_type(p)

                case QualTypeKind.FunctionPtr:
                    for arg in t.func.Args:
                        use_rec_type(arg)

                case QualTypeKind.Array:
                    for p in t.Parameters:
                        use_rec_type(p)

                case QualTypeKind.TypeExpr:
                    pass

                case _:
                    assert False, t.Kind

        match decl:
            case GenTuStruct():
                for _field in decl.fields:
                    assert _field.type, _field
                    use_rec_type(_field.type)

            case GenTuFunction():
                for arg in decl.arguments:
                    assert arg.type, arg
                    use_rec_type(arg.type)

                assert decl.result, decl
                use_rec_type(decl.result)

            case GenTuTypedef():
                assert decl.base, decl
                use_rec_type(decl.base)

            case GenTuEnum():
                pass

            case _:
                assert False, type(decl)

        return result

    def merge_structs(self, stored: GenTuStruct, added: GenTuStruct):
        stored_fields = set([f.name for f in stored.fields])
        for _field in added.fields:
            if _field.name not in stored_fields:
                stored.fields.append(deepcopy(_field))

    def merge_enums(self, stored: GenTuEnum, added: GenTuEnum):
        pass

    def merge_functions(self, stored: GenTuFunction, added: GenTuFunction):
        pass

    def add_entry(self, entry: GenTuUnion, sub: Sub) -> int:
        _id = self.id_from_entry(entry)
        if _id in self.id_to_entry:
            if isinstance(entry, GenTuStruct) or isinstance(entry, GenTuEnum):
                olddef = self.id_to_entry[_id]
                if olddef.IsForwardDecl and not entry.IsForwardDecl:
                    # Previously added declaration was a forward declaration and it needs to be removed from
                    # all subgraphs since there is not a proper definition present in the graph
                    for old in self.subgraphs:
                        if _id in old.nodes:
                            old.nodes.discard(_id)

                    # New subgraph properly introduces type definition and it should contain
                    # the content instead.
                    sub.nodes.add(_id)

                elif not olddef.IsForwardDecl and entry.IsForwardDecl:
                    # Newly introduced type is a forward declaration and should not be added to a new subgraph
                    pass

                elif olddef.IsForwardDecl and entry.IsForwardDecl:
                    # Haven't found proper forward declaration yet, new ones still don't need to be added to
                    # more graphs
                    pass

                elif not olddef.IsForwardDecl and not entry.IsForwardDecl:
                    log.error(
                        f"Two full definitions of the same entry {entry.format(dbgOrigin=True)} == {olddef.format(dbgOrigin=True)} in the code"
                    )

            else:
                # Multiple declarations of the same functions across different modules, TODO is this an error
                sub.nodes.add(_id)

        else:
            # This ID has never been registered for the type graph and it should be added to the
            # translation unit subgraph unconditionally
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

    def add_function(self, func: GenTuFunction, sub: Sub):
        _id = self.add_entry(func, sub)
        merge = self.id_to_entry[_id]
        self.merge_functions(merge, func)

        self.graph.vs[_id]["label"] = func.format()
        self.graph.vs[_id]["color"] = "magenta"

    def add_unit(self, wrap: TuWrap):
        sub = GenGraph.Sub(wrap.name, wrap.original)
        self.out_map[wrap.original] = wrap.mapping
        self.subgraphs.append(sub)
        for struct in wrap.tu.structs:
            self.add_struct(struct, sub)

        for enum in wrap.tu.enums:
            self.add_enum(enum, sub)

        for typedef in wrap.tu.typedefs:
            self.add_typedef(typedef, sub)

        for func in wrap.tu.functions:
            self.add_function(func, sub)

    def connect_usages(self, conf: TuOptions):
        for _id, decl in self.id_to_entry.items():
            for used_type in self.get_used_type(decl):
                self.use_type(_id, used_type)

        # Cross-subgraph usage does not generate cycles all the time. This code expands edge structure
        # through all the types placed in a single file. Given a file `FA` with types `A1, A2` defined
        # and file `FB` with types `B1, B2` and `A1 -> B2`, `A2 -> B1` relation, there is no cycle in
        # in the type graph, but when imports are generated, the import will be cyclic, because "is in
        # the same file" is also a relation that affects how the code is ought to be structured.
        #
        # By adding `A1 -> A2 -> ... AN -> A1` link, converter puts a new cycle into the type graph
        # and mutually recursive detection will pick it up later on.
        for sub in self.subgraphs:
            type_ids = list(
                itertools.dropwhile(
                    lambda _id: isinstance(self.id_to_entry[_id], GenTuFunction),
                    sub.nodes))

            if 1 < len(type_ids):
                for decl1, decl2 in itertools.pairwise(type_ids):
                    if decl1 != decl2:
                        self.graph.add_edge(decl1, decl2)

                self.graph.add_edge(type_ids[-1], type_ids[0])

    def group_connected_files(self, conf: TuOptions):
        # Find strongly connected components
        g = self.graph
        sccs = [scc for scc in g.connected_components(mode="strong") if 1 < len(scc)]

        with open("/tmp/sccs.txt", "w") as file:
            for idx, scc in enumerate(sccs):
                print(f"[{idx}] SCC group " + "~" * 120, file=file)
                for node in scc:
                    print(f"  Node {g.vs[node]['label']} in {g.vs[node]['dbg_origin']}",
                          file=file)
                    for edge in g.incident(node, mode="out"):
                        print(f"    -> {g.vs[g.es[edge].target]['label']}", file=file)

        # Map each vertex to its corresponding strongly connected component
        vertex_to_scc = {
            vertex: scc_index for scc_index, scc in enumerate(sccs) for vertex in scc
        }

        # Function to get the SCC index for a set of vertices
        def get_scc_indices(sub: GenGraph.Sub):
            return {vertex_to_scc[v] for v in sub.nodes if v in vertex_to_scc}

        ungrouped_sets: List[GenGraph.Sub] = []
        # Group vertex sets by their SCCs
        grouped_sets: Dict[frozenset, List[GenGraph.Sub]] = {}
        for vertex_set in self.subgraphs:
            scc_indices = frozenset(get_scc_indices(vertex_set))
            if len(scc_indices) == 0:
                ungrouped_sets.append(vertex_set)

            else:
                if scc_indices not in grouped_sets:
                    grouped_sets[scc_indices] = []
                grouped_sets[scc_indices].append(vertex_set)

        new_grouped: List[GenGraph.Sub] = []
        for group in grouped_sets.values():
            result = GenGraph.Sub(original=group[0].original, name=group[0].name)
            for item in group:
                result.nodes = result.nodes.union(item.nodes)

            new_grouped.append(result)

            if 1 < len(group):
                log.info("Merging strongly connected files %s" %
                         (", ".join([f"[green]{g.original}[/green]" for g in group])))

        self.subgraphs = new_grouped + ungrouped_sets

    def type_to_nim(self, b: nim.ASTBuilder, t: QualType) -> nim.Type:
        if t.func:
            return nim.Type(Name="",
                            Kind=nim.TypeKind.Function,
                            Parameters=[
                                self.type_to_nim(b, t.func.ReturnTy),
                            ] + [self.type_to_nim(b, arg) for arg in t.func.Args])
        elif t.name == "char" and t.isConst and t.ptrCount == 1:
            return nim.Type("cstring")

        elif t.name == "void" and t.ptrCount == 1:
            return nim.Type("pointer")

        elif t.Kind == QualTypeKind.Array:
            return nim.Type("array",
                            Parameters=[
                                self.type_to_nim(b, t.Parameters[1]),
                                self.type_to_nim(b, t.Parameters[0]),
                            ])

        elif t.Kind == QualTypeKind.TypeExpr:
            return nim.Type("", Kind=nim.TypeKind.Expr, Expr=b.string(t.expr))

        else:
            assert (t.Kind == QualTypeKind.RegularType)
            t_map = t.name
            match t.name:
                case "int":
                    t_map = "cint"
                case "short":
                    t_map = "cshort"
                case "unsigned short":
                    t_map = "cushort"

                case "int":
                    t_map = "cint"
                case "unsigned" | "unsigned int":
                    t_map = "cuint"

                case "long":
                    t_map = "clong"
                case "unsigned long":
                    t_map = "culong"

                case "long long":
                    t_map = "clonglong"
                case "unsigned long long":
                    t_map = "culonglong"

                case "void":
                    t_map = "void"

                case "char":
                    t_map = "char"
                case "unsigned char":
                    t_map = "uint8"

                case "float":
                    t_map = "cfloat"
                case "double":
                    t_map = "cdouble"
                case "bool":
                    t_map = "bool"
                case "size_t":
                    t_map = "csize_t"
                case "ssize_t":
                    t_map = "csize_t"

                case "int8_t":
                    t_map = "int8"
                case "int16_t":
                    t_map = "int16"
                case "int32_t":
                    t_map = "int32"
                case "int64_t":
                    t_map = "int64"

                case "uint8_t":
                    t_map = "uint8"
                case "uint16_t":
                    t_map = "uint16"
                case "uint32_t":
                    t_map = "uint32"
                case "uint64_t":
                    t_map = "uint64"
                case "auto":
                    t_map = "auto"

            result = nim.Type(Name=t_map)

            for i in range(t.ptrCount):
                result = nim.Type(Name="ptr", Parameters=[result])

            return result

    def enum_to_nim(self, b: nim.ASTBuilder, enum: GenTuEnum) -> ConvRes:
        result = ConvRes()
        c_name = "c_" + enum.name.name

        def f_name(f: GenTuEnumField) -> str:
            return nim.sanitize_name(f.name)

        def c_enum_field(idx: int, f: GenTuEnumField) -> nim.EnumFieldParams:
            value: str = ""
            if f.value == idx:
                value = str(f.value)

            elif f.value == 0:
                value = "0 shl 0"

            elif 0 < f.value and math.log2(f.value).is_integer():
                value = f"1 shl {int(math.log2(f.value))}"

            else:
                value = str(f.value)

            return nim.EnumFieldParams(Name="c_" + f_name(f), Value=b.string(value))

        result.procs.append(
            nim.FunctionParams(
                Kind=nim.FunctionKind.CONVERTER,
                Name="toCInt",
                Arguments=[nim.IdentParams(Name="arg", Type=nim.Type(c_name))],
                ReturnTy=nim.Type("cint"),
                Implementation=b.string("cint(ord(arg))"),
                OneLineImpl=True,
            ))

        w = max([len(f_name(f)) for f in enum.fields] + [0])
        result.procs.append(
            nim.FunctionParams(
                Kind=nim.FunctionKind.CONVERTER,
                Name="toCInt",
                Arguments=[
                    nim.IdentParams(Name="args",
                                    Type=nim.Type("set",
                                                  Parameters=[nim.Type(enum.name.name)]))
                ],
                ReturnTy=nim.Type("cint"),
                Implementation=b.stack(
                    b.string("for value in items(args):"),
                    b.indent(
                        2,
                        b.string("case value:"),
                        b.indent(
                            2, *[
                                b.string(
                                    f"of {f_name(f).ljust(w)}: result = cint(result or {f.value})"
                                ) for f in enum.fields
                            ]),
                    ),
                )))

        for op in ["-", "+"]:
            for arguments in [
                [
                    nim.IdentParams("arg", nim.Type(c_name)),
                    nim.IdentParams("offset", nim.Type("int"))
                ],
                [
                    nim.IdentParams("offset", nim.Type("int")),
                    nim.IdentParams("arg", nim.Type(c_name))
                ],
            ]:

                result.procs.append(
                    nim.FunctionParams(
                        Kind=nim.FunctionKind.FUNC,
                        Name=op,
                        Arguments=arguments,
                        ReturnTy=nim.Type("cint"),
                        Implementation=b.string(f"cast[{c_name}](ord(arg) {op} offset)"),
                        OneLineImpl=True,
                    ))

        fields: List[GenTuEnumField] = []

        for key, group in itertools.groupby(sorted(enum.fields, key=lambda f: f.value),
                                            key=lambda f: f.value):
            fields.append(list(group)[0])

        result.types.append(
            nim.EnumParams(Name=c_name,
                           Exported=True,
                           Pragmas=[
                               nim.PragmaParams(Name="size",
                                                Arguments=[
                                                    b.string("sizeof(cint)"),
                                                ])
                           ],
                           Fields=[c_enum_field(idx, f) for idx, f in enumerate(fields)]))

        result.types.append(
            nim.EnumParams(
                Name=enum.name.name,
                Exported=True,
                Fields=[nim.EnumFieldParams(Name=f_name(f)) for f in enum.fields]))

        return result

    def field_to_nim(self, b: nim.ASTBuilder, f: GenTuField) -> nim.IdentParams:
        result = nim.IdentParams(Name=nim.sanitize_name(f.name),
                                 Exported=True,
                                 Type=self.type_to_nim(b, f.type))
        if result.Name != f.name:
            result.Pragmas.append(nim.PragmaParams("importc", [b.Lit(f.name)]))

        return result

    def struct_to_nim(self, b: nim.ASTBuilder, rec: GenTuStruct) -> ConvRes:
        return ConvRes(types=[
            nim.ObjectParams(Name=rec.name.name,
                             Pragmas=[
                                 nim.PragmaParams("importc"),
                                 nim.PragmaParams("bycopy"),
                                 *([nim.PragmaParams("incompleteStruct")] if rec.
                                   IsForwardDecl else []),
                             ],
                             Fields=[self.field_to_nim(b, f) for f in rec.fields])
        ])

    def typedef_to_nim(self, b: nim.ASTBuilder, typdef: GenTuTypedef) -> ConvRes:
        return ConvRes(types=[
            nim.TypedefParams(Name=typdef.name.name,
                              Exported=True,
                              Base=self.type_to_nim(b, typdef.base))
        ])

    def function_to_nim(self, b: nim.ASTBuilder, func: GenTuFunction, conf: TuOptions) -> ConvRes:
        return ConvRes(procs=[
            nim.FunctionParams(Name=nim.sanitize_name(apply_rename(func.name, conf.function_renames)),
                               ReturnTy=self.type_to_nim(b, func.result),
                               Pragmas=[
                                   nim.PragmaParams("git2Proc"),
                                   nim.PragmaParams("importc", [b.Lit(func.name)]),
                               ],
                               Arguments=[
                                   nim.IdentParams(Arg.name, self.type_to_nim(
                                       b, Arg.type)) for Arg in func.arguments
                               ])
        ])

    def to_decl_info(self, sub: Sub) -> TranslationUnitInfo:
        result = TranslationUnitInfo()

        for _id in sub.nodes:
            decl = self.id_to_entry[_id]
            match decl:
                case GenTuEnum(name=name) | GenTuStruct(name=name) | GenTuTypedef(
                    name=name):
                    result.Defines.append(name)

        return result

    def to_nim(self, sub: Sub, conf: TuOptions) -> Optional[str]:
        t = TextLayout()
        builder = nim.ASTBuilder(t)

        types: List[BlockId] = []
        procs: List[BlockId] = []
        header: List[BlockId] = []
        depend_on: List[nim.ImportParams] = []

        for imp in sorted(conf.universal_import):
            gen = self.gen_file_import(self.get_out_path(sub.original),
                                       Path(conf.output_directory).joinpath(imp))
            if gen is not None:
                depend_on.append(gen)

        depend_on.append(self.to_nim_imports(sub))

        for _id in sub.nodes:
            decl = self.id_to_entry[_id]
            conv: ConvRes = ConvRes()

            match decl:
                case GenTuEnum():
                    conv = self.enum_to_nim(builder, decl)

                case GenTuStruct():
                    conv = self.struct_to_nim(builder, decl)

                case GenTuTypedef():
                    conv = self.typedef_to_nim(builder, decl)

                case GenTuFunction():
                    conv = self.function_to_nim(builder, decl, conf)

                case _:
                    assert False

            for proc in conv.procs:
                procs.append(builder.Function(proc))

            for _type in conv.types:
                if isinstance(_type, nim.EnumParams):
                    types.append(builder.Enum(_type))

                elif isinstance(_type, nim.ObjectParams):
                    types.append(builder.Object(_type))

                elif isinstance(_type, nim.TypedefParams):
                    types.append(builder.Typedef(_type))

        for item in depend_on:
            header.append(builder.Import(item))

        if 0 < len(types) or 0 < len(procs):
            opts = TextOptions()
            opts.rightMargin = 160
            if 0 < len(types):
                newCode = t.toString(
                    builder.sep_stack([
                        t.stack(header),
                        t.stack([
                            t.text("type"),
                            t.indent(2, builder.sep_stack(types)),
                        ]),
                        t.text(""),
                    ] + procs), opts)

            else:
                newCode = t.toString(t.stack(header + [builder.sep_stack(procs)]), opts)

            return newCode

    def to_csv(self, node_file, edge_file):
        """
        Export an igraph graph to CSV files for nodes and edges.

        Args:
        - graph (ig.Graph): The igraph graph to export.
        - node_file (str): File path for the nodes CSV.
        - edge_file (str): File path for the edges CSV.
        """
        import pandas as pd

        g = self.graph

        # Export Nodes to CSV
        nodes_data = [
            dict(node_id=node, **{attr: g.vs[node][attr]
                                  for attr in g.vs.attributes()})
            for node in range(len(g.vs))
        ]
        nodes_df = pd.DataFrame(nodes_data)
        nodes_df.to_csv(node_file, index=False)

        # Export Edges to CSV
        edges_data = [
            dict(edge_id=edge,
                 source_id=g.es[edge].source,
                 target_id=g.es[edge].target,
                 **{attr: g.es[edge][attr]
                    for attr in g.es.attributes()})
            for edge in range(len(g.es))
        ]
        edges_df = pd.DataFrame(edges_data)
        edges_df.to_csv(edge_file, index=False)

    def to_graphviz(self,
                    output_file: str,
                    with_subgraphs: bool = True,
                    drop_zero_degree: bool = False,
                    drop_builtin_types: bool = True):
        dot = gv.Digraph(format='dot')
        dot.attr(rankdir="LR")
        dot.attr(overlap="false")
        dot.attr(splies="true")
        dot.attr(ranksep="3")
        dot.attr("node", shape="rect")
        dot.attr(concentrate="true")
        g = self.graph

        # Track which nodes have been added to subgraphs
        added_nodes = set()

        @beartype
        def is_accepted_node(node: int) -> bool:
            if drop_zero_degree and g.degree(node) == 0:
                return False

            elif drop_builtin_types and g.vs[node]["is_builtin"]:
                return False

            else:
                return True

        @beartype
        def is_accepted_connection(edge: ig.Edge) -> bool:
            return not drop_builtin_types or not g.vs[edge.target]["is_builtin"]

        parent_tus: Dict[int, List[str]] = {}
        for node in g.vs:
            for sub in self.subgraphs:
                if node.index in sub.nodes:
                    if node.index not in parent_tus:
                        parent_tus[node.index] = [sub.name]

                    else:
                        parent_tus[node.index].append(sub.name)

        def rec_subgraph(target: gv.Graph, sub: GenGraph.Sub):
            for node in sub.nodes:
                if is_accepted_node(node):
                    target.node(
                        f'{sub.name}_{node}',
                        **{attr: str(g.vs[node][attr]) for attr in g.vs.attributes()})
                    added_nodes.add(node)
                    if node in parent_tus and 1 < len(parent_tus[node]):
                        for target in parent_tus[node]:
                            if target != sub.name:
                                dot.edge(f"{target}_{node}", f"{sub.name}_{node}")

        # Add nodes to subgraphs
        for sub in self.subgraphs:
            if with_subgraphs:
                with dot.subgraph(name=f'cluster_{sub.name}') as c:
                    c.attr(label=sub.name)
                    rec_subgraph(c, sub)

            else:
                rec_subgraph(dot, sub)

        # Add top-level nodes
        for node in range(len(g.vs)):
            if node not in added_nodes:
                if is_accepted_node(node):
                    dot.node(str(node),
                             **{attr: str(g.vs[node][attr]) for attr in g.vs.attributes()})

        # Add edges
        for edge in g.es:
            if not is_accepted_connection(edge):
                continue

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
        with open(output_file, "w") as file:
            file.write(dot.source)


def model_options(f):
    return conf_provider.apply_options(f, conf_provider.options_from_model(TuOptions))


class CompileCommand(BaseModel):
    directory: str
    command: str
    file: str
    output: Optional[str] = None


@beartype
def write_run_result_information(conf: TuOptions, tu: CollectorRunResult, path: Path,
                                 commands: List[CompileCommand]):
    debug_dir = Path(conf.convert_failure_log_dir)
    # if debug_dir.exists():
    #     shutil.rmtree(str(debug_dir))

    debug_dir.mkdir(parents=True, exist_ok=True)
    sanitized = "".join([c if c.isalnum() else "_" for c in str(path)])

    if not tu.success:
        log.warning(
            f"Failed to run conversion for [green]{path}[/green], wrote to {debug_dir}/{sanitized}"
        )

    with open(debug_dir.joinpath(sanitized), "w") as file:

        def sep(name: str):
            file.write("\n\n" + name + "-" * 120 + "\n\n")

        sep("Failure stdout:")
        file.write(tu.res_stdout)

        sep("Failure stderr:")
        file.write(tu.res_stderr)

        for cmd in commands:
            if cmd.file == str(path):
                sep("Compile commands:")
                file.write(json.dumps(cmd.model_dump(), indent=2))

                sep("Binary command:")
                file.write(" \\\n    ".join(cmd.command.split()))

        sep("Flags:")
        file.write(" \\\n    ".join([conf.indexing_tool] + tu.flags))


@beartype
def run_collector_for_path(conf: TuOptions, mapping: PathMapping,
                           commands: List[CompileCommand]) -> Optional[TuWrap]:
    path = mapping.path
    tu: CollectorRunResult = run_collector(conf, path, path.with_suffix(".py"))
    if tu.success:
        relative = Path(conf.output_directory).joinpath(path.relative_to(mapping.root))

        if not relative.parent.exists():
            relative.parent.mkdir(parents=True)

        with open(str(relative.with_suffix(".json")), "w") as file:
            file.write(open_proto_file(str(tu.pb_path)).to_json(2))

        write_run_result_information(conf, tu, path, commands)

        return TuWrap(name=path.stem,
                      tu=tu.conv_tu,
                      original=path,
                      mapping=relative.with_suffix(".nim"))


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

    log.info(conf.universal_import)

    paths: List[PathMapping] = expand_input(conf.input, conf.path_suffixes)  # [:10]
    wraps: List[TuWrap] = []

    with GlobCompleteEvent("Load compilation database", "config"):
        commands: List[CompileCommand] = [
            CompileCommand.model_validate(d)
            for d in json.load(open(conf.compilation_database))
        ]

    with GlobCompleteEvent("Run reflection collector", "read"):
        mapping: PathMapping
        for mapping in paths:
            if any([cmd.file == str(mapping.path) for cmd in commands]):
                with GlobCompleteEvent("Run collector", "read",
                                       {"path": str(mapping.path)}):
                    wrap = run_collector_for_path(conf, mapping, commands)
                    if wrap:
                        wraps.append(wrap)

            else:
                log.warning(f"No compile commands for {mapping.path}")

    with GlobCompleteEvent("Merge graph information", "build"):
        graph: GenGraph = GenGraph()
        for wrap in wraps:
            graph.add_unit(wrap)

        log.info("Finished conversion")

    with GlobCompleteEvent("Build graph edges", "build"):
        graph.connect_usages(conf)

    with GlobCompleteEvent("Group connected files", "build"):
        graph.group_connected_files(conf)

    with GlobCompleteEvent("Generate graphviz image", "write"):
        graph.to_graphviz("/tmp/output.dot", drop_zero_degree=True)
        graph.to_csv("/tmp/nodes.csv", "/tmp/edges.csv")

    graph.graph.write_graphml("/tmp/output.graphml")

    with GlobCompleteEvent("Write wrapper output", "write"):
        for sub in graph.subgraphs:
            with GlobCompleteEvent("Single file wrap", "write",
                                   {"original": str(sub.original)}):
                code: Optional[str] = graph.to_nim(sub, conf)
                if code:
                    result = graph.get_out_path(sub.original)
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

                result = graph.get_out_path(sub.original)
                result = result.with_stem(result.stem + "-tu").with_suffix(".json")

                with GlobCompleteEvent("Write JSON information for file", "write"):
                    with open(str(result), "w") as file:
                        file.write(json.dumps(info.model_dump(), indent=2))

    GlobExportJson(conf.execution_trace)
    log.info("Done all")


if __name__ == "__main__":
    run()
