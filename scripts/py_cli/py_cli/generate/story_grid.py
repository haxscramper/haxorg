#!/usr/bin/env python

import dataclasses
import itertools
import statistics
from dataclasses import dataclass, field, fields
from datetime import datetime, timedelta
from numbers import Number
from pathlib import Path

import dominate
import dominate.tags as tags
import py_codegen.astbuilder_typst as typ
import py_haxorg.pyhaxorg_wrap as org
import py_wrappers.py_adaptagrams_wrap as cola
import rich_click as click
from beartype import beartype
from beartype.typing import Any, Dict, List, Optional, Tuple, Union
from dominate.util import text
from py_cli import haxorg_cli, haxorg_opts
from py_exporters.export_html import ExporterHtml, add_html, add_new
from py_exporters.export_ultraplain import ExporterUltraplain
from py_haxorg.pyhaxorg_utils import evalDateTime
from py_scriptutils.algorithm import maybe_splice
from py_scriptutils.script_logging import log, pprint_to_file, to_debug_json

CAT = "story-grid"


def cli_options(f: Any) -> Any:
    return haxorg_cli.apply_options(
        f, haxorg_cli.options_from_model(haxorg_opts.StoryGridOpts))


@beartype
@dataclass
class Header():
    title: List[org.Org]
    level: int
    words: Optional[int] = None
    duration: Optional[str] = None
    pov: Optional[List[org.Org]] = None
    location: Optional[List[org.Org]] = None
    value: Optional[List[org.Org]] = None
    note: Optional[List[org.Org]] = None
    event: Optional[List[org.Org]] = None
    turning_point: Optional[List[org.Org]] = None
    shift: Optional[Tuple[str, str]] = None
    tags: List[org.HashTag] = field(default_factory=list)
    time: Optional[Union[datetime, Tuple[datetime, datetime]]] = None
    nested: List["Header"] = field(default_factory=list)


@beartype
def rec_filter_subnodes(node: org.Org, target: List[org.OrgSemKind]) -> List[org.Org]:
    result: List[org.Org] = []
    if node is None:
        return result

    if node.getKind() in target:
        result.append(node)

    for sub in node:
        result += rec_filter_subnodes(sub, target)

    return result


osk = org.OrgSemKind


@beartype
def rec_node(node: org.Org) -> List[Header]:
    result: List[Header] = []
    match node:
        case org.Subtree():
            log(CAT).info(f"Subtree {node.getCleanTitle()}")
            if node.isComment or node.isArchived:
                return result

            title = [sub for sub in node.title]
            time = None
            if title and isinstance(title[0], (org.Time, org.TimeRange)):
                time = title.pop(0)
                if isinstance(title[0], org.Space):
                    title.pop(0)

            header = Header(title=title, level=node.level)

            if isinstance(time, org.Time):
                header.time = evalDateTime(time.getStatic().time)

            elif isinstance(time, org.TimeRange):
                header.time = (
                    evalDateTime(time.from_.getStatic().time),
                    evalDateTime(time.to.getStatic().time),
                )

            for prop in node.properties:
                match prop.getName():
                    case "story_polarity_shift":
                        plain = str(prop.getCustomRaw().value).strip()
                        header.shift = plain.split("/")

                    case "story_duration":
                        plain = str(prop.getCustomRaw().value).strip()
                        header.duration = plain

                    case _:
                        assert not prop.getName().startswith("story_"), prop.getName()

            for tag in node.tags:
                header.tags.append(tag)

            def count_words(node: org.Org) -> None:
                count = 0

                if node.getKind() in [osk.Word, osk.RawText]:
                    count += 1

                for sub in node:
                    count_words(sub)

                if count != 0:
                    if header.words:
                        header.words += count

                    else:
                        header.words = count

            for sub in node:
                if isinstance(sub, (org.Subtree, org.Document, org.CmdInclude, org.File)):
                    header.nested += rec_node(sub)

                elif isinstance(sub, org.List):
                    if sub.isDescriptionList():
                        for item in sub:
                            tag = [
                                w.text
                                for w in rec_filter_subnodes(item.header, [
                                    org.OrgSemKind.Word,
                                    org.OrgSemKind.RawText,
                                ])
                            ]

                            if len(tag) == 1:
                                match tag[0]:
                                    case "story_event":
                                        header.event = list(item.subnodes)

                                    case "story_turning_point":
                                        header.turning_point = list(item.subnodes)

                                    case "story_location":
                                        header.location = list(item.subnodes)

                                    case "story_pov":
                                        header.pov = list(item.subnodes)

                                    case "story_note":
                                        header.note = list(item.subnodes)

                                    case "story_value":
                                        header.value = list(item.subnodes)

                                    case "story_time":
                                        it = item.subnodes[0][0]
                                        match it:
                                            case org.Time():
                                                header.time = evalDateTime(
                                                    it.getStatic().time)

                                            case org.TimeRange():
                                                header.time = (
                                                    evalDateTime(
                                                        it.from_.getStatic().time),
                                                    evalDateTime(it.to.getStatic().time),
                                                )

                                    case _:
                                        assert not tag[0].startswith("story_"), tag

                    else:
                        count_words(sub)

                else:
                    count_words(sub)

            result.append(header)

        case org.Document() | org.CmdInclude() | org.File():
            for sub in node:
                result += rec_node(sub)

    return result


