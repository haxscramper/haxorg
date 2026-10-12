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
from pathlib import Path

logger = logging.getLogger("conan_ci")


def run_command(
    arguments: list[str],
    directory: Path,
    environment: dict[str, str],
) -> None:
    logger.info(f"Running command in {directory}: {shlex.join(arguments)}")
    started = time.monotonic()

    subprocess.run(
        arguments,
        cwd=directory,
        env=environment,
        check=True,
    )

    logger.info(
        f"Command completed in {time.monotonic() - started:.2f}s: {shlex.join(arguments)}"
    )


def capture_command(
    arguments: list[str],
    directory: Path,
    environment: dict[str, str],
) -> str:
    logger.info(f"Running command in {directory}: {shlex.join(arguments)}")
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
        f"Command completed in {time.monotonic() - started:.2f}s: {shlex.join(arguments)}"
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
    logger.info(f"Writing Conan server configuration to {configuration_path}")

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
    attempt = 0

    while time.monotonic() < deadline:
        attempt += 1
        return_code = process.poll()

        if return_code is not None:
            raise RuntimeError(
                f"Conan server PID {process.pid} exited with status "
                f"{return_code} before becoming ready at {ping_url}.\n"
                f"{log_path.read_text(encoding='utf-8')}"
            )

        logger.info(f"Checking server readiness at {ping_url}, attempt {attempt}")

        try:
            with urllib.request.urlopen(ping_url, timeout=1.0) as response:
                logger.info(
                    f"Conan server PID {process.pid} is ready: HTTP {response.status}"
                )
                return
        except urllib.error.URLError as error:
            if not isinstance(error.reason, ConnectionRefusedError):
                raise

            logger.info(f"Server is not listening yet at {ping_url}")

        time.sleep(0.5)

    raise TimeoutError(
        f"Conan server PID {process.pid} did not become ready at "
        f"{ping_url} within {timeout}s.\n"
        f"{log_path.read_text(encoding='utf-8')}"
    )


def stop_server(
    process: subprocess.Popen,
    log_path: Path,
    timeout: float,
) -> None:
    return_code = process.poll()

    if return_code is None:
        logger.info(f"Stopping Conan server PID {process.pid}")
        process.terminate()
        return_code = process.wait(timeout=timeout)
        logger.info(f"Conan server PID {process.pid} stopped with status {return_code}")
    else:
        logger.info(
            f"Conan server PID {process.pid} already exited with status {return_code}"
        )

    logger.info(
        f"Conan server log from {log_path}:\n{log_path.read_text(encoding='utf-8')}"
    )


@contextlib.contextmanager
def conan_server_session(
    temporary: Path,
    server_home: Path,
    log_path: Path,
    server_port: int,
    username: str,
    password: str,
    startup_timeout: float,
    shutdown_timeout: float,
    environment: dict[str, str],
) -> Iterator[str]:
    server_url = f"http://127.0.0.1:{server_port}"
    command = ["conan_server", "--server_dir", str(server_home)]
    logger.info(f"Starting server: {shlex.join(command)}; server log={log_path}")

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
    logger.info(f"Wrote Conan default profile {destination} with {version_line}")


