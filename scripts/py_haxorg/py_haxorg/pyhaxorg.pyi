/* clang-format off */
from typing import *
from enum import Enum
from datetime import datetime, date, time
class Org:
    def __init__(self, loc: Optional[LineCol], documentId: Optional[int], subnodes: List[Org]) -> None: ...
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
    def __init__(self, line: int, column: int, pos: int) -> None: ...
    line: int
    column: int
    pos: int

class Stmt(Org):
    def __init__(self, attached: List[Org]) -> None: ...
    def getAttached(self, kind: OrgSemKind) -> Optional[Org]: ...
    attached: List[Org]

class Inline(Org):
    def __init__(self) -> None: ...

class StmtList(Org):
    def __init__(self) -> None: ...

class Empty(Org):
    def __init__(self) -> None: ...

class Cell(Org):
    def __init__(self) -> None: ...

class Row(Org):
    def __init__(self, cells: List[Cell]) -> None: ...
    cells: List[Cell]

class Table(Stmt):
    def __init__(self, rows: List[Row], attached: List[Org]) -> None: ...
    def getAttached(self, kind: OrgSemKind) -> Optional[Org]: ...
    rows: List[Row]
    attached: List[Org]

class HashTag(Inline):
    def __init__(self, head: str, subtags: List[HashTag]) -> None: ...
    def prefixMatch(self, prefix: List[str]) -> bool: ...
    head: str
    subtags: List[HashTag]

class Footnote(Inline):
    def __init__(self, tag: str, definition: Optional[Org]) -> None: ...
    tag: str
    definition: Optional[Org]

class Completion(Inline):
    def __init__(self, done: int, full: int, isPercent: bool) -> None: ...
    done: int
    full: int
    isPercent: bool

class Paragraph(Stmt):
    def __init__(self, attached: List[Org]) -> None: ...
    def getAttached(self, kind: OrgSemKind) -> Optional[Org]: ...
    attached: List[Org]

class AnnotatedParagraphNone:
    def __init__(self) -> None: ...

class AnnotatedParagraphFootnote:
    def __init__(self, name: str) -> None: ...
    name: str

class AnnotatedParagraphAdmonition:
    def __init__(self, name: BigIdent) -> None: ...
    name: BigIdent

class AnnotatedParagraphTimestamp:
    def __init__(self, time: Time) -> None: ...
    time: Time

AnnotatedParagraphData = Union[AnnotatedParagraphNone, AnnotatedParagraphFootnote, AnnotatedParagraphAdmonition, AnnotatedParagraphTimestamp]
class AnnotatedParagraphAnnotationKind(Enum):
    _None = 1
    Footnote = 2
    Admonition = 3
    Timestamp = 4

class AnnotatedParagraph(Stmt):
    def __init__(self, data: AnnotatedParagraphData, attached: List[Org]) -> None: ...
    def getNone(self) -> AnnotatedParagraphNone: ...
    def getFootnote(self) -> AnnotatedParagraphFootnote: ...
    def getAdmonition(self) -> AnnotatedParagraphAdmonition: ...
    def getTimestamp(self) -> AnnotatedParagraphTimestamp: ...
    @staticmethod
    def getAnnotationKindStatic(self, __input: AnnotatedParagraphData) -> AnnotatedParagraphAnnotationKind: ...
    def getAnnotationKind(self) -> AnnotatedParagraphAnnotationKind: ...
    def getAttached(self, kind: OrgSemKind) -> Optional[Org]: ...
    data: AnnotatedParagraphData
    attached: List[Org]

class Format(Org):
    def __init__(self) -> None: ...

class Center(Format):
    def __init__(self) -> None: ...

class Command(Org):
    def __init__(self) -> None: ...

class LineCommand(Command):
    def __init__(self) -> None: ...

class Standalone(LineCommand):
    def __init__(self) -> None: ...

class Attached(LineCommand):
    def __init__(self) -> None: ...

class Caption(Attached):
    def __init__(self, text: Paragraph) -> None: ...
    text: Paragraph

