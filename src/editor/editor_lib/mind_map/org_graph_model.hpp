#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <editor/editor_lib/document/org_document_model.hpp>
#include <QObject>
#include <hstd/system/macros.hpp>
#include <QAbstractItemModel>
#include <editor/editor_lib/common/app_utils.hpp>
#include <editor/editor_lib/mind_map/org_graph_layout.hpp>
#include <QPainterPath>
#include <QTextDocument>
#include <hstd/stdlib/Set.hpp>

namespace org::mind_map {


struct GraphLink {
    /// Link description field can be reused or, for description list
    /// items, this field contains a newly created statment list
    Opt<sem::SemId<sem::Org>> description;
    /// \brief Original link used to create the graph edge. Used to return
    /// an edge to unresolved state when target is deleted. When source is
    /// deleted the edge is simply dropped.
    sem::SemId<sem::Link> link;

    bool operator==(GraphLink const& other) const {
        Q_ASSERT(!link.isNil());
        Q_ASSERT(!other.link.isNil());

        sem::Link const& lhs = *link.value;
        sem::Link const& rhs = *other.link.value;

        if (lhs.getLinkKind() != rhs.getLinkKind()) {
            return false;
        } else {
            switch (lhs.getLinkKind()) {
                case sem::Link::Kind::Id:
                    return lhs.getId().text == rhs.getId().text;
                case sem::Link::Kind::Footnote:
                    return lhs.getFootnote().target
                        == rhs.getFootnote().target;
                default: qFatal("TODO");
            }
        }
    }

    DESC_FIELDS(GraphLink, (link, description));
};

/// \brief Property for the org-mode graph structure
struct OrgGraphNode {
    DECL_DESCRIBED_ENUM(
        Kind,
        Subtree,
        Document,
        Paragraph,
        Footnote,
        List,
        ListItem);

