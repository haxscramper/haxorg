from plumbum import local, ProcessExecutionError, FG, BG, NOHUP
import plumbum
import re
from py_scriptutils.script_logging import log
from pathlib import Path
import os
from invoke import task, Failure
from invoke.context import Context
from invoke.tasks import Task
from beartype.typing import Optional, List, Union, Literal, Callable, Unpack, TypedDict
from shutil import which, rmtree
from py_scriptutils.files import FileOperation
from py_scriptutils.tracer import GlobCompleteEvent, GlobExportJson, getGlobalTraceCollector
from functools import wraps
from beartype import beartype
from beartype.typing import Dict, List, Callable, Iterable
import logging
from pprint import pprint
import textwrap
import json
import sys
import traceback
import itertools
from py_scriptutils.repo_files import HaxorgConfig
from py_repository.gen_coverage_cookies import ProfdataParams, ProfdataFullProfile, ProfdataCookie
from py_scriptutils.algorithm import remove_ansi, maybe_splice, cond
from py_scriptutils.toml_config_profiler import merge_dicts
from py_scriptutils import os_utils
import typing
import inspect
import copy
import shutil
import signal
import psutil
import subprocess
from py_ci.util_scripting import cmake_opt, get_j_cap, get_threading_count, haxorg_env, parse_haxorg_env
from py_ci.data_build import (
    get_emscripten_cmake_flags,
    get_external_deps_list,
    get_deps_install_config,
    CmakeCLIConfig,
    CmakeFlagConfig,
    CmakeOptConfig,
    ExternalDep,
)
from py_scriptutils.repo_files import (
    HaxorgConfig,
    HaxorgCoverageCookiePattern,
    HaxorgCoverageAggregateFilter,
)

from tempfile import TemporaryDirectory

graphviz_logger = logging.getLogger("graphviz._tools")
graphviz_logger.setLevel(logging.WARNING)
import graphviz

# Major version of the LLVM toolchain used for the project. This is not a configuration
# value, only as constant to avoid typing the same thing all over.
LLVM_MAJOR = "18"
LLVM_VERSION = "18.1.4"
CAT = "tasks"
HAXORG_VERSION = "1.0.0"
HAXORG_NAME = "haxorg"


def custom_traceback_handler(exc_type, exc_value, exc_traceback):
    """
    Custom traceback handler that filters and prints stack traces
    only for frames that originate from 'tasks.py'.
    """
    log(CAT).error("tasks traceback ----------------------")
    for frame in traceback.extract_tb(exc_traceback):
        log(CAT).error("File \"{}\", line {}, in {}  {}".format(
            frame.filename,
            frame.lineno,
            frame.name,
            frame.line,
        ))

    log(CAT).error(f"{exc_type}, {exc_value}")


# Register the custom traceback handler
sys.excepthook = custom_traceback_handler


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


def get_script_root(relative: Optional[str] = None) -> Path:
    current_script_path = os.path.abspath(__file__)
    value = Path(os.path.dirname(current_script_path)).resolve()
    if relative:
        value = value.joinpath(relative)
    return value


@beartype
def filter_cookies(
    cookies: List[ProfdataCookie],
    aggregate_filter: HaxorgCoverageAggregateFilter | None,
) -> List[ProfdataCookie]:
    if not aggregate_filter or not aggregate_filter.whitelist_patterns:
        return []

    filtered_cookies = []

    for cookie in cookies:
        # Check whitelist
        if any(
                matches_pattern(cookie, pattern)
                for pattern in aggregate_filter.whitelist_patterns):
            # Check blacklist
            if not any(
                    matches_pattern(cookie, pattern)
                    for pattern in aggregate_filter.blacklist_patterns):
                filtered_cookies.append(cookie)

    return filtered_cookies


@beartype
def matches_pattern(cookie: ProfdataCookie, pattern: HaxorgCoverageCookiePattern) -> bool:
    if pattern.binary_pattern and not re.search(pattern.binary_pattern,
                                                cookie.test_binary):
        return False

    if pattern.name_pattern and not re.search(pattern.name_pattern, cookie.test_name):
        return False

    if pattern.class_pattern:
        if cookie.test_class is None:
            return False
        if not re.search(pattern.class_pattern, cookie.test_class):
            return False

    return True


@beartype
def get_real_build_basename(ctx: Context, component: str) -> str:
    """
    Get basename of the binary output directory for component
    """
    result = component + "_" + ("debug" if get_config(ctx).debug else "release")
    if get_config(ctx).emscripten:
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


def get_task_stamp(name: str) -> Path:
    return get_build_root().joinpath(f"stamps/{name}.stamp")


def get_llvm_root(relative: Optional[str] = None) -> Path:
    value = get_script_root().joinpath("toolchain/llvm")
    if relative:
        value = value.joinpath(relative)

    return value


from py_scriptutils.script_logging import pprint_to_file, to_debug_json

CONFIG_CACHE: Optional[HaxorgConfig] = None


def get_config(ctx: Context) -> HaxorgConfig:
    global CONFIG_CACHE
    if CONFIG_CACHE:
        return CONFIG_CACHE

    else:
        res_dict = dict()

        def aux(it):
            match it:
                case bool() | None | str() | type():
                    return it

                case list():
                    return [aux(i) for i in it]

                case _:
                    out = dict()
                    for key in it:
                        out[key] = aux(it[key])

                    return out

        ctx_dict = aux(ctx.config)

        env_dict = parse_haxorg_env()
        log(CAT).info(f"Parsed haxorg env variables")
        print(json.dumps(to_debug_json(env_dict), indent=2))
        res_dict = merge_dicts([ctx_dict, env_dict])
        log(CAT).info(f"Final parsed dictionary")
        print(json.dumps(to_debug_json(res_dict), indent=2))

        CONFIG_CACHE = HaxorgConfig(**res_dict)

        return CONFIG_CACHE


def is_instrumented_coverage(ctx: Context) -> bool:
    return get_config(ctx).instrument.coverage


def is_xray_coverage(ctx: Context) -> bool:
    return get_config(ctx).instrument.xray


def is_forced(ctx: Context, name: str) -> bool:
    return name in get_config(ctx).force_task or get_config(ctx).forceall


@beartype
def is_ci() -> bool:
    return bool(os.getenv("INVOKE_CI"))


@beartype
def invoke_opt(name: str, value: bool) -> str:
    match value:
        case bool():
            # Because invoke has
            # - `No idea what 'False' is!`,
            # - `No idea what 'off' is!` and
            # - `No idea what 'false' is!`
            if value:
                return f"--{name}"

            else:
                return f"--no-{name}"

        case _:
            raise TypeError(type(value))


def get_py_env(ctx: Context) -> Dict[str, str]:
    if get_config(ctx).instrument.asan:
        asan_lib = get_llvm_root(
            f"lib/clang/{LLVM_MAJOR}/lib/x86_64-unknown-linux-gnu/libclang_rt.asan.so")

        assert asan_lib.exists(), asan_lib

        return {
            "LD_PRELOAD": str(asan_lib),
            "ASAN_OPTIONS": "detect_leaks=0",
        }

    else:
        return {}


@beartype
def get_log_dir() -> Path:
    res = get_build_root().joinpath("logs")
    ensure_existing_dir(res)
    return res


@beartype
def get_cmd_debug_file(kind: str):
    return get_log_dir().joinpath(f"{TASK_STACK[-1]}_{kind}.txt")


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


