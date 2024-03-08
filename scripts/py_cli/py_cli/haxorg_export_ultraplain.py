from py_cli.haxorg_cli import *

class ExportUltraplainOptions(BaseModel):
    infile: Path
    outfile: Path
    exportTraceFile: Optional[str] = Field(
        description="Write python export trace to this file",
        default=None,
        alias="export_trace_file"
    )

def export_ultraplain_options(f):
    return apply_options(f, options_from_model(ExportUltraplainOptions))

@click.command("ultraplain")
@export_ultraplain_options
@click.pass_context
def export_ultraplain(ctx: click.Context, config: Optional[str] = None, **kwargs):
    pack_context(ctx, "ultraplain", ExportUltraplainOptions, config=config, kwargs=kwargs)
    opts: ExportUltraplainOptions = ctx.obj["ultraplain"]
    node = parseFile(ctx.obj["root"], opts.infile)
    from py_exporters.export_ultraplain import ExporterUltraplain
    exp = ExporterUltraplain()
    if opts.exportTraceFile:
        exp.exp.enableFileTrace(opts.exportTraceFile, False)

    with open(opts.outfile, "w") as file:
        exp.exp.evalTop(node)
        file.write(exp.result)

    log("haxorg.ultraplain").info(f"Finished DB write to {opts.outfile}")

