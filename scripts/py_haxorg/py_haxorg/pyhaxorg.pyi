/* clang-format off */
from typing import *
from enum import Enum
from datetime import datetime, date, time
class Org:
    def getKind(self) -> OrgSemKind: ...
    def isGenerated(self) -> bool: ...
    def push_back(self, sub: Org) -> None: ...
    def at(self, idx: int) -> Org: ...
    def is_(self, kind: OrgSemKind) -> bool: ...
    def __getitem__(self, idx: int) -> Org: ...
    def __iter__(self, node: Org) -> auto: ...
    loc: Optional[LineCol]
    subnodes: List[Org]

class LineCol:
    line: int
    column: int
    pos: int

class Stmt(Org):
    def getAttached(self, kind: OrgSemKind) -> Optional[Org]: ...
    attached: List[Org]

class Inline(Org):
    pass

class StmtList(Org):
    loc: Optional[LineCol]

class Empty(Org):
    loc: Optional[LineCol]

class Cell(Org):
    loc: Optional[LineCol]

class Row(Org):
    loc: Optional[LineCol]
    cells: List[Cell]

class Table(Stmt):
    def getAttached(self, kind: OrgSemKind) -> Optional[Org]: ...
    loc: Optional[LineCol]
    rows: List[Row]
    attached: List[Org]

class HashTag(Inline):
    def prefixMatch(self, prefix: List[str]) -> bool: ...
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
    def isFootnoteDefinition(self) -> bool: ...
    def getAttached(self, kind: OrgSemKind) -> Optional[Org]: ...
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

class CmdName(Attached):
    loc: Optional[LineCol]

class CmdResults(Attached):
    loc: Optional[LineCol]

class CommandGroup(Stmt):
    def getAttached(self, kind: OrgSemKind) -> Optional[Org]: ...
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
    def popArg(self, key: str) -> Optional[CmdArgument]: ...
    loc: Optional[LineCol]
    positional: List[CmdArgument]
    named: Dict[str, CmdArgument]

class CmdAttr(Attached):
    loc: Optional[LineCol]
    target: str
    parameters: CmdArguments

class CmdArgument(Org):
    def getInt(self) -> Optional[int]: ...
    def getBool(self) -> Optional[bool]: ...
    def getString(self) -> str: ...
    loc: Optional[LineCol]
    key: Optional[str]
    value: str

class ExportFormat(Enum):
    Inline = 1
    Line = 2
    Block = 3

class Export(Block):
    loc: Optional[LineCol]
    format: ExportFormat
    exporter: str
    parameters: Optional[CmdArguments]
    placement: Optional[str]
    content: str

class AdmonitionBlock(Block):
    loc: Optional[LineCol]

class Call(Org):
    loc: Optional[LineCol]
    name: Optional[str]

class CodeLinePartRaw:
    code: str

class CodeLinePartCallout:
    name: str

class CodeLinePartTangle:
    target: str

CodeLinePartData = Union[CodeLinePartRaw, CodeLinePartCallout, CodeLinePartTangle]
class CodeLinePartKind(Enum):
    Raw = 1
    Callout = 2
    Tangle = 3

class CodeLinePart:
    def getRaw(self) -> CodeLinePartRaw: ...
    def getCallout(self) -> CodeLinePartCallout: ...
    def getTangle(self) -> CodeLinePartTangle: ...
    def getKind(self) -> CodeLinePartKind: ...
    data: CodeLinePartData

class CodeLine:
    parts: List[CodeLinePart]

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

CodeSwitchData = Union[CodeSwitchLineStart, CodeSwitchCalloutFormat, CodeSwitchRemoveCallout, CodeSwitchEmphasizeLine, CodeSwitchDedent]
class CodeSwitchKind(Enum):
    LineStart = 1
    CalloutFormat = 2
    RemoveCallout = 3
    EmphasizeLine = 4
    Dedent = 5

class CodeSwitch:
    def getLineStart(self) -> CodeSwitchLineStart: ...
    def getCalloutFormat(self) -> CodeSwitchCalloutFormat: ...
    def getRemoveCallout(self) -> CodeSwitchRemoveCallout: ...
    def getEmphasizeLine(self) -> CodeSwitchEmphasizeLine: ...
    def getDedent(self) -> CodeSwitchDedent: ...
    def getKind(self) -> CodeSwitchKind: ...
    data: CodeSwitchData

