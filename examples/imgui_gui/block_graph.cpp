#include "block_graph.hpp"
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>
#include <hstd/stdlib/Enumerate.hpp>

struct DocLayout {
    GraphLayoutIR              ir;
    UnorderedMap<DocNode, int> rectMap;
};

DocLayout to_layout(DocGraph const& g) {
    DocLayout lyt;

    for (auto const& lane : enumerator(g.lanes)) {
        for (auto const& row : lane.value().visibleRange) {
            DocNode node{.lane = lane.index(), .row = row};
            lyt.ir.rectangles.push_back(GraphSize{
                .w = static_cast<double>(
                    lane.value().blocks.at(row).width),
                .h = static_cast<double>(
                    lane.value().blocks.at(row).height),
            });

            int idx = lyt.ir.rectangles.high();
            lyt.rectMap.insert_or_assign(node, idx);
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
    col.writeSvg("/tmp/run_block_graph_test.svg");
}
