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

class IncludeKind(Enum):
    Example = 1
    Export = 2
    Src = 3
    OrgDocument = 4

class OrgSpecName(Enum):
    Unnamed_ = 1
    Result_ = 2
    Year_ = 3
    Day_ = 4
    Clock_ = 5
    Repeater_ = 6
    Zone_ = 7
    Link_ = 8
    Tags_ = 9
    Tag_ = 10
    State_ = 11
    Protocol_ = 12
    Desc_ = 13
    Times_ = 14
    Drawer_ = 15
    Args_ = 16
    Name_ = 17
    Definition_ = 18
    Body_ = 19
    HeaderArgs_ = 20
    File_ = 21
    Kind_ = 22
    Lang_ = 23
    Prefix_ = 24
    Text_ = 25
    Todo_ = 26
    Urgency_ = 27
    Title_ = 28
    Completion_ = 29
    Head_ = 30
    Subnodes_ = 31
    Properties_ = 32
    Logbook_ = 33
    Description_ = 34
    Logs_ = 35
    Newstate_ = 36
    Oldstate_ = 37
    Time_ = 38
    From_ = 39
    EndArgs_ = 40
    Flags_ = 41
    Value_ = 42
    Assoc_ = 43
    Main_ = 44
    Hash_ = 45
    Bullet_ = 46
    Counter_ = 47
    Checkbox_ = 48
    Header_ = 49
    To_ = 50
    Diff_ = 51
    Property_ = 52
    Subname_ = 53
    Values_ = 54
    Cells_ = 55
    Rows_ = 56
    Lines_ = 57
    Chunks_ = 58
    InheritanceMode_ = 59
    MainSetRule_ = 60
    SubSetRule_ = 61

class OrgNodeKind(Enum):
    None_ = 1
    Document_ = 2
    UserNode_ = 3
    Empty_ = 4
    Error_ = 5
    ErrorTerminator_ = 6
    ErrorToken_ = 7
    InlineStmtList_ = 8
    StmtList_ = 9
    AssocStmtList_ = 10
    Subtree_ = 11
    SubtreeTimes_ = 12
    SubtreeStars_ = 13
    Completion_ = 14
    Checkbox_ = 15
    List_ = 16
    Bullet_ = 17
    ListItem_ = 18
    ListTag_ = 19
    Counter_ = 20
    Comment_ = 21
    RawText_ = 22
    Unparsed_ = 23
    Command_ = 24
    CommandArguments_ = 25
    CommandTitle_ = 26
    CommandAuthor_ = 27
    CommandCreator_ = 28
    CommandInclude_ = 29
    CommandLanguage_ = 30
    CommandAttrHtml_ = 31
    CommandName_ = 32
    CommandHeader_ = 33
    CommandOptions_ = 34
    CommandTblfm_ = 35
    CommandBackendOptions_ = 36
    AttrImg_ = 37
    CommandCaption_ = 38
    File_ = 39
    BlockExport_ = 40
    InlineExport_ = 41
    MultilineCommand_ = 42
    Result_ = 43
    Ident_ = 44
    BareIdent_ = 45
    AdmonitionTag_ = 46
    BigIdent_ = 47
    VerbatimMultilineBlock_ = 48
    CodeLine_ = 49
    CodeText_ = 50
    CodeTangle_ = 51
    CodeCallout_ = 52
    QuoteBlock_ = 53
    AdmonitionBlock_ = 54
    CenterBlock_ = 55
    VerseBlock_ = 56
    Example_ = 57
    SrcCode_ = 58
    SrcInlineCode_ = 59
    CallCode_ = 60
    PassCode_ = 61
    CmdArguments_ = 62
    CmdFlag_ = 63
    CmdKey_ = 64
    CmdValue_ = 65
    CmdNamedValue_ = 66
    UrgencyStatus_ = 67
    TextSeparator_ = 68
    Paragraph_ = 69
    AnnotatedParagraph_ = 70
    Bold_ = 71
    Italic_ = 72
    Verbatim_ = 73
    Backtick_ = 74
    Underline_ = 75
    Strike_ = 76
    Quote_ = 77
    Angle_ = 78
    Monospace_ = 79
    Par_ = 80
    InlineMath_ = 81
    DisplayMath_ = 82
    Space_ = 83
    Punctuation_ = 84
    Colon_ = 85
    Word_ = 86
    Escaped_ = 87
    Newline_ = 88
    RawLink_ = 89
    Link_ = 90
    Macro_ = 91
    BackendRaw_ = 92
    Symbol_ = 93
    TimeAssoc_ = 94
    StaticActiveTime_ = 95
    StaticInactiveTime_ = 96
    DynamicActiveTime_ = 97
    DynamicInactiveTime_ = 98
    TimeRange_ = 99
    SimpleTime_ = 100
    Details_ = 101
    Summary_ = 102
    Table_ = 103
    TableRow_ = 104
    TableCell_ = 105
    InlineFootnote_ = 106
    Footnote_ = 107
    Horizontal_ = 108
    Filetags_ = 109
    OrgTag_ = 110
    HashTag_ = 111
    MetaSymbol_ = 112
    AtMention_ = 113
    BracTag_ = 114
    Drawer_ = 115
    LatexClass_ = 116
    LatexHeader_ = 117
    LatexCompiler_ = 118
    LatexClassOptions_ = 119
    HtmlHead_ = 120
    Columns_ = 121
    CmdPropertyArgs_ = 122
    CmdPropertyText_ = 123
    CmdPropertyRaw_ = 124
    PropertyList_ = 125
    Property_ = 126
    Placeholder_ = 127
    SubtreeDescription_ = 128
    SubtreeUrgency_ = 129
    Logbook_ = 130
    LogbookStateChange_ = 131
    RadioTarget_ = 132
    Target_ = 133