@beartype
def run_command(
    ctx: Context,
    cmd: Union[str, Path],
    args: List[Union[str, Path, Task]],
    capture: bool = False,
    allow_fail: bool = False,
    env: dict[str, str] = {},
    cwd: Optional[Union[str, Path]] = None,
    stderr_debug: Optional[Path] = None,
    stdout_debug: Optional[Path] = None,
    append_stdout_debug: bool = False,
    append_stderr_debug: bool = False,
    run_mode: Literal["nohup", "bg", "fg"] = "fg",
) -> tuple[int, str, str]:
    stderr_debug = stderr_debug or get_cmd_debug_file("stderr")
    stdout_debug = stdout_debug or get_cmd_debug_file("stdout")
    if isinstance(cmd, Path):
        assert cmd.exists(), cmd
        cmd = str(cmd.resolve())

    if cmd == "invoke" and not isinstance(args[0], Task):
        assert False, f"command name for `invoke` recursive call should be passed as a function name but got {str(args)}"

    def conv_arg(arg) -> str:
        if isinstance(arg, Task):
            return arg.name.replace("_", "-")

        elif isinstance(arg, Path):
            return str(arg)

        else:
            return arg

    args: List[str] = [conv_arg(it) for it in args]

    args_repr = " ".join((f"\"[cyan]{s}[/cyan]\"" for s in args))

    def append_to_log(path: Path):
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

    try:
        run = local[cmd]

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
                [str(cmd), *args],
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
        if get_config(ctx).quiet:
            retcode, stdout, stderr = run.run(list(args), retcode=None)

        else:
            retcode, stdout, stderr = run[*args] & plumbum.TEE(retcode=None)

        @beartype
        def write_file(path: Path, append: bool, text: str):
            if append:
                if not path.exists():
                    path.write_text("")

                with path.open("a") as file:
                    file.write(remove_ansi(text))
                    file.flush()

            else:
                path.write_text(remove_ansi(text))

        if stdout_debug and stdout:
            log(CAT).info(f"Wrote stdout to {stdout_debug}")
            write_file(stdout_debug, append_stdout_debug, stdout)

        if stderr_debug and stderr:
            log(CAT).info(f"Wrote stderr to {stderr_debug}")
            write_file(stderr_debug, append_stderr_debug, stderr)

        if allow_fail or retcode == 0:
            return (retcode, stdout, stderr)

        else:
            raise Failure("Failed to execute the command {} {}{}{}".format(
                cmd,
                " ".join((f"\"{s}\"" for s in args)),
                f"\nwrote stdout to {stdout_debug}" if (stdout_debug and stdout) else "",
                f"\nwrote stderr to {stderr_debug}" if (stderr_debug and stderr) else "",
            )) from None


@beartype
def run_self(
    ctx: Context,
    args: List[str | Task | Path],
    capture: bool = False,
    allow_fail: bool = False,
    env: dict[str, str] = {},
    cwd: Optional[str] = None,
) -> tuple[int, str, str]:
    return run_command(
        ctx,
        "invoke",
        args,
        capture=capture,
        allow_fail=allow_fail,
        env=env,
        cwd=cwd,
    )


@beartype
def run_cmake(
    ctx: Context,
    args: List[str | Path],
    **kwargs: Unpack[RunCommandKwargs],
) -> tuple[int, str, str]:
    return run_command(ctx, "cmake", args, **kwargs)


@beartype
def run_cmake_configure_component(
    ctx: Context,
    component: str,
    script_path: str,
    args: List[str | Path] = [],
    **kwargs: Unpack[RunCommandKwargs],
) -> tuple[int, str, str]:
    return run_cmake(
        ctx,
        [
            "-B",
            get_component_build_dir(ctx, component),
            "-S",
            get_script_root(script_path),
            cmake_opt("CMAKE_TOOLCHAIN_FILE", get_toolchain_path(ctx)),
            cmake_opt("ORG_USE_COVERAGE",
                      get_config(ctx).instrument.coverage),
            "-G",
            "Ninja",
        ] + args,
        **kwargs,
    )


@beartype
def run_cmake_build_component(
    ctx: Context,
    component: str,
    targets: List[str] = ["all"],
    args: List[str | Path] = [],
    **kwargs: Unpack[RunCommandKwargs],
) -> tuple[int, str, str]:
    return run_cmake(
        ctx,
        [
            "--build",
            get_component_build_dir(ctx, component),
            "--target",
            *targets,
        ] + args,
        **kwargs,
    )


@beartype
def ui_notify(message: str, is_ok: bool = True):
    try:
        cmd = local["notify-send"]
        cmd.run(
            [message] if is_ok else ["--urgency=critical", "--expire-time=1000", message])

    except Exception:
        if is_ok:
            log(CAT).info(message)

        else:
            log(CAT).error(message)


TASK_DEPS: Dict[Callable, List[Callable]] = {}
TASK_STACK: List[str] = []


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


def get_toolchain_path(ctx: Context) -> Path:
    if get_config(ctx).emscripten:
        return Path("/usr/lib/emscripten/cmake/Modules/Platform/Emscripten.cmake")

    else:
        return get_script_root().joinpath("toolchain.cmake")


def get_cmake_defines(ctx: Context) -> List[str]:
    result: List[str] = []
    conf = get_config(ctx)

    result.append(cmake_opt("ORG_USE_COVERAGE", conf.instrument.coverage))
    result.append(cmake_opt("ORG_USE_XRAY", conf.instrument.xray))
    result.append(cmake_opt("ORG_USE_SANITIZER", conf.instrument.asan))
    result.append(cmake_opt("ORG_USE_PERFETTO", conf.instrument.perfetto))
    result.append(
        cmake_opt("CMAKE_BUILD_TYPE", "Debug" if conf.debug else "RelWithDebInfo"))

    result.append(cmake_opt("SQLITECPP_RUN_CPPLINT", False))

    result.append(cmake_opt("ORG_FORCE_ADAPTAGRAMS_BUILD", False))
    result.append(cmake_opt("ORG_DEPS_INSTALL_ROOT", get_deps_install_dir(ctx)))
    result.append(cmake_opt("CMAKE_EXPORT_COMPILE_COMMANDS", True))

    if conf.emscripten:
        result.append(cmake_opt("CMAKE_TOOLCHAIN_FILE", get_toolchain_path(ctx)))
        result.append(cmake_opt("ORG_DEPS_USE_PROTOBUF", False))
        result.append(cmake_opt("ORG_EMCC_BUILD", True))
        # result.append(cmake_opt("CMAKE_SIZEOF_VOID_P", "4"))
        # result.append(cmake_opt("CMAKE_SYSTEM_PROCESSOR", "wasm32"))

        for flag in get_emscripten_cmake_flags():
            result.append(cmake_opt(flag.name, flag.value))

    else:
        result.append(cmake_opt("ORG_EMCC_BUILD", False))
        result.append(cmake_opt("CMAKE_CXX_COMPILER", get_llvm_root("bin/clang++")))
        result.append(cmake_opt("ORG_DEPS_USE_PROTOBUF", True))

    debug = False
    if debug:
        result.append(cmake_opt("CMAKE_FIND_DEBUG_MODE", True))
        result.append("--trace")
        result.append("--trace-expand")

    else:
        result.append(cmake_opt("CMAKE_FIND_DEBUG_MODE", False))

    return result


@beartype
def create_graph(call_map: Dict[Callable, List[Callable]]) -> graphviz.Digraph:
    dot = graphviz.Digraph(comment='Function Call Graph')
    dot.attr(rankdir="LR")

    for func, callees in call_map.items():
        func_name = func.__name__
        task_name = func_name.replace("_", "-")
        if func.__doc__:
            doc_text = "<BR/>".join(textwrap.wrap(func.__doc__, width=50))
            func_label = f"<<B>{task_name}</B><BR/><FONT POINT-SIZE='10'>{doc_text}</FONT>>"

        else:
            func_label = task_name

        dot.node(func_name, label=func_label, shape='rectangle', fontname='Iosevka')

        for callee in callees:
            callee_name = callee.__name__
            dot.node(callee_name, shape='rectangle', fontname='Iosevka')
            dot.edge(callee_name, func_name)

    return dot


