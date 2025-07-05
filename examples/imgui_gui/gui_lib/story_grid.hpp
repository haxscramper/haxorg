#pragma once
// immer templates are instantiated in the haxorg library without debug
// checks, but building imgui application in debug mode causes a new series
// of instantiations and overwrites the symbols with debug enabled, causing
// constant assertion failures.
#include "block_graph.hpp"
// #define NDEBUG ORG_LIB_DEBUG_BUILD

#include <GLFW/glfw3.h>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include "imgui.h"
#include <haxorg/sem/ImmOrgGraph.hpp>
#include <adaptagrams/adaptagrams_ir.hpp>
#include <gui_lib/im_org_ui_common.hpp>
#include <gui_lib/node_grid_graph.hpp>
#include <gui_lib/imgui_utils.hpp>
#include <boost/bimap.hpp>

DECL_ID_TYPE_MASKED(StoryNode, StoryNodeId, std::size_t, 8);
struct StoryGridConfig;
struct StoryGridContext;
struct StoryGridModel;
struct TreeGridDocument;

struct TreeGridCell {

    struct None {
        DESC_FIELDS(None, (size));
        ImVec2 size;
    };

    struct Value {
        EditableOrgTextEntry value;
        DESC_FIELDS(Value, (value));
        std::string getFinalValue() { return value.getFinalValue(); }
    };

    SUB_VARIANTS(Kind, Data, data, getKind, None, Value);
    DESC_FIELDS(TreeGridCell, (data));

    Data data;

    static TreeGridCell from_adapter(
        org::imm::ImmAdapter  adapter,
        int                   width,
        EditableOrgText::Mode edit) {
        return TreeGridCell{TreeGridCell::Value{
            EditableOrgTextEntry::from_adapter(adapter, width, edit)}};
    }

    bool isEditing() const {
        return isValue() && getValue().value.isEditing();
    }

    ImVec2 getSize() const {
        return isNone() ? getNone().size : getValue().value.getSize();
    }

    std::string getFinalTextValue() { return getValue().getFinalValue(); }
    org::imm::ImmAdapter getOrigin() const {
        return getValue().value.getOrigin();
    }

    void render(
        StoryGridModel&        model,
        StoryNodeId const&     id,
        StoryGridConfig const& conf,
        ImVec2 const&          start,
        std::string const&     im_tag);
};

struct TreeGridColumn {
    std::string           name;
    int                   width = 120;
    EditableOrgText::Mode edit  = EditableOrgText::Mode::Multiline;
    DESC_FIELDS(TreeGridColumn, (name, width, edit));
};

struct TreeGridRow : hstd::SharedPtrApi<TreeGridRow> {
    int                                         flatIdx;
    org::imm::ImmAdapterT<org::imm::ImmSubtree> origin;
    hstd::UnorderedMap<hstd::Str, TreeGridCell> columns;
    hstd::Vec<TreeGridRow::Ptr>                 nested;
    std::weak_ptr<TreeGridRow>                  parent;
    bool                                        isVisible = true;
    bool                                        isOpen    = true;

    DESC_FIELDS(
        TreeGridRow,
        (columns, origin, flatIdx, nested, isVisible, isOpen));

    bool isEditing() const {
        return hstd::rs::any_of(columns, [](auto const& arg) -> bool {
            return arg.second.isEditing();
        });
    }

    bool hasParent() const { return !parent.expired(); }

    bool isInvisibleOrParentFolded() const {
        return !isVisible
            || (hasParent() && parent.lock()->isInvisibleOrParentFolded());
    }

    bool isShowingNested() const { return !nested.empty() && isOpen; }

    hstd::Vec<int> getOriginPath() const {
        hstd::Vec<int> idx;
        for (auto const& step : origin.flatPath().path) {
            if (step.isIndex()) { idx.push_back(step.getIndex().index); }
        }
        return idx;
    }

    void addNested(TreeGridRow::Ptr const& nest) {
        nested.push_back(nest);
        nested.back()->parent = weak_from_this();
    }

    hstd::Vec<Ptr> flatThisNested(bool withInvisible) const;
    int            getHeightDirect(int padding = 0) const;
    hstd::Opt<int> getHeight(int padding = 0) const;
    int            getHeightRecDirect(int padding = 0) const;
    hstd::Opt<int> getHeightRec(int padding = 0) const;

    TreeGridRow::Ptr getLastLeaf() const {
        if (nested.empty()) {
            return mshared_from_this();
        } else {
            return nested.back()->getLastLeaf();
        }
    }