class CodeResults(Enum):
    Replace = 1

class CodeExports(Enum):
    _None = 1
    Both = 2
    Code = 3
    Results = 4

class Code(Block):
    loc: Optional[LineCol]
    lang: Optional[str]
    switches: List[CodeSwitch]
    exports: CodeExports
    lines: List[CodeLine]
    parameters: Optional[CmdArguments]
    cache: bool
    eval: bool
    noweb: bool
    hlines: bool
    tangle: bool

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

class TimeRepeat:
    mode: TimeRepeatMode
    period: TimeRepeatPeriod
    count: int

class TimeStatic:
    repeat: Optional[TimeRepeat]
    time: UserTime

class TimeDynamic:
    expr: str

TimeTimeVariant = Union[TimeStatic, TimeDynamic]
class TimeTimeKind(Enum):
    Static = 1
    Dynamic = 2

class Time(Org):
    def getStatic(self) -> TimeStatic: ...
    def getDynamic(self) -> TimeDynamic: ...
    def getTimeKind(self) -> TimeTimeKind: ...
    loc: Optional[LineCol]
    isActive: bool
    time: TimeTimeVariant

class TimeRange(Org):
    loc: Optional[LineCol]
    from_: Time
    to: Time

class Macro(Org):
    loc: Optional[LineCol]
    name: str
    arguments: List[str]

class SymbolParam:
    key: Optional[str]
    value: str

class Symbol(Org):
    loc: Optional[LineCol]
    name: str
    parameters: List[SymbolParam]
    positional: List[Org]

class SubtreeLogDescribedLog:
    desc: Optional[StmtList]

class SubtreeLogPriorityAction(Enum):
    Added = 1
    Removed = 2
    Changed = 3

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
    from_: str
    to: str
    on: Time

class SubtreeLogTag:
    on: Time
    tag: HashTag
    added: bool

SubtreeLogLogEntry = Union[SubtreeLogPriority, SubtreeLogNote, SubtreeLogRefile, SubtreeLogClock, SubtreeLogState, SubtreeLogTag]
class SubtreeLogKind(Enum):
    Priority = 1
    Note = 2
    Refile = 3
    Clock = 4
    State = 5
    Tag = 6

class SubtreeLog(Org):
    def setDescription(self, desc: StmtList) -> None: ...
    def getPriority(self) -> SubtreeLogPriority: ...
    def getNote(self) -> SubtreeLogNote: ...
    def getRefile(self) -> SubtreeLogRefile: ...
    def getClock(self) -> SubtreeLogClock: ...
    def getState(self) -> SubtreeLogState: ...
    def getTag(self) -> SubtreeLogTag: ...
    def getLogKind(self) -> SubtreeLogKind: ...
    loc: Optional[LineCol]
    log: SubtreeLogLogEntry

class SubtreePeriodKind(Enum):
    Clocked = 1
    Scheduled = 2
    Titled = 3
    Deadline = 4
    Created = 5
    Repeated = 6

class SubtreePeriod:
    def getTime(self) -> Time: ...
    def getTimeRange(self) -> TimeRange: ...
    kind: SubtreePeriodKind

class SubtreePropertySetMode(Enum):
    Override = 1
    Add = 2
    Subtract = 3

class SubtreePropertyInheritanceMode(Enum):
    ThisAndSub = 1
    OnlyThis = 2
    OnlySub = 3

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

class SubtreePropertyVisibilityLevel(Enum):
    Folded = 1
    Children = 2
    Content = 3
    All = 4

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

SubtreePropertyData = Union[SubtreePropertyNonblocking, SubtreePropertyTrigger, SubtreePropertyOrigin, SubtreePropertyExportLatexClass, SubtreePropertyExportLatexClassOptions, SubtreePropertyExportLatexHeader, SubtreePropertyExportLatexCompiler, SubtreePropertyOrdered, SubtreePropertyEffort, SubtreePropertyVisibility, SubtreePropertyExportOptions, SubtreePropertyBlocker, SubtreePropertyUnnumbered, SubtreePropertyCreated, SubtreePropertyUnknown]
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

