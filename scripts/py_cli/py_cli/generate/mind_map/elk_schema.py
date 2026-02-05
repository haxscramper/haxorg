#!/usr/bin/env python

from dataclasses import dataclass
from enum import Enum
from pathlib import Path
from tempfile import TemporaryDirectory
from typing import Any, Dict, List, Optional, Union

from beartype import beartype
from beartype.typing import List, Optional, Tuple
from matplotlib.patches import FancyArrowPatch, FancyBboxPatch
import matplotlib.patches as patches
from matplotlib.path import Path as MPath
import matplotlib.pyplot as plt
import numpy as np
from plumbum import local
from pydantic import BaseModel, Field, field_serializer, field_validator, model_serializer, model_validator, ValidationError


@beartype
def parse_indents(v: str) -> Optional[List[str]]:
    if v is None:
        return None

    if isinstance(v, str):
        v = v.strip()
        if v == "[]":
            return []
        if v.startswith("[") and v.endswith("]"):
            content = v[1:-1].strip()
            if not content:
                return []
            items = [item.strip() for item in content.split(",")]
            return [item for item in items if item]
        return None
    return v


@beartype
def serialize_indents(value: Optional[List[str]]) -> Optional[str]:
    if value is None:
        return None
    if not value:
        return "[]"
    return f"[{','.join(value)}]"


class ELKAlgorithm(str, Enum):
    LAYERED = "layered"
    FORCE = "force"
    STRESS = "stress"
    MRTREE = "mrtree"
    RADIAL = "radial"
    DISCO = "disco"
    RECTPACKING = "rectpacking"


class ELKDirection(str, Enum):
    RIGHT = "RIGHT"
    LEFT = "LEFT"
    DOWN = "DOWN"
    UP = "UP"


class ELKAlignment(str, Enum):
    RIGHT = "RIGHT"
    LEFT = "LEFT"
    CENTER = "CENTER"
    TOP = "TOP"
    BOTTOM = "BOTTOM"


class ELKEdgeRouting(str, Enum):
    ORTHOGONAL = "ORTHOGONAL"
    POLYLINE = "POLYLINE"
    SPLINES = "SPLINES"


class ELKHierarchyHandling(str, Enum):
    SEPARATE_CHILDREN = "SEPARATE_CHILDREN"
    INCLUDE_CHILDREN = "INCLUDE_CHILDREN"


class NodeFlexibility(str, Enum):
    NODE_SIZE = "NODE_SIZE"
    PORT_POSITION = "PORT_POSITION"
    NONE = "NONE"


class PortSide(str, Enum):
    NORTH = "NORTH"
    SOUTH = "SOUTH"
    EAST = "EAST"
    WEST = "WEST"


class PortConstraints(str, Enum):
    FIXED_ORDER = "FIXED_ORDER"
    FIXED_SIDE = "FIXED_SIDE"
    FIXED_POS = "FIXED_POS"
    FREE = "FREE"
    UNDEFINED = "UNDEFINED"


class PortAlignment(str, Enum):
    CENTER = "CENTER"
    BEGIN = "BEGIN"
    END = "END"
    DISTRIBUTED = "DISTRIBUTED"
    JUSTIFIED = "JUSTIFIED"


class ELKNodePlacementBK(BaseModel, extra="forbid"):
    fixedAlignment: Optional[str] = None


class ELKNodePlacement(BaseModel, extra="forbid"):
    bk: Optional[ELKNodePlacementBK] = None


class DirectionCongruency(str, Enum):
    READING_DIRECTION = "READING_DIRECTION"
    ROTATION = "ROTATION"


class InteractiveReferencePoint(str, Enum):
    CENTER = "CENTER"
    TOP_LEFT = "TOP_LEFT"


class PortSortingStrategy(str, Enum):
    INPUT_ORDER = "INPUT_ORDER"
    PORT_DEGREE = "PORT_DEGREE"


class CycleBreakingStrategy(str, Enum):
    GREEDY = "GREEDY"
    DEPTH_FIRST = "DEPTH_FIRST"
    INTERACTIVE = "INTERACTIVE"


