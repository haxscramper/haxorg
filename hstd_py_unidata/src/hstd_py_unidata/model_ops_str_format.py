from __future__ import annotations

import locale
import math
from dataclasses import dataclass, replace
from enum import Enum

from beartype import beartype
from beartype.typing import Mapping, Optional, Sequence

from hstd_py_unidata.model_value import (
    ListValue,
    MapValue,
    OptValue,
    ScalarValue,
    TupleValue,
    Value,
    VariantValue,
    value_text,
)


class Alignment(Enum):
    LEFT = "<"
    RIGHT = ">"
    CENTER = "^"


class Sign(Enum):
    NEGATIVE = "-"
    ALWAYS = "+"
    SPACE = " "


class Presentation(Enum):
    DEFAULT = ""
    BINARY = "b"
    BINARY_UPPER = "B"
    CHARACTER = "c"
    DECIMAL = "d"
    OCTAL = "o"
    HEX = "x"
    HEX_UPPER = "X"
    HEX_FLOAT = "a"
    HEX_FLOAT_UPPER = "A"
    SCIENTIFIC = "e"
    SCIENTIFIC_UPPER = "E"
    FIXED = "f"
    FIXED_UPPER = "F"
    GENERAL = "g"
    GENERAL_UPPER = "G"
    STRING = "s"
    POINTER = "p"
    DEBUG = "?"
    DEBUG_STRING = "?s"
    MAP = "m"


@beartype
@dataclass(frozen=True)
class ArgumentRef:
    index: int | str
    offset: int


@beartype
@dataclass(frozen=True)
class FormatOptions:
    offset: int
    fill: str = " "
    alignment: Optional[Alignment] = None
    sign: Optional[Sign] = None
    alternate: bool = False
    zero: bool = False
    width: int | ArgumentRef | None = None
    precision: int | ArgumentRef | None = None
    localized: bool = False
    no_brackets: bool = False
    presentation: Presentation = Presentation.DEFAULT
    nested: Optional[FormatOptions] = None


@beartype
@dataclass(frozen=True)
class FormatSpec:
    argument: ArgumentRef
    format_spec: FormatOptions
    start: int
    end: int


@beartype
@dataclass(frozen=True)
class ParsedFormat:
    parts: tuple[str | FormatSpec, ...]

    def get_specs(self) -> list[FormatSpec]:
        return [it for it in self.parts if isinstance(it, FormatSpec)]


@beartype
@dataclass(frozen=True)
class FormatLocale:
    decimal_point: str = "."
    thousands_separator: str = ""
    grouping: tuple[int, ...] = ()
    true_name: str = "true"
    false_name: str = "false"


