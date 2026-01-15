from dataclasses import dataclass

import glom
import igraph as ig
from beartype import beartype
from beartype.typing import Any, Dict, List, Optional, Set
from py_cli.generate.mind_map import elk_converter, elk_schema
from py_cli import haxorg_opts
from py_scriptutils.json_utils import Json
from py_scriptutils.script_logging import log
from pydantic import BaseModel, Field

CAT = __name__


class EdgeExtra(BaseModel, extra="forbid"):
    structuredEdgeBrief: Optional[Dict[str, Any]] = None
    edgeBrief: Optional[str] = None
    structuredEdgeDetailed: Optional[Dict[str, Any]] = None
    edgeDetailed: Optional[str] = None


class Edge(BaseModel, extra="forbid"):
    edgeId: str
    sourceId: str
    targetId: str
    sourcePortId: Optional[str] = None
    targetPortId: Optional[str] = None
    bundleIndex: Optional[int] = None
    extra: Optional[EdgeExtra] = None
    extra_type: Optional[str] = None


class EdgeCategory(BaseModel, extra="forbid"):
    edges: List[Edge]
    categoryName: str
    hierarchyEdgeCrossings: Dict[str, List[str]] = Field(default_factory=dict)


class RectSpacing(BaseModel, extra="forbid"):
    top: Optional[int | float] = None
    left: Optional[int | float] = None
    bottom: Optional[int | float] = None
    right: Optional[int | float] = None


class Size(BaseModel, extra="forbid"):
    width: int | float
    height: int | float


class Pos(BaseModel, extra="forbid"):
    x: int | float
    y: int | float


class VertexGeometry(BaseModel, extra="forbid"):
    size: Optional[Size] = None
    pos: Optional[Pos] = None
    padding: Optional[RectSpacing] = None
    margin: Optional[RectSpacing] = None


class TodoSubtree(BaseModel, extra="forbid"):
    name: str
    description: Optional[str] = None
    nested: List["TodoSubtree"] = Field(default_factory=list)
    structuredName: Optional[Json] = None
    todoState: Optional[str] = None
    structuredDescription: Optional[Json] = None


class VertexExtra(BaseModel, extra="forbid"):
    structuredName: Optional[Json] = None
    structuredDescription: Optional[Json] = None
    todoState: Optional[str] = None
    nestingLevel: Optional[int] = None
    geometry: Optional[VertexGeometry] = None
    nestedSubtrees: List[TodoSubtree] = Field(default_factory=list)


class Vertex(BaseModel, extra="forbid"):
    vertexId: str
    vertexName: Optional[str] = None
    vertexDescription: Optional[str] = None
    vertexKind: Optional[str] = None
    extra: Optional[VertexExtra] = None
    extra_type: Optional[str] = None


class Graph(BaseModel, extra="forbid"):
    edges: Dict[str, EdgeCategory]
    vertices: Dict[str, Vertex]
    flatVertexIDs: List[str]
    rootVertexIDs: List[str]
    vertexNestingMap: Dict[str, List[str]]
    vertexParentMap: Dict[str, str]
    maxNestingLevel: int = 0


@beartype
def convert_to_igraph(g: Graph) -> ig.Graph:
    result = ig.Graph(directed=True)
    vertex_idx: Dict[str, int] = dict()

    @beartype
    def add_node(vertex: Vertex) -> None:
        vertex_idx[vertex.vertexId] = result.vcount()
        result.add_vertex(data=vertex)

    @beartype
    def add_edge(edge: Edge) -> None:
        result.add_edge(
            source=vertex_idx[edge.sourceId],
            target=vertex_idx[edge.targetId],
            data=edge,
        )

    for v_id, v in g.vertices.items():
        add_node(v)

    for _, cat in g.edges.items():
        for e in cat.edges:
            add_edge(e)

    return result


@beartype
@dataclass
class HaxorgMMapEdgeCrossingSegment():
    source: str
    target: str
    edgeId: str
    crossingIdx: int
    originalEdgeId: str
    segmentCount: int
    sourcePortId: Optional[str] = None
    targetPortId: Optional[str] = None


