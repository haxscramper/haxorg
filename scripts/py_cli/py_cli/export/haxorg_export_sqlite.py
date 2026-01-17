from beartype.typing import List, Tuple, Any, Optional
from py_cli import haxorg_opts, haxorg_cli
import rich_click as click
import py_haxorg.pyhaxorg_wrap as org
from beartype import beartype

CAT = "haxorg.export.sqlite"


@beartype
def export_sqlite(opts: haxorg_opts.RootOptions,
                  run: Optional[haxorg_cli.CliRunContext] = None) -> None:

    if not run:
        run = haxorg_cli.get_run(opts) # type: ignore

    assert opts.export
    assert opts.export.sqlite
    assert opts.export.sqlite.infile
    assert opts.export.sqlite.outfile
    with run.event("Run sqlite export", CAT):
        nodes: List[Tuple[org.Org, str]] = []

        with run.event("Parse input files", CAT):
            for file in opts.export.sqlite.infile:
                filesize = len(file.read_text()) if run.is_trace_enabled() else 0
                with run.event("Parse file", CAT, dict(
                        path=str(file),
                        size=filesize,
                )):
                    nodes.append((haxorg_cli.parseFile(opts, file), str(file)))

        from py_exporters.export_sqlite import registerDocument, Base
        from sqlalchemy import create_engine, Engine
        if opts.export.sqlite.outfile.exists():
            opts.export.sqlite.outfile.unlink()

        engine: Engine = create_engine("sqlite:///" + str(opts.export.sqlite.outfile))
        Base.metadata.create_all(engine)
        with run.event("Register all documents", CAT):
            for node, file_path in nodes:
                with run.event("Register document", CAT, dict(path=file_path)):
                    registerDocument(node, engine, file_path)

    run.finalize()


@click.command("sqlite")
@haxorg_cli.get_wrap_options(haxorg_opts.ExportSQliteOptions)
@click.pass_context
def export_sqlite_cli(ctx: click.Context, **kwargs: Any) -> None:
    export_sqlite(haxorg_cli.get_opts(ctx))
