/* clang-format off */
#undef slots
#define PYBIND11_DETAILED_ERROR_MESSAGES
#include <pybind11/pybind11.h>
#include <haxorg/sem/SemOrg.hpp>
#include <pybind11/stl.h>
#include "pyhaxorg_manual_impl.hpp"
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Org>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Org>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::BlockCodeLine::Part>)
PYBIND11_MAKE_OPAQUE(Vec<sem::BlockCodeLine::Part>)
PYBIND11_MAKE_OPAQUE(std::vector<int>)
PYBIND11_MAKE_OPAQUE(Vec<int>)
PYBIND11_MAKE_OPAQUE(std::vector<Str>)
PYBIND11_MAKE_OPAQUE(Vec<Str>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<Str, Str>)
PYBIND11_MAKE_OPAQUE(UnorderedMap<Str, Str>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::CmdArgument>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::CmdArgument>>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<Str, sem::SemId<sem::CmdArgumentList>>)
PYBIND11_MAKE_OPAQUE(UnorderedMap<Str, sem::SemId<sem::CmdArgumentList>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::ErrorItem>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::ErrorItem>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::HashTag>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::HashTag>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Symbol::Param>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Symbol::Param>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::BlockCodeSwitch>)
PYBIND11_MAKE_OPAQUE(Vec<sem::BlockCodeSwitch>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::BlockCodeLine>)
PYBIND11_MAKE_OPAQUE(Vec<sem::BlockCodeLine>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::SubtreeLog>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::SubtreeLog>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::NamedProperty>)
PYBIND11_MAKE_OPAQUE(Vec<sem::NamedProperty>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SubtreePeriod>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SubtreePeriod>)
PYBIND11_MAKE_OPAQUE(IntSet<sem::SubtreePeriod::Kind>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Cell>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Cell>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Row>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Row>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Subtree>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Subtree>>)
PYBIND11_MAKE_OPAQUE(std::vector<SequenceSegment>)
PYBIND11_MAKE_OPAQUE(Vec<SequenceSegment>)
PYBIND11_MAKE_OPAQUE(std::vector<SequenceAnnotationTag>)
PYBIND11_MAKE_OPAQUE(Vec<SequenceAnnotationTag>)
PYBIND11_MAKE_OPAQUE(std::vector<SequenceAnnotation>)
PYBIND11_MAKE_OPAQUE(Vec<SequenceAnnotation>)
PYBIND11_MAKE_OPAQUE(std::vector<SequenceSegmentGroup>)
PYBIND11_MAKE_OPAQUE(Vec<SequenceSegmentGroup>)
PYBIND11_MODULE(pyhaxorg, m) {
  PyTypeRegistryGuard type_registry_guard{};
  bind_vector<sem::SemId<sem::Org>>(m, "VecOfSemIdOfOrg", type_registry_guard);
  bind_vector<sem::BlockCodeLine::Part>(m, "VecOfBlockCodeLinePart", type_registry_guard);
  bind_vector<int>(m, "VecOfint", type_registry_guard);
  bind_vector<Str>(m, "VecOfStr", type_registry_guard);
  bind_unordered_map<Str, Str>(m, "UnorderedMapOfStrStr", type_registry_guard);
  bind_vector<sem::SemId<sem::CmdArgument>>(m, "VecOfSemIdOfCmdArgument", type_registry_guard);
  bind_unordered_map<Str, sem::SemId<sem::CmdArgumentList>>(m, "UnorderedMapOfStrSemIdOfCmdArgumentList", type_registry_guard);
  bind_vector<sem::SemId<sem::ErrorItem>>(m, "VecOfSemIdOfErrorItem", type_registry_guard);
  bind_vector<sem::SemId<sem::HashTag>>(m, "VecOfSemIdOfHashTag", type_registry_guard);
  bind_vector<sem::Symbol::Param>(m, "VecOfSymbolParam", type_registry_guard);
  bind_vector<sem::BlockCodeSwitch>(m, "VecOfBlockCodeSwitch", type_registry_guard);
  bind_vector<sem::BlockCodeLine>(m, "VecOfBlockCodeLine", type_registry_guard);
  bind_vector<sem::SemId<sem::SubtreeLog>>(m, "VecOfSemIdOfSubtreeLog", type_registry_guard);
  bind_vector<sem::NamedProperty>(m, "VecOfNamedProperty", type_registry_guard);
  bind_vector<sem::SubtreePeriod>(m, "VecOfSubtreePeriod", type_registry_guard);
  bind_int_set<sem::SubtreePeriod::Kind>(m, "IntSetOfSubtreePeriodKind", type_registry_guard);
  bind_vector<sem::SemId<sem::Cell>>(m, "VecOfSemIdOfCell", type_registry_guard);
  bind_vector<sem::SemId<sem::Row>>(m, "VecOfSemIdOfRow", type_registry_guard);
  bind_vector<sem::SemId<sem::Subtree>>(m, "VecOfSemIdOfSubtree", type_registry_guard);
  bind_vector<SequenceSegment>(m, "VecOfSequenceSegment", type_registry_guard);
  bind_vector<SequenceAnnotationTag>(m, "VecOfSequenceAnnotationTag", type_registry_guard);
  bind_vector<SequenceAnnotation>(m, "VecOfSequenceAnnotation", type_registry_guard);
  bind_vector<SequenceSegmentGroup>(m, "VecOfSequenceSegmentGroup", type_registry_guard);
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
  pybind11::class_<sem::BlockCodeLine::Part::Raw>(m, "BlockCodeLinePartRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeLine::Part::Raw {
                        sem::BlockCodeLine::Part::Raw result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("code", &sem::BlockCodeLine::Part::Raw::code)
    .def("operator==",
         static_cast<bool(sem::BlockCodeLine::Part::Raw::*)(sem::BlockCodeLine::Part::Raw const&) const>(&sem::BlockCodeLine::Part::Raw::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeLine::Part::Raw _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeLine::Part::Raw _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeLine::Part::Callout>(m, "BlockCodeLinePartCallout")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeLine::Part::Callout {
                        sem::BlockCodeLine::Part::Callout result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::BlockCodeLine::Part::Callout::name)
    .def("operator==",
         static_cast<bool(sem::BlockCodeLine::Part::Callout::*)(sem::BlockCodeLine::Part::Callout const&) const>(&sem::BlockCodeLine::Part::Callout::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeLine::Part::Callout _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeLine::Part::Callout _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeLine::Part::Tangle>(m, "BlockCodeLinePartTangle")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeLine::Part::Tangle {
                        sem::BlockCodeLine::Part::Tangle result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &sem::BlockCodeLine::Part::Tangle::target)
    .def("operator==",
         static_cast<bool(sem::BlockCodeLine::Part::Tangle::*)(sem::BlockCodeLine::Part::Tangle const&) const>(&sem::BlockCodeLine::Part::Tangle::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeLine::Part::Tangle _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeLine::Part::Tangle _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::BlockCodeLine::Part::Kind>(m, "BlockCodeLinePartKind", type_registry_guard);
  pybind11::enum_<sem::BlockCodeLine::Part::Kind>(m, "BlockCodeLinePartKind")
    .value("Raw", sem::BlockCodeLine::Part::Kind::Raw)
    .value("Callout", sem::BlockCodeLine::Part::Kind::Callout)
    .value("Tangle", sem::BlockCodeLine::Part::Kind::Tangle)
    .def("__iter__", [](sem::BlockCodeLine::Part::Kind _self) -> PyEnumIterator<sem::BlockCodeLine::Part::Kind> {
                     return
                     PyEnumIterator<sem::BlockCodeLine::Part::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::BlockCodeLine::Part>(m, "BlockCodeLinePart")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeLine::Part {
                        sem::BlockCodeLine::Part result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &sem::BlockCodeLine::Part::data)
    .def("operator==",
         static_cast<bool(sem::BlockCodeLine::Part::*)(sem::BlockCodeLine::Part const&) const>(&sem::BlockCodeLine::Part::operator==),
         pybind11::arg("other"))
    .def("getRaw", static_cast<sem::BlockCodeLine::Part::Raw&(sem::BlockCodeLine::Part::*)()>(&sem::BlockCodeLine::Part::getRaw))
    .def("getCallout", static_cast<sem::BlockCodeLine::Part::Callout&(sem::BlockCodeLine::Part::*)()>(&sem::BlockCodeLine::Part::getCallout))
    .def("getTangle", static_cast<sem::BlockCodeLine::Part::Tangle&(sem::BlockCodeLine::Part::*)()>(&sem::BlockCodeLine::Part::getTangle))
    .def_static("getKindStatic",
                static_cast<sem::BlockCodeLine::Part::Kind(*)(sem::BlockCodeLine::Part::Data const&)>(&sem::BlockCodeLine::Part::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<sem::BlockCodeLine::Part::Kind(sem::BlockCodeLine::Part::*)() const>(&sem::BlockCodeLine::Part::getKind))
    .def("__repr__", [](sem::BlockCodeLine::Part _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeLine::Part _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeLine>(m, "BlockCodeLine")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeLine {
                        sem::BlockCodeLine result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("parts", &sem::BlockCodeLine::parts, R"RAW(parts of the single line)RAW")
    .def("operator==",
         static_cast<bool(sem::BlockCodeLine::*)(sem::BlockCodeLine const&) const>(&sem::BlockCodeLine::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeLine _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeLine _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeSwitch::LineStart>(m, "BlockCodeSwitchLineStart")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeSwitch::LineStart {
                        sem::BlockCodeSwitch::LineStart result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("start", &sem::BlockCodeSwitch::LineStart::start, R"RAW(First line number)RAW")
    .def_readwrite("extendLast", &sem::BlockCodeSwitch::LineStart::extendLast, R"RAW(Continue numbering from the previous block nstead of starting anew)RAW")
    .def("operator==",
         static_cast<bool(sem::BlockCodeSwitch::LineStart::*)(sem::BlockCodeSwitch::LineStart const&) const>(&sem::BlockCodeSwitch::LineStart::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeSwitch::LineStart _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeSwitch::LineStart _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeSwitch::CalloutFormat>(m, "BlockCodeSwitchCalloutFormat")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeSwitch::CalloutFormat {
                        sem::BlockCodeSwitch::CalloutFormat result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("format", &sem::BlockCodeSwitch::CalloutFormat::format)
    .def("operator==",
         static_cast<bool(sem::BlockCodeSwitch::CalloutFormat::*)(sem::BlockCodeSwitch::CalloutFormat const&) const>(&sem::BlockCodeSwitch::CalloutFormat::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeSwitch::CalloutFormat _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeSwitch::CalloutFormat _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeSwitch::RemoveCallout>(m, "BlockCodeSwitchRemoveCallout")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeSwitch::RemoveCallout {
                        sem::BlockCodeSwitch::RemoveCallout result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("remove", &sem::BlockCodeSwitch::RemoveCallout::remove)
    .def("operator==",
         static_cast<bool(sem::BlockCodeSwitch::RemoveCallout::*)(sem::BlockCodeSwitch::RemoveCallout const&) const>(&sem::BlockCodeSwitch::RemoveCallout::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeSwitch::RemoveCallout _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeSwitch::RemoveCallout _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeSwitch::EmphasizeLine>(m, "BlockCodeSwitchEmphasizeLine")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeSwitch::EmphasizeLine {
                        sem::BlockCodeSwitch::EmphasizeLine result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("line", &sem::BlockCodeSwitch::EmphasizeLine::line)
    .def("operator==",
         static_cast<bool(sem::BlockCodeSwitch::EmphasizeLine::*)(sem::BlockCodeSwitch::EmphasizeLine const&) const>(&sem::BlockCodeSwitch::EmphasizeLine::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeSwitch::EmphasizeLine _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeSwitch::EmphasizeLine _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeSwitch::Dedent>(m, "BlockCodeSwitchDedent")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeSwitch::Dedent {
                        sem::BlockCodeSwitch::Dedent result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &sem::BlockCodeSwitch::Dedent::value)
    .def("operator==",
         static_cast<bool(sem::BlockCodeSwitch::Dedent::*)(sem::BlockCodeSwitch::Dedent const&) const>(&sem::BlockCodeSwitch::Dedent::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeSwitch::Dedent _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeSwitch::Dedent _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::BlockCodeSwitch::Kind>(m, "BlockCodeSwitchKind", type_registry_guard);
  pybind11::enum_<sem::BlockCodeSwitch::Kind>(m, "BlockCodeSwitchKind")
    .value("LineStart", sem::BlockCodeSwitch::Kind::LineStart)
    .value("CalloutFormat", sem::BlockCodeSwitch::Kind::CalloutFormat)
    .value("RemoveCallout", sem::BlockCodeSwitch::Kind::RemoveCallout)
    .value("EmphasizeLine", sem::BlockCodeSwitch::Kind::EmphasizeLine)
    .value("Dedent", sem::BlockCodeSwitch::Kind::Dedent)
    .def("__iter__", [](sem::BlockCodeSwitch::Kind _self) -> PyEnumIterator<sem::BlockCodeSwitch::Kind> {
                     return
                     PyEnumIterator<sem::BlockCodeSwitch::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::BlockCodeSwitch>(m, "BlockCodeSwitch")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeSwitch {
                        sem::BlockCodeSwitch result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &sem::BlockCodeSwitch::data)
    .def("operator==",
         static_cast<bool(sem::BlockCodeSwitch::*)(sem::BlockCodeSwitch const&) const>(&sem::BlockCodeSwitch::operator==),
         pybind11::arg("other"))
    .def("getLineStart", static_cast<sem::BlockCodeSwitch::LineStart&(sem::BlockCodeSwitch::*)()>(&sem::BlockCodeSwitch::getLineStart))
    .def("getCalloutFormat", static_cast<sem::BlockCodeSwitch::CalloutFormat&(sem::BlockCodeSwitch::*)()>(&sem::BlockCodeSwitch::getCalloutFormat))
    .def("getRemoveCallout", static_cast<sem::BlockCodeSwitch::RemoveCallout&(sem::BlockCodeSwitch::*)()>(&sem::BlockCodeSwitch::getRemoveCallout))
    .def("getEmphasizeLine", static_cast<sem::BlockCodeSwitch::EmphasizeLine&(sem::BlockCodeSwitch::*)()>(&sem::BlockCodeSwitch::getEmphasizeLine))
    .def("getDedent", static_cast<sem::BlockCodeSwitch::Dedent&(sem::BlockCodeSwitch::*)()>(&sem::BlockCodeSwitch::getDedent))
    .def_static("getKindStatic",
                static_cast<sem::BlockCodeSwitch::Kind(*)(sem::BlockCodeSwitch::Data const&)>(&sem::BlockCodeSwitch::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<sem::BlockCodeSwitch::Kind(sem::BlockCodeSwitch::*)() const>(&sem::BlockCodeSwitch::getKind))
    .def("__repr__", [](sem::BlockCodeSwitch _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeSwitch _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeEvalResult::None>(m, "BlockCodeEvalResultNone")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeEvalResult::None {
                        sem::BlockCodeEvalResult::None result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("operator==",
         static_cast<bool(sem::BlockCodeEvalResult::None::*)(sem::BlockCodeEvalResult::None const&) const>(&sem::BlockCodeEvalResult::None::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeEvalResult::None _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeEvalResult::None _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeEvalResult::OrgValue>(m, "BlockCodeEvalResultOrgValue")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeEvalResult::OrgValue {
                        sem::BlockCodeEvalResult::OrgValue result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &sem::BlockCodeEvalResult::OrgValue::value, R"RAW(Evaluation result)RAW")
    .def("operator==",
         static_cast<bool(sem::BlockCodeEvalResult::OrgValue::*)(sem::BlockCodeEvalResult::OrgValue const&) const>(&sem::BlockCodeEvalResult::OrgValue::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeEvalResult::OrgValue _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeEvalResult::OrgValue _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeEvalResult::File>(m, "BlockCodeEvalResultFile")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeEvalResult::File {
                        sem::BlockCodeEvalResult::File result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("path", &sem::BlockCodeEvalResult::File::path)
    .def("operator==",
         static_cast<bool(sem::BlockCodeEvalResult::File::*)(sem::BlockCodeEvalResult::File const&) const>(&sem::BlockCodeEvalResult::File::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeEvalResult::File _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeEvalResult::File _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeEvalResult::Raw>(m, "BlockCodeEvalResultRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeEvalResult::Raw {
                        sem::BlockCodeEvalResult::Raw result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::BlockCodeEvalResult::Raw::text)
    .def("operator==",
         static_cast<bool(sem::BlockCodeEvalResult::Raw::*)(sem::BlockCodeEvalResult::Raw const&) const>(&sem::BlockCodeEvalResult::Raw::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeEvalResult::Raw _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeEvalResult::Raw _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::BlockCodeEvalResult::Kind>(m, "BlockCodeEvalResultKind", type_registry_guard);
  pybind11::enum_<sem::BlockCodeEvalResult::Kind>(m, "BlockCodeEvalResultKind")
    .value("None", sem::BlockCodeEvalResult::Kind::None)
    .value("OrgValue", sem::BlockCodeEvalResult::Kind::OrgValue)
    .value("File", sem::BlockCodeEvalResult::Kind::File)
    .value("Raw", sem::BlockCodeEvalResult::Kind::Raw)
    .def("__iter__", [](sem::BlockCodeEvalResult::Kind _self) -> PyEnumIterator<sem::BlockCodeEvalResult::Kind> {
                     return
                     PyEnumIterator<sem::BlockCodeEvalResult::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::BlockCodeEvalResult>(m, "BlockCodeEvalResult")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeEvalResult {
                        sem::BlockCodeEvalResult result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &sem::BlockCodeEvalResult::data)
    .def("operator==",
         static_cast<bool(sem::BlockCodeEvalResult::*)(sem::BlockCodeEvalResult const&) const>(&sem::BlockCodeEvalResult::operator==),
         pybind11::arg("other"))
    .def("getNone", static_cast<sem::BlockCodeEvalResult::None&(sem::BlockCodeEvalResult::*)()>(&sem::BlockCodeEvalResult::getNone))
    .def("getOrgValue", static_cast<sem::BlockCodeEvalResult::OrgValue&(sem::BlockCodeEvalResult::*)()>(&sem::BlockCodeEvalResult::getOrgValue))
    .def("getFile", static_cast<sem::BlockCodeEvalResult::File&(sem::BlockCodeEvalResult::*)()>(&sem::BlockCodeEvalResult::getFile))
    .def("getRaw", static_cast<sem::BlockCodeEvalResult::Raw&(sem::BlockCodeEvalResult::*)()>(&sem::BlockCodeEvalResult::getRaw))
    .def_static("getKindStatic",
                static_cast<sem::BlockCodeEvalResult::Kind(*)(sem::BlockCodeEvalResult::Data const&)>(&sem::BlockCodeEvalResult::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<sem::BlockCodeEvalResult::Kind(sem::BlockCodeEvalResult::*)() const>(&sem::BlockCodeEvalResult::getKind))
    .def("__repr__", [](sem::BlockCodeEvalResult _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeEvalResult _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::DocumentExportConfig::TaskExport>(m, "DocumentExportConfigTaskExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentExportConfig::TaskExport {
                        sem::DocumentExportConfig::TaskExport result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("taskWhitelist", &sem::DocumentExportConfig::TaskExport::taskWhitelist)
    .def("operator==",
         static_cast<bool(sem::DocumentExportConfig::TaskExport::*)(sem::DocumentExportConfig::TaskExport const&) const>(&sem::DocumentExportConfig::TaskExport::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::DocumentExportConfig::TaskExport _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::DocumentExportConfig::TaskExport _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::DocumentExportConfig::TagExport>(m, "DocumentExportConfigTagExport", type_registry_guard);
  pybind11::enum_<sem::DocumentExportConfig::TagExport>(m, "DocumentExportConfigTagExport")
    .value("None", sem::DocumentExportConfig::TagExport::None)
    .value("All", sem::DocumentExportConfig::TagExport::All)
    .value("NotInToc", sem::DocumentExportConfig::TagExport::NotInToc, R"RAW(Expot tags in subtree titles but not in the table of content)RAW")
    .def("__iter__", [](sem::DocumentExportConfig::TagExport _self) -> PyEnumIterator<sem::DocumentExportConfig::TagExport> {
                     return
                     PyEnumIterator<sem::DocumentExportConfig::TagExport>
                     ();
                     })
    ;
  bind_enum_iterator<sem::DocumentExportConfig::TaskFiltering>(m, "DocumentExportConfigTaskFiltering", type_registry_guard);
  pybind11::enum_<sem::DocumentExportConfig::TaskFiltering>(m, "DocumentExportConfigTaskFiltering")
    .value("Whitelist", sem::DocumentExportConfig::TaskFiltering::Whitelist, R"RAW(Include tasks from the whitelist)RAW")
    .value("Done", sem::DocumentExportConfig::TaskFiltering::Done, R"RAW(Include tasks marked as done)RAW")
    .value("None", sem::DocumentExportConfig::TaskFiltering::None, R"RAW(Exclude all task subtrees from export)RAW")
    .value("All", sem::DocumentExportConfig::TaskFiltering::All, R"RAW(Add all task subtrees to export)RAW")
    .def("__iter__", [](sem::DocumentExportConfig::TaskFiltering _self) -> PyEnumIterator<sem::DocumentExportConfig::TaskFiltering> {
                     return
                     PyEnumIterator<sem::DocumentExportConfig::TaskFiltering>
                     ();
                     })
    ;
  bind_enum_iterator<sem::DocumentExportConfig::BrokenLinks>(m, "DocumentExportConfigBrokenLinks", type_registry_guard);
  pybind11::enum_<sem::DocumentExportConfig::BrokenLinks>(m, "DocumentExportConfigBrokenLinks")
    .value("Mark", sem::DocumentExportConfig::BrokenLinks::Mark)
    .value("Raise", sem::DocumentExportConfig::BrokenLinks::Raise)
    .value("Ignore", sem::DocumentExportConfig::BrokenLinks::Ignore)
    .def("__iter__", [](sem::DocumentExportConfig::BrokenLinks _self) -> PyEnumIterator<sem::DocumentExportConfig::BrokenLinks> {
                     return
                     PyEnumIterator<sem::DocumentExportConfig::BrokenLinks>
                     ();
                     })
    ;
  pybind11::class_<sem::DocumentExportConfig::DoExport>(m, "DocumentExportConfigDoExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentExportConfig::DoExport {
                        sem::DocumentExportConfig::DoExport result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("exportToc", &sem::DocumentExportConfig::DoExport::exportToc)
    .def("operator==",
         static_cast<bool(sem::DocumentExportConfig::DoExport::*)(sem::DocumentExportConfig::DoExport const&) const>(&sem::DocumentExportConfig::DoExport::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::DocumentExportConfig::DoExport _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::DocumentExportConfig::DoExport _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::DocumentExportConfig::ExportFixed>(m, "DocumentExportConfigExportFixed")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentExportConfig::ExportFixed {
                        sem::DocumentExportConfig::ExportFixed result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("exportLevels", &sem::DocumentExportConfig::ExportFixed::exportLevels)
    .def("operator==",
         static_cast<bool(sem::DocumentExportConfig::ExportFixed::*)(sem::DocumentExportConfig::ExportFixed const&) const>(&sem::DocumentExportConfig::ExportFixed::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::DocumentExportConfig::ExportFixed _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::DocumentExportConfig::ExportFixed _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::DocumentExportConfig::TocExportKind>(m, "DocumentExportConfigTocExportKind", type_registry_guard);
  pybind11::enum_<sem::DocumentExportConfig::TocExportKind>(m, "DocumentExportConfigTocExportKind")
    .value("DoExport", sem::DocumentExportConfig::TocExportKind::DoExport)
    .value("ExportFixed", sem::DocumentExportConfig::TocExportKind::ExportFixed)
    .def("__iter__", [](sem::DocumentExportConfig::TocExportKind _self) -> PyEnumIterator<sem::DocumentExportConfig::TocExportKind> {
                     return
                     PyEnumIterator<sem::DocumentExportConfig::TocExportKind>
                     ();
                     })
    ;
  pybind11::class_<sem::DocumentExportConfig>(m, "DocumentExportConfig")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentExportConfig {
                        sem::DocumentExportConfig result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("inlinetasks", &sem::DocumentExportConfig::inlinetasks)
    .def_readwrite("footnotes", &sem::DocumentExportConfig::footnotes)
    .def_readwrite("clock", &sem::DocumentExportConfig::clock)
    .def_readwrite("author", &sem::DocumentExportConfig::author)
    .def_readwrite("emphasis", &sem::DocumentExportConfig::emphasis)
    .def_readwrite("specialStrings", &sem::DocumentExportConfig::specialStrings)
    .def_readwrite("propertyDrawers", &sem::DocumentExportConfig::propertyDrawers)
    .def_readwrite("statisticsCookies", &sem::DocumentExportConfig::statisticsCookies)
    .def_readwrite("todoText", &sem::DocumentExportConfig::todoText, R"RAW(Include todo keywords in export)RAW")
    .def_readwrite("brokenLinks", &sem::DocumentExportConfig::brokenLinks)
    .def_readwrite("tocExport", &sem::DocumentExportConfig::tocExport)
    .def_readwrite("tagExport", &sem::DocumentExportConfig::tagExport)
    .def_readwrite("data", &sem::DocumentExportConfig::data)
    .def("operator==",
         static_cast<bool(sem::DocumentExportConfig::*)(sem::DocumentExportConfig const&) const>(&sem::DocumentExportConfig::operator==),
         pybind11::arg("other"))
    .def("getDoExport", static_cast<sem::DocumentExportConfig::DoExport&(sem::DocumentExportConfig::*)()>(&sem::DocumentExportConfig::getDoExport))
    .def("getExportFixed", static_cast<sem::DocumentExportConfig::ExportFixed&(sem::DocumentExportConfig::*)()>(&sem::DocumentExportConfig::getExportFixed))
    .def_static("getTocExportKindStatic",
                static_cast<sem::DocumentExportConfig::TocExportKind(*)(sem::DocumentExportConfig::TocExport const&)>(&sem::DocumentExportConfig::getTocExportKind),
                pybind11::arg("__input"))
    .def("getTocExportKind", static_cast<sem::DocumentExportConfig::TocExportKind(sem::DocumentExportConfig::*)() const>(&sem::DocumentExportConfig::getTocExportKind))
    .def("__repr__", [](sem::DocumentExportConfig _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::DocumentExportConfig _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::SubtreePeriod::Kind>(m, "SubtreePeriodKind", type_registry_guard);
  pybind11::enum_<sem::SubtreePeriod::Kind>(m, "SubtreePeriodKind")
    .value("Clocked", sem::SubtreePeriod::Kind::Clocked, R"RAW(Time period of the task execution.)RAW")
    .value("Closed", sem::SubtreePeriod::Kind::Closed, R"RAW(Task marked as closed)RAW")
    .value("Scheduled", sem::SubtreePeriod::Kind::Scheduled, R"RAW(Date of task execution start plus it's estimated effort duration. If the latter one is missing then only a single time point is returned)RAW")
    .value("Titled", sem::SubtreePeriod::Kind::Titled, R"RAW(Single point or time range used in title. Single point can also be a simple time, such as `12:20`)RAW")
    .value("Deadline", sem::SubtreePeriod::Kind::Deadline, R"RAW(Date of task completion. Must be a single time point)RAW")
    .value("Created", sem::SubtreePeriod::Kind::Created, R"RAW(When the subtree was created)RAW")
    .value("Repeated", sem::SubtreePeriod::Kind::Repeated, R"RAW(Last repeat time of the recurring tasks)RAW")
    .def("__iter__", [](sem::SubtreePeriod::Kind _self) -> PyEnumIterator<sem::SubtreePeriod::Kind> {
                     return
                     PyEnumIterator<sem::SubtreePeriod::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::SubtreePeriod>(m, "SubtreePeriod")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreePeriod {
                        sem::SubtreePeriod result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("kind", &sem::SubtreePeriod::kind, R"RAW(Time period kind -- not associated with point/range distinction)RAW")
    .def_readwrite("from_", &sem::SubtreePeriod::from, R"RAW(Clock start time)RAW")
    .def_readwrite("to", &sem::SubtreePeriod::to, R"RAW(Optional end of the clock)RAW")
    .def("operator==",
         static_cast<bool(sem::SubtreePeriod::*)(sem::SubtreePeriod const&) const>(&sem::SubtreePeriod::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::SubtreePeriod _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreePeriod _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::NamedProperty::SetMode>(m, "NamedPropertySetMode", type_registry_guard);
  pybind11::enum_<sem::NamedProperty::SetMode>(m, "NamedPropertySetMode")
    .value("Override", sem::NamedProperty::SetMode::Override)
    .value("Add", sem::NamedProperty::SetMode::Add)
    .value("Subtract", sem::NamedProperty::SetMode::Subtract)
    .def("__iter__", [](sem::NamedProperty::SetMode _self) -> PyEnumIterator<sem::NamedProperty::SetMode> {
                     return
                     PyEnumIterator<sem::NamedProperty::SetMode>
                     ();
                     })
    ;
  bind_enum_iterator<sem::NamedProperty::InheritanceMode>(m, "NamedPropertyInheritanceMode", type_registry_guard);
  pybind11::enum_<sem::NamedProperty::InheritanceMode>(m, "NamedPropertyInheritanceMode")
    .value("ThisAndSub", sem::NamedProperty::InheritanceMode::ThisAndSub)
    .value("OnlyThis", sem::NamedProperty::InheritanceMode::OnlyThis)
    .value("OnlySub", sem::NamedProperty::InheritanceMode::OnlySub)
    .def("__iter__", [](sem::NamedProperty::InheritanceMode _self) -> PyEnumIterator<sem::NamedProperty::InheritanceMode> {
                     return
                     PyEnumIterator<sem::NamedProperty::InheritanceMode>
                     ();
                     })
    ;
  pybind11::class_<sem::NamedProperty::Nonblocking>(m, "NamedPropertyNonblocking")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::Nonblocking {
                        sem::NamedProperty::Nonblocking result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isBlocking", &sem::NamedProperty::Nonblocking::isBlocking)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::Nonblocking::*)(sem::NamedProperty::Nonblocking const&) const>(&sem::NamedProperty::Nonblocking::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::Nonblocking _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::Nonblocking _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::Trigger>(m, "NamedPropertyTrigger")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::Trigger {
                        sem::NamedProperty::Trigger result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("operator==",
         static_cast<bool(sem::NamedProperty::Trigger::*)(sem::NamedProperty::Trigger const&) const>(&sem::NamedProperty::Trigger::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::Trigger _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::Trigger _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::ExportLatexClass>(m, "NamedPropertyExportLatexClass")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::ExportLatexClass {
                        sem::NamedProperty::ExportLatexClass result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("latexClass", &sem::NamedProperty::ExportLatexClass::latexClass)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::ExportLatexClass::*)(sem::NamedProperty::ExportLatexClass const&) const>(&sem::NamedProperty::ExportLatexClass::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::ExportLatexClass _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::ExportLatexClass _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::ExportLatexClassOptions>(m, "NamedPropertyExportLatexClassOptions")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::ExportLatexClassOptions {
                        sem::NamedProperty::ExportLatexClassOptions result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("options", &sem::NamedProperty::ExportLatexClassOptions::options)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::ExportLatexClassOptions::*)(sem::NamedProperty::ExportLatexClassOptions const&) const>(&sem::NamedProperty::ExportLatexClassOptions::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::ExportLatexClassOptions _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::ExportLatexClassOptions _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::ExportLatexHeader>(m, "NamedPropertyExportLatexHeader")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::ExportLatexHeader {
                        sem::NamedProperty::ExportLatexHeader result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("header", &sem::NamedProperty::ExportLatexHeader::header)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::ExportLatexHeader::*)(sem::NamedProperty::ExportLatexHeader const&) const>(&sem::NamedProperty::ExportLatexHeader::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::ExportLatexHeader _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::ExportLatexHeader _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::ExportLatexCompiler>(m, "NamedPropertyExportLatexCompiler")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::ExportLatexCompiler {
                        sem::NamedProperty::ExportLatexCompiler result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("compiler", &sem::NamedProperty::ExportLatexCompiler::compiler)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::ExportLatexCompiler::*)(sem::NamedProperty::ExportLatexCompiler const&) const>(&sem::NamedProperty::ExportLatexCompiler::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::ExportLatexCompiler _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::ExportLatexCompiler _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::Ordered>(m, "NamedPropertyOrdered")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::Ordered {
                        sem::NamedProperty::Ordered result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isOrdered", &sem::NamedProperty::Ordered::isOrdered)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::Ordered::*)(sem::NamedProperty::Ordered const&) const>(&sem::NamedProperty::Ordered::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::Ordered _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::Ordered _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::Effort>(m, "NamedPropertyEffort")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::Effort {
                        sem::NamedProperty::Effort result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("hours", &sem::NamedProperty::Effort::hours)
    .def_readwrite("minutes", &sem::NamedProperty::Effort::minutes)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::Effort::*)(sem::NamedProperty::Effort const&) const>(&sem::NamedProperty::Effort::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::Effort _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::Effort _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::NamedProperty::Visibility::Level>(m, "NamedPropertyVisibilityLevel", type_registry_guard);
  pybind11::enum_<sem::NamedProperty::Visibility::Level>(m, "NamedPropertyVisibilityLevel")
    .value("Folded", sem::NamedProperty::Visibility::Level::Folded)
    .value("Children", sem::NamedProperty::Visibility::Level::Children)
    .value("Content", sem::NamedProperty::Visibility::Level::Content)
    .value("All", sem::NamedProperty::Visibility::Level::All)
    .def("__iter__", [](sem::NamedProperty::Visibility::Level _self) -> PyEnumIterator<sem::NamedProperty::Visibility::Level> {
                     return
                     PyEnumIterator<sem::NamedProperty::Visibility::Level>
                     ();
                     })
    ;
  pybind11::class_<sem::NamedProperty::Visibility>(m, "NamedPropertyVisibility")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::Visibility {
                        sem::NamedProperty::Visibility result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("level", &sem::NamedProperty::Visibility::level)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::Visibility::*)(sem::NamedProperty::Visibility const&) const>(&sem::NamedProperty::Visibility::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::Visibility _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::Visibility _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::ExportOptions>(m, "NamedPropertyExportOptions")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::ExportOptions {
                        sem::NamedProperty::ExportOptions result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("backend", &sem::NamedProperty::ExportOptions::backend)
    .def_readwrite("values", &sem::NamedProperty::ExportOptions::values)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::ExportOptions::*)(sem::NamedProperty::ExportOptions const&) const>(&sem::NamedProperty::ExportOptions::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::ExportOptions _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::ExportOptions _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::Blocker>(m, "NamedPropertyBlocker")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::Blocker {
                        sem::NamedProperty::Blocker result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("blockers", &sem::NamedProperty::Blocker::blockers)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::Blocker::*)(sem::NamedProperty::Blocker const&) const>(&sem::NamedProperty::Blocker::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::Blocker _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::Blocker _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::Unnumbered>(m, "NamedPropertyUnnumbered")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::Unnumbered {
                        sem::NamedProperty::Unnumbered result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("operator==",
         static_cast<bool(sem::NamedProperty::Unnumbered::*)(sem::NamedProperty::Unnumbered const&) const>(&sem::NamedProperty::Unnumbered::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::Unnumbered _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::Unnumbered _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::Created>(m, "NamedPropertyCreated")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::Created {
                        sem::NamedProperty::Created result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("time", &sem::NamedProperty::Created::time)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::Created::*)(sem::NamedProperty::Created const&) const>(&sem::NamedProperty::Created::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::Created _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::Created _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::CustomArgs>(m, "NamedPropertyCustomArgs")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::CustomArgs {
                        sem::NamedProperty::CustomArgs result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::NamedProperty::CustomArgs::name, R"RAW(Original name of the property)RAW")
    .def_readwrite("sub", &sem::NamedProperty::CustomArgs::sub, R"RAW(Property target specialization)RAW")
    .def_readwrite("parameters", &sem::NamedProperty::CustomArgs::parameters, R"RAW(Property parameters)RAW")
    .def("operator==",
         static_cast<bool(sem::NamedProperty::CustomArgs::*)(sem::NamedProperty::CustomArgs const&) const>(&sem::NamedProperty::CustomArgs::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::CustomArgs _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::CustomArgs _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::CustomRaw>(m, "NamedPropertyCustomRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::CustomRaw {
                        sem::NamedProperty::CustomRaw result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::NamedProperty::CustomRaw::name, R"RAW(Original name of the property)RAW")
    .def_readwrite("value", &sem::NamedProperty::CustomRaw::value, R"RAW(Property value)RAW")
    .def("operator==",
         static_cast<bool(sem::NamedProperty::CustomRaw::*)(sem::NamedProperty::CustomRaw const&) const>(&sem::NamedProperty::CustomRaw::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::CustomRaw _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::CustomRaw _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::NamedProperty::Kind>(m, "NamedPropertyKind", type_registry_guard);
  pybind11::enum_<sem::NamedProperty::Kind>(m, "NamedPropertyKind")
    .value("Nonblocking", sem::NamedProperty::Kind::Nonblocking)
    .value("Trigger", sem::NamedProperty::Kind::Trigger)
    .value("ExportLatexClass", sem::NamedProperty::Kind::ExportLatexClass)
    .value("ExportLatexClassOptions", sem::NamedProperty::Kind::ExportLatexClassOptions)
    .value("ExportLatexHeader", sem::NamedProperty::Kind::ExportLatexHeader)
    .value("ExportLatexCompiler", sem::NamedProperty::Kind::ExportLatexCompiler)
    .value("Ordered", sem::NamedProperty::Kind::Ordered)
    .value("Effort", sem::NamedProperty::Kind::Effort)
    .value("Visibility", sem::NamedProperty::Kind::Visibility)
    .value("ExportOptions", sem::NamedProperty::Kind::ExportOptions)
    .value("Blocker", sem::NamedProperty::Kind::Blocker)
    .value("Unnumbered", sem::NamedProperty::Kind::Unnumbered)
    .value("Created", sem::NamedProperty::Kind::Created)
    .value("CustomArgs", sem::NamedProperty::Kind::CustomArgs)
    .value("CustomRaw", sem::NamedProperty::Kind::CustomRaw)
    .def("__iter__", [](sem::NamedProperty::Kind _self) -> PyEnumIterator<sem::NamedProperty::Kind> {
                     return
                     PyEnumIterator<sem::NamedProperty::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::NamedProperty>(m, "NamedProperty")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty {
                        sem::NamedProperty result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("mainSetRule", &sem::NamedProperty::mainSetRule)
    .def_readwrite("subSetRule", &sem::NamedProperty::subSetRule)
    .def_readwrite("inheritanceMode", &sem::NamedProperty::inheritanceMode)
    .def_readwrite("data", &sem::NamedProperty::data)
    .def("isMatching",
         static_cast<bool(sem::NamedProperty::*)(Str const&, Opt<Str> const&) const>(&sem::NamedProperty::isMatching),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt),
         R"RAW(Check if property matches specified kind and optional subkind. Built-in property checking is also done with this function -- 'created' etc.)RAW")
    .def("getName", static_cast<Str(sem::NamedProperty::*)() const>(&sem::NamedProperty::getName), R"RAW(Get non-normalized name of the property (for built-in and user))RAW")
    .def("getSubKind", static_cast<Opt<Str>(sem::NamedProperty::*)() const>(&sem::NamedProperty::getSubKind), R"RAW(Get non-normalized sub-kind for the property.)RAW")
    .def("operator==",
         static_cast<bool(sem::NamedProperty::*)(sem::NamedProperty const&) const>(&sem::NamedProperty::operator==),
         pybind11::arg("other"))
    .def("getNonblocking", static_cast<sem::NamedProperty::Nonblocking&(sem::NamedProperty::*)()>(&sem::NamedProperty::getNonblocking))
    .def("getTrigger", static_cast<sem::NamedProperty::Trigger&(sem::NamedProperty::*)()>(&sem::NamedProperty::getTrigger))
    .def("getExportLatexClass", static_cast<sem::NamedProperty::ExportLatexClass&(sem::NamedProperty::*)()>(&sem::NamedProperty::getExportLatexClass))
    .def("getExportLatexClassOptions", static_cast<sem::NamedProperty::ExportLatexClassOptions&(sem::NamedProperty::*)()>(&sem::NamedProperty::getExportLatexClassOptions))
    .def("getExportLatexHeader", static_cast<sem::NamedProperty::ExportLatexHeader&(sem::NamedProperty::*)()>(&sem::NamedProperty::getExportLatexHeader))
    .def("getExportLatexCompiler", static_cast<sem::NamedProperty::ExportLatexCompiler&(sem::NamedProperty::*)()>(&sem::NamedProperty::getExportLatexCompiler))
    .def("getOrdered", static_cast<sem::NamedProperty::Ordered&(sem::NamedProperty::*)()>(&sem::NamedProperty::getOrdered))
    .def("getEffort", static_cast<sem::NamedProperty::Effort&(sem::NamedProperty::*)()>(&sem::NamedProperty::getEffort))
    .def("getVisibility", static_cast<sem::NamedProperty::Visibility&(sem::NamedProperty::*)()>(&sem::NamedProperty::getVisibility))
    .def("getExportOptions", static_cast<sem::NamedProperty::ExportOptions&(sem::NamedProperty::*)()>(&sem::NamedProperty::getExportOptions))
    .def("getBlocker", static_cast<sem::NamedProperty::Blocker&(sem::NamedProperty::*)()>(&sem::NamedProperty::getBlocker))
    .def("getUnnumbered", static_cast<sem::NamedProperty::Unnumbered&(sem::NamedProperty::*)()>(&sem::NamedProperty::getUnnumbered))
    .def("getCreated", static_cast<sem::NamedProperty::Created&(sem::NamedProperty::*)()>(&sem::NamedProperty::getCreated))
    .def("getCustomArgs", static_cast<sem::NamedProperty::CustomArgs&(sem::NamedProperty::*)()>(&sem::NamedProperty::getCustomArgs))
    .def("getCustomRaw", static_cast<sem::NamedProperty::CustomRaw&(sem::NamedProperty::*)()>(&sem::NamedProperty::getCustomRaw))
    .def_static("getKindStatic",
                static_cast<sem::NamedProperty::Kind(*)(sem::NamedProperty::Data const&)>(&sem::NamedProperty::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<sem::NamedProperty::Kind(sem::NamedProperty::*)() const>(&sem::NamedProperty::getKind))
    .def("__repr__", [](sem::NamedProperty _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::None, sem::SemId<sem::None>, sem::Org>(m, "None")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::None {
                        sem::None result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::None _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::None _self, std::string name) -> pybind11::object {
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
  bind_enum_iterator<sem::Time::Repeat::Mode>(m, "TimeRepeatMode", type_registry_guard);
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
  bind_enum_iterator<sem::Time::Repeat::Period>(m, "TimeRepeatPeriod", type_registry_guard);
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
  bind_enum_iterator<sem::Time::TimeKind>(m, "TimeTimeKind", type_registry_guard);
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
  bind_enum_iterator<sem::Link::Kind>(m, "LinkKind", type_registry_guard);
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
  bind_enum_iterator<sem::BlockExport::Format>(m, "BlockExportFormat", type_registry_guard);
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
  bind_enum_iterator<sem::SubtreeLog::Priority::Action>(m, "SubtreeLogPriorityAction", type_registry_guard);
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
  bind_enum_iterator<sem::SubtreeLog::Kind>(m, "SubtreeLogKind", type_registry_guard);
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
         static_cast<Vec<sem::SubtreePeriod>(sem::Subtree::*)(IntSet<sem::SubtreePeriod::Kind>) const>(&sem::Subtree::getTimePeriods),
         pybind11::arg("kinds"))
    .def("getProperties",
         static_cast<Vec<sem::NamedProperty>(sem::Subtree::*)(Str const&, Opt<Str> const&) const>(&sem::Subtree::getProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", std::nullopt))
    .def("getProperty",
         static_cast<Opt<sem::NamedProperty>(sem::Subtree::*)(Str const&, Opt<Str> const&) const>(&sem::Subtree::getProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", std::nullopt))
    .def("removeProperty",
         static_cast<void(sem::Subtree::*)(Str const&, Opt<Str> const&)>(&sem::Subtree::removeProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", std::nullopt),
         R"RAW(Remove all instances of the property with matching kind/subkind from the property list)RAW")
    .def("setProperty",
         static_cast<void(sem::Subtree::*)(sem::NamedProperty const&)>(&sem::Subtree::setProperty),
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
  bind_enum_iterator<sem::AnnotatedParagraph::AnnotationKind>(m, "AnnotatedParagraphAnnotationKind", type_registry_guard);
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
  bind_enum_iterator<sem::ListItem::Checkbox>(m, "ListItemCheckbox", type_registry_guard);
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
         static_cast<Vec<sem::NamedProperty>(sem::DocumentOptions::*)(Str const&, Opt<Str> const&) const>(&sem::DocumentOptions::getProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt))
    .def("getProperty",
         static_cast<Opt<sem::NamedProperty>(sem::DocumentOptions::*)(Str const&, Opt<Str> const&) const>(&sem::DocumentOptions::getProperty),
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
         static_cast<Vec<sem::NamedProperty>(sem::Document::*)(Str const&, Opt<Str> const&) const>(&sem::Document::getProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt))
    .def("getProperty",
         static_cast<Opt<sem::NamedProperty>(sem::Document::*)(Str const&, Opt<Str> const&) const>(&sem::Document::getProperty),
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
  bind_enum_iterator<sem::Include::Kind>(m, "IncludeKind", type_registry_guard);
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
  bind_enum_iterator<InitialSubtreeVisibility>(m, "InitialSubtreeVisibility", type_registry_guard);
  pybind11::enum_<InitialSubtreeVisibility>(m, "InitialSubtreeVisibility")
    .value("Overview", InitialSubtreeVisibility::Overview)
    .value("Content", InitialSubtreeVisibility::Content)
    .value("ShowAll", InitialSubtreeVisibility::ShowAll)
    .value("Show2Levels", InitialSubtreeVisibility::Show2Levels)
    .value("Show3Levels", InitialSubtreeVisibility::Show3Levels)
    .value("Show4Levels", InitialSubtreeVisibility::Show4Levels)
    .value("Show5Levels", InitialSubtreeVisibility::Show5Levels)
    .value("ShowEverything", InitialSubtreeVisibility::ShowEverything)
    .def("__iter__", [](InitialSubtreeVisibility _self) -> PyEnumIterator<InitialSubtreeVisibility> {
                     return
                     PyEnumIterator<InitialSubtreeVisibility>
                     ();
                     })
    ;
  bind_enum_iterator<BlockCodeResults>(m, "BlockCodeResults", type_registry_guard);
  pybind11::enum_<BlockCodeResults>(m, "BlockCodeResults")
    .value("Replace", BlockCodeResults::Replace, R"RAW(Remove old result, replace with new value)RAW")
    .def("__iter__", [](BlockCodeResults _self) -> PyEnumIterator<BlockCodeResults> {
                     return
                     PyEnumIterator<BlockCodeResults>
                     ();
                     })
    ;
  bind_enum_iterator<BlockCodeExports>(m, "BlockCodeExports", type_registry_guard);
  pybind11::enum_<BlockCodeExports>(m, "BlockCodeExports")
    .value("None", BlockCodeExports::None, R"RAW(Hide both original code and run result)RAW")
    .value("Both", BlockCodeExports::Both, R"RAW(Show output and code)RAW")
    .value("Code", BlockCodeExports::Code, R"RAW(Show only code)RAW")
    .value("Results", BlockCodeExports::Results, R"RAW(Show only evaluation results)RAW")
    .def("__iter__", [](BlockCodeExports _self) -> PyEnumIterator<BlockCodeExports> {
                     return
                     PyEnumIterator<BlockCodeExports>
                     ();
                     })
    ;
  bind_enum_iterator<OrgSpecName>(m, "OrgSpecName", type_registry_guard);
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
  bind_enum_iterator<OrgNodeKind>(m, "OrgNodeKind", type_registry_guard);
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
  bind_enum_iterator<OrgSemKind>(m, "OrgSemKind", type_registry_guard);
  pybind11::enum_<OrgSemKind>(m, "OrgSemKind")
    .value("None", OrgSemKind::None)
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
  bind_enum_iterator<sem::SubnodeVisitorCtxPart::Kind>(m, "SubnodeVisitorCtxPartKind", type_registry_guard);
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
  bind_enum_iterator<LeafFieldType>(m, "LeafFieldType", type_registry_guard);
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
  m.def("asOneNode",
        static_cast<sem::SemId<sem::Org>(*)(sem::OrgArg)>(&sem::asOneNode),
        pybind11::arg("arg"));
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