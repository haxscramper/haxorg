#!/usr/bin/env python

from pathlib import Path
import pickle
import igraph as ig
import py_scriptutils.graph_utils.elk_schema as elk
import py_scriptutils.graph_utils.typst_schema as typ
from pydantic import BaseModel
from beartype.typing import Literal, Union, List, Optional, Set, Tuple, Any, Dict, Callable
from numbers import Number
from enum import Enum
from beartype import beartype
from shapely.geometry import LineString, Polygon
from shapely.ops import unary_union
from PIL import Image
import numpy as np
from sklearn.cluster import KMeans
from abc import ABC, abstractmethod
from py_scriptutils.script_logging import log

CAT = __name__


class HyperEdgeData(BaseModel):
    merged_edge_ids: List[str]
    pattern: Optional[Dict[str, Any]] = None
    merged_edge_extra: Optional[Dict[str, Any]] = None
    hyperedge_extra: Optional[Dict[str, Any]] = None


@beartype
class ElkExtra(BaseModel, extra="forbid"):
    data: Any
    kind: str


def graph_to_typst(
    graph: elk.Graph,
    edge_command: str = "draw_edge",
    node_command: str = "draw_node",
) -> typ.Document:
    subnodes: List[typ.TypstNode] = []

    bbox = elk.compute_graph_bounding_box(graph)

    subnodes.append(
        typ.Set(target="page",
                args=dict(
                    width=typ.Literal(value=typ.PtSize(size=bbox.width)),
                    height=typ.Literal(value=typ.PtSize(size=bbox.height)),
                    margin=typ.Literal(value=dict(
                        top=typ.PtSize(size=0),
                        bottom=typ.PtSize(size=0),
                        left=typ.PtSize(size=0),
                        right=typ.PtSize(size=0),
                    )),
                )))

    if graph.edges:
        for edge in graph.edges:
            subnodes.append(
                typ.Command(
                    name=edge_command,
                    args=[typ.Literal(value=edge.model_dump(exclude_none=True))],
                ))

    if graph.children:
        for node in graph.children:
            subnodes.append(
                typ.Command(
                    name=node_command,
                    args=[typ.Literal(value=node.model_dump(exclude_none=True))],
                ))

    return typ.Document(subnodes=subnodes)


def _collect_all_edges(node: elk.Graph, all_edges: List[elk.Edge]) -> None:
    if hasattr(node, 'edges') and node.edges:
        all_edges.extend(node.edges)

    if hasattr(node, 'children') and node.children:
        for child in node.children:
            _collect_all_edges(child, all_edges)


from collections import defaultdict


def get_edge_groups_by_shared_ports(graph: elk.Graph) -> List[List[elk.Edge]]:
    port_to_edges = defaultdict(list)
    for edge in graph.edges:
        source_ports = []
        target_ports = []

        if edge.sourcePort:
            source_ports.append((edge.source, edge.sourcePort))
        elif edge.source:
            source_ports.append((edge.source, None))
        elif edge.sources:
            for source in edge.sources:
                source_ports.append((source, None))

        if edge.targetPort:
            target_ports.append((edge.target, edge.targetPort))
        elif edge.target:
            target_ports.append((edge.target, None))
        elif edge.targets:
            for target in edge.targets:
                target_ports.append((target, None))

        for port_key in source_ports + target_ports:
            port_to_edges[port_key].append(edge)

    edge_groups = []
    processed_edges = set()

    for edges_list in port_to_edges.values():
        if len(edges_list) == 1:
            edge_groups.append(edges_list)

    for edges_list in port_to_edges.values():
        if len(edges_list) <= 1:
            continue

        group = []
        for edge in edges_list:
            if id(edge) not in processed_edges:
                group.append(edge)
                processed_edges.add(id(edge))

        if len(group) > 1:
            edge_groups.append(group)

    return edge_groups


from pathlib import Path
from typing import List, Tuple
from dataclasses import dataclass
from beartype import beartype
import matplotlib.font_manager as fm
from fontTools.ttLib import TTFont
from fontTools.pens.boundsPen import BoundsPen
import matplotlib.pyplot as plt
import matplotlib.patches as patches

_font_cache = {}


@dataclass
class SplitResult:
    lines: List[str]
    height: Number


@beartype
def get_font_metrics(font_path: str) -> Tuple[TTFont, Number]:
    if font_path in _font_cache:
        return _font_cache[font_path]

    ttfont = TTFont(font_path)
    units_per_em = ttfont["head"].unitsPerEm
    _font_cache[font_path] = (ttfont, units_per_em)
    return ttfont, units_per_em