@beartype
@dataclass
class FormatParser:
    text: str
    pos: int = 0
    next_index: int = 0
    automatic_indexing: Optional[bool] = None

    def fail(self, message: str, offset: Optional[int] = None) -> ValueError:
        location = self.pos if offset is None else offset
        return ValueError(
            f"{message} at offset {location} in format string {self.text!r}"
        )

    def peek(self) -> str:
        return self.text[self.pos] if self.pos < len(self.text) else ""

    def number(self, description: str) -> int:
        start = self.pos

        while self.pos < len(self.text):
            char = self.text[self.pos]
            if not ("0" <= char <= "9"):
                break
            self.pos += 1

        if start == self.pos:
            raise self.fail(f"Expected decimal digits for {description}")

        digits = self.text[start : self.pos]

        if 10 < len(digits) or (len(digits) == 10 and "2147483647" < digits):
            raise self.fail(
                f"{description.capitalize()} {digits!r} exceeds 2147483647",
                start,
            )

        return int(digits)

    def argument(self) -> ArgumentRef:
        start = self.pos
        char = self.peek()

        if char in (":", "}"):
            if self.automatic_indexing is False:
                raise self.fail(
                    "Automatic argument indexing cannot follow explicit indexing",
                    start,
                )

            self.automatic_indexing = True
            index = self.next_index
            self.next_index += 1
            return ArgumentRef(index=index, offset=start)

        if char and "0" <= char <= "9":
            index = self.number("argument index")

            if 1 < self.pos - start and self.text[start] == "0":
                raise self.fail(
                    "Explicit argument indices cannot have leading zeroes",
                    start,
                )

            if self.automatic_indexing is True:
                raise self.fail(
                    "Explicit argument indexing cannot follow automatic indexing",
                    start,
                )

            self.automatic_indexing = False
            return ArgumentRef(index=index, offset=start)

        if char and ("a" <= char <= "z" or "A" <= char <= "Z" or char == "_"):
            self.pos += 1

            while self.pos < len(self.text):
                char = self.text[self.pos]
                if not (
                    "a" <= char <= "z"
                    or "A" <= char <= "Z"
                    or "0" <= char <= "9"
                    or char == "_"
                ):
                    break
                self.pos += 1

            return ArgumentRef(
                index=self.text[start : self.pos],
                offset=start,
            )

        raise self.fail(
            f"Expected an argument index, argument name, ':' or '}}'; got {char!r}",
            start,
        )

    def dynamic_number(self, description: str) -> ArgumentRef:
        start = self.pos
        self.pos += 1
        argument = self.argument()

        if self.peek() != "}":
            raise self.fail(
                f"Dynamic {description} must contain only an argument reference"
            )

        self.pos += 1
        return replace(argument, offset=start)

    def options(self) -> FormatOptions:
        start = self.pos
        fill = " "
        alignment: Optional[Alignment] = None
        sign: Optional[Sign] = None
        alternate = False
        zero = False
        width: int | ArgumentRef | None = None
        precision: int | ArgumentRef | None = None
        localized = False
        no_brackets = False
        presentation = Presentation.DEFAULT
        nested: Optional[FormatOptions] = None
        alignments = {item.value for item in Alignment}

        if self.pos + 1 < len(self.text) and self.text[self.pos + 1] in alignments:
            fill = self.text[self.pos]

            if fill in ("{", "}"):
                raise self.fail(f"Brace {fill!r} cannot be used as a fill character")

            alignment = Alignment(self.text[self.pos + 1])
            self.pos += 2

        elif self.peek() in alignments:
            alignment = Alignment(self.peek())
            self.pos += 1

        if self.peek() in {item.value for item in Sign}:
            sign = Sign(self.peek())
            self.pos += 1

        if self.peek() == "#":
            alternate = True
            self.pos += 1

        if self.peek() == "0":
            zero = True
            self.pos += 1

        char = self.peek()

        if char and "0" <= char <= "9":
            width = self.number("width")
        elif char == "{":
            width = self.dynamic_number("width")

        if self.peek() == ".":
            self.pos += 1
            char = self.peek()

            if char and "0" <= char <= "9":
                precision = self.number("precision")
            elif char == "{":
                precision = self.dynamic_number("precision")
            else:
                raise self.fail(
                    "Precision requires decimal digits or a dynamic argument reference"
                )

        if self.peek() == "L":
            localized = True
            self.pos += 1

        if self.peek() == "n":
            no_brackets = True
            self.pos += 1

        char = self.peek()

        if char and char not in (":", "}"):
            if self.text.startswith("?s", self.pos):
                presentation = Presentation.DEBUG_STRING
                self.pos += 2
            else:
                presentations = {
                    item.value: item
                    for item in Presentation
                    if item is not Presentation.DEFAULT
                }

                if char not in presentations:
                    raise self.fail(
                        f"Unknown presentation type {char!r}; expected one of "
                        f"{', '.join(repr(item) for item in presentations)}"
                    )

                presentation = presentations[char]
                self.pos += 1

        if self.peek() == ":":
            self.pos += 1
            nested = self.options()

        if self.peek() != "}":
            raise self.fail(
                f"Unexpected character {self.peek()!r} after format specification; "
                "expected '}'"
            )

        return FormatOptions(
            offset=start,
            fill=fill,
            alignment=alignment,
            sign=sign,
            alternate=alternate,
            zero=zero,
            width=width,
            precision=precision,
            localized=localized,
            no_brackets=no_brackets,
            presentation=presentation,
            nested=nested,
        )

    def field(self) -> FormatSpec:
        start = self.pos
        self.pos += 1
        argument = self.argument()
        char = self.peek()

        if char == ":":
            self.pos += 1
            options = self.options()
        elif char == "}":
            options = FormatOptions(offset=self.pos)
        else:
            raise self.fail(
                f"Expected ':' or '}}' after argument reference; got {char!r}"
            )

        if self.peek() != "}":
            raise self.fail("Replacement field has no closing brace", start)

        self.pos += 1
        return FormatSpec(
            argument=argument,
            format_spec=options,
            start=start,
            end=self.pos,
        )

    def parse(self) -> ParsedFormat:
        parts: list[str | FormatSpec] = []
        literal: list[str] = []

        while self.pos < len(self.text):
            char = self.text[self.pos]

            match char:
                case "{":
                    if self.text.startswith("{{", self.pos):
                        literal.append("{")
                        self.pos += 2
                        continue

                    if literal:
                        parts.append("".join(literal))
                        literal.clear()

                    parts.append(self.field())

                case "}":
                    if not self.text.startswith("}}", self.pos):
                        raise self.fail("Unmatched closing brace")

                    literal.append("}")
                    self.pos += 2

                case _:
                    literal.append(char)
                    self.pos += 1

        if literal:
            parts.append("".join(literal))

        return ParsedFormat(parts=tuple(parts))


