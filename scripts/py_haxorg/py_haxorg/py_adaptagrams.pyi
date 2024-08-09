from typing import *
from enum import Enum
from datetime import datetime, date, time
class OrgSpecName(Enum):
    Unnamed = 1
    Result = 2
    Year = 3
    Day = 4
    Clock = 5
    Repeater = 6
    Zone = 7
    Link = 8
    Tags = 9
    Tag = 10
    State = 11
    Protocol = 12
    Desc = 13
    Times = 14
    Drawer = 15
    Args = 16
    Name = 17
    Definition = 18
    Body = 19
    HeaderArgs = 20
    File = 21
    Kind = 22
    Lang = 23
    Prefix = 24
    Text = 25
    Todo = 26
    Importance = 27
    Title = 28
    Completion = 29
    Head = 30
    Subnodes = 31
    Properties = 32
    Logbook = 33
    Description = 34
    Logs = 35
    Newstate = 36
    Oldstate = 37
    Time = 38
    From = 39
    EndArgs = 40
    Flags = 41
    Value = 42
    Assoc = 43
    Main = 44
    Hash = 45
    Bullet = 46
    Counter = 47
    Checkbox = 48
    Header = 49
    To = 50
    Diff = 51
    Property = 52
    Subname = 53
    Values = 54
    Cells = 55
    Rows = 56
    Lines = 57
    Chunks = 58
    InheritanceMode = 59
    MainSetRule = 60
    SubSetRule = 61

class OrgNodeKind(Enum):
    _None = 1
    Document = 2
    Empty = 3
    InlineStmtList = 4
    StmtList = 5
    Checkbox = 6
    List = 7
    Bullet = 8
    ListItem = 9
    ListTag = 10
    Counter = 11
    File = 12
    ColonExample = 13
    TextSeparator = 14
    Paragraph = 15
    AnnotatedParagraph = 16
    TableRow = 17
    TableCell = 18
    Table = 19
    InlineFootnote = 20
    Footnote = 21
    Cmd = 22
    CmdArguments = 23
    CmdTitle = 24
    CmdAuthor = 25
    CmdCreator = 26
    CmdInclude = 27
    CmdLanguage = 28
    CmdAttr = 29
    CmdStartup = 30
    CmdName = 31
    CmdCustomTextCommand = 32
    CmdCustomArgsCommand = 33
    CmdCustomRawCommand = 34
    CmdResults = 35
    CmdHeader = 36
    CmdOptions = 37
    CmdTblfm = 38
    CmdCaption = 39
    CmdResult = 40
    CmdCallCode = 41
    CmdFlag = 42
    CmdKey = 43
    CmdValue = 44
    CmdNamedValue = 45
    CmdLatexClass = 46
    CmdLatexHeader = 47
    CmdLatexCompiler = 48
    CmdLatexClassOptions = 49
    CmdHtmlHead = 50
    CmdColumns = 51
    CmdPropertyArgs = 52
    CmdPropertyText = 53
    CmdPropertyRaw = 54
    CmdFiletags = 55
    BlockVerbatimMultiline = 56
    CodeLine = 57
    CodeText = 58
    CodeTangle = 59
    CodeCallout = 60
    BlockCode = 61
    BlockQuote = 62
    BlockComment = 63
    BlockCenter = 64
    BlockVerse = 65
    BlockExample = 66
    BlockExport = 67
    BlockDetails = 68
    BlockSummary = 69
    Ident = 70
    BigIdent = 71
    Bold = 72
    Italic = 73
    Verbatim = 74
    Backtick = 75
    Underline = 76
    Strike = 77
    Quote = 78
    Angle = 79
    Monospace = 80
    Par = 81
    InlineMath = 82
    DisplayMath = 83
    Space = 84
    Punctuation = 85
    Colon = 86
    Word = 87
    Escaped = 88
    Newline = 89
    RawLink = 90
    Link = 91
    Macro = 92
    Symbol = 93
    StaticActiveTime = 94
    StaticInactiveTime = 95
    DynamicActiveTime = 96
    DynamicInactiveTime = 97
    TimeRange = 98
    SimpleTime = 99
    HashTag = 100
    MetaSymbol = 101
    AtMention = 102
    Placeholder = 103
    RadioTarget = 104
    Target = 105
    SrcInlineCode = 106
    InlineCallCode = 107
    InlineExport = 108
    InlineComment = 109
    RawText = 110
    SubtreeDescription = 111
    SubtreeUrgency = 112
    DrawerLogbook = 113
    Drawer = 114
    DrawerPropertyList = 115
    DrawerProperty = 116
    Subtree = 117
    SubtreeTimes = 118
    SubtreeStars = 119
    SubtreeCompletion = 120
    SubtreeImportance = 121

