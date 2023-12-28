from refl_test_driver import run_provider, STABLE_FILE_NAME, get_enum, get_nim_code
import pytest
from pprint import pprint
from more_itertools import first_true
import py_codegen.wrapper_gen_nim as gen_nim


def test_enum_field_extract():
    enum = get_enum("enum CEnum { Member1, Member2 };")
    assert enum.name.name == "CEnum"
    assert len(enum.fields) == 2
    assert enum.fields[0].name == "Member1"
    assert enum.fields[1].name == "Member2"


def test_namespaced_enum_extract():
    enum = get_enum("namespace Space { enum Enum { member1 }; }")
    assert enum.name.name == "Enum"
    assert len(enum.name.Spaces) == 1
    assert enum.name.Spaces[0].name == "Space"


def test_nim_enum_conversion():
    con = get_nim_code(get_enum("enum En { Field1, Field2 };"))
    with open("/tmp/a.py", "w") as file:
        pprint(con, stream=file)

    raw_wrap = first_true(con.types, default=None, pred=lambda it: it.Name == "c_En")
    assert raw_wrap
    assert len(raw_wrap.Fields) == 2
    assert raw_wrap.Fields[0].Name == "c_Field1"
    assert raw_wrap.Fields[1].Name == "c_Field2"

    nim_wrap = first_true(con.types, default=None, pred=lambda it: it.Name == "En")
    assert nim_wrap
    assert len(nim_wrap.Fields) == 2
    assert nim_wrap.Fields[0].Name == "Field1"
    assert nim_wrap.Fields[1].Name == "Field2"

    # Convert set of nim enums to C-style set with bitor components
    nim_set_to_cint = first_true(
        con.procs,
        default=None,
        pred=lambda it: it.Name == "toCInt" and it.Arguments[0].Type.Name == "set")

    assert nim_set_to_cint
    assert len(nim_set_to_cint.Arguments) == 1
    assert nim_set_to_cint.ReturnTy.Name == "cint"
    assert nim_set_to_cint.Arguments[0].Type.Parameters[0].Name == "En"
    assert nim_set_to_cint.Kind == gen_nim.nim.FunctionKind.CONVERTER

    # Convert C enum to cint value
    c_en_to_cint = first_true(
        con.procs,
        default=None,
        pred=lambda it: it.Name == "toCInt" and it.Arguments[0].Type.Name == "c_En")

    assert c_en_to_cint
    assert len(c_en_to_cint.Arguments) == 1
    assert c_en_to_cint.ReturnTy.Name == "cint"
    assert nim_set_to_cint.Kind == gen_nim.nim.FunctionKind.CONVERTER

    # Convert nim enum to cint value
    en_to_cint = first_true(
        con.procs,
        default=None,
        pred=lambda it: it.Name == "toCInt" and it.Arguments[0].Type.Name == "En")

    assert en_to_cint
    assert len(en_to_cint.Arguments) == 1
    assert en_to_cint.ReturnTy.Name == "cint"
    assert nim_set_to_cint.Kind == gen_nim.nim.FunctionKind.CONVERTER


    nim_to_c = first_true(con.procs, default=None, pred=lambda it: it.Name == "to_c_En")
    assert nim_to_c
    assert len(nim_to_c.Arguments) == 1
    assert nim_to_c.Arguments[0].Type.Name == "En"
    assert nim_to_c.ReturnTy.Name == "c_En"

    c_to_nim = first_true(con.procs, default=None, pred=lambda it: it.Name == "to_En")
    assert c_to_nim
    assert len(c_to_nim.Arguments) == 1
    assert c_to_nim.Arguments[0].Type.Name == "c_En"
    assert c_to_nim.ReturnTy.Name == "En"
