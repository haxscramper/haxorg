from collections import defaultdict
from concurrent.futures import as_completed, ThreadPoolExecutor
from dataclasses import dataclass, field
from pathlib import Path

from beartype import beartype
from beartype.typing import Any, Dict, List, Optional, Tuple
import dominate
import dominate.tags
import dominate.util
import graphviz
import igraph
from py_ci.data_build import get_deps_install_config
from py_codegen.astbuilder_cpp import QualType, QualTypeKind
from py_codegen.gen_tu_cpp import GenTuInclude
import py_codegen.proto_lib.reflection_defs as pb
from py_codegen.refl_read import conv_proto_file, ConvTu
from py_codegen.refl_wrapper_graph import get_declared_types_rec, get_used_types_rec, hash_qual_type
from py_repository.code_analysis import gen_coverage_cookies
from py_repository.repo_tasks.command_execution import run_command, run_command_with_json_args
from py_repository.repo_tasks.common import ctx_write_text, ensure_existing_dir, get_build_root, get_script_root, get_workflow_out
from py_repository.repo_tasks.workflow_utils import TaskContext
from py_scriptutils.script_logging import log
from pydantic import BaseModel, Field

CAT = __name__


@beartype
@dataclass
class IncludeVertexData():
    name: str
    path: str
    isProjectFile: bool
    fileIncludes: List[GenTuInclude] = field(default_factory=list)
    declaredTypes: List[QualType] = field(default_factory=list)
    usedTypes: List[QualType] = field(default_factory=list)


@dataclass
@beartype
class ReflectionFile():
    tu: ConvTu
    declaredTypes: List[QualType] = field(default_factory=list)
    usedTypes: List[QualType] = field(default_factory=list)


@beartype
def create_include_graph(ctx: TaskContext,
                         translation_units: List[ReflectionFile]) -> igraph.Graph:
    g = igraph.Graph(directed=True)
    file_to_vertex = {}

    # Create a mapping from path to translation unit data
    path_to_tu: Dict[Path, ReflectionFile] = {}
    for tu in translation_units:
        if tu.tu.absoluteOriginal is None:
            continue
        tu_path = Path(tu.tu.absoluteOriginal).resolve()
        path_to_tu[tu_path] = tu

    for tu in translation_units:
        if tu.tu.absoluteOriginal is None:
            continue

        tu_path = Path(tu.tu.absoluteOriginal).resolve()

        @beartype
        def get_vertex_id_for_path(path: Path) -> igraph.Vertex:
            resolved = path.resolve()

            if resolved not in file_to_vertex:
                # Find the correct TU data for this specific path
                tu_data = path_to_tu.get(resolved)
                if tu_data is None:
                    # Handle case where we don't have TU data for this file --
                    # if the included file was outside of the project
                    declared_types = []
                    used_types = []
                else:
                    declared_types = tu_data.declaredTypes
                    used_types = tu_data.usedTypes

                icd = IncludeVertexData(
                    name=path.name,
                    path=str(path),
                    isProjectFile=path.is_relative_to(get_script_root(ctx)),
                    declaredTypes=declared_types,
                    usedTypes=used_types,
                )

                vertex_id = g.add_vertex(include_data=icd)
                file_to_vertex[resolved] = vertex_id

            return file_to_vertex[resolved]

        @beartype
        def get_vertex_data(path: Path) -> IncludeVertexData:
            vertex_id = get_vertex_id_for_path(path)
            return g.vs[vertex_id.index]["include_data"]

        get_vertex_data(tu_path).fileIncludes = tu.tu.includes

        for include in tu.tu.includes:
            if include.absolutePath is None or include.isSystem:
                continue

            include_path = Path(include.absolutePath).resolve()

            g.add_edge(
                get_vertex_id_for_path(include_path),
                get_vertex_id_for_path(tu_path),
            )

    return g