@beartype
def parse_format(fmt: str) -> ParsedFormat:
    return FormatParser(text=fmt).parse()


@beartype
@dataclass(frozen=True)
class FormatArguments:
    values: Sequence[Value]
    named_values: Mapping[str, Value]

    def get(self, reference: ArgumentRef) -> Value:
        match reference.index:
            case int() as index:
                if not (0 <= index < len(self.values)):
                    raise ValueError(
                        f"Argument index {index} at offset {reference.offset} "
                        f"is out of range for {len(self.values)} positional arguments"
                    )

                return self.values[index]

            case str() as name:
                if name not in self.named_values:
                    available = ", ".join(repr(item) for item in self.named_values)
                    raise ValueError(
                        f"Named argument {name!r} at offset {reference.offset} "
                        f"was not supplied; available names: {available or '(none)'}"
                    )

                return self.named_values[name]

    def count(
        self,
        count: int | ArgumentRef | None,
        description: str,
    ) -> Optional[int]:
        match count:
            case None:
                return None

            case int():
                return count

            case ArgumentRef():
                value = self.get(count)

                if not (
                    isinstance(value, ScalarValue)
                    and isinstance(value.value, int)
                    and not isinstance(value.value, bool)
                ):
                    actual = (
                        repr(value.value)
                        if isinstance(value, ScalarValue)
                        else type(value).__name__
                    )
                    raise ValueError(
                        f"Dynamic {description} argument {count.index!r} "
                        f"at offset {count.offset} must be an integer, got {actual}"
                    )

                if not (0 <= value.value <= 2147483647):
                    raise ValueError(
                        f"Dynamic {description} argument {count.index!r} "
                        f"at offset {count.offset} must be between 0 and "
                        f"2147483647, got {value.value}"
                    )

                return value.value

    def resolve_options(self, options: FormatOptions) -> FormatOptions:
        return replace(
            options,
            width=self.count(options.width, "width"),
            precision=self.count(options.precision, "precision"),
            nested=(
                self.resolve_options(options.nested)
                if options.nested is not None
                else None
            ),
        )


@beartype
def resolve_format(
    parsed: ParsedFormat,
    arguments: FormatArguments,
) -> ParsedFormat:
    parts: list[str | FormatSpec] = []

    for part in parsed.parts:
        match part:
            case str():
                parts.append(part)

            case FormatSpec():
                arguments.get(part.argument)
                parts.append(
                    replace(
                        part,
                        format_spec=arguments.resolve_options(part.format_spec),
                    )
                )

    return ParsedFormat(parts=tuple(parts))


@beartype
def current_format_locale() -> FormatLocale:
    conventions = locale.localeconv()
    return FormatLocale(
        decimal_point=conventions["decimal_point"],
        thousands_separator=conventions["thousands_sep"],
        grouping=tuple(conventions["grouping"]),
    )


