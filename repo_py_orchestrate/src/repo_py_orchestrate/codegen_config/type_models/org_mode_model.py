from typing import List, Optional

from hstd_py_unidata.model_dsl import (
    Int32,
    Int64,
    __config__,
    __variant__,
    get_dsl_model,
)
from hstd_py_unidata.model_ir import ModelDef

from .org_shared_model import M as Shared

M = get_dsl_model("org.sem.model")
H = get_dsl_model("hstd")
P = get_dsl_model("org.parse")


class Org(M.Class):
    """Root semantic AST node."""

    loc: Optional[P._T["SourceLoc"]] = None
    subnodes: List["Org"]

    __config__(
        backend=dict(
            cpp=dict(
                ast_root=True,
                abstract=True,
            ),
        ),
    )


class NoNode(Org, M.Class):
    pass


class ErrorItem(Org, M.Class):
    diag: Shared._T["OrgDiagnostics"]


class ErrorGroup(Org, M.Class):
    diagnostics: List[ErrorItem]


class Stmt(Org, M.Class):
    """Base class for document-level entries."""

    attached: List[Org]

    __config__(
        backend=dict(
            cpp=dict(
                abstract=True,
                section_code=[
                    dict(
                        kind="public",
                        text=(
                            "Stmt(hstd::Vec<SemId<Org>> const& attached, "
                            "hstd::Vec<SemId<Org>> const& subnodes) "
                            ": Org(subnodes), attached(attached) {}"
                        ),
                    ),
                ],
            ),
        ),
    )

    def getAttached(self, kind: Optional[str] = None) -> List[Org]: ...

    def getCaption(self) -> List[Org]: ...

    def getName(self) -> List[str]: ...

    @M.Method(backend=dict(cpp=dict(is_virtual=True)))
    def getAttrs(
        self,
        kind: Optional[str] = None,
    ) -> List[Shared._T["AttrValue"]]: ...

    @M.Method(backend=dict(cpp=dict(is_virtual=True)))
    def getFirstAttr(self, kind: str) -> Optional[Shared._T["AttrValue"]]: ...

    def getFirstAttrString(self, kind: str) -> Optional[str]: ...

    def getFirstAttrInt(self, kind: str) -> Optional[Int32]: ...

    def getFirstAttrBool(self, kind: str) -> Optional[bool]: ...

    def getFirstAttrDouble(self, kind: str) -> Optional[float]: ...

    def getFirstAttrLisp(
        self,
        kind: str,
    ) -> Optional[Shared._T["AttrValue.LispValue"]]: ...

    def getFirstAttrKind(
        self,
        kind: str,
    ) -> Optional[Shared._T["AttrValue.Kind"]]: ...


class Inline(Org, M.Class):
    __config__(backend=dict(cpp=dict(abstract=True)))


class StmtList(Org, M.Class):
    pass


class Empty(Org, M.Class):
    pass


class Cmd(Stmt, M.Class):
    attrs: Shared._T["AttrGroup"]

    __config__(backend=dict(cpp=dict(abstract=True)))

    @M.Method(backend=dict(cpp=dict(is_virtual=True, is_override=True)))
    def getAttrs(
        self,
        key: Optional[str] = None,
    ) -> List[Shared._T["AttrValue"]]: ...

    @M.Method(backend=dict(cpp=dict(is_virtual=True, is_override=True)))
    def getFirstAttr(self, kind: str) -> Optional[Shared._T["AttrValue"]]: ...


class Block(Cmd, M.Class):
    __config__(backend=dict(cpp=dict(abstract=True)))


class LineCommand(Cmd, M.Class):
    __config__(backend=dict(cpp=dict(abstract=True)))


class Attached(LineCommand, M.Class):
    __config__(backend=dict(cpp=dict(abstract=True)))


class Leaf(Org, M.Class):
    text: str = ""

    __config__(backend=dict(cpp=dict(abstract=True)))

    @M.Method(backend=dict(cpp=dict(body="return text;")))
    def getText(self) -> str: ...


class CmdCaption(Attached, M.Class):
    text: "Paragraph"


class CmdCreator(Cmd, M.Class):
    text: "Paragraph"


class CmdAuthor(Cmd, M.Class):
    text: "Paragraph"


class CmdEmail(Cmd, M.Class):
    text: str


class CmdLanguage(Cmd, M.Class):
    text: str


class CmdColumns(Attached, M.Class):
    view: Shared._T["ColumnView"]


class CmdName(Attached, M.Class):
    name: str


class CmdCustomArgs(Cmd, M.Class):
    name: str
    isAttached: bool = False


