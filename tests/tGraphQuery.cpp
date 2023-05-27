//#include "common.hpp"
#include <gtest/gtest.h>
#include <hstd/stdlib/GraphQuery.hpp>

using namespace boost;

struct EdgeProp {};
struct VertProp {};


using Graph = adjacency_list<
    vecS,
    vecS,
    bidirectionalS,
    VertProp,
    EdgeProp>;

using QS = QuerySystem<Graph, std::string>;

Graph simpleGraph() {
    Graph graph;
    auto  v1   = add_vertex(graph);
    auto  v2   = add_vertex(graph);
    auto  edge = add_edge(v1, v2, graph);

    return graph;
}

Graph bigGraph() {
    Graph graph;
    auto  _id1 = add_vertex(graph);
    auto  _id2 = add_vertex(graph);
    auto  _id3 = add_vertex(graph);
    auto  _id4 = add_vertex(graph);
    auto  _id5 = add_vertex(graph);
    auto  _id6 = add_vertex(graph);

    add_edge(_id1, _id2, graph);
    add_edge(_id2, _id3, graph);
    add_edge(_id2, _id4, graph);
    add_edge(_id2, _id5, graph);
    add_edge(_id2, _id6, graph);
    add_edge(_id3, _id4, graph);
    add_edge(_id4, _id5, graph);
    add_edge(_id5, _id3, graph);
    add_edge(_id3, _id5, graph);
    add_edge(_id4, _id3, graph);
    add_edge(_id5, _id4, graph);
    add_edge(_id3, _id6, graph);
    add_edge(_id4, _id6, graph);
    add_edge(_id5, _id6, graph);
    add_edge(_id6, _id3, graph);
    add_edge(_id6, _id4, graph);
    add_edge(_id6, _id5, graph);

    return graph;
}

TEST(BasicApi, OutNode) {
    Graph graph = simpleGraph();

    auto result = QS::Query{}
                      .start(boost::vertex(0, graph))
                      .outNodes()
                      .runForAllVertices(graph);

    ASSERT_EQ(result.size(), 1);
}

TEST(BasicApi, StartReturns) {
    Graph graph = simpleGraph();

    auto v      = boost::vertex(0, graph);
    auto result = QS::Query{}.start(v).runForAllVertices(graph);

    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result.at(0), v);
}

TEST(BasicApi, InNode) {
    Graph graph = simpleGraph();

    auto v      = boost::vertex(1, graph);
    auto result = QS::Query{}.start(v).inNodes().runForAllVertices(graph);

    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result.at(0), boost::vertex(0, graph));
}

template <typename T>
Vec<T> sorted(Vec<T> const& in) {
    Vec<T> res = in;
    std::sort(res.begin(), res.end());
    return res;
}

TEST(BasicApi, NestedOutgoing) {
    auto g      = bigGraph();
    auto result = QS::Query{}
                      .start(vertex(0, g))
                      .outNodes()
                      .outNodes()
                      .runForAllVertices(g);

    ASSERT_EQ(result.size(), 4);
    ASSERT_EQ(
        result,
        sorted<decltype(vertex(3, g))>({
            vertex(2, g),
            vertex(3, g),
            vertex(4, g),
            vertex(5, g),
        }));
}
