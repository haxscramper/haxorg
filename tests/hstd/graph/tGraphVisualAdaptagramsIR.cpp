#include "../t_graph_tests_common.hpp"

struct GraphAdaptagramsIR_Test : public GraphUtils_Test {};

TEST_F(GraphAdaptagramsIR_Test, LibcolaIr1) {
    VertexID v1    = graph->addVertex();
    VertexID v2    = graph->addVertex();
    VertexID rg_id = graph->addVertex();

    EdgeID e12 = graph->addEdge(v1, v2);

    ASSERT_NE(graph->getEdge(e12), nullptr);

    hstd::SPtr<cst::ColaGroup> root = cst::ColaGroup::newRootGraph(run);
    run->addRootGroup(rg_id, root);

    root->addVertex(rg_id, v1, Size(5, 5));
    root->addVertex(rg_id, v2, Size(6, 6));
    root->addEdge(e12);

    run->runFullLayout();

    auto const& res = run->result;

    ASSERT_TRUE(res.vertices.contains(v1));
    ASSERT_TRUE(res.vertices.contains(v2));
    ASSERT_TRUE(res.vertices.contains(rg_id));

    EXPECT_NEAR(run->getLayout(v1)->getBBox().width(), 5, 0.005);
    EXPECT_NEAR(run->getLayout(v1)->getBBox().height(), 5, 0.005);

    EXPECT_NEAR(run->getLayout(v2)->getBBox().width(), 6, 0.005);
    EXPECT_NEAR(run->getLayout(v2)->getBBox().height(), 6, 0.005);

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
}

TEST_F(GraphAdaptagramsIR_Test, LibcolaAlign) {
    VertexID v1    = graph->addVertex();
    VertexID v2    = graph->addVertex();
    VertexID v3    = graph->addVertex();
    VertexID v4    = graph->addVertex();
    VertexID rg_id = graph->addVertex();


    hstd::SPtr<cst::ColaGroup> root = cst::ColaGroup::newRootGraph(run);

    run->addRootGroup(rg_id, root);

    root->addVertex(rg_id, v1, Size(50, 50));
    root->addVertex(rg_id, v2, Size(60, 60));
    root->addVertex(rg_id, v3, Size(70, 70));
    root->addVertex(rg_id, v4, Size(80, 80));

    root->addConstraint<cst::AlignConstraint>(root)
        ->useX()
        ->addAlignVertex(v1)
        ->addAlignVertex(v2);

    root->addConstraint<cst::AlignConstraint>(root)
        ->useY()
        ->addAlignVertex(v1)
        ->addAlignVertex(v4);

    run->runFullLayout();

    auto const& res = run->result;

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());

    EXPECT_OUTCOME_OK(
        checkAlignedHorizontally(run->getVisual(v1), run->getVisual(v4)));

    EXPECT_OUTCOME_OK(
        checkAlignedVertically(run->getVisual(v1), run->getVisual(v2)));
}

