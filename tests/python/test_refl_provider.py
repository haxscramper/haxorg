import py_codegen.refl_extract as ex
from tempfile import NamedTemporaryFile, TemporaryDirectory
from pathlib import Path
import json
from py_scriptutils.script_logging import log
from py_scriptutils.toml_config_profiler import interpolate_dictionary, get_haxorg_repo_root_path
from pprint import pprint
from py_codegen.refl_read import ConvTu, GenTuStruct, GenTuEnum, GenTuFunction
from beartype.typing import Optional
from beartype import beartype

STABLE_FILE_NAME = "/tmp/cpp_stable.cpp"

@beartype
def run_provider(text: str, stable_cpp_file: Optional[str] = None, print_reflection_run_fail_to_stdout: bool = False) -> ConvTu:
    with (
            # TODO Delete only when test run is ok
        (open(stable_cpp_file, "w") if stable_cpp_file else NamedTemporaryFile(
            mode="w", suffix=".cpp", delete=False)) as file,
            NamedTemporaryFile(mode="w", suffix=".json", delete=False) as
            compile_commands,
    ):
        tmp_parent = str(Path(file.name).parent)
        base_dict = dict(
            input=[file.name],
            indexing_tool="{haxorg_root}/build/utils/reflection_tool",
            compilation_database=compile_commands.name,
            toolchain_include="{haxorg_root}/toolchain/llvm/lib/clang/17/include",
            output_directory=tmp_parent,
            directory_root=tmp_parent)

        conf = ex.TuOptions.model_validate(
            interpolate_dictionary(base_dict,
                                   {"haxorg_root": get_haxorg_repo_root_path()}))

        conf.print_reflection_run_fail_to_stdout = print_reflection_run_fail_to_stdout
        conf.reflection_run_verbose = True

        compile_commands.write(
            json.dumps([{
                "directory": conf.directory_root,
                "command": f"clang++ {file.name}",
                "file": conf.input[0],
                "output": str(Path(conf.input[0]).with_suffix(".o"))
            }]))

        compile_commands.flush()

        file.write(text)
        file.flush()

        mappings = ex.expand_input(conf)
        commands = ex.read_compile_cmmands(conf)
        wrap = ex.run_collector_for_path(conf, mappings[0], commands)
        assert wrap
        return wrap.tu


def get_struct(text: str, **kwargs) -> GenTuStruct:
    tu = run_provider(text, **kwargs)
    assert len(tu.structs) == 1
    return tu.structs[0]


def get_enum(text: str, **kwargs) -> GenTuEnum:
    tu = run_provider(text, **kwargs)
    assert len(tu.enums) == 1
    return tu.enums[0]


def get_function(text: str, **kwargs) -> GenTuFunction:
    tu = run_provider(text, **kwargs)
    assert len(tu.functions) == 1
    return tu.functions[0]


def test_simple_structure_registration():
    struct = get_struct("struct Test {};")
    assert struct.name.name == "Test"
    assert len(struct.methods) == 0
    assert len(struct.fields) == 0


def test_structure_field_registration():
    struct = get_struct("struct Test { int field; };")
    assert len(struct.fields) == 1
    field = struct.fields[0]
    assert field.name == "field"
    assert field.type.name == "int"


def test_anon_structure_fields():
    struct = get_struct("struct Main { union { int int_field; char char_field; }; };")
    assert len(struct.nested) == 1
    union: GenTuStruct = struct.nested[0]
    assert not union.has_name
    assert len(union.fields) == 2
    field1 = union.fields[0]
    field2 = union.fields[1]
    assert field1.name == "int_field"
    assert field2.name == "char_field"
    assert field1.type.name == "int"
    assert field2.type.name == "char"


def test_enum_field_extract():
    enum = get_enum("enum CEnum { Member1, Member2 };")
    assert enum.name.name == "CEnum"
    assert len(enum.fields) == 2
    assert enum.fields[0].name == "Member1"
    assert enum.fields[1].name == "Member2"


def test_namespaced_enum_extract():
    enum = get_enum("namespace Space { enum Enum { member1 }; }")
    assert enum.name.name == "Enum"
    assert len(enum.name.Spaces) == 1
    assert enum.name.Spaces[0].name == "Space"


def test_function_extract_0_args():
    func = get_function("int get_something();")
    assert func.name == "get_something"
    assert len(func.arguments) == 0
    assert func.result.name == "int"


def test_function_extract_args():
    func = get_function("int do_something(int first, char second);")
    assert func.name == "do_something"
    assert len(func.arguments) == 2
    assert func.result.name == "int"
    assert func.arguments[0].type.name == "int"
    assert func.arguments[1].type.name == "char"
    assert func.arguments[0].name == "first"
    assert func.arguments[1].name == "second"


def test_field_with_std_import():
    tu = run_provider("#include <vector>\nstruct Content { std::vector<int> items; };")
    
    assert len(tu.structs) == 1
    assert len(tu.enums) == 0
    assert len(tu.functions) == 0
    assert len(tu.typedefs) == 0
    struct = tu.structs[0]
    assert struct.name.name == "Content"
    assert len(struct.fields) == 1
    field = struct.fields[0]
    assert field.name == "items"
    assert field.type.name == "vector"
    assert len(field.type.Spaces) == 1
    assert field.type.Spaces[0].name == "std"
    assert len(field.type.Parameters) == 1
    assert field.type.Parameters[0].name == "int"

def test_anon_struct_for_field():
    struct = get_struct("struct Main { struct { int nested; } field; };")
    assert struct.name.name == "Main"
    assert len(struct.nested) == 0
    assert len(struct.fields) == 1
    assert len(struct.methods) == 0
    field = struct.fields[0]
    assert field.isTypeDecl
    assert field.name == "field"
    decl = field.decl
    assert len(decl.fields) == 1
    assert decl.fields[0].name == "nested"
    
def test_anon_struct_for_field():
    struct = get_struct("struct Main { struct Named { int nested; } field; };")
    assert struct.name.name == "Main"
    assert len(struct.nested) == 1
    assert len(struct.fields) == 1
    assert len(struct.methods) == 0
    nested = struct.nested[0]
    field = struct.fields[0]

    assert nested.name.name == "Named"
    assert field.name == "field"
    assert field.type.name == "Named"

    # FIXME namespace extraction should take declaration locations into location
    # at the moment this is not implemented
    # assert len(field.type.Spaces) == 1
    # assert len(field.type.Spaces[0].name) == "Main"
