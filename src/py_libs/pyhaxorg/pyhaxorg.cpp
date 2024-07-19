/* clang-format off */
#undef slots
#define PYBIND11_DETAILED_ERROR_MESSAGES
#include <pybind11/pybind11.h>
#include <sem/SemOrg.hpp>
#include <pybind11/stl.h>
#include "pyhaxorg_manual_impl.hpp"
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Org>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Org>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::CmdArgument>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::CmdArgument>>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<Str, sem::SemId<sem::CmdArgumentList>>)
PYBIND11_MAKE_OPAQUE(UnorderedMap<Str, sem::SemId<sem::CmdArgumentList>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::ErrorItem>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::ErrorItem>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::HashTag>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::HashTag>>)
PYBIND11_MAKE_OPAQUE(std::vector<Str>)
PYBIND11_MAKE_OPAQUE(Vec<Str>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Symbol::Param>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Symbol::Param>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::BlockCode::Line::Part>)
PYBIND11_MAKE_OPAQUE(Vec<sem::BlockCode::Line::Part>)
PYBIND11_MAKE_OPAQUE(std::vector<int>)
PYBIND11_MAKE_OPAQUE(Vec<int>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::BlockCode::Switch>)
PYBIND11_MAKE_OPAQUE(Vec<sem::BlockCode::Switch>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::BlockCode::Line>)
PYBIND11_MAKE_OPAQUE(Vec<sem::BlockCode::Line>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<Str, Str>)
PYBIND11_MAKE_OPAQUE(UnorderedMap<Str, Str>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::SubtreeLog>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::SubtreeLog>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Subtree::Property>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Subtree::Property>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Subtree::Period>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Subtree::Period>)
PYBIND11_MAKE_OPAQUE(IntSet<sem::Subtree::Period::Kind>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Cell>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Cell>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Row>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Row>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Subtree>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Subtree>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::OrgSelectorCondition>)
PYBIND11_MAKE_OPAQUE(Vec<sem::OrgSelectorCondition>)
PYBIND11_MAKE_OPAQUE(IntSet<OrgSemKind>)
PYBIND11_MAKE_OPAQUE(std::vector<SequenceSegment>)
PYBIND11_MAKE_OPAQUE(Vec<SequenceSegment>)
PYBIND11_MAKE_OPAQUE(std::vector<SequenceAnnotationTag>)
PYBIND11_MAKE_OPAQUE(Vec<SequenceAnnotationTag>)
PYBIND11_MAKE_OPAQUE(std::vector<SequenceAnnotation>)
PYBIND11_MAKE_OPAQUE(Vec<SequenceAnnotation>)
PYBIND11_MAKE_OPAQUE(std::vector<SequenceSegmentGroup>)
PYBIND11_MAKE_OPAQUE(Vec<SequenceSegmentGroup>)
PYBIND11_MODULE(pyhaxorg, m) {
  bind_vector<sem::SemId<sem::Org>>(m, "VecOfSemIdOfOrg");
  bind_vector<sem::SemId<sem::CmdArgument>>(m, "VecOfSemIdOfCmdArgument");
  bind_unordered_map<Str, sem::SemId<sem::CmdArgumentList>>(m, "UnorderedMapOfStrSemIdOfCmdArgumentList");
  bind_vector<sem::SemId<sem::ErrorItem>>(m, "VecOfSemIdOfErrorItem");
  bind_vector<sem::SemId<sem::HashTag>>(m, "VecOfSemIdOfHashTag");
  bind_vector<Str>(m, "VecOfStr");
  bind_vector<sem::Symbol::Param>(m, "VecOfSymbolParam");
  bind_vector<sem::BlockCode::Line::Part>(m, "VecOfBlockCodeLinePart");
  bind_vector<int>(m, "VecOfint");
  bind_vector<sem::BlockCode::Switch>(m, "VecOfBlockCodeSwitch");
  bind_vector<sem::BlockCode::Line>(m, "VecOfBlockCodeLine");
  bind_unordered_map<Str, Str>(m, "UnorderedMapOfStrStr");
  bind_vector<sem::SemId<sem::SubtreeLog>>(m, "VecOfSemIdOfSubtreeLog");
  bind_vector<sem::Subtree::Property>(m, "VecOfSubtreeProperty");
  bind_vector<sem::Subtree::Period>(m, "VecOfSubtreePeriod");
  bind_int_set<sem::Subtree::Period::Kind>(m, "IntSetOfSubtreePeriodKind");
  bind_vector<sem::SemId<sem::Cell>>(m, "VecOfSemIdOfCell");
  bind_vector<sem::SemId<sem::Row>>(m, "VecOfSemIdOfRow");
  bind_vector<sem::SemId<sem::Subtree>>(m, "VecOfSemIdOfSubtree");
  bind_vector<sem::OrgSelectorCondition>(m, "VecOfOrgSelectorCondition");
  bind_int_set<OrgSemKind>(m, "IntSetOfOrgSemKind");
  bind_vector<SequenceSegment>(m, "VecOfSequenceSegment");
  bind_vector<SequenceAnnotationTag>(m, "VecOfSequenceAnnotationTag");
  bind_vector<SequenceAnnotation>(m, "VecOfSequenceAnnotation");
  bind_vector<SequenceSegmentGroup>(m, "VecOfSequenceSegmentGroup");
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
    .def("insert",
         static_cast<void(sem::Org::*)(int, sem::SemId<sem::Org>)>(&sem::Org::insert),
         pybind11::arg("pos"),
         pybind11::arg("node"))
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
    .def("__repr__", [](LineCol _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](LineCol _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdArgument, sem::SemId<sem::CmdArgument>, sem::Org>(m, "CmdArgument")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdArgument {
                        sem::CmdArgument result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("key", &sem::CmdArgument::key, R"RAW(Key)RAW")
    .def_readwrite("varname", &sem::CmdArgument::varname, R"RAW(When used in the `:var` assignment, this stores variable name)RAW")
    .def_readwrite("value", &sem::CmdArgument::value, R"RAW(Value)RAW")
    .def("getInt", static_cast<Opt<int>(sem::CmdArgument::*)() const>(&sem::CmdArgument::getInt), R"RAW(Parse argument as integer value)RAW")
    .def("getBool", static_cast<Opt<bool>(sem::CmdArgument::*)() const>(&sem::CmdArgument::getBool), R"RAW(Get argument as bool)RAW")
    .def("getString", static_cast<Str(sem::CmdArgument::*)() const>(&sem::CmdArgument::getString), R"RAW(Get original string)RAW")
    .def("__repr__", [](sem::CmdArgument _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdArgument _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdArgumentList, sem::SemId<sem::CmdArgumentList>, sem::Org>(m, "CmdArgumentList")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdArgumentList {
                        sem::CmdArgumentList result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("args", &sem::CmdArgumentList::args, R"RAW(List of arguments)RAW")
    .def("__repr__", [](sem::CmdArgumentList _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdArgumentList _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdArguments, sem::SemId<sem::CmdArguments>, sem::Org>(m, "CmdArguments")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdArguments {
                        sem::CmdArguments result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("positional", &sem::CmdArguments::positional, R"RAW(Positional arguments with no keys)RAW")
    .def_readwrite("named", &sem::CmdArguments::named, R"RAW(Stored key-value mapping)RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::CmdArguments::*)(Opt<Str> const&) const>(&sem::CmdArguments::getArguments),
         pybind11::arg_v("key", std::nullopt))
    .def("__repr__", [](sem::CmdArguments _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdArguments _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::ErrorItem, sem::SemId<sem::ErrorItem>, sem::Org>(m, "ErrorItem")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::ErrorItem {
                        sem::ErrorItem result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("message", &sem::ErrorItem::message)
    .def_readwrite("function", &sem::ErrorItem::function, R"RAW(Conversion function name where the error was created)RAW")
    .def_readwrite("line", &sem::ErrorItem::line, R"RAW(Line number for the conversion where the error was created)RAW")
    .def("__repr__", [](sem::ErrorItem _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::ErrorItem _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::ErrorGroup, sem::SemId<sem::ErrorGroup>, sem::Org>(m, "ErrorGroup")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::ErrorGroup {
                        sem::ErrorGroup result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("diagnostics", &sem::ErrorGroup::diagnostics)
    .def_readwrite("function", &sem::ErrorGroup::function, R"RAW(Conversion function name where the error was created)RAW")
    .def_readwrite("line", &sem::ErrorGroup::line, R"RAW(Line number for the conversion where the error was created)RAW")
    .def("__repr__", [](sem::ErrorGroup _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::ErrorGroup _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Stmt, sem::SemId<sem::Stmt>, sem::Org>(m, "Stmt")
    .def_readwrite("attached", &sem::Stmt::attached)
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Stmt::*)(Opt<Str> const&) const>(&sem::Stmt::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::Stmt::*)(Opt<Str> const&) const>(&sem::Stmt::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Stmt::*)(Str const&) const>(&sem::Stmt::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    ;
  pybind11::class_<sem::Inline, sem::SemId<sem::Inline>, sem::Org>(m, "Inline")
    ;
  pybind11::class_<sem::StmtList, sem::SemId<sem::StmtList>, sem::Org>(m, "StmtList")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::StmtList {
                        sem::StmtList result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::StmtList _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::StmtList _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Empty, sem::SemId<sem::Empty>, sem::Org>(m, "Empty")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Empty {
                        sem::Empty result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Empty _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Empty _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Cmd, sem::SemId<sem::Cmd>, sem::Stmt>(m, "Cmd")
    .def_readwrite("parameters", &sem::Cmd::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::Cmd::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::Cmd::*)(Opt<Str> const&) const>(&sem::Cmd::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Cmd::*)(Str const&) const>(&sem::Cmd::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Cmd::*)(Opt<Str> const&) const>(&sem::Cmd::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::Cmd::*)(Opt<Str> const&) const>(&sem::Cmd::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Cmd::*)(Str const&) const>(&sem::Cmd::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    ;
  pybind11::class_<sem::Block, sem::SemId<sem::Block>, sem::Cmd>(m, "Block")
    .def_readwrite("parameters", &sem::Block::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::Block::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::Block::*)(Opt<Str> const&) const>(&sem::Block::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Block::*)(Str const&) const>(&sem::Block::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Block::*)(Opt<Str> const&) const>(&sem::Block::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::Block::*)(Opt<Str> const&) const>(&sem::Block::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Block::*)(Str const&) const>(&sem::Block::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    ;
  pybind11::class_<sem::LineCommand, sem::SemId<sem::LineCommand>, sem::Cmd>(m, "LineCommand")
    .def_readwrite("parameters", &sem::LineCommand::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::LineCommand::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::LineCommand::*)(Opt<Str> const&) const>(&sem::LineCommand::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::LineCommand::*)(Str const&) const>(&sem::LineCommand::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::LineCommand::*)(Opt<Str> const&) const>(&sem::LineCommand::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::LineCommand::*)(Opt<Str> const&) const>(&sem::LineCommand::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::LineCommand::*)(Str const&) const>(&sem::LineCommand::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    ;
  pybind11::class_<sem::Attached, sem::SemId<sem::Attached>, sem::LineCommand>(m, "Attached")
    .def_readwrite("parameters", &sem::Attached::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::Attached::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::Attached::*)(Opt<Str> const&) const>(&sem::Attached::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Attached::*)(Str const&) const>(&sem::Attached::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Attached::*)(Opt<Str> const&) const>(&sem::Attached::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::Attached::*)(Opt<Str> const&) const>(&sem::Attached::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Attached::*)(Str const&) const>(&sem::Attached::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    ;
  pybind11::class_<sem::Leaf, sem::SemId<sem::Leaf>, sem::Org>(m, "Leaf")
    .def_readwrite("text", &sem::Leaf::text, R"RAW(Final leaf value)RAW")
    ;
  pybind11::class_<sem::CmdCaption, sem::SemId<sem::CmdCaption>, sem::Attached>(m, "CmdCaption")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdCaption {
                        sem::CmdCaption result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::CmdCaption::text, R"RAW(Content description)RAW")
    .def_readwrite("parameters", &sem::CmdCaption::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::CmdCaption::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::CmdCaption::*)(Opt<Str> const&) const>(&sem::CmdCaption::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::CmdCaption::*)(Str const&) const>(&sem::CmdCaption::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdCaption::*)(Opt<Str> const&) const>(&sem::CmdCaption::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::CmdCaption::*)(Opt<Str> const&) const>(&sem::CmdCaption::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::CmdCaption::*)(Str const&) const>(&sem::CmdCaption::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::CmdCaption _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdCaption _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdName, sem::SemId<sem::CmdName>, sem::Attached>(m, "CmdName")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdName {
                        sem::CmdName result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::CmdName::name)
    .def_readwrite("parameters", &sem::CmdName::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::CmdName::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::CmdName::*)(Opt<Str> const&) const>(&sem::CmdName::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::CmdName::*)(Str const&) const>(&sem::CmdName::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdName::*)(Opt<Str> const&) const>(&sem::CmdName::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::CmdName::*)(Opt<Str> const&) const>(&sem::CmdName::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::CmdName::*)(Str const&) const>(&sem::CmdName::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::CmdName _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdName _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdCustomArgs, sem::SemId<sem::CmdCustomArgs>, sem::Cmd>(m, "CmdCustomArgs")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdCustomArgs {
                        sem::CmdCustomArgs result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::CmdCustomArgs::name)
    .def_readwrite("isAttached", &sem::CmdCustomArgs::isAttached)
    .def_readwrite("parameters", &sem::CmdCustomArgs::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::CmdCustomArgs::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::CmdCustomArgs::*)(Opt<Str> const&) const>(&sem::CmdCustomArgs::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::CmdCustomArgs::*)(Str const&) const>(&sem::CmdCustomArgs::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdCustomArgs::*)(Opt<Str> const&) const>(&sem::CmdCustomArgs::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::CmdCustomArgs::*)(Opt<Str> const&) const>(&sem::CmdCustomArgs::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::CmdCustomArgs::*)(Str const&) const>(&sem::CmdCustomArgs::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::CmdCustomArgs _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdCustomArgs _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdCustomRaw, sem::SemId<sem::CmdCustomRaw>, sem::Stmt>(m, "CmdCustomRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdCustomRaw {
                        sem::CmdCustomRaw result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::CmdCustomRaw::name)
    .def_readwrite("isAttached", &sem::CmdCustomRaw::isAttached)
    .def_readwrite("text", &sem::CmdCustomRaw::text)
    .def_readwrite("attached", &sem::CmdCustomRaw::attached)
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdCustomRaw::*)(Opt<Str> const&) const>(&sem::CmdCustomRaw::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::CmdCustomRaw::*)(Opt<Str> const&) const>(&sem::CmdCustomRaw::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::CmdCustomRaw::*)(Str const&) const>(&sem::CmdCustomRaw::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::CmdCustomRaw _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdCustomRaw _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdCustomText, sem::SemId<sem::CmdCustomText>, sem::Stmt>(m, "CmdCustomText")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdCustomText {
                        sem::CmdCustomText result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::CmdCustomText::name)
    .def_readwrite("isAttached", &sem::CmdCustomText::isAttached)
    .def_readwrite("text", &sem::CmdCustomText::text)
    .def_readwrite("attached", &sem::CmdCustomText::attached)
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdCustomText::*)(Opt<Str> const&) const>(&sem::CmdCustomText::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::CmdCustomText::*)(Opt<Str> const&) const>(&sem::CmdCustomText::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::CmdCustomText::*)(Str const&) const>(&sem::CmdCustomText::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::CmdCustomText _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdCustomText _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdResults, sem::SemId<sem::CmdResults>, sem::Attached>(m, "CmdResults")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdResults {
                        sem::CmdResults result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("parameters", &sem::CmdResults::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::CmdResults::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::CmdResults::*)(Opt<Str> const&) const>(&sem::CmdResults::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::CmdResults::*)(Str const&) const>(&sem::CmdResults::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdResults::*)(Opt<Str> const&) const>(&sem::CmdResults::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::CmdResults::*)(Opt<Str> const&) const>(&sem::CmdResults::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::CmdResults::*)(Str const&) const>(&sem::CmdResults::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::CmdResults _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdResults _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdTblfm, sem::SemId<sem::CmdTblfm>, sem::Cmd>(m, "CmdTblfm")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdTblfm {
                        sem::CmdTblfm result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("parameters", &sem::CmdTblfm::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::CmdTblfm::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::CmdTblfm::*)(Opt<Str> const&) const>(&sem::CmdTblfm::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::CmdTblfm::*)(Str const&) const>(&sem::CmdTblfm::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdTblfm::*)(Opt<Str> const&) const>(&sem::CmdTblfm::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::CmdTblfm::*)(Opt<Str> const&) const>(&sem::CmdTblfm::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::CmdTblfm::*)(Str const&) const>(&sem::CmdTblfm::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::CmdTblfm _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdTblfm _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def("__repr__", [](sem::HashTag _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::HashTag _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Footnote, sem::SemId<sem::Footnote>, sem::Inline>(m, "Footnote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Footnote {
                        sem::Footnote result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("tag", &sem::Footnote::tag, R"RAW(Footnote text target name)RAW")
    .def_readwrite("definition", &sem::Footnote::definition, R"RAW(Link to possibly resolved definition)RAW")
    .def("__repr__", [](sem::Footnote _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Footnote _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def("__repr__", [](sem::Time::Repeat _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Time::Repeat _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Time::Static>(m, "TimeStatic")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Time::Static {
                        sem::Time::Static result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("repeat", &sem::Time::Static::repeat)
    .def_readwrite("time", &sem::Time::Static::time)
    .def("__repr__", [](sem::Time::Static _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Time::Static _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Time::Dynamic>(m, "TimeDynamic")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Time::Dynamic {
                        sem::Time::Dynamic result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("expr", &sem::Time::Dynamic::expr)
    .def("__repr__", [](sem::Time::Dynamic _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Time::Dynamic _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def_static("getTimeKindStatic",
                static_cast<sem::Time::TimeKind(*)(sem::Time::TimeVariant const&)>(&sem::Time::getTimeKind),
                pybind11::arg("__input"))
    .def("getTimeKind", static_cast<sem::Time::TimeKind(sem::Time::*)() const>(&sem::Time::getTimeKind))
    .def("__repr__", [](sem::Time _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Time _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::TimeRange, sem::SemId<sem::TimeRange>, sem::Org>(m, "TimeRange")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::TimeRange {
                        sem::TimeRange result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("from_", &sem::TimeRange::from, R"RAW(Starting time)RAW")
    .def_readwrite("to", &sem::TimeRange::to, R"RAW(Finishing time)RAW")
    .def("__repr__", [](sem::TimeRange _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::TimeRange _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Macro, sem::SemId<sem::Macro>, sem::Org>(m, "Macro")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Macro {
                        sem::Macro result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::Macro::name, R"RAW(Macro name)RAW")
    .def_readwrite("parameters", &sem::Macro::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def("__repr__", [](sem::Macro _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Macro _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Symbol::Param>(m, "SymbolParam")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Symbol::Param {
                        sem::Symbol::Param result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("key", &sem::Symbol::Param::key, R"RAW(Key -- for non-positional)RAW")
    .def_readwrite("value", &sem::Symbol::Param::value, R"RAW(Uninterpreted value)RAW")
    .def("__repr__", [](sem::Symbol::Param _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Symbol::Param _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def("__repr__", [](sem::Symbol _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Symbol _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Escaped, sem::SemId<sem::Escaped>, sem::Leaf>(m, "Escaped")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Escaped {
                        sem::Escaped result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Escaped::text, R"RAW(Final leaf value)RAW")
    .def("__repr__", [](sem::Escaped _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Escaped _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Newline, sem::SemId<sem::Newline>, sem::Leaf>(m, "Newline")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Newline {
                        sem::Newline result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Newline::text, R"RAW(Final leaf value)RAW")
    .def("__repr__", [](sem::Newline _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Newline _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Space, sem::SemId<sem::Space>, sem::Leaf>(m, "Space")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Space {
                        sem::Space result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Space::text, R"RAW(Final leaf value)RAW")
    .def("__repr__", [](sem::Space _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Space _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Word, sem::SemId<sem::Word>, sem::Leaf>(m, "Word")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Word {
                        sem::Word result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Word::text, R"RAW(Final leaf value)RAW")
    .def("__repr__", [](sem::Word _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Word _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::AtMention, sem::SemId<sem::AtMention>, sem::Leaf>(m, "AtMention")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::AtMention {
                        sem::AtMention result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::AtMention::text, R"RAW(Final leaf value)RAW")
    .def("__repr__", [](sem::AtMention _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::AtMention _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::RawText, sem::SemId<sem::RawText>, sem::Leaf>(m, "RawText")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::RawText {
                        sem::RawText result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::RawText::text, R"RAW(Final leaf value)RAW")
    .def("__repr__", [](sem::RawText _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::RawText _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Punctuation, sem::SemId<sem::Punctuation>, sem::Leaf>(m, "Punctuation")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Punctuation {
                        sem::Punctuation result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Punctuation::text, R"RAW(Final leaf value)RAW")
    .def("__repr__", [](sem::Punctuation _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Punctuation _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Placeholder, sem::SemId<sem::Placeholder>, sem::Leaf>(m, "Placeholder")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Placeholder {
                        sem::Placeholder result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Placeholder::text, R"RAW(Final leaf value)RAW")
    .def("__repr__", [](sem::Placeholder _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Placeholder _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BigIdent, sem::SemId<sem::BigIdent>, sem::Leaf>(m, "BigIdent")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BigIdent {
                        sem::BigIdent result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::BigIdent::text, R"RAW(Final leaf value)RAW")
    .def("__repr__", [](sem::BigIdent _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BigIdent _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::RadioTarget, sem::SemId<sem::RadioTarget>, sem::Leaf>(m, "RadioTarget")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::RadioTarget {
                        sem::RadioTarget result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::RadioTarget::text, R"RAW(Final leaf value)RAW")
    .def("__repr__", [](sem::RadioTarget _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::RadioTarget _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::TextTarget, sem::SemId<sem::TextTarget>, sem::Leaf>(m, "TextTarget")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::TextTarget {
                        sem::TextTarget result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::TextTarget::text, R"RAW(Final leaf value)RAW")
    .def("__repr__", [](sem::TextTarget _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::TextTarget _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Markup, sem::SemId<sem::Markup>, sem::Org>(m, "Markup")
    ;
  pybind11::class_<sem::Bold, sem::SemId<sem::Bold>, sem::Markup>(m, "Bold")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Bold {
                        sem::Bold result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Bold _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Bold _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Underline, sem::SemId<sem::Underline>, sem::Markup>(m, "Underline")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Underline {
                        sem::Underline result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Underline _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Underline _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Monospace, sem::SemId<sem::Monospace>, sem::Markup>(m, "Monospace")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Monospace {
                        sem::Monospace result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Monospace _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Monospace _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::MarkQuote, sem::SemId<sem::MarkQuote>, sem::Markup>(m, "MarkQuote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::MarkQuote {
                        sem::MarkQuote result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::MarkQuote _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::MarkQuote _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Verbatim, sem::SemId<sem::Verbatim>, sem::Markup>(m, "Verbatim")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Verbatim {
                        sem::Verbatim result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Verbatim _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Verbatim _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Italic, sem::SemId<sem::Italic>, sem::Markup>(m, "Italic")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Italic {
                        sem::Italic result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Italic _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Italic _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Strike, sem::SemId<sem::Strike>, sem::Markup>(m, "Strike")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Strike {
                        sem::Strike result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Strike _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Strike _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Par, sem::SemId<sem::Par>, sem::Markup>(m, "Par")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Par {
                        sem::Par result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Par _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Par _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Latex, sem::SemId<sem::Latex>, sem::Org>(m, "Latex")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Latex {
                        sem::Latex result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Latex _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Latex _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Link::Raw>(m, "LinkRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Raw {
                        sem::Link::Raw result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Link::Raw::text)
    .def("__repr__", [](sem::Link::Raw _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link::Raw _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Link::Id>(m, "LinkId")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Id {
                        sem::Link::Id result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Link::Id::text)
    .def("__repr__", [](sem::Link::Id _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link::Id _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Link::Person>(m, "LinkPerson")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Person {
                        sem::Link::Person result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::Link::Person::name)
    .def("__repr__", [](sem::Link::Person _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link::Person _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Link::UserProtocol>(m, "LinkUserProtocol")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::UserProtocol {
                        sem::Link::UserProtocol result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("protocol", &sem::Link::UserProtocol::protocol)
    .def_readwrite("target", &sem::Link::UserProtocol::target)
    .def("__repr__", [](sem::Link::UserProtocol _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link::UserProtocol _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Link::Internal>(m, "LinkInternal")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Internal {
                        sem::Link::Internal result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &sem::Link::Internal::target)
    .def("__repr__", [](sem::Link::Internal _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link::Internal _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Link::Footnote>(m, "LinkFootnote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Footnote {
                        sem::Link::Footnote result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &sem::Link::Footnote::target)
    .def("__repr__", [](sem::Link::Footnote _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link::Footnote _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Link::File>(m, "LinkFile")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::File {
                        sem::Link::File result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("file", &sem::Link::File::file)
    .def("__repr__", [](sem::Link::File _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link::File _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Link::Attachment>(m, "LinkAttachment")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Attachment {
                        sem::Link::Attachment result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("file", &sem::Link::Attachment::file)
    .def("__repr__", [](sem::Link::Attachment _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link::Attachment _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .value("Attachment", sem::Link::Kind::Attachment)
    .def("__iter__", [](sem::Link::Kind _self) -> PyEnumIterator<sem::Link::Kind> {
                     return
                     PyEnumIterator<sem::Link::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::Link, sem::SemId<sem::Link>, sem::Stmt>(m, "Link")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link {
                        sem::Link result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("description", &sem::Link::description)
    .def_readwrite("data", &sem::Link::data)
    .def_readwrite("attached", &sem::Link::attached)
    .def("getRaw", static_cast<sem::Link::Raw&(sem::Link::*)()>(&sem::Link::getRaw))
    .def("getId", static_cast<sem::Link::Id&(sem::Link::*)()>(&sem::Link::getId))
    .def("getPerson", static_cast<sem::Link::Person&(sem::Link::*)()>(&sem::Link::getPerson))
    .def("getUserProtocol", static_cast<sem::Link::UserProtocol&(sem::Link::*)()>(&sem::Link::getUserProtocol))
    .def("getInternal", static_cast<sem::Link::Internal&(sem::Link::*)()>(&sem::Link::getInternal))
    .def("getFootnote", static_cast<sem::Link::Footnote&(sem::Link::*)()>(&sem::Link::getFootnote))
    .def("getFile", static_cast<sem::Link::File&(sem::Link::*)()>(&sem::Link::getFile))
    .def("getAttachment", static_cast<sem::Link::Attachment&(sem::Link::*)()>(&sem::Link::getAttachment))
    .def_static("getLinkKindStatic",
                static_cast<sem::Link::Kind(*)(sem::Link::Data const&)>(&sem::Link::getLinkKind),
                pybind11::arg("__input"))
    .def("getLinkKind", static_cast<sem::Link::Kind(sem::Link::*)() const>(&sem::Link::getLinkKind))
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Link::*)(Opt<Str> const&) const>(&sem::Link::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::Link::*)(Opt<Str> const&) const>(&sem::Link::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Link::*)(Str const&) const>(&sem::Link::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::Link _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCenter, sem::SemId<sem::BlockCenter>, sem::Block>(m, "BlockCenter")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCenter {
                        sem::BlockCenter result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("parameters", &sem::BlockCenter::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::BlockCenter::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::BlockCenter::*)(Opt<Str> const&) const>(&sem::BlockCenter::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::BlockCenter::*)(Str const&) const>(&sem::BlockCenter::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockCenter::*)(Opt<Str> const&) const>(&sem::BlockCenter::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::BlockCenter::*)(Opt<Str> const&) const>(&sem::BlockCenter::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::BlockCenter::*)(Str const&) const>(&sem::BlockCenter::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockCenter _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCenter _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockQuote, sem::SemId<sem::BlockQuote>, sem::Block>(m, "BlockQuote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockQuote {
                        sem::BlockQuote result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("parameters", &sem::BlockQuote::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::BlockQuote::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::BlockQuote::*)(Opt<Str> const&) const>(&sem::BlockQuote::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::BlockQuote::*)(Str const&) const>(&sem::BlockQuote::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockQuote::*)(Opt<Str> const&) const>(&sem::BlockQuote::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::BlockQuote::*)(Opt<Str> const&) const>(&sem::BlockQuote::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::BlockQuote::*)(Str const&) const>(&sem::BlockQuote::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockQuote _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockQuote _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockComment, sem::SemId<sem::BlockComment>, sem::Stmt>(m, "BlockComment")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockComment {
                        sem::BlockComment result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attached", &sem::BlockComment::attached)
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockComment::*)(Opt<Str> const&) const>(&sem::BlockComment::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::BlockComment::*)(Opt<Str> const&) const>(&sem::BlockComment::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::BlockComment::*)(Str const&) const>(&sem::BlockComment::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockComment _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockComment _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockVerse, sem::SemId<sem::BlockVerse>, sem::Block>(m, "BlockVerse")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockVerse {
                        sem::BlockVerse result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("parameters", &sem::BlockVerse::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::BlockVerse::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::BlockVerse::*)(Opt<Str> const&) const>(&sem::BlockVerse::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::BlockVerse::*)(Str const&) const>(&sem::BlockVerse::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockVerse::*)(Opt<Str> const&) const>(&sem::BlockVerse::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::BlockVerse::*)(Opt<Str> const&) const>(&sem::BlockVerse::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::BlockVerse::*)(Str const&) const>(&sem::BlockVerse::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockVerse _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockVerse _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockExample, sem::SemId<sem::BlockExample>, sem::Block>(m, "BlockExample")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockExample {
                        sem::BlockExample result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("parameters", &sem::BlockExample::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::BlockExample::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::BlockExample::*)(Opt<Str> const&) const>(&sem::BlockExample::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::BlockExample::*)(Str const&) const>(&sem::BlockExample::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockExample::*)(Opt<Str> const&) const>(&sem::BlockExample::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::BlockExample::*)(Opt<Str> const&) const>(&sem::BlockExample::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::BlockExample::*)(Str const&) const>(&sem::BlockExample::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockExample _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockExample _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::BlockExport::Format>(m, "BlockExportFormat");
  pybind11::enum_<sem::BlockExport::Format>(m, "BlockExportFormat")
    .value("Inline", sem::BlockExport::Format::Inline, R"RAW(Export directly in the paragraph)RAW")
    .value("Line", sem::BlockExport::Format::Line, R"RAW(Single line of export)RAW")
    .value("Block", sem::BlockExport::Format::Block, R"RAW(Multiple lines of export)RAW")
    .def("__iter__", [](sem::BlockExport::Format _self) -> PyEnumIterator<sem::BlockExport::Format> {
                     return
                     PyEnumIterator<sem::BlockExport::Format>
                     ();
                     })
    ;
  pybind11::class_<sem::BlockExport, sem::SemId<sem::BlockExport>, sem::Block>(m, "BlockExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockExport {
                        sem::BlockExport result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("format", &sem::BlockExport::format, R"RAW(Export block type)RAW")
    .def_readwrite("exporter", &sem::BlockExport::exporter, R"RAW(Exporter backend name)RAW")
    .def_readwrite("placement", &sem::BlockExport::placement, R"RAW(Customized position of the text in the final exporting document.)RAW")
    .def_readwrite("content", &sem::BlockExport::content, R"RAW(Raw exporter content string)RAW")
    .def_readwrite("parameters", &sem::BlockExport::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::BlockExport::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::BlockExport::*)(Opt<Str> const&) const>(&sem::BlockExport::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::BlockExport::*)(Str const&) const>(&sem::BlockExport::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockExport::*)(Opt<Str> const&) const>(&sem::BlockExport::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::BlockExport::*)(Opt<Str> const&) const>(&sem::BlockExport::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::BlockExport::*)(Str const&) const>(&sem::BlockExport::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockExport _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockExport _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockAdmonition, sem::SemId<sem::BlockAdmonition>, sem::Block>(m, "BlockAdmonition")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockAdmonition {
                        sem::BlockAdmonition result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("parameters", &sem::BlockAdmonition::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::BlockAdmonition::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::BlockAdmonition::*)(Opt<Str> const&) const>(&sem::BlockAdmonition::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::BlockAdmonition::*)(Str const&) const>(&sem::BlockAdmonition::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockAdmonition::*)(Opt<Str> const&) const>(&sem::BlockAdmonition::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::BlockAdmonition::*)(Opt<Str> const&) const>(&sem::BlockAdmonition::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::BlockAdmonition::*)(Str const&) const>(&sem::BlockAdmonition::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockAdmonition _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockAdmonition _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCode::Line::Part::Raw>(m, "BlockCodeLinePartRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode::Line::Part::Raw {
                        sem::BlockCode::Line::Part::Raw result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("code", &sem::BlockCode::Line::Part::Raw::code)
    .def("__repr__", [](sem::BlockCode::Line::Part::Raw _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode::Line::Part::Raw _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCode::Line::Part::Callout>(m, "BlockCodeLinePartCallout")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode::Line::Part::Callout {
                        sem::BlockCode::Line::Part::Callout result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::BlockCode::Line::Part::Callout::name)
    .def("__repr__", [](sem::BlockCode::Line::Part::Callout _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode::Line::Part::Callout _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCode::Line::Part::Tangle>(m, "BlockCodeLinePartTangle")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode::Line::Part::Tangle {
                        sem::BlockCode::Line::Part::Tangle result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &sem::BlockCode::Line::Part::Tangle::target)
    .def("__repr__", [](sem::BlockCode::Line::Part::Tangle _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode::Line::Part::Tangle _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::BlockCode::Line::Part::Kind>(m, "BlockCodeLinePartKind");
  pybind11::enum_<sem::BlockCode::Line::Part::Kind>(m, "BlockCodeLinePartKind")
    .value("Raw", sem::BlockCode::Line::Part::Kind::Raw)
    .value("Callout", sem::BlockCode::Line::Part::Kind::Callout)
    .value("Tangle", sem::BlockCode::Line::Part::Kind::Tangle)
    .def("__iter__", [](sem::BlockCode::Line::Part::Kind _self) -> PyEnumIterator<sem::BlockCode::Line::Part::Kind> {
                     return
                     PyEnumIterator<sem::BlockCode::Line::Part::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::BlockCode::Line::Part>(m, "BlockCodeLinePart")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode::Line::Part {
                        sem::BlockCode::Line::Part result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &sem::BlockCode::Line::Part::data)
    .def("getRaw", static_cast<sem::BlockCode::Line::Part::Raw&(sem::BlockCode::Line::Part::*)()>(&sem::BlockCode::Line::Part::getRaw))
    .def("getCallout", static_cast<sem::BlockCode::Line::Part::Callout&(sem::BlockCode::Line::Part::*)()>(&sem::BlockCode::Line::Part::getCallout))
    .def("getTangle", static_cast<sem::BlockCode::Line::Part::Tangle&(sem::BlockCode::Line::Part::*)()>(&sem::BlockCode::Line::Part::getTangle))
    .def_static("getKindStatic",
                static_cast<sem::BlockCode::Line::Part::Kind(*)(sem::BlockCode::Line::Part::Data const&)>(&sem::BlockCode::Line::Part::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<sem::BlockCode::Line::Part::Kind(sem::BlockCode::Line::Part::*)() const>(&sem::BlockCode::Line::Part::getKind))
    .def("__repr__", [](sem::BlockCode::Line::Part _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode::Line::Part _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCode::Line>(m, "BlockCodeLine")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode::Line {
                        sem::BlockCode::Line result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("parts", &sem::BlockCode::Line::parts, R"RAW(parts of the single line)RAW")
    .def("__repr__", [](sem::BlockCode::Line _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode::Line _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCode::Switch::LineStart>(m, "BlockCodeSwitchLineStart")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode::Switch::LineStart {
                        sem::BlockCode::Switch::LineStart result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("start", &sem::BlockCode::Switch::LineStart::start, R"RAW(First line number)RAW")
    .def_readwrite("extendLast", &sem::BlockCode::Switch::LineStart::extendLast, R"RAW(Continue numbering from the previous block nstead of starting anew)RAW")
    .def("__repr__", [](sem::BlockCode::Switch::LineStart _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode::Switch::LineStart _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCode::Switch::CalloutFormat>(m, "BlockCodeSwitchCalloutFormat")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode::Switch::CalloutFormat {
                        sem::BlockCode::Switch::CalloutFormat result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("format", &sem::BlockCode::Switch::CalloutFormat::format)
    .def("__repr__", [](sem::BlockCode::Switch::CalloutFormat _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode::Switch::CalloutFormat _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCode::Switch::RemoveCallout>(m, "BlockCodeSwitchRemoveCallout")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode::Switch::RemoveCallout {
                        sem::BlockCode::Switch::RemoveCallout result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("remove", &sem::BlockCode::Switch::RemoveCallout::remove)
    .def("__repr__", [](sem::BlockCode::Switch::RemoveCallout _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode::Switch::RemoveCallout _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCode::Switch::EmphasizeLine>(m, "BlockCodeSwitchEmphasizeLine")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode::Switch::EmphasizeLine {
                        sem::BlockCode::Switch::EmphasizeLine result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("line", &sem::BlockCode::Switch::EmphasizeLine::line)
    .def("__repr__", [](sem::BlockCode::Switch::EmphasizeLine _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode::Switch::EmphasizeLine _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCode::Switch::Dedent>(m, "BlockCodeSwitchDedent")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode::Switch::Dedent {
                        sem::BlockCode::Switch::Dedent result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &sem::BlockCode::Switch::Dedent::value)
    .def("__repr__", [](sem::BlockCode::Switch::Dedent _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode::Switch::Dedent _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::BlockCode::Switch::Kind>(m, "BlockCodeSwitchKind");
  pybind11::enum_<sem::BlockCode::Switch::Kind>(m, "BlockCodeSwitchKind")
    .value("LineStart", sem::BlockCode::Switch::Kind::LineStart)
    .value("CalloutFormat", sem::BlockCode::Switch::Kind::CalloutFormat)
    .value("RemoveCallout", sem::BlockCode::Switch::Kind::RemoveCallout)
    .value("EmphasizeLine", sem::BlockCode::Switch::Kind::EmphasizeLine)
    .value("Dedent", sem::BlockCode::Switch::Kind::Dedent)
    .def("__iter__", [](sem::BlockCode::Switch::Kind _self) -> PyEnumIterator<sem::BlockCode::Switch::Kind> {
                     return
                     PyEnumIterator<sem::BlockCode::Switch::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::BlockCode::Switch>(m, "BlockCodeSwitch")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode::Switch {
                        sem::BlockCode::Switch result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &sem::BlockCode::Switch::data)
    .def("getLineStart", static_cast<sem::BlockCode::Switch::LineStart&(sem::BlockCode::Switch::*)()>(&sem::BlockCode::Switch::getLineStart))
    .def("getCalloutFormat", static_cast<sem::BlockCode::Switch::CalloutFormat&(sem::BlockCode::Switch::*)()>(&sem::BlockCode::Switch::getCalloutFormat))
    .def("getRemoveCallout", static_cast<sem::BlockCode::Switch::RemoveCallout&(sem::BlockCode::Switch::*)()>(&sem::BlockCode::Switch::getRemoveCallout))
    .def("getEmphasizeLine", static_cast<sem::BlockCode::Switch::EmphasizeLine&(sem::BlockCode::Switch::*)()>(&sem::BlockCode::Switch::getEmphasizeLine))
    .def("getDedent", static_cast<sem::BlockCode::Switch::Dedent&(sem::BlockCode::Switch::*)()>(&sem::BlockCode::Switch::getDedent))
    .def_static("getKindStatic",
                static_cast<sem::BlockCode::Switch::Kind(*)(sem::BlockCode::Switch::Data const&)>(&sem::BlockCode::Switch::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<sem::BlockCode::Switch::Kind(sem::BlockCode::Switch::*)() const>(&sem::BlockCode::Switch::getKind))
    .def("__repr__", [](sem::BlockCode::Switch _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode::Switch _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::BlockCode::Results>(m, "BlockCodeResults");
  pybind11::enum_<sem::BlockCode::Results>(m, "BlockCodeResults")
    .value("Replace", sem::BlockCode::Results::Replace, R"RAW(Remove old result, replace with new value)RAW")
    .def("__iter__", [](sem::BlockCode::Results _self) -> PyEnumIterator<sem::BlockCode::Results> {
                     return
                     PyEnumIterator<sem::BlockCode::Results>
                     ();
                     })
    ;
  bind_enum_iterator<sem::BlockCode::Exports>(m, "BlockCodeExports");
  pybind11::enum_<sem::BlockCode::Exports>(m, "BlockCodeExports")
    .value("None", sem::BlockCode::Exports::None, R"RAW(Hide both original code and run result)RAW")
    .value("Both", sem::BlockCode::Exports::Both, R"RAW(Show output and code)RAW")
    .value("Code", sem::BlockCode::Exports::Code, R"RAW(Show only code)RAW")
    .value("Results", sem::BlockCode::Exports::Results, R"RAW(Show only evaluation results)RAW")
    .def("__iter__", [](sem::BlockCode::Exports _self) -> PyEnumIterator<sem::BlockCode::Exports> {
                     return
                     PyEnumIterator<sem::BlockCode::Exports>
                     ();
                     })
    ;
  pybind11::class_<sem::BlockCode::EvalResult::None>(m, "BlockCodeEvalResultNone")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode::EvalResult::None {
                        sem::BlockCode::EvalResult::None result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::BlockCode::EvalResult::None _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode::EvalResult::None _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCode::EvalResult::OrgValue>(m, "BlockCodeEvalResultOrgValue")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode::EvalResult::OrgValue {
                        sem::BlockCode::EvalResult::OrgValue result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &sem::BlockCode::EvalResult::OrgValue::value, R"RAW(Parsed value of the evaluation result)RAW")
    .def("__repr__", [](sem::BlockCode::EvalResult::OrgValue _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode::EvalResult::OrgValue _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCode::EvalResult::File>(m, "BlockCodeEvalResultFile")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode::EvalResult::File {
                        sem::BlockCode::EvalResult::File result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("path", &sem::BlockCode::EvalResult::File::path)
    .def("__repr__", [](sem::BlockCode::EvalResult::File _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode::EvalResult::File _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCode::EvalResult::Raw>(m, "BlockCodeEvalResultRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode::EvalResult::Raw {
                        sem::BlockCode::EvalResult::Raw result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::BlockCode::EvalResult::Raw::text)
    .def("__repr__", [](sem::BlockCode::EvalResult::Raw _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode::EvalResult::Raw _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::BlockCode::EvalResult::Kind>(m, "BlockCodeEvalResultKind");
  pybind11::enum_<sem::BlockCode::EvalResult::Kind>(m, "BlockCodeEvalResultKind")
    .value("None", sem::BlockCode::EvalResult::Kind::None)
    .value("OrgValue", sem::BlockCode::EvalResult::Kind::OrgValue)
    .value("File", sem::BlockCode::EvalResult::Kind::File)
    .value("Raw", sem::BlockCode::EvalResult::Kind::Raw)
    .def("__iter__", [](sem::BlockCode::EvalResult::Kind _self) -> PyEnumIterator<sem::BlockCode::EvalResult::Kind> {
                     return
                     PyEnumIterator<sem::BlockCode::EvalResult::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::BlockCode::EvalResult>(m, "BlockCodeEvalResult")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode::EvalResult {
                        sem::BlockCode::EvalResult result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &sem::BlockCode::EvalResult::data)
    .def("getNone", static_cast<sem::BlockCode::EvalResult::None&(sem::BlockCode::EvalResult::*)()>(&sem::BlockCode::EvalResult::getNone))
    .def("getOrgValue", static_cast<sem::BlockCode::EvalResult::OrgValue&(sem::BlockCode::EvalResult::*)()>(&sem::BlockCode::EvalResult::getOrgValue))
    .def("getFile", static_cast<sem::BlockCode::EvalResult::File&(sem::BlockCode::EvalResult::*)()>(&sem::BlockCode::EvalResult::getFile))
    .def("getRaw", static_cast<sem::BlockCode::EvalResult::Raw&(sem::BlockCode::EvalResult::*)()>(&sem::BlockCode::EvalResult::getRaw))
    .def_static("getKindStatic",
                static_cast<sem::BlockCode::EvalResult::Kind(*)(sem::BlockCode::EvalResult::Data const&)>(&sem::BlockCode::EvalResult::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<sem::BlockCode::EvalResult::Kind(sem::BlockCode::EvalResult::*)() const>(&sem::BlockCode::EvalResult::getKind))
    .def("__repr__", [](sem::BlockCode::EvalResult _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode::EvalResult _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCode, sem::SemId<sem::BlockCode>, sem::Block>(m, "BlockCode")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode {
                        sem::BlockCode result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("lang", &sem::BlockCode::lang, R"RAW(Code block language name)RAW")
    .def_readwrite("switches", &sem::BlockCode::switches, R"RAW(Switch options for block)RAW")
    .def_readwrite("exports", &sem::BlockCode::exports, R"RAW(What to export)RAW")
    .def_readwrite("result", &sem::BlockCode::result, R"RAW(Code evaluation results)RAW")
    .def_readwrite("lines", &sem::BlockCode::lines, R"RAW(Collected code lines)RAW")
    .def_readwrite("cache", &sem::BlockCode::cache, R"RAW(Do cache values?)RAW")
    .def_readwrite("eval", &sem::BlockCode::eval, R"RAW(Eval on export?)RAW")
    .def_readwrite("noweb", &sem::BlockCode::noweb, R"RAW(Web-tangle code on export/run)RAW")
    .def_readwrite("hlines", &sem::BlockCode::hlines, R"RAW(?)RAW")
    .def_readwrite("tangle", &sem::BlockCode::tangle, R"RAW(?)RAW")
    .def_readwrite("parameters", &sem::BlockCode::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::BlockCode::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::BlockCode::*)(Opt<Str> const&) const>(&sem::BlockCode::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::BlockCode::*)(Str const&) const>(&sem::BlockCode::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockCode::*)(Opt<Str> const&) const>(&sem::BlockCode::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::BlockCode::*)(Opt<Str> const&) const>(&sem::BlockCode::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::BlockCode::*)(Str const&) const>(&sem::BlockCode::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockCode _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubtreeLog::DescribedLog>(m, "SubtreeLogDescribedLog")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::DescribedLog {
                        sem::SubtreeLog::DescribedLog result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("desc", &sem::SubtreeLog::DescribedLog::desc, R"RAW(Optional description of the log entry)RAW")
    .def("__repr__", [](sem::SubtreeLog::DescribedLog _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog::DescribedLog _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def("__repr__", [](sem::SubtreeLog::Priority _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog::Priority _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubtreeLog::Note, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogNote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::Note {
                        sem::SubtreeLog::Note result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("on", &sem::SubtreeLog::Note::on, R"RAW(Where log was taken)RAW")
    .def("__repr__", [](sem::SubtreeLog::Note _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog::Note _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubtreeLog::Refile, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogRefile")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::Refile {
                        sem::SubtreeLog::Refile result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("on", &sem::SubtreeLog::Refile::on, R"RAW(When the refiling happened)RAW")
    .def_readwrite("from_", &sem::SubtreeLog::Refile::from, R"RAW(Link to the original subtree)RAW")
    .def("__repr__", [](sem::SubtreeLog::Refile _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog::Refile _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubtreeLog::Clock, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogClock")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::Clock {
                        sem::SubtreeLog::Clock result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("from_", &sem::SubtreeLog::Clock::from, R"RAW(Clock start time)RAW")
    .def_readwrite("to", &sem::SubtreeLog::Clock::to, R"RAW(Optional end of the clock)RAW")
    .def("__repr__", [](sem::SubtreeLog::Clock _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog::Clock _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def("__repr__", [](sem::SubtreeLog::State _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog::State _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def("__repr__", [](sem::SubtreeLog::Tag _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog::Tag _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubtreeLog::Unknown, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogUnknown")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::Unknown {
                        sem::SubtreeLog::Unknown result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::SubtreeLog::Unknown _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog::Unknown _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def_static("getLogKindStatic",
                static_cast<sem::SubtreeLog::Kind(*)(sem::SubtreeLog::LogEntry const&)>(&sem::SubtreeLog::getLogKind),
                pybind11::arg("__input"))
    .def("getLogKind", static_cast<sem::SubtreeLog::Kind(sem::SubtreeLog::*)() const>(&sem::SubtreeLog::getLogKind))
    .def("__repr__", [](sem::SubtreeLog _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def("__repr__", [](sem::Subtree::Period _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Period _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def("__repr__", [](sem::Subtree::Property::Nonblocking _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property::Nonblocking _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Subtree::Property::Trigger>(m, "SubtreePropertyTrigger")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Trigger {
                        sem::Subtree::Property::Trigger result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Subtree::Property::Trigger _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property::Trigger _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Subtree::Property::Origin>(m, "SubtreePropertyOrigin")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Origin {
                        sem::Subtree::Property::Origin result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Subtree::Property::Origin::text)
    .def("__repr__", [](sem::Subtree::Property::Origin _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property::Origin _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Subtree::Property::ExportLatexClass>(m, "SubtreePropertyExportLatexClass")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::ExportLatexClass {
                        sem::Subtree::Property::ExportLatexClass result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("latexClass", &sem::Subtree::Property::ExportLatexClass::latexClass)
    .def("__repr__", [](sem::Subtree::Property::ExportLatexClass _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property::ExportLatexClass _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Subtree::Property::ExportLatexClassOptions>(m, "SubtreePropertyExportLatexClassOptions")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::ExportLatexClassOptions {
                        sem::Subtree::Property::ExportLatexClassOptions result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("options", &sem::Subtree::Property::ExportLatexClassOptions::options)
    .def("__repr__", [](sem::Subtree::Property::ExportLatexClassOptions _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property::ExportLatexClassOptions _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Subtree::Property::ExportLatexHeader>(m, "SubtreePropertyExportLatexHeader")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::ExportLatexHeader {
                        sem::Subtree::Property::ExportLatexHeader result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("header", &sem::Subtree::Property::ExportLatexHeader::header)
    .def("__repr__", [](sem::Subtree::Property::ExportLatexHeader _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property::ExportLatexHeader _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Subtree::Property::ExportLatexCompiler>(m, "SubtreePropertyExportLatexCompiler")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::ExportLatexCompiler {
                        sem::Subtree::Property::ExportLatexCompiler result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("compiler", &sem::Subtree::Property::ExportLatexCompiler::compiler)
    .def("__repr__", [](sem::Subtree::Property::ExportLatexCompiler _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property::ExportLatexCompiler _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Subtree::Property::Ordered>(m, "SubtreePropertyOrdered")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Ordered {
                        sem::Subtree::Property::Ordered result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isOrdered", &sem::Subtree::Property::Ordered::isOrdered)
    .def("__repr__", [](sem::Subtree::Property::Ordered _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property::Ordered _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Subtree::Property::Effort>(m, "SubtreePropertyEffort")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Effort {
                        sem::Subtree::Property::Effort result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("hours", &sem::Subtree::Property::Effort::hours)
    .def_readwrite("minutes", &sem::Subtree::Property::Effort::minutes)
    .def("__repr__", [](sem::Subtree::Property::Effort _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property::Effort _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def("__repr__", [](sem::Subtree::Property::Visibility _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property::Visibility _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Subtree::Property::ExportOptions>(m, "SubtreePropertyExportOptions")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::ExportOptions {
                        sem::Subtree::Property::ExportOptions result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("backend", &sem::Subtree::Property::ExportOptions::backend)
    .def_readwrite("values", &sem::Subtree::Property::ExportOptions::values)
    .def("__repr__", [](sem::Subtree::Property::ExportOptions _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property::ExportOptions _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Subtree::Property::Blocker>(m, "SubtreePropertyBlocker")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Blocker {
                        sem::Subtree::Property::Blocker result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("blockers", &sem::Subtree::Property::Blocker::blockers)
    .def("__repr__", [](sem::Subtree::Property::Blocker _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property::Blocker _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Subtree::Property::Unnumbered>(m, "SubtreePropertyUnnumbered")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Unnumbered {
                        sem::Subtree::Property::Unnumbered result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Subtree::Property::Unnumbered _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property::Unnumbered _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Subtree::Property::Created>(m, "SubtreePropertyCreated")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::Created {
                        sem::Subtree::Property::Created result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("time", &sem::Subtree::Property::Created::time)
    .def("__repr__", [](sem::Subtree::Property::Created _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property::Created _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Subtree::Property::CustomArgs>(m, "SubtreePropertyCustomArgs")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::CustomArgs {
                        sem::Subtree::Property::CustomArgs result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::Subtree::Property::CustomArgs::name, R"RAW(Original name of the property)RAW")
    .def_readwrite("sub", &sem::Subtree::Property::CustomArgs::sub, R"RAW(Property target specialization)RAW")
    .def_readwrite("parameters", &sem::Subtree::Property::CustomArgs::parameters, R"RAW(Property parameters)RAW")
    .def("__repr__", [](sem::Subtree::Property::CustomArgs _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property::CustomArgs _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Subtree::Property::CustomRaw>(m, "SubtreePropertyCustomRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree::Property::CustomRaw {
                        sem::Subtree::Property::CustomRaw result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::Subtree::Property::CustomRaw::name, R"RAW(Original name of the property)RAW")
    .def_readwrite("value", &sem::Subtree::Property::CustomRaw::value, R"RAW(Property value)RAW")
    .def("__repr__", [](sem::Subtree::Property::CustomRaw _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property::CustomRaw _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .value("CustomArgs", sem::Subtree::Property::Kind::CustomArgs)
    .value("CustomRaw", sem::Subtree::Property::Kind::CustomRaw)
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
    .def("getCustomArgs", static_cast<sem::Subtree::Property::CustomArgs&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getCustomArgs))
    .def("getCustomRaw", static_cast<sem::Subtree::Property::CustomRaw&(sem::Subtree::Property::*)()>(&sem::Subtree::Property::getCustomRaw))
    .def_static("getKindStatic",
                static_cast<sem::Subtree::Property::Kind(*)(sem::Subtree::Property::Data const&)>(&sem::Subtree::Property::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<sem::Subtree::Property::Kind(sem::Subtree::Property::*)() const>(&sem::Subtree::Property::getKind))
    .def("__repr__", [](sem::Subtree::Property _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree::Property _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def_readwrite("isComment", &sem::Subtree::isComment, R"RAW(Subtree is annotated with the COMMENT keyword)RAW")
    .def_readwrite("isArchived", &sem::Subtree::isArchived, R"RAW(Subtree is tagged with `:ARCHIVE:` tag)RAW")
    .def_readwrite("priority", &sem::Subtree::priority)
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
    .def("removeProperty",
         static_cast<void(sem::Subtree::*)(Str const&, Opt<Str> const&)>(&sem::Subtree::removeProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", std::nullopt),
         R"RAW(Remove all instances of the property with matching kind/subkind from the property list)RAW")
    .def("setProperty",
         static_cast<void(sem::Subtree::*)(sem::Subtree::Property const&)>(&sem::Subtree::setProperty),
         pybind11::arg("value"),
         R"RAW(Create or override existing property value in the subtree property list)RAW")
    .def("setPropertyStrValue",
         static_cast<void(sem::Subtree::*)(Str const&, Str const&, Opt<Str> const&)>(&sem::Subtree::setPropertyStrValue),
         pybind11::arg("value"),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", std::nullopt),
         R"RAW(Assign a raw string literal to a property.)RAW")
    .def("__repr__", [](sem::Subtree _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubtreeCompletion, sem::SemId<sem::SubtreeCompletion>, sem::Inline>(m, "SubtreeCompletion")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeCompletion {
                        sem::SubtreeCompletion result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("done", &sem::SubtreeCompletion::done, R"RAW(Number of completed tasks)RAW")
    .def_readwrite("full", &sem::SubtreeCompletion::full, R"RAW(Full number of tasks)RAW")
    .def_readwrite("isPercent", &sem::SubtreeCompletion::isPercent, R"RAW(Use fraction or percent to display completion)RAW")
    .def("__repr__", [](sem::SubtreeCompletion _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeCompletion _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Cell, sem::SemId<sem::Cell>, sem::Cmd>(m, "Cell")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Cell {
                        sem::Cell result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isBlock", &sem::Cell::isBlock, R"RAW(Single-line pipe cell or `#+cell:` command)RAW")
    .def_readwrite("parameters", &sem::Cell::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::Cell::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::Cell::*)(Opt<Str> const&) const>(&sem::Cell::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Cell::*)(Str const&) const>(&sem::Cell::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Cell::*)(Opt<Str> const&) const>(&sem::Cell::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::Cell::*)(Opt<Str> const&) const>(&sem::Cell::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Cell::*)(Str const&) const>(&sem::Cell::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::Cell _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Cell _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Row, sem::SemId<sem::Row>, sem::Cmd>(m, "Row")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Row {
                        sem::Row result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("cells", &sem::Row::cells, R"RAW(List of cells on the row)RAW")
    .def_readwrite("isBlock", &sem::Row::isBlock, R"RAW(Single-line pipe cell or `#+cell:` command)RAW")
    .def_readwrite("parameters", &sem::Row::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::Row::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::Row::*)(Opt<Str> const&) const>(&sem::Row::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Row::*)(Str const&) const>(&sem::Row::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Row::*)(Opt<Str> const&) const>(&sem::Row::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::Row::*)(Opt<Str> const&) const>(&sem::Row::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Row::*)(Str const&) const>(&sem::Row::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::Row _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Row _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Table, sem::SemId<sem::Table>, sem::Block>(m, "Table")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Table {
                        sem::Table result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("rows", &sem::Table::rows, R"RAW(List of rows for the table)RAW")
    .def_readwrite("isBlock", &sem::Table::isBlock, R"RAW(Single-line pipe cell or `#+cell:` command)RAW")
    .def_readwrite("parameters", &sem::Table::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::Table::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::Table::*)(Opt<Str> const&) const>(&sem::Table::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Table::*)(Str const&) const>(&sem::Table::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Table::*)(Opt<Str> const&) const>(&sem::Table::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::Table::*)(Opt<Str> const&) const>(&sem::Table::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Table::*)(Str const&) const>(&sem::Table::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::Table _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Table _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Paragraph, sem::SemId<sem::Paragraph>, sem::Stmt>(m, "Paragraph")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Paragraph {
                        sem::Paragraph result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attached", &sem::Paragraph::attached)
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Paragraph::*)(Opt<Str> const&) const>(&sem::Paragraph::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::Paragraph::*)(Opt<Str> const&) const>(&sem::Paragraph::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::Paragraph::*)(Str const&) const>(&sem::Paragraph::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::Paragraph _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Paragraph _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::AnnotatedParagraph::None>(m, "AnnotatedParagraphNone")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::AnnotatedParagraph::None {
                        sem::AnnotatedParagraph::None result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::AnnotatedParagraph::None _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::AnnotatedParagraph::None _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::AnnotatedParagraph::Footnote>(m, "AnnotatedParagraphFootnote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::AnnotatedParagraph::Footnote {
                        sem::AnnotatedParagraph::Footnote result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::AnnotatedParagraph::Footnote::name)
    .def("__repr__", [](sem::AnnotatedParagraph::Footnote _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::AnnotatedParagraph::Footnote _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::AnnotatedParagraph::Admonition>(m, "AnnotatedParagraphAdmonition")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::AnnotatedParagraph::Admonition {
                        sem::AnnotatedParagraph::Admonition result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::AnnotatedParagraph::Admonition::name, R"RAW(Prefix admonition for the paragraph)RAW")
    .def("__repr__", [](sem::AnnotatedParagraph::Admonition _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::AnnotatedParagraph::Admonition _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::AnnotatedParagraph::Timestamp>(m, "AnnotatedParagraphTimestamp")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::AnnotatedParagraph::Timestamp {
                        sem::AnnotatedParagraph::Timestamp result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("time", &sem::AnnotatedParagraph::Timestamp::time, R"RAW(Leading timestamp for the paragraph)RAW")
    .def("__repr__", [](sem::AnnotatedParagraph::Timestamp _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::AnnotatedParagraph::Timestamp _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def_static("getAnnotationKindStatic",
                static_cast<sem::AnnotatedParagraph::AnnotationKind(*)(sem::AnnotatedParagraph::Data const&)>(&sem::AnnotatedParagraph::getAnnotationKind),
                pybind11::arg("__input"))
    .def("getAnnotationKind", static_cast<sem::AnnotatedParagraph::AnnotationKind(sem::AnnotatedParagraph::*)() const>(&sem::AnnotatedParagraph::getAnnotationKind))
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::AnnotatedParagraph::*)(Opt<Str> const&) const>(&sem::AnnotatedParagraph::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::AnnotatedParagraph::*)(Opt<Str> const&) const>(&sem::AnnotatedParagraph::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::AnnotatedParagraph::*)(Str const&) const>(&sem::AnnotatedParagraph::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::AnnotatedParagraph _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::AnnotatedParagraph _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::ColonExample, sem::SemId<sem::ColonExample>, sem::Org>(m, "ColonExample")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::ColonExample {
                        sem::ColonExample result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::ColonExample _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::ColonExample _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdAttr, sem::SemId<sem::CmdAttr>, sem::Attached>(m, "CmdAttr")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdAttr {
                        sem::CmdAttr result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &sem::CmdAttr::target)
    .def_readwrite("parameters", &sem::CmdAttr::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::CmdAttr::attached)
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::CmdAttr::*)(Opt<Str> const&) const>(&sem::CmdAttr::getArguments),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::CmdAttr::*)(Str const&) const>(&sem::CmdAttr::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdAttr::*)(Opt<Str> const&) const>(&sem::CmdAttr::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::CmdAttr::*)(Opt<Str> const&) const>(&sem::CmdAttr::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::CmdAttr::*)(Str const&) const>(&sem::CmdAttr::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::CmdAttr _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdAttr _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Call, sem::SemId<sem::Call>, sem::Org>(m, "Call")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Call {
                        sem::Call result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::Call::name, R"RAW(Call target name)RAW")
    .def_readwrite("parameters", &sem::Call::parameters, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("isCommand", &sem::Call::isCommand)
    .def("__repr__", [](sem::Call _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Call _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::List, sem::SemId<sem::List>, sem::Stmt>(m, "List")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::List {
                        sem::List result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attached", &sem::List::attached)
    .def("isDescriptionList", static_cast<bool(sem::List::*)() const>(&sem::List::isDescriptionList), R"RAW(List is marked as description if any list item has a header)RAW")
    .def("isNumberedList", static_cast<bool(sem::List::*)() const>(&sem::List::isNumberedList), R"RAW(List is marked as numbered if any list item has bullet text set)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::List::*)(Opt<Str> const&) const>(&sem::List::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getArguments",
         static_cast<Opt<sem::SemId<sem::CmdArgumentList>>(sem::List::*)(Opt<Str> const&) const>(&sem::List::getArguments),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstArgument",
         static_cast<Opt<sem::SemId<sem::CmdArgument>>(sem::List::*)(Str const&) const>(&sem::List::getFirstArgument),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::List _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::List _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def_readwrite("header", &sem::ListItem::header, R"RAW(Description list item header)RAW")
    .def_readwrite("bullet", &sem::ListItem::bullet, R"RAW(Full text of the numbered list item, e.g. `a)`, `a.`)RAW")
    .def("isDescriptionItem", static_cast<bool(sem::ListItem::*)() const>(&sem::ListItem::isDescriptionItem))
    .def("__repr__", [](sem::ListItem _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::ListItem _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::DocumentOptions::ExportConfig::TaskExport>(m, "DocumentOptionsExportConfigTaskExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentOptions::ExportConfig::TaskExport {
                        sem::DocumentOptions::ExportConfig::TaskExport result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("taskWhitelist", &sem::DocumentOptions::ExportConfig::TaskExport::taskWhitelist)
    .def("__repr__", [](sem::DocumentOptions::ExportConfig::TaskExport _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::DocumentOptions::ExportConfig::TaskExport _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::DocumentOptions::ExportConfig::TagExport>(m, "DocumentOptionsExportConfigTagExport");
  pybind11::enum_<sem::DocumentOptions::ExportConfig::TagExport>(m, "DocumentOptionsExportConfigTagExport")
    .value("None", sem::DocumentOptions::ExportConfig::TagExport::None)
    .value("All", sem::DocumentOptions::ExportConfig::TagExport::All)
    .value("NotInToc", sem::DocumentOptions::ExportConfig::TagExport::NotInToc, R"RAW(Expot tags in subtree titles but not in the table of content)RAW")
    .def("__iter__", [](sem::DocumentOptions::ExportConfig::TagExport _self) -> PyEnumIterator<sem::DocumentOptions::ExportConfig::TagExport> {
                     return
                     PyEnumIterator<sem::DocumentOptions::ExportConfig::TagExport>
                     ();
                     })
    ;
  bind_enum_iterator<sem::DocumentOptions::ExportConfig::TaskFiltering>(m, "DocumentOptionsExportConfigTaskFiltering");
  pybind11::enum_<sem::DocumentOptions::ExportConfig::TaskFiltering>(m, "DocumentOptionsExportConfigTaskFiltering")
    .value("Whitelist", sem::DocumentOptions::ExportConfig::TaskFiltering::Whitelist, R"RAW(Include tasks from the whitelist)RAW")
    .value("Done", sem::DocumentOptions::ExportConfig::TaskFiltering::Done, R"RAW(Include tasks marked as done)RAW")
    .value("None", sem::DocumentOptions::ExportConfig::TaskFiltering::None, R"RAW(Exclude all task subtrees from export)RAW")
    .value("All", sem::DocumentOptions::ExportConfig::TaskFiltering::All, R"RAW(Add all task subtrees to export)RAW")
    .def("__iter__", [](sem::DocumentOptions::ExportConfig::TaskFiltering _self) -> PyEnumIterator<sem::DocumentOptions::ExportConfig::TaskFiltering> {
                     return
                     PyEnumIterator<sem::DocumentOptions::ExportConfig::TaskFiltering>
                     ();
                     })
    ;
  bind_enum_iterator<sem::DocumentOptions::ExportConfig::BrokenLinks>(m, "DocumentOptionsExportConfigBrokenLinks");
  pybind11::enum_<sem::DocumentOptions::ExportConfig::BrokenLinks>(m, "DocumentOptionsExportConfigBrokenLinks")
    .value("Raise", sem::DocumentOptions::ExportConfig::BrokenLinks::Raise)
    .value("Ignore", sem::DocumentOptions::ExportConfig::BrokenLinks::Ignore)
    .value("Mark", sem::DocumentOptions::ExportConfig::BrokenLinks::Mark)
    .def("__iter__", [](sem::DocumentOptions::ExportConfig::BrokenLinks _self) -> PyEnumIterator<sem::DocumentOptions::ExportConfig::BrokenLinks> {
                     return
                     PyEnumIterator<sem::DocumentOptions::ExportConfig::BrokenLinks>
                     ();
                     })
    ;
  pybind11::class_<sem::DocumentOptions::ExportConfig::DoExport>(m, "DocumentOptionsExportConfigDoExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentOptions::ExportConfig::DoExport {
                        sem::DocumentOptions::ExportConfig::DoExport result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("exportToc", &sem::DocumentOptions::ExportConfig::DoExport::exportToc)
    .def("__repr__", [](sem::DocumentOptions::ExportConfig::DoExport _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::DocumentOptions::ExportConfig::DoExport _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::DocumentOptions::ExportConfig::ExportFixed>(m, "DocumentOptionsExportConfigExportFixed")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentOptions::ExportConfig::ExportFixed {
                        sem::DocumentOptions::ExportConfig::ExportFixed result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("exportLevels", &sem::DocumentOptions::ExportConfig::ExportFixed::exportLevels)
    .def("__repr__", [](sem::DocumentOptions::ExportConfig::ExportFixed _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::DocumentOptions::ExportConfig::ExportFixed _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::DocumentOptions::ExportConfig::TocExportKind>(m, "DocumentOptionsExportConfigTocExportKind");
  pybind11::enum_<sem::DocumentOptions::ExportConfig::TocExportKind>(m, "DocumentOptionsExportConfigTocExportKind")
    .value("DoExport", sem::DocumentOptions::ExportConfig::TocExportKind::DoExport)
    .value("ExportFixed", sem::DocumentOptions::ExportConfig::TocExportKind::ExportFixed)
    .def("__iter__", [](sem::DocumentOptions::ExportConfig::TocExportKind _self) -> PyEnumIterator<sem::DocumentOptions::ExportConfig::TocExportKind> {
                     return
                     PyEnumIterator<sem::DocumentOptions::ExportConfig::TocExportKind>
                     ();
                     })
    ;
  pybind11::class_<sem::DocumentOptions::ExportConfig>(m, "DocumentOptionsExportConfig")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentOptions::ExportConfig {
                        sem::DocumentOptions::ExportConfig result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("inlinetasks", &sem::DocumentOptions::ExportConfig::inlinetasks)
    .def_readwrite("footnotes", &sem::DocumentOptions::ExportConfig::footnotes)
    .def_readwrite("clock", &sem::DocumentOptions::ExportConfig::clock)
    .def_readwrite("author", &sem::DocumentOptions::ExportConfig::author)
    .def_readwrite("emphasis", &sem::DocumentOptions::ExportConfig::emphasis)
    .def_readwrite("specialStrings", &sem::DocumentOptions::ExportConfig::specialStrings)
    .def_readwrite("propertyDrawers", &sem::DocumentOptions::ExportConfig::propertyDrawers)
    .def_readwrite("statisticsCookies", &sem::DocumentOptions::ExportConfig::statisticsCookies)
    .def_readwrite("todoText", &sem::DocumentOptions::ExportConfig::todoText, R"RAW(Include todo keywords in export)RAW")
    .def_readwrite("brokenLinks", &sem::DocumentOptions::ExportConfig::brokenLinks)
    .def_readwrite("tocExport", &sem::DocumentOptions::ExportConfig::tocExport)
    .def_readwrite("tagExport", &sem::DocumentOptions::ExportConfig::tagExport)
    .def_readwrite("data", &sem::DocumentOptions::ExportConfig::data)
    .def("getDoExport", static_cast<sem::DocumentOptions::ExportConfig::DoExport&(sem::DocumentOptions::ExportConfig::*)()>(&sem::DocumentOptions::ExportConfig::getDoExport))
    .def("getExportFixed", static_cast<sem::DocumentOptions::ExportConfig::ExportFixed&(sem::DocumentOptions::ExportConfig::*)()>(&sem::DocumentOptions::ExportConfig::getExportFixed))
    .def_static("getTocExportKindStatic",
                static_cast<sem::DocumentOptions::ExportConfig::TocExportKind(*)(sem::DocumentOptions::ExportConfig::TocExport const&)>(&sem::DocumentOptions::ExportConfig::getTocExportKind),
                pybind11::arg("__input"))
    .def("getTocExportKind", static_cast<sem::DocumentOptions::ExportConfig::TocExportKind(sem::DocumentOptions::ExportConfig::*)() const>(&sem::DocumentOptions::ExportConfig::getTocExportKind))
    .def("__repr__", [](sem::DocumentOptions::ExportConfig _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::DocumentOptions::ExportConfig _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def_readwrite("initialVisibility", &sem::DocumentOptions::initialVisibility)
    .def_readwrite("properties", &sem::DocumentOptions::properties)
    .def_readwrite("exportConfig", &sem::DocumentOptions::exportConfig)
    .def_readwrite("fixedWidthSections", &sem::DocumentOptions::fixedWidthSections)
    .def_readwrite("startupIndented", &sem::DocumentOptions::startupIndented)
    .def_readwrite("category", &sem::DocumentOptions::category)
    .def_readwrite("setupfile", &sem::DocumentOptions::setupfile)
    .def_readwrite("maxSubtreeLevelExport", &sem::DocumentOptions::maxSubtreeLevelExport)
    .def("getProperties",
         static_cast<Vec<sem::Subtree::Property>(sem::DocumentOptions::*)(Str const&, Opt<Str> const&) const>(&sem::DocumentOptions::getProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt))
    .def("getProperty",
         static_cast<Opt<sem::Subtree::Property>(sem::DocumentOptions::*)(Str const&, Opt<Str> const&) const>(&sem::DocumentOptions::getProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt))
    .def("__repr__", [](sem::DocumentOptions _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::DocumentOptions _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def("__repr__", [](sem::Document _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Document _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def("__repr__", [](sem::FileTarget _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::FileTarget _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::TextSeparator, sem::SemId<sem::TextSeparator>, sem::Org>(m, "TextSeparator")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::TextSeparator {
                        sem::TextSeparator result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::TextSeparator _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::TextSeparator _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Include::Example>(m, "IncludeExample")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Include::Example {
                        sem::Include::Example result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Include::Example _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Include::Example _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Include::Export>(m, "IncludeExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Include::Export {
                        sem::Include::Export result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Include::Export _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Include::Export _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Include::Src>(m, "IncludeSrc")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Include::Src {
                        sem::Include::Src result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Include::Src _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Include::Src _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Include::OrgDocument>(m, "IncludeOrgDocument")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Include::OrgDocument {
                        sem::Include::OrgDocument result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("minLevel", &sem::Include::OrgDocument::minLevel, R"RAW(The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.)RAW")
    .def("__repr__", [](sem::Include::OrgDocument _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Include::OrgDocument _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def_readwrite("path", &sem::Include::path, R"RAW(Path to include)RAW")
    .def_readwrite("firstLine", &sem::Include::firstLine, R"RAW(0-based index of the first line to include. NOTE: Org-mode syntax uses 1-based half-open range in the text)RAW")
    .def_readwrite("lastLine", &sem::Include::lastLine, R"RAW(0-based index of the last line to include)RAW")
    .def_readwrite("data", &sem::Include::data)
    .def("getExample", static_cast<sem::Include::Example&(sem::Include::*)()>(&sem::Include::getExample))
    .def("getExport", static_cast<sem::Include::Export&(sem::Include::*)()>(&sem::Include::getExport))
    .def("getSrc", static_cast<sem::Include::Src&(sem::Include::*)()>(&sem::Include::getSrc))
    .def("getOrgDocument", static_cast<sem::Include::OrgDocument&(sem::Include::*)()>(&sem::Include::getOrgDocument))
    .def_static("getIncludeKindStatic",
                static_cast<sem::Include::Kind(*)(sem::Include::Data const&)>(&sem::Include::getIncludeKind),
                pybind11::arg("__input"))
    .def("getIncludeKind", static_cast<sem::Include::Kind(sem::Include::*)() const>(&sem::Include::getIncludeKind))
    .def("__repr__", [](sem::Include _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Include _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::DocumentGroup, sem::SemId<sem::DocumentGroup>, sem::Org>(m, "DocumentGroup")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentGroup {
                        sem::DocumentGroup result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::DocumentGroup _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::DocumentGroup _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .value("CmdArgument", OrgSemKind::CmdArgument)
    .value("CmdArgumentList", OrgSemKind::CmdArgumentList)
    .value("CmdArguments", OrgSemKind::CmdArguments)
    .value("ErrorItem", OrgSemKind::ErrorItem)
    .value("ErrorGroup", OrgSemKind::ErrorGroup)
    .value("StmtList", OrgSemKind::StmtList)
    .value("Empty", OrgSemKind::Empty)
    .value("CmdCaption", OrgSemKind::CmdCaption)
    .value("CmdName", OrgSemKind::CmdName)
    .value("CmdCustomArgs", OrgSemKind::CmdCustomArgs)
    .value("CmdCustomRaw", OrgSemKind::CmdCustomRaw)
    .value("CmdCustomText", OrgSemKind::CmdCustomText)
    .value("CmdResults", OrgSemKind::CmdResults)
    .value("CmdTblfm", OrgSemKind::CmdTblfm)
    .value("HashTag", OrgSemKind::HashTag)
    .value("Footnote", OrgSemKind::Footnote)
    .value("Time", OrgSemKind::Time)
    .value("TimeRange", OrgSemKind::TimeRange)
    .value("Macro", OrgSemKind::Macro)
    .value("Symbol", OrgSemKind::Symbol)
    .value("Escaped", OrgSemKind::Escaped)
    .value("Newline", OrgSemKind::Newline)
    .value("Space", OrgSemKind::Space)
    .value("Word", OrgSemKind::Word)
    .value("AtMention", OrgSemKind::AtMention)
    .value("RawText", OrgSemKind::RawText)
    .value("Punctuation", OrgSemKind::Punctuation)
    .value("Placeholder", OrgSemKind::Placeholder)
    .value("BigIdent", OrgSemKind::BigIdent)
    .value("RadioTarget", OrgSemKind::RadioTarget)
    .value("TextTarget", OrgSemKind::TextTarget)
    .value("Bold", OrgSemKind::Bold)
    .value("Underline", OrgSemKind::Underline)
    .value("Monospace", OrgSemKind::Monospace)
    .value("MarkQuote", OrgSemKind::MarkQuote)
    .value("Verbatim", OrgSemKind::Verbatim)
    .value("Italic", OrgSemKind::Italic)
    .value("Strike", OrgSemKind::Strike)
    .value("Par", OrgSemKind::Par)
    .value("Latex", OrgSemKind::Latex)
    .value("Link", OrgSemKind::Link)
    .value("BlockCenter", OrgSemKind::BlockCenter)
    .value("BlockQuote", OrgSemKind::BlockQuote)
    .value("BlockComment", OrgSemKind::BlockComment)
    .value("BlockVerse", OrgSemKind::BlockVerse)
    .value("BlockExample", OrgSemKind::BlockExample)
    .value("BlockExport", OrgSemKind::BlockExport)
    .value("BlockAdmonition", OrgSemKind::BlockAdmonition)
    .value("BlockCode", OrgSemKind::BlockCode)
    .value("SubtreeLog", OrgSemKind::SubtreeLog)
    .value("Subtree", OrgSemKind::Subtree)
    .value("SubtreeCompletion", OrgSemKind::SubtreeCompletion)
    .value("Cell", OrgSemKind::Cell)
    .value("Row", OrgSemKind::Row)
    .value("Table", OrgSemKind::Table)
    .value("Paragraph", OrgSemKind::Paragraph)
    .value("AnnotatedParagraph", OrgSemKind::AnnotatedParagraph)
    .value("ColonExample", OrgSemKind::ColonExample)
    .value("CmdAttr", OrgSemKind::CmdAttr)
    .value("Call", OrgSemKind::Call)
    .value("List", OrgSemKind::List)
    .value("ListItem", OrgSemKind::ListItem)
    .value("DocumentOptions", OrgSemKind::DocumentOptions)
    .value("Document", OrgSemKind::Document)
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
    .def("__repr__", [](UserTimeBreakdown _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](UserTimeBreakdown _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<UserTime>(m, "UserTime")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> UserTime {
                        UserTime result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getBreakdown", static_cast<UserTimeBreakdown(UserTime::*)() const>(&UserTime::getBreakdown))
    .def("format", static_cast<std::string(UserTime::*)() const>(&UserTime::format))
    .def("__repr__", [](UserTime _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](UserTime _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::OrgParseParameters>(m, "OrgParseParameters")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::OrgParseParameters {
                        sem::OrgParseParameters result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("baseTokenTracePath", &sem::OrgParseParameters::baseTokenTracePath)
    .def_readwrite("tokenTracePath", &sem::OrgParseParameters::tokenTracePath)
    .def_readwrite("parseTracePath", &sem::OrgParseParameters::parseTracePath)
    .def_readwrite("semTracePath", &sem::OrgParseParameters::semTracePath)
    .def("__repr__", [](sem::OrgParseParameters _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::OrgParseParameters _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::OrgYamlExportOpts>(m, "OrgYamlExportOpts")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::OrgYamlExportOpts {
                        sem::OrgYamlExportOpts result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("skipNullFields", &sem::OrgYamlExportOpts::skipNullFields)
    .def_readwrite("skipFalseFields", &sem::OrgYamlExportOpts::skipFalseFields)
    .def_readwrite("skipZeroFields", &sem::OrgYamlExportOpts::skipZeroFields)
    .def_readwrite("skipLocation", &sem::OrgYamlExportOpts::skipLocation)
    .def_readwrite("skipId", &sem::OrgYamlExportOpts::skipId)
    .def("__repr__", [](sem::OrgYamlExportOpts _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::OrgYamlExportOpts _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::OrgTreeExportOpts>(m, "OrgTreeExportOpts")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::OrgTreeExportOpts {
                        sem::OrgTreeExportOpts result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("withLineCol", &sem::OrgTreeExportOpts::withLineCol)
    .def_readwrite("withOriginalId", &sem::OrgTreeExportOpts::withOriginalId)
    .def_readwrite("withSubnodeIdx", &sem::OrgTreeExportOpts::withSubnodeIdx)
    .def_readwrite("skipEmptyFields", &sem::OrgTreeExportOpts::skipEmptyFields)
    .def_readwrite("startLevel", &sem::OrgTreeExportOpts::startLevel)
    .def_readwrite("withColor", &sem::OrgTreeExportOpts::withColor)
    .def_readwrite("maxDepth", &sem::OrgTreeExportOpts::maxDepth)
    .def("__repr__", [](sem::OrgTreeExportOpts _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::OrgTreeExportOpts _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubnodeVisitorCtxPart>(m, "SubnodeVisitorCtxPart")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubnodeVisitorCtxPart {
                        sem::SubnodeVisitorCtxPart result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("node", &sem::SubnodeVisitorCtxPart::node, R"RAW(\brief Parent node for the currently visited one. Each node is
encountered exactly once in the visitor context path, but when
visiting multi-layered fields (vector field) the node is not,
present.

For vector fields the path will have two parts:
`[node+field-name]+[index]` -- the first element from the actual
field visit and the second is from accessing each particular index.)RAW")
    .def_readwrite("index", &sem::SubnodeVisitorCtxPart::index, R"RAW(\brief If the current visit is in vector field -- index of
the node in parent list.)RAW")
    .def_readwrite("field", &sem::SubnodeVisitorCtxPart::field, R"RAW(\brief If the current visit is in the dedicated field (`.title` for
example),)RAW")
    .def_readwrite("kind", &sem::SubnodeVisitorCtxPart::kind)
    .def("__repr__", [](sem::SubnodeVisitorCtxPart _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubnodeVisitorCtxPart _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubnodeVisitorOpts>(m, "SubnodeVisitorOpts")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubnodeVisitorOpts {
                        sem::SubnodeVisitorOpts result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::SubnodeVisitorOpts _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubnodeVisitorOpts _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubnodeVisitorResult>(m, "SubnodeVisitorResult")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubnodeVisitorResult {
                        sem::SubnodeVisitorResult result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("visitNextFields", &sem::SubnodeVisitorResult::visitNextFields, R"RAW(\brief After visting the current node, descend into it's node
fields)RAW")
    .def_readwrite("visitNextSubnodes", &sem::SubnodeVisitorResult::visitNextSubnodes, R"RAW(\brief)RAW")
    .def_readwrite("visitNextBases", &sem::SubnodeVisitorResult::visitNextBases)
    .def("__repr__", [](sem::SubnodeVisitorResult _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubnodeVisitorResult _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def("__repr__", [](sem::OrgDocumentContext _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::OrgDocumentContext _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::OrgSelectorLink>(m, "OrgSelectorLink")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::OrgSelectorLink {
                        sem::OrgSelectorLink result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::OrgSelectorLink _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::OrgSelectorLink _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::OrgSelectorResult>(m, "OrgSelectorResult")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::OrgSelectorResult {
                        sem::OrgSelectorResult result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::OrgSelectorResult _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::OrgSelectorResult _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::OrgSelectorCondition>(m, "OrgSelectorCondition")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::OrgSelectorCondition {
                        sem::OrgSelectorCondition result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isTarget", &sem::OrgSelectorCondition::isTarget, R"RAW(\brief Matched node should be added to the full match set)RAW")
    .def_readwrite("debug", &sem::OrgSelectorCondition::debug)
    .def_readwrite("link", &sem::OrgSelectorCondition::link)
    .def("__repr__", [](sem::OrgSelectorCondition _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::OrgSelectorCondition _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::OrgDocumentSelector>(m, "OrgDocumentSelector")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::OrgDocumentSelector {
                        sem::OrgDocumentSelector result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("path", &sem::OrgDocumentSelector::path)
    .def_readwrite("debug", &sem::OrgDocumentSelector::debug)
    .def("getMatches",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::OrgDocumentSelector::*)(sem::SemId<sem::Org> const&) const>(&sem::OrgDocumentSelector::getMatches),
         pybind11::arg("node"))
    .def("linkDirectSubnode", static_cast<sem::OrgSelectorLink(sem::OrgDocumentSelector::*)() const>(&sem::OrgDocumentSelector::linkDirectSubnode))
    .def("linkIndirectSubnode", static_cast<sem::OrgSelectorLink(sem::OrgDocumentSelector::*)() const>(&sem::OrgDocumentSelector::linkIndirectSubnode))
    .def("linkField",
         static_cast<sem::OrgSelectorLink(sem::OrgDocumentSelector::*)(Str const&) const>(&sem::OrgDocumentSelector::linkField),
         pybind11::arg("name"))
    .def("searchSubtreePlaintextTitle",
         static_cast<void(sem::OrgDocumentSelector::*)(Str const&, bool, std::optional<sem::OrgSelectorLink>)>(&sem::OrgDocumentSelector::searchSubtreePlaintextTitle),
         pybind11::arg("title"),
         pybind11::arg("isTarget"),
         pybind11::arg_v("link", std::nullopt))
    .def("searchSubtreeId",
         static_cast<void(sem::OrgDocumentSelector::*)(Str const&, bool, std::optional<int>, std::optional<sem::OrgSelectorLink>)>(&sem::OrgDocumentSelector::searchSubtreeId),
         pybind11::arg("id"),
         pybind11::arg("isTarget"),
         pybind11::arg_v("maxLevel", std::nullopt),
         pybind11::arg_v("link", std::nullopt))
    .def("searchAnyKind",
         static_cast<void(sem::OrgDocumentSelector::*)(IntSet<OrgSemKind> const&, bool, std::optional<sem::OrgSelectorLink>)>(&sem::OrgDocumentSelector::searchAnyKind),
         pybind11::arg("kinds"),
         pybind11::arg("isTarget"),
         pybind11::arg_v("link", std::nullopt))
    .def("searchPredicate",
         static_cast<void(sem::OrgDocumentSelector::*)(sem::OrgSelectorCondition::Predicate const&, bool, std::optional<sem::OrgSelectorLink>)>(&sem::OrgDocumentSelector::searchPredicate),
         pybind11::arg("predicate"),
         pybind11::arg("isTarget"),
         pybind11::arg_v("link", std::nullopt))
    .def("__repr__", [](sem::OrgDocumentSelector _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::OrgDocumentSelector _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<SequenceSegment>(m, "SequenceSegment")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> SequenceSegment {
                        SequenceSegment result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("kind", &SequenceSegment::kind, R"RAW(\brief Kind of the segment, does not have to be unique for all
segments, and different sequence segment groups can have segments
with identical kinds.)RAW")
    .def_readwrite("first", &SequenceSegment::first, R"RAW(\brief Inclusive left boundary of the segment. Mustnot overlap with
other segments' boundaries,but can be identical to the `last`,
to create a point segment (spans 1 element).)RAW")
    .def_readwrite("last", &SequenceSegment::last, R"RAW(\brief Inclusive right boundary for the segment)RAW")
    .def("__repr__", [](SequenceSegment _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](SequenceSegment _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<SequenceSegmentGroup>(m, "SequenceSegmentGroup")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> SequenceSegmentGroup {
                        SequenceSegmentGroup result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("kind", &SequenceSegmentGroup::kind, R"RAW(\brief An kind of the segment group, does not have to be unique)RAW")
    .def_readwrite("segments", &SequenceSegmentGroup::segments, R"RAW(\brief List of input segments for grouping)RAW")
    .def("__repr__", [](SequenceSegmentGroup _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](SequenceSegmentGroup _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<SequenceAnnotationTag>(m, "SequenceAnnotationTag")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> SequenceAnnotationTag {
                        SequenceAnnotationTag result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("groupKind", &SequenceAnnotationTag::groupKind, R"RAW(\brief ID of the original group this segment came from)RAW")
    .def_readwrite("segmentKinds", &SequenceAnnotationTag::segmentKinds, R"RAW(\brief ID of the segment in this group.

Segment kinds are constructed from all ranges
that overlap points in the segment.
In the example below, there are 3 separate slices, `[2,3]`, `[1,4]`
and finally `[6,7]`. The resulting segmentation will have 4
different sequence segments from these ranges. The first one is
`[1,1]`, then `[2,3]`, `[4]`, and `[6,7]`.
```
0
1   |
2 | |
3 | |
4   |
5
6   |
7   |
```)RAW")
    .def("__repr__", [](SequenceAnnotationTag _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](SequenceAnnotationTag _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<SequenceAnnotation>(m, "SequenceAnnotation")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> SequenceAnnotation {
                        SequenceAnnotation result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("first", &SequenceAnnotation::first, R"RAW(\brief Inclusive left boundary for the sequence segment annotation)RAW")
    .def_readwrite("last", &SequenceAnnotation::last, R"RAW(\brief Inclusive right boundary for the sequence segment)RAW")
    .def_readwrite("annotations", &SequenceAnnotation::annotations, R"RAW(\brief Full list of all annotated segments.)RAW")
    .def("isAnnotatedWith",
         static_cast<bool(SequenceAnnotation::*)(int, int) const>(&SequenceAnnotation::isAnnotatedWith),
         pybind11::arg("groupKind"),
         pybind11::arg("segmentKind"),
         R"RAW(\brief Check if the segment is annotated with a given group kind
and a segment kind.)RAW")
    .def("__repr__", [](SequenceAnnotation _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](SequenceAnnotation _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
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
    .def("__repr__", [](ExporterPython _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](ExporterPython _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::SubnodeVisitorCtxPart::Kind>(m, "SubnodeVisitorCtxPartKind");
  pybind11::enum_<sem::SubnodeVisitorCtxPart::Kind>(m, "SubnodeVisitorCtxPartKind")
    .value("Field", sem::SubnodeVisitorCtxPart::Kind::Field)
    .value("Index", sem::SubnodeVisitorCtxPart::Kind::Index)
    .value("Key", sem::SubnodeVisitorCtxPart::Kind::Key)
    .def("__iter__", [](sem::SubnodeVisitorCtxPart::Kind _self) -> PyEnumIterator<sem::SubnodeVisitorCtxPart::Kind> {
                     return
                     PyEnumIterator<sem::SubnodeVisitorCtxPart::Kind>
                     ();
                     })
    ;
  bind_enum_iterator<sem::OrgSelectorLink::Kind>(m, "OrgSelectorLinkKind");
  pybind11::enum_<sem::OrgSelectorLink::Kind>(m, "OrgSelectorLinkKind")
    .value("DirectSubnode", sem::OrgSelectorLink::Kind::DirectSubnode)
    .value("IndirectSubnode", sem::OrgSelectorLink::Kind::IndirectSubnode)
    .value("FieldName", sem::OrgSelectorLink::Kind::FieldName)
    .def("__iter__", [](sem::OrgSelectorLink::Kind _self) -> PyEnumIterator<sem::OrgSelectorLink::Kind> {
                     return
                     PyEnumIterator<sem::OrgSelectorLink::Kind>
                     ();
                     })
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
  m.def("newSemTimeStatic",
        static_cast<sem::SemId<sem::Time>(*)(UserTimeBreakdown const&, bool)>(&sem::newSemTimeStatic),
        pybind11::arg("breakdown"),
        pybind11::arg_v("isActive", 0));
  m.def("parseFile",
        static_cast<sem::SemId<sem::Document>(*)(std::string, sem::OrgParseParameters const&)>(&sem::parseFile),
        pybind11::arg("file"),
        pybind11::arg("opts"));
  m.def("parseString",
        static_cast<sem::SemId<sem::Document>(*)(std::string const)>(&sem::parseString),
        pybind11::arg("text"));
  m.def("parseStringOpts",
        static_cast<sem::SemId<sem::Document>(*)(std::string const, sem::OrgParseParameters const&)>(&sem::parseStringOpts),
        pybind11::arg("text"),
        pybind11::arg("opts"));
  m.def("formatToString",
        static_cast<std::string(*)(sem::SemId<sem::Org>)>(&sem::formatToString),
        pybind11::arg("arg"));
  m.def("exportToYamlString",
        static_cast<std::string(*)(sem::SemId<sem::Org> const&, sem::OrgYamlExportOpts const&)>(&sem::exportToYamlString),
        pybind11::arg("node"),
        pybind11::arg("opts"));
  m.def("exportToYamlFile",
        static_cast<void(*)(sem::SemId<sem::Org> const&, std::string, sem::OrgYamlExportOpts const&)>(&sem::exportToYamlFile),
        pybind11::arg("node"),
        pybind11::arg("path"),
        pybind11::arg("opts"));
  m.def("exportToJsonString",
        static_cast<std::string(*)(sem::SemId<sem::Org> const&)>(&sem::exportToJsonString),
        pybind11::arg("node"));
  m.def("exportToJsonFile",
        static_cast<void(*)(sem::SemId<sem::Org> const&, std::string)>(&sem::exportToJsonFile),
        pybind11::arg("node"),
        pybind11::arg("path"));
  m.def("readProtobufFile",
        static_cast<sem::SemId<sem::Document>(*)(std::string const&)>(&sem::readProtobufFile),
        pybind11::arg("file"));
  m.def("exportToProtobufFile",
        static_cast<void(*)(sem::SemId<sem::Document>, std::string const&)>(&sem::exportToProtobufFile),
        pybind11::arg("doc"),
        pybind11::arg("file"));
  m.def("exportToTreeString",
        static_cast<std::string(*)(sem::SemId<sem::Org> const&, sem::OrgTreeExportOpts const&)>(&sem::exportToTreeString),
        pybind11::arg("node"),
        pybind11::arg("opts"));
  m.def("exportToTreeFile",
        static_cast<void(*)(sem::SemId<sem::Org> const&, std::string, sem::OrgTreeExportOpts const&)>(&sem::exportToTreeFile),
        pybind11::arg("node"),
        pybind11::arg("path"),
        pybind11::arg("opts"));
  m.def("annotateSequence",
        static_cast<Vec<SequenceAnnotation>(*)(Vec<SequenceSegmentGroup> const&, int, int)>(&annotateSequence),
        pybind11::arg("groups"),
        pybind11::arg("first"),
        pybind11::arg("last"));
  m.def("eachSubnodeRec",
        static_cast<void(*)(sem::SemId<sem::Org>, pybind11::function)>(&eachSubnodeRec),
        pybind11::arg("node"),
        pybind11::arg("callback"));
}
/* clang-format on */