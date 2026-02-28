from pathlib import Path

import py_codegen.astbuilder_cpp as cpp
from beartype.typing import List
import pytest

from py_scriptutils.repo_files import get_haxorg_repo_root_path
from tests.python.conf_test_common import WithBinaryCoverageTest


def get_type(stable_test_dir: Path, stable_unique_test_name: str, preamble: List[str],
             typ: str) -> cpp.QualType:
    "Utility function to get reflection type value"
    import tests.python.refl.refl_test_driver as refl_test_driver
    with WithBinaryCoverageTest(
            test_binary=f"{get_haxorg_repo_root_path()}/build/haxorg/reflection_tool",
            uniq_name=stable_unique_test_name,
            coverage_out_dir=stable_test_dir) as profraw_path:
        t = refl_test_driver.get_type(
            preamble,
            typ,
            stable_test_dir,
            reflection_tool_profraw_path=profraw_path,
        )
    return t


@pytest.mark.test_release
def test_primitive_type(stable_test_dir: Path, stable_unique_test_name: str):
    t = get_type(
        stable_test_dir,
        stable_unique_test_name,
        [],
        "int",
    )
    assert t.name == "int"
    assert t.isPrimitive() == True


@pytest.mark.test_release
def test_primitive_type_const(stable_test_dir: Path):
    import tests.python.refl.refl_test_driver as refl_test_driver
    t = refl_test_driver.get_type([], "int const", stable_test_dir)
    assert t.name == "int"
    assert t.isPrimitive() == True
    assert t.isConst == True
    assert t.ptrCount == 0


@pytest.mark.test_release
def test_primitive_type_const_ptr(stable_test_dir: Path):
    import tests.python.refl.refl_test_driver as refl_test_driver
    t = refl_test_driver.get_type([], "int const*", stable_test_dir)
    assert t.name == "int"
    assert t.isPrimitive() == True
    assert t.isConst == True
    assert t.ptrCount == 1


@pytest.mark.test_release
def test_user_defined(stable_test_dir: Path):
    import tests.python.refl.refl_test_driver as refl_test_driver
    t = refl_test_driver.get_type(["struct UserDefined{};"], "UserDefined",
                                  stable_test_dir)
    assert t.name == "UserDefined"
    assert t.isPrimitive() == False


@pytest.mark.test_release
def test_user_defined_template(stable_test_dir: Path):
    import tests.python.refl.refl_test_driver as refl_test_driver
    t = refl_test_driver.get_type(["template <typename T> struct Templ{};"], "Templ<int>",
                                  stable_test_dir)
    assert t.name == "Templ"
    assert len(t.Parameters) == 1
    assert t.par0().name == "int"
    assert t.par0().isPrimitive() == True
