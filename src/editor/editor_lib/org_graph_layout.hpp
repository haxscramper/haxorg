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
#include <editor/editor_lib/app_utils.hpp>
#include <QPainterPath>


/// \brief IR wrapper for the cola layout constraints
struct GraphConstraint {
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
        SPtr<cola::CompoundConstraint> toCola() const {
            auto result = std::make_shared<cola::AlignmentConstraint>(
                dimension);

            for (auto const& spec : nodes) {
                result->addShape(spec.node, spec.offset);
                if (spec.fixPos) { result->fixPos(*spec.fixPos); }
            }

            return result;
        }
    };

    SPtr<cola::CompoundConstraint> toCola() const {
        return std::visit(
            [](auto const& spec) { return spec.toCola(); }, data);
    }

    SUB_VARIANTS(Kind, Data, data, getKind, Align);
    Data data;

    GraphConstraint(CR<Data> data) : data(data){};
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

    struct Edge {
        Vec<QPainterPath> paths;
        Opt<QRect>        labelRect;
        DESC_FIELDS(Edge, (paths, labelRect));
    };

    struct Result {
        struct Subgraph {
            QRect         bbox;
            Vec<Subgraph> subgraphs;

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

        Vec<QRect>                 fixed;
        UnorderedMap<IrEdge, Edge> lines;
        QRect                      bbox;
        Vec<Subgraph>              subgraphs;
        Vec<Vec<int>>              subgraphPaths;

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

    /// Intermediate layout representation storage
    struct ColaResult {
        Vec<vpsc::Rectangle>          baseRectangles;
        Vec<vpsc::Rectangle*>         rectPointers;
        Vec<Pair<unsigned, unsigned>> edges;

        Result convert();

        void writeSvg(CR<Str> path) {
            OutputFile output(rectPointers, edges, nullptr, path);
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
