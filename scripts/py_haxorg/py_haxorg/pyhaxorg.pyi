/* clang-format off */
from typing import *
from enum import Enum
from datetime import datetime, date, time
class Org:
    def getKind(self) -> OrgSemKind: ...
    def isGenerated(self) -> bool: ...
    def push_back(self, sub: Org) -> None: ...
    def insert(self, pos: int, node: Org) -> None: ...
    def at(self, idx: int) -> Org: ...
    def is_(self, kind: OrgSemKind) -> bool: ...
    def __getitem__(self, idx: int) -> Org: ...
    def __iter__(self, node: Org) -> auto: ...
    loc: Optional[LineCol]
    documentId: Optional[int]
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
    pass

class Empty(Org):
    pass

class Cell(Org):
    pass

class Row(Org):
    cells: List[Cell]

class Table(Stmt):
    def getAttached(self, kind: OrgSemKind) -> Optional[Org]: ...
    rows: List[Row]
    attached: List[Org]

class HashTag(Inline):
    def prefixMatch(self, prefix: List[str]) -> bool: ...
    head: str
    subtags: List[HashTag]

class Footnote(Inline):
    tag: str
    definition: Optional[Org]

class Completion(Inline):
    done: int
    full: int
    isPercent: bool

class Paragraph(Stmt):
    def getAttached(self, kind: OrgSemKind) -> Optional[Org]: ...
    attached: List[Org]

class AnnotatedParagraphNone:
    pass

class AnnotatedParagraphFootnote:
    name: str

class AnnotatedParagraphAdmonition:
    name: BigIdent

class AnnotatedParagraphTimestamp:
    time: Time

AnnotatedParagraphData = Union[AnnotatedParagraphNone, AnnotatedParagraphFootnote, AnnotatedParagraphAdmonition, AnnotatedParagraphTimestamp]
class AnnotatedParagraphAnnotationKind(Enum):
    _None = 1
    Footnote = 2
    Admonition = 3
    Timestamp = 4

class AnnotatedParagraph(Stmt):
    def getNone(self) -> AnnotatedParagraphNone: ...
    def getFootnote(self) -> AnnotatedParagraphFootnote: ...
    def getAdmonition(self) -> AnnotatedParagraphAdmonition: ...
    def getTimestamp(self) -> AnnotatedParagraphTimestamp: ...
    def getAnnotationKind(self) -> AnnotatedParagraphAnnotationKind: ...
    def getAttached(self, kind: OrgSemKind) -> Optional[Org]: ...
    data: AnnotatedParagraphData
    attached: List[Org]

class Format(Org):
    pass

class Center(Format):
    pass

class Command(Org):
    pass

class LineCommand(Command):
    pass

class Standalone(LineCommand):
    pass

class Attached(LineCommand):
    pass

class Caption(Attached):
    text: Paragraph

class CmdName(Attached):
    pass

class CmdResults(Attached):
    pass

class CommandGroup(Stmt):
    def getAttached(self, kind: OrgSemKind) -> Optional[Org]: ...
    attached: List[Org]

class Block(Command):
    def getParameter(self, key: str) -> Optional[CmdArgument]: ...
    parameters: Optional[CmdArguments]

class Tblfm(Command):
    pass

class Quote(Org):
    pass

class CommentBlock(Org):
    pass

class Verse(Block):
    def getParameter(self, key: str) -> Optional[CmdArgument]: ...
    parameters: Optional[CmdArguments]

class Example(Block):
    def getParameter(self, key: str) -> Optional[CmdArgument]: ...
    parameters: Optional[CmdArguments]

class CmdArguments(Org):
    def getParameter(self, key: str) -> Optional[CmdArgument]: ...
    positional: List[CmdArgument]
    named: Dict[str, CmdArgument]

class CmdAttr(Attached):
    target: str
    parameters: CmdArguments

class CmdArgument(Org):
    def getInt(self) -> Optional[int]: ...
    def getBool(self) -> Optional[bool]: ...
    def getString(self) -> str: ...
    key: Optional[str]
    value: str

class ExportFormat(Enum):
    Inline = 1
    Line = 2
    Block = 3

class Export(Block):
    def getParameter(self, key: str) -> Optional[CmdArgument]: ...
    format: ExportFormat
    exporter: str
    placement: Optional[str]
    content: str
    parameters: Optional[CmdArguments]

class AdmonitionBlock(Block):
    def getParameter(self, key: str) -> Optional[CmdArgument]: ...
    parameters: Optional[CmdArguments]

class Call(Org):
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
    def getParameter(self, key: str) -> Optional[CmdArgument]: ...
    lang: Optional[str]
    switches: List[CodeSwitch]
    exports: CodeExports
    lines: List[CodeLine]
    cache: bool
    eval: bool
    noweb: bool
    hlines: bool
    tangle: bool
    parameters: Optional[CmdArguments]

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
    isActive: bool
    time: TimeTimeVariant

class TimeRange(Org):
    from_: Time
    to: Time

class Macro(Org):
    name: str
    arguments: List[str]

class SymbolParam:
    key: Optional[str]
    value: str

