from pathlib import Path

from setuptools.build_meta import prepare_metadata_for_build_editable

import py_codegen.astbuilder_cpp as cpp
from py_codegen.codegen_ir import QualTypeKind
from beartype.typing import List, Optional
import pytest

from py_scriptutils.repo_files import get_haxorg_repo_root_path
from tests.python.conf_test_common import WithBinaryCoverageTest


def get_type(
    stable_test_dir: Path,
    stable_unique_test_name: str,
    preamble: List[str],
    typ: str = "",
    verbose: bool = False,
    struct_header: str = "struct [[refl]] test",
    field_decl: Optional[str] = None,
) -> cpp.QualType:
    "Utility function to get reflection type value"
    import tests.python.refl.refl_test_driver as refl_test_driver
    with WithBinaryCoverageTest(
            test_binary=f"{get_haxorg_repo_root_path()}/build/haxorg/reflection_tool",
            uniq_name=stable_unique_test_name,
            coverage_out_dir=stable_test_dir) as profraw_path:
        t = refl_test_driver.get_type(
            preamble=preamble,
            typ=typ,
            stable_test_dir=stable_test_dir,
            reflection_tool_profraw_path=profraw_path,
            reflection_run_verbose=verbose,
            struct_header=struct_header,
            field_decl=field_decl,
        )
    return t


@pytest.mark.test_release
@pytest.mark.parametrize("type_name", ["int", "char", "bool", "float"])
def test_primitive_type(stable_test_dir: Path, stable_unique_test_name: str,
                        type_name: str):
    t = get_type(
        stable_test_dir=stable_test_dir,
        stable_unique_test_name=stable_unique_test_name,
        preamble=[],
        typ=type_name,
    )
    assert t.name == type_name
    assert t.isPrimitive() == True


@pytest.mark.test_release
def test_primitive_type_const(stable_test_dir: Path, stable_unique_test_name: str):
    t = get_type(
        stable_test_dir=stable_test_dir,
        stable_unique_test_name=stable_unique_test_name,
        preamble=[],
        typ="int const",
    )
    assert t.name == "int"
    assert t.isPrimitive() == True
    assert t.isConst == True
    assert t.ptrCount == 0


@pytest.mark.test_release
def test_primitive_type_const_ptr(stable_test_dir: Path, stable_unique_test_name: str):
    t = get_type(
        stable_test_dir=stable_test_dir,
        stable_unique_test_name=stable_unique_test_name,
        preamble=[],
        typ="int const*",
    )
    assert t.name == "int"
    assert t.isPrimitive() == True
    assert t.isConst == True
    assert t.ptrCount == 1


@pytest.mark.test_release
def test_user_defined(stable_test_dir: Path, stable_unique_test_name: str):
    t = get_type(
        stable_test_dir=stable_test_dir,
        stable_unique_test_name=stable_unique_test_name,
        preamble=["struct UserDefined{};"],
        typ="UserDefined",
    )
    assert t.name == "UserDefined"
    assert t.isPrimitive() == False


@pytest.mark.test_release
def test_user_defined_template(stable_test_dir: Path, stable_unique_test_name: str):
    t = get_type(
        stable_test_dir=stable_test_dir,
        stable_unique_test_name=stable_unique_test_name,
        preamble=["template <typename T> struct Templ{};"],
        typ="Templ<int>",
    )
    assert t.name == "Templ"
    assert len(t.Parameters) == 1
    assert t.par0().name == "int"
    assert t.par0().isPrimitive() == True


@pytest.mark.test_release
def test_enum_class(stable_test_dir: Path, stable_unique_test_name: str):
    t = get_type(
        stable_test_dir=stable_test_dir,
        stable_unique_test_name=stable_unique_test_name,
        preamble=["enum class TestEnum {};"],
        typ="TestEnum",
    )

    assert t.name == "TestEnum"


@pytest.mark.test_release
def test_namespaced_user_defined(stable_test_dir: Path, stable_unique_test_name: str):
    t = get_type(
        stable_test_dir=stable_test_dir,
        stable_unique_test_name=stable_unique_test_name,
        preamble=["""
namespace ns {
    struct UserDefined {};
}
"""],
        typ="ns::UserDefined",
    )

    assert t.name == "UserDefined"
    assert t.isPrimitive() == False
    assert [s.name for s in t.Spaces] == ["ns"]
    assert [s.isNamespace for s in t.Spaces] == [True]


