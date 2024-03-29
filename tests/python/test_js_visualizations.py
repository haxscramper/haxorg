import pytest
from py_cli.scratch_scripts.serve_org_content import create_app
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from plumbum import local
from pathlib import Path
from beartype import beartype
from tempfile import TemporaryDirectory
import json
import xml.dom.minidom as minidom
from beartype.typing import List, Dict, Optional
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


@beartype
def dom_to_json(node: Node) -> Dict:
    if node.nodeType == node.TEXT_NODE:
        return {"kind": "Text", "data": node.data}

    node_dict = {"kind": "Node", "tag": node.tagName, "attrs": [], "subnodes": []}

    if node.hasAttributes():
        for attr_name in node.attributes.keys():
            node_dict["attrs"].append({
                "name": attr_name,
                "value": node.getAttribute(attr_name)
            })

    for child in node.childNodes:
        child_dict = dom_to_json(child)
        if child_dict:
            node_dict["subnodes"].append(child_dict)

    return node_dict


@beartype
def eval_visual_for(content: str,
                    endpoints: Dict[str, str],
                    js_module: str,
                    test_tmp_dir: Optional[Path] = None) -> Node:
    with TemporaryDirectory() as tmp_dir:
        dir = Path(test_tmp_dir) if test_tmp_dir else Path(tmp_dir)
        app = create_app(directory=dir, script_dir=get_js_root())
        client = app.test_client()

        dir.joinpath("file.org").write_text(content)

        json_data = {}

        for key, endpoint in endpoints.items():
            response = client.get(f"/{endpoint}/file.org")
            assert response.status_code == 200

            json_data[key] = json.loads(response.text)

        json_file = dir.joinpath("data.json")
        json_file.write_text(json.dumps(json_data, indent=2))
        svg_file = dir.joinpath("result.svg")
        eval_js_visual(
            module_path=get_js_root().joinpath(js_module),
            json_path=json_file,
            output_path=svg_file,
        )

        return read_svg(svg_file)


def test_indented_subtree():
    svg_content = eval_visual_for(
        content="""
* [2024-02-12] Something
""",
        endpoints={
            "graphData": "mind_map",
            "treeData": "tree_structure",
        },
        js_module="indented_subtree/indented_subtree.mjs",
    )

    titles: List[Dict] = [
        dom_to_json(it) for it in svg_content.getElementsByTagName("title")
    ]

    assert titles[0]["subnodes"][0]["data"] == "<document>", titles
    assert titles[1]["subnodes"][0]["data"] == "<document>/Something", titles
