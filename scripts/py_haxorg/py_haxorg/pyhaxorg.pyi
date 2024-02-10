/* clang-format off */
from typing import *
from enum import Enum
from datetime import datetime, date, time
class ExportFormat(Enum):
    Inline = 1
    Line = 2
    Block = 3

class CodeSwitchKind(Enum):
    LineStart = 1
    CalloutFormat = 2
    RemoveCallout = 3
    EmphasizeLine = 4
    Dedent = 5

class CodeResults(Enum):
    Replace = 1

class CodeExports(Enum):
    _None = 1
    Both = 2
    Code = 3
    Results = 4

class TimeRepeatMode(Enum):
    _None = 1
    Exact = 2
    FirstMatch = 3
    SameDay = 4

class TimeRepeatPeriod(Enum):
    Year = 1
    Month = 2
    Week = 3
    Day = 4
    Hour = 5
    Minute = 6

class TimeTimeKind(Enum):
    Static = 1
    Dynamic = 2

class SubtreeLogPriorityAction(Enum):
    Added = 1
    Removed = 2
    Changed = 3

class SubtreeLogKind(Enum):
    Priority = 1
    Note = 2
    Refile = 3
    Clock = 4
    State = 5
    Tag = 6

class SubtreePeriodKind(Enum):
    Clocked = 1
    Scheduled = 2
    Titled = 3
    Deadline = 4
    Created = 5
    Repeated = 6

class SubtreePropertySetMode(Enum):
    Override = 1
    Add = 2
    Subtract = 3

class SubtreePropertyInheritanceMode(Enum):
    ThisAndSub = 1
    OnlyThis = 2
    OnlySub = 3

class SubtreePropertyVisibilityLevel(Enum):
    Folded = 1
    Children = 2
    Content = 3
    All = 4

class SubtreePropertyKind(Enum):
    Nonblocking = 1
    Trigger = 2
    Origin = 3
    ExportLatexClass = 4
    ExportLatexClassOptions = 5
    ExportLatexHeader = 6
    ExportLatexCompiler = 7
    Ordered = 8
    Effort = 9
    Visibility = 10
    ExportOptions = 11
    Blocker = 12
    Unnumbered = 13
    Created = 14
    Unknown = 15

class ListItemCheckbox(Enum):
    _None = 1
    Done = 2
    Empty = 3

class LinkKind(Enum):
    Raw = 1
    Id = 2
    Person = 3
    Footnote = 4
    File = 5

class IncludeKind(Enum):
    Example = 1
    Export = 2
    Src = 3
    OrgDocument = 4

class DocumentOptionsTocExportKind(Enum):
    DoExport = 1
    ExportFixed = 2

class DocumentOptionsBrokenLinks(Enum):
    Raise = 1
    Ignore = 2
    Mark = 3

