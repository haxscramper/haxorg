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

struct GridNode {
    Vec<GridRow>    rows;
    Vec<int>        rowPositions;
    Vec<GridColumn> columns;

    UnorderedMap<org::ImmUniqId, int> rowOrigins;

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

    DESC_FIELDS(GridNode, (rows, rowPositions, columns));
};

struct DocumentNode {
    struct Grid {
        ImVec2   pos;
        ImVec2   size;
        GridNode node;
        DESC_FIELDS(Grid, (node, pos, size));
    };

    struct Text {
        ImVec2          pos;
        ImVec2          size;
        org::ImmAdapter node;
        std::string     text;
        DESC_FIELDS(Text, (node, pos, size));
    };


    SUB_VARIANTS(Kind, Data, data, getKind, Grid, Text);
    Data data;
    DESC_FIELDS(DocumentNode, (data));
};

struct DocumentGraph {
    Vec<DocumentNode> nodes;
    DESC_FIELDS(DocumentGraph, (nodes));
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
    Vec<GridState>          history;
    DocumentGraph           document;
    GridContext             conf;
    org::graph::MapGraph    graph;
    GraphLayoutIR::Result   layout;
    ImVec2                  shift{20, 20};
    Opt<DocConstraintDebug> debug;
    void                    updateDocument();
    Vec<Slice<int>>         laneSpans;
    Vec<float>              laneOffsets;
    GridState&              getCurrentState() { return history.back(); }
    void                    apply(GridAction const& act);
};


void story_grid_loop(GLFWwindow* window, std::string const& file);