class SubtreeProperty:
    def getNonblocking(self) -> SubtreePropertyNonblocking: ...
    def getTrigger(self) -> SubtreePropertyTrigger: ...
    def getOrigin(self) -> SubtreePropertyOrigin: ...
    def getExportLatexClass(self) -> SubtreePropertyExportLatexClass: ...
    def getExportLatexClassOptions(self) -> SubtreePropertyExportLatexClassOptions: ...
    def getExportLatexHeader(self) -> SubtreePropertyExportLatexHeader: ...
    def getExportLatexCompiler(self) -> SubtreePropertyExportLatexCompiler: ...
    def getOrdered(self) -> SubtreePropertyOrdered: ...
    def getEffort(self) -> SubtreePropertyEffort: ...
    def getVisibility(self) -> SubtreePropertyVisibility: ...
    def getExportOptions(self) -> SubtreePropertyExportOptions: ...
    def getBlocker(self) -> SubtreePropertyBlocker: ...
    def getUnnumbered(self) -> SubtreePropertyUnnumbered: ...
    def getCreated(self) -> SubtreePropertyCreated: ...
    def getUnknown(self) -> SubtreePropertyUnknown: ...
    def getKind(self) -> SubtreePropertyKind: ...
    mainSetRule: SubtreePropertySetMode
    subSetRule: SubtreePropertySetMode
    inheritanceMode: SubtreePropertyInheritanceMode
    data: SubtreePropertyData

class Subtree(Org):
    def getTimePeriods(self, kinds: IntSet[SubtreePeriodKind]) -> List[SubtreePeriod]: ...
    def getProperties(self, kind: SubtreePropertyKind, subkind: str) -> List[SubtreeProperty]: ...
    def getProperty(self, kind: SubtreePropertyKind, subkind: str) -> Optional[SubtreeProperty]: ...
    def getContextualProperties(self, kind: SubtreePropertyKind, subkind: str) -> List[SubtreeProperty]: ...
    def getContextualProperty(self, kind: SubtreePropertyKind, subkind: str) -> Optional[SubtreeProperty]: ...
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
    def isDescriptionList(self) -> bool: ...
    loc: Optional[LineCol]

class ListItemCheckbox(Enum):
    _None = 1
    Done = 2
    Empty = 3

class ListItem(Org):
    def isDescriptionItem(self) -> bool: ...
    loc: Optional[LineCol]
    checkbox: ListItemCheckbox
    header: Optional[Paragraph]

class LinkRaw:
    text: str

class LinkId:
    text: str

class LinkPerson:
    name: str

class LinkUserProtocol:
    protocol: str
    target: str

class LinkInternal:
    target: str

class LinkFootnote:
    target: str

class LinkFile:
    file: str

LinkData = Union[LinkRaw, LinkId, LinkPerson, LinkUserProtocol, LinkInternal, LinkFootnote, LinkFile]
class LinkKind(Enum):
    Raw = 1
    Id = 2
    Person = 3
    UserProtocol = 4
    Internal = 5
    Footnote = 6
    File = 7

class Link(Org):
    def getRaw(self) -> LinkRaw: ...
    def getId(self) -> LinkId: ...
    def getPerson(self) -> LinkPerson: ...
    def getUserProtocol(self) -> LinkUserProtocol: ...
    def getInternal(self) -> LinkInternal: ...
    def getFootnote(self) -> LinkFootnote: ...
    def getFile(self) -> LinkFile: ...
    def getLinkKind(self) -> LinkKind: ...
    loc: Optional[LineCol]
    description: Optional[Paragraph]
    data: LinkData

class DocumentOptionsDoExport:
    exportToc: bool

class DocumentOptionsExportFixed:
    exportLevels: int

DocumentOptionsTocExport = Union[DocumentOptionsDoExport, DocumentOptionsExportFixed]
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

class DocumentOptions(Org):
    def getProperties(self, kind: SubtreePropertyKind, subKind: str) -> List[SubtreeProperty]: ...
    def getProperty(self, kind: SubtreePropertyKind, subKind: str) -> Optional[SubtreeProperty]: ...
    def getDoExport(self) -> DocumentOptionsDoExport: ...
    def getExportFixed(self) -> DocumentOptionsExportFixed: ...
    def getTocExportKind(self) -> DocumentOptionsTocExportKind: ...
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

class Document(Org):
    def getProperties(self, kind: SubtreePropertyKind, subKind: str) -> List[SubtreeProperty]: ...
    def getProperty(self, kind: SubtreePropertyKind, subKind: str) -> Optional[SubtreeProperty]: ...
    loc: Optional[LineCol]
    title: Optional[Paragraph]
    author: Optional[Paragraph]
    creator: Optional[Paragraph]
    filetags: List[HashTag]
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

