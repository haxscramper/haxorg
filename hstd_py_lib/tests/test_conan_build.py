import enum
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
from beartype import beartype
from loguru import logger


class ExPackage(enum.Enum):
    PyStandalone = "ex_py_standalone"
    PyNeedBinary = "ex_py_need_binary"
    PyNeedNanobind = "ex_py_need_nanobind"
    PyFinalDownstream = "ex_py_final_downstream"
    CppLibrary = "ex_cpp_library"
    CppBinary = "ex_cpp_binary"
    CppNanobind = "ex_cpp_nanobind"


REPOSITORY = Path(__file__).resolve().parents[2]
ASSETS = Path(__file__).with_suffix("")
PROFILE = REPOSITORY / "repo_tool_configs/conan/conanprofile_debug.txt"
UV_VALIDATOR = REPOSITORY / "repo_ci_config/py_ci/test_uv_install.py"

PYTHON_DEPENDENCIES: dict[ExPackage, tuple[ExPackage, ...]] = {
    ExPackage.PyStandalone: (),
    ExPackage.PyNeedBinary: (),
    ExPackage.PyNeedNanobind: (),
    ExPackage.PyFinalDownstream: (
        ExPackage.PyStandalone,
        ExPackage.PyNeedBinary,
        ExPackage.PyNeedNanobind,
    ),
}

NATIVE_DEPENDENCIES: dict[ExPackage, tuple[ExPackage, ...]] = {
    ExPackage.CppLibrary: (),
    ExPackage.CppBinary: (ExPackage.CppLibrary,),
    ExPackage.CppNanobind: (ExPackage.CppLibrary,),
}

PYTHON_NATIVE_DEPENDENCIES: dict[ExPackage, tuple[ExPackage, ...]] = {
    ExPackage.PyStandalone: (),
    ExPackage.PyNeedBinary: (ExPackage.CppBinary,),
    ExPackage.PyNeedNanobind: (ExPackage.CppNanobind,),
    ExPackage.PyFinalDownstream: (),
}

NATIVE_ORDER = (
    ExPackage.CppLibrary,
    ExPackage.CppBinary,
    ExPackage.CppNanobind,
)

PYTHON_ORDER = (
    ExPackage.PyStandalone,
    ExPackage.PyNeedBinary,
    ExPackage.PyNeedNanobind,
    ExPackage.PyFinalDownstream,
)

BACKED_PYTHON = (
    ExPackage.PyNeedBinary,
    ExPackage.PyNeedNanobind,
    ExPackage.PyFinalDownstream,
)

PYTHON_PACKAGES = (*BACKED_PYTHON, ExPackage.PyStandalone)
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


@beartype
def write(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content, encoding="utf-8")


@beartype
def write_toml(path: Path, data: dict) -> None:
    write(path, tomli_w.dumps(data))


@beartype
def replace_once(path: Path, old: str, new: str) -> None:
    content = path.read_text(encoding="utf-8")
    assert content.count(old) == 1, (path, old)
    write(path, content.replace(old, new, 1))


@beartype
def closure(
    names: set[ExPackage],
    dependencies: dict[ExPackage, tuple[ExPackage, ...]],
) -> set[ExPackage]:
    result = set(names)

    while True:
        expanded = result | {
            dependency for name in result for dependency in dependencies[name]
        }

        if expanded == result:
            return result

        result = expanded


@beartype
def normalized_name(name: str) -> str:
    return re.sub(r"[-_.]+", "-", name).lower()


@beartype
def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


@beartype
def one_file(paths: list[Path]) -> Path:
    files = sorted({path.resolve() for path in paths if path.is_file()})
    assert len(files) == 1, f"Expected one file, found {len(files)}: {files}"
    return files[0]


@beartype
@dataclass(frozen=True)
class FileFingerprint:
    modified_ns: int
    sha256: str


@beartype
def fingerprint(path: Path) -> FileFingerprint:
    return FileFingerprint(
        modified_ns=path.stat().st_mtime_ns,
        sha256=digest(path),
    )


class BuildStage(enum.Enum):
    Build = 0
    Link = 1


BuildEvent = tuple[BuildStage, ExPackage | None, str]

