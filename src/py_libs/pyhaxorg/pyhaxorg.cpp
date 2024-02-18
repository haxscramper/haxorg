/* clang-format off */
#undef slots
#include <pybind11/pybind11.h>
#include <sem/SemOrg.hpp>
#include <pybind11/stl.h>
#ifndef IN_CLANGD_PROCESSING
  #define PY_HAXORG_COMPILING
  #include "pyhaxorg_manual_impl.hpp"
#endif
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Org>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Org>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Row>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Row>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::HashTag>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::HashTag>>)
PYBIND11_MAKE_OPAQUE(std::vector<Str>)
PYBIND11_MAKE_OPAQUE(Vec<Str>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::CmdArgument>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::CmdArgument>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Code::Switch>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Code::Switch>)
PYBIND11_MAKE_OPAQUE(std::vector<int>)
PYBIND11_MAKE_OPAQUE(Vec<int>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Symbol::Param>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Symbol::Param>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::SubtreeLog>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::SubtreeLog>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Subtree::Property>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Subtree::Property>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Subtree::Period>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Subtree::Period>)
PYBIND11_MODULE(pyhaxorg, m) {
  bind_vector<sem::SemId<sem::Org>>(m, "VecOfSemIdOfOrg");
  bind_vector<sem::SemId<sem::Row>>(m, "VecOfSemIdOfRow");
  bind_vector<sem::SemId<sem::HashTag>>(m, "VecOfSemIdOfHashTag");
  bind_vector<Str>(m, "VecOfStr");
  bind_vector<sem::SemId<sem::CmdArgument>>(m, "VecOfSemIdOfCmdArgument");
  bind_vector<sem::Code::Switch>(m, "VecOfSwitch");
  bind_vector<int>(m, "VecOfint");
  bind_vector<sem::Symbol::Param>(m, "VecOfParam");
  bind_vector<sem::SemId<sem::SubtreeLog>>(m, "VecOfSemIdOfSubtreeLog");
  bind_vector<sem::Subtree::Property>(m, "VecOfProperty");
  bind_vector<sem::Subtree::Period>(m, "VecOfPeriod");
  pybind11::class_<sem::Org, sem::SemId<sem::Org>>(m, "Org")
    .def_readwrite("loc", &sem::Org::loc, R"RAW(\brief Location of the node in the original source file)RAW")
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
         [](sem::Org const& node) -> auto { return pybind11::make_iterator(node.subnodes.begin(), node.subnodes.end()); },
         pybind11::keep_alive<0, 1>())
    ;
  pybind11::class_<LineCol>(m, "LineCol")
    .def(pybind11::init<>())
    .def_readwrite("line", &LineCol::line)
    .def_readwrite("column", &LineCol::column)
    .def_readwrite("pos", &LineCol::pos)
    ;
  #ifndef IN_CLANGD_PROCESSING
    #define PY_HAXORG_COMPILING
    #include "pyhaxorg_manual_wrap.hpp"
  #endif
  pybind11::class_<sem::Stmt, sem::SemId<sem::Stmt>, sem::Org>(m, "Stmt")
    .def_readwrite("attached", &sem::Stmt::attached)
    .def("getAttached",
         static_cast<Opt<sem::SemId<sem::Org>>(sem::Stmt::*)(OrgSemKind)>(&sem::Stmt::getAttached),
         pybind11::arg("kind"))
    ;
  pybind11::class_<sem::Inline, sem::SemId<sem::Inline>, sem::Org>(m, "Inline")
    ;
  pybind11::class_<sem::StmtList, sem::SemId<sem::StmtList>, sem::Org>(m, "StmtList")
    .def_readwrite("loc", &sem::StmtList::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::Empty, sem::SemId<sem::Empty>, sem::Org>(m, "Empty")
    .def_readwrite("loc", &sem::Empty::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::Row, sem::SemId<sem::Row>, sem::Org>(m, "Row")
    .def_readwrite("loc", &sem::Row::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::Table, sem::SemId<sem::Table>, sem::Stmt>(m, "Table")
    .def_readwrite("loc", &sem::Table::loc, R"RAW(Document)RAW")
    .def_readwrite("rows", &sem::Table::rows, R"RAW(List of rows for the table)RAW")
    .def_readwrite("attached", &sem::Table::attached)
    .def("getAttached",
         static_cast<Opt<sem::SemId<sem::Org>>(sem::Table::*)(OrgSemKind)>(&sem::Table::getAttached),
         pybind11::arg("kind"))
    ;
  pybind11::class_<sem::HashTag, sem::SemId<sem::HashTag>, sem::Inline>(m, "HashTag")
    .def_readwrite("loc", &sem::HashTag::loc, R"RAW(Document)RAW")
    .def_readwrite("head", &sem::HashTag::head, R"RAW(Main part of the tag)RAW")
    .def_readwrite("subtags", &sem::HashTag::subtags, R"RAW(List of nested tags)RAW")
    .def("prefixMatch",
         static_cast<bool(sem::HashTag::*)(Vec<Str> const&) const>(&sem::HashTag::prefixMatch),
         pybind11::arg("prefix"),
         R"RAW(Check if list of tag names is a prefix for either of the nested hash tags in this one)RAW")
    ;
  pybind11::class_<sem::Footnote, sem::SemId<sem::Footnote>, sem::Inline>(m, "Footnote")
    .def_readwrite("loc", &sem::Footnote::loc, R"RAW(Document)RAW")
    .def_readwrite("tag", &sem::Footnote::tag, R"RAW(Footnote text target name)RAW")
    .def_readwrite("definition", &sem::Footnote::definition, R"RAW(Link to possibly resolved definition)RAW")
    ;
  pybind11::class_<sem::Completion, sem::SemId<sem::Completion>, sem::Inline>(m, "Completion")
    .def_readwrite("loc", &sem::Completion::loc, R"RAW(Document)RAW")
    .def_readwrite("done", &sem::Completion::done, R"RAW(Number of completed tasks)RAW")
    .def_readwrite("full", &sem::Completion::full, R"RAW(Full number of tasks)RAW")
    .def_readwrite("isPercent", &sem::Completion::isPercent, R"RAW(Use fraction or percent to display completion)RAW")
    ;
  pybind11::class_<sem::Paragraph, sem::SemId<sem::Paragraph>, sem::Stmt>(m, "Paragraph")
    .def_readwrite("loc", &sem::Paragraph::loc, R"RAW(Document)RAW")
    .def_readwrite("attached", &sem::Paragraph::attached)
    .def("isFootnoteDefinition", static_cast<bool(sem::Paragraph::*)() const>(&sem::Paragraph::isFootnoteDefinition), R"RAW(Check if paragraph defines footnote)RAW")
    .def("getAttached",
         static_cast<Opt<sem::SemId<sem::Org>>(sem::Paragraph::*)(OrgSemKind)>(&sem::Paragraph::getAttached),
         pybind11::arg("kind"))
    ;
  pybind11::class_<sem::Format, sem::SemId<sem::Format>, sem::Org>(m, "Format")
    ;
  pybind11::class_<sem::Center, sem::SemId<sem::Center>, sem::Format>(m, "Center")
    .def_readwrite("loc", &sem::Center::loc, R"RAW(Document)RAW")
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
    .def_readwrite("loc", &sem::Caption::loc, R"RAW(Document)RAW")
    .def_readwrite("text", &sem::Caption::text, R"RAW(Content description)RAW")
    ;
  pybind11::class_<sem::CommandGroup, sem::SemId<sem::CommandGroup>, sem::Stmt>(m, "CommandGroup")
    .def_readwrite("loc", &sem::CommandGroup::loc, R"RAW(Document)RAW")
    .def_readwrite("attached", &sem::CommandGroup::attached)
    .def("getAttached",
         static_cast<Opt<sem::SemId<sem::Org>>(sem::CommandGroup::*)(OrgSemKind)>(&sem::CommandGroup::getAttached),
         pybind11::arg("kind"))
    ;
  pybind11::class_<sem::Block, sem::SemId<sem::Block>, sem::Command>(m, "Block")
    ;
  pybind11::class_<sem::Tblfm, sem::SemId<sem::Tblfm>, sem::Command>(m, "Tblfm")
    .def_readwrite("loc", &sem::Tblfm::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::Quote, sem::SemId<sem::Quote>, sem::Org>(m, "Quote")
    .def_readwrite("loc", &sem::Quote::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::Verse, sem::SemId<sem::Verse>, sem::Block>(m, "Verse")
    .def_readwrite("loc", &sem::Verse::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::Example, sem::SemId<sem::Example>, sem::Block>(m, "Example")
    .def_readwrite("loc", &sem::Example::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::CmdArguments, sem::SemId<sem::CmdArguments>, sem::Org>(m, "CmdArguments")
    .def_readwrite("loc", &sem::CmdArguments::loc, R"RAW(Document)RAW")
    .def_readwrite("positional", &sem::CmdArguments::positional, R"RAW(Positional arguments that had no keys)RAW")
    .def_readwrite("named", &sem::CmdArguments::named, R"RAW(Stored key-value mapping)RAW")
    .def("popArg",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::CmdArguments::*)(Str)>(&sem::CmdArguments::popArg),
         pybind11::arg("key"),
         R"RAW(Remove argument value from the map and return it if present)RAW")
    ;
  pybind11::class_<sem::CmdArgument, sem::SemId<sem::CmdArgument>, sem::Org>(m, "CmdArgument")
    .def_readwrite("loc", &sem::CmdArgument::loc, R"RAW(Document)RAW")
    .def_readwrite("key", &sem::CmdArgument::key, R"RAW(Key)RAW")
    .def_readwrite("value", &sem::CmdArgument::value, R"RAW(Value)RAW")
    .def("getInt", static_cast<Opt<int>(sem::CmdArgument::*)() const>(&sem::CmdArgument::getInt), R"RAW(Parse argument as integer value)RAW")
    .def("getBool", static_cast<Opt<bool>(sem::CmdArgument::*)() const>(&sem::CmdArgument::getBool), R"RAW(Get argument as bool)RAW")
    .def("getString", static_cast<Str(sem::CmdArgument::*)() const>(&sem::CmdArgument::getString), R"RAW(Get original string)RAW")
    ;
  pybind11::class_<sem::Export, sem::SemId<sem::Export>, sem::Block>(m, "Export")
    .def_readwrite("loc", &sem::Export::loc, R"RAW(Document)RAW")
    .def_readwrite("format", &sem::Export::format, R"RAW(Export block type)RAW")
    .def_readwrite("exporter", &sem::Export::exporter, R"RAW(Exporter backend name)RAW")
    .def_readwrite("parameters", &sem::Export::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("placement", &sem::Export::placement, R"RAW(Customized position of the text in the final exporting document.)RAW")
    .def_readwrite("content", &sem::Export::content, R"RAW(Raw exporter content string)RAW")
    ;
  pybind11::enum_<sem::Export::Format>(m, "ExportFormat")
    .value("Inline", sem::Export::Format::Inline, R"RAW(Export directly in the paragraph)RAW")
    .value("Line", sem::Export::Format::Line, R"RAW(Single line of export)RAW")
    .value("Block", sem::Export::Format::Block, R"RAW(Multiple lines of export)RAW")
    ;
  pybind11::class_<sem::AdmonitionBlock, sem::SemId<sem::AdmonitionBlock>, sem::Block>(m, "AdmonitionBlock")
    .def_readwrite("loc", &sem::AdmonitionBlock::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::Code, sem::SemId<sem::Code>, sem::Block>(m, "Code")
    .def_readwrite("loc", &sem::Code::loc, R"RAW(Document)RAW")
    .def_readwrite("lang", &sem::Code::lang, R"RAW(Code block language name)RAW")
    .def_readwrite("switches", &sem::Code::switches, R"RAW(Switch options for block)RAW")
    .def_readwrite("exports", &sem::Code::exports, R"RAW(What to export)RAW")
    .def_readwrite("parameters", &sem::Code::parameters, R"RAW(Additional parameters that are language-specific)RAW")
    .def_readwrite("cache", &sem::Code::cache, R"RAW(Do cache values?)RAW")
    .def_readwrite("eval", &sem::Code::eval, R"RAW(Eval on export?)RAW")
    .def_readwrite("noweb", &sem::Code::noweb, R"RAW(Web-tangle code on export/run)RAW")
    .def_readwrite("hlines", &sem::Code::hlines, R"RAW(?)RAW")
    .def_readwrite("tangle", &sem::Code::tangle, R"RAW(?)RAW")
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
    ;
  pybind11::enum_<sem::Code::Results>(m, "CodeResults")
    .value("Replace", sem::Code::Results::Replace, R"RAW(Remove old result, replace with new value)RAW")
    ;
  pybind11::enum_<sem::Code::Exports>(m, "CodeExports")
    .value("None", sem::Code::Exports::None, R"RAW(Hide both original code and run result)RAW")
    .value("Both", sem::Code::Exports::Both, R"RAW(Show output and code)RAW")
    .value("Code", sem::Code::Exports::Code, R"RAW(Show only code)RAW")
    .value("Results", sem::Code::Exports::Results, R"RAW(Show only evaluation results)RAW")
    ;
  pybind11::class_<sem::Time, sem::SemId<sem::Time>, sem::Org>(m, "Time")
    .def_readwrite("loc", &sem::Time::loc, R"RAW(Document)RAW")
    .def_readwrite("isActive", &sem::Time::isActive, R"RAW(<active> vs [inactive])RAW")
    .def_readwrite("time", &sem::Time::time)
    .def("getStatic", static_cast<sem::Time::Static&(sem::Time::*)()>(&sem::Time::getStatic))
    .def("getDynamic", static_cast<sem::Time::Dynamic&(sem::Time::*)()>(&sem::Time::getDynamic))
    .def("getTimeKind", static_cast<sem::Time::TimeKind(sem::Time::*)() const>(&sem::Time::getTimeKind))
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
    ;
  pybind11::enum_<sem::Time::Repeat::Period>(m, "TimeRepeatPeriod")
    .value("Year", sem::Time::Repeat::Period::Year)
    .value("Month", sem::Time::Repeat::Period::Month)
    .value("Week", sem::Time::Repeat::Period::Week)
    .value("Day", sem::Time::Repeat::Period::Day)
    .value("Hour", sem::Time::Repeat::Period::Hour)
    .value("Minute", sem::Time::Repeat::Period::Minute)
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
    ;
  pybind11::class_<sem::TimeRange, sem::SemId<sem::TimeRange>, sem::Org>(m, "TimeRange")
    .def_readwrite("loc", &sem::TimeRange::loc, R"RAW(Document)RAW")
    .def_readwrite("from_", &sem::TimeRange::from, R"RAW(Starting time)RAW")
    .def_readwrite("to", &sem::TimeRange::to, R"RAW(Finishing time)RAW")
    ;
  pybind11::class_<sem::Macro, sem::SemId<sem::Macro>, sem::Org>(m, "Macro")
    .def_readwrite("loc", &sem::Macro::loc, R"RAW(Document)RAW")
    .def_readwrite("name", &sem::Macro::name, R"RAW(Macro name)RAW")
    .def_readwrite("arguments", &sem::Macro::arguments, R"RAW(Raw uninterpreted macro arguments)RAW")
    ;
  pybind11::class_<sem::Symbol, sem::SemId<sem::Symbol>, sem::Org>(m, "Symbol")
    .def_readwrite("loc", &sem::Symbol::loc, R"RAW(Document)RAW")
    .def_readwrite("name", &sem::Symbol::name, R"RAW(Name of the symbol)RAW")
    .def_readwrite("parameters", &sem::Symbol::parameters, R"RAW(Optional list of parameters)RAW")
    .def_readwrite("positional", &sem::Symbol::positional, R"RAW(Positional parameters)RAW")
    ;
  pybind11::class_<sem::Symbol::Param>(m, "SymbolParam")
    .def(pybind11::init<>())
    .def_readwrite("key", &sem::Symbol::Param::key, R"RAW(Key -- for non-positional)RAW")
    .def_readwrite("value", &sem::Symbol::Param::value, R"RAW(Uninterpreted value)RAW")
    ;
  pybind11::class_<sem::SubtreeLog, sem::SemId<sem::SubtreeLog>, sem::Org>(m, "SubtreeLog")
    .def_readwrite("loc", &sem::SubtreeLog::loc, R"RAW(Document)RAW")
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
    .def("getLogKind", static_cast<sem::SubtreeLog::Kind(sem::SubtreeLog::*)() const>(&sem::SubtreeLog::getLogKind))
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
    ;
  pybind11::class_<sem::Subtree, sem::SemId<sem::Subtree>, sem::Org>(m, "Subtree")
    .def_readwrite("loc", &sem::Subtree::loc, R"RAW(Document)RAW")
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
         static_cast<Vec<sem::Subtree::Property>(sem::Subtree::*)(sem::Subtree::Property::Kind, Str const&) const>(&sem::Subtree::getProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", ""))
    .def("getProperty",
         static_cast<Opt<sem::Subtree::Property>(sem::Subtree::*)(sem::Subtree::Property::Kind, Str const&) const>(&sem::Subtree::getProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", ""))
    .def("getContextualProperties",
         static_cast<Vec<sem::Subtree::Property>(sem::Subtree::*)(sem::Subtree::Property::Kind, Str const&) const>(&sem::Subtree::getContextualProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", ""))
    .def("getContextualProperty",
         static_cast<Opt<sem::Subtree::Property>(sem::Subtree::*)(sem::Subtree::Property::Kind, Str const&) const>(&sem::Subtree::getContextualProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", ""))
    ;
  pybind11::class_<sem::Subtree::Period>(m, "SubtreePeriod")
    .def(pybind11::init<>())
    .def_readwrite("kind", &sem::Subtree::Period::kind, R"RAW(Time period kind -- not associated with point/range distinction)RAW")
    .def("getTime", static_cast<sem::SemId<sem::Time>(sem::Subtree::Period::*)()>(&sem::Subtree::Period::getTime), R"RAW(Get associated time point)RAW")
    .def("getTimeRange", static_cast<sem::SemId<sem::TimeRange>(sem::Subtree::Period::*)()>(&sem::Subtree::Period::getTimeRange), R"RAW(Get associated time period)RAW")
    ;
  pybind11::enum_<sem::Subtree::Period::Kind>(m, "SubtreePeriodKind")
    .value("Clocked", sem::Subtree::Period::Kind::Clocked, R"RAW(Time period of the task execution.)RAW")
    .value("Scheduled", sem::Subtree::Period::Kind::Scheduled, R"RAW(Date of task execution start plus it's estimated effort duration. If the latter one is missing then only a single time point is returned)RAW")
    .value("Titled", sem::Subtree::Period::Kind::Titled, R"RAW(Single point or time range used in title. Single point can also be a simple time, such as `12:20`)RAW")
    .value("Deadline", sem::Subtree::Period::Kind::Deadline, R"RAW(Date of task completion. Must be a single time point)RAW")
    .value("Created", sem::Subtree::Period::Kind::Created, R"RAW(When the subtree was created)RAW")
    .value("Repeated", sem::Subtree::Period::Kind::Repeated, R"RAW(Last repeat time of the recurring tasks)RAW")
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
    .def("getUnknown", static_cast<sem::Subtree::Property::Unknown&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getUnknown))
    .def("getKind", static_cast<sem::Subtree::Property::Kind(sem::Subtree::Property::*)() const>(&sem::Subtree::Property::getKind))
    ;
  pybind11::enum_<sem::Subtree::Property::SetMode>(m, "SubtreePropertySetMode")
    .value("Override", sem::Subtree::Property::SetMode::Override)
    .value("Add", sem::Subtree::Property::SetMode::Add)
    .value("Subtract", sem::Subtree::Property::SetMode::Subtract)
    ;
  pybind11::enum_<sem::Subtree::Property::InheritanceMode>(m, "SubtreePropertyInheritanceMode")
    .value("ThisAndSub", sem::Subtree::Property::InheritanceMode::ThisAndSub)
    .value("OnlyThis", sem::Subtree::Property::InheritanceMode::OnlyThis)
    .value("OnlySub", sem::Subtree::Property::InheritanceMode::OnlySub)
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
  pybind11::class_<sem::Subtree::Property::Unknown>(m, "SubtreePropertyUnknown")
    .def(pybind11::init<>())
    .def_readwrite("value", &sem::Subtree::Property::Unknown::value, R"RAW(Converted value of the property)RAW")
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
    .value("Unknown", sem::Subtree::Property::Kind::Unknown)
    ;
  pybind11::class_<sem::LatexBody, sem::SemId<sem::LatexBody>, sem::Org>(m, "LatexBody")
    ;
  pybind11::class_<sem::InlineMath, sem::SemId<sem::InlineMath>, sem::LatexBody>(m, "InlineMath")
    .def_readwrite("loc", &sem::InlineMath::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::Leaf, sem::SemId<sem::Leaf>, sem::Org>(m, "Leaf")
    .def_readwrite("text", &sem::Leaf::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::Escaped, sem::SemId<sem::Escaped>, sem::Leaf>(m, "Escaped")
    .def_readwrite("loc", &sem::Escaped::loc, R"RAW(Document)RAW")
    .def_readwrite("text", &sem::Escaped::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::Newline, sem::SemId<sem::Newline>, sem::Leaf>(m, "Newline")
    .def_readwrite("loc", &sem::Newline::loc, R"RAW(Document)RAW")
    .def_readwrite("text", &sem::Newline::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::Space, sem::SemId<sem::Space>, sem::Leaf>(m, "Space")
    .def_readwrite("loc", &sem::Space::loc, R"RAW(Document)RAW")
    .def_readwrite("text", &sem::Space::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::Word, sem::SemId<sem::Word>, sem::Leaf>(m, "Word")
    .def_readwrite("loc", &sem::Word::loc, R"RAW(Document)RAW")
    .def_readwrite("text", &sem::Word::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::AtMention, sem::SemId<sem::AtMention>, sem::Leaf>(m, "AtMention")
    .def_readwrite("loc", &sem::AtMention::loc, R"RAW(Document)RAW")
    .def_readwrite("text", &sem::AtMention::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::RawText, sem::SemId<sem::RawText>, sem::Leaf>(m, "RawText")
    .def_readwrite("loc", &sem::RawText::loc, R"RAW(Document)RAW")
    .def_readwrite("text", &sem::RawText::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::Punctuation, sem::SemId<sem::Punctuation>, sem::Leaf>(m, "Punctuation")
    .def_readwrite("loc", &sem::Punctuation::loc, R"RAW(Document)RAW")
    .def_readwrite("text", &sem::Punctuation::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::Placeholder, sem::SemId<sem::Placeholder>, sem::Leaf>(m, "Placeholder")
    .def_readwrite("loc", &sem::Placeholder::loc, R"RAW(Document)RAW")
    .def_readwrite("text", &sem::Placeholder::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::BigIdent, sem::SemId<sem::BigIdent>, sem::Leaf>(m, "BigIdent")
    .def_readwrite("loc", &sem::BigIdent::loc, R"RAW(Document)RAW")
    .def_readwrite("text", &sem::BigIdent::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::Markup, sem::SemId<sem::Markup>, sem::Org>(m, "Markup")
    ;
  pybind11::class_<sem::Bold, sem::SemId<sem::Bold>, sem::Markup>(m, "Bold")
    .def_readwrite("loc", &sem::Bold::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::Underline, sem::SemId<sem::Underline>, sem::Markup>(m, "Underline")
    .def_readwrite("loc", &sem::Underline::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::Monospace, sem::SemId<sem::Monospace>, sem::Markup>(m, "Monospace")
    .def_readwrite("loc", &sem::Monospace::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::MarkQuote, sem::SemId<sem::MarkQuote>, sem::Markup>(m, "MarkQuote")
    .def_readwrite("loc", &sem::MarkQuote::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::Verbatim, sem::SemId<sem::Verbatim>, sem::Markup>(m, "Verbatim")
    .def_readwrite("loc", &sem::Verbatim::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::Italic, sem::SemId<sem::Italic>, sem::Markup>(m, "Italic")
    .def_readwrite("loc", &sem::Italic::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::Strike, sem::SemId<sem::Strike>, sem::Markup>(m, "Strike")
    .def_readwrite("loc", &sem::Strike::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::Par, sem::SemId<sem::Par>, sem::Markup>(m, "Par")
    .def_readwrite("loc", &sem::Par::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::List, sem::SemId<sem::List>, sem::Org>(m, "List")
    .def_readwrite("loc", &sem::List::loc, R"RAW(Document)RAW")
    .def("isDescriptionList", static_cast<bool(sem::List::*)() const>(&sem::List::isDescriptionList))
    ;
  pybind11::class_<sem::ListItem, sem::SemId<sem::ListItem>, sem::Org>(m, "ListItem")
    .def_readwrite("loc", &sem::ListItem::loc, R"RAW(Document)RAW")
    .def_readwrite("checkbox", &sem::ListItem::checkbox)
    .def_readwrite("header", &sem::ListItem::header)
    .def("isDescriptionItem", static_cast<bool(sem::ListItem::*)() const>(&sem::ListItem::isDescriptionItem))
    ;
  pybind11::enum_<sem::ListItem::Checkbox>(m, "ListItemCheckbox")
    .value("None", sem::ListItem::Checkbox::None)
    .value("Done", sem::ListItem::Checkbox::Done)
    .value("Empty", sem::ListItem::Checkbox::Empty)
    ;
  pybind11::class_<sem::Link, sem::SemId<sem::Link>, sem::Org>(m, "Link")
    .def_readwrite("loc", &sem::Link::loc, R"RAW(Document)RAW")
    .def_readwrite("description", &sem::Link::description)
    .def_readwrite("data", &sem::Link::data)
    .def("getRaw", static_cast<sem::Link::Raw&(sem::Link::*)()>(&sem::Link::getRaw))
    .def("getId", static_cast<sem::Link::Id&(sem::Link::*)()>(&sem::Link::getId))
    .def("getPerson", static_cast<sem::Link::Person&(sem::Link::*)()>(&sem::Link::getPerson))
    .def("getFootnote", static_cast<sem::Link::Footnote&(sem::Link::*)()>(&sem::Link::getFootnote))
    .def("getFile", static_cast<sem::Link::File&(sem::Link::*)()>(&sem::Link::getFile))
    .def("getLinkKind", static_cast<sem::Link::Kind(sem::Link::*)() const>(&sem::Link::getLinkKind))
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
    ;
  pybind11::class_<sem::DocumentOptions, sem::SemId<sem::DocumentOptions>, sem::Org>(m, "DocumentOptions")
    .def_readwrite("loc", &sem::DocumentOptions::loc, R"RAW(Document)RAW")
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
         static_cast<Vec<sem::Subtree::Property>(sem::DocumentOptions::*)(sem::Subtree::Property::Kind, Str const&) const>(&sem::DocumentOptions::getProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", ""))
    .def("getProperty",
         static_cast<Opt<sem::Subtree::Property>(sem::DocumentOptions::*)(sem::Subtree::Property::Kind, Str const&) const>(&sem::DocumentOptions::getProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", ""))
    .def("getDoExport", static_cast<sem::DocumentOptions::DoExport&(sem::DocumentOptions::*)()>(&sem::DocumentOptions::getDoExport))
    .def("getExportFixed", static_cast<sem::DocumentOptions::ExportFixed&(sem::DocumentOptions::*)()>(&sem::DocumentOptions::getExportFixed))
    .def("getTocExportKind", static_cast<sem::DocumentOptions::TocExportKind(sem::DocumentOptions::*)() const>(&sem::DocumentOptions::getTocExportKind))
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
    ;
  pybind11::enum_<sem::DocumentOptions::BrokenLinks>(m, "DocumentOptionsBrokenLinks")
    .value("Raise", sem::DocumentOptions::BrokenLinks::Raise)
    .value("Ignore", sem::DocumentOptions::BrokenLinks::Ignore)
    .value("Mark", sem::DocumentOptions::BrokenLinks::Mark)
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
    ;
  pybind11::class_<sem::Document, sem::SemId<sem::Document>, sem::Org>(m, "Document")
    .def_readwrite("loc", &sem::Document::loc, R"RAW(Document)RAW")
    .def_readwrite("title", &sem::Document::title)
    .def_readwrite("author", &sem::Document::author)
    .def_readwrite("creator", &sem::Document::creator)
    .def_readwrite("email", &sem::Document::email)
    .def_readwrite("language", &sem::Document::language)
    .def_readwrite("options", &sem::Document::options)
    .def_readwrite("exportFileName", &sem::Document::exportFileName)
    .def("getProperties",
         static_cast<Vec<sem::Subtree::Property>(sem::Document::*)(sem::Subtree::Property::Kind, Str const&) const>(&sem::Document::getProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", ""))
    .def("getProperty",
         static_cast<Opt<sem::Subtree::Property>(sem::Document::*)(sem::Subtree::Property::Kind, Str const&) const>(&sem::Document::getProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", ""))
    ;
  pybind11::class_<sem::ParseError, sem::SemId<sem::ParseError>, sem::Org>(m, "ParseError")
    .def_readwrite("loc", &sem::ParseError::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::FileTarget, sem::SemId<sem::FileTarget>, sem::Org>(m, "FileTarget")
    .def_readwrite("loc", &sem::FileTarget::loc, R"RAW(Document)RAW")
    .def_readwrite("path", &sem::FileTarget::path)
    .def_readwrite("line", &sem::FileTarget::line)
    .def_readwrite("searchTarget", &sem::FileTarget::searchTarget)
    .def_readwrite("restrictToHeadlines", &sem::FileTarget::restrictToHeadlines)
    .def_readwrite("targetId", &sem::FileTarget::targetId)
    .def_readwrite("regexp", &sem::FileTarget::regexp)
    ;
  pybind11::class_<sem::TextSeparator, sem::SemId<sem::TextSeparator>, sem::Org>(m, "TextSeparator")
    .def_readwrite("loc", &sem::TextSeparator::loc, R"RAW(Document)RAW")
    ;
  pybind11::class_<sem::Include, sem::SemId<sem::Include>, sem::Org>(m, "Include")
    .def_readwrite("loc", &sem::Include::loc, R"RAW(Document)RAW")
    .def_readwrite("data", &sem::Include::data)
    .def("getExample", static_cast<sem::Include::Example&(sem::Include::*)()>(&sem::Include::getExample))
    .def("getExport", static_cast<sem::Include::Export&(sem::Include::*)()>(&sem::Include::getExport))
    .def("getSrc", static_cast<sem::Include::Src&(sem::Include::*)()>(&sem::Include::getSrc))
    .def("getOrgDocument", static_cast<sem::Include::OrgDocument&(sem::Include::*)()>(&sem::Include::getOrgDocument))
    .def("getIncludeKind", static_cast<sem::Include::Kind(sem::Include::*)() const>(&sem::Include::getIncludeKind))
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
    ;
  pybind11::class_<sem::DocumentGroup, sem::SemId<sem::DocumentGroup>, sem::Org>(m, "DocumentGroup")
    .def_readwrite("loc", &sem::DocumentGroup::loc, R"RAW(Document)RAW")
    ;
  pybind11::enum_<OrgSpecName>(m, "OrgSpecName")
    .value("Unnamed_", OrgSpecName::Unnamed)
    .value("Result_", OrgSpecName::Result)
    .value("Year_", OrgSpecName::Year)
    .value("Day_", OrgSpecName::Day)
    .value("Clock_", OrgSpecName::Clock)
    .value("Repeater_", OrgSpecName::Repeater)
    .value("Zone_", OrgSpecName::Zone)
    .value("Link_", OrgSpecName::Link)
    .value("Tags_", OrgSpecName::Tags)
    .value("Tag_", OrgSpecName::Tag)
    .value("State_", OrgSpecName::State)
    .value("Protocol_", OrgSpecName::Protocol)
    .value("Desc_", OrgSpecName::Desc)
    .value("Times_", OrgSpecName::Times)
    .value("Drawer_", OrgSpecName::Drawer)
    .value("Args_", OrgSpecName::Args)
    .value("Name_", OrgSpecName::Name)
    .value("Definition_", OrgSpecName::Definition)
    .value("Body_", OrgSpecName::Body)
    .value("HeaderArgs_", OrgSpecName::HeaderArgs)
    .value("File_", OrgSpecName::File)
    .value("Kind_", OrgSpecName::Kind)
    .value("Lang_", OrgSpecName::Lang)
    .value("Prefix_", OrgSpecName::Prefix)
    .value("Text_", OrgSpecName::Text)
    .value("Todo_", OrgSpecName::Todo)
    .value("Urgency_", OrgSpecName::Urgency)
    .value("Title_", OrgSpecName::Title)
    .value("Completion_", OrgSpecName::Completion)
    .value("Head_", OrgSpecName::Head)
    .value("Subnodes_", OrgSpecName::Subnodes)
    .value("Properties_", OrgSpecName::Properties)
    .value("Logbook_", OrgSpecName::Logbook)
    .value("Description_", OrgSpecName::Description)
    .value("Logs_", OrgSpecName::Logs)
    .value("Newstate_", OrgSpecName::Newstate)
    .value("Oldstate_", OrgSpecName::Oldstate)
    .value("Time_", OrgSpecName::Time)
    .value("From_", OrgSpecName::From)
    .value("EndArgs_", OrgSpecName::EndArgs)
    .value("Flags_", OrgSpecName::Flags)
    .value("Value_", OrgSpecName::Value)
    .value("Assoc_", OrgSpecName::Assoc)
    .value("Main_", OrgSpecName::Main)
    .value("Hash_", OrgSpecName::Hash)
    .value("Bullet_", OrgSpecName::Bullet)
    .value("Counter_", OrgSpecName::Counter)
    .value("Checkbox_", OrgSpecName::Checkbox)
    .value("Header_", OrgSpecName::Header)
    .value("To_", OrgSpecName::To)
    .value("Diff_", OrgSpecName::Diff)
    .value("Property_", OrgSpecName::Property)
    .value("Subname_", OrgSpecName::Subname)
    .value("Values_", OrgSpecName::Values)
    .value("Cells_", OrgSpecName::Cells)
    .value("Rows_", OrgSpecName::Rows)
    .value("Lines_", OrgSpecName::Lines)
    .value("Chunks_", OrgSpecName::Chunks)
    .value("InheritanceMode_", OrgSpecName::InheritanceMode)
    .value("MainSetRule_", OrgSpecName::MainSetRule)
    .value("SubSetRule_", OrgSpecName::SubSetRule)
    ;
  pybind11::enum_<OrgNodeKind>(m, "OrgNodeKind")
    .value("None_", OrgNodeKind::None, R"RAW(Default valye for node - invalid state)RAW")
    .value("Document_", OrgNodeKind::Document, R"RAW(Toplevel part of the ast, not created by parser, and only used in `semorg` stage)RAW")
    .value("UserNode_", OrgNodeKind::UserNode, R"RAW(User-defined node [[code:OrgUserNode]])RAW")
    .value("Empty_", OrgNodeKind::Empty, R"RAW(Empty node - valid state that does not contain any value)RAW")
    .value("Error_", OrgNodeKind::Error, R"RAW(Failed node parse


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
    .value("ErrorTerminator_", OrgNodeKind::ErrorTerminator, R"RAW(Terminator node for failure in nested structure parsing)RAW")
    .value("ErrorToken_", OrgNodeKind::ErrorToken, R"RAW(Single invalid token)RAW")
    .value("InlineStmtList_", OrgNodeKind::InlineStmtList)
    .value("StmtList_", OrgNodeKind::StmtList, R"RAW(List of statements, possibly recursive. Used as toplevel part of the document, in recursive parsing of subtrees, or as regular list, in cases where multiple subnodes have to be grouped together.)RAW")
    .value("AssocStmtList_", OrgNodeKind::AssocStmtList, R"RAW(Associated list of statements - AST elements like commands and links are grouped together if placed on adjacent lines)RAW")
    .value("Subtree_", OrgNodeKind::Subtree, R"RAW(Section subtree)RAW")
    .value("SubtreeTimes_", OrgNodeKind::SubtreeTimes, R"RAW(Time? associated with subtree entry)RAW")
    .value("SubtreeStars_", OrgNodeKind::SubtreeStars)
    .value("Completion_", OrgNodeKind::Completion, R"RAW(Task compleation cookie, indicated either in percents of completion, or as `<done>/<todo>` ratio.)RAW")
    .value("Checkbox_", OrgNodeKind::Checkbox, R"RAW(Single checkbox item like `[X]` or `[-]`)RAW")
    .value("List_", OrgNodeKind::List)
    .value("Bullet_", OrgNodeKind::Bullet, R"RAW(List item prefix)RAW")
    .value("ListItem_", OrgNodeKind::ListItem)
    .value("ListTag_", OrgNodeKind::ListTag, R"RAW(Auxilliary wrapper for the paragraph placed at the start of the description list.)RAW")
    .value("Counter_", OrgNodeKind::Counter)
    .value("Comment_", OrgNodeKind::Comment, R"RAW(Inline or trailling comment. Can be used addition to `#+comment:` line or `#+begin-comment` section. Nested comment syntax is allowed (`#[ level1 #[ level2 ]# ]#`), but only outermost one is represented as separate AST node, everything else is a `.text`)RAW")
    .value("RawText_", OrgNodeKind::RawText, R"RAW(Raw string of text from input buffer. Things like particular syntax details of every single command, link formats are not handled in parser, deferring formatting to future processing layers )RAW")
    .value("Unparsed_", OrgNodeKind::Unparsed, R"RAW(Part of the org-mode document that is yet to be parsed. This node should not be created manually, it is only used for handling mutually recursive DSLs such as tables, which might include lists, which in turn might contain more tables in different bullet points.)RAW")
    .value("Command_", OrgNodeKind::Command, R"RAW(Undefined single-line command -- most likely custom user-provided oe)RAW")
    .value("CommandArguments_", OrgNodeKind::CommandArguments, R"RAW(Arguments for the command block)RAW")
    .value("CommandTitle_", OrgNodeKind::CommandTitle, R"RAW(`#+title:` - full document title)RAW")
    .value("CommandAuthor_", OrgNodeKind::CommandAuthor, R"RAW(`#+author:` Document author)RAW")
    .value("CommandCreator_", OrgNodeKind::CommandCreator, R"RAW(`#+creator:` Document creator)RAW")
    .value("CommandInclude_", OrgNodeKind::CommandInclude, R"RAW(`#+include:` - include other org-mode document (or subsection of it), source code or backend-specific chunk.)RAW")
    .value("CommandLanguage_", OrgNodeKind::CommandLanguage, R"RAW(`#+language:`)RAW")
    .value("CommandAttrHtml_", OrgNodeKind::CommandAttrHtml, R"RAW(`#+attr_html:`)RAW")
    .value("CommandName_", OrgNodeKind::CommandName, R"RAW(`#+name:` - name of the associated entry)RAW")
    .value("CommandHeader_", OrgNodeKind::CommandHeader, R"RAW(`#+header:` - extended list of parameters passed to associated block)RAW")
    .value("CommandOptions_", OrgNodeKind::CommandOptions, R"RAW(`#+options:` - document-wide formatting options)RAW")
    .value("CommandTblfm_", OrgNodeKind::CommandTblfm)
    .value("CommandBackendOptions_", OrgNodeKind::CommandBackendOptions, R"RAW(Backend-specific configuration options like `#+latex_header` `#+latex_class` etc.)RAW")
    .value("AttrImg_", OrgNodeKind::AttrImg)
    .value("CommandCaption_", OrgNodeKind::CommandCaption, R"RAW(`#+caption:` command)RAW")
    .value("File_", OrgNodeKind::File)
    .value("BlockExport_", OrgNodeKind::BlockExport)
    .value("InlineExport_", OrgNodeKind::InlineExport)
    .value("MultilineCommand_", OrgNodeKind::MultilineCommand, R"RAW(Multiline command such as code block, latex equation, large block of passthrough code. Some built-in org-mode commands do not requires `#+begin` prefix, (such as `#+quote` or `#+example`) are represented by this type of block as well.)RAW")
    .value("Result_", OrgNodeKind::Result, R"RAW(Command evaluation result)RAW")
    .value("Ident_", OrgNodeKind::Ident, R"RAW(regular identifier - `alnum + [-_]` characters for punctuation. Identifiers are compared and parsed in style-insensetive manner, meaning `CODE_BLOCK`, `code-block` and `codeblock` are identical.)RAW")
    .value("BareIdent_", OrgNodeKind::BareIdent, R"RAW(Bare identifier - any characters are allowed)RAW")
    .value("AdmonitionTag_", OrgNodeKind::AdmonitionTag, R"RAW(Big ident used in conjunction with colon at the start of paragraph is considered an admonition tag: `NOTE: Text`, `WARNING: text` etc.)RAW")
    .value("BigIdent_", OrgNodeKind::BigIdent, R"RAW(full-uppsercase identifier such as `MUST` or `TODO`)RAW")
    .value("VerbatimMultilineBlock_", OrgNodeKind::VerbatimMultilineBlock, R"RAW(Verbatim mulitiline block that *might* be a part of `orgMultilineCommand` (in case of `#+begin-src`), but not necessarily. Can also be a part of =quote= and =example= multiline blocks.)RAW")
    .value("CodeLine_", OrgNodeKind::CodeLine, R"RAW(Single line of source code)RAW")
    .value("CodeText_", OrgNodeKind::CodeText, R"RAW(Block of source code text)RAW")
    .value("CodeTangle_", OrgNodeKind::CodeTangle, R"RAW(Single tangle target in the code block)RAW")
    .value("CodeCallout_", OrgNodeKind::CodeCallout, R"RAW(`(refs:` callout in the source code)RAW")
    .value("QuoteBlock_", OrgNodeKind::QuoteBlock, R"RAW(`#+quote:` block in code)RAW")
    .value("AdmonitionBlock_", OrgNodeKind::AdmonitionBlock)
    .value("CenterBlock_", OrgNodeKind::CenterBlock, R"RAW(')RAW")
    .value("VerseBlock_", OrgNodeKind::VerseBlock)
    .value("Example_", OrgNodeKind::Example, R"RAW(Verbatim example text block)RAW")
    .value("SrcCode_", OrgNodeKind::SrcCode, R"RAW(Block of source code - can be multiline, single-line and)RAW")
    .value("SrcInlineCode_", OrgNodeKind::SrcInlineCode, R"RAW(inline piece of code (such as `src_nim`),. Latter is different from regular monospaced text inside of `~~` pair as it contains additional internal structure, optional parameter for code evaluation etc.)RAW")
    .value("CallCode_", OrgNodeKind::CallCode, R"RAW(Call to named source code block. Inline, multiline, or single-line.)RAW")
    .value("PassCode_", OrgNodeKind::PassCode, R"RAW(Passthrough block. Inline, multiline, or single-line. Syntax is `@@<backend-name>:<any-body>@@`. Has line and block syntax respectively)RAW")
    .value("CmdArguments_", OrgNodeKind::CmdArguments, R"RAW(Command arguments)RAW")
    .value("CmdFlag_", OrgNodeKind::CmdFlag, R"RAW(Flag for source code block. For example `-n`, which is used to to make source code block export with lines)RAW")
    .value("CmdKey_", OrgNodeKind::CmdKey)
    .value("CmdValue_", OrgNodeKind::CmdValue)
    .value("CmdNamedValue_", OrgNodeKind::CmdNamedValue, R"RAW(Key-value pair for source code block call.)RAW")
    .value("UrgencyStatus_", OrgNodeKind::UrgencyStatus, R"RAW(Subtree importance level, such as `[#A]` or `[#B]`. Default org-mode only allows single character for contents inside of `[]`, but this parser makes it possible to use any regular identifier, such as `[#urgent]`.)RAW")
    .value("TextSeparator_", OrgNodeKind::TextSeparator, R"RAW(Long horizontal line `----`)RAW")
    .value("Paragraph_", OrgNodeKind::Paragraph, R"RAW(Single 'paragraph' of text. Used as generic container for any place in AST where unordered sentence might be encountered (e.g. caption, link description) - not limited to actual paragraph)RAW")
    .value("AnnotatedParagraph_", OrgNodeKind::AnnotatedParagraph, R"RAW(Annotated paragraph -- a wrapper around a regular paragraph kind with added admonition, footnote, list tag prefix and similar types. `[fn:ID] Some Text` is an annotated paragraph, just like `NOTE: Text` or `- Prefix :: Body` (in this case list header is an annotated paragraph))RAW")
    .value("Bold_", OrgNodeKind::Bold, R"RAW(Region of text with formatting, which contains standalone words -
     can itself contain subnodes, which allows to represent nested
     formatting regions, such as `*bold /italic/*` text. Particular type
     of identifier is stored in string form in `str` field for `OrgNode`
     -- bold is represented as `"*"`, italic as `/` and so on. In case
     of explicit open/close pairs only opening one is stored.

     NOTE: when structured sentences are enabled, regular punctuation
     elements like `some text (notes)` are also represented as `Word,
     Word, Markup(str: "(", [Word])` - e.g. structure is not fully flat.)RAW")
    .value("Italic_", OrgNodeKind::Italic)
    .value("Verbatim_", OrgNodeKind::Verbatim)
    .value("Backtick_", OrgNodeKind::Backtick)
    .value("Underline_", OrgNodeKind::Underline)
    .value("Strike_", OrgNodeKind::Strike)
    .value("Quote_", OrgNodeKind::Quote)
    .value("Angle_", OrgNodeKind::Angle)
    .value("Monospace_", OrgNodeKind::Monospace)
    .value("Par_", OrgNodeKind::Par)
    .value("InlineMath_", OrgNodeKind::InlineMath, R"RAW(Inline latex math. Contains latex math body - either from `$dollar-wrapped$` or `\(paren-wrapped\)` inline text.)RAW")
    .value("DisplayMath_", OrgNodeKind::DisplayMath, R"RAW(Inline display latex math from `$$double-dollar$$` or `\[bracket-wrapped\]` code.)RAW")
    .value("Space_", OrgNodeKind::Space, R"RAW(Space or tab character in regular text)RAW")
    .value("Punctuation_", OrgNodeKind::Punctuation)
    .value("Colon_", OrgNodeKind::Colon)
    .value("Word_", OrgNodeKind::Word, R"RAW(Regular word - technically not different from `orgIdent`, but defined separately to disiguish between places where special syntax is required and free-form text.)RAW")
    .value("Escaped_", OrgNodeKind::Escaped, R"RAW(Escaped formatting character in the text)RAW")
    .value("Newline_", OrgNodeKind::Newline)
    .value("RawLink_", OrgNodeKind::RawLink, R"RAW(Raw unwrapped link that was pasted in text)RAW")
    .value("Link_", OrgNodeKind::Link, R"RAW(External or internal link. Consists of one or two elements - target
     (url, file location etc.) and description (`orgParagraph` of text).
     Description might be empty, and represented as empty node in this
     case. For external links particular formatting of the address is
     not handled by parser and instead contains raw string from input
     text.)RAW")
    .value("Macro_", OrgNodeKind::Macro, R"RAW(Org-mode macro replacement - during export each macro is expanded
     and evaluated according to it's environment. Body of the macro is
     not parsed fully during org-mode evaluation, but is checked for
     correct parenthesis balance (as macro might contain elisp code))RAW")
    .value("BackendRaw_", OrgNodeKind::BackendRaw, R"RAW(Raw content to be passed to a particular backend. This is the most
     compact way of quoting export strings, after `#+<backend>:
     <single-backend-line>` and `#+begin-export <backend>`
     `<multiple-lines>`.)RAW")
    .value("Symbol_", OrgNodeKind::Symbol, R"RAW(Special symbol that should be exported differently to various backends - greek letters (`lpha`), mathematical notations and so on.)RAW")
    .value("TimeAssoc_", OrgNodeKind::TimeAssoc, R"RAW(Time association pair for the subtree deadlines.)RAW")
    .value("StaticActiveTime_", OrgNodeKind::StaticActiveTime)
    .value("StaticInactiveTime_", OrgNodeKind::StaticInactiveTime)
    .value("DynamicActiveTime_", OrgNodeKind::DynamicActiveTime)
    .value("DynamicInactiveTime_", OrgNodeKind::DynamicInactiveTime, R"RAW(Single date and time entry (active or inactive),, possibly with repeater interval. Is not parsed directly, and instead contains `orgRawText` that can be parsed later)RAW")
    .value("TimeRange_", OrgNodeKind::TimeRange, R"RAW(Date and time range format - two `orgDateTime` entries)RAW")
    .value("SimpleTime_", OrgNodeKind::SimpleTime, R"RAW(Result of the time range evaluation or trailing annotation a subtree)RAW")
    .value("Details_", OrgNodeKind::Details, R"RAW(`#+begin_details`  section)RAW")
    .value("Summary_", OrgNodeKind::Summary, R"RAW(`#+begin_summary` section)RAW")
    .value("Table_", OrgNodeKind::Table, R"RAW(Org-mode table. Tables can be writtein in different formats, but in
   the end they are all represented using single ast type. NOTE: it is
   not guaranteed that all subnodes for table are exactly
   `orgTableRow` - sometimes additional property metadata might be
   used, making AST like `Table[AssocStmtList[Command[_],
   TableRow[_]]]` possible)RAW")
    .value("TableRow_", OrgNodeKind::TableRow, R"RAW(Horizontal table row)RAW")
    .value("TableCell_", OrgNodeKind::TableCell, R"RAW(Single cell in row. Might contain anyting, including other tables, simple text paragraph etc.)RAW")
    .value("InlineFootnote_", OrgNodeKind::InlineFootnote, R"RAW(Inline footnote with text placed directly in the node body.)RAW")
    .value("Footnote_", OrgNodeKind::Footnote, R"RAW(Footnote entry. Just as regular links - internal content is not parsed, and instead just cut out verbatim into target AST node.)RAW")
    .value("Horizontal_", OrgNodeKind::Horizontal, R"RAW(Horizotal rule. Rule body might contain other subnodes, to represnt `---- some text ----` kind of formatting.)RAW")
    .value("Filetags_", OrgNodeKind::Filetags, R"RAW(`#+filetags:` line command)RAW")
    .value("OrgTag_", OrgNodeKind::OrgTag, R"RAW(Original format of org-mode tags in form of `:tagname:`. Might
   contain one or mode identifgiers, but does not provide support for
   nesting - `:tag1:tag2:`. Can only be placed within restricted set
   of places such as subtree headings and has separate place in AST
   when allowed (`orgSubtree` always has subnode `№4` with either
   `orgEmpty` or `orgOrgTag`))RAW")
    .value("HashTag_", OrgNodeKind::HashTag, R"RAW(More commonly used `#hashtag` format, with some additional
   extension. Can be placed anywere in the document (including section
   headers), but does not have separate place in AST (e.g. considered
   regular part of the text))RAW")
    .value("MetaSymbol_", OrgNodeKind::MetaSymbol, R"RAW(`\sym{}` with explicit arguments)RAW")
    .value("AtMention_", OrgNodeKind::AtMention, R"RAW(`@user`)RAW")
    .value("BracTag_", OrgNodeKind::BracTag, R"RAW(Custom extension to org-mode. Similarly to `BigIdent` used to have something like informal keywords `MUST`, `OPTIONAL`, but instead aimed /specifically/ at commit message headers - `[FEATURE]`, `[FIX]` and so on.)RAW")
    .value("Drawer_", OrgNodeKind::Drawer, R"RAW(Single enclosed drawer like `:properties: ... :end:` or `:logbook: ... :end:`)RAW")
    .value("LatexClass_", OrgNodeKind::LatexClass)
    .value("LatexHeader_", OrgNodeKind::LatexHeader)
    .value("LatexCompiler_", OrgNodeKind::LatexCompiler)
    .value("LatexClassOptions_", OrgNodeKind::LatexClassOptions)
    .value("HtmlHead_", OrgNodeKind::HtmlHead)
    .value("Columns_", OrgNodeKind::Columns, R"RAW(`#+columns:` line command for specifying formatting of the org-mode clock table visualization on per-file basis.)RAW")
    .value("CmdPropertyArgs_", OrgNodeKind::CmdPropertyArgs, R"RAW(`#+property:` command)RAW")
    .value("CmdPropertyText_", OrgNodeKind::CmdPropertyText, R"RAW(`#+property:` command)RAW")
    .value("CmdPropertyRaw_", OrgNodeKind::CmdPropertyRaw, R"RAW(`#+property:` command)RAW")
    .value("PropertyList_", OrgNodeKind::PropertyList)
    .value("Property_", OrgNodeKind::Property, R"RAW(`:property:` drawer)RAW")
    .value("Placeholder_", OrgNodeKind::Placeholder, R"RAW(Placeholder entry in text, usually writte like `<text to replace>`)RAW")
    .value("SubtreeDescription_", OrgNodeKind::SubtreeDescription, R"RAW(`:description:` entry)RAW")
    .value("SubtreeUrgency_", OrgNodeKind::SubtreeUrgency)
    .value("Logbook_", OrgNodeKind::Logbook, R"RAW(`:logbook:` entry storing note information)RAW")
    .value("LogbookStateChange_", OrgNodeKind::LogbookStateChange, R"RAW(Annotation about change in the subtree todo state)RAW")
    .value("RadioTarget_", OrgNodeKind::RadioTarget, R"RAW(`<<<RADIO>>>`)RAW")
    .value("Target_", OrgNodeKind::Target, R"RAW(`<<TARGET>>`)RAW")
    ;
  pybind11::enum_<OrgBigIdentKind>(m, "OrgBigIdentKind")
    .value("None_", OrgBigIdentKind::None)
    .value("Must_", OrgBigIdentKind::Must, R"RAW(MUST This word, or the terms "REQUIRED" or "SHALL", mean that the definition is an absolute requirement of the specification.)RAW")
    .value("MustNot_", OrgBigIdentKind::MustNot, R"RAW(MUST NOT This phrase, or the phrase "SHALL NOT", mean that the definition is an absolute prohibition of the specification.)RAW")
    .value("Should_", OrgBigIdentKind::Should, R"RAW(SHOULD This word, or the adjective "RECOMMENDED", mean that there
   may exist valid reasons in particular circumstances to ignore a
   particular item, but the full implications must be understood and
   carefully weighed before choosing a different course.)RAW")
    .value("ShouldNot_", OrgBigIdentKind::ShouldNot, R"RAW(SHOULD NOT This phrase, or the phrase "NOT RECOMMENDED" mean that
   there may exist valid reasons in particular circumstances when the
   particular behavior is acceptable or even useful, but the full
   implications should be understood and the case carefully weighed
   before implementing any behavior described with this label.)RAW")
    .value("Required_", OrgBigIdentKind::Required)
    .value("Optional_", OrgBigIdentKind::Optional, R"RAW(MAY This word, or the adjective "OPTIONAL", mean that an item is
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
    .value("ReallyShouldNot_", OrgBigIdentKind::ReallyShouldNot)
    .value("OughtTo_", OrgBigIdentKind::OughtTo)
    .value("WouldProbably_", OrgBigIdentKind::WouldProbably)
    .value("MayWishTo_", OrgBigIdentKind::MayWishTo)
    .value("Could_", OrgBigIdentKind::Could)
    .value("Might_", OrgBigIdentKind::Might)
    .value("Possible_", OrgBigIdentKind::Possible)
    .value("Todo_", OrgBigIdentKind::Todo)
    .value("Idea_", OrgBigIdentKind::Idea)
    .value("Error_", OrgBigIdentKind::Error)
    .value("Fixme_", OrgBigIdentKind::Fixme)
    .value("Doc_", OrgBigIdentKind::Doc)
    .value("Refactor_", OrgBigIdentKind::Refactor)
    .value("Review_", OrgBigIdentKind::Review)
    .value("Hack_", OrgBigIdentKind::Hack)
    .value("Implement_", OrgBigIdentKind::Implement)
    .value("Example_", OrgBigIdentKind::Example)
    .value("Question_", OrgBigIdentKind::Question)
    .value("Assume_", OrgBigIdentKind::Assume)
    .value("Internal_", OrgBigIdentKind::Internal)
    .value("Design_", OrgBigIdentKind::Design)
    .value("Why_", OrgBigIdentKind::Why)
    .value("Wip_", OrgBigIdentKind::Wip)
    .value("Fix_", OrgBigIdentKind::Fix)
    .value("Clean_", OrgBigIdentKind::Clean)
    .value("Feature_", OrgBigIdentKind::Feature)
    .value("Style_", OrgBigIdentKind::Style)
    .value("Repo_", OrgBigIdentKind::Repo)
    .value("Skip_", OrgBigIdentKind::Skip)
    .value("Break_", OrgBigIdentKind::Break)
    .value("Poc_", OrgBigIdentKind::Poc)
    .value("Next_", OrgBigIdentKind::Next)
    .value("Later_", OrgBigIdentKind::Later)
    .value("Postponed_", OrgBigIdentKind::Postponed)
    .value("Stalled_", OrgBigIdentKind::Stalled)
    .value("Done_", OrgBigIdentKind::Done)
    .value("Partially_", OrgBigIdentKind::Partially)
    .value("Cancelled_", OrgBigIdentKind::Cancelled)
    .value("Failed_", OrgBigIdentKind::Failed)
    .value("Note_", OrgBigIdentKind::Note)
    .value("Tip_", OrgBigIdentKind::Tip)
    .value("Important_", OrgBigIdentKind::Important)
    .value("Caution_", OrgBigIdentKind::Caution)
    .value("Warning_", OrgBigIdentKind::Warning)
    .value("UserCodeComment_", OrgBigIdentKind::UserCodeComment, R"RAW(User-defined comment message)RAW")
    .value("UserCommitMsg_", OrgBigIdentKind::UserCommitMsg, R"RAW(User-defined commit message ident)RAW")
    .value("UserTaskState_", OrgBigIdentKind::UserTaskState, R"RAW(User-defined task state)RAW")
    .value("UserAdmonition_", OrgBigIdentKind::UserAdmonition, R"RAW(User-defined admonition label)RAW")
    .value("Other_", OrgBigIdentKind::Other, R"RAW(User-defined big-idents, not included in default set.)RAW")
    .value("StructIf_", OrgBigIdentKind::StructIf)
    .value("StructAnd_", OrgBigIdentKind::StructAnd)
    .value("StructOr_", OrgBigIdentKind::StructOr)
    .value("StructNot_", OrgBigIdentKind::StructNot)
    .value("StructGet_", OrgBigIdentKind::StructGet)
    .value("StructSet_", OrgBigIdentKind::StructSet)
    .value("StructThen_", OrgBigIdentKind::StructThen)
    .value("StructElse_", OrgBigIdentKind::StructElse)
    .value("StructWhile_", OrgBigIdentKind::StructWhile)
    ;
  pybind11::enum_<OrgSemKind>(m, "OrgSemKind")
    .value("StmtList_", OrgSemKind::StmtList)
    .value("Empty_", OrgSemKind::Empty)
    .value("Row_", OrgSemKind::Row)
    .value("Table_", OrgSemKind::Table)
    .value("HashTag_", OrgSemKind::HashTag)
    .value("Footnote_", OrgSemKind::Footnote)
    .value("Completion_", OrgSemKind::Completion)
    .value("Paragraph_", OrgSemKind::Paragraph)
    .value("Center_", OrgSemKind::Center)
    .value("Caption_", OrgSemKind::Caption)
    .value("CommandGroup_", OrgSemKind::CommandGroup)
    .value("Tblfm_", OrgSemKind::Tblfm)
    .value("Quote_", OrgSemKind::Quote)
    .value("Verse_", OrgSemKind::Verse)
    .value("Example_", OrgSemKind::Example)
    .value("CmdArguments_", OrgSemKind::CmdArguments)
    .value("CmdArgument_", OrgSemKind::CmdArgument)
    .value("Export_", OrgSemKind::Export)
    .value("AdmonitionBlock_", OrgSemKind::AdmonitionBlock)
    .value("Code_", OrgSemKind::Code)
    .value("Time_", OrgSemKind::Time)
    .value("TimeRange_", OrgSemKind::TimeRange)
    .value("Macro_", OrgSemKind::Macro)
    .value("Symbol_", OrgSemKind::Symbol)
    .value("SubtreeLog_", OrgSemKind::SubtreeLog)
    .value("Subtree_", OrgSemKind::Subtree)
    .value("InlineMath_", OrgSemKind::InlineMath)
    .value("Escaped_", OrgSemKind::Escaped)
    .value("Newline_", OrgSemKind::Newline)
    .value("Space_", OrgSemKind::Space)
    .value("Word_", OrgSemKind::Word)
    .value("AtMention_", OrgSemKind::AtMention)
    .value("RawText_", OrgSemKind::RawText)
    .value("Punctuation_", OrgSemKind::Punctuation)
    .value("Placeholder_", OrgSemKind::Placeholder)
    .value("BigIdent_", OrgSemKind::BigIdent)
    .value("Bold_", OrgSemKind::Bold)
    .value("Underline_", OrgSemKind::Underline)
    .value("Monospace_", OrgSemKind::Monospace)
    .value("MarkQuote_", OrgSemKind::MarkQuote)
    .value("Verbatim_", OrgSemKind::Verbatim)
    .value("Italic_", OrgSemKind::Italic)
    .value("Strike_", OrgSemKind::Strike)
    .value("Par_", OrgSemKind::Par)
    .value("List_", OrgSemKind::List)
    .value("ListItem_", OrgSemKind::ListItem)
    .value("Link_", OrgSemKind::Link)
    .value("DocumentOptions_", OrgSemKind::DocumentOptions)
    .value("Document_", OrgSemKind::Document)
    .value("ParseError_", OrgSemKind::ParseError)
    .value("FileTarget_", OrgSemKind::FileTarget)
    .value("TextSeparator_", OrgSemKind::TextSeparator)
    .value("Include_", OrgSemKind::Include)
    .value("DocumentGroup_", OrgSemKind::DocumentGroup)
    ;
  pybind11::class_<OrgExporterJson>(m, "OrgExporterJson")
    .def(pybind11::init<>())
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
    .def(pybind11::init<>())
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
    .def(pybind11::init<>())
    .def("parseFile",
         static_cast<sem::SemId<sem::Document>(OrgContext::*)(std::string)>(&OrgContext::parseFile),
         pybind11::arg("file"))
    .def("parseString",
         static_cast<sem::SemId<sem::Document>(OrgContext::*)(std::string const)>(&OrgContext::parseString),
         pybind11::arg("text"))
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
         static_cast<ExporterPython::Res(ExporterPython::*)(sem::SemId<sem::Org>)>(&ExporterPython::evalTop),
         pybind11::arg("org"))
    .def("eval",
         static_cast<ExporterPython::Res(ExporterPython::*)(sem::SemId<sem::Org>)>(&ExporterPython::eval),
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
    ;
}
/* clang-format on */