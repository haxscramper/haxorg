import hashlib
import json
import os
import re
import shlex
import shutil
import sys
import sysconfig
from dataclasses import dataclass
from pathlib import Path

import plumbum
import pytest
import tomli_w

REPOSITORY = Path(__file__).resolve().parents[2]
ASSETS = Path(__file__).with_suffix("")
PROFILE = REPOSITORY / "repo_tool_configs/conan/conanprofile.txt"
UV_VALIDATOR = REPOSITORY / "repo_ci_config/py_ci/test_uv_install.py"

PYTHON_DEPENDENCIES = {
    "ex_py_standalone": (),
    "ex_py_need_binary": (),
    "ex_py_need_nanobind": (),
    "ex_py_final_downstream": (
        "ex_py_standalone",
        "ex_py_need_binary",
        "ex_py_need_nanobind",
    ),
}

NATIVE_DEPENDENCIES = {
    "ex_cpp_library": (),
    "ex_cpp_binary": ("ex_cpp_library",),
    "ex_cpp_nanobind": ("ex_cpp_library",),
}

PYTHON_NATIVE_DEPENDENCIES = {
    "ex_py_standalone": (),
    "ex_py_need_binary": ("ex_cpp_binary",),
    "ex_py_need_nanobind": ("ex_cpp_nanobind",),
    "ex_py_final_downstream": (),
}

NATIVE_ORDER = (
    "ex_cpp_library",
    "ex_cpp_binary",
    "ex_cpp_nanobind",
)

PYTHON_ORDER = (
    "ex_py_standalone",
    "ex_py_need_binary",
    "ex_py_need_nanobind",
    "ex_py_final_downstream",
)

BACKED_PYTHON = (
    "ex_py_need_binary",
    "ex_py_need_nanobind",
    "ex_py_final_downstream",
)

PYTHON_PACKAGES = (*BACKED_PYTHON, "ex_py_standalone")
INSTALL_MODES = [
    pytest.param(True, id="editable"),
    pytest.param(False, id="non-editable"),
]

COPY_IGNORES = shutil.ignore_patterns(
    "__pycache__",
    ".pytest_cache",
    ".venv",
    "dist",
    "build",
    "*.egg-info",
    "*.so",
)


def write(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content, encoding="utf-8")


def write_toml(path: Path, data: dict) -> None:
    write(path, tomli_w.dumps(data))


def replace_once(path: Path, old: str, new: str) -> None:
    content = path.read_text(encoding="utf-8")
    assert content.count(old) == 1, (path, old)
    write(path, content.replace(old, new, 1))


def closure(names: set[str], dependencies: dict[str, tuple[str, ...]]) -> set[str]:
    result = set(names)

    while True:
        expanded = result | {
            dependency for name in result for dependency in dependencies[name]
        }

        if expanded == result:
            return result

        result = expanded


def normalized_name(name: str) -> str:
    return re.sub(r"[-_.]+", "-", name).lower()


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def one_file(paths: list[Path]) -> Path:
    files = sorted({path.resolve() for path in paths if path.is_file()})
    assert len(files) == 1, f"Expected one file, found {len(files)}: {files}"
    return files[0]


@dataclass(frozen=True)
class FileFingerprint:
    modified_ns: int
    sha256: str


def fingerprint(path: Path) -> FileFingerprint:
    return FileFingerprint(
        modified_ns=path.stat().st_mtime_ns,
        sha256=digest(path),
    )


