import itertools
from pathlib import Path
import sys

import igraph as ig
import py_repository.code_analysis.gen_coverage_cookies as cov
from py_repository.repo_tasks.command_execution import (
    get_python_binary,
    run_command,
    run_command_with_json_args,
)
from py_repository.repo_tasks.common import (
    check_is_file,
    ensure_existing_dir,
    get_build_root,
    get_script_root,
    get_workflow_out,
)
from py_repository.repo_tasks.config import get_tmpdir, HaxorgLogLevel
from py_repository.repo_tasks.haxorg_base import get_deps_install_dir, symlink_build
from py_repository.repo_tasks.haxorg_build import (
    build_and_setup_text_layout_lib,
    build_haxorg,
    build_targets,
    configure_cmake_haxorg,
)

import json
from pathlib import Path
from dataclasses import fields
import betterproto
import typing

from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_scriptutils.script_logging import log

CAT = __name__


def betterproto_to_jsonschema(msg_class, defs=None):
    if defs is None:
        defs = {}

    class_name = msg_class.__name__
    if class_name in defs:
        return {"$ref": f"#/$defs/{class_name}"}

    defs[class_name] = {}
    properties = {}

    resolved_hints = typing.get_type_hints(msg_class)

    for f in fields(msg_class):
        if f.name.startswith("_"):
            continue

        resolved_type = resolved_hints.get(f.name, f.type)
        prop = _field_to_schema(resolved_type, defs)
        if prop is not None:
            properties[f.name] = prop

    schema = {"type": "object", "properties": properties}
    defs[class_name] = schema
    return {"$ref": f"#/$defs/{class_name}"}


def _field_to_schema(tp, defs):
    origin = typing.get_origin(tp)
    args = typing.get_args(tp)

    if origin is list:
        inner = args[0] if args else str
        return {"type": "array", "items": _type_to_schema(inner, defs)}

    if origin is typing.Optional or origin is typing.Union:
        # Optional[X] is Union[X, None]
        non_none = [a for a in args if a is not type(None)]
        if non_none:
            return _type_to_schema(non_none[0], defs)

    return _type_to_schema(tp, defs)


def _type_to_schema(tp, defs):
    if tp is bool:
        return {"type": "boolean"}
    if tp is int:
        return {"type": "integer"}
    if tp is float:
        return {"type": "number"}
    if tp is str:
        return {"type": "string"}
    if tp is bytes:
        return {"type": "string", "contentEncoding": "base64"}

    try:
        if isinstance(tp, type) and issubclass(tp, betterproto.Enum):
            return {"type": "string", "enum": [e.name for e in tp]}
    except TypeError:
        pass

    try:
        if isinstance(tp, type) and issubclass(tp, betterproto.Message):
            return betterproto_to_jsonschema(tp, defs)
    except TypeError:
        pass

    return {}


def _generate_schema(msg_class) -> dict:
    defs = {}
    root = betterproto_to_jsonschema(msg_class, defs)
    return {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        **root,
        "$defs": defs,
    }


def _write_schema(msg_class, output_path: Path):
    schema = _generate_schema(msg_class)
    output_path.write_text(json.dumps(schema, indent=2))


@haxorg_task(dependencies=[symlink_build])
def generate_python_protobuf_files(ctx: TaskContext) -> None:
    """Generate new python code from the protobuf reflection files"""
    proto_config = get_script_root(ctx, "scripts/cxx_codegen/reflection_defs.proto")
    python_path = str(get_python_binary(ctx)).replace("/bin/python", "")
    log(CAT).info(f"Using protoc plugin path '{python_path}'")
    protoc_plugin = Path(python_path).joinpath("bin/protoc-gen-python_betterproto")

    if not check_is_file(ctx, protoc_plugin):
        raise RuntimeError(
            f"Protoc plugin for better python is not installed correctly, {protoc_plugin} does not exist"
        )

    proto_lib = get_script_root(ctx, "scripts/py_codegen/py_codegen/proto_lib")

    ensure_existing_dir(ctx, proto_lib)

    protoc_bin = get_deps_install_dir(ctx).joinpath("protobuf/bin/protoc")
    proto_include_dir = get_script_root(ctx, "scripts/cxx_codegen")
    proto_path = get_script_root(ctx, "scripts/py_codegen/py_codegen/reflection_tool")

    run_command(
        ctx,
        protoc_bin,
        [
            f"--plugin={protoc_plugin}",
            "-I",
            proto_include_dir,
            "--proto_path=" + str(proto_path),
            "--python_betterproto_out=" + str(proto_lib),
            proto_config,
        ],
        env=dict(LD_PRELOAD=""),
    )

    from py_codegen.proto_lib.reflection_defs import TU
    ensure_existing_dir(ctx, proto_lib)
    _write_schema(TU, proto_lib / "TU.schema.json")


