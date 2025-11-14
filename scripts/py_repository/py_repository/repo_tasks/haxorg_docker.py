
import itertools
from beartype import beartype
from pathlib import Path
from beartype.typing import List



from py_ci.util_scripting import get_docker_cap_flags
from py_repository.repo_tasks.airflow_utils import haxorg_task
from py_repository.repo_tasks.command_execution import run_command
from py_repository.repo_tasks.common import get_script_root
from py_repository.repo_tasks.config import get_config
from py_scriptutils.script_logging import log

CAT = __name__

@beartype
def docker_mnt(src: Path, dst: Path) -> List[str]:
    assert src.exists(), f"'{src}'"
    log(CAT).debug(f"Mounting docker '{src}' to '{dst}'")
    return ["--mount", f"type=bind,src={src},dst={dst}"]



@haxorg_task()
def build_docker_develop_image():
    run_command("docker", ["rm", get_config().HAXORG_DOCKER_IMAGE], allow_fail=True)
    run_command("docker", [
        "build",
        "-t",
        get_config().HAXORG_DOCKER_IMAGE,
        "-f",
        get_script_root("scripts/py_repository/Dockerfile"),
        ".",
    ])




@haxorg_task(dependencies=[build_docker_develop_image])
def run_docker_develop_test(
    interactive: bool = False,
    build: bool = True,
    test: bool = True,
    docs: bool = True,
    coverage: bool = True,
    reflection: bool = True,
    deps: bool = True,
    build_dir: str = get_tmpdir("docker_develop", "build"),
    example: bool = True,
    install: bool = True,
    emscripten_deps: bool = True,
    emscripten_build: bool = True,
    emscripten_test: bool = True,
):
    """Run docker"""

    HAXORG_BUILD_TMP = Path(build_dir)
    if not HAXORG_BUILD_TMP.exists():
        HAXORG_BUILD_TMP.mkdir(parents=True)

    @beartype
    def docker_path(path: str) -> Path:
        return Path("/haxorg").joinpath(path)

    run_command(
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
                "poetry.lock",
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
            *get_docker_cap_flags(),
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
                invoke_opt("deps", deps),
                invoke_opt("install", install),
                invoke_opt("example", example),
                invoke_opt("emscripten-deps", emscripten_deps),
                invoke_opt("emscripten-build", emscripten_build),
                invoke_opt("emscripten-test", emscripten_test),
            ]),
        ])




@haxorg_task(dependencies=[])
def run_docker_release_test(
    build_dir: str = get_tmpdir("docker_release", "build"),
    clone_dir: str = get_tmpdir("docker_release", "clone"),
    clone_code: Literal["none", "comitted", "all"] = "all",
    deps: bool = True,
    test: str = "python",
    build: bool = True,
    interactive: bool = False,
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

    @beartype
    def docker_path(path: str) -> Path:
        return Path("/haxorg/src").joinpath(path)

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

        else:
            source_prefix = clone_dir

        @beartype
        def pass_mnt(path: Optional[str] = None) -> Path:
            if path is None:
                if source_prefix:
                    return source_prefix

                else:
                    return get_script_root()

            else:
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
                *(["-it"] if interactive else []),
                *get_docker_cap_flags(),
                "--rm",
                *docker_user(),
                *docker_mnt(pass_mnt(), Path("/haxorg/src")),
                *docker_mnt(build_dir, Path("/haxorg/wip")),
                "-e",
                "PYTHONPATH=/haxorg/src/scripts/py_ci",
                "-e",
                f"HAXORG_THIRD_PARTY_DIR_PATH={docker_path('thirdparty')}",
                CPACK_TEST_IMAGE,
                *(["bash"] if interactive else [
                    # "ls",
                    # "-a",
                    # "/haxorg_wip",
                    "python",
                    "-m",
                    "py_ci.test_cpack_build",
                    invoke_opt("build", build),
                    invoke_opt("deps", deps),
                    f"--test={test}",
                ])
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





@haxorg_task()
def run_develop_ci(
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
        haxorg_env(["use", "qt"], False),
    ])

    if coverage:
        env = merge_dicts([
            env,
            haxorg_env(["instrument", "coverage"], True),
        ])

    emscripten_env = merge_dicts([
        env,
        haxorg_env(["emscripten", "build"], True),
        haxorg_env(["instrument", "coverage"], False),
    ])

    if deps:
        log(CAT).info("Running CI dependency installation")
        run_self([build_develop_deps], env=env)

    if install:
        log(CAT).info("Running install")
        run_self(
            ctx,
            [install_haxorg_develop],
            env=env,
        )

    if build:
        log(CAT).info("Running CI cmake")
        run_self([build_haxorg], env=env)

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
        run_self([build_examples], env=env)

    if coverage:
        log(CAT).info("Running CI coverage merge")
        run_self([run_cxx_coverage_merge], env=env)

    if docs:
        log(CAT).info("Running CI docs")
        run_self([build_custom_docs], env=env)

    if emscripten_deps:
        run_self([build_develop_deps], env=emscripten_env)

    if emscripten_build:
        run_self([build_haxorg], env=emscripten_env)

    if emscripten_test:
        run_self([run_js_test_example], env=emscripten_env)
