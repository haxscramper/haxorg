from pydantic import BaseModel, Field
from beartype.typing import List, Optional, Dict, Any
from beartype import beartype
import igraph as ig


class Edge(BaseModel, extra="forbid"):
    edgeId: str
    category: str
    sourceId: str
    targetId: str
    sourcePortId: Optional[str] = None
    targetPortId: Optional[str] = None
    bundleIndex: Optional[int] = None
    extra: Optional[Dict[str, Any]] = None


class Vertex(BaseModel, extra="forbid"):
    vertexId: str
    vertexName: Optional[str] = None
    vertexDescription: Optional[str] = None
    vertexKind: Optional[str] = None
    extra: Optional[Dict[str, Any]] = None


class Graph(BaseModel, extra="forbid"):
    edges: List[Edge]
    vertices: List[Vertex]


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

    for v in g.vertices:
        add_node(v)

    for e in g.edges:
        add_edge(e)

    return result
