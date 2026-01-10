import json
from pathlib import Path
import signal
from beartype.typing import List, Unpack
from beartype import beartype

import plumbum
from py_ci.util_scripting import cmake_opt
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_repository.repo_tasks.command_execution import RunCommandKwargs, run_cmake, run_command
from py_repository.repo_tasks.common import ensure_clean_dir, find_process, get_build_tmpdir, get_component_build_dir, get_log_dir, get_script_root, get_workflow_out
from py_repository.repo_tasks.deps_build import validate_dependencies_install
from py_repository.repo_tasks.haxorg_base import get_toolchain_path, symlink_build
from py_repository.repo_tasks.haxorg_build import build_haxorg
from py_scriptutils.algorithm import maybe_splice
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_scriptutils.script_logging import log, pprint_to_file, to_debug_json

CAT = __name__


@beartype
def run_cmake_configure_component(
    ctx: TaskContext,
    component: str,
    script_path: str,
    args: List[str | Path] = [],
    **kwargs: Unpack[RunCommandKwargs],
) -> tuple[int, str, str]:
    toolchain = get_toolchain_path(ctx)
    return run_cmake(
        ctx,
        [
            "-B",
            get_component_build_dir(ctx, component),
            "-S",
            get_script_root(ctx, script_path),
            "--fresh",
            *maybe_splice(toolchain, cmake_opt("CMAKE_TOOLCHAIN_FILE", toolchain)),
            cmake_opt("ORG_USE_COVERAGE", ctx.config.instrument.coverage),
            cmake_opt("CMAKE_CXX_COMPILER", ctx.config.build_conf.cxx_compiler),
            cmake_opt("CMAKE_C_COMPILER", ctx.config.build_conf.c_compiler),
            "-G",
            "Ninja",
            "-Wno-dev",
        ] + args,
        **kwargs,
    )


@beartype
def run_cmake_build_component(
    ctx: TaskContext,
    component: str,
    targets: List[str] = ["all"],
    args: List[str | Path] = [],
    **kwargs: Unpack[RunCommandKwargs],
) -> tuple[int, str, str]:
    return run_cmake(
        ctx,
        [
            "--build",
            get_component_build_dir(ctx, component),
            "--target",
            *targets,
        ] + args,  # type: ignore
        **kwargs,
    )


@haxorg_task(dependencies=[validate_dependencies_install])
def configure_example_imgui_gui(ctx: TaskContext) -> None:
    run_cmake_configure_component(
        ctx,
        "example_imgui_gui",
        "examples/imgui_gui",
    )


@haxorg_task(dependencies=[configure_example_imgui_gui])
def build_example_imgui_gui(ctx: TaskContext) -> None:
    run_cmake_build_component(
        ctx,
        "example_imgui_gui",
    )


@haxorg_task(dependencies=[validate_dependencies_install])
def configure_example_qt_gui_org_viewer(ctx: TaskContext) -> None:
    assert ctx.config.use.qt, "Qt GUI example can only be built if the project enable the Qt usage"
    run_cmake_configure_component(
        ctx,
        "example_qt_gui_org_viewer",
        "examples/qt_gui/org_viewer",
    )


@haxorg_task(dependencies=[configure_example_qt_gui_org_viewer])
def build_example_qt_gui_org_viewer(ctx: TaskContext) -> None:
    assert ctx.config.use.qt, "Qt GUI example can only be built if the project enable the Qt usage"
    run_cmake_build_component(
        ctx,
        "example_qt_gui_org_viewer",
    )


@haxorg_task(dependencies=[validate_dependencies_install])
def configure_example_qt_gui_org_diagram(ctx: TaskContext) -> None:
    assert ctx.config.use.qt, "Qt GUI example can only be built if the project enable the Qt usage"
    run_cmake_configure_component(
        ctx,
        "example_qt_gui_org_diagram",
        "examples/qt_gui/org_diagram",
        args=[cmake_opt("JAVA_HOME", "/usr/lib/jvm/default")],
    )


@haxorg_task(dependencies=[configure_example_qt_gui_org_diagram])
def build_example_qt_gui_org_diagram(ctx: TaskContext) -> None:
    assert ctx.config.use.qt, "Qt GUI example can only be built if the project enable the Qt usage"
    run_cmake_build_component(
        ctx,
        "example_qt_gui_org_diagram",
    )


@haxorg_task(
    dependencies=[build_example_qt_gui_org_viewer, build_example_qt_gui_org_diagram])
def build_example_qt_gui(ctx: TaskContext) -> None:
    pass


@haxorg_task(dependencies=[build_example_qt_gui, build_example_imgui_gui])
def build_examples(ctx: TaskContext) -> None:
    pass


@haxorg_task(dependencies=[])
def run_examples(ctx: TaskContext) -> None:
    pass


@haxorg_task(dependencies=[build_haxorg])
def build_d3_example(ctx: TaskContext) -> None:
    """
    Build d3.js visualization example
    """

    dir = get_script_root(ctx).joinpath("examples/d3_visuals")
    ensure_clean_dir(ctx, dir.joinpath("dist"))
    run_command(ctx, "deno", ["task", "build"], cwd=dir)


@haxorg_task(dependencies=[build_d3_example])
def run_d3_example(ctx: TaskContext, sync: bool = False) -> None:
    assert ctx.config.emscripten.build, "D3 example requires emscripten to be enabled"
    d3_example_dir = get_script_root(ctx).joinpath("examples/d3_visuals")
    deno_run = find_process("deno", d3_example_dir, ["task", "run-gui"])

    import time
    time.sleep(1)

    if not sync and deno_run:
        log(CAT).info("Sending user signal to electron")
        electron = find_process("electron", d3_example_dir)
        assert electron is not None
        electron.send_signal(signal.SIGUSR1)

    else:
        run_command(
            ctx,
            "deno",
            ["task", "run-gui"],
            cwd=d3_example_dir,
            run_mode="fg" if sync else "nohup",
        )


@haxorg_task(dependencies=[symlink_build])
def run_js_test_example(ctx: TaskContext) -> None:
    assert ctx.config.emscripten.build, "JS example requires emscripten to be enabled"
    js_example_dir = get_script_root(ctx).joinpath("examples/js_test")

    run_command(
        ctx,
        "node",
        ["js_test.js"],
        cwd=js_example_dir,
        env=dict(
            NODE_PATH=str(get_component_build_dir(ctx, "haxorg")),
            TMPDIR=str(get_build_tmpdir(ctx, "haxorg")),
        ),
    )
