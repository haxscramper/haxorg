from pathlib import Path

import py_haxorg.pyhaxorg_wrap as org
import rich_click as click
from beartype import beartype
from beartype.typing import Optional, TypeVar, Dict, Any
from py_scriptutils.files import FileOperation
from py_scriptutils.script_logging import log
from py_scriptutils.toml_config_profiler import (
    DefaultWrapperValue,
    apply_options,
    get_cli_model,
    get_user_provided_params,
    make_config_provider,
    merge_cli_model,
    options_from_model,
    run_config_provider,
    pack_context,
)
from py_scriptutils.tracer import TraceCollector
from py_cli.haxorg_opts import RootOptions

CONFIG_FILE_NAME = "pyhaxorg.toml"
CAT = __name__


@beartype
class CliRunContext:

    def __init__(self, opts: RootOptions) -> None:
        self.tracer = TraceCollector()
        self.opts = opts

    def event(self, name: str, category: str, args: Dict[str, Any] = {}) -> Any:
        return self.tracer.complete_event(name=name, category=category, args=args)

    def is_trace_enabled(self) -> bool:
        return bool(self.opts.trace_path)

    def finalize(self) -> None:
        if self.is_trace_enabled():
            assert self.opts.trace_path, "Missing trace path configuration"
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

    def aux() -> org.Org:
        if with_includes:
            opts = org.OrgDirectoryParseParameters()
            if parse_opts:
                parse_opts.currentFile = str(file)

                def parse_node_impl(path: str) -> org.Org:
                    return org.parseStringOpts(Path(path).read_text(), parse_opts)

                org.setGetParsedNode(opts, parse_node_impl)

            return org.parseFileWithIncludes(str(file.resolve()), opts)
        else:
            if parse_opts:
                parse_opts.currentFile = str(file)
                return org.parseStringOpts(file.read_text(), parse_opts)
            else:
                return org.parseFile(str(file.resolve()))

    if cache_file:
        with FileOperation.InOut([file], [cache_file]) as op:
            if op.should_run():
                # log("haxorg.cache").info(f"{file} parsing")
                node = aux()

                if not cache_file.parent.exists():
                    cache_file.parent.mkdir()

                org.exportToProtobufFile(node, str(cache_file))

            else:
                # log("haxorg.cache").info(f"{file} read from cache {cache_file}")
                node = org.readProtobufFile(str(cache_file))

            return node

    else:
        return aux()


@beartype
def parseFile(
    root: RootOptions,
    file: Path,
    parse_opts: Optional[org.OrgParseParameters] = None,
) -> org.Org:
    return parseCachedFile(file, root.cache, parse_opts=parse_opts)


@beartype
def getParseOpts(root: RootOptions, infile: Path) -> org.OrgParseParameters:
    parse_opts = org.OrgParseParameters()

    def get_file(dir: str) -> str:
        result = Path(dir).joinpath(infile.stem).with_suffix(".log")
        result.parent.mkdir(exist_ok=True, parents=True)
        return str(result)

    if root.baseToken_traceDir:
        parse_opts.baseTokenTracePath = get_file(root.baseToken_traceDir)

    if root.tokenizer_traceDir:
        parse_opts.tokenTracePath = get_file(root.tokenizer_traceDir)

    if root.sem_traceDir:
        parse_opts.semTracePath = get_file(root.sem_traceDir)

    if root.parse_traceDir:
        parse_opts.parseTracePath = get_file(root.parse_traceDir)

    parse_opts.currentFile = str(infile)

    return parse_opts


@beartype
def get_opts(ctx: click.Context) -> RootOptions:
    return pack_context(ctx, RootOptions, cli_kwargs=get_user_provided_params(ctx))


@beartype
def get_wrap_options(t: Any) -> Any:

    def analysis_options(f: Any) -> Any:
        return apply_options(f, options_from_model(t))

    return analysis_options


@beartype
def get_tmp_file(opts: RootOptions, path: str) -> Path:
    file = opts.tmp_dir.joinpath(path)
    file.parent.mkdir(parents=True, exist_ok=True)
    return file
