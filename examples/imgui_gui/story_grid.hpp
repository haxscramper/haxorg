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

struct GridCell {
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
    DESC_FIELDS(GridCell, (height, width, data));
};

struct GridColumn {
    std::string name;
    int         width = 120;
    DECL_DESCRIBED_ENUM(EditMode, Multiline, SingleLine);
    EditMode edit = EditMode::Multiline;
    DESC_FIELDS(GridColumn, (name, width, edit));
};

struct GridRow {
    int                               flatIdx;
    org::ImmAdapterT<org::ImmSubtree> origin;
    UnorderedMap<Str, GridCell>       columns;
    Vec<GridRow>                      nested;
    DESC_FIELDS(GridRow, (columns, origin, flatIdx, nested));

    Vec<GridRow*> flatThisNested() {
        Vec<GridRow*> result;
        result.push_back(this);
        for (auto& sub : nested) { result.append(sub.flatThisNested()); }

        return result;
    }

    int getHeight(int padding = 0) const;

    int getHeightRec(int padding = 0) const;
};

struct DocumentGrid {
    Vec<GridRow>    rows;
    Vec<int>        rowPositions;
    Vec<GridColumn> columns;

    UnorderedMap<org::ImmUniqId, int>            rowOrigins;
    UnorderedMap<org::ImmUniqId, org::ImmUniqId> annotationParents;

    GridColumn& getColumn(CR<Str> name) {
        auto iter = rs::find_if(
            columns, [&](GridColumn const& col) -> bool {
                return col.name == name;
            });
        if (iter == columns.end()) {
            columns.push_back(GridColumn{.name = name});
            return columns.back();
        } else {
            return *iter;
        }
    }

    Vec<GridRow*> flatRows() {
        Vec<GridRow*> result;
        for (auto& row : rows) { result.append(row.flatThisNested()); }
        return result;
    }

    GridRow* getRow(int pos) {
        // TODO Optimize, this is a O(n^2) code.
        for (auto it : flatRows()) {
            if (it->flatIdx == pos) { return it; }
        }
        return nullptr;
    }

    GridRow const* getRow(int pos) const {
        // TODO Optimize, this is a O(n^2) code.
        for (auto it : const_cast<DocumentGrid*>(this)->flatRows()) {
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

    DESC_FIELDS(DocumentGrid, (rows, rowPositions, columns));
};

struct DocumentNode {
    struct Grid {
        ImVec2       pos;
        ImVec2       size;
        DocumentGrid node;
        DESC_FIELDS(Grid, (node, pos, size));
    };

    struct List {
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
        DESC_FIELDS(List, (items, pos, size));

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


    SUB_VARIANTS(Kind, Data, data, getKind, Grid, Text, List);
    Data data;
    DESC_FIELDS(DocumentNode, (data));
};

struct DocumentGraph {
    Vec<DocumentNode>          nodes;
    DocGraph                   ir;
    UnorderedMap<int, DocNode> gridNodeToNode;
    UnorderedMap<DocNode, int> nodeToGridNode;
    org::graph::MapGraph       graph;

    UnorderedMap<org::ImmUniqId, DocNode> orgToId;

    DESC_FIELDS(
        DocumentGraph,
        (nodes, ir, gridNodeToNode, nodeToGridNode));

    void addIrNode(int flatIdx, DocNode const& irNode) {
        gridNodeToNode.insert_or_assign(flatIdx, irNode);
        nodeToGridNode.insert_or_assign(irNode, flatIdx);
    }

    DocumentNode const& getDocNode(int idx) const { return nodes.at(idx); }

    DocumentNode const& getDocNode(DocNode const& idx) const {
        return getDocNode(getFlatIdx(idx));
    }

    DocNode const& getIrNode(int idx) const {
        return gridNodeToNode.at(idx);
    }

    int const& getFlatIdx(DocNode const& node) const {
        return nodeToGridNode.at(node);
    }
};

struct GridContext
    : OperationsTracer
    , OperationsScope {

    DESC_FIELDS(GridContext, ());

    void message(
        std::string const& value,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE()) const;
};

struct GridAction {
    struct EditCell {
        GridCell    cell;
        std::string updated;
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

struct GridState {
    org::ImmAstVersion ast;
};


struct GridModel {
    DECL_DESCRIBED_ENUM(UpdateNeeded, Scroll, Graph);
    Vec<GridState>             history;
    DocumentGraph              rectGraph;
    GridContext                conf;
    GraphLayoutIR::Result      layout;
    ImVec2                     shift{20, 20};
    Opt<DocConstraintDebug>    debug;
    void                       updateDocument();
    Vec<Slice<int>>            laneSpans;
    Vec<float>                 laneOffsets;
    GridState&                 getCurrentState() { return history.back(); }
    void                       apply(GridAction const& act);
    UnorderedSet<UpdateNeeded> updateNeeded;
};


void story_grid_loop(GLFWwindow* window, std::string const& file);
