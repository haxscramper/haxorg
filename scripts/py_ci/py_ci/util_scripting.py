from typing import Union, List, Generator, Tuple, Dict
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
    logger.info(f"Executing: {cmd_str} from {filename}:{lineno}")
    try:
        subprocess.run(cmd, check=True, env=env)

    except Exception as e:
        e.add_note(f"Failed to execute from {filename}:{lineno}")
        raise e from None


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
