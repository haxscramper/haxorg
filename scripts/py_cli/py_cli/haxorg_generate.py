import py_cli.haxorg_cli as h_cli
from pydantic import BaseModel
from beartype.typing import Any, Optional
import rich_click as click

class CliGenerateOptions(BaseModel, extra="forbid"): 
    pass

def generate_cli_options(f: Any) -> Any:
    return h_cli.apply_options(f, h_cli.options_from_model(CliGenerateOptions))

@click.group()
@click.pass_context
@generate_cli_options
def generate(ctx: click.Context, config: Optional[str] = None, **kwargs: Any) -> None:
    """Generate/analyze input org-mode document"""
    pass
