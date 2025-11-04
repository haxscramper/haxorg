from pydantic import BaseModel, Field
from beartype.typing import List, Optional, Dict, Any
from beartype import beartype
from py_scriptutils.graph_utils import elk_converter
from py_scriptutils.graph_utils import elk_schema
import igraph as ig
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

class HaxorgMMapWalker(elk_converter.GraphWalker):
    flat_edge_map: Dict[str, Edge]

    def __init__(self, igraph: ig.Graph, hgraph: Graph) -> None:
        super().__init__()
        self.igraph = igraph
        self.hgraph = hgraph

        self.flat_edge_map = dict()
        for _, cat in self.hgraph.edges.items():
            for e in cat.edges:
                self.flat_edge_map[e.edgeId] = e

    def getTopVertices(self) -> List[str]:
        return self.hgraph.rootVertexIDs

    def getEdges(self) -> List[str]:
        return sorted(k for k in self.flat_edge_map)

    def getELKEdge(self, edge_id: str) -> elk_schema.Edge:
        data: Edge = self.flat_edge_map[edge_id]
        assert isinstance(data, Edge)
        return elk_schema.Edge(
            id=data.edgeId,
            source=data.sourceId,
            target=data.targetId,
            sourcePort=data.sourcePortId,
            targetPort=data.targetPortId,
            extra=dict(data=data),
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

        return result
