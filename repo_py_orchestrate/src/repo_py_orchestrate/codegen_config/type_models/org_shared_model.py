from typing import Dict, List, Optional

from hstd_py_unidata.model_dsl import (
    Float32,
    Int32,
    __config__,
    __variant__,
    get_dsl_model,
)
from hstd_py_unidata.model_ir import ModelDef

M = get_dsl_model("org.sem.shared")
H = get_dsl_model("hstd")
P = get_dsl_model("org.parse")
Syntax = get_dsl_model("org.syntax")
Native = get_dsl_model("org.sem.native")


class CheckboxState(M.Enum):
    None_: int = 0
    Done: int = 1
    Empty: int = 2
    Partial: int = 3


class LinkVisibility(M.Enum):
    LiteralLinks: int = 0
    DescriptiveLinks: int = 1


class BlockVisibility(M.Enum):
    HideBlocks: int = 0
    NoHideBlocks: int = 1


class SubtreeTodoSource(M.Enum):
    """Where to take todo completion statistics from."""

    Checkbox: int = 0
    Todo: int = 1
    Both: int = 2


class ListFormattingMode(M.Enum):
    None_: int = 0
    Table1D1Col: int = 1
    Table1D2Col: int = 2
    Table2DColFirst: int = 3
    Table2DRowFirst: int = 4


class InitialSubtreeVisibility(M.Enum):
    Overview: int = 0
    Content: int = 1
    ShowAll: int = 2
    Show2Levels: int = 3
    Show3Levels: int = 4
    Show4Levels: int = 5
    Show5Levels: int = 6
    ShowEverything: int = 7


class LispCode(M.Class):
    class Call(M.Case):
        name: str
        args: List["LispCode"]

    class Quoted(M.Case):
        items: List["LispCode"]

    class List(M.Case):
        items: List["LispCode"]

    class Vector(M.Case):
        items: List["LispCode"]

    class KeyValue(M.Case):
        name: str
        value: List["LispCode"]

    class Number(M.Case):
        value: Int32 = 0

    class Text(M.Case):
        value: str

    class Ident(M.Case):
        name: str

    class Boolean(M.Case):
        value: bool = False

    class Real(M.Case):
        value: Float32

    __variant__(
        Call,
        Quoted,
        List,
        Vector,
        KeyValue,
        Number,
        Text,
        Ident,
        Boolean,
        Real,
        field="data",
        kind="Kind",
    )


class TimeValue(M.Class):
    class FixedTime(M.Case):
        time: H._T["UserTime"]

    class DynamicTime(M.Case):
        time: LispCode

    isActive: bool = False

    __variant__(FixedTime, DynamicTime, field="data", kind="Kind")


class Tblfm(M.Class):
    class Expr(M.Class):
        class AxisRef(M.Case):
            class Position(M.Class):
                class Index(M.Case):
                    index: Int32

                class Name(M.Case):
                    name: str

                __variant__(Index, Name, field="data", kind="Kind")

            col: Position
            row: Optional[Position] = None

        class AxisName(M.Case):
            name: str

        class IntLiteral(M.Case):
            value: Int32

        class FloatLiteral(M.Case):
            value: Float32

        class RangeRef(M.Case):
            first: Optional["Tblfm.Expr.AxisRef"] = None
            last: Optional["Tblfm.Expr.AxisRef"] = None

        class Call(M.Case):
            name: str
            args: List["Tblfm.Expr"]

        class Elisp(M.Case):
            value: str

        __variant__(
            AxisRef,
            AxisName,
            IntLiteral,
            FloatLiteral,
            RangeRef,
            Call,
            Elisp,
            field="data",
            kind="Kind",
        )

    class Assign(M.Class):
        class Flag(M.Enum):
            CellLeftAlign: int = 0
            CellRightAlign: int = 1
            CellCenterAlign: int = 2
            CellNumber: int = 3
            CellExponential: int = 4
            CellFloating: int = 5
            CellUnformat: int = 6
            CellText: int = 7
            CellBool: int = 8
            CellDecimal: int = 9
            CellPercentage: int = 10
            CellHours: int = 11
            CellZero: int = 12
            CellMarkInvalid: int = 13
            CellQuote: int = 14

        target: "Tblfm.Expr.AxisRef"
        expr: List["Tblfm.Expr"]
        flags: List[Flag]

    exprs: List[Assign]


