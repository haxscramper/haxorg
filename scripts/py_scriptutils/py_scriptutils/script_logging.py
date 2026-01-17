from dataclasses import dataclass
import traceback
import logging
import sys

from rich.logging import RichHandler
from rich.console import Console
from rich.text import Text
from rich.console import Console

from types import MethodType
import enum
import os
from beartype.typing import Any, Set, Callable, Optional, Literal


def is_ci() -> bool:
    return bool(os.getenv("INVOKE_CI"))


def to_debug_json(
    obj: Any,
    include_single_underscore_attrs: bool = False,
    include_double_underscore_attrs: bool = False,
    skip_cyclic_data: bool = True,
    override_callback: Optional[Callable] = None,
    with_stable_formatting: bool = True,
) -> Any:
    visited: Set[Any] = set()

    def aux(obj: Any) -> Any:
        if override_callback:
            override_result = override_callback(obj)
            if override_result:
                return override_result

        if isinstance(obj, (int, float, str, bool, type(None))):
            return obj

        elif isinstance(obj, (enum.Enum, enum.IntEnum, enum.StrEnum)):
            return str(obj)

        if skip_cyclic_data and id(obj) in visited:
            if with_stable_formatting:
                return f"cycle {type(obj)}"

            else:
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


def pprint_to_file(value: Any, path: str, width: int = 120) -> None:
    # Built-in python pprint is too broken for regular uses -- output is not
    # always rendered to the max column limit is the biggest problem and I could
    # not find any way to print converted translation unit safely.
    with open(path, "w") as file:
        print("# pyright: reportUndefinedVariable=false", file=file)
        from py_scriptutils.rich_utils import render_rich_pprint
        print(render_rich_pprint(value, width=width, color=False), file=file)


def pprint_to_string(value: Any, width: int = 120) -> str:
    from py_scriptutils.rich_utils import render_rich_pprint
    return render_rich_pprint(value, width=width, color=False)


class NoTTYFormatter(logging.Formatter):

    def __init__(self, fmt: Any, datefmt: Any = None) -> None:
        super().__init__(fmt, datefmt)
        self.console = Console()

    def format(self, record: Any) -> str:
        record.msg = self.console.render_str(record.getMessage(), highlight=False)
        return super().format(record)


def log(category: str = "rich") -> logging.Logger:
    log = logging.getLogger(category)
    log.setLevel(logging.DEBUG)

    if "pytest" in sys.modules or hasattr(sys, "_called_from_test"):
        return log

    if not hasattr(log, "__has_haxorg_handler__"):
        setattr(log, "__has_haxorg_handler__", True)
        if sys.stdout.isatty():
            rich_handler = RichHandler(
                console=Console(width=None),
                rich_tracebacks=True,
                markup=True,
                enable_link_path=False,
                show_time=False,
                show_path=False,
            )
            rich_handler.setFormatter(
                logging.Formatter(
                    "[dim]%(name)s %(filename)s:%(lineno)d[/dim] - %(message)s"))

            log.addHandler(rich_handler)

        else:
            handler = logging.StreamHandler()
            handler.setFormatter(
                NoTTYFormatter("[%(name)s %(filename)s:%(lineno)s] %(message)s"))

            log.addHandler(handler)

    return log


def ci_log() -> logging.Logger:
    return log("ci")


class ExceptionContextNote:
    """
    If context body raises an exception, add a note to it.
    """

    def __init__(self, note: str) -> None:
        self.note = note

    def __enter__(self) -> "ExceptionContextNote":
        return self

    def __exit__(self, exc_type: Any, exc_value: Any, traceback: Any) -> Literal[False]:
        if exc_value is not None:
            if not hasattr(exc_value, '__notes__'):
                exc_value.__notes__ = []
            exc_value.__notes__.append(self.note)

        return False


CUSTOM_TRACEBACK_HANDLER_TRUNCATE_VALUE = True
CUSTOM_TRACEBACK_HANDLER_SHOW_ARGS = True
CUSTOM_TRACEBACK_HANDLER_SHOW_ARGUMENT_TYPE_ANNOTATED = False
CUSTOM_TRACEBACK_HANDLER_SHOW_ARGUMENT_TYPE_RUNTIME = False


def get_function_annotations(frame: Any) -> dict[str, str]:
    func_name = frame.f_code.co_name
    annotations = {}

    try:
        if "self" in frame.f_locals:
            obj = frame.f_locals["self"]
            if hasattr(obj, func_name):
                func = getattr(obj, func_name)
                if hasattr(func, "__annotations__"):
                    annotations = func.__annotations__
        elif "cls" in frame.f_locals:
            cls = frame.f_locals["cls"]
            if hasattr(cls, func_name):
                func = getattr(cls, func_name)
                if hasattr(func, "__annotations__"):
                    annotations = func.__annotations__
        else:
            for name, obj in frame.f_globals.items():
                if callable(obj) and getattr(obj, "__name__", None) == func_name:
                    if hasattr(obj, "__annotations__"):
                        annotations = obj.__annotations__
                    break
    except (AttributeError, KeyError):
        pass

    return {k: str(v) for k, v in annotations.items() if k != "return"}


@dataclass
class FrameInfo:
    filename: str
    line_no: int
    func_name: str
    args: dict[str, Any]
    arg_types: dict[str, str]
    runtime_types: dict[str, str]
    code_line: str


