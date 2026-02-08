from contextlib import contextmanager
import inspect
import json
import logging
import os
from pathlib import Path
import subprocess
from typing import Any, Dict, Generator, List, Optional, Sequence, Tuple, Union

logging.root.setLevel(logging.DEBUG)
logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)


def get_threading_count() -> int:
    return int((os.cpu_count() or 6) * 0.9)


def get_j_cap() -> List[str]:
    # Using Ninja's default formula with CPU_COUNT+2 exhausts all the
    # memory in the system (64GB).
    return ["-j", str(get_threading_count())]


def get_docker_cap_flags() -> List[str]:
    return ["--memory=20G", f"--cpus={int((os.cpu_count() or 6) * 0.9)}"]


@contextmanager
def change_dir(target_dir: Path) -> Generator[None, None, None]:
    """Temporarily change the working directory."""
    current_dir: Path = Path.cwd()
    try:
        os.chdir(target_dir)
        yield
    finally:
        os.chdir(current_dir)


def get_caller_info() -> Tuple[str, int]:
    """Get the filename and line number of the caller."""
    frame = inspect.currentframe()
    if frame is not None and frame.f_back is not None:
        frame = frame.f_back.f_back  # Skip this function and the immediate caller
        if frame is not None:
            return frame.f_code.co_filename, frame.f_lineno
    return "unknown", 0


def run_cmd(
    cmd: Sequence[str | Path],
    env: Dict[str, str] | None = None,
    cwd: Optional[str] = None,
    check: bool = True,
) -> (int, str, str):
    """Run a subprocess command with logging. Return tuple: (code, stdout, stderr)"""
    cmd_str = " ".join(str(arg) for arg in cmd)
    filename, lineno = get_caller_info()
    logger.info("~" * 120)
    logger.info(f"Executing: {cmd_str} from {filename}:{lineno} in {cwd or os.getcwd()}")
    try:
        process = subprocess.run(
            [str(s) for s in cmd],
            env=env,
            cwd=cwd,
            capture_output=True,
            text=True,
            check=False,
        )
        logger.info(f"stdout:\n{process.stdout}")
        logger.info(f"stderr:\n{process.stderr}")

        if check and process.returncode != 0:
            err = RuntimeError(
                f"Failed to execute command '{cmd_str}'  from {filename}:{lineno}")
            if process.stdout:
                err.add_note(f"stdout:\n{process.stdout}")

            if process.stderr:
                err.add_note(f"stderr:\n{process.stderr}")

            if cwd:
                err.add_note(f"cwd:{cwd}")

            raise err

        return (process.returncode, process.stdout, process.stderr)

    except Exception as e:
        e.add_note(f"Failed to execute from {filename}:{lineno}")
        raise e from None


def haxorg_env(path: List[str], value: Union[str, bool, Path, None]) -> dict[str, str]:
    assert isinstance(path, list), str(path)
    result = "HAXORG_ENV_" + "_".join([str(p).upper() for p in path])
    match value:
        case str():
            return {result: value}

        case bool():
            if value:
                return {result: "1"}

            else:
                return {result: "0"}

        case None:
            return {result: "OFF"}

        case _:
            return {result: str(value)}


def parse_haxorg_env_value(value: str, type_hint: Optional[str] = None) -> Any:
    """Parse environment variable value based on type hint or CMake-like rules."""

    if type_hint:
        if type_hint == "str":
            return value
        elif type_hint == "int":
            return int(value)
        elif type_hint == "float":
            return float(value)
        elif type_hint == "bool":
            return value.upper() in ("TRUE", "ON", "YES", "1")
        elif type_hint in ("list", "dict", "json"):
            return json.loads(value)
        else:
            # Unknown type hint, treat as string
            return value

    # CMake-like parsing rules when no type hint
    # Check for boolean values first
    upper_value = value.upper()
    if upper_value in ("TRUE", "ON", "YES", "1"):
        return True
    elif upper_value in ("FALSE", "OFF", "NO", "0"):
        return False

    # Try to parse as integer
    try:
        return int(value)
    except ValueError:
        pass

    # Try to parse as float
    try:
        return float(value)
    except ValueError:
        pass

    # Try to parse as JSON (for lists/dicts)
    if value.startswith(('[', '{')):
        try:
            return json.loads(value)
        except json.JSONDecodeError:
            pass

    # Default to string
    return value


def set_nested_dict(d: Dict[str, Any], keys: List[str], value: Any) -> None:
    """Set a value in a nested dictionary using a list of keys."""
    current = d
    for key in keys[:-1]:
        if key not in current:
            current[key] = {}
        elif not isinstance(current[key], dict):
            # If there's a conflict, convert to dict
            current[key] = {}
        current = current[key]

    current[keys[-1]] = value


def parse_haxorg_env() -> Dict[str, Any]:
    """Parse HAXORG_ENV_* environment variables into a nested dictionary."""
    result: Dict[str, Any] = {}

    for env_var, env_value in os.environ.items():
        if not env_var.startswith("HAXORG_ENV_"):
            continue

        # Remove HAXORG_ENV_ prefix
        tail = env_var[11:]  # len("HAXORG_ENV_") = 11

        # Check for type hint
        type_hint = None
        if ":" in tail:
            tail, type_hint = tail.rsplit(":", 1)

        # Convert to lowercase and split by underscore
        keys = tail.lower().split("_")

        # Filter out empty keys
        keys = [key for key in keys if key]

        if not keys:
            continue

        # Parse the value
        parsed_value = parse_haxorg_env_value(env_value, type_hint)

        # Set in nested dictionary
        set_nested_dict(result, keys, parsed_value)

    return result


def cmake_opt(name: str, value: Union[str, bool, Path, None, List]) -> str:
    result = "-D" + name + "="
    if isinstance(value, (str, Path)):
        result += str(value)

    elif isinstance(value, bool):
        result += ("ON" if value else "OFF")

    elif isinstance(value, list):
        result += ";".join([str(it) for it in value])

    elif value is None:
        result += "OFF"

    return result