class CmdName(Attached):
    def __init__(self) -> None: ...

class CmdResults(Attached):
    def __init__(self) -> None: ...

class CommandGroup(Stmt):
    def __init__(self, attached: List[Org]) -> None: ...
    def getAttached(self, kind: OrgSemKind) -> Optional[Org]: ...
    attached: List[Org]

class Block(Command):
    def __init__(self, parameters: Optional[CmdArguments]) -> None: ...
    def getParameter(self, key: str) -> Optional[CmdArgument]: ...
    parameters: Optional[CmdArguments]

class Tblfm(Command):
    def __init__(self) -> None: ...

class Quote(Org):
    def __init__(self) -> None: ...

class CommentBlock(Org):
    def __init__(self) -> None: ...

class Verse(Block):
    def __init__(self, parameters: Optional[CmdArguments]) -> None: ...
    def getParameter(self, key: str) -> Optional[CmdArgument]: ...
    parameters: Optional[CmdArguments]

class Example(Block):
    def __init__(self, parameters: Optional[CmdArguments]) -> None: ...
    def getParameter(self, key: str) -> Optional[CmdArgument]: ...
    parameters: Optional[CmdArguments]

class ColonExample(Org):
    def __init__(self) -> None: ...

class CmdArguments(Org):
    def __init__(self, positional: List[CmdArgument], named: Dict[str, CmdArgument]) -> None: ...
    def getParameter(self, key: str) -> Optional[CmdArgument]: ...
    positional: List[CmdArgument]
    named: Dict[str, CmdArgument]

class CmdAttr(Attached):
    def __init__(self, target: str, parameters: CmdArguments) -> None: ...
    target: str
    parameters: CmdArguments

class CmdArgument(Org):
    def __init__(self, key: Optional[str], value: str) -> None: ...
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
    def __init__(self, format: ExportFormat, exporter: str, placement: Optional[str], content: str, parameters: Optional[CmdArguments]) -> None: ...
    def getParameter(self, key: str) -> Optional[CmdArgument]: ...
    format: ExportFormat
    exporter: str
    placement: Optional[str]
    content: str
    parameters: Optional[CmdArguments]

class AdmonitionBlock(Block):
    def __init__(self, parameters: Optional[CmdArguments]) -> None: ...
    def getParameter(self, key: str) -> Optional[CmdArgument]: ...
    parameters: Optional[CmdArguments]

class Call(Org):
    def __init__(self, name: Optional[str]) -> None: ...
    name: Optional[str]

class CodeLinePartRaw:
    def __init__(self, code: str) -> None: ...
    code: str

class CodeLinePartCallout:
    def __init__(self, name: str) -> None: ...
    name: str

class CodeLinePartTangle:
    def __init__(self, target: str) -> None: ...
    target: str

CodeLinePartData = Union[CodeLinePartRaw, CodeLinePartCallout, CodeLinePartTangle]
class CodeLinePartKind(Enum):
    Raw = 1
    Callout = 2
    Tangle = 3

class CodeLinePart:
    def __init__(self, data: CodeLinePartData) -> None: ...
    def getRaw(self) -> CodeLinePartRaw: ...
    def getCallout(self) -> CodeLinePartCallout: ...
    def getTangle(self) -> CodeLinePartTangle: ...
    @staticmethod
    def getKindStatic(self, __input: CodeLinePartData) -> CodeLinePartKind: ...
    def getKind(self) -> CodeLinePartKind: ...
    data: CodeLinePartData

class CodeLine:
    def __init__(self, parts: List[CodeLinePart]) -> None: ...
    parts: List[CodeLinePart]

class CodeSwitchLineStart:
    def __init__(self, start: int, extendLast: bool) -> None: ...
    start: int
    extendLast: bool

class CodeSwitchCalloutFormat:
    def __init__(self, format: str) -> None: ...
    format: str

class CodeSwitchRemoveCallout:
    def __init__(self, remove: bool) -> None: ...
    remove: bool

