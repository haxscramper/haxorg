#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <editor/editor_lib/org_document_model.hpp>
#include <QObject>
#include <hstd/system/macros.hpp>
#include <QAbstractItemModel>
#include <editor/editor_lib/app_utils.hpp>
#include <editor/editor_lib/org_graph_layout.hpp>
#include <QPainterPath>
#include <QTextDocument>

struct OrgGraphNode {
    DECL_DESCRIBED_ENUM(
        Kind,
        Subtree,
        Document,
        Paragraph,
        Footnote,
        List,
        ListItem);

    OrgBoxId box;
    Kind     kind;
};

struct OrgGraphEdge {
    DECL_DESCRIBED_ENUM(Kind, SubtreeId, Footnote);
    Kind                      kind;
    Opt<sem::SemId<sem::Org>> description;
};

/// Model roles shared between org graph model and proxy layouts that are
/// strapped on top of the flat list model.
enum OrgGraphModelRoles
{
    OrgGraphModelRoles__FIRST__ = SharedModelRoles::__LAST__ + 1,
    NodeShapeRole, ///< Node shape in absolute coordinates after layout
    EdgeShapeRole, ///< Edge spline in absolute coordinates after layout
    IsNodeRole,    ///< Check if the index points to and edge or to a node.
    NodeDescAtRole, ///< Get node descriptor for an index
    EdgeDescAtRole, ///< Get edge descriptor for index
    SourceAndTargetRole,
    DebugDisplayRole,

    OrgGraphModelRoles__LAST__,
};


struct OrgGraph : public QAbstractListModel {
  private:
    Q_OBJECT
  public:
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
        : QAbstractListModel(parent), store(store) {}

    Graph                         g;
    UnorderedMap<OrgBoxId, VDesc> boxToVertex;
    OrgStore*                     store;
    /// List of edges and nodes for a graph to maintain stable flat list of
    /// nodes.
    Vec<EDesc> edges;
    Vec<VDesc> nodes;

    UnorderedMap<Str, Vec<OrgBoxId>> subtreeIds;
    UnorderedMap<Str, Vec<OrgBoxId>> footnoteTargets;

    void updateUnresolved(VDesc newNode);


    struct UnresolvedLink {
        sem::SemId<sem::Link>     link;
        Opt<sem::SemId<sem::Org>> description;
    };

    UnorderedMap<OrgBoxId, Vec<UnresolvedLink>> unresolved;

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


    std::string toGraphviz();

    QString getDisplayText(CR<QModelIndex> index) const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)
        const override;

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[Qt::DisplayRole]                    = "DisplayRole";
        roles[SharedModelRoles::IndexBoxRole]     = "IndexBoxRole";
        roles[OrgGraphModelRoles::IsNodeRole]     = "IsNodeRole";
        roles[OrgGraphModelRoles::NodeDescAtRole] = "NodeDescAtRole";
        roles[OrgGraphModelRoles::EdgeDescAtRole] = "EdgeDescAtRole";
        roles[OrgGraphModelRoles::SourceAndTargetRole]
            = "SourceAndTargetRole";
        roles[OrgGraphModelRoles::DebugDisplayRole] = "DebugDisplayRole";
        return roles;
    }


    void addFullStore() {
        Q_ASSERT(store != nullptr);
        for (auto const& box : store->boxes()) { addBox(box); }
    }


    bool hasEdge(CR<OrgBoxId> source, CR<OrgBoxId> target) {
        return 0 < out_edges(source, target).size();
    }

    int numNodes() const { return boost::num_vertices(g); }

    int numEdges() const { return boost::num_edges(g); }

    EDesc getEdgeDesc(int row) const { return edges.at(row - numNodes()); }

    EDesc getEdgeDesc(QModelIndex index) const {
        return getEdgeDesc(index.row());
    }

    VDesc getBoxNode(CR<OrgBoxId> id) const { return boxToVertex.at(id); }

    VDesc getEdgeSource(EDesc d) const { return boost::source(d, g); }

    VDesc getEdgeTarget(EDesc d) const { return boost::target(d, g); }

    VDesc getNodeDesc(int idx) const { return nodes.at(idx); }

    VDesc getNodeDesc(QModelIndex index) const {
        return getNodeDesc(index.row());
    }

    OrgBoxId getBox(int row) const {
        return getNodeProp(getNodeDesc(row)).box;
    }

    OrgGraphEdge& getEdgeProp(EDesc desc) { return g[desc]; }

    OrgGraphNode& getNodeProp(VDesc desc) { return g[desc]; }

    OrgGraphEdge const& getEdgeProp(EDesc desc) const { return g[desc]; }

    OrgGraphNode const& getNodeProp(VDesc desc) const { return g[desc]; }

    EDesc addEdge(VDesc source, VDesc target) {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        EDesc e;
        bool  inserted;
        boost::tie(e, inserted) = boost::add_edge(source, target, g);
        if (inserted) { edges.push_back(e); }
        endInsertRows();
        return e;
    }

    VDesc addVertex() {
        beginInsertRows(QModelIndex(), nodes.size(), nodes.size());
        VDesc v = boost::add_vertex(g);
        nodes.push_back(v);
        endInsertRows();
        return v;
    }


    void removeVertex(VDesc vertex) {
        auto it = std::find(nodes.begin(), nodes.end(), vertex);
        if (it != nodes.end()) {
            int index = std::distance(nodes.begin(), it);
            beginRemoveRows(QModelIndex(), index, index);
            boost::clear_vertex(*it, g);
            boost::remove_vertex(*it, g);
            nodes.erase(it);

            rebuildEdges();
            endRemoveRows();
        }
    }

    void rebuildEdges() {
        edges.clear();
        Graph::edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = boost::edges(g); ei != ei_end;
             ++ei) {
            edges.push_back(*ei);
        }
    }


    OrgGraphEdge& out_edge0(CR<OrgBoxId> source, CR<OrgBoxId> target) {
        return getEdgeProp(out_edges(source, target).at(0));
    }

    Vec<EDesc> out_edges(
        CR<OrgBoxId>      source,
        CR<Opt<OrgBoxId>> target = std::nullopt) {
        VDesc      v1 = getBoxNode(source);
        Opt<VDesc> v2 = target ? std::make_optional(getBoxNode(*target))
                               : std::nullopt;
        Vec<EDesc> result;

        Graph::out_edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = boost::out_edges(v1, g);
             ei != ei_end;
             ++ei) {
            if (!v2 || boost::target(*ei, g) == *v2) {
                result.push_back(*ei);
            }
        }

        return result;
    }


    Vec<EDesc> in_edges(
        CR<OrgBoxId>      source,
        CR<Opt<OrgBoxId>> target = std::nullopt) {
        VDesc      v1 = getBoxNode(source);
        Opt<VDesc> v2 = target ? std::make_optional(getBoxNode(*target))
                               : std::nullopt;
        Vec<EDesc> result;

        Graph::in_edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = boost::in_edges(v1, g); ei != ei_end;
             ++ei) {
            if (!v2 || boost::target(*ei, g) == *v2) {
                result.push_back(*ei);
            }
        }

        return result;
    }

  public slots:
    void replaceBox(CR<OrgBoxId> before, CR<OrgBoxId> replace) {}
    void addBox(CR<OrgBoxId> box);
};

