from py_cli.haxorg_cli import *
from beartype.typing import List, Tuple


class ExportSQliteOptions(BaseModel):
    infile: List[Path]
    outfile: Path


CAT = "haxorg.export.sqlite"


def export_sqlite_options(f):
    return apply_options(f, options_from_model(ExportSQliteOptions))


@click.command("sqlite")
@export_sqlite_options
@click.pass_context
def export_sqlite(ctx: click.Context, config: Optional[str] = None, **kwargs):
    pack_context(ctx, "sqlite", ExportSQliteOptions, config=config, kwargs=kwargs)
    run = get_run(ctx)
    with run.event("Run sqlite export", CAT):
        opts: ExportSQliteOptions = ctx.obj["sqlite"]
        nodes: List[Tuple[org.Org, str]] = []

        with run.event("Parse input files", CAT):
            for file in opts.infile:
                filesize = len(file.read_text()) if run.is_trace_enabled() else 0
                with run.event("Parse file", CAT, dict(
                        path=str(file),
                        size=filesize,
                )):
                    nodes.append((parseFile(ctx.obj["root"], file), str(file)))

        from py_exporters.export_sqlite import registerDocument, Base
        from sqlalchemy import create_engine, Engine
        if opts.outfile.exists():
            opts.outfile.unlink()

        engine: Engine = create_engine("sqlite:///" + str(opts.outfile))
        Base.metadata.create_all(engine)
        with run.event("Register all documents", CAT):
            for node, file in nodes:
                with run.event("Register document", CAT, dict(path=str(file))):
                    registerDocument(node, engine, file)

    run.finalize()
