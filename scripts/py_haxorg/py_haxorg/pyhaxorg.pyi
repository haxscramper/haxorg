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

class OrgSemPlacement(Enum):
    TreeTitle = 1
    TreeBody = 2
    LinkDescription = 3
    ListItemBody = 4
    ListItemDesc = 5
    DocBody = 6

class OrgHorizontalDirection(Enum):
    ohdNone = 1
    ohdLeft = 2
    ohdRight = 3
    ohdCenter = 4

class OrgVerticalDirection(Enum):
    ovdNone = 1
    ovdTop = 2
    ovdCenter = 3
    ovdBottom = 4

class OrgSpecName(Enum):
    Unnamed = 1
    Result = 2
    Year = 3
    Day = 4
    Clock = 5
    Repeater = 6
    Link = 7
    Tags = 8
    Tag = 9
    State = 10
    Protocol = 11
    Desc = 12
    Times = 13
    Drawer = 14
    Args = 15
    Name = 16
    Definition = 17
    Body = 18
    HeaderArgs = 19
    File = 20
    Kind = 21
    Lang = 22
    Prefix = 23
    Text = 24
    Todo = 25
    Urgency = 26
    Title = 27
    Completion = 28
    Head = 29
    Subnodes = 30
    Properties = 31
    Logbook = 32
    Description = 33
    Logs = 34
    Newstate = 35
    Oldstate = 36
    Time = 37
    From = 38
    EndArgs = 39
    Flags = 40
    Value = 41
    Assoc = 42
    Main = 43
    Hash = 44
    Bullet = 45
    Counter = 46
    Checkbox = 47
    Header = 48
    To = 49
    Diff = 50
    Property = 51
    Subname = 52
    Values = 53
    Cells = 54
    Rows = 55
    Lines = 56
    Chunks = 57
    InheritanceMode = 58
    MainSetRule = 59
    SubSetRule = 60

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
    Example = 56
    SrcCode = 57
    SrcInlineCode = 58
    CallCode = 59
    PassCode = 60
    CmdArguments = 61
    CmdFlag = 62
    CmdKey = 63
    CmdValue = 64
    CmdNamedValue = 65
    UrgencyStatus = 66
    TextSeparator = 67
    Paragraph = 68
    AnnotatedParagraph = 69
    Bold = 70
    Italic = 71
    Verbatim = 72
    Backtick = 73
    Underline = 74
    Strike = 75
    Quote = 76
    Angle = 77
    Monospace = 78
    Par = 79
    InlineMath = 80
    DisplayMath = 81
    Space = 82
    Punctuation = 83
    Colon = 84
    Word = 85
    Escaped = 86
    Newline = 87
    SkipNewline = 88
    SkipSpace = 89
    SkipAny = 90
    RawLink = 91
    Link = 92
    Macro = 93
    BackendRaw = 94
    Symbol = 95
    TimeAssoc = 96
    StaticActiveTime = 97
    StaticInactiveTime = 98
    DynamicActiveTime = 99
    DynamicInactiveTime = 100
    TimeRange = 101
    SimpleTime = 102
    Details = 103
    Summary = 104
    Table = 105
    TableRow = 106
    TableCell = 107
    InlineFootnote = 108
    Footnote = 109
    Horizontal = 110
    Filetags = 111
    OrgTag = 112
    HashTag = 113
    MetaSymbol = 114
    AtMention = 115
    BracTag = 116
    Drawer = 117
    LatexClass = 118
    LatexHeader = 119
    LatexCompiler = 120
    LatexClassOptions = 121
    HtmlHead = 122
    Columns = 123
    PropertyList = 124
    Property = 125
    Placeholder = 126
    SubtreeDescription = 127
    SubtreeUrgency = 128
    Logbook = 129
    LogbookEntry = 130
    LogbookStateChange = 131
    LogbookNote = 132
    LogbookClock = 133
    LogbookRefile = 134
    LogbookPriority = 135
    LogbookPriorityChangeAction = 136
    LogbookReschedule = 137
    LogbookTagChange = 138
    LogbookTagChangeAction = 139
    RadioTarget = 140
    Target = 141