class CmdCustomRaw(Stmt, M.Class):
    name: str
    isAttached: bool = False
    text: str


class CmdCustomText(Stmt, M.Class):
    name: str
    isAttached: bool = False
    text: "Paragraph"


class CmdCall(Attached, M.Class):
    name: str
    fileName: Optional[str] = None
    insideHeaderAttrs: Shared._T["AttrGroup"]
    callAttrs: Shared._T["AttrGroup"]
    endHeaderAttrs: Shared._T["AttrGroup"]
    result: List["BlockCodeEvalResult"]


class CmdTblfm(Cmd, M.Class):
    expr: Shared._T["Tblfm"]


class BlockCenter(Block, M.Class):
    pass


class BlockQuote(Block, M.Class):
    pass


class BlockComment(Stmt, M.Class):
    pass


class BlockVerse(Block, M.Class):
    pass


class BlockDynamicFallback(Block, M.Class):
    name: str


class BlockExample(Block, M.Class):
    pass


class BlockExport(Block, M.Class):
    exporter: str
    content: str

    def getPlacement(self) -> Optional[str]: ...


class BlockAdmonition(Block, M.Class):
    pass


class BlockCodeEvalResult(Block, M.Class):
    raw: List[Shared._T["OrgCodeEvalOutput"]]
    node: Org


class BlockCode(Block, M.Class):
    lang: Optional[str] = None
    result: List[BlockCodeEvalResult]
    lines: List[Shared._T["BlockCodeLine"]]
    switches: Shared._T["AttrGroup"]

    def getVariable(self, varname: str) -> Optional[Shared._T["AttrValue"]]: ...


class HashTag(Inline, M.Class):
    text: Shared._T["HashTagText"]


class InlineFootnote(Inline, M.Class):
    tag: str = ""
    definition: Optional[Org] = None


class InlineExport(Inline, M.Class):
    exporter: str
    content: str


class Time(Org, M.Class):
    class Repeat(M.Class):
        class Mode(M.Enum):
            None_: int = 0
            Exact: int = 1
            FirstMatch: int = 2
            SameDay: int = 3

        class Period(M.Enum):
            Year: int = 0
            Month: int = 1
            Week: int = 2
            Day: int = 3
            Hour: int = 4
            Minute: int = 5

        mode: Mode
        period: Period
        count: Int32

    class Static(M.Case):
        repeat: List["Time.Repeat"]
        warn: Optional["Time.Repeat"] = None
        time: H._T["UserTime"]

    class Dynamic(M.Case):
        expr: Shared._T["LispCode"]

    isActive: bool = False

    __variant__(Static, Dynamic, field="time", kind="TimeKind")

    __config__(
        backend=dict(
            cpp=dict(
                variants=dict(
                    time=dict(
                        variant_name="TimeVariant",
                        kind_getter="getTimeKind",
                    ),
                ),
            ),
        ),
    )

    def getYear(self) -> Optional[Int32]: ...

    def getMonth(self) -> Optional[Int32]: ...

    def getDay(self) -> Optional[Int32]: ...

    def getHour(self) -> Optional[Int32]: ...

    def getMinute(self) -> Optional[Int32]: ...

    def getSecond(self) -> Optional[Int32]: ...

    def getStaticTime(self) -> H._T["UserTime"]: ...


class TimeRange(Org, M.Class):
    from_: Time
    to: Time

    __config__(
        backend=dict(cpp=dict(field_names=dict(from_="from"))),
    )

    def getClockedTimeSeconds(self) -> Optional[Int64]: ...


class Macro(Org, M.Class):
    name: str = ""
    attrs: Shared._T["AttrGroup"]


class Symbol(Org, M.Class):
    class Param(M.Class):
        key: Optional[str] = None
        value: str

    name: str
    parameters: List[Param]
    positional: List[Org]


class Escaped(Leaf, M.Class):
    pass


class Newline(Leaf, M.Class):
    pass


class Space(Leaf, M.Class):
    pass


class Word(Leaf, M.Class):
    pass


class AtMention(Leaf, M.Class):
    pass


class RawText(Leaf, M.Class):
    pass


class Punctuation(Leaf, M.Class):
    pass


class Placeholder(Leaf, M.Class):
    pass


class BigIdent(Leaf, M.Class):
    pass


class TextTarget(Leaf, M.Class):
    pass


class ErrorSkipToken(Leaf, M.Class):
    pass


class ErrorSkipGroup(Org, M.Class):
    skipped: List[ErrorSkipToken]