@beartype
def igraph_to_graphviz(
    graph: igraph.Graph,
    target: Optional[igraph.Vertex] = None,
) -> graphviz.Digraph:
    dot = graphviz.Digraph("includes")
    dot.attr("node", shape="plaintext")

    def get_transitive_incoming_count(vertex_index: int) -> int:
        reachable = graph.subcomponent(vertex_index, mode="in")
        return len(reachable) - 1

    def get_transitive_outgoing_count(vertex_index: int) -> int:
        reachable = graph.subcomponent(vertex_index, mode="out")
        return len(reachable) - 1

    for vertex in graph.vs:
        incd: IncludeVertexData = vertex["include_data"]

        if incd.isProjectFile:
            is_target = vertex == target
            doc = dominate.tags.table(
                border="1",
                cellborder="0",
                cellspacing="0",
                bgcolor="lightskyblue1" if is_target else "mistyrose",
            )

            with doc:
                with dominate.tags.tr():
                    dominate.tags.td(incd.name, colspan="2", align="center")
                with dominate.tags.tr():
                    dominate.tags.td("File Includes:")
                    dominate.tags.td(str(len(incd.fileIncludes)))
                with dominate.tags.tr():
                    dominate.tags.td("Direct Incoming:")
                    dominate.tags.td(str(vertex.indegree()))
                with dominate.tags.tr():
                    dominate.tags.td("Transitive Incoming:")
                    dominate.tags.td(str(get_transitive_incoming_count(vertex.index)))
                with dominate.tags.tr():
                    dominate.tags.td("Transitive Outgoing:")
                    dominate.tags.td(str(get_transitive_outgoing_count(vertex.index)))

                with dominate.tags.tr():
                    dominate.tags.td(
                        "Declared type:" if not target or is_target else "Used Types:")

                    with dominate.tags.td():
                        if target:
                            target_types = incd.declaredTypes if is_target else incd.usedTypes

                        else:
                            target_types = incd.declaredTypes

                        if target_types:
                            with dominate.tags.table(
                                    border="1",
                                    cellborder="0",
                                    cellspacing="0",
                            ):
                                for ty in target_types:
                                    type_name = ty.format_native(
                                        with_cvref=False,
                                        max_depth=1,
                                        max_params=4,
                                        max_param_size=12,
                                    )
                                    with dominate.tags.tr():
                                        dominate.tags.td(dominate.util.text(type_name))

            label = "<" + doc.render() + ">"
            dot.node(str(vertex.index), label=label)
        else:
            doc = dominate.tags.table(border="1", cellborder="0", cellspacing="0")
            with doc:
                with dominate.tags.tr():
                    dominate.tags.td(incd.name)

            label = "<" + doc.render() + ">"
            dot.node(str(vertex.index), label=label)

    for edge in graph.es:
        dot.edge(str(edge.source), str(edge.target), headport="n", tailport="s")

    return dot


@beartype
def process_reflection_file(
    ctx: TaskContext,
    file: Path,
    compile_commands: Path,
    header_commands: Path,
) -> Optional[Path]:
    relative = file.relative_to(get_script_root(ctx))
    out_file = get_build_root(ctx, f"{relative}_translation.pb")
    ensure_existing_dir(ctx, out_file.parent)

    refl_tool = get_build_root(ctx, "haxorg/reflection_tool")

    if out_file.exists() and file.stat().st_mtime <= out_file.stat(
    ).st_mtime and refl_tool.stat().st_mtime < out_file.stat().st_mtime:
        return out_file

    cmd_code, cmd_stdout, cmd_stderr = run_command_with_json_args(
        ctx,
        refl_tool,
        gen_coverage_cookies.ReflectionCLI(
            input=[str(file)],
            output=str(out_file),
            mode=gen_coverage_cookies.Mode.AllMainSymbolsInCompilationDb,
            reflection=gen_coverage_cookies.ReflectionConfig(
                compilation_database=str(header_commands.resolve())),
        ).model_dump(),
        capture=True,
        allow_fail=True,
    )

    out_stderr_path = out_file.with_suffix(".stderr.log")
    out_stdout_path = out_file.with_suffix(".stdout.log")

    out_stderr_path.write_text(cmd_stderr)
    out_stdout_path.write_text(cmd_stdout)

    if "Compile command not found" in cmd_stderr:
        return None
    elif cmd_code != 0:
        if cmd_stdout:
            log(CAT).info(f"Execution failed, wrote stdout to {out_stdout_path}")
        if cmd_stderr:
            log(CAT).error(f"Execution failed, wroute stderr to {out_stderr_path}")
        return None
    else:
        assert out_file.exists(), f"{relative}"
        return out_file


