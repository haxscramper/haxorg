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
#include <gui_lib/im_org_ui_common.hpp>
#include <gui_lib/node_grid_graph.hpp>

struct TreeGridCell {

    struct None {
        DESC_FIELDS(None, ());
    };

    struct Value {
        EditableOrgText value;
        org::ImmAdapter origin = org::ImmAdapter{};
        DESC_FIELDS(Value, (value, origin));
        std::string getFinalValue() { return value.getFinalValue(); }
    };

    SUB_VARIANTS(Kind, Data, data, getKind, None, Value);
    DESC_FIELDS(TreeGridCell, (height, width, data));


    Data data;
    int  height;
    int  width;


    bool isEditing() const {
        return isValue() && getValue().value.is_editing;
    }
    int    getHeight() const { return height + (isEditing() ? 40 : 0); }
    ImVec2 getSize() const { return ImVec2(width, getHeight()); }
    std::string getFinalTextValue() { return getValue().getFinalValue(); }
};

struct TreeGridColumn {
    std::string           name;
    int                   width = 120;
    EditableOrgText::Mode edit  = EditableOrgText::Mode::Multiline;
    DESC_FIELDS(TreeGridColumn, (name, width, edit));
};

struct TreeGridRow {
    int                               flatIdx;
    org::ImmAdapterT<org::ImmSubtree> origin;
    UnorderedMap<Str, TreeGridCell>   columns;
    Vec<TreeGridRow>                  nested;
    bool                              isVisible = true;
    bool                              isOpen    = true;
    DESC_FIELDS(
        TreeGridRow,
        (columns, origin, flatIdx, nested, isVisible, isOpen));

    bool isEditing() const {
        return rs::any_of(columns, [](auto const& arg) -> bool {
            return arg.second.isEditing();
        });
    }


    bool isShowingNested() const { return !nested.empty() && isOpen; }

    Vec<int> getOriginPath() const {
        Vec<int> idx;
        for (auto const& step : origin.flatPath().path) {
            if (step.isIndex()) { idx.push_back(step.getIndex().index); }
        }
        return idx;
    }

    Vec<TreeGridRow*> flatThisNested(bool withInvisible);

    int      getHeightDirect(int padding = 0) const;
    Opt<int> getHeight(int padding = 0) const;
    int      getHeightRecDirect(int padding = 0) const;
    Opt<int> getHeightRec(int padding = 0) const;

    TreeGridRow* getLastLeaf() {
        if (nested.empty()) {
            return this;
        } else {
            return nested.back().getLastLeaf();
        }
    }

    TreeGridRow const* getLastLeaf() const {
        if (nested.empty()) {
            return this;
        } else {
            return nested.back().getLastLeaf();
        }
    }
};

struct TreeGridDocument {
    Vec<TreeGridRow>    rows;
    Vec<TreeGridColumn> columns;
    int                 rowPadding        = 6;
    int                 colPadding        = 6;
    int                 treeFoldWidth     = 120;
    int                 tableHeaderHeight = 16;
    Vec<int>            rowPositions;
    Vec<int>            colPositions;

    UnorderedMap<org::ImmUniqId, int> rowOrigins;

    void resetGridStatics();

    int getRowYPos(TreeGridRow const& r) { return getRowYPos(r.flatIdx); }
    int getRowYPos(int index) { return rowPositions.at(index); }

    int getColumnXPos(CR<Str> name) {
        return colPositions.at(getColumnIndex(name));
    }

    TreeGridCell& getExistingCell(int row, CR<Str> column) {
        return flatRows(true).at(row)->columns.at(column);
    }


    ImVec2 getCellPos(int row, CR<Str> column) {
        return ImVec2(getColumnXPos(column), getRowYPos(row));
    }

    ImVec2 getSize() const { return ImVec2(getWidth(), getHeight()); }

    int getColumnIndex(CR<Str> name) {
        auto iter = rs::find_if(
            columns, [&](TreeGridColumn const& col) -> bool {
                return col.name == name;
            });
        if (iter == columns.end()) {
            columns.push_back(TreeGridColumn{.name = name});
            return columns.high();
        } else {
            return std::distance(columns.begin(), iter);
        }
    }

    TreeGridColumn& getColumn(CR<Str> name) {
        return columns.at(getColumnIndex(name));
    }

    Vec<TreeGridRow*> flatRows(bool withInvisible) {
        Vec<TreeGridRow*> result;
        for (auto& row : rows) {
            result.append(row.flatThisNested(withInvisible));
        }
        return result;
    }

    TreeGridRow* getRow(int pos) {
        // TODO Optimize, this is a O(n^2) code.
        for (auto it : flatRows(true)) {
            if (it->flatIdx == pos) { return it; }
        }
        return nullptr;
    }