class AttrValue(M.Class):
    class DimensionSpan(M.Class):
        first: Int32 = 0
        last: Optional[Int32] = None

    class TextValue(M.Case):
        value: str

    class FileReference(M.Case):
        file: str
        reference: str

    class LispValue(M.Case):
        code: LispCode

    name: Optional[str] = None
    varname: Optional[str] = None
    span: List[DimensionSpan]
    isQuoted: bool = False

    __variant__(
        TextValue,
        FileReference,
        LispValue,
        field="data",
        kind="Kind",
    )

    __config__(
        backend=dict(
            cpp=dict(
                variants=dict(
                    data=dict(variant_name="DataVariant"),
                ),
            ),
        ),
    )

    def getBool(self) -> Optional[bool]: ...

    def getInt(self) -> Optional[Int32]: ...

    def getString(self) -> str: ...

    def getDouble(self) -> Optional[float]: ...


class HashTagFlat(M.Class):
    tags: List[str]

    @M.Method(backend=dict(cpp=dict(name="operator<")))
    def less(self, other: "HashTagFlat") -> bool: ...


class TodoKeyword(M.Class):
    class Transition(M.Enum):
        None_: int = 0
        NoteWithTimestamp: int = 1
        Timestamp: int = 2

    name: str
    shortcut: Optional[str] = None
    onEnter: Transition
    onLeave: Transition


class HashTagText(M.Class):
    """Single or nested inline hashtag."""

    head: str = M.Field(doc="Main part of the tag")
    subtags: List["HashTagText"] = M.Field(doc="Nested tags")

    def prefixMatch(self, prefix: List[str]) -> bool: ...

    def getFlatHashes(self, withIntermediate: bool = True) -> List[HashTagFlat]: ...


class SubtreePath(M.Class):
    path: List[str]


class LinkTarget(M.Class):
    class Raw(M.Case):
        text: str

    class Id(M.Case):
        text: str

    class CustomId(M.Case):
        text: str

    class SubtreeTitle(M.Case):
        title: SubtreePath
        level: Int32

    class Person(M.Case):
        name: str

    class UserProtocol(M.Case):
        protocol: str
        target: str

    class Internal(M.Case):
        target: str

    class Footnote(M.Case):
        target: str

    class File(M.Case):
        file: str

    class Attachment(M.Case):
        file: str

    __variant__(
        Raw,
        Id,
        CustomId,
        SubtreeTitle,
        Person,
        UserProtocol,
        Internal,
        Footnote,
        File,
        Attachment,
        field="data",
        kind="Kind",
    )


class SubtreeLogHead(M.Class):
    class Priority(M.Case):
        class Action(M.Enum):
            Added: int = 0
            Removed: int = 1
            Changed: int = 2

        oldPriority: Optional[str] = None
        newPriority: Optional[str] = None
        on: H._T["UserTime"]
        action: Action

    class Note(M.Case):
        on: H._T["UserTime"]

    class Refile(M.Case):
        on: H._T["UserTime"]
        from_: LinkTarget

        __config__(
            backend=dict(cpp=dict(field_names=dict(from_="from"))),
        )

    class Clock(M.Case):
        from_: H._T["UserTime"]
        to: Optional[H._T["UserTime"]] = None

        __config__(
            backend=dict(cpp=dict(field_names=dict(from_="from"))),
        )

    class State(M.Case):
        from_: str
        to: str
        on: H._T["UserTime"]

        __config__(
            backend=dict(cpp=dict(field_names=dict(from_="from"))),
        )

    class Deadline(M.Case):
        from_: Optional[H._T["UserTime"]] = None
        to: H._T["UserTime"]
        on: H._T["UserTime"]

        __config__(
            backend=dict(cpp=dict(field_names=dict(from_="from"))),
        )

    class Schedule(M.Case):
        from_: Optional[H._T["UserTime"]] = None
        to: H._T["UserTime"]
        on: H._T["UserTime"]

        __config__(
            backend=dict(cpp=dict(field_names=dict(from_="from"))),
        )

    class Tag(M.Case):
        on: H._T["UserTime"]
        tag: HashTagText
        added: bool = False

    class Unknown(M.Case):
        pass

    __variant__(
        Priority,
        Note,
        Refile,
        Clock,
        State,
        Deadline,
        Schedule,
        Tag,
        Unknown,
        field="log",
        kind="Kind",
    )

    __config__(
        backend=dict(
            cpp=dict(
                variants=dict(
                    log=dict(
                        variant_name="LogEntry",
                        kind_getter="getLogKind",
                        default="Note{}",
                    ),
                ),
            ),
        ),
    )