def custom_traceback_handler(exc_type: Any, exc_value: Any, exc_traceback: Any) -> None:
    console = Console()

    current_tb = exc_traceback
    frames_info = []

    while current_tb is not None:
        frame = current_tb.tb_frame
        filename = frame.f_code.co_filename

        if "<@beartype" not in filename:
            line_no = current_tb.tb_lineno
            func_name = frame.f_code.co_name

            args = {}
            arg_types = {}
            runtime_types = {}

            if CUSTOM_TRACEBACK_HANDLER_SHOW_ARGS:
                arg_names = frame.f_code.co_varnames[:frame.f_code.co_argcount]
                for arg_name in arg_names:
                    if arg_name in frame.f_locals:
                        args[arg_name] = frame.f_locals[arg_name]

                        if CUSTOM_TRACEBACK_HANDLER_SHOW_ARGUMENT_TYPE_RUNTIME:
                            runtime_types[arg_name] = type(
                                frame.f_locals[arg_name]).__name__

                if CUSTOM_TRACEBACK_HANDLER_SHOW_ARGUMENT_TYPE_ANNOTATED:
                    arg_types = get_function_annotations(frame)

            extracted_frame = traceback.extract_tb(current_tb, limit=1)[0]
            frames_info.append(
                FrameInfo(filename, line_no, func_name, args, arg_types, runtime_types,
                          extracted_frame.line or ""))

        current_tb = current_tb.tb_next

    if not frames_info:
        print(f"{exc_type.__name__} : {exc_value}")
        return

    max_arg_name_width = 0
    if CUSTOM_TRACEBACK_HANDLER_SHOW_ARGS:
        for frame_info in frames_info:
            if frame_info.args:
                max_arg_name_width = max(
                    max_arg_name_width,
                    max(len(arg_name) for arg_name in frame_info.args.keys()))

    for frame_info in frames_info:
        header = f"File \"{frame_info.filename}\", line {frame_info.line_no}, in {frame_info.func_name}"
        print(f"{header} : {frame_info.code_line}")

        if CUSTOM_TRACEBACK_HANDLER_SHOW_ARGS:
            for arg_name, arg_value in frame_info.args.items():
                type_info = ""

                if CUSTOM_TRACEBACK_HANDLER_SHOW_ARGUMENT_TYPE_ANNOTATED and arg_name in frame_info.arg_types:
                    type_info = f": {frame_info.arg_types[arg_name]}"

                if CUSTOM_TRACEBACK_HANDLER_SHOW_ARGUMENT_TYPE_RUNTIME and arg_name in frame_info.runtime_types:
                    runtime_type = frame_info.runtime_types[arg_name]
                    if type_info:
                        type_info += f" ({runtime_type})"
                    else:
                        type_info = f": {runtime_type}"

                available_width = console.width - max_arg_name_width - len(type_info) - 5

                if CUSTOM_TRACEBACK_HANDLER_TRUNCATE_VALUE:
                    arg_repr = repr(arg_value)
                    if len(arg_repr) > available_width:
                        arg_repr = arg_repr[:available_width - 3] + "..."
                    print(
                        f"  {arg_name}{type_info:<{max_arg_name_width-len(arg_name)}} = {arg_repr}"
                    )
                else:
                    import pprint
                    formatted_value = pprint.pformat(arg_value, width=available_width)
                    lines = formatted_value.split('\n')

                    print(
                        f"  {arg_name}{type_info:<{max_arg_name_width-len(arg_name)}} = {lines[0]}"
                    )
                    for line in lines[1:]:
                        print(f"  {'':<{max_arg_name_width}}   {line}")

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
from rich.text import Text


class MultiFileHandler(logging.Handler):

    @beartype
    def __init__(self, base_dir: Path) -> None:
        super().__init__()
        self.base_dir = base_dir
        self.base_dir.mkdir(parents=True, exist_ok=True)
        self.logger_handlers: Dict[str, logging.FileHandler] = {}
        self.main_handler = logging.FileHandler(self.base_dir / "main.log", mode="w")
        self.main_handler.setFormatter(
            logging.Formatter(
                "%(asctime)s - %(filename)s:%(lineno)d - %(name)s - %(levelname)s - %(message)s"
            ))
        self.plain_console = Console(color_system=None,
                                     legacy_windows=False,
                                     force_terminal=False,
                                     no_color=True,
                                     width=999999)

    @beartype
    def _strip_rich_formatting(self, message: str) -> str:
        text = Text.from_markup(message)
        with self.plain_console.capture() as capture:
            self.plain_console.print(text, end="")
        return capture.get()

    @beartype
    def _get_logger_handler(self, logger_name: str) -> logging.FileHandler:
        if logger_name not in self.logger_handlers:
            safe_name = logger_name.replace("/", "_").replace("\\", "_")
            log_file = self.base_dir / f"{safe_name}.log"
            handler = logging.FileHandler(log_file, mode="w")
            handler.setFormatter(
                logging.Formatter(
                    "%(asctime)s - %(filename)s:%(lineno)d - %(levelname)s - %(message)s")
            )
            self.logger_handlers[logger_name] = handler
        return self.logger_handlers[logger_name]

    @beartype
    def emit(self, record: logging.LogRecord) -> None:
        record.msg = self._strip_rich_formatting(str(record.msg))
        if hasattr(record, "args") and record.args:
            record.args = tuple(
                self._strip_rich_formatting(str(arg)) if isinstance(arg, str) else arg
                for arg in record.args)

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
