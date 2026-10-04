import json
from pathlib import Path

from beartype import beartype
from hstd_py_codegen.read_cpp.refl_extract import (
    TuOptions,
    run_reflection_tool,
)
from hstd_py_codegen.read_cpp.refl_read import ConvTu


@beartype
def extract_reflection(
    compilation_database: Path,
    output_directory: Path,
    target_file: Path,
) -> ConvTu:
    compilation_database = compilation_database.resolve()
    output_directory = output_directory.resolve()
    target_file = target_file.resolve()

    assert compilation_database.is_file(), (
        f"Compilation database does not exist: {compilation_database}"
    )
    assert target_file.is_file(), f"Reflection input does not exist: {target_file}"

    output_directory.mkdir(parents=True, exist_ok=True)

    options = TuOptions(
        input=[str(target_file)],
        compilation_database=str(compilation_database),
        header_root=str(target_file.parent),
        binary_tmp=str(output_directory / "collector"),
        output_directory=str(output_directory),
        convert_failure_log_dir=str(output_directory / "failures"),
        only_annotated=True,
        cache_collector_runs=False,
    )

    result = run_reflection_tool(
        options,
        target_file,
        output_directory / target_file.with_suffix(".py").name,
    )

    assert result.success, (
        f"Reflection extraction failed for {target_file}\n"
        f"Flags:\n{json.dumps(result.flags, indent=2)}\n"
        f"stdout:\n{result.res_stdout}\n"
        f"stderr:\n{result.res_stderr}"
    )
    assert result.conv_tu is not None, (
        f"Collector succeeded but returned no converted translation unit: {target_file}"
    )
    return result.conv_tu