@pytest.mark.test_release
def test_nested_namespaces(stable_test_dir: Path, stable_unique_test_name: str):
    t = get_type(
        stable_test_dir=stable_test_dir,
        stable_unique_test_name=stable_unique_test_name,
        preamble=["""
namespace n1 {
namespace n2 {
    struct DeepType {};
}
}
"""],
        typ="n1::n2::DeepType",
    )

    assert t.name == "DeepType"
    assert [s.name for s in t.Spaces] == ["n1", "n2"]
    assert [s.isNamespace for s in t.Spaces] == [True, True]


@pytest.mark.test_release
def test_namespace_alias_is_expanded(stable_test_dir: Path, stable_unique_test_name: str):
    t = get_type(
        stable_test_dir=stable_test_dir,
        stable_unique_test_name=stable_unique_test_name,
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

    assert t.name == "AliasTarget"
    assert [s.name for s in t.Spaces] == ["real_ns"]
    assert [s.isNamespace for s in t.Spaces] == [True]


@pytest.mark.test_release
def test_nested_type_qualifier(stable_test_dir: Path, stable_unique_test_name: str):
    t = get_type(
        stable_test_dir=stable_test_dir,
        stable_unique_test_name=stable_unique_test_name,
        preamble=["""
struct Outer {
    struct Inner {};
};
"""],
        typ="Outer::Inner",
    )

    assert t.name == "Inner"
    assert [s.name for s in t.Spaces] == ["Outer"]
    assert [s.isNamespace for s in t.Spaces] == [False]


@pytest.mark.test_release
def test_namespaced_template(stable_test_dir: Path, stable_unique_test_name: str):
    t = get_type(
        stable_test_dir=stable_test_dir,
        stable_unique_test_name=stable_unique_test_name,
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

    assert t.name == "Box"
    assert [s.name for s in t.Spaces] == ["tpl_ns"]
    assert len(t.Parameters) == 1
    assert t.par0().name == "int"
    assert t.par0().isPrimitive() == True


@pytest.mark.test_release
def test_global_namespace_qualified(stable_test_dir: Path, stable_unique_test_name: str):
    t = get_type(
        stable_test_dir=stable_test_dir,
        stable_unique_test_name=stable_unique_test_name,
        preamble=["""
namespace top {
    struct GlobalRef {};
}
"""],
        typ="::top::GlobalRef",
    )

    assert t.name == "GlobalRef"
    assert [s.name for s in t.Spaces] == ["top"]


@pytest.mark.test_release
def test_fixed_size_array_type(stable_test_dir: Path, stable_unique_test_name: str):
    t = get_type(
        stable_test_dir=stable_test_dir,
        stable_unique_test_name=stable_unique_test_name,
        preamble=[],
        field_decl="[[refl]] int field[8];",
    )

    assert t.Kind == QualTypeKind.Array
    assert t.name == "ConstantArray"
    assert len(t.Parameters) == 2
    assert t.par0().name == "int"
    assert t.par0().Kind == QualTypeKind.RegularType
    assert t.par1().expr == "8"
    assert t.par1().Kind == QualTypeKind.TypeExpr


@pytest.mark.test_release
def test_multidim_array_type(stable_test_dir: Path, stable_unique_test_name: str):
    t = get_type(
        stable_test_dir=stable_test_dir,
        stable_unique_test_name=stable_unique_test_name,
        preamble=[],
        field_decl="[[refl]] float field[2][4];",
    )

    assert t.Kind == QualTypeKind.Array
    assert len(t.Parameters) == 2

    assert t.par1().expr == "2"
    inner = t.par0()
    assert inner.Kind == QualTypeKind.Array
    assert len(inner.Parameters) == 2
    assert inner.par0().name == "float"
    assert inner.par1().expr == "4"


@pytest.mark.test_release
def test_function_pointer_type(stable_test_dir: Path, stable_unique_test_name: str):
    t = get_type(
        stable_test_dir=stable_test_dir,
        stable_unique_test_name=stable_unique_test_name,
        preamble=[],
        field_decl="[[refl]] int (*field)(double, char const*);",
    )

    assert t.Kind == QualTypeKind.FunctionPtr
    assert len(t.Parameters) == 0
    assert t.func.ReturnTy.name == "int"
    assert len(t.func.Args) == 2
    assert t.func.Args[0].name == "double"
    assert t.func.Args[1].name == "char"
    assert t.func.Args[1].ptrCount == 1
    assert t.func.Args[1].isConst == True
