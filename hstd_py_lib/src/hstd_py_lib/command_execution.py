import subprocess
from dataclasses import dataclass
from pathlib import Path

import plumbum
from beartype import beartype
from beartype.typing import (
    Any,
    Callable,
    Dict,
    List,
    Literal,
    Optional,
    Sequence,
    TypedDict,
    Union,
    Unpack,
)
from loguru import logger

from hstd_py_lib.algorithm import remove_ansi


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
def _write_debug_outputs(
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
def _consume_execution_fail(
    cmd: str,
    args: List[str],
    stdout_debug: Optional[Path],
    stderr_debug: Optional[Path],
    stdout: str,
    stderr: str,
    allow_fail: bool,
) -> None:
    message = "Failed to execute the command {} {}{}{}".format(
        cmd,
        " ".join((f'"{s}"' for s in args)),
        f"\nwrote stdout to {stdout_debug}" if (stdout_debug and stdout) else "",
        f"\nwrote stderr to {stderr_debug}" if (stderr_debug and stderr) else "",
    )

    if allow_fail:
        logger.warning(message)

    else:
        raise RuntimeError(message) from None


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
        logger.error(e)
        for path in e.path:
            logger.info(path)
            dir = Path(path)
            if "haxorg" in str(dir):
                if not dir.exists():
                    logger.error("Dir does not exist")

                for file in dir.glob("*"):
                    logger.debug(f"  - {file}")

            else:
                logger.debug(f"- is a system dir")

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
        if not print_output:
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
    """
    Return tuple: (code, stdout, stderr)
    """
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
        if isinstance(arg, Callable):  # type: ignore
            return arg.name.replace("_", "-")

        elif isinstance(arg, Path):
            return str(arg)

        else:
            return arg

    str_args: List[str] = [conv_arg(it) for it in args]

    args_repr = " ".join((f'"[cyan]{s}[/cyan]"' for s in str_args))

    def append_to_log(path: Path) -> None:
        with path.open("a") as file:
            file.write(f"""
{"*" * 120}
cwd : {cwd}
args: {args}
cmd:  {cmd}
{"*" * 120}


""")
            file.flush()

    if append_stderr_debug:
        append_to_log(stderr_debug)

    if append_stdout_debug:
        append_to_log(stdout_debug)

    logger.debug(
        f"Running [red]{cmd}[/red] {args_repr}"
        + (f" in [green]{cwd}[/green]" if cwd else "")
        + (f" with [purple]{env}[/purple]" if env else "")
    )

    if ctx.config.dryrun:
        logger.warning("Dry run, early exit")
        return (0, "", "")

    str_cwd = str(cwd) if cwd else None

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

    _write_debug_outputs(
        result=result,
        stdout_debug=stdout_debug,
        stderr_debug=stderr_debug,
        append_stdout_debug=append_stdout_debug,
        append_stderr_debug=append_stderr_debug,
    )

    if result.retcode != 0:
        _consume_execution_fail(
            cmd=str(cmd),
            args=str_args,
            stdout_debug=stdout_debug,
            stderr_debug=stderr_debug,
            stdout=result.stdout,
            stderr=result.stderr,
            allow_fail=allow_fail,
        )

    elif ctx.config.log_level == HaxorgLogLevel.VERBOSE:
        if stdout_debug and result.stdout:
            logger.debug(f"Wrote stdout to {stdout_debug}")

        if stderr_debug and result.stderr:
            logger.debug(f"Wrote stderr to {stderr_debug}")

    return (result.retcode, result.stdout, result.stderr)


@beartype
def run_command_with_json_args(
    ctx: TaskContext,
    cmd: str | Path,
    args: Dict[str, Any],
    json_file_path: Optional[Path] = None,
    **kwargs: Unpack[RunCommandKwargs],
) -> tuple[int, str, str]:
    import json

    if json_file_path:
        json_file_path.write_text(json.dumps(args, indent=2))
        return run_command(ctx, cmd, [str(json_file_path)], **kwargs)

    else:
        return run_command(ctx, cmd, [json.dumps(args)], **kwargs)