    OrgBoxId       box;  ///< Original box ID for the node
    Kind           kind; ///< Structural type of the original node.
    Opt<Str>       subtreeId;
    Opt<Str>       footnoteName;
    Vec<GraphLink> unresolved;
    DESC_FIELDS(
        OrgGraphNode,
        (box, kind, subtreeId, footnoteName, unresolved));
};


/// Mind map graph property
struct OrgGraphEdge {
    DECL_DESCRIBED_ENUM(Kind, SubtreeId, Footnote);
    Kind      kind; ///< What is the context for the edge creation
    GraphLink link;
    DESC_FIELDS(OrgGraphEdge, (kind, link));
};

/// Model roles shared between org graph model and proxy layouts that are
/// strapped on top of the flat list model. In addition to the roles listed
/// here, model also provides a regular display role that returns an HTML
/// formatted value of the node text or edge label.
enum class OrgGraphRoles
{
    OrgGraphModelRoles__FIRST__ = (int)SharedModelRoles::__LAST__ + 1,
    NodeShape, ///< Node shape in absolute coordinates after layout
    EdgeShape, ///< Edge spline in absolute coordinates after layout
    IsNode,    ///< Check if the index points to and edge or to a node.
    NodeDesc,  ///< Get node descriptor for an index
    EdgeDesc,  ///< Get edge descriptor for index
    SourceAndTarget, ///< Pair of vertex ID elements
    DebugDisplay, ///< String value for debug visualization of the content.
    SubnodeIndices, ///< Get list of model indixes for subnode.
                    ///< Returned indices come from the base graph
                    ///< model.
    ElementKind,    ///< Node, edge, or subgraph. Base model only provides
                    /// nodes and subgraphs.
    OrgGraphModelRoles__LAST__,
};

BOOST_DESCRIBE_ENUM(
    OrgGraphRoles,
    OrgGraphModelRoles__FIRST__,
    NodeShape,
    EdgeShape,
    IsNode,
    NodeDesc,
    EdgeDesc,
    SourceAndTarget,
    DebugDisplay,
    SubnodeIndices,
    ElementKind,
    OrgGraphModelRoles__LAST__);

/// Type of the individual graph element that model can provide
enum class OrgGraphElementKind
{
    Node,     ///< Base mode, created from some org-mode box in the store
    Edge,     ///< Link between two boxes in the store
    Subgraph, ///< Grouping element, provided by the proxy layout model
};

BOOST_DESCRIBE_ENUM(OrgGraphElementKind, Node, Edge, Subgraph);

/// Base data structure for the whole mind map. The parameters are
/// not configurable,
using BoostBase = boost::adjacency_list<
    boost::setS,
    boost::setS,
    boost::bidirectionalS,
    OrgGraphNode,
    OrgGraphEdge>;

using GraphTraits = boost::graph_traits<BoostBase>;
using VDesc       = GraphTraits::vertex_descriptor;
using EDesc       = GraphTraits::edge_descriptor;

/// Base data provider model for all interactions with the graph. Wraps
/// around boost graph and exposes its nodes and edges as a flat list of
/// elements.
struct Graph
    : public QAbstractListModel
    , public CRTP_qdebug<Graph> {

    friend class CRTP_qdebug;

  private:
    Q_OBJECT
  public:
    void connectStore() {
        QObject::connect(
            store, &OrgStore::boxReplaced, this, &Graph::replaceBox);
        QObject::connect(
            store, &OrgStore::boxDeleted, this, &Graph::deleteBox);
        QObject::connect(store, &OrgStore::boxAdded, this, &Graph::addBox);
    }

    Graph(OrgStore* store, QObject* parent)
        : QAbstractListModel(parent), store(store) {
        state.store = store;
    }

    OrgStore* store;

    int rowCount(
        const QModelIndex& parent = QModelIndex()) const override {
        if (parent.isValid()) {
            return 0;
        } else {
            return numNodes() + numEdges();
        }
    }

    bool isNode(CR<QModelIndex> index) const {
        return index.row() < numNodes();
    }

    Pair<VDesc, VDesc> sourceTargetAt(QModelIndex index) const {
        auto eDesc = getEdgeDesc(index.row());
        return std::make_pair<VDesc, VDesc>(
            getEdgeSource(eDesc), getEdgeTarget(eDesc));
    }

    /// Dump mind map structure in simple graphviz representation for
    /// debugging.
    std::string toGraphviz();

    /// \brief Get formatted HTML text for rendering in the graph view or
    /// computing size for.
    QString getDisplayText(CR<QModelIndex> index) const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)
        const override;

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[Qt::DisplayRole]                     = "DisplayRole";
        roles[(int)SharedModelRoles::IndexBox]     = "IndexBoxRole";
        roles[(int)OrgGraphRoles::IsNode]          = "IsNodeRole";
        roles[(int)OrgGraphRoles::NodeDesc]        = "NodeDescAtRole";
        roles[(int)OrgGraphRoles::EdgeDesc]        = "EdgeDescAtRole";
        roles[(int)OrgGraphRoles::SourceAndTarget] = "SourceAndTargetRole";
        roles[(int)OrgGraphRoles::DebugDisplay]    = "DebugDisplayRole";
        roles[(int)OrgGraphRoles::SubnodeIndices]  = "SubnodeIndicesRole";
        return roles;
    }

    /// Add all boxes registered in the store.
    void addFullStore() {
        Q_ASSERT(store != nullptr);
        for (auto const& box : store->boxes()) { addBox(box); }
    }

    /// \brief There is at least one edge between source and target boxes
    bool hasEdge(CR<OrgBoxId> source, CR<OrgBoxId> target) {
        return 0 < out_edges(source, target).size();
    }

    /// Full number of nodes in the graph.
    int numNodes() const { return state.nodes.size(); }
    int numEdges() const { return state.edges.size(); }

    /// Graph edge descriptor for a specific row
    EDesc getEdgeDesc(int row) const {
        return state.edges.at(row - numNodes());
    }

    EDesc getEdgeDesc(QModelIndex index) const {
        return getEdgeDesc(index.row());
    }

    bool hasBoxDesc(CR<OrgBoxId> id) const {
        return state.boxToVertex.contains(id);
    }

    VDesc getBoxDesc(CR<OrgBoxId> id) const {
        return state.boxToVertex.at(id);
    }

    VDesc getEdgeSource(EDesc d) const {
        return boost::source(d, state.g);
    }

    VDesc getEdgeTarget(EDesc d) const {
        return boost::target(d, state.g);
    }

    VDesc getNodeDesc(int idx) const { return state.nodes.at(idx); }

    VDesc getNodeDesc(QModelIndex index) const {
        return getNodeDesc(index.row());
    }

    /// \brief Store box for a row
    OrgBoxId getBox(int row) const {
        return getNodeProp(getNodeDesc(row)).box;
    }

    OrgBoxId getBox(VDesc vertex) const { return getNodeProp(vertex).box; }

    /// \brief Find model row number for a graph vertex descriptor. Finds
    /// element by O(n) iteration over all nodes.
    int getDescIndex(VDesc desc) const {
        for (auto const& it : enumerator(state.nodes)) {
            if (it.value() == desc) { return it.index(); }
        }

        throw std::logic_error("vertex does not exist in graph");
    }

    int getBoxIndex(CR<OrgBoxId> desc) const {
        return getDescIndex(getBoxDesc(desc));
    }

    OrgGraphEdge& getEdgeProp(EDesc desc) { return state.g[desc]; }
    OrgGraphEdge& getEdgeProp(CR<OrgBoxId> source, CR<OrgBoxId> target) {
        return getEdgeProp(out_edges(source, target).at(0));
    }

    OrgGraphNode& getNodeProp(VDesc desc) { return state.g[desc]; }

    /// \brief Sem getBoxedNode from a graph vertex.
    sem::SemId<sem::Org> getNodeSem(VDesc desc) const {
        return store->getBoxedNode(getNodeProp(desc).box);
    }

    OrgGraphEdge const& getEdgeProp(EDesc desc) const {
        return state.g[desc];
    }

    OrgGraphNode const& getNodeProp(VDesc desc) const {
        return state.g[desc];
    }


    OrgGraphNode const& getNodeProp(OrgBoxId desc) const {
        return state.g[state.boxToVertex.at(desc)];
    }


    /// \brief Get property of the first edge between source and target.
    /// Mainly for testing purposes. Can raise range error if there are no
    /// edges between provided nodes.
    OrgGraphEdge& out_edge0(CR<OrgBoxId> source, CR<OrgBoxId> target) {
        return getEdgeProp(out_edges(source, target).at(0));
    }

    Vec<EDesc> out_edges(
        CR<VDesc>      source,
        CR<Opt<VDesc>> target = std::nullopt);

    /// \brief get full list of edges between source and target. If the
    /// target is null return all outgoing edges for a source node.
    Vec<EDesc> out_edges(
        CR<OrgBoxId>      source,
        CR<Opt<OrgBoxId>> target = std::nullopt) {
        return out_edges(
            getBoxDesc(source),
            target ? std::make_optional(getBoxDesc(*target))
                   : std::nullopt);
    }

    Vec<EDesc> in_edges(
        CR<VDesc>      target,
        CR<Opt<VDesc>> source = std::nullopt);

    /// \brief Get full list of all nodes incoming to the target from the
    /// source. If the target is none, return full list of all edges
    /// incoming to the source.
    Vec<EDesc> in_edges(
        CR<OrgBoxId>      target,
        CR<Opt<OrgBoxId>> source = std::nullopt) {
        return in_edges(
            getBoxDesc(target),
            source ? std::make_optional(getBoxDesc(*source))
                   : std::nullopt);
    }

    // Graph modification API

    struct GraphStructureUpdate {
        Vec<EDesc> removed_edges;
        Vec<EDesc> added_edges;
        Opt<VDesc> removed_node = std::nullopt;
        Opt<VDesc> added_node   = std::nullopt;

        DESC_FIELDS(
            GraphStructureUpdate,
            (removed_edges, removed_node, added_edges, added_node));
    };

    struct ResolvedLink {
        GraphLink link;
        OrgBoxId  target;
        OrgBoxId  source;
        DESC_FIELDS(ResolvedLink, (link, target, source))
    };

    struct ResolveResult {
        OrgGraphNode      node;
        Vec<ResolvedLink> resolved;
        DESC_FIELDS(ResolveResult, (node, resolved));
    };

    struct State {
        bool debug = false;

        OrgStore*                     store;
        BoostBase                     g;
        UnorderedMap<OrgBoxId, VDesc> boxToVertex;
        /// List of edges and nodes for a graph to maintain stable flat
        /// list of nodes.
        Vec<EDesc> edges;
        Vec<VDesc> nodes;

        /// Mapping from the subtree to the box IDs. This field is
        /// dynamically updated as new nodes are removed or added to the
        /// graph
        UnorderedMap<Str, OrgBoxId> subtreeIds;
        UnorderedMap<Str, OrgBoxId> footnoteTargets;

        /// Map each box to a list of unresolved outgoing links. This field
        /// is mutated as boxes are added or removed from the tree.
        UnorderedSet<OrgBoxId> unresolved;

        GraphStructureUpdate addMutation(OrgGraphNode const& edit);
        GraphStructureUpdate delMutation(OrgGraphNode const& edit);

        /// Iterate over all unresolved links visited so far and *try to*
        /// fix them. Does not guarantee to resolve all the links. Called
        /// when a new node is added to the graph.
        ResolveResult     getUnresolvedEdits(CR<OrgGraphNode> edit) const;
        Opt<ResolvedLink> getResolveTarget(
            CR<OrgBoxId>  source,
            CR<GraphLink> link) const;

        DESC_FIELDS(
            State,
            (g, boxToVertex, edges, nodes, subtreeIds, footnoteTargets));
    };

    State state;

    /// \brief Compute an IR reprensetation of the box ID associated with a
    /// node if it should be inserted in a graph. Return nullopt if a node
    /// does not have a direct representation in the graph (description
    /// list item or elements nested in it etc.)
    Opt<OrgGraphNode> getNodeInsert(CR<OrgBoxId> box) const;


    void emitChanges(CR<GraphStructureUpdate> upd);

    void addBoxImpl(CR<OrgBoxId> box) {
        auto edits = getNodeInsert(box);
        if (edits) {
            auto upd = state.addMutation(edits.value());
            emitChanges(upd);
        }
    }

    void deleteBoxImpl(CR<OrgBoxId> deleted) {
        if (state.boxToVertex.contains(deleted)) {
            auto v   = state.boxToVertex.at(deleted);
            auto upd = state.delMutation(state.g[v]);
            emitChanges(upd);
        }
    }

  public slots:
    void replaceBox(CR<OrgBoxId> before, CR<OrgBoxId> replace) {
        emit layoutAboutToBeChanged();
        deleteBoxImpl(before);
        addBoxImpl(replace);
        emit layoutChanged();
    }

    void addBox(CR<OrgBoxId> box) {
        emit layoutAboutToBeChanged();
        addBoxImpl(box);
        emit layoutChanged();
    }

    void deleteBox(CR<OrgBoxId> deleted) {
        emit layoutAboutToBeChanged();
        deleteBoxImpl(deleted);
        emit layoutChanged();
    }

  signals:
    /// \brief Store box value was replaced with something differrent. No
    /// new nodes added to the graph, potentially edges added to the graph.
    void nodeUpdated(VDesc desc);

    void edgeAdded(EDesc desc);
    void edgeRemoved(EDesc desc);
    void nodeAdded(VDesc desc);
    void nodeRemoved(VDesc desc);
};