ANSI_ESCAPE = re.compile(r"\x1b\[[0-?]*[ -/]*[@-~]")

BUILD_ACTION = re.compile(
    r"\b(?:"
    r"Building (?:C|CXX) object (?P<object>[^\r\n]+)"
    r"|"
    r"Linking (?:C|CXX) "
    r"(?:static library|shared library|shared module|executable) "
    r"(?P<link>[^\r\n]+)"
    r")"
)


@beartype
def build_events(output: str, with_external: bool = False) -> set[BuildEvent]:
    output = ANSI_ESCAPE.sub("", output)
    events = set()

    native = "|".join(n.value for n in NATIVE_ORDER)

    for match in BUILD_ACTION.finditer(output):
        object_path = match.group("object")

        if object_path is not None:
            path = object_path.strip().replace("\\", "/").removesuffix(".o")
            if match := re.match(
                f"^CMakeFiles/({native}).dir/src/(?:{native})/(.*)$", path
            ):
                events.add((BuildStage.Build, ExPackage(match[1]), match[2]))
            elif with_external:
                events.add((BuildStage.Build, None, path))

        else:
            path = match.group("link").strip().replace("\\", "/")
            events.add((BuildStage.Link, None, Path(path).name))

    return events


@beartype
@dataclass
class ProbeReport:
    version: int
    packages: dict[str, str]

    executable_file: str | None = None
    nanobind_file: str | None = None

    binary_protobuf_file: str | None = None
    binary_revision_field: bool | None = None
    binary_shared_label: str | None = None

    nanobind_protobuf_file: str | None = None
    nanobind_shared_label: str | None = None
    nanobind_revision_field: bool | None = None


