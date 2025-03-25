from typing import *
from enum import Enum
from datetime import datetime, date, time
class GraphPoint:
    def __init__(self, x: double, y: double) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    x: double
    y: double

class GraphPath:
    def __init__(self, points: List[GraphPoint], startPoint: Optional[GraphPoint], endPoint: Optional[GraphPoint], bezier: bool) -> None: ...
    def point(self, x: double, y: double) -> None: ...
    def point(self, p: GraphPoint) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    points: List[GraphPoint]
    startPoint: Optional[GraphPoint]
    endPoint: Optional[GraphPoint]
    bezier: bool

class GraphSize:
    def __init__(self, w: double, h: double) -> None: ...
    def height(self) -> double: ...
    def width(self) -> double: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    w: double
    h: double

class GraphRect:
    def __init__(self, left: double, top: double, width: double, height: double) -> None: ...
    def size(self) -> GraphSize: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    left: double
    top: double
    width: double
    height: double

class GraphNodeConstraint:
    def __init__(self) -> None: ...
    def getEmpty(self) -> GraphNodeConstraintEmpty: ...
    def getAlign(self) -> GraphNodeConstraintAlign: ...
    def getFixedRelative(self) -> GraphNodeConstraintFixedRelative: ...
    def getSeparate(self) -> GraphNodeConstraintSeparate: ...
    def getMultiSeparate(self) -> GraphNodeConstraintMultiSeparate: ...
    def getPageBoundary(self) -> GraphNodeConstraintPageBoundary: ...
    def getKind(self) -> Kind: ...
    @staticmethod
    def InitEmptyStatic(self, arg: GraphNodeConstraintEmpty) -> GraphNodeConstraint: ...
    @staticmethod
    def InitAlignStatic(self, arg: GraphNodeConstraintAlign) -> GraphNodeConstraint: ...
    @staticmethod
    def InitSeparateStatic(self, arg: GraphNodeConstraintSeparate) -> GraphNodeConstraint: ...
    @staticmethod
    def InitMultiSeparateStatic(self, arg: GraphNodeConstraintMultiSeparate) -> GraphNodeConstraint: ...
    @staticmethod
    def InitFixedRelativeStatic(self, arg: GraphNodeConstraintFixedRelative) -> GraphNodeConstraint: ...
    @staticmethod
    def InitPageBoundaryStatic(self, arg: GraphNodeConstraintPageBoundary) -> GraphNodeConstraint: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...

class GraphNodeConstraintEmpty:
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...

class GraphNodeConstraintAlign:
    def __init__(self, nodes: List[GraphNodeConstraintAlignSpec], dimension: GraphDimension) -> None: ...
    def toColaString(self) -> str: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    nodes: List[GraphNodeConstraintAlignSpec]
    dimension: GraphDimension

class GraphNodeConstraintAlignSpec:
    def __init__(self, node: int, fixPos: Optional[double], offset: double) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    node: int
    fixPos: Optional[double]
    offset: double

class GraphNodeConstraintSeparate:
    def __init__(self, left: GraphNodeConstraintAlign, right: GraphNodeConstraintAlign, separationDistance: double, isExactSeparation: bool, dimension: GraphDimension) -> None: ...
    def toColaString(self) -> str: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    left: GraphNodeConstraintAlign
    right: GraphNodeConstraintAlign
    separationDistance: double
    isExactSeparation: bool
    dimension: GraphDimension

class GraphNodeConstraintMultiSeparate:
    def __init__(self, lines: List[GraphNodeConstraintAlign], alignPairs: List[stdpair[int, int]], dimension: GraphDimension, separationDistance: double, isExactSeparation: bool) -> None: ...
    def toColaString(self) -> str: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    lines: List[GraphNodeConstraintAlign]
    alignPairs: List[stdpair[int, int]]
    dimension: GraphDimension
    separationDistance: double
    isExactSeparation: bool

