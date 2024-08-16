/* clang-format off */
#undef slots
#define PYBIND11_DETAILED_ERROR_MESSAGES
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>
#include <py_libs/pybind11_utils.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
PYBIND11_MAKE_OPAQUE(std::vector<GraphPoint>)
PYBIND11_MAKE_OPAQUE(Vec<GraphPoint>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphNodeConstraint::Align::Spec>)
PYBIND11_MAKE_OPAQUE(Vec<GraphNodeConstraint::Align::Spec>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphNodeConstraint::Align>)
PYBIND11_MAKE_OPAQUE(Vec<GraphNodeConstraint::Align>)
PYBIND11_MAKE_OPAQUE(std::vector<std::pair<int, int>>)
PYBIND11_MAKE_OPAQUE(Vec<std::pair<int, int>>)
PYBIND11_MAKE_OPAQUE(std::vector<int>)
PYBIND11_MAKE_OPAQUE(Vec<int>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphSize>)
PYBIND11_MAKE_OPAQUE(Vec<GraphSize>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphEdge>)
PYBIND11_MAKE_OPAQUE(Vec<GraphEdge>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphNodeConstraint>)
PYBIND11_MAKE_OPAQUE(Vec<GraphNodeConstraint>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphLayoutIR::Subgraph>)
PYBIND11_MAKE_OPAQUE(Vec<GraphLayoutIR::Subgraph>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<GraphEdge, GraphSize>)
PYBIND11_MAKE_OPAQUE(UnorderedMap<GraphEdge, GraphSize>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<GraphEdge, GraphEdgeConstraint>)
PYBIND11_MAKE_OPAQUE(UnorderedMap<GraphEdge, GraphEdgeConstraint>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphPath>)
PYBIND11_MAKE_OPAQUE(Vec<GraphPath>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphRect>)
PYBIND11_MAKE_OPAQUE(Vec<GraphRect>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<GraphEdge, GraphLayoutIR::Edge>)
PYBIND11_MAKE_OPAQUE(UnorderedMap<GraphEdge, GraphLayoutIR::Edge>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphLayoutIR::Result::Subgraph>)
PYBIND11_MAKE_OPAQUE(Vec<GraphLayoutIR::Result::Subgraph>)
PYBIND11_MAKE_OPAQUE(std::vector<Vec<int>>)
PYBIND11_MAKE_OPAQUE(Vec<Vec<int>>)
PYBIND11_MODULE(py_adaptagrams, m) {
  PyTypeRegistryGuard type_registry_guard{};
  bind_vector<GraphPoint>(m, "VecOfGraphPoint", type_registry_guard);
  bind_vector<GraphNodeConstraint::Align::Spec>(m, "VecOfGraphNodeConstraintAlignSpec", type_registry_guard);
  bind_vector<GraphNodeConstraint::Align>(m, "VecOfGraphNodeConstraintAlign", type_registry_guard);
  bind_vector<std::pair<int, int>>(m, "VecOfstdpairOfintint", type_registry_guard);
  bind_vector<int>(m, "VecOfint", type_registry_guard);
  bind_vector<GraphSize>(m, "VecOfGraphSize", type_registry_guard);
  bind_vector<GraphEdge>(m, "VecOfGraphEdge", type_registry_guard);
  bind_vector<GraphNodeConstraint>(m, "VecOfGraphNodeConstraint", type_registry_guard);
  bind_vector<GraphLayoutIR::Subgraph>(m, "VecOfGraphLayoutIRSubgraph", type_registry_guard);
  bind_unordered_map<GraphEdge, GraphSize>(m, "UnorderedMapOfGraphEdgeGraphSize", type_registry_guard);
  bind_unordered_map<GraphEdge, GraphEdgeConstraint>(m, "UnorderedMapOfGraphEdgeGraphEdgeConstraint", type_registry_guard);
  bind_vector<GraphPath>(m, "VecOfGraphPath", type_registry_guard);
  bind_vector<GraphRect>(m, "VecOfGraphRect", type_registry_guard);
  bind_unordered_map<GraphEdge, GraphLayoutIR::Edge>(m, "UnorderedMapOfGraphEdgeGraphLayoutIREdge", type_registry_guard);
  bind_vector<GraphLayoutIR::Result::Subgraph>(m, "VecOfGraphLayoutIRResultSubgraph", type_registry_guard);
  bind_vector<Vec<int>>(m, "VecOfVecOfint", type_registry_guard);
  pybind11::class_<GraphPoint>(m, "GraphPoint")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphPoint {
                        GraphPoint result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("x", &GraphPoint::x)
    .def_readwrite("y", &GraphPoint::y)
    .def("__repr__", [](GraphPoint _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphPoint _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphPath>(m, "GraphPath")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphPath {
                        GraphPath result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("points", &GraphPath::points)
    .def_readwrite("startPoint", &GraphPath::startPoint)
    .def_readwrite("endPoint", &GraphPath::endPoint)
    .def_readwrite("bezier", &GraphPath::bezier)
    .def("point",
         static_cast<void(GraphPath::*)(double, double)>(&GraphPath::point),
         pybind11::arg("x"),
         pybind11::arg("y"))
    .def("point",
         static_cast<void(GraphPath::*)(GraphPoint const&)>(&GraphPath::point),
         pybind11::arg("p"))
    .def("__repr__", [](GraphPath _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphPath _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphSize>(m, "GraphSize")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphSize {
                        GraphSize result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("w", &GraphSize::w)
    .def_readwrite("h", &GraphSize::h)
    .def("height", static_cast<double(GraphSize::*)() const>(&GraphSize::height))
    .def("width", static_cast<double(GraphSize::*)() const>(&GraphSize::width))
    .def("__repr__", [](GraphSize _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphSize _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphRect>(m, "GraphRect")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphRect {
                        GraphRect result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("left", &GraphRect::left)
    .def_readwrite("top", &GraphRect::top)
    .def_readwrite("width", &GraphRect::width)
    .def_readwrite("height", &GraphRect::height)
    .def("size", static_cast<GraphSize(GraphRect::*)() const>(&GraphRect::size))
    .def("setBottomLeft",
         static_cast<void(GraphRect::*)(double, double)>(&GraphRect::setBottomLeft),
         pybind11::arg("x"),
         pybind11::arg("y"))
    .def("setTopRight",
         static_cast<void(GraphRect::*)(double, double)>(&GraphRect::setTopRight),
         pybind11::arg("x"),
         pybind11::arg("y"))
    .def("setBottomLeft",
         static_cast<void(GraphRect::*)(GraphPoint const&)>(&GraphRect::setBottomLeft),
         pybind11::arg("p"))
    .def("setTopRight",
         static_cast<void(GraphRect::*)(GraphPoint const&)>(&GraphRect::setTopRight),
         pybind11::arg("p"))
    .def("__repr__", [](GraphRect _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphRect _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphNodeConstraint>(m, "GraphNodeConstraint")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphNodeConstraint {
                        GraphNodeConstraint result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getEmpty", static_cast<GraphNodeConstraint::Empty const&(GraphNodeConstraint::*)() const>(&GraphNodeConstraint::getEmpty))
    .def("getAlign", static_cast<GraphNodeConstraint::Align const&(GraphNodeConstraint::*)() const>(&GraphNodeConstraint::getAlign))
    .def("getFixedRelative", static_cast<GraphNodeConstraint::FixedRelative&(GraphNodeConstraint::*)()>(&GraphNodeConstraint::getFixedRelative))
    .def("getSeparate", static_cast<GraphNodeConstraint::Separate const&(GraphNodeConstraint::*)() const>(&GraphNodeConstraint::getSeparate))
    .def("getMultiSeparate", static_cast<GraphNodeConstraint::MultiSeparate const&(GraphNodeConstraint::*)() const>(&GraphNodeConstraint::getMultiSeparate))
    .def("getPageBoundary", static_cast<GraphNodeConstraint::PageBoundary const&(GraphNodeConstraint::*)() const>(&GraphNodeConstraint::getPageBoundary))
    .def("getKind", static_cast<GraphNodeConstraint::Kind(GraphNodeConstraint::*)() const>(&GraphNodeConstraint::getKind))
    .def_static("InitEmptyStatic",
                static_cast<GraphNodeConstraint(*)(GraphNodeConstraint::Empty const&)>(&GraphNodeConstraint::InitEmpty),
                pybind11::arg("arg"))
    .def_static("InitAlignStatic",
                static_cast<GraphNodeConstraint(*)(GraphNodeConstraint::Align const&)>(&GraphNodeConstraint::InitAlign),
                pybind11::arg("arg"))
    .def_static("InitSeparateStatic",
                static_cast<GraphNodeConstraint(*)(GraphNodeConstraint::Separate const&)>(&GraphNodeConstraint::InitSeparate),
                pybind11::arg("arg"))
    .def_static("InitMultiSeparateStatic",
                static_cast<GraphNodeConstraint(*)(GraphNodeConstraint::MultiSeparate const&)>(&GraphNodeConstraint::InitMultiSeparate),
                pybind11::arg("arg"))
    .def_static("InitFixedRelativeStatic",
                static_cast<GraphNodeConstraint(*)(GraphNodeConstraint::FixedRelative const&)>(&GraphNodeConstraint::InitFixedRelative),
                pybind11::arg("arg"))
    .def_static("InitPageBoundaryStatic",
                static_cast<GraphNodeConstraint(*)(GraphNodeConstraint::PageBoundary const&)>(&GraphNodeConstraint::InitPageBoundary),
                pybind11::arg("arg"))
    .def("__repr__", [](GraphNodeConstraint _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphNodeConstraint _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphNodeConstraint::Empty>(m, "GraphNodeConstraintEmpty")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphNodeConstraint::Empty {
                        GraphNodeConstraint::Empty result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](GraphNodeConstraint::Empty _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphNodeConstraint::Empty _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphNodeConstraint::Align>(m, "GraphNodeConstraintAlign")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphNodeConstraint::Align {
                        GraphNodeConstraint::Align result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("nodes", &GraphNodeConstraint::Align::nodes)
    .def_readwrite("dimension", &GraphNodeConstraint::Align::dimension, R"RAW(Which axist to align on)RAW")
    .def("toColaString", static_cast<std::string(GraphNodeConstraint::Align::*)() const>(&GraphNodeConstraint::Align::toColaString))
    .def("__repr__", [](GraphNodeConstraint::Align _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphNodeConstraint::Align _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphNodeConstraint::Align::Spec>(m, "GraphNodeConstraintAlignSpec")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphNodeConstraint::Align::Spec {
                        GraphNodeConstraint::Align::Spec result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("node", &GraphNodeConstraint::Align::Spec::node, R"RAW(Rectangle index)RAW")
    .def_readwrite("fixPos", &GraphNodeConstraint::Align::Spec::fixPos, R"RAW(??? wtf)RAW")
    .def_readwrite("offset", &GraphNodeConstraint::Align::Spec::offset, R"RAW(Offset from the axis)RAW")
    .def("__repr__", [](GraphNodeConstraint::Align::Spec _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphNodeConstraint::Align::Spec _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphNodeConstraint::Separate>(m, "GraphNodeConstraintSeparate")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphNodeConstraint::Separate {
                        GraphNodeConstraint::Separate result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("left", &GraphNodeConstraint::Separate::left)
    .def_readwrite("right", &GraphNodeConstraint::Separate::right)
    .def_readwrite("separationDistance", &GraphNodeConstraint::Separate::separationDistance)
    .def_readwrite("isExactSeparation", &GraphNodeConstraint::Separate::isExactSeparation)
    .def_readwrite("dimension", &GraphNodeConstraint::Separate::dimension, R"RAW(Which axis to partition
nodes)RAW")
    .def("toColaString", static_cast<std::string(GraphNodeConstraint::Separate::*)() const>(&GraphNodeConstraint::Separate::toColaString))
    .def("__repr__", [](GraphNodeConstraint::Separate _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphNodeConstraint::Separate _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphNodeConstraint::MultiSeparate>(m, "GraphNodeConstraintMultiSeparate")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphNodeConstraint::MultiSeparate {
                        GraphNodeConstraint::MultiSeparate result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("lines", &GraphNodeConstraint::MultiSeparate::lines)
    .def_readwrite("alignPairs", &GraphNodeConstraint::MultiSeparate::alignPairs)
    .def_readwrite("dimension", &GraphNodeConstraint::MultiSeparate::dimension)
    .def_readwrite("separationDistance", &GraphNodeConstraint::MultiSeparate::separationDistance)
    .def_readwrite("isExactSeparation", &GraphNodeConstraint::MultiSeparate::isExactSeparation)
    .def("toColaString", static_cast<std::string(GraphNodeConstraint::MultiSeparate::*)() const>(&GraphNodeConstraint::MultiSeparate::toColaString))
    .def("__repr__", [](GraphNodeConstraint::MultiSeparate _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphNodeConstraint::MultiSeparate _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphNodeConstraint::FixedRelative>(m, "GraphNodeConstraintFixedRelative")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphNodeConstraint::FixedRelative {
                        GraphNodeConstraint::FixedRelative result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("nodes", &GraphNodeConstraint::FixedRelative::nodes)
    .def_readwrite("fixedPosition", &GraphNodeConstraint::FixedRelative::fixedPosition)
    .def("__repr__", [](GraphNodeConstraint::FixedRelative _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphNodeConstraint::FixedRelative _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphNodeConstraint::PageBoundary>(m, "GraphNodeConstraintPageBoundary")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphNodeConstraint::PageBoundary {
                        GraphNodeConstraint::PageBoundary result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("rect", &GraphNodeConstraint::PageBoundary::rect)
    .def_readwrite("weight", &GraphNodeConstraint::PageBoundary::weight)
    .def_readwrite("nodes", &GraphNodeConstraint::PageBoundary::nodes)
    .def("toColaString",
         static_cast<std::string(GraphNodeConstraint::PageBoundary::*)(std::vector<vpsc::Rectangle*> const&) const>(&GraphNodeConstraint::PageBoundary::toColaString),
         pybind11::arg("allRects"))
    .def("__repr__", [](GraphNodeConstraint::PageBoundary _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphNodeConstraint::PageBoundary _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphEdge>(m, "GraphEdge")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphEdge {
                        GraphEdge result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("source", &GraphEdge::source)
    .def_readwrite("target", &GraphEdge::target)
    .def("__repr__", [](GraphEdge _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphEdge _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphEdgeConstraint>(m, "GraphEdgeConstraint")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphEdgeConstraint {
                        GraphEdgeConstraint result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("sourcePort", &GraphEdgeConstraint::sourcePort)
    .def_readwrite("targetPort", &GraphEdgeConstraint::targetPort)
    .def("__repr__", [](GraphEdgeConstraint _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphEdgeConstraint _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphLayoutIR>(m, "GraphLayoutIR")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphLayoutIR {
                        GraphLayoutIR result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("rectangles", &GraphLayoutIR::rectangles, R"RAW(\brief Nodes for the graph. Node is identified by the index in the
array of sizes. In the result value each original qsize is mapped
to the rectangle.)RAW")
    .def_readwrite("edges", &GraphLayoutIR::edges, R"RAW(\brief List of source-target pairs. Edge source/target IDs refer to
the size rectangles.)RAW")
    .def_readwrite("nodeConstraints", &GraphLayoutIR::nodeConstraints, R"RAW(\brief Cola nodeConstraints for graph layout. This part is
backend-specific.)RAW")
    .def_readwrite("subgraphs", &GraphLayoutIR::subgraphs)
    .def_readwrite("edgeLabels", &GraphLayoutIR::edgeLabels, R"RAW(\brief If some edge has a dedicated label of specified size.)RAW")
    .def_readwrite("edgeConstraints", &GraphLayoutIR::edgeConstraints)
    .def_readwrite("width", &GraphLayoutIR::width)
    .def_readwrite("height", &GraphLayoutIR::height)
    .def_readwrite("leftBBoxMargin", &GraphLayoutIR::leftBBoxMargin)
    .def_readwrite("rightBBoxMargin", &GraphLayoutIR::rightBBoxMargin)
    .def_readwrite("topBBoxMargin", &GraphLayoutIR::topBBoxMargin)
    .def_readwrite("bottomBBoxMargin", &GraphLayoutIR::bottomBBoxMargin)
    .def_readwrite("graphName", &GraphLayoutIR::graphName, R"RAW(\brief Graph name. Backend-specific.)RAW")
    .def_readwrite("graphviz_size_scaling", &GraphLayoutIR::graphviz_size_scaling, R"RAW(\brief Which DPI to use when converting to and from graphviz sizes.
Backend-specific, 72 is the default used by graphviz.)RAW")
    .def("validate", static_cast<void(GraphLayoutIR::*)()>(&GraphLayoutIR::validate), R"RAW(\brief validate the edge/rectangle structure for debugging. Throws
assert failure if the structure is incorrect.)RAW")
    .def("doHolaConvert", static_cast<GraphLayoutIR::Result(GraphLayoutIR::*)()>(&GraphLayoutIR::doHolaConvert))
    .def("doColaConvert", static_cast<GraphLayoutIR::Result(GraphLayoutIR::*)()>(&GraphLayoutIR::doColaConvert))
    .def("doColaSvgWrite",
         static_cast<void(GraphLayoutIR::*)(std::string const&)>(&GraphLayoutIR::doColaSvgWrite),
         pybind11::arg("path"))
    .def("doColaStrFormat", static_cast<std::string(GraphLayoutIR::*)()>(&GraphLayoutIR::doColaStrFormat))
    .def("__repr__", [](GraphLayoutIR _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphLayoutIR _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphLayoutIR::Subgraph>(m, "GraphLayoutIRSubgraph")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphLayoutIR::Subgraph {
                        GraphLayoutIR::Subgraph result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](GraphLayoutIR::Subgraph _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphLayoutIR::Subgraph _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphLayoutIR::Edge>(m, "GraphLayoutIREdge")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphLayoutIR::Edge {
                        GraphLayoutIR::Edge result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("paths", &GraphLayoutIR::Edge::paths, R"RAW(\brief Sequence of painter paths going from source to target
node. If the node has a label rectangle specified, the paths
are placed in a way to accomodate for the rectangle.)RAW")
    .def_readwrite("labelRect", &GraphLayoutIR::Edge::labelRect, R"RAW(\brief Edge label rectangle)RAW")
    .def("__repr__", [](GraphLayoutIR::Edge _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphLayoutIR::Edge _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphLayoutIR::Result>(m, "GraphLayoutIRResult")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphLayoutIR::Result {
                        GraphLayoutIR::Result result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("fixed", &GraphLayoutIR::Result::fixed, R"RAW(\brief Fixed node layout rectangles with absolute coordinates.
Subgraph nodes are also included. Edge label nodes are not
included.)RAW")
    .def_readwrite("lines", &GraphLayoutIR::Result::lines, R"RAW(\brief Mapping from the source-target edge pair to the edge
layout spec)RAW")
    .def_readwrite("bbox", &GraphLayoutIR::Result::bbox, R"RAW(\brief Bounding box for the whole rectangle)RAW")
    .def_readwrite("subgraphs", &GraphLayoutIR::Result::subgraphs, R"RAW(\brief Top-level list of subgraphs)RAW")
    .def_readwrite("subgraphPaths", &GraphLayoutIR::Result::subgraphPaths, R"RAW(\brief Flattened list of subgraphs in DFS order with paths)RAW")
    .def("__repr__", [](GraphLayoutIR::Result _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphLayoutIR::Result _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphLayoutIR::Result::Subgraph>(m, "GraphLayoutIRResultSubgraph")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphLayoutIR::Result::Subgraph {
                        GraphLayoutIR::Result::Subgraph result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("bbox", &GraphLayoutIR::Result::Subgraph::bbox, R"RAW(\brief Bounding box for the rectangle content)RAW")
    .def_readwrite("subgraphs", &GraphLayoutIR::Result::Subgraph::subgraphs)
    .def("__repr__", [](GraphLayoutIR::Result::Subgraph _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphLayoutIR::Result::Subgraph _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<GraphDimension>(m, "GraphDimension", type_registry_guard);
  pybind11::enum_<GraphDimension>(m, "GraphDimension")
    .value("XDIM", GraphDimension::XDIM)
    .value("YDIM", GraphDimension::YDIM)
    .value("UNSET", GraphDimension::UNSET)
    .def("__iter__", [](GraphDimension _self) -> PyEnumIterator<GraphDimension> {
                     return
                     PyEnumIterator<GraphDimension>
                     ();
                     })
    ;
  bind_enum_iterator<GraphNodeConstraint::Kind>(m, "GraphNodeConstraintKind", type_registry_guard);
  pybind11::enum_<GraphNodeConstraint::Kind>(m, "GraphNodeConstraintKind")
    .value("Empty", GraphNodeConstraint::Kind::Empty)
    .value("Align", GraphNodeConstraint::Kind::Align)
    .value("FixedRelative", GraphNodeConstraint::Kind::FixedRelative)
    .value("Separate", GraphNodeConstraint::Kind::Separate)
    .value("MultiSeparate", GraphNodeConstraint::Kind::MultiSeparate)
    .value("PageBoundary", GraphNodeConstraint::Kind::PageBoundary)
    .def("__iter__", [](GraphNodeConstraint::Kind _self) -> PyEnumIterator<GraphNodeConstraint::Kind> {
                     return
                     PyEnumIterator<GraphNodeConstraint::Kind>
                     ();
                     })
    ;
  bind_enum_iterator<GraphEdgeConstraint::Port>(m, "GraphEdgeConstraintPort", type_registry_guard);
  pybind11::enum_<GraphEdgeConstraint::Port>(m, "GraphEdgeConstraintPort")
    .value("Default", GraphEdgeConstraint::Port::Default)
    .value("North", GraphEdgeConstraint::Port::North)
    .value("South", GraphEdgeConstraint::Port::South)
    .value("West", GraphEdgeConstraint::Port::West)
    .value("East", GraphEdgeConstraint::Port::East)
    .value("Center", GraphEdgeConstraint::Port::Center)
    .def("__iter__", [](GraphEdgeConstraint::Port _self) -> PyEnumIterator<GraphEdgeConstraint::Port> {
                     return
                     PyEnumIterator<GraphEdgeConstraint::Port>
                     ();
                     })
    ;
}
/* clang-format on */