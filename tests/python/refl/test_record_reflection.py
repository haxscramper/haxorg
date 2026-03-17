import itertools
from pathlib import Path
from tempfile import gettempdir

from more_itertools import first_true
import pytest


@pytest.mark.test_release
def test_simple_structure_registration(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    struct = refl_test_driver.get_struct(
        "struct Test {};",
        stable_test_dir=stable_test_dir,
    )
    assert struct.Name.Name == "Test"
    assert len(struct.Methods) == 0
    assert len(struct.Fields) == 0


@pytest.mark.test_release
def test_structure_field_registration(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    struct = refl_test_driver.get_struct(
        "struct Test { int field; };",
        stable_test_dir=stable_test_dir,
    )
    assert len(struct.Fields) == 1
    field = struct.Fields[0]
    assert field.Name == "field"
    assert field.Type.Name == "int"


@pytest.mark.test_release
def test_anon_structure_fields(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    struct = refl_test_driver.get_struct(
        "struct Main { union { int int_field; char char_field; }; };",
        stable_test_dir=stable_test_dir,
    )
    assert len(struct.Nested) == 1
    union: refl_test_driver.GenTuStruct = struct.Nested[0]
    assert not union.HasName
    assert len(union.Fields) == 2
    field1 = union.Fields[0]
    field2 = union.Fields[1]
    assert field1.Name == "int_field"
    assert field2.Name == "char_field"
    assert field1.Type.Name == "int"
    assert field2.Type.Name == "char"


@pytest.mark.test_release
def test_field_with_std_import(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    code_dir = Path(stable_test_dir)
    tu = refl_test_driver.run_reflection_tool_provider(
        "#include <vector>\nstruct Content { std::vector<int> items; };",
        code_dir,
        output_dir=stable_test_dir,
    ).wraps[0].tu

    assert len(tu.structs) == 1
    assert len(tu.enums) == 0
    assert len(tu.functions) == 0
    assert len(tu.typedefs) == 0
    struct = tu.structs[0]
    assert struct.Name.Name == "Content"
    assert len(struct.Fields) == 1
    field = struct.Fields[0]
    assert field.Name == "items"
    assert field.Type.Name == "vector"
    assert len(field.Type.Spaces) == 1
    assert field.Type.Spaces[0].Name == "std"
    assert len(field.Type.Params) == 1
    assert field.Type.Params[0].Name == "int"


@pytest.mark.test_release
def test_anon_struct_for_field(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    struct = refl_test_driver.get_struct(
        "struct Main { struct { int nested; } field; };",
        code_dir_override=Path(gettempdir()) / "code_dir_override",
        stable_test_dir=stable_test_dir,
    )

    assert struct.Name.Name == "Main"
    assert len(struct.Nested) == 0
    assert len(struct.Fields) == 1
    assert len(struct.Methods) == 0
    field = struct.Fields[0]
    assert field.IsTypeDecl
    assert field.Name == "field"
    decl = field.Decl
    assert len(decl.Fields) == 1
    assert decl.Fields[0].Name == "nested"


@pytest.mark.test_release
def test_anon_struct_for_field_2(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    struct = refl_test_driver.get_struct(
        "struct Main { struct Named { int nested; } field; };",
        stable_test_dir=stable_test_dir,
    )

    assert struct.Name.Name == "Main"
    assert len(struct.Nested) == 1
    assert len(struct.Fields) == 1
    assert len(struct.Methods) == 0
    nested = struct.Nested[0]
    field = struct.Fields[0]

    assert nested.Name.Name == "Named"
    assert field.Name == "field"
    assert field.Type.Name == "Named"


@pytest.mark.test_release
def test_namespace_extraction_for_nested_struct(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    struct = refl_test_driver.get_struct(
        "struct Main { struct Nested {}; Nested field; };",
        code_dir_override=Path(gettempdir()) /
        "test_namespace_extraction_for_nested_struct",
        stable_test_dir=stable_test_dir,
    )
    field = struct.Fields[0]
    assert len(field.Type.Spaces) == 1
    assert field.Type.Spaces[0].Name == "Main"


@pytest.mark.test_release
def test_namespace_extraction(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    entires = refl_test_driver.get_entires(
        "namespace Space { struct Nest {}; } struct Main { Space::Nest field; };",
        stable_test_dir=stable_test_dir,
    )

    struct: refl_test_driver.GenTuStruct = entires[1]
    field = struct.Fields[0]
    assert len(field.Type.Spaces) == 1
    assert field.Type.Name == "Nest"
    assert field.Type.Spaces[0].Name == "Space"


@pytest.mark.test_release
def test_nim_record_conversion(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    conv = refl_test_driver.get_nim_code(
        refl_test_driver.get_struct(
            "struct Main {};",
            stable_test_dir=stable_test_dir,
        ))

    assert len(conv.procs) == 0
    assert len(conv.types) == 1
    record = conv.types[0]
    assert record.Name == "Main"
    assert record.Exported
    assert any(p.Name == "bycopy" for p in record.Pragmas)


@pytest.mark.test_release
def test_nim_record_field_conversion(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    conv = refl_test_driver.get_nim_code(
        refl_test_driver.get_struct(
            "struct Main { int field; };",
            stable_test_dir=stable_test_dir,
        ))

    assert len(conv.procs) == 0
    assert len(conv.types) == 1
    record = conv.types[0]
    assert record.Name == "Main"
    assert len(record.Fields) == 1
    field = record.Fields[0]
    assert field.Name == "field"
    assert field.Type.Name == "cint"


@pytest.mark.test_release
def test_nim_record_with_compile(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    code_dir = stable_test_dir
    value = refl_test_driver.run_reflection_tool_provider(
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
        code_dir=code_dir,
        output_dir=stable_test_dir,
    )

    tu = value.wraps[0].tu
    assert len(tu.functions) == 0
    assert len(tu.structs) == 1
    assert len(tu.enums) == 0
    assert len(tu.typedefs) == 0
    s = tu.structs[0]
    assert s.Name.Name == "Test"
    assert len(s.Methods) == 1
    assert s.Methods[0].Name == "run_method"
    assert len(s.Fields) == 1
    assert s.Fields[0].Type.Name == "int"
    assert s.Methods[0].ReturnType.Name == "int"

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
def test_annotated_declaration(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    value = refl_test_driver.run_reflection_tool_provider(
        """
struct NotAnnotatedStruct {};
struct [[refl]] AnnotatedStruct {};

void function_no_annotation();
[[refl]] void function_with_annotation();

struct [[refl]] PartiallyAnnotatedFields {
    [[refl]] int field1;
    int field_not_annotated;
    [[refl]] int field2;
};
        """,
        code_dir=stable_test_dir,
        output_dir=stable_test_dir,
        only_annotated=True,
    )

    assert len(value.wraps) == 1
    tu = value.wraps[0].tu

    assert len(tu.structs) == 2
    assert tu.structs[0].Name.Name == "AnnotatedStruct"
    assert tu.structs[1].Name.Name == "PartiallyAnnotatedFields"

    part_a = tu.structs[1]
    assert len(part_a.Fields) == 2
    assert part_a.Fields[0].Name == "field1"
    assert part_a.Fields[1].Name == "field2"

    assert len(tu.functions) == 1
    assert tu.functions[0].Name == "function_with_annotation"


@pytest.mark.test_release
def test_reflection_bases(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    value = refl_test_driver.get_struct(
        """
        struct A {};
        struct B {};
        template <typename T1, typename T2> struct C {};
        struct [[refl]] Derived : public A, public B, public C<int, float> {};
        """,
        stable_test_dir=stable_test_dir,
        only_annotated=True,
    )

    assert value.Name.Name == "Derived"
    assert len(value.Bases) == 3
    assert value.Bases[0].Name == "A"
    assert value.Bases[1].Name == "B"
    assert value.Bases[2].Name == "C"
    assert value.Bases[2].Params[0].Name == "int"
    assert value.Bases[2].Params[1].Name == "float"


@pytest.mark.test_release
def test_trivial_method_reflection(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    value = refl_test_driver.get_struct(
        """
        struct [[refl]] Derived {
            [[refl]] int test1();
            [[refl]] void test2();
            [[refl]] virtual int test3() const = 0;
            [[refl]] virtual int test4() const;
            [[refl]] int test5(int default_value = 5);
            [[refl]] static int test6();
        };
        """,
        stable_test_dir=stable_test_dir,
        only_annotated=True,
    )

    assert value.Name.Name == "Derived"
    assert len(value.Methods) == 6
    m = value.Methods
    assert m[0].Name == "test1"
    assert m[0].ReturnType.Name == "int"

    assert m[1].Name == "test2"
    assert m[1].ReturnType.Name == "void"

    assert m[2].Name == "test3"
    assert m[2].ReturnType.Name == "int"
    assert m[2].IsConst == True
    assert m[2].IsVirtual == True
    assert m[2].IsPureVirtual == True

    assert m[3].Name == "test4"
    assert m[3].ReturnType.Name == "int"
    assert m[3].IsConst == True
    assert m[3].IsVirtual == True

    assert m[4].Name == "test5"
    assert m[4].ReturnType.Name == "int"
    assert len(m[4].Args) == 1
    assert m[4].Args[0].Type.Name == "int"
    assert m[4].Args[0].Value == "5"
    assert m[4].Args[0].Name == "default_value"

    assert m[5].Name == "test6"
    assert m[5].ReturnType.Name == "int"
    assert m[5].IsStatic == True


@pytest.mark.test_release
def test_type_cross_dependency(stable_test_dir: Path) -> None:
    import py_codegen.wrapper_gen_nim as gen_nim

    import tests.python.refl.refl_test_driver as refl_test_driver

    code_dir = stable_test_dir
    value = refl_test_driver.run_reflection_tool_provider(
        {
            "a.hpp": "struct B; struct A { B* field; };",
            "b.hpp": "struct A; struct B { A* field; };"
        },
        code_dir=code_dir,
        output_dir=stable_test_dir,
    )

    assert len(value.wraps) == 2
    a = first_true(value.wraps, pred=lambda it: it.name == "a")
    b = first_true(value.wraps, pred=lambda it: it.name == "b")
    assert a
    assert b
    assert a.name == "a"
    assert b.name == "b"

    assert all([it.OriginalPath == code_dir.joinpath("a.hpp") for it in a.tu.structs])
    assert all([it.OriginalPath == code_dir.joinpath("b.hpp") for it in b.tu.structs])

    assert len(a.tu.functions) == 0
    assert len(b.tu.functions) == 0
    assert len(a.tu.structs) == 2
    assert len(b.tu.structs) == 2
    assert a.tu.structs[0].IsForwardDecl
    assert b.tu.structs[0].IsForwardDecl
    assert a.tu.structs[0].Name.Name == "B", [s.Name.Name for s in a.tu.structs]
    assert b.tu.structs[0].Name.Name == "A", [s.Name.Name for s in b.tu.structs]

    formatted = refl_test_driver.format_nim_code(value)
    assert "a.nim" in formatted
    res = formatted["a.nim"]
    assert len(res.conv) == 2

    types = list(itertools.chain(*[conv.types for conv in res.conv]))

    a_wrap: gen_nim.nim.ObjectParams = first_true(types, pred=lambda it: it.Name == "A")
    b_wrap: gen_nim.nim.ObjectParams = first_true(types, pred=lambda it: it.Name == "B")
    assert a_wrap
    assert b_wrap

    assert a_wrap.Fields[0].Name == "field"
    assert a_wrap.Fields[0].Type.Name == "ptr"
    assert b_wrap.Fields[0].Type.Name == "ptr"
    assert a_wrap.Fields[0].Type.Parameters[0].Name == "B"
    assert b_wrap.Fields[0].Type.Parameters[0].Name == "A"

    if refl_test_driver.has_nim_installed():
        refl_test_driver.verify_nim_code(code_dir, formatted, "import a; echo A(), B()")


@pytest.mark.test_release
def test_templates_record(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    value = refl_test_driver.get_struct(
        """
        template <typename T>
        struct [[refl]] Templated {
            [[refl]] T get_content();
            [[refl]] T::nested get_nested();
            [[refl]] T value_field;
            [[refl]] T::multi_nested::second get_multi_nested();
        };
        """,
        stable_test_dir=stable_test_dir,
        only_annotated=True,
        reflection_run_verbose=True,
    )
