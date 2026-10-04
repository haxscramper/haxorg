import hashlib
import json
import os
import shlex
import shutil
import subprocess
import sys
import sysconfig
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

import pytest

REPOSITORY = Path(__file__).resolve().parents[2]
ASSETS = Path(__file__).with_suffix("")
PROFILE = REPOSITORY / "repo_tool_configs/conan/conanprofile.txt"
UV_VALIDATOR = REPOSITORY / "repo_ci_config/py_ci/test_uv_install.py"
SHARED_SCHEMA = "ex_cpp_shared_schema"


@dataclass(frozen=True)
class Case:
    native: str
    python: str
    executable: bool = False
    nanobind: bool = False
    protobuf: bool = False


CASES = [
    Case(
        native="ex_cpp_protobuf_executable",
        python="ex_py_needs_protobuf_executable",
        executable=True,
        protobuf=True,
    ),
    Case(
        native="ex_cpp_protobuf_nanobind",
        python="ex_py_needs_protobuf_nanobind",
        nanobind=True,
        protobuf=True,
    ),
    Case(
        native="ex_cpp_nanobind",
        python="ex_py_needs_nanobind",
        nanobind=True,
    ),
    Case(
        native="ex_cpp_executable",
        python="ex_py_needs_executable",
        executable=True,
    ),
    Case(
        native="ex_cpp_protobuf",
        python="ex_py_needs_protobuf",
        protobuf=True,
    ),
]


def write(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content, encoding="utf-8")


def render_tree(
    source: Path,
    destination: Path,
    replacements: dict[str, str],
) -> None:
    for source_file in sorted(source.rglob("*")):
        if not source_file.is_file():
            continue

        relative = source_file.relative_to(source).as_posix()
        content = source_file.read_text(encoding="utf-8")

        if relative.endswith(".in"):
            relative = relative.removesuffix(".in")

        for token, value in replacements.items():
            relative = relative.replace(token, value)
            content = content.replace(token, value)

        write(destination / relative, content)


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def one_file(paths: list[Path]) -> Path:
    files = sorted({path.resolve() for path in paths if path.is_file()})
    assert len(files) == 1, files
    return files[0]


