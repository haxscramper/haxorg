from pathlib import Path

import pytest
from beartype import beartype
from refl_test_driver import get_type

import haxdex_read_code_cpp.proto as pb


@pytest.mark.test_release
@pytest.mark.parametrize("type_name", ["int", "char", "bool", "float"])
@beartype
def test_primitive_type(stable_test_dir: Path, type_name: str) -> None:
    typ = get_type(
        stable_test_dir=stable_test_dir,
        preamble=[],
        typ=type_name,
    )

    assert typ.name == type_name
    assert typ.is_builtin


@pytest.mark.test_release
@beartype
def test_primitive_type_const(stable_test_dir: Path) -> None:
    typ = get_type(
        stable_test_dir=stable_test_dir,
        preamble=[],
        typ="int const",
    )

    assert typ.name == "int"
    assert typ.is_builtin
    assert any(qualifier.is_const for qualifier in typ.qualifiers)
    assert sum(qualifier.is_pointer for qualifier in typ.qualifiers) == 0


@pytest.mark.test_release
@beartype
def test_primitive_type_const_ptr(stable_test_dir: Path) -> None:
    typ = get_type(
        stable_test_dir=stable_test_dir,
        preamble=[],
        typ="int const*",
    )

    assert typ.name == "int"
    assert typ.is_builtin
    assert any(qualifier.is_const for qualifier in typ.qualifiers)
    assert sum(qualifier.is_pointer for qualifier in typ.qualifiers) == 1


@pytest.mark.test_release
@beartype
def test_user_defined(stable_test_dir: Path) -> None:
    typ = get_type(
        stable_test_dir=stable_test_dir,
        preamble=["struct UserDefined {};"],
        typ="UserDefined",
    )

    assert typ.name == "UserDefined"
    assert not typ.is_builtin


@pytest.mark.test_release
@beartype
def test_user_defined_template(stable_test_dir: Path) -> None:
    typ = get_type(
        stable_test_dir=stable_test_dir,
        preamble=["template <typename T> struct Templ {};"],
        typ="Templ<int>",
    )

    assert typ.name == "Templ"
    assert len(typ.parameters) == 1
    assert typ.parameters[0].name == "int"
    assert typ.parameters[0].is_builtin


@pytest.mark.test_release
@beartype
def test_enum_class(stable_test_dir: Path) -> None:
    typ = get_type(
        stable_test_dir=stable_test_dir,
        preamble=["enum class TestEnum {};"],
        typ="TestEnum",
    )

    assert typ.name == "TestEnum"


@pytest.mark.test_release
@beartype
def test_namespaced_user_defined(stable_test_dir: Path) -> None:
    typ = get_type(
        stable_test_dir=stable_test_dir,
        preamble=[
            """
            namespace ns {
                struct UserDefined {};
            }
            """
        ],
        typ="ns::UserDefined",
    )

    assert typ.name == "UserDefined"
    assert not typ.is_builtin
    assert [space.name for space in typ.spaces] == ["ns"]
    assert all(space.is_namespace for space in typ.spaces)


@pytest.mark.test_release
@beartype
def test_nested_namespaces(stable_test_dir: Path) -> None:
    typ = get_type(
        stable_test_dir=stable_test_dir,
        preamble=[
            """
            namespace n1 {
                namespace n2 {
                    struct DeepType {};
                }
            }
            """
        ],
        typ="n1::n2::DeepType",
    )

    assert typ.name == "DeepType"
    assert [space.name for space in typ.spaces] == ["n1", "n2"]
    assert all(space.is_namespace for space in typ.spaces)


@pytest.mark.test_release
@beartype
def test_namespace_alias_is_expanded(stable_test_dir: Path) -> None:
    typ = get_type(
        stable_test_dir=stable_test_dir,
        preamble=[
            """
            namespace real_ns {
                struct AliasTarget {};
            }
            namespace alias_ns = real_ns;
            """
        ],
        typ="alias_ns::AliasTarget",
    )

    assert typ.name == "AliasTarget"
    assert [space.name for space in typ.spaces] == ["real_ns"]
    assert all(space.is_namespace for space in typ.spaces)


@pytest.mark.test_release
@beartype
def test_nested_type_qualifier(stable_test_dir: Path) -> None:
    typ = get_type(
        stable_test_dir=stable_test_dir,
        preamble=[
            """
            struct Outer {
                struct Inner {};
            };
            """
        ],
        typ="Outer::Inner",
    )

    assert typ.name == "Inner"
    assert [space.name for space in typ.spaces] == ["Outer"]
    assert not typ.spaces[0].is_namespace


@pytest.mark.test_release
@beartype
def test_namespaced_template(stable_test_dir: Path) -> None:
    typ = get_type(
        stable_test_dir=stable_test_dir,
        preamble=[
            """
            namespace tpl_ns {
                template <typename T>
                struct Box {};
            }
            """
        ],
        typ="tpl_ns::Box<int>",
    )

    assert typ.name == "Box"
    assert [space.name for space in typ.spaces] == ["tpl_ns"]
    assert len(typ.parameters) == 1
    assert typ.parameters[0].name == "int"
    assert typ.parameters[0].is_builtin


@pytest.mark.test_release
@beartype
def test_global_namespace_qualified(stable_test_dir: Path) -> None:
    typ = get_type(
        stable_test_dir=stable_test_dir,
        preamble=[
            """
            namespace top {
                struct GlobalRef {};
            }
            """
        ],
        typ="::top::GlobalRef",
    )

    assert typ.name == "GlobalRef"
    assert [space.name for space in typ.spaces] == ["top"]


@pytest.mark.test_release
@beartype
def test_fixed_size_array_type(stable_test_dir: Path) -> None:
    typ = get_type(
        stable_test_dir=stable_test_dir,
        preamble=[],
        field_decl="[[refl]] int field[8];",
    )

    assert typ.kind == pb.TypeKind.Array
    assert typ.name == "ConstantArray"
    assert len(typ.parameters) == 2

    element = typ.parameters[0]
    extent = typ.parameters[1]
    assert element.name == "int"
    assert element.kind == pb.TypeKind.RegularType
    assert extent.type_value.value == "8"
    assert extent.kind == pb.TypeKind.TypeExpr


@pytest.mark.test_release
@beartype
def test_multidim_array_type(stable_test_dir: Path) -> None:
    typ = get_type(
        stable_test_dir=stable_test_dir,
        preamble=[],
        field_decl="[[refl]] float field[2][4];",
    )

    assert typ.kind == pb.TypeKind.Array
    assert len(typ.parameters) == 2
    assert typ.parameters[1].type_value.value == "2"

    inner = typ.parameters[0]
    assert inner.kind == pb.TypeKind.Array
    assert len(inner.parameters) == 2
    assert inner.parameters[0].name == "float"
    assert inner.parameters[1].type_value.value == "4"


@pytest.mark.test_release
@beartype
def test_function_pointer_type(stable_test_dir: Path) -> None:
    typ = get_type(
        stable_test_dir=stable_test_dir,
        preamble=[],
        field_decl="[[refl]] int (*field)(double, char const*);",
    )

    assert typ.kind == pb.TypeKind.FunctionPtr
    assert len(typ.parameters) == 3

    result = typ.parameters[0]
    first_argument = typ.parameters[1]
    second_argument = typ.parameters[2]

    assert result.name == "int"
    assert first_argument.name == "double"
    assert second_argument.name == "char"
    assert sum(qualifier.is_pointer for qualifier in second_argument.qualifiers) == 1
    assert any(qualifier.is_const for qualifier in second_argument.qualifiers)