@dataclass
class Sandbox:
    directory: Path
    root: Path
    environment: dict[str, str]
    python_packages: tuple[str, ...]
    native_packages: tuple[str, ...]
    members: tuple[str, ...]

    def run(
        self,
        command: list[str],
        *,
        cwd: Path | None = None,
        environment: dict[str, str] | None = None,
    ) -> tuple[int, str, str]:
        actual_environment = self.environment.copy()

        if environment is not None:
            actual_environment.update(environment)

        return plumbum.local[command[0]][command[1:]].run(
            cwd=str(self.root if cwd is None else cwd),
            env=actual_environment,
        )

    def conan_arguments(self, root: Path | None = None) -> list[str]:
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
            f"user.haxorg:uv_project={self.root if root is None else root}",
        ]

    def reinstall_arguments(self, root: Path) -> list[str]:
        import tomllib

        with (root / "pyproject.toml").open("rb") as stream:
            configuration = tomllib.load(stream)

        arguments = []

        for member in configuration["tool"]["uv"]["workspace"]["members"]:
            with (root / member / "pyproject.toml").open("rb") as stream:
                metadata = tomllib.load(stream)

            arguments.extend(
                [
                    "--reinstall-package",
                    normalized_name(metadata["project"]["name"]),
                ]
            )

        return arguments

    def sync(
        self,
        target: str,
        *,
        editable: bool,
        root: Path | None = None,
        environment_name: str = "workspace",
    ) -> Path:
        root = self.root if root is None else root
        environment_path = self.directory / "environments" / environment_name

        command = [
            "uv",
            "sync",
            "--project",
            str(root),
            "--package",
            target,
            "--group",
            "dev",
            *self.reinstall_arguments(root),
        ]

        if not editable:
            command.append("--no-editable")

        self.run(
            command,
            cwd=root,
            environment={"UV_PROJECT_ENVIRONMENT": str(environment_path)},
        )

        return environment_path

    def validate_uv(self, target: str, *, editable: bool) -> Path:
        environment_path = self.directory / "environments" / "validation"
        command = [
            sys.executable,
            str(UV_VALIDATOR),
            str(self.root / target),
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
        target: str,
        *,
        editable: bool,
        root: Path | None = None,
    ) -> dict:
        root = self.root if root is None else root
        cwd = self.directory / "empty"
        cwd.mkdir(exist_ok=True)

        _, stdout, _ = self.run(
            [
                str(environment_path / "bin" / "python"),
                str(ASSETS / "probe.py"),
            ],
            cwd=cwd,
            environment={
                "EX_PROBE_PACKAGE": target,
                "PATH": f"{environment_path / 'bin'}:{self.environment['PATH']}",
            },
        )

        reports = [
            json.loads(line.removeprefix("EX_PROBE="))
            for line in stdout.splitlines()
            if line.startswith("EX_PROBE=")
        ]
        assert len(reports) == 1, stdout
        report = reports[0]

        assert report["version"] == int(self.environment["EX_EXPECTED_VERSION"])

        for name, filename in report["packages"].items():
            installed = Path(filename).resolve()
            source = (root / name / "src").resolve()

            assert installed.is_relative_to(source) is editable, (
                name,
                installed,
                source,
            )

            if not editable:
                assert installed.is_relative_to(environment_path.resolve())

        artifact_packages = {
            "executable_file": None,
            "nanobind_file": "ex_py_need_nanobind",
            "binary_protobuf_file": "ex_py_need_binary",
            "nanobind_protobuf_file": "ex_py_need_nanobind",
        }

        for key, package in artifact_packages.items():
            if key not in report:
                continue

            artifact = Path(report[key]).resolve()
            assert artifact.is_file()

            if package is None or not editable:
                assert artifact.is_relative_to(environment_path.resolve())
            else:
                assert artifact.is_relative_to((root / package / "src").resolve())

        return report

    def workspace_outputs(self) -> dict[str, Path]:
        roots = [self.root / "build"]
        roots.extend(self.root / name for name in self.native_packages)
        patterns = {
            "ex_cpp_library": "libex_cpp_library.a",
            "ex_cpp_binary": "ex_cpp_binary",
            "ex_cpp_nanobind": "ex_cpp_nanobind*.so",
        }

        return {
            name: one_file(
                [path for root in roots for path in root.rglob(patterns[name])]
            )
            for name in self.native_packages
        }

    def workspace_fingerprints(self) -> dict[str, FileFingerprint]:
        return {
            name: fingerprint(path) for name, path in self.workspace_outputs().items()
        }

    def assert_workspace_provenance(self, report: dict) -> None:
        outputs = self.workspace_outputs()

        for key, native in (
            ("executable_file", "ex_cpp_binary"),
            ("nanobind_file", "ex_cpp_nanobind"),
        ):
            if key in report:
                assert digest(Path(report[key])) == digest(outputs[native])

    def create_native(self) -> None:
        assert not (self.root / "conanws.yml").exists()

        for name in self.native_packages:
            _, stdout, stderr = self.run(
                [
                    "conan",
                    "create",
                    str(self.root / name),
                    "--build=missing",
                    *self.conan_arguments(),
                    "-c",
                    "tools.build:skip_test=False",
                ],
                environment={
                    "UV_PROJECT_ENVIRONMENT": str(
                        self.directory / "environments" / "native-tests"
                    ),
                },
            )

            output = stdout + stderr
            expected = self.environment["EX_EXPECTED_VERSION"]
            marker = f"EX_CONAN_TEST_PACKAGE:{name}:{expected}"
            assert marker in output, output

            if name in ("ex_cpp_library", "ex_cpp_binary"):
                assert "100% tests passed" in output, output

            if name == "ex_cpp_binary":
                assert f"EX_NATIVE_PYTEST:{name}:{expected}" in output, output

    def cached_package_folder(self, name: str, root: Path) -> Path:
        _, stdout, _ = self.run(
            [
                "conan",
                "graph",
                "info",
                f"--requires={name}/0.1.0",
                "--format=json",
                *self.conan_arguments(root),
            ],
            cwd=root,
        )

        graph = json.loads(stdout)
        nodes = [
            node
            for node in graph["graph"]["nodes"].values()
            if str(node.get("ref", "")).split("#", maxsplit=1)[0] == f"{name}/0.1.0"
        ]
        assert len(nodes) == 1, nodes
        node = nodes[0]

        package_reference = f"{node['ref']}:{node['package_id']}"

        if node.get("prev"):
            package_reference += f"#{node['prev']}"

        _, stdout, _ = self.run(
            ["conan", "cache", "path", package_reference],
            cwd=root,
        )

        folder = Path(stdout.strip()).resolve()
        assert folder.is_dir()
        assert folder.is_relative_to(Path(self.environment["CONAN_HOME"]).resolve())
        return folder

    def assert_cache_provenance(self, report: dict, root: Path) -> None:
        folders = {
            name: self.cached_package_folder(name, root) for name in self.native_packages
        }

        if "executable_file" in report:
            assert digest(Path(report["executable_file"])) == digest(
                folders["ex_cpp_binary"] / "bin" / "ex_cpp_binary"
            )

        if "nanobind_file" in report:
            extension = one_file(
                list((folders["ex_cpp_nanobind"] / "lib").glob("ex_cpp_nanobind*.so"))
            )
            assert digest(Path(report["nanobind_file"])) == digest(extension)

        for name, filename in (
            ("ex_cpp_library", "shared.proto"),
            ("ex_cpp_binary", "api.proto"),
        ):
            if name not in folders:
                continue

            cached = folders[name] / "proto" / name / filename
            source = self.root / name / "proto" / name / filename
            assert cached.read_bytes() == source.read_bytes()

    def update_sources(self) -> None:
        assert self.environment["EX_EXPECTED_VERSION"] == "1"

        if "ex_cpp_library" in self.native_packages:
            replace_once(
                self.root / "ex_cpp_library/src/ex_cpp_library/value.cpp",
                "return 1;",
                "return 2;",
            )
            replace_once(
                self.root / "ex_cpp_library/proto/ex_cpp_library/shared.proto",
                "  string label = 1;",
                "  string label = 1;\n  int32 revision = 2;",
            )

        if "ex_cpp_binary" in self.native_packages:
            replace_once(
                self.root / "ex_cpp_binary/proto/ex_cpp_binary/api.proto",
                "  google.protobuf.Struct metadata = 3;",
                "  google.protobuf.Struct metadata = 3;\n  int32 revision = 4;",
            )

        if "ex_py_standalone" in self.python_packages:
            replace_once(
                self.root / "ex_py_standalone/src/ex_py_standalone/value.py",
                "VALUE = 1",
                "VALUE = 2",
            )

        self.environment["EX_EXPECTED_VERSION"] = "2"

    def make_downstream(self) -> Path:
        root = self.directory / "downstream"
        root.mkdir()

        members = []

        for name in self.python_packages:
            shutil.copytree(
                self.root / name,
                root / name,
                ignore=shutil.ignore_patterns(
                    "__pycache__",
                    ".pytest_cache",
                    ".venv",
                    "dist",
                    "build",
                    "*.egg-info",
                    "*.so",
                    "proto",
                ),
            )
            members.append(name)

        shutil.copytree(
            self.root / "hstd_py_lib",
            root / "hstd_py_lib",
            ignore=COPY_IGNORES,
        )
        members.append("hstd_py_lib")

        write_workspace(root, tuple(members))
        assert not (root / "conanws.yml").exists()

        for name in NATIVE_ORDER:
            assert not (root / name).exists()

        return root

    def refresh_downstream_sources(self, root: Path) -> None:
        source = self.root / "ex_py_standalone/src/ex_py_standalone/value.py"
        destination = root / "ex_py_standalone/src/ex_py_standalone/value.py"
        shutil.copy2(source, destination)


