from rich.logging import RichHandler
import logging
from rich.console import Console
import traceback
from rich.pretty import pprint
import sys
from types import MethodType
from rich.text import Text
from rich.console import Console
import enum
import os

def is_ci() -> bool:
    return bool(os.getenv("INVOKE_CI"))


def to_debug_json(
    obj,
    include_single_underscore_attrs: bool = False,
    include_double_underscore_attrs: bool = False,
    skip_cyclic_data: bool = True,
    override_callback: callable = None,
):
    visited = set()

    def aux(obj):   
        if override_callback:
            override_result = override_callback(obj)
            if override_result:
                return override_result

        if isinstance(obj, (int, float, str, bool, type(None))):
            return obj

        elif isinstance(obj, (enum.Enum, enum.IntEnum, enum.StrEnum)):
            return str(obj)

        if skip_cyclic_data and id(obj) in visited:
            return f"cycle {type(obj)} {id(obj)}"

        visited.add(id(obj))

        # Handle different data types
        if isinstance(obj, dict):
            result = {}
            for key, value in obj.items():
                result[str(key)] = aux(value)

            return result

        elif isinstance(obj, (list, tuple, set, frozenset)):
            return [aux(item) for item in obj]

        elif callable(obj):
            return f"{obj}"

        else:

            def include_attr(name: str) -> bool:
                has_double = name.startswith("__")
                has_single = name.startswith("_")
                is_regular = not has_single
                return (has_double and include_double_underscore_attrs) or (
                    not has_double and has_single and
                    include_single_underscore_attrs) or is_regular

            try:
                hasattr(obj, "__dict__")

            except TypeError as e:
                if "Unregistered" in str(e):
                    return str(e)

                else:
                    raise e from None

            if hasattr(obj, "__dict__"):
                result = {}
                for key, value in obj.__dict__.items():
                    if include_attr(key):
                        result[key] = aux(value)

                return result

            elif hasattr(obj, "__slots__"):
                result = {}
                for slot_name in obj.__slots__:
                    if include_attr(slot_name):
                        value = getattr(obj, slot_name)
                        result[slot_name] = aux(value)

                return result

            elif hasattr(obj, "keys") and hasattr(obj, "__getitem__"):
                keys = obj.keys()
                if all(isinstance(it, str) for it in keys):
                    return {key: aux(obj[key]) for key in keys}

                else:
                    return [[aux(key), aux(obj[key])] for key in keys]

            elif hasattr(obj, "__len__") and hasattr(obj, "__getitem__"):
                return [aux(obj[i]) for i in range(0, len(obj))]

            elif hasattr(obj, "__iter__"):
                return [aux(item) for item in obj]

            elif hasattr(obj, "__str__") or hasattr(obj, "__repr__"):
                return f"{type(obj)} = {obj}"
            
            elif hasattr(obj, "__int__"):
                return f"{type(obj)} = {int(obj)}"

            else:
                return f"unhandled {type(obj)}"

    return aux(obj)


def pprint_to_file(value, path: str, width: int = 120):
    # Built-in python pprint is too broken for regular uses -- output is not
    # always rendered to the max column limit is the biggest problem and I could
    # not find any way to print converted translation unit safely.
    with open(path, "w") as file:
        print("# pyright: reportUndefinedVariable=false", file=file)
        from py_scriptutils.rich_utils import render_rich_pprint
        print(render_rich_pprint(value, width=width, color=False), file=file)

def pprint_to_string(value, width: int = 120):
    from py_scriptutils.rich_utils import render_rich_pprint
    return render_rich_pprint(value, width=width, color=False)

class NoTTYFormatter(logging.Formatter):

    def __init__(self, fmt, datefmt=None):
        super().__init__(fmt, datefmt)
        self.console = Console()

    def format(self, record):
        record.msg = self.console.render_str(record.getMessage(), highlight=False)
        return super().format(record)


if sys.stdout.isatty():
    logging.basicConfig(
        level="NOTSET",
        format="%(name)s - %(message)s",
        datefmt="[%X]",
        handlers=[
            RichHandler(
                rich_tracebacks=True,
                markup=True,
                enable_link_path=False,
                show_time=False,
            )
        ],
    )

