#pragma once

/// \file org_graph_layout.hpp
///
/// \brief Intermediate representation for interfacing with specific graph
/// layout backends: graphviz and adaptagrams/cola.

#include <libcola/cola.h>
#include <libcola/output_svg.h>
#include <hstd/wrappers/graphviz.hpp>
#include <QRect>
#include <QPolygonF>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <editor/editor_lib/common/app_utils.hpp>
#include <QPainterPath>
#include <libavoid/libavoid.h>
#include <libdialect/graphs.h>


/// \brief IR wrapper for the cola layout constraints
struct GraphConstraint {
    using Res = SPtr<cola::CompoundConstraint>;

    /// \brief Listed nodes must be positioned on the same X/Y dimension in
    /// the layout
    struct Align {
        struct Spec {
            int         node;                  ///< Rectangle index
            Opt<double> fixPos = std::nullopt; ///< ??? wtf
            double      offset = 0.0;          ///< Offset from the axis
        };

        Vec<Spec> nodes;
        vpsc::Dim dimension; ///< Which axist to align on
        DESC_FIELDS(Align, (nodes, dimension));

        /// \brief Map to cola layout constraint object
        Res toCola() const {
            auto result = std::make_shared<cola::AlignmentConstraint>(
                dimension);

            for (auto const& spec : nodes) {
                result->addShape(spec.node, spec.offset);
                if (spec.fixPos) { result->fixPos(*spec.fixPos); }
            }

            return result;
        }
    };

    struct Separate {
        Align     left;
        Align     right;
        double    separationDistance = 1.0;
        bool      isExactSeparation  = false;
        vpsc::Dim dimension; ///< Which axis to partition nodes
        DESC_FIELDS(
            Separate,
            (left, right, separationDistance, isExactSeparation));

        Vec<Res> toCola() const {
            auto left_constraint  = left.toCola();
            auto right_constraint = right.toCola();
            auto result = std::make_shared<cola::SeparationConstraint>(
                dimension,
                dynamic_cast<cola::AlignmentConstraint*>(
                    left_constraint.get()),
                dynamic_cast<cola::AlignmentConstraint*>(
                    right_constraint.get()),
                separationDistance,
                isExactSeparation);

            return {result, left_constraint, right_constraint};
        }
    };

    struct MultiSeparate {
        Vec<Align>          lines;
        Vec<Pair<int, int>> alignPairs;
        vpsc::Dim           dimension;
        double              separationDistance;
        bool                isExactSeparation;

        Vec<Res> toCola() const {
            Vec<Res> result;
            for (auto const& line : lines) {
                result.push_back(line.toCola());
            }

            auto sep = std::make_shared<cola::MultiSeparationConstraint>(
                dimension, separationDistance, isExactSeparation);

            for (auto [pair1, pair2] : alignPairs) {
                sep->addAlignmentPair(
                    dynamic_cast<cola::AlignmentConstraint*>(
                        result.at(pair1).get()),
                    dynamic_cast<cola::AlignmentConstraint*>(
                        result.at(pair2).get()));
            }

            result.push_back(sep);

            return result;
        }
    };

    struct FixedRelative {
        Vec<int> nodes;
        bool     fixedPosition = false;
        Res toCola(std::vector<vpsc::Rectangle*> const& allRects) const {
            return std::make_shared<cola::FixedRelativeConstraint>(
                allRects,
                nodes //
                    | rv::transform(
                        [](int i) { return static_cast<unsigned>(i); })
                    | rs::to<std::vector>(),
                fixedPosition);
        }
    };

    struct PageBoundary {
        QRect  rect;
        double weight = 100.0;
        Res    toCola() const {
            return std::make_shared<cola::PageBoundaryConstraints>(
                rect.left(),
                rect.right(),
                rect.bottom(),
                rect.top(),
                weight);
        }
    };