@org_task()
def generate_org_task_graph(ctx: Context, dot_file: str = "/tmp/graph.dot"):
    """Generate graphviz for task graph"""
    graph = create_graph(TASK_DEPS)
    file = Path(dot_file)
    file.write_text(graph.source)
    log(CAT).info(f"Wrote graph to {dot_file}")
    run_command(ctx, "dot", [
        "-Tpng",
        file,
        "-o",
        file.with_suffix(".png"),
    ])


@org_task()
def git_init_submodules(ctx: Context):
    """Init submodules if missing"""
    if get_script_root().joinpath("thirdparty/mp11").exists():
        log(CAT).info("Submodules were checked out")
    else:
        log(CAT).info("Submodules were not checked out, running update")
        run_command(ctx, "git",
                    ["submodule", "update", "--init", "--recursive", "--progress"])


HAXORG_DOCKER_IMAGE = "docker-haxorg"


@org_task()
def build_docker_develop_image(ctx: Context):
    run_command(ctx, "docker", ["rm", HAXORG_DOCKER_IMAGE], allow_fail=True)
    run_command(ctx, "docker", [
        "build",
        "-t",
        HAXORG_DOCKER_IMAGE,
        "-f",
        get_script_root("scripts/py_repository/Dockerfile"),
        ".",
    ])


@beartype
def docker_path(path: str) -> Path:
    return Path("/haxorg").joinpath(path)


@beartype
def docker_mnt(src: Path, dst: Path) -> List[str]:
    assert src.exists(), f"'{src}'"
    log(CAT).debug(f"Mounting docker '{src}' to '{dst}'")
    return ["--mount", f"type=bind,src={src},dst={dst}"]


@beartype
def docker_user() -> List[str]:
    return ["--user", f"{os.getuid()}:{os.getgid()}"]


@org_task(pre=[build_docker_develop_image])
def run_docker_develop_test(
    ctx: Context,
    interactive: bool = False,
    build: bool = True,
    test: bool = True,
    docs: bool = True,
    coverage: bool = True,
    reflection: bool = True,
    deps_configure: bool = True,
    deps_build: bool = True,
    build_dir: str = "/tmp/haxorg_build_dir",
    example: bool = True,
    install: bool = True,
):
    """Run docker"""

    HAXORG_BUILD_TMP = Path(build_dir)
    if not HAXORG_BUILD_TMP.exists():
        HAXORG_BUILD_TMP.mkdir(parents=True)

    run_command(
        ctx,
        "docker",
        [
            "run",
            *itertools.chain(*(docker_mnt(
                src=get_script_root(it),
                dst=docker_path(it),
            ) for it in [
                "src",
                "scripts",
                "tests",
                "benchmark",
                "tasks.py",
                "examples",
                "docs",
                "pyproject.toml",
                "ignorelist.txt",
                ".git",
                "thirdparty",
                "CMakeLists.txt",
                "toolchain.cmake",
                "HaxorgConfig.cmake.in",
            ])),
            # Scratch directory for simplified local debugging and rebuilds if needed.
            *docker_mnt(HAXORG_BUILD_TMP, docker_path("build")),
            *(["-it"] if interactive else []),
            "--memory=32G",
            "--rm",
            HAXORG_DOCKER_IMAGE,
            "./scripts/py_repository/poetry_with_deps.sh",
            *(["bash"] if interactive else [
                "invoke",
                "run-develop-ci",
                invoke_opt("build", build),
                invoke_opt("test", test),
                invoke_opt("docs", docs),
                invoke_opt("coverage", coverage),
                invoke_opt("reflection", reflection),
                invoke_opt("deps-configure", deps_configure),
                invoke_opt("deps-build", deps_build),
                invoke_opt("install", install),
                invoke_opt("example", example),
            ]),
        ])


@org_task()
def download_llvm(ctx: Context):
    """Download LLVM toolchain if missing"""
    llvm_dir = get_script_root("toolchain/llvm")
    if not os.path.isdir(llvm_dir):
        log(CAT).info("LLVM not found. Downloading...")
    else:
        log(CAT).info("LLVM already exists. Skipping download.")


@org_task(pre=[git_init_submodules, download_llvm])
def base_environment(ctx: Context):
    """Ensure base dependencies are installed"""
    pass


@beartype
def get_deps_tmp_dir(ctx: Context) -> Path:
    return get_build_root().joinpath(
        "deps_emcc" if get_config(ctx).emscripten else "deps_bin")


@beartype
def get_deps_install_dir(ctx: Context) -> Path:
    return get_deps_tmp_dir(ctx).joinpath("install")


@beartype
def get_deps_build_dir(ctx: Context) -> Path:
    return get_deps_tmp_dir(ctx).joinpath("build")

@beartype
def create_symlink(link_path: Path, real_path: Path, is_dir: bool):
    if link_path.exists():
        assert link_path.is_symlink(), link_path
        link_path.unlink()
        log(CAT).debug(f"'{link_path}' exists and is a symlink, removing")
        assert not link_path.exists(), link_path

    log(CAT).debug(f"'{link_path}'.symlink_to('{real_path}')")

    assert not link_path.exists(), link_path
    assert real_path.exists(), real_path

    link_path.symlink_to(target=real_path, target_is_directory=is_dir)

@org_task()
def symlink_build(ctx: Context):
    """
    Create proxy symbolic links around the build directory
    """

    create_symlink(
        real_path=get_component_build_dir(ctx, "haxorg"),
        link_path=get_build_root("haxorg"),
        is_dir=True,
    )

    create_symlink(
        real_path=get_component_build_dir(ctx, "haxorg"),
        link_path=get_script_root("examples").joinpath("js_test/haxorg_wasm"),
        is_dir=True,
    )


@org_task(pre=[symlink_build])
def generate_python_protobuf_files(ctx: Context):
    """Generate new python code from the protobuf reflection files"""
    proto_config = get_script_root(
        "scripts/cxx_codegen/reflection_tool/reflection_defs.proto")
    with FileOperation.InTmp(
        [proto_config],
            stamp_path=get_task_stamp("python-protobuf-files"),
    ) as op:
        explain = op.explain("python protobuf")
        forced = is_forced(ctx, "generate_python_protobuf_files")
        if forced or op.should_run():
            log(CAT).info(f"Running protc {explain}")
            _, stdout, _ = run_command(ctx,
                                       "poetry", ["env", "info", "--path"],
                                       capture=True)
            stdout = stdout.strip()
            log(CAT).info(f"Using protoc plugin path '{stdout}'")
            protoc_plugin = Path(stdout).joinpath("bin/protoc-gen-python_betterproto")

            if not protoc_plugin.exists():
                raise Failure(
                    f"Protoc plugin for better python is not installed correctly, {protoc_plugin} does not exist"
                )

            proto_lib = get_script_root("scripts/py_codegen/py_codegen/proto_lib")

            if not proto_lib.exists():
                proto_lib.mkdir()

            run_command(
                ctx,
                get_deps_install_dir(ctx).joinpath("protobuf/bin/protoc"),
                [
                    f"--plugin={protoc_plugin}",
                    "-I",
                    get_script_root("scripts/cxx_codegen"),
                    "--proto_path=" +
                    str(get_script_root("scripts/py_codegen/py_codegen/reflection_tool")),
                    "--python_betterproto_out=" + str(proto_lib),
                    proto_config,
                ],
                env=dict(LD_PRELOAD=""),
            )
        else:
            log(CAT).info("Skipping protoc run " + explain)


@org_task()
def validate_dependencies_install(ctx: Context):
    install_dir = get_deps_install_dir(ctx).joinpath("paths.cmake")
    assert install_dir.exists(), f"No dependency paths found at '{install_dir}'"