class CodeSwitchEmphasizeLine:
    def __init__(self, line: List[int]) -> None: ...
    line: List[int]

class CodeSwitchDedent:
    def __init__(self, value: int) -> None: ...
    value: int

CodeSwitchData = Union[CodeSwitchLineStart, CodeSwitchCalloutFormat, CodeSwitchRemoveCallout, CodeSwitchEmphasizeLine, CodeSwitchDedent]
class CodeSwitchKind(Enum):
    LineStart = 1
    CalloutFormat = 2
    RemoveCallout = 3
    EmphasizeLine = 4
    Dedent = 5

class CodeSwitch:
    def __init__(self, data: CodeSwitchData) -> None: ...
    def getLineStart(self) -> CodeSwitchLineStart: ...
    def getCalloutFormat(self) -> CodeSwitchCalloutFormat: ...
    def getRemoveCallout(self) -> CodeSwitchRemoveCallout: ...
    def getEmphasizeLine(self) -> CodeSwitchEmphasizeLine: ...
    def getDedent(self) -> CodeSwitchDedent: ...
    @staticmethod
    def getKindStatic(self, __input: CodeSwitchData) -> CodeSwitchKind: ...
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
    def __init__(self, lang: Optional[str], switches: List[CodeSwitch], exports: CodeExports, lines: List[CodeLine], cache: bool, eval: bool, noweb: bool, hlines: bool, tangle: bool, parameters: Optional[CmdArguments]) -> None: ...
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
    def __init__(self, mode: TimeRepeatMode, period: TimeRepeatPeriod, count: int) -> None: ...
    mode: TimeRepeatMode
    period: TimeRepeatPeriod
    count: int

class TimeStatic:
    def __init__(self, repeat: Optional[TimeRepeat], time: UserTime) -> None: ...
    repeat: Optional[TimeRepeat]
    time: UserTime

class TimeDynamic:
    def __init__(self, expr: str) -> None: ...
    expr: str

TimeTimeVariant = Union[TimeStatic, TimeDynamic]
class TimeTimeKind(Enum):
    Static = 1
    Dynamic = 2

class Time(Org):
    def __init__(self, isActive: bool, time: TimeTimeVariant) -> None: ...
    def getStatic(self) -> TimeStatic: ...
    def getDynamic(self) -> TimeDynamic: ...
    @staticmethod
    def getTimeKindStatic(self, __input: TimeTimeVariant) -> TimeTimeKind: ...
    def getTimeKind(self) -> TimeTimeKind: ...
    isActive: bool
    time: TimeTimeVariant

class TimeRange(Org):
    def __init__(self, from_: Time, to: Time) -> None: ...
    from_: Time
    to: Time

class Macro(Org):
    def __init__(self, name: str, arguments: List[str]) -> None: ...
    name: str
    arguments: List[str]

class SymbolParam:
    def __init__(self, key: Optional[str], value: str) -> None: ...
    key: Optional[str]
    value: str

class Symbol(Org):
    def __init__(self, name: str, parameters: List[SymbolParam], positional: List[Org]) -> None: ...
    name: str
    parameters: List[SymbolParam]
    positional: List[Org]

class SubtreeLogDescribedLog:
    def __init__(self, desc: Optional[StmtList]) -> None: ...
    desc: Optional[StmtList]

class SubtreeLogPriorityAction(Enum):
    Added = 1
    Removed = 2
    Changed = 3

class SubtreeLogPriority(SubtreeLogDescribedLog):
    def __init__(self, oldPriority: Optional[str], newPriority: Optional[str], on: Time, action: SubtreeLogPriorityAction) -> None: ...
    oldPriority: Optional[str]
    newPriority: Optional[str]
    on: Time
    action: SubtreeLogPriorityAction

class SubtreeLogNote(SubtreeLogDescribedLog):
    def __init__(self, on: Time) -> None: ...
    on: Time

