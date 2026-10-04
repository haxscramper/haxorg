import os

from ex_py_final_downstream import verify


def test_transitive_dependencies() -> None:
    report = verify(int(os.environ["EX_EXPECTED_VERSION"]))

    assert set(report["packages"]) == {
        "ex_py_final_downstream",
        "ex_py_standalone",
        "ex_py_need_binary",
        "ex_py_need_nanobind",
    }
    assert "executable_file" in report
    assert "nanobind_file" in report
    assert "binary_protobuf_file" in report
    assert "nanobind_protobuf_file" in report
