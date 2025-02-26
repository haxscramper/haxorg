/* clang-format off */
#undef slots
#define PYBIND11_DETAILED_ERROR_MESSAGES
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>
#include <py_libs/pybind11_utils.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
PYBIND11_MAKE_OPAQUE(std::vector<hstd::ext::GraphPoint>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphPoint>)
/* (('hstd', False, 0, NotRef), ('hstd', False, 0, NotRef), ('ext', False, 0, NotRef), ('GraphPoint', False, 0, NotRef), ('Vec', False, 0, NotRef)) */
PYBIND11_MAKE_OPAQUE(std::vector<hstd::ext::GraphNodeConstraint::Align::Spec>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphNodeConstraint::Align::Spec>)
/* (('hstd', False, 0, NotRef), ('hstd', False, 0, NotRef), ('ext', False, 0, NotRef), ('GraphNodeConstraint', False, 0, NotRef), ('Align', False, 0, NotRef), ('Spec', False, 0, NotRef), ('Vec', False, 0, NotRef)) */
PYBIND11_MAKE_OPAQUE(std::vector<hstd::ext::GraphNodeConstraint::Align>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphNodeConstraint::Align>)
/* (('hstd', False, 0, NotRef), ('hstd', False, 0, NotRef), ('ext', False, 0, NotRef), ('GraphNodeConstraint', False, 0, NotRef), ('Align', False, 0, NotRef), ('Vec', False, 0, NotRef)) */
PYBIND11_MAKE_OPAQUE(std::vector<std::pair<int, int>>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<std::pair<int, int>>)
/* (('hstd', False, 0, NotRef), ('std', False, 0, NotRef), ('int', False, 0, NotRef), ('int', False, 0, NotRef), ('pair', False, 0, NotRef), ('Vec', False, 0, NotRef)) */
PYBIND11_MAKE_OPAQUE(std::vector<int>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<int>)
/* (('hstd', False, 0, NotRef), ('int', False, 0, NotRef), ('Vec', False, 0, NotRef)) */
PYBIND11_MAKE_OPAQUE(std::vector<hstd::ext::GraphSize>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphSize>)
/* (('hstd', False, 0, NotRef), ('hstd', False, 0, NotRef), ('ext', False, 0, NotRef), ('GraphSize', False, 0, NotRef), ('Vec', False, 0, NotRef)) */
PYBIND11_MAKE_OPAQUE(std::vector<hstd::ext::GraphEdge>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphEdge>)
/* (('hstd', False, 0, NotRef), ('hstd', False, 0, NotRef), ('ext', False, 0, NotRef), ('GraphEdge', False, 0, NotRef), ('Vec', False, 0, NotRef)) */
PYBIND11_MAKE_OPAQUE(std::vector<hstd::ext::GraphNodeConstraint>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphNodeConstraint>)
/* (('hstd', False, 0, NotRef), ('hstd', False, 0, NotRef), ('ext', False, 0, NotRef), ('GraphNodeConstraint', False, 0, NotRef), ('Vec', False, 0, NotRef)) */
PYBIND11_MAKE_OPAQUE(std::vector<hstd::ext::GraphLayoutIR::Subgraph>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphLayoutIR::Subgraph>)
/* (('hstd', False, 0, NotRef), ('hstd', False, 0, NotRef), ('ext', False, 0, NotRef), ('GraphLayoutIR', False, 0, NotRef), ('Subgraph', False, 0, NotRef), ('Vec', False, 0, NotRef)) */
PYBIND11_MAKE_OPAQUE(std::unordered_map<hstd::ext::GraphEdge, hstd::ext::GraphSize>)
PYBIND11_MAKE_OPAQUE(hstd::UnorderedMap<hstd::ext::GraphEdge, hstd::ext::GraphSize>)
/* (('hstd', False, 0, NotRef), ('hstd', False, 0, NotRef), ('ext', False, 0, NotRef), ('GraphEdge', False, 0, NotRef), ('hstd', False, 0, NotRef), ('ext', False, 0, NotRef), ('GraphSize', False, 0, NotRef), ('UnorderedMap', False, 0, NotRef)) */
PYBIND11_MAKE_OPAQUE(std::unordered_map<hstd::ext::GraphEdge, hstd::ext::GraphEdgeConstraint>)
PYBIND11_MAKE_OPAQUE(hstd::UnorderedMap<hstd::ext::GraphEdge, hstd::ext::GraphEdgeConstraint>)
/* (('hstd', False, 0, NotRef), ('hstd', False, 0, NotRef), ('ext', False, 0, NotRef), ('GraphEdge', False, 0, NotRef), ('hstd', False, 0, NotRef), ('ext', False, 0, NotRef), ('GraphEdgeConstraint', False, 0, NotRef), ('UnorderedMap', False, 0, NotRef)) */
PYBIND11_MAKE_OPAQUE(std::vector<hstd::ext::GraphPath>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphPath>)
/* (('hstd', False, 0, NotRef), ('hstd', False, 0, NotRef), ('ext', False, 0, NotRef), ('GraphPath', False, 0, NotRef), ('Vec', False, 0, NotRef)) */
PYBIND11_MAKE_OPAQUE(std::vector<hstd::ext::GraphRect>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphRect>)
/* (('hstd', False, 0, NotRef), ('hstd', False, 0, NotRef), ('ext', False, 0, NotRef), ('GraphRect', False, 0, NotRef), ('Vec', False, 0, NotRef)) */
PYBIND11_MAKE_OPAQUE(std::unordered_map<hstd::ext::GraphEdge, hstd::ext::GraphLayoutIR::Edge>)
PYBIND11_MAKE_OPAQUE(hstd::UnorderedMap<hstd::ext::GraphEdge, hstd::ext::GraphLayoutIR::Edge>)
/* (('hstd', False, 0, NotRef), ('hstd', False, 0, NotRef), ('ext', False, 0, NotRef), ('GraphEdge', False, 0, NotRef), ('hstd', False, 0, NotRef), ('ext', False, 0, NotRef), ('GraphLayoutIR', False, 0, NotRef), ('Edge', False, 0, NotRef), ('UnorderedMap', False, 0, NotRef)) */
PYBIND11_MAKE_OPAQUE(std::vector<hstd::ext::GraphLayoutIR::Result::Subgraph>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::ext::GraphLayoutIR::Result::Subgraph>)
/* (('hstd', False, 0, NotRef), ('hstd', False, 0, NotRef), ('ext', False, 0, NotRef), ('GraphLayoutIR', False, 0, NotRef), ('Result', False, 0, NotRef), ('Subgraph', False, 0, NotRef), ('Vec', False, 0, NotRef)) */
PYBIND11_MAKE_OPAQUE(std::vector<hstd::Vec<int>>)
PYBIND11_MAKE_OPAQUE(hstd::Vec<hstd::Vec<int>>)
/* (('hstd', False, 0, NotRef), ('hstd', False, 0, NotRef), ('int', False, 0, NotRef), ('Vec', False, 0, NotRef), ('Vec', False, 0, NotRef)) */
PYBIND11_MODULE(py_adaptagrams, m) {
  org::bind::python::PyTypeRegistryGuard type_registry_guard{};
  bind_vector<hstd::ext::GraphPoint>(m, "hstdVecOfhstdextGraphPoint", type_registry_guard);
  bind_vector<hstd::ext::GraphNodeConstraint::Align::Spec>(m, "hstdVecOfhstdextGraphNodeConstraintAlignSpec", type_registry_guard);
  bind_vector<hstd::ext::GraphNodeConstraint::Align>(m, "hstdVecOfhstdextGraphNodeConstraintAlign", type_registry_guard);
  bind_vector<std::pair<int, int>>(m, "hstdVecOfstdpairOfintint", type_registry_guard);
  bind_vector<int>(m, "hstdVecOfint", type_registry_guard);
  bind_vector<hstd::ext::GraphSize>(m, "hstdVecOfhstdextGraphSize", type_registry_guard);
  bind_vector<hstd::ext::GraphEdge>(m, "hstdVecOfhstdextGraphEdge", type_registry_guard);
  bind_vector<hstd::ext::GraphNodeConstraint>(m, "hstdVecOfhstdextGraphNodeConstraint", type_registry_guard);
  bind_vector<hstd::ext::GraphLayoutIR::Subgraph>(m, "hstdVecOfhstdextGraphLayoutIRSubgraph", type_registry_guard);
  bind_unordered_map<hstd::ext::GraphEdge, hstd::ext::GraphSize>(m, "hstdUnorderedMapOfhstdextGraphEdgehstdextGraphSize", type_registry_guard);
  bind_unordered_map<hstd::ext::GraphEdge, hstd::ext::GraphEdgeConstraint>(m, "hstdUnorderedMapOfhstdextGraphEdgehstdextGraphEdgeConstraint", type_registry_guard);
  bind_vector<hstd::ext::GraphPath>(m, "hstdVecOfhstdextGraphPath", type_registry_guard);
  bind_vector<hstd::ext::GraphRect>(m, "hstdVecOfhstdextGraphRect", type_registry_guard);
  bind_unordered_map<hstd::ext::GraphEdge, hstd::ext::GraphLayoutIR::Edge>(m, "hstdUnorderedMapOfhstdextGraphEdgehstdextGraphLayoutIREdge", type_registry_guard);
  bind_vector<hstd::ext::GraphLayoutIR::Result::Subgraph>(m, "hstdVecOfhstdextGraphLayoutIRResultSubgraph", type_registry_guard);
  bind_vector<hstd::Vec<int>>(m, "hstdVecOfhstdVecOfint", type_registry_guard);
  pybind11::class_<hstd::ext::GraphPoint>(m, "hstdextGraphPoint")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphPoint {
                        hstd::ext::GraphPoint result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("x", &hstd::ext::GraphPoint::x)
    .def_readwrite("y", &hstd::ext::GraphPoint::y)
    .def("__repr__", [](hstd::ext::GraphPoint _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphPoint _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphPath>(m, "hstdextGraphPath")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphPath {
                        hstd::ext::GraphPath result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("points", &hstd::ext::GraphPath::points)
    .def_readwrite("startPoint", &hstd::ext::GraphPath::startPoint)
    .def_readwrite("endPoint", &hstd::ext::GraphPath::endPoint)
    .def_readwrite("bezier", &hstd::ext::GraphPath::bezier)
    .def("point",
         static_cast<void(hstd::ext::GraphPath::*)(double, double)>(&hstd::ext::GraphPath::point),
         pybind11::arg("x"),
         pybind11::arg("y"))
    .def("point",
         static_cast<void(hstd::ext::GraphPath::*)(hstd::ext::GraphPoint const&)>(&hstd::ext::GraphPath::point),
         pybind11::arg("p"))
    .def("__repr__", [](hstd::ext::GraphPath _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphPath _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphSize>(m, "hstdextGraphSize")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphSize {
                        hstd::ext::GraphSize result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("w", &hstd::ext::GraphSize::w)
    .def_readwrite("h", &hstd::ext::GraphSize::h)
    .def("height", static_cast<double(hstd::ext::GraphSize::*)() const>(&hstd::ext::GraphSize::height))
    .def("width", static_cast<double(hstd::ext::GraphSize::*)() const>(&hstd::ext::GraphSize::width))
    .def("__repr__", [](hstd::ext::GraphSize _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphSize _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphRect>(m, "hstdextGraphRect")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphRect {
                        hstd::ext::GraphRect result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("left", &hstd::ext::GraphRect::left)
    .def_readwrite("top", &hstd::ext::GraphRect::top)
    .def_readwrite("width", &hstd::ext::GraphRect::width)
    .def_readwrite("height", &hstd::ext::GraphRect::height)
    .def("size", static_cast<hstd::ext::GraphSize(hstd::ext::GraphRect::*)() const>(&hstd::ext::GraphRect::size))
    .def("__repr__", [](hstd::ext::GraphRect _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphRect _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphNodeConstraint>(m, "hstdextGraphNodeConstraint")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphNodeConstraint {
                        hstd::ext::GraphNodeConstraint result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getEmpty", static_cast<hstd::ext::GraphNodeConstraint::Empty const&(hstd::ext::GraphNodeConstraint::*)() const>(&hstd::ext::GraphNodeConstraint::getEmpty))
    .def("getAlign", static_cast<hstd::ext::GraphNodeConstraint::Align const&(hstd::ext::GraphNodeConstraint::*)() const>(&hstd::ext::GraphNodeConstraint::getAlign))
    .def("getFixedRelative", static_cast<hstd::ext::GraphNodeConstraint::FixedRelative&(hstd::ext::GraphNodeConstraint::*)()>(&hstd::ext::GraphNodeConstraint::getFixedRelative))
    .def("getSeparate", static_cast<hstd::ext::GraphNodeConstraint::Separate const&(hstd::ext::GraphNodeConstraint::*)() const>(&hstd::ext::GraphNodeConstraint::getSeparate))
    .def("getMultiSeparate", static_cast<hstd::ext::GraphNodeConstraint::MultiSeparate const&(hstd::ext::GraphNodeConstraint::*)() const>(&hstd::ext::GraphNodeConstraint::getMultiSeparate))
    .def("getPageBoundary", static_cast<hstd::ext::GraphNodeConstraint::PageBoundary const&(hstd::ext::GraphNodeConstraint::*)() const>(&hstd::ext::GraphNodeConstraint::getPageBoundary))
    .def("getKind", static_cast<hstd::ext::GraphNodeConstraint::Kind(hstd::ext::GraphNodeConstraint::*)() const>(&hstd::ext::GraphNodeConstraint::getKind))
    .def_static("InitEmptyStatic",
                static_cast<hstd::ext::GraphNodeConstraint(*)(hstd::ext::GraphNodeConstraint::Empty const&)>(&hstd::ext::GraphNodeConstraint::InitEmpty),
                pybind11::arg("arg"))
    .def_static("InitAlignStatic",
                static_cast<hstd::ext::GraphNodeConstraint(*)(hstd::ext::GraphNodeConstraint::Align const&)>(&hstd::ext::GraphNodeConstraint::InitAlign),
                pybind11::arg("arg"))
    .def_static("InitSeparateStatic",
                static_cast<hstd::ext::GraphNodeConstraint(*)(hstd::ext::GraphNodeConstraint::Separate const&)>(&hstd::ext::GraphNodeConstraint::InitSeparate),
                pybind11::arg("arg"))
    .def_static("InitMultiSeparateStatic",
                static_cast<hstd::ext::GraphNodeConstraint(*)(hstd::ext::GraphNodeConstraint::MultiSeparate const&)>(&hstd::ext::GraphNodeConstraint::InitMultiSeparate),
                pybind11::arg("arg"))
    .def_static("InitFixedRelativeStatic",
                static_cast<hstd::ext::GraphNodeConstraint(*)(hstd::ext::GraphNodeConstraint::FixedRelative const&)>(&hstd::ext::GraphNodeConstraint::InitFixedRelative),
                pybind11::arg("arg"))
    .def_static("InitPageBoundaryStatic",
                static_cast<hstd::ext::GraphNodeConstraint(*)(hstd::ext::GraphNodeConstraint::PageBoundary const&)>(&hstd::ext::GraphNodeConstraint::InitPageBoundary),
                pybind11::arg("arg"))
    .def("__repr__", [](hstd::ext::GraphNodeConstraint _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphNodeConstraint _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphNodeConstraint::Empty>(m, "hstdextGraphNodeConstraintEmpty")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphNodeConstraint::Empty {
                        hstd::ext::GraphNodeConstraint::Empty result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](hstd::ext::GraphNodeConstraint::Empty _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphNodeConstraint::Empty _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphNodeConstraint::Align>(m, "hstdextGraphNodeConstraintAlign")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphNodeConstraint::Align {
                        hstd::ext::GraphNodeConstraint::Align result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("nodes", &hstd::ext::GraphNodeConstraint::Align::nodes)
    .def_readwrite("dimension", &hstd::ext::GraphNodeConstraint::Align::dimension, R"RAW(Which axist to align on)RAW")
    .def("toColaString", static_cast<std::string(hstd::ext::GraphNodeConstraint::Align::*)() const>(&hstd::ext::GraphNodeConstraint::Align::toColaString))
    .def("__repr__", [](hstd::ext::GraphNodeConstraint::Align _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphNodeConstraint::Align _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphNodeConstraint::Align::Spec>(m, "hstdextGraphNodeConstraintAlignSpec")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphNodeConstraint::Align::Spec {
                        hstd::ext::GraphNodeConstraint::Align::Spec result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("node", &hstd::ext::GraphNodeConstraint::Align::Spec::node, R"RAW(Rectangle index)RAW")
    .def_readwrite("fixPos", &hstd::ext::GraphNodeConstraint::Align::Spec::fixPos, R"RAW(??? wtf)RAW")
    .def_readwrite("offset", &hstd::ext::GraphNodeConstraint::Align::Spec::offset, R"RAW(Offset from the axis)RAW")
    .def("__repr__", [](hstd::ext::GraphNodeConstraint::Align::Spec _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphNodeConstraint::Align::Spec _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphNodeConstraint::Separate>(m, "hstdextGraphNodeConstraintSeparate")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphNodeConstraint::Separate {
                        hstd::ext::GraphNodeConstraint::Separate result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("left", &hstd::ext::GraphNodeConstraint::Separate::left)
    .def_readwrite("right", &hstd::ext::GraphNodeConstraint::Separate::right)
    .def_readwrite("separationDistance", &hstd::ext::GraphNodeConstraint::Separate::separationDistance)
    .def_readwrite("isExactSeparation", &hstd::ext::GraphNodeConstraint::Separate::isExactSeparation)
    .def_readwrite("dimension", &hstd::ext::GraphNodeConstraint::Separate::dimension, R"RAW(Which axis to partition
nodes)RAW")
    .def("toColaString", static_cast<std::string(hstd::ext::GraphNodeConstraint::Separate::*)() const>(&hstd::ext::GraphNodeConstraint::Separate::toColaString))
    .def("__repr__", [](hstd::ext::GraphNodeConstraint::Separate _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphNodeConstraint::Separate _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphNodeConstraint::MultiSeparate>(m, "hstdextGraphNodeConstraintMultiSeparate")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphNodeConstraint::MultiSeparate {
                        hstd::ext::GraphNodeConstraint::MultiSeparate result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("lines", &hstd::ext::GraphNodeConstraint::MultiSeparate::lines)
    .def_readwrite("alignPairs", &hstd::ext::GraphNodeConstraint::MultiSeparate::alignPairs)
    .def_readwrite("dimension", &hstd::ext::GraphNodeConstraint::MultiSeparate::dimension)
    .def_readwrite("separationDistance", &hstd::ext::GraphNodeConstraint::MultiSeparate::separationDistance)
    .def_readwrite("isExactSeparation", &hstd::ext::GraphNodeConstraint::MultiSeparate::isExactSeparation)
    .def("toColaString", static_cast<std::string(hstd::ext::GraphNodeConstraint::MultiSeparate::*)() const>(&hstd::ext::GraphNodeConstraint::MultiSeparate::toColaString))
    .def("__repr__", [](hstd::ext::GraphNodeConstraint::MultiSeparate _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphNodeConstraint::MultiSeparate _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphNodeConstraint::FixedRelative>(m, "hstdextGraphNodeConstraintFixedRelative")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphNodeConstraint::FixedRelative {
                        hstd::ext::GraphNodeConstraint::FixedRelative result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("nodes", &hstd::ext::GraphNodeConstraint::FixedRelative::nodes)
    .def_readwrite("fixedPosition", &hstd::ext::GraphNodeConstraint::FixedRelative::fixedPosition)
    .def("__repr__", [](hstd::ext::GraphNodeConstraint::FixedRelative _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphNodeConstraint::FixedRelative _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphNodeConstraint::PageBoundary>(m, "hstdextGraphNodeConstraintPageBoundary")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphNodeConstraint::PageBoundary {
                        hstd::ext::GraphNodeConstraint::PageBoundary result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("rect", &hstd::ext::GraphNodeConstraint::PageBoundary::rect)
    .def_readwrite("weight", &hstd::ext::GraphNodeConstraint::PageBoundary::weight)
    .def_readwrite("nodes", &hstd::ext::GraphNodeConstraint::PageBoundary::nodes)
    .def("toColaString",
         static_cast<std::string(hstd::ext::GraphNodeConstraint::PageBoundary::*)(std::vector<vpsc::Rectangle*> const&) const>(&hstd::ext::GraphNodeConstraint::PageBoundary::toColaString),
         pybind11::arg("allRects"))
    .def("__repr__", [](hstd::ext::GraphNodeConstraint::PageBoundary _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphNodeConstraint::PageBoundary _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphEdge>(m, "hstdextGraphEdge")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphEdge {
                        hstd::ext::GraphEdge result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("source", &hstd::ext::GraphEdge::source)
    .def_readwrite("target", &hstd::ext::GraphEdge::target)
    .def_readwrite("bundle", &hstd::ext::GraphEdge::bundle)
    .def("__repr__", [](hstd::ext::GraphEdge _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphEdge _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphEdgeConstraint>(m, "hstdextGraphEdgeConstraint")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphEdgeConstraint {
                        hstd::ext::GraphEdgeConstraint result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("sourcePort", &hstd::ext::GraphEdgeConstraint::sourcePort)
    .def_readwrite("targetPort", &hstd::ext::GraphEdgeConstraint::targetPort)
    .def_readwrite("sourceOffset", &hstd::ext::GraphEdgeConstraint::sourceOffset, R"RAW(\brief Offset the port position on the side of the shape. Value in
range [0, 1] used as a relative position along the edge of the
shape. For vertical edges (west/east) the port movement would be
vertical, and for horizontal (north/south) it would be horizontal.
If the value is not provided the nodes are placed in the center
with the ratio computed automatically.)RAW")
    .def_readwrite("targetOffset", &hstd::ext::GraphEdgeConstraint::targetOffset)
    .def_readwrite("sourceCheckpoint", &hstd::ext::GraphEdgeConstraint::sourceCheckpoint)
    .def_readwrite("targetCheckpoint", &hstd::ext::GraphEdgeConstraint::targetCheckpoint)
    .def("__repr__", [](hstd::ext::GraphEdgeConstraint _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphEdgeConstraint _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphLayoutIR>(m, "hstdextGraphLayoutIR")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphLayoutIR {
                        hstd::ext::GraphLayoutIR result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("rectangles", &hstd::ext::GraphLayoutIR::rectangles, R"RAW(\brief Nodes for the graph. Node is identified by the index in the
array of sizes. In the result value each original qsize is mapped
to the rectangle.)RAW")
    .def_readwrite("edges", &hstd::ext::GraphLayoutIR::edges, R"RAW(\brief List of source-target pairs. Edge source/target IDs refer to
the size rectangles.)RAW")
    .def_readwrite("nodeConstraints", &hstd::ext::GraphLayoutIR::nodeConstraints, R"RAW(\brief Cola nodeConstraints for graph layout. This part is
backend-specific.)RAW")
    .def_readwrite("subgraphs", &hstd::ext::GraphLayoutIR::subgraphs)
    .def_readwrite("edgeLabels", &hstd::ext::GraphLayoutIR::edgeLabels, R"RAW(\brief If some edge has a dedicated label of specified size.)RAW")
    .def_readwrite("edgeConstraints", &hstd::ext::GraphLayoutIR::edgeConstraints)
    .def_readwrite("width", &hstd::ext::GraphLayoutIR::width)
    .def_readwrite("height", &hstd::ext::GraphLayoutIR::height)
    .def_readwrite("leftBBoxMargin", &hstd::ext::GraphLayoutIR::leftBBoxMargin)
    .def_readwrite("rightBBoxMargin", &hstd::ext::GraphLayoutIR::rightBBoxMargin)
    .def_readwrite("topBBoxMargin", &hstd::ext::GraphLayoutIR::topBBoxMargin)
    .def_readwrite("bottomBBoxMargin", &hstd::ext::GraphLayoutIR::bottomBBoxMargin)
    .def_readwrite("graphName", &hstd::ext::GraphLayoutIR::graphName, R"RAW(\brief Graph name. Backend-specific.)RAW")
    .def_readwrite("graphviz_size_scaling", &hstd::ext::GraphLayoutIR::graphviz_size_scaling, R"RAW(\brief Which DPI to use when converting to and from graphviz sizes.
Backend-specific, 72 is the default used by graphviz.)RAW")
    .def("validate", static_cast<void(hstd::ext::GraphLayoutIR::*)()>(&hstd::ext::GraphLayoutIR::validate), R"RAW(\brief validate the edge/rectangle structure for debugging. Throws
assert failure if the structure is incorrect.)RAW")
    .def("doGraphvizConvert", static_cast<hstd::ext::GraphLayoutIR::Result(hstd::ext::GraphLayoutIR::*)()>(&hstd::ext::GraphLayoutIR::doGraphvizConvert))
    .def("doHolaConvert", static_cast<hstd::ext::GraphLayoutIR::Result(hstd::ext::GraphLayoutIR::*)()>(&hstd::ext::GraphLayoutIR::doHolaConvert))
    .def("doColaConvert", static_cast<hstd::ext::GraphLayoutIR::Result(hstd::ext::GraphLayoutIR::*)()>(&hstd::ext::GraphLayoutIR::doColaConvert))
    .def("doColaSvgWrite",
         static_cast<void(hstd::ext::GraphLayoutIR::*)(std::string const&)>(&hstd::ext::GraphLayoutIR::doColaSvgWrite),
         pybind11::arg("path"))
    .def("doColaStrFormat", static_cast<std::string(hstd::ext::GraphLayoutIR::*)()>(&hstd::ext::GraphLayoutIR::doColaStrFormat))
    .def("__repr__", [](hstd::ext::GraphLayoutIR _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphLayoutIR _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphLayoutIR::Subgraph>(m, "hstdextGraphLayoutIRSubgraph")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphLayoutIR::Subgraph {
                        hstd::ext::GraphLayoutIR::Subgraph result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](hstd::ext::GraphLayoutIR::Subgraph _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphLayoutIR::Subgraph _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphLayoutIR::Edge>(m, "hstdextGraphLayoutIREdge")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphLayoutIR::Edge {
                        hstd::ext::GraphLayoutIR::Edge result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("paths", &hstd::ext::GraphLayoutIR::Edge::paths, R"RAW(\brief Sequence of painter paths going from source to target
node. If the node has a label rectangle specified, the paths
are placed in a way to accomodate for the rectangle.)RAW")
    .def_readwrite("labelRect", &hstd::ext::GraphLayoutIR::Edge::labelRect, R"RAW(\brief Edge label rectangle)RAW")
    .def("__repr__", [](hstd::ext::GraphLayoutIR::Edge _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphLayoutIR::Edge _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphLayoutIR::Result>(m, "hstdextGraphLayoutIRResult")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphLayoutIR::Result {
                        hstd::ext::GraphLayoutIR::Result result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("fixed", &hstd::ext::GraphLayoutIR::Result::fixed, R"RAW(\brief Fixed node layout rectangles with absolute coordinates.
Subgraph nodes are also included. Edge label nodes are not
included.)RAW")
    .def_readwrite("lines", &hstd::ext::GraphLayoutIR::Result::lines, R"RAW(\brief Mapping from the source-target edge pair to the edge
layout spec)RAW")
    .def_readwrite("bbox", &hstd::ext::GraphLayoutIR::Result::bbox, R"RAW(\brief Bounding box for the whole rectangle)RAW")
    .def_readwrite("subgraphs", &hstd::ext::GraphLayoutIR::Result::subgraphs, R"RAW(\brief Top-level list of subgraphs)RAW")
    .def_readwrite("subgraphPaths", &hstd::ext::GraphLayoutIR::Result::subgraphPaths, R"RAW(\brief Flattened list of subgraphs in DFS order with paths)RAW")
    .def("__repr__", [](hstd::ext::GraphLayoutIR::Result _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphLayoutIR::Result _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<hstd::ext::GraphLayoutIR::Result::Subgraph>(m, "hstdextGraphLayoutIRResultSubgraph")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> hstd::ext::GraphLayoutIR::Result::Subgraph {
                        hstd::ext::GraphLayoutIR::Result::Subgraph result{};
                        org::bind::python::init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("bbox", &hstd::ext::GraphLayoutIR::Result::Subgraph::bbox, R"RAW(\brief Bounding box for the rectangle content)RAW")
    .def_readwrite("subgraphs", &hstd::ext::GraphLayoutIR::Result::Subgraph::subgraphs)
    .def("__repr__", [](hstd::ext::GraphLayoutIR::Result::Subgraph _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd::ext::GraphLayoutIR::Result::Subgraph _self, std::string name) -> pybind11::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<hstd::ext::GraphDimension>(m, "hstdextGraphDimension", type_registry_guard);
  pybind11::enum_<hstd::ext::GraphDimension>(m, "hstdextGraphDimension")
    .value("XDIM", hstd::ext::GraphDimension::XDIM)
    .value("YDIM", hstd::ext::GraphDimension::YDIM)
    .value("UNSET", hstd::ext::GraphDimension::UNSET)
    .def("__iter__", [](hstd::ext::GraphDimension _self) -> org::bind::python::PyEnumIterator<hstd::ext::GraphDimension> {
                     return
                     org::bind::python::PyEnumIterator<hstd::ext::GraphDimension>
                     ();
                     })
    ;
  bind_enum_iterator<hstd::ext::GraphNodeConstraint::Kind>(m, "hstdextGraphNodeConstraintKind", type_registry_guard);
  pybind11::enum_<hstd::ext::GraphNodeConstraint::Kind>(m, "hstdextGraphNodeConstraintKind")
    .value("Empty", hstd::ext::GraphNodeConstraint::Kind::Empty)
    .value("Align", hstd::ext::GraphNodeConstraint::Kind::Align)
    .value("FixedRelative", hstd::ext::GraphNodeConstraint::Kind::FixedRelative)
    .value("Separate", hstd::ext::GraphNodeConstraint::Kind::Separate)
    .value("MultiSeparate", hstd::ext::GraphNodeConstraint::Kind::MultiSeparate)
    .value("PageBoundary", hstd::ext::GraphNodeConstraint::Kind::PageBoundary)
    .def("__iter__", [](hstd::ext::GraphNodeConstraint::Kind _self) -> org::bind::python::PyEnumIterator<hstd::ext::GraphNodeConstraint::Kind> {
                     return
                     org::bind::python::PyEnumIterator<hstd::ext::GraphNodeConstraint::Kind>
                     ();
                     })
    ;
  bind_enum_iterator<hstd::ext::GraphEdgeConstraint::Port>(m, "hstdextGraphEdgeConstraintPort", type_registry_guard);
  pybind11::enum_<hstd::ext::GraphEdgeConstraint::Port>(m, "hstdextGraphEdgeConstraintPort")
    .value("Default", hstd::ext::GraphEdgeConstraint::Port::Default)
    .value("North", hstd::ext::GraphEdgeConstraint::Port::North)
    .value("South", hstd::ext::GraphEdgeConstraint::Port::South)
    .value("West", hstd::ext::GraphEdgeConstraint::Port::West)
    .value("East", hstd::ext::GraphEdgeConstraint::Port::East)
    .value("Center", hstd::ext::GraphEdgeConstraint::Port::Center)
    .def("__iter__", [](hstd::ext::GraphEdgeConstraint::Port _self) -> org::bind::python::PyEnumIterator<hstd::ext::GraphEdgeConstraint::Port> {
                     return
                     org::bind::python::PyEnumIterator<hstd::ext::GraphEdgeConstraint::Port>
                     ();
                     })
    ;
}
/* clang-format on */