class SubtreeLogRefile(SubtreeLogDescribedLog):
    def __init__(self, on: Time, from_: Link) -> None: ...
    on: Time
    from_: Link

class SubtreeLogClock(SubtreeLogDescribedLog):
    def __init__(self, from_: Time, to: Optional[Time]) -> None: ...
    from_: Time
    to: Optional[Time]

class SubtreeLogState(SubtreeLogDescribedLog):
    def __init__(self, from_: str, to: str, on: Time) -> None: ...
    from_: str
    to: str
    on: Time

class SubtreeLogTag(SubtreeLogDescribedLog):
    def __init__(self, on: Time, tag: HashTag, added: bool) -> None: ...
    on: Time
    tag: HashTag
    added: bool

class SubtreeLogUnknown(SubtreeLogDescribedLog):
    def __init__(self) -> None: ...

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
    def __init__(self, log: SubtreeLogLogEntry) -> None: ...
    def setDescription(self, desc: StmtList) -> None: ...
    def getPriority(self) -> SubtreeLogPriority: ...
    def getNote(self) -> SubtreeLogNote: ...
    def getRefile(self) -> SubtreeLogRefile: ...
    def getClock(self) -> SubtreeLogClock: ...
    def getState(self) -> SubtreeLogState: ...
    def getTag(self) -> SubtreeLogTag: ...
    def getUnknown(self) -> SubtreeLogUnknown: ...
    @staticmethod
    def getLogKindStatic(self, __input: SubtreeLogLogEntry) -> SubtreeLogKind: ...
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
    def __init__(self, kind: SubtreePeriodKind, from_: Time, to: Optional[Time]) -> None: ...
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
    def __init__(self, isBlocking: bool) -> None: ...
    isBlocking: bool

class SubtreePropertyTrigger:
    def __init__(self) -> None: ...

class SubtreePropertyOrigin:
    def __init__(self, text: Paragraph) -> None: ...
    text: Paragraph

class SubtreePropertyExportLatexClass:
    def __init__(self, latexClass: str) -> None: ...
    latexClass: str

class SubtreePropertyExportLatexClassOptions:
    def __init__(self, options: List[str]) -> None: ...
    options: List[str]

class SubtreePropertyExportLatexHeader:
    def __init__(self, header: str) -> None: ...
    header: str

class SubtreePropertyExportLatexCompiler:
    def __init__(self, compiler: str) -> None: ...
    compiler: str

class SubtreePropertyOrdered:
    def __init__(self, isOrdered: bool) -> None: ...
    isOrdered: bool

class SubtreePropertyEffort:
    def __init__(self, hours: int, minutes: int) -> None: ...
    hours: int
    minutes: int

class SubtreePropertyVisibilityLevel(Enum):
    Folded = 1
    Children = 2
    Content = 3
    All = 4

class SubtreePropertyVisibility:
    def __init__(self, level: SubtreePropertyVisibilityLevel) -> None: ...
    level: SubtreePropertyVisibilityLevel

class SubtreePropertyExportOptions:
    def __init__(self, backend: str, values: Dict[str, str]) -> None: ...
    backend: str
    values: Dict[str, str]

class SubtreePropertyBlocker:
    def __init__(self, blockers: List[str]) -> None: ...
    blockers: List[str]

class SubtreePropertyUnnumbered:
    def __init__(self) -> None: ...

class SubtreePropertyCreated:
    def __init__(self, time: Time) -> None: ...
    time: Time

class SubtreePropertyUnknown:
    def __init__(self, value: Org, name: str) -> None: ...
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
    def __init__(self, mainSetRule: SubtreePropertySetMode, subSetRule: SubtreePropertySetMode, inheritanceMode: SubtreePropertyInheritanceMode, data: SubtreePropertyData) -> None: ...
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
    @staticmethod
    def getKindStatic(self, __input: SubtreePropertyData) -> SubtreePropertyKind: ...
    def getKind(self) -> SubtreePropertyKind: ...
    mainSetRule: SubtreePropertySetMode
    subSetRule: SubtreePropertySetMode
    inheritanceMode: SubtreePropertyInheritanceMode
    data: SubtreePropertyData

