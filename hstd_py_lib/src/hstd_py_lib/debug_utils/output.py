import logging
import sys

from hstd_py_lib.debug_utils.config import Settings
from hstd_py_lib.debug_utils.model import Report, ValueNode


class PropagatingStreamHandler(logging.StreamHandler):
    def handleError(self, record: logging.LogRecord) -> None:
        error = sys.exception()
        if error is not None:
            raise error

        raise RuntimeError(f"Logging failed while emitting {record.getMessage()!r}")


class PropagatingFileHandler(logging.FileHandler):
    def handleError(self, record: logging.LogRecord) -> None:
        error = sys.exception()
        if error is not None:
            raise error

        raise RuntimeError(
            f"Logging to {self.baseFilename!r} failed "
            f"while emitting {record.getMessage()!r}"
        )


def create_logger(
    name: str,
    settings: Settings,
) -> logging.Logger:
    logger = logging.getLogger(name)
    logger.setLevel(logging.INFO)
    logger.propagate = False

    for handler in list(logger.handlers):
        logger.removeHandler(handler)
        handler.close()

    if settings.log_file is None:
        handler = PropagatingStreamHandler(sys.stderr)
    else:
        handler = PropagatingFileHandler(
            settings.log_file,
            encoding="utf-8",
        )

    handler.setFormatter(logging.Formatter("%(message)s"))
    logger.addHandler(handler)
    return logger


def format_value(
    node: ValueNode,
    depth: int,
) -> list[str]:
    indent = "    " * depth
    text = f"{indent}{node.name}: {node.type_name}"

    if node.value is not None:
        text += f" = {node.value}"

    if node.summary is not None:
        text += f" {node.summary}"

    if node.truncated:
        text += " [truncated]"

    lines = [text]

    if node.error is not None:
        for line in node.error.splitlines():
            lines.append(f"{indent}    [error] {line}")

    for nested in node.nested:
        lines.extend(format_value(nested, depth + 1))

    return lines


def format_report(report: Report) -> str:
    lines = [
        f"=== {report.reason.value} traceback ===",
        f"pid={report.pid}",
    ]

    for thread in report.threads:
        lines.append(f"thread tid={thread.tid}: {thread.stop_reason}")

        if thread.signal_name is not None:
            lines.append(f"signal={thread.signal_name} number={thread.signal_number}")

        for frame in thread.frames:
            location = ""

            if frame.file_path is not None:
                location = f" @ {frame.file_path}:{frame.line}"

            lines.append(f"frame #{frame.index}: {frame.function_name}{location}")

            for argument in frame.arguments:
                lines.extend(format_value(argument, 1))

    lines.append("=== end ===")
    return "\n".join(lines)


def emit_report(
    logger: logging.Logger,
    settings: Settings,
    report: Report,
) -> None:
    text = report.to_json() if settings.structured_output else format_report(report)
    logger.info(text)
