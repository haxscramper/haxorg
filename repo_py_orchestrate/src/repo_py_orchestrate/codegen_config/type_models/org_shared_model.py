from typing import Annotated, Dict, List, Optional

from hstd_py_unidata.model_dsl import (
    EnFieldAnnotation,
    Float32,
    Int32,
    __config__,
    __variant__,
    get_dsl_model,
)
from hstd_py_unidata.model_ir import ModelDef
from repo_py_orchestrate.codegen_config.codegen_type_groups import OrgTypeGroup

M = get_dsl_model("org.sem.shared")
H = get_dsl_model("hstd")
P = get_dsl_model("org.parse")
Syntax = get_dsl_model("org.syntax")
Native = get_dsl_model("org.sem.native")


class CheckboxState(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    None_: int = 0
    Done: int = 1
    Empty: int = 2
    Partial: int = 3


class LinkVisibility(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    LiteralLinks: int = 0
    DescriptiveLinks: int = 1


class BlockVisibility(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    HideBlocks: int = 0
    NoHideBlocks: int = 1


class SubtreeTodoSource(M.Enum):
    """Where to take todo completion statistics from"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    Checkbox: Annotated[
        int,
        EnFieldAnnotation(doc="Only count checkbox subnodes as a progress completion"),
    ] = 0
    Todo: Annotated[int, EnFieldAnnotation(doc="Use subtrees with todo keywords")] = 1
    Both: Annotated[int, EnFieldAnnotation(doc="Use both subtrees and todo keywords")] = 2


class ListFormattingMode(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    None_: Annotated[int, EnFieldAnnotation(doc="Default, no custom formatting")] = 0
    Table1D1Col: Annotated[
        int, EnFieldAnnotation(doc="one column, each table item is an individual row")
    ] = 1
    Table1D2Col: Annotated[
        int,
        EnFieldAnnotation(
            doc="for description lists, treat header row as an individual column"
        ),
    ] = 2
    Table2DColFirst: Annotated[
        int,
        EnFieldAnnotation(
            doc="for tables tables with arbitrary column count, treat the first level of items as "
            "column names, treat all nested elements in these columns as row values"
        ),
    ] = 3
    Table2DRowFirst: Annotated[
        int,
        EnFieldAnnotation(
            doc="for tables with arbitrary column count, each top-level list item is an individual "
            "row, then each item in the nested list is a cell on this row."
        ),
    ] = 4


class InitialSubtreeVisibility(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    Overview: int = 0
    Content: int = 1
    ShowAll: int = 2
    Show2Levels: int = 3
    Show3Levels: int = 4
    Show4Levels: int = 5
    Show5Levels: int = 6
    ShowEverything: int = 7


class LispCode(M.Class):
    __config__(
        backend=dict(
            cpp=dict(
                org_groups=OrgTypeGroup.SHARED_TYPES,
                default_constructor=True,
            )
        )
    )

    class Call(M.Case):
        name: str
        args: List["LispCode"]
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class Quoted(M.Case):
        items: List["LispCode"]
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class List(M.Case):
        items: List["LispCode"]
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class Vector(M.Case):
        items: List["LispCode"]
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class KeyValue(M.Case):
        name: str
        value: List["LispCode"]
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class Number(M.Case):
        value: Int32 = 0
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class Text(M.Case):
        value: str
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class Ident(M.Case):
        name: str
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class Boolean(M.Case):
        value: bool = False
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class Real(M.Case):
        value: Float32
        __config__(backend=dict(cpp=dict(default_constructor=True)))

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
    __config__(
        backend=dict(
            cpp=dict(
                org_groups=OrgTypeGroup.SHARED_TYPES,
                default_constructor=True,
            )
        )
    )

    class FixedTime(M.Case):
        time: H._T["UserTime"]
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class DynamicTime(M.Case):
        time: LispCode
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    isActive: bool = False

    __variant__(FixedTime, DynamicTime, field="data", kind="Kind")


class Tblfm(M.Class):
    __config__(
        backend=dict(
            cpp=dict(
                org_groups=OrgTypeGroup.SHARED_TYPES,
                default_constructor=True,
            )
        )
    )

    class Expr(M.Class):
        class AxisRef(M.Case):
            class Position(M.Class):
                class Index(M.Case):
                    index: Int32
                    __config__(backend=dict(cpp=dict(default_constructor=True)))

                class Name(M.Case):
                    name: str
                    __config__(backend=dict(cpp=dict(default_constructor=True)))

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
            """Flags for table format expression cell formulas"""

            CellLeftAlign: Annotated[
                int, EnFieldAnnotation(doc="Left-align the result")
            ] = 0
            CellRightAlign: Annotated[
                int, EnFieldAnnotation(doc="Right-align the result")
            ] = 1
            CellCenterAlign: Annotated[
                int, EnFieldAnnotation(doc="Center-align the result")
            ] = 2
            CellNumber: Annotated[
                int, EnFieldAnnotation(doc="Convert result to number/currency format")
            ] = 3
            CellExponential: Annotated[
                int, EnFieldAnnotation(doc="Use exponential notation for numbers")
            ] = 4
            CellFloating: Annotated[
                int, EnFieldAnnotation(doc="Use floating point format")
            ] = 5
            CellUnformat: Annotated[
                int, EnFieldAnnotation(doc="Unformat values before calculating")
            ] = 6
            CellText: Annotated[int, EnFieldAnnotation(doc="Convert result to text")] = 7
            CellBool: Annotated[
                int, EnFieldAnnotation(doc="Display boolean values as t/nil")
            ] = 8
            CellDecimal: Annotated[
                int,
                EnFieldAnnotation(
                    doc="Fixed format with specified decimal places (e.g., ;D2)"
                ),
            ] = 9
            CellPercentage: Annotated[int, EnFieldAnnotation(doc="Percentage format")] = (
                10
            )
            CellHours: Annotated[
                int, EnFieldAnnotation(doc="Convert to hours/minutes (HH:MM)")
            ] = 11
            CellZero: Annotated[
                int, EnFieldAnnotation(doc="Display zero as empty cell")
            ] = 12
            CellMarkInvalid: Annotated[
                int, EnFieldAnnotation(doc="Mark field as invalid if conversion fails")
            ] = 13
            CellQuote: Annotated[int, EnFieldAnnotation(doc="Quote field contents")] = 14

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
    isQuoted: bool = M.Field(
        doc="If the original value was explicitly quoted in the org-mode code",
        default=False,
    )

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
                org_groups=OrgTypeGroup.SHARED_TYPES,
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
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SHARED_TYPES)))

    tags: List[str]

    @M.Method(backend=dict(cpp=dict(name="operator<")))
    def less(self, other: "HashTagFlat") -> bool: ...


class TodoKeyword(M.Class):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SHARED_TYPES)))

    class Transition(M.Enum):
        None_: int = 0
        NoteWithTimestamp: int = 1
        Timestamp: int = 2

    name: str
    shortcut: Optional[str] = None
    onEnter: Transition
    onLeave: Transition


class HashTagText(M.Class):
    """Single or nested inline hash-tag"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SHARED_TYPES)))

    head: str = M.Field(doc="Main part of the tag")
    subtags: List["HashTagText"] = M.Field(doc="List of nested tags")

    def prefixMatch(self, prefix: List[str]) -> bool:
        """Check if list of tag names is a prefix for either of the nested hash tags in this one"""
        ...

    def getFlatHashes(self, withIntermediate: bool = True) -> List[HashTagFlat]:
        """Get flat list of expanded hashtags"""
        ...


class SubtreePath(M.Class):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SHARED_TYPES)))

    path: List[str]


