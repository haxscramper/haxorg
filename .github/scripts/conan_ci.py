#!/usr/bin/env python

import configparser
import contextlib
import http.client
import json
import logging
import os
import secrets
import shlex
import shutil
import subprocess
import sys
import sysconfig
import time
import urllib.error
import urllib.parse
import urllib.request
from collections.abc import Iterator
from dataclasses import dataclass, field
from pathlib import Path

logger = logging.getLogger("conan_ci")

CACHE_VERSION = "conan-package-v3"

CI_CONAN_PACKAGES = {
    "haxorg_conan_base",
    "protovalidate-cc",
    "hstd_cpp_lib",
    "hstd_cpp_text_layout",
    "haxorg_cpp_org_lib",
    "haxorg_cpp_py_wrap",
}

CACHE_CLIENT = """
import fs from "node:fs";
import * as cache from "@actions/cache";

async function main() {
    const payload = JSON.parse(process.env.CONAN_CACHE_PAYLOAD);
    let result;

    if (payload.operation === "restore") {
        result = await cache.restoreCache(
            [payload.directory],
            payload.key,
            [payload.prefix],
        );
    } else if (payload.operation === "save") {
        result = await cache.saveCache(
            [payload.directory],
            payload.key,
        );

        if (result < 0) {
            throw new Error(`Cache save failed for ${payload.key}`);
        }
    } else {
        throw new Error(`Unknown cache operation: ${payload.operation}`);
    }

    fs.writeFileSync(
        payload.result_path,
        JSON.stringify({result: result ?? null}),
    );
}

main().catch((error) => {
    console.error(error);
    process.exitCode = 1;
});
"""


def run_command(
    arguments: list[str],
    directory: Path,
    environment: dict[str, str],
) -> None:
    logger.info("Running command in %s: %s", directory, shlex.join(arguments))
    started = time.monotonic()

    subprocess.run(
        arguments,
        cwd=directory,
        env=environment,
        check=True,
    )

    logger.info(
        "Command completed in %.2fs: %s",
        time.monotonic() - started,
        shlex.join(arguments),
    )


def capture_command(
    arguments: list[str],
    directory: Path,
    environment: dict[str, str],
) -> str:
    logger.info("Running command in %s: %s", directory, shlex.join(arguments))
    started = time.monotonic()

    result = subprocess.run(
        arguments,
        cwd=directory,
        env=environment,
        stdout=subprocess.PIPE,
        text=True,
        check=True,
    )

    logger.info(
        "Command completed in %.2fs: %s",
        time.monotonic() - started,
        shlex.join(arguments),
    )

    return result.stdout


def write_server_configuration(
    server_home: Path,
    server_data: Path,
    port: int,
    username: str,
    password: str,
) -> None:
    configuration = configparser.ConfigParser(interpolation=None)
    configuration["server"] = {
        "jwt_secret": secrets.token_hex(32),
        "jwt_expire_minutes": "1440",
        "ssl_enabled": "False",
        "port": str(port),
        "public_port": str(port),
        "host_name": "127.0.0.1",
        "authorize_timeout": "86400",
        "disk_storage_path": str(server_data),
        "disk_storage_adapter": "",
        "updown_secret": secrets.token_hex(32),
    }
    configuration["write_permissions"] = {"*/*@*/*": username}
    configuration["read_permissions"] = {"*/*@*/*": "*"}
    configuration["users"] = {username: password}

    configuration_path = server_home / "server.conf"

    with configuration_path.open("w", encoding="utf-8") as stream:
        configuration.write(stream)


def wait_for_server(
    process: subprocess.Popen,
    server_url: str,
    log_path: Path,
    timeout: float,
) -> None:
    ping_url = f"{server_url}/v1/ping"
    deadline = time.monotonic() + timeout

    while time.monotonic() < deadline:
        return_code = process.poll()

        if return_code is not None:
            raise RuntimeError(
                f"Conan server exited with status {return_code} before "
                f"becoming ready at {ping_url}.\n"
                f"{log_path.read_text(encoding='utf-8')}"
            )

        try:
            with urllib.request.urlopen(ping_url, timeout=1.0) as response:
                logger.info("Conan server is ready: HTTP %s", response.status)
                return
        except urllib.error.URLError as error:
            if not isinstance(error.reason, ConnectionRefusedError):
                raise

        time.sleep(0.5)

    raise TimeoutError(
        f"Conan server did not become ready at {ping_url} within {timeout}s.\n"
        f"{log_path.read_text(encoding='utf-8')}"
    )