class SubtreeCompletion(M.Class):
    done: Int32 = 0
    full: Int32 = 0
    isPercent: bool = False


class AttrList(M.Class):
    items: List[AttrValue]


class AttrGroup(M.Class):
    positional: AttrList
    named: Dict[str, AttrList]

    def getFlatArgs(self) -> List[AttrValue]: ...

    def getAttrs(self, key: Optional[str] = None) -> List[AttrValue]: ...

    @M.Method(backend=dict(cpp=dict(is_const=False)))
    def setNamedAttr(self, key: str, attrs: List[AttrValue]) -> None: ...

    @M.Method(backend=dict(cpp=dict(is_const=False)))
    def setPositionalAttr(self, items: List[AttrValue]) -> None: ...

    def getPositionalSize(self) -> Int32: ...

    def getNamedSize(self) -> Int32: ...

    def isEmpty(self) -> bool: ...

    def getAll(self) -> AttrList: ...

    @M.Method(backend=dict(cpp=dict(return_const_ref=True)))
    def atPositional(self, index: Int32) -> AttrValue: ...

    def getPositional(self, index: Int32) -> Optional[AttrValue]: ...

    @M.Method(backend=dict(cpp=dict(return_const_ref=True)))
    def atNamed(self, index: str) -> AttrList: ...

    def getNamed(self, index: str) -> Optional[AttrList]: ...

    def atVarNamed(self, index: str) -> AttrList: ...

    def getVarNamed(self, index: str) -> Optional[AttrList]: ...

    def atFirstVarNamed(self, index: str) -> AttrValue: ...

    def getFirstVarNamed(self, index: str) -> Optional[AttrValue]: ...


class OrgCodeEvalInput(M.Class):
    class Var(M.Class):
        name: str
        value: Native._T["OrgJson"]

    class ResultType(M.Enum):
        None_: int = 0
        Table: int = 1
        List: int = 2
        Scalar: int = 3
        SaveFile: int = 4

    class ResultFormat(M.Enum):
        None_: int = 0
        Raw: int = 1
        Code: int = 2
        Drawer: int = 3
        ExportType: int = 4
        Link: int = 5

    class ResultHandling(M.Enum):
        None_: int = 0
        Replace: int = 1
        Silent: int = 2
        Discard: int = 3
        Append: int = 4
        Prepend: int = 5

    blockAttrs: AttrGroup
    tangledCode: str
    exportType: Optional[str] = None
    resultType: ResultType
    resultFormat: ResultFormat
    resultHandling: ResultHandling
    language: str
    argList: List[Var]

    def getVariable(self, name: str) -> Optional["OrgCodeEvalInput.Var"]: ...


class OrgCodeEvalOutput(M.Class):
    """Single command/subprocess executed to evaluate an Org Babel entry."""

    stdoutText: str
    stderrText: str
    code: Int32 = 0
    cmd: Optional[str] = None
    args: List[str]
    cwd: str
    appliedHeaderArg: AttrGroup


class ColumnView(M.Class):
    class Summary(M.Class):
        class CheckboxAggregate(M.Case):
            class Kind(M.Enum):
                IfAllNested: int = 0
                AggregateFractionRec: int = 1
                AggregatePercentRec: int = 2

            kind: Kind

        class MathAggregate(M.Case):
            class Kind(M.Enum):
                Min: int = 0
                Max: int = 1
                Mean: int = 2
                Sum: int = 3
                LowHighEst: int = 4

            kind: Kind
            formatDigits: Optional[Int32] = None
            formatPrecision: Optional[Int32] = None

        __variant__(
            CheckboxAggregate,
            MathAggregate,
            field="data",
            kind="Kind",
        )

    class Column(M.Class):
        summary: Optional["ColumnView.Summary"] = None
        width: Optional[Int32] = None
        property: Optional[str] = None
        propertyTitle: Optional[str] = None

    columns: List[Column]


