from beartype.typing import Dict, Callable, List, Optional
from beartype import beartype
from functools import wraps
from py_scriptutils.script_logging import log
from copy import copy
import typing
import inspect
import shutil

from invoke import task, Failure
from invoke.context import Context
from invoke.tasks import Task

from py_scriptutils.tracer import GlobCompleteEvent, GlobExportJson
from py_scriptutils.repo_files import get_haxorg_repo_root_path


from pathlib import Path

import os




CAT = __name__

def get_script_root(relative: Optional[str] = None) -> Path:
    value = get_haxorg_repo_root_path()
    if relative:
        value = value.joinpath(relative)
    return value


@beartype
def ensure_clean_dir(dir: Path):
    if dir.exists():
        shutil.rmtree(str(dir))

    dir.mkdir(parents=True, exist_ok=True)


@beartype
def ensure_existing_dir(dir: Path):
    dir.mkdir(parents=True, exist_ok=True)


@beartype
def ensure_clean_file(file: Path):
    ensure_existing_dir(file.parent)
    file.write_text("")



@beartype
def get_real_build_basename(ctx: Context, component: str) -> str:
    """
    Get basename of the binary output directory for component
    """
    result = component + "_" + ("debug" if get_config(ctx).debug else "release")
    if get_config(ctx).emscripten.build:
        result += "_emscripten"

    if get_config(ctx).instrument.coverage:
        result += "_instrumented"

    return result



@beartype
def get_component_build_dir(ctx: Context, component: str) -> Path:
    result = get_build_root(get_real_build_basename(ctx, component))
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
def get_build_tmpdir(ctx: Context, component: str) -> Path:
    result = get_build_root().joinpath("tmp").joinpath(
        get_real_build_basename(ctx, component))
    ensure_existing_dir(result)
    return result



TASK_DEPS: Dict[Callable, List[Callable]] = {}
TASK_STACK: List[str] = []

@beartype
def get_cmd_debug_file(kind: str):
    return get_log_dir().joinpath(f"{TASK_STACK[-1]}_{kind}.txt")

@beartype
def org_task(
        task_name: Optional[str] = None,
        pre: List[Callable] = [],
        force_notify: bool = False,
        pre_optional: List[Callable] = [],
        help=dict(),
        **kwargs,
) -> Callable:

    help_base = copy.copy(help)

    def org_inner(func: Callable) -> Callable:
        TASK_DEPS[func] = pre

        signature = inspect.signature(func)
        params = signature.parameters
        arg_names = [param.name for param in params.values()]
        type_annotations = typing.get_type_hints(func)

        updated_help = dict()

        for arg in arg_names:
            if arg in ["ctx"]:
                continue

            cli = arg.replace("_", "-")
            if arg in type_annotations:
                T = type_annotations[arg]
                if isinstance(T, (type(bool), type(int), type(float))):
                    description = ""

                else:
                    description = f"{str(T)}"

            else:
                description = ""

            if cli in help_base:
                if description:
                    description += " "

                description += f"{help_base[cli]}"

            updated_help[cli] = description

        @wraps(func)
        def wrapper(*args, **kwargs):
            name = task_name or func.__name__
            log(CAT).info(f"Running [yellow]{name}[/yellow] ...")
            run_ok = False
            try:
                with GlobCompleteEvent(f"task {name}", "build") as last:
                    assert os.getcwd() == str(get_script_root(
                    )), "Invoke tasks must be executed from the root directory"
                    TASK_STACK.append(name)
                    result = func(*args, **kwargs)
                    TASK_STACK.pop()

                run_ok = True

            finally:
                log(CAT).info(
                    f"Completed [green]{name}[/green] in [blue]{last.dur / 10e2:5.1f}[/blue]ms"
                )

                color = "green"
                name_format = f"<span color='#{color}'>{name:^40}</span>"
                if 100000 < last.dur or force_notify:
                    ui_notify(
                        f"DONE [<b>{name:^40}</b>] in {last.dur / 10e2:05.1f}ms",
                        is_ok=run_ok,
                    )

                GlobExportJson(get_build_root("task_build_time.json"))

            return result

        return task(wrapper, pre=pre, help=copy.copy(updated_help), **kwargs)

    return org_inner