class OrgTextContext(Enum):
    otcPlain = 1
    otcSubtree0 = 2
    otcSubtree1 = 3
    otcSubtree2 = 4
    otcSubtree3 = 5
    otcSubtree4 = 6
    otcSubtree5 = 7
    otcSubtree6 = 8
    otcSubtree7 = 9
    otcSubtree8 = 10
    otcSubtree9 = 11
    otcSubtree10 = 12
    otcSubtree11 = 13
    otcSubtree12 = 14
    otcSubtreeOther = 15
    otcBold = 16
    otcItalic = 17
    otcStrike = 18
    otcUnderline = 19
    otcMonospaceInline = 20
    otcMonospaceBlock = 21

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

class OrgTokenKind(Enum):
    _None = 1
    Eof = 2
    GroupStart = 3
    GroupEnd = 4
    ErrorTerminator = 5
    CommandPrefix = 6
    LineCommand = 7
    CommandBegin = 8
    CommandEnd = 9
    DoubleColon = 10
    Text = 11
    StmtList = 12
    StmtListOpen = 13
    StmtListClose = 14
    ListStart = 15
    ListItemStart = 16
    ListClock = 17
    ListPlus = 18
    ListStar = 19
    ListDescOpen = 20
    ListDescClose = 21
    ListItemEnd = 22
    ListEnd = 23
    Checkbox = 24
    SubtreeTodoState = 25
    SubtreeUrgency = 26
    SubtreeCompletion = 27
    SubtreeStars = 28
    SubtreeTagSeparator = 29
    SubtreeTime = 30
    SubtreeEnd = 31
    ImplicitTime = 32
    TimeDuration = 33
    InactiveTimeBegin = 34
    InactiveTimeEnd = 35
    ActiveTimeBegin = 36
    ActiveTimeEnd = 37
    DynamicTimeContent = 38
    StaticTimeDatePart = 39
    StaticTimeDayPart = 40
    StaticTimeClockPart = 41
    StaticTimeRepeater = 42
    TimeDash = 43
    TimeArrow = 44
    Comment = 45
    ListDoubleColon = 46
    CommandArgumentsBegin = 47
    CommandArgumentsEnd = 48
    CommandKey = 49
    CommandValue = 50
    CommandFlag = 51
    CommandBracket = 52
    ColonLiteral = 53
    ColonIdent = 54
    ColonProperties = 55
    ColonDescription = 56
    ColonEnd = 57
    ColonLogbook = 58
    RawLogbook = 59
    LogbookStart = 60
    LogbookEnd = 61
    RawProperty = 62
    Link = 63
    CommandContentStart = 64
    CommandContentEnd = 65
    CodeContent = 66
    CodeContentBegin = 67
    CodeContentEnd = 68
    CodeText = 69
    TableContent = 70
    QuoteContent = 71
    BackendPass = 72
    LogBook = 73
    Drawer = 74
    Indent = 75
    Dedent = 76
    SameIndent = 77
    NoIndent = 78
    BoldOpen = 79
    BoldClose = 80
    BoldInline = 81
    BoldInlineOpen = 82
    BoldInlineClose = 83
    ItalicOpen = 84
    ItalicClose = 85
    ItalicInline = 86
    ItalicInlineOpen = 87
    ItalicInlineClose = 88
    VerbatimOpen = 89
    VerbatimClose = 90
    VerbatimInline = 91
    VerbatimInlineOpen = 92
    VerbatimInlineClose = 93
    MonospaceOpen = 94
    MonospaceClose = 95
    MonospaceInline = 96
    MonospaceInlineOpen = 97
    MonospaceInlineClose = 98
    BacktickOpen = 99
    BacktickClose = 100
    BacktickInline = 101
    BacktickInlineOpen = 102
    BacktickInlineClose = 103
    UnderlineOpen = 104
    UnderlineClose = 105
    UnderlineInline = 106
    UnderlineInlineOpen = 107
    UnderlineInlineClose = 108
    StrikeOpen = 109
    StrikeClose = 110
    StrikeInline = 111
    StrikeInlineOpen = 112
    StrikeInlineClose = 113
    QuoteOpen = 114
    QuoteClose = 115
    Punctuation = 116
    LinkOpen = 117
    LinkClose = 118
    RawUrl = 119
    LinkTargetOpen = 120
    LinkTargetClose = 121
    LinkInternal = 122
    LinkProtocol = 123
    LinkFull = 124
    LinkPath = 125
    LinkTarget = 126
    LinkExtraSeparator = 127
    LinkExtra = 128
    LinkDescriptionOpen = 129
    LinkDescriptionClose = 130
    TextSeparator = 131
    ParagraphStart = 132
    ParagraphEnd = 133
    FootnoteStart = 134
    FootnoteEnd = 135
    Word = 136
    Escaped = 137
    DoubleSlash = 138
    Newline = 139
    SkipSpace = 140
    SkipNewline = 141
    SkipAny = 142
    MaybeWord = 143
    Space = 144
    BigIdent = 145
    RawText = 146
    InlineSrc = 147
    InlineCall = 148
    CurlyStart = 149
    CurlyEnd = 150
    SymbolStart = 151
    Ident = 152
    DollarOpen = 153
    DollarClose = 154
    DoubleDollarOpen = 155
    DoubleDollarClose = 156
    LatexParOpen = 157
    LatexParClose = 158
    LatexBraceOpen = 159
    LatexBraceClose = 160
    LatexInlineRaw = 161
    DoubleAt = 162
    AtBracket = 163
    AtMention = 164
    HashTag = 165
    HashTagSub = 166
    HashTagOpen = 167
    HashTagClose = 168
    Comma = 169
    ParOpen = 170
    ParClose = 171
    Colon = 172
    Circumflex = 173
    MacroOpen = 174
    MacroClose = 175
    MetaBraceOpen = 176
    MetaBraceBody = 177
    MetaBraceClose = 178
    MetaArgsOpen = 179
    MetaArgsBody = 180
    MetaArgsClose = 181
    SrcOpen = 182
    SrcName = 183
    SrcArgs = 184
    SrcBody = 185
    SrcClose = 186
    CallOpen = 187
    CallName = 188
    CallInsideHeader = 189
    CallArgs = 190
    EndHeader = 191
    CallClose = 192
    CmdArguments = 193
    TableBegin = 194
    TableEnd = 195
    CellBody = 196
    RowSpec = 197
    CellSpec = 198
    Content = 199
    ContentStart = 200
    ContentEnd = 201
    PipeOpen = 202
    PipeSeparator = 203
    PipeClose = 204
    PipeCellOpen = 205
    DashSeparator = 206
    CornerPlus = 207
    Command = 208
    CommandArgs = 209
    Body = 210
    LangName = 211
    DoubleAngleOpen = 212
    DoubleAngleClose = 213
    TripleAngleOpen = 214
    TripleAngleClose = 215
    AngleOpen = 216
    AngleClose = 217
    TextBlock = 218

