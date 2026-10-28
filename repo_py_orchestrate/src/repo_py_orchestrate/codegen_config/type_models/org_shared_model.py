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
Native = get_dsl_model("org.sem.native")


class OrgSpecName(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    Unnamed: int = 0
    Result: int = 1
    Year: int = 2
    Day: int = 3
    Clock: int = 4
    Repeater: int = 5
    Warn: int = 6
    Zone: int = 7
    Link: int = 8
    Tags: int = 9
    Tag: int = 10
    State: int = 11
    Protocol: int = 12
    Desc: int = 13
    Times: int = 14
    Drawer: int = 15
    Args: int = 16
    Name: int = 17
    Definition: int = 18
    Body: int = 19
    HeaderArgs: int = 20
    File: int = 21
    Kind: int = 22
    Lang: int = 23
    Prefix: int = 24
    Text: int = 25
    Todo: int = 26
    Importance: int = 27
    Title: int = 28
    Completion: int = 29
    Head: int = 30
    Subnodes: int = 31
    Properties: int = 32
    Logbook: int = 33
    Description: int = 34
    Logs: int = 35
    Newstate: int = 36
    Oldstate: int = 37
    Time: int = 38
    From: int = 39
    EndArgs: int = 40
    Flags: int = 41
    Value: int = 42
    Assoc: int = 43
    Main: int = 44
    Hash: int = 45
    Bullet: int = 46
    Counter: int = 47
    Checkbox: int = 48
    Header: int = 49
    To: int = 50
    Diff: int = 51
    Property: int = 52
    Subname: int = 53
    Values: int = 54
    Cells: int = 55
    Rows: int = 56
    Lines: int = 57
    Chunks: int = 58


class OrgNodeKind(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    None_: Annotated[
        int, EnFieldAnnotation(doc="Default valye for node - invalid state")
    ] = 0
    Document: Annotated[
        int,
        EnFieldAnnotation(
            doc="Toplevel part of the ast, not created by parser, and only used in `semorg` stage"
        ),
    ] = 1
    Empty: Annotated[
        int,
        EnFieldAnnotation(doc="Empty node - valid state that does not contain any value"),
    ] = 2
    InlineStmtList: int = 3
    StmtList: Annotated[
        int,
        EnFieldAnnotation(
            doc="List of statements, possibly recursive. Used as toplevel part of the document, in recursive parsing of subtrees, or as regular list, in cases where multiple subnodes have to be grouped together."
        ),
    ] = 4
    Checkbox: Annotated[
        int, EnFieldAnnotation(doc="Single checkbox item like `[X]` or `[-]`")
    ] = 5
    List: int = 6
    Bullet: Annotated[int, EnFieldAnnotation(doc="List item prefix")] = 7
    ListItem: int = 8
    ListTag: Annotated[
        int,
        EnFieldAnnotation(
            doc="Auxilliary wrapper for the paragraph placed at the start of the description list."
        ),
    ] = 9
    Counter: int = 10
    File: int = 11
    ColonExample: Annotated[int, EnFieldAnnotation(doc="Colon example block")] = 12
    TextSeparator: Annotated[
        int, EnFieldAnnotation(doc="Long horizontal line `----`")
    ] = 13
    Paragraph: Annotated[
        int,
        EnFieldAnnotation(
            doc="Single 'paragraph' of text. Used as generic container for any place in AST where unordered sentence might be encountered (e.g. caption, link description) - not limited to actual paragraph"
        ),
    ] = 14
    TableRow: Annotated[int, EnFieldAnnotation(doc="Horizontal table row")] = 15
    TableCell: Annotated[
        int,
        EnFieldAnnotation(
            doc="Single cell in row. Might contain anyting, including other tables, simple text paragraph etc."
        ),
    ] = 16
    Table: Annotated[int, EnFieldAnnotation(doc="Org-mode table")] = 17
    InlineFootnote: Annotated[
        int,
        EnFieldAnnotation(
            doc="Inline footnote with text placed directly in the node body."
        ),
    ] = 18
    Footnote: Annotated[
        int,
        EnFieldAnnotation(
            doc="Footnote entry. Just as regular links - internal content is not parsed, and instead just cut out verbatim into target AST node."
        ),
    ] = 19
    Cmd: Annotated[
        int,
        EnFieldAnnotation(
            doc="Undefined single-line command -- most likely custom user-provided oe"
        ),
    ] = 20
    Attrs: Annotated[int, EnFieldAnnotation(doc="Arguments for the command block")] = 21
    AttrValue: Annotated[int, EnFieldAnnotation(doc=":key name=value syntax")] = 22
    LispExpr: Annotated[
        int, EnFieldAnnotation(doc="S-expression as an attribute value value")
    ] = 23
    LispList: Annotated[int, EnFieldAnnotation(doc="`(a b c)` without quoting")] = 24
    LispVector: Annotated[int, EnFieldAnnotation(doc="[1 2 3 4]` without quoting")] = 25
    LispQuoted: Annotated[
        int, EnFieldAnnotation(doc="Extra wrapping node for quoted elements")
    ] = 26
    CmdTitle: Annotated[
        int, EnFieldAnnotation(doc="`#+title:` - full document title")
    ] = 27
    CmdAuthor: Annotated[int, EnFieldAnnotation(doc="`#+author:` Document author")] = 28
    CmdCreator: Annotated[int, EnFieldAnnotation(doc="`#+creator:` Document creator")] = (
        29
    )
    CmdInclude: Annotated[
        int,
        EnFieldAnnotation(
            doc="`#+include:` - include other org-mode document (or subsection of it), source code or backend-specific chunk."
        ),
    ] = 30
    CmdLanguage: Annotated[int, EnFieldAnnotation(doc="`#+language:`")] = 31
    CmdEmail: Annotated[int, EnFieldAnnotation(doc="`#+email:`")] = 32
    CmdAttr: Annotated[
        int, EnFieldAnnotation(doc="`#+attr_html:`, `#+attr_image` etc.")
    ] = 33
    CmdStartup: Annotated[int, EnFieldAnnotation(doc="`#+startup:`")] = 34
    CmdName: Annotated[
        int, EnFieldAnnotation(doc="`#+name:` - name of the associated entry")
    ] = 35
    CmdCustomTextCommand: Annotated[
        int, EnFieldAnnotation(doc="Line command with parsed text value")
    ] = 36
    CmdCustomArgsCommand: Annotated[
        int, EnFieldAnnotation(doc="Line command with parsed argument list")
    ] = 37
    CmdCustomRawCommand: Annotated[
        int, EnFieldAnnotation(doc="Line command with raw text argument")
    ] = 38
    CmdResults: Annotated[
        int, EnFieldAnnotation(doc="`#+results:` - source code block evaluation results")
    ] = 39
    CmdHeader: Annotated[
        int,
        EnFieldAnnotation(
            doc="`#+header:` - extended list of parameters passed to associated block"
        ),
    ] = 40
    CmdOptions: Annotated[
        int, EnFieldAnnotation(doc="`#+options:` - document-wide formatting options")
    ] = 41
    CmdTblfm: int = 42
    CmdCaption: Annotated[int, EnFieldAnnotation(doc="`#+caption:` command")] = 43
    CmdResult: Annotated[int, EnFieldAnnotation(doc="Command evaluation result")] = 44
    CmdCallCode: Annotated[
        int, EnFieldAnnotation(doc="Call to named source code block.")
    ] = 45
    CmdFlag: Annotated[
        int,
        EnFieldAnnotation(
            doc="Flag for source code block. For example `-n`, which is used to to make source code block export with lines"
        ),
    ] = 46
    CmdLatexClass: int = 47
    CmdLatexHeader: int = 48
    CmdLatexCompiler: int = 49
    CmdLatexClassOptions: int = 50
    CmdHtmlHead: int = 51
    CmdColumns: Annotated[
        int,
        EnFieldAnnotation(
            doc="`#+columns:` line command for specifying formatting of the org-mode clock table visualization on per-file basis."
        ),
    ] = 52
    CmdPropertyArgs: Annotated[int, EnFieldAnnotation(doc="`#+property:` command")] = 53
    CmdPropertyText: Annotated[int, EnFieldAnnotation(doc="`#+property:` command")] = 54
    CmdPropertyRaw: Annotated[int, EnFieldAnnotation(doc="`#+property:` command")] = 55
    CmdFiletags: Annotated[int, EnFieldAnnotation(doc="`#+filetags:` line command")] = 56
    CmdKeywords: int = 57
    BlockVerbatimMultiline: Annotated[
        int,
        EnFieldAnnotation(
            doc="Verbatim mulitiline block that *might* be a part of `orgMultilineCommand` (in case of `#+begin-src`), but not necessarily. Can also be a part of =quote= and =example= multiline blocks."
        ),
    ] = 58
    CodeLine: Annotated[int, EnFieldAnnotation(doc="Single line of source code")] = 59
    CodeText: Annotated[int, EnFieldAnnotation(doc="Block of source code text")] = 60
    CodeTangle: Annotated[
        int, EnFieldAnnotation(doc="Single tangle target in the code block")
    ] = 61
    CodeCallout: Annotated[
        int, EnFieldAnnotation(doc="`(refs:` callout in the source code")
    ] = 62
    BlockCode: int = 63
    BlockQuote: Annotated[
        int, EnFieldAnnotation(doc="`#+begin_quote:` block in code")
    ] = 64
    BlockComment: Annotated[
        int, EnFieldAnnotation(doc="`#+begin_comment:` block in code")
    ] = 65
    BlockCenter: int = 66
    BlockVerse: int = 67
    BlockExample: Annotated[int, EnFieldAnnotation(doc="Verbatim example text block")] = (
        68
    )
    BlockExport: int = 69
    BlockDetails: Annotated[int, EnFieldAnnotation(doc="`#+begin_details`  section")] = 70
    BlockSummary: Annotated[int, EnFieldAnnotation(doc="`#+begin_summary` section")] = 71
    BlockDynamicFallback: Annotated[
        int, EnFieldAnnotation(doc="#+begin: <name> section")
    ] = 72
    BlockCustomText: Annotated[
        int, EnFieldAnnotation(doc="#+begin_<any> section for text blocks")
    ] = 73
    BlockCustomRaw: Annotated[
        int, EnFieldAnnotation(doc="#+begin_<any> section for raw content blocks")
    ] = 74
    BigIdent: Annotated[
        int, EnFieldAnnotation(doc="full-uppsercase identifier such as `MUST` or `TODO`")
    ] = 75
    Bold: Annotated[
        int,
        EnFieldAnnotation(
            doc='Region of text with formatting, which contains standalone words -\n     can itself contain subnodes, which allows to represent nested\n     formatting regions, such as `*bold /italic/*` text. Particular type\n     of identifier is stored in string form in `str` field for `OrgNode`\n     -- bold is represented as `"*"`, italic as `/` and so on. In case\n     of explicit open/close pairs only opening one is stored.\n\n     NOTE: when structured sentences are enabled, regular punctuation\n     elements like `some text (notes)` are also represented as `Word,\n     Word, Markup(str: "(", [Word])` - e.g. structure is not fully flat.'
        ),
    ] = 76
    ErrorInfoToken: Annotated[
        int,
        EnFieldAnnotation(doc="Error leaf node inserted into the parse tree on failure"),
    ] = 77
    ErrorSkipGroup: Annotated[
        int,
        EnFieldAnnotation(
            doc="Parent node for one or more tokens skipped during error recovery"
        ),
    ] = 78
    ErrorSkipToken: Annotated[
        int,
        EnFieldAnnotation(
            doc="Single token node skipped while the parser searched for recovery point"
        ),
    ] = 79
    Italic: int = 80
    Verbatim: int = 81
    Backtick: int = 82
    Underline: int = 83
    Strike: int = 84
    Quote: int = 85
    Angle: int = 86
    Monospace: int = 87
    Par: int = 88
    CriticMarkStructure: int = 89
    InlineMath: Annotated[
        int,
        EnFieldAnnotation(
            doc="Inline latex math. Contains latex math body - either from `$dollar-wrapped$` or `\\(paren-wrapped\\)` inline text."
        ),
    ] = 90
    DisplayMath: Annotated[
        int,
        EnFieldAnnotation(
            doc="Inline display latex math from `$$double-dollar$$` or `\\[bracket-wrapped\\]` code."
        ),
    ] = 91
    Space: Annotated[
        int, EnFieldAnnotation(doc="Space or tab character in regular text")
    ] = 92
    Punctuation: int = 93
    Colon: int = 94
    Word: Annotated[
        int,
        EnFieldAnnotation(
            doc="Regular word - technically not different from `orgIdent`, but defined separately to disiguish between places where special syntax is required and free-form text."
        ),
    ] = 95
    Escaped: Annotated[
        int, EnFieldAnnotation(doc="Escaped formatting character in the text")
    ] = 96
    Newline: int = 97
    RawLink: Annotated[
        int, EnFieldAnnotation(doc="Raw unwrapped link that was pasted in text")
    ] = 98
    Link: Annotated[
        int,
        EnFieldAnnotation(
            doc="External or internal link. Consists of one or two elements - target\n     (url, file location etc.) and description (`orgParagraph` of text).\n     Description might be empty, and represented as empty node in this\n     case. For external links particular formatting of the address is\n     not handled by parser and instead contains raw string from input\n     text."
        ),
    ] = 99
    Macro: Annotated[
        int,
        EnFieldAnnotation(
            doc="Org-mode macro replacement - during export each macro is expanded\n     and evaluated according to it's environment. Body of the macro is\n     not parsed fully during org-mode evaluation, but is checked for\n     correct parenthesis balance (as macro might contain elisp code)"
        ),
    ] = 100
    Symbol: Annotated[
        int,
        EnFieldAnnotation(
            doc="Special symbol that should be exported differently to various backends - greek letters (`\alpha`), mathematical notations and so on."
        ),
    ] = 101
    StaticActiveTime: int = 102
    StaticInactiveTime: int = 103
    DynamicActiveTime: int = 104
    DiaryTime: int = 105
    DynamicInactiveTime: Annotated[
        int,
        EnFieldAnnotation(
            doc="Single date and time entry (active or inactive),, possibly with repeater interval. Is not parsed directly, and instead contains `orgRawText` that can be parsed later"
        ),
    ] = 106
    TimeRange: Annotated[
        int,
        EnFieldAnnotation(doc="Date and time range format - two `orgDateTime` entries"),
    ] = 107
    SimpleTime: Annotated[
        int,
        EnFieldAnnotation(
            doc="Result of the time range evaluation or trailing annotation a subtree"
        ),
    ] = 108
    HashTag: int = 109
    MetaSymbol: Annotated[
        int, EnFieldAnnotation(doc="`\\sym{}` with explicit arguments")
    ] = 110
    AtMention: Annotated[int, EnFieldAnnotation(doc="`@user`")] = 111
    Placeholder: Annotated[
        int,
        EnFieldAnnotation(
            doc="Placeholder entry in text, usually writte like `<text to replace>`"
        ),
    ] = 112
    RadioTarget: Annotated[int, EnFieldAnnotation(doc="`<<<RADIO>>>`")] = 113
    Target: Annotated[int, EnFieldAnnotation(doc="`<<TARGET>>`")] = 114
    SrcInlineCode: Annotated[
        int,
        EnFieldAnnotation(
            doc="inline piece of code (such as `src_nim`),. Latter is different from regular monospaced text inside of `~~` pair as it contains additional internal structure, optional parameter for code evaluation etc."
        ),
    ] = 115
    InlineCallCode: Annotated[
        int, EnFieldAnnotation(doc="Call to named source code block.")
    ] = 116
    InlineExport: Annotated[
        int,
        EnFieldAnnotation(
            doc="Passthrough block. Inline, multiline, or single-line. Syntax is `@@<backend-name>:<any-body>@@`. Has line and block syntax respectively"
        ),
    ] = 117
    InlineComment: int = 118
    RawText: Annotated[
        int,
        EnFieldAnnotation(
            doc="Raw string of text from input buffer. Things like particular syntax details of every single command, link formats are not handled in parser, deferring formatting to future processing layers "
        ),
    ] = 119
    SubtreeDescription: Annotated[int, EnFieldAnnotation(doc="`:description:` entry")] = (
        120
    )
    SubtreeUrgency: int = 121
    DrawerLogbook: Annotated[
        int, EnFieldAnnotation(doc="`:logbook:` entry storing note information")
    ] = 122
    Drawer: Annotated[
        int,
        EnFieldAnnotation(
            doc="Single enclosed drawer like `:properties: ... :end:` or `:logbook: ... :end:`"
        ),
    ] = 123
    DrawerPropertyList: int = 124
    DrawerProperty: Annotated[int, EnFieldAnnotation(doc="`:property:` drawer")] = 125
    Subtree: Annotated[int, EnFieldAnnotation(doc="Section subtree")] = 126
    SubtreeTimes: Annotated[
        int, EnFieldAnnotation(doc="Time? associated with subtree entry")
    ] = 127
    SubtreeStars: int = 128
    SubtreeCompletion: Annotated[
        int,
        EnFieldAnnotation(
            doc="Task compleation cookie, indicated either in percents of completion, or as `<done>/<todo>` ratio."
        ),
    ] = 129
    SubtreeImportance: Annotated[
        int,
        EnFieldAnnotation(
            doc="Subtree importance level, such as `[#A]` or `[#B]`. Default org-mode only allows single character for contents inside of `[]`, but this parser makes it possible to use any regular identifier, such as `[#urgent]`."
        ),
    ] = 130


class OrgTokenKind(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    Ampersand: int = 0
    AngleBegin: int = 1
    AngleEnd: int = 2
    AnyPunct: int = 3
    Asterisk: int = 4
    At: int = 5
    Backtick: int = 6
    BigIdent: int = 7
    BoldBegin: int = 8
    BoldEnd: int = 9
    BoldUnknown: int = 10
    BraceBegin: int = 11
    BraceEnd: int = 12
    Checkbox: int = 13
    Circumflex: int = 14
    CmdAdmonitionEnd: int = 15
    CmdAttr: int = 16
    CmdAuthor: int = 17
    CmdBindRaw: int = 18
    CmdCall: int = 19
    CmdCaption: int = 20
    CmdCategoryRaw: int = 21
    CmdCell: int = 22
    CmdCellBegin: int = 23
    CmdCellEnd: int = 24
    CmdCenterBegin: int = 25
    CmdCenterEnd: int = 26
    CmdColonIdent: int = 27
    CmdColumns: int = 28
    CmdCommentBegin: int = 29
    CmdCommentEnd: int = 30
    CmdConstants: int = 31
    CmdContentBegin: int = 32
    CmdContentEnd: int = 33
    CmdCreator: int = 34
    CmdCustomRaw: int = 35
    CmdDateRaw: int = 36
    CmdDescription: int = 37
    CmdDrawersRaw: int = 38
    CmdDynamicBlockBegin: Annotated[
        int, EnFieldAnnotation(doc="`#+begin:` with the unspecified name")
    ] = 39
    CmdDynamicBlockEnd: Annotated[
        int, EnFieldAnnotation(doc="`#+end:` matching with `#+begin:`")
    ] = 40
    CmdCustomTextBlockBegin: Annotated[
        int, EnFieldAnnotation(doc="`#+begin_` with the text content inside")
    ] = 41
    CmdCustomTextBlockEnd: int = 42
    CmdCustomRawBlockBegin: Annotated[
        int, EnFieldAnnotation(doc="`#+begin_` block with the raw string")
    ] = 43
    CmdCustomRawBlockLine: int = 44
    CmdCustomRawBlockEnd: int = 45
    CmdEmailRaw: int = 46
    CmdExampleBegin: int = 47
    CmdExampleEnd: int = 48
    CmdExampleLine: int = 49
    CmdExcludeTagsRaw: int = 50
    CmdExportBegin: int = 51
    CmdExportEnd: int = 52
    CmdExportLine: int = 53
    CmdFiletags: int = 54
    CmdFlag: int = 55
    CmdHeader: int = 56
    CmdHtmlHeadRaw: int = 57
    CmdInclude: int = 58
    CmdLanguage: int = 59
    CmdLatexClass: int = 60
    CmdLatexClassOptions: int = 61
    CmdLatexCompiler: int = 62
    CmdLatexHeader: int = 63
    CmdLatexHeaderExtraRaw: int = 64
    CmdLinkRaw: int = 65
    CmdMacroRaw: int = 66
    CmdName: int = 67
    CmdOptions: int = 68
    CmdPrefix: int = 69
    CmdPrioritiesRaw: int = 70
    CmdPropertyArgs: int = 71
    CmdPropertyRaw: int = 72
    CmdPropertyText: int = 73
    CmdQuoteBegin: int = 74
    CmdQuoteEnd: int = 75
    CmdRawArg: int = 76
    CmdResults: int = 77
    CmdRow: int = 78
    CmdRowBegin: int = 79
    CmdRowEnd: int = 80
    CmdSelectTagsRaw: int = 81
    CmdSeqTodoRaw: int = 82
    CmdKeywordsRaw: int = 83
    CmdSetupfileRaw: int = 84
    CmdSrcBegin: int = 85
    CmdSrcEnd: int = 86
    CmdStartup: int = 87
    CmdTableBegin: int = 88
    CmdTableEnd: int = 89
    CmdTagsRaw: int = 90
    CmdTblfm: int = 91
    CmdTitle: int = 92
    CmdVerseBegin: int = 93
    CmdVerseEnd: int = 94
    Colon: int = 95
    ColonArgumentsProperty: int = 96
    ColonEnd: int = 97
    ColonExampleLine: int = 98
    ColonLiteralProperty: int = 99
    ColonLogbook: int = 100
    ColonProperties: int = 101
    ColonPropertyText: int = 102
    Comma: int = 103
    Comment: int = 104
    CriticAddBegin: int = 105
    CriticAddEnd: int = 106
    CriticCommentBegin: int = 107
    CriticCommentEnd: int = 108
    CriticDeleteBegin: int = 109
    CriticDeleteEnd: int = 110
    CriticHighlightBegin: int = 111
    CriticHighlightEnd: int = 112
    CriticReplaceBegin: int = 113
    CriticReplaceEnd: int = 114
    CriticReplaceMiddle: int = 115
    CurlyBegin: int = 116
    CurlyEnd: int = 117
    Date: int = 118
    Dedent: int = 119
    Dollar: int = 120
    DoubleAngleBegin: int = 121
    DoubleAngleEnd: int = 122
    DoubleColon: int = 123
    DoubleDash: int = 124
    DoubleHash: int = 125
    DoubleQuote: int = 126
    DoubleSlash: int = 127
    ActiveDynamicTimeContent: int = 128
    InactiveDynamicTimeContent: int = 129
    AgendaDiaryTimeContent: Annotated[
        int,
        EnFieldAnnotation(
            doc="`%%(` at the start of the line in the subtree, denoting the start of the dynamic agenda."
        ),
    ] = 130
    EndOfFile: int = 131
    Equals: int = 132
    Escaped: int = 133
    Exclamation: int = 134
    FootnoteInlineBegin: Annotated[
        int, EnFieldAnnotation(doc="`[fn::` with the inline definition")
    ] = 135
    FootnoteLinked: int = 136
    ForwardSlash: int = 137
    HashIdent: int = 138
    HashTagBegin: int = 139
    Indent: int = 140
    InlineExportBackend: int = 141
    InlineExportContent: int = 142
    ItalicBegin: int = 143
    ItalicEnd: int = 144
    ItalicUnknown: int = 145
    LatexInlineRaw: int = 146
    LatexParBegin: int = 147
    LatexParEnd: int = 148
    LatexBraceBegin: int = 149
    LatexBraceEnd: int = 150
    LatexDollar1Begin: int = 151
    LatexDollar1End: int = 152
    LatexDollar2Begin: int = 153
    LatexDollar2End: int = 154
    LeadingMinus: int = 155
    LeadingNumber: int = 156
    LeadingPipe: int = 157
    LeadingPlus: int = 158
    LeadingSpace: int = 159
    LeadingCharacter: Annotated[int, EnFieldAnnotation(doc="a)")] = 160
    LineCommand: int = 161
    LinkBegin: int = 162
    LinkDescriptionBegin: int = 163
    LinkDescriptionEnd: int = 164
    LinkEnd: int = 165
    LinkFull: int = 166
    LinkProtocol: int = 167
    LinkProtocolAttachment: int = 168
    LinkProtocolCustomId: int = 169
    LinkProtocolFile: int = 170
    LinkProtocolHttp: int = 171
    LinkProtocolId: int = 172
    LinkProtocolInternal: int = 173
    LinkProtocolTitle: int = 174
    LinkSplit: int = 175
    LinkTarget: int = 176
    LinkTargetBegin: int = 177
    LinkTargetEnd: int = 178
    LinkTargetFile: int = 179
    ListBegin: int = 180
    ListEnd: int = 181
    ListItemBegin: int = 182
    ListItemEnd: int = 183
    LongNewline: int = 184
    MediumNewline: int = 185
    Minus: int = 186
    MiscUnicode: int = 187
    MonospaceBegin: int = 188
    MonospaceEnd: int = 189
    MonospaceUnknown: int = 190
    Newline: int = 191
    Number: int = 192
    ParBegin: int = 193
    ParEnd: int = 194
    Percent: int = 195
    Pipe: int = 196
    Placeholder: int = 197
    Plus: int = 198
    Punctuation: int = 199
    RawText: int = 200
    SameIndent: int = 201
    Semicolon: int = 202
    SingleQuote: int = 203
    SrcContent: int = 204
    StmtListBegin: int = 205
    StmtListEnd: int = 206
    StrikeBegin: int = 207
    StrikeEnd: int = 208
    StrikeUnknown: int = 209
    SubtreeCompletion: int = 210
    SubtreePriority: int = 211
    SubtreeStars: int = 212
    Symbol: int = 213
    TableSeparator: int = 214
    TextSeparator: int = 215
    TextSrcBegin: int = 216
    Tilda: int = 217
    Time: int = 218
    TimeArrow: int = 219
    TimeRepeaterDuration: int = 220
    TimeRepeaterSpec: int = 221
    TimeWarnPeriod: int = 222
    TrailingPipe: int = 223
    TreeClock: int = 224
    TreeTime: int = 225
    TripleAngleBegin: int = 226
    TripleAngleEnd: int = 227
    Underline: int = 228
    UnderlineBegin: int = 229
    UnderlineEnd: int = 230
    UnderlineUnknown: int = 231
    Unknown: int = 232
    VerbatimBegin: int = 233
    VerbatimEnd: int = 234
    VerbatimUnknown: int = 235
    Whitespace: int = 236
    Word: int = 237


class OrgJsonKind(M.Enum):
    __config__(backend=dict(cpp=dict(org_groups=OrgTypeGroup.FULL_ENUMS)))

    Null: int = 0
    Object: int = 1
    Array: int = 2
    String: int = 3
    Boolean: int = 4
    Int: int = 5
    Float: int = 6


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
        tokenKind: M._T["OrgTokenKind"]
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
