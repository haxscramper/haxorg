from rich.logging import RichHandler
import logging

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

log("graphviz._tools").setLevel(logging.ERROR)
log("matplotlib").setLevel(logging.WARNING)
