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
    DESC_FIELDS(TreeGridCell, (height, width, data));


    Data data;
    int  height;
    int  width;


    bool   isEditing() const { return isValue() && getValue().is_editing; }
    int    getHeight() const { return height + (isEditing() ? 40 : 0); }
    ImVec2 getSize() const { return ImVec2(width, getHeight()); }
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
    Vec<int>            rowPositions;
    Vec<int>            colPositions;
    Vec<TreeGridColumn> columns;
    int                 rowPadding        = 6;
    int                 colPadding        = 6;
    int                 treeFoldWidth     = 120;
    int                 tableHeaderHeight = 16;

    UnorderedMap<org::ImmUniqId, int> rowOrigins;

    void resetCellPositions();

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
        bool      isSelected = false;
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


struct DocAnnotation {
    org::graph::MapNode source;
    org::graph::MapNode target;
    DESC_FIELDS(DocAnnotation, (source, target));
};

struct StoryGridGraph {
    Vec<StoryGridNode>             nodes;
    LaneBlockGraph                 ir;
    UnorderedMap<int, LaneNodePos> gridNodeToNode;
    UnorderedMap<LaneNodePos, int> nodeToGridNode;
    org::graph::MapGraph           graph;
    Vec<Vec<DocAnnotation>>        partition;
    int                            laneRowPadding = 6;

    UnorderedMap<org::ImmUniqId, org::ImmUniqId> annotationParents;
    UnorderedMap<org::ImmUniqId, LaneNodePos>    orgToId;

    bool isVisible(org::ImmUniqId const& id) const {
        auto lane_pos = orgToId.get(id);
        if (!lane_pos) { return false; }
        auto node = nodeToGridNode.get(lane_pos.value());
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
        EditCellChanged);

    Data data;
    DESC_FIELDS(GridAction, (data));
};

struct StoryGridStyle {
    ImU32 foldCellHoverBackground = IM_COL32(0, 255, 255, 255);
    ImU32 foldCellBackground      = IM_COL32(255, 0, 0, 128);
    DESC_FIELDS(StoryGridStyle, (foldCellHoverBackground));
};

struct StoryGridContext
    : OperationsTracer
    , OperationsScope {

    DESC_FIELDS(StoryGridContext, (annotated, actions, style));

    Vec<GridAction> actions;
    bool            annotated;
    StoryGridStyle  style;

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
    StoryGridContext         conf;
    GraphLayoutIR::Result    layout;
    ImVec2                   shift{20, 20};
    Opt<ColaConstraintDebug> debug;
    void              updateDocument(const TreeGridDocument& init_doc);
    Vec<Slice<int>>   laneSpans;
    Vec<float>        laneOffsets;
    StoryGridHistory& getLastHistory() { return history.back(); }
    void              apply(GridAction const& act);
    UnorderedSet<UpdateNeeded> updateNeeded;
    StoryGridState             state;
};


Opt<json> story_grid_loop(
    GLFWwindow*        window,
    std::string const& file,
    bool               annotated,
    Opt<json> const&   in_state);

void run_story_grid_annotated_cycle(StoryGridModel& model);
void run_story_grid_cycle(StoryGridModel& model);
void apply_story_grid_changes(
    StoryGridModel&         model,
    TreeGridDocument const& init_doc);