@beartype
def get_text_width(text: str, font_path: str, font_size: Number) -> Number:
    ttfont, units_per_em = get_font_metrics(font_path)
    cmap = ttfont.getBestCmap()
    hmtx = ttfont["hmtx"]

    total_width = 0
    for char in text:
        if ord(char) in cmap:
            glyph_name = cmap[ord(char)]
            advance_width, _ = hmtx[glyph_name]
            total_width += advance_width

    return (total_width / units_per_em) * font_size


@beartype
def get_line_height(font_path: str, font_size: Number) -> Number:
    ttfont, units_per_em = get_font_metrics(font_path)
    hhea = ttfont["hhea"]
    line_height = hhea.ascent - hhea.descent + hhea.lineGap
    return (line_height / units_per_em) * font_size


@beartype
def get_break_priority(char: str) -> int:
    if char == " ":
        return 0
    elif char in ".,;!?":
        return 1
    elif char in ":_-/\\|":
        return 2
    elif char.isalnum():
        return 4
    else:
        return 3


@beartype
def split_text_to_fit(text: str, expected_width: Number, font_path: str,
                      font_size: Number) -> SplitResult:
    if not text:
        return SplitResult(lines=[], height=0.0)

    n = len(text)
    char_widths = []
    for char in text:
        char_widths.append(get_text_width(char, font_path, font_size))

    dp = [float("inf")] * (n + 1)
    parent = [-1] * (n + 1)
    dp[0] = 0

    for i in range(n):
        if dp[i] == float("inf"):
            continue

        current_width = 0
        for j in range(i, n):
            current_width += char_widths[j]
            if current_width > expected_width:
                break

            break_penalty = 0
            if j < n - 1:
                break_penalty = get_break_priority(text[j])

            new_cost = dp[i] + break_penalty
            if new_cost < dp[j + 1]:
                dp[j + 1] = new_cost
                parent[j + 1] = i

    breaks = []
    current = n
    while parent[current] != -1:
        breaks.append(parent[current])
        current = parent[current]
    breaks.reverse()

    lines = []
    start = 0
    for break_point in breaks:
        if break_point > start:
            lines.append(text[start:break_point])
            start = break_point
    if start < n:
        lines.append(text[start:])

    line_height = get_line_height(font_path, font_size)
    total_height = len(lines) * line_height

    return SplitResult(lines=lines, height=total_height)


@beartype
class Direction(Enum):
    IN = 0
    OUT = 1

    def to_port_side(self) -> elk.PortSide:
        if self == Direction.IN:
            return elk.PortSide.WEST

        else:
            return elk.PortSide.EAST


@beartype
def get_resource_port_id(id: str, side: Direction) -> str:
    return f"{id}-{side.name}"


def round_to_multiple(number, multiple):
    if round(number / multiple) == 0:
        return multiple

    else:
        return round(number / multiple) * multiple


@beartype
def get_node_height_for_text(text: str,
                             expected_width: Number,
                             font_size: Number,
                             size_step: Number = 25) -> Number:
    font_path = fm.findfont(fm.FontProperties(family="DejaVu Sans"))
    split_fit = split_text_to_fit(
        text,
        expected_width=expected_width,
        font_path=font_path,
        font_size=font_size,
    )

    result = round_to_multiple(
        get_line_height(font_path, font_size) *
        len(split_fit.lines if split_fit.lines else [""]), size_step)

    assert result is not None
    assert result != 0

    return result


@beartype
def single_line_label(
        id: str,
        text: str,
        font_size: Number,
        extra_extra: Dict[str, Any] = dict(),
        size_step: Number = 25,
) -> elk.Label:
    font_path = fm.findfont(fm.FontProperties(family="DejaVu Sans"))
    expected_width = round_to_multiple(
        get_text_width(text, font_path, font_size) + font_size * 2, size_step)
    expected_height = round_to_multiple(
        get_line_height(font_path, font_size) + font_size, size_step)

    return elk.Label(
        id=id,
        text=text,
        width=expected_width,
        height=expected_height,
        extra=dict(
            expected_width=expected_width,
            expected_height=expected_height,
            font_size=font_size,
            **extra_extra,
        ),
    )


@beartype
def compute_hyperedge_polygon(sections: List[elk.EdgeSection],
                              width: float) -> List[Tuple[float, float]]:
    buffered_lines = []

    for section in sections:
        points = [(section.startPoint.x, section.startPoint.y)]
        if section.bendPoints:
            points.extend([(bp.x, bp.y) for bp in section.bendPoints])
        points.append((section.endPoint.x, section.endPoint.y))

        if len(points) >= 2:
            line = LineString(points)
            buffered_line = line.buffer(width / 2, cap_style=2, join_style=2)
            buffered_lines.append(buffered_line)

    if not buffered_lines:
        return []

    combined_polygon = unary_union(buffered_lines)

    if hasattr(combined_polygon, 'exterior'):
        return list(combined_polygon.exterior.coords)
    else:
        return []


