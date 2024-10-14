#pragma once

#include <GLFW/glfw3.h>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>

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
    int          topMargin    = 5;
    int          bottomMargin = 5;

    int fullHeight() const { return height + topMargin + bottomMargin; }

    Slice<int> heightSpan(int start) const {
        return slice(start, start + fullHeight());
    }

    DESC_FIELDS(
        DocBlock,
        (width, height, outEdges, topMargin, bottomMargin));
};

struct DocBlockStack {
    Vec<DocBlock> blocks;
    int           scrollOffset;
    Slice<int>    visibleRange;
    int           leftMargin  = 50;
    int           rightMargin = 50;
    DESC_FIELDS(
        DocBlockStack,
        (blocks, visibleRange, scrollOffset, leftMargin, rightMargin));
    int        getBlockHeightStart(int blockIdx) const;
    bool       inSpan(int blockIdx, Slice<int> heightRange) const;
    Slice<int> getVisibleBlocks(Slice<int> heightRange) const;
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
    GraphSize          visible;
    DESC_FIELDS(DocGraph, (lanes, visible));

    DocBlock const& at(DocNode const& node) const {
        return lanes.at(node.lane).blocks.at(node.row);
    }
};

void run_block_graph_test(GLFWwindow* window);
