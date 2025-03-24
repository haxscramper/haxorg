/* clang-format off */
#undef slots
#define PYBIND11_DETAILED_ERROR_MESSAGES
#include <pybind11/pybind11.h>
#include <haxorg/sem/SemOrg.hpp>
#include <pybind11/stl.h>
#include "pyhaxorg_manual_impl.hpp"
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::Org>>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::Org>>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::LispCode>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::LispCode>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::Tblfm::Expr>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::Tblfm::Expr>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::Tblfm::Assign::Flag>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::Tblfm::Assign::Flag>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::Tblfm::Assign>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::Tblfm::Assign>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::AttrValue::DimensionSpan>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::AttrValue::DimensionSpan>)
PYBIND11_MAKE_OPAQUE(std::vector<hstd::Str>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::Str>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::HashTagText>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::HashTagText>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::HashTagFlat>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::HashTagFlat>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::AttrValue>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::AttrValue>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<hstd::Str, org::sem::AttrList>)
PYBIND11_MAKE_OPAQUE(hstd::UnorderedMap<hstd::Str, org::sem::AttrList>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::OrgCodeEvalInput::Var>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::OrgCodeEvalInput::Var>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::ColumnView::Column>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::ColumnView::Column>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::BlockCodeLine::Part>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::BlockCodeLine::Part>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<hstd::Str, hstd::Str>)
PYBIND11_MAKE_OPAQUE(hstd::UnorderedMap<hstd::Str, hstd::Str>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::ErrorItem>>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::BlockCodeEvalResult>>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::Symbol::Param>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::Symbol::Param>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::OrgCodeEvalOutput>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::OrgCodeEvalOutput>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::BlockCodeLine>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::BlockCodeLine>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::HashTag>>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::HashTag>>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::SubtreeLog>>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::NamedProperty>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::NamedProperty>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::SubtreePeriod>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::SubtreePeriod>)
PYBIND11_MAKE_OPAQUE(hstd::IntSet<org::sem::SubtreePeriod::Kind>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::Cell>>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::Cell>>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::Row>>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::Row>>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::BigIdent>>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::BigIdent>>)
PYBIND11_MAKE_OPAQUE(std::vector<hstd::UserTime>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::UserTime>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::Time>>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::Time>>)
PYBIND11_MAKE_OPAQUE(std::vector<org::sem::OrgJson>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::sem::OrgJson>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<org::sem::HashTagFlat, org::AstTrackingPath>)
PYBIND11_MAKE_OPAQUE(hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingPath>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<hstd::Str, org::AstTrackingAlternatives>)
PYBIND11_MAKE_OPAQUE(hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<org::sem::HashTagFlat, org::AstTrackingAlternatives>)
PYBIND11_MAKE_OPAQUE(hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingAlternatives>)
PYBIND11_MAKE_OPAQUE(std::vector<hstd::SequenceSegment>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::SequenceSegment>)
PYBIND11_MAKE_OPAQUE(std::vector<int>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<int>)
PYBIND11_MAKE_OPAQUE(std::vector<hstd::SequenceAnnotationTag>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::SequenceAnnotationTag>)
PYBIND11_MAKE_OPAQUE(std::vector<org::AstTrackingGroup>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<org::AstTrackingGroup>)
PYBIND11_MAKE_OPAQUE(std::vector<hstd::SequenceAnnotation>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::SequenceAnnotation>)
PYBIND11_MAKE_OPAQUE(std::vector<hstd::SequenceSegmentGroup>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::SequenceSegmentGroup>)
PYBIND11_MODULE(pyhaxorg, m) {
  org::bind::python::PyTypeRegistryGuard type_registry_guard{};
  bind_vector<org::sem::SemId<org::sem::Org>>(m, "VecOfSemIdOfOrg", type_registry_guard);
  bind_vector<org::sem::LispCode>(m, "VecOfLispCode", type_registry_guard);
  bind_vector<org::sem::Tblfm::Expr>(m, "VecOfTblfmExpr", type_registry_guard);
  bind_vector<org::sem::Tblfm::Assign::Flag>(m, "VecOfTblfmAssignFlag", type_registry_guard);
  bind_vector<org::sem::Tblfm::Assign>(m, "VecOfTblfmAssign", type_registry_guard);
  bind_vector<org::sem::AttrValue::DimensionSpan>(m, "VecOfAttrValueDimensionSpan", type_registry_guard);
  bind_vector<hstd::Str>(m, "VecOfStr", type_registry_guard);
  bind_vector<org::sem::HashTagText>(m, "VecOfHashTagText", type_registry_guard);
  bind_vector<org::sem::HashTagFlat>(m, "VecOfHashTagFlat", type_registry_guard);
  bind_vector<org::sem::AttrValue>(m, "VecOfAttrValue", type_registry_guard);
  bind_unordered_map<hstd::Str, org::sem::AttrList>(m, "UnorderedMapOfStrAttrList", type_registry_guard);
  bind_vector<org::sem::OrgCodeEvalInput::Var>(m, "VecOfOrgCodeEvalInputVar", type_registry_guard);
  bind_vector<org::sem::ColumnView::Column>(m, "VecOfColumnViewColumn", type_registry_guard);
  bind_vector<org::sem::BlockCodeLine::Part>(m, "VecOfBlockCodeLinePart", type_registry_guard);
  bind_unordered_map<hstd::Str, hstd::Str>(m, "UnorderedMapOfStrStr", type_registry_guard);
  bind_vector<org::sem::SemId<org::sem::ErrorItem>>(m, "VecOfSemIdOfErrorItem", type_registry_guard);
  bind_vector<org::sem::SemId<org::sem::BlockCodeEvalResult>>(m, "VecOfSemIdOfBlockCodeEvalResult", type_registry_guard);
  bind_vector<org::sem::Symbol::Param>(m, "VecOfSymbolParam", type_registry_guard);
  bind_vector<org::sem::OrgCodeEvalOutput>(m, "VecOfOrgCodeEvalOutput", type_registry_guard);
  bind_vector<org::sem::BlockCodeLine>(m, "VecOfBlockCodeLine", type_registry_guard);
  bind_vector<org::sem::SemId<org::sem::HashTag>>(m, "VecOfSemIdOfHashTag", type_registry_guard);
  bind_vector<org::sem::SemId<org::sem::SubtreeLog>>(m, "VecOfSemIdOfSubtreeLog", type_registry_guard);
  bind_vector<org::sem::NamedProperty>(m, "VecOfNamedProperty", type_registry_guard);
  bind_vector<org::sem::SubtreePeriod>(m, "VecOfSubtreePeriod", type_registry_guard);
  bind_int_set<org::sem::SubtreePeriod::Kind>(m, "IntSetOfSubtreePeriodKind", type_registry_guard);
  bind_vector<org::sem::SemId<org::sem::Cell>>(m, "VecOfSemIdOfCell", type_registry_guard);
  bind_vector<org::sem::SemId<org::sem::Row>>(m, "VecOfSemIdOfRow", type_registry_guard);
  bind_vector<org::sem::SemId<org::sem::BigIdent>>(m, "VecOfSemIdOfBigIdent", type_registry_guard);
  bind_vector<hstd::UserTime>(m, "VecOfUserTime", type_registry_guard);
  bind_vector<org::sem::SemId<org::sem::Time>>(m, "VecOfSemIdOfTime", type_registry_guard);
  bind_vector<org::sem::OrgJson>(m, "VecOfOrgJson", type_registry_guard);
  bind_unordered_map<org::sem::HashTagFlat, org::AstTrackingPath>(m, "UnorderedMapOfHashTagFlatAstTrackingPath", type_registry_guard);
  bind_unordered_map<hstd::Str, org::AstTrackingAlternatives>(m, "UnorderedMapOfStrAstTrackingAlternatives", type_registry_guard);
  bind_unordered_map<org::sem::HashTagFlat, org::AstTrackingAlternatives>(m, "UnorderedMapOfHashTagFlatAstTrackingAlternatives", type_registry_guard);
  bind_vector<hstd::SequenceSegment>(m, "VecOfSequenceSegment", type_registry_guard);
  bind_vector<int>(m, "VecOfint", type_registry_guard);
  bind_vector<hstd::SequenceAnnotationTag>(m, "VecOfSequenceAnnotationTag", type_registry_guard);
  bind_vector<org::AstTrackingGroup>(m, "VecOfAstTrackingGroup", type_registry_guard);
  bind_vector<hstd::SequenceAnnotation>(m, "VecOfSequenceAnnotation", type_registry_guard);
  bind_vector<hstd::SequenceSegmentGroup>(m, "VecOfSequenceSegmentGroup", type_registry_guard);
  pybind11::class_<org::sem::Org, org::sem::SemId<org::sem::Org>>(m, "Org")
    .def_readwrite("loc", &org::sem::Org::loc, R"RAW(\brief Location of the node in the original source file)RAW")
    .def_readwrite("subnodes", &org::sem::Org::subnodes, R"RAW(\brief List of subnodes.

Some of the derived nodes don't make the use of subnode list
(word, punctuation etc), but it was left on the top level of the
hierarchy for conveinience purposes. It is not expected that 'any'
node can have subnodes.)RAW")
    .def("getKind", static_cast<OrgSemKind(org::sem::Org::*)() const>(&org::sem::Org::getKind), R"RAW(\brief Get kind of this sem node)RAW")
    .def("isGenerated", static_cast<bool(org::sem::Org::*)() const>(&org::sem::Org::isGenerated), R"RAW(\brief Whether original node adapter is missing)RAW")
    .def("push_back",
         static_cast<void(org::sem::Org::*)(org::sem::SemId<org::sem::Org>)>(&org::sem::Org::push_back),
         pybind11::arg("sub"))
    .def("insert",
         static_cast<void(org::sem::Org::*)(int, org::sem::SemId<org::sem::Org>)>(&org::sem::Org::insert),
         pybind11::arg("pos"),
         pybind11::arg("node"))
    .def("at",
         static_cast<org::sem::SemId<org::sem::Org>(org::sem::Org::*)(int) const>(&org::sem::Org::at),
         pybind11::arg("idx"),
         R"RAW(\brief Get subnode at specified index)RAW")
    .def("is_",
         static_cast<bool(org::sem::Org::*)(OrgSemKind) const>(&org::sem::Org::is),
         pybind11::arg("kind"))
    .def("__getitem__",
         static_cast<org::sem::SemId<org::sem::Org>(org::sem::Org::*)(int) const>(&org::sem::Org::at),
         pybind11::arg("idx"))
    .def("__iter__",
         [](org::sem::Org const& node) -> auto {
         return pybind11::make_iterator(node.subnodes.begin(), node.subnodes.end());
         },
         pybind11::keep_alive<0, 1>())
    ;
  pybind11::class_<org::parse::LineCol>(m, "parseLineCol")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::parse::LineCol {
                        org::parse::LineCol result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("line", &org::parse::LineCol::line)
    .def_readwrite("column", &org::parse::LineCol::column)
    .def_readwrite("pos", &org::parse::LineCol::pos)
    .def("__repr__", [](org::parse::LineCol _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::parse::LineCol _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LispCode::Call>(m, "LispCodeCall")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LispCode::Call {
                        org::sem::LispCode::Call result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::LispCode::Call::name)
    .def_readwrite("args", &org::sem::LispCode::Call::args)
    .def("operator==",
         static_cast<bool(org::sem::LispCode::Call::*)(org::sem::LispCode::Call const&) const>(&org::sem::LispCode::Call::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Call _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Call _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LispCode::List>(m, "LispCodeList")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LispCode::List {
                        org::sem::LispCode::List result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("items", &org::sem::LispCode::List::items)
    .def("operator==",
         static_cast<bool(org::sem::LispCode::List::*)(org::sem::LispCode::List const&) const>(&org::sem::LispCode::List::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LispCode::List _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::List _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LispCode::KeyValue>(m, "LispCodeKeyValue")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LispCode::KeyValue {
                        org::sem::LispCode::KeyValue result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::LispCode::KeyValue::name)
    .def_readwrite("value", &org::sem::LispCode::KeyValue::value)
    .def("operator==",
         static_cast<bool(org::sem::LispCode::KeyValue::*)(org::sem::LispCode::KeyValue const&) const>(&org::sem::LispCode::KeyValue::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LispCode::KeyValue _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::KeyValue _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LispCode::Number>(m, "LispCodeNumber")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LispCode::Number {
                        org::sem::LispCode::Number result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &org::sem::LispCode::Number::value)
    .def("operator==",
         static_cast<bool(org::sem::LispCode::Number::*)(org::sem::LispCode::Number const&) const>(&org::sem::LispCode::Number::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Number _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Number _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LispCode::Text>(m, "LispCodeText")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LispCode::Text {
                        org::sem::LispCode::Text result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &org::sem::LispCode::Text::value)
    .def("operator==",
         static_cast<bool(org::sem::LispCode::Text::*)(org::sem::LispCode::Text const&) const>(&org::sem::LispCode::Text::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Text _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Text _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LispCode::Ident>(m, "LispCodeIdent")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LispCode::Ident {
                        org::sem::LispCode::Ident result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::LispCode::Ident::name)
    .def("operator==",
         static_cast<bool(org::sem::LispCode::Ident::*)(org::sem::LispCode::Ident const&) const>(&org::sem::LispCode::Ident::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Ident _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Ident _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LispCode::Boolean>(m, "LispCodeBoolean")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LispCode::Boolean {
                        org::sem::LispCode::Boolean result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &org::sem::LispCode::Boolean::value)
    .def("operator==",
         static_cast<bool(org::sem::LispCode::Boolean::*)(org::sem::LispCode::Boolean const&) const>(&org::sem::LispCode::Boolean::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Boolean _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Boolean _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LispCode::Real>(m, "LispCodeReal")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LispCode::Real {
                        org::sem::LispCode::Real result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &org::sem::LispCode::Real::value)
    .def("operator==",
         static_cast<bool(org::sem::LispCode::Real::*)(org::sem::LispCode::Real const&) const>(&org::sem::LispCode::Real::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Real _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Real _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::LispCode::Kind>(m, "LispCodeKind", type_registry_guard);
  pybind11::enum_<org::sem::LispCode::Kind>(m, "LispCodeKind")
    .value("Call", org::sem::LispCode::Kind::Call)
    .value("List", org::sem::LispCode::Kind::List)
    .value("KeyValue", org::sem::LispCode::Kind::KeyValue)
    .value("Number", org::sem::LispCode::Kind::Number)
    .value("Text", org::sem::LispCode::Kind::Text)
    .value("Ident", org::sem::LispCode::Kind::Ident)
    .value("Boolean", org::sem::LispCode::Kind::Boolean)
    .value("Real", org::sem::LispCode::Kind::Real)
    .def("__iter__", [](org::sem::LispCode::Kind _self) -> org::bind::python::PyEnumIterator<org::sem::LispCode::Kind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::LispCode::Kind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::LispCode>(m, "LispCode")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LispCode {
                        org::sem::LispCode result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &org::sem::LispCode::data)
    .def("operator==",
         static_cast<bool(org::sem::LispCode::*)(org::sem::LispCode const&) const>(&org::sem::LispCode::operator==),
         pybind11::arg("other"))
    .def("isCall", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isCall))
    .def("getCall", static_cast<org::sem::LispCode::Call&(org::sem::LispCode::*)()>(&org::sem::LispCode::getCall))
    .def("isList", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isList))
    .def("getList", static_cast<org::sem::LispCode::List&(org::sem::LispCode::*)()>(&org::sem::LispCode::getList))
    .def("isKeyValue", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isKeyValue))
    .def("getKeyValue", static_cast<org::sem::LispCode::KeyValue&(org::sem::LispCode::*)()>(&org::sem::LispCode::getKeyValue))
    .def("isNumber", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isNumber))
    .def("getNumber", static_cast<org::sem::LispCode::Number&(org::sem::LispCode::*)()>(&org::sem::LispCode::getNumber))
    .def("isText", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isText))
    .def("getText", static_cast<org::sem::LispCode::Text&(org::sem::LispCode::*)()>(&org::sem::LispCode::getText))
    .def("isIdent", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isIdent))
    .def("getIdent", static_cast<org::sem::LispCode::Ident&(org::sem::LispCode::*)()>(&org::sem::LispCode::getIdent))
    .def("isBoolean", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isBoolean))
    .def("getBoolean", static_cast<org::sem::LispCode::Boolean&(org::sem::LispCode::*)()>(&org::sem::LispCode::getBoolean))
    .def("isReal", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isReal))
    .def("getReal", static_cast<org::sem::LispCode::Real&(org::sem::LispCode::*)()>(&org::sem::LispCode::getReal))
    .def_static("getKindStatic",
                static_cast<org::sem::LispCode::Kind(*)(org::sem::LispCode::Data const&)>(&org::sem::LispCode::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<org::sem::LispCode::Kind(org::sem::LispCode::*)() const>(&org::sem::LispCode::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::LispCode::*)() const>(&org::sem::LispCode::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::LispCode::Data const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::LispCode::Kind(org::sem::LispCode::*)() const>(&org::sem::LispCode::sub_variant_get_kind))
    .def("__repr__", [](org::sem::LispCode _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Tblfm::Expr::AxisRef::Position::Index>(m, "TblfmExprAxisRefPositionIndex")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Tblfm::Expr::AxisRef::Position::Index {
                        org::sem::Tblfm::Expr::AxisRef::Position::Index result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("index", &org::sem::Tblfm::Expr::AxisRef::Position::Index::index)
    .def("operator==",
         static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::Index::*)(org::sem::Tblfm::Expr::AxisRef::Position::Index const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::Index::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::AxisRef::Position::Index _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::AxisRef::Position::Index _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Tblfm::Expr::AxisRef::Position::Name>(m, "TblfmExprAxisRefPositionName")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Tblfm::Expr::AxisRef::Position::Name {
                        org::sem::Tblfm::Expr::AxisRef::Position::Name result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::Tblfm::Expr::AxisRef::Position::Name::name)
    .def("operator==",
         static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::Name::*)(org::sem::Tblfm::Expr::AxisRef::Position::Name const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::Name::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::AxisRef::Position::Name _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::AxisRef::Position::Name _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::Tblfm::Expr::AxisRef::Position::Kind>(m, "TblfmExprAxisRefPositionKind", type_registry_guard);
  pybind11::enum_<org::sem::Tblfm::Expr::AxisRef::Position::Kind>(m, "TblfmExprAxisRefPositionKind")
    .value("Index", org::sem::Tblfm::Expr::AxisRef::Position::Kind::Index)
    .value("Name", org::sem::Tblfm::Expr::AxisRef::Position::Kind::Name)
    .def("__iter__", [](org::sem::Tblfm::Expr::AxisRef::Position::Kind _self) -> org::bind::python::PyEnumIterator<org::sem::Tblfm::Expr::AxisRef::Position::Kind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::Tblfm::Expr::AxisRef::Position::Kind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::Tblfm::Expr::AxisRef::Position>(m, "TblfmExprAxisRefPosition")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Tblfm::Expr::AxisRef::Position {
                        org::sem::Tblfm::Expr::AxisRef::Position result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &org::sem::Tblfm::Expr::AxisRef::Position::data)
    .def("operator==",
         static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)(org::sem::Tblfm::Expr::AxisRef::Position const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::operator==),
         pybind11::arg("other"))
    .def("isIndex", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::isIndex))
    .def("getIndex", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Index&(org::sem::Tblfm::Expr::AxisRef::Position::*)()>(&org::sem::Tblfm::Expr::AxisRef::Position::getIndex))
    .def("isName", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::isName))
    .def("getName", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Name&(org::sem::Tblfm::Expr::AxisRef::Position::*)()>(&org::sem::Tblfm::Expr::AxisRef::Position::getName))
    .def_static("getKindStatic",
                static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(*)(org::sem::Tblfm::Expr::AxisRef::Position::Data const&)>(&org::sem::Tblfm::Expr::AxisRef::Position::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Data const&(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::sub_variant_get_kind))
    .def("__repr__", [](org::sem::Tblfm::Expr::AxisRef::Position _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::AxisRef::Position _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Tblfm::Expr::AxisRef>(m, "TblfmExprAxisRef")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Tblfm::Expr::AxisRef {
                        org::sem::Tblfm::Expr::AxisRef result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("col", &org::sem::Tblfm::Expr::AxisRef::col)
    .def_readwrite("row", &org::sem::Tblfm::Expr::AxisRef::row)
    .def("operator==",
         static_cast<bool(org::sem::Tblfm::Expr::AxisRef::*)(org::sem::Tblfm::Expr::AxisRef const&) const>(&org::sem::Tblfm::Expr::AxisRef::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::AxisRef _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::AxisRef _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Tblfm::Expr::AxisName>(m, "TblfmExprAxisName")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Tblfm::Expr::AxisName {
                        org::sem::Tblfm::Expr::AxisName result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::Tblfm::Expr::AxisName::name)
    .def("operator==",
         static_cast<bool(org::sem::Tblfm::Expr::AxisName::*)(org::sem::Tblfm::Expr::AxisName const&) const>(&org::sem::Tblfm::Expr::AxisName::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::AxisName _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::AxisName _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Tblfm::Expr::IntLiteral>(m, "TblfmExprIntLiteral")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Tblfm::Expr::IntLiteral {
                        org::sem::Tblfm::Expr::IntLiteral result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &org::sem::Tblfm::Expr::IntLiteral::value)
    .def("operator==",
         static_cast<bool(org::sem::Tblfm::Expr::IntLiteral::*)(org::sem::Tblfm::Expr::IntLiteral const&) const>(&org::sem::Tblfm::Expr::IntLiteral::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::IntLiteral _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::IntLiteral _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Tblfm::Expr::FloatLiteral>(m, "TblfmExprFloatLiteral")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Tblfm::Expr::FloatLiteral {
                        org::sem::Tblfm::Expr::FloatLiteral result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &org::sem::Tblfm::Expr::FloatLiteral::value)
    .def("operator==",
         static_cast<bool(org::sem::Tblfm::Expr::FloatLiteral::*)(org::sem::Tblfm::Expr::FloatLiteral const&) const>(&org::sem::Tblfm::Expr::FloatLiteral::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::FloatLiteral _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::FloatLiteral _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Tblfm::Expr::RangeRef>(m, "TblfmExprRangeRef")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Tblfm::Expr::RangeRef {
                        org::sem::Tblfm::Expr::RangeRef result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("first", &org::sem::Tblfm::Expr::RangeRef::first)
    .def_readwrite("last", &org::sem::Tblfm::Expr::RangeRef::last)
    .def("operator==",
         static_cast<bool(org::sem::Tblfm::Expr::RangeRef::*)(org::sem::Tblfm::Expr::RangeRef const&) const>(&org::sem::Tblfm::Expr::RangeRef::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::RangeRef _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::RangeRef _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Tblfm::Expr::Call>(m, "TblfmExprCall")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Tblfm::Expr::Call {
                        org::sem::Tblfm::Expr::Call result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::Tblfm::Expr::Call::name)
    .def_readwrite("args", &org::sem::Tblfm::Expr::Call::args)
    .def("operator==",
         static_cast<bool(org::sem::Tblfm::Expr::Call::*)(org::sem::Tblfm::Expr::Call const&) const>(&org::sem::Tblfm::Expr::Call::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::Call _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::Call _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Tblfm::Expr::Elisp>(m, "TblfmExprElisp")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Tblfm::Expr::Elisp {
                        org::sem::Tblfm::Expr::Elisp result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &org::sem::Tblfm::Expr::Elisp::value)
    .def("operator==",
         static_cast<bool(org::sem::Tblfm::Expr::Elisp::*)(org::sem::Tblfm::Expr::Elisp const&) const>(&org::sem::Tblfm::Expr::Elisp::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::Elisp _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::Elisp _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::Tblfm::Expr::Kind>(m, "TblfmExprKind", type_registry_guard);
  pybind11::enum_<org::sem::Tblfm::Expr::Kind>(m, "TblfmExprKind")
    .value("AxisRef", org::sem::Tblfm::Expr::Kind::AxisRef)
    .value("AxisName", org::sem::Tblfm::Expr::Kind::AxisName)
    .value("IntLiteral", org::sem::Tblfm::Expr::Kind::IntLiteral)
    .value("FloatLiteral", org::sem::Tblfm::Expr::Kind::FloatLiteral)
    .value("RangeRef", org::sem::Tblfm::Expr::Kind::RangeRef)
    .value("Call", org::sem::Tblfm::Expr::Kind::Call)
    .value("Elisp", org::sem::Tblfm::Expr::Kind::Elisp)
    .def("__iter__", [](org::sem::Tblfm::Expr::Kind _self) -> org::bind::python::PyEnumIterator<org::sem::Tblfm::Expr::Kind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::Tblfm::Expr::Kind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::Tblfm::Expr>(m, "TblfmExpr")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Tblfm::Expr {
                        org::sem::Tblfm::Expr result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &org::sem::Tblfm::Expr::data)
    .def("operator==",
         static_cast<bool(org::sem::Tblfm::Expr::*)(org::sem::Tblfm::Expr const&) const>(&org::sem::Tblfm::Expr::operator==),
         pybind11::arg("other"))
    .def("isAxisRef", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isAxisRef))
    .def("getAxisRef", static_cast<org::sem::Tblfm::Expr::AxisRef&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getAxisRef))
    .def("isAxisName", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isAxisName))
    .def("getAxisName", static_cast<org::sem::Tblfm::Expr::AxisName&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getAxisName))
    .def("isIntLiteral", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isIntLiteral))
    .def("getIntLiteral", static_cast<org::sem::Tblfm::Expr::IntLiteral&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getIntLiteral))
    .def("isFloatLiteral", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isFloatLiteral))
    .def("getFloatLiteral", static_cast<org::sem::Tblfm::Expr::FloatLiteral&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getFloatLiteral))
    .def("isRangeRef", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isRangeRef))
    .def("getRangeRef", static_cast<org::sem::Tblfm::Expr::RangeRef&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getRangeRef))
    .def("isCall", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isCall))
    .def("getCall", static_cast<org::sem::Tblfm::Expr::Call&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getCall))
    .def("isElisp", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isElisp))
    .def("getElisp", static_cast<org::sem::Tblfm::Expr::Elisp&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getElisp))
    .def_static("getKindStatic",
                static_cast<org::sem::Tblfm::Expr::Kind(*)(org::sem::Tblfm::Expr::Data const&)>(&org::sem::Tblfm::Expr::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<org::sem::Tblfm::Expr::Kind(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::Tblfm::Expr::Data const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::Tblfm::Expr::Kind(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::sub_variant_get_kind))
    .def("__repr__", [](org::sem::Tblfm::Expr _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::Tblfm::Assign::Flag>(m, "TblfmAssignFlag", type_registry_guard);
  pybind11::enum_<org::sem::Tblfm::Assign::Flag>(m, "TblfmAssignFlag")
    .value("CellLeftAlign", org::sem::Tblfm::Assign::Flag::CellLeftAlign, R"RAW(Left-align the result)RAW")
    .value("CellRightAlign", org::sem::Tblfm::Assign::Flag::CellRightAlign, R"RAW(Right-align the result)RAW")
    .value("CellCenterAlign", org::sem::Tblfm::Assign::Flag::CellCenterAlign, R"RAW(Center-align the result)RAW")
    .value("CellNumber", org::sem::Tblfm::Assign::Flag::CellNumber, R"RAW(Convert result to number/currency format)RAW")
    .value("CellExponential", org::sem::Tblfm::Assign::Flag::CellExponential, R"RAW(Use exponential notation for numbers)RAW")
    .value("CellFloating", org::sem::Tblfm::Assign::Flag::CellFloating, R"RAW(Use floating point format)RAW")
    .value("CellUnformat", org::sem::Tblfm::Assign::Flag::CellUnformat, R"RAW(Unformat values before calculating)RAW")
    .value("CellText", org::sem::Tblfm::Assign::Flag::CellText, R"RAW(Convert result to text)RAW")
    .value("CellBool", org::sem::Tblfm::Assign::Flag::CellBool, R"RAW(Display boolean values as t/nil)RAW")
    .value("CellDecimal", org::sem::Tblfm::Assign::Flag::CellDecimal, R"RAW(Fixed format with specified decimal places (e.g., ;D2))RAW")
    .value("CellPercentage", org::sem::Tblfm::Assign::Flag::CellPercentage, R"RAW(Percentage format)RAW")
    .value("CellHours", org::sem::Tblfm::Assign::Flag::CellHours, R"RAW(Convert to hours/minutes (HH:MM))RAW")
    .value("CellZero", org::sem::Tblfm::Assign::Flag::CellZero, R"RAW(Display zero as empty cell)RAW")
    .value("CellMarkInvalid", org::sem::Tblfm::Assign::Flag::CellMarkInvalid, R"RAW(Mark field as invalid if conversion fails)RAW")
    .value("CellQuote", org::sem::Tblfm::Assign::Flag::CellQuote, R"RAW(Quote field contents)RAW")
    .def("__iter__", [](org::sem::Tblfm::Assign::Flag _self) -> org::bind::python::PyEnumIterator<org::sem::Tblfm::Assign::Flag> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::Tblfm::Assign::Flag>
                     ();
                     })
    ;
  pybind11::class_<org::sem::Tblfm::Assign>(m, "TblfmAssign")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Tblfm::Assign {
                        org::sem::Tblfm::Assign result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &org::sem::Tblfm::Assign::target)
    .def_readwrite("expr", &org::sem::Tblfm::Assign::expr)
    .def_readwrite("flags", &org::sem::Tblfm::Assign::flags)
    .def("operator==",
         static_cast<bool(org::sem::Tblfm::Assign::*)(org::sem::Tblfm::Assign const&) const>(&org::sem::Tblfm::Assign::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Assign _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Assign _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Tblfm>(m, "Tblfm")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Tblfm {
                        org::sem::Tblfm result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("exprs", &org::sem::Tblfm::exprs)
    .def("operator==",
         static_cast<bool(org::sem::Tblfm::*)(org::sem::Tblfm const&) const>(&org::sem::Tblfm::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::Tblfm _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::AttrValue::Kind>(m, "AttrValueKind", type_registry_guard);
  pybind11::enum_<org::sem::AttrValue::Kind>(m, "AttrValueKind")
    .value("String", org::sem::AttrValue::Kind::String)
    .value("Boolean", org::sem::AttrValue::Kind::Boolean)
    .value("Integer", org::sem::AttrValue::Kind::Integer)
    .value("Float", org::sem::AttrValue::Kind::Float)
    .value("FileReference", org::sem::AttrValue::Kind::FileReference)
    .def("__iter__", [](org::sem::AttrValue::Kind _self) -> org::bind::python::PyEnumIterator<org::sem::AttrValue::Kind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::AttrValue::Kind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::AttrValue::DimensionSpan>(m, "AttrValueDimensionSpan")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::AttrValue::DimensionSpan {
                        org::sem::AttrValue::DimensionSpan result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("first", &org::sem::AttrValue::DimensionSpan::first)
    .def_readwrite("last", &org::sem::AttrValue::DimensionSpan::last)
    .def("operator==",
         static_cast<bool(org::sem::AttrValue::DimensionSpan::*)(org::sem::AttrValue::DimensionSpan const&) const>(&org::sem::AttrValue::DimensionSpan::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::AttrValue::DimensionSpan _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrValue::DimensionSpan _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::AttrValue::TextValue>(m, "AttrValueTextValue")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::AttrValue::TextValue {
                        org::sem::AttrValue::TextValue result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &org::sem::AttrValue::TextValue::value)
    .def("operator==",
         static_cast<bool(org::sem::AttrValue::TextValue::*)(org::sem::AttrValue::TextValue const&) const>(&org::sem::AttrValue::TextValue::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::AttrValue::TextValue _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrValue::TextValue _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::AttrValue::FileReference>(m, "AttrValueFileReference")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::AttrValue::FileReference {
                        org::sem::AttrValue::FileReference result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("file", &org::sem::AttrValue::FileReference::file)
    .def_readwrite("reference", &org::sem::AttrValue::FileReference::reference)
    .def("operator==",
         static_cast<bool(org::sem::AttrValue::FileReference::*)(org::sem::AttrValue::FileReference const&) const>(&org::sem::AttrValue::FileReference::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::AttrValue::FileReference _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrValue::FileReference _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::AttrValue::LispValue>(m, "AttrValueLispValue")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::AttrValue::LispValue {
                        org::sem::AttrValue::LispValue result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("code", &org::sem::AttrValue::LispValue::code)
    .def("operator==",
         static_cast<bool(org::sem::AttrValue::LispValue::*)(org::sem::AttrValue::LispValue const&) const>(&org::sem::AttrValue::LispValue::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::AttrValue::LispValue _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrValue::LispValue _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::AttrValue::DataKind>(m, "AttrValueDataKind", type_registry_guard);
  pybind11::enum_<org::sem::AttrValue::DataKind>(m, "AttrValueDataKind")
    .value("TextValue", org::sem::AttrValue::DataKind::TextValue)
    .value("FileReference", org::sem::AttrValue::DataKind::FileReference)
    .value("LispValue", org::sem::AttrValue::DataKind::LispValue)
    .def("__iter__", [](org::sem::AttrValue::DataKind _self) -> org::bind::python::PyEnumIterator<org::sem::AttrValue::DataKind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::AttrValue::DataKind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::AttrValue>(m, "AttrValue")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::AttrValue {
                        org::sem::AttrValue result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::AttrValue::name)
    .def_readwrite("varname", &org::sem::AttrValue::varname)
    .def_readwrite("span", &org::sem::AttrValue::span)
    .def_readwrite("isQuoted", &org::sem::AttrValue::isQuoted, R"RAW(If the original value was explicitly quoted in the org-mode code)RAW")
    .def_readwrite("data", &org::sem::AttrValue::data)
    .def("getBool", static_cast<hstd::Opt<bool>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getBool))
    .def("getInt", static_cast<hstd::Opt<int>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getInt))
    .def("getString", static_cast<hstd::Str(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getString))
    .def("getFile", static_cast<hstd::Str(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getFile))
    .def("getReference", static_cast<hstd::Str(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getReference))
    .def("getDouble", static_cast<hstd::Opt<double>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getDouble))
    .def("operator==",
         static_cast<bool(org::sem::AttrValue::*)(org::sem::AttrValue const&) const>(&org::sem::AttrValue::operator==),
         pybind11::arg("other"))
    .def("isTextValue", static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isTextValue))
    .def("getTextValue", static_cast<org::sem::AttrValue::TextValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getTextValue))
    .def("isFileReference", static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isFileReference))
    .def("getFileReference", static_cast<org::sem::AttrValue::FileReference&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getFileReference))
    .def("isLispValue", static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isLispValue))
    .def("getLispValue", static_cast<org::sem::AttrValue::LispValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getLispValue))
    .def_static("getDataKindStatic",
                static_cast<org::sem::AttrValue::DataKind(*)(org::sem::AttrValue::DataVariant const&)>(&org::sem::AttrValue::getDataKind),
                pybind11::arg("__input"))
    .def("getDataKind", static_cast<org::sem::AttrValue::DataKind(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getDataKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::AttrValue::DataVariant const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::AttrValue::DataKind(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::sub_variant_get_kind))
    .def("__repr__", [](org::sem::AttrValue _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrValue _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::HashTagFlat>(m, "HashTagFlat")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::HashTagFlat {
                        org::sem::HashTagFlat result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("tags", &org::sem::HashTagFlat::tags)
    .def("operator==",
         static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator==),
         pybind11::arg("other"))
    .def("operator<",
         static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator<),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::HashTagFlat _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::HashTagFlat _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::HashTagText>(m, "HashTagText")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::HashTagText {
                        org::sem::HashTagText result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("head", &org::sem::HashTagText::head, R"RAW(Main part of the tag)RAW")
    .def_readwrite("subtags", &org::sem::HashTagText::subtags, R"RAW(List of nested tags)RAW")
    .def("operator==",
         static_cast<bool(org::sem::HashTagText::*)(org::sem::HashTagText const&) const>(&org::sem::HashTagText::operator==),
         pybind11::arg("other"))
    .def("prefixMatch",
         static_cast<bool(org::sem::HashTagText::*)(hstd::Vec<hstd::Str> const&) const>(&org::sem::HashTagText::prefixMatch),
         pybind11::arg("prefix"),
         R"RAW(Check if list of tag names is a prefix for either of the nested hash tags in this one)RAW")
    .def("getFlatHashes",
         static_cast<hstd::Vec<org::sem::HashTagFlat>(org::sem::HashTagText::*)(bool) const>(&org::sem::HashTagText::getFlatHashes),
         pybind11::arg_v("withIntermediate", true),
         R"RAW(Get flat list of expanded hashtags)RAW")
    .def("__repr__", [](org::sem::HashTagText _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::HashTagText _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::SubtreePath>(m, "SubtreePath")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::SubtreePath {
                        org::sem::SubtreePath result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("path", &org::sem::SubtreePath::path)
    .def("operator==",
         static_cast<bool(org::sem::SubtreePath::*)(org::sem::SubtreePath const&) const>(&org::sem::SubtreePath::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::SubtreePath _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreePath _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LinkTarget::Raw>(m, "LinkTargetRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LinkTarget::Raw {
                        org::sem::LinkTarget::Raw result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &org::sem::LinkTarget::Raw::text)
    .def("operator==",
         static_cast<bool(org::sem::LinkTarget::Raw::*)(org::sem::LinkTarget::Raw const&) const>(&org::sem::LinkTarget::Raw::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Raw _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Raw _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LinkTarget::Id>(m, "LinkTargetId")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LinkTarget::Id {
                        org::sem::LinkTarget::Id result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &org::sem::LinkTarget::Id::text)
    .def("operator==",
         static_cast<bool(org::sem::LinkTarget::Id::*)(org::sem::LinkTarget::Id const&) const>(&org::sem::LinkTarget::Id::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Id _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Id _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LinkTarget::CustomId>(m, "LinkTargetCustomId")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LinkTarget::CustomId {
                        org::sem::LinkTarget::CustomId result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &org::sem::LinkTarget::CustomId::text)
    .def("operator==",
         static_cast<bool(org::sem::LinkTarget::CustomId::*)(org::sem::LinkTarget::CustomId const&) const>(&org::sem::LinkTarget::CustomId::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::CustomId _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::CustomId _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LinkTarget::SubtreeTitle>(m, "LinkTargetSubtreeTitle")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LinkTarget::SubtreeTitle {
                        org::sem::LinkTarget::SubtreeTitle result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("title", &org::sem::LinkTarget::SubtreeTitle::title)
    .def_readwrite("level", &org::sem::LinkTarget::SubtreeTitle::level)
    .def("operator==",
         static_cast<bool(org::sem::LinkTarget::SubtreeTitle::*)(org::sem::LinkTarget::SubtreeTitle const&) const>(&org::sem::LinkTarget::SubtreeTitle::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::SubtreeTitle _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::SubtreeTitle _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LinkTarget::Person>(m, "LinkTargetPerson")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LinkTarget::Person {
                        org::sem::LinkTarget::Person result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::LinkTarget::Person::name)
    .def("operator==",
         static_cast<bool(org::sem::LinkTarget::Person::*)(org::sem::LinkTarget::Person const&) const>(&org::sem::LinkTarget::Person::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Person _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Person _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LinkTarget::UserProtocol>(m, "LinkTargetUserProtocol")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LinkTarget::UserProtocol {
                        org::sem::LinkTarget::UserProtocol result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("protocol", &org::sem::LinkTarget::UserProtocol::protocol)
    .def_readwrite("target", &org::sem::LinkTarget::UserProtocol::target)
    .def("operator==",
         static_cast<bool(org::sem::LinkTarget::UserProtocol::*)(org::sem::LinkTarget::UserProtocol const&) const>(&org::sem::LinkTarget::UserProtocol::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::UserProtocol _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::UserProtocol _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LinkTarget::Internal>(m, "LinkTargetInternal")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LinkTarget::Internal {
                        org::sem::LinkTarget::Internal result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &org::sem::LinkTarget::Internal::target)
    .def("operator==",
         static_cast<bool(org::sem::LinkTarget::Internal::*)(org::sem::LinkTarget::Internal const&) const>(&org::sem::LinkTarget::Internal::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Internal _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Internal _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LinkTarget::Footnote>(m, "LinkTargetFootnote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LinkTarget::Footnote {
                        org::sem::LinkTarget::Footnote result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &org::sem::LinkTarget::Footnote::target)
    .def("operator==",
         static_cast<bool(org::sem::LinkTarget::Footnote::*)(org::sem::LinkTarget::Footnote const&) const>(&org::sem::LinkTarget::Footnote::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Footnote _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Footnote _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LinkTarget::File>(m, "LinkTargetFile")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LinkTarget::File {
                        org::sem::LinkTarget::File result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("file", &org::sem::LinkTarget::File::file)
    .def("operator==",
         static_cast<bool(org::sem::LinkTarget::File::*)(org::sem::LinkTarget::File const&) const>(&org::sem::LinkTarget::File::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::File _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::File _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::LinkTarget::Attachment>(m, "LinkTargetAttachment")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LinkTarget::Attachment {
                        org::sem::LinkTarget::Attachment result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("file", &org::sem::LinkTarget::Attachment::file)
    .def("operator==",
         static_cast<bool(org::sem::LinkTarget::Attachment::*)(org::sem::LinkTarget::Attachment const&) const>(&org::sem::LinkTarget::Attachment::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Attachment _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Attachment _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::LinkTarget::Kind>(m, "LinkTargetKind", type_registry_guard);
  pybind11::enum_<org::sem::LinkTarget::Kind>(m, "LinkTargetKind")
    .value("Raw", org::sem::LinkTarget::Kind::Raw)
    .value("Id", org::sem::LinkTarget::Kind::Id)
    .value("CustomId", org::sem::LinkTarget::Kind::CustomId)
    .value("SubtreeTitle", org::sem::LinkTarget::Kind::SubtreeTitle)
    .value("Person", org::sem::LinkTarget::Kind::Person)
    .value("UserProtocol", org::sem::LinkTarget::Kind::UserProtocol)
    .value("Internal", org::sem::LinkTarget::Kind::Internal)
    .value("Footnote", org::sem::LinkTarget::Kind::Footnote)
    .value("File", org::sem::LinkTarget::Kind::File)
    .value("Attachment", org::sem::LinkTarget::Kind::Attachment)
    .def("__iter__", [](org::sem::LinkTarget::Kind _self) -> org::bind::python::PyEnumIterator<org::sem::LinkTarget::Kind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::LinkTarget::Kind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::LinkTarget>(m, "LinkTarget")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::LinkTarget {
                        org::sem::LinkTarget result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &org::sem::LinkTarget::data)
    .def("operator==",
         static_cast<bool(org::sem::LinkTarget::*)(org::sem::LinkTarget const&) const>(&org::sem::LinkTarget::operator==),
         pybind11::arg("other"))
    .def("isRaw", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isRaw))
    .def("getRaw", static_cast<org::sem::LinkTarget::Raw&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getRaw))
    .def("isId", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isId))
    .def("getId", static_cast<org::sem::LinkTarget::Id&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getId))
    .def("isCustomId", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isCustomId))
    .def("getCustomId", static_cast<org::sem::LinkTarget::CustomId&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getCustomId))
    .def("isSubtreeTitle", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isSubtreeTitle))
    .def("getSubtreeTitle", static_cast<org::sem::LinkTarget::SubtreeTitle&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getSubtreeTitle))
    .def("isPerson", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isPerson))
    .def("getPerson", static_cast<org::sem::LinkTarget::Person&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getPerson))
    .def("isUserProtocol", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isUserProtocol))
    .def("getUserProtocol", static_cast<org::sem::LinkTarget::UserProtocol&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getUserProtocol))
    .def("isInternal", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isInternal))
    .def("getInternal", static_cast<org::sem::LinkTarget::Internal&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getInternal))
    .def("isFootnote", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isFootnote))
    .def("getFootnote", static_cast<org::sem::LinkTarget::Footnote&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getFootnote))
    .def("isFile", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isFile))
    .def("getFile", static_cast<org::sem::LinkTarget::File&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getFile))
    .def("isAttachment", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isAttachment))
    .def("getAttachment", static_cast<org::sem::LinkTarget::Attachment&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getAttachment))
    .def_static("getKindStatic",
                static_cast<org::sem::LinkTarget::Kind(*)(org::sem::LinkTarget::Data const&)>(&org::sem::LinkTarget::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<org::sem::LinkTarget::Kind(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::LinkTarget::Data const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::LinkTarget::Kind(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::sub_variant_get_kind))
    .def("__repr__", [](org::sem::LinkTarget _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::SubtreeLogHead::Priority::Action>(m, "SubtreeLogHeadPriorityAction", type_registry_guard);
  pybind11::enum_<org::sem::SubtreeLogHead::Priority::Action>(m, "SubtreeLogHeadPriorityAction")
    .value("Added", org::sem::SubtreeLogHead::Priority::Action::Added, R"RAW(`Priority B added on [timestamp]`)RAW")
    .value("Removed", org::sem::SubtreeLogHead::Priority::Action::Removed, R"RAW(`Priority C removed on [timestamp]`)RAW")
    .value("Changed", org::sem::SubtreeLogHead::Priority::Action::Changed, R"RAW(`Priority B changed from C on [timestamp]`)RAW")
    .def("__iter__", [](org::sem::SubtreeLogHead::Priority::Action _self) -> org::bind::python::PyEnumIterator<org::sem::SubtreeLogHead::Priority::Action> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::SubtreeLogHead::Priority::Action>
                     ();
                     })
    ;
  pybind11::class_<org::sem::SubtreeLogHead::Priority>(m, "SubtreeLogHeadPriority")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::SubtreeLogHead::Priority {
                        org::sem::SubtreeLogHead::Priority result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("oldPriority", &org::sem::SubtreeLogHead::Priority::oldPriority, R"RAW(Previous priority for change and removal)RAW")
    .def_readwrite("newPriority", &org::sem::SubtreeLogHead::Priority::newPriority, R"RAW(New priority for change and addition)RAW")
    .def_readwrite("on", &org::sem::SubtreeLogHead::Priority::on, R"RAW(When priority was changed)RAW")
    .def_readwrite("action", &org::sem::SubtreeLogHead::Priority::action, R"RAW(Which action taken)RAW")
    .def("operator==",
         static_cast<bool(org::sem::SubtreeLogHead::Priority::*)(org::sem::SubtreeLogHead::Priority const&) const>(&org::sem::SubtreeLogHead::Priority::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Priority _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Priority _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::SubtreeLogHead::Note>(m, "SubtreeLogHeadNote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::SubtreeLogHead::Note {
                        org::sem::SubtreeLogHead::Note result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("on", &org::sem::SubtreeLogHead::Note::on, R"RAW(Where log was taken)RAW")
    .def("operator==",
         static_cast<bool(org::sem::SubtreeLogHead::Note::*)(org::sem::SubtreeLogHead::Note const&) const>(&org::sem::SubtreeLogHead::Note::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Note _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Note _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::SubtreeLogHead::Refile>(m, "SubtreeLogHeadRefile")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::SubtreeLogHead::Refile {
                        org::sem::SubtreeLogHead::Refile result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("on", &org::sem::SubtreeLogHead::Refile::on, R"RAW(When the refiling happened)RAW")
    .def_readwrite("from_", &org::sem::SubtreeLogHead::Refile::from, R"RAW(Link to the original subtree)RAW")
    .def("operator==",
         static_cast<bool(org::sem::SubtreeLogHead::Refile::*)(org::sem::SubtreeLogHead::Refile const&) const>(&org::sem::SubtreeLogHead::Refile::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Refile _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Refile _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::SubtreeLogHead::Clock>(m, "SubtreeLogHeadClock")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::SubtreeLogHead::Clock {
                        org::sem::SubtreeLogHead::Clock result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("from_", &org::sem::SubtreeLogHead::Clock::from, R"RAW(Clock start time)RAW")
    .def_readwrite("to", &org::sem::SubtreeLogHead::Clock::to, R"RAW(Optional end of the clock)RAW")
    .def("operator==",
         static_cast<bool(org::sem::SubtreeLogHead::Clock::*)(org::sem::SubtreeLogHead::Clock const&) const>(&org::sem::SubtreeLogHead::Clock::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Clock _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Clock _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::SubtreeLogHead::State>(m, "SubtreeLogHeadState")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::SubtreeLogHead::State {
                        org::sem::SubtreeLogHead::State result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("from_", &org::sem::SubtreeLogHead::State::from)
    .def_readwrite("to", &org::sem::SubtreeLogHead::State::to)
    .def_readwrite("on", &org::sem::SubtreeLogHead::State::on)
    .def("operator==",
         static_cast<bool(org::sem::SubtreeLogHead::State::*)(org::sem::SubtreeLogHead::State const&) const>(&org::sem::SubtreeLogHead::State::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::State _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::State _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::SubtreeLogHead::Deadline>(m, "SubtreeLogHeadDeadline")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::SubtreeLogHead::Deadline {
                        org::sem::SubtreeLogHead::Deadline result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("from_", &org::sem::SubtreeLogHead::Deadline::from)
    .def_readwrite("to", &org::sem::SubtreeLogHead::Deadline::to)
    .def_readwrite("on", &org::sem::SubtreeLogHead::Deadline::on)
    .def("operator==",
         static_cast<bool(org::sem::SubtreeLogHead::Deadline::*)(org::sem::SubtreeLogHead::Deadline const&) const>(&org::sem::SubtreeLogHead::Deadline::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Deadline _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Deadline _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::SubtreeLogHead::Schedule>(m, "SubtreeLogHeadSchedule")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::SubtreeLogHead::Schedule {
                        org::sem::SubtreeLogHead::Schedule result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("from_", &org::sem::SubtreeLogHead::Schedule::from)
    .def_readwrite("to", &org::sem::SubtreeLogHead::Schedule::to)
    .def_readwrite("on", &org::sem::SubtreeLogHead::Schedule::on)
    .def("operator==",
         static_cast<bool(org::sem::SubtreeLogHead::Schedule::*)(org::sem::SubtreeLogHead::Schedule const&) const>(&org::sem::SubtreeLogHead::Schedule::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Schedule _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Schedule _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::SubtreeLogHead::Tag>(m, "SubtreeLogHeadTag")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::SubtreeLogHead::Tag {
                        org::sem::SubtreeLogHead::Tag result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("on", &org::sem::SubtreeLogHead::Tag::on, R"RAW(When the log was assigned)RAW")
    .def_readwrite("tag", &org::sem::SubtreeLogHead::Tag::tag, R"RAW(Tag in question)RAW")
    .def_readwrite("added", &org::sem::SubtreeLogHead::Tag::added, R"RAW(Added/removed?)RAW")
    .def("operator==",
         static_cast<bool(org::sem::SubtreeLogHead::Tag::*)(org::sem::SubtreeLogHead::Tag const&) const>(&org::sem::SubtreeLogHead::Tag::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Tag _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Tag _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::SubtreeLogHead::Unknown>(m, "SubtreeLogHeadUnknown")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::SubtreeLogHead::Unknown {
                        org::sem::SubtreeLogHead::Unknown result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("operator==",
         static_cast<bool(org::sem::SubtreeLogHead::Unknown::*)(org::sem::SubtreeLogHead::Unknown const&) const>(&org::sem::SubtreeLogHead::Unknown::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Unknown _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Unknown _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::SubtreeLogHead::Kind>(m, "SubtreeLogHeadKind", type_registry_guard);
  pybind11::enum_<org::sem::SubtreeLogHead::Kind>(m, "SubtreeLogHeadKind")
    .value("Priority", org::sem::SubtreeLogHead::Kind::Priority)
    .value("Note", org::sem::SubtreeLogHead::Kind::Note)
    .value("Refile", org::sem::SubtreeLogHead::Kind::Refile)
    .value("Clock", org::sem::SubtreeLogHead::Kind::Clock)
    .value("State", org::sem::SubtreeLogHead::Kind::State)
    .value("Deadline", org::sem::SubtreeLogHead::Kind::Deadline)
    .value("Schedule", org::sem::SubtreeLogHead::Kind::Schedule)
    .value("Tag", org::sem::SubtreeLogHead::Kind::Tag)
    .value("Unknown", org::sem::SubtreeLogHead::Kind::Unknown)
    .def("__iter__", [](org::sem::SubtreeLogHead::Kind _self) -> org::bind::python::PyEnumIterator<org::sem::SubtreeLogHead::Kind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::SubtreeLogHead::Kind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::SubtreeLogHead>(m, "SubtreeLogHead")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::SubtreeLogHead {
                        org::sem::SubtreeLogHead result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("log", &org::sem::SubtreeLogHead::log)
    .def("operator==",
         static_cast<bool(org::sem::SubtreeLogHead::*)(org::sem::SubtreeLogHead const&) const>(&org::sem::SubtreeLogHead::operator==),
         pybind11::arg("other"))
    .def("isPriority", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isPriority))
    .def("getPriority", static_cast<org::sem::SubtreeLogHead::Priority&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getPriority))
    .def("isNote", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isNote))
    .def("getNote", static_cast<org::sem::SubtreeLogHead::Note&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getNote))
    .def("isRefile", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isRefile))
    .def("getRefile", static_cast<org::sem::SubtreeLogHead::Refile&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getRefile))
    .def("isClock", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isClock))
    .def("getClock", static_cast<org::sem::SubtreeLogHead::Clock&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getClock))
    .def("isState", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isState))
    .def("getState", static_cast<org::sem::SubtreeLogHead::State&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getState))
    .def("isDeadline", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isDeadline))
    .def("getDeadline", static_cast<org::sem::SubtreeLogHead::Deadline&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getDeadline))
    .def("isSchedule", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isSchedule))
    .def("getSchedule", static_cast<org::sem::SubtreeLogHead::Schedule&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getSchedule))
    .def("isTag", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isTag))
    .def("getTag", static_cast<org::sem::SubtreeLogHead::Tag&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getTag))
    .def("isUnknown", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isUnknown))
    .def("getUnknown", static_cast<org::sem::SubtreeLogHead::Unknown&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getUnknown))
    .def_static("getLogKindStatic",
                static_cast<org::sem::SubtreeLogHead::Kind(*)(org::sem::SubtreeLogHead::LogEntry const&)>(&org::sem::SubtreeLogHead::getLogKind),
                pybind11::arg("__input"))
    .def("getLogKind", static_cast<org::sem::SubtreeLogHead::Kind(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getLogKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::SubtreeLogHead::LogEntry const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::SubtreeLogHead::Kind(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::sub_variant_get_kind))
    .def("__repr__", [](org::sem::SubtreeLogHead _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::SubtreeCompletion>(m, "SubtreeCompletion")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::SubtreeCompletion {
                        org::sem::SubtreeCompletion result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("done", &org::sem::SubtreeCompletion::done, R"RAW(Number of completed tasks)RAW")
    .def_readwrite("full", &org::sem::SubtreeCompletion::full, R"RAW(Full number of tasks)RAW")
    .def_readwrite("isPercent", &org::sem::SubtreeCompletion::isPercent, R"RAW(Use fraction or percent to display completion)RAW")
    .def("operator==",
         static_cast<bool(org::sem::SubtreeCompletion::*)(org::sem::SubtreeCompletion const&) const>(&org::sem::SubtreeCompletion::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::SubtreeCompletion _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeCompletion _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::AttrList>(m, "AttrList")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::AttrList {
                        org::sem::AttrList result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("items", &org::sem::AttrList::items)
    .def("operator==",
         static_cast<bool(org::sem::AttrList::*)(org::sem::AttrList const&) const>(&org::sem::AttrList::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::AttrList _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrList _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::AttrGroup>(m, "AttrGroup")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::AttrGroup {
                        org::sem::AttrGroup result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("positional", &org::sem::AttrGroup::positional, R"RAW(Positional arguments with no keys)RAW")
    .def_readwrite("named", &org::sem::AttrGroup::named, R"RAW(Stored key-value mapping)RAW")
    .def("getFlatArgs", static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getFlatArgs))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::AttrGroup::getAttrs),
         pybind11::arg_v("key", std::nullopt))
    .def("setNamedAttr",
         static_cast<void(org::sem::AttrGroup::*)(hstd::Str const&, hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setNamedAttr),
         pybind11::arg("key"),
         pybind11::arg("attrs"))
    .def("setPositionalAttr",
         static_cast<void(org::sem::AttrGroup::*)(hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setPositionalAttr),
         pybind11::arg("items"))
    .def("getPositionalSize", static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getPositionalSize))
    .def("getNamedSize", static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getNamedSize))
    .def("isEmpty", static_cast<bool(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::isEmpty))
    .def("getAll", static_cast<org::sem::AttrList(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getAll))
    .def("atPositional",
         static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::atPositional),
         pybind11::arg("index"))
    .def("getPositional",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::getPositional),
         pybind11::arg("index"))
    .def("atNamed",
         static_cast<org::sem::AttrList const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atNamed),
         pybind11::arg("index"))
    .def("getNamed",
         static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getNamed),
         pybind11::arg("index"))
    .def("atFirstNamed",
         static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstNamed),
         pybind11::arg("index"))
    .def("getFirstNamed",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstNamed),
         pybind11::arg("index"))
    .def("atVarNamed",
         static_cast<org::sem::AttrList(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atVarNamed),
         pybind11::arg("index"))
    .def("getVarNamed",
         static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getVarNamed),
         pybind11::arg("index"))
    .def("atFirstVarNamed",
         static_cast<org::sem::AttrValue(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstVarNamed),
         pybind11::arg("index"))
    .def("getFirstVarNamed",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstVarNamed),
         pybind11::arg("index"))
    .def("operator==",
         static_cast<bool(org::sem::AttrGroup::*)(org::sem::AttrGroup const&) const>(&org::sem::AttrGroup::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::AttrGroup _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrGroup _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::OrgCodeEvalInput::Var>(m, "OrgCodeEvalInputVar")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::OrgCodeEvalInput::Var {
                        org::sem::OrgCodeEvalInput::Var result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::OrgCodeEvalInput::Var::name)
    .def_readwrite("value", &org::sem::OrgCodeEvalInput::Var::value)
    .def("operator==",
         static_cast<bool(org::sem::OrgCodeEvalInput::Var::*)(org::sem::OrgCodeEvalInput::Var const&) const>(&org::sem::OrgCodeEvalInput::Var::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::OrgCodeEvalInput::Var _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgCodeEvalInput::Var _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::OrgCodeEvalInput::ResultType>(m, "OrgCodeEvalInputResultType", type_registry_guard);
  pybind11::enum_<org::sem::OrgCodeEvalInput::ResultType>(m, "OrgCodeEvalInputResultType")
    .value("None", org::sem::OrgCodeEvalInput::ResultType::None)
    .value("Table", org::sem::OrgCodeEvalInput::ResultType::Table, R"RAW(Interpret the results as an Org table. If the result is a single value, create a table with one row and one column.)RAW")
    .value("List", org::sem::OrgCodeEvalInput::ResultType::List, R"RAW(Interpret the results as an Org list. If the result is a single value, create a list of one element.)RAW")
    .value("Scalar", org::sem::OrgCodeEvalInput::ResultType::Scalar, R"RAW(Interpret literally and insert as quoted text. Do not create a table.)RAW")
    .value("SaveFile", org::sem::OrgCodeEvalInput::ResultType::SaveFile, R"RAW(Interpret as a filename. Save the results of execution of the code block to that file, then insert a link to it.)RAW")
    .def("__iter__", [](org::sem::OrgCodeEvalInput::ResultType _self) -> org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultType> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultType>
                     ();
                     })
    ;
  bind_enum_iterator<org::sem::OrgCodeEvalInput::ResultFormat>(m, "OrgCodeEvalInputResultFormat", type_registry_guard);
  pybind11::enum_<org::sem::OrgCodeEvalInput::ResultFormat>(m, "OrgCodeEvalInputResultFormat")
    .value("None", org::sem::OrgCodeEvalInput::ResultFormat::None)
    .value("Raw", org::sem::OrgCodeEvalInput::ResultFormat::Raw, R"RAW(Interpreted as raw Org mode. Inserted directly into the buffer.)RAW")
    .value("Code", org::sem::OrgCodeEvalInput::ResultFormat::Code, R"RAW(Result enclosed in a code block.)RAW")
    .value("Drawer", org::sem::OrgCodeEvalInput::ResultFormat::Drawer, R"RAW(Results are added directly to the Org file as with ‘raw’, but are wrapped in a ‘RESULTS’ drawer or results macro (for inline code blocks), for later scripting and automated processing.)RAW")
    .value("ExportType", org::sem::OrgCodeEvalInput::ResultFormat::ExportType, R"RAW(Results enclosed in a ‘BEGIN_EXPORT’ block.)RAW")
    .value("Link", org::sem::OrgCodeEvalInput::ResultFormat::Link)
    .def("__iter__", [](org::sem::OrgCodeEvalInput::ResultFormat _self) -> org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultFormat> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultFormat>
                     ();
                     })
    ;
  bind_enum_iterator<org::sem::OrgCodeEvalInput::ResultHandling>(m, "OrgCodeEvalInputResultHandling", type_registry_guard);
  pybind11::enum_<org::sem::OrgCodeEvalInput::ResultHandling>(m, "OrgCodeEvalInputResultHandling")
    .value("None", org::sem::OrgCodeEvalInput::ResultHandling::None)
    .value("Replace", org::sem::OrgCodeEvalInput::ResultHandling::Replace)
    .value("Silent", org::sem::OrgCodeEvalInput::ResultHandling::Silent)
    .value("Discard", org::sem::OrgCodeEvalInput::ResultHandling::Discard)
    .value("Append", org::sem::OrgCodeEvalInput::ResultHandling::Append)
    .value("Prepend", org::sem::OrgCodeEvalInput::ResultHandling::Prepend)
    .def("__iter__", [](org::sem::OrgCodeEvalInput::ResultHandling _self) -> org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultHandling> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultHandling>
                     ();
                     })
    ;
  pybind11::class_<org::sem::OrgCodeEvalInput>(m, "OrgCodeEvalInput")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::OrgCodeEvalInput {
                        org::sem::OrgCodeEvalInput result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("blockAttrs", &org::sem::OrgCodeEvalInput::blockAttrs)
    .def_readwrite("tangledCode", &org::sem::OrgCodeEvalInput::tangledCode)
    .def_readwrite("exportType", &org::sem::OrgCodeEvalInput::exportType)
    .def_readwrite("resultType", &org::sem::OrgCodeEvalInput::resultType)
    .def_readwrite("resultFormat", &org::sem::OrgCodeEvalInput::resultFormat)
    .def_readwrite("resultHandling", &org::sem::OrgCodeEvalInput::resultHandling)
    .def_readwrite("language", &org::sem::OrgCodeEvalInput::language)
    .def_readwrite("argList", &org::sem::OrgCodeEvalInput::argList)
    .def("operator==",
         static_cast<bool(org::sem::OrgCodeEvalInput::*)(org::sem::OrgCodeEvalInput const&) const>(&org::sem::OrgCodeEvalInput::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::OrgCodeEvalInput _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgCodeEvalInput _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::OrgCodeEvalOutput>(m, "OrgCodeEvalOutput")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::OrgCodeEvalOutput {
                        org::sem::OrgCodeEvalOutput result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("stdout", &org::sem::OrgCodeEvalOutput::stdout)
    .def_readwrite("stderr", &org::sem::OrgCodeEvalOutput::stderr)
    .def_readwrite("code", &org::sem::OrgCodeEvalOutput::code)
    .def_readwrite("cmd", &org::sem::OrgCodeEvalOutput::cmd, R"RAW(Command evaluated, if none then eval output did not run CLI subprocess)RAW")
    .def_readwrite("args", &org::sem::OrgCodeEvalOutput::args, R"RAW(Command line arguments provided for execution)RAW")
    .def_readwrite("cwd", &org::sem::OrgCodeEvalOutput::cwd, R"RAW(Working directory where command was executed)RAW")
    .def_readwrite("appliedHeaderArg", &org::sem::OrgCodeEvalOutput::appliedHeaderArg, R"RAW(Final set of header arguments applied during evaluation)RAW")
    .def("operator==",
         static_cast<bool(org::sem::OrgCodeEvalOutput::*)(org::sem::OrgCodeEvalOutput const&) const>(&org::sem::OrgCodeEvalOutput::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::OrgCodeEvalOutput _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgCodeEvalOutput _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::ColumnView::Summary::CheckboxAggregate::Kind>(m, "ColumnViewSummaryCheckboxAggregateKind", type_registry_guard);
  pybind11::enum_<org::sem::ColumnView::Summary::CheckboxAggregate::Kind>(m, "ColumnViewSummaryCheckboxAggregateKind")
    .value("IfAllNested", org::sem::ColumnView::Summary::CheckboxAggregate::Kind::IfAllNested)
    .value("AggregateFractionRec", org::sem::ColumnView::Summary::CheckboxAggregate::Kind::AggregateFractionRec)
    .value("AggregatePercentRec", org::sem::ColumnView::Summary::CheckboxAggregate::Kind::AggregatePercentRec)
    .def("__iter__", [](org::sem::ColumnView::Summary::CheckboxAggregate::Kind _self) -> org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::CheckboxAggregate::Kind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::CheckboxAggregate::Kind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::ColumnView::Summary::CheckboxAggregate>(m, "ColumnViewSummaryCheckboxAggregate")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::ColumnView::Summary::CheckboxAggregate {
                        org::sem::ColumnView::Summary::CheckboxAggregate result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("kind", &org::sem::ColumnView::Summary::CheckboxAggregate::kind)
    .def("operator==",
         static_cast<bool(org::sem::ColumnView::Summary::CheckboxAggregate::*)(org::sem::ColumnView::Summary::CheckboxAggregate const&) const>(&org::sem::ColumnView::Summary::CheckboxAggregate::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::ColumnView::Summary::CheckboxAggregate _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColumnView::Summary::CheckboxAggregate _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::ColumnView::Summary::MathAggregate::Kind>(m, "ColumnViewSummaryMathAggregateKind", type_registry_guard);
  pybind11::enum_<org::sem::ColumnView::Summary::MathAggregate::Kind>(m, "ColumnViewSummaryMathAggregateKind")
    .value("Min", org::sem::ColumnView::Summary::MathAggregate::Kind::Min)
    .value("Max", org::sem::ColumnView::Summary::MathAggregate::Kind::Max)
    .value("Mean", org::sem::ColumnView::Summary::MathAggregate::Kind::Mean)
    .value("Sum", org::sem::ColumnView::Summary::MathAggregate::Kind::Sum)
    .value("LowHighEst", org::sem::ColumnView::Summary::MathAggregate::Kind::LowHighEst)
    .def("__iter__", [](org::sem::ColumnView::Summary::MathAggregate::Kind _self) -> org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::MathAggregate::Kind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::MathAggregate::Kind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::ColumnView::Summary::MathAggregate>(m, "ColumnViewSummaryMathAggregate")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::ColumnView::Summary::MathAggregate {
                        org::sem::ColumnView::Summary::MathAggregate result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("kind", &org::sem::ColumnView::Summary::MathAggregate::kind)
    .def_readwrite("formatDigits", &org::sem::ColumnView::Summary::MathAggregate::formatDigits)
    .def_readwrite("formatPrecision", &org::sem::ColumnView::Summary::MathAggregate::formatPrecision)
    .def("operator==",
         static_cast<bool(org::sem::ColumnView::Summary::MathAggregate::*)(org::sem::ColumnView::Summary::MathAggregate const&) const>(&org::sem::ColumnView::Summary::MathAggregate::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::ColumnView::Summary::MathAggregate _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColumnView::Summary::MathAggregate _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::ColumnView::Summary::Kind>(m, "ColumnViewSummaryKind", type_registry_guard);
  pybind11::enum_<org::sem::ColumnView::Summary::Kind>(m, "ColumnViewSummaryKind")
    .value("CheckboxAggregate", org::sem::ColumnView::Summary::Kind::CheckboxAggregate)
    .value("MathAggregate", org::sem::ColumnView::Summary::Kind::MathAggregate)
    .def("__iter__", [](org::sem::ColumnView::Summary::Kind _self) -> org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::Kind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::Kind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::ColumnView::Summary>(m, "ColumnViewSummary")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::ColumnView::Summary {
                        org::sem::ColumnView::Summary result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &org::sem::ColumnView::Summary::data)
    .def("operator==",
         static_cast<bool(org::sem::ColumnView::Summary::*)(org::sem::ColumnView::Summary const&) const>(&org::sem::ColumnView::Summary::operator==),
         pybind11::arg("other"))
    .def("isCheckboxAggregate", static_cast<bool(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::isCheckboxAggregate))
    .def("getCheckboxAggregate", static_cast<org::sem::ColumnView::Summary::CheckboxAggregate&(org::sem::ColumnView::Summary::*)()>(&org::sem::ColumnView::Summary::getCheckboxAggregate))
    .def("isMathAggregate", static_cast<bool(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::isMathAggregate))
    .def("getMathAggregate", static_cast<org::sem::ColumnView::Summary::MathAggregate&(org::sem::ColumnView::Summary::*)()>(&org::sem::ColumnView::Summary::getMathAggregate))
    .def_static("getKindStatic",
                static_cast<org::sem::ColumnView::Summary::Kind(*)(org::sem::ColumnView::Summary::Data const&)>(&org::sem::ColumnView::Summary::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<org::sem::ColumnView::Summary::Kind(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::ColumnView::Summary::Data const&(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::ColumnView::Summary::Kind(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::sub_variant_get_kind))
    .def("__repr__", [](org::sem::ColumnView::Summary _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColumnView::Summary _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::ColumnView::Column>(m, "ColumnViewColumn")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::ColumnView::Column {
                        org::sem::ColumnView::Column result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("summary", &org::sem::ColumnView::Column::summary)
    .def_readwrite("width", &org::sem::ColumnView::Column::width)
    .def_readwrite("property", &org::sem::ColumnView::Column::property)
    .def_readwrite("propertyTitle", &org::sem::ColumnView::Column::propertyTitle)
    .def("operator==",
         static_cast<bool(org::sem::ColumnView::Column::*)(org::sem::ColumnView::Column const&) const>(&org::sem::ColumnView::Column::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::ColumnView::Column _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColumnView::Column _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::ColumnView>(m, "ColumnView")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::ColumnView {
                        org::sem::ColumnView result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("columns", &org::sem::ColumnView::columns)
    .def("operator==",
         static_cast<bool(org::sem::ColumnView::*)(org::sem::ColumnView const&) const>(&org::sem::ColumnView::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::ColumnView _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColumnView _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::BlockCodeLine::Part::Raw>(m, "BlockCodeLinePartRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::BlockCodeLine::Part::Raw {
                        org::sem::BlockCodeLine::Part::Raw result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("code", &org::sem::BlockCodeLine::Part::Raw::code)
    .def("operator==",
         static_cast<bool(org::sem::BlockCodeLine::Part::Raw::*)(org::sem::BlockCodeLine::Part::Raw const&) const>(&org::sem::BlockCodeLine::Part::Raw::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::BlockCodeLine::Part::Raw _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeLine::Part::Raw _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::BlockCodeLine::Part::Callout>(m, "BlockCodeLinePartCallout")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::BlockCodeLine::Part::Callout {
                        org::sem::BlockCodeLine::Part::Callout result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::BlockCodeLine::Part::Callout::name)
    .def("operator==",
         static_cast<bool(org::sem::BlockCodeLine::Part::Callout::*)(org::sem::BlockCodeLine::Part::Callout const&) const>(&org::sem::BlockCodeLine::Part::Callout::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::BlockCodeLine::Part::Callout _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeLine::Part::Callout _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::BlockCodeLine::Part::Tangle>(m, "BlockCodeLinePartTangle")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::BlockCodeLine::Part::Tangle {
                        org::sem::BlockCodeLine::Part::Tangle result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &org::sem::BlockCodeLine::Part::Tangle::target)
    .def("operator==",
         static_cast<bool(org::sem::BlockCodeLine::Part::Tangle::*)(org::sem::BlockCodeLine::Part::Tangle const&) const>(&org::sem::BlockCodeLine::Part::Tangle::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::BlockCodeLine::Part::Tangle _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeLine::Part::Tangle _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::BlockCodeLine::Part::Kind>(m, "BlockCodeLinePartKind", type_registry_guard);
  pybind11::enum_<org::sem::BlockCodeLine::Part::Kind>(m, "BlockCodeLinePartKind")
    .value("Raw", org::sem::BlockCodeLine::Part::Kind::Raw)
    .value("Callout", org::sem::BlockCodeLine::Part::Kind::Callout)
    .value("Tangle", org::sem::BlockCodeLine::Part::Kind::Tangle)
    .def("__iter__", [](org::sem::BlockCodeLine::Part::Kind _self) -> org::bind::python::PyEnumIterator<org::sem::BlockCodeLine::Part::Kind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::BlockCodeLine::Part::Kind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::BlockCodeLine::Part>(m, "BlockCodeLinePart")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::BlockCodeLine::Part {
                        org::sem::BlockCodeLine::Part result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &org::sem::BlockCodeLine::Part::data)
    .def("operator==",
         static_cast<bool(org::sem::BlockCodeLine::Part::*)(org::sem::BlockCodeLine::Part const&) const>(&org::sem::BlockCodeLine::Part::operator==),
         pybind11::arg("other"))
    .def("isRaw", static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isRaw))
    .def("getRaw", static_cast<org::sem::BlockCodeLine::Part::Raw&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getRaw))
    .def("isCallout", static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isCallout))
    .def("getCallout", static_cast<org::sem::BlockCodeLine::Part::Callout&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getCallout))
    .def("isTangle", static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isTangle))
    .def("getTangle", static_cast<org::sem::BlockCodeLine::Part::Tangle&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getTangle))
    .def_static("getKindStatic",
                static_cast<org::sem::BlockCodeLine::Part::Kind(*)(org::sem::BlockCodeLine::Part::Data const&)>(&org::sem::BlockCodeLine::Part::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<org::sem::BlockCodeLine::Part::Kind(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::BlockCodeLine::Part::Data const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::BlockCodeLine::Part::Kind(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::sub_variant_get_kind))
    .def("__repr__", [](org::sem::BlockCodeLine::Part _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeLine::Part _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::BlockCodeLine>(m, "BlockCodeLine")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::BlockCodeLine {
                        org::sem::BlockCodeLine result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("parts", &org::sem::BlockCodeLine::parts, R"RAW(parts of the single line)RAW")
    .def("operator==",
         static_cast<bool(org::sem::BlockCodeLine::*)(org::sem::BlockCodeLine const&) const>(&org::sem::BlockCodeLine::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::BlockCodeLine _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeLine _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::DocumentExportConfig::TaskExport>(m, "DocumentExportConfigTaskExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::DocumentExportConfig::TaskExport {
                        org::sem::DocumentExportConfig::TaskExport result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("taskWhitelist", &org::sem::DocumentExportConfig::TaskExport::taskWhitelist)
    .def("operator==",
         static_cast<bool(org::sem::DocumentExportConfig::TaskExport::*)(org::sem::DocumentExportConfig::TaskExport const&) const>(&org::sem::DocumentExportConfig::TaskExport::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::DocumentExportConfig::TaskExport _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentExportConfig::TaskExport _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::DocumentExportConfig::TagExport>(m, "DocumentExportConfigTagExport", type_registry_guard);
  pybind11::enum_<org::sem::DocumentExportConfig::TagExport>(m, "DocumentExportConfigTagExport")
    .value("None", org::sem::DocumentExportConfig::TagExport::None)
    .value("All", org::sem::DocumentExportConfig::TagExport::All)
    .value("NotInToc", org::sem::DocumentExportConfig::TagExport::NotInToc, R"RAW(Expot tags in subtree titles but not in the table of content)RAW")
    .def("__iter__", [](org::sem::DocumentExportConfig::TagExport _self) -> org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TagExport> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TagExport>
                     ();
                     })
    ;
  bind_enum_iterator<org::sem::DocumentExportConfig::TaskFiltering>(m, "DocumentExportConfigTaskFiltering", type_registry_guard);
  pybind11::enum_<org::sem::DocumentExportConfig::TaskFiltering>(m, "DocumentExportConfigTaskFiltering")
    .value("Whitelist", org::sem::DocumentExportConfig::TaskFiltering::Whitelist, R"RAW(Include tasks from the whitelist)RAW")
    .value("Done", org::sem::DocumentExportConfig::TaskFiltering::Done, R"RAW(Include tasks marked as done)RAW")
    .value("None", org::sem::DocumentExportConfig::TaskFiltering::None, R"RAW(Exclude all task subtrees from export)RAW")
    .value("All", org::sem::DocumentExportConfig::TaskFiltering::All, R"RAW(Add all task subtrees to export)RAW")
    .def("__iter__", [](org::sem::DocumentExportConfig::TaskFiltering _self) -> org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TaskFiltering> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TaskFiltering>
                     ();
                     })
    ;
  bind_enum_iterator<org::sem::DocumentExportConfig::BrokenLinks>(m, "DocumentExportConfigBrokenLinks", type_registry_guard);
  pybind11::enum_<org::sem::DocumentExportConfig::BrokenLinks>(m, "DocumentExportConfigBrokenLinks")
    .value("Mark", org::sem::DocumentExportConfig::BrokenLinks::Mark)
    .value("Raise", org::sem::DocumentExportConfig::BrokenLinks::Raise)
    .value("Ignore", org::sem::DocumentExportConfig::BrokenLinks::Ignore)
    .def("__iter__", [](org::sem::DocumentExportConfig::BrokenLinks _self) -> org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::BrokenLinks> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::BrokenLinks>
                     ();
                     })
    ;
  pybind11::class_<org::sem::DocumentExportConfig::DoExport>(m, "DocumentExportConfigDoExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::DocumentExportConfig::DoExport {
                        org::sem::DocumentExportConfig::DoExport result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("exportToc", &org::sem::DocumentExportConfig::DoExport::exportToc)
    .def("operator==",
         static_cast<bool(org::sem::DocumentExportConfig::DoExport::*)(org::sem::DocumentExportConfig::DoExport const&) const>(&org::sem::DocumentExportConfig::DoExport::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::DocumentExportConfig::DoExport _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentExportConfig::DoExport _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::DocumentExportConfig::ExportFixed>(m, "DocumentExportConfigExportFixed")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::DocumentExportConfig::ExportFixed {
                        org::sem::DocumentExportConfig::ExportFixed result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("exportLevels", &org::sem::DocumentExportConfig::ExportFixed::exportLevels)
    .def("operator==",
         static_cast<bool(org::sem::DocumentExportConfig::ExportFixed::*)(org::sem::DocumentExportConfig::ExportFixed const&) const>(&org::sem::DocumentExportConfig::ExportFixed::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::DocumentExportConfig::ExportFixed _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentExportConfig::ExportFixed _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::DocumentExportConfig::TocExportKind>(m, "DocumentExportConfigTocExportKind", type_registry_guard);
  pybind11::enum_<org::sem::DocumentExportConfig::TocExportKind>(m, "DocumentExportConfigTocExportKind")
    .value("DoExport", org::sem::DocumentExportConfig::TocExportKind::DoExport)
    .value("ExportFixed", org::sem::DocumentExportConfig::TocExportKind::ExportFixed)
    .def("__iter__", [](org::sem::DocumentExportConfig::TocExportKind _self) -> org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TocExportKind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TocExportKind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::DocumentExportConfig>(m, "DocumentExportConfig")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::DocumentExportConfig {
                        org::sem::DocumentExportConfig result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("inlinetasks", &org::sem::DocumentExportConfig::inlinetasks)
    .def_readwrite("footnotes", &org::sem::DocumentExportConfig::footnotes)
    .def_readwrite("clock", &org::sem::DocumentExportConfig::clock)
    .def_readwrite("author", &org::sem::DocumentExportConfig::author)
    .def_readwrite("emphasis", &org::sem::DocumentExportConfig::emphasis)
    .def_readwrite("specialStrings", &org::sem::DocumentExportConfig::specialStrings)
    .def_readwrite("propertyDrawers", &org::sem::DocumentExportConfig::propertyDrawers)
    .def_readwrite("statisticsCookies", &org::sem::DocumentExportConfig::statisticsCookies)
    .def_readwrite("todoText", &org::sem::DocumentExportConfig::todoText, R"RAW(Include todo keywords in export)RAW")
    .def_readwrite("brokenLinks", &org::sem::DocumentExportConfig::brokenLinks)
    .def_readwrite("tocExport", &org::sem::DocumentExportConfig::tocExport)
    .def_readwrite("tagExport", &org::sem::DocumentExportConfig::tagExport)
    .def_readwrite("data", &org::sem::DocumentExportConfig::data)
    .def("operator==",
         static_cast<bool(org::sem::DocumentExportConfig::*)(org::sem::DocumentExportConfig const&) const>(&org::sem::DocumentExportConfig::operator==),
         pybind11::arg("other"))
    .def("isDoExport", static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isDoExport))
    .def("getDoExport", static_cast<org::sem::DocumentExportConfig::DoExport&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getDoExport))
    .def("isExportFixed", static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isExportFixed))
    .def("getExportFixed", static_cast<org::sem::DocumentExportConfig::ExportFixed&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getExportFixed))
    .def_static("getTocExportKindStatic",
                static_cast<org::sem::DocumentExportConfig::TocExportKind(*)(org::sem::DocumentExportConfig::TocExport const&)>(&org::sem::DocumentExportConfig::getTocExportKind),
                pybind11::arg("__input"))
    .def("getTocExportKind", static_cast<org::sem::DocumentExportConfig::TocExportKind(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getTocExportKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::DocumentExportConfig::TocExport const&(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::DocumentExportConfig::TocExportKind(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::sub_variant_get_kind))
    .def("__repr__", [](org::sem::DocumentExportConfig _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentExportConfig _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::SubtreePeriod::Kind>(m, "SubtreePeriodKind", type_registry_guard);
  pybind11::enum_<org::sem::SubtreePeriod::Kind>(m, "SubtreePeriodKind")
    .value("Clocked", org::sem::SubtreePeriod::Kind::Clocked, R"RAW(Time period of the task execution.)RAW")
    .value("Closed", org::sem::SubtreePeriod::Kind::Closed, R"RAW(Task marked as closed)RAW")
    .value("Scheduled", org::sem::SubtreePeriod::Kind::Scheduled, R"RAW(Date of task execution start plus it's estimated effort duration. If the latter one is missing then only a single time point is returned)RAW")
    .value("Titled", org::sem::SubtreePeriod::Kind::Titled, R"RAW(Single point or time range used in title. Single point can also be a simple time, such as `12:20`)RAW")
    .value("Deadline", org::sem::SubtreePeriod::Kind::Deadline, R"RAW(Date of task completion. Must be a single time point)RAW")
    .value("Created", org::sem::SubtreePeriod::Kind::Created, R"RAW(When the subtree was created)RAW")
    .value("Repeated", org::sem::SubtreePeriod::Kind::Repeated, R"RAW(Last repeat time of the recurring tasks)RAW")
    .def("__iter__", [](org::sem::SubtreePeriod::Kind _self) -> org::bind::python::PyEnumIterator<org::sem::SubtreePeriod::Kind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::SubtreePeriod::Kind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::SubtreePeriod>(m, "SubtreePeriod")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::SubtreePeriod {
                        org::sem::SubtreePeriod result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("kind", &org::sem::SubtreePeriod::kind, R"RAW(Time period kind -- not associated with point/range distinction)RAW")
    .def_readwrite("from_", &org::sem::SubtreePeriod::from, R"RAW(Clock start time)RAW")
    .def_readwrite("to", &org::sem::SubtreePeriod::to, R"RAW(Optional end of the clock)RAW")
    .def("operator==",
         static_cast<bool(org::sem::SubtreePeriod::*)(org::sem::SubtreePeriod const&) const>(&org::sem::SubtreePeriod::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::SubtreePeriod _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreePeriod _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::Nonblocking>(m, "NamedPropertyNonblocking")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::Nonblocking {
                        org::sem::NamedProperty::Nonblocking result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isBlocking", &org::sem::NamedProperty::Nonblocking::isBlocking)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::Nonblocking::*)(org::sem::NamedProperty::Nonblocking const&) const>(&org::sem::NamedProperty::Nonblocking::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Nonblocking _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Nonblocking _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::ArchiveTime>(m, "NamedPropertyArchiveTime")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::ArchiveTime {
                        org::sem::NamedProperty::ArchiveTime result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("time", &org::sem::NamedProperty::ArchiveTime::time)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::ArchiveTime::*)(org::sem::NamedProperty::ArchiveTime const&) const>(&org::sem::NamedProperty::ArchiveTime::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveTime _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveTime _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::ArchiveFile>(m, "NamedPropertyArchiveFile")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::ArchiveFile {
                        org::sem::NamedProperty::ArchiveFile result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("file", &org::sem::NamedProperty::ArchiveFile::file)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::ArchiveFile::*)(org::sem::NamedProperty::ArchiveFile const&) const>(&org::sem::NamedProperty::ArchiveFile::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveFile _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveFile _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::ArchiveOlpath>(m, "NamedPropertyArchiveOlpath")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::ArchiveOlpath {
                        org::sem::NamedProperty::ArchiveOlpath result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("path", &org::sem::NamedProperty::ArchiveOlpath::path)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::ArchiveOlpath::*)(org::sem::NamedProperty::ArchiveOlpath const&) const>(&org::sem::NamedProperty::ArchiveOlpath::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveOlpath _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveOlpath _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::ArchiveTarget>(m, "NamedPropertyArchiveTarget")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::ArchiveTarget {
                        org::sem::NamedProperty::ArchiveTarget result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("path", &org::sem::NamedProperty::ArchiveTarget::path)
    .def_readwrite("pattern", &org::sem::NamedProperty::ArchiveTarget::pattern)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::ArchiveTarget::*)(org::sem::NamedProperty::ArchiveTarget const&) const>(&org::sem::NamedProperty::ArchiveTarget::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveTarget _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveTarget _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::ArchiveCategory>(m, "NamedPropertyArchiveCategory")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::ArchiveCategory {
                        org::sem::NamedProperty::ArchiveCategory result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("category", &org::sem::NamedProperty::ArchiveCategory::category)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::ArchiveCategory::*)(org::sem::NamedProperty::ArchiveCategory const&) const>(&org::sem::NamedProperty::ArchiveCategory::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveCategory _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveCategory _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::ArchiveTodo>(m, "NamedPropertyArchiveTodo")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::ArchiveTodo {
                        org::sem::NamedProperty::ArchiveTodo result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("todo", &org::sem::NamedProperty::ArchiveTodo::todo)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::ArchiveTodo::*)(org::sem::NamedProperty::ArchiveTodo const&) const>(&org::sem::NamedProperty::ArchiveTodo::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveTodo _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveTodo _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::Trigger>(m, "NamedPropertyTrigger")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::Trigger {
                        org::sem::NamedProperty::Trigger result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::Trigger::*)(org::sem::NamedProperty::Trigger const&) const>(&org::sem::NamedProperty::Trigger::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Trigger _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Trigger _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::ExportLatexClass>(m, "NamedPropertyExportLatexClass")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::ExportLatexClass {
                        org::sem::NamedProperty::ExportLatexClass result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("latexClass", &org::sem::NamedProperty::ExportLatexClass::latexClass)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::ExportLatexClass::*)(org::sem::NamedProperty::ExportLatexClass const&) const>(&org::sem::NamedProperty::ExportLatexClass::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ExportLatexClass _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ExportLatexClass _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::NamedProperty::CookieData::TodoSource>(m, "NamedPropertyCookieDataTodoSource", type_registry_guard);
  pybind11::enum_<org::sem::NamedProperty::CookieData::TodoSource>(m, "NamedPropertyCookieDataTodoSource")
    .value("Checkbox", org::sem::NamedProperty::CookieData::TodoSource::Checkbox, R"RAW(Only count checkbox subnodes as a progress completion)RAW")
    .value("Todo", org::sem::NamedProperty::CookieData::TodoSource::Todo, R"RAW(Use subtrees with todo keywords)RAW")
    .value("Both", org::sem::NamedProperty::CookieData::TodoSource::Both, R"RAW(Use both subtrees and todo keywords)RAW")
    .def("__iter__", [](org::sem::NamedProperty::CookieData::TodoSource _self) -> org::bind::python::PyEnumIterator<org::sem::NamedProperty::CookieData::TodoSource> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::NamedProperty::CookieData::TodoSource>
                     ();
                     })
    ;
  pybind11::class_<org::sem::NamedProperty::CookieData>(m, "NamedPropertyCookieData")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::CookieData {
                        org::sem::NamedProperty::CookieData result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isRecursive", &org::sem::NamedProperty::CookieData::isRecursive)
    .def_readwrite("source", &org::sem::NamedProperty::CookieData::source)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::CookieData::*)(org::sem::NamedProperty::CookieData const&) const>(&org::sem::NamedProperty::CookieData::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CookieData _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CookieData _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::ExportLatexClassOptions>(m, "NamedPropertyExportLatexClassOptions")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::ExportLatexClassOptions {
                        org::sem::NamedProperty::ExportLatexClassOptions result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("options", &org::sem::NamedProperty::ExportLatexClassOptions::options)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::ExportLatexClassOptions::*)(org::sem::NamedProperty::ExportLatexClassOptions const&) const>(&org::sem::NamedProperty::ExportLatexClassOptions::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ExportLatexClassOptions _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ExportLatexClassOptions _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::ExportLatexHeader>(m, "NamedPropertyExportLatexHeader")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::ExportLatexHeader {
                        org::sem::NamedProperty::ExportLatexHeader result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("header", &org::sem::NamedProperty::ExportLatexHeader::header)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::ExportLatexHeader::*)(org::sem::NamedProperty::ExportLatexHeader const&) const>(&org::sem::NamedProperty::ExportLatexHeader::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ExportLatexHeader _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ExportLatexHeader _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::ExportLatexCompiler>(m, "NamedPropertyExportLatexCompiler")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::ExportLatexCompiler {
                        org::sem::NamedProperty::ExportLatexCompiler result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("compiler", &org::sem::NamedProperty::ExportLatexCompiler::compiler)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::ExportLatexCompiler::*)(org::sem::NamedProperty::ExportLatexCompiler const&) const>(&org::sem::NamedProperty::ExportLatexCompiler::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ExportLatexCompiler _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ExportLatexCompiler _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::Ordered>(m, "NamedPropertyOrdered")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::Ordered {
                        org::sem::NamedProperty::Ordered result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isOrdered", &org::sem::NamedProperty::Ordered::isOrdered)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::Ordered::*)(org::sem::NamedProperty::Ordered const&) const>(&org::sem::NamedProperty::Ordered::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Ordered _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Ordered _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::Effort>(m, "NamedPropertyEffort")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::Effort {
                        org::sem::NamedProperty::Effort result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("hours", &org::sem::NamedProperty::Effort::hours)
    .def_readwrite("minutes", &org::sem::NamedProperty::Effort::minutes)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::Effort::*)(org::sem::NamedProperty::Effort const&) const>(&org::sem::NamedProperty::Effort::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Effort _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Effort _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::NamedProperty::Visibility::Level>(m, "NamedPropertyVisibilityLevel", type_registry_guard);
  pybind11::enum_<org::sem::NamedProperty::Visibility::Level>(m, "NamedPropertyVisibilityLevel")
    .value("Folded", org::sem::NamedProperty::Visibility::Level::Folded)
    .value("Children", org::sem::NamedProperty::Visibility::Level::Children)
    .value("Content", org::sem::NamedProperty::Visibility::Level::Content)
    .value("All", org::sem::NamedProperty::Visibility::Level::All)
    .def("__iter__", [](org::sem::NamedProperty::Visibility::Level _self) -> org::bind::python::PyEnumIterator<org::sem::NamedProperty::Visibility::Level> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::NamedProperty::Visibility::Level>
                     ();
                     })
    ;
  pybind11::class_<org::sem::NamedProperty::Visibility>(m, "NamedPropertyVisibility")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::Visibility {
                        org::sem::NamedProperty::Visibility result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("level", &org::sem::NamedProperty::Visibility::level)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::Visibility::*)(org::sem::NamedProperty::Visibility const&) const>(&org::sem::NamedProperty::Visibility::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Visibility _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Visibility _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::ExportOptions>(m, "NamedPropertyExportOptions")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::ExportOptions {
                        org::sem::NamedProperty::ExportOptions result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("backend", &org::sem::NamedProperty::ExportOptions::backend)
    .def_readwrite("values", &org::sem::NamedProperty::ExportOptions::values)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::ExportOptions::*)(org::sem::NamedProperty::ExportOptions const&) const>(&org::sem::NamedProperty::ExportOptions::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ExportOptions _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ExportOptions _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::Blocker>(m, "NamedPropertyBlocker")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::Blocker {
                        org::sem::NamedProperty::Blocker result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("blockers", &org::sem::NamedProperty::Blocker::blockers)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::Blocker::*)(org::sem::NamedProperty::Blocker const&) const>(&org::sem::NamedProperty::Blocker::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Blocker _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Blocker _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::Unnumbered>(m, "NamedPropertyUnnumbered")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::Unnumbered {
                        org::sem::NamedProperty::Unnumbered result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::Unnumbered::*)(org::sem::NamedProperty::Unnumbered const&) const>(&org::sem::NamedProperty::Unnumbered::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Unnumbered _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Unnumbered _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::Created>(m, "NamedPropertyCreated")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::Created {
                        org::sem::NamedProperty::Created result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("time", &org::sem::NamedProperty::Created::time)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::Created::*)(org::sem::NamedProperty::Created const&) const>(&org::sem::NamedProperty::Created::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Created _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Created _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::RadioId>(m, "NamedPropertyRadioId")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::RadioId {
                        org::sem::NamedProperty::RadioId result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("words", &org::sem::NamedProperty::RadioId::words)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::RadioId::*)(org::sem::NamedProperty::RadioId const&) const>(&org::sem::NamedProperty::RadioId::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::RadioId _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::RadioId _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::HashtagDef>(m, "NamedPropertyHashtagDef")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::HashtagDef {
                        org::sem::NamedProperty::HashtagDef result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("hashtag", &org::sem::NamedProperty::HashtagDef::hashtag)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::HashtagDef::*)(org::sem::NamedProperty::HashtagDef const&) const>(&org::sem::NamedProperty::HashtagDef::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::HashtagDef _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::HashtagDef _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::CustomArgs>(m, "NamedPropertyCustomArgs")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::CustomArgs {
                        org::sem::NamedProperty::CustomArgs result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::NamedProperty::CustomArgs::name, R"RAW(Original name of the property)RAW")
    .def_readwrite("sub", &org::sem::NamedProperty::CustomArgs::sub, R"RAW(Property target specialization)RAW")
    .def_readwrite("attrs", &org::sem::NamedProperty::CustomArgs::attrs, R"RAW(Property parameters)RAW")
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::CustomArgs::*)(org::sem::NamedProperty::CustomArgs const&) const>(&org::sem::NamedProperty::CustomArgs::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CustomArgs _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CustomArgs _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::CustomRaw>(m, "NamedPropertyCustomRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::CustomRaw {
                        org::sem::NamedProperty::CustomRaw result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::NamedProperty::CustomRaw::name, R"RAW(Original name of the property)RAW")
    .def_readwrite("value", &org::sem::NamedProperty::CustomRaw::value, R"RAW(Property value)RAW")
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::CustomRaw::*)(org::sem::NamedProperty::CustomRaw const&) const>(&org::sem::NamedProperty::CustomRaw::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CustomRaw _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CustomRaw _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::CustomSubtreeJson>(m, "NamedPropertyCustomSubtreeJson")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::CustomSubtreeJson {
                        org::sem::NamedProperty::CustomSubtreeJson result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::NamedProperty::CustomSubtreeJson::name)
    .def_readwrite("value", &org::sem::NamedProperty::CustomSubtreeJson::value)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::CustomSubtreeJson::*)(org::sem::NamedProperty::CustomSubtreeJson const&) const>(&org::sem::NamedProperty::CustomSubtreeJson::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CustomSubtreeJson _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CustomSubtreeJson _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::NamedProperty::CustomSubtreeFlags>(m, "NamedPropertyCustomSubtreeFlags")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty::CustomSubtreeFlags {
                        org::sem::NamedProperty::CustomSubtreeFlags result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::NamedProperty::CustomSubtreeFlags::name)
    .def_readwrite("value", &org::sem::NamedProperty::CustomSubtreeFlags::value)
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::CustomSubtreeFlags::*)(org::sem::NamedProperty::CustomSubtreeFlags const&) const>(&org::sem::NamedProperty::CustomSubtreeFlags::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CustomSubtreeFlags _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CustomSubtreeFlags _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::NamedProperty::Kind>(m, "NamedPropertyKind", type_registry_guard);
  pybind11::enum_<org::sem::NamedProperty::Kind>(m, "NamedPropertyKind")
    .value("Nonblocking", org::sem::NamedProperty::Kind::Nonblocking)
    .value("ArchiveTime", org::sem::NamedProperty::Kind::ArchiveTime)
    .value("ArchiveFile", org::sem::NamedProperty::Kind::ArchiveFile)
    .value("ArchiveOlpath", org::sem::NamedProperty::Kind::ArchiveOlpath)
    .value("ArchiveTarget", org::sem::NamedProperty::Kind::ArchiveTarget)
    .value("ArchiveCategory", org::sem::NamedProperty::Kind::ArchiveCategory)
    .value("ArchiveTodo", org::sem::NamedProperty::Kind::ArchiveTodo)
    .value("Trigger", org::sem::NamedProperty::Kind::Trigger)
    .value("ExportLatexClass", org::sem::NamedProperty::Kind::ExportLatexClass)
    .value("CookieData", org::sem::NamedProperty::Kind::CookieData)
    .value("ExportLatexClassOptions", org::sem::NamedProperty::Kind::ExportLatexClassOptions)
    .value("ExportLatexHeader", org::sem::NamedProperty::Kind::ExportLatexHeader)
    .value("ExportLatexCompiler", org::sem::NamedProperty::Kind::ExportLatexCompiler)
    .value("Ordered", org::sem::NamedProperty::Kind::Ordered)
    .value("Effort", org::sem::NamedProperty::Kind::Effort)
    .value("Visibility", org::sem::NamedProperty::Kind::Visibility)
    .value("ExportOptions", org::sem::NamedProperty::Kind::ExportOptions)
    .value("Blocker", org::sem::NamedProperty::Kind::Blocker)
    .value("Unnumbered", org::sem::NamedProperty::Kind::Unnumbered)
    .value("Created", org::sem::NamedProperty::Kind::Created)
    .value("RadioId", org::sem::NamedProperty::Kind::RadioId)
    .value("HashtagDef", org::sem::NamedProperty::Kind::HashtagDef)
    .value("CustomArgs", org::sem::NamedProperty::Kind::CustomArgs)
    .value("CustomRaw", org::sem::NamedProperty::Kind::CustomRaw)
    .value("CustomSubtreeJson", org::sem::NamedProperty::Kind::CustomSubtreeJson)
    .value("CustomSubtreeFlags", org::sem::NamedProperty::Kind::CustomSubtreeFlags)
    .def("__iter__", [](org::sem::NamedProperty::Kind _self) -> org::bind::python::PyEnumIterator<org::sem::NamedProperty::Kind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::NamedProperty::Kind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::NamedProperty>(m, "NamedProperty")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::NamedProperty {
                        org::sem::NamedProperty result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &org::sem::NamedProperty::data)
    .def("isMatching",
         static_cast<bool(org::sem::NamedProperty::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::NamedProperty::isMatching),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt),
         R"RAW(Check if property matches specified kind and optional subkind. Built-in property checking is also done with this function -- 'created' etc.)RAW")
    .def("getName", static_cast<hstd::Str(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getName), R"RAW(Get non-normalized name of the property (for built-in and user))RAW")
    .def("getSubKind", static_cast<hstd::Opt<hstd::Str>(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getSubKind), R"RAW(Get non-normalized sub-kind for the property.)RAW")
    .def("operator==",
         static_cast<bool(org::sem::NamedProperty::*)(org::sem::NamedProperty const&) const>(&org::sem::NamedProperty::operator==),
         pybind11::arg("other"))
    .def("isNonblocking", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isNonblocking))
    .def("getNonblocking", static_cast<org::sem::NamedProperty::Nonblocking&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getNonblocking))
    .def("isArchiveTime", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTime))
    .def("getArchiveTime", static_cast<org::sem::NamedProperty::ArchiveTime&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTime))
    .def("isArchiveFile", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveFile))
    .def("getArchiveFile", static_cast<org::sem::NamedProperty::ArchiveFile&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveFile))
    .def("isArchiveOlpath", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveOlpath))
    .def("getArchiveOlpath", static_cast<org::sem::NamedProperty::ArchiveOlpath&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveOlpath))
    .def("isArchiveTarget", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTarget))
    .def("getArchiveTarget", static_cast<org::sem::NamedProperty::ArchiveTarget&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTarget))
    .def("isArchiveCategory", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveCategory))
    .def("getArchiveCategory", static_cast<org::sem::NamedProperty::ArchiveCategory&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveCategory))
    .def("isArchiveTodo", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTodo))
    .def("getArchiveTodo", static_cast<org::sem::NamedProperty::ArchiveTodo&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTodo))
    .def("isTrigger", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isTrigger))
    .def("getTrigger", static_cast<org::sem::NamedProperty::Trigger&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getTrigger))
    .def("isExportLatexClass", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexClass))
    .def("getExportLatexClass", static_cast<org::sem::NamedProperty::ExportLatexClass&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexClass))
    .def("isCookieData", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCookieData))
    .def("getCookieData", static_cast<org::sem::NamedProperty::CookieData&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCookieData))
    .def("isExportLatexClassOptions", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexClassOptions))
    .def("getExportLatexClassOptions", static_cast<org::sem::NamedProperty::ExportLatexClassOptions&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexClassOptions))
    .def("isExportLatexHeader", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexHeader))
    .def("getExportLatexHeader", static_cast<org::sem::NamedProperty::ExportLatexHeader&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexHeader))
    .def("isExportLatexCompiler", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexCompiler))
    .def("getExportLatexCompiler", static_cast<org::sem::NamedProperty::ExportLatexCompiler&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexCompiler))
    .def("isOrdered", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isOrdered))
    .def("getOrdered", static_cast<org::sem::NamedProperty::Ordered&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getOrdered))
    .def("isEffort", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isEffort))
    .def("getEffort", static_cast<org::sem::NamedProperty::Effort&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getEffort))
    .def("isVisibility", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isVisibility))
    .def("getVisibility", static_cast<org::sem::NamedProperty::Visibility&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getVisibility))
    .def("isExportOptions", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportOptions))
    .def("getExportOptions", static_cast<org::sem::NamedProperty::ExportOptions&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportOptions))
    .def("isBlocker", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isBlocker))
    .def("getBlocker", static_cast<org::sem::NamedProperty::Blocker&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getBlocker))
    .def("isUnnumbered", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isUnnumbered))
    .def("getUnnumbered", static_cast<org::sem::NamedProperty::Unnumbered&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getUnnumbered))
    .def("isCreated", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCreated))
    .def("getCreated", static_cast<org::sem::NamedProperty::Created&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCreated))
    .def("isRadioId", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isRadioId))
    .def("getRadioId", static_cast<org::sem::NamedProperty::RadioId&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getRadioId))
    .def("isHashtagDef", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isHashtagDef))
    .def("getHashtagDef", static_cast<org::sem::NamedProperty::HashtagDef&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getHashtagDef))
    .def("isCustomArgs", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomArgs))
    .def("getCustomArgs", static_cast<org::sem::NamedProperty::CustomArgs&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomArgs))
    .def("isCustomRaw", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomRaw))
    .def("getCustomRaw", static_cast<org::sem::NamedProperty::CustomRaw&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomRaw))
    .def("isCustomSubtreeJson", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeJson))
    .def("getCustomSubtreeJson", static_cast<org::sem::NamedProperty::CustomSubtreeJson&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeJson))
    .def("isCustomSubtreeFlags", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeFlags))
    .def("getCustomSubtreeFlags", static_cast<org::sem::NamedProperty::CustomSubtreeFlags&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeFlags))
    .def_static("getKindStatic",
                static_cast<org::sem::NamedProperty::Kind(*)(org::sem::NamedProperty::Data const&)>(&org::sem::NamedProperty::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<org::sem::NamedProperty::Kind(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::NamedProperty::Data const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::NamedProperty::Kind(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::sub_variant_get_kind))
    .def("__repr__", [](org::sem::NamedProperty _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::None, org::sem::SemId<org::sem::None>, org::sem::Org>(m, "None")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::None {
                        org::sem::None result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::None _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::None _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::ErrorItem, org::sem::SemId<org::sem::ErrorItem>, org::sem::Org>(m, "ErrorItem")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::ErrorItem {
                        org::sem::ErrorItem result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("message", &org::sem::ErrorItem::message)
    .def_readwrite("function", &org::sem::ErrorItem::function, R"RAW(Conversion function name where the error was created)RAW")
    .def_readwrite("line", &org::sem::ErrorItem::line, R"RAW(Line number for the conversion where the error was created)RAW")
    .def("__repr__", [](org::sem::ErrorItem _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ErrorItem _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::ErrorGroup, org::sem::SemId<org::sem::ErrorGroup>, org::sem::Org>(m, "ErrorGroup")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::ErrorGroup {
                        org::sem::ErrorGroup result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("diagnostics", &org::sem::ErrorGroup::diagnostics)
    .def_readwrite("function", &org::sem::ErrorGroup::function, R"RAW(Conversion function name where the error was created)RAW")
    .def_readwrite("line", &org::sem::ErrorGroup::line, R"RAW(Line number for the conversion where the error was created)RAW")
    .def("__repr__", [](org::sem::ErrorGroup _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ErrorGroup _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Stmt, org::sem::SemId<org::sem::Stmt>, org::sem::Org>(m, "Stmt")
    .def_readwrite("attached", &org::sem::Stmt::attached)
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt::*)() const>(&org::sem::Stmt::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::Stmt::*)() const>(&org::sem::Stmt::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Stmt::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    ;
  pybind11::class_<org::sem::Inline, org::sem::SemId<org::sem::Inline>, org::sem::Org>(m, "Inline")
    ;
  pybind11::class_<org::sem::StmtList, org::sem::SemId<org::sem::StmtList>, org::sem::Org>(m, "StmtList")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::StmtList {
                        org::sem::StmtList result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::StmtList _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::StmtList _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Empty, org::sem::SemId<org::sem::Empty>, org::sem::Org>(m, "Empty")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Empty {
                        org::sem::Empty result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::Empty _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Empty _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Cmd, org::sem::SemId<org::sem::Cmd>, org::sem::Stmt>(m, "Cmd")
    .def_readwrite("attrs", &org::sem::Cmd::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::Cmd::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Cmd::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Cmd::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Cmd::*)(hstd::Str const&) const>(&org::sem::Cmd::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Cmd::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Cmd::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Cmd::*)() const>(&org::sem::Cmd::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::Cmd::*)() const>(&org::sem::Cmd::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Cmd::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Cmd::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Cmd::*)(hstd::Str const&) const>(&org::sem::Cmd::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    ;
  pybind11::class_<org::sem::Block, org::sem::SemId<org::sem::Block>, org::sem::Cmd>(m, "Block")
    .def_readwrite("attrs", &org::sem::Block::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::Block::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Block::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Block::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Block::*)(hstd::Str const&) const>(&org::sem::Block::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Block::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Block::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Block::*)() const>(&org::sem::Block::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::Block::*)() const>(&org::sem::Block::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Block::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Block::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Block::*)(hstd::Str const&) const>(&org::sem::Block::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    ;
  pybind11::class_<org::sem::LineCommand, org::sem::SemId<org::sem::LineCommand>, org::sem::Cmd>(m, "LineCommand")
    .def_readwrite("attrs", &org::sem::LineCommand::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::LineCommand::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::LineCommand::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::LineCommand::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::LineCommand::*)(hstd::Str const&) const>(&org::sem::LineCommand::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::LineCommand::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::LineCommand::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::LineCommand::*)() const>(&org::sem::LineCommand::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::LineCommand::*)() const>(&org::sem::LineCommand::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::LineCommand::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::LineCommand::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::LineCommand::*)(hstd::Str const&) const>(&org::sem::LineCommand::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    ;
  pybind11::class_<org::sem::Attached, org::sem::SemId<org::sem::Attached>, org::sem::LineCommand>(m, "Attached")
    .def_readwrite("attrs", &org::sem::Attached::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::Attached::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Attached::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Attached::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Attached::*)(hstd::Str const&) const>(&org::sem::Attached::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Attached::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Attached::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Attached::*)() const>(&org::sem::Attached::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::Attached::*)() const>(&org::sem::Attached::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Attached::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Attached::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Attached::*)(hstd::Str const&) const>(&org::sem::Attached::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    ;
  pybind11::class_<org::sem::Leaf, org::sem::SemId<org::sem::Leaf>, org::sem::Org>(m, "Leaf")
    .def_readwrite("text", &org::sem::Leaf::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<hstd::Str(org::sem::Leaf::*)() const>(&org::sem::Leaf::getText))
    ;
  pybind11::class_<org::sem::CmdCaption, org::sem::SemId<org::sem::CmdCaption>, org::sem::Attached>(m, "CmdCaption")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdCaption {
                        org::sem::CmdCaption result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &org::sem::CmdCaption::text, R"RAW(Content description)RAW")
    .def_readwrite("attrs", &org::sem::CmdCaption::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::CmdCaption::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdCaption::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdCaption::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdCaption::*)(hstd::Str const&) const>(&org::sem::CmdCaption::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdCaption::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdCaption::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdCaption::*)() const>(&org::sem::CmdCaption::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::CmdCaption::*)() const>(&org::sem::CmdCaption::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdCaption::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdCaption::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdCaption::*)(hstd::Str const&) const>(&org::sem::CmdCaption::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::CmdCaption _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCaption _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::CmdColumns, org::sem::SemId<org::sem::CmdColumns>, org::sem::Attached>(m, "CmdColumns")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdColumns {
                        org::sem::CmdColumns result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("view", &org::sem::CmdColumns::view)
    .def_readwrite("attrs", &org::sem::CmdColumns::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::CmdColumns::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdColumns::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdColumns::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdColumns::*)(hstd::Str const&) const>(&org::sem::CmdColumns::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdColumns::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdColumns::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdColumns::*)() const>(&org::sem::CmdColumns::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::CmdColumns::*)() const>(&org::sem::CmdColumns::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdColumns::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdColumns::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdColumns::*)(hstd::Str const&) const>(&org::sem::CmdColumns::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::CmdColumns _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdColumns _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::CmdName, org::sem::SemId<org::sem::CmdName>, org::sem::Attached>(m, "CmdName")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdName {
                        org::sem::CmdName result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::CmdName::name)
    .def_readwrite("attrs", &org::sem::CmdName::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::CmdName::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdName::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdName::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdName::*)(hstd::Str const&) const>(&org::sem::CmdName::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdName::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdName::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdName::*)() const>(&org::sem::CmdName::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::CmdName::*)() const>(&org::sem::CmdName::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdName::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdName::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdName::*)(hstd::Str const&) const>(&org::sem::CmdName::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::CmdName _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdName _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::CmdCustomArgs, org::sem::SemId<org::sem::CmdCustomArgs>, org::sem::Cmd>(m, "CmdCustomArgs")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdCustomArgs {
                        org::sem::CmdCustomArgs result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::CmdCustomArgs::name)
    .def_readwrite("isAttached", &org::sem::CmdCustomArgs::isAttached)
    .def_readwrite("attrs", &org::sem::CmdCustomArgs::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::CmdCustomArgs::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdCustomArgs::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdCustomArgs::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdCustomArgs::*)(hstd::Str const&) const>(&org::sem::CmdCustomArgs::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdCustomArgs::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdCustomArgs::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdCustomArgs::*)() const>(&org::sem::CmdCustomArgs::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::CmdCustomArgs::*)() const>(&org::sem::CmdCustomArgs::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdCustomArgs::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdCustomArgs::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdCustomArgs::*)(hstd::Str const&) const>(&org::sem::CmdCustomArgs::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::CmdCustomArgs _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCustomArgs _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::CmdCustomRaw, org::sem::SemId<org::sem::CmdCustomRaw>, org::sem::Stmt>(m, "CmdCustomRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdCustomRaw {
                        org::sem::CmdCustomRaw result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::CmdCustomRaw::name)
    .def_readwrite("isAttached", &org::sem::CmdCustomRaw::isAttached)
    .def_readwrite("text", &org::sem::CmdCustomRaw::text)
    .def_readwrite("attached", &org::sem::CmdCustomRaw::attached)
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdCustomRaw::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdCustomRaw::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdCustomRaw::*)() const>(&org::sem::CmdCustomRaw::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::CmdCustomRaw::*)() const>(&org::sem::CmdCustomRaw::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdCustomRaw::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdCustomRaw::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdCustomRaw::*)(hstd::Str const&) const>(&org::sem::CmdCustomRaw::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::CmdCustomRaw _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCustomRaw _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::CmdCustomText, org::sem::SemId<org::sem::CmdCustomText>, org::sem::Stmt>(m, "CmdCustomText")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdCustomText {
                        org::sem::CmdCustomText result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::CmdCustomText::name)
    .def_readwrite("isAttached", &org::sem::CmdCustomText::isAttached)
    .def_readwrite("text", &org::sem::CmdCustomText::text)
    .def_readwrite("attached", &org::sem::CmdCustomText::attached)
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdCustomText::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdCustomText::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdCustomText::*)() const>(&org::sem::CmdCustomText::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::CmdCustomText::*)() const>(&org::sem::CmdCustomText::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdCustomText::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdCustomText::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdCustomText::*)(hstd::Str const&) const>(&org::sem::CmdCustomText::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::CmdCustomText _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCustomText _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::CmdCall, org::sem::SemId<org::sem::CmdCall>, org::sem::Attached>(m, "CmdCall")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdCall {
                        org::sem::CmdCall result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::CmdCall::name, R"RAW(Code block call name)RAW")
    .def_readwrite("fileName", &org::sem::CmdCall::fileName, R"RAW(Which file code block should come from)RAW")
    .def_readwrite("insideHeaderAttrs", &org::sem::CmdCall::insideHeaderAttrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("callAttrs", &org::sem::CmdCall::callAttrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("endHeaderAttrs", &org::sem::CmdCall::endHeaderAttrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("result", &org::sem::CmdCall::result, R"RAW(Code evaluation results)RAW")
    .def_readwrite("attrs", &org::sem::CmdCall::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::CmdCall::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdCall::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdCall::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdCall::*)(hstd::Str const&) const>(&org::sem::CmdCall::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdCall::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdCall::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdCall::*)() const>(&org::sem::CmdCall::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::CmdCall::*)() const>(&org::sem::CmdCall::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdCall::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdCall::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdCall::*)(hstd::Str const&) const>(&org::sem::CmdCall::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::CmdCall _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCall _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::CmdTblfm, org::sem::SemId<org::sem::CmdTblfm>, org::sem::Cmd>(m, "CmdTblfm")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdTblfm {
                        org::sem::CmdTblfm result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("expr", &org::sem::CmdTblfm::expr)
    .def_readwrite("attrs", &org::sem::CmdTblfm::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::CmdTblfm::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdTblfm::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdTblfm::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdTblfm::*)(hstd::Str const&) const>(&org::sem::CmdTblfm::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdTblfm::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdTblfm::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdTblfm::*)() const>(&org::sem::CmdTblfm::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::CmdTblfm::*)() const>(&org::sem::CmdTblfm::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdTblfm::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdTblfm::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdTblfm::*)(hstd::Str const&) const>(&org::sem::CmdTblfm::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::CmdTblfm _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdTblfm _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::HashTag, org::sem::SemId<org::sem::HashTag>, org::sem::Inline>(m, "HashTag")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::HashTag {
                        org::sem::HashTag result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &org::sem::HashTag::text)
    .def("__repr__", [](org::sem::HashTag _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::HashTag _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::InlineFootnote, org::sem::SemId<org::sem::InlineFootnote>, org::sem::Inline>(m, "InlineFootnote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::InlineFootnote {
                        org::sem::InlineFootnote result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("tag", &org::sem::InlineFootnote::tag, R"RAW(Footnote text target name)RAW")
    .def_readwrite("definition", &org::sem::InlineFootnote::definition, R"RAW(Link to possibly resolved definition)RAW")
    .def("__repr__", [](org::sem::InlineFootnote _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::InlineFootnote _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::InlineExport, org::sem::SemId<org::sem::InlineExport>, org::sem::Inline>(m, "InlineExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::InlineExport {
                        org::sem::InlineExport result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("exporter", &org::sem::InlineExport::exporter)
    .def_readwrite("content", &org::sem::InlineExport::content)
    .def("__repr__", [](org::sem::InlineExport _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::InlineExport _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::Time::Repeat::Mode>(m, "TimeRepeatMode", type_registry_guard);
  pybind11::enum_<org::sem::Time::Repeat::Mode>(m, "TimeRepeatMode")
    .value("None", org::sem::Time::Repeat::Mode::None, R"RAW(Do not repeat task on completion)RAW")
    .value("Exact", org::sem::Time::Repeat::Mode::Exact, R"RAW(?)RAW")
    .value("FirstMatch", org::sem::Time::Repeat::Mode::FirstMatch, R"RAW(Repeat on the first matching day in the future)RAW")
    .value("SameDay", org::sem::Time::Repeat::Mode::SameDay, R"RAW(Repeat task on the same day next week/month/year)RAW")
    .def("__iter__", [](org::sem::Time::Repeat::Mode _self) -> org::bind::python::PyEnumIterator<org::sem::Time::Repeat::Mode> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::Time::Repeat::Mode>
                     ();
                     })
    ;
  bind_enum_iterator<org::sem::Time::Repeat::Period>(m, "TimeRepeatPeriod", type_registry_guard);
  pybind11::enum_<org::sem::Time::Repeat::Period>(m, "TimeRepeatPeriod")
    .value("Year", org::sem::Time::Repeat::Period::Year)
    .value("Month", org::sem::Time::Repeat::Period::Month)
    .value("Week", org::sem::Time::Repeat::Period::Week)
    .value("Day", org::sem::Time::Repeat::Period::Day)
    .value("Hour", org::sem::Time::Repeat::Period::Hour)
    .value("Minute", org::sem::Time::Repeat::Period::Minute)
    .def("__iter__", [](org::sem::Time::Repeat::Period _self) -> org::bind::python::PyEnumIterator<org::sem::Time::Repeat::Period> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::Time::Repeat::Period>
                     ();
                     })
    ;
  pybind11::class_<org::sem::Time::Repeat>(m, "TimeRepeat")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Time::Repeat {
                        org::sem::Time::Repeat result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("mode", &org::sem::Time::Repeat::mode, R"RAW(mode)RAW")
    .def_readwrite("period", &org::sem::Time::Repeat::period, R"RAW(period)RAW")
    .def_readwrite("count", &org::sem::Time::Repeat::count, R"RAW(count)RAW")
    .def("__repr__", [](org::sem::Time::Repeat _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Time::Repeat _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Time::Static>(m, "TimeStatic")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Time::Static {
                        org::sem::Time::Static result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("repeat", &org::sem::Time::Static::repeat)
    .def_readwrite("time", &org::sem::Time::Static::time)
    .def("__repr__", [](org::sem::Time::Static _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Time::Static _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Time::Dynamic>(m, "TimeDynamic")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Time::Dynamic {
                        org::sem::Time::Dynamic result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("expr", &org::sem::Time::Dynamic::expr)
    .def("__repr__", [](org::sem::Time::Dynamic _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Time::Dynamic _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::Time::TimeKind>(m, "TimeTimeKind", type_registry_guard);
  pybind11::enum_<org::sem::Time::TimeKind>(m, "TimeTimeKind")
    .value("Static", org::sem::Time::TimeKind::Static)
    .value("Dynamic", org::sem::Time::TimeKind::Dynamic)
    .def("__iter__", [](org::sem::Time::TimeKind _self) -> org::bind::python::PyEnumIterator<org::sem::Time::TimeKind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::Time::TimeKind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::Time, org::sem::SemId<org::sem::Time>, org::sem::Org>(m, "Time")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Time {
                        org::sem::Time result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isActive", &org::sem::Time::isActive, R"RAW(<active> vs [inactive])RAW")
    .def_readwrite("time", &org::sem::Time::time)
    .def("getYear", static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getYear))
    .def("getMonth", static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getMonth))
    .def("getDay", static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getDay))
    .def("getHour", static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getHour))
    .def("getMinute", static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getMinute))
    .def("getSecond", static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getSecond))
    .def("getStaticTime", static_cast<hstd::UserTime(org::sem::Time::*)() const>(&org::sem::Time::getStaticTime))
    .def("isStatic", static_cast<bool(org::sem::Time::*)() const>(&org::sem::Time::isStatic))
    .def("getStatic", static_cast<org::sem::Time::Static&(org::sem::Time::*)()>(&org::sem::Time::getStatic))
    .def("isDynamic", static_cast<bool(org::sem::Time::*)() const>(&org::sem::Time::isDynamic))
    .def("getDynamic", static_cast<org::sem::Time::Dynamic&(org::sem::Time::*)()>(&org::sem::Time::getDynamic))
    .def_static("getTimeKindStatic",
                static_cast<org::sem::Time::TimeKind(*)(org::sem::Time::TimeVariant const&)>(&org::sem::Time::getTimeKind),
                pybind11::arg("__input"))
    .def("getTimeKind", static_cast<org::sem::Time::TimeKind(org::sem::Time::*)() const>(&org::sem::Time::getTimeKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::Time::*)() const>(&org::sem::Time::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::Time::TimeVariant const&(org::sem::Time::*)() const>(&org::sem::Time::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::Time::TimeKind(org::sem::Time::*)() const>(&org::sem::Time::sub_variant_get_kind))
    .def("__repr__", [](org::sem::Time _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Time _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::TimeRange, org::sem::SemId<org::sem::TimeRange>, org::sem::Org>(m, "TimeRange")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::TimeRange {
                        org::sem::TimeRange result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("from_", &org::sem::TimeRange::from, R"RAW(Starting time)RAW")
    .def_readwrite("to", &org::sem::TimeRange::to, R"RAW(Finishing time)RAW")
    .def("__repr__", [](org::sem::TimeRange _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::TimeRange _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Macro, org::sem::SemId<org::sem::Macro>, org::sem::Org>(m, "Macro")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Macro {
                        org::sem::Macro result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::Macro::name, R"RAW(Macro name)RAW")
    .def_readwrite("attrs", &org::sem::Macro::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def("__repr__", [](org::sem::Macro _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Macro _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Symbol::Param>(m, "SymbolParam")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Symbol::Param {
                        org::sem::Symbol::Param result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("key", &org::sem::Symbol::Param::key, R"RAW(Key -- for non-positional)RAW")
    .def_readwrite("value", &org::sem::Symbol::Param::value, R"RAW(Uninterpreted value)RAW")
    .def("__repr__", [](org::sem::Symbol::Param _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Symbol::Param _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Symbol, org::sem::SemId<org::sem::Symbol>, org::sem::Org>(m, "Symbol")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Symbol {
                        org::sem::Symbol result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::Symbol::name, R"RAW(Name of the symbol)RAW")
    .def_readwrite("parameters", &org::sem::Symbol::parameters, R"RAW(Optional list of parameters)RAW")
    .def_readwrite("positional", &org::sem::Symbol::positional, R"RAW(Positional parameters)RAW")
    .def("__repr__", [](org::sem::Symbol _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Symbol _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Escaped, org::sem::SemId<org::sem::Escaped>, org::sem::Leaf>(m, "Escaped")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Escaped {
                        org::sem::Escaped result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &org::sem::Escaped::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<hstd::Str(org::sem::Escaped::*)() const>(&org::sem::Escaped::getText))
    .def("__repr__", [](org::sem::Escaped _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Escaped _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Newline, org::sem::SemId<org::sem::Newline>, org::sem::Leaf>(m, "Newline")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Newline {
                        org::sem::Newline result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &org::sem::Newline::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<hstd::Str(org::sem::Newline::*)() const>(&org::sem::Newline::getText))
    .def("__repr__", [](org::sem::Newline _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Newline _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Space, org::sem::SemId<org::sem::Space>, org::sem::Leaf>(m, "Space")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Space {
                        org::sem::Space result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &org::sem::Space::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<hstd::Str(org::sem::Space::*)() const>(&org::sem::Space::getText))
    .def("__repr__", [](org::sem::Space _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Space _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Word, org::sem::SemId<org::sem::Word>, org::sem::Leaf>(m, "Word")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Word {
                        org::sem::Word result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &org::sem::Word::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<hstd::Str(org::sem::Word::*)() const>(&org::sem::Word::getText))
    .def("__repr__", [](org::sem::Word _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Word _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::AtMention, org::sem::SemId<org::sem::AtMention>, org::sem::Leaf>(m, "AtMention")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::AtMention {
                        org::sem::AtMention result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &org::sem::AtMention::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<hstd::Str(org::sem::AtMention::*)() const>(&org::sem::AtMention::getText))
    .def("__repr__", [](org::sem::AtMention _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AtMention _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::RawText, org::sem::SemId<org::sem::RawText>, org::sem::Leaf>(m, "RawText")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::RawText {
                        org::sem::RawText result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &org::sem::RawText::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<hstd::Str(org::sem::RawText::*)() const>(&org::sem::RawText::getText))
    .def("__repr__", [](org::sem::RawText _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::RawText _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Punctuation, org::sem::SemId<org::sem::Punctuation>, org::sem::Leaf>(m, "Punctuation")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Punctuation {
                        org::sem::Punctuation result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &org::sem::Punctuation::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<hstd::Str(org::sem::Punctuation::*)() const>(&org::sem::Punctuation::getText))
    .def("__repr__", [](org::sem::Punctuation _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Punctuation _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Placeholder, org::sem::SemId<org::sem::Placeholder>, org::sem::Leaf>(m, "Placeholder")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Placeholder {
                        org::sem::Placeholder result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &org::sem::Placeholder::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<hstd::Str(org::sem::Placeholder::*)() const>(&org::sem::Placeholder::getText))
    .def("__repr__", [](org::sem::Placeholder _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Placeholder _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::BigIdent, org::sem::SemId<org::sem::BigIdent>, org::sem::Leaf>(m, "BigIdent")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::BigIdent {
                        org::sem::BigIdent result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &org::sem::BigIdent::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<hstd::Str(org::sem::BigIdent::*)() const>(&org::sem::BigIdent::getText))
    .def("__repr__", [](org::sem::BigIdent _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BigIdent _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::TextTarget, org::sem::SemId<org::sem::TextTarget>, org::sem::Leaf>(m, "TextTarget")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::TextTarget {
                        org::sem::TextTarget result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &org::sem::TextTarget::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<hstd::Str(org::sem::TextTarget::*)() const>(&org::sem::TextTarget::getText))
    .def("__repr__", [](org::sem::TextTarget _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::TextTarget _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Markup, org::sem::SemId<org::sem::Markup>, org::sem::Org>(m, "Markup")
    ;
  pybind11::class_<org::sem::Bold, org::sem::SemId<org::sem::Bold>, org::sem::Markup>(m, "Bold")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Bold {
                        org::sem::Bold result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::Bold _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Bold _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Underline, org::sem::SemId<org::sem::Underline>, org::sem::Markup>(m, "Underline")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Underline {
                        org::sem::Underline result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::Underline _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Underline _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Monospace, org::sem::SemId<org::sem::Monospace>, org::sem::Markup>(m, "Monospace")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Monospace {
                        org::sem::Monospace result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::Monospace _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Monospace _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::MarkQuote, org::sem::SemId<org::sem::MarkQuote>, org::sem::Markup>(m, "MarkQuote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::MarkQuote {
                        org::sem::MarkQuote result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::MarkQuote _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::MarkQuote _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Verbatim, org::sem::SemId<org::sem::Verbatim>, org::sem::Markup>(m, "Verbatim")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Verbatim {
                        org::sem::Verbatim result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::Verbatim _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Verbatim _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Italic, org::sem::SemId<org::sem::Italic>, org::sem::Markup>(m, "Italic")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Italic {
                        org::sem::Italic result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::Italic _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Italic _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Strike, org::sem::SemId<org::sem::Strike>, org::sem::Markup>(m, "Strike")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Strike {
                        org::sem::Strike result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::Strike _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Strike _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Par, org::sem::SemId<org::sem::Par>, org::sem::Markup>(m, "Par")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Par {
                        org::sem::Par result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::Par _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Par _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::RadioTarget, org::sem::SemId<org::sem::RadioTarget>, org::sem::Org>(m, "RadioTarget")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::RadioTarget {
                        org::sem::RadioTarget result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("words", &org::sem::RadioTarget::words)
    .def("__repr__", [](org::sem::RadioTarget _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::RadioTarget _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Latex, org::sem::SemId<org::sem::Latex>, org::sem::Org>(m, "Latex")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Latex {
                        org::sem::Latex result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::Latex _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Latex _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Link, org::sem::SemId<org::sem::Link>, org::sem::Stmt>(m, "Link")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Link {
                        org::sem::Link result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("description", &org::sem::Link::description)
    .def_readwrite("target", &org::sem::Link::target)
    .def_readwrite("attached", &org::sem::Link::attached)
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Link::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Link::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Link::*)() const>(&org::sem::Link::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::Link::*)() const>(&org::sem::Link::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Link::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Link::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Link::*)(hstd::Str const&) const>(&org::sem::Link::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::Link _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Link _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::BlockCenter, org::sem::SemId<org::sem::BlockCenter>, org::sem::Block>(m, "BlockCenter")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::BlockCenter {
                        org::sem::BlockCenter result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attrs", &org::sem::BlockCenter::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::BlockCenter::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockCenter::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockCenter::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockCenter::*)(hstd::Str const&) const>(&org::sem::BlockCenter::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockCenter::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockCenter::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockCenter::*)() const>(&org::sem::BlockCenter::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::BlockCenter::*)() const>(&org::sem::BlockCenter::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockCenter::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockCenter::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockCenter::*)(hstd::Str const&) const>(&org::sem::BlockCenter::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::BlockCenter _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCenter _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::BlockQuote, org::sem::SemId<org::sem::BlockQuote>, org::sem::Block>(m, "BlockQuote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::BlockQuote {
                        org::sem::BlockQuote result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attrs", &org::sem::BlockQuote::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::BlockQuote::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockQuote::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockQuote::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockQuote::*)(hstd::Str const&) const>(&org::sem::BlockQuote::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockQuote::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockQuote::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockQuote::*)() const>(&org::sem::BlockQuote::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::BlockQuote::*)() const>(&org::sem::BlockQuote::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockQuote::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockQuote::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockQuote::*)(hstd::Str const&) const>(&org::sem::BlockQuote::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::BlockQuote _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockQuote _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::BlockComment, org::sem::SemId<org::sem::BlockComment>, org::sem::Stmt>(m, "BlockComment")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::BlockComment {
                        org::sem::BlockComment result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attached", &org::sem::BlockComment::attached)
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockComment::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockComment::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockComment::*)() const>(&org::sem::BlockComment::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::BlockComment::*)() const>(&org::sem::BlockComment::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockComment::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockComment::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockComment::*)(hstd::Str const&) const>(&org::sem::BlockComment::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::BlockComment _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockComment _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::BlockVerse, org::sem::SemId<org::sem::BlockVerse>, org::sem::Block>(m, "BlockVerse")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::BlockVerse {
                        org::sem::BlockVerse result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attrs", &org::sem::BlockVerse::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::BlockVerse::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockVerse::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockVerse::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockVerse::*)(hstd::Str const&) const>(&org::sem::BlockVerse::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockVerse::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockVerse::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockVerse::*)() const>(&org::sem::BlockVerse::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::BlockVerse::*)() const>(&org::sem::BlockVerse::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockVerse::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockVerse::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockVerse::*)(hstd::Str const&) const>(&org::sem::BlockVerse::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::BlockVerse _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockVerse _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::BlockDynamicFallback, org::sem::SemId<org::sem::BlockDynamicFallback>, org::sem::Block>(m, "BlockDynamicFallback")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::BlockDynamicFallback {
                        org::sem::BlockDynamicFallback result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::BlockDynamicFallback::name)
    .def_readwrite("attrs", &org::sem::BlockDynamicFallback::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::BlockDynamicFallback::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockDynamicFallback::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockDynamicFallback::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockDynamicFallback::*)(hstd::Str const&) const>(&org::sem::BlockDynamicFallback::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockDynamicFallback::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockDynamicFallback::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockDynamicFallback::*)() const>(&org::sem::BlockDynamicFallback::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::BlockDynamicFallback::*)() const>(&org::sem::BlockDynamicFallback::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockDynamicFallback::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockDynamicFallback::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockDynamicFallback::*)(hstd::Str const&) const>(&org::sem::BlockDynamicFallback::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::BlockDynamicFallback _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockDynamicFallback _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::BlockExample, org::sem::SemId<org::sem::BlockExample>, org::sem::Block>(m, "BlockExample")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::BlockExample {
                        org::sem::BlockExample result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attrs", &org::sem::BlockExample::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::BlockExample::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockExample::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockExample::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockExample::*)(hstd::Str const&) const>(&org::sem::BlockExample::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockExample::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockExample::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockExample::*)() const>(&org::sem::BlockExample::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::BlockExample::*)() const>(&org::sem::BlockExample::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockExample::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockExample::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockExample::*)(hstd::Str const&) const>(&org::sem::BlockExample::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::BlockExample _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockExample _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::BlockExport, org::sem::SemId<org::sem::BlockExport>, org::sem::Block>(m, "BlockExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::BlockExport {
                        org::sem::BlockExport result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("exporter", &org::sem::BlockExport::exporter)
    .def_readwrite("content", &org::sem::BlockExport::content)
    .def_readwrite("attrs", &org::sem::BlockExport::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::BlockExport::attached)
    .def("getPlacement", static_cast<hstd::Opt<hstd::Str>(org::sem::BlockExport::*)() const>(&org::sem::BlockExport::getPlacement), R"RAW(Return value of the :placement attribute if present)RAW")
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockExport::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockExport::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockExport::*)(hstd::Str const&) const>(&org::sem::BlockExport::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockExport::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockExport::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockExport::*)() const>(&org::sem::BlockExport::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::BlockExport::*)() const>(&org::sem::BlockExport::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockExport::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockExport::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockExport::*)(hstd::Str const&) const>(&org::sem::BlockExport::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::BlockExport _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockExport _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::BlockAdmonition, org::sem::SemId<org::sem::BlockAdmonition>, org::sem::Block>(m, "BlockAdmonition")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::BlockAdmonition {
                        org::sem::BlockAdmonition result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attrs", &org::sem::BlockAdmonition::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::BlockAdmonition::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockAdmonition::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockAdmonition::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockAdmonition::*)(hstd::Str const&) const>(&org::sem::BlockAdmonition::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockAdmonition::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockAdmonition::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockAdmonition::*)() const>(&org::sem::BlockAdmonition::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::BlockAdmonition::*)() const>(&org::sem::BlockAdmonition::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockAdmonition::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockAdmonition::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockAdmonition::*)(hstd::Str const&) const>(&org::sem::BlockAdmonition::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::BlockAdmonition _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockAdmonition _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::BlockCodeEvalResult, org::sem::SemId<org::sem::BlockCodeEvalResult>, org::sem::Block>(m, "BlockCodeEvalResult")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::BlockCodeEvalResult {
                        org::sem::BlockCodeEvalResult result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("raw", &org::sem::BlockCodeEvalResult::raw)
    .def_readwrite("node", &org::sem::BlockCodeEvalResult::node)
    .def_readwrite("attrs", &org::sem::BlockCodeEvalResult::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::BlockCodeEvalResult::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockCodeEvalResult::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockCodeEvalResult::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockCodeEvalResult::*)(hstd::Str const&) const>(&org::sem::BlockCodeEvalResult::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockCodeEvalResult::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockCodeEvalResult::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockCodeEvalResult::*)() const>(&org::sem::BlockCodeEvalResult::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::BlockCodeEvalResult::*)() const>(&org::sem::BlockCodeEvalResult::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockCodeEvalResult::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockCodeEvalResult::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockCodeEvalResult::*)(hstd::Str const&) const>(&org::sem::BlockCodeEvalResult::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::BlockCodeEvalResult _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeEvalResult _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::BlockCode, org::sem::SemId<org::sem::BlockCode>, org::sem::Block>(m, "BlockCode")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::BlockCode {
                        org::sem::BlockCode result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("lang", &org::sem::BlockCode::lang, R"RAW(Code block language name)RAW")
    .def_readwrite("exports", &org::sem::BlockCode::exports, R"RAW(What to export)RAW")
    .def_readwrite("result", &org::sem::BlockCode::result, R"RAW(Code evaluation results)RAW")
    .def_readwrite("lines", &org::sem::BlockCode::lines, R"RAW(Collected code lines)RAW")
    .def_readwrite("cache", &org::sem::BlockCode::cache, R"RAW(Do cache values?)RAW")
    .def_readwrite("eval", &org::sem::BlockCode::eval, R"RAW(Eval on export?)RAW")
    .def_readwrite("noweb", &org::sem::BlockCode::noweb, R"RAW(Web-tangle code on export/run)RAW")
    .def_readwrite("hlines", &org::sem::BlockCode::hlines, R"RAW(?)RAW")
    .def_readwrite("tangle", &org::sem::BlockCode::tangle, R"RAW(?)RAW")
    .def_readwrite("switches", &org::sem::BlockCode::switches, R"RAW(Dash-based switches for code block execution)RAW")
    .def_readwrite("attrs", &org::sem::BlockCode::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::BlockCode::attached)
    .def("getVariable",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockCode::*)(hstd::Str const&) const>(&org::sem::BlockCode::getVariable),
         pybind11::arg("varname"))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockCode::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockCode::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockCode::*)(hstd::Str const&) const>(&org::sem::BlockCode::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockCode::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockCode::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::BlockCode::*)() const>(&org::sem::BlockCode::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::BlockCode::*)() const>(&org::sem::BlockCode::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::BlockCode::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::BlockCode::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockCode::*)(hstd::Str const&) const>(&org::sem::BlockCode::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::BlockCode _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCode _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::SubtreeLog, org::sem::SemId<org::sem::SubtreeLog>, org::sem::Org>(m, "SubtreeLog")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::SubtreeLog {
                        org::sem::SubtreeLog result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("head", &org::sem::SubtreeLog::head)
    .def_readwrite("desc", &org::sem::SubtreeLog::desc, R"RAW(Optional description of the log entry)RAW")
    .def("setDescription",
         static_cast<void(org::sem::SubtreeLog::*)(org::sem::SemId<org::sem::StmtList>)>(&org::sem::SubtreeLog::setDescription),
         pybind11::arg("desc"))
    .def("__repr__", [](org::sem::SubtreeLog _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLog _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Subtree, org::sem::SemId<org::sem::Subtree>, org::sem::Org>(m, "Subtree")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Subtree {
                        org::sem::Subtree result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("level", &org::sem::Subtree::level, R"RAW(Subtree level)RAW")
    .def_readwrite("treeId", &org::sem::Subtree::treeId, R"RAW(:ID: property)RAW")
    .def_readwrite("todo", &org::sem::Subtree::todo, R"RAW(Todo state of the tree)RAW")
    .def_readwrite("completion", &org::sem::Subtree::completion, R"RAW(Task completion state)RAW")
    .def_readwrite("description", &org::sem::Subtree::description)
    .def_readwrite("tags", &org::sem::Subtree::tags, R"RAW(Trailing tags)RAW")
    .def_readwrite("title", &org::sem::Subtree::title, R"RAW(Main title)RAW")
    .def_readwrite("logbook", &org::sem::Subtree::logbook, R"RAW(Associated subtree log)RAW")
    .def_readwrite("properties", &org::sem::Subtree::properties, R"RAW(Immediate properties)RAW")
    .def_readwrite("closed", &org::sem::Subtree::closed, R"RAW(When subtree was marked as closed)RAW")
    .def_readwrite("deadline", &org::sem::Subtree::deadline, R"RAW(When is the deadline)RAW")
    .def_readwrite("scheduled", &org::sem::Subtree::scheduled, R"RAW(When the event is scheduled)RAW")
    .def_readwrite("isComment", &org::sem::Subtree::isComment, R"RAW(Subtree is annotated with the COMMENT keyword)RAW")
    .def_readwrite("isArchived", &org::sem::Subtree::isArchived, R"RAW(Subtree is tagged with `:ARCHIVE:` tag)RAW")
    .def_readwrite("priority", &org::sem::Subtree::priority)
    .def("getTimePeriods",
         static_cast<hstd::Vec<org::sem::SubtreePeriod>(org::sem::Subtree::*)(hstd::IntSet<org::sem::SubtreePeriod::Kind>) const>(&org::sem::Subtree::getTimePeriods),
         pybind11::arg("kinds"))
    .def("getProperties",
         static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree::getProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", std::nullopt))
    .def("getProperty",
         static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree::getProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", std::nullopt))
    .def("removeProperty",
         static_cast<void(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree::removeProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", std::nullopt),
         R"RAW(Remove all instances of the property with matching kind/subkind from the property list)RAW")
    .def("setProperty",
         static_cast<void(org::sem::Subtree::*)(org::sem::NamedProperty const&)>(&org::sem::Subtree::setProperty),
         pybind11::arg("value"),
         R"RAW(Create or override existing property value in the subtree property list)RAW")
    .def("setPropertyStrValue",
         static_cast<void(org::sem::Subtree::*)(hstd::Str const&, hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree::setPropertyStrValue),
         pybind11::arg("value"),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", std::nullopt),
         R"RAW(Assign a raw string literal to a property.)RAW")
    .def("getCleanTitle", static_cast<hstd::Str(org::sem::Subtree::*)() const>(&org::sem::Subtree::getCleanTitle), R"RAW(Get subtree title as a flat string, without markup nodes, but with all left strings)RAW")
    .def("__repr__", [](org::sem::Subtree _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Subtree _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Cell, org::sem::SemId<org::sem::Cell>, org::sem::Cmd>(m, "Cell")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Cell {
                        org::sem::Cell result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isBlock", &org::sem::Cell::isBlock, R"RAW(Single-line pipe cell or `#+cell:` command)RAW")
    .def_readwrite("attrs", &org::sem::Cell::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::Cell::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Cell::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Cell::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Cell::*)(hstd::Str const&) const>(&org::sem::Cell::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Cell::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Cell::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Cell::*)() const>(&org::sem::Cell::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::Cell::*)() const>(&org::sem::Cell::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Cell::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Cell::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Cell::*)(hstd::Str const&) const>(&org::sem::Cell::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::Cell _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Cell _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Row, org::sem::SemId<org::sem::Row>, org::sem::Cmd>(m, "Row")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Row {
                        org::sem::Row result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("cells", &org::sem::Row::cells, R"RAW(List of cells on the row)RAW")
    .def_readwrite("isBlock", &org::sem::Row::isBlock, R"RAW(Single-line pipe cell or `#+cell:` command)RAW")
    .def_readwrite("attrs", &org::sem::Row::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::Row::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Row::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Row::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Row::*)(hstd::Str const&) const>(&org::sem::Row::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Row::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Row::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Row::*)() const>(&org::sem::Row::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::Row::*)() const>(&org::sem::Row::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Row::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Row::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Row::*)(hstd::Str const&) const>(&org::sem::Row::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::Row _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Row _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Table, org::sem::SemId<org::sem::Table>, org::sem::Block>(m, "Table")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Table {
                        org::sem::Table result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("rows", &org::sem::Table::rows, R"RAW(List of rows for the table)RAW")
    .def_readwrite("isBlock", &org::sem::Table::isBlock, R"RAW(Single-line pipe cell or `#+cell:` command)RAW")
    .def_readwrite("attrs", &org::sem::Table::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::Table::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Table::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Table::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Table::*)(hstd::Str const&) const>(&org::sem::Table::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Table::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Table::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Table::*)() const>(&org::sem::Table::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::Table::*)() const>(&org::sem::Table::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Table::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Table::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Table::*)(hstd::Str const&) const>(&org::sem::Table::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::Table _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Table _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Paragraph, org::sem::SemId<org::sem::Paragraph>, org::sem::Stmt>(m, "Paragraph")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Paragraph {
                        org::sem::Paragraph result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attached", &org::sem::Paragraph::attached)
    .def("isFootnoteDefinition", static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::isFootnoteDefinition))
    .def("getFootnoteName", static_cast<hstd::Opt<hstd::Str>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getFootnoteName))
    .def("hasAdmonition", static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasAdmonition))
    .def("getAdmonitions", static_cast<hstd::Vec<hstd::Str>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getAdmonitions))
    .def("getAdmonitionNodes", static_cast<hstd::Vec<org::sem::SemId<org::sem::BigIdent>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getAdmonitionNodes))
    .def("hasTimestamp", static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasTimestamp))
    .def("getTimestamps", static_cast<hstd::Vec<hstd::UserTime>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getTimestamps))
    .def("getTimestampNodes", static_cast<hstd::Vec<org::sem::SemId<org::sem::Time>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getTimestampNodes))
    .def("hasLeadHashtags", static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasLeadHashtags))
    .def("getLeadHashtags", static_cast<hstd::Vec<org::sem::SemId<org::sem::HashTag>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getLeadHashtags))
    .def("getBody", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getBody), R"RAW(Return content of the paragraph, without prefix idents, hashtags, footnotes etc. )RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Paragraph::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Paragraph::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Paragraph::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Paragraph::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Paragraph::*)(hstd::Str const&) const>(&org::sem::Paragraph::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::Paragraph _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Paragraph _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::ColonExample, org::sem::SemId<org::sem::ColonExample>, org::sem::Org>(m, "ColonExample")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::ColonExample {
                        org::sem::ColonExample result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::ColonExample _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColonExample _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::CmdAttr, org::sem::SemId<org::sem::CmdAttr>, org::sem::Attached>(m, "CmdAttr")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdAttr {
                        org::sem::CmdAttr result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &org::sem::CmdAttr::target)
    .def_readwrite("attrs", &org::sem::CmdAttr::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::CmdAttr::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdAttr::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdAttr::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdAttr::*)(hstd::Str const&) const>(&org::sem::CmdAttr::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdAttr::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdAttr::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdAttr::*)() const>(&org::sem::CmdAttr::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::CmdAttr::*)() const>(&org::sem::CmdAttr::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdAttr::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdAttr::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdAttr::*)(hstd::Str const&) const>(&org::sem::CmdAttr::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::CmdAttr _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdAttr _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::CmdExport, org::sem::SemId<org::sem::CmdExport>, org::sem::Attached>(m, "CmdExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdExport {
                        org::sem::CmdExport result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("exporter", &org::sem::CmdExport::exporter)
    .def_readwrite("content", &org::sem::CmdExport::content)
    .def_readwrite("attrs", &org::sem::CmdExport::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &org::sem::CmdExport::attached)
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdExport::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdExport::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdExport::*)(hstd::Str const&) const>(&org::sem::CmdExport::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdExport::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdExport::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::CmdExport::*)() const>(&org::sem::CmdExport::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::CmdExport::*)() const>(&org::sem::CmdExport::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::CmdExport::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::CmdExport::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::CmdExport::*)(hstd::Str const&) const>(&org::sem::CmdExport::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::CmdExport _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdExport _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Call, org::sem::SemId<org::sem::Call>, org::sem::Org>(m, "Call")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Call {
                        org::sem::Call result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &org::sem::Call::name, R"RAW(Call target name)RAW")
    .def_readwrite("attrs", &org::sem::Call::attrs, R"RAW(Additional parameters aside from 'exporter')RAW")
    .def_readwrite("isCommand", &org::sem::Call::isCommand)
    .def("__repr__", [](org::sem::Call _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Call _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::List, org::sem::SemId<org::sem::List>, org::sem::Stmt>(m, "List")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::List {
                        org::sem::List result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attached", &org::sem::List::attached)
    .def("getListAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::List::*)(hstd::Str const&) const>(&org::sem::List::getListAttrs),
         pybind11::arg("key"))
    .def("getListFormattingMode", static_cast<ListFormattingMode(org::sem::List::*)() const>(&org::sem::List::getListFormattingMode))
    .def("isDescriptionList", static_cast<bool(org::sem::List::*)() const>(&org::sem::List::isDescriptionList), R"RAW(List is marked as description if any list item has a header)RAW")
    .def("isNumberedList", static_cast<bool(org::sem::List::*)() const>(&org::sem::List::isNumberedList), R"RAW(List is marked as numbered if any list item has bullet text set)RAW")
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::List::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::List::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::List::*)() const>(&org::sem::List::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::List::*)() const>(&org::sem::List::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::List::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::List::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::List::*)(hstd::Str const&) const>(&org::sem::List::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](org::sem::List _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::List _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::ListItem::Checkbox>(m, "ListItemCheckbox", type_registry_guard);
  pybind11::enum_<org::sem::ListItem::Checkbox>(m, "ListItemCheckbox")
    .value("None", org::sem::ListItem::Checkbox::None)
    .value("Done", org::sem::ListItem::Checkbox::Done)
    .value("Empty", org::sem::ListItem::Checkbox::Empty)
    .value("Partial", org::sem::ListItem::Checkbox::Partial)
    .def("__iter__", [](org::sem::ListItem::Checkbox _self) -> org::bind::python::PyEnumIterator<org::sem::ListItem::Checkbox> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::ListItem::Checkbox>
                     ();
                     })
    ;
  pybind11::class_<org::sem::ListItem, org::sem::SemId<org::sem::ListItem>, org::sem::Org>(m, "ListItem")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::ListItem {
                        org::sem::ListItem result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("checkbox", &org::sem::ListItem::checkbox)
    .def_readwrite("header", &org::sem::ListItem::header, R"RAW(Description list item header)RAW")
    .def_readwrite("bullet", &org::sem::ListItem::bullet, R"RAW(Full text of the numbered list item, e.g. `a)`, `a.`)RAW")
    .def("isDescriptionItem", static_cast<bool(org::sem::ListItem::*)() const>(&org::sem::ListItem::isDescriptionItem))
    .def("getCleanHeader", static_cast<hstd::Opt<hstd::Str>(org::sem::ListItem::*)() const>(&org::sem::ListItem::getCleanHeader), R"RAW(Return flat text for the description list header)RAW")
    .def("__repr__", [](org::sem::ListItem _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ListItem _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::DocumentOptions, org::sem::SemId<org::sem::DocumentOptions>, org::sem::Org>(m, "DocumentOptions")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::DocumentOptions {
                        org::sem::DocumentOptions result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("initialVisibility", &org::sem::DocumentOptions::initialVisibility)
    .def_readwrite("properties", &org::sem::DocumentOptions::properties)
    .def_readwrite("exportConfig", &org::sem::DocumentOptions::exportConfig)
    .def_readwrite("fixedWidthSections", &org::sem::DocumentOptions::fixedWidthSections)
    .def_readwrite("startupIndented", &org::sem::DocumentOptions::startupIndented)
    .def_readwrite("category", &org::sem::DocumentOptions::category)
    .def_readwrite("setupfile", &org::sem::DocumentOptions::setupfile)
    .def_readwrite("maxSubtreeLevelExport", &org::sem::DocumentOptions::maxSubtreeLevelExport)
    .def_readwrite("columns", &org::sem::DocumentOptions::columns)
    .def("getProperties",
         static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::DocumentOptions::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions::getProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt))
    .def("getProperty",
         static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::DocumentOptions::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions::getProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt))
    .def("__repr__", [](org::sem::DocumentOptions _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentOptions _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::DocumentFragment, org::sem::SemId<org::sem::DocumentFragment>, org::sem::Org>(m, "DocumentFragment")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::DocumentFragment {
                        org::sem::DocumentFragment result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("baseLine", &org::sem::DocumentFragment::baseLine)
    .def_readwrite("baseCol", &org::sem::DocumentFragment::baseCol)
    .def("__repr__", [](org::sem::DocumentFragment _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentFragment _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::CriticMarkup::Kind>(m, "CriticMarkupKind", type_registry_guard);
  pybind11::enum_<org::sem::CriticMarkup::Kind>(m, "CriticMarkupKind")
    .value("Deletion", org::sem::CriticMarkup::Kind::Deletion)
    .value("Addition", org::sem::CriticMarkup::Kind::Addition)
    .value("Substitution", org::sem::CriticMarkup::Kind::Substitution)
    .value("Highlighting", org::sem::CriticMarkup::Kind::Highlighting)
    .value("Comment", org::sem::CriticMarkup::Kind::Comment)
    .def("__iter__", [](org::sem::CriticMarkup::Kind _self) -> org::bind::python::PyEnumIterator<org::sem::CriticMarkup::Kind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::CriticMarkup::Kind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::CriticMarkup, org::sem::SemId<org::sem::CriticMarkup>, org::sem::Org>(m, "CriticMarkup")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CriticMarkup {
                        org::sem::CriticMarkup result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("kind", &org::sem::CriticMarkup::kind)
    .def("__repr__", [](org::sem::CriticMarkup _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CriticMarkup _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Document, org::sem::SemId<org::sem::Document>, org::sem::Org>(m, "Document")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Document {
                        org::sem::Document result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("title", &org::sem::Document::title)
    .def_readwrite("author", &org::sem::Document::author)
    .def_readwrite("creator", &org::sem::Document::creator)
    .def_readwrite("filetags", &org::sem::Document::filetags)
    .def_readwrite("email", &org::sem::Document::email)
    .def_readwrite("language", &org::sem::Document::language)
    .def_readwrite("options", &org::sem::Document::options)
    .def_readwrite("exportFileName", &org::sem::Document::exportFileName)
    .def("getProperties",
         static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Document::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document::getProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt))
    .def("getProperty",
         static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Document::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document::getProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt))
    .def("__repr__", [](org::sem::Document _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Document _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::FileTarget, org::sem::SemId<org::sem::FileTarget>, org::sem::Org>(m, "FileTarget")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::FileTarget {
                        org::sem::FileTarget result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("path", &org::sem::FileTarget::path)
    .def_readwrite("line", &org::sem::FileTarget::line)
    .def_readwrite("searchTarget", &org::sem::FileTarget::searchTarget)
    .def_readwrite("restrictToHeadlines", &org::sem::FileTarget::restrictToHeadlines)
    .def_readwrite("targetId", &org::sem::FileTarget::targetId)
    .def_readwrite("regexp", &org::sem::FileTarget::regexp)
    .def("__repr__", [](org::sem::FileTarget _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::FileTarget _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::TextSeparator, org::sem::SemId<org::sem::TextSeparator>, org::sem::Org>(m, "TextSeparator")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::TextSeparator {
                        org::sem::TextSeparator result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::TextSeparator _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::TextSeparator _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::DocumentGroup, org::sem::SemId<org::sem::DocumentGroup>, org::sem::Org>(m, "DocumentGroup")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::DocumentGroup {
                        org::sem::DocumentGroup result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::DocumentGroup _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentGroup _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::File::Document>(m, "FileDocument")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::File::Document {
                        org::sem::File::Document result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::File::Document _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::File::Document _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::File::Attachment>(m, "FileAttachment")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::File::Attachment {
                        org::sem::File::Attachment result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::File::Attachment _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::File::Attachment _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::File::Source>(m, "FileSource")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::File::Source {
                        org::sem::File::Source result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::File::Source _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::File::Source _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::File::Kind>(m, "FileKind", type_registry_guard);
  pybind11::enum_<org::sem::File::Kind>(m, "FileKind")
    .value("Document", org::sem::File::Kind::Document)
    .value("Attachment", org::sem::File::Kind::Attachment)
    .value("Source", org::sem::File::Kind::Source)
    .def("__iter__", [](org::sem::File::Kind _self) -> org::bind::python::PyEnumIterator<org::sem::File::Kind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::File::Kind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::File, org::sem::SemId<org::sem::File>, org::sem::Org>(m, "File")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::File {
                        org::sem::File result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("relPath", &org::sem::File::relPath, R"RAW(Relative path from the root directory)RAW")
    .def_readwrite("absPath", &org::sem::File::absPath, R"RAW(Absolute resolved path to physical file)RAW")
    .def_readwrite("data", &org::sem::File::data)
    .def("isDocument", static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isDocument))
    .def("getDocument", static_cast<org::sem::File::Document&(org::sem::File::*)()>(&org::sem::File::getDocument))
    .def("isAttachment", static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isAttachment))
    .def("getAttachment", static_cast<org::sem::File::Attachment&(org::sem::File::*)()>(&org::sem::File::getAttachment))
    .def("isSource", static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isSource))
    .def("getSource", static_cast<org::sem::File::Source&(org::sem::File::*)()>(&org::sem::File::getSource))
    .def_static("getFileKindStatic",
                static_cast<org::sem::File::Kind(*)(org::sem::File::Data const&)>(&org::sem::File::getFileKind),
                pybind11::arg("__input"))
    .def("getFileKind", static_cast<org::sem::File::Kind(org::sem::File::*)() const>(&org::sem::File::getFileKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::File::*)() const>(&org::sem::File::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::File::Data const&(org::sem::File::*)() const>(&org::sem::File::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::File::Kind(org::sem::File::*)() const>(&org::sem::File::sub_variant_get_kind))
    .def("__repr__", [](org::sem::File _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::File _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Directory, org::sem::SemId<org::sem::Directory>, org::sem::Org>(m, "Directory")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Directory {
                        org::sem::Directory result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("relPath", &org::sem::Directory::relPath, R"RAW(Relative path from the root directory, empty if this is the root directory)RAW")
    .def_readwrite("absPath", &org::sem::Directory::absPath, R"RAW(Absolute resolved path to physical directory)RAW")
    .def("__repr__", [](org::sem::Directory _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Directory _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::Symlink, org::sem::SemId<org::sem::Symlink>, org::sem::Org>(m, "Symlink")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::Symlink {
                        org::sem::Symlink result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isDirectory", &org::sem::Symlink::isDirectory)
    .def_readwrite("absPath", &org::sem::Symlink::absPath, R"RAW(Absolute path to the symlinked target directory. All relative paths under symlink node use its absolute path as a root.)RAW")
    .def("__repr__", [](org::sem::Symlink _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Symlink _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeIncludeBase")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdInclude::IncludeBase {
                        org::sem::CmdInclude::IncludeBase result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::CmdInclude::IncludeBase _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::IncludeBase _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::CmdInclude::Example, org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeExample")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdInclude::Example {
                        org::sem::CmdInclude::Example result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::sem::CmdInclude::Example _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::Example _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::CmdInclude::Export, org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdInclude::Export {
                        org::sem::CmdInclude::Export result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("language", &org::sem::CmdInclude::Export::language, R"RAW(Source code language for export)RAW")
    .def("__repr__", [](org::sem::CmdInclude::Export _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::Export _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::CmdInclude::Custom, org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeCustom")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdInclude::Custom {
                        org::sem::CmdInclude::Custom result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("blockName", &org::sem::CmdInclude::Custom::blockName, R"RAW(Block name not covered by the default values)RAW")
    .def("__repr__", [](org::sem::CmdInclude::Custom _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::Custom _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::CmdInclude::Src, org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeSrc")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdInclude::Src {
                        org::sem::CmdInclude::Src result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("language", &org::sem::CmdInclude::Src::language, R"RAW(Source code language for code block)RAW")
    .def("__repr__", [](org::sem::CmdInclude::Src _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::Src _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::CmdInclude::OrgDocument, org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeOrgDocument")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdInclude::OrgDocument {
                        org::sem::CmdInclude::OrgDocument result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("onlyContent", &org::sem::CmdInclude::OrgDocument::onlyContent, R"RAW(omits any planning lines or property drawers)RAW")
    .def_readwrite("subtreePath", &org::sem::CmdInclude::OrgDocument::subtreePath, R"RAW(Include first subtree matching path with `file.org::* tree`)RAW")
    .def_readwrite("minLevel", &org::sem::CmdInclude::OrgDocument::minLevel, R"RAW(The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.)RAW")
    .def_readwrite("customIdTarget", &org::sem::CmdInclude::OrgDocument::customIdTarget, R"RAW(Include target subtree content with `file.org::#custom`)RAW")
    .def("__repr__", [](org::sem::CmdInclude::OrgDocument _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::OrgDocument _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::sem::CmdInclude::Kind>(m, "CmdIncludeKind", type_registry_guard);
  pybind11::enum_<org::sem::CmdInclude::Kind>(m, "CmdIncludeKind")
    .value("Example", org::sem::CmdInclude::Kind::Example)
    .value("Export", org::sem::CmdInclude::Kind::Export)
    .value("Custom", org::sem::CmdInclude::Kind::Custom)
    .value("Src", org::sem::CmdInclude::Kind::Src)
    .value("OrgDocument", org::sem::CmdInclude::Kind::OrgDocument)
    .def("__iter__", [](org::sem::CmdInclude::Kind _self) -> org::bind::python::PyEnumIterator<org::sem::CmdInclude::Kind> {
                     return
                     org::bind::python::PyEnumIterator<org::sem::CmdInclude::Kind>
                     ();
                     })
    ;
  pybind11::class_<org::sem::CmdInclude, org::sem::SemId<org::sem::CmdInclude>, org::sem::Org>(m, "CmdInclude")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::CmdInclude {
                        org::sem::CmdInclude result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("path", &org::sem::CmdInclude::path, R"RAW(Path to include)RAW")
    .def_readwrite("firstLine", &org::sem::CmdInclude::firstLine, R"RAW(0-based index of the first line to include. NOTE: Org-mode syntax uses 1-based half-open range in the text)RAW")
    .def_readwrite("lastLine", &org::sem::CmdInclude::lastLine, R"RAW(0-based index of the last line to include)RAW")
    .def_readwrite("data", &org::sem::CmdInclude::data)
    .def("isExample", static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isExample))
    .def("getExample", static_cast<org::sem::CmdInclude::Example&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getExample))
    .def("isExport", static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isExport))
    .def("getExport", static_cast<org::sem::CmdInclude::Export&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getExport))
    .def("isCustom", static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isCustom))
    .def("getCustom", static_cast<org::sem::CmdInclude::Custom&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getCustom))
    .def("isSrc", static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isSrc))
    .def("getSrc", static_cast<org::sem::CmdInclude::Src&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getSrc))
    .def("isOrgDocument", static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isOrgDocument))
    .def("getOrgDocument", static_cast<org::sem::CmdInclude::OrgDocument&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getOrgDocument))
    .def_static("getIncludeKindStatic",
                static_cast<org::sem::CmdInclude::Kind(*)(org::sem::CmdInclude::Data const&)>(&org::sem::CmdInclude::getIncludeKind),
                pybind11::arg("__input"))
    .def("getIncludeKind", static_cast<org::sem::CmdInclude::Kind(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getIncludeKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::CmdInclude::Data const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::CmdInclude::Kind(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::sub_variant_get_kind))
    .def("__repr__", [](org::sem::CmdInclude _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<ListFormattingMode>(m, "ListFormattingMode", type_registry_guard);
  pybind11::enum_<ListFormattingMode>(m, "ListFormattingMode")
    .value("None", ListFormattingMode::None, R"RAW(Default, no custom formatting)RAW")
    .value("Table1D1Col", ListFormattingMode::Table1D1Col, R"RAW(one column, each table item is an individual row)RAW")
    .value("Table1D2Col", ListFormattingMode::Table1D2Col, R"RAW(for description lists, treat header row as an individual column)RAW")
    .value("Table2DColFirst", ListFormattingMode::Table2DColFirst, R"RAW(for nested tables, treat the first level of items as column names, treat all nested elements in these columns as row values)RAW")
    .def("__iter__", [](ListFormattingMode _self) -> org::bind::python::PyEnumIterator<ListFormattingMode> {
                     return
                     org::bind::python::PyEnumIterator<ListFormattingMode>
                     ();
                     })
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
    .def("__iter__", [](InitialSubtreeVisibility _self) -> org::bind::python::PyEnumIterator<InitialSubtreeVisibility> {
                     return
                     org::bind::python::PyEnumIterator<InitialSubtreeVisibility>
                     ();
                     })
    ;
  bind_enum_iterator<BlockCodeResults>(m, "BlockCodeResults", type_registry_guard);
  pybind11::enum_<BlockCodeResults>(m, "BlockCodeResults")
    .value("Replace", BlockCodeResults::Replace, R"RAW(Remove old result, replace with new value)RAW")
    .def("__iter__", [](BlockCodeResults _self) -> org::bind::python::PyEnumIterator<BlockCodeResults> {
                     return
                     org::bind::python::PyEnumIterator<BlockCodeResults>
                     ();
                     })
    ;
  bind_enum_iterator<BlockCodeExports>(m, "BlockCodeExports", type_registry_guard);
  pybind11::enum_<BlockCodeExports>(m, "BlockCodeExports")
    .value("None", BlockCodeExports::None, R"RAW(Hide both original code and run result)RAW")
    .value("Both", BlockCodeExports::Both, R"RAW(Show output and code)RAW")
    .value("Code", BlockCodeExports::Code, R"RAW(Show only code)RAW")
    .value("Results", BlockCodeExports::Results, R"RAW(Show only evaluation results)RAW")
    .def("__iter__", [](BlockCodeExports _self) -> org::bind::python::PyEnumIterator<BlockCodeExports> {
                     return
                     org::bind::python::PyEnumIterator<BlockCodeExports>
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
    .def("__iter__", [](OrgSpecName _self) -> org::bind::python::PyEnumIterator<OrgSpecName> {
                     return
                     org::bind::python::PyEnumIterator<OrgSpecName>
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
    .value("TableRow", OrgNodeKind::TableRow, R"RAW(Horizontal table row)RAW")
    .value("TableCell", OrgNodeKind::TableCell, R"RAW(Single cell in row. Might contain anyting, including other tables, simple text paragraph etc.)RAW")
    .value("Table", OrgNodeKind::Table, R"RAW(Org-mode table)RAW")
    .value("InlineFootnote", OrgNodeKind::InlineFootnote, R"RAW(Inline footnote with text placed directly in the node body.)RAW")
    .value("Footnote", OrgNodeKind::Footnote, R"RAW(Footnote entry. Just as regular links - internal content is not parsed, and instead just cut out verbatim into target AST node.)RAW")
    .value("Cmd", OrgNodeKind::Cmd, R"RAW(Undefined single-line command -- most likely custom user-provided oe)RAW")
    .value("Attrs", OrgNodeKind::Attrs, R"RAW(Arguments for the command block)RAW")
    .value("AttrValue", OrgNodeKind::AttrValue, R"RAW(:key name=value syntax)RAW")
    .value("AttrLisp", OrgNodeKind::AttrLisp, R"RAW(S-expression as an attribute value value)RAW")
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
    .value("BlockDynamicFallback", OrgNodeKind::BlockDynamicFallback, R"RAW(#+begin_<any> section)RAW")
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
    .value("ErrorWrap", OrgNodeKind::ErrorWrap)
    .value("ErrorToken", OrgNodeKind::ErrorToken)
    .value("Italic", OrgNodeKind::Italic)
    .value("Verbatim", OrgNodeKind::Verbatim)
    .value("Backtick", OrgNodeKind::Backtick)
    .value("Underline", OrgNodeKind::Underline)
    .value("Strike", OrgNodeKind::Strike)
    .value("Quote", OrgNodeKind::Quote)
    .value("Angle", OrgNodeKind::Angle)
    .value("Monospace", OrgNodeKind::Monospace)
    .value("Par", OrgNodeKind::Par)
    .value("CriticMarkStructure", OrgNodeKind::CriticMarkStructure)
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
    .def("__iter__", [](OrgNodeKind _self) -> org::bind::python::PyEnumIterator<OrgNodeKind> {
                     return
                     org::bind::python::PyEnumIterator<OrgNodeKind>
                     ();
                     })
    ;
  bind_enum_iterator<OrgJsonKind>(m, "OrgJsonKind", type_registry_guard);
  pybind11::enum_<OrgJsonKind>(m, "OrgJsonKind")
    .value("Null", OrgJsonKind::Null)
    .value("Object", OrgJsonKind::Object)
    .value("Array", OrgJsonKind::Array)
    .value("String", OrgJsonKind::String)
    .value("Boolean", OrgJsonKind::Boolean)
    .value("Int", OrgJsonKind::Int)
    .value("Float", OrgJsonKind::Float)
    .def("__iter__", [](OrgJsonKind _self) -> org::bind::python::PyEnumIterator<OrgJsonKind> {
                     return
                     org::bind::python::PyEnumIterator<OrgJsonKind>
                     ();
                     })
    ;
  bind_enum_iterator<OrgSemKind>(m, "OrgSemKind", type_registry_guard);
  pybind11::enum_<OrgSemKind>(m, "OrgSemKind")
    .value("None", OrgSemKind::None)
    .value("ErrorItem", OrgSemKind::ErrorItem)
    .value("ErrorGroup", OrgSemKind::ErrorGroup)
    .value("StmtList", OrgSemKind::StmtList)
    .value("Empty", OrgSemKind::Empty)
    .value("CmdCaption", OrgSemKind::CmdCaption)
    .value("CmdColumns", OrgSemKind::CmdColumns)
    .value("CmdName", OrgSemKind::CmdName)
    .value("CmdCustomArgs", OrgSemKind::CmdCustomArgs)
    .value("CmdCustomRaw", OrgSemKind::CmdCustomRaw)
    .value("CmdCustomText", OrgSemKind::CmdCustomText)
    .value("CmdCall", OrgSemKind::CmdCall)
    .value("CmdTblfm", OrgSemKind::CmdTblfm)
    .value("HashTag", OrgSemKind::HashTag)
    .value("InlineFootnote", OrgSemKind::InlineFootnote)
    .value("InlineExport", OrgSemKind::InlineExport)
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
    .value("TextTarget", OrgSemKind::TextTarget)
    .value("Bold", OrgSemKind::Bold)
    .value("Underline", OrgSemKind::Underline)
    .value("Monospace", OrgSemKind::Monospace)
    .value("MarkQuote", OrgSemKind::MarkQuote)
    .value("Verbatim", OrgSemKind::Verbatim)
    .value("Italic", OrgSemKind::Italic)
    .value("Strike", OrgSemKind::Strike)
    .value("Par", OrgSemKind::Par)
    .value("RadioTarget", OrgSemKind::RadioTarget)
    .value("Latex", OrgSemKind::Latex)
    .value("Link", OrgSemKind::Link)
    .value("BlockCenter", OrgSemKind::BlockCenter)
    .value("BlockQuote", OrgSemKind::BlockQuote)
    .value("BlockComment", OrgSemKind::BlockComment)
    .value("BlockVerse", OrgSemKind::BlockVerse)
    .value("BlockDynamicFallback", OrgSemKind::BlockDynamicFallback)
    .value("BlockExample", OrgSemKind::BlockExample)
    .value("BlockExport", OrgSemKind::BlockExport)
    .value("BlockAdmonition", OrgSemKind::BlockAdmonition)
    .value("BlockCodeEvalResult", OrgSemKind::BlockCodeEvalResult)
    .value("BlockCode", OrgSemKind::BlockCode)
    .value("SubtreeLog", OrgSemKind::SubtreeLog)
    .value("Subtree", OrgSemKind::Subtree)
    .value("Cell", OrgSemKind::Cell)
    .value("Row", OrgSemKind::Row)
    .value("Table", OrgSemKind::Table)
    .value("Paragraph", OrgSemKind::Paragraph)
    .value("ColonExample", OrgSemKind::ColonExample)
    .value("CmdAttr", OrgSemKind::CmdAttr)
    .value("CmdExport", OrgSemKind::CmdExport)
    .value("Call", OrgSemKind::Call)
    .value("List", OrgSemKind::List)
    .value("ListItem", OrgSemKind::ListItem)
    .value("DocumentOptions", OrgSemKind::DocumentOptions)
    .value("DocumentFragment", OrgSemKind::DocumentFragment)
    .value("CriticMarkup", OrgSemKind::CriticMarkup)
    .value("Document", OrgSemKind::Document)
    .value("FileTarget", OrgSemKind::FileTarget)
    .value("TextSeparator", OrgSemKind::TextSeparator)
    .value("DocumentGroup", OrgSemKind::DocumentGroup)
    .value("File", OrgSemKind::File)
    .value("Directory", OrgSemKind::Directory)
    .value("Symlink", OrgSemKind::Symlink)
    .value("CmdInclude", OrgSemKind::CmdInclude)
    .def("__iter__", [](OrgSemKind _self) -> org::bind::python::PyEnumIterator<OrgSemKind> {
                     return
                     org::bind::python::PyEnumIterator<OrgSemKind>
                     ();
                     })
    ;
  pybind11::class_<hstd::UserTimeBreakdown>(m, "UserTimeBreakdown")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::UserTimeBreakdown {
                        hstd::UserTimeBreakdown result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("year", &hstd::UserTimeBreakdown::year)
    .def_readwrite("month", &hstd::UserTimeBreakdown::month)
    .def_readwrite("day", &hstd::UserTimeBreakdown::day)
    .def_readwrite("hour", &hstd::UserTimeBreakdown::hour)
    .def_readwrite("minute", &hstd::UserTimeBreakdown::minute)
    .def_readwrite("second", &hstd::UserTimeBreakdown::second)
    .def_readwrite("zone", &hstd::UserTimeBreakdown::zone)
    .def("__repr__", [](hstd::UserTimeBreakdown _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::UserTimeBreakdown _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::UserTime>(m, "UserTime")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::UserTime {
                        hstd::UserTime result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getBreakdown", static_cast<hstd::UserTimeBreakdown(hstd::UserTime::*)() const>(&hstd::UserTime::getBreakdown))
    .def("format", static_cast<std::string(hstd::UserTime::*)() const>(&hstd::UserTime::format))
    .def("__repr__", [](hstd::UserTime _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::UserTime _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::sem::OrgJson>(m, "OrgJson")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::sem::OrgJson {
                        org::sem::OrgJson result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getKind", static_cast<OrgJsonKind(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getKind))
    .def("getJsonString", static_cast<std::string(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getJsonString))
    .def("at",
         static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::at),
         pybind11::arg("idx"))
    .def("at",
         static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(std::string const&) const>(&org::sem::OrgJson::at),
         pybind11::arg("name"))
    .def("getString", static_cast<std::string(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getString))
    .def("getField",
         static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(std::string const&) const>(&org::sem::OrgJson::getField),
         pybind11::arg("name"))
    .def("getItem",
         static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::getItem),
         pybind11::arg("index"))
    .def("getInt", static_cast<int(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getInt))
    .def("getBool", static_cast<bool(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getBool))
    .def("getArray", static_cast<hstd::Vec<org::sem::OrgJson>(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getArray))
    .def("__repr__", [](org::sem::OrgJson _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgJson _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmUniqId>(m, "immImmUniqId")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmUniqId {
                        org::imm::ImmUniqId result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::imm::ImmUniqId _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmUniqId _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmNoneValueRead>(m, "immImmNoneValueRead")
    ;
  pybind11::class_<org::imm::ImmNoneValue>(m, "immImmNoneValue")
    ;
  pybind11::class_<org::imm::ImmErrorItemValueRead>(m, "immImmErrorItemValueRead")
    .def("getMessage", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmErrorItemValueRead::*)() const>(&org::imm::ImmErrorItemValueRead::getMessage))
    .def("getFunction", static_cast<immer::ext::ext::box<std::optional<hstd::Str>> const&(org::imm::ImmErrorItemValueRead::*)() const>(&org::imm::ImmErrorItemValueRead::getFunction))
    .def("getLine", static_cast<immer::ext::ext::box<std::optional<int>> const&(org::imm::ImmErrorItemValueRead::*)() const>(&org::imm::ImmErrorItemValueRead::getLine))
    ;
  pybind11::class_<org::imm::ImmErrorItemValue>(m, "immImmErrorItemValue")
    .def("setMessage",
         static_cast<void(org::imm::ImmErrorItemValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmErrorItemValue::setMessage),
         pybind11::arg("value"))
    .def("setFunction",
         static_cast<void(org::imm::ImmErrorItemValue::*)(immer::ext::ext::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmErrorItemValue::setFunction),
         pybind11::arg("value"))
    .def("setLine",
         static_cast<void(org::imm::ImmErrorItemValue::*)(immer::ext::ext::box<std::optional<int>> const&)>(&org::imm::ImmErrorItemValue::setLine),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmErrorGroupValueRead>(m, "immImmErrorGroupValueRead")
    .def("getDiagnostics", static_cast<immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmErrorItem>> const&(org::imm::ImmErrorGroupValueRead::*)() const>(&org::imm::ImmErrorGroupValueRead::getDiagnostics))
    .def("getFunction", static_cast<immer::ext::ext::box<std::optional<hstd::Str>> const&(org::imm::ImmErrorGroupValueRead::*)() const>(&org::imm::ImmErrorGroupValueRead::getFunction))
    .def("getLine", static_cast<immer::ext::ext::box<std::optional<int>> const&(org::imm::ImmErrorGroupValueRead::*)() const>(&org::imm::ImmErrorGroupValueRead::getLine))
    ;
  pybind11::class_<org::imm::ImmErrorGroupValue>(m, "immImmErrorGroupValue")
    .def("setDiagnostics",
         static_cast<void(org::imm::ImmErrorGroupValue::*)(immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmErrorItem>> const&)>(&org::imm::ImmErrorGroupValue::setDiagnostics),
         pybind11::arg("value"))
    .def("setFunction",
         static_cast<void(org::imm::ImmErrorGroupValue::*)(immer::ext::ext::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmErrorGroupValue::setFunction),
         pybind11::arg("value"))
    .def("setLine",
         static_cast<void(org::imm::ImmErrorGroupValue::*)(immer::ext::ext::box<std::optional<int>> const&)>(&org::imm::ImmErrorGroupValue::setLine),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmStmtListValueRead>(m, "immImmStmtListValueRead")
    ;
  pybind11::class_<org::imm::ImmStmtListValue>(m, "immImmStmtListValue")
    ;
  pybind11::class_<org::imm::ImmEmptyValueRead>(m, "immImmEmptyValueRead")
    ;
  pybind11::class_<org::imm::ImmEmptyValue>(m, "immImmEmptyValue")
    ;
  pybind11::class_<org::imm::ImmCmdCaptionValueRead>(m, "immImmCmdCaptionValueRead")
    .def("getText", static_cast<org::imm::ImmIdT<org::imm::ImmParagraph> const&(org::imm::ImmCmdCaptionValueRead::*)() const>(&org::imm::ImmCmdCaptionValueRead::getText))
    ;
  pybind11::class_<org::imm::ImmCmdCaptionValue>(m, "immImmCmdCaptionValue")
    .def("setText",
         static_cast<void(org::imm::ImmCmdCaptionValue::*)(org::imm::ImmIdT<org::imm::ImmParagraph> const&)>(&org::imm::ImmCmdCaptionValue::setText),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmCmdColumnsValueRead>(m, "immImmCmdColumnsValueRead")
    .def("getView", static_cast<org::sem::ColumnView const&(org::imm::ImmCmdColumnsValueRead::*)() const>(&org::imm::ImmCmdColumnsValueRead::getView))
    ;
  pybind11::class_<org::imm::ImmCmdColumnsValue>(m, "immImmCmdColumnsValue")
    .def("setView",
         static_cast<void(org::imm::ImmCmdColumnsValue::*)(org::sem::ColumnView const&)>(&org::imm::ImmCmdColumnsValue::setView),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmCmdNameValueRead>(m, "immImmCmdNameValueRead")
    .def("getName", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmCmdNameValueRead::*)() const>(&org::imm::ImmCmdNameValueRead::getName))
    ;
  pybind11::class_<org::imm::ImmCmdNameValue>(m, "immImmCmdNameValue")
    .def("setName",
         static_cast<void(org::imm::ImmCmdNameValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmCmdNameValue::setName),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmCmdCustomArgsValueRead>(m, "immImmCmdCustomArgsValueRead")
    .def("getName", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmCmdCustomArgsValueRead::*)() const>(&org::imm::ImmCmdCustomArgsValueRead::getName))
    .def("getIsattached", static_cast<bool const&(org::imm::ImmCmdCustomArgsValueRead::*)() const>(&org::imm::ImmCmdCustomArgsValueRead::getIsattached))
    ;
  pybind11::class_<org::imm::ImmCmdCustomArgsValue>(m, "immImmCmdCustomArgsValue")
    .def("setName",
         static_cast<void(org::imm::ImmCmdCustomArgsValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmCmdCustomArgsValue::setName),
         pybind11::arg("value"))
    .def("setIsattached",
         static_cast<void(org::imm::ImmCmdCustomArgsValue::*)(bool const&)>(&org::imm::ImmCmdCustomArgsValue::setIsattached),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmCmdCustomRawValueRead>(m, "immImmCmdCustomRawValueRead")
    .def("getName", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmCmdCustomRawValueRead::*)() const>(&org::imm::ImmCmdCustomRawValueRead::getName))
    .def("getIsattached", static_cast<bool const&(org::imm::ImmCmdCustomRawValueRead::*)() const>(&org::imm::ImmCmdCustomRawValueRead::getIsattached))
    .def("getText", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmCmdCustomRawValueRead::*)() const>(&org::imm::ImmCmdCustomRawValueRead::getText))
    ;
  pybind11::class_<org::imm::ImmCmdCustomRawValue>(m, "immImmCmdCustomRawValue")
    .def("setName",
         static_cast<void(org::imm::ImmCmdCustomRawValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmCmdCustomRawValue::setName),
         pybind11::arg("value"))
    .def("setIsattached",
         static_cast<void(org::imm::ImmCmdCustomRawValue::*)(bool const&)>(&org::imm::ImmCmdCustomRawValue::setIsattached),
         pybind11::arg("value"))
    .def("setText",
         static_cast<void(org::imm::ImmCmdCustomRawValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmCmdCustomRawValue::setText),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmCmdCustomTextValueRead>(m, "immImmCmdCustomTextValueRead")
    .def("getName", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmCmdCustomTextValueRead::*)() const>(&org::imm::ImmCmdCustomTextValueRead::getName))
    .def("getIsattached", static_cast<bool const&(org::imm::ImmCmdCustomTextValueRead::*)() const>(&org::imm::ImmCmdCustomTextValueRead::getIsattached))
    .def("getText", static_cast<org::imm::ImmIdT<org::imm::ImmParagraph> const&(org::imm::ImmCmdCustomTextValueRead::*)() const>(&org::imm::ImmCmdCustomTextValueRead::getText))
    ;
  pybind11::class_<org::imm::ImmCmdCustomTextValue>(m, "immImmCmdCustomTextValue")
    .def("setName",
         static_cast<void(org::imm::ImmCmdCustomTextValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmCmdCustomTextValue::setName),
         pybind11::arg("value"))
    .def("setIsattached",
         static_cast<void(org::imm::ImmCmdCustomTextValue::*)(bool const&)>(&org::imm::ImmCmdCustomTextValue::setIsattached),
         pybind11::arg("value"))
    .def("setText",
         static_cast<void(org::imm::ImmCmdCustomTextValue::*)(org::imm::ImmIdT<org::imm::ImmParagraph> const&)>(&org::imm::ImmCmdCustomTextValue::setText),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmCmdCallValueRead>(m, "immImmCmdCallValueRead")
    .def("getName", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getName))
    .def("getFilename", static_cast<immer::ext::ext::box<std::optional<hstd::Str>> const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getFilename))
    .def("getInsideheaderattrs", static_cast<org::sem::AttrGroup const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getInsideheaderattrs))
    .def("getCallattrs", static_cast<org::sem::AttrGroup const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getCallattrs))
    .def("getEndheaderattrs", static_cast<org::sem::AttrGroup const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getEndheaderattrs))
    .def("getResult", static_cast<immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const&(org::imm::ImmCmdCallValueRead::*)() const>(&org::imm::ImmCmdCallValueRead::getResult))
    ;
  pybind11::class_<org::imm::ImmCmdCallValue>(m, "immImmCmdCallValue")
    .def("setName",
         static_cast<void(org::imm::ImmCmdCallValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmCmdCallValue::setName),
         pybind11::arg("value"))
    .def("setFilename",
         static_cast<void(org::imm::ImmCmdCallValue::*)(immer::ext::ext::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmCmdCallValue::setFilename),
         pybind11::arg("value"))
    .def("setInsideheaderattrs",
         static_cast<void(org::imm::ImmCmdCallValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmCmdCallValue::setInsideheaderattrs),
         pybind11::arg("value"))
    .def("setCallattrs",
         static_cast<void(org::imm::ImmCmdCallValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmCmdCallValue::setCallattrs),
         pybind11::arg("value"))
    .def("setEndheaderattrs",
         static_cast<void(org::imm::ImmCmdCallValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmCmdCallValue::setEndheaderattrs),
         pybind11::arg("value"))
    .def("setResult",
         static_cast<void(org::imm::ImmCmdCallValue::*)(immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const&)>(&org::imm::ImmCmdCallValue::setResult),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmCmdTblfmValueRead>(m, "immImmCmdTblfmValueRead")
    .def("getExpr", static_cast<org::sem::Tblfm const&(org::imm::ImmCmdTblfmValueRead::*)() const>(&org::imm::ImmCmdTblfmValueRead::getExpr))
    ;
  pybind11::class_<org::imm::ImmCmdTblfmValue>(m, "immImmCmdTblfmValue")
    .def("setExpr",
         static_cast<void(org::imm::ImmCmdTblfmValue::*)(org::sem::Tblfm const&)>(&org::imm::ImmCmdTblfmValue::setExpr),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmHashTagValueRead>(m, "immImmHashTagValueRead")
    .def("getText", static_cast<org::sem::HashTagText const&(org::imm::ImmHashTagValueRead::*)() const>(&org::imm::ImmHashTagValueRead::getText))
    ;
  pybind11::class_<org::imm::ImmHashTagValue>(m, "immImmHashTagValue")
    .def("setText",
         static_cast<void(org::imm::ImmHashTagValue::*)(org::sem::HashTagText const&)>(&org::imm::ImmHashTagValue::setText),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmInlineFootnoteValueRead>(m, "immImmInlineFootnoteValueRead")
    .def("getTag", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmInlineFootnoteValueRead::*)() const>(&org::imm::ImmInlineFootnoteValueRead::getTag))
    .def("getDefinition", static_cast<immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmOrg>>> const&(org::imm::ImmInlineFootnoteValueRead::*)() const>(&org::imm::ImmInlineFootnoteValueRead::getDefinition))
    ;
  pybind11::class_<org::imm::ImmInlineFootnoteValue>(m, "immImmInlineFootnoteValue")
    .def("setTag",
         static_cast<void(org::imm::ImmInlineFootnoteValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmInlineFootnoteValue::setTag),
         pybind11::arg("value"))
    .def("setDefinition",
         static_cast<void(org::imm::ImmInlineFootnoteValue::*)(immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmOrg>>> const&)>(&org::imm::ImmInlineFootnoteValue::setDefinition),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmInlineExportValueRead>(m, "immImmInlineExportValueRead")
    .def("getExporter", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmInlineExportValueRead::*)() const>(&org::imm::ImmInlineExportValueRead::getExporter))
    .def("getContent", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmInlineExportValueRead::*)() const>(&org::imm::ImmInlineExportValueRead::getContent))
    ;
  pybind11::class_<org::imm::ImmInlineExportValue>(m, "immImmInlineExportValue")
    .def("setExporter",
         static_cast<void(org::imm::ImmInlineExportValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmInlineExportValue::setExporter),
         pybind11::arg("value"))
    .def("setContent",
         static_cast<void(org::imm::ImmInlineExportValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmInlineExportValue::setContent),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmTimeValueRead>(m, "immImmTimeValueRead")
    .def("getIsactive", static_cast<bool const&(org::imm::ImmTimeValueRead::*)() const>(&org::imm::ImmTimeValueRead::getIsactive))
    .def("getTime", static_cast<org::imm::ImmTime::TimeVariant const&(org::imm::ImmTimeValueRead::*)() const>(&org::imm::ImmTimeValueRead::getTime))
    ;
  pybind11::class_<org::imm::ImmTimeValue>(m, "immImmTimeValue")
    .def("setIsactive",
         static_cast<void(org::imm::ImmTimeValue::*)(bool const&)>(&org::imm::ImmTimeValue::setIsactive),
         pybind11::arg("value"))
    .def("setTime",
         static_cast<void(org::imm::ImmTimeValue::*)(org::imm::ImmTime::TimeVariant const&)>(&org::imm::ImmTimeValue::setTime),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmTimeRangeValueRead>(m, "immImmTimeRangeValueRead")
    .def("getFrom", static_cast<org::imm::ImmIdT<org::imm::ImmTime> const&(org::imm::ImmTimeRangeValueRead::*)() const>(&org::imm::ImmTimeRangeValueRead::getFrom))
    .def("getTo", static_cast<org::imm::ImmIdT<org::imm::ImmTime> const&(org::imm::ImmTimeRangeValueRead::*)() const>(&org::imm::ImmTimeRangeValueRead::getTo))
    ;
  pybind11::class_<org::imm::ImmTimeRangeValue>(m, "immImmTimeRangeValue")
    .def("setFrom",
         static_cast<void(org::imm::ImmTimeRangeValue::*)(org::imm::ImmIdT<org::imm::ImmTime> const&)>(&org::imm::ImmTimeRangeValue::setFrom),
         pybind11::arg("value"))
    .def("setTo",
         static_cast<void(org::imm::ImmTimeRangeValue::*)(org::imm::ImmIdT<org::imm::ImmTime> const&)>(&org::imm::ImmTimeRangeValue::setTo),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmMacroValueRead>(m, "immImmMacroValueRead")
    .def("getName", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmMacroValueRead::*)() const>(&org::imm::ImmMacroValueRead::getName))
    .def("getAttrs", static_cast<org::sem::AttrGroup const&(org::imm::ImmMacroValueRead::*)() const>(&org::imm::ImmMacroValueRead::getAttrs))
    ;
  pybind11::class_<org::imm::ImmMacroValue>(m, "immImmMacroValue")
    .def("setName",
         static_cast<void(org::imm::ImmMacroValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmMacroValue::setName),
         pybind11::arg("value"))
    .def("setAttrs",
         static_cast<void(org::imm::ImmMacroValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmMacroValue::setAttrs),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmSymbolValueRead>(m, "immImmSymbolValueRead")
    .def("getName", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmSymbolValueRead::*)() const>(&org::imm::ImmSymbolValueRead::getName))
    .def("getParameters", static_cast<immer::ext::ext::flex_vector<org::imm::ImmSymbol::imm::ImmSymbol::imm::ImmSymbol::Param> const&(org::imm::ImmSymbolValueRead::*)() const>(&org::imm::ImmSymbolValueRead::getParameters))
    .def("getPositional", static_cast<immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmOrg>> const&(org::imm::ImmSymbolValueRead::*)() const>(&org::imm::ImmSymbolValueRead::getPositional))
    ;
  pybind11::class_<org::imm::ImmSymbolValue>(m, "immImmSymbolValue")
    .def("setName",
         static_cast<void(org::imm::ImmSymbolValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmSymbolValue::setName),
         pybind11::arg("value"))
    .def("setParameters",
         static_cast<void(org::imm::ImmSymbolValue::*)(immer::ext::ext::flex_vector<org::imm::ImmSymbol::imm::ImmSymbol::imm::ImmSymbol::Param> const&)>(&org::imm::ImmSymbolValue::setParameters),
         pybind11::arg("value"))
    .def("setPositional",
         static_cast<void(org::imm::ImmSymbolValue::*)(immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmOrg>> const&)>(&org::imm::ImmSymbolValue::setPositional),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmEscapedValueRead>(m, "immImmEscapedValueRead")
    ;
  pybind11::class_<org::imm::ImmEscapedValue>(m, "immImmEscapedValue")
    ;
  pybind11::class_<org::imm::ImmNewlineValueRead>(m, "immImmNewlineValueRead")
    ;
  pybind11::class_<org::imm::ImmNewlineValue>(m, "immImmNewlineValue")
    ;
  pybind11::class_<org::imm::ImmSpaceValueRead>(m, "immImmSpaceValueRead")
    ;
  pybind11::class_<org::imm::ImmSpaceValue>(m, "immImmSpaceValue")
    ;
  pybind11::class_<org::imm::ImmWordValueRead>(m, "immImmWordValueRead")
    ;
  pybind11::class_<org::imm::ImmWordValue>(m, "immImmWordValue")
    ;
  pybind11::class_<org::imm::ImmAtMentionValueRead>(m, "immImmAtMentionValueRead")
    ;
  pybind11::class_<org::imm::ImmAtMentionValue>(m, "immImmAtMentionValue")
    ;
  pybind11::class_<org::imm::ImmRawTextValueRead>(m, "immImmRawTextValueRead")
    ;
  pybind11::class_<org::imm::ImmRawTextValue>(m, "immImmRawTextValue")
    ;
  pybind11::class_<org::imm::ImmPunctuationValueRead>(m, "immImmPunctuationValueRead")
    ;
  pybind11::class_<org::imm::ImmPunctuationValue>(m, "immImmPunctuationValue")
    ;
  pybind11::class_<org::imm::ImmPlaceholderValueRead>(m, "immImmPlaceholderValueRead")
    ;
  pybind11::class_<org::imm::ImmPlaceholderValue>(m, "immImmPlaceholderValue")
    ;
  pybind11::class_<org::imm::ImmBigIdentValueRead>(m, "immImmBigIdentValueRead")
    ;
  pybind11::class_<org::imm::ImmBigIdentValue>(m, "immImmBigIdentValue")
    ;
  pybind11::class_<org::imm::ImmTextTargetValueRead>(m, "immImmTextTargetValueRead")
    ;
  pybind11::class_<org::imm::ImmTextTargetValue>(m, "immImmTextTargetValue")
    ;
  pybind11::class_<org::imm::ImmBoldValueRead>(m, "immImmBoldValueRead")
    ;
  pybind11::class_<org::imm::ImmBoldValue>(m, "immImmBoldValue")
    ;
  pybind11::class_<org::imm::ImmUnderlineValueRead>(m, "immImmUnderlineValueRead")
    ;
  pybind11::class_<org::imm::ImmUnderlineValue>(m, "immImmUnderlineValue")
    ;
  pybind11::class_<org::imm::ImmMonospaceValueRead>(m, "immImmMonospaceValueRead")
    ;
  pybind11::class_<org::imm::ImmMonospaceValue>(m, "immImmMonospaceValue")
    ;
  pybind11::class_<org::imm::ImmMarkQuoteValueRead>(m, "immImmMarkQuoteValueRead")
    ;
  pybind11::class_<org::imm::ImmMarkQuoteValue>(m, "immImmMarkQuoteValue")
    ;
  pybind11::class_<org::imm::ImmVerbatimValueRead>(m, "immImmVerbatimValueRead")
    ;
  pybind11::class_<org::imm::ImmVerbatimValue>(m, "immImmVerbatimValue")
    ;
  pybind11::class_<org::imm::ImmItalicValueRead>(m, "immImmItalicValueRead")
    ;
  pybind11::class_<org::imm::ImmItalicValue>(m, "immImmItalicValue")
    ;
  pybind11::class_<org::imm::ImmStrikeValueRead>(m, "immImmStrikeValueRead")
    ;
  pybind11::class_<org::imm::ImmStrikeValue>(m, "immImmStrikeValue")
    ;
  pybind11::class_<org::imm::ImmParValueRead>(m, "immImmParValueRead")
    ;
  pybind11::class_<org::imm::ImmParValue>(m, "immImmParValue")
    ;
  pybind11::class_<org::imm::ImmRadioTargetValueRead>(m, "immImmRadioTargetValueRead")
    .def("getWords", static_cast<immer::ext::ext::flex_vector<hstd::Str> const&(org::imm::ImmRadioTargetValueRead::*)() const>(&org::imm::ImmRadioTargetValueRead::getWords))
    ;
  pybind11::class_<org::imm::ImmRadioTargetValue>(m, "immImmRadioTargetValue")
    .def("setWords",
         static_cast<void(org::imm::ImmRadioTargetValue::*)(immer::ext::ext::flex_vector<hstd::Str> const&)>(&org::imm::ImmRadioTargetValue::setWords),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmLatexValueRead>(m, "immImmLatexValueRead")
    ;
  pybind11::class_<org::imm::ImmLatexValue>(m, "immImmLatexValue")
    ;
  pybind11::class_<org::imm::ImmLinkValueRead>(m, "immImmLinkValueRead")
    .def("getDescription", static_cast<immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmLinkValueRead::*)() const>(&org::imm::ImmLinkValueRead::getDescription))
    .def("getTarget", static_cast<org::sem::LinkTarget const&(org::imm::ImmLinkValueRead::*)() const>(&org::imm::ImmLinkValueRead::getTarget))
    ;
  pybind11::class_<org::imm::ImmLinkValue>(m, "immImmLinkValue")
    .def("setDescription",
         static_cast<void(org::imm::ImmLinkValue::*)(immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmLinkValue::setDescription),
         pybind11::arg("value"))
    .def("setTarget",
         static_cast<void(org::imm::ImmLinkValue::*)(org::sem::LinkTarget const&)>(&org::imm::ImmLinkValue::setTarget),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmBlockCenterValueRead>(m, "immImmBlockCenterValueRead")
    ;
  pybind11::class_<org::imm::ImmBlockCenterValue>(m, "immImmBlockCenterValue")
    ;
  pybind11::class_<org::imm::ImmBlockQuoteValueRead>(m, "immImmBlockQuoteValueRead")
    ;
  pybind11::class_<org::imm::ImmBlockQuoteValue>(m, "immImmBlockQuoteValue")
    ;
  pybind11::class_<org::imm::ImmBlockCommentValueRead>(m, "immImmBlockCommentValueRead")
    ;
  pybind11::class_<org::imm::ImmBlockCommentValue>(m, "immImmBlockCommentValue")
    ;
  pybind11::class_<org::imm::ImmBlockVerseValueRead>(m, "immImmBlockVerseValueRead")
    ;
  pybind11::class_<org::imm::ImmBlockVerseValue>(m, "immImmBlockVerseValue")
    ;
  pybind11::class_<org::imm::ImmBlockDynamicFallbackValueRead>(m, "immImmBlockDynamicFallbackValueRead")
    .def("getName", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmBlockDynamicFallbackValueRead::*)() const>(&org::imm::ImmBlockDynamicFallbackValueRead::getName))
    ;
  pybind11::class_<org::imm::ImmBlockDynamicFallbackValue>(m, "immImmBlockDynamicFallbackValue")
    .def("setName",
         static_cast<void(org::imm::ImmBlockDynamicFallbackValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmBlockDynamicFallbackValue::setName),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmBlockExampleValueRead>(m, "immImmBlockExampleValueRead")
    ;
  pybind11::class_<org::imm::ImmBlockExampleValue>(m, "immImmBlockExampleValue")
    ;
  pybind11::class_<org::imm::ImmBlockExportValueRead>(m, "immImmBlockExportValueRead")
    .def("getExporter", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmBlockExportValueRead::*)() const>(&org::imm::ImmBlockExportValueRead::getExporter))
    .def("getContent", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmBlockExportValueRead::*)() const>(&org::imm::ImmBlockExportValueRead::getContent))
    ;
  pybind11::class_<org::imm::ImmBlockExportValue>(m, "immImmBlockExportValue")
    .def("setExporter",
         static_cast<void(org::imm::ImmBlockExportValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmBlockExportValue::setExporter),
         pybind11::arg("value"))
    .def("setContent",
         static_cast<void(org::imm::ImmBlockExportValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmBlockExportValue::setContent),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmBlockAdmonitionValueRead>(m, "immImmBlockAdmonitionValueRead")
    ;
  pybind11::class_<org::imm::ImmBlockAdmonitionValue>(m, "immImmBlockAdmonitionValue")
    ;
  pybind11::class_<org::imm::ImmBlockCodeEvalResultValueRead>(m, "immImmBlockCodeEvalResultValueRead")
    .def("getRaw", static_cast<immer::ext::ext::flex_vector<org::sem::OrgCodeEvalOutput> const&(org::imm::ImmBlockCodeEvalResultValueRead::*)() const>(&org::imm::ImmBlockCodeEvalResultValueRead::getRaw))
    .def("getNode", static_cast<org::imm::ImmIdT<org::imm::ImmOrg> const&(org::imm::ImmBlockCodeEvalResultValueRead::*)() const>(&org::imm::ImmBlockCodeEvalResultValueRead::getNode))
    ;
  pybind11::class_<org::imm::ImmBlockCodeEvalResultValue>(m, "immImmBlockCodeEvalResultValue")
    .def("setRaw",
         static_cast<void(org::imm::ImmBlockCodeEvalResultValue::*)(immer::ext::ext::flex_vector<org::sem::OrgCodeEvalOutput> const&)>(&org::imm::ImmBlockCodeEvalResultValue::setRaw),
         pybind11::arg("value"))
    .def("setNode",
         static_cast<void(org::imm::ImmBlockCodeEvalResultValue::*)(org::imm::ImmIdT<org::imm::ImmOrg> const&)>(&org::imm::ImmBlockCodeEvalResultValue::setNode),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmBlockCodeValueRead>(m, "immImmBlockCodeValueRead")
    .def("getLang", static_cast<immer::ext::ext::box<std::optional<hstd::Str>> const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getLang))
    .def("getExports", static_cast<BlockCodeExports const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getExports))
    .def("getResult", static_cast<immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getResult))
    .def("getLines", static_cast<immer::ext::ext::flex_vector<org::sem::BlockCodeLine> const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getLines))
    .def("getCache", static_cast<bool const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getCache))
    .def("getEval", static_cast<bool const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getEval))
    .def("getNoweb", static_cast<bool const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getNoweb))
    .def("getHlines", static_cast<bool const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getHlines))
    .def("getTangle", static_cast<bool const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getTangle))
    .def("getSwitches", static_cast<org::sem::AttrGroup const&(org::imm::ImmBlockCodeValueRead::*)() const>(&org::imm::ImmBlockCodeValueRead::getSwitches))
    ;
  pybind11::class_<org::imm::ImmBlockCodeValue>(m, "immImmBlockCodeValue")
    .def("setLang",
         static_cast<void(org::imm::ImmBlockCodeValue::*)(immer::ext::ext::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmBlockCodeValue::setLang),
         pybind11::arg("value"))
    .def("setExports",
         static_cast<void(org::imm::ImmBlockCodeValue::*)(BlockCodeExports const&)>(&org::imm::ImmBlockCodeValue::setExports),
         pybind11::arg("value"))
    .def("setResult",
         static_cast<void(org::imm::ImmBlockCodeValue::*)(immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const&)>(&org::imm::ImmBlockCodeValue::setResult),
         pybind11::arg("value"))
    .def("setLines",
         static_cast<void(org::imm::ImmBlockCodeValue::*)(immer::ext::ext::flex_vector<org::sem::BlockCodeLine> const&)>(&org::imm::ImmBlockCodeValue::setLines),
         pybind11::arg("value"))
    .def("setCache",
         static_cast<void(org::imm::ImmBlockCodeValue::*)(bool const&)>(&org::imm::ImmBlockCodeValue::setCache),
         pybind11::arg("value"))
    .def("setEval",
         static_cast<void(org::imm::ImmBlockCodeValue::*)(bool const&)>(&org::imm::ImmBlockCodeValue::setEval),
         pybind11::arg("value"))
    .def("setNoweb",
         static_cast<void(org::imm::ImmBlockCodeValue::*)(bool const&)>(&org::imm::ImmBlockCodeValue::setNoweb),
         pybind11::arg("value"))
    .def("setHlines",
         static_cast<void(org::imm::ImmBlockCodeValue::*)(bool const&)>(&org::imm::ImmBlockCodeValue::setHlines),
         pybind11::arg("value"))
    .def("setTangle",
         static_cast<void(org::imm::ImmBlockCodeValue::*)(bool const&)>(&org::imm::ImmBlockCodeValue::setTangle),
         pybind11::arg("value"))
    .def("setSwitches",
         static_cast<void(org::imm::ImmBlockCodeValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmBlockCodeValue::setSwitches),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmSubtreeLogValueRead>(m, "immImmSubtreeLogValueRead")
    .def("getHead", static_cast<org::sem::SubtreeLogHead const&(org::imm::ImmSubtreeLogValueRead::*)() const>(&org::imm::ImmSubtreeLogValueRead::getHead))
    .def("getDesc", static_cast<immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmStmtList>>> const&(org::imm::ImmSubtreeLogValueRead::*)() const>(&org::imm::ImmSubtreeLogValueRead::getDesc))
    ;
  pybind11::class_<org::imm::ImmSubtreeLogValue>(m, "immImmSubtreeLogValue")
    .def("setHead",
         static_cast<void(org::imm::ImmSubtreeLogValue::*)(org::sem::SubtreeLogHead const&)>(&org::imm::ImmSubtreeLogValue::setHead),
         pybind11::arg("value"))
    .def("setDesc",
         static_cast<void(org::imm::ImmSubtreeLogValue::*)(immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmStmtList>>> const&)>(&org::imm::ImmSubtreeLogValue::setDesc),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmSubtreeValueRead>(m, "immImmSubtreeValueRead")
    .def("getLevel", static_cast<int const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getLevel))
    .def("getTreeid", static_cast<immer::ext::ext::box<std::optional<hstd::Str>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getTreeid))
    .def("getTodo", static_cast<immer::ext::ext::box<std::optional<hstd::Str>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getTodo))
    .def("getCompletion", static_cast<immer::ext::ext::box<std::optional<org::sem::SubtreeCompletion>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getCompletion))
    .def("getDescription", static_cast<immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getDescription))
    .def("getTags", static_cast<immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmHashTag>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getTags))
    .def("getTitle", static_cast<org::imm::ImmIdT<org::imm::ImmParagraph> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getTitle))
    .def("getLogbook", static_cast<immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmSubtreeLog>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getLogbook))
    .def("getProperties", static_cast<immer::ext::ext::flex_vector<org::sem::NamedProperty> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getProperties))
    .def("getClosed", static_cast<immer::ext::ext::box<std::optional<hstd::UserTime>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getClosed))
    .def("getDeadline", static_cast<immer::ext::ext::box<std::optional<hstd::UserTime>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getDeadline))
    .def("getScheduled", static_cast<immer::ext::ext::box<std::optional<hstd::UserTime>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getScheduled))
    .def("getIscomment", static_cast<bool const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getIscomment))
    .def("getIsarchived", static_cast<bool const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getIsarchived))
    .def("getPriority", static_cast<immer::ext::ext::box<std::optional<hstd::Str>> const&(org::imm::ImmSubtreeValueRead::*)() const>(&org::imm::ImmSubtreeValueRead::getPriority))
    ;
  pybind11::class_<org::imm::ImmSubtreeValue>(m, "immImmSubtreeValue")
    .def("setLevel",
         static_cast<void(org::imm::ImmSubtreeValue::*)(int const&)>(&org::imm::ImmSubtreeValue::setLevel),
         pybind11::arg("value"))
    .def("setTreeid",
         static_cast<void(org::imm::ImmSubtreeValue::*)(immer::ext::ext::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmSubtreeValue::setTreeid),
         pybind11::arg("value"))
    .def("setTodo",
         static_cast<void(org::imm::ImmSubtreeValue::*)(immer::ext::ext::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmSubtreeValue::setTodo),
         pybind11::arg("value"))
    .def("setCompletion",
         static_cast<void(org::imm::ImmSubtreeValue::*)(immer::ext::ext::box<std::optional<org::sem::SubtreeCompletion>> const&)>(&org::imm::ImmSubtreeValue::setCompletion),
         pybind11::arg("value"))
    .def("setDescription",
         static_cast<void(org::imm::ImmSubtreeValue::*)(immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmSubtreeValue::setDescription),
         pybind11::arg("value"))
    .def("setTags",
         static_cast<void(org::imm::ImmSubtreeValue::*)(immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmHashTag>> const&)>(&org::imm::ImmSubtreeValue::setTags),
         pybind11::arg("value"))
    .def("setTitle",
         static_cast<void(org::imm::ImmSubtreeValue::*)(org::imm::ImmIdT<org::imm::ImmParagraph> const&)>(&org::imm::ImmSubtreeValue::setTitle),
         pybind11::arg("value"))
    .def("setLogbook",
         static_cast<void(org::imm::ImmSubtreeValue::*)(immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmSubtreeLog>> const&)>(&org::imm::ImmSubtreeValue::setLogbook),
         pybind11::arg("value"))
    .def("setProperties",
         static_cast<void(org::imm::ImmSubtreeValue::*)(immer::ext::ext::flex_vector<org::sem::NamedProperty> const&)>(&org::imm::ImmSubtreeValue::setProperties),
         pybind11::arg("value"))
    .def("setClosed",
         static_cast<void(org::imm::ImmSubtreeValue::*)(immer::ext::ext::box<std::optional<hstd::UserTime>> const&)>(&org::imm::ImmSubtreeValue::setClosed),
         pybind11::arg("value"))
    .def("setDeadline",
         static_cast<void(org::imm::ImmSubtreeValue::*)(immer::ext::ext::box<std::optional<hstd::UserTime>> const&)>(&org::imm::ImmSubtreeValue::setDeadline),
         pybind11::arg("value"))
    .def("setScheduled",
         static_cast<void(org::imm::ImmSubtreeValue::*)(immer::ext::ext::box<std::optional<hstd::UserTime>> const&)>(&org::imm::ImmSubtreeValue::setScheduled),
         pybind11::arg("value"))
    .def("setIscomment",
         static_cast<void(org::imm::ImmSubtreeValue::*)(bool const&)>(&org::imm::ImmSubtreeValue::setIscomment),
         pybind11::arg("value"))
    .def("setIsarchived",
         static_cast<void(org::imm::ImmSubtreeValue::*)(bool const&)>(&org::imm::ImmSubtreeValue::setIsarchived),
         pybind11::arg("value"))
    .def("setPriority",
         static_cast<void(org::imm::ImmSubtreeValue::*)(immer::ext::ext::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmSubtreeValue::setPriority),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmCellValueRead>(m, "immImmCellValueRead")
    .def("getIsblock", static_cast<bool const&(org::imm::ImmCellValueRead::*)() const>(&org::imm::ImmCellValueRead::getIsblock))
    ;
  pybind11::class_<org::imm::ImmCellValue>(m, "immImmCellValue")
    .def("setIsblock",
         static_cast<void(org::imm::ImmCellValue::*)(bool const&)>(&org::imm::ImmCellValue::setIsblock),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmRowValueRead>(m, "immImmRowValueRead")
    .def("getCells", static_cast<immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmCell>> const&(org::imm::ImmRowValueRead::*)() const>(&org::imm::ImmRowValueRead::getCells))
    .def("getIsblock", static_cast<bool const&(org::imm::ImmRowValueRead::*)() const>(&org::imm::ImmRowValueRead::getIsblock))
    ;
  pybind11::class_<org::imm::ImmRowValue>(m, "immImmRowValue")
    .def("setCells",
         static_cast<void(org::imm::ImmRowValue::*)(immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmCell>> const&)>(&org::imm::ImmRowValue::setCells),
         pybind11::arg("value"))
    .def("setIsblock",
         static_cast<void(org::imm::ImmRowValue::*)(bool const&)>(&org::imm::ImmRowValue::setIsblock),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmTableValueRead>(m, "immImmTableValueRead")
    .def("getRows", static_cast<immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmRow>> const&(org::imm::ImmTableValueRead::*)() const>(&org::imm::ImmTableValueRead::getRows))
    .def("getIsblock", static_cast<bool const&(org::imm::ImmTableValueRead::*)() const>(&org::imm::ImmTableValueRead::getIsblock))
    ;
  pybind11::class_<org::imm::ImmTableValue>(m, "immImmTableValue")
    .def("setRows",
         static_cast<void(org::imm::ImmTableValue::*)(immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmRow>> const&)>(&org::imm::ImmTableValue::setRows),
         pybind11::arg("value"))
    .def("setIsblock",
         static_cast<void(org::imm::ImmTableValue::*)(bool const&)>(&org::imm::ImmTableValue::setIsblock),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmParagraphValueRead>(m, "immImmParagraphValueRead")
    ;
  pybind11::class_<org::imm::ImmParagraphValue>(m, "immImmParagraphValue")
    ;
  pybind11::class_<org::imm::ImmColonExampleValueRead>(m, "immImmColonExampleValueRead")
    ;
  pybind11::class_<org::imm::ImmColonExampleValue>(m, "immImmColonExampleValue")
    ;
  pybind11::class_<org::imm::ImmCmdAttrValueRead>(m, "immImmCmdAttrValueRead")
    .def("getTarget", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmCmdAttrValueRead::*)() const>(&org::imm::ImmCmdAttrValueRead::getTarget))
    ;
  pybind11::class_<org::imm::ImmCmdAttrValue>(m, "immImmCmdAttrValue")
    .def("setTarget",
         static_cast<void(org::imm::ImmCmdAttrValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmCmdAttrValue::setTarget),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmCmdExportValueRead>(m, "immImmCmdExportValueRead")
    .def("getExporter", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmCmdExportValueRead::*)() const>(&org::imm::ImmCmdExportValueRead::getExporter))
    .def("getContent", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmCmdExportValueRead::*)() const>(&org::imm::ImmCmdExportValueRead::getContent))
    ;
  pybind11::class_<org::imm::ImmCmdExportValue>(m, "immImmCmdExportValue")
    .def("setExporter",
         static_cast<void(org::imm::ImmCmdExportValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmCmdExportValue::setExporter),
         pybind11::arg("value"))
    .def("setContent",
         static_cast<void(org::imm::ImmCmdExportValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmCmdExportValue::setContent),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmCallValueRead>(m, "immImmCallValueRead")
    .def("getName", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmCallValueRead::*)() const>(&org::imm::ImmCallValueRead::getName))
    .def("getAttrs", static_cast<org::sem::AttrGroup const&(org::imm::ImmCallValueRead::*)() const>(&org::imm::ImmCallValueRead::getAttrs))
    .def("getIscommand", static_cast<bool const&(org::imm::ImmCallValueRead::*)() const>(&org::imm::ImmCallValueRead::getIscommand))
    ;
  pybind11::class_<org::imm::ImmCallValue>(m, "immImmCallValue")
    .def("setName",
         static_cast<void(org::imm::ImmCallValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmCallValue::setName),
         pybind11::arg("value"))
    .def("setAttrs",
         static_cast<void(org::imm::ImmCallValue::*)(org::sem::AttrGroup const&)>(&org::imm::ImmCallValue::setAttrs),
         pybind11::arg("value"))
    .def("setIscommand",
         static_cast<void(org::imm::ImmCallValue::*)(bool const&)>(&org::imm::ImmCallValue::setIscommand),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmListValueRead>(m, "immImmListValueRead")
    ;
  pybind11::class_<org::imm::ImmListValue>(m, "immImmListValue")
    ;
  pybind11::class_<org::imm::ImmListItemValueRead>(m, "immImmListItemValueRead")
    .def("getCheckbox", static_cast<org::imm::org::imm::ImmListItem::Checkbox const&(org::imm::ImmListItemValueRead::*)() const>(&org::imm::ImmListItemValueRead::getCheckbox))
    .def("getHeader", static_cast<immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmListItemValueRead::*)() const>(&org::imm::ImmListItemValueRead::getHeader))
    .def("getBullet", static_cast<immer::ext::ext::box<std::optional<hstd::Str>> const&(org::imm::ImmListItemValueRead::*)() const>(&org::imm::ImmListItemValueRead::getBullet))
    ;
  pybind11::class_<org::imm::ImmListItemValue>(m, "immImmListItemValue")
    .def("setCheckbox",
         static_cast<void(org::imm::ImmListItemValue::*)(org::imm::org::imm::ImmListItem::Checkbox const&)>(&org::imm::ImmListItemValue::setCheckbox),
         pybind11::arg("value"))
    .def("setHeader",
         static_cast<void(org::imm::ImmListItemValue::*)(immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmListItemValue::setHeader),
         pybind11::arg("value"))
    .def("setBullet",
         static_cast<void(org::imm::ImmListItemValue::*)(immer::ext::ext::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmListItemValue::setBullet),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmDocumentOptionsValueRead>(m, "immImmDocumentOptionsValueRead")
    .def("getInitialvisibility", static_cast<InitialSubtreeVisibility const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getInitialvisibility))
    .def("getProperties", static_cast<immer::ext::ext::flex_vector<org::sem::NamedProperty> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getProperties))
    .def("getExportconfig", static_cast<org::sem::DocumentExportConfig const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getExportconfig))
    .def("getFixedwidthsections", static_cast<immer::ext::ext::box<std::optional<bool>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getFixedwidthsections))
    .def("getStartupindented", static_cast<immer::ext::ext::box<std::optional<bool>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getStartupindented))
    .def("getCategory", static_cast<immer::ext::ext::box<std::optional<hstd::Str>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getCategory))
    .def("getSetupfile", static_cast<immer::ext::ext::box<std::optional<hstd::Str>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getSetupfile))
    .def("getMaxsubtreelevelexport", static_cast<immer::ext::ext::box<std::optional<int>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getMaxsubtreelevelexport))
    .def("getColumns", static_cast<immer::ext::ext::box<std::optional<org::sem::ColumnView>> const&(org::imm::ImmDocumentOptionsValueRead::*)() const>(&org::imm::ImmDocumentOptionsValueRead::getColumns))
    ;
  pybind11::class_<org::imm::ImmDocumentOptionsValue>(m, "immImmDocumentOptionsValue")
    .def("setInitialvisibility",
         static_cast<void(org::imm::ImmDocumentOptionsValue::*)(InitialSubtreeVisibility const&)>(&org::imm::ImmDocumentOptionsValue::setInitialvisibility),
         pybind11::arg("value"))
    .def("setProperties",
         static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::ext::ext::flex_vector<org::sem::NamedProperty> const&)>(&org::imm::ImmDocumentOptionsValue::setProperties),
         pybind11::arg("value"))
    .def("setExportconfig",
         static_cast<void(org::imm::ImmDocumentOptionsValue::*)(org::sem::DocumentExportConfig const&)>(&org::imm::ImmDocumentOptionsValue::setExportconfig),
         pybind11::arg("value"))
    .def("setFixedwidthsections",
         static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::ext::ext::box<std::optional<bool>> const&)>(&org::imm::ImmDocumentOptionsValue::setFixedwidthsections),
         pybind11::arg("value"))
    .def("setStartupindented",
         static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::ext::ext::box<std::optional<bool>> const&)>(&org::imm::ImmDocumentOptionsValue::setStartupindented),
         pybind11::arg("value"))
    .def("setCategory",
         static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::ext::ext::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmDocumentOptionsValue::setCategory),
         pybind11::arg("value"))
    .def("setSetupfile",
         static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::ext::ext::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmDocumentOptionsValue::setSetupfile),
         pybind11::arg("value"))
    .def("setMaxsubtreelevelexport",
         static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::ext::ext::box<std::optional<int>> const&)>(&org::imm::ImmDocumentOptionsValue::setMaxsubtreelevelexport),
         pybind11::arg("value"))
    .def("setColumns",
         static_cast<void(org::imm::ImmDocumentOptionsValue::*)(immer::ext::ext::box<std::optional<org::sem::ColumnView>> const&)>(&org::imm::ImmDocumentOptionsValue::setColumns),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmDocumentFragmentValueRead>(m, "immImmDocumentFragmentValueRead")
    .def("getBaseline", static_cast<int const&(org::imm::ImmDocumentFragmentValueRead::*)() const>(&org::imm::ImmDocumentFragmentValueRead::getBaseline))
    .def("getBasecol", static_cast<int const&(org::imm::ImmDocumentFragmentValueRead::*)() const>(&org::imm::ImmDocumentFragmentValueRead::getBasecol))
    ;
  pybind11::class_<org::imm::ImmDocumentFragmentValue>(m, "immImmDocumentFragmentValue")
    .def("setBaseline",
         static_cast<void(org::imm::ImmDocumentFragmentValue::*)(int const&)>(&org::imm::ImmDocumentFragmentValue::setBaseline),
         pybind11::arg("value"))
    .def("setBasecol",
         static_cast<void(org::imm::ImmDocumentFragmentValue::*)(int const&)>(&org::imm::ImmDocumentFragmentValue::setBasecol),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmCriticMarkupValueRead>(m, "immImmCriticMarkupValueRead")
    .def("getKind", static_cast<org::imm::org::imm::ImmCriticMarkup::Kind const&(org::imm::ImmCriticMarkupValueRead::*)() const>(&org::imm::ImmCriticMarkupValueRead::getKind))
    ;
  pybind11::class_<org::imm::ImmCriticMarkupValue>(m, "immImmCriticMarkupValue")
    .def("setKind",
         static_cast<void(org::imm::ImmCriticMarkupValue::*)(org::imm::org::imm::ImmCriticMarkup::Kind const&)>(&org::imm::ImmCriticMarkupValue::setKind),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmDocumentValueRead>(m, "immImmDocumentValueRead")
    .def("getTitle", static_cast<immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getTitle))
    .def("getAuthor", static_cast<immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getAuthor))
    .def("getCreator", static_cast<immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getCreator))
    .def("getFiletags", static_cast<immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmHashTag>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getFiletags))
    .def("getEmail", static_cast<immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmRawText>>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getEmail))
    .def("getLanguage", static_cast<immer::ext::ext::flex_vector<hstd::Str> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getLanguage))
    .def("getOptions", static_cast<org::imm::ImmIdT<org::imm::ImmDocumentOptions> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getOptions))
    .def("getExportfilename", static_cast<immer::ext::ext::box<std::optional<hstd::Str>> const&(org::imm::ImmDocumentValueRead::*)() const>(&org::imm::ImmDocumentValueRead::getExportfilename))
    ;
  pybind11::class_<org::imm::ImmDocumentValue>(m, "immImmDocumentValue")
    .def("setTitle",
         static_cast<void(org::imm::ImmDocumentValue::*)(immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmDocumentValue::setTitle),
         pybind11::arg("value"))
    .def("setAuthor",
         static_cast<void(org::imm::ImmDocumentValue::*)(immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmDocumentValue::setAuthor),
         pybind11::arg("value"))
    .def("setCreator",
         static_cast<void(org::imm::ImmDocumentValue::*)(immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmParagraph>>> const&)>(&org::imm::ImmDocumentValue::setCreator),
         pybind11::arg("value"))
    .def("setFiletags",
         static_cast<void(org::imm::ImmDocumentValue::*)(immer::ext::ext::flex_vector<org::imm::ImmIdT<org::imm::ImmHashTag>> const&)>(&org::imm::ImmDocumentValue::setFiletags),
         pybind11::arg("value"))
    .def("setEmail",
         static_cast<void(org::imm::ImmDocumentValue::*)(immer::ext::ext::box<std::optional<org::imm::ImmIdT<org::imm::ImmRawText>>> const&)>(&org::imm::ImmDocumentValue::setEmail),
         pybind11::arg("value"))
    .def("setLanguage",
         static_cast<void(org::imm::ImmDocumentValue::*)(immer::ext::ext::flex_vector<hstd::Str> const&)>(&org::imm::ImmDocumentValue::setLanguage),
         pybind11::arg("value"))
    .def("setOptions",
         static_cast<void(org::imm::ImmDocumentValue::*)(org::imm::ImmIdT<org::imm::ImmDocumentOptions> const&)>(&org::imm::ImmDocumentValue::setOptions),
         pybind11::arg("value"))
    .def("setExportfilename",
         static_cast<void(org::imm::ImmDocumentValue::*)(immer::ext::ext::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmDocumentValue::setExportfilename),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmFileTargetValueRead>(m, "immImmFileTargetValueRead")
    .def("getPath", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getPath))
    .def("getLine", static_cast<immer::ext::ext::box<std::optional<int>> const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getLine))
    .def("getSearchtarget", static_cast<immer::ext::ext::box<std::optional<hstd::Str>> const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getSearchtarget))
    .def("getRestricttoheadlines", static_cast<bool const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getRestricttoheadlines))
    .def("getTargetid", static_cast<immer::ext::ext::box<std::optional<hstd::Str>> const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getTargetid))
    .def("getRegexp", static_cast<immer::ext::ext::box<std::optional<hstd::Str>> const&(org::imm::ImmFileTargetValueRead::*)() const>(&org::imm::ImmFileTargetValueRead::getRegexp))
    ;
  pybind11::class_<org::imm::ImmFileTargetValue>(m, "immImmFileTargetValue")
    .def("setPath",
         static_cast<void(org::imm::ImmFileTargetValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmFileTargetValue::setPath),
         pybind11::arg("value"))
    .def("setLine",
         static_cast<void(org::imm::ImmFileTargetValue::*)(immer::ext::ext::box<std::optional<int>> const&)>(&org::imm::ImmFileTargetValue::setLine),
         pybind11::arg("value"))
    .def("setSearchtarget",
         static_cast<void(org::imm::ImmFileTargetValue::*)(immer::ext::ext::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmFileTargetValue::setSearchtarget),
         pybind11::arg("value"))
    .def("setRestricttoheadlines",
         static_cast<void(org::imm::ImmFileTargetValue::*)(bool const&)>(&org::imm::ImmFileTargetValue::setRestricttoheadlines),
         pybind11::arg("value"))
    .def("setTargetid",
         static_cast<void(org::imm::ImmFileTargetValue::*)(immer::ext::ext::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmFileTargetValue::setTargetid),
         pybind11::arg("value"))
    .def("setRegexp",
         static_cast<void(org::imm::ImmFileTargetValue::*)(immer::ext::ext::box<std::optional<hstd::Str>> const&)>(&org::imm::ImmFileTargetValue::setRegexp),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmTextSeparatorValueRead>(m, "immImmTextSeparatorValueRead")
    ;
  pybind11::class_<org::imm::ImmTextSeparatorValue>(m, "immImmTextSeparatorValue")
    ;
  pybind11::class_<org::imm::ImmDocumentGroupValueRead>(m, "immImmDocumentGroupValueRead")
    ;
  pybind11::class_<org::imm::ImmDocumentGroupValue>(m, "immImmDocumentGroupValue")
    ;
  pybind11::class_<org::imm::ImmFileValueRead>(m, "immImmFileValueRead")
    .def("getRelpath", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmFileValueRead::*)() const>(&org::imm::ImmFileValueRead::getRelpath))
    .def("getAbspath", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmFileValueRead::*)() const>(&org::imm::ImmFileValueRead::getAbspath))
    .def("getData", static_cast<org::imm::ImmFile::Data const&(org::imm::ImmFileValueRead::*)() const>(&org::imm::ImmFileValueRead::getData))
    ;
  pybind11::class_<org::imm::ImmFileValue>(m, "immImmFileValue")
    .def("setRelpath",
         static_cast<void(org::imm::ImmFileValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmFileValue::setRelpath),
         pybind11::arg("value"))
    .def("setAbspath",
         static_cast<void(org::imm::ImmFileValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmFileValue::setAbspath),
         pybind11::arg("value"))
    .def("setData",
         static_cast<void(org::imm::ImmFileValue::*)(org::imm::ImmFile::Data const&)>(&org::imm::ImmFileValue::setData),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmDirectoryValueRead>(m, "immImmDirectoryValueRead")
    .def("getRelpath", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmDirectoryValueRead::*)() const>(&org::imm::ImmDirectoryValueRead::getRelpath))
    .def("getAbspath", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmDirectoryValueRead::*)() const>(&org::imm::ImmDirectoryValueRead::getAbspath))
    ;
  pybind11::class_<org::imm::ImmDirectoryValue>(m, "immImmDirectoryValue")
    .def("setRelpath",
         static_cast<void(org::imm::ImmDirectoryValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmDirectoryValue::setRelpath),
         pybind11::arg("value"))
    .def("setAbspath",
         static_cast<void(org::imm::ImmDirectoryValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmDirectoryValue::setAbspath),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmSymlinkValueRead>(m, "immImmSymlinkValueRead")
    .def("getIsdirectory", static_cast<bool const&(org::imm::ImmSymlinkValueRead::*)() const>(&org::imm::ImmSymlinkValueRead::getIsdirectory))
    .def("getAbspath", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmSymlinkValueRead::*)() const>(&org::imm::ImmSymlinkValueRead::getAbspath))
    ;
  pybind11::class_<org::imm::ImmSymlinkValue>(m, "immImmSymlinkValue")
    .def("setIsdirectory",
         static_cast<void(org::imm::ImmSymlinkValue::*)(bool const&)>(&org::imm::ImmSymlinkValue::setIsdirectory),
         pybind11::arg("value"))
    .def("setAbspath",
         static_cast<void(org::imm::ImmSymlinkValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmSymlinkValue::setAbspath),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmCmdIncludeValueRead>(m, "immImmCmdIncludeValueRead")
    .def("getPath", static_cast<immer::ext::ext::box<hstd::Str> const&(org::imm::ImmCmdIncludeValueRead::*)() const>(&org::imm::ImmCmdIncludeValueRead::getPath))
    .def("getFirstline", static_cast<immer::ext::ext::box<std::optional<int>> const&(org::imm::ImmCmdIncludeValueRead::*)() const>(&org::imm::ImmCmdIncludeValueRead::getFirstline))
    .def("getLastline", static_cast<immer::ext::ext::box<std::optional<int>> const&(org::imm::ImmCmdIncludeValueRead::*)() const>(&org::imm::ImmCmdIncludeValueRead::getLastline))
    .def("getData", static_cast<org::imm::ImmCmdInclude::Data const&(org::imm::ImmCmdIncludeValueRead::*)() const>(&org::imm::ImmCmdIncludeValueRead::getData))
    ;
  pybind11::class_<org::imm::ImmCmdIncludeValue>(m, "immImmCmdIncludeValue")
    .def("setPath",
         static_cast<void(org::imm::ImmCmdIncludeValue::*)(immer::ext::ext::box<hstd::Str> const&)>(&org::imm::ImmCmdIncludeValue::setPath),
         pybind11::arg("value"))
    .def("setFirstline",
         static_cast<void(org::imm::ImmCmdIncludeValue::*)(immer::ext::ext::box<std::optional<int>> const&)>(&org::imm::ImmCmdIncludeValue::setFirstline),
         pybind11::arg("value"))
    .def("setLastline",
         static_cast<void(org::imm::ImmCmdIncludeValue::*)(immer::ext::ext::box<std::optional<int>> const&)>(&org::imm::ImmCmdIncludeValue::setLastline),
         pybind11::arg("value"))
    .def("setData",
         static_cast<void(org::imm::ImmCmdIncludeValue::*)(org::imm::ImmCmdInclude::Data const&)>(&org::imm::ImmCmdIncludeValue::setData),
         pybind11::arg("value"))
    ;
  pybind11::class_<org::imm::ImmAdapterOrgAPI>(m, "immImmAdapterOrgAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterStmtAPI>(m, "immImmAdapterStmtAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterCmdAPI>(m, "immImmAdapterCmdAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterSubtreeAPI>(m, "immImmAdapterSubtreeAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterNoneAPI>(m, "immImmAdapterNoneAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterAttrAPI>(m, "immImmAdapterAttrAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterAttrListAPI>(m, "immImmAdapterAttrListAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterAttrsAPI>(m, "immImmAdapterAttrsAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterErrorItemAPI>(m, "immImmAdapterErrorItemAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterErrorGroupAPI>(m, "immImmAdapterErrorGroupAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterStmtListAPI>(m, "immImmAdapterStmtListAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterEmptyAPI>(m, "immImmAdapterEmptyAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterLineCommandAPI>(m, "immImmAdapterLineCommandAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterAttachedAPI>(m, "immImmAdapterAttachedAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterCmdCaptionAPI>(m, "immImmAdapterCmdCaptionAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterCmdColumnsAPI>(m, "immImmAdapterCmdColumnsAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterCmdNameAPI>(m, "immImmAdapterCmdNameAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterCmdCallAPI>(m, "immImmAdapterCmdCallAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterCmdCustomArgsAPI>(m, "immImmAdapterCmdCustomArgsAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterCmdCustomRawAPI>(m, "immImmAdapterCmdCustomRawAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterCmdCustomTextAPI>(m, "immImmAdapterCmdCustomTextAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterCmdResultsAPI>(m, "immImmAdapterCmdResultsAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterCmdTblfmAPI>(m, "immImmAdapterCmdTblfmAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterInlineAPI>(m, "immImmAdapterInlineAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterHashTagAPI>(m, "immImmAdapterHashTagAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterInlineFootnoteAPI>(m, "immImmAdapterInlineFootnoteAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterTimeAPI>(m, "immImmAdapterTimeAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterTimeRangeAPI>(m, "immImmAdapterTimeRangeAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterMacroAPI>(m, "immImmAdapterMacroAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterSymbolAPI>(m, "immImmAdapterSymbolAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterLeafAPI>(m, "immImmAdapterLeafAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterEscapedAPI>(m, "immImmAdapterEscapedAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterNewlineAPI>(m, "immImmAdapterNewlineAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterSpaceAPI>(m, "immImmAdapterSpaceAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterWordAPI>(m, "immImmAdapterWordAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterAtMentionAPI>(m, "immImmAdapterAtMentionAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterRawTextAPI>(m, "immImmAdapterRawTextAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterPunctuationAPI>(m, "immImmAdapterPunctuationAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterPlaceholderAPI>(m, "immImmAdapterPlaceholderAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterBigIdentAPI>(m, "immImmAdapterBigIdentAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterTextTargetAPI>(m, "immImmAdapterTextTargetAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterMarkupAPI>(m, "immImmAdapterMarkupAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterBoldAPI>(m, "immImmAdapterBoldAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterUnderlineAPI>(m, "immImmAdapterUnderlineAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterMonospaceAPI>(m, "immImmAdapterMonospaceAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterMarkQuoteAPI>(m, "immImmAdapterMarkQuoteAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterRadioTargetAPI>(m, "immImmAdapterRadioTargetAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterVerbatimAPI>(m, "immImmAdapterVerbatimAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterItalicAPI>(m, "immImmAdapterItalicAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterStrikeAPI>(m, "immImmAdapterStrikeAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterParAPI>(m, "immImmAdapterParAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterLatexAPI>(m, "immImmAdapterLatexAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterLinkAPI>(m, "immImmAdapterLinkAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterBlockAPI>(m, "immImmAdapterBlockAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterBlockCenterAPI>(m, "immImmAdapterBlockCenterAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterBlockQuoteAPI>(m, "immImmAdapterBlockQuoteAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterBlockCommentAPI>(m, "immImmAdapterBlockCommentAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterBlockVerseAPI>(m, "immImmAdapterBlockVerseAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterBlockExampleAPI>(m, "immImmAdapterBlockExampleAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterInlineExportAPI>(m, "immImmAdapterInlineExportAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterCmdExportAPI>(m, "immImmAdapterCmdExportAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterBlockExportAPI>(m, "immImmAdapterBlockExportAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterBlockDynamicFallbackAPI>(m, "immImmAdapterBlockDynamicFallbackAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterBlockAdmonitionAPI>(m, "immImmAdapterBlockAdmonitionAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterBlockCodeEvalResultAPI>(m, "immImmAdapterBlockCodeEvalResultAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterBlockCodeAPI>(m, "immImmAdapterBlockCodeAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterSubtreeLogAPI>(m, "immImmAdapterSubtreeLogAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterSubtreeCompletionAPI>(m, "immImmAdapterSubtreeCompletionAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterCellAPI>(m, "immImmAdapterCellAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterRowAPI>(m, "immImmAdapterRowAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterTableAPI>(m, "immImmAdapterTableAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterParagraphAPI>(m, "immImmAdapterParagraphAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterColonExampleAPI>(m, "immImmAdapterColonExampleAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterCmdAttrAPI>(m, "immImmAdapterCmdAttrAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterCallAPI>(m, "immImmAdapterCallAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterFileAPI>(m, "immImmAdapterFileAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterDirectoryAPI>(m, "immImmAdapterDirectoryAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterSymlinkAPI>(m, "immImmAdapterSymlinkAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterDocumentFragmentAPI>(m, "immImmAdapterDocumentFragmentAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterCriticMarkupAPI>(m, "immImmAdapterCriticMarkupAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterListAPI>(m, "immImmAdapterListAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterListItemAPI>(m, "immImmAdapterListItemAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterDocumentOptionsAPI>(m, "immImmAdapterDocumentOptionsAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterDocumentAPI>(m, "immImmAdapterDocumentAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterFileTargetAPI>(m, "immImmAdapterFileTargetAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterTextSeparatorAPI>(m, "immImmAdapterTextSeparatorAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterCmdIncludeAPI>(m, "immImmAdapterCmdIncludeAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterDocumentGroupAPI>(m, "immImmAdapterDocumentGroupAPI")
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmNoneValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmErrorItemValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmErrorGroupValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmStmtListValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmEmptyValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmCmdCaptionValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmCmdColumnsValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmCmdNameValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmCmdCustomArgsValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmCmdCustomRawValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmCmdCustomTextValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmCmdCallValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmCmdTblfmValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmHashTagValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmInlineFootnoteValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmInlineExportValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmTimeValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmTimeRangeValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmMacroValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmSymbolValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmEscapedValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmNewlineValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmSpaceValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmWordValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmAtMentionValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmRawTextValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmPunctuationValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmPlaceholderValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmBigIdentValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmTextTargetValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmBoldValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmUnderlineValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmMonospaceValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmMarkQuoteValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmVerbatimValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmItalicValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmStrikeValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmParValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmRadioTargetValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmLatexValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmLinkValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmBlockCenterValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmBlockQuoteValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmBlockCommentValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmBlockVerseValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmBlockDynamicFallbackValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmBlockExampleValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmBlockExportValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmBlockAdmonitionValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmBlockCodeEvalResultValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmBlockCodeValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmSubtreeLogValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmSubtreeValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmCellValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmRowValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmTableValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmParagraphValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmColonExampleValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmCmdAttrValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmCmdExportValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmCallValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmListValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmListItemValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmDocumentOptionsValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmDocumentFragmentValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmCriticMarkupValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmDocumentValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmFileTargetValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmTextSeparatorValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmDocumentGroupValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmFileValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmDirectoryValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmSymlinkValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::imm::ImmAdapterT>(m, "immImmAdapterT")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::imm::ImmAdapterT {
                        org::imm::ImmAdapterT result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getValue", static_cast<org::imm::ImmCmdIncludeValueRead(org::imm::ImmAdapterT::*)() const>(&org::imm::ImmAdapterT::getValue))
    .def("__repr__", [](org::imm::ImmAdapterT _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapterT _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::OrgParseFragment>(m, "OrgParseFragment")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::OrgParseFragment {
                        org::OrgParseFragment result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("baseLine", &org::OrgParseFragment::baseLine)
    .def_readwrite("baseCol", &org::OrgParseFragment::baseCol)
    .def_readwrite("text", &org::OrgParseFragment::text)
    .def("__repr__", [](org::OrgParseFragment _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::OrgParseFragment _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::OrgParseParameters>(m, "OrgParseParameters")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::OrgParseParameters {
                        org::OrgParseParameters result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("baseTokenTracePath", &org::OrgParseParameters::baseTokenTracePath)
    .def_readwrite("tokenTracePath", &org::OrgParseParameters::tokenTracePath)
    .def_readwrite("parseTracePath", &org::OrgParseParameters::parseTracePath)
    .def_readwrite("semTracePath", &org::OrgParseParameters::semTracePath)
    .def("__repr__", [](org::OrgParseParameters _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::OrgParseParameters _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::OrgDirectoryParseParameters>(m, "OrgDirectoryParseParameters")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::OrgDirectoryParseParameters {
                        org::OrgDirectoryParseParameters result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](org::OrgDirectoryParseParameters _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::OrgDirectoryParseParameters _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::OrgYamlExportOpts>(m, "OrgYamlExportOpts")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::OrgYamlExportOpts {
                        org::OrgYamlExportOpts result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("skipNullFields", &org::OrgYamlExportOpts::skipNullFields)
    .def_readwrite("skipFalseFields", &org::OrgYamlExportOpts::skipFalseFields)
    .def_readwrite("skipZeroFields", &org::OrgYamlExportOpts::skipZeroFields)
    .def_readwrite("skipLocation", &org::OrgYamlExportOpts::skipLocation)
    .def_readwrite("skipId", &org::OrgYamlExportOpts::skipId)
    .def("__repr__", [](org::OrgYamlExportOpts _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::OrgYamlExportOpts _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::OrgTreeExportOpts>(m, "OrgTreeExportOpts")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::OrgTreeExportOpts {
                        org::OrgTreeExportOpts result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("withLineCol", &org::OrgTreeExportOpts::withLineCol)
    .def_readwrite("withOriginalId", &org::OrgTreeExportOpts::withOriginalId)
    .def_readwrite("withSubnodeIdx", &org::OrgTreeExportOpts::withSubnodeIdx)
    .def_readwrite("skipEmptyFields", &org::OrgTreeExportOpts::skipEmptyFields)
    .def_readwrite("startLevel", &org::OrgTreeExportOpts::startLevel)
    .def_readwrite("withColor", &org::OrgTreeExportOpts::withColor)
    .def_readwrite("maxDepth", &org::OrgTreeExportOpts::maxDepth)
    .def("__repr__", [](org::OrgTreeExportOpts _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::OrgTreeExportOpts _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::AstTrackingPath>(m, "AstTrackingPath")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::AstTrackingPath {
                        org::AstTrackingPath result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("path", &org::AstTrackingPath::path)
    .def("getParent",
         static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingPath::*)(int) const>(&org::AstTrackingPath::getParent),
         pybind11::arg_v("offset", 0))
    .def("getNode", static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingPath::*)() const>(&org::AstTrackingPath::getNode))
    .def("__repr__", [](org::AstTrackingPath _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::AstTrackingPath _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::AstTrackingAlternatives>(m, "AstTrackingAlternatives")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::AstTrackingAlternatives {
                        org::AstTrackingAlternatives result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getAllNodes", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::AstTrackingAlternatives::*)() const>(&org::AstTrackingAlternatives::getAllNodes), R"RAW(\brief Return final nodes for all tracking alternatives.)RAW")
    .def("getNode", static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingAlternatives::*)() const>(&org::AstTrackingAlternatives::getNode), R"RAW(\brief Return first node from the alternatives.)RAW")
    .def("__repr__", [](org::AstTrackingAlternatives _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::AstTrackingAlternatives _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::AstTrackingGroup>(m, "AstTrackingGroup")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::AstTrackingGroup {
                        org::AstTrackingGroup result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getRadioTarget", static_cast<org::AstTrackingGroup::RadioTarget const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getRadioTarget))
    .def("getTrackedHashtag", static_cast<org::AstTrackingGroup::TrackedHashtag&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getTrackedHashtag))
    .def("getSingle", static_cast<org::AstTrackingGroup::Single const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getSingle))
    .def("getRadioTarget", static_cast<org::AstTrackingGroup::RadioTarget&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getRadioTarget))
    .def("getSingle", static_cast<org::AstTrackingGroup::Single&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getSingle))
    .def("isSingle", static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isSingle))
    .def("isTrackedHashtag", static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isTrackedHashtag))
    .def("isRadioTarget", static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isRadioTarget))
    .def("__repr__", [](org::AstTrackingGroup _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::AstTrackingGroup _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::AstTrackingGroup::RadioTarget>(m, "AstTrackingGroupRadioTarget")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::AstTrackingGroup::RadioTarget {
                        org::AstTrackingGroup::RadioTarget result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &org::AstTrackingGroup::RadioTarget::target)
    .def_readwrite("nodes", &org::AstTrackingGroup::RadioTarget::nodes)
    .def("__repr__", [](org::AstTrackingGroup::RadioTarget _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::AstTrackingGroup::RadioTarget _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::AstTrackingGroup::Single>(m, "AstTrackingGroupSingle")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::AstTrackingGroup::Single {
                        org::AstTrackingGroup::Single result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("node", &org::AstTrackingGroup::Single::node)
    .def("__repr__", [](org::AstTrackingGroup::Single _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::AstTrackingGroup::Single _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::AstTrackingGroup::TrackedHashtag>(m, "AstTrackingGroupTrackedHashtag")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::AstTrackingGroup::TrackedHashtag {
                        org::AstTrackingGroup::TrackedHashtag result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("tag", &org::AstTrackingGroup::TrackedHashtag::tag)
    .def_readwrite("targets", &org::AstTrackingGroup::TrackedHashtag::targets)
    .def("__repr__", [](org::AstTrackingGroup::TrackedHashtag _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::AstTrackingGroup::TrackedHashtag _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::AstTrackingMap>(m, "AstTrackingMap")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::AstTrackingMap {
                        org::AstTrackingMap result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("footnotes", &org::AstTrackingMap::footnotes)
    .def_readwrite("subtrees", &org::AstTrackingMap::subtrees)
    .def_readwrite("names", &org::AstTrackingMap::names)
    .def_readwrite("anchorTargets", &org::AstTrackingMap::anchorTargets)
    .def_readwrite("radioTargets", &org::AstTrackingMap::radioTargets)
    .def_readwrite("hashtagDefinitions", &org::AstTrackingMap::hashtagDefinitions)
    .def("getIdPath",
         static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getIdPath),
         pybind11::arg("id"))
    .def("getNamePath",
         static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getNamePath),
         pybind11::arg("id"))
    .def("getAnchorTarget",
         static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getAnchorTarget),
         pybind11::arg("id"))
    .def("getFootnotePath",
         static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getFootnotePath),
         pybind11::arg("id"))
    .def("__repr__", [](org::AstTrackingMap _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::AstTrackingMap _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::SequenceSegment>(m, "SequenceSegment")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::SequenceSegment {
                        hstd::SequenceSegment result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("kind", &hstd::SequenceSegment::kind, R"RAW(\brief Kind of the segment, does not have to be unique for all
segments, and different sequence segment groups can have segments
with identical kinds.)RAW")
    .def_readwrite("first", &hstd::SequenceSegment::first, R"RAW(\brief Inclusive left boundary of the segment. Mustnot overlap with
other segments' boundaries,but can be identical to the `last`,
to create a point segment (spans 1 element).)RAW")
    .def_readwrite("last", &hstd::SequenceSegment::last, R"RAW(\brief Inclusive right boundary for the segment)RAW")
    .def("__repr__", [](hstd::SequenceSegment _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::SequenceSegment _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::SequenceSegmentGroup>(m, "SequenceSegmentGroup")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::SequenceSegmentGroup {
                        hstd::SequenceSegmentGroup result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("kind", &hstd::SequenceSegmentGroup::kind, R"RAW(\brief An kind of the segment group, does not have to be unique)RAW")
    .def_readwrite("segments", &hstd::SequenceSegmentGroup::segments, R"RAW(\brief List of input segments for grouping)RAW")
    .def("__repr__", [](hstd::SequenceSegmentGroup _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::SequenceSegmentGroup _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::SequenceAnnotationTag>(m, "SequenceAnnotationTag")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::SequenceAnnotationTag {
                        hstd::SequenceAnnotationTag result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("groupKind", &hstd::SequenceAnnotationTag::groupKind, R"RAW(\brief ID of the original group this segment came from)RAW")
    .def_readwrite("segmentKinds", &hstd::SequenceAnnotationTag::segmentKinds, R"RAW(\brief ID of the segment in this group.

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
    .def("__repr__", [](hstd::SequenceAnnotationTag _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::SequenceAnnotationTag _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::SequenceAnnotation>(m, "SequenceAnnotation")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::SequenceAnnotation {
                        hstd::SequenceAnnotation result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("first", &hstd::SequenceAnnotation::first, R"RAW(\brief Inclusive left boundary for the sequence segment annotation)RAW")
    .def_readwrite("last", &hstd::SequenceAnnotation::last, R"RAW(\brief Inclusive right boundary for the sequence segment)RAW")
    .def_readwrite("annotations", &hstd::SequenceAnnotation::annotations, R"RAW(\brief Full list of all annotated segments.)RAW")
    .def("isAnnotatedWith",
         static_cast<bool(hstd::SequenceAnnotation::*)(int, int) const>(&hstd::SequenceAnnotation::isAnnotatedWith),
         pybind11::arg("groupKind"),
         pybind11::arg("segmentKind"),
         R"RAW(\brief Check if the segment is annotated with a given group kind
and a segment kind.)RAW")
    .def("__repr__", [](hstd::SequenceAnnotation _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::SequenceAnnotation _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::bind::python::PyCodeEvalParameters>(m, "PyCodeEvalParameters")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::bind::python::PyCodeEvalParameters {
                        org::bind::python::PyCodeEvalParameters result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("evalBlock", &org::bind::python::PyCodeEvalParameters::evalBlock)
    .def("setTraceFile",
         static_cast<void(org::bind::python::PyCodeEvalParameters::*)(std::string const&)>(&org::bind::python::PyCodeEvalParameters::setTraceFile),
         pybind11::arg("path"))
    .def("__repr__", [](org::bind::python::PyCodeEvalParameters _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::bind::python::PyCodeEvalParameters _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<org::bind::python::ExporterPython>(m, "ExporterPython")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> org::bind::python::ExporterPython {
                        org::bind::python::ExporterPython result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("enableBufferTrace", static_cast<void(org::bind::python::ExporterPython::*)()>(&org::bind::python::ExporterPython::enableBufferTrace))
    .def("getTraceBuffer", static_cast<std::string(org::bind::python::ExporterPython::*)() const>(&org::bind::python::ExporterPython::getTraceBuffer))
    .def("enableFileTrace",
         static_cast<void(org::bind::python::ExporterPython::*)(std::string const&, bool)>(&org::bind::python::ExporterPython::enableFileTrace),
         pybind11::arg("path"),
         pybind11::arg("colored"))
    .def("setVisitAnyIdAround",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitAnyIdAround),
         pybind11::arg("cb"))
    .def("setVisitAnyIdIn",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitAnyIdIn),
         pybind11::arg("cb"))
    .def("setVisitAnyField",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitAnyField),
         pybind11::arg("cb"))
    .def("setEvalTopCb",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setEvalTopCb),
         pybind11::arg("cb"))
    .def("setVisitIdAround",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitIdAround),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setEvalIdAround",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setEvalIdAround),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setVisitIdInCb",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitIdInCb),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setEvalIdIn",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setEvalIdIn),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setVisitLeafField",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::LeafFieldType, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitLeafField),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setEvalLeafField",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::LeafFieldType, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setEvalLeafField),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setVisitOrgField",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitOrgField),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setEvalOrgField",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setEvalOrgField),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setSelf",
         static_cast<void(org::bind::python::ExporterPython::*)(pybind11::object)>(&org::bind::python::ExporterPython::setSelf),
         pybind11::arg("val"))
    .def("setNewOrgRes",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setNewOrgRes),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setNewAnyOrgRes",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setNewAnyOrgRes),
         pybind11::arg("cb"))
    .def("setNewLeafRes",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::LeafFieldType, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setNewLeafRes),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setNewAnyLeafRes",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setNewAnyLeafRes),
         pybind11::arg("cb"))
    .def("setPushVisitAnyId",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setPushVisitAnyId),
         pybind11::arg("cb"))
    .def("setPopVisitAnyId",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setPopVisitAnyId),
         pybind11::arg("cb"))
    .def("setPushVisitId",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setPushVisitId),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setPopVisitIdCb",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setPopVisitIdCb),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setVisitAnyHookCb",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitAnyHookCb),
         pybind11::arg("cb"))
    .def("setVisitIdHook",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitIdHook),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("print_trace",
         static_cast<void(org::bind::python::ExporterPython::*)(std::string const&, std::string const&, std::string const&, int)>(&org::bind::python::ExporterPython::print_trace),
         pybind11::arg("trace"),
         pybind11::arg("file"),
         pybind11::arg("function"),
         pybind11::arg("line"))
    .def("evalTop",
         static_cast<org::bind::python::ExporterPython::Res(org::bind::python::ExporterPython::*)(org::sem::SemId<org::sem::Org>)>(&org::bind::python::ExporterPython::evalTop),
         pybind11::arg("org"))
    .def("eval",
         static_cast<org::bind::python::ExporterPython::Res(org::bind::python::ExporterPython::*)(org::sem::SemId<org::sem::Org>)>(&org::bind::python::ExporterPython::eval),
         pybind11::arg("org"))
    .def("__repr__", [](org::bind::python::ExporterPython _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::bind::python::ExporterPython _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<org::AstTrackingGroup::Kind>(m, "AstTrackingGroupKind", type_registry_guard);
  pybind11::enum_<org::AstTrackingGroup::Kind>(m, "AstTrackingGroupKind")
    .value("RadioTarget", org::AstTrackingGroup::Kind::RadioTarget)
    .value("Single", org::AstTrackingGroup::Kind::Single)
    .value("TrackedHashtag", org::AstTrackingGroup::Kind::TrackedHashtag)
    .def("__iter__", [](org::AstTrackingGroup::Kind _self) -> org::bind::python::PyEnumIterator<org::AstTrackingGroup::Kind> {
                     return
                     org::bind::python::PyEnumIterator<org::AstTrackingGroup::Kind>
                     ();
                     })
    ;
  bind_enum_iterator<org::bind::python::LeafFieldType>(m, "LeafFieldType", type_registry_guard);
  pybind11::enum_<org::bind::python::LeafFieldType>(m, "LeafFieldType")
    .value("Int", org::bind::python::LeafFieldType::Int)
    .value("UserTimeKind", org::bind::python::LeafFieldType::UserTimeKind)
    .value("QDate", org::bind::python::LeafFieldType::QDate)
    .value("Bool", org::bind::python::LeafFieldType::Bool)
    .value("FixedIdVec", org::bind::python::LeafFieldType::FixedIdVec)
    .value("TopIdVec", org::bind::python::LeafFieldType::TopIdVec)
    .value("QDateTime", org::bind::python::LeafFieldType::QDateTime)
    .value("Str", org::bind::python::LeafFieldType::Str)
    .value("Any", org::bind::python::LeafFieldType::Any)
    .def("__iter__", [](org::bind::python::LeafFieldType _self) -> org::bind::python::PyEnumIterator<org::bind::python::LeafFieldType> {
                     return
                     org::bind::python::PyEnumIterator<org::bind::python::LeafFieldType>
                     ();
                     })
    ;
  m.def("newSemTimeStatic",
        static_cast<org::sem::SemId<org::sem::Time>(*)(hstd::UserTimeBreakdown const&, bool)>(&org::newSemTimeStatic),
        pybind11::arg("breakdown"),
        pybind11::arg_v("isActive", 0));
  m.def("parseFile",
        static_cast<org::sem::SemId<org::sem::Org>(*)(std::string, org::OrgParseParameters const&)>(&org::parseFile),
        pybind11::arg("file"),
        pybind11::arg("opts"));
  m.def("parseString",
        static_cast<org::sem::SemId<org::sem::Org>(*)(std::string const)>(&org::parseString),
        pybind11::arg("text"));
  m.def("parseStringOpts",
        static_cast<org::sem::SemId<org::sem::Org>(*)(std::string const, org::OrgParseParameters const&)>(&org::parseStringOpts),
        pybind11::arg("text"),
        pybind11::arg("opts"));
  m.def("parseDirectoryOpts",
        static_cast<std::optional<org::sem::SemId<org::sem::Org>>(*)(std::string const&, org::OrgDirectoryParseParameters const&)>(&org::parseDirectoryOpts),
        pybind11::arg("path"),
        pybind11::arg("opts"));
  m.def("parseFileWithIncludes",
        static_cast<org::sem::SemId<org::sem::File>(*)(std::string const&, org::OrgDirectoryParseParameters const&)>(&org::parseFileWithIncludes),
        pybind11::arg("file"),
        pybind11::arg("opts"));
  m.def("asOneNode",
        static_cast<org::sem::SemId<org::sem::Org>(*)(org::sem::OrgArg)>(&org::asOneNode),
        pybind11::arg("arg"));
  m.def("formatToString",
        static_cast<std::string(*)(org::sem::SemId<org::sem::Org>)>(&org::formatToString),
        pybind11::arg("arg"));
  m.def("exportToYamlString",
        static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&, org::OrgYamlExportOpts const&)>(&org::exportToYamlString),
        pybind11::arg("node"),
        pybind11::arg("opts"));
  m.def("exportToYamlFile",
        static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string, org::OrgYamlExportOpts const&)>(&org::exportToYamlFile),
        pybind11::arg("node"),
        pybind11::arg("path"),
        pybind11::arg("opts"));
  m.def("exportToJsonString",
        static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&)>(&org::exportToJsonString),
        pybind11::arg("node"));
  m.def("exportToJsonFile",
        static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string)>(&org::exportToJsonFile),
        pybind11::arg("node"),
        pybind11::arg("path"));
  m.def("readProtobufFile",
        static_cast<org::sem::SemId<org::sem::Document>(*)(std::string const&)>(&org::readProtobufFile),
        pybind11::arg("file"));
  m.def("exportToProtobufFile",
        static_cast<void(*)(org::sem::SemId<org::sem::Document>, std::string const&)>(&org::exportToProtobufFile),
        pybind11::arg("doc"),
        pybind11::arg("file"));
  m.def("exportToTreeString",
        static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&, org::OrgTreeExportOpts const&)>(&org::exportToTreeString),
        pybind11::arg("node"),
        pybind11::arg("opts"));
  m.def("exportToTreeFile",
        static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string, org::OrgTreeExportOpts const&)>(&org::exportToTreeFile),
        pybind11::arg("node"),
        pybind11::arg("path"),
        pybind11::arg("opts"));
  m.def("getAstTrackingMap",
        static_cast<org::AstTrackingMap(*)(hstd::Vec<org::sem::SemId<org::sem::Org>> const&)>(&org::getAstTrackingMap),
        pybind11::arg("nodes"));
  m.def("getSubnodeGroups",
        static_cast<hstd::Vec<org::AstTrackingGroup>(*)(org::sem::SemId<org::sem::Org>, org::AstTrackingMap const&)>(&org::getSubnodeGroups),
        pybind11::arg("node"),
        pybind11::arg("map"));
  m.def("annotateSequence",
        static_cast<hstd::Vec<hstd::SequenceAnnotation>(*)(hstd::Vec<hstd::SequenceSegmentGroup> const&, int, int)>(&hstd::annotateSequence),
        pybind11::arg("groups"),
        pybind11::arg("first"),
        pybind11::arg("last"));
  m.def("eachSubnodeRec",
        static_cast<void(*)(org::sem::SemId<org::sem::Org>, pybind11::function)>(&org::bind::python::eachSubnodeRec),
        pybind11::arg("node"),
        pybind11::arg("callback"));
  m.def("eachSubnodeRecSimplePath",
        static_cast<void(*)(org::sem::SemId<org::sem::Org>, pybind11::function)>(&org::bind::python::eachSubnodeRecSimplePath),
        pybind11::arg("node"),
        pybind11::arg("callback"));
  m.def("setShouldProcessPath",
        static_cast<void(*)(org::OrgDirectoryParseParameters*, pybind11::function)>(&org::bind::python::setShouldProcessPath),
        pybind11::arg("parameters"),
        pybind11::arg("callback"));
  m.def("setGetParsedNode",
        static_cast<void(*)(org::OrgDirectoryParseParameters*, pybind11::function)>(&org::bind::python::setGetParsedNode),
        pybind11::arg("params"),
        pybind11::arg("callback"));
  m.def("evaluateCodeBlocks",
        static_cast<org::sem::SemId<org::sem::Org>(*)(org::sem::SemId<org::sem::Org>, org::bind::python::PyCodeEvalParameters const&)>(&org::bind::python::evaluateCodeBlocks),
        pybind11::arg("node"),
        pybind11::arg("conf"));
}
/* clang-format on */