#!/usr/bin/env python

import importlib
import json
import os


def main() -> None:
    package = importlib.import_module(os.environ["EX_PROBE_PACKAGE"])
    report = package.verify(int(os.environ["EX_EXPECTED_VERSION"]))
    print("EX_PROBE=" + json.dumps(report, sort_keys=True))


if __name__ == "__main__":
    main()