@beartype
def format_error(options: FormatOptions, message: str) -> ValueError:
    return ValueError(
        f"Invalid format specification at offset {options.offset}: {message}"
    )


@beartype
def resolved_count(
    count: int | ArgumentRef | None,
    options: FormatOptions,
) -> Optional[int]:
    if isinstance(count, ArgumentRef):
        raise format_error(
            options,
            f"argument {count.index!r} was not resolved before rendering",
        )

    return count


@beartype
def validate_options(
    options: FormatOptions,
    kind: str,
    presentations: frozenset[Presentation],
    allowed: frozenset[str],
) -> None:
    if options.presentation not in presentations:
        expected = ", ".join(
            repr(item.value or "(default)")
            for item in sorted(presentations, key=lambda item: item.value)
        )
        raise format_error(
            options,
            f"presentation {options.presentation.value!r} is not valid for "
            f"{kind}; expected {expected}",
        )

    enabled = {
        "sign": options.sign is not None,
        "alternate": options.alternate,
        "zero": options.zero,
        "precision": options.precision is not None,
        "localized": options.localized,
        "no_brackets": options.no_brackets,
        "nested": options.nested is not None,
    }

    for name, active in enabled.items():
        if active and name not in allowed:
            raise format_error(
                options,
                f"option {name!r} is not valid for {kind}",
            )


@beartype
def estimated_width(text: str) -> int:
    width = 0

    for char in text:
        code = ord(char)
        wide = (
            0x1100 <= code <= 0x115F
            or code in (0x2329, 0x232A)
            or (0x2E80 <= code <= 0xA4CF and code != 0x303F)
            or 0xAC00 <= code <= 0xD7A3
            or 0xF900 <= code <= 0xFAFF
            or 0xFE10 <= code <= 0xFE19
            or 0xFE30 <= code <= 0xFE6F
            or 0xFF00 <= code <= 0xFF60
            or 0xFFE0 <= code <= 0xFFE6
            or 0x1F300 <= code <= 0x1F64F
            or 0x1F900 <= code <= 0x1F9FF
            or 0x20000 <= code <= 0x3FFFD
        )
        width += 2 if wide else 1

    return width


@beartype
def pad_text(
    text: str,
    options: FormatOptions,
    default_alignment: Alignment,
) -> str:
    width = resolved_count(options.width, options)

    if width is None:
        return text

    padding = max(0, width - estimated_width(text))
    alignment = options.alignment or default_alignment

    match alignment:
        case Alignment.LEFT:
            return text + options.fill * padding

        case Alignment.RIGHT:
            return options.fill * padding + text

        case Alignment.CENTER:
            left = padding // 2
            return options.fill * left + text + options.fill * (padding - left)


@beartype
def debug_text(text: str, quote: str = '"') -> str:
    parts = [quote]

    for char in text:
        match char:
            case "\\":
                parts.append("\\\\")

            case "\n":
                parts.append("\\n")

            case "\r":
                parts.append("\\r")

            case "\t":
                parts.append("\\t")

            case _:
                if char == quote:
                    parts.append("\\" + char)
                elif char.isprintable():
                    parts.append(char)
                else:
                    code = ord(char)

                    if code < 0x100:
                        parts.append(f"\\x{code:02x}")
                    elif code < 0x10000:
                        parts.append(f"\\u{code:04x}")
                    else:
                        parts.append(f"\\U{code:08x}")

    parts.append(quote)
    return "".join(parts)


@beartype
def group_digits(digits: str, conventions: FormatLocale) -> str:
    if not conventions.thousands_separator or not conventions.grouping:
        return digits

    groups: list[str] = []
    end = len(digits)
    group_index = 0
    previous = 0

    while 0 < end:
        if group_index < len(conventions.grouping):
            size = conventions.grouping[group_index]
            group_index += 1
        else:
            size = 0

        if size == 0:
            size = previous
        elif size == locale.CHAR_MAX:
            break

        if size <= 0:
            break

        start = max(0, end - size)
        groups.append(digits[start:end])
        end = start
        previous = size

    if 0 < end:
        groups.append(digits[:end])

    groups.reverse()
    return conventions.thousands_separator.join(groups)


