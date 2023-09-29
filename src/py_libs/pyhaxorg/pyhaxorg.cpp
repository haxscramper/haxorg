#undef slots
#include <pybind11/pybind11.h>
#include <sem/SemOrg.hpp>
#include <pybind11/stl.h>
#ifndef IN_CLANGD_PROCESSING
  #define PY_HAXORG_COMPILING
  #include "pyhaxorg_manual_impl.hpp"
#endif
PYBIND11_MODULE(pyhaxorg, m) {
  pybind11::class_<sem::DefaultSemId<sem::Stmt>>(m, "Stmt")
    .def(pybind11::init<>())
    .def_property("attached",
                  [](sem::DefaultSemId<sem::Stmt> _self) -> Vec<sem::SemId> { return _self.id->attached; },
                  [](sem::DefaultSemId<sem::Stmt> _self, Vec<sem::SemId> attached) { _self.id->attached = attached; })
    .def("getAttached",
         [](sem::DefaultSemId<sem::Stmt> _self, OrgSemKind kind) -> Opt<sem::SemId> { return _self.id->getAttached(kind); },
         pybind11::arg("kind"))
    ;
  pybind11::class_<sem::DefaultSemId<sem::Inline>>(m, "Inline")
    .def(pybind11::init<>())
    ;
  pybind11::class_<sem::DefaultSemId<sem::StmtList>>(m, "StmtList")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::StmtList> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Empty>>(m, "Empty")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Empty> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Row>>(m, "Row")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Row> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Table>>(m, "Table")
    .def(pybind11::init<>())
    .def_property("rows",
                  [](sem::DefaultSemId<sem::Table> _self) -> Vec<sem::SemIdT<sem::Row>> { return _self.id->rows; },
                  [](sem::DefaultSemId<sem::Table> _self, Vec<sem::SemIdT<sem::Row>> rows) { _self.id->rows = rows; })
    .def("getKind",
         [](sem::DefaultSemId<sem::Table> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::HashTag>>(m, "HashTag")
    .def(pybind11::init<>())
    .def_property("head",
                  [](sem::DefaultSemId<sem::HashTag> _self) -> Str { return _self.id->head; },
                  [](sem::DefaultSemId<sem::HashTag> _self, Str head) { _self.id->head = head; })
    .def_property("subtags",
                  [](sem::DefaultSemId<sem::HashTag> _self) -> Vec<sem::SemIdT<sem::HashTag>> { return _self.id->subtags; },
                  [](sem::DefaultSemId<sem::HashTag> _self, Vec<sem::SemIdT<sem::HashTag>> subtags) { _self.id->subtags = subtags; })
    .def("getKind",
         [](sem::DefaultSemId<sem::HashTag> _self) -> OrgSemKind { return _self.id->getKind(); })
    .def("prefixMatch",
         [](sem::DefaultSemId<sem::HashTag> _self, Vec<Str> const& prefix) -> bool { return _self.id->prefixMatch(prefix); },
         pybind11::arg("prefix"),
         R"RAW(Check if list of tag names is a prefix for either of the nested hash tags in this one)RAW")
    ;
  pybind11::class_<sem::DefaultSemId<sem::Footnote>>(m, "Footnote")
    .def(pybind11::init<>())
    .def_property("tag",
                  [](sem::DefaultSemId<sem::Footnote> _self) -> Str { return _self.id->tag; },
                  [](sem::DefaultSemId<sem::Footnote> _self, Str tag) { _self.id->tag = tag; })
    .def_property("definition",
                  [](sem::DefaultSemId<sem::Footnote> _self) -> Opt<sem::SemId> { return _self.id->definition; },
                  [](sem::DefaultSemId<sem::Footnote> _self, Opt<sem::SemId> definition) { _self.id->definition = definition; })
    .def("getKind",
         [](sem::DefaultSemId<sem::Footnote> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Completion>>(m, "Completion")
    .def(pybind11::init<>())
    .def_property("done",
                  [](sem::DefaultSemId<sem::Completion> _self) -> int { return _self.id->done; },
                  [](sem::DefaultSemId<sem::Completion> _self, int done) { _self.id->done = done; })
    .def_property("full",
                  [](sem::DefaultSemId<sem::Completion> _self) -> int { return _self.id->full; },
                  [](sem::DefaultSemId<sem::Completion> _self, int full) { _self.id->full = full; })
    .def_property("isPercent",
                  [](sem::DefaultSemId<sem::Completion> _self) -> bool { return _self.id->isPercent; },
                  [](sem::DefaultSemId<sem::Completion> _self, bool isPercent) { _self.id->isPercent = isPercent; })
    .def("getKind",
         [](sem::DefaultSemId<sem::Completion> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Paragraph>>(m, "Paragraph")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Paragraph> _self) -> OrgSemKind { return _self.id->getKind(); })
    .def("isFootnoteDefinition",
         [](sem::DefaultSemId<sem::Paragraph> _self) -> bool { return _self.id->isFootnoteDefinition(); },
         R"RAW(Check if paragraph defines footnote)RAW")
    ;
  pybind11::class_<sem::DefaultSemId<sem::Format>>(m, "Format")
    .def(pybind11::init<>())
    ;
  pybind11::class_<sem::DefaultSemId<sem::Center>>(m, "Center")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Center> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Command>>(m, "Command")
    .def(pybind11::init<>())
    ;
  pybind11::class_<sem::DefaultSemId<sem::LineCommand>>(m, "LineCommand")
    .def(pybind11::init<>())
    ;
  pybind11::class_<sem::DefaultSemId<sem::Standalone>>(m, "Standalone")
    .def(pybind11::init<>())
    ;
  pybind11::class_<sem::DefaultSemId<sem::Attached>>(m, "Attached")
    .def(pybind11::init<>())
    ;
  pybind11::class_<sem::DefaultSemId<sem::Caption>>(m, "Caption")
    .def(pybind11::init<>())
    .def_property("text",
                  [](sem::DefaultSemId<sem::Caption> _self) -> sem::SemIdT<sem::Paragraph> { return _self.id->text; },
                  [](sem::DefaultSemId<sem::Caption> _self, sem::SemIdT<sem::Paragraph> text) { _self.id->text = text; })
    .def("getKind",
         [](sem::DefaultSemId<sem::Caption> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::CommandGroup>>(m, "CommandGroup")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::CommandGroup> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Block>>(m, "Block")
    .def(pybind11::init<>())
    ;
  pybind11::class_<sem::DefaultSemId<sem::Quote>>(m, "Quote")
    .def(pybind11::init<>())
    .def_property("text",
                  [](sem::DefaultSemId<sem::Quote> _self) -> sem::SemIdT<sem::Paragraph> { return _self.id->text; },
                  [](sem::DefaultSemId<sem::Quote> _self, sem::SemIdT<sem::Paragraph> text) { _self.id->text = text; })
    .def("getKind",
         [](sem::DefaultSemId<sem::Quote> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Example>>(m, "Example")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Example> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::CmdArguments>>(m, "CmdArguments")
    .def(pybind11::init<>())
    .def_property("positional",
                  [](sem::DefaultSemId<sem::CmdArguments> _self) -> Vec<sem::SemIdT<sem::CmdArgument>> { return _self.id->positional; },
                  [](sem::DefaultSemId<sem::CmdArguments> _self, Vec<sem::SemIdT<sem::CmdArgument>> positional) { _self.id->positional = positional; })
    .def_property("named",
                  [](sem::DefaultSemId<sem::CmdArguments> _self) -> UnorderedMap<Str, sem::SemIdT<sem::CmdArgument>> { return _self.id->named; },
                  [](sem::DefaultSemId<sem::CmdArguments> _self, UnorderedMap<Str, sem::SemIdT<sem::CmdArgument>> named) { _self.id->named = named; })
    .def("getKind",
         [](sem::DefaultSemId<sem::CmdArguments> _self) -> OrgSemKind { return _self.id->getKind(); })
    .def("popArg",
         [](sem::DefaultSemId<sem::CmdArguments> _self, Str key) -> Opt<sem::SemIdT<sem::CmdArgument>> { return _self.id->popArg(key); },
         pybind11::arg("key"),
         R"RAW(Remove argument value from the map and return it if present)RAW")
    ;
  pybind11::class_<sem::DefaultSemId<sem::CmdArgument>>(m, "CmdArgument")
    .def(pybind11::init<>())
    .def_property("key",
                  [](sem::DefaultSemId<sem::CmdArgument> _self) -> Opt<Str> { return _self.id->key; },
                  [](sem::DefaultSemId<sem::CmdArgument> _self, Opt<Str> key) { _self.id->key = key; })
    .def_property("value",
                  [](sem::DefaultSemId<sem::CmdArgument> _self) -> Str { return _self.id->value; },
                  [](sem::DefaultSemId<sem::CmdArgument> _self, Str value) { _self.id->value = value; })
    .def("getKind",
         [](sem::DefaultSemId<sem::CmdArgument> _self) -> OrgSemKind { return _self.id->getKind(); })
    .def("getInt",
         [](sem::DefaultSemId<sem::CmdArgument> _self) -> Opt<int> { return _self.id->getInt(); },
         R"RAW(Parse argument as integer value)RAW")
    .def("getBool",
         [](sem::DefaultSemId<sem::CmdArgument> _self) -> Opt<bool> { return _self.id->getBool(); },
         R"RAW(Get argument as bool)RAW")
    .def("getString",
         [](sem::DefaultSemId<sem::CmdArgument> _self) -> Str { return _self.id->getString(); },
         R"RAW(Get original string)RAW")
    ;
  pybind11::class_<sem::DefaultSemId<sem::Export>>(m, "Export")
    .def(pybind11::init<>())
    .def_property("format",
                  [](sem::DefaultSemId<sem::Export> _self) -> sem::Export::Format { return _self.id->format; },
                  [](sem::DefaultSemId<sem::Export> _self, sem::Export::Format format) { _self.id->format = format; })
    .def_property("exporter",
                  [](sem::DefaultSemId<sem::Export> _self) -> Str { return _self.id->exporter; },
                  [](sem::DefaultSemId<sem::Export> _self, Str exporter) { _self.id->exporter = exporter; })
    .def_property("parameters",
                  [](sem::DefaultSemId<sem::Export> _self) -> sem::SemIdT<sem::CmdArguments> { return _self.id->parameters; },
                  [](sem::DefaultSemId<sem::Export> _self, sem::SemIdT<sem::CmdArguments> parameters) { _self.id->parameters = parameters; })
    .def_property("placement",
                  [](sem::DefaultSemId<sem::Export> _self) -> Opt<Str> { return _self.id->placement; },
                  [](sem::DefaultSemId<sem::Export> _self, Opt<Str> placement) { _self.id->placement = placement; })
    .def_property("content",
                  [](sem::DefaultSemId<sem::Export> _self) -> Str { return _self.id->content; },
                  [](sem::DefaultSemId<sem::Export> _self, Str content) { _self.id->content = content; })
    .def("getKind",
         [](sem::DefaultSemId<sem::Export> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::enum_<sem::Export::Format>(m, "ExportFormat")
    .value("Inline", sem::Export::Format::Inline)
    .value("Line", sem::Export::Format::Line)
    .value("Block", sem::Export::Format::Block)
    .export_values()
    ;
  pybind11::class_<sem::DefaultSemId<sem::AdmonitionBlock>>(m, "AdmonitionBlock")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::AdmonitionBlock> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Code>>(m, "Code")
    .def(pybind11::init<>())
    .def_property("lang",
                  [](sem::DefaultSemId<sem::Code> _self) -> Opt<Str> { return _self.id->lang; },
                  [](sem::DefaultSemId<sem::Code> _self, Opt<Str> lang) { _self.id->lang = lang; })
    .def_property("switches",
                  [](sem::DefaultSemId<sem::Code> _self) -> Vec<sem::Code::Switch> { return _self.id->switches; },
                  [](sem::DefaultSemId<sem::Code> _self, Vec<sem::Code::Switch> switches) { _self.id->switches = switches; })
    .def_property("exports",
                  [](sem::DefaultSemId<sem::Code> _self) -> sem::Code::Exports { return _self.id->exports; },
                  [](sem::DefaultSemId<sem::Code> _self, sem::Code::Exports exports) { _self.id->exports = exports; })
    .def_property("parameters",
                  [](sem::DefaultSemId<sem::Code> _self) -> sem::SemIdT<sem::CmdArguments> { return _self.id->parameters; },
                  [](sem::DefaultSemId<sem::Code> _self, sem::SemIdT<sem::CmdArguments> parameters) { _self.id->parameters = parameters; })
    .def_property("cache",
                  [](sem::DefaultSemId<sem::Code> _self) -> bool { return _self.id->cache; },
                  [](sem::DefaultSemId<sem::Code> _self, bool cache) { _self.id->cache = cache; })
    .def_property("eval",
                  [](sem::DefaultSemId<sem::Code> _self) -> bool { return _self.id->eval; },
                  [](sem::DefaultSemId<sem::Code> _self, bool eval) { _self.id->eval = eval; })
    .def_property("noweb",
                  [](sem::DefaultSemId<sem::Code> _self) -> bool { return _self.id->noweb; },
                  [](sem::DefaultSemId<sem::Code> _self, bool noweb) { _self.id->noweb = noweb; })
    .def_property("hlines",
                  [](sem::DefaultSemId<sem::Code> _self) -> bool { return _self.id->hlines; },
                  [](sem::DefaultSemId<sem::Code> _self, bool hlines) { _self.id->hlines = hlines; })
    .def_property("tangle",
                  [](sem::DefaultSemId<sem::Code> _self) -> bool { return _self.id->tangle; },
                  [](sem::DefaultSemId<sem::Code> _self, bool tangle) { _self.id->tangle = tangle; })
    .def("getKind",
         [](sem::DefaultSemId<sem::Code> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;

  pybind11::class_<sem::Code::Switch::LineStart>(m, "CodeSwitchLineStart")
    .def(pybind11::init<>())
    .def_readwrite("start", &sem::Code::Switch::LineStart::start, "First line number")
    .def_readwrite("extendLast", &sem::Code::Switch::LineStart::extendLast, "Continue numbering from the previous block nstead of starting anew")
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
  pybind11::enum_<sem::Code::Results>(m, "CodeResults")
    .value("Replace", sem::Code::Results::Replace)
    .export_values()
    ;
  pybind11::enum_<sem::Code::Exports>(m, "CodeExports")
    .value("None", sem::Code::Exports::None)
    .value("Both", sem::Code::Exports::Both)
    .value("Code", sem::Code::Exports::Code)
    .value("Results", sem::Code::Exports::Results)
    .export_values()
    ;
  pybind11::class_<sem::DefaultSemId<sem::Time>>(m, "Time")
    .def(pybind11::init<>())
    .def_property("isActive",
                  [](sem::DefaultSemId<sem::Time> _self) -> bool { return _self.id->isActive; },
                  [](sem::DefaultSemId<sem::Time> _self, bool isActive) { _self.id->isActive = isActive; })
    .def("getKind",
         [](sem::DefaultSemId<sem::Time> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::Time::Repeat>(m, "TimeRepeat")
    .def(pybind11::init<>())
    .def_readwrite("mode", &sem::Time::Repeat::mode, "mode")
    .def_readwrite("period", &sem::Time::Repeat::period, "period")
    .def_readwrite("count", &sem::Time::Repeat::count, "count")
    ;
  pybind11::enum_<sem::Time::Repeat::Mode>(m, "TimeRepeatMode")
    .value("None", sem::Time::Repeat::Mode::None)
    .value("Exact", sem::Time::Repeat::Mode::Exact)
    .value("FirstMatch", sem::Time::Repeat::Mode::FirstMatch)
    .value("SameDay", sem::Time::Repeat::Mode::SameDay)
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
  pybind11::class_<sem::DefaultSemId<sem::TimeRange>>(m, "TimeRange")
    .def(pybind11::init<>())
    .def_property("from",
                  [](sem::DefaultSemId<sem::TimeRange> _self) -> sem::SemIdT<sem::Time> { return _self.id->from; },
                  [](sem::DefaultSemId<sem::TimeRange> _self, sem::SemIdT<sem::Time> from) { _self.id->from = from; })
    .def_property("to",
                  [](sem::DefaultSemId<sem::TimeRange> _self) -> sem::SemIdT<sem::Time> { return _self.id->to; },
                  [](sem::DefaultSemId<sem::TimeRange> _self, sem::SemIdT<sem::Time> to) { _self.id->to = to; })
    .def("getKind",
         [](sem::DefaultSemId<sem::TimeRange> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Macro>>(m, "Macro")
    .def(pybind11::init<>())
    .def_property("name",
                  [](sem::DefaultSemId<sem::Macro> _self) -> Str { return _self.id->name; },
                  [](sem::DefaultSemId<sem::Macro> _self, Str name) { _self.id->name = name; })
    .def_property("arguments",
                  [](sem::DefaultSemId<sem::Macro> _self) -> Vec<Str> { return _self.id->arguments; },
                  [](sem::DefaultSemId<sem::Macro> _self, Vec<Str> arguments) { _self.id->arguments = arguments; })
    .def("getKind",
         [](sem::DefaultSemId<sem::Macro> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Symbol>>(m, "Symbol")
    .def(pybind11::init<>())
    .def_property("name",
                  [](sem::DefaultSemId<sem::Symbol> _self) -> Str { return _self.id->name; },
                  [](sem::DefaultSemId<sem::Symbol> _self, Str name) { _self.id->name = name; })
    .def_property("parameters",
                  [](sem::DefaultSemId<sem::Symbol> _self) -> Vec<sem::Symbol::Param> { return _self.id->parameters; },
                  [](sem::DefaultSemId<sem::Symbol> _self, Vec<sem::Symbol::Param> parameters) { _self.id->parameters = parameters; })
    .def_property("positional",
                  [](sem::DefaultSemId<sem::Symbol> _self) -> Vec<sem::SemId> { return _self.id->positional; },
                  [](sem::DefaultSemId<sem::Symbol> _self, Vec<sem::SemId> positional) { _self.id->positional = positional; })
    .def("getKind",
         [](sem::DefaultSemId<sem::Symbol> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::Symbol::Param>(m, "SymbolParam")
    .def(pybind11::init<>())
    .def_readwrite("key", &sem::Symbol::Param::key, "Key -- for non-positional")
    .def_readwrite("value", &sem::Symbol::Param::value, "Uninterpreted value")
    ;
  pybind11::class_<sem::DefaultSemId<sem::SubtreeLog>>(m, "SubtreeLog")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::SubtreeLog> _self) -> OrgSemKind { return _self.id->getKind(); })
    .def("setDescription",
         [](sem::DefaultSemId<sem::SubtreeLog> _self, sem::SemIdT<sem::StmtList> desc) -> void { return _self.id->setDescription(desc); },
         pybind11::arg("desc"))
    ;
  pybind11::class_<sem::SubtreeLog::DescribedLog>(m, "SubtreeLogDescribedLog")
    .def(pybind11::init<>())
    .def_readwrite("desc", &sem::SubtreeLog::DescribedLog::desc, "Optional description of the log entry")
    ;
  pybind11::class_<sem::SubtreeLog::Priority>(m, "SubtreeLogPriority")
    .def(pybind11::init<>())
    .def_readwrite("oldPriority", &sem::SubtreeLog::Priority::oldPriority, "Previous priority for change and removal")
    .def_readwrite("newPriority", &sem::SubtreeLog::Priority::newPriority, "New priority for change and addition")
    .def_readwrite("on", &sem::SubtreeLog::Priority::on, "When priority was changed")
    ;
  pybind11::enum_<sem::SubtreeLog::Priority::Action>(m, "SubtreeLogPriorityAction")
    .value("Added", sem::SubtreeLog::Priority::Action::Added)
    .value("Removed", sem::SubtreeLog::Priority::Action::Removed)
    .value("Changed", sem::SubtreeLog::Priority::Action::Changed)
    .export_values()
    ;
  pybind11::class_<sem::SubtreeLog::Note>(m, "SubtreeLogNote")
    .def(pybind11::init<>())
    .def_readwrite("on", &sem::SubtreeLog::Note::on, "Where log was taken")
    ;
  pybind11::class_<sem::SubtreeLog::Refile>(m, "SubtreeLogRefile")
    .def(pybind11::init<>())
    .def_readwrite("on", &sem::SubtreeLog::Refile::on, "When the refiling happened")
    .def_readwrite("from", &sem::SubtreeLog::Refile::from, "Link to the original subtree")
    ;
  pybind11::class_<sem::SubtreeLog::Clock>(m, "SubtreeLogClock")
    .def(pybind11::init<>())
    ;
  pybind11::class_<sem::SubtreeLog::State>(m, "SubtreeLogState")
    .def(pybind11::init<>())
    .def_readwrite("from", &sem::SubtreeLog::State::from)
    .def_readwrite("to", &sem::SubtreeLog::State::to)
    .def_readwrite("on", &sem::SubtreeLog::State::on)
    ;
  pybind11::class_<sem::SubtreeLog::Tag>(m, "SubtreeLogTag")
    .def(pybind11::init<>())
    .def_readwrite("on", &sem::SubtreeLog::Tag::on, "When the log was assigned")
    .def_readwrite("tag", &sem::SubtreeLog::Tag::tag, "Tag in question")
    .def_readwrite("added", &sem::SubtreeLog::Tag::added, "Added/removed?")
    ;
  pybind11::class_<sem::DefaultSemId<sem::Subtree>>(m, "Subtree")
    .def(pybind11::init<>())
    .def_property("level",
                  [](sem::DefaultSemId<sem::Subtree> _self) -> int { return _self.id->level; },
                  [](sem::DefaultSemId<sem::Subtree> _self, int level) { _self.id->level = level; })
    .def_property("treeId",
                  [](sem::DefaultSemId<sem::Subtree> _self) -> Opt<Str> { return _self.id->treeId; },
                  [](sem::DefaultSemId<sem::Subtree> _self, Opt<Str> treeId) { _self.id->treeId = treeId; })
    .def_property("todo",
                  [](sem::DefaultSemId<sem::Subtree> _self) -> Opt<Str> { return _self.id->todo; },
                  [](sem::DefaultSemId<sem::Subtree> _self, Opt<Str> todo) { _self.id->todo = todo; })
    .def_property("completion",
                  [](sem::DefaultSemId<sem::Subtree> _self) -> Opt<sem::SemIdT<sem::Completion>> { return _self.id->completion; },
                  [](sem::DefaultSemId<sem::Subtree> _self, Opt<sem::SemIdT<sem::Completion>> completion) { _self.id->completion = completion; })
    .def_property("description",
                  [](sem::DefaultSemId<sem::Subtree> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self.id->description; },
                  [](sem::DefaultSemId<sem::Subtree> _self, Opt<sem::SemIdT<sem::Paragraph>> description) { _self.id->description = description; })
    .def_property("tags",
                  [](sem::DefaultSemId<sem::Subtree> _self) -> Vec<sem::SemIdT<sem::HashTag>> { return _self.id->tags; },
                  [](sem::DefaultSemId<sem::Subtree> _self, Vec<sem::SemIdT<sem::HashTag>> tags) { _self.id->tags = tags; })
    .def_property("title",
                  [](sem::DefaultSemId<sem::Subtree> _self) -> sem::SemIdT<sem::Paragraph> { return _self.id->title; },
                  [](sem::DefaultSemId<sem::Subtree> _self, sem::SemIdT<sem::Paragraph> title) { _self.id->title = title; })
    .def_property("logbook",
                  [](sem::DefaultSemId<sem::Subtree> _self) -> Vec<sem::SemIdT<sem::SubtreeLog>> { return _self.id->logbook; },
                  [](sem::DefaultSemId<sem::Subtree> _self, Vec<sem::SemIdT<sem::SubtreeLog>> logbook) { _self.id->logbook = logbook; })
    .def_property("properties",
                  [](sem::DefaultSemId<sem::Subtree> _self) -> Vec<sem::Subtree::Property> { return _self.id->properties; },
                  [](sem::DefaultSemId<sem::Subtree> _self, Vec<sem::Subtree::Property> properties) { _self.id->properties = properties; })
    .def_property("closed",
                  [](sem::DefaultSemId<sem::Subtree> _self) -> Opt<sem::SemIdT<sem::Time>> { return _self.id->closed; },
                  [](sem::DefaultSemId<sem::Subtree> _self, Opt<sem::SemIdT<sem::Time>> closed) { _self.id->closed = closed; })
    .def_property("deadline",
                  [](sem::DefaultSemId<sem::Subtree> _self) -> Opt<sem::SemIdT<sem::Time>> { return _self.id->deadline; },
                  [](sem::DefaultSemId<sem::Subtree> _self, Opt<sem::SemIdT<sem::Time>> deadline) { _self.id->deadline = deadline; })
    .def_property("scheduled",
                  [](sem::DefaultSemId<sem::Subtree> _self) -> Opt<sem::SemIdT<sem::Time>> { return _self.id->scheduled; },
                  [](sem::DefaultSemId<sem::Subtree> _self, Opt<sem::SemIdT<sem::Time>> scheduled) { _self.id->scheduled = scheduled; })
    .def("getKind",
         [](sem::DefaultSemId<sem::Subtree> _self) -> OrgSemKind { return _self.id->getKind(); })
    .def("getTimePeriods",
         [](sem::DefaultSemId<sem::Subtree> _self, IntSet<sem::Subtree::Period::Kind> kinds) -> Vec<sem::Subtree::Period> { return _self.id->getTimePeriods(kinds); },
         pybind11::arg("kinds"))
    .def("getProperties",
         [](sem::DefaultSemId<sem::Subtree> _self, sem::Subtree::Property::Kind kind, Str const& subkind) -> Vec<sem::Subtree::Property> { return _self.id->getProperties(kind, subkind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", ""))
    .def("getProperty",
         [](sem::DefaultSemId<sem::Subtree> _self, sem::Subtree::Property::Kind kind, Str const& subkind) -> Opt<sem::Subtree::Property> { return _self.id->getProperty(kind, subkind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", ""))
    .def("getContextualProperties",
         [](sem::DefaultSemId<sem::Subtree> _self, sem::Subtree::Property::Kind kind, Str const& subkind) -> Vec<sem::Subtree::Property> { return _self.id->getContextualProperties(kind, subkind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", ""))
    .def("getContextualProperty",
         [](sem::DefaultSemId<sem::Subtree> _self, sem::Subtree::Property::Kind kind, Str const& subkind) -> Opt<sem::Subtree::Property> { return _self.id->getContextualProperty(kind, subkind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", ""))
    ;

  pybind11::enum_<sem::Subtree::Period::Kind>(m, "SubtreePeriodKind")
    .value("Clocked", sem::Subtree::Period::Kind::Clocked)
    .value("Scheduled", sem::Subtree::Period::Kind::Scheduled)
    .value("Titled", sem::Subtree::Period::Kind::Titled)
    .value("Deadline", sem::Subtree::Period::Kind::Deadline)
    .value("Created", sem::Subtree::Period::Kind::Created)
    .value("Repeated", sem::Subtree::Period::Kind::Repeated)
    .export_values()
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
  pybind11::class_<sem::DefaultSemId<sem::LatexBody>>(m, "LatexBody")
    .def(pybind11::init<>())
    ;
  pybind11::class_<sem::DefaultSemId<sem::InlineMath>>(m, "InlineMath")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::InlineMath> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Leaf>>(m, "Leaf")
    .def(pybind11::init<>())
    .def_property("text",
                  [](sem::DefaultSemId<sem::Leaf> _self) -> Str { return _self.id->text; },
                  [](sem::DefaultSemId<sem::Leaf> _self, Str text) { _self.id->text = text; })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Escaped>>(m, "Escaped")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Escaped> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Newline>>(m, "Newline")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Newline> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Space>>(m, "Space")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Space> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Word>>(m, "Word")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Word> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::AtMention>>(m, "AtMention")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::AtMention> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::RawText>>(m, "RawText")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::RawText> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Punctuation>>(m, "Punctuation")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Punctuation> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Placeholder>>(m, "Placeholder")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Placeholder> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::BigIdent>>(m, "BigIdent")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::BigIdent> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Markup>>(m, "Markup")
    .def(pybind11::init<>())
    ;
  pybind11::class_<sem::DefaultSemId<sem::Bold>>(m, "Bold")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Bold> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Underline>>(m, "Underline")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Underline> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Monospace>>(m, "Monospace")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Monospace> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::MarkQuote>>(m, "MarkQuote")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::MarkQuote> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Verbatim>>(m, "Verbatim")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Verbatim> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Italic>>(m, "Italic")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Italic> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Strike>>(m, "Strike")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Strike> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Par>>(m, "Par")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Par> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::List>>(m, "List")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::List> _self) -> OrgSemKind { return _self.id->getKind(); })
    .def("isDescriptionList",
         [](sem::DefaultSemId<sem::List> _self) -> bool { return _self.id->isDescriptionList(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::ListItem>>(m, "ListItem")
    .def(pybind11::init<>())
    .def_property("checkbox",
                  [](sem::DefaultSemId<sem::ListItem> _self) -> sem::ListItem::Checkbox { return _self.id->checkbox; },
                  [](sem::DefaultSemId<sem::ListItem> _self, sem::ListItem::Checkbox checkbox) { _self.id->checkbox = checkbox; })
    .def_property("header",
                  [](sem::DefaultSemId<sem::ListItem> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self.id->header; },
                  [](sem::DefaultSemId<sem::ListItem> _self, Opt<sem::SemIdT<sem::Paragraph>> header) { _self.id->header = header; })
    .def("getKind",
         [](sem::DefaultSemId<sem::ListItem> _self) -> OrgSemKind { return _self.id->getKind(); })
    .def("isDescriptionItem",
         [](sem::DefaultSemId<sem::ListItem> _self) -> bool { return _self.id->isDescriptionItem(); })
    ;
  pybind11::enum_<sem::ListItem::Checkbox>(m, "ListItemCheckbox")
    .value("None", sem::ListItem::Checkbox::None)
    .value("Done", sem::ListItem::Checkbox::Done)
    .value("Empty", sem::ListItem::Checkbox::Empty)
    .export_values()
    ;
  pybind11::class_<sem::DefaultSemId<sem::Link>>(m, "Link")
    .def(pybind11::init<>())
    .def_property("description",
                  [](sem::DefaultSemId<sem::Link> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self.id->description; },
                  [](sem::DefaultSemId<sem::Link> _self, Opt<sem::SemIdT<sem::Paragraph>> description) { _self.id->description = description; })
    .def("getKind",
         [](sem::DefaultSemId<sem::Link> _self) -> OrgSemKind { return _self.id->getKind(); })
    .def("resolve",
         [](sem::DefaultSemId<sem::Link> _self, sem::Document const& doc) -> Opt<sem::SemId> { return _self.id->resolve(doc); },
         pybind11::arg("doc"))
    .def("resolve",
         [](sem::DefaultSemId<sem::Link> _self) -> Opt<sem::SemId> { return _self.id->resolve(); })
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
  pybind11::class_<sem::DefaultSemId<sem::Document>>(m, "Document")
    .def(pybind11::init<>())
    .def_property("idTable",
                  [](sem::DefaultSemId<sem::Document> _self) -> UnorderedMap<Str, sem::SemId> { return _self.id->idTable; },
                  [](sem::DefaultSemId<sem::Document> _self, UnorderedMap<Str, sem::SemId> idTable) { _self.id->idTable = idTable; })
    .def_property("nameTable",
                  [](sem::DefaultSemId<sem::Document> _self) -> UnorderedMap<Str, sem::SemId> { return _self.id->nameTable; },
                  [](sem::DefaultSemId<sem::Document> _self, UnorderedMap<Str, sem::SemId> nameTable) { _self.id->nameTable = nameTable; })
    .def_property("footnoteTable",
                  [](sem::DefaultSemId<sem::Document> _self) -> UnorderedMap<Str, sem::SemId> { return _self.id->footnoteTable; },
                  [](sem::DefaultSemId<sem::Document> _self, UnorderedMap<Str, sem::SemId> footnoteTable) { _self.id->footnoteTable = footnoteTable; })
    .def_property("anchorTable",
                  [](sem::DefaultSemId<sem::Document> _self) -> UnorderedMap<Str, sem::SemId> { return _self.id->anchorTable; },
                  [](sem::DefaultSemId<sem::Document> _self, UnorderedMap<Str, sem::SemId> anchorTable) { _self.id->anchorTable = anchorTable; })
    .def_property("title",
                  [](sem::DefaultSemId<sem::Document> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self.id->title; },
                  [](sem::DefaultSemId<sem::Document> _self, Opt<sem::SemIdT<sem::Paragraph>> title) { _self.id->title = title; })
    .def_property("author",
                  [](sem::DefaultSemId<sem::Document> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self.id->author; },
                  [](sem::DefaultSemId<sem::Document> _self, Opt<sem::SemIdT<sem::Paragraph>> author) { _self.id->author = author; })
    .def_property("creator",
                  [](sem::DefaultSemId<sem::Document> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self.id->creator; },
                  [](sem::DefaultSemId<sem::Document> _self, Opt<sem::SemIdT<sem::Paragraph>> creator) { _self.id->creator = creator; })
    .def_property("email",
                  [](sem::DefaultSemId<sem::Document> _self) -> Opt<sem::SemIdT<sem::RawText>> { return _self.id->email; },
                  [](sem::DefaultSemId<sem::Document> _self, Opt<sem::SemIdT<sem::RawText>> email) { _self.id->email = email; })
    .def_property("language",
                  [](sem::DefaultSemId<sem::Document> _self) -> Opt<Vec<Str>> { return _self.id->language; },
                  [](sem::DefaultSemId<sem::Document> _self, Opt<Vec<Str>> language) { _self.id->language = language; })
    .def_property("options",
                  [](sem::DefaultSemId<sem::Document> _self) -> sem::SemIdT<sem::DocumentOptions> { return _self.id->options; },
                  [](sem::DefaultSemId<sem::Document> _self, sem::SemIdT<sem::DocumentOptions> options) { _self.id->options = options; })
    .def_property("exportFileName",
                  [](sem::DefaultSemId<sem::Document> _self) -> Opt<Str> { return _self.id->exportFileName; },
                  [](sem::DefaultSemId<sem::Document> _self, Opt<Str> exportFileName) { _self.id->exportFileName = exportFileName; })
    .def("getKind",
         [](sem::DefaultSemId<sem::Document> _self) -> OrgSemKind { return _self.id->getKind(); })
    .def("resolve",
         [](sem::DefaultSemId<sem::Document> _self, sem::SemId const& node) -> Opt<sem::SemId> { return _self.id->resolve(node); },
         pybind11::arg("node"))
    .def("getSubtree",
         [](sem::DefaultSemId<sem::Document> _self, Str const& id) -> Opt<sem::SemIdT<sem::Subtree>> { return _self.id->getSubtree(id); },
         pybind11::arg("id"))
    .def("getProperties",
         [](sem::DefaultSemId<sem::Document> _self, sem::Subtree::Property::Kind kind, Str const& subKind) -> Vec<sem::Subtree::Property> { return _self.id->getProperties(kind, subKind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", ""))
    .def("getProperty",
         [](sem::DefaultSemId<sem::Document> _self, sem::Subtree::Property::Kind kind, Str const& subKind) -> Opt<sem::Subtree::Property> { return _self.id->getProperty(kind, subKind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", ""))
    ;
  pybind11::class_<sem::DefaultSemId<sem::ParseError>>(m, "ParseError")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::ParseError> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::FileTarget>>(m, "FileTarget")
    .def(pybind11::init<>())
    .def_property("path",
                  [](sem::DefaultSemId<sem::FileTarget> _self) -> Str { return _self.id->path; },
                  [](sem::DefaultSemId<sem::FileTarget> _self, Str path) { _self.id->path = path; })
    .def_property("line",
                  [](sem::DefaultSemId<sem::FileTarget> _self) -> Opt<int> { return _self.id->line; },
                  [](sem::DefaultSemId<sem::FileTarget> _self, Opt<int> line) { _self.id->line = line; })
    .def_property("searchTarget",
                  [](sem::DefaultSemId<sem::FileTarget> _self) -> Opt<Str> { return _self.id->searchTarget; },
                  [](sem::DefaultSemId<sem::FileTarget> _self, Opt<Str> searchTarget) { _self.id->searchTarget = searchTarget; })
    .def_property("restrictToHeadlines",
                  [](sem::DefaultSemId<sem::FileTarget> _self) -> bool { return _self.id->restrictToHeadlines; },
                  [](sem::DefaultSemId<sem::FileTarget> _self, bool restrictToHeadlines) { _self.id->restrictToHeadlines = restrictToHeadlines; })
    .def_property("targetId",
                  [](sem::DefaultSemId<sem::FileTarget> _self) -> Opt<Str> { return _self.id->targetId; },
                  [](sem::DefaultSemId<sem::FileTarget> _self, Opt<Str> targetId) { _self.id->targetId = targetId; })
    .def_property("regexp",
                  [](sem::DefaultSemId<sem::FileTarget> _self) -> Opt<Str> { return _self.id->regexp; },
                  [](sem::DefaultSemId<sem::FileTarget> _self, Opt<Str> regexp) { _self.id->regexp = regexp; })
    .def("getKind",
         [](sem::DefaultSemId<sem::FileTarget> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::TextSeparator>>(m, "TextSeparator")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::TextSeparator> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  pybind11::class_<sem::DefaultSemId<sem::Include>>(m, "Include")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::Include> _self) -> OrgSemKind { return _self.id->getKind(); })
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
  pybind11::class_<sem::DefaultSemId<sem::DocumentOptions>>(m, "DocumentOptions")
    .def(pybind11::init<>())
    .def_property("brokenLinks",
                  [](sem::DefaultSemId<sem::DocumentOptions> _self) -> sem::DocumentOptions::BrokenLinks { return _self.id->brokenLinks; },
                  [](sem::DefaultSemId<sem::DocumentOptions> _self, sem::DocumentOptions::BrokenLinks brokenLinks) { _self.id->brokenLinks = brokenLinks; })
    .def_property("initialVisibility",
                  [](sem::DefaultSemId<sem::DocumentOptions> _self) -> sem::DocumentOptions::Visibility { return _self.id->initialVisibility; },
                  [](sem::DefaultSemId<sem::DocumentOptions> _self, sem::DocumentOptions::Visibility initialVisibility) { _self.id->initialVisibility = initialVisibility; })
    .def_property("tocExport",
                  [](sem::DefaultSemId<sem::DocumentOptions> _self) -> sem::DocumentOptions::TocExport { return _self.id->tocExport; },
                  [](sem::DefaultSemId<sem::DocumentOptions> _self, sem::DocumentOptions::TocExport tocExport) { _self.id->tocExport = tocExport; })
    .def_property("properties",
                  [](sem::DefaultSemId<sem::DocumentOptions> _self) -> Vec<sem::Subtree::Property> { return _self.id->properties; },
                  [](sem::DefaultSemId<sem::DocumentOptions> _self, Vec<sem::Subtree::Property> properties) { _self.id->properties = properties; })
    .def_property("smartQuotes",
                  [](sem::DefaultSemId<sem::DocumentOptions> _self) -> bool { return _self.id->smartQuotes; },
                  [](sem::DefaultSemId<sem::DocumentOptions> _self, bool smartQuotes) { _self.id->smartQuotes = smartQuotes; })
    .def_property("emphasizedText",
                  [](sem::DefaultSemId<sem::DocumentOptions> _self) -> bool { return _self.id->emphasizedText; },
                  [](sem::DefaultSemId<sem::DocumentOptions> _self, bool emphasizedText) { _self.id->emphasizedText = emphasizedText; })
    .def_property("specialStrings",
                  [](sem::DefaultSemId<sem::DocumentOptions> _self) -> bool { return _self.id->specialStrings; },
                  [](sem::DefaultSemId<sem::DocumentOptions> _self, bool specialStrings) { _self.id->specialStrings = specialStrings; })
    .def_property("fixedWidthSections",
                  [](sem::DefaultSemId<sem::DocumentOptions> _self) -> bool { return _self.id->fixedWidthSections; },
                  [](sem::DefaultSemId<sem::DocumentOptions> _self, bool fixedWidthSections) { _self.id->fixedWidthSections = fixedWidthSections; })
    .def_property("includeTimestamps",
                  [](sem::DefaultSemId<sem::DocumentOptions> _self) -> bool { return _self.id->includeTimestamps; },
                  [](sem::DefaultSemId<sem::DocumentOptions> _self, bool includeTimestamps) { _self.id->includeTimestamps = includeTimestamps; })
    .def_property("preserveLineBreaks",
                  [](sem::DefaultSemId<sem::DocumentOptions> _self) -> bool { return _self.id->preserveLineBreaks; },
                  [](sem::DefaultSemId<sem::DocumentOptions> _self, bool preserveLineBreaks) { _self.id->preserveLineBreaks = preserveLineBreaks; })
    .def_property("plaintextSubscripts",
                  [](sem::DefaultSemId<sem::DocumentOptions> _self) -> bool { return _self.id->plaintextSubscripts; },
                  [](sem::DefaultSemId<sem::DocumentOptions> _self, bool plaintextSubscripts) { _self.id->plaintextSubscripts = plaintextSubscripts; })
    .def_property("exportArchived",
                  [](sem::DefaultSemId<sem::DocumentOptions> _self) -> bool { return _self.id->exportArchived; },
                  [](sem::DefaultSemId<sem::DocumentOptions> _self, bool exportArchived) { _self.id->exportArchived = exportArchived; })
    .def_property("exportWithAuthor",
                  [](sem::DefaultSemId<sem::DocumentOptions> _self) -> bool { return _self.id->exportWithAuthor; },
                  [](sem::DefaultSemId<sem::DocumentOptions> _self, bool exportWithAuthor) { _self.id->exportWithAuthor = exportWithAuthor; })
    .def_property("exportBrokenLinks",
                  [](sem::DefaultSemId<sem::DocumentOptions> _self) -> bool { return _self.id->exportBrokenLinks; },
                  [](sem::DefaultSemId<sem::DocumentOptions> _self, bool exportBrokenLinks) { _self.id->exportBrokenLinks = exportBrokenLinks; })
    .def_property("exportWithClock",
                  [](sem::DefaultSemId<sem::DocumentOptions> _self) -> bool { return _self.id->exportWithClock; },
                  [](sem::DefaultSemId<sem::DocumentOptions> _self, bool exportWithClock) { _self.id->exportWithClock = exportWithClock; })
    .def_property("exportWithCreator",
                  [](sem::DefaultSemId<sem::DocumentOptions> _self) -> bool { return _self.id->exportWithCreator; },
                  [](sem::DefaultSemId<sem::DocumentOptions> _self, bool exportWithCreator) { _self.id->exportWithCreator = exportWithCreator; })
    .def("getKind",
         [](sem::DefaultSemId<sem::DocumentOptions> _self) -> OrgSemKind { return _self.id->getKind(); })
    .def("getProperties",
         [](sem::DefaultSemId<sem::DocumentOptions> _self, sem::Subtree::Property::Kind kind, Str const& subKind) -> Vec<sem::Subtree::Property> { return _self.id->getProperties(kind, subKind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", ""))
    .def("getProperty",
         [](sem::DefaultSemId<sem::DocumentOptions> _self, sem::Subtree::Property::Kind kind, Str const& subKind) -> Opt<sem::Subtree::Property> { return _self.id->getProperty(kind, subKind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", ""))
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
  pybind11::class_<sem::DefaultSemId<sem::DocumentGroup>>(m, "DocumentGroup")
    .def(pybind11::init<>())
    .def("getKind",
         [](sem::DefaultSemId<sem::DocumentGroup> _self) -> OrgSemKind { return _self.id->getKind(); })
    ;
  #ifndef IN_CLANGD_PROCESSING
    #define PY_HAXORG_COMPILING
    #include "pyhaxorg_manual_wrap.hpp"
  #endif
  pybind11::class_<OrgExporterJson>(m, "OrgExporterJson")
    .def(pybind11::init<>())
    .def("visitNode",
         &OrgExporterJson::visitNode,
         pybind11::arg("node"),
         R"RAW(Visit top-level node of the exporter, filling in the internal
return state.)RAW")
    .def("exportToString",
         &OrgExporterJson::exportToString)
    .def("exportToFile",
         &OrgExporterJson::exportToFile,
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
         &OrgExporterTree::toString,
         pybind11::arg("node"),
         pybind11::arg("opts"))
    .def("toFile",
         &OrgExporterTree::toFile,
         pybind11::arg("node"),
         pybind11::arg("path"),
         pybind11::arg("opts"))
    ;
  pybind11::class_<OrgExporterYaml>(m, "OrgExporterYaml")
    .def(pybind11::init<>())
    .def("visitNode",
         &OrgExporterYaml::visitNode,
         pybind11::arg("node"),
         R"RAW(Visit top-level node of the exporter, filling in the internal
return state.)RAW")
    .def("exportToString",
         &OrgExporterYaml::exportToString)
    .def("exportToFile",
         &OrgExporterYaml::exportToFile,
         pybind11::arg("path"))
    ;
  pybind11::class_<OrgContext>(m, "OrgContext")
    .def(pybind11::init<>())
    .def("initLocationResolvers",
         &OrgContext::initLocationResolvers)
    .def("run",
         &OrgContext::run,
         pybind11::arg("file"))
    .def("getNode",
         &OrgContext::getNode)
    ;
}