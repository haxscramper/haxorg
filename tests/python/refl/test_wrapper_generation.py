import pytest

from tests.python.conftest import stable_test_dir
from py_codegen import astbuilder_nim, astbuilder_embind, astbuilder_py, astbuilder_nanobind


@pytest.mark.test_release
def test_structure_wrapping(stable_test_dir):
    from tests.python.refl import refl_test_driver

    wraps = refl_test_driver.get_all_code(
        {"header.hpp": "struct [[refl]] Defined {};"},
        stable_test_dir=stable_test_dir,
    )

    struct_nim = wraps.getNimEntries("Defined")[0]

    assert struct_nim
    assert struct_nim.Name == "Defined"

    struct_py = wraps.getPythonEntries("Defined")[0]

    assert struct_py
    assert struct_py.getPyName() == "Defined"

    struct_em = wraps.getWasmEntries("Defined")[0]

    assert struct_em
    assert struct_em.getWasmName() == "Defined"


@pytest.mark.test_release
def test_function_wrapping(stable_test_dir):
    from tests.python.refl import refl_test_driver
    wraps = refl_test_driver.get_all_code("[[refl]] int defined();",
                                          stable_test_dir=stable_test_dir)

    fun_nim = wraps.getNimEntries("defined")[0]

    assert fun_nim
    assert fun_nim.Name == "defined"

    fun_py: astbuilder_nanobind.NbFunction = wraps.getPythonEntries("defined")[0]

    assert fun_py
    assert fun_py.PyName == "defined"
