import json
from pathlib import Path
from textwrap import dedent

from beartype import beartype
from hstd_py_codegen.read_cpp.refl_extract import (
    TuOptions,
    read_compile_commands,
    run_reflection_tool,
)
from hstd_py_codegen.read_cpp.refl_read import ConvTu
from plumbum import local


@beartype
def create_cmake_project(root: Path, files: dict[str, str]) -> Path:
    source_root = root / "source"
    build_root = root / "build"
    source_root.mkdir(parents=True)

    sources: list[str] = []
    for name, content in files.items():
        relative = Path(name)
        path = source_root / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(dedent(content).lstrip(), encoding="utf-8")

        if relative.suffix in {".cpp", ".cc", ".cxx"}:
            sources.append(f'    "{relative.as_posix()}"')

    assert sources, (
        f"CMake project requires at least one C++ source file; supplied files: "
        f"{sorted(files)}"
    )

    configuration = dedent(
        """
        cmake_minimum_required(VERSION 3.28)
        project(reflection_fixture LANGUAGES CXX)

        set(CMAKE_CXX_STANDARD 23)
        set(CMAKE_CXX_STANDARD_REQUIRED ON)
        set(CMAKE_CXX_EXTENSIONS OFF)
        set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

        add_library(reflection_fixture STATIC
        """
    ).lstrip()
    configuration += "\n".join(sources)
    configuration += dedent(
        """

        )
        target_include_directories(
            reflection_fixture PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
        )
        """
    )
    (source_root / "CMakeLists.txt").write_text(
        configuration,
        encoding="utf-8",
    )

    local["cmake"].run(
        [
            "-S",
            str(source_root),
            "-B",
            str(build_root),
            "-G",
            "Ninja",
            "-DCMAKE_BUILD_TYPE=Debug",
        ]
    )
    local["cmake"].run(["--build", str(build_root)])

    assert (build_root / "compile_commands.json").is_file()
    return build_root


@beartype
def extract_translation_unit(build_root: Path, filename: str) -> ConvTu:
    root = build_root.parent
    source_root = root / "source"
    input_path = source_root / filename
    output_root = root / "reflection"
    output_root.mkdir(exist_ok=True)

    options = TuOptions(
        input=[str(input_path)],
        build_root=str(build_root),
        source_root=str(source_root),
        header_root=str(source_root),
        binary_tmp=str(root / "collector"),
        output_directory=str(output_root),
        convert_failure_log_dir=str(root / "failures"),
        only_annotated=True,
        cache_collector_runs=False,
    )

    result = run_reflection_tool(
        options,
        input_path,
        output_root / Path(filename).with_suffix(".py"),
    )

    assert result.success, (
        f"Reflection failed for {input_path}\n"
        f"Flags:\n{json.dumps(result.flags, indent=2)}\n"
        f"stdout:\n{result.res_stdout}\n"
        f"stderr:\n{result.res_stderr}"
    )
    assert result.pb_path is not None
    assert result.pb_path.is_file(), (
        f"Collector reported success but protobuf is missing: {result.pb_path}"
    )
    assert result.conv_tu is not None
    return result.conv_tu


