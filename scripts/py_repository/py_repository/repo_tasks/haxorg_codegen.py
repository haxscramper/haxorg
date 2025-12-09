from pathlib import Path

from beartype import beartype
from beartype.typing import List, Optional
import igraph
from py_ci.data_build import get_deps_install_config
from py_codegen.refl_read import ConvTu, conv_proto_file
from py_repository.repo_tasks.config import HaxorgLogLevel
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.common import check_is_file, ensure_existing_dir, get_build_root, get_log_dir, get_script_root
from py_repository.repo_tasks.haxorg_base import get_deps_install_dir, symlink_build
from py_repository.repo_tasks.haxorg_build import build_haxorg
from py_scriptutils.script_logging import log

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


@beartype
def create_include_graph(translation_units: List[ConvTu],
                         filter_directory: Optional[str] = None) -> igraph.Graph:
    g = igraph.Graph(directed=True)

    file_to_vertex = {}

    for tu in translation_units:
        if tu.absoluteOriginal is None:
            continue

        tu_path = Path(tu.absoluteOriginal).resolve()

        if filter_directory is not None:
            if not str(tu_path).startswith(filter_directory):
                continue

        if tu.absoluteOriginal not in file_to_vertex:
            vertex_id = g.add_vertex(name=tu.absoluteOriginal, path=str(tu_path))
            file_to_vertex[tu.absoluteOriginal] = vertex_id

        for include in tu.includes:
            if include.absolutePath is None or include.isSystem:
                continue

            include_path = Path(include.absolutePath).resolve()

            if filter_directory is not None:
                if not str(include_path).startswith(filter_directory):
                    continue

            if include.absolutePath not in file_to_vertex:
                vertex_id = g.add_vertex(name=include.absolutePath,
                                         path=str(include_path))
                file_to_vertex[include.absolutePath] = vertex_id

            g.add_edge(file_to_vertex[tu.absoluteOriginal],
                       file_to_vertex[include.absolutePath])

    return g


@beartype
def igraph_to_graphviz(graph: igraph.Graph) -> str:
    lines = ["digraph includes {"]

    for vertex in graph.vs:
        vertex_name = Path(vertex["name"]).name
        lines.append(f'  "{vertex.index}" [label="{vertex_name}"];')

    for edge in graph.es:
        lines.append(f'  "{edge.source}" -> "{edge.target}";')

    lines.append("}")

    return "\n".join(lines)


@haxorg_task(dependencies=[generate_python_protobuf_files])
def generate_full_code_reflection(ctx: TaskContext) -> None:
    """Generate new source code reflection file for the python source code wrapper"""
    compile_commands = get_script_root(ctx, "build/haxorg/compile_commands.json")
    toolchain_include = get_script_root(
        ctx, f"toolchain/llvm/lib/clang/{ctx.config.LLVM_MAJOR}/include")

    conf_copy = ctx.config.model_copy(deep=True)
    conf_copy.build_conf.target = ["reflection_lib", "reflection_tool"]
    conf_copy.build_conf.force = True
    build_haxorg(ctx=ctx.with_temp_config(conf_copy))
    ok_files: List[Path] = []

    for file in get_script_root(ctx, "src").rglob("*.cpp"):
        out_file = get_build_root(ctx, f"{file}_translation.pb")
        log(CAT).info(f"Analysing TU for {file}")
        if out_file.exists() and file.stat().st_mtime <= out_file.stat().st_mtime:
            log(CAT).info("TU file already exists")
            ok_files.append(out_file)
            continue

        continue

        cmd_code, cmd_stdout, cmd_stderr = run_command(
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
                "--main-tu-analysis",
                *(["--verbose"]
                  if ctx.config.log_level == HaxorgLogLevel.VERBOSE else []),
                "--out",
                out_file,
                file,
            ],
            capture=True,
            allow_fail=True,
        )

        if "Compile command not found" in cmd_stderr:
            continue

        elif cmd_code != 0:
            log(CAT).info(cmd_stdout)
            log(CAT).error(cmd_stderr)
            # raise RuntimeError("Failed to execute")

        else:
            ok_files.append(out_file)

    conv_tus = [conv_proto_file(f) for f in ok_files]
    igraph_tus = create_include_graph(conv_tus,
                                    #   filter_directory=str(get_script_root(ctx))
                                      )
    for tu in conv_tus:
        log(CAT).info(f"{tu.absoluteOriginal} includes size {len(tu.includes)}")
        for inc in tu.includes:
            log(CAT).info(f"  {inc.absolutePath}")

    graphviz_tus = igraph_to_graphviz(igraph_tus)
    Path("/tmp/result.dot").write_text(graphviz_tus)
