from __future__ import annotations

from dataclasses import dataclass
import html
from pathlib import Path
from typing import Literal

from dominate import document
from dominate.tags import a, body, div, head, meta, script, style
from dominate.util import raw
import graphviz
import igraph as ig
import py_codegen.proto_lib as pb


@dataclass(frozen=True)
class IncludeTreeNode:
    visit: pb.IncludeVisit
    node_id: str
    path_key: str
    parent_id: str | None
    parent_row_index: int | None


def create_include_tree_graph(
    visit: pb.IncludeVisit,
    *,
    root_dir: str | Path | None = None,
) -> tuple[graphviz.Digraph, ig.Graph]:
    dot = graphviz.Digraph("include_tree")
    dot.attr("graph", rankdir="LR")
    dot.attr("node", shape="plain")

    graph = ig.Graph(directed=True)
    cumulative_cache: dict[int, int] = {}
    kept_cache: dict[int, bool] = {}

    root_path = Path(root_dir).resolve() if root_dir is not None else None

    def visit_path(v: pb.IncludeVisit) -> Path | None:
        path = v.absolute_path or v.relative_path
        if not path:
            return None
        return Path(path).resolve()

    def is_kept(v: pb.IncludeVisit) -> bool:
        key = id(v)
        if key in kept_cache:
            return kept_cache[key]

        if root_path is None:
            result = True
        else:
            path = visit_path(v)
            if path is None:
                result = False
            else:
                result = root_path == path or root_path in path.parents

        kept_cache[key] = result
        return result

    def cumulative_used(v: pb.IncludeVisit) -> int:
        key = id(v)
        if key in cumulative_cache:
            return cumulative_cache[key]
        total = int(v.used_line_count)
        for ch in v.nested:
            if is_kept(ch):
                total += cumulative_used(ch)
        cumulative_cache[key] = total
        return total

    def progress_table_html(percent: float) -> str:
        clamped = max(0.0, min(100.0, percent))
        text = f"{int(round(clamped)):d}%"
        return (
            '<TABLE BORDER="0" CELLBORDER="1" CELLSPACING="0">'
            "<TR>"
            f'<TD WIDTH="60" ALIGN="RIGHT">{html.escape(text)}</TD>'
            '<TD WIDTH="120" HEIGHT="10" FIXEDSIZE="TRUE" CELLPADDING="0">'
            '<TABLE BORDER="0" CELLBORDER="0" CELLSPACING="0" CELLPADDING="0" WIDTH="120">'
            "<TR>"
            f'<TD BGCOLOR="#4caf50" WIDTH="{clamped:.2f}%"></TD>'
            f'<TD BGCOLOR="#e0e0e0" WIDTH="{100.0 - clamped:.2f}%"></TD>'
            "</TR>"
            "</TABLE>"
            "</TD>"
            "</TR>"
            "</TABLE>")

    def node_label(v: pb.IncludeVisit) -> str:
        title = html.escape(v.relative_path or v.absolute_path or "<root>")
        physical = int(v.file_line_count)
        used_sum = cumulative_used(v)

        children = [ch for ch in v.nested if is_kept(ch)]
        child_rows = []
        for ch in children:
            used = cumulative_used(ch)
            share = 0.0 if used_sum == 0 else (used / used_sum) * 100.0
            rel = html.escape(ch.relative_path or ch.absolute_path or "<unknown>")
            child_rows.append((rel, used, int(ch.file_line_count), share))

        child_rows.sort(key=lambda item: item[1], reverse=True)

        rows = [
            "<TR>",
            f'<TD COLSPAN="4"><B>{title}</B></TD>',
            '<TD><FONT POINT-SIZE="10">'
            '<TABLE BORDER="0" CELLBORDER="1" CELLSPACING="0">'
            f"<TR><TD ALIGN=\"LEFT\">physical</TD><TD>{physical}</TD></TR>"
            f"<TR><TD ALIGN=\"LEFT\">used sum</TD><TD>{used_sum}</TD></TR>"
            "</TABLE>"
            "</FONT></TD>",
            "</TR>",
            "<TR>"
            "<TD><B>include</B></TD>"
            "<TD><B>used Σ</B></TD>"
            "<TD><B>lines</B></TD>"
            "<TD><B>% of used</B></TD>"
            "<TD><B>to</B></TD>"
            "</TR>",
        ]

        for i, (rel, used, lines, share) in enumerate(child_rows):
            progress = progress_table_html(share)
            rows.append("<TR>"
                        f'<TD ALIGN="LEFT">{rel}</TD>'
                        f"<TD>{used}</TD>"
                        f"<TD>{lines}</TD>"
                        f"<TD>{progress}</TD>"
                        f'<TD PORT="p{i}">→</TD>'
                        "</TR>")

        return ("<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">" +
                "".join(rows) + "</TABLE>>")

    seq = 0
    graph_nodes: list[IncludeTreeNode] = []

    def add_vertex_record(
        v: pb.IncludeVisit,
        node_id: str,
        parent_id: str | None,
        parent_row_index: int | None,
    ) -> None:
        graph.add_vertex(
            name=node_id,
            label=v.relative_path or v.absolute_path or "<root>",
            absolute_path=v.absolute_path or "",
            relative_path=v.relative_path or "",
            physical_lines=int(v.file_line_count),
            used_lines=int(v.used_line_count),
            cumulative_used_lines=cumulative_used(v),
            parent_id=parent_id or "",
            parent_row_index=-1 if parent_row_index is None else parent_row_index,
        )
        graph_nodes.append(
            IncludeTreeNode(
                visit=v,
                node_id=node_id,
                path_key=v.absolute_path or v.relative_path or node_id,
                parent_id=parent_id,
                parent_row_index=parent_row_index,
            ))

    def emit(
        v: pb.IncludeVisit,
        *,
        parent_id: str | None,
        parent_row_index: int | None,
    ) -> str:
        nonlocal seq
        node_id = f"n{seq}"
        seq += 1

        add_vertex_record(v, node_id, parent_id, parent_row_index)
        dot.node(node_id, node_label(v))

        children = [ch for ch in v.nested if is_kept(ch)]
        child_rows = []
        for ch in children:
            child_rows.append((
                ch,
                cumulative_used(ch),
                int(ch.file_line_count),
                ch.relative_path or ch.absolute_path or "<unknown>",
            ))

        child_rows.sort(key=lambda item: item[1], reverse=True)

        for row_index, (ch, _used, _lines, _name) in enumerate(child_rows):
            child_id = emit(
                ch,
                parent_id=node_id,
                parent_row_index=row_index,
            )
            dot.edge(f"{node_id}:p{row_index}:e", child_id)
            graph.add_edge(
                node_id,
                child_id,
                parent_row_index=row_index,
            )

        return node_id

    emit(visit, parent_id=None, parent_row_index=None)
    return dot, graph


