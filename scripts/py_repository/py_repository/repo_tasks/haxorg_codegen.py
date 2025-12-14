from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor, as_completed
from dataclasses import dataclass, field
import itertools
from pathlib import Path

from beartype import beartype
from beartype.typing import List, Optional, Any, Tuple, Dict
import igraph
from py_ci.data_build import get_deps_install_config
from py_codegen.astbuilder_cpp import QualType
from py_codegen.gen_tu_cpp import GenTuInclude
from py_codegen.refl_read import ConvTu, conv_proto_file
from py_codegen.refl_wrapper_graph import get_declared_types_rec, get_used_types_rec, hash_qual_type
from py_repository.repo_tasks.config import HaxorgLogLevel
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.common import check_is_file, ensure_existing_dir, get_build_root, get_log_dir, get_script_root
from py_repository.repo_tasks.haxorg_base import get_deps_install_dir, symlink_build
from py_repository.repo_tasks.haxorg_build import build_haxorg, configure_cmake_haxorg
from py_scriptutils.script_logging import log
import py_codegen.proto_lib.reflection_tool.reflection_defs as pb
import dominate
import graphviz
import dominate.tags
import dominate.util
from pydantic import BaseModel, Field
import statistics

CAT = __name__


@haxorg_task(dependencies=[symlink_build])
def generate_python_protobuf_files(ctx: TaskContext) -> None:
    """Generate new python code from the protobuf reflection files"""
    proto_config = get_script_root(
        ctx, "scripts/cxx_codegen/reflection_tool/reflection_defs.proto")

    _, stdout, _ = run_command(ctx, "poetry", ["env", "info", "--path"], capture=True)
    stdout = stdout.strip()
    log(CAT).info(f"Using protoc plugin path '{stdout}'")
    protoc_plugin = Path(stdout).joinpath("bin/protoc-gen-python_betterproto")

    log(CAT).debug(f"Has docker container? {ctx.docker_container}")
    if not check_is_file(ctx, protoc_plugin):
        raise RuntimeError(
            f"Protoc plugin for better python is not installed correctly, {protoc_plugin} does not exist"
        )

    proto_lib = get_script_root(ctx, "scripts/py_codegen/py_codegen/proto_lib")

    ensure_existing_dir(ctx, proto_lib)

    run_command(
        ctx,
        get_deps_install_dir(ctx).joinpath("protobuf/bin/protoc"),
        [
            f"--plugin={protoc_plugin}",
            "-I",
            get_script_root(ctx, "scripts/cxx_codegen"),
            "--proto_path=" +
            str(get_script_root(ctx, "scripts/py_codegen/py_codegen/reflection_tool")),
            "--python_betterproto_out=" + str(proto_lib),
            proto_config,
        ],
        env=dict(LD_PRELOAD=""),
    )


CODEGEN_TASKS = [
    "adaptagrams",
    "pyhaxorg",
]


@haxorg_task(dependencies=[generate_python_protobuf_files])
def generate_reflection_snapshot(ctx: TaskContext) -> None:
    """Generate new source code reflection file for the python source code wrapper"""
    compile_commands = get_script_root(ctx, "build/haxorg/compile_commands.json")
    toolchain_include = get_script_root(
        ctx, f"toolchain/llvm/lib/clang/{ctx.config.LLVM_MAJOR}/include")

    conf_copy = ctx.config.model_copy(deep=True)
    conf_copy.build_conf.target = ["reflection_lib", "reflection_tool"]
    conf_copy.build_conf.force = True
    build_haxorg(ctx=ctx.with_temp_config(conf_copy))

    for task in CODEGEN_TASKS:
        out_file = get_build_root(ctx, f"{task}.pb")
        match task:
            case "pyhaxorg":
                src_file = get_script_root(
                    ctx, "src/py_libs/pyhaxorg/pyhaxorg_manual_refl.cpp")

            case "adaptagrams":
                src_file = get_script_root(
                    ctx, "src/py_libs/py_adaptagrams/adaptagrams_ir_refl_target.cpp")

        run_command(
            ctx,
            get_build_root(ctx,
                           "haxorg/scripts/cxx_codegen/reflection_tool/reflection_tool"),
            [
                "-p",
                compile_commands,
                "--compilation-database",
                compile_commands,
                "--toolchain-include",
                toolchain_include,
                *(["--verbose"]
                  if ctx.config.log_level == HaxorgLogLevel.VERBOSE else []),
                "--out",
                out_file,
                src_file,
            ],
        )

        log(CAT).info("Updated reflection")


# TODO Make compiled reflection generation build optional
@haxorg_task()
def generate_haxorg_sources(ctx: TaskContext) -> None:
    """Update auto-generated source files"""
    assert not ctx.config.emscripten.build, "Codegen is not supported for the EMCC build"

    # TODO source file generation should optionally overwrite the target OR
    # compare the new and old source code (to avoid breaking the subsequent
    # compilation of the source)
    if not ctx.config.generate_sources_conf.standalone:
        config_copy = ctx.config.model_copy(deep=True)
        config_copy.build_conf.target = ["py_textlayout_cpp"]
        ctx_copy = ctx.with_temp_config(config_copy)
        ctx_copy.run(build_haxorg, ctx=ctx_copy)
        ctx_copy.run(generate_reflection_snapshot, ctx=ctx_copy)
        ctx_copy.run(symlink_build, ctx=ctx_copy)

    for task in CODEGEN_TASKS:
        run_command(
            ctx,
            "poetry",
            [
                "run",
                get_script_root(ctx, "scripts/py_codegen/py_codegen/codegen.py"),
                "--reflection_path={}".format(get_build_root(ctx).joinpath(f"{task}.pb")),
                f"--codegen_task={task}",
                f"--tmp={ctx.config.generate_sources_conf.tmp}",
            ],
            # env=get_py_env(),
        )

        log(CAT).info("Updated code definitions")


