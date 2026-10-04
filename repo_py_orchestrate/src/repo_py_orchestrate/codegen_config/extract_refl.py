import json
from pathlib import Path

from beartype import beartype
from hstd_py_codegen.read_cpp.refl_extract import (
    TuOptions,
    read_compile_commands,
    run_reflection_tool,
)
from hstd_py_codegen.read_cpp.refl_read import ConvTu
from plumbum import local


@beartype
def extract_manual_reflection(
    monorepo_root: Path,
    output_directory: Path,
) -> ConvTu:
    monorepo_root = monorepo_root.resolve()
    output_directory = output_directory.resolve()

    with local.cwd(monorepo_root):
        _, stdout, _ = local["conan"].run(["workspace", "info", "--format=json"])

    workspace = json.loads(stdout)
    workspace_root = Path(workspace["folder"])
    package_name = "haxorg_cpp_py_wrap"
    packages = [
        package
        for package in workspace["packages"]
        if package["ref"].split("/", 1)[0] == package_name
    ]

    if len(packages) != 1:
        raise ValueError(
            f"Expected one workspace package named {package_name!r}, "
            f"found {len(packages)}. "
            f"Available packages: "
            f"{[package['ref'] for package in workspace['packages']]}"
        )

    package = packages[0]
    project_root = workspace_root / package["path"]
    build_root = workspace_root / package["output_folder"]
    input_path = project_root / "src" / package_name / "pyhaxorg_manual_refl.cpp"

    assert input_path.is_file(), f"Reflection input does not exist: {input_path}"
    assert (build_root / "compile_commands.json").is_file(), (
        f"Compilation database does not exist in Conan output folder: {build_root}"
    )

    output_directory.mkdir(parents=True, exist_ok=True)
    commands = read_compile_commands(build_root)
    database_path = output_directory / "compile_commands.json"
    database_path.write_text(
        json.dumps(
            [command.model_dump(exclude_none=True) for command in commands],
            indent=2,
        ),
        encoding="utf-8",
    )

    options = TuOptions(
        input=[str(input_path)],
        compilation_database=str(database_path),
        build_root=str(build_root),
        source_root=str(project_root),
        header_root=str(project_root / "src"),
        binary_tmp=str(output_directory / "collector"),
        output_directory=str(output_directory),
        convert_failure_log_dir=str(output_directory / "failures"),
        only_annotated=True,
        cache_collector_runs=False,
    )

    result = run_reflection_tool(
        options,
        input_path,
        output_directory / "pyhaxorg_manual_refl.py",
    )

    assert result.success, (
        f"Reflection extraction failed for {input_path}\n"
        f"Flags:\n{json.dumps(result.flags, indent=2)}\n"
        f"stdout:\n{result.res_stdout}\n"
        f"stderr:\n{result.res_stderr}"
    )
    assert result.conv_tu is not None, (
        f"Collector succeeded but returned no converted translation unit: {input_path}"
    )
    return result.conv_tu
