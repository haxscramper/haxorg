from typing import Annotated, Optional
from typing import List as ListType

from hstd_py_unidata.model_dsl import (
    EnFieldAnnotation,
    Int32,
    Int64,
    __config__,
    __variant__,
    get_dsl_model,
)
from hstd_py_unidata.model_ir import ModelDef
from repo_py_orchestrate.codegen_config.codegen_type_groups import OrgTypeGroup

from .org_shared_model import M as Shared

M = get_dsl_model("org.sem.model")
H = get_dsl_model("hstd")
P = get_dsl_model("org.parse")


class Org(M.Class):
    """Root semantic AST node."""

    loc: Optional[P._T["SourceLoc"]] = None
    subnodes: ListType["Org"]

    __config__(
        backend=dict(
            cpp=dict(
                org_groups=OrgTypeGroup.AST_ROOT,
                ast_root=True,
                abstract=True,
            ),
        ),
    )


class NoNode(Org, M.Class):
    """No node"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class ErrorItem(Org, M.Class):
    diag: Shared._T["OrgDiagnostics"]

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class ErrorGroup(Org, M.Class):
    """Group of value conversion errors"""

    diagnostics: ListType[ErrorItem]

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Stmt(Org, M.Class):
    """Base class for all document-level entries. Note that some node kinds might also have inline entries (examples include links, source code blocks, call blocks)"""

    attached: ListType[Org]

    __config__(
        backend=dict(
            cpp=dict(
                org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS,
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

    def getAttached(self, kind: Optional[str] = None) -> ListType[Org]:
        """Return attached nodes of a specific kinds or all attached (if kind is nullopt)"""
        ...

    def getCaption(self) -> ListType[Org]: ...

    def getName(self) -> ListType[str]: ...

    @M.Method(backend=dict(cpp=dict(is_virtual=True)))
    def getAttrs(
        self,
        kind: Optional[str] = None,
    ) -> ListType[Shared._T["AttrValue"]]:
        """Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties."""
        ...

    @M.Method(backend=dict(cpp=dict(is_virtual=True)))
    def getFirstAttr(self, kind: str) -> Optional[Shared._T["AttrValue"]]:
        """Get the first parameter for the statement. In case there is a longer list of values matching a given kind, different node kinds can implement different priorities."""
        ...

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
    """Base class for all inline elements"""

    __config__(
        backend=dict(
            cpp=dict(abstract=True, org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)
        )
    )


class StmtList(Org, M.Class):
    """Zero or more statement nodes"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Empty(Org, M.Class):
    """Node without content"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Cmd(Stmt, M.Class):
    """Base class for block or line commands"""

    attrs: Shared._T["AttrGroup"] = M.Field(
        doc="Additional parameters aside from 'exporter',"
    )

    __config__(
        backend=dict(
            cpp=dict(abstract=True, org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)
        )
    )

    @M.Method(backend=dict(cpp=dict(is_virtual=True, is_override=True)))
    def getAttrs(
        self,
        key: Optional[str] = None,
    ) -> ListType[Shared._T["AttrValue"]]:
        """Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any."""
        ...

    @M.Method(backend=dict(cpp=dict(is_virtual=True, is_override=True)))
    def getFirstAttr(self, kind: str) -> Optional[Shared._T["AttrValue"]]:
        """Override of the base statement argument get, prioritizing the explicit command parameters"""
        ...


class Block(Cmd, M.Class):
    """Block command type"""

    __config__(
        backend=dict(
            cpp=dict(abstract=True, org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)
        )
    )


class LineCommand(Cmd, M.Class):
    """Line commands"""

    __config__(
        backend=dict(
            cpp=dict(abstract=True, org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)
        )
    )


class Attached(LineCommand, M.Class):
    """Line command that might get attached to some block element"""

    __config__(
        backend=dict(
            cpp=dict(abstract=True, org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)
        )
    )


class Leaf(Org, M.Class):
    """Final node"""

    text: str = M.Field(doc="Final leaf value", default="")

    __config__(
        backend=dict(
            cpp=dict(abstract=True, org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)
        )
    )

    @M.Method(backend=dict(cpp=dict(body="return text;")))
    def getText(self) -> str: ...


class CmdCaption(Attached, M.Class):
    """Caption annotation for any subsequent node"""

    text: "Paragraph" = M.Field(doc="Content description")

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class CmdCreator(Cmd, M.Class):
    """Creator of the document"""

    text: "Paragraph" = M.Field(doc="Creator name text")

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class CmdAuthor(Cmd, M.Class):
    """Author of the document"""

    text: "Paragraph" = M.Field(doc="Author name text")

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class CmdEmail(Cmd, M.Class):
    text: str

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class CmdLanguage(Cmd, M.Class):
    text: str

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class CmdColumns(Attached, M.Class):
    """Caption annotation for any subsequent node"""

    view: Shared._T["ColumnView"]

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class CmdName(Attached, M.Class):
    """Name identifier for the statement elements."""

    name: str

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class CmdCustomArgs(Cmd, M.Class):
    """Custom line command with list of parsed arguments"""

    name: str
    isAttached: bool = False

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class CmdCustomRaw(Stmt, M.Class):
    """Custom command with raw unparsed string value"""

    name: str
    isAttached: bool = False
    text: str

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class CmdCustomText(Stmt, M.Class):
    """Custom line command with text paragraph value"""

    name: str
    isAttached: bool = False
    text: "Paragraph"

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class CmdCall(Attached, M.Class):
    name: str = M.Field(doc="Code block call name")
    fileName: Optional[str] = M.Field(
        doc="Which file code block should come from", default=None
    )
    insideHeaderAttrs: Shared._T["AttrGroup"] = M.Field(
        doc="Additional parameters aside from 'exporter',"
    )
    callAttrs: Shared._T["AttrGroup"] = M.Field(
        doc="Additional parameters aside from 'exporter',"
    )
    endHeaderAttrs: Shared._T["AttrGroup"] = M.Field(
        doc="Additional parameters aside from 'exporter',"
    )
    result: ListType["BlockCodeEvalResult"] = M.Field(doc="Code evaluation results")

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class CmdTblfm(Cmd, M.Class):
    """Tblfm command type"""

    expr: Shared._T["Tblfm"]

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class BlockCenter(Block, M.Class):
    """Center nested content in export"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class BlockQuote(Block, M.Class):
    """Quotation block"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class BlockComment(Stmt, M.Class):
    """Comment block"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class BlockVerse(Block, M.Class):
    """Verse quotation block"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class BlockDynamicFallback(Block, M.Class):
    name: str

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class BlockExample(Block, M.Class):
    """Example block"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class BlockExport(Block, M.Class):
    """Direct export passthrough"""

    exporter: str
    content: str

    def getPlacement(self) -> Optional[str]:
        """Return value of the :placement attribute if present"""
        ...

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class BlockAdmonition(Block, M.Class):
    """Block of text with admonition tag: 'note',', 'warning','"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class BlockCodeEvalResult(Block, M.Class):
    """Parsed results of code block evaluation"""

    raw: ListType[Shared._T["OrgCodeEvalOutput"]]
    node: Org

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class BlockCode(Block, M.Class):
    """Base class for all code blocks"""

    lang: Optional[str] = M.Field(doc="Code block language name", default=None)
    result: ListType[BlockCodeEvalResult] = M.Field(doc="Code evaluation results")
    lines: ListType[Shared._T["BlockCodeLine"]] = M.Field(doc="Collected code lines")
    switches: Shared._T["AttrGroup"] = M.Field(
        doc="Dash-based switches for code block execution"
    )

    def getVariable(self, varname: str) -> Optional[Shared._T["AttrValue"]]: ...

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class HashTag(Inline, M.Class):
    text: Shared._T["HashTagText"]

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class InlineFootnote(Inline, M.Class):
    r"""Inline footnote definition

    \note in-text link to the footnotes are implemented using `Link` nodes
    """

    tag: str = M.Field(doc="Footnote text target name", default="")
    definition: Optional[Org] = M.Field(
        doc="Link to possibly resolved definition", default=None
    )

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class InlineExport(Inline, M.Class):
    """Inline export"""

    exporter: str
    content: str

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Time(Org, M.Class):
    """Single static or dynamic timestamp (active or inactive)"""

    class Repeat(M.Class):
        """Repetition information for static time"""

        class Mode(M.Enum):
            """Timestamp repetition mode"""

            None_: Annotated[
                int, EnFieldAnnotation(doc="Do not repeat task on completion")
            ] = 0
            Exact: Annotated[int, EnFieldAnnotation(doc="?")] = 1
            FirstMatch: Annotated[
                int,
                EnFieldAnnotation(doc="Repeat on the first matching day in the future"),
            ] = 2
            SameDay: Annotated[
                int,
                EnFieldAnnotation(doc="Repeat task on the same day next week/month/year"),
            ] = 3

        class Period(M.Enum):
            """Repetition period. Temporary placeholder for now, until I figure out what would be the proper way to represent whatever org can do ... which is to be determined as well"""

            Year: int = 0
            Month: int = 1
            Week: int = 2
            Day: int = 3
            Hour: int = 4
            Minute: int = 5

        mode: Mode = M.Field(doc="mode")
        period: Period = M.Field(doc="period")
        count: Int32 = M.Field(doc="count")

    class Static(M.Case):
        repeat: ListType["Time.Repeat"]
        warn: Optional["Time.Repeat"] = None
        time: H._T["UserTime"]
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    class Dynamic(M.Case):
        expr: Shared._T["LispCode"]
        __config__(backend=dict(cpp=dict(default_constructor=True)))

    isActive: bool = M.Field(doc="<active> vs [inactive]", default=False)

    __variant__(Static, Dynamic, field="time", kind="TimeKind")

    __config__(
        backend=dict(
            cpp=dict(
                org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS,
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
    """Range of time delimited by two points"""

    from_: Time = M.Field(doc="Starting time")
    to: Time = M.Field(doc="Finishing time")

    __config__(
        backend=dict(
            cpp=dict(
                org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS,
                field_names=dict(from_="from"),
            )
        ),
    )

    def getClockedTimeSeconds(self) -> Optional[Int64]: ...


class Macro(Org, M.Class):
    """Inline macro invocation"""

    name: str = M.Field(doc="Macro name", default="")
    attrs: Shared._T["AttrGroup"] = M.Field(
        doc="Additional parameters aside from 'exporter',"
    )

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Symbol(Org, M.Class):
    """Text symbol or symbol command"""

    class Param(M.Class):
        """Symbol parameters"""

        key: Optional[str] = M.Field(doc="Key -- for non-positional", default=None)
        value: str = M.Field(doc="Uninterpreted value")

    name: str = M.Field(doc="Name of the symbol")
    parameters: ListType[Param] = M.Field(doc="Optional list of parameters")
    positional: ListType[Org] = M.Field(doc="Positional parameters")

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Escaped(Leaf, M.Class):
    """Escaped text"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Newline(Leaf, M.Class):
    r"""\n newline"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Space(Leaf, M.Class):
    """' "space","""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Word(Leaf, M.Class):
    """word"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class AtMention(Leaf, M.Class):
    """`@mention`"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class RawText(Leaf, M.Class):
    pass

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Punctuation(Leaf, M.Class):
    pass

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Placeholder(Leaf, M.Class):
    pass

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class BigIdent(Leaf, M.Class):
    pass

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class TextTarget(Leaf, M.Class):
    """`<<target>>`"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class ErrorSkipToken(Leaf, M.Class):
    """Single token skipped during error recovery"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class ErrorSkipGroup(Org, M.Class):
    """Group of tokens skipped in search of the next synchronization point during parse fail recovery"""

    skipped: ListType[ErrorSkipToken]

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Markup(Org, M.Class):
    __config__(
        backend=dict(
            cpp=dict(abstract=True, org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)
        )
    )


