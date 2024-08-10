/* clang-format off */
#undef slots
#define PYBIND11_DETAILED_ERROR_MESSAGES
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>
#include <py_libs/pybind11_utils.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
PYBIND11_MAKE_OPAQUE(std::vector<GraphPoint>)
PYBIND11_MAKE_OPAQUE(Vec<GraphPoint>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphConstraint::Align::Spec>)
PYBIND11_MAKE_OPAQUE(Vec<GraphConstraint::Align::Spec>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphConstraint::Align>)
PYBIND11_MAKE_OPAQUE(Vec<GraphConstraint::Align>)
PYBIND11_MAKE_OPAQUE(std::vector<std::pair<int, int>>)
PYBIND11_MAKE_OPAQUE(Vec<std::pair<int, int>>)
PYBIND11_MAKE_OPAQUE(std::vector<int>)
PYBIND11_MAKE_OPAQUE(Vec<int>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphSize>)
PYBIND11_MAKE_OPAQUE(Vec<GraphSize>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphEdge>)
PYBIND11_MAKE_OPAQUE(Vec<GraphEdge>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphConstraint>)
PYBIND11_MAKE_OPAQUE(Vec<GraphConstraint>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphLayoutIR::Subgraph>)
PYBIND11_MAKE_OPAQUE(Vec<GraphLayoutIR::Subgraph>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<GraphEdge, GraphSize>)
PYBIND11_MAKE_OPAQUE(UnorderedMap<GraphEdge, GraphSize>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphRect>)
PYBIND11_MAKE_OPAQUE(Vec<GraphRect>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<GraphEdge, GraphLayoutIR::Edge>)
PYBIND11_MAKE_OPAQUE(UnorderedMap<GraphEdge, GraphLayoutIR::Edge>)
PYBIND11_MAKE_OPAQUE(std::vector<GraphLayoutIR::Result::Subgraph>)
PYBIND11_MAKE_OPAQUE(Vec<GraphLayoutIR::Result::Subgraph>)
PYBIND11_MAKE_OPAQUE(std::vector<Vec<int>>)
PYBIND11_MAKE_OPAQUE(Vec<Vec<int>>)
PYBIND11_MODULE(pyhaxorg, m) {
  bind_vector<GraphPoint>(m, "VecOfGraphPoint");
  bind_vector<GraphConstraint::Align::Spec>(m, "VecOfGraphConstraintAlignSpec");
  bind_vector<GraphConstraint::Align>(m, "VecOfGraphConstraintAlign");
  bind_vector<std::pair<int, int>>(m, "VecOfstdpairOfintint");
  bind_vector<int>(m, "VecOfint");
  bind_vector<GraphSize>(m, "VecOfGraphSize");
  bind_vector<GraphEdge>(m, "VecOfGraphEdge");
  bind_vector<GraphConstraint>(m, "VecOfGraphConstraint");
  bind_vector<GraphLayoutIR::Subgraph>(m, "VecOfGraphLayoutIRSubgraph");
  bind_unordered_map<GraphEdge, GraphSize>(m, "UnorderedMapOfGraphEdgeGraphSize");
  bind_vector<GraphRect>(m, "VecOfGraphRect");
  bind_unordered_map<GraphEdge, GraphLayoutIR::Edge>(m, "UnorderedMapOfGraphEdgeGraphLayoutIREdge");
  bind_vector<GraphLayoutIR::Result::Subgraph>(m, "VecOfGraphLayoutIRResultSubgraph");
  bind_vector<Vec<int>>(m, "VecOfVecOfint");
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
         static_cast<void(GraphPath::*)(int, int)>(&GraphPath::point),
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
    .def("height", static_cast<int(GraphSize::*)() const>(&GraphSize::height))
    .def("width", static_cast<int(GraphSize::*)() const>(&GraphSize::width))
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
         static_cast<void(GraphRect::*)(int, int)>(&GraphRect::setBottomLeft),
         pybind11::arg("x"),
         pybind11::arg("y"))
    .def("setTopRight",
         static_cast<void(GraphRect::*)(int, int)>(&GraphRect::setTopRight),
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
  pybind11::class_<GraphConstraint>(m, "GraphConstraint")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphConstraint {
                        GraphConstraint result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](GraphConstraint _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphConstraint _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphConstraint::Empty>(m, "GraphConstraintEmpty")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphConstraint::Empty {
                        GraphConstraint::Empty result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](GraphConstraint::Empty _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphConstraint::Empty _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphConstraint::Align>(m, "GraphConstraintAlign")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphConstraint::Align {
                        GraphConstraint::Align result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("nodes", &GraphConstraint::Align::nodes)
    .def_readwrite("dimension", &GraphConstraint::Align::dimension, R"RAW(Which axist to align on)RAW")
    .def("__repr__", [](GraphConstraint::Align _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphConstraint::Align _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphConstraint::Align::Spec>(m, "GraphConstraintAlignSpec")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphConstraint::Align::Spec {
                        GraphConstraint::Align::Spec result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("node", &GraphConstraint::Align::Spec::node, R"RAW(Rectangle index)RAW")
    .def_readwrite("fixPos", &GraphConstraint::Align::Spec::fixPos, R"RAW(??? wtf)RAW")
    .def_readwrite("offset", &GraphConstraint::Align::Spec::offset, R"RAW(Offset from the axis)RAW")
    .def("__repr__", [](GraphConstraint::Align::Spec _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphConstraint::Align::Spec _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphConstraint::Separate>(m, "GraphConstraintSeparate")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphConstraint::Separate {
                        GraphConstraint::Separate result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("left", &GraphConstraint::Separate::left)
    .def_readwrite("right", &GraphConstraint::Separate::right)
    .def_readwrite("separationDistance", &GraphConstraint::Separate::separationDistance)
    .def_readwrite("isExactSeparation", &GraphConstraint::Separate::isExactSeparation)
    .def_readwrite("dimension", &GraphConstraint::Separate::dimension, R"RAW(Which axis to partition nodes)RAW")
    .def("__repr__", [](GraphConstraint::Separate _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphConstraint::Separate _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphConstraint::MultiSeparate>(m, "GraphConstraintMultiSeparate")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphConstraint::MultiSeparate {
                        GraphConstraint::MultiSeparate result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("lines", &GraphConstraint::MultiSeparate::lines)
    .def_readwrite("alignPairs", &GraphConstraint::MultiSeparate::alignPairs)
    .def_readwrite("dimension", &GraphConstraint::MultiSeparate::dimension)
    .def_readwrite("separationDistance", &GraphConstraint::MultiSeparate::separationDistance)
    .def_readwrite("isExactSeparation", &GraphConstraint::MultiSeparate::isExactSeparation)
    .def("__repr__", [](GraphConstraint::MultiSeparate _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphConstraint::MultiSeparate _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphConstraint::FixedRelative>(m, "GraphConstraintFixedRelative")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphConstraint::FixedRelative {
                        GraphConstraint::FixedRelative result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("nodes", &GraphConstraint::FixedRelative::nodes)
    .def_readwrite("fixedPosition", &GraphConstraint::FixedRelative::fixedPosition)
    .def("__repr__", [](GraphConstraint::FixedRelative _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphConstraint::FixedRelative _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<GraphConstraint::PageBoundary>(m, "GraphConstraintPageBoundary")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> GraphConstraint::PageBoundary {
                        GraphConstraint::PageBoundary result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("rect", &GraphConstraint::PageBoundary::rect)
    .def_readwrite("weight", &GraphConstraint::PageBoundary::weight)
    .def("__repr__", [](GraphConstraint::PageBoundary _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](GraphConstraint::PageBoundary _self, std::string name) -> pybind11::object {
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
    .def_readwrite("constraints", &GraphLayoutIR::constraints, R"RAW(\brief Cola constraints for graph layout. This part is
backend-specific.)RAW")
    .def_readwrite("subgraphs", &GraphLayoutIR::subgraphs)
    .def_readwrite("edgeLabels", &GraphLayoutIR::edgeLabels, R"RAW(\brief If some edge has a dedicated label of specified size.)RAW")
    .def_readwrite("width", &GraphLayoutIR::width)
    .def_readwrite("height", &GraphLayoutIR::height)
    .def_readwrite("graphName", &GraphLayoutIR::graphName, R"RAW(\brief Graph name. Backend-specific.)RAW")
    .def_readwrite("graphviz_size_scaling", &GraphLayoutIR::graphviz_size_scaling, R"RAW(\brief Which DPI to use when converting to and from graphviz sizes.
Backend-specific, 72 is the default used by graphviz.)RAW")
    .def("validate", static_cast<void(GraphLayoutIR::*)()>(&GraphLayoutIR::validate), R"RAW(\brief validate the edge/rectangle structure for debugging. Throws
assert failure if the structure is incorrect.)RAW")
    .def("doHolaConvert", static_cast<GraphLayoutIR::Result(GraphLayoutIR::*)()>(&GraphLayoutIR::doHolaConvert))
    .def("doColaConvert", static_cast<GraphLayoutIR::Result(GraphLayoutIR::*)()>(&GraphLayoutIR::doColaConvert))
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
}
/* clang-format on */