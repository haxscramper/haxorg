from py_scriptutils import configure_asan
import itertools
from pathlib import Path
from tempfile import TemporaryDirectory
from pprint import pprint
from more_itertools import first_true
import pytest
from tempfile import gettempdir
# import py_scriptutils.script_logging

import os
from beartype.typing import TYPE_CHECKING
if os.getenv("HAXORG_REDUCED_RELEASE_TEST") and not TYPE_CHECKING:
    from py_scriptutils.test_utils import HasAnyAttr
    refl_test_driver = HasAnyAttr()
else:
    import refl_test_driver

if os.getenv("HAXORG_REDUCED_RELEASE_TEST") and not TYPE_CHECKING:
    from py_scriptutils.test_utils import HasAnyAttr
    gen_nim = HasAnyAttr()
else:
    import py_codegen.wrapper_gen_nim as gen_nim

import pytest


@pytest.mark.test_release
def test_simple_structure_registration():
    struct = refl_test_driver.get_struct("struct Test {};")
    assert struct.name.name == "Test"
    assert len(struct.methods) == 0
    assert len(struct.fields) == 0


@pytest.mark.test_release
def test_structure_field_registration():
    struct = refl_test_driver.get_struct("struct Test { int field; };")
    assert len(struct.fields) == 1
    field = struct.fields[0]
    assert field.name == "field"
    assert field.type.name == "int"


@pytest.mark.test_release
def test_anon_structure_fields():
    struct = refl_test_driver.get_struct(
        "struct Main { union { int int_field; char char_field; }; };")
    assert len(struct.nested) == 1
    union: refl_test_driver.GenTuStruct = struct.nested[0]
    assert not union.has_name
    assert len(union.fields) == 2
    field1 = union.fields[0]
    field2 = union.fields[1]
    assert field1.name == "int_field"
    assert field2.name == "char_field"
    assert field1.type.name == "int"
    assert field2.type.name == "char"


@pytest.mark.test_release
def test_field_with_std_import():
    with TemporaryDirectory() as dir:
        code_dir = Path(dir)
        tu = refl_test_driver.run_provider(
            "#include <vector>\nstruct Content { std::vector<int> items; };",
            code_dir).wraps[0].tu

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


@pytest.mark.test_release
def test_anon_struct_for_field():
    struct = refl_test_driver.get_struct(
        "struct Main { struct { int nested; } field; };",
        code_dir_override=Path(gettempdir()) / "code_dir_override",
    )
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


@pytest.mark.test_release
def test_anon_struct_for_field_2():
    struct = refl_test_driver.get_struct(
        "struct Main { struct Named { int nested; } field; };")
    assert struct.name.name == "Main"
    assert len(struct.nested) == 1
    assert len(struct.fields) == 1
    assert len(struct.methods) == 0
    nested = struct.nested[0]
    field = struct.fields[0]

    assert nested.name.name == "Named"
    assert field.name == "field"
    assert field.type.name == "Named"


@pytest.mark.test_release
def test_namespace_extraction_for_nested_struct():
    struct = refl_test_driver.get_struct(
        "struct Main { struct Nested {}; Nested field; };",
        code_dir_override=Path(gettempdir()) /
        "test_namespace_extraction_for_nested_struct")
    field = struct.fields[0]
    assert len(field.type.Spaces) == 1
    assert field.type.Spaces[0].name == "Main"


@pytest.mark.test_release
def test_namespace_extraction():
    entires = refl_test_driver.get_entires(
        "namespace Space { struct Nest {}; } struct Main { Space::Nest field; };")
    struct: refl_test_driver.GenTuStruct = entires[1]
    field = struct.fields[0]
    assert len(field.type.Spaces) == 1
    assert field.type.name == "Nest"
    assert field.type.Spaces[0].name == "Space"


@pytest.mark.test_release
def test_nim_record_conversion():
    conv = refl_test_driver.get_nim_code(refl_test_driver.get_struct("struct Main {};"))
    assert len(conv.procs) == 0
    assert len(conv.types) == 1
    record = conv.types[0]
    assert record.Name == "Main"
    assert record.Exported
    assert any(p.Name == "bycopy" for p in record.Pragmas)


@pytest.mark.test_release
def test_nim_record_field_conversion():
    conv = refl_test_driver.get_nim_code(
        refl_test_driver.get_struct("struct Main { int field; };"))
    assert len(conv.procs) == 0
    assert len(conv.types) == 1
    record = conv.types[0]
    assert record.Name == "Main"
    assert len(record.Fields) == 1
    field = record.Fields[0]
    assert field.Name == "field"
    assert field.Type.Name == "cint"


@pytest.mark.test_release
def test_nim_record_with_compile():
    with TemporaryDirectory() as dir:
        code_dir = Path(dir)
        value = refl_test_driver.run_provider(
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

        formatted = refl_test_driver.format_nim_code(value)
        if refl_test_driver.has_nim_installed():
            _, stdout, _ = refl_test_driver.verify_nim_code(
                code_dir, formatted, """
import file
let value = Test()
echo "value field ", value.field
echo "method field", value.run_method()
""")

            assert stdout.split("\n")[0:3] == [
                'value field 0', '-- default constructor', 'method field24'
            ]


@pytest.mark.test_release
def test_type_cross_dependency():
    with TemporaryDirectory() as dir:
        code_dir = Path(dir)
        value = refl_test_driver.run_provider(
            {
                "a.hpp": "struct B; struct A { B* field; };",
                "b.hpp": "struct A; struct B { A* field; };"
            },
            code_dir=code_dir)

        assert len(value.wraps) == 2
        a = first_true(value.wraps, pred=lambda it: it.name == "a")
        b = first_true(value.wraps, pred=lambda it: it.name == "b")
        assert a
        assert b
        assert a.name == "a"
        assert b.name == "b"

        assert all([it.original == code_dir.joinpath("a.hpp") for it in a.tu.structs])
        assert all([it.original == code_dir.joinpath("b.hpp") for it in b.tu.structs])

        assert len(a.tu.functions) == 0
        assert len(b.tu.functions) == 0
        assert len(a.tu.structs) == 2
        assert len(b.tu.structs) == 2
        assert a.tu.structs[0].IsForwardDecl
        assert b.tu.structs[0].IsForwardDecl
        assert a.tu.structs[0].name.name == "B", [s.name.name for s in a.tu.structs]
        assert b.tu.structs[0].name.name == "A", [s.name.name for s in b.tu.structs]

        formatted = refl_test_driver.format_nim_code(value)
        assert "a.nim" in formatted
        res = formatted["a.nim"]
        assert len(res.conv) == 2

        types = list(itertools.chain(*[conv.types for conv in res.conv]))

        a_wrap: gen_nim.nim.ObjectParams = first_true(types,
                                                      pred=lambda it: it.Name == "A")
        b_wrap: gen_nim.nim.ObjectParams = first_true(types,
                                                      pred=lambda it: it.Name == "B")
        assert a_wrap
        assert b_wrap

        assert a_wrap.Fields[0].Name == "field"
        assert a_wrap.Fields[0].Type.Name == "ptr"
        assert b_wrap.Fields[0].Type.Name == "ptr"
        assert a_wrap.Fields[0].Type.Parameters[0].Name == "B"
        assert b_wrap.Fields[0].Type.Parameters[0].Name == "A"

        if refl_test_driver.has_nim_installed():
            refl_test_driver.verify_nim_code(code_dir, formatted,
                                             "import a; echo A(), B()")
