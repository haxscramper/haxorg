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
from py_scriptutils.tracer import TraceCollector

@beartype
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
    cache: Optional[Path] = Field(
        description=
        "Optional directory to cache file parsing to speed up large corpus processing",
        default=None,
    )

    trace_path: Optional[str] = None

@beartype
class CliRunContext:
    def __init__(self, opts: CliRootOptions) -> None:
        self.tracer = TraceCollector()
        self.opts = opts
    
    def event(self, name: str, category: str, args: dict[str, any] = {}):
        return self.tracer.complete_event(name=name, category=category, args=args)
    
    def is_trace_enabled(self) -> bool:
        return bool(self.opts.trace_path)
    
    def finalize(self):
        if self.is_trace_enabled():
            self.tracer.export_to_json(Path(self.opts.trace_path))
            log("haxorg.cli").info(f"Wrote execution trace to {self.opts.trace_path}")

def get_run(ctx: click.Context) -> CliRunContext:
    return ctx.obj["run"]

@beartype
def parseCachedFile(file: Path, cache: Optional[Path]) -> org.Org:
    cache_file = None if not cache else Path(cache).joinpath(file.name)
    if cache_file:
        with FileOperation.InOut([file], [cache_file]) as op:
            if op.should_run():
                log("haxorg.cache").info(f"{file} parsing")
                node = org.parseFile(str(file.resolve()))
                if not cache_file.parent.exists():
                    cache_file.parent.mkdir()

                org.exportToProtobufFile(node, str(cache_file))

            else:
                log("haxorg.cache").info(f"{file} read from cache {cache_file}")
                node = org.readProtobufFile(str(cache_file))

            return node

    else:
        return org.parseFile(str(file.resolve()), org.OrgParseParameters())

@beartype
def parseFile(root: CliRootOptions, file: Path) -> org.Org:
    return parseCachedFile(file, root.cache)



def base_cli_options(f):
    return apply_options(f, options_from_model(CliRootOptions))
