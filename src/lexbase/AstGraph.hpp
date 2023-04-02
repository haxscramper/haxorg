#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/graphviz.hpp>

#include <lexbase/Node.hpp>


template <typename N, typename K>
struct VertexProp {
    NodeId<N, K> id    = NodeId<N, K>::Nil();
    int          index = 0;
};

template <typename N, typename K>
struct EdgeProp {};

template <typename N, typename K>
using Graph = boost::adjacency_list<
    boost::vecS,
    boost::vecS,
    boost::directedS,
    VertexProp<N, K>,
    EdgeProp<N, K>>;

template <typename N, typename K>
using GraphTraits = boost::graph_traits<Graph<N, K>>;

template <typename N, typename K>
using VertDesc = typename GraphTraits<N, K>::vertex_descriptor;
template <typename N, typename K>
using VertBundledType = typename boost::vertex_bundle_type<
    Graph<N, K>>::type;
template <typename N, typename K>
using EdgeBundledType = typename boost::edge_bundle_type<
    Graph<N, K>>::type;

template <typename N, typename K>
Graph<N, K> graphRepr(NodeGroup<N, K>* group, NodeId<N, K> root) {
    Func<void(NodeId<N, K>, Opt<VertDesc<N, K>>, int)> aux;
    Graph<N, K>                                        graph;
    aux = [&graph, group, &aux](
              NodeId<N, K> node, Opt<VertDesc<N, K>> parent, int index) {
        VertDesc<N, K> vertex = add_vertex(
            VertexProp<N, K>{.id = node, .index = index}, graph);

        if (parent.has_value()) {
            add_edge(parent.value(), vertex, EdgeProp<N, K>{}, graph);
        }

        if (!group->at(node).isTerminal()) {
            auto [begin, end] = group->subnodesOf(node).value();
            int node_index    = 0;
            for (; begin != end; ++begin) {
                aux(*begin, vertex, node_index);
                ++node_index;
            }
        }
    };

    aux(root, std::nullopt, 0);
    return graph;
}
