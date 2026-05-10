#include "../t_graph_tests_common.hpp"

struct GraphVisualElk_Test : public GraphUtils_Test {};

geometry::Size size{50, 50};

TEST_F(GraphVisualElk_Test, GraphvizSimpleConstruction) {
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

    auto root = elk::GroupVisual::newRootGraph(run);
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