class OrgCommandKind(Enum):
    _None = 1
    Include = 2
    Filetags = 3
    Setupfile = 4
    Columns = 5
    OtherProperty = 6
    BeginTable = 7
    EndTable = 8
    Row = 9
    Cell = 10
    BeginAdmonition = 11
    EndAdmonition = 12
    BeginDynamic = 13
    EndDynamic = 14
    BeginCenter = 15
    EndCenter = 16
    BeginQuote = 17
    EndQuote = 18
    BeginSrc = 19
    EndSrc = 20
    BeginExport = 21
    EndExport = 22
    BeginExample = 23
    EndExample = 24
    BeginDetails = 25
    EndDetails = 26
    BeginSummary = 27
    EndSummary = 28
    LatexClassOptions = 29
    LatexClass = 30
    LatexCompiler = 31
    AttrLatex = 32
    AttrImg = 33
    AttrHtml = 34
    HtmlHead = 35
    Language = 36
    Options = 37
    Title = 38
    Property = 39
    Author = 40
    Bind = 41
    Creator = 42
    LatexHeader = 43
    Results = 44
    Call = 45
    Name = 46
    Caption = 47
    Header = 48
    TableFormula = 49

class OrgPropertyKind(Enum):
    Title = 1
    Author = 2
    Date = 3
    Email = 4
    Language = 5
    Url = 6
    SourceUrl = 7
    AttrImg = 8
    Toplevel = 9
    Blocker = 10
    Created = 11
    Unnumbered = 12
    Trigger = 13
    Ordered = 14
    Noblocking = 15
    ExportOptions = 16
    BackendExportOptions = 17
    AttrBackend = 18
    ColumnSpec = 19
    Name = 20
    Caption = 21
    LinkAbbrev = 22
    Filetags = 23
    TagConf = 24
    LatexHeader = 25
    OtherProperty = 26
    Id = 27

