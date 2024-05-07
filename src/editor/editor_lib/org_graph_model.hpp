#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <editor/editor_lib/org_document_model.hpp>
#include <QObject>
#include <hstd/system/macros.hpp>

struct OrgGraphNode {
    OrgBoxId box;
};

struct OrgGraphEdge {
    DECL_DESCRIBED_ENUM(Kind, Nested);
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

    void addFullStore() {
        for (auto const& box : store->boxes()) { addBox(box); }
    }

    VDesc desc(CR<OrgBoxId> id) const { return boxToVertex.at(id); }

    generator<VDesc> nodes() const {
        for (auto [begin, end] = boost::vertices(g); begin != end;
             ++begin) {
            co_yield *begin;
        }
    }

    template <typename Self>
    OrgGraphEdge&& edge(this Self&& self, EDesc desc) {
        return self.g[desc];
    }

    template <typename Self>
    OrgGraphNode&& node(this Self&& self, VDesc desc) {
        return self.g[desc];
    }

    Vec<EDesc> edges(CR<OrgBoxId> source, CR<OrgBoxId> target) {
        VDesc      v1 = desc(source);
        VDesc      v2 = desc(target);
        Vec<EDesc> result;

        Graph::out_edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = out_edges(v1, g); ei != ei_end;
             ++ei) {
            if (boost::target(*ei, g) == v2) { result.push_back(*ei); }
        }

        return result;
    }

  public slots:
    void replaceBox(CR<OrgBoxId> before, CR<OrgBoxId> replace) {}
    void addBox(CR<OrgBoxId> box);
};