class Subtree(Org):
    def __init__(self, level: int, treeId: Optional[str], todo: Optional[str], completion: Optional[Completion], description: Optional[Paragraph], tags: List[HashTag], title: Paragraph, logbook: List[SubtreeLog], properties: List[SubtreeProperty], closed: Optional[Time], deadline: Optional[Time], scheduled: Optional[Time]) -> None: ...
    def getTimePeriods(self, kinds: IntSet[SubtreePeriodKind]) -> List[SubtreePeriod]: ...
    def getProperties(self, kind: str, subkind: Optional[str]) -> List[SubtreeProperty]: ...
    def getProperty(self, kind: str, subkind: Optional[str]) -> Optional[SubtreeProperty]: ...
    def removeProperty(self, kind: str, subkind: Optional[str]) -> None: ...
    def setProperty(self, value: SubtreeProperty) -> None: ...
    def setPropertyStrValue(self, value: str, kind: str, subkind: Optional[str]) -> None: ...
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
    def __init__(self) -> None: ...

class InlineMath(LatexBody):
    def __init__(self) -> None: ...

class Leaf(Org):
    def __init__(self, text: str) -> None: ...
    text: str

class Escaped(Leaf):
    def __init__(self, text: str) -> None: ...
    text: str

class Newline(Leaf):
    def __init__(self, text: str) -> None: ...
    text: str

class Space(Leaf):
    def __init__(self, text: str) -> None: ...
    text: str

class Word(Leaf):
    def __init__(self, text: str) -> None: ...
    text: str

class AtMention(Leaf):
    def __init__(self, text: str) -> None: ...
    text: str

class RawText(Leaf):
    def __init__(self, text: str) -> None: ...
    text: str

class Punctuation(Leaf):
    def __init__(self, text: str) -> None: ...
    text: str

class Placeholder(Leaf):
    def __init__(self, text: str) -> None: ...
    text: str

class BigIdent(Leaf):
    def __init__(self, text: str) -> None: ...
    text: str

class Markup(Org):
    def __init__(self) -> None: ...

class Bold(Markup):
    def __init__(self) -> None: ...

class Underline(Markup):
    def __init__(self) -> None: ...

class Monospace(Markup):
    def __init__(self) -> None: ...

class MarkQuote(Markup):
    def __init__(self) -> None: ...

class Verbatim(Markup):
    def __init__(self) -> None: ...

class Italic(Markup):
    def __init__(self) -> None: ...

class Strike(Markup):
    def __init__(self) -> None: ...

class Par(Markup):
    def __init__(self) -> None: ...

class List(Org):
    def __init__(self) -> None: ...
    def isDescriptionList(self) -> bool: ...

class ListItemCheckbox(Enum):
    _None = 1
    Done = 2
    Empty = 3
    Partial = 4

class ListItem(Org):
    def __init__(self, checkbox: ListItemCheckbox, header: Optional[Paragraph]) -> None: ...
    def isDescriptionItem(self) -> bool: ...
    checkbox: ListItemCheckbox
    header: Optional[Paragraph]

class LinkRaw:
    def __init__(self, text: str) -> None: ...
    text: str

class LinkId:
    def __init__(self, text: str) -> None: ...
    text: str

class LinkPerson:
    def __init__(self, name: str) -> None: ...
    name: str

class LinkUserProtocol:
    def __init__(self, protocol: str, target: str) -> None: ...
    protocol: str
    target: str

class LinkInternal:
    def __init__(self, target: str) -> None: ...
    target: str

class LinkFootnote:
    def __init__(self, target: str) -> None: ...
    target: str

