from plumbum import local, ProcessExecutionError, FG
import plumbum
from py_scriptutils.script_logging import log
from pathlib import Path
import os
from invoke import task, Failure
from invoke.context import Context
from beartype.typing import Optional, List, Union, Literal
from shutil import which, rmtree
from py_scriptutils.files import FileOperation
from py_scriptutils.tracer import GlobCompleteEvent, GlobExportJson, getGlobalTraceCollector
from functools import wraps
from beartype import beartype
from beartype.typing import Dict, List, Callable
import logging
from pprint import pprint
import textwrap
import json
import sys
import traceback
import itertools
from py_scriptutils.repo_files import HaxorgConfig, get_haxorg_repo_root_config
from py_repository.gen_coverage_cxx import ProfdataParams

graphviz_logger = logging.getLogger("graphviz._tools")
graphviz_logger.setLevel(logging.WARNING)
import graphviz

# Major version of the LLVM toolchain used for the project. This is not a configuration
# value, only as constant to avoid typing the same thing all over.
LLVM_MAJOR = "17"
LLVM_VERSION = f"{LLVM_MAJOR}.0.6"
CAT = "tasks"


def custom_traceback_handler(exc_type, exc_value, exc_traceback):
    """
    Custom traceback handler that filters and prints stack traces
    only for frames that originate from 'tasks.py'.
    """
    print("tasks traceback ----------------------")
    for frame in traceback.extract_tb(exc_traceback):
        log(CAT).error("File \"{}\", line {}, in {}  {}".format(
            frame.filename,
            frame.lineno,
            frame.name,
            frame.line,
        ))

    print(exc_type, exc_value)


# Register the custom traceback handler
sys.excepthook = custom_traceback_handler


def get_script_root(relative: Optional[str] = None) -> Path:
    current_script_path = os.path.abspath(__file__)
    value = Path(os.path.dirname(current_script_path)).resolve()
    if relative:
        value = value.joinpath(relative)
    return value


@beartype
def get_real_build_basename(ctx: Context, component: Literal["haxorg", "utils"]) -> str:
    """
    Get basename of the binary output directory for component
    """
    result = component + "_" + ("debug" if get_config(ctx).debug else "release")
    if get_config(ctx).instrument.coverage:
        result += "_instrumented"

    return result


@beartype
def get_component_build_dir(ctx: Context, component: Literal["haxorg", "utils"]) -> Path:
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


conf = get_haxorg_repo_root_config()


def get_config(ctx: Context) -> HaxorgConfig:
    return conf


def is_instrumented_coverage(ctx: Context) -> bool:
    return ctx.config.get("instrument")["coverage"]


def is_xray_coverage(ctx: Context) -> bool:
    return ctx.config.get("instrument")["xray"]


def is_forced(ctx: Context, name: str) -> bool:
    return name in get_config(ctx).force_task


@beartype
def is_ci() -> bool:
    return bool(os.getenv("INVOKE_CI"))


@beartype
def cmake_opt(name: str, value: Union[str, bool]) -> str:
    result = "-D" + name + "="
    if isinstance(value, str):
        result += value

    elif isinstance(value, bool):
        result += ("ON" if value else "OFF")

    return result


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


def run_command(
    ctx: Context,
    cmd: Union[str, Path],
    args: List[str],
    capture: bool = False,
    allow_fail: bool = False,
    env: dict[str, str] = {},
    cwd: Optional[str] = None,
) -> tuple[int, str, str]:
    if isinstance(cmd, Path):
        assert cmd.exists(), cmd
        cmd = str(cmd.resolve())

    args_repr = " ".join((f"'[cyan]{s}[/cyan]'" for s in args))

    log(CAT).debug(f"Running [red]{cmd}[/red] {args_repr}")

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
        run = run.with_cwd(cwd)

    try:
        if capture or get_config(ctx).quiet:
            retcode, stdout, stderr = run.run(
                tuple(args),
                retcode=None if allow_fail else 0,
            )
            return (retcode, stdout, stderr)

        else:
            run[*args] & FG
            return (0, "", "")

    except ProcessExecutionError as e:
        if allow_fail:
            return (1, "", "")

        else:
            raise Failure(f"Failed to execute the command {cmd}") from None


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


