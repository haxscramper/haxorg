#!/usr/bin/env python

import argparse
import logging
import os
import subprocess
import sys
import tempfile
from pathlib import Path

import tomllib

logging.basicConfig(
    level=logging.DEBUG,
    format="%(levelname)s %(filename)s:%(lineno)d: %(message)s",
)

CONAN_PROJECTS = {
    "haxorg_py_lib": "haxorg_cpp_py_wrap",
    "htsd_py_text_layout": "hstd_cpp_text_layout_py_wrap",
}


def run(
    command: list[str],
    *,
    cwd: Path,
    env: dict[str, str] | None = None,
) -> None:
    logging.info("==> %s", " ".join(command))
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


def create_conan_package(
    workspace_root: Path,
    project_path: Path,
    conan_profile: Path,
) -> None:
    conan_project = CONAN_PROJECTS.get(project_path.name)
    if conan_project is None:
        return

    run(
        [
            "conan",
            "create",
            str(workspace_root / conan_project),
            "--profile:all",
            str(conan_profile),
            "-s",
            "build_type=Release",
            "--build=missing",
            "-vstatus",
        ],
        cwd=workspace_root,
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

    if editable:
        if project_path.name in CONAN_PROJECTS:
            if conan_profile is None:
                raise RuntimeError(
                    "--conan-profile is required for editable validation of "
                    f"{project_path.name}"
                )

            create_conan_package(
                workspace_root,
                project_path,
                conan_profile,
            )

    run(
        ["uv", "run", "--group", "dev", "ruff", "check", str(project_path)],
        cwd=workspace_root,
    )

    with tempfile.TemporaryDirectory(prefix="verify_pkg_") as temporary:
        environment_path = Path(temporary) / ".venv"
        environment = os.environ.copy()
        environment["UV_PROJECT_ENVIRONMENT"] = str(environment_path)

        if conan_profile is not None:
            environment["CONAN_PROFILE"] = str(conan_profile)

        sync_command = [
            "uv",
            "sync",
            "--project",
            str(workspace_root),
            "--package",
            project_name,
            "--group",
            "dev",
        ]

        if not editable:
            sync_command.append("--no-editable")

        run(
            sync_command,
            cwd=workspace_root,
            env=environment,
        )

        python = environment_path / "bin" / "python"

        run(
            [
                str(python),
                "-m",
                "pytest",
                str(project_path / "tests"),
            ],
            cwd=workspace_root,
            env=environment,
        )

        run(
            [
                "uv",
                "pip",
                "install",
                "--python",
                str(python),
                str(test_package),
            ],
            cwd=workspace_root,
            env=environment,
        )

        run(
            [
                str(python),
                str(test_package / "main.py"),
            ],
            cwd=test_package,
            env=environment,
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
        logging.error("%s", error)
        sys.exit(1)


if __name__ == "__main__":
    main()
