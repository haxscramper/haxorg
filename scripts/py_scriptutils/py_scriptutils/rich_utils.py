from rich.console import Console


def render_rich(it) -> str:
    console = Console()
    with console.capture() as capture:
        console.print(it)

    return capture.get()
