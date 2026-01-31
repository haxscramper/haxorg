import itertools
from pathlib import Path

import py_repository.code_analysis.gen_coverage_cookies as cov
from py_repository.repo_tasks.config import HaxorgLogLevel
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_repository.repo_tasks.command_execution import run_command, run_command_with_json_args
from py_repository.repo_tasks.common import check_is_file, ensure_existing_dir, get_build_root, get_log_dir, get_script_root, get_workflow_out
from py_repository.repo_tasks.haxorg_base import get_deps_install_dir, symlink_build
from py_repository.repo_tasks.haxorg_build import build_haxorg, build_targets, configure_cmake_haxorg
from py_scriptutils.script_logging import log

CAT = __name__


@haxorg_task(dependencies=[symlink_build])
def generate_python_protobuf_files(ctx: TaskContext) -> None:
    """Generate new python code from the protobuf reflection files"""
    proto_config = get_script_root(ctx, "scripts/cxx_codegen/reflection_defs.proto")

    _, stdout, _ = run_command(ctx, "uv", ["run", "--all-groups", "which", "python"], capture=True)
    stdout = stdout.strip().replace("/bin/python", "")
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
    build_targets(ctx=ctx, targets=["reflection_tool", "haxorg_generate_protobuf"])

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
        build_targets(ctx=ctx, targets=["py_textlayout_cpp"])
        ctx.run(generate_reflection_snapshot, ctx=ctx)
        ctx.run(symlink_build, ctx=ctx)

    from py_codegen.codegen import run_codegen_task

    for task in CODEGEN_TASKS:
        run_codegen_task(
            task=task,
            reflection_path=get_build_root(ctx).joinpath(f"{task}.pb"),
            is_tmp_codegen=ctx.config.generate_sources_conf.tmp,
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