def write_workspace(root: Path, members: tuple[str, ...]) -> None:
    sources = {}

    for member in members:
        if member.endswith("/tests"):
            name = member.removesuffix("/tests") + "_pytest_package"
        else:
            name = member

        sources[name] = {"workspace": True}

    write_toml(
        root / "pyproject.toml",
        {
            "tool": {
                "uv": {
                    "workspace": {"members": list(members)},
                    "sources": sources,
                },
            },
            "dependency-groups": {"dev": ["pytest>=8.4.2"]},
        },
    )


def make_sandbox(
    directory: Path,
    *,
    python_target: str | None = None,
    native_target: str | None = None,
    conan_workspace: bool,
) -> Sandbox:
    directory = Path(str(directory).replace("[", "_").replace("]", "_"))

    if directory.exists():
        shutil.rmtree(directory)

    root = directory / "workspace"
    root.mkdir(parents=True)

    selected_python = (
        closure({python_target}, PYTHON_DEPENDENCIES)
        if python_target is not None
        else set()
    )
    selected_native = set()

    for name in selected_python:
        selected_native.update(PYTHON_NATIVE_DEPENDENCIES[name])

    if native_target is not None:
        selected_native.add(native_target)

    selected_native = closure(selected_native, NATIVE_DEPENDENCIES)

    # Conan-hosted binary pytest has a real workspace Python dependency.
    if "ex_cpp_binary" in selected_native:
        selected_python.add("ex_py_standalone")

    python_packages = tuple(name for name in PYTHON_ORDER if name in selected_python)
    native_packages = tuple(name for name in NATIVE_ORDER if name in selected_native)
    members = list(python_packages)

    for name in (*native_packages, *python_packages):
        shutil.copytree(ASSETS / name, root / name, ignore=COPY_IGNORES)

    if native_packages:
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
                "*.egg-info",
            ),
        )
        members.append("hstd_py_lib")

    if "ex_cpp_binary" in native_packages:
        members.append("ex_cpp_binary/tests")

    write_workspace(root, tuple(members))

    if conan_workspace:
        assert native_packages
        write(
            root / "conanws.yml",
            json.dumps(
                {
                    "packages": [
                        {
                            "path": name,
                            "ref": f"{name}/0.1.0",
                            "output_folder": f"build/conan_build/{name}",
                        }
                        for name in native_packages
                    ],
                },
                indent=2,
            ),
        )

    environment = os.environ.copy()

    for key in (
        "VIRTUAL_ENV",
        "PYTHONPATH",
        "UV_PROJECT_ENVIRONMENT",
        "HAXORG_PY_TEST_UV_INSTALL_DIR_OVERRIDE",
    ):
        environment.pop(key, None)

    environment.update(
        {
            "CONAN_HOME": str(directory / "conan-home"),
            "CONAN_PROFILE": str(PROFILE),
            "UV_CACHE_DIR": str(directory / "uv-cache"),
            "PYTHONNOUSERSITE": "1",
            "HATCH_CONAN_RUN_TESTS": "0",
            "HSTD_PY_PYTEST_EXTRA_ARGS": json.dumps(["-s", "-vv", "--color=no"]),
            "HSTD_PY_TEST_UV_INSTALL_UV_FLAGS": "[]",
            "EX_EXPECTED_VERSION": "1",
            "CC": "clang",
            "CXX": "clang++",
        }
    )

    sandbox = Sandbox(
        directory=directory,
        root=root,
        environment=environment,
        python_packages=python_packages,
        native_packages=native_packages,
        members=tuple(members),
    )

    if native_packages:
        sandbox.run(["conan", "profile", "detect", "--force"])
        sandbox.run(["conan", "export", str(REPOSITORY / "haxorg_conan_base")])

    sandbox.run(["uv", "lock", "--project", str(root)])
    return sandbox