def write_include_tree_html(
    dot: graphviz.Digraph,
    graph: ig.Graph,
    output_html: str | Path,
    *,
    root_dir: str | Path | None = None,
) -> None:
    svg = dot.pipe(format="svg").decode("utf-8")

    doc = document(title="Include tree")
    with doc:
        with head():
            meta(charset="utf-8")
            style("""
                html, body {
                    margin: 0;
                    padding: 0;
                    height: 100%;
                    font-family: sans-serif;
                }

                #app {
                    width: 100%;
                    height: 100vh;
                    overflow: auto;
                    background: #ffffff;
                }

                #app svg {
                    width: max-content;
                    height: auto;
                    display: block;
                }

                .include-arrow-hit {
                    cursor: pointer;
                }

                .include-focus {
                    outline: 3px solid #ff9800;
                    outline-offset: 4px;
                }
                """)

        edge_list = graph.get_edgelist()
        edge_names = [
            (graph.vs[src]["name"], graph.vs[dst]["name"]) for src, dst in edge_list
        ]
        edge_rows = (list(graph.es["parent_row_index"]) if "parent_row_index"
                     in graph.es.attribute_names() else [-1] * len(edge_list))

        with body():
            with div(id="app"):
                raw(svg)
            script(
                raw(f"""
                    const EDGE_DATA = {edge_list};
                    const EDGE_ROWS = {edge_rows};
                    const EDGE_NAMES = {edge_names};

                    function getSvgRoot() {{
                        return document.querySelector('#app svg');
                    }}

                    function getGraphRootGroup() {{
                        const svg = getSvgRoot();
                        if (!svg) {{
                            return null;
                        }}
                        return svg.querySelector('g.graph');
                    }}

                    function getNodeGroup(nodeId) {{
                        const graphRoot = getGraphRootGroup();
                        if (!graphRoot) {{
                            return null;
                        }}
                        const title = Array.from(graphRoot.querySelectorAll('g.node > title'))
                            .find(el => el.textContent.trim() === nodeId);
                        return title ? title.parentElement : null;
                    }}

                    function getEdgeGroup(parentId, childId) {{
                        const graphRoot = getGraphRootGroup();
                        if (!graphRoot) {{
                            return null;
                        }}
                        const titleText = `${{parentId}}->${{childId}}`;
                        const title = Array.from(graphRoot.querySelectorAll('g.edge > title'))
                            .find(el => el.textContent.trim() === titleText);
                        return title ? title.parentElement : null;
                    }}

                    function getArrowCell(parentId, rowIndex) {{
                        const nodeGroup = getNodeGroup(parentId);
                        if (!nodeGroup) {{
                            return null;
                        }}
                        const texts = Array.from(nodeGroup.querySelectorAll('text'));
                        const arrows = texts.filter(el => el.textContent.trim() === '→');
                        return arrows[rowIndex] || null;
                    }}

                    function clearFocus() {{
                        document.querySelectorAll('.include-focus').forEach(el => {{
                            el.classList.remove('include-focus');
                        }});
                    }}

                    function focusNode(nodeId) {{
                        const nodeGroup = getNodeGroup(nodeId);
                        if (!nodeGroup) {{
                            return;
                        }}
                        clearFocus();
                        nodeGroup.classList.add('include-focus');
                        nodeGroup.scrollIntoView({{
                            behavior: 'smooth',
                            block: 'center',
                            inline: 'center',
                        }});
                    }}

                    function attachInteractivity() {{
                        for (let i = 0; i < EDGE_NAMES.length; ++i) {{
                            const [parentId, childId] = EDGE_NAMES[i];
                            const rowIndex = EDGE_ROWS[i];
                            const arrowText = getArrowCell(parentId, rowIndex);
                            if (!arrowText) {{
                                continue;
                            }}

                            const bbox = arrowText.getBBox();
                            const svg = getSvgRoot();
                            const ns = 'http://www.w3.org/2000/svg';
                            const rect = document.createElementNS(ns, 'rect');
                            rect.setAttribute('x', String(bbox.x - 4));
                            rect.setAttribute('y', String(bbox.y - 2));
                            rect.setAttribute('width', String(bbox.width + 8));
                            rect.setAttribute('height', String(bbox.height + 4));
                            rect.setAttribute('fill', 'transparent');
                            rect.setAttribute('class', 'include-arrow-hit');

                            rect.addEventListener('click', () => focusNode(childId));

                            arrowText.parentElement.appendChild(rect);

                            const edgeGroup = getEdgeGroup(parentId, childId);
                            if (edgeGroup) {{
                                edgeGroup.style.pointerEvents = 'none';
                            }}
                        }}
                    }}

                    window.addEventListener('load', attachInteractivity);
                    """))

    Path(output_html).write_text(doc.render(), encoding="utf-8")