def stop_server(
    process: subprocess.Popen,
    log_path: Path,
    timeout: float,
) -> None:
    if process.poll() is None:
        logger.info("Stopping Conan server PID %s", process.pid)
        process.terminate()
        process.wait(timeout=timeout)

    logger.info(
        "Conan server log from %s:\n%s",
        log_path,
        log_path.read_text(encoding="utf-8"),
    )


@contextlib.contextmanager
def conan_server_session(
    temporary: Path,
    server_home: Path,
    log_path: Path,
    server_port: int,
    startup_timeout: float,
    shutdown_timeout: float,
    environment: dict[str, str],
) -> Iterator[str]:
    server_url = f"http://127.0.0.1:{server_port}"
    command = ["conan_server", "--server_dir", str(server_home)]

    logger.info("Starting server: %s", shlex.join(command))

    with log_path.open("w", encoding="utf-8") as stream:
        process = subprocess.Popen(
            command,
            cwd=temporary,
            env=environment,
            stdin=subprocess.DEVNULL,
            stdout=stream,
            stderr=subprocess.STDOUT,
        )

        try:
            wait_for_server(process, server_url, log_path, startup_timeout)
            yield server_url
        finally:
            stop_server(process, log_path, shutdown_timeout)


def write_default_profile(
    conan_home: Path,
    profile: Path,
    compiler_major: str,
) -> None:
    lines = profile.read_text(encoding="utf-8").splitlines()
    output: list[str] = []
    settings = False
    replaced = False
    version_line = f"compiler.version={compiler_major}"

    for line in lines:
        stripped = line.strip()
        section = stripped.startswith("[") and stripped.endswith("]")

        if section and settings and not replaced:
            output.append(version_line)
            replaced = True

        if section:
            settings = stripped == "[settings]"

        if settings and stripped.startswith("compiler.version="):
            output.append(version_line)
            replaced = True
            continue

        output.append(line)

    if not replaced:
        if settings:
            output.append(version_line)
        else:
            output.extend(["", "[settings]", version_line])

    destination = conan_home / "profiles" / "default"
    destination.parent.mkdir(parents=True, exist_ok=True)
    destination.write_text("\n".join(output) + "\n", encoding="utf-8")


def build_package(
    package: str,
    package_directory: Path,
    workspace: Path,
    temporary: Path,
    compiler_major: str,
    environment: dict[str, str],
) -> None:
    if package == "haxorg_conan_base":
        run_command(
            ["conan", "export", str(package_directory)],
            temporary,
            environment,
        )
        return

    profile = workspace / "repo_tool_configs/conan/conanprofile_debug.txt"

    arguments = [
        "-pr:a",
        str(profile),
        "-s:a",
        f"compiler.version={compiler_major}",
        "-c:a",
        'tools.build:compiler_executables={"c":"clang","cpp":"clang++"}',
        "-c:a",
        "tools.build:skip_test=False",
        "-o:a",
        "hstd_cpp_lib/*:with_perfetto=False",
        "-o:a",
        "hstd_cpp_lib/*:with_protovalidate=True",
        "-o:a",
        "haxorg_cpp_org_lib/*:with_perfetto=False",
        "-o:a",
        "haxorg_cpp_org_lib/*:with_protovalidate=True",
        "-c:a",
        'protovalidate-cc/*:tools.cmake:configure_args=["--debug-trycompile"]',
        "--build=missing",
    ]

    if package == "haxorg_cpp_py_wrap":
        arguments.extend(
            [
                "-c:a",
                f"user.haxorg:python_executable={sys.executable}",
                "-c:a",
                f"user.haxorg:python_abi={sysconfig.get_config_var('SOABI')}",
            ]
        )

    exported = json.loads(
        capture_command(
            [
                "conan",
                "export",
                str(package_directory),
                "--format=json",
            ],
            temporary,
            environment,
        )
    )
    reference = exported["reference"]

    graph = json.loads(
        capture_command(
            [
                "conan",
                "graph",
                "info",
                f"--requires={reference}",
                *arguments,
                "--format=json",
            ],
            temporary,
            environment,
        )
    )

    for node_id, node in graph["graph"]["nodes"].items():
        if node.get("binary") is None:
            continue

        logger.info(
            "Binary availability: node=%s, reference=%s, package_id=%s, "
            "package_revision=%s, status=%s, remote=%s, binary_remote=%s",
            node_id,
            node.get("ref"),
            node.get("package_id"),
            node.get("prev"),
            node.get("binary"),
            node.get("remote"),
            node.get("binary_remote"),
        )

    run_command(
        ["conan", "create", str(package_directory), *arguments],
        temporary,
        environment,
    )


