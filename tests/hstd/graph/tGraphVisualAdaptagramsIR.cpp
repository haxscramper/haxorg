#include "../t_graph_tests_common.hpp"
#include <hstd/stdlib/Ranges.hpp>

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
        ->useVerticalAxis()
        ->addAlignVertex(v1)
        ->addAlignVertex(v2);

    root->addConstraint<cst::AlignConstraint>(root)
        ->useHorizontalAxis()
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

class GraphAdaptagramsIR_BoolParamTest
    : public GraphAdaptagramsIR_Test
    , public testing::WithParamInterface<bool> {};

TEST_P(GraphAdaptagramsIR_BoolParamTest, LibcolaAlign_Offset) {
    VertexID v1    = addVertex("v1");
    VertexID v2    = addVertex("v2");
    VertexID v3    = addVertex("v3");
    VertexID rg_id = addVertex("rg");

    hstd::SPtr<cst::ColaGroup> root = cst::ColaGroup::newRootGraph(run);

    run->addRootGroup(rg_id, root);

    root->addVertex(rg_id, v1, Size(50, 50));
    root->addVertex(rg_id, v2, Size(60, 60));
    root->addVertex(rg_id, v3, Size(70, 70));

    bool const is_vertical = GetParam();

    auto c = root->addConstraint<cst::AlignConstraint>(root);

    if (is_vertical) {
        c->useVerticalAxis();
    } else {
        c->useHorizontalAxis();
    }

    c //
        ->addAlignVertex(v1, cst::AlignConstraint::AxisAlign::Center, 0)
        ->addAlignVertex(v2, cst::AlignConstraint::AxisAlign::Center, 50)
        ->addAlignVertex(v3, cst::AlignConstraint::AxisAlign::Center, 100);

    run->runFullLayout();

    auto const& res = run->result;

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/true).to_string());

    auto offset = is_vertical ? geometry::Point{50, 0}
                              : geometry::Point{0, 50};

    if (is_vertical) {
        EXPECT_OUTCOME_OK(checkAlignedVertically(
            run->getVisual(v1).computeBounds().center(),
            run->getVisual(v2).computeBounds().center() - offset));

        EXPECT_OUTCOME_OK(checkAlignedVertically(
            run->getVisual(v2).computeBounds().center(),
            run->getVisual(v3).computeBounds().center() - offset));

        EXPECT_OUTCOME_OK(checkAlignedVertically(
            run->getVisual(v1).computeBounds().center(),
            run->getVisual(v3).computeBounds().center() - offset * 2));
    } else {
        EXPECT_OUTCOME_OK(checkAlignedHorizontally(
            run->getVisual(v1).computeBounds().center(),
            run->getVisual(v2).computeBounds().center() - offset));

        EXPECT_OUTCOME_OK(checkAlignedHorizontally(
            run->getVisual(v2).computeBounds().center(),
            run->getVisual(v3).computeBounds().center() - offset));

        EXPECT_OUTCOME_OK(checkAlignedHorizontally(
            run->getVisual(v1).computeBounds().center(),
            run->getVisual(v3).computeBounds().center() - offset * 2));
    }
}

TEST_P(GraphAdaptagramsIR_BoolParamTest, SeparationConstraintAlign) {
    VertexID v1    = addVertex("v1");
    VertexID v2    = addVertex("v2");
    VertexID v3    = addVertex("v3");
    VertexID v4    = addVertex("v4");
    VertexID rg_id = addVertex("rg");

    hstd::SPtr<cst::ColaGroup> root = cst::ColaGroup::newRootGraph(run);

    run->addRootGroup(rg_id, root);

    root->addVertex(rg_id, v1, Size(50, 50));
    root->addVertex(rg_id, v2, Size(60, 60));
    root->addVertex(rg_id, v3, Size(70, 70));
    root->addVertex(rg_id, v4, Size(50, 50));

    bool const is_vertical = GetParam();

    auto c = root->addConstraint<cst::SeparateConstraint>(root);

    if (is_vertical) {
        c->separateVertically();
    } else {
        c->separateHorizontally();
    }

    c->setSeparationDistance(90)
        ->setIsExactSeparation(true)
        ->addLeftVertex(v1)
        ->addLeftVertex(v2)
        ->addRightVertex(v3)
        ->addRightVertex(v4);

    run->runFullLayout();

    auto const& res = run->result;

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/true).to_string());

    auto v1_center = run->getVisual(v1).computeBounds().center();
    auto v2_center = run->getVisual(v2).computeBounds().center();
    auto v3_center = run->getVisual(v3).computeBounds().center();
    auto v4_center = run->getVisual(v4).computeBounds().center();

    auto debug = hstd::fmt(
        "v1:{} v2:{} v3:{} v4:{}",
        v1_center,
        v2_center,
        v3_center,
        v4_center);

    if (is_vertical) {
        EXPECT_OUTCOME_OK(checkAlignedHorizontally(v1_center, v2_center));
        EXPECT_OUTCOME_OK(checkAlignedHorizontally(v3_center, v4_center));
        EXPECT_NEAR(v1_center.y() + 90, v4_center.y(), 0.005) << debug;
        EXPECT_NEAR(v2_center.y() + 90, v3_center.y(), 0.005) << debug;
    } else {
        EXPECT_OUTCOME_OK(checkAlignedVertically(v1_center, v2_center));
        EXPECT_OUTCOME_OK(checkAlignedVertically(v3_center, v4_center));
        EXPECT_NEAR(v1_center.x() + 90, v4_center.x(), 0.005) << debug;
        EXPECT_NEAR(v2_center.x() + 90, v3_center.x(), 0.005) << debug;
    }
}

