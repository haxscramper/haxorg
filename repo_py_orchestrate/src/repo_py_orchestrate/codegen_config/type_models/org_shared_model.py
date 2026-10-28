import enum
from typing import Annotated, Dict, List, Optional

from hstd_py_unidata.model_dsl import (
    EnFieldAnnotation,
    Float32,
    Int32,
    __config__,
    __variant__,
    get_dsl_model,
)
from hstd_py_unidata.model_ir import ModelDef, TypeAnnotation
from repo_py_orchestrate.codegen_config.codegen_type_groups import OrgTypeGroup

M = get_dsl_model("org.sem.shared")
H = get_dsl_model("hstd")
P = get_dsl_model("org.parse")
Native = get_dsl_model("org.sem.native")


class OrgSpecName(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    Unnamed: int = enum.auto()
    Result: int = enum.auto()
    Year: int = enum.auto()
    Day: int = enum.auto()
    Clock: int = enum.auto()
    Repeater: int = enum.auto()
    Warn: int = enum.auto()
    Zone: int = enum.auto()
    Link: int = enum.auto()
    Tags: int = enum.auto()
    Tag: int = enum.auto()
    State: int = enum.auto()
    Protocol: int = enum.auto()
    Desc: int = enum.auto()
    Times: int = enum.auto()
    Drawer: int = enum.auto()
    Args: int = enum.auto()
    Name: int = enum.auto()
    Definition: int = enum.auto()
    Body: int = enum.auto()
    HeaderArgs: int = enum.auto()
    File: int = enum.auto()
    Kind: int = enum.auto()
    Lang: int = enum.auto()
    Prefix: int = enum.auto()
    Text: int = enum.auto()
    Todo: int = enum.auto()
    Importance: int = enum.auto()
    Title: int = enum.auto()
    Completion: int = enum.auto()
    Head: int = enum.auto()
    Subnodes: int = enum.auto()
    Properties: int = enum.auto()
    Logbook: int = enum.auto()
    Description: int = enum.auto()
    Logs: int = enum.auto()
    Newstate: int = enum.auto()
    Oldstate: int = enum.auto()
    Time: int = enum.auto()
    From: int = enum.auto()
    EndArgs: int = enum.auto()
    Flags: int = enum.auto()
    Value: int = enum.auto()
    Assoc: int = enum.auto()
    Main: int = enum.auto()
    Hash: int = enum.auto()
    Bullet: int = enum.auto()
    Counter: int = enum.auto()
    Checkbox: int = enum.auto()
    Header: int = enum.auto()
    To: int = enum.auto()
    Diff: int = enum.auto()
    Property: int = enum.auto()
    Subname: int = enum.auto()
    Values: int = enum.auto()
    Cells: int = enum.auto()
    Rows: int = enum.auto()
    Lines: int = enum.auto()
    Chunks: int = enum.auto()


class OrgNodeKind(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    None_: Annotated[
        int, EnFieldAnnotation(doc="Default valye for node - invalid state")
    ] = enum.auto()
    Document: Annotated[
        int,
        EnFieldAnnotation(
            doc="Toplevel part of the ast, not created by parser, and only used in `semorg` stage"
        ),
    ] = enum.auto()
    Empty: Annotated[
        int,
        EnFieldAnnotation(doc="Empty node - valid state that does not contain any value"),
    ] = enum.auto()
    InlineStmtList: int = enum.auto()
    StmtList: Annotated[
        int,
        EnFieldAnnotation(
            doc="List of statements, possibly recursive. Used as toplevel part of the document, in recursive parsing of subtrees, or as regular list, in cases where multiple subnodes have to be grouped together."
        ),
    ] = enum.auto()
    Checkbox: Annotated[
        int, EnFieldAnnotation(doc="Single checkbox item like `[X]` or `[-]`")
    ] = enum.auto()
    List: int = enum.auto()
    Bullet: Annotated[int, EnFieldAnnotation(doc="List item prefix")] = enum.auto()
    ListItem: int = enum.auto()
    ListTag: Annotated[
        int,
        EnFieldAnnotation(
            doc="Auxilliary wrapper for the paragraph placed at the start of the description list."
        ),
    ] = enum.auto()
    Counter: int = enum.auto()
    File: int = enum.auto()
    ColonExample: Annotated[int, EnFieldAnnotation(doc="Colon example block")] = (
        enum.auto()
    )
    TextSeparator: Annotated[
        int, EnFieldAnnotation(doc="Long horizontal line `----`")
    ] = enum.auto()
    Paragraph: Annotated[
        int,
        EnFieldAnnotation(
            doc="Single 'paragraph' of text. Used as generic container for any place in AST where unordered sentence might be encountered (e.g. caption, link description) - not limited to actual paragraph"
        ),
    ] = enum.auto()
    TableRow: Annotated[int, EnFieldAnnotation(doc="Horizontal table row")] = enum.auto()
    TableCell: Annotated[
        int,
        EnFieldAnnotation(
            doc="Single cell in row. Might contain anyting, including other tables, simple text paragraph etc."
        ),
    ] = enum.auto()
    Table: Annotated[int, EnFieldAnnotation(doc="Org-mode table")] = enum.auto()
    InlineFootnote: Annotated[
        int,
        EnFieldAnnotation(
            doc="Inline footnote with text placed directly in the node body."
        ),
    ] = enum.auto()
    Footnote: Annotated[
        int,
        EnFieldAnnotation(
            doc="Footnote entry. Just as regular links - internal content is not parsed, and instead just cut out verbatim into target AST node."
        ),
    ] = enum.auto()
    Cmd: Annotated[
        int,
        EnFieldAnnotation(
            doc="Undefined single-line command -- most likely custom user-provided oe"
        ),
    ] = enum.auto()
    Attrs: Annotated[int, EnFieldAnnotation(doc="Arguments for the command block")] = (
        enum.auto()
    )
    AttrValue: Annotated[int, EnFieldAnnotation(doc=":key name=value syntax")] = (
        enum.auto()
    )
    LispExpr: Annotated[
        int, EnFieldAnnotation(doc="S-expression as an attribute value value")
    ] = enum.auto()
    LispList: Annotated[int, EnFieldAnnotation(doc="`(a b c)` without quoting")] = (
        enum.auto()
    )
    LispVector: Annotated[int, EnFieldAnnotation(doc="[1 2 3 4]` without quoting")] = (
        enum.auto()
    )
    LispQuoted: Annotated[
        int, EnFieldAnnotation(doc="Extra wrapping node for quoted elements")
    ] = enum.auto()
    CmdTitle: Annotated[
        int, EnFieldAnnotation(doc="`#+title:` - full document title")
    ] = enum.auto()
    CmdAuthor: Annotated[int, EnFieldAnnotation(doc="`#+author:` Document author")] = (
        enum.auto()
    )
    CmdCreator: Annotated[int, EnFieldAnnotation(doc="`#+creator:` Document creator")] = (
        29
    )
    CmdInclude: Annotated[
        int,
        EnFieldAnnotation(
            doc="`#+include:` - include other org-mode document (or subsection of it), source code or backend-specific chunk."
        ),
    ] = enum.auto()
    CmdLanguage: Annotated[int, EnFieldAnnotation(doc="`#+language:`")] = enum.auto()
    CmdEmail: Annotated[int, EnFieldAnnotation(doc="`#+email:`")] = enum.auto()
    CmdAttr: Annotated[
        int, EnFieldAnnotation(doc="`#+attr_html:`, `#+attr_image` etc.")
    ] = enum.auto()
    CmdStartup: Annotated[int, EnFieldAnnotation(doc="`#+startup:`")] = enum.auto()
    CmdName: Annotated[
        int, EnFieldAnnotation(doc="`#+name:` - name of the associated entry")
    ] = enum.auto()
    CmdCustomTextCommand: Annotated[
        int, EnFieldAnnotation(doc="Line command with parsed text value")
    ] = enum.auto()
    CmdCustomArgsCommand: Annotated[
        int, EnFieldAnnotation(doc="Line command with parsed argument list")
    ] = enum.auto()
    CmdCustomRawCommand: Annotated[
        int, EnFieldAnnotation(doc="Line command with raw text argument")
    ] = enum.auto()
    CmdResults: Annotated[
        int, EnFieldAnnotation(doc="`#+results:` - source code block evaluation results")
    ] = enum.auto()
    CmdHeader: Annotated[
        int,
        EnFieldAnnotation(
            doc="`#+header:` - extended list of parameters passed to associated block"
        ),
    ] = enum.auto()
    CmdOptions: Annotated[
        int, EnFieldAnnotation(doc="`#+options:` - document-wide formatting options")
    ] = enum.auto()
    CmdTblfm: int = enum.auto()
    CmdCaption: Annotated[int, EnFieldAnnotation(doc="`#+caption:` command")] = (
        enum.auto()
    )
    CmdResult: Annotated[int, EnFieldAnnotation(doc="Command evaluation result")] = (
        enum.auto()
    )
    CmdCallCode: Annotated[
        int, EnFieldAnnotation(doc="Call to named source code block.")
    ] = enum.auto()
    CmdFlag: Annotated[
        int,
        EnFieldAnnotation(
            doc="Flag for source code block. For example `-n`, which is used to to make source code block export with lines"
        ),
    ] = enum.auto()
    CmdLatexClass: int = enum.auto()
    CmdLatexHeader: int = enum.auto()
    CmdLatexCompiler: int = enum.auto()
    CmdLatexClassOptions: int = enum.auto()
    CmdHtmlHead: int = enum.auto()
    CmdColumns: Annotated[
        int,
        EnFieldAnnotation(
            doc="`#+columns:` line command for specifying formatting of the org-mode clock table visualization on per-file basis."
        ),
    ] = enum.auto()
    CmdPropertyArgs: Annotated[int, EnFieldAnnotation(doc="`#+property:` command")] = (
        enum.auto()
    )
    CmdPropertyText: Annotated[int, EnFieldAnnotation(doc="`#+property:` command")] = (
        enum.auto()
    )
    CmdPropertyRaw: Annotated[int, EnFieldAnnotation(doc="`#+property:` command")] = (
        enum.auto()
    )
    CmdFiletags: Annotated[int, EnFieldAnnotation(doc="`#+filetags:` line command")] = (
        enum.auto()
    )
    CmdKeywords: int = enum.auto()
    BlockVerbatimMultiline: Annotated[
        int,
        EnFieldAnnotation(
            doc="Verbatim mulitiline block that *might* be a part of `orgMultilineCommand` (in case of `#+begin-src`), but not necessarily. Can also be a part of =quote= and =example= multiline blocks."
        ),
    ] = enum.auto()
    CodeLine: Annotated[int, EnFieldAnnotation(doc="Single line of source code")] = (
        enum.auto()
    )
    CodeText: Annotated[int, EnFieldAnnotation(doc="Block of source code text")] = (
        enum.auto()
    )
    CodeTangle: Annotated[
        int, EnFieldAnnotation(doc="Single tangle target in the code block")
    ] = enum.auto()
    CodeCallout: Annotated[
        int, EnFieldAnnotation(doc="`(refs:` callout in the source code")
    ] = enum.auto()
    BlockCode: int = enum.auto()
    BlockQuote: Annotated[
        int, EnFieldAnnotation(doc="`#+begin_quote:` block in code")
    ] = enum.auto()
    BlockComment: Annotated[
        int, EnFieldAnnotation(doc="`#+begin_comment:` block in code")
    ] = enum.auto()
    BlockCenter: int = enum.auto()
    BlockVerse: int = enum.auto()
    BlockExample: Annotated[int, EnFieldAnnotation(doc="Verbatim example text block")] = (
        68
    )
    BlockExport: int = enum.auto()
    BlockDetails: Annotated[int, EnFieldAnnotation(doc="`#+begin_details`  section")] = (
        enum.auto()
    )
    BlockSummary: Annotated[int, EnFieldAnnotation(doc="`#+begin_summary` section")] = (
        enum.auto()
    )
    BlockDynamicFallback: Annotated[
        int, EnFieldAnnotation(doc="#+begin: <name> section")
    ] = enum.auto()
    BlockCustomText: Annotated[
        int, EnFieldAnnotation(doc="#+begin_<any> section for text blocks")
    ] = enum.auto()
    BlockCustomRaw: Annotated[
        int, EnFieldAnnotation(doc="#+begin_<any> section for raw content blocks")
    ] = enum.auto()
    BigIdent: Annotated[
        int, EnFieldAnnotation(doc="full-uppsercase identifier such as `MUST` or `TODO`")
    ] = enum.auto()
    Bold: Annotated[
        int,
        EnFieldAnnotation(
            doc='Region of text with formatting, which contains standalone words -\n     can itself contain subnodes, which allows to represent nested\n     formatting regions, such as `*bold /italic/*` text. Particular type\n     of identifier is stored in string form in `str` field for `OrgNode`\n     -- bold is represented as `"*"`, italic as `/` and so on. In case\n     of explicit open/close pairs only opening one is stored.\n\n     NOTE: when structured sentences are enabled, regular punctuation\n     elements like `some text (notes)` are also represented as `Word,\n     Word, Markup(str: "(", [Word])` - e.g. structure is not fully flat.'
        ),
    ] = enum.auto()
    ErrorInfoToken: Annotated[
        int,
        EnFieldAnnotation(doc="Error leaf node inserted into the parse tree on failure"),
    ] = enum.auto()
    ErrorSkipGroup: Annotated[
        int,
        EnFieldAnnotation(
            doc="Parent node for one or more tokens skipped during error recovery"
        ),
    ] = enum.auto()
    ErrorSkipToken: Annotated[
        int,
        EnFieldAnnotation(
            doc="Single token node skipped while the parser searched for recovery point"
        ),
    ] = enum.auto()
    Italic: int = enum.auto()
    Verbatim: int = enum.auto()
    Backtick: int = enum.auto()
    Underline: int = enum.auto()
    Strike: int = enum.auto()
    Quote: int = enum.auto()
    Angle: int = enum.auto()
    Monospace: int = enum.auto()
    Par: int = enum.auto()
    CriticMarkStructure: int = enum.auto()
    InlineMath: Annotated[
        int,
        EnFieldAnnotation(
            doc="Inline latex math. Contains latex math body - either from `$dollar-wrapped$` or `\\(paren-wrapped\\)` inline text."
        ),
    ] = enum.auto()
    DisplayMath: Annotated[
        int,
        EnFieldAnnotation(
            doc="Inline display latex math from `$$double-dollar$$` or `\\[bracket-wrapped\\]` code."
        ),
    ] = enum.auto()
    Space: Annotated[
        int, EnFieldAnnotation(doc="Space or tab character in regular text")
    ] = enum.auto()
    Punctuation: int = enum.auto()
    Colon: int = enum.auto()
    Word: Annotated[
        int,
        EnFieldAnnotation(
            doc="Regular word - technically not different from `orgIdent`, but defined separately to disiguish between places where special syntax is required and free-form text."
        ),
    ] = enum.auto()
    Escaped: Annotated[
        int, EnFieldAnnotation(doc="Escaped formatting character in the text")
    ] = enum.auto()
    Newline: int = enum.auto()
    RawLink: Annotated[
        int, EnFieldAnnotation(doc="Raw unwrapped link that was pasted in text")
    ] = enum.auto()
    Link: Annotated[
        int,
        EnFieldAnnotation(
            doc="External or internal link. Consists of one or two elements - target\n     (url, file location etc.) and description (`orgParagraph` of text).\n     Description might be empty, and represented as empty node in this\n     case. For external links particular formatting of the address is\n     not handled by parser and instead contains raw string from input\n     text."
        ),
    ] = enum.auto()
    Macro: Annotated[
        int,
        EnFieldAnnotation(
            doc="Org-mode macro replacement - during export each macro is expanded\n     and evaluated according to it's environment. Body of the macro is\n     not parsed fully during org-mode evaluation, but is checked for\n     correct parenthesis balance (as macro might contain elisp code)"
        ),
    ] = enum.auto()
    Symbol: Annotated[
        int,
        EnFieldAnnotation(
            doc="Special symbol that should be exported differently to various backends - greek letters (`\alpha`), mathematical notations and so on."
        ),
    ] = enum.auto()
    StaticActiveTime: int = enum.auto()
    StaticInactiveTime: int = enum.auto()
    DynamicActiveTime: int = enum.auto()
    DiaryTime: int = enum.auto()
    DynamicInactiveTime: Annotated[
        int,
        EnFieldAnnotation(
            doc="Single date and time entry (active or inactive),, possibly with repeater interval. Is not parsed directly, and instead contains `orgRawText` that can be parsed later"
        ),
    ] = enum.auto()
    TimeRange: Annotated[
        int,
        EnFieldAnnotation(doc="Date and time range format - two `orgDateTime` entries"),
    ] = enum.auto()
    SimpleTime: Annotated[
        int,
        EnFieldAnnotation(
            doc="Result of the time range evaluation or trailing annotation a subtree"
        ),
    ] = enum.auto()
    HashTag: int = enum.auto()
    MetaSymbol: Annotated[
        int, EnFieldAnnotation(doc="`\\sym{}` with explicit arguments")
    ] = enum.auto()
    AtMention: Annotated[int, EnFieldAnnotation(doc="`@user`")] = enum.auto()
    Placeholder: Annotated[
        int,
        EnFieldAnnotation(
            doc="Placeholder entry in text, usually writte like `<text to replace>`"
        ),
    ] = enum.auto()
    RadioTarget: Annotated[int, EnFieldAnnotation(doc="`<<<RADIO>>>`")] = enum.auto()
    Target: Annotated[int, EnFieldAnnotation(doc="`<<TARGET>>`")] = enum.auto()
    SrcInlineCode: Annotated[
        int,
        EnFieldAnnotation(
            doc="inline piece of code (such as `src_nim`),. Latter is different from regular monospaced text inside of `~~` pair as it contains additional internal structure, optional parameter for code evaluation etc."
        ),
    ] = enum.auto()
    InlineCallCode: Annotated[
        int, EnFieldAnnotation(doc="Call to named source code block.")
    ] = enum.auto()
    InlineExport: Annotated[
        int,
        EnFieldAnnotation(
            doc="Passthrough block. Inline, multiline, or single-line. Syntax is `@@<backend-name>:<any-body>@@`. Has line and block syntax respectively"
        ),
    ] = enum.auto()
    InlineComment: int = enum.auto()
    RawText: Annotated[
        int,
        EnFieldAnnotation(
            doc="Raw string of text from input buffer. Things like particular syntax details of every single command, link formats are not handled in parser, deferring formatting to future processing layers "
        ),
    ] = enum.auto()
    SubtreeDescription: Annotated[int, EnFieldAnnotation(doc="`:description:` entry")] = (
        120
    )
    SubtreeUrgency: int = enum.auto()
    DrawerLogbook: Annotated[
        int, EnFieldAnnotation(doc="`:logbook:` entry storing note information")
    ] = enum.auto()
    Drawer: Annotated[
        int,
        EnFieldAnnotation(
            doc="Single enclosed drawer like `:properties: ... :end:` or `:logbook: ... :end:`"
        ),
    ] = enum.auto()
    DrawerPropertyList: int = enum.auto()
    DrawerProperty: Annotated[int, EnFieldAnnotation(doc="`:property:` drawer")] = (
        enum.auto()
    )
    Subtree: Annotated[int, EnFieldAnnotation(doc="Section subtree")] = enum.auto()
    SubtreeTimes: Annotated[
        int, EnFieldAnnotation(doc="Time? associated with subtree entry")
    ] = enum.auto()
    SubtreeStars: int = enum.auto()
    SubtreeCompletion: Annotated[
        int,
        EnFieldAnnotation(
            doc="Task compleation cookie, indicated either in percents of completion, or as `<done>/<todo>` ratio."
        ),
    ] = enum.auto()
    SubtreeImportance: Annotated[
        int,
        EnFieldAnnotation(
            doc="Subtree importance level, such as `[#A]` or `[#B]`. Default org-mode only allows single character for contents inside of `[]`, but this parser makes it possible to use any regular identifier, such as `[#urgent]`."
        ),
    ] = enum.auto()


class OrgTokenKind(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    Ampersand: int = enum.auto()
    AngleBegin: int = enum.auto()
    AngleEnd: int = enum.auto()
    AnyPunct: int = enum.auto()
    Asterisk: int = enum.auto()
    At: int = enum.auto()
    Backtick: int = enum.auto()
    BigIdent: int = enum.auto()
    BoldBegin: int = enum.auto()
    BoldEnd: int = enum.auto()
    BoldUnknown: int = enum.auto()
    BraceBegin: int = enum.auto()
    BraceEnd: int = enum.auto()
    Checkbox: int = enum.auto()
    Circumflex: int = enum.auto()
    CmdAdmonitionEnd: int = enum.auto()
    CmdAttr: int = enum.auto()
    CmdAuthor: int = enum.auto()
    CmdBindRaw: int = enum.auto()
    CmdCall: int = enum.auto()
    CmdCaption: int = enum.auto()
    CmdCategoryRaw: int = enum.auto()
    CmdCell: int = enum.auto()
    CmdCellBegin: int = enum.auto()
    CmdCellEnd: int = enum.auto()
    CmdCenterBegin: int = enum.auto()
    CmdCenterEnd: int = enum.auto()
    CmdColonIdent: int = enum.auto()
    CmdColumns: int = enum.auto()
    CmdCommentBegin: int = enum.auto()
    CmdCommentEnd: int = enum.auto()
    CmdConstants: int = enum.auto()
    CmdContentBegin: int = enum.auto()
    CmdContentEnd: int = enum.auto()
    CmdCreator: int = enum.auto()
    CmdCustomRaw: int = enum.auto()
    CmdDateRaw: int = enum.auto()
    CmdDescription: int = enum.auto()
    CmdDrawersRaw: int = enum.auto()
    CmdDynamicBlockBegin: Annotated[
        int, EnFieldAnnotation(doc="`#+begin:` with the unspecified name")
    ] = enum.auto()
    CmdDynamicBlockEnd: Annotated[
        int, EnFieldAnnotation(doc="`#+end:` matching with `#+begin:`")
    ] = enum.auto()
    CmdCustomTextBlockBegin: Annotated[
        int, EnFieldAnnotation(doc="`#+begin_` with the text content inside")
    ] = enum.auto()
    CmdCustomTextBlockEnd: int = enum.auto()
    CmdCustomRawBlockBegin: Annotated[
        int, EnFieldAnnotation(doc="`#+begin_` block with the raw string")
    ] = enum.auto()
    CmdCustomRawBlockLine: int = enum.auto()
    CmdCustomRawBlockEnd: int = enum.auto()
    CmdEmailRaw: int = enum.auto()
    CmdExampleBegin: int = enum.auto()
    CmdExampleEnd: int = enum.auto()
    CmdExampleLine: int = enum.auto()
    CmdExcludeTagsRaw: int = enum.auto()
    CmdExportBegin: int = enum.auto()
    CmdExportEnd: int = enum.auto()
    CmdExportLine: int = enum.auto()
    CmdFiletags: int = enum.auto()
    CmdFlag: int = enum.auto()
    CmdHeader: int = enum.auto()
    CmdHtmlHeadRaw: int = enum.auto()
    CmdInclude: int = enum.auto()
    CmdLanguage: int = enum.auto()
    CmdLatexClass: int = enum.auto()
    CmdLatexClassOptions: int = enum.auto()
    CmdLatexCompiler: int = enum.auto()
    CmdLatexHeader: int = enum.auto()
    CmdLatexHeaderExtraRaw: int = enum.auto()
    CmdLinkRaw: int = enum.auto()
    CmdMacroRaw: int = enum.auto()
    CmdName: int = enum.auto()
    CmdOptions: int = enum.auto()
    CmdPrefix: int = enum.auto()
    CmdPrioritiesRaw: int = enum.auto()
    CmdPropertyArgs: int = enum.auto()
    CmdPropertyRaw: int = enum.auto()
    CmdPropertyText: int = enum.auto()
    CmdQuoteBegin: int = enum.auto()
    CmdQuoteEnd: int = enum.auto()
    CmdRawArg: int = enum.auto()
    CmdResults: int = enum.auto()
    CmdRow: int = enum.auto()
    CmdRowBegin: int = enum.auto()
    CmdRowEnd: int = enum.auto()
    CmdSelectTagsRaw: int = enum.auto()
    CmdSeqTodoRaw: int = enum.auto()
    CmdKeywordsRaw: int = enum.auto()
    CmdSetupfileRaw: int = enum.auto()
    CmdSrcBegin: int = enum.auto()
    CmdSrcEnd: int = enum.auto()
    CmdStartup: int = enum.auto()
    CmdTableBegin: int = enum.auto()
    CmdTableEnd: int = enum.auto()
    CmdTagsRaw: int = enum.auto()
    CmdTblfm: int = enum.auto()
    CmdTitle: int = enum.auto()
    CmdVerseBegin: int = enum.auto()
    CmdVerseEnd: int = enum.auto()
    Colon: int = enum.auto()
    ColonArgumentsProperty: int = enum.auto()
    ColonEnd: int = enum.auto()
    ColonExampleLine: int = enum.auto()
    ColonLiteralProperty: int = enum.auto()
    ColonLogbook: int = enum.auto()
    ColonProperties: int = enum.auto()
    ColonPropertyText: int = enum.auto()
    Comma: int = enum.auto()
    Comment: int = enum.auto()
    CriticAddBegin: int = enum.auto()
    CriticAddEnd: int = enum.auto()
    CriticCommentBegin: int = enum.auto()
    CriticCommentEnd: int = enum.auto()
    CriticDeleteBegin: int = enum.auto()
    CriticDeleteEnd: int = enum.auto()
    CriticHighlightBegin: int = enum.auto()
    CriticHighlightEnd: int = enum.auto()
    CriticReplaceBegin: int = enum.auto()
    CriticReplaceEnd: int = enum.auto()
    CriticReplaceMiddle: int = enum.auto()
    CurlyBegin: int = enum.auto()
    CurlyEnd: int = enum.auto()
    Date: int = enum.auto()
    Dedent: int = enum.auto()
    Dollar: int = enum.auto()
    DoubleAngleBegin: int = enum.auto()
    DoubleAngleEnd: int = enum.auto()
    DoubleColon: int = enum.auto()
    DoubleDash: int = enum.auto()
    DoubleHash: int = enum.auto()
    DoubleQuote: int = enum.auto()
    DoubleSlash: int = enum.auto()
    ActiveDynamicTimeContent: int = enum.auto()
    InactiveDynamicTimeContent: int = enum.auto()
    AgendaDiaryTimeContent: Annotated[
        int,
        EnFieldAnnotation(
            doc="`%%(` at the start of the line in the subtree, denoting the start of the dynamic agenda."
        ),
    ] = enum.auto()
    EndOfFile: int = enum.auto()
    Equals: int = enum.auto()
    Escaped: int = enum.auto()
    Exclamation: int = enum.auto()
    FootnoteInlineBegin: Annotated[
        int, EnFieldAnnotation(doc="`[fn::` with the inline definition")
    ] = enum.auto()
    FootnoteLinked: int = enum.auto()
    ForwardSlash: int = enum.auto()
    HashIdent: int = enum.auto()
    HashTagBegin: int = enum.auto()
    Indent: int = enum.auto()
    InlineExportBackend: int = enum.auto()
    InlineExportContent: int = enum.auto()
    ItalicBegin: int = enum.auto()
    ItalicEnd: int = enum.auto()
    ItalicUnknown: int = enum.auto()
    LatexInlineRaw: int = enum.auto()
    LatexParBegin: int = enum.auto()
    LatexParEnd: int = enum.auto()
    LatexBraceBegin: int = enum.auto()
    LatexBraceEnd: int = enum.auto()
    LatexDollar1Begin: int = enum.auto()
    LatexDollar1End: int = enum.auto()
    LatexDollar2Begin: int = enum.auto()
    LatexDollar2End: int = enum.auto()
    LeadingMinus: int = enum.auto()
    LeadingNumber: int = enum.auto()
    LeadingPipe: int = enum.auto()
    LeadingPlus: int = enum.auto()
    LeadingSpace: int = enum.auto()
    LeadingCharacter: Annotated[int, EnFieldAnnotation(doc="a)")] = enum.auto()
    LineCommand: int = enum.auto()
    LinkBegin: int = enum.auto()
    LinkDescriptionBegin: int = enum.auto()
    LinkDescriptionEnd: int = enum.auto()
    LinkEnd: int = enum.auto()
    LinkFull: int = enum.auto()
    LinkProtocol: int = enum.auto()
    LinkProtocolAttachment: int = enum.auto()
    LinkProtocolCustomId: int = enum.auto()
    LinkProtocolFile: int = enum.auto()
    LinkProtocolHttp: int = enum.auto()
    LinkProtocolId: int = enum.auto()
    LinkProtocolInternal: int = enum.auto()
    LinkProtocolTitle: int = enum.auto()
    LinkSplit: int = enum.auto()
    LinkTarget: int = enum.auto()
    LinkTargetBegin: int = enum.auto()
    LinkTargetEnd: int = enum.auto()
    LinkTargetFile: int = enum.auto()
    ListBegin: int = enum.auto()
    ListEnd: int = enum.auto()
    ListItemBegin: int = enum.auto()
    ListItemEnd: int = enum.auto()
    LongNewline: int = enum.auto()
    MediumNewline: int = enum.auto()
    Minus: int = enum.auto()
    MiscUnicode: int = enum.auto()
    MonospaceBegin: int = enum.auto()
    MonospaceEnd: int = enum.auto()
    MonospaceUnknown: int = enum.auto()
    Newline: int = enum.auto()
    Number: int = enum.auto()
    ParBegin: int = enum.auto()
    ParEnd: int = enum.auto()
    Percent: int = enum.auto()
    Pipe: int = enum.auto()
    Placeholder: int = enum.auto()
    Plus: int = enum.auto()
    Punctuation: int = enum.auto()
    RawText: int = enum.auto()
    SameIndent: int = enum.auto()
    Semicolon: int = enum.auto()
    SingleQuote: int = enum.auto()
    SrcContent: int = enum.auto()
    StmtListBegin: int = enum.auto()
    StmtListEnd: int = enum.auto()
    StrikeBegin: int = enum.auto()
    StrikeEnd: int = enum.auto()
    StrikeUnknown: int = enum.auto()
    SubtreeCompletion: int = enum.auto()
    SubtreePriority: int = enum.auto()
    SubtreeStars: int = enum.auto()
    Symbol: int = enum.auto()
    TableSeparator: int = enum.auto()
    TextSeparator: int = enum.auto()
    TextSrcBegin: int = enum.auto()
    Tilda: int = enum.auto()
    Time: int = enum.auto()
    TimeArrow: int = enum.auto()
    TimeRepeaterDuration: int = enum.auto()
    TimeRepeaterSpec: int = enum.auto()
    TimeWarnPeriod: int = enum.auto()
    TrailingPipe: int = enum.auto()
    TreeClock: int = enum.auto()
    TreeTime: int = enum.auto()
    TripleAngleBegin: int = enum.auto()
    TripleAngleEnd: int = enum.auto()
    Underline: int = enum.auto()
    UnderlineBegin: int = enum.auto()
    UnderlineEnd: int = enum.auto()
    UnderlineUnknown: int = enum.auto()
    Unknown: int = enum.auto()
    VerbatimBegin: int = enum.auto()
    VerbatimEnd: int = enum.auto()
    VerbatimUnknown: int = enum.auto()
    Whitespace: int = enum.auto()
    Word: int = enum.auto()


class OrgJsonKind(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    Null: int = enum.auto()
    Object: int = enum.auto()
    Array: int = enum.auto()
    String: int = enum.auto()
    Boolean: int = enum.auto()
    Int: int = enum.auto()
    Float: int = enum.auto()


class CheckboxState(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    None_: int = enum.auto()
    Done: int = enum.auto()
    Empty: int = enum.auto()
    Partial: int = enum.auto()


class LinkVisibility(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    LiteralLinks: int = enum.auto()
    DescriptiveLinks: int = enum.auto()


class BlockVisibility(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    HideBlocks: int = enum.auto()
    NoHideBlocks: int = enum.auto()


class SubtreeTodoSource(M.Enum):
    """Where to take todo completion statistics from"""

    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    Checkbox: Annotated[
        int,
        EnFieldAnnotation(doc="Only count checkbox subnodes as a progress completion"),
    ] = enum.auto()
    Todo: Annotated[int, EnFieldAnnotation(doc="Use subtrees with todo keywords")] = (
        enum.auto()
    )
    Both: Annotated[int, EnFieldAnnotation(doc="Use both subtrees and todo keywords")] = (
        enum.auto()
    )


class ListFormattingMode(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    None_: Annotated[int, EnFieldAnnotation(doc="Default, no custom formatting")] = (
        enum.auto()
    )
    Table1D1Col: Annotated[
        int, EnFieldAnnotation(doc="one column, each table item is an individual row")
    ] = enum.auto()
    Table1D2Col: Annotated[
        int,
        EnFieldAnnotation(
            doc="for description lists, treat header row as an individual column"
        ),
    ] = enum.auto()
    Table2DColFirst: Annotated[
        int,
        EnFieldAnnotation(
            doc="for tables tables with arbitrary column count, treat the first level of items as "
            "column names, treat all nested elements in these columns as row values"
        ),
    ] = enum.auto()
    Table2DRowFirst: Annotated[
        int,
        EnFieldAnnotation(
            doc="for tables with arbitrary column count, each top-level list item is an individual "
            "row, then each item in the nested list is a cell on this row."
        ),
    ] = enum.auto()


class InitialSubtreeVisibility(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    Overview: int = enum.auto()
    Content: int = enum.auto()
    ShowAll: int = enum.auto()
    Show2Levels: int = enum.auto()
    Show3Levels: int = enum.auto()
    Show4Levels: int = enum.auto()
    Show5Levels: int = enum.auto()
    ShowEverything: int = enum.auto()


_CXX_BACKEND = dict(
    default_constructor=True,
    default_eq=True,
)

# Shared types with default constructor
_CXX_SHARED = dict(
    org_groups=OrgTypeGroup.SHARED_TYPES,
    **_CXX_BACKEND,
)

# Aggregate struct types with no explicit default
# constructor
_CXX_SHARED_AGGREGATE = dict(
    org_groups=OrgTypeGroup.SHARED_TYPES,
    default_eq=True,
)


class LispCode(M.Class):
    __config__(
        backend=dict(
            cpp=dict(
                org_groups=OrgTypeGroup.SHARED_TYPES,
                default_constructor=True,
                default_eq=True,
            )
        )
    )

    class Call(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        name: str
        args: List["LispCode"]

    class Quoted(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        items: List["LispCode"]

    class List(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        items: List["LispCode"]

    class Vector(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        items: List["LispCode"]

    class KeyValue(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        name: str
        value: List["LispCode"]

    class Number(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        value: Int32 = 0

    class Text(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        value: str

    class Ident(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        name: str

    class Boolean(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        value: bool = False

    class Real(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

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
    __config__(backend=dict(cpp=_CXX_SHARED))

    class FixedTime(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        time: H._T["UserTime"]

    class DynamicTime(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        time: LispCode

    isActive: bool = False

    __variant__(FixedTime, DynamicTime, field="data", kind="Kind")


class Tblfm(M.Class):
    __config__(backend=dict(cpp=_CXX_SHARED))

    class Expr(M.Class):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        class AxisRef(M.Case):
            __config__(backend=dict(cpp=_CXX_BACKEND))

            class Position(M.Class):
                __config__(backend=dict(cpp=_CXX_BACKEND))

                class Index(M.Case):
                    __config__(backend=dict(cpp=_CXX_BACKEND))

                    index: Int32

                class Name(M.Case):
                    __config__(backend=dict(cpp=_CXX_BACKEND))

                    name: str

                __variant__(Index, Name, field="data", kind="Kind")

            col: Position
            row: Optional[Position] = None

        class AxisName(M.Case):
            __config__(backend=dict(cpp=_CXX_BACKEND))

            name: str

        class IntLiteral(M.Case):
            __config__(backend=dict(cpp=_CXX_BACKEND))

            value: Int32

        class FloatLiteral(M.Case):
            __config__(backend=dict(cpp=_CXX_BACKEND))

            value: Float32

        class RangeRef(M.Case):
            __config__(backend=dict(cpp=_CXX_BACKEND))

            first: Optional["Tblfm.Expr.AxisRef"] = None
            last: Optional["Tblfm.Expr.AxisRef"] = None

        class Call(M.Case):
            __config__(backend=dict(cpp=_CXX_BACKEND))

            name: str
            args: List["Tblfm.Expr"]

        class Elisp(M.Case):
            __config__(backend=dict(cpp=_CXX_BACKEND))

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
        __config__(backend=dict(cpp=_CXX_BACKEND))

        class Flag(M.Enum):
            """Flags for table format expression cell formulas"""

            CellLeftAlign: Annotated[
                int, EnFieldAnnotation(doc="Left-align the result")
            ] = enum.auto()
            CellRightAlign: Annotated[
                int, EnFieldAnnotation(doc="Right-align the result")
            ] = enum.auto()
            CellCenterAlign: Annotated[
                int, EnFieldAnnotation(doc="Center-align the result")
            ] = enum.auto()
            CellNumber: Annotated[
                int, EnFieldAnnotation(doc="Convert result to number/currency format")
            ] = enum.auto()
            CellExponential: Annotated[
                int, EnFieldAnnotation(doc="Use exponential notation for numbers")
            ] = enum.auto()
            CellFloating: Annotated[
                int, EnFieldAnnotation(doc="Use floating point format")
            ] = enum.auto()
            CellUnformat: Annotated[
                int, EnFieldAnnotation(doc="Unformat values before calculating")
            ] = enum.auto()
            CellText: Annotated[int, EnFieldAnnotation(doc="Convert result to text")] = (
                enum.auto()
            )
            CellBool: Annotated[
                int, EnFieldAnnotation(doc="Display boolean values as t/nil")
            ] = enum.auto()
            CellDecimal: Annotated[
                int,
                EnFieldAnnotation(
                    doc="Fixed format with specified decimal places (e.g., ;D2)"
                ),
            ] = enum.auto()
            CellPercentage: Annotated[int, EnFieldAnnotation(doc="Percentage format")] = (
                10
            )
            CellHours: Annotated[
                int, EnFieldAnnotation(doc="Convert to hours/minutes (HH:MM)")
            ] = enum.auto()
            CellZero: Annotated[
                int, EnFieldAnnotation(doc="Display zero as empty cell")
            ] = enum.auto()
            CellMarkInvalid: Annotated[
                int, EnFieldAnnotation(doc="Mark field as invalid if conversion fails")
            ] = enum.auto()
            CellQuote: Annotated[int, EnFieldAnnotation(doc="Quote field contents")] = (
                enum.auto()
            )

        target: "Tblfm.Expr.AxisRef"
        expr: List["Tblfm.Expr"]
        flags: List[Flag]

    exprs: List[Assign]


class AttrValue(M.Class):
    __config__(
        backend=dict(
            cpp=dict(
                org_groups=OrgTypeGroup.SHARED_TYPES,
                variants=dict(data=dict(variant_name="DataVariant")),
                **_CXX_BACKEND,
            ),
        ),
    )

    class DimensionSpan(M.Class):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        first: Int32 = 0
        last: Optional[Int32] = None

    class TextValue(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        value: str

    class FileReference(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        file: str
        reference: str

    class LispValue(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

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

    def getBool(self) -> Optional[bool]: ...

    def getInt(self) -> Optional[Int32]: ...

    def getString(self) -> str: ...

    def getDouble(self) -> Optional[float]: ...


class HashTagFlat(M.Class):
    __config__(backend=dict(cpp=_CXX_SHARED))

    tags: List[str]

    @M.Method(backend=dict(cpp=dict(name="operator<")))
    def less(self, other: "HashTagFlat") -> bool: ...


class TodoKeyword(M.Class):
    __config__(backend=dict(cpp=_CXX_SHARED))

    class Transition(M.Enum):
        None_: int = enum.auto()
        NoteWithTimestamp: int = enum.auto()
        Timestamp: int = enum.auto()

    name: str
    shortcut: Optional[str] = None
    onEnter: Transition
    onLeave: Transition


class HashTagText(M.Class):
    """Single or nested inline hash-tag"""

    __config__(backend=dict(cpp=_CXX_SHARED))

    head: str = M.Field(doc="Main part of the tag")
    subtags: List["HashTagText"] = M.Field(doc="List of nested tags")

    def prefixMatch(self, prefix: List[str]) -> bool:
        """Check if list of tag names is a prefix for either of the nested hash tags in this one"""
        ...

    def getFlatHashes(self, withIntermediate: bool = True) -> List[HashTagFlat]:
        """Get flat list of expanded hashtags"""
        ...


class SubtreePath(M.Class):
    __config__(backend=dict(cpp=_CXX_SHARED))

    path: List[str]


class LinkTarget(M.Class):
    __config__(backend=dict(cpp=_CXX_SHARED))

    class Raw(M.Case):
        __config__(backend=dict(cpp=_CXX_SHARED))

        text: str

    class Id(M.Case):
        __config__(backend=dict(cpp=_CXX_SHARED))

        text: str

    class CustomId(M.Case):
        __config__(backend=dict(cpp=_CXX_SHARED))

        text: str

    class SubtreeTitle(M.Case):
        __config__(backend=dict(cpp=_CXX_SHARED))

        title: SubtreePath
        level: Int32

    class Person(M.Case):
        __config__(backend=dict(cpp=_CXX_SHARED))

        name: str

    class UserProtocol(M.Case):
        __config__(backend=dict(cpp=_CXX_SHARED))

        protocol: str
        target: str

    class Internal(M.Case):
        __config__(backend=dict(cpp=_CXX_SHARED))

        target: str

    class Footnote(M.Case):
        __config__(backend=dict(cpp=_CXX_SHARED))

        target: str

    class File(M.Case):
        __config__(backend=dict(cpp=_CXX_SHARED))

        file: str

    class Attachment(M.Case):
        __config__(backend=dict(cpp=_CXX_SHARED))

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
    __config__(
        backend=dict(
            cpp=dict(
                **_CXX_SHARED,
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

    class Priority(M.Case):
        """Priority added"""

        __config__(backend=dict(cpp=_CXX_SHARED))

        class Action(M.Enum):
            """Priority change action"""

            Added: Annotated[
                int, EnFieldAnnotation(doc="`Priority B added on [timestamp]`")
            ] = enum.auto()
            Removed: Annotated[
                int, EnFieldAnnotation(doc="`Priority C removed on [timestamp]`")
            ] = enum.auto()
            Changed: Annotated[
                int, EnFieldAnnotation(doc="`Priority B changed from C on [timestamp]`")
            ] = enum.auto()

        oldPriority: Optional[str] = M.Field(
            doc="Previous priority for change and removal"
        )
        newPriority: Optional[str] = M.Field(doc="New priority for change and addition")
        on: H._T["UserTime"] = M.Field(doc="When priority was changed")
        action: Action = M.Field(doc="Which action taken")

    class Note(M.Case):
        """Timestamped note"""

        __config__(backend=dict(cpp=_CXX_SHARED))

        on: H._T["UserTime"] = M.Field(doc="Where log was taken")

    class Refile(M.Case):
        """Refiling action"""

        __config__(
            backend=dict(cpp=dict(field_names=dict(from_="from"), **_CXX_SHARED)),
        )

        on: H._T["UserTime"] = M.Field(doc="When the refiling happened")
        from_: LinkTarget = M.Field(doc="Link to the original subtree")

    class Clock(M.Case):
        """Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`"""

        __config__(
            backend=dict(cpp=dict(field_names=dict(from_="from"), **_CXX_SHARED)),
        )

        from_: H._T["UserTime"] = M.Field(doc="Clock start time")
        to: Optional[H._T["UserTime"]] = M.Field(
            doc="Optional end of the clock", default=None
        )

    class State(M.Case):
        """Change of the subtree state -- `- State "WIP" from "TODO" [2023-04-30 Sun 13:29:04]`"""

        __config__(
            backend=dict(cpp=dict(field_names=dict(from_="from"), **_CXX_SHARED)),
        )

        from_: str
        to: str
        on: H._T["UserTime"]

    class Deadline(M.Case):
        """Change of the subtree deadline"""

        __config__(
            backend=dict(cpp=dict(field_names=dict(from_="from"), **_CXX_SHARED)),
        )

        from_: Optional[H._T["UserTime"]] = None
        to: H._T["UserTime"]
        on: H._T["UserTime"]

    class Schedule(M.Case):
        """Change of the subtree Schedule"""

        __config__(
            backend=dict(cpp=dict(field_names=dict(from_="from"), **_CXX_SHARED)),
        )

        from_: Optional[H._T["UserTime"]] = None
        to: H._T["UserTime"]
        on: H._T["UserTime"]

    class Tag(M.Case):
        """Assign tag to the subtree `- Tag "project##haxorg" Added on [2023-04-30 Sun 13:29:06]`"""

        __config__(backend=dict(cpp=_CXX_SHARED))

        on: H._T["UserTime"] = M.Field(doc="When the log was assigned")
        tag: HashTagText = M.Field(doc="Tag in question")
        added: bool = M.Field(doc="Added/removed?", default=False)

    class Unknown(M.Case):
        """Unknown subtree log entry kind"""

        __config__(backend=dict(cpp=_CXX_SHARED))

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


class SubtreeCompletion(M.Class):
    """Completion status of the subtree list element"""

    __config__(backend=dict(cpp=_CXX_SHARED))

    done: Int32 = M.Field(doc="Number of completed tasks", default=0)
    full: Int32 = M.Field(doc="Full number of tasks", default=0)
    isPercent: bool = M.Field(
        doc="Use fraction or percent to display completion", default=False
    )


class AttrList(M.Class):
    __config__(backend=dict(cpp=_CXX_SHARED))

    items: List[AttrValue]


class AttrGroup(M.Class):
    __config__(backend=dict(cpp=_CXX_SHARED))

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

    def atFirstNamed(
        self, index: str
    ) -> Annotated[AttrValue, TypeAnnotation(backend=dict(cpp=dict(is_ref=True)))]: ...

    def getFirstNamed(self, index: str) -> Optional[AttrValue]: ...


class OrgCodeEvalInput(M.Class):
    __config__(backend=dict(cpp=_CXX_SHARED))

    class Var(M.Class):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        name: str
        value: Native._T["OrgJson"]

    class ResultType(M.Enum):
        """What context to use for results"""

        None_: int = enum.auto()
        Table: Annotated[
            int,
            EnFieldAnnotation(
                doc="Interpret the results as an Org table. If the result is a single value, create a table with one row and one column."
            ),
        ] = enum.auto()
        List: Annotated[
            int,
            EnFieldAnnotation(
                doc="Interpret the results as an Org list. If the result is a single value, create a list of one element."
            ),
        ] = enum.auto()
        Scalar: Annotated[
            int,
            EnFieldAnnotation(
                doc="Interpret literally and insert as quoted text. Do not create a table."
            ),
        ] = enum.auto()
        SaveFile: Annotated[
            int,
            EnFieldAnnotation(
                doc="Interpret as a filename. Save the results of execution of the code block to that file, then insert a link to it."
            ),
        ] = enum.auto()

    class ResultFormat(M.Enum):
        """How to interpret output from the script"""

        None_: int = enum.auto()
        Raw: Annotated[
            int,
            EnFieldAnnotation(
                doc="Interpreted as raw Org mode. Inserted directly into the buffer."
            ),
        ] = enum.auto()
        Code: Annotated[
            int, EnFieldAnnotation(doc="Result enclosed in a code block.")
        ] = enum.auto()
        Drawer: Annotated[
            int,
            EnFieldAnnotation(
                doc="Results are added directly to the Org file as with ‘raw’, but are wrapped in a ‘RESULTS’ drawer or results macro (for inline code blocks), for later scripting and automated processing."
            ),
        ] = enum.auto()
        ExportType: Annotated[
            int, EnFieldAnnotation(doc="Results enclosed in a ‘BEGIN_EXPORT’ block.")
        ] = enum.auto()
        Link: int = enum.auto()

    class ResultHandling(M.Enum):
        """What to do with the final evaluation results"""

        None_: int = enum.auto()
        Replace: int = enum.auto()
        Silent: int = enum.auto()
        Discard: int = enum.auto()
        Append: int = enum.auto()
        Prepend: int = enum.auto()

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

    __config__(backend=dict(cpp=_CXX_SHARED))

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
    __config__(backend=dict(cpp=_CXX_SHARED))

    class Summary(M.Class):
        __config__(backend=dict(cpp=_CXX_SHARED))

        class CheckboxAggregate(M.Case):
            __config__(backend=dict(cpp=_CXX_SHARED))

            class Kind(M.Enum):
                IfAllNested: int = enum.auto()
                AggregateFractionRec: int = enum.auto()
                AggregatePercentRec: int = enum.auto()

            kind: Kind

        class MathAggregate(M.Case):
            __config__(backend=dict(cpp=_CXX_SHARED))

            class Kind(M.Enum):
                Min: int = enum.auto()
                Max: int = enum.auto()
                Mean: int = enum.auto()
                Sum: int = enum.auto()
                LowHighEst: int = enum.auto()

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
        __config__(backend=dict(cpp=_CXX_SHARED))

        summary: Optional["ColumnView.Summary"] = None
        width: Optional[Int32] = None
        property: Optional[str] = None
        propertyTitle: Optional[str] = None

    columns: List[Column]


class BlockCodeLine(M.Class):
    __config__(backend=dict(cpp=_CXX_SHARED))

    class Part(M.Class):
        __config__(backend=dict(cpp=_CXX_SHARED))

        class Raw(M.Case):
            __config__(backend=dict(cpp=_CXX_SHARED))
            code: str

        class Callout(M.Case):
            __config__(backend=dict(cpp=_CXX_SHARED))
            name: str

        class Tangle(M.Case):
            __config__(backend=dict(cpp=_CXX_SHARED))
            target: str

        __variant__(Raw, Callout, Tangle, field="data", kind="Kind")

    parts: List[Part] = M.Field(doc="parts of the single line")


class DocumentExportConfig(M.Class):
    __config__(
        backend=dict(
            cpp=dict(
                **_CXX_SHARED,
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

    class TaskExport(M.Class):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        taskWhitelist: List[str]

    class TagExport(M.Enum):
        None_: int = enum.auto()
        All: int = enum.auto()
        NotInToc: Annotated[
            int,
            EnFieldAnnotation(
                doc="Export tags in subtree titles but not in the table of content"
            ),
        ] = enum.auto()

    class TaskFiltering(M.Enum):
        Whitelist: Annotated[
            int, EnFieldAnnotation(doc="Include tasks from the whitelist")
        ] = enum.auto()
        Done: Annotated[int, EnFieldAnnotation(doc="Include tasks marked as done")] = (
            enum.auto()
        )
        None_: Annotated[
            int, EnFieldAnnotation(doc="Exclude all task subtrees from export")
        ] = enum.auto()
        All: Annotated[int, EnFieldAnnotation(doc="Add all task subtrees to export")] = (
            enum.auto()
        )

    class BrokenLinks(M.Enum):
        None_: int = enum.auto()
        Mark: int = enum.auto()
        Raise: int = enum.auto()
        Ignore: int = enum.auto()

    class ArchivedTrees(M.Enum):
        """Configure how archived trees are exported"""

        Skip: Annotated[int, EnFieldAnnotation(doc="Skip archived trees entirely")] = (
            enum.auto()
        )
        Headline: Annotated[
            int, EnFieldAnnotation(doc="Export only headlines of archived trees")
        ] = enum.auto()
        All: Annotated[
            int, EnFieldAnnotation(doc="Export archived trees with full content")
        ] = enum.auto()

    class DoExport(M.Case):
        exportToc: bool

    class ExportFixed(M.Case):
        exportLevels: Int32

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


class SubtreePeriod(M.Class):
    """Type of the subtree associated time periods"""

    __config__(
        backend=dict(
            cpp=dict(
                field_names=dict(from_="from"),
                **_CXX_SHARED,
            )
        ),
    )

    class Kind(M.Enum):
        """Period kind"""

        Clocked: Annotated[
            int, EnFieldAnnotation(doc="Time period of the task execution.")
        ] = enum.auto()
        Closed: Annotated[int, EnFieldAnnotation(doc="Task marked as closed")] = (
            enum.auto()
        )
        Scheduled: Annotated[
            int,
            EnFieldAnnotation(
                doc="Date of task execution start plus it's estimated effort duration. If the latter one is missing then only a single time point is returned"
            ),
        ] = enum.auto()
        Titled: Annotated[
            int,
            EnFieldAnnotation(
                doc="Single point or time range used in title. Single point can also be a simple time, such as `12:20`"
            ),
        ] = enum.auto()
        Deadline: Annotated[
            int,
            EnFieldAnnotation(doc="Date of task completion. Must be a single time point"),
        ] = enum.auto()
        Created: Annotated[int, EnFieldAnnotation(doc="When the subtree was created")] = (
            enum.auto()
        )
        Repeated: Annotated[
            int, EnFieldAnnotation(doc="Last repeat time of the recurring tasks")
        ] = enum.auto()

    kind: Kind = M.Field(
        doc="Time period kind -- not associated with point/range distinction"
    )
    from_: H._T["UserTime"] = M.Field(doc="Clock start time")
    to: Optional[H._T["UserTime"]] = M.Field(
        doc="Optional end of the clock", default=None
    )


class NamedProperty(M.Class):
    """Single subtree property"""

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

    class Nonblocking(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        isBlocking: bool

    class ArchiveTime(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        time: H._T["UserTime"]

    class ArchiveFile(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        file: str

    class ArchiveOlpath(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        path: SubtreePath

    class ArchiveTarget(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        path: SubtreePath
        pattern: str

    class ArchiveCategory(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        category: str

    class ArchiveTodo(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        todo: str

    class Trigger(M.Case):
        pass

    class ExportLatexClass(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        latexClass: str

    class CookieData(M.Case):
        """`:COOKIE_DATA:` for the subtree completion calculation"""

        __config__(backend=dict(cpp=_CXX_BACKEND))

        isRecursive: bool
        source: SubtreeTodoSource

    class ExportLatexClassOptions(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        options: List[str]

    class ExportLatexHeader(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        header: str

    class ExportLatexCompiler(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        compiler: str

    class Ordered(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        isOrdered: bool

    class Effort(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        hours: Int32 = 0
        minutes: Int32 = 0

    class Visibility(M.Case):
        class Level(M.Enum):
            Folded: int = enum.auto()
            Children: int = enum.auto()
            Content: int = enum.auto()
            All: int = enum.auto()

        level: Level

    class ExportOptions(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        backend: str
        values: Dict[str, str]

    class Blocker(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        blockers: List[str]

    class Unnumbered(M.Case):
        pass

    class Created(M.Case):
        __config__(backend=dict(cpp=_CXX_BACKEND))

        time: TimeValue

    class RadioId(M.Case):
        """Radio target ID"""

        __config__(backend=dict(cpp=_CXX_BACKEND))

        words: List[str]

    class HashtagDef(M.Case):
        """Definition of a hashtag entry"""

        __config__(backend=dict(cpp=_CXX_BACKEND))

        hashtag: HashTagText

    class CustomArgs(M.Case):
        """Custom property with unparsed arguments"""

        __config__(backend=dict(cpp=_CXX_BACKEND))

        name: str = M.Field(doc="Original name of the property")
        sub: Optional[str] = M.Field(doc="Property target specialization", default=None)
        attrs: AttrGroup = M.Field(doc="Property parameters")

    class CustomRaw(M.Case):
        """Custom property with unparsed arguments"""

        __config__(backend=dict(cpp=_CXX_BACKEND))

        name: str = M.Field(doc="Original name of the property")
        value: str = M.Field(doc="Property value")

    class CustomId(M.Case):
        """Custom property with unparsed arguments"""

        __config__(backend=dict(cpp=_CXX_BACKEND))

        value: str = M.Field(doc="Property value")

    class CustomSubtreeJson(M.Case):
        """Free-form JSON"""

        __config__(backend=dict(cpp=_CXX_BACKEND))

        name: str
        value: Native._T["OrgJson"]

    class CustomSubtreeFlags(M.Case):
        """Free-form flags"""

        __config__(backend=dict(cpp=_CXX_BACKEND))

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

    class ParseTokenError(M.Case):
        """Parser errors for situations when failure can be attributed to specific token"""

        __config__(backend=dict(cpp=_CXX_BACKEND))

        brief: str
        detail: str
        parserFunction: str
        parserLine: Int32
        tokenKind: M._T["OrgTokenKind"]
        tokenText: str
        loc: Optional[P._T["SourceLoc"]] = None
        errName: str
        errCode: str

    class ParseError(M.Case):
        """General parser errors"""

        __config__(backend=dict(cpp=_CXX_BACKEND))

        brief: str
        detail: str
        parserFunction: str
        parserLine: Int32
        errName: str
        errCode: str
        loc: Optional[P._T["SourceLoc"]] = None

    class IncludeError(M.Case):
        """Cannot convert parsed tree into"""

        __config__(backend=dict(cpp=_CXX_BACKEND))

        brief: str
        targetPath: str
        workingFile: str

    class ConvertError(M.Case):
        """Cannot convert parsed tree into"""

        __config__(backend=dict(cpp=_CXX_BACKEND))

        brief: str
        detail: str
        convertFunction: str
        convertLine: Int32
        convertFile: str
        errName: str
        errCode: str
        loc: Optional[P._T["SourceLoc"]] = None

    class InternalError(M.Case):
        """Internal implementation error: should not be visible to the end-user."""

        __config__(backend=dict(cpp=_CXX_BACKEND))

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


def get_model() -> ModelDef:
    return M.finalize()