class LinkFile:
    def __init__(self, file: str) -> None: ...
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
    def __init__(self, description: Optional[Paragraph], data: LinkData) -> None: ...
    def getRaw(self) -> LinkRaw: ...
    def getId(self) -> LinkId: ...
    def getPerson(self) -> LinkPerson: ...
    def getUserProtocol(self) -> LinkUserProtocol: ...
    def getInternal(self) -> LinkInternal: ...
    def getFootnote(self) -> LinkFootnote: ...
    def getFile(self) -> LinkFile: ...
    @staticmethod
    def getLinkKindStatic(self, __input: LinkData) -> LinkKind: ...
    def getLinkKind(self) -> LinkKind: ...
    description: Optional[Paragraph]
    data: LinkData

class DocumentOptionsDoExport:
    def __init__(self, exportToc: bool) -> None: ...
    exportToc: bool

class DocumentOptionsExportFixed:
    def __init__(self, exportLevels: int) -> None: ...
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
    def __init__(self, brokenLinks: DocumentOptionsBrokenLinks, initialVisibility: DocumentOptionsVisibility, tocExport: DocumentOptionsTocExport, properties: List[SubtreeProperty], smartQuotes: bool, emphasizedText: bool, specialStrings: bool, fixedWidthSections: bool, includeTimestamps: bool, preserveLineBreaks: bool, plaintextSubscripts: bool, exportArchived: bool, exportWithAuthor: bool, exportBrokenLinks: bool, exportWithClock: bool, exportWithCreator: bool, data: DocumentOptionsTocExport) -> None: ...
    def getProperties(self, kind: str, subKind: Optional[str]) -> List[SubtreeProperty]: ...
    def getProperty(self, kind: str, subKind: Optional[str]) -> Optional[SubtreeProperty]: ...
    def getDoExport(self) -> DocumentOptionsDoExport: ...
    def getExportFixed(self) -> DocumentOptionsExportFixed: ...
    @staticmethod
    def getTocExportKindStatic(self, __input: DocumentOptionsTocExport) -> DocumentOptionsTocExportKind: ...
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
    def __init__(self, title: Optional[Paragraph], author: Optional[Paragraph], creator: Optional[Paragraph], filetags: List[HashTag], email: Optional[RawText], language: List[str], options: DocumentOptions, exportFileName: Optional[str]) -> None: ...
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
    def __init__(self) -> None: ...

class FileTarget(Org):
    def __init__(self, path: str, line: Optional[int], searchTarget: Optional[str], restrictToHeadlines: bool, targetId: Optional[str], regexp: Optional[str]) -> None: ...
    path: str
    line: Optional[int]
    searchTarget: Optional[str]
    restrictToHeadlines: bool
    targetId: Optional[str]
    regexp: Optional[str]

class TextSeparator(Org):
    def __init__(self) -> None: ...

class IncludeExample:
    def __init__(self) -> None: ...

class IncludeExport:
    def __init__(self) -> None: ...

class IncludeSrc:
    def __init__(self) -> None: ...

class IncludeOrgDocument:
    def __init__(self) -> None: ...

IncludeData = Union[IncludeExample, IncludeExport, IncludeSrc, IncludeOrgDocument]
class IncludeKind(Enum):
    Example = 1
    Export = 2
    Src = 3
    OrgDocument = 4

class Include(Org):
    def __init__(self, data: IncludeData) -> None: ...
    def getExample(self) -> IncludeExample: ...
    def getExport(self) -> IncludeExport: ...
    def getSrc(self) -> IncludeSrc: ...
    def getOrgDocument(self) -> IncludeOrgDocument: ...
    @staticmethod
    def getIncludeKindStatic(self, __input: IncludeData) -> IncludeKind: ...
    def getIncludeKind(self) -> IncludeKind: ...
    data: IncludeData

