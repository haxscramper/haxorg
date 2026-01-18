from pathlib import Path
from beartype import beartype
from beartype.typing import List, Optional
import os

from py_repository.repo_tasks.config import HaxorgConfig
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_scriptutils.script_logging import log
from py_repository.repo_tasks.common import check_path_exists, create_symlink, ctx_write_text, get_component_build_dir, get_script_root, ensure_existing_dir, get_build_root
from py_repository.repo_tasks.command_execution import run_command
from py_ci.data_build import get_external_deps_list, get_deps_install_config, get_emscripten_cmake_flags
from py_ci.util_scripting import cmake_opt

CAT = __name__


@beartype
def get_deps_tmp_dir(ctx: TaskContext) -> Path:
    return get_build_root(ctx).joinpath(
        "deps_emcc" if ctx.config.emscripten.build else "deps_bin")


@beartype
def get_deps_install_dir(ctx: TaskContext) -> Path:
    return get_deps_tmp_dir(ctx).joinpath("install")


@beartype
def get_deps_build_dir(ctx: TaskContext) -> Path:
    return get_deps_tmp_dir(ctx).joinpath("build")


@haxorg_task()
def git_init_submodules(ctx: TaskContext) -> None:
    """Init submodules if missing"""
    if get_script_root(ctx).joinpath("thirdparty/mp11").exists():
        log(CAT).info("Submodules were checked out")
    else:
        log(CAT).info("Submodules were not checked out, running update")
        run_command(ctx, "git",
                    ["submodule", "update", "--init", "--recursive", "--progress"])


@haxorg_task(dependencies=[git_init_submodules])
def base_environment(ctx: TaskContext) -> None:
    """Ensure base dependencies are installed"""
    pass


@haxorg_task()
def generate_develop_deps_install_paths(ctx: TaskContext) -> None:
    install_dir = get_deps_install_dir(ctx)
    ensure_existing_dir(ctx, install_dir)
    ctx_write_text(
        ctx,
        install_dir.joinpath("paths.cmake"),
        get_deps_install_config(
            deps=get_external_deps_list(
                install_dir=install_dir,
                is_emcc=ctx.config.emscripten.build,
            ),
            install_dir=install_dir,
            exists_check=lambda path: check_path_exists(ctx, path),
        ),
    )


@beartype
def get_llvm_root(ctx: TaskContext, relative: Optional[str] = None) -> Path:
    value = get_script_root(ctx).joinpath("toolchain/llvm")
    if relative:
        value = value.joinpath(relative)

    return value


@beartype
def get_toolchain_path(ctx: TaskContext) -> Optional[Path]:
    if ctx.config.emscripten.build:
        result = Path(ctx.config.emscripten.toolchain)
        assert check_path_exists(ctx,
                                 result), f"EMCC toolchain path does not exist {result}"
        log(CAT).info(f"Using EMCC toolchain path {result}")
        return result

    else:
        return None
        return get_script_root(ctx).joinpath("toolchain.cmake")


@beartype
def get_cmake_defines(ctx: TaskContext) -> List[str]:
    result: List[str] = []
    conf = ctx.config

    assert not (conf.use.qt and
                conf.emscripten.build), "Qt cannot be used in the emcc build"

    if ctx.config.use_sarif:
        result.append(cmake_opt("ORG_USE_SARIF", True))

    result.append(cmake_opt("ORG_USE_COVERAGE", conf.instrument.coverage))
    result.append(cmake_opt("ORG_USE_XRAY", conf.instrument.xray))
    result.append(cmake_opt("ORG_USE_SANITIZER", conf.instrument.asan))
    result.append(cmake_opt("ORG_USE_PERFETTO", conf.instrument.perfetto))
    result.append(cmake_opt("ORG_USE_MSGPACK", conf.build_conf.use_msgpack))
    result.append(cmake_opt("ORG_USE_QT", conf.use.qt))
    result.append(cmake_opt("ORG_USE_IMGUI", conf.use.imgui))
    # result.append(cmake_opt("CMAKE_CXX_INCLUDE_WHAT_YOU_USE", "/home/haxscramper/software/include-what-you-use/build/bin/include-what-you-use;--verbose=7"))
    result.append(
        cmake_opt("CMAKE_BUILD_TYPE", "Debug" if conf.debug else "RelWithDebInfo"))

    result.append(cmake_opt("SQLITECPP_RUN_CPPLINT", False))

    result.append(cmake_opt("ORG_FORCE_ADAPTAGRAMS_BUILD", False))
    result.append(cmake_opt("ORG_DEPS_INSTALL_ROOT", get_deps_install_dir(ctx)))
    result.append(cmake_opt("CMAKE_EXPORT_COMPILE_COMMANDS", True))

    if conf.emscripten.build:
        result.append(cmake_opt("CMAKE_TOOLCHAIN_FILE", get_toolchain_path(ctx)))
        result.append(cmake_opt("ORG_DEPS_USE_PROTOBUF", False))
        result.append(cmake_opt("ORG_EMCC_BUILD", True))
        # result.append(cmake_opt("CMAKE_SIZEOF_VOID_P", "4"))
        # result.append(cmake_opt("CMAKE_SYSTEM_PROCESSOR", "wasm32"))

        for flag in get_emscripten_cmake_flags():
            result.append(cmake_opt(flag.name, flag.value))

    else:
        result.append(cmake_opt("ORG_EMCC_BUILD", False))
        result.append(cmake_opt("CMAKE_CXX_COMPILER", conf.build_conf.cxx_compiler))
        result.append(cmake_opt("CMAKE_C_COMPILER", conf.build_conf.c_compiler))
        result.append(cmake_opt("ORG_DEPS_USE_PROTOBUF", conf.build_conf.use_protobuf))

    debug = False
    if debug:
        result.append(cmake_opt("CMAKE_FIND_DEBUG_MODE", True))
        result.append("--trace")
        result.append("--trace-expand")

    else:
        result.append(cmake_opt("CMAKE_FIND_DEBUG_MODE", False))

    return result


@haxorg_task()
def symlink_build(ctx: TaskContext) -> None:
    """
    Create proxy symbolic links around the build directory
    """

    create_symlink(
        ctx,
        real_path=get_component_build_dir(ctx, "haxorg"),
        link_path=get_build_root(ctx, "haxorg"),
        is_dir=True,
    )
