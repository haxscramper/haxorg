from py_cli.generate.mind_map import haxorg_mind_map, elk_converter, elk_schema, typst_schema
from py_cli import haxorg_cli, haxorg_opts
import igraph as ig
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_scriptutils.script_logging import log, pprint_to_file, to_debug_json
from pathlib import Path
import plumbum
import json
import rich_click as click
from beartype.typing import Any
import logging


CAT = __name__


def gen_mind_map(opts: haxorg_opts.RootOptions) -> None:
    logging.getLogger("fontTools.ttLib.ttFont").setLevel(logging.WARNING)
    assert opts.generate
    assert opts.generate.mind_map
    mind_map_opts = opts.generate.mind_map
    assert mind_map_opts.infile, mind_map_opts.infile
    assert Path(mind_map_opts.infile).exists(), mind_map_opts.infile

    repo_root = get_haxorg_repo_root_path()

    wrapper_dir = opts.generate.mind_map.wrapper_dir
    gradle_cmd = plumbum.local["gradle"].with_cwd(repo_root.joinpath(wrapper_dir))
    gradle_cmd.run(["build"])
    gradle_cmd.run(["install"])

    def get_out(name: str) -> Path:
        return haxorg_cli.get_tmp_file(opts, f"mind_map/{name}")

    mman_initial_path = get_out("mind-map-dump.json")
    org_diagram_cmd = plumbum.local[str(
        opts.generate.mind_map.org_diagram_tool)].with_env(ASAN_OPTIONS="detect_leaks=0",)

    org_diagram_cmd.run([
        json.dumps(
            dict(
                documentPath=str(opts.generate.mind_map.infile),
                mode="MindMapDump",
                outputPath=str(mman_initial_path),
            ))
    ])

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

    if opts.generate.mind_map.group_hyperedges:
        elk_converter.group_multi_layout(
            mmap_elk_layout,
            single_item_hyperedge=opts.generate.mind_map.group_single_item_hyperedge,
            hyperedge_polygon_width=opts.generate.mind_map.hyperedge_width,
        )

    pprint_to_file(to_debug_json(mmap_elk_layout),
                   get_out("mmap_elk_layout_post_hyperedge.py"))
    doc = elk_converter.graph_to_typst(mmap_elk_layout)

    doc.subnodes.insert(
        0,
        typst_schema.Import(
            path=str(get_haxorg_repo_root_path().joinpath(
                "scripts/py_cli/py_cli/generate/mind_map/haxorg_mind_map.typ")),
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


@click.command("mind_map")
@haxorg_cli.get_wrap_options(haxorg_opts.RootOptions)
@click.pass_context
def haxorg_main_cli(ctx: click.Context, **kwargs: Any) -> None:
    opts = haxorg_cli.get_opts(ctx)
    gen_mind_map(opts)