@dataclass
class Sandbox:
    directory: Path
    root: Path
    environment: dict[str, str]
    case: Case | None
    members: list[str] = field(default_factory=list)
    command_number: int = 0

    @property
    def python_package(self) -> str:
        if self.case is None:
            return "ex_py_clean_python"

        return self.case.python

    @property
    def python_project(self) -> Path:
        return self.root / self.python_package

    def run(
        self,
        command: list[str],
        *,
        cwd: Path | None = None,
        environment: dict[str, str] | None = None,
    ) -> subprocess.CompletedProcess[str]:
        self.command_number += 1
        log = self.directory / "logs" / f"{self.command_number:03d}.log"
        log.parent.mkdir(parents=True, exist_ok=True)

        actual_environment = self.environment.copy()
        if environment is not None:
            actual_environment.update(environment)

        actual_cwd = cwd if cwd is not None else self.root

        result = subprocess.run(
            command,
            cwd=actual_cwd,
            env=actual_environment,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            check=False,
        )

        write(
            log,
            (
                f"cwd: {actual_cwd}\n"
                f"command: {shlex.join(command)}\n"
                f"returncode: {result.returncode}\n"
                f"\nstdout:\n{result.stdout}"
                f"\nstderr:\n{result.stderr}"
            ),
        )

        if result.returncode != 0:
            print(log.read_text(encoding="utf-8"))

        result.check_returncode()
        return result

    def set_version(self, version: int) -> None:
        self.environment["EX_EXPECTED_VERSION"] = str(version)

        if self.case is None:
            write(
                self.python_project / "src" / self.python_package / "_value.py",
                f"VALUE = {version}\n",
            )
            return

        native = self.root / self.case.native
        write(
            native / "src" / self.case.native / "value.hpp",
            (
                "#pragma once\n"
                "\n"
                "namespace ex_fixture {\n"
                f"inline constexpr int value = {version};\n"
                "}\n"
            ),
        )

        if self.case.protobuf:
            revision = ""
            if 2 <= version:
                revision = "  int32 revision = 3;\n"

            write(
                native / "proto" / self.case.native / "api.proto",
                (
                    'syntax = "proto3";\n'
                    "\n"
                    "package ex_fixture;\n"
                    "\n"
                    f'import "{SHARED_SCHEMA}/shared.proto";\n'
                    'import "google/protobuf/struct.proto";\n'
                    "\n"
                    "message Record {\n"
                    "  string payload = 1;\n"
                    "  google.protobuf.Struct metadata = 2;\n"
                    f"{revision}"
                    "}\n"
                ),
            )

    def reinstall_arguments(self) -> list[str]:
        arguments = []

        for member in self.members:
            name = member.replace("/", "_").replace("_", "-")
            arguments.extend(["--reinstall-package", name])

        return arguments

    def sync(
        self,
        *,
        target: str | None = None,
        editable: bool = True,
        environment_path: Path | None = None,
    ) -> Path:
        if target is None:
            target = self.python_package

        if environment_path is None:
            environment_path = self.directory / "environments" / "workspace"

        command = [
            "uv",
            "--verbose",
            "sync",
            "--project",
            str(self.root),
            "--package",
            target,
            "--group",
            "dev",
            *self.reinstall_arguments(),
        ]

        if not editable:
            command.append("--no-editable")

        self.run(
            command,
            environment={
                "UV_PROJECT_ENVIRONMENT": str(environment_path),
            },
        )
        return environment_path

    def validate_uv(self, *, editable: bool) -> Path:
        environment_path = self.directory / "environments" / "validation"

        command = [
            sys.executable,
            str(UV_VALIDATOR),
            str(self.python_project),
            "--conan-profile",
            str(PROFILE),
        ]

        if editable:
            command.append("--editable")

        self.run(
            command,
            environment={
                "HAXORG_PY_TEST_UV_INSTALL_DIR_OVERRIDE": str(environment_path),
            },
        )
        return environment_path

    def probe(
        self,
        environment_path: Path,
        *,
        package: str | None = None,
        source: Path | None = None,
        editable: bool,
    ) -> dict[str, Any]:
        if package is None:
            package = self.python_package

        if source is None:
            source = self.python_project / "src"

        cwd = self.directory / "empty"
        cwd.mkdir(exist_ok=True)

        result = self.run(
            [
                str(environment_path / "bin" / "python"),
                str(ASSETS / "probe.py.in"),
            ],
            cwd=cwd,
            environment={
                "EX_PROBE_PACKAGE": package,
                "PATH": (f"{environment_path / 'bin'}:{self.environment['PATH']}"),
            },
        )

        lines = [
            line.removeprefix("EX_PROBE=")
            for line in result.stdout.splitlines()
            if line.startswith("EX_PROBE=")
        ]
        assert len(lines) == 1, result.stdout

        report = json.loads(lines[0])
        python_file = Path(report["python_file"]).resolve()

        assert python_file.is_relative_to(source.resolve()) is editable

        if not editable:
            assert python_file.is_relative_to(environment_path.resolve())

        return report

    def native_outputs(self) -> dict[str, tuple[int, str]]:
        assert self.case is not None

        roots = [
            self.root / self.case.native,
            self.root / "build",
        ]
        outputs = {}

        if self.case.executable:
            binary = one_file(
                [path for root in roots for path in root.rglob(self.case.native)],
            )
            outputs["executable"] = (
                binary.stat().st_mtime_ns,
                digest(binary),
            )

        if self.case.nanobind:
            extension = one_file(
                [
                    path
                    for root in roots
                    for path in root.rglob(f"{self.case.native}*.so")
                ],
            )
            outputs["nanobind"] = (
                extension.stat().st_mtime_ns,
                digest(extension),
            )

        return outputs

    def assert_workspace_provenance(self, report: dict[str, Any]) -> None:
        outputs = self.native_outputs()

        if "executable" in outputs:
            assert digest(Path(report["executable_file"])) == outputs["executable"][1]

        if "nanobind" in outputs:
            assert digest(Path(report["nanobind_file"])) == outputs["nanobind"][1]

    def conan_arguments(self) -> list[str]:
        return [
            "--profile:all",
            str(PROFILE),
            "-s",
            "build_type=Release",
            "-c",
            f"user.haxorg:python_executable={sys.executable}",
            "-c",
            f"user.haxorg:python_abi={sysconfig.get_config_var('SOABI')}",
            "-c",
            f"user.haxorg:uv_project={self.root}",
        ]

    def create_native(self) -> subprocess.CompletedProcess[str]:
        assert self.case is not None
        assert not (self.root / "conanws.yml").exists()

        native_test_environment = {
            "UV_PROJECT_ENVIRONMENT": str(
                self.directory / "environments" / "native-tests"
            ),
        }

        if self.case.protobuf:
            self.run(
                [
                    "conan",
                    "create",
                    str(self.root / SHARED_SCHEMA),
                    "--build=missing",
                    *self.conan_arguments(),
                    "-c",
                    "tools.build:skip_test=False",
                ],
                environment=native_test_environment,
            )

        result = self.run(
            [
                "conan",
                "create",
                str(self.root / self.case.native),
                "--build=missing",
                *self.conan_arguments(),
                "-c",
                "tools.build:skip_test=False",
            ],
            environment=native_test_environment,
        )

        marker = (
            f"EX_NATIVE_PYTEST:{self.case.native}:"
            f"{self.environment['EX_EXPECTED_VERSION']}"
        )
        assert marker in result.stdout + result.stderr
        return result

    def cached_package_folder(self) -> Path:
        assert self.case is not None

        result = self.run(
            [
                "conan",
                "graph",
                "info",
                f"--requires={self.case.native}/0.1.0",
                "--format=json",
                *self.conan_arguments(),
            ],
        )
        graph = json.loads(result.stdout)
        nodes = [
            node
            for node in graph["graph"]["nodes"].values()
            if str(node.get("ref", "")).split("#", maxsplit=1)[0]
            == f"{self.case.native}/0.1.0"
        ]
        assert len(nodes) == 1, nodes

        node = nodes[0]
        package_reference = f"{node['ref']}:{node['package_id']}"

        if node.get("prev"):
            package_reference += f"#{node['prev']}"

        result = self.run(
            ["conan", "cache", "path", package_reference],
        )
        folder = Path(result.stdout.strip()).resolve()
        assert folder.is_dir()
        assert folder.is_relative_to(Path(self.environment["CONAN_HOME"]).resolve())
        return folder

    def assert_cache_provenance(self, report: dict[str, Any]) -> None:
        assert self.case is not None
        folder = self.cached_package_folder()

        if self.case.executable:
            assert digest(Path(report["executable_file"])) == digest(
                folder / "bin" / self.case.native
            )

        if self.case.nanobind:
            cached_extension = one_file(
                list((folder / "lib").glob(f"{self.case.native}*.so"))
            )
            assert digest(Path(report["nanobind_file"])) == digest(cached_extension)

        if self.case.protobuf:
            cached_schema = folder / "proto" / self.case.native / "api.proto"
            source_schema = (
                self.root / self.case.native / "proto" / self.case.native / "api.proto"
            )
            assert cached_schema.read_bytes() == source_schema.read_bytes()