class Symbol(Org):
    name: str
    parameters: List[SymbolParam]
    positional: List[Org]

class SubtreeLogDescribedLog:
    desc: Optional[StmtList]

class SubtreeLogPriorityAction(Enum):
    Added = 1
    Removed = 2
    Changed = 3

class SubtreeLogPriority(SubtreeLogDescribedLog):
    oldPriority: Optional[str]
    newPriority: Optional[str]
    on: Time
    action: SubtreeLogPriorityAction

class SubtreeLogNote(SubtreeLogDescribedLog):
    on: Time

class SubtreeLogRefile(SubtreeLogDescribedLog):
    on: Time
    from_: Link

class SubtreeLogClock(SubtreeLogDescribedLog):
    from_: Time
    to: Optional[Time]

class SubtreeLogState(SubtreeLogDescribedLog):
    from_: str
    to: str
    on: Time

class SubtreeLogTag(SubtreeLogDescribedLog):
    on: Time
    tag: HashTag
    added: bool

class SubtreeLogUnknown(SubtreeLogDescribedLog):
    pass

SubtreeLogLogEntry = Union[SubtreeLogPriority, SubtreeLogNote, SubtreeLogRefile, SubtreeLogClock, SubtreeLogState, SubtreeLogTag, SubtreeLogUnknown]
class SubtreeLogKind(Enum):
    Priority = 1
    Note = 2
    Refile = 3
    Clock = 4
    State = 5
    Tag = 6
    Unknown = 7

class SubtreeLog(Org):
    def setDescription(self, desc: StmtList) -> None: ...
    def getPriority(self) -> SubtreeLogPriority: ...
    def getNote(self) -> SubtreeLogNote: ...
    def getRefile(self) -> SubtreeLogRefile: ...
    def getClock(self) -> SubtreeLogClock: ...
    def getState(self) -> SubtreeLogState: ...
    def getTag(self) -> SubtreeLogTag: ...
    def getUnknown(self) -> SubtreeLogUnknown: ...
    def getLogKind(self) -> SubtreeLogKind: ...
    log: SubtreeLogLogEntry

class SubtreePeriodKind(Enum):
    Clocked = 1
    Closed = 2
    Scheduled = 3
    Titled = 4
    Deadline = 5
    Created = 6
    Repeated = 7

class SubtreePeriod:
    kind: SubtreePeriodKind
    from_: Time
    to: Optional[Time]

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
    name: str

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
    def isMatching(self, kind: str, subKind: Optional[str]) -> bool: ...
    def getName(self) -> str: ...
    def getSubKind(self) -> Optional[str]: ...
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
    def getProperties(self, kind: str, subkind: Optional[str]) -> List[SubtreeProperty]: ...
    def getProperty(self, kind: str, subkind: Optional[str]) -> Optional[SubtreeProperty]: ...
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
    pass

class Leaf(Org):
    text: str

class Escaped(Leaf):
    text: str

class Newline(Leaf):
    text: str

class Space(Leaf):
    text: str

class Word(Leaf):
    text: str

class AtMention(Leaf):
    text: str

class RawText(Leaf):
    text: str

class Punctuation(Leaf):
    text: str

class Placeholder(Leaf):
    text: str

class BigIdent(Leaf):
    text: str

class Markup(Org):
    pass

class Bold(Markup):
    pass

class Underline(Markup):
    pass

class Monospace(Markup):
    pass

class MarkQuote(Markup):
    pass

class Verbatim(Markup):
    pass

class Italic(Markup):
    pass

class Strike(Markup):
    pass

class Par(Markup):
    pass

class List(Org):
    def isDescriptionList(self) -> bool: ...

class ListItemCheckbox(Enum):
    _None = 1
    Done = 2
    Empty = 3
    Partial = 4

class ListItem(Org):
    def isDescriptionItem(self) -> bool: ...
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
    def getProperties(self, kind: str, subKind: Optional[str]) -> List[SubtreeProperty]: ...
    def getProperty(self, kind: str, subKind: Optional[str]) -> Optional[SubtreeProperty]: ...
    def getDoExport(self) -> DocumentOptionsDoExport: ...
    def getExportFixed(self) -> DocumentOptionsExportFixed: ...
    def getTocExportKind(self) -> DocumentOptionsTocExportKind: ...
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
    def getProperties(self, kind: str, subKind: Optional[str]) -> List[SubtreeProperty]: ...
    def getProperty(self, kind: str, subKind: Optional[str]) -> Optional[SubtreeProperty]: ...
    title: Optional[Paragraph]
    author: Optional[Paragraph]
    creator: Optional[Paragraph]
    filetags: List[HashTag]
    email: Optional[RawText]
    language: List[str]
    options: DocumentOptions
    exportFileName: Optional[str]

class ParseError(Org):
    pass

class FileTarget(Org):
    path: str
    line: Optional[int]
    searchTarget: Optional[str]
    restrictToHeadlines: bool
    targetId: Optional[str]
    regexp: Optional[str]

class TextSeparator(Org):
    pass

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
    data: IncludeData

