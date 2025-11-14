

@haxorg_task()
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



@haxorg_task(
    iterable=["file_blacklist", "file_whitelist"],
    help={
        **HELP_coverage_file,
    },
)
def build_custom_docs(
        ctx: Context,
        coverage_file_whitelist: List[str] = [".*"],
        coverage_file_blacklist: List[str] = [],
        out_dir: str = get_tmpdir("docs_out"),
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

    prof_params = get_cxx_profdata_params(ctx)
    if Path(prof_params.coverage_db).exists():
        args.append(f"--cxx_coverage_path={prof_params.coverage_db}")
        log(CAT).info(f"Using coveage database from {prof_params.coverage_db}")
    else:
        log(CAT).info(
            f"No coverage database generated, {prof_params.coverage_db} does not exist")

    run_command(ctx, "poetry", args, env=get_py_env(ctx))