/// \brief Helper type to provide more convenient API for accessing
/// different node element properties. NOTE: Holds the reference to a
/// wrapped widget, is not intended as a copyable type to store/work with.
/// Only as an more type-safe entry point to the API.
struct GraphIndex {
    QModelIndex const& index;
    GraphIndex(QModelIndex const& index) : index(index) {}

    operator QModelIndex const&() const { return index; }

    VDesc getVDesc() const {
        return qindex_get<VDesc>(index, OrgGraphRoles::NodeDesc);
    }

    EDesc getEDesc() const {
        return qindex_get<EDesc>(index, OrgGraphRoles::EdgeDesc);
    }

    bool isNode() const {
        return qindex_get<bool>(index, OrgGraphRoles::IsNode);
    }

    OrgBoxId getBox() const {
        return qindex_get<OrgBoxId>(index, SharedModelRoles::IndexBox);
    }

    QString getDisplay() const {
        return qindex_get<QString>(index, Qt::DisplayRole);
    }

    Pair<VDesc, VDesc> getSourceTarget() const {
        return qindex_get<Pair<VDesc, VDesc>>(
            index, OrgGraphRoles::SourceAndTarget);
    }

    OrgGraphElementKind getKind() const {
        return qindex_get<OrgGraphElementKind>(
            index, OrgGraphRoles::ElementKind);
    }

