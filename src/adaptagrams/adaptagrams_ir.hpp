#pragma once

#include <variant>
#include <hstd/stdlib/Str.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/ext/graphviz.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/PairFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>

#ifdef ORG_DEPS_USE_ADAPTAGRAMS
#    pragma warning(push, 0)
#    include <libavoid/libavoid.h>
#    include <libdialect/graphs.h>
#    pragma warning(pop)
#endif
#pragma clang diagnostic ignored "-Wunknown-attributes"

namespace hstd::ext {

enum class [[refl]] GraphDimension
{
    XDIM  = 0,
    YDIM  = 1,
    UNSET = 2,
};

BOOST_DESCRIBE_ENUM(GraphDimension, XDIM, YDIM, UNSET)

struct [[refl]] GraphPoint {
    [[refl]] double x;
    [[refl]] double y;
    GraphPoint() : x{0}, y{0} {}
    GraphPoint(double x, double y) : x{x}, y{y} {}
    DESC_FIELDS(GraphPoint, (x, y));
};

struct [[refl]] GraphPath {
    [[refl]] Vec<GraphPoint> points;
    [[refl]] Opt<GraphPoint> startPoint;
    [[refl]] Opt<GraphPoint> endPoint;
    [[refl]] bool            bezier;
    [[refl]] void            point(double x, double y) {
        points.push_back(GraphPoint(x, y));
    }
    [[refl]] void point(GraphPoint const& p) { points.push_back(p); }
    DESC_FIELDS(GraphPath, (points, startPoint, endPoint, bezier));
};

struct [[refl]] GraphSize {
    [[refl]] double w;
    [[refl]] double h;

    [[refl]] double height() const { return h; }
    [[refl]] double width() const { return w; }

    bool operator==(GraphSize const& other) const {
        return w == other.w && h == other.h;
    }
    DESC_FIELDS(GraphSize, (w, h));
};

struct [[refl]] GraphRect {
    [[refl]] double    left;
    [[refl]] double    top;
    [[refl]] double    width;
    [[refl]] double    height;
    [[refl]] GraphSize size() const { return GraphSize(width, height); }
    GraphRect() : left(0), top(0), width(-1), height(-1) {}
    GraphRect(double left, double top, double width, double height)
        : left{left}, top{top}, width{width}, height{height} {}

    DESC_FIELDS(GraphRect, (left, top, width, height));

    GraphPoint topLeft() const { return GraphPoint{left, top}; }
    GraphPoint bottomRight() const {
        return GraphPoint{left + width, top + height};
    }

    bool contains(GraphPoint const& p) const {
        return (left <= p.x && p.x <= (left + width))
            && (top <= p.y && p.y <= (top + height));
    }

    void extend(GraphPoint const& point);
};

/// \brief IR wrapper for the cola layout constraints
struct [[refl]] GraphNodeConstraint {
#ifdef ORG_DEPS_USE_ADAPTAGRAMS
    using Res = SPtr<cola::CompoundConstraint>;

    struct [[refl]] Empty {
        DESC_FIELDS(Empty, ());
    };

    /// \brief Listed nodes must be positioned on the same X/Y dimension in
    /// the layout
    struct [[refl]] Align {
        struct [[refl]] Spec {
            [[refl]] int         node; ///< Rectangle index
            [[refl]] Opt<double> fixPos = std::nullopt; ///< ??? wtf
            [[refl]] double      offset = 0.0; ///< Offset from the axis
            DESC_FIELDS(Spec, (node, fixPos, offset));
        };

        [[refl]] Vec<Spec>      nodes;
        [[refl]] GraphDimension dimension; ///< Which axist to align on
        DESC_FIELDS(Align, (nodes, dimension));

        /// \brief Map to cola layout constraint object
        Res                  toCola() const;
        [[refl]] std::string toColaString() const {
            return toCola()->toString();
        }
    };

    struct [[refl]] Separate {
        [[refl]] Align          left;
        [[refl]] Align          right;
        [[refl]] double         separationDistance = 1.0;
        [[refl]] bool           isExactSeparation  = false;
        [[refl]] GraphDimension dimension; ///< Which axis to partition
                                           ///< nodes
        DESC_FIELDS(
            Separate,
            (left,
             right,
             separationDistance,
             isExactSeparation,
             dimension));

        Vec<Res>             toCola() const;
        [[refl]] std::string toColaString() const;
    };

    struct [[refl]] MultiSeparate {
        [[refl]] Vec<Align>          lines;
        [[refl]] Vec<Pair<int, int>> alignPairs;
        [[refl]] GraphDimension      dimension;
        [[refl]] double              separationDistance;
        [[refl]] bool                isExactSeparation;