@org_task()
def generate_develop_deps_install_paths(ctx: Context):
    install_dir = get_deps_install_dir(ctx)
    ensure_existing_dir(install_dir)
    install_dir.joinpath("paths.cmake").write_text(
        get_deps_install_config(
            deps=get_external_deps_list(
                install_dir=install_dir,
                is_emcc=get_config(ctx).emscripten,
            ),
            install_dir=install_dir,
        ))


@org_task(pre=[base_environment, generate_develop_deps_install_paths])
def configure_cmake_haxorg(ctx: Context, force: bool = False):
    """Execute cmake configuration step for haxorg"""

    with FileOperation.InTmp(
        [
            Path("CMakeLists.txt"),
            *Path("src/cmake").rglob("*.cmake"),
        ],
            stamp_path=get_task_stamp("configure_cmake_haxorg"),
            stamp_content=str(get_cmake_defines(ctx)),
    ) as op:
        log(CAT).info(op.explain("cmake configuration"))
        if force or is_forced(ctx, "configure_cmake_haxorg") or op.should_run():
            log(CAT).info("running haxorg cmake configuration")
            pass_flags = [
                "-B",
                get_component_build_dir(ctx, "haxorg"),
                "-S",
                get_script_root(),
                "-G",
                "Ninja",
                *get_cmake_defines(ctx),
                cmake_opt("ORG_CPACK_PACKAGE_VERSION", HAXORG_VERSION),
                cmake_opt("ORG_CPACK_PACKAGE_NAME", HAXORG_NAME),
                cmake_opt("ORG_DEPS_INSTALL_ROOT", get_deps_install_dir(ctx)),
                *cond(
                    get_config(ctx).python_version,
                    [
                        cmake_opt("ORG_DEPS_USE_PYTHON_VERSION",
                                  get_config(ctx).python_version)
                    ],
                    [],
                ),
            ]

            import shlex
            Path("/tmp/cmake_configure_haxorg_flags.txt").write_text(
                shlex.join([str(s) for s in pass_flags[6:]]))
            run_command(ctx, "cmake", pass_flags)


@org_task()
def run_cmake_haxorg_clean(ctx: Context):
    """Clean build directory for the current configuration"""
    build_dir = get_component_build_dir(ctx, "haxorg")
    if build_dir.joinpath("CMakeCache.txt").exists():
        run_command(ctx, "cmake", [
            "--build",
            build_dir,
            "--target",
            "clean",
        ])

    adaptagrams_dir = build_dir.joinpath("libcola")
    import shutil
    if adaptagrams_dir.exists():
        shutil.rmtree(str(adaptagrams_dir))

    stamp_path = get_task_stamp("cmake_haxorg")
    if stamp_path.exists():
        stamp_path.unlink()

    os_utils.rmdir_quiet(get_build_root().joinpath("deps_build"))
    os_utils.rmdir_quiet(get_deps_install_dir())


@org_task(iterable=["build_whitelist"])
def build_develop_deps(
    ctx: Context,
    rebuild: bool = False,
    force: bool = False,
    build_whitelist: List[str] = [],
    configure: bool = True,
):
    "Install dependencies for cmake project development"
    conf = get_config(ctx)
    build_dir = get_deps_build_dir(ctx)
    ensure_existing_dir(build_dir)
    install_dir = get_deps_install_dir(ctx)
    ensure_existing_dir(install_dir)
    deps_dir = get_script_root().joinpath("thirdparty")

    dep_debug_stdout = get_cmd_debug_file("stdout")
    dep_debug_stderr = get_cmd_debug_file("stderr")

    debug_conf = dict(
        append_stderr_debug=True,
        append_stdout_debug=True,
        stdout_debug=dep_debug_stdout,
        stderr_debug=dep_debug_stderr,
    )

    @beartype
    def dep(item: ExternalDep):
        if 0 < len(build_whitelist) and item.build_name not in build_whitelist:
            return

        configure_args = list(
            itertools.chain(*[
                it.get_cli()
                for it in item.configure_args
                if isinstance(it, CmakeOptConfig) or not it.isBuild
            ]))

        log(CAT).info(f"Running build name='{item.build_name}' deps='{item.deps_name}'")
        if configure:
            run_command(
                ctx,
                "cmake",
                [
                    "-B",
                    build_dir.joinpath(item.build_name),
                    "-S",
                    deps_dir.joinpath(item.deps_name),
                    "-G",
                    "Ninja",
                    cmake_opt("CMAKE_INSTALL_PREFIX", install_dir.joinpath(
                        item.build_name)),
                    cmake_opt("CMAKE_BUILD_TYPE", "RelWithDebInfo"),
                    *([cmake_opt("CMAKE_TOOLCHAIN_FILE", get_toolchain_path(ctx))]
                      if item.is_bundled_toolchain else []),
                    *configure_args,
                    *maybe_splice(force, "--fresh"),
                ],
                **debug_conf,
            )

        build_args = list(
            itertools.chain(*[
                it.get_cli()
                for it in item.configure_args
                if isinstance(it, CmakeFlagConfig) and it.isBuild
            ]))

        run_command(
            ctx,
            "cmake",
            [
                "--build",
                build_dir.joinpath(item.build_name),
                "--target",
                "install",
                *get_j_cap(),
                *(["--", *build_args] if 0 < len(build_args) else []),
            ],
            **debug_conf,
        )

    if is_ci():
        run_command(ctx, "git", [
            "config",
            "--global",
            "--add",
            "safe.directory",
            deps_dir.joinpath("range-v3"),
        ])

    for item in get_external_deps_list(
            install_dir,
            is_emcc=get_config(ctx).emscripten,
    ):
        dep(item)

    log(CAT).info(f"Finished develop dependencies installation, {debug_conf}")
    generate_develop_deps_install_paths(ctx)
    log(CAT).info(f"Installed into {install_dir}")


@org_task(pre=[configure_cmake_haxorg], iterable=["target", "ninja_flag"])
def build_haxorg(ctx: Context, target: List[str] = ["all"], force: bool = False):
    """Compile main set of libraries and binaries for org-mode parser"""
    log(CAT).info(f"Using dependency dir {get_deps_install_dir(ctx)}")
    log(CAT).info(f"Building with\n{' '.join(get_cmake_defines(ctx))}")
    build_dir = get_component_build_dir(ctx, "haxorg")
    with FileOperation.InTmp(
        [
            Path(path).rglob(glob) for path in ["src", "scripts", "tests"] for glob in [
                "*.cpp",
                "*.hpp",
                "*.cppm",
                "*.cmake",
                "CMakeLists.txt",
            ]
        ],
            stamp_path=get_task_stamp("build_haxorg"),
            stamp_content=str(get_cmake_defines(ctx) + target),
    ) as op:
        pprint_to_file(
            to_debug_json(get_config(ctx)),
            "/tmp/config.py",
            width=240,
        )
        if force or is_forced(ctx, "build_haxorg") or op.should_run():
            log(CAT).info(op.explain("Main C++"))
            run_command(
                ctx,
                "cmake",
                [
                    "--build",
                    build_dir,
                    "--target",
                    *cond(0 < len(target), target, ["all"]),
                    *get_j_cap(),
                    *([
                        "--",
                        "-d",
                        "explain",
                    ] if is_ci() else []),
                ],
                env={'NINJA_FORCE_COLOR': '1'},
            )

        elif not op.should_run():
            log(CAT).info(f"Not running build {op.explain('build_haxorg')}")


@org_task(pre=[build_haxorg])
def install_haxorg_develop(ctx: Context, perfetto: bool = False):
    """Install haxorg targets in the build directory"""
    install_dir = get_build_root().joinpath("install")
    if install_dir.exists():
        shutil.rmtree(install_dir)

    run_command(
        ctx,
        "cmake",
        [
            "--install",
            get_component_build_dir(ctx, "haxorg"),
            "--prefix",
            install_dir,
            # cmake_opt("ORG_USE_PERFETTO", perfetto),
            # "--component",
            # "haxorg_component"
        ])