class IncludeExample:
    pass

class IncludeExport:
    pass

class IncludeSrc:
    pass

class IncludeOrgDocument:
    pass

IncludeData = Union[IncludeExample, IncludeExport, IncludeSrc, IncludeOrgDocument]
class IncludeKind(Enum):
    Example = 1
    Export = 2
    Src = 3
    OrgDocument = 4

class Include(Org):
    def getExample(self) -> IncludeExample: ...
    def getExport(self) -> IncludeExport: ...
    def getSrc(self) -> IncludeSrc: ...
    def getOrgDocument(self) -> IncludeOrgDocument: ...
    def getIncludeKind(self) -> IncludeKind: ...
    loc: Optional[LineCol]
    data: IncludeData

class DocumentGroup(Org):
    loc: Optional[LineCol]

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
    CommandAttr = 31
    CommandStartup = 32
    CommandName = 33
    CommandResults = 34
    CommandHeader = 35
    CommandOptions = 36
    CommandTblfm = 37
    CommandBackendOptions = 38
    AttrImg = 39
    CommandCaption = 40
    File = 41
    BlockExport = 42
    InlineExport = 43
    MultilineCommand = 44
    Result = 45
    Ident = 46
    BareIdent = 47
    AdmonitionTag = 48
    BigIdent = 49
    VerbatimMultilineBlock = 50
    CodeLine = 51
    CodeText = 52
    CodeTangle = 53
    CodeCallout = 54
    QuoteBlock = 55
    AdmonitionBlock = 56
    CenterBlock = 57
    VerseBlock = 58
    Example = 59
    SrcCode = 60
    SrcInlineCode = 61
    InlineCallCode = 62
    CmdCallCode = 63
    PassCode = 64
    CmdArguments = 65
    CmdFlag = 66
    CmdKey = 67
    CmdValue = 68
    CmdNamedValue = 69
    UrgencyStatus = 70
    TextSeparator = 71
    Paragraph = 72
    AnnotatedParagraph = 73
    Bold = 74
    Italic = 75
    Verbatim = 76
    Backtick = 77
    Underline = 78
    Strike = 79
    Quote = 80
    Angle = 81
    Monospace = 82
    Par = 83
    InlineMath = 84
    DisplayMath = 85
    Space = 86
    Punctuation = 87
    Colon = 88
    Word = 89
    Escaped = 90
    Newline = 91
    RawLink = 92
    Link = 93
    Macro = 94
    BackendRaw = 95
    Symbol = 96
    TimeAssoc = 97
    StaticActiveTime = 98
    StaticInactiveTime = 99
    DynamicActiveTime = 100
    DynamicInactiveTime = 101
    TimeRange = 102
    SimpleTime = 103
    Details = 104
    Summary = 105
    Table = 106
    TableRow = 107
    TableCell = 108
    InlineFootnote = 109
    Footnote = 110
    Horizontal = 111
    Filetags = 112
    OrgTag = 113
    HashTag = 114
    MetaSymbol = 115
    AtMention = 116
    BracTag = 117
    Drawer = 118
    LatexClass = 119
    LatexHeader = 120
    LatexCompiler = 121
    LatexClassOptions = 122
    HtmlHead = 123
    Columns = 124
    CmdPropertyArgs = 125
    CmdPropertyText = 126
    CmdPropertyRaw = 127
    PropertyList = 128
    Property = 129
    Placeholder = 130
    SubtreeDescription = 131
    SubtreeUrgency = 132
    Logbook = 133
    LogbookStateChange = 134
    RadioTarget = 135
    Target = 136

class OrgSemKind(Enum):
    StmtList = 1
    Empty = 2
    Cell = 3
    Row = 4
    Table = 5
    HashTag = 6
    Footnote = 7
    Completion = 8
    Paragraph = 9
    Center = 10
    Caption = 11
    CmdName = 12
    CmdResults = 13
    CommandGroup = 14
    Tblfm = 15
    Quote = 16
    Verse = 17
    Example = 18
    CmdArguments = 19
    CmdAttr = 20
    CmdArgument = 21
    Export = 22
    AdmonitionBlock = 23
    Call = 24
    Code = 25
    Time = 26
    TimeRange = 27
    Macro = 28
    Symbol = 29
    SubtreeLog = 30
    Subtree = 31
    InlineMath = 32
    Escaped = 33
    Newline = 34
    Space = 35
    Word = 36
    AtMention = 37
    RawText = 38
    Punctuation = 39
    Placeholder = 40
    BigIdent = 41
    Bold = 42
    Underline = 43
    Monospace = 44
    MarkQuote = 45
    Verbatim = 46
    Italic = 47
    Strike = 48
    Par = 49
    List = 50
    ListItem = 51
    Link = 52
    DocumentOptions = 53
    Document = 54
    ParseError = 55
    FileTarget = 56
    TextSeparator = 57
    Include = 58
    DocumentGroup = 59