TEST_P(GraphAdaptagramsIR_BoolParamTest, SeparationConstraintAlignLarge) {
    VertexID rg_id = addVertex("rg");

    hstd::Vec<VertexIDVec> vert;

    for (int align_row = 0; align_row < 6; ++align_row) {
        VertexIDVec row;
        for (int align_col = 0; align_col < 6; ++align_col) {
            row.push_back(
                addVertex(hstd::fmt("v_{}_{}", align_row, align_col)));
        }
        vert.push_back(row);
    }

    hstd::SPtr<cst::ColaGroup> root = cst::ColaGroup::newRootGraph(run);

    run->addRootGroup(rg_id, root);
    for (auto const& row : vert) {
        for (auto const& col : row) {
            root->addVertex(rg_id, col, Size(50, 50));
        }
    }

    bool const is_vertical = GetParam();

    hstd::Vec<cst::SeparateConstraint*> separations;

    int sep_distance = 90;
    for (auto const& [row_idx, row] : enumerate(vert)) {
        auto c = root->addConstraint<cst::SeparateConstraint>(root)
                     ->setSeparationDistance(90)
                     ->setIsExactSeparation(true);

        if (is_vertical) {
            c->separateVertically();
        } else {
            c->separateHorizontally();
        }

        if (row_idx == 0) {
            c->addLeftVertex(row);
            c->addRightVertex(vert.at(row_idx + 1));
        } else {
            c->addLeftVertex(vert.at(row_idx - 1).at(0));
            c->addRightVertex(row);
        }

        separations.push_back(c);
    }

    run->runFullLayout();

    auto const& res = run->result;

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/true).to_string());

    auto get_c = [&](VertexID const& id) -> geometry::Point {
        return run->getVisual(id).computeBounds().center();
    };

    if (is_vertical) {
        //   ┌───┐┌───┐┌───┐┌───┐┌───┐
        // ┌─┼───┼┼───┼┼───┼┼───┼┼───│
        // │ └───┘└───┘└───┘└───┘└───┘
        // │ ┌───┐┌───┐┌───┐┌───┐┌───┐
        // ├─┼───┼┼───┼┼───┼┼───┼┼───│
        // │ └───┘└───┘└───┘└───┘└───┘
        // │ ┌───┐┌───┐┌───┐┌───┐┌───┐
        // ├─┼───┼┼───┼┼───┼┼───┼┼───│
        // │ └───┘└───┘└───┘└───┘└───┘
        // │ ┌───┐┌───┐┌───┐┌───┐┌───┐
        // └─┼───┼┼───┼┼───┼┼───┼┼───│
        //   └───┘└───┘└───┘└───┘└───┘
        for (auto const& row : vert) {
            for (auto const& col : row | hstd::rv::sliding(2)) {
                EXPECT_OUTCOME_OK(checkAlignedHorizontally(
                    get_c(col[0]), get_c(col[1])));
            }
        }

        for (auto const& row : vert | hstd::rv::sliding(2)) {
            for (auto const& col : hstd::rv::zip(row[0], row[1])) {
                EXPECT_NEAR(
                    get_c(col.first).y() + 90,
                    get_c(col.second).y(),
                    0.005);
            }
        }
    } else {
        //   ┌────┬────┬────┬────┐
        // ┌─┼─┐┌─┼─┐┌─┼─┐┌─┼─┐┌─┼─┐
        // │ │ ││ │ ││ │ ││ │ ││ │ │
        // └─┼─┘└─┼─┘└─┼─┘└─┼─┘└─┼─┘
        // ┌─┼─┐┌─┼─┐┌─┼─┐┌─┼─┐┌─┼─┐
        // │ │ ││ │ ││ │ ││ │ ││ │ │
        // └─┼─┘└─┼─┘└─┼─┘└─┼─┘└─┼─┘
        // ┌─┼─┐┌─┼─┐┌─┼─┐┌─┼─┐┌─┼─┐
        // │ │ ││ │ ││ │ ││ │ ││ │ │
        // └─┼─┘└─┼─┘└─┼─┘└─┼─┘└─┼─┘
        // ┌─┼─┐┌─┼─┐┌─┼─┐┌─┼─┐┌─┼─┐
        // │ │ ││ │ ││ │ ││ │ ││ │ │
        // └───┘└───┘└───┘└───┘└───┘
        for (auto const& row : vert) {
            for (auto const& col : row | hstd::rv::sliding(2)) {
                EXPECT_OUTCOME_OK(
                    checkAlignedVertically(get_c(col[0]), get_c(col[1])));
            }
        }

        for (auto const& row : vert | hstd::rv::sliding(2)) {
            for (auto const& col : hstd::rv::zip(row[0], row[1])) {
                EXPECT_NEAR(
                    get_c(col.first).x() + 90,
                    get_c(col.second).x(),
                    0.005);
            }
        }
    }
}