@org_task(pre=[configure_cmake_haxorg])
def build_release_archive(ctx: Context, force: bool = False):
    "Generate source archive"

    pack_res = get_script_root().joinpath("_CPack_Packages")
    log(CAT).info(f"Package tmp directory {pack_res}")
    if pack_res.exists():
        shutil.rmtree(str(pack_res))

    run_command(
        ctx,
        "cpack",
        [
            "--debug",
            # "--verbose",
            "--config",
            str(
                get_component_build_dir(ctx,
                                        "haxorg").joinpath("CPackSourceConfig.cmake")),
        ],
    )

    # else:
    #     log(CAT).debug(op.explain("cpack code"))


@org_task(pre=[validate_dependencies_install])
def configure_example_imgui_gui(ctx: Context):
    run_cmake_configure_component(
        ctx,
        "example_imgui_gui",
        "examples/imgui_gui",
    )


@org_task(pre=[configure_example_imgui_gui])
def build_example_imgui_gui(ctx: Context):
    run_cmake_build_component(
        ctx,
        "example_imgui_gui",
    )


@org_task(pre=[validate_dependencies_install])
def configure_example_qt_gui_org_viewer(ctx: Context):
    run_cmake_configure_component(
        ctx,
        "example_qt_gui_org_viewer",
        "examples/qt_gui/org_viewer",
    )


@org_task(pre=[configure_example_qt_gui_org_viewer])
def build_example_qt_gui_org_viewer(ctx: Context):
    run_cmake_build_component(
        ctx,
        "example_qt_gui_org_viewer",
    )


@org_task(pre=[build_example_qt_gui_org_viewer])
def build_example_qt_gui(ctx: Context):
    pass


@org_task(pre=[build_example_qt_gui, build_example_imgui_gui])
def build_examples(ctx: Context):
    pass


@org_task(pre=[build_release_archive])
def build_release_deps(
    ctx: Context,
    testdir: Optional[str] = None,
    deps_install_dir: Optional[str] = None,
):
    "Test cpack-provided build"

    package_archive = get_script_root().joinpath(
        f"{HAXORG_NAME}-{HAXORG_VERSION}-Source.zip")

    with TemporaryDirectory() as tmpdir:
        if testdir:
            build_dir = Path(testdir)

        else:
            build_dir = Path(tmpdir)

        if build_dir.exists():
            shutil.rmtree(build_dir)

        build_dir.mkdir(parents=True, exist_ok=True)
        package_copy = build_dir.joinpath("target.zip")

        shutil.copy(package_archive, package_copy)
        unzip = local["unzip"]
        unzip.run([
            str(package_copy),
            "-d",
            str(build_dir),
        ])

        log(CAT).info(f"Unzipped package to {build_dir}")
        src_root = build_dir.joinpath(f"{HAXORG_NAME}-{HAXORG_VERSION}-Source")
        src_build = build_dir.joinpath("build")

        install_dir = get_build_root().joinpath("deps_install")

        run_command(ctx, "cmake", [
            "-B",
            str(src_build),
            "-S",
            str(src_root),
            "-G",
            "Ninja",
            *cond(
                deps_install_dir,
                [cmake_opt("ORG_DEPS_INSTALL_ROOT", deps_install_dir)],
                [],
            ),
            cmake_opt("ORG_DEPS_USE_PROTOBUF", False),
            cmake_opt("ORG_BUILD_IS_DEVELOP", False),
            cmake_opt("ORG_BUILD_TESTS", True),
            cmake_opt("ORG_BUILD_ASSUME_CLANG", False),
            cmake_opt("CMAKE_CXX_COMPILER", "clang++"),
            cmake_opt("CMAKE_C_COMPILER", "clang"),
            cmake_opt("ORG_DEPS_USE_ADAPTAGRAMS", False),
            cmake_opt("ORG_DEPS_USE_PACKAGED_BOOST", False),
            cmake_opt("CMAKE_PREFIX_PATH", [
                install_dir.joinpath("lexy/lib/cmake/lexy"),
                install_dir.joinpath("abseil/lib/cmake/absl"),
                install_dir.joinpath("abseil/lib64/cmake/absl"),
            ]),
        ])

        log(CAT).info("Completed cpack build configuration")

        run_command(
            ctx,
            "cmake",
            [
                "--build",
                str(src_build),
                "--target",
                "all",
                *get_j_cap(),
            ],
            stderr_debug=get_log_dir().joinpath("cpack_build_stderr.log"),
            stdout_debug=get_log_dir().joinpath("cpack_build_stdout.log"),
        )


def clone_repo_with_uncommitted_changes(
    ctx: Context,
    src_repo: Path,
    dst_repo: Path,
):
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


@org_task(pre=[])
def run_docker_release_test(
    ctx: Context,
    build_dir: Optional[str] = None,
    clone_dir: Optional[str] = None,
    clone_code: Literal["none", "comitted", "all"] = "all",
):
    CPACK_TEST_IMAGE = "docker-haxorg-cpack"

    dep_debug_stdout = get_cmd_debug_file("stdout")
    dep_debug_stderr = get_cmd_debug_file("stderr")

    ensure_clean_file(dep_debug_stderr)
    ensure_clean_file(dep_debug_stdout)

    debug_conf = dict(
        append_stderr_debug=True,
        append_stdout_debug=True,
        stdout_debug=dep_debug_stdout,
        stderr_debug=dep_debug_stderr,
    )

    run_command(
        ctx,
        "docker",
        ["rm", CPACK_TEST_IMAGE],
        allow_fail=True,
        **debug_conf,
    )

    run_command(
        ctx,
        "docker",
        [
            "build",
            "-t",
            CPACK_TEST_IMAGE,
            "-f",
            get_script_root("scripts/py_repository/cpack_build_in_fedora.dockerfile"),
            ".",
        ],
        **debug_conf,
    )

    @beartype
    def run_docker(clone_dir: Path, build_dir: Path):
        source_prefix: Optional[Path] = None
        if clone_code == "all":
            if clone_dir.exists():
                shutil.rmtree(clone_dir)
            clone_repo_with_uncommitted_changes(
                ctx=ctx,
                src_repo=get_script_root(),
                dst_repo=clone_dir,
            )

            source_prefix = clone_dir

        elif clone_code == "comitted":
            if clone_dir.exists():
                shutil.rmtree(clone_dir)
            run_command(
                ctx,
                "git",
                ["clone", get_script_root(), clone_dir],
                **debug_conf,
            )
            source_prefix = clone_dir

        @beartype
        def pass_mnt(path: str) -> Path:
            if source_prefix:
                assert source_prefix.is_absolute(), source_prefix
                return source_prefix.joinpath(path)

            else:
                return get_script_root(path)

        run_command(
            ctx,
            "docker",
            [
                "run",
                *docker_mnt(
                    src=get_script_root("thirdparty"),
                    dst=docker_path("thirdparty"),
                ),
                *itertools.chain(*(docker_mnt(
                    src=pass_mnt(it),
                    dst=docker_path(it),
                ) for it in [
                    "src",
                    "scripts",
                    "CMakeLists.txt",
                    "HaxorgConfig.cmake.in",
                    "tests",
                    "benchmark",
                ])),
                "--memory=32G",
                "--rm",
                *docker_user(),
                *docker_mnt(build_dir or Path("/tmp"), Path("/haxorg_wip")),
                "-e",
                "PYTHONPATH=/haxorg/scripts/py_ci",
                CPACK_TEST_IMAGE,
                # "ls",
                # "-a",
                # "/haxorg_wip",
                "python",
                "-m",
                "py_ci.test_cpack_build",
            ],
            **debug_conf,
        )

    def run_with_build_dir(build_dir: Path):
        if clone_dir:
            log(CAT).info(f"Specified clone directory, using it for docker")
            run_docker(clone_dir=Path(clone_dir), build_dir=build_dir)

        else:
            with TemporaryDirectory() as dir:
                log(CAT).info(
                    f"No docker clone directory specified, using temporary {dir}")
                run_docker(clone_dir=Path(dir), build_dir=build_dir)

    if build_dir:
        if not Path(build_dir).exists():
            Path(build_dir).mkdir(parents=True)

        run_with_build_dir(build_dir=Path(build_dir))

    else:
        with TemporaryDirectory() as dir:
            run_with_build_dir(build_dir=Path(dir))


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


