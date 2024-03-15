/* clang-format off */
#undef slots
#include <pybind11/pybind11.h>
#include <sem/SemOrg.hpp>
#include <pybind11/stl.h>
#include "pyhaxorg_manual_impl.hpp"
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Org>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Org>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Cell>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Cell>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Row>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Row>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::HashTag>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::HashTag>>)
PYBIND11_MAKE_OPAQUE(std::vector<Str>)
PYBIND11_MAKE_OPAQUE(Vec<Str>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::CmdArgument>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::CmdArgument>>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<Str, sem::SemId<sem::CmdArgument>>)
PYBIND11_MAKE_OPAQUE(UnorderedMap<Str, sem::SemId<sem::CmdArgument>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Code::Line::Part>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Code::Line::Part>)
PYBIND11_MAKE_OPAQUE(std::vector<int>)
PYBIND11_MAKE_OPAQUE(Vec<int>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Code::Switch>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Code::Switch>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Code::Line>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Code::Line>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Symbol::Param>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Symbol::Param>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<Str, Str>)
PYBIND11_MAKE_OPAQUE(UnorderedMap<Str, Str>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::SubtreeLog>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::SubtreeLog>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Subtree::Property>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Subtree::Property>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Subtree::Period>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Subtree::Period>)
PYBIND11_MAKE_OPAQUE(IntSet<sem::Subtree::Period::Kind>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Subtree>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Subtree>>)
PYBIND11_MODULE(pyhaxorg, m) {
  bind_vector<sem::SemId<sem::Org>>(m, "VecOfSemIdOfOrg");
  bind_vector<sem::SemId<sem::Cell>>(m, "VecOfSemIdOfCell");
  bind_vector<sem::SemId<sem::Row>>(m, "VecOfSemIdOfRow");
  bind_vector<sem::SemId<sem::HashTag>>(m, "VecOfSemIdOfHashTag");
  bind_vector<Str>(m, "VecOfStr");
  bind_vector<sem::SemId<sem::CmdArgument>>(m, "VecOfSemIdOfCmdArgument");
  bind_unordered_map<Str, sem::SemId<sem::CmdArgument>>(m, "UnorderedMapOfStrSemIdOfCmdArgument");
  bind_vector<sem::Code::Line::Part>(m, "VecOfCodeLinePart");
  bind_vector<int>(m, "VecOfint");
  bind_vector<sem::Code::Switch>(m, "VecOfCodeSwitch");
  bind_vector<sem::Code::Line>(m, "VecOfCodeLine");
  bind_vector<sem::Symbol::Param>(m, "VecOfSymbolParam");
  bind_unordered_map<Str, Str>(m, "UnorderedMapOfStrStr");
  bind_vector<sem::SemId<sem::SubtreeLog>>(m, "VecOfSemIdOfSubtreeLog");
  bind_vector<sem::Subtree::Property>(m, "VecOfSubtreeProperty");
  bind_vector<sem::Subtree::Period>(m, "VecOfSubtreePeriod");
  bind_int_set<sem::Subtree::Period::Kind>(m, "IntSetOfSubtreePeriodKind");
  bind_vector<sem::SemId<sem::Subtree>>(m, "VecOfSemIdOfSubtree");
  pybind11::class_<sem::Org, sem::SemId<sem::Org>>(m, "Org")
    .def_readwrite("loc", &sem::Org::loc, R"RAW(\brief Location of the node in the original source file)RAW")
    .def_readwrite("documentId", &sem::Org::documentId, R"RAW(\brief Application specific ID of the original document)RAW")
    .def_readwrite("subnodes", &sem::Org::subnodes, R"RAW(\brief List of subnodes.

Some of the derived nodes don't make the use of subnode list
(word, punctuation etc), but it was left on the top level of the
hierarchy for conveinience purposes. It is not expected that 'any'
node can have subnodes.)RAW")
    .def("getKind", static_cast<OrgSemKind(sem::Org::*)() const>(&sem::Org::getKind), R"RAW(\brief Get kind of this sem node)RAW")
    .def("isGenerated", static_cast<bool(sem::Org::*)() const>(&sem::Org::isGenerated), R"RAW(\brief Whether original node adapter is missing)RAW")
    .def("push_back",
         static_cast<void(sem::Org::*)(sem::SemId<sem::Org>)>(&sem::Org::push_back),
         pybind11::arg("sub"))
    .def("at",
         static_cast<sem::SemId<sem::Org>(sem::Org::*)(int) const>(&sem::Org::at),
         pybind11::arg("idx"),
         R"RAW(\brief Get subnode at specified index)RAW")
    .def("is_",
         static_cast<bool(sem::Org::*)(OrgSemKind) const>(&sem::Org::is),
         pybind11::arg("kind"))
    .def("__getitem__",
         static_cast<sem::SemId<sem::Org>(sem::Org::*)(int) const>(&sem::Org::at),
         pybind11::arg("idx"))
    .def("__iter__",
         [](sem::Org const& node) -> auto {
         return pybind11::make_iterator(node.subnodes.begin(), node.subnodes.end());
         },
         pybind11::keep_alive<0, 1>())
    ;
  pybind11::class_<LineCol>(m, "LineCol")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> LineCol {
                        LineCol result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("line", &LineCol::line)
    .def_readwrite("column", &LineCol::column)
    .def_readwrite("pos", &LineCol::pos)
    ;
  pybind11::class_<sem::Stmt, sem::SemId<sem::Stmt>, sem::Org>(m, "Stmt")
    .def_readwrite("attached", &sem::Stmt::attached)
    .def("getAttached",
         static_cast<Opt<sem::SemId<sem::Org>>(sem::Stmt::*)(OrgSemKind)>(&sem::Stmt::getAttached),
         pybind11::arg("kind"))
    ;
  pybind11::class_<sem::Inline, sem::SemId<sem::Inline>, sem::Org>(m, "Inline")
    ;
  pybind11::class_<sem::StmtList, sem::SemId<sem::StmtList>, sem::Org>(m, "StmtList")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::StmtList {
                        sem::StmtList result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Empty, sem::SemId<sem::Empty>, sem::Org>(m, "Empty")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Empty {
                        sem::Empty result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Cell, sem::SemId<sem::Cell>, sem::Org>(m, "Cell")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Cell {
                        sem::Cell result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Row, sem::SemId<sem::Row>, sem::Org>(m, "Row")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Row {
                        sem::Row result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("cells", &sem::Row::cells, R"RAW(List of cells on the row)RAW")
    ;
  pybind11::class_<sem::Table, sem::SemId<sem::Table>, sem::Stmt>(m, "Table")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Table {
                        sem::Table result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("rows", &sem::Table::rows, R"RAW(List of rows for the table)RAW")
    .def_readwrite("attached", &sem::Table::attached)
    .def("getAttached",
         static_cast<Opt<sem::SemId<sem::Org>>(sem::Table::*)(OrgSemKind)>(&sem::Table::getAttached),
         pybind11::arg("kind"))
    ;
  pybind11::class_<sem::HashTag, sem::SemId<sem::HashTag>, sem::Inline>(m, "HashTag")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::HashTag {
                        sem::HashTag result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("head", &sem::HashTag::head, R"RAW(Main part of the tag)RAW")
    .def_readwrite("subtags", &sem::HashTag::subtags, R"RAW(List of nested tags)RAW")
    .def("prefixMatch",
         static_cast<bool(sem::HashTag::*)(Vec<Str> const&) const>(&sem::HashTag::prefixMatch),
         pybind11::arg("prefix"),
         R"RAW(Check if list of tag names is a prefix for either of the nested hash tags in this one)RAW")
    ;
  pybind11::class_<sem::Footnote, sem::SemId<sem::Footnote>, sem::Inline>(m, "Footnote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Footnote {
                        sem::Footnote result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("tag", &sem::Footnote::tag, R"RAW(Footnote text target name)RAW")
    .def_readwrite("definition", &sem::Footnote::definition, R"RAW(Link to possibly resolved definition)RAW")
    ;
  pybind11::class_<sem::Completion, sem::SemId<sem::Completion>, sem::Inline>(m, "Completion")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Completion {
                        sem::Completion result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("done", &sem::Completion::done, R"RAW(Number of completed tasks)RAW")
    .def_readwrite("full", &sem::Completion::full, R"RAW(Full number of tasks)RAW")
    .def_readwrite("isPercent", &sem::Completion::isPercent, R"RAW(Use fraction or percent to display completion)RAW")
    ;
  pybind11::class_<sem::Paragraph, sem::SemId<sem::Paragraph>, sem::Stmt>(m, "Paragraph")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Paragraph {
                        sem::Paragraph result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attached", &sem::Paragraph::attached)
    .def("getAttached",
         static_cast<Opt<sem::SemId<sem::Org>>(sem::Paragraph::*)(OrgSemKind)>(&sem::Paragraph::getAttached),
         pybind11::arg("kind"))
    ;
  pybind11::class_<sem::AnnotatedParagraph::None>(m, "AnnotatedParagraphNone")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::AnnotatedParagraph::None {
                        sem::AnnotatedParagraph::None result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::AnnotatedParagraph::Footnote>(m, "AnnotatedParagraphFootnote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::AnnotatedParagraph::Footnote {
                        sem::AnnotatedParagraph::Footnote result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::AnnotatedParagraph::Footnote::name)
    ;
  pybind11::class_<sem::AnnotatedParagraph::Admonition>(m, "AnnotatedParagraphAdmonition")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::AnnotatedParagraph::Admonition {
                        sem::AnnotatedParagraph::Admonition result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::AnnotatedParagraph::Admonition::name, R"RAW(Prefix admonition for the paragraph)RAW")
    ;
  pybind11::class_<sem::AnnotatedParagraph::Timestamp>(m, "AnnotatedParagraphTimestamp")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::AnnotatedParagraph::Timestamp {
                        sem::AnnotatedParagraph::Timestamp result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("time", &sem::AnnotatedParagraph::Timestamp::time, R"RAW(Leading timestamp for the paragraph)RAW")
    ;
  bind_enum_iterator<sem::AnnotatedParagraph::AnnotationKind>(m, "AnnotatedParagraphAnnotationKind");
  pybind11::enum_<sem::AnnotatedParagraph::AnnotationKind>(m, "AnnotatedParagraphAnnotationKind")
    .value("None", sem::AnnotatedParagraph::AnnotationKind::None)
    .value("Footnote", sem::AnnotatedParagraph::AnnotationKind::Footnote)
    .value("Admonition", sem::AnnotatedParagraph::AnnotationKind::Admonition)
    .value("Timestamp", sem::AnnotatedParagraph::AnnotationKind::Timestamp)
    .def("__iter__", [](sem::AnnotatedParagraph::AnnotationKind _self) -> PyEnumIterator<sem::AnnotatedParagraph::AnnotationKind> {
                     return
                     PyEnumIterator<sem::AnnotatedParagraph::AnnotationKind>
                     ();
                     })
    ;
  pybind11::class_<sem::AnnotatedParagraph, sem::SemId<sem::AnnotatedParagraph>, sem::Stmt>(m, "AnnotatedParagraph")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::AnnotatedParagraph {
                        sem::AnnotatedParagraph result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &sem::AnnotatedParagraph::data)
    .def_readwrite("attached", &sem::AnnotatedParagraph::attached)
    .def("getNone", static_cast<sem::AnnotatedParagraph::None&(sem::AnnotatedParagraph::*)()>(&sem::AnnotatedParagraph::getNone))
    .def("getFootnote", static_cast<sem::AnnotatedParagraph::Footnote&(sem::AnnotatedParagraph::*)()>(&sem::AnnotatedParagraph::getFootnote))
    .def("getAdmonition", static_cast<sem::AnnotatedParagraph::Admonition&(sem::AnnotatedParagraph::*)()>(&sem::AnnotatedParagraph::getAdmonition))
    .def("getTimestamp", static_cast<sem::AnnotatedParagraph::Timestamp&(sem::AnnotatedParagraph::*)()>(&sem::AnnotatedParagraph::getTimestamp))
    .def("getAnnotationKind", static_cast<sem::AnnotatedParagraph::AnnotationKind(sem::AnnotatedParagraph::*)() const>(&sem::AnnotatedParagraph::getAnnotationKind))
    .def("getAttached",
         static_cast<Opt<sem::SemId<sem::Org>>(sem::AnnotatedParagraph::*)(OrgSemKind)>(&sem::AnnotatedParagraph::getAttached),
         pybind11::arg("kind"))
    ;
  pybind11::class_<sem::Format, sem::SemId<sem::Format>, sem::Org>(m, "Format")
    ;
  pybind11::class_<sem::Center, sem::SemId<sem::Center>, sem::Format>(m, "Center")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Center {
                        sem::Center result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Command, sem::SemId<sem::Command>, sem::Org>(m, "Command")
    ;
  pybind11::class_<sem::LineCommand, sem::SemId<sem::LineCommand>, sem::Command>(m, "LineCommand")
    ;
  pybind11::class_<sem::Standalone, sem::SemId<sem::Standalone>, sem::LineCommand>(m, "Standalone")
    ;
  pybind11::class_<sem::Attached, sem::SemId<sem::Attached>, sem::LineCommand>(m, "Attached")
    ;
  pybind11::class_<sem::Caption, sem::SemId<sem::Caption>, sem::Attached>(m, "Caption")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Caption {
                        sem::Caption result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Caption::text, R"RAW(Content description)RAW")
    ;
  pybind11::class_<sem::CmdName, sem::SemId<sem::CmdName>, sem::Attached>(m, "CmdName")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdName {
                        sem::CmdName result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::CmdResults, sem::SemId<sem::CmdResults>, sem::Attached>(m, "CmdResults")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdResults {
                        sem::CmdResults result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::CommandGroup, sem::SemId<sem::CommandGroup>, sem::Stmt>(m, "CommandGroup")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CommandGroup {
                        sem::CommandGroup result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attached", &sem::CommandGroup::attached)
    .def("getAttached",
         static_cast<Opt<sem::SemId<sem::Org>>(sem::CommandGroup::*)(OrgSemKind)>(&sem::CommandGroup::getAttached),
         pybind11::arg("kind"))
    ;
  pybind11::class_<sem::Block, sem::SemId<sem::Block>, sem::Command>(m, "Block")
    .def_readwrite("parameters", &sem::Block::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def("getParameter",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Block::*)(Str const&) const>(&sem::Block::getParameter),
         pybind11::arg("key"))
    ;
  pybind11::class_<sem::Tblfm, sem::SemId<sem::Tblfm>, sem::Command>(m, "Tblfm")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Tblfm {
                        sem::Tblfm result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Quote, sem::SemId<sem::Quote>, sem::Org>(m, "Quote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Quote {
                        sem::Quote result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::CommentBlock, sem::SemId<sem::CommentBlock>, sem::Org>(m, "CommentBlock")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CommentBlock {
                        sem::CommentBlock result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Verse, sem::SemId<sem::Verse>, sem::Block>(m, "Verse")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Verse {
                        sem::Verse result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("parameters", &sem::Verse::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def("getParameter",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Verse::*)(Str const&) const>(&sem::Verse::getParameter),
         pybind11::arg("key"))
    ;
  pybind11::class_<sem::Example, sem::SemId<sem::Example>, sem::Block>(m, "Example")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Example {
                        sem::Example result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("parameters", &sem::Example::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def("getParameter",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Example::*)(Str const&) const>(&sem::Example::getParameter),
         pybind11::arg("key"))
    ;
  pybind11::class_<sem::CmdArguments, sem::SemId<sem::CmdArguments>, sem::Org>(m, "CmdArguments")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdArguments {
                        sem::CmdArguments result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("positional", &sem::CmdArguments::positional, R"RAW(Positional arguments that had no keys)RAW")
    .def_readwrite("named", &sem::CmdArguments::named, R"RAW(Stored key-value mapping)RAW")
    .def("getParameter",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::CmdArguments::*)(Str const&) const>(&sem::CmdArguments::getParameter),
         pybind11::arg("key"))
    ;
  pybind11::class_<sem::CmdAttr, sem::SemId<sem::CmdAttr>, sem::Attached>(m, "CmdAttr")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdAttr {
                        sem::CmdAttr result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &sem::CmdAttr::target)
    .def_readwrite("parameters", &sem::CmdAttr::parameters, R"RAW(HTML attributes)RAW")
    ;
  pybind11::class_<sem::CmdArgument, sem::SemId<sem::CmdArgument>, sem::Org>(m, "CmdArgument")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdArgument {
                        sem::CmdArgument result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("key", &sem::CmdArgument::key, R"RAW(Key)RAW")
    .def_readwrite("value", &sem::CmdArgument::value, R"RAW(Value)RAW")
    .def("getInt", static_cast<Opt<int>(sem::CmdArgument::*)() const>(&sem::CmdArgument::getInt), R"RAW(Parse argument as integer value)RAW")
    .def("getBool", static_cast<Opt<bool>(sem::CmdArgument::*)() const>(&sem::CmdArgument::getBool), R"RAW(Get argument as bool)RAW")
    .def("getString", static_cast<Str(sem::CmdArgument::*)() const>(&sem::CmdArgument::getString), R"RAW(Get original string)RAW")
    ;
  bind_enum_iterator<sem::Export::Format>(m, "ExportFormat");
  pybind11::enum_<sem::Export::Format>(m, "ExportFormat")
    .value("Inline", sem::Export::Format::Inline, R"RAW(Export directly in the paragraph)RAW")
    .value("Line", sem::Export::Format::Line, R"RAW(Single line of export)RAW")
    .value("Block", sem::Export::Format::Block, R"RAW(Multiple lines of export)RAW")
    .def("__iter__", [](sem::Export::Format _self) -> PyEnumIterator<sem::Export::Format> {
                     return
                     PyEnumIterator<sem::Export::Format>
                     ();
                     })
    ;
  pybind11::class_<sem::Export, sem::SemId<sem::Export>, sem::Block>(m, "Export")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Export {
                        sem::Export result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("format", &sem::Export::format, R"RAW(Export block type)RAW")
    .def_readwrite("exporter", &sem::Export::exporter, R"RAW(Exporter backend name)RAW")
    .def_readwrite("placement", &sem::Export::placement, R"RAW(Customized position of the text in the final exporting document.)RAW")
    .def_readwrite("content", &sem::Export::content, R"RAW(Raw exporter content string)RAW")
    .def_readwrite("parameters", &sem::Export::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def("getParameter",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Export::*)(Str const&) const>(&sem::Export::getParameter),
         pybind11::arg("key"))
    ;
  pybind11::class_<sem::AdmonitionBlock, sem::SemId<sem::AdmonitionBlock>, sem::Block>(m, "AdmonitionBlock")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::AdmonitionBlock {
                        sem::AdmonitionBlock result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("parameters", &sem::AdmonitionBlock::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def("getParameter",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::AdmonitionBlock::*)(Str const&) const>(&sem::AdmonitionBlock::getParameter),
         pybind11::arg("key"))
    ;
  pybind11::class_<sem::Call, sem::SemId<sem::Call>, sem::Org>(m, "Call")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Call {
                        sem::Call result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::Call::name, R"RAW(Call target name)RAW")
    ;
  pybind11::class_<sem::Code::Line::Part::Raw>(m, "CodeLinePartRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Code::Line::Part::Raw {
                        sem::Code::Line::Part::Raw result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("code", &sem::Code::Line::Part::Raw::code)
    ;
  pybind11::class_<sem::Code::Line::Part::Callout>(m, "CodeLinePartCallout")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Code::Line::Part::Callout {
                        sem::Code::Line::Part::Callout result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::Code::Line::Part::Callout::name)
    ;
  pybind11::class_<sem::Code::Line::Part::Tangle>(m, "CodeLinePartTangle")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Code::Line::Part::Tangle {
                        sem::Code::Line::Part::Tangle result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &sem::Code::Line::Part::Tangle::target)
    ;
  bind_enum_iterator<sem::Code::Line::Part::Kind>(m, "CodeLinePartKind");
  pybind11::enum_<sem::Code::Line::Part::Kind>(m, "CodeLinePartKind")
    .value("Raw", sem::Code::Line::Part::Kind::Raw)
    .value("Callout", sem::Code::Line::Part::Kind::Callout)
    .value("Tangle", sem::Code::Line::Part::Kind::Tangle)
    .def("__iter__", [](sem::Code::Line::Part::Kind _self) -> PyEnumIterator<sem::Code::Line::Part::Kind> {
                     return
                     PyEnumIterator<sem::Code::Line::Part::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::Code::Line::Part>(m, "CodeLinePart")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Code::Line::Part {
                        sem::Code::Line::Part result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &sem::Code::Line::Part::data)
    .def("getRaw", static_cast<sem::Code::Line::Part::Raw&(sem::Code::Line::Part::*)()>(&sem::Code::Line::Part::getRaw))
    .def("getCallout", static_cast<sem::Code::Line::Part::Callout&(sem::Code::Line::Part::*)()>(&sem::Code::Line::Part::getCallout))
    .def("getTangle", static_cast<sem::Code::Line::Part::Tangle&(sem::Code::Line::Part::*)()>(&sem::Code::Line::Part::getTangle))
    .def("getKind", static_cast<sem::Code::Line::Part::Kind(sem::Code::Line::Part::*)() const>(&sem::Code::Line::Part::getKind))
    ;
  pybind11::class_<sem::Code::Line>(m, "CodeLine")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Code::Line {
                        sem::Code::Line result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("parts", &sem::Code::Line::parts, R"RAW(parts of the single line)RAW")
    ;
  pybind11::class_<sem::Code::Switch::LineStart>(m, "CodeSwitchLineStart")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Code::Switch::LineStart {
                        sem::Code::Switch::LineStart result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("start", &sem::Code::Switch::LineStart::start, R"RAW(First line number)RAW")
    .def_readwrite("extendLast", &sem::Code::Switch::LineStart::extendLast, R"RAW(Continue numbering from the previous block nstead of starting anew)RAW")
    ;
  pybind11::class_<sem::Code::Switch::CalloutFormat>(m, "CodeSwitchCalloutFormat")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Code::Switch::CalloutFormat {
                        sem::Code::Switch::CalloutFormat result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("format", &sem::Code::Switch::CalloutFormat::format)
    ;
  pybind11::class_<sem::Code::Switch::RemoveCallout>(m, "CodeSwitchRemoveCallout")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Code::Switch::RemoveCallout {
                        sem::Code::Switch::RemoveCallout result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("remove", &sem::Code::Switch::RemoveCallout::remove)
    ;
  pybind11::class_<sem::Code::Switch::EmphasizeLine>(m, "CodeSwitchEmphasizeLine")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Code::Switch::EmphasizeLine {
                        sem::Code::Switch::EmphasizeLine result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("line", &sem::Code::Switch::EmphasizeLine::line)
    ;
  pybind11::class_<sem::Code::Switch::Dedent>(m, "CodeSwitchDedent")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Code::Switch::Dedent {
                        sem::Code::Switch::Dedent result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &sem::Code::Switch::Dedent::value)
    ;
  bind_enum_iterator<sem::Code::Switch::Kind>(m, "CodeSwitchKind");
  pybind11::enum_<sem::Code::Switch::Kind>(m, "CodeSwitchKind")
    .value("LineStart", sem::Code::Switch::Kind::LineStart)
    .value("CalloutFormat", sem::Code::Switch::Kind::CalloutFormat)
    .value("RemoveCallout", sem::Code::Switch::Kind::RemoveCallout)
    .value("EmphasizeLine", sem::Code::Switch::Kind::EmphasizeLine)
    .value("Dedent", sem::Code::Switch::Kind::Dedent)
    .def("__iter__", [](sem::Code::Switch::Kind _self) -> PyEnumIterator<sem::Code::Switch::Kind> {
                     return
                     PyEnumIterator<sem::Code::Switch::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::Code::Switch>(m, "CodeSwitch")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Code::Switch {
                        sem::Code::Switch result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &sem::Code::Switch::data)
    .def("getLineStart", static_cast<sem::Code::Switch::LineStart&(sem::Code::Switch::*)()>(&sem::Code::Switch::getLineStart))
    .def("getCalloutFormat", static_cast<sem::Code::Switch::CalloutFormat&(sem::Code::Switch::*)()>(&sem::Code::Switch::getCalloutFormat))
    .def("getRemoveCallout", static_cast<sem::Code::Switch::RemoveCallout&(sem::Code::Switch::*)()>(&sem::Code::Switch::getRemoveCallout))
    .def("getEmphasizeLine", static_cast<sem::Code::Switch::EmphasizeLine&(sem::Code::Switch::*)()>(&sem::Code::Switch::getEmphasizeLine))
    .def("getDedent", static_cast<sem::Code::Switch::Dedent&(sem::Code::Switch::*)()>(&sem::Code::Switch::getDedent))
    .def("getKind", static_cast<sem::Code::Switch::Kind(sem::Code::Switch::*)() const>(&sem::Code::Switch::getKind))
    ;
  bind_enum_iterator<sem::Code::Results>(m, "CodeResults");
  pybind11::enum_<sem::Code::Results>(m, "CodeResults")
    .value("Replace", sem::Code::Results::Replace, R"RAW(Remove old result, replace with new value)RAW")
    .def("__iter__", [](sem::Code::Results _self) -> PyEnumIterator<sem::Code::Results> {
                     return
                     PyEnumIterator<sem::Code::Results>
                     ();
                     })
    ;
  bind_enum_iterator<sem::Code::Exports>(m, "CodeExports");
  pybind11::enum_<sem::Code::Exports>(m, "CodeExports")
    .value("None", sem::Code::Exports::None, R"RAW(Hide both original code and run result)RAW")
    .value("Both", sem::Code::Exports::Both, R"RAW(Show output and code)RAW")
    .value("Code", sem::Code::Exports::Code, R"RAW(Show only code)RAW")
    .value("Results", sem::Code::Exports::Results, R"RAW(Show only evaluation results)RAW")
    .def("__iter__", [](sem::Code::Exports _self) -> PyEnumIterator<sem::Code::Exports> {
                     return
                     PyEnumIterator<sem::Code::Exports>
                     ();
                     })
    ;
  pybind11::class_<sem::Code, sem::SemId<sem::Code>, sem::Block>(m, "Code")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Code {
                        sem::Code result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("lang", &sem::Code::lang, R"RAW(Code block language name)RAW")
    .def_readwrite("switches", &sem::Code::switches, R"RAW(Switch options for block)RAW")
    .def_readwrite("exports", &sem::Code::exports, R"RAW(What to export)RAW")
    .def_readwrite("lines", &sem::Code::lines, R"RAW(Collected code lines)RAW")
    .def_readwrite("cache", &sem::Code::cache, R"RAW(Do cache values?)RAW")
    .def_readwrite("eval", &sem::Code::eval, R"RAW(Eval on export?)RAW")
    .def_readwrite("noweb", &sem::Code::noweb, R"RAW(Web-tangle code on export/run)RAW")
    .def_readwrite("hlines", &sem::Code::hlines, R"RAW(?)RAW")
    .def_readwrite("tangle", &sem::Code::tangle, R"RAW(?)RAW")
    .def_readwrite("parameters", &sem::Code::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def("getParameter",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Code::*)(Str const&) const>(&sem::Code::getParameter),
         pybind11::arg("key"))
    ;
  bind_enum_iterator<sem::Time::Repeat::Mode>(m, "TimeRepeatMode");
  pybind11::enum_<sem::Time::Repeat::Mode>(m, "TimeRepeatMode")
    .value("None", sem::Time::Repeat::Mode::None, R"RAW(Do not repeat task on completion)RAW")
    .value("Exact", sem::Time::Repeat::Mode::Exact, R"RAW(?)RAW")
    .value("FirstMatch", sem::Time::Repeat::Mode::FirstMatch, R"RAW(Repeat on the first matching day in the future)RAW")
    .value("SameDay", sem::Time::Repeat::Mode::SameDay, R"RAW(Repeat task on the same day next week/month/year)RAW")
    .def("__iter__", [](sem::Time::Repeat::Mode _self) -> PyEnumIterator<sem::Time::Repeat::Mode> {
                     return
                     PyEnumIterator<sem::Time::Repeat::Mode>
                     ();
                     })
    ;
  bind_enum_iterator<sem::Time::Repeat::Period>(m, "TimeRepeatPeriod");
  pybind11::enum_<sem::Time::Repeat::Period>(m, "TimeRepeatPeriod")
    .value("Year", sem::Time::Repeat::Period::Year)
    .value("Month", sem::Time::Repeat::Period::Month)
    .value("Week", sem::Time::Repeat::Period::Week)
    .value("Day", sem::Time::Repeat::Period::Day)
    .value("Hour", sem::Time::Repeat::Period::Hour)
    .value("Minute", sem::Time::Repeat::Period::Minute)
    .def("__iter__", [](sem::Time::Repeat::Period _self) -> PyEnumIterator<sem::Time::Repeat::Period> {
                     return
                     PyEnumIterator<sem::Time::Repeat::Period>
                     ();
                     })
    ;
  pybind11::class_<sem::Time::Repeat>(m, "TimeRepeat")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Time::Repeat {
                        sem::Time::Repeat result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("mode", &sem::Time::Repeat::mode, R"RAW(mode)RAW")
    .def_readwrite("period", &sem::Time::Repeat::period, R"RAW(period)RAW")
    .def_readwrite("count", &sem::Time::Repeat::count, R"RAW(count)RAW")
    ;
  pybind11::class_<sem::Time::Static>(m, "TimeStatic")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Time::Static {
                        sem::Time::Static result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("repeat", &sem::Time::Static::repeat)
    .def_readwrite("time", &sem::Time::Static::time)
    ;
  pybind11::class_<sem::Time::Dynamic>(m, "TimeDynamic")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Time::Dynamic {
                        sem::Time::Dynamic result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("expr", &sem::Time::Dynamic::expr)
    ;
  bind_enum_iterator<sem::Time::TimeKind>(m, "TimeTimeKind");
  pybind11::enum_<sem::Time::TimeKind>(m, "TimeTimeKind")
    .value("Static", sem::Time::TimeKind::Static)
    .value("Dynamic", sem::Time::TimeKind::Dynamic)
    .def("__iter__", [](sem::Time::TimeKind _self) -> PyEnumIterator<sem::Time::TimeKind> {
                     return
                     PyEnumIterator<sem::Time::TimeKind>
                     ();
                     })
    ;
  pybind11::class_<sem::Time, sem::SemId<sem::Time>, sem::Org>(m, "Time")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Time {
                        sem::Time result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isActive", &sem::Time::isActive, R"RAW(<active> vs [inactive])RAW")
    .def_readwrite("time", &sem::Time::time)
    .def("getStatic", static_cast<sem::Time::Static&(sem::Time::*)()>(&sem::Time::getStatic))
    .def("getDynamic", static_cast<sem::Time::Dynamic&(sem::Time::*)()>(&sem::Time::getDynamic))
    .def("getTimeKind", static_cast<sem::Time::TimeKind(sem::Time::*)() const>(&sem::Time::getTimeKind))
    ;
  pybind11::class_<sem::TimeRange, sem::SemId<sem::TimeRange>, sem::Org>(m, "TimeRange")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::TimeRange {
                        sem::TimeRange result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("from_", &sem::TimeRange::from, R"RAW(Starting time)RAW")
    .def_readwrite("to", &sem::TimeRange::to, R"RAW(Finishing time)RAW")
    ;
  pybind11::class_<sem::Macro, sem::SemId<sem::Macro>, sem::Org>(m, "Macro")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Macro {
                        sem::Macro result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::Macro::name, R"RAW(Macro name)RAW")
    .def_readwrite("arguments", &sem::Macro::arguments, R"RAW(Raw uninterpreted macro arguments)RAW")
    ;
  pybind11::class_<sem::Symbol::Param>(m, "SymbolParam")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Symbol::Param {
                        sem::Symbol::Param result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("key", &sem::Symbol::Param::key, R"RAW(Key -- for non-positional)RAW")
    .def_readwrite("value", &sem::Symbol::Param::value, R"RAW(Uninterpreted value)RAW")
    ;
  pybind11::class_<sem::Symbol, sem::SemId<sem::Symbol>, sem::Org>(m, "Symbol")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Symbol {
                        sem::Symbol result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::Symbol::name, R"RAW(Name of the symbol)RAW")
    .def_readwrite("parameters", &sem::Symbol::parameters, R"RAW(Optional list of parameters)RAW")
    .def_readwrite("positional", &sem::Symbol::positional, R"RAW(Positional parameters)RAW")
    ;
  pybind11::class_<sem::SubtreeLog::DescribedLog>(m, "SubtreeLogDescribedLog")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::DescribedLog {
                        sem::SubtreeLog::DescribedLog result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("desc", &sem::SubtreeLog::DescribedLog::desc, R"RAW(Optional description of the log entry)RAW")
    ;
  bind_enum_iterator<sem::SubtreeLog::Priority::Action>(m, "SubtreeLogPriorityAction");
  pybind11::enum_<sem::SubtreeLog::Priority::Action>(m, "SubtreeLogPriorityAction")
    .value("Added", sem::SubtreeLog::Priority::Action::Added, R"RAW(`Priority B added on [timestamp]`)RAW")
    .value("Removed", sem::SubtreeLog::Priority::Action::Removed, R"RAW(`Priority C removed on [timestamp]`)RAW")
    .value("Changed", sem::SubtreeLog::Priority::Action::Changed, R"RAW(`Priority B changed from C on [timestamp]`)RAW")
    .def("__iter__", [](sem::SubtreeLog::Priority::Action _self) -> PyEnumIterator<sem::SubtreeLog::Priority::Action> {
                     return
                     PyEnumIterator<sem::SubtreeLog::Priority::Action>
                     ();
                     })
    ;
  pybind11::class_<sem::SubtreeLog::Priority, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogPriority")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::Priority {
                        sem::SubtreeLog::Priority result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("oldPriority", &sem::SubtreeLog::Priority::oldPriority, R"RAW(Previous priority for change and removal)RAW")
    .def_readwrite("newPriority", &sem::SubtreeLog::Priority::newPriority, R"RAW(New priority for change and addition)RAW")
    .def_readwrite("on", &sem::SubtreeLog::Priority::on, R"RAW(When priority was changed)RAW")
    .def_readwrite("action", &sem::SubtreeLog::Priority::action, R"RAW(Which action taken)RAW")
    ;
  pybind11::class_<sem::SubtreeLog::Note, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogNote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::Note {
                        sem::SubtreeLog::Note result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("on", &sem::SubtreeLog::Note::on, R"RAW(Where log was taken)RAW")
    ;
  pybind11::class_<sem::SubtreeLog::Refile, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogRefile")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::Refile {
                        sem::SubtreeLog::Refile result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("on", &sem::SubtreeLog::Refile::on, R"RAW(When the refiling happened)RAW")
    .def_readwrite("from_", &sem::SubtreeLog::Refile::from, R"RAW(Link to the original subtree)RAW")
    ;
  pybind11::class_<sem::SubtreeLog::Clock, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogClock")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::Clock {
                        sem::SubtreeLog::Clock result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("from_", &sem::SubtreeLog::Clock::from, R"RAW(Clock start time)RAW")
    .def_readwrite("to", &sem::SubtreeLog::Clock::to, R"RAW(Optional end of the clock)RAW")
    ;
  pybind11::class_<sem::SubtreeLog::State, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogState")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::State {
                        sem::SubtreeLog::State result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("from_", &sem::SubtreeLog::State::from)
    .def_readwrite("to", &sem::SubtreeLog::State::to)
    .def_readwrite("on", &sem::SubtreeLog::State::on)
    ;
  pybind11::class_<sem::SubtreeLog::Tag, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogTag")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::Tag {
                        sem::SubtreeLog::Tag result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("on", &sem::SubtreeLog::Tag::on, R"RAW(When the log was assigned)RAW")
    .def_readwrite("tag", &sem::SubtreeLog::Tag::tag, R"RAW(Tag in question)RAW")
    .def_readwrite("added", &sem::SubtreeLog::Tag::added, R"RAW(Added/removed?)RAW")
    ;
  pybind11::class_<sem::SubtreeLog::Unknown, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogUnknown")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::Unknown {
                        sem::SubtreeLog::Unknown result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  bind_enum_iterator<sem::SubtreeLog::Kind>(m, "SubtreeLogKind");
  pybind11::enum_<sem::SubtreeLog::Kind>(m, "SubtreeLogKind")
    .value("Priority", sem::SubtreeLog::Kind::Priority)
    .value("Note", sem::SubtreeLog::Kind::Note)
    .value("Refile", sem::SubtreeLog::Kind::Refile)
    .value("Clock", sem::SubtreeLog::Kind::Clock)
    .value("State", sem::SubtreeLog::Kind::State)
    .value("Tag", sem::SubtreeLog::Kind::Tag)
    .value("Unknown", sem::SubtreeLog::Kind::Unknown)
    .def("__iter__", [](sem::SubtreeLog::Kind _self) -> PyEnumIterator<sem::SubtreeLog::Kind> {
                     return
                     PyEnumIterator<sem::SubtreeLog::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::SubtreeLog, sem::SemId<sem::SubtreeLog>, sem::Org>(m, "SubtreeLog")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog {
                        sem::SubtreeLog result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("log", &sem::SubtreeLog::log)
    .def("setDescription",
         static_cast<void(sem::SubtreeLog::*)(sem::SemId<sem::StmtList>)>(&sem::SubtreeLog::setDescription),
         pybind11::arg("desc"))
    .def("getPriority", static_cast<sem::SubtreeLog::Priority&(sem::SubtreeLog::*)()>(&sem::SubtreeLog::getPriority))
    .def("getNote", static_cast<sem::SubtreeLog::Note&(sem::SubtreeLog::*)()>(&sem::SubtreeLog::getNote))
    .def("getRefile", static_cast<sem::SubtreeLog::Refile&(sem::SubtreeLog::*)()>(&sem::SubtreeLog::getRefile))
    .def("getClock", static_cast<sem::SubtreeLog::Clock&(sem::SubtreeLog::*)()>(&sem::SubtreeLog::getClock))
    .def("getState", static_cast<sem::SubtreeLog::State&(sem::SubtreeLog::*)()>(&sem::SubtreeLog::getState))
    .def("getTag", static_cast<sem::SubtreeLog::Tag&(sem::SubtreeLog::*)()>(&sem::SubtreeLog::getTag))
    .def("getUnknown", static_cast<sem::SubtreeLog::Unknown&(sem::SubtreeLog::*)()>(&sem::SubtreeLog::getUnknown))
    .def("getLogKind", static_cast<sem::SubtreeLog::Kind(sem::SubtreeLog::*)() const>(&sem::SubtreeLog::getLogKind))
    ;
  bind_enum_iterator<sem::Subtree::Period::Kind>(m, "SubtreePeriodKind");
  pybind11::enum_<sem::Subtree::Period::Kind>(m, "SubtreePeriodKind")
    .value("Clocked", sem::Subtree::Period::Kind::Clocked, R"RAW(Time period of the task execution.)RAW")
    .value("Closed", sem::Subtree::Period::Kind::Closed, R"RAW(Task marked as closed)RAW")
    .value("Scheduled", sem::Subtree::Period::Kind::Scheduled, R"RAW(Date of task execution start plus it's estimated effort duration. If the latter one is missing then only a single time point is returned)RAW")
    .value("Titled", sem::Subtree::Period::Kind::Titled, R"RAW(Single point or time range used in title. Single point can also be a simple time, such as `12:20`)RAW")
    .value("Deadline", sem::Subtree::Period::Kind::Deadline, R"RAW(Date of task completion. Must be a single time point)RAW")
    .value("Created", sem::Subtree::Period::Kind::Created, R"RAW(When the subtree was created)RAW")
    .value("Repeated", sem::Subtree::Period::Kind::Repeated, R"RAW(Last repeat time of the recurring tasks)RAW")
    .def("__iter__", [](sem::Subtree::Period::Kind _self) -> PyEnumIterator<sem::Subtree::Period::Kind> {
                     return
                     PyEnumIterator<sem::Subtree::Period::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::Subtree::Period>(m, "SubtreePeriod")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Period {
                        sem::Subtree::Period result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("kind", &sem::Subtree::Period::kind, R"RAW(Time period kind -- not associated with point/range distinction)RAW")
    .def_readwrite("from_", &sem::Subtree::Period::from, R"RAW(Clock start time)RAW")
    .def_readwrite("to", &sem::Subtree::Period::to, R"RAW(Optional end of the clock)RAW")
    ;
  bind_enum_iterator<sem::Subtree::Property::SetMode>(m, "SubtreePropertySetMode");
  pybind11::enum_<sem::Subtree::Property::SetMode>(m, "SubtreePropertySetMode")
    .value("Override", sem::Subtree::Property::SetMode::Override)
    .value("Add", sem::Subtree::Property::SetMode::Add)
    .value("Subtract", sem::Subtree::Property::SetMode::Subtract)
    .def("__iter__", [](sem::Subtree::Property::SetMode _self) -> PyEnumIterator<sem::Subtree::Property::SetMode> {
                     return
                     PyEnumIterator<sem::Subtree::Property::SetMode>
                     ();
                     })
    ;
  bind_enum_iterator<sem::Subtree::Property::InheritanceMode>(m, "SubtreePropertyInheritanceMode");
  pybind11::enum_<sem::Subtree::Property::InheritanceMode>(m, "SubtreePropertyInheritanceMode")
    .value("ThisAndSub", sem::Subtree::Property::InheritanceMode::ThisAndSub)
    .value("OnlyThis", sem::Subtree::Property::InheritanceMode::OnlyThis)
    .value("OnlySub", sem::Subtree::Property::InheritanceMode::OnlySub)
    .def("__iter__", [](sem::Subtree::Property::InheritanceMode _self) -> PyEnumIterator<sem::Subtree::Property::InheritanceMode> {
                     return
                     PyEnumIterator<sem::Subtree::Property::InheritanceMode>
                     ();
                     })
    ;
  pybind11::class_<sem::Subtree::Property::Nonblocking>(m, "SubtreePropertyNonblocking")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Nonblocking {
                        sem::Subtree::Property::Nonblocking result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isBlocking", &sem::Subtree::Property::Nonblocking::isBlocking)
    ;
  pybind11::class_<sem::Subtree::Property::Trigger>(m, "SubtreePropertyTrigger")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Trigger {
                        sem::Subtree::Property::Trigger result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Subtree::Property::Origin>(m, "SubtreePropertyOrigin")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Origin {
                        sem::Subtree::Property::Origin result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Subtree::Property::Origin::text)
    ;
  pybind11::class_<sem::Subtree::Property::ExportLatexClass>(m, "SubtreePropertyExportLatexClass")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::ExportLatexClass {
                        sem::Subtree::Property::ExportLatexClass result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("latexClass", &sem::Subtree::Property::ExportLatexClass::latexClass)
    ;
  pybind11::class_<sem::Subtree::Property::ExportLatexClassOptions>(m, "SubtreePropertyExportLatexClassOptions")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::ExportLatexClassOptions {
                        sem::Subtree::Property::ExportLatexClassOptions result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("options", &sem::Subtree::Property::ExportLatexClassOptions::options)
    ;
  pybind11::class_<sem::Subtree::Property::ExportLatexHeader>(m, "SubtreePropertyExportLatexHeader")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::ExportLatexHeader {
                        sem::Subtree::Property::ExportLatexHeader result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("header", &sem::Subtree::Property::ExportLatexHeader::header)
    ;
  pybind11::class_<sem::Subtree::Property::ExportLatexCompiler>(m, "SubtreePropertyExportLatexCompiler")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::ExportLatexCompiler {
                        sem::Subtree::Property::ExportLatexCompiler result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("compiler", &sem::Subtree::Property::ExportLatexCompiler::compiler)
    ;
  pybind11::class_<sem::Subtree::Property::Ordered>(m, "SubtreePropertyOrdered")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Ordered {
                        sem::Subtree::Property::Ordered result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isOrdered", &sem::Subtree::Property::Ordered::isOrdered)
    ;
  pybind11::class_<sem::Subtree::Property::Effort>(m, "SubtreePropertyEffort")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Effort {
                        sem::Subtree::Property::Effort result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("hours", &sem::Subtree::Property::Effort::hours)
    .def_readwrite("minutes", &sem::Subtree::Property::Effort::minutes)
    ;
  bind_enum_iterator<sem::Subtree::Property::Visibility::Level>(m, "SubtreePropertyVisibilityLevel");
  pybind11::enum_<sem::Subtree::Property::Visibility::Level>(m, "SubtreePropertyVisibilityLevel")
    .value("Folded", sem::Subtree::Property::Visibility::Level::Folded)
    .value("Children", sem::Subtree::Property::Visibility::Level::Children)
    .value("Content", sem::Subtree::Property::Visibility::Level::Content)
    .value("All", sem::Subtree::Property::Visibility::Level::All)
    .def("__iter__", [](sem::Subtree::Property::Visibility::Level _self) -> PyEnumIterator<sem::Subtree::Property::Visibility::Level> {
                     return
                     PyEnumIterator<sem::Subtree::Property::Visibility::Level>
                     ();
                     })
    ;
  pybind11::class_<sem::Subtree::Property::Visibility>(m, "SubtreePropertyVisibility")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Visibility {
                        sem::Subtree::Property::Visibility result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("level", &sem::Subtree::Property::Visibility::level)
    ;
  pybind11::class_<sem::Subtree::Property::ExportOptions>(m, "SubtreePropertyExportOptions")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::ExportOptions {
                        sem::Subtree::Property::ExportOptions result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("backend", &sem::Subtree::Property::ExportOptions::backend)
    .def_readwrite("values", &sem::Subtree::Property::ExportOptions::values)
    ;
  pybind11::class_<sem::Subtree::Property::Blocker>(m, "SubtreePropertyBlocker")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Blocker {
                        sem::Subtree::Property::Blocker result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("blockers", &sem::Subtree::Property::Blocker::blockers)
    ;
  pybind11::class_<sem::Subtree::Property::Unnumbered>(m, "SubtreePropertyUnnumbered")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Unnumbered {
                        sem::Subtree::Property::Unnumbered result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Subtree::Property::Created>(m, "SubtreePropertyCreated")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Created {
                        sem::Subtree::Property::Created result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("time", &sem::Subtree::Property::Created::time)
    ;
  pybind11::class_<sem::Subtree::Property::Unknown>(m, "SubtreePropertyUnknown")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Unknown {
                        sem::Subtree::Property::Unknown result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &sem::Subtree::Property::Unknown::value, R"RAW(Converted value of the property)RAW")
    .def_readwrite("name", &sem::Subtree::Property::Unknown::name, R"RAW(Original name of the property)RAW")
    ;
  bind_enum_iterator<sem::Subtree::Property::Kind>(m, "SubtreePropertyKind");
  pybind11::enum_<sem::Subtree::Property::Kind>(m, "SubtreePropertyKind")
    .value("Nonblocking", sem::Subtree::Property::Kind::Nonblocking)
    .value("Trigger", sem::Subtree::Property::Kind::Trigger)
    .value("Origin", sem::Subtree::Property::Kind::Origin)
    .value("ExportLatexClass", sem::Subtree::Property::Kind::ExportLatexClass)
    .value("ExportLatexClassOptions", sem::Subtree::Property::Kind::ExportLatexClassOptions)
    .value("ExportLatexHeader", sem::Subtree::Property::Kind::ExportLatexHeader)
    .value("ExportLatexCompiler", sem::Subtree::Property::Kind::ExportLatexCompiler)
    .value("Ordered", sem::Subtree::Property::Kind::Ordered)
    .value("Effort", sem::Subtree::Property::Kind::Effort)
    .value("Visibility", sem::Subtree::Property::Kind::Visibility)
    .value("ExportOptions", sem::Subtree::Property::Kind::ExportOptions)
    .value("Blocker", sem::Subtree::Property::Kind::Blocker)
    .value("Unnumbered", sem::Subtree::Property::Kind::Unnumbered)
    .value("Created", sem::Subtree::Property::Kind::Created)
    .value("Unknown", sem::Subtree::Property::Kind::Unknown)
    .def("__iter__", [](sem::Subtree::Property::Kind _self) -> PyEnumIterator<sem::Subtree::Property::Kind> {
                     return
                     PyEnumIterator<sem::Subtree::Property::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::Subtree::Property>(m, "SubtreeProperty")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property {
                        sem::Subtree::Property result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("mainSetRule", &sem::Subtree::Property::mainSetRule)
    .def_readwrite("subSetRule", &sem::Subtree::Property::subSetRule)
    .def_readwrite("inheritanceMode", &sem::Subtree::Property::inheritanceMode)
    .def_readwrite("data", &sem::Subtree::Property::data)
    .def("isMatching",
         static_cast<bool(sem::Subtree::Property::*)(Str const&, Opt<Str> const&) const>(&sem::Subtree::Property::isMatching),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt),
         R"RAW(Check if property matches specified kind and optional subkind. Built-in property checking is also done with this function -- 'created' etc.)RAW")
    .def("getName", static_cast<Str(sem::Subtree::Property::*)() const>(&sem::Subtree::Property::getName), R"RAW(Get non-normalized name of the property (for built-in and user))RAW")
    .def("getSubKind", static_cast<Opt<Str>(sem::Subtree::Property::*)() const>(&sem::Subtree::Property::getSubKind), R"RAW(Get non-normalized sub-kind for the property.)RAW")
    .def("getNonblocking", static_cast<sem::Subtree::Property::Nonblocking&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getNonblocking))
    .def("getTrigger", static_cast<sem::Subtree::Property::Trigger&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getTrigger))
    .def("getOrigin", static_cast<sem::Subtree::Property::Origin&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getOrigin))
    .def("getExportLatexClass", static_cast<sem::Subtree::Property::ExportLatexClass&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getExportLatexClass))
    .def("getExportLatexClassOptions", static_cast<sem::Subtree::Property::ExportLatexClassOptions&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getExportLatexClassOptions))
    .def("getExportLatexHeader", static_cast<sem::Subtree::Property::ExportLatexHeader&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getExportLatexHeader))
    .def("getExportLatexCompiler", static_cast<sem::Subtree::Property::ExportLatexCompiler&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getExportLatexCompiler))
    .def("getOrdered", static_cast<sem::Subtree::Property::Ordered&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getOrdered))
    .def("getEffort", static_cast<sem::Subtree::Property::Effort&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getEffort))
    .def("getVisibility", static_cast<sem::Subtree::Property::Visibility&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getVisibility))
    .def("getExportOptions", static_cast<sem::Subtree::Property::ExportOptions&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getExportOptions))
    .def("getBlocker", static_cast<sem::Subtree::Property::Blocker&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getBlocker))
    .def("getUnnumbered", static_cast<sem::Subtree::Property::Unnumbered&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getUnnumbered))
    .def("getCreated", static_cast<sem::Subtree::Property::Created&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getCreated))
    .def("getUnknown", static_cast<sem::Subtree::Property::Unknown&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getUnknown))
    .def("getKind", static_cast<sem::Subtree::Property::Kind(sem::Subtree::Property::*)() const>(&sem::Subtree::Property::getKind))
    ;
  pybind11::class_<sem::Subtree, sem::SemId<sem::Subtree>, sem::Org>(m, "Subtree")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree {
                        sem::Subtree result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("level", &sem::Subtree::level, R"RAW(Subtree level)RAW")
    .def_readwrite("treeId", &sem::Subtree::treeId, R"RAW(:ID: property)RAW")
    .def_readwrite("todo", &sem::Subtree::todo, R"RAW(Todo state of the tree)RAW")
    .def_readwrite("completion", &sem::Subtree::completion, R"RAW(Task completion state)RAW")
    .def_readwrite("description", &sem::Subtree::description)
    .def_readwrite("tags", &sem::Subtree::tags, R"RAW(Trailing tags)RAW")
    .def_readwrite("title", &sem::Subtree::title, R"RAW(Main title)RAW")
    .def_readwrite("logbook", &sem::Subtree::logbook, R"RAW(Associated subtree log)RAW")
    .def_readwrite("properties", &sem::Subtree::properties, R"RAW(Immediate properties)RAW")
    .def_readwrite("closed", &sem::Subtree::closed, R"RAW(When subtree was marked as closed)RAW")
    .def_readwrite("deadline", &sem::Subtree::deadline, R"RAW(When is the deadline)RAW")
    .def_readwrite("scheduled", &sem::Subtree::scheduled, R"RAW(When the event is scheduled)RAW")
    .def("getTimePeriods",
         static_cast<Vec<sem::Subtree::Period>(sem::Subtree::*)(IntSet<sem::Subtree::Period::Kind>) const>(&sem::Subtree::getTimePeriods),
         pybind11::arg("kinds"))
    .def("getProperties",
         static_cast<Vec<sem::Subtree::Property>(sem::Subtree::*)(Str const&, Opt<Str> const&) const>(&sem::Subtree::getProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", std::nullopt))
    .def("getProperty",
         static_cast<Opt<sem::Subtree::Property>(sem::Subtree::*)(Str const&, Opt<Str> const&) const>(&sem::Subtree::getProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", std::nullopt))
    ;
  pybind11::class_<sem::LatexBody, sem::SemId<sem::LatexBody>, sem::Org>(m, "LatexBody")
    ;
  pybind11::class_<sem::InlineMath, sem::SemId<sem::InlineMath>, sem::LatexBody>(m, "InlineMath")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::InlineMath {
                        sem::InlineMath result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Leaf, sem::SemId<sem::Leaf>, sem::Org>(m, "Leaf")
    .def_readwrite("text", &sem::Leaf::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::Escaped, sem::SemId<sem::Escaped>, sem::Leaf>(m, "Escaped")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Escaped {
                        sem::Escaped result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Escaped::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::Newline, sem::SemId<sem::Newline>, sem::Leaf>(m, "Newline")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Newline {
                        sem::Newline result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Newline::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::Space, sem::SemId<sem::Space>, sem::Leaf>(m, "Space")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Space {
                        sem::Space result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Space::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::Word, sem::SemId<sem::Word>, sem::Leaf>(m, "Word")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Word {
                        sem::Word result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Word::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::AtMention, sem::SemId<sem::AtMention>, sem::Leaf>(m, "AtMention")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::AtMention {
                        sem::AtMention result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::AtMention::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::RawText, sem::SemId<sem::RawText>, sem::Leaf>(m, "RawText")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::RawText {
                        sem::RawText result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::RawText::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::Punctuation, sem::SemId<sem::Punctuation>, sem::Leaf>(m, "Punctuation")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Punctuation {
                        sem::Punctuation result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Punctuation::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::Placeholder, sem::SemId<sem::Placeholder>, sem::Leaf>(m, "Placeholder")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Placeholder {
                        sem::Placeholder result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Placeholder::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::BigIdent, sem::SemId<sem::BigIdent>, sem::Leaf>(m, "BigIdent")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BigIdent {
                        sem::BigIdent result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::BigIdent::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::Markup, sem::SemId<sem::Markup>, sem::Org>(m, "Markup")
    ;
  pybind11::class_<sem::Bold, sem::SemId<sem::Bold>, sem::Markup>(m, "Bold")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Bold {
                        sem::Bold result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Underline, sem::SemId<sem::Underline>, sem::Markup>(m, "Underline")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Underline {
                        sem::Underline result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Monospace, sem::SemId<sem::Monospace>, sem::Markup>(m, "Monospace")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Monospace {
                        sem::Monospace result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::MarkQuote, sem::SemId<sem::MarkQuote>, sem::Markup>(m, "MarkQuote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::MarkQuote {
                        sem::MarkQuote result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Verbatim, sem::SemId<sem::Verbatim>, sem::Markup>(m, "Verbatim")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Verbatim {
                        sem::Verbatim result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Italic, sem::SemId<sem::Italic>, sem::Markup>(m, "Italic")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Italic {
                        sem::Italic result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Strike, sem::SemId<sem::Strike>, sem::Markup>(m, "Strike")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Strike {
                        sem::Strike result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Par, sem::SemId<sem::Par>, sem::Markup>(m, "Par")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Par {
                        sem::Par result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::List, sem::SemId<sem::List>, sem::Org>(m, "List")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::List {
                        sem::List result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("isDescriptionList", static_cast<bool(sem::List::*)() const>(&sem::List::isDescriptionList))
    ;
  bind_enum_iterator<sem::ListItem::Checkbox>(m, "ListItemCheckbox");
  pybind11::enum_<sem::ListItem::Checkbox>(m, "ListItemCheckbox")
    .value("None", sem::ListItem::Checkbox::None)
    .value("Done", sem::ListItem::Checkbox::Done)
    .value("Empty", sem::ListItem::Checkbox::Empty)
    .value("Partial", sem::ListItem::Checkbox::Partial)
    .def("__iter__", [](sem::ListItem::Checkbox _self) -> PyEnumIterator<sem::ListItem::Checkbox> {
                     return
                     PyEnumIterator<sem::ListItem::Checkbox>
                     ();
                     })
    ;
  pybind11::class_<sem::ListItem, sem::SemId<sem::ListItem>, sem::Org>(m, "ListItem")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::ListItem {
                        sem::ListItem result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("checkbox", &sem::ListItem::checkbox)
    .def_readwrite("header", &sem::ListItem::header)
    .def("isDescriptionItem", static_cast<bool(sem::ListItem::*)() const>(&sem::ListItem::isDescriptionItem))
    ;
  pybind11::class_<sem::Link::Raw>(m, "LinkRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Raw {
                        sem::Link::Raw result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Link::Raw::text)
    ;
  pybind11::class_<sem::Link::Id>(m, "LinkId")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Id {
                        sem::Link::Id result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Link::Id::text)
    ;
  pybind11::class_<sem::Link::Person>(m, "LinkPerson")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Person {
                        sem::Link::Person result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::Link::Person::name)
    ;
  pybind11::class_<sem::Link::UserProtocol>(m, "LinkUserProtocol")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::UserProtocol {
                        sem::Link::UserProtocol result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("protocol", &sem::Link::UserProtocol::protocol)
    .def_readwrite("target", &sem::Link::UserProtocol::target)
    ;
  pybind11::class_<sem::Link::Internal>(m, "LinkInternal")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Internal {
                        sem::Link::Internal result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &sem::Link::Internal::target)
    ;
  pybind11::class_<sem::Link::Footnote>(m, "LinkFootnote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Footnote {
                        sem::Link::Footnote result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &sem::Link::Footnote::target)
    ;
  pybind11::class_<sem::Link::File>(m, "LinkFile")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::File {
                        sem::Link::File result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("file", &sem::Link::File::file)
    ;
  bind_enum_iterator<sem::Link::Kind>(m, "LinkKind");
  pybind11::enum_<sem::Link::Kind>(m, "LinkKind")
    .value("Raw", sem::Link::Kind::Raw)
    .value("Id", sem::Link::Kind::Id)
    .value("Person", sem::Link::Kind::Person)
    .value("UserProtocol", sem::Link::Kind::UserProtocol)
    .value("Internal", sem::Link::Kind::Internal)
    .value("Footnote", sem::Link::Kind::Footnote)
    .value("File", sem::Link::Kind::File)
    .def("__iter__", [](sem::Link::Kind _self) -> PyEnumIterator<sem::Link::Kind> {
                     return
                     PyEnumIterator<sem::Link::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::Link, sem::SemId<sem::Link>, sem::Org>(m, "Link")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link {
                        sem::Link result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("description", &sem::Link::description)
    .def_readwrite("data", &sem::Link::data)
    .def("getRaw", static_cast<sem::Link::Raw&(sem::Link::*)()>(&sem::Link::getRaw))
    .def("getId", static_cast<sem::Link::Id&(sem::Link::*)()>(&sem::Link::getId))
    .def("getPerson", static_cast<sem::Link::Person&(sem::Link::*)()>(&sem::Link::getPerson))
    .def("getUserProtocol", static_cast<sem::Link::UserProtocol&(sem::Link::*)()>(&sem::Link::getUserProtocol))
    .def("getInternal", static_cast<sem::Link::Internal&(sem::Link::*)()>(&sem::Link::getInternal))
    .def("getFootnote", static_cast<sem::Link::Footnote&(sem::Link::*)()>(&sem::Link::getFootnote))
    .def("getFile", static_cast<sem::Link::File&(sem::Link::*)()>(&sem::Link::getFile))
    .def("getLinkKind", static_cast<sem::Link::Kind(sem::Link::*)() const>(&sem::Link::getLinkKind))
    ;
  pybind11::class_<sem::DocumentOptions::DoExport>(m, "DocumentOptionsDoExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentOptions::DoExport {
                        sem::DocumentOptions::DoExport result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("exportToc", &sem::DocumentOptions::DoExport::exportToc)
    ;
  pybind11::class_<sem::DocumentOptions::ExportFixed>(m, "DocumentOptionsExportFixed")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentOptions::ExportFixed {
                        sem::DocumentOptions::ExportFixed result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("exportLevels", &sem::DocumentOptions::ExportFixed::exportLevels)
    ;
  bind_enum_iterator<sem::DocumentOptions::TocExportKind>(m, "DocumentOptionsTocExportKind");
  pybind11::enum_<sem::DocumentOptions::TocExportKind>(m, "DocumentOptionsTocExportKind")
    .value("DoExport", sem::DocumentOptions::TocExportKind::DoExport)
    .value("ExportFixed", sem::DocumentOptions::TocExportKind::ExportFixed)
    .def("__iter__", [](sem::DocumentOptions::TocExportKind _self) -> PyEnumIterator<sem::DocumentOptions::TocExportKind> {
                     return
                     PyEnumIterator<sem::DocumentOptions::TocExportKind>
                     ();
                     })
    ;
  bind_enum_iterator<sem::DocumentOptions::BrokenLinks>(m, "DocumentOptionsBrokenLinks");
  pybind11::enum_<sem::DocumentOptions::BrokenLinks>(m, "DocumentOptionsBrokenLinks")
    .value("Raise", sem::DocumentOptions::BrokenLinks::Raise)
    .value("Ignore", sem::DocumentOptions::BrokenLinks::Ignore)
    .value("Mark", sem::DocumentOptions::BrokenLinks::Mark)
    .def("__iter__", [](sem::DocumentOptions::BrokenLinks _self) -> PyEnumIterator<sem::DocumentOptions::BrokenLinks> {
                     return
                     PyEnumIterator<sem::DocumentOptions::BrokenLinks>
                     ();
                     })
    ;
  bind_enum_iterator<sem::DocumentOptions::Visibility>(m, "DocumentOptionsVisibility");
  pybind11::enum_<sem::DocumentOptions::Visibility>(m, "DocumentOptionsVisibility")
    .value("Overview", sem::DocumentOptions::Visibility::Overview)
    .value("Content", sem::DocumentOptions::Visibility::Content)
    .value("ShowAll", sem::DocumentOptions::Visibility::ShowAll)
    .value("Show2Levels", sem::DocumentOptions::Visibility::Show2Levels)
    .value("Show3Levels", sem::DocumentOptions::Visibility::Show3Levels)
    .value("Show4Levels", sem::DocumentOptions::Visibility::Show4Levels)
    .value("Show5Levels", sem::DocumentOptions::Visibility::Show5Levels)
    .value("ShowEverything", sem::DocumentOptions::Visibility::ShowEverything)
    .def("__iter__", [](sem::DocumentOptions::Visibility _self) -> PyEnumIterator<sem::DocumentOptions::Visibility> {
                     return
                     PyEnumIterator<sem::DocumentOptions::Visibility>
                     ();
                     })
    ;
  pybind11::class_<sem::DocumentOptions, sem::SemId<sem::DocumentOptions>, sem::Org>(m, "DocumentOptions")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentOptions {
                        sem::DocumentOptions result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("brokenLinks", &sem::DocumentOptions::brokenLinks)
    .def_readwrite("initialVisibility", &sem::DocumentOptions::initialVisibility)
    .def_readwrite("tocExport", &sem::DocumentOptions::tocExport)
    .def_readwrite("properties", &sem::DocumentOptions::properties)
    .def_readwrite("smartQuotes", &sem::DocumentOptions::smartQuotes)
    .def_readwrite("emphasizedText", &sem::DocumentOptions::emphasizedText)
    .def_readwrite("specialStrings", &sem::DocumentOptions::specialStrings)
    .def_readwrite("fixedWidthSections", &sem::DocumentOptions::fixedWidthSections)
    .def_readwrite("includeTimestamps", &sem::DocumentOptions::includeTimestamps)
    .def_readwrite("preserveLineBreaks", &sem::DocumentOptions::preserveLineBreaks)
    .def_readwrite("plaintextSubscripts", &sem::DocumentOptions::plaintextSubscripts)
    .def_readwrite("exportArchived", &sem::DocumentOptions::exportArchived)
    .def_readwrite("exportWithAuthor", &sem::DocumentOptions::exportWithAuthor)
    .def_readwrite("exportBrokenLinks", &sem::DocumentOptions::exportBrokenLinks)
    .def_readwrite("exportWithClock", &sem::DocumentOptions::exportWithClock)
    .def_readwrite("exportWithCreator", &sem::DocumentOptions::exportWithCreator)
    .def_readwrite("data", &sem::DocumentOptions::data)
    .def("getProperties",
         static_cast<Vec<sem::Subtree::Property>(sem::DocumentOptions::*)(Str const&, Opt<Str> const&) const>(&sem::DocumentOptions::getProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt))
    .def("getProperty",
         static_cast<Opt<sem::Subtree::Property>(sem::DocumentOptions::*)(Str const&, Opt<Str> const&) const>(&sem::DocumentOptions::getProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt))
    .def("getDoExport", static_cast<sem::DocumentOptions::DoExport&(sem::DocumentOptions::*)()>(&sem::DocumentOptions::getDoExport))
    .def("getExportFixed", static_cast<sem::DocumentOptions::ExportFixed&(sem::DocumentOptions::*)()>(&sem::DocumentOptions::getExportFixed))
    .def("getTocExportKind", static_cast<sem::DocumentOptions::TocExportKind(sem::DocumentOptions::*)() const>(&sem::DocumentOptions::getTocExportKind))
    ;
  pybind11::class_<sem::Document, sem::SemId<sem::Document>, sem::Org>(m, "Document")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Document {
                        sem::Document result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("title", &sem::Document::title)
    .def_readwrite("author", &sem::Document::author)
    .def_readwrite("creator", &sem::Document::creator)
    .def_readwrite("filetags", &sem::Document::filetags)
    .def_readwrite("email", &sem::Document::email)
    .def_readwrite("language", &sem::Document::language)
    .def_readwrite("options", &sem::Document::options)
    .def_readwrite("exportFileName", &sem::Document::exportFileName)
    .def("getProperties",
         static_cast<Vec<sem::Subtree::Property>(sem::Document::*)(Str const&, Opt<Str> const&) const>(&sem::Document::getProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt))
    .def("getProperty",
         static_cast<Opt<sem::Subtree::Property>(sem::Document::*)(Str const&, Opt<Str> const&) const>(&sem::Document::getProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt))
    ;
  pybind11::class_<sem::ParseError, sem::SemId<sem::ParseError>, sem::Org>(m, "ParseError")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::ParseError {
                        sem::ParseError result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::FileTarget, sem::SemId<sem::FileTarget>, sem::Org>(m, "FileTarget")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::FileTarget {
                        sem::FileTarget result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("path", &sem::FileTarget::path)
    .def_readwrite("line", &sem::FileTarget::line)
    .def_readwrite("searchTarget", &sem::FileTarget::searchTarget)
    .def_readwrite("restrictToHeadlines", &sem::FileTarget::restrictToHeadlines)
    .def_readwrite("targetId", &sem::FileTarget::targetId)
    .def_readwrite("regexp", &sem::FileTarget::regexp)
    ;
  pybind11::class_<sem::TextSeparator, sem::SemId<sem::TextSeparator>, sem::Org>(m, "TextSeparator")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::TextSeparator {
                        sem::TextSeparator result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Include::Example>(m, "IncludeExample")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Include::Example {
                        sem::Include::Example result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Include::Export>(m, "IncludeExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Include::Export {
                        sem::Include::Export result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Include::Src>(m, "IncludeSrc")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Include::Src {
                        sem::Include::Src result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  pybind11::class_<sem::Include::OrgDocument>(m, "IncludeOrgDocument")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Include::OrgDocument {
                        sem::Include::OrgDocument result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
  bind_enum_iterator<sem::Include::Kind>(m, "IncludeKind");
  pybind11::enum_<sem::Include::Kind>(m, "IncludeKind")
    .value("Example", sem::Include::Kind::Example)
    .value("Export", sem::Include::Kind::Export)
    .value("Src", sem::Include::Kind::Src)
    .value("OrgDocument", sem::Include::Kind::OrgDocument)
    .def("__iter__", [](sem::Include::Kind _self) -> PyEnumIterator<sem::Include::Kind> {
                     return
                     PyEnumIterator<sem::Include::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::Include, sem::SemId<sem::Include>, sem::Org>(m, "Include")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Include {
                        sem::Include result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &sem::Include::data)
    .def("getExample", static_cast<sem::Include::Example&(sem::Include::*)()>(&sem::Include::getExample))
    .def("getExport", static_cast<sem::Include::Export&(sem::Include::*)()>(&sem::Include::getExport))
    .def("getSrc", static_cast<sem::Include::Src&(sem::Include::*)()>(&sem::Include::getSrc))
    .def("getOrgDocument", static_cast<sem::Include::OrgDocument&(sem::Include::*)()>(&sem::Include::getOrgDocument))
    .def("getIncludeKind", static_cast<sem::Include::Kind(sem::Include::*)() const>(&sem::Include::getIncludeKind))
    ;
  pybind11::class_<sem::DocumentGroup, sem::SemId<sem::DocumentGroup>, sem::Org>(m, "DocumentGroup")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentGroup {
                        sem::DocumentGroup result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    ;
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
    .value("Urgency", OrgSpecName::Urgency)
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
    .value("UserNode", OrgNodeKind::UserNode, R"RAW(User-defined node [[code:OrgUserNode]])RAW")
    .value("Empty", OrgNodeKind::Empty, R"RAW(Empty node - valid state that does not contain any value)RAW")
    .value("Error", OrgNodeKind::Error, R"RAW(Failed node parse


   Failed node parse - technically there are no /wrong/ syntax in the
   org-mode document because everything can be considered a one large
   word or a paragraph with flat `Word` content.

   Error node's extent covers all subnodes that were constructed
   during nested content parsing plus ErrorTerminator node with error
   token (description of the parsing failure). So failure node will be
   structured as `[Error <some content> <ErrorToken>
   <ErrorTermiator>]`. Second-to-last is the invalid token itself,
   error terminator will hold fake token that referes to an error.

   Error node can be produced by any parsing routine, although it is
   mostly used in the low-level text elements, since high-level
   structures are mostly detected based on the correct syntax - for
   example, `*** subtree` (and any title variations) can never be an
   error in itself. Title /text/ might contain an error, but invalid
   it is not possible to write an invalid subtree - it is either `*
   ANYTHING` or not a subtree at all.
   )RAW")
    .value("ErrorTerminator", OrgNodeKind::ErrorTerminator, R"RAW(Terminator node for failure in nested structure parsing)RAW")
    .value("ErrorToken", OrgNodeKind::ErrorToken, R"RAW(Single invalid token)RAW")
    .value("InlineStmtList", OrgNodeKind::InlineStmtList)
    .value("StmtList", OrgNodeKind::StmtList, R"RAW(List of statements, possibly recursive. Used as toplevel part of the document, in recursive parsing of subtrees, or as regular list, in cases where multiple subnodes have to be grouped together.)RAW")
    .value("AssocStmtList", OrgNodeKind::AssocStmtList, R"RAW(Associated list of statements - AST elements like commands and links are grouped together if placed on adjacent lines)RAW")
    .value("Subtree", OrgNodeKind::Subtree, R"RAW(Section subtree)RAW")
    .value("SubtreeTimes", OrgNodeKind::SubtreeTimes, R"RAW(Time? associated with subtree entry)RAW")
    .value("SubtreeStars", OrgNodeKind::SubtreeStars)
    .value("Completion", OrgNodeKind::Completion, R"RAW(Task compleation cookie, indicated either in percents of completion, or as `<done>/<todo>` ratio.)RAW")
    .value("Checkbox", OrgNodeKind::Checkbox, R"RAW(Single checkbox item like `[X]` or `[-]`)RAW")
    .value("List", OrgNodeKind::List)
    .value("Bullet", OrgNodeKind::Bullet, R"RAW(List item prefix)RAW")
    .value("ListItem", OrgNodeKind::ListItem)
    .value("ListTag", OrgNodeKind::ListTag, R"RAW(Auxilliary wrapper for the paragraph placed at the start of the description list.)RAW")
    .value("Counter", OrgNodeKind::Counter)
    .value("Comment", OrgNodeKind::Comment, R"RAW(Inline or trailling comment. Can be used addition to `#+comment:` line or `#+begin-comment` section. Nested comment syntax is allowed (`#[ level1 #[ level2 ]# ]#`), but only outermost one is represented as separate AST node, everything else is a `.text`)RAW")
    .value("RawText", OrgNodeKind::RawText, R"RAW(Raw string of text from input buffer. Things like particular syntax details of every single command, link formats are not handled in parser, deferring formatting to future processing layers )RAW")
    .value("Unparsed", OrgNodeKind::Unparsed, R"RAW(Part of the org-mode document that is yet to be parsed. This node should not be created manually, it is only used for handling mutually recursive DSLs such as tables, which might include lists, which in turn might contain more tables in different bullet points.)RAW")
    .value("Command", OrgNodeKind::Command, R"RAW(Undefined single-line command -- most likely custom user-provided oe)RAW")
    .value("CommandArguments", OrgNodeKind::CommandArguments, R"RAW(Arguments for the command block)RAW")
    .value("CommandTitle", OrgNodeKind::CommandTitle, R"RAW(`#+title:` - full document title)RAW")
    .value("CommandAuthor", OrgNodeKind::CommandAuthor, R"RAW(`#+author:` Document author)RAW")
    .value("CommandCreator", OrgNodeKind::CommandCreator, R"RAW(`#+creator:` Document creator)RAW")
    .value("CommandInclude", OrgNodeKind::CommandInclude, R"RAW(`#+include:` - include other org-mode document (or subsection of it), source code or backend-specific chunk.)RAW")
    .value("CommandLanguage", OrgNodeKind::CommandLanguage, R"RAW(`#+language:`)RAW")
    .value("CommandAttr", OrgNodeKind::CommandAttr, R"RAW(`#+attr_html:`, `#+attr_image` etc.)RAW")
    .value("CommandStartup", OrgNodeKind::CommandStartup, R"RAW(`#+startup:`)RAW")
    .value("CommandName", OrgNodeKind::CommandName, R"RAW(`#+name:` - name of the associated entry)RAW")
    .value("CommandResults", OrgNodeKind::CommandResults, R"RAW(`#+results:` - source code block evaluation results)RAW")
    .value("CommandHeader", OrgNodeKind::CommandHeader, R"RAW(`#+header:` - extended list of parameters passed to associated block)RAW")
    .value("CommandOptions", OrgNodeKind::CommandOptions, R"RAW(`#+options:` - document-wide formatting options)RAW")
    .value("CommandTblfm", OrgNodeKind::CommandTblfm)
    .value("CommandBackendOptions", OrgNodeKind::CommandBackendOptions, R"RAW(Backend-specific configuration options like `#+latex_header` `#+latex_class` etc.)RAW")
    .value("AttrImg", OrgNodeKind::AttrImg)
    .value("CommandCaption", OrgNodeKind::CommandCaption, R"RAW(`#+caption:` command)RAW")
    .value("File", OrgNodeKind::File)
    .value("BlockExport", OrgNodeKind::BlockExport)
    .value("InlineExport", OrgNodeKind::InlineExport)
    .value("MultilineCommand", OrgNodeKind::MultilineCommand, R"RAW(Multiline command such as code block, latex equation, large block of passthrough code. Some built-in org-mode commands do not requires `#+begin` prefix, (such as `#+quote` or `#+example`) are represented by this type of block as well.)RAW")
    .value("Result", OrgNodeKind::Result, R"RAW(Command evaluation result)RAW")
    .value("Ident", OrgNodeKind::Ident, R"RAW(regular identifier - `alnum + [-_]` characters for punctuation. Identifiers are compared and parsed in style-insensetive manner, meaning `CODE_BLOCK`, `code-block` and `codeblock` are identical.)RAW")
    .value("BareIdent", OrgNodeKind::BareIdent, R"RAW(Bare identifier - any characters are allowed)RAW")
    .value("AdmonitionTag", OrgNodeKind::AdmonitionTag, R"RAW(Big ident used in conjunction with colon at the start of paragraph is considered an admonition tag: `NOTE: Text`, `WARNING: text` etc.)RAW")
    .value("BigIdent", OrgNodeKind::BigIdent, R"RAW(full-uppsercase identifier such as `MUST` or `TODO`)RAW")
    .value("VerbatimMultilineBlock", OrgNodeKind::VerbatimMultilineBlock, R"RAW(Verbatim mulitiline block that *might* be a part of `orgMultilineCommand` (in case of `#+begin-src`), but not necessarily. Can also be a part of =quote= and =example= multiline blocks.)RAW")
    .value("CodeLine", OrgNodeKind::CodeLine, R"RAW(Single line of source code)RAW")
    .value("CodeText", OrgNodeKind::CodeText, R"RAW(Block of source code text)RAW")
    .value("CodeTangle", OrgNodeKind::CodeTangle, R"RAW(Single tangle target in the code block)RAW")
    .value("CodeCallout", OrgNodeKind::CodeCallout, R"RAW(`(refs:` callout in the source code)RAW")
    .value("QuoteBlock", OrgNodeKind::QuoteBlock, R"RAW(`#+begin_quote:` block in code)RAW")
    .value("CommentBlock", OrgNodeKind::CommentBlock, R"RAW(`#+begin_comment:` block in code)RAW")
    .value("AdmonitionBlock", OrgNodeKind::AdmonitionBlock)
    .value("CenterBlock", OrgNodeKind::CenterBlock, R"RAW(')RAW")
    .value("VerseBlock", OrgNodeKind::VerseBlock)
    .value("Example", OrgNodeKind::Example, R"RAW(Verbatim example text block)RAW")
    .value("SrcCode", OrgNodeKind::SrcCode, R"RAW(Block of source code - can be multiline, single-line and)RAW")
    .value("SrcInlineCode", OrgNodeKind::SrcInlineCode, R"RAW(inline piece of code (such as `src_nim`),. Latter is different from regular monospaced text inside of `~~` pair as it contains additional internal structure, optional parameter for code evaluation etc.)RAW")
    .value("InlineCallCode", OrgNodeKind::InlineCallCode, R"RAW(Call to named source code block.)RAW")
    .value("CmdCallCode", OrgNodeKind::CmdCallCode, R"RAW(Call to named source code block.)RAW")
    .value("PassCode", OrgNodeKind::PassCode, R"RAW(Passthrough block. Inline, multiline, or single-line. Syntax is `@@<backend-name>:<any-body>@@`. Has line and block syntax respectively)RAW")
    .value("CmdArguments", OrgNodeKind::CmdArguments, R"RAW(Command arguments)RAW")
    .value("CmdFlag", OrgNodeKind::CmdFlag, R"RAW(Flag for source code block. For example `-n`, which is used to to make source code block export with lines)RAW")
    .value("CmdKey", OrgNodeKind::CmdKey)
    .value("CmdValue", OrgNodeKind::CmdValue)
    .value("CmdNamedValue", OrgNodeKind::CmdNamedValue, R"RAW(Key-value pair for source code block call.)RAW")
    .value("UrgencyStatus", OrgNodeKind::UrgencyStatus, R"RAW(Subtree importance level, such as `[#A]` or `[#B]`. Default org-mode only allows single character for contents inside of `[]`, but this parser makes it possible to use any regular identifier, such as `[#urgent]`.)RAW")
    .value("TextSeparator", OrgNodeKind::TextSeparator, R"RAW(Long horizontal line `----`)RAW")
    .value("Paragraph", OrgNodeKind::Paragraph, R"RAW(Single 'paragraph' of text. Used as generic container for any place in AST where unordered sentence might be encountered (e.g. caption, link description) - not limited to actual paragraph)RAW")
    .value("AnnotatedParagraph", OrgNodeKind::AnnotatedParagraph, R"RAW(Annotated paragraph -- a wrapper around a regular paragraph kind with added admonition, footnote, list tag prefix and similar types. `[fn:ID] Some Text` is an annotated paragraph, just like `NOTE: Text` or `- Prefix :: Body` (in this case list header is an annotated paragraph))RAW")
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
    .value("BackendRaw", OrgNodeKind::BackendRaw, R"RAW(Raw content to be passed to a particular backend. This is the most
     compact way of quoting export strings, after `#+<backend>:
     <single-backend-line>` and `#+begin-export <backend>`
     `<multiple-lines>`.)RAW")
    .value("Symbol", OrgNodeKind::Symbol, R"RAW(Special symbol that should be exported differently to various backends - greek letters (`lpha`), mathematical notations and so on.)RAW")
    .value("TimeAssoc", OrgNodeKind::TimeAssoc, R"RAW(Time association pair for the subtree deadlines.)RAW")
    .value("StaticActiveTime", OrgNodeKind::StaticActiveTime)
    .value("StaticInactiveTime", OrgNodeKind::StaticInactiveTime)
    .value("DynamicActiveTime", OrgNodeKind::DynamicActiveTime)
    .value("DynamicInactiveTime", OrgNodeKind::DynamicInactiveTime, R"RAW(Single date and time entry (active or inactive),, possibly with repeater interval. Is not parsed directly, and instead contains `orgRawText` that can be parsed later)RAW")
    .value("TimeRange", OrgNodeKind::TimeRange, R"RAW(Date and time range format - two `orgDateTime` entries)RAW")
    .value("SimpleTime", OrgNodeKind::SimpleTime, R"RAW(Result of the time range evaluation or trailing annotation a subtree)RAW")
    .value("Details", OrgNodeKind::Details, R"RAW(`#+begin_details`  section)RAW")
    .value("Summary", OrgNodeKind::Summary, R"RAW(`#+begin_summary` section)RAW")
    .value("Table", OrgNodeKind::Table, R"RAW(Org-mode table. Tables can be writtein in different formats, but in
   the end they are all represented using single ast type. NOTE: it is
   not guaranteed that all subnodes for table are exactly
   `orgTableRow` - sometimes additional property metadata might be
   used, making AST like `Table[AssocStmtList[Command[_],
   TableRow[_]]]` possible)RAW")
    .value("TableRow", OrgNodeKind::TableRow, R"RAW(Horizontal table row)RAW")
    .value("TableCell", OrgNodeKind::TableCell, R"RAW(Single cell in row. Might contain anyting, including other tables, simple text paragraph etc.)RAW")
    .value("InlineFootnote", OrgNodeKind::InlineFootnote, R"RAW(Inline footnote with text placed directly in the node body.)RAW")
    .value("Footnote", OrgNodeKind::Footnote, R"RAW(Footnote entry. Just as regular links - internal content is not parsed, and instead just cut out verbatim into target AST node.)RAW")
    .value("Horizontal", OrgNodeKind::Horizontal, R"RAW(Horizotal rule. Rule body might contain other subnodes, to represnt `---- some text ----` kind of formatting.)RAW")
    .value("Filetags", OrgNodeKind::Filetags, R"RAW(`#+filetags:` line command)RAW")
    .value("OrgTag", OrgNodeKind::OrgTag, R"RAW(Original format of org-mode tags in form of `:tagname:`. Might
   contain one or mode identifgiers, but does not provide support for
   nesting - `:tag1:tag2:`. Can only be placed within restricted set
   of places such as subtree headings and has separate place in AST
   when allowed (`orgSubtree` always has subnode `№4` with either
   `orgEmpty` or `orgOrgTag`))RAW")
    .value("HashTag", OrgNodeKind::HashTag, R"RAW(More commonly used `#hashtag` format, with some additional
   extension. Can be placed anywere in the document (including section
   headers), but does not have separate place in AST (e.g. considered
   regular part of the text))RAW")
    .value("MetaSymbol", OrgNodeKind::MetaSymbol, R"RAW(`\sym{}` with explicit arguments)RAW")
    .value("AtMention", OrgNodeKind::AtMention, R"RAW(`@user`)RAW")
    .value("BracTag", OrgNodeKind::BracTag, R"RAW(Custom extension to org-mode. Similarly to `BigIdent` used to have something like informal keywords `MUST`, `OPTIONAL`, but instead aimed /specifically/ at commit message headers - `[FEATURE]`, `[FIX]` and so on.)RAW")
    .value("Drawer", OrgNodeKind::Drawer, R"RAW(Single enclosed drawer like `:properties: ... :end:` or `:logbook: ... :end:`)RAW")
    .value("LatexClass", OrgNodeKind::LatexClass)
    .value("LatexHeader", OrgNodeKind::LatexHeader)
    .value("LatexCompiler", OrgNodeKind::LatexCompiler)
    .value("LatexClassOptions", OrgNodeKind::LatexClassOptions)
    .value("HtmlHead", OrgNodeKind::HtmlHead)
    .value("Columns", OrgNodeKind::Columns, R"RAW(`#+columns:` line command for specifying formatting of the org-mode clock table visualization on per-file basis.)RAW")
    .value("CmdPropertyArgs", OrgNodeKind::CmdPropertyArgs, R"RAW(`#+property:` command)RAW")
    .value("CmdPropertyText", OrgNodeKind::CmdPropertyText, R"RAW(`#+property:` command)RAW")
    .value("CmdPropertyRaw", OrgNodeKind::CmdPropertyRaw, R"RAW(`#+property:` command)RAW")
    .value("PropertyList", OrgNodeKind::PropertyList)
    .value("Property", OrgNodeKind::Property, R"RAW(`:property:` drawer)RAW")
    .value("Placeholder", OrgNodeKind::Placeholder, R"RAW(Placeholder entry in text, usually writte like `<text to replace>`)RAW")
    .value("SubtreeDescription", OrgNodeKind::SubtreeDescription, R"RAW(`:description:` entry)RAW")
    .value("SubtreeUrgency", OrgNodeKind::SubtreeUrgency)
    .value("Logbook", OrgNodeKind::Logbook, R"RAW(`:logbook:` entry storing note information)RAW")
    .value("LogbookStateChange", OrgNodeKind::LogbookStateChange, R"RAW(Annotation about change in the subtree todo state)RAW")
    .value("RadioTarget", OrgNodeKind::RadioTarget, R"RAW(`<<<RADIO>>>`)RAW")
    .value("Target", OrgNodeKind::Target, R"RAW(`<<TARGET>>`)RAW")
    .def("__iter__", [](OrgNodeKind _self) -> PyEnumIterator<OrgNodeKind> {
                     return
                     PyEnumIterator<OrgNodeKind>
                     ();
                     })
    ;
  bind_enum_iterator<OrgSemKind>(m, "OrgSemKind");
  pybind11::enum_<OrgSemKind>(m, "OrgSemKind")
    .value("StmtList", OrgSemKind::StmtList)
    .value("Empty", OrgSemKind::Empty)
    .value("Cell", OrgSemKind::Cell)
    .value("Row", OrgSemKind::Row)
    .value("Table", OrgSemKind::Table)
    .value("HashTag", OrgSemKind::HashTag)
    .value("Footnote", OrgSemKind::Footnote)
    .value("Completion", OrgSemKind::Completion)
    .value("Paragraph", OrgSemKind::Paragraph)
    .value("AnnotatedParagraph", OrgSemKind::AnnotatedParagraph)
    .value("Center", OrgSemKind::Center)
    .value("Caption", OrgSemKind::Caption)
    .value("CmdName", OrgSemKind::CmdName)
    .value("CmdResults", OrgSemKind::CmdResults)
    .value("CommandGroup", OrgSemKind::CommandGroup)
    .value("Tblfm", OrgSemKind::Tblfm)
    .value("Quote", OrgSemKind::Quote)
    .value("CommentBlock", OrgSemKind::CommentBlock)
    .value("Verse", OrgSemKind::Verse)
    .value("Example", OrgSemKind::Example)
    .value("CmdArguments", OrgSemKind::CmdArguments)
    .value("CmdAttr", OrgSemKind::CmdAttr)
    .value("CmdArgument", OrgSemKind::CmdArgument)
    .value("Export", OrgSemKind::Export)
    .value("AdmonitionBlock", OrgSemKind::AdmonitionBlock)
    .value("Call", OrgSemKind::Call)
    .value("Code", OrgSemKind::Code)
    .value("Time", OrgSemKind::Time)
    .value("TimeRange", OrgSemKind::TimeRange)
    .value("Macro", OrgSemKind::Macro)
    .value("Symbol", OrgSemKind::Symbol)
    .value("SubtreeLog", OrgSemKind::SubtreeLog)
    .value("Subtree", OrgSemKind::Subtree)
    .value("InlineMath", OrgSemKind::InlineMath)
    .value("Escaped", OrgSemKind::Escaped)
    .value("Newline", OrgSemKind::Newline)
    .value("Space", OrgSemKind::Space)
    .value("Word", OrgSemKind::Word)
    .value("AtMention", OrgSemKind::AtMention)
    .value("RawText", OrgSemKind::RawText)
    .value("Punctuation", OrgSemKind::Punctuation)
    .value("Placeholder", OrgSemKind::Placeholder)
    .value("BigIdent", OrgSemKind::BigIdent)
    .value("Bold", OrgSemKind::Bold)
    .value("Underline", OrgSemKind::Underline)
    .value("Monospace", OrgSemKind::Monospace)
    .value("MarkQuote", OrgSemKind::MarkQuote)
    .value("Verbatim", OrgSemKind::Verbatim)
    .value("Italic", OrgSemKind::Italic)
    .value("Strike", OrgSemKind::Strike)
    .value("Par", OrgSemKind::Par)
    .value("List", OrgSemKind::List)
    .value("ListItem", OrgSemKind::ListItem)
    .value("Link", OrgSemKind::Link)
    .value("DocumentOptions", OrgSemKind::DocumentOptions)
    .value("Document", OrgSemKind::Document)
    .value("ParseError", OrgSemKind::ParseError)
    .value("FileTarget", OrgSemKind::FileTarget)
    .value("TextSeparator", OrgSemKind::TextSeparator)
    .value("Include", OrgSemKind::Include)
    .value("DocumentGroup", OrgSemKind::DocumentGroup)
    .def("__iter__", [](OrgSemKind _self) -> PyEnumIterator<OrgSemKind> {
                     return
                     PyEnumIterator<OrgSemKind>
                     ();
                     })
    ;
  pybind11::class_<UserTimeBreakdown>(m, "UserTimeBreakdown")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> UserTimeBreakdown {
                        UserTimeBreakdown result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("year", &UserTimeBreakdown::year)
    .def_readwrite("month", &UserTimeBreakdown::month)
    .def_readwrite("day", &UserTimeBreakdown::day)
    .def_readwrite("hour", &UserTimeBreakdown::hour)
    .def_readwrite("minute", &UserTimeBreakdown::minute)
    .def_readwrite("second", &UserTimeBreakdown::second)
    .def_readwrite("zone", &UserTimeBreakdown::zone)
    ;
  pybind11::class_<UserTime>(m, "UserTime")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> UserTime {
                        UserTime result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getBreakdown", static_cast<UserTimeBreakdown(UserTime::*)() const>(&UserTime::getBreakdown))
    .def("format", static_cast<std::string(UserTime::*)() const>(&UserTime::format))
    ;
  pybind11::class_<sem::OrgDocumentContext>(m, "OrgDocumentContext")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::OrgDocumentContext {
                        sem::OrgDocumentContext result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getSubtreeById",
         static_cast<Vec<sem::SemId<sem::Subtree>>(sem::OrgDocumentContext::*)(Str const&) const>(&sem::OrgDocumentContext::getSubtreeById),
         pybind11::arg("id"))
    .def("getLinkTarget",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::OrgDocumentContext::*)(sem::SemId<sem::Link> const&) const>(&sem::OrgDocumentContext::getLinkTarget),
         pybind11::arg("link"))
    .def("getRadioTarget",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::OrgDocumentContext::*)(Str const&) const>(&sem::OrgDocumentContext::getRadioTarget),
         pybind11::arg("name"))
    .def("addNodes",
         static_cast<void(sem::OrgDocumentContext::*)(sem::SemId<sem::Org> const&)>(&sem::OrgDocumentContext::addNodes),
         pybind11::arg("node"),
         R"RAW(\brief Recursively register all availble targets from the nodes.)RAW")
    ;
  pybind11::class_<OrgExporterJson>(m, "OrgExporterJson")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> OrgExporterJson {
                        OrgExporterJson result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("visitNode",
         static_cast<void(OrgExporterJson::*)(sem::SemId<sem::Org>)>(&OrgExporterJson::visitNode),
         pybind11::arg("node"),
         R"RAW(Visit top-level node of the exporter, filling in the internal
return state.)RAW")
    .def("exportToString", static_cast<std::string(OrgExporterJson::*)()>(&OrgExporterJson::exportToString))
    .def("exportToFile",
         static_cast<void(OrgExporterJson::*)(std::string)>(&OrgExporterJson::exportToFile),
         pybind11::arg("path"))
    ;
  pybind11::class_<ExporterTreeOpts>(m, "ExporterTreeOpts")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> ExporterTreeOpts {
                        ExporterTreeOpts result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("withLineCol", &ExporterTreeOpts::withLineCol)
    .def_readwrite("withOriginalId", &ExporterTreeOpts::withOriginalId)
    .def_readwrite("withSubnodeIdx", &ExporterTreeOpts::withSubnodeIdx)
    .def_readwrite("skipEmptyFields", &ExporterTreeOpts::skipEmptyFields)
    .def_readwrite("startLevel", &ExporterTreeOpts::startLevel)
    .def_readwrite("withColor", &ExporterTreeOpts::withColor)
    ;
  pybind11::class_<OrgExporterTree>(m, "OrgExporterTree")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> OrgExporterTree {
                        OrgExporterTree result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("toString",
         static_cast<std::string(OrgExporterTree::*)(sem::SemId<sem::Org>, ExporterTreeOpts)>(&OrgExporterTree::toString),
         pybind11::arg("node"),
         pybind11::arg("opts"))
    .def("toFile",
         static_cast<void(OrgExporterTree::*)(sem::SemId<sem::Org>, std::string, ExporterTreeOpts)>(&OrgExporterTree::toFile),
         pybind11::arg("node"),
         pybind11::arg("path"),
         pybind11::arg("opts"))
    ;
  pybind11::class_<OrgExporterYaml>(m, "OrgExporterYaml")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> OrgExporterYaml {
                        OrgExporterYaml result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("visitNode",
         static_cast<void(OrgExporterYaml::*)(sem::SemId<sem::Org>)>(&OrgExporterYaml::visitNode),
         pybind11::arg("node"),
         R"RAW(Visit top-level node of the exporter, filling in the internal
return state.)RAW")
    .def("exportToString", static_cast<std::string(OrgExporterYaml::*)()>(&OrgExporterYaml::exportToString))
    .def("exportToFile",
         static_cast<void(OrgExporterYaml::*)(std::string)>(&OrgExporterYaml::exportToFile),
         pybind11::arg("path"))
    ;
  pybind11::class_<OrgContext>(m, "OrgContext")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> OrgContext {
                        OrgContext result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("baseTokenTracePath", &OrgContext::baseTokenTracePath)
    .def_readwrite("tokenTracePath", &OrgContext::tokenTracePath)
    .def_readwrite("parseTracePath", &OrgContext::parseTracePath)
    .def_readwrite("semTracePath", &OrgContext::semTracePath)
    .def("parseFile",
         static_cast<sem::SemId<sem::Document>(OrgContext::*)(std::string)>(&OrgContext::parseFile),
         pybind11::arg("file"))
    .def("parseString",
         static_cast<sem::SemId<sem::Document>(OrgContext::*)(std::string const)>(&OrgContext::parseString),
         pybind11::arg("text"))
    .def("parseProtobuf",
         static_cast<sem::SemId<sem::Document>(OrgContext::*)(std::string const&)>(&OrgContext::parseProtobuf),
         pybind11::arg("file"))
    .def("saveProtobuf",
         static_cast<void(OrgContext::*)(sem::SemId<sem::Document>, std::string const&)>(&OrgContext::saveProtobuf),
         pybind11::arg("doc"),
         pybind11::arg("file"))
    .def("formatToString",
         static_cast<std::string(OrgContext::*)(sem::SemId<sem::Org>)>(&OrgContext::formatToString),
         pybind11::arg("arg"))
    .def("eachSubnodeRec",
         static_cast<void(OrgContext::*)(sem::SemId<sem::Org>, pybind11::function)>(&OrgContext::eachSubnodeRec),
         pybind11::arg("node"),
         pybind11::arg("callback"))
    ;
  pybind11::class_<ExporterPython>(m, "ExporterPython")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> ExporterPython {
                        ExporterPython result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("enablePyStreamTrace",
         static_cast<void(ExporterPython::*)(pybind11::object)>(&ExporterPython::enablePyStreamTrace),
         pybind11::arg("stream"))
    .def("enableBufferTrace", static_cast<void(ExporterPython::*)()>(&ExporterPython::enableBufferTrace))
    .def("getTraceBuffer", static_cast<std::string(ExporterPython::*)() const>(&ExporterPython::getTraceBuffer))
    .def("enableFileTrace",
         static_cast<void(ExporterPython::*)(std::string const&, bool)>(&ExporterPython::enableFileTrace),
         pybind11::arg("path"),
         pybind11::arg("colored"))
    .def("setVisitAnyIdAround",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setVisitAnyIdAround),
         pybind11::arg("cb"))
    .def("setVisitAnyIdIn",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setVisitAnyIdIn),
         pybind11::arg("cb"))
    .def("setVisitAnyField",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setVisitAnyField),
         pybind11::arg("cb"))
    .def("setEvalTopCb",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setEvalTopCb),
         pybind11::arg("cb"))
    .def("setVisitIdAround",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setVisitIdAround),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setEvalIdAround",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setEvalIdAround),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setVisitIdInCb",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setVisitIdInCb),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setEvalIdIn",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setEvalIdIn),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setVisitLeafField",
         static_cast<void(ExporterPython::*)(LeafFieldType, ExporterPython::PyFunc)>(&ExporterPython::setVisitLeafField),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setEvalLeafField",
         static_cast<void(ExporterPython::*)(LeafFieldType, ExporterPython::PyFunc)>(&ExporterPython::setEvalLeafField),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setVisitOrgField",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setVisitOrgField),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setEvalOrgField",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setEvalOrgField),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setSelf",
         static_cast<void(ExporterPython::*)(pybind11::object)>(&ExporterPython::setSelf),
         pybind11::arg("val"))
    .def("setNewOrgRes",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setNewOrgRes),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setNewAnyOrgRes",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setNewAnyOrgRes),
         pybind11::arg("cb"))
    .def("setNewLeafRes",
         static_cast<void(ExporterPython::*)(LeafFieldType, ExporterPython::PyFunc)>(&ExporterPython::setNewLeafRes),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setNewAnyLeafRes",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setNewAnyLeafRes),
         pybind11::arg("cb"))
    .def("setPushVisitAnyId",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setPushVisitAnyId),
         pybind11::arg("cb"))
    .def("setPopVisitAnyId",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setPopVisitAnyId),
         pybind11::arg("cb"))
    .def("setPushVisitId",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setPushVisitId),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setPopVisitIdCb",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setPopVisitIdCb),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setVisitAnyHookCb",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setVisitAnyHookCb),
         pybind11::arg("cb"))
    .def("setVisitIdHook",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setVisitIdHook),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("evalTop",
         static_cast<ExporterPython::Res(ExporterPython::*)(sem::SemId<sem::Org>)>(&ExporterPython::evalTop),
         pybind11::arg("org"))
    .def("eval",
         static_cast<ExporterPython::Res(ExporterPython::*)(sem::SemId<sem::Org>)>(&ExporterPython::eval),
         pybind11::arg("org"))
    ;
  bind_enum_iterator<LeafFieldType>(m, "LeafFieldType");
  pybind11::enum_<LeafFieldType>(m, "LeafFieldType")
    .value("Int", LeafFieldType::Int)
    .value("UserTimeKind", LeafFieldType::UserTimeKind)
    .value("QDate", LeafFieldType::QDate)
    .value("Bool", LeafFieldType::Bool)
    .value("FixedIdVec", LeafFieldType::FixedIdVec)
    .value("TopIdVec", LeafFieldType::TopIdVec)
    .value("QDateTime", LeafFieldType::QDateTime)
    .value("Str", LeafFieldType::Str)
    .value("Any", LeafFieldType::Any)
    .def("__iter__", [](LeafFieldType _self) -> PyEnumIterator<LeafFieldType> {
                     return
                     PyEnumIterator<LeafFieldType>
                     ();
                     })
    ;
}
/* clang-format on */