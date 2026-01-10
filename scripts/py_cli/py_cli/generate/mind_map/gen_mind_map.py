from dataclasses import dataclass
import json
import logging
from pathlib import Path

from beartype import beartype
import igraph as ig
import plumbum
import rich_click as click
from beartype.typing import Any
from py_cli import haxorg_cli, haxorg_opts
from py_cli.generate.mind_map import (elk_converter, elk_schema, haxorg_mind_map,
                                      typst_schema)
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_scriptutils.script_logging import log, pprint_to_file, to_debug_json

CAT = __name__


@beartype
class MindMapBuildArtifacts():
    mmap_model: haxorg_mind_map.Graph
    mmap_igraph: ig.Graph
    mmap_elk_layout: elk_schema.Graph


def gen_mind_map(opts: haxorg_opts.RootOptions) -> MindMapBuildArtifacts:
    result = MindMapBuildArtifacts()
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

    result.mmap_model = haxorg_mind_map.Graph.model_validate(
        json.loads(Path(mman_initial_path).read_text()))
    result.mmap_igraph = haxorg_mind_map.convert_to_igraph(result.mmap_model)

    result.mmap_igraph = result.mmap_igraph.induced_subgraph(
        filter(lambda vertex: vertex["data"].vertexKind == "Item", result.mmap_igraph.vs))

    mmap_walker = haxorg_mind_map.HaxorgMMapWalker(result.mmap_igraph, result.mmap_model)
    from py_scriptutils.rich_utils import render_rich
    get_out("mmap_walker_repr.txt").write_text(render_rich(mmap_walker.getRepr()))
    pprint_to_file(to_debug_json(mmap_walker), get_out("mmap_walker.py"))
    mmap_elk = mmap_walker.getELKGraph()

    pprint_to_file(mmap_elk, get_out("mmap_elk.py"))

    layout_script = Path(wrapper_dir).joinpath(
        "build/install/elk_cli_wrapper/bin/elk_cli_wrapper")

    assert layout_script.exists()
    result.mmap_elk_layout = elk_schema.perform_graph_layout(mmap_elk, str(layout_script))

    if opts.generate.mind_map.group_hyperedges:
        elk_converter.group_multi_layout(
            result.mmap_elk_layout,
            single_item_hyperedge=opts.generate.mind_map.group_single_item_hyperedge,
            hyperedge_polygon_width=opts.generate.mind_map.hyperedge_width,
        )

    pprint_to_file(to_debug_json(result.mmap_elk_layout),
                   get_out("mmap_elk_layout_post_hyperedge.py"))
    doc = elk_converter.graph_to_typst(result.mmap_elk_layout)

    for path, items in opts.generate.mind_map.typst_import_list:
        doc.subnodes.insert(0, typst_schema.Import(path=path, items=items))

    final = typst_schema.generate_typst(doc)
    final_path = get_out("mind_map_result.typ")
    final_path.write_text(final)

    try:
        fmt = plumbum.local["typstyle"]
        fmt.run(["--inplace", str(final_path)])

    except plumbum.CommandNotFound:
        pass

    if opts.generate.mind_map.typst_do_compile:
        compile_args = ["compile"]

        if opts.generate.mind_map.typst_compile_root:
            compile_args.extend(["--root", opts.generate.mind_map.typst_compile_root])

        compile_args.extend([
            str(final_path),
            str(opts.generate.mind_map.outfile),
        ])

        compile_cmd = plumbum.local["typst"]
        compile_cmd.run(compile_args)

    return result


@click.command("mind_map")
@haxorg_cli.get_wrap_options(haxorg_opts.RootOptions)
@click.pass_context
def gen_mind_map_cli(ctx: click.Context, **kwargs: Any) -> None:
    opts = haxorg_cli.get_opts(ctx)
    gen_mind_map(opts)
