from pathlib import Path

import pytest
import refl_test_driver
from beartype import beartype

INPUT = (Path(__file__).parent / "assets" / "coverall_input.cpp").resolve()


@pytest.mark.test_release
@beartype
def test_coverall_extract(stable_test_dir: Path) -> None:
    result = refl_test_driver.run_reflection_tool_provider(
        {str(INPUT): INPUT.read_text(encoding="utf-8")},
        code_dir=INPUT.parent,
        output_dir=stable_test_dir,
    )

    assert len(result.tus) == 1
    tu = result.tus[0]
    assert Path(tu.absolute_path) == INPUT
    assert Path(tu.main_file_include_tree.absolute_path) == INPUT
