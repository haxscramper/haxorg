from collections.abc import Mapping

from beartype import beartype
from beartype.typing import Any
from rich.console import Console, Group
from rich.pretty import pprint
from rich.table import Table
from rich.text import Text
from rich.tree import Tree


@beartype
def use_colored_repr() -> bool:
    import sys

    return sys.stdout.isatty()


@beartype
def render_rich(it: Any, color: bool = use_colored_repr(), width: int = 2500) -> str:
    console = Console(force_terminal=color, width=width)
    with console.capture() as capture:
        console.print(it)

    return capture.get()


@beartype
def render_rich_pprint(
    obj: Any,
    width: int = 150,
    color: bool = use_colored_repr(),
    max_string: int | None = None,
) -> str:

    console = Console(record=True, width=width, force_terminal=color)
    with console.capture() as capture:
        pprint(
            obj,
            console=console,
            max_length=width,
            max_string=max_string,
            indent_guides=False,
        )
    return capture.get()


@beartype
def render_debug(value: Any, color: bool = use_colored_repr(), width: int = 200) -> str:
    return render_rich_pprint(value, width=width, color=color)


@beartype
def dict_of_tables_to_group(
    tables: Mapping[str, Table],
    style: bool = use_colored_repr(),
    table_lines: list[list[str]] = list(),
) -> Group:
    """Arrange named tables in rows, then append unlisted tables in sorted order."""

    def st(text: str, wrap: str) -> str:
        if style:
            return f"[{wrap}]{text}[/{wrap}]"

        else:
            return text

    def table_group(table_name: str) -> Group:
        table_content = tables[table_name]
        count = table_content.row_count
        caption = Text(
            "Table: {table_name} {size}{count}".format(
                table_name=st(str(table_name), "bold magenta"),
                size=st("Size:", "white"),
                count=count if count else st("empty", "red"),
            ),
            style="bold underline" if style else "",
        )
        return Group(caption, table_content) if count else Group(caption)

    result = list()
    placed = set()
    for line in table_lines:
        if not line:
            continue

        row = Table.grid(padding=(0, 1))
        for table_name in line:
            row.add_column(vertical="top")

        row.add_row(*(table_group(table_name) for table_name in line))
        result.append(row)
        placed.update(line)

    for table_name in sorted(tables.keys() - placed):
        result.append(table_group(table_name))

    return Group(*result)


class IndentedTree(Tree):
    TREE_GUIDES = [("    ", "    ", "    ", "    ")] * 3
    ASCII_GUIDES = ("    ", "    ", "    ", "    ")