@org_task(pre=[build_haxorg])
def build_d3_example(ctx: Context):
    """
    Build d3.js visualization example
    """

    dir = get_script_root().joinpath("examples/d3_visuals")
    ensure_clean_dir(dir.joinpath("dist"))
    run_command(ctx, "deno", ["task", "build"], cwd=dir)


@org_task(pre=[build_d3_example])
def run_d3_example(ctx: Context, sync: bool = False):
    assert get_config(ctx).emscripten, "D3 example requires emscripten to be enabled"
    d3_example_dir = get_script_root().joinpath("examples/d3_visuals")
    deno_run = find_process("deno", d3_example_dir, ["task", "run-gui"])

    import time
    time.sleep(1)

    if not sync and deno_run:
        log(CAT).info("Sending user signal to electron")
        electron = find_process("electron", d3_example_dir)
        electron.send_signal(signal.SIGUSR1)

    else:
        run_command(
            ctx,
            "deno",
            ["task", "run-gui"],
            cwd=d3_example_dir,
            run_mode="fg" if sync else "nohup",
            stderr_debug=get_log_dir().joinpath("electron_stderr.log"),
            stdout_debug=get_log_dir().joinpath("electron_stdout.log"),
        )


@org_task(pre=[symlink_build])
def run_js_test_example(ctx: Context):
    assert get_config(ctx).emscripten, "JS example requires emscripten to be enabled"
    js_example_dir = get_script_root().joinpath("examples/js_test")

    run_command(
        ctx,
        "node",
        ["js_test.js"],
        cwd=js_example_dir,
    )


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


@org_task(pre=[build_haxorg])
def haxorg_code_forensics(ctx: Context, debug: bool = False):
    "Generate code forensics dump for the repository"
    tool = get_build_root("haxorg/code_forensics")
    config = {
        "repo": {
            "path": str(get_script_root()),
            "branch": "master"
        },
        "out": {
            "text_dump": "/tmp/code_forenics.txt"
        },
    }
    if debug:
        run_command(ctx, "lldb", [
            str(tool),
            "--batch",
            *get_lldb_py_import(),
            "-o",
            "run",
            *get_lldb_source_on_crash(),
            json.dumps(config),
        ])
    else:
        run_command(ctx, tool, [json.dumps(config)])


CODEGEN_TASKS = [
    "adaptagrams",
    "pyhaxorg",
]


@org_task(pre=[
    generate_python_protobuf_files,
    # cmake_haxorg,
])
def generate_reflection_snapshot(
    ctx: Context,
    verbose: bool = False,
):
    """Generate new source code reflection file for the python source code wrapper"""
    compile_commands = get_script_root("build/haxorg/compile_commands.json")
    toolchain_include = get_script_root(f"toolchain/llvm/lib/clang/{LLVM_MAJOR}/include")

    run_self(
        ctx,
        [
            build_haxorg,
            "--target=reflection_lib",
            "--target=reflection_tool",
            "--force",
        ],
    )

    with FileOperation.InTmp(
            input=[
                Path(path).rglob(glob)
                for path in ["src"]
                for glob in ["*.hpp", "*.cppm"]
            ],
            output=[get_build_root(f"{task}.pb") for task in CODEGEN_TASKS],
            stamp_path=get_task_stamp("generate_reflection_snapshot"),
    ) as op:
        if is_forced(ctx, "generate_reflection_snapshot") or (
                op.should_run() and not ctx.config.get("tasks")["skip_python_refl"]):
            for task in CODEGEN_TASKS:
                out_file = get_build_root(f"{task}.pb")
                match task:
                    case "pyhaxorg":
                        src_file = get_script_root(
                            "src/py_libs/pyhaxorg/pyhaxorg_manual_refl.cpp")

                    case "adaptagrams":
                        src_file = get_script_root(
                            "src/py_libs/py_adaptagrams/adaptagrams_ir_refl_target.cpp")

                run_command(
                    ctx,
                    "build/haxorg/scripts/cxx_codegen/reflection_tool/reflection_tool",
                    [
                        "-p",
                        compile_commands,
                        "--compilation-database",
                        compile_commands,
                        "--toolchain-include",
                        toolchain_include,
                        *(["--verbose"] if verbose else []),
                        "--out",
                        out_file,
                        src_file,
                    ],
                    stderr_debug=get_log_dir().joinpath(
                        f"debug_reflection_{task}_stderr.txt"),
                    stdout_debug=get_log_dir().joinpath(
                        f"debug_reflection_{task}_stdout.txt"),
                )

                log(CAT).info("Updated reflection")

        else:
            log(CAT).info("Python reflection run not needed " +
                          op.explain("py haxorg reflection"))


# TODO Make compiled reflection generation build optional
@org_task()
def generate_haxorg_sources(ctx: Context, tmp: bool = False, standalone: bool = False):
    """Update auto-generated source files"""
    # TODO source file generation should optionally overwrite the target OR
    # compare the new and old source code (to avoid breaking the subsequent
    # compilation of the source)
    log(CAT).info("Executing haxorg code generation step.")
    if not standalone:
        run_self(ctx, [build_haxorg, "--target=py_textlayout_cpp"])
        run_self(ctx, [generate_reflection_snapshot])
        run_self(ctx, [symlink_build])

    for task in CODEGEN_TASKS:
        run_command(
            ctx,
            "poetry",
            [
                "run",
                get_script_root("scripts/py_codegen/py_codegen/codegen.py"),
                "--reflection_path={}".format(get_build_root().joinpath(f"{task}.pb")),
                f"--codegen_task={task}",
                f"--tmp={tmp}",
            ],
            env=get_py_env(ctx),
        )

        log(CAT).info("Updated code definitions")


@beartype
def binary_coverage(ctx: Context, test: Path):
    dir = test.parent
    tools = get_llvm_root() / "bin"
    # Remove `.profdata` files
    for file in dir.glob("*.profdata"):
        file.unlink()

    assert dir.exists()
    run_command(ctx, test, [], allow_fail=True, cwd=str(dir))


@org_task(pre=[build_haxorg], iterable=["arg"])
def run_profdata_coverrage(
    ctx: Context,
    binary: str,
    arg: List[str] = [],
    report_path: Optional[str] = None,
):
    "Generate profdata coverage information for binary @arg binary"
    tools = get_llvm_root("bin")
    if Path(binary).is_absolute():
        bin_path = Path(binary)

    else:
        bin_path = get_component_build_dir(ctx, "haxorg").joinpath(binary)

    for file in bin_path.parent.glob("*.profdata"):
        file.unlink()

    for file in bin_path.parent.rglob("*.gcda"):
        file.unlink()

    dir = get_build_root().joinpath("profile")
    dir.mkdir(parents=True, exist_ok=True)
    current = Path().cwd()

    run_command(ctx, bin_path, args=arg)
    print(bin_path.parent)

    default_profraw = current / "default.profraw"
    result_profdata = dir / "bench.profdata"

    assert default_profraw.exists()

    run_command(ctx, tools / "llvm-profdata", [
        "merge",
        "-output=" + str(result_profdata),
        default_profraw,
    ])

    if report_path:
        report_dir = Path(report_path)

    else:
        report_dir = dir / bin_path.name

    if report_dir.exists():
        rmtree(report_dir)

    report_dir.mkdir(parents=True, exist_ok=True)

    run_command(ctx, tools / "llvm-cov", [
        "show",
        bin_path,
        "-instr-profile=" + str(result_profdata),
        "-format=html",
        "-output-dir=" + str(report_dir),
    ])