@beartype
def to_html(node: org.Org | List[org.Org] | str | int) -> Any:
    if isinstance(node, list):
        html: List[tags.html_tag] = []
        for item in node:
            add_html(html, to_html(item))

        return html

    elif isinstance(node, (str, int)):
        return text(str(node))

    else:
        html_exp = ExporterHtml()
        return html_exp.exp.evalTop(node)


@beartype
def format_time_difference(delta: timedelta) -> List[str]:
    # Define a year and a month in seconds for approximate calculation
    # Assuming an average month length of 30.44 days and a year of 365.25 days
    seconds_per_year = 365.25 * 24 * 60 * 60
    seconds_per_month = 30.44 * 24 * 60 * 60
    seconds_per_day = 24 * 60 * 60
    seconds_per_hour = 60 * 60
    seconds_per_minute = 60

    duration_parts = []
    # Calculate total difference in seconds
    diff_seconds = int(delta.total_seconds())

    # Calculate years, months, days, hours, minutes, and seconds
    years, diff_seconds = divmod(diff_seconds, int(seconds_per_year))
    months, diff_seconds = divmod(diff_seconds, int(seconds_per_month))
    days, diff_seconds = divmod(diff_seconds, seconds_per_day)
    hours, diff_seconds = divmod(diff_seconds, seconds_per_hour)
    minutes, seconds = divmod(diff_seconds, seconds_per_minute)

    # Append non-zero time periods to the duration_parts list
    if years > 0:
        duration_parts.append(f"{int(years)}y")
    if months > 0:
        duration_parts.append(f"{int(months)}m")
    if days > 0:
        duration_parts.append(f"{int(days)}d")
    if hours > 0:
        duration_parts.append(f"{int(hours)}h")
    if minutes > 0:
        duration_parts.append(f"{int(minutes)}min")
    if seconds > 0 or not duration_parts:
        duration_parts.append(f"{int(seconds)}s")

    return duration_parts


SKIP_FIELDS = ["level", "pov", "tags", "nested"]