def restore_package_archives(
    package: str,
    python_package: bool,
    incoming_packages: list[str],
    temporary: Path,
    environment: dict[str, str],
) -> None:
    cache_root = temporary / "conan-package-cache"

    if not python_package:
        previous_archive = cache_root / package / "package.tgz"

        if previous_archive.is_file():
            run_command(
                ["conan", "cache", "restore", str(previous_archive)],
                temporary,
                environment,
            )

            # Only an archive produced by this invocation may subsequently
            # be published. Do not mistake a restored archive for a new one.
            previous_archive.unlink()

    for incoming_package in dict.fromkeys(incoming_packages):
        archive = cache_root / incoming_package / "package.tgz"

        if not archive.is_file():
            raise FileNotFoundError(
                f"Required upstream package archive does not exist: {archive}"
            )

        run_command(
            ["conan", "cache", "restore", str(archive)],
            temporary,
            environment,
        )


def read_package_list(
    temporary: Path,
    environment: dict[str, str],
) -> dict:
    # Include recipe-only packages, such as haxorg_conan_base, as well as
    # all completed package revisions available in the client cache.
    recipes = json.loads(
        capture_command(
            ["conan", "list", "*#*", "--format=json"],
            temporary,
            environment,
        )
    )
    binaries = json.loads(
        capture_command(
            ["conan", "list", "*#*:*#*", "--format=json"],
            temporary,
            environment,
        )
    )

    local_cache = recipes["Local Cache"]

    for reference, contents in binaries["Local Cache"].items():
        entry = local_cache.setdefault(reference, {"revisions": {}})

        for revision, revision_contents in contents["revisions"].items():
            entry["revisions"].setdefault(revision, {}).update(revision_contents)

    return recipes


def upload_package_list(
    package_list: dict,
    list_path: Path,
    temporary: Path,
    environment: dict[str, str],
) -> None:
    if not package_list["Local Cache"]:
        return

    list_path.write_text(
        json.dumps(package_list, indent=2) + "\n",
        encoding="utf-8",
    )

    run_command(
        [
            "conan",
            "upload",
            "--list",
            str(list_path),
            "--remote",
            "ci",
            "--confirm",
        ],
        temporary,
        environment,
    )


def upload_restored_dependencies(
    package: str,
    temporary: Path,
    environment: dict[str, str],
) -> None:
    package_list = read_package_list(temporary, environment)
    local_cache = package_list["Local Cache"]

    # Do not upload the package being tested before its tests pass.
    # Upstream repository packages have already passed their own CI tasks.
    for reference in list(local_cache):
        if reference.split("/", 1)[0] == package:
            del local_cache[reference]

    upload_package_list(
        package_list,
        temporary / "conan-restored-upload-list.json",
        temporary,
        environment,
    )


def save_package_archive(
    package: str,
    include_package: bool,
    temporary: Path,
    environment: dict[str, str],
) -> dict:
    directory = temporary / "conan-package-cache" / package
    directory.mkdir(parents=True, exist_ok=True)
    archive = directory / "package.tgz"

    if archive.exists():
        archive.unlink()

    package_list = read_package_list(temporary, environment)
    local_cache = package_list["Local Cache"]

    for reference in list(local_cache):
        name = reference.split("/", 1)[0]

        if name in CI_CONAN_PACKAGES:
            if name != package or not include_package:
                del local_cache[reference]

    # On failure this contains only third-party dependencies, never the
    # failing repository package or any other repository package.
    if not local_cache:
        logger.info(
            "Nothing to archive for package=%s, include_package=%s",
            package,
            include_package,
        )
        return package_list

    list_path = directory / "package-list.json"
    list_path.write_text(
        json.dumps(package_list, indent=2) + "\n",
        encoding="utf-8",
    )

    run_command(
        [
            "conan",
            "cache",
            "save",
            "--list",
            str(list_path),
            "--file",
            str(archive),
        ],
        temporary,
        environment,
    )

    logger.info(
        "Saved package=%s, include_package=%s, archive=%s, bytes=%s",
        package,
        include_package,
        archive,
        archive.stat().st_size,
    )

    return package_list


