#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <editor/editor_lib/org_document_model.hpp>
#include <QObject>
#include <hstd/system/macros.hpp>
#include <QAbstractItemModel>
#include <editor/editor_lib/app_utils.hpp>
#include <editor/editor_lib/org_graph_layout.hpp>

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

struct OrgGraph : public QObject {
  private:
    Q_OBJECT
  public:
    using Graph = boost::adjacency_list<
        boost::setS,
        boost::vecS,
        boost::bidirectionalS,
        OrgGraphNode,
        OrgGraphEdge>;

    using GraphTraits = boost::graph_traits<Graph>;
    using VDesc       = GraphTraits::vertex_descriptor;
    using EDesc       = GraphTraits::edge_descriptor;

    OrgGraph(OrgStore* store) : store(store) {}

    Graph                         g;
    UnorderedMap<OrgBoxId, VDesc> boxToVertex;
    OrgStore*                     store;

    UnorderedMap<Str, Vec<OrgBoxId>> subtreeIds;
    UnorderedMap<Str, Vec<OrgBoxId>> footnoteTargets;

    void updateUnresolved(VDesc newNode);

    struct UnresolvedLink {
        sem::SemId<sem::Link>     link;
        Opt<sem::SemId<sem::Org>> description;
    };

    UnorderedMap<OrgBoxId, Vec<UnresolvedLink>> unresolved;

    std::string toGraphviz();

    void addFullStore() {
        Q_ASSERT(store != nullptr);
        for (auto const& box : store->boxes()) { addBox(box); }
    }

    VDesc desc(CR<OrgBoxId> id) const { return boxToVertex.at(id); }

    int  numNodes() { return boost::num_vertices(g); }
    int  numEdges() { return boost::num_edges(g); }
    bool hasEdge(CR<OrgBoxId> source, CR<OrgBoxId> target) {
        return 0 < out_edges(source, target).size();
    }

    generator<VDesc> nodes() const {
        for (auto [begin, end] = boost::vertices(g); begin != end;
             ++begin) {
            co_yield *begin;
        }
    }

    generator<EDesc> edges() const {
        for (auto [begin, end] = boost::edges(g); begin != end; ++begin) {
            co_yield *begin;
        }
    }

    OrgGraphEdge& edge(EDesc desc) { return g[desc]; }
    OrgGraphNode& node(VDesc desc) { return g[desc]; }


    EDesc edgeAt(int idx) {
        auto [it, end] = boost::edges(g);
        std::advance(it, idx);
        return *it;
    }

    VDesc source(EDesc d) const { return boost::source(d, g); }
    VDesc target(EDesc d) const { return boost::target(d, g); }

    VDesc nodeAt(int idx) {
        auto [it, end] = boost::vertices(g);
        std::advance(it, idx);
        return *it;
    }

    OrgGraphEdge& out_edge0(CR<OrgBoxId> source, CR<OrgBoxId> target) {
        return edge(out_edges(source, target).at(0));
    }

    Vec<EDesc> out_edges(
        CR<OrgBoxId>      source,
        CR<Opt<OrgBoxId>> target = std::nullopt) {
        VDesc      v1 = desc(source);
        Opt<VDesc> v2 = target ? std::make_optional(desc(*target))
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
        VDesc      v1 = desc(source);
        Opt<VDesc> v2 = target ? std::make_optional(desc(*target))
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

/// Model roles shared between org graph model and proxy layouts that are
/// strapped on top of the flat list model.
enum OrgGraphModelRoles
{
    OrgGraphModelRoles__FIRST__ = SharedModelRoles::__LAST__ + 1,
    NodeShapeRole, ///< Node shape in absolute coordinates after layout
    EdgeShapeRole, ///< Edge spline in absolute coordinates after layout
    IsNodeRole,    ///< Check if the index points to and edge or to a node.
};

struct OrgGraphModel : public QAbstractListModel {
  private:
    Q_OBJECT
  public:
    OrgGraph* g;
    explicit OrgGraphModel(OrgGraph* g, QObject* parent)
        : QAbstractListModel(parent), g(g) {}

    int rowCount(
        const QModelIndex& parent = QModelIndex()) const override {
        if (parent.isValid()) {
            return 0;
        } else {
            return g->numNodes() + g->numEdges();
        }
    }

    bool isNode(CR<QModelIndex> index) const {
        return index.row() < g->numNodes();
    }

    OrgBoxId boxAt(int row) const { return g->node(nodeAt(row)).box; }

    OrgGraph::VDesc nodeAt(int row) const { return g->nodeAt(row); }

    OrgGraph::VDesc nodeAt(QModelIndex index) const {
        return nodeAt(index.row());
    }

    OrgGraph::EDesc edgeAt(int row) const {
        return g->edgeAt(row - g->numNodes());
    }

    OrgGraph::EDesc edgeAt(QModelIndex index) const {
        return edgeAt(index.row());
    }

    Pair<OrgGraph::VDesc, OrgGraph::VDesc> sourceTargetAt(
        QModelIndex index) const {
        auto eDesc = edgeAt(index);
        return std::make_pair<OrgGraph::VDesc, OrgGraph::VDesc>(
            g->source(eDesc), g->target(eDesc));
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)
        const override;

    QSize nodeSize(QModelIndex const& index) const;

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[Qt::DisplayRole]                = "DisplayRole";
        roles[SharedModelRoles::IndexBoxRole] = "IndexBoxRole";
        roles[OrgGraphModelRoles::IsNodeRole] = "IsNodeRole";
        return roles;
    }
};

struct OrgGraphLayoutProxy : public QSortFilterProxyModel {
  private:
    Q_OBJECT
  public:
    struct ElementLayout {
        Variant<QRect, QPolygonF> data;

        bool isNode() const { return std::holds_alternative<QRect>(data); }
        QRect const& getNode() const { return std::get<QRect>(data); }

        QPolygonF const& getEdge() const {
            return std::get<QPolygonF>(data);
        }
    };

    struct FullLayout {
        QHash<QModelIndex, ElementLayout> data;
        QRect                             bbox;
    };

    ElementLayout getElement(QModelIndex const& idx) const {
        Q_ASSERT(currentLayout.data.contains(mapToSource(idx)));
        return currentLayout.data[mapToSource(idx)];
    }

    FullLayout currentLayout;
    FullLayout getFullLayout() const;
    void       updateCurrentLayout() { currentLayout = getFullLayout(); }

    OrgGraphModel const* graphModel() const {
        return static_cast<OrgGraphModel*>(sourceModel());
    }

    OrgGraphModel* graphModel() {
        return static_cast<OrgGraphModel*>(sourceModel());
    }

    virtual QVariant data(const QModelIndex& index, int role)
        const override;

    virtual QHash<int, QByteArray> roleNames() const override {
        auto base = sourceModel()->roleNames();
        base[OrgGraphModelRoles::NodeShapeRole] = "NodeShapeRole";
        base[OrgGraphModelRoles::EdgeShapeRole] = "EdgeShapeRole";
        return base;
    }
};