class OrgUnnumberedKind(Enum):
    Notoc = 1
    _True = 2
    _False = 3

class OrgBlockLexerState(Enum):
    _None = 1
    InHeader = 2
    InBody = 3
    Ended = 4
    Complete = 5

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
    Quote = 12
    Example = 13
    CmdArguments = 14
    CmdArgument = 15
    Export = 16
    AdmonitionBlock = 17
    Code = 18
    Time = 19
    TimeRange = 20
    Macro = 21
    Symbol = 22
    SubtreeLog = 23
    Subtree = 24
    InlineMath = 25
    Escaped = 26
    Newline = 27
    Space = 28
    Word = 29
    AtMention = 30
    RawText = 31
    Punctuation = 32
    Placeholder = 33
    BigIdent = 34
    Bold = 35
    Underline = 36
    Monospace = 37
    MarkQuote = 38
    Verbatim = 39
    Italic = 40
    Strike = 41
    Par = 42
    List = 43
    ListItem = 44
    Link = 45
    Document = 46
    ParseError = 47
    FileTarget = 48
    TextSeparator = 49
    Include = 50
    DocumentOptions = 51
    DocumentGroup = 52

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

SemStmt: Type
SemInline: Type
SemStmtList: Type
SemEmpty: Type
SemRow: Type
SemTable: Type
SemHashTag: Type
SemFootnote: Type
SemCompletion: Type
SemParagraph: Type
SemFormat: Type
SemCenter: Type
SemCommand: Type
SemLineCommand: Type
SemStandalone: Type
SemAttached: Type
SemCaption: Type
SemCommandGroup: Type
SemBlock: Type
SemQuote: Type
SemExample: Type
SemCmdArguments: Type
SemCmdArgument: Type
SemExport: Type
SemAdmonitionBlock: Type
SemCode: Type
CodeSwitch: Type
CodeSwitchLineStart: Type
CodeSwitchCalloutFormat: Type
CodeSwitchRemoveCallout: Type
CodeSwitchEmphasizeLine: Type
CodeSwitchDedent: Type
SemTime: Type
TimeRepeat: Type
TimeStatic: Type
TimeDynamic: Type
SemTimeRange: Type
SemMacro: Type
SemSymbol: Type
SymbolParam: Type
SemSubtreeLog: Type
SubtreeLogDescribedLog: Type
SubtreeLogPriority: Type
SubtreeLogNote: Type
SubtreeLogRefile: Type
SubtreeLogClock: Type
SubtreeLogState: Type
SubtreeLogTag: Type
SemSubtree: Type
SubtreePeriod: Type
SubtreeProperty: Type
SubtreePropertyNonblocking: Type
SubtreePropertyTrigger: Type
SubtreePropertyOrigin: Type
SubtreePropertyExportLatexClass: Type
SubtreePropertyExportLatexClassOptions: Type
SubtreePropertyExportLatexHeader: Type
SubtreePropertyExportLatexCompiler: Type
SubtreePropertyOrdered: Type
SubtreePropertyEffort: Type
SubtreePropertyVisibility: Type
SubtreePropertyExportOptions: Type
SubtreePropertyBlocker: Type
SubtreePropertyUnnumbered: Type
SubtreePropertyCreated: Type
SemLatexBody: Type
SemInlineMath: Type
SemLeaf: Type
SemEscaped: Type
SemNewline: Type
SemSpace: Type
SemWord: Type
SemAtMention: Type
SemRawText: Type
SemPunctuation: Type
SemPlaceholder: Type
SemBigIdent: Type
SemMarkup: Type
SemBold: Type
SemUnderline: Type
SemMonospace: Type
SemMarkQuote: Type
SemVerbatim: Type
SemItalic: Type
SemStrike: Type
SemPar: Type
SemList: Type
SemListItem: Type
SemLink: Type
LinkRaw: Type
LinkId: Type
LinkPerson: Type
LinkFootnote: Type
LinkFile: Type
SemDocument: Type
SemParseError: Type
SemFileTarget: Type
SemTextSeparator: Type
SemInclude: Type
IncludeExample: Type
IncludeExport: Type
IncludeSrc: Type
IncludeOrgDocument: Type
SemDocumentOptions: Type
SemDocumentGroup: Type
OrgExporterJson: Type
OrgExporterJson: Type
ExporterTreeOpts: Type
ExporterTreeOpts: Type
OrgExporterTree: Type
OrgExporterTree: Type
OrgExporterYaml: Type
OrgExporterYaml: Type
OrgContext: Type
OrgContext: Type
ExporterPython: Type
ExporterPython: Type