@beartype
def localize_float(text: str, conventions: FormatLocale) -> str:
    exponent_start = len(text)

    for index, char in enumerate(text):
        if char in ("e", "E", "p", "P"):
            exponent_start = index
            break

    mantissa = text[:exponent_start]
    exponent = text[exponent_start:]
    integer, separator, fractional = mantissa.partition(".")

    if integer.startswith(("0x", "0X")):
        integer = integer[:2] + group_digits(integer[2:], conventions)
    else:
        integer = group_digits(integer, conventions)

    if separator:
        return integer + conventions.decimal_point + fractional + exponent

    return integer + exponent


@beartype
def numeric_text(
    digits: str,
    negative: bool,
    prefix: str,
    options: FormatOptions,
    finite: bool = True,
) -> str:
    if negative:
        sign = "-"
    else:
        match options.sign:
            case Sign.ALWAYS:
                sign = "+"
            case Sign.SPACE:
                sign = " "
            case _:
                sign = ""

    text = sign + prefix + digits
    width = resolved_count(options.width, options)

    if options.zero and options.alignment is None and finite and width is not None:
        padding = max(0, width - estimated_width(text))
        return sign + prefix + "0" * padding + digits

    return pad_text(text, options, Alignment.RIGHT)


@beartype
def hex_float(
    value: float,
    precision: Optional[int],
    alternate: bool,
    upper: bool,
) -> str:
    source = value.hex()
    mantissa, exponent_text = source[2:].split("p")
    integer, fractional = mantissa.split(".")
    exponent = int(exponent_text)

    if precision is None:
        fractional = fractional.rstrip("0")
        digits = integer

        if fractional or alternate:
            digits += "." + fractional

    else:
        significand = int(integer + fractional, 16)
        original_places = len(fractional)

        if precision < original_places:
            divisor = 16 ** (original_places - precision)
            rounded, remainder = divmod(significand, divisor)
            twice_remainder = remainder * 2

            if divisor < twice_remainder or (
                twice_remainder == divisor and rounded % 2 == 1
            ):
                rounded += 1

            significand = rounded
        else:
            significand *= 16 ** (precision - original_places)

        digits = format(significand, "x").rjust(precision + 1, "0")

        if precision:
            digits = digits[:-precision] + "." + digits[-precision:]
        elif alternate:
            digits += "."

    exponent_sign = "+" if 0 <= exponent else "-"
    result = f"0x{digits}p{exponent_sign}{abs(exponent)}"
    return result.upper() if upper else result


