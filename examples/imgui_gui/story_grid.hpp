#pragma once
#define IMMER_TAGGED_NODE 0

#include <GLFW/glfw3.h>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/sem/ImmOrg.hpp>

struct GridCell {
    int             height;
    int             width;
    std::string     value;
    org::ImmAdapter origin;
    DESC_FIELDS(GridCell, (height, width, value, origin));
};

struct GridRow {
    GridCell title;

    struct Columns {
        Opt<GridCell> event;
        Opt<GridCell> location;
        DESC_FIELDS(Columns, (event, location));
    };

    Columns      columns;
    Vec<GridRow> nested;
    DESC_FIELDS(GridRow, (title, columns, nested));
};

struct GridDocument {
    Vec<GridRow> rows;

    DESC_FIELDS(GridDocument, (rows));
};

struct GridConfig {
    struct Widths {
        int event;
        int location;
        int title;
        DESC_FIELDS(Widths, (event, location, title));
    };
    Widths widths;
    DESC_FIELDS(GridConfig, (widths));
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
    GridConfig     conf;
    void           updateDocument();
    GridState&     getCurrentState() { return history.back(); }
    void           apply(GridAction const& act);
};

GridCell buildCell(org::ImmAdapter adapter, int width);
GridRow  buildRow(
     org::ImmAdapterT<org::ImmSubtree> tree,
     GridConfig const&                 conf);
Vec<GridRow> buildRows(org::ImmAdapter root, GridConfig const& conf);

void story_grid_loop(GLFWwindow* window, sem::SemId<sem::Org> node);
