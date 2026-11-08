#!/usr/bin/env python

import os

from ex_py_need_nanobind import verify


def main() -> None:
    verify(int(os.environ["EX_EXPECTED_VERSION"]))


if __name__ == "__main__":
    main()