@beartype
def org_task(
    task_name: Optional[str] = None,
    pre: List[Callable] = [],
    force_notify: bool = False,
    **kwargs,
) -> Callable:

    def org_inner(func: Callable) -> Callable:
        TASK_DEPS[func] = pre

        @wraps(func)
        def wrapper(*args, **kwargs):
            name = task_name or func.__name__
            log(CAT).info(f"Running [yellow]{name}[/yellow] ...")
            run_ok = False
            try:
                with GlobCompleteEvent(f"task {name}", "build") as last:
                    result = func(*args, **kwargs)

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

        return task(wrapper, pre=pre, **kwargs)

    return org_inner


def get_cmake_defines(ctx: Context) -> List[str]:
    result: List[str] = []
    conf = get_config(ctx)

    result.append(cmake_opt("ORG_USE_COVERAGE", conf.instrument.coverage))
    result.append(cmake_opt("ORG_USE_XRAY", conf.instrument.xray))
    result.append(cmake_opt("ORG_USE_SANITIZER", conf.instrument.asan))
    result.append(
        cmake_opt("CMAKE_BUILD_TYPE", "Debug" if conf.debug else "RelWithDebInfo"))

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
def org_task_graph(ctx: Context, dot_file: str = "/tmp/graph.dot"):
    """Generate graphviz for task graph"""
    graph = create_graph(TASK_DEPS)
    with open(dot_file, "w") as file:
        file.write(graph.source)
        log(CAT).info(f"Wrote graph to {dot_file}")


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
def docker_image(ctx: Context):
    run_command(ctx, "docker", ["rm", HAXORG_DOCKER_IMAGE], allow_fail=True)
    run_command(ctx, "docker", [
        "build",
        "-t",
        HAXORG_DOCKER_IMAGE,
        "-f",
        get_script_root("scripts/py_repository/Dockerfile"),
        ".",
    ])


