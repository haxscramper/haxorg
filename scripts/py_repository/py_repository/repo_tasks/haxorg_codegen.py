from pathlib import Path

from py_ci.data_build import get_deps_install_config
from py_repository.repo_tasks.workflow_utils import haxorg_task
from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.common import get_script_root
from py_repository.repo_tasks.haxorg_base import symlink_build
from py_repository.repo_tasks.haxorg_build import build_haxorg
from py_scriptutils.script_logging import log

CAT = __name__


@haxorg_task(dependencies=[symlink_build])
def generate_python_protobuf_files():
    """Generate new python code from the protobuf reflection files"""
    proto_config = get_script_root(
        "scripts/cxx_codegen/reflection_tool/reflection_defs.proto")

    _, stdout, _ = run_command("poetry", ["env", "info", "--path"], capture=True)
    stdout = stdout.strip()
    log(CAT).info(f"Using protoc plugin path '{stdout}'")
    protoc_plugin = Path(stdout).joinpath("bin/protoc-gen-python_betterproto")

    if not protoc_plugin.exists():
        raise RuntimeError(
            f"Protoc plugin for better python is not installed correctly, {protoc_plugin} does not exist"
        )

    proto_lib = get_script_root("scripts/py_codegen/py_codegen/proto_lib")

    if not proto_lib.exists():
        proto_lib.mkdir()

    run_command(
        get_deps_install_config().joinpath("protobuf/bin/protoc"),
        [
            f"--plugin={protoc_plugin}",
            "-I",
            get_script_root("scripts/cxx_codegen"),
            "--proto_path=" +
            str(get_script_root("scripts/py_codegen/py_codegen/reflection_tool")),
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
def generate_reflection_snapshot(
    verbose: bool = False,
):
    """Generate new source code reflection file for the python source code wrapper"""
    compile_commands = get_script_root("build/haxorg/compile_commands.json")
    toolchain_include = get_script_root(f"toolchain/llvm/lib/clang/{LLVM_MAJOR}/include")

    run_self(
        [
            build_haxorg,
            "--target=reflection_lib",
            "--target=reflection_tool",
            "--force",
        ],
    )


    for task in CODEGEN_TASKS:
        out_file = get_build_root(f"{task}.pb")
        match task:
            case "pyhaxorg":
                src_file = get_script_root(
                    "src/py_libs/pyhaxorg/pyhaxorg_manual_refl.cpp")

            case "adaptagrams":
                src_file = get_script_root(
                    "src/py_libs/py_adaptagrams/adaptagrams_ir_refl_target.cpp")

        run_command(
            "build/haxorg/scripts/cxx_codegen/reflection_tool/reflection_tool",
            [
                "-p",
                compile_commands,
                "--compilation-database",
                compile_commands,
                "--toolchain-include",
                toolchain_include,
                *(["--verbose"] if verbose else []),
                "--out",
                out_file,
                src_file,
            ],
            stderr_debug=get_log_dir().joinpath(
                f"debug_reflection_{task}_stderr.txt"),
            stdout_debug=get_log_dir().joinpath(
                f"debug_reflection_{task}_stdout.txt"),
        )

        log(CAT).info("Updated reflection")



# TODO Make compiled reflection generation build optional
@haxorg_task()
def generate_haxorg_sources(tmp: bool = False, standalone: bool = False):
    """Update auto-generated source files"""
    # TODO source file generation should optionally overwrite the target OR
    # compare the new and old source code (to avoid breaking the subsequent
    # compilation of the source)
    log(CAT).info("Executing haxorg code generation step.")
    if not standalone:
        run_self([build_haxorg, "--target=py_textlayout_cpp"])
        run_self([generate_reflection_snapshot])
        run_self([symlink_build])

    for task in CODEGEN_TASKS:
        run_command(
            "poetry",
            [
                "run",
                get_script_root("scripts/py_codegen/py_codegen/codegen.py"),
                "--reflection_path={}".format(get_build_root().joinpath(f"{task}.pb")),
                f"--codegen_task={task}",
                f"--tmp={tmp}",
            ],
            env=get_py_env(),
        )

        log(CAT).info("Updated code definitions")