    Vec<Res> toCola(std::vector<vpsc::Rectangle*> const& allRects) const {
        return std::visit(
            overloaded{
                [&](FixedRelative const& fixed) -> Vec<Res> {
                    return {fixed.toCola(allRects)};
                },
                [&](Align const& align) -> Vec<Res> {
                    return {align.toCola()};
                },
                [&](MultiSeparate const& sep) -> Vec<Res> {
                    return sep.toCola();
                },
                [&](PageBoundary const& sep) -> Vec<Res> {
                    return {sep.toCola()};
                },
                [&](Separate const& sep) -> Vec<Res> {
                    return sep.toCola();
                },
            },
            data);
    }

    SUB_VARIANTS(
        Kind,
        Data,
        data,
        getKind,
        Align,
        FixedRelative,
        Separate,
        MultiSeparate,
        PageBoundary);

    Data data;

    GraphConstraint(CR<Data> data) : data(data) {};
};

/// \brief Main store for the graph layout intermediate representation.
/// Stores a minimum amount of information about the graph properties --
/// list of edges, shapes of nodes, and some backend-specific parameters.
struct GraphLayoutIR {
    using IrEdge = Pair<int, int>;

    struct Subgraph {
        Str graphName; ///< Graphviz graph name

        /// \brief Which nodes go directly in this cluster level (subgraphs
        /// will have their own sub-nodes, there should be no overlap or
        /// duplication)
        Vec<int> nodes;
        /// \brief List of nested subgraphs
        Vec<Subgraph> subgraphs;
        /// \brief For graphviz: px spacing between subgraph and the
        /// content inside.
        Opt<int> internalMargin;

        bool isEmpty() const {
            return nodes.empty()
                && rs::all_of(subgraphs, [](CR<Subgraph> s) {
                       return s.isEmpty();
                   });
        }
    };

    /// \brief Nodes for the graph. Node is identified by the index in the
    /// array of sizes. In the result value each original qsize is mapped
    /// to the rectangle.
    Vec<QSize> rectangles;
    /// \brief List of source-target pairs. Edge source/target IDs refer to
    /// the size rectangles.
    Vec<IrEdge> edges;
    /// \brief Cola constraints for graph layout. This part is
    /// backend-specific.
    Vec<GraphConstraint> constraints;
    Vec<Subgraph>        subgraphs;
    /// \brief If some edge has a dedicated label of specified size.
    UnorderedMap<IrEdge, QSize> edgeLabels;
    double                      width  = 100;
    double                      height = 100;
    /// \brief Graph name. Backend-specific.
    Str graphName = "G";

    /// \brief Which DPI to use when converting to and from graphviz sizes.
    /// Backend-specific, 72 is the default used by graphviz.
    int graphviz_size_scaling = 72;

    /// \brief validate the edge/rectangle structure for debugging. Throws
    /// assert failure if the structure is incorrect.
    void validate() {
        for (auto const& e : enumerator(edges)) {
            for (auto const& it :
                 Vec<int>{e.value().first, e.value().second}) {
                Q_ASSERT_X(
                    it < rectangles.size(),
                    "validate",
                    fmt("Edge {} point is out of range for rectangles: "
                        "[{}] out of {} rects",
                        e.index(),
                        it,
                        rectangles.size()));
            }
        }
    }

    /// \brief Graph edge layout
    struct Edge {
        /// \brief Sequence of painter paths going from source to target
        /// node. If the node has a label rectangle specified, the paths
        /// are placed in a way to accomodate for the rectangle.
        Vec<QPainterPath> paths;
        /// \brief Edge label rectangle
        Opt<QRect> labelRect;
        DESC_FIELDS(Edge, (paths, labelRect));
    };

    /// \brief Full layout result from the conversion
    struct Result {
        /// \brief Recursive subgraph layout. Nodes and edges inside of the
        /// subgraph are stored in a flat layout result.
        struct Subgraph {
            /// \brief Bounding box for the rectangle content
            QRect         bbox;
            Vec<Subgraph> subgraphs;

