from py_scriptutils.toml_config_profiler import (
    make_config_provider,
    run_config_provider,
    apply_options,
    options_from_model,
    merge_cli_model,
)

from beartype.typing import Optional
from pathlib import Path
import rich_click as click
from pydantic import BaseModel, Field
from beartype import beartype
import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.files import FileOperation
from py_scriptutils.script_logging import log

def pack_context(ctx: click.Context, name: str, T: type, kwargs: dict, config: Optional[str]):
    """
    Convert the provided CLI parameters into the object of type `T` for
    more typesafe usage
    """
    config_base = run_config_provider(
        ([str(Path(config).resolve())] if config else []), True) if config else {}
    conf = merge_cli_model(ctx, config_base, kwargs, T)
    ctx.ensure_object(dict)
    ctx.obj[name] = conf


CONFIG_FILE_NAME = "pyhaxorg.toml"


class CliRootOptions(BaseModel, extra="forbid"):
    lex_traceDir: Optional[str] = None
    lex_trace: bool = False
    parse_traceDir: Optional[str] = None
    parse_trace: bool = False
    sem_traceDir: Optional[str] = None
    sem_trace: bool = False
    config: Optional[str] = None
    cache: Optional[str] = Field(
        description=
        "Optional directory to cache file parsing to speed up large corpus processing",
        default=None,
    )

    trace_path: Optional[str] = None



@beartype
def parseFile(root: CliRootOptions, file: Path) -> org.Org:
    cache_file = None if not root.cache else Path(root.cache).joinpath(file.name)
    ctx = org.OrgContext()
    if cache_file:
        with FileOperation.InOut([file], [cache_file]) as op:
            if op.should_run():
                log("haxorg.cache").info(f"{file} parsing")
                node = ctx.parseFile(str(file.resolve()))
                if not cache_file.parent.exists():
                    cache_file.parent.mkdir()

                ctx.saveProtobuf(node, str(cache_file))

            else:
                log("haxorg.cache").info(f"{file} read from cache {cache_file}")
                node = ctx.parseProtobuf(str(cache_file))

            return node

    else:
        return ctx.parseFile(str(file.resolve()))


def base_cli_options(f):
    return apply_options(f, options_from_model(CliRootOptions))
