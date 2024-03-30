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
from py_scriptutils.script_logging import log

from threading import Thread
from werkzeug.serving import make_server
from flask import Flask

CAT = "test-js"

@beartype
class ServerThread(Thread):

    def __init__(self, app: Flask, port: int):
        Thread.__init__(self)
        app.debug = True
        self.srv = make_server('127.0.0.1', port, app)
        self.ctx = app.app_context()
        self.ctx.push()

    def run(self):
        self.srv.serve_forever()

    def shutdown(self):
        self.srv.shutdown()


@beartype
def run_flask_app_in_background(app: Flask, port: int) -> ServerThread:
    server_thread = ServerThread(app, port=port)
    server_thread.start()
    return server_thread


def get_js_root() -> Path:
    return get_haxorg_repo_root_path().joinpath("scripts/py_cli/py_cli/scratch_scripts")


@beartype
def eval_js_visual(module_path: str, output_path: Path) -> None:
    cmd = local["node"]
    runner_path = get_haxorg_repo_root_path().joinpath(
        "tests/python/test_js_visualizations.mjs")

    code, stdout, stderr = cmd.run([
        runner_path,
        f"--module-path={module_path}",
        f"--output-file={output_path}",
    ])

    if stdout:
        log(CAT).info(stdout)

    if stderr:
        log(CAT).warning(stderr)


@beartype
def eval_visual_for(content: str,
                    js_module: str,
                    test_tmp_dir: Optional[Path] = None) -> Node:
    with TemporaryDirectory() as tmp_dir:
        dir = Path(test_tmp_dir) if test_tmp_dir else Path(tmp_dir)
        app = create_app(directory=dir, script_dir=get_js_root())
        dir.joinpath("file.org").write_text(content)
        client = run_flask_app_in_background(app, 9876)
        svg_file = dir.joinpath("result.svg")

        eval_js_visual(
            module_path=js_module,
            output_path=svg_file,
        )



        client.shutdown()

        return read_svg(svg_file)


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


def test_indented_subtree():
    svg_content = eval_visual_for(
        content="""
* [2024-02-12] Something
""",
        js_module="indented_subtree/indented_subtree_test.html",
    )

    titles: List[Dict] = [
        dom_to_json(it) for it in svg_content.getElementsByTagName("title")
    ]

    assert titles[0]["subnodes"][0]["data"] == "<document>", titles
    assert titles[1]["subnodes"][0]["data"] == "<document>/Something", titles


def test_collapsible_subtree():
    svg_content = eval_visual_for(
        content="""
* Top1
** Nested1
** Nested2
* Top2
""",
        js_module="collapsible_subtrees/collapsible_subtrees_test.html",
    )

    Path("/tmp/test.svg").write_text(svg_content.toprettyxml())
