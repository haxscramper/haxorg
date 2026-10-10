#!/usr/bin/env python

import argparse
import json
import logging
import os
import re
import shutil
import subprocess
import sys
import tempfile
from contextlib import ExitStack
from pathlib import Path

import tomllib

logging.basicConfig(
    level=logging.DEBUG,
    format="%(levelname)s %(filename)s:%(lineno)d: %(message)s",
)

CONAN_PROJECTS = {
    "haxorg_py_lib": "haxorg_cpp_py_wrap",
    "hstd_py_text_layout": "hstd_cpp_text_layout_py_wrap",
}

TEST_UV_INSTALL_FLAGS = json.loads(os.getenv("HSTD_PY_TEST_UV_INSTALL_UV_FLAGS", "[]"))


def run(
    command: list[str],
    *,
    cwd: Path,
    env: dict[str, str] | None = None,
) -> None:
    logging.info("==> {}".format(" ".join(command)))
    subprocess.run(
        command,
        cwd=cwd,
        env=env,
        check=True,
    )


def find_workspace_root(project_path: Path) -> Path:
    for candidate in [project_path, *project_path.parents]:
        pyproject = candidate / "pyproject.toml"
        if not pyproject.is_file():
            continue

        with pyproject.open("rb") as file:
            data = tomllib.load(file)

        if "workspace" in data.get("tool", {}).get("uv", {}):
            return candidate

    raise RuntimeError(f"Could not find a UV workspace containing {project_path}")


def get_project_name(project_path: Path) -> str:
    with (project_path / "pyproject.toml").open("rb") as file:
        data = tomllib.load(file)

    return data["project"]["name"]


def validate_structure(project_path: Path) -> None:
    package_name = project_path.name
    expected = [
        project_path / "pyproject.toml",
        project_path / "src" / package_name,
        project_path / "tests",
        project_path / "test_package",
        project_path / "test_package" / "pyproject.toml",
        project_path / "test_package" / "main.py",
    ]

    missing = [path for path in expected if not path.exists()]
    if missing:
        formatted = "\n".join(f"  {path}" for path in missing)
        raise RuntimeError(
            f"{package_name}: invalid package structure; missing:\n{formatted}"
        )


def sync_environment(
    workspace_root: Path,
    project_name: str,
    *,
    editable: bool,
    env: dict[str, str],
) -> None:
    command = [
        "uv",
        *TEST_UV_INSTALL_FLAGS,
        "sync",
        "--project",
        str(workspace_root),
        "--package",
        project_name,
        "--group",
        "dev",
    ]

    if not editable:
        command.append("--no-editable")

    # Reinstall workspace packages without discarding cached third-party dependencies.
    with (workspace_root / "pyproject.toml").open("rb") as file:
        workspace_config = tomllib.load(file)

    for member in workspace_config["tool"]["uv"]["workspace"]["members"]:
        package_name = re.sub(
            r"[-_.]+",
            "-",
            get_project_name(workspace_root / member),
        ).lower()
        command.extend(["--reinstall-package", package_name])

    run(command, cwd=workspace_root, env=env)


def run_package_tests(
    project_path: Path,
    workspace_root: Path,
    project_name: str,
    *,
    env: dict[str, str],
) -> None:
    command = [
        "pytest",
        *json.loads(env.get("HSTD_PY_PYTEST_EXTRA_ARGS", "[]")),
        str(project_path / "tests"),
    ]

    if env.get("HSTD_PY_PYTEST_USE_LLDB") == "1":
        lldb_command = ["lldb", "--batch"]
        lldb_script = env.get("HSTD_PY_PYTEST_LLDB_SCRIPT")

        if lldb_script:
            lldb_command.extend(["--source", lldb_script])
        else:
            lldb_command.extend(
                [
                    "-o",
                    "run",
                    "-k",
                    "thread backtrace all",
                ]
            )

        command = [
            *lldb_command,
            "--",
            "python",
            "-m",
            *command,
        ]

    run(
        [
            "uv",
            *TEST_UV_INSTALL_FLAGS,
            "run",
            "--project",
            str(workspace_root),
            "--package",
            project_name,
            "--no-sync",
            *command,
        ],
        cwd=workspace_root,
        env=env,
    )


def install_test_package(
    test_package: Path,
    workspace_root: Path,
    environment_path: Path,
    *,
    env: dict[str, str],
) -> None:
    run(
        [
            "uv",
            *TEST_UV_INSTALL_FLAGS,
            "pip",
            "install",
            # Preserve already-synced dependencies. Additional test-package
            # dependencies must be included in the selected package's dev group.
            "--no-deps",
            "--python",
            str(environment_path / "bin" / "python"),
            str(test_package),
        ],
        cwd=workspace_root,
        env=env,
    )


def run_test_package(
    test_package: Path,
    workspace_root: Path,
    project_name: str,
    *,
    env: dict[str, str],
) -> None:
    run(
        [
            "uv",
            *TEST_UV_INSTALL_FLAGS,
            "run",
            "--project",
            str(workspace_root),
            "--package",
            project_name,
            "--no-sync",
            "python",
            str(test_package / "main.py"),
        ],
        cwd=test_package,
        env=env,
    )


def validate_package(
    project_path: Path,
    *,
    editable: bool,
    conan_profile: Path | None,
) -> None:
    project_path = project_path.resolve()
    workspace_root = find_workspace_root(project_path)
    project_name = get_project_name(project_path)
    test_package = project_path / "test_package"

    validate_structure(project_path)

    with ExitStack() as stack:
        override = os.environ.get("HAXORG_PY_TEST_UV_INSTALL_DIR_OVERRIDE")

        if override is not None:
            if not override:
                raise ValueError("HAXORG_PY_TEST_UV_INSTALL_DIR_OVERRIDE cannot be empty")

            environment_path = Path(override)
            if environment_path.exists():
                shutil.rmtree(environment_path)

            environment_path.mkdir(parents=True)
        else:
            temporary = stack.enter_context(
                tempfile.TemporaryDirectory(prefix="verify_pkg_")
            )
            environment_path = Path(temporary) / ".venv"

        env = os.environ.copy()
        env["UV_PROJECT_ENVIRONMENT"] = str(environment_path)

        if conan_profile is not None:
            env["CONAN_PROFILE"] = str(conan_profile)

        sync_environment(workspace_root, project_name, editable=editable, env=env)
        run_package_tests(project_path, workspace_root, project_name, env=env)
        install_test_package(test_package, workspace_root, environment_path, env=env)
        run_test_package(test_package, workspace_root, project_name, env=env)


def main() -> None:
    parser = argparse.ArgumentParser(
        description=(
            "Validate structure, tests, installation, and the test package "
            "for a UV workspace package"
        )
    )
    parser.add_argument(
        "project_path",
        type=Path,
    )
    parser.add_argument(
        "--editable",
        action="store_true",
        help=(
            "Install the workspace package in editable mode. Conan-backed "
            "packages are recreated from their current C++ sources first."
        ),
    )
    parser.add_argument(
        "--conan-profile",
        type=Path,
    )

    arguments = parser.parse_args()

    try:
        validate_package(
            arguments.project_path,
            editable=arguments.editable,
            conan_profile=(
                arguments.conan_profile.resolve() if arguments.conan_profile else None
            ),
        )
    except (RuntimeError, subprocess.CalledProcessError) as error:
        logging.error(f"{error}")
        sys.exit(1)

    logging.info("package validation OK, no errors")


if __name__ == "__main__":
    main()
