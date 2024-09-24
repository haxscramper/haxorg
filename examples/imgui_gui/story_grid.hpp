#pragma once
// immer templates are instantiated in the haxorg library without debug
// checks, but building imgui application in debug mode causes a new series
// of instantiations and overwrites the symbols with debug enabled, causing
// constant assertion failures.
#define NDEBUG 0

#include <GLFW/glfw3.h>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/sem/ImmOrg.hpp>

struct GridCell {
    int             height;
    int             width;
    int             wrapcount;
    std::string     value;
    org::ImmAdapter origin;
    DESC_FIELDS(GridCell, (height, width, value, origin));
};

struct GridRow {
    org::ImmAdapterT<org::ImmSubtree> origin;
    UnorderedMap<Str, GridCell>       columns;
    Vec<GridRow>                      nested;
    DESC_FIELDS(GridRow, (columns, nested));
};

struct GridDocument {
    Vec<GridRow> rows;

    DESC_FIELDS(GridDocument, (rows));
};

struct GridContext
    : OperationsTracer
    , OperationsScope {

    Vec<Str>               columnNames;
    UnorderedMap<Str, int> widths;
    DESC_FIELDS(GridContext, (widths));

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


void story_grid_loop(GLFWwindow* window, sem::SemId<sem::Org> node);
