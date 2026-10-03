from pathlib import Path

import pytest
import refl_test_driver

import haxdex_read_code_cpp.proto as pb


@pytest.mark.test_release
def test_function_extract_0_args(stable_test_dir: Path) -> None:
    func = refl_test_driver.get_function(
        "int get_something();",
        stable_test_dir=stable_test_dir,
    )

    assert func.name == "get_something"
    assert len(func.arguments) == 0
    assert func.result_ty.name == "int"


@pytest.mark.test_release
def test_function_extract_args(stable_test_dir: Path) -> None:
    func = refl_test_driver.get_function(
        "int do_something(int first, char second);",
        stable_test_dir=stable_test_dir,
    )

    assert func.name == "do_something"
    assert len(func.arguments) == 2
    assert func.result_ty.name == "int"
    assert func.arguments[0].type.name == "int"
    assert func.arguments[1].type.name == "char"
    assert func.arguments[0].name == "first"
    assert func.arguments[1].name == "second"


@pytest.mark.test_release
def test_function_const_ref(stable_test_dir: Path) -> None:
    func = refl_test_driver.get_function(
        "void enable_file_trace(int const&);",
        stable_test_dir=stable_test_dir,
    )

    assert func.name == "enable_file_trace"

    typ = func.arguments[0].type
    assert typ.name == "int"
    assert any(qualifier.is_const for qualifier in typ.qualifiers)
    assert typ.ref_kind == pb.ReferenceKind.L_VALUE


@pytest.mark.test_release
def test_method_const_ref(stable_test_dir: Path) -> None:
    record = refl_test_driver.get_struct(
        "struct S { void enable_file_trace(int const&); };",
        stable_test_dir=stable_test_dir,
    )

    assert len(record.methods) == 1

    method = record.methods[0]
    assert method.name == "enable_file_trace"

    typ = method.args[0].type
    assert typ.name == "int"
    assert any(qualifier.is_const for qualifier in typ.qualifiers)
    assert typ.ref_kind == pb.ReferenceKind.L_VALUE
