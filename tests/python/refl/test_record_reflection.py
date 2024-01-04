from pathlib import Path
from tempfile import TemporaryDirectory

from refl_test_driver import run_provider, STABLE_FILE_NAME, GenTuStruct, get_struct, get_nim_code, format_nim_code, \
    compile_nim_code
import pytest
from pprint import pprint
from plumbum import local


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


def test_field_with_std_import():
    with TemporaryDirectory() as code_dir:
        tu = run_provider(
            "#include <vector>\nstruct Content { std::vector<int> items; };",
            Path(code_dir)).wraps[0].tu

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


@pytest.mark.xfail()
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


def test_anon_struct_for_field_2():
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


@pytest.mark.xfail(reason="Namespace extraction for inner types is not implemented yet")
def test_namespace_extraction_for_nested_struct():
    struct = get_struct("struct Main { struct Nested {}; Nested field; }")
    field = struct.fields[0]
    assert len(field.type.Spaces) == 1
    assert len(field.type.Spaces[0].name) == "Main"


def test_namespace_extraction():
    struct = get_struct(
        "namespace Space { struct Nest {}; } struct Main { Space::Nest field; };")
    field = struct.fields[0]
    assert len(field.type.Spaces) == 1
    assert field.type.name == "Nest"
    assert field.type.Spaces[0].name == "Space"


def test_nim_record_conversion():
    conv = get_nim_code(get_struct("struct Main {};"))
    assert len(conv.procs) == 0
    assert len(conv.types) == 1
    record = conv.types[0]
    assert record.Name == "Main"
    assert record.Exported == True
    assert any(p.Name == "bycopy" for p in record.Pragmas)


def test_nim_record_field_conversion():
    conv = get_nim_code(get_struct("struct Main { int field; };"))
    assert len(conv.procs) == 0
    assert len(conv.types) == 1
    record = conv.types[0]
    assert record.Name == "Main"
    assert len(record.Fields) == 1
    field = record.Fields[0]
    assert field.Name == "field"
    assert field.Type.Name == "cint"


def test_nim_record_with_compile():
    with TemporaryDirectory() as dir:
        code_dir = Path("/tmp/code_test")
        value = run_provider(
            {
                "file.hpp":
                    """
            #include <cstdio>
            
            struct Test {
                int field = 12;
                int run_method() { puts("-- default constructor"); return 24; }
            };
            """
            },
            code_dir=code_dir)
        tu = value.wraps[0].tu
        assert len(tu.functions) == 0
        assert len(tu.structs) == 1
        assert len(tu.enums) == 0
        assert len(tu.typedefs) == 0
        s = tu.structs[0]
        assert s.name.name == "Test"
        assert len(s.methods) == 1
        assert s.methods[0].name == "run_method"
        assert len(s.fields) == 1
        assert s.fields[0].type.name == "int"
        assert s.methods[0].result.name == "int"

        formatted = format_nim_code(value)

        compile_nim_code(code_dir=code_dir,
                         files={
                             file: res.content for file, res in formatted.items()
                         })

        compile_nim_code(code_dir,
                         files={
                             "main.nim":
                                 """
import file
let value = Test()
echo "value field ", value.field
echo "method field", value.run_method()
"""
                         })

        binary = local[str(code_dir.joinpath("main.bin"))]
        retcode, stdout, stderr = binary.run()
        assert stdout.split("\n")[0:3] == ['value field 0', '-- default constructor', 'method field24']