@beartype
@dataclass
class Sandbox:
    directory: Path
    root: Path
    environment: dict[str, str]
    python_packages: tuple[ExPackage, ...]
    native_packages: tuple[ExPackage, ...]
    members: tuple[str, ...]
    last_build_output: str = ""

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

        result = plumbum.local[command[0]][command[1:]].run(
            cwd=str(self.root if cwd is None else cwd),
            env=actual_environment,
        )

        logger.debug(f"{command}")
        # logger.debug(f"stdout:\n{result[0]}")
        # logger.debug(f"stderr:\n{result[1]}")

        return result

    def conan_arguments(self, root: Path | None = None) -> list[str]:
        return [
            "--profile:all",
            str(PROFILE),
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
        target: ExPackage,
        *,
        editable: bool,
        root: Path | None = None,
        environment_name: str = "workspace",
    ) -> Path:
        root = self.root if root is None else root
        environment_path = self.directory / "environments" / environment_name

        command = [
            "uv",
            "-vv",
            "sync",
            "--project",
            str(root),
            "--package",
            target.value,
            "--group",
            "dev",
            *self.reinstall_arguments(root),
        ]

        if not editable:
            command.append("--no-editable")

        _, stdout, stderr = self.run(
            command,
            cwd=root,
            environment={"UV_PROJECT_ENVIRONMENT": str(environment_path)},
        )

        self.last_build_output = stdout + "\n" + stderr

        return environment_path

    def validate_uv(self, target: ExPackage, *, editable: bool) -> Path:
        environment_path = self.directory / "environments" / "validation"
        command = [
            sys.executable,
            str(UV_VALIDATOR),
            str(self.root / target.value),
            "--conan-profile",
            str(PROFILE),
        ]

        if editable:
            command.append("--editable")

        _, stdout, stderr = self.run(
            command,
            environment={
                "HAXORG_PY_TEST_UV_INSTALL_DIR_OVERRIDE": str(environment_path),
                "HSTD_PY_TEST_UV_INSTALL_UV_FLAGS": json.dumps(["-vv"]),
            },
        )
        self.last_build_output = stdout + "\n" + stderr

        return environment_path

    def probe(
        self,
        environment_path: Path,
        target: ExPackage,
        *,
        editable: bool,
        root: Path | None = None,
    ) -> ProbeReport:
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
                "EX_PROBE_PACKAGE": target.value,
                "PATH": f"{environment_path / 'bin'}:{self.environment['PATH']}",
            },
        )

        reports = [
            json.loads(line.removeprefix("EX_PROBE="))
            for line in stdout.splitlines()
            if line.startswith("EX_PROBE=")
        ]
        assert len(reports) == 1, stdout
        report = ProbeReport(**reports[0])

        assert report.version == int(self.environment["EX_EXPECTED_VERSION"])

        for package_name, filename in report.packages.items():
            name = ExPackage(package_name)
            installed = Path(filename).resolve()
            source = (root / name.value / "src").resolve()

            assert installed.is_relative_to(source) is editable, (
                name,
                installed,
                source,
            )

            if not editable:
                assert installed.is_relative_to(environment_path.resolve())

        artifacts = [
            (report.executable_file, None),
            (report.nanobind_file, ExPackage.PyNeedNanobind),
            (report.binary_protobuf_file, ExPackage.PyNeedBinary),
            (report.nanobind_protobuf_file, ExPackage.PyNeedNanobind),
        ]

        for filename, package in artifacts:
            if filename is None:
                continue

            artifact = Path(filename).resolve()
            assert artifact.is_file()

            if package is None or not editable:
                assert artifact.is_relative_to(environment_path.resolve())
            else:
                assert artifact.is_relative_to((root / package.value / "src").resolve())

        return report

    def workspace_outputs(self) -> dict[ExPackage, Path]:
        roots = [self.root / "build"]
        roots.extend(self.root / name.value for name in self.native_packages)
        patterns = {
            ExPackage.CppLibrary: f"lib{ExPackage.CppLibrary.value}.a",
            ExPackage.CppBinary: ExPackage.CppBinary.value,
            ExPackage.CppNanobind: f"{ExPackage.CppNanobind.value}*.so",
        }

        return {
            name: one_file(
                [path for root in roots for path in root.rglob(patterns[name])]
            )
            for name in self.native_packages
        }

    def workspace_fingerprints(self) -> dict[ExPackage, FileFingerprint]:
        return {
            name: fingerprint(path) for name, path in self.workspace_outputs().items()
        }

    def assert_workspace_artifacts_match(self, report: ProbeReport) -> None:
        outputs = self.workspace_outputs()

        for filename, native in (
            (report.executable_file, ExPackage.CppBinary),
            (report.nanobind_file, ExPackage.CppNanobind),
        ):
            if filename is not None:
                assert digest(Path(filename)) == digest(outputs[native])

    def create_native(self) -> None:
        assert not (self.root / "conanws.yml").exists()

        for name in self.native_packages:
            _, stdout, stderr = self.run(
                [
                    "conan",
                    "create",
                    str(self.root / name.value),
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
            marker = f"EX_CONAN_TEST_PACKAGE:{name.value}:{expected}"
            assert marker in output, output

            if name in (ExPackage.CppLibrary, ExPackage.CppBinary):
                assert "100% tests passed" in output, output

            if name == ExPackage.CppBinary:
                assert f"EX_NATIVE_PYTEST:{name.value}:{expected}" in output, output

    def cached_package_folder(self, name: ExPackage, root: Path) -> Path:
        reference = f"{name.value}/0.1.0"
        _, stdout, _ = self.run(
            [
                "conan",
                "graph",
                "info",
                f"--requires={reference}",
                "--format=json",
                *self.conan_arguments(root),
            ],
            cwd=root,
        )

        graph = json.loads(stdout)
        nodes = [
            node
            for node in graph["graph"]["nodes"].values()
            if str(node.get("ref", "")).split("#", maxsplit=1)[0] == reference
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

    def assert_cached_artifacts_match(self, report: ProbeReport, root: Path) -> None:
        folders = {
            name: self.cached_package_folder(name, root) for name in self.native_packages
        }

        if report.executable_file is not None:
            assert digest(Path(report.executable_file)) == digest(
                folders[ExPackage.CppBinary] / "bin" / ExPackage.CppBinary.value
            )

        if report.nanobind_file is not None:
            extension = one_file(
                list(
                    (folders[ExPackage.CppNanobind] / "lib").glob(
                        f"{ExPackage.CppNanobind.value}*.so"
                    )
                )
            )
            assert digest(Path(report.nanobind_file)) == digest(extension)

        for name, filename in (
            (ExPackage.CppLibrary, "shared.proto"),
            (ExPackage.CppBinary, "api.proto"),
        ):
            if name not in folders:
                continue

            cached = folders[name] / "proto" / name.value / filename
            source = self.root / name.value / "proto" / name.value / filename
            assert cached.read_bytes() == source.read_bytes()

    def update_sources(self) -> None:
        assert self.environment["EX_EXPECTED_VERSION"] == "1"

        if ExPackage.CppLibrary in self.native_packages:
            name = ExPackage.CppLibrary
            replace_once(
                self.root / name.value / "src" / name.value / "value.cpp",
                "return 1;",
                "return 2;",
            )
            replace_once(
                self.root / name.value / "proto" / name.value / "shared.proto",
                "  string label = 1;",
                "  string label = 1;\n  int32 revision = 2;",
            )

        if ExPackage.CppBinary in self.native_packages:
            name = ExPackage.CppBinary
            replace_once(
                self.root / name.value / "proto" / name.value / "api.proto",
                "  google.protobuf.Struct metadata = 3;",
                "  google.protobuf.Struct metadata = 3;\n  int32 revision = 4;",
            )

        if ExPackage.PyStandalone in self.python_packages:
            name = ExPackage.PyStandalone
            replace_once(
                self.root / name.value / "src" / name.value / "value.py",
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
                self.root / name.value,
                root / name.value,
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
            members.append(name.value)

        shutil.copytree(
            self.root / "hstd_py_lib",
            root / "hstd_py_lib",
            ignore=COPY_IGNORES,
        )
        members.append("hstd_py_lib")

        write_workspace(root, tuple(members))
        assert not (root / "conanws.yml").exists()

        for name in NATIVE_ORDER:
            assert not (root / name.value).exists()

        return root

    def refresh_downstream_sources(self, root: Path) -> None:
        name = ExPackage.PyStandalone
        source = self.root / name.value / "src" / name.value / "value.py"
        destination = root / name.value / "src" / name.value / "value.py"
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


@beartype
def make_sandbox(
    directory: Path,
    *,
    python_target: ExPackage | None = None,
    native_target: ExPackage | None = None,
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
    selected_native: set[ExPackage] = set()

    for name in selected_python:
        selected_native.update(PYTHON_NATIVE_DEPENDENCIES[name])

    if native_target is not None:
        selected_native.add(native_target)

    selected_native = closure(selected_native, NATIVE_DEPENDENCIES)

    # Conan-hosted binary pytest has a real workspace Python dependency.
    if ExPackage.CppBinary in selected_native:
        selected_python.add(ExPackage.PyStandalone)

    python_packages = tuple(name for name in PYTHON_ORDER if name in selected_python)
    native_packages = tuple(name for name in NATIVE_ORDER if name in selected_native)
    members = [name.value for name in python_packages]

    for name in (*native_packages, *python_packages):
        shutil.copytree(
            ASSETS / name.value,
            root / name.value,
            ignore=COPY_IGNORES,
        )

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

    if ExPackage.CppBinary in native_packages:
        members.append(f"{ExPackage.CppBinary.value}/tests")

    write_workspace(root, tuple(members))

    if conan_workspace:
        assert native_packages
        write(
            root / "conanws.yml",
            json.dumps(
                {
                    "packages": [
                        {
                            "path": name.value,
                            "ref": f"{name.value}/0.1.0",
                            "output_folder": f"build/conan_build/{name.value}",
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
            "HSTD_PY_TEST_UV_INSTALL_UV_FLAGS": json.dumps(["-vv"]),
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
    target: ExPackage,
    editable: bool,
) -> None:
    logger.debug("")
    sandbox = make_sandbox(
        stable_test_dir,
        python_target=target,
        conan_workspace=True,
    )

    Ep = ExPackage

    def get_stage(stage: str) -> tuple[list[tuple[ExPackage, str]], list[str]]:
        res_build = list()
        res_link = list()
        events = build_events(sandbox.last_build_output)
        logger.debug(f"target={target} editable={editable}")
        for e in events:
            logger.debug(f"{stage}: {e}")
            if e[0] == BuildStage.Build and e[1] is not None:
                res_build.append((e[1], e[2]))

            elif e[0] == BuildStage.Link:
                res_link.append(e[2])

        return res_build, res_link

    environment = sandbox.sync(target, editable=editable)
    ev_init, ev_init_link = get_stage("initial")

    nanobind_extension = f"{Ep.CppNanobind.value}{sysconfig.get_config_var('EXT_SUFFIX')}"

    match target:
        case ExPackage.PyNeedBinary:
            assert set(ev_init) == {
                (Ep.CppBinary, "main.cpp"),
                (Ep.CppLibrary, "value.cpp"),
            }, ev_init
            assert set(ev_init_link) == {
                "libex_cpp_library.a",
                Ep.CppBinary.value,
            }, ev_init_link

        case ExPackage.PyNeedNanobind:
            assert set(ev_init) == {
                (Ep.CppNanobind, "module.cpp"),
                (Ep.CppLibrary, "value.cpp"),
            }, ev_init
            assert set(ev_init_link) == {
                "libex_cpp_library.a",
                "libnanobind-static.a",
                nanobind_extension,
            }, ev_init_link

        case ExPackage.PyFinalDownstream:
            assert set(ev_init) == {
                (Ep.CppBinary, "main.cpp"),
                (Ep.CppNanobind, "module.cpp"),
                (Ep.CppLibrary, "value.cpp"),
            }, ev_init
            assert set(ev_init_link) == {
                "libex_cpp_library.a",
                "libnanobind-static.a",
                Ep.CppBinary.value,
                nanobind_extension,
            }, ev_init_link

    initial_report = sandbox.probe(environment, target, editable=editable)
    sandbox.assert_workspace_artifacts_match(initial_report)
    initial_outputs = sandbox.workspace_fingerprints()

    sandbox.sync(target, editable=editable)
    ev_resync, _ = get_stage("resync")

    assert len(ev_resync) == 0

    unchanged_report = sandbox.probe(environment, target, editable=editable)
    sandbox.assert_workspace_artifacts_match(unchanged_report)

    assert unchanged_report == initial_report
    assert sandbox.workspace_fingerprints() == initial_outputs

    sandbox.update_sources()
    sandbox.sync(target, editable=editable)
    ev_edit, ev_edit_link = get_stage("resync")

    match target:
        case ExPackage.PyNeedBinary:
            assert set(ev_edit) == {(Ep.CppLibrary, "value.cpp")}, ev_edit
            assert set(ev_edit_link) == {
                "libex_cpp_library.a",
                Ep.CppBinary.value,
            }, ev_edit_link

        case ExPackage.PyNeedNanobind:
            assert set(ev_edit) == {(Ep.CppLibrary, "value.cpp")}, ev_edit
            assert set(ev_edit_link) == {
                "libex_cpp_library.a",
                nanobind_extension,
            }, ev_edit_link

        case ExPackage.PyFinalDownstream:
            assert set(ev_edit) == {(Ep.CppLibrary, "value.cpp")}, ev_edit
            assert set(ev_edit_link) == {
                "libex_cpp_library.a",
                Ep.CppBinary.value,
                nanobind_extension,
            }, ev_edit_link

    updated_report = sandbox.probe(environment, target, editable=editable)
    sandbox.assert_workspace_artifacts_match(updated_report)

    updated_outputs = sandbox.workspace_fingerprints()

    for name, initial in initial_outputs.items():
        assert updated_outputs[name].sha256 != initial.sha256, name


@pytest.mark.parametrize("target", PYTHON_PACKAGES)
@pytest.mark.parametrize("editable", INSTALL_MODES)
def test_uv_package_validation(
    stable_test_dir: Path,
    target: ExPackage,
    editable: bool,
) -> None:
    sandbox = make_sandbox(
        stable_test_dir,
        python_target=target,
        conan_workspace=target != ExPackage.PyStandalone,
    )

    called = sandbox.directory / "unexpected-conan-call"

    if target == ExPackage.PyStandalone:
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
    initial_report = sandbox.probe(environment, target, editable=editable)

    if sandbox.native_packages:
        sandbox.assert_workspace_artifacts_match(initial_report)

    initial_outputs = sandbox.workspace_fingerprints()

    # The validator recreates its environment and rebuilds Python packages,
    # but unchanged workspace C++ must not compile or link again.
    environment = sandbox.validate_uv(target, editable=editable)
    unchanged_report = sandbox.probe(environment, target, editable=editable)

    if sandbox.native_packages:
        sandbox.assert_workspace_artifacts_match(unchanged_report)

    assert unchanged_report == initial_report
    assert sandbox.workspace_fingerprints() == initial_outputs

    sandbox.update_sources()
    environment = sandbox.validate_uv(target, editable=editable)
    updated_report = sandbox.probe(environment, target, editable=editable)

    if sandbox.native_packages:
        sandbox.assert_workspace_artifacts_match(updated_report)

    updated_outputs = sandbox.workspace_fingerprints()

    for name, initial in initial_outputs.items():
        assert updated_outputs[name].sha256 != initial.sha256, name

    assert not called.exists()


@pytest.mark.parametrize("target", NATIVE_ORDER)
def test_conan_create_validation(
    stable_test_dir: Path,
    target: ExPackage,
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
    target: ExPackage,
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
    sandbox.assert_cached_artifacts_match(report, sandbox.root)

    sandbox.update_sources()
    sandbox.create_native()
    sandbox.sync(target, editable=editable)
    report = sandbox.probe(environment, target, editable=editable)
    sandbox.assert_cached_artifacts_match(report, sandbox.root)


@pytest.mark.parametrize("editable", INSTALL_MODES)
def test_external_downstream(
    stable_test_dir: Path,
    editable: bool,
) -> None:
    target = ExPackage.PyFinalDownstream
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
    sandbox.assert_cached_artifacts_match(report, downstream)

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
    sandbox.assert_cached_artifacts_match(report, downstream)


def test_editable_removes_stale_extensions(stable_test_dir: Path) -> None:
    target = ExPackage.PyNeedNanobind
    sandbox = make_sandbox(
        stable_test_dir,
        python_target=target,
        conan_workspace=True,
    )
    environment = sandbox.sync(target, editable=True)
    report = sandbox.probe(environment, target, editable=True)
    assert report.nanobind_file
    extension = Path(report.nanobind_file)
    stale = extension.with_name(f"{ExPackage.CppNanobind.value}.obsolete-abi.so")
    shutil.copy2(extension, stale)

    sandbox.sync(target, editable=True)
    assert not stale.exists()

    report = sandbox.probe(environment, target, editable=True)
    sandbox.assert_workspace_artifacts_match(report)


def assert_process_failure(
    failure: pytest.ExceptionInfo[plumbum.ProcessExecutionError],
    marker: str,
) -> None:
    output = (failure.value.stdout or "") + (failure.value.stderr or "")
    assert marker in output, output


def test_conan_python_test_failure_propagates(stable_test_dir: Path) -> None:
    target = ExPackage.CppBinary
    sandbox = make_sandbox(
        stable_test_dir,
        native_target=target,
        conan_workspace=False,
    )
    replace_once(
        sandbox.root / target.value / "tests/test_binary.py",
        "assert actual == expected",
        'assert False, "EX_NATIVE_FORCED_FAILURE"',
    )

    with pytest.raises(plumbum.ProcessExecutionError) as failure:
        sandbox.create_native()

    assert_process_failure(failure, "EX_NATIVE_FORCED_FAILURE")


def test_conan_cpp_test_failure_propagates(stable_test_dir: Path) -> None:
    target = ExPackage.CppLibrary
    sandbox = make_sandbox(
        stable_test_dir,
        native_target=target,
        conan_workspace=False,
    )
    replace_once(
        sandbox.root / target.value / "tests/test_value.cpp",
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
    target = ExPackage.PyNeedBinary
    sandbox = make_sandbox(
        stable_test_dir,
        python_target=target,
        conan_workspace=True,
    )
    write(
        sandbox.root / target.value / "tests/test_install.py",
        'def test_forced_failure() -> None:\n    assert False, "EX_UV_FORCED_FAILURE"\n',
    )

    with pytest.raises(plumbum.ProcessExecutionError) as failure:
        sandbox.validate_uv(target, editable=editable)

    assert_process_failure(failure, "EX_UV_FORCED_FAILURE")
