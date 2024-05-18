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

    OrgBoxId box;  ///< Original box ID for the node
    Kind     kind; ///< Structural type of the original node.
};


/// Mind map graph property
struct OrgGraphEdge {
    DECL_DESCRIBED_ENUM(Kind, SubtreeId, Footnote);
    Kind kind; ///< What is the context for the edge creation
    /// Link description field can be reused or, for description list
    /// items, this field contains a newly created statment list
    Opt<sem::SemId<sem::Org>> description;
    /// \brief Original link used to create the graph edge. Used to return
    /// an edge to unresolved state when target is deleted. When source is
    /// deleted the edge is simply dropped.
    sem::SemId<sem::Link> link;
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

/// Type of the individual graph element that model can provide
enum class OrgGraphElementKind
{
    Node,     ///< Base mode, created from some org-mode box in the store
    Edge,     ///< Link between two boxes in the store
    Subgraph, ///< Grouping element, provided by the proxy layout model
};

/// Base data provider model for all interactions with the graph. Wraps
/// around boost graph and exposes its nodes and edges as a flat list of
/// elements.
struct OrgGraph : public QAbstractListModel {
  private:
    Q_OBJECT
  public:
    /// Base data structure for the whole mind map. The parameters are
    /// not configurable,
    using Graph = boost::adjacency_list<
        boost::vecS,
        boost::vecS,
        boost::bidirectionalS,
        OrgGraphNode,
        OrgGraphEdge>;

    using GraphTraits = boost::graph_traits<Graph>;
    using VDesc       = GraphTraits::vertex_descriptor;
    using EDesc       = GraphTraits::edge_descriptor;

    OrgGraph(OrgStore* store, QObject* parent)
        : QAbstractListModel(parent), store(store) {
        QObject::connect(
            store, &OrgStore::boxReplaced, this, &OrgGraph::replaceBox);
        QObject::connect(
            store, &OrgStore::boxDeleted, this, &OrgGraph::deleteBox);
        QObject::connect(
            store, &OrgStore::boxAdded, this, &OrgGraph::addBox);
    }

    Graph                         g;
    UnorderedMap<OrgBoxId, VDesc> boxToVertex;
    OrgStore*                     store;
    /// List of edges and nodes for a graph to maintain stable flat list of
    /// nodes.
    Vec<EDesc> edges;
    Vec<VDesc> nodes;

    /// Mapping from the subtree to the box IDs. This field is dynamically
    /// updated as new nodes are removed or added to the graph
    UnorderedMap<Str, Vec<OrgBoxId>> subtreeIds;
    UnorderedMap<Str, Vec<OrgBoxId>> footnoteTargets;

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

