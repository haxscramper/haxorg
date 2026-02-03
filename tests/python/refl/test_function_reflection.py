from pathlib import Path

import py_codegen.astbuilder_cpp as cpp
import py_codegen.astbuilder_pybind11 as py11
from py_codegen.gen_tu_cpp import ReferenceKind
from py_textlayout.py_textlayout_wrap import TextLayout
from py_textlayout.py_textlayout_wrap import TextOptions
import pytest


@pytest.mark.test_release
def test_function_extract_0_args(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    func = refl_test_driver.get_function(
        "int get_something();",
        stable_test_dir=stable_test_dir,
    )
    assert func.name == "get_something"
    assert len(func.arguments) == 0
    assert func.result.name == "int"


@pytest.mark.test_release
def test_function_extract_args(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    func = refl_test_driver.get_function(
        "int do_something(int first, char second);",
        stable_test_dir=stable_test_dir,
    )
    assert func.name == "do_something"
    assert len(func.arguments) == 2
    assert func.result.name == "int"
    assert func.arguments[0].type.name == "int"
    assert func.arguments[1].type.name == "char"
    assert func.arguments[0].name == "first"
    assert func.arguments[1].name == "second"


@pytest.mark.test_release
def test_function_const_ref(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    func = refl_test_driver.get_function(
        "void enable_file_trace(int const&);",
        stable_test_dir=stable_test_dir,
    )

    assert func.name == "enable_file_trace"
    t = func.arguments[0].type
    assert t.name == "int"
    assert t.isConst
    assert t.RefKind == ReferenceKind.LValue


@pytest.mark.test_release
def test_method_const_ref(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    struct = refl_test_driver.get_struct(
        "struct S { void enable_file_trace(int const&); };",
        stable_test_dir=stable_test_dir,
    )

    assert len(struct.methods) == 1
    func = struct.methods[0]
    assert func.name == "enable_file_trace"
    t = func.arguments[0].type
    assert t.name == "int"
    assert t.isConst
    assert t.RefKind == ReferenceKind.LValue

    ast = cpp.ASTBuilder(in_b=TextLayout())
    wrap: py11.Py11Class = py11.Py11Class(ast, struct)
    wrap.InitDefault(ast, wrap.Fields)
    lyt = TextLayout()
    builder = cpp.ASTBuilder(lyt)
    bind = wrap.Methods[0].build_bind(struct.name, builder)
    assert "static_cast<void(S::*)(int const&)>(&S::enable_file_trace)" in lyt.toString(
        bind, TextOptions())
