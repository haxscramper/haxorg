# fork of https://github.com/inakleinbottle/texoutparse/tree/master
"""
Parser for LaTeX log files.
"""
from collections import deque
from dataclasses import dataclass
from dataclasses import field
import re

from beartype import beartype
from beartype.typing import Any
from beartype.typing import Iterable
from beartype.typing import List
from beartype.typing import Optional
from beartype.typing import Tuple

CAT = __name__


@beartype
@dataclass
class LogFileMessage:
    """
    Helper class for storing log file messages.

    Messages and attributes of the messages can be accessed and added using
    the item notation.
    """

    message: str = ""
    type_: str = ""
    direction: Optional[str] = None
    direction_by: Optional[str] = None
    lines: Optional[Tuple[str, str]] = None
    package: Optional[str] = None
    class_: Optional[str] = None
    component: Optional[str] = None
    extra: Optional[str] = None
    context_lines: List[str] = field(default_factory=list)
    location: Optional[int] = None


class _LineIterWrapper:
    """
    Wrapper around an iterable that allows peeking ahead to get context lines
    without consuming the iterator.
    """

    def __init__(self, iterable: Iterable[Any], ctx_lines: int) -> None:
        self.iterable = iter(iterable)
        self.cache: deque[str] = deque()
        self.ctx_lines = ctx_lines
        self.current = None

    def __next__(self) -> str:
        if self.cache:
            self.current = current = self.cache.popleft()  # type: ignore
        else:
            self.current = current = next(self.iterable)
        return current

    def __iter__(self) -> "_LineIterWrapper":
        return self

    def get_context(self) -> List[str]:
        rv: List[str] = [self.current] if self.current else []
        for _ in range(self.ctx_lines + 1 - len(rv)):
            try:
                next_val = next(self.iterable)
                self.cache.append(next_val)
                rv.append(next_val)
            except StopIteration:
                break
        return rv


