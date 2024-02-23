from haxorg_cli import *
from beartype.typing import List, Tuple

class ExportSQliteOptions(BaseModel):
    infile: List[Path]
    outfile: Path


def export_sqlite_options(f):
    return apply_options(f, options_from_model(ExportSQliteOptions))


@click.command("sqlite")
@export_sqlite_options
@click.pass_context
def export_sqlite(ctx: click.Context, config: Optional[str] = None, **kwargs):
    pack_context(ctx, "sqlite", ExportSQliteOptions, config=config, kwargs=kwargs)
    opts: ExportSQliteOptions = ctx.obj["sqlite"]
    nodes: List[Tuple[org.Org, str]] = [
        (parseFile(ctx.obj["root"], file), str(file)) for file in opts.infile
    ]
    from py_exporters.export_sqlite import registerDocument, Base
    from sqlalchemy import create_engine, Engine
    if opts.outfile.exists():
        opts.outfile.unlink()

    engine: Engine = create_engine("sqlite:///" + str(opts.outfile))
    Base.metadata.create_all(engine)
    for node, file in nodes:
        registerDocument(node, engine, file)

    log("haxorg.sql").info(f"Finished DB write to {opts.outfile}")

