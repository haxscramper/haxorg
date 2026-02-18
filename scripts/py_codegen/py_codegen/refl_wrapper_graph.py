from copy import copy, deepcopy
from dataclasses import dataclass, field
import itertools
from pathlib import Path
from pprint import pformat

from beartype import beartype
from beartype.typing import Dict, List, Optional, Set, TypeAlias, Union
import graphviz as gv
import igraph as ig
from py_codegen.gen_tu_cpp import (
    GenTuEnum,
    GenTuFunction,
    GenTuStruct,
    GenTuTypedef,
    GenTuUnion,
    QualType,
    QualTypeKind,
)
from py_codegen.refl_read import ConvTu
from py_scriptutils.script_logging import log
from pydantic import BaseModel, Field


@beartype
def get_declared_types_rec(
    decl: GenTuUnion | ConvTu,
    expanded_use: bool = True,
) -> List[QualType]:
    result: List[QualType] = []

    def add(t: QualType) -> None:
        if expanded_use:
            result.extend(t.get_recursive_uses())

        else:
            result.append(t)

    match decl:
        case GenTuStruct():
            add(decl.name)

            for _nested in decl.nested:
                result.extend(
                    get_declared_types_rec(
                        _nested,  # type: ignore
                        expanded_use=expanded_use,
                    ))

        case GenTuTypedef():
            add(decl.name)

        case GenTuEnum():
            add(decl.name)

        case ConvTu():
            for it in decl.get_all():
                result.extend(get_declared_types_rec(
                    it,
                    expanded_use=expanded_use,
                ))

    return result


@beartype
def get_used_types_rec(
    decl: GenTuUnion | ConvTu,
    expanded_use: bool = True,
) -> List[QualType]:
    result: List[QualType] = []

    def add(t: QualType) -> None:
        if expanded_use:
            result.extend(t.get_recursive_uses())

        else:
            result.append(t)

    match decl:
        case GenTuStruct():
            for base in decl.bases:
                add(base)

            for _field in decl.fields:
                if _field.isTypeDecl:
                    result += get_used_types_rec(
                        _field.decl,  # type: ignore
                        expanded_use=expanded_use,
                    )

                else:
                    assert _field.type, _field
                    add(_field.type)

        case GenTuFunction():
            for arg in decl.arguments:
                assert arg.type, arg
                add(arg.type)

            assert decl.result, decl
            add(decl.result)

        case GenTuTypedef():
            assert decl.base, decl
            add(decl.base)

        case ConvTu():
            for it in decl.get_all():
                result.extend(get_used_types_rec(
                    it,
                    expanded_use=expanded_use,
                ))

        case GenTuEnum():
            pass

        case _:
            assert False, type(decl)

    return result


@beartype
def hash_qual_type(
    t: QualType,
    with_namespace: bool = False,
) -> int:
    """
    Generate a hashed value for qualified type, ignoring constant qualifiers,
    pointers and other elements. This function is primarily used to map
    declared entries to some simpler value for ID.
    """
    parts: List[str | int] = [hash(t.Kind)]
    match t.Kind:
        case QualTypeKind.FunctionPtr:
            assert t.func
            if t.func.ReturnTy:
                parts.append(
                    hash_qual_type(
                        t.func.ReturnTy,
                        with_namespace=with_namespace,
                    ))

            else:
                parts.append(0)

            for T in t.func.Args:
                parts.append(hash_qual_type(
                    T,
                    with_namespace=with_namespace,
                ))

        case QualTypeKind.Array:
            pass

        case QualTypeKind.RegularType:
            parts.append(hash(t.name))

            for space in t.Spaces:
                parts.append(hash_qual_type(
                    space,
                    with_namespace=with_namespace,
                ))

            for param in t.Parameters:
                parts.append(hash_qual_type(
                    param,
                    with_namespace=with_namespace,
                ))

    assert parts != [0], pformat(t)

    return hash(tuple(parts))


@beartype
class TranslationUnitLocations(BaseModel):
    """
    Information about external dependencies of a translation unit -- `Name` of the dependency
    library/package and the relative path inside of this library.
    """
    Name: str = Field(description="Name of the translation unit group", default="")
    Files: List[Path] = Field(
        description="Paths relative to the root directory of this translation unit group")


@beartype
class TranslationUnitInfo(BaseModel):
    """
    Helper information for the translation unit conversion, can be written
    alongside the generated files and translation unit JSON dumps, to simplify
    search for "who defines" and "what is imported" information.
    """
    Defines: List[QualType] = Field(
        description="List of types defined in the translation module",
        default_factory=list)
    Depends: List[TranslationUnitLocations] = Field(
        description="Dependencies on translation units from other external locations",
        default_factory=list)


