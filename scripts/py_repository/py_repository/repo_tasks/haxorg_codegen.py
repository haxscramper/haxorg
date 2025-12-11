from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor, as_completed
from dataclasses import dataclass, field
import itertools
from pathlib import Path

from beartype import beartype
from beartype.typing import List, Optional, Any, Tuple, Dict
import igraph
from py_ci.data_build import get_deps_install_config
from py_codegen.gen_tu_cpp import GenTuInclude
from py_codegen.refl_read import ConvTu, conv_proto_file
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
    averageSourceTime: Optional[float] = None


@beartype
def create_include_graph(
    ctx: TaskContext,
    translation_units: List[ConvTu],
    source_averages: defaultdict[Path, List[int]],
) -> igraph.Graph:
    g = igraph.Graph(directed=True)

    file_to_vertex = {}

    for tu in translation_units:
        if tu.absoluteOriginal is None:
            continue

        tu_path = Path(tu.absoluteOriginal).resolve()

        @beartype
        def get_vertex_id_for_path(path: Path) -> igraph.Vertex:
            resolved = path.resolve()

            if resolved not in file_to_vertex:
                icd = IncludeVertexData(
                    name=path.name,
                    path=str(path),
                    isProjectFile=path.is_relative_to(get_script_root(ctx)),
                )

                if resolved in source_averages:
                    icd.averageSourceTime = statistics.mean(source_averages[resolved])

                vertex_id = g.add_vertex(include_data=icd)

                file_to_vertex[resolved] = vertex_id

            return file_to_vertex[resolved]

        @beartype
        def get_vertex_data(path: Path) -> IncludeVertexData:
            vertex_id = get_vertex_id_for_path(path)
            return g.vs[vertex_id.index]["include_data"]

        get_vertex_data(tu_path).fileIncludes = tu.includes

        for include in tu.includes:
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
            doc = dominate.tags.table(
                border="1",
                cellborder="0",
                cellspacing="0",
                bgcolor="lightskyblue1" if vertex == target else "mistyrose",
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

                if incd.averageSourceTime:
                    with dominate.tags.tr():
                        dominate.tags.td("Average source:")
                        dominate.tags.td(f"{incd.averageSourceTime/1E3:.3f}")

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

    cmd_code, cmd_stdout, cmd_stderr = run_command(
        ctx,
        get_build_root(ctx, "haxorg/scripts/cxx_codegen/reflection_tool/reflection_tool"),
        [
            "-p",
            compile_commands,
            "--compilation-database",
            header_commands,
            "--toolchain-include",
            toolchain_include,
            "--main-tu-analysis",
            *(["--verbose"] if ctx.config.log_level == HaxorgLogLevel.VERBOSE else []),
            "--out",
            out_file,
            file,
        ],
        capture=True,
        allow_fail=True,
    )

    if "Compile command not found" in cmd_stderr:
        return None
    elif cmd_code != 0:
        log(CAT).info(cmd_stdout)
        log(CAT).error(cmd_stderr)
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
def create_project_file_subgraphs(
        graph: igraph.Graph) -> List[Tuple[igraph.Graph, igraph.Vertex]]:
    result: List[Tuple[igraph.Graph, igraph.Vertex]] = []

    for vertex in graph.vs:
        incd: IncludeVertexData = vertex["include_data"]

        if incd.isProjectFile:
            reachable_from = set(graph.subcomponent(vertex.index, mode="in"))
            reachable_to = set(graph.subcomponent(vertex.index, mode="out"))
            all_reachable = reachable_from.union(reachable_to)

            subgraph = graph.subgraph(list(all_reachable))

            new_vertex_index = None
            for v in subgraph.vs:
                if v["include_data"].path == incd.path:
                    new_vertex_index = v.index
                    break

            result.append((subgraph, subgraph.vs[new_vertex_index]))

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

    with ThreadPoolExecutor(max_workers=6) as executor:
        futures = [
            executor.submit(process_reflection_file, ctx, file, compile_commands,
                            header_commands, toolchain_include) for file in files
        ]

        for future in as_completed(futures):
            result = future.result()
            if result is not None:
                ok_files.append(result)

    conv_tus = []

    for f in ok_files:
        tu = conv_proto_file(f)
        tu_unit = pb.TU.FromString(f.read_bytes())
        tu_json = f.with_suffix(".json")
        tu_json.write_text(tu_unit.to_json(indent=2))
        log(CAT).debug(f"tu_json debug {tu_json}")
        if tu.absoluteOriginal.endswith("hpp"):
            conv_tus.append(tu)

    igraph_tus = create_include_graph(ctx, conv_tus)

    def generate_transitive_subgraph(suffix: str) -> None:
        for subgraph, sub_vertex in create_project_file_subgraphs(igraph_tus):
            incd: IncludeVertexData = subgraph.vs[sub_vertex.index]["include_data"]
            sub_file = Path(
                str(
                    get_build_root(ctx, f"reflect/individual_include_graphs/{incd.name}").
                    with_suffix("")) + suffix)

            ensure_existing_dir(ctx, sub_file.parent)
            log(CAT).info(f"sub_file.{suffix} = {sub_file}.png")
            igraph_to_graphviz(subgraph, target=sub_vertex).render(sub_file, format="png")

    # generate_transitive_subgraph("_base")
    igraph_tus = remove_redundant_edges(igraph_tus)
    generate_transitive_subgraph("_reduced")

    graphviz_tus = igraph_to_graphviz(igraph_tus)
    graphviz_file = get_build_root(ctx, "reflect/include_graph.png").with_suffix("")
    graphviz_tus.render(graphviz_file, format="png")
    log(CAT).info(f"Final grouped graph {graphviz_file}.png")