    TreeGridRow const* getRow(int pos) const {
        // TODO Optimize, this is a O(n^2) code.
        for (auto it :
             const_cast<TreeGridDocument*>(this)->flatRows(true)) {
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

    int getHeight() const {
        return rowPositions.back()
             + rows.back().getLastLeaf()->getHeight().value_or(0);
    }

    int getWidth() const {
        return colPositions.back() + columns.back().width;
    }

    Opt<int> getRowCenterOffset(int rowIdx) const {
        if (getRow(rowIdx)->isVisible) {
            return float(rowPositions.at(rowIdx))
                 + float(getRow(rowIdx)->getHeight().value()) / 2;
        } else {
            return std::nullopt;
        }
    }

    DESC_FIELDS(TreeGridDocument, (rows, rowPositions, columns));
};

struct StoryGridNode {
    struct TreeGrid {
        ImVec2           pos;
        TreeGridDocument node;
        DESC_FIELDS(TreeGrid, (node, pos));
        ImVec2 getSize() const { return node.getSize(); }
    };

    struct LinkList {
        struct Item {
            EditableOrgText text;
            int             width;
            int             height;
            org::ImmAdapter node;
            DESC_FIELDS(Item, (text, width, height, node));
        };
        Vec<Item> items;
        ImVec2    pos;
        ImVec2    size;
        bool      isSelected           = false;
        int       imguiTableRowPadding = 5;
        DESC_FIELDS(LinkList, (items, pos, size, isSelected));

        int getRow(org::ImmUniqId const& row) const {
            auto iter = rs::find_if(items, [&](Item const& i) {
                return i.node.uniq() == row;
            });
            LOGIC_ASSERTION_CHECK(iter != items.end(), "{}", row);
            return std::distance(items.begin(), iter);
        }

        int getRowOffset(org::ImmUniqId const& row) const {
            return getRowOffset(getRow(row));
        }

        int getRowOffset(int row) const {
            int offset = 0;
            for (auto const& [row_idx, item] : enumerate(items)) {
                if (row_idx < row) { offset += item.height; }
            }
            return offset;
        }

        int getRowCenterOffset(int row) const {
            return getRowOffset(row) + items.at(row).height / 2.0f;
        }

        ImVec2 getSize() const { return ImVec2(getWidth(), getHeight()); }

        int getHeight() const {
            int result = 0;
            for (auto const& item : items) {
                result += imguiTableRowPadding + item.height;
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
        org::ImmAdapter origin;
        EditableOrgText text;
        DESC_FIELDS(Text, (origin, pos, size, text));
        ImVec2 getSize() const {
            return ImVec2(size.x, size.y + (text.is_editing ? 40 : 0));
        }
    };

    ImVec2 getSize() const {
        return std::visit(
            overloaded{
                [](LinkList const& l) -> ImVec2 { return l.getSize(); },
                [](TreeGrid const& t) -> ImVec2 { return t.getSize(); },
                [](Text const& t) -> ImVec2 { return t.getSize(); },
            },
            data);
    }

    void setPos(ImVec2 const& pos) {
        std::visit(
            overloaded{
                [&](Text& t) { t.pos = pos; },
                [&](TreeGrid& t) { t.pos = pos; },
                [&](LinkList& l) { l.pos = pos; },
            },
            data);
    }

    SUB_VARIANTS(Kind, Data, data, getKind, TreeGrid, Text, LinkList);
    Data data;
    bool isVisible = true;
    DESC_FIELDS(StoryGridNode, (data, isVisible));
};


struct StoryGridAnnotation {
    org::graph::MapNode source;
    org::graph::MapNode target;
    DESC_FIELDS(StoryGridAnnotation, (source, target));
};

struct StoryGridGraph {
    Vec<StoryGridNode>            nodes;
    NodeGridGraph                 ir;
    org::graph::MapGraph          graph;
    Vec<Vec<StoryGridAnnotation>> partition;

    UnorderedMap<org::ImmUniqId, org::ImmUniqId> annotationParents;
    UnorderedMap<org::ImmUniqId, LaneNodePos>    orgToId;

    bool isVisible(org::ImmUniqId const& id) const {
        auto lane_pos = orgToId.get(id);
        if (!lane_pos) { return false; }
        auto node = ir.getFlat(lane_pos.value());
        if (!node) { return false; }
        if (!nodes.at(node.value()).isTreeGrid()) { return false; }
        auto origin = nodes.at(node.value())
                          .getTreeGrid()
                          .node.rowOrigins.get(id);
        if (!origin) { return false; }
        return nodes.at(node.value())
            .getTreeGrid()
            .node.getRow(origin.value())
            ->isVisible;
    }

    DESC_FIELDS(StoryGridGraph, (nodes, ir, graph, partition));

    StoryGridNode& at(LaneNodePos const& pos) {
        return nodes.at(ir.at(pos));
    }

    StoryGridNode const& getDocNode(int idx) const {
        return nodes.at(idx);
    }

    StoryGridNode const& getDocNode(LaneNodePos const& idx) const {
        return getDocNode(getFlatIdx(idx));
    }

    LaneNodePos getIrNode(int idx) const {
        return ir.getGrid(idx).value();
    }

    int getFlatIdx(LaneNodePos const& node) const {
        return ir.getFlat(node).value();
    }

    int addNode(
        int                         lane,
        ImVec2 const&               size,
        StoryGridNode const&        node,
        LaneBlockGraphConfig const& conf) {
        nodes.push_back(node);
        auto rootRect = ir.ir.addNode(0, size, conf);
        ir.add(nodes.high(), rootRect);
        return nodes.high();
    }
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

    struct EditCellChanged {
        TreeGridCell cell;
        int          documentNodeIdx;
        DESC_FIELDS(EditCellChanged, (cell, documentNodeIdx));
    };

    struct EditNodeText {
        LaneNodePos pos;
        std::string updated;
        DESC_FIELDS(EditNodeText, (pos, updated));
    };

    struct EditNodeChanged {
        LaneNodePos pos;
        DESC_FIELDS(EditNodeChanged, (pos));
    };

    struct LinkListClick {
        DESC_FIELDS(LinkListClick, ());
    };

    struct RowFolding {
        bool isOpen;
        int  flatIdx;
        int  documentNodeIdx;
        DESC_FIELDS(RowFolding, (isOpen, flatIdx, documentNodeIdx));
    };

    SUB_VARIANTS(
        Kind,
        Data,
        data,
        getKind,
        EditCell,
        Scroll,
        LinkListClick,
        RowFolding,
        EditCellChanged,
        EditNodeChanged,
        EditNodeText);

    Data data;
    DESC_FIELDS(GridAction, (data));
};

/// \brief All the configuration parameters for rendering the story grid,
/// static variables that change the logic of the render, data model
/// updates etc., but are not change-able from within the UI part of the
/// application.
struct StoryGridConfig {
    struct StoryGridColumnConfig {
        Opt<int>                   width;
        Opt<EditableOrgText::Mode> edit;
        Str                        name;
        DESC_FIELDS(StoryGridColumnConfig, (width, edit, name));
    };

    Vec<StoryGridColumnConfig> defaultColumns;
    LaneBlockGraphConfig       blockGraphConf;

    ImU32  foldCellHoverBackground = IM_COL32(0, 255, 255, 255);
    ImU32  foldCellBackground      = IM_COL32(255, 0, 0, 128);
    ImU32  annotationNodeWindowBg  = IM_COL32(128, 128, 128, 128);
    bool   annotated               = true;
    int    pageUpScrollStep        = 20;
    int    pageDownScrollStep      = -20;
    int    mouseScrollMultiplier   = 10;
    int    annotationNodeWidth     = 200;
    int    laneRowPadding          = 6;
    ImVec2 gridViewport;


    DESC_FIELDS(
        StoryGridConfig,
        (defaultColumns,
         foldCellHoverBackground,
         foldCellBackground,
         blockGraphConf,
         annotated,
         pageUpScrollStep,
         pageDownScrollStep,
         mouseScrollMultiplier,
         annotationNodeWidth,
         laneRowPadding,
         gridViewport));
};

/// \brief Highly mutable context variable that is passed to all rendering
/// elements to collect actions.
struct StoryGridContext
    : OperationsTracer
    , OperationsScope {

    DESC_FIELDS(StoryGridContext, (actions));

    Vec<GridAction> actions;

    void action(
        GridAction::Data const& act,
        int                     line     = __builtin_LINE(),
        char const*             function = __builtin_FUNCTION(),
        char const*             file     = __builtin_FILE()) {
        GridAction ga{act};
        message(fmt("Action {}", ga), line, function, file);
        actions.push_back({ga});
    }

    void message(
        std::string const& value,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE()) const;
};

struct StoryGridHistory {
    org::ImmAstVersion ast;
};

struct StoryGridState {
    UnorderedMap<int, UnorderedMap<Vec<int>, bool>> folded;
    DESC_FIELDS(StoryGridState, (folded));
};


struct StoryGridModel {
    DECL_DESCRIBED_ENUM(UpdateNeeded, LinkListClick, Scroll, Graph);
    Vec<StoryGridHistory>    history;
    StoryGridGraph           rectGraph;
    StoryGridContext         ctx;
    ImVec2                   shift{};
    Opt<ColaConstraintDebug> debug;
    StoryGridHistory&        getLastHistory() { return history.back(); }
    void apply(GridAction const& act, StoryGridConfig const& style);

    void updateDocument(
        const TreeGridDocument& init_doc,
        const StoryGridConfig&  conf);
    UnorderedSet<UpdateNeeded> updateNeeded;
    StoryGridState             state;
};


Opt<json> story_grid_loop(
    GLFWwindow*            window,
    std::string const&     file,
    Opt<json> const&       in_state,
    const StoryGridConfig& conf);

void run_story_grid_annotated_cycle(
    StoryGridModel&        model,
    const StoryGridConfig& conf);
void run_story_grid_cycle(
    StoryGridModel&        model,
    StoryGridConfig const& conf);
void apply_story_grid_changes(
    StoryGridModel&         model,
    TreeGridDocument const& init_doc,
    const StoryGridConfig&  conf);
