#!/usr/bin/env python

import configparser
import http.client
import json
import logging
import os
import secrets
import shlex
import shutil
import subprocess
import sys
import time
import urllib.error
import urllib.parse
import urllib.request
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


def preserve_previous_snapshot(temporary_directory: str) -> None:
    temporary = Path(os.path.expandvars(temporary_directory))
    snapshot = temporary / "conan-server-snapshot"
    previous = temporary / "conan-server-previous"

    if previous.exists():
        logger.info(f"Removing previous snapshot staging directory at {previous}")
        shutil.rmtree(previous)

    if snapshot.exists():
        logger.info(f"Moving restored snapshot from {snapshot} to {previous}")
        snapshot.rename(previous)
    else:
        logger.info(f"No previous package snapshot was restored at {snapshot}")


def prepare_storage(
    server_data: Path,
    previous_data: Path,
    incoming_data: Path,
) -> None:
    if server_data.exists():
        logger.info(f"Removing previous server storage at {server_data}")
        shutil.rmtree(server_data)

    logger.info(f"Initializing Conan server storage at {server_data}")
    server_data.mkdir(parents=True)

    if previous_data.exists():
        logger.info(f"Restoring previous package storage from {previous_data}")
        shutil.copytree(previous_data, server_data, dirs_exist_ok=True)
    else:
        logger.info(f"No previous package storage exists at {previous_data}")

    if incoming_data.exists():
        logger.info(f"Applying authoritative upstream storage from {incoming_data}")

        for source in sorted(incoming_data.iterdir()):
            destination = server_data / source.name
            logger.info(f"Replacing upstream storage entry {destination}")

            if destination.is_dir():
                shutil.rmtree(destination)
            elif destination.exists():
                destination.unlink()

            if source.is_dir():
                shutil.copytree(source, destination)
            else:
                shutil.copy2(source, destination)
    else:
        logger.info(f"No upstream storage exists at {incoming_data}")


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


def build_package(
    package: str,
    package_directory: Path,
    workspace: Path,
    temporary: Path,
    environment: dict[str, str],
) -> None:
    logger.info(
        f"Building package={package}, recipe={package_directory}, "
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

    compiler_version = subprocess.check_output(
        ["clang", "-dumpversion"],
        cwd=temporary,
        env=environment,
        text=True,
    ).strip()
    compiler_major = compiler_version.split(".", 1)[0]
    logger.info(
        f"Detected Clang version {compiler_version}; "
        f"using Conan compiler.version={compiler_major}"
    )

    arguments = [
        "conan",
        "create",
        str(package_directory),
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
        f"--build={package}/*",
    ]

    run_command(["conan", "config", "home"], temporary, environment)
    run_command(["conan", "editable", "list"], temporary, environment)
    run_command(arguments, temporary, environment)


def run_package(
    package: str,
    package_directory: str,
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
    recipe = repository / package_directory
    server_home = temporary / "conan-server"
    server_data = server_home / "data"
    snapshot = temporary / "conan-server-snapshot"
    previous = temporary / "conan-server-previous"
    conan_home = temporary / "conan-ci"
    log_path = temporary / "conan-server.log"
    server_url = f"http://127.0.0.1:{server_port}"

    environment = os.environ.copy()
    environment["CONAN_HOME"] = str(conan_home)
    environment["PYTHONUNBUFFERED"] = "1"

    logger.info(
        f"Starting package task: package={package}, recipe={recipe}, "
        f"workspace={repository}, temporary={temporary}, server={server_url}"
    )

    if conan_home.exists():
        logger.info(f"Removing previous job-local Conan cache at {conan_home}")
        shutil.rmtree(conan_home)

    conan_home.mkdir()

    prepare_storage(server_data, previous / "data", snapshot / "data")
    write_server_configuration(
        server_home,
        server_data,
        server_port,
        username,
        password,
    )

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

            run_command(
                ["conan", "remote", "add", "ci", server_url, "--index", "0"],
                temporary,
                environment,
            )
            run_command(
                [
                    "conan",
                    "remote",
                    "login",
                    "ci",
                    username,
                    "--password",
                    password,
                ],
                temporary,
                environment,
            )

            logger.info(f"Removing previous server versions and revisions of {package}")
            run_command(
                [
                    "conan",
                    "remove",
                    f"{package}/*",
                    "--remote",
                    "ci",
                    "--confirm",
                ],
                temporary,
                environment,
            )

            build_package(package, recipe, repository, temporary, environment)

            logger.info(
                f"Uploading successful recipes and binaries for {package} "
                f"and its dependencies to {server_url}"
            )
            run_command(
                ["conan", "upload", "*", "--remote", "ci", "--confirm"],
                temporary,
                environment,
            )
        finally:
            stop_server(process, log_path, shutdown_timeout)

    logger.info(f"Preparing successful server snapshot at {snapshot}")

    if snapshot.exists():
        shutil.rmtree(snapshot)

    snapshot.mkdir()
    shutil.copytree(server_data, snapshot / "data")

    files = 0
    size = 0

    for entry in snapshot.rglob("*"):
        if entry.is_file():
            files += 1
            size += entry.stat().st_size

    logger.info(
        f"Package {package} completed in {time.monotonic() - started:.2f}s; "
        f"snapshot={snapshot}, files={files}, bytes={size}"
    )


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