class Markup(Org, M.Class):
    __config__(backend=dict(cpp=dict(abstract=True)))


class Bold(Markup, M.Class):
    pass


class Underline(Markup, M.Class):
    pass


class Monospace(Markup, M.Class):
    pass


class MarkQuote(Markup, M.Class):
    pass


class Verbatim(Markup, M.Class):
    pass


class Italic(Markup, M.Class):
    pass


class Strike(Markup, M.Class):
    pass


class Par(Markup, M.Class):
    pass


class RadioTarget(Org, M.Class):
    words: List[str]


class Latex(Org, M.Class):
    pass


class Link(Stmt, M.Class):
    description: Optional["Paragraph"] = None
    target: Shared._T["LinkTarget"]


class SubtreeLog(Org, M.Class):
    head: Shared._T["SubtreeLogHead"]
    desc: Optional[StmtList] = None

    @M.Method(
        backend=dict(
            cpp=dict(
                is_const=False,
                args=dict(desc=dict(const_ref=False)),
            ),
        ),
    )
    def setDescription(self, desc: StmtList) -> None: ...


class Subtree(Org, M.Class):
    level: Int32 = 0
    treeId: Optional[str] = None
    todo: Optional[str] = None
    completion: Optional[Shared._T["SubtreeCompletion"]] = None
    description: Optional["Paragraph"] = None
    tags: List[HashTag]
    title: "Paragraph"
    logbook: List[SubtreeLog]
    properties: List[Shared._T["NamedProperty"]]
    closed: Optional[Time] = None
    deadline: Optional[Time] = None
    scheduled: Optional[Time] = None
    isComment: bool = False
    isArchived: bool = False
    priority: Optional[str] = None

    @M.Method(
        backend=dict(
            cpp=dict(
                args=dict(
                    kinds=dict(
                        type="hstd::IntSet",
                        const_ref=False,
                    ),
                ),
            ),
        ),
    )
    def getTimePeriods(
        self,
        kinds: List[Shared._T["SubtreePeriod.Kind"]],
    ) -> List[Shared._T["SubtreePeriod"]]: ...

    def getProperties(
        self,
        kind: str,
        subkind: Optional[str] = None,
    ) -> List[Shared._T["NamedProperty"]]: ...

    def getProperty(
        self,
        kind: str,
        subkind: Optional[str] = None,
    ) -> Optional[Shared._T["NamedProperty"]]: ...

    @M.Method(backend=dict(cpp=dict(is_const=False)))
    def removeProperty(self, kind: str, subkind: Optional[str] = None) -> None: ...

    @M.Method(backend=dict(cpp=dict(is_const=False)))
    def setProperty(self, value: Shared._T["NamedProperty"]) -> None: ...

    @M.Method(backend=dict(cpp=dict(is_const=False)))
    def setPropertyStrValue(
        self,
        value: str,
        kind: str,
        subkind: Optional[str] = None,
    ) -> None: ...

    def getCleanTitle(self) -> str: ...

    def getTodoKeyword(self) -> Optional[str]: ...


class Cell(Cmd, M.Class):
    isBlock: bool = False


class Row(Cmd, M.Class):
    cells: List[Cell]
    isBlock: bool = False


class Table(Block, M.Class):
    rows: List[Row]
    isBlock: bool = False


class Paragraph(Stmt, M.Class):
    def isFootnoteDefinition(self) -> bool: ...

    def getFootnoteName(self) -> Optional[str]: ...

    def hasAdmonition(self) -> bool: ...

    def getAdmonitions(self) -> List[str]: ...

    def getAdmonitionNodes(self) -> List[BigIdent]: ...

    def hasTimestamp(self) -> bool: ...

    def getTimestamps(self) -> List[H._T["UserTime"]]: ...

    def getTimestampNodes(self) -> List[Time]: ...

    def hasLeadHashtags(self) -> bool: ...

    def getLeadHashtags(self) -> List[HashTag]: ...

    def getBody(self) -> List[Org]: ...


class ColonExample(Org, M.Class):
    pass


class CmdAttr(Attached, M.Class):
    target: str


class CmdExport(Attached, M.Class):
    exporter: str
    content: str


class Call(Org, M.Class):
    name: str
    attrs: Shared._T["AttrGroup"]
    isCommand: bool = False


class List(Stmt, M.Class):
    def getListAttrs(self, key: str) -> List[Shared._T["AttrValue"]]: ...

    def getListFormattingMode(self) -> Shared._T["ListFormattingMode"]: ...

    def isDescriptionList(self) -> bool: ...

    def isNumberedList(self) -> bool: ...


