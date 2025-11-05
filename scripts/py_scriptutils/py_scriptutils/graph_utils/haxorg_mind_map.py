from pydantic import BaseModel, Field
from beartype.typing import List, Optional, Dict, Any
from beartype import beartype
from py_scriptutils.graph_utils import elk_converter
from py_scriptutils.graph_utils import elk_schema
import igraph as ig
from dataclasses import dataclass, field
from abc import ABC, abstractmethod


class Edge(BaseModel, extra="forbid"):
    edgeId: str
    sourceId: str
    targetId: str
    sourcePortId: Optional[str] = None
    targetPortId: Optional[str] = None
    bundleIndex: Optional[int] = None
    extra: Optional[Dict[str, Any]] = None


class EdgeCategory(BaseModel, extra="forbid"):
    edges: List[Edge]
    categoryName: str
    hierarchyEdgeCrossings: Dict[str, List[str]] = Field(default_factory=list)


class Vertex(BaseModel, extra="forbid"):
    vertexId: str
    vertexName: Optional[str] = None
    vertexDescription: Optional[str] = None
    vertexKind: Optional[str] = None
    extra: Optional[Dict[str, Any]] = None
    extra_type: Optional[str] = None


class Graph(BaseModel, extra="forbid"):
    edges: Dict[str, EdgeCategory]
    vertices: Dict[str, Vertex]
    flatVertexIDs: List[str]
    rootVertexIDs: List[str]
    vertexNestingMap: Dict[str, List[str]]
    vertexParentMap: Dict[str, str]


@beartype
def convert_to_igraph(g: Graph) -> ig.Graph:
    result = ig.Graph(directed=True)
    vertex_idx: Dict[str, int] = dict()

    @beartype
    def add_node(vertex: Vertex):
        vertex_idx[vertex.vertexId] = result.vcount()
        result.add_vertex(data=vertex)

    @beartype
    def add_edge(edge: Edge):
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
    sourcePortId: Optional[str] = None
    targetPortId: Optional[str] = None


@beartype
@dataclass
class HaxorgMMapPortCrossing():
    portId: str


@beartype
class HaxorgMMapWalker(elk_converter.GraphWalker):
    edge_no_crossings: Dict[str, Edge]
    fragmented_edge_map: Dict[str, HaxorgMMapEdgeCrossingSegment]
    node_crossing_ports: Dict[str, Dict[str, HaxorgMMapPortCrossing]]

    def __init__(self, igraph: ig.Graph, hgraph: Graph) -> None:
        super().__init__()
        self.igraph = igraph
        self.hgraph = hgraph
        self.edge_no_crossings = dict()
        self.fragmented_edge_map = dict()
        self.node_crossing_ports = dict()

        for _, cat in self.hgraph.edges.items():
            for e in cat.edges:
                cross = cat.hierarchyEdgeCrossings
                if e.edgeId not in cross or not cross[e.edgeId]:
                    self.edge_no_crossings[e.edgeId] = e

                else:
                    import itertools

                    @beartype
                    def getCrossingConnection(
                            vertexID: str, isCrossing: bool) -> tuple[str, Optional[str]]:
                        if isCrossing:
                            portId = f"{vertexID}-crossed-by-{e.edgeId}"

                            if vertexID not in self.node_crossing_ports:
                                self.node_crossing_ports[vertexID] = dict()

                            if portId not in self.node_crossing_ports[vertexID]:
                                self.node_crossing_ports[vertexID][
                                    portId] = HaxorgMMapPortCrossing(portId=portId,)

                            return (vertexID, portId)

                        else:
                            return (vertexID, None)

                    for index, (source, target) in enumerate(
                            itertools.pairwise([(e.sourceId, False)] +
                                               [(n, True) for n in cross[e.edgeId]] +
                                               [(e.targetId, False)])):
                        sourceId, sourcePortId = getCrossingConnection(
                            source[0], source[1])
                        targetId, targetPortId = getCrossingConnection(
                            target[0], target[1])
                        crossingEdgeID = f"{e.edgeId}-segment-{index}"

                        self.fragmented_edge_map[
                            crossingEdgeID] = HaxorgMMapEdgeCrossingSegment(
                                edgeId=crossingEdgeID,
                                source=sourceId,
                                target=targetId,
                                sourcePortId=sourcePortId,
                                targetPortId=targetPortId,
                                originalEdgeId=e.edgeId,
                                crossingIdx=index,
                            )

    def getTopVertices(self) -> List[str]:
        return self.hgraph.rootVertexIDs

    def getEdges(self) -> List[str]:
        return sorted(k for k in self.edge_no_crossings) + sorted(
            k for k in self.fragmented_edge_map)

    def getELKEdge(self, edge_id: str) -> elk_schema.Edge:
        if edge_id in self.edge_no_crossings:
            haxorg_edge: Edge = self.edge_no_crossings[edge_id]
            assert isinstance(haxorg_edge, Edge)
            return elk_schema.Edge(
                id=haxorg_edge.edgeId,
                source=haxorg_edge.sourceId,
                target=haxorg_edge.targetId,
                sourcePort=haxorg_edge.sourcePortId,
                targetPort=haxorg_edge.targetPortId,
                extra=dict(haxorg_edge=haxorg_edge),
            )

        else:
            crossing_edge: HaxorgMMapEdgeCrossingSegment = self.fragmented_edge_map[
                edge_id]
            return elk_schema.Edge(
                id=crossing_edge.edgeId,
                extra=dict(crossing_edge=crossing_edge),
                source=crossing_edge.source,
                target=crossing_edge.target,
                sourcePort=crossing_edge.sourcePortId,
                targetPort=crossing_edge.targetPortId,
            )

    def getNestedVertices(self, vertex_id: str) -> List[str]:
        if vertex_id in self.hgraph.vertexNestingMap:
            return self.hgraph.vertexNestingMap[vertex_id]

        else:
            return []

    def getELKNodeNonRec(self, vertex_id: str) -> elk_schema.Node:
        data: Vertex = self.hgraph.vertices[vertex_id]
        assert isinstance(data, Vertex)

        node_width = 150

        if data.vertexDescription:
            result = elk_schema.Node(
                id=data.vertexId,
                height=elk_converter.get_node_height_for_text(
                    data.vertexName,
                    expected_width=node_width,
                    font_size=12,
                    size_step=50,
                ),
                width=node_width,
                extra=dict(data=data),
                labels=[],
                properties={
                    "nodeLabels.placement": "[H_CENTER, V_TOP, OUTSIDE]",
                    "portLabels.placement": "NEXT_TO_PORT_OF_POSSIBLE",
                },
            )

            if data.vertexName:
                result.labels.append(
                    elk_converter.single_line_label(
                        id=f"{data.vertexId}-title-label",
                        text=data.vertexName,
                        font_size=8.0,
                    ))

        else:
            result = elk_schema.Node(
                id=data.vertexId,
                width=node_width,
                height=elk_converter.get_node_height_for_text(
                    data.vertexName,
                    expected_width=node_width,
                    font_size=12,
                ),
                extra=dict(data=data),
            )

        if data.vertexId in self.node_crossing_ports:
            if not result.ports:
                result.ports = []

            for _, port in self.node_crossing_ports[data.vertexId].items():
                result.ports.append(elk_schema.Port(
                    id=port.portId,
                    width=10,
                    height=10,
                ))

        return result
