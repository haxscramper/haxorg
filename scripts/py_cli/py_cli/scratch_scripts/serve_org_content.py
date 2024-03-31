#!/usr/bin/env python

from flask import Flask, send_from_directory
from flask_cors import CORS
import os
import rich_click as click
from py_scriptutils.script_logging import log, custom_traceback_handler
import sys
import logging
from py_scriptutils.files import cache_file_processing_result
from beartype import beartype
from pathlib import Path
import py_haxorg.pyhaxorg_wrap as org
import json
from py_haxorg.pyhaxorg_utils import NodeIdProvider
from py_scriptutils.repo_files import get_haxorg_repo_root_path


@cache_file_processing_result(input_arg_names=["file"])
def getNode(file: Path) -> org.Org:
    return org.parseFile(str(file), org.OrgParseParameters())


CAT = "serve_org"


@beartype
def create_app(
    directory: Path,
    script_dir: Path = get_haxorg_repo_root_path().joinpath(
        "scripts/py_cli/py_cli/scratch_scripts"),
) -> Flask:
    app = Flask(__name__)
    CORS(app)

    app.config["DIRECTORY"] = directory
    app.config["SCRIPT_DIR"] = script_dir
    idProvider = NodeIdProvider()

    def getDir() -> Path:
        return app.config["DIRECTORY"]

    @app.route("/gantt_chart/<path:filename>")
    def gantt_chart(filename: str):
        from py_cli.scratch_scripts.js_timeline_with_zoom.gantt_timeline import getGantt
        return json.dumps(getGantt(getNode(getDir().joinpath(filename))).toJson())

    @app.route("/tree_structure/<path:filename>")
    def tree_structure(filename: str):
        from py_cli.scratch_scripts.collapsible_subtrees.subtree_structure import getStructure
        return json.dumps(
            getStructure(idProvider, getNode(getDir().joinpath(filename))).model_dump())

    @app.route("/get_mind_map/<path:filename>")
    def mind_map(filename: str):
        from py_cli.scratch_scripts.mind_map.mind_map import getGraph
        graph = getGraph(idProvider, [getNode(getDir().joinpath(filename))])
        result = graph.toJsonGraph().model_dump_json()
        Path("/tmp/result.json").write_text(graph.toJsonGraph().model_dump_json(indent=2))
        return result

    @app.route("/<path:filename>")
    def js_source(filename):
        return send_from_directory(app.config["SCRIPT_DIR"], filename)

    @app.route('/node_modules/<path:filename>')
    def serve_node_modules(filename):
        return send_from_directory(get_haxorg_repo_root_path().joinpath("node_modules"),
                                   filename)

    return app


@click.command()
@click.option("--directory", default=".", help="Directory to serve files from", type=str)
@click.option("--script-dir", default=".", help="Directory to serve files from", type=str)
@click.option("--port", default=9555, help="Port to serve on", type=int)
@click.option("--debug", default=False, help="Enable flask debuggign", type=bool)
def serve(directory: str, port: int, script_dir: str, debug: bool):
    app = create_app(Path(directory), Path(script_dir))
    log(CAT).info(f"Serving HTTP on port {port} from directory {directory}...")
    sys.excepthook = custom_traceback_handler
    app.run(host="localhost", port=port, debug=debug)


if __name__ == "__main__":
    serve()