class DocumentOptionsVisibility(Enum):
    Overview = 1
    Content = 2
    ShowAll = 3
    Show2Levels = 4
    Show3Levels = 5
    Show4Levels = 6
    Show5Levels = 7
    ShowEverything = 8

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
    Urgency = 27
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
    UserNode = 3
    Empty = 4
    Error = 5
    ErrorTerminator = 6
    ErrorToken = 7
    InlineStmtList = 8
    StmtList = 9
    AssocStmtList = 10
    Subtree = 11
    SubtreeTimes = 12
    SubtreeStars = 13
    Completion = 14
    Checkbox = 15
    List = 16
    Bullet = 17
    ListItem = 18
    ListTag = 19
    Counter = 20
    Comment = 21
    RawText = 22
    Unparsed = 23
    Command = 24
    CommandArguments = 25
    CommandTitle = 26
    CommandAuthor = 27
    CommandCreator = 28
    CommandInclude = 29
    CommandLanguage = 30
    CommandAttrHtml = 31
    CommandName = 32
    CommandHeader = 33
    CommandOptions = 34
    CommandTblfm = 35
    CommandBackendOptions = 36
    AttrImg = 37
    CommandCaption = 38
    File = 39
    BlockExport = 40
    InlineExport = 41
    MultilineCommand = 42
    Result = 43
    Ident = 44
    BareIdent = 45
    AdmonitionTag = 46
    BigIdent = 47
    VerbatimMultilineBlock = 48
    CodeLine = 49
    CodeText = 50
    CodeTangle = 51
    CodeCallout = 52
    QuoteBlock = 53
    AdmonitionBlock = 54
    CenterBlock = 55
    VerseBlock = 56
    Example = 57
    SrcCode = 58
    SrcInlineCode = 59
    CallCode = 60
    PassCode = 61
    CmdArguments = 62
    CmdFlag = 63
    CmdKey = 64
    CmdValue = 65
    CmdNamedValue = 66
    UrgencyStatus = 67
    TextSeparator = 68
    Paragraph = 69
    AnnotatedParagraph = 70
    Bold = 71
    Italic = 72
    Verbatim = 73
    Backtick = 74
    Underline = 75
    Strike = 76
    Quote = 77
    Angle = 78
    Monospace = 79
    Par = 80
    InlineMath = 81
    DisplayMath = 82
    Space = 83
    Punctuation = 84
    Colon = 85
    Word = 86
    Escaped = 87
    Newline = 88
    RawLink = 89
    Link = 90
    Macro = 91
    BackendRaw = 92
    Symbol = 93
    TimeAssoc = 94
    StaticActiveTime = 95
    StaticInactiveTime = 96
    DynamicActiveTime = 97
    DynamicInactiveTime = 98
    TimeRange = 99
    SimpleTime = 100
    Details = 101
    Summary = 102
    Table = 103
    TableRow = 104
    TableCell = 105
    InlineFootnote = 106
    Footnote = 107
    Horizontal = 108
    Filetags = 109
    OrgTag = 110
    HashTag = 111
    MetaSymbol = 112
    AtMention = 113
    BracTag = 114
    Drawer = 115
    LatexClass = 116
    LatexHeader = 117
    LatexCompiler = 118
    LatexClassOptions = 119
    HtmlHead = 120
    Columns = 121
    CmdPropertyArgs = 122
    CmdPropertyText = 123
    CmdPropertyRaw = 124
    PropertyList = 125
    Property = 126
    Placeholder = 127
    SubtreeDescription = 128
    SubtreeUrgency = 129
    Logbook = 130
    LogbookStateChange = 131
    RadioTarget = 132
    Target = 133

class OrgBigIdentKind(Enum):
    _None = 1
    Must = 2
    MustNot = 3
    Should = 4
    ShouldNot = 5
    Required = 6
    Optional = 7
    ReallyShouldNot = 8
    OughtTo = 9
    WouldProbably = 10
    MayWishTo = 11
    Could = 12
    Might = 13
    Possible = 14
    Todo = 15
    Idea = 16
    Error = 17
    Fixme = 18
    Doc = 19
    Refactor = 20
    Review = 21
    Hack = 22
    Implement = 23
    Example = 24
    Question = 25
    Assume = 26
    Internal = 27
    Design = 28
    Why = 29
    Wip = 30
    Fix = 31
    Clean = 32
    Feature = 33
    Style = 34
    Repo = 35
    Skip = 36
    Break = 37
    Poc = 38
    Next = 39
    Later = 40
    Postponed = 41
    Stalled = 42
    Done = 43
    Partially = 44
    Cancelled = 45
    Failed = 46
    Note = 47
    Tip = 48
    Important = 49
    Caution = 50
    Warning = 51
    UserCodeComment = 52
    UserCommitMsg = 53
    UserTaskState = 54
    UserAdmonition = 55
    Other = 56
    StructIf = 57
    StructAnd = 58
    StructOr = 59
    StructNot = 60
    StructGet = 61
    StructSet = 62
    StructThen = 63
    StructElse = 64
    StructWhile = 65

