from pathlib import Path

import py_haxorg.pyhaxorg_wrap as org
import rich_click as click
from beartype import beartype
from beartype.typing import Optional, TypeVar, Dict, Any
from py_scriptutils.files import FileOperation
from py_scriptutils.script_logging import log
from py_scriptutils.toml_config_profiler import (
    apply_options,
    get_cli_model,
    make_config_provider,
    merge_cli_model,
    options_from_model,
    run_config_provider,
    pack_context,
)
from py_scriptutils.tracer import TraceCollector
from pydantic import BaseModel, Field

CONFIG_FILE_NAME = "pyhaxorg.toml"
CAT = __name__

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

    def event(self, name: str, category: str, args: Dict[str, Any] = {}):
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
def parseCachedFile(
    file: Path,
    cache: Optional[Path],
    with_includes: bool = True,
    parse_opts: Optional[org.OrgParseParameters] = None,
) -> org.Org:
    cache_file = None if not cache else Path(cache).joinpath(file.name)

    def aux():
        log(CAT).info(f"Processing {file}")
        if with_includes:
            opts = org.OrgDirectoryParseParameters()
            if parse_opts:
                def parse_node_impl(path: str):
                    return org.parseStringOpts(Path(path).read_text(), parse_opts)

                org.setGetParsedNode(opts, parse_node_impl)

            return org.parseFileWithIncludes(str(file.resolve()), opts)
        else:
            if parse_opts:
                return org.parseStringOpts(file.read_text(), parse_opts)
            else:
                return org.parseFile(str(file.resolve()))

    if cache_file:
        with FileOperation.InOut([file], [cache_file]) as op:
            if op.should_run():
                log("haxorg.cache").info(f"{file} parsing")
                node = aux()

                if not cache_file.parent.exists():
                    cache_file.parent.mkdir()

                org.exportToProtobufFile(node, str(cache_file))

            else:
                log("haxorg.cache").info(f"{file} read from cache {cache_file}")
                node = org.readProtobufFile(str(cache_file))

            return node

    else:
        return aux()


@beartype
def parseFile(
    root: CliRootOptions,
    file: Path,
    parse_opts: Optional[org.OrgParseParameters] = None,
) -> org.Org:
    return parseCachedFile(file, root.cache, parse_opts=parse_opts)


def base_cli_options(f):
    return apply_options(f, options_from_model(CliRootOptions))