def build_package(
    package: str,
    package_directory: Path,
    workspace: Path,
    temporary: Path,
    environment: dict[str, str],
) -> None:
    logger.info(
        f"Preparing package={package}, recipe={package_directory}, "
        f"CONAN_HOME={environment['CONAN_HOME']}"
    )

    if package == "haxorg_conan_base":
        run_command(
            ["conan", "export", str(package_directory)],
            temporary,
            environment,
        )
        return

    profile = workspace / "repo_tool_configs/conan/conanprofile_debug.txt"
    logger.info(f"Using Conan profile {profile}")

    compiler_version = capture_command(
        ["clang", "-dumpversion"],
        temporary,
        environment,
    ).strip()
    compiler_major = compiler_version.split(".", 1)[0]

    logger.info(
        f"Detected Clang version {compiler_version}; "
        f"using Conan compiler.version={compiler_major}"
    )

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

    run_command(["conan", "config", "home"], temporary, environment)
    run_command(["conan", "editable", "list"], temporary, environment)

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

    logger.info(f"Exported current recipe: package={package}, reference={reference}")

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
        binary = node.get("binary")

        if binary is None:
            continue

        logger.info(
            f"Binary availability: node={node_id}, "
            f"reference={node.get('ref')}, "
            f"package_id={node.get('package_id')}, "
            f"package_revision={node.get('prev')}, "
            f"status={binary}, "
            f"remote={json.dumps(node.get('remote'))}, "
            f"binary_remote={json.dumps(node.get('binary_remote'))}"
        )

    logger.info(
        f"Creating and testing {reference}; existing matching binaries "
        f"will be reused, missing binaries will be built"
    )

    run_command(
        [
            "conan",
            "create",
            str(package_directory),
            *arguments,
        ],
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

        if previous_archive.exists():
            logger.info(f"Restoring previous package archive {previous_archive}")
            run_command(
                ["conan", "cache", "restore", str(previous_archive)],
                temporary,
                environment,
            )

    for incoming_package in dict.fromkeys(incoming_packages):
        archive = cache_root / incoming_package / "package.tgz"

        if not archive.is_file():
            raise FileNotFoundError(
                f"Required upstream package archive does not exist: {archive}"
            )

        logger.info(f"Restoring upstream package archive {archive}")
        run_command(
            ["conan", "cache", "restore", str(archive)],
            temporary,
            environment,
        )


def save_package_archive(
    package: str,
    temporary: Path,
    environment: dict[str, str],
) -> None:
    directory = temporary / "conan-package-cache" / package
    directory.mkdir(parents=True, exist_ok=True)
    archive = directory / "package.tgz"

    if archive.exists():
        archive.unlink()

    # The base package only exports a recipe; other packages include binaries.
    pattern = f"{package}/*" if package == "haxorg_conan_base" else f"{package}/*:*"

    run_command(
        [
            "conan",
            "cache",
            "save",
            pattern,
            "--file",
            str(archive),
        ],
        temporary,
        environment,
    )

    logger.info(
        f"Saved package={package}, archive={archive}, bytes={archive.stat().st_size}"
    )


def run_python_package(
    package: str,
    directory: Path,
    environment: dict[str, str],
) -> None:
    run_command(
        ["uv", "python", "install", environment["UV_PYTHON"]],
        directory,
        environment,
    )

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
    package_directory: str,
    python_package: bool,
    incoming_packages: list[str],
    workspace: str,
    temporary_directory: str,
    server_port: int,
    username: str,
    password: str,
    startup_timeout: float,
    shutdown_timeout: float,
) -> None:
    started = time.monotonic()
    repository = Path(os.path.expandvars(workspace))
    temporary = Path(os.path.expandvars(temporary_directory))
    directory = repository / package_directory
    server_home = temporary / "conan-server"
    server_data = server_home / "data"
    conan_home = temporary / "conan-ci"
    log_path = temporary / "conan-server.log"

    environment = os.environ.copy()
    environment["CONAN_HOME"] = str(conan_home)
    environment["PYTHONUNBUFFERED"] = "1"

    logger.info(
        f"Starting package task: package={package}, "
        f"python_package={python_package}, directory={directory}, "
        f"incoming_packages={incoming_packages}"
    )

    for path in (conan_home, server_home):
        if path.exists():
            shutil.rmtree(path)

    conan_home.mkdir(parents=True)
    server_data.mkdir(parents=True)

    compiler_major = (
        capture_command(
            ["clang", "-dumpversion"],
            temporary,
            environment,
        )
        .strip()
        .split(".", 1)[0]
    )

    write_default_profile(
        conan_home,
        repository / "repo_tool_configs/conan/conanprofile_debug.txt",
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
        username,
        password,
    )

    with conan_server_session(
        temporary,
        server_home,
        log_path,
        server_port,
        username,
        password,
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
            ["conan", "remote", "login", "ci", username, "--password", password],
            temporary,
            environment,
        )

        # Populate the server uniformly, including for Python builds that
        # invoke Conan with a separate client cache.
        cached_recipes = json.loads(
            capture_command(
                ["conan", "list", "*", "--format=json"],
                temporary,
                environment,
            )
        )

        if cached_recipes["Local Cache"]:
            run_command(
                ["conan", "upload", "*", "--remote", "ci", "--confirm"],
                temporary,
                environment,
            )

        if python_package:
            run_python_package(package, directory, environment)
        else:
            build_package(
                package,
                directory,
                repository,
                temporary,
                environment,
            )

            run_command(
                ["conan", "upload", "*", "--remote", "ci", "--confirm"],
                temporary,
                environment,
            )

    if not python_package:
        save_package_archive(package, temporary, environment)

    logger.info(f"Package {package} completed in {time.monotonic() - started:.2f}s")


