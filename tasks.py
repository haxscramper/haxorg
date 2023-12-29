from plumbum import local, ProcessExecutionError, FG
from py_scriptutils.script_logging import log
from pathlib import Path
import os
from invoke import task, Failure
from invoke.context import Context
from beartype.typing import Optional, List, Union
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

graphviz_logger = logging.getLogger("graphviz._tools")
graphviz_logger.setLevel(logging.WARNING)
import graphviz

# Major version of the LLVM toolchain used for the project. This is not a configuration
# value, only as constant to avoid typing the same thing all over.
LLVM_MAJOR = "17"
LLVM_VERSION = f"{LLVM_MAJOR}.0.6"


def get_script_root(relative: Optional[str] = None) -> Path:
    current_script_path = os.path.abspath(__file__)
    value = Path(os.path.dirname(current_script_path)).resolve()
    if relative:
        value = value.joinpath(relative)
    return value


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


def is_quiet(ctx: Context) -> bool:
    return ctx.config.get('quiet', False)


def is_debug(ctx: Context) -> bool:
    return ctx.config.get('debug', False)


def is_instrumented_coverage(ctx: Context) -> bool:
    return ctx.config.get("instrument")["coverage"]


def is_xray_coverage(ctx: Context) -> bool:
    return ctx.config.get("instrument")["xray"]


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

    else:
        assert which(cmd), cmd

    args_repr = " ".join((str(s) for s in args))

    log.debug(f"Running [red]{cmd}[/red] [cyan]{args_repr}[/cyan]")

    run = local[cmd]
    if env:
        run = run.with_env(**env)

    if cwd is not None:
        run = run.with_cwd(cwd)

    try:
        if capture or is_quiet(ctx):
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


TASK_DEPS: Dict[Callable, List[Callable]] = {}


@beartype
def org_task(task_name: Optional[str] = None, pre: List[Callable] = []) -> Callable:

    def org_inner(func: Callable) -> Callable:
        TASK_DEPS[func] = pre

        @wraps(func)
        def wrapper(*args, **kwargs):
            name = task_name or func.__name__
            log.info(f"Running [yellow]{name}[/yellow] ...")
            with GlobCompleteEvent(f"task {name}", "build"):
                result = func(*args, **kwargs)

            last = getGlobalTraceCollector().get_last_event()
            log.info(
                f"Completed [green]{name}[/green] in [blue]{last.dur / 10e3:5.1f}[/blue]ms"
            )

            GlobExportJson(get_build_root("task_build_time.json"))

            return result

        return task(wrapper, pre=pre)

    return org_inner


def get_cmake_defines(ctx: Context) -> List[str]:
    result: List[str] = []
    if is_instrumented_coverage(ctx):
        result.append("-DORG_USE_COVERAGE=ON")

    if is_xray_coverage(ctx):
        result.append("-DORG_USE_XRAY=ON")

    if is_debug(ctx):
        result.append("-DCMAKE_BUILD_TYPE=Debug")

    else:
        result.append("-DCMAKE_BUILD_TYPE=RelWithDebInfo")

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
    "Generate graphviz for task graph"
    graph = create_graph(TASK_DEPS)
    with open(dot_file, "w") as file:
        file.write(graph.source)
        log.info(f"Wrote graph to {dot_file}")


@org_task()
def git_init_submodules(ctx: Context):
    "Init submodules if missing"
    if get_script_root().joinpath("thirdparty/mp11").exists():
        log.info("Submodules were checked out")
    else:
        log.info("Submodules were not checked out, running update")
        run_command(ctx, "git",
                    ("submodule", "update", "--init", "--recursive", "--progress"))


@org_task()
def download_llvm(ctx: Context):
    "Download LLVM toolchain if missing"
    llvm_dir = get_script_root("toolchain/llvm")
    if not os.path.isdir(llvm_dir):
        log.info("LLVM not found. Downloading...")
        # curl = local["curl"]
        # version = "17.0.6"
        # wget = local["wget"]
        # if not os.path.isdir("toolchain"):
        #     os.makedirs("toolchain")

        # wget.run((
        #     "https://github.com/llvm/llvm-project/releases/download/llvmorg-{version}/clang+llvm-{version}-x86_64-linux-gnu-ubuntu-22.04.tar.xz"
        # ))

        # ctx.run(f"tar -xf llvm.tar.xz -C toolchain && mv toolchain/clang+llvm-{version}-x86_64-linux-gnu-ubuntu-22.04 toolchain/llvm")
        # os.remove("llvm.tar.xz")
        # log.info("LLVM downloaded and unpacked successfully!")
    else:
        log.info("LLVM already exists. Skipping download.")


