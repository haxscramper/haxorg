/* clang-format off */
#undef slots
#define PYBIND11_DETAILED_ERROR_MESSAGES
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/map.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/stl/function.h>
#include <nanobind/stl/map.h>
#include <nanobind/stl/optional.h>
#include <nanobind/stl/set.h>
#include <nanobind/stl/shared_ptr.h>
#include <nanobind/stl/string_view.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/unique_ptr.h>
#include <nanobind/stl/unordered_map.h>
#include <nanobind/stl/variant.h>
#include <nanobind/operators.h>
#include <nanobind/make_iterator.h>
#include <nanobind/ndarray.h>
#include <haxorg/sem/SemOrg.hpp>
#include "pyhaxorg_manual_impl.hpp"
NB_MAKE_OPAQUE(std::vector<org::sem::OrgJson>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::OrgJson>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::Org>>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::Org>>)
NB_MAKE_OPAQUE(std::vector<hstd::ext::Report>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::ext::Report>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::ErrorGroup>>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>)
NB_MAKE_OPAQUE(std::vector<int>)
NB_MAKE_OPAQUE(hstd::Vec<int>)
NB_MAKE_OPAQUE(std::vector<org::imm::ImmAdapter>)
NB_MAKE_OPAQUE(hstd::Vec<org::imm::ImmAdapter>)
NB_MAKE_OPAQUE(std::unordered_map<org::sem::HashTagFlat, org::AstTrackingPath>)
NB_MAKE_OPAQUE(hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingPath>)
NB_MAKE_OPAQUE(std::unordered_map<hstd::Str, org::AstTrackingAlternatives>)
NB_MAKE_OPAQUE(hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives>)
NB_MAKE_OPAQUE(std::unordered_map<org::sem::HashTagFlat, org::AstTrackingAlternatives>)
NB_MAKE_OPAQUE(hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingAlternatives>)
NB_MAKE_OPAQUE(std::vector<hstd::SequenceSegment>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::SequenceSegment>)
NB_MAKE_OPAQUE(std::vector<hstd::SequenceAnnotationTag>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::SequenceAnnotationTag>)
NB_MAKE_OPAQUE(std::vector<org::imm::ImmUniqId>)
NB_MAKE_OPAQUE(hstd::Vec<org::imm::ImmUniqId>)
NB_MAKE_OPAQUE(std::vector<org::graph::MapLink>)
NB_MAKE_OPAQUE(hstd::Vec<org::graph::MapLink>)
NB_MAKE_OPAQUE(std::unordered_map<org::graph::MapNode, org::graph::MapNodeProp>)
NB_MAKE_OPAQUE(hstd::UnorderedMap<org::graph::MapNode, org::graph::MapNodeProp>)
NB_MAKE_OPAQUE(std::unordered_map<org::graph::MapEdge, org::graph::MapEdgeProp>)
NB_MAKE_OPAQUE(hstd::UnorderedMap<org::graph::MapEdge, org::graph::MapEdgeProp>)
NB_MAKE_OPAQUE(std::unordered_map<org::graph::MapNode, org::graph::AdjNodesList>)
NB_MAKE_OPAQUE(hstd::UnorderedMap<org::graph::MapNode, org::graph::AdjNodesList>)
NB_MAKE_OPAQUE(std::vector<org::graph::MapNode>)
NB_MAKE_OPAQUE(hstd::Vec<org::graph::MapNode>)
NB_MAKE_OPAQUE(std::vector<org::graph::MapEdge>)
NB_MAKE_OPAQUE(hstd::Vec<org::graph::MapEdge>)
NB_MAKE_OPAQUE(std::vector<org::sem::LispCode>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::LispCode>)
NB_MAKE_OPAQUE(std::vector<org::sem::Tblfm::Assign>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::Tblfm::Assign>)
NB_MAKE_OPAQUE(std::vector<org::sem::Tblfm::Expr>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::Tblfm::Expr>)
NB_MAKE_OPAQUE(std::vector<org::sem::Tblfm::Assign::Flag>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::Tblfm::Assign::Flag>)
NB_MAKE_OPAQUE(std::vector<org::sem::AttrValue::DimensionSpan>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::AttrValue::DimensionSpan>)
NB_MAKE_OPAQUE(std::vector<hstd::Str>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::Str>)
NB_MAKE_OPAQUE(std::vector<org::sem::HashTagText>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::HashTagText>)
NB_MAKE_OPAQUE(std::vector<org::sem::HashTagFlat>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::HashTagFlat>)
NB_MAKE_OPAQUE(std::vector<org::sem::AttrValue>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::AttrValue>)
NB_MAKE_OPAQUE(std::unordered_map<hstd::Str, org::sem::AttrList>)
NB_MAKE_OPAQUE(hstd::UnorderedMap<hstd::Str, org::sem::AttrList>)
NB_MAKE_OPAQUE(std::vector<org::sem::OrgCodeEvalInput::Var>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::OrgCodeEvalInput::Var>)
NB_MAKE_OPAQUE(std::vector<org::sem::ColumnView::Column>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::ColumnView::Column>)
NB_MAKE_OPAQUE(std::vector<org::sem::BlockCodeLine::Part>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::BlockCodeLine::Part>)
NB_MAKE_OPAQUE(std::unordered_map<hstd::Str, hstd::Str>)
NB_MAKE_OPAQUE(hstd::UnorderedMap<hstd::Str, hstd::Str>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::ErrorItem>>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>)
NB_MAKE_OPAQUE(std::vector<org::sem::Time::Repeat>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::Time::Repeat>)
NB_MAKE_OPAQUE(std::vector<org::sem::Symbol::Param>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::Symbol::Param>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::ErrorSkipToken>>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::HashTag>>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::HashTag>>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::SubtreeLog>>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>)
NB_MAKE_OPAQUE(std::vector<org::sem::NamedProperty>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::NamedProperty>)
NB_MAKE_OPAQUE(std::vector<org::sem::SubtreePeriod>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SubtreePeriod>)
NB_MAKE_OPAQUE(hstd::IntSet<org::sem::SubtreePeriod::Kind>)
NB_MAKE_OPAQUE(std::vector<org::sem::TodoKeyword>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::TodoKeyword>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::BigIdent>>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::BigIdent>>)
NB_MAKE_OPAQUE(std::vector<hstd::UserTime>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::UserTime>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::Time>>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::Time>>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::Cell>>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::Cell>>)
NB_MAKE_OPAQUE(std::vector<org::sem::OrgCodeEvalOutput>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::OrgCodeEvalOutput>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::BlockCodeEvalResult>>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>)
NB_MAKE_OPAQUE(std::vector<org::sem::BlockCodeLine>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::BlockCodeLine>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::Row>>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::Row>>)
NB_MAKE_OPAQUE(std::vector<org::AstTrackingGroup>)
NB_MAKE_OPAQUE(hstd::Vec<org::AstTrackingGroup>)
NB_MAKE_OPAQUE(std::vector<hstd::SequenceAnnotation>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::SequenceAnnotation>)
NB_MAKE_OPAQUE(std::vector<hstd::SequenceSegmentGroup>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::SequenceSegmentGroup>)
NB_MODULE(pyhaxorg, m) {
  org::bind::python::PyTypeRegistryGuard type_registry_guard{};
  bind_hstdVec<org::sem::OrgJson>(m, "VecOfOrgJson", type_registry_guard);
  bind_hstdVec<org::sem::SemId<org::sem::Org>>(m, "VecOfSemIdOfOrg", type_registry_guard);
  bind_hstdVec<hstd::ext::Report>(m, "VecOfReport", type_registry_guard);
  bind_hstdVec<org::sem::SemId<org::sem::ErrorGroup>>(m, "VecOfSemIdOfErrorGroup", type_registry_guard);
  bind_hstdVec<int>(m, "VecOfInt", type_registry_guard);
  bind_hstdVec<org::imm::ImmAdapter>(m, "VecOfImmAdapter", type_registry_guard);
  bind_hstdUnorderedMap<org::sem::HashTagFlat, org::AstTrackingPath>(m, "UnorderedMapOfHashTagFlatAstTrackingPath", type_registry_guard);
  bind_hstdUnorderedMap<hstd::Str, org::AstTrackingAlternatives>(m, "UnorderedMapOfStrAstTrackingAlternatives", type_registry_guard);
  bind_hstdUnorderedMap<org::sem::HashTagFlat, org::AstTrackingAlternatives>(m, "UnorderedMapOfHashTagFlatAstTrackingAlternatives", type_registry_guard);
  bind_hstdVec<hstd::SequenceSegment>(m, "VecOfSequenceSegment", type_registry_guard);
  bind_hstdVec<hstd::SequenceAnnotationTag>(m, "VecOfSequenceAnnotationTag", type_registry_guard);
  bind_hstdVec<org::imm::ImmUniqId>(m, "VecOfImmUniqId", type_registry_guard);
  bind_hstdVec<org::graph::MapLink>(m, "VecOfGraphMapLink", type_registry_guard);
  bind_hstdUnorderedMap<org::graph::MapNode, org::graph::MapNodeProp>(m, "UnorderedMapOfGraphMapNodeGraphMapNodeProp", type_registry_guard);
  bind_hstdUnorderedMap<org::graph::MapEdge, org::graph::MapEdgeProp>(m, "UnorderedMapOfGraphMapEdgeGraphMapEdgeProp", type_registry_guard);
  bind_hstdUnorderedMap<org::graph::MapNode, org::graph::AdjNodesList>(m, "UnorderedMapOfGraphMapNodeGraphAdjNodesList", type_registry_guard);
  bind_hstdVec<org::graph::MapNode>(m, "VecOfGraphMapNode", type_registry_guard);
  bind_hstdVec<org::graph::MapEdge>(m, "VecOfGraphMapEdge", type_registry_guard);
  bind_hstdVec<org::sem::LispCode>(m, "VecOfLispCode", type_registry_guard);
  bind_hstdVec<org::sem::Tblfm::Assign>(m, "VecOfTblfmAssign", type_registry_guard);
  bind_hstdVec<org::sem::Tblfm::Expr>(m, "VecOfTblfmExpr", type_registry_guard);
  bind_hstdVec<org::sem::Tblfm::Assign::Flag>(m, "VecOfTblfmAssignFlag", type_registry_guard);
  bind_hstdVec<org::sem::AttrValue::DimensionSpan>(m, "VecOfAttrValueDimensionSpan", type_registry_guard);
  bind_hstdVec<hstd::Str>(m, "VecOfStr", type_registry_guard);
  bind_hstdVec<org::sem::HashTagText>(m, "VecOfHashTagText", type_registry_guard);
  bind_hstdVec<org::sem::HashTagFlat>(m, "VecOfHashTagFlat", type_registry_guard);
  bind_hstdVec<org::sem::AttrValue>(m, "VecOfAttrValue", type_registry_guard);
  bind_hstdUnorderedMap<hstd::Str, org::sem::AttrList>(m, "UnorderedMapOfStrAttrList", type_registry_guard);
  bind_hstdVec<org::sem::OrgCodeEvalInput::Var>(m, "VecOfOrgCodeEvalInputVar", type_registry_guard);
  bind_hstdVec<org::sem::ColumnView::Column>(m, "VecOfColumnViewColumn", type_registry_guard);
  bind_hstdVec<org::sem::BlockCodeLine::Part>(m, "VecOfBlockCodeLinePart", type_registry_guard);
  bind_hstdUnorderedMap<hstd::Str, hstd::Str>(m, "UnorderedMapOfStrStr", type_registry_guard);
  bind_hstdVec<org::sem::SemId<org::sem::ErrorItem>>(m, "VecOfSemIdOfErrorItem", type_registry_guard);
  bind_hstdVec<org::sem::Time::Repeat>(m, "VecOfTimeRepeat", type_registry_guard);
  bind_hstdVec<org::sem::Symbol::Param>(m, "VecOfSymbolParam", type_registry_guard);
  bind_hstdVec<org::sem::SemId<org::sem::ErrorSkipToken>>(m, "VecOfSemIdOfErrorSkipToken", type_registry_guard);
  bind_hstdVec<org::sem::SemId<org::sem::HashTag>>(m, "VecOfSemIdOfHashTag", type_registry_guard);
  bind_hstdVec<org::sem::SemId<org::sem::SubtreeLog>>(m, "VecOfSemIdOfSubtreeLog", type_registry_guard);
  bind_hstdVec<org::sem::NamedProperty>(m, "VecOfNamedProperty", type_registry_guard);
  bind_hstdVec<org::sem::SubtreePeriod>(m, "VecOfSubtreePeriod", type_registry_guard);
  bind_hstdIntSet<org::sem::SubtreePeriod::Kind>(m, "IntSetOfSubtreePeriodKind", type_registry_guard);
  bind_hstdVec<org::sem::TodoKeyword>(m, "VecOfTodoKeyword", type_registry_guard);
  bind_hstdVec<org::sem::SemId<org::sem::BigIdent>>(m, "VecOfSemIdOfBigIdent", type_registry_guard);
  bind_hstdVec<hstd::UserTime>(m, "VecOfUserTime", type_registry_guard);
  bind_hstdVec<org::sem::SemId<org::sem::Time>>(m, "VecOfSemIdOfTime", type_registry_guard);
  bind_hstdVec<org::sem::SemId<org::sem::Cell>>(m, "VecOfSemIdOfCell", type_registry_guard);
  bind_hstdVec<org::sem::OrgCodeEvalOutput>(m, "VecOfOrgCodeEvalOutput", type_registry_guard);
  bind_hstdVec<org::sem::SemId<org::sem::BlockCodeEvalResult>>(m, "VecOfSemIdOfBlockCodeEvalResult", type_registry_guard);
  bind_hstdVec<org::sem::BlockCodeLine>(m, "VecOfBlockCodeLine", type_registry_guard);
  bind_hstdVec<org::sem::SemId<org::sem::Row>>(m, "VecOfSemIdOfRow", type_registry_guard);
  bind_hstdVec<org::AstTrackingGroup>(m, "VecOfAstTrackingGroup", type_registry_guard);
  bind_hstdVec<hstd::SequenceAnnotation>(m, "VecOfSequenceAnnotation", type_registry_guard);
  bind_hstdVec<hstd::SequenceSegmentGroup>(m, "VecOfSequenceSegmentGroup", type_registry_guard);
  nanobind::class_<hstd::UserTimeBreakdown>(m, "UserTimeBreakdown")
    .def("__init__",
         [](hstd::UserTimeBreakdown* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::UserTimeBreakdown();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("year", &hstd::UserTimeBreakdown::year)
    .def_rw("month", &hstd::UserTimeBreakdown::month)
    .def_rw("day", &hstd::UserTimeBreakdown::day)
    .def_rw("hour", &hstd::UserTimeBreakdown::hour)
    .def_rw("minute", &hstd::UserTimeBreakdown::minute)
    .def_rw("second", &hstd::UserTimeBreakdown::second)
    .def_rw("zone", &hstd::UserTimeBreakdown::zone)
    .def("__repr__", [](hstd::UserTimeBreakdown const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::UserTimeBreakdown const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::UserTime>(m, "UserTime")
    .def("__init__",
         [](hstd::UserTime* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::UserTime();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getBreakdown", static_cast<hstd::UserTimeBreakdown(hstd::UserTime::*)() const>(&hstd::UserTime::getBreakdown))
    .def("format", static_cast<std::string(hstd::UserTime::*)() const>(&hstd::UserTime::format))
    .def("getTimeDeltaSeconds",
         static_cast<int64_t(hstd::UserTime::*)(hstd::UserTime const&) const>(&hstd::UserTime::getTimeDeltaSeconds),
         nanobind::arg("other"))
    .def("toUnixTimestamp", static_cast<int64_t(hstd::UserTime::*)() const>(&hstd::UserTime::toUnixTimestamp))
    .def("__repr__", [](hstd::UserTime const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::UserTime const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::parse::SourceLoc>(m, "parseSourceLoc")
    .def("__init__",
         [](org::parse::SourceLoc* result, nanobind::kwargs const& kwargs) {
         new(result) org::parse::SourceLoc();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("line", &org::parse::SourceLoc::line)
    .def_rw("column", &org::parse::SourceLoc::column)
    .def_rw("pos", &org::parse::SourceLoc::pos)
    .def_rw("file_id", &org::parse::SourceLoc::file_id)
    .def("__repr__", [](org::parse::SourceLoc const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::parse::SourceLoc const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::OrgJson>(m, "OrgJson")
    .def("__init__",
         [](org::sem::OrgJson* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::OrgJson();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getKind", static_cast<OrgJsonKind(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getKind))
    .def("getJsonString", static_cast<std::string(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getJsonString))
    .def("at",
         static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::at),
         nanobind::arg("idx"))
    .def("at",
         static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(std::string const&) const>(&org::sem::OrgJson::at),
         nanobind::arg("name"))
    .def("getString", static_cast<std::string(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getString))
    .def("getField",
         static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(std::string const&) const>(&org::sem::OrgJson::getField),
         nanobind::arg("name"))
    .def("getItem",
         static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::getItem),
         nanobind::arg("index"))
    .def("getInt", static_cast<int(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getInt))
    .def("getBool", static_cast<bool(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getBool))
    .def("getArray", static_cast<hstd::Vec<org::sem::OrgJson>(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getArray))
    .def("dump",
         static_cast<std::string(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::dump),
         nanobind::arg("indent"))
    .def("__repr__", [](org::sem::OrgJson const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgJson const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Org>(m, "Org")
    .def_rw("loc", &org::sem::Org::loc, R"RAW(\brief Location of the node in the original source file)RAW")
    .def_rw("subnodes", &org::sem::Org::subnodes, R"RAW(\brief List of subnodes.

Some of the derived nodes don't make the use of subnode list
(word, punctuation etc), but it was left on the top level of the
hierarchy for conveinience purposes. It is not expected that 'any'
node can have subnodes.)RAW")
    .def("getKind", static_cast<OrgSemKind(org::sem::Org::*)() const>(&org::sem::Org::getKind), R"RAW(\brief Get kind of this sem node)RAW")
    .def("push_back",
         static_cast<void(org::sem::Org::*)(org::sem::SemId<org::sem::Org>)>(&org::sem::Org::push_back),
         nanobind::arg("sub"))
    .def("size", static_cast<int(org::sem::Org::*)() const>(&org::sem::Org::size))
    .def("insert",
         static_cast<void(org::sem::Org::*)(int, org::sem::SemId<org::sem::Org>)>(&org::sem::Org::insert),
         nanobind::arg("pos"),
         nanobind::arg("node"))
    .def("at",
         static_cast<org::sem::SemId<org::sem::Org>(org::sem::Org::*)(int) const>(&org::sem::Org::at),
         nanobind::arg("idx"))
    .def("is_",
         static_cast<bool(org::sem::Org::*)(OrgSemKind) const>(&org::sem::Org::is),
         nanobind::arg("kind"))
    .def("__getitem__",
         static_cast<org::sem::SemId<org::sem::Org>(org::sem::Org::*)(int) const>(&org::sem::Org::at),
         nanobind::arg("idx"))
    .def("__iter__",
         [](org::sem::Org const& node) -> auto {
         return nanobind::make_iterator(nanobind::type<org::sem::Org>(), "Org__iter__", node.begin(), node.end());
         },
         nanobind::keep_alive<0, 1>())
    ;
  nanobind::class_<hstd::OperationsTracer>(m, "OperationsTracer")
    .def("__init__",
         [](hstd::OperationsTracer* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::OperationsTracer();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("TraceState", &hstd::OperationsTracer::TraceState)
    .def_rw("traceToFile", &hstd::OperationsTracer::traceToFile)
    .def_rw("traceToBuffer", &hstd::OperationsTracer::traceToBuffer)
    .def_rw("traceStructured", &hstd::OperationsTracer::traceStructured)
    .def_rw("traceColored", &hstd::OperationsTracer::traceColored)
    .def_rw("activeLevel", &hstd::OperationsTracer::activeLevel)
    .def_rw("traceBuffer", &hstd::OperationsTracer::traceBuffer)
    .def("setTraceFileStr",
         static_cast<void(hstd::OperationsTracer::*)(std::string const&, bool)>(&hstd::OperationsTracer::setTraceFileStr),
         nanobind::arg("outfile"),
         nanobind::arg("overwrite"),
         R"RAW(\brief Helper method for reflection)RAW")
    .def("sendMessage",
         static_cast<void(hstd::OperationsTracer::*)(std::string const&, std::string const&, int, std::string const&)>(&hstd::OperationsTracer::sendMessage),
         nanobind::arg("value"),
         nanobind::arg("function"),
         nanobind::arg("line"),
         nanobind::arg("file"))
    .def("__repr__", [](hstd::OperationsTracer const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::OperationsTracer const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::Cache>(m, "Cache")
    ;
  nanobind::class_<org::parse::OrgParseFragment>(m, "parseOrgParseFragment")
    .def("__init__",
         [](org::parse::OrgParseFragment* result, nanobind::kwargs const& kwargs) {
         new(result) org::parse::OrgParseFragment();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("baseLine", &org::parse::OrgParseFragment::baseLine)
    .def_rw("baseCol", &org::parse::OrgParseFragment::baseCol)
    .def_rw("text", &org::parse::OrgParseFragment::text)
    .def("__repr__", [](org::parse::OrgParseFragment const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::parse::OrgParseFragment const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::parse::OrgParseParameters>(m, "OrgParseParameters")
    .def("__init__",
         [](org::parse::OrgParseParameters* result, nanobind::kwargs const& kwargs) {
         new(result) org::parse::OrgParseParameters();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("baseTokenTracePath", &org::parse::OrgParseParameters::baseTokenTracePath)
    .def_rw("tokenTracePath", &org::parse::OrgParseParameters::tokenTracePath)
    .def_rw("parseTracePath", &org::parse::OrgParseParameters::parseTracePath)
    .def_rw("semTracePath", &org::parse::OrgParseParameters::semTracePath)
    .def("__repr__", [](org::parse::OrgParseParameters const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::parse::OrgParseParameters const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::parse::OrgDirectoryParseParameters>(m, "OrgDirectoryParseParameters")
    .def("__init__",
         [](org::parse::OrgDirectoryParseParameters* result, nanobind::kwargs const& kwargs) {
         new(result) org::parse::OrgDirectoryParseParameters();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::parse::OrgDirectoryParseParameters const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::parse::OrgDirectoryParseParameters const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::parse::ParseContext>(m, "ParseContext")
    .def("__init__",
         [](org::parse::ParseContext* result, nanobind::kwargs const& kwargs) {
         new(result) org::parse::ParseContext();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getDiagnosticStrings", static_cast<std::shared_ptr<hstd::ext::Cache>(org::parse::ParseContext::*)()>(&org::parse::ParseContext::getDiagnosticStrings))
    .def("addSource",
         static_cast<org::parse::SourceFileId(org::parse::ParseContext::*)(std::string const&, std::string const&) const>(&org::parse::ParseContext::addSource),
         nanobind::arg("path"),
         nanobind::arg("content"))
    .def("parseFileOpts",
         static_cast<org::sem::SemId<org::sem::Org>(org::parse::ParseContext::*)(std::string const&, std::shared_ptr<org::parse::OrgParseParameters> const&)>(&org::parse::ParseContext::parseFileOpts),
         nanobind::arg("file"),
         nanobind::arg("opts"))
    .def("parseFile",
         static_cast<org::sem::SemId<org::sem::Org>(org::parse::ParseContext::*)(std::string const&)>(&org::parse::ParseContext::parseFile),
         nanobind::arg("file"))
    .def("parseString",
         static_cast<org::sem::SemId<org::sem::Org>(org::parse::ParseContext::*)(std::string const&, std::string const&)>(&org::parse::ParseContext::parseString),
         nanobind::arg("text"),
         nanobind::arg("file_name"))
    .def("parseStringOpts",
         static_cast<org::sem::SemId<org::sem::Org>(org::parse::ParseContext::*)(std::string const, std::string const&, std::shared_ptr<org::parse::OrgParseParameters> const&)>(&org::parse::ParseContext::parseStringOpts),
         nanobind::arg("text"),
         nanobind::arg("file_name"),
         nanobind::arg("opts"))
    .def("parseDirectory",
         static_cast<std::optional<org::sem::SemId<org::sem::Org>>(org::parse::ParseContext::*)(std::string const&)>(&org::parse::ParseContext::parseDirectory),
         nanobind::arg("path"))
    .def("parseDirectoryOpts",
         static_cast<std::optional<org::sem::SemId<org::sem::Org>>(org::parse::ParseContext::*)(std::string const&, std::shared_ptr<org::parse::OrgDirectoryParseParameters> const&)>(&org::parse::ParseContext::parseDirectoryOpts),
         nanobind::arg("path"),
         nanobind::arg("opts"))
    .def("parseFileWithIncludes",
         static_cast<org::sem::SemId<org::sem::File>(org::parse::ParseContext::*)(std::string const&, std::shared_ptr<org::parse::OrgDirectoryParseParameters> const&)>(&org::parse::ParseContext::parseFileWithIncludes),
         nanobind::arg("file"),
         nanobind::arg("opts"))
    .def("collectDiagnostics",
         static_cast<hstd::Vec<hstd::ext::Report>(org::parse::ParseContext::*)(org::sem::SemId<org::sem::Org> const&, std::shared_ptr<hstd::ext::Cache> const&)>(&org::parse::ParseContext::collectDiagnostics),
         nanobind::arg("tree"),
         nanobind::arg("cache"))
    .def("collectErrorNodes",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>(org::parse::ParseContext::*)(org::sem::SemId<org::sem::Org> const&)>(&org::parse::ParseContext::collectErrorNodes),
         nanobind::arg("tree"))
    .def("__repr__", [](org::parse::ParseContext const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::parse::ParseContext const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmId>(m, "ImmId")
    .def("__init__",
         [](org::imm::ImmId* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmId();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getKind", static_cast<OrgSemKind(org::imm::ImmId::*)() const>(&org::imm::ImmId::getKind))
    .def("is_",
         static_cast<bool(org::imm::ImmId::*)(OrgSemKind) const>(&org::imm::ImmId::is),
         nanobind::arg("kind"))
    .def("getNodeIndex", static_cast<org::imm::ImmId::NodeIdxT(org::imm::ImmId::*)() const>(&org::imm::ImmId::getNodeIndex), R"RAW(\brief Get index of the node in associated kind store. NOTE: The
node must not be nil)RAW")
    .def("getReadableId", static_cast<std::string(org::imm::ImmId::*)() const>(&org::imm::ImmId::getReadableId))
    .def("__repr__", [](org::imm::ImmId const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmId const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmOrg>(m, "ImmOrg")
    ;
  nanobind::class_<org::imm::ImmPathStep>(m, "ImmPathStep")
    .def("__init__",
         [](org::imm::ImmPathStep* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmPathStep();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::imm::ImmPathStep const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmPathStep const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmPath>(m, "ImmPath")
    .def("__init__",
         [](org::imm::ImmPath* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmPath();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("root", &org::imm::ImmPath::root, R"RAW(\brief Root ID node)RAW")
    .def_rw("path", &org::imm::ImmPath::path, R"RAW(\brief Sequence of jumps from the root of the document down to the
specified target node. For the path iteration structure see \see
ImmPathStep documentation.)RAW")
    .def("empty", static_cast<bool(org::imm::ImmPath::*)() const>(&org::imm::ImmPath::empty), R"RAW(\brief Empty path refers to the root of the document)RAW")
    .def("__repr__", [](org::imm::ImmPath const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmPath const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmUniqId>(m, "ImmUniqId")
    .def("__init__",
         [](org::imm::ImmUniqId* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmUniqId();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::imm::ImmUniqId const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmUniqId const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmAstReplaceEpoch>(m, "ImmAstReplaceEpoch")
    .def("__repr__", [](org::imm::ImmAstReplaceEpoch const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAstReplaceEpoch const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmAstContext>(m, "ImmAstContext")
    .def("addRoot",
         static_cast<org::imm::ImmAstVersion(org::imm::ImmAstContext::*)(org::sem::SemId<org::sem::Org>)>(&org::imm::ImmAstContext::addRoot),
         nanobind::arg("data"),
         R"RAW(\brief Add new root node to the store, create a new AST version
with a new root, new epoch and new AST context tracking the updated
state of the tree.)RAW")
    .def("getEmptyVersion", static_cast<org::imm::ImmAstVersion(org::imm::ImmAstContext::*)()>(&org::imm::ImmAstContext::getEmptyVersion), R"RAW(\brief Create empty AST version with no edits, no root, and linked
to the current context.)RAW")
    .def("get",
         static_cast<org::sem::SemId<org::sem::Org>(org::imm::ImmAstContext::*)(org::imm::ImmId)>(&org::imm::ImmAstContext::get),
         nanobind::arg("id"),
         R"RAW(\brief Convert immutable AST tree to the sem AST -- the sem AST is
created anew following the immutable ID structure.)RAW")
    .def("__repr__", [](org::imm::ImmAstContext const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAstContext const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmAstVersion>(m, "ImmAstVersion")
    .def("__init__",
         [](org::imm::ImmAstVersion* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmAstVersion();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getRoot", static_cast<org::imm::ImmId(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getRoot))
    .def("getRootAdapter", static_cast<org::imm::ImmAdapter(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getRootAdapter))
    .def("getContext", static_cast<std::shared_ptr<org::imm::ImmAstContext>(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getContext))
    .def("getEpoch", static_cast<std::shared_ptr<org::imm::ImmAstReplaceEpoch>(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getEpoch))
    .def("__repr__", [](org::imm::ImmAstVersion const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAstVersion const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmAdapter::TreeReprConf>(m, "ImmAdapterTreeReprConf")
    .def("__init__",
         [](org::imm::ImmAdapter::TreeReprConf* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmAdapter::TreeReprConf();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("maxDepth", &org::imm::ImmAdapter::TreeReprConf::maxDepth, R"RAW(\brief Do not print nodes that are more than N levels deep from
the root)RAW")
    .def_rw("withAuxFields", &org::imm::ImmAdapter::TreeReprConf::withAuxFields, R"RAW(\brief Include auxiliary subnodes in the tree repr -- `.title`
field and other locations outside of standard `.subnodes`)RAW")
    .def_rw("withReflFields", &org::imm::ImmAdapter::TreeReprConf::withReflFields, R"RAW(\brief Format full immutable node value as a part of tree repr)RAW")
    .def_rw("withFieldSubset", &org::imm::ImmAdapter::TreeReprConf::withFieldSubset, R"RAW(\brief Profide extra pretty-printed information for a given
field subset.)RAW")
    .def("__repr__", [](org::imm::ImmAdapter::TreeReprConf const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapter::TreeReprConf const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmAdapter>(m, "ImmAdapter")
    .def("size", static_cast<int(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::size))
    .def("isNil", static_cast<bool(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::isNil))
    .def("isRoot", static_cast<bool(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::isRoot))
    .def("getKind", static_cast<OrgSemKind(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getKind))
    .def("uniq", static_cast<org::imm::ImmUniqId(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::uniq))
    .def("treeReprString", static_cast<std::string(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::treeReprString))
    .def("treeReprStringOpts",
         static_cast<std::string(org::imm::ImmAdapter::*)(org::imm::ImmAdapter::TreeReprConf const&) const>(&org::imm::ImmAdapter::treeReprStringOpts),
         nanobind::arg("conf"))
    .def("isDirectParentOf",
         static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isDirectParentOf),
         nanobind::arg("other"))
    .def("isIndirectParentOf",
         static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isIndirectParentOf),
         nanobind::arg("other"))
    .def("isSubnodeOf",
         static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isSubnodeOf),
         nanobind::arg("other"))
    .def("getParent", static_cast<std::optional<org::imm::ImmAdapter>(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getParent))
    .def("getSelfIndex", static_cast<int(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getSelfIndex))
    .def("at",
         static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(org::imm::ImmReflFieldId const&) const>(&org::imm::ImmAdapter::at),
         nanobind::arg("field"))
    .def("at",
         static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(int, bool) const>(&org::imm::ImmAdapter::at),
         nanobind::arg("idx"),
         nanobind::arg("withPath") = 1)
    .def("at",
         static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(hstd::Vec<int> const&, bool) const>(&org::imm::ImmAdapter::at),
         nanobind::arg("path"),
         nanobind::arg("withPath") = 1)
    .def("is_",
         static_cast<bool(org::imm::ImmAdapter::*)(OrgSemKind) const>(&org::imm::ImmAdapter::is),
         nanobind::arg("kind"))
    .def("sub",
         static_cast<hstd::Vec<org::imm::ImmAdapter>(org::imm::ImmAdapter::*)(bool) const>(&org::imm::ImmAdapter::sub),
         nanobind::arg("withPath") = 1)
    .def("__repr__", [](org::imm::ImmAdapter const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmAdapter const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmAdapterVirtualBase>(m, "ImmAdapterVirtualBase")
    ;
  nanobind::class_<org::OrgYamlExportOpts>(m, "OrgYamlExportOpts")
    .def("__init__",
         [](org::OrgYamlExportOpts* result, nanobind::kwargs const& kwargs) {
         new(result) org::OrgYamlExportOpts();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("skipNullFields", &org::OrgYamlExportOpts::skipNullFields)
    .def_rw("skipFalseFields", &org::OrgYamlExportOpts::skipFalseFields)
    .def_rw("skipZeroFields", &org::OrgYamlExportOpts::skipZeroFields)
    .def_rw("skipLocation", &org::OrgYamlExportOpts::skipLocation)
    .def_rw("skipId", &org::OrgYamlExportOpts::skipId)
    .def("__repr__", [](org::OrgYamlExportOpts const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::OrgYamlExportOpts const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::OrgTreeExportOpts>(m, "OrgTreeExportOpts")
    .def("__init__",
         [](org::OrgTreeExportOpts* result, nanobind::kwargs const& kwargs) {
         new(result) org::OrgTreeExportOpts();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("withLineCol", &org::OrgTreeExportOpts::withLineCol)
    .def_rw("withOriginalId", &org::OrgTreeExportOpts::withOriginalId)
    .def_rw("withSubnodeIdx", &org::OrgTreeExportOpts::withSubnodeIdx)
    .def_rw("skipEmptyFields", &org::OrgTreeExportOpts::skipEmptyFields)
    .def_rw("startLevel", &org::OrgTreeExportOpts::startLevel)
    .def_rw("withColor", &org::OrgTreeExportOpts::withColor)
    .def_rw("maxDepth", &org::OrgTreeExportOpts::maxDepth)
    .def("__repr__", [](org::OrgTreeExportOpts const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::OrgTreeExportOpts const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::AstTrackingPath>(m, "AstTrackingPath")
    .def("__init__",
         [](org::AstTrackingPath* result, nanobind::kwargs const& kwargs) {
         new(result) org::AstTrackingPath();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("path", &org::AstTrackingPath::path)
    .def("getParent",
         static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingPath::*)(int) const>(&org::AstTrackingPath::getParent),
         nanobind::arg("offset") = 0)
    .def("getNode", static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingPath::*)() const>(&org::AstTrackingPath::getNode))
    .def("__repr__", [](org::AstTrackingPath const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::AstTrackingPath const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::AstTrackingAlternatives>(m, "AstTrackingAlternatives")
    .def("__init__",
         [](org::AstTrackingAlternatives* result, nanobind::kwargs const& kwargs) {
         new(result) org::AstTrackingAlternatives();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getAllNodes", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::AstTrackingAlternatives::*)() const>(&org::AstTrackingAlternatives::getAllNodes), R"RAW(\brief Return final nodes for all tracking alternatives.)RAW")
    .def("getNode", static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingAlternatives::*)() const>(&org::AstTrackingAlternatives::getNode), R"RAW(\brief Return first node from the alternatives.)RAW")
    .def("__repr__", [](org::AstTrackingAlternatives const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::AstTrackingAlternatives const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::AstTrackingGroup::RadioTarget>(m, "AstTrackingGroupRadioTarget")
    .def("__init__",
         [](org::AstTrackingGroup::RadioTarget* result, nanobind::kwargs const& kwargs) {
         new(result) org::AstTrackingGroup::RadioTarget();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("target", &org::AstTrackingGroup::RadioTarget::target)
    .def_rw("nodes", &org::AstTrackingGroup::RadioTarget::nodes)
    .def("__repr__", [](org::AstTrackingGroup::RadioTarget const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::AstTrackingGroup::RadioTarget const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::AstTrackingGroup::Single>(m, "AstTrackingGroupSingle")
    .def("__init__",
         [](org::AstTrackingGroup::Single* result, nanobind::kwargs const& kwargs) {
         new(result) org::AstTrackingGroup::Single();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("node", &org::AstTrackingGroup::Single::node)
    .def("__repr__", [](org::AstTrackingGroup::Single const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::AstTrackingGroup::Single const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::AstTrackingGroup::TrackedHashtag>(m, "AstTrackingGroupTrackedHashtag")
    .def("__init__",
         [](org::AstTrackingGroup::TrackedHashtag* result, nanobind::kwargs const& kwargs) {
         new(result) org::AstTrackingGroup::TrackedHashtag();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("tag", &org::AstTrackingGroup::TrackedHashtag::tag)
    .def_rw("targets", &org::AstTrackingGroup::TrackedHashtag::targets)
    .def("__repr__", [](org::AstTrackingGroup::TrackedHashtag const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::AstTrackingGroup::TrackedHashtag const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::AstTrackingGroup>(m, "AstTrackingGroup")
    .def("__init__",
         [](org::AstTrackingGroup* result, nanobind::kwargs const& kwargs) {
         new(result) org::AstTrackingGroup();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getRadioTarget", static_cast<org::AstTrackingGroup::RadioTarget const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getRadioTarget))
    .def("getTrackedHashtag", static_cast<org::AstTrackingGroup::TrackedHashtag&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getTrackedHashtag))
    .def("getSingle", static_cast<org::AstTrackingGroup::Single const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getSingle))
    .def("getRadioTarget", static_cast<org::AstTrackingGroup::RadioTarget&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getRadioTarget))
    .def("getSingle", static_cast<org::AstTrackingGroup::Single&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getSingle))
    .def("isSingle", static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isSingle))
    .def("isTrackedHashtag", static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isTrackedHashtag))
    .def("isRadioTarget", static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isRadioTarget))
    .def("__repr__", [](org::AstTrackingGroup const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::AstTrackingGroup const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::AstTrackingMap>(m, "AstTrackingMap")
    .def("__init__",
         [](org::AstTrackingMap* result, nanobind::kwargs const& kwargs) {
         new(result) org::AstTrackingMap();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("footnotes", &org::AstTrackingMap::footnotes)
    .def_rw("subtrees", &org::AstTrackingMap::subtrees)
    .def_rw("names", &org::AstTrackingMap::names)
    .def_rw("anchorTargets", &org::AstTrackingMap::anchorTargets)
    .def_rw("radioTargets", &org::AstTrackingMap::radioTargets)
    .def_rw("hashtagDefinitions", &org::AstTrackingMap::hashtagDefinitions)
    .def("getIdPath",
         static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getIdPath),
         nanobind::arg("id"))
    .def("getNamePath",
         static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getNamePath),
         nanobind::arg("id"))
    .def("getAnchorTarget",
         static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getAnchorTarget),
         nanobind::arg("id"))
    .def("getFootnotePath",
         static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getFootnotePath),
         nanobind::arg("id"))
    .def("__repr__", [](org::AstTrackingMap const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::AstTrackingMap const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::SequenceSegment>(m, "SequenceSegment")
    .def("__init__",
         [](hstd::SequenceSegment* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::SequenceSegment();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("kind", &hstd::SequenceSegment::kind, R"RAW(\brief Kind of the segment, does not have to be unique for all
segments, and different sequence segment groups can have segments
with identical kinds.)RAW")
    .def_rw("first", &hstd::SequenceSegment::first, R"RAW(\brief Inclusive left boundary of the segment. Mustnot overlap with
other segments' boundaries,but can be identical to the `last`,
to create a point segment (spans 1 element).)RAW")
    .def_rw("last", &hstd::SequenceSegment::last, R"RAW(\brief Inclusive right boundary for the segment)RAW")
    .def("__repr__", [](hstd::SequenceSegment const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::SequenceSegment const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::SequenceSegmentGroup>(m, "SequenceSegmentGroup")
    .def("__init__",
         [](hstd::SequenceSegmentGroup* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::SequenceSegmentGroup();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("kind", &hstd::SequenceSegmentGroup::kind, R"RAW(\brief An kind of the segment group, does not have to be unique)RAW")
    .def_rw("segments", &hstd::SequenceSegmentGroup::segments, R"RAW(\brief List of input segments for grouping)RAW")
    .def("__repr__", [](hstd::SequenceSegmentGroup const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::SequenceSegmentGroup const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::SequenceAnnotationTag>(m, "SequenceAnnotationTag")
    .def("__init__",
         [](hstd::SequenceAnnotationTag* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::SequenceAnnotationTag();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("groupKind", &hstd::SequenceAnnotationTag::groupKind, R"RAW(\brief ID of the original group this segment came from)RAW")
    .def_rw("segmentKinds", &hstd::SequenceAnnotationTag::segmentKinds, R"RAW(\brief ID of the segment in this group.

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
    .def("__repr__", [](hstd::SequenceAnnotationTag const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::SequenceAnnotationTag const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::SequenceAnnotation>(m, "SequenceAnnotation")
    .def("__init__",
         [](hstd::SequenceAnnotation* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::SequenceAnnotation();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("first", &hstd::SequenceAnnotation::first, R"RAW(\brief Inclusive left boundary for the sequence segment annotation)RAW")
    .def_rw("last", &hstd::SequenceAnnotation::last, R"RAW(\brief Inclusive right boundary for the sequence segment)RAW")
    .def_rw("annotations", &hstd::SequenceAnnotation::annotations, R"RAW(\brief Full list of all annotated segments.)RAW")
    .def("isAnnotatedWith",
         static_cast<bool(hstd::SequenceAnnotation::*)(int, int) const>(&hstd::SequenceAnnotation::isAnnotatedWith),
         nanobind::arg("groupKind"),
         nanobind::arg("segmentKind"),
         R"RAW(\brief Check if the segment is annotated with a given group kind
and a segment kind.)RAW")
    .def("__repr__", [](hstd::SequenceAnnotation const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::SequenceAnnotation const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::graph::MapLink::Link>(m, "graphMapLinkLink")
    .def("__init__",
         [](org::graph::MapLink::Link* result, nanobind::kwargs const& kwargs) {
         new(result) org::graph::MapLink::Link();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("link", &org::graph::MapLink::Link::link, R"RAW(\brief Original link used to create the graph edge. Used to
return an edge to unresolved state when target is deleted. When
source is deleted the edge is simply dropped.)RAW")
    .def_rw("description", &org::graph::MapLink::Link::description, R"RAW(MapLink description field can be reused or, for description
list items, this field contains a newly created statment list)RAW")
    .def("__repr__", [](org::graph::MapLink::Link const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::graph::MapLink::Link const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::graph::MapLink::Radio>(m, "graphMapLinkRadio")
    .def("__init__",
         [](org::graph::MapLink::Radio* result, nanobind::kwargs const& kwargs) {
         new(result) org::graph::MapLink::Radio();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("target", &org::graph::MapLink::Radio::target)
    .def("__repr__", [](org::graph::MapLink::Radio const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::graph::MapLink::Radio const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::graph::MapLink>(m, "graphMapLink")
    .def("__init__",
         [](org::graph::MapLink* result, nanobind::kwargs const& kwargs) {
         new(result) org::graph::MapLink();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getRadio", static_cast<org::graph::MapLink::Radio&(org::graph::MapLink::*)()>(&org::graph::MapLink::getRadio))
    .def("isRadio", static_cast<bool(org::graph::MapLink::*)() const>(&org::graph::MapLink::isRadio))
    .def("getLink", static_cast<org::graph::MapLink::Link&(org::graph::MapLink::*)()>(&org::graph::MapLink::getLink))
    .def("isLink", static_cast<bool(org::graph::MapLink::*)() const>(&org::graph::MapLink::isLink))
    .def("getKind", static_cast<org::graph::MapLink::Kind(org::graph::MapLink::*)() const>(&org::graph::MapLink::getKind))
    .def("__repr__", [](org::graph::MapLink const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::graph::MapLink const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::graph::MapNodeProp>(m, "graphMapNodeProp")
    .def("__init__",
         [](org::graph::MapNodeProp* result, nanobind::kwargs const& kwargs) {
         new(result) org::graph::MapNodeProp();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("id", &org::graph::MapNodeProp::id)
    .def_rw("unresolved", &org::graph::MapNodeProp::unresolved)
    .def("getAdapter",
         static_cast<org::imm::ImmAdapter(org::graph::MapNodeProp::*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&org::graph::MapNodeProp::getAdapter),
         nanobind::arg("context"))
    .def("getSubtreeId",
         static_cast<std::optional<hstd::Str>(org::graph::MapNodeProp::*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&org::graph::MapNodeProp::getSubtreeId),
         nanobind::arg("context"))
    .def("getFootnoteName",
         static_cast<std::optional<hstd::Str>(org::graph::MapNodeProp::*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&org::graph::MapNodeProp::getFootnoteName),
         nanobind::arg("context"))
    .def("__repr__", [](org::graph::MapNodeProp const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::graph::MapNodeProp const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::graph::MapEdgeProp>(m, "graphMapEdgeProp")
    .def("__init__",
         [](org::graph::MapEdgeProp* result, nanobind::kwargs const& kwargs) {
         new(result) org::graph::MapEdgeProp();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("link", &org::graph::MapEdgeProp::link)
    .def("__repr__", [](org::graph::MapEdgeProp const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::graph::MapEdgeProp const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::graph::MapNode>(m, "graphMapNode")
    .def("__init__",
         [](org::graph::MapNode* result, nanobind::kwargs const& kwargs) {
         new(result) org::graph::MapNode();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("id", &org::graph::MapNode::id)
    .def("__eq__",
         static_cast<bool(org::graph::MapNode::*)(org::graph::MapNode const&) const>(&org::graph::MapNode::operator==),
         nanobind::arg("other"))
    .def("__lt__",
         static_cast<bool(org::graph::MapNode::*)(org::graph::MapNode const&) const>(&org::graph::MapNode::operator<),
         nanobind::arg("other"))
    .def("__repr__", [](org::graph::MapNode const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::graph::MapNode const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::graph::MapEdge>(m, "graphMapEdge")
    .def("__init__",
         [](org::graph::MapEdge* result, nanobind::kwargs const& kwargs) {
         new(result) org::graph::MapEdge();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("source", &org::graph::MapEdge::source)
    .def_rw("target", &org::graph::MapEdge::target)
    .def("__repr__", [](org::graph::MapEdge const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::graph::MapEdge const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::graph::MapGraph>(m, "graphMapGraph")
    .def("__init__",
         [](org::graph::MapGraph* result, nanobind::kwargs const& kwargs) {
         new(result) org::graph::MapGraph();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("nodeProps", &org::graph::MapGraph::nodeProps)
    .def_rw("edgeProps", &org::graph::MapGraph::edgeProps)
    .def_rw("adjList", &org::graph::MapGraph::adjList)
    .def_rw("adjListIn", &org::graph::MapGraph::adjListIn)
    .def("nodeCount", static_cast<int(org::graph::MapGraph::*)() const>(&org::graph::MapGraph::nodeCount))
    .def("edgeCount", static_cast<int(org::graph::MapGraph::*)() const>(&org::graph::MapGraph::edgeCount))
    .def("outNodes",
         static_cast<org::graph::AdjNodesList const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outNodes),
         nanobind::arg("node"))
    .def("inNodes",
         static_cast<org::graph::AdjNodesList const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inNodes),
         nanobind::arg("node"))
    .def("adjEdges",
         static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::adjEdges),
         nanobind::arg("node"))
    .def("adjNodes",
         static_cast<hstd::Vec<org::graph::MapNode>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::adjNodes),
         nanobind::arg("node"))
    .def("outEdges",
         static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outEdges),
         nanobind::arg("node"))
    .def("inEdges",
         static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inEdges),
         nanobind::arg("node"))
    .def("outDegree",
         static_cast<int(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outDegree),
         nanobind::arg("node"))
    .def("inDegree",
         static_cast<int(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inDegree),
         nanobind::arg("node"))
    .def("isRegisteredNode",
         static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::isRegisteredNode),
         nanobind::arg("id"))
    .def("isRegisteredNode",
         static_cast<bool(org::graph::MapGraph::*)(org::imm::ImmUniqId const&) const>(&org::graph::MapGraph::isRegisteredNode),
         nanobind::arg("id"))
    .def("at",
         static_cast<org::graph::MapNodeProp const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::at),
         nanobind::arg("node"))
    .def("at",
         static_cast<org::graph::MapEdgeProp const&(org::graph::MapGraph::*)(org::graph::MapEdge const&) const>(&org::graph::MapGraph::at),
         nanobind::arg("edge"))
    .def("addEdge",
         static_cast<void(org::graph::MapGraph::*)(org::graph::MapEdge const&)>(&org::graph::MapGraph::addEdge),
         nanobind::arg("edge"))
    .def("addEdge",
         static_cast<void(org::graph::MapGraph::*)(org::graph::MapEdge const&, org::graph::MapEdgeProp const&)>(&org::graph::MapGraph::addEdge),
         nanobind::arg("edge"),
         nanobind::arg("prop"))
    .def("addNode",
         static_cast<void(org::graph::MapGraph::*)(org::graph::MapNode const&)>(&org::graph::MapGraph::addNode),
         nanobind::arg("node"),
         R"RAW(\brief Add node to the graph, without registering any outgoing or
ingoing elements.)RAW")
    .def("addNode",
         static_cast<void(org::graph::MapGraph::*)(org::graph::MapNode const&, org::graph::MapNodeProp const&)>(&org::graph::MapGraph::addNode),
         nanobind::arg("node"),
         nanobind::arg("prop"))
    .def("hasEdge",
         static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&, org::graph::MapNode const&) const>(&org::graph::MapGraph::hasEdge),
         nanobind::arg("source"),
         nanobind::arg("target"))
    .def("hasNode",
         static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::hasNode),
         nanobind::arg("node"))
    .def("hasEdge",
         static_cast<bool(org::graph::MapGraph::*)(org::imm::ImmAdapter const&, org::imm::ImmAdapter const&) const>(&org::graph::MapGraph::hasEdge),
         nanobind::arg("source"),
         nanobind::arg("target"))
    .def("__repr__", [](org::graph::MapGraph const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::graph::MapGraph const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::graph::MapConfig>(m, "graphMapConfig")
    .def("__init__",
         [](org::graph::MapConfig* result, nanobind::kwargs const& kwargs) {
         new(result) org::graph::MapConfig();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("dbg", &org::graph::MapConfig::dbg)
    .def("__repr__", [](org::graph::MapConfig const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::graph::MapConfig const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::graph::MapGraphState>(m, "graphMapGraphState")
    .def_rw("graph", &org::graph::MapGraphState::graph)
    .def_rw("ast", &org::graph::MapGraphState::ast)
    .def("getGraph", static_cast<std::shared_ptr<org::graph::MapGraph>(org::graph::MapGraphState::*)() const>(&org::graph::MapGraphState::getGraph))
    .def_static("FromAstContextStatic",
                static_cast<std::shared_ptr<org::graph::MapGraphState>(*)(std::shared_ptr<org::imm::ImmAstContext>)>(&org::graph::MapGraphState::FromAstContext),
                nanobind::arg("ast"))
    .def("registerNode",
         static_cast<void(org::graph::MapGraphState::*)(org::graph::MapNodeProp const&, std::shared_ptr<org::graph::MapConfig> const&)>(&org::graph::MapGraphState::registerNode),
         nanobind::arg("node"),
         nanobind::arg("conf"))
    .def("addNode",
         static_cast<void(org::graph::MapGraphState::*)(org::imm::ImmAdapter const&, std::shared_ptr<org::graph::MapConfig> const&)>(&org::graph::MapGraphState::addNode),
         nanobind::arg("node"),
         nanobind::arg("conf"))
    .def("addNodeRec",
         static_cast<void(org::graph::MapGraphState::*)(std::shared_ptr<org::imm::ImmAstContext> const&, org::imm::ImmAdapter const&, std::shared_ptr<org::graph::MapConfig> const&)>(&org::graph::MapGraphState::addNodeRec),
         nanobind::arg("ast"),
         nanobind::arg("node"),
         nanobind::arg("conf"))
    .def("getUnresolvedSubtreeLinks",
         static_cast<hstd::Vec<org::graph::MapLink>(org::graph::MapGraphState::*)(org::imm::ImmAdapterT<org::imm::ImmSubtree>, std::shared_ptr<org::graph::MapConfig> const&) const>(&org::graph::MapGraphState::getUnresolvedSubtreeLinks),
         nanobind::arg("node"),
         nanobind::arg("conf"))
    .def("getUnresolvedLink",
         static_cast<std::optional<org::graph::MapLink>(org::graph::MapGraphState::*)(org::imm::ImmAdapterT<org::imm::ImmLink>, std::shared_ptr<org::graph::MapConfig> const&) const>(&org::graph::MapGraphState::getUnresolvedLink),
         nanobind::arg("node"),
         nanobind::arg("conf"))
    .def("__repr__", [](org::graph::MapGraphState const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::graph::MapGraphState const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::bind::python::PyCodeEvalParameters>(m, "PyCodeEvalParameters")
    .def("__init__",
         [](org::bind::python::PyCodeEvalParameters* result, nanobind::kwargs const& kwargs) {
         new(result) org::bind::python::PyCodeEvalParameters();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("evalBlock", &org::bind::python::PyCodeEvalParameters::evalBlock)
    .def("setTraceFile",
         static_cast<void(org::bind::python::PyCodeEvalParameters::*)(std::string const&)>(&org::bind::python::PyCodeEvalParameters::setTraceFile),
         nanobind::arg("path"))
    .def("__repr__", [](org::bind::python::PyCodeEvalParameters const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::bind::python::PyCodeEvalParameters const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::bind::python::ExporterPython>(m, "ExporterPython")
    .def("__init__",
         [](org::bind::python::ExporterPython* result, nanobind::kwargs const& kwargs) {
         new(result) org::bind::python::ExporterPython();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("enableBufferTrace", static_cast<void(org::bind::python::ExporterPython::*)()>(&org::bind::python::ExporterPython::enableBufferTrace))
    .def("getTraceBuffer", static_cast<std::string(org::bind::python::ExporterPython::*)() const>(&org::bind::python::ExporterPython::getTraceBuffer))
    .def("enableFileTrace",
         static_cast<void(org::bind::python::ExporterPython::*)(std::string const&, bool)>(&org::bind::python::ExporterPython::enableFileTrace),
         nanobind::arg("path"),
         nanobind::arg("colored"))
    .def("setVisitAnyIdAround",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitAnyIdAround),
         nanobind::arg("cb"))
    .def("setVisitAnyIdIn",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitAnyIdIn),
         nanobind::arg("cb"))
    .def("setVisitAnyField",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitAnyField),
         nanobind::arg("cb"))
    .def("setEvalTopCb",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setEvalTopCb),
         nanobind::arg("cb"))
    .def("setVisitIdAround",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitIdAround),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setEvalIdAround",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setEvalIdAround),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setVisitIdInCb",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitIdInCb),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setEvalIdIn",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setEvalIdIn),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setVisitLeafField",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::LeafFieldType, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitLeafField),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setEvalLeafField",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::LeafFieldType, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setEvalLeafField),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setVisitOrgField",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitOrgField),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setEvalOrgField",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setEvalOrgField),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setSelf",
         static_cast<void(org::bind::python::ExporterPython::*)(nanobind::object)>(&org::bind::python::ExporterPython::setSelf),
         nanobind::arg("val"))
    .def("setNewOrgRes",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setNewOrgRes),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setNewAnyOrgRes",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setNewAnyOrgRes),
         nanobind::arg("cb"))
    .def("setNewLeafRes",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::LeafFieldType, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setNewLeafRes),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setNewAnyLeafRes",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setNewAnyLeafRes),
         nanobind::arg("cb"))
    .def("setPushVisitAnyId",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setPushVisitAnyId),
         nanobind::arg("cb"))
    .def("setPopVisitAnyId",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setPopVisitAnyId),
         nanobind::arg("cb"))
    .def("setPushVisitId",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setPushVisitId),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setPopVisitIdCb",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setPopVisitIdCb),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setVisitAnyHookCb",
         static_cast<void(org::bind::python::ExporterPython::*)(org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitAnyHookCb),
         nanobind::arg("cb"))
    .def("setVisitIdHook",
         static_cast<void(org::bind::python::ExporterPython::*)(OrgSemKind, org::bind::python::ExporterPython::PyFunc)>(&org::bind::python::ExporterPython::setVisitIdHook),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("print_trace",
         static_cast<void(org::bind::python::ExporterPython::*)(std::string const&, std::string const&, std::string const&, int)>(&org::bind::python::ExporterPython::print_trace),
         nanobind::arg("trace"),
         nanobind::arg("file"),
         nanobind::arg("function"),
         nanobind::arg("line"))
    .def("evalTop",
         static_cast<org::bind::python::ExporterPython::Res(org::bind::python::ExporterPython::*)(org::sem::SemId<org::sem::Org>)>(&org::bind::python::ExporterPython::evalTop),
         nanobind::arg("org"))
    .def("eval",
         static_cast<org::bind::python::ExporterPython::Res(org::bind::python::ExporterPython::*)(org::sem::SemId<org::sem::Org>)>(&org::bind::python::ExporterPython::eval),
         nanobind::arg("org"))
    .def("__repr__", [](org::bind::python::ExporterPython const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::bind::python::ExporterPython const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LispCode::Call>(m, "LispCodeCall")
    .def("__init__",
         [](org::sem::LispCode::Call* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LispCode::Call();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::LispCode::Call::name)
    .def_rw("args", &org::sem::LispCode::Call::args)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::Call::*)(org::sem::LispCode::Call const&) const>(&org::sem::LispCode::Call::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Call const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Call const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LispCode::List>(m, "LispCodeList")
    .def("__init__",
         [](org::sem::LispCode::List* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LispCode::List();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("items", &org::sem::LispCode::List::items)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::List::*)(org::sem::LispCode::List const&) const>(&org::sem::LispCode::List::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LispCode::List const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::List const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LispCode::KeyValue>(m, "LispCodeKeyValue")
    .def("__init__",
         [](org::sem::LispCode::KeyValue* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LispCode::KeyValue();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::LispCode::KeyValue::name)
    .def_rw("value", &org::sem::LispCode::KeyValue::value)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::KeyValue::*)(org::sem::LispCode::KeyValue const&) const>(&org::sem::LispCode::KeyValue::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LispCode::KeyValue const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::KeyValue const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LispCode::Number>(m, "LispCodeNumber")
    .def("__init__",
         [](org::sem::LispCode::Number* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LispCode::Number();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::LispCode::Number::value)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::Number::*)(org::sem::LispCode::Number const&) const>(&org::sem::LispCode::Number::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Number const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Number const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LispCode::Text>(m, "LispCodeText")
    .def("__init__",
         [](org::sem::LispCode::Text* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LispCode::Text();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::LispCode::Text::value)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::Text::*)(org::sem::LispCode::Text const&) const>(&org::sem::LispCode::Text::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Text const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Text const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LispCode::Ident>(m, "LispCodeIdent")
    .def("__init__",
         [](org::sem::LispCode::Ident* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LispCode::Ident();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::LispCode::Ident::name)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::Ident::*)(org::sem::LispCode::Ident const&) const>(&org::sem::LispCode::Ident::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Ident const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Ident const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LispCode::Boolean>(m, "LispCodeBoolean")
    .def("__init__",
         [](org::sem::LispCode::Boolean* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LispCode::Boolean();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::LispCode::Boolean::value)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::Boolean::*)(org::sem::LispCode::Boolean const&) const>(&org::sem::LispCode::Boolean::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Boolean const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Boolean const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LispCode::Real>(m, "LispCodeReal")
    .def("__init__",
         [](org::sem::LispCode::Real* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LispCode::Real();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::LispCode::Real::value)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::Real::*)(org::sem::LispCode::Real const&) const>(&org::sem::LispCode::Real::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Real const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Real const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::LispCode::Kind>(m, "LispCodeKind", type_registry_guard);
  nanobind::enum_<org::sem::LispCode::Kind>(m, "LispCodeKind")
    .value("Call", org::sem::LispCode::Kind::Call)
    .value("List", org::sem::LispCode::Kind::List)
    .value("KeyValue", org::sem::LispCode::Kind::KeyValue)
    .value("Number", org::sem::LispCode::Kind::Number)
    .value("Text", org::sem::LispCode::Kind::Text)
    .value("Ident", org::sem::LispCode::Kind::Ident)
    .value("Boolean", org::sem::LispCode::Kind::Boolean)
    .value("Real", org::sem::LispCode::Kind::Real)
    .def("__iter__", [](org::sem::LispCode::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::LispCode::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::LispCode::Kind>();
                     })
    .def("__eq__",
         [](org::sem::LispCode::Kind lhs, org::sem::LispCode::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::LispCode::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::LispCode>(m, "LispCode")
    .def("__init__",
         [](org::sem::LispCode* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LispCode();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("data", &org::sem::LispCode::data)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::*)(org::sem::LispCode const&) const>(&org::sem::LispCode::operator==),
         nanobind::arg("other"))
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
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::LispCode::Kind(org::sem::LispCode::*)() const>(&org::sem::LispCode::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::LispCode::*)() const>(&org::sem::LispCode::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::LispCode::Data const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::LispCode::Kind(org::sem::LispCode::*)() const>(&org::sem::LispCode::sub_variant_get_kind))
    .def("__repr__", [](org::sem::LispCode const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::AxisRef::Position::Index>(m, "TblfmExprAxisRefPositionIndex")
    .def("__init__",
         [](org::sem::Tblfm::Expr::AxisRef::Position::Index* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Tblfm::Expr::AxisRef::Position::Index();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("index", &org::sem::Tblfm::Expr::AxisRef::Position::Index::index)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::Index::*)(org::sem::Tblfm::Expr::AxisRef::Position::Index const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::Index::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::AxisRef::Position::Index const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::AxisRef::Position::Index const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::AxisRef::Position::Name>(m, "TblfmExprAxisRefPositionName")
    .def("__init__",
         [](org::sem::Tblfm::Expr::AxisRef::Position::Name* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Tblfm::Expr::AxisRef::Position::Name();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::Tblfm::Expr::AxisRef::Position::Name::name)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::Name::*)(org::sem::Tblfm::Expr::AxisRef::Position::Name const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::Name::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::AxisRef::Position::Name const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::AxisRef::Position::Name const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::Tblfm::Expr::AxisRef::Position::Kind>(m, "TblfmExprAxisRefPositionKind", type_registry_guard);
  nanobind::enum_<org::sem::Tblfm::Expr::AxisRef::Position::Kind>(m, "TblfmExprAxisRefPositionKind")
    .value("Index", org::sem::Tblfm::Expr::AxisRef::Position::Kind::Index)
    .value("Name", org::sem::Tblfm::Expr::AxisRef::Position::Kind::Name)
    .def("__iter__", [](org::sem::Tblfm::Expr::AxisRef::Position::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::Tblfm::Expr::AxisRef::Position::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::Tblfm::Expr::AxisRef::Position::Kind>();
                     })
    .def("__eq__",
         [](org::sem::Tblfm::Expr::AxisRef::Position::Kind lhs, org::sem::Tblfm::Expr::AxisRef::Position::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::Tblfm::Expr::AxisRef::Position::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::Tblfm::Expr::AxisRef::Position>(m, "TblfmExprAxisRefPosition")
    .def("__init__",
         [](org::sem::Tblfm::Expr::AxisRef::Position* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Tblfm::Expr::AxisRef::Position();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("data", &org::sem::Tblfm::Expr::AxisRef::Position::data)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)(org::sem::Tblfm::Expr::AxisRef::Position const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::operator==),
         nanobind::arg("other"))
    .def("isIndex", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::isIndex))
    .def("getIndex", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Index&(org::sem::Tblfm::Expr::AxisRef::Position::*)()>(&org::sem::Tblfm::Expr::AxisRef::Position::getIndex))
    .def("isName", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::isName))
    .def("getName", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Name&(org::sem::Tblfm::Expr::AxisRef::Position::*)()>(&org::sem::Tblfm::Expr::AxisRef::Position::getName))
    .def_static("getKindStatic",
                static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(*)(org::sem::Tblfm::Expr::AxisRef::Position::Data const&)>(&org::sem::Tblfm::Expr::AxisRef::Position::getKind),
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Data const&(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::sub_variant_get_kind))
    .def("__repr__", [](org::sem::Tblfm::Expr::AxisRef::Position const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::AxisRef::Position const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::AxisRef>(m, "TblfmExprAxisRef")
    .def("__init__",
         [](org::sem::Tblfm::Expr::AxisRef* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Tblfm::Expr::AxisRef();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("col", &org::sem::Tblfm::Expr::AxisRef::col)
    .def_rw("row", &org::sem::Tblfm::Expr::AxisRef::row)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::AxisRef::*)(org::sem::Tblfm::Expr::AxisRef const&) const>(&org::sem::Tblfm::Expr::AxisRef::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::AxisRef const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::AxisRef const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::AxisName>(m, "TblfmExprAxisName")
    .def("__init__",
         [](org::sem::Tblfm::Expr::AxisName* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Tblfm::Expr::AxisName();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::Tblfm::Expr::AxisName::name)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::AxisName::*)(org::sem::Tblfm::Expr::AxisName const&) const>(&org::sem::Tblfm::Expr::AxisName::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::AxisName const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::AxisName const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::IntLiteral>(m, "TblfmExprIntLiteral")
    .def("__init__",
         [](org::sem::Tblfm::Expr::IntLiteral* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Tblfm::Expr::IntLiteral();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::Tblfm::Expr::IntLiteral::value)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::IntLiteral::*)(org::sem::Tblfm::Expr::IntLiteral const&) const>(&org::sem::Tblfm::Expr::IntLiteral::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::IntLiteral const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::IntLiteral const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::FloatLiteral>(m, "TblfmExprFloatLiteral")
    .def("__init__",
         [](org::sem::Tblfm::Expr::FloatLiteral* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Tblfm::Expr::FloatLiteral();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::Tblfm::Expr::FloatLiteral::value)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::FloatLiteral::*)(org::sem::Tblfm::Expr::FloatLiteral const&) const>(&org::sem::Tblfm::Expr::FloatLiteral::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::FloatLiteral const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::FloatLiteral const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::RangeRef>(m, "TblfmExprRangeRef")
    .def("__init__",
         [](org::sem::Tblfm::Expr::RangeRef* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Tblfm::Expr::RangeRef();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("first", &org::sem::Tblfm::Expr::RangeRef::first)
    .def_rw("last", &org::sem::Tblfm::Expr::RangeRef::last)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::RangeRef::*)(org::sem::Tblfm::Expr::RangeRef const&) const>(&org::sem::Tblfm::Expr::RangeRef::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::RangeRef const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::RangeRef const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::Call>(m, "TblfmExprCall")
    .def("__init__",
         [](org::sem::Tblfm::Expr::Call* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Tblfm::Expr::Call();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::Tblfm::Expr::Call::name)
    .def_rw("args", &org::sem::Tblfm::Expr::Call::args)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::Call::*)(org::sem::Tblfm::Expr::Call const&) const>(&org::sem::Tblfm::Expr::Call::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::Call const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::Call const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::Elisp>(m, "TblfmExprElisp")
    .def("__init__",
         [](org::sem::Tblfm::Expr::Elisp* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Tblfm::Expr::Elisp();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::Tblfm::Expr::Elisp::value)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::Elisp::*)(org::sem::Tblfm::Expr::Elisp const&) const>(&org::sem::Tblfm::Expr::Elisp::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::Elisp const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::Elisp const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::Tblfm::Expr::Kind>(m, "TblfmExprKind", type_registry_guard);
  nanobind::enum_<org::sem::Tblfm::Expr::Kind>(m, "TblfmExprKind")
    .value("AxisRef", org::sem::Tblfm::Expr::Kind::AxisRef)
    .value("AxisName", org::sem::Tblfm::Expr::Kind::AxisName)
    .value("IntLiteral", org::sem::Tblfm::Expr::Kind::IntLiteral)
    .value("FloatLiteral", org::sem::Tblfm::Expr::Kind::FloatLiteral)
    .value("RangeRef", org::sem::Tblfm::Expr::Kind::RangeRef)
    .value("Call", org::sem::Tblfm::Expr::Kind::Call)
    .value("Elisp", org::sem::Tblfm::Expr::Kind::Elisp)
    .def("__iter__", [](org::sem::Tblfm::Expr::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::Tblfm::Expr::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::Tblfm::Expr::Kind>();
                     })
    .def("__eq__",
         [](org::sem::Tblfm::Expr::Kind lhs, org::sem::Tblfm::Expr::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::Tblfm::Expr::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::Tblfm::Expr>(m, "TblfmExpr")
    .def("__init__",
         [](org::sem::Tblfm::Expr* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Tblfm::Expr();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("data", &org::sem::Tblfm::Expr::data)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::*)(org::sem::Tblfm::Expr const&) const>(&org::sem::Tblfm::Expr::operator==),
         nanobind::arg("other"))
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
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::Tblfm::Expr::Kind(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::Tblfm::Expr::Data const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::Tblfm::Expr::Kind(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::sub_variant_get_kind))
    .def("__repr__", [](org::sem::Tblfm::Expr const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::Tblfm::Assign::Flag>(m, "TblfmAssignFlag", type_registry_guard);
  nanobind::enum_<org::sem::Tblfm::Assign::Flag>(m, "TblfmAssignFlag")
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
    .def("__iter__", [](org::sem::Tblfm::Assign::Flag const& _self) -> org::bind::python::PyEnumIterator<org::sem::Tblfm::Assign::Flag> {
                     return org::bind::python::PyEnumIterator<org::sem::Tblfm::Assign::Flag>();
                     })
    .def("__eq__",
         [](org::sem::Tblfm::Assign::Flag lhs, org::sem::Tblfm::Assign::Flag rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::Tblfm::Assign::Flag it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::Tblfm::Assign>(m, "TblfmAssign")
    .def("__init__",
         [](org::sem::Tblfm::Assign* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Tblfm::Assign();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("target", &org::sem::Tblfm::Assign::target)
    .def_rw("expr", &org::sem::Tblfm::Assign::expr)
    .def_rw("flags", &org::sem::Tblfm::Assign::flags)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Assign::*)(org::sem::Tblfm::Assign const&) const>(&org::sem::Tblfm::Assign::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Assign const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Assign const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm>(m, "Tblfm")
    .def("__init__",
         [](org::sem::Tblfm* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Tblfm();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("exprs", &org::sem::Tblfm::exprs)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::*)(org::sem::Tblfm const&) const>(&org::sem::Tblfm::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::AttrValue::DimensionSpan>(m, "AttrValueDimensionSpan")
    .def("__init__",
         [](org::sem::AttrValue::DimensionSpan* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::AttrValue::DimensionSpan();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("first", &org::sem::AttrValue::DimensionSpan::first)
    .def_rw("last", &org::sem::AttrValue::DimensionSpan::last)
    .def("__eq__",
         static_cast<bool(org::sem::AttrValue::DimensionSpan::*)(org::sem::AttrValue::DimensionSpan const&) const>(&org::sem::AttrValue::DimensionSpan::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::AttrValue::DimensionSpan const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrValue::DimensionSpan const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::AttrValue::TextValue>(m, "AttrValueTextValue")
    .def("__init__",
         [](org::sem::AttrValue::TextValue* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::AttrValue::TextValue();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::AttrValue::TextValue::value)
    .def("__eq__",
         static_cast<bool(org::sem::AttrValue::TextValue::*)(org::sem::AttrValue::TextValue const&) const>(&org::sem::AttrValue::TextValue::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::AttrValue::TextValue const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrValue::TextValue const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::AttrValue::FileReference>(m, "AttrValueFileReference")
    .def("__init__",
         [](org::sem::AttrValue::FileReference* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::AttrValue::FileReference();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("file", &org::sem::AttrValue::FileReference::file)
    .def_rw("reference", &org::sem::AttrValue::FileReference::reference)
    .def("__eq__",
         static_cast<bool(org::sem::AttrValue::FileReference::*)(org::sem::AttrValue::FileReference const&) const>(&org::sem::AttrValue::FileReference::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::AttrValue::FileReference const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrValue::FileReference const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::AttrValue::LispValue>(m, "AttrValueLispValue")
    .def("__init__",
         [](org::sem::AttrValue::LispValue* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::AttrValue::LispValue();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("code", &org::sem::AttrValue::LispValue::code)
    .def("__eq__",
         static_cast<bool(org::sem::AttrValue::LispValue::*)(org::sem::AttrValue::LispValue const&) const>(&org::sem::AttrValue::LispValue::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::AttrValue::LispValue const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrValue::LispValue const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::AttrValue::Kind>(m, "AttrValueKind", type_registry_guard);
  nanobind::enum_<org::sem::AttrValue::Kind>(m, "AttrValueKind")
    .value("TextValue", org::sem::AttrValue::Kind::TextValue)
    .value("FileReference", org::sem::AttrValue::Kind::FileReference)
    .value("LispValue", org::sem::AttrValue::Kind::LispValue)
    .def("__iter__", [](org::sem::AttrValue::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::AttrValue::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::AttrValue::Kind>();
                     })
    .def("__eq__",
         [](org::sem::AttrValue::Kind lhs, org::sem::AttrValue::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::AttrValue::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::AttrValue>(m, "AttrValue")
    .def("__init__",
         [](org::sem::AttrValue* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::AttrValue();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::AttrValue::name)
    .def_rw("varname", &org::sem::AttrValue::varname)
    .def_rw("span", &org::sem::AttrValue::span)
    .def_rw("isQuoted", &org::sem::AttrValue::isQuoted, R"RAW(If the original value was explicitly quoted in the org-mode code)RAW")
    .def_rw("data", &org::sem::AttrValue::data)
    .def("getBool", static_cast<hstd::Opt<bool>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getBool))
    .def("getInt", static_cast<hstd::Opt<int>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getInt))
    .def("getString", static_cast<hstd::Str(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getString))
    .def("getDouble", static_cast<hstd::Opt<double>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getDouble))
    .def("__eq__",
         static_cast<bool(org::sem::AttrValue::*)(org::sem::AttrValue const&) const>(&org::sem::AttrValue::operator==),
         nanobind::arg("other"))
    .def("isTextValue", static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isTextValue))
    .def("getTextValue", static_cast<org::sem::AttrValue::TextValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getTextValue))
    .def("isFileReference", static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isFileReference))
    .def("getFileReference", static_cast<org::sem::AttrValue::FileReference&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getFileReference))
    .def("isLispValue", static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isLispValue))
    .def("getLispValue", static_cast<org::sem::AttrValue::LispValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getLispValue))
    .def_static("getKindStatic",
                static_cast<org::sem::AttrValue::Kind(*)(org::sem::AttrValue::DataVariant const&)>(&org::sem::AttrValue::getKind),
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::AttrValue::Kind(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::AttrValue::DataVariant const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::AttrValue::Kind(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::sub_variant_get_kind))
    .def("__repr__", [](org::sem::AttrValue const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrValue const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::HashTagFlat>(m, "HashTagFlat")
    .def("__init__",
         [](org::sem::HashTagFlat* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::HashTagFlat();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("tags", &org::sem::HashTagFlat::tags)
    .def("__eq__",
         static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator==),
         nanobind::arg("other"))
    .def("__lt__",
         static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator<),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::HashTagFlat const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::HashTagFlat const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::TodoKeyword::Transition>(m, "TodoKeywordTransition", type_registry_guard);
  nanobind::enum_<org::sem::TodoKeyword::Transition>(m, "TodoKeywordTransition")
    .value("None", org::sem::TodoKeyword::Transition::None)
    .value("NoteWithTimestamp", org::sem::TodoKeyword::Transition::NoteWithTimestamp)
    .value("Timestamp", org::sem::TodoKeyword::Transition::Timestamp)
    .def("__iter__", [](org::sem::TodoKeyword::Transition const& _self) -> org::bind::python::PyEnumIterator<org::sem::TodoKeyword::Transition> {
                     return org::bind::python::PyEnumIterator<org::sem::TodoKeyword::Transition>();
                     })
    .def("__eq__",
         [](org::sem::TodoKeyword::Transition lhs, org::sem::TodoKeyword::Transition rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::TodoKeyword::Transition it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::TodoKeyword>(m, "TodoKeyword")
    .def("__init__",
         [](org::sem::TodoKeyword* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::TodoKeyword();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::TodoKeyword::name)
    .def_rw("shortcut", &org::sem::TodoKeyword::shortcut)
    .def_rw("onEnter", &org::sem::TodoKeyword::onEnter)
    .def_rw("onLeave", &org::sem::TodoKeyword::onLeave)
    .def("__eq__",
         static_cast<bool(org::sem::TodoKeyword::*)(org::sem::TodoKeyword const&) const>(&org::sem::TodoKeyword::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::TodoKeyword const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::TodoKeyword const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::HashTagText>(m, "HashTagText")
    .def("__init__",
         [](org::sem::HashTagText* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::HashTagText();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("head", &org::sem::HashTagText::head, R"RAW(Main part of the tag)RAW")
    .def_rw("subtags", &org::sem::HashTagText::subtags, R"RAW(List of nested tags)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::HashTagText::*)(org::sem::HashTagText const&) const>(&org::sem::HashTagText::operator==),
         nanobind::arg("other"))
    .def("prefixMatch",
         static_cast<bool(org::sem::HashTagText::*)(hstd::Vec<hstd::Str> const&) const>(&org::sem::HashTagText::prefixMatch),
         nanobind::arg("prefix"),
         R"RAW(Check if list of tag names is a prefix for either of the nested hash tags in this one)RAW")
    .def("getFlatHashes",
         static_cast<hstd::Vec<org::sem::HashTagFlat>(org::sem::HashTagText::*)(bool) const>(&org::sem::HashTagText::getFlatHashes),
         nanobind::arg("withIntermediate") = true,
         R"RAW(Get flat list of expanded hashtags)RAW")
    .def("__repr__", [](org::sem::HashTagText const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::HashTagText const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreePath>(m, "SubtreePath")
    .def("__init__",
         [](org::sem::SubtreePath* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::SubtreePath();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("path", &org::sem::SubtreePath::path)
    .def("__eq__",
         static_cast<bool(org::sem::SubtreePath::*)(org::sem::SubtreePath const&) const>(&org::sem::SubtreePath::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreePath const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreePath const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::Raw>(m, "LinkTargetRaw")
    .def("__init__",
         [](org::sem::LinkTarget::Raw* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LinkTarget::Raw();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::LinkTarget::Raw::text)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::Raw::*)(org::sem::LinkTarget::Raw const&) const>(&org::sem::LinkTarget::Raw::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Raw const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Raw const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::Id>(m, "LinkTargetId")
    .def("__init__",
         [](org::sem::LinkTarget::Id* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LinkTarget::Id();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::LinkTarget::Id::text)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::Id::*)(org::sem::LinkTarget::Id const&) const>(&org::sem::LinkTarget::Id::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Id const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Id const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::CustomId>(m, "LinkTargetCustomId")
    .def("__init__",
         [](org::sem::LinkTarget::CustomId* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LinkTarget::CustomId();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::LinkTarget::CustomId::text)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::CustomId::*)(org::sem::LinkTarget::CustomId const&) const>(&org::sem::LinkTarget::CustomId::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::CustomId const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::CustomId const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::SubtreeTitle>(m, "LinkTargetSubtreeTitle")
    .def("__init__",
         [](org::sem::LinkTarget::SubtreeTitle* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LinkTarget::SubtreeTitle();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("title", &org::sem::LinkTarget::SubtreeTitle::title)
    .def_rw("level", &org::sem::LinkTarget::SubtreeTitle::level)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::SubtreeTitle::*)(org::sem::LinkTarget::SubtreeTitle const&) const>(&org::sem::LinkTarget::SubtreeTitle::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::SubtreeTitle const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::SubtreeTitle const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::Person>(m, "LinkTargetPerson")
    .def("__init__",
         [](org::sem::LinkTarget::Person* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LinkTarget::Person();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::LinkTarget::Person::name)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::Person::*)(org::sem::LinkTarget::Person const&) const>(&org::sem::LinkTarget::Person::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Person const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Person const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::UserProtocol>(m, "LinkTargetUserProtocol")
    .def("__init__",
         [](org::sem::LinkTarget::UserProtocol* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LinkTarget::UserProtocol();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("protocol", &org::sem::LinkTarget::UserProtocol::protocol)
    .def_rw("target", &org::sem::LinkTarget::UserProtocol::target)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::UserProtocol::*)(org::sem::LinkTarget::UserProtocol const&) const>(&org::sem::LinkTarget::UserProtocol::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::UserProtocol const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::UserProtocol const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::Internal>(m, "LinkTargetInternal")
    .def("__init__",
         [](org::sem::LinkTarget::Internal* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LinkTarget::Internal();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("target", &org::sem::LinkTarget::Internal::target)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::Internal::*)(org::sem::LinkTarget::Internal const&) const>(&org::sem::LinkTarget::Internal::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Internal const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Internal const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::Footnote>(m, "LinkTargetFootnote")
    .def("__init__",
         [](org::sem::LinkTarget::Footnote* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LinkTarget::Footnote();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("target", &org::sem::LinkTarget::Footnote::target)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::Footnote::*)(org::sem::LinkTarget::Footnote const&) const>(&org::sem::LinkTarget::Footnote::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Footnote const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Footnote const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::File>(m, "LinkTargetFile")
    .def("__init__",
         [](org::sem::LinkTarget::File* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LinkTarget::File();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("file", &org::sem::LinkTarget::File::file)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::File::*)(org::sem::LinkTarget::File const&) const>(&org::sem::LinkTarget::File::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::File const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::File const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::Attachment>(m, "LinkTargetAttachment")
    .def("__init__",
         [](org::sem::LinkTarget::Attachment* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LinkTarget::Attachment();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("file", &org::sem::LinkTarget::Attachment::file)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::Attachment::*)(org::sem::LinkTarget::Attachment const&) const>(&org::sem::LinkTarget::Attachment::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Attachment const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Attachment const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::LinkTarget::Kind>(m, "LinkTargetKind", type_registry_guard);
  nanobind::enum_<org::sem::LinkTarget::Kind>(m, "LinkTargetKind")
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
    .def("__iter__", [](org::sem::LinkTarget::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::LinkTarget::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::LinkTarget::Kind>();
                     })
    .def("__eq__",
         [](org::sem::LinkTarget::Kind lhs, org::sem::LinkTarget::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::LinkTarget::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::LinkTarget>(m, "LinkTarget")
    .def("__init__",
         [](org::sem::LinkTarget* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::LinkTarget();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("data", &org::sem::LinkTarget::data)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::*)(org::sem::LinkTarget const&) const>(&org::sem::LinkTarget::operator==),
         nanobind::arg("other"))
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
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::LinkTarget::Kind(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::LinkTarget::Data const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::LinkTarget::Kind(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::sub_variant_get_kind))
    .def("__repr__", [](org::sem::LinkTarget const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::SubtreeLogHead::Priority::Action>(m, "SubtreeLogHeadPriorityAction", type_registry_guard);
  nanobind::enum_<org::sem::SubtreeLogHead::Priority::Action>(m, "SubtreeLogHeadPriorityAction")
    .value("Added", org::sem::SubtreeLogHead::Priority::Action::Added, R"RAW(`Priority B added on [timestamp]`)RAW")
    .value("Removed", org::sem::SubtreeLogHead::Priority::Action::Removed, R"RAW(`Priority C removed on [timestamp]`)RAW")
    .value("Changed", org::sem::SubtreeLogHead::Priority::Action::Changed, R"RAW(`Priority B changed from C on [timestamp]`)RAW")
    .def("__iter__", [](org::sem::SubtreeLogHead::Priority::Action const& _self) -> org::bind::python::PyEnumIterator<org::sem::SubtreeLogHead::Priority::Action> {
                     return org::bind::python::PyEnumIterator<org::sem::SubtreeLogHead::Priority::Action>();
                     })
    .def("__eq__",
         [](org::sem::SubtreeLogHead::Priority::Action lhs, org::sem::SubtreeLogHead::Priority::Action rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::SubtreeLogHead::Priority::Action it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::SubtreeLogHead::Priority>(m, "SubtreeLogHeadPriority")
    .def("__init__",
         [](org::sem::SubtreeLogHead::Priority* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::SubtreeLogHead::Priority();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("oldPriority", &org::sem::SubtreeLogHead::Priority::oldPriority, R"RAW(Previous priority for change and removal)RAW")
    .def_rw("newPriority", &org::sem::SubtreeLogHead::Priority::newPriority, R"RAW(New priority for change and addition)RAW")
    .def_rw("on", &org::sem::SubtreeLogHead::Priority::on, R"RAW(When priority was changed)RAW")
    .def_rw("action", &org::sem::SubtreeLogHead::Priority::action, R"RAW(Which action taken)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::Priority::*)(org::sem::SubtreeLogHead::Priority const&) const>(&org::sem::SubtreeLogHead::Priority::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Priority const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Priority const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLogHead::Note>(m, "SubtreeLogHeadNote")
    .def("__init__",
         [](org::sem::SubtreeLogHead::Note* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::SubtreeLogHead::Note();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("on", &org::sem::SubtreeLogHead::Note::on, R"RAW(Where log was taken)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::Note::*)(org::sem::SubtreeLogHead::Note const&) const>(&org::sem::SubtreeLogHead::Note::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Note const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Note const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLogHead::Refile>(m, "SubtreeLogHeadRefile")
    .def("__init__",
         [](org::sem::SubtreeLogHead::Refile* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::SubtreeLogHead::Refile();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("on", &org::sem::SubtreeLogHead::Refile::on, R"RAW(When the refiling happened)RAW")
    .def_rw("from_", &org::sem::SubtreeLogHead::Refile::from, R"RAW(Link to the original subtree)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::Refile::*)(org::sem::SubtreeLogHead::Refile const&) const>(&org::sem::SubtreeLogHead::Refile::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Refile const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Refile const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLogHead::Clock>(m, "SubtreeLogHeadClock")
    .def("__init__",
         [](org::sem::SubtreeLogHead::Clock* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::SubtreeLogHead::Clock();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("from_", &org::sem::SubtreeLogHead::Clock::from, R"RAW(Clock start time)RAW")
    .def_rw("to", &org::sem::SubtreeLogHead::Clock::to, R"RAW(Optional end of the clock)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::Clock::*)(org::sem::SubtreeLogHead::Clock const&) const>(&org::sem::SubtreeLogHead::Clock::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Clock const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Clock const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLogHead::State>(m, "SubtreeLogHeadState")
    .def("__init__",
         [](org::sem::SubtreeLogHead::State* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::SubtreeLogHead::State();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("from_", &org::sem::SubtreeLogHead::State::from)
    .def_rw("to", &org::sem::SubtreeLogHead::State::to)
    .def_rw("on", &org::sem::SubtreeLogHead::State::on)
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::State::*)(org::sem::SubtreeLogHead::State const&) const>(&org::sem::SubtreeLogHead::State::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::State const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::State const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLogHead::Deadline>(m, "SubtreeLogHeadDeadline")
    .def("__init__",
         [](org::sem::SubtreeLogHead::Deadline* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::SubtreeLogHead::Deadline();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("from_", &org::sem::SubtreeLogHead::Deadline::from)
    .def_rw("to", &org::sem::SubtreeLogHead::Deadline::to)
    .def_rw("on", &org::sem::SubtreeLogHead::Deadline::on)
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::Deadline::*)(org::sem::SubtreeLogHead::Deadline const&) const>(&org::sem::SubtreeLogHead::Deadline::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Deadline const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Deadline const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLogHead::Schedule>(m, "SubtreeLogHeadSchedule")
    .def("__init__",
         [](org::sem::SubtreeLogHead::Schedule* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::SubtreeLogHead::Schedule();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("from_", &org::sem::SubtreeLogHead::Schedule::from)
    .def_rw("to", &org::sem::SubtreeLogHead::Schedule::to)
    .def_rw("on", &org::sem::SubtreeLogHead::Schedule::on)
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::Schedule::*)(org::sem::SubtreeLogHead::Schedule const&) const>(&org::sem::SubtreeLogHead::Schedule::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Schedule const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Schedule const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLogHead::Tag>(m, "SubtreeLogHeadTag")
    .def("__init__",
         [](org::sem::SubtreeLogHead::Tag* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::SubtreeLogHead::Tag();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("on", &org::sem::SubtreeLogHead::Tag::on, R"RAW(When the log was assigned)RAW")
    .def_rw("tag", &org::sem::SubtreeLogHead::Tag::tag, R"RAW(Tag in question)RAW")
    .def_rw("added", &org::sem::SubtreeLogHead::Tag::added, R"RAW(Added/removed?)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::Tag::*)(org::sem::SubtreeLogHead::Tag const&) const>(&org::sem::SubtreeLogHead::Tag::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Tag const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Tag const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLogHead::Unknown>(m, "SubtreeLogHeadUnknown")
    .def("__init__",
         [](org::sem::SubtreeLogHead::Unknown* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::SubtreeLogHead::Unknown();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::Unknown::*)(org::sem::SubtreeLogHead::Unknown const&) const>(&org::sem::SubtreeLogHead::Unknown::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Unknown const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Unknown const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::SubtreeLogHead::Kind>(m, "SubtreeLogHeadKind", type_registry_guard);
  nanobind::enum_<org::sem::SubtreeLogHead::Kind>(m, "SubtreeLogHeadKind")
    .value("Priority", org::sem::SubtreeLogHead::Kind::Priority)
    .value("Note", org::sem::SubtreeLogHead::Kind::Note)
    .value("Refile", org::sem::SubtreeLogHead::Kind::Refile)
    .value("Clock", org::sem::SubtreeLogHead::Kind::Clock)
    .value("State", org::sem::SubtreeLogHead::Kind::State)
    .value("Deadline", org::sem::SubtreeLogHead::Kind::Deadline)
    .value("Schedule", org::sem::SubtreeLogHead::Kind::Schedule)
    .value("Tag", org::sem::SubtreeLogHead::Kind::Tag)
    .value("Unknown", org::sem::SubtreeLogHead::Kind::Unknown)
    .def("__iter__", [](org::sem::SubtreeLogHead::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::SubtreeLogHead::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::SubtreeLogHead::Kind>();
                     })
    .def("__eq__",
         [](org::sem::SubtreeLogHead::Kind lhs, org::sem::SubtreeLogHead::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::SubtreeLogHead::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::SubtreeLogHead>(m, "SubtreeLogHead")
    .def("__init__",
         [](org::sem::SubtreeLogHead* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::SubtreeLogHead();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("log", &org::sem::SubtreeLogHead::log)
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::*)(org::sem::SubtreeLogHead const&) const>(&org::sem::SubtreeLogHead::operator==),
         nanobind::arg("other"))
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
                nanobind::arg("__input"))
    .def("getLogKind", static_cast<org::sem::SubtreeLogHead::Kind(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getLogKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::SubtreeLogHead::LogEntry const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::SubtreeLogHead::Kind(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::sub_variant_get_kind))
    .def("__repr__", [](org::sem::SubtreeLogHead const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeCompletion>(m, "SubtreeCompletion")
    .def("__init__",
         [](org::sem::SubtreeCompletion* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::SubtreeCompletion();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("done", &org::sem::SubtreeCompletion::done, R"RAW(Number of completed tasks)RAW")
    .def_rw("full", &org::sem::SubtreeCompletion::full, R"RAW(Full number of tasks)RAW")
    .def_rw("isPercent", &org::sem::SubtreeCompletion::isPercent, R"RAW(Use fraction or percent to display completion)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeCompletion::*)(org::sem::SubtreeCompletion const&) const>(&org::sem::SubtreeCompletion::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeCompletion const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeCompletion const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::AttrList>(m, "AttrList")
    .def("__init__",
         [](org::sem::AttrList* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::AttrList();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("items", &org::sem::AttrList::items)
    .def("__eq__",
         static_cast<bool(org::sem::AttrList::*)(org::sem::AttrList const&) const>(&org::sem::AttrList::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::AttrList const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrList const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::AttrGroup>(m, "AttrGroup")
    .def("__init__",
         [](org::sem::AttrGroup* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::AttrGroup();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("positional", &org::sem::AttrGroup::positional, R"RAW(Positional arguments with no keys)RAW")
    .def_rw("named", &org::sem::AttrGroup::named, R"RAW(Stored key-value mapping)RAW")
    .def("getFlatArgs", static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getFlatArgs))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::AttrGroup::getAttrs),
         nanobind::arg("key") = std::nullopt)
    .def("setNamedAttr",
         static_cast<void(org::sem::AttrGroup::*)(hstd::Str const&, hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setNamedAttr),
         nanobind::arg("key"),
         nanobind::arg("attrs"))
    .def("setPositionalAttr",
         static_cast<void(org::sem::AttrGroup::*)(hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setPositionalAttr),
         nanobind::arg("items"))
    .def("getPositionalSize", static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getPositionalSize))
    .def("getNamedSize", static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getNamedSize))
    .def("isEmpty", static_cast<bool(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::isEmpty))
    .def("getAll", static_cast<org::sem::AttrList(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getAll))
    .def("atPositional",
         static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::atPositional),
         nanobind::arg("index"))
    .def("getPositional",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::getPositional),
         nanobind::arg("index"))
    .def("atNamed",
         static_cast<org::sem::AttrList const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atNamed),
         nanobind::arg("index"))
    .def("getNamed",
         static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getNamed),
         nanobind::arg("index"))
    .def("atFirstNamed",
         static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstNamed),
         nanobind::arg("index"))
    .def("getFirstNamed",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstNamed),
         nanobind::arg("index"))
    .def("atVarNamed",
         static_cast<org::sem::AttrList(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atVarNamed),
         nanobind::arg("index"))
    .def("getVarNamed",
         static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getVarNamed),
         nanobind::arg("index"))
    .def("atFirstVarNamed",
         static_cast<org::sem::AttrValue(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstVarNamed),
         nanobind::arg("index"))
    .def("getFirstVarNamed",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstVarNamed),
         nanobind::arg("index"))
    .def("__eq__",
         static_cast<bool(org::sem::AttrGroup::*)(org::sem::AttrGroup const&) const>(&org::sem::AttrGroup::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::AttrGroup const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrGroup const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::OrgCodeEvalInput::Var>(m, "OrgCodeEvalInputVar")
    .def("__init__",
         [](org::sem::OrgCodeEvalInput::Var* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::OrgCodeEvalInput::Var();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::OrgCodeEvalInput::Var::name)
    .def_rw("value", &org::sem::OrgCodeEvalInput::Var::value)
    .def("__eq__",
         static_cast<bool(org::sem::OrgCodeEvalInput::Var::*)(org::sem::OrgCodeEvalInput::Var const&) const>(&org::sem::OrgCodeEvalInput::Var::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::OrgCodeEvalInput::Var const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgCodeEvalInput::Var const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::OrgCodeEvalInput::ResultType>(m, "OrgCodeEvalInputResultType", type_registry_guard);
  nanobind::enum_<org::sem::OrgCodeEvalInput::ResultType>(m, "OrgCodeEvalInputResultType")
    .value("None", org::sem::OrgCodeEvalInput::ResultType::None)
    .value("Table", org::sem::OrgCodeEvalInput::ResultType::Table, R"RAW(Interpret the results as an Org table. If the result is a single value, create a table with one row and one column.)RAW")
    .value("List", org::sem::OrgCodeEvalInput::ResultType::List, R"RAW(Interpret the results as an Org list. If the result is a single value, create a list of one element.)RAW")
    .value("Scalar", org::sem::OrgCodeEvalInput::ResultType::Scalar, R"RAW(Interpret literally and insert as quoted text. Do not create a table.)RAW")
    .value("SaveFile", org::sem::OrgCodeEvalInput::ResultType::SaveFile, R"RAW(Interpret as a filename. Save the results of execution of the code block to that file, then insert a link to it.)RAW")
    .def("__iter__", [](org::sem::OrgCodeEvalInput::ResultType const& _self) -> org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultType> {
                     return org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultType>();
                     })
    .def("__eq__",
         [](org::sem::OrgCodeEvalInput::ResultType lhs, org::sem::OrgCodeEvalInput::ResultType rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::OrgCodeEvalInput::ResultType it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org::sem::OrgCodeEvalInput::ResultFormat>(m, "OrgCodeEvalInputResultFormat", type_registry_guard);
  nanobind::enum_<org::sem::OrgCodeEvalInput::ResultFormat>(m, "OrgCodeEvalInputResultFormat")
    .value("None", org::sem::OrgCodeEvalInput::ResultFormat::None)
    .value("Raw", org::sem::OrgCodeEvalInput::ResultFormat::Raw, R"RAW(Interpreted as raw Org mode. Inserted directly into the buffer.)RAW")
    .value("Code", org::sem::OrgCodeEvalInput::ResultFormat::Code, R"RAW(Result enclosed in a code block.)RAW")
    .value("Drawer", org::sem::OrgCodeEvalInput::ResultFormat::Drawer, R"RAW(Results are added directly to the Org file as with ‘raw’, but are wrapped in a ‘RESULTS’ drawer or results macro (for inline code blocks), for later scripting and automated processing.)RAW")
    .value("ExportType", org::sem::OrgCodeEvalInput::ResultFormat::ExportType, R"RAW(Results enclosed in a ‘BEGIN_EXPORT’ block.)RAW")
    .value("Link", org::sem::OrgCodeEvalInput::ResultFormat::Link)
    .def("__iter__", [](org::sem::OrgCodeEvalInput::ResultFormat const& _self) -> org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultFormat> {
                     return org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultFormat>();
                     })
    .def("__eq__",
         [](org::sem::OrgCodeEvalInput::ResultFormat lhs, org::sem::OrgCodeEvalInput::ResultFormat rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::OrgCodeEvalInput::ResultFormat it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org::sem::OrgCodeEvalInput::ResultHandling>(m, "OrgCodeEvalInputResultHandling", type_registry_guard);
  nanobind::enum_<org::sem::OrgCodeEvalInput::ResultHandling>(m, "OrgCodeEvalInputResultHandling")
    .value("None", org::sem::OrgCodeEvalInput::ResultHandling::None)
    .value("Replace", org::sem::OrgCodeEvalInput::ResultHandling::Replace)
    .value("Silent", org::sem::OrgCodeEvalInput::ResultHandling::Silent)
    .value("Discard", org::sem::OrgCodeEvalInput::ResultHandling::Discard)
    .value("Append", org::sem::OrgCodeEvalInput::ResultHandling::Append)
    .value("Prepend", org::sem::OrgCodeEvalInput::ResultHandling::Prepend)
    .def("__iter__", [](org::sem::OrgCodeEvalInput::ResultHandling const& _self) -> org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultHandling> {
                     return org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultHandling>();
                     })
    .def("__eq__",
         [](org::sem::OrgCodeEvalInput::ResultHandling lhs, org::sem::OrgCodeEvalInput::ResultHandling rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::OrgCodeEvalInput::ResultHandling it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::OrgCodeEvalInput>(m, "OrgCodeEvalInput")
    .def("__init__",
         [](org::sem::OrgCodeEvalInput* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::OrgCodeEvalInput();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("blockAttrs", &org::sem::OrgCodeEvalInput::blockAttrs)
    .def_rw("tangledCode", &org::sem::OrgCodeEvalInput::tangledCode)
    .def_rw("exportType", &org::sem::OrgCodeEvalInput::exportType)
    .def_rw("resultType", &org::sem::OrgCodeEvalInput::resultType)
    .def_rw("resultFormat", &org::sem::OrgCodeEvalInput::resultFormat)
    .def_rw("resultHandling", &org::sem::OrgCodeEvalInput::resultHandling)
    .def_rw("language", &org::sem::OrgCodeEvalInput::language)
    .def_rw("argList", &org::sem::OrgCodeEvalInput::argList)
    .def("__eq__",
         static_cast<bool(org::sem::OrgCodeEvalInput::*)(org::sem::OrgCodeEvalInput const&) const>(&org::sem::OrgCodeEvalInput::operator==),
         nanobind::arg("other"))
    .def("getVariable",
         static_cast<hstd::Opt<org::sem::OrgCodeEvalInput::Var>(org::sem::OrgCodeEvalInput::*)(hstd::Str const&) const>(&org::sem::OrgCodeEvalInput::getVariable),
         nanobind::arg("name"))
    .def("__repr__", [](org::sem::OrgCodeEvalInput const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgCodeEvalInput const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::OrgCodeEvalOutput>(m, "OrgCodeEvalOutput")
    .def("__init__",
         [](org::sem::OrgCodeEvalOutput* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::OrgCodeEvalOutput();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("stdoutText", &org::sem::OrgCodeEvalOutput::stdoutText)
    .def_rw("stderrText", &org::sem::OrgCodeEvalOutput::stderrText)
    .def_rw("code", &org::sem::OrgCodeEvalOutput::code)
    .def_rw("cmd", &org::sem::OrgCodeEvalOutput::cmd, R"RAW(Command evaluated, if none then eval output did not run CLI subprocess)RAW")
    .def_rw("args", &org::sem::OrgCodeEvalOutput::args, R"RAW(Command line arguments provided for execution)RAW")
    .def_rw("cwd", &org::sem::OrgCodeEvalOutput::cwd, R"RAW(Working directory where command was executed)RAW")
    .def_rw("appliedHeaderArg", &org::sem::OrgCodeEvalOutput::appliedHeaderArg, R"RAW(Final set of header arguments applied during evaluation)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::OrgCodeEvalOutput::*)(org::sem::OrgCodeEvalOutput const&) const>(&org::sem::OrgCodeEvalOutput::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::OrgCodeEvalOutput const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgCodeEvalOutput const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::ColumnView::Summary::CheckboxAggregate::Kind>(m, "ColumnViewSummaryCheckboxAggregateKind", type_registry_guard);
  nanobind::enum_<org::sem::ColumnView::Summary::CheckboxAggregate::Kind>(m, "ColumnViewSummaryCheckboxAggregateKind")
    .value("IfAllNested", org::sem::ColumnView::Summary::CheckboxAggregate::Kind::IfAllNested)
    .value("AggregateFractionRec", org::sem::ColumnView::Summary::CheckboxAggregate::Kind::AggregateFractionRec)
    .value("AggregatePercentRec", org::sem::ColumnView::Summary::CheckboxAggregate::Kind::AggregatePercentRec)
    .def("__iter__", [](org::sem::ColumnView::Summary::CheckboxAggregate::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::CheckboxAggregate::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::CheckboxAggregate::Kind>();
                     })
    .def("__eq__",
         [](org::sem::ColumnView::Summary::CheckboxAggregate::Kind lhs, org::sem::ColumnView::Summary::CheckboxAggregate::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::ColumnView::Summary::CheckboxAggregate::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::ColumnView::Summary::CheckboxAggregate>(m, "ColumnViewSummaryCheckboxAggregate")
    .def("__init__",
         [](org::sem::ColumnView::Summary::CheckboxAggregate* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::ColumnView::Summary::CheckboxAggregate();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("kind", &org::sem::ColumnView::Summary::CheckboxAggregate::kind)
    .def("__eq__",
         static_cast<bool(org::sem::ColumnView::Summary::CheckboxAggregate::*)(org::sem::ColumnView::Summary::CheckboxAggregate const&) const>(&org::sem::ColumnView::Summary::CheckboxAggregate::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::ColumnView::Summary::CheckboxAggregate const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColumnView::Summary::CheckboxAggregate const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::ColumnView::Summary::MathAggregate::Kind>(m, "ColumnViewSummaryMathAggregateKind", type_registry_guard);
  nanobind::enum_<org::sem::ColumnView::Summary::MathAggregate::Kind>(m, "ColumnViewSummaryMathAggregateKind")
    .value("Min", org::sem::ColumnView::Summary::MathAggregate::Kind::Min)
    .value("Max", org::sem::ColumnView::Summary::MathAggregate::Kind::Max)
    .value("Mean", org::sem::ColumnView::Summary::MathAggregate::Kind::Mean)
    .value("Sum", org::sem::ColumnView::Summary::MathAggregate::Kind::Sum)
    .value("LowHighEst", org::sem::ColumnView::Summary::MathAggregate::Kind::LowHighEst)
    .def("__iter__", [](org::sem::ColumnView::Summary::MathAggregate::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::MathAggregate::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::MathAggregate::Kind>();
                     })
    .def("__eq__",
         [](org::sem::ColumnView::Summary::MathAggregate::Kind lhs, org::sem::ColumnView::Summary::MathAggregate::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::ColumnView::Summary::MathAggregate::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::ColumnView::Summary::MathAggregate>(m, "ColumnViewSummaryMathAggregate")
    .def("__init__",
         [](org::sem::ColumnView::Summary::MathAggregate* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::ColumnView::Summary::MathAggregate();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("kind", &org::sem::ColumnView::Summary::MathAggregate::kind)
    .def_rw("formatDigits", &org::sem::ColumnView::Summary::MathAggregate::formatDigits)
    .def_rw("formatPrecision", &org::sem::ColumnView::Summary::MathAggregate::formatPrecision)
    .def("__eq__",
         static_cast<bool(org::sem::ColumnView::Summary::MathAggregate::*)(org::sem::ColumnView::Summary::MathAggregate const&) const>(&org::sem::ColumnView::Summary::MathAggregate::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::ColumnView::Summary::MathAggregate const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColumnView::Summary::MathAggregate const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::ColumnView::Summary::Kind>(m, "ColumnViewSummaryKind", type_registry_guard);
  nanobind::enum_<org::sem::ColumnView::Summary::Kind>(m, "ColumnViewSummaryKind")
    .value("CheckboxAggregate", org::sem::ColumnView::Summary::Kind::CheckboxAggregate)
    .value("MathAggregate", org::sem::ColumnView::Summary::Kind::MathAggregate)
    .def("__iter__", [](org::sem::ColumnView::Summary::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::Kind>();
                     })
    .def("__eq__",
         [](org::sem::ColumnView::Summary::Kind lhs, org::sem::ColumnView::Summary::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::ColumnView::Summary::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::ColumnView::Summary>(m, "ColumnViewSummary")
    .def("__init__",
         [](org::sem::ColumnView::Summary* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::ColumnView::Summary();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("data", &org::sem::ColumnView::Summary::data)
    .def("__eq__",
         static_cast<bool(org::sem::ColumnView::Summary::*)(org::sem::ColumnView::Summary const&) const>(&org::sem::ColumnView::Summary::operator==),
         nanobind::arg("other"))
    .def("isCheckboxAggregate", static_cast<bool(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::isCheckboxAggregate))
    .def("getCheckboxAggregate", static_cast<org::sem::ColumnView::Summary::CheckboxAggregate&(org::sem::ColumnView::Summary::*)()>(&org::sem::ColumnView::Summary::getCheckboxAggregate))
    .def("isMathAggregate", static_cast<bool(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::isMathAggregate))
    .def("getMathAggregate", static_cast<org::sem::ColumnView::Summary::MathAggregate&(org::sem::ColumnView::Summary::*)()>(&org::sem::ColumnView::Summary::getMathAggregate))
    .def_static("getKindStatic",
                static_cast<org::sem::ColumnView::Summary::Kind(*)(org::sem::ColumnView::Summary::Data const&)>(&org::sem::ColumnView::Summary::getKind),
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::ColumnView::Summary::Kind(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::ColumnView::Summary::Data const&(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::ColumnView::Summary::Kind(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::sub_variant_get_kind))
    .def("__repr__", [](org::sem::ColumnView::Summary const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColumnView::Summary const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::ColumnView::Column>(m, "ColumnViewColumn")
    .def("__init__",
         [](org::sem::ColumnView::Column* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::ColumnView::Column();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("summary", &org::sem::ColumnView::Column::summary)
    .def_rw("width", &org::sem::ColumnView::Column::width)
    .def_rw("property", &org::sem::ColumnView::Column::property)
    .def_rw("propertyTitle", &org::sem::ColumnView::Column::propertyTitle)
    .def("__eq__",
         static_cast<bool(org::sem::ColumnView::Column::*)(org::sem::ColumnView::Column const&) const>(&org::sem::ColumnView::Column::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::ColumnView::Column const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColumnView::Column const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::ColumnView>(m, "ColumnView")
    .def("__init__",
         [](org::sem::ColumnView* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::ColumnView();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("columns", &org::sem::ColumnView::columns)
    .def("__eq__",
         static_cast<bool(org::sem::ColumnView::*)(org::sem::ColumnView const&) const>(&org::sem::ColumnView::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::ColumnView const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColumnView const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockCodeLine::Part::Raw>(m, "BlockCodeLinePartRaw")
    .def("__init__",
         [](org::sem::BlockCodeLine::Part::Raw* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::BlockCodeLine::Part::Raw();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("code", &org::sem::BlockCodeLine::Part::Raw::code)
    .def("__eq__",
         static_cast<bool(org::sem::BlockCodeLine::Part::Raw::*)(org::sem::BlockCodeLine::Part::Raw const&) const>(&org::sem::BlockCodeLine::Part::Raw::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::BlockCodeLine::Part::Raw const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeLine::Part::Raw const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockCodeLine::Part::Callout>(m, "BlockCodeLinePartCallout")
    .def("__init__",
         [](org::sem::BlockCodeLine::Part::Callout* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::BlockCodeLine::Part::Callout();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::BlockCodeLine::Part::Callout::name)
    .def("__eq__",
         static_cast<bool(org::sem::BlockCodeLine::Part::Callout::*)(org::sem::BlockCodeLine::Part::Callout const&) const>(&org::sem::BlockCodeLine::Part::Callout::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::BlockCodeLine::Part::Callout const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeLine::Part::Callout const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockCodeLine::Part::Tangle>(m, "BlockCodeLinePartTangle")
    .def("__init__",
         [](org::sem::BlockCodeLine::Part::Tangle* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::BlockCodeLine::Part::Tangle();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("target", &org::sem::BlockCodeLine::Part::Tangle::target)
    .def("__eq__",
         static_cast<bool(org::sem::BlockCodeLine::Part::Tangle::*)(org::sem::BlockCodeLine::Part::Tangle const&) const>(&org::sem::BlockCodeLine::Part::Tangle::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::BlockCodeLine::Part::Tangle const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeLine::Part::Tangle const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::BlockCodeLine::Part::Kind>(m, "BlockCodeLinePartKind", type_registry_guard);
  nanobind::enum_<org::sem::BlockCodeLine::Part::Kind>(m, "BlockCodeLinePartKind")
    .value("Raw", org::sem::BlockCodeLine::Part::Kind::Raw)
    .value("Callout", org::sem::BlockCodeLine::Part::Kind::Callout)
    .value("Tangle", org::sem::BlockCodeLine::Part::Kind::Tangle)
    .def("__iter__", [](org::sem::BlockCodeLine::Part::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::BlockCodeLine::Part::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::BlockCodeLine::Part::Kind>();
                     })
    .def("__eq__",
         [](org::sem::BlockCodeLine::Part::Kind lhs, org::sem::BlockCodeLine::Part::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::BlockCodeLine::Part::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::BlockCodeLine::Part>(m, "BlockCodeLinePart")
    .def("__init__",
         [](org::sem::BlockCodeLine::Part* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::BlockCodeLine::Part();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("data", &org::sem::BlockCodeLine::Part::data)
    .def("__eq__",
         static_cast<bool(org::sem::BlockCodeLine::Part::*)(org::sem::BlockCodeLine::Part const&) const>(&org::sem::BlockCodeLine::Part::operator==),
         nanobind::arg("other"))
    .def("isRaw", static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isRaw))
    .def("getRaw", static_cast<org::sem::BlockCodeLine::Part::Raw&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getRaw))
    .def("isCallout", static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isCallout))
    .def("getCallout", static_cast<org::sem::BlockCodeLine::Part::Callout&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getCallout))
    .def("isTangle", static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isTangle))
    .def("getTangle", static_cast<org::sem::BlockCodeLine::Part::Tangle&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getTangle))
    .def_static("getKindStatic",
                static_cast<org::sem::BlockCodeLine::Part::Kind(*)(org::sem::BlockCodeLine::Part::Data const&)>(&org::sem::BlockCodeLine::Part::getKind),
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::BlockCodeLine::Part::Kind(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::BlockCodeLine::Part::Data const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::BlockCodeLine::Part::Kind(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::sub_variant_get_kind))
    .def("__repr__", [](org::sem::BlockCodeLine::Part const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeLine::Part const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockCodeLine>(m, "BlockCodeLine")
    .def("__init__",
         [](org::sem::BlockCodeLine* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::BlockCodeLine();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("parts", &org::sem::BlockCodeLine::parts, R"RAW(parts of the single line)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::BlockCodeLine::*)(org::sem::BlockCodeLine const&) const>(&org::sem::BlockCodeLine::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::BlockCodeLine const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeLine const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::DocumentExportConfig::TaskExport>(m, "DocumentExportConfigTaskExport")
    .def("__init__",
         [](org::sem::DocumentExportConfig::TaskExport* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::DocumentExportConfig::TaskExport();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("taskWhitelist", &org::sem::DocumentExportConfig::TaskExport::taskWhitelist)
    .def("__eq__",
         static_cast<bool(org::sem::DocumentExportConfig::TaskExport::*)(org::sem::DocumentExportConfig::TaskExport const&) const>(&org::sem::DocumentExportConfig::TaskExport::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::DocumentExportConfig::TaskExport const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentExportConfig::TaskExport const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::DocumentExportConfig::TagExport>(m, "DocumentExportConfigTagExport", type_registry_guard);
  nanobind::enum_<org::sem::DocumentExportConfig::TagExport>(m, "DocumentExportConfigTagExport")
    .value("None", org::sem::DocumentExportConfig::TagExport::None)
    .value("All", org::sem::DocumentExportConfig::TagExport::All)
    .value("NotInToc", org::sem::DocumentExportConfig::TagExport::NotInToc, R"RAW(Export tags in subtree titles but not in the table of content)RAW")
    .def("__iter__", [](org::sem::DocumentExportConfig::TagExport const& _self) -> org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TagExport> {
                     return org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TagExport>();
                     })
    .def("__eq__",
         [](org::sem::DocumentExportConfig::TagExport lhs, org::sem::DocumentExportConfig::TagExport rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::DocumentExportConfig::TagExport it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org::sem::DocumentExportConfig::TaskFiltering>(m, "DocumentExportConfigTaskFiltering", type_registry_guard);
  nanobind::enum_<org::sem::DocumentExportConfig::TaskFiltering>(m, "DocumentExportConfigTaskFiltering")
    .value("Whitelist", org::sem::DocumentExportConfig::TaskFiltering::Whitelist, R"RAW(Include tasks from the whitelist)RAW")
    .value("Done", org::sem::DocumentExportConfig::TaskFiltering::Done, R"RAW(Include tasks marked as done)RAW")
    .value("None", org::sem::DocumentExportConfig::TaskFiltering::None, R"RAW(Exclude all task subtrees from export)RAW")
    .value("All", org::sem::DocumentExportConfig::TaskFiltering::All, R"RAW(Add all task subtrees to export)RAW")
    .def("__iter__", [](org::sem::DocumentExportConfig::TaskFiltering const& _self) -> org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TaskFiltering> {
                     return org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TaskFiltering>();
                     })
    .def("__eq__",
         [](org::sem::DocumentExportConfig::TaskFiltering lhs, org::sem::DocumentExportConfig::TaskFiltering rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::DocumentExportConfig::TaskFiltering it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org::sem::DocumentExportConfig::BrokenLinks>(m, "DocumentExportConfigBrokenLinks", type_registry_guard);
  nanobind::enum_<org::sem::DocumentExportConfig::BrokenLinks>(m, "DocumentExportConfigBrokenLinks")
    .value("None", org::sem::DocumentExportConfig::BrokenLinks::None)
    .value("Mark", org::sem::DocumentExportConfig::BrokenLinks::Mark)
    .value("Raise", org::sem::DocumentExportConfig::BrokenLinks::Raise)
    .value("Ignore", org::sem::DocumentExportConfig::BrokenLinks::Ignore)
    .def("__iter__", [](org::sem::DocumentExportConfig::BrokenLinks const& _self) -> org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::BrokenLinks> {
                     return org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::BrokenLinks>();
                     })
    .def("__eq__",
         [](org::sem::DocumentExportConfig::BrokenLinks lhs, org::sem::DocumentExportConfig::BrokenLinks rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::DocumentExportConfig::BrokenLinks it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org::sem::DocumentExportConfig::ArchivedTrees>(m, "DocumentExportConfigArchivedTrees", type_registry_guard);
  nanobind::enum_<org::sem::DocumentExportConfig::ArchivedTrees>(m, "DocumentExportConfigArchivedTrees")
    .value("Skip", org::sem::DocumentExportConfig::ArchivedTrees::Skip, R"RAW(Skip archived trees entirely)RAW")
    .value("Headline", org::sem::DocumentExportConfig::ArchivedTrees::Headline, R"RAW(Export only headlines of archived trees)RAW")
    .value("All", org::sem::DocumentExportConfig::ArchivedTrees::All, R"RAW(Export archived trees with full content)RAW")
    .def("__iter__", [](org::sem::DocumentExportConfig::ArchivedTrees const& _self) -> org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::ArchivedTrees> {
                     return org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::ArchivedTrees>();
                     })
    .def("__eq__",
         [](org::sem::DocumentExportConfig::ArchivedTrees lhs, org::sem::DocumentExportConfig::ArchivedTrees rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::DocumentExportConfig::ArchivedTrees it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::DocumentExportConfig::DoExport>(m, "DocumentExportConfigDoExport")
    .def("__init__",
         [](org::sem::DocumentExportConfig::DoExport* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::DocumentExportConfig::DoExport();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("exportToc", &org::sem::DocumentExportConfig::DoExport::exportToc)
    .def("__eq__",
         static_cast<bool(org::sem::DocumentExportConfig::DoExport::*)(org::sem::DocumentExportConfig::DoExport const&) const>(&org::sem::DocumentExportConfig::DoExport::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::DocumentExportConfig::DoExport const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentExportConfig::DoExport const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::DocumentExportConfig::ExportFixed>(m, "DocumentExportConfigExportFixed")
    .def("__init__",
         [](org::sem::DocumentExportConfig::ExportFixed* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::DocumentExportConfig::ExportFixed();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("exportLevels", &org::sem::DocumentExportConfig::ExportFixed::exportLevels)
    .def("__eq__",
         static_cast<bool(org::sem::DocumentExportConfig::ExportFixed::*)(org::sem::DocumentExportConfig::ExportFixed const&) const>(&org::sem::DocumentExportConfig::ExportFixed::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::DocumentExportConfig::ExportFixed const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentExportConfig::ExportFixed const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::DocumentExportConfig::TocExportKind>(m, "DocumentExportConfigTocExportKind", type_registry_guard);
  nanobind::enum_<org::sem::DocumentExportConfig::TocExportKind>(m, "DocumentExportConfigTocExportKind")
    .value("DoExport", org::sem::DocumentExportConfig::TocExportKind::DoExport)
    .value("ExportFixed", org::sem::DocumentExportConfig::TocExportKind::ExportFixed)
    .def("__iter__", [](org::sem::DocumentExportConfig::TocExportKind const& _self) -> org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TocExportKind> {
                     return org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TocExportKind>();
                     })
    .def("__eq__",
         [](org::sem::DocumentExportConfig::TocExportKind lhs, org::sem::DocumentExportConfig::TocExportKind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::DocumentExportConfig::TocExportKind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::DocumentExportConfig>(m, "DocumentExportConfig")
    .def("__init__",
         [](org::sem::DocumentExportConfig* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::DocumentExportConfig();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("inlinetasks", &org::sem::DocumentExportConfig::inlinetasks, R"RAW(Toggle inclusion of inlinetasks)RAW")
    .def_rw("footnotes", &org::sem::DocumentExportConfig::footnotes, R"RAW(Toggle the inclusion of footnotes)RAW")
    .def_rw("clock", &org::sem::DocumentExportConfig::clock, R"RAW(Toggle inclusion of 'CLOCK' keywords)RAW")
    .def_rw("author", &org::sem::DocumentExportConfig::author, R"RAW(Toggle inclusion of author name into exported file)RAW")
    .def_rw("emphasis", &org::sem::DocumentExportConfig::emphasis, R"RAW(Toggle emphasized text)RAW")
    .def_rw("specialStrings", &org::sem::DocumentExportConfig::specialStrings, R"RAW(Toggle conversion of special strings)RAW")
    .def_rw("propertyDrawers", &org::sem::DocumentExportConfig::propertyDrawers, R"RAW(Toggle inclusion of property drawers)RAW")
    .def_rw("statisticsCookies", &org::sem::DocumentExportConfig::statisticsCookies, R"RAW(Toggle inclusion of statistics cookies)RAW")
    .def_rw("todoText", &org::sem::DocumentExportConfig::todoText, R"RAW(Toggle inclusion of TODO keywords into exported text)RAW")
    .def_rw("smartQuotes", &org::sem::DocumentExportConfig::smartQuotes, R"RAW(Toggle smart quotes)RAW")
    .def_rw("fixedWidth", &org::sem::DocumentExportConfig::fixedWidth, R"RAW(Toggle fixed-width sections)RAW")
    .def_rw("timestamps", &org::sem::DocumentExportConfig::timestamps, R"RAW(Toggle inclusion of time/date active/inactive stamps)RAW")
    .def_rw("preserveBreaks", &org::sem::DocumentExportConfig::preserveBreaks, R"RAW(Toggles whether to preserve line breaks)RAW")
    .def_rw("subSuperscripts", &org::sem::DocumentExportConfig::subSuperscripts, R"RAW(Toggle TeX-like syntax for sub- and superscripts)RAW")
    .def_rw("expandLinks", &org::sem::DocumentExportConfig::expandLinks, R"RAW(Toggle expansion of environment variables in file paths)RAW")
    .def_rw("creator", &org::sem::DocumentExportConfig::creator, R"RAW(Toggle inclusion of creator information in the exported file)RAW")
    .def_rw("drawers", &org::sem::DocumentExportConfig::drawers, R"RAW(Toggle inclusion of drawers)RAW")
    .def_rw("date", &org::sem::DocumentExportConfig::date, R"RAW(Toggle inclusion of a date into exported file)RAW")
    .def_rw("entities", &org::sem::DocumentExportConfig::entities, R"RAW(Toggle inclusion of entities)RAW")
    .def_rw("email", &org::sem::DocumentExportConfig::email, R"RAW(Toggle inclusion of the author's e-mail into exported file)RAW")
    .def_rw("sectionNumbers", &org::sem::DocumentExportConfig::sectionNumbers, R"RAW(Toggle section-numbers)RAW")
    .def_rw("planning", &org::sem::DocumentExportConfig::planning, R"RAW(Toggle export of planning information)RAW")
    .def_rw("priority", &org::sem::DocumentExportConfig::priority, R"RAW(Toggle inclusion of priority cookies)RAW")
    .def_rw("latex", &org::sem::DocumentExportConfig::latex, R"RAW(Toggle LaTeX export)RAW")
    .def_rw("timestamp", &org::sem::DocumentExportConfig::timestamp, R"RAW(Toggle inclusion of the creation time in the exported file)RAW")
    .def_rw("title", &org::sem::DocumentExportConfig::title, R"RAW(Toggle inclusion of title)RAW")
    .def_rw("tables", &org::sem::DocumentExportConfig::tables, R"RAW(Toggle inclusion of tables)RAW")
    .def_rw("headlineLevels", &org::sem::DocumentExportConfig::headlineLevels, R"RAW(Set the number of headline levels for export)RAW")
    .def_rw("brokenLinks", &org::sem::DocumentExportConfig::brokenLinks)
    .def_rw("tocExport", &org::sem::DocumentExportConfig::tocExport)
    .def_rw("tagExport", &org::sem::DocumentExportConfig::tagExport)
    .def_rw("taskFiltering", &org::sem::DocumentExportConfig::taskFiltering)
    .def_rw("archivedTrees", &org::sem::DocumentExportConfig::archivedTrees)
    .def_rw("data", &org::sem::DocumentExportConfig::data)
    .def("__eq__",
         static_cast<bool(org::sem::DocumentExportConfig::*)(org::sem::DocumentExportConfig const&) const>(&org::sem::DocumentExportConfig::operator==),
         nanobind::arg("other"))
    .def("isDoExport", static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isDoExport))
    .def("getDoExport", static_cast<org::sem::DocumentExportConfig::DoExport&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getDoExport))
    .def("isExportFixed", static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isExportFixed))
    .def("getExportFixed", static_cast<org::sem::DocumentExportConfig::ExportFixed&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getExportFixed))
    .def_static("getTocExportKindStatic",
                static_cast<org::sem::DocumentExportConfig::TocExportKind(*)(org::sem::DocumentExportConfig::TocExport const&)>(&org::sem::DocumentExportConfig::getTocExportKind),
                nanobind::arg("__input"))
    .def("getTocExportKind", static_cast<org::sem::DocumentExportConfig::TocExportKind(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getTocExportKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::DocumentExportConfig::TocExport const&(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::DocumentExportConfig::TocExportKind(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::sub_variant_get_kind))
    .def("__repr__", [](org::sem::DocumentExportConfig const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentExportConfig const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::SubtreePeriod::Kind>(m, "SubtreePeriodKind", type_registry_guard);
  nanobind::enum_<org::sem::SubtreePeriod::Kind>(m, "SubtreePeriodKind")
    .value("Clocked", org::sem::SubtreePeriod::Kind::Clocked, R"RAW(Time period of the task execution.)RAW")
    .value("Closed", org::sem::SubtreePeriod::Kind::Closed, R"RAW(Task marked as closed)RAW")
    .value("Scheduled", org::sem::SubtreePeriod::Kind::Scheduled, R"RAW(Date of task execution start plus it's estimated effort duration. If the latter one is missing then only a single time point is returned)RAW")
    .value("Titled", org::sem::SubtreePeriod::Kind::Titled, R"RAW(Single point or time range used in title. Single point can also be a simple time, such as `12:20`)RAW")
    .value("Deadline", org::sem::SubtreePeriod::Kind::Deadline, R"RAW(Date of task completion. Must be a single time point)RAW")
    .value("Created", org::sem::SubtreePeriod::Kind::Created, R"RAW(When the subtree was created)RAW")
    .value("Repeated", org::sem::SubtreePeriod::Kind::Repeated, R"RAW(Last repeat time of the recurring tasks)RAW")
    .def("__iter__", [](org::sem::SubtreePeriod::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::SubtreePeriod::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::SubtreePeriod::Kind>();
                     })
    .def("__eq__",
         [](org::sem::SubtreePeriod::Kind lhs, org::sem::SubtreePeriod::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::SubtreePeriod::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::SubtreePeriod>(m, "SubtreePeriod")
    .def("__init__",
         [](org::sem::SubtreePeriod* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::SubtreePeriod();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("kind", &org::sem::SubtreePeriod::kind, R"RAW(Time period kind -- not associated with point/range distinction)RAW")
    .def_rw("from_", &org::sem::SubtreePeriod::from, R"RAW(Clock start time)RAW")
    .def_rw("to", &org::sem::SubtreePeriod::to, R"RAW(Optional end of the clock)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::SubtreePeriod::*)(org::sem::SubtreePeriod const&) const>(&org::sem::SubtreePeriod::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreePeriod const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreePeriod const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::Nonblocking>(m, "NamedPropertyNonblocking")
    .def("__init__",
         [](org::sem::NamedProperty::Nonblocking* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::Nonblocking();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("isBlocking", &org::sem::NamedProperty::Nonblocking::isBlocking)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::Nonblocking::*)(org::sem::NamedProperty::Nonblocking const&) const>(&org::sem::NamedProperty::Nonblocking::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Nonblocking const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Nonblocking const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ArchiveTime>(m, "NamedPropertyArchiveTime")
    .def("__init__",
         [](org::sem::NamedProperty::ArchiveTime* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::ArchiveTime();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("time", &org::sem::NamedProperty::ArchiveTime::time)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ArchiveTime::*)(org::sem::NamedProperty::ArchiveTime const&) const>(&org::sem::NamedProperty::ArchiveTime::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveTime const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveTime const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ArchiveFile>(m, "NamedPropertyArchiveFile")
    .def("__init__",
         [](org::sem::NamedProperty::ArchiveFile* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::ArchiveFile();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("file", &org::sem::NamedProperty::ArchiveFile::file)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ArchiveFile::*)(org::sem::NamedProperty::ArchiveFile const&) const>(&org::sem::NamedProperty::ArchiveFile::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveFile const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveFile const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ArchiveOlpath>(m, "NamedPropertyArchiveOlpath")
    .def("__init__",
         [](org::sem::NamedProperty::ArchiveOlpath* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::ArchiveOlpath();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("path", &org::sem::NamedProperty::ArchiveOlpath::path)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ArchiveOlpath::*)(org::sem::NamedProperty::ArchiveOlpath const&) const>(&org::sem::NamedProperty::ArchiveOlpath::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveOlpath const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveOlpath const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ArchiveTarget>(m, "NamedPropertyArchiveTarget")
    .def("__init__",
         [](org::sem::NamedProperty::ArchiveTarget* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::ArchiveTarget();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("path", &org::sem::NamedProperty::ArchiveTarget::path)
    .def_rw("pattern", &org::sem::NamedProperty::ArchiveTarget::pattern)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ArchiveTarget::*)(org::sem::NamedProperty::ArchiveTarget const&) const>(&org::sem::NamedProperty::ArchiveTarget::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveTarget const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveTarget const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ArchiveCategory>(m, "NamedPropertyArchiveCategory")
    .def("__init__",
         [](org::sem::NamedProperty::ArchiveCategory* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::ArchiveCategory();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("category", &org::sem::NamedProperty::ArchiveCategory::category)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ArchiveCategory::*)(org::sem::NamedProperty::ArchiveCategory const&) const>(&org::sem::NamedProperty::ArchiveCategory::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveCategory const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveCategory const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ArchiveTodo>(m, "NamedPropertyArchiveTodo")
    .def("__init__",
         [](org::sem::NamedProperty::ArchiveTodo* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::ArchiveTodo();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("todo", &org::sem::NamedProperty::ArchiveTodo::todo)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ArchiveTodo::*)(org::sem::NamedProperty::ArchiveTodo const&) const>(&org::sem::NamedProperty::ArchiveTodo::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveTodo const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveTodo const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::Trigger>(m, "NamedPropertyTrigger")
    .def("__init__",
         [](org::sem::NamedProperty::Trigger* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::Trigger();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::Trigger::*)(org::sem::NamedProperty::Trigger const&) const>(&org::sem::NamedProperty::Trigger::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Trigger const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Trigger const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ExportLatexClass>(m, "NamedPropertyExportLatexClass")
    .def("__init__",
         [](org::sem::NamedProperty::ExportLatexClass* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::ExportLatexClass();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("latexClass", &org::sem::NamedProperty::ExportLatexClass::latexClass)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ExportLatexClass::*)(org::sem::NamedProperty::ExportLatexClass const&) const>(&org::sem::NamedProperty::ExportLatexClass::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ExportLatexClass const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ExportLatexClass const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::CookieData>(m, "NamedPropertyCookieData")
    .def("__init__",
         [](org::sem::NamedProperty::CookieData* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::CookieData();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("isRecursive", &org::sem::NamedProperty::CookieData::isRecursive)
    .def_rw("source", &org::sem::NamedProperty::CookieData::source)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::CookieData::*)(org::sem::NamedProperty::CookieData const&) const>(&org::sem::NamedProperty::CookieData::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CookieData const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CookieData const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ExportLatexClassOptions>(m, "NamedPropertyExportLatexClassOptions")
    .def("__init__",
         [](org::sem::NamedProperty::ExportLatexClassOptions* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::ExportLatexClassOptions();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("options", &org::sem::NamedProperty::ExportLatexClassOptions::options)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ExportLatexClassOptions::*)(org::sem::NamedProperty::ExportLatexClassOptions const&) const>(&org::sem::NamedProperty::ExportLatexClassOptions::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ExportLatexClassOptions const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ExportLatexClassOptions const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ExportLatexHeader>(m, "NamedPropertyExportLatexHeader")
    .def("__init__",
         [](org::sem::NamedProperty::ExportLatexHeader* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::ExportLatexHeader();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("header", &org::sem::NamedProperty::ExportLatexHeader::header)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ExportLatexHeader::*)(org::sem::NamedProperty::ExportLatexHeader const&) const>(&org::sem::NamedProperty::ExportLatexHeader::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ExportLatexHeader const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ExportLatexHeader const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ExportLatexCompiler>(m, "NamedPropertyExportLatexCompiler")
    .def("__init__",
         [](org::sem::NamedProperty::ExportLatexCompiler* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::ExportLatexCompiler();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("compiler", &org::sem::NamedProperty::ExportLatexCompiler::compiler)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ExportLatexCompiler::*)(org::sem::NamedProperty::ExportLatexCompiler const&) const>(&org::sem::NamedProperty::ExportLatexCompiler::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ExportLatexCompiler const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ExportLatexCompiler const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::Ordered>(m, "NamedPropertyOrdered")
    .def("__init__",
         [](org::sem::NamedProperty::Ordered* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::Ordered();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("isOrdered", &org::sem::NamedProperty::Ordered::isOrdered)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::Ordered::*)(org::sem::NamedProperty::Ordered const&) const>(&org::sem::NamedProperty::Ordered::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Ordered const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Ordered const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::Effort>(m, "NamedPropertyEffort")
    .def("__init__",
         [](org::sem::NamedProperty::Effort* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::Effort();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("hours", &org::sem::NamedProperty::Effort::hours)
    .def_rw("minutes", &org::sem::NamedProperty::Effort::minutes)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::Effort::*)(org::sem::NamedProperty::Effort const&) const>(&org::sem::NamedProperty::Effort::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Effort const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Effort const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::NamedProperty::Visibility::Level>(m, "NamedPropertyVisibilityLevel", type_registry_guard);
  nanobind::enum_<org::sem::NamedProperty::Visibility::Level>(m, "NamedPropertyVisibilityLevel")
    .value("Folded", org::sem::NamedProperty::Visibility::Level::Folded)
    .value("Children", org::sem::NamedProperty::Visibility::Level::Children)
    .value("Content", org::sem::NamedProperty::Visibility::Level::Content)
    .value("All", org::sem::NamedProperty::Visibility::Level::All)
    .def("__iter__", [](org::sem::NamedProperty::Visibility::Level const& _self) -> org::bind::python::PyEnumIterator<org::sem::NamedProperty::Visibility::Level> {
                     return org::bind::python::PyEnumIterator<org::sem::NamedProperty::Visibility::Level>();
                     })
    .def("__eq__",
         [](org::sem::NamedProperty::Visibility::Level lhs, org::sem::NamedProperty::Visibility::Level rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::NamedProperty::Visibility::Level it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::NamedProperty::Visibility>(m, "NamedPropertyVisibility")
    .def("__init__",
         [](org::sem::NamedProperty::Visibility* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::Visibility();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("level", &org::sem::NamedProperty::Visibility::level)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::Visibility::*)(org::sem::NamedProperty::Visibility const&) const>(&org::sem::NamedProperty::Visibility::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Visibility const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Visibility const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ExportOptions>(m, "NamedPropertyExportOptions")
    .def("__init__",
         [](org::sem::NamedProperty::ExportOptions* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::ExportOptions();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("backend", &org::sem::NamedProperty::ExportOptions::backend)
    .def_rw("values", &org::sem::NamedProperty::ExportOptions::values)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ExportOptions::*)(org::sem::NamedProperty::ExportOptions const&) const>(&org::sem::NamedProperty::ExportOptions::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ExportOptions const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ExportOptions const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::Blocker>(m, "NamedPropertyBlocker")
    .def("__init__",
         [](org::sem::NamedProperty::Blocker* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::Blocker();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("blockers", &org::sem::NamedProperty::Blocker::blockers)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::Blocker::*)(org::sem::NamedProperty::Blocker const&) const>(&org::sem::NamedProperty::Blocker::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Blocker const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Blocker const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::Unnumbered>(m, "NamedPropertyUnnumbered")
    .def("__init__",
         [](org::sem::NamedProperty::Unnumbered* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::Unnumbered();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::Unnumbered::*)(org::sem::NamedProperty::Unnumbered const&) const>(&org::sem::NamedProperty::Unnumbered::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Unnumbered const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Unnumbered const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::Created>(m, "NamedPropertyCreated")
    .def("__init__",
         [](org::sem::NamedProperty::Created* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::Created();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("time", &org::sem::NamedProperty::Created::time)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::Created::*)(org::sem::NamedProperty::Created const&) const>(&org::sem::NamedProperty::Created::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Created const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Created const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::RadioId>(m, "NamedPropertyRadioId")
    .def("__init__",
         [](org::sem::NamedProperty::RadioId* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::RadioId();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("words", &org::sem::NamedProperty::RadioId::words)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::RadioId::*)(org::sem::NamedProperty::RadioId const&) const>(&org::sem::NamedProperty::RadioId::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::RadioId const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::RadioId const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::HashtagDef>(m, "NamedPropertyHashtagDef")
    .def("__init__",
         [](org::sem::NamedProperty::HashtagDef* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::HashtagDef();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("hashtag", &org::sem::NamedProperty::HashtagDef::hashtag)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::HashtagDef::*)(org::sem::NamedProperty::HashtagDef const&) const>(&org::sem::NamedProperty::HashtagDef::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::HashtagDef const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::HashtagDef const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::CustomArgs>(m, "NamedPropertyCustomArgs")
    .def("__init__",
         [](org::sem::NamedProperty::CustomArgs* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::CustomArgs();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::NamedProperty::CustomArgs::name, R"RAW(Original name of the property)RAW")
    .def_rw("sub", &org::sem::NamedProperty::CustomArgs::sub, R"RAW(Property target specialization)RAW")
    .def_rw("attrs", &org::sem::NamedProperty::CustomArgs::attrs, R"RAW(Property parameters)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::CustomArgs::*)(org::sem::NamedProperty::CustomArgs const&) const>(&org::sem::NamedProperty::CustomArgs::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CustomArgs const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CustomArgs const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::CustomRaw>(m, "NamedPropertyCustomRaw")
    .def("__init__",
         [](org::sem::NamedProperty::CustomRaw* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::CustomRaw();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::NamedProperty::CustomRaw::name, R"RAW(Original name of the property)RAW")
    .def_rw("value", &org::sem::NamedProperty::CustomRaw::value, R"RAW(Property value)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::CustomRaw::*)(org::sem::NamedProperty::CustomRaw const&) const>(&org::sem::NamedProperty::CustomRaw::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CustomRaw const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CustomRaw const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::CustomId>(m, "NamedPropertyCustomId")
    .def("__init__",
         [](org::sem::NamedProperty::CustomId* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::CustomId();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::NamedProperty::CustomId::value, R"RAW(Property value)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::CustomId::*)(org::sem::NamedProperty::CustomId const&) const>(&org::sem::NamedProperty::CustomId::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CustomId const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CustomId const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::CustomSubtreeJson>(m, "NamedPropertyCustomSubtreeJson")
    .def("__init__",
         [](org::sem::NamedProperty::CustomSubtreeJson* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::CustomSubtreeJson();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::NamedProperty::CustomSubtreeJson::name)
    .def_rw("value", &org::sem::NamedProperty::CustomSubtreeJson::value)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::CustomSubtreeJson::*)(org::sem::NamedProperty::CustomSubtreeJson const&) const>(&org::sem::NamedProperty::CustomSubtreeJson::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CustomSubtreeJson const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CustomSubtreeJson const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::CustomSubtreeFlags>(m, "NamedPropertyCustomSubtreeFlags")
    .def("__init__",
         [](org::sem::NamedProperty::CustomSubtreeFlags* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty::CustomSubtreeFlags();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::NamedProperty::CustomSubtreeFlags::name)
    .def_rw("value", &org::sem::NamedProperty::CustomSubtreeFlags::value)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::CustomSubtreeFlags::*)(org::sem::NamedProperty::CustomSubtreeFlags const&) const>(&org::sem::NamedProperty::CustomSubtreeFlags::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CustomSubtreeFlags const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CustomSubtreeFlags const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::NamedProperty::Kind>(m, "NamedPropertyKind", type_registry_guard);
  nanobind::enum_<org::sem::NamedProperty::Kind>(m, "NamedPropertyKind")
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
    .value("CustomId", org::sem::NamedProperty::Kind::CustomId)
    .value("CustomSubtreeJson", org::sem::NamedProperty::Kind::CustomSubtreeJson)
    .value("CustomSubtreeFlags", org::sem::NamedProperty::Kind::CustomSubtreeFlags)
    .def("__iter__", [](org::sem::NamedProperty::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::NamedProperty::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::NamedProperty::Kind>();
                     })
    .def("__eq__",
         [](org::sem::NamedProperty::Kind lhs, org::sem::NamedProperty::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::NamedProperty::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::NamedProperty>(m, "NamedProperty")
    .def("__init__",
         [](org::sem::NamedProperty* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NamedProperty();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("data", &org::sem::NamedProperty::data)
    .def("isMatching",
         static_cast<bool(org::sem::NamedProperty::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::NamedProperty::isMatching),
         nanobind::arg("kind"),
         nanobind::arg("subKind") = std::nullopt,
         R"RAW(Check if property matches specified kind and optional subkind. Built-in property checking is also done with this function -- 'created' etc.)RAW")
    .def("getName", static_cast<hstd::Str(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getName), R"RAW(Get non-normalized name of the property (for built-in and user))RAW")
    .def("getSubKind", static_cast<hstd::Opt<hstd::Str>(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getSubKind), R"RAW(Get non-normalized sub-kind for the property.)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::*)(org::sem::NamedProperty const&) const>(&org::sem::NamedProperty::operator==),
         nanobind::arg("other"))
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
    .def("isCustomId", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomId))
    .def("getCustomId", static_cast<org::sem::NamedProperty::CustomId&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomId))
    .def("isCustomSubtreeJson", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeJson))
    .def("getCustomSubtreeJson", static_cast<org::sem::NamedProperty::CustomSubtreeJson&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeJson))
    .def("isCustomSubtreeFlags", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeFlags))
    .def("getCustomSubtreeFlags", static_cast<org::sem::NamedProperty::CustomSubtreeFlags&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeFlags))
    .def_static("getKindStatic",
                static_cast<org::sem::NamedProperty::Kind(*)(org::sem::NamedProperty::Data const&)>(&org::sem::NamedProperty::getKind),
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::NamedProperty::Kind(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::NamedProperty::Data const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::NamedProperty::Kind(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::sub_variant_get_kind))
    .def("__repr__", [](org::sem::NamedProperty const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::OrgDiagnostics::ParseTokenError>(m, "OrgDiagnosticsParseTokenError")
    .def("__init__",
         [](org::sem::OrgDiagnostics::ParseTokenError* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::OrgDiagnostics::ParseTokenError();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("brief", &org::sem::OrgDiagnostics::ParseTokenError::brief)
    .def_rw("detail", &org::sem::OrgDiagnostics::ParseTokenError::detail)
    .def_rw("parserFunction", &org::sem::OrgDiagnostics::ParseTokenError::parserFunction)
    .def_rw("parserLine", &org::sem::OrgDiagnostics::ParseTokenError::parserLine)
    .def_rw("tokenKind", &org::sem::OrgDiagnostics::ParseTokenError::tokenKind)
    .def_rw("tokenText", &org::sem::OrgDiagnostics::ParseTokenError::tokenText)
    .def_rw("loc", &org::sem::OrgDiagnostics::ParseTokenError::loc)
    .def_rw("errName", &org::sem::OrgDiagnostics::ParseTokenError::errName)
    .def_rw("errCode", &org::sem::OrgDiagnostics::ParseTokenError::errCode)
    .def("__eq__",
         static_cast<bool(org::sem::OrgDiagnostics::ParseTokenError::*)(org::sem::OrgDiagnostics::ParseTokenError const&) const>(&org::sem::OrgDiagnostics::ParseTokenError::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::OrgDiagnostics::ParseTokenError const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgDiagnostics::ParseTokenError const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::OrgDiagnostics::ParseError>(m, "OrgDiagnosticsParseError")
    .def("__init__",
         [](org::sem::OrgDiagnostics::ParseError* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::OrgDiagnostics::ParseError();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("brief", &org::sem::OrgDiagnostics::ParseError::brief)
    .def_rw("detail", &org::sem::OrgDiagnostics::ParseError::detail)
    .def_rw("parserFunction", &org::sem::OrgDiagnostics::ParseError::parserFunction)
    .def_rw("parserLine", &org::sem::OrgDiagnostics::ParseError::parserLine)
    .def_rw("errName", &org::sem::OrgDiagnostics::ParseError::errName)
    .def_rw("errCode", &org::sem::OrgDiagnostics::ParseError::errCode)
    .def_rw("loc", &org::sem::OrgDiagnostics::ParseError::loc)
    .def("__eq__",
         static_cast<bool(org::sem::OrgDiagnostics::ParseError::*)(org::sem::OrgDiagnostics::ParseError const&) const>(&org::sem::OrgDiagnostics::ParseError::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::OrgDiagnostics::ParseError const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgDiagnostics::ParseError const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::OrgDiagnostics::IncludeError>(m, "OrgDiagnosticsIncludeError")
    .def("__init__",
         [](org::sem::OrgDiagnostics::IncludeError* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::OrgDiagnostics::IncludeError();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("brief", &org::sem::OrgDiagnostics::IncludeError::brief)
    .def_rw("targetPath", &org::sem::OrgDiagnostics::IncludeError::targetPath)
    .def_rw("workingFile", &org::sem::OrgDiagnostics::IncludeError::workingFile)
    .def("__eq__",
         static_cast<bool(org::sem::OrgDiagnostics::IncludeError::*)(org::sem::OrgDiagnostics::IncludeError const&) const>(&org::sem::OrgDiagnostics::IncludeError::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::OrgDiagnostics::IncludeError const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgDiagnostics::IncludeError const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::OrgDiagnostics::ConvertError>(m, "OrgDiagnosticsConvertError")
    .def("__init__",
         [](org::sem::OrgDiagnostics::ConvertError* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::OrgDiagnostics::ConvertError();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("brief", &org::sem::OrgDiagnostics::ConvertError::brief)
    .def_rw("detail", &org::sem::OrgDiagnostics::ConvertError::detail)
    .def_rw("convertFunction", &org::sem::OrgDiagnostics::ConvertError::convertFunction)
    .def_rw("convertLine", &org::sem::OrgDiagnostics::ConvertError::convertLine)
    .def_rw("convertFile", &org::sem::OrgDiagnostics::ConvertError::convertFile)
    .def_rw("errName", &org::sem::OrgDiagnostics::ConvertError::errName)
    .def_rw("errCode", &org::sem::OrgDiagnostics::ConvertError::errCode)
    .def_rw("loc", &org::sem::OrgDiagnostics::ConvertError::loc)
    .def("__eq__",
         static_cast<bool(org::sem::OrgDiagnostics::ConvertError::*)(org::sem::OrgDiagnostics::ConvertError const&) const>(&org::sem::OrgDiagnostics::ConvertError::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::OrgDiagnostics::ConvertError const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgDiagnostics::ConvertError const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::OrgDiagnostics::InternalError>(m, "OrgDiagnosticsInternalError")
    .def("__init__",
         [](org::sem::OrgDiagnostics::InternalError* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::OrgDiagnostics::InternalError();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("message", &org::sem::OrgDiagnostics::InternalError::message)
    .def_rw("function", &org::sem::OrgDiagnostics::InternalError::function)
    .def_rw("line", &org::sem::OrgDiagnostics::InternalError::line)
    .def_rw("file", &org::sem::OrgDiagnostics::InternalError::file)
    .def_rw("loc", &org::sem::OrgDiagnostics::InternalError::loc)
    .def("__eq__",
         static_cast<bool(org::sem::OrgDiagnostics::InternalError::*)(org::sem::OrgDiagnostics::InternalError const&) const>(&org::sem::OrgDiagnostics::InternalError::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::OrgDiagnostics::InternalError const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgDiagnostics::InternalError const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::OrgDiagnostics::Kind>(m, "OrgDiagnosticsKind", type_registry_guard);
  nanobind::enum_<org::sem::OrgDiagnostics::Kind>(m, "OrgDiagnosticsKind")
    .value("ParseTokenError", org::sem::OrgDiagnostics::Kind::ParseTokenError)
    .value("ParseError", org::sem::OrgDiagnostics::Kind::ParseError)
    .value("IncludeError", org::sem::OrgDiagnostics::Kind::IncludeError)
    .value("ConvertError", org::sem::OrgDiagnostics::Kind::ConvertError)
    .value("InternalError", org::sem::OrgDiagnostics::Kind::InternalError)
    .def("__iter__", [](org::sem::OrgDiagnostics::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::OrgDiagnostics::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::OrgDiagnostics::Kind>();
                     })
    .def("__eq__",
         [](org::sem::OrgDiagnostics::Kind lhs, org::sem::OrgDiagnostics::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::OrgDiagnostics::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::OrgDiagnostics>(m, "OrgDiagnostics")
    .def("__init__",
         [](org::sem::OrgDiagnostics* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::OrgDiagnostics();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("data", &org::sem::OrgDiagnostics::data)
    .def("__eq__",
         static_cast<bool(org::sem::OrgDiagnostics::*)(org::sem::OrgDiagnostics const&) const>(&org::sem::OrgDiagnostics::operator==),
         nanobind::arg("other"))
    .def("isParseTokenError", static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isParseTokenError))
    .def("getParseTokenError", static_cast<org::sem::OrgDiagnostics::ParseTokenError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getParseTokenError))
    .def("isParseError", static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isParseError))
    .def("getParseError", static_cast<org::sem::OrgDiagnostics::ParseError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getParseError))
    .def("isIncludeError", static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isIncludeError))
    .def("getIncludeError", static_cast<org::sem::OrgDiagnostics::IncludeError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getIncludeError))
    .def("isConvertError", static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isConvertError))
    .def("getConvertError", static_cast<org::sem::OrgDiagnostics::ConvertError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getConvertError))
    .def("isInternalError", static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isInternalError))
    .def("getInternalError", static_cast<org::sem::OrgDiagnostics::InternalError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getInternalError))
    .def_static("getKindStatic",
                static_cast<org::sem::OrgDiagnostics::Kind(*)(org::sem::OrgDiagnostics::Data const&)>(&org::sem::OrgDiagnostics::getKind),
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::OrgDiagnostics::Kind(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::OrgDiagnostics::Data const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::OrgDiagnostics::Kind(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::sub_variant_get_kind))
    .def("__repr__", [](org::sem::OrgDiagnostics const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgDiagnostics const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmNoNode>>(m, "ImmAdapterNoNodeBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmErrorItem>>(m, "ImmAdapterErrorItemBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmErrorGroup>>(m, "ImmAdapterErrorGroupBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmStmt>>(m, "ImmAdapterStmtBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmInline>>(m, "ImmAdapterInlineBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmStmtList>>(m, "ImmAdapterStmtListBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmEmpty>>(m, "ImmAdapterEmptyBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmd>>(m, "ImmAdapterCmdBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlock>>(m, "ImmAdapterBlockBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmLineCommand>>(m, "ImmAdapterLineCommandBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmAttached>>(m, "ImmAdapterAttachedBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmLeaf>>(m, "ImmAdapterLeafBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdCaption>>(m, "ImmAdapterCmdCaptionBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdCreator>>(m, "ImmAdapterCmdCreatorBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdAuthor>>(m, "ImmAdapterCmdAuthorBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdEmail>>(m, "ImmAdapterCmdEmailBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdLanguage>>(m, "ImmAdapterCmdLanguageBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdColumns>>(m, "ImmAdapterCmdColumnsBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdName>>(m, "ImmAdapterCmdNameBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomArgs>>(m, "ImmAdapterCmdCustomArgsBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomRaw>>(m, "ImmAdapterCmdCustomRawBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomText>>(m, "ImmAdapterCmdCustomTextBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdCall>>(m, "ImmAdapterCmdCallBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdTblfm>>(m, "ImmAdapterCmdTblfmBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmHashTag>>(m, "ImmAdapterHashTagBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmInlineFootnote>>(m, "ImmAdapterInlineFootnoteBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmInlineExport>>(m, "ImmAdapterInlineExportBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmTime>>(m, "ImmAdapterTimeBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmTimeRange>>(m, "ImmAdapterTimeRangeBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmMacro>>(m, "ImmAdapterMacroBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmSymbol>>(m, "ImmAdapterSymbolBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmEscaped>>(m, "ImmAdapterEscapedBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmNewline>>(m, "ImmAdapterNewlineBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmSpace>>(m, "ImmAdapterSpaceBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmWord>>(m, "ImmAdapterWordBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmAtMention>>(m, "ImmAdapterAtMentionBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmRawText>>(m, "ImmAdapterRawTextBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmPunctuation>>(m, "ImmAdapterPunctuationBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmPlaceholder>>(m, "ImmAdapterPlaceholderBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBigIdent>>(m, "ImmAdapterBigIdentBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmTextTarget>>(m, "ImmAdapterTextTargetBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmErrorSkipToken>>(m, "ImmAdapterErrorSkipTokenBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmErrorSkipGroup>>(m, "ImmAdapterErrorSkipGroupBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmMarkup>>(m, "ImmAdapterMarkupBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBold>>(m, "ImmAdapterBoldBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmUnderline>>(m, "ImmAdapterUnderlineBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmMonospace>>(m, "ImmAdapterMonospaceBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmMarkQuote>>(m, "ImmAdapterMarkQuoteBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmVerbatim>>(m, "ImmAdapterVerbatimBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmItalic>>(m, "ImmAdapterItalicBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmStrike>>(m, "ImmAdapterStrikeBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmPar>>(m, "ImmAdapterParBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmRadioTarget>>(m, "ImmAdapterRadioTargetBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmLatex>>(m, "ImmAdapterLatexBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmLink>>(m, "ImmAdapterLinkBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockCenter>>(m, "ImmAdapterBlockCenterBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockQuote>>(m, "ImmAdapterBlockQuoteBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockComment>>(m, "ImmAdapterBlockCommentBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockVerse>>(m, "ImmAdapterBlockVerseBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockDynamicFallback>>(m, "ImmAdapterBlockDynamicFallbackBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockExample>>(m, "ImmAdapterBlockExampleBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockExport>>(m, "ImmAdapterBlockExportBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockAdmonition>>(m, "ImmAdapterBlockAdmonitionBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockCodeEvalResult>>(m, "ImmAdapterBlockCodeEvalResultBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockCode>>(m, "ImmAdapterBlockCodeBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmSubtreeLog>>(m, "ImmAdapterSubtreeLogBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmSubtree>>(m, "ImmAdapterSubtreeBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCell>>(m, "ImmAdapterCellBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmRow>>(m, "ImmAdapterRowBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmTable>>(m, "ImmAdapterTableBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmParagraph>>(m, "ImmAdapterParagraphBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmColonExample>>(m, "ImmAdapterColonExampleBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdAttr>>(m, "ImmAdapterCmdAttrBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdExport>>(m, "ImmAdapterCmdExportBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCall>>(m, "ImmAdapterCallBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmList>>(m, "ImmAdapterListBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmListItem>>(m, "ImmAdapterListItemBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmDocumentOptions>>(m, "ImmAdapterDocumentOptionsBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmDocumentFragment>>(m, "ImmAdapterDocumentFragmentBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCriticMarkup>>(m, "ImmAdapterCriticMarkupBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmDocument>>(m, "ImmAdapterDocumentBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmFileTarget>>(m, "ImmAdapterFileTargetBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmTextSeparator>>(m, "ImmAdapterTextSeparatorBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmDocumentGroup>>(m, "ImmAdapterDocumentGroupBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmFile>>(m, "ImmAdapterFileBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmDirectory>>(m, "ImmAdapterDirectoryBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmSymlink>>(m, "ImmAdapterSymlinkBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdInclude>>(m, "ImmAdapterCmdIncludeBase")
    ;
  nanobind::class_<org::sem::NoNode, org::sem::Org>(m, "NoNode")
    .def("__init__",
         [](org::sem::NoNode* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::NoNode();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::NoNode const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NoNode const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::ErrorItem, org::sem::Org>(m, "ErrorItem")
    .def("__init__",
         [](org::sem::ErrorItem* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::ErrorItem();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("diag", &org::sem::ErrorItem::diag)
    .def("__repr__", [](org::sem::ErrorItem const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ErrorItem const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::ErrorGroup, org::sem::Org>(m, "ErrorGroup")
    .def("__init__",
         [](org::sem::ErrorGroup* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::ErrorGroup();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("diagnostics", &org::sem::ErrorGroup::diagnostics)
    .def("__repr__", [](org::sem::ErrorGroup const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ErrorGroup const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Stmt, org::sem::Org>(m, "Stmt")
    .def_rw("attached", &org::sem::Stmt::attached)
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt::getAttached),
         nanobind::arg("kind") = std::nullopt,
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt::*)() const>(&org::sem::Stmt::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::Stmt::*)() const>(&org::sem::Stmt::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Stmt::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt::getAttrs),
         nanobind::arg("kind") = std::nullopt,
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttr),
         nanobind::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("getFirstAttrString",
         static_cast<hstd::Opt<hstd::Str>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrString),
         nanobind::arg("kind"))
    .def("getFirstAttrInt",
         static_cast<hstd::Opt<int>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrInt),
         nanobind::arg("kind"))
    .def("getFirstAttrBool",
         static_cast<hstd::Opt<bool>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrBool),
         nanobind::arg("kind"))
    .def("getFirstAttrDouble",
         static_cast<hstd::Opt<double>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrDouble),
         nanobind::arg("kind"))
    .def("getFirstAttrLisp",
         static_cast<hstd::Opt<org::sem::AttrValue::LispValue>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrLisp),
         nanobind::arg("kind"))
    .def("getFirstAttrKind",
         static_cast<hstd::Opt<org::sem::AttrValue::Kind>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrKind),
         nanobind::arg("kind"))
    ;
  nanobind::class_<org::sem::Inline, org::sem::Org>(m, "Inline")
    ;
  nanobind::class_<org::sem::StmtList, org::sem::Org>(m, "StmtList")
    .def("__init__",
         [](org::sem::StmtList* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::StmtList();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::StmtList const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::StmtList const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Empty, org::sem::Org>(m, "Empty")
    .def("__init__",
         [](org::sem::Empty* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Empty();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Empty const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Empty const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Leaf, org::sem::Org>(m, "Leaf")
    .def_rw("text", &org::sem::Leaf::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<hstd::Str(org::sem::Leaf::*)() const>(&org::sem::Leaf::getText))
    ;
  bind_enum_iterator<org::sem::Time::Repeat::Mode>(m, "TimeRepeatMode", type_registry_guard);
  nanobind::enum_<org::sem::Time::Repeat::Mode>(m, "TimeRepeatMode")
    .value("None", org::sem::Time::Repeat::Mode::None, R"RAW(Do not repeat task on completion)RAW")
    .value("Exact", org::sem::Time::Repeat::Mode::Exact, R"RAW(?)RAW")
    .value("FirstMatch", org::sem::Time::Repeat::Mode::FirstMatch, R"RAW(Repeat on the first matching day in the future)RAW")
    .value("SameDay", org::sem::Time::Repeat::Mode::SameDay, R"RAW(Repeat task on the same day next week/month/year)RAW")
    .def("__iter__", [](org::sem::Time::Repeat::Mode const& _self) -> org::bind::python::PyEnumIterator<org::sem::Time::Repeat::Mode> {
                     return org::bind::python::PyEnumIterator<org::sem::Time::Repeat::Mode>();
                     })
    .def("__eq__",
         [](org::sem::Time::Repeat::Mode lhs, org::sem::Time::Repeat::Mode rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::Time::Repeat::Mode it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org::sem::Time::Repeat::Period>(m, "TimeRepeatPeriod", type_registry_guard);
  nanobind::enum_<org::sem::Time::Repeat::Period>(m, "TimeRepeatPeriod")
    .value("Year", org::sem::Time::Repeat::Period::Year)
    .value("Month", org::sem::Time::Repeat::Period::Month)
    .value("Week", org::sem::Time::Repeat::Period::Week)
    .value("Day", org::sem::Time::Repeat::Period::Day)
    .value("Hour", org::sem::Time::Repeat::Period::Hour)
    .value("Minute", org::sem::Time::Repeat::Period::Minute)
    .def("__iter__", [](org::sem::Time::Repeat::Period const& _self) -> org::bind::python::PyEnumIterator<org::sem::Time::Repeat::Period> {
                     return org::bind::python::PyEnumIterator<org::sem::Time::Repeat::Period>();
                     })
    .def("__eq__",
         [](org::sem::Time::Repeat::Period lhs, org::sem::Time::Repeat::Period rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::Time::Repeat::Period it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::Time::Repeat>(m, "TimeRepeat")
    .def("__init__",
         [](org::sem::Time::Repeat* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Time::Repeat();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("mode", &org::sem::Time::Repeat::mode, R"RAW(mode)RAW")
    .def_rw("period", &org::sem::Time::Repeat::period, R"RAW(period)RAW")
    .def_rw("count", &org::sem::Time::Repeat::count, R"RAW(count)RAW")
    .def("__repr__", [](org::sem::Time::Repeat const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Time::Repeat const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Time::Static>(m, "TimeStatic")
    .def("__init__",
         [](org::sem::Time::Static* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Time::Static();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("repeat", &org::sem::Time::Static::repeat)
    .def_rw("warn", &org::sem::Time::Static::warn)
    .def_rw("time", &org::sem::Time::Static::time)
    .def("__repr__", [](org::sem::Time::Static const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Time::Static const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Time::Dynamic>(m, "TimeDynamic")
    .def("__init__",
         [](org::sem::Time::Dynamic* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Time::Dynamic();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("expr", &org::sem::Time::Dynamic::expr)
    .def("__repr__", [](org::sem::Time::Dynamic const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Time::Dynamic const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::Time::TimeKind>(m, "TimeTimeKind", type_registry_guard);
  nanobind::enum_<org::sem::Time::TimeKind>(m, "TimeTimeKind")
    .value("Static", org::sem::Time::TimeKind::Static)
    .value("Dynamic", org::sem::Time::TimeKind::Dynamic)
    .def("__iter__", [](org::sem::Time::TimeKind const& _self) -> org::bind::python::PyEnumIterator<org::sem::Time::TimeKind> {
                     return org::bind::python::PyEnumIterator<org::sem::Time::TimeKind>();
                     })
    .def("__eq__",
         [](org::sem::Time::TimeKind lhs, org::sem::Time::TimeKind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::Time::TimeKind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::Time, org::sem::Org>(m, "Time")
    .def("__init__",
         [](org::sem::Time* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Time();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("isActive", &org::sem::Time::isActive, R"RAW(<active> vs [inactive])RAW")
    .def_rw("time", &org::sem::Time::time)
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
                nanobind::arg("__input"))
    .def("getTimeKind", static_cast<org::sem::Time::TimeKind(org::sem::Time::*)() const>(&org::sem::Time::getTimeKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::Time::*)() const>(&org::sem::Time::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::Time::TimeVariant const&(org::sem::Time::*)() const>(&org::sem::Time::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::Time::TimeKind(org::sem::Time::*)() const>(&org::sem::Time::sub_variant_get_kind))
    .def("__repr__", [](org::sem::Time const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Time const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::TimeRange, org::sem::Org>(m, "TimeRange")
    .def("__init__",
         [](org::sem::TimeRange* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::TimeRange();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("from_", &org::sem::TimeRange::from, R"RAW(Starting time)RAW")
    .def_rw("to", &org::sem::TimeRange::to, R"RAW(Finishing time)RAW")
    .def("getClockedTimeSeconds", static_cast<hstd::Opt<int64_t>(org::sem::TimeRange::*)() const>(&org::sem::TimeRange::getClockedTimeSeconds))
    .def("__repr__", [](org::sem::TimeRange const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::TimeRange const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Macro, org::sem::Org>(m, "Macro")
    .def("__init__",
         [](org::sem::Macro* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Macro();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::Macro::name, R"RAW(Macro name)RAW")
    .def_rw("attrs", &org::sem::Macro::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def("__repr__", [](org::sem::Macro const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Macro const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Symbol::Param>(m, "SymbolParam")
    .def("__init__",
         [](org::sem::Symbol::Param* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Symbol::Param();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("key", &org::sem::Symbol::Param::key, R"RAW(Key -- for non-positional)RAW")
    .def_rw("value", &org::sem::Symbol::Param::value, R"RAW(Uninterpreted value)RAW")
    .def("__repr__", [](org::sem::Symbol::Param const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Symbol::Param const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Symbol, org::sem::Org>(m, "Symbol")
    .def("__init__",
         [](org::sem::Symbol* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Symbol();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::Symbol::name, R"RAW(Name of the symbol)RAW")
    .def_rw("parameters", &org::sem::Symbol::parameters, R"RAW(Optional list of parameters)RAW")
    .def_rw("positional", &org::sem::Symbol::positional, R"RAW(Positional parameters)RAW")
    .def("__repr__", [](org::sem::Symbol const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Symbol const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::ErrorSkipGroup, org::sem::Org>(m, "ErrorSkipGroup")
    .def("__init__",
         [](org::sem::ErrorSkipGroup* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::ErrorSkipGroup();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("skipped", &org::sem::ErrorSkipGroup::skipped)
    .def("__repr__", [](org::sem::ErrorSkipGroup const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ErrorSkipGroup const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Markup, org::sem::Org>(m, "Markup")
    ;
  nanobind::class_<org::sem::RadioTarget, org::sem::Org>(m, "RadioTarget")
    .def("__init__",
         [](org::sem::RadioTarget* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::RadioTarget();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("words", &org::sem::RadioTarget::words)
    .def("__repr__", [](org::sem::RadioTarget const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::RadioTarget const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Latex, org::sem::Org>(m, "Latex")
    .def("__init__",
         [](org::sem::Latex* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Latex();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Latex const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Latex const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLog, org::sem::Org>(m, "SubtreeLog")
    .def("__init__",
         [](org::sem::SubtreeLog* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::SubtreeLog();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("head", &org::sem::SubtreeLog::head)
    .def_rw("desc", &org::sem::SubtreeLog::desc, R"RAW(Optional description of the log entry)RAW")
    .def("setDescription",
         static_cast<void(org::sem::SubtreeLog::*)(org::sem::SemId<org::sem::StmtList>)>(&org::sem::SubtreeLog::setDescription),
         nanobind::arg("desc"))
    .def("__repr__", [](org::sem::SubtreeLog const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLog const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Subtree, org::sem::Org>(m, "Subtree")
    .def("__init__",
         [](org::sem::Subtree* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Subtree();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("level", &org::sem::Subtree::level, R"RAW(Subtree level)RAW")
    .def_rw("treeId", &org::sem::Subtree::treeId, R"RAW(:ID: property)RAW")
    .def_rw("todo", &org::sem::Subtree::todo, R"RAW(Todo state of the tree)RAW")
    .def_rw("completion", &org::sem::Subtree::completion, R"RAW(Task completion state)RAW")
    .def_rw("description", &org::sem::Subtree::description)
    .def_rw("tags", &org::sem::Subtree::tags, R"RAW(Trailing tags)RAW")
    .def_rw("title", &org::sem::Subtree::title, R"RAW(Main title)RAW")
    .def_rw("logbook", &org::sem::Subtree::logbook, R"RAW(Associated subtree log)RAW")
    .def_rw("properties", &org::sem::Subtree::properties, R"RAW(Immediate properties)RAW")
    .def_rw("closed", &org::sem::Subtree::closed, R"RAW(When subtree was marked as closed)RAW")
    .def_rw("deadline", &org::sem::Subtree::deadline, R"RAW(When is the deadline)RAW")
    .def_rw("scheduled", &org::sem::Subtree::scheduled, R"RAW(When the event is scheduled)RAW")
    .def_rw("isComment", &org::sem::Subtree::isComment, R"RAW(Subtree is annotated with the COMMENT keyword)RAW")
    .def_rw("isArchived", &org::sem::Subtree::isArchived, R"RAW(Subtree is tagged with `:ARCHIVE:` tag)RAW")
    .def_rw("priority", &org::sem::Subtree::priority)
    .def("getTimePeriods",
         static_cast<hstd::Vec<org::sem::SubtreePeriod>(org::sem::Subtree::*)(hstd::IntSet<org::sem::SubtreePeriod::Kind>) const>(&org::sem::Subtree::getTimePeriods),
         nanobind::arg("kinds"))
    .def("getProperties",
         static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree::getProperties),
         nanobind::arg("kind"),
         nanobind::arg("subkind") = std::nullopt)
    .def("getProperty",
         static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree::getProperty),
         nanobind::arg("kind"),
         nanobind::arg("subkind") = std::nullopt)
    .def("removeProperty",
         static_cast<void(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree::removeProperty),
         nanobind::arg("kind"),
         nanobind::arg("subkind") = std::nullopt,
         R"RAW(Remove all instances of the property with matching kind/subkind from the property list)RAW")
    .def("setProperty",
         static_cast<void(org::sem::Subtree::*)(org::sem::NamedProperty const&)>(&org::sem::Subtree::setProperty),
         nanobind::arg("value"),
         R"RAW(Create or override existing property value in the subtree property list)RAW")
    .def("setPropertyStrValue",
         static_cast<void(org::sem::Subtree::*)(hstd::Str const&, hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree::setPropertyStrValue),
         nanobind::arg("value"),
         nanobind::arg("kind"),
         nanobind::arg("subkind") = std::nullopt,
         R"RAW(Assign a raw string literal to a property.)RAW")
    .def("getCleanTitle", static_cast<hstd::Str(org::sem::Subtree::*)() const>(&org::sem::Subtree::getCleanTitle), R"RAW(Get subtree title as a flat string, without markup nodes, but with all left strings)RAW")
    .def("getTodoKeyword", static_cast<hstd::Opt<hstd::Str>(org::sem::Subtree::*)() const>(&org::sem::Subtree::getTodoKeyword))
    .def("__repr__", [](org::sem::Subtree const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Subtree const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::ColonExample, org::sem::Org>(m, "ColonExample")
    .def("__init__",
         [](org::sem::ColonExample* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::ColonExample();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::ColonExample const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColonExample const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Call, org::sem::Org>(m, "Call")
    .def("__init__",
         [](org::sem::Call* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Call();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::Call::name, R"RAW(Call target name)RAW")
    .def_rw("attrs", &org::sem::Call::attrs, R"RAW(Additional parameters aside from 'exporter')RAW")
    .def_rw("isCommand", &org::sem::Call::isCommand)
    .def("__repr__", [](org::sem::Call const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Call const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::ListItem, org::sem::Org>(m, "ListItem")
    .def("__init__",
         [](org::sem::ListItem* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::ListItem();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("checkbox", &org::sem::ListItem::checkbox)
    .def_rw("header", &org::sem::ListItem::header, R"RAW(Description list item header)RAW")
    .def_rw("bullet", &org::sem::ListItem::bullet, R"RAW(Full text of the numbered list item, e.g. `a)`, `a.`)RAW")
    .def("isDescriptionItem", static_cast<bool(org::sem::ListItem::*)() const>(&org::sem::ListItem::isDescriptionItem))
    .def("getCleanHeader", static_cast<hstd::Opt<hstd::Str>(org::sem::ListItem::*)() const>(&org::sem::ListItem::getCleanHeader), R"RAW(Return flat text for the description list header)RAW")
    .def("__repr__", [](org::sem::ListItem const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ListItem const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::DocumentOptions, org::sem::Org>(m, "DocumentOptions")
    .def("__init__",
         [](org::sem::DocumentOptions* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::DocumentOptions();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("initialVisibility", &org::sem::DocumentOptions::initialVisibility)
    .def_rw("properties", &org::sem::DocumentOptions::properties)
    .def_rw("exportConfig", &org::sem::DocumentOptions::exportConfig)
    .def_rw("fixedWidthSections", &org::sem::DocumentOptions::fixedWidthSections)
    .def_rw("startupIndented", &org::sem::DocumentOptions::startupIndented)
    .def_rw("category", &org::sem::DocumentOptions::category)
    .def_rw("setupfile", &org::sem::DocumentOptions::setupfile)
    .def_rw("maxSubtreeLevelExport", &org::sem::DocumentOptions::maxSubtreeLevelExport)
    .def_rw("columns", &org::sem::DocumentOptions::columns)
    .def_rw("todoKeywords", &org::sem::DocumentOptions::todoKeywords)
    .def_rw("doneKeywords", &org::sem::DocumentOptions::doneKeywords)
    .def("getProperties",
         static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::DocumentOptions::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions::getProperties),
         nanobind::arg("kind"),
         nanobind::arg("subKind") = std::nullopt)
    .def("getProperty",
         static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::DocumentOptions::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions::getProperty),
         nanobind::arg("kind"),
         nanobind::arg("subKind") = std::nullopt)
    .def("__repr__", [](org::sem::DocumentOptions const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentOptions const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::DocumentFragment, org::sem::Org>(m, "DocumentFragment")
    .def("__init__",
         [](org::sem::DocumentFragment* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::DocumentFragment();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("baseLine", &org::sem::DocumentFragment::baseLine)
    .def_rw("baseCol", &org::sem::DocumentFragment::baseCol)
    .def("__repr__", [](org::sem::DocumentFragment const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentFragment const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::CriticMarkup::Kind>(m, "CriticMarkupKind", type_registry_guard);
  nanobind::enum_<org::sem::CriticMarkup::Kind>(m, "CriticMarkupKind")
    .value("Deletion", org::sem::CriticMarkup::Kind::Deletion)
    .value("Addition", org::sem::CriticMarkup::Kind::Addition)
    .value("Substitution", org::sem::CriticMarkup::Kind::Substitution)
    .value("Highlighting", org::sem::CriticMarkup::Kind::Highlighting)
    .value("Comment", org::sem::CriticMarkup::Kind::Comment)
    .def("__iter__", [](org::sem::CriticMarkup::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::CriticMarkup::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::CriticMarkup::Kind>();
                     })
    .def("__eq__",
         [](org::sem::CriticMarkup::Kind lhs, org::sem::CriticMarkup::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::CriticMarkup::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::CriticMarkup, org::sem::Org>(m, "CriticMarkup")
    .def("__init__",
         [](org::sem::CriticMarkup* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CriticMarkup();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("kind", &org::sem::CriticMarkup::kind)
    .def("__repr__", [](org::sem::CriticMarkup const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CriticMarkup const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Document, org::sem::Org>(m, "Document")
    .def("__init__",
         [](org::sem::Document* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Document();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("title", &org::sem::Document::title)
    .def_rw("author", &org::sem::Document::author)
    .def_rw("creator", &org::sem::Document::creator)
    .def_rw("filetags", &org::sem::Document::filetags)
    .def_rw("email", &org::sem::Document::email)
    .def_rw("language", &org::sem::Document::language)
    .def_rw("options", &org::sem::Document::options)
    .def_rw("exportFileName", &org::sem::Document::exportFileName)
    .def("getProperties",
         static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Document::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document::getProperties),
         nanobind::arg("kind"),
         nanobind::arg("subKind") = std::nullopt)
    .def("getProperty",
         static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Document::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document::getProperty),
         nanobind::arg("kind"),
         nanobind::arg("subKind") = std::nullopt)
    .def("__repr__", [](org::sem::Document const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Document const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::FileTarget, org::sem::Org>(m, "FileTarget")
    .def("__init__",
         [](org::sem::FileTarget* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::FileTarget();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("path", &org::sem::FileTarget::path)
    .def_rw("line", &org::sem::FileTarget::line)
    .def_rw("searchTarget", &org::sem::FileTarget::searchTarget)
    .def_rw("restrictToHeadlines", &org::sem::FileTarget::restrictToHeadlines)
    .def_rw("targetId", &org::sem::FileTarget::targetId)
    .def_rw("regexp", &org::sem::FileTarget::regexp)
    .def("__repr__", [](org::sem::FileTarget const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::FileTarget const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::TextSeparator, org::sem::Org>(m, "TextSeparator")
    .def("__init__",
         [](org::sem::TextSeparator* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::TextSeparator();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::TextSeparator const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::TextSeparator const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::DocumentGroup, org::sem::Org>(m, "DocumentGroup")
    .def("__init__",
         [](org::sem::DocumentGroup* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::DocumentGroup();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::DocumentGroup const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentGroup const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::File::Document>(m, "FileDocument")
    .def("__init__",
         [](org::sem::File::Document* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::File::Document();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::File::Document const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::File::Document const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::File::Attachment>(m, "FileAttachment")
    .def("__init__",
         [](org::sem::File::Attachment* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::File::Attachment();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::File::Attachment const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::File::Attachment const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::File::Source>(m, "FileSource")
    .def("__init__",
         [](org::sem::File::Source* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::File::Source();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::File::Source const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::File::Source const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::File::Kind>(m, "FileKind", type_registry_guard);
  nanobind::enum_<org::sem::File::Kind>(m, "FileKind")
    .value("Document", org::sem::File::Kind::Document)
    .value("Attachment", org::sem::File::Kind::Attachment)
    .value("Source", org::sem::File::Kind::Source)
    .def("__iter__", [](org::sem::File::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::File::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::File::Kind>();
                     })
    .def("__eq__",
         [](org::sem::File::Kind lhs, org::sem::File::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::File::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::File, org::sem::Org>(m, "File")
    .def("__init__",
         [](org::sem::File* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::File();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("relPath", &org::sem::File::relPath, R"RAW(Relative path from the root directory)RAW")
    .def_rw("absPath", &org::sem::File::absPath, R"RAW(Absolute resolved path to physical file)RAW")
    .def_rw("data", &org::sem::File::data)
    .def("isDocument", static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isDocument))
    .def("getDocument", static_cast<org::sem::File::Document&(org::sem::File::*)()>(&org::sem::File::getDocument))
    .def("isAttachment", static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isAttachment))
    .def("getAttachment", static_cast<org::sem::File::Attachment&(org::sem::File::*)()>(&org::sem::File::getAttachment))
    .def("isSource", static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isSource))
    .def("getSource", static_cast<org::sem::File::Source&(org::sem::File::*)()>(&org::sem::File::getSource))
    .def_static("getFileKindStatic",
                static_cast<org::sem::File::Kind(*)(org::sem::File::Data const&)>(&org::sem::File::getFileKind),
                nanobind::arg("__input"))
    .def("getFileKind", static_cast<org::sem::File::Kind(org::sem::File::*)() const>(&org::sem::File::getFileKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::File::*)() const>(&org::sem::File::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::File::Data const&(org::sem::File::*)() const>(&org::sem::File::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::File::Kind(org::sem::File::*)() const>(&org::sem::File::sub_variant_get_kind))
    .def("__repr__", [](org::sem::File const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::File const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Directory, org::sem::Org>(m, "Directory")
    .def("__init__",
         [](org::sem::Directory* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Directory();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("relPath", &org::sem::Directory::relPath, R"RAW(Relative path from the root directory, empty if this is the root directory)RAW")
    .def_rw("absPath", &org::sem::Directory::absPath, R"RAW(Absolute resolved path to physical directory)RAW")
    .def("__repr__", [](org::sem::Directory const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Directory const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Symlink, org::sem::Org>(m, "Symlink")
    .def("__init__",
         [](org::sem::Symlink* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Symlink();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("isDirectory", &org::sem::Symlink::isDirectory)
    .def_rw("absPath", &org::sem::Symlink::absPath, R"RAW(Absolute path to the symlinked target directory. All relative paths under symlink node use its absolute path as a root.)RAW")
    .def("__repr__", [](org::sem::Symlink const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Symlink const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeIncludeBase")
    .def("__init__",
         [](org::sem::CmdInclude::IncludeBase* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdInclude::IncludeBase();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::CmdInclude::IncludeBase const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::IncludeBase const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdInclude::Example, org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeExample")
    .def("__init__",
         [](org::sem::CmdInclude::Example* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdInclude::Example();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::CmdInclude::Example const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::Example const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdInclude::Export, org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeExport")
    .def("__init__",
         [](org::sem::CmdInclude::Export* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdInclude::Export();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("language", &org::sem::CmdInclude::Export::language, R"RAW(Source code language for export)RAW")
    .def("__repr__", [](org::sem::CmdInclude::Export const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::Export const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdInclude::Custom, org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeCustom")
    .def("__init__",
         [](org::sem::CmdInclude::Custom* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdInclude::Custom();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("blockName", &org::sem::CmdInclude::Custom::blockName, R"RAW(Block name not covered by the default values)RAW")
    .def("__repr__", [](org::sem::CmdInclude::Custom const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::Custom const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdInclude::Src, org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeSrc")
    .def("__init__",
         [](org::sem::CmdInclude::Src* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdInclude::Src();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("language", &org::sem::CmdInclude::Src::language, R"RAW(Source code language for code block)RAW")
    .def("__repr__", [](org::sem::CmdInclude::Src const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::Src const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdInclude::OrgDocument, org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeOrgDocument")
    .def("__init__",
         [](org::sem::CmdInclude::OrgDocument* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdInclude::OrgDocument();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("onlyContent", &org::sem::CmdInclude::OrgDocument::onlyContent, R"RAW(omits any planning lines or property drawers)RAW")
    .def_rw("subtreePath", &org::sem::CmdInclude::OrgDocument::subtreePath, R"RAW(Include first subtree matching path with `file.org::* tree`)RAW")
    .def_rw("minLevel", &org::sem::CmdInclude::OrgDocument::minLevel, R"RAW(The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.)RAW")
    .def_rw("customIdTarget", &org::sem::CmdInclude::OrgDocument::customIdTarget, R"RAW(Include target subtree content with `file.org::#custom`)RAW")
    .def("__repr__", [](org::sem::CmdInclude::OrgDocument const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::OrgDocument const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::CmdInclude::Kind>(m, "CmdIncludeKind", type_registry_guard);
  nanobind::enum_<org::sem::CmdInclude::Kind>(m, "CmdIncludeKind")
    .value("Example", org::sem::CmdInclude::Kind::Example)
    .value("Export", org::sem::CmdInclude::Kind::Export)
    .value("Custom", org::sem::CmdInclude::Kind::Custom)
    .value("Src", org::sem::CmdInclude::Kind::Src)
    .value("OrgDocument", org::sem::CmdInclude::Kind::OrgDocument)
    .def("__iter__", [](org::sem::CmdInclude::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::CmdInclude::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::CmdInclude::Kind>();
                     })
    .def("__eq__",
         [](org::sem::CmdInclude::Kind lhs, org::sem::CmdInclude::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::CmdInclude::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::CmdInclude, org::sem::Org>(m, "CmdInclude")
    .def("__init__",
         [](org::sem::CmdInclude* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdInclude();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("path", &org::sem::CmdInclude::path, R"RAW(Path to include)RAW")
    .def_rw("firstLine", &org::sem::CmdInclude::firstLine, R"RAW(0-based index of the first line to include. NOTE: Org-mode syntax uses 1-based half-open range in the text)RAW")
    .def_rw("lastLine", &org::sem::CmdInclude::lastLine, R"RAW(0-based index of the last line to include)RAW")
    .def_rw("data", &org::sem::CmdInclude::data)
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
                nanobind::arg("__input"))
    .def("getIncludeKind", static_cast<org::sem::CmdInclude::Kind(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getIncludeKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::CmdInclude::Data const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::CmdInclude::Kind(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::sub_variant_get_kind))
    .def("__repr__", [](org::sem::CmdInclude const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmNoNode>, org::imm::ImmId>(m, "ImmIdTNoNode")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmErrorItem>, org::imm::ImmId>(m, "ImmIdTErrorItem")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmErrorGroup>, org::imm::ImmId>(m, "ImmIdTErrorGroup")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmStmt>, org::imm::ImmId>(m, "ImmIdTStmt")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmInline>, org::imm::ImmId>(m, "ImmIdTInline")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmStmtList>, org::imm::ImmId>(m, "ImmIdTStmtList")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmEmpty>, org::imm::ImmId>(m, "ImmIdTEmpty")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmd>, org::imm::ImmId>(m, "ImmIdTCmd")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlock>, org::imm::ImmId>(m, "ImmIdTBlock")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmLineCommand>, org::imm::ImmId>(m, "ImmIdTLineCommand")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmAttached>, org::imm::ImmId>(m, "ImmIdTAttached")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmLeaf>, org::imm::ImmId>(m, "ImmIdTLeaf")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdCaption>, org::imm::ImmId>(m, "ImmIdTCmdCaption")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdCreator>, org::imm::ImmId>(m, "ImmIdTCmdCreator")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdAuthor>, org::imm::ImmId>(m, "ImmIdTCmdAuthor")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdEmail>, org::imm::ImmId>(m, "ImmIdTCmdEmail")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdLanguage>, org::imm::ImmId>(m, "ImmIdTCmdLanguage")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdColumns>, org::imm::ImmId>(m, "ImmIdTCmdColumns")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdName>, org::imm::ImmId>(m, "ImmIdTCmdName")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdCustomArgs>, org::imm::ImmId>(m, "ImmIdTCmdCustomArgs")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdCustomRaw>, org::imm::ImmId>(m, "ImmIdTCmdCustomRaw")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdCustomText>, org::imm::ImmId>(m, "ImmIdTCmdCustomText")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdCall>, org::imm::ImmId>(m, "ImmIdTCmdCall")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdTblfm>, org::imm::ImmId>(m, "ImmIdTCmdTblfm")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmHashTag>, org::imm::ImmId>(m, "ImmIdTHashTag")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmInlineFootnote>, org::imm::ImmId>(m, "ImmIdTInlineFootnote")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmInlineExport>, org::imm::ImmId>(m, "ImmIdTInlineExport")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmTime>, org::imm::ImmId>(m, "ImmIdTTime")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmTimeRange>, org::imm::ImmId>(m, "ImmIdTTimeRange")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmMacro>, org::imm::ImmId>(m, "ImmIdTMacro")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmSymbol>, org::imm::ImmId>(m, "ImmIdTSymbol")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmEscaped>, org::imm::ImmId>(m, "ImmIdTEscaped")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmNewline>, org::imm::ImmId>(m, "ImmIdTNewline")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmSpace>, org::imm::ImmId>(m, "ImmIdTSpace")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmWord>, org::imm::ImmId>(m, "ImmIdTWord")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmAtMention>, org::imm::ImmId>(m, "ImmIdTAtMention")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmRawText>, org::imm::ImmId>(m, "ImmIdTRawText")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmPunctuation>, org::imm::ImmId>(m, "ImmIdTPunctuation")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmPlaceholder>, org::imm::ImmId>(m, "ImmIdTPlaceholder")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBigIdent>, org::imm::ImmId>(m, "ImmIdTBigIdent")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmTextTarget>, org::imm::ImmId>(m, "ImmIdTTextTarget")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmErrorSkipToken>, org::imm::ImmId>(m, "ImmIdTErrorSkipToken")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmErrorSkipGroup>, org::imm::ImmId>(m, "ImmIdTErrorSkipGroup")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmMarkup>, org::imm::ImmId>(m, "ImmIdTMarkup")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBold>, org::imm::ImmId>(m, "ImmIdTBold")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmUnderline>, org::imm::ImmId>(m, "ImmIdTUnderline")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmMonospace>, org::imm::ImmId>(m, "ImmIdTMonospace")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmMarkQuote>, org::imm::ImmId>(m, "ImmIdTMarkQuote")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmVerbatim>, org::imm::ImmId>(m, "ImmIdTVerbatim")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmItalic>, org::imm::ImmId>(m, "ImmIdTItalic")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmStrike>, org::imm::ImmId>(m, "ImmIdTStrike")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmPar>, org::imm::ImmId>(m, "ImmIdTPar")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmRadioTarget>, org::imm::ImmId>(m, "ImmIdTRadioTarget")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmLatex>, org::imm::ImmId>(m, "ImmIdTLatex")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmLink>, org::imm::ImmId>(m, "ImmIdTLink")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockCenter>, org::imm::ImmId>(m, "ImmIdTBlockCenter")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockQuote>, org::imm::ImmId>(m, "ImmIdTBlockQuote")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockComment>, org::imm::ImmId>(m, "ImmIdTBlockComment")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockVerse>, org::imm::ImmId>(m, "ImmIdTBlockVerse")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockDynamicFallback>, org::imm::ImmId>(m, "ImmIdTBlockDynamicFallback")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockExample>, org::imm::ImmId>(m, "ImmIdTBlockExample")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockExport>, org::imm::ImmId>(m, "ImmIdTBlockExport")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockAdmonition>, org::imm::ImmId>(m, "ImmIdTBlockAdmonition")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>, org::imm::ImmId>(m, "ImmIdTBlockCodeEvalResult")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockCode>, org::imm::ImmId>(m, "ImmIdTBlockCode")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmSubtreeLog>, org::imm::ImmId>(m, "ImmIdTSubtreeLog")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmSubtree>, org::imm::ImmId>(m, "ImmIdTSubtree")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCell>, org::imm::ImmId>(m, "ImmIdTCell")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmRow>, org::imm::ImmId>(m, "ImmIdTRow")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmTable>, org::imm::ImmId>(m, "ImmIdTTable")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmParagraph>, org::imm::ImmId>(m, "ImmIdTParagraph")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmColonExample>, org::imm::ImmId>(m, "ImmIdTColonExample")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdAttr>, org::imm::ImmId>(m, "ImmIdTCmdAttr")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdExport>, org::imm::ImmId>(m, "ImmIdTCmdExport")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCall>, org::imm::ImmId>(m, "ImmIdTCall")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmList>, org::imm::ImmId>(m, "ImmIdTList")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmListItem>, org::imm::ImmId>(m, "ImmIdTListItem")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmDocumentOptions>, org::imm::ImmId>(m, "ImmIdTDocumentOptions")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmDocumentFragment>, org::imm::ImmId>(m, "ImmIdTDocumentFragment")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCriticMarkup>, org::imm::ImmId>(m, "ImmIdTCriticMarkup")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmDocument>, org::imm::ImmId>(m, "ImmIdTDocument")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmFileTarget>, org::imm::ImmId>(m, "ImmIdTFileTarget")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmTextSeparator>, org::imm::ImmId>(m, "ImmIdTTextSeparator")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmDocumentGroup>, org::imm::ImmId>(m, "ImmIdTDocumentGroup")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmFile>, org::imm::ImmId>(m, "ImmIdTFile")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmDirectory>, org::imm::ImmId>(m, "ImmIdTDirectory")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmSymlink>, org::imm::ImmId>(m, "ImmIdTSymlink")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdInclude>, org::imm::ImmId>(m, "ImmIdTCmdInclude")
    ;
  nanobind::class_<org::imm::ImmTime::Repeat>(m, "ImmTimeRepeat")
    .def("__init__",
         [](org::imm::ImmTime::Repeat* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmTime::Repeat();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("mode", &org::imm::ImmTime::Repeat::mode, R"RAW(mode)RAW")
    .def_rw("period", &org::imm::ImmTime::Repeat::period, R"RAW(period)RAW")
    .def_rw("count", &org::imm::ImmTime::Repeat::count, R"RAW(count)RAW")
    .def("__eq__",
         static_cast<bool(org::imm::ImmTime::Repeat::*)(org::imm::ImmTime::Repeat const&) const>(&org::imm::ImmTime::Repeat::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmTime::Repeat const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmTime::Repeat const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmTime::Static>(m, "ImmTimeStatic")
    .def("__init__",
         [](org::imm::ImmTime::Static* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmTime::Static();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("repeat", &org::imm::ImmTime::Static::repeat)
    .def_rw("warn", &org::imm::ImmTime::Static::warn)
    .def_rw("time", &org::imm::ImmTime::Static::time)
    .def("__eq__",
         static_cast<bool(org::imm::ImmTime::Static::*)(org::imm::ImmTime::Static const&) const>(&org::imm::ImmTime::Static::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmTime::Static const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmTime::Static const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmTime::Dynamic>(m, "ImmTimeDynamic")
    .def("__init__",
         [](org::imm::ImmTime::Dynamic* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmTime::Dynamic();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("expr", &org::imm::ImmTime::Dynamic::expr)
    .def("__eq__",
         static_cast<bool(org::imm::ImmTime::Dynamic::*)(org::imm::ImmTime::Dynamic const&) const>(&org::imm::ImmTime::Dynamic::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmTime::Dynamic const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmTime::Dynamic const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::imm::ImmTime::TimeKind>(m, "ImmTimeTimeKind", type_registry_guard);
  nanobind::enum_<org::imm::ImmTime::TimeKind>(m, "ImmTimeTimeKind")
    .value("Static", org::imm::ImmTime::TimeKind::Static)
    .value("Dynamic", org::imm::ImmTime::TimeKind::Dynamic)
    .def("__iter__", [](org::imm::ImmTime::TimeKind const& _self) -> org::bind::python::PyEnumIterator<org::imm::ImmTime::TimeKind> {
                     return org::bind::python::PyEnumIterator<org::imm::ImmTime::TimeKind>();
                     })
    .def("__eq__",
         [](org::imm::ImmTime::TimeKind lhs, org::imm::ImmTime::TimeKind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::imm::ImmTime::TimeKind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::imm::ImmSymbol::Param>(m, "ImmSymbolParam")
    .def("__init__",
         [](org::imm::ImmSymbol::Param* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmSymbol::Param();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("key", &org::imm::ImmSymbol::Param::key, R"RAW(Key -- for non-positional)RAW")
    .def_rw("value", &org::imm::ImmSymbol::Param::value, R"RAW(Uninterpreted value)RAW")
    .def("__eq__",
         static_cast<bool(org::imm::ImmSymbol::Param::*)(org::imm::ImmSymbol::Param const&) const>(&org::imm::ImmSymbol::Param::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmSymbol::Param const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmSymbol::Param const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmFile::Document>(m, "ImmFileDocument")
    .def("__init__",
         [](org::imm::ImmFile::Document* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmFile::Document();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::imm::ImmFile::Document::*)(org::imm::ImmFile::Document const&) const>(&org::imm::ImmFile::Document::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmFile::Document const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmFile::Document const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmFile::Attachment>(m, "ImmFileAttachment")
    .def("__init__",
         [](org::imm::ImmFile::Attachment* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmFile::Attachment();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::imm::ImmFile::Attachment::*)(org::imm::ImmFile::Attachment const&) const>(&org::imm::ImmFile::Attachment::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmFile::Attachment const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmFile::Attachment const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmFile::Source>(m, "ImmFileSource")
    .def("__init__",
         [](org::imm::ImmFile::Source* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmFile::Source();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::imm::ImmFile::Source::*)(org::imm::ImmFile::Source const&) const>(&org::imm::ImmFile::Source::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmFile::Source const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmFile::Source const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::imm::ImmFile::Kind>(m, "ImmFileKind", type_registry_guard);
  nanobind::enum_<org::imm::ImmFile::Kind>(m, "ImmFileKind")
    .value("Document", org::imm::ImmFile::Kind::Document)
    .value("Attachment", org::imm::ImmFile::Kind::Attachment)
    .value("Source", org::imm::ImmFile::Kind::Source)
    .def("__iter__", [](org::imm::ImmFile::Kind const& _self) -> org::bind::python::PyEnumIterator<org::imm::ImmFile::Kind> {
                     return org::bind::python::PyEnumIterator<org::imm::ImmFile::Kind>();
                     })
    .def("__eq__",
         [](org::imm::ImmFile::Kind lhs, org::imm::ImmFile::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::imm::ImmFile::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::imm::ImmCmdInclude::IncludeBase>(m, "ImmCmdIncludeIncludeBase")
    .def("__init__",
         [](org::imm::ImmCmdInclude::IncludeBase* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmCmdInclude::IncludeBase();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::imm::ImmCmdInclude::IncludeBase::*)(org::imm::ImmCmdInclude::IncludeBase const&) const>(&org::imm::ImmCmdInclude::IncludeBase::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmCmdInclude::IncludeBase const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmCmdInclude::IncludeBase const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmCmdInclude::Example, org::imm::ImmCmdInclude::IncludeBase>(m, "ImmCmdIncludeExample")
    .def("__init__",
         [](org::imm::ImmCmdInclude::Example* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmCmdInclude::Example();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::imm::ImmCmdInclude::Example::*)(org::imm::ImmCmdInclude::Example const&) const>(&org::imm::ImmCmdInclude::Example::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmCmdInclude::Example const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmCmdInclude::Example const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmCmdInclude::Export, org::imm::ImmCmdInclude::IncludeBase>(m, "ImmCmdIncludeExport")
    .def("__init__",
         [](org::imm::ImmCmdInclude::Export* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmCmdInclude::Export();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("language", &org::imm::ImmCmdInclude::Export::language, R"RAW(Source code language for export)RAW")
    .def("__eq__",
         static_cast<bool(org::imm::ImmCmdInclude::Export::*)(org::imm::ImmCmdInclude::Export const&) const>(&org::imm::ImmCmdInclude::Export::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmCmdInclude::Export const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmCmdInclude::Export const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmCmdInclude::Custom, org::imm::ImmCmdInclude::IncludeBase>(m, "ImmCmdIncludeCustom")
    .def("__init__",
         [](org::imm::ImmCmdInclude::Custom* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmCmdInclude::Custom();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("blockName", &org::imm::ImmCmdInclude::Custom::blockName, R"RAW(Block name not covered by the default values)RAW")
    .def("__eq__",
         static_cast<bool(org::imm::ImmCmdInclude::Custom::*)(org::imm::ImmCmdInclude::Custom const&) const>(&org::imm::ImmCmdInclude::Custom::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmCmdInclude::Custom const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmCmdInclude::Custom const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmCmdInclude::Src, org::imm::ImmCmdInclude::IncludeBase>(m, "ImmCmdIncludeSrc")
    .def("__init__",
         [](org::imm::ImmCmdInclude::Src* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmCmdInclude::Src();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("language", &org::imm::ImmCmdInclude::Src::language, R"RAW(Source code language for code block)RAW")
    .def("__eq__",
         static_cast<bool(org::imm::ImmCmdInclude::Src::*)(org::imm::ImmCmdInclude::Src const&) const>(&org::imm::ImmCmdInclude::Src::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmCmdInclude::Src const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmCmdInclude::Src const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmCmdInclude::OrgDocument, org::imm::ImmCmdInclude::IncludeBase>(m, "ImmCmdIncludeOrgDocument")
    .def("__init__",
         [](org::imm::ImmCmdInclude::OrgDocument* result, nanobind::kwargs const& kwargs) {
         new(result) org::imm::ImmCmdInclude::OrgDocument();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("onlyContent", &org::imm::ImmCmdInclude::OrgDocument::onlyContent, R"RAW(omits any planning lines or property drawers)RAW")
    .def_rw("subtreePath", &org::imm::ImmCmdInclude::OrgDocument::subtreePath, R"RAW(Include first subtree matching path with `file.org::* tree`)RAW")
    .def_rw("minLevel", &org::imm::ImmCmdInclude::OrgDocument::minLevel, R"RAW(The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.)RAW")
    .def_rw("customIdTarget", &org::imm::ImmCmdInclude::OrgDocument::customIdTarget, R"RAW(Include target subtree content with `file.org::#custom`)RAW")
    .def("__eq__",
         static_cast<bool(org::imm::ImmCmdInclude::OrgDocument::*)(org::imm::ImmCmdInclude::OrgDocument const&) const>(&org::imm::ImmCmdInclude::OrgDocument::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmCmdInclude::OrgDocument const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmCmdInclude::OrgDocument const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::imm::ImmCmdInclude::Kind>(m, "ImmCmdIncludeKind", type_registry_guard);
  nanobind::enum_<org::imm::ImmCmdInclude::Kind>(m, "ImmCmdIncludeKind")
    .value("Example", org::imm::ImmCmdInclude::Kind::Example)
    .value("Export", org::imm::ImmCmdInclude::Kind::Export)
    .value("Custom", org::imm::ImmCmdInclude::Kind::Custom)
    .value("Src", org::imm::ImmCmdInclude::Kind::Src)
    .value("OrgDocument", org::imm::ImmCmdInclude::Kind::OrgDocument)
    .def("__iter__", [](org::imm::ImmCmdInclude::Kind const& _self) -> org::bind::python::PyEnumIterator<org::imm::ImmCmdInclude::Kind> {
                     return org::bind::python::PyEnumIterator<org::imm::ImmCmdInclude::Kind>();
                     })
    .def("__eq__",
         [](org::imm::ImmCmdInclude::Kind lhs, org::imm::ImmCmdInclude::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::imm::ImmCmdInclude::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::imm::ImmAdapterOrgAPI, org::imm::ImmAdapterVirtualBase>(m, "ImmAdapterOrgAPI")
    ;
  nanobind::class_<org::sem::Cmd, org::sem::Stmt>(m, "Cmd")
    .def_rw("attrs", &org::sem::Cmd::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Cmd::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Cmd::getAttrs),
         nanobind::arg("key") = std::nullopt,
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Cmd::*)(hstd::Str const&) const>(&org::sem::Cmd::getFirstAttr),
         nanobind::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    ;
  nanobind::class_<org::sem::CmdCustomRaw, org::sem::Stmt>(m, "CmdCustomRaw")
    .def("__init__",
         [](org::sem::CmdCustomRaw* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdCustomRaw();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::CmdCustomRaw::name)
    .def_rw("isAttached", &org::sem::CmdCustomRaw::isAttached)
    .def_rw("text", &org::sem::CmdCustomRaw::text)
    .def("__repr__", [](org::sem::CmdCustomRaw const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCustomRaw const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdCustomText, org::sem::Stmt>(m, "CmdCustomText")
    .def("__init__",
         [](org::sem::CmdCustomText* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdCustomText();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::CmdCustomText::name)
    .def_rw("isAttached", &org::sem::CmdCustomText::isAttached)
    .def_rw("text", &org::sem::CmdCustomText::text)
    .def("__repr__", [](org::sem::CmdCustomText const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCustomText const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Link, org::sem::Stmt>(m, "Link")
    .def("__init__",
         [](org::sem::Link* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Link();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("description", &org::sem::Link::description)
    .def_rw("target", &org::sem::Link::target)
    .def("__repr__", [](org::sem::Link const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Link const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockComment, org::sem::Stmt>(m, "BlockComment")
    .def("__init__",
         [](org::sem::BlockComment* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::BlockComment();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::BlockComment const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockComment const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Paragraph, org::sem::Stmt>(m, "Paragraph")
    .def("__init__",
         [](org::sem::Paragraph* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Paragraph();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
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
    .def("__repr__", [](org::sem::Paragraph const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Paragraph const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::List, org::sem::Stmt>(m, "List")
    .def("__init__",
         [](org::sem::List* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::List();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getListAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::List::*)(hstd::Str const&) const>(&org::sem::List::getListAttrs),
         nanobind::arg("key"))
    .def("getListFormattingMode", static_cast<ListFormattingMode(org::sem::List::*)() const>(&org::sem::List::getListFormattingMode))
    .def("isDescriptionList", static_cast<bool(org::sem::List::*)() const>(&org::sem::List::isDescriptionList), R"RAW(List is marked as description if any list item has a header)RAW")
    .def("isNumberedList", static_cast<bool(org::sem::List::*)() const>(&org::sem::List::isNumberedList), R"RAW(List is marked as numbered if any list item has bullet text set)RAW")
    .def("__repr__", [](org::sem::List const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::List const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::HashTag, org::sem::Inline>(m, "HashTag")
    .def("__init__",
         [](org::sem::HashTag* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::HashTag();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::HashTag::text)
    .def("__repr__", [](org::sem::HashTag const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::HashTag const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::InlineFootnote, org::sem::Inline>(m, "InlineFootnote")
    .def("__init__",
         [](org::sem::InlineFootnote* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::InlineFootnote();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("tag", &org::sem::InlineFootnote::tag, R"RAW(Footnote text target name)RAW")
    .def_rw("definition", &org::sem::InlineFootnote::definition, R"RAW(Link to possibly resolved definition)RAW")
    .def("__repr__", [](org::sem::InlineFootnote const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::InlineFootnote const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::InlineExport, org::sem::Inline>(m, "InlineExport")
    .def("__init__",
         [](org::sem::InlineExport* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::InlineExport();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("exporter", &org::sem::InlineExport::exporter)
    .def_rw("content", &org::sem::InlineExport::content)
    .def("__repr__", [](org::sem::InlineExport const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::InlineExport const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Escaped, org::sem::Leaf>(m, "Escaped")
    .def("__init__",
         [](org::sem::Escaped* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Escaped();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Escaped const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Escaped const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Newline, org::sem::Leaf>(m, "Newline")
    .def("__init__",
         [](org::sem::Newline* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Newline();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Newline const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Newline const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Space, org::sem::Leaf>(m, "Space")
    .def("__init__",
         [](org::sem::Space* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Space();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Space const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Space const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Word, org::sem::Leaf>(m, "Word")
    .def("__init__",
         [](org::sem::Word* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Word();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Word const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Word const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::AtMention, org::sem::Leaf>(m, "AtMention")
    .def("__init__",
         [](org::sem::AtMention* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::AtMention();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::AtMention const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AtMention const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::RawText, org::sem::Leaf>(m, "RawText")
    .def("__init__",
         [](org::sem::RawText* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::RawText();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::RawText const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::RawText const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Punctuation, org::sem::Leaf>(m, "Punctuation")
    .def("__init__",
         [](org::sem::Punctuation* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Punctuation();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Punctuation const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Punctuation const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Placeholder, org::sem::Leaf>(m, "Placeholder")
    .def("__init__",
         [](org::sem::Placeholder* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Placeholder();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Placeholder const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Placeholder const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BigIdent, org::sem::Leaf>(m, "BigIdent")
    .def("__init__",
         [](org::sem::BigIdent* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::BigIdent();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::BigIdent const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BigIdent const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::TextTarget, org::sem::Leaf>(m, "TextTarget")
    .def("__init__",
         [](org::sem::TextTarget* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::TextTarget();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::TextTarget const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::TextTarget const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::ErrorSkipToken, org::sem::Leaf>(m, "ErrorSkipToken")
    .def("__init__",
         [](org::sem::ErrorSkipToken* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::ErrorSkipToken();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::ErrorSkipToken const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ErrorSkipToken const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Bold, org::sem::Markup>(m, "Bold")
    .def("__init__",
         [](org::sem::Bold* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Bold();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Bold const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Bold const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Underline, org::sem::Markup>(m, "Underline")
    .def("__init__",
         [](org::sem::Underline* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Underline();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Underline const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Underline const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Monospace, org::sem::Markup>(m, "Monospace")
    .def("__init__",
         [](org::sem::Monospace* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Monospace();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Monospace const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Monospace const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::MarkQuote, org::sem::Markup>(m, "MarkQuote")
    .def("__init__",
         [](org::sem::MarkQuote* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::MarkQuote();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::MarkQuote const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::MarkQuote const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Verbatim, org::sem::Markup>(m, "Verbatim")
    .def("__init__",
         [](org::sem::Verbatim* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Verbatim();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Verbatim const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Verbatim const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Italic, org::sem::Markup>(m, "Italic")
    .def("__init__",
         [](org::sem::Italic* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Italic();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Italic const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Italic const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Strike, org::sem::Markup>(m, "Strike")
    .def("__init__",
         [](org::sem::Strike* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Strike();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Strike const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Strike const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Par, org::sem::Markup>(m, "Par")
    .def("__init__",
         [](org::sem::Par* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Par();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Par const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Par const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmAdapterStmtAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterStmtAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterSubtreeAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterSubtreeAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterNoNodeAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterNoNodeAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterAttrAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterAttrAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterAttrListAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterAttrListAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterAttrsAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterAttrsAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterErrorItemAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterErrorItemAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterErrorGroupAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterErrorGroupAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterErrorSkipGroupAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterErrorSkipGroupAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterErrorSkipTokenAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterErrorSkipTokenAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterStmtListAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterStmtListAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterEmptyAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterEmptyAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterInlineAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterInlineAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterTimeAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterTimeAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterTimeRangeAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterTimeRangeAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterMacroAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterMacroAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterSymbolAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterSymbolAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterLeafAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterLeafAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterMarkupAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterMarkupAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterLatexAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterLatexAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterSubtreeLogAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterSubtreeLogAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterColonExampleAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterColonExampleAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCallAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterCallAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterFileAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterFileAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterDirectoryAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterDirectoryAPI")
    .def("getFsSubnode",
         static_cast<std::optional<org::imm::ImmAdapter>(org::imm::ImmAdapterDirectoryAPI::*)(hstd::Str const&, bool) const>(&org::imm::ImmAdapterDirectoryAPI::getFsSubnode),
         nanobind::arg("name"),
         nanobind::arg("withPath") = 1)
    ;
  nanobind::class_<org::imm::ImmAdapterSymlinkAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterSymlinkAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterDocumentFragmentAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterDocumentFragmentAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCriticMarkupAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterCriticMarkupAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterListItemAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterListItemAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterDocumentOptionsAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterDocumentOptionsAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterDocumentAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterDocumentAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterFileTargetAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterFileTargetAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterTextSeparatorAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterTextSeparatorAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCmdIncludeAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterCmdIncludeAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterDocumentGroupAPI, org::imm::ImmAdapterOrgAPI>(m, "ImmAdapterDocumentGroupAPI")
    ;
  nanobind::class_<org::sem::Block, org::sem::Cmd>(m, "Block")
    ;
  nanobind::class_<org::sem::LineCommand, org::sem::Cmd>(m, "LineCommand")
    ;
  nanobind::class_<org::sem::CmdCreator, org::sem::Cmd>(m, "CmdCreator")
    .def("__init__",
         [](org::sem::CmdCreator* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdCreator();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::CmdCreator::text, R"RAW(Creator name text)RAW")
    .def("__repr__", [](org::sem::CmdCreator const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCreator const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdAuthor, org::sem::Cmd>(m, "CmdAuthor")
    .def("__init__",
         [](org::sem::CmdAuthor* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdAuthor();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::CmdAuthor::text, R"RAW(Author name text)RAW")
    .def("__repr__", [](org::sem::CmdAuthor const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdAuthor const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdEmail, org::sem::Cmd>(m, "CmdEmail")
    .def("__init__",
         [](org::sem::CmdEmail* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdEmail();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::CmdEmail::text)
    .def("__repr__", [](org::sem::CmdEmail const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdEmail const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdLanguage, org::sem::Cmd>(m, "CmdLanguage")
    .def("__init__",
         [](org::sem::CmdLanguage* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdLanguage();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::CmdLanguage::text)
    .def("__repr__", [](org::sem::CmdLanguage const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdLanguage const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdCustomArgs, org::sem::Cmd>(m, "CmdCustomArgs")
    .def("__init__",
         [](org::sem::CmdCustomArgs* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdCustomArgs();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::CmdCustomArgs::name)
    .def_rw("isAttached", &org::sem::CmdCustomArgs::isAttached)
    .def("__repr__", [](org::sem::CmdCustomArgs const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCustomArgs const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdTblfm, org::sem::Cmd>(m, "CmdTblfm")
    .def("__init__",
         [](org::sem::CmdTblfm* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdTblfm();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("expr", &org::sem::CmdTblfm::expr)
    .def("__repr__", [](org::sem::CmdTblfm const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdTblfm const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Cell, org::sem::Cmd>(m, "Cell")
    .def("__init__",
         [](org::sem::Cell* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Cell();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("isBlock", &org::sem::Cell::isBlock, R"RAW(Single-line pipe cell or `#+cell:` command)RAW")
    .def("__repr__", [](org::sem::Cell const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Cell const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Row, org::sem::Cmd>(m, "Row")
    .def("__init__",
         [](org::sem::Row* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Row();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("cells", &org::sem::Row::cells, R"RAW(List of cells on the row)RAW")
    .def_rw("isBlock", &org::sem::Row::isBlock, R"RAW(Single-line pipe cell or `#+cell:` command)RAW")
    .def("__repr__", [](org::sem::Row const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Row const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmAdapterCmdAPI, org::imm::ImmAdapterStmtAPI>(m, "ImmAdapterCmdAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCmdCustomRawAPI, org::imm::ImmAdapterStmtAPI>(m, "ImmAdapterCmdCustomRawAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCmdCustomTextAPI, org::imm::ImmAdapterStmtAPI>(m, "ImmAdapterCmdCustomTextAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterLinkAPI, org::imm::ImmAdapterStmtAPI>(m, "ImmAdapterLinkAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterBlockCommentAPI, org::imm::ImmAdapterStmtAPI>(m, "ImmAdapterBlockCommentAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterParagraphAPI, org::imm::ImmAdapterStmtAPI>(m, "ImmAdapterParagraphAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterListAPI, org::imm::ImmAdapterStmtAPI>(m, "ImmAdapterListAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmStmt>, org::imm::ImmAdapterStmtAPI>(m, "ImmStmtAdapter")
    .def("getValue", static_cast<org::imm::ImmStmtValueRead(org::imm::ImmAdapterT<org::imm::ImmStmt>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmStmt>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmSubtree>, org::imm::ImmAdapterSubtreeAPI>(m, "ImmSubtreeAdapter")
    .def("getValue", static_cast<org::imm::ImmSubtreeValueRead(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmNoNode>, org::imm::ImmAdapterNoNodeAPI>(m, "ImmNoNodeAdapter")
    .def("getValue", static_cast<org::imm::ImmNoNodeValueRead(org::imm::ImmAdapterT<org::imm::ImmNoNode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmNoNode>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmErrorItem>, org::imm::ImmAdapterErrorItemAPI>(m, "ImmErrorItemAdapter")
    .def("getValue", static_cast<org::imm::ImmErrorItemValueRead(org::imm::ImmAdapterT<org::imm::ImmErrorItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorItem>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmErrorGroup>, org::imm::ImmAdapterErrorGroupAPI>(m, "ImmErrorGroupAdapter")
    .def("getValue", static_cast<org::imm::ImmErrorGroupValueRead(org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>, org::imm::ImmAdapterErrorSkipGroupAPI>(m, "ImmErrorSkipGroupAdapter")
    .def("getValue", static_cast<org::imm::ImmErrorSkipGroupValueRead(org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken>, org::imm::ImmAdapterErrorSkipTokenAPI>(m, "ImmErrorSkipTokenAdapter")
    .def("getValue", static_cast<org::imm::ImmErrorSkipTokenValueRead(org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmStmtList>, org::imm::ImmAdapterStmtListAPI>(m, "ImmStmtListAdapter")
    .def("getValue", static_cast<org::imm::ImmStmtListValueRead(org::imm::ImmAdapterT<org::imm::ImmStmtList>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmStmtList>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmEmpty>, org::imm::ImmAdapterEmptyAPI>(m, "ImmEmptyAdapter")
    .def("getValue", static_cast<org::imm::ImmEmptyValueRead(org::imm::ImmAdapterT<org::imm::ImmEmpty>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmEmpty>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterHashTagAPI, org::imm::ImmAdapterInlineAPI>(m, "ImmAdapterHashTagAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterInlineFootnoteAPI, org::imm::ImmAdapterInlineAPI>(m, "ImmAdapterInlineFootnoteAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterSubtreeCompletionAPI, org::imm::ImmAdapterInlineAPI>(m, "ImmAdapterSubtreeCompletionAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmInline>, org::imm::ImmAdapterInlineAPI>(m, "ImmInlineAdapter")
    .def("getValue", static_cast<org::imm::ImmInlineValueRead(org::imm::ImmAdapterT<org::imm::ImmInline>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInline>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmTime>, org::imm::ImmAdapterTimeAPI>(m, "ImmTimeAdapter")
    .def("getValue", static_cast<org::imm::ImmTimeValueRead(org::imm::ImmAdapterT<org::imm::ImmTime>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTime>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmTimeRange>, org::imm::ImmAdapterTimeRangeAPI>(m, "ImmTimeRangeAdapter")
    .def("getValue", static_cast<org::imm::ImmTimeRangeValueRead(org::imm::ImmAdapterT<org::imm::ImmTimeRange>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTimeRange>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmMacro>, org::imm::ImmAdapterMacroAPI>(m, "ImmMacroAdapter")
    .def("getValue", static_cast<org::imm::ImmMacroValueRead(org::imm::ImmAdapterT<org::imm::ImmMacro>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMacro>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmSymbol>, org::imm::ImmAdapterSymbolAPI>(m, "ImmSymbolAdapter")
    .def("getValue", static_cast<org::imm::ImmSymbolValueRead(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterEscapedAPI, org::imm::ImmAdapterLeafAPI>(m, "ImmAdapterEscapedAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterNewlineAPI, org::imm::ImmAdapterLeafAPI>(m, "ImmAdapterNewlineAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterSpaceAPI, org::imm::ImmAdapterLeafAPI>(m, "ImmAdapterSpaceAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterWordAPI, org::imm::ImmAdapterLeafAPI>(m, "ImmAdapterWordAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterAtMentionAPI, org::imm::ImmAdapterLeafAPI>(m, "ImmAdapterAtMentionAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterRawTextAPI, org::imm::ImmAdapterLeafAPI>(m, "ImmAdapterRawTextAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterPunctuationAPI, org::imm::ImmAdapterLeafAPI>(m, "ImmAdapterPunctuationAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterPlaceholderAPI, org::imm::ImmAdapterLeafAPI>(m, "ImmAdapterPlaceholderAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterBigIdentAPI, org::imm::ImmAdapterLeafAPI>(m, "ImmAdapterBigIdentAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterTextTargetAPI, org::imm::ImmAdapterLeafAPI>(m, "ImmAdapterTextTargetAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmLeaf>, org::imm::ImmAdapterLeafAPI>(m, "ImmLeafAdapter")
    .def("getValue", static_cast<org::imm::ImmLeafValueRead(org::imm::ImmAdapterT<org::imm::ImmLeaf>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLeaf>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterBoldAPI, org::imm::ImmAdapterMarkupAPI>(m, "ImmAdapterBoldAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterUnderlineAPI, org::imm::ImmAdapterMarkupAPI>(m, "ImmAdapterUnderlineAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterMonospaceAPI, org::imm::ImmAdapterMarkupAPI>(m, "ImmAdapterMonospaceAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterMarkQuoteAPI, org::imm::ImmAdapterMarkupAPI>(m, "ImmAdapterMarkQuoteAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterRadioTargetAPI, org::imm::ImmAdapterMarkupAPI>(m, "ImmAdapterRadioTargetAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterVerbatimAPI, org::imm::ImmAdapterMarkupAPI>(m, "ImmAdapterVerbatimAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterItalicAPI, org::imm::ImmAdapterMarkupAPI>(m, "ImmAdapterItalicAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterStrikeAPI, org::imm::ImmAdapterMarkupAPI>(m, "ImmAdapterStrikeAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterParAPI, org::imm::ImmAdapterMarkupAPI>(m, "ImmAdapterParAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmMarkup>, org::imm::ImmAdapterMarkupAPI>(m, "ImmMarkupAdapter")
    .def("getValue", static_cast<org::imm::ImmMarkupValueRead(org::imm::ImmAdapterT<org::imm::ImmMarkup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMarkup>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmLatex>, org::imm::ImmAdapterLatexAPI>(m, "ImmLatexAdapter")
    .def("getValue", static_cast<org::imm::ImmLatexValueRead(org::imm::ImmAdapterT<org::imm::ImmLatex>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLatex>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>, org::imm::ImmAdapterSubtreeLogAPI>(m, "ImmSubtreeLogAdapter")
    .def("getValue", static_cast<org::imm::ImmSubtreeLogValueRead(org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmColonExample>, org::imm::ImmAdapterColonExampleAPI>(m, "ImmColonExampleAdapter")
    .def("getValue", static_cast<org::imm::ImmColonExampleValueRead(org::imm::ImmAdapterT<org::imm::ImmColonExample>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmColonExample>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCall>, org::imm::ImmAdapterCallAPI>(m, "ImmCallAdapter")
    .def("getValue", static_cast<org::imm::ImmCallValueRead(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmFile>, org::imm::ImmAdapterFileAPI>(m, "ImmFileAdapter")
    .def("getValue", static_cast<org::imm::ImmFileValueRead(org::imm::ImmAdapterT<org::imm::ImmFile>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFile>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmDirectory>, org::imm::ImmAdapterDirectoryAPI>(m, "ImmDirectoryAdapter")
    .def("getValue", static_cast<org::imm::ImmDirectoryValueRead(org::imm::ImmAdapterT<org::imm::ImmDirectory>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDirectory>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmSymlink>, org::imm::ImmAdapterSymlinkAPI>(m, "ImmSymlinkAdapter")
    .def("getValue", static_cast<org::imm::ImmSymlinkValueRead(org::imm::ImmAdapterT<org::imm::ImmSymlink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymlink>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>, org::imm::ImmAdapterDocumentFragmentAPI>(m, "ImmDocumentFragmentAdapter")
    .def("getValue", static_cast<org::imm::ImmDocumentFragmentValueRead(org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>, org::imm::ImmAdapterCriticMarkupAPI>(m, "ImmCriticMarkupAdapter")
    .def("getValue", static_cast<org::imm::ImmCriticMarkupValueRead(org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmListItem>, org::imm::ImmAdapterListItemAPI>(m, "ImmListItemAdapter")
    .def("getValue", static_cast<org::imm::ImmListItemValueRead(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>, org::imm::ImmAdapterDocumentOptionsAPI>(m, "ImmDocumentOptionsAdapter")
    .def("getValue", static_cast<org::imm::ImmDocumentOptionsValueRead(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmDocument>, org::imm::ImmAdapterDocumentAPI>(m, "ImmDocumentAdapter")
    .def("getValue", static_cast<org::imm::ImmDocumentValueRead(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmFileTarget>, org::imm::ImmAdapterFileTargetAPI>(m, "ImmFileTargetAdapter")
    .def("getValue", static_cast<org::imm::ImmFileTargetValueRead(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmTextSeparator>, org::imm::ImmAdapterTextSeparatorAPI>(m, "ImmTextSeparatorAdapter")
    .def("getValue", static_cast<org::imm::ImmTextSeparatorValueRead(org::imm::ImmAdapterT<org::imm::ImmTextSeparator>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTextSeparator>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdInclude>, org::imm::ImmAdapterCmdIncludeAPI>(m, "ImmCmdIncludeAdapter")
    .def("getValue", static_cast<org::imm::ImmCmdIncludeValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>, org::imm::ImmAdapterDocumentGroupAPI>(m, "ImmDocumentGroupAdapter")
    .def("getValue", static_cast<org::imm::ImmDocumentGroupValueRead(org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>::getValue))
    ;
  nanobind::class_<org::sem::BlockCenter, org::sem::Block>(m, "BlockCenter")
    .def("__init__",
         [](org::sem::BlockCenter* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::BlockCenter();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::BlockCenter const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCenter const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockQuote, org::sem::Block>(m, "BlockQuote")
    .def("__init__",
         [](org::sem::BlockQuote* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::BlockQuote();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::BlockQuote const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockQuote const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockVerse, org::sem::Block>(m, "BlockVerse")
    .def("__init__",
         [](org::sem::BlockVerse* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::BlockVerse();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::BlockVerse const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockVerse const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockDynamicFallback, org::sem::Block>(m, "BlockDynamicFallback")
    .def("__init__",
         [](org::sem::BlockDynamicFallback* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::BlockDynamicFallback();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::BlockDynamicFallback::name)
    .def("__repr__", [](org::sem::BlockDynamicFallback const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockDynamicFallback const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockExample, org::sem::Block>(m, "BlockExample")
    .def("__init__",
         [](org::sem::BlockExample* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::BlockExample();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::BlockExample const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockExample const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockExport, org::sem::Block>(m, "BlockExport")
    .def("__init__",
         [](org::sem::BlockExport* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::BlockExport();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("exporter", &org::sem::BlockExport::exporter)
    .def_rw("content", &org::sem::BlockExport::content)
    .def("getPlacement", static_cast<hstd::Opt<hstd::Str>(org::sem::BlockExport::*)() const>(&org::sem::BlockExport::getPlacement), R"RAW(Return value of the :placement attribute if present)RAW")
    .def("__repr__", [](org::sem::BlockExport const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockExport const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockAdmonition, org::sem::Block>(m, "BlockAdmonition")
    .def("__init__",
         [](org::sem::BlockAdmonition* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::BlockAdmonition();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::BlockAdmonition const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockAdmonition const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockCodeEvalResult, org::sem::Block>(m, "BlockCodeEvalResult")
    .def("__init__",
         [](org::sem::BlockCodeEvalResult* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::BlockCodeEvalResult();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("raw", &org::sem::BlockCodeEvalResult::raw)
    .def_rw("node", &org::sem::BlockCodeEvalResult::node)
    .def("__repr__", [](org::sem::BlockCodeEvalResult const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeEvalResult const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockCode, org::sem::Block>(m, "BlockCode")
    .def("__init__",
         [](org::sem::BlockCode* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::BlockCode();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("lang", &org::sem::BlockCode::lang, R"RAW(Code block language name)RAW")
    .def_rw("result", &org::sem::BlockCode::result, R"RAW(Code evaluation results)RAW")
    .def_rw("lines", &org::sem::BlockCode::lines, R"RAW(Collected code lines)RAW")
    .def_rw("switches", &org::sem::BlockCode::switches, R"RAW(Dash-based switches for code block execution)RAW")
    .def("getVariable",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockCode::*)(hstd::Str const&) const>(&org::sem::BlockCode::getVariable),
         nanobind::arg("varname"))
    .def("__repr__", [](org::sem::BlockCode const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCode const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Table, org::sem::Block>(m, "Table")
    .def("__init__",
         [](org::sem::Table* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::Table();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("rows", &org::sem::Table::rows, R"RAW(List of rows for the table)RAW")
    .def_rw("isBlock", &org::sem::Table::isBlock, R"RAW(Single-line pipe cell or `#+cell:` command)RAW")
    .def("__repr__", [](org::sem::Table const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Table const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Attached, org::sem::LineCommand>(m, "Attached")
    ;
  nanobind::class_<org::imm::ImmAdapterLineCommandAPI, org::imm::ImmAdapterCmdAPI>(m, "ImmAdapterLineCommandAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCmdCustomArgsAPI, org::imm::ImmAdapterCmdAPI>(m, "ImmAdapterCmdCustomArgsAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCmdCreatorAPI, org::imm::ImmAdapterCmdAPI>(m, "ImmAdapterCmdCreatorAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCmdAuthorAPI, org::imm::ImmAdapterCmdAPI>(m, "ImmAdapterCmdAuthorAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCmdEmailAPI, org::imm::ImmAdapterCmdAPI>(m, "ImmAdapterCmdEmailAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCmdLanguageAPI, org::imm::ImmAdapterCmdAPI>(m, "ImmAdapterCmdLanguageAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCmdTblfmAPI, org::imm::ImmAdapterCmdAPI>(m, "ImmAdapterCmdTblfmAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterBlockAPI, org::imm::ImmAdapterCmdAPI>(m, "ImmAdapterBlockAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCellAPI, org::imm::ImmAdapterCmdAPI>(m, "ImmAdapterCellAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterRowAPI, org::imm::ImmAdapterCmdAPI>(m, "ImmAdapterRowAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmd>, org::imm::ImmAdapterCmdAPI>(m, "ImmCmdAdapter")
    .def("getValue", static_cast<org::imm::ImmCmdValueRead(org::imm::ImmAdapterT<org::imm::ImmCmd>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmd>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>, org::imm::ImmAdapterCmdCustomRawAPI>(m, "ImmCmdCustomRawAdapter")
    .def("getValue", static_cast<org::imm::ImmCmdCustomRawValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>, org::imm::ImmAdapterCmdCustomTextAPI>(m, "ImmCmdCustomTextAdapter")
    .def("getValue", static_cast<org::imm::ImmCmdCustomTextValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmLink>, org::imm::ImmAdapterLinkAPI>(m, "ImmLinkAdapter")
    .def("getValue", static_cast<org::imm::ImmLinkValueRead(org::imm::ImmAdapterT<org::imm::ImmLink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLink>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockComment>, org::imm::ImmAdapterBlockCommentAPI>(m, "ImmBlockCommentAdapter")
    .def("getValue", static_cast<org::imm::ImmBlockCommentValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockComment>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockComment>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmParagraph>, org::imm::ImmAdapterParagraphAPI>(m, "ImmParagraphAdapter")
    .def("getValue", static_cast<org::imm::ImmParagraphValueRead(org::imm::ImmAdapterT<org::imm::ImmParagraph>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmParagraph>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmList>, org::imm::ImmAdapterListAPI>(m, "ImmListAdapter")
    .def("getValue", static_cast<org::imm::ImmListValueRead(org::imm::ImmAdapterT<org::imm::ImmList>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmList>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmHashTag>, org::imm::ImmAdapterHashTagAPI>(m, "ImmHashTagAdapter")
    .def("getValue", static_cast<org::imm::ImmHashTagValueRead(org::imm::ImmAdapterT<org::imm::ImmHashTag>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmHashTag>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>, org::imm::ImmAdapterInlineFootnoteAPI>(m, "ImmInlineFootnoteAdapter")
    .def("getValue", static_cast<org::imm::ImmInlineFootnoteValueRead(org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmEscaped>, org::imm::ImmAdapterEscapedAPI>(m, "ImmEscapedAdapter")
    .def("getValue", static_cast<org::imm::ImmEscapedValueRead(org::imm::ImmAdapterT<org::imm::ImmEscaped>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmEscaped>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmNewline>, org::imm::ImmAdapterNewlineAPI>(m, "ImmNewlineAdapter")
    .def("getValue", static_cast<org::imm::ImmNewlineValueRead(org::imm::ImmAdapterT<org::imm::ImmNewline>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmNewline>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmSpace>, org::imm::ImmAdapterSpaceAPI>(m, "ImmSpaceAdapter")
    .def("getValue", static_cast<org::imm::ImmSpaceValueRead(org::imm::ImmAdapterT<org::imm::ImmSpace>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSpace>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmWord>, org::imm::ImmAdapterWordAPI>(m, "ImmWordAdapter")
    .def("getValue", static_cast<org::imm::ImmWordValueRead(org::imm::ImmAdapterT<org::imm::ImmWord>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmWord>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmAtMention>, org::imm::ImmAdapterAtMentionAPI>(m, "ImmAtMentionAdapter")
    .def("getValue", static_cast<org::imm::ImmAtMentionValueRead(org::imm::ImmAdapterT<org::imm::ImmAtMention>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmAtMention>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmRawText>, org::imm::ImmAdapterRawTextAPI>(m, "ImmRawTextAdapter")
    .def("getValue", static_cast<org::imm::ImmRawTextValueRead(org::imm::ImmAdapterT<org::imm::ImmRawText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRawText>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmPunctuation>, org::imm::ImmAdapterPunctuationAPI>(m, "ImmPunctuationAdapter")
    .def("getValue", static_cast<org::imm::ImmPunctuationValueRead(org::imm::ImmAdapterT<org::imm::ImmPunctuation>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmPunctuation>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmPlaceholder>, org::imm::ImmAdapterPlaceholderAPI>(m, "ImmPlaceholderAdapter")
    .def("getValue", static_cast<org::imm::ImmPlaceholderValueRead(org::imm::ImmAdapterT<org::imm::ImmPlaceholder>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmPlaceholder>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBigIdent>, org::imm::ImmAdapterBigIdentAPI>(m, "ImmBigIdentAdapter")
    .def("getValue", static_cast<org::imm::ImmBigIdentValueRead(org::imm::ImmAdapterT<org::imm::ImmBigIdent>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBigIdent>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmTextTarget>, org::imm::ImmAdapterTextTargetAPI>(m, "ImmTextTargetAdapter")
    .def("getValue", static_cast<org::imm::ImmTextTargetValueRead(org::imm::ImmAdapterT<org::imm::ImmTextTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTextTarget>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBold>, org::imm::ImmAdapterBoldAPI>(m, "ImmBoldAdapter")
    .def("getValue", static_cast<org::imm::ImmBoldValueRead(org::imm::ImmAdapterT<org::imm::ImmBold>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBold>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmUnderline>, org::imm::ImmAdapterUnderlineAPI>(m, "ImmUnderlineAdapter")
    .def("getValue", static_cast<org::imm::ImmUnderlineValueRead(org::imm::ImmAdapterT<org::imm::ImmUnderline>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmUnderline>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmMonospace>, org::imm::ImmAdapterMonospaceAPI>(m, "ImmMonospaceAdapter")
    .def("getValue", static_cast<org::imm::ImmMonospaceValueRead(org::imm::ImmAdapterT<org::imm::ImmMonospace>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMonospace>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmMarkQuote>, org::imm::ImmAdapterMarkQuoteAPI>(m, "ImmMarkQuoteAdapter")
    .def("getValue", static_cast<org::imm::ImmMarkQuoteValueRead(org::imm::ImmAdapterT<org::imm::ImmMarkQuote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMarkQuote>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmRadioTarget>, org::imm::ImmAdapterRadioTargetAPI>(m, "ImmRadioTargetAdapter")
    .def("getValue", static_cast<org::imm::ImmRadioTargetValueRead(org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmVerbatim>, org::imm::ImmAdapterVerbatimAPI>(m, "ImmVerbatimAdapter")
    .def("getValue", static_cast<org::imm::ImmVerbatimValueRead(org::imm::ImmAdapterT<org::imm::ImmVerbatim>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmVerbatim>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmItalic>, org::imm::ImmAdapterItalicAPI>(m, "ImmItalicAdapter")
    .def("getValue", static_cast<org::imm::ImmItalicValueRead(org::imm::ImmAdapterT<org::imm::ImmItalic>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmItalic>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmStrike>, org::imm::ImmAdapterStrikeAPI>(m, "ImmStrikeAdapter")
    .def("getValue", static_cast<org::imm::ImmStrikeValueRead(org::imm::ImmAdapterT<org::imm::ImmStrike>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmStrike>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmPar>, org::imm::ImmAdapterParAPI>(m, "ImmParAdapter")
    .def("getValue", static_cast<org::imm::ImmParValueRead(org::imm::ImmAdapterT<org::imm::ImmPar>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmPar>::getValue))
    ;
  nanobind::class_<org::sem::CmdCaption, org::sem::Attached>(m, "CmdCaption")
    .def("__init__",
         [](org::sem::CmdCaption* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdCaption();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::CmdCaption::text, R"RAW(Content description)RAW")
    .def("__repr__", [](org::sem::CmdCaption const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCaption const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdColumns, org::sem::Attached>(m, "CmdColumns")
    .def("__init__",
         [](org::sem::CmdColumns* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdColumns();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("view", &org::sem::CmdColumns::view)
    .def("__repr__", [](org::sem::CmdColumns const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdColumns const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdName, org::sem::Attached>(m, "CmdName")
    .def("__init__",
         [](org::sem::CmdName* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdName();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::CmdName::name)
    .def("__repr__", [](org::sem::CmdName const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdName const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdCall, org::sem::Attached>(m, "CmdCall")
    .def("__init__",
         [](org::sem::CmdCall* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdCall();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::CmdCall::name, R"RAW(Code block call name)RAW")
    .def_rw("fileName", &org::sem::CmdCall::fileName, R"RAW(Which file code block should come from)RAW")
    .def_rw("insideHeaderAttrs", &org::sem::CmdCall::insideHeaderAttrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_rw("callAttrs", &org::sem::CmdCall::callAttrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_rw("endHeaderAttrs", &org::sem::CmdCall::endHeaderAttrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_rw("result", &org::sem::CmdCall::result, R"RAW(Code evaluation results)RAW")
    .def("__repr__", [](org::sem::CmdCall const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCall const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdAttr, org::sem::Attached>(m, "CmdAttr")
    .def("__init__",
         [](org::sem::CmdAttr* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdAttr();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("target", &org::sem::CmdAttr::target)
    .def("__repr__", [](org::sem::CmdAttr const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdAttr const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdExport, org::sem::Attached>(m, "CmdExport")
    .def("__init__",
         [](org::sem::CmdExport* result, nanobind::kwargs const& kwargs) {
         new(result) org::sem::CmdExport();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("exporter", &org::sem::CmdExport::exporter)
    .def_rw("content", &org::sem::CmdExport::content)
    .def("__repr__", [](org::sem::CmdExport const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdExport const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmAdapterAttachedAPI, org::imm::ImmAdapterLineCommandAPI>(m, "ImmAdapterAttachedAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmLineCommand>, org::imm::ImmAdapterLineCommandAPI>(m, "ImmLineCommandAdapter")
    .def("getValue", static_cast<org::imm::ImmLineCommandValueRead(org::imm::ImmAdapterT<org::imm::ImmLineCommand>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLineCommand>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>, org::imm::ImmAdapterCmdCustomArgsAPI>(m, "ImmCmdCustomArgsAdapter")
    .def("getValue", static_cast<org::imm::ImmCmdCustomArgsValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCreator>, org::imm::ImmAdapterCmdCreatorAPI>(m, "ImmCmdCreatorAdapter")
    .def("getValue", static_cast<org::imm::ImmCmdCreatorValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdCreator>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCreator>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>, org::imm::ImmAdapterCmdAuthorAPI>(m, "ImmCmdAuthorAdapter")
    .def("getValue", static_cast<org::imm::ImmCmdAuthorValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdEmail>, org::imm::ImmAdapterCmdEmailAPI>(m, "ImmCmdEmailAdapter")
    .def("getValue", static_cast<org::imm::ImmCmdEmailValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdEmail>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdEmail>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>, org::imm::ImmAdapterCmdLanguageAPI>(m, "ImmCmdLanguageAdapter")
    .def("getValue", static_cast<org::imm::ImmCmdLanguageValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>, org::imm::ImmAdapterCmdTblfmAPI>(m, "ImmCmdTblfmAdapter")
    .def("getValue", static_cast<org::imm::ImmCmdTblfmValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterBlockCenterAPI, org::imm::ImmAdapterBlockAPI>(m, "ImmAdapterBlockCenterAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterBlockQuoteAPI, org::imm::ImmAdapterBlockAPI>(m, "ImmAdapterBlockQuoteAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterBlockVerseAPI, org::imm::ImmAdapterBlockAPI>(m, "ImmAdapterBlockVerseAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterBlockExampleAPI, org::imm::ImmAdapterBlockAPI>(m, "ImmAdapterBlockExampleAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterInlineExportAPI, org::imm::ImmAdapterBlockAPI>(m, "ImmAdapterInlineExportAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCmdExportAPI, org::imm::ImmAdapterBlockAPI>(m, "ImmAdapterCmdExportAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterBlockExportAPI, org::imm::ImmAdapterBlockAPI>(m, "ImmAdapterBlockExportAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterBlockDynamicFallbackAPI, org::imm::ImmAdapterBlockAPI>(m, "ImmAdapterBlockDynamicFallbackAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterBlockAdmonitionAPI, org::imm::ImmAdapterBlockAPI>(m, "ImmAdapterBlockAdmonitionAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterBlockCodeEvalResultAPI, org::imm::ImmAdapterBlockAPI>(m, "ImmAdapterBlockCodeEvalResultAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterBlockCodeAPI, org::imm::ImmAdapterBlockAPI>(m, "ImmAdapterBlockCodeAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterTableAPI, org::imm::ImmAdapterBlockAPI>(m, "ImmAdapterTableAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlock>, org::imm::ImmAdapterBlockAPI>(m, "ImmBlockAdapter")
    .def("getValue", static_cast<org::imm::ImmBlockValueRead(org::imm::ImmAdapterT<org::imm::ImmBlock>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlock>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCell>, org::imm::ImmAdapterCellAPI>(m, "ImmCellAdapter")
    .def("getValue", static_cast<org::imm::ImmCellValueRead(org::imm::ImmAdapterT<org::imm::ImmCell>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCell>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmRow>, org::imm::ImmAdapterRowAPI>(m, "ImmRowAdapter")
    .def("getValue", static_cast<org::imm::ImmRowValueRead(org::imm::ImmAdapterT<org::imm::ImmRow>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRow>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterCmdCaptionAPI, org::imm::ImmAdapterAttachedAPI>(m, "ImmAdapterCmdCaptionAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCmdColumnsAPI, org::imm::ImmAdapterAttachedAPI>(m, "ImmAdapterCmdColumnsAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCmdNameAPI, org::imm::ImmAdapterAttachedAPI>(m, "ImmAdapterCmdNameAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCmdCallAPI, org::imm::ImmAdapterAttachedAPI>(m, "ImmAdapterCmdCallAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCmdResultsAPI, org::imm::ImmAdapterAttachedAPI>(m, "ImmAdapterCmdResultsAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterCmdAttrAPI, org::imm::ImmAdapterAttachedAPI>(m, "ImmAdapterCmdAttrAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmAttached>, org::imm::ImmAdapterAttachedAPI>(m, "ImmAttachedAdapter")
    .def("getValue", static_cast<org::imm::ImmAttachedValueRead(org::imm::ImmAdapterT<org::imm::ImmAttached>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmAttached>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockCenter>, org::imm::ImmAdapterBlockCenterAPI>(m, "ImmBlockCenterAdapter")
    .def("getValue", static_cast<org::imm::ImmBlockCenterValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockCenter>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCenter>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockQuote>, org::imm::ImmAdapterBlockQuoteAPI>(m, "ImmBlockQuoteAdapter")
    .def("getValue", static_cast<org::imm::ImmBlockQuoteValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockQuote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockQuote>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockVerse>, org::imm::ImmAdapterBlockVerseAPI>(m, "ImmBlockVerseAdapter")
    .def("getValue", static_cast<org::imm::ImmBlockVerseValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockVerse>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockVerse>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockExample>, org::imm::ImmAdapterBlockExampleAPI>(m, "ImmBlockExampleAdapter")
    .def("getValue", static_cast<org::imm::ImmBlockExampleValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockExample>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockExample>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmInlineExport>, org::imm::ImmAdapterInlineExportAPI>(m, "ImmInlineExportAdapter")
    .def("getValue", static_cast<org::imm::ImmInlineExportValueRead(org::imm::ImmAdapterT<org::imm::ImmInlineExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineExport>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdExport>, org::imm::ImmAdapterCmdExportAPI>(m, "ImmCmdExportAdapter")
    .def("getValue", static_cast<org::imm::ImmCmdExportValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdExport>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockExport>, org::imm::ImmAdapterBlockExportAPI>(m, "ImmBlockExportAdapter")
    .def("getValue", static_cast<org::imm::ImmBlockExportValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockExport>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>, org::imm::ImmAdapterBlockDynamicFallbackAPI>(m, "ImmBlockDynamicFallbackAdapter")
    .def("getValue", static_cast<org::imm::ImmBlockDynamicFallbackValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>, org::imm::ImmAdapterBlockAdmonitionAPI>(m, "ImmBlockAdmonitionAdapter")
    .def("getValue", static_cast<org::imm::ImmBlockAdmonitionValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>, org::imm::ImmAdapterBlockCodeEvalResultAPI>(m, "ImmBlockCodeEvalResultAdapter")
    .def("getValue", static_cast<org::imm::ImmBlockCodeEvalResultValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockCode>, org::imm::ImmAdapterBlockCodeAPI>(m, "ImmBlockCodeAdapter")
    .def("getValue", static_cast<org::imm::ImmBlockCodeValueRead(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmTable>, org::imm::ImmAdapterTableAPI>(m, "ImmTableAdapter")
    .def("getValue", static_cast<org::imm::ImmTableValueRead(org::imm::ImmAdapterT<org::imm::ImmTable>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTable>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCaption>, org::imm::ImmAdapterCmdCaptionAPI>(m, "ImmCmdCaptionAdapter")
    .def("getValue", static_cast<org::imm::ImmCmdCaptionValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdColumns>, org::imm::ImmAdapterCmdColumnsAPI>(m, "ImmCmdColumnsAdapter")
    .def("getValue", static_cast<org::imm::ImmCmdColumnsValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdName>, org::imm::ImmAdapterCmdNameAPI>(m, "ImmCmdNameAdapter")
    .def("getValue", static_cast<org::imm::ImmCmdNameValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdName>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdName>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCall>, org::imm::ImmAdapterCmdCallAPI>(m, "ImmCmdCallAdapter")
    .def("getValue", static_cast<org::imm::ImmCmdCallValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getValue))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdAttr>, org::imm::ImmAdapterCmdAttrAPI>(m, "ImmCmdAttrAdapter")
    .def("getValue", static_cast<org::imm::ImmCmdAttrValueRead(org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::getValue))
    ;
  bind_enum_iterator<CheckboxState>(m, "CheckboxState", type_registry_guard);
  nanobind::enum_<CheckboxState>(m, "CheckboxState")
    .value("None", CheckboxState::None)
    .value("Done", CheckboxState::Done)
    .value("Empty", CheckboxState::Empty)
    .value("Partial", CheckboxState::Partial)
    .def("__iter__", [](CheckboxState const& _self) -> org::bind::python::PyEnumIterator<CheckboxState> {
                     return org::bind::python::PyEnumIterator<CheckboxState>();
                     })
    .def("__eq__",
         [](CheckboxState lhs, CheckboxState rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](CheckboxState it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<SubtreeTodoSource>(m, "SubtreeTodoSource", type_registry_guard);
  nanobind::enum_<SubtreeTodoSource>(m, "SubtreeTodoSource")
    .value("Checkbox", SubtreeTodoSource::Checkbox, R"RAW(Only count checkbox subnodes as a progress completion)RAW")
    .value("Todo", SubtreeTodoSource::Todo, R"RAW(Use subtrees with todo keywords)RAW")
    .value("Both", SubtreeTodoSource::Both, R"RAW(Use both subtrees and todo keywords)RAW")
    .def("__iter__", [](SubtreeTodoSource const& _self) -> org::bind::python::PyEnumIterator<SubtreeTodoSource> {
                     return org::bind::python::PyEnumIterator<SubtreeTodoSource>();
                     })
    .def("__eq__",
         [](SubtreeTodoSource lhs, SubtreeTodoSource rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](SubtreeTodoSource it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<ListFormattingMode>(m, "ListFormattingMode", type_registry_guard);
  nanobind::enum_<ListFormattingMode>(m, "ListFormattingMode")
    .value("None", ListFormattingMode::None, R"RAW(Default, no custom formatting)RAW")
    .value("Table1D1Col", ListFormattingMode::Table1D1Col, R"RAW(one column, each table item is an individual row)RAW")
    .value("Table1D2Col", ListFormattingMode::Table1D2Col, R"RAW(for description lists, treat header row as an individual column)RAW")
    .value("Table2DColFirst", ListFormattingMode::Table2DColFirst, R"RAW(for tables tables with arbitrary column count, treat the first level of items as column names, treat all nested elements in these columns as row values)RAW")
    .value("Table2DRowFirst", ListFormattingMode::Table2DRowFirst, R"RAW(for tables with arbitrary column count, each top-level list item is an individual row, then each item in the nested list is a cell on this row.)RAW")
    .def("__iter__", [](ListFormattingMode const& _self) -> org::bind::python::PyEnumIterator<ListFormattingMode> {
                     return org::bind::python::PyEnumIterator<ListFormattingMode>();
                     })
    .def("__eq__",
         [](ListFormattingMode lhs, ListFormattingMode rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](ListFormattingMode it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<InitialSubtreeVisibility>(m, "InitialSubtreeVisibility", type_registry_guard);
  nanobind::enum_<InitialSubtreeVisibility>(m, "InitialSubtreeVisibility")
    .value("Overview", InitialSubtreeVisibility::Overview)
    .value("Content", InitialSubtreeVisibility::Content)
    .value("ShowAll", InitialSubtreeVisibility::ShowAll)
    .value("Show2Levels", InitialSubtreeVisibility::Show2Levels)
    .value("Show3Levels", InitialSubtreeVisibility::Show3Levels)
    .value("Show4Levels", InitialSubtreeVisibility::Show4Levels)
    .value("Show5Levels", InitialSubtreeVisibility::Show5Levels)
    .value("ShowEverything", InitialSubtreeVisibility::ShowEverything)
    .def("__iter__", [](InitialSubtreeVisibility const& _self) -> org::bind::python::PyEnumIterator<InitialSubtreeVisibility> {
                     return org::bind::python::PyEnumIterator<InitialSubtreeVisibility>();
                     })
    .def("__eq__",
         [](InitialSubtreeVisibility lhs, InitialSubtreeVisibility rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](InitialSubtreeVisibility it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<OrgSpecName>(m, "OrgSpecName", type_registry_guard);
  nanobind::enum_<OrgSpecName>(m, "OrgSpecName")
    .value("Unnamed", OrgSpecName::Unnamed)
    .value("Result", OrgSpecName::Result)
    .value("Year", OrgSpecName::Year)
    .value("Day", OrgSpecName::Day)
    .value("Clock", OrgSpecName::Clock)
    .value("Repeater", OrgSpecName::Repeater)
    .value("Warn", OrgSpecName::Warn)
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
    .def("__iter__", [](OrgSpecName const& _self) -> org::bind::python::PyEnumIterator<OrgSpecName> {
                     return org::bind::python::PyEnumIterator<OrgSpecName>();
                     })
    .def("__eq__",
         [](OrgSpecName lhs, OrgSpecName rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](OrgSpecName it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<OrgNodeKind>(m, "OrgNodeKind", type_registry_guard);
  nanobind::enum_<OrgNodeKind>(m, "OrgNodeKind")
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
    .value("CmdEmail", OrgNodeKind::CmdEmail, R"RAW(`#+email:`)RAW")
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
    .value("CmdKeywords", OrgNodeKind::CmdKeywords)
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
    .value("ErrorInfoToken", OrgNodeKind::ErrorInfoToken, R"RAW(Error leaf node inserted into the parse tree on failure)RAW")
    .value("ErrorSkipGroup", OrgNodeKind::ErrorSkipGroup, R"RAW(Parent node for one or more tokens skipped during error recovery)RAW")
    .value("ErrorSkipToken", OrgNodeKind::ErrorSkipToken, R"RAW(Single token node skipped while the parser searched for recovery point)RAW")
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
    .def("__iter__", [](OrgNodeKind const& _self) -> org::bind::python::PyEnumIterator<OrgNodeKind> {
                     return org::bind::python::PyEnumIterator<OrgNodeKind>();
                     })
    .def("__eq__",
         [](OrgNodeKind lhs, OrgNodeKind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](OrgNodeKind it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<OrgTokenKind>(m, "OrgTokenKind", type_registry_guard);
  nanobind::enum_<OrgTokenKind>(m, "OrgTokenKind")
    .value("Ampersand", OrgTokenKind::Ampersand)
    .value("AngleBegin", OrgTokenKind::AngleBegin)
    .value("AngleEnd", OrgTokenKind::AngleEnd)
    .value("AnyPunct", OrgTokenKind::AnyPunct)
    .value("Asterisk", OrgTokenKind::Asterisk)
    .value("At", OrgTokenKind::At)
    .value("Backtick", OrgTokenKind::Backtick)
    .value("BigIdent", OrgTokenKind::BigIdent)
    .value("BoldBegin", OrgTokenKind::BoldBegin)
    .value("BoldEnd", OrgTokenKind::BoldEnd)
    .value("BoldUnknown", OrgTokenKind::BoldUnknown)
    .value("BraceBegin", OrgTokenKind::BraceBegin)
    .value("BraceEnd", OrgTokenKind::BraceEnd)
    .value("Checkbox", OrgTokenKind::Checkbox)
    .value("Circumflex", OrgTokenKind::Circumflex)
    .value("CmdAdmonitionEnd", OrgTokenKind::CmdAdmonitionEnd)
    .value("CmdAttr", OrgTokenKind::CmdAttr)
    .value("CmdAuthor", OrgTokenKind::CmdAuthor)
    .value("CmdBindRaw", OrgTokenKind::CmdBindRaw)
    .value("CmdCall", OrgTokenKind::CmdCall)
    .value("CmdCaption", OrgTokenKind::CmdCaption)
    .value("CmdCategoryRaw", OrgTokenKind::CmdCategoryRaw)
    .value("CmdCell", OrgTokenKind::CmdCell)
    .value("CmdCellBegin", OrgTokenKind::CmdCellBegin)
    .value("CmdCellEnd", OrgTokenKind::CmdCellEnd)
    .value("CmdCenterBegin", OrgTokenKind::CmdCenterBegin)
    .value("CmdCenterEnd", OrgTokenKind::CmdCenterEnd)
    .value("CmdColonIdent", OrgTokenKind::CmdColonIdent)
    .value("CmdColumns", OrgTokenKind::CmdColumns)
    .value("CmdCommentBegin", OrgTokenKind::CmdCommentBegin)
    .value("CmdCommentEnd", OrgTokenKind::CmdCommentEnd)
    .value("CmdConstants", OrgTokenKind::CmdConstants)
    .value("CmdContentBegin", OrgTokenKind::CmdContentBegin)
    .value("CmdContentEnd", OrgTokenKind::CmdContentEnd)
    .value("CmdCreator", OrgTokenKind::CmdCreator)
    .value("CmdCustomRaw", OrgTokenKind::CmdCustomRaw)
    .value("CmdDateRaw", OrgTokenKind::CmdDateRaw)
    .value("CmdDescription", OrgTokenKind::CmdDescription)
    .value("CmdDrawersRaw", OrgTokenKind::CmdDrawersRaw)
    .value("CmdDynamicBegin", OrgTokenKind::CmdDynamicBegin)
    .value("CmdDynamicBlockBegin", OrgTokenKind::CmdDynamicBlockBegin)
    .value("CmdDynamicBlockEnd", OrgTokenKind::CmdDynamicBlockEnd)
    .value("CmdDynamicEnd", OrgTokenKind::CmdDynamicEnd)
    .value("CmdEmailRaw", OrgTokenKind::CmdEmailRaw)
    .value("CmdExampleBegin", OrgTokenKind::CmdExampleBegin)
    .value("CmdExampleEnd", OrgTokenKind::CmdExampleEnd)
    .value("CmdExampleLine", OrgTokenKind::CmdExampleLine)
    .value("CmdExcludeTagsRaw", OrgTokenKind::CmdExcludeTagsRaw)
    .value("CmdExportBegin", OrgTokenKind::CmdExportBegin)
    .value("CmdExportEnd", OrgTokenKind::CmdExportEnd)
    .value("CmdExportLine", OrgTokenKind::CmdExportLine)
    .value("CmdFiletags", OrgTokenKind::CmdFiletags)
    .value("CmdFlag", OrgTokenKind::CmdFlag)
    .value("CmdHeader", OrgTokenKind::CmdHeader)
    .value("CmdHtmlHeadRaw", OrgTokenKind::CmdHtmlHeadRaw)
    .value("CmdInclude", OrgTokenKind::CmdInclude)
    .value("CmdLanguage", OrgTokenKind::CmdLanguage)
    .value("CmdLatexClass", OrgTokenKind::CmdLatexClass)
    .value("CmdLatexClassOptions", OrgTokenKind::CmdLatexClassOptions)
    .value("CmdLatexCompiler", OrgTokenKind::CmdLatexCompiler)
    .value("CmdLatexHeader", OrgTokenKind::CmdLatexHeader)
    .value("CmdLatexHeaderExtraRaw", OrgTokenKind::CmdLatexHeaderExtraRaw)
    .value("CmdLinkRaw", OrgTokenKind::CmdLinkRaw)
    .value("CmdMacroRaw", OrgTokenKind::CmdMacroRaw)
    .value("CmdName", OrgTokenKind::CmdName)
    .value("CmdOptions", OrgTokenKind::CmdOptions)
    .value("CmdPrefix", OrgTokenKind::CmdPrefix)
    .value("CmdPrioritiesRaw", OrgTokenKind::CmdPrioritiesRaw)
    .value("CmdPropertyArgs", OrgTokenKind::CmdPropertyArgs)
    .value("CmdPropertyRaw", OrgTokenKind::CmdPropertyRaw)
    .value("CmdPropertyText", OrgTokenKind::CmdPropertyText)
    .value("CmdQuoteBegin", OrgTokenKind::CmdQuoteBegin)
    .value("CmdQuoteEnd", OrgTokenKind::CmdQuoteEnd)
    .value("CmdRawArg", OrgTokenKind::CmdRawArg)
    .value("CmdResults", OrgTokenKind::CmdResults)
    .value("CmdRow", OrgTokenKind::CmdRow)
    .value("CmdRowBegin", OrgTokenKind::CmdRowBegin)
    .value("CmdRowEnd", OrgTokenKind::CmdRowEnd)
    .value("CmdSelectTagsRaw", OrgTokenKind::CmdSelectTagsRaw)
    .value("CmdSeqTodoRaw", OrgTokenKind::CmdSeqTodoRaw)
    .value("CmdKeywordsRaw", OrgTokenKind::CmdKeywordsRaw)
    .value("CmdSetupfileRaw", OrgTokenKind::CmdSetupfileRaw)
    .value("CmdSrcBegin", OrgTokenKind::CmdSrcBegin)
    .value("CmdSrcEnd", OrgTokenKind::CmdSrcEnd)
    .value("CmdStartup", OrgTokenKind::CmdStartup)
    .value("CmdTableBegin", OrgTokenKind::CmdTableBegin)
    .value("CmdTableEnd", OrgTokenKind::CmdTableEnd)
    .value("CmdTagsRaw", OrgTokenKind::CmdTagsRaw)
    .value("CmdTblfm", OrgTokenKind::CmdTblfm)
    .value("CmdTitle", OrgTokenKind::CmdTitle)
    .value("CmdVerseBegin", OrgTokenKind::CmdVerseBegin)
    .value("CmdVerseEnd", OrgTokenKind::CmdVerseEnd)
    .value("Colon", OrgTokenKind::Colon)
    .value("ColonArgumentsProperty", OrgTokenKind::ColonArgumentsProperty)
    .value("ColonEnd", OrgTokenKind::ColonEnd)
    .value("ColonExampleLine", OrgTokenKind::ColonExampleLine)
    .value("ColonLiteralProperty", OrgTokenKind::ColonLiteralProperty)
    .value("ColonLogbook", OrgTokenKind::ColonLogbook)
    .value("ColonProperties", OrgTokenKind::ColonProperties)
    .value("ColonPropertyText", OrgTokenKind::ColonPropertyText)
    .value("Comma", OrgTokenKind::Comma)
    .value("Comment", OrgTokenKind::Comment)
    .value("CriticAddBegin", OrgTokenKind::CriticAddBegin)
    .value("CriticAddEnd", OrgTokenKind::CriticAddEnd)
    .value("CriticCommentBegin", OrgTokenKind::CriticCommentBegin)
    .value("CriticCommentEnd", OrgTokenKind::CriticCommentEnd)
    .value("CriticDeleteBegin", OrgTokenKind::CriticDeleteBegin)
    .value("CriticDeleteEnd", OrgTokenKind::CriticDeleteEnd)
    .value("CriticHighlightBegin", OrgTokenKind::CriticHighlightBegin)
    .value("CriticHighlightEnd", OrgTokenKind::CriticHighlightEnd)
    .value("CriticReplaceBegin", OrgTokenKind::CriticReplaceBegin)
    .value("CriticReplaceEnd", OrgTokenKind::CriticReplaceEnd)
    .value("CriticReplaceMiddle", OrgTokenKind::CriticReplaceMiddle)
    .value("CurlyBegin", OrgTokenKind::CurlyBegin)
    .value("CurlyEnd", OrgTokenKind::CurlyEnd)
    .value("Date", OrgTokenKind::Date)
    .value("Dedent", OrgTokenKind::Dedent)
    .value("Dollar", OrgTokenKind::Dollar)
    .value("DoubleAngleBegin", OrgTokenKind::DoubleAngleBegin)
    .value("DoubleAngleEnd", OrgTokenKind::DoubleAngleEnd)
    .value("DoubleColon", OrgTokenKind::DoubleColon)
    .value("DoubleDash", OrgTokenKind::DoubleDash)
    .value("DoubleHash", OrgTokenKind::DoubleHash)
    .value("DoubleQuote", OrgTokenKind::DoubleQuote)
    .value("DoubleSlash", OrgTokenKind::DoubleSlash)
    .value("ActiveDynamicTimeContent", OrgTokenKind::ActiveDynamicTimeContent)
    .value("InactiveDynamicTimeContent", OrgTokenKind::InactiveDynamicTimeContent)
    .value("EndOfFile", OrgTokenKind::EndOfFile)
    .value("Equals", OrgTokenKind::Equals)
    .value("Escaped", OrgTokenKind::Escaped)
    .value("Exclamation", OrgTokenKind::Exclamation)
    .value("FootnoteInlineBegin", OrgTokenKind::FootnoteInlineBegin)
    .value("FootnoteLinked", OrgTokenKind::FootnoteLinked)
    .value("ForwardSlash", OrgTokenKind::ForwardSlash)
    .value("HashIdent", OrgTokenKind::HashIdent)
    .value("HashTagBegin", OrgTokenKind::HashTagBegin)
    .value("Indent", OrgTokenKind::Indent)
    .value("InlineExportBackend", OrgTokenKind::InlineExportBackend)
    .value("InlineExportContent", OrgTokenKind::InlineExportContent)
    .value("ItalicBegin", OrgTokenKind::ItalicBegin)
    .value("ItalicEnd", OrgTokenKind::ItalicEnd)
    .value("ItalicUnknown", OrgTokenKind::ItalicUnknown)
    .value("LatexInlineRaw", OrgTokenKind::LatexInlineRaw)
    .value("LatexParBegin", OrgTokenKind::LatexParBegin)
    .value("LatexParEnd", OrgTokenKind::LatexParEnd)
    .value("LeadingMinus", OrgTokenKind::LeadingMinus)
    .value("LeadingNumber", OrgTokenKind::LeadingNumber)
    .value("LeadingPipe", OrgTokenKind::LeadingPipe)
    .value("LeadingPlus", OrgTokenKind::LeadingPlus)
    .value("LeadingSpace", OrgTokenKind::LeadingSpace)
    .value("LineCommand", OrgTokenKind::LineCommand)
    .value("LinkBegin", OrgTokenKind::LinkBegin)
    .value("LinkDescriptionBegin", OrgTokenKind::LinkDescriptionBegin)
    .value("LinkDescriptionEnd", OrgTokenKind::LinkDescriptionEnd)
    .value("LinkEnd", OrgTokenKind::LinkEnd)
    .value("LinkFull", OrgTokenKind::LinkFull)
    .value("LinkProtocol", OrgTokenKind::LinkProtocol)
    .value("LinkProtocolAttachment", OrgTokenKind::LinkProtocolAttachment)
    .value("LinkProtocolCustomId", OrgTokenKind::LinkProtocolCustomId)
    .value("LinkProtocolFile", OrgTokenKind::LinkProtocolFile)
    .value("LinkProtocolHttp", OrgTokenKind::LinkProtocolHttp)
    .value("LinkProtocolId", OrgTokenKind::LinkProtocolId)
    .value("LinkProtocolInternal", OrgTokenKind::LinkProtocolInternal)
    .value("LinkProtocolTitle", OrgTokenKind::LinkProtocolTitle)
    .value("LinkSplit", OrgTokenKind::LinkSplit)
    .value("LinkTarget", OrgTokenKind::LinkTarget)
    .value("LinkTargetBegin", OrgTokenKind::LinkTargetBegin)
    .value("LinkTargetEnd", OrgTokenKind::LinkTargetEnd)
    .value("LinkTargetFile", OrgTokenKind::LinkTargetFile)
    .value("ListBegin", OrgTokenKind::ListBegin)
    .value("ListEnd", OrgTokenKind::ListEnd)
    .value("ListItemBegin", OrgTokenKind::ListItemBegin)
    .value("ListItemEnd", OrgTokenKind::ListItemEnd)
    .value("LongNewline", OrgTokenKind::LongNewline)
    .value("MediumNewline", OrgTokenKind::MediumNewline)
    .value("Minus", OrgTokenKind::Minus)
    .value("MiscUnicode", OrgTokenKind::MiscUnicode)
    .value("MonospaceBegin", OrgTokenKind::MonospaceBegin)
    .value("MonospaceEnd", OrgTokenKind::MonospaceEnd)
    .value("MonospaceUnknown", OrgTokenKind::MonospaceUnknown)
    .value("Newline", OrgTokenKind::Newline)
    .value("Number", OrgTokenKind::Number)
    .value("ParBegin", OrgTokenKind::ParBegin)
    .value("ParEnd", OrgTokenKind::ParEnd)
    .value("Percent", OrgTokenKind::Percent)
    .value("Pipe", OrgTokenKind::Pipe)
    .value("Placeholder", OrgTokenKind::Placeholder)
    .value("Plus", OrgTokenKind::Plus)
    .value("Punctuation", OrgTokenKind::Punctuation)
    .value("RawText", OrgTokenKind::RawText)
    .value("SameIndent", OrgTokenKind::SameIndent)
    .value("Semicolon", OrgTokenKind::Semicolon)
    .value("SingleQuote", OrgTokenKind::SingleQuote)
    .value("SrcContent", OrgTokenKind::SrcContent)
    .value("StmtListBegin", OrgTokenKind::StmtListBegin)
    .value("StmtListEnd", OrgTokenKind::StmtListEnd)
    .value("StrikeBegin", OrgTokenKind::StrikeBegin)
    .value("StrikeEnd", OrgTokenKind::StrikeEnd)
    .value("StrikeUnknown", OrgTokenKind::StrikeUnknown)
    .value("SubtreeCompletion", OrgTokenKind::SubtreeCompletion)
    .value("SubtreePriority", OrgTokenKind::SubtreePriority)
    .value("SubtreeStars", OrgTokenKind::SubtreeStars)
    .value("Symbol", OrgTokenKind::Symbol)
    .value("TableSeparator", OrgTokenKind::TableSeparator)
    .value("TextSeparator", OrgTokenKind::TextSeparator)
    .value("TextSrcBegin", OrgTokenKind::TextSrcBegin)
    .value("Tilda", OrgTokenKind::Tilda)
    .value("Time", OrgTokenKind::Time)
    .value("TimeArrow", OrgTokenKind::TimeArrow)
    .value("TimeRepeaterDuration", OrgTokenKind::TimeRepeaterDuration)
    .value("TimeRepeaterSpec", OrgTokenKind::TimeRepeaterSpec)
    .value("TimeWarnPeriod", OrgTokenKind::TimeWarnPeriod)
    .value("TrailingPipe", OrgTokenKind::TrailingPipe)
    .value("TreeClock", OrgTokenKind::TreeClock)
    .value("TreeTime", OrgTokenKind::TreeTime)
    .value("TripleAngleBegin", OrgTokenKind::TripleAngleBegin)
    .value("TripleAngleEnd", OrgTokenKind::TripleAngleEnd)
    .value("Underline", OrgTokenKind::Underline)
    .value("UnderlineBegin", OrgTokenKind::UnderlineBegin)
    .value("UnderlineEnd", OrgTokenKind::UnderlineEnd)
    .value("UnderlineUnknown", OrgTokenKind::UnderlineUnknown)
    .value("Unknown", OrgTokenKind::Unknown)
    .value("VerbatimBegin", OrgTokenKind::VerbatimBegin)
    .value("VerbatimEnd", OrgTokenKind::VerbatimEnd)
    .value("VerbatimUnknown", OrgTokenKind::VerbatimUnknown)
    .value("Whitespace", OrgTokenKind::Whitespace)
    .value("Word", OrgTokenKind::Word)
    .def("__iter__", [](OrgTokenKind const& _self) -> org::bind::python::PyEnumIterator<OrgTokenKind> {
                     return org::bind::python::PyEnumIterator<OrgTokenKind>();
                     })
    .def("__eq__",
         [](OrgTokenKind lhs, OrgTokenKind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](OrgTokenKind it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<OrgJsonKind>(m, "OrgJsonKind", type_registry_guard);
  nanobind::enum_<OrgJsonKind>(m, "OrgJsonKind")
    .value("Null", OrgJsonKind::Null)
    .value("Object", OrgJsonKind::Object)
    .value("Array", OrgJsonKind::Array)
    .value("String", OrgJsonKind::String)
    .value("Boolean", OrgJsonKind::Boolean)
    .value("Int", OrgJsonKind::Int)
    .value("Float", OrgJsonKind::Float)
    .def("__iter__", [](OrgJsonKind const& _self) -> org::bind::python::PyEnumIterator<OrgJsonKind> {
                     return org::bind::python::PyEnumIterator<OrgJsonKind>();
                     })
    .def("__eq__",
         [](OrgJsonKind lhs, OrgJsonKind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](OrgJsonKind it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<OrgSemKind>(m, "OrgSemKind", type_registry_guard);
  nanobind::enum_<OrgSemKind>(m, "OrgSemKind")
    .value("NoNode", OrgSemKind::NoNode)
    .value("ErrorItem", OrgSemKind::ErrorItem)
    .value("ErrorGroup", OrgSemKind::ErrorGroup)
    .value("StmtList", OrgSemKind::StmtList)
    .value("Empty", OrgSemKind::Empty)
    .value("CmdCaption", OrgSemKind::CmdCaption)
    .value("CmdCreator", OrgSemKind::CmdCreator)
    .value("CmdAuthor", OrgSemKind::CmdAuthor)
    .value("CmdEmail", OrgSemKind::CmdEmail)
    .value("CmdLanguage", OrgSemKind::CmdLanguage)
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
    .value("ErrorSkipToken", OrgSemKind::ErrorSkipToken)
    .value("ErrorSkipGroup", OrgSemKind::ErrorSkipGroup)
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
    .def("__iter__", [](OrgSemKind const& _self) -> org::bind::python::PyEnumIterator<OrgSemKind> {
                     return org::bind::python::PyEnumIterator<OrgSemKind>();
                     })
    .def("__eq__",
         [](OrgSemKind lhs, OrgSemKind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](OrgSemKind it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org::AstTrackingGroup::Kind>(m, "AstTrackingGroupKind", type_registry_guard);
  nanobind::enum_<org::AstTrackingGroup::Kind>(m, "AstTrackingGroupKind")
    .value("RadioTarget", org::AstTrackingGroup::Kind::RadioTarget)
    .value("Single", org::AstTrackingGroup::Kind::Single)
    .value("TrackedHashtag", org::AstTrackingGroup::Kind::TrackedHashtag)
    .def("__iter__", [](org::AstTrackingGroup::Kind const& _self) -> org::bind::python::PyEnumIterator<org::AstTrackingGroup::Kind> {
                     return org::bind::python::PyEnumIterator<org::AstTrackingGroup::Kind>();
                     })
    .def("__eq__",
         [](org::AstTrackingGroup::Kind lhs, org::AstTrackingGroup::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::AstTrackingGroup::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org::graph::MapLink::Kind>(m, "graphMapLinkKind", type_registry_guard);
  nanobind::enum_<org::graph::MapLink::Kind>(m, "graphMapLinkKind")
    .value("Radio", org::graph::MapLink::Kind::Radio)
    .value("Link", org::graph::MapLink::Kind::Link)
    .def("__iter__", [](org::graph::MapLink::Kind const& _self) -> org::bind::python::PyEnumIterator<org::graph::MapLink::Kind> {
                     return org::bind::python::PyEnumIterator<org::graph::MapLink::Kind>();
                     })
    .def("__eq__",
         [](org::graph::MapLink::Kind lhs, org::graph::MapLink::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::graph::MapLink::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org::bind::python::LeafFieldType>(m, "LeafFieldType", type_registry_guard);
  nanobind::enum_<org::bind::python::LeafFieldType>(m, "LeafFieldType")
    .value("Int", org::bind::python::LeafFieldType::Int)
    .value("UserTimeKind", org::bind::python::LeafFieldType::UserTimeKind)
    .value("QDate", org::bind::python::LeafFieldType::QDate)
    .value("Bool", org::bind::python::LeafFieldType::Bool)
    .value("FixedIdVec", org::bind::python::LeafFieldType::FixedIdVec)
    .value("TopIdVec", org::bind::python::LeafFieldType::TopIdVec)
    .value("QDateTime", org::bind::python::LeafFieldType::QDateTime)
    .value("Str", org::bind::python::LeafFieldType::Str)
    .value("Any", org::bind::python::LeafFieldType::Any)
    .def("__iter__", [](org::bind::python::LeafFieldType const& _self) -> org::bind::python::PyEnumIterator<org::bind::python::LeafFieldType> {
                     return org::bind::python::PyEnumIterator<org::bind::python::LeafFieldType>();
                     })
    .def("__eq__",
         [](org::bind::python::LeafFieldType lhs, org::bind::python::LeafFieldType rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::bind::python::LeafFieldType it) -> int {
         return static_cast<int>(it);
         })
    ;
  m.def("newSemTimeStatic",
        static_cast<org::sem::SemId<org::sem::Time>(*)(hstd::UserTimeBreakdown const&, bool)>(&org::newSemTimeStatic),
        nanobind::arg("breakdown"),
        nanobind::arg("isActive") = 0);
  m.def("initImmutableAstContext", static_cast<std::shared_ptr<org::imm::ImmAstContext>(*)()>(&org::initImmutableAstContext));
  m.def("asOneNode",
        static_cast<org::sem::SemId<org::sem::Org>(*)(org::sem::SemId<org::sem::Org> const&)>(&org::asOneNode),
        nanobind::arg("arg"));
  m.def("formatToString",
        static_cast<std::string(*)(org::sem::SemId<org::sem::Org>)>(&org::formatToString),
        nanobind::arg("arg"));
  m.def("exportToYamlString",
        static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&, org::OrgYamlExportOpts const&)>(&org::exportToYamlString),
        nanobind::arg("node"),
        nanobind::arg("opts"));
  m.def("exportToYamlFile",
        static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string, org::OrgYamlExportOpts const&)>(&org::exportToYamlFile),
        nanobind::arg("node"),
        nanobind::arg("path"),
        nanobind::arg("opts"));
  m.def("exportToJsonString",
        static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&)>(&org::exportToJsonString),
        nanobind::arg("node"));
  m.def("exportToJsonFile",
        static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string)>(&org::exportToJsonFile),
        nanobind::arg("node"),
        nanobind::arg("path"));
  m.def("readProtobufFile",
        static_cast<org::sem::SemId<org::sem::Document>(*)(std::string const&)>(&org::readProtobufFile),
        nanobind::arg("file"));
  m.def("exportToProtobufFile",
        static_cast<void(*)(org::sem::SemId<org::sem::Document>, std::string const&)>(&org::exportToProtobufFile),
        nanobind::arg("doc"),
        nanobind::arg("file"));
  m.def("exportToTreeString",
        static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&, org::OrgTreeExportOpts const&)>(&org::exportToTreeString),
        nanobind::arg("node"),
        nanobind::arg("opts"));
  m.def("exportToTreeFile",
        static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string, org::OrgTreeExportOpts const&)>(&org::exportToTreeFile),
        nanobind::arg("node"),
        nanobind::arg("path"),
        nanobind::arg("opts"));
  m.def("getAstTrackingMap",
        static_cast<org::AstTrackingMap(*)(hstd::Vec<org::sem::SemId<org::sem::Org>> const&)>(&org::getAstTrackingMap),
        nanobind::arg("nodes"));
  m.def("getSubnodeGroups",
        static_cast<hstd::Vec<org::AstTrackingGroup>(*)(org::sem::SemId<org::sem::Org>, org::AstTrackingMap const&)>(&org::getSubnodeGroups),
        nanobind::arg("node"),
        nanobind::arg("map"));
  m.def("annotateSequence",
        static_cast<hstd::Vec<hstd::SequenceAnnotation>(*)(hstd::Vec<hstd::SequenceSegmentGroup> const&, int, int)>(&hstd::annotateSequence),
        nanobind::arg("groups"),
        nanobind::arg("first"),
        nanobind::arg("last"));
  m.def("initMapGraphState",
        static_cast<std::shared_ptr<org::graph::MapGraphState>(*)(std::shared_ptr<org::imm::ImmAstContext>)>(&org::graph::initMapGraphState),
        nanobind::arg("ast"));
  m.def("serializeToText",
        static_cast<std::string(*)(std::shared_ptr<org::imm::ImmAstContext> const&)>(&org::imm::serializeToText),
        nanobind::arg("store"));
  m.def("serializeFromText",
        static_cast<void(*)(std::string const&, std::shared_ptr<org::imm::ImmAstContext> const&)>(&org::imm::serializeFromText),
        nanobind::arg("binary"),
        nanobind::arg("store"));
  m.def("serializeToText",
        static_cast<std::string(*)(std::shared_ptr<org::imm::ImmAstReplaceEpoch> const&)>(&org::imm::serializeToText),
        nanobind::arg("store"));
  m.def("serializeFromText",
        static_cast<void(*)(std::string const&, std::shared_ptr<org::imm::ImmAstReplaceEpoch> const&)>(&org::imm::serializeFromText),
        nanobind::arg("binary"),
        nanobind::arg("store"));
  m.def("serializeToText",
        static_cast<std::string(*)(std::shared_ptr<org::graph::MapGraph> const&)>(&org::imm::serializeToText),
        nanobind::arg("store"));
  m.def("serializeFromText",
        static_cast<void(*)(std::string const&, std::shared_ptr<org::graph::MapGraph> const&)>(&org::imm::serializeFromText),
        nanobind::arg("binary"),
        nanobind::arg("store"));
  m.def("serializeFromTextToTreeDump",
        static_cast<std::string(*)(std::string const&)>(&org::imm::serializeFromTextToTreeDump),
        nanobind::arg("binary"));
  m.def("eachSubnodeRec",
        static_cast<void(*)(org::sem::SemId<org::sem::Org>, nanobind::callable)>(&org::bind::python::eachSubnodeRec),
        nanobind::arg("node"),
        nanobind::arg("callback"));
  m.def("eachSubnodeRecSimplePath",
        static_cast<void(*)(org::sem::SemId<org::sem::Org>, nanobind::callable)>(&org::bind::python::eachSubnodeRecSimplePath),
        nanobind::arg("node"),
        nanobind::arg("callback"));
  m.def("setShouldProcessPath",
        static_cast<void(*)(org::parse::OrgDirectoryParseParameters*, nanobind::callable)>(&org::bind::python::setShouldProcessPath),
        nanobind::arg("parameters"),
        nanobind::arg("callback"));
  m.def("serializeAstContextToText",
        static_cast<nanobind::bytes(*)(std::shared_ptr<org::imm::ImmAstContext> const&)>(&org::bind::python::serializeAstContextToText),
        nanobind::arg("store"));
  m.def("serializeAstContextFromText",
        static_cast<void(*)(nanobind::bytes const&, std::shared_ptr<org::imm::ImmAstContext> const&)>(&org::bind::python::serializeAstContextFromText),
        nanobind::arg("binary"),
        nanobind::arg("store"));
  m.def("serializeAstReplaceEpochToText",
        static_cast<nanobind::bytes(*)(std::shared_ptr<org::imm::ImmAstReplaceEpoch> const&)>(&org::bind::python::serializeAstReplaceEpochToText),
        nanobind::arg("store"));
  m.def("serializeAstReplaceEpochFromText",
        static_cast<void(*)(nanobind::bytes const&, std::shared_ptr<org::imm::ImmAstReplaceEpoch> const&)>(&org::bind::python::serializeAstReplaceEpochFromText),
        nanobind::arg("binary"),
        nanobind::arg("store"));
  m.def("serializeMapGraphFromText",
        static_cast<void(*)(nanobind::bytes const&, std::shared_ptr<org::graph::MapGraph> const&)>(&org::bind::python::serializeMapGraphFromText),
        nanobind::arg("binary"),
        nanobind::arg("store"));
  m.def("serializeMapGraphToText",
        static_cast<nanobind::bytes(*)(std::shared_ptr<org::graph::MapGraph> const&)>(&org::bind::python::serializeMapGraphToText),
        nanobind::arg("store"));
  m.def("setGetParsedNode",
        static_cast<void(*)(org::parse::OrgDirectoryParseParameters*, nanobind::callable)>(&org::bind::python::setGetParsedNode),
        nanobind::arg("params"),
        nanobind::arg("callback"));
  m.def("evaluateCodeBlocks",
        static_cast<org::sem::SemId<org::sem::Org>(*)(org::sem::SemId<org::sem::Org>, org::bind::python::PyCodeEvalParameters const&, std::shared_ptr<org::parse::ParseContext>)>(&org::bind::python::evaluateCodeBlocks),
        nanobind::arg("node"),
        nanobind::arg("conf"),
        nanobind::arg("parse_context"));
}
/* clang-format on */