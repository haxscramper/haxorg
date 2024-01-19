import pytest
from pathlib import Path
from py_scriptutils.repo_files import get_haxorg_repo_root_path
import os

root = get_haxorg_repo_root_path()
ld_preload = root.joinpath("toolchain/llvm/lib/clang/17/lib/x86_64-unknown-linux-gnu/libclang_rt.asan.so")
os.environ["LD_PRELOAD"] = str(ld_preload)
os.environ["ASAN_OPTIONS"] = "detect_leaks=0"

from py_scriptutils.tracer import TraceCollector

trace_collector: TraceCollector = None

def get_trace_collector():
    global trace_collector
    if not trace_collector:
        trace_collector = TraceCollector()

    return trace_collector



@pytest.fixture(scope="session", autouse=True)
def trace_session():
    get_trace_collector().push_complete_event("session", "test-session")
    yield
    get_trace_collector().pop_complete_event()
    get_trace_collector().export_to_json(Path("/tmp/haxorg_py_tests.json"))

@pytest.fixture(scope="module", autouse=True)
def trace_module(request):
    module_name = request.module.__name__
    get_trace_collector().push_complete_event(module_name, "test-file")
    yield
    get_trace_collector().pop_complete_event()

@pytest.fixture(autouse=True)
def trace_test(request):
    test_name = request.node.name
    get_trace_collector().push_complete_event(test_name, "test")
    yield
    get_trace_collector().pop_complete_event()