def run_python_package(
    package: str,
    directory: Path,
    environment: dict[str, str],
) -> None:
    run_command(
        ["uv", "build", "-vv", f"--package={package}"],
        directory,
        environment,
    )

    run_command(
        [
            "uv",
            "run",
            f"--package={package}",
            "pytest",
            "--color=no",
            "-vv",
        ],
        directory,
        environment,
    )


def run_ci_package(
    package: str,
    package_directory: Path,
    python_package: bool,
    incoming_packages: list[str],
    workspace: Path,
    temporary: Path,
    compiler_major: str,
    server_port: int = 9300,
    startup_timeout: float = 60.0,
    shutdown_timeout: float = 30.0,
) -> None:
    started = time.monotonic()
    server_home = temporary / "conan-server"
    server_data = server_home / "data"
    conan_home = temporary / "conan-ci"
    log_path = temporary / "conan-server.log"

    environment = os.environ.copy()
    environment["CONAN_HOME"] = str(conan_home)
    environment["PYTHONUNBUFFERED"] = "1"

    logger.info(
        "Starting package=%s, python_package=%s, directory=%s, upstream=%s",
        package,
        python_package,
        package_directory,
        incoming_packages,
    )

    for path in (conan_home, server_home):
        if path.exists():
            shutil.rmtree(path)

    conan_home.mkdir(parents=True)
    server_data.mkdir(parents=True)

    write_default_profile(
        conan_home,
        workspace / "repo_tool_configs/conan/conanprofile_debug.txt",
        compiler_major,
    )

    restore_package_archives(
        package,
        python_package,
        incoming_packages,
        temporary,
        environment,
    )

    write_server_configuration(
        server_home,
        server_data,
        server_port,
        "ci",
        "ci",
    )

    with conan_server_session(
        temporary,
        server_home,
        log_path,
        server_port,
        startup_timeout,
        shutdown_timeout,
        environment,
    ) as server_url:
        run_command(
            ["conan", "remote", "add", "ci", server_url, "--index", "0"],
            temporary,
            environment,
        )

        run_command(
            ["conan", "remote", "login", "ci", "ci", "--password", "ci"],
            temporary,
            environment,
        )

        upload_restored_dependencies(package, temporary, environment)

        if python_package:
            run_python_package(package, package_directory, environment)
        else:
            try:
                build_package(
                    package,
                    package_directory,
                    workspace,
                    temporary,
                    compiler_major,
                    environment,
                )
            except Exception:
                # A failed create may still leave successfully built
                # third-party dependencies in Conan's client cache.
                #
                # Archive those dependencies before propagating the error.
                # Exclude every repository package, including the failed
                # package even if Conan packaged it before its tests failed.
                dependencies = save_package_archive(
                    package=package,
                    include_package=False,
                    temporary=temporary,
                    environment=environment,
                )

                upload_package_list(
                    dependencies,
                    temporary / "conan-built-upload-list.json",
                    temporary,
                    environment,
                )
                raise
            else:
                verified_packages = save_package_archive(
                    package=package,
                    include_package=True,
                    temporary=temporary,
                    environment=environment,
                )

                upload_package_list(
                    verified_packages,
                    temporary / "conan-built-upload-list.json",
                    temporary,
                    environment,
                )

    logger.info(
        "Package %s completed in %.2fs",
        package,
        time.monotonic() - started,
    )


