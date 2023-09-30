#undef slots
#include <pybind11/pybind11.h>
#include <sem/SemOrg.hpp>
#include <pybind11/stl.h>
#ifndef IN_CLANGD_PROCESSING
  #define PY_HAXORG_COMPILING
  #include "pyhaxorg_manual_impl.hpp"
#endif
PYBIND11_MODULE(pyhaxorg, m) {
  pybind11::class_<TypedPySemId<sem::Stmt>, PySemId>(m, "SemStmt")
    .def(pybind11::init<>())
    .def_property("attached",
                  [](TypedPySemId<sem::Stmt> _self) -> Vec<sem::SemId> { return _self.as<sem::Stmt>()->attached; },
                  [](TypedPySemId<sem::Stmt> _self, Vec<sem::SemId> attached) { _self.as<sem::Stmt>()->attached = attached; })
    .def("getAttached",
         [](TypedPySemId<sem::Stmt> _self, OrgSemKind kind) -> Opt<sem::SemId> { return _self.as<sem::Stmt>()->getAttached(kind); },
         pybind11::arg("kind"))
    ;
  pybind11::class_<TypedPySemId<sem::Inline>, PySemId>(m, "SemInline")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::StmtList>, PySemId>(m, "SemStmtList")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Empty>, PySemId>(m, "SemEmpty")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Row>, PySemId>(m, "SemRow")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Table>, PySemId>(m, "SemTable")
    .def(pybind11::init<>())
    .def_property("rows",
                  [](TypedPySemId<sem::Table> _self) -> Vec<sem::SemIdT<sem::Row>> { return _self.as<sem::Table>()->rows; },
                  [](TypedPySemId<sem::Table> _self, Vec<sem::SemIdT<sem::Row>> rows) { _self.as<sem::Table>()->rows = rows; })
    ;
  pybind11::class_<TypedPySemId<sem::HashTag>, PySemId>(m, "SemHashTag")
    .def(pybind11::init<>())
    .def_property("head",
                  [](TypedPySemId<sem::HashTag> _self) -> Str { return _self.as<sem::HashTag>()->head; },
                  [](TypedPySemId<sem::HashTag> _self, Str head) { _self.as<sem::HashTag>()->head = head; })
    .def_property("subtags",
                  [](TypedPySemId<sem::HashTag> _self) -> Vec<sem::SemIdT<sem::HashTag>> { return _self.as<sem::HashTag>()->subtags; },
                  [](TypedPySemId<sem::HashTag> _self, Vec<sem::SemIdT<sem::HashTag>> subtags) { _self.as<sem::HashTag>()->subtags = subtags; })
    .def("prefixMatch",
         [](TypedPySemId<sem::HashTag> _self, Vec<Str> const& prefix) -> bool { return _self.as<sem::HashTag>()->prefixMatch(prefix); },
         pybind11::arg("prefix"),
         R"RAW(Check if list of tag names is a prefix for either of the nested hash tags in this one)RAW")
    ;
  pybind11::class_<TypedPySemId<sem::Footnote>, PySemId>(m, "SemFootnote")
    .def(pybind11::init<>())
    .def_property("tag",
                  [](TypedPySemId<sem::Footnote> _self) -> Str { return _self.as<sem::Footnote>()->tag; },
                  [](TypedPySemId<sem::Footnote> _self, Str tag) { _self.as<sem::Footnote>()->tag = tag; })
    .def_property("definition",
                  [](TypedPySemId<sem::Footnote> _self) -> Opt<sem::SemId> { return _self.as<sem::Footnote>()->definition; },
                  [](TypedPySemId<sem::Footnote> _self, Opt<sem::SemId> definition) { _self.as<sem::Footnote>()->definition = definition; })
    ;
  pybind11::class_<TypedPySemId<sem::Completion>, PySemId>(m, "SemCompletion")
    .def(pybind11::init<>())
    .def_property("done",
                  [](TypedPySemId<sem::Completion> _self) -> int { return _self.as<sem::Completion>()->done; },
                  [](TypedPySemId<sem::Completion> _self, int done) { _self.as<sem::Completion>()->done = done; })
    .def_property("full",
                  [](TypedPySemId<sem::Completion> _self) -> int { return _self.as<sem::Completion>()->full; },
                  [](TypedPySemId<sem::Completion> _self, int full) { _self.as<sem::Completion>()->full = full; })
    .def_property("isPercent",
                  [](TypedPySemId<sem::Completion> _self) -> bool { return _self.as<sem::Completion>()->isPercent; },
                  [](TypedPySemId<sem::Completion> _self, bool isPercent) { _self.as<sem::Completion>()->isPercent = isPercent; })
    ;
  pybind11::class_<TypedPySemId<sem::Paragraph>, PySemId>(m, "SemParagraph")
    .def(pybind11::init<>())
    .def("isFootnoteDefinition",
         [](TypedPySemId<sem::Paragraph> _self) -> bool { return _self.as<sem::Paragraph>()->isFootnoteDefinition(); },
         R"RAW(Check if paragraph defines footnote)RAW")
    ;
  pybind11::class_<TypedPySemId<sem::Format>, PySemId>(m, "SemFormat")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Center>, PySemId>(m, "SemCenter")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Command>, PySemId>(m, "SemCommand")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::LineCommand>, PySemId>(m, "SemLineCommand")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Standalone>, PySemId>(m, "SemStandalone")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Attached>, PySemId>(m, "SemAttached")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Caption>, PySemId>(m, "SemCaption")
    .def(pybind11::init<>())
    .def_property("text",
                  [](TypedPySemId<sem::Caption> _self) -> sem::SemIdT<sem::Paragraph> { return _self.as<sem::Caption>()->text; },
                  [](TypedPySemId<sem::Caption> _self, sem::SemIdT<sem::Paragraph> text) { _self.as<sem::Caption>()->text = text; })
    ;
  pybind11::class_<TypedPySemId<sem::CommandGroup>, PySemId>(m, "SemCommandGroup")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Block>, PySemId>(m, "SemBlock")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Quote>, PySemId>(m, "SemQuote")
    .def(pybind11::init<>())
    .def_property("text",
                  [](TypedPySemId<sem::Quote> _self) -> sem::SemIdT<sem::Paragraph> { return _self.as<sem::Quote>()->text; },
                  [](TypedPySemId<sem::Quote> _self, sem::SemIdT<sem::Paragraph> text) { _self.as<sem::Quote>()->text = text; })
    ;
  pybind11::class_<TypedPySemId<sem::Example>, PySemId>(m, "SemExample")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::CmdArguments>, PySemId>(m, "SemCmdArguments")
    .def(pybind11::init<>())
    .def_property("positional",
                  [](TypedPySemId<sem::CmdArguments> _self) -> Vec<sem::SemIdT<sem::CmdArgument>> { return _self.as<sem::CmdArguments>()->positional; },
                  [](TypedPySemId<sem::CmdArguments> _self, Vec<sem::SemIdT<sem::CmdArgument>> positional) { _self.as<sem::CmdArguments>()->positional = positional; })
    .def_property("named",
                  [](TypedPySemId<sem::CmdArguments> _self) -> UnorderedMap<Str, sem::SemIdT<sem::CmdArgument>> { return _self.as<sem::CmdArguments>()->named; },
                  [](TypedPySemId<sem::CmdArguments> _self, UnorderedMap<Str, sem::SemIdT<sem::CmdArgument>> named) { _self.as<sem::CmdArguments>()->named = named; })
    .def("popArg",
         [](TypedPySemId<sem::CmdArguments> _self, Str key) -> Opt<sem::SemIdT<sem::CmdArgument>> { return _self.as<sem::CmdArguments>()->popArg(key); },
         pybind11::arg("key"),
         R"RAW(Remove argument value from the map and return it if present)RAW")
    ;
  pybind11::class_<TypedPySemId<sem::CmdArgument>, PySemId>(m, "SemCmdArgument")
    .def(pybind11::init<>())
    .def_property("key",
                  [](TypedPySemId<sem::CmdArgument> _self) -> Opt<Str> { return _self.as<sem::CmdArgument>()->key; },
                  [](TypedPySemId<sem::CmdArgument> _self, Opt<Str> key) { _self.as<sem::CmdArgument>()->key = key; })
    .def_property("value",
                  [](TypedPySemId<sem::CmdArgument> _self) -> Str { return _self.as<sem::CmdArgument>()->value; },
                  [](TypedPySemId<sem::CmdArgument> _self, Str value) { _self.as<sem::CmdArgument>()->value = value; })
    .def("getInt",
         [](TypedPySemId<sem::CmdArgument> _self) -> Opt<int> { return _self.as<sem::CmdArgument>()->getInt(); },
         R"RAW(Parse argument as integer value)RAW")
    .def("getBool",
         [](TypedPySemId<sem::CmdArgument> _self) -> Opt<bool> { return _self.as<sem::CmdArgument>()->getBool(); },
         R"RAW(Get argument as bool)RAW")
    .def("getString",
         [](TypedPySemId<sem::CmdArgument> _self) -> Str { return _self.as<sem::CmdArgument>()->getString(); },
         R"RAW(Get original string)RAW")
    ;
  pybind11::class_<TypedPySemId<sem::Export>, PySemId>(m, "SemExport")
    .def(pybind11::init<>())
    .def_property("format",
                  [](TypedPySemId<sem::Export> _self) -> sem::Export::Format { return _self.as<sem::Export>()->format; },
                  [](TypedPySemId<sem::Export> _self, sem::Export::Format format) { _self.as<sem::Export>()->format = format; })
    .def_property("exporter",
                  [](TypedPySemId<sem::Export> _self) -> Str { return _self.as<sem::Export>()->exporter; },
                  [](TypedPySemId<sem::Export> _self, Str exporter) { _self.as<sem::Export>()->exporter = exporter; })
    .def_property("parameters",
                  [](TypedPySemId<sem::Export> _self) -> sem::SemIdT<sem::CmdArguments> { return _self.as<sem::Export>()->parameters; },
                  [](TypedPySemId<sem::Export> _self, sem::SemIdT<sem::CmdArguments> parameters) { _self.as<sem::Export>()->parameters = parameters; })
    .def_property("placement",
                  [](TypedPySemId<sem::Export> _self) -> Opt<Str> { return _self.as<sem::Export>()->placement; },
                  [](TypedPySemId<sem::Export> _self, Opt<Str> placement) { _self.as<sem::Export>()->placement = placement; })
    .def_property("content",
                  [](TypedPySemId<sem::Export> _self) -> Str { return _self.as<sem::Export>()->content; },
                  [](TypedPySemId<sem::Export> _self, Str content) { _self.as<sem::Export>()->content = content; })
    ;
  pybind11::enum_<sem::Export::Format>(m, "ExportFormat")
    .value("Inline", sem::Export::Format::Inline, R"RAW(Export directly in the paragraph)RAW")
    .value("Line", sem::Export::Format::Line, R"RAW(Single line of export)RAW")
    .value("Block", sem::Export::Format::Block, R"RAW(Multiple lines of export)RAW")
    .export_values()
    ;
  pybind11::class_<TypedPySemId<sem::AdmonitionBlock>, PySemId>(m, "SemAdmonitionBlock")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Code>, PySemId>(m, "SemCode")
    .def(pybind11::init<>())
    .def_property("lang",
                  [](TypedPySemId<sem::Code> _self) -> Opt<Str> { return _self.as<sem::Code>()->lang; },
                  [](TypedPySemId<sem::Code> _self, Opt<Str> lang) { _self.as<sem::Code>()->lang = lang; })
    .def_property("switches",
                  [](TypedPySemId<sem::Code> _self) -> Vec<sem::Code::Switch> { return _self.as<sem::Code>()->switches; },
                  [](TypedPySemId<sem::Code> _self, Vec<sem::Code::Switch> switches) { _self.as<sem::Code>()->switches = switches; })
    .def_property("exports",
                  [](TypedPySemId<sem::Code> _self) -> sem::Code::Exports { return _self.as<sem::Code>()->exports; },
                  [](TypedPySemId<sem::Code> _self, sem::Code::Exports exports) { _self.as<sem::Code>()->exports = exports; })
    .def_property("parameters",
                  [](TypedPySemId<sem::Code> _self) -> sem::SemIdT<sem::CmdArguments> { return _self.as<sem::Code>()->parameters; },
                  [](TypedPySemId<sem::Code> _self, sem::SemIdT<sem::CmdArguments> parameters) { _self.as<sem::Code>()->parameters = parameters; })
    .def_property("cache",
                  [](TypedPySemId<sem::Code> _self) -> bool { return _self.as<sem::Code>()->cache; },
                  [](TypedPySemId<sem::Code> _self, bool cache) { _self.as<sem::Code>()->cache = cache; })
    .def_property("eval",
                  [](TypedPySemId<sem::Code> _self) -> bool { return _self.as<sem::Code>()->eval; },
                  [](TypedPySemId<sem::Code> _self, bool eval) { _self.as<sem::Code>()->eval = eval; })
    .def_property("noweb",
                  [](TypedPySemId<sem::Code> _self) -> bool { return _self.as<sem::Code>()->noweb; },
                  [](TypedPySemId<sem::Code> _self, bool noweb) { _self.as<sem::Code>()->noweb = noweb; })
    .def_property("hlines",
                  [](TypedPySemId<sem::Code> _self) -> bool { return _self.as<sem::Code>()->hlines; },
                  [](TypedPySemId<sem::Code> _self, bool hlines) { _self.as<sem::Code>()->hlines = hlines; })
    .def_property("tangle",
                  [](TypedPySemId<sem::Code> _self) -> bool { return _self.as<sem::Code>()->tangle; },
                  [](TypedPySemId<sem::Code> _self, bool tangle) { _self.as<sem::Code>()->tangle = tangle; })
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
  pybind11::class_<TypedPySemId<sem::Time>, PySemId>(m, "SemTime")
    .def(pybind11::init<>())
    .def_property("isActive",
                  [](TypedPySemId<sem::Time> _self) -> bool { return _self.as<sem::Time>()->isActive; },
                  [](TypedPySemId<sem::Time> _self, bool isActive) { _self.as<sem::Time>()->isActive = isActive; })
    ;
  pybind11::class_<sem::Time::Repeat>(m, "TimeRepeat")
    .def(pybind11::init<>())
    .def_readwrite("mode", &sem::Time::Repeat::mode, "mode")
    .def_readwrite("period", &sem::Time::Repeat::period, "period")
    .def_readwrite("count", &sem::Time::Repeat::count, "count")
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
  pybind11::class_<TypedPySemId<sem::TimeRange>, PySemId>(m, "SemTimeRange")
    .def(pybind11::init<>())
    .def_property("from",
                  [](TypedPySemId<sem::TimeRange> _self) -> sem::SemIdT<sem::Time> { return _self.as<sem::TimeRange>()->from; },
                  [](TypedPySemId<sem::TimeRange> _self, sem::SemIdT<sem::Time> from) { _self.as<sem::TimeRange>()->from = from; })
    .def_property("to",
                  [](TypedPySemId<sem::TimeRange> _self) -> sem::SemIdT<sem::Time> { return _self.as<sem::TimeRange>()->to; },
                  [](TypedPySemId<sem::TimeRange> _self, sem::SemIdT<sem::Time> to) { _self.as<sem::TimeRange>()->to = to; })
    ;
  pybind11::class_<TypedPySemId<sem::Macro>, PySemId>(m, "SemMacro")
    .def(pybind11::init<>())
    .def_property("name",
                  [](TypedPySemId<sem::Macro> _self) -> Str { return _self.as<sem::Macro>()->name; },
                  [](TypedPySemId<sem::Macro> _self, Str name) { _self.as<sem::Macro>()->name = name; })
    .def_property("arguments",
                  [](TypedPySemId<sem::Macro> _self) -> Vec<Str> { return _self.as<sem::Macro>()->arguments; },
                  [](TypedPySemId<sem::Macro> _self, Vec<Str> arguments) { _self.as<sem::Macro>()->arguments = arguments; })
    ;
  pybind11::class_<TypedPySemId<sem::Symbol>, PySemId>(m, "SemSymbol")
    .def(pybind11::init<>())
    .def_property("name",
                  [](TypedPySemId<sem::Symbol> _self) -> Str { return _self.as<sem::Symbol>()->name; },
                  [](TypedPySemId<sem::Symbol> _self, Str name) { _self.as<sem::Symbol>()->name = name; })
    .def_property("parameters",
                  [](TypedPySemId<sem::Symbol> _self) -> Vec<sem::Symbol::Param> { return _self.as<sem::Symbol>()->parameters; },
                  [](TypedPySemId<sem::Symbol> _self, Vec<sem::Symbol::Param> parameters) { _self.as<sem::Symbol>()->parameters = parameters; })
    .def_property("positional",
                  [](TypedPySemId<sem::Symbol> _self) -> Vec<sem::SemId> { return _self.as<sem::Symbol>()->positional; },
                  [](TypedPySemId<sem::Symbol> _self, Vec<sem::SemId> positional) { _self.as<sem::Symbol>()->positional = positional; })
    ;
  pybind11::class_<sem::Symbol::Param>(m, "SymbolParam")
    .def(pybind11::init<>())
    .def_readwrite("key", &sem::Symbol::Param::key, "Key -- for non-positional")
    .def_readwrite("value", &sem::Symbol::Param::value, "Uninterpreted value")
    ;
  pybind11::class_<TypedPySemId<sem::SubtreeLog>, PySemId>(m, "SemSubtreeLog")
    .def(pybind11::init<>())
    .def("setDescription",
         [](TypedPySemId<sem::SubtreeLog> _self, sem::SemIdT<sem::StmtList> desc) -> void { return _self.as<sem::SubtreeLog>()->setDescription(desc); },
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
  pybind11::class_<TypedPySemId<sem::Subtree>, PySemId>(m, "SemSubtree")
    .def(pybind11::init<>())
    .def_property("level",
                  [](TypedPySemId<sem::Subtree> _self) -> int { return _self.as<sem::Subtree>()->level; },
                  [](TypedPySemId<sem::Subtree> _self, int level) { _self.as<sem::Subtree>()->level = level; })
    .def_property("treeId",
                  [](TypedPySemId<sem::Subtree> _self) -> Opt<Str> { return _self.as<sem::Subtree>()->treeId; },
                  [](TypedPySemId<sem::Subtree> _self, Opt<Str> treeId) { _self.as<sem::Subtree>()->treeId = treeId; })
    .def_property("todo",
                  [](TypedPySemId<sem::Subtree> _self) -> Opt<Str> { return _self.as<sem::Subtree>()->todo; },
                  [](TypedPySemId<sem::Subtree> _self, Opt<Str> todo) { _self.as<sem::Subtree>()->todo = todo; })
    .def_property("completion",
                  [](TypedPySemId<sem::Subtree> _self) -> Opt<sem::SemIdT<sem::Completion>> { return _self.as<sem::Subtree>()->completion; },
                  [](TypedPySemId<sem::Subtree> _self, Opt<sem::SemIdT<sem::Completion>> completion) { _self.as<sem::Subtree>()->completion = completion; })
    .def_property("description",
                  [](TypedPySemId<sem::Subtree> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self.as<sem::Subtree>()->description; },
                  [](TypedPySemId<sem::Subtree> _self, Opt<sem::SemIdT<sem::Paragraph>> description) { _self.as<sem::Subtree>()->description = description; })
    .def_property("tags",
                  [](TypedPySemId<sem::Subtree> _self) -> Vec<sem::SemIdT<sem::HashTag>> { return _self.as<sem::Subtree>()->tags; },
                  [](TypedPySemId<sem::Subtree> _self, Vec<sem::SemIdT<sem::HashTag>> tags) { _self.as<sem::Subtree>()->tags = tags; })
    .def_property("title",
                  [](TypedPySemId<sem::Subtree> _self) -> sem::SemIdT<sem::Paragraph> { return _self.as<sem::Subtree>()->title; },
                  [](TypedPySemId<sem::Subtree> _self, sem::SemIdT<sem::Paragraph> title) { _self.as<sem::Subtree>()->title = title; })
    .def_property("logbook",
                  [](TypedPySemId<sem::Subtree> _self) -> Vec<sem::SemIdT<sem::SubtreeLog>> { return _self.as<sem::Subtree>()->logbook; },
                  [](TypedPySemId<sem::Subtree> _self, Vec<sem::SemIdT<sem::SubtreeLog>> logbook) { _self.as<sem::Subtree>()->logbook = logbook; })
    .def_property("properties",
                  [](TypedPySemId<sem::Subtree> _self) -> Vec<sem::Subtree::Property> { return _self.as<sem::Subtree>()->properties; },
                  [](TypedPySemId<sem::Subtree> _self, Vec<sem::Subtree::Property> properties) { _self.as<sem::Subtree>()->properties = properties; })
    .def_property("closed",
                  [](TypedPySemId<sem::Subtree> _self) -> Opt<sem::SemIdT<sem::Time>> { return _self.as<sem::Subtree>()->closed; },
                  [](TypedPySemId<sem::Subtree> _self, Opt<sem::SemIdT<sem::Time>> closed) { _self.as<sem::Subtree>()->closed = closed; })
    .def_property("deadline",
                  [](TypedPySemId<sem::Subtree> _self) -> Opt<sem::SemIdT<sem::Time>> { return _self.as<sem::Subtree>()->deadline; },
                  [](TypedPySemId<sem::Subtree> _self, Opt<sem::SemIdT<sem::Time>> deadline) { _self.as<sem::Subtree>()->deadline = deadline; })
    .def_property("scheduled",
                  [](TypedPySemId<sem::Subtree> _self) -> Opt<sem::SemIdT<sem::Time>> { return _self.as<sem::Subtree>()->scheduled; },
                  [](TypedPySemId<sem::Subtree> _self, Opt<sem::SemIdT<sem::Time>> scheduled) { _self.as<sem::Subtree>()->scheduled = scheduled; })
    .def("getTimePeriods",
         [](TypedPySemId<sem::Subtree> _self, IntSet<sem::Subtree::Period::Kind> kinds) -> Vec<sem::Subtree::Period> { return _self.as<sem::Subtree>()->getTimePeriods(kinds); },
         pybind11::arg("kinds"))
    .def("getProperties",
         [](TypedPySemId<sem::Subtree> _self, sem::Subtree::Property::Kind kind, Str const& subkind) -> Vec<sem::Subtree::Property> { return _self.as<sem::Subtree>()->getProperties(kind, subkind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", ""))
    .def("getProperty",
         [](TypedPySemId<sem::Subtree> _self, sem::Subtree::Property::Kind kind, Str const& subkind) -> Opt<sem::Subtree::Property> { return _self.as<sem::Subtree>()->getProperty(kind, subkind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", ""))
    .def("getContextualProperties",
         [](TypedPySemId<sem::Subtree> _self, sem::Subtree::Property::Kind kind, Str const& subkind) -> Vec<sem::Subtree::Property> { return _self.as<sem::Subtree>()->getContextualProperties(kind, subkind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", ""))
    .def("getContextualProperty",
         [](TypedPySemId<sem::Subtree> _self, sem::Subtree::Property::Kind kind, Str const& subkind) -> Opt<sem::Subtree::Property> { return _self.as<sem::Subtree>()->getContextualProperty(kind, subkind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", ""))
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
  pybind11::class_<TypedPySemId<sem::LatexBody>, PySemId>(m, "SemLatexBody")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::InlineMath>, PySemId>(m, "SemInlineMath")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Leaf>, PySemId>(m, "SemLeaf")
    .def(pybind11::init<>())
    .def_property("text",
                  [](TypedPySemId<sem::Leaf> _self) -> Str { return _self.as<sem::Leaf>()->text; },
                  [](TypedPySemId<sem::Leaf> _self, Str text) { _self.as<sem::Leaf>()->text = text; })
    ;
  pybind11::class_<TypedPySemId<sem::Escaped>, PySemId>(m, "SemEscaped")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Newline>, PySemId>(m, "SemNewline")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Space>, PySemId>(m, "SemSpace")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Word>, PySemId>(m, "SemWord")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::AtMention>, PySemId>(m, "SemAtMention")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::RawText>, PySemId>(m, "SemRawText")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Punctuation>, PySemId>(m, "SemPunctuation")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Placeholder>, PySemId>(m, "SemPlaceholder")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::BigIdent>, PySemId>(m, "SemBigIdent")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Markup>, PySemId>(m, "SemMarkup")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Bold>, PySemId>(m, "SemBold")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Underline>, PySemId>(m, "SemUnderline")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Monospace>, PySemId>(m, "SemMonospace")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::MarkQuote>, PySemId>(m, "SemMarkQuote")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Verbatim>, PySemId>(m, "SemVerbatim")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Italic>, PySemId>(m, "SemItalic")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Strike>, PySemId>(m, "SemStrike")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Par>, PySemId>(m, "SemPar")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::List>, PySemId>(m, "SemList")
    .def(pybind11::init<>())
    .def("isDescriptionList",
         [](TypedPySemId<sem::List> _self) -> bool { return _self.as<sem::List>()->isDescriptionList(); })
    ;
  pybind11::class_<TypedPySemId<sem::ListItem>, PySemId>(m, "SemListItem")
    .def(pybind11::init<>())
    .def_property("checkbox",
                  [](TypedPySemId<sem::ListItem> _self) -> sem::ListItem::Checkbox { return _self.as<sem::ListItem>()->checkbox; },
                  [](TypedPySemId<sem::ListItem> _self, sem::ListItem::Checkbox checkbox) { _self.as<sem::ListItem>()->checkbox = checkbox; })
    .def_property("header",
                  [](TypedPySemId<sem::ListItem> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self.as<sem::ListItem>()->header; },
                  [](TypedPySemId<sem::ListItem> _self, Opt<sem::SemIdT<sem::Paragraph>> header) { _self.as<sem::ListItem>()->header = header; })
    .def("isDescriptionItem",
         [](TypedPySemId<sem::ListItem> _self) -> bool { return _self.as<sem::ListItem>()->isDescriptionItem(); })
    ;
  pybind11::enum_<sem::ListItem::Checkbox>(m, "ListItemCheckbox")
    .value("None", sem::ListItem::Checkbox::None)
    .value("Done", sem::ListItem::Checkbox::Done)
    .value("Empty", sem::ListItem::Checkbox::Empty)
    .export_values()
    ;
  pybind11::class_<TypedPySemId<sem::Link>, PySemId>(m, "SemLink")
    .def(pybind11::init<>())
    .def_property("description",
                  [](TypedPySemId<sem::Link> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self.as<sem::Link>()->description; },
                  [](TypedPySemId<sem::Link> _self, Opt<sem::SemIdT<sem::Paragraph>> description) { _self.as<sem::Link>()->description = description; })
    .def("resolve",
         [](TypedPySemId<sem::Link> _self, sem::Document const& doc) -> Opt<sem::SemId> { return _self.as<sem::Link>()->resolve(doc); },
         pybind11::arg("doc"))
    .def("resolve",
         [](TypedPySemId<sem::Link> _self) -> Opt<sem::SemId> { return _self.as<sem::Link>()->resolve(); })
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
  pybind11::class_<TypedPySemId<sem::Document>, PySemId>(m, "SemDocument")
    .def(pybind11::init<>())
    .def_property("idTable",
                  [](TypedPySemId<sem::Document> _self) -> UnorderedMap<Str, sem::SemId> { return _self.as<sem::Document>()->idTable; },
                  [](TypedPySemId<sem::Document> _self, UnorderedMap<Str, sem::SemId> idTable) { _self.as<sem::Document>()->idTable = idTable; })
    .def_property("nameTable",
                  [](TypedPySemId<sem::Document> _self) -> UnorderedMap<Str, sem::SemId> { return _self.as<sem::Document>()->nameTable; },
                  [](TypedPySemId<sem::Document> _self, UnorderedMap<Str, sem::SemId> nameTable) { _self.as<sem::Document>()->nameTable = nameTable; })
    .def_property("footnoteTable",
                  [](TypedPySemId<sem::Document> _self) -> UnorderedMap<Str, sem::SemId> { return _self.as<sem::Document>()->footnoteTable; },
                  [](TypedPySemId<sem::Document> _self, UnorderedMap<Str, sem::SemId> footnoteTable) { _self.as<sem::Document>()->footnoteTable = footnoteTable; })
    .def_property("anchorTable",
                  [](TypedPySemId<sem::Document> _self) -> UnorderedMap<Str, sem::SemId> { return _self.as<sem::Document>()->anchorTable; },
                  [](TypedPySemId<sem::Document> _self, UnorderedMap<Str, sem::SemId> anchorTable) { _self.as<sem::Document>()->anchorTable = anchorTable; })
    .def_property("title",
                  [](TypedPySemId<sem::Document> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self.as<sem::Document>()->title; },
                  [](TypedPySemId<sem::Document> _self, Opt<sem::SemIdT<sem::Paragraph>> title) { _self.as<sem::Document>()->title = title; })
    .def_property("author",
                  [](TypedPySemId<sem::Document> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self.as<sem::Document>()->author; },
                  [](TypedPySemId<sem::Document> _self, Opt<sem::SemIdT<sem::Paragraph>> author) { _self.as<sem::Document>()->author = author; })
    .def_property("creator",
                  [](TypedPySemId<sem::Document> _self) -> Opt<sem::SemIdT<sem::Paragraph>> { return _self.as<sem::Document>()->creator; },
                  [](TypedPySemId<sem::Document> _self, Opt<sem::SemIdT<sem::Paragraph>> creator) { _self.as<sem::Document>()->creator = creator; })
    .def_property("email",
                  [](TypedPySemId<sem::Document> _self) -> Opt<sem::SemIdT<sem::RawText>> { return _self.as<sem::Document>()->email; },
                  [](TypedPySemId<sem::Document> _self, Opt<sem::SemIdT<sem::RawText>> email) { _self.as<sem::Document>()->email = email; })
    .def_property("language",
                  [](TypedPySemId<sem::Document> _self) -> Opt<Vec<Str>> { return _self.as<sem::Document>()->language; },
                  [](TypedPySemId<sem::Document> _self, Opt<Vec<Str>> language) { _self.as<sem::Document>()->language = language; })
    .def_property("options",
                  [](TypedPySemId<sem::Document> _self) -> sem::SemIdT<sem::DocumentOptions> { return _self.as<sem::Document>()->options; },
                  [](TypedPySemId<sem::Document> _self, sem::SemIdT<sem::DocumentOptions> options) { _self.as<sem::Document>()->options = options; })
    .def_property("exportFileName",
                  [](TypedPySemId<sem::Document> _self) -> Opt<Str> { return _self.as<sem::Document>()->exportFileName; },
                  [](TypedPySemId<sem::Document> _self, Opt<Str> exportFileName) { _self.as<sem::Document>()->exportFileName = exportFileName; })
    .def("resolve",
         [](TypedPySemId<sem::Document> _self, sem::SemId const& node) -> Opt<sem::SemId> { return _self.as<sem::Document>()->resolve(node); },
         pybind11::arg("node"))
    .def("getSubtree",
         [](TypedPySemId<sem::Document> _self, Str const& id) -> Opt<sem::SemIdT<sem::Subtree>> { return _self.as<sem::Document>()->getSubtree(id); },
         pybind11::arg("id"))
    .def("getProperties",
         [](TypedPySemId<sem::Document> _self, sem::Subtree::Property::Kind kind, Str const& subKind) -> Vec<sem::Subtree::Property> { return _self.as<sem::Document>()->getProperties(kind, subKind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", ""))
    .def("getProperty",
         [](TypedPySemId<sem::Document> _self, sem::Subtree::Property::Kind kind, Str const& subKind) -> Opt<sem::Subtree::Property> { return _self.as<sem::Document>()->getProperty(kind, subKind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", ""))
    ;
  pybind11::class_<TypedPySemId<sem::ParseError>, PySemId>(m, "SemParseError")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::FileTarget>, PySemId>(m, "SemFileTarget")
    .def(pybind11::init<>())
    .def_property("path",
                  [](TypedPySemId<sem::FileTarget> _self) -> Str { return _self.as<sem::FileTarget>()->path; },
                  [](TypedPySemId<sem::FileTarget> _self, Str path) { _self.as<sem::FileTarget>()->path = path; })
    .def_property("line",
                  [](TypedPySemId<sem::FileTarget> _self) -> Opt<int> { return _self.as<sem::FileTarget>()->line; },
                  [](TypedPySemId<sem::FileTarget> _self, Opt<int> line) { _self.as<sem::FileTarget>()->line = line; })
    .def_property("searchTarget",
                  [](TypedPySemId<sem::FileTarget> _self) -> Opt<Str> { return _self.as<sem::FileTarget>()->searchTarget; },
                  [](TypedPySemId<sem::FileTarget> _self, Opt<Str> searchTarget) { _self.as<sem::FileTarget>()->searchTarget = searchTarget; })
    .def_property("restrictToHeadlines",
                  [](TypedPySemId<sem::FileTarget> _self) -> bool { return _self.as<sem::FileTarget>()->restrictToHeadlines; },
                  [](TypedPySemId<sem::FileTarget> _self, bool restrictToHeadlines) { _self.as<sem::FileTarget>()->restrictToHeadlines = restrictToHeadlines; })
    .def_property("targetId",
                  [](TypedPySemId<sem::FileTarget> _self) -> Opt<Str> { return _self.as<sem::FileTarget>()->targetId; },
                  [](TypedPySemId<sem::FileTarget> _self, Opt<Str> targetId) { _self.as<sem::FileTarget>()->targetId = targetId; })
    .def_property("regexp",
                  [](TypedPySemId<sem::FileTarget> _self) -> Opt<Str> { return _self.as<sem::FileTarget>()->regexp; },
                  [](TypedPySemId<sem::FileTarget> _self, Opt<Str> regexp) { _self.as<sem::FileTarget>()->regexp = regexp; })
    ;
  pybind11::class_<TypedPySemId<sem::TextSeparator>, PySemId>(m, "SemTextSeparator")
    .def(pybind11::init<>())
    ;
  pybind11::class_<TypedPySemId<sem::Include>, PySemId>(m, "SemInclude")
    .def(pybind11::init<>())
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
  pybind11::class_<TypedPySemId<sem::DocumentOptions>, PySemId>(m, "SemDocumentOptions")
    .def(pybind11::init<>())
    .def_property("brokenLinks",
                  [](TypedPySemId<sem::DocumentOptions> _self) -> sem::DocumentOptions::BrokenLinks { return _self.as<sem::DocumentOptions>()->brokenLinks; },
                  [](TypedPySemId<sem::DocumentOptions> _self, sem::DocumentOptions::BrokenLinks brokenLinks) { _self.as<sem::DocumentOptions>()->brokenLinks = brokenLinks; })
    .def_property("initialVisibility",
                  [](TypedPySemId<sem::DocumentOptions> _self) -> sem::DocumentOptions::Visibility { return _self.as<sem::DocumentOptions>()->initialVisibility; },
                  [](TypedPySemId<sem::DocumentOptions> _self, sem::DocumentOptions::Visibility initialVisibility) { _self.as<sem::DocumentOptions>()->initialVisibility = initialVisibility; })
    .def_property("tocExport",
                  [](TypedPySemId<sem::DocumentOptions> _self) -> sem::DocumentOptions::TocExport { return _self.as<sem::DocumentOptions>()->tocExport; },
                  [](TypedPySemId<sem::DocumentOptions> _self, sem::DocumentOptions::TocExport tocExport) { _self.as<sem::DocumentOptions>()->tocExport = tocExport; })
    .def_property("properties",
                  [](TypedPySemId<sem::DocumentOptions> _self) -> Vec<sem::Subtree::Property> { return _self.as<sem::DocumentOptions>()->properties; },
                  [](TypedPySemId<sem::DocumentOptions> _self, Vec<sem::Subtree::Property> properties) { _self.as<sem::DocumentOptions>()->properties = properties; })
    .def_property("smartQuotes",
                  [](TypedPySemId<sem::DocumentOptions> _self) -> bool { return _self.as<sem::DocumentOptions>()->smartQuotes; },
                  [](TypedPySemId<sem::DocumentOptions> _self, bool smartQuotes) { _self.as<sem::DocumentOptions>()->smartQuotes = smartQuotes; })
    .def_property("emphasizedText",
                  [](TypedPySemId<sem::DocumentOptions> _self) -> bool { return _self.as<sem::DocumentOptions>()->emphasizedText; },
                  [](TypedPySemId<sem::DocumentOptions> _self, bool emphasizedText) { _self.as<sem::DocumentOptions>()->emphasizedText = emphasizedText; })
    .def_property("specialStrings",
                  [](TypedPySemId<sem::DocumentOptions> _self) -> bool { return _self.as<sem::DocumentOptions>()->specialStrings; },
                  [](TypedPySemId<sem::DocumentOptions> _self, bool specialStrings) { _self.as<sem::DocumentOptions>()->specialStrings = specialStrings; })
    .def_property("fixedWidthSections",
                  [](TypedPySemId<sem::DocumentOptions> _self) -> bool { return _self.as<sem::DocumentOptions>()->fixedWidthSections; },
                  [](TypedPySemId<sem::DocumentOptions> _self, bool fixedWidthSections) { _self.as<sem::DocumentOptions>()->fixedWidthSections = fixedWidthSections; })
    .def_property("includeTimestamps",
                  [](TypedPySemId<sem::DocumentOptions> _self) -> bool { return _self.as<sem::DocumentOptions>()->includeTimestamps; },
                  [](TypedPySemId<sem::DocumentOptions> _self, bool includeTimestamps) { _self.as<sem::DocumentOptions>()->includeTimestamps = includeTimestamps; })
    .def_property("preserveLineBreaks",
                  [](TypedPySemId<sem::DocumentOptions> _self) -> bool { return _self.as<sem::DocumentOptions>()->preserveLineBreaks; },
                  [](TypedPySemId<sem::DocumentOptions> _self, bool preserveLineBreaks) { _self.as<sem::DocumentOptions>()->preserveLineBreaks = preserveLineBreaks; })
    .def_property("plaintextSubscripts",
                  [](TypedPySemId<sem::DocumentOptions> _self) -> bool { return _self.as<sem::DocumentOptions>()->plaintextSubscripts; },
                  [](TypedPySemId<sem::DocumentOptions> _self, bool plaintextSubscripts) { _self.as<sem::DocumentOptions>()->plaintextSubscripts = plaintextSubscripts; })
    .def_property("exportArchived",
                  [](TypedPySemId<sem::DocumentOptions> _self) -> bool { return _self.as<sem::DocumentOptions>()->exportArchived; },
                  [](TypedPySemId<sem::DocumentOptions> _self, bool exportArchived) { _self.as<sem::DocumentOptions>()->exportArchived = exportArchived; })
    .def_property("exportWithAuthor",
                  [](TypedPySemId<sem::DocumentOptions> _self) -> bool { return _self.as<sem::DocumentOptions>()->exportWithAuthor; },
                  [](TypedPySemId<sem::DocumentOptions> _self, bool exportWithAuthor) { _self.as<sem::DocumentOptions>()->exportWithAuthor = exportWithAuthor; })
    .def_property("exportBrokenLinks",
                  [](TypedPySemId<sem::DocumentOptions> _self) -> bool { return _self.as<sem::DocumentOptions>()->exportBrokenLinks; },
                  [](TypedPySemId<sem::DocumentOptions> _self, bool exportBrokenLinks) { _self.as<sem::DocumentOptions>()->exportBrokenLinks = exportBrokenLinks; })
    .def_property("exportWithClock",
                  [](TypedPySemId<sem::DocumentOptions> _self) -> bool { return _self.as<sem::DocumentOptions>()->exportWithClock; },
                  [](TypedPySemId<sem::DocumentOptions> _self, bool exportWithClock) { _self.as<sem::DocumentOptions>()->exportWithClock = exportWithClock; })
    .def_property("exportWithCreator",
                  [](TypedPySemId<sem::DocumentOptions> _self) -> bool { return _self.as<sem::DocumentOptions>()->exportWithCreator; },
                  [](TypedPySemId<sem::DocumentOptions> _self, bool exportWithCreator) { _self.as<sem::DocumentOptions>()->exportWithCreator = exportWithCreator; })
    .def("getProperties",
         [](TypedPySemId<sem::DocumentOptions> _self, sem::Subtree::Property::Kind kind, Str const& subKind) -> Vec<sem::Subtree::Property> { return _self.as<sem::DocumentOptions>()->getProperties(kind, subKind); },
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", ""))
    .def("getProperty",
         [](TypedPySemId<sem::DocumentOptions> _self, sem::Subtree::Property::Kind kind, Str const& subKind) -> Opt<sem::Subtree::Property> { return _self.as<sem::DocumentOptions>()->getProperty(kind, subKind); },
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
  pybind11::class_<TypedPySemId<sem::DocumentGroup>, PySemId>(m, "SemDocumentGroup")
    .def(pybind11::init<>())
    ;
  pybind11::enum_<OrgSemPlacement>(m, "OrgSemPlacement")
    .value("TreeTitle", OrgSemPlacement::TreeTitle, R"RAW(Subtree title)RAW")
    .value("TreeBody", OrgSemPlacement::TreeBody, R"RAW(Inner content of the subtree)RAW")
    .value("LinkDescription", OrgSemPlacement::LinkDescription, R"RAW(Description paragraph for the link)RAW")
    .value("ListItemBody", OrgSemPlacement::ListItemBody, R"RAW(Statement list or inner content of the list item body)RAW")
    .value("ListItemDesc", OrgSemPlacement::ListItemDesc, R"RAW(Description part of the list item)RAW")
    .value("DocBody", OrgSemPlacement::DocBody, R"RAW(Toplevel document)RAW")
    .export_values()
    ;
  pybind11::enum_<OrgHorizontalDirection>(m, "OrgHorizontalDirection")
    .value("ohdNone", OrgHorizontalDirection::ohdNone, R"RAW(No specific positioning requirements)RAW")
    .value("ohdLeft", OrgHorizontalDirection::ohdLeft, R"RAW(Align to the left)RAW")
    .value("ohdRight", OrgHorizontalDirection::ohdRight, R"RAW(Align to the right)RAW")
    .value("ohdCenter", OrgHorizontalDirection::ohdCenter, R"RAW(Align to the center)RAW")
    .export_values()
    ;
  pybind11::enum_<OrgVerticalDirection>(m, "OrgVerticalDirection")
    .value("ovdNone", OrgVerticalDirection::ovdNone, R"RAW(No specific positioning)RAW")
    .value("ovdTop", OrgVerticalDirection::ovdTop, R"RAW(Align to the top)RAW")
    .value("ovdCenter", OrgVerticalDirection::ovdCenter, R"RAW(Center)RAW")
    .value("ovdBottom", OrgVerticalDirection::ovdBottom, R"RAW(Bottom)RAW")
    .export_values()
    ;
  pybind11::enum_<OrgSpecName>(m, "OrgSpecName")
    .value("Unnamed", OrgSpecName::Unnamed)
    .value("Result", OrgSpecName::Result)
    .value("Year", OrgSpecName::Year)
    .value("Day", OrgSpecName::Day)
    .value("Clock", OrgSpecName::Clock)
    .value("Repeater", OrgSpecName::Repeater)
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
    .value("SkipNewline", OrgNodeKind::SkipNewline)
    .value("SkipSpace", OrgNodeKind::SkipSpace)
    .value("SkipAny", OrgNodeKind::SkipAny)
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
    .value("PropertyList", OrgNodeKind::PropertyList)
    .value("Property", OrgNodeKind::Property, R"RAW(Property entry, either in `#+property:` command, or in `:property:` drawer)RAW")
    .value("Placeholder", OrgNodeKind::Placeholder, R"RAW(Placeholder entry in text, usually writte like `<text to replace>`)RAW")
    .value("SubtreeDescription", OrgNodeKind::SubtreeDescription, R"RAW(`:description:` entry)RAW")
    .value("SubtreeUrgency", OrgNodeKind::SubtreeUrgency)
    .value("Logbook", OrgNodeKind::Logbook, R"RAW(`:logbook:` entry storing note information)RAW")
    .value("LogbookEntry", OrgNodeKind::LogbookEntry)
    .value("LogbookStateChange", OrgNodeKind::LogbookStateChange, R"RAW(Annotation about change in the subtree todo state)RAW")
    .value("LogbookNote", OrgNodeKind::LogbookNote, R"RAW(Timestamped log note on the subtree)RAW")
    .value("LogbookClock", OrgNodeKind::LogbookClock, R"RAW(`CLOCK` entry in the subtree)RAW")
    .value("LogbookRefile", OrgNodeKind::LogbookRefile, R"RAW(`Refile` entry in the subtree logbook drawer)RAW")
    .value("LogbookPriority", OrgNodeKind::LogbookPriority, R"RAW(Change in the subtree priority)RAW")
    .value("LogbookPriorityChangeAction", OrgNodeKind::LogbookPriorityChangeAction, R"RAW(Action to change subtree)RAW")
    .value("LogbookReschedule", OrgNodeKind::LogbookReschedule)
    .value("LogbookTagChange", OrgNodeKind::LogbookTagChange)
    .value("LogbookTagChangeAction", OrgNodeKind::LogbookTagChangeAction)
    .value("RadioTarget", OrgNodeKind::RadioTarget, R"RAW(`<<<RADIO>>>`)RAW")
    .value("Target", OrgNodeKind::Target, R"RAW(`<<TARGET>>`)RAW")
    .export_values()
    ;
  pybind11::enum_<OrgTextContext>(m, "OrgTextContext")
    .value("otcPlain", OrgTextContext::otcPlain)
    .value("otcSubtree0", OrgTextContext::otcSubtree0)
    .value("otcSubtree1", OrgTextContext::otcSubtree1)
    .value("otcSubtree2", OrgTextContext::otcSubtree2)
    .value("otcSubtree3", OrgTextContext::otcSubtree3)
    .value("otcSubtree4", OrgTextContext::otcSubtree4)
    .value("otcSubtree5", OrgTextContext::otcSubtree5)
    .value("otcSubtree6", OrgTextContext::otcSubtree6)
    .value("otcSubtree7", OrgTextContext::otcSubtree7)
    .value("otcSubtree8", OrgTextContext::otcSubtree8)
    .value("otcSubtree9", OrgTextContext::otcSubtree9)
    .value("otcSubtree10", OrgTextContext::otcSubtree10)
    .value("otcSubtree11", OrgTextContext::otcSubtree11)
    .value("otcSubtree12", OrgTextContext::otcSubtree12)
    .value("otcSubtreeOther", OrgTextContext::otcSubtreeOther)
    .value("otcBold", OrgTextContext::otcBold)
    .value("otcItalic", OrgTextContext::otcItalic)
    .value("otcStrike", OrgTextContext::otcStrike)
    .value("otcUnderline", OrgTextContext::otcUnderline)
    .value("otcMonospaceInline", OrgTextContext::otcMonospaceInline)
    .value("otcMonospaceBlock", OrgTextContext::otcMonospaceBlock)
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
  pybind11::enum_<OrgTokenKind>(m, "OrgTokenKind")
    .value("None", OrgTokenKind::None)
    .value("Eof", OrgTokenKind::Eof)
    .value("GroupStart", OrgTokenKind::GroupStart, R"RAW(Start of the tokenizer token group)RAW")
    .value("GroupEnd", OrgTokenKind::GroupEnd, R"RAW(Tokenizer token group end)RAW")
    .value("ErrorTerminator", OrgTokenKind::ErrorTerminator)
    .value("CommandPrefix", OrgTokenKind::CommandPrefix)
    .value("LineCommand", OrgTokenKind::LineCommand)
    .value("CommandBegin", OrgTokenKind::CommandBegin, R"RAW(`#+begin` part of the multiline command. `begin_<block-type>` is split into two tokens - `begin_` prefix and `ockBegin<block-type>` section.)RAW")
    .value("CommandEnd", OrgTokenKind::CommandEnd)
    .value("DoubleColon", OrgTokenKind::DoubleColon)
    .value("Text", OrgTokenKind::Text)
    .value("StmtList", OrgTokenKind::StmtList, R"RAW(Unlexed group of statements - used in the list content to enable secondary parsing.)RAW")
    .value("StmtListOpen", OrgTokenKind::StmtListOpen, R"RAW(Start of the expanded statement list content)RAW")
    .value("StmtListClose", OrgTokenKind::StmtListClose, R"RAW(End of the expanded statement list content)RAW")
    .value("ListStart", OrgTokenKind::ListStart, R"RAW(Start of the list token group)RAW")
    .value("ListItemStart", OrgTokenKind::ListItemStart, R"RAW(Start of the list item element)RAW")
    .value("ListClock", OrgTokenKind::ListClock, R"RAW(`CLOCK:` entry at the start of the logbook entry list)RAW")
    .value("ListPlus", OrgTokenKind::ListPlus)
    .value("ListStar", OrgTokenKind::ListStar)
    .value("ListDescOpen", OrgTokenKind::ListDescOpen, R"RAW(Start of the description list key,)RAW")
    .value("ListDescClose", OrgTokenKind::ListDescClose, R"RAW(End of the description list key `::`)RAW")
    .value("ListItemEnd", OrgTokenKind::ListItemEnd, R"RAW(End of the list item)RAW")
    .value("ListEnd", OrgTokenKind::ListEnd, R"RAW(Complete end of the list token group)RAW")
    .value("Checkbox", OrgTokenKind::Checkbox, R"RAW(List or subtree checkbox)RAW")
    .value("SubtreeTodoState", OrgTokenKind::SubtreeTodoState)
    .value("SubtreeUrgency", OrgTokenKind::SubtreeUrgency, R"RAW(Subtree importance marker)RAW")
    .value("SubtreeCompletion", OrgTokenKind::SubtreeCompletion, R"RAW(Subtree completion marker)RAW")
    .value("SubtreeStars", OrgTokenKind::SubtreeStars, R"RAW(Subtree prefix)RAW")
    .value("SubtreeTagSeparator", OrgTokenKind::SubtreeTagSeparator)
    .value("SubtreeTime", OrgTokenKind::SubtreeTime)
    .value("SubtreeEnd", OrgTokenKind::SubtreeEnd)
    .value("ImplicitTime", OrgTokenKind::ImplicitTime, R"RAW(You can write time ranges without any additional formatting for
   subtrees that have a diary timestamps. For example, you have a
   complex date predicate, but event occurs for `18:00-21:00`, so you
   write it in the random place in the subtree.)RAW")
    .value("TimeDuration", OrgTokenKind::TimeDuration, R"RAW(Time duration for the `effort` property or time range length evaluation)RAW")
    .value("InactiveTimeBegin", OrgTokenKind::InactiveTimeBegin, R"RAW(Start of the inactive timestamp (`[2022-03-12]`))RAW")
    .value("InactiveTimeEnd", OrgTokenKind::InactiveTimeEnd)
    .value("ActiveTimeBegin", OrgTokenKind::ActiveTimeBegin, R"RAW(Start of the active timestamp `<2030-02-03>`)RAW")
    .value("ActiveTimeEnd", OrgTokenKind::ActiveTimeEnd)
    .value("DynamicTimeContent", OrgTokenKind::DynamicTimeContent, R"RAW(Dynamic time content)RAW")
    .value("StaticTimeDatePart", OrgTokenKind::StaticTimeDatePart, R"RAW(year-month-day part of the timestamp)RAW")
    .value("StaticTimeDayPart", OrgTokenKind::StaticTimeDayPart, R"RAW(weekday part of the timestamp)RAW")
    .value("StaticTimeClockPart", OrgTokenKind::StaticTimeClockPart, R"RAW(Clock part of the timestamp)RAW")
    .value("StaticTimeRepeater", OrgTokenKind::StaticTimeRepeater, R"RAW(Type of the time repeater: `+`, `++`, `.+`)RAW")
    .value("TimeDash", OrgTokenKind::TimeDash, R"RAW(Separator dash between two periods in the time range (`<start>--<finish.`))RAW")
    .value("TimeArrow", OrgTokenKind::TimeArrow, R"RAW(Time range evaluation arrow `[from]--[to] =>`)RAW")
    .value("Comment", OrgTokenKind::Comment, R"RAW(line or inline comment)RAW")
    .value("ListDoubleColon", OrgTokenKind::ListDoubleColon, R"RAW(Double colon between description list tag and body)RAW")
    .value("CommandArgumentsBegin", OrgTokenKind::CommandArgumentsBegin, R"RAW(List of command arguments)RAW")
    .value("CommandArgumentsEnd", OrgTokenKind::CommandArgumentsEnd, R"RAW(End of the command arguments list)RAW")
    .value("CommandKey", OrgTokenKind::CommandKey)
    .value("CommandValue", OrgTokenKind::CommandValue)
    .value("CommandFlag", OrgTokenKind::CommandFlag)
    .value("CommandBracket", OrgTokenKind::CommandBracket, R"RAW(`#+results[HASH...]`)RAW")
    .value("ColonLiteral", OrgTokenKind::ColonLiteral, R"RAW(Literal block with `:`)RAW")
    .value("ColonIdent", OrgTokenKind::ColonIdent, R"RAW(Drawer or source code block wrappers with colon-wrapped identifiers. `:results:`, `:end:` etc.)RAW")
    .value("ColonProperties", OrgTokenKind::ColonProperties, R"RAW(Start of the `:PROPERTIES:` block drawer block)RAW")
    .value("ColonDescription", OrgTokenKind::ColonDescription, R"RAW(Start of the `:description:` drawer block)RAW")
    .value("ColonEnd", OrgTokenKind::ColonEnd)
    .value("ColonLogbook", OrgTokenKind::ColonLogbook)
    .value("RawLogbook", OrgTokenKind::RawLogbook)
    .value("LogbookStart", OrgTokenKind::LogbookStart)
    .value("LogbookEnd", OrgTokenKind::LogbookEnd)
    .value("RawProperty", OrgTokenKind::RawProperty)
    .value("Link", OrgTokenKind::Link, R"RAW(Any kind of link)RAW")
    .value("CommandContentStart", OrgTokenKind::CommandContentStart)
    .value("CommandContentEnd", OrgTokenKind::CommandContentEnd)
    .value("CodeContent", OrgTokenKind::CodeContent, R"RAW(Block of code inside `#+begin_src`)RAW")
    .value("CodeContentBegin", OrgTokenKind::CodeContentBegin, R"RAW(Start of the expanded code content)RAW")
    .value("CodeContentEnd", OrgTokenKind::CodeContentEnd, R"RAW(End of the expanded code content)RAW")
    .value("CodeText", OrgTokenKind::CodeText, R"RAW(Uninterrupted text span without newlines - either a whole line or sub subsection of it if callout or tangle elements were detected)RAW")
    .value("TableContent", OrgTokenKind::TableContent, R"RAW(Block of text inside `#+table`)RAW")
    .value("QuoteContent", OrgTokenKind::QuoteContent, R"RAW(`#+quote` content)RAW")
    .value("BackendPass", OrgTokenKind::BackendPass, R"RAW(Backend-specific passthrough)RAW")
    .value("LogBook", OrgTokenKind::LogBook, R"RAW(Logbook including content)RAW")
    .value("Drawer", OrgTokenKind::Drawer, R"RAW(Drawer including content)RAW")
    .value("Indent", OrgTokenKind::Indent, R"RAW(Increase in indentation)RAW")
    .value("Dedent", OrgTokenKind::Dedent, R"RAW(Decrease in indentation)RAW")
    .value("SameIndent", OrgTokenKind::SameIndent)
    .value("NoIndent", OrgTokenKind::NoIndent)
    .value("BoldOpen", OrgTokenKind::BoldOpen)
    .value("BoldClose", OrgTokenKind::BoldClose)
    .value("BoldInline", OrgTokenKind::BoldInline)
    .value("BoldInlineOpen", OrgTokenKind::BoldInlineOpen)
    .value("BoldInlineClose", OrgTokenKind::BoldInlineClose)
    .value("ItalicOpen", OrgTokenKind::ItalicOpen)
    .value("ItalicClose", OrgTokenKind::ItalicClose)
    .value("ItalicInline", OrgTokenKind::ItalicInline)
    .value("ItalicInlineOpen", OrgTokenKind::ItalicInlineOpen)
    .value("ItalicInlineClose", OrgTokenKind::ItalicInlineClose)
    .value("VerbatimOpen", OrgTokenKind::VerbatimOpen)
    .value("VerbatimClose", OrgTokenKind::VerbatimClose)
    .value("VerbatimInline", OrgTokenKind::VerbatimInline)
    .value("VerbatimInlineOpen", OrgTokenKind::VerbatimInlineOpen)
    .value("VerbatimInlineClose", OrgTokenKind::VerbatimInlineClose)
    .value("MonospaceOpen", OrgTokenKind::MonospaceOpen)
    .value("MonospaceClose", OrgTokenKind::MonospaceClose)
    .value("MonospaceInline", OrgTokenKind::MonospaceInline)
    .value("MonospaceInlineOpen", OrgTokenKind::MonospaceInlineOpen)
    .value("MonospaceInlineClose", OrgTokenKind::MonospaceInlineClose)
    .value("BacktickOpen", OrgTokenKind::BacktickOpen)
    .value("BacktickClose", OrgTokenKind::BacktickClose)
    .value("BacktickInline", OrgTokenKind::BacktickInline)
    .value("BacktickInlineOpen", OrgTokenKind::BacktickInlineOpen)
    .value("BacktickInlineClose", OrgTokenKind::BacktickInlineClose)
    .value("UnderlineOpen", OrgTokenKind::UnderlineOpen)
    .value("UnderlineClose", OrgTokenKind::UnderlineClose)
    .value("UnderlineInline", OrgTokenKind::UnderlineInline)
    .value("UnderlineInlineOpen", OrgTokenKind::UnderlineInlineOpen)
    .value("UnderlineInlineClose", OrgTokenKind::UnderlineInlineClose)
    .value("StrikeOpen", OrgTokenKind::StrikeOpen)
    .value("StrikeClose", OrgTokenKind::StrikeClose)
    .value("StrikeInline", OrgTokenKind::StrikeInline)
    .value("StrikeInlineOpen", OrgTokenKind::StrikeInlineOpen)
    .value("StrikeInlineClose", OrgTokenKind::StrikeInlineClose)
    .value("QuoteOpen", OrgTokenKind::QuoteOpen)
    .value("QuoteClose", OrgTokenKind::QuoteClose)
    .value("Punctuation", OrgTokenKind::Punctuation)
    .value("LinkOpen", OrgTokenKind::LinkOpen)
    .value("LinkClose", OrgTokenKind::LinkClose)
    .value("RawUrl", OrgTokenKind::RawUrl)
    .value("LinkTargetOpen", OrgTokenKind::LinkTargetOpen)
    .value("LinkTargetClose", OrgTokenKind::LinkTargetClose)
    .value("LinkInternal", OrgTokenKind::LinkInternal, R"RAW(No protocol is used in the link, it is targeting some internal named entry.)RAW")
    .value("LinkProtocol", OrgTokenKind::LinkProtocol, R"RAW(Protocol used by the link - `file:`, `https:` etc.)RAW")
    .value("LinkFull", OrgTokenKind::LinkFull, R"RAW(Full token for the link, used in cases where it does not make sense to fracture the token - regular https URLs etc.)RAW")
    .value("LinkPath", OrgTokenKind::LinkPath, R"RAW(Link path for searches in file)RAW")
    .value("LinkTarget", OrgTokenKind::LinkTarget, R"RAW(Target of the link protocol that does not follow regular URI encoding scheme - for example `id:`, `elisp`, or `shell` links.)RAW")
    .value("LinkExtraSeparator", OrgTokenKind::LinkExtraSeparator, R"RAW(Separator of the extra content in the link, `::`)RAW")
    .value("LinkExtra", OrgTokenKind::LinkExtra, R"RAW(Additional parametrization for the link search)RAW")
    .value("LinkDescriptionOpen", OrgTokenKind::LinkDescriptionOpen)
    .value("LinkDescriptionClose", OrgTokenKind::LinkDescriptionClose)
    .value("TextSeparator", OrgTokenKind::TextSeparator)
    .value("ParagraphStart", OrgTokenKind::ParagraphStart, R"RAW(Fake token inserted by the lexer to delimit start of the paragraph)RAW")
    .value("ParagraphEnd", OrgTokenKind::ParagraphEnd)
    .value("FootnoteStart", OrgTokenKind::FootnoteStart)
    .value("FootnoteEnd", OrgTokenKind::FootnoteEnd)
    .value("Word", OrgTokenKind::Word, R"RAW(Regular word in the paragraph)RAW")
    .value("Escaped", OrgTokenKind::Escaped, R"RAW(Escaped character in plain text - `\*`, `\/` etc. Escaped characters and sequences thereof are treated like a regular plain text.)RAW")
    .value("DoubleSlash", OrgTokenKind::DoubleSlash, R"RAW(Put at the end of the lexer first logbook line to separate the  note, otherwise is treated as standalone escaped slash.)RAW")
    .value("Newline", OrgTokenKind::Newline, R"RAW(Explicit newline a paragraph)RAW")
    .value("SkipSpace", OrgTokenKind::SkipSpace)
    .value("SkipNewline", OrgTokenKind::SkipNewline)
    .value("SkipAny", OrgTokenKind::SkipAny)
    .value("MaybeWord", OrgTokenKind::MaybeWord)
    .value("Space", OrgTokenKind::Space, R"RAW(Space in the paragraph)RAW")
    .value("BigIdent", OrgTokenKind::BigIdent, R"RAW(`TODO`, `NOTE` and similar capitalized words)RAW")
    .value("RawText", OrgTokenKind::RawText, R"RAW(Unparsed raw text, either as a part of paragraph or some embedded construction such as link address.)RAW")
    .value("InlineSrc", OrgTokenKind::InlineSrc, R"RAW(Start of an inline source code block: `src_nim[]{}`)RAW")
    .value("InlineCall", OrgTokenKind::InlineCall, R"RAW(Start of an inline call block: `call_name[]{}`)RAW")
    .value("CurlyStart", OrgTokenKind::CurlyStart, R"RAW(Start of the curly section of an inline source/call)RAW")
    .value("CurlyEnd", OrgTokenKind::CurlyEnd, R"RAW(End of the curly section of an inline source/call)RAW")
    .value("SymbolStart", OrgTokenKind::SymbolStart, R"RAW(Unquoted `\symbol` directly in the text)RAW")
    .value("Ident", OrgTokenKind::Ident)
    .value("DollarOpen", OrgTokenKind::DollarOpen, R"RAW(Opening dollar inline latex math)RAW")
    .value("DollarClose", OrgTokenKind::DollarClose, R"RAW(Closing dollar for inline latex math)RAW")
    .value("DoubleDollarOpen", OrgTokenKind::DoubleDollarOpen, R"RAW(Opening `$` for inline latex)RAW")
    .value("DoubleDollarClose", OrgTokenKind::DoubleDollarClose, R"RAW(Closing `$` for inline latex)RAW")
    .value("LatexParOpen", OrgTokenKind::LatexParOpen, R"RAW(Opening `\(` for inline latex math)RAW")
    .value("LatexParClose", OrgTokenKind::LatexParClose, R"RAW(Closing `\)` for inline latex math)RAW")
    .value("LatexBraceOpen", OrgTokenKind::LatexBraceOpen, R"RAW(Opening `\[` for inline display latex equation)RAW")
    .value("LatexBraceClose", OrgTokenKind::LatexBraceClose, R"RAW(Closing `\]` for inline display latex equation)RAW")
    .value("LatexInlineRaw", OrgTokenKind::LatexInlineRaw, R"RAW(Content of the brace/par-enclosed math)RAW")
    .value("DoubleAt", OrgTokenKind::DoubleAt, R"RAW(Inline backend passthrough `@@`)RAW")
    .value("AtBracket", OrgTokenKind::AtBracket, R"RAW(Inline annotation)RAW")
    .value("AtMention", OrgTokenKind::AtMention, R"RAW(`@user` mention in the text)RAW")
    .value("HashTag", OrgTokenKind::HashTag, R"RAW(Start of the inline hashtag `#tag`)RAW")
    .value("HashTagSub", OrgTokenKind::HashTagSub, R"RAW(Nested hashtag separator)RAW")
    .value("HashTagOpen", OrgTokenKind::HashTagOpen, R"RAW(Start of the nested hashtag grop bracket)RAW")
    .value("HashTagClose", OrgTokenKind::HashTagClose, R"RAW(End of the nested hashtag group separator)RAW")
    .value("Comma", OrgTokenKind::Comma, R"RAW(Comma - punctuation or a syntax element (e.g. for macro arguments))RAW")
    .value("ParOpen", OrgTokenKind::ParOpen, R"RAW(Paren open - punctuation or a syntax element)RAW")
    .value("ParClose", OrgTokenKind::ParClose, R"RAW(Paren close - punctuation or a syntax element)RAW")
    .value("Colon", OrgTokenKind::Colon)
    .value("Circumflex", OrgTokenKind::Circumflex, R"RAW(`^` possible superscript in the text)RAW")
    .value("MacroOpen", OrgTokenKind::MacroOpen, R"RAW(Start of the macro call `{{{`)RAW")
    .value("MacroClose", OrgTokenKind::MacroClose, R"RAW(Close of the macro call `}}}`)RAW")
    .value("MetaBraceOpen", OrgTokenKind::MetaBraceOpen)
    .value("MetaBraceBody", OrgTokenKind::MetaBraceBody)
    .value("MetaBraceClose", OrgTokenKind::MetaBraceClose)
    .value("MetaArgsOpen", OrgTokenKind::MetaArgsOpen)
    .value("MetaArgsBody", OrgTokenKind::MetaArgsBody)
    .value("MetaArgsClose", OrgTokenKind::MetaArgsClose)
    .value("SrcOpen", OrgTokenKind::SrcOpen)
    .value("SrcName", OrgTokenKind::SrcName)
    .value("SrcArgs", OrgTokenKind::SrcArgs)
    .value("SrcBody", OrgTokenKind::SrcBody)
    .value("SrcClose", OrgTokenKind::SrcClose)
    .value("CallOpen", OrgTokenKind::CallOpen)
    .value("CallName", OrgTokenKind::CallName)
    .value("CallInsideHeader", OrgTokenKind::CallInsideHeader)
    .value("CallArgs", OrgTokenKind::CallArgs)
    .value("EndHeader", OrgTokenKind::EndHeader)
    .value("CallClose", OrgTokenKind::CallClose)
    .value("CmdArguments", OrgTokenKind::CmdArguments)
    .value("TableBegin", OrgTokenKind::TableBegin)
    .value("TableEnd", OrgTokenKind::TableEnd)
    .value("CellBody", OrgTokenKind::CellBody, R"RAW(Unformatted table cell body)RAW")
    .value("RowSpec", OrgTokenKind::RowSpec, R"RAW(`#+row` command together with parameters)RAW")
    .value("CellSpec", OrgTokenKind::CellSpec, R"RAW(`#+cell` command with parameters)RAW")
    .value("Content", OrgTokenKind::Content, R"RAW(Temporary token created during initial content lexing)RAW")
    .value("ContentStart", OrgTokenKind::ContentStart, R"RAW(Start of the table cell content section)RAW")
    .value("ContentEnd", OrgTokenKind::ContentEnd, R"RAW(End of the table cell content section)RAW")
    .value("PipeOpen", OrgTokenKind::PipeOpen)
    .value("PipeSeparator", OrgTokenKind::PipeSeparator, R"RAW(Vertical pipe (`|`) cell separator)RAW")
    .value("PipeClose", OrgTokenKind::PipeClose)
    .value("PipeCellOpen", OrgTokenKind::PipeCellOpen)
    .value("DashSeparator", OrgTokenKind::DashSeparator, R"RAW(Horizontal dash (`---`, `:---`, `---:` or `:---:`) row separator)RAW")
    .value("CornerPlus", OrgTokenKind::CornerPlus, R"RAW(Corner plus (`+`))RAW")
    .value("Command", OrgTokenKind::Command)
    .value("CommandArgs", OrgTokenKind::CommandArgs)
    .value("Body", OrgTokenKind::Body)
    .value("LangName", OrgTokenKind::LangName)
    .value("DoubleAngleOpen", OrgTokenKind::DoubleAngleOpen, R"RAW(`<<` - open for noweb or anchor placeholder)RAW")
    .value("DoubleAngleClose", OrgTokenKind::DoubleAngleClose, R"RAW(`>>` - close for noweb or anchor placeholder)RAW")
    .value("TripleAngleOpen", OrgTokenKind::TripleAngleOpen, R"RAW(`<<<` - radio target open)RAW")
    .value("TripleAngleClose", OrgTokenKind::TripleAngleClose, R"RAW(`>>>` - radio target close)RAW")
    .value("AngleOpen", OrgTokenKind::AngleOpen, R"RAW(Placeholder open)RAW")
    .value("AngleClose", OrgTokenKind::AngleClose, R"RAW(Placeholder close)RAW")
    .value("TextBlock", OrgTokenKind::TextBlock, R"RAW(Code before noweb placeholder. Requires separate token to handle `##<<commented>>` - prefix comment should be duplicated for each line of the placeholder expansion.)RAW")
    .export_values()
    ;
  pybind11::enum_<OrgCommandKind>(m, "OrgCommandKind")
    .value("None", OrgCommandKind::None)
    .value("Include", OrgCommandKind::Include)
    .value("Filetags", OrgCommandKind::Filetags)
    .value("Setupfile", OrgCommandKind::Setupfile)
    .value("Columns", OrgCommandKind::Columns)
    .value("OtherProperty", OrgCommandKind::OtherProperty)
    .value("BeginTable", OrgCommandKind::BeginTable)
    .value("EndTable", OrgCommandKind::EndTable, R"RAW(`#+table`)RAW")
    .value("Row", OrgCommandKind::Row, R"RAW(`#+row`)RAW")
    .value("Cell", OrgCommandKind::Cell, R"RAW(`#+cell`)RAW")
    .value("BeginAdmonition", OrgCommandKind::BeginAdmonition)
    .value("EndAdmonition", OrgCommandKind::EndAdmonition)
    .value("BeginDynamic", OrgCommandKind::BeginDynamic)
    .value("EndDynamic", OrgCommandKind::EndDynamic, R"RAW(`#+begin:`)RAW")
    .value("BeginCenter", OrgCommandKind::BeginCenter)
    .value("EndCenter", OrgCommandKind::EndCenter, R"RAW(`#+begin_center`)RAW")
    .value("BeginQuote", OrgCommandKind::BeginQuote)
    .value("EndQuote", OrgCommandKind::EndQuote, R"RAW(`#+quote`)RAW")
    .value("BeginSrc", OrgCommandKind::BeginSrc)
    .value("EndSrc", OrgCommandKind::EndSrc, R"RAW(`#+begin_src`)RAW")
    .value("BeginExport", OrgCommandKind::BeginExport)
    .value("EndExport", OrgCommandKind::EndExport, R"RAW(`#+end_export`)RAW")
    .value("BeginExample", OrgCommandKind::BeginExample)
    .value("EndExample", OrgCommandKind::EndExample)
    .value("BeginDetails", OrgCommandKind::BeginDetails)
    .value("EndDetails", OrgCommandKind::EndDetails)
    .value("BeginSummary", OrgCommandKind::BeginSummary)
    .value("EndSummary", OrgCommandKind::EndSummary)
    .value("LatexClassOptions", OrgCommandKind::LatexClassOptions, R"RAW(`#+latex_class_options`)RAW")
    .value("LatexClass", OrgCommandKind::LatexClass)
    .value("LatexCompiler", OrgCommandKind::LatexCompiler)
    .value("AttrLatex", OrgCommandKind::AttrLatex, R"RAW(`#+attr_latex:`)RAW")
    .value("AttrImg", OrgCommandKind::AttrImg, R"RAW(`#+attr_img:`)RAW")
    .value("AttrHtml", OrgCommandKind::AttrHtml, R"RAW(`#+attr_html:`)RAW")
    .value("HtmlHead", OrgCommandKind::HtmlHead, R"RAW(`#+html_head:`)RAW")
    .value("Language", OrgCommandKind::Language, R"RAW(`#+language:`)RAW")
    .value("Options", OrgCommandKind::Options, R"RAW(`#+options: `)RAW")
    .value("Title", OrgCommandKind::Title, R"RAW(`#+title:`)RAW")
    .value("Property", OrgCommandKind::Property, R"RAW(`#+property:`)RAW")
    .value("Author", OrgCommandKind::Author, R"RAW(`#+author:`)RAW")
    .value("Bind", OrgCommandKind::Bind, R"RAW(`#+bind:`)RAW")
    .value("Creator", OrgCommandKind::Creator, R"RAW(`#+creator:`)RAW")
    .value("LatexHeader", OrgCommandKind::LatexHeader, R"RAW(`#+latex_header`)RAW")
    .value("Results", OrgCommandKind::Results, R"RAW(`#+results:`)RAW")
    .value("Call", OrgCommandKind::Call, R"RAW(`#+call:`)RAW")
    .value("Name", OrgCommandKind::Name, R"RAW(`#+name:`)RAW")
    .value("Caption", OrgCommandKind::Caption, R"RAW(`#+caption:`)RAW")
    .value("Header", OrgCommandKind::Header, R"RAW(`#+header:`)RAW")
    .value("TableFormula", OrgCommandKind::TableFormula, R"RAW(`#+tblfm:`)RAW")
    .export_values()
    ;
  pybind11::enum_<OrgPropertyKind>(m, "OrgPropertyKind")
    .value("Title", OrgPropertyKind::Title)
    .value("Author", OrgPropertyKind::Author)
    .value("Date", OrgPropertyKind::Date)
    .value("Email", OrgPropertyKind::Email)
    .value("Language", OrgPropertyKind::Language)
    .value("Url", OrgPropertyKind::Url)
    .value("SourceUrl", OrgPropertyKind::SourceUrl)
    .value("AttrImg", OrgPropertyKind::AttrImg)
    .value("Toplevel", OrgPropertyKind::Toplevel)
    .value("Blocker", OrgPropertyKind::Blocker)
    .value("Created", OrgPropertyKind::Created)
    .value("Unnumbered", OrgPropertyKind::Unnumbered)
    .value("Trigger", OrgPropertyKind::Trigger)
    .value("Ordered", OrgPropertyKind::Ordered)
    .value("Noblocking", OrgPropertyKind::Noblocking)
    .value("ExportOptions", OrgPropertyKind::ExportOptions)
    .value("BackendExportOptions", OrgPropertyKind::BackendExportOptions)
    .value("AttrBackend", OrgPropertyKind::AttrBackend)
    .value("ColumnSpec", OrgPropertyKind::ColumnSpec)
    .value("Name", OrgPropertyKind::Name)
    .value("Caption", OrgPropertyKind::Caption)
    .value("LinkAbbrev", OrgPropertyKind::LinkAbbrev)
    .value("Filetags", OrgPropertyKind::Filetags)
    .value("TagConf", OrgPropertyKind::TagConf)
    .value("LatexHeader", OrgPropertyKind::LatexHeader)
    .value("OtherProperty", OrgPropertyKind::OtherProperty)
    .value("Id", OrgPropertyKind::Id)
    .export_values()
    ;
  pybind11::enum_<OrgUnnumberedKind>(m, "OrgUnnumberedKind")
    .value("Notoc", OrgUnnumberedKind::Notoc)
    .value("True", OrgUnnumberedKind::True)
    .value("False", OrgUnnumberedKind::False)
    .export_values()
    ;
  pybind11::enum_<OrgBlockLexerState>(m, "OrgBlockLexerState")
    .value("None", OrgBlockLexerState::None)
    .value("InHeader", OrgBlockLexerState::InHeader)
    .value("InBody", OrgBlockLexerState::InBody)
    .value("Ended", OrgBlockLexerState::Ended)
    .value("Complete", OrgBlockLexerState::Complete)
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
  #ifndef IN_CLANGD_PROCESSING
    #define PY_HAXORG_COMPILING
    #include "pyhaxorg_manual_wrap.hpp"
  #endif
  pybind11::class_<PySemId>(m, "PySemId")
    .def(pybind11::init<>())
    .def("getKind",
         &PySemId::getKind)
    .def("getSubnodeRange",
         &PySemId::getSubnodeRange,
         pybind11::arg("slice"))
    .def("getSingleSubnode",
         &PySemId::getSingleSubnode,
         pybind11::arg("index"))
    .def("castAs",
         &PySemId::castAs)
    .def("operator[]",
         &PySemId::operator[],
         pybind11::arg("index"))
    .def("operator[]",
         &PySemId::operator[],
         pybind11::arg("slice"))
    ;
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
    .def("parseFile",
         &OrgContext::parseFile,
         pybind11::arg("file"))
    .def("parseString",
         &OrgContext::parseString,
         pybind11::arg("text"))
    .def("getNode",
         &OrgContext::getNode)
    ;
}