import json
from dataclasses import dataclass
from pathlib import Path

from beartype import beartype
from beartype.typing import Any
from plumbum import local

import haxdex_read_code_cpp.proto as pb


@beartype
@dataclass
class ReflProviderRunResult:
    tus: list[pb.Tu]
    code_dir: Path


@beartype
def run_reflection_tool_provider(
    text: str | dict[str, str],
    code_dir: Path,
    output_dir: Path,
    only_annotated: bool = False,
    reflection_run_verbose: bool = False,
) -> ReflProviderRunResult:
    code_dir = code_dir.resolve()
    output_dir = output_dir.resolve()
    code_dir.mkdir(parents=True, exist_ok=True)
    output_dir.mkdir(parents=True, exist_ok=True)

    if isinstance(text, str):
        text = {"automatic_provider_run_file.hpp": text}

    sources: list[Path] = []
    for filename, content in text.items():
        source = (code_dir / filename).resolve()
        source.parent.mkdir(parents=True, exist_ok=True)
        source.write_text(content, encoding="utf-8")
        sources.append(source)

    compilation_database = output_dir / "compile_commands.json"
    compilation_database.write_text(
        json.dumps(
            [
                {
                    "directory": str(code_dir),
                    "arguments": [
                        "clang++",
                        "-std=c++23",
                        "-x",
                        "c++",
                        "-c",
                        str(source),
                    ],
                    "file": str(source),
                }
                for source in sources
            ],
            indent=2,
        ),
        encoding="utf-8",
    )

    executable = local["haxdex_read_code_cpp"]
    mode = "AllAnotatedSymbols" if only_annotated else "AllTargetedFiles"
    tus: list[pb.Tu] = []

    for index, source in enumerate(sources):
        output = output_dir / f"reflection_{index}.pb"
        configuration = {
            "mode": mode,
            "reflection": {
                "compilation_database": str(compilation_database),
            },
            "verbose_log": reflection_run_verbose,
            "input": [str(source)],
            "output": str(output),
        }

        executable(json.dumps(configuration))
        tus.append(pb.Tu.ParseFromString(output.read_bytes()))

    return ReflProviderRunResult(tus=tus, code_dir=code_dir)


@beartype
def get_tu(
    text: str,
    stable_test_dir: Path,
    code_dir_override: Path | None = None,
    **kwargs: Any,
) -> pb.Tu:
    result = run_reflection_tool_provider(
        text,
        code_dir=code_dir_override or stable_test_dir,
        output_dir=stable_test_dir,
        **kwargs,
    )

    assert len(result.tus) == 1
    return result.tus[0]


@beartype
def get_struct(
    text: str,
    stable_test_dir: Path,
    code_dir_override: Path | None = None,
    **kwargs: Any,
) -> pb.Record:
    tu = get_tu(
        text,
        stable_test_dir=stable_test_dir,
        code_dir_override=code_dir_override,
        **kwargs,
    )

    assert len(tu.records) == 1
    return tu.records[0]


@beartype
def get_function(
    text: str,
    stable_test_dir: Path,
    **kwargs: Any,
) -> pb.Function:
    tu = get_tu(text, stable_test_dir=stable_test_dir, **kwargs)

    assert len(tu.functions) == 1
    return tu.functions[0]


@beartype
def get_enum(
    text: str,
    stable_test_dir: Path,
    **kwargs: Any,
) -> pb.Enum:
    tu = get_tu(text, stable_test_dir=stable_test_dir, **kwargs)

    assert len(tu.enums) == 1
    return tu.enums[0]


@beartype
def get_include_tree(
    text: str | dict[str, str],
    stable_test_dir: Path,
    main_file_suffix: str,
    code_dir_override: Path | None = None,
    **kwargs: Any,
) -> pb.IncludeVisit:
    result = run_reflection_tool_provider(
        text,
        code_dir=code_dir_override or stable_test_dir,
        output_dir=stable_test_dir,
        **kwargs,
    )

    matches = [
        tu.main_file_include_tree
        for tu in result.tus
        if tu.main_file_include_tree.absolute_path.endswith(main_file_suffix)
    ]

    assert len(matches) == 1, (
        f"Expected one include tree ending with {main_file_suffix!r}; "
        f"found {len(matches)}. Available paths: "
        f"{[tu.main_file_include_tree.absolute_path for tu in result.tus]}"
    )
    return matches[0]


@beartype
def get_type(
    *,
    preamble: list[str],
    stable_test_dir: Path,
    typ: str = "",
    struct_header: str = "struct [[refl]] test",
    field_decl: str | None = None,
    **kwargs: Any,
) -> pb.QualType:
    assert not (typ and field_decl), (
        f"Declare either typ or field_decl, not both: "
        f"typ={typ!r}, field_decl={field_decl!r}"
    )

    type_use = field_decl if field_decl is not None else f"[[refl]] {typ} field;"
    record = get_struct(
        "\n".join(
            [
                *preamble,
                f"{struct_header} {{",
                type_use,
                "};",
            ]
        ),
        stable_test_dir=stable_test_dir,
        only_annotated=True,
        **kwargs,
    )

    assert len(record.fields) == 1
    return record.fields[0].type
