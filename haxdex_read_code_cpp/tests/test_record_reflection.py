from pathlib import Path

import pytest
import refl_test_driver
from beartype import beartype

import haxdex_read_code_cpp.proto as pb


@beartype
def template_group(record: pb.Record) -> pb.TemplateGroup:
    assert record.is_template_record
    assert len(record.templates) == 1
    assert len(record.templates[0].stacks) == 1
    return record.templates[0].stacks[0]


@beartype
def template_param(record: pb.Record) -> pb.TemplateParam:
    group = template_group(record)
    assert len(group.params) == 1
    return group.params[0]


@beartype
def nested_template_param(param: pb.TemplateParam) -> pb.TemplateParam:
    assert len(param.template_params) == 1
    assert len(param.template_params[0].stacks) == 1
    group = param.template_params[0].stacks[0]
    assert len(group.params) == 1
    return group.params[0]


@beartype
def qualified_spaces(typ: pb.QualType) -> list[pb.QualType]:
    result: list[pb.QualType] = []
    for space in typ.spaces:
        result.extend(qualified_spaces(space))
        result.append(space)
    return result


@pytest.mark.test_release
def test_simple_structure_registration(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        "struct Test {};",
        stable_test_dir=stable_test_dir,
    )

    assert record.name.name == "Test"
    assert len(record.methods) == 0
    assert len(record.fields) == 0


@pytest.mark.test_release
def test_structure_field_registration(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        "struct Test { int field; };",
        stable_test_dir=stable_test_dir,
    )

    assert len(record.fields) == 1
    field = record.fields[0]
    assert field.name == "field"
    assert field.type.name == "int"


@pytest.mark.test_release
def test_anon_structure_fields(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        "struct Main { union { int int_field; char char_field; }; };",
        stable_test_dir=stable_test_dir,
    )

    assert len(record.nested_rec) == 1
    union = record.nested_rec[0]
    assert union.is_union
    assert not union.has_name
    assert len(union.fields) == 2

    field1 = union.fields[0]
    field2 = union.fields[1]
    assert field1.name == "int_field"
    assert field2.name == "char_field"
    assert field1.type.name == "int"
    assert field2.type.name == "char"


@pytest.mark.test_release
def test_field_with_std_import(stable_test_dir: Path) -> None:
    tu = refl_test_driver.get_tu(
        "#include <vector>\nstruct Content { std::vector<int> items; };",
        stable_test_dir=stable_test_dir,
    )

    assert len(tu.records) == 1
    assert len(tu.enums) == 0
    assert len(tu.functions) == 0
    assert len(tu.typedefs) == 0

    record = tu.records[0]
    assert record.name.name == "Content"
    assert len(record.fields) == 1

    field = record.fields[0]
    assert field.name == "items"
    assert field.type.name == "vector"
    assert len(field.type.spaces) == 1
    assert field.type.spaces[0].name == "std"
    assert len(field.type.parameters) == 1
    assert field.type.parameters[0].name == "int"


@pytest.mark.test_release
def test_anon_struct_for_field(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        "struct Main { struct { int nested; } field; };",
        code_dir_override=stable_test_dir / "code_dir_override",
        stable_test_dir=stable_test_dir,
    )

    assert record.name.name == "Main"
    assert len(record.nested_rec) == 0
    assert len(record.fields) == 1
    assert len(record.methods) == 0

    field = record.fields[0]
    assert field.is_type_decl
    assert field.name == "field"

    declaration = field.type_decl
    assert len(declaration.fields) == 1
    assert declaration.fields[0].name == "nested"


@pytest.mark.test_release
def test_anon_struct_for_field_2(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        "struct Main { struct Named { int nested; } field; };",
        stable_test_dir=stable_test_dir,
    )

    assert record.name.name == "Main"
    assert len(record.nested_rec) == 1
    assert len(record.fields) == 1
    assert len(record.methods) == 0

    nested = record.nested_rec[0]
    field = record.fields[0]
    assert nested.name.name == "Named"
    assert field.name == "field"
    assert field.type.name == "Named"


@pytest.mark.test_release
def test_namespace_extraction_for_nested_struct(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        "struct Main { struct Nested {}; Nested field; };",
        code_dir_override=stable_test_dir / "code_dir_override",
        stable_test_dir=stable_test_dir,
    )

    assert len(record.fields) == 1
    field = record.fields[0]
    assert len(field.type.spaces) == 1
    assert field.type.spaces[0].name == "Main"


@pytest.mark.test_release
def test_namespace_extraction(stable_test_dir: Path) -> None:
    tu = refl_test_driver.get_tu(
        "namespace Space { struct Nest {}; } struct Main { Space::Nest field; };",
        stable_test_dir=stable_test_dir,
    )

    assert len(tu.records) == 2
    record = next(record for record in tu.records if record.name.name == "Main")
    assert len(record.fields) == 1

    field = record.fields[0]
    assert len(field.type.spaces) == 1
    assert field.type.name == "Nest"
    assert field.type.spaces[0].name == "Space"