def make_native(
    sandbox: Sandbox,
    *,
    name: str,
    executable: bool = False,
    nanobind: bool = False,
    protobuf: bool = False,
    shared_schema: bool = False,
) -> None:
    project = sandbox.root / name

    render_tree(
        ASSETS / "common" / "native",
        project,
        {"@NATIVE@": name},
    )

    configuration = {
        "name": name,
        "executable": executable,
        "nanobind": nanobind,
        "protobuf": protobuf,
        "shared_schema": shared_schema,
    }

    write(
        project / "conandata.yml",
        json.dumps({"fixture": configuration}, indent=2),
    )
    write(
        project / "fixture.json",
        json.dumps(configuration, indent=2),
    )
    write(
        project / "fixture.cmake",
        (
            f"set(EX_NAME {name})\n"
            f"set(EX_EXECUTABLE {'ON' if executable else 'OFF'})\n"
            f"set(EX_NANOBIND {'ON' if nanobind else 'OFF'})\n"
            f"set(EX_PROTOBUF {'ON' if protobuf else 'OFF'})\n"
        ),
    )
    write(
        project / "tests" / "pyproject.toml",
        (
            "[project]\n"
            f'name = "{name}_pytest_package"\n'
            'version = "0.1.0"\n'
            'requires-python = ">=3.13,<3.14"\n'
            'dependencies = ["pytest"]\n'
            "\n"
            "[build-system]\n"
            'requires = ["hatchling>=1.27"]\n'
            'build-backend = "hatchling.build"\n'
            "\n"
            "[tool.hatch.build.targets.wheel]\n"
            f'packages = ["src/{name}_pytest_package"]\n'
        ),
    )
    write(
        project / "tests" / "src" / f"{name}_pytest_package" / "__init__.py",
        "",
    )

    sandbox.members.append(f"{name}/tests")

    if shared_schema:
        write(
            project / "proto" / name / "shared.proto",
            (
                'syntax = "proto3";\n'
                "\n"
                "package ex_shared;\n"
                "\n"
                "// Import-only resource: verifies transitive schema staging.\n"
                "// Referenced Python types are generated from owner sources\n"
                "// and explicitly configured well-known sources.\n"
                "message SharedResource {\n"
                "  string label = 1;\n"
                "}\n"
            ),
        )


