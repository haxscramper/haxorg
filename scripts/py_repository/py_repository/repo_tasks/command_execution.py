import os
import shutil
from beartype import beartype
from beartype.typing import Optional, Union, List, Callable, TypedDict, Literal, Unpack, Any, Sequence
from pathlib import Path
import plumbum
import subprocess

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

    stderr_debug = stderr_debug or debug_override[0]
    stdout_debug = stdout_debug or debug_override[1]
    if isinstance(cmd, Path):
        assert cmd.exists(), f"{cmd} does not exist"
        cmd = str(cmd.resolve())

    def conv_arg(arg: Any) -> str:
        if isinstance(arg, Callable):
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

    import shlex
    # print(shlex.join(args))

    log(CAT).debug(f"Running [red]{cmd}[/red] {args_repr}" +
                   (f" in [green]{cwd}[/green]" if cwd else "") +
                   (f" with [purple]{env}[/purple]" if env else ""))

    if ctx.config.dryrun:
        log(CAT).warning("Dry run, early exit")
        return (0, "", "")

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
        run = run.with_cwd(str(cwd))

    if run_mode == "nohup" or run_mode == "bg":
        stderr_stream = open(stderr_debug, "w") if stderr_debug else None
        stdout_stream = open(stdout_debug, "w") if stdout_debug else None

        try:
            subprocess.Popen(
                [str(cmd), *str_args],
                cwd=str(cwd) if cwd else None,
                start_new_session=run_mode == "nohup",
                stdout=stdout_stream if stdout_stream else subprocess.DEVNULL,
                stderr=stderr_stream if stderr_stream else subprocess.DEVNULL,
            )

        finally:
            if stdout_stream:
                stdout_stream.close()

            if stderr_stream:
                stderr_stream.close()

        return (0, "", "")

    else:
        if ctx.config.log_level == HaxorgLogLevel.QUIET or (
                not print_output and ctx.config.log_level == HaxorgLogLevel.NORMAL):
            retcode, stdout, stderr = run.run(list(str_args), retcode=None)

        else:
            retcode, stdout, stderr = run[*str_args] & plumbum.TEE(retcode=None)

        @beartype
        def write_file(path: Path, append: bool, text: str) -> None:
            if append:
                if not path.exists():
                    path.write_text("")

                with path.open("a") as file:
                    file.write(remove_ansi(text))
                    file.flush()

            else:
                path.write_text(remove_ansi(text))

        if stdout_debug and stdout:
            # log(CAT).info(f"Wrote stdout to {stdout_debug}")
            write_file(stdout_debug, append_stdout_debug, stdout)

        if stderr_debug and stderr:
            # log(CAT).info(f"Wrote stderr to {stderr_debug}")
            write_file(stderr_debug, append_stderr_debug, stderr)

        if allow_fail or retcode == 0:
            return (retcode, stdout, stderr)

        else:
            raise RuntimeError("Failed to execute the command {} {}{}{}".format(
                cmd,
                " ".join((f"\"{s}\"" for s in args)),
                f"\nwrote stdout to {stdout_debug}" if (stdout_debug and stdout) else "",
                f"\nwrote stderr to {stderr_debug}" if (stderr_debug and stderr) else "",
            )) from None


@beartype
def run_cmake(
    ctx: TaskContext,
    args: List[str | Path],
    **kwargs: Unpack[RunCommandKwargs],
) -> tuple[int, str, str]:
    return run_command(ctx, "cmake", args, **kwargs)


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