class LinkTarget(M.Class):
    __config__(
        backend=dict(
            cpp=dict(
                org_groups=OrgTypeGroup.SHARED_TYPES,
                default_field_pass_constructor=True,
            )
        )
    )

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
        """Priority added"""

        class Action(M.Enum):
            """Priority change action"""

            Added: Annotated[
                int, EnFieldAnnotation(doc="`Priority B added on [timestamp]`")
            ] = 0
            Removed: Annotated[
                int, EnFieldAnnotation(doc="`Priority C removed on [timestamp]`")
            ] = 1
            Changed: Annotated[
                int, EnFieldAnnotation(doc="`Priority B changed from C on [timestamp]`")
            ] = 2

        oldPriority: Optional[str] = M.Field(
            doc="Previous priority for change and removal"
        )
        newPriority: Optional[str] = M.Field(doc="New priority for change and addition")
        on: H._T["UserTime"] = M.Field(doc="When priority was changed")
        action: Action = M.Field(doc="Which action taken")

    class Note(M.Case):
        """Timestamped note"""

        on: H._T["UserTime"] = M.Field(doc="Where log was taken")

    class Refile(M.Case):
        """Refiling action"""

        on: H._T["UserTime"] = M.Field(doc="When the refiling happened")
        from_: LinkTarget = M.Field(doc="Link to the original subtree")

        __config__(
            backend=dict(cpp=dict(field_names=dict(from_="from"))),
        )

    class Clock(M.Case):
        """Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`"""

        from_: H._T["UserTime"] = M.Field(doc="Clock start time")
        to: Optional[H._T["UserTime"]] = M.Field(
            doc="Optional end of the clock", default=None
        )

        __config__(
            backend=dict(cpp=dict(field_names=dict(from_="from"))),
        )

    class State(M.Case):
        """Change of the subtree state -- `- State "WIP" from "TODO" [2023-04-30 Sun 13:29:04]`"""

        from_: str
        to: str
        on: H._T["UserTime"]

        __config__(
            backend=dict(cpp=dict(field_names=dict(from_="from"))),
        )

    class Deadline(M.Case):
        """Change of the subtree deadline"""

        from_: Optional[H._T["UserTime"]] = None
        to: H._T["UserTime"]
        on: H._T["UserTime"]

        __config__(
            backend=dict(cpp=dict(field_names=dict(from_="from"))),
        )

    class Schedule(M.Case):
        """Change of the subtree Schedule"""

        from_: Optional[H._T["UserTime"]] = None
        to: H._T["UserTime"]
        on: H._T["UserTime"]

        __config__(
            backend=dict(cpp=dict(field_names=dict(from_="from"))),
        )

    class Tag(M.Case):
        """Assign tag to the subtree `- Tag "project##haxorg" Added on [2023-04-30 Sun 13:29:06]`"""

        on: H._T["UserTime"] = M.Field(doc="When the log was assigned")
        tag: HashTagText = M.Field(doc="Tag in question")
        added: bool = M.Field(doc="Added/removed?", default=False)

    class Unknown(M.Case):
        """Unknown subtree log entry kind"""

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
                org_groups=OrgTypeGroup.SHARED_TYPES,
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
    """Completion status of the subtree list element"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SHARED_TYPES)))

    done: Int32 = M.Field(doc="Number of completed tasks", default=0)
    full: Int32 = M.Field(doc="Full number of tasks", default=0)
    isPercent: bool = M.Field(
        doc="Use fraction or percent to display completion", default=False
    )


class AttrList(M.Class):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SHARED_TYPES)))

    items: List[AttrValue]


class AttrGroup(M.Class):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SHARED_TYPES)))

    positional: AttrList = M.Field(doc="Positional arguments with no keys")
    named: Dict[str, AttrList] = M.Field(doc="Stored key-value mapping")

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

    def atFirstNamed(self, index: str) -> AttrValue: ...

    def getFirstNamed(self, index: str) -> Optional[AttrValue]: ...


class OrgCodeEvalInput(M.Class):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SHARED_TYPES)))

    class Var(M.Class):
        name: str
        value: Native._T["OrgJson"]

    class ResultType(M.Enum):
        """What context to use for results"""

        None_: int = 0
        Table: Annotated[
            int,
            EnFieldAnnotation(
                doc="Interpret the results as an Org table. If the result is a single value, create a table with one row and one column."
            ),
        ] = 1
        List: Annotated[
            int,
            EnFieldAnnotation(
                doc="Interpret the results as an Org list. If the result is a single value, create a list of one element."
            ),
        ] = 2
        Scalar: Annotated[
            int,
            EnFieldAnnotation(
                doc="Interpret literally and insert as quoted text. Do not create a table."
            ),
        ] = 3
        SaveFile: Annotated[
            int,
            EnFieldAnnotation(
                doc="Interpret as a filename. Save the results of execution of the code block to that file, then insert a link to it."
            ),
        ] = 4

    class ResultFormat(M.Enum):
        """How to interpret output from the script"""

        None_: int = 0
        Raw: Annotated[
            int,
            EnFieldAnnotation(
                doc="Interpreted as raw Org mode. Inserted directly into the buffer."
            ),
        ] = 1
        Code: Annotated[
            int, EnFieldAnnotation(doc="Result enclosed in a code block.")
        ] = 2
        Drawer: Annotated[
            int,
            EnFieldAnnotation(
                doc="Results are added directly to the Org file as with ‘raw’, but are wrapped in a ‘RESULTS’ drawer or results macro (for inline code blocks), for later scripting and automated processing."
            ),
        ] = 3
        ExportType: Annotated[
            int, EnFieldAnnotation(doc="Results enclosed in a ‘BEGIN_EXPORT’ block.")
        ] = 4
        Link: int = 5

    class ResultHandling(M.Enum):
        """What to do with the final evaluation results"""

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
    """Single command/subprocess executed to evaluate org babel code entry"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SHARED_TYPES)))

    stdoutText: str
    stderrText: str
    code: Int32 = 0
    cmd: Optional[str] = M.Field(
        doc="Command evaluated, if none then eval output did not run CLI subprocess",
        default=None,
    )
    args: List[str] = M.Field(doc="Command line arguments provided for execution")
    cwd: str = M.Field(doc="Working directory where command was executed")
    appliedHeaderArg: AttrGroup = M.Field(
        doc="Final set of header arguments applied during evaluation"
    )


