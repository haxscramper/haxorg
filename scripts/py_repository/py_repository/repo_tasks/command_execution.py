import os
import shutil
import docker
import docker.models.containers
from dataclasses import dataclass
from beartype import beartype
from beartype.typing import Optional, Union, List, Callable, TypedDict, Literal, Unpack, Any, Sequence
from pathlib import Path
import plumbum
import subprocess

from py_ci.util_scripting import get_j_cap
from py_repository.repo_tasks.config import HaxorgLogLevel
from py_repository.repo_tasks.workflow_utils import TaskContext
from py_scriptutils.script_logging import log
from py_scriptutils.algorithm import remove_ansi

CAT = __name__


@beartype
def get_cmd_debug_file(kind: str) -> Path:
    return Path(f"/tmp/debug_{kind}.log")


class RunCommandKwargs(TypedDict, total=False):
    capture: bool
    allow_fail: bool
    env: dict[str, str]
    cwd: Optional[Union[str, Path]]
    stderr_debug: Optional[Path]
    stdout_debug: Optional[Path]
    append_stdout_debug: bool
    append_stderr_debug: bool
    run_mode: Literal["nohup", "bg", "fg"]
    print_output: bool


@dataclass
class CommandResult:
    retcode: int
    stdout: str
    stderr: str


@beartype
def write_debug_file(path: Path, append: bool, text: str) -> None:
    if append:
        if not path.exists():
            path.write_text("")

        with path.open("a") as file:
            file.write(remove_ansi(text))
            file.flush()

    else:
        path.write_text(remove_ansi(text))


@beartype
def write_debug_outputs(
    result: CommandResult,
    stdout_debug: Optional[Path],
    stderr_debug: Optional[Path],
    append_stdout_debug: bool,
    append_stderr_debug: bool,
) -> None:
    if stdout_debug and result.stdout:
        write_debug_file(stdout_debug, append_stdout_debug, result.stdout)

    if stderr_debug and result.stderr:
        write_debug_file(stderr_debug, append_stderr_debug, result.stderr)


@beartype
def raise_command_error(
    cmd: str,
    args: List[str],
    stdout_debug: Optional[Path],
    stderr_debug: Optional[Path],
    stdout: str,
    stderr: str,
) -> None:
    raise RuntimeError("Failed to execute the command {} {}{}{}".format(
        cmd,
        " ".join((f"\"{s}\"" for s in args)),
        f"\nwrote stdout to {stdout_debug}" if (stdout_debug and stdout) else "",
        f"\nwrote stderr to {stderr_debug}" if (stderr_debug and stderr) else "",
    )) from None


@beartype
def _capture_all(log_level: HaxorgLogLevel, print_output: bool) -> bool:
    return log_level == HaxorgLogLevel.QUIET or (not print_output and
                                                 log_level == HaxorgLogLevel.NORMAL)


@beartype
def run_command_in_docker(
    container: docker.models.containers.Container,
    cmd: str,
    args: List[str],
    env: dict[str, str],
    cwd: Optional[str],
    print_output: bool,
    log_level: HaxorgLogLevel,
) -> CommandResult:
    full_command = [cmd] + args

    if env:
        env_prefix = [f"{k}={v}" for k, v in env.items()]
        full_command = ["env"] + env_prefix + full_command

    exit_code, output = container.exec_run(
        cmd=full_command,
        workdir=cwd,
        stream=False,
        demux=True,
    )

    stdout = output[0].decode("utf-8") if output[0] else ""
    stderr = output[1].decode("utf-8") if output[1] else ""

    if log_level == HaxorgLogLevel.VERBOSE or print_output:
        if stdout:
            print(stdout, end="")
        if stderr:
            print(stderr, end="")

    return CommandResult(retcode=exit_code, stdout=stdout, stderr=stderr)


@beartype
def run_command_on_host(
    cmd: str,
    args: List[str],
    env: dict[str, str],
    cwd: Optional[str],
    run_mode: Literal["nohup", "bg", "fg"],
    print_output: bool,
    log_level: HaxorgLogLevel,
    stdout_debug: Optional[Path],
    stderr_debug: Optional[Path],
) -> CommandResult:
    try:
        run = plumbum.local[cmd]

    except plumbum.CommandNotFound as e:
        log(CAT).error(e)
        for path in e.path:
            log(CAT).info(path)
            dir = Path(path)
            if "haxorg" in str(dir):
                if not dir.exists():
                    log(CAT).error("Dir does not exist")

                for file in dir.glob("*"):
                    log(CAT).debug(f"  - {file}")

            else:
                log(CAT).debug(f"- is a system dir")

        raise e

    if env:
        run = run.with_env(**env)

    if cwd is not None:
        run = run.with_cwd(cwd)

    if run_mode == "nohup" or run_mode == "bg":
        stderr_stream = open(stderr_debug, "w") if stderr_debug else None
        stdout_stream = open(stdout_debug, "w") if stdout_debug else None

        try:
            subprocess.Popen(
                [cmd, *args],
                cwd=cwd,
                start_new_session=run_mode == "nohup",
                stdout=stdout_stream if stdout_stream else subprocess.DEVNULL,
                stderr=stderr_stream if stderr_stream else subprocess.DEVNULL,
            )

        finally:
            if stdout_stream:
                stdout_stream.close()

            if stderr_stream:
                stderr_stream.close()

        return CommandResult(retcode=0, stdout="", stderr="")

    else:
        if _capture_all(log_level, print_output):
            retcode, stdout, stderr = run.run(list(args), retcode=None)

        else:
            retcode, stdout, stderr = run[*args] & plumbum.TEE(retcode=None)

        return CommandResult(retcode=retcode, stdout=stdout, stderr=stderr)