def extract_color_palette(texture_path: str, n_colors: int = 3) -> dict:
    img = Image.open(texture_path).convert('RGB')
    pixels = np.array(img).reshape(-1, 3)

    kmeans = KMeans(n_clusters=n_colors, random_state=42)
    kmeans.fit(pixels)

    colors = []
    for center in kmeans.cluster_centers_:
        colors.append({
            "r": int(center[0]),
            "g": int(center[1]),
            "b": int(center[2]),
            "hex": f"#{int(center[0]):02x}{int(center[1]):02x}{int(center[2]):02x}"
        })

    return {"palette": colors}


@beartype
def merge_edges_into_hyperedge(edges: List[elk.Edge]) -> elk.Edge:
    if not edges:
        raise ValueError("Cannot merge empty list of edges")

    if len(edges) == 1:
        return edges[0]

    all_sources = set()
    all_targets = set()
    all_source_ports = set()
    all_target_ports = set()
    all_sections = []
    all_junction_points = []
    all_labels = []

    merged_extra: Dict[str, Any] = dict()
    edge_order: List[str] = []

    for edge in edges:
        edge_order.append(edge.id)

        if edge.source:
            all_sources.add(edge.source)
        if edge.sources:
            all_sources.update(edge.sources)

        if edge.target:
            all_targets.add(edge.target)
        if edge.targets:
            all_targets.update(edge.targets)

        if edge.sourcePort:
            all_source_ports.add((edge.source, edge.sourcePort))
        if edge.targetPort:
            all_target_ports.add((edge.target, edge.targetPort))

        if edge.sections:
            all_sections.extend(edge.sections)

        if edge.junctionPoints:
            all_junction_points.extend(edge.junctionPoints)

        if edge.labels:
            all_labels.extend(edge.labels)

        if edge.extra:
            assert isinstance(edge, elk.Edge)
            assert isinstance(edge.extra, dict)
            merged_extra[edge.id] = edge.extra

    merged_edge = elk.Edge(
        id=f"merged_{hash(tuple(e.id for e in edges))}",
        sources=list(all_sources) if len(all_sources) > 1 else None,
        targets=list(all_targets) if len(all_targets) > 1 else None,
        source=list(all_sources)[0] if len(all_sources) == 1 else None,
        target=list(all_targets)[0] if len(all_targets) == 1 else None,
        sections=all_sections,
        junctionPoints=all_junction_points if all_junction_points else None,
        labels=all_labels if all_labels else None,
        extra=dict(data=ElkExtra(
            data=HyperEdgeData(
                polygon=compute_hyperedge_polygon(all_sections, width=4.0),
                merged_edge_extra=merged_extra,
                merged_edge_ids=merged_edge,
            ),
            kind="hyperedge",
        )),
    )

    return merged_edge


@beartype
def group_multi_layout(graph: elk.Graph):
    grouped_multi_edges: List[elk.Edge] = []

    for group in get_edge_groups_by_shared_ports(graph):
        if len(group) == 1:
            grouped_multi_edges.append(group[0])

        else:
            grouped_multi_edges.append(merge_edges_into_hyperedge(group))

    graph.edges = grouped_multi_edges


@beartype
class GraphWalker(ABC):

    @abstractmethod
    def getTopVertices(self) -> List[str]:
        ...

    @abstractmethod
    def getELKNodeNonRec(self, vertex_id: str) -> elk.Node:
        ...

    @abstractmethod
    def getELKEdge(self, edge_id: str) -> elk.Edge:
        ...

    @abstractmethod
    def getNestedVertices(self, vertex_id: str) -> List[str]:
        ...


    @abstractmethod
    def getEdges(self) -> List[str]:
        ...


    def getELKNodeRec(self, vertex_id: str) -> elk.Node:
        result = self.getELKNodeNonRec(vertex_id)
        nested = self.getNestedVertices(vertex_id)
        if nested:
            result.children = []
            for sub in nested:
                result.children.append(self.getELKNodeRec(sub))

        return result

    def getELKGraph(self) -> elk.Graph:
        result = elk.Graph(
            id="root",
            children=[],
            edges=[],
            ports=[],
            layoutOptions={
                "org.eclipse.elk.spacing.edgeEdge": 15,
                "org.eclipse.elk.spacing.edgeNode": 20,
                "org.eclipse.elk.spacing.labelNode": 10,
                "org.eclipse.elk.layered.spacing.edgeNodeBetweenLayers": 30,
                "org.eclipse.elk.layered.spacing.edgeEdgeBetweenLayers": 20,
                "org.eclipse.elk.spacing.labelPortVertical": 0,
                "org.eclipse.elk.direction": "LEFT",
            },
        )

        for v in self.getTopVertices():
            result.children.append(self.getELKNodeRec(v))

        for e in self.getEdges():
            result.edges.append(self.getELKEdge(e))

        return result