class ListItem(Org, M.Class):
    checkbox: Shared._T["CheckboxState"]
    header: Optional[Paragraph] = None
    bullet: Optional[str] = None

    def isDescriptionItem(self) -> bool: ...

    def getCleanHeader(self) -> Optional[str]: ...


class DocumentOptions(Org, M.Class):
    initialVisibility: Shared._T["InitialSubtreeVisibility"]
    properties: List[Shared._T["NamedProperty"]]
    exportConfig: Shared._T["DocumentExportConfig"]
    fixedWidthSections: Optional[bool] = None
    linkVisibility: Optional[Shared._T["LinkVisibility"]] = None
    blockVisibility: Optional[Shared._T["BlockVisibility"]] = None
    startupIndented: Optional[bool] = None
    category: Optional[str] = None
    setupfile: Optional[str] = None
    maxSubtreeLevelExport: Optional[Int32] = None
    columns: Optional[Shared._T["ColumnView"]] = None
    todoKeywords: List[Shared._T["TodoKeyword"]]
    doneKeywords: List[Shared._T["TodoKeyword"]]

    __config__(
        backend=dict(
            cpp=dict(
                field_defaults=dict(
                    initialVisibility=(
                        "org::sem::InitialSubtreeVisibility::ShowEverything"
                    ),
                ),
            ),
        ),
    )

    def getProperties(
        self,
        kind: str,
        subKind: Optional[str] = None,
    ) -> List[Shared._T["NamedProperty"]]: ...

    def getProperty(
        self,
        kind: str,
        subKind: Optional[str] = None,
    ) -> Optional[Shared._T["NamedProperty"]]: ...


class DocumentFragment(Org, M.Class):
    baseLine: Int32 = 0
    baseCol: Int32 = 0


class CriticMarkup(Org, M.Class):
    class Kind(M.Enum):
        Deletion: int = 0
        Addition: int = 1
        Substitution: int = 2
        Highlighting: int = 3
        Comment: int = 4

    kind: Kind


class Document(Org, M.Class):
    title: Optional[Paragraph] = None
    author: Optional[Paragraph] = None
    creator: Optional[Paragraph] = None
    filetags: List[HashTag]
    email: Optional[RawText] = None
    language: List[str]
    options: DocumentOptions
    exportFileName: Optional[str] = None

    def getProperties(
        self,
        kind: str,
        subKind: Optional[str] = None,
    ) -> List[Shared._T["NamedProperty"]]: ...

    def getProperty(
        self,
        kind: str,
        subKind: Optional[str] = None,
    ) -> Optional[Shared._T["NamedProperty"]]: ...


class FileTarget(Org, M.Class):
    path: str
    line: Optional[Int32] = None
    searchTarget: Optional[str] = None
    restrictToHeadlines: bool = False
    targetId: Optional[str] = None
    regexp: Optional[str] = None


class TextSeparator(Org, M.Class):
    pass


class DocumentGroup(Org, M.Class):
    pass


class File(Org, M.Class):
    class Document(M.Case):
        pass

    class Attachment(M.Case):
        pass

    class Source(M.Case):
        pass

    relPath: str
    absPath: str

    __variant__(Document, Attachment, Source, field="data", kind="Kind")

    __config__(
        backend=dict(
            cpp=dict(
                variants=dict(
                    data=dict(kind_getter="getFileKind"),
                ),
            ),
        ),
    )


class Directory(Org, M.Class):
    relPath: str
    absPath: str


class Symlink(Org, M.Class):
    isDirectory: bool
    absPath: str


class CmdInclude(Org, M.Class):
    class IncludeBase(M.Class):
        pass

    class Example(IncludeBase, M.Case):
        pass

    class Export(IncludeBase, M.Case):
        language: str

    class Custom(IncludeBase, M.Case):
        blockName: str

    class Src(IncludeBase, M.Case):
        language: str

    class OrgDocument(IncludeBase, M.Case):
        onlyContent: Optional[bool] = None
        subtreePath: Optional[Shared._T["SubtreePath"]] = None
        minLevel: Optional[Int32] = None
        customIdTarget: Optional[str] = None

    path: str
    firstLine: Optional[Int32] = None
    lastLine: Optional[Int32] = None

    __variant__(
        Example,
        Export,
        Custom,
        Src,
        OrgDocument,
        field="data",
        kind="Kind",
    )

    __config__(
        backend=dict(
            cpp=dict(
                variants=dict(
                    data=dict(kind_getter="getIncludeKind"),
                ),
            ),
        ),
    )


def get_model() -> ModelDef:
    return M.finalize()