@pytest.mark.parametrize("target", BACKED_PYTHON)
@pytest.mark.parametrize("editable", INSTALL_MODES)
def test_workspace_refresh(
    stable_test_dir: Path,
    target: str,
    editable: bool,
) -> None:
    sandbox = make_sandbox(
        stable_test_dir,
        python_target=target,
        conan_workspace=True,
    )

    environment = sandbox.sync(target, editable=editable)
    initial_report = sandbox.probe(environment, target, editable=editable)
    sandbox.assert_workspace_provenance(initial_report)
    initial_outputs = sandbox.workspace_fingerprints()

    sandbox.sync(target, editable=editable)
    unchanged_report = sandbox.probe(environment, target, editable=editable)
    sandbox.assert_workspace_provenance(unchanged_report)

    assert unchanged_report == initial_report
    assert sandbox.workspace_fingerprints() == initial_outputs

    sandbox.update_sources()
    sandbox.sync(target, editable=editable)
    updated_report = sandbox.probe(environment, target, editable=editable)
    sandbox.assert_workspace_provenance(updated_report)

    updated_outputs = sandbox.workspace_fingerprints()

    for name, initial in initial_outputs.items():
        assert updated_outputs[name].sha256 != initial.sha256, name


@pytest.mark.parametrize("target", PYTHON_PACKAGES)
@pytest.mark.parametrize("editable", INSTALL_MODES)
def test_uv_package_validation(
    stable_test_dir: Path,
    target: str,
    editable: bool,
) -> None:
    sandbox = make_sandbox(
        stable_test_dir,
        python_target=target,
        conan_workspace=target != "ex_py_standalone",
    )

    called = sandbox.directory / "unexpected-conan-call"

    if target == "ex_py_standalone":
        sentinel = sandbox.directory / "forbidden-tools" / "conan"
        write(
            sentinel,
            "#!/bin/sh\n"
            f"touch {shlex.quote(str(called))}\n"
            'printf "%s\\n" "Unexpected Conan invocation" >&2\n'
            "exit 99\n",
        )
        sentinel.chmod(0o755)
        sandbox.environment["PATH"] = f"{sentinel.parent}:{sandbox.environment['PATH']}"

    environment = sandbox.validate_uv(target, editable=editable)
    report = sandbox.probe(environment, target, editable=editable)

    if sandbox.native_packages:
        sandbox.assert_workspace_provenance(report)

    sandbox.update_sources()
    environment = sandbox.validate_uv(target, editable=editable)
    report = sandbox.probe(environment, target, editable=editable)

    if sandbox.native_packages:
        sandbox.assert_workspace_provenance(report)

    assert not called.exists()


