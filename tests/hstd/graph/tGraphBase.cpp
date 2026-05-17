#include "../t_graph_tests_common.hpp"

struct GraphBase_Test : public GraphUtils_Test {};

struct AutoSegmentTest {
    std::shared_ptr<TrivialEdgeCollection> segmented_edges;
    std::shared_ptr<TrivialPortCollection> connection_ports;
    AutoSegmentingCollection               as;

    AutoSegmentTest(IGraph* g, hstd::SPtr<IVertexHierarchy> const& h)
        : segmented_edges{std::make_shared<TrivialEdgeCollection>(
              EdgeCollectionID{139})}
        , connection_ports{std::make_shared<TrivialPortCollection>()}
        , as{
              segmented_edges.get(),
              connection_ports.get(),
              h.get(),
              g,
          } {
        g->addPorts(connection_ports);
        g->addCollection(segmented_edges);
    }
};

TEST_F(GraphBase_Test, AddVertex) {
    auto id = addVertex("a");
    EXPECT_NE(graph->getVertex(id), nullptr);
}

TEST_F(GraphBase_Test, AddEdge) {
    auto a = addVertex("a");
    auto b = addVertex("b");
    auto e = addEdge(a, b, "e");
    EXPECT_TRUE(graph->edges->hasEdge(e));
    EXPECT_EQ(graph->edges->getSource(e), a);
    EXPECT_EQ(graph->edges->getTarget(e), b);
}

TEST_F(GraphBase_Test, OnePortPerVertex) {
    TrivialPortCollection ports;
    auto                  a = addVertex("a");
    auto                  b = addVertex("b");
    auto                  e = addEdge(a, b, "e");

    auto port_a_e = ports.addPort(a, e, true);
    auto port_b_e = ports.addPort(b, e, false);

    EXPECT_TRUE(ports.isSourcePort(port_a_e));
    EXPECT_TRUE(ports.isTargetPort(port_b_e));

    EXPECT_EQ(graph->edges->getOutgoing(a).size(), 1);
    EXPECT_EQ(graph->edges->getIncoming(a).size(), 0);

    EXPECT_EQ(graph->edges->getOutgoing(b).size(), 0);
    EXPECT_EQ(graph->edges->getIncoming(b).size(), 1);
}

TEST_F(GraphBase_Test, MultiPort) {
    TrivialPortCollection ports;
    auto                  a = addVertex("a");
    auto                  b = addVertex("b");
    auto                  c = addVertex("c");

    //
    auto ab1 = addEdge(a, b, "ab1");
    auto ab2 = addEdge(a, b, "ab2");
    //
    auto ac1 = addEdge(a, c, "ac1");
    auto ac2 = addEdge(a, c, "ac2");
    //
    auto bc1 = addEdge(b, c, "bc1");
    auto bc2 = addEdge(b, c, "bc2");
    auto bc3 = addEdge(b, c, "bc3");

    ports.addPorts(graph->edges->getPortSpecs(ab1));
    ports.addPorts(graph->edges->getPortSpecs(ab2));

    ports.addPorts(graph->edges->getPortSpecs(ac1));
    ports.addPorts(graph->edges->getPortSpecs(ac2));

    ports.addPorts(graph->edges->getPortSpecs(bc1));
    ports.addPorts(graph->edges->getPortSpecs(bc2));
    ports.addPorts(graph->edges->getPortSpecs(bc3));

    EXPECT_EQ(ports.getPortsForVertex(a).size(), 4);
    EXPECT_EQ(ports.getPortsForVertex(b).size(), 5);
    EXPECT_EQ(ports.getPortsForVertex(c).size(), 5);

    EXPECT_TRUE(ports.hasPortConnection(a, ab1, true));
    EXPECT_TRUE(ports.hasPortConnection(b, ab1, false));
}