@beartype
def test_multiple_files(stable_test_dir: Path) -> None:
    build_root = create_cmake_project(
        stable_test_dir,
        {
            "model/types.hpp": """
                #pragma once

                namespace demo {
                enum class [[refl]] State : int {
                    Idle = 0,
                    Active = 7,
                    Finished = 12
                };

                struct [[refl]] Base {
                    [[refl]] int identifier;
                };

                struct [[refl]] Record : Base {
                    [[refl]] double weight;
                    [[refl]] int* destination;

                    [[refl]] int value() const {
                        return identifier;
                    }

                    [[refl]] static int capacity() {
                        return 16;
                    }
                };

                }
            """,
            "api/operations.hpp": """
                #pragma once
                #include "model/types.hpp"

                namespace demo {
                [[refl]] int combine(int left, int right);
                [[refl]] Record make_record(int identifier);

                int ignored_operation(int value);
                }
            """,
            "src/model.cpp": """
                #include "model/types.hpp"

                static_assert(sizeof(demo::Record) != 0);
            """,
            "src/operations.cpp": """
                #include "api/operations.hpp"

                namespace demo {
                int combine(int left, int right) {
                    return left + right;
                }

                Record make_record(int identifier) {
                    Record result{};
                    result.identifier = identifier;
                    result.weight = 1.5;
                    return result;
                }


                int ignored_operation(int value) {
                    return value;
                }
                }
            """,
        },
    )

    commands = read_compile_commands(build_root)
    source_root = build_root.parent / "source"
    command_files = {
        (
            Path(command.file)
            if Path(command.file).is_absolute()
            else Path(command.directory) / command.file
        ).resolve()
        for command in commands
    }
    expected_files = {
        source_root / "model/types.hpp",
        source_root / "api/operations.hpp",
        source_root / "src/model.cpp",
        source_root / "src/operations.cpp",
    }
    assert expected_files <= command_files, (
        f"Expanded compilation database is missing: "
        f"{sorted(str(path) for path in expected_files - command_files)}"
    )

    model = extract_translation_unit(build_root, "model/types.hpp")
    api = extract_translation_unit(build_root, "api/operations.hpp")

    structs = {record.Name.Name: record for record in model.structs}
    assert {"Base", "Record"} <= structs.keys()

    record = structs["Record"]
    assert [space.Name for space in record.Name.Spaces] == ["demo"]
    assert not record.IsForwardDecl
    assert not record.IsAbstract
    assert len(record.Bases) == 1
    assert record.Bases[0].Name == "Base"

    fields = {item.Name: item for item in record.Fields}
    assert set(fields) == {"weight", "destination"}
    assert fields["weight"].Type is not None
    assert fields["weight"].Type.Name == "double"
    assert fields["weight"].Type.IsBuiltin
    assert fields["destination"].Type is not None
    assert fields["destination"].Type.Name == "int"
    assert fields["destination"].Type.PtrCount == 1

    methods = {
        method.Name: method for method in record.Methods if not method.IsConstructor
    }
    assert {"value", "capacity"} <= methods.keys()
    assert methods["value"].IsConst
    assert methods["value"].ReturnType.Name == "int"
    assert methods["value"].Args == []
    assert methods["capacity"].IsStatic
    assert methods["capacity"].ReturnType.Name == "int"

    enums = {enum.Name.Name: enum for enum in model.enums}
    state = enums["State"]
    assert [space.Name for space in state.Name.Spaces] == ["demo"]
    assert state.IsEnumClass
    # TODO: Support reflection base extraction from enum declarations
    # assert state.Base == "int"
    assert len(state.Fields) == 3

    functions = {function.Name: function for function in api.functions}
    assert {"combine", "make_record"} <= functions.keys()
    assert "ignored_operation" not in functions
    assert functions["combine"].ReturnType.Name == "int"
    assert len(functions["combine"].Args) == 2
    assert [space.Name for space in functions["combine"].Spaces] == ["demo"]
    assert functions["make_record"].ReturnType.Name == "Record"
    assert len(functions["make_record"].Args) == 1

    assert len(model.get_all()) == (
        len(model.enums) + len(model.typedefs) + len(model.structs) + len(model.functions)
    )


@beartype
def test_struct_fields(stable_test_dir: Path) -> None:
    build_root = create_cmake_project(
        stable_test_dir,
        {
            "record.hpp": """
                #pragma once

                struct [[refl]] Sample {
                    [[refl]] int count;
                    [[refl]] double weight;
                    [[refl]] int* destination;
                };
            """,
            "record.cpp": """
                #include "record.hpp"

                static_assert(sizeof(Sample) != 0);
            """,
        },
    )
    tu = extract_translation_unit(build_root, "record.hpp")

    assert len(tu.structs) == 1
    record = tu.structs[0]
    assert record.Name.Name == "Sample"
    assert record.Bases == []

    assert [item.Name for item in record.Fields] == [
        "count",
        "weight",
        "destination",
    ]
    for item, expected_name, expected_pointers in zip(
        record.Fields,
        ["int", "double", "int"],
        [0, 0, 1],
        strict=True,
    ):
        assert item.Type is not None
        assert item.Type.Name == expected_name
        assert item.Type.PtrCount == expected_pointers


