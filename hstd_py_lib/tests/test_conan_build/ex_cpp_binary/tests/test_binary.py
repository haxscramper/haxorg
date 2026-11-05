import os
import shutil
import subprocess

from ex_py_standalone import value


def test_binary() -> None:
    expected = int(os.environ["EX_EXPECTED_VERSION"])
    assert value() == expected

    executable = shutil.which("ex_cpp_binary")
    assert executable is not None

    result = subprocess.run(
        [executable],
        check=True,
        stdout=subprocess.PIPE,
        text=True,
    )
    actual = int(result.stdout.strip())
    assert actual == expected

    print(f"EX_NATIVE_PYTEST:ex_cpp_binary:{expected}")
