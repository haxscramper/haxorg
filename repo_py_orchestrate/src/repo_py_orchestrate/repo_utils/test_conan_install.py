#!/usr/bin/env python

import argparse
import json
import os
import shlex
import shutil
import subprocess
import sys
from pathlib import Path
from typing import TextIO


def run(
    command: list[str],
    *,
    environment: dict[str, str],
    log: TextIO,
) -> str:
    heading = f"$ {shlex.join(command)}\n"
    sys.stdout.write(heading)
    log.write(heading)
    log.flush()

    output: list[str] = []

    with subprocess.Popen(
        command,
        env=environment,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    ) as process:
        assert process.stdout is not None

        for line in process.stdout:
            sys.stdout.write(line)
            sys.stdout.flush()
            log.write(line)
            log.flush()
            output.append(line)

        returncode = process.wait()

    if returncode:
        raise subprocess.CalledProcessError(returncode, command)

    return "".join(output)


def get_reference(target: Path, environment: dict[str, str]) -> str:
    result = subprocess.run(
        ["conan", "inspect", str(target), "--format=json"],
        env=environment,
        stdout=subprocess.PIPE,
        text=True,
        check=True,
    )
    metadata = json.loads(result.stdout)

    name = metadata["name"]
    version = metadata["version"]

    if not name or not version:
        raise ValueError(f"{target}: recipe must define name and version")

    reference = f"{name}/{version}"
    user = metadata.get("user")
    channel = metadata.get("channel")

    if user or channel:
        if not user or not channel:
            raise ValueError(f"{target}: user and channel must both be defined")
        reference += f"@{user}/{channel}"

    return reference


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("target", type=Path)
    parser.add_argument(
        "--editable",
        action=argparse.BooleanOptionalAction,
        default=False,
    )
    parser.add_argument("--profile", required=True)
    parser.add_argument("--warning-suppressions", required=True)
    parser.add_argument("--python-config", required=True)
    parser.add_argument("--log-dir", required=True, type=Path)
    args = parser.parse_args()

    target = args.target.resolve()
    log_dir = args.log_dir.resolve()

    if log_dir.exists():
        shutil.rmtree(log_dir)
    log_dir.mkdir(parents=True)

    environment = os.environ.copy()
    pytest_arguments = json.loads(environment.get("HSTD_PY_PYTEST_EXTRA_ARGS", "[]"))
    pytest_arguments.append(f"--report-log={log_dir / 'conan_pytest.jsonl'}")
    environment["HSTD_PY_PYTEST_EXTRA_ARGS"] = json.dumps(pytest_arguments)
    environment["GTEST_OUTPUT"] = f"json:{log_dir}/gtest_results/"

    conan_arguments = [
        f"--profile:all={args.profile}",
        "-c",
        f"user.hstd:warning_suppressions={args.warning_suppressions}",
        "-c",
        'user.hstd:ninja_args=["-k","0","--verbose"]',
        *shlex.split(args.python_config),
        "--build=missing",
        "-vstatus",
    ]

    log_name = "conan_editable.log" if args.editable else "conan_create.log"

    with (log_dir / log_name).open("w") as log:
        if args.editable:
            reference = get_reference(target, environment)

            run(
                ["conan", "build", str(target), *conan_arguments],
                environment=environment,
                log=log,
            )
            run(
                [
                    "conan",
                    "test",
                    str(target / "test_package"),
                    reference,
                    *conan_arguments,
                ],
                environment=environment,
                log=log,
            )
        else:
            run(
                ["conan", "remove", f"{target.name}/*", "--confirm"],
                environment=environment,
                log=log,
            )
            run(
                ["conan", "create", str(target), *conan_arguments],
                environment=environment,
                log=log,
            )


if __name__ == "__main__":
    try:
        main()
    except subprocess.CalledProcessError as error:
        sys.exit(error.returncode)