TEST_F(GraphBase_Test, SimpleHierarchy_TwoVertices) {
    TrivialGraph g;
    auto         h = std::make_shared<TrivialHierarchy>();
    g.addHierarchy(h);

    auto a = g.addVertex("a");
    auto b = g.addVertex("b");

    EXPECT_THROW_TEXT_CONTAINS(
        graph_error,
        (g.trackSubVertexRelation(h->getCollectionID(), a, b)),
        "parent vertex",
        "not found");

    h->trackVertex(a);

    EXPECT_THROW_TEXT_CONTAINS(
        graph_error,
        (g.trackSubVertexRelation(h->getCollectionID(), a, b)),
        "sub vertex",
        "not found");

    h->trackVertex(b);

    auto e = g.trackSubVertexRelation(
        h->getCollectionID(), /*parent=*/a, /*sub=*/b);

    EXPECT_THROW_TEXT_CONTAINS(
        graph_error,
        (g.trackSubVertexRelation(h->getCollectionID(), a, b)),
        "already has a parent");

    EXPECT_EQ(h->getIncoming(b).size(), 1);
    EXPECT_EQ(h->getOutgoing(a).size(), 1);
    EXPECT_EQ(h->getIncoming(a).size(), 0);
    EXPECT_EQ(h->getOutgoing(b).size(), 0);
    EXPECT_EQ(h->getParentVertex(b).value(), a);
    EXPECT_FALSE(h->getParentVertex(a).has_value());
    EXPECT_EQ(h->getParentChain(b).size(), 1);
    EXPECT_EQ(h->getParentChain(b).at(0), a);
}

TEST_F(GraphBase_Test, SingleHierarchy_FourVertices) {
    TrivialGraph g;
    auto         h = std::make_shared<TrivialHierarchy>();
    g.addHierarchy(h);

    auto v1 = g.addVertex("v1");
    auto v2 = g.addVertex("v2");
    auto v3 = g.addVertex("v3");
    auto v4 = g.addVertex("v4");

    h->trackVertex(v1);
    h->trackVertex(v2);
    h->trackVertex(v3);
    h->trackVertex(v4);

    std::ignore = h->trackSubVertexRelation(v1, v2);
    std::ignore = h->trackSubVertexRelation(v2, v3);
    std::ignore = h->trackSubVertexRelation(v3, v4);

    EXPECT_EQ(h->getSubVertices(v1).size(), 1);
    EXPECT_FALSE(h->getParentVertex(v1).has_value());
    EXPECT_EQ(h->getSubVertices(v1).items().at(0), v2);

    EXPECT_EQ(h->getParentChain(v4).size(), 3);
    EXPECT_EQ(h->getParentVertex(v4).value(), v3);
}

TEST_F(GraphBase_Test, HierarchyCrossingEdges_NoSplit) {
    //   V1           V2
    //   ┌───┐        ┌───┐
    //   │ S ├──────►│ T │
    //   └───┘        └───┘
    TrivialGraph g;
    auto         h = std::make_shared<TrivialHierarchy>();
    g.addHierarchy(h);

    auto v1 = g.addVertex("v1");
    auto v2 = g.addVertex("v2");
    auto e  = g.addEdge(v1, v2);
    h->trackVertex(v1);
    h->trackVertex(v2);
    EXPECT_EQ(g.getHierarchyCrossings(e).size(), 0);
}


TEST_F(GraphBase_Test, HierarchyCrossingEdges_FromInnerToParent) {
    //  ┌───────────────────────┐
    //  │ ┌───┐       ▲        │
    //  │ │ S ├───────┘  T      │
    //  │ └───┘V1               │
    //  └───────────────────────┘V2
    TrivialGraph g;
    auto         h = std::make_shared<TrivialHierarchy>();
    g.addHierarchy(h);

    auto v1 = g.addVertex("v1");
    auto v2 = g.addVertex("v2");
    auto e  = g.addEdge(v1, v2);
    h->trackVertex(v1);
    h->trackVertex(v2);
    std::ignore = h->trackSubVertexRelation(v2, v1);
    EXPECT_EQ(g.getHierarchyCrossings(e).size(), 0);
}