@beartype
def run_command(
    ctx: TaskContext,
    cmd: Union[str, Path],
    args: Sequence[Union[str, Path, Callable]],
    capture: bool = False,
    allow_fail: bool = False,
    env: dict[str, str] = {},
    cwd: Optional[Union[str, Path]] = None,
    stderr_debug: Optional[Path] = None,
    stdout_debug: Optional[Path] = None,
    append_stdout_debug: bool = False,
    append_stderr_debug: bool = False,
    run_mode: Literal["nohup", "bg", "fg"] = "fg",
    print_output: bool = False,
) -> tuple[int, str, str]:
    debug_override = ctx.get_task_debug_streams(
        str(str(cmd).split("/")[-1] if "/" in str(cmd) else cmd),
        args,
    )

    from py_repository.repo_tasks.common import check_path_exists

    stderr_debug = stderr_debug or debug_override[0]
    stdout_debug = stdout_debug or debug_override[1]
    if isinstance(cmd, Path):
        assert check_path_exists(ctx, cmd), f"{cmd} does not exist"
        cmd = str(cmd.resolve())

    def conv_arg(arg: Any) -> str:
        if isinstance(arg, Callable):  # type: ignore
            return arg.name.replace("_", "-")

        elif isinstance(arg, Path):
            return str(arg)

        else:
            return arg

    str_args: List[str] = [conv_arg(it) for it in args]

    args_repr = " ".join((f"\"[cyan]{s}[/cyan]\"" for s in str_args))

    def append_to_log(path: Path) -> None:
        with path.open("a") as file:
            file.write(f"""
{'*' * 120}
cwd : {cwd}
args: {args}
cmd:  {cmd}
{'*' * 120}


""")
            file.flush()

    if append_stderr_debug:
        append_to_log(stderr_debug)

    if append_stdout_debug:
        append_to_log(stdout_debug)

    log(CAT).debug(f"Running [red]{cmd}[/red] {args_repr}" +
                   (f" in [green]{cwd}[/green]" if cwd else "") +
                   (f" with [purple]{env}[/purple]" if env else ""))

    if ctx.config.dryrun:
        log(CAT).warning("Dry run, early exit")
        return (0, "", "")

    str_cwd = str(cwd) if cwd else None

    if ctx.docker_container is not None:
        result = run_command_in_docker(
            container=ctx.docker_container,
            cmd=str(cmd),
            args=str_args,
            env=env,
            cwd=str_cwd,
            print_output=print_output,
            log_level=ctx.config.log_level,
        )

    else:
        result = run_command_on_host(
            cmd=str(cmd),
            args=str_args,
            env=env,
            cwd=str_cwd,
            run_mode=run_mode,
            print_output=print_output,
            log_level=ctx.config.log_level,
            stdout_debug=stdout_debug,
            stderr_debug=stderr_debug,
        )

    write_debug_outputs(
        result=result,
        stdout_debug=stdout_debug,
        stderr_debug=stderr_debug,
        append_stdout_debug=append_stdout_debug,
        append_stderr_debug=append_stderr_debug,
    )

    if allow_fail or result.retcode == 0:
        return (result.retcode, result.stdout, result.stderr)

    else:
        raise_command_error(
            cmd=str(cmd),
            args=str_args,
            stdout_debug=stdout_debug,
            stderr_debug=stderr_debug,
            stdout=result.stdout,
            stderr=result.stderr,
        )

        return (0, "", "")


@beartype
def run_cmake(
    ctx: TaskContext,
    args: List[str | Path],
    **kwargs: Unpack[RunCommandKwargs],
) -> tuple[int, str, str]:
    return run_command(ctx, "cmake", args, **kwargs)


@beartype
def run_cmake_build(
    ctx: TaskContext,
    build_dir: Path,
    targets: List[str],
    args: List[str | Path] = [],
    build_tool_args: List[str | Path] = [],
    **kwargs: Unpack[RunCommandKwargs],
) -> tuple[int, str, str]:


    build_args: List[str | Path] = build_tool_args[:]

    if ctx.config.in_ci:
        build_args.extend(["-d", "explain"])

    if ctx.config.force_full_build:
        build_args.extend(["-k0"])

    if 0 < len(build_args):
        build_args.insert(0, "--")

    return run_command(  # type: ignore
        ctx,
        "cmake",
        [
            "--build",
            build_dir,
            "--target",
            *targets,
            *args,
            *get_j_cap(),
            *build_args,
        ],
        env={
            'NINJA_FORCE_COLOR': '1',
            **kwargs.get('env', {})
        },
        **kwargs,
    )


def clone_repo_with_uncommitted_changes(
    ctx: TaskContext,
    src_repo: Path,
    dst_repo: Path,
) -> None:
    run_command(ctx, "git", ["clone", src_repo, dst_repo])

    code, stdout, stderr = run_command(ctx, "git", [
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