def python_project_toml(case: Case | None, name: str) -> str:
    build_dependencies = ["hatchling>=1.27"]
    runtime_dependencies = []
    hook = ""
    sources = ""

    if case is not None:
        build_dependencies.extend(["hstd_py_lib", "conan>=2"])
        runtime_dependencies.append("hstd_py_lib")

        sources = "\n[tool.uv.sources]\nhstd_py_lib = { workspace = true }\n"
        hook = (
            "\n[tool.hatch.build.hooks.conan]\n"
            f'reference = "{case.native}/0.1.0"\n'
            'editable-root = "src"\n'
        )

        if case.executable:
            hook += (
                "\n[[tool.hatch.build.hooks.conan.artifacts]]\n"
                f'artifact = "{case.native}"\n'
                'package_type = "application"\n'
            )

        if case.nanobind:
            hook += (
                "\n[[tool.hatch.build.hooks.conan.artifacts]]\n"
                f'artifact = "{case.native}*.so"\n'
                'package_type = "shared-library"\n'
                f'destination = "{name}"\n'
            )

        if case.protobuf:
            build_dependencies.extend(
                [
                    "grpcio-tools",
                    "betterproto2-compiler",
                ]
            )
            runtime_dependencies.append("betterproto2")
            hook += (
                "\n[tool.hatch.build.hooks.conan.protobuf]\n"
                f'sources = ["{case.native}/api.proto"]\n'
                f'destination = "{name}/proto"\n'
                'well-known-sources = ["google/protobuf/struct.proto"]\n'
            )

    return (
        "[project]\n"
        f'name = "{name}"\n'
        'version = "0.1.0"\n'
        'requires-python = ">=3.13,<3.14"\n'
        f"dependencies = {json.dumps(runtime_dependencies)}\n"
        "\n[dependency-groups]\n"
        'dev = ["pytest"]\n'
        "\n[build-system]\n"
        f"requires = {json.dumps(build_dependencies)}\n"
        'build-backend = "hatchling.build"\n'
        "\n[tool.hatch.build.targets.wheel]\n"
        f'packages = ["src/{name}"]\n'
        f'exclude = ["/src/{name}/proto", "/src/{name}/*.so"]\n'
        f"{sources}"
        f"{hook}"
    )


