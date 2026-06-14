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

    visible_subtree_cache: dict[int, bool] = {}

    def has_visible_subtree(v: pb.IncludeVisit) -> bool:
        key = id(v)
        if key in visible_subtree_cache:
            return visible_subtree_cache[key]

        result = is_kept(v) or any(has_visible_subtree(ch) for ch in v.nested)
        visible_subtree_cache[key] = result
        return result

    def nested_rows_for(
            v: pb.IncludeVisit
    ) -> list[tuple[pb.IncludeVisit, int, int, str, int | None]]:
        rows: list[tuple[pb.IncludeVisit, int, int, str, bool]] = []
        for ch in v.nested:
            rows.append((
                ch,
                cumulative_used(ch),
                int(ch.file_line_count),
                ch.relative_path or ch.absolute_path or "<unknown>",
                has_visible_subtree(ch),
            ))

        rows.sort(key=lambda item: item[1], reverse=True)

        result: list[tuple[pb.IncludeVisit, int, int, str, int | None]] = []
        port_index = 0
        for ch, used, lines, name, has_visible in rows:
            if has_visible:
                result.append((ch, used, lines, name, port_index))
                port_index += 1
            else:
                result.append((ch, used, lines, name, None))

        return result

    def node_label(v: pb.IncludeVisit) -> str:
        title = html.escape(v.relative_path or v.absolute_path or "<root>")
        physical = int(v.file_line_count)
        used_sum = cumulative_used(v)

        nested_rows = nested_rows_for(v)

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

        for ch, used, lines, rel, port_index in nested_rows:
            share = 0.0 if used_sum == 0 else (used / used_sum) * 100.0
            progress = progress_table_html(share)
            rel_escaped = html.escape(rel)

            if port_index is None:
                to_cell = "<TD></TD>"
            else:
                to_cell = f'<TD PORT="p{port_index}">→</TD>'

            rows.append("<TR>"
                        f'<TD ALIGN="LEFT">{rel_escaped}</TD>'
                        f"<TD>{used}</TD>"
                        f"<TD>{lines}</TD>"
                        f"<TD>{progress}</TD>"
                        f"{to_cell}"
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
    ) -> tuple[str, list[str]]:
        nonlocal seq
        node_id = f"n{seq}"
        seq += 1

        add_vertex_record(v, node_id, parent_id, parent_row_index)

        visible = is_kept(v)
        if visible:
            dot.node(node_id, node_label(v))

        visible_roots: list[str] = [node_id] if visible else []

        for ch, _used, _lines, _name, port_index in nested_rows_for(v):
            child_id, child_visible_roots = emit(
                ch,
                parent_id=node_id,
                parent_row_index=port_index,
            )

            graph.add_edge(
                node_id,
                child_id,
                parent_row_index=-1 if port_index is None else port_index,
            )

            if visible and port_index is not None:
                for child_visible_id in child_visible_roots:
                    dot.edge(f"{node_id}:p{port_index}:e", child_visible_id)

            if not visible:
                visible_roots.extend(child_visible_roots)

        return node_id, visible_roots

    _root_id, _visible_roots = emit(visit, parent_id=None, parent_row_index=None)
    return dot, graph
