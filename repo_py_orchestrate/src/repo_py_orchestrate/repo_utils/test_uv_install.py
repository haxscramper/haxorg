#!/usr/bin/env python

import argparse
import json
import logging
import os
import re
import selectors
import shlex
import shutil
import subprocess
import sys
import tempfile
from contextlib import ExitStack
from pathlib import Path
from tempfile import TemporaryDirectory

import tomllib
from hstd_py_lib.debug_utils import bootstrap, config

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
    stage_name: str,
    env: dict[str, str] | None = None,
    output_dir: Path | None = None,
) -> None:
    logging.info("==> {}".format(" ".join(command)))

    if output_dir is None:
        subprocess.run(
            command,
            cwd=cwd,
            env=env,
            check=True,
        )
        return

    log_path = output_dir / f"{Path(command[0]).name}_{stage_name}.log"

    with (
        log_path.open("wb") as log_file,
        subprocess.Popen(
            command,
            cwd=cwd,
            env=env,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        ) as process,
    ):
        assert process.stdout is not None
        assert process.stderr is not None

        with selectors.DefaultSelector() as selector:
            selector.register(
                process.stdout,
                selectors.EVENT_READ,
                sys.stdout.buffer,
            )
            selector.register(
                process.stderr,
                selectors.EVENT_READ,
                sys.stderr.buffer,
            )

            while selector.get_map():
                for key, _ in selector.select():
                    chunk = os.read(key.fd, 65536)

                    if not chunk:
                        selector.unregister(key.fileobj)
                        continue

                    log_file.write(chunk)
                    log_file.flush()
                    key.data.write(chunk)
                    key.data.flush()

        returncode = process.wait()

    if returncode != 0:
        raise subprocess.CalledProcessError(returncode, command)


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
    output_dir: Path | None = None,
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

    run(
        command,
        cwd=workspace_root,
        stage_name="sync_environment",
        env=env,
        output_dir=output_dir,
    )


def run_package_tests(
    project_path: Path,
    workspace_root: Path,
    project_name: str,
    *,
    env: dict[str, str],
    output_dir: Path | None = None,
) -> None:
    command = [
        "python",
        "-m",
        "pytest",
        *json.loads(env.get("HSTD_PY_PYTEST_EXTRA_ARGS", '["--color=no"]')),
        str(project_path / "tests"),
    ]

    assert "--color=no" in command, command

    if output_dir is not None:
        command.append(f"--report-log={output_dir / 'package_tests.jsonl'}")

    lldb_debug_config = config.Settings.from_environment(env)

    if lldb_debug_config.enabled:
        logging.info("LLDB is enabled, running pytest under LLDB")

        command.extend(
            [
                "-p",
                "hstd_py_lib.debug_utils.pytest_plugin",
            ]
        )

        script = (
            lldb_debug_config.script
            if lldb_debug_config.script is not None
            else Path(bootstrap.__file__).resolve()
        )

        exit_status_script = Path(__file__).resolve().with_name("lldb_exit_status.py")

        command = [
            "lldb",
            "--batch",
            "-o",
            f"command script import {shlex.quote(str(script))}",
            "-o",
            "rich-backtrace-configure",
            "-o",
            "run",
            "-o",
            f"command script import {shlex.quote(str(exit_status_script))}",
            "--",
            *command,
        ]

    with TemporaryDirectory(prefix="hstd-pytest-backtraces-") as directory:
        run_env = dict(env)

        if lldb_debug_config.enabled:
            run_env["HSTD_PY_LLDB_PYTEST_BACKTRACE_DIR"] = directory

        try:
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
                stage_name="package_tests",
                env=run_env,
                output_dir=output_dir,
            )

        finally:
            if (
                lldb_debug_config.enabled
                and os.getenv("HSTD_PY_LLDB_PYTEST_SHOW_WORKER_LOGS") == "1"
            ):
                # Show all errors from individual workers during execution.
                for log in Path(directory).rglob("*"):
                    if log.is_file():
                        logging.error(f"{log}:\n{log.read_text()}")


def install_test_package(
    test_package: Path,
    workspace_root: Path,
    environment_path: Path,
    *,
    env: dict[str, str],
    output_dir: Path | None = None,
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
        stage_name="install_test_package",
        env=env,
        output_dir=output_dir,
    )


def run_test_package(
    test_package: Path,
    workspace_root: Path,
    project_name: str,
    *,
    env: dict[str, str],
    output_dir: Path | None = None,
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
        stage_name="test_package",
        env=env,
        output_dir=output_dir,
    )


def validate_package(
    project_path: Path,
    *,
    editable: bool,
    conan_profile: Path | None,
    output_dir: Path | None = None,
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
        env["PYTHON_COLORS"] = "0"

        if conan_profile is not None:
            env["CONAN_PROFILE"] = str(conan_profile)

        if output_dir is not None:
            output_dir = output_dir.resolve()
            output_dir.mkdir(parents=True, exist_ok=True)

        sync_environment(
            workspace_root,
            project_name,
            editable=editable,
            env=env,
            output_dir=output_dir,
        )
        run_package_tests(
            project_path,
            workspace_root,
            project_name,
            env=env,
            output_dir=output_dir,
        )
        install_test_package(
            test_package,
            workspace_root,
            environment_path,
            env=env,
            output_dir=output_dir,
        )
        run_test_package(
            test_package,
            workspace_root,
            project_name,
            env=env,
            output_dir=output_dir,
        )


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
    parser.add_argument(
        "--output-dir",
        type=Path,
        help="Write the pytest JSONL report and subprocess logs to this directory.",
    )

    arguments = parser.parse_args()

    try:
        validate_package(
            arguments.project_path,
            editable=arguments.editable,
            conan_profile=(
                arguments.conan_profile.resolve() if arguments.conan_profile else None
            ),
            output_dir=arguments.output_dir,
        )
    except (RuntimeError, subprocess.CalledProcessError) as error:
        logging.error(f"{error}")
        sys.exit(1)

    logging.info("package validation OK, no errors")


if __name__ == "__main__":
    main()