class BlockCodeLine(M.Class):
    class Part(M.Class):
        class Raw(M.Case):
            code: str

        class Callout(M.Case):
            name: str

        class Tangle(M.Case):
            target: str

        __variant__(Raw, Callout, Tangle, field="data", kind="Kind")

    parts: List[Part]


class DocumentExportConfig(M.Class):
    class TaskExport(M.Class):
        taskWhitelist: List[str]

    class TagExport(M.Enum):
        None_: int = 0
        All: int = 1
        NotInToc: int = 2

    class TaskFiltering(M.Enum):
        Whitelist: int = 0
        Done: int = 1
        None_: int = 2
        All: int = 3

    class BrokenLinks(M.Enum):
        None_: int = 0
        Mark: int = 1
        Raise: int = 2
        Ignore: int = 3

    class ArchivedTrees(M.Enum):
        Skip: int = 0
        Headline: int = 1
        All: int = 2

    class DoExport(M.Case):
        exportToc: bool

    class ExportFixed(M.Case):
        exportLevels: Int32

    inlinetasks: Optional[bool] = None
    footnotes: Optional[bool] = None
    clock: Optional[bool] = None
    author: Optional[bool] = None
    emphasis: Optional[bool] = None
    specialStrings: Optional[bool] = None
    propertyDrawers: Optional[bool] = None
    statisticsCookies: Optional[bool] = None
    todoText: Optional[bool] = None
    smartQuotes: Optional[bool] = None
    fixedWidth: Optional[bool] = None
    timestamps: Optional[bool] = None
    preserveBreaks: Optional[bool] = None
    subSuperscripts: Optional[bool] = None
    expandLinks: Optional[bool] = None
    creator: Optional[bool] = None
    drawers: Optional[bool] = None
    date: Optional[bool] = None
    entities: Optional[bool] = None
    email: Optional[bool] = None
    sectionNumbers: Optional[bool] = None
    planning: Optional[bool] = None
    priority: Optional[bool] = None
    latex: Optional[bool] = None
    timestamp: Optional[bool] = None
    title: Optional[bool] = None
    tables: Optional[bool] = None
    headlineLevels: Optional[Int32] = None
    brokenLinks: BrokenLinks
    tagExport: TagExport
    taskFiltering: TaskFiltering
    archivedTrees: ArchivedTrees

    __variant__(DoExport, ExportFixed, field="tocExport", kind="TocExportKind")

    __config__(
        backend=dict(
            cpp=dict(
                field_defaults=dict(
                    tagExport="TagExport::NotInToc",
                    taskFiltering="TaskFiltering::All",
                    archivedTrees="ArchivedTrees::Headline",
                ),
                variants=dict(
                    tocExport=dict(
                        variant_name="TocExport",
                        kind_getter="getTocExportKind",
                    ),
                ),
            ),
        ),
    )


class SubtreePeriod(M.Class):
    class Kind(M.Enum):
        Clocked: int = 0
        Closed: int = 1
        Scheduled: int = 2
        Titled: int = 3
        Deadline: int = 4
        Created: int = 5
        Repeated: int = 6

    kind: Kind
    from_: H._T["UserTime"]
    to: Optional[H._T["UserTime"]] = None

    __config__(
        backend=dict(cpp=dict(field_names=dict(from_="from"))),
    )