struct OrgGraphFilterProxy : public QSortFilterProxyModel {
  private:
    Q_OBJECT
  public:
    using AcceptNodeCb = Func<bool(OrgGraph::VDesc const&)>;
    using AcceptEdgeCb = Func<bool(OrgGraph::EDesc const&)>;

    AcceptNodeCb accept_node;
    AcceptEdgeCb accept_edge;

    virtual bool filterAcceptsRow(
        int                source_row,
        const QModelIndex& source_parent) const override {
        QModelIndex index = sourceModel()->index(
            source_row, 0, source_parent);
        if (qindex_get<bool>(index, OrgGraphModelRoles::IsNodeRole)) {
            return accept_node(qindex_get<OrgGraph::VDesc>(
                index, OrgGraphModelRoles::NodeDescAtRole));
        } else {
            return accept_edge(qindex_get<OrgGraph::EDesc>(
                index, OrgGraphModelRoles::EdgeDescAtRole));
        }
    }
};

struct OrgGraphLayoutProxy : public QSortFilterProxyModel {
  private:
    Q_OBJECT
  public:
    enum Roles
    {
        LayoutBBoxRole = OrgGraphModelRoles::OrgGraphModelRoles__LAST__
                       + 1,
    };

    struct ElementLayout {
        Variant<QRect, QPainterPath> data;

        bool isNode() const { return std::holds_alternative<QRect>(data); }
        QRect const& getNode() const { return std::get<QRect>(data); }

        QPainterPath const& getEdge() const {
            return std::get<QPainterPath>(data);
        }
    };

    struct FullLayout {
        QHash<int, ElementLayout> data;
        QRect                     bbox;
        Variant<
            std::monostate,
            GraphLayoutIR::GraphvizResult,
            GraphLayoutIR::ColaResult //
            >
            original;
    };

    using GetNodeSize = Func<QSize(QModelIndex const& index)>;
    GetNodeSize getNodeSize;

    OrgGraphLayoutProxy(CR<GetNodeSize> size, QObject* parent)
        : QSortFilterProxyModel(parent), getNodeSize(size) {}


    ElementLayout getElement(QModelIndex const& idx) const {
        Q_ASSERT_X(
            currentLayout.data.contains(idx.row()),
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
        auto base = sourceModel()->roleNames();
        base[OrgGraphModelRoles::NodeShapeRole] = "NodeShapeRole";
        base[OrgGraphModelRoles::EdgeShapeRole] = "EdgeShapeRole";
        base[LayoutBBoxRole]                    = "LayoutBBoxRole";
        return base;
    }
};