class DocumentGroup(Org):
    def __init__(self) -> None: ...

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
    ColonExample = 61
    SrcCode = 62
    SrcInlineCode = 63
    InlineCallCode = 64
    CmdCallCode = 65
    PassCode = 66
    CmdArguments = 67
    CmdFlag = 68
    CmdKey = 69
    CmdValue = 70
    CmdNamedValue = 71
    UrgencyStatus = 72
    TextSeparator = 73
    Paragraph = 74
    AnnotatedParagraph = 75
    Bold = 76
    Italic = 77
    Verbatim = 78
    Backtick = 79
    Underline = 80
    Strike = 81
    Quote = 82
    Angle = 83
    Monospace = 84
    Par = 85
    InlineMath = 86
    DisplayMath = 87
    Space = 88
    Punctuation = 89
    Colon = 90
    Word = 91
    Escaped = 92
    Newline = 93
    RawLink = 94
    Link = 95
    Macro = 96
    BackendRaw = 97
    Symbol = 98
    TimeAssoc = 99
    StaticActiveTime = 100
    StaticInactiveTime = 101
    DynamicActiveTime = 102
    DynamicInactiveTime = 103
    TimeRange = 104
    SimpleTime = 105
    Details = 106
    Summary = 107
    Table = 108
    TableRow = 109
    TableCell = 110
    InlineFootnote = 111
    Footnote = 112
    Horizontal = 113
    Filetags = 114
    OrgTag = 115
    HashTag = 116
    MetaSymbol = 117
    AtMention = 118
    BracTag = 119
    Drawer = 120
    LatexClass = 121
    LatexHeader = 122
    LatexCompiler = 123
    LatexClassOptions = 124
    HtmlHead = 125
    Columns = 126
    CmdPropertyArgs = 127
    CmdPropertyText = 128
    CmdPropertyRaw = 129
    PropertyList = 130
    Property = 131
    Placeholder = 132
    SubtreeDescription = 133
    SubtreeUrgency = 134
    Logbook = 135
    LogbookStateChange = 136
    RadioTarget = 137
    Target = 138

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
    ColonExample = 21
    CmdArguments = 22
    CmdAttr = 23
    CmdArgument = 24
    Export = 25
    AdmonitionBlock = 26
    Call = 27
    Code = 28
    Time = 29
    TimeRange = 30
    Macro = 31
    Symbol = 32
    SubtreeLog = 33
    Subtree = 34
    InlineMath = 35
    Escaped = 36
    Newline = 37
    Space = 38
    Word = 39
    AtMention = 40
    RawText = 41
    Punctuation = 42
    Placeholder = 43
    BigIdent = 44
    Bold = 45
    Underline = 46
    Monospace = 47
    MarkQuote = 48
    Verbatim = 49
    Italic = 50
    Strike = 51
    Par = 52
    List = 53
    ListItem = 54
    Link = 55
    DocumentOptions = 56
    Document = 57
    ParseError = 58
    FileTarget = 59
    TextSeparator = 60
    Include = 61
    DocumentGroup = 62

class UserTimeBreakdown:
    def __init__(self, year: Optional[int], month: Optional[int], day: Optional[int], hour: Optional[int], minute: Optional[int], second: Optional[int], zone: Optional[str]) -> None: ...
    year: Optional[int]
    month: Optional[int]
    day: Optional[int]
    hour: Optional[int]
    minute: Optional[int]
    second: Optional[int]
    zone: Optional[str]

class UserTime:
    def __init__(self) -> None: ...
    def getBreakdown(self) -> UserTimeBreakdown: ...
    def format(self) -> str: ...

class OrgParseParameters:
    def __init__(self, baseTokenTracePath: Optional[str], tokenTracePath: Optional[str], parseTracePath: Optional[str], semTracePath: Optional[str]) -> None: ...
    baseTokenTracePath: Optional[str]
    tokenTracePath: Optional[str]
    parseTracePath: Optional[str]
    semTracePath: Optional[str]

class OrgYamlExportOpts:
    def __init__(self, skipNullFields: bool, skipFalseFields: bool, skipZeroFields: bool, skipLocation: bool, skipId: bool) -> None: ...
    skipNullFields: bool
    skipFalseFields: bool
    skipZeroFields: bool
    skipLocation: bool
    skipId: bool

