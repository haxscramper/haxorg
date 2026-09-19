#!/usr/bin/env python
"""
Verify a Python package can be independently installed and used as a dependency.

Usage:
    verify_package.py <project_path> [--test-package <test_path>] [--config-setting KEY=VALUE]...

Examples:
    # Basic verification with test package in <project>/test_package/
    ./verify_package.py ./my-project

    # Custom test package location
    ./verify_package.py ./my-project --test-package ./my-project/tests/integration

    # With build config settings
    ./verify_package.py ./my-project --config-setting cmake.define.MY_OPT=ON --config-setting cmake.build-type=Release
"""

import argparse
import logging
from pathlib import Path
import subprocess
import sys
import tempfile

logging.basicConfig(
    level=logging.DEBUG,
    format="%(levelname)s %(filename)s:%(lineno)d: %(message)s",
)


def main():
    parser = argparse.ArgumentParser(
        description="Verify a Python package can be installed and used independently")
    parser.add_argument(
        "project_path",
        type=Path,
        help="Path to the Python project to verify",
    )
    parser.add_argument(
        "--test-package",
        type=Path,
        default=None,
        help="Path to the test package (default: <project_path>/test_package/)",
    )
    parser.add_argument(
        "--config-setting",
        "-C",
        action="append",
        default=[],
        dest="config_settings",
        help="Build config settings passed to uv pip install (e.g. cmake.define.FOO=BAR)",
    )

    args = parser.parse_args()

    project_path = args.project_path.resolve()
    if not project_path.is_dir():
        logging.error(
            f"project path does not exist: {project_path} or is not a directory")
        sys.exit(1)

    test_package = (args.test_package.resolve() if args.test_package else project_path /
                    "test_package")

    if not test_package.is_dir():
        logging.error(
            f"test package path does not exist: {test_package} or is not a directory")
        sys.exit(1)

    test_script = test_package / "test.py"
    if not test_script.is_file():
        logging.error(f"test script not found: {test_script} or is not a file")
        sys.exit(1)

    with tempfile.TemporaryDirectory(prefix="verify_pkg_") as tmpdir:
        venv_path = Path(tmpdir) / ".venv"

        logging.info(f"==> Creating virtual environment in {venv_path}")
        subprocess.run(
            ["uv", "venv", str(venv_path)],
            check=True,
        )

        # Build the install command
        install_cmd = [
            "uv",
            "pip",
            "install",
            "--python",
            str(venv_path / "bin" / "python"),
            str(project_path),
        ]
        for setting in args.config_settings:
            install_cmd.extend(["--config-setting", setting])

        logging.info(f"==> Installing package from {project_path}")
        subprocess.run(install_cmd, check=True)

        # Install test package dependencies if it has a pyproject.toml or requirements.txt
        test_pyproject = test_package / "pyproject.toml"
        test_requirements = test_package / "requirements.txt"
        if test_pyproject.is_file():
            logging.info(f"==> Installing test package from {test_package}")
            subprocess.run(
                [
                    "uv",
                    "pip",
                    "install",
                    "--python",
                    str(venv_path / "bin" / "python"),
                    str(test_package),
                ],
                check=True,
            )
        elif test_requirements.is_file():
            logging.info(f"==> Installing test requirements from {test_requirements}")
            subprocess.run(
                [
                    "uv",
                    "pip",
                    "install",
                    "--python",
                    str(venv_path / "bin" / "python"),
                    "-r",
                    str(test_requirements),
                ],
                check=True,
            )

        python_bin = venv_path / "bin" / "python"

        logging.info(f"==> Running test script: {test_script}")
        result = subprocess.run(
            [str(python_bin), str(test_script)],
            cwd=test_package,
        )

        if result.returncode != 0:
            logging.error(
                f"\n==> FAILED: test script exited with code {result.returncode}")
            sys.exit(result.returncode)

        logging.info("\n==> SUCCESS: package installed and test passed")


if __name__ == "__main__":
    main()
