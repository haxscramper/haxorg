import pytest


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
