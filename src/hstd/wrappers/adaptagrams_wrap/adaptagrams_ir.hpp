#pragma once

#include <variant>
#include <hstd/stdlib/Str.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/wrappers/hstd_extra/graphviz.hpp>

#pragma warning(push, 0)
#include <libavoid/libavoid.h>
#include <libdialect/graphs.h>
#pragma warning(pop)

struct GraphPoint {
    int x;
    int y;
    GraphPoint() : x{0}, y{0} {}
    GraphPoint(int x, int y) : x{x}, y{y} {}
    DESC_FIELDS(GraphPoint, (x, y));
};

struct GraphPath {
    Vec<GraphPoint> points;
    Opt<GraphPoint> startPoint;
    Opt<GraphPoint> endPoint;
    bool            bezier;
    void point(int x, int y) { points.push_back(GraphPoint(x, y)); }
    void point(GraphPoint const& p) { points.push_back(p); }
    DESC_FIELDS(GraphPath, (points, startPoint, endPoint, bezier));
};

struct GraphSize {
    int w;
    int h;

    int  height() const { return h; }
    int  width() const { return w; }
    bool operator==(GraphSize const& other) const {
        return w == other.w && h == other.h;
    }
    DESC_FIELDS(GraphSize, (w, h));
};

struct GraphRect {
    int       left;
    int       top;
    int       width;
    int       height;
    GraphSize size() const { return GraphSize(width, height); }
    GraphRect() : left(0), top(0), width(-1), height(-1) {}
    GraphRect(int left, int top, int width, int height)
        : left{left}, top{top}, width{width}, height{height} {}

    void setBottomLeft(int x, int y) {
        width  = (width >= 0) ? width : left - x;
        height = (height >= 0) ? height : top - y;
        left   = x;
        top    = y - height;
    }

    void setTopRight(int x, int y) {
        width  = (width >= 0) ? width : x - left;
        height = (height >= 0) ? height : y - top;
        top    = y;
    }


    void setBottomLeft(GraphPoint const& p) { setBottomLeft(p.x, p.y); }
    void setTopRight(GraphPoint const& p) { setTopRight(p.x, p.y); }
    DESC_FIELDS(GraphRect, (left, top, width, height));
};


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
        Res toCola(std::vector<vpsc::Rectangle*> const& allRects) const;
    };

    struct PageBoundary {
        GraphRect rect;
        double    weight = 100.0;
        Res       toCola() const {
            return std::make_shared<cola::PageBoundaryConstraints>(
                rect.left,
                rect.left + rect.width,
                rect.top + rect.height,
                rect.top,
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

        bool isEmpty() const;
    };

    /// \brief Nodes for the graph. Node is identified by the index in the
    /// array of sizes. In the result value each original qsize is mapped
    /// to the rectangle.
    Vec<GraphSize> rectangles;
    /// \brief List of source-target pairs. Edge source/target IDs refer to
    /// the size rectangles.
    Vec<IrEdge> edges;
    /// \brief Cola constraints for graph layout. This part is
    /// backend-specific.
    Vec<GraphConstraint> constraints;
    Vec<Subgraph>        subgraphs;
    /// \brief If some edge has a dedicated label of specified size.
    UnorderedMap<IrEdge, GraphSize> edgeLabels;
    double                          width  = 100;
    double                          height = 100;
    /// \brief Graph name. Backend-specific.
    Str graphName = "G";

    /// \brief Which DPI to use when converting to and from graphviz sizes.
    /// Backend-specific, 72 is the default used by graphviz.
    int graphviz_size_scaling = 72;

    /// \brief validate the edge/rectangle structure for debugging. Throws
    /// assert failure if the structure is incorrect.
    void validate();

    /// \brief Graph edge layout
    struct Edge {
        /// \brief Sequence of painter paths going from source to target
        /// node. If the node has a label rectangle specified, the paths
        /// are placed in a way to accomodate for the rectangle.
        Vec<GraphPath> paths;
        /// \brief Edge label rectangle
        Opt<GraphRect> labelRect;
        DESC_FIELDS(Edge, (paths, labelRect));
    };

    /// \brief Full layout result from the conversion
    struct Result {
        /// \brief Recursive subgraph layout. Nodes and edges inside of the
        /// subgraph are stored in a flat layout result.
        struct Subgraph {
            /// \brief Bounding box for the rectangle content
            GraphRect     bbox;
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
        Vec<GraphRect> fixed;
        /// \brief Mapping from the source-target edge pair to the edge
        /// layout spec
        UnorderedMap<IrEdge, Edge> lines;
        /// \brief Bounding box for the whole rectangle
        GraphRect bbox;
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
        void writeSvg(CR<Str> path);
    };

    ColaResult doColaLayout();
};
