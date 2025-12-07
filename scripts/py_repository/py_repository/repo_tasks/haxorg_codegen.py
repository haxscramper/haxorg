from pathlib import Path

from py_ci.data_build import get_deps_install_config
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


@haxorg_task(dependencies=[
    generate_python_protobuf_files,
    build_haxorg,
])
def generate_reflection_snapshot(ctx: TaskContext) -> None:
    """Generate new source code reflection file for the python source code wrapper"""
    compile_commands = get_script_root(ctx, "build/haxorg/compile_commands.json")
    toolchain_include = get_script_root(
        ctx, f"toolchain/llvm/lib/clang/{ctx.config.LLVM_MAJOR}/include")

    conf_copy = ctx.config.model_copy()
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
                *(["--verbose"] if ctx.config.verbose else []),
                "--out",
                out_file,
                src_file,
            ],
            stderr_debug=get_log_dir().joinpath(f"debug_reflection_{task}_stderr.txt"),
            stdout_debug=get_log_dir().joinpath(f"debug_reflection_{task}_stdout.txt"),
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
        from dataclasses import replace
        config_copy = ctx.config.model_copy()
        config_copy.build_conf.target = ["py_textlayout_cpp"]
        ctx_copy = replace(ctx, config=config_copy)
        ctx_copy.run(build_haxorg, ctx=ctx_copy)
        ctx_copy.run(generate_reflection_snapshot, ctx=ctx_copy)
        ctx_copy.run(symlink_build, ctx=ctx_copy)

    for task in CODEGEN_TASKS:
        run_command(
            ctx,
            "poetry",
            [
                "run",
                get_script_root("scripts/py_codegen/py_codegen/codegen.py"),
                "--reflection_path={}".format(get_build_root().joinpath(f"{task}.pb")),
                f"--codegen_task={task}",
                f"--tmp={ctx.config.generate_sources_conf.tmp}",
            ],
            # env=get_py_env(),
        )

        log(CAT).info("Updated code definitions")