    QList<QModelIndex> getSubnodes() const {
        return qindex_get<QList<QModelIndex>>(
            index, OrgGraphRoles::SubnodeIndices);
    }

    QString debug() const {
        return qindex_get<QString>(index, OrgGraphRoles::DebugDisplay);
    }
};

/// \brief Filter nodes from a graph using callback predicates.
struct GraphFilterProxy : public QSortFilterProxyModel {
  private:
    Q_OBJECT
  public:
    using AcceptNodeCb = Func<bool(VDesc const&)>;
    using AcceptEdgeCb = Func<bool(EDesc const&)>;

    AcceptNodeCb accept_node; ///< Individual node is ok
    AcceptEdgeCb accept_edge; ///< Individual edge is ok. If source/target
                              ///< for edge are not OK nodes the edge is
                              ///< also filtered.
    virtual bool filterAcceptsRow(
        int                source_row,
        const QModelIndex& source_parent) const override;

    int rowCount(
        const QModelIndex& parent = QModelIndex()) const override {
        int count = QSortFilterProxyModel::rowCount(parent);
        return count;
    }


    virtual void setSourceModel(QAbstractItemModel* sourceModel) override;
};

/// \brief Layout data provider for the graph. Implements node and edge
/// shape properties, adds new rows with graph cluster elements.
///
/// The model maintains an internal list of layout elements which is
/// effectively put 'on top' of the underlying graph data. The list of
/// elemens differs in size as it also contains subgraphs. Layout elements
/// are all populated and updated in a single layout run.
///
/// General control flow for this model is:
/// - Provide an underlying node/edge provider
/// - Call `updateCurrentLayout` to run the layout backend of choice
/// - Now the model can serve a new set of layout elements`
struct GraphLayoutProxy
    : public QSortFilterProxyModel
    , public CRTP_qdebug<GraphLayoutProxy> {

    friend class CRTP_qdebug;

  private:
    Q_OBJECT
  public:
    enum class Role
    {
        /// Get bounding box for the whole graph
        LayoutBBoxRole = (int)OrgGraphRoles::OrgGraphModelRoles__LAST__
                       + 1,
        Subgraph, ///< Get subgraph object
    };

    /// \brief Subgraph layout description.
    ///
    /// List of these objects is created automatically if layout is enabled
    /// and they are concatenated together after the node+edge rows.
    /// Clusters can be spatially nested, but the model returns them as a
    /// flat list, not as parent/child indices.
    struct Subgraph {
        Str name;   /// Subgraph description name, may be assigned
                    /// automatically.
        QRect bbox; /// Bounding box around subgraph content
        DESC_FIELDS(Subgraph, (name, bbox));
    };

    /// \brief Single entry for the layout
    struct ElementLayout {
        // Monostate used to identify an invalid default value of the
        // layout element.
        Variant<std::monostate, QRect, GraphLayoutIR::Edge, Subgraph> data;

        OrgGraphElementKind getKind() const {
            Q_ASSERT_X(
                !std::holds_alternative<std::monostate>(data),
                "getKind",
                "element layout not initialized");

            if (std::holds_alternative<QRect>(data)) {
                return OrgGraphElementKind::Node;
            } else if (std::holds_alternative<GraphLayoutIR::Edge>(data)) {
                return OrgGraphElementKind::Edge;
            } else {
                return OrgGraphElementKind::Subgraph;
            }
        }

        QRect const& getNode() const { return std::get<QRect>(data); }

        Subgraph const& getSubgraph() const {
            return std::get<Subgraph>(data);
        }

        GraphLayoutIR::Edge const& getEdge() const {
            return std::get<GraphLayoutIR::Edge>(data);
        }
    };

    using GetNodeSize       = Func<QSize(QModelIndex const& index)>;
    using GetSubgraphMargin = Func<Opt<int>(QModelIndex const&)>;


    /// \brief Layout algorithm configuration options.
    struct LayoutConfig {
        /// \brief Add grouping cluster for each individual subtree in the
        /// graph.
        bool        clusterSubtrees = false;
        GetNodeSize getNodeSize;
        /// If the node has a complex label, use this function to get its
        /// size
        GetNodeSize getEdgeLabelSize;
        /// Customize internal margin between subtree clusters and the
        /// content. Default margin is ~10
        Opt<GetSubgraphMargin> getSubgraphMargin;

        Graphviz::LayoutType graphvizLayout = Graphviz::LayoutType::Dot;
    };


    /// \brief current layout state
    struct FullLayout {
        /// \brief Full result of layout for all elements
        Vec<ElementLayout> data;
        /// \brief Bounding box for the main graph content
        QRect bbox;
        /// \brief Original layout content
        Variant<
            std::monostate,
            GraphLayoutIR::GraphvizResult,
            GraphLayoutIR::ColaResult //
            >
            original;
    };


    LayoutConfig config;
    OrgStore*    store;

    GraphLayoutProxy(
        OrgStore*        store,
        CR<LayoutConfig> size,
        QObject*         parent)
        : QSortFilterProxyModel(parent), store(store), config(size) {
        blockSignals(true);
        Q_ASSERT(connect(
            store,
            &OrgStore::beginBatchAdd,
            this,
            &GraphLayoutProxy::batchAddBegin,
            Qt::UniqueConnection));
        Q_ASSERT(connect(
            store,
            &OrgStore::endBatchAdd,
            this,
            &GraphLayoutProxy::batchAddEnd,
            Qt::UniqueConnection));
    }


    ElementLayout const& getElement(QModelIndex const& idx) const {
        Q_ASSERT_X(
            currentLayout.data.has(idx.row()),
            "getElement",
            fmt("No element for index {}", idx.row()));
        return currentLayout.data[idx.row()];
    }

    FullLayout currentLayout;
    FullLayout getFullLayout() const;

    void setNewLayout() { currentLayout = getFullLayout(); }

    virtual QVariant data(const QModelIndex& index, int role)
        const override;

    virtual QHash<int, QByteArray> roleNames() const override {
        auto base                           = sourceModel()->roleNames();
        base[(int)OrgGraphRoles::NodeShape] = "NodeShapeRole";
        base[(int)OrgGraphRoles::EdgeShape] = "EdgeShapeRole";
        base[(int)Role::Subgraph]           = "Subgraph";
        base[(int)Role::LayoutBBoxRole]     = "LayoutBBoxRole";
        return base;
    }

    virtual int rowCount(
        const QModelIndex& parent = QModelIndex()) const override {
        if (parent.isValid()) {
            return 0;
        } else {
            return currentLayout.data.size();
        }
    }

    virtual QModelIndex index(
        int                row,
        int                column = 0,
        const QModelIndex& parent = QModelIndex()) const override {
        if (sourceModel()->hasIndex(row, column, parent)) {
            return QSortFilterProxyModel::index(row, column, parent);
        } else {
            return createIndex(row, column);
        }
    }

    void connectModel() {
        Q_ASSERT(connect(
            sourceModel(),
            &QAbstractItemModel::layoutChanged,
            this,
            &GraphLayoutProxy::onLayoutChanged,
            Qt::UniqueConnection));
    }

    void resetLayoutData() {
        PERF_MMAP(__func__);
        blockSignals(false);
        emit layoutAboutToBeChanged();
        setNewLayout();
        emit dataChanged(
            index(0, 0, QModelIndex{}),
            index(rowCount(QModelIndex{}) - 1, 0, QModelIndex{}));
        emit layoutChanged();
        blockSignals(true);
    }

    bool isBatchAdd = false;

  public slots:
    void batchAddBegin() { isBatchAdd = true; }

    void batchAddEnd() {
        isBatchAdd = false;
        resetLayoutData();
    }

    void onLayoutChanged(
        const QList<QPersistentModelIndex>&  parents,
        QAbstractItemModel::LayoutChangeHint hint) {
        if (!isBatchAdd) { resetLayoutData(); }
    }
};
} // namespace org::mind_map

Q_DECLARE_METATYPE(org::mind_map::GraphLayoutProxy::Subgraph);

inline QDebug operator<<(
    QDebug                                           debug,
    const org::mind_map::GraphLayoutProxy::Subgraph& t) {
    QDebugStateSaver saver(debug);
    debug.nospace() << "OrgGraphLayoutProxy::Subgraph(" << t.name << " "
                    << t.bbox << ")";
    return debug;
}

template <>
struct std::formatter<org::mind_map::EDesc> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::mind_map::EDesc& p, FormatContext& ctx) const {
        fmt_ctx(p.m_source, ctx);
        fmt_ctx("-", ctx);
        return fmt_ctx(p.m_target, ctx);
    }
};

Q_DECLARE_FMT_METATYPE(org::mind_map::VDesc);
Q_DECLARE_FMT_METATYPE(org::mind_map::EDesc);
