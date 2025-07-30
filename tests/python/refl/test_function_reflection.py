from py_scriptutils import configure_asan
from py_textlayout.py_textlayout_wrap import TextLayout, TextOptions

import os
from beartype.typing import TYPE_CHECKING
if os.getenv("HAXORG_REDUCED_RELEASE_TEST") and not TYPE_CHECKING:
    from py_scriptutils.test_utils import HasAnyAttr 
    refl_test_driver = HasAnyAttr()
else: 
    import refl_test_driver

import pytest
from py_codegen.gen_tu_cpp import ReferenceKind, GenTypeMap
import py_codegen.astbuilder_pybind11 as py11
import py_codegen.astbuilder_py as py
import py_codegen.astbuilder_cpp as cpp


@pytest.mark.test_release
def test_function_extract_0_args():
    func = refl_test_driver.get_function("int get_something();")
    assert func.name == "get_something"
    assert len(func.arguments) == 0
    assert func.result.name == "int"


@pytest.mark.test_release
def test_function_extract_args():
    func = refl_test_driver.get_function("int do_something(int first, char second);")
    assert func.name == "do_something"
    assert len(func.arguments) == 2
    assert func.result.name == "int"
    assert func.arguments[0].type.name == "int"
    assert func.arguments[1].type.name == "char"
    assert func.arguments[0].name == "first"
    assert func.arguments[1].name == "second"


@pytest.mark.test_release
def test_function_const_ref():
    func = refl_test_driver.get_function("void enable_file_trace(int const&);")
    assert func.name == "enable_file_trace"
    t = func.arguments[0].type
    assert t.name == "int"
    assert t.isConst
    assert t.RefKind == ReferenceKind.LValue

@pytest.mark.test_release
def test_method_const_ref():
    struct = refl_test_driver.get_struct("struct S { void enable_file_trace(int const&); };")
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
    assert "static_cast<void(S::*)(int const&)>(&S::enable_file_trace)" in lyt.toString(bind, TextOptions())