@org_task(pre=[docker_image])
def docker_run(
    ctx: Context,
    interactive: bool = False,
    build: bool = True,
    test: bool = True,
    docs: bool = True,
    coverage: bool = True,
):
    """Run docker"""

    def docker_path(path: str) -> Path:
        return Path("/haxorg").joinpath(path)

    def mnt(local: str, container: Optional[str] = None) -> List[str]:
        container = container or local
        local = Path(local) if Path(local).is_absolute() else get_script_root(local)
        return ["--mount", f"type=bind,src={local},dst={docker_path(container)}"]

    HAXORG_BUILD_TMP = Path("/tmp/haxorg_build_dir")
    if not HAXORG_BUILD_TMP.exists():
        HAXORG_BUILD_TMP.mkdir(parents=True)

    run_command(
        ctx,
        "docker",
        [
            "run",
            *itertools.chain(
                mnt(it) for it in [
                    "src",
                    "scripts",
                    "tests",
                    "tasks.py",
                    "docs",
                    "invoke.yaml",
                    "invoke-ci.yaml",
                    "pyproject.toml",
                    "ignorelist.txt",
                    ".git",
                    "thirdparty",
                    "CMakeLists.txt",
                ]),
            # Scratch directory for simplified local debugging and rebuilds if needed.
            *mnt(HAXORG_BUILD_TMP, "build"),
            *(["-it"] if interactive else []),
            "--rm",
            HAXORG_DOCKER_IMAGE,
            "./scripts/py_repository/poetry_with_deps.sh",
            *(["bash"] if interactive else [
                "invoke",
                "ci",
                # Because invoke has
                # - `No idea what 'False' is!`,
                # - `No idea what 'off' is!` and
                # - `No idea what 'false' is!`
                "--build" if build else "--no-build",
                "--test" if test else "--no-test",
                "--docs" if docs else "--no-docs",
                "--coverage" if coverage else "--no-coverage",
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


@org_task(pre=[base_environment])
def cmake_configure_utils(ctx: Context):
    """Execute configuration for utility binary compilation"""
    log(CAT).info("Configuring cmake utils build")
    run_command(
        ctx,
        "cmake",
        [
            "-B",
            get_component_build_dir(ctx, "utils"),
            "-S",
            str(get_script_root().joinpath("scripts/cxx_codegen")),
            "-G",
            "Ninja",
            f"-DCMAKE_BUILD_TYPE={'Debug' if get_config(ctx).debug else 'RelWithDebInfo'}",
            f"-DCMAKE_CXX_COMPILER={get_script_root('toolchain/llvm/bin/clang++')}",
        ],
    )


@org_task(task_name="Build cmake utils", pre=[cmake_configure_utils])
def cmake_utils(ctx: Context):
    """Compile libraries and binaries for utils"""
    log(CAT).info("Building build utils")
    run_command(ctx, "cmake", ["--build", get_component_build_dir(ctx, "utils")])
    log(CAT).info("CMake utils build ok")


REFLEX_PATH = "build/reflex"


@org_task(pre=[base_environment])
def reflex_lexer_generator(ctx: Context):
    """Build reflex lexer generator"""
    expected = get_script_root(REFLEX_PATH)
    if not expected.exists():
        run_command(ctx, "cmake", [
            "-B",
            expected.parent,
            "-S",
            get_script_root("thirdparty/RE-flex"),
            "-DCMAKE_BUILD_TYPE=Release",
        ])

        run_command(ctx, "cmake", [
            "--build",
            expected.parent,
        ])


@org_task(pre=[base_environment, reflex_lexer_generator], force_notify=True)
def haxorg_base_lexer(ctx: Context):
    """Generate base lexer file definitions and compile them to C code"""
    py_file = get_script_root("src/base_lexer/base_lexer.py")
    gen_lexer = get_script_root("src/base_lexer/base_lexer.l")
    reflex_run_params = [
        "--fast",
        "--nodefault",
        # "--debug",
        "--case-insensitive",
        f"--outfile={get_script_root('src/base_lexer/base_lexer_gen.cpp')}",
        "--namespace=base_lexer",
        gen_lexer,
    ]
    with FileOperation.InTmp(
            input=[py_file, py_file.with_suffix(".yaml")],
            output=[gen_lexer],
            stamp_path=get_task_stamp("haxorg_base_lexer"),
            stamp_content=str(reflex_run_params),
    ) as op:
        if op.should_run():
            log(CAT).info(f"Generating base lexer for haxorg " +
                          op.explain("haxorg_base_lexer"))
            run_command(ctx, "poetry", ["run", py_file])
            run_command(
                ctx,
                get_script_root(REFLEX_PATH),
                reflex_run_params,
                env={"LD_LIBRARY_PATH": str(get_script_root("thirdparty/RE-flex/lib"))},
            )

            gen_lexer.touch()

        else:
            log(CAT).info("No changes in base lexer config")


@org_task()
def python_protobuf_files(ctx: Context):
    """Generate new python code from the protobuf reflection files"""
    proto_config = get_script_root(
        "scripts/cxx_codegen/reflection_tool/reflection_defs.proto")
    with FileOperation.InTmp(
        [proto_config],
            stamp_path=get_task_stamp("python-protobuf-files"),
    ) as op:
        explain = op.explain("python protobuf")
        forced = is_forced(ctx, "python_protobuf_files")
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
                "protoc",
                [
                    f"--plugin={protoc_plugin}",
                    "-I",
                    get_script_root("scripts/cxx_codegen"),
                    "--proto_path=" +
                    str(get_script_root("scripts/py_codegen/py_codegen/reflection_tool")),
                    "--python_betterproto_out=" + str(proto_lib),
                    proto_config,
                ],
            )
        else:
            log(CAT).info("Skipping protoc run " + explain)


@org_task(pre=[base_environment])
def cmake_configure_haxorg(ctx: Context):
    """Execute cmake configuration step for haxorg"""

    with FileOperation.InTmp(
        [
            Path("CMakeLists.txt"),
            Path("src/cmake").rglob("*.cmake"),
        ],
            stamp_path=get_task_stamp("cmake_configure_haxorg"),
            stamp_content=str(get_cmake_defines(ctx)),
    ) as op:
        log(CAT).info(op.explain("cmake configuration"))
        if is_forced(ctx, "cmake_configure_haxorg") or op.should_run():
            log(CAT).info("running haxorg cmake configuration")
            pass_flags = [
                "-B",
                get_component_build_dir(ctx, "haxorg"),
                "-S",
                get_script_root(),
                "-G",
                "Ninja",
                f"-DCMAKE_CXX_COMPILER={get_llvm_root('bin/clang++')}",
                *get_cmake_defines(ctx),
            ]

            run_command(ctx, "cmake", tuple(pass_flags))


@org_task(pre=[cmake_configure_haxorg])
def cmake_haxorg(ctx: Context):
    """Compile main set of libraries and binaries for org-mode parser"""
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
            stamp_path=get_task_stamp("cmake_haxorg"),
            stamp_content=str(get_cmake_defines(ctx)),
    ) as op:
        if is_forced(ctx, "cmake_haxorg") or op.should_run():
            log(CAT).info(op.explain("Main C++"))
            run_command(ctx,
                        "cmake", ["--build", build_dir],
                        env={'NINJA_FORCE_COLOR': '1'})


LLDB_AUTO_BACKTRACE: List[str] = [
    "--one-line-on-crash", "bt", "--one-line-on-crash", "exit"
]


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


@org_task(pre=[cmake_haxorg])
def haxorg_code_forensics(ctx: Context, debug: bool = False):
    "Generate code forensics dump for the repository"
    tool = get_build_root("haxorg/scripts/cxx_repository/code_forensics")
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


@org_task(pre=[cmake_utils, python_protobuf_files])
def update_py_haxorg_reflection(
    ctx: Context,
    force: bool = False,
    verbose: bool = False,
):
    """Generate new source code reflection file for the python source code wrapper"""
    compile_commands = get_script_root("build/haxorg/compile_commands.json")
    include_dir = get_script_root(f"toolchain/llvm/lib/clang/{LLVM_MAJOR}/include")
    out_file = get_script_root("build/reflection.pb")
    src_file = "src/py_libs/pyhaxorg/pyhaxorg_manual_refl.cpp"

    with FileOperation.InTmp(
            input=[
                Path(path).rglob(glob)
                for path in ["src"]
                for glob in ["*.hpp", "*.cppm"]
            ],
            output=[out_file],
            stamp_path=get_task_stamp("update_py_haxorg_reflection"),
    ) as op:
        if force or (op.should_run() and not ctx.config.get("tasks")["skip_python_refl"]):
            exitcode, stdout, stderr = run_command(
                ctx,
                "build/utils/reflection_tool/reflection_tool",
                [
                    "-p",
                    compile_commands,
                    "--compilation-database",
                    compile_commands,
                    "--toolchain-include",
                    include_dir,
                    *(["--verbose"] if verbose else []),
                    "--out",
                    out_file,
                    src_file,
                ],
                capture=True,
                allow_fail=True,
            )

            Path("/tmp/debug_reflection_stdout.txt").write_text(stdout)
            Path("/tmp/debug_reflection_stderr.txt").write_text(stderr)

            if exitcode != 0:
                log(CAT).error("Reflection tool failed: %s")
                raise

            log(CAT).info("Updated reflection")

        else:
            log(CAT).info("Python reflection run not needed " +
                          op.explain("py haxorg reflection"))


# TODO Make compiled reflection generation build optional
@org_task(pre=[cmake_utils, update_py_haxorg_reflection])
def haxorg_codegen(ctx: Context, as_diff: bool = False):
    """Update auto-generated source files"""
    # TODO source file generation should optionally overwrite the target OR
    # compare the new and old source code (to avoid breaking the subsequent
    # compilation of the source)
    log(CAT).info("Executing haxorg code generation step.")
    run_command(ctx,
                "poetry", [
                    "run",
                    get_script_root("scripts/py_codegen/py_codegen/codegen.py"),
                    get_build_root(),
                    get_script_root(),
                ],
                env=get_py_env(ctx))

    log(CAT).info("Updated code definitions")


@org_task(pre=[cmake_haxorg])
def std_tests(ctx):
    """Execute standard library tests"""
    dir = get_build_root("haxorg")
    test = dir / "tests_hstd"
    run_command(ctx, test, [], cwd=str(dir))


@org_task(pre=[cmake_haxorg])
def org_tests(ctx):
    """Execute standard library tests"""
    dir = get_build_root("haxorg")
    test = dir / "tests_org"
    run_command(ctx, test, [], cwd=str(dir))


@beartype
def binary_coverage(ctx: Context, test: Path):
    dir = test.parent
    tools = get_llvm_root() / "bin"
    # Remove `.profdata` files
    for file in dir.glob("*.profdata"):
        file.unlink()

    assert dir.exists()
    run_command(ctx, test, [], allow_fail=True, cwd=str(dir))


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


@org_task(pre=[cmake_haxorg])
def org_test_perf(ctx: Context):
    """Generate performance sampling profile for tests"""

    tests = str(get_build_root("haxorg") / "tests_org")
    run = local["perf"]

    try:
        run["record", "--call-graph", "dwarf", tests] & FG
    except ProcessExecutionError:
        pass


@org_task(pre=[cmake_haxorg])
def std_xray(ctx: Context):
    """Generate test xray information for STD"""
    xray_coverage(ctx, get_build_root("haxorg") / "tests_hstd")


@org_task(pre=[cmake_haxorg])
def std_coverage(ctx: Context):
    """Generate test coverage information for STD"""
    binary_coverage(ctx, get_build_root("haxorg") / "tests_hstd")


@org_task(pre=[cmake_haxorg])
def org_coverage(ctx: Context):
    """Generate test coverage information for ORG"""
    binary_coverage(ctx, get_build_root("haxorg") / "tests_org")


@org_task(pre=[cmake_haxorg, cmake_utils, python_protobuf_files])
def py_cli(
    ctx: Context,
    arg: List[str] = [],
):
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


@task(iterable=["arg"])
def py_debug_script(ctx: Context, arg):
    run_command(
        ctx,
        "poetry",
        get_poetry_lldb(" ".join(arg)),
        allow_fail=True,
        env=get_py_env(ctx),
    )


@org_task(pre=[cmake_haxorg, cmake_utils, python_protobuf_files])
def py_test_debug(ctx: Context, test: str):
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


@org_task()
def symlink_build(ctx: Context):
    """
    Create proxy symbolic links around the build directory
    """

    def link(link_path: Path, real_path: Path, is_dir: bool):
        if link_path.exists():
            assert link_path.is_symlink(), link_path
            link_path.unlink()
            log(CAT).debug(f"'{link_path}' exists and is a symlink, removing")
            assert not link_path.exists(), link_path

        log(CAT).debug(f"'{link_path}'.symlink_to('{real_path}')")

        assert not link_path.exists(), link_path
        assert real_path.exists(), real_path

        link_path.symlink_to(target=real_path, target_is_directory=is_dir)

    link(
        real_path=get_component_build_dir(ctx, "haxorg"),
        link_path=get_build_root("haxorg"),
        is_dir=True,
    )

    link(
        real_path=get_component_build_dir(ctx, "utils"),
        link_path=get_build_root("utils"),
        is_dir=True,
    )


@org_task(pre=[haxorg_base_lexer, cmake_haxorg, cmake_utils])
def cmake_all(ctx: Context):
    """Build all binary artifacts"""
    pass


@beartype
def get_cxx_coverage_dir() -> Path:
    return get_build_root("coverage_artifacts")


@beartype
def get_cxx_profdata_params_path() -> Path:
    return get_cxx_coverage_dir().joinpath("profile-collect.json")


@beartype
def get_cxx_profdata_params() -> ProfdataParams:
    coverage_dir = get_cxx_coverage_dir()
    return ProfdataParams(
        coverage=str(coverage_dir.joinpath("test-summary.json")),
        coverage_db=str(coverage_dir.joinpath("coverage.sqlite")),
        perf_trace=str(coverage_dir.joinpath("coverage_merge.pftrace")),
        debug_file=str(coverage_dir.joinpath("coverage_debug.json")),
        file_whitelist=[".*"],
        file_blacklist=[
            "thirdparty",
            r"base_lexer_gen\.cpp",
        ],
    )


@org_task(pre=[cmake_utils])
def cxx_merge_coverage(ctx: Context):
    profile_path = get_cxx_profdata_params_path()
    run_command(
        ctx,
        "build/utils/profdata_merger/profdata_merger",
        [
            profile_path,
        ],
    )


@org_task(pre=[cmake_all, python_protobuf_files, symlink_build], iterable=["arg"])
def py_tests(ctx: Context, arg: List[str] = []):
    """
    Execute the whole python test suite or run a single test file in non-interactive
    LLDB debugger to work on compiled component issues. 
    """

    args = arg

    env = get_py_env(ctx)

    if is_instrumented_coverage(ctx):
        coverage_dir = get_cxx_coverage_dir()
        env["HAX_COVERAGE_OUT_DIR"] = str(coverage_dir)
        profile_path = get_cxx_profdata_params_path()
        log(CAT).info(f"Profile collect options: {profile_path}")
        profile_path.parent.mkdir(parents=True, exist_ok=True)
        profile_path.write_text(get_cxx_profdata_params().model_dump_json(indent=2))

    run_command(ctx, "poetry", [
        "run",
        "python",
        "scripts/py_repository/py_repository/gen_coverage_cxx.py",
    ])

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
            # "--cov-branch",
            *args,
        ],
        allow_fail=True,
        env=env,
    )

    if retcode != 0:
        exit(1)


