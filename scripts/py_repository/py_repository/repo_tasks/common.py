import os
from pathlib import Path
import shutil

from beartype import beartype
from beartype.typing import Iterable, List, Optional
import docker.models.containers
from plumbum import local
import psutil
from py_repository.repo_tasks.workflow_utils import TaskContext
from py_scriptutils.script_logging import log

CAT = __name__


@beartype
def get_script_root(ctx: TaskContext, relative: Optional[str] = None) -> Path:
    value = ctx.repo_root
    if relative:
        value = value.joinpath(relative)
    return value


@beartype
def symlink_build_dir(ctx: TaskContext) -> None:
    """
    Create proxy symbolic links around the build directory
    """

    haxorg_dir = get_build_root(ctx, get_real_build_basename(ctx, "haxorg"))
    haxorg_dir.mkdir(parents=True, exist_ok=True)

    create_symlink(
        ctx,
        real_path=haxorg_dir,
        link_path=get_build_root(ctx, "haxorg"),
        is_dir=True,
    )


@beartype
def ensure_clean_dir(ctx: TaskContext, dir: Path) -> Path:
    if dir.exists():
        shutil.rmtree(str(dir))
    dir.mkdir(parents=True, exist_ok=True)
    return dir


@beartype
def ensure_existing_dir(ctx: TaskContext, dir: Path) -> Path:
    if "build/haxorg" in str(dir):
        symlink_build_dir(ctx)

    dir.mkdir(parents=True, exist_ok=True)
    return dir


@beartype
def ensure_clean_file(ctx: TaskContext, file: Path) -> Path:
    ensure_existing_dir(ctx, file.parent)
    file.write_text("")
    return file


@beartype
def path_exists_in_container(container: docker.models.containers.Container,
                             path: Path) -> bool:
    exit_code, _ = container.exec_run(cmd=["test", "-e", str(path)],)
    return exit_code == 0


@beartype
def is_file_in_container(container: docker.models.containers.Container,
                         path: Path) -> bool:
    exit_code, _ = container.exec_run(cmd=["test", "-f", str(path)],)
    return exit_code == 0


@beartype
def is_dir_in_container(container: docker.models.containers.Container,
                        path: Path) -> bool:
    exit_code, _ = container.exec_run(cmd=["test", "-d", str(path)],)
    return exit_code == 0


@beartype
def check_path_exists(ctx: TaskContext, path: Path) -> bool:
    return path.exists()


@beartype
def check_is_file(ctx: TaskContext, path: Path) -> bool:
    return path.is_file()


@beartype
def check_is_dir(ctx: TaskContext, path: Path) -> bool:
    return path.is_dir()


@beartype
def _create_tar_archive(filename: str, content: bytes) -> bytes:
    import io
    import tarfile

    tar_buffer = io.BytesIO()
    with tarfile.open(fileobj=tar_buffer, mode='w') as tar:
        tarinfo = tarfile.TarInfo(name=filename)
        tarinfo.size = len(content)
        tar.addfile(tarinfo, io.BytesIO(content))

    tar_buffer.seek(0)
    return tar_buffer.read()


@beartype
def ctx_write_text(ctx: TaskContext, path: Path, content: str) -> None:
    path.write_text(content)


@beartype
def ctx_read_text(ctx: TaskContext, path: Path) -> str:
    return path.read_text()


@beartype
def ctx_remove_path(ctx: TaskContext, path: Path) -> None:
    """
    Remove specified path from the local filesystem or the currently active
    docker container. The function will remove both files and directories.
    """
    import shutil
    if path.is_dir():
        shutil.rmtree(path)
    else:
        path.unlink()


@beartype
def get_real_build_basename(ctx: TaskContext, component: str) -> str:
    """
    Get basename of the binary output directory for component
    """
    if ctx.config.build_base_override:
        result = f"{component}_{ctx.config.build_base_override}"

    else:
        result = component + "_" + ("debug" if ctx.config.debug else "release")
        if ctx.config.emscripten.build:
            result += "_emscripten"

        if ctx.config.instrument.coverage:
            result += "_instrumented"

    return result


@beartype
def get_list_cli_pass(list_name: str, args: Iterable[str]) -> List[str]:
    return [f"--{list_name}={arg}" for arg in args]


@beartype
def get_component_build_dir(ctx: TaskContext, component: str) -> Path:
    result = get_build_root(ctx, get_real_build_basename(ctx, component))
    ensure_existing_dir(ctx, result)
    return result


@beartype
def get_build_root(ctx: TaskContext, relative: Optional[str] = None) -> Path:
    value = get_script_root(ctx).joinpath("build")
    if relative:
        value = value.joinpath(relative)

    return value


def get_workflow_out(ctx: TaskContext, path: str) -> Path:
    result = ctx.config.workflow_out_dir.joinpath(path)
    ensure_existing_dir(ctx, result.parent)
    return result


def get_workflow_tmp(ctx: TaskContext, path: str) -> Path:
    result = ctx.config.workflow_tmp_dir.joinpath(path)
    ensure_existing_dir(ctx, result.parent)
    return result


@beartype
def get_log_dir(ctx: TaskContext) -> Path:
    res = get_build_root(ctx).joinpath("logs")
    ensure_existing_dir(ctx, res)
    return res


@beartype
def get_build_tmpdir(ctx: TaskContext, component: str) -> Path:
    result = get_build_root(ctx).joinpath("tmp").joinpath(
        get_real_build_basename(ctx, component))
    ensure_existing_dir(ctx, result)
    return result


@beartype
def create_symlink(ctx: TaskContext, link_path: Path, real_path: Path,
                   is_dir: bool) -> None:

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
def get_example_build(ctx: TaskContext, example_name: str) -> Path:
    return get_build_root(ctx).joinpath(f"example_build_{example_name}")


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


def get_lldb_py_import(ctx: TaskContext) -> List[str]:
    return [
        "-o",
        f"command script import {get_script_root(ctx, 'scripts/cxx_repository/lldb_script.py')}"
    ]


def get_lldb_source_on_crash(ctx: TaskContext) -> List[str]:
    return [
        "--source-on-crash",
        str(get_script_root(ctx, "scripts/cxx_repository/lldb-script.txt"))
    ]


@beartype
def docker_user() -> List[str]:
    return ["--user", f"{os.getuid()}:{os.getgid()}"]
