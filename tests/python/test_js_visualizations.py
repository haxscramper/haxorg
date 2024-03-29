import pytest
from py_cli.scratch_scripts.serve_org_content import create_app
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from plumbum import local
from pathlib import Path
from beartype import beartype
from tempfile import TemporaryDirectory
import json
import xml.dom.minidom as minidom
from beartype.typing import List
from xml.dom.minidom import Node


def get_js_root() -> Path:
    return get_haxorg_repo_root_path().joinpath("scripts/py_cli/py_cli/scratch_scripts")


@beartype
def eval_js_visual(module_path: Path, json_path: Path, output_path: Path) -> None:
    cmd = local["node"]
    runner_path = get_haxorg_repo_root_path().joinpath(
        "tests/python/test_js_visualizations.mjs")

    cmd.run([
        runner_path,
        f"--module-path={module_path}",
        f"--input-file={json_path}",
        f"--output-file={output_path}",
    ])


@beartype
def read_svg(path: Path) -> Node:
    return minidom.parse(str(path))

def test_indented_subtree():
    with TemporaryDirectory() as tmp_dir:
        dir = Path(tmp_dir)
        app = create_app(directory=dir, script_dir=get_js_root())
        client = app.test_client()

        dir.joinpath("file.org").write_text("""
* [2024-02-12] Something
""")

        mind_map_response = client.get("/mind_map/file.org")
        print(mind_map_response)
        assert mind_map_response.status_code == 200
        tree_structure_response = client.get("/tree_structure/file.org")
        assert tree_structure_response.status_code == 200


        json_data = {
            "graphData": json.loads(mind_map_response.text),
            "treeData": json.loads(tree_structure_response.text),
        }

        json_file = dir.joinpath("data.json")
        json_file.write_text(json.dumps(json_data, indent=2))
        svg_file = dir.joinpath("result.svg")
        eval_js_visual(
            module_path=get_js_root().joinpath("indented_subtree/indented_subtree.mjs"),
            json_path=json_file,
            output_path=svg_file,
        )

        svg_content = read_svg(svg_file)

        titles: List[Node] = [it.firstChild.data for it in svg_content.getElementsByTagName("title")]
        assert titles[0] == "<document>", svg_content.toprettyxml()
        assert titles[1] == "<document>/Something", svg_content.toprettyxml()