@org_task(pre=[cmake_all, python_protobuf_files, symlink_build], iterable=["arg"])
def py_script(ctx: Context, script: str, arg: List[str] = []):
    run_command(ctx, "poetry", [
        "run",
        script,
        *arg,
    ])


@org_task(pre=[py_tests])
def py_tests_ci(ctx: Context):
    """
    CI task that builds base lexer codegen before running the build 
    """
    pass


@org_task()
def docs_doxygen(ctx: Context):
    "Build docunentation for the project using doxygen"
    out_dir = get_script_root("docs/docs_out/doxygen")
    if not out_dir.exists():
        out_dir.mkdir(parents=True)

    run_command(ctx, "doxygen", [str(get_script_root("docs/Doxyfile"))])
    log(CAT).info("Completed CXX docs build")


@org_task()
def docs_custom(ctx: Context):
    """Build documentation for the project using custom script"""
    out_dir = get_script_root("docs/custom_html")
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
    ]

    # prof_params = get_cxx_profdata_params()
    # if Path(prof_params.coverage_db).exists():
    #     args.append(f"--cxx_coverage_path={prof_params.coverage_db}")

    run_command(ctx, "poetry", args)


@org_task()
def ci(
    ctx: Context,
    build: bool = True,
    test: bool = True,
    docs: bool = True,
    coverage: bool = True,
):
    "Execute all CI tasks"
    env = {"INVOKE_CI": "ON"}
    if build:
        run_command(
            ctx,
            "invoke",
            ["cmake-all"],
            env=env,
        )

    if test:
        python_protobuf_files(ctx)
        run_command(
            ctx,
            "invoke",
            [
                "py-tests",
                "--arg=-m",
                "--arg=not (unstable or x11)",
            ],
            env=env,
        )

    if coverage:
        run_command(
            ctx,
            "invoke",
            ["cxx-merge-coverage"],
            env=env,
        )

    if docs:
        run_command(
            ctx,
            "invoke",
            ["docs-custom"],
            env=env,
        )