    Pair<OrgGraph::VDesc, OrgGraph::VDesc> sourceTargetAt(
        QModelIndex index) const {
        auto eDesc = getEdgeDesc(index.row());
        return std::make_pair<OrgGraph::VDesc, OrgGraph::VDesc>(
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
    int numNodes() const { return boost::num_vertices(g); }

    int numEdges() const { return boost::num_edges(g); }

    /// Graph edge descriptor for a specific row
    EDesc getEdgeDesc(int row) const { return edges.at(row - numNodes()); }

    EDesc getEdgeDesc(QModelIndex index) const {
        return getEdgeDesc(index.row());
    }

    bool hasBoxDesc(CR<OrgBoxId> id) const {
        return boxToVertex.contains(id);
    }

    VDesc getBoxDesc(CR<OrgBoxId> id) const { return boxToVertex.at(id); }

    VDesc getEdgeSource(EDesc d) const { return boost::source(d, g); }

    VDesc getEdgeTarget(EDesc d) const { return boost::target(d, g); }

    VDesc getNodeDesc(int idx) const { return nodes.at(idx); }

    VDesc getNodeDesc(QModelIndex index) const {
        return getNodeDesc(index.row());
    }

    /// \brief Store box for a row
    OrgBoxId getBox(int row) const {
        return getNodeProp(getNodeDesc(row)).box;
    }

    /// Find model row number for a graph vertex descriptor
    int getDescIndex(VDesc desc) const {
        for (auto const& it : enumerator(nodes)) {
            if (it.value() == desc) { return it.index(); }
        }

        throw std::logic_error("vertex does not exist in graph");
    }

    OrgGraphEdge& getEdgeProp(EDesc desc) { return g[desc]; }

    OrgGraphNode& getNodeProp(VDesc desc) { return g[desc]; }

    /// \brief Sem node from a graph vertex.
    sem::SemId<sem::Org> getNodeSem(VDesc desc) const {
        return store->node(getNodeProp(desc).box);
    }

    OrgGraphEdge const& getEdgeProp(EDesc desc) const { return g[desc]; }

    OrgGraphNode const& getNodeProp(VDesc desc) const { return g[desc]; }

    /// \brief Add new edge between two boxes, register it in all fields
    /// and emit model update signals.
    EDesc addEdge(VDesc source, VDesc target) {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        EDesc e;
        bool  inserted;
        boost::tie(e, inserted) = boost::add_edge(source, target, g);
        if (inserted) { edges.push_back(e); }
        endInsertRows();
        emit edgeAdded(e);
        return e;
    }

    /// \brief Add new vertex for a box, register it in all fields. This
    /// only registers a vertex in a graph. To do full box content
    /// registration call `addBox()`
    VDesc addVertex(CR<OrgBoxId> box) {
        beginInsertRows(QModelIndex(), nodes.size(), nodes.size());
        VDesc v = boost::add_vertex(g);
        nodes.push_back(v);
        endInsertRows();
        g[v].box         = box;
        boxToVertex[box] = v;
        emit nodeAdded(v);
        return v;
    }


    void removeVertex(VDesc vertex);

    /// \brief Clear cached values for edge rows and push a new list of
    /// edges. Called when graph vertex descriptors might have been
    /// invalidated.
    void rebuildEdges() {
        edges.clear();
        Graph::edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = boost::edges(g); ei != ei_end;
             ++ei) {
            edges.push_back(*ei);
        }
    }

    /// \brief Get property of the first edge between source and target.
    /// Mainly for testing purposes. Can raise range error if there are no
    /// edges between provided nodes.
    OrgGraphEdge& out_edge0(CR<OrgBoxId> source, CR<OrgBoxId> target) {
        return getEdgeProp(out_edges(source, target).at(0));
    }

    Vec<EDesc> out_edges(
        CR<VDesc>      source,
        CR<Opt<VDesc>> target = std::nullopt) {
        Vec<EDesc> result;

        Graph::out_edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = boost::out_edges(source, g);
             ei != ei_end;
             ++ei) {
            if (!target || boost::target(*ei, g) == *target) {
                result.push_back(*ei);
            }
        }

        return result;
    }

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
        CR<Opt<VDesc>> source = std::nullopt) {
        Vec<EDesc> result;

        Graph::in_edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = boost::in_edges(target, g);
             ei != ei_end;
             ++ei) {
            if (!source || boost::source(*ei, g) == *source) {
                result.push_back(*ei);
            }
        }

        return result;
    }

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

    struct EdgeData {
        VDesc        source;
        VDesc        target;
        OrgGraphEdge spec;
    };

    /// Link node in the mind map pending resolution. Might be due to
    /// an error, might be because an element have not been added yet.
    struct UnresolvedLink {
        sem::SemId<sem::Link> link;
        /// Link description at the time when an element was added.
        Opt<sem::SemId<sem::Org>> description;
    };

    struct ResolveResult {
        Vec<EdgeData>       establishedEdges;
        Vec<UnresolvedLink> missingLinks;
    };

    /// Iterate over all unresolved links visited so far and *try to* fix
    /// them. Does not guarantee to resolve all the links. Called when a
    /// new node is added to the graph.
    ResolveResult updateUnresolved(
        OrgBoxId             unresolved_source,
        CVec<UnresolvedLink> list) const;

    /// Map each box to a list of unresolved outgoing links. This field is
    /// mutated as boxes are added or removed from the tree.
    UnorderedMap<OrgBoxId, Vec<UnresolvedLink>> unresolved;


    void insertNewNode(CR<OrgBoxId> box);

    void insertUnresolvedEdges() {
        for (auto const& id : unresolved.keys()) {
            auto resolve_result = updateUnresolved(id, unresolved.at(id));
            if (resolve_result.missingLinks.empty()) {
                unresolved.erase(id);
            } else {
                unresolved.at(id) = resolve_result.missingLinks;
            }
            for (auto const& e : resolve_result.establishedEdges) {
                auto desc = addEdge(e.source, e.target);
                g[desc]   = e.spec;
            }
        }
    }

  public slots:
    void replaceBox(CR<OrgBoxId> before, CR<OrgBoxId> replace) {
        deleteBox(before);
        addBox(replace);
    }

    void addBox(CR<OrgBoxId> box) {
        insertNewNode(box);
        insertUnresolvedEdges();
    }

    void deleteBox(CR<OrgBoxId> deleted);

  signals:
    void nodeAdded(VDesc desc);
    void nodeRemoved(VDesc desc);
    void edgeAdded(EDesc edge);
    void edgeRemoved(EDesc edge);
    /// \brief Store box value was replaced with something differrent. No
    /// new nodes added to the graph, potentially edges added to the graph.
    void nodeUpdated(VDesc desc);
};