@beartype
@dataclass
class HaxorgMMapPortCrossing():
    portId: str


@beartype
@dataclass
class HaxorgMMapLabelNode():
    originalEdgeId: str

    def getLabelNodeId(self) -> str:
        return f"{self.originalEdgeId}-label-node"

    def getHeadSegmentId(self) -> str:
        return f"{self.originalEdgeId}-head-segment"

    def getTailSegmentId(self) -> str:
        return f"{self.originalEdgeId}-tail-segment"

    def getHeadSegmentPortId(self) -> str:
        return f"{self.getHeadSegmentId()}-port"

    def getTailSegmentPortId(self) -> str:
        return f"{self.getTailSegmentId()}-port"


from collections import defaultdict
from numbers import Number

from beartype.typing import Tuple
from rich.tree import Tree


@beartype
class HaxorgMMapWalker(elk_converter.GraphWalker):
    edge_no_crossings: Dict[str, Edge]
    all_edges: Dict[str, Edge]
    fragmented_edge_map: Dict[str, HaxorgMMapEdgeCrossingSegment]
    node_crossing_ports: Dict[str, Dict[str, HaxorgMMapPortCrossing]]
    visual_root_vertices: List[str]
    excluded_vertices: Set[str]
    # Parent node ID (or None if this is a root node) mapped to the list of edge label nodes
    label_node_nesting: defaultdict[Optional[str], Set[str]]
    label_nodes: Dict[str, HaxorgMMapLabelNode]
    conf: haxorg_opts.MMapDiagramConfig

    def hasEdgeLabel(self, e: Edge) -> bool:
        return bool(e.extra and (e.extra.edgeBrief or e.extra.edgeDetailed))

    def addCrossingConnection(self, vertexID: str, isCrossing: bool,
                              e: Edge) -> tuple[str, Optional[str]]:
        if isCrossing:
            portId = f"{vertexID}-crossed-by-{e.edgeId}"

            if vertexID not in self.node_crossing_ports:
                self.node_crossing_ports[vertexID] = dict()

            if portId not in self.node_crossing_ports[vertexID]:
                self.node_crossing_ports[vertexID][portId] = HaxorgMMapPortCrossing(
                    portId=portId,)

            return (vertexID, portId)

        else:
            return (vertexID, None)

    def getRepr(self) -> Tree:
        result = Tree("graph")

        import re

        def auxVertex(v: str) -> Tree:
            label = f"{v}"
            vert: Vertex | HaxorgMMapLabelNode
            if v in self.hgraph.vertices:
                vert = self.hgraph.vertices[v]
                label += " '" + re.sub(r"\s{2,}", " ", vert.vertexName or "") + "'"

            elif v in self.label_nodes:
                vert = self.label_nodes[v]
                edge = self.all_edges[vert.originalEdgeId]
                label += " '" + re.sub(r"\s{2,}", " ",
                                       (edge.extra and edge.extra.edgeBrief) or "") + "'"

            result = Tree(label)

            if v in self.label_nodes:
                vert = self.label_nodes[v]
                edge = self.all_edges[vert.originalEdgeId]
                result.add(
                    f"source:{edge.sourceId} source-parent:{self.getParent(edge.sourceId)}"
                )
                result.add(
                    f"target:{edge.targetId} target-parent:{self.getParent(edge.targetId)}"
                )
                result.add(f"head:{vert.getHeadSegmentId()}")
                result.add(f"tail:{vert.getTailSegmentId()}")

            for nested in self.getNestedVertices(v):
                result.add(auxVertex(nested))

            return result

        vertices = Tree("vertices")
        for v in self.getTopVertices():
            vertices.add(auxVertex(v))
        result.add(vertices)

        edges = Tree("edges")
        for e in self.getEdges():
            edge: Edge | HaxorgMMapEdgeCrossingSegment
            if e in self.fragmented_edge_map:
                edge = self.fragmented_edge_map[e]
                label = f"{edge.edgeId}"
                edges.add(Tree(label))

            else:
                edge = self.edge_no_crossings[e]
                label = f"{edge.edgeId} {edge.sourceId} -> {edge.targetId}"
                edges.add(Tree(label))

        result.add(edges)
        return result

    def addSegmentedEdge(self, e: Edge, cross: Dict[str, List[str]]) -> None:
        import itertools
        edge_segmentation = [(e.sourceId, False)] + [
            (n, True) for n in cross[e.edgeId] if n not in self.excluded_vertices
        ] + [(e.targetId, False)]

        for index, (source, target) in enumerate(itertools.pairwise(edge_segmentation)):
            sourceId, sourcePortId = self.addCrossingConnection(source[0], source[1], e)
            targetId, targetPortId = self.addCrossingConnection(target[0], target[1], e)
            crossingEdgeID = f"{e.edgeId}-segment-{index}"

            self.fragmented_edge_map[crossingEdgeID] = HaxorgMMapEdgeCrossingSegment(
                edgeId=crossingEdgeID,
                source=sourceId,
                target=targetId,
                sourcePortId=sourcePortId,
                targetPortId=targetPortId,
                originalEdgeId=e.edgeId,
                crossingIdx=index,
                segmentCount=len(edge_segmentation) - 1,
            )

    def isParent(self, parent: str, vertex: str) -> bool:
        return parent in self.hgraph.vertexNestingMap and vertex in self.hgraph.vertexNestingMap[
            parent]

    def getParent(self, vertex: str) -> Optional[str]:
        result = self.hgraph.vertexParentMap.get(vertex, None)
        if result in self.excluded_vertices:
            return None

        else:
            return result

    def addDirectEdge(self, e: Edge) -> None:
        if self.hasEdgeLabel(
                e
        ) and self.conf.edge_label_type == haxorg_opts.MMapDiagramEdgeLabelType.INSERT_LABEL_NODES:
            label_node = HaxorgMMapLabelNode(originalEdgeId=e.edgeId)
            self.fragmented_edge_map[
                label_node.getHeadSegmentId()] = HaxorgMMapEdgeCrossingSegment(
                    edgeId=label_node.getHeadSegmentId(),
                    source=label_node.getLabelNodeId(),
                    sourcePortId=label_node.getHeadSegmentPortId(),
                    target=e.targetId,
                    targetPortId=e.targetPortId,
                    originalEdgeId=e.edgeId,
                    crossingIdx=1,
                    segmentCount=2,
                )

            self.fragmented_edge_map[
                label_node.getTailSegmentId()] = HaxorgMMapEdgeCrossingSegment(
                    edgeId=label_node.getTailSegmentId(),
                    target=label_node.getLabelNodeId(),
                    targetPortId=label_node.getTailSegmentPortId(),
                    source=e.sourceId,
                    sourcePortId=e.sourcePortId,
                    originalEdgeId=e.edgeId,
                    crossingIdx=0,
                    segmentCount=2,
                )

            self.label_nodes[label_node.getLabelNodeId()] = label_node

            if self.isParent(parent=e.sourceId, vertex=e.targetId):
                self.label_node_nesting[e.sourceId].add(label_node.getLabelNodeId())

            elif self.isParent(parent=e.targetId, vertex=e.sourceId):
                self.label_node_nesting[e.targetId].add(label_node.getLabelNodeId())

            else:
                self.label_node_nesting[self.getParent(e.targetId) or
                                        self.getParent(e.sourceId)].add(
                                            label_node.getLabelNodeId())

        else:
            self.edge_no_crossings[e.edgeId] = e

    def addHGraphEdges(self) -> None:
        for _, cat in self.hgraph.edges.items():
            for e in cat.edges:
                self.all_edges[e.edgeId] = e
                cross = cat.hierarchyEdgeCrossings
                if e.edgeId not in cross or not cross[e.edgeId]:
                    self.addDirectEdge(e)

                else:
                    self.addSegmentedEdge(e, cross)

    def addHGraphRootVertices(self) -> None:

        def append_root_items(id: str) -> None:
            if self.hgraph.vertices[id].vertexKind in ["Item"]:
                self.visual_root_vertices.append(id)

            else:
                self.excluded_vertices.add(id)
                for sub in self.hgraph.vertexNestingMap[id]:
                    append_root_items(sub)

        for top in self.hgraph.rootVertexIDs:
            append_root_items(top)

    def __init__(self, igraph: ig.Graph, hgraph: Graph,
                 conf: haxorg_opts.MMapDiagramConfig) -> None:
        super().__init__()
        self.igraph = igraph
        self.hgraph = hgraph
        self.edge_no_crossings = dict()
        self.fragmented_edge_map = dict()
        self.node_crossing_ports = dict()
        self.visual_root_vertices = list()
        self.excluded_vertices = set()
        self.all_edges = dict()
        self.label_node_nesting = defaultdict(lambda: set())
        self.label_nodes = dict()
        self.conf = conf

        self.addHGraphRootVertices()
        self.addHGraphEdges()

    def getTopVertices(self) -> List[str]:
        return self.visual_root_vertices + sorted(self.label_node_nesting.get(None, []))

    def getEdges(self) -> List[str]:
        return sorted(k for k in self.edge_no_crossings) + sorted(
            k for k in self.fragmented_edge_map)

    def getELKEdge(self, edge_id: str) -> elk_schema.Edge:
        if edge_id in self.edge_no_crossings:
            haxorg_edge: Edge = self.edge_no_crossings[edge_id]
            assert isinstance(haxorg_edge, Edge)

            result = elk_schema.Edge(
                id=haxorg_edge.edgeId,
                source=haxorg_edge.sourceId,
                target=haxorg_edge.targetId,
                sourcePort=haxorg_edge.sourcePortId,
                targetPort=haxorg_edge.targetPortId,
                extra=dict(haxorg_edge=haxorg_edge),
                layoutOptions={
                    "edgeLabels.placement": "CENTER",
                },
            )

        else:
            crossing_edge: HaxorgMMapEdgeCrossingSegment = self.fragmented_edge_map[
                edge_id]

            haxorg_edge_crossing: Edge = self.all_edges[crossing_edge.originalEdgeId]

            result = elk_schema.Edge(
                id=crossing_edge.edgeId,
                extra=dict(crossing_edge=crossing_edge),
                source=crossing_edge.source,
                target=crossing_edge.target,
                sourcePort=crossing_edge.sourcePortId,
                targetPort=crossing_edge.targetPortId,
                layoutOptions={
                    "edgeLabels.placement": "CENTER",
                },
            )

        return result

    def getNestedVertices(self, vertex_id: str) -> List[str]:
        result = []
        if vertex_id in self.hgraph.vertexNestingMap:
            result.extend(self.hgraph.vertexNestingMap[vertex_id])

        if vertex_id in self.label_node_nesting:
            result.extend(self.label_node_nesting[vertex_id])

        return result

    def getHGraphNode(self, vertex_id: str) -> elk_schema.Node:
        data: Vertex = self.hgraph.vertices[vertex_id]
        assert data.vertexName is not None

        def get_dimension(name: str, fallback: float) -> float:
            size = glom.glom(
                data,
                (
                    glom.Path("extra", "geometry", "size", name),
                    glom.Check(lambda x: x not in [None, -1, 0] and x > 0),
                ),
                default=fallback,
            )

            assert isinstance(size, (float, int)), type(size)
            assert size not in [-1, 0, None
                               ] and 0 < size, f"size:{size} fallback:{fallback}"
            return size

        node_width = get_dimension("width", self.conf.diagram_node_default_width)
        assert isinstance(data, Vertex)
        if data.vertexDescription or self.getNestedVertices(vertex_id):
            height = get_dimension(
                "height",
                elk_converter.get_node_height_for_text(
                    data.vertexName,
                    expected_width=float(node_width),
                    font_size=self.conf.diagram_node_font_size,
                    size_step=self.conf.diagram_node_height_step,
                    max_height=self.conf.diagram_node_max_height,
                    min_height=self.conf.diagram_node_min_height,
                ),
            )
            result = elk_schema.Node(
                id=data.vertexId,
                height=height,
                width=node_width,
                extra=dict(haxorg_vertex=data),
                labels=[],
                layoutOptions={
                    "nodeLabels.placement": "[H_CENTER, V_TOP, OUTSIDE]",
                    "portLabels.placement": "NEXT_TO_PORT_OF_POSSIBLE",
                    "edgeLabels.placement": "CENTER",
                    "elk.nodeSize.constraints": "MINIMUM_SIZE",
                    "elk.nodeSize.minimum": f"({node_width}, {height})",
                    "elk.margins": 0,
                },
            )

            if data.vertexName:
                result.labels.append(  # type: ignore[union-attr]
                    elk_converter.single_line_label(
                        id=f"{data.vertexId}-title-label",
                        text=data.vertexName,
                        font_size=self.conf.diagram_node_title_label_font_size,
                    ))

        else:
            result = elk_schema.Node(
                id=data.vertexId,
                width=node_width,
                height=get_dimension(
                    "width",
                    elk_converter.get_node_height_for_text(
                        data.vertexName,
                        expected_width=float(node_width),
                        font_size=self.conf.diagram_node_font_size,
                        size_step=self.conf.diagram_node_height_step,
                        max_height=self.conf.diagram_node_max_height,
                        min_height=self.conf.diagram_node_min_height,
                    ),
                ),
                extra=dict(haxorg_vertex=data),
            )

        if not result.layoutOptions:
            result.layoutOptions = dict()

        if data.extra:
            extra = data.extra
            if extra.geometry:
                geom = extra.geometry
                if geom.padding:
                    padding = []
                    default_padding = self.conf.default_inner_padding
                    for attr in ["left", "right", "top", "bottom"]:
                        padding.append(
                            f"{attr}={getattr(geom.padding, attr) or default_padding}")

                    if padding:
                        result.layoutOptions["org.eclipse.elk.padding"] = "[{}]".format(
                            ",".join(padding))

        if data.vertexId in self.node_crossing_ports:
            if not result.ports:
                result.ports = []

            for _, port in self.node_crossing_ports[data.vertexId].items():
                result.ports.append(
                    elk_schema.Port(
                        id=port.portId,
                        width=self.conf.diagram_node_port_dimensions[0],
                        height=self.conf.diagram_node_port_dimensions[1],
                    ))

        return result

    def getLabelNode(self, vertex_id: str) -> elk_schema.Node:
        label_node = self.label_nodes[vertex_id]
        label_edge = self.all_edges[label_node.originalEdgeId]
        return elk_schema.Node(
            id=label_node.getLabelNodeId(),
            width=self.conf.label_node_expected_width,
            height=elk_converter.get_node_height_for_text(
                (label_edge.extra and ((label_edge.extra.edgeBrief or "") +
                                       (label_edge.extra.edgeDetailed or ""))) or "",
                expected_width=self.conf.label_node_expected_width,
                font_size=self.conf.label_node_font_size,
                max_height=self.conf.label_node_max_height,
                min_height=self.conf.label_node_min_height,
            ),
            ports=[
                elk_schema.Port(
                    id=label_node.getHeadSegmentPortId(),
                    width=self.conf.label_node_port_dimensions[0],
                    height=self.conf.label_node_port_dimensions[1],
                ),
                elk_schema.Port(
                    id=label_node.getTailSegmentPortId(),
                    width=self.conf.label_node_port_dimensions[0],
                    height=self.conf.label_node_port_dimensions[1],
                )
            ],
            extra=dict(haxorg_label_edge=label_edge,),
            layoutOptions={
                "elk.margins": 0,
            },
        )

    def getELKNodeNonRec(self, vertex_id: str) -> elk_schema.Node:
        if vertex_id in self.label_nodes:
            return self.getLabelNode(vertex_id)

        else:
            return self.getHGraphNode(vertex_id)