@beartype
def xray_coverage(ctx: Context, test: Path):
    dir = test.parent
    tools = get_llvm_root("bin")

    # Remove existing XRay log and profdata files
    for file in dir.glob(f"xray-log.{test.stem}.*"):
        file.unlink()

    for file in dir.glob("*.profdata"):
        file.unlink()

    log(CAT).info(f"Running XRAY log agregation for directory {dir}")
    run_command(
        ctx,
        test, [],
        env={"XRAY_OPTIONS": "patch_premain=true xray_mode=xray-basic verbosity=1"},
        allow_fail=True,
        capture=True,
        cwd=dir)

    # Find the latest XRay log file
    log_files = sorted(dir.glob(f"xray-log.{test.stem}.*"),
                       key=os.path.getmtime,
                       reverse=True)
    if log_files:
        log(CAT).info(f"Latest XRay log file '{log_files[0]}'")
        logfile = log_files[0]

        # Process log file with llvm-xray and llvm-profdata
        run_command(ctx, tools / "llvm-xray", [
            "convert",
            "--symbolize",
            "--instr_map=" + str(test),
            "--output-format=trace_event",
            "--output=" + str(dir / "trace_events.json"),
            logfile,
        ])

        run_command(ctx, tools / "llvm-xray", [
            "graph",
            "--instr_map=" + str(test),
            "--output=" + str(dir / "trace_events.dot"),
            logfile,
        ])

        run_command(ctx, tools / "llvm-profdata", [
            "merge",
            "-output=" + str(dir / "bench.profdata"),
            dir / "default.profraw",
        ])

        run_command(ctx, tools / "llvm-cov", [
            "show",
            test,
            "-instr-profile=" + str(dir / "bench.profdata"),
            "-format=html",
            "-output-dir=" + str(dir / "coverage_report"),
        ])
    else:
        raise Failure(
            f"No XRay log files found in '{dir}', xray coverage enabled in settings {is_xray_coverage(ctx)}"
        )


@org_task(pre=[build_haxorg])
def run_org_test_performance(ctx: Context):
    """Generate performance sampling profile for tests"""

    tests = str(get_build_root("haxorg") / "tests_org")
    run = local["perf"]

    try:
        run["record", "--call-graph", "dwarf", tests] & FG
    except ProcessExecutionError:
        pass


@org_task(pre=[build_haxorg, generate_python_protobuf_files])
def py_cli(
    ctx: Context,
    arg: List[str] = [],
):
    "Run haxorg CLI script"
    log(CAT).info(get_py_env(ctx))
    log(CAT).info(arg)
    run_command(
        ctx,
        "poetry",
        ["run", get_script_root("scripts/py_cli/haxorg.py"), *arg],
        env=get_py_env(ctx),
    )


def get_poetry_lldb(test: str) -> list[str]:
    return [
        "run",
        "lldb",  # NOTE using system-provided LLDB instead of the get_llvm_root("bin/lldb"),
        # because the latter one is not guaranteed to be compiled with the python
        # installed on the system. For example, 17.0.6 required python 3.10, but the
        # arch linux already moved to 3.11 here.
        "--batch",
        *get_lldb_py_import(),
        "-o",
        f"run {test}",
        *get_lldb_source_on_crash(),
        "--",
        "python",
    ]


@org_task(iterable=["arg"])
def run_py_debug_script(ctx: Context, arg):
    run_command(
        ctx,
        "poetry",
        get_poetry_lldb(" ".join(arg)),
        allow_fail=True,
        env=get_py_env(ctx),
    )


@org_task(pre=[build_haxorg, generate_python_protobuf_files])
def run_py_test_debug(ctx: Context, test: str):
    log(CAT).info(get_py_env(ctx))
    test: Path = Path(test)
    if not test.is_absolute():
        test = get_script_root(test)

    retcode, _, _ = run_command(
        ctx,
        "poetry",
        get_poetry_lldb(test),
        allow_fail=True,
        env=get_py_env(ctx),
    )

    if retcode != 0:
        exit(1)


def get_poetry_import_paths(ctx: Context) -> List[Path]:
    return [
        Path(it) for it in run_command(
            ctx,
            "poetry",
            ['run', 'python', '-c', 'import sys; print("\\n".join(sys.path))'],
            capture=True,
        )[1].split("\n") if 0 < len(it.strip())
    ]


@beartype
def get_cxx_coverage_dir() -> Path:
    return get_build_root("coverage_artifacts")


@beartype
def get_cxx_profdata_params_path() -> Path:
    return get_cxx_coverage_dir().joinpath("profile-collect.json")


HELP_profdata_file = {
    "profdata-file-whitelist":
        f"List of blacklist regexps to allow in the coverage database.",
    "profdata-file-blacklist":
        f"List of regexps to disallow in the coverage database."
}

HELP_coverage_file = {
    "coverage-file-whitelist": "List of regexps to allow in the final HTML output.",
    "coverage-file-blacklist": "List of regexps to filter out fo the final HTML output",
}


@beartype
def get_cxx_profdata_params(ctx: Context) -> ProfdataParams:
    coverage_dir = get_cxx_coverage_dir()
    stored_summary_collection = coverage_dir.joinpath("test-summary.json")
    summary_data: ProfdataFullProfile = ProfdataFullProfile.model_validate_json(
        stored_summary_collection.read_text())
    filtered_summary = ProfdataFullProfile(
        runs=filter_cookies(summary_data.runs,
                            get_config(ctx).aggregate_filters))
    filtered_summary_collection = coverage_dir.joinpath("test-summary-filtered.json")
    filtered_summary_collection.write_text(filtered_summary.model_dump_json(indent=2))
    return ProfdataParams(
        coverage=str(filtered_summary_collection),
        coverage_db=str(coverage_dir.joinpath("coverage.sqlite")),
        # perf_trace=str(coverage_dir.joinpath("coverage_merge.pftrace")),
        debug_file=str(coverage_dir.joinpath("coverage_debug.json")),
        file_whitelist=get_config(ctx).profdata_file_whitelist,
        file_blacklist=get_config(ctx).profdata_file_blacklist,
        run_group_batch_size=get_threading_count(),
    )


HELP_coverage_mapping_dump = {
    "coverage_mapping_dump":
        "Directory to dump JSON information for every processed coverage mapping object"
}


@beartype
def configure_cxx_merge(
    ctx: Context,
    coverage_mapping_dump: Optional[str] = None,
):
    if is_instrumented_coverage(ctx):
        profile_path = get_cxx_profdata_params_path()
        log(CAT).info(
            f"Profile collect options: {profile_path} coverage_mapping_dump = {coverage_mapping_dump}"
        )
        profile_path.parent.mkdir(parents=True, exist_ok=True)
        model = get_cxx_profdata_params()
        if coverage_mapping_dump:
            Path(coverage_mapping_dump).mkdir(exist_ok=True)
            model.coverage_mapping_dump = coverage_mapping_dump

        profile_path.write_text(model.model_dump_json(indent=2))


@org_task(
    pre=[build_haxorg],
    help={
        **HELP_profdata_file,
        **HELP_coverage_mapping_dump,
    },
)
def run_cxx_coverage_merge(
    ctx: Context,
    coverage_mapping_dump: Optional[str] = None,
):
    configure_cxx_merge(
        ctx,
        coverage_mapping_dump,
    )
    coverage_dir = get_cxx_coverage_dir()

    profile_path = get_cxx_profdata_params_path()
    run_command(
        ctx,
        "build/haxorg/profdata_merger",
        [
            profile_path,
        ],
        stderr_debug=coverage_dir.joinpath("profdata_merger_stderr.txt"),
        stdout_debug=coverage_dir.joinpath("profdata_merger_stdout.txt"),
    )