@beartype
@dataclass(frozen=True)
class FormatRenderer:
    conventions: FormatLocale

    def string(
        self,
        value: str,
        options: FormatOptions,
        debug: bool = False,
    ) -> str:
        validate_options(
            options,
            "a string",
            frozenset(
                {
                    Presentation.DEFAULT,
                    Presentation.STRING,
                    Presentation.DEBUG,
                }
            ),
            frozenset({"precision"}),
        )

        precision = resolved_count(options.precision, options)

        if precision is not None:
            value = value[:precision]

        if options.presentation is Presentation.DEBUG or (
            debug and options.presentation is Presentation.DEFAULT
        ):
            value = debug_text(value)

        return pad_text(value, options, Alignment.LEFT)

    def character(self, value: int, options: FormatOptions) -> str:
        validate_options(
            options,
            "a character",
            frozenset({Presentation.CHARACTER}),
            frozenset(),
        )

        if not (0 <= value <= 0x10FFFF and not (0xD800 <= value <= 0xDFFF)):
            raise format_error(
                options,
                f"integer {value} is not a Unicode scalar value and "
                "cannot use character presentation",
            )

        return pad_text(chr(value), options, Alignment.LEFT)

    def integer(self, value: int, options: FormatOptions) -> str:
        if options.presentation is Presentation.CHARACTER:
            return self.character(value, options)

        validate_options(
            options,
            "an integer",
            frozenset(
                {
                    Presentation.DEFAULT,
                    Presentation.BINARY,
                    Presentation.BINARY_UPPER,
                    Presentation.DECIMAL,
                    Presentation.OCTAL,
                    Presentation.HEX,
                    Presentation.HEX_UPPER,
                }
            ),
            frozenset({"sign", "alternate", "zero", "localized"}),
        )

        magnitude = abs(value)
        prefix = ""

        match options.presentation:
            case Presentation.BINARY | Presentation.BINARY_UPPER:
                digits = format(magnitude, "b")

                if options.alternate:
                    prefix = (
                        "0B"
                        if options.presentation is Presentation.BINARY_UPPER
                        else "0b"
                    )

            case Presentation.OCTAL:
                digits = format(magnitude, "o")

                if options.alternate and magnitude != 0:
                    prefix = "0"

            case Presentation.HEX | Presentation.HEX_UPPER:
                upper = options.presentation is Presentation.HEX_UPPER
                digits = format(magnitude, "X" if upper else "x")

                if options.alternate:
                    prefix = "0X" if upper else "0x"

            case _:
                digits = str(magnitude)

        if options.localized:
            digits = group_digits(digits, self.conventions)

        return numeric_text(
            digits=digits,
            negative=value < 0,
            prefix=prefix,
            options=options,
        )

    def boolean(self, value: bool, options: FormatOptions) -> str:
        if options.presentation not in (
            Presentation.DEFAULT,
            Presentation.STRING,
        ):
            return self.integer(int(value), options)

        validate_options(
            options,
            "a textual boolean",
            frozenset(
                {
                    Presentation.DEFAULT,
                    Presentation.STRING,
                }
            ),
            frozenset({"localized"}),
        )

        if options.localized:
            text = self.conventions.true_name if value else self.conventions.false_name
        else:
            text = "true" if value else "false"

        return pad_text(text, options, Alignment.LEFT)

    def floating(self, value: float, options: FormatOptions) -> str:
        validate_options(
            options,
            "a floating-point number",
            frozenset(
                {
                    Presentation.DEFAULT,
                    Presentation.HEX_FLOAT,
                    Presentation.HEX_FLOAT_UPPER,
                    Presentation.SCIENTIFIC,
                    Presentation.SCIENTIFIC_UPPER,
                    Presentation.FIXED,
                    Presentation.FIXED_UPPER,
                    Presentation.GENERAL,
                    Presentation.GENERAL_UPPER,
                }
            ),
            frozenset(
                {
                    "sign",
                    "alternate",
                    "zero",
                    "precision",
                    "localized",
                }
            ),
        )

        negative = math.copysign(1.0, value) < 0
        magnitude = abs(value)
        precision = resolved_count(options.precision, options)
        upper = options.presentation in (
            Presentation.HEX_FLOAT_UPPER,
            Presentation.SCIENTIFIC_UPPER,
            Presentation.FIXED_UPPER,
            Presentation.GENERAL_UPPER,
        )
        finite = math.isfinite(value)
        prefix = ""

        if not finite:
            digits = "nan" if math.isnan(value) else "inf"

            if upper:
                digits = digits.upper()

        elif options.presentation in (
            Presentation.HEX_FLOAT,
            Presentation.HEX_FLOAT_UPPER,
        ):
            text = hex_float(
                value=magnitude,
                precision=precision,
                alternate=options.alternate,
                upper=upper,
            )
            prefix = text[:2]
            digits = text[2:]

            if options.localized:
                digits = localize_float(digits, self.conventions)

        elif options.presentation is Presentation.DEFAULT and precision is None:
            digits = repr(magnitude)

            if digits.endswith(".0") and not options.alternate:
                digits = digits[:-2]

            if options.alternate:
                mantissa, separator, exponent = digits.partition("e")

                if "." not in mantissa:
                    mantissa += "."

                digits = mantissa + (separator + exponent if separator else "")

            if options.localized:
                digits = localize_float(digits, self.conventions)

        else:
            presentation = options.presentation

            if presentation is Presentation.DEFAULT:
                presentation = Presentation.GENERAL

            effective_precision = 6 if precision is None else precision

            if (
                presentation
                in (
                    Presentation.GENERAL,
                    Presentation.GENERAL_UPPER,
                )
                and effective_precision == 0
            ):
                effective_precision = 1

            alternate = "#" if options.alternate else ""
            numeric_spec = f"{alternate}.{effective_precision}{presentation.value}"
            digits = format(magnitude, numeric_spec)

            if options.localized:
                digits = localize_float(digits, self.conventions)

        return numeric_text(
            digits=digits,
            negative=negative,
            prefix=prefix,
            options=options,
            finite=finite,
        )

    def pointer(self, options: FormatOptions) -> str:
        validate_options(
            options,
            "a null pointer",
            frozenset(
                {
                    Presentation.DEFAULT,
                    Presentation.POINTER,
                }
            ),
            frozenset({"zero"}),
        )

        return numeric_text(
            digits="0",
            negative=False,
            prefix="0x",
            options=options,
        )

    def tuple_value(
        self,
        items: Sequence[Value],
        options: FormatOptions,
        map_entry: bool = False,
    ) -> str:
        validate_options(
            options,
            "a tuple",
            frozenset(
                {
                    Presentation.DEFAULT,
                    Presentation.MAP,
                }
            ),
            frozenset({"no_brackets"}),
        )

        mapping = map_entry or options.presentation is Presentation.MAP

        if mapping and len(items) != 2:
            raise format_error(
                options,
                f"map-style tuple formatting requires exactly two elements, "
                f"got {len(items)}",
            )

        element_options = FormatOptions(offset=options.offset)
        rendered = [self.value(item, element_options, debug=True) for item in items]

        if mapping:
            text = ": ".join(rendered)
        else:
            text = ", ".join(rendered)

            if not options.no_brackets:
                text = "(" + text + ")"

        return pad_text(text, options, Alignment.LEFT)

    def string_range(
        self,
        items: Sequence[Value],
        options: FormatOptions,
    ) -> str:
        if options.no_brackets:
            raise format_error(
                options,
                "the 'n' modifier cannot be combined with string-range presentation",
            )

        if options.nested is not None:
            raise format_error(
                options,
                "string-range presentation cannot have an element specification",
            )

        characters: list[str] = []

        for index, item in enumerate(items):
            if not (
                isinstance(item, ScalarValue)
                and isinstance(item.value, str)
                and len(item.value) == 1
            ):
                actual = (
                    repr(item.value)
                    if isinstance(item, ScalarValue)
                    else type(item).__name__
                )
                raise format_error(
                    options,
                    f"string-range element {index} must be a single-character "
                    f"string, got {actual}",
                )

            characters.append(item.value)

        text = "".join(characters)

        if options.presentation is Presentation.DEBUG_STRING:
            text = debug_text(text)

        return pad_text(text, options, Alignment.LEFT)

    def range_value(
        self,
        items: Sequence[Value],
        options: FormatOptions,
    ) -> str:
        validate_options(
            options,
            "a range",
            frozenset(
                {
                    Presentation.DEFAULT,
                    Presentation.MAP,
                    Presentation.STRING,
                    Presentation.DEBUG_STRING,
                }
            ),
            frozenset({"no_brackets", "nested"}),
        )

        if options.presentation in (
            Presentation.STRING,
            Presentation.DEBUG_STRING,
        ):
            return self.string_range(items, options)

        mapping = options.presentation is Presentation.MAP
        element_options = options.nested or FormatOptions(offset=options.offset)
        rendered: list[str] = []

        for index, item in enumerate(items):
            if mapping:
                if not isinstance(item, TupleValue):
                    raise format_error(
                        options,
                        f"map-style range element {index} must be a two-element "
                        f"TupleValue, got {type(item).__name__}",
                    )

                rendered.append(
                    self.tuple_value(
                        item.items,
                        element_options,
                        map_entry=True,
                    )
                )
            else:
                rendered.append(
                    self.value(
                        item,
                        element_options,
                        debug=options.nested is None,
                    )
                )

        text = ", ".join(rendered)

        if not options.no_brackets:
            opening, closing = ("{", "}") if mapping else ("[", "]")
            text = opening + text + closing

        return pad_text(text, options, Alignment.LEFT)

    def map_value(
        self,
        value: MapValue,
        options: FormatOptions,
    ) -> str:
        validate_options(
            options,
            "a map",
            frozenset(
                {
                    Presentation.DEFAULT,
                    Presentation.MAP,
                }
            ),
            frozenset({"no_brackets", "nested"}),
        )

        element_options = options.nested or FormatOptions(offset=options.offset)
        rendered = [
            self.tuple_value(
                (key, item),
                element_options,
                map_entry=True,
            )
            for key, item in value.entries
        ]
        text = ", ".join(rendered)

        if not options.no_brackets:
            text = "{" + text + "}"

        return pad_text(text, options, Alignment.LEFT)

    def optional(
        self,
        value: OptValue,
        options: FormatOptions,
    ) -> str:
        if value.value is None:
            return "none"

        return (
            "optional("
            + self.value(
                value.value,
                options,
                debug=True,
            )
            + ")"
        )

    def variant(
        self,
        value: VariantValue,
        options: FormatOptions,
    ) -> str:
        validate_options(
            options,
            "a variant",
            frozenset({Presentation.DEFAULT}),
            frozenset(),
        )

        if options.alignment is not None or options.width is not None:
            raise format_error(
                options,
                "variant formatting does not accept alignment or width",
            )

        nested = self.value(
            value.case,
            FormatOptions(offset=options.offset),
            debug=True,
        )
        return "variant(" + nested + ")"

    def scalar(
        self,
        value: ScalarValue,
        options: FormatOptions,
        debug: bool,
    ) -> str:
        match value.value:
            case bool() as primitive:
                return self.boolean(primitive, options)

            case int() as primitive:
                return self.integer(primitive, options)

            case float() as primitive:
                return self.floating(primitive, options)

            case str() as primitive:
                return self.string(primitive, options, debug)

            case None:
                return self.pointer(options)

    def value(
        self,
        value: Value,
        options: FormatOptions,
        debug: bool = False,
    ) -> str:
        match value:
            case ScalarValue():
                return self.scalar(value, options, debug)

            case ListValue():
                return self.range_value(value.items, options)

            case MapValue():
                return self.map_value(value, options)

            case TupleValue():
                return self.tuple_value(value.items, options)

            case OptValue():
                return self.optional(value, options)

            case VariantValue():
                return self.variant(value, options)

            case _:
                return self.string(value_text(value), options, debug)


