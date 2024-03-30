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
    with console.capture() as capture:
        pprint(
            obj,
            console=console,
            max_length=width,
            max_string=max_string,
            indent_guides=False,
        )
    return capture.get()

def render_debug(value, color: bool = False, width: int = 200) -> str:
    return render_rich_pprint(value, width=width, color=color)
