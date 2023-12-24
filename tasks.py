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
            raise Failure(f"Failed to execute the command {cmd}")


def task_time(func: callable) -> callable:

    @wraps(func)
    def wrapper(*args, **kwargs):
        name = func.__name__
        log.info(f"Running [yellow]{name}[/yellow] ...")
        with GlobCompleteEvent(f"task {name}", "build"):
            result = func(*args, **kwargs)

        last = getGlobalTraceCollector().get_last_event()
        log.info(f"Completed [green]{name}[/green] in [blue]{last.dur / 10e3:5.1f}[/blue]ms")

        GlobExportJson(get_build_root("task_build_time.json"))

        return result

    return wrapper


def get_cmake_defines(ctx: Context) -> List[str]:
    result: List[str] = []
    if is_instrumented_coverage(ctx):
        result.append("-DORG_USE_COVERAGE=ON")

    if is_debug(ctx):
        result.append("-DCMAKE_BUILD_TYPE=Debug")

    else:
        result.append("-DCMAKE_BUILD_TYPE=RelWithDebInfo")

    return result


@task
@task_time
def git_init_submodules(ctx: Context):
    if get_script_root().joinpath("thirdparty/mp11").exists():
        log.info("Submodules were checked out")
    else:
        log.info("Submodules were not checked out, running update")
        run_command(ctx, "git",
                    ("submodule", "update", "--init", "--recursive", "--progress"))


@task
@task_time
def download_llvm(ctx: Context):
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


@task(pre=[git_init_submodules, download_llvm])
@task_time
def base_environment(ctx: Context):
    pass


@task(pre=[base_environment])
@task_time
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


@task(pre=[cmake_configure_utils])
@task_time
def cmake_utils(ctx: Context, debug=True):
    log.info("Building build utils")
    """Compile libraries and binaries for utils"""
    build_dir = "build/utils_debug" if debug else "build/utils_release"
    run_command(ctx, "cmake", ("--build", get_script_root(build_dir)))
    log.info("CMake utils build ok")


@task(pre=[cmake_utils])
@task_time
def py_reflection(ctx: Context):
    log.info("Updating reflection artifacts using standalone build tool")
    run_command(
        ctx,
        get_build_root("utils/reflection_tool"),
        (
            "-p=build/haxorg/compile_commands.json",
            "--compilation-database=build/haxorg/compile_commands.json",
            f"--toolchain-include={get_script_root('toolchain/llvm/lib/clang/16/include')}",
            f"--out={get_build_root('reflection.pb')}",
            "src/py_libs/pyhaxorg/pyhaxorg.cpp",
        ),
    )


@task(pre=[base_environment])
@task_time
def haxorg_base_lexer(ctx: Context):
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


@task
@task_time
def haxorg_codegen(ctx: Context):
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


@task
@task_time
def reflection_protobuf(ctx: Context):
    """Update protobuf data definition for reflection"""
    poetry = local["poetry"]
    _, stdout, _ = run_command(ctx, "poetry", ("env", "info", "--path"), capture=True)
    print(f"Using protoc plugin path '{stdout}'")
    protoc_plugin = os.path.join(stdout, "bin/protoc-gen-python_betterproto")

    run_command(
        ctx,
        "protoc",
        (
            f"--plugin={protoc_plugin}",
            "-I",
            get_script_root("scripts/cxx_codegen"),
            "--proto_path=" + str(get_script_root("scripts/py_codegen")),
            "--python_betterproto_out=" +
            str(get_script_root("scripts/py_codegen/proto_lib")),
            get_script_root("scripts/cxx_codegen/reflection_defs.proto"),
        ),
    )


@task(pre=[download_llvm])
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


@task(pre=[cmake_configure_haxorg])
@task_time
def cmake_haxorg(ctx):
    "Compile main set of libraries and binaries for org-mode parser"
    build_dir = f'build/haxorg_{"debug" if is_debug(ctx) else "release"}'
    with FileOperation.InTmp(
        [
            Path("src").rglob("*.cpp"),
            Path("src").rglob("*.hpp"),
            Path("src").rglob("*.cppm"),
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


@task(pre=[cmake_haxorg])
@task_time
def std_tests(ctx):
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


@task(pre=[cmake_haxorg])
@task_time
def std_coverage(ctx: Context):
    "Generate test coverage information for STD"
    binary_coverage(ctx, get_build_root("haxorg") / "tests_hstd")


@task(pre=[cmake_haxorg])
@task_time
def org_coverage(ctx: Context):
    "Generate test coverage information for ORG"
    binary_coverage(ctx, get_build_root("haxorg") / "tests_org")


@task(pre=[cmake_haxorg])
@task_time
def py_tests(ctx: Context):
    retcode, _, _ = run_command(ctx, "poetry", ["run", "pytest", "-s"], allow_fail=True)
    if retcode != 0:
        exit(1)


@task
def update_reflection(ctx: Context):
    compile_commands = local.path("build/haxorg/compile_commands.json")
    include_dir = local.path("toolchain/llvm/lib/clang/17/include")
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


@task
def generate_lexer(ctx: Context):
    lexer_l = f"{get_script_root()}/src/base_lexer/base_lexer.l"
    lexer_out = f"{get_script_root()}/src/base_lexer/base_lexer_gen.cpp"
    poetry = local["poetry"]

    poetry["run", "src/base_lexer/base_lexer.py"] & FG

    with local.env(LD_LIBRARY_PATH=f"{get_script_root()}/toolchain/RE-flex/lib"):
        run_command(
            ctx,
            get_script_root("/toolchain/RE-flex/build/reflex"),
            (
                "--fast",
                "--nodefault",
                "--case-insensitive",
                f"--outfile={lexer_out}",
                f"--namespace=base_lexer",
                lexer_l,
            ),
        )

    log.info("Generated base lexer")


@task
@task_time
def test_python(ctx: Context):
    run_command(ctx, "poetry", ("run", "pytest", "-s"))


@task
@task_time
def build_cxx_docs(ctx: Context):
    run_command(ctx, "doxygen", str(get_script_root("Doxyfile")))
    log.info("Completed CXX docs build")


@task
@task_time
def build_py_docs(ctx: Context):
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
