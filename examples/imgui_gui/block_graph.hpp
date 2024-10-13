#pragma once

#include <hstd/stdlib/Vec.hpp>

struct DocNode {
    int  lane;
    int  row;
    bool operator==(DocNode const& other) const {
        return lane == other.lane && row == other.row;
    }
    DESC_FIELDS(DocNode, (lane, row));
};

struct DocBlock {
    int          width;
    int          height;
    Vec<DocNode> outEdges;

    DESC_FIELDS(DocBlock, (width, height, outEdges));
};

struct DocBlockStack {
    Vec<DocBlock> blocks;
    Slice<int>    visibleRange;
    DESC_FIELDS(DocBlockStack, (blocks, visibleRange));
};

template <>
struct std::hash<DocNode> {
    std::size_t operator()(DocNode const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.lane);
        hax_hash_combine(result, it.row);
        return result;
    }
};


struct DocGraph {
    Vec<DocBlockStack> lanes;
    DESC_FIELDS(DocGraph, (lanes));

    DocBlock const& at(DocNode const& node) const {
        return lanes.at(node.lane).blocks.at(node.row);
    }
};

void run_block_graph_test();
