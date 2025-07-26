from typing import Union, List, Generator, Tuple, Dict, Any
import json
from pathlib import Path
import logging
import subprocess
from contextlib import contextmanager
import os
import inspect

logging.basicConfig()
logging.root.setLevel(logging.NOTSET)
logging.basicConfig(
    level=logging.NOTSET,
    format="%(asctime)s - %(filename)s:%(lineno)d - %(levelname)s - %(message)s")

logger = logging.getLogger(__name__)


def get_threading_count() -> int:
    return int(os.cpu_count() * 0.6)


def get_j_cap() -> List[str]:
    # Using Ninja's default formula with CPU_COUNT+2 exhausts all the
    # memory in the system (64GB).
    return ["-j", str(get_threading_count())]


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
    cmd: List[str],
    env: Dict[str, str] | None = None,
) -> None:
    """Run a subprocess command with logging."""
    cmd_str = " ".join(str(arg) for arg in cmd)
    filename, lineno = get_caller_info()
    logger.info(f"Executing: {cmd_str} from {filename}:{lineno} in {os.getcwd()}")
    try:
        subprocess.run(cmd, check=True, env=env)

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


def parse_haxorg_env_value(value: str, type_hint: str = None) -> Any:
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
    result = {}

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