class NamedProperty(M.Class):
    """Single subtree property."""

    class Nonblocking(M.Case):
        isBlocking: bool

    class ArchiveTime(M.Case):
        time: H._T["UserTime"]

    class ArchiveFile(M.Case):
        file: str

    class ArchiveOlpath(M.Case):
        path: SubtreePath

    class ArchiveTarget(M.Case):
        path: SubtreePath
        pattern: str

    class ArchiveCategory(M.Case):
        category: str

    class ArchiveTodo(M.Case):
        todo: str

    class Trigger(M.Case):
        pass

    class ExportLatexClass(M.Case):
        latexClass: str

    class CookieData(M.Case):
        """COOKIE_DATA settings for subtree completion calculation."""

        isRecursive: bool
        source: SubtreeTodoSource

    class ExportLatexClassOptions(M.Case):
        options: List[str]

    class ExportLatexHeader(M.Case):
        header: str

    class ExportLatexCompiler(M.Case):
        compiler: str

    class Ordered(M.Case):
        isOrdered: bool

    class Effort(M.Case):
        hours: Int32 = 0
        minutes: Int32 = 0

    class Visibility(M.Case):
        class Level(M.Enum):
            Folded: int = 0
            Children: int = 1
            Content: int = 2
            All: int = 3

        level: Level

    class ExportOptions(M.Case):
        backend: str
        values: Dict[str, str]

    class Blocker(M.Case):
        blockers: List[str]

    class Unnumbered(M.Case):
        pass

    class Created(M.Case):
        time: TimeValue

    class RadioId(M.Case):
        words: List[str]

    class HashtagDef(M.Case):
        hashtag: HashTagText

    class CustomArgs(M.Case):
        """Custom property with parsed arguments."""

        name: str
        sub: Optional[str] = None
        attrs: AttrGroup

    class CustomRaw(M.Case):
        name: str
        value: str

    class CustomId(M.Case):
        value: str

    class CustomSubtreeJson(M.Case):
        name: str
        value: Native._T["OrgJson"]

    class CustomSubtreeFlags(M.Case):
        name: str
        value: AttrGroup

    __variant__(
        Nonblocking,
        ArchiveTime,
        ArchiveFile,
        ArchiveOlpath,
        ArchiveTarget,
        ArchiveCategory,
        ArchiveTodo,
        Trigger,
        ExportLatexClass,
        CookieData,
        ExportLatexClassOptions,
        ExportLatexHeader,
        ExportLatexCompiler,
        Ordered,
        Effort,
        Visibility,
        ExportOptions,
        Blocker,
        Unnumbered,
        Created,
        RadioId,
        HashtagDef,
        CustomArgs,
        CustomRaw,
        CustomId,
        CustomSubtreeJson,
        CustomSubtreeFlags,
        field="data",
        kind="Kind",
    )

    __config__(
        backend=dict(
            cpp=dict(
                section_code=[
                    dict(
                        kind="public",
                        text="NamedProperty(Data const& data) : data(data) {}",
                    ),
                ],
            ),
        ),
    )

    def isMatching(self, kind: str, subKind: Optional[str] = None) -> bool: ...

    def getName(self) -> str: ...

    def getSubKind(self) -> Optional[str]: ...


class OrgDiagnostics(M.Class):
    """Diagnostics collected by parsing, semantic conversion, and evaluation."""

    class ParseTokenError(M.Case):
        brief: str
        detail: str
        parserFunction: str
        parserLine: Int32
        tokenKind: Syntax._T["OrgTokenKind"]
        tokenText: str
        loc: Optional[P._T["SourceLoc"]] = None
        errName: str
        errCode: str

    class ParseError(M.Case):
        brief: str
        detail: str
        parserFunction: str
        parserLine: Int32
        errName: str
        errCode: str
        loc: Optional[P._T["SourceLoc"]] = None

    class IncludeError(M.Case):
        brief: str
        targetPath: str
        workingFile: str

    class ConvertError(M.Case):
        brief: str
        detail: str
        convertFunction: str
        convertLine: Int32
        convertFile: str
        errName: str
        errCode: str
        loc: Optional[P._T["SourceLoc"]] = None

    class InternalError(M.Case):
        message: str
        function: str
        line: Int32
        file: str
        loc: Optional[P._T["SourceLoc"]] = None

    __variant__(
        ParseTokenError,
        ParseError,
        IncludeError,
        ConvertError,
        InternalError,
        field="data",
        kind="Kind",
    )

    __config__(
        backend=dict(
            cpp=dict(
                section_code=[
                    dict(
                        kind="public",
                        text="OrgDiagnostics(Data const& data) : data(data) {}",
                    ),
                ],
            ),
        ),
    )


def get_model() -> ModelDef:
    return M.finalize()