class SemId:
    def getKind(self) -> OrgSemKind: ...
    def __iter__(self) -> Iterator[SemId]: ...
    def __len__(self) -> int: ...
    def getDocument(self) -> Optional[SemId]

    @overload
    def __getitem__(self, idx: int) -> SemId: ...

    @overload
    def __getitem__(self, slice) -> List[SemId]: ...

    def eachSubnodeRec(self, cb) -> None: ...
    def _is(self, kind: OrgSemKind) -> bool: ...

class SemStmt(SemId):
    def getAttached(kind: OrgSemKind) -> Optional[SemId]: ...
    attached: List[SemId]

class SemInline(SemId):
    pass

class SemStmtList(SemId):
    pass

class SemEmpty(SemId):
    pass

class SemRow(SemId):
    pass

class SemTable(SemId):
    def getAttached(kind: OrgSemKind) -> Optional[SemId]: ...
    rows: List[SemRow]
    attached: List[SemId]

class SemHashTag(SemId):
    def prefixMatch(prefix: List[str]) -> bool: ...
    head: str
    subtags: List[SemHashTag]

class SemFootnote(SemId):
    tag: str
    definition: Optional[SemId]

class SemCompletion(SemId):
    done: int
    full: int
    isPercent: bool

class SemParagraph(SemId):
    def isFootnoteDefinition() -> bool: ...
    def getAttached(kind: OrgSemKind) -> Optional[SemId]: ...
    attached: List[SemId]

class SemFormat(SemId):
    pass

class SemCenter(SemId):
    pass

class SemCommand(SemId):
    pass

class SemLineCommand(SemId):
    pass

class SemStandalone(SemId):
    pass

class SemAttached(SemId):
    pass

class SemCaption(SemId):
    text: SemParagraph

class SemCommandGroup(SemId):
    def getAttached(kind: OrgSemKind) -> Optional[SemId]: ...
    attached: List[SemId]

class SemBlock(SemId):
    pass

class SemQuote(SemId):
    text: SemParagraph

class SemExample(SemId):
    pass

class SemCmdArguments(SemId):
    def popArg(key: str) -> Optional[SemCmdArgument]: ...
    positional: List[SemCmdArgument]
    named: UnorderedMap[str, SemCmdArgument]

class SemCmdArgument(SemId):
    def getInt() -> Optional[int]: ...
    def getBool() -> Optional[bool]: ...
    def getString() -> str: ...
    key: Optional[str]
    value: str

class SemExport(SemId):
    format: ExportFormat
    exporter: str
    parameters: SemCmdArguments
    placement: Optional[str]
    content: str

class SemAdmonitionBlock(SemId):
    pass

class SemCode(SemId):
    lang: Optional[str]
    switches: List[CodeSwitch]
    exports: CodeExports
    parameters: SemCmdArguments
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

class SemTime(SemId):
    def getStatic() -> TimeStatic: ...
    def getDynamic() -> TimeDynamic: ...
    def getTimeKind() -> TimeTimeKind: ...
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

class SemTimeRange(SemId):
    from_: SemTime
    to: SemTime

class SemMacro(SemId):
    name: str
    arguments: List[str]

class SemSymbol(SemId):
    name: str
    parameters: List[SymbolParam]
    positional: List[SemId]

class SymbolParam:
    key: Optional[str]
    value: str

class SemSubtreeLog(SemId):
    def setDescription(desc: SemStmtList) -> None: ...
    def getPriority() -> SubtreeLogPriority: ...
    def getNote() -> SubtreeLogNote: ...
    def getRefile() -> SubtreeLogRefile: ...
    def getClock() -> SubtreeLogClock: ...
    def getState() -> SubtreeLogState: ...
    def getTag() -> SubtreeLogTag: ...
    def getLogKind() -> SubtreeLogKind: ...
    log: SubtreeLogLogEntry

class SubtreeLogDescribedLog:
    desc: Optional[SemStmtList]

class SubtreeLogPriority:
    oldPriority: Optional[str]
    newPriority: Optional[str]
    on: SemTime

