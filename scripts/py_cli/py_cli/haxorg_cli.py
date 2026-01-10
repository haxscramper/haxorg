from pathlib import Path

import py_haxorg.pyhaxorg_wrap as org
import rich_click as click
from beartype import beartype
from beartype.typing import Optional, TypeVar, Dict, Any, List
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


def get_run(opts: RootOptions) -> CliRunContext:
    return CliRunContext(opts)


@beartype
def parseFile(
    opts: RootOptions,
    file: Path,
    parse_opts: Optional[org.OrgParseParameters] = None,
) -> org.Org:
    result: org.Org = None  # type: ignore
    if opts.follow_includes:
        dir_opts = org.OrgDirectoryParseParameters()
        if parse_opts:
            parse_opts.currentFile = str(file)

            def parse_node_impl(path: str) -> org.Org:
                return org.parseStringOpts(Path(path).read_text(), parse_opts)

            org.setGetParsedNode(dir_opts, parse_node_impl)

        result = org.parseFileWithIncludes(str(file.resolve()), dir_opts)
    else:
        if parse_opts:
            parse_opts.currentFile = str(file)
            result = org.parseStringOpts(file.read_text(), parse_opts)
        else:
            result = org.parseFile(str(file.resolve()))

    def get_file(dir: str, suffix: str) -> str:
        result = Path(dir).joinpath(f"{file.stem}").with_suffix(suffix)
        result.parent.mkdir(exist_ok=True, parents=True)
        return str(result)

    if opts.yamlDump_traceDir:
        org.exportToYamlFile(
            result, str(get_file(opts.yamlDump_traceDir, ".yaml")),
            org.OrgYamlExportOpts(
                skipNullFields=True,
                skipLocation=True,
            ))

    if opts.jsonDump_traceDir:
        org.exportToJsonFile(result, str(get_file(opts.jsonDump_traceDir, ".json")))

    if opts.treeDump_traceDir:
        org.exportToTreeFile(result, str(get_file(opts.treeDump_traceDir, ".txt")),
                             org.OrgTreeExportOpts())

    return result


@beartype
def parseCachedFile(
    opts: RootOptions,
    file: Path,
    parse_opts: Optional[org.OrgParseParameters] = None,
) -> org.Org:
    cache_file = None if not opts.cache else Path(opts.cache).joinpath(file.name)

    if cache_file:
        with FileOperation.InOut([file], [cache_file]) as op:
            if op.should_run():
                node = parseFile(opts, file, parse_opts)
                if not cache_file.parent.exists():
                    cache_file.parent.mkdir()

                org.exportToProtobufFile(node, str(cache_file))

            else:
                # log("haxorg.cache").info(f"{file} read from cache {cache_file}")
                node = org.readProtobufFile(str(cache_file))

            return node

    else:
        return parseFile(opts, file, parse_opts)


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

    parse_opts.currentFile = str(infile)

    return parse_opts


@beartype
def parseDirectory(opts: RootOptions, dir: Path) -> org.Org:
    dir_opts = org.OrgDirectoryParseParameters()

    def parse_node_impl(path: str) -> org.Org:
        try:
            result = parseCachedFile(
                opts,
                Path(path),
                parse_opts=getParseOpts(opts, Path(path)),
            )

            return result

        except Exception as e:
            log(CAT).error(f"Failed parsing {path}", exc_info=e)
            return org.Empty()

    org.setGetParsedNode(dir_opts, parse_node_impl)
    return org.parseDirectoryOpts(str(dir), dir_opts)


@beartype
def parsePathList(opts: RootOptions, paths: List[Path]) -> List[org.Org]:
    return [parseDirectory(opts, path) for path in paths]


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