TEST_F(GraphAdaptagramsIR_Test, LibcolaIr3) {
    hstd::Vec<VertexID> vs;
    hstd::Vec<EdgeID>   es;

    for (int i = 0; i < 12; ++i) { vs.push_back(graph->addVertex()); }

    auto add_edge = [&](int source, int target) {
        es.push_back(graph->addEdge(vs.at(source), vs.at(target)));
    };

    VertexID rg_id = graph->addVertex();

    add_edge(0, 3);
    add_edge(1, 4);
    add_edge(1, 5);
    add_edge(1, 6);
    add_edge(2, 7);
    add_edge(3, 8);
    add_edge(4, 8);
    add_edge(4, 9);
    add_edge(5, 9);
    add_edge(6, 9);
    add_edge(6, 10);
    add_edge(7, 9);
    add_edge(7, 11);

    hstd::SPtr<cst::ColaGroup> root = cst::ColaGroup::newRootGraph(run);
    run->addRootGroup(rg_id, root);
    root->getAlgorithm<cst::ColaLayoutAlgorithm>()
        ->router->shapeBufferDistance = 25;

    for (VertexID v : vs) { root->addVertex(rg_id, v, Size(75, 25)); }
    for (EdgeID e : es) { root->addEdge(e); }

    root->addConstraint<cst::AlignConstraint>(root)
        ->useX()
        ->addAlignVertex(vs.at(0))
        ->addAlignVertex(vs.at(1))
        ->addAlignVertex(vs.at(2));

    root->addConstraint<cst::AlignConstraint>(root)
        ->useX()
        ->addAlignVertex(vs.at(3))
        ->addAlignVertex(vs.at(4))
        ->addAlignVertex(vs.at(5))
        ->addAlignVertex(vs.at(6))
        ->addAlignVertex(vs.at(7));

    root->addConstraint<cst::AlignConstraint>(root)
        ->useX()
        ->addAlignVertex(vs.at(8))
        ->addAlignVertex(vs.at(9))
        ->addAlignVertex(vs.at(10))
        ->addAlignVertex(vs.at(11));

    run->runFullLayout();

    auto const& res = run->result;
    EXPECT_EQ(res.vertices.size(), 13);
    EXPECT_EQ(res.edges.size(), 13);

    for (EdgeID e : es) {
        ASSERT_TRUE(res.edges.contains(e));
        EXPECT_TRUE(!res.edges.at(e)->getPath().commands.empty());
    }

    hstd::writeFile(
        getDebugFile("libcola_ir3.svg"),
        hstd::ext::visual::toSvg(run->getVisual(), /*debug=*/false)
            .to_string());
}

TEST_F(GraphAdaptagramsIR_Test, LibcolaIrMultiSeparate) {
    hstd::Vec<VertexID> vs;
    hstd::Vec<EdgeID>   es;

    for (int i = 0; i < 12; ++i) { vs.push_back(graph->addVertex()); }

    VertexID rg_id = graph->addVertex();

    hstd::SPtr<cst::ColaGroup> root = cst::ColaGroup::newRootGraph(run);
    run->addRootGroup(rg_id, root);
    root->getAlgorithm<cst::ColaLayoutAlgorithm>()
        ->router->shapeBufferDistance = 25;

    for (VertexID v : vs) { root->addVertex(rg_id, v, Size(75, 25)); }

    root->addConstraint<cst::MultiSeparateConstraint>(root)
        ->separateHorizontally()
        ->addFullLane({vs.at(0), vs.at(1), vs.at(2)})
        ->addFullLane({vs.at(3), vs.at(4), vs.at(5), vs.at(6), vs.at(7)})
        ->addFullLane({vs.at(8), vs.at(9), vs.at(10), vs.at(11)})
        ->setSeparationDistance(120);

    run->runFullLayout();

    auto const& res = run->result;
    EXPECT_EQ(res.vertices.size(), 13);

    hstd::writeFile(
        getDebugFile("libcola_ir_multi_separate.svg"),
        hstd::ext::visual::toSvg(run->getVisual(), /*debug=*/false)
            .to_string());
}

TEST_F(GraphAdaptagramsIR_Test, LibcolaIrMultiEdge) {
    VertexID v0    = graph->addVertex();
    VertexID v1    = graph->addVertex();
    VertexID rg_id = graph->addVertex();

    hstd::Vec<EdgeID> es;
    es.push_back(graph->addEdge(v0, v1));
    es.push_back(graph->addEdge(v0, v1));
    es.push_back(graph->addEdge(v0, v1));
    es.push_back(graph->addEdge(v0, v1));

    hstd::SPtr<cst::ColaGroup> root = cst::ColaGroup::newRootGraph(run);
    run->addRootGroup(rg_id, root);

    root->addVertex(rg_id, v0, Size(25, 100));
    root->addVertex(rg_id, v1, Size(25, 100));

    root->addConstraint<cst::AlignConstraint>(root)
        ->useY()
        ->addAlignVertex(v0)
        ->addAlignVertex(v1);

    for (EdgeID e : es) { root->addEdge(e); }

    run->runFullLayout();

    auto const& res = run->result;
    EXPECT_EQ(res.vertices.size(), 3);
    EXPECT_EQ(res.edges.size(), 4);

    for (EdgeID e : es) {
        ASSERT_TRUE(res.edges.contains(e));
        EXPECT_TRUE(!res.edges.at(e)->getPath().commands.empty());
    }

    hstd::writeFile(
        getDebugFile("libcola_ir_multi_edge.svg"),
        hstd::ext::visual::toSvg(run->getVisual(), /*debug=*/false)
            .to_string());
}

