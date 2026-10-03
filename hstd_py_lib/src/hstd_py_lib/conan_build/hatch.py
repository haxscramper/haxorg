import fcntl
import json
import os
import shlex
import shutil
import subprocess
import sys
import sysconfig
import tempfile
from pathlib import Path
from typing import Any

import tomllib
from hatchling.builders.hooks.plugin.interface import BuildHookInterface
from hatchling.plugin import hookimpl


class ConanBuildHook(BuildHookInterface):
    PLUGIN_NAME = "conan"

    def initialize(
        self,
        version: str,
        build_data: dict[str, Any],
    ) -> None:
        reference = self.config["reference"]
        artifact_pattern = self.config["artifact"]
        destination = self.config.get("destination", "")

        self._log(f"build version: {version}")
        self._log(f"project root: {self.root}")
        self._log(f"hook configuration: {dict(self.config)}")
        self._log(f"CONAN_PROFILE: {os.environ.get('CONAN_PROFILE', '<unset>')}")

        workspace_root = self._find_workspace(reference)

        self._log(
            "workspace root: "
            f"{workspace_root if workspace_root is not None else '<none>'}"
        )

        if workspace_root is not None:
            lock_path = workspace_root / "build" / "hatch_conan_workspace.lock"
            lock_path.parent.mkdir(parents=True, exist_ok=True)

            self._log(f"waiting for workspace lock: {lock_path}")

            with lock_path.open("w") as lock_file:
                fcntl.flock(lock_file, fcntl.LOCK_EX)
                self._log(f"acquired workspace lock: {lock_path}")

                self._prepare_workspace(workspace_root)
                artifact = self._deploy_artifact(
                    reference=reference,
                    artifact_pattern=artifact_pattern,
                    cwd=workspace_root,
                )
        else:
            artifact = self._deploy_artifact(
                reference=reference,
                artifact_pattern=artifact_pattern,
                cwd=Path(self.root),
            )

        wheel_path = Path(destination) / artifact.name

        self._log(f"selected artifact: {artifact}")
        self._log(f"wheel artifact path: {wheel_path.as_posix()}")

        build_data["pure_python"] = False
        build_data["infer_tag"] = True

        force_include = build_data.setdefault("force_include", {})
        force_include[str(artifact)] = wheel_path.as_posix()

        if version == "editable":
            source_destination = Path(self.root) / "src" / wheel_path

            self._log(f"copying editable artifact to: {source_destination}")

            source_destination.parent.mkdir(parents=True, exist_ok=True)

            self._remove_stale_extensions(
                source_destination.parent,
                artifact.name,
            )
            shutil.copy2(artifact, source_destination)

    def finalize(
        self,
        version: str,
        build_data: dict[str, Any],
        artifact_path: str,
    ) -> None:
        self._log(f"finalized build artifact: {artifact_path}")

        temporary_directory = getattr(self, "_temporary_directory", None)
        if temporary_directory is not None:
            self._log(
                f"removing temporary deployment directory: {temporary_directory.name}"
            )
            temporary_directory.cleanup()

    def _uv_workspace_root(self) -> Path:
        for directory in (Path(self.root), *Path(self.root).parents):
            pyproject = directory / "pyproject.toml"

            if pyproject.is_file():
                with pyproject.open("rb") as file:
                    data = tomllib.load(file)

                if "workspace" in data.get("tool", {}).get("uv", {}):
                    return directory

        raise RuntimeError("Could not find the uv workspace root")

    def _python_configuration(self) -> list[str]:
        run_tests = os.environ.get("HATCH_CONAN_RUN_TESTS") == "1"

        return [
            # fmt: off
            "-c",
            f"tools.build:skip_test={not run_tests}",
            "-c",
            f"user.haxorg:python_executable={sys.executable}",
            "-c",
            f"user.haxorg:python_abi={sysconfig.get_config_var('SOABI')}",
            "-c",
            f"user.haxorg:uv_project={self._uv_workspace_root()}",
            # fmt: on
        ]

    def _find_workspace(self, reference: str) -> Path | None:
        project_root = Path(self.root).resolve()

        workspace_file = next(
            (
                parent / "conanws.yml"
                for parent in (project_root, *project_root.parents)
                if (parent / "conanws.yml").is_file()
            ),
            None,
        )

        if workspace_file is None:
            self._log("no conanws.yml found")
            return None

        self._log(f"workspace definition: {workspace_file}")

        command = [
            "conan",
            "workspace",
            "info",
            "--format=json",
        ]

        self._log("phase: inspect Conan workspace")
        self._log(f"cwd: {workspace_file.parent}")
        self._log(f"command: {shlex.join(command)}")

        try:
            result = subprocess.run(
                command,
                cwd=workspace_file.parent,
                check=True,
                stdout=subprocess.PIPE,
                text=True,
            )
        except subprocess.CalledProcessError as error:
            self._log("phase failed: inspect Conan workspace")
            self._log(f"exit code: {error.returncode}")
            raise

        self._log(f"workspace info: {result.stdout.strip()}")

        workspace = json.loads(result.stdout)
        workspace_packages = [package["ref"] for package in workspace["packages"]]

        self._log("workspace packages: " + ", ".join(workspace_packages))

        if reference not in workspace_packages:
            self._log(f"reference is not a workspace package: {reference}")
            return None

        return Path(workspace["folder"])

    def _prepare_workspace(self, workspace_root: Path) -> None:
        command = [
            "conan",
            "workspace",
            "super-install",
            f"--output-folder={workspace_root / 'build' / 'conan_super'}",
            "-s",
            "build_type=Release",
            "--build=missing",
        ]

        conan_profile = os.environ.get("CONAN_PROFILE")
        if conan_profile:
            command.extend(["--profile:all", conan_profile])

        command.extend(self._python_configuration())

        self._run(
            phase="install workspace dependencies",
            command=command,
            cwd=workspace_root,
        )

        build_command = [
            "conan",
            "workspace",
            "build",
        ]

        if conan_profile:
            build_command.extend(["--profile:all", conan_profile])

        build_command.extend(self._python_configuration())

        self._run(
            phase="build workspace packages",
            command=build_command,
            cwd=workspace_root,
        )

    def _deploy_artifact(
        self,
        reference: str,
        artifact_pattern: str,
        cwd: Path,
    ) -> Path:
        self._temporary_directory = tempfile.TemporaryDirectory(prefix="hatch_conan_")
        deploy_directory = Path(self._temporary_directory.name)

        self._log(f"deployment directory: {deploy_directory}")
        self._log(f"artifact pattern: {artifact_pattern}")

        command = [
            "conan",
            "install",
            f"--requires={reference}",
            "--deployer=full_deploy",
            f"--deployer-folder={deploy_directory}",
            "--build=missing",
            "-s",
            "build_type=Release",
        ]

        conan_profile = os.environ.get("CONAN_PROFILE")
        if conan_profile:
            command.extend(["--profile:all", conan_profile])

        command.extend(self._python_configuration())

        self._run(
            phase=f"deploy Conan artifact for {reference}",
            command=command,
            cwd=cwd,
        )

        artifacts = sorted(deploy_directory.glob(f"**/{artifact_pattern}"))

        if artifacts:
            self._log(
                "matching artifacts:\n" + "\n".join(f"  {path}" for path in artifacts)
            )
        else:
            self._log("matching artifacts: <none>")

        if len(artifacts) != 1:
            formatted = "\n".join(f"  {path}" for path in artifacts)
            raise RuntimeError(
                f"Expected exactly one Conan artifact matching "
                f"{artifact_pattern!r}, found {len(artifacts)}:\n{formatted}"
            )

        return artifacts[0]

    def _remove_stale_extensions(
        self,
        directory: Path,
        artifact_name: str,
    ) -> None:
        module_name = artifact_name.split(".", maxsplit=1)[0]

        for candidate in directory.glob(f"{module_name}*.so"):
            self._log(f"removing stale extension: {candidate}")
            candidate.unlink()

    def _run(
        self,
        phase: str,
        command: list[str],
        cwd: Path,
    ) -> None:
        self._log(f"phase: {phase}")
        self._log(f"cwd: {cwd}")
        self._log(f"command: {shlex.join(command)}")

        try:
            subprocess.run(
                command,
                cwd=cwd,
                check=True,
            )
        except subprocess.CalledProcessError as error:
            self._log(f"phase failed: {phase}")
            self._log(f"exit code: {error.returncode}")
            raise

    def _log(self, message: str) -> None:
        print(
            f"[hatch-conan] {message}",
            file=sys.stderr,
            flush=True,
        )


@hookimpl
def hatch_register_build_hook() -> type[BuildHookInterface]:
    return ConanBuildHook