@beartype
def remove_redundant_edges(igraph_tus: igraph.Graph) -> igraph.Graph:
    edges_to_remove = []

    for edge in igraph_tus.es:
        source = edge.source
        target = edge.target

        paths = igraph_tus.get_all_simple_paths(source, target, cutoff=len(igraph_tus.vs))

        for path in paths:
            if len(path) > 2:
                edges_to_remove.append(edge.index)
                break

    igraph_tus.delete_edges(edges_to_remove)
    return igraph_tus


@beartype
def _types_match(type1: QualType, type2: QualType, verbose: bool = False) -> bool:
    if verbose:
        log(CAT).debug(
            f"MATCH {type1.format_native(False)} <> {type2.format_native(False)}")

    if type1.Kind != type2.Kind:
        if verbose:
            log(CAT).debug(f"  {type1.Kind} != {type2.Kind}")
        return False

    match type1.Kind:
        case QualTypeKind.RegularType:
            if type1.name != type2.name:
                if verbose:
                    log(CAT).debug(f"  {type1.name} != {type2.name}")

                return False

            if len(type1.Spaces) != len(type2.Spaces):
                if verbose:
                    log(CAT).debug(
                        f"  Spaces len mismatch {len(type1.Spaces)} != {len(type2.Spaces)}"
                    )

                return False

            if any(not _types_match(s1, s2)
                   for s1, s2 in zip(type1.Spaces, type2.Spaces)):
                return False

            return True

        case _:
            return False


@beartype
def _is_type_declared_in_target(
    qual_type: QualType,
    target_declared_types: List[QualType],
    verbose: bool = False,
) -> bool:
    for target_type in target_declared_types:
        if _types_match(qual_type, target_type, verbose=verbose):
            return True

    for param in qual_type.Parameters:
        if _is_type_declared_in_target(param, target_declared_types, verbose=verbose):
            return True

    for space in qual_type.Spaces:
        if _is_type_declared_in_target(space, target_declared_types, verbose=verbose):
            return True

    return False


@beartype
def create_project_file_subgraphs(
        graph: igraph.Graph) -> List[Tuple[igraph.Graph, igraph.Vertex]]:
    result: List[Tuple[igraph.Graph, igraph.Vertex]] = []

    for vertex in graph.vs:
        incd: IncludeVertexData = vertex["include_data"]
        if incd.isProjectFile:
            reachable_from = set(graph.subcomponent(vertex.index, mode="in"))
            reachable_to = set(graph.subcomponent(vertex.index, mode="out"))
            all_reachable = reachable_from.union(reachable_to)

            subgraph = graph.subgraph(list(all_reachable)).copy()

            target_vertex_index = None
            for v in subgraph.vs:
                if v["include_data"].path == incd.path:
                    target_vertex_index = v.index
                    break

            target_declared_types = incd.declaredTypes or []

            outgoing_vertices = set()
            for edge in graph.es.select(_source=vertex.index):
                outgoing_vertices.add(edge.target)

            for v in subgraph.vs:
                original_data: IncludeVertexData = v["include_data"]

                if v.index == target_vertex_index:
                    new_data = IncludeVertexData(
                        name=original_data.name,
                        path=original_data.path,
                        isProjectFile=original_data.isProjectFile,
                        fileIncludes=original_data.fileIncludes,
                        declaredTypes=original_data.declaredTypes,
                        usedTypes=original_data.usedTypes,
                    )

                else:
                    original_vertex_index = None
                    for orig_v in graph.vs:
                        if orig_v["include_data"].path == original_data.path:
                            original_vertex_index = orig_v.index
                            break

                    filtered_declared_types = list()
                    filtered_used_types = list()

                    if original_vertex_index in outgoing_vertices:
                        filtered_declared_types = original_data.declaredTypes
                        if original_data.usedTypes:
                            dbg_t = False  # incd.path.endswith("/Set.hpp")
                            for qt in original_data.usedTypes:
                                decl_check = _is_type_declared_in_target(
                                    qt,
                                    target_declared_types,
                                    verbose=dbg_t,
                                )

                                if decl_check:
                                    filtered_used_types.append(qt)

                    else:
                        filtered_declared_types = list()
                        filtered_used_types = list()

                    new_data = IncludeVertexData(
                        name=original_data.name,
                        path=original_data.path,
                        isProjectFile=original_data.isProjectFile,
                        fileIncludes=original_data.fileIncludes,
                        declaredTypes=filtered_declared_types,
                        usedTypes=filtered_used_types,
                    )

                v["include_data"] = new_data

            result.append((subgraph, subgraph.vs[target_vertex_index]))

    return result


