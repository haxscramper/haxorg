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

struct [[refl]] GraphPoint {
    [[refl]] int x;
    [[refl]] int y;
    GraphPoint() : x{0}, y{0} {}
    GraphPoint(int x, int y) : x{x}, y{y} {}
    DESC_FIELDS(GraphPoint, (x, y));
};

struct [[refl]] GraphPath {
    [[refl]] Vec<GraphPoint> points;
    [[refl]] Opt<GraphPoint> startPoint;
    [[refl]] Opt<GraphPoint> endPoint;
    [[refl]] bool            bezier;
    [[refl]] void            point(int x, int y) {
        points.push_back(GraphPoint(x, y));
    }
    [[refl]] void point(GraphPoint const& p) { points.push_back(p); }
    DESC_FIELDS(GraphPath, (points, startPoint, endPoint, bezier));
};

struct [[refl]] GraphSize {
    [[refl]] int w;
    [[refl]] int h;

    [[refl]] int height() const { return h; }
    [[refl]] int width() const { return w; }

    bool operator==(GraphSize const& other) const {
        return w == other.w && h == other.h;
    }
    DESC_FIELDS(GraphSize, (w, h));
};

struct [[refl]] GraphRect {
    [[refl]] int       left;
    [[refl]] int       top;
    [[refl]] int       width;
    [[refl]] int       height;
    [[refl]] GraphSize size() const { return GraphSize(width, height); }
    GraphRect() : left(0), top(0), width(-1), height(-1) {}
    GraphRect(int left, int top, int width, int height)
        : left{left}, top{top}, width{width}, height{height} {}

    [[refl]] void setBottomLeft(int x, int y) {
        width  = (width >= 0) ? width : left - x;
        height = (height >= 0) ? height : top - y;
        left   = x;
        top    = y - height;
    }

    [[refl]] void setTopRight(int x, int y) {
        width  = (width >= 0) ? width : x - left;
        height = (height >= 0) ? height : y - top;
        top    = y;
    }


    [[refl]] void setBottomLeft(GraphPoint const& p) {
        setBottomLeft(p.x, p.y);
    }
    [[refl]] void setTopRight(GraphPoint const& p) {
        setTopRight(p.x, p.y);
    }
    DESC_FIELDS(GraphRect, (left, top, width, height));
};


/// \brief IR wrapper for the cola layout constraints
struct [[refl]] GraphConstraint {
    using Res = SPtr<cola::CompoundConstraint>;

    /// \brief Listed nodes must be positioned on the same X/Y dimension in
    /// the layout
    struct [[refl]] Align {
        struct [[refl]] Spec {
            [[refl]] int         node; ///< Rectangle index
            [[refl]] Opt<double> fixPos = std::nullopt; ///< ??? wtf
            [[refl]] double      offset = 0.0; ///< Offset from the axis
        };

        [[refl]] Vec<Spec> nodes;
        [[refl]] vpsc::Dim dimension; ///< Which axist to align on
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

    struct [[refl]] Separate {
        [[refl]] Align     left;
        [[refl]] Align     right;
        [[refl]] double    separationDistance = 1.0;
        [[refl]] bool      isExactSeparation  = false;
        [[refl]] vpsc::Dim dimension; ///< Which axis to partition nodes
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

    struct [[refl]] MultiSeparate {
        [[refl]] Vec<Align>          lines;
        [[refl]] Vec<Pair<int, int>> alignPairs;
        [[refl]] vpsc::Dim           dimension;
        [[refl]] double              separationDistance;
        [[refl]] bool                isExactSeparation;

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

    struct [[refl]] FixedRelative {
        [[refl]] Vec<int> nodes;
        [[refl]] bool     fixedPosition = false;
        Res toCola(std::vector<vpsc::Rectangle*> const& allRects) const;
    };

    struct [[refl]] PageBoundary {
        [[refl]] GraphRect rect;
        [[refl]] double    weight = 100.0;
        Res                toCola() const {
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
struct [[refl]] GraphLayoutIR {
    struct [[refl]] IrEdge {
        [[refl]] int source;
        [[refl]] int target;
    };

    struct [[refl]] Subgraph {
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
    [[refl]] Vec<GraphSize> rectangles;
    /// \brief List of source-target pairs. Edge source/target IDs refer to
    /// the size rectangles.
    [[refl]] Vec<IrEdge> edges;
    /// \brief Cola constraints for graph layout. This part is
    /// backend-specific.
    [[refl]] Vec<GraphConstraint> constraints;
    [[refl]] Vec<Subgraph>        subgraphs;
    /// \brief If some edge has a dedicated label of specified size.
    [[refl]] UnorderedMap<IrEdge, GraphSize> edgeLabels;
    [[refl]] double                          width  = 100;
    [[refl]] double                          height = 100;
    /// \brief Graph name. Backend-specific.
    [[refl]] Str graphName = "G";

    /// \brief Which DPI to use when converting to and from graphviz sizes.
    /// Backend-specific, 72 is the default used by graphviz.
    [[refl]] int graphviz_size_scaling = 72;

    /// \brief validate the edge/rectangle structure for debugging. Throws
    /// assert failure if the structure is incorrect.
    [[refl]] void validate();

    /// \brief Graph edge layout
    struct [[refl]] Edge {
        /// \brief Sequence of painter paths going from source to target
        /// node. If the node has a label rectangle specified, the paths
        /// are placed in a way to accomodate for the rectangle.
        Vec<GraphPath> paths;
        /// \brief Edge label rectangle
        Opt<GraphRect> labelRect;
        DESC_FIELDS(Edge, (paths, labelRect));
    };

    /// \brief Full layout result from the conversion
    struct [[refl]] Result {
        /// \brief Recursive subgraph layout. Nodes and edges inside of the
        /// subgraph are stored in a flat layout result.
        struct [[refl]] Subgraph {
            /// \brief Bounding box for the rectangle content
            [[refl]] GraphRect     bbox;
            [[refl]] Vec<Subgraph> subgraphs;

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
        [[refl]] Vec<GraphRect> fixed;
        /// \brief Mapping from the source-target edge pair to the edge
        /// layout spec
        [[refl]] UnorderedMap<IrEdge, Edge> lines;
        /// \brief Bounding box for the whole rectangle
        [[refl]] GraphRect bbox;
        /// \brief Top-level list of subgraphs
        [[refl]] Vec<Subgraph> subgraphs;
        /// \brief Flattened list of subgraphs in DFS order with paths
        [[refl]] Vec<Vec<int>> subgraphPaths;

        /// \brief Get subgraph at path
        [[refl]] Subgraph const& getSubgraph(CVec<int> path) {
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

    HolaResult      doHolaLayout();
    [[refl]] Result doHolaConvert() { return doHolaLayout().convert(); }

    /// \brief Backend-specific layout results for cola graph layout
    struct [[refl]] ColaResult {
        Vec<vpsc::Rectangle>  baseRectangles;
        Vec<vpsc::Rectangle*> rectPointers;

        struct [[refl]] EdgeData {
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

    ColaResult      doColaLayout();
    [[refl]] Result doColaConvert() { return doColaLayout().convert(); }
};
