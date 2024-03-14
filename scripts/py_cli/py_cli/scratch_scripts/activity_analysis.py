#!/usr/bin/env python

import py_exporters.export_sqlite as sql
from py_cli.haxorg_cli import *
from beartype.typing import List, Tuple
from beartype import beartype
from py_scriptutils.files import IsNewInput
from sqlalchemy import create_engine, Engine
from py_scriptutils.script_logging import log


CAT = "example.activity_analysis"

class ActivityAnalysisOptions(BaseModel):
    infile: List[Path]
    outdir: Path
    cachedir: Optional[Path] = None
    force_db: bool = False
    db_path: Optional[Path] = Field(
        default=None,
        description="Path to the generated SQLite DB, defaults to outdir/db.sqlite")


def analysis_options(f):
    return apply_options(f, options_from_model(ActivityAnalysisOptions))


@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@analysis_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs) -> None:
    pack_context(ctx, "root", ActivityAnalysisOptions, config=config, kwargs=kwargs)
    opts: ActivityAnalysisOptions = ctx.obj["root"]
    sql_db = opts.db_path if opts.db_path else opts.outdir.joinpath("db.sqlite")

    if opts.force_db or IsNewInput(input_path=opts.infile, output_path=[sql_db]):
        nodes: List[Tuple[org.Org, str]] = []
        for file in opts.infile:
            log(CAT).info(file)
            nodes.append((parseCachedFile(file, opts.cachedir), file.name))

        if sql_db.exists():
            sql_db.unlink()

        engine: Engine = create_engine("sqlite:///" + str(sql_db))
        sql.Base.metadata.create_all(engine)
        for node, file in nodes:
            sql.registerDocument(node, engine, file)

    else:
        engine: Engine = create_engine("sqlite:///" + str(sql_db))
        log(CAT).info("No DB update needed")