class TraceEvent(BaseModel, extra="forbid"):
    pid: int = 0
    tid: int = 0
    ph: str = ""
    ts: int = 0
    dur: int = 0
    name: str = ""
    cat: Optional[str] = None
    args: Dict[str, Any] = Field(default_factory=dict)


class TraceEventNode(BaseModel, extra="forbid"):
    event: TraceEvent
    children: List["TraceEventNode"]


class TraceFile(BaseModel, extra="forbid"):
    traceEvents: List[TraceEvent] = field(default_factory=list)
    tree: Optional[TraceEventNode] = None
    path: str = ""
    beginningOfTime: int = 0


@beartype
def gen_include_graph(
    ctx: TaskContext,
    compile_commands: Path,
    header_commands: Path,
) -> None:
    header_compdb_content = run_command(
        ctx,
        "uv",
        [
            "run",
            "compdb",
            "-p",
            compile_commands.parent,
            "list",
        ],
        capture=True,
    )

    ctx_write_text(ctx, header_commands, header_compdb_content[1])
    log(CAT).info(f"Wrote extended compilation database to {header_commands}")

    ok_files: List[Path] = []
    files = list(get_script_root(ctx, "src").rglob("*.?pp"))

    # files = files[:10]

    with ThreadPoolExecutor(max_workers=6) as executor:
        futures = [
            executor.submit(process_reflection_file, ctx, file, compile_commands,
                            header_commands) for file in files
        ]

        for future in as_completed(futures):
            result = future.result()
            if result is not None:
                ok_files.append(result)

    conv_tus: List[ReflectionFile] = []

    for f in ok_files:
        tu = conv_proto_file(f)
        tu_unit = pb.TU.FromString(f.read_bytes())
        tu_json = f.with_suffix(".json")
        tu_json.write_text(tu_unit.to_json(indent=2))
        if tu.absoluteOriginal.endswith("hpp"):
            used_types: List[QualType] = list()
            used_types_set = set()
            for t in get_used_types_rec(tu, expanded_use=False):
                thash = hash_qual_type(t, with_namespace=True)
                if thash in used_types_set:
                    continue
                else:
                    used_types_set.add(thash)

                if "describe" not in t.flatQualName():
                    used_types.append(t)

            declared_types = get_declared_types_rec(
                tu,
                expanded_use=False,
            )

            conv_tus.append(
                ReflectionFile(
                    tu=tu,
                    declaredTypes=declared_types,
                    usedTypes=used_types,
                ))

    igraph_tus = create_include_graph(ctx, conv_tus)

    graphviz_tus = igraph_to_graphviz(igraph_tus)
    graphviz_file = get_workflow_out(ctx,
                                     "include_graph/include_graph.png").with_suffix("")
    graphviz_tus.render(graphviz_file, format="png")
    log(CAT).info(f"Final grouped graph {graphviz_file}.png")

    def generate_transitive_subgraph(suffix: str) -> None:
        for subgraph, sub_vertex in create_project_file_subgraphs(igraph_tus):
            incd: IncludeVertexData = subgraph.vs[sub_vertex.index]["include_data"]
            sub_file = Path(
                str(
                    get_workflow_out(
                        ctx, f"include_graph/individual_include_graphs/{incd.name}").
                    with_suffix("")) + suffix)

            log(CAT).info(f"Partial group graph in {sub_file}")
            ensure_existing_dir(ctx, sub_file.parent)
            igraph_to_graphviz(subgraph, target=sub_vertex).render(sub_file, format="png")

    # generate_transitive_subgraph("_base")
    igraph_tus = remove_redundant_edges(igraph_tus)
    generate_transitive_subgraph("_reduced")
