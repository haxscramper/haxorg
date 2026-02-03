from pathlib import Path
import time

from beartype import beartype
from beartype.typing import Any
from beartype.typing import Dict
from beartype.typing import List
from beartype.typing import Optional
from beartype.typing import TypeVar
from py_cli.haxorg_opts import RootOptions
import py_haxorg.pyhaxorg_wrap as org
from py_scriptutils.files import FileOperation
from py_scriptutils.script_logging import log
from py_scriptutils.toml_config_profiler import apply_options
from py_scriptutils.toml_config_profiler import DefaultWrapperValue
from py_scriptutils.toml_config_profiler import get_cli_model
from py_scriptutils.toml_config_profiler import get_user_provided_params
from py_scriptutils.toml_config_profiler import make_config_provider
from py_scriptutils.toml_config_profiler import merge_cli_model
from py_scriptutils.toml_config_profiler import options_from_model
from py_scriptutils.toml_config_profiler import pack_context
from py_scriptutils.toml_config_profiler import run_config_provider
from py_scriptutils.tracer import TraceCollector
import rich.highlighter
import rich.text
import rich_click as click

CONFIG_FILE_NAME = "pyhaxorg.toml"
CAT = __name__


@beartype
class CliRunContext:

    def __init__(self, opts: RootOptions) -> None:
        self.tracer = TraceCollector()
        self.opts = opts
        self.parse = org.ParseContext()

    def event(self, name: str, category: str, args: Dict[str, Any] = {}) -> Any:
        return self.tracer.complete_event(name=name, category=category, args=args)

    def is_trace_enabled(self) -> bool:
        return bool(self.opts.trace_path)

    def finalize(self) -> None:
        if self.is_trace_enabled():
            assert self.opts.trace_path, "Missing trace path configuration"
            self.tracer.export_to_json(Path(self.opts.trace_path))
            log("haxorg.cli").info(f"Wrote execution trace to {self.opts.trace_path}")


@beartype
def parseFile(
    ctx: CliRunContext,
    file: Path,
    parse_opts: Optional[org.OrgParseParameters] = None,
) -> org.Org:
    result: org.Org = None  # type: ignore
    if ctx.opts.follow_includes:
        dir_opts = org.OrgDirectoryParseParameters()
        if parse_opts:

            def parse_node_impl(path: str) -> org.Org:
                return ctx.parse.parseFileOpts(path, parse_opts)

            org.setGetParsedNode(dir_opts, parse_node_impl)

        log(CAT).info(f"Parse file with includes {file}")
        result = ctx.parse.parseFileWithIncludes(str(file.resolve()), dir_opts)
    else:
        if parse_opts:
            result = ctx.parse.parseFileOpts(str(file.resolve()), parse_opts)
        else:
            result = ctx.parse.parseFile(str(file.resolve()))

    def get_file(dir: str, suffix: str) -> str:
        result = Path(dir).joinpath(f"{file.stem}").with_suffix(suffix)
        result.parent.mkdir(exist_ok=True, parents=True)
        return str(result)

    if ctx.opts.yamlDump_traceDir:
        org.exportToYamlFile(
            result, str(get_file(ctx.opts.yamlDump_traceDir, ".yaml")),
            org.OrgYamlExportOpts(
                skipNullFields=True,
                skipLocation=True,
            ))

    if ctx.opts.jsonDump_traceDir:
        org.exportToJsonFile(result, str(get_file(ctx.opts.jsonDump_traceDir, ".json")))

    if ctx.opts.treeDump_traceDir:
        org.exportToTreeFile(result, str(get_file(ctx.opts.treeDump_traceDir, ".txt")),
                             org.OrgTreeExportOpts())

    return result


@beartype
def parseCachedFile(
    ctx: CliRunContext,
    file: Path,
    parse_opts: Optional[org.OrgParseParameters] = None,
) -> org.Org:
    cache_file = None if not ctx.opts.cache else Path(ctx.opts.cache).joinpath(file.name)

    if cache_file:
        with FileOperation.InOut([file], [cache_file]) as op:
            if op.should_run():
                node = parseFile(ctx, file, parse_opts)
                if not cache_file.parent.exists():
                    cache_file.parent.mkdir()

                org.exportToProtobufFile(node, str(cache_file))

            else:
                # log("haxorg.cache").info(f"{file} read from cache {cache_file}")
                node = org.readProtobufFile(str(cache_file))

            return node

    else:
        return parseFile(ctx, file, parse_opts)


@beartype
def getParseOpts(root: RootOptions, infile: Path) -> org.OrgParseParameters:
    parse_opts = org.OrgParseParameters()

    def get_file(dir: str, type: str) -> str:
        result = Path(dir).joinpath(f"{infile.stem}_{type}").with_suffix(".log")
        result.parent.mkdir(exist_ok=True, parents=True)
        return str(result)

    if root.baseToken_traceDir:
        parse_opts.baseTokenTracePath = get_file(root.baseToken_traceDir, "base_token")

    if root.tokenizer_traceDir:
        parse_opts.tokenTracePath = get_file(root.tokenizer_traceDir, "tokenizer")

    if root.sem_traceDir:
        parse_opts.semTracePath = get_file(root.sem_traceDir, "sem")

    if root.parse_traceDir:
        parse_opts.parseTracePath = get_file(root.parse_traceDir, "parse")

    return parse_opts


@beartype
def parseDirectory(ctx: CliRunContext, dir: Path) -> org.Org:
    dir_opts = org.OrgDirectoryParseParameters()

    def parse_node_impl(path: str) -> org.Org:
        try:
            start = time.perf_counter()
            result = parseCachedFile(
                ctx,
                Path(path),
                parse_opts=getParseOpts(ctx.opts, Path(path)),
            )

            elapsed = time.perf_counter() - start

            log(CAT).info(f"Parsed '{path}' in {elapsed:.3f} sec")

            return result

        except Exception as e:
            message = rich.highlighter.ReprHighlighter()(
                rich.text.Text(f"Failed parsing '{path}'"))

            for line in str(e).split("\n")[:10]:
                message.append(rich.text.Text(f"\n{line}", style="dim"))

            log(CAT).error(message,
                           extra={
                               "highlighter": rich.highlighter.NullHighlighter(),
                               "markup": True,
                           })

            return org.Empty()

    org.setGetParsedNode(dir_opts, parse_node_impl)
    return ctx.parse.parseDirectoryOpts(str(dir), dir_opts)


@beartype
def parsePathList(ctx: CliRunContext, paths: List[Path]) -> List[org.Org]:
    return [parseDirectory(ctx, path) for path in paths]


@beartype
def get_opts(ctx: click.Context) -> RootOptions:
    return pack_context(ctx, RootOptions, cli_kwargs=get_user_provided_params(ctx))


@beartype
def get_run(opts: RootOptions | click.Context) -> CliRunContext:
    if isinstance(opts, RootOptions):
        return CliRunContext(opts)

    else:
        return CliRunContext(get_opts(opts))


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
