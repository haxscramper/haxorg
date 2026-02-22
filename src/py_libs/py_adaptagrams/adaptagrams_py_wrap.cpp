/* clang-format off */
#undef slots
#define PYBIND11_DETAILED_ERROR_MESSAGES
#include <adaptagrams/adaptagrams_ir.hpp>
#include <py_libs/pybind11_utils.hpp>
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
NB_MAKE_OPAQUE(std::vector<hstd::ext::GraphPoint>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphPoint>)
NB_MAKE_OPAQUE(std::vector<hstd::ext::GraphNodeConstraint::Align::Spec>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphNodeConstraint::Align::Spec>)
NB_MAKE_OPAQUE(std::vector<hstd::ext::GraphNodeConstraint::Align>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphNodeConstraint::Align>)
NB_MAKE_OPAQUE(std::vector<std::pair<int, int>>)
NB_MAKE_OPAQUE(hstd::Vec<std::pair<int, int>>)
NB_MAKE_OPAQUE(std::vector<int>)
NB_MAKE_OPAQUE(hstd::Vec<int>)
NB_MAKE_OPAQUE(std::vector<vpsc::Rectangle>)
NB_MAKE_OPAQUE(std::vector<hstd::ext::GraphSize>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphSize>)
NB_MAKE_OPAQUE(std::vector<hstd::ext::GraphEdge>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphEdge>)
NB_MAKE_OPAQUE(std::vector<hstd::ext::GraphNodeConstraint>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphNodeConstraint>)
NB_MAKE_OPAQUE(std::vector<hstd::ext::GraphLayoutIR::Subgraph>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphLayoutIR::Subgraph>)
NB_MAKE_OPAQUE(std::unordered_map<hstd::ext::GraphEdge, hstd::ext::GraphSize>)
NB_MAKE_OPAQUE(hstd::UnorderedMap<hstd::ext::GraphEdge, hstd::ext::GraphSize>)
NB_MAKE_OPAQUE(std::unordered_map<hstd::ext::GraphEdge, hstd::ext::GraphEdgeConstraint>)
NB_MAKE_OPAQUE(hstd::UnorderedMap<hstd::ext::GraphEdge, hstd::ext::GraphEdgeConstraint>)
NB_MAKE_OPAQUE(std::vector<hstd::ext::GraphPath>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphPath>)
NB_MAKE_OPAQUE(std::vector<hstd::ext::GraphRect>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphRect>)
NB_MAKE_OPAQUE(std::unordered_map<hstd::ext::GraphEdge, hstd::ext::GraphLayoutIR::Edge>)
NB_MAKE_OPAQUE(hstd::UnorderedMap<hstd::ext::GraphEdge, hstd::ext::GraphLayoutIR::Edge>)
NB_MAKE_OPAQUE(std::vector<hstd::ext::GraphLayoutIR::Result::Subgraph>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphLayoutIR::Result::Subgraph>)
NB_MAKE_OPAQUE(std::vector<hstd::Vec<int>>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::Vec<int>>)
NB_MODULE(py_adaptagrams, m) {
  org::bind::python::PyTypeRegistryGuard type_registry_guard{};
  bind_hstdVec<hstd::ext::GraphPoint>(m, "VecOfGraphPoint", type_registry_guard);
  bind_hstdVec<hstd::ext::GraphNodeConstraint::Align::Spec>(m, "VecOfGraphNodeConstraintAlignSpec", type_registry_guard);
  bind_hstdVec<hstd::ext::GraphNodeConstraint::Align>(m, "VecOfGraphNodeConstraintAlign", type_registry_guard);
  bind_hstdVec<std::pair<int, int>>(m, "VecOfStdPairOfIntInt", type_registry_guard);
  bind_hstdVec<int>(m, "VecOfInt", type_registry_guard);
  bind_stdvector<vpsc::Rectangle>(m, "StdVectorOfVpscRectangle", type_registry_guard);
  bind_hstdVec<hstd::ext::GraphSize>(m, "VecOfGraphSize", type_registry_guard);
  bind_hstdVec<hstd::ext::GraphEdge>(m, "VecOfGraphEdge", type_registry_guard);
  bind_hstdVec<hstd::ext::GraphNodeConstraint>(m, "VecOfGraphNodeConstraint", type_registry_guard);
  bind_hstdVec<hstd::ext::GraphLayoutIR::Subgraph>(m, "VecOfGraphLayoutIRSubgraph", type_registry_guard);
  bind_hstdUnorderedMap<hstd::ext::GraphEdge, hstd::ext::GraphSize>(m, "UnorderedMapOfGraphEdgeGraphSize", type_registry_guard);
  bind_hstdUnorderedMap<hstd::ext::GraphEdge, hstd::ext::GraphEdgeConstraint>(m, "UnorderedMapOfGraphEdgeGraphEdgeConstraint", type_registry_guard);
  bind_hstdVec<hstd::ext::GraphPath>(m, "VecOfGraphPath", type_registry_guard);
  bind_hstdVec<hstd::ext::GraphRect>(m, "VecOfGraphRect", type_registry_guard);
  bind_hstdUnorderedMap<hstd::ext::GraphEdge, hstd::ext::GraphLayoutIR::Edge>(m, "UnorderedMapOfGraphEdgeGraphLayoutIREdge", type_registry_guard);
  bind_hstdVec<hstd::ext::GraphLayoutIR::Result::Subgraph>(m, "VecOfGraphLayoutIRResultSubgraph", type_registry_guard);
  bind_hstdVec<hstd::Vec<int>>(m, "VecOfVecOfInt", type_registry_guard);
  bind_enum_iterator<hstd::ext::GraphDimension>(m, "GraphDimension", type_registry_guard);
  nanobind::enum_<hstd::ext::GraphDimension>(m, "GraphDimension")
    .value("XDIM", hstd::ext::GraphDimension::XDIM)
    .value("YDIM", hstd::ext::GraphDimension::YDIM)
    .value("UNSET", hstd::ext::GraphDimension::UNSET)
    .def("__iter__", [](hstd::ext::GraphDimension const& _self) -> org::bind::python::PyEnumIterator<hstd::ext::GraphDimension> {
                     return org::bind::python::PyEnumIterator<hstd::ext::GraphDimension>();
                     })
    .def("__int__", [](hstd::ext::GraphDimension const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](hstd::ext::GraphDimension const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](hstd::ext::GraphDimension lhs, hstd::ext::GraphDimension rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](hstd::ext::GraphDimension it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<hstd::ext::GraphNodeConstraint::Kind>(m, "GraphNodeConstraintKind", type_registry_guard);
  nanobind::enum_<hstd::ext::GraphNodeConstraint::Kind>(m, "GraphNodeConstraintKind")
    .value("Empty", hstd::ext::GraphNodeConstraint::Kind::Empty)
    .value("Align", hstd::ext::GraphNodeConstraint::Kind::Align)
    .value("FixedRelative", hstd::ext::GraphNodeConstraint::Kind::FixedRelative)
    .value("Separate", hstd::ext::GraphNodeConstraint::Kind::Separate)
    .value("MultiSeparate", hstd::ext::GraphNodeConstraint::Kind::MultiSeparate)
    .value("PageBoundary", hstd::ext::GraphNodeConstraint::Kind::PageBoundary)
    .def("__iter__", [](hstd::ext::GraphNodeConstraint::Kind const& _self) -> org::bind::python::PyEnumIterator<hstd::ext::GraphNodeConstraint::Kind> {
                     return org::bind::python::PyEnumIterator<hstd::ext::GraphNodeConstraint::Kind>();
                     })
    .def("__int__", [](hstd::ext::GraphNodeConstraint::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](hstd::ext::GraphNodeConstraint::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](hstd::ext::GraphNodeConstraint::Kind lhs, hstd::ext::GraphNodeConstraint::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](hstd::ext::GraphNodeConstraint::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<hstd::ext::GraphEdgeConstraint::Port>(m, "GraphEdgeConstraintPort", type_registry_guard);
  nanobind::enum_<hstd::ext::GraphEdgeConstraint::Port>(m, "GraphEdgeConstraintPort")
    .value("Default", hstd::ext::GraphEdgeConstraint::Port::Default)
    .value("North", hstd::ext::GraphEdgeConstraint::Port::North)
    .value("South", hstd::ext::GraphEdgeConstraint::Port::South)
    .value("West", hstd::ext::GraphEdgeConstraint::Port::West)
    .value("East", hstd::ext::GraphEdgeConstraint::Port::East)
    .value("Center", hstd::ext::GraphEdgeConstraint::Port::Center)
    .def("__iter__", [](hstd::ext::GraphEdgeConstraint::Port const& _self) -> org::bind::python::PyEnumIterator<hstd::ext::GraphEdgeConstraint::Port> {
                     return org::bind::python::PyEnumIterator<hstd::ext::GraphEdgeConstraint::Port>();
                     })
    .def("__int__", [](hstd::ext::GraphEdgeConstraint::Port const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](hstd::ext::GraphEdgeConstraint::Port const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](hstd::ext::GraphEdgeConstraint::Port lhs, hstd::ext::GraphEdgeConstraint::Port rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](hstd::ext::GraphEdgeConstraint::Port it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<hstd::ext::GraphPoint>(m, "GraphPoint")
    .def("__init__",
         [](hstd::ext::GraphPoint* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphPoint();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("x", &hstd::ext::GraphPoint::x)
    .def_rw("y", &hstd::ext::GraphPoint::y)
    .def("__repr__", [](hstd::ext::GraphPoint const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphPoint const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphPath>(m, "GraphPath")
    .def("__init__",
         [](hstd::ext::GraphPath* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphPath();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("points", &hstd::ext::GraphPath::points)
    .def_rw("startPoint", &hstd::ext::GraphPath::startPoint)
    .def_rw("endPoint", &hstd::ext::GraphPath::endPoint)
    .def_rw("bezier", &hstd::ext::GraphPath::bezier)
    .def("point",
         static_cast<void(hstd::ext::GraphPath::*)(double, double)>(&hstd::ext::GraphPath::point),
         nanobind::arg("x"),
         nanobind::arg("y"))
    .def("point",
         static_cast<void(hstd::ext::GraphPath::*)(hstd::ext::GraphPoint const&)>(&hstd::ext::GraphPath::point),
         nanobind::arg("p"))
    .def("__repr__", [](hstd::ext::GraphPath const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphPath const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphSize>(m, "GraphSize")
    .def("__init__",
         [](hstd::ext::GraphSize* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphSize();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("w", &hstd::ext::GraphSize::w)
    .def_rw("h", &hstd::ext::GraphSize::h)
    .def("height", static_cast<double(hstd::ext::GraphSize::*)() const>(&hstd::ext::GraphSize::height))
    .def("width", static_cast<double(hstd::ext::GraphSize::*)() const>(&hstd::ext::GraphSize::width))
    .def("__repr__", [](hstd::ext::GraphSize const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphSize const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphRect>(m, "GraphRect")
    .def("__init__",
         [](hstd::ext::GraphRect* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphRect();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("left", &hstd::ext::GraphRect::left)
    .def_rw("top", &hstd::ext::GraphRect::top)
    .def_rw("width", &hstd::ext::GraphRect::width)
    .def_rw("height", &hstd::ext::GraphRect::height)
    .def("size", static_cast<hstd::ext::GraphSize(hstd::ext::GraphRect::*)() const>(&hstd::ext::GraphRect::size))
    .def("__repr__", [](hstd::ext::GraphRect const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphRect const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphNodeConstraint::Empty>(m, "GraphNodeConstraintEmpty")
    .def("__init__",
         [](hstd::ext::GraphNodeConstraint::Empty* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphNodeConstraint::Empty();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](hstd::ext::GraphNodeConstraint::Empty const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphNodeConstraint::Empty const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphNodeConstraint::Align::Spec>(m, "GraphNodeConstraintAlignSpec")
    .def("__init__",
         [](hstd::ext::GraphNodeConstraint::Align::Spec* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphNodeConstraint::Align::Spec();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("node", &hstd::ext::GraphNodeConstraint::Align::Spec::node, R"RAW(Rectangle index)RAW")
    .def_rw("fixPos", &hstd::ext::GraphNodeConstraint::Align::Spec::fixPos, R"RAW(??? wtf)RAW")
    .def_rw("offset", &hstd::ext::GraphNodeConstraint::Align::Spec::offset, R"RAW(Offset from the axis)RAW")
    .def("__repr__", [](hstd::ext::GraphNodeConstraint::Align::Spec const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphNodeConstraint::Align::Spec const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphNodeConstraint::Align>(m, "GraphNodeConstraintAlign")
    .def("__init__",
         [](hstd::ext::GraphNodeConstraint::Align* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphNodeConstraint::Align();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("nodes", &hstd::ext::GraphNodeConstraint::Align::nodes)
    .def_rw("dimension", &hstd::ext::GraphNodeConstraint::Align::dimension, R"RAW(Which axist to align on)RAW")
    .def("toColaString", static_cast<std::string(hstd::ext::GraphNodeConstraint::Align::*)() const>(&hstd::ext::GraphNodeConstraint::Align::toColaString))
    .def("__repr__", [](hstd::ext::GraphNodeConstraint::Align const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphNodeConstraint::Align const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphNodeConstraint::Separate>(m, "GraphNodeConstraintSeparate")
    .def("__init__",
         [](hstd::ext::GraphNodeConstraint::Separate* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphNodeConstraint::Separate();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("left", &hstd::ext::GraphNodeConstraint::Separate::left)
    .def_rw("right", &hstd::ext::GraphNodeConstraint::Separate::right)
    .def_rw("separationDistance", &hstd::ext::GraphNodeConstraint::Separate::separationDistance)
    .def_rw("isExactSeparation", &hstd::ext::GraphNodeConstraint::Separate::isExactSeparation)
    .def_rw("dimension", &hstd::ext::GraphNodeConstraint::Separate::dimension, R"RAW(Which axis to partition
nodes)RAW")
    .def("toColaString", static_cast<std::string(hstd::ext::GraphNodeConstraint::Separate::*)() const>(&hstd::ext::GraphNodeConstraint::Separate::toColaString))
    .def("__repr__", [](hstd::ext::GraphNodeConstraint::Separate const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphNodeConstraint::Separate const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphNodeConstraint::MultiSeparate>(m, "GraphNodeConstraintMultiSeparate")
    .def("__init__",
         [](hstd::ext::GraphNodeConstraint::MultiSeparate* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphNodeConstraint::MultiSeparate();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("lines", &hstd::ext::GraphNodeConstraint::MultiSeparate::lines)
    .def_rw("alignPairs", &hstd::ext::GraphNodeConstraint::MultiSeparate::alignPairs)
    .def_rw("dimension", &hstd::ext::GraphNodeConstraint::MultiSeparate::dimension)
    .def_rw("separationDistance", &hstd::ext::GraphNodeConstraint::MultiSeparate::separationDistance)
    .def_rw("isExactSeparation", &hstd::ext::GraphNodeConstraint::MultiSeparate::isExactSeparation)
    .def("toColaString", static_cast<std::string(hstd::ext::GraphNodeConstraint::MultiSeparate::*)() const>(&hstd::ext::GraphNodeConstraint::MultiSeparate::toColaString))
    .def("__repr__", [](hstd::ext::GraphNodeConstraint::MultiSeparate const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphNodeConstraint::MultiSeparate const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphNodeConstraint::FixedRelative>(m, "GraphNodeConstraintFixedRelative")
    .def("__init__",
         [](hstd::ext::GraphNodeConstraint::FixedRelative* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphNodeConstraint::FixedRelative();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("nodes", &hstd::ext::GraphNodeConstraint::FixedRelative::nodes)
    .def_rw("fixedPosition", &hstd::ext::GraphNodeConstraint::FixedRelative::fixedPosition)
    .def("__repr__", [](hstd::ext::GraphNodeConstraint::FixedRelative const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphNodeConstraint::FixedRelative const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphNodeConstraint::PageBoundary>(m, "GraphNodeConstraintPageBoundary")
    .def("__init__",
         [](hstd::ext::GraphNodeConstraint::PageBoundary* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphNodeConstraint::PageBoundary();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("rect", &hstd::ext::GraphNodeConstraint::PageBoundary::rect)
    .def_rw("weight", &hstd::ext::GraphNodeConstraint::PageBoundary::weight)
    .def_rw("nodes", &hstd::ext::GraphNodeConstraint::PageBoundary::nodes)
    .def("toColaString",
         static_cast<std::string(hstd::ext::GraphNodeConstraint::PageBoundary::*)(std::vector<vpsc::Rectangle*> const&) const>(&hstd::ext::GraphNodeConstraint::PageBoundary::toColaString),
         nanobind::arg("allRects"))
    .def("__repr__", [](hstd::ext::GraphNodeConstraint::PageBoundary const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphNodeConstraint::PageBoundary const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphNodeConstraint>(m, "GraphNodeConstraint")
    .def("__init__",
         [](hstd::ext::GraphNodeConstraint* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphNodeConstraint();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getEmpty", static_cast<hstd::ext::GraphNodeConstraint::Empty&(hstd::ext::GraphNodeConstraint::*)()>(&hstd::ext::GraphNodeConstraint::getEmpty))
    .def("isEmpty", static_cast<bool(hstd::ext::GraphNodeConstraint::*)() const>(&hstd::ext::GraphNodeConstraint::isEmpty))
    .def("getAlign", static_cast<hstd::ext::GraphNodeConstraint::Align&(hstd::ext::GraphNodeConstraint::*)()>(&hstd::ext::GraphNodeConstraint::getAlign))
    .def("isAlign", static_cast<bool(hstd::ext::GraphNodeConstraint::*)() const>(&hstd::ext::GraphNodeConstraint::isAlign))
    .def("getFixedRelative", static_cast<hstd::ext::GraphNodeConstraint::FixedRelative&(hstd::ext::GraphNodeConstraint::*)()>(&hstd::ext::GraphNodeConstraint::getFixedRelative))
    .def("isFixedRelative", static_cast<bool(hstd::ext::GraphNodeConstraint::*)() const>(&hstd::ext::GraphNodeConstraint::isFixedRelative))
    .def("getSeparate", static_cast<hstd::ext::GraphNodeConstraint::Separate&(hstd::ext::GraphNodeConstraint::*)()>(&hstd::ext::GraphNodeConstraint::getSeparate))
    .def("isSeparate", static_cast<bool(hstd::ext::GraphNodeConstraint::*)() const>(&hstd::ext::GraphNodeConstraint::isSeparate))
    .def("getMultiSeparate", static_cast<hstd::ext::GraphNodeConstraint::MultiSeparate&(hstd::ext::GraphNodeConstraint::*)()>(&hstd::ext::GraphNodeConstraint::getMultiSeparate))
    .def("isMultiSeparate", static_cast<bool(hstd::ext::GraphNodeConstraint::*)() const>(&hstd::ext::GraphNodeConstraint::isMultiSeparate))
    .def("getPageBoundary", static_cast<hstd::ext::GraphNodeConstraint::PageBoundary&(hstd::ext::GraphNodeConstraint::*)()>(&hstd::ext::GraphNodeConstraint::getPageBoundary))
    .def("isPageBoundary", static_cast<bool(hstd::ext::GraphNodeConstraint::*)() const>(&hstd::ext::GraphNodeConstraint::isPageBoundary))
    .def("getKind", static_cast<hstd::ext::GraphNodeConstraint::Kind(hstd::ext::GraphNodeConstraint::*)() const>(&hstd::ext::GraphNodeConstraint::getKind))
    .def_static("InitEmptyStatic",
                static_cast<hstd::ext::GraphNodeConstraint(*)(hstd::ext::GraphNodeConstraint::Empty const&)>(&hstd::ext::GraphNodeConstraint::InitEmpty),
                nanobind::arg("arg"))
    .def_static("InitAlignStatic",
                static_cast<hstd::ext::GraphNodeConstraint(*)(hstd::ext::GraphNodeConstraint::Align const&)>(&hstd::ext::GraphNodeConstraint::InitAlign),
                nanobind::arg("arg"))
    .def_static("InitSeparateStatic",
                static_cast<hstd::ext::GraphNodeConstraint(*)(hstd::ext::GraphNodeConstraint::Separate const&)>(&hstd::ext::GraphNodeConstraint::InitSeparate),
                nanobind::arg("arg"))
    .def_static("InitMultiSeparateStatic",
                static_cast<hstd::ext::GraphNodeConstraint(*)(hstd::ext::GraphNodeConstraint::MultiSeparate const&)>(&hstd::ext::GraphNodeConstraint::InitMultiSeparate),
                nanobind::arg("arg"))
    .def_static("InitFixedRelativeStatic",
                static_cast<hstd::ext::GraphNodeConstraint(*)(hstd::ext::GraphNodeConstraint::FixedRelative const&)>(&hstd::ext::GraphNodeConstraint::InitFixedRelative),
                nanobind::arg("arg"))
    .def_static("InitPageBoundaryStatic",
                static_cast<hstd::ext::GraphNodeConstraint(*)(hstd::ext::GraphNodeConstraint::PageBoundary const&)>(&hstd::ext::GraphNodeConstraint::InitPageBoundary),
                nanobind::arg("arg"))
    .def("__repr__", [](hstd::ext::GraphNodeConstraint const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphNodeConstraint const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphEdge>(m, "GraphEdge")
    .def("__init__",
         [](hstd::ext::GraphEdge* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphEdge();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("source", &hstd::ext::GraphEdge::source)
    .def_rw("target", &hstd::ext::GraphEdge::target)
    .def_rw("bundle", &hstd::ext::GraphEdge::bundle)
    .def("__repr__", [](hstd::ext::GraphEdge const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphEdge const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphEdgeConstraint>(m, "GraphEdgeConstraint")
    .def("__init__",
         [](hstd::ext::GraphEdgeConstraint* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphEdgeConstraint();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("sourcePort", &hstd::ext::GraphEdgeConstraint::sourcePort)
    .def_rw("targetPort", &hstd::ext::GraphEdgeConstraint::targetPort)
    .def_rw("sourceOffset", &hstd::ext::GraphEdgeConstraint::sourceOffset, R"RAW(\brief Offset the port position on the side of the shape. Value in
range [0, 1] used as a relative position along the edge of the
shape. For vertical edges (west/east) the port movement would be
vertical, and for horizontal (north/south) it would be horizontal.
If the value is not provided the nodes are placed in the center
with the ratio computed automatically.)RAW")
    .def_rw("targetOffset", &hstd::ext::GraphEdgeConstraint::targetOffset)
    .def_rw("sourceCheckpoint", &hstd::ext::GraphEdgeConstraint::sourceCheckpoint)
    .def_rw("targetCheckpoint", &hstd::ext::GraphEdgeConstraint::targetCheckpoint)
    .def("__repr__", [](hstd::ext::GraphEdgeConstraint const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphEdgeConstraint const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphLayoutIR::Subgraph>(m, "GraphLayoutIRSubgraph")
    .def("__init__",
         [](hstd::ext::GraphLayoutIR::Subgraph* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphLayoutIR::Subgraph();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](hstd::ext::GraphLayoutIR::Subgraph const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphLayoutIR::Subgraph const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphLayoutIR::Edge>(m, "GraphLayoutIREdge")
    .def("__init__",
         [](hstd::ext::GraphLayoutIR::Edge* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphLayoutIR::Edge();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("paths", &hstd::ext::GraphLayoutIR::Edge::paths, R"RAW(\brief Sequence of painter paths going from source to target
node. If the node has a label rectangle specified, the paths
are placed in a way to accomodate for the rectangle.)RAW")
    .def_rw("labelRect", &hstd::ext::GraphLayoutIR::Edge::labelRect, R"RAW(\brief Edge label rectangle)RAW")
    .def("__repr__", [](hstd::ext::GraphLayoutIR::Edge const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphLayoutIR::Edge const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphLayoutIR::Result::Subgraph>(m, "GraphLayoutIRResultSubgraph")
    .def("__init__",
         [](hstd::ext::GraphLayoutIR::Result::Subgraph* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphLayoutIR::Result::Subgraph();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("bbox", &hstd::ext::GraphLayoutIR::Result::Subgraph::bbox, R"RAW(\brief Bounding box for the rectangle content)RAW")
    .def_rw("subgraphs", &hstd::ext::GraphLayoutIR::Result::Subgraph::subgraphs)
    .def("__repr__", [](hstd::ext::GraphLayoutIR::Result::Subgraph const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphLayoutIR::Result::Subgraph const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphLayoutIR::Result>(m, "GraphLayoutIRResult")
    .def("__init__",
         [](hstd::ext::GraphLayoutIR::Result* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphLayoutIR::Result();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("fixed", &hstd::ext::GraphLayoutIR::Result::fixed, R"RAW(\brief Fixed node layout rectangles with absolute coordinates.
Subgraph nodes are also included. Edge label nodes are not
included.)RAW")
    .def_rw("lines", &hstd::ext::GraphLayoutIR::Result::lines, R"RAW(\brief Mapping from the source-target edge pair to the edge
layout spec)RAW")
    .def_rw("bbox", &hstd::ext::GraphLayoutIR::Result::bbox, R"RAW(\brief Bounding box for the whole rectangle)RAW")
    .def_rw("subgraphs", &hstd::ext::GraphLayoutIR::Result::subgraphs, R"RAW(\brief Top-level list of subgraphs)RAW")
    .def_rw("subgraphPaths", &hstd::ext::GraphLayoutIR::Result::subgraphPaths, R"RAW(\brief Flattened list of subgraphs in DFS order with paths)RAW")
    .def("__repr__", [](hstd::ext::GraphLayoutIR::Result const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphLayoutIR::Result const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd::ext::GraphLayoutIR>(m, "GraphLayoutIR")
    .def("__init__",
         [](hstd::ext::GraphLayoutIR* result, nanobind::kwargs const& kwargs) {
         new(result) hstd::ext::GraphLayoutIR();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("rectangles", &hstd::ext::GraphLayoutIR::rectangles, R"RAW(\brief Nodes for the graph. Node is identified by the index in the
array of sizes. In the result value each original qsize is mapped
to the rectangle.)RAW")
    .def_rw("edges", &hstd::ext::GraphLayoutIR::edges, R"RAW(\brief List of source-target pairs. Edge source/target IDs refer to
the size rectangles.)RAW")
    .def_rw("nodeConstraints", &hstd::ext::GraphLayoutIR::nodeConstraints, R"RAW(\brief Cola nodeConstraints for graph layout. This part is
backend-specific.)RAW")
    .def_rw("subgraphs", &hstd::ext::GraphLayoutIR::subgraphs)
    .def_rw("edgeLabels", &hstd::ext::GraphLayoutIR::edgeLabels, R"RAW(\brief If some edge has a dedicated label of specified size.)RAW")
    .def_rw("edgeConstraints", &hstd::ext::GraphLayoutIR::edgeConstraints)
    .def_rw("width", &hstd::ext::GraphLayoutIR::width)
    .def_rw("height", &hstd::ext::GraphLayoutIR::height)
    .def_rw("leftBBoxMargin", &hstd::ext::GraphLayoutIR::leftBBoxMargin)
    .def_rw("rightBBoxMargin", &hstd::ext::GraphLayoutIR::rightBBoxMargin)
    .def_rw("topBBoxMargin", &hstd::ext::GraphLayoutIR::topBBoxMargin)
    .def_rw("bottomBBoxMargin", &hstd::ext::GraphLayoutIR::bottomBBoxMargin)
    .def_rw("graphName", &hstd::ext::GraphLayoutIR::graphName, R"RAW(\brief Graph name. Backend-specific.)RAW")
    .def_rw("graphviz_size_scaling", &hstd::ext::GraphLayoutIR::graphviz_size_scaling, R"RAW(\brief Which DPI to use when converting to and from graphviz sizes.
Backend-specific, 72 is the default used by graphviz.)RAW")
    .def("validate", static_cast<void(hstd::ext::GraphLayoutIR::*)()>(&hstd::ext::GraphLayoutIR::validate), R"RAW(\brief validate the edge/rectangle structure for debugging. Throws
assert failure if the structure is incorrect.)RAW")
    .def("doGraphvizConvert", static_cast<hstd::ext::GraphLayoutIR::Result(hstd::ext::GraphLayoutIR::*)()>(&hstd::ext::GraphLayoutIR::doGraphvizConvert))
    .def("doHolaConvert", static_cast<hstd::ext::GraphLayoutIR::Result(hstd::ext::GraphLayoutIR::*)()>(&hstd::ext::GraphLayoutIR::doHolaConvert))
    .def("doColaConvert", static_cast<hstd::ext::GraphLayoutIR::Result(hstd::ext::GraphLayoutIR::*)()>(&hstd::ext::GraphLayoutIR::doColaConvert))
    .def("doColaSvgWrite",
         static_cast<void(hstd::ext::GraphLayoutIR::*)(std::string const&)>(&hstd::ext::GraphLayoutIR::doColaSvgWrite),
         nanobind::arg("path"))
    .def("doColaStrFormat", static_cast<std::string(hstd::ext::GraphLayoutIR::*)()>(&hstd::ext::GraphLayoutIR::doColaStrFormat))
    .def("__repr__", [](hstd::ext::GraphLayoutIR const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphLayoutIR const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::set_leak_warnings(false);
}
/* clang-format on */