def make_python(sandbox: Sandbox) -> None:
    case = sandbox.case
    name = sandbox.python_package

    replacements = {
        "@PYTHON@": name,
        "@NATIVE_LITERAL@": repr(case.native if case is not None else None),
        "@EXECUTABLE@": repr(case.executable if case is not None else False),
        "@NANOBIND@": repr(case.nanobind if case is not None else False),
        "@PROTOBUF@": repr(case.protobuf if case is not None else False),
    }

    render_tree(
        ASSETS / "common" / "python",
        sandbox.python_project,
        replacements,
    )
    write(
        sandbox.python_project / "pyproject.toml",
        python_project_toml(case, name),
    )
    write(
        sandbox.python_project / "test_package" / "pyproject.toml",
        (
            "[project]\n"
            f'name = "{name}_test_package"\n'
            'version = "0.1.0"\n'
            'requires-python = ">=3.13,<3.14"\n'
            f'dependencies = ["{name}"]\n'
            "\n[build-system]\n"
            'requires = ["hatchling>=1.27"]\n'
            'build-backend = "hatchling.build"\n'
            "\n[tool.hatch.build.targets.wheel]\n"
            f'packages = ["src/{name}_test_package"]\n'
        ),
    )
    write(
        sandbox.python_project
        / "test_package"
        / "src"
        / f"{name}_test_package"
        / "__init__.py",
        "",
    )
    sandbox.members.append(name)


def make_consumer(root: Path, dependency: str) -> None:
    project = root / "ex_py_consumer"

    write(
        project / "pyproject.toml",
        (
            "[project]\n"
            'name = "ex_py_consumer"\n'
            'version = "0.1.0"\n'
            'requires-python = ">=3.13,<3.14"\n'
            f'dependencies = ["{dependency}"]\n'
            "\n[dependency-groups]\n"
            'dev = ["pytest"]\n'
            "\n[build-system]\n"
            'requires = ["hatchling>=1.27"]\n'
            'build-backend = "hatchling.build"\n'
            "\n[tool.hatch.build.targets.wheel]\n"
            'packages = ["src/ex_py_consumer"]\n'
        ),
    )
    write(
        project / "src" / "ex_py_consumer" / "__init__.py",
        f"from {dependency} import verify\n",
    )


def write_workspace(sandbox: Sandbox, *, conan_workspace: bool) -> None:
    sources = []

    for member in sandbox.members:
        if member == "hstd_py_lib":
            name = member
        elif member.endswith("/tests"):
            name = member.removesuffix("/tests") + "_pytest_package"
        else:
            name = member

        sources.append(f"{name} = {{ workspace = true }}")

    write(
        sandbox.root / "pyproject.toml",
        (
            "[tool.uv.workspace]\n"
            f"members = {json.dumps(sandbox.members)}\n"
            "\n[tool.uv.sources]\n" + "\n".join(sources) + "\n\n[dependency-groups]\n"
            'dev = ["pytest"]\n'
        ),
    )

    if conan_workspace:
        assert sandbox.case is not None
        native_names = [sandbox.case.native]

        if sandbox.case.protobuf:
            native_names.insert(0, SHARED_SCHEMA)

        # JSON is valid YAML and avoids a second serialization dependency.
        write(
            sandbox.root / "conanws.yml",
            json.dumps(
                {
                    "packages": [
                        {
                            "path": name,
                            "ref": f"{name}/0.1.0",
                            "output_folder": f"build/conan_build/{name}",
                        }
                        for name in native_names
                    ],
                },
                indent=2,
            ),
        )


