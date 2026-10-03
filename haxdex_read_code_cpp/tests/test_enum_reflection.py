from pathlib import Path

import pytest
import refl_test_driver
from beartype import beartype


@pytest.mark.test_release
@beartype
def test_enum_field_extract(logged_test_dir: Path) -> None:
    enum = refl_test_driver.get_enum(
        "enum CEnum { Member1, Member2 };",
        stable_test_dir=logged_test_dir,
    )

    assert enum.name.name == "CEnum"
    assert len(enum.fields) == 2
    assert enum.fields[0].name == "Member1"
    assert enum.fields[1].name == "Member2"
    assert enum.fields[0].value == 0
    assert enum.fields[1].value == 1


@pytest.mark.test_release
@beartype
def test_namespaced_enum_extract(logged_test_dir: Path) -> None:
    enum = refl_test_driver.get_enum(
        "namespace Space { enum Enum { member1 }; }",
        stable_test_dir=logged_test_dir,
    )

    assert enum.name.name == "Enum"
    assert len(enum.name.spaces) == 1
    assert enum.name.spaces[0].name == "Space"
