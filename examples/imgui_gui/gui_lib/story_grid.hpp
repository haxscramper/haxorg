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

struct TreeGridRow : SharedPtrApi<TreeGridRow> {
    int                               flatIdx;
    org::ImmAdapterT<org::ImmSubtree> origin;
    UnorderedMap<Str, TreeGridCell>   columns;
    Vec<TreeGridRow::Ptr>             nested;
    std::weak_ptr<TreeGridRow>        parent;
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

    bool hasParent() const { return !parent.expired(); }

    bool isInvisibleOrParentFolded() const {
        return !isVisible
            || (hasParent() && parent.lock()->isInvisibleOrParentFolded());
    }

    bool isShowingNested() const { return !nested.empty() && isOpen; }

    Vec<int> getOriginPath() const {
        Vec<int> idx;
        for (auto const& step : origin.flatPath().path) {
            if (step.isIndex()) { idx.push_back(step.getIndex().index); }
        }
        return idx;
    }

    void addNested(TreeGridRow::Ptr const& nest) {
        nested.push_back(nest);
        nested.back()->parent = weak_from_this();
    }

    Vec<Ptr> flatThisNested(bool withInvisible) const;
    int      getHeightDirect(int padding = 0) const;
    Opt<int> getHeight(int padding = 0) const;
    int      getHeightRecDirect(int padding = 0) const;
    Opt<int> getHeightRec(int padding = 0) const;

    TreeGridRow::Ptr getLastLeaf() const {
        if (nested.empty()) {
            return mshared_from_this();
        } else {
            return nested.back()->getLastLeaf();
        }
    }
};

struct StoryGridConfig;
struct StoryGridContext;
struct TreeGridDocument {
    Vec<TreeGridRow::Ptr> rows;
    Vec<TreeGridColumn>   columns;
    int                   rowPadding = 6;
    int                   colPadding = 6;
    /// \brief Width of leftmost column with tree folding indicators
    int      treeFoldWidth     = 120;
    int      tableHeaderHeight = 16;
    Vec<int> rowPositions;
    Vec<int> colPositions;

    UnorderedMap<org::ImmUniqId, int> rowOrigins;

    void updatePositions();

    int getRowYPos(TreeGridRow::Ptr const& r) {
        return getRowYPos(r->flatIdx);
    }
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

    Vec<TreeGridRow::Ptr> flatRows(bool withInvisible) const {
        Vec<TreeGridRow::Ptr> result;
        for (auto& row : rows) {
            result.append(row->flatThisNested(withInvisible));
        }
        return result;
    }