@dataclass
class TuWrap:
    """
    Converted translation unit
    """
    name: str
    tu: ConvTu
    original: Path  ## Path of the original main file of the translation unit
    ## TODO move customization point further down the line, no need to keep it directly with collectr
    mapping: Path  ## Target generated mapping, constructed based during collector
    ## run.


@beartype
@dataclass
class GenGraph:
    """
    Graph structure constructed from the translation unit modules. Collection
    of translation units is added to the generation graph, rearranged to resolve
    internal links (mainly mutually recursive type usages) and a new list of subgraphs
    can then be converted to target language definitions.
    """

    @beartype
    @dataclass
    class Sub:
        """
        Single sugbraph containing an unordered series of definitions. At the
        start each translation unit gets its own subgraph, later on the subgraphs
        might be merged together if mutually recursive file imports are detected.
        """
        ## Name of the original translatuion unit
        name: str
        ## Full path of the path of the main translation unit file
        original: Path
        ## **Unordered** collection of definitions in the graph
        nodes: Set[int] = field(default_factory=set)

    id_to_entry: Dict[int, GenTuUnion] = field(default_factory=dict)

    ## Main directed graph holding all declarations and type usage links.
    graph: ig.Graph = field(default_factory=lambda: ig.Graph(directed=True))

    ## List of currently registered subgraphs
    subgraphs: List[Sub] = field(default_factory=list)
    ## Mapping from the hashed value of the type or procedure to the graph ID
    id_map: Dict[int, int] = field(default_factory=dict)

    def get_sub(self, _id: int) -> Optional[Sub]:
        """
        Find which subgraph definition belongs to. If No definition is found, return
        empty subgraph.
        """
        matching: List[GenGraph.Sub] = []
        for sub in self.subgraphs:
            if _id in sub.nodes:
                matching.append(sub)

        assert len(matching) <= 1, [
            f"{m.name}, {m.original}, id: {_id}, entry: {self.id_to_entry[_id].format()}"  # type: ignore
            for m in matching
        ]
        if len(matching) == 1:
            return matching[0]

        else:
            return None

    def get_declared_sub(self, typ: QualType) -> Optional[Sub]:
        """Get subgraph defining the qualified type"""
        _id = self.id_from_hash(hash_qual_type(typ))
        if not (typ.isPrimitive() or typ.isArray() or
                typ.isFunction()) and _id not in self.id_to_entry:
            log().warning(f"No known declaration of the [red]{typ.format()}[/red]")

        return self.get_sub(_id)

    def id_from_hash(self, hashed: int) -> int:
        if hashed not in self.id_map:
            self.id_map[hashed] = len(self.id_map)

        return self.id_map[hashed]

    def id_from_entry(self, entry: GenTuUnion, parent: Optional[QualType] = None) -> int:
        """Get ID from the entry declartion"""
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

    def use_type(self, _id: int, Type: QualType, dbg_from: str = "") -> None:
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

    def get_used_type(self, decl: GenTuUnion) -> List[QualType]:
        """
        Get list of types used in the declaration -- field types, arguments, return
        types, structure bases etc.
        """
        return get_used_types_rec(decl)

    def merge_structs(self, stored: GenTuStruct, added: GenTuStruct) -> None:
        stored_fields = set([f.name for f in stored.fields])
        for _field in added.fields:
            if _field.name not in stored_fields:
                stored.fields.append(deepcopy(_field))

        stored.IsForwardDecl = stored.IsForwardDecl and added.IsForwardDecl
        if stored.IsForwardDecl and not added.IsForwardDecl:
            stored.original = copy(added.original)

    def merge_enums(self, stored: GenTuEnum, added: GenTuEnum) -> None:
        pass

    def merge_functions(self, stored: GenTuFunction, added: GenTuFunction) -> None:
        pass

    def add_entry(self, entry: GenTuUnion, sub: Sub) -> int:
        """
        Register new entry in the graph or update existing registration.

        If the entry has already been added in a simpler form (formward declared in a different
        translation unit), then old declaration is removed and added the `sub` subgraph. If new
        declaration itself is a forward declaration then no entry addition will happen.

        If this is a completely new declaration/definition then new vertex will be added to the graph
        and a full deep copy of the entry will be stored into the `id_to_entry` field for
        future modifications and merges in case it is encountered through a different translation unit.
        """
        _id = self.id_from_entry(entry)
        if _id in self.id_to_entry:
            if isinstance(entry, GenTuStruct) or isinstance(entry, GenTuEnum):
                olddef: GenTuStruct | GenTuEnum = self.id_to_entry[_id]  # type: ignore
                if olddef.IsForwardDecl and not entry.IsForwardDecl:
                    # Previously added declaration was a forward declaration and it needs to be removed from
                    # all subgraphs since there is not a proper definition present in the graph
                    for old in self.subgraphs:
                        if _id in old.nodes:
                            old.nodes.discard(_id)

                    # New subgraph properly introduces type definition and it should contain
                    # the content instead.
                    sub.nodes.add(_id)
                    olddef.original = entry.original

                elif not olddef.IsForwardDecl and entry.IsForwardDecl:
                    # Newly introduced type is a forward declaration and should not be added to a new subgraph
                    pass

                elif olddef.IsForwardDecl and entry.IsForwardDecl:
                    # Haven't found proper forward declaration yet, new ones still don't need to be added to
                    # more graphs
                    pass

                elif not olddef.IsForwardDecl and not entry.IsForwardDecl:
                    log("refl.cli.read").error(
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

    def add_struct(self, struct: GenTuStruct, sub: Sub) -> None:
        _id = self.add_entry(struct, sub)

        merge: GenTuStruct = self.id_to_entry[_id]  # type: ignore
        self.merge_structs(merge, struct)

        self.graph.vs[_id]["label"] = struct.name.format()
        self.graph.vs[_id]["dbg_origin"] = struct.name.dbg_origin
        self.graph.vs[_id]["color"] = "green"

    def add_enum(self, enum: GenTuEnum, sub: Sub) -> None:
        _id = self.add_entry(enum, sub)

        merge: GenTuEnum = self.id_to_entry[_id]  # type: ignore
        self.merge_enums(merge, enum)

        self.graph.vs[_id]["label"] = enum.name.format()
        self.graph.vs[_id]["dbg_origin"] = enum.name.dbg_origin
        self.graph.vs[_id]["color"] = "red"

    def add_typedef(self, typedef: GenTuTypedef, sub: Sub) -> None:
        _id = self.add_entry(typedef, sub)
        merge = self.id_to_entry[_id]

        self.graph.vs[_id]["label"] = typedef.name.format()
        self.graph.vs[_id]["dbg_origin"] = typedef.name.dbg_origin
        self.graph.vs[_id]["color"] = "blue"

    def add_function(self, func: GenTuFunction, sub: Sub) -> None:
        _id = self.add_entry(func, sub)
        merge: GenTuFunction = self.id_to_entry[_id]  # type: ignore
        self.merge_functions(merge, func)

        self.graph.vs[_id]["label"] = func.format()
        self.graph.vs[_id]["color"] = "magenta"

    def add_unit(self, wrap: TuWrap) -> None:
        """Add all declarations from the converted translation unit"""
        sub = GenGraph.Sub(wrap.name, wrap.original)
        self.subgraphs.append(sub)
        for struct in wrap.tu.structs:
            self.add_struct(struct, sub)

        for enum in wrap.tu.enums:
            self.add_enum(enum, sub)

        for typedef in wrap.tu.typedefs:
            self.add_typedef(typedef, sub)

        for func in wrap.tu.functions:
            self.add_function(func, sub)

    def connect_usages(self) -> None:
        """
        Iterate overlall registered declarations in the graph and establish outgoing links
        from every node that uses some type -- functions, structures etc.

        Note: This method must be called after the graph is fully constructed, otherwise some
        dependencies might be missing becase target types could not be found. Additionally,
        the method links together declarations from the same subgraph, so it must be called
        before the connected file grouping.
        """
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

    def group_connected_files(self) -> None:
        """
        Find mutually recursive subgraphs and merge them into single blocks
        """
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
        def get_scc_indices(sub: GenGraph.Sub) -> set[int]:
            return {vertex_to_scc[v] for v in sub.nodes if v in vertex_to_scc}

        # Group vertex sets by their SCCs and directly pass subgraphs that are not
        # placed in any SCC -- those are standalone files, can be used on their own
        ungrouped_sets: List[GenGraph.Sub] = []
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
                log("refl.cli.read").info(
                    "Merging strongly connected files %s" % (", ".join([
                        f"[green]{g.original.name}[/green]" for g in group if g.original
                    ])))

        self.subgraphs = new_grouped + ungrouped_sets

    def to_decl_info(self, sub: Sub) -> TranslationUnitInfo:
        result = TranslationUnitInfo()

        for _id in sub.nodes:
            decl = self.id_to_entry[_id]
            match decl:
                case GenTuEnum(name=name) | GenTuStruct(name=name) | GenTuTypedef(
                    name=name):
                    result.Defines.append(name)

        return result

    def to_csv(self, node_file: str, edge_file: str) -> None:
        """
        Export an igraph graph to CSV files for nodes and edges.

        Args:
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
                    drop_builtin_types: bool = True) -> None:
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

        def rec_subgraph(target: gv.Graph, sub: GenGraph.Sub) -> None:
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
