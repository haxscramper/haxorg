#pragma once

#include <hstd/stdlib/Vec.hpp>

struct DocBlock {
    int      width;
    int      height;
    Vec<int> outPortPositions;
    Vec<int> inPortPositions;

    DESC_FIELDS(
        DocBlock,
        (width, height, outPortPositions, inPortPositions));
};

struct DocBlockStack {
    Vec<DocBlock> blocks;
    Slice<int>    visibleRange;
};

void run_block_graph_test();