class OrgSemKind(Enum):
    StmtList = 1
    Empty = 2
    Row = 3
    Table = 4
    HashTag = 5
    Footnote = 6
    Completion = 7
    Paragraph = 8
    Center = 9
    Caption = 10
    CommandGroup = 11
    Tblfm = 12
    Quote = 13
    Verse = 14
    Example = 15
    CmdArguments = 16
    CmdArgument = 17
    Export = 18
    AdmonitionBlock = 19
    Code = 20
    Time = 21
    TimeRange = 22
    Macro = 23
    Symbol = 24
    SubtreeLog = 25
    Subtree = 26
    InlineMath = 27
    Escaped = 28
    Newline = 29
    Space = 30
    Word = 31
    AtMention = 32
    RawText = 33
    Punctuation = 34
    Placeholder = 35
    BigIdent = 36
    Bold = 37
    Underline = 38
    Monospace = 39
    MarkQuote = 40
    Verbatim = 41
    Italic = 42
    Strike = 43
    Par = 44
    List = 45
    ListItem = 46
    Link = 47
    Document = 48
    ParseError = 49
    FileTarget = 50
    TextSeparator = 51
    Include = 52
    DocumentOptions = 53
    DocumentGroup = 54

class LeafFieldType(Enum):
    Int = 1
    UserTimeKind = 2
    QDate = 3
    Bool = 4
    FixedIdVec = 5
    TopIdVec = 6
    QDateTime = 7
    Str = 8
    Any = 9

class Org:
    def getKind() -> OrgSemKind: ...
    def isGenerated() -> bool: ...
    def push_back(sub: Org) -> None: ...
    def at(idx: int) -> Org: ...
    def is(kind: OrgSemKind) -> bool: ...
    def __getitem__(idx: int) -> Org: ...
    def __iter__(node: Org) -> auto: ...
    loc: Optional[LineCol]
    subnodes: List[Org]

class LineCol:
    line: int
    column: int
    pos: int

class Stmt(Org):
    def getAttached(kind: OrgSemKind) -> Optional[Org]: ...
    attached: List[Org]

class Inline(Org):
    pass

class StmtList(Org):
    loc: Optional[LineCol]

class Empty(Org):
    loc: Optional[LineCol]

class Row(Org):
    loc: Optional[LineCol]

class Table(Stmt):
    def getAttached(kind: OrgSemKind) -> Optional[Org]: ...
    loc: Optional[LineCol]
    rows: List[Row]
    attached: List[Org]

class HashTag(Inline):
    def prefixMatch(prefix: List[str]) -> bool: ...
    loc: Optional[LineCol]
    head: str
    subtags: List[HashTag]

class Footnote(Inline):
    loc: Optional[LineCol]
    tag: str
    definition: Optional[Org]

class Completion(Inline):
    loc: Optional[LineCol]
    done: int
    full: int
    isPercent: bool

class Paragraph(Stmt):
    def isFootnoteDefinition() -> bool: ...
    def getAttached(kind: OrgSemKind) -> Optional[Org]: ...
    loc: Optional[LineCol]
    attached: List[Org]

class Format(Org):
    pass

class Center(Format):
    loc: Optional[LineCol]

class Command(Org):
    pass

class LineCommand(Command):
    pass

class Standalone(LineCommand):
    pass

class Attached(LineCommand):
    pass

class Caption(Attached):
    loc: Optional[LineCol]
    text: Paragraph

class CommandGroup(Stmt):
    def getAttached(kind: OrgSemKind) -> Optional[Org]: ...
    loc: Optional[LineCol]
    attached: List[Org]

class Block(Command):
    pass

class Tblfm(Command):
    loc: Optional[LineCol]

class Quote(Org):
    loc: Optional[LineCol]

class Verse(Block):
    loc: Optional[LineCol]

class Example(Block):
    loc: Optional[LineCol]

