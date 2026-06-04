import json
import os
from pathlib import Path
import signal
import subprocess
import sys
import time

from py_scriptutils.repo_files import get_haxorg_repo_root_path

BIN = f"{get_haxorg_repo_root_path()}/build/haxorg/executor_tracker"


def _start_tracker(tmp_path: Path) -> subprocess.Popen:
    tracker_configuration = {
        "pids": [os.getpid()],
        "path": str(tmp_path / "execution-log.jsonl"),
        "emitExisting": False,
    }
    proc = subprocess.Popen(
        [BIN, json.dumps(tracker_configuration)],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    time.sleep(0.1)
    return proc


def _stop_tracker(proc: subprocess.Popen) -> list[dict]:
    proc.send_signal(signal.SIGTERM)
    out, err = proc.communicate(timeout=10)
    assert proc.returncode == 0, err
    return [json.loads(line) for line in out.splitlines() if line.strip()]


def _assert_pid_lifecycle(events: list[dict], pid: int) -> None:
    matching = [ev for ev in events if ev.get("pid") == pid]
    names = [ev.get("name") for ev in matching]
    assert "proc.start" in names
    assert "proc.end" in names
    assert names.index("proc.start") < names.index("proc.end")


def test_tracks_subprocess_from_current_script(tmp_path: Path) -> None:
    tracker = _start_tracker(tmp_path)

    child = subprocess.Popen([sys.executable, "-c", "import time; time.sleep(0.4)"])
    child_pid = child.pid
    child.wait(timeout=5)

    time.sleep(0.2)
    events = _stop_tracker(tracker)

    _assert_pid_lifecycle(events, child_pid)


def test_tracks_parallel_subprocesses(tmp_path: Path) -> None:
    tracker = _start_tracker(tmp_path)

    children = [
        subprocess.Popen([sys.executable, "-c", "import time; time.sleep(0.5)"])
        for _ in range(4)
    ]
    child_pids = [p.pid for p in children]
    for proc in children:
        proc.wait(timeout=5)

    time.sleep(0.2)
    events = _stop_tracker(tracker)

    for pid in child_pids:
        _assert_pid_lifecycle(events, pid)


def test_tracks_execution_of_clangpp_built_program(tmp_path: Path) -> None:
    source = tmp_path / "elem.cpp"
    binary = tmp_path / "elem_bin"

    source.write_text("""
#include <chrono>
#include <thread>
int main() {
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    return 0;
}
""".strip())

    subprocess.run(
        ["clang++", "-std=c++20", str(source), "-o",
         str(binary)],
        check=True,
    )

    tracker = _start_tracker(tmp_path)

    child = subprocess.Popen([str(binary)])
    child_pid = child.pid
    child.wait(timeout=5)

    time.sleep(0.2)
    events = _stop_tracker(tracker)

    _assert_pid_lifecycle(events, child_pid)


def test_tracks_execution_of_cmake_built_cpp_program(tmp_path: Path) -> None:
    project = tmp_path / "cmake_proj"
    build = project / "build"
    project.mkdir()

    (project / "CMakeLists.txt").write_text("""
cmake_minimum_required(VERSION 3.20)
project(exec_tracker_test LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
add_executable(cmake_sample main.cpp)
""".strip())

    (project / "main.cpp").write_text("""
#include <chrono>
#include <thread>
int main() {
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    return 0;
}
""".strip())

    subprocess.run(["cmake", "-S", str(project), "-B", str(build)], check=True)
    subprocess.run(["cmake", "--build", str(build)], check=True)

    tracker = _start_tracker(tmp_path)

    exe = build / "cmake_sample"
    child = subprocess.Popen([str(exe)])
    child_pid = child.pid
    child.wait(timeout=5)

    time.sleep(0.2)
    events = _stop_tracker(tracker)

    _assert_pid_lifecycle(events, child_pid)