@org_task(pre=[git_init_submodules, download_llvm])
def base_environment(ctx: Context):
    "Ensure base dependencies are installed"
    pass


@org_task(pre=[base_environment])
def cmake_configure_utils(ctx: Context, debug=True):
    """Execute configuration for utility binary compilation"""
    log.info("Configuring cmake utils build")
    build_dir = "build/utils_debug" if debug else "build/utils_release"
    run_command(
        ctx,
        "cmake",
        (
            "-B",
            get_script_root(build_dir),
            "-S",
            str(get_script_root().joinpath("scripts/cxx_codegen")),
            "-G",
            "Ninja",
            f"-DCMAKE_BUILD_TYPE={'Debug' if debug else 'RelWithDebInfo'}",
            f"-DCMAKE_CXX_COMPILER={get_script_root('toolchain/llvm/bin/clang++')}",
        ),
    )


@org_task(task_name="Build cmake utils", pre=[cmake_configure_utils])
def cmake_utils(ctx: Context, debug=True):
    """Compile libraries and binaries for utils"""
    log.info("Building build utils")
    build_dir = "build/utils_debug" if debug else "build/utils_release"
    run_command(ctx, "cmake", ("--build", get_script_root(build_dir)))
    log.info("CMake utils build ok")


@org_task(pre=[base_environment])
def haxorg_base_lexer(ctx: Context):
    "Generate base lexer file definitions and compile them to C code"
    log.info("Generating base lexer for haxorg")
    run_command(ctx, "poetry", ("run", "src/base_lexer/base_lexer.py"))
    run_command(
        ctx,
        get_script_root("toolchain/RE-flex/build/reflex"),
        (
            "--fast",
            "--nodefault",
            "--case-insensitive",
            f"--outfile={get_script_root('src/base_lexer/base_lexer_gen.cpp')}",
            "--namespace=base_lexer",
            get_script_root("src/base_lexer/base_lexer.l"),
        ),
        env={"LD_LIBRARY_PATH": str(get_script_root("toolchain/RE-flex/lib"))},
    )


@org_task()
def python_protobuf_files(ctx: Context):
    "Generate new python code from the protobuf reflection files"
    proto_config = get_script_root("scripts/cxx_codegen/reflection_defs.proto")
    with FileOperation.InTmp(
        [proto_config],
            stamp_path=get_task_stamp("python-protobuf-files"),
    ) as op:
        if op.should_run():
            log.info(f"Running protc {op.explain('python protobuf')}")
            _, stdout, _ = run_command(ctx,
                                       "poetry", ("env", "info", "--path"),
                                       capture=True)
            stdout = stdout.strip()
            log.info(f"Using protoc plugin path '{stdout}'")
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
                (
                    f"--plugin={protoc_plugin}",
                    "-I",
                    get_script_root("scripts/cxx_codegen"),
                    "--proto_path=" +
                    str(get_script_root("scripts/py_codegen/py_codegen")),
                    "--python_betterproto_out=" + str(proto_lib),
                    proto_config,
                ),
            )


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
        log.info(op.explain("cmake configuration"))
        if op.should_run():
            log.info("running haxorg cmake configuration")
            build_dir = "build/haxorg_debug" if is_debug(ctx) else "build/haxorg_release"
            pass_flags = [
                "-B",
                get_script_root(build_dir), "-S",
                get_script_root(), "-G", "Ninja",
                f"-DCMAKE_CXX_COMPILER={get_llvm_root('bin/clang++')}",
                *get_cmake_defines(ctx)
            ]

            run_command(ctx, "cmake", tuple(pass_flags))


