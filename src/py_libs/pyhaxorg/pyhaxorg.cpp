/* clang-format off */
#undef slots
#include <pybind11/pybind11.h>
#include <sem/SemOrg.hpp>
#include <pybind11/stl.h>
#ifndef IN_CLANGD_PROCESSING
  #define PY_HAXORG_COMPILING
  #include "pyhaxorg_manual_impl.hpp"
#endif
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemIdT<sem::Row>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemIdT<sem::Row>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemIdT<sem::HashTag>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemIdT<sem::HashTag>>)
PYBIND11_MAKE_OPAQUE(std::vector<Str>)
PYBIND11_MAKE_OPAQUE(Vec<Str>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemIdT<sem::CmdArgument>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemIdT<sem::CmdArgument>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Code::Switch>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Code::Switch>)
PYBIND11_MAKE_OPAQUE(std::vector<int>)
PYBIND11_MAKE_OPAQUE(Vec<int>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Symbol::Param>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Symbol::Param>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemIdT<sem::SubtreeLog>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemIdT<sem::SubtreeLog>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Subtree::Property>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Subtree::Property>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Subtree::Period>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Subtree::Period>)
PYBIND11_MODULE(pyhaxorg, m) {
  bind_vector<sem::SemId>(m, "VecOfSemId");
  bind_vector<sem::SemIdT<sem::Row>>(m, "VecOfSemIdTOfRow");
  bind_vector<sem::SemIdT<sem::HashTag>>(m, "VecOfSemIdTOfHashTag");
  bind_vector<Str>(m, "VecOfStr");
  bind_vector<sem::SemIdT<sem::CmdArgument>>(m, "VecOfSemIdTOfCmdArgument");
  bind_vector<sem::Code::Switch>(m, "VecOfSwitch");
  bind_vector<int>(m, "VecOfint");
  bind_vector<sem::Symbol::Param>(m, "VecOfParam");
  bind_vector<sem::SemIdT<sem::SubtreeLog>>(m, "VecOfSemIdTOfSubtreeLog");
  bind_vector<sem::Subtree::Property>(m, "VecOfProperty");
  bind_vector<sem::Subtree::Period>(m, "VecOfPeriod");
  #ifndef IN_CLANGD_PROCESSING
    #define PY_HAXORG_COMPILING
    #include "pyhaxorg_manual_wrap.hpp"
  #endif
  pybind11::class_<sem::SemIdT<sem::Stmt>, sem::SemId>(m, "SemStmt")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Stmt> { return sem::SemIdT<sem::Stmt>::Nil(); }))
    .def_property("attached",
                  [](sem::SemIdT<sem::Stmt> _self) -> Vec<sem::SemId> { return _self->attached; },
                  [](sem::SemIdT<sem::Stmt> _self, Vec<sem::SemId> attached) { _self->attached = attached; })
    .def("getAttached",
         [](sem::SemIdT<sem::Stmt> _self, OrgSemKind kind) -> Opt<sem::SemId> { return _self->getAttached(kind); },
         pybind11::arg("kind"))
    ;
  pybind11::class_<sem::SemIdT<sem::Inline>, sem::SemId>(m, "SemInline")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Inline> { return sem::SemIdT<sem::Inline>::Nil(); }))
    ;
  pybind11::class_<sem::SemIdT<sem::StmtList>, sem::SemId>(m, "SemStmtList")
    .def(pybind11::init([]() -> sem::SemIdT<sem::StmtList> { return sem::SemIdT<sem::StmtList>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::StmtList> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::StmtList> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::Empty>, sem::SemId>(m, "SemEmpty")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Empty> { return sem::SemIdT<sem::Empty>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Empty> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Empty> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::Row>, sem::SemId>(m, "SemRow")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Row> { return sem::SemIdT<sem::Row>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Row> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Row> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::Table>, sem::SemId>(m, "SemTable")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Table> { return sem::SemIdT<sem::Table>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Table> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Table> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("rows",
                  [](sem::SemIdT<sem::Table> _self) -> Vec<sem::SemIdT<sem::Row>> { return _self->rows; },
                  [](sem::SemIdT<sem::Table> _self, Vec<sem::SemIdT<sem::Row>> rows) { _self->rows = rows; })
    .def_property("attached",
                  [](sem::SemIdT<sem::Table> _self) -> Vec<sem::SemId> { return _self->attached; },
                  [](sem::SemIdT<sem::Table> _self, Vec<sem::SemId> attached) { _self->attached = attached; })
    .def("getAttached",
         [](sem::SemIdT<sem::Table> _self, OrgSemKind kind) -> Opt<sem::SemId> { return _self->getAttached(kind); },
         pybind11::arg("kind"))
    ;
  pybind11::class_<sem::SemIdT<sem::HashTag>, sem::SemId>(m, "SemHashTag")
    .def(pybind11::init([]() -> sem::SemIdT<sem::HashTag> { return sem::SemIdT<sem::HashTag>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::HashTag> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::HashTag> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("head",
                  [](sem::SemIdT<sem::HashTag> _self) -> Str { return _self->head; },
                  [](sem::SemIdT<sem::HashTag> _self, Str head) { _self->head = head; })
    .def_property("subtags",
                  [](sem::SemIdT<sem::HashTag> _self) -> Vec<sem::SemIdT<sem::HashTag>> { return _self->subtags; },
                  [](sem::SemIdT<sem::HashTag> _self, Vec<sem::SemIdT<sem::HashTag>> subtags) { _self->subtags = subtags; })
    .def("prefixMatch",
         [](sem::SemIdT<sem::HashTag> _self, Vec<Str> const& prefix) -> bool { return _self->prefixMatch(prefix); },
         pybind11::arg("prefix"),
         R"RAW(Check if list of tag names is a prefix for either of the nested hash tags in this one)RAW")
    ;
  pybind11::class_<sem::SemIdT<sem::Footnote>, sem::SemId>(m, "SemFootnote")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Footnote> { return sem::SemIdT<sem::Footnote>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Footnote> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Footnote> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("tag",
                  [](sem::SemIdT<sem::Footnote> _self) -> Str { return _self->tag; },
                  [](sem::SemIdT<sem::Footnote> _self, Str tag) { _self->tag = tag; })
    .def_property("definition",
                  [](sem::SemIdT<sem::Footnote> _self) -> Opt<sem::SemId> { return _self->definition; },
                  [](sem::SemIdT<sem::Footnote> _self, Opt<sem::SemId> definition) { _self->definition = definition; })
    ;
  pybind11::class_<sem::SemIdT<sem::Completion>, sem::SemId>(m, "SemCompletion")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Completion> { return sem::SemIdT<sem::Completion>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Completion> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Completion> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("done",
                  [](sem::SemIdT<sem::Completion> _self) -> int { return _self->done; },
                  [](sem::SemIdT<sem::Completion> _self, int done) { _self->done = done; })
    .def_property("full",
                  [](sem::SemIdT<sem::Completion> _self) -> int { return _self->full; },
                  [](sem::SemIdT<sem::Completion> _self, int full) { _self->full = full; })
    .def_property("isPercent",
                  [](sem::SemIdT<sem::Completion> _self) -> bool { return _self->isPercent; },
                  [](sem::SemIdT<sem::Completion> _self, bool isPercent) { _self->isPercent = isPercent; })
    ;
  pybind11::class_<sem::SemIdT<sem::Paragraph>, sem::SemId>(m, "SemParagraph")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Paragraph> { return sem::SemIdT<sem::Paragraph>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Paragraph> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Paragraph> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("attached",
                  [](sem::SemIdT<sem::Paragraph> _self) -> Vec<sem::SemId> { return _self->attached; },
                  [](sem::SemIdT<sem::Paragraph> _self, Vec<sem::SemId> attached) { _self->attached = attached; })
    .def("isFootnoteDefinition", [](sem::SemIdT<sem::Paragraph> _self) -> bool { return _self->isFootnoteDefinition(); }, R"RAW(Check if paragraph defines footnote)RAW")
    .def("getAttached",
         [](sem::SemIdT<sem::Paragraph> _self, OrgSemKind kind) -> Opt<sem::SemId> { return _self->getAttached(kind); },
         pybind11::arg("kind"))
    ;
  pybind11::class_<sem::SemIdT<sem::Format>, sem::SemId>(m, "SemFormat")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Format> { return sem::SemIdT<sem::Format>::Nil(); }))
    ;
  pybind11::class_<sem::SemIdT<sem::Center>, sem::SemId>(m, "SemCenter")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Center> { return sem::SemIdT<sem::Center>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Center> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Center> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::Command>, sem::SemId>(m, "SemCommand")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Command> { return sem::SemIdT<sem::Command>::Nil(); }))
    ;
  pybind11::class_<sem::SemIdT<sem::LineCommand>, sem::SemId>(m, "SemLineCommand")
    .def(pybind11::init([]() -> sem::SemIdT<sem::LineCommand> { return sem::SemIdT<sem::LineCommand>::Nil(); }))
    ;
  pybind11::class_<sem::SemIdT<sem::Standalone>, sem::SemId>(m, "SemStandalone")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Standalone> { return sem::SemIdT<sem::Standalone>::Nil(); }))
    ;
  pybind11::class_<sem::SemIdT<sem::Attached>, sem::SemId>(m, "SemAttached")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Attached> { return sem::SemIdT<sem::Attached>::Nil(); }))
    ;
  pybind11::class_<sem::SemIdT<sem::Caption>, sem::SemId>(m, "SemCaption")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Caption> { return sem::SemIdT<sem::Caption>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Caption> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Caption> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("text",
                  [](sem::SemIdT<sem::Caption> _self) -> sem::SemIdT<sem::Paragraph> { return _self->text; },
                  [](sem::SemIdT<sem::Caption> _self, sem::SemIdT<sem::Paragraph> text) { _self->text = text; })
    ;
  pybind11::class_<sem::SemIdT<sem::CommandGroup>, sem::SemId>(m, "SemCommandGroup")
    .def(pybind11::init([]() -> sem::SemIdT<sem::CommandGroup> { return sem::SemIdT<sem::CommandGroup>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::CommandGroup> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::CommandGroup> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("attached",
                  [](sem::SemIdT<sem::CommandGroup> _self) -> Vec<sem::SemId> { return _self->attached; },
                  [](sem::SemIdT<sem::CommandGroup> _self, Vec<sem::SemId> attached) { _self->attached = attached; })
    .def("getAttached",
         [](sem::SemIdT<sem::CommandGroup> _self, OrgSemKind kind) -> Opt<sem::SemId> { return _self->getAttached(kind); },
         pybind11::arg("kind"))
    ;
  pybind11::class_<sem::SemIdT<sem::Block>, sem::SemId>(m, "SemBlock")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Block> { return sem::SemIdT<sem::Block>::Nil(); }))
    ;
  pybind11::class_<sem::SemIdT<sem::Quote>, sem::SemId>(m, "SemQuote")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Quote> { return sem::SemIdT<sem::Quote>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Quote> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Quote> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("text",
                  [](sem::SemIdT<sem::Quote> _self) -> sem::SemIdT<sem::Paragraph> { return _self->text; },
                  [](sem::SemIdT<sem::Quote> _self, sem::SemIdT<sem::Paragraph> text) { _self->text = text; })
    ;
  pybind11::class_<sem::SemIdT<sem::Verse>, sem::SemId>(m, "SemVerse")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Verse> { return sem::SemIdT<sem::Verse>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Verse> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Verse> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::Example>, sem::SemId>(m, "SemExample")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Example> { return sem::SemIdT<sem::Example>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Example> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Example> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::CmdArguments>, sem::SemId>(m, "SemCmdArguments")
    .def(pybind11::init([]() -> sem::SemIdT<sem::CmdArguments> { return sem::SemIdT<sem::CmdArguments>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::CmdArguments> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::CmdArguments> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("positional",
                  [](sem::SemIdT<sem::CmdArguments> _self) -> Vec<sem::SemIdT<sem::CmdArgument>> { return _self->positional; },
                  [](sem::SemIdT<sem::CmdArguments> _self, Vec<sem::SemIdT<sem::CmdArgument>> positional) { _self->positional = positional; })
    .def_property("named",
                  [](sem::SemIdT<sem::CmdArguments> _self) -> UnorderedMap<Str, sem::SemIdT<sem::CmdArgument>> { return _self->named; },
                  [](sem::SemIdT<sem::CmdArguments> _self, UnorderedMap<Str, sem::SemIdT<sem::CmdArgument>> named) { _self->named = named; })
    .def("popArg",
         [](sem::SemIdT<sem::CmdArguments> _self, Str key) -> Opt<sem::SemIdT<sem::CmdArgument>> { return _self->popArg(key); },
         pybind11::arg("key"),
         R"RAW(Remove argument value from the map and return it if present)RAW")
    ;
  pybind11::class_<sem::SemIdT<sem::CmdArgument>, sem::SemId>(m, "SemCmdArgument")
    .def(pybind11::init([]() -> sem::SemIdT<sem::CmdArgument> { return sem::SemIdT<sem::CmdArgument>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::CmdArgument> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::CmdArgument> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("key",
                  [](sem::SemIdT<sem::CmdArgument> _self) -> Opt<Str> { return _self->key; },
                  [](sem::SemIdT<sem::CmdArgument> _self, Opt<Str> key) { _self->key = key; })
    .def_property("value",
                  [](sem::SemIdT<sem::CmdArgument> _self) -> Str { return _self->value; },
                  [](sem::SemIdT<sem::CmdArgument> _self, Str value) { _self->value = value; })
    .def("getInt", [](sem::SemIdT<sem::CmdArgument> _self) -> Opt<int> { return _self->getInt(); }, R"RAW(Parse argument as integer value)RAW")
    .def("getBool", [](sem::SemIdT<sem::CmdArgument> _self) -> Opt<bool> { return _self->getBool(); }, R"RAW(Get argument as bool)RAW")
    .def("getString", [](sem::SemIdT<sem::CmdArgument> _self) -> Str { return _self->getString(); }, R"RAW(Get original string)RAW")
    ;
  pybind11::class_<sem::SemIdT<sem::Export>, sem::SemId>(m, "SemExport")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Export> { return sem::SemIdT<sem::Export>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Export> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Export> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("format",
                  [](sem::SemIdT<sem::Export> _self) -> sem::Export::Format { return _self->format; },
                  [](sem::SemIdT<sem::Export> _self, sem::Export::Format format) { _self->format = format; })
    .def_property("exporter",
                  [](sem::SemIdT<sem::Export> _self) -> Str { return _self->exporter; },
                  [](sem::SemIdT<sem::Export> _self, Str exporter) { _self->exporter = exporter; })
    .def_property("parameters",
                  [](sem::SemIdT<sem::Export> _self) -> Opt<sem::SemIdT<sem::CmdArguments>> { return _self->parameters; },
                  [](sem::SemIdT<sem::Export> _self, Opt<sem::SemIdT<sem::CmdArguments>> parameters) { _self->parameters = parameters; })
    .def_property("placement",
                  [](sem::SemIdT<sem::Export> _self) -> Opt<Str> { return _self->placement; },
                  [](sem::SemIdT<sem::Export> _self, Opt<Str> placement) { _self->placement = placement; })
    .def_property("content",
                  [](sem::SemIdT<sem::Export> _self) -> Str { return _self->content; },
                  [](sem::SemIdT<sem::Export> _self, Str content) { _self->content = content; })
    ;
  pybind11::enum_<sem::Export::Format>(m, "ExportFormat")
    .value("Inline", sem::Export::Format::Inline, R"RAW(Export directly in the paragraph)RAW")
    .value("Line", sem::Export::Format::Line, R"RAW(Single line of export)RAW")
    .value("Block", sem::Export::Format::Block, R"RAW(Multiple lines of export)RAW")
    .export_values()
    ;
  pybind11::class_<sem::SemIdT<sem::AdmonitionBlock>, sem::SemId>(m, "SemAdmonitionBlock")
    .def(pybind11::init([]() -> sem::SemIdT<sem::AdmonitionBlock> { return sem::SemIdT<sem::AdmonitionBlock>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::AdmonitionBlock> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::AdmonitionBlock> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::Code>, sem::SemId>(m, "SemCode")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Code> { return sem::SemIdT<sem::Code>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Code> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Code> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("lang",
                  [](sem::SemIdT<sem::Code> _self) -> Opt<Str> { return _self->lang; },
                  [](sem::SemIdT<sem::Code> _self, Opt<Str> lang) { _self->lang = lang; })
    .def_property("switches",
                  [](sem::SemIdT<sem::Code> _self) -> Vec<sem::Code::Switch> { return _self->switches; },
                  [](sem::SemIdT<sem::Code> _self, Vec<sem::Code::Switch> switches) { _self->switches = switches; })
    .def_property("exports",
                  [](sem::SemIdT<sem::Code> _self) -> sem::Code::Exports { return _self->exports; },
                  [](sem::SemIdT<sem::Code> _self, sem::Code::Exports exports) { _self->exports = exports; })
    .def_property("parameters",
                  [](sem::SemIdT<sem::Code> _self) -> Opt<sem::SemIdT<sem::CmdArguments>> { return _self->parameters; },
                  [](sem::SemIdT<sem::Code> _self, Opt<sem::SemIdT<sem::CmdArguments>> parameters) { _self->parameters = parameters; })
    .def_property("cache",
                  [](sem::SemIdT<sem::Code> _self) -> bool { return _self->cache; },
                  [](sem::SemIdT<sem::Code> _self, bool cache) { _self->cache = cache; })
    .def_property("eval",
                  [](sem::SemIdT<sem::Code> _self) -> bool { return _self->eval; },
                  [](sem::SemIdT<sem::Code> _self, bool eval) { _self->eval = eval; })
    .def_property("noweb",
                  [](sem::SemIdT<sem::Code> _self) -> bool { return _self->noweb; },
                  [](sem::SemIdT<sem::Code> _self, bool noweb) { _self->noweb = noweb; })
    .def_property("hlines",
                  [](sem::SemIdT<sem::Code> _self) -> bool { return _self->hlines; },
                  [](sem::SemIdT<sem::Code> _self, bool hlines) { _self->hlines = hlines; })
    .def_property("tangle",
                  [](sem::SemIdT<sem::Code> _self) -> bool { return _self->tangle; },
                  [](sem::SemIdT<sem::Code> _self, bool tangle) { _self->tangle = tangle; })
    ;
  pybind11::class_<sem::Code::Switch>(m, "CodeSwitch")
    .def(pybind11::init<>())
    .def_readwrite("data", &sem::Code::Switch::data)
    .def("getLineStart", static_cast<sem::Code::Switch::LineStart&(sem::Code::Switch::*)()>(&sem::Code::Switch::getLineStart))
    .def("getCalloutFormat", static_cast<sem::Code::Switch::CalloutFormat&(sem::Code::Switch::*)()>(&sem::Code::Switch::getCalloutFormat))
    .def("getRemoveCallout", static_cast<sem::Code::Switch::RemoveCallout&(sem::Code::Switch::*)()>(&sem::Code::Switch::getRemoveCallout))
    .def("getEmphasizeLine", static_cast<sem::Code::Switch::EmphasizeLine&(sem::Code::Switch::*)()>(&sem::Code::Switch::getEmphasizeLine))
    .def("getDedent", static_cast<sem::Code::Switch::Dedent&(sem::Code::Switch::*)()>(&sem::Code::Switch::getDedent))
    .def("getKind", static_cast<sem::Code::Switch::Kind(sem::Code::Switch::*)() const>(&sem::Code::Switch::getKind))
    ;
  pybind11::class_<sem::Code::Switch::LineStart>(m, "CodeSwitchLineStart")
    .def(pybind11::init<>())
    .def_readwrite("start", &sem::Code::Switch::LineStart::start, R"RAW(First line number)RAW")
    .def_readwrite("extendLast", &sem::Code::Switch::LineStart::extendLast, R"RAW(Continue numbering from the previous block nstead of starting anew)RAW")
    ;
  pybind11::class_<sem::Code::Switch::CalloutFormat>(m, "CodeSwitchCalloutFormat")
    .def(pybind11::init<>())
    .def_readwrite("format", &sem::Code::Switch::CalloutFormat::format)
    ;
  pybind11::class_<sem::Code::Switch::RemoveCallout>(m, "CodeSwitchRemoveCallout")
    .def(pybind11::init<>())
    .def_readwrite("remove", &sem::Code::Switch::RemoveCallout::remove)
    ;
  pybind11::class_<sem::Code::Switch::EmphasizeLine>(m, "CodeSwitchEmphasizeLine")
    .def(pybind11::init<>())
    .def_readwrite("line", &sem::Code::Switch::EmphasizeLine::line)
    ;
  pybind11::class_<sem::Code::Switch::Dedent>(m, "CodeSwitchDedent")
    .def(pybind11::init<>())
    .def_readwrite("value", &sem::Code::Switch::Dedent::value)
    ;
  pybind11::enum_<sem::Code::Switch::Kind>(m, "CodeSwitchKind")
    .value("LineStart", sem::Code::Switch::Kind::LineStart)
    .value("CalloutFormat", sem::Code::Switch::Kind::CalloutFormat)
    .value("RemoveCallout", sem::Code::Switch::Kind::RemoveCallout)
    .value("EmphasizeLine", sem::Code::Switch::Kind::EmphasizeLine)
    .value("Dedent", sem::Code::Switch::Kind::Dedent)
    .export_values()
    ;
  pybind11::enum_<sem::Code::Results>(m, "CodeResults")
    .value("Replace", sem::Code::Results::Replace, R"RAW(Remove old result, replace with new value)RAW")
    .export_values()
    ;
  pybind11::enum_<sem::Code::Exports>(m, "CodeExports")
    .value("None", sem::Code::Exports::None, R"RAW(Hide both original code and run result)RAW")
    .value("Both", sem::Code::Exports::Both, R"RAW(Show output and code)RAW")
    .value("Code", sem::Code::Exports::Code, R"RAW(Show only code)RAW")
    .value("Results", sem::Code::Exports::Results, R"RAW(Show only evaluation results)RAW")
    .export_values()
    ;
  pybind11::class_<sem::SemIdT<sem::Time>, sem::SemId>(m, "SemTime")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Time> { return sem::SemIdT<sem::Time>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Time> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Time> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("isActive",
                  [](sem::SemIdT<sem::Time> _self) -> bool { return _self->isActive; },
                  [](sem::SemIdT<sem::Time> _self, bool isActive) { _self->isActive = isActive; })
    .def_property("time",
                  [](sem::SemIdT<sem::Time> _self) -> sem::Time::TimeVariant { return _self->time; },
                  [](sem::SemIdT<sem::Time> _self, sem::Time::TimeVariant time) { _self->time = time; })
    .def("getStatic", [](sem::SemIdT<sem::Time> _self) -> sem::Time::Static& { return _self->getStatic(); })
    .def("getDynamic", [](sem::SemIdT<sem::Time> _self) -> sem::Time::Dynamic& { return _self->getDynamic(); })
    .def("getTimeKind", [](sem::SemIdT<sem::Time> _self) -> sem::Time::TimeKind { return _self->getTimeKind(); })
    ;
  pybind11::class_<sem::Time::Repeat>(m, "TimeRepeat")
    .def(pybind11::init<>())
    .def_readwrite("mode", &sem::Time::Repeat::mode, R"RAW(mode)RAW")
    .def_readwrite("period", &sem::Time::Repeat::period, R"RAW(period)RAW")
    .def_readwrite("count", &sem::Time::Repeat::count, R"RAW(count)RAW")
    ;
  pybind11::enum_<sem::Time::Repeat::Mode>(m, "TimeRepeatMode")
    .value("None", sem::Time::Repeat::Mode::None, R"RAW(Do not repeat task on completion)RAW")
    .value("Exact", sem::Time::Repeat::Mode::Exact, R"RAW(?)RAW")
    .value("FirstMatch", sem::Time::Repeat::Mode::FirstMatch, R"RAW(Repeat on the first matching day in the future)RAW")
    .value("SameDay", sem::Time::Repeat::Mode::SameDay, R"RAW(Repeat task on the same day next week/month/year)RAW")
    .export_values()
    ;
  pybind11::enum_<sem::Time::Repeat::Period>(m, "TimeRepeatPeriod")
    .value("Year", sem::Time::Repeat::Period::Year)
    .value("Month", sem::Time::Repeat::Period::Month)
    .value("Week", sem::Time::Repeat::Period::Week)
    .value("Day", sem::Time::Repeat::Period::Day)
    .value("Hour", sem::Time::Repeat::Period::Hour)
    .value("Minute", sem::Time::Repeat::Period::Minute)
    .export_values()
    ;
  pybind11::class_<sem::Time::Static>(m, "TimeStatic")
    .def(pybind11::init<>())
    .def_readwrite("repeat", &sem::Time::Static::repeat)
    .def_readwrite("time", &sem::Time::Static::time)
    ;
  pybind11::class_<sem::Time::Dynamic>(m, "TimeDynamic")
    .def(pybind11::init<>())
    .def_readwrite("expr", &sem::Time::Dynamic::expr)
    ;
  pybind11::enum_<sem::Time::TimeKind>(m, "TimeTimeKind")
    .value("Static", sem::Time::TimeKind::Static)
    .value("Dynamic", sem::Time::TimeKind::Dynamic)
    .export_values()
    ;
  pybind11::class_<sem::SemIdT<sem::TimeRange>, sem::SemId>(m, "SemTimeRange")
    .def(pybind11::init([]() -> sem::SemIdT<sem::TimeRange> { return sem::SemIdT<sem::TimeRange>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::TimeRange> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::TimeRange> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("from_",
                  [](sem::SemIdT<sem::TimeRange> _self) -> sem::SemIdT<sem::Time> { return _self->from; },
                  [](sem::SemIdT<sem::TimeRange> _self, sem::SemIdT<sem::Time> from) { _self->from = from; })
    .def_property("to",
                  [](sem::SemIdT<sem::TimeRange> _self) -> sem::SemIdT<sem::Time> { return _self->to; },
                  [](sem::SemIdT<sem::TimeRange> _self, sem::SemIdT<sem::Time> to) { _self->to = to; })
    ;
  pybind11::class_<sem::SemIdT<sem::Macro>, sem::SemId>(m, "SemMacro")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Macro> { return sem::SemIdT<sem::Macro>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Macro> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Macro> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("name",
                  [](sem::SemIdT<sem::Macro> _self) -> Str { return _self->name; },
                  [](sem::SemIdT<sem::Macro> _self, Str name) { _self->name = name; })
    .def_property("arguments",
                  [](sem::SemIdT<sem::Macro> _self) -> Vec<Str> { return _self->arguments; },
                  [](sem::SemIdT<sem::Macro> _self, Vec<Str> arguments) { _self->arguments = arguments; })
    ;
  pybind11::class_<sem::SemIdT<sem::Symbol>, sem::SemId>(m, "SemSymbol")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Symbol> { return sem::SemIdT<sem::Symbol>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Symbol> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Symbol> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("name",
                  [](sem::SemIdT<sem::Symbol> _self) -> Str { return _self->name; },
                  [](sem::SemIdT<sem::Symbol> _self, Str name) { _self->name = name; })
    .def_property("parameters",
                  [](sem::SemIdT<sem::Symbol> _self) -> Vec<sem::Symbol::Param> { return _self->parameters; },
                  [](sem::SemIdT<sem::Symbol> _self, Vec<sem::Symbol::Param> parameters) { _self->parameters = parameters; })
    .def_property("positional",
                  [](sem::SemIdT<sem::Symbol> _self) -> Vec<sem::SemId> { return _self->positional; },
                  [](sem::SemIdT<sem::Symbol> _self, Vec<sem::SemId> positional) { _self->positional = positional; })
    ;
  pybind11::class_<sem::Symbol::Param>(m, "SymbolParam")
    .def(pybind11::init<>())
    .def_readwrite("key", &sem::Symbol::Param::key, R"RAW(Key -- for non-positional)RAW")
    .def_readwrite("value", &sem::Symbol::Param::value, R"RAW(Uninterpreted value)RAW")
    ;
  pybind11::class_<sem::SemIdT<sem::SubtreeLog>, sem::SemId>(m, "SemSubtreeLog")
    .def(pybind11::init([]() -> sem::SemIdT<sem::SubtreeLog> { return sem::SemIdT<sem::SubtreeLog>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::SubtreeLog> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::SubtreeLog> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("log",
                  [](sem::SemIdT<sem::SubtreeLog> _self) -> sem::SubtreeLog::LogEntry { return _self->log; },
                  [](sem::SemIdT<sem::SubtreeLog> _self, sem::SubtreeLog::LogEntry log) { _self->log = log; })
    .def("setDescription",
         [](sem::SemIdT<sem::SubtreeLog> _self, sem::SemIdT<sem::StmtList> desc) -> void { return _self->setDescription(desc); },
         pybind11::arg("desc"))
    .def("getPriority", [](sem::SemIdT<sem::SubtreeLog> _self) -> sem::SubtreeLog::Priority& { return _self->getPriority(); })
    .def("getNote", [](sem::SemIdT<sem::SubtreeLog> _self) -> sem::SubtreeLog::Note& { return _self->getNote(); })
    .def("getRefile", [](sem::SemIdT<sem::SubtreeLog> _self) -> sem::SubtreeLog::Refile& { return _self->getRefile(); })
    .def("getClock", [](sem::SemIdT<sem::SubtreeLog> _self) -> sem::SubtreeLog::Clock& { return _self->getClock(); })
    .def("getState", [](sem::SemIdT<sem::SubtreeLog> _self) -> sem::SubtreeLog::State& { return _self->getState(); })
    .def("getTag", [](sem::SemIdT<sem::SubtreeLog> _self) -> sem::SubtreeLog::Tag& { return _self->getTag(); })
    .def("getLogKind", [](sem::SemIdT<sem::SubtreeLog> _self) -> sem::SubtreeLog::Kind { return _self->getLogKind(); })
    ;
  pybind11::class_<sem::SubtreeLog::DescribedLog>(m, "SubtreeLogDescribedLog")
    .def(pybind11::init<>())
    .def_readwrite("desc", &sem::SubtreeLog::DescribedLog::desc, R"RAW(Optional description of the log entry)RAW")
    ;
  pybind11::class_<sem::SubtreeLog::Priority>(m, "SubtreeLogPriority")
    .def(pybind11::init<>())
    .def_readwrite("oldPriority", &sem::SubtreeLog::Priority::oldPriority, R"RAW(Previous priority for change and removal)RAW")
    .def_readwrite("newPriority", &sem::SubtreeLog::Priority::newPriority, R"RAW(New priority for change and addition)RAW")
    .def_readwrite("on", &sem::SubtreeLog::Priority::on, R"RAW(When priority was changed)RAW")
    ;
  pybind11::enum_<sem::SubtreeLog::Priority::Action>(m, "SubtreeLogPriorityAction")
    .value("Added", sem::SubtreeLog::Priority::Action::Added)
    .value("Removed", sem::SubtreeLog::Priority::Action::Removed)
    .value("Changed", sem::SubtreeLog::Priority::Action::Changed)
    .export_values()
    ;
  pybind11::class_<sem::SubtreeLog::Note>(m, "SubtreeLogNote")
    .def(pybind11::init<>())
    .def_readwrite("on", &sem::SubtreeLog::Note::on, R"RAW(Where log was taken)RAW")
    ;
  pybind11::class_<sem::SubtreeLog::Refile>(m, "SubtreeLogRefile")
    .def(pybind11::init<>())
    .def_readwrite("on", &sem::SubtreeLog::Refile::on, R"RAW(When the refiling happened)RAW")
    .def_readwrite("from_", &sem::SubtreeLog::Refile::from, R"RAW(Link to the original subtree)RAW")
    ;
  pybind11::class_<sem::SubtreeLog::Clock>(m, "SubtreeLogClock")
    .def(pybind11::init<>())
    ;
  pybind11::class_<sem::SubtreeLog::State>(m, "SubtreeLogState")
    .def(pybind11::init<>())
    .def_readwrite("from_", &sem::SubtreeLog::State::from)
    .def_readwrite("to", &sem::SubtreeLog::State::to)
    .def_readwrite("on", &sem::SubtreeLog::State::on)
    ;
  pybind11::class_<sem::SubtreeLog::Tag>(m, "SubtreeLogTag")
    .def(pybind11::init<>())
    .def_readwrite("on", &sem::SubtreeLog::Tag::on, R"RAW(When the log was assigned)RAW")
    .def_readwrite("tag", &sem::SubtreeLog::Tag::tag, R"RAW(Tag in question)RAW")
    .def_readwrite("added", &sem::SubtreeLog::Tag::added, R"RAW(Added/removed?)RAW")
    ;
  pybind11::enum_<sem::SubtreeLog::Kind>(m, "SubtreeLogKind")
    .value("Priority", sem::SubtreeLog::Kind::Priority)
    .value("Note", sem::SubtreeLog::Kind::Note)
    .value("Refile", sem::SubtreeLog::Kind::Refile)
    .value("Clock", sem::SubtreeLog::Kind::Clock)
    .value("State", sem::SubtreeLog::Kind::State)
    .value("Tag", sem::SubtreeLog::Kind::Tag)
    .export_values()
    ;
  pybind11::class_<sem::SemIdT<sem::Subtree>, sem::SemId>(m, "SemSubtree")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Subtree> { return sem::SemIdT<sem::Subtree>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Subtree> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Subtree> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("level",
                  [](sem::SemIdT<sem::Subtree> _self) -> int { return _self->level; },
                  [](sem::SemIdT<sem::Subtree> _self, int level) { _self->level = level; })
    .def_property("treeId",
                  [](sem::SemIdT<sem::Subtree> _self) -> Opt<Str> { return _self->treeId; },
                  [](sem::SemIdT<sem::Subtree> _self, Opt<Str> treeId) { _self->treeId = treeId; })
    .def_property("todo",
                  [](sem::SemIdT<sem::Subtree> _self) -> Opt<Str> { return _self->todo; },
                  [](sem::SemIdT<sem::Subtree> _self, Opt<Str> todo) { _self->todo = todo; })
    .def_property("completion",
                  [](sem::SemIdT<sem::Subtree> _self) -> Opt<sem::SemIdT<sem::Completion>> { return _self->completion; },
                  [](sem::SemIdT<sem::Subtree> _self, Opt<sem::SemIdT<sem::Completion>> completion) { _self->completion = completion; })
    .def_property("description",
                  [](sem::SemIdT<sem::Subtree> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self->description; },
                  [](sem::SemIdT<sem::Subtree> _self, Opt<sem::SemIdT<sem::Paragraph>> description) { _self->description = description; })
    .def_property("tags",
                  [](sem::SemIdT<sem::Subtree> _self) -> Vec<sem::SemIdT<sem::HashTag>> { return _self->tags; },
                  [](sem::SemIdT<sem::Subtree> _self, Vec<sem::SemIdT<sem::HashTag>> tags) { _self->tags = tags; })
    .def_property("title",
                  [](sem::SemIdT<sem::Subtree> _self) -> sem::SemIdT<sem::Paragraph> { return _self->title; },
                  [](sem::SemIdT<sem::Subtree> _self, sem::SemIdT<sem::Paragraph> title) { _self->title = title; })
    .def_property("logbook",
                  [](sem::SemIdT<sem::Subtree> _self) -> Vec<sem::SemIdT<sem::SubtreeLog>> { return _self->logbook; },
                  [](sem::SemIdT<sem::Subtree> _self, Vec<sem::SemIdT<sem::SubtreeLog>> logbook) { _self->logbook = logbook; })
    .def_property("properties",
                  [](sem::SemIdT<sem::Subtree> _self) -> Vec<sem::Subtree::Property> { return _self->properties; },
                  [](sem::SemIdT<sem::Subtree> _self, Vec<sem::Subtree::Property> properties) { _self->properties = properties; })
    .def_property("closed",
                  [](sem::SemIdT<sem::Subtree> _self) -> Opt<sem::SemIdT<sem::Time>> { return _self->closed; },
                  [](sem::SemIdT<sem::Subtree> _self, Opt<sem::SemIdT<sem::Time>> closed) { _self->closed = closed; })
    .def_property("deadline",
                  [](sem::SemIdT<sem::Subtree> _self) -> Opt<sem::SemIdT<sem::Time>> { return _self->deadline; },
                  [](sem::SemIdT<sem::Subtree> _self, Opt<sem::SemIdT<sem::Time>> deadline) { _self->deadline = deadline; })
    .def_property("scheduled",
                  [](sem::SemIdT<sem::Subtree> _self) -> Opt<sem::SemIdT<sem::Time>> { return _self->scheduled; },
                  [](sem::SemIdT<sem::Subtree> _self, Opt<sem::SemIdT<sem::Time>> scheduled) { _self->scheduled = scheduled; })
    .def("getTimePeriods",
         [](sem::SemIdT<sem::Subtree> _self, IntSet<sem::Subtree::Period::Kind> kinds) -> Vec<sem::Subtree::Period> { return _self->getTimePeriods(kinds); },
         pybind11::arg("kinds"))
    .def("getProperties",
         [](sem::SemIdT<sem::Subtree> _self, sem::Subtree::Property::Kind kind, Str const& subkind) -> Vec<sem::Subtree::Property> { return _self->getProperties(kind, subkind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", ""))
    .def("getProperty",
         [](sem::SemIdT<sem::Subtree> _self, sem::Subtree::Property::Kind kind, Str const& subkind) -> Opt<sem::Subtree::Property> { return _self->getProperty(kind, subkind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", ""))
    .def("getContextualProperties",
         [](sem::SemIdT<sem::Subtree> _self, sem::Subtree::Property::Kind kind, Str const& subkind) -> Vec<sem::Subtree::Property> { return _self->getContextualProperties(kind, subkind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", ""))
    .def("getContextualProperty",
         [](sem::SemIdT<sem::Subtree> _self, sem::Subtree::Property::Kind kind, Str const& subkind) -> Opt<sem::Subtree::Property> { return _self->getContextualProperty(kind, subkind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", ""))
    ;
  pybind11::class_<sem::Subtree::Period>(m, "SubtreePeriod")
    .def(pybind11::init<>())
    .def_readwrite("kind", &sem::Subtree::Period::kind, R"RAW(Time period kind -- not associated with point/range distinction)RAW")
    .def("getTime", static_cast<sem::SemIdT<sem::Time>(sem::Subtree::Period::*)()>(&sem::Subtree::Period::getTime), R"RAW(Get associated time point)RAW")
    .def("getTimeRange", static_cast<sem::SemIdT<sem::Time>(sem::Subtree::Period::*)()>(&sem::Subtree::Period::getTimeRange), R"RAW(Get associated time period)RAW")
    ;
  pybind11::enum_<sem::Subtree::Period::Kind>(m, "SubtreePeriodKind")
    .value("Clocked", sem::Subtree::Period::Kind::Clocked, R"RAW(Time period of the task execution.)RAW")
    .value("Scheduled", sem::Subtree::Period::Kind::Scheduled, R"RAW(Date of task execution start plus it's estimated effort duration. If the latter one is missing then only a single time point is returned)RAW")
    .value("Titled", sem::Subtree::Period::Kind::Titled, R"RAW(Single point or time range used in title. Single point can also be a simple time, such as `12:20`)RAW")
    .value("Deadline", sem::Subtree::Period::Kind::Deadline, R"RAW(Date of task completion. Must be a single time point)RAW")
    .value("Created", sem::Subtree::Period::Kind::Created, R"RAW(When the subtree was created)RAW")
    .value("Repeated", sem::Subtree::Period::Kind::Repeated, R"RAW(Last repeat time of the recurring tasks)RAW")
    .export_values()
    ;
  pybind11::class_<sem::Subtree::Property>(m, "SubtreeProperty")
    .def(pybind11::init<>())
    .def_readwrite("mainSetRule", &sem::Subtree::Property::mainSetRule)
    .def_readwrite("subSetRule", &sem::Subtree::Property::subSetRule)
    .def_readwrite("inheritanceMode", &sem::Subtree::Property::inheritanceMode)
    .def_readwrite("data", &sem::Subtree::Property::data)
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
    .def("getKind", static_cast<sem::Subtree::Property::Kind(sem::Subtree::Property::*)() const>(&sem::Subtree::Property::getKind))
    ;
  pybind11::enum_<sem::Subtree::Property::SetMode>(m, "SubtreePropertySetMode")
    .value("Override", sem::Subtree::Property::SetMode::Override)
    .value("Add", sem::Subtree::Property::SetMode::Add)
    .value("Subtract", sem::Subtree::Property::SetMode::Subtract)
    .export_values()
    ;
  pybind11::enum_<sem::Subtree::Property::InheritanceMode>(m, "SubtreePropertyInheritanceMode")
    .value("ThisAndSub", sem::Subtree::Property::InheritanceMode::ThisAndSub)
    .value("OnlyThis", sem::Subtree::Property::InheritanceMode::OnlyThis)
    .value("OnlySub", sem::Subtree::Property::InheritanceMode::OnlySub)
    .export_values()
    ;
  pybind11::class_<sem::Subtree::Property::Nonblocking>(m, "SubtreePropertyNonblocking")
    .def(pybind11::init<>())
    .def_readwrite("isBlocking", &sem::Subtree::Property::Nonblocking::isBlocking)
    ;
  pybind11::class_<sem::Subtree::Property::Trigger>(m, "SubtreePropertyTrigger")
    .def(pybind11::init<>())
    ;
  pybind11::class_<sem::Subtree::Property::Origin>(m, "SubtreePropertyOrigin")
    .def(pybind11::init<>())
    .def_readwrite("text", &sem::Subtree::Property::Origin::text)
    ;
  pybind11::class_<sem::Subtree::Property::ExportLatexClass>(m, "SubtreePropertyExportLatexClass")
    .def(pybind11::init<>())
    .def_readwrite("latexClass", &sem::Subtree::Property::ExportLatexClass::latexClass)
    ;
  pybind11::class_<sem::Subtree::Property::ExportLatexClassOptions>(m, "SubtreePropertyExportLatexClassOptions")
    .def(pybind11::init<>())
    .def_readwrite("options", &sem::Subtree::Property::ExportLatexClassOptions::options)
    ;
  pybind11::class_<sem::Subtree::Property::ExportLatexHeader>(m, "SubtreePropertyExportLatexHeader")
    .def(pybind11::init<>())
    .def_readwrite("header", &sem::Subtree::Property::ExportLatexHeader::header)
    ;
  pybind11::class_<sem::Subtree::Property::ExportLatexCompiler>(m, "SubtreePropertyExportLatexCompiler")
    .def(pybind11::init<>())
    .def_readwrite("compiler", &sem::Subtree::Property::ExportLatexCompiler::compiler)
    ;
  pybind11::class_<sem::Subtree::Property::Ordered>(m, "SubtreePropertyOrdered")
    .def(pybind11::init<>())
    .def_readwrite("isOrdered", &sem::Subtree::Property::Ordered::isOrdered)
    ;
  pybind11::class_<sem::Subtree::Property::Effort>(m, "SubtreePropertyEffort")
    .def(pybind11::init<>())
    .def_readwrite("hours", &sem::Subtree::Property::Effort::hours)
    .def_readwrite("minutes", &sem::Subtree::Property::Effort::minutes)
    ;
  pybind11::class_<sem::Subtree::Property::Visibility>(m, "SubtreePropertyVisibility")
    .def(pybind11::init<>())
    .def_readwrite("level", &sem::Subtree::Property::Visibility::level)
    ;
  pybind11::enum_<sem::Subtree::Property::Visibility::Level>(m, "SubtreePropertyVisibilityLevel")
    .value("Folded", sem::Subtree::Property::Visibility::Level::Folded)
    .value("Children", sem::Subtree::Property::Visibility::Level::Children)
    .value("Content", sem::Subtree::Property::Visibility::Level::Content)
    .value("All", sem::Subtree::Property::Visibility::Level::All)
    .export_values()
    ;
  pybind11::class_<sem::Subtree::Property::ExportOptions>(m, "SubtreePropertyExportOptions")
    .def(pybind11::init<>())
    .def_readwrite("backend", &sem::Subtree::Property::ExportOptions::backend)
    .def_readwrite("values", &sem::Subtree::Property::ExportOptions::values)
    ;
  pybind11::class_<sem::Subtree::Property::Blocker>(m, "SubtreePropertyBlocker")
    .def(pybind11::init<>())
    .def_readwrite("blockers", &sem::Subtree::Property::Blocker::blockers)
    ;
  pybind11::class_<sem::Subtree::Property::Unnumbered>(m, "SubtreePropertyUnnumbered")
    .def(pybind11::init<>())
    ;
  pybind11::class_<sem::Subtree::Property::Created>(m, "SubtreePropertyCreated")
    .def(pybind11::init<>())
    .def_readwrite("time", &sem::Subtree::Property::Created::time)
    ;
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
    .export_values()
    ;
  pybind11::class_<sem::SemIdT<sem::LatexBody>, sem::SemId>(m, "SemLatexBody")
    .def(pybind11::init([]() -> sem::SemIdT<sem::LatexBody> { return sem::SemIdT<sem::LatexBody>::Nil(); }))
    ;
  pybind11::class_<sem::SemIdT<sem::InlineMath>, sem::SemId>(m, "SemInlineMath")
    .def(pybind11::init([]() -> sem::SemIdT<sem::InlineMath> { return sem::SemIdT<sem::InlineMath>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::InlineMath> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::InlineMath> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::Leaf>, sem::SemId>(m, "SemLeaf")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Leaf> { return sem::SemIdT<sem::Leaf>::Nil(); }))
    .def_property("text",
                  [](sem::SemIdT<sem::Leaf> _self) -> Str { return _self->text; },
                  [](sem::SemIdT<sem::Leaf> _self, Str text) { _self->text = text; })
    ;
  pybind11::class_<sem::SemIdT<sem::Escaped>, sem::SemId>(m, "SemEscaped")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Escaped> { return sem::SemIdT<sem::Escaped>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Escaped> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Escaped> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("text",
                  [](sem::SemIdT<sem::Escaped> _self) -> Str { return _self->text; },
                  [](sem::SemIdT<sem::Escaped> _self, Str text) { _self->text = text; })
    ;
  pybind11::class_<sem::SemIdT<sem::Newline>, sem::SemId>(m, "SemNewline")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Newline> { return sem::SemIdT<sem::Newline>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Newline> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Newline> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("text",
                  [](sem::SemIdT<sem::Newline> _self) -> Str { return _self->text; },
                  [](sem::SemIdT<sem::Newline> _self, Str text) { _self->text = text; })
    ;
  pybind11::class_<sem::SemIdT<sem::Space>, sem::SemId>(m, "SemSpace")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Space> { return sem::SemIdT<sem::Space>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Space> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Space> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("text",
                  [](sem::SemIdT<sem::Space> _self) -> Str { return _self->text; },
                  [](sem::SemIdT<sem::Space> _self, Str text) { _self->text = text; })
    ;
  pybind11::class_<sem::SemIdT<sem::Word>, sem::SemId>(m, "SemWord")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Word> { return sem::SemIdT<sem::Word>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Word> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Word> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("text",
                  [](sem::SemIdT<sem::Word> _self) -> Str { return _self->text; },
                  [](sem::SemIdT<sem::Word> _self, Str text) { _self->text = text; })
    ;
  pybind11::class_<sem::SemIdT<sem::AtMention>, sem::SemId>(m, "SemAtMention")
    .def(pybind11::init([]() -> sem::SemIdT<sem::AtMention> { return sem::SemIdT<sem::AtMention>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::AtMention> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::AtMention> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("text",
                  [](sem::SemIdT<sem::AtMention> _self) -> Str { return _self->text; },
                  [](sem::SemIdT<sem::AtMention> _self, Str text) { _self->text = text; })
    ;
  pybind11::class_<sem::SemIdT<sem::RawText>, sem::SemId>(m, "SemRawText")
    .def(pybind11::init([]() -> sem::SemIdT<sem::RawText> { return sem::SemIdT<sem::RawText>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::RawText> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::RawText> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("text",
                  [](sem::SemIdT<sem::RawText> _self) -> Str { return _self->text; },
                  [](sem::SemIdT<sem::RawText> _self, Str text) { _self->text = text; })
    ;
  pybind11::class_<sem::SemIdT<sem::Punctuation>, sem::SemId>(m, "SemPunctuation")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Punctuation> { return sem::SemIdT<sem::Punctuation>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Punctuation> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Punctuation> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("text",
                  [](sem::SemIdT<sem::Punctuation> _self) -> Str { return _self->text; },
                  [](sem::SemIdT<sem::Punctuation> _self, Str text) { _self->text = text; })
    ;
  pybind11::class_<sem::SemIdT<sem::Placeholder>, sem::SemId>(m, "SemPlaceholder")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Placeholder> { return sem::SemIdT<sem::Placeholder>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Placeholder> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Placeholder> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("text",
                  [](sem::SemIdT<sem::Placeholder> _self) -> Str { return _self->text; },
                  [](sem::SemIdT<sem::Placeholder> _self, Str text) { _self->text = text; })
    ;
  pybind11::class_<sem::SemIdT<sem::BigIdent>, sem::SemId>(m, "SemBigIdent")
    .def(pybind11::init([]() -> sem::SemIdT<sem::BigIdent> { return sem::SemIdT<sem::BigIdent>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::BigIdent> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::BigIdent> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("text",
                  [](sem::SemIdT<sem::BigIdent> _self) -> Str { return _self->text; },
                  [](sem::SemIdT<sem::BigIdent> _self, Str text) { _self->text = text; })
    ;
  pybind11::class_<sem::SemIdT<sem::Markup>, sem::SemId>(m, "SemMarkup")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Markup> { return sem::SemIdT<sem::Markup>::Nil(); }))
    ;
  pybind11::class_<sem::SemIdT<sem::Bold>, sem::SemId>(m, "SemBold")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Bold> { return sem::SemIdT<sem::Bold>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Bold> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Bold> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::Underline>, sem::SemId>(m, "SemUnderline")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Underline> { return sem::SemIdT<sem::Underline>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Underline> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Underline> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::Monospace>, sem::SemId>(m, "SemMonospace")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Monospace> { return sem::SemIdT<sem::Monospace>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Monospace> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Monospace> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::MarkQuote>, sem::SemId>(m, "SemMarkQuote")
    .def(pybind11::init([]() -> sem::SemIdT<sem::MarkQuote> { return sem::SemIdT<sem::MarkQuote>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::MarkQuote> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::MarkQuote> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::Verbatim>, sem::SemId>(m, "SemVerbatim")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Verbatim> { return sem::SemIdT<sem::Verbatim>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Verbatim> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Verbatim> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::Italic>, sem::SemId>(m, "SemItalic")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Italic> { return sem::SemIdT<sem::Italic>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Italic> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Italic> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::Strike>, sem::SemId>(m, "SemStrike")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Strike> { return sem::SemIdT<sem::Strike>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Strike> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Strike> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::Par>, sem::SemId>(m, "SemPar")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Par> { return sem::SemIdT<sem::Par>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Par> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Par> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::List>, sem::SemId>(m, "SemList")
    .def(pybind11::init([]() -> sem::SemIdT<sem::List> { return sem::SemIdT<sem::List>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::List> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::List> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def("isDescriptionList", [](sem::SemIdT<sem::List> _self) -> bool { return _self->isDescriptionList(); })
    ;
  pybind11::class_<sem::SemIdT<sem::ListItem>, sem::SemId>(m, "SemListItem")
    .def(pybind11::init([]() -> sem::SemIdT<sem::ListItem> { return sem::SemIdT<sem::ListItem>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::ListItem> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::ListItem> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("checkbox",
                  [](sem::SemIdT<sem::ListItem> _self) -> sem::ListItem::Checkbox { return _self->checkbox; },
                  [](sem::SemIdT<sem::ListItem> _self, sem::ListItem::Checkbox checkbox) { _self->checkbox = checkbox; })
    .def_property("header",
                  [](sem::SemIdT<sem::ListItem> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self->header; },
                  [](sem::SemIdT<sem::ListItem> _self, Opt<sem::SemIdT<sem::Paragraph>> header) { _self->header = header; })
    .def("isDescriptionItem", [](sem::SemIdT<sem::ListItem> _self) -> bool { return _self->isDescriptionItem(); })
    ;
  pybind11::enum_<sem::ListItem::Checkbox>(m, "ListItemCheckbox")
    .value("None", sem::ListItem::Checkbox::None)
    .value("Done", sem::ListItem::Checkbox::Done)
    .value("Empty", sem::ListItem::Checkbox::Empty)
    .export_values()
    ;
  pybind11::class_<sem::SemIdT<sem::Link>, sem::SemId>(m, "SemLink")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Link> { return sem::SemIdT<sem::Link>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Link> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Link> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("description",
                  [](sem::SemIdT<sem::Link> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self->description; },
                  [](sem::SemIdT<sem::Link> _self, Opt<sem::SemIdT<sem::Paragraph>> description) { _self->description = description; })
    .def_property("data",
                  [](sem::SemIdT<sem::Link> _self) -> sem::Link::Data { return _self->data; },
                  [](sem::SemIdT<sem::Link> _self, sem::Link::Data data) { _self->data = data; })
    .def("resolve",
         [](sem::SemIdT<sem::Link> _self, sem::Document const& doc) -> Opt<sem::SemId> { return _self->resolve(doc); },
         pybind11::arg("doc"))
    .def("resolve", [](sem::SemIdT<sem::Link> _self) -> Opt<sem::SemId> { return _self->resolve(); })
    .def("getRaw", [](sem::SemIdT<sem::Link> _self) -> sem::Link::Raw& { return _self->getRaw(); })
    .def("getId", [](sem::SemIdT<sem::Link> _self) -> sem::Link::Id& { return _self->getId(); })
    .def("getPerson", [](sem::SemIdT<sem::Link> _self) -> sem::Link::Person& { return _self->getPerson(); })
    .def("getFootnote", [](sem::SemIdT<sem::Link> _self) -> sem::Link::Footnote& { return _self->getFootnote(); })
    .def("getFile", [](sem::SemIdT<sem::Link> _self) -> sem::Link::File& { return _self->getFile(); })
    .def("getLinkKind", [](sem::SemIdT<sem::Link> _self) -> sem::Link::Kind { return _self->getLinkKind(); })
    ;
  pybind11::class_<sem::Link::Raw>(m, "LinkRaw")
    .def(pybind11::init<>())
    .def_readwrite("text", &sem::Link::Raw::text)
    ;
  pybind11::class_<sem::Link::Id>(m, "LinkId")
    .def(pybind11::init<>())
    .def_readwrite("text", &sem::Link::Id::text)
    ;
  pybind11::class_<sem::Link::Person>(m, "LinkPerson")
    .def(pybind11::init<>())
    .def_readwrite("name", &sem::Link::Person::name)
    ;
  pybind11::class_<sem::Link::Footnote>(m, "LinkFootnote")
    .def(pybind11::init<>())
    .def_readwrite("target", &sem::Link::Footnote::target)
    ;
  pybind11::class_<sem::Link::File>(m, "LinkFile")
    .def(pybind11::init<>())
    .def_readwrite("file", &sem::Link::File::file)
    ;
  pybind11::enum_<sem::Link::Kind>(m, "LinkKind")
    .value("Raw", sem::Link::Kind::Raw)
    .value("Id", sem::Link::Kind::Id)
    .value("Person", sem::Link::Kind::Person)
    .value("Footnote", sem::Link::Kind::Footnote)
    .value("File", sem::Link::Kind::File)
    .export_values()
    ;
  pybind11::class_<sem::SemIdT<sem::Document>, sem::SemId>(m, "SemDocument")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Document> { return sem::SemIdT<sem::Document>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Document> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Document> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("idTable",
                  [](sem::SemIdT<sem::Document> _self) -> UnorderedMap<Str, sem::SemId> { return _self->idTable; },
                  [](sem::SemIdT<sem::Document> _self, UnorderedMap<Str, sem::SemId> idTable) { _self->idTable = idTable; })
    .def_property("nameTable",
                  [](sem::SemIdT<sem::Document> _self) -> UnorderedMap<Str, sem::SemId> { return _self->nameTable; },
                  [](sem::SemIdT<sem::Document> _self, UnorderedMap<Str, sem::SemId> nameTable) { _self->nameTable = nameTable; })
    .def_property("footnoteTable",
                  [](sem::SemIdT<sem::Document> _self) -> UnorderedMap<Str, sem::SemId> { return _self->footnoteTable; },
                  [](sem::SemIdT<sem::Document> _self, UnorderedMap<Str, sem::SemId> footnoteTable) { _self->footnoteTable = footnoteTable; })
    .def_property("anchorTable",
                  [](sem::SemIdT<sem::Document> _self) -> UnorderedMap<Str, sem::SemId> { return _self->anchorTable; },
                  [](sem::SemIdT<sem::Document> _self, UnorderedMap<Str, sem::SemId> anchorTable) { _self->anchorTable = anchorTable; })
    .def_property("title",
                  [](sem::SemIdT<sem::Document> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self->title; },
                  [](sem::SemIdT<sem::Document> _self, Opt<sem::SemIdT<sem::Paragraph>> title) { _self->title = title; })
    .def_property("author",
                  [](sem::SemIdT<sem::Document> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self->author; },
                  [](sem::SemIdT<sem::Document> _self, Opt<sem::SemIdT<sem::Paragraph>> author) { _self->author = author; })
    .def_property("creator",
                  [](sem::SemIdT<sem::Document> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self->creator; },
                  [](sem::SemIdT<sem::Document> _self, Opt<sem::SemIdT<sem::Paragraph>> creator) { _self->creator = creator; })
    .def_property("email",
                  [](sem::SemIdT<sem::Document> _self) -> Opt<sem::SemIdT<sem::RawText>> { return _self->email; },
                  [](sem::SemIdT<sem::Document> _self, Opt<sem::SemIdT<sem::RawText>> email) { _self->email = email; })
    .def_property("language",
                  [](sem::SemIdT<sem::Document> _self) -> Vec<Str> { return _self->language; },
                  [](sem::SemIdT<sem::Document> _self, Vec<Str> language) { _self->language = language; })
    .def_property("options",
                  [](sem::SemIdT<sem::Document> _self) -> sem::SemIdT<sem::DocumentOptions> { return _self->options; },
                  [](sem::SemIdT<sem::Document> _self, sem::SemIdT<sem::DocumentOptions> options) { _self->options = options; })
    .def_property("exportFileName",
                  [](sem::SemIdT<sem::Document> _self) -> Opt<Str> { return _self->exportFileName; },
                  [](sem::SemIdT<sem::Document> _self, Opt<Str> exportFileName) { _self->exportFileName = exportFileName; })
    .def("resolve",
         [](sem::SemIdT<sem::Document> _self, sem::SemId const& node) -> Opt<sem::SemId> { return _self->resolve(node); },
         pybind11::arg("node"))
    .def("getSubtree",
         [](sem::SemIdT<sem::Document> _self, Str const& id) -> Opt<sem::SemIdT<sem::Subtree>> { return _self->getSubtree(id); },
         pybind11::arg("id"))
    .def("getProperties",
         [](sem::SemIdT<sem::Document> _self, sem::Subtree::Property::Kind kind, Str const& subKind) -> Vec<sem::Subtree::Property> { return _self->getProperties(kind, subKind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", ""))
    .def("getProperty",
         [](sem::SemIdT<sem::Document> _self, sem::Subtree::Property::Kind kind, Str const& subKind) -> Opt<sem::Subtree::Property> { return _self->getProperty(kind, subKind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", ""))
    ;
  pybind11::class_<sem::SemIdT<sem::ParseError>, sem::SemId>(m, "SemParseError")
    .def(pybind11::init([]() -> sem::SemIdT<sem::ParseError> { return sem::SemIdT<sem::ParseError>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::ParseError> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::ParseError> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::FileTarget>, sem::SemId>(m, "SemFileTarget")
    .def(pybind11::init([]() -> sem::SemIdT<sem::FileTarget> { return sem::SemIdT<sem::FileTarget>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::FileTarget> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::FileTarget> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("path",
                  [](sem::SemIdT<sem::FileTarget> _self) -> Str { return _self->path; },
                  [](sem::SemIdT<sem::FileTarget> _self, Str path) { _self->path = path; })
    .def_property("line",
                  [](sem::SemIdT<sem::FileTarget> _self) -> Opt<int> { return _self->line; },
                  [](sem::SemIdT<sem::FileTarget> _self, Opt<int> line) { _self->line = line; })
    .def_property("searchTarget",
                  [](sem::SemIdT<sem::FileTarget> _self) -> Opt<Str> { return _self->searchTarget; },
                  [](sem::SemIdT<sem::FileTarget> _self, Opt<Str> searchTarget) { _self->searchTarget = searchTarget; })
    .def_property("restrictToHeadlines",
                  [](sem::SemIdT<sem::FileTarget> _self) -> bool { return _self->restrictToHeadlines; },
                  [](sem::SemIdT<sem::FileTarget> _self, bool restrictToHeadlines) { _self->restrictToHeadlines = restrictToHeadlines; })
    .def_property("targetId",
                  [](sem::SemIdT<sem::FileTarget> _self) -> Opt<Str> { return _self->targetId; },
                  [](sem::SemIdT<sem::FileTarget> _self, Opt<Str> targetId) { _self->targetId = targetId; })
    .def_property("regexp",
                  [](sem::SemIdT<sem::FileTarget> _self) -> Opt<Str> { return _self->regexp; },
                  [](sem::SemIdT<sem::FileTarget> _self, Opt<Str> regexp) { _self->regexp = regexp; })
    ;
  pybind11::class_<sem::SemIdT<sem::TextSeparator>, sem::SemId>(m, "SemTextSeparator")
    .def(pybind11::init([]() -> sem::SemIdT<sem::TextSeparator> { return sem::SemIdT<sem::TextSeparator>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::TextSeparator> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::TextSeparator> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
  pybind11::class_<sem::SemIdT<sem::Include>, sem::SemId>(m, "SemInclude")
    .def(pybind11::init([]() -> sem::SemIdT<sem::Include> { return sem::SemIdT<sem::Include>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::Include> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::Include> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("data",
                  [](sem::SemIdT<sem::Include> _self) -> sem::Include::Data { return _self->data; },
                  [](sem::SemIdT<sem::Include> _self, sem::Include::Data data) { _self->data = data; })
    .def("getExample", [](sem::SemIdT<sem::Include> _self) -> sem::Include::Example& { return _self->getExample(); })
    .def("getExport", [](sem::SemIdT<sem::Include> _self) -> sem::Include::Export& { return _self->getExport(); })
    .def("getSrc", [](sem::SemIdT<sem::Include> _self) -> sem::Include::Src& { return _self->getSrc(); })
    .def("getOrgDocument", [](sem::SemIdT<sem::Include> _self) -> sem::Include::OrgDocument& { return _self->getOrgDocument(); })
    .def("getIncludeKind", [](sem::SemIdT<sem::Include> _self) -> sem::Include::Kind { return _self->getIncludeKind(); })
    ;
  pybind11::class_<sem::Include::Example>(m, "IncludeExample")
    .def(pybind11::init<>())
    ;
  pybind11::class_<sem::Include::Export>(m, "IncludeExport")
    .def(pybind11::init<>())
    ;
  pybind11::class_<sem::Include::Src>(m, "IncludeSrc")
    .def(pybind11::init<>())
    ;
  pybind11::class_<sem::Include::OrgDocument>(m, "IncludeOrgDocument")
    .def(pybind11::init<>())
    ;
  pybind11::enum_<sem::Include::Kind>(m, "IncludeKind")
    .value("Example", sem::Include::Kind::Example)
    .value("Export", sem::Include::Kind::Export)
    .value("Src", sem::Include::Kind::Src)
    .value("OrgDocument", sem::Include::Kind::OrgDocument)
    .export_values()
    ;
  pybind11::class_<sem::SemIdT<sem::DocumentOptions>, sem::SemId>(m, "SemDocumentOptions")
    .def(pybind11::init([]() -> sem::SemIdT<sem::DocumentOptions> { return sem::SemIdT<sem::DocumentOptions>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, Opt<LineCol> loc) { _self->loc = loc; })
    .def_property("brokenLinks",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> sem::DocumentOptions::BrokenLinks { return _self->brokenLinks; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, sem::DocumentOptions::BrokenLinks brokenLinks) { _self->brokenLinks = brokenLinks; })
    .def_property("initialVisibility",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> sem::DocumentOptions::Visibility { return _self->initialVisibility; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, sem::DocumentOptions::Visibility initialVisibility) { _self->initialVisibility = initialVisibility; })
    .def_property("tocExport",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> sem::DocumentOptions::TocExport { return _self->tocExport; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, sem::DocumentOptions::TocExport tocExport) { _self->tocExport = tocExport; })
    .def_property("properties",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> Vec<sem::Subtree::Property> { return _self->properties; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, Vec<sem::Subtree::Property> properties) { _self->properties = properties; })
    .def_property("smartQuotes",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> bool { return _self->smartQuotes; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, bool smartQuotes) { _self->smartQuotes = smartQuotes; })
    .def_property("emphasizedText",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> bool { return _self->emphasizedText; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, bool emphasizedText) { _self->emphasizedText = emphasizedText; })
    .def_property("specialStrings",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> bool { return _self->specialStrings; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, bool specialStrings) { _self->specialStrings = specialStrings; })
    .def_property("fixedWidthSections",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> bool { return _self->fixedWidthSections; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, bool fixedWidthSections) { _self->fixedWidthSections = fixedWidthSections; })
    .def_property("includeTimestamps",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> bool { return _self->includeTimestamps; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, bool includeTimestamps) { _self->includeTimestamps = includeTimestamps; })
    .def_property("preserveLineBreaks",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> bool { return _self->preserveLineBreaks; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, bool preserveLineBreaks) { _self->preserveLineBreaks = preserveLineBreaks; })
    .def_property("plaintextSubscripts",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> bool { return _self->plaintextSubscripts; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, bool plaintextSubscripts) { _self->plaintextSubscripts = plaintextSubscripts; })
    .def_property("exportArchived",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> bool { return _self->exportArchived; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, bool exportArchived) { _self->exportArchived = exportArchived; })
    .def_property("exportWithAuthor",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> bool { return _self->exportWithAuthor; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, bool exportWithAuthor) { _self->exportWithAuthor = exportWithAuthor; })
    .def_property("exportBrokenLinks",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> bool { return _self->exportBrokenLinks; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, bool exportBrokenLinks) { _self->exportBrokenLinks = exportBrokenLinks; })
    .def_property("exportWithClock",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> bool { return _self->exportWithClock; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, bool exportWithClock) { _self->exportWithClock = exportWithClock; })
    .def_property("exportWithCreator",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> bool { return _self->exportWithCreator; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, bool exportWithCreator) { _self->exportWithCreator = exportWithCreator; })
    .def_property("data",
                  [](sem::SemIdT<sem::DocumentOptions> _self) -> sem::DocumentOptions::TocExport { return _self->data; },
                  [](sem::SemIdT<sem::DocumentOptions> _self, sem::DocumentOptions::TocExport data) { _self->data = data; })
    .def("getProperties",
         [](sem::SemIdT<sem::DocumentOptions> _self, sem::Subtree::Property::Kind kind, Str const& subKind) -> Vec<sem::Subtree::Property> { return _self->getProperties(kind, subKind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", ""))
    .def("getProperty",
         [](sem::SemIdT<sem::DocumentOptions> _self, sem::Subtree::Property::Kind kind, Str const& subKind) -> Opt<sem::Subtree::Property> { return _self->getProperty(kind, subKind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", ""))
    .def("getDoExport", [](sem::SemIdT<sem::DocumentOptions> _self) -> sem::DocumentOptions::DoExport& { return _self->getDoExport(); })
    .def("getExportFixed", [](sem::SemIdT<sem::DocumentOptions> _self) -> sem::DocumentOptions::ExportFixed& { return _self->getExportFixed(); })
    .def("getTocExportKind", [](sem::SemIdT<sem::DocumentOptions> _self) -> sem::DocumentOptions::TocExportKind { return _self->getTocExportKind(); })
    ;
  pybind11::class_<sem::DocumentOptions::DoExport>(m, "DocumentOptionsDoExport")
    .def(pybind11::init<>())
    .def_readwrite("exportToc", &sem::DocumentOptions::DoExport::exportToc)
    ;
  pybind11::class_<sem::DocumentOptions::ExportFixed>(m, "DocumentOptionsExportFixed")
    .def(pybind11::init<>())
    .def_readwrite("exportLevels", &sem::DocumentOptions::ExportFixed::exportLevels)
    ;
  pybind11::enum_<sem::DocumentOptions::TocExportKind>(m, "DocumentOptionsTocExportKind")
    .value("DoExport", sem::DocumentOptions::TocExportKind::DoExport)
    .value("ExportFixed", sem::DocumentOptions::TocExportKind::ExportFixed)
    .export_values()
    ;
  pybind11::enum_<sem::DocumentOptions::BrokenLinks>(m, "DocumentOptionsBrokenLinks")
    .value("Raise", sem::DocumentOptions::BrokenLinks::Raise)
    .value("Ignore", sem::DocumentOptions::BrokenLinks::Ignore)
    .value("Mark", sem::DocumentOptions::BrokenLinks::Mark)
    .export_values()
    ;
  pybind11::enum_<sem::DocumentOptions::Visibility>(m, "DocumentOptionsVisibility")
    .value("Overview", sem::DocumentOptions::Visibility::Overview)
    .value("Content", sem::DocumentOptions::Visibility::Content)
    .value("ShowAll", sem::DocumentOptions::Visibility::ShowAll)
    .value("Show2Levels", sem::DocumentOptions::Visibility::Show2Levels)
    .value("Show3Levels", sem::DocumentOptions::Visibility::Show3Levels)
    .value("Show4Levels", sem::DocumentOptions::Visibility::Show4Levels)
    .value("Show5Levels", sem::DocumentOptions::Visibility::Show5Levels)
    .value("ShowEverything", sem::DocumentOptions::Visibility::ShowEverything)
    .export_values()
    ;
  pybind11::class_<sem::SemIdT<sem::DocumentGroup>, sem::SemId>(m, "SemDocumentGroup")
    .def(pybind11::init([]() -> sem::SemIdT<sem::DocumentGroup> { return sem::SemIdT<sem::DocumentGroup>::Nil(); }))
    .def_property("loc",
                  [](sem::SemIdT<sem::DocumentGroup> _self) -> Opt<LineCol> { return _self->loc; },
                  [](sem::SemIdT<sem::DocumentGroup> _self, Opt<LineCol> loc) { _self->loc = loc; })
    ;
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
    .export_values()
    ;
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
    .value("CommandAttrHtml", OrgNodeKind::CommandAttrHtml, R"RAW(`#+attr_html:`)RAW")
    .value("CommandName", OrgNodeKind::CommandName, R"RAW(`#+name:` - name of the associated entry)RAW")
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
    .value("QuoteBlock", OrgNodeKind::QuoteBlock, R"RAW(`#+quote:` block in code)RAW")
    .value("AdmonitionBlock", OrgNodeKind::AdmonitionBlock)
    .value("CenterBlock", OrgNodeKind::CenterBlock, R"RAW(')RAW")
    .value("Example", OrgNodeKind::Example, R"RAW(Verbatim example text block)RAW")
    .value("SrcCode", OrgNodeKind::SrcCode, R"RAW(Block of source code - can be multiline, single-line and)RAW")
    .value("SrcInlineCode", OrgNodeKind::SrcInlineCode, R"RAW(inline piece of code (such as `src_nim`),. Latter is different from regular monospaced text inside of `~~` pair as it contains additional internal structure, optional parameter for code evaluation etc.)RAW")
    .value("CallCode", OrgNodeKind::CallCode, R"RAW(Call to named source code block. Inline, multiline, or single-line.)RAW")
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
    .export_values()
    ;
  pybind11::enum_<OrgBigIdentKind>(m, "OrgBigIdentKind")
    .value("None", OrgBigIdentKind::None)
    .value("Must", OrgBigIdentKind::Must, R"RAW(MUST This word, or the terms "REQUIRED" or "SHALL", mean that the definition is an absolute requirement of the specification.)RAW")
    .value("MustNot", OrgBigIdentKind::MustNot, R"RAW(MUST NOT This phrase, or the phrase "SHALL NOT", mean that the definition is an absolute prohibition of the specification.)RAW")
    .value("Should", OrgBigIdentKind::Should, R"RAW(SHOULD This word, or the adjective "RECOMMENDED", mean that there
   may exist valid reasons in particular circumstances to ignore a
   particular item, but the full implications must be understood and
   carefully weighed before choosing a different course.)RAW")
    .value("ShouldNot", OrgBigIdentKind::ShouldNot, R"RAW(SHOULD NOT This phrase, or the phrase "NOT RECOMMENDED" mean that
   there may exist valid reasons in particular circumstances when the
   particular behavior is acceptable or even useful, but the full
   implications should be understood and the case carefully weighed
   before implementing any behavior described with this label.)RAW")
    .value("Required", OrgBigIdentKind::Required)
    .value("Optional", OrgBigIdentKind::Optional, R"RAW(MAY This word, or the adjective "OPTIONAL", mean that an item is
   truly optional. One vendor may choose to include the item because a
   particular marketplace requires it or because the vendor feels that
   it enhances the product while another vendor may omit the same
   item. An implementation which does not include a particular option
   MUST be prepared to interoperate with another implementation which
   does include the option, though perhaps with reduced functionality.
   In the same vein an implementation which does include a particular
   option MUST be prepared to interoperate with another implementation
   which does not include the option (except, of course, for the
   feature the option provides.))RAW")
    .value("ReallyShouldNot", OrgBigIdentKind::ReallyShouldNot)
    .value("OughtTo", OrgBigIdentKind::OughtTo)
    .value("WouldProbably", OrgBigIdentKind::WouldProbably)
    .value("MayWishTo", OrgBigIdentKind::MayWishTo)
    .value("Could", OrgBigIdentKind::Could)
    .value("Might", OrgBigIdentKind::Might)
    .value("Possible", OrgBigIdentKind::Possible)
    .value("Todo", OrgBigIdentKind::Todo)
    .value("Idea", OrgBigIdentKind::Idea)
    .value("Error", OrgBigIdentKind::Error)
    .value("Fixme", OrgBigIdentKind::Fixme)
    .value("Doc", OrgBigIdentKind::Doc)
    .value("Refactor", OrgBigIdentKind::Refactor)
    .value("Review", OrgBigIdentKind::Review)
    .value("Hack", OrgBigIdentKind::Hack)
    .value("Implement", OrgBigIdentKind::Implement)
    .value("Example", OrgBigIdentKind::Example)
    .value("Question", OrgBigIdentKind::Question)
    .value("Assume", OrgBigIdentKind::Assume)
    .value("Internal", OrgBigIdentKind::Internal)
    .value("Design", OrgBigIdentKind::Design)
    .value("Why", OrgBigIdentKind::Why)
    .value("Wip", OrgBigIdentKind::Wip)
    .value("Fix", OrgBigIdentKind::Fix)
    .value("Clean", OrgBigIdentKind::Clean)
    .value("Feature", OrgBigIdentKind::Feature)
    .value("Style", OrgBigIdentKind::Style)
    .value("Repo", OrgBigIdentKind::Repo)
    .value("Skip", OrgBigIdentKind::Skip)
    .value("Break", OrgBigIdentKind::Break)
    .value("Poc", OrgBigIdentKind::Poc)
    .value("Next", OrgBigIdentKind::Next)
    .value("Later", OrgBigIdentKind::Later)
    .value("Postponed", OrgBigIdentKind::Postponed)
    .value("Stalled", OrgBigIdentKind::Stalled)
    .value("Done", OrgBigIdentKind::Done)
    .value("Partially", OrgBigIdentKind::Partially)
    .value("Cancelled", OrgBigIdentKind::Cancelled)
    .value("Failed", OrgBigIdentKind::Failed)
    .value("Note", OrgBigIdentKind::Note)
    .value("Tip", OrgBigIdentKind::Tip)
    .value("Important", OrgBigIdentKind::Important)
    .value("Caution", OrgBigIdentKind::Caution)
    .value("Warning", OrgBigIdentKind::Warning)
    .value("UserCodeComment", OrgBigIdentKind::UserCodeComment, R"RAW(User-defined comment message)RAW")
    .value("UserCommitMsg", OrgBigIdentKind::UserCommitMsg, R"RAW(User-defined commit message ident)RAW")
    .value("UserTaskState", OrgBigIdentKind::UserTaskState, R"RAW(User-defined task state)RAW")
    .value("UserAdmonition", OrgBigIdentKind::UserAdmonition, R"RAW(User-defined admonition label)RAW")
    .value("Other", OrgBigIdentKind::Other, R"RAW(User-defined big-idents, not included in default set.)RAW")
    .value("StructIf", OrgBigIdentKind::StructIf)
    .value("StructAnd", OrgBigIdentKind::StructAnd)
    .value("StructOr", OrgBigIdentKind::StructOr)
    .value("StructNot", OrgBigIdentKind::StructNot)
    .value("StructGet", OrgBigIdentKind::StructGet)
    .value("StructSet", OrgBigIdentKind::StructSet)
    .value("StructThen", OrgBigIdentKind::StructThen)
    .value("StructElse", OrgBigIdentKind::StructElse)
    .value("StructWhile", OrgBigIdentKind::StructWhile)
    .export_values()
    ;
  pybind11::enum_<OrgSemKind>(m, "OrgSemKind")
    .value("StmtList", OrgSemKind::StmtList)
    .value("Empty", OrgSemKind::Empty)
    .value("Row", OrgSemKind::Row)
    .value("Table", OrgSemKind::Table)
    .value("HashTag", OrgSemKind::HashTag)
    .value("Footnote", OrgSemKind::Footnote)
    .value("Completion", OrgSemKind::Completion)
    .value("Paragraph", OrgSemKind::Paragraph)
    .value("Center", OrgSemKind::Center)
    .value("Caption", OrgSemKind::Caption)
    .value("CommandGroup", OrgSemKind::CommandGroup)
    .value("Quote", OrgSemKind::Quote)
    .value("Verse", OrgSemKind::Verse)
    .value("Example", OrgSemKind::Example)
    .value("CmdArguments", OrgSemKind::CmdArguments)
    .value("CmdArgument", OrgSemKind::CmdArgument)
    .value("Export", OrgSemKind::Export)
    .value("AdmonitionBlock", OrgSemKind::AdmonitionBlock)
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
    .value("Document", OrgSemKind::Document)
    .value("ParseError", OrgSemKind::ParseError)
    .value("FileTarget", OrgSemKind::FileTarget)
    .value("TextSeparator", OrgSemKind::TextSeparator)
    .value("Include", OrgSemKind::Include)
    .value("DocumentOptions", OrgSemKind::DocumentOptions)
    .value("DocumentGroup", OrgSemKind::DocumentGroup)
    .export_values()
    ;
  pybind11::class_<OrgExporterJson>(m, "OrgExporterJson")
    .def(pybind11::init<>())
    .def("visitNode",
         static_cast<void(OrgExporterJson::*)(sem::SemId)>(&OrgExporterJson::visitNode),
         pybind11::arg("node"),
         R"RAW(Visit top-level node of the exporter, filling in the internal
return state.)RAW")
    .def("exportToString", static_cast<std::string(OrgExporterJson::*)()>(&OrgExporterJson::exportToString))
    .def("exportToFile",
         static_cast<void(OrgExporterJson::*)(std::string)>(&OrgExporterJson::exportToFile),
         pybind11::arg("path"))
    ;
  pybind11::class_<ExporterTreeOpts>(m, "ExporterTreeOpts")
    .def(pybind11::init<>())
    .def_readwrite("withLineCol", &ExporterTreeOpts::withLineCol)
    .def_readwrite("withOriginalId", &ExporterTreeOpts::withOriginalId)
    .def_readwrite("withSubnodeIdx", &ExporterTreeOpts::withSubnodeIdx)
    .def_readwrite("skipEmptyFields", &ExporterTreeOpts::skipEmptyFields)
    .def_readwrite("startLevel", &ExporterTreeOpts::startLevel)
    .def_readwrite("withColor", &ExporterTreeOpts::withColor)
    ;
  pybind11::class_<OrgExporterTree>(m, "OrgExporterTree")
    .def(pybind11::init<>())
    .def("toString",
         static_cast<std::string(OrgExporterTree::*)(sem::SemId, ExporterTreeOpts)>(&OrgExporterTree::toString),
         pybind11::arg("node"),
         pybind11::arg("opts"))
    .def("toFile",
         static_cast<void(OrgExporterTree::*)(sem::SemId, std::string, ExporterTreeOpts)>(&OrgExporterTree::toFile),
         pybind11::arg("node"),
         pybind11::arg("path"),
         pybind11::arg("opts"))
    ;
  pybind11::class_<OrgExporterYaml>(m, "OrgExporterYaml")
    .def(pybind11::init<>())
    .def("visitNode",
         static_cast<void(OrgExporterYaml::*)(sem::SemId)>(&OrgExporterYaml::visitNode),
         pybind11::arg("node"),
         R"RAW(Visit top-level node of the exporter, filling in the internal
return state.)RAW")
    .def("exportToString", static_cast<std::string(OrgExporterYaml::*)()>(&OrgExporterYaml::exportToString))
    .def("exportToFile",
         static_cast<void(OrgExporterYaml::*)(std::string)>(&OrgExporterYaml::exportToFile),
         pybind11::arg("path"))
    ;
  pybind11::class_<OrgContext>(m, "OrgContext")
    .def(pybind11::init<>())
    .def("parseFile",
         static_cast<void(OrgContext::*)(std::string)>(&OrgContext::parseFile),
         pybind11::arg("file"))
    .def("parseString",
         static_cast<void(OrgContext::*)(std::string)>(&OrgContext::parseString),
         pybind11::arg("text"))
    .def("getNode", static_cast<sem::SemIdT<sem::Document>(OrgContext::*)()>(&OrgContext::getNode))
    ;
  pybind11::class_<ExporterPython>(m, "ExporterPython")
    .def(pybind11::init<>())
    .def("enablePyStreamTrace",
         static_cast<void(ExporterPython::*)(pybind11::object)>(&ExporterPython::enablePyStreamTrace),
         pybind11::arg("stream"))
    .def("enableBufferTrace", static_cast<void(ExporterPython::*)()>(&ExporterPython::enableBufferTrace))
    .def("getTraceBuffer", static_cast<std::string(ExporterPython::*)() const>(&ExporterPython::getTraceBuffer))
    .def("enableFileTrace",
         static_cast<void(ExporterPython::*)(std::string const&)>(&ExporterPython::enableFileTrace),
         pybind11::arg("path"))
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
         static_cast<ExporterPython::Res(ExporterPython::*)(sem::SemId)>(&ExporterPython::evalTop),
         pybind11::arg("org"))
    .def("eval",
         static_cast<ExporterPython::Res(ExporterPython::*)(sem::SemId)>(&ExporterPython::eval),
         pybind11::arg("org"))
    ;
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
    .export_values()
    ;
}
/* clang-format on */