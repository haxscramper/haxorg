#!/usr/bin/env python

import ast
import logging
import os
import subprocess
import sys
import time
import warnings
from pathlib import Path

import pytest
from beartype import beartype
from beartype.typing import Any, List
from hstd_py_lib.tracer import TraceCollector

CAT = "conftest"

trace_collector: TraceCollector = None


def pytest_configure(config: Any) -> None:
    "nodoc"
    for logger_name in [
        "plumbum.local",
        "matplotlib.font_manager",
        "graphviz._tools",
        "matplotlib",
        "asyncio",
        "git.cmd",
        "git.util",
    ]:
        logger = logging.getLogger(logger_name)
        logger.disabled = True

    warnings.filterwarnings(
        "ignore",
        category=DeprecationWarning,
        module="pydantic._internal._config",
    )
    warnings.filterwarnings(
        "ignore",
        category=UserWarning,
        module="pydantic._internal._config",
    )
    warnings.filterwarnings(
        "ignore",
        category=pytest.PytestRemovedIn9Warning,
        module="tests.python.conftest",
    )
    warnings.filterwarnings(
        "ignore",
        category=DeprecationWarning,
        module="dominate.dom_tag",
    )


def get_trace_collector() -> TraceCollector:
    global trace_collector
    if not trace_collector:
        trace_collector = TraceCollector()

    return trace_collector


def check_gui_application_on_display(app_command: str, display: str) -> None:
    env = os.environ.copy()
    env["DISPLAY"] = display

    try:
        process = subprocess.Popen(
            app_command, env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE
        )
        time.sleep(2)
        if process.poll() is not None:
            stdout, stderr = process.communicate()
            raise Exception(f"""
Application failed to start:"
STDOUT: {stdout.decode()}
STDERR: {stderr.decode()}
                """)

        else:
            process.terminate()
    except Exception as e:
        print(f"Failed to start the application: {str(e)}")


class FunctionNameExtractor(ast.NodeVisitor):
    def __init__(self) -> None:
        self.function_names: List[str] = []

    def visit_Call(self, node: ast.Call) -> None:
        if isinstance(node.func, ast.Name):
            self.function_names.append(node.func.id)
        self.generic_visit(node)


def get_function_names(expression: str) -> List[str]:
    parsed_ast = ast.parse(expression, mode="eval")
    extractor = FunctionNameExtractor()
    extractor.visit(parsed_ast)
    return extractor.function_names


@pytest.fixture
def cpp_debugger(request: Any) -> dict[str, bool]:

    @beartype
    def run_under_lldb() -> None:
        test_path = str(request.node.fspath)
        test_name = request.node.Name

        lldb_script_content = """breakpoint set -E C++
breakpoint set -n __cxa_throw
breakpoint set -n abort
breakpoint set -n std::terminate
run
bt
continue
"""

        script_path = Path("/tmp/debug.lldb")
        script_path.write_text(lldb_script_content)

        pytest_cmd = [
            sys.executable,
            "-m",
            "pytest",
            f"{test_path}::{test_name}",
            "-vv",
            "-s",
            "--tb=line",
        ]

        lldb_cmd = ["lldb", "--source", str(script_path), "--"] + pytest_cmd

        try:
            subprocess.run(lldb_cmd)
        finally:
            script_path.unlink()

    @beartype
    def finalizer() -> None:
        if hasattr(request.node, "rep_call") and request.node.rep_call.failed:
            run_under_lldb()

    request.addfinalizer(finalizer)
    return {"debug_enabled": True}
