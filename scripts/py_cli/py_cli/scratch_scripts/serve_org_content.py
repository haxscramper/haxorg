#!/usr/bin/env python

import rich_click as click
from http.server import HTTPServer, SimpleHTTPRequestHandler
from py_scriptutils.script_logging import log
from functools import partial

class CORSHTTPRequestHandler(SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET")
        self.send_header("Cache-Control", "no-store, no-cache, must-revalidate")
        return super().end_headers()

@click.command()
@click.option("--directory", default=".", help="Directory to serve files from", type=str)
@click.option("--port", default=9555, help="Port to serve on", type=int)
def serve(directory: str, port: int):
    handler_class = partial(CORSHTTPRequestHandler, directory=directory)
    httpd = HTTPServer(("localhost", port), handler_class)
    log("http").info(f"Serving HTTP on port {port} from directory {directory}...")
    httpd.serve_forever()

if __name__ == "__main__":
    serve()
