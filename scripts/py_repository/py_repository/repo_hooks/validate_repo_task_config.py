#!/usr/bin/env python

from pathlib import Path
import sys

import commentjson


def check_json_file(filepath: Path) -> list[str]:
    errors = []

    with open(filepath) as f:
        data = commentjson.load(f)

    # Check use_dependencies
    if "use_dependencies" in data and data["use_dependencies"] is not True:
        errors.append(f"{filepath}: 'use_dependencies' must be true or not set")

    # Check py_test_conf.extra_pytest_args
    if "py_test_conf" in data and "extra_pytest_args" in data["py_test_conf"]:
        args = data["py_test_conf"]["extra_pytest_args"]
        if args:
            for arg in args:
                if not arg.startswith("-"):
                    errors.append(
                        f"{filepath}: 'py_test_conf.extra_pytest_args' contains non-flag argument: {arg}"
                    )

    return errors


def main() -> int:
    all_errors = []

    for filepath in sys.argv[1:]:
        all_errors.extend(check_json_file(Path(filepath)))

    for error in all_errors:
        print(error)

    return 1 if all_errors else 0


if __name__ == "__main__":
    sys.exit(main())