class OrgBigIdentKind(Enum):
    None_ = 1
    Must_ = 2
    MustNot_ = 3
    Should_ = 4
    ShouldNot_ = 5
    Required_ = 6
    Optional_ = 7
    ReallyShouldNot_ = 8
    OughtTo_ = 9
    WouldProbably_ = 10
    MayWishTo_ = 11
    Could_ = 12
    Might_ = 13
    Possible_ = 14
    Todo_ = 15
    Idea_ = 16
    Error_ = 17
    Fixme_ = 18
    Doc_ = 19
    Refactor_ = 20
    Review_ = 21
    Hack_ = 22
    Implement_ = 23
    Example_ = 24
    Question_ = 25
    Assume_ = 26
    Internal_ = 27
    Design_ = 28
    Why_ = 29
    Wip_ = 30
    Fix_ = 31
    Clean_ = 32
    Feature_ = 33
    Style_ = 34
    Repo_ = 35
    Skip_ = 36
    Break_ = 37
    Poc_ = 38
    Next_ = 39
    Later_ = 40
    Postponed_ = 41
    Stalled_ = 42
    Done_ = 43
    Partially_ = 44
    Cancelled_ = 45
    Failed_ = 46
    Note_ = 47
    Tip_ = 48
    Important_ = 49
    Caution_ = 50
    Warning_ = 51
    UserCodeComment_ = 52
    UserCommitMsg_ = 53
    UserTaskState_ = 54
    UserAdmonition_ = 55
    Other_ = 56
    StructIf_ = 57
    StructAnd_ = 58
    StructOr_ = 59
    StructNot_ = 60
    StructGet_ = 61
    StructSet_ = 62
    StructThen_ = 63
    StructElse_ = 64
    StructWhile_ = 65

class OrgSemKind(Enum):
    StmtList_ = 1
    Empty_ = 2
    Row_ = 3
    Table_ = 4
    HashTag_ = 5
    Footnote_ = 6
    Completion_ = 7
    Paragraph_ = 8
    Center_ = 9
    Caption_ = 10
    CommandGroup_ = 11
    Tblfm_ = 12
    Quote_ = 13
    Verse_ = 14
    Example_ = 15
    CmdArguments_ = 16
    CmdArgument_ = 17
    Export_ = 18
    AdmonitionBlock_ = 19
    Code_ = 20
    Time_ = 21
    TimeRange_ = 22
    Macro_ = 23
    Symbol_ = 24
    SubtreeLog_ = 25
    Subtree_ = 26
    InlineMath_ = 27
    Escaped_ = 28
    Newline_ = 29
    Space_ = 30
    Word_ = 31
    AtMention_ = 32
    RawText_ = 33
    Punctuation_ = 34
    Placeholder_ = 35
    BigIdent_ = 36
    Bold_ = 37
    Underline_ = 38
    Monospace_ = 39
    MarkQuote_ = 40
    Verbatim_ = 41
    Italic_ = 42
    Strike_ = 43
    Par_ = 44
    List_ = 45
    ListItem_ = 46
    Link_ = 47
    DocumentOptions_ = 48
    Document_ = 49
    ParseError_ = 50
    FileTarget_ = 51
    TextSeparator_ = 52
    Include_ = 53
    DocumentGroup_ = 54

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
    def is_(kind: OrgSemKind) -> bool: ...
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
    def enableFileTrace(path: str, colored: bool) -> None: ...
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