class ColumnView(M.Class):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SHARED_TYPES)))

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
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SHARED_TYPES)))

    class Part(M.Class):
        class Raw(M.Case):
            code: str

        class Callout(M.Case):
            name: str

        class Tangle(M.Case):
            target: str

        __variant__(Raw, Callout, Tangle, field="data", kind="Kind")

    parts: List[Part] = M.Field(doc="parts of the single line")


class DocumentExportConfig(M.Class):
    class TaskExport(M.Class):
        taskWhitelist: List[str]
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class TagExport(M.Enum):
        None_: int = 0
        All: int = 1
        NotInToc: Annotated[
            int,
            EnFieldAnnotation(
                doc="Export tags in subtree titles but not in the table of content"
            ),
        ] = 2

    class TaskFiltering(M.Enum):
        Whitelist: Annotated[
            int, EnFieldAnnotation(doc="Include tasks from the whitelist")
        ] = 0
        Done: Annotated[int, EnFieldAnnotation(doc="Include tasks marked as done")] = 1
        None_: Annotated[
            int, EnFieldAnnotation(doc="Exclude all task subtrees from export")
        ] = 2
        All: Annotated[int, EnFieldAnnotation(doc="Add all task subtrees to export")] = 3

    class BrokenLinks(M.Enum):
        None_: int = 0
        Mark: int = 1
        Raise: int = 2
        Ignore: int = 3

    class ArchivedTrees(M.Enum):
        """Configure how archived trees are exported"""

        Skip: Annotated[int, EnFieldAnnotation(doc="Skip archived trees entirely")] = 0
        Headline: Annotated[
            int, EnFieldAnnotation(doc="Export only headlines of archived trees")
        ] = 1
        All: Annotated[
            int, EnFieldAnnotation(doc="Export archived trees with full content")
        ] = 2

    class DoExport(M.Case):
        exportToc: bool
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class ExportFixed(M.Case):
        exportLevels: Int32
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    inlinetasks: Optional[bool] = M.Field(
        doc="Toggle inclusion of inlinetasks", default=None
    )
    footnotes: Optional[bool] = M.Field(
        doc="Toggle the inclusion of footnotes", default=None
    )
    clock: Optional[bool] = M.Field(
        doc="Toggle inclusion of 'CLOCK' keywords", default=None
    )
    author: Optional[bool] = M.Field(
        doc="Toggle inclusion of author name into exported file", default=None
    )
    emphasis: Optional[bool] = M.Field(doc="Toggle emphasized text", default=None)
    specialStrings: Optional[bool] = M.Field(
        doc="Toggle conversion of special strings", default=None
    )
    propertyDrawers: Optional[bool] = M.Field(
        doc="Toggle inclusion of property drawers", default=None
    )
    statisticsCookies: Optional[bool] = M.Field(
        doc="Toggle inclusion of statistics cookies", default=None
    )
    todoText: Optional[bool] = M.Field(
        doc="Toggle inclusion of TODO keywords into exported text", default=None
    )
    smartQuotes: Optional[bool] = M.Field(doc="Toggle smart quotes", default=None)
    fixedWidth: Optional[bool] = M.Field(doc="Toggle fixed-width sections", default=None)
    timestamps: Optional[bool] = M.Field(
        doc="Toggle inclusion of time/date active/inactive stamps", default=None
    )
    preserveBreaks: Optional[bool] = M.Field(
        doc="Toggles whether to preserve line breaks", default=None
    )
    subSuperscripts: Optional[bool] = M.Field(
        doc="Toggle TeX-like syntax for sub- and superscripts", default=None
    )
    expandLinks: Optional[bool] = M.Field(
        doc="Toggle expansion of environment variables in file paths", default=None
    )
    creator: Optional[bool] = M.Field(
        doc="Toggle inclusion of creator information in the exported file", default=None
    )
    drawers: Optional[bool] = M.Field(doc="Toggle inclusion of drawers", default=None)
    date: Optional[bool] = M.Field(
        doc="Toggle inclusion of a date into exported file", default=None
    )
    entities: Optional[bool] = M.Field(doc="Toggle inclusion of entities", default=None)
    email: Optional[bool] = M.Field(
        doc="Toggle inclusion of the author's e-mail into exported file", default=None
    )
    sectionNumbers: Optional[bool] = M.Field(doc="Toggle section-numbers", default=None)
    planning: Optional[bool] = M.Field(
        doc="Toggle export of planning information", default=None
    )
    priority: Optional[bool] = M.Field(
        doc="Toggle inclusion of priority cookies", default=None
    )
    latex: Optional[bool] = M.Field(doc="Toggle LaTeX export", default=None)
    timestamp: Optional[bool] = M.Field(
        doc="Toggle inclusion of the creation time in the exported file", default=None
    )
    title: Optional[bool] = M.Field(doc="Toggle inclusion of title", default=None)
    tables: Optional[bool] = M.Field(doc="Toggle inclusion of tables", default=None)
    headlineLevels: Optional[Int32] = M.Field(
        doc="Set the number of headline levels for export", default=None
    )
    brokenLinks: BrokenLinks
    tagExport: TagExport
    taskFiltering: TaskFiltering
    archivedTrees: ArchivedTrees

    __variant__(DoExport, ExportFixed, field="tocExport", kind="TocExportKind")

    __config__(
        backend=dict(
            cpp=dict(
                org_groups=OrgTypeGroup.SHARED_TYPES,
                default_constructor=True,
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
    """Type of the subtree associated time periods"""

    class Kind(M.Enum):
        """Period kind"""

        Clocked: Annotated[
            int, EnFieldAnnotation(doc="Time period of the task execution.")
        ] = 0
        Closed: Annotated[int, EnFieldAnnotation(doc="Task marked as closed")] = 1
        Scheduled: Annotated[
            int,
            EnFieldAnnotation(
                doc="Date of task execution start plus it's estimated effort duration. If the latter one is missing then only a single time point is returned"
            ),
        ] = 2
        Titled: Annotated[
            int,
            EnFieldAnnotation(
                doc="Single point or time range used in title. Single point can also be a simple time, such as `12:20`"
            ),
        ] = 3
        Deadline: Annotated[
            int,
            EnFieldAnnotation(doc="Date of task completion. Must be a single time point"),
        ] = 4
        Created: Annotated[int, EnFieldAnnotation(doc="When the subtree was created")] = 5
        Repeated: Annotated[
            int, EnFieldAnnotation(doc="Last repeat time of the recurring tasks")
        ] = 6

    kind: Kind = M.Field(
        doc="Time period kind -- not associated with point/range distinction"
    )
    from_: H._T["UserTime"] = M.Field(doc="Clock start time")
    to: Optional[H._T["UserTime"]] = M.Field(
        doc="Optional end of the clock", default=None
    )

    __config__(
        backend=dict(
            cpp=dict(
                org_groups=OrgTypeGroup.SHARED_TYPES,
                field_names=dict(from_="from"),
            )
        ),
    )


class NamedProperty(M.Class):
    """Single subtree property"""

    class Nonblocking(M.Case):
        isBlocking: bool
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class ArchiveTime(M.Case):
        time: H._T["UserTime"]
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class ArchiveFile(M.Case):
        file: str
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class ArchiveOlpath(M.Case):
        path: SubtreePath
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class ArchiveTarget(M.Case):
        path: SubtreePath
        pattern: str
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class ArchiveCategory(M.Case):
        category: str
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class ArchiveTodo(M.Case):
        todo: str
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class Trigger(M.Case):
        pass

    class ExportLatexClass(M.Case):
        latexClass: str
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class CookieData(M.Case):
        """`:COOKIE_DATA:` for the subtree completion calculation"""

        isRecursive: bool
        source: SubtreeTodoSource
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class ExportLatexClassOptions(M.Case):
        options: List[str]
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class ExportLatexHeader(M.Case):
        header: str
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class ExportLatexCompiler(M.Case):
        compiler: str
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class Ordered(M.Case):
        isOrdered: bool
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class Effort(M.Case):
        hours: Int32 = 0
        minutes: Int32 = 0
        __config__(backend=dict(cpp=dict(default_constructor=True)))

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
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class Blocker(M.Case):
        blockers: List[str]
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class Unnumbered(M.Case):
        pass

    class Created(M.Case):
        time: TimeValue
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class RadioId(M.Case):
        """Radio target ID"""

        words: List[str]
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class HashtagDef(M.Case):
        """Definition of a hashtag entry"""

        hashtag: HashTagText
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class CustomArgs(M.Case):
        """Custom property with unparsed arguments"""

        name: str = M.Field(doc="Original name of the property")
        sub: Optional[str] = M.Field(doc="Property target specialization", default=None)
        attrs: AttrGroup = M.Field(doc="Property parameters")
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class CustomRaw(M.Case):
        """Custom property with unparsed arguments"""

        name: str = M.Field(doc="Original name of the property")
        value: str = M.Field(doc="Property value")
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class CustomId(M.Case):
        """Custom property with unparsed arguments"""

        value: str = M.Field(doc="Property value")
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class CustomSubtreeJson(M.Case):
        """Free-form JSON"""

        name: str
        value: Native._T["OrgJson"]
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class CustomSubtreeFlags(M.Case):
        """Free-form flags"""

        name: str
        value: AttrGroup
        __config__(backend=dict(cpp=dict(default_constructor=True)))

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
                org_groups=OrgTypeGroup.SHARED_TYPES,
                default_constructor=True,
                section_code=[
                    dict(
                        kind="public",
                        text="NamedProperty(Data const& data) : data(data) {}",
                    ),
                ],
            ),
        ),
    )

    def isMatching(self, kind: str, subKind: Optional[str] = None) -> bool:
        """Check if property matches specified kind and optional subkind. Built-in property checking is also done with this function -- 'created' etc."""
        ...

    def getName(self) -> str:
        """Get non-normalized name of the property (for built-in and user)"""
        ...

    def getSubKind(self) -> Optional[str]:
        """Get non-normalized sub-kind for the property."""
        ...


