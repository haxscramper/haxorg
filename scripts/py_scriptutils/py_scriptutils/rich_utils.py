from rich.console import Console
from rich.pretty import pprint


def render_rich(it) -> str:
    console = Console()
    with console.capture() as capture:
        console.print(it)

    return capture.get()


def render_rich_pprint(
    obj,
    width: int = 80,
    color: bool = True,
    max_string: int | None = None,
) -> str:
    
    console = Console(record=True, width=width, force_terminal=color)

    pprint(
        obj,
        console=console,
        indent_guides=False,
        max_length=width,
        max_string=max_string,
    )

    return console.export_text()