@org_task(pre=[cmake_configure_haxorg])
def cmake_haxorg(ctx: Context):
    "Compile main set of libraries and binaries for org-mode parser"
    build_dir = f'build/haxorg_{"debug" if is_debug(ctx) else "release"}'
    with FileOperation.InTmp(
        [
            Path(path).rglob(glob)
            for path in ["src", "scripts", "tests"]
            for glob in ["*.cpp", "*.hpp", "*.cppm"]
        ],
            stamp_path=get_task_stamp("cmake_haxorg"),
            stamp_content=str(get_cmake_defines(ctx)),
    ) as op:
        log.info(op.explain("Main C++"))
        if op.should_run():
            log.info('Running cmake haxorg build')
            run_command(ctx,
                        "cmake", ["--build", build_dir],
                        env={'NINJA_FORCE_COLOR': '1'})

    text_layout_link = get_script_root(
        "scripts/py_textlayout/py_textlayout/py_textlayout.so")
    if not text_layout_link.exists():
        text_layout_link.symlink_to("haxorg/py_textlayout.so")

    haxorg_link = get_script_root("scripts/py_haxorg/py_haxorg/pyhaxorg.so")
    if not haxorg_link.exists():
        haxorg_link.symlink_to("haxorg/pyhaxorg.so")


LLDB_AUTO_BACKTRACE: List[str] = [
    "--one-line-on-crash", "bt", "--one-line-on-crash", "exit"
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
            "-o",
            f"command script import {get_script_root('scripts/cxx_repository/lldb_script.py')}",
            "-o",
            "run",
            "--source-on-crash",
            str(get_script_root("scripts/cxx_repository/lldb-script.txt")),
            json.dumps(config),
        ])
    else:
        run_command(ctx, tool, [json.dumps(config)])


@org_task(pre=[cmake_utils, python_protobuf_files])
def update_py_haxorg_reflection(ctx: Context):
    "Generate new source code reflection file for the python source code wrapper"
    compile_commands = local.path("build/haxorg/compile_commands.json")
    include_dir = local.path(f"toolchain/llvm/lib/clang/{LLVM_MAJOR}/include")
    out_file = local.path("build/reflection.pb")
    src_file = "src/py_libs/pyhaxorg/pyhaxorg.cpp"

    try:
        run_command(
            ctx,
            "build/utils/reflection_tool",
            (
                "-p",
                compile_commands,
                "--compilation-database",
                compile_commands,
                "--toolchain-include",
                include_dir,
                "--out",
                out_file,
                src_file,
            ),
        )
    except ProcessExecutionError as e:
        log.error("Reflection tool failed: %s", e)
        raise

    log.info("Updated reflection")


# TODO Make compiled reflection generation build optional
@org_task(pre=[cmake_utils, update_py_haxorg_reflection])
def haxorg_codegen(ctx: Context, as_diff: bool = False):
    "Update auto-generated source files"
    # TODO source file generation should optionally overwrite the target OR
    # compare the new and old source code (to avoid breaking the subsequent
    # compilation of the source)
    log.info("Executing haxorg code generation step.")
    run_command(
        ctx,
        "poetry",
        (
            "run",
            "scripts/py_codegen/codegen.py",
            get_build_root(),
            get_script_root(),
        ),
    )

    log.info("Updated code definitions")


@org_task(pre=[cmake_haxorg])
def std_tests(ctx):
    "Execute standard library tests"
    dir = get_build_root("haxorg")
    test = dir / "tests_hstd"
    run_command(ctx, test, [], cwd=str(dir))


@beartype
def binary_coverage(ctx: Context, test: Path):
    dir = test.parent
    tools = get_llvm_root() / "bin"
    # Remove .profdata files
    for file in dir.glob("*.profdata"):
        file.unlink()

    assert dir.exists()
    run_command(ctx, test, [], allow_fail=True, cwd=str(dir))

    profraw = dir / "default.profraw"
    coverage_dir = dir / "coverage_report"
    if profraw.exists():
        # Merging profdata
        run_command(ctx, tools / "llvm-profdata", [
            "merge",
            "-output=" + str(dir / "test.profdata"),
            str(profraw),
        ])

        # Generating coverage report
        run_command(ctx, tools / "llvm-cov", [
            "show",
            str(test),
            "-ignore-filename-regex",
            ".*/(_?deps|thirdparty)/.*",
            "-instr-profile=" + str(dir / "test.profdata"),
            "-format=html",
            "-output-dir=" + str(coverage_dir),
        ])

        log.info(f"Generated coverage to {coverage_dir}")

    else:
        raise Failure(
            f"{profraw} does not exist after running tests. Instrumentation was set to {is_instrumented_coverage(ctx)}"
        )