            /// \brief Get reference to subgraph specified at path
            Subgraph const& getSubgraph(Span<int> path) const {
                switch (path.size()) {
                    case 0: return *this;
                    case 1: return subgraphs.at(path.front());
                    default:
                        return subgraphs.at(path.front())
                            .getSubgraph(path.at(slice(1, 1_B)));
                }
            }
        };

        /// \brief Fixed node layout rectangles with absolute coordinates.
        /// Subgraph nodes are also included. Edge label nodes are not
        /// included.
        Vec<QRect> fixed;
        /// \brief Mapping from the source-target edge pair to the edge
        /// layout spec
        UnorderedMap<IrEdge, Edge> lines;
        /// \brief Bounding box for the whole rectangle
        QRect bbox;
        /// \brief Top-level list of subgraphs
        Vec<Subgraph> subgraphs;
        /// \brief Flattened list of subgraphs in DFS order with paths
        Vec<Vec<int>> subgraphPaths;

        /// \brief Get subgraph at path
        Subgraph const& getSubgraph(CVec<int> path) {
            switch (path.size()) {
                case 0:
                    throw std::invalid_argument(
                        "Expected at least 1 element in the subgraph "
                        "path, got 0");
                case 1: return subgraphs.at(path.front());
                default:
                    return subgraphs.at(path.front())
                        .getSubgraph(path.at(slice(1, 1_B)));
            }
        }
    };

    /// \brief Backend-specific layout results for graphviz graph
    struct GraphvizResult {
        Graphviz::Graph graph;
        Graphviz        gvc;
        int             graphviz_size_scaling;

        void writeSvg(CR<Str> path) const {
            gvc.writeFile(path, graph, Graphviz::RenderFormat::SVG);
        }

        void writeXDot(CR<Str> path) const {
            gvc.writeFile(path, graph, Graphviz::RenderFormat::XDOT);
        }

        Result convert();
    };

    GraphvizResult doGraphvizLayout(
        Graphviz             gvc,
        Graphviz::LayoutType layout = Graphviz::LayoutType::Dot);

    struct HolaResult {
        SPtr<dialect::Graph>                      graph;
        Vec<SPtr<dialect::Node>>                  nodes;
        UnorderedMap<IrEdge, SPtr<dialect::Edge>> edges;

        Result convert();
    };

    HolaResult doHolaLayout();

    /// \brief Backend-specific layout results for cola graph layout
    struct ColaResult {
        Vec<vpsc::Rectangle>  baseRectangles;
        Vec<vpsc::Rectangle*> rectPointers;

        struct EdgeData {
            IrEdge                     edge;
            Avoid::ShapeConnectionPin* sourcePin;
            Avoid::ShapeConnectionPin* targetPin;
            Avoid::ConnEnd             sourceEnd;
            Avoid::ConnEnd             targetEnd;
            Avoid::ConnRef*            connection;
            int                        sourcePinClassId;
            int                        targetPinClassId;
        };

        SPtr<Avoid::Router> router;
        Vec<EdgeData>       edges;

        Result convert();

        /// \brief write graph layout result into the SVG svg file
        void writeSvg(CR<Str> path) {
            auto e //
                = edges
                | rv::transform([](EdgeData const& e) -> Pair<uint, uint> {
                      return std::make_pair(
                          static_cast<uint>(e.edge.first),
                          static_cast<uint>(e.edge.second));
                  })
                | rs::to<std::vector>();
            OutputFile output(rectPointers, e, nullptr, path);
            output.rects = true;
            output.generate();
        }
    };

    ColaResult doColaLayout();
};


DECL_QDEBUG_FORMATTER(QPainterPath);
DECL_QDEBUG_FORMATTER(QRect);
DECL_QDEBUG_FORMATTER(QSize);

Q_DECLARE_REFL_METATYPE(GraphLayoutIR::Edge);