class GraphNodeConstraintFixedRelative:
    def __init__(self, nodes: List[int], fixedPosition: bool) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    nodes: List[int]
    fixedPosition: bool

class GraphNodeConstraintPageBoundary:
    def __init__(self, rect: GraphRect, weight: double, nodes: List[int]) -> None: ...
    def toColaString(self, allRects: stdvector[vpscRectangle]) -> str: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    rect: GraphRect
    weight: double
    nodes: List[int]

class GraphEdge:
    def __init__(self, source: int, target: int, bundle: int) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    source: int
    target: int
    bundle: int

class GraphEdgeConstraint:
    def __init__(self, sourcePort: Port, targetPort: Port, sourceOffset: Optional[double], targetOffset: Optional[double], sourceCheckpoint: Optional[double], targetCheckpoint: Optional[double]) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    sourcePort: Port
    targetPort: Port
    sourceOffset: Optional[double]
    targetOffset: Optional[double]
    sourceCheckpoint: Optional[double]
    targetCheckpoint: Optional[double]

class GraphLayoutIR:
    def __init__(self, rectangles: List[GraphSize], edges: List[GraphEdge], nodeConstraints: List[GraphNodeConstraint], subgraphs: List[GraphLayoutIRSubgraph], edgeLabels: Dict[GraphEdge, GraphSize], edgeConstraints: Dict[GraphEdge, GraphEdgeConstraint], width: double, height: double, leftBBoxMargin: double, rightBBoxMargin: double, topBBoxMargin: double, bottomBBoxMargin: double, graphName: str, graphviz_size_scaling: int) -> None: ...
    def validate(self) -> None: ...
    def doGraphvizConvert(self) -> GraphLayoutIRResult: ...
    def doHolaConvert(self) -> GraphLayoutIRResult: ...
    def doColaConvert(self) -> GraphLayoutIRResult: ...
    def doColaSvgWrite(self, path: str) -> None: ...
    def doColaStrFormat(self) -> str: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    rectangles: List[GraphSize]
    edges: List[GraphEdge]
    nodeConstraints: List[GraphNodeConstraint]
    subgraphs: List[GraphLayoutIRSubgraph]
    edgeLabels: Dict[GraphEdge, GraphSize]
    edgeConstraints: Dict[GraphEdge, GraphEdgeConstraint]
    width: double
    height: double
    leftBBoxMargin: double
    rightBBoxMargin: double
    topBBoxMargin: double
    bottomBBoxMargin: double
    graphName: str
    graphviz_size_scaling: int

class GraphLayoutIRSubgraph:
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...

class GraphLayoutIREdge:
    def __init__(self, paths: List[GraphPath], labelRect: Optional[GraphRect]) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    paths: List[GraphPath]
    labelRect: Optional[GraphRect]

class GraphLayoutIRResult:
    def __init__(self, fixed: List[GraphRect], lines: Dict[GraphEdge, GraphLayoutIREdge], bbox: GraphRect, subgraphs: List[GraphLayoutIRResultSubgraph], subgraphPaths: List[List[int]]) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    fixed: List[GraphRect]
    lines: Dict[GraphEdge, GraphLayoutIREdge]
    bbox: GraphRect
    subgraphs: List[GraphLayoutIRResultSubgraph]
    subgraphPaths: List[List[int]]

class GraphLayoutIRResultSubgraph:
    def __init__(self, bbox: GraphRect, subgraphs: List[GraphLayoutIRResultSubgraph]) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    bbox: GraphRect
    subgraphs: List[GraphLayoutIRResultSubgraph]

class GraphDimension(Enum):
    XDIM = 1
    YDIM = 2
    UNSET = 3

class GraphNodeConstraintKind(Enum):
    Empty = 1
    Align = 2
    FixedRelative = 3
    Separate = 4
    MultiSeparate = 5
    PageBoundary = 6

class GraphEdgeConstraintPort(Enum):
    Default = 1
    North = 2
    South = 3
    West = 4
    East = 5
    Center = 6
