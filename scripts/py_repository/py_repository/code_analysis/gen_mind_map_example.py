import json
from pathlib import Path
from beartype import beartype
import plumbum
from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.common import get_component_build_dir, get_script_root, get_workflow_out
from py_repository.repo_tasks.workflow_utils import TaskContext
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_scriptutils.script_logging import log, pprint_to_file, to_debug_json

CAT = __name__


def gen_mind_map(ctx: TaskContext) -> None:
    from py_scriptutils.graph_utils import haxorg_mind_map
    from py_scriptutils.graph_utils import elk_converter
    from py_scriptutils.graph_utils import elk_schema
    from py_scriptutils.graph_utils import typst_schema
    import igraph as ig

    assert ctx.config.example_conf.mind_map.infile, ctx.config.example_conf.mind_map.infile
    assert Path(ctx.config.example_conf.mind_map.infile).exists(
    ), ctx.config.example_conf.mind_map.infile

    wrapper_dir = "scripts/py_scriptutils/py_scriptutils/graph_utils/elk_cli_wrapper"
    run_command(ctx,
                "gradle",
                args=["build"],
                cwd=get_script_root(ctx).joinpath(wrapper_dir))
    run_command(ctx,
                "gradle",
                args=["install"],
                cwd=get_script_root(ctx).joinpath(wrapper_dir))
    diagram_build_dir = get_component_build_dir(ctx, "example_qt_gui_org_diagram")

    def get_out(name: str) -> Path:
        return get_workflow_out(ctx, f"mind_map/{name}")

    mman_initial_path = get_out("mind-map-dump.json")
    run_command(
        ctx,
        diagram_build_dir.joinpath("org_diagram"),
        args=[
            json.dumps(
                dict(
                    documentPath=str(ctx.config.example_conf.mind_map.infile),
                    mode="MindMapDump",
                    outputPath=str(mman_initial_path),
                ))
        ],
        env={
            "ASAN_OPTIONS": "detect_leaks=0",
        },
    )

    mmap_model = haxorg_mind_map.Graph.model_validate(
        json.loads(Path(mman_initial_path).read_text()))
    mmap_igraph = haxorg_mind_map.convert_to_igraph(mmap_model)

    mmap_igraph = mmap_igraph.induced_subgraph(
        filter(lambda vertex: vertex["data"].vertexKind == "Item", mmap_igraph.vs))

    mmap_walker = haxorg_mind_map.HaxorgMMapWalker(mmap_igraph, mmap_model)
    from py_scriptutils.rich_utils import render_rich
    get_out("mmap_walker_repr.txt").write_text(render_rich(mmap_walker.getRepr()))
    pprint_to_file(to_debug_json(mmap_walker), get_out("mmap_walker.py"))
    mmap_elk = mmap_walker.getELKGraph()

    pprint_to_file(mmap_elk, get_out("mmap_elk.py"))

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
                   get_out("mmap_elk_layout_post_hyperedge.py"))
    doc = elk_converter.graph_to_typst(mmap_elk_layout)

    doc.subnodes.insert(
        0,
        typst_schema.Import(
            path=str(get_haxorg_repo_root_path().joinpath(
                "scripts/py_scriptutils/py_scriptutils/graph_utils/haxorg_mind_map.typ")),
            items=["*"],
        ))

    final = typst_schema.generate_typst(doc)
    final_path = get_out("mind_map_result.typ")
    log(CAT).info(f"Write final text to {final_path}")
    final_path.write_text(final)

    try:
        fmt = plumbum.local["typstyle"]
        fmt.run(["--inplace", str(final_path)])

    except plumbum.CommandNotFound:
        log(CAT).warning(
            f"Could not find commands `typstyle` -- install it for auto-formatting `.typ` file after creation"
        )

    try:
        compile_cmd = plumbum.local["typst"]
        compile_cmd.run([
            "compile",
            str(final_path),
            "--root",
            "/",
        ])

        log(CAT).info(f"Result PDF in {final_path.with_suffix('.pdf')}")

    except plumbum.CommandNotFound:
        log(CAT).warning(
            f"Could not find commands `typst` to auto-comple example file {final_path}")
