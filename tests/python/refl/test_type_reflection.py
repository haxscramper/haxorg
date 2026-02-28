from pathlib import Path

import py_codegen.astbuilder_cpp as cpp
import py_codegen.astbuilder_nanobind as py11
from py_codegen.codegen_ir import get_base_map, ReferenceKind
from py_haxorg.layout.wrap import TextLayout, TextOptions
import pytest


@pytest.mark.test_release
def test_primitive_type(stable_test_dir: Path):
    import tests.python.refl.refl_test_driver as refl_test_driver
    t = refl_test_driver.get_type([], "int", stable_test_dir)
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