def github_request(
    url: str,
    method: str,
    token: str,
    timeout: float = 30.0,
) -> http.client.HTTPResponse:
    logger.info("GitHub API request: %s %s", method, url)

    request = urllib.request.Request(
        url,
        method=method,
        headers={
            "Accept": "application/vnd.github+json",
            "Authorization": f"Bearer {token}",
            "X-GitHub-Api-Version": "2022-11-28",
            "User-Agent": "conan-ci",
        },
    )

    return urllib.request.urlopen(request, timeout=timeout)


def evict_previous_caches(
    cache_prefix: str,
    cache_key: str,
) -> None:
    repository = os.environ["GITHUB_REPOSITORY"]
    ref = os.environ["GITHUB_REF"]
    token = os.environ["GH_TOKEN"]
    api_url = os.environ["GITHUB_API_URL"].rstrip("/")
    endpoint = f"{api_url}/repos/{repository}/actions/caches"

    caches = []
    page = 1

    while True:
        query = urllib.parse.urlencode(
            {
                "key": cache_prefix,
                "ref": ref,
                "per_page": 100,
                "page": page,
            }
        )

        with github_request(
            f"{endpoint}?{query}",
            "GET",
            token,
        ) as response:
            batch = json.load(response)["actions_caches"]

        caches.extend(batch)

        if len(batch) < 100:
            break

        page += 1

    current = [
        cache for cache in caches if cache["key"] == cache_key and cache["ref"] == ref
    ]

    if len(current) != 1:
        raise RuntimeError(
            f"Expected one saved cache for key={cache_key!r}, ref={ref!r}; "
            f"found {len(current)}. Previous entries were not deleted."
        )

    retained = current[0]

    for cache in caches:
        if (
            cache["ref"] == ref
            and cache["key"].startswith(cache_prefix)
            and cache["id"] != retained["id"]
        ):
            logger.info(
                "Evicting cache id=%s, key=%s, ref=%s",
                cache["id"],
                cache["key"],
                cache["ref"],
            )

            with github_request(
                f"{endpoint}/{cache['id']}",
                "DELETE",
                token,
            ) as response:
                logger.info(
                    "Deleted cache id=%s: HTTP %s",
                    cache["id"],
                    response.status,
                )


@dataclass
class Pipeline:
    workspace: Path
    temporary: Path
    compiler_major: str
    completed_conan_packages: list[str] = field(default_factory=list)

    def cache_prefix(self, package: str) -> str:
        return f"{CACHE_VERSION}-{package}--"

    def cache_key(self, package: str) -> str:
        run_id = os.environ["GITHUB_RUN_ID"]
        run_attempt = os.environ["GITHUB_RUN_ATTEMPT"]
        return f"{self.cache_prefix(package)}{run_id}-{run_attempt}"

    def cache_operation(
        self,
        operation: str,
        package: str,
    ) -> str | int | None:
        directory = self.temporary / "conan-package-cache" / package
        result_path = self.temporary / "conan-cache-result.json"

        if result_path.exists():
            result_path.unlink()

        environment = os.environ.copy()
        environment["CONAN_CACHE_PAYLOAD"] = json.dumps(
            {
                "operation": operation,
                "directory": str(directory),
                "key": self.cache_key(package),
                "prefix": self.cache_prefix(package),
                "result_path": str(result_path),
            }
        )

        run_command(
            ["node", "--input-type=module", "-e", CACHE_CLIENT],
            self.temporary / "conan-cache-client",
            environment,
        )

        return json.loads(result_path.read_text(encoding="utf-8"))["result"]

    def restore_cache(self, package: str) -> None:
        matched_key = self.cache_operation("restore", package)

        if matched_key is None:
            logger.info("No previous cache for package=%s", package)
            return

        archive = self.temporary / "conan-package-cache" / package / "package.tgz"

        if not archive.is_file():
            raise FileNotFoundError(f"Cache {matched_key} did not contain {archive}")

        logger.info(
            "Restored package=%s from cache=%s",
            package,
            matched_key,
        )

    def publish_cache(self, package: str) -> None:
        archive = self.temporary / "conan-package-cache" / package / "package.tgz"

        if not archive.is_file():
            return

        self.cache_operation("save", package)

        # Preserve the original act behavior: restore/save still run,
        # but eviction through GitHub's repository API does not.
        if os.environ.get("ACT") != "true":
            evict_previous_caches(
                self.cache_prefix(package),
                self.cache_key(package),
            )

    def verify(
        self,
        package: str,
        package_directory: str | None = None,
        python_package: bool = False,
        incoming_packages: list[str] | None = None,
    ) -> None:
        if incoming_packages is None:
            incoming_packages = self.completed_conan_packages.copy()

        for incoming_package in incoming_packages:
            if incoming_package not in self.completed_conan_packages:
                raise RuntimeError(
                    f"Package {package} requires {incoming_package}, "
                    "which has not been verified in this pipeline."
                )

        if not python_package:
            self.restore_cache(package)

        try:
            run_ci_package(
                package=package,
                package_directory=(self.workspace / (package_directory or package)),
                python_package=python_package,
                incoming_packages=incoming_packages,
                workspace=self.workspace,
                temporary=self.temporary,
                compiler_major=self.compiler_major,
            )
        finally:
            # Publish dependency-only archives even when conan create
            # failed. The original failure still propagates afterward.
            if not python_package:
                self.publish_cache(package)

        if not python_package:
            self.completed_conan_packages.append(package)