class CmdArguments(Org):
    def popArg(key: str) -> Optional[CmdArgument]: ...
    loc: Optional[LineCol]
    positional: List[CmdArgument]
    named: Dict[str, CmdArgument]

class CmdArgument(Org):
    def getInt() -> Optional[int]: ...
    def getBool() -> Optional[bool]: ...
    def getString() -> str: ...
    loc: Optional[LineCol]
    key: Optional[str]
    value: str

class Export(Block):
    loc: Optional[LineCol]
    format: ExportFormat
    exporter: str
    parameters: Optional[CmdArguments]
    placement: Optional[str]
    content: str

class AdmonitionBlock(Block):
    loc: Optional[LineCol]

class Code(Block):
    loc: Optional[LineCol]
    lang: Optional[str]
    switches: List[CodeSwitch]
    exports: CodeExports
    parameters: Optional[CmdArguments]
    cache: bool
    eval: bool
    noweb: bool
    hlines: bool
    tangle: bool

class CodeSwitch:
    def getLineStart() -> CodeSwitchLineStart: ...
    def getCalloutFormat() -> CodeSwitchCalloutFormat: ...
    def getRemoveCallout() -> CodeSwitchRemoveCallout: ...
    def getEmphasizeLine() -> CodeSwitchEmphasizeLine: ...
    def getDedent() -> CodeSwitchDedent: ...
    def getKind() -> CodeSwitchKind: ...
    data: CodeSwitchData

class CodeSwitchLineStart:
    start: int
    extendLast: bool

class CodeSwitchCalloutFormat:
    format: str

class CodeSwitchRemoveCallout:
    remove: bool

class CodeSwitchEmphasizeLine:
    line: List[int]

class CodeSwitchDedent:
    value: int

class Time(Org):
    def getStatic() -> TimeStatic: ...
    def getDynamic() -> TimeDynamic: ...
    def getTimeKind() -> TimeTimeKind: ...
    loc: Optional[LineCol]
    isActive: bool
    time: TimeTimeVariant

class TimeRepeat:
    mode: TimeRepeatMode
    period: TimeRepeatPeriod
    count: int

class TimeStatic:
    repeat: Optional[TimeRepeat]
    time: datetime

class TimeDynamic:
    expr: str

class TimeRange(Org):
    loc: Optional[LineCol]
    from_: Time
    to: Time

class Macro(Org):
    loc: Optional[LineCol]
    name: str
    arguments: List[str]

class Symbol(Org):
    loc: Optional[LineCol]
    name: str
    parameters: List[SymbolParam]
    positional: List[Org]

class SymbolParam:
    key: Optional[str]
    value: str

class SubtreeLog(Org):
    def setDescription(desc: StmtList) -> None: ...
    def getPriority() -> SubtreeLogPriority: ...
    def getNote() -> SubtreeLogNote: ...
    def getRefile() -> SubtreeLogRefile: ...
    def getClock() -> SubtreeLogClock: ...
    def getState() -> SubtreeLogState: ...
    def getTag() -> SubtreeLogTag: ...
    def getLogKind() -> SubtreeLogKind: ...
    loc: Optional[LineCol]
    log: SubtreeLogLogEntry

class SubtreeLogDescribedLog:
    desc: Optional[StmtList]

class SubtreeLogPriority:
    oldPriority: Optional[str]
    newPriority: Optional[str]
    on: Time

class SubtreeLogNote:
    on: Time

class SubtreeLogRefile:
    on: Time
    from_: Link

class SubtreeLogClock:
    pass

class SubtreeLogState:
    from_: OrgBigIdentKind
    to: OrgBigIdentKind
    on: Time

class SubtreeLogTag:
    on: Time
    tag: HashTag
    added: bool

