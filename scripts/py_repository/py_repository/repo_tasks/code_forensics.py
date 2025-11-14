
@haxorg_task(dependencies=[build_haxorg])
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

