#!/usr/bin/env python

from py_cli.haxorg_cli import (
    pack_context,
    BaseModel,
)

from py_scriptutils.toml_config_profiler import (
    make_config_provider,
    run_config_provider,
    apply_options,
    options_from_model,
    merge_cli_model,
)

from py_exporters.export_html import ExporterHtml, add_html, add_new

import py_haxorg.pyhaxorg_wrap as org

from pathlib import Path
from beartype import beartype
from dataclasses import dataclass, field
from beartype.typing import Optional, Tuple, List
import dominate.tags as tags
import dominate
from dominate.util import text


class StoryGridOpts(BaseModel, extra="forbid"):
    infile: Path
    outfile: Path


import rich_click as click


def cli_options(f):
    return apply_options(f, options_from_model(StoryGridOpts))


@beartype
@dataclass
class Header():
    title: List[org.Org]
    level: int
    tags: List[org.HashTag] = field(default_factory=list)
    location: Optional[List[org.Org]] = None
    pov: Optional[List[org.Org]] = None
    event: Optional[List[org.Org]] = None
    shift: Optional[Tuple[str, str]] = None
    duration: Optional[str] = None


def rec_filter_subnodes(node: org.Org, target: List[org.OrgSemKind]) -> List[org.Org]:
    result = []
    if node.getKind() in target:
        result.append(node)

    for sub in node:
        result += rec_filter_subnodes(sub, target)

    return result


@beartype
def rec_node(node: org.Org) -> List[Header]:
    result = []
    match node:
        case org.Subtree():
            title = [sub for sub in node.title]
            if isinstance(title[0], (org.Time, org.TimeRange)):
                title.pop(0)

                if isinstance(title[0], org.Space):
                    title.pop(0)

            header = Header(title=title, level=node.level)

            for tag in node.tags:
                header.tags.append(tag)

            result.append(header)
            for sub in node:
                if isinstance(sub, org.Subtree):
                    result += rec_node(sub)

                elif isinstance(sub, org.List):
                    if sub.isDescriptionList():
                        for item in sub:
                            tag = [w.text for w in rec_filter_subnodes(item.header, [
                                org.OrgSemKind.Word,
                                org.OrgSemKind.RawText,
                            ])] 

                            if len(tag) == 1:
                                match tag[0]:
                                    case "story_event":
                                        header.event = list(item.subnodes)

                                    case "story_location":
                                        header.location = list(item.subnodes)

                                    case "story_pov":
                                        header.pov = list(item.subnodes)

                                    case _:
                                        assert not tag[0].startswith("story_"), tag
                                        

        case org.Document():
            for sub in node:
                result += rec_node(sub)

    return result


def to_html(node: org.Org | List[org.Org]):
    if isinstance(node, list):
        html = []
        for item in node:
            exp = ExporterHtml()
            add_html(html, exp.exp.evalTop(item))

        return html

    else:
        html = ExporterHtml()
        return html.exp.evalTop(node)


@click.command()
@click.option("--config",
              type=click.Path(exists=True),
              default=None,
              help="Path to config file.")
@cli_options
@click.pass_context
def cli(ctx: click.Context, config: str, **kwargs) -> None:
    pack_context(ctx, "root", StoryGridOpts, config=config, kwargs=kwargs)
    opts: StoryGridOpts = ctx.obj["root"]
    ctx: org.OrgContext = org.OrgContext()
    # ctx.parseTracePath = "/tmp/parse.log"
    # ctx.tokenTracePath = "/tmp/token.log"
    node = ctx.parseFile(str(opts.infile.resolve()))
    headers = rec_node(node)

    with open("/tmp/res.txt", "w") as file:
        file.write(org.treeRepr(node, colored=False))

    doc = dominate.document()

    table = tags.table(border=1, style='border-collapse: collapse; width: 100%;')
    thead = tags.thead(style='position: sticky; top: 0; background-color: #ddd;')
    header_row = tags.tr()
    for header in ["title", "event", "location", "pov"]:
        header_row.add(tags.th(header))
    thead.add(header_row)
    table.add(thead)

    for h in headers:
        row = tags.tr()
        row.add(add_new(tags.td(), to_html(h.title)))

        def opt(it):
            if it:
                row.add(add_new(tags.td(), to_html(it)))

            else:
                row.add(text(""))

        opt(h.event)
        opt(h.location)
        opt(h.pov)

        table.add(row)


    doc.add(table)

    with open(opts.outfile, "w") as out:
        out.write(str(doc))

    print("parsed node ok")


if __name__ == "__main__":
    cli()