class Subtree(Org):
    def getTimePeriods(kinds: IntSet[SubtreePeriodKind]) -> List[SubtreePeriod]: ...
    def getProperties(kind: SubtreePropertyKind, subkind: str) -> List[SubtreeProperty]: ...
    def getProperty(kind: SubtreePropertyKind, subkind: str) -> Optional[SubtreeProperty]: ...
    def getContextualProperties(kind: SubtreePropertyKind, subkind: str) -> List[SubtreeProperty]: ...
    def getContextualProperty(kind: SubtreePropertyKind, subkind: str) -> Optional[SubtreeProperty]: ...
    loc: Optional[LineCol]
    level: int
    treeId: Optional[str]
    todo: Optional[str]
    completion: Optional[Completion]
    description: Optional[Paragraph]
    tags: List[HashTag]
    title: Paragraph
    logbook: List[SubtreeLog]
    properties: List[SubtreeProperty]
    closed: Optional[Time]
    deadline: Optional[Time]
    scheduled: Optional[Time]

class SubtreePeriod:
    def getTime() -> Time: ...
    def getTimeRange() -> TimeRange: ...
    kind: SubtreePeriodKind

class SubtreeProperty:
    def getNonblocking() -> SubtreePropertyNonblocking: ...
    def getTrigger() -> SubtreePropertyTrigger: ...
    def getOrigin() -> SubtreePropertyOrigin: ...
    def getExportLatexClass() -> SubtreePropertyExportLatexClass: ...
    def getExportLatexClassOptions() -> SubtreePropertyExportLatexClassOptions: ...
    def getExportLatexHeader() -> SubtreePropertyExportLatexHeader: ...
    def getExportLatexCompiler() -> SubtreePropertyExportLatexCompiler: ...
    def getOrdered() -> SubtreePropertyOrdered: ...
    def getEffort() -> SubtreePropertyEffort: ...
    def getVisibility() -> SubtreePropertyVisibility: ...
    def getExportOptions() -> SubtreePropertyExportOptions: ...
    def getBlocker() -> SubtreePropertyBlocker: ...
    def getUnnumbered() -> SubtreePropertyUnnumbered: ...
    def getCreated() -> SubtreePropertyCreated: ...
    def getUnknown() -> SubtreePropertyUnknown: ...
    def getKind() -> SubtreePropertyKind: ...
    mainSetRule: SubtreePropertySetMode
    subSetRule: SubtreePropertySetMode
    inheritanceMode: SubtreePropertyInheritanceMode
    data: SubtreePropertyData

class SubtreePropertyNonblocking:
    isBlocking: bool

class SubtreePropertyTrigger:
    pass

class SubtreePropertyOrigin:
    text: Paragraph

class SubtreePropertyExportLatexClass:
    latexClass: str

class SubtreePropertyExportLatexClassOptions:
    options: List[str]

class SubtreePropertyExportLatexHeader:
    header: str

class SubtreePropertyExportLatexCompiler:
    compiler: str

class SubtreePropertyOrdered:
    isOrdered: bool

class SubtreePropertyEffort:
    hours: int
    minutes: int

class SubtreePropertyVisibility:
    level: SubtreePropertyVisibilityLevel

class SubtreePropertyExportOptions:
    backend: str
    values: Dict[str, str]

class SubtreePropertyBlocker:
    blockers: List[str]

class SubtreePropertyUnnumbered:
    pass

class SubtreePropertyCreated:
    time: Time

class SubtreePropertyUnknown:
    value: Org

class LatexBody(Org):
    pass

class InlineMath(LatexBody):
    loc: Optional[LineCol]

class Leaf(Org):
    text: str

class Escaped(Leaf):
    loc: Optional[LineCol]
    text: str

class Newline(Leaf):
    loc: Optional[LineCol]
    text: str

class Space(Leaf):
    loc: Optional[LineCol]
    text: str

class Word(Leaf):
    loc: Optional[LineCol]
    text: str

class AtMention(Leaf):
    loc: Optional[LineCol]
    text: str

class RawText(Leaf):
    loc: Optional[LineCol]
    text: str

