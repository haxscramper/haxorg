import tempfile
from beartype.typing import Dict, Callable, List, Optional, Iterable
from beartype import beartype
from functools import wraps
import psutil
from py_repository.repo_tasks.config import HaxorgConfig
from py_scriptutils.script_logging import log
import copy
import typing
import inspect
import shutil

from py_scriptutils.tracer import GlobCompleteEvent, GlobExportJson
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from plumbum import local

from pathlib import Path

import os

CAT = __name__


def get_script_root(relative: Optional[str] = None) -> Path:
    value = get_haxorg_repo_root_path()
    if relative:
        value = value.joinpath(relative)
    return value


@beartype
def ensure_clean_dir(dir: Path) -> Path:
    if dir.exists():
        shutil.rmtree(str(dir))

    dir.mkdir(parents=True, exist_ok=True)
    return dir


@beartype
def ensure_existing_dir(dir: Path) -> Path:
    dir.mkdir(parents=True, exist_ok=True)
    return dir


@beartype
def ensure_clean_file(file: Path) -> Path:
    ensure_existing_dir(file.parent)
    file.write_text("")
    return file


@beartype
def get_real_build_basename(config: HaxorgConfig, component: str) -> str:
    """
    Get basename of the binary output directory for component
    """
    result = component + "_" + ("debug" if config.debug else "release")
    if config.emscripten.build:
        result += "_emscripten"

    if config.instrument.coverage:
        result += "_instrumented"

    return result


@beartype
def get_list_cli_pass(list_name: str, args: Iterable[str]) -> List[str]:
    return [f"--{list_name}={arg}" for arg in args]


@beartype
def get_component_build_dir(config: HaxorgConfig, component: str) -> Path:
    result = get_build_root(get_real_build_basename(config, component))
    result.mkdir(parents=True, exist_ok=True)
    return result


@beartype
def get_build_root(relative: Optional[str] = None) -> Path:
    value = get_script_root().joinpath("build")
    if relative:
        value = value.joinpath(relative)

    return value


@beartype
def get_log_dir() -> Path:
    res = get_build_root().joinpath("logs")
    ensure_existing_dir(res)
    return res


@beartype
def get_build_tmpdir(config: HaxorgConfig, component: str) -> Path:
    result = get_build_root().joinpath("tmp").joinpath(
        get_real_build_basename(config, component))
    ensure_existing_dir(result)
    return result


@beartype
def ui_notify(message: str, is_ok: bool = True) -> None:
    try:
        cmd = local["notify-send"]
        cmd.run(
            [message] if is_ok else ["--urgency=critical", "--expire-time=1000", message])

    except Exception:
        if is_ok:
            log(CAT).info(message)

        else:
            log(CAT).error(message)


@beartype
def create_symlink(link_path: Path, real_path: Path, is_dir: bool) -> None:
    if link_path.exists():
        assert link_path.is_symlink(), link_path
        link_path.unlink()
        log(CAT).debug(f"'{link_path}' exists and is a symlink, removing")
        assert not link_path.exists(), link_path

    log(CAT).debug(f"'{link_path}'.symlink_to('{real_path}')")

    assert not link_path.exists(), link_path
    assert real_path.exists(), real_path

    link_path.symlink_to(target=real_path, target_is_directory=is_dir)


@beartype
def get_example_build(example_name: str) -> Path:
    return get_build_root().joinpath(f"example_build_{example_name}")


@beartype
def find_process(
    name: str,
    root_dir: Optional[Path] = None,
    args: Optional[list[str]] = None,
) -> Optional[psutil.Process]:
    for proc in psutil.process_iter(['pid', 'name', 'cmdline', 'cwd']):
        try:
            if ((proc.name() == name) and
                (root_dir is None or proc.cwd() == str(root_dir)) and
                (args is None or all(arg in proc.cmdline() for arg in args))):
                return proc
        except (psutil.NoSuchProcess, psutil.AccessDenied):
            continue
    return None


def clone_repo_with_uncommitted_changes(
    src_repo: Path,
    dst_repo: Path,
) -> None:
    run_command("git", ["clone", src_repo, dst_repo])

    code, stdout, stderr = run_command("git", [
        "-C",
        src_repo,
        "ls-files",
        "--modified",
        "--others",
        "--exclude-standard",
    ])

    if stdout.strip():
        file_list = stdout.strip().split('\n')
        for file in file_list:
            src_file = Path(f"{src_repo}/{file}")
            dst_file = Path(f"{dst_repo}/{os.path.dirname(file)}")
            log(CAT).info(f"Copying uncomitted changes {src_file} -> {dst_file}")
            dst_file.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy(src=src_file, dst=dst_file)


def get_lldb_py_import() -> List[str]:
    return [
        "-o",
        f"command script import {get_script_root('scripts/cxx_repository/lldb_script.py')}"
    ]


def get_lldb_source_on_crash() -> List[str]:
    return [
        "--source-on-crash",
        str(get_script_root("scripts/cxx_repository/lldb-script.txt"))
    ]


@beartype
def docker_user() -> List[str]:
    return ["--user", f"{os.getuid()}:{os.getgid()}"]