@beartype
def render_format(
    resolved: ParsedFormat,
    arguments: FormatArguments,
    conventions: Optional[FormatLocale] = None,
) -> str:
    renderer = FormatRenderer(
        conventions=(current_format_locale() if conventions is None else conventions)
    )
    parts: list[str] = []

    for part in resolved.parts:
        match part:
            case str():
                parts.append(part)

            case FormatSpec():
                value = arguments.get(part.argument)

                try:
                    rendered = renderer.value(value, part.format_spec)
                except ValueError as error:
                    raise ValueError(
                        f"Cannot format argument {part.argument.index!r} "
                        f"in replacement field at offsets "
                        f"{part.start}:{part.end}: {error}"
                    ) from error

                parts.append(rendered)

    return "".join(parts)


@beartype
def apply_parsed_format(
    parsed: ParsedFormat,
    values: Sequence[Value],
    *,
    named_values: Optional[Mapping[str, Value]] = None,
    conventions: Optional[FormatLocale] = None,
) -> str:
    arguments = FormatArguments(
        values=values,
        named_values={} if named_values is None else named_values,
    )
    resolved = resolve_format(parsed, arguments)
    return render_format(resolved, arguments, conventions)


@beartype
def apply_format(
    fmt: str,
    values: Sequence[Value],
    *,
    named_values: Optional[Mapping[str, Value]] = None,
    conventions: Optional[FormatLocale] = None,
) -> str:
    return apply_parsed_format(
        parse_format(fmt),
        values,
        named_values=named_values,
        conventions=conventions,
    )