    void render(
        TreeGridDocument*      doc,
        StoryGridModel&        model,
        StoryNodeId const&     id,
        StoryGridConfig const& conf,
        ImVec2 const&          start);
};


struct TreeGridDocument {
    hstd::Vec<TreeGridRow::Ptr> rows;
    hstd::Vec<TreeGridColumn>   columns;
    int                         rowPadding = 6;
    int                         colPadding = 6;
    /// \brief Width of leftmost column with tree folding indicators
    int            treeFoldWidth     = 120;
    int            tableHeaderHeight = 16;
    hstd::Vec<int> rowPositions;
    hstd::Vec<int> colPositions;

    org::imm::ImmAdapterT<org::imm::ImmDocument> origin;
    hstd::UnorderedMap<org::imm::ImmUniqId, int> rowOrigins;

    void updatePositions();

    int getRowYPos(TreeGridRow::Ptr const& r) {
        return getRowYPos(r->flatIdx);
    }
    int getRowYPos(int index) { return rowPositions.at(index); }

    int getColumnXPos(hstd::CR<hstd::Str> name) {
        return colPositions.at(getColumnIndex(name));
    }

    TreeGridCell& getExistingCell(int row, hstd::CR<hstd::Str> column) {
        return flatRows(true).at(row)->columns.at(column);
    }


    ImVec2 getCellPos(int row, hstd::CR<hstd::Str> column) {
        return ImVec2(getColumnXPos(column), getRowYPos(row));
    }

    ImVec2 getSize() const { return ImVec2(getWidth(), getHeight()); }