def make_sandbox(
    directory: Path,
    case: Case | None,
    *,
    conan_workspace: bool,
) -> Sandbox:
    root = directory / "workspace"
    root.mkdir(parents=True)

    environment = os.environ.copy()
    for key in [
        "VIRTUAL_ENV",
        "PYTHONPATH",
        "UV_PROJECT_ENVIRONMENT",
        "HAXORG_PY_TEST_UV_INSTALL_DIR_OVERRIDE",
    ]:
        environment.pop(key, None)

    environment.update(
        {
            "CONAN_HOME": str(directory / "conan-home"),
            "CONAN_PROFILE": str(PROFILE),
            "UV_CACHE_DIR": str(directory / "uv-cache"),
            "PYTHONNOUSERSITE": "1",
            "HATCH_CONAN_RUN_TESTS": "0",
            "HSTD_PY_PYTEST_EXTRA_ARGS": json.dumps(["-s"]),
            "EX_EXPECTED_VERSION": "1",
            "CC": "clang",
            "CXX": "clang++",
        }
    )

    sandbox = Sandbox(
        directory=directory,
        root=root,
        environment=environment,
        case=case,
    )

    shutil.copytree(
        REPOSITORY / "hstd_py_lib",
        root / "hstd_py_lib",
        ignore=shutil.ignore_patterns(
            "tests",
            "__pycache__",
            ".pytest_cache",
            ".venv",
            "dist",
            "build",
        ),
    )
    sandbox.members.append("hstd_py_lib")

    if case is not None:
        make_native(
            sandbox,
            name=case.native,
            executable=case.executable,
            nanobind=case.nanobind,
            protobuf=case.protobuf,
        )

        if case.protobuf:
            make_native(
                sandbox,
                name=SHARED_SCHEMA,
                protobuf=True,
                shared_schema=True,
            )

    make_python(sandbox)
    make_consumer(root, sandbox.python_package)
    sandbox.members.append("ex_py_consumer")

    sandbox.set_version(1)
    write_workspace(sandbox, conan_workspace=conan_workspace)

    if case is not None:
        sandbox.run(["conan", "profile", "detect", "--force"])
        sandbox.run(
            [
                "conan",
                "export",
                str(REPOSITORY / "haxorg_conan_base"),
            ]
        )

    return sandbox


def make_downstream(sandbox: Sandbox) -> Path:
    root = sandbox.directory / "consumer"
    root.mkdir()

    shutil.copytree(
        sandbox.root / "hstd_py_lib",
        root / "hstd_py_lib",
    )
    shutil.copytree(
        sandbox.python_project,
        root / sandbox.python_package,
    )

    project_file = root / sandbox.python_package / "pyproject.toml"
    content = project_file.read_text(encoding="utf-8")
    content = content.replace(
        "hstd_py_lib = { workspace = true }",
        'hstd_py_lib = { path = "../hstd_py_lib" }',
    )
    write(project_file, content)

    make_consumer(root, sandbox.python_package)

    write(
        root / "pyproject.toml",
        (
            "[tool.uv.workspace]\n"
            'members = ["ex_py_consumer"]\n'
            f'exclude = ["{sandbox.python_package}", "hstd_py_lib"]\n'
            "\n[tool.uv.sources]\n"
            f"{sandbox.python_package} = {{ "
            f'path = "{sandbox.python_package}", editable = false }}\n'
            'hstd_py_lib = { path = "hstd_py_lib" }\n'
            "\n[dependency-groups]\n"
            'dev = ["pytest"]\n'
        ),
    )
    return root


def sync_downstream(sandbox: Sandbox, root: Path) -> Path:
    environment_path = sandbox.directory / "environments" / "consumer"

    sandbox.run(
        [
            "uv",
            "--verbose",
            "sync",
            "--project",
            str(root),
            "--package",
            "ex_py_consumer",
            "--no-editable",
            "--reinstall-package",
            sandbox.python_package.replace("_", "-"),
            "--reinstall-package",
            "hstd-py-lib",
        ],
        cwd=root,
        environment={
            "UV_PROJECT_ENVIRONMENT": str(environment_path),
        },
    )
    return environment_path


