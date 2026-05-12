#include "../t_graph_tests_common.hpp"

struct GraphVisualElk_Test : public GraphUtils_Test {};

namespace {
geometry::Size size{50, 50};
}

TEST_F(GraphVisualElk_Test, SimpleGraph) {
    // Create initial graph structure
    auto v1 = addVertex("v1");
    auto v2 = addVertex("v2");
    auto v3 = addVertex("v3");
    auto v4 = addVertex("v4");

    ASSERT_NE(v1, v2);
    ASSERT_NE(v2, v3);
    ASSERT_NE(v3, v4);

    auto e12 = addEdge(v1, v2, "e12");
    auto e23 = addEdge(v2, v3, "e23");
    auto e31 = addEdge(v3, v1, "e31");

    auto rg_id = graph->addVertex();

    auto root = elk::ElkGroupVisualAttribute::newRootGraph(run);
    run->addRootGroup(rg_id, root);

    root->addVertex(rg_id, v1)->setSize(size);
    root->addVertex(rg_id, v2)->setSize(size);
    root->addVertex(rg_id, v3)->setSize(size);
    root->addVertex(rg_id, v4)->setSize(size);
    root->addEdge(e12);
    root->addEdge(e23);
    root->addEdge(e31);

    run->runFullLayout();

    hstd::writeFile(
        getDebugFile("repr.txt"), run->treeRepr().toString(false));

    auto const& res = run->result;

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
}

TEST_F(GraphVisualElk_Test, SimpleSubGraph) {
    auto g1 = addVertex("g1");
    auto g2 = addVertex("g2");

    auto v1 = addVertex("v1");
    auto v2 = addVertex("v2");
    auto v3 = addVertex("v3");
    auto v4 = addVertex("v4");
    auto v5 = addVertex("v5");
    auto v6 = addVertex("v6");
    auto v7 = addVertex("v7");
    auto v8 = addVertex("v8");

    auto e15     = addEdge(v1, v5, "e15");
    auto e12     = addEdge(v1, v2, "e12");
    auto e23     = addEdge(v2, v3, "e23");
    auto e34     = addEdge(v3, v4, "e34");
    auto e_g1_g2 = addEdge(g1, g2, "e_g1_g2");

    auto rg_id = graph->addVertex();

    auto root = elk::ElkGroupVisualAttribute::newRootGraph(run);
    run->addRootGroup(rg_id, root);

    auto g1_sub = root->addNewNativeSubgroup(rg_id, g1);
    auto g2_sub = root->addNewNativeSubgroup(rg_id, g2);

    g1_sub->addVertex(g1, v1)->setSize(size);
    g1_sub->addVertex(g1, v2)->setSize(size);
    g1_sub->addVertex(g1, v3)->setSize(size);
    g1_sub->addVertex(g1, v4)->setSize(size);

    g2_sub->addVertex(g2, v5)->setSize(size);
    g2_sub->addVertex(g2, v6)->setSize(size);
    g2_sub->addVertex(g2, v7)->setSize(size);
    g2_sub->addVertex(g2, v8)->setSize(size);

    root->addEdge(e15);
    root->addEdge(e_g1_g2);
    g1_sub->addEdge(e12);
    g1_sub->addEdge(e23);
    g1_sub->addEdge(e34);

    run->runFullLayout();

    hstd::writeFile(
        getDebugFile("repr.txt"), run->treeRepr().toString(false));

    auto const& res = run->result;

    EXPECT_TRUE(res.edges.contains(e15));
    EXPECT_TRUE(res.edges.contains(e_g1_g2));

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
}