class OrgDiagnostics(M.Class):
    """Structure to store all diagnostics data collected by the parser, sem, eval etc."""

    class ParseTokenError(M.Case):
        """Parser errors for situations when failure can be attributed to specific token"""

        brief: str
        detail: str
        parserFunction: str
        parserLine: Int32
        tokenKind: Syntax._T["OrgTokenKind"]
        tokenText: str
        loc: Optional[P._T["SourceLoc"]] = None
        errName: str
        errCode: str
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class ParseError(M.Case):
        """General parser errors"""

        brief: str
        detail: str
        parserFunction: str
        parserLine: Int32
        errName: str
        errCode: str
        loc: Optional[P._T["SourceLoc"]] = None
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class IncludeError(M.Case):
        """Cannot convert parsed tree into"""

        brief: str
        targetPath: str
        workingFile: str
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class ConvertError(M.Case):
        """Cannot convert parsed tree into"""

        brief: str
        detail: str
        convertFunction: str
        convertLine: Int32
        convertFile: str
        errName: str
        errCode: str
        loc: Optional[P._T["SourceLoc"]] = None
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class InternalError(M.Case):
        """Internal implementation error: should not be visible to the end-user."""

        message: str
        function: str
        line: Int32
        file: str
        loc: Optional[P._T["SourceLoc"]] = None
        __config__(backend=dict(cpp=dict(default_constructor=True)))

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
                org_groups=OrgTypeGroup.SHARED_TYPES,
                default_constructor=True,
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