INSTANTIATE_TEST_SUITE_P(
    BoolCases,
    GraphAdaptagramsIR_BoolParamTest,
    testing::Values(false, true));

TEST_F(GraphAdaptagramsIR_Test, MultiSeparationConstraint) {
    VertexID rg_id = addVertex("rg");

    hstd::Vec<VertexIDVec> grid;
    int                    size = 6;

    for (int align_row = 0; align_row < size; ++align_row) {
        VertexIDVec row;
        for (int align_col = 0; align_col < size; ++align_col) {
            row.push_back(
                addVertex(hstd::fmt("v_{}_{}", align_row, align_col)));
        }
        grid.push_back(row);
    }

    hstd::SPtr<cst::ColaGroup> root = cst::ColaGroup::newRootGraph(run);

    run->addRootGroup(rg_id, root);
    for (auto const& row : grid) {
        for (auto const& col : row) {
            root->addVertex(rg_id, col, Size(50, 50));
        }
    }

    int  sep_distance = 90;
    auto sep1 = root->addConstraint<cst::MultiSeparateConstraint>(root)
                    ->setSeparationDistance(sep_distance)
                    ->separateVertically()
                    ->setIsExactSeparation(true);

    auto sep2 = root->addConstraint<cst::MultiSeparateConstraint>(root)
                    ->setSeparationDistance(sep_distance)
                    ->separateHorizontally()
                    ->setIsExactSeparation(true);

    hstd::Vec<VertexIDVec>
        grid_T = hstd::rv::iota(0, size)
               | hstd::rv::transform([&](int col) -> VertexIDVec {
                     return grid
                          | hstd::rv::transform(
                                [&](VertexIDVec const& v) -> VertexID {
                                    return v.at(col);
                                })
                          | hstd::rs::to<hstd::Vec>();
                 })
               | hstd::rs::to<hstd::Vec>();


    for (auto const& row : grid) { sep1->addFullLane(row); }
    for (auto const& col : grid_T) { sep2->addFullLane(col); }

    run->runFullLayout();

    auto const& res = run->result;

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/true).to_string());

    auto get_c = [&](VertexID const& id) -> geometry::Point {
        return run->getVisual(id).computeBounds().center();
    };

    //   ┌───┐┌───┐┌───┐┌───┐┌───┐
    // ┌─┼───┼┼───┼┼───┼┼───┼┼───│
    // │ └───┘└───┘└───┘└───┘└───┘
    // │ ┌───┐┌───┐┌───┐┌───┐┌───┐
    // ├─┼───┼┼───┼┼───┼┼───┼┼───│
    // │ └───┘└───┘└───┘└───┘└───┘
    // │ ┌───┐┌───┐┌───┐┌───┐┌───┐
    // ├─┼───┼┼───┼┼───┼┼───┼┼───│
    // │ └───┘└───┘└───┘└───┘└───┘
    // │ ┌───┐┌───┐┌───┐┌───┐┌───┐
    // └─┼───┼┼───┼┼───┼┼───┼┼───│
    //   └───┘└───┘└───┘└───┘└───┘
    for (auto const& row : grid) {
        for (auto const& col : row | hstd::rv::sliding(2)) {
            EXPECT_OUTCOME_OK(
                checkAlignedHorizontally(get_c(col[0]), get_c(col[1])),
                hstd::fmt(
                    "Failed to align {} and {}",
                    run->getGraph()->getDebugVertexFormat(col[0]),
                    run->getGraph()->getDebugVertexFormat(col[1])));
        }
    }

    for (auto const& col : grid_T) {
        for (auto const& row : col | hstd::rv::sliding(2)) {
            EXPECT_OUTCOME_OK(
                checkAlignedVertically(get_c(col[0]), get_c(col[1])),
                hstd::fmt(
                    "Failed to align {} and {}",
                    run->getGraph()->getDebugVertexFormat(col[0]),
                    run->getGraph()->getDebugVertexFormat(col[1])));
        }
    }
}