@beartype
def get_html_story_grid(nested_headers: List[Header]) -> dominate.document:
    headers: List[Header] = []

    @beartype
    def aux(h: Header) -> None:
        headers.append(h)
        for sub in h.nested:
            aux(sub)

    for h in nested_headers:
        aux(h)

    assert all(isinstance(h, Header) for h in headers)

    doc = dominate.document(title="story_grid")

    table = tags.table(border=1, style='border-collapse: collapse; width: 100%;')
    thead = tags.thead(style='position: sticky; top: 0; background-color: #ddd;')
    header_row = tags.tr()

    for field in fields(Header([], 0)):
        if field.name in SKIP_FIELDS:
            continue

        elif field.name == "time":
            header_row.add(tags.th("delta"))

        header_row.add(tags.th(field.name))

    thead.add(header_row)
    table.add(thead)

    max_level = max(h.level for h in headers) * 1.0
    max_words = max((h.words or 0) for h in headers)

    for idx, h in enumerate(headers):
        row = tags.tr()

        def prev_time() -> Optional[Union[datetime, Tuple[datetime, datetime]]]:
            offset = 1
            while 0 <= (idx - offset):
                prev_h = headers[idx - offset]
                if isinstance(prev_h.time, (datetime, tuple)):
                    return prev_h.time

                else:
                    offset += 1

            return None

        def opt(it: Any, **kwargs: Any) -> None:
            if it:
                row.add(add_new(tags.td(**kwargs), to_html(it)))

            else:
                row.add(tags.td(**kwargs))

        for field in fields(h):
            opacity = (max_level - h.level) / max_level * 0.75
            header_style = f"background-color: rgba(255, 0, 0, {opacity:.2f});"
            cell_args = dict()
            # if 0 < len(h.nested):
            #     cell_args["style"] = header_style

            if field.name in SKIP_FIELDS:
                continue

            elif field.name == "title":
                prefix = f"#{idx} " + "*" * h.level + " "
                row.add(
                    add_new(
                        tags.td(style=header_style),
                        [to_html(prefix), to_html(h.title)],
                    ))

            elif field.name == "words":
                if h.words:
                    opacity = h.words / (max_words * 1.0)
                    row.add(
                        add_new(
                            tags.td(
                                style=f"background-color: rgba(0, 255, 0, {opacity:.2f});"
                            ), to_html(h.words)))

                else:
                    opt(h.words, **cell_args)

            elif field.name == "time":
                if h.time:
                    prev = prev_time()
                    offset = ""
                    start, end = (h.time,
                                  None) if isinstance(h.time, datetime) else h.time
                    if prev:
                        prev_start, prev_end = (prev, None) if isinstance(
                            prev, datetime) else prev
                        offset += "{}".format(" ".join(
                            format_time_difference(start - prev_start)[:2]))

                    if isinstance(h.time, datetime):
                        opt(offset, **cell_args)
                        opt("{}".format(start.strftime("[%Y-%m-%d]")), **cell_args)

                    else:
                        opt(offset, **cell_args)
                        opt(
                            "{}-{}".format(
                                start.strftime("[%Y-%m-%d]"),
                                end.strftime("[%Y-%m-%d]"),
                            ),
                            **cell_args,
                        )

                else:
                    opt("", **cell_args)
                    opt("", **cell_args)

            elif field.name == "shift":
                value = getattr(h, field.name)
                if value:
                    opt("/".join(value), **cell_args)

                else:
                    opt("", **cell_args)

            else:
                opt(getattr(h, field.name), **cell_args)

        table.add(row)

    doc.add(table)

    return doc


@beartype
@dataclass
class Cell():
    content: str
    rect_idx: int = -1
    debug: Dict[str, Any] = field(default_factory=dict)
    field: Optional[dataclasses.Field] = None


TYP_SKIP_FIELDS = SKIP_FIELDS + ["title", "words"]


@beartype
def get_typ_content(h: Header) -> List[dataclasses.Field[Any]]:
    return [f for f in fields(h) if f.name not in TYP_SKIP_FIELDS]


@beartype
def get_typ_cols(t: Header) -> int:
    subs = [get_typ_cols(s) for s in t.nested]
    content = get_typ_content(t)
    if len(subs) == 1:
        return max(subs[0], len(content))

    elif 1 < len(subs):
        return max(max(*subs), len(content))

    else:
        return len(content)


@beartype
def get_typ_rows(t: Header) -> int:
    res = sum(get_typ_rows(s) for s in t.nested) + 1
    content = get_typ_content(t)
    # res += 1
    return res