class Punctuation(Leaf):
    loc: Optional[LineCol]
    text: str

class Placeholder(Leaf):
    loc: Optional[LineCol]
    text: str

class BigIdent(Leaf):
    loc: Optional[LineCol]
    text: str

class Markup(Org):
    pass

class Bold(Markup):
    loc: Optional[LineCol]

class Underline(Markup):
    loc: Optional[LineCol]

class Monospace(Markup):
    loc: Optional[LineCol]

class MarkQuote(Markup):
    loc: Optional[LineCol]

class Verbatim(Markup):
    loc: Optional[LineCol]

class Italic(Markup):
    loc: Optional[LineCol]

class Strike(Markup):
    loc: Optional[LineCol]

class Par(Markup):
    loc: Optional[LineCol]

class List(Org):
    def isDescriptionList() -> bool: ...
    loc: Optional[LineCol]

class ListItem(Org):
    def isDescriptionItem() -> bool: ...
    loc: Optional[LineCol]
    checkbox: ListItemCheckbox
    header: Optional[Paragraph]

class Link(Org):
    def getRaw() -> LinkRaw: ...
    def getId() -> LinkId: ...
    def getPerson() -> LinkPerson: ...
    def getFootnote() -> LinkFootnote: ...
    def getFile() -> LinkFile: ...
    def getLinkKind() -> LinkKind: ...
    loc: Optional[LineCol]
    description: Optional[Paragraph]
    data: LinkData

class LinkRaw:
    text: str

class LinkId:
    text: str

class LinkPerson:
    name: str

class LinkFootnote:
    target: str

class LinkFile:
    file: str

class Document(Org):
    def getProperties(kind: SubtreePropertyKind, subKind: str) -> List[SubtreeProperty]: ...
    def getProperty(kind: SubtreePropertyKind, subKind: str) -> Optional[SubtreeProperty]: ...
    loc: Optional[LineCol]
    title: Optional[Paragraph]
    author: Optional[Paragraph]
    creator: Optional[Paragraph]
    email: Optional[RawText]
    language: List[str]
    options: DocumentOptions
    exportFileName: Optional[str]

class ParseError(Org):
    loc: Optional[LineCol]

class FileTarget(Org):
    loc: Optional[LineCol]
    path: str
    line: Optional[int]
    searchTarget: Optional[str]
    restrictToHeadlines: bool
    targetId: Optional[str]
    regexp: Optional[str]

class TextSeparator(Org):
    loc: Optional[LineCol]

class Include(Org):
    def getExample() -> IncludeExample: ...
    def getExport() -> IncludeExport: ...
    def getSrc() -> IncludeSrc: ...
    def getOrgDocument() -> IncludeOrgDocument: ...
    def getIncludeKind() -> IncludeKind: ...
    loc: Optional[LineCol]
    data: IncludeData

class IncludeExample:
    pass

class IncludeExport:
    pass

class IncludeSrc:
    pass

class IncludeOrgDocument:
    pass

class DocumentOptions(Org):
    def getProperties(kind: SubtreePropertyKind, subKind: str) -> List[SubtreeProperty]: ...
    def getProperty(kind: SubtreePropertyKind, subKind: str) -> Optional[SubtreeProperty]: ...
    def getDoExport() -> DocumentOptionsDoExport: ...
    def getExportFixed() -> DocumentOptionsExportFixed: ...
    def getTocExportKind() -> DocumentOptionsTocExportKind: ...
    loc: Optional[LineCol]
    brokenLinks: DocumentOptionsBrokenLinks
    initialVisibility: DocumentOptionsVisibility
    tocExport: DocumentOptionsTocExport
    properties: List[SubtreeProperty]
    smartQuotes: bool
    emphasizedText: bool
    specialStrings: bool
    fixedWidthSections: bool
    includeTimestamps: bool
    preserveLineBreaks: bool
    plaintextSubscripts: bool
    exportArchived: bool
    exportWithAuthor: bool
    exportBrokenLinks: bool
    exportWithClock: bool
    exportWithCreator: bool
    data: DocumentOptionsTocExport