TEST_F(GraphAdaptagramsIR_Test, LibcolaIr3) {
    VertexIDVec       vs;
    hstd::Vec<EdgeID> es;

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
        ->useVerticalAxis()
        ->addAlignVertex(vs.at(0))
        ->addAlignVertex(vs.at(1))
        ->addAlignVertex(vs.at(2));

    root->addConstraint<cst::AlignConstraint>(root)
        ->useVerticalAxis()
        ->addAlignVertex(vs.at(3))
        ->addAlignVertex(vs.at(4))
        ->addAlignVertex(vs.at(5))
        ->addAlignVertex(vs.at(6))
        ->addAlignVertex(vs.at(7));

    root->addConstraint<cst::AlignConstraint>(root)
        ->useVerticalAxis()
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
    VertexIDVec       vs;
    hstd::Vec<EdgeID> es;

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
        ->useHorizontalAxis()
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
    VertexIDVec       vs;
    hstd::Vec<EdgeID> es;
    for (int i = 0; i < 11; ++i) {
        auto id = graph->addVertex();
        graph->getCastMVertex<TrivialVertex>(id)
            ->stableIdOverride = hstd::fmt("id_{}", i);
        vs.push_back(id);
    }

    auto edge = [&](int source, int target) {
        es.push_back(graph->addEdge(vs.at(source), vs.at(target)));
    };

    VertexID rg_id  = addVertex("rg_id");
    VertexID sg_id1 = addVertex("sg_id1");
    VertexID sg_id2 = addVertex("sg_id2");

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

    int const size = 50;

    // root nodes
    root->addVertex(rg_id, vs.at(0), Size(size, size));
    root->addVertex(rg_id, vs.at(1), Size(size, size));

    sg_1->addConstraint<cst::SeparateConstraint>(sg_1)
        ->separateHorizontally()
        ->setSeparationDistance(size * 3)
        ->addLeftVertex(vs.at(2))
        ->addRightVertex(vs.at(6));

    // sub group 1
    sg_1->addVertex(sg_id1, vs.at(2), Size(size, size));
    sg_1->addVertex(sg_id1, vs.at(3), Size(size, size));
    sg_1->addVertex(sg_id1, vs.at(4), Size(size, size));
    sg_1->addVertex(sg_id1, vs.at(5), Size(size, size));

    sg_1->addConstraint<cst::SeparateConstraint>(sg_1)
        ->separateHorizontally()
        ->addLeftVertex(vs.at(2))
        ->addLeftVertex(vs.at(4))
        ->addRightVertex(vs.at(3))
        ->addRightVertex(vs.at(5));

    // sub group 2
    sg_2->addVertex(sg_id2, vs.at(6), Size(size, size));
    sg_2->addVertex(sg_id2, vs.at(7), Size(size, size));
    sg_2->addVertex(sg_id2, vs.at(8), Size(size, size));
    sg_2->addVertex(sg_id2, vs.at(9), Size(size, size));
    sg_2->addVertex(sg_id2, vs.at(10), Size(size, size));

    sg_2->addConstraint<cst::AlignConstraint>(sg_2)
        ->useHorizontalAxis()
        ->addAlignVertex(
            vs.at(6), cst::AlignConstraint::AxisAlign::Center, 0)
        ->addAlignVertex(
            vs.at(7), cst::AlignConstraint::AxisAlign::Center, size)
        ->addAlignVertex(
            vs.at(8), cst::AlignConstraint::AxisAlign::Center, size * 2)
        ->addAlignVertex(
            vs.at(9), cst::AlignConstraint::AxisAlign::Center, size * 3)
        ->addAlignVertex(
            vs.at(10), cst::AlignConstraint::AxisAlign::Center, size * 4);

    sg_2->addConstraint<cst::MultiSeparateConstraint>(sg_2)
        ->separateHorizontally()
        ->setSeparationDistance(size)
        ->addFullLane({vs.at(6)})
        ->addFullLane({vs.at(7)})
        ->addFullLane({vs.at(8)})
        ->addFullLane({vs.at(9)})
        ->addFullLane({vs.at(10)});

    run->runFullLayout();

    auto const& res = run->result;

    hstd::writeFile(
        getDebugFile("libcola_sub_group.svg"),
        hstd::ext::visual::toSvg(run->getVisual(), /*debug=*/false)
            .to_string());
}