    int getColumnIndex(hstd::CR<hstd::Str> name) {
        auto iter = hstd::rs::find_if(
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

    TreeGridColumn& getColumn(hstd::CR<hstd::Str> name) {
        return columns.at(getColumnIndex(name));
    }

    hstd::Vec<TreeGridRow::Ptr> flatRows(bool withInvisible) const {
        hstd::Vec<TreeGridRow::Ptr> result;
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

    hstd::Opt<int> getRow(org::imm::ImmUniqId const& id) const {
        return rowOrigins.get(id);
    }

    int getNodeOffset(org::imm::ImmUniqId const& id) const {
        return rowPositions.at(rowOrigins.at(id));
    }

    int getHeight() const {
        return rowPositions.back()
             + rows.back()->getLastLeaf()->getHeight().value_or(0);
    }

    int getWidth() const {
        return colPositions.back() + columns.back().width;
    }

    hstd::Opt<int> getRowCenterOffset(int rowIdx) const {
        if (getRow(rowIdx)->isVisible) {
            return float(rowPositions.at(rowIdx))
                 + float(getRow(rowIdx)->getHeight().value()) / 2;
        } else {
            return std::nullopt;
        }
    }

    static TreeGridDocument from_root(
        const org::imm::ImmAdapter& node,
        const StoryGridConfig&      conf,
        StoryGridContext&           ctx);

    void render(
        StoryGridModel&        model,
        StoryNodeId const&     id,
        StoryGridConfig const& conf);

    DESC_FIELDS(TreeGridDocument, (rows, rowPositions, columns));
};


struct StoryGridModel;
struct StoryNode {
    using id_type = StoryNodeId;
    struct TreeGrid {
        TreeGridDocument node;
        DESC_FIELDS(TreeGrid, (node));
        ImVec2 getSize() const { return node.getSize(); }

        void render(
            StoryGridModel&        model,
            StoryNodeId const&     id,
            StoryGridConfig const& conf);
    };

    struct LinkList {
        struct Item {
            EditableOrgTextEntry text;
            org::imm::ImmAdapter node;
            DESC_FIELDS(Item, (text, node));
            ImVec2 getSize() const { return text.getSize(); }
            int    getHeight() const { return text.getHeight(); }
            int    getWidth() const { return text.getWidth(); }
        };
        hstd::Vec<Item>      items;
        ImVec2               size;
        org::imm::ImmAdapter origin;
        bool                 isSelected           = false;
        int                  imguiTableRowPadding = 5;
        DESC_FIELDS(LinkList, (items, size, isSelected, origin));

        int getRow(org::imm::ImmUniqId const& row) const {
            auto iter = hstd::rs::find_if(items, [&](Item const& i) {
                return i.node.uniq() == row;
            });
            LOGIC_ASSERTION_CHECK(iter != items.end(), "{}", row);
            return std::distance(items.begin(), iter);
        }

        int getRowOffset(org::imm::ImmUniqId const& row) const {
            return getRowOffset(getRow(row));
        }

        int getRowOffset(int row) const {
            int offset = 0;
            for (auto const& [row_idx, item] : enumerate(items)) {
                if (row_idx < row) { offset += item.getHeight(); }
            }
            return offset;
        }

        int getRowCenterOffset(int row) const {
            return getRowOffset(row) + items.at(row).getHeight() / 2.0f;
        }

        ImVec2 getSize() const { return ImVec2(getWidth(), getHeight()); }

        int getHeight() const {
            int result = 0;
            for (auto const& item : items) {
                result += imguiTableRowPadding + item.getHeight();
            }
            return result;
        }

        int getWidth() const {
            return hstd::rs::max(
                items | hstd::rv::transform([&](Item const& col) -> int {
                    return col.getWidth();
                }));
        }

        void render(
            StoryGridModel&        model,
            StoryNodeId const&     id,
            StoryGridConfig const& conf);
    };

    struct Text {
        ImVec2               size;
        org::imm::ImmAdapter origin;
        EditableOrgText      text;
        DESC_FIELDS(Text, (origin, size, text));
        ImVec2 getSize() const {
            return ImVec2(size.x, size.y + (text.is_editing ? 40 : 0));
        }

        void render(
            StoryGridModel&        model,
            StoryNodeId const&     id,
            StoryGridConfig const& conf);
    };

    ImVec2 getSize() const {
        return std::visit(
            hstd::overloaded{
                [](LinkList const& l) -> ImVec2 { return l.getSize(); },
                [](TreeGrid const& t) -> ImVec2 { return t.getSize(); },
                [](Text const& t) -> ImVec2 { return t.getSize(); },
            },
            data);
    }

    SUB_VARIANTS(Kind, Data, data, getKind, TreeGrid, Text, LinkList);
    Data data;
    bool isVisible = true;
    DESC_FIELDS(StoryNode, (data, isVisible));
};


struct StoryGridContext;
struct StoryGridConfig;

struct StoryGridGraph {
    struct SemGraphStore {
        org::imm::ImmAstContext::Ptr ctx;
        /// \brief Node IDs that are explicitly mapped to a node in the
        /// story grid.
        hstd::Vec<org::imm::ImmUniqId> graphGroupRoots;
        /// \brief Graph storage for specific document nodes that are
        /// targeting other parts of the document. Map graph entries are
        /// nested under parent nodes.
        org::graph::MapGraph::Ptr graph;

        /// \brief Mapping from map graph nodes to the actual parents that
        /// are going to be rendered in the story grid. This is done to
        /// handle cases like grid/list. In case of list the semantic graph
        /// contains nodes nodes for list *items*, not the list itself. But
        /// to render them on the scene and compute layout the list items
        /// must be grouped under a single parent, a list.
        hstd::UnorderedMap<org::imm::ImmUniqId, org::imm::ImmUniqId>
            annotationParents;
        DESC_FIELDS(
            SemGraphStore,
            (annotationParents, graph, graphGroupRoots));

        void setParent(
            org::imm::ImmUniqId const& nested,
            org::imm::ImmUniqId const& parent) {
            annotationParents.insert_or_assign(nested, parent);
        }

        org::imm::ImmUniqId getRoot(
            org::imm::ImmUniqId const& nested) const {
            auto res = annotationParents.get(nested).value_or(nested);
            LOGIC_ASSERTION_CHECK(
                graphGroupRoots.contains(res),
                "Node {} mapped to {}, but this node was not added as an "
                "explicit story node root in the sem graph",
                nested,
                res);
            return res;
        }

        void addStoryNode(org::imm::ImmUniqId const& id) {
            graphGroupRoots.push_back(id);
        }

        void addDocNode(
            org::imm::ImmAdapter const& node,
            StoryGridConfig const&      conf,
            StoryGridContext&           ctx);

        void addGridAnnotationNodes(
            TreeGridDocument const& doc,
            StoryGridContext&       ctx);

        void addDescriptionListNodes(
            org::imm::ImmAdapterT<org::imm::ImmList> const& list,
            StoryGridContext&                               ctx);

        void addFootnoteAnnotationNode(
            hstd::UnorderedSet<org::imm::ImmUniqId>& visited,
            org::imm::ImmUniqId const&               origin,
            org::imm::ImmAdapter const&              node,
            StoryGridContext&                        ctx);

        void addFootnoteAnnotationNode(
            org::imm::ImmUniqId const&  origin,
            org::imm::ImmAdapter const& node,
            StoryGridContext&           ctx) {
            hstd::UnorderedSet<org::imm::ImmUniqId> visited;
            addFootnoteAnnotationNode(visited, origin, node, ctx);
        }


        static SemGraphStore init(
            hstd::Vec<org::imm::ImmAdapter> const& root,
            StoryGridConfig const&                 conf,
            StoryGridContext&                      ctx);
    };


    struct FlatNodeStore : hstd::SharedPtrApi<FlatNodeStore> {
        struct Partition {
            hstd::Vec<hstd::Vec<org::graph::MapNode>> nodes;
            hstd::UnorderedMap<
                org::graph::MapNode,
                hstd::UnorderedSet<org::graph::MapNode>>
                edges;

            DESC_FIELDS(Partition, (nodes, edges));

            std::string toString(SemGraphStore const& semGraph) const;
        };

        struct Store {
            hstd::UnorderedMap<org::imm::ImmUniqId, StoryNodeId>
                                                     orgToFlatIdx;
            hstd::dod::Store<StoryNodeId, StoryNode> nodes;

            StoryNodeId add(
                const org::imm::ImmAdapter& node,
                const StoryGridConfig&      conf,
                StoryGridContext&           ctx);

            StoryNodeId add(StoryNode const& node) {
                auto id = nodes.add(node);
                setOrgNodeOrigin(node, id);
                return id;
            }

            hstd::generator<hstd::Pair<org::imm::ImmUniqId, StoryNodeId>> getOrgToFlatMapping()
                const {
                for (auto const& pair : orgToFlatIdx) { co_yield pair; }
            }

            void setOrgNodeOrigin(StoryNode const& n, StoryNodeId id);

            void setOrgNodeOrigin(
                org::imm::ImmUniqId const& id,
                StoryNodeId                flatIdx) {
                LOGIC_ASSERTION_CHECK(
                    !id.id.isNil(), "Cannot map NIL node to node");
                orgToFlatIdx.insert_or_assign(id, flatIdx);
            }

            template <typename Self>
            auto pairs(this Self&& self)
                -> hstd::generator<hstd::Pair<
                    StoryNodeId,
                    transfer_this_const_t<StoryNode*, Self>>> {
                const int size = self.nodes.size();
                for (int i = 0; i < size; ++i) {
                    auto id = StoryNodeId::FromIndex(i);
                    co_yield {id, &self.nodes.at(id)};
                }
            }

            hstd::generator<StoryNodeId> getNodeIds() const {
                for (auto const& [id, node] : nodes.pairs()) {
                    co_yield id;
                }
            }

            auto items() -> hstd::generator<StoryNode*> {
                const int size = nodes.size();
                for (int i = 0; i < size; ++i) {
                    auto id = StoryNodeId::FromIndex(i);
                    co_yield &nodes.at(id);
                }
            }

            /// \brief If grid graph has focused linked description list,
            /// hide all grid rows except ones that are directly targeted
            /// by the link list. If there is no focused list, then show
            /// all rows.
            void focusLinkListTargetRows(
                StoryGridContext&    ctx,
                SemGraphStore const& semGraph);


            auto&& getNodes(this auto&& self) { return self.nodes; }

            StoryNode& getStoryNode(StoryNodeId const& id) {
                return getNodes().at(id);
            }

            StoryNode const& getStoryNode(StoryNodeId const& id) const {
                return getNodes().at(id);
            }

            auto&& getStoryNode(
                this auto&&                s,
                org::imm::ImmUniqId const& id) {
                return s.getStoryNode(s.orgToFlatIdx.at(id));
            }


            hstd::Opt<StoryNodeId> getStoryNodeId(
                org::imm::ImmUniqId const& id) const {
                return orgToFlatIdx.get(id);
            }

            DESC_FIELDS(Store, (orgToFlatIdx, nodes));
        };

        struct Proxy {
            FlatNodeStore::Ptr source;
            boost::bimap<
                boost::bimaps::set_of<StoryNodeId>,
                boost::bimaps::set_of<StoryNodeId>>
                map;

            void add(
                StoryNodeId const& underlying,
                StoryNodeId const& proxy);

            hstd::generator<hstd::Pair<org::imm::ImmUniqId, StoryNodeId>> getOrgToFlatMapping()
                const {
                for (auto const& pair : source->getOrgToFlatMapping()) {
                    if (hasUnderlying(pair.second)) {
                        co_yield {pair.first, getProxy(pair.second)};
                    }
                }
            }

            bool hasUnderlying(StoryNodeId const& id) const {
                return map.left.find(id) != map.left.end();
            }

            bool hasProxy(StoryNodeId const& id) const {
                return map.right.find(id) != map.right.end();
            }

            hstd::generator<StoryNodeId> getNodeIds() const {
                for (auto const& pair : map) { co_yield pair.right; }
            }

            template <typename Self>
            hstd::generator<hstd::Pair<StoryNodeId, transfer_this_const_t<StoryNode*, Self>>> pairs(
                this Self&& self) {
                for (auto const& id : self.getNodeIds()) {
                    co_yield {id, &self.getStoryNode(id)};
                }
            }

            StoryNodeId getProxy(StoryNodeId const& underlying) const {
                auto it = map.left.find(underlying);
                LOGIC_ASSERTION_CHECK(
                    it != map.left.end(),
                    "No mapped proxy for underlying node {}",
                    underlying);

                return it->second;
            }

            StoryNodeId getUnderlying(StoryNodeId const& proxy) const {
                auto it = map.right.find(proxy);
                LOGIC_ASSERTION_CHECK(
                    it != map.right.end(),
                    "No underlying node for proxy {}",
                    proxy);

                return it->first;
            }

            DESC_FIELDS(Proxy, (source, map));

            StoryNode&       getStoryNode(StoryNodeId const& id);
            StoryNode const& getStoryNode(StoryNodeId const& id) const;

            hstd::Opt<StoryNodeId> getStoryNodeId(
                org::imm::ImmUniqId const& id) const {
                auto mapped = source->getStoryNodeId(id);
                if (mapped && hasProxy(mapped.value())) {
                    return getProxy(mapped.value());
                } else {
                    return std::nullopt;
                }
            }
        };


        SUB_VARIANTS(Kind, Data, data, getKind, Proxy, Store);
        Data data;
        DESC_FIELDS(FlatNodeStore, (data));

        hstd::Vec<org::graph::MapNode> getInitialNodes(
            StoryGridContext&    ctx,
            SemGraphStore const& semGraph) const;


        static FlatNodeStore::Ptr init_store(
            SemGraphStore const&   semGraph,
            StoryGridContext&      ctx,
            StoryGridConfig const& conf);

        static FlatNodeStore::Ptr init_proxy(
            FlatNodeStore::Ptr const& prev,
            SemGraphStore const&      semGraph,
            StoryGridContext&         ctx,
            StoryGridConfig const&    conf);

        bool isVisible(const org::imm::ImmUniqId& id) const;


        Partition getPartition(
            StoryGridContext&    ctx,
            SemGraphStore const& semGraph) const;

        template <typename Self>
        hstd::generator<hstd::Pair<StoryNodeId, transfer_this_const_t<StoryNode*, Self>>> pairs(
            this Self&& self) {
            if (self.isStore()) {
                return self.getStore().pairs();
            } else {
                return self.getProxy().pairs();
            }
        }

        hstd::generator<hstd::Pair<org::imm::ImmUniqId, StoryNodeId>> getOrgToFlatMapping()
            const {
            if (isStore()) {
                return getStore().getOrgToFlatMapping();
            } else {
                return getProxy().getOrgToFlatMapping();
            }
        }

        auto&& getStoryNode(this auto&& self, StoryNodeId const& id) {
            if (self.isStore()) {
                return self.getStore().getStoryNode(id);
            } else {
                return self.getProxy().getStoryNode(id);
            }
        }

        hstd::Opt<StoryNodeId> getStoryNodeId(
            org::imm::ImmUniqId const& id) const {
            if (isStore()) {
                return getStore().getStoryNodeId(id);
            } else {
                return getProxy().getStoryNodeId(id);
            }
        }

        hstd::generator<StoryNodeId> getNodeIds() const {
            if (isStore()) {
                return getStore().getNodeIds();
            } else {
                return getStore().getNodeIds();
            }
        }
    };

    struct NodePositionStore;
    struct BlockGraphStore {
        LaneBlockGraph           ir;
        FlatNodeStore::Partition partition;
        boost::bimap<
            boost::bimaps::set_of<StoryNodeId>,
            boost::bimaps::set_of<BlockNodeId>>
            irMapping;

        DESC_FIELDS(BlockGraphStore, (ir, partition, irMapping));


        StoryNodeId toStory(BlockNodeId id) const {
            auto it = irMapping.right.find(id);
            LOGIC_ASSERTION_CHECK(
                it != irMapping.right.end(),
                "No mapping to block from {}",
                id);
            return it->second;
        }

        static BlockNodeId toInitialBlockId(StoryNodeId id) {
            return BlockNodeId::FromIndex(id.getIndex());
        }

        bool hasBlockForNode(StoryNodeId id) const {
            return irMapping.left.find(id) != irMapping.left.end();
        }

        BlockNodeId toBlock(StoryNodeId id) const {
            auto it = irMapping.left.find(id);
            LOGIC_ASSERTION_CHECK(
                it != irMapping.left.end(),
                "No mapping to block from {}",
                id);
            return it->second;
        }

        hstd::Opt<LaneNodePos> getBlockPos(StoryNodeId const& id) const {
            if (hasBlockForNode(id)) {
                return ir.getBlockPos(toBlock(id));
            } else {
                return std::nullopt;
            }
        }

        hstd::Opt<StoryNodeId> getStoryNodeId(
            LaneNodePos const& pos) const {
            auto idx = ir.getBlockId(pos);
            if (idx) {
                return StoryNodeId::FromIndex(idx.value().getIndex());
            } else {
                return std::nullopt;
            }
        }

        LaneNodePos addToLane(
            int                       laneIdx,
            StoryNodeId               id,
            StoryGridConfig const&    conf,
            FlatNodeStore::Ptr const& nodes);

        void setPartition(
            FlatNodeStore::Partition const& inPartition,
            FlatNodeStore::Ptr const&       storyNodes,
            SemGraphStore const&            semGraph,
            StoryGridConfig const&          conf,
            StoryGridContext&               ctx);


        /// \brief Mark edge and node visibility based on the current
        /// scroll positions. This function is called in the
        /// `updateDocumentLayout` and requires node positions to be
        /// computed before.
        void updateHiddenRowConnection(
            StoryGridConfig const&    conf,
            StoryGridContext&         ctx,
            SemGraphStore const&      semGraph,
            FlatNodeStore::Ptr const& storyNodes);

        void updateBlockNodes(
            StoryGridConfig const&    conf,
            StoryGridContext&         ctx,
            FlatNodeStore::Ptr const& storyNodes);

        /// \brief Sync IR block state with the provided story nodes.
        /// Assign current block visibility and check
        void updateBlockState(
            StoryGridConfig const&    conf,
            StoryGridContext&         ctx,
            SemGraphStore const&      semGraph,
            FlatNodeStore::Ptr const& storyNodes);

        static BlockGraphStore init(
            SemGraphStore const&      semGraph,
            FlatNodeStore::Ptr const& storyNodes,
            StoryGridContext&         ctx,
            StoryGridConfig const&    conf);
    };

    struct NodePositionStore {
        LaneBlockLayout                         lyt;
        hstd::UnorderedMap<StoryNodeId, ImVec2> nodePositions;
        hstd::Opt<ColaConstraintDebug>          debug;

        /// \brief Check if the story node has a position information. If
        /// the block node is hidden or went out of visible range, it is
        /// not going to have an associated position information.
        bool hasNode(StoryNodeId const& id) const {
            return nodePositions.contains(id);
        }

        ImVec2 at(StoryNodeId const& id) const {
            return nodePositions.at(id);
        }

        static NodePositionStore init(
            StoryGridContext&         ctx,
            FlatNodeStore::Ptr const& storyNodes,
            BlockGraphStore const&    blockGraph,
            StoryGridConfig const&    conf);

        DESC_FIELDS(NodePositionStore, (lyt, nodePositions, debug));
    };


    struct Layer {
        FlatNodeStore::Ptr flat;
        SemGraphStore      sem;
        BlockGraphStore    block;
        NodePositionStore  position;
        DESC_FIELDS(Layer, (flat, sem, block, position));

        SemGraphStore getSubgraph(
            StoryGridContext&      ctx,
            StoryGridConfig const& conf) const;

        void updateGeometry(StoryNodeId const& id) {
            StoryNode& node = flat->getStore().getStoryNode(id);
            if (node.isTreeGrid()) {
                node.getTreeGrid().node.updatePositions();
            }
        }

        void updateLinkListTargetRows(StoryGridContext& ctx) {
            flat->getStore().focusLinkListTargetRows(ctx, sem);
        }

        void updateStoryNodes(
            StoryGridContext&      ctx,
            StoryGridConfig const& conf) {
            flat = FlatNodeStore::init_store(sem, ctx, conf);
        }

        void updateSemanticGraph(
            hstd::Vec<org::imm::ImmAdapter> const& root,
            StoryGridContext&                      ctx,
            StoryGridConfig const&                 conf) {
            sem = SemGraphStore::init(root, conf, ctx);
        }

        /// \brief Rebuild block grid
        void updateNodeLanePlacement(
            StoryGridContext&      ctx,
            StoryGridConfig const& conf) {
            hstd::Vec<int> offset //
                = block.ir.lanes  //
                | hstd::rv::transform(hstd::get_field_get(
                    &LaneBlockStack::scrollOffset)) //
                | hstd::rs::to<hstd::Vec>();

            block = BlockGraphStore::init(sem, flat, ctx, conf);

            for (int i = 0; i < block.ir.lanes.size(); ++i) {
                if (offset.has(i)) {
                    block.ir.lanes.at(i).scrollOffset = offset.at(i);
                }
            }
        }

        void updateNodePositions(
            StoryGridContext&      ctx,
            StoryGridConfig const& conf) {
            position = NodePositionStore::init(ctx, flat, block, conf);
        }
    };

    Layer            base;
    hstd::Opt<Layer> subgraph;

    Layer const& getLayer() const {
        if (subgraph) {
            return subgraph.value();
        } else {
            return base;
        }
    }

    Layer& getLayer() {
        if (subgraph) {
            return subgraph.value();
        } else {
            return base;
        }
    }

    // clang-format off
    void cascadeSemanticUpdate(hstd::Vec<org::imm::ImmAdapter> const &root, StoryGridContext &ctx, StoryGridConfig const &conf);
    void cascadeStoryNodeUpdate(StoryGridContext &ctx, StoryGridConfig const &conf);
    void cascadeBlockGraphUpdate(StoryGridContext &ctx, StoryGridConfig const &conf);
    void cascadeGeometryUpdate(StoryNodeId const &id, StoryGridContext &ctx, StoryGridConfig const &conf);
    void cascadeScrollingUpdate(const ImVec2 &graphPos, float direction, StoryGridContext &ctx, StoryGridConfig const &conf);
    void cascadeNodePositionsUpdate(StoryGridContext &ctx, StoryGridConfig const &conf);
    void cascadeLinkListTargetsUpdate(StoryGridContext &ctx, StoryGridConfig const &conf);
    // clang-format on

    ImVec2 getPosition(StoryNodeId id) const {
        return getLayer().position.at(id);
    }

    ImVec2 getPosition(LaneNodePos const& pos) const {
        return getLayer().position.at(
            getLayer().block.getStoryNodeId(pos).value());
    }

    bool isNodeVisible(StoryNodeId const& id) {
        return getLayer().block.getBlockPos(id).has_value();
    }

    hstd::Vec<StoryNode*> getGridNodes() {
        hstd::Vec<StoryNode*> res;
        for (auto const& node : getLayer().flat->getStore().items()) {
            if (node->isTreeGrid()) { res.push_back(node); }
        }
        return res;
    }

    bool isVisible(org::imm::ImmUniqId const& id) const;

    DESC_FIELDS(StoryGridGraph, (base, subgraph));

    hstd::generator<hstd::Pair<StoryNodeId, StoryNode*>> getPositionedStoryNodes() {
        for (auto const& [node_id, node] : getLayer().flat->pairs()) {
            if (getLayer().position.hasNode(node_id)) {
                co_yield {node_id, node};
            }
        }
    }

    StoryNode& getStoryNode(LaneNodePos const& pos) {
        return getLayer().flat->getStoryNode(getStoryNodeId(pos).value());
    }

    StoryNode& getStoryNode(StoryNodeId idx) {
        return getLayer().flat->getStoryNode(idx);
    }

    StoryNode const& getStoryNode(StoryNodeId idx) const {
        return getLayer().flat->getStoryNode(idx);
    }

    StoryNode const& getStoryNode(LaneNodePos const& idx) const {
        return getLayer().flat->getStoryNode(getStoryNodeId(idx).value());
    }

    hstd::Opt<LaneNodePos> getBlockPos(StoryNodeId idx) const {
        return getLayer().block.getBlockPos(idx);
    }

    hstd::Opt<StoryNodeId> getStoryNodeId(LaneNodePos const& node) const {
        return getLayer().block.getStoryNodeId(node);
    }

    hstd::Opt<StoryNodeId> getStoryNodeId(
        org::imm::ImmUniqId const& id) const {
        return getLayer().flat->getStoryNodeId(id);
    }

    hstd::Opt<LaneNodePos> getBlockNodePos(org::imm::ImmUniqId const& id) {
        auto flat = getStoryNodeId(id);
        if (flat) {
            return getLayer().block.getBlockPos(flat.value());
        } else {
            return std::nullopt;
        }
    }
};

struct GridAction {
    struct EditCell {
        EditableOrgText::Result edit;
        StoryNodeId             id;
        DESC_FIELDS(EditCell, (edit, id));
    };

    struct EditNodeText {
        EditableOrgText::Result edit;
        StoryNodeId             id;
        DESC_FIELDS(EditNodeText, (id, edit));
    };

    struct Scroll {
        ImVec2 pos;
        float  direction;
        DESC_FIELDS(Scroll, (pos, direction));
    };


    struct LinkListClick {
        StoryNodeId id;
        DESC_FIELDS(LinkListClick, (id));
    };

    struct RowFolding {
        bool        isOpen;
        int         flatIdx;
        StoryNodeId id;
        DESC_FIELDS(RowFolding, (isOpen, flatIdx, id));
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
        EditNodeText);

    Data data;
    DESC_FIELDS(GridAction, (data));
};

/// \brief All the configuration parameters for rendering the story
/// grid, static variables that change the logic of the render, data
/// model updates etc., but are not change-able from within the UI part
/// of the application.
struct StoryGridConfig {
    LaneBlockGraphConfig           blockGraphConf;
    hstd::Func<TreeGridDocument()> getDefaultDoc;

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
    bool   renderDebugOverlay = false;


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

/// \brief Highly mutable context variable that is passed to all
/// rendering elements to collect actions.
struct StoryGridContext : hstd::OperationsTracer {

    DESC_FIELDS(StoryGridContext, (actions));

    hstd::Vec<GridAction> actions;

    void action(
        GridAction::Data const& act,
        int                     line     = __builtin_LINE(),
        char const*             function = __builtin_FUNCTION(),
        char const*             file     = __builtin_FILE()) {
        GridAction ga{act};
        message(hstd::fmt("Action {}", ga), line, function, file);
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
    org::imm::ImmAstVersion ast;
};

struct StoryGridState {
    hstd::UnorderedMap<int, hstd::UnorderedMap<hstd::Vec<int>, bool>>
        folded;
    DESC_FIELDS(StoryGridState, (folded));
};


struct StoryGridModel {
    EditableOrgDocGroup* history;
    StoryGridGraph       graph;
    StoryGridContext     ctx;
    ImVec2               shift{};

    EditableOrgDocGroup::RootGroup documents;

    StoryGridModel(EditableOrgDocGroup* h) : history{h} {}

    /// \brief Root of the tree grid document in the `rectGraph.nodes`.
    int            docNodeIndex = 0;
    StoryGridState state;
    void apply(GridAction const& act, StoryGridConfig const& style);
    void updateGridState();

    void addDocument(DocRootId root) { documents.add(root); }

    /// \brief Get graph nodes associated with the current root grid
    /// node.
    hstd::Vec<org::graph::MapNode> getDocNodes();

    /// \brief Get existing block node position for AST adapter.
    int getFlatNodePos(org::imm::ImmAdapter const& node);

    /// \brief Update full document using latest history data.
    void rebuild(const StoryGridConfig& conf) {
        STORY_GRID_MSG_SCOPE(
            ctx,
            hstd::fmt(
                "Update full document, history size {}",
                history->history.size()));
        graph.cascadeSemanticUpdate(
            history->getAdapters(documents), ctx, conf);
    }

    void applyChanges(StoryGridConfig const& conf);
};


hstd::Opt<json> story_grid_loop(
    GLFWwindow*                 window,
    const hstd::Vec<hstd::Str>& file,
    hstd::Opt<json> const&      in_state,
    StoryGridConfig&            conf);

void run_story_grid_annotated_cycle(
    StoryGridModel&        model,
    const StoryGridConfig& conf);
void run_story_grid_cycle(
    StoryGridModel&        model,
    StoryGridConfig const& conf);
