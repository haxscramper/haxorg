import json
from pathlib import Path
import signal
from beartype.typing import List, Unpack
from beartype import beartype

import plumbum
from py_ci.util_scripting import cmake_opt
from py_repository.repo_tasks.workflow_utils import haxorg_task, TaskContext
from py_repository.repo_tasks.command_execution import RunCommandKwargs, run_cmake, run_command
from py_repository.repo_tasks.common import ensure_clean_dir, get_component_build_dir, get_script_root
from py_repository.repo_tasks.deps_build import validate_dependencies_install
from py_repository.repo_tasks.haxorg_base import get_toolchain_path, symlink_build
from py_repository.repo_tasks.haxorg_build import build_haxorg
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
    return run_cmake(
        ctx,
        [
            "-B",
            get_component_build_dir(component),
            "-S",
            get_script_root(script_path),
            # "--fresh",
            cmake_opt("CMAKE_TOOLCHAIN_FILE", get_toolchain_path()),
            cmake_opt("ORG_USE_COVERAGE",
                      get_config().instrument.coverage),
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
            get_component_build_dir(component),
            "--target",
            *targets,
        ] + args,
        **kwargs,
    )


@haxorg_task(dependencies=[validate_dependencies_install])
def configure_example_imgui_gui(ctx: TaskContext):
    run_cmake_configure_component(
        ctx,
        "example_imgui_gui",
        "examples/imgui_gui",
    )


@haxorg_task(dependencies=[configure_example_imgui_gui])
def build_example_imgui_gui(ctx: TaskContext):
    run_cmake_build_component(ctx, "example_imgui_gui",)


@haxorg_task(dependencies=[validate_dependencies_install])
def configure_example_qt_gui_org_viewer(ctx: TaskContext):
    assert get_config().use.qt, "Qt GUI example can only be built if the project enable the Qt usage"
    run_cmake_configure_component(
        ctx,
        "example_qt_gui_org_viewer",
        "examples/qt_gui/org_viewer",
    )


@haxorg_task(dependencies=[configure_example_qt_gui_org_viewer])
def build_example_qt_gui_org_viewer(ctx: TaskContext):
    assert get_config().use.qt, "Qt GUI example can only be built if the project enable the Qt usage"
    run_cmake_build_component(ctx, "example_qt_gui_org_viewer",)


@haxorg_task(dependencies=[validate_dependencies_install])
def configure_example_qt_gui_org_diagram(ctx: TaskContext):
    assert get_config().use.qt, "Qt GUI example can only be built if the project enable the Qt usage"
    run_cmake_configure_component(
        ctx,
        "example_qt_gui_org_diagram",
        "examples/qt_gui/org_diagram",
        args=[cmake_opt("JAVA_HOME", "/usr/lib/jvm/default")],
    )


@haxorg_task(dependencies=[configure_example_qt_gui_org_diagram])
def build_example_qt_gui_org_diagram(ctx: TaskContext):
    assert get_config().use.qt, "Qt GUI example can only be built if the project enable the Qt usage"
    run_cmake_build_component(ctx, "example_qt_gui_org_diagram",)


