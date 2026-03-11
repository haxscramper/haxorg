from pathlib import Path

import py_codegen.astbuilder_cpp as cpp
import py_codegen.astbuilder_nanobind as py11
from py_codegen.astbuilder_nanobind_config import NanobindAstbuilderConfig
from py_codegen.codegen_ir import get_type_map, ReferenceKind
from py_haxorg.layout.wrap import TextLayout, TextOptions
import pytest


@pytest.mark.test_release
def test_function_extract_0_args(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    func = refl_test_driver.get_function(
        "int get_something();",
        stable_test_dir=stable_test_dir,
    )
    assert func.Name == "get_something"
    assert len(func.Args) == 0
    assert func.ReturnType.Name == "int"


@pytest.mark.test_release
def test_function_extract_args(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    func = refl_test_driver.get_function(
        "int do_something(int first, char second);",
        stable_test_dir=stable_test_dir,
    )
    assert func.Name == "do_something"
    assert len(func.Args) == 2
    assert func.ReturnType.Name == "int"
    assert func.Args[0].Type.Name == "int"
    assert func.Args[1].Type.Name == "char"
    assert func.Args[0].Name == "first"
    assert func.Args[1].Name == "second"


@pytest.mark.test_release
def test_function_const_ref(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    func = refl_test_driver.get_function(
        "void enable_file_trace(int const&);",
        stable_test_dir=stable_test_dir,
    )

    assert func.Name == "enable_file_trace"
    t = func.Args[0].Type
    assert t.Name == "int"
    assert t.IsConst
    assert t.RefKind == ReferenceKind.LValue


@pytest.mark.test_release
def test_method_const_ref(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    struct = refl_test_driver.get_struct(
        "struct S { void enable_file_trace(int const&); };",
        stable_test_dir=stable_test_dir,
    )

    assert len(struct.Methods) == 1
    func = struct.Methods[0]
    assert func.Name == "enable_file_trace"
    t = func.Args[0].Type
    assert t.Name == "int"
    assert t.IsConst
    assert t.RefKind == ReferenceKind.LValue

    ast = cpp.ASTBuilder(in_b=TextLayout())
    conf = NanobindAstbuilderConfig(get_type_map([]))
    wrap: py11.NbClass = py11.NbClass(ast, struct, conf)
    wrap.InitDefault(ast, wrap.Fields)
    lyt = TextLayout()
    builder = cpp.ASTBuilder(lyt)
    bind = wrap.Methods[0].build_bind(struct.Name, builder)
    assert "static_cast<void(S::*)(int const&)>(&S::enable_file_trace)" in lyt.toString(
        bind, TextOptions())