class DocumentOptionsDoExport:
    exportToc: bool

class DocumentOptionsExportFixed:
    exportLevels: int

class DocumentGroup(Org):
    loc: Optional[LineCol]

class OrgExporterJson:
    def visitNode(node: Org) -> None: ...
    def exportToString() -> str: ...
    def exportToFile(path: str) -> None: ...

class ExporterTreeOpts:
    withLineCol: bool
    withOriginalId: bool
    withSubnodeIdx: bool
    skipEmptyFields: bool
    startLevel: int
    withColor: bool

class OrgExporterTree:
    def toString(node: Org, opts: ExporterTreeOpts) -> str: ...
    def toFile(node: Org, path: str, opts: ExporterTreeOpts) -> None: ...

class OrgExporterYaml:
    def visitNode(node: Org) -> None: ...
    def exportToString() -> str: ...
    def exportToFile(path: str) -> None: ...

class OrgContext:
    def parseFile(file: str) -> Document: ...
    def parseString(text: str) -> Document: ...

class ExporterPython:
    def enablePyStreamTrace(stream: object) -> None: ...
    def enableBufferTrace() -> None: ...
    def getTraceBuffer() -> str: ...
    def enableFileTrace(path: str) -> None: ...
    def setVisitAnyIdAround(cb: ExporterPythonPyFunc) -> None: ...
    def setVisitAnyIdIn(cb: ExporterPythonPyFunc) -> None: ...
    def setVisitAnyField(cb: ExporterPythonPyFunc) -> None: ...
    def setEvalTopCb(cb: ExporterPythonPyFunc) -> None: ...
    def setVisitIdAround(kind: OrgSemKind, cb: ExporterPythonPyFunc) -> None: ...
    def setEvalIdAround(kind: OrgSemKind, cb: ExporterPythonPyFunc) -> None: ...
    def setVisitIdInCb(kind: OrgSemKind, cb: ExporterPythonPyFunc) -> None: ...
    def setEvalIdIn(kind: OrgSemKind, cb: ExporterPythonPyFunc) -> None: ...
    def setVisitLeafField(kind: LeafFieldType, cb: ExporterPythonPyFunc) -> None: ...
    def setEvalLeafField(kind: LeafFieldType, cb: ExporterPythonPyFunc) -> None: ...
    def setVisitOrgField(kind: OrgSemKind, cb: ExporterPythonPyFunc) -> None: ...
    def setEvalOrgField(kind: OrgSemKind, cb: ExporterPythonPyFunc) -> None: ...
    def setSelf(val: object) -> None: ...
    def setNewOrgRes(kind: OrgSemKind, cb: ExporterPythonPyFunc) -> None: ...
    def setNewAnyOrgRes(cb: ExporterPythonPyFunc) -> None: ...
    def setNewLeafRes(kind: LeafFieldType, cb: ExporterPythonPyFunc) -> None: ...
    def setNewAnyLeafRes(cb: ExporterPythonPyFunc) -> None: ...
    def setPushVisitAnyId(cb: ExporterPythonPyFunc) -> None: ...
    def setPopVisitAnyId(cb: ExporterPythonPyFunc) -> None: ...
    def setPushVisitId(kind: OrgSemKind, cb: ExporterPythonPyFunc) -> None: ...
    def setPopVisitIdCb(kind: OrgSemKind, cb: ExporterPythonPyFunc) -> None: ...
    def setVisitAnyHookCb(cb: ExporterPythonPyFunc) -> None: ...
    def setVisitIdHook(kind: OrgSemKind, cb: ExporterPythonPyFunc) -> None: ...
    def evalTop(org: Org) -> ExporterPythonRes: ...
    def eval(org: Org) -> ExporterPythonRes: ...

/* clang-format on */