class OrgSemKind(Enum):


class GraphPoint:
    def __init__(self, x: int, y: int) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    x: int
    y: int

class GraphPath:
    def __init__(self, points: List[GraphPoint], startPoint: Optional[GraphPoint], endPoint: Optional[GraphPoint], bezier: bool) -> None: ...
    def point(self, x: int, y: int) -> None: ...
    def point(self, p: GraphPoint) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    points: List[GraphPoint]
    startPoint: Optional[GraphPoint]
    endPoint: Optional[GraphPoint]
    bezier: bool

class GraphSize:
    def __init__(self, w: int, h: int) -> None: ...
    def height(self) -> int: ...
    def width(self) -> int: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    w: int
    h: int

class GraphRect:
    def __init__(self, left: int, top: int, width: int, height: int) -> None: ...
    def size(self) -> GraphSize: ...
    def setBottomLeft(self, x: int, y: int) -> None: ...
    def setTopRight(self, x: int, y: int) -> None: ...
    def setBottomLeft(self, p: GraphPoint) -> None: ...
    def setTopRight(self, p: GraphPoint) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    left: int
    top: int
    width: int
    height: int

class GraphConstraint:
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...

class GraphConstraintAlign:
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...

class GraphConstraintAlignSpec:
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...

class GraphConstraintSeparate:
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...

class GraphConstraintMultiSeparate:
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...

class GraphConstraintFixedRelative:
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...

class GraphConstraintPageBoundary:
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...

class GraphLayoutIR:
    def __init__(self, rectangles: List[GraphSize], edges: List[GraphLayoutIRIrEdge], constraints: List[GraphConstraint], subgraphs: List[GraphLayoutIRSubgraph], edgeLabels: Dict[GraphLayoutIRIrEdge, GraphSize], width: double, height: double, graphName: str, graphviz_size_scaling: int) -> None: ...
    def validate(self) -> None: ...
    def doHolaConvert(self) -> GraphLayoutIRResult: ...
    def doColaConvert(self) -> GraphLayoutIRResult: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    rectangles: List[GraphSize]
    edges: List[GraphLayoutIRIrEdge]
    constraints: List[GraphConstraint]
    subgraphs: List[GraphLayoutIRSubgraph]
    edgeLabels: Dict[GraphLayoutIRIrEdge, GraphSize]
    width: double
    height: double
    graphName: str
    graphviz_size_scaling: int

class GraphLayoutIRSubgraph:
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...

class GraphLayoutIREdge:
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...

class GraphLayoutIRResult:
    def __init__(self, fixed: List[GraphRect], lines: Dict[GraphLayoutIRIrEdge, GraphLayoutIREdge], bbox: GraphRect, subgraphs: List[GraphLayoutIRResultSubgraph], subgraphPaths: List[List[int]]) -> None: ...
    def getSubgraph(self, path: List[List]) -> GraphLayoutIRResultSubgraph: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    fixed: List[GraphRect]
    lines: Dict[GraphLayoutIRIrEdge, GraphLayoutIREdge]
    bbox: GraphRect
    subgraphs: List[GraphLayoutIRResultSubgraph]
    subgraphPaths: List[List[int]]

class GraphLayoutIRResultSubgraph:
    def __init__(self, bbox: GraphRect, subgraphs: List[GraphLayoutIRResultSubgraph]) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
    bbox: GraphRect
    subgraphs: List[GraphLayoutIRResultSubgraph]

class GraphLayoutIRColaResult:
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...

class GraphLayoutIRColaResultEdgeData:
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...
    def __getattr__(self, name: str) -> object: ...