class SubtreeLogNote:
    on: SemTime

class SubtreeLogRefile:
    on: SemTime
    from_: SemLink

class SubtreeLogClock:
    pass

class SubtreeLogState:
    from_: OrgBigIdentKind
    to: OrgBigIdentKind
    on: SemTime

class SubtreeLogTag:
    on: SemTime
    tag: SemHashTag
    added: bool

class SemSubtree(SemId):
    def getTimePeriods(kinds: IntSet[SubtreePeriodKind]) -> List[SubtreePeriod]: ...
    def getProperties(kind: SubtreePropertyKind, subkind: str) -> List[SubtreeProperty]: ...
    def getProperty(kind: SubtreePropertyKind, subkind: str) -> Optional[SubtreeProperty]: ...
    def getContextualProperties(kind: SubtreePropertyKind, subkind: str) -> List[SubtreeProperty]: ...
    def getContextualProperty(kind: SubtreePropertyKind, subkind: str) -> Optional[SubtreeProperty]: ...
    level: int
    treeId: Optional[str]
    todo: Optional[str]
    completion: Optional[SemCompletion]
    description: Optional[SemParagraph]
    tags: List[SemHashTag]
    title: SemParagraph
    logbook: List[SemSubtreeLog]
    properties: List[SubtreeProperty]
    closed: Optional[SemTime]
    deadline: Optional[SemTime]
    scheduled: Optional[SemTime]

class SubtreePeriod:
    def getTime() -> SemTime: ...
    def getTimeRange() -> SemTime: ...
    kind: Kind

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
    text: str

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
    values: UnorderedMap[str, str]

class SubtreePropertyBlocker:
    blockers: List[str]

class SubtreePropertyUnnumbered:
    pass

class SubtreePropertyCreated:
    time: SemTime

class SemLatexBody(SemId):
    pass

class SemInlineMath(SemId):
    pass

class SemLeaf(SemId):
    text: str

class SemEscaped(SemId):
    text: str

class SemNewline(SemId):
    text: str

class SemSpace(SemId):
    text: str

class SemWord(SemId):
    text: str

class SemAtMention(SemId):
    text: str

class SemRawText(SemId):
    text: str

class SemPunctuation(SemId):
    text: str

class SemPlaceholder(SemId):
    text: str

class SemBigIdent(SemId):
    text: str

class SemMarkup(SemId):
    pass

class SemBold(SemId):
    pass

class SemUnderline(SemId):
    pass

class SemMonospace(SemId):
    pass

class SemMarkQuote(SemId):
    pass

class SemVerbatim(SemId):
    pass

class SemItalic(SemId):
    pass

class SemStrike(SemId):
    pass

class SemPar(SemId):
    pass

class SemList(SemId):
    def isDescriptionList() -> bool: ...

class SemListItem(SemId):
    def isDescriptionItem() -> bool: ...
    checkbox: ListItemCheckbox
    header: Optional[SemParagraph]

class SemLink(SemId):
    def resolve(doc: Document) -> Optional[SemId]: ...
    def resolve() -> Optional[SemId]: ...
    def getRaw() -> LinkRaw: ...
    def getId() -> LinkId: ...
    def getPerson() -> LinkPerson: ...
    def getFootnote() -> LinkFootnote: ...
    def getFile() -> LinkFile: ...
    def getLinkKind() -> LinkKind: ...
    description: Optional[SemParagraph]
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

class SemDocument(SemId):
    def resolve(node: SemId) -> Optional[SemId]: ...
    def getSubtree(id: str) -> Optional[SemSubtree]: ...
    def getProperties(kind: SubtreePropertyKind, subKind: str) -> List[SubtreeProperty]: ...
    def getProperty(kind: SubtreePropertyKind, subKind: str) -> Optional[SubtreeProperty]: ...
    idTable: UnorderedMap[str, SemId]
    nameTable: UnorderedMap[str, SemId]
    footnoteTable: UnorderedMap[str, SemId]
    anchorTable: UnorderedMap[str, SemId]
    title: Optional[SemParagraph]
    author: Optional[SemParagraph]
    creator: Optional[SemParagraph]
    email: Optional[SemRawText]
    language: Optional[List[str]]
    options: SemDocumentOptions
    exportFileName: Optional[str]

class SemParseError(SemId):
    pass