class Bold(Markup, M.Class):
    pass

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Underline(Markup, M.Class):
    pass

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Monospace(Markup, M.Class):
    pass

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class MarkQuote(Markup, M.Class):
    pass

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Verbatim(Markup, M.Class):
    pass

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Italic(Markup, M.Class):
    pass

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Strike(Markup, M.Class):
    pass

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Par(Markup, M.Class):
    pass

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class RadioTarget(Org, M.Class):
    """`<<<target>>>`"""

    words: ListType[str]

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Latex(Org, M.Class):
    """Latex code body"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Link(Stmt, M.Class):
    description: Optional["Paragraph"] = None
    target: Shared._T["LinkTarget"]

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class SubtreeLog(Org, M.Class):
    """Single subtree log entry"""

    head: Shared._T["SubtreeLogHead"]
    desc: Optional[StmtList] = M.Field(
        doc="Optional description of the log entry", default=None
    )

    @M.Method(
        backend=dict(
            cpp=dict(
                is_const=False,
                args=dict(desc=dict(const_ref=False)),
            ),
        ),
    )
    def setDescription(self, desc: StmtList) -> None: ...

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Subtree(Org, M.Class):
    """Subtree"""

    level: Int32 = M.Field(doc="Subtree level", default=0)
    treeId: Optional[str] = M.Field(doc=":ID: property", default=None)
    todo: Optional[str] = M.Field(doc="Todo state of the tree", default=None)
    completion: Optional[Shared._T["SubtreeCompletion"]] = M.Field(
        doc="Task completion state", default=None
    )
    description: Optional["Paragraph"] = None
    tags: ListType[HashTag] = M.Field(doc="Trailing tags")
    title: "Paragraph" = M.Field(doc="Main title")
    logbook: ListType[SubtreeLog] = M.Field(doc="Associated subtree log")
    properties: ListType[Shared._T["NamedProperty"]] = M.Field(doc="Immediate properties")
    closed: Optional[Time] = M.Field(
        doc="When subtree was marked as closed", default=None
    )
    deadline: Optional[Time] = M.Field(doc="When is the deadline", default=None)
    scheduled: Optional[Time] = M.Field(doc="When the event is scheduled", default=None)
    isComment: bool = M.Field(
        doc="Subtree is annotated with the COMMENT keyword", default=False
    )
    isArchived: bool = M.Field(
        doc="Subtree is tagged with `:ARCHIVE:` tag", default=False
    )
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
        kinds: ListType[Shared._T["SubtreePeriod.Kind"]],
    ) -> ListType[Shared._T["SubtreePeriod"]]: ...

    def getProperties(
        self,
        kind: str,
        subkind: Optional[str] = None,
    ) -> ListType[Shared._T["NamedProperty"]]: ...

    def getProperty(
        self,
        kind: str,
        subkind: Optional[str] = None,
    ) -> Optional[Shared._T["NamedProperty"]]: ...

    @M.Method(backend=dict(cpp=dict(is_const=False)))
    def removeProperty(self, kind: str, subkind: Optional[str] = None) -> None:
        """Remove all instances of the property with matching kind/subkind from the property list"""
        ...

    @M.Method(backend=dict(cpp=dict(is_const=False)))
    def setProperty(self, value: Shared._T["NamedProperty"]) -> None:
        """Create or override existing property value in the subtree property list"""
        ...

    @M.Method(backend=dict(cpp=dict(is_const=False)))
    def setPropertyStrValue(
        self,
        value: str,
        kind: str,
        subkind: Optional[str] = None,
    ) -> None:
        """Assign a raw string literal to a property.

        This function will not do the conversion or parsing of the assigned value, so if it is a 'created' or some other property with a typed value, it will still remain as string until the file is written and then parsed back from scratch.
        """
        ...

    def getCleanTitle(self) -> str:
        """Get subtree title as a flat string, without markup nodes, but with all left strings"""
        ...

    def getTodoKeyword(self) -> Optional[str]: ...

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Cell(Cmd, M.Class):
    """Table cell"""

    isBlock: bool = M.Field(
        doc="Single-line pipe cell or `#+cell:` command", default=False
    )

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Row(Cmd, M.Class):
    """Table row"""

    cells: ListType[Cell] = M.Field(doc="List of cells on the row")
    isBlock: bool = M.Field(
        doc="Single-line pipe cell or `#+cell:` command", default=False
    )

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Table(Block, M.Class):
    """Table"""

    rows: ListType[Row] = M.Field(doc="List of rows for the table")
    isBlock: bool = M.Field(
        doc="Single-line pipe cell or `#+cell:` command", default=False
    )

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Paragraph(Stmt, M.Class):
    """Top-level or inline paragraph"""

    def isFootnoteDefinition(self) -> bool: ...

    def getFootnoteName(self) -> Optional[str]: ...

    def hasAdmonition(self) -> bool: ...

    def getAdmonitions(self) -> ListType[str]: ...

    def getAdmonitionNodes(self) -> ListType[BigIdent]: ...

    def hasTimestamp(self) -> bool: ...

    def getTimestamps(self) -> ListType[H._T["UserTime"]]: ...

    def getTimestampNodes(self) -> ListType[Time]: ...

    def hasLeadHashtags(self) -> bool: ...

    def getLeadHashtags(self) -> ListType[HashTag]: ...

    def getBody(self) -> ListType[Org]:
        """Return content of the paragraph, without prefix idents, hashtags, footnotes etc."""
        ...

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class ColonExample(Org, M.Class):
    """Shortened colon example block"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class CmdAttr(Attached, M.Class):
    """Caption annotation for any subsequent node"""

    target: str

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class CmdExport(Attached, M.Class):
    """Single line of passthrough code"""

    exporter: str
    content: str

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Call(Org, M.Class):
    """Inline, statement or block call"""

    name: str = M.Field(doc="Call target name")
    attrs: Shared._T["AttrGroup"] = M.Field(
        doc="Additional parameters aside from 'exporter'"
    )
    isCommand: bool = False

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class List(Stmt, M.Class):
    def getListAttrs(self, key: str) -> ListType[Shared._T["AttrValue"]]: ...

    def getListFormattingMode(self) -> Shared._T["ListFormattingMode"]: ...

    def isDescriptionList(self) -> bool:
        """List is marked as description if any list item has a header"""
        ...

    def isNumberedList(self) -> bool:
        """List is marked as numbered if any list item has bullet text set"""
        ...

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class ListItem(Org, M.Class):
    checkbox: Shared._T["CheckboxState"]
    header: Optional[Paragraph] = M.Field(
        doc="Description list item header", default=None
    )
    bullet: Optional[str] = M.Field(
        doc="Full text of the numbered list item, e.g. `a)`, `a.`", default=None
    )

    def isDescriptionItem(self) -> bool: ...

    def getCleanHeader(self) -> Optional[str]:
        """Return flat text for the description list header"""
        ...

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class DocumentOptions(Org, M.Class):
    initialVisibility: Shared._T["InitialSubtreeVisibility"]
    properties: ListType[Shared._T["NamedProperty"]]
    exportConfig: Shared._T["DocumentExportConfig"]
    fixedWidthSections: Optional[bool] = None
    linkVisibility: Optional[Shared._T["LinkVisibility"]] = None
    blockVisibility: Optional[Shared._T["BlockVisibility"]] = None
    startupIndented: Optional[bool] = None
    category: Optional[str] = None
    setupfile: Optional[str] = None
    maxSubtreeLevelExport: Optional[Int32] = None
    columns: Optional[Shared._T["ColumnView"]] = None
    todoKeywords: ListType[Shared._T["TodoKeyword"]]
    doneKeywords: ListType[Shared._T["TodoKeyword"]]

    __config__(
        backend=dict(
            cpp=dict(
                org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS,
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
    ) -> ListType[Shared._T["NamedProperty"]]: ...

    def getProperty(
        self,
        kind: str,
        subKind: Optional[str] = None,
    ) -> Optional[Shared._T["NamedProperty"]]: ...


class DocumentFragment(Org, M.Class):
    """Part of the document embedded in a larger file (e.g. in comments)"""

    baseLine: Int32 = 0
    baseCol: Int32 = 0

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class CriticMarkup(Org, M.Class):
    """https://fletcher.github.io/MultiMarkdown-6/syntax/critic.html"""

    class Kind(M.Enum):
        Deletion: int = 0
        Addition: int = 1
        Substitution: int = 2
        Highlighting: int = 3
        Comment: int = 4

    kind: Kind

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Document(Org, M.Class):
    title: Optional[Paragraph] = None
    author: Optional[Paragraph] = None
    creator: Optional[Paragraph] = None
    filetags: ListType[HashTag]
    email: Optional[RawText] = None
    language: ListType[str]
    options: DocumentOptions
    exportFileName: Optional[str] = None

    def getProperties(
        self,
        kind: str,
        subKind: Optional[str] = None,
    ) -> ListType[Shared._T["NamedProperty"]]: ...

    def getProperty(
        self,
        kind: str,
        subKind: Optional[str] = None,
    ) -> Optional[Shared._T["NamedProperty"]]: ...

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class FileTarget(Org, M.Class):
    path: str
    line: Optional[Int32] = None
    searchTarget: Optional[str] = None
    restrictToHeadlines: bool = False
    targetId: Optional[str] = None
    regexp: Optional[str] = None

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class TextSeparator(Org, M.Class):
    pass

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class DocumentGroup(Org, M.Class):
    pass

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class File(Org, M.Class):
    class Document(M.Case):
        pass

    class Attachment(M.Case):
        pass

    class Source(M.Case):
        pass

    relPath: str = M.Field(doc="Relative path from the root directory")
    absPath: str = M.Field(doc="Absolute resolved path to physical file")

    __variant__(Document, Attachment, Source, field="data", kind="Kind")

    __config__(
        backend=dict(
            cpp=dict(
                org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS,
                variants=dict(
                    data=dict(kind_getter="getFileKind"),
                ),
            ),
        ),
    )


class Directory(Org, M.Class):
    relPath: str = M.Field(
        doc="Relative path from the root directory, empty if this is the root directory"
    )
    absPath: str = M.Field(doc="Absolute resolved path to physical directory")

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class Symlink(Org, M.Class):
    isDirectory: bool
    absPath: str = M.Field(
        doc="Absolute path to the symlinked target directory. All relative paths under symlink node use its absolute path as a root."
    )

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS)))