class LayeringStrategy(str, Enum):
    NETWORK_SIMPLEX = "NETWORK_SIMPLEX"
    LONGEST_PATH = "LONGEST_PATH"
    COFFMAN_GRAHAM = "COFFMAN_GRAHAM"
    INTERACTIVE = "INTERACTIVE"
    STRETCH_WIDTH = "STRETCH_WIDTH"
    MIN_WIDTH = "MIN_WIDTH"


class LayerConstraint(str, Enum):
    NONE = "NONE"
    FIRST = "FIRST"
    FIRST_SEPARATE = "FIRST_SEPARATE"
    LAST = "LAST"
    LAST_SEPARATE = "LAST_SEPARATE"


class NodePromotionStrategy(str, Enum):
    NONE = "NONE"
    LEFT = "LEFT"
    RIGHT = "RIGHT"
    ALL = "ALL"
    NIKOLOV = "NIKOLOV"


class CrossingMinimizationStrategy(str, Enum):
    LAYER_SWEEP = "LAYER_SWEEP"
    INTERACTIVE = "INTERACTIVE"


class GreedySwitchType(str, Enum):
    OFF = "OFF"
    ONE_SIDED = "ONE_SIDED"
    TWO_SIDED = "TWO_SIDED"


class NodePlacementStrategy(str, Enum):
    BRANDES_KOEPF = "BRANDES_KOEPF"
    LINEAR_SEGMENTS = "LINEAR_SEGMENTS"
    INTERACTIVE = "INTERACTIVE"
    SIMPLE = "SIMPLE"
    NETWORK_SIMPLEX = "NETWORK_SIMPLEX"


class EdgeStraighteningStrategy(str, Enum):
    NONE = "NONE"
    IMPROVE_STRAIGHTNESS = "IMPROVE_STRAIGHTNESS"


class FixedAlignment(str, Enum):
    NONE = "NONE"
    LEFTUP = "LEFTUP"
    RIGHTUP = "RIGHTUP"
    LEFTDOWN = "LEFTDOWN"
    RIGHTDOWN = "RIGHTDOWN"
    BALANCED = "BALANCED"


class PortProperties(BaseModel, extra="forbid"):
    port: Optional[Dict[str, Any]] = None
    portConstraints: Optional[PortConstraints] = None
    portAlignment: Optional[PortAlignment] = None
    allowNonFlowPortsToSwitchSides: Optional[bool] = None
    side: Optional[PortSide] = None

    @model_validator(mode="before")
    @classmethod
    def unflatten_port_properties(
        cls,
        values: Dict[str, Any],
    ) -> Dict[str, Any]:
        if not isinstance(values, dict):
            return values

        result = {}
        port_data: Dict[str, Any] = {}

        for key, value in values.items():
            if key.startswith("port."):
                parts = key.split(".", 1)
                if len(parts) == 2:
                    if "port" not in port_data:
                        port_data["port"] = {}
                    port_data["port"][parts[1]] = value
            else:
                result[key] = value

        result.update(port_data)
        return result

    @model_serializer(mode='plain')
    def serialize_model(self) -> Dict[str, Any]:
        data: Dict[str, Any] = {}

        if self.portConstraints is not None:
            data["portConstraints"] = self.portConstraints
        if self.portAlignment is not None:
            data["portAlignment"] = self.portAlignment
        if self.allowNonFlowPortsToSwitchSides is not None:
            data["allowNonFlowPortsToSwitchSides"] = self.allowNonFlowPortsToSwitchSides

        if self.side is not None:
            data["port.side"] = self.side.name

        # Handle port nested data
        if hasattr(self, "__pydantic_extra__") and self.__pydantic_extra__:
            for key, value in self.__pydantic_extra__.items():
                if key == "port" and isinstance(value, dict):
                    for port_key, port_value in value.items():
                        data[f"port.{port_key}"] = port_value
                else:
                    data[key] = value

        return data


class Point(BaseModel, extra="forbid"):
    x: float
    y: float


