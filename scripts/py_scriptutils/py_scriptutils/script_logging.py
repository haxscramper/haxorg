from rich.logging import RichHandler
import logging
from rich.console import Console
import sys
import traceback

import os
import sys

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
