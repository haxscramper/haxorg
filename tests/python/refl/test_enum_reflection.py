from refl_test_driver import run_provider, STABLE_FILE_NAME, GenTuStruct, get_enum, get_function, get_struct
import pytest

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