class OrgTreeExportOpts:
    def __init__(self, withLineCol: bool, withOriginalId: bool, withSubnodeIdx: bool, skipEmptyFields: bool, startLevel: int, withColor: bool) -> None: ...
    withLineCol: bool
    withOriginalId: bool
    withSubnodeIdx: bool
    skipEmptyFields: bool
    startLevel: int
    withColor: bool

class SubnodeVisitorCtxPart:
    def __init__(self, node: Optional[Org], index: Optional[int], field: Optional[str], kind: Kind) -> None: ...
    node: Optional[Org]
    index: Optional[int]
    field: Optional[str]
    kind: Kind

class SubnodeVisitorOpts:
    def __init__(self) -> None: ...

class SubnodeVisitorResult:
    def __init__(self, visitNextFields: bool, visitNextSubnodes: bool, visitNextBases: bool) -> None: ...
    visitNextFields: bool
    visitNextSubnodes: bool
    visitNextBases: bool

class OrgDocumentContext:
    def __init__(self) -> None: ...
    def getSubtreeById(self, id: str) -> List[Subtree]: ...
    def getLinkTarget(self, link: Link) -> List[Org]: ...
    def getRadioTarget(self, name: str) -> List[Org]: ...
    def addNodes(self, node: Org) -> None: ...

class OrgSelectorLink:
    def __init__(self) -> None: ...

class OrgSelectorResult:
    def __init__(self) -> None: ...

class OrgSelectorCondition:
    def __init__(self, isTarget: bool, debug: Optional[str], link: Optional[OrgSelectorLink]) -> None: ...
    isTarget: bool
    debug: Optional[str]
    link: Optional[OrgSelectorLink]

class OrgDocumentSelector:
    def __init__(self, path: List[OrgSelectorCondition], debug: bool) -> None: ...
    def getMatches(self, node: Org) -> List[Org]: ...
    def linkDirectSubnode(self) -> OrgSelectorLink: ...
    def linkIndirectSubnode(self) -> OrgSelectorLink: ...
    def linkField(self, name: str) -> OrgSelectorLink: ...
    def searchSubtreePlaintextTitle(self, title: str, isTarget: bool, link: Optional[OrgSelectorLink]) -> None: ...
    def searchSubtreeId(self, id: str, isTarget: bool, maxLevel: Optional[int], link: Optional[OrgSelectorLink]) -> None: ...
    def searchAnyKind(self, kinds: IntSet[OrgSemKind], isTarget: bool, link: Optional[OrgSelectorLink]) -> None: ...
    def searchPredicate(self, predicate: OrgSelectorConditionPredicate, isTarget: bool, link: Optional[OrgSelectorLink]) -> None: ...
    path: List[OrgSelectorCondition]
    debug: bool

class ExporterPython:
    def __init__(self) -> None: ...
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

class OrgSelectorLinkKind(Enum):
    DirectSubnode = 1
    IndirectSubnode = 2
    FieldName = 3

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

def newSemTimeStatic(breakdown: UserTimeBreakdown, isActive: bool) -> Time: ...

def parseFile(file: str, opts: OrgParseParameters) -> Document: ...

def parseString(text: str) -> Document: ...

def parseStringOpts(text: str, opts: OrgParseParameters) -> Document: ...

def formatToString(arg: Org) -> str: ...

def exportToYamlString(node: Org, opts: OrgYamlExportOpts) -> str: ...

def exportToYamlFile(node: Org, path: str, opts: OrgYamlExportOpts) -> None: ...

def exportToJsonString(node: Org) -> str: ...

def exportToJsonFile(node: Org, path: str) -> None: ...

def readProtobufFile(file: str) -> Document: ...

def exportToProtobufFile(doc: Document, file: str) -> None: ...

def exportToTreeString(node: Org, opts: OrgTreeExportOpts) -> str: ...

def exportToTreeFile(node: Org, path: str, opts: OrgTreeExportOpts) -> None: ...

def eachSubnodeRec(node: Org, callback: function) -> None: ...

/* clang-format on */