class Label(BaseModel, extra="forbid"):
    id: str
    x: Optional[float] = None
    y: Optional[float] = None
    width: Optional[float] = None
    height: Optional[float] = None
    text: Optional[str] = None
    labels: Optional[List["Label"]] = None
    layoutOptions: Optional[Dict[str, Any]] = None
    extra: Optional[Dict[str, Any]] = None


class Port(BaseModel, extra="forbid"):
    id: str
    x: Optional[float] = None
    y: Optional[float] = None
    width: Optional[float] = None
    height: Optional[float] = None
    labels: Optional[List[Label]] = None
    properties: Optional[PortProperties] = None
    layoutOptions: Optional[Dict[str, Any]] = None
    extra: Optional[Dict[str, Any]] = None


class EdgeSection(BaseModel, extra="forbid"):
    id: Optional[str] = None
    startPoint: Point
    endPoint: Point
    bendPoints: Optional[List[Point]] = None
    incomingShape: Optional[str] = None
    outgoingShape: Optional[str] = None
    incomingSections: Optional[List[str]] = None
    outgoingSections: Optional[List[str]] = None


class Edge(BaseModel, extra="forbid"):
    id: str
    source: Optional[str] = None
    sourcePort: Optional[str] = None
    target: Optional[str] = None
    targetPort: Optional[str] = None
    sources: Optional[List[str]] = None
    targets: Optional[List[str]] = None
    sourcePoint: Optional[Point] = None
    targetPoint: Optional[Point] = None
    bendPoints: Optional[List[Point]] = None
    sections: Optional[List[EdgeSection]] = None
    labels: Optional[List[Label]] = None
    junctionPoints: Optional[List[Point]] = None
    layoutOptions: Optional[Dict[str, Any]] = None
    extra: Optional[Dict[str, Any]] = None

    def __hash__(self) -> int:
        return hash(self.id)

    def __eq__(self, other: Any) -> bool:
        return isinstance(other, Edge) and self.id == other.id


class Node(BaseModel, extra="forbid"):
    id: str
    extra: Optional[Dict[str, Any]] = None
    x: Optional[float] = None
    y: Optional[float] = None
    children: Optional[List["Node"]] = None
    width: Optional[float] = None
    height: Optional[float] = None
    type: Optional[str] = None
    ports: Optional[List[Port]] = None
    labels: Optional[List[Label]] = None
    edges: Optional[List[Edge]] = None
    properties: Optional[Dict[str, Any]] = None
    layoutOptions: Optional[Dict[str, Any]] = None


class Graph(BaseModel, extra="forbid"):
    id: str
    x: Optional[float] = None
    y: Optional[float] = None
    width: Optional[float] = None
    height: Optional[float] = None
    layoutOptions: Dict[str, Any] = Field(default_factory=dict)
    children: List[Node] = Field(default_factory=list)
    edges: Optional[List[Edge]] = None
    ports: Optional[List[Port]] = None
    labels: Optional[List[Label]] = None
    extra: Optional[Dict[str, Any]] = None


Node.model_rebuild()
Label.model_rebuild()

import json
from pathlib import Path
from typing import Any, Dict, Optional


class GraphSerializer:

    @staticmethod
    def to_nested_json(graph: Graph) -> Dict[str, Any]:
        return graph.model_dump(exclude_none=True)

    @staticmethod
    def from_json(data: Dict[str, Any]) -> Graph:
        return Graph(**data)

    @staticmethod
    def save_to_file(graph: Graph, filepath: Path, use_dotted: bool = True) -> None:
        data = GraphSerializer.to_nested_json(graph)

        with open(filepath, "w") as f:
            json.dump(data, f, indent=2)

    @staticmethod
    def load_from_file(filepath: Path) -> Graph:
        with open(filepath, "r") as f:
            data = json.load(f)
        return GraphSerializer.from_json(data)