@pytest.mark.parametrize("target", NATIVE_ORDER)
def test_conan_create_validation(
    stable_test_dir: Path,
    target: str,
) -> None:
    sandbox = make_sandbox(
        stable_test_dir,
        native_target=target,
        conan_workspace=False,
    )

    sandbox.create_native()
    sandbox.update_sources()
    sandbox.create_native()


@pytest.mark.parametrize("target", BACKED_PYTHON)
@pytest.mark.parametrize("editable", INSTALL_MODES)
def test_cached_package_installation(
    stable_test_dir: Path,
    target: str,
    editable: bool,
) -> None:
    sandbox = make_sandbox(
        stable_test_dir,
        python_target=target,
        conan_workspace=False,
    )

    sandbox.create_native()
    environment = sandbox.sync(target, editable=editable)
    report = sandbox.probe(environment, target, editable=editable)
    sandbox.assert_cache_provenance(report, sandbox.root)

    sandbox.update_sources()
    sandbox.create_native()
    sandbox.sync(target, editable=editable)
    report = sandbox.probe(environment, target, editable=editable)
    sandbox.assert_cache_provenance(report, sandbox.root)


@pytest.mark.parametrize("editable", INSTALL_MODES)
def test_external_downstream(
    stable_test_dir: Path,
    editable: bool,
) -> None:
    target = "ex_py_final_downstream"
    sandbox = make_sandbox(
        stable_test_dir,
        python_target=target,
        conan_workspace=False,
    )

    sandbox.create_native()
    downstream = sandbox.make_downstream()

    environment = sandbox.sync(
        target,
        editable=editable,
        root=downstream,
        environment_name="downstream",
    )
    report = sandbox.probe(
        environment,
        target,
        editable=editable,
        root=downstream,
    )
    sandbox.assert_cache_provenance(report, downstream)

    sandbox.update_sources()
    sandbox.create_native()
    sandbox.refresh_downstream_sources(downstream)

    sandbox.sync(
        target,
        editable=editable,
        root=downstream,
        environment_name="downstream",
    )
    report = sandbox.probe(
        environment,
        target,
        editable=editable,
        root=downstream,
    )
    sandbox.assert_cache_provenance(report, downstream)


