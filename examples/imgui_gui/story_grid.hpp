#pragma once
// immer templates are instantiated in the haxorg library without debug
// checks, but building imgui application in debug mode causes a new series
// of instantiations and overwrites the symbols with debug enabled, causing
// constant assertion failures.
#include "block_graph.hpp"
#define NDEBUG 0

#include <GLFW/glfw3.h>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include "imgui.h"
#include <haxorg/sem/ImmOrgGraph.hpp>
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>

struct TreeGridCell {
    struct None {
        DESC_FIELDS(None, ());
    };
    struct Value {
        std::string     value       = std::string{};
        org::ImmAdapter origin      = org::ImmAdapter{};
        bool            is_editing  = false;
        std::string     edit_buffer = std::string{};
        DESC_FIELDS(Value, (value, origin, is_editing, edit_buffer));
    };

    SUB_VARIANTS(Kind, Data, data, getKind, None, Value);
    Data data;
    int  height;
    int  width;
    DESC_FIELDS(TreeGridCell, (height, width, data));
};

struct TreeGridColumn {
    std::string name;
    int         width = 120;
    DECL_DESCRIBED_ENUM(EditMode, Multiline, SingleLine);
    EditMode edit = EditMode::Multiline;
    DESC_FIELDS(TreeGridColumn, (name, width, edit));
};

struct TreeGridRow {
    int                               flatIdx;
    org::ImmAdapterT<org::ImmSubtree> origin;
    UnorderedMap<Str, TreeGridCell>   columns;
    Vec<TreeGridRow>                  nested;
    DESC_FIELDS(TreeGridRow, (columns, origin, flatIdx, nested));

    Vec<TreeGridRow*> flatThisNested() {
        Vec<TreeGridRow*> result;
        result.push_back(this);
        for (auto& sub : nested) { result.append(sub.flatThisNested()); }

        return result;
    }

    int getHeight(int padding = 0) const;

    int getHeightRec(int padding = 0) const;
};

struct TreeGridDocument {
    Vec<TreeGridRow>    rows;
    Vec<int>            rowPositions;
    Vec<TreeGridColumn> columns;

    UnorderedMap<org::ImmUniqId, int> rowOrigins;


    TreeGridColumn& getColumn(CR<Str> name) {
        auto iter = rs::find_if(
            columns, [&](TreeGridColumn const& col) -> bool {
                return col.name == name;
            });
        if (iter == columns.end()) {
            columns.push_back(TreeGridColumn{.name = name});
            return columns.back();
        } else {
            return *iter;
        }
    }

    Vec<TreeGridRow*> flatRows() {
        Vec<TreeGridRow*> result;
        for (auto& row : rows) { result.append(row.flatThisNested()); }
        return result;
    }

    TreeGridRow* getRow(int pos) {
        // TODO Optimize, this is a O(n^2) code.
        for (auto it : flatRows()) {
            if (it->flatIdx == pos) { return it; }
        }
        return nullptr;
    }

    TreeGridRow const* getRow(int pos) const {
        // TODO Optimize, this is a O(n^2) code.
        for (auto it : const_cast<TreeGridDocument*>(this)->flatRows()) {
            if (it->flatIdx == pos) { return it; }
        }
        return nullptr;
    }


    Opt<int> getRow(org::ImmUniqId const& id) const {
        return rowOrigins.get(id);
    }

    int getNodeOffset(org::ImmUniqId const& id) const {
        return rowPositions.at(rowOrigins.at(id));
    }

    int getHeight(int padding = 0) const {
        int res = 0;
        for (auto const& row : rows) { res += row.getHeightRec(padding); }
        return res;
    }

    int getWidth(int padding = 0) const {
        int tableWidth = 0;
        for (auto const& col : columns) {
            tableWidth += col.width + padding;
        }
        return tableWidth;
    }

    int getRowCenterOffset(int rowIdx) const {
        return float(rowPositions.at(rowIdx))
             + float(getRow(rowIdx)->getHeight()) / 2;
    }

    DESC_FIELDS(TreeGridDocument, (rows, rowPositions, columns));
};

struct StoryGridNode {
    struct TreeGrid {
        ImVec2           pos;
        ImVec2           size;
        TreeGridDocument node;
        DESC_FIELDS(TreeGrid, (node, pos, size));
    };