CODEGEN_TASKS = [
    "adaptagrams",
    "pyhaxorg",
]


@haxorg_task(
    dependencies=[generate_python_protobuf_files, build_and_setup_text_layout_lib])
def generate_reflection_snapshot(ctx: TaskContext) -> None:
    """Generate new source code reflection file for the python source code wrapper"""
    compile_commands = get_script_root(ctx, "build/haxorg/compile_commands.json")
    build_targets(ctx=ctx, targets=["reflection_tool", "haxorg_generate_protobuf"])
    from py_codegen.refl_read import open_proto_file

    for task in CODEGEN_TASKS:
        out_file = get_build_root(ctx, f"{task}.pb")
        match task:
            case "pyhaxorg":
                src_file = get_script_root(
                    ctx, "src/py_libs/pyhaxorg/pyhaxorg_manual_refl.cpp")

            case "adaptagrams":
                src_file = get_script_root(
                    ctx, "src/py_libs/py_adaptagrams/adaptagrams_ir_refl_target.cpp")

        run_command_with_json_args(
            ctx,
            str(get_build_root(ctx, "haxorg/reflection_tool")),
            args=cov.ReflectionCLI(
                output=str(out_file),
                input=[str(src_file)],
                log_path=str(get_workflow_out(ctx, f"{task}_reflection_run.log")),
                mode=cov.Mode.AllAnotatedSymbols,
                verbose_log=ctx.config.log_level == HaxorgLogLevel.VERBOSE,
                reflection=cov.ReflectionConfig(
                    compilation_database=str(compile_commands),),
            ).model_dump(),
        )

        reflection_debug = get_tmpdir().joinpath(f"reflection_{task}.json")
        reflection_debug.write_text(open_proto_file(out_file).to_json(2))

        log(CAT).info(f"Updated reflection, wrote debug JSON to {reflection_debug}")


# TODO Make compiled reflection generation build optional
@haxorg_task(dependencies=[generate_reflection_snapshot])
def generate_haxorg_sources(ctx: TaskContext) -> None:
    """Update auto-generated source files"""
    assert not ctx.config.emscripten.build, "Codegen is not supported for the EMCC build"
    ctx.run(build_and_setup_text_layout_lib)
    from py_codegen.codegen import run_codegen_task

    for task in CODEGEN_TASKS:
        run_codegen_task(
            task=task,
            reflection_path=get_build_root(ctx).joinpath(f"{task}.pb"),
            is_tmp_codegen=ctx.config.generate_sources_conf.tmp,
            manual_tu_path=get_script_root(
                ctx, "scripts/py_codegen/py_codegen/codegen_extra_types.json"),
        )

        log(CAT).info("Updated code definitions")


@haxorg_task()
def merge_build_times(ctx: TaskContext) -> None:
    from py_repository.code_analysis.gen_include_graph import TraceFile
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


@haxorg_task()
def generate_binary_size_report(ctx: TaskContext) -> None:
    from py_repository.code_analysis import gen_symbol_size_report as gsrs
    if ctx.config.binary_size_conf.update_db:
        build_targets(ctx=ctx, targets=["reflection_tool"])
        gsrs.generate_binary_size_db(ctx)
    gsrs.generate_symbol_size_report(ctx)


@haxorg_task(dependencies=[generate_python_protobuf_files])
def generate_include_graph(ctx: TaskContext) -> None:
    compile_commands = get_script_root(ctx, "build/haxorg/compile_commands.json")
    header_commands = get_script_root(ctx,
                                      "build/haxorg/compile_commands_with_headers.json")
    # re-configure the whole project to generate new compilation database.
    configure_cmake_haxorg(ctx=ctx)
    build_targets(ctx=ctx, targets=["reflection_tool", "haxorg_generate_protobuf"])

    from py_repository.code_analysis.gen_include_graph import gen_include_graph
    gen_include_graph(
        ctx,
        compile_commands=compile_commands,
        header_commands=header_commands,
    )


@haxorg_task(dependencies=[generate_python_protobuf_files])
def generate_import_graph(ctx: TaskContext) -> None:
    """
    Generate import graph for all sub-projects and modules.
    """
    from py_repository.code_analysis import gen_import_graph
    import_graph = gen_import_graph.gen_import_graph(ctx)
    tmp = get_tmpdir("haxorg_import")
    ensure_existing_dir(ctx, tmp)
    tmp.joinpath("result.json").write_text(import_graph.model_dump_json(indent=2))
    ig_graph = gen_import_graph.import_graph_to_igraph(import_graph)
    gv_graph = gen_import_graph.import_igraph_to_graphviz(ig_graph)
    gv_graph.render(tmp.joinpath("result"), format="png", engine="dot")
    ig_graph.write_graphml(str(tmp.joinpath("result.graphml")))