@beartype
def xray_coverage(ctx: Context, test: Path):
    dir = test.parent
    tools = get_llvm_root("bin")

    # Remove existing XRay log and profdata files
    for file in dir.glob(f"xray-log.{test.stem}.*"):
        file.unlink()

    for file in dir.glob("*.profdata"):
        file.unlink()

    log.info(f"Running XRAY log agregation for directory {dir}")
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
        log.info(f"Latest XRay log file '{log_files[0]}'")
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
def std_xray(ctx: Context):
    "Generate test xray information for STD"
    xray_coverage(ctx, get_build_root("haxorg") / "tests_hstd")


@org_task(pre=[cmake_haxorg])
def std_coverage(ctx: Context):
    "Generate test coverage information for STD"
    binary_coverage(ctx, get_build_root("haxorg") / "tests_hstd")


@org_task(pre=[cmake_haxorg])
def org_coverage(ctx: Context):
    "Generate test coverage information for ORG"
    binary_coverage(ctx, get_build_root("haxorg") / "tests_org")


@org_task(pre=[cmake_haxorg, cmake_utils, python_protobuf_files])
def py_tests(ctx: Context, debug: bool = False, debug_test: Optional[str] = None):
    """
    Execute the whole python test suite or run a single test file in non-interactive
    LLDB debugger to work on compiled component issues. 
    """
    preload = {
        "LD_PRELOAD":
            str(
                get_llvm_root(
                    f"lib/clang/{LLVM_MAJOR}/lib/x86_64-unknown-linux-gnu/libclang_rt.asan.so"
                ))
    }

    if debug:
        debug_test: Path = Path(debug_test)
        if not debug_test.is_absolute():
            debug_test = get_script_root("tests").joinpath(debug_test)

        retcode, _, _ = run_command(
            ctx,
            "poetry",
            [
                "run",
                "lldb",  # NOTE using system-provided LLDB instead of the get_llvm_root("bin/lldb"),
                # because the latter one is not guaranteed to be compiled with the python
                # installed on the system. For example, 17.0.6 required python 3.10, but the
                # arch linux already moved to 3.11 here.
                "--batch",
                "-o",
                f"run {debug_test}",
                *LLDB_AUTO_BACKTRACE,
                "--",
                "python",
            ],
            allow_fail=True,
            env=preload,
        )

    else:
        retcode, _, _ = run_command(
            ctx,
            "poetry",
            ["run", "pytest", "-v", "-ra", "-s", "--tb=short"],
            allow_fail=True,
            env=preload,
        )
    if retcode != 0:
        exit(1)


@org_task()
def build_cxx_docs(ctx: Context):
    "Build Doxygen docunentation for the project"
    run_command(ctx, "doxygen", str(get_script_root("Doxyfile")))
    log.info("Completed CXX docs build")


@org_task()
def build_py_docs(ctx: Context):
    "Build python documentation for the project"
    autogen_dir = get_script_root(f"docs/sphinx_config/api_source")
    if autogen_dir.exists():
        rmtree(autogen_dir)

    auto_config_content = "import sys\n"

    for source_dir, doc_dir in [
        (get_script_root(), "main"),
            *[(d, d.name) for d in [
                Path(get_script_root(f"scripts/{d}"))
                for d in os.listdir(get_script_root("scripts"))
            ] if d.is_dir() and d.name.startswith("py_")],
    ]:
        run_command(ctx, "poetry", [
            "run",
            "sphinx-apidoc",
            "-o",
            autogen_dir / doc_dir,
            source_dir,
        ])

        auto_config_content += f"sys.path.append('{source_dir.resolve()}')\n"

    with open(autogen_dir / "sphinx_autoconf.py", "w") as file:
        file.write(auto_config_content)

    for format in ["html", "json"]:
        run_command(ctx, "poetry", [
            "run",
            "sphinx-build",
            "-M",
            format,
            get_script_root("docs/sphinx_config/source"),
            get_script_root("docs/sphinx_config/build"),
        ])


@org_task(pre=[build_py_docs, build_cxx_docs])
def build_all_docs(ctx: Context):
    "Build all documentation for the project"
    pass