    TreeGridRow::Ptr getRow(int pos) const {
        // TODO Optimize, this is a O(n^2) code.
        for (auto it : flatRows(true)) {
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
             + rows.back()->getLastLeaf()->getHeight().value_or(0);
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

    static TreeGridDocument from_root(
        const org::ImmAdapter& node,
        const StoryGridConfig& conf,
        StoryGridContext&      ctx);

    DESC_FIELDS(TreeGridDocument, (rows, rowPositions, columns));
};

DECL_ID_TYPE(StoryNode, StoryNodeId, std::size_t);

struct StoryNode {
    using id_type = StoryNodeId;
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
        Vec<Item>       items;
        ImVec2          pos;
        ImVec2          size;
        org::ImmAdapter origin;
        bool            isSelected           = false;
        int             imguiTableRowPadding = 5;
        DESC_FIELDS(LinkList, (items, pos, size, isSelected, origin));

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
    DESC_FIELDS(StoryNode, (data, isVisible));
};


struct StoryGridAnnotation {
    org::graph::MapNode source;
    org::graph::MapNode target;
    DESC_FIELDS(StoryGridAnnotation, (source, target));
};

struct StoryGridContext;
struct StoryGridConfig;

struct StoryGridGraph {

    struct SemGraphStore {
        org::ImmAstContext::Ptr                      ctx;
        UnorderedMap<org::ImmUniqId, org::ImmUniqId> annotationParents;
        org::graph::MapGraph                         graph;
        DESC_FIELDS(SemGraphStore, (annotationParents, graph));

        TreeGridDocument addDocNode(
            org::ImmAdapter const& node,
            StoryGridConfig const& conf,
            StoryGridContext&      ctx);

        void addGridAnnotationNodes(
            TreeGridDocument const& doc,
            StoryGridContext&       ctx);

        void addDescriptionListNodes(
            org::ImmAdapterT<org::ImmList> const& list,
            StoryGridContext&                     ctx);

        static SemGraphStore init(
            org::ImmAdapter const& root,
            StoryGridConfig const& conf,
            StoryGridContext&      ctx);
    };


    struct FlatNodeStore {
        UnorderedMap<org::ImmUniqId, StoryNodeId> orgToFlatIdx;
        dod::Store<StoryNodeId, StoryNode>        nodes;
        DESC_FIELDS(FlatNodeStore, (orgToFlatIdx, nodes));

        auto&& getStoryNode(this auto&& s, StoryNodeId const& id) {
            return s.nodes.at(id);
        }

        auto&& getStoryNode(this auto&& s, org::ImmUniqId const& id) {
            return s.getStoryNode(s.orgToFlatIdx.at(id));
        }

        Opt<StoryNodeId> getStoryNodeId(org::ImmUniqId const& id) const {
            return orgToFlatIdx.get(id);
        }

        static FlatNodeStore init(
            SemGraphStore const&   semGraph,
            StoryGridContext&      ctx,
            StoryGridConfig const& conf);

        void setOrgNodeOrigin(
            org::ImmUniqId const& id,
            StoryNodeId           flatIdx) {
            orgToFlatIdx.insert_or_assign(id, flatIdx);
        }

        void setOrgNodeOrigin(StoryNode const& n, StoryNodeId id);

        StoryNodeId add(
            const org::ImmAdapter& node,
            const StoryGridConfig& conf,
            StoryGridContext&      ctx);

        StoryNodeId add(StoryNode const& node) {
            auto id = nodes.add(node);
            setOrgNodeOrigin(node, id);
            return id;
        }

        auto pairs() -> generator<Pair<StoryNodeId, StoryNode*>> {
            const int size = nodes.size();
            for (int i = 0; i < size; ++i) {
                auto id = StoryNodeId::FromIndex(i);
                co_yield {id, &nodes.at(id)};
            }
        }

        auto items() -> generator<StoryNode*> {
            const int size = nodes.size();
            for (int i = 0; i < size; ++i) {
                auto id = StoryNodeId::FromIndex(i);
                co_yield &nodes.at(id);
            }
        }

        bool isVisible(const org::ImmUniqId& id) const;

        /// \brief If grid graph has focused linked description list, hide
        /// all grid rows except ones that are directly targeted by the
        /// link list. If there is no focused list, then show all rows.
        void focusLinkListTargetRows(
            StoryGridContext&    ctx,
            SemGraphStore const& semGraph);

        Vec<org::graph::MapNode> getInitialNodes(
            StoryGridContext&    ctx,
            SemGraphStore const& semGraph) const;

        Vec<Vec<StoryGridAnnotation>> getGraphPartition(
            StoryGridContext&    ctx,
            SemGraphStore const& semGraph) const;
    };

    struct BlockGraphStore {
        NodeGridGraph                 ir;
        Vec<Vec<StoryGridAnnotation>> partition;
        DESC_FIELDS(BlockGraphStore, (ir, partition));

        Opt<LaneNodePos> getBlockPos(StoryNodeId const& id) const {
            return ir.getGrid(id.getIndex());
        }

        Opt<StoryNodeId> getStoryNodeId(LaneNodePos const& pos) const {
            auto idx = ir.getFlat(pos);
            if (idx) {
                return StoryNodeId::FromIndex(idx.value());
            } else {
                return std::nullopt;
            }
        }

        LaneNodePos addToLane(
            int                    laneIdx,
            StoryNodeId            id,
            StoryGridConfig const& conf,
            FlatNodeStore const&   nodes);

        void setPartition(
            Vec<Vec<StoryGridAnnotation>> const& inPartition,
            FlatNodeStore const&                 storyNodes,
            SemGraphStore const&                 semGraph,
            StoryGridConfig const&               conf,
            StoryGridContext&                    ctx);


        /// \brief Mark edge and node visibility based on the current
        /// scroll positions. This function is called in the
        /// `updateDocumentLayout` and requires node positions to be
        /// computed before.
        void updateHiddenRowConnection(
            StoryGridConfig const& conf,
            StoryGridContext&      ctx,
            SemGraphStore const&   semGraph,
            FlatNodeStore&         storyNodes);


        /// \brief Update document layout for the current graph
        /// configuration. Syncs node sizes and builds graph layout IR to
        /// sync with the current document state. This is the entry point
        /// to update node and edge positions if the graph structure itself
        /// is the same.
        void updateDocumentLayout(
            StoryGridConfig const& conf,
            StoryGridContext&      ctx,
            SemGraphStore const&   semGraph,
            FlatNodeStore&         storyNodes);

        /// \brief Update document node positions with current node sizes
        /// and edge positions. Called by `updateDocumentLayout`
        void updateDocumentNodePositions(
            StoryGridConfig const& conf,
            StoryGridContext&      ctx,
            FlatNodeStore&         storyNodes);

        static BlockGraphStore init(
            SemGraphStore const&   semGraph,
            FlatNodeStore&         storyNodes,
            StoryGridContext&      ctx,
            StoryGridConfig const& conf);
    };

    FlatNodeStore   storyNodes;
    SemGraphStore   semGraph;
    BlockGraphStore blockGraph;

    Vec<StoryNode*> getGridNodes() {
        Vec<StoryNode*> res;
        for (auto const& node : storyNodes.items()) {
            if (node->isTreeGrid()) { res.push_back(node); }
        }
        return res;
    }

    void updateGeometry(StoryNodeId const& id) {
        if (storyNodes.getStoryNode(id).isTreeGrid()) {
            auto& n = storyNodes.getStoryNode(id).getTreeGrid();
            n.node.updatePositions();
        }
    }

    void focusLinkListTargetRows(StoryGridContext& ctx) {
        storyNodes.focusLinkListTargetRows(ctx, semGraph);
    }

    void updateStoryNodes(
        StoryGridContext&      ctx,
        StoryGridConfig const& conf) {
        storyNodes = FlatNodeStore::init(semGraph, ctx, conf);
    }

    void updateSemanticGraph(
        org::ImmAdapter const& root,
        StoryGridContext&      ctx,
        StoryGridConfig const& conf) {
        semGraph = SemGraphStore::init(root, conf, ctx);
    }

    /// \brief Rebuild block grid
    void updateNodeLanePlacement(
        StoryGridContext&      ctx,
        StoryGridConfig const& conf) {
        // FIXME: the same as node position update, later on block graph
        // should be split into "lane node graph" + "node position bundle"
        blockGraph = BlockGraphStore::init(
            semGraph, storyNodes, ctx, conf);
    }

    void updateNodePositions(
        StoryGridContext&      ctx,
        StoryGridConfig const& conf) {
        blockGraph = BlockGraphStore::init(
            semGraph, storyNodes, ctx, conf);
    }

    void resetBlockLanes(StoryGridConfig const& conf);


    bool isVisible(org::ImmUniqId const& id) const;

    DESC_FIELDS(StoryGridGraph, (storyNodes, semGraph, blockGraph));

    generator<Pair<StoryNodeId, StoryNode*>> getStoryNodes() {
        return storyNodes.pairs();
    }

    StoryNode& getStoryNode(LaneNodePos const& pos) {
        return storyNodes.getStoryNode(getStoryNodeId(pos).value());
    }

    StoryNode& getStoryNode(StoryNodeId idx) {
        return storyNodes.getStoryNode(idx);
    }

    StoryNode const& getStoryNode(StoryNodeId idx) const {
        return storyNodes.getStoryNode(idx);
    }

    StoryNode const& getStoryNode(LaneNodePos const& idx) const {
        return storyNodes.getStoryNode(getStoryNodeId(idx).value());
    }

    Opt<LaneNodePos> getBlockPos(StoryNodeId idx) const {
        return blockGraph.getBlockPos(idx);
    }

    Opt<StoryNodeId> getStoryNodeId(LaneNodePos const& node) const {
        return blockGraph.getStoryNodeId(node);
    }

    Opt<StoryNodeId> getStoryNodeId(org::ImmUniqId const& id) const {
        return storyNodes.getStoryNodeId(id);
    }

    Opt<LaneNodePos> getBlockNodePos(org::ImmUniqId const& id) {
        auto flat = getStoryNodeId(id);
        if (flat) {
            return blockGraph.getBlockPos(flat.value());
        } else {
            return std::nullopt;
        }
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
        StoryNodeId  documentNodeIdx;
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
        bool        isOpen;
        int         flatIdx;
        StoryNodeId documentNodeIdx;
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
    LaneBlockGraphConfig     blockGraphConf;
    Func<TreeGridDocument()> getDefaultDoc;

    ImU32  foldCellHoverBackground_Open   = IM_COL32(0, 255, 255, 255);
    ImU32  foldCellForeground_Open        = IM_COL32(255, 0, 0, 128);
    ImU32  foldCellHoverBackground_Closed = IM_COL32(0, 255, 255, 255);
    ImU32  foldCellForeground_Closed      = IM_COL32(0, 255, 0, 128);
    ImU32  annotationNodeWindowBg         = IM_COL32(128, 128, 128, 128);
    bool   annotated                      = true;
    int    pageUpScrollStep               = 20;
    int    pageDownScrollStep             = -20;
    int    mouseScrollMultiplier          = 10;
    int    annotationNodeWidth            = 200;
    int    laneRowPadding                 = 6;
    ImVec2 gridViewport;


    DESC_FIELDS(
        StoryGridConfig,
        (foldCellHoverBackground_Open,
         foldCellForeground_Open,
         foldCellHoverBackground_Closed,
         foldCellForeground_Closed,
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

#define STORY_GRID_MSG_SCOPE(__ctx, __message)                            \
    __ctx.message(__message);                                             \
    auto BOOST_PP_CAT(__scope, __COUNTER__) = __ctx.scopeLevel();

struct StoryGridHistory {
    org::ImmAstVersion ast;
};

struct StoryGridState {
    UnorderedMap<int, UnorderedMap<Vec<int>, bool>> folded;
    DESC_FIELDS(StoryGridState, (folded));
};


struct StoryGridModel {
    Vec<StoryGridHistory>    history;
    StoryGridGraph           rectGraph;
    StoryGridContext         ctx;
    ImVec2                   shift{};
    Opt<ColaConstraintDebug> debug;
    /// \brief Root of the tree grid document in the `rectGraph.nodes`.
    int            docNodeIndex = 0;
    StoryGridState state;

    StoryGridHistory& getLastHistory() { return history.back(); }
    void apply(GridAction const& act, StoryGridConfig const& style);

    void updateGridState();

    /// \brief Get graph nodes associated with the current root grid node.
    Vec<org::graph::MapNode> getDocNodes();

    /// \brief Get existing block node position for AST adapter.
    int getFlatNodePos(org::ImmAdapter const& node);

    /// \brief Update full document using latest history data.
    void updateDocument(const StoryGridConfig& conf) {
        STORY_GRID_MSG_SCOPE(ctx, "Update full document");
        updateDocumentGraph(conf);
        rectGraph.updateStoryNodes(ctx, conf);
        updateDocumentLayout(conf);
    }

    /// \brief Reset model graph from scratch and populate the structure
    /// using information from the current history roots.
    void updateDocumentGraph(StoryGridConfig const& conf) {
        STORY_GRID_MSG_SCOPE(ctx, "Update document graph");
        updateDocumentSemanticGraph(conf);
        updateDocumentBlockGraph(conf);
    }

    /// \brief Reset map graph and populate the semantic node/edge
    /// connections in the `rectGraph.graph` part. Called by the
    /// `updateDocumentGraph`
    void updateDocumentSemanticGraph(StoryGridConfig const& conf) {
        STORY_GRID_MSG_SCOPE(ctx, "Update document semantic graph");
        rectGraph = StoryGridGraph{};
        auto& ast = getLastHistory().ast;
        rectGraph.updateSemanticGraph(ast.getRootAdapter(), ctx, conf);
    }

    /// \brief Rebuild block graph, populate edges and nodes in the
    /// `rectGraph.ir`. Called by the `updateDocumentGraph` part.
    void updateDocumentBlockGraph(StoryGridConfig const& conf) {
        STORY_GRID_MSG_SCOPE(ctx, "Update document block graph");
        rectGraph.updateNodeLanePlacement(ctx, conf);
    }

    void updateNodePositions(StoryGridConfig const& conf) {
        STORY_GRID_MSG_SCOPE(ctx, "Update document node positions");
        rectGraph.updateNodePositions(ctx, conf);
    }

    void updateDocumentLayout(StoryGridConfig const& conf) {
        STORY_GRID_MSG_SCOPE(ctx, "Update document layout");
        updateDocumentBlockGraph(conf);
        updateNodePositions(conf);
    }

    void applyChanges(StoryGridConfig const& conf);
};


Opt<json> story_grid_loop(
    GLFWwindow*        window,
    std::string const& file,
    Opt<json> const&   in_state,
    StoryGridConfig&   conf);

void run_story_grid_annotated_cycle(
    StoryGridModel&        model,
    const StoryGridConfig& conf);
void run_story_grid_cycle(
    StoryGridModel&        model,
    StoryGridConfig const& conf);