def validate_graph_structure(graph: Graph) -> bool:
    node_ids = set()
    port_ids = set()
    edge_ids = set()
    label_ids = set()

    def validate_label(label: Label) -> None:
        if label.extra and not label.id:
            raise ValueError(f"Label {label} has 'extra' field, but not ID")

        if label.id and label.id in label_ids:
            raise ValueError(f"Duplicate label ID: {label.id}")

        label_ids.add(label.id)

    def validate_nodes(node: Node) -> None:
        if node.id in node_ids:
            raise ValueError(f"Duplicate node id: {node.id}")
        node_ids.add(node.id)

        if node.labels:
            for l in node.labels:
                validate_label(l)

        if node.ports:
            for port in node.ports:
                if port.id in port_ids:
                    raise ValueError(f"Duplicate port id: {port.id}")
                port_ids.add(port.id)

            if port.labels:
                for l in port.labels:
                    validate_label(l)

        if node.children:
            for child in node.children:
                validate_nodes(child)

    if graph.children:
        for node in graph.children:
            validate_nodes(node)

    if graph.ports:
        for port in graph.ports:
            if port.id in port_ids:
                raise ValueError(f"Duplicate port id: {port.id}")
            port_ids.add(port.id)

    def validate_edges(edges: Optional[List[Edge]]) -> None:
        if not edges:
            return

        for edge in edges:
            if edge.id in edge_ids:
                raise ValueError(f"Duplicate edge id: {edge.id}")
            edge_ids.add(edge.id)

            if edge.labels:
                for l in edge.labels:
                    validate_label(l)

            if edge.source is not None:
                if edge.source not in node_ids and edge.source not in port_ids:
                    raise ValueError(
                        f"Edge {edge.id} references unknown source: {edge.source}")

            if edge.target is not None:
                if edge.target not in node_ids and edge.target not in port_ids:
                    raise ValueError(
                        f"Edge {edge.id} references unknown target: {edge.target}")

            if edge.sourcePort is not None:
                if edge.sourcePort not in port_ids:
                    raise ValueError(
                        f"Edge {edge.id} references unknown source port: {edge.sourcePort}"
                    )

            if edge.targetPort is not None:
                if edge.targetPort not in port_ids:
                    raise ValueError(
                        f"Edge {edge.id} references unknown target port: {edge.targetPort}"
                    )

            if edge.sources:
                for source in edge.sources:
                    if source not in node_ids and source not in port_ids:
                        raise ValueError(
                            f"Edge {edge.id} references unknown source: {source}")

            if edge.targets:
                for target in edge.targets:
                    if target not in node_ids and target not in port_ids:
                        raise ValueError(
                            f"Edge {edge.id} references unknown target: {target}")

    validate_edges(graph.edges)

    def validate_node_edges(node: Node) -> None:
        if node.edges:
            validate_edges(node.edges)
        if node.children:
            for child in node.children:
                validate_node_edges(child)

    if graph.children:
        for node in graph.children:
            validate_node_edges(node)

    return True


@dataclass
class AbsolutePosition:
    x: float
    y: float
    width: float
    height: float
    id: str
    type: Optional[str] = None


@beartype
def compute_absolute_positions(
    graph: Graph
) -> Tuple[List[AbsolutePosition], List[Tuple[Point, List[Point], Point]]]:
    nodes = []
    edges_coords = []

    def process_node(node: Node, parent_x: float = 0, parent_y: float = 0) -> None:
        abs_x = parent_x + (node.x or 0)
        abs_y = parent_y + (node.y or 0)

        nodes.append(
            AbsolutePosition(x=abs_x,
                             y=abs_y,
                             width=node.width or 0,
                             height=node.height or 0,
                             id=str(node.id),
                             type=node.type))

        if node.children:
            for child in node.children:
                process_node(child, abs_x, abs_y)

    if graph.children:
        for node in graph.children:
            process_node(node)

    def process_edges(edges: Optional[List[Edge]],
                      container_x: float = 0,
                      container_y: float = 0) -> None:
        if not edges:
            return

        for edge in edges:
            if edge.sections:
                for section in edge.sections:
                    start = Point(x=container_x + section.startPoint.x,
                                  y=container_y + section.startPoint.y)
                    end = Point(x=container_x + section.endPoint.x,
                                y=container_y + section.endPoint.y)
                    bends = []
                    if section.bendPoints:
                        for bend in section.bendPoints:
                            bends.append(
                                Point(x=container_x + bend.x, y=container_y + bend.y))
                    edges_coords.append((start, bends, end))
            elif edge.sourcePoint and edge.targetPoint:
                start = Point(x=container_x + edge.sourcePoint.x,
                              y=container_y + edge.sourcePoint.y)
                end = Point(x=container_x + edge.targetPoint.x,
                            y=container_y + edge.targetPoint.y)
                bends = []
                if edge.bendPoints:
                    for bend in edge.bendPoints:
                        bends.append(Point(x=container_x + bend.x,
                                           y=container_y + bend.y))
                edges_coords.append((start, bends, end))

    process_edges(graph.edges)

    def process_node_edges(node: Node, parent_x: float = 0, parent_y: float = 0) -> None:
        abs_x = parent_x + (node.x or 0)
        abs_y = parent_y + (node.y or 0)

        process_edges(node.edges, abs_x, abs_y)

        if node.children:
            for child in node.children:
                process_node_edges(child, abs_x, abs_y)

    if graph.children:
        for node in graph.children:
            process_node_edges(node)

    return nodes, edges_coords


