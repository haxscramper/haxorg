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
import rich.logging
import _pytest.logging
import pytest
from py_scriptutils.rich_utils import render_debug
import pytest

CAT = "test-js"

import logging


def dbg(value) -> str:
    if isinstance(value, Node):
        return value.toprettyxml()

    else:
        return render_debug(value)


def print_effective_handlers(logger):
    current_logger = logger
    while current_logger:
        for handler in current_logger.handlers:
            print(f"Handler found on '{current_logger.name}': {handler} {type(handler)}")
        if not current_logger.propagate or current_logger.parent is None:
            break
        current_logger = current_logger.parent


# Remove log handler noise with duplicate logging entries
def adjust_werkzeug_logger():
    werkzeug_logger = logging.getLogger("werkzeug")
    root_logger = logging.getLogger()

    for handler in werkzeug_logger.handlers[:]:
        werkzeug_logger.removeHandler(handler)

    for handler in root_logger.handlers:
        if isinstance(handler, rich.logging.RichHandler) or isinstance(
                handler, _pytest.logging.LogCaptureHandler):
            werkzeug_logger.addHandler(handler)
        elif isinstance(handler, _pytest.logging._LiveLoggingStreamHandler):
            pass

        else:
            pass

    werkzeug_logger.propagate = False
    werkzeug_logger.setLevel(logging.INFO)


@beartype
class ServerThread(Thread):

    def __init__(self, app: Flask, port: int):
        Thread.__init__(self)
        app.debug = True
        self.srv = make_server('127.0.0.1', port, app)
        self.ctx = app.app_context()
        self.ctx.push()

    def run(self):
        adjust_werkzeug_logger()
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

    if test_tmp_dir and not test_tmp_dir.exists():
        test_tmp_dir.mkdir(parents=True)

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

    node_dict = {"kind": "Node", "tag": node.tagName, "attrs": {}, "subnodes": []}

    if node.hasAttributes():
        for attr_name in node.attributes.keys():
            node_dict["attrs"][attr_name] = node.getAttribute(attr_name)

    for child in node.childNodes:
        child_dict = dom_to_json(child)
        if child_dict:
            node_dict["subnodes"].append(child_dict)

    return node_dict


@pytest.mark.x11
@pytest.mark.skip(reason="Puppeteer timeout, and I don't want to deal with the fucking JS garbage anymore. In the next feature branch I will drop the whole visualization test and leave the JS scripts to just rot in the corner until further notice.")
def test_indented_subtree():
    svg_content = eval_visual_for(
        content="""
* [2024-02-12] Something
""",
        js_module="indented_subtree/indented_subtree_test.html",
        test_tmp_dir=Path("/tmp/test_indented_subtree"),
    )

    titles: List[Dict] = [
        dom_to_json(it) for it in svg_content.getElementsByTagName("title")
    ]

    assert titles[0]["subnodes"][0]["data"] == "<document>", titles
    assert titles[1]["subnodes"][0]["data"] == "<document>/Something", titles


@pytest.mark.x11
@pytest.mark.skip(reason="Puppeteer timeout, and I don't want to deal with the fucking JS garbage anymore. In the next feature branch I will drop the whole visualization test and leave the JS scripts to just rot in the corner until further notice.")
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

    texts: List[Dict] = [
        dom_to_json(it)["subnodes"][0]["data"]
        for it in svg_content.getElementsByTagName("text")
    ]

    # Content is arranged in the BFS order, layer by layer
    assert texts == [
        "<document>",
        "Top1",
        "Top2",
        "Nested1",
        "Nested2",
    ]


@pytest.mark.x11
@pytest.mark.skip(reason="Puppeteer timeout, and I don't want to deal with the fucking JS garbage anymore. In the next feature branch I will drop the whole visualization test and leave the JS scripts to just rot in the corner until further notice.")
def test_timeline_with_zoom():
    svg_content = eval_visual_for(
        content="""
* [2024-12-02 10:00:00]--[2024-12-02 10:30:00] Event1
* [2024-12-02 11:00:00]--[2024-12-02 11:30:00] Event2
""",
        js_module="js_timeline_with_zoom/timeline_with_zoom_test.html")

    it: Node
    events = [
        event
        for event in (dom_to_json(it) for it in svg_content.getElementsByTagName("text"))
        if event["attrs"].get("class", None) == "data_overlay"
    ]

    assert events[0]["subnodes"] == [{"kind": "Text", "data": "Event1"}], dbg(events)
    assert events[1]["subnodes"] == [{"kind": "Text", "data": "Event2"}], dbg(events)


@pytest.mark.x11
@pytest.mark.skip(reason="Puppeteer timeout, and I don't want to deal with the fucking JS garbage anymore. In the next feature branch I will drop the whole visualization test and leave the JS scripts to just rot in the corner until further notice.")
def test_standalone_tree_arcs():
    svg_content = eval_visual_for(
        content="""
* Top11
** Top21
** Top22
** Top23
* Top12
""",
        js_module="mind_map/standalone_mind_map_arcs_test.html",
    )

    events = [
        dom_to_json(it)["subnodes"] for it in svg_content.getElementsByTagName("text")
    ][1:]

    assert events[0] == [{"kind": "Text", "data": "Top11"}], dbg(events)
    assert events[1] == [{"kind": "Text", "data": "Top12"}], dbg(events)
    assert events[2] == [{"kind": "Text", "data": "Top21"}], dbg(events)
    assert events[3] == [{"kind": "Text", "data": "Top22"}], dbg(events)
    assert events[4] == [{"kind": "Text", "data": "Top23"}], dbg(events)