@pytest.mark.parametrize("case", CASES, ids=lambda case: case.native)
def test_editable_workspace_updates(
    stable_test_dir: Path,
    case: Case,
) -> None:
    sandbox = make_sandbox(stable_test_dir, case, conan_workspace=True)

    environment = sandbox.sync()
    first = sandbox.probe(environment, editable=True)
    sandbox.assert_workspace_provenance(first)
    initial_outputs = sandbox.native_outputs()

    sandbox.sync()
    unchanged = sandbox.probe(environment, editable=True)
    sandbox.assert_workspace_provenance(unchanged)

    assert sandbox.native_outputs() == initial_outputs
    assert unchanged == first

    sandbox.set_version(2)
    sandbox.sync()
    updated = sandbox.probe(environment, editable=True)
    sandbox.assert_workspace_provenance(updated)

    assert updated["version"] == 2
    for kind, initial in initial_outputs.items():
        assert sandbox.native_outputs()[kind][1] != initial[1]


@pytest.mark.parametrize("case", CASES, ids=lambda case: case.native)
@pytest.mark.parametrize("editable", [True, False], ids=["editable", "wheel"])
def test_uv_package_validation(
    stable_test_dir: Path,
    case: Case,
    editable: bool,
) -> None:
    sandbox = make_sandbox(stable_test_dir, case, conan_workspace=True)

    environment = sandbox.validate_uv(editable=editable)
    first = sandbox.probe(environment, editable=editable)
    sandbox.assert_workspace_provenance(first)

    sandbox.set_version(2)
    environment = sandbox.validate_uv(editable=editable)
    updated = sandbox.probe(environment, editable=editable)
    sandbox.assert_workspace_provenance(updated)

    assert updated["version"] == 2


@pytest.mark.parametrize("case", CASES, ids=lambda case: case.native)
def test_conan_create_validation(
    stable_test_dir: Path,
    case: Case,
) -> None:
    sandbox = make_sandbox(stable_test_dir, case, conan_workspace=False)

    sandbox.create_native()
    environment = sandbox.sync(editable=False)
    first = sandbox.probe(environment, editable=False)
    sandbox.assert_cache_provenance(first)

    sandbox.set_version(2)
    sandbox.create_native()
    sandbox.sync(editable=False)
    updated = sandbox.probe(environment, editable=False)
    sandbox.assert_cache_provenance(updated)

    assert updated["version"] == 2


@pytest.mark.parametrize("case", CASES, ids=lambda case: case.native)
def test_downstream_cached_dependency(
    stable_test_dir: Path,
    case: Case,
) -> None:
    sandbox = make_sandbox(stable_test_dir, case, conan_workspace=False)

    sandbox.create_native()
    consumer = make_downstream(sandbox)
    environment = sync_downstream(sandbox, consumer)

    first = sandbox.probe(
        environment,
        package="ex_py_consumer",
        source=consumer / sandbox.python_package / "src",
        editable=False,
    )
    sandbox.assert_cache_provenance(first)

    sandbox.set_version(2)
    sandbox.create_native()
    sync_downstream(sandbox, consumer)

    updated = sandbox.probe(
        environment,
        package="ex_py_consumer",
        source=consumer / sandbox.python_package / "src",
        editable=False,
    )
    sandbox.assert_cache_provenance(updated)

    assert updated["version"] == 2