template <>
struct std::formatter<OrgGraph::EDesc> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const OrgGraph::EDesc& p, FormatContext& ctx) const {
        fmt_ctx(p.m_source, ctx);
        fmt_ctx("-", ctx);
        return fmt_ctx(p.m_target, ctx);
    }
};

Q_DECLARE_FMT_METATYPE(OrgGraph::VDesc);
Q_DECLARE_FMT_METATYPE(OrgGraph::EDesc);


/// \brief Helper type to provide more convenient API for accessing
/// different node element properties. NOTE: Holds the reference to a
/// wrapped widget, is not intended as a copyable type to store/work with.
/// Only as an more type-safe entry point to the API.
struct OrgGraphIndex {
    QModelIndex const& index;
    OrgGraphIndex(QModelIndex const& index) : index(index) {}

    operator QModelIndex const&() const { return index; }

    OrgGraph::VDesc getVDesc() const {
        return qindex_get<OrgGraph::VDesc>(index, OrgGraphRoles::NodeDesc);
    }

    OrgGraph::EDesc getEDesc() const {
        return qindex_get<OrgGraph::EDesc>(index, OrgGraphRoles::EdgeDesc);
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

    Pair<OrgGraph::VDesc, OrgGraph::VDesc> getSourceTarget() const {
        return qindex_get<Pair<OrgGraph::VDesc, OrgGraph::VDesc>>(
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
};

/// \brief Filter nodes from a graph using callback predicates.
struct OrgGraphFilterProxy : public QSortFilterProxyModel {
  private:
    Q_OBJECT
  public:
    using AcceptNodeCb = Func<bool(OrgGraph::VDesc const&)>;
    using AcceptEdgeCb = Func<bool(OrgGraph::EDesc const&)>;

    AcceptNodeCb accept_node; ///< Individual node is ok
    AcceptEdgeCb accept_edge; ///< Individual edge is ok. If source/target
                              ///< for edge are not OK nodes the edge is
                              ///< also filtered.

    virtual bool filterAcceptsRow(
        int                source_row,
        const QModelIndex& source_parent) const override {
        QModelIndex index = sourceModel()->index(
            source_row, 0, source_parent);
        if (qindex_get<bool>(index, OrgGraphRoles::IsNode)) {
            return accept_node(qindex_get<OrgGraph::VDesc>(
                index, OrgGraphRoles::NodeDesc));
        } else {
            auto [source, target] = qindex_get<
                Pair<OrgGraph::VDesc, OrgGraph::VDesc>>(
                index, OrgGraphRoles::SourceAndTarget);
            // Avoid dangling edges with missing source/target nodes.
            return accept_node(source) //
                && accept_node(target)
                && accept_edge(qindex_get<OrgGraph::EDesc>(
                    index, OrgGraphRoles::EdgeDesc));
        }
    }
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
struct OrgGraphLayoutProxy : public QSortFilterProxyModel {
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

    OrgGraphLayoutProxy(
        OrgStore*        store,
        CR<LayoutConfig> size,
        QObject*         parent)
        : QSortFilterProxyModel(parent), store(store), config(size) {}


    ElementLayout const& getElement(QModelIndex const& idx) const {
        Q_ASSERT_X(
            currentLayout.data.has(idx.row()),
            "getElement",
            fmt("No element for index {}", idx.row()));
        return currentLayout.data[idx.row()];
    }

    FullLayout currentLayout;
    FullLayout getFullLayout() const;
    void       updateCurrentLayout() { currentLayout = getFullLayout(); }


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

    virtual int rowCount(const QModelIndex& parent) const override {
        if (parent.isValid()) {
            return 0;
        } else {
            return currentLayout.data.size();
        }
    }

    virtual QModelIndex index(
        int                row,
        int                column,
        const QModelIndex& parent) const override {
        if (sourceModel()->hasIndex(row, column, parent)) {
            return QSortFilterProxyModel::index(row, column, parent);
        } else {
            return createIndex(row, column);
        }
    }
};


Q_DECLARE_METATYPE(OrgGraphLayoutProxy::Subgraph);

inline QDebug operator<<(
    QDebug                               debug,
    const OrgGraphLayoutProxy::Subgraph& t) {
    QDebugStateSaver saver(debug);
    debug.nospace() << "OrgGraphLayoutProxy::Subgraph(" << t.name << " "
                    << t.bbox << ")";
    return debug;
}
