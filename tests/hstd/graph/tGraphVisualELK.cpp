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

TEST_F(GraphVisualElk_Test, AspectCompositeQM) {
    // port of the example model aspect_compositeqm_CompositeQM.json

    // clang-format off
/*
                                  ┌────────────────┐
┌───────────┐   ┌────────────┬────┘ ┌───────────┐  └───┬──────────────┐
│disc_clock1├───┤ramp1       ├──────┤scale1     ├──────┤ timed_plotter│
└───────────┘   └────────────┴────┐ └───────────┘  ┌───┴──────────────┘
                                  └────────────────┘

┌───────────┐   ┌────────────┐      ┌───────────┐
│disc_clock2├───┤ramp2       ├──────┤scale2     │
└───────────┘   └────────────┘      └───────────┘


┌───────────┐
│a          ■─┐
└───────────┘  │
               │
               │
┌───────────┐  └■┌───────────┐     ┌───────────────┐   ┌───────────────┐
│b         ■───■│merge2     ■──■│server         ├───┤ comm_resp     │
└───────────┘     └───────────┘     └───────────────┘   └───────────────┘
*/
    // clang-format on

    auto r_id           = addVertex("r");
    auto a_id           = addVertex("a");
    auto b_id           = addVertex("b");
    auto merge2_id      = addVertex("Merge2");
    auto server_id      = addVertex("Server");
    auto comm_resp_id   = addVertex("comm_resp");
    auto disc_clock1_id = addVertex("disc_clock1");
    auto disc_clock2_id = addVertex("disc_clock2");
    auto ramp1_id       = addVertex("ramp1");
    auto ramp2_id       = addVertex("ramp2");
    auto scale1_id      = addVertex("scale1");
    auto scale2_id      = addVertex("scale2");
    auto plotter_id     = addVertex("timed_plotter");

    auto e_a_merge      = addEdge(a_id, merge2_id, "e_a_merge");
    auto e_b_merge      = addEdge(b_id, merge2_id, "e_b_merge");
    auto e_merge_server = addEdge(merge2_id, server_id, "merge_server");
    auto e_server_comm  = addEdge(server_id, comm_resp_id, "server_comm");

    auto e_clock1_ramp1 = addEdge(disc_clock1_id, ramp1_id, "clock1_ramp");
    auto e_clock2_ramp2 = addEdge(disc_clock2_id, ramp2_id, "clock2_ramp");

    auto e_ramp1_scale1   = addEdge(ramp1_id, scale1_id, "ramp1_scale1");
    auto e_ramp1_plotter  = addEdge(ramp1_id, plotter_id, "ramp1_plotter");
    auto e_ramp1_scale2   = addEdge(ramp1_id, scale2_id, "ramp1_scale2");
    auto e_scale1_plotter = addEdge(
        scale1_id, plotter_id, "scale1_plotter");
    auto e_scale2_plotter = addEdge(
        scale2_id, plotter_id, "scale2_plotter");

    auto e_ramp2_scape2 = addEdge(ramp2_id, scale2_id, "ramp2_scape2");


    auto root = elk::ElkGroupVisualAttribute::newRootGraph(run);
    run->addRootGroup(r_id, root);

    geometry::Size size{50, 30};
    geometry::Size port_size{5, 5};

    root->addVertex(r_id, a_id)->setSize(size);
    root->addVertex(r_id, b_id)->setSize(size);
    root->addVertex(r_id, merge2_id)->setSize(size);
    root->addVertex(r_id, server_id)->setSize(size);
    root->addVertex(r_id, comm_resp_id)->setSize(size);
    root->addVertex(r_id, disc_clock1_id)->setSize(size);
    root->addVertex(r_id, disc_clock2_id)->setSize(size);
    root->addVertex(r_id, ramp1_id)->setSize(size);
    root->addVertex(r_id, ramp2_id)->setSize(size);
    root->addVertex(r_id, scale1_id)->setSize(size);
    root->addVertex(r_id, scale2_id)->setSize(size);
    root->addVertex(r_id, plotter_id)->setSize(size);

    root->addEdge(e_a_merge);
    root->addEdge(e_b_merge);
    root->addEdge(e_merge_server);
    root->addEdge(e_server_comm);
    root->addEdge(e_clock1_ramp1);
    root->addEdge(e_clock2_ramp2);
    root->addEdge(e_ramp1_scale1);
    root->addEdge(e_ramp1_plotter);
    root->addEdge(e_ramp1_scale2);
    root->addEdge(e_scale1_plotter);
    root->addEdge(e_scale2_plotter);
    root->addEdge(e_ramp2_scape2);

    // a->merge
    root->addPort(addPort(a_id, e_a_merge, true))->setSize(port_size);
    root->addPort(addPort(merge2_id, e_a_merge, false))
        ->setSize(port_size);

    // b->merge
    root->addPort(addPort(b_id, e_b_merge, true))->setSize(port_size);
    root->addPort(addPort(merge2_id, e_b_merge, false))
        ->setSize(port_size);

    // merge->server
    root->addPort(addPort(merge2_id, e_merge_server, true))
        ->setSize(port_size);
    root->addPort(addPort(server_id, e_merge_server, false))
        ->setSize(port_size);

    // server->comm_resp, only one port for the edge
    root->addPort(addPort(server_id, e_server_comm, true))
        ->setSize(port_size);

    VertexIDSet all_vertices{
        a_id,
        b_id,
        merge2_id,
        server_id,
        comm_resp_id,
        disc_clock1_id,
        disc_clock2_id,
        ramp1_id,
        ramp2_id,
        scale1_id,
        scale2_id,
        plotter_id,
    };

    EXPECT_EQ(run->getDirectVertices(r_id).size(), 12);
    EXPECT_EQ((run->getDirectVertices(r_id) - all_vertices).size(), 0);

    // ports are assigned to individual rectangles, one edge has two ports
    // associated with two different rectangles.
    EXPECT_TRUE(run->ports->hasSourcePort(a_id, e_a_merge));
    EXPECT_FALSE(run->ports->hasTargetPort(a_id, e_a_merge));

    EXPECT_TRUE(run->ports->hasTargetPort(merge2_id, e_a_merge));
    EXPECT_FALSE(run->ports->hasSourcePort(merge2_id, e_a_merge));

    EXPECT_EQ(run->ports->getPortsForVertex(a_id).size(), 1);
    EXPECT_EQ(run->ports->getPortsForVertex(b_id).size(), 1);
    EXPECT_EQ(run->ports->getPortsForVertex(merge2_id).size(), 3);

    EXPECT_EQ(run->getDirectPorts(r_id).size(), 7);

    run->runFullLayout();

    hstd::writeFile(
        getDebugFile("repr.txt"), run->treeRepr().toString(false));

    auto const& res = run->result;

    EXPECT_OUTCOME_OK(checkLeftOf(
        run->getAbsoluteBBox(merge2_id), run->getAbsoluteBBox(a_id)));

    EXPECT_OUTCOME_OK(checkLeftOf(
        run->getAbsoluteBBox(merge2_id), run->getAbsoluteBBox(b_id)));

    // source port for b->merge
    EXPECT_OUTCOME_OK(checkRightOf(
        /*stationary=*/run->getAbsoluteBBox(b_id),
        /*relative=*/run->getAbsoluteBBox(
            run->ports->getPortForConnection(b_id, e_b_merge, true))));

    // source port for a->merge
    EXPECT_OUTCOME_OK(checkRightOf(
        /*stationary=*/run->getAbsoluteBBox(a_id),
        /*relative=*/run->getAbsoluteBBox(
            run->ports->getPortForConnection(a_id, e_a_merge, true))));

    // target port for a->merge
    EXPECT_OUTCOME_OK(checkLeftOf(
        /*stationary=*/run->getAbsoluteBBox(merge2_id),
        /*relative=*/run->getAbsoluteBBox(run->ports->getPortForConnection(
            merge2_id, e_a_merge, false))));

    // target port for b->merge
    EXPECT_OUTCOME_OK(checkLeftOf(
        /*stationary=*/run->getAbsoluteBBox(merge2_id),
        /*relative=*/run->getAbsoluteBBox(run->ports->getPortForConnection(
            merge2_id, e_a_merge, false))));


    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
}