        DESC_FIELDS(
            MultiSeparate,
            (lines,
             alignPairs,
             dimension,
             separationDistance,
             isExactSeparation));

        Vec<Res>             toCola() const;
        [[refl]] std::string toColaString() const;
    };

    struct [[refl]] FixedRelative {
        [[refl]] Vec<int> nodes;
        [[refl]] bool     fixedPosition = false;
        DESC_FIELDS(FixedRelative, (nodes, fixedPosition));
        Res toCola(std::vector<vpsc::Rectangle*> const& allRects) const;
    };

    struct [[refl]] PageBoundary {
        [[refl]] GraphRect rect;
        [[refl]] double    weight = 100.0;
        [[refl]] Vec<int>  nodes;
        DESC_FIELDS(PageBoundary, (rect, weight, nodes));

        Res toCola(std::vector<vpsc::Rectangle*> const& allRects) const;
        [[refl]] std::string toColaString(
            std::vector<vpsc::Rectangle*> const& allRects) const {
            return toCola(allRects)->toString();
        }
    };

    Vec<Res> toCola(std::vector<vpsc::Rectangle*> const& allRects) const;
    std::string toColaString(
        std::vector<vpsc::Rectangle*> const& allRects) const;

    SUB_VARIANTS_REFL(
        Kind,
        Data,
        data,
        getKind,
        Empty,
        Align,
        FixedRelative,
        Separate,
        MultiSeparate,
        PageBoundary);

    Data data;

    GraphNodeConstraint() {}
    GraphNodeConstraint(CR<Data> data) : data(data) {};

    [[refl]] static GraphNodeConstraint InitEmpty(Empty const& arg) {
        return GraphNodeConstraint(arg);
    }

    [[refl]] static GraphNodeConstraint InitAlign(Align const& arg) {
        return GraphNodeConstraint(arg);
    }

    [[refl]] static GraphNodeConstraint InitSeparate(Separate const& arg) {
        return GraphNodeConstraint(arg);
    }

    [[refl]] static GraphNodeConstraint InitMultiSeparate(
        MultiSeparate const& arg) {
        return GraphNodeConstraint(arg);
    }

    [[refl]] static GraphNodeConstraint InitFixedRelative(
        FixedRelative const& arg) {
        return GraphNodeConstraint(arg);
    }

    [[refl]] static GraphNodeConstraint InitPageBoundary(
        PageBoundary const& arg) {
        return GraphNodeConstraint(arg);
    }


    DESC_FIELDS(GraphNodeConstraint, (data));
#endif
};

struct [[refl]] GraphEdge {
    [[refl]] int source;
    [[refl]] int target;
    [[refl]] int bundle = 0;

    bool operator==(GraphEdge const& other) const {
        return source == other.source //
            && target == other.target //
            && bundle == other.bundle;
    }

    DESC_FIELDS(GraphEdge, (source, target, bundle));
};

} // namespace hstd::ext

template <>
struct std::hash<::hstd::ext::GraphEdge> {
    std::size_t operator()(
        ::hstd::ext::GraphEdge const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.source);
        hstd::hax_hash_combine(result, it.target);
        hstd::hax_hash_combine(result, it.bundle);
        return result;
    }
};


namespace hstd::ext {


struct [[refl]] GraphEdgeConstraint {
    enum class [[refl]] Port
    {
        Default,
        North,
        South,
        West,
        East,
        Center,
    };

    BOOST_DESCRIBE_NESTED_ENUM(
        Port,
        Default,
        North,
        South,
        West,
        East,
        Center);

    [[refl]] Port sourcePort;
    [[refl]] Port targetPort;
    /// \brief Offset the port position on the side of the shape. Value in
    /// range [0, 1] used as a relative position along the edge of the
    /// shape. For vertical edges (west/east) the port movement would be
    /// vertical, and for horizontal (north/south) it would be horizontal.
    /// If the value is not provided the nodes are placed in the center
    /// with the ratio computed automatically.
    [[refl]] Opt<double> sourceOffset     = std::nullopt;
    [[refl]] Opt<double> targetOffset     = std::nullopt;
    [[refl]] Opt<double> sourceCheckpoint = 10.0;
    [[refl]] Opt<double> targetCheckpoint = 10.0;

    DESC_FIELDS(
        GraphEdgeConstraint,
        (sourcePort,
         targetPort,
         sourceOffset,
         targetOffset,
         sourceCheckpoint,
         targetCheckpoint));
};


/// \brief Main store for the graph layout intermediate representation.
/// Stores a minimum amount of information about the graph properties --
/// list of edges, shapes of nodes, and some backend-specific parameters.
struct [[refl]] GraphLayoutIR {


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
        Opt<double> internalMargin;