def test_editable_removes_stale_extensions(stable_test_dir: Path) -> None:
    target = "ex_py_need_nanobind"
    sandbox = make_sandbox(
        stable_test_dir,
        python_target=target,
        conan_workspace=True,
    )
    environment = sandbox.sync(target, editable=True)
    report = sandbox.probe(environment, target, editable=True)
    extension = Path(report["nanobind_file"])
    stale = extension.with_name("ex_cpp_nanobind.obsolete-abi.so")
    shutil.copy2(extension, stale)

    sandbox.sync(target, editable=True)
    assert not stale.exists()

    report = sandbox.probe(environment, target, editable=True)
    sandbox.assert_workspace_provenance(report)


def assert_process_failure(
    failure: pytest.ExceptionInfo[plumbum.ProcessExecutionError],
    marker: str,
) -> None:
    output = (failure.value.stdout or "") + (failure.value.stderr or "")
    assert marker in output, output


def test_conan_python_test_failure_propagates(stable_test_dir: Path) -> None:
    sandbox = make_sandbox(
        stable_test_dir,
        native_target="ex_cpp_binary",
        conan_workspace=False,
    )
    replace_once(
        sandbox.root / "ex_cpp_binary/tests/test_binary.py",
        "assert actual == expected",
        'assert False, "EX_NATIVE_FORCED_FAILURE"',
    )

    with pytest.raises(plumbum.ProcessExecutionError) as failure:
        sandbox.create_native()

    assert_process_failure(failure, "EX_NATIVE_FORCED_FAILURE")


def test_conan_cpp_test_failure_propagates(stable_test_dir: Path) -> None:
    sandbox = make_sandbox(
        stable_test_dir,
        native_target="ex_cpp_library",
        conan_workspace=False,
    )
    replace_once(
        sandbox.root / "ex_cpp_library/tests/test_value.cpp",
        "return actual == expected ? 0 : 1;",
        'std::cerr << "EX_CTEST_FORCED_FAILURE\\n";\n    return 1;',
    )

    with pytest.raises(plumbum.ProcessExecutionError) as failure:
        sandbox.create_native()

    assert_process_failure(failure, "EX_CTEST_FORCED_FAILURE")


@pytest.mark.parametrize("editable", INSTALL_MODES)
def test_uv_python_test_failure_propagates(
    stable_test_dir: Path,
    editable: bool,
) -> None:
    target = "ex_py_need_binary"
    sandbox = make_sandbox(
        stable_test_dir,
        python_target=target,
        conan_workspace=True,
    )
    write(
        sandbox.root / target / "tests/test_install.py",
        'def test_forced_failure() -> None:\n    assert False, "EX_UV_FORCED_FAILURE"\n',
    )

    with pytest.raises(plumbum.ProcessExecutionError) as failure:
        sandbox.validate_uv(target, editable=editable)

    assert_process_failure(failure, "EX_UV_FORCED_FAILURE")