@pytest.mark.test_release
def test_record_method_reflection(stable_test_dir: Path) -> None:
    tu = refl_test_driver.get_tu(
        """
        #include <cstdio>

        struct Test {
            int field = 12;
            int run_method() { puts("-- default constructor"); return 24; }
        };
        """,
        stable_test_dir=stable_test_dir,
    )

    assert len(tu.functions) == 0
    assert len(tu.records) == 1
    assert len(tu.enums) == 0
    assert len(tu.typedefs) == 0

    record = tu.records[0]
    assert record.name.name == "Test"
    assert len(record.methods) == 1
    assert record.methods[0].name == "run_method"
    assert record.methods[0].return_ty.name == "int"
    assert len(record.fields) == 1
    assert record.fields[0].type.name == "int"


@pytest.mark.test_release
def test_annotated_declaration(stable_test_dir: Path) -> None:
    tu = refl_test_driver.get_tu(
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
        stable_test_dir=stable_test_dir,
        only_annotated=True,
    )

    assert len(tu.records) == 2
    assert tu.records[0].name.name == "AnnotatedStruct"
    assert tu.records[1].name.name == "PartiallyAnnotatedFields"

    partial = tu.records[1]
    assert len(partial.fields) == 2
    assert partial.fields[0].name == "field1"
    assert partial.fields[1].name == "field2"

    assert len(tu.functions) == 1
    assert tu.functions[0].name == "function_with_annotation"


@pytest.mark.test_release
def test_reflection_bases(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        """
        struct A {};
        struct B {};
        template <typename T1, typename T2> struct C {};
        struct [[refl]] Derived : public A, public B, public C<int, float> {};
        """,
        stable_test_dir=stable_test_dir,
        only_annotated=True,
    )

    assert record.name.name == "Derived"
    assert len(record.bases) == 3
    assert record.bases[0].name.name == "A"
    assert record.bases[1].name.name == "B"
    assert record.bases[2].name.name == "C"
    assert len(record.bases[2].name.parameters) == 2
    assert record.bases[2].name.parameters[0].name == "int"
    assert record.bases[2].name.parameters[1].name == "float"