@beartype
def init_grid(
    row_count: int,
    col_count: int,
    max_depth: int,
    root: Header,
    ir: cola.GraphLayout,
    mult: float,
) -> List[List[Optional[Cell]]]:

    #[row][col]
    grid: List[List[Optional[Cell]]] = [[None] * col_count for _ in range(0, row_count)]
    dfs_row: int = 0

    def debug_grid() -> None:

        def fmt_cell(cell: Optional[Cell]) -> str:
            if cell == None:
                return "[" + "_" * 7 + "]"

            else:
                return f"{cell.rect_idx:>02} {cell.content}"[0:9].center(9, " ")

        grid_fmt = "\n".join(" ".join(fmt_cell(cell) for cell in row) for row in grid)

        Path("/tmp/grid_fmt.txt").write_text(grid_fmt)

        pprint_to_file(
            to_debug_json(grid),
            "/tmp/grid_debug.py",
            width=240,
        )

    rect_inset = 5
    rect_width = 40

    def aux(h: Header, level: int) -> None:
        nonlocal dfs_row
        this_row = dfs_row

        def rect_textsize(fmt_field: str) -> float:
            return ((float(len(fmt_field) * 5) / rect_width) + 1) * mult

        def rect_for_content(fmt_field: str) -> int:
            return ir.rect(
                width=int(rect_width * mult),
                height=int(rect_textsize(fmt_field)) + (rect_inset * 2),
            )

        title_text = "".join([ExporterUltraplain.getStr(it) for it in h.title])

        def set_cell(row: int, col: int, text: str, **kwargs: Any) -> None:
            rect = rect_for_content(text)
            grid[row][col] = Cell(
                content=text,
                rect_idx=rect,
                debug=dict(
                    width=ir.ir.rectangles[rect].width(),
                    height=ir.ir.rectangles[rect].height(),
                    textlen=len(text),
                    textsize=int(rect_textsize(text)),
                ),
                **kwargs,
            )

        set_cell(
            dfs_row,
            level,
            title_text,
            field=[f for f in fields(h) if f.name == "title"][0],
        )

        content = get_typ_content(h)
        # dfs_row += 1
        for cell_idx, field in enumerate(content):
            fmt_field: str = ""
            value = getattr(h, field.name)
            if value == None:
                continue

            assert field.name not in TYP_SKIP_FIELDS
            match value:
                case list():
                    for it in value:
                        match it:
                            case org.Org():
                                fmt_field += ExporterUltraplain.getStr(it)

                            case str():
                                fmt_field += it

                            case _:
                                raise TypeError(type(it))

                case _:
                    fmt_field = str(value)

            set_cell(
                dfs_row,
                max_depth + cell_idx,
                fmt_field,
                field=field,
            )

        # debug_grid()

        source_rect = grid[this_row][level].rect_idx
        for i in range(0, len(grid[dfs_row]) - max_depth):
            if grid[dfs_row][max_depth + i] != None:
                target_rect = grid[dfs_row][max_depth + i].rect_idx

                ir.edge(source=source_rect, target=target_rect)
                ir.edgePorts(
                    source=source_rect,
                    target=target_rect,
                    sourcePort=cola.GraphEdgeConstraintPort.East,
                    targetPort=cola.GraphEdgeConstraintPort.West,
                )

                break

        content_offsets = [
            idx for idx in range(0, len(content)) if grid[dfs_row][max_depth + idx]
        ]
        for src_index, dst_index in itertools.pairwise(content_offsets):
            source_rect = grid[dfs_row][max_depth + src_index].rect_idx
            target_rect = grid[dfs_row][max_depth + dst_index].rect_idx

            ir.edge(source=source_rect, target=target_rect)
            ir.edgePorts(
                source=source_rect,
                target=target_rect,
                sourcePort=cola.GraphEdgeConstraintPort.East,
                targetPort=cola.GraphEdgeConstraintPort.West,
            )

        dfs_row += 1
        sub_rows: List[int] = []

        for s in h.nested:
            sub_rows.append(dfs_row)
            aux(s, level + 1)

        for row in sub_rows:
            source_rect = grid[this_row][level].rect_idx
            target_rect = grid[row][level + 1].rect_idx

            ir.edge(source=source_rect, target=target_rect)
            ir.edgePorts(
                source=source_rect,
                target=target_rect,
                sourcePort=cola.GraphEdgeConstraintPort.South,
                targetPort=cola.GraphEdgeConstraintPort.West,
            )

    aux(root, 0)
    debug_grid()

    return grid


