

@haxorg_task(dependencies=[build_haxorg, symlink_build, generate_python_protobuf_files],
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
            "scripts/py_repository/py_repository/coverage_collection/gen_coverage_cxx.py",
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
            "--log-cli-level=DEBUG",
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


@haxorg_task(
    pre=[
        # build_haxorg, generate_python_protobuf_files, symlink_build,
    ],
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


@haxorg_task(dependencies=[run_py_tests])
def run_py_tests_ci(ctx: Context):
    """
    CI task that builds base lexer codegen before running the build 
    """
    pass
