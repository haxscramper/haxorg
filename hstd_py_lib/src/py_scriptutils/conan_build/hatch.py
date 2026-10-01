import os
import shutil
import subprocess
import tempfile
from pathlib import Path
from typing import Any

from hatchling.builders.hooks.plugin.interface import BuildHookInterface


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

        self._temporary_directory = tempfile.TemporaryDirectory(prefix="hatch_conan_")
        deploy_directory = Path(self._temporary_directory.name)

        command = [
            "conan",
            "install",
            f"--requires={reference}",
            "--deployer=full_deploy",
            f"--deployer-folder={deploy_directory}",
            "--build=never",
            "-s",
            "build_type=Release",
        ]

        conan_profile = os.environ.get("CONAN_PROFILE")
        if conan_profile:
            command.extend(["--profile:all", conan_profile])

        subprocess.run(command, check=True)

        artifacts = sorted(deploy_directory.glob(f"**/{artifact_pattern}"))
        if len(artifacts) != 1:
            formatted = "\n".join(f"  {path}" for path in artifacts)
            raise RuntimeError(
                f"Expected exactly one Conan artifact matching "
                f"{artifact_pattern!r}, found {len(artifacts)}:\n{formatted}"
            )

        artifact = artifacts[0]
        wheel_path = Path(destination) / artifact.name

        force_include = build_data.setdefault("force_include", {})
        force_include[str(artifact)] = wheel_path.as_posix()

        if version == "editable":
            source_destination = Path(self.root) / "src" / wheel_path
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
        temporary_directory = getattr(self, "_temporary_directory", None)
        if temporary_directory is not None:
            temporary_directory.cleanup()

    def _remove_stale_extensions(
        self,
        directory: Path,
        artifact_name: str,
    ) -> None:
        module_name = artifact_name.split(".", maxsplit=1)[0]

        for candidate in directory.glob(f"{module_name}*.so"):
            candidate.unlink()
