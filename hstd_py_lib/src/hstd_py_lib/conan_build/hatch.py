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
        if self.target_name != "wheel":
            return

        reference = self.config["reference"]
        protobuf_config = self.config.get("protobuf")

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
                deploy_directory = self._deploy_package(
                    reference=reference,
                    cwd=workspace_root,
                )
        else:
            deploy_directory = self._deploy_package(
                reference=reference,
                cwd=Path(self.root),
            )

        with (deploy_directory / "manifest.json").open(encoding="utf-8") as file:
            manifest = json.load(file)

        if manifest["artifacts"]:
            build_data["pure_python"] = False
            build_data["infer_tag"] = True

        for artifact in manifest["artifacts"]:
            self._include_artifact(
                version=version,
                build_data=build_data,
                source=deploy_directory / artifact["source"],
                destination=Path(artifact["destination"]),
            )

        if protobuf_config is not None:
            generated_directory = self._generate_protobuf(
                deploy_directory=deploy_directory,
                config=protobuf_config,
                deployment=manifest["protobuf"],
            )

            self._include_artifact(
                version=version,
                build_data=build_data,
                source=generated_directory,
                destination=Path(protobuf_config["destination"]),
            )

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

    def _artifact_configurations(self) -> list[dict[str, Any]]:
        if "artifacts" in self.config:
            if "artifact" in self.config or "destination" in self.config:
                raise ValueError(
                    "Configure either 'artifacts' or the legacy "
                    "'artifact'/'destination' fields, not both"
                )

            return list(self.config["artifacts"])

        if "artifact" in self.config:
            return [
                {
                    "artifact": self.config["artifact"],
                    "destination": self.config.get("destination", ""),
                }
            ]

        if "protobuf" in self.config:
            return []

        raise ValueError("The Conan hook requires 'artifact', 'artifacts', or 'protobuf'")

    def _include_artifact(
        self,
        version: str,
        build_data: dict[str, Any],
        source: Path,
        destination: Path,
    ) -> None:
        if destination.is_absolute() or ".." in destination.parts:
            raise ValueError(
                f"Artifact destination must be package-relative: {destination}"
            )

        self._log(f"selected artifact: {source}")
        self._log(f"wheel artifact path: {destination.as_posix()}")

        force_include = build_data.setdefault("force_include", {})
        force_include[str(source)] = destination.as_posix()

        if version != "editable":
            return

        editable_root = Path(self.config.get("editable-root", "src"))

        if editable_root.is_absolute() or ".." in editable_root.parts:
            raise ValueError(f"Editable root must be project-relative: {editable_root}")

        source_destination = Path(self.root) / editable_root / destination

        self._log(f"copying editable artifact to: {source_destination}")

        source_destination.parent.mkdir(parents=True, exist_ok=True)

        if source.is_dir():
            if source_destination.exists():
                shutil.rmtree(source_destination)

            shutil.copytree(source, source_destination)
        else:
            if source.suffix == ".so":
                self._remove_stale_extensions(
                    source_destination.parent,
                    source.name,
                )

            shutil.copy2(source, source_destination)

    def _generate_protobuf(
        self,
        deploy_directory: Path,
        config: dict[str, Any],
        deployment: dict[str, Any],
    ) -> Path:
        import grpc_tools

        include_directories = [
            deploy_directory / directory for directory in deployment["include-roots"]
        ]

        protobuf_include = Path(grpc_tools.__file__).resolve().parent / "_proto"
        include_directories.append(protobuf_include)

        sources = [deploy_directory / source for source in deployment["sources"]]

        sources.extend(
            protobuf_include / relative_path
            for relative_path in config.get("well-known-sources", [])
        )

        for source in sources:
            if not source.is_file():
                raise FileNotFoundError(source)

        output_directory = Path(
            tempfile.mkdtemp(
                prefix="generated-protobuf-",
                dir=deploy_directory,
            )
        )

        command = [
            sys.executable,
            "-m",
            "grpc_tools.protoc",
            *(f"--proto_path={directory}" for directory in include_directories),
            f"--python_betterproto2_out={output_directory}",
            *(str(source) for source in sources),
        ]

        self._run(
            phase="generate betterproto2 bindings",
            command=command,
            cwd=Path(self.root),
        )

        if not any(output_directory.iterdir()):
            raise RuntimeError(
                f"Protobuf generation produced no files: {output_directory}"
            )

        return output_directory

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

        # fmt: off
        return [
            "-c", f"tools.build:skip_test={not run_tests}",
            "-c", f"user.haxorg:python_executable={sys.executable}",
            "-c", f"user.haxorg:python_abi={sysconfig.get_config_var('SOABI')}",
            "-c", f"user.haxorg:uv_project={self._uv_workspace_root()}",
        ]
        # fmt: on

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

    def _deploy_package(
        self,
        reference: str,
        cwd: Path,
    ) -> Path:
        self._temporary_directory = tempfile.TemporaryDirectory(prefix="hatch_conan_")
        temporary_root = Path(self._temporary_directory.name)

        deploy_directory = temporary_root / "deployment"
        configuration_path = temporary_root / "configuration.json"
        deployer_path = Path(__file__).resolve().with_name("deployer.py")

        configuration = {
            "reference": reference,
            "artifacts": self._artifact_configurations(),
            "protobuf": self.config.get("protobuf"),
        }

        with configuration_path.open("w", encoding="utf-8") as file:
            json.dump(configuration, file, indent=2)

        self._log(f"deployment directory: {deploy_directory}")
        self._log(f"deployer: {deployer_path}")

        command = [
            "conan",
            "install",
            f"--requires={reference}",
            f"--deployer={deployer_path}",
            f"--deployer-folder={deploy_directory}",
            "--build=missing",
            "-s",
            "build_type=Release",
            "-c",
            f"user.haxorg:hatch_deployment={configuration_path}",
        ]

        conan_profile = os.environ.get("CONAN_PROFILE")

        if conan_profile:
            command.extend(["--profile:all", conan_profile])

        command.extend(self._python_configuration())

        self._run(
            phase=f"deploy Conan package for {reference}",
            command=command,
            cwd=cwd,
        )

        return deploy_directory

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