else:
    handler = logging.StreamHandler()
    handler.setFormatter(NoTTYFormatter("[%(name)s %(filename)s:%(lineno)s] %(message)s"))
    logging.basicConfig(level="NOTSET", handlers=[handler])

for name in logging.root.manager.loggerDict:
    logger = logging.getLogger(name)
    logger.setLevel(logging.WARNING)


def log(category="rich") -> logging.Logger:
    log = logging.getLogger(category)
    return log

def ci_log() -> logging.Logger:
    return log("ci")

class ExceptionContextNote:
    """
    If context body raises an exception, add a note to it.
    """

    def __init__(self, note: str):
        self.note = note

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        if exc_value is not None:
            if not hasattr(exc_value, '__notes__'):
                exc_value.__notes__ = []
            exc_value.__notes__.append(self.note)
        return False


def custom_traceback_handler(exc_type, exc_value, exc_traceback):
    """
    Custom traceback handler that filters out frames with '<@beartype' and formats
    the output using 'rich' library, with the decision on one-line or two-line format
    based on available width.
    """
    console = Console()

    # Extract traceback information
    extracted_tb = traceback.extract_tb(exc_traceback)

    # Filter out frames with "<@beartype" in their names
    filtered_tb = [frame for frame in extracted_tb if "<@beartype" not in frame.filename]
    formatted = [(f"File \"{frame.filename}\", line {frame.lineno}, in {frame.name}",
                  frame.line) for frame in filtered_tb]

    max_formatted_width = max([len(it[0]) for it in formatted]) + 2

    # Determine if one-line formatting is feasible
    one_line_format = console.width >= 100  # example threshold for deciding format

    for frame in formatted:
        print("{:<{}}{}{}".format(frame[0], max_formatted_width,
                                  " : " if one_line_format else "\n  ", frame[1]))

    print(f"{exc_type.__name__} : {exc_value}")
    if hasattr(exc_value, "__notes__"):
        for note in exc_value.__notes__:
            print(f"Note: {note}")

    if hasattr(exc_value, "__rich_msg__"):
        console.print(getattr(exc_value, "__rich_msg__"))


sys.excepthook = custom_traceback_handler

log("graphviz").setLevel(logging.ERROR)
log("asyncio").setLevel(logging.ERROR)
log("matplotlib").setLevel(logging.WARNING)


import logging
from pathlib import Path
from beartype import beartype
from typing import Dict


class MultiFileHandler(logging.Handler):
    @beartype
    def __init__(self, base_dir: Path):
        super().__init__()
        self.base_dir = base_dir
        self.base_dir.mkdir(parents=True, exist_ok=True)
        self.logger_handlers: Dict[str, logging.FileHandler] = {}
        self.main_handler = logging.FileHandler(self.base_dir / "main.log")
        self.main_handler.setFormatter(
            logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")
        )

    @beartype
    def _get_logger_handler(self, logger_name: str) -> logging.FileHandler:
        if logger_name not in self.logger_handlers:
            safe_name = logger_name.replace("/", "_").replace("\\", "_")
            log_file = self.base_dir / f"{safe_name}.log"
            handler = logging.FileHandler(log_file)
            handler.setFormatter(
                logging.Formatter("%(asctime)s - %(levelname)s - %(message)s")
            )
            self.logger_handlers[logger_name] = handler
        return self.logger_handlers[logger_name]

    @beartype
    def emit(self, record: logging.LogRecord) -> None:
        self.main_handler.emit(record)
        logger_handler = self._get_logger_handler(record.name)
        logger_handler.emit(record)

    @beartype
    def close(self) -> None:
        self.main_handler.close()
        for handler in self.logger_handlers.values():
            handler.close()
        super().close()


@beartype
def setup_multi_file_logging(base_dir: Path) -> MultiFileHandler:
    handler = MultiFileHandler(base_dir)
    handler.setLevel(logging.DEBUG)
    root_logger = logging.getLogger()
    root_logger.addHandler(handler)
    root_logger.setLevel(logging.DEBUG)
    return handler