class UserTimeBreakdown:
    year: Optional[int]
    month: Optional[int]
    day: Optional[int]
    hour: Optional[int]
    minute: Optional[int]
    second: Optional[int]
    zone: Optional[str]

class UserTime:
    def getBreakdown(self) -> UserTimeBreakdown: ...
    def format(self) -> str: ...

class OrgExporterJson:
    def visitNode(self, node: Org) -> None: ...
    def exportToString(self) -> str: ...
    def exportToFile(self, path: str) -> None: ...

class ExporterTreeOpts:
    withLineCol: bool
    withOriginalId: bool
    withSubnodeIdx: bool
    skipEmptyFields: bool
    startLevel: int
    withColor: bool

class OrgExporterTree:
    def toString(self, node: Org, opts: ExporterTreeOpts) -> str: ...
    def toFile(self, node: Org, path: str, opts: ExporterTreeOpts) -> None: ...

class OrgExporterYaml:
    def visitNode(self, node: Org) -> None: ...
    def exportToString(self) -> str: ...
    def exportToFile(self, path: str) -> None: ...

class OrgContext:
    def parseFile(self, file: str) -> Document: ...
    def parseString(self, text: str) -> Document: ...
    def parseProtobuf(self, file: str) -> Document: ...
    def saveProtobuf(self, doc: Document, file: str) -> None: ...
    def formatToString(self, arg: Org) -> str: ...
    baseTokenTracePath: Optional[str]
    tokenTracePath: Optional[str]
    parseTracePath: Optional[str]
    semTracePath: Optional[str]

class ExporterPython:
    def enablePyStreamTrace(self, stream: object) -> None: ...
    def enableBufferTrace(self) -> None: ...
    def getTraceBuffer(self) -> str: ...
    def enableFileTrace(self, path: str, colored: bool) -> None: ...
    def setVisitAnyIdAround(self, cb: function) -> None: ...
    def setVisitAnyIdIn(self, cb: function) -> None: ...
    def setVisitAnyField(self, cb: function) -> None: ...
    def setEvalTopCb(self, cb: function) -> None: ...
    def setVisitIdAround(self, kind: OrgSemKind, cb: function) -> None: ...
    def setEvalIdAround(self, kind: OrgSemKind, cb: function) -> None: ...
    def setVisitIdInCb(self, kind: OrgSemKind, cb: function) -> None: ...
    def setEvalIdIn(self, kind: OrgSemKind, cb: function) -> None: ...
    def setVisitLeafField(self, kind: LeafFieldType, cb: function) -> None: ...
    def setEvalLeafField(self, kind: LeafFieldType, cb: function) -> None: ...
    def setVisitOrgField(self, kind: OrgSemKind, cb: function) -> None: ...
    def setEvalOrgField(self, kind: OrgSemKind, cb: function) -> None: ...
    def setSelf(self, val: object) -> None: ...
    def setNewOrgRes(self, kind: OrgSemKind, cb: function) -> None: ...
    def setNewAnyOrgRes(self, cb: function) -> None: ...
    def setNewLeafRes(self, kind: LeafFieldType, cb: function) -> None: ...
    def setNewAnyLeafRes(self, cb: function) -> None: ...
    def setPushVisitAnyId(self, cb: function) -> None: ...
    def setPopVisitAnyId(self, cb: function) -> None: ...
    def setPushVisitId(self, kind: OrgSemKind, cb: function) -> None: ...
    def setPopVisitIdCb(self, kind: OrgSemKind, cb: function) -> None: ...
    def setVisitAnyHookCb(self, cb: function) -> None: ...
    def setVisitIdHook(self, kind: OrgSemKind, cb: function) -> None: ...
    def evalTop(self, org: Org) -> ExporterPythonRes: ...
    def eval(self, org: Org) -> ExporterPythonRes: ...

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

/* clang-format on */