    struct LinkList {
        struct Item {
            std::string     text;
            int             width;
            int             height;
            org::ImmAdapter node;
            DESC_FIELDS(Item, (text, width, height, node));
        };
        Vec<Item> items;
        ImVec2    pos;
        ImVec2    size;
        DESC_FIELDS(LinkList, (items, pos, size));

        int getRowOffset(org::ImmUniqId const& row) const {
            auto iter = rs::find_if(items, [&](Item const& i) {
                return i.node.uniq() == row;
            });
            LOGIC_ASSERTION_CHECK(iter != items.end(), "{}", row);
            return getRowOffset(std::distance(items.begin(), iter));
        }

        int getRowOffset(int row) const {
            int offset = 0;
            for (auto const& [row_idx, item] : enumerate(items)) {
                if (row_idx < row) { offset += item.height; }
            }
            return offset;
        }

        int getHeight(int rowPadding) const {
            int result = 0;
            for (auto const& item : items) {
                result += rowPadding + item.height;
            }
            return result;
        }

        int getWidth() const {
            return rs::max(items | rv::transform([&](Item const& col) {
                               return col.width;
                           }));
        }
    };

    struct Text {
        ImVec2          pos;
        ImVec2          size;
        org::ImmAdapter node;
        std::string     text;
        DESC_FIELDS(Text, (node, pos, size));
    };


    SUB_VARIANTS(Kind, Data, data, getKind, TreeGrid, Text, LinkList);
    Data data;
    bool isVisible = true;
    DESC_FIELDS(StoryGridNode, (data, isVisible));
};

struct StoryGridGraph {
    Vec<StoryGridNode>             nodes;
    LaneBlockGraph                 ir;
    UnorderedMap<int, LaneNodePos> gridNodeToNode;
    UnorderedMap<LaneNodePos, int> nodeToGridNode;
    org::graph::MapGraph           graph;

    UnorderedMap<org::ImmUniqId, org::ImmUniqId> annotationParents;
    UnorderedMap<org::ImmUniqId, LaneNodePos>    orgToId;

    DESC_FIELDS(
        StoryGridGraph,
        (nodes, ir, gridNodeToNode, nodeToGridNode));

    void addIrNode(int flatIdx, LaneNodePos const& irNode) {
        gridNodeToNode.insert_or_assign(flatIdx, irNode);
        nodeToGridNode.insert_or_assign(irNode, flatIdx);
    }

    StoryGridNode const& getDocNode(int idx) const {
        return nodes.at(idx);
    }

    StoryGridNode const& getDocNode(LaneNodePos const& idx) const {
        return getDocNode(getFlatIdx(idx));
    }

    LaneNodePos const& getIrNode(int idx) const {
        return gridNodeToNode.at(idx);
    }

    int const& getFlatIdx(LaneNodePos const& node) const {
        return nodeToGridNode.at(node);
    }

    int addNode(int lane, ImVec2 const& size, StoryGridNode const& node) {
        nodes.push_back(node);
        auto rootRect = ir.addNode(0, size);
        addIrNode(nodes.high(), rootRect);
        return nodes.high();
    }
};

struct StoryGridContext
    : OperationsTracer
    , OperationsScope {

    DESC_FIELDS(StoryGridContext, ());

    void message(
        std::string const& value,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE()) const;
};

struct GridAction {
    struct EditCell {
        TreeGridCell cell;
        std::string  updated;
        DESC_FIELDS(EditCell, (cell, updated));
    };

    struct Scroll {
        ImVec2 pos;
        float  direction;
        DESC_FIELDS(Scroll, (pos, direction));
    };

    SUB_VARIANTS(Kind, Data, data, getKind, EditCell, Scroll);
    Data data;
    DESC_FIELDS(GridAction, (data));
};

struct StoryGridState {
    org::ImmAstVersion ast;
};


struct StoryGridModel {
    DECL_DESCRIBED_ENUM(UpdateNeeded, Scroll, Graph);
    Vec<StoryGridState>        history;
    StoryGridGraph             rectGraph;
    StoryGridContext           conf;
    GraphLayoutIR::Result      layout;
    ImVec2                     shift{20, 20};
    Opt<ColaConstraintDebug>   debug;
    void                       updateDocument();
    Vec<Slice<int>>            laneSpans;
    Vec<float>                 laneOffsets;
    StoryGridState&            getCurrentState() { return history.back(); }
    void                       apply(GridAction const& act);
    UnorderedSet<UpdateNeeded> updateNeeded;
};


void story_grid_loop(GLFWwindow* window, std::string const& file);