TEST_F(GraphAdaptagramsIR_Test, LibcolaSubgroups) {
    hstd::Vec<VertexID> vs;
    hstd::Vec<EdgeID>   es;
    for (int i = 0; i < 11; ++i) {
        auto id = graph->addVertex();
        graph->getCastMVertex<TrivialVertex>(id)
            ->stableIdOverride = hstd::fmt("id_{}", i);
        vs.push_back(id);
    }

    auto edge = [&](int source, int target) {
        es.push_back(graph->addEdge(vs.at(source), vs.at(target)));
    };

    VertexID rg_id = graph->addVertex();
    graph->getCastMVertex<TrivialVertex>(rg_id)
        ->stableIdOverride = "rg_id";
    VertexID sg_id1        = graph->addVertex();
    graph->getCastMVertex<TrivialVertex>(rg_id)
        ->stableIdOverride = "sg_id1";
    VertexID sg_id2        = graph->addVertex();
    graph->getCastMVertex<TrivialVertex>(rg_id)
        ->stableIdOverride = "sg_id2";

    edge(0, 2);  // 0
    edge(2, 1);  // 1
    edge(1, 8);  // 2
    edge(8, 3);  // 3
    edge(3, 4);  // 4
    edge(4, 6);  // 5
    edge(3, 6);  // 6
    edge(8, 5);  // 7
    edge(5, 9);  // 8
    edge(9, 10); // 9
    edge(10, 7); // 10
    edge(7, 5);  // 11

    hstd::SPtr<cst::ColaGroup> root = cst::ColaGroup::newRootGraph(run);
    auto                       ctx  = root->shared;

    run->addRootGroup(rg_id, root);

    hstd::SPtr<cst::ColaGroup> sg_1 = root->addNewNativeSubgroup(
        rg_id, sg_id1);
    hstd::SPtr<cst::ColaGroup> sg_2 = root->addNewNativeSubgroup(
        rg_id, sg_id2);

    // root nodes
    root->addVertex(rg_id, vs.at(0), Size(25, 25));
    root->addVertex(rg_id, vs.at(1), Size(25, 25));

    // sub group 1
    sg_1->addVertex(sg_id1, vs.at(2), Size(25, 25));
    sg_1->addVertex(sg_id1, vs.at(3), Size(25, 25));
    sg_1->addVertex(sg_id1, vs.at(4), Size(25, 25));
    sg_1->addVertex(sg_id1, vs.at(5), Size(25, 25));

    // sub group 2
    sg_2->addVertex(sg_id2, vs.at(6), Size(25, 25));
    sg_2->addVertex(sg_id2, vs.at(7), Size(25, 25));
    sg_2->addVertex(sg_id2, vs.at(8), Size(25, 25));
    sg_2->addVertex(sg_id2, vs.at(9), Size(25, 25));
    sg_2->addVertex(sg_id2, vs.at(10), Size(25, 25));

    run->runFullLayout();

    auto const& res = run->result;

    hstd::writeFile(
        getDebugFile("libcola_sub_group.svg"),
        hstd::ext::visual::toSvg(run->getVisual(), /*debug=*/false)
            .to_string());
}