def run_haxorg_conan_base_ci(pipeline: Pipeline) -> None:
    pipeline.verify("haxorg_conan_base")


def run_protovalidate_cc_ci(pipeline: Pipeline) -> None:
    pipeline.verify(
        "protovalidate-cc",
        package_directory="repo_conan_wraps/protovalidate-cc",
    )


def run_hstd_cpp_lib_ci(pipeline: Pipeline) -> None:
    pipeline.verify("hstd_cpp_lib")


def run_hstd_cpp_text_layout_ci(pipeline: Pipeline) -> None:
    pipeline.verify("hstd_cpp_text_layout")


def run_haxorg_cpp_org_lib_ci(pipeline: Pipeline) -> None:
    pipeline.verify("haxorg_cpp_org_lib")


def run_haxorg_cpp_py_wrap_ci(pipeline: Pipeline) -> None:
    pipeline.verify("haxorg_cpp_py_wrap")


def run_hstd_py_lib_ci(pipeline: Pipeline) -> None:
    pipeline.verify(
        "hstd_py_lib",
        python_package=True,
        incoming_packages=["haxorg_conan_base"],
    )


def run_haxorg_py_lib_ci(pipeline: Pipeline) -> None:
    pipeline.verify(
        "haxorg_py_lib",
        python_package=True,
    )


def run_whole_pipeline(
    workspace: str,
    temporary_directory: str,
) -> None:
    started = time.monotonic()
    repository = Path(os.path.expandvars(workspace)).resolve()
    temporary = Path(os.path.expandvars(temporary_directory)).resolve()
    temporary.mkdir(parents=True, exist_ok=True)

    cache_root = temporary / "conan-package-cache"

    if cache_root.exists():
        shutil.rmtree(cache_root)

    cache_root.mkdir(parents=True)

    compiler_version = capture_command(
        ["clang", "-dumpversion"],
        temporary,
        os.environ.copy(),
    ).strip()
    compiler_major = compiler_version.split(".", 1)[0]

    logger.info(
        "Starting whole pipeline: workspace=%s, compiler=%s",
        repository,
        compiler_version,
    )

    pipeline = Pipeline(
        workspace=repository,
        temporary=temporary,
        compiler_major=compiler_major,
    )

    run_haxorg_conan_base_ci(pipeline)
    run_protovalidate_cc_ci(pipeline)
    run_hstd_cpp_lib_ci(pipeline)
    run_hstd_cpp_text_layout_ci(pipeline)
    run_haxorg_cpp_org_lib_ci(pipeline)
    run_haxorg_cpp_py_wrap_ci(pipeline)
    run_hstd_py_lib_ci(pipeline)
    run_haxorg_py_lib_ci(pipeline)

    logger.info(
        "Whole pipeline completed in %.2fs",
        time.monotonic() - started,
    )


def main() -> None:
    logging.basicConfig(
        level=logging.INFO,
        format=("%(asctime)s %(levelname)s %(name)s %(funcName)s:%(lineno)d %(message)s"),
        stream=sys.stdout,
    )

    name, payload = sys.argv[1:]
    actions = {
        "run_whole_pipeline": run_whole_pipeline,
    }
    actions[name](**json.loads(payload))


if __name__ == "__main__":
    main()