@beartype
def add_typ_constraints(
    ir: cola.GraphLayout,
    grid: List[List[Optional[Cell]]],
    col_count: int,
    row_count: int,
    mult: Number,
) -> None:
    y_aligns: List[cola.GraphNodeConstraintAlign] = []
    x_aligns: List[cola.GraphNodeConstraintAlign] = []
    vertical_sizes: List[int] = []
    horizontal_sizes: List[int] = []

    for row in grid:
        row_nodes: List[int] = [cell.rect_idx for cell in row if cell]
        if 0 < len(row_nodes):
            vertical_sizes.append(
                int(
                    statistics.mean(ir.ir.rectangles[idx].height() for idx in row_nodes) +
                    1))

            y_aligns.append(ir.newAlignY(row_nodes))

    ir.separateYDimN(
        y_aligns,
        distance=float(max(vertical_sizes) + 10),
        isExactSeparation=True,
    )

    for col in range(0, col_count):
        col_nodes: List[int] = [row[col].rect_idx for row in grid if row[col]]
        if 0 < len(col_nodes):
            horizontal_sizes.append(
                int(
                    statistics.mean(ir.ir.rectangles[idx].width() for idx in col_nodes) +
                    1))

            x_aligns.append(ir.newAlignX(col_nodes))

    ir.separateXDimN(
        x_aligns,
        distance=float(statistics.mean(horizontal_sizes) + 5),
        isExactSeparation=True,
    )

    ir.ir.width = 100 * mult * col_count
    ir.ir.height = 100 * mult * row_count
    ir.ir.leftBBoxMargin = 100
    ir.ir.rightBBoxMargin = 100
    ir.ir.topBBoxMargin = 100
    ir.ir.bottomBBoxMargin = 100


@beartype
def get_typ_content_rect(
    ast: typ.ASTBuilder,
    cell: Cell,
    rect: cola.GraphRect,
    add_debug: bool = False,
) -> Any:
    text = [ast.string(ast.escape(cell.content.replace("\n", " ")))]

    def get_args(color: str) -> dict:
        return dict(
            fill=ast.litRaw(f"{color}.lighten(80%)"),
            stroke=ast.litRaw(f"{color}"),
            inset=ast.litPt(3),
            radius=ast.litPt(3),
            # baseline=ast.litRaw("20%"),
        )

    if add_debug:
        for key in sorted(cell.debug.keys()):
            text.append(
                ast.call(
                    name="box",
                    args=get_args("blue"),
                    body=[ast.string(key)],
                    isLine=True,
                ))

            text.append(
                ast.call(
                    name="box",
                    args=get_args("green"),
                    body=[ast.string(ast.escape(str(cell.debug[key])))],
                    isLine=True,
                ))

    return ast.call(
        "rect",
        args=dict(
            width=ast.litPt(rect.width),
            height=ast.litPt(rect.height),
            radius=ast.litPt(5),
        ),
        isLine=True,
        body=ast.call(
            name="align",
            positional=[ast.litRaw("center + horizon")],
            body=ast.line(*text),
            isLine=True,
        ),
    )


@beartype
def add_typ_nodes(
    ast: typ.ASTBuilder,
    page: typ.BlockId,
    conv: cola.GraphLayoutIRResult,
    grid: List[List[Optional[Cell]]],
) -> None:
    for row in grid:
        for cell in row:
            if cell == None:
                continue

            rect_idx = cell.rect_idx
            rect = conv.fixed[rect_idx]

            def get_field_name_rect() -> None:
                return ast.litRaw(
                    ast.place(
                        anchor="top + left",
                        body=ast.content(
                            ast.call(
                                name="rect",
                                args=dict(
                                    fill=ast.litRaw("red.lighten(80%)"),
                                    stroke=ast.litRaw("red"),
                                    radius=ast.litPt(2),
                                    inset=ast.litPt(2),
                                ),
                                body=[ast.string(cell.field.name)],
                                isLine=True,
                            )),
                        dx=0,
                        dy=-15,
                        isLine=True,
                    ))

            ast.add_at(
                page,
                ast.place(
                    anchor="top + left",
                    dx=rect.left,
                    dy=rect.top,
                    body=ast.content(
                        [
                            *maybe_splice(
                                cell.field,
                                cell.field and get_field_name_rect(),
                            ),
                            get_typ_content_rect(
                                ast=ast,
                                add_debug=False,
                                cell=cell,
                                rect=rect,
                            ),
                        ],
                        isLine=True,
                    ),
                    isLine=True,
                ))