@beartype
def test_function_overloads(stable_test_dir: Path) -> None:
    build_root = create_cmake_project(
        stable_test_dir,
        {
            "functions.hpp": """
                #pragma once

                namespace arithmetic {
                [[refl]] int calculate(int value);
                [[refl]] double calculate(double left, double right);
                }
            """,
            "functions.cpp": """
                #include "functions.hpp"

                namespace arithmetic {
                int calculate(int value) {
                    return value + 1;
                }

                double calculate(double left, double right) {
                    return left + right;
                }
                }
            """,
        },
    )
    tu = extract_translation_unit(build_root, "functions.hpp")

    assert len(tu.functions) == 2
    assert {function.Name for function in tu.functions} == {"calculate"}
    assert {
        (function.ReturnType.Name, len(function.Args)) for function in tu.functions
    } == {("int", 1), ("double", 2)}
    for function in tu.functions:
        assert [space.Name for space in function.Spaces] == ["arithmetic"]


@beartype
def test_scoped_enum(stable_test_dir: Path) -> None:
    build_root = create_cmake_project(
        stable_test_dir,
        {
            "status.hpp": """
                #pragma once

                namespace protocol {
                enum class [[refl]] Status : unsigned int {
                    Ready = 2,
                    Busy = 5,
                    Done = 9
                };
                }
            """,
            "status.cpp": """
                #include "status.hpp"

                static_assert(static_cast<unsigned int>(protocol::Status::Done) == 9);
            """,
        },
    )
    tu = extract_translation_unit(build_root, "status.hpp")

    assert len(tu.enums) == 1
    enum = tu.enums[0]
    assert enum.Name.Name == "Status"
    assert [space.Name for space in enum.Name.Spaces] == ["protocol"]
    assert enum.IsEnumClass
    assert not enum.IsForwardDecl
    # TODO: Support reflection base extraction from enum declarations
    # assert enum.Base == "unsigned int"
    assert len(enum.Fields) == 3


@beartype
def test_methods(stable_test_dir: Path) -> None:
    build_root = create_cmake_project(
        stable_test_dir,
        {
            "counter.hpp": """
                #pragma once

                struct [[refl]] Counter {
                    int count;

                    [[refl]] int read() const {
                        return count;
                    }

                    [[refl]] void reset(int value) {
                        count = value;
                    }

                    [[refl]] static int limit() {
                        return 100;
                    }
                };
            """,
            "counter.cpp": """
                #include "counter.hpp"

                static_assert(sizeof(Counter) != 0);
            """,
        },
    )
    tu = extract_translation_unit(build_root, "counter.hpp")

    assert len(tu.structs) == 1
    methods = {
        method.Name: method
        for method in tu.structs[0].Methods
        if not method.IsConstructor
    }
    assert set(methods) == {"read", "reset", "limit"}

    assert methods["read"].IsConst
    assert not methods["read"].IsStatic
    assert methods["read"].ReturnType.Name == "int"
    assert methods["read"].Args == []

    assert not methods["reset"].IsConst
    assert methods["reset"].ReturnType.Name == "void"
    assert len(methods["reset"].Args) == 1

    assert methods["limit"].IsStatic
    assert methods["limit"].ReturnType.Name == "int"
    assert methods["limit"].Args == []


@beartype
def test_only_annotated_declarations(stable_test_dir: Path) -> None:
    build_root = create_cmake_project(
        stable_test_dir,
        {
            "annotations.hpp": """
                #pragma once

                struct [[refl]] VisibleRecord {
                    int value;
                };

                struct HiddenRecord {
                    int value;
                };

                enum class [[refl]] VisibleEnum : int {
                    Value = 1
                };

                enum class HiddenEnum : int {
                    Value = 1
                };

                [[refl]] inline int visible_function() {
                    return 1;
                }

                inline int hidden_function() {
                    return 2;
                }
            """,
            "annotations.cpp": """
                #include "annotations.hpp"

                static_assert(sizeof(VisibleRecord) == sizeof(HiddenRecord));
            """,
        },
    )
    tu = extract_translation_unit(build_root, "annotations.hpp")

    assert {record.Name.Name for record in tu.structs} == {"VisibleRecord"}
    assert {enum.Name.Name for enum in tu.enums} == {"VisibleEnum"}
    assert {function.Name for function in tu.functions} == {"visible_function"}
