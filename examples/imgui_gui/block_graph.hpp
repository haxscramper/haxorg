#pragma once

#include <GLFW/glfw3.h>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>
#include "imgui.h"
#include <hstd/stdlib/Ranges.hpp>

struct DocNode {
    int  lane;
    int  row;
    bool operator==(DocNode const& other) const {
        return lane == other.lane && row == other.row;
    }
    DESC_FIELDS(DocNode, (lane, row));
};

struct DocOutEdge {
    DocNode                   target;
    Opt<int>                  heightOffset;
    GraphEdgeConstraint::Port targetPort = GraphEdgeConstraint::Port::East;
    GraphEdgeConstraint::Port sourcePort = GraphEdgeConstraint::Port::West;
    DESC_FIELDS(
        DocOutEdge,
        (target, heightOffset, targetPort, sourcePort));
};

struct DocBlock {
    int             width;
    int             height;
    Vec<DocOutEdge> outEdges;
    int             topMargin    = 5;
    int             bottomMargin = 5;

    /// \brief Get full vertical space occupied by the doc block, including
    /// top and bottom margins.
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
    int  getBlockHeightStart(int blockIdx) const;
    void resetVisibleRange() { visibleRange = slice(0, blocks.high()); }
    bool inSpan(int blockIdx, Slice<int> heightRange) const;
    Slice<int> getVisibleBlocks(Slice<int> heightRange) const;
    int        addBlock(ImVec2 const& size) {
        blocks.push_back(DocBlock{
                   .width  = static_cast<int>(size.x),
                   .height = static_cast<int>(size.y),
        });
        return blocks.high();
    }

    int getWidth() const {
        return rs::max(blocks | rv::transform([](DocBlock const& b) {
                           return float(b.width);
                       }));
    }

    int getFullWidth() const {
        return getWidth() + leftMargin + rightMargin;
    }

    void addEdge(int row, DocOutEdge const& target) {
        return blocks.at(row).outEdges.push_back(target);
    }
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
    DocNode addNode(int lane, ImVec2 const& size) {
        return DocNode{
            .lane = lane,
            .row  = this->lane(lane).addBlock(size),
        };
    }

    void addEdge(DocNode const& source, DocOutEdge const& target) {
        return lane(source.lane).addEdge(source.row, target);
    }

    DocBlockStack& lane(int lane) { return lanes.resize_at(lane); }

    DocBlock& at(DocNode const& node) {
        return lanes.at(node.lane).blocks.at(node.row);
    }

    DocBlock const& at(DocNode const& node) const {
        return lanes.at(node.lane).blocks.at(node.row);
    }
};


struct DocLayout {
    GraphLayoutIR              ir;
    UnorderedMap<DocNode, int> rectMap;
    DESC_FIELDS(DocLayout, (ir, rectMap));
};

struct DocConstraintDebug {
    struct Constraint {
        struct Align {
            ImVec2 start;
            ImVec2 end;
            DESC_FIELDS(Align, (start, end));
        };

        SUB_VARIANTS(Kind, Data, data, getKind, Align);
        Data data;
        DESC_FIELDS(Constraint, (data));
    };

    GraphLayoutIR::Result const* ir;
    Vec<Constraint>              constraints;
    DESC_FIELDS(DocConstraintDebug, (constraints));
};

DocConstraintDebug to_constraints(
    DocLayout const&             lyt,
    DocGraph const&              g,
    const GraphLayoutIR::Result& final);

void render_point(const GraphPoint& point, ImVec2 const& shift);
void render_path(const GraphPath& path, ImVec2 const& shift);
void render_path(const GraphPath& path, ImVec2 const& shift);
void render_rect(const GraphRect& rect, ImVec2 const& shift);
void render_edge(const GraphLayoutIR::Edge& edge, ImVec2 const& shift);
void render_result(GraphLayoutIR::Result const& res, ImVec2 const& shift);
void render_debug(DocConstraintDebug const& debug, const ImVec2& shift);

DocLayout to_layout(DocGraph const& g);
void      run_block_graph_test(GLFWwindow* window);
