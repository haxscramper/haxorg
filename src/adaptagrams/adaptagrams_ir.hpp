#pragma once


#include <variant>
#include <hstd/stdlib/Str.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/ext/graph/graph_graphviz.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/PairFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/MapFormatter.hpp>

#if false
namespace hstd::ext {



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


} // namespace hstd::ext


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

#    if ORG_BUILD_WITH_CGRAPH
    /// \brief Backend-specific layout results for graphviz graph
    struct GraphvizResult {
        Graphviz::Graph graph;
        Graphviz        gvc;
        int             graphviz_size_scaling;

        void writeSvg(fs::path const& path) const {
            gvc.writeFile(path, graph, Graphviz::RenderFormat::SVG);
        }

        void writeXDot(fs::path const& path) const {
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
#    endif

#    ifdef ORG_BUILD_WITH_ADAPTAGRAMS
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
        void writeSvg(Str const& path);

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
#    endif
};

} // namespace hstd::ext
#endif