TEST_F(GraphBase_Test, HierarchyCrossingEdges_FromParentToInner) {
    //  ┌─────────────┬─────────┐
    //  │ ┌───┐       │         │
    //  │ │ T │◄─────┘  S      │
    //  │ └───┘V1               │
    //  └───────────────────────┘V2
    TrivialGraph g;
    auto         h = std::make_shared<TrivialHierarchy>();
    g.addHierarchy(h);

    auto v1 = g.addVertex("v1");
    auto v2 = g.addVertex("v2");
    auto e  = g.addEdge(v1, v2);
    h->trackVertex(v1);
    h->trackVertex(v2);
    std::ignore = h->trackSubVertexRelation(v2, v1);
    EXPECT_EQ(g.getHierarchyCrossings(e).size(), 0);
}


TEST_F(GraphBase_Test, HierarchyCrossingEdges_FromInnermostToOutermost) {
    // ┌───────────────────────────────┐
    // │ ┌───────────────────────┐ ▲  │
    // │ │ ┌───┐                 │ │   │
    // │ │ │ S ├─────────────────┼─┘   │
    // │ │ └───┘V1               │  T  │
    // │ └───────────────────────┘V2   │
    // └───────────────────────────────┘V3
    TrivialGraph g;
    auto         h = std::make_shared<TrivialHierarchy>();
    g.addHierarchy(h);

    auto v1 = g.addVertex("v1");
    auto v2 = g.addVertex("v2");
    auto v3 = g.addVertex("v3");
    auto e  = g.addEdge(v1, v2);
    h->trackVertex(v1);
    h->trackVertex(v2);
    h->trackVertex(v3);
    std::ignore = h->trackSubVertexRelation(v2, v1);
    std::ignore = h->trackSubVertexRelation(v3, v2);
    EXPECT_EQ(g.getHierarchyCrossings(e).at(0).crossings.size(), 1);
    EXPECT_EQ(g.getHierarchyCrossings(e).at(0).crossings.at(0), v2);
}


TEST_F(
    GraphBase_Test,
    HierarchyCrossingEdges_FromInnerNestedToInnerNested) {
    // ┌────────────────────────────────┐
    // │┌────────┐       ┌──────────┐   │
    // ││ ┌───┐  │       │  ┌───┐   │   │
    // ││ │ S ├──┼───────┼►│ T │   │   │
    // ││ └───┘V1│       │  └───┘V3 │   │
    // │└────────┘V2     └──────────┘V4 │
    // └────────────────────────────────┘V5
    TrivialGraph g;
    auto         h = std::make_shared<TrivialHierarchy>();
    g.addHierarchy(h);

    auto v1 = g.addVertex("v1");
    auto v2 = g.addVertex("v2");
    auto v3 = g.addVertex("v3");
    auto v4 = g.addVertex("v4");
    auto v5 = g.addVertex("v5");

    auto e = g.addEdge(v1, v3);
    h->trackVertex(v1);
    h->trackVertex(v2);
    h->trackVertex(v3);
    h->trackVertex(v4);
    h->trackVertex(v5);

    std::ignore = h->trackSubVertexRelation(v2, v1);
    std::ignore = h->trackSubVertexRelation(v4, v3);
    std::ignore = h->trackSubVertexRelation(v5, v2);
    std::ignore = h->trackSubVertexRelation(v5, v4);

    EXPECT_EQ(g.getHierarchyCrossings(e).at(0).crossings.size(), 2);
    EXPECT_EQ(g.getHierarchyCrossings(e).at(0).crossings.at(0), v2);
    EXPECT_EQ(g.getHierarchyCrossings(e).at(0).crossings.at(1), v4);

    AutoSegmentTest as{&g, h};

    as.as.addEdge(e);
    EXPECT_EQ(as.as.getSegmentationPorts(e).size(), 2);
    EXPECT_EQ(as.as.getSegments(e).size(), 3);
}