from dataclasses import dataclass
from typing import Optional


@dataclass
class BoundingBox:
    min_x: float
    min_y: float
    max_x: float
    max_y: float

    @property
    def width(self) -> float:
        return self.max_x - self.min_x

    @property
    def height(self) -> float:
        return self.max_y - self.min_y


def compute_graph_bounding_box(graph: Graph,
                               parent_x: float = 0.0,
                               parent_y: float = 0.0) -> BoundingBox:
    min_x = float("inf")
    min_y = float("inf")
    max_x = float("-inf")
    max_y = float("-inf")

    def update_bounds(x: float,
                      y: float,
                      width: float = 0.0,
                      height: float = 0.0) -> None:
        nonlocal min_x, min_y, max_x, max_y
        min_x = min(min_x, x)
        min_y = min(min_y, y)
        max_x = max(max_x, x + width)
        max_y = max(max_y, y + height)

    def process_label(label: Label, abs_x: float, abs_y: float) -> None:
        label_x = abs_x + (label.x or 0.0)
        label_y = abs_y + (label.y or 0.0)
        update_bounds(label_x, label_y, label.width or 0.0, label.height or 0.0)

        if label.labels:
            for sub_label in label.labels:
                process_label(sub_label, label_x, label_y)

    def process_port(port: Port, abs_x: float, abs_y: float) -> None:
        port_x = abs_x + (port.x or 0.0)
        port_y = abs_y + (port.y or 0.0)
        update_bounds(port_x, port_y, port.width or 0.0, port.height or 0.0)

        if port.labels:
            for label in port.labels:
                process_label(label, port_x, port_y)

    def process_edge(edge: Edge) -> None:
        if edge.sourcePoint:
            update_bounds(edge.sourcePoint.x, edge.sourcePoint.y)
        if edge.targetPoint:
            update_bounds(edge.targetPoint.x, edge.targetPoint.y)
        if edge.bendPoints:
            for point in edge.bendPoints:
                update_bounds(point.x, point.y)
        if edge.sections:
            for section in edge.sections:
                update_bounds(section.startPoint.x, section.startPoint.y)
                update_bounds(section.endPoint.x, section.endPoint.y)
                if section.bendPoints:
                    for point in section.bendPoints:
                        update_bounds(point.x, point.y)
        if edge.junctionPoints:
            for point in edge.junctionPoints:
                update_bounds(point.x, point.y)
        if edge.labels:
            for label in edge.labels:
                process_label(label, 0.0, 0.0)

    def process_node(node: Node, abs_x: float, abs_y: float) -> None:
        node_x = abs_x + (node.x or 0.0)
        node_y = abs_y + (node.y or 0.0)
        update_bounds(node_x, node_y, node.width or 0.0, node.height or 0.0)

        if node.ports:
            for port in node.ports:
                process_port(port, node_x, node_y)

        if node.labels:
            for label in node.labels:
                process_label(label, node_x, node_y)

        if node.edges:
            for edge in node.edges:
                process_edge(edge)

        if node.children:
            for child in node.children:
                process_node(child, node_x, node_y)

    graph_x = parent_x + (graph.x or 0.0)
    graph_y = parent_y + (graph.y or 0.0)
    update_bounds(graph_x, graph_y, graph.width or 0.0, graph.height or 0.0)

    for node in graph.children:
        process_node(node, graph_x, graph_y)

    if graph.edges:
        for edge in graph.edges:
            process_edge(edge)

    if graph.ports:
        for port in graph.ports:
            process_port(port, graph_x, graph_y)

    if graph.labels:
        for label in graph.labels:
            process_label(label, graph_x, graph_y)

    if min_x == float("inf"):
        return BoundingBox(0.0, 0.0, 0.0, 0.0)

    return BoundingBox(min_x, min_y, max_x, max_y)


