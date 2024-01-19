from refl_test_driver import (
    run_provider,
    STABLE_FILE_NAME,
    GenTuStruct,
    get_enum,
    get_function,
    get_struct,
)
import pytest
from py_codegen.gen_tu_cpp import ReferenceKind


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


def test_function_const_ref():
    func = get_function("void enable_file_trace(int const&);")
    assert func.name == "enable_file_trace"
    t = func.arguments[0].type
    assert t.name == "int"
    assert t.isConst
    assert t.RefKind == ReferenceKind.LValue