class CmdInclude(Org, M.Class):
    class IncludeBase(M.Case):
        pass

    class Example(IncludeBase, M.Case):
        pass

    class Export(IncludeBase, M.Case):
        language: str = M.Field(doc="Source code language for export")

    class Custom(IncludeBase, M.Case):
        """Second positional argument in the include command can have any arbitrary value -- default src/export/example have additional properties, but user can provide anything else there."""

        blockName: str = M.Field(doc="Block name not covered by the default values")

    class Src(IncludeBase, M.Case):
        language: str = M.Field(doc="Source code language for code block")

    class OrgDocument(IncludeBase, M.Case):
        onlyContent: Optional[bool] = M.Field(
            doc="omits any planning lines or property drawers", default=None
        )
        subtreePath: Optional[Shared._T["SubtreePath"]] = M.Field(
            doc="Include first subtree matching path with `file.org::* tree`",
            default=None,
        )
        minLevel: Optional[Int32] = M.Field(
            doc="The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.",
            default=None,
        )
        customIdTarget: Optional[str] = M.Field(
            doc="Include target subtree content with `file.org::#custom`", default=None
        )

    path: str = M.Field(doc="Path to include")
    firstLine: Optional[Int32] = M.Field(
        doc="0-based index of the first line to include. NOTE: Org-mode syntax uses 1-based half-open range in the text",
        default=None,
    )
    lastLine: Optional[Int32] = M.Field(
        doc="0-based index of the last line to include", default=None
    )

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
                org_groups=OrgTypeGroup.SEM_NODE_DEFINITIONS,
                variants=dict(
                    data=dict(kind_getter="getIncludeKind"),
                ),
            ),
        ),
    )


def get_model() -> ModelDef:
    return M.finalize()