@pytest.mark.parametrize("case", CASES, ids=lambda case: case.native)
def test_transitive_python_dependency(
    stable_test_dir: Path,
    case: Case,
) -> None:
    sandbox = make_sandbox(stable_test_dir, case, conan_workspace=True)

    environment = sandbox.sync(target="ex_py_consumer")
    first = sandbox.probe(
        environment,
        package="ex_py_consumer",
        editable=True,
    )
    sandbox.assert_workspace_provenance(first)

    sandbox.set_version(2)
    sandbox.sync(target="ex_py_consumer")
    updated = sandbox.probe(
        environment,
        package="ex_py_consumer",
        editable=True,
    )
    sandbox.assert_workspace_provenance(updated)

    assert updated["version"] == 2


@pytest.mark.parametrize(
    "case",
    [case for case in CASES if case.nanobind],
    ids=lambda case: case.native,
)
def test_editable_removes_stale_extensions(
    stable_test_dir: Path,
    case: Case,
) -> None:
    sandbox = make_sandbox(stable_test_dir, case, conan_workspace=True)
    environment = sandbox.sync()

    initial = sandbox.probe(environment, editable=True)
    extension = Path(initial["nanobind_file"])
    stale = extension.with_name(f"{case.native}.obsolete-abi.so")
    shutil.copy2(extension, stale)
    assert stale.is_file()

    sandbox.sync()
    assert not stale.exists()

    updated = sandbox.probe(environment, editable=True)
    sandbox.assert_workspace_provenance(updated)


def test_conan_python_test_failure_propagates(
    stable_test_dir: Path,
) -> None:
    case = next(case for case in CASES if case.native == "ex_cpp_executable")
    sandbox = make_sandbox(stable_test_dir, case, conan_workspace=False)

    test_file = sandbox.root / case.native / "tests" / "test_native.py"
    content = test_file.read_text(encoding="utf-8")
    assert "assert value > 0" in content
    write(
        test_file,
        content.replace(
            "assert value > 0",
            'assert False, "EX_NATIVE_FORCED_FAILURE"',
        ),
    )

    with pytest.raises(subprocess.CalledProcessError) as failure:
        sandbox.create_native()

    output = (failure.value.stdout or "") + (failure.value.stderr or "")
    assert "EX_NATIVE_FORCED_FAILURE" in output


def test_uv_python_test_failure_propagates(
    stable_test_dir: Path,
) -> None:
    case = next(case for case in CASES if case.native == "ex_cpp_executable")
    sandbox = make_sandbox(stable_test_dir, case, conan_workspace=True)

    write(
        sandbox.python_project / "tests" / "test_install.py",
        (
            "def test_forced_failure() -> None:\n"
            '    assert False, "EX_UV_FORCED_FAILURE"\n'
        ),
    )

    with pytest.raises(subprocess.CalledProcessError) as failure:
        sandbox.validate_uv(editable=True)

    output = (failure.value.stdout or "") + (failure.value.stderr or "")
    assert "EX_UV_FORCED_FAILURE" in output


@pytest.mark.parametrize("editable", [True, False], ids=["editable", "wheel"])
def test_clean_python_validation(
    stable_test_dir: Path,
    editable: bool,
) -> None:
    sandbox = make_sandbox(stable_test_dir, None, conan_workspace=False)

    sentinel_directory = stable_test_dir / "forbidden-tools"
    sentinel = sentinel_directory / "conan"
    called = stable_test_dir / "unexpected-conan-call"

    write(
        sentinel,
        (
            "#!/bin/sh\n"
            f"touch {shlex.quote(str(called))}\n"
            'printf "%s\\n" "Unexpected Conan invocation" >&2\n'
            "exit 99\n"
        ),
    )
    sentinel.chmod(0o755)
    sandbox.environment["PATH"] = f"{sentinel_directory}:{sandbox.environment['PATH']}"

    environment = sandbox.validate_uv(editable=editable)
    first = sandbox.probe(environment, editable=editable)
    assert first["version"] == 1

    sandbox.set_version(2)
    environment = sandbox.validate_uv(editable=editable)
    updated = sandbox.probe(environment, editable=editable)

    assert updated["version"] == 2
    assert not called.exists()