def render_to_png(nodes: List[AbsolutePosition], edges: List[Tuple[Point, List[Point],
                                                                   Point]],
                  output_file: Path) -> None:
    fig, ax = plt.subplots(1, 1, figsize=(16, 10))

    max_x = max((n.x + n.width for n in nodes), default=100)
    max_y = max((n.y + n.height for n in nodes), default=100)

    ax.set_xlim(-10, max_x + 10)
    ax.set_ylim(-10, max_y + 10)
    ax.invert_yaxis()
    ax.set_aspect("equal")
    ax.axis("off")

    node_colors = {
        "start": "#90EE90",
        "activity": "#87CEEB",
        "gateway": "#FFD700",
        None: "#D3D3D3"
    }

    for node in nodes:
        color = node_colors.get(node.type, "#D3D3D3")

        if node.type == "gateway":
            diamond = patches.FancyBboxPatch((node.x, node.y),
                                             node.width,
                                             node.height,
                                             boxstyle="round,pad=0.02",
                                             facecolor=color,
                                             edgecolor="black",
                                             linewidth=1.5)
            ax.add_patch(diamond)
        elif node.type == "start":
            circle = patches.Circle((node.x + node.width / 2, node.y + node.height / 2),
                                    min(node.width, node.height) / 2,
                                    facecolor=color,
                                    edgecolor="black",
                                    linewidth=1.5)
            ax.add_patch(circle)
        else:
            rect = patches.Rectangle((node.x, node.y),
                                     node.width,
                                     node.height,
                                     facecolor=color,
                                     edgecolor="black",
                                     linewidth=1.5)
            ax.add_patch(rect)

        ax.text(node.x + node.width / 2,
                node.y + node.height / 2,
                node.id,
                ha="center",
                va="center",
                fontsize=8,
                fontweight="bold")

    for start, bends, end in edges:
        points = [start] + bends + [end]

        for i in range(len(points) - 1):
            ax.plot([points[i].x, points[i + 1].x], [points[i].y, points[i + 1].y],
                    "k-",
                    linewidth=1.5)

        if len(points) < 2:
            continue

        last_segment_start = points[-2]
        last_segment_end = points[-1]

        dx = last_segment_end.x - last_segment_start.x
        dy = last_segment_end.y - last_segment_start.y
        length = np.sqrt(dx**2 + dy**2)

        if length < 0.001:
            continue

        arrow = FancyArrowPatch((last_segment_start.x, last_segment_start.y),
                                (last_segment_end.x, last_segment_end.y),
                                arrowstyle="->",
                                mutation_scale=15,
                                linewidth=1.5,
                                color="black")
        ax.add_patch(arrow)

    plt.tight_layout()
    plt.savefig(output_file, dpi=150, bbox_inches="tight")
    plt.close()


from collections import defaultdict