@haxorg_task(dependencies=[build_example_qt_gui_org_diagram])
def run_example_org_elk_diagram(ctx: TaskContext, infile: str):
    from py_scriptutils.graph_utils import haxorg_mind_map
    from py_scriptutils.graph_utils import elk_converter
    from py_scriptutils.graph_utils import elk_schema
    from py_scriptutils.graph_utils import typst_schema
    import igraph as ig

    wrapper_dir = "scripts/py_scriptutils/py_scriptutils/graph_utils/elk_cli_wrapper"
    run_command("gradle",
                args=["build"],
                cwd=get_haxorg_repo_root_path().joinpath(wrapper_dir))
    run_command("gradle",
                args=["install"],
                cwd=get_haxorg_repo_root_path().joinpath(wrapper_dir))
    diagram_build_dir = get_component_build_dir("example_qt_gui_org_diagram")
    mman_initial_path = "/tmp/mind-map-dump.json"
    run_command(diagram_build_dir.joinpath("org_diagram"),
                args=[
                    json.dumps(
                        dict(
                            documentPath=infile,
                            mode="MindMapDump",
                            outputPath=mman_initial_path,
                        ))
                ])

    mmap_model = haxorg_mind_map.Graph.model_validate(
        json.loads(Path(mman_initial_path).read_text()))
    mmap_igraph = haxorg_mind_map.convert_to_igraph(mmap_model)

    mmap_igraph = mmap_igraph.induced_subgraph(
        filter(lambda vertex: vertex["data"].vertexKind == "Item", mmap_igraph.vs))

    mmap_walker = haxorg_mind_map.HaxorgMMapWalker(mmap_igraph, mmap_model)
    from py_scriptutils.rich_utils import render_rich
    Path("/tmp/mmap_walker_repr.txt").write_text(render_rich(mmap_walker.getRepr()))
    pprint_to_file(to_debug_json(mmap_walker), "/tmp/mmap_walker.py")
    mmap_elk = mmap_walker.getELKGraph()

    pprint_to_file(mmap_elk, "/tmp/mmap_elk.py")

    layout_script = Path(wrapper_dir).joinpath(
        "build/install/elk_cli_wrapper/bin/elk_cli_wrapper")
    assert layout_script.exists()
    mmap_elk_layout = elk_schema.perform_graph_layout(mmap_elk, str(layout_script))

    elk_converter.group_multi_layout(
        mmap_elk_layout,
        single_item_hyperedge=True,
        hyperedge_polygon_width=2.0,
    )

    pprint_to_file(to_debug_json(mmap_elk_layout),
                   "/tmp/mmap_elk_layout_post_hyperedge.py")
    doc = elk_converter.graph_to_typst(mmap_elk_layout)

    doc.subnodes.insert(
        0,
        typst_schema.Import(
            path=str(get_haxorg_repo_root_path().joinpath(
                "scripts/py_scriptutils/py_scriptutils/graph_utils/haxorg_mind_map.typ")),
            items=["*"],
        ))

    final = typst_schema.generate_typst(doc)
    final_path = Path("/tmp/result.typ")
    log(CAT).info(f"Write final text to {final_path}")
    final_path.write_text(final)

    try:
        fmt = plumbum.local["typstyle"]
        fmt.run(["--inplace", str(final_path)])

    except plumbum.CommandNotFound:
        log.warning(
            f"Could not find commands `typstyle` -- install it for auto-formatting `.typ` file after creation"
        )

    compile_cmd = plumbum.local["typst"]
    compile_cmd.run([
        "compile",
        str(final_path),
        "--root",
        "/",
    ])


@haxorg_task(
    dependencies=[build_example_qt_gui_org_viewer, build_example_qt_gui_org_diagram])
def build_example_qt_gui(ctx: TaskContext):
    pass


@haxorg_task(dependencies=[build_example_qt_gui, build_example_imgui_gui])
def build_examples(ctx: TaskContext):
    pass


@haxorg_task(dependencies=[build_haxorg])
def build_d3_example(ctx: TaskContext):
    """
    Build d3.js visualization example
    """

    dir = get_script_root().joinpath("examples/d3_visuals")
    ensure_clean_dir(dir.joinpath("dist"))
    run_command("deno", ["task", "build"], cwd=dir)


@haxorg_task(dependencies=[build_d3_example])
def run_d3_example(ctx: TaskContext, sync: bool = False):
    assert get_config().emscripten.build, "D3 example requires emscripten to be enabled"
    d3_example_dir = get_script_root().joinpath("examples/d3_visuals")
    deno_run = find_process("deno", d3_example_dir, ["task", "run-gui"])

    import time
    time.sleep(1)

    if not sync and deno_run:
        log(CAT).info("Sending user signal to electron")
        electron = find_process("electron", d3_example_dir)
        electron.send_signal(signal.SIGUSR1)

    else:
        run_command(
            "deno",
            ["task", "run-gui"],
            cwd=d3_example_dir,
            run_mode="fg" if sync else "nohup",
            stderr_debug=get_log_dir().joinpath("electron_stderr.log"),
            stdout_debug=get_log_dir().joinpath("electron_stdout.log"),
        )


@haxorg_task(dependencies=[symlink_build])
def run_js_test_example(ctx: TaskContext):
    assert get_config().emscripten.build, "JS example requires emscripten to be enabled"
    js_example_dir = get_script_root().joinpath("examples/js_test")

    run_command(
        "node",
        ["js_test.js"],
        cwd=js_example_dir,
        env=dict(
            NODE_PATH=str(get_component_build_dir("haxorg")),
            TMPDIR=str(get_build_tmpdir(ctx, "haxorg")),
        ),
    )