@haxorg_task()
def merge_build_times(ctx: TaskContext) -> None:
    out_merge = TraceFile()

    for file in itertools.chain(
            get_build_root(ctx, "haxorg/src/haxorg/CMakeFiles/").rglob("*.cpp.json"),
            get_build_root(ctx, "haxorg/").rglob("*.time-trace"),
    ):
        log(CAT).debug(file)
        read_file = TraceFile.model_validate_json(file.read_text())
        read_file.path = str(file)

        file_stem = Path(file).stem

        for event in read_file.traceEvents:
            if event.ph == "M" and event.name == "process_name" and "name" in event.args:
                event.args["name"] = f"{event.args['name']} {file_stem}"

        out_merge.traceEvents.extend(read_file.traceEvents)

    get_build_root(ctx, "haxorg/full-profile-merge.json").write_text(
        out_merge.model_dump_json(indent=2))


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
    toolchain_include: Path,
) -> Optional[Path]:
    relative = file.relative_to(get_script_root(ctx))
    out_file = get_build_root(ctx, f"{relative}_translation.pb")
    log(CAT).info(f"Analysing TU for {relative}")

    ensure_existing_dir(ctx, out_file.parent)

    if out_file.exists() and file.stat().st_mtime <= out_file.stat().st_mtime:
        log(CAT).info("TU file already exists")
        return out_file

    else:
        return None

    cmd_code, cmd_stdout, cmd_stderr = run_command(
        ctx,
        get_build_root(ctx, "haxorg/scripts/cxx_codegen/reflection_tool/reflection_tool"),
        [
            "-p",
            compile_commands.resolve(),
            "--compilation-database",
            header_commands.resolve(),
            "--toolchain-include",
            toolchain_include.resolve(),
            "--main-tu-analysis",
            "--verbose",
            "--out",
            out_file,
            file,
        ],
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
def _is_type_declared_in_target(qual_type: QualType,
                                target_declared_types: List[QualType]) -> bool:
    for target_type in target_declared_types:
        if _types_match(qual_type, target_type):
            return True

    for param in qual_type.Parameters:
        if _is_type_declared_in_target(param, target_declared_types):
            return True

    for space in qual_type.Spaces:
        if _is_type_declared_in_target(space, target_declared_types):
            return True

    return False


@beartype
def _types_match(type1: QualType, type2: QualType) -> bool:
    return (type1.name == type2.name and type1.Spaces == type2.Spaces and
            type1.isNamespace == type2.isNamespace)


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
                            for qt in original_data.usedTypes:
                                if _is_type_declared_in_target(qt, target_declared_types):
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


@haxorg_task(dependencies=[generate_python_protobuf_files])
def generate_full_code_reflection(ctx: TaskContext) -> None:
    """Generate new source code reflection file for the python source code wrapper"""
    compile_commands = get_script_root(ctx, "build/haxorg/compile_commands.json")
    header_commands = get_script_root(ctx,
                                      "build/haxorg/compile_commands_with_headers.json")
    toolchain_include = get_script_root(
        ctx, f"toolchain/llvm/lib/clang/{ctx.config.LLVM_MAJOR}/include")

    # re-configure the whole project to generate new compilation database.
    configure_cmake_haxorg(ctx=ctx)

    conf_copy = ctx.config.model_copy(deep=True)
    conf_copy.build_conf.target = ["reflection_lib", "reflection_tool"]
    conf_copy.build_conf.force = True
    build_haxorg(ctx=ctx.with_temp_config(conf_copy))

    header_compdb_content = run_command(
        ctx,
        "compdb",
        [
            "-p",
            compile_commands.parent,
            "list",
        ],
        capture=True,
    )

    header_commands.write_text(header_compdb_content[1])
    log(CAT).info(f"Wrote extended compilation database to {header_commands}")

    ok_files: List[Path] = []
    files = list(get_script_root(ctx, "src").rglob("*.?pp"))

    # files = files[:10]

    with ThreadPoolExecutor(max_workers=6) as executor:
        futures = [
            executor.submit(process_reflection_file, ctx, file, compile_commands,
                            header_commands, toolchain_include) for file in files
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
        log(CAT).debug(f"tu_json debug {tu_json}")
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
    graphviz_file = get_build_root(ctx, "reflect/include_graph.png").with_suffix("")
    graphviz_tus.render(graphviz_file, format="png")
    log(CAT).info(f"Final grouped graph {graphviz_file}.png")

    def generate_transitive_subgraph(suffix: str) -> None:
        for subgraph, sub_vertex in create_project_file_subgraphs(igraph_tus):
            incd: IncludeVertexData = subgraph.vs[sub_vertex.index]["include_data"]
            sub_file = Path(
                str(
                    get_build_root(ctx, f"reflect/individual_include_graphs/{incd.name}").
                    with_suffix("")) + suffix)

            ensure_existing_dir(ctx, sub_file.parent)
            igraph_to_graphviz(subgraph, target=sub_vertex).render(sub_file, format="png")

    # generate_transitive_subgraph("_base")
    igraph_tus = remove_redundant_edges(igraph_tus)
    generate_transitive_subgraph("_reduced")
