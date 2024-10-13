#include "block_graph.hpp"
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Ranges.hpp>

struct DocLayout {
    GraphLayoutIR              ir;
    UnorderedMap<DocNode, int> rectMap;
};

template <typename T>
struct JsonSerde<Slice<T>> {
    static T from_json(json const& j) {
        return slice<T>(
            JsonSerde<T>::from_json(j["first"]),
            JsonSerde<T>::from_json(j["last"]));
    }

    static json to_json(Slice<T> const& value) {
        return json::object({
            {"first", JsonSerde<T>::to_json(value.first)},
            {"last", JsonSerde<T>::to_json(value.last)},
        });
    }
};

GraphNodeConstraint::Align::Spec spec(int rect) {
    return GraphNodeConstraint::Align::Spec{.node = rect};
}

DocLayout to_layout(DocGraph const& g) {
    DocLayout lyt;

    Vec<GraphNodeConstraint::Align> laneAlignments;
    for (auto const& [lane_idx, lane] : enumerate(g.lanes)) {
        for (auto const& row : lane.visibleRange) {
            DocNode node{.lane = lane_idx, .row = row};
            lyt.ir.rectangles.push_back(GraphSize{
                .w = static_cast<double>(lane.blocks.at(row).width),
                .h = static_cast<double>(lane.blocks.at(row).height),
            });

            int idx = lyt.ir.rectangles.high();
            lyt.rectMap.insert_or_assign(node, idx);
        }

        GraphNodeConstraint::Align align;

        for (auto const& row : lane.visibleRange) {
            DocNode node{.lane = lane_idx, .row = row};
            align.nodes.push_back(GraphNodeConstraint::Align::Spec{
                .node = lyt.rectMap.at(node)});

            auto next_row = row + 1;
            if (lane.visibleRange.contains(next_row)) {
                DocNode next{.lane = lane_idx, .row = next_row};
                lyt.ir.nodeConstraints.push_back(
                    GraphNodeConstraint{GraphNodeConstraint::Separate{
                        .left  = {Vec{spec(lyt.rectMap.at(node))}},
                        .right = {Vec{spec(lyt.rectMap.at(next))}},
                        .separationDistance //
                        = float(
                              lane.blocks.at(row).height
                              + lane.blocks.at(next_row).height + 100)
                        / 2.0f,
                        .isExactSeparation = true,
                    }});
            }
        }

        align.dimension = GraphDimension::XDIM;
        laneAlignments.push_back(align);
    }

    for (auto const& [lane_idx, lane] : enumerate(g.lanes)) {
        if (lane_idx < g.lanes.high()) {
            int         next_idx = lane_idx + 1;
            auto const& next     = g.lanes.at(next_idx);

            float lane_width //
                = rs::max(
                    lane.blocks | rv::transform([](DocBlock const& b) {
                        return float(b.width);
                    }));

            float next_width //
                = rs::max(
                    next.blocks | rv::transform([](DocBlock const& b) {
                        return float(b.width);
                    }));

            lyt.ir.nodeConstraints.push_back(
                GraphNodeConstraint{GraphNodeConstraint::Separate{
                    .left  = laneAlignments.at(lane_idx),
                    .right = laneAlignments.at(next_idx),
                    .separationDistance //
                    = float(lane_width + next_width + 100) / 2.0f,
                    .isExactSeparation = true,
                }});
        }
    }

    for (auto const& lane : enumerator(g.lanes)) {
        for (auto const& row : lane.value().visibleRange) {
            DocNode source{.lane = lane.index(), .row = row};
            for (auto const& target : g.at(source).outEdges) {
                GraphEdge edge{
                    lyt.rectMap.at(source),
                    lyt.rectMap.at(target),
                };
                lyt.ir.edges.push_back(edge);
                lyt.ir.edgeConstraints.insert_or_assign(
                    edge,
                    GraphEdgeConstraint{
                        .sourcePort = GraphEdgeConstraint::Port::East,
                        .targetPort = GraphEdgeConstraint::Port::West,
                    });
            }
        }
    }

    return lyt;
}

DocNode n(int lane, int row) { return DocNode{.lane = lane, .row = row}; }

void run_block_graph_test() {
    auto lane0 = Vec<DocBlock>{
        // 0.0
        DocBlock{.width = 100, .height = 200, .outEdges = {n(1, 0)}},
        // 0.1
        DocBlock{
            .width    = 100,
            .height   = 250,
            .outEdges = {n(1, 1), n(1, 2), n(1, 3)}},
        // 0.2
        DocBlock{.width = 100, .height = 280, .outEdges = {n(1, 4)}},
    };

    auto lane1 = Vec<DocBlock>{
        // 1.0
        DocBlock{.width = 100, .height = 200, .outEdges = {n(2, 0)}},
        // 1.1
        DocBlock{
            .width = 100, .height = 250, .outEdges = {n(2, 0), n(2, 1)}},
        // 1.2
        DocBlock{.width = 100, .height = 280, .outEdges = {n(2, 1)}},
        // 1.3
        DocBlock{
            .width = 100, .height = 280, .outEdges = {n(2, 1), n(2, 2)}},
        // 1.4
        DocBlock{
            .width = 100, .height = 280, .outEdges = {n(2, 1), n(2, 3)}},
    };

    auto lane2 = Vec<DocBlock>{
        // 2.0
        DocBlock{.width = 100, .height = 200},
        // 2.1
        DocBlock{.width = 100, .height = 250},
        // 2.2
        DocBlock{.width = 100, .height = 280},
        // 2.3
        DocBlock{.width = 100, .height = 280},
    };

    DocGraph g{
        .lanes = {
            DocBlockStack{
                .blocks       = lane0,
                .visibleRange = slice(0, 2),
            },
            DocBlockStack{
                .blocks       = lane1,
                .visibleRange = slice(0, 4),
            },
            DocBlockStack{
                .blocks       = lane2,
                .visibleRange = slice(0, 3),
            },
        }};

    auto lyt = to_layout(g);
    auto col = lyt.ir.doColaLayout();
    writeFile("/tmp/run_block_graph_test.json", to_json_eval(g).dump(2));
    col.writeSvg("/tmp/run_block_graph_test.svg");
}