class SemFileTarget(SemId):
    path: str
    line: Optional[int]
    searchTarget: Optional[str]
    restrictToHeadlines: bool
    targetId: Optional[str]
    regexp: Optional[str]

class SemTextSeparator(SemId):
    pass

class SemInclude(SemId):
    def getExample() -> IncludeExample: ...
    def getExport() -> IncludeExport: ...
    def getSrc() -> IncludeSrc: ...
    def getOrgDocument() -> IncludeOrgDocument: ...
    def getIncludeKind() -> IncludeKind: ...
    data: IncludeData

class IncludeExample:
    pass

class IncludeExport:
    pass

class IncludeSrc:
    pass

class IncludeOrgDocument:
    pass

class SemDocumentOptions(SemId):
    def getProperties(kind: SubtreePropertyKind, subKind: str) -> List[SubtreeProperty]: ...
    def getProperty(kind: SubtreePropertyKind, subKind: str) -> Optional[SubtreeProperty]: ...
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

class SemDocumentGroup(SemId):
    pass

class OrgExporterJson:
    pass

class OrgExporterJson:
    def visitNode(node: SemId) -> None: ...
    def exportToString() -> str: ...
    def exportToFile(path: str) -> None: ...

class ExporterTreeOpts:
    withLineCol: bool
    withOriginalId: bool
    withSubnodeIdx: bool
    skipEmptyFields: bool
    startLevel: int
    withColor: bool

class ExporterTreeOpts:
    withLineCol: bool
    withOriginalId: bool
    withSubnodeIdx: bool
    skipEmptyFields: bool
    startLevel: int
    withColor: bool

class OrgExporterTree:
    pass

class OrgExporterTree:
    def toString(node: SemId, opts: ExporterTreeOpts) -> str: ...
    def toFile(node: SemId, path: str, opts: ExporterTreeOpts) -> None: ...

class OrgExporterYaml:
    pass

class OrgExporterYaml:
    def visitNode(node: SemId) -> None: ...
    def exportToString() -> str: ...
    def exportToFile(path: str) -> None: ...

class OrgContext:
    pass

class OrgContext:
    def parseFile(file: str) -> None: ...
    def parseString(text: str) -> None: ...
    def getNode() -> SemDocument: ...

class ExporterPython:
    pass

class ExporterPython:
    def enablePyStreamTrace(stream: object) -> None: ...
    def enableBufferTrace() -> None: ...
    def getTraceBuffer() -> str: ...
    def enableFileTrace(path: str) -> None: ...
    def setVisitAnyIdAround(cb: function) -> None: ...
    def setVisitAnyIdIn(cb: function) -> None: ...
    def setVisitAnyField(cb: function) -> None: ...
    def setEvalTopCb(cb: function) -> None: ...
    def setVisitIdAround(kind: OrgSemKind, cb: function) -> None: ...
    def setEvalIdAround(kind: OrgSemKind, cb: function) -> None: ...
    def setVisitIdInCb(kind: OrgSemKind, cb: function) -> None: ...
    def setEvalIdIn(kind: OrgSemKind, cb: function) -> None: ...
    def setVisitLeafField(kind: LeafFieldType, cb: function) -> None: ...
    def setEvalLeafField(kind: LeafFieldType, cb: function) -> None: ...
    def setVisitOrgField(kind: OrgSemKind, cb: function) -> None: ...
    def setEvalOrgField(kind: OrgSemKind, cb: function) -> None: ...
    def setSelf(val: object) -> None: ...
    def setNewOrgRes(kind: OrgSemKind, cb: function) -> None: ...
    def setNewAnyOrgRes(cb: function) -> None: ...
    def setNewLeafRes(kind: LeafFieldType, cb: function) -> None: ...
    def setNewAnyLeafRes(cb: function) -> None: ...
    def setPushVisitAnyId(cb: function) -> None: ...
    def setPopVisitAnyId(cb: function) -> None: ...
    def setPushVisitId(kind: OrgSemKind, cb: function) -> None: ...
    def setPopVisitIdCb(kind: OrgSemKind, cb: function) -> None: ...
    def setVisitAnyHookCb(cb: function) -> None: ...
    def setVisitIdHook(kind: OrgSemKind, cb: function) -> None: ...
    def evalTop(org: SemId) -> Res: ...
    def eval(org: SemId) -> Res: ...

/* clang-format on */