@beartype
@dataclass
class LatexLogParser:
    """
    Parser for LaTeX Log files.

    An LatexLogParser object can parse the log file or output of and generate
    lists of errors, warnings, and bad boxes described in the log. Each error.
    warning, or bad box is stored as a LogFileMessage in the corresponding
    list.
    """

    error = re.compile(
        r"^(?:! ((?:La|pdf)TeX|Package|Class)(?: (\w+))? [eE]rror(?: \(([\\]?\w+)\))?: (.*)|! (.*))"
    )

    warning = re.compile(
        r"^((?:La|pdf)TeX|Package|Class)(?: (\w+))? [wW]arning(?: \(([\\]?\w+)\))?: (.*)",
    )

    badbox = re.compile(r"^(Over|Under)full "
                        r"\\([hv])box "
                        r"\((?:badness (\d+)|(\d+(?:\.\d+)?pt) too \w+)\) (?:"
                        r"(?:(?:in paragraph|in alignment|detected) "
                        r"(?:at lines (\d+)--(\d+)|at line (\d+)))"
                        r"|(?:has occurred while [\\]output is active [\[][\]]))")

    warnings: List[LogFileMessage] = field(default_factory=list)
    errors: List[LogFileMessage] = field(default_factory=list)
    badboxes: List[LogFileMessage] = field(default_factory=list)
    context_lines: int = 2

    def __str__(self) -> str:
        return (f"Errors: {len(self.errors)}, "
                f"Warnings: {len(self.warnings)}, "
                f"Badboxes: {len(self.badboxes)}")

    def get_context_lines(self) -> List[str]:
        return self.lines_iterable.get_context()

    def process(self, lines: Iterable[str]) -> None:
        """
        Process the lines of a logfile to produce a report.

        Steps through each non-empty line and passes it to the process_line
        function.

        :param lines: Iterable over lines of log.
        """
        self.lines_iterable = _LineIterWrapper(lines, self.context_lines)

        # cache the line processor for speed
        process_line = self.process_line

        for i, line in enumerate(self.lines_iterable):
            if not line:
                continue
            err = process_line(line)

    def process_line(self, line: str) -> Optional[LogFileMessage]:
        """
        Process a line in the log file and delegate to correct handler.

        Tests in turn matches to the badbox regex, warning regex, and
        then error regex. Once a match is found, the corresponding
        process function is called its result returned.

        :param line: Line to process
        :returns: LogFileMessage object or None
        """

        # Badboxes are probably most common, so match those first
        match = self.badbox.match(line)
        if match is not None:
            return self.process_badbox(match)

        # Now try warnings
        match = self.warning.match(line)
        if match is not None:
            return self.process_warning(match)

        # Now try errors
        match = self.error.match(line)
        if match is not None:
            return self.process_error(match)

        return None

    def process_badbox(self, match: re.Match) -> LogFileMessage:
        """
        Process a badbox regex match and return the log message object.

        :param match: regex match object to process
        :return: LogFileMessage object
        """

        # Regex match groups
        # 0 - Whole match (line)
        # 1 - Type (Over|Under)
        # 2 - Direction ([hv])
        # 3 - Underfull box badness (badness (\d+))
        # 4 - Overfull box over size (\d+(\.\d+)?pt too \w+)
        # 5 - Multi-line start line (at lines (\d+)--)
        # 6 - Multi-line end line (--(d+))
        # 7 - Single line (at line (\d+))

        message = LogFileMessage(
            type_=match.group(1),
            direction=match.group(2),
            direction_by=match.group(3) or match.group(4),
            context_lines=self.get_context_lines(),
        )

        # single or multi-line
        if match.group(7) is not None:
            message.lines = (match.group(7), match.group(7))
        else:
            message.lines = (match.group(5), match.group(6))

        self.badboxes.append(message)
        return message

    def process_warning(self, match: re.Match) -> LogFileMessage:
        """
        Process a warning regex match and return the log message object.

        :param match: regex match object to process
        :return: LogFileMessage object
        """

        # Regex match groups
        # 0 - Whole match (line)
        # 1 - Type ((?:La|pdf)TeX|Package|Class)
        # 2 - Package or Class name (\w*)
        # 3 - extra
        # 4 - Warning message (.*)

        message = LogFileMessage(
            type_=match.group(1),
            context_lines=self.get_context_lines(),
        )

        if message.type_ == 'Package':
            # package name should be group 2
            message.package = match.group(2)
        elif message.type_ == 'Class':
            # class should be group 2
            message.class_ = match.group(2)
        elif match.group(2) is not None:
            # In any other case we want to record the component responsible for
            # the warning, if one is present.
            message.component = match.group(2)

        if match.group(3) is not None:
            message.extra = match.group(3)

        message.message = match.group(4)
        self.warnings.append(message)
        return message

    def process_error(self, match: re.Match) -> LogFileMessage:
        """
        Process a warning regex match and return the log message object.

        :param match: regex match object to process
        :return: LogFileMessage object
        """

        # Regex match groups
        # 0 - Whole match (line)
        # 1 - Type (LaTeX|Package|Class)
        # 2 - Package or Class (\w+)
        # 3 - extra (\(([\\]\w+)\))
        # 4 - Error message for typed error (.*)
        # 5 - TeX error message (.*)

        message = LogFileMessage(context_lines=self.get_context_lines())
        if match.group(1) is not None:
            message.type_ = match.group(1)

            if message.type_ == 'Package':
                # Package name should be group 2
                message.package = match.group(2)
            elif message.type_ == 'Class':
                # Class name should be group 2
                message.class_ = match.group(2)
            elif match.group(2) is not None:
                message.component = match.group(2)

            if match.group(3) is not None:
                message.extra = match.group(3)

            message.message = match.group(4)
        else:
            message.message = match.group(5)

        if "Undefined control sequence" in message.message:
            new_context = []
            for line in message.context_lines:
                undefined_control_line = re.match(r"l.(\d+).*?(\\\w+)", line)
                if undefined_control_line:
                    message.lines = (undefined_control_line.group(1), "")
                    message.type_ = f"Undefined {undefined_control_line.group(2)}"

                else:
                    new_context.append(line)

            message.context_lines = new_context

        self.errors.append(message)
        return message