@beartype
def extract_extra_data(graph: Graph) -> Dict[str, Dict[str, Any]]:
    extra_map: Dict[str, Dict[str, Any]] = defaultdict(lambda: dict())

    def collect_extra(obj: Any) -> None:
        if hasattr(obj, "id"):

            def get_property(name: str) -> None:
                if hasattr(obj, name) and getattr(obj, name) is not None:
                    extra_map[obj.id][name] = getattr(obj, name)
                    delattr(obj, name)

            get_property("extra")

            if isinstance(obj, Port):
                get_property("properties")

    def traverse_edge(edge: Edge) -> None:
        collect_extra(edge)

        if edge.labels:
            for label in edge.labels:
                collect_extra(label)

    def traverse_node(node: Node) -> None:
        collect_extra(node)
        if node.children:
            for child in node.children:
                traverse_node(child)

        if node.ports:
            for port in node.ports:
                collect_extra(port)
                if port.labels:
                    for label in port.labels:
                        traverse_label(label)

        if node.labels:
            for label in node.labels:
                traverse_label(label)

        if node.edges:
            for edge in node.edges:
                traverse_edge(edge)

    def traverse_label(label: Label) -> None:
        if label.id is not None:
            collect_extra(label)
        if label.labels:
            for sub_label in label.labels:
                traverse_label(sub_label)

    collect_extra(graph)

    for child in graph.children:
        traverse_node(child)

    if graph.edges:
        for edge in graph.edges:
            traverse_edge(edge)

    if graph.ports:
        for port in graph.ports:
            collect_extra(port)
            if port.labels:
                for label in port.labels:
                    traverse_label(label)

    if graph.labels:
        for label in graph.labels:
            traverse_label(label)

    return extra_map


@beartype
def restore_extra_data(graph: Graph, extra_map: Dict[str, Dict[str, Any]]) -> Graph:

    def restore_extra(obj: Any) -> None:
        if hasattr(obj, "id"):

            def transfer_property(name: str) -> None:
                if hasattr(obj, name):
                    obj_id = str(obj.id)
                    if obj_id in extra_map and name in extra_map[obj_id]:
                        setattr(obj, name, extra_map[obj_id][name])

            transfer_property("extra")

            if isinstance(obj, Port):
                transfer_property("properties")

    def traverse_edge(edge: Edge) -> None:
        restore_extra(edge)

        if edge.labels:
            for label in edge.labels:
                restore_extra(label)

    def traverse_node(node: Node) -> None:
        restore_extra(node)
        if node.children:
            for child in node.children:
                traverse_node(child)
        if node.ports:
            for port in node.ports:
                restore_extra(port)
                if port.labels:
                    for label in port.labels:
                        traverse_label(label)
        if node.labels:
            for label in node.labels:
                traverse_label(label)

        if node.edges:
            for edge in node.edges:
                traverse_edge(edge)

    def traverse_label(label: Label) -> None:
        if label.id is not None:
            restore_extra(label)
        if label.labels:
            for sub_label in label.labels:
                traverse_label(sub_label)

    restore_extra(graph)

    for child in graph.children:
        traverse_node(child)

    if graph.edges:
        for edge in graph.edges:
            traverse_edge(edge)

    if graph.ports:
        for port in graph.ports:
            restore_extra(port)
            if port.labels:
                for label in port.labels:
                    traverse_label(label)

    if graph.labels:
        for label in graph.labels:
            traverse_label(label)

    return graph


from py_scriptutils.script_logging import pprint_to_file, to_debug_json


def perform_graph_layout(graph: Graph, layout_script_path: str) -> Graph:
    validate_graph_structure(graph)

    with TemporaryDirectory() as output_subdir:
        dir = Path(output_subdir)
        dir = Path("/tmp")
        validated_path = dir / f"result_validated.json"
        extra_metadata = extract_extra_data(graph)
        GraphSerializer.save_to_file(graph, validated_path, use_dotted=True)

        pprint_to_file(extra_metadata, "/tmp/extra_metadata.py")

        layout_path = dir / f"result_layout.json"

        cmd = local[str(layout_script_path)]
        cmd.run([f"--input={validated_path}", f"--output={layout_path}"])

        LAYOUT_VALIDATION_DEBUG_PATH = Path("/tmp/layout-result-validation.txt")
        try:
            result = GraphSerializer.load_from_file(layout_path)
            restore_extra_data(result, extra_metadata)

            LAYOUT_VALIDATION_DEBUG_PATH.write_text("LAYOUT_VALIDATION_DEBUG_PATH OK")

            pprint_to_file(result, "/tmp/layout_result_model.py")

            return result

        except ValidationError as err:
            LAYOUT_VALIDATION_DEBUG_PATH.write_text(str(err))
            raise ValueError("Failed to validate resulting graph layout") from None
