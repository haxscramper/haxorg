#!/usr/bin/env python

import importlib
import os
import sys
from pathlib import Path


def main() -> None:
    directory = Path(sys.argv[1]).resolve()
    sys.path.insert(0, str(directory))

    module = importlib.import_module("ex_cpp_nanobind")
    expected = int(os.environ["EX_EXPECTED_VERSION"])

    assert Path(module.__file__).resolve().parent == directory
    assert module.value() == expected

    print(f"EX_CONAN_TEST_PACKAGE:ex_cpp_nanobind:{expected}")


if __name__ == "__main__":
    main()
