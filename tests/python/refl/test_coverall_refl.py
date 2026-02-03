from pathlib import Path

import pytest

INPUT = Path(__file__).parent.joinpath("test_coverall_input.cpp")


@pytest.mark.test_release
def test_coverall_extract(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    value = refl_test_driver.run_provider(
        {str(INPUT): INPUT.read_text()},
        code_dir=INPUT.parent,
        output_dir=stable_test_dir,
    )

    formatted = refl_test_driver.format_nim_code(value)
    assert len(formatted) == 1


@pytest.mark.test_release
def test_coverall_nim(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    value = refl_test_driver.run_provider(
        {
            str(INPUT): INPUT.read_text()
        },
        code_dir=INPUT.parent,
        output_dir=stable_test_dir,
    ).wraps[0].tu

    for _enum in value.enums:
        refl_test_driver.get_nim_code(_enum)

    for _function in value.functions:
        refl_test_driver.get_nim_code(_function)

    for _record in value.structs:
        refl_test_driver.get_nim_code(_record)

    for _typedef in value.typedefs:
        refl_test_driver.get_nim_code(_typedef)