@org_task(pre=[build_haxorg, symlink_build, generate_python_protobuf_files],
          iterable=["arg"])
def run_py_tests(ctx: Context, arg: List[str] = []):
    """
    Execute the whole python test suite or run a single test file in non-interactive
    LLDB debugger to work on compiled component issues. 
    """

    args = arg

    env = get_py_env(ctx)
    if is_instrumented_coverage(ctx):
        coverage_dir = get_cxx_coverage_dir()
        env["HAX_COVERAGE_OUT_DIR"] = str(coverage_dir)

    run_command(
        ctx,
        "poetry",
        [
            "run",
            "python",
            "scripts/py_repository/py_repository/gen_coverage_cxx.py",
        ],
        env=get_py_env(ctx),
    )

    retcode, _, _ = run_command(
        ctx,
        "poetry",
        [
            "run",
            "pytest",
            "-vv",
            "-ra",
            "-s",
            "--tb=short",
            "--cov=scripts",
            "--cov-report=html",
            "--cov-context=test",
            "--disable-warnings",
            # "--cov-branch",
            *args,
        ],
        allow_fail=True,
        env=env,
    )

    if retcode != 0:
        exit(1)


@org_task(pre=[build_haxorg, generate_python_protobuf_files, symlink_build],
          iterable=["arg"])
def run_py_script(ctx: Context, script: str, arg: List[str] = []):
    """
    Run script with arguments with all environment variables set.
    Debug task. 
    """
    run_command(
        ctx,
        "poetry",
        [
            "run",
            script,
            *arg,
        ],
        env=get_py_env(ctx),
    )


@org_task(pre=[run_py_tests])
def run_py_tests_ci(ctx: Context):
    """
    CI task that builds base lexer codegen before running the build 
    """
    pass


@org_task()
def docs_doxygen(ctx: Context):
    "Build docunentation for the project using doxygen"
    out_dir = get_script_root("/tmp/doxygen")
    # if out_dir.exists():
    #     shutil.rmtree(out_dir)

    out_dir.mkdir(parents=True, exist_ok=True)

    run_command(
        ctx,
        "doxygen",
        [str(get_script_root("docs/Doxyfile"))],
        stdout_debug=get_build_root().joinpath("doxygen_stdout.log"),
        stderr_debug=get_build_root().joinpath("doxygen_stderr.log"),
        # run_mode="bg",
    )
    log(CAT).info("Completed CXX docs build")


@beartype
def get_list_cli_pass(list_name: str, args: Iterable[str]) -> List[str]:
    return [f"--{list_name}={arg}" for arg in args]


@org_task(
    iterable=["file_blacklist", "file_whitelist"],
    help={
        **HELP_coverage_file,
    },
)
def build_custom_docs(
    ctx: Context,
    coverage_file_whitelist: List[str] = [".*"],
    coverage_file_blacklist: List[str] = [],
    out_dir: str = "/tmp/docs_out",
):
    """Build documentation for the project using custom script"""
    out_dir = Path(out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)

    args = [
        "run",
        get_script_root("scripts/py_repository/py_repository/gen_documentation.py"),
        f"--html_out_path={out_dir}",
        f"--root_path={get_script_root()}",
        f"--src_path={get_script_root('src')}",
        f"--src_path={get_script_root('scripts')}",
        f"--py_coverage_path={get_script_root('.coverage')}",
        f"--test_path={get_script_root('tests')}",
        f"--profile_out_path={out_dir.joinpath('profile.json')}",
        *get_list_cli_pass("coverage_file_whitelist", coverage_file_whitelist),
        *get_list_cli_pass("coverage_file_blacklist", coverage_file_blacklist),
    ]

    prof_params = get_cxx_profdata_params()
    if Path(prof_params.coverage_db).exists():
        args.append(f"--cxx_coverage_path={prof_params.coverage_db}")
        log(CAT).info(f"Using coveage database from {prof_params.coverage_db}")
    else:
        log(CAT).info(
            f"No coverage database generated, {prof_params.coverage_db} does not exist")

    run_command(ctx, "poetry", args, env=get_py_env(ctx))


@org_task(
    iterable=[
        "file_whitelist",
        "file_blacklist",
    ],
    help={
        **HELP_profdata_file,
        **HELP_coverage_mapping_dump,
        **HELP_coverage_file,
    },
)
def cxx_target_coverage(
    ctx: Context,
    pytest_filter: Optional[str] = None,
    coverage_file_whitelist: List[str] = [".*"],
    coverage_file_blacklist: List[str] = [],
    out_dir: str = "/tmp/docs_out_targeted",
    run_tests: bool = True,
    run_merge: bool = True,
    run_docgen: bool = True,
    coverage_mapping_dump: Optional[str] = None,
    allow_test_fail: bool = False,
):
    """
    Run full cycle of the code coverage generation. 
    """

    if run_tests:
        if pytest_filter:
            run_self(
                ctx,
                [
                    run_py_tests,
                    f"--arg=--markfilter",
                    f"--arg={pytest_filter}",
                    "--arg=--markfilter-debug=True",
                ],
                allow_fail=allow_test_fail,
            )

        else:
            run_self(
                ctx,
                [run_py_tests],
                allow_fail=allow_test_fail,
            )

    if run_merge:
        if coverage_mapping_dump:
            run_self(ctx, [
                run_cxx_coverage_merge,
                f"--coverage-mapping-dump={coverage_mapping_dump}",
            ])
        else:
            run_self(ctx, [
                run_cxx_coverage_merge,
            ])

    if run_docgen:
        run_self(ctx, [
            build_custom_docs,
            f"--out-dir={out_dir}",
        ])


@org_task()
def run_develop_ci(
    ctx: Context,
    deps: bool = True,
    build: bool = True,
    test: bool = True,
    docs: bool = True,
    coverage: bool = True,
    reflection: bool = True,
    install: bool = True,
    example: bool = True,
    emscripten_deps: bool = True,
    emscripten_build: bool = True,
    emscripten_test: bool = True,
):
    "Execute all CI tasks"
    env = merge_dicts([
        haxorg_env(["ci"], True),
        haxorg_env(["forceall"], True),
    ])

    emscripten_env = merge_dicts([env, haxorg_env(["emscripten"], True)])

    if deps:
        log(CAT).info("Running CI dependency installation")
        run_self(ctx, [build_develop_deps], env=env)

    if install:
        log(CAT).info("Running install")
        run_self(
            ctx,
            [install_haxorg_develop],
            env=env,
        )

    if build:
        log(CAT).info("Running CI cmake")
        run_self(ctx, [build_haxorg], env=env)

    if reflection:
        log(CAT).info("Running CI reflection")
        run_self(
            ctx,
            [generate_haxorg_sources],
            env=env,
        )

    if test:
        log(CAT).info("Running CI tests")
        generate_python_protobuf_files(ctx)
        run_self(
            ctx,
            [
                run_py_tests,
                "--arg=-m",
                "--arg=not (unstable or x11)",
            ],
            env=env,
        )

    if example:
        log(CAT).info("Running CI cmake")
        run_self(ctx, [build_examples], env=env)

    if coverage:
        log(CAT).info("Running CI coverage merge")
        run_self(ctx, [run_cxx_coverage_merge], env=env)

    if docs:
        log(CAT).info("Running CI docs")
        run_self(ctx, [build_custom_docs], env=env)

    if emscripten_deps:
        run_self(ctx, [build_develop_deps], env=emscripten_env)

    if emscripten_build:
        run_self(ctx, [build_haxorg], env=emscripten_env)

    if emscripten_test:
        run_self(ctx, [run_js_test_example], env=emscripten_env)