@beartype
def add_typ_edges(
    ast: typ.ASTBuilder,
    page: typ.BlockId,
    conv: cola.GraphLayoutIRResult,
) -> None:
    for targets, edge in conv.lines.items():
        for path in edge.paths:
            x0 = path.points[0].x
            y0 = path.points[0].y
            ast.add_at(
                page,
                ast.call(
                    "place",
                    positional=[
                        ast.litRaw("top + left"),
                        ast.litRaw(
                            ast.call(
                                "path",
                                args=dict(stroke=ast.litRaw("blue"),),
                                post_positional=[
                                    ast.litRaw(
                                        ast.expr(
                                            [
                                                ast.litPt(pt.x - x0),
                                                ast.litPt(pt.y - y0),
                                            ],
                                            isLine=True,
                                        )) for pt in path.points
                                ],
                                isLine=True,
                                isFirst=False,
                            ))
                    ],
                    args=dict(
                        dx=ast.litPt(x0),
                        dy=ast.litPt(y0),
                    ),
                    isLine=True,
                ))


@beartype
def get_typst_story_grid(headers: List[Header]) -> None:
    root = Header([], 0)
    root.nested = headers

    def get_depth(t: Header) -> None:
        subs = [get_depth(s) for s in t.nested]
        if 1 < len(subs):
            return max(*subs) + 1

        elif len(subs) == 1:
            return subs[0] + 1

        else:
            return 1

    max_depth = get_depth(root)
    col_count = max_depth + get_typ_cols(root)
    row_count = get_typ_rows(root) + 1
    ir = cola.GraphLayout()
    mult = 5.0

    grid = init_grid(
        row_count=row_count,
        col_count=col_count,
        max_depth=max_depth,
        mult=mult,
        root=root,
        ir=ir,
    )

    add_typ_constraints(
        ir=ir,
        grid=grid,
        col_count=col_count,
        row_count=row_count,
        mult=mult,
    )

    log(CAT).info("doing layout")
    # conv = ir.ir.doGraphvizConvert()
    conv = ir.ir.doColaConvert()
    log(CAT).info("done layout")

    svg_doc = cola.svg.toSvgFileText(
        cola.toSvg(
            conv,
            ir=ir.ir,
            draw_geometric_positions=False,
        ))
    Path("/tmp/result2.svg").write_text(str(svg_doc))
    log(CAT).info("saved to SVG file")

    ast = typ.ASTBuilder()

    page = ast.stack([])
    ast.add_at(
        page,
        ast.set(
            "page",
            args=dict(
                height=ast.litPt(int(conv.bbox.height)),
                width=ast.litPt(int(conv.bbox.width)),
                margin=dict(
                    top=ast.litPt(0),
                    left=ast.litPt(0),
                    right=ast.litPt(0),
                    bottom=ast.litPt(0),
                ),
            ),
        ))

    ast.add_at(page, ast.set("par", args=dict(justify=ast.litRaw("true"))))
    add_typ_nodes(ast=ast, page=page, conv=conv, grid=grid)
    add_typ_edges(ast=ast, page=page, conv=conv)
    Path("/tmp/result.typ").write_text(ast.toString(page))


@click.command("story_grid")
@cli_options
@click.pass_context
def story_grid_cli(ctx: click.Context, config: str, **kwargs: Any) -> None:
    opts = haxorg_cli.get_opts(ctx, config)
    assert opts.generate
    assert opts.generate.story_grid
    node = haxorg_cli.parseFile(opts, Path(opts.generate.story_grid.infile))
    headers = rec_node(node)

    doc = get_html_story_grid(headers)
    Path(opts.generate.story_grid.outfile).write_text(str(doc))

    typst = get_typst_story_grid(headers)


if __name__ == "__main__":
    story_grid_cli()
