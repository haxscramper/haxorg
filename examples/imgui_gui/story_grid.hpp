#pragma once
// immer templates are instantiated in the haxorg library without debug
// checks, but building imgui application in debug mode causes a new series
// of instantiations and overwrites the symbols with debug enabled, causing
// constant assertion failures.
#define NDEBUG 0

#include <GLFW/glfw3.h>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include "imgui.h"

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

    int getHeight() const {
        return rs::max(
            own_view(columns.keys()) | rv::transform([&](Str const& col) {
                return columns.at(col).height;
            }));
    }

    int getHeightRec() const {
        return getHeight()
             + rs::fold_left(
                   nested | rv::transform([](GridRow const& r) {
                       return r.getHeightRec();
                   }),
                   0,
                   [](int lhs, int rhs) { return lhs + rhs; });
    }
};

struct GridDocument {
    Vec<GridRow> rows;
    int          getHeight() const {
        int res = 0;
        for (auto const& row : rows) { res += row.getHeightRec(); }
        return res;
    }

    DESC_FIELDS(GridDocument, (rows));
};

struct GridContext
    : OperationsTracer
    , OperationsScope {

    Vec<ImVec2> rowPositions;

    Vec<GridColumn> columns;
    DESC_FIELDS(GridContext, (columns));

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
    };

    SUB_VARIANTS(Kind, Data, data, getKind, EditCell);
    Data data;
};

struct GridState {
    org::ImmAstVersion ast;
};

struct GridModel {
    Vec<GridState> history;
    GridDocument   document;
    GridContext    conf;
    void           updateDocument();
    GridState&     getCurrentState() { return history.back(); }
    void           apply(GridAction const& act);
};


void story_grid_loop(GLFWwindow* window, std::string const& file);