        DESC_FIELDS(
            Subgraph,
            (graphName, nodes, subgraphs, internalMargin));

        bool isEmpty() const;
    };

    /// \brief Nodes for the graph. Node is identified by the index in the
    /// array of sizes. In the result value each original qsize is mapped
    /// to the rectangle.
    [[refl]] Vec<GraphSize> rectangles;
    /// \brief List of source-target pairs. Edge source/target IDs refer to
    /// the size rectangles.
    [[refl]] Vec<GraphEdge> edges;
    /// \brief Cola nodeConstraints for graph layout. This part is
    /// backend-specific.
    [[refl]] Vec<GraphNodeConstraint> nodeConstraints;
    [[refl]] Vec<Subgraph>            subgraphs;
    /// \brief If some edge has a dedicated label of specified size.
    [[refl]] UnorderedMap<GraphEdge, GraphSize>           edgeLabels = {};
    [[refl]] UnorderedMap<GraphEdge, GraphEdgeConstraint> edgeConstraints;

    [[refl]] double width            = 100;
    [[refl]] double height           = 100;
    [[refl]] double leftBBoxMargin   = 0.0;
    [[refl]] double rightBBoxMargin  = 0.0;
    [[refl]] double topBBoxMargin    = 0.0;
    [[refl]] double bottomBBoxMargin = 0.0;
    /// \brief Graph name. Backend-specific.
    [[refl]] Str graphName = "G";

    DESC_FIELDS(
        GraphLayoutIR,
        (rectangles,
         edges,
         nodeConstraints,
         subgraphs,
         edgeLabels,
         edgeConstraints,
         width,
         height,
         leftBBoxMargin,
         rightBBoxMargin,
         topBBoxMargin,
         bottomBBoxMargin,
         graphName,
         graphviz_size_scaling));

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
        [[refl]] Vec<GraphPath> paths;
        /// \brief Edge label rectangle
        [[refl]] Opt<GraphRect> labelRect;
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

            DESC_FIELDS(Subgraph, (bbox, subgraphs));

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
        [[refl]] UnorderedMap<GraphEdge, Edge> lines;
        /// \brief Bounding box for the whole rectangle
        [[refl]] GraphRect bbox;
        /// \brief Top-level list of subgraphs
        [[refl]] Vec<Subgraph> subgraphs;
        /// \brief Flattened list of subgraphs in DFS order with paths
        [[refl]] Vec<Vec<int>> subgraphPaths;

        DESC_FIELDS(
            Result,
            (fixed, lines, bbox, subgraphs, subgraphPaths));

        /// \brief Get subgraph at path
        Subgraph const& getSubgraph(Vec<int> const& path) {
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

        void writeSvg(CR<fs::path> path) const {
            gvc.writeFile(path, graph, Graphviz::RenderFormat::SVG);
        }

        void writeXDot(CR<fs::path> path) const {
            gvc.writeFile(path, graph, Graphviz::RenderFormat::XDOT);
        }

        Result convert();
    };

    GraphvizResult doGraphvizLayout(
        Graphviz             gvc,
        Graphviz::LayoutType layout = Graphviz::LayoutType::Dot);

    [[refl]] Result doGraphvizConvert() {
        Graphviz gvc;
        return doGraphvizLayout(gvc).convert();
    }

#ifdef ORG_DEPS_USE_ADAPTAGRAMS
    struct HolaResult {
        SPtr<dialect::Graph>                         graph;
        Vec<SPtr<dialect::Node>>                     nodes;
        UnorderedMap<GraphEdge, SPtr<dialect::Edge>> edges;

        Result convert();
    };

    HolaResult      doHolaLayout();
    [[refl]] Result doHolaConvert() { return doHolaLayout().convert(); }

    /// \brief Backend-specific layout results for cola graph layout
    struct ColaResult {
        GraphLayoutIR*        baseIr;
        Vec<vpsc::Rectangle>  baseRectangles;
        Vec<vpsc::Rectangle*> rectPointers;

        struct EdgeData {
            GraphEdge                  edge;
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

        Vec<SPtr<cola::CompoundConstraint>> setupConstraints(
            Vec<GraphSize> const&           rectangles,
            Vec<GraphNodeConstraint> const& constraints);
    };

    ColaResult      doColaLayout();
    [[refl]] Result doColaConvert() { return doColaLayout().convert(); }
    [[refl]] void   doColaSvgWrite(std::string const& path) {
        doColaLayout().writeSvg(path);
    }

    [[refl]] std::string doColaStrFormat();
#endif
};

} // namespace hstd::ext