def github_request(
    url: str,
    method: str,
    token: str,
    timeout: float,
) -> http.client.HTTPResponse:
    logger.info(f"GitHub API request: {method} {url}")

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
    repository: str,
    cache_prefix: str,
    cache_key: str,
    ref: str,
    api_url: str,
    token_environment: str,
    request_timeout: float,
) -> None:
    token = os.environ[token_environment]
    endpoint = f"{api_url.rstrip('/')}/repos/{repository}/actions/caches"
    caches = []
    page = 1

    logger.info(
        f"Checking saved cache: repository={repository}, ref={ref}, "
        f"key={cache_key}, eviction prefix={cache_prefix}"
    )

    while True:
        query = urllib.parse.urlencode(
            {"key": cache_prefix, "per_page": 100, "page": page}
        )

        with github_request(
            f"{endpoint}?{query}",
            "GET",
            token,
            request_timeout,
        ) as response:
            batch = json.load(response)["actions_caches"]

        caches.extend(batch)
        logger.info(f"Retrieved cache page {page}: {len(batch)} entries")

        if len(batch) < 100:
            break

        page += 1

    current = [
        cache for cache in caches if cache["key"] == cache_key and cache["ref"] == ref
    ]

    if len(current) != 1:
        visible = [
            {"id": cache["id"], "key": cache["key"], "ref": cache["ref"]}
            for cache in caches
        ]
        raise RuntimeError(
            f"Expected one saved cache for key={cache_key!r}, ref={ref!r}; "
            f"found {len(current)}. Previous entries were not deleted. "
            f"Visible caches: {json.dumps(visible)}"
        )

    retained = current[0]
    logger.info(
        f"Retaining cache id={retained['id']}, key={retained['key']}, "
        f"ref={retained['ref']}, bytes={retained['size_in_bytes']}"
    )

    deleted = 0

    for cache in caches:
        if cache["key"].startswith(cache_prefix) and cache["id"] != retained["id"]:
            logger.info(
                f"Evicting cache id={cache['id']}, key={cache['key']}, "
                f"ref={cache['ref']}, bytes={cache['size_in_bytes']}"
            )

            with github_request(
                f"{endpoint}/{cache['id']}",
                "DELETE",
                token,
                request_timeout,
            ) as response:
                logger.info(f"Deleted cache id={cache['id']}: HTTP {response.status}")

            deleted += 1

    logger.info(
        f"Cache replacement completed: retained={retained['id']}, deleted={deleted}"
    )


def main() -> None:
    logging.basicConfig(
        level=logging.INFO,
        format=("%(asctime)s %(levelname)s %(name)s %(funcName)s:%(lineno)d %(message)s"),
        stream=sys.stdout,
    )

    name, payload = sys.argv[1:]
    logger.info(f"Dispatching CI action {name}")
    globals()[name](**json.loads(payload))


if __name__ == "__main__":
    main()
