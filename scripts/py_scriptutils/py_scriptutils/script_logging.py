from rich.logging import RichHandler
import logging
from rich.console import Console
import traceback
from rich.pretty import pprint
import sys
from types import MethodType


def to_debug_json(
    obj,
    include_single_underscore_attrs: bool = False,
    include_double_underscore_attrs: bool = False,
):
    visited = set()

    def aux(obj):
        if isinstance(obj, (int, float, str, bool, type(None))):
            return obj

        if id(obj) in visited:
            return f"cycle {type(obj)} {id(obj)}"

        visited.add(id(obj))

        # Handle different data types
        if isinstance(obj, dict):
            result = {}
            for key, value in obj.items():
                result[key] = aux(value)
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

            else:
                return f"unhandled {type(obj)}"

    return aux(obj)


def pprint_to_file(value, path: str):
    # Built-in python pprint is too broken for regular uses -- output is not
    # always rendered to the max column limit is the biggest problem and I could
    # not find any way to print converted translation unit safely.
    with open(path, "w") as file:
        pprint(value, console=Console(file=file, force_terminal=True, color_system=None))


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

for name in logging.root.manager.loggerDict:
    logger = logging.getLogger(name)
    logger.setLevel(logging.WARNING)


def log(category="rich") -> logging.Logger:
    log = logging.getLogger(category)
    return log


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

    print(exc_type.__name__, ":", exc_value)


sys.excepthook = custom_traceback_handler

log("graphviz._tools").setLevel(logging.ERROR)
log("matplotlib").setLevel(logging.WARNING)