class DocumentGroup(Org):
    pass

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
    CommentBlock = 56
    AdmonitionBlock = 57
    CenterBlock = 58
    VerseBlock = 59
    Example = 60
    SrcCode = 61
    SrcInlineCode = 62
    InlineCallCode = 63
    CmdCallCode = 64
    PassCode = 65
    CmdArguments = 66
    CmdFlag = 67
    CmdKey = 68
    CmdValue = 69
    CmdNamedValue = 70
    UrgencyStatus = 71
    TextSeparator = 72
    Paragraph = 73
    AnnotatedParagraph = 74
    Bold = 75
    Italic = 76
    Verbatim = 77
    Backtick = 78
    Underline = 79
    Strike = 80
    Quote = 81
    Angle = 82
    Monospace = 83
    Par = 84
    InlineMath = 85
    DisplayMath = 86
    Space = 87
    Punctuation = 88
    Colon = 89
    Word = 90
    Escaped = 91
    Newline = 92
    RawLink = 93
    Link = 94
    Macro = 95
    BackendRaw = 96
    Symbol = 97
    TimeAssoc = 98
    StaticActiveTime = 99
    StaticInactiveTime = 100
    DynamicActiveTime = 101
    DynamicInactiveTime = 102
    TimeRange = 103
    SimpleTime = 104
    Details = 105
    Summary = 106
    Table = 107
    TableRow = 108
    TableCell = 109
    InlineFootnote = 110
    Footnote = 111
    Horizontal = 112
    Filetags = 113
    OrgTag = 114
    HashTag = 115
    MetaSymbol = 116
    AtMention = 117
    BracTag = 118
    Drawer = 119
    LatexClass = 120
    LatexHeader = 121
    LatexCompiler = 122
    LatexClassOptions = 123
    HtmlHead = 124
    Columns = 125
    CmdPropertyArgs = 126
    CmdPropertyText = 127
    CmdPropertyRaw = 128
    PropertyList = 129
    Property = 130
    Placeholder = 131
    SubtreeDescription = 132
    SubtreeUrgency = 133
    Logbook = 134
    LogbookStateChange = 135
    RadioTarget = 136
    Target = 137

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
    AnnotatedParagraph = 10
    Center = 11
    Caption = 12
    CmdName = 13
    CmdResults = 14
    CommandGroup = 15
    Tblfm = 16
    Quote = 17
    CommentBlock = 18
    Verse = 19
    Example = 20
    CmdArguments = 21
    CmdAttr = 22
    CmdArgument = 23
    Export = 24
    AdmonitionBlock = 25
    Call = 26
    Code = 27
    Time = 28
    TimeRange = 29
    Macro = 30
    Symbol = 31
    SubtreeLog = 32
    Subtree = 33
    InlineMath = 34
    Escaped = 35
    Newline = 36
    Space = 37
    Word = 38
    AtMention = 39
    RawText = 40
    Punctuation = 41
    Placeholder = 42
    BigIdent = 43
    Bold = 44
    Underline = 45
    Monospace = 46
    MarkQuote = 47
    Verbatim = 48
    Italic = 49
    Strike = 50
    Par = 51
    List = 52
    ListItem = 53
    Link = 54
    DocumentOptions = 55
    Document = 56
    ParseError = 57
    FileTarget = 58
    TextSeparator = 59
    Include = 60
    DocumentGroup = 61

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

class SubnodeVisitorCtxPart:
    node: Optional[Org]
    index: Optional[int]
    field: Optional[str]
    kind: Kind

class OrgDocumentContext:
    def getSubtreeById(self, id: str) -> List[Subtree]: ...
    def getLinkTarget(self, link: Link) -> List[Org]: ...
    def getRadioTarget(self, name: str) -> List[Org]: ...
    def addNodes(self, node: Org) -> None: ...

class OrgParseParameters:
    baseTokenTracePath: Optional[str]
    tokenTracePath: Optional[str]
    parseTracePath: Optional[str]
    semTracePath: Optional[str]

class OrgTreeExportOpts:
    withLineCol: bool
    withOriginalId: bool
    withSubnodeIdx: bool
    skipEmptyFields: bool
    startLevel: int
    withColor: bool

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

class SubnodeVisitorCtxPartKind(Enum):
    Field = 1
    Index = 2
    Key = 3

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

def parseFile(file: str, opts: OrgParseParameters) -> Document: ...

def parseString(text: str) -> Document: ...

def parseStringOpts(text: str, opts: OrgParseParameters) -> Document: ...

def formatToString(arg: Org) -> str: ...

def exportToYamlString(node: Org) -> str: ...

def exportToYamlFile(node: Org, path: str) -> None: ...

def exportToJsonString(node: Org) -> str: ...

def exportToJsonFile(node: Org, path: str) -> None: ...

def readProtobufFile(file: str) -> Document: ...

def exportToProtobufFile(doc: Document, file: str) -> None: ...

def exportToTreeString(node: Org, opts: OrgTreeExportOpts) -> str: ...

def exportToTreeFile(node: Org, path: str, opts: OrgTreeExportOpts) -> None: ...

def eachSubnodeRec(node: Org, callback: function) -> None: ...

/* clang-format on */