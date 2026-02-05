import copy
from functools import wraps
import inspect
import os
from pathlib import Path
import shutil
import tempfile
import typing

from beartype import beartype
from beartype.typing import Callable, Dict, Iterable, List, Optional
import docker.models.containers
from plumbum import local
import psutil
from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.config import HaxorgConfig
from py_repository.repo_tasks.workflow_utils import TaskContext
from py_scriptutils.repo_files import get_haxorg_repo_root_path
from py_scriptutils.script_logging import log
from py_scriptutils.tracer import GlobCompleteEvent, GlobExportJson

CAT = __name__


@beartype
def get_script_root(ctx: TaskContext, relative: Optional[str] = None) -> Path:
    value = ctx.repo_root
    if relative:
        value = value.joinpath(relative)
    return value


@beartype
def ensure_clean_dir(ctx: TaskContext, dir: Path) -> Path:
    if ctx.docker_container is not None:
        ctx.docker_container.exec_run(
            cmd=["bash", "-c", f"rm -rf {dir} && mkdir -p {dir}"],)
    else:
        if dir.exists():
            shutil.rmtree(str(dir))
        dir.mkdir(parents=True, exist_ok=True)
    return dir


@beartype
def ensure_existing_dir(ctx: TaskContext, dir: Path) -> Path:
    if ctx.docker_container is not None:
        ctx.docker_container.exec_run(cmd=["mkdir", "-p", str(dir)],)
    else:
        dir.mkdir(parents=True, exist_ok=True)
    return dir


@beartype
def ensure_clean_file(ctx: TaskContext, file: Path) -> Path:
    ensure_existing_dir(ctx, file.parent)
    if ctx.docker_container is not None:
        ctx.docker_container.exec_run(cmd=["bash", "-c", f"truncate -s 0 {file}"],)
    else:
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
    if ctx.docker_container is not None:
        return path_exists_in_container(ctx.docker_container, path)
    else:
        return path.exists()


@beartype
def check_is_file(ctx: TaskContext, path: Path) -> bool:
    if ctx.docker_container is not None:
        return is_file_in_container(ctx.docker_container, path)
    else:
        return path.is_file()


@beartype
def check_is_dir(ctx: TaskContext, path: Path) -> bool:
    if ctx.docker_container is not None:
        return is_dir_in_container(ctx.docker_container, path)
    else:
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
    if ctx.docker_container is not None:
        import base64
        import tempfile

        # Create a temporary file on the host
        with tempfile.NamedTemporaryFile(mode='w', delete=False,
                                         encoding='utf-8') as tmp_file:
            tmp_file.write(content)
            tmp_host_path = tmp_file.name

        try:
            # Copy the temporary file into the container
            with open(tmp_host_path, 'rb') as f:
                success = ctx.docker_container.put_archive(path=str(path.parent),
                                                           data=_create_tar_archive(
                                                               path.name, f.read()))
                if not success:
                    raise RuntimeError(
                        f"Failed to write file {path}: could not copy to container")
        finally:
            # Clean up the temporary file
            import os
            os.unlink(tmp_host_path)
    else:
        path.write_text(content)


@beartype
def ctx_read_text(ctx: TaskContext, path: Path) -> str:
    if ctx.docker_container is not None:
        exit_code, output = ctx.docker_container.exec_run(
            cmd=["cat", str(path)],
            demux=True,
        )
        if exit_code != 0:
            _, stderr = output
            raise RuntimeError(
                f"Failed to read file {path}: {stderr.decode('utf-8') if stderr else 'unknown error'}"
            )
        stdout, _ = output
        return stdout.decode("utf-8")
    else:
        return path.read_text()


@beartype
def ctx_remove_file(ctx: TaskContext, path: Path) -> None:
    if ctx.docker_container is not None:
        exit_code, output = ctx.docker_container.exec_run(
            cmd=["rm", str(path)],
            demux=True,
        )
        if exit_code != 0:
            _, stderr = output
            raise RuntimeError(
                f"Failed to remove file {path}: {stderr.decode('utf-8') if stderr else 'unknown error'}"
            )
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
def create_symlink(ctx: TaskContext, link_path: Path, real_path: Path,
                   is_dir: bool) -> None:
    if ctx.docker_container is not None:
        exit_code, output = ctx.docker_container.exec_run(
            cmd=["test", "-L", str(link_path)],)
        link_exists_and_is_symlink = exit_code == 0

        exit_code, _ = ctx.docker_container.exec_run(cmd=["test", "-e", str(link_path)],)
        link_exists = exit_code == 0

        if link_exists:
            assert link_exists_and_is_symlink, link_path
            ctx.docker_container.exec_run(cmd=["rm", str(link_path)])
            log(CAT).debug(f"'{link_path}' exists and is a symlink, removing")
            exit_code, _ = ctx.docker_container.exec_run(
                cmd=["test", "-e", str(link_path)],)
            assert exit_code != 0, link_path

        log(CAT).debug(f"'{link_path}'.symlink_to('{real_path}')")

        exit_code, _ = ctx.docker_container.exec_run(cmd=["test", "-e", str(link_path)],)
        assert exit_code != 0, link_path

        exit_code, _ = ctx.docker_container.exec_run(cmd=["test", "-e", str(real_path)],)
        assert exit_code == 0, real_path

        exit_code, output = ctx.docker_container.exec_run(
            cmd=["ln", "-s", str(real_path), str(link_path)],
            demux=True,
        )
        if exit_code != 0:
            _, stderr = output
            raise RuntimeError(
                f"Failed to create symlink: {stderr.decode('utf-8') if stderr else 'unknown error'}"
            )
    else:
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