@pytest.mark.test_release
def test_trivial_method_reflection(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
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

    assert record.name.name == "Derived"
    assert len(record.methods) == 6
    methods = record.methods

    assert methods[0].name == "test1"
    assert methods[0].return_ty.name == "int"

    assert methods[1].name == "test2"
    assert methods[1].return_ty.name == "void"

    assert methods[2].name == "test3"
    assert methods[2].return_ty.name == "int"
    assert methods[2].is_const
    assert methods[2].is_virtual
    assert methods[2].is_pure_virtual

    assert methods[3].name == "test4"
    assert methods[3].return_ty.name == "int"
    assert methods[3].is_const
    assert methods[3].is_virtual

    assert methods[4].name == "test5"
    assert methods[4].return_ty.name == "int"
    assert len(methods[4].args) == 1
    assert methods[4].args[0].type.name == "int"
    assert methods[4].args[0].default.value == "5"
    assert methods[4].args[0].name == "default_value"

    assert methods[5].name == "test6"
    assert methods[5].return_ty.name == "int"
    assert methods[5].is_static


@pytest.mark.test_release
def test_type_cross_dependency(stable_test_dir: Path) -> None:
    result = refl_test_driver.run_reflection_tool_provider(
        {
            "a.hpp": "struct B; struct A { B* field; };",
            "b.hpp": "struct A; struct B { A* field; };",
        },
        code_dir=stable_test_dir,
        output_dir=stable_test_dir,
    )

    assert len(result.tus) == 2

    a = next(tu for tu in result.tus if Path(tu.absolute_path).name == "a.hpp")
    b = next(tu for tu in result.tus if Path(tu.absolute_path).name == "b.hpp")

    assert Path(a.absolute_path) == (stable_test_dir / "a.hpp").resolve()
    assert Path(b.absolute_path) == (stable_test_dir / "b.hpp").resolve()
    assert len(a.functions) == 0
    assert len(b.functions) == 0
    assert len(a.records) == 2
    assert len(b.records) == 2

    assert a.records[0].is_forward_decl
    assert b.records[0].is_forward_decl
    assert a.records[0].name.name == "B"
    assert b.records[0].name.name == "A"

    a_record = a.records[1]
    b_record = b.records[1]
    assert a_record.name.name == "A"
    assert b_record.name.name == "B"
    assert len(a_record.fields) == 1
    assert len(b_record.fields) == 1
    assert a_record.fields[0].name == "field"
    assert b_record.fields[0].name == "field"
    assert a_record.fields[0].type.name == "B"
    assert b_record.fields[0].type.name == "A"
    assert any(qualifier.is_pointer for qualifier in a_record.fields[0].type.qualifiers)
    assert any(qualifier.is_pointer for qualifier in b_record.fields[0].type.qualifiers)


@pytest.mark.test_release
def test_templates_record(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        """
        template <typename Arg>
        concept ILabel = requires(Arg v)
        {
            typename Arg::nested;
        };

        template <ILabel T>
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

    assert record.name.name == "Templated"
    assert len(record.fields) == 1
    assert len(record.methods) == 3

    param = template_param(record)
    assert param.type_expr.name == "T"
    assert param.concept == "ILabel"

    method0 = record.methods[0]
    method1 = record.methods[1]
    method2 = record.methods[2]

    assert method0.name == "get_content"
    assert method0.return_ty.name == "T"
    assert method0.return_ty.is_template_type_param
    assert len(method0.return_ty.spaces) == 0

    assert method1.name == "get_nested"
    assert method1.return_ty.name == "nested"
    assert method1.return_ty.is_template_injected_type
    assert not method1.return_ty.is_template_type_param
    assert len(method1.return_ty.spaces) == 1

    assert method1.return_ty
    scope1 = qualified_spaces(method1.return_ty)
    assert len(scope1) == 1
    assert scope1[0].name == "T"
    assert scope1[0].is_template_type_param
    assert not scope1[0].is_template_injected_type

    assert method2.name == "get_multi_nested"
    assert method2.return_ty.name == "second"
    assert method2.return_ty.is_template_injected_type
    assert not method2.return_ty.is_template_type_param
    assert method2.return_ty

    scope2 = qualified_spaces(method2.return_ty)
    assert len(scope2) == 2
    assert scope2[0].name == "T"
    assert scope2[0].is_template_type_param
    assert not scope2[0].is_template_injected_type
    assert scope2[1].name == "multi_nested"
    assert not scope2[1].is_template_type_param
    assert scope2[1].is_template_injected_type


@pytest.mark.test_release
def test_templates_record_type_param_plain(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        """
        template <typename T>
        struct [[refl]] Box {};
        """,
        stable_test_dir=stable_test_dir,
        only_annotated=True,
        reflection_run_verbose=True,
    )

    assert record.name.name == "Box"
    param = template_param(record)
    assert param.kind == pb.TemplateParamKind.TYPE
    assert param.type_expr.name == "T"
    assert param.type_expr.is_template_type_param
    assert not param.variadic
    assert param.concept == ""
    assert len(param.default) == 0
    assert len(param.template_params) == 0


@pytest.mark.test_release
def test_templates_record_type_param_default(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        """
        struct DefaultType {};

        template <typename T = DefaultType>
        struct [[refl]] Box {};
        """,
        stable_test_dir=stable_test_dir,
        only_annotated=True,
        reflection_run_verbose=True,
    )

    assert record.name.name == "Box"
    param = template_param(record)
    assert param.kind == pb.TemplateParamKind.TYPE
    assert param.type_expr.name == "T"
    assert len(param.default) == 1
    assert param.default[0].name == "DefaultType"


@pytest.mark.test_release
def test_templates_record_variadic_type_param(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        """
        template <typename... Ts>
        struct [[refl]] Pack {};
        """,
        stable_test_dir=stable_test_dir,
        only_annotated=True,
        reflection_run_verbose=True,
    )

    assert record.name.name == "Pack"
    param = template_param(record)
    assert param.kind == pb.TemplateParamKind.TYPE
    assert param.type_expr.name == "Ts"
    assert param.variadic
    assert param.type_expr.is_template_type_param


@pytest.mark.test_release
def test_templates_record_non_type_param(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        """
        template <int N>
        struct [[refl]] Sized {};
        """,
        stable_test_dir=stable_test_dir,
        only_annotated=True,
        reflection_run_verbose=True,
    )

    assert record.name.name == "Sized"
    param = template_param(record)
    assert param.kind == pb.TemplateParamKind.NON_TYPE
    assert param.type_expr.name == "N"
    assert len(param.non_type_constraint) == 1
    assert param.non_type_constraint[0].name == "int"
    assert not param.variadic
    assert param.concept == ""
    assert len(param.default) == 0
    assert len(param.template_params) == 0


@pytest.mark.test_release
def test_templates_record_non_type_param_default(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        """
        template <int N = 8>
        struct [[refl]] Sized {};
        """,
        stable_test_dir=stable_test_dir,
        only_annotated=True,
        reflection_run_verbose=True,
    )

    assert record.name.name == "Sized"
    param = template_param(record)
    assert param.kind == pb.TemplateParamKind.NON_TYPE
    assert param.type_expr.name == "N"
    assert len(param.default) == 1


@pytest.mark.test_release
def test_templates_record_auto_non_type_param(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        """
        template <auto V>
        struct [[refl]] ValueHolder {};
        """,
        stable_test_dir=stable_test_dir,
        only_annotated=True,
        reflection_run_verbose=True,
    )

    assert record.name.name == "ValueHolder"
    param = template_param(record)
    assert param.kind == pb.TemplateParamKind.TYPE
    assert param.type_expr.name == "V"


@pytest.mark.test_release
def test_templates_record_template_template_param(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        """
        template <template <typename> typename TT>
        struct [[refl]] Wrapper {};
        """,
        stable_test_dir=stable_test_dir,
        only_annotated=True,
        reflection_run_verbose=True,
    )

    assert record.name.name == "Wrapper"
    param = template_param(record)
    assert param.kind == pb.TemplateParamKind.TEMPLATE
    assert param.type_expr.name == "TT"
    assert param.type_expr.is_template_type_param

    nested = nested_template_param(param)
    assert nested.kind == pb.TemplateParamKind.TYPE
    assert nested.type_expr.name == ""
    assert nested.type_expr.is_template_type_param
    assert not nested.variadic


@pytest.mark.test_release
def test_templates_record_template_template_param_named_nested(
    stable_test_dir: Path,
) -> None:
    record = refl_test_driver.get_struct(
        """
        template <template <typename U> typename TT>
        struct [[refl]] Wrapper {};
        """,
        stable_test_dir=stable_test_dir,
        only_annotated=True,
        reflection_run_verbose=True,
    )

    assert record.name.name == "Wrapper"
    param = template_param(record)
    assert param.kind == pb.TemplateParamKind.TEMPLATE
    assert param.type_expr.name == "TT"

    nested = nested_template_param(param)
    assert nested.kind == pb.TemplateParamKind.TYPE
    assert nested.type_expr.name == "U"


@pytest.mark.test_release
def test_templates_record_template_template_param_with_non_type_nested(
    stable_test_dir: Path,
) -> None:
    record = refl_test_driver.get_struct(
        """
        template <template <int N> typename TT>
        struct [[refl]] Wrapper {};
        """,
        stable_test_dir=stable_test_dir,
        only_annotated=True,
        reflection_run_verbose=True,
    )

    assert record.name.name == "Wrapper"
    param = template_param(record)
    assert param.kind == pb.TemplateParamKind.TEMPLATE
    assert param.type_expr.name == "TT"

    nested = nested_template_param(param)
    assert nested.kind == pb.TemplateParamKind.NON_TYPE
    assert nested.type_expr.name == "N"
    assert len(nested.non_type_constraint) == 1
    assert nested.non_type_constraint[0].name == "int"


@pytest.mark.test_release
def test_templates_record_mixed_params(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        """
        template <typename T, int N, template <typename> typename TT>
        struct [[refl]] Mixed {};
        """,
        stable_test_dir=stable_test_dir,
        only_annotated=True,
        reflection_run_verbose=True,
    )

    assert record.name.name == "Mixed"
    group = template_group(record)
    assert len(group.params) == 3

    param0 = group.params[0]
    param1 = group.params[1]
    param2 = group.params[2]

    assert param0.kind == pb.TemplateParamKind.TYPE
    assert param0.type_expr.name == "T"

    assert param1.kind == pb.TemplateParamKind.NON_TYPE
    assert param1.type_expr.name == "N"
    assert len(param1.non_type_constraint) == 1
    assert param1.non_type_constraint[0].name == "int"

    assert param2.kind == pb.TemplateParamKind.TEMPLATE
    assert param2.type_expr.name == "TT"

    nested = nested_template_param(param2)
    assert nested.kind == pb.TemplateParamKind.TYPE


@pytest.mark.test_release
def test_templates_record_constrained_and_defaulted_params(
    stable_test_dir: Path,
) -> None:
    record = refl_test_driver.get_struct(
        """
        template <typename Arg>
        concept HasNested = requires(Arg v)
        {
            typename Arg::nested;
        };

        struct DefaultType {};

        template <HasNested T, typename U = DefaultType>
        struct [[refl]] Constrained {};
        """,
        stable_test_dir=stable_test_dir,
        only_annotated=True,
        reflection_run_verbose=True,
    )

    assert record.name.name == "Constrained"
    group = template_group(record)
    assert len(group.params) == 2

    param0 = group.params[0]
    param1 = group.params[1]

    assert param0.kind == pb.TemplateParamKind.TYPE
    assert param0.type_expr.name == "T"
    assert param0.concept == "HasNested"
    assert len(param0.default) == 0

    assert param1.kind == pb.TemplateParamKind.TYPE
    assert param1.type_expr.name == "U"
    assert param1.concept == ""
    assert len(param1.default) == 1
    assert param1.default[0].name == "DefaultType"
