/* clang-format off */
#undef slots
#define PYBIND11_DETAILED_ERROR_MESSAGES
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
PYBIND11_MAKE_OPAQUE(std::vector<GraphPoint>)
PYBIND11_MAKE_OPAQUE(Vec<GraphPoint>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphSize>)
PYBIND11_MAKE_OPAQUE(Vec<GraphSize>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphLayoutIR::IrEdge>)
PYBIND11_MAKE_OPAQUE(Vec<GraphLayoutIR::IrEdge>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphConstraint>)
PYBIND11_MAKE_OPAQUE(Vec<GraphConstraint>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphLayoutIR::Subgraph>)
PYBIND11_MAKE_OPAQUE(Vec<GraphLayoutIR::Subgraph>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<GraphLayoutIR::IrEdge, GraphSize>)
PYBIND11_MAKE_OPAQUE(UnorderedMap<GraphLayoutIR::IrEdge, GraphSize>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphRect>)
PYBIND11_MAKE_OPAQUE(Vec<GraphRect>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<GraphLayoutIR::IrEdge, GraphLayoutIR::Edge>)
PYBIND11_MAKE_OPAQUE(UnorderedMap<GraphLayoutIR::IrEdge, GraphLayoutIR::Edge>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphLayoutIR::Result::Subgraph>)
PYBIND11_MAKE_OPAQUE(Vec<GraphLayoutIR::Result::Subgraph>)
PYBIND11_MAKE_OPAQUE(std::vector<Vec<int>>)
PYBIND11_MAKE_OPAQUE(Vec<Vec<int>>)
PYBIND11_MAKE_OPAQUE(std::vector<int>)
PYBIND11_MAKE_OPAQUE(Vec<int>)
PYBIND11_MAKE_OPAQUE(std::vector<Vec>)
PYBIND11_MAKE_OPAQUE(Vec<Vec>)
PYBIND11_MAKE_OPAQUE(std::vector)
PYBIND11_MAKE_OPAQUE(Vec)
PYBIND11_MODULE(pyhaxorg, m) {
  bind_vector<GraphPoint>(m, "VecOfGraphPoint");
  bind_vector<GraphSize>(m, "VecOfGraphSize");
  bind_vector<GraphLayoutIR::IrEdge>(m, "VecOfGraphLayoutIRIrEdge");
  bind_vector<GraphConstraint>(m, "VecOfGraphConstraint");
  bind_vector<GraphLayoutIR::Subgraph>(m, "VecOfGraphLayoutIRSubgraph");
  bind_unordered_map<GraphLayoutIR::IrEdge, GraphSize>(m, "UnorderedMapOfGraphLayoutIRIrEdgeGraphSize");
  bind_vector<GraphRect>(m, "VecOfGraphRect");
  bind_unordered_map<GraphLayoutIR::IrEdge, GraphLayoutIR::Edge>(m, "UnorderedMapOfGraphLayoutIRIrEdgeGraphLayoutIREdge");
  bind_vector<GraphLayoutIR::Result::Subgraph>(m, "VecOfGraphLayoutIRResultSubgraph");
  bind_vector<Vec<int>>(m, "VecOfVecOfint");
  bind_vector<int>(m, "VecOfint");
  bind_vector<Vec>(m, "VecOfVec");
  bind_vector<>(m, "Vec");
  bind_enum_iterator<OrgSpecName>(m, "OrgSpecName");
  pybind11::enum_<OrgSpecName>(m, "OrgSpecName")
    .value("Unnamed", OrgSpecName::Unnamed)
    .value("Result", OrgSpecName::Result)
    .value("Year", OrgSpecName::Year)
    .value("Day", OrgSpecName::Day)
    .value("Clock", OrgSpecName::Clock)
    .value("Repeater", OrgSpecName::Repeater)
    .value("Zone", OrgSpecName::Zone)
    .value("Link", OrgSpecName::Link)
    .value("Tags", OrgSpecName::Tags)
    .value("Tag", OrgSpecName::Tag)
    .value("State", OrgSpecName::State)
    .value("Protocol", OrgSpecName::Protocol)
    .value("Desc", OrgSpecName::Desc)
    .value("Times", OrgSpecName::Times)
    .value("Drawer", OrgSpecName::Drawer)
    .value("Args", OrgSpecName::Args)
    .value("Name", OrgSpecName::Name)
    .value("Definition", OrgSpecName::Definition)
    .value("Body", OrgSpecName::Body)
    .value("HeaderArgs", OrgSpecName::HeaderArgs)
    .value("File", OrgSpecName::File)
    .value("Kind", OrgSpecName::Kind)
    .value("Lang", OrgSpecName::Lang)
    .value("Prefix", OrgSpecName::Prefix)
    .value("Text", OrgSpecName::Text)
    .value("Todo", OrgSpecName::Todo)
    .value("Importance", OrgSpecName::Importance)
    .value("Title", OrgSpecName::Title)
    .value("Completion", OrgSpecName::Completion)
    .value("Head", OrgSpecName::Head)
    .value("Subnodes", OrgSpecName::Subnodes)
    .value("Properties", OrgSpecName::Properties)
    .value("Logbook", OrgSpecName::Logbook)
    .value("Description", OrgSpecName::Description)
    .value("Logs", OrgSpecName::Logs)
    .value("Newstate", OrgSpecName::Newstate)
    .value("Oldstate", OrgSpecName::Oldstate)
    .value("Time", OrgSpecName::Time)
    .value("From", OrgSpecName::From)
    .value("EndArgs", OrgSpecName::EndArgs)
    .value("Flags", OrgSpecName::Flags)
    .value("Value", OrgSpecName::Value)
    .value("Assoc", OrgSpecName::Assoc)
    .value("Main", OrgSpecName::Main)
    .value("Hash", OrgSpecName::Hash)
    .value("Bullet", OrgSpecName::Bullet)
    .value("Counter", OrgSpecName::Counter)
    .value("Checkbox", OrgSpecName::Checkbox)
    .value("Header", OrgSpecName::Header)
    .value("To", OrgSpecName::To)
    .value("Diff", OrgSpecName::Diff)
    .value("Property", OrgSpecName::Property)
    .value("Subname", OrgSpecName::Subname)
    .value("Values", OrgSpecName::Values)
    .value("Cells", OrgSpecName::Cells)
    .value("Rows", OrgSpecName::Rows)
    .value("Lines", OrgSpecName::Lines)
    .value("Chunks", OrgSpecName::Chunks)
    .value("InheritanceMode", OrgSpecName::InheritanceMode)
    .value("MainSetRule", OrgSpecName::MainSetRule)
    .value("SubSetRule", OrgSpecName::SubSetRule)
    .def("__iter__", [](OrgSpecName _self) -> PyEnumIterator<OrgSpecName> {
                     return
                     PyEnumIterator<OrgSpecName>
                     ();
                     })
    ;
  bind_enum_iterator<OrgNodeKind>(m, "OrgNodeKind");
  pybind11::enum_<OrgNodeKind>(m, "OrgNodeKind")
    .value("None", OrgNodeKind::None, R"RAW(Default valye for node - invalid state)RAW")
    .value("Document", OrgNodeKind::Document, R"RAW(Toplevel part of the ast, not created by parser, and only used in `semorg` stage)RAW")
    .value("Empty", OrgNodeKind::Empty, R"RAW(Empty node - valid state that does not contain any value)RAW")
    .value("InlineStmtList", OrgNodeKind::InlineStmtList)
    .value("StmtList", OrgNodeKind::StmtList, R"RAW(List of statements, possibly recursive. Used as toplevel part of the document, in recursive parsing of subtrees, or as regular list, in cases where multiple subnodes have to be grouped together.)RAW")
    .value("Checkbox", OrgNodeKind::Checkbox, R"RAW(Single checkbox item like `[X]` or `[-]`)RAW")
    .value("List", OrgNodeKind::List)
    .value("Bullet", OrgNodeKind::Bullet, R"RAW(List item prefix)RAW")
    .value("ListItem", OrgNodeKind::ListItem)
    .value("ListTag", OrgNodeKind::ListTag, R"RAW(Auxilliary wrapper for the paragraph placed at the start of the description list.)RAW")
    .value("Counter", OrgNodeKind::Counter)
    .value("File", OrgNodeKind::File)
    .value("ColonExample", OrgNodeKind::ColonExample, R"RAW(Colon example block)RAW")
    .value("TextSeparator", OrgNodeKind::TextSeparator, R"RAW(Long horizontal line `----`)RAW")
    .value("Paragraph", OrgNodeKind::Paragraph, R"RAW(Single 'paragraph' of text. Used as generic container for any place in AST where unordered sentence might be encountered (e.g. caption, link description) - not limited to actual paragraph)RAW")
    .value("AnnotatedParagraph", OrgNodeKind::AnnotatedParagraph, R"RAW(Annotated paragraph -- a wrapper around a regular paragraph kind with added admonition, footnote, list tag prefix and similar types. `[fn:ID] Some Text` is an annotated paragraph, just like `NOTE: Text` or `- Prefix :: Body` (in this case list header is an annotated paragraph))RAW")
    .value("TableRow", OrgNodeKind::TableRow, R"RAW(Horizontal table row)RAW")
    .value("TableCell", OrgNodeKind::TableCell, R"RAW(Single cell in row. Might contain anyting, including other tables, simple text paragraph etc.)RAW")
    .value("Table", OrgNodeKind::Table, R"RAW(Org-mode table)RAW")
    .value("InlineFootnote", OrgNodeKind::InlineFootnote, R"RAW(Inline footnote with text placed directly in the node body.)RAW")
    .value("Footnote", OrgNodeKind::Footnote, R"RAW(Footnote entry. Just as regular links - internal content is not parsed, and instead just cut out verbatim into target AST node.)RAW")
    .value("Cmd", OrgNodeKind::Cmd, R"RAW(Undefined single-line command -- most likely custom user-provided oe)RAW")
    .value("CmdArguments", OrgNodeKind::CmdArguments, R"RAW(Arguments for the command block)RAW")
    .value("CmdTitle", OrgNodeKind::CmdTitle, R"RAW(`#+title:` - full document title)RAW")
    .value("CmdAuthor", OrgNodeKind::CmdAuthor, R"RAW(`#+author:` Document author)RAW")
    .value("CmdCreator", OrgNodeKind::CmdCreator, R"RAW(`#+creator:` Document creator)RAW")
    .value("CmdInclude", OrgNodeKind::CmdInclude, R"RAW(`#+include:` - include other org-mode document (or subsection of it), source code or backend-specific chunk.)RAW")
    .value("CmdLanguage", OrgNodeKind::CmdLanguage, R"RAW(`#+language:`)RAW")
    .value("CmdAttr", OrgNodeKind::CmdAttr, R"RAW(`#+attr_html:`, `#+attr_image` etc.)RAW")
    .value("CmdStartup", OrgNodeKind::CmdStartup, R"RAW(`#+startup:`)RAW")
    .value("CmdName", OrgNodeKind::CmdName, R"RAW(`#+name:` - name of the associated entry)RAW")
    .value("CmdCustomTextCommand", OrgNodeKind::CmdCustomTextCommand, R"RAW(Line command with parsed text value)RAW")
    .value("CmdCustomArgsCommand", OrgNodeKind::CmdCustomArgsCommand, R"RAW(Line command with parsed argument list)RAW")
    .value("CmdCustomRawCommand", OrgNodeKind::CmdCustomRawCommand, R"RAW(Line command with raw text argument)RAW")
    .value("CmdResults", OrgNodeKind::CmdResults, R"RAW(`#+results:` - source code block evaluation results)RAW")
    .value("CmdHeader", OrgNodeKind::CmdHeader, R"RAW(`#+header:` - extended list of parameters passed to associated block)RAW")
    .value("CmdOptions", OrgNodeKind::CmdOptions, R"RAW(`#+options:` - document-wide formatting options)RAW")
    .value("CmdTblfm", OrgNodeKind::CmdTblfm)
    .value("CmdCaption", OrgNodeKind::CmdCaption, R"RAW(`#+caption:` command)RAW")
    .value("CmdResult", OrgNodeKind::CmdResult, R"RAW(Command evaluation result)RAW")
    .value("CmdCallCode", OrgNodeKind::CmdCallCode, R"RAW(Call to named source code block.)RAW")
    .value("CmdFlag", OrgNodeKind::CmdFlag, R"RAW(Flag for source code block. For example `-n`, which is used to to make source code block export with lines)RAW")
    .value("CmdKey", OrgNodeKind::CmdKey)
    .value("CmdValue", OrgNodeKind::CmdValue)
    .value("CmdNamedValue", OrgNodeKind::CmdNamedValue, R"RAW(Key-value pair for source code block call.)RAW")
    .value("CmdLatexClass", OrgNodeKind::CmdLatexClass)
    .value("CmdLatexHeader", OrgNodeKind::CmdLatexHeader)
    .value("CmdLatexCompiler", OrgNodeKind::CmdLatexCompiler)
    .value("CmdLatexClassOptions", OrgNodeKind::CmdLatexClassOptions)
    .value("CmdHtmlHead", OrgNodeKind::CmdHtmlHead)
    .value("CmdColumns", OrgNodeKind::CmdColumns, R"RAW(`#+columns:` line command for specifying formatting of the org-mode clock table visualization on per-file basis.)RAW")
    .value("CmdPropertyArgs", OrgNodeKind::CmdPropertyArgs, R"RAW(`#+property:` command)RAW")
    .value("CmdPropertyText", OrgNodeKind::CmdPropertyText, R"RAW(`#+property:` command)RAW")
    .value("CmdPropertyRaw", OrgNodeKind::CmdPropertyRaw, R"RAW(`#+property:` command)RAW")
    .value("CmdFiletags", OrgNodeKind::CmdFiletags, R"RAW(`#+filetags:` line command)RAW")
    .value("BlockVerbatimMultiline", OrgNodeKind::BlockVerbatimMultiline, R"RAW(Verbatim mulitiline block that *might* be a part of `orgMultilineCommand` (in case of `#+begin-src`), but not necessarily. Can also be a part of =quote= and =example= multiline blocks.)RAW")
    .value("CodeLine", OrgNodeKind::CodeLine, R"RAW(Single line of source code)RAW")
    .value("CodeText", OrgNodeKind::CodeText, R"RAW(Block of source code text)RAW")
    .value("CodeTangle", OrgNodeKind::CodeTangle, R"RAW(Single tangle target in the code block)RAW")
    .value("CodeCallout", OrgNodeKind::CodeCallout, R"RAW(`(refs:` callout in the source code)RAW")
    .value("BlockCode", OrgNodeKind::BlockCode)
    .value("BlockQuote", OrgNodeKind::BlockQuote, R"RAW(`#+begin_quote:` block in code)RAW")
    .value("BlockComment", OrgNodeKind::BlockComment, R"RAW(`#+begin_comment:` block in code)RAW")
    .value("BlockCenter", OrgNodeKind::BlockCenter)
    .value("BlockVerse", OrgNodeKind::BlockVerse)
    .value("BlockExample", OrgNodeKind::BlockExample, R"RAW(Verbatim example text block)RAW")
    .value("BlockExport", OrgNodeKind::BlockExport)
    .value("BlockDetails", OrgNodeKind::BlockDetails, R"RAW(`#+begin_details`  section)RAW")
    .value("BlockSummary", OrgNodeKind::BlockSummary, R"RAW(`#+begin_summary` section)RAW")
    .value("Ident", OrgNodeKind::Ident, R"RAW(regular identifier - `alnum + [-_]` characters for punctuation. Identifiers are compared and parsed in style-insensetive manner, meaning `CODE_BLOCK`, `code-block` and `codeblock` are identical.)RAW")
    .value("BigIdent", OrgNodeKind::BigIdent, R"RAW(full-uppsercase identifier such as `MUST` or `TODO`)RAW")
    .value("Bold", OrgNodeKind::Bold, R"RAW(Region of text with formatting, which contains standalone words -
     can itself contain subnodes, which allows to represent nested
     formatting regions, such as `*bold /italic/*` text. Particular type
     of identifier is stored in string form in `str` field for `OrgNode`
     -- bold is represented as `"*"`, italic as `/` and so on. In case
     of explicit open/close pairs only opening one is stored.

     NOTE: when structured sentences are enabled, regular punctuation
     elements like `some text (notes)` are also represented as `Word,
     Word, Markup(str: "(", [Word])` - e.g. structure is not fully flat.)RAW")
    .value("Italic", OrgNodeKind::Italic)
    .value("Verbatim", OrgNodeKind::Verbatim)
    .value("Backtick", OrgNodeKind::Backtick)
    .value("Underline", OrgNodeKind::Underline)
    .value("Strike", OrgNodeKind::Strike)
    .value("Quote", OrgNodeKind::Quote)
    .value("Angle", OrgNodeKind::Angle)
    .value("Monospace", OrgNodeKind::Monospace)
    .value("Par", OrgNodeKind::Par)
    .value("InlineMath", OrgNodeKind::InlineMath, R"RAW(Inline latex math. Contains latex math body - either from `$dollar-wrapped$` or `\(paren-wrapped\)` inline text.)RAW")
    .value("DisplayMath", OrgNodeKind::DisplayMath, R"RAW(Inline display latex math from `$$double-dollar$$` or `\[bracket-wrapped\]` code.)RAW")
    .value("Space", OrgNodeKind::Space, R"RAW(Space or tab character in regular text)RAW")
    .value("Punctuation", OrgNodeKind::Punctuation)
    .value("Colon", OrgNodeKind::Colon)
    .value("Word", OrgNodeKind::Word, R"RAW(Regular word - technically not different from `orgIdent`, but defined separately to disiguish between places where special syntax is required and free-form text.)RAW")
    .value("Escaped", OrgNodeKind::Escaped, R"RAW(Escaped formatting character in the text)RAW")
    .value("Newline", OrgNodeKind::Newline)
    .value("RawLink", OrgNodeKind::RawLink, R"RAW(Raw unwrapped link that was pasted in text)RAW")
    .value("Link", OrgNodeKind::Link, R"RAW(External or internal link. Consists of one or two elements - target
     (url, file location etc.) and description (`orgParagraph` of text).
     Description might be empty, and represented as empty node in this
     case. For external links particular formatting of the address is
     not handled by parser and instead contains raw string from input
     text.)RAW")
    .value("Macro", OrgNodeKind::Macro, R"RAW(Org-mode macro replacement - during export each macro is expanded
     and evaluated according to it's environment. Body of the macro is
     not parsed fully during org-mode evaluation, but is checked for
     correct parenthesis balance (as macro might contain elisp code))RAW")
    .value("Symbol", OrgNodeKind::Symbol, R"RAW(Special symbol that should be exported differently to various backends - greek letters (`lpha`), mathematical notations and so on.)RAW")
    .value("StaticActiveTime", OrgNodeKind::StaticActiveTime)
    .value("StaticInactiveTime", OrgNodeKind::StaticInactiveTime)
    .value("DynamicActiveTime", OrgNodeKind::DynamicActiveTime)
    .value("DynamicInactiveTime", OrgNodeKind::DynamicInactiveTime, R"RAW(Single date and time entry (active or inactive),, possibly with repeater interval. Is not parsed directly, and instead contains `orgRawText` that can be parsed later)RAW")
    .value("TimeRange", OrgNodeKind::TimeRange, R"RAW(Date and time range format - two `orgDateTime` entries)RAW")
    .value("SimpleTime", OrgNodeKind::SimpleTime, R"RAW(Result of the time range evaluation or trailing annotation a subtree)RAW")
    .value("HashTag", OrgNodeKind::HashTag)
    .value("MetaSymbol", OrgNodeKind::MetaSymbol, R"RAW(`\sym{}` with explicit arguments)RAW")
    .value("AtMention", OrgNodeKind::AtMention, R"RAW(`@user`)RAW")
    .value("Placeholder", OrgNodeKind::Placeholder, R"RAW(Placeholder entry in text, usually writte like `<text to replace>`)RAW")
    .value("RadioTarget", OrgNodeKind::RadioTarget, R"RAW(`<<<RADIO>>>`)RAW")
    .value("Target", OrgNodeKind::Target, R"RAW(`<<TARGET>>`)RAW")
    .value("SrcInlineCode", OrgNodeKind::SrcInlineCode, R"RAW(inline piece of code (such as `src_nim`),. Latter is different from regular monospaced text inside of `~~` pair as it contains additional internal structure, optional parameter for code evaluation etc.)RAW")
    .value("InlineCallCode", OrgNodeKind::InlineCallCode, R"RAW(Call to named source code block.)RAW")
    .value("InlineExport", OrgNodeKind::InlineExport, R"RAW(Passthrough block. Inline, multiline, or single-line. Syntax is `@@<backend-name>:<any-body>@@`. Has line and block syntax respectively)RAW")
    .value("InlineComment", OrgNodeKind::InlineComment)
    .value("RawText", OrgNodeKind::RawText, R"RAW(Raw string of text from input buffer. Things like particular syntax details of every single command, link formats are not handled in parser, deferring formatting to future processing layers )RAW")
    .value("SubtreeDescription", OrgNodeKind::SubtreeDescription, R"RAW(`:description:` entry)RAW")
    .value("SubtreeUrgency", OrgNodeKind::SubtreeUrgency)
    .value("DrawerLogbook", OrgNodeKind::DrawerLogbook, R"RAW(`:logbook:` entry storing note information)RAW")
    .value("Drawer", OrgNodeKind::Drawer, R"RAW(Single enclosed drawer like `:properties: ... :end:` or `:logbook: ... :end:`)RAW")
    .value("DrawerPropertyList", OrgNodeKind::DrawerPropertyList)
    .value("DrawerProperty", OrgNodeKind::DrawerProperty, R"RAW(`:property:` drawer)RAW")
    .value("Subtree", OrgNodeKind::Subtree, R"RAW(Section subtree)RAW")
    .value("SubtreeTimes", OrgNodeKind::SubtreeTimes, R"RAW(Time? associated with subtree entry)RAW")
    .value("SubtreeStars", OrgNodeKind::SubtreeStars)
    .value("SubtreeCompletion", OrgNodeKind::SubtreeCompletion, R"RAW(Task compleation cookie, indicated either in percents of completion, or as `<done>/<todo>` ratio.)RAW")
    .value("SubtreeImportance", OrgNodeKind::SubtreeImportance, R"RAW(Subtree importance level, such as `[#A]` or `[#B]`. Default org-mode only allows single character for contents inside of `[]`, but this parser makes it possible to use any regular identifier, such as `[#urgent]`.)RAW")
    .def("__iter__", [](OrgNodeKind _self) -> PyEnumIterator<OrgNodeKind> {
                     return
                     PyEnumIterator<OrgNodeKind>
                     ();
                     })
    ;
  bind_enum_iterator<OrgSemKind>(m, "OrgSemKind");
  pybind11::enum_<OrgSemKind>(m, "OrgSemKind")
    .def("__iter__", [](OrgSemKind _self) -> PyEnumIterator<OrgSemKind> {
                     return
                     PyEnumIterator<OrgSemKind>
                     ();
                     })
    ;
  pybind11::class_<GraphPoint>(m, "GraphPoint")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphPoint {
                        GraphPoint result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("x", &GraphPoint::x)
    .def_readwrite("y", &GraphPoint::y)
    .def("__repr__", [](GraphPoint _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphPoint _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphPath>(m, "GraphPath")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphPath {
                        GraphPath result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("points", &GraphPath::points)
    .def_readwrite("startPoint", &GraphPath::startPoint)
    .def_readwrite("endPoint", &GraphPath::endPoint)
    .def_readwrite("bezier", &GraphPath::bezier)
    .def("point",
         static_cast<void(GraphPath::*)(int, int)>(&GraphPath::point),
         pybind11::arg("x"),
         pybind11::arg("y"))
    .def("point",
         static_cast<void(GraphPath::*)(GraphPoint const&)>(&GraphPath::point),
         pybind11::arg("p"))
    .def("__repr__", [](GraphPath _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphPath _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphSize>(m, "GraphSize")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphSize {
                        GraphSize result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("w", &GraphSize::w)
    .def_readwrite("h", &GraphSize::h)
    .def("height", static_cast<int(GraphSize::*)() const>(&GraphSize::height))
    .def("width", static_cast<int(GraphSize::*)() const>(&GraphSize::width))
    .def("__repr__", [](GraphSize _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphSize _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphRect>(m, "GraphRect")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphRect {
                        GraphRect result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("left", &GraphRect::left)
    .def_readwrite("top", &GraphRect::top)
    .def_readwrite("width", &GraphRect::width)
    .def_readwrite("height", &GraphRect::height)
    .def("size", static_cast<GraphSize(GraphRect::*)() const>(&GraphRect::size))
    .def("setBottomLeft",
         static_cast<void(GraphRect::*)(int, int)>(&GraphRect::setBottomLeft),
         pybind11::arg("x"),
         pybind11::arg("y"))
    .def("setTopRight",
         static_cast<void(GraphRect::*)(int, int)>(&GraphRect::setTopRight),
         pybind11::arg("x"),
         pybind11::arg("y"))
    .def("setBottomLeft",
         static_cast<void(GraphRect::*)(GraphPoint const&)>(&GraphRect::setBottomLeft),
         pybind11::arg("p"))
    .def("setTopRight",
         static_cast<void(GraphRect::*)(GraphPoint const&)>(&GraphRect::setTopRight),
         pybind11::arg("p"))
    .def("__repr__", [](GraphRect _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphRect _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphConstraint>(m, "GraphConstraint")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphConstraint {
                        GraphConstraint result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](GraphConstraint _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphConstraint _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphConstraint::Align>(m, "GraphConstraintAlign")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphConstraint::Align {
                        GraphConstraint::Align result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](GraphConstraint::Align _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphConstraint::Align _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphConstraint::Align::Spec>(m, "GraphConstraintAlignSpec")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphConstraint::Align::Spec {
                        GraphConstraint::Align::Spec result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](GraphConstraint::Align::Spec _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphConstraint::Align::Spec _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphConstraint::Separate>(m, "GraphConstraintSeparate")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphConstraint::Separate {
                        GraphConstraint::Separate result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](GraphConstraint::Separate _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphConstraint::Separate _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphConstraint::MultiSeparate>(m, "GraphConstraintMultiSeparate")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphConstraint::MultiSeparate {
                        GraphConstraint::MultiSeparate result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](GraphConstraint::MultiSeparate _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphConstraint::MultiSeparate _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphConstraint::FixedRelative>(m, "GraphConstraintFixedRelative")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphConstraint::FixedRelative {
                        GraphConstraint::FixedRelative result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](GraphConstraint::FixedRelative _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphConstraint::FixedRelative _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphConstraint::PageBoundary>(m, "GraphConstraintPageBoundary")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphConstraint::PageBoundary {
                        GraphConstraint::PageBoundary result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](GraphConstraint::PageBoundary _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphConstraint::PageBoundary _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphLayoutIR>(m, "GraphLayoutIR")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphLayoutIR {
                        GraphLayoutIR result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("rectangles", &GraphLayoutIR::rectangles, R"RAW(\brief Nodes for the graph. Node is identified by the index in the
array of sizes. In the result value each original qsize is mapped
to the rectangle.)RAW")
    .def_readwrite("edges", &GraphLayoutIR::edges, R"RAW(\brief List of source-target pairs. Edge source/target IDs refer to
the size rectangles.)RAW")
    .def_readwrite("constraints", &GraphLayoutIR::constraints, R"RAW(\brief Cola constraints for graph layout. This part is
backend-specific.)RAW")
    .def_readwrite("subgraphs", &GraphLayoutIR::subgraphs)
    .def_readwrite("edgeLabels", &GraphLayoutIR::edgeLabels, R"RAW(\brief If some edge has a dedicated label of specified size.)RAW")
    .def_readwrite("width", &GraphLayoutIR::width)
    .def_readwrite("height", &GraphLayoutIR::height)
    .def_readwrite("graphName", &GraphLayoutIR::graphName, R"RAW(\brief Graph name. Backend-specific.)RAW")
    .def_readwrite("graphviz_size_scaling", &GraphLayoutIR::graphviz_size_scaling, R"RAW(\brief Which DPI to use when converting to and from graphviz sizes.
Backend-specific, 72 is the default used by graphviz.)RAW")
    .def("validate", static_cast<void(GraphLayoutIR::*)()>(&GraphLayoutIR::validate), R"RAW(\brief validate the edge/rectangle structure for debugging. Throws
assert failure if the structure is incorrect.)RAW")
    .def("doHolaConvert", static_cast<GraphLayoutIR::Result(GraphLayoutIR::*)()>(&GraphLayoutIR::doHolaConvert))
    .def("doColaConvert", static_cast<GraphLayoutIR::Result(GraphLayoutIR::*)()>(&GraphLayoutIR::doColaConvert))
    .def("__repr__", [](GraphLayoutIR _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphLayoutIR _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphLayoutIR::Subgraph>(m, "GraphLayoutIRSubgraph")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphLayoutIR::Subgraph {
                        GraphLayoutIR::Subgraph result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](GraphLayoutIR::Subgraph _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphLayoutIR::Subgraph _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphLayoutIR::Edge>(m, "GraphLayoutIREdge")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphLayoutIR::Edge {
                        GraphLayoutIR::Edge result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](GraphLayoutIR::Edge _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphLayoutIR::Edge _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphLayoutIR::Result>(m, "GraphLayoutIRResult")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphLayoutIR::Result {
                        GraphLayoutIR::Result result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("fixed", &GraphLayoutIR::Result::fixed, R"RAW(\brief Fixed node layout rectangles with absolute coordinates.
Subgraph nodes are also included. Edge label nodes are not
included.)RAW")
    .def_readwrite("lines", &GraphLayoutIR::Result::lines, R"RAW(\brief Mapping from the source-target edge pair to the edge
layout spec)RAW")
    .def_readwrite("bbox", &GraphLayoutIR::Result::bbox, R"RAW(\brief Bounding box for the whole rectangle)RAW")
    .def_readwrite("subgraphs", &GraphLayoutIR::Result::subgraphs, R"RAW(\brief Top-level list of subgraphs)RAW")
    .def_readwrite("subgraphPaths", &GraphLayoutIR::Result::subgraphPaths, R"RAW(\brief Flattened list of subgraphs in DFS order with paths)RAW")
    .def("getSubgraph",
         static_cast<GraphLayoutIR::Result::Subgraph const&(GraphLayoutIR::Result::*)(Vec<Vec> const&)>(&GraphLayoutIR::Result::getSubgraph),
         pybind11::arg("path"),
         R"RAW(\brief Get subgraph at path)RAW")
    .def("__repr__", [](GraphLayoutIR::Result _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphLayoutIR::Result _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphLayoutIR::Result::Subgraph>(m, "GraphLayoutIRResultSubgraph")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphLayoutIR::Result::Subgraph {
                        GraphLayoutIR::Result::Subgraph result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("bbox", &GraphLayoutIR::Result::Subgraph::bbox, R"RAW(\brief Bounding box for the rectangle content)RAW")
    .def_readwrite("subgraphs", &GraphLayoutIR::Result::Subgraph::subgraphs)
    .def("__repr__", [](GraphLayoutIR::Result::Subgraph _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphLayoutIR::Result::Subgraph _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphLayoutIR::ColaResult>(m, "GraphLayoutIRColaResult")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphLayoutIR::ColaResult {
                        GraphLayoutIR::ColaResult result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](GraphLayoutIR::ColaResult _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphLayoutIR::ColaResult _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphLayoutIR::ColaResult::EdgeData>(m, "GraphLayoutIRColaResultEdgeData")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphLayoutIR::ColaResult::EdgeData {
                        GraphLayoutIR::ColaResult::EdgeData result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](GraphLayoutIR::ColaResult::EdgeData _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphLayoutIR::ColaResult::EdgeData _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
}
/* clang-format on */