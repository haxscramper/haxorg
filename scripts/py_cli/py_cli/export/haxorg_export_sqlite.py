from beartype import beartype
from beartype.typing import Any
from beartype.typing import List
from beartype.typing import Optional
from beartype.typing import Tuple
from py_cli import haxorg_cli
from py_cli import haxorg_opts
import py_haxorg.pyhaxorg_wrap as org
import rich_click as click

CAT = "haxorg.export.sqlite"


@beartype
def export_sqlite(ctx: haxorg_cli.CliRunContext) -> None:
    assert ctx.opts.export
    assert ctx.opts.export.sqlite
    assert ctx.opts.export.sqlite.infile
    assert ctx.opts.export.sqlite.outfile
    with ctx.event("Run sqlite export", CAT):
        nodes: List[Tuple[org.Org, str]] = []

        with ctx.event("Parse input files", CAT):
            for file in ctx.opts.export.sqlite.infile:
                filesize = len(file.read_text()) if ctx.is_trace_enabled() else 0
                with ctx.event("Parse file", CAT, dict(
                        path=str(file),
                        size=filesize,
                )):
                    nodes.append((haxorg_cli.parseFile(ctx, file), str(file)))

        from py_exporters.export_sqlite import Base
        from py_exporters.export_sqlite import registerDocument
        from sqlalchemy import create_engine
        from sqlalchemy import Engine
        if ctx.opts.export.sqlite.outfile.exists():
            ctx.opts.export.sqlite.outfile.unlink()

        engine: Engine = create_engine("sqlite:///" + str(ctx.opts.export.sqlite.outfile))
        Base.metadata.create_all(engine)
        with ctx.event("Register all documents", CAT):
            for node, file_path in nodes:
                with ctx.event("Register document", CAT, dict(path=file_path)):
                    registerDocument(node, engine, file_path)

    ctx.finalize()


@click.command("sqlite")
@haxorg_cli.get_wrap_options(haxorg_opts.ExportSQliteOptions)
@click.pass_context
def export_sqlite_cli(ctx: click.Context, **kwargs: Any) -> None:
    export_sqlite(haxorg_cli.get_run(ctx))
