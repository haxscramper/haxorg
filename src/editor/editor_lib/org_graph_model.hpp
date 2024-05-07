#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <editor/editor_lib/org_document_model.hpp>
#include <QObject>
#include <hstd/system/macros.hpp>

struct OrgGraphNode {
    OrgBoxId box;
    DECL_DESCRIBED_ENUM(Kind, Subtree, Document, Paragraph, Footnote);
    Kind kind;
};

struct OrgGraphEdge {
    DECL_DESCRIBED_ENUM(Kind, SubtreeId, Footnote);
    Kind kind;
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
        sem::SemId<sem::Link> link;
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

    OrgGraphEdge& edge(EDesc desc) { return g[desc]; }
    OrgGraphNode& node(VDesc desc) { return g[desc]; }

    OrgGraphEdge& out_edge0(CR<OrgBoxId> source, CR<OrgBoxId> target) {
        return edge(out_edges(source, target).at(0));
    }

    Vec<EDesc> out_edges(CR<OrgBoxId> source, CR<OrgBoxId> target) {
        VDesc      v1 = desc(source);
        VDesc      v2 = desc(target);
        Vec<EDesc> result;

        Graph::out_edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = boost::out_edges(v1, g);
             ei != ei_end;
             ++ei) {
            if (boost::target(*ei, g) == v2) { result.push_back(*ei); }
        }

        return result;
    }


    Vec<EDesc> in_edges(CR<OrgBoxId> source, CR<OrgBoxId> target) {
        VDesc      v1 = desc(source);
        VDesc      v2 = desc(target);
        Vec<EDesc> result;

        Graph::in_edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = boost::in_edges(v1, g); ei != ei_end;
             ++ei) {
            if (boost::target(*ei, g) == v2) { result.push_back(*ei); }
        }

        return result;
    }

  public slots:
    void replaceBox(CR<OrgBoxId> before, CR<OrgBoxId> replace) {}
    void addBox(CR<OrgBoxId> box);
};
