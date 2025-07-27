import pytest
import os
if not os.getenv("HAXORG_REDUCED_RELEASE_TEST"):
    from refl_test_driver import run_provider, STABLE_FILE_NAME, get_nim_code, format_nim_code

from py_scriptutils import configure_asan
from pprint import pprint
from more_itertools import first_true
import py_codegen.wrapper_gen_nim as gen_nim
from pathlib import Path

INPUT = Path(__file__).parent.joinpath("test_coverall_input.cpp")


@pytest.mark.test_release
def test_coverall_extract():
    value = run_provider({str(INPUT): INPUT.read_text()}, code_dir=INPUT.parent)
    formatted = format_nim_code(value)
    assert len(formatted) == 1


@pytest.mark.test_release
def test_coverall_nim():
    value = run_provider({
        str(INPUT): INPUT.read_text()
    }, code_dir=INPUT.parent).wraps[0].tu
    for _enum in value.enums:
        get_nim_code(_enum)

    for _function in value.functions:
        get_nim_code(_function)

    for _record in value.structs:
        get_nim_code(_record)

    for _typedef in value.typedefs:
        get_nim_code(_typedef)
