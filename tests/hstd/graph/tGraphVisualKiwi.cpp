#include "../t_graph_tests_common.hpp"
#include <hstd/ext/graph/visual/graph_kiwi.hpp>
#include <hstd/stdlib/Ranges.hpp>

struct GraphKiwi_Test : public GraphUtils_Test {};

TEST_F(GraphKiwi_Test, KiwiIr1) {
    VertexID v1    = getGraph()->addVertex("v1");
    VertexID v2    = getGraph()->addVertex("v2");
    VertexID rg_id = getGraph()->addVertex("rg");

    EdgeID e12 = getGraph()->addEdge(v1, v2);

    ASSERT_NE(getGraph()->getEdge(e12), nullptr);

    hstd::SPtr<kw::KiwiGroup> root = kw::KiwiGroup::newRootGraph(run);
    run->setRootGroupAttribute(rg_id, root);

    root->addVertex(addNesting(rg_id, v1), Size(5, 5));
    root->addVertex(addNesting(rg_id, v2), Size(6, 6));
    root->addEdge(e12);

    run->runFullLayout();

    auto const& res = run->result;
    ASSERT_TRUE(res.vertices.contains(v1));
    ASSERT_TRUE(res.vertices.contains(v2));
    ASSERT_TRUE(res.vertices.contains(rg_id));

    EXPECT_NEAR(box(v1).width(), 5, 0.005);
    EXPECT_NEAR(box(v1).height(), 5, 0.005);
    EXPECT_NEAR(box(v2).width(), 6, 0.005);
    EXPECT_NEAR(box(v2).height(), 6, 0.005);
}

TEST_F(GraphKiwi_Test, KiwiFixedAbsoluteRelative) {
    VertexID v_fixed    = getGraph()->addVertex("v_fixed");
    VertexID v_relative = getGraph()->addVertex("v_relative");
    VertexID rg_id      = getGraph()->addVertex("rg");

    hstd::SPtr<kw::KiwiGroup> root = kw::KiwiGroup::newRootGraph(run);
    run->setRootGroupAttribute(rg_id, root);

    root->addVertex(addNesting(rg_id, v_fixed), Size(5, 5));
    root->addVertex(addNesting(rg_id, v_relative), Size(6, 6));

    root->addConstraint<kw::RelativeConstraint>(root, v_fixed, v_relative)
        ->setAbsoluteOffset(10, 10);

    run->runFullLayout();
    writeVisual();

    EXPECT_OUTCOME_OK(checkDistance(
        box(v_fixed).upper_left(),
        box(v_relative).upper_left(),
        10,
        DistanceCheck::XOnly));

    EXPECT_OUTCOME_OK(checkDistance(
        box(v_fixed).upper_left(),
        box(v_relative).upper_left(),
        10,
        DistanceCheck::YOnly));
}

TEST_F(GraphKiwi_Test, KiwiFixedRelativeRelative) {
    VertexID v_fixed    = getGraph()->addVertex("v_fixed");
    VertexID v_relative = getGraph()->addVertex("v_relative");
    VertexID rg_id      = getGraph()->addVertex("rg");

    hstd::SPtr<kw::KiwiGroup> root = kw::KiwiGroup::newRootGraph(run);
    run->setRootGroupAttribute(rg_id, root);

    root->addVertex(addNesting(rg_id, v_fixed), Size(5, 5));
    root->addVertex(addNesting(rg_id, v_relative), Size(6, 6));

    root->addConstraint<kw::RelativeConstraint>(root, v_fixed, v_relative)
        ->setRelativeOffset(10, 10);

    run->runFullLayout();
    writeVisual();

    EXPECT_OUTCOME_OK(checkDistance(
        box(v_fixed).upper_left(),
        box(v_relative).upper_left(),
        50,
        DistanceCheck::XOnly));

    EXPECT_OUTCOME_OK(checkDistance(
        box(v_fixed).upper_left(),
        box(v_relative).upper_left(),
        50,
        DistanceCheck::YOnly));
}

// TODO: Test the same configuration but with the gaps between graph
// elements.
TEST_F(GraphKiwi_Test, KiwiLinearConstraintTrivial) {
    VertexID v_center     = getGraph()->addVertex("v_center");
    VertexID v_up_left    = getGraph()->addVertex("v_up_left");
    VertexID v_up_right   = getGraph()->addVertex("v_up_right");
    VertexID v_down_left  = getGraph()->addVertex("v_down_left");
    VertexID v_down_right = getGraph()->addVertex("v_down_right");
    VertexID rg_id        = getGraph()->addVertex("rg");

    hstd::SPtr<kw::KiwiGroup> root = kw::KiwiGroup::newRootGraph(run);
    run->setRootGroupAttribute(rg_id, root);

    root->addVertex(addNesting(rg_id, v_center), Size(50, 50));
    root->addVertex(addNesting(rg_id, v_up_left), Size(50, 50));
    root->addVertex(addNesting(rg_id, v_up_right), Size(50, 50));
    root->addVertex(addNesting(rg_id, v_down_left), Size(50, 50));
    root->addVertex(addNesting(rg_id, v_down_right), Size(50, 50));

    root->addConstraint<kw::LinearConstraint>(root) //
        ->setSecondBelowFirst(v_center, v_down_left);

    root->addConstraint<kw::LinearConstraint>(root) //
        ->setSecondBelowFirst(v_center, v_down_right);

    root->addConstraint<kw::LinearConstraint>(root) //
        ->setSecondAboveFirst(v_center, v_up_left);

    root->addConstraint<kw::LinearConstraint>(root) //
        ->setSecondAboveFirst(v_center, v_up_right);

    root->addConstraint<kw::LinearConstraint>(root) //
        ->setSecondLeftOfFirst(v_center, v_down_left);

    root->addConstraint<kw::LinearConstraint>(root) //
        ->setSecondLeftOfFirst(v_center, v_up_left);

    root->addConstraint<kw::LinearConstraint>(root) //
        ->setSecondRightOfFirst(v_center, v_down_right);

    root->addConstraint<kw::LinearConstraint>(root) //
        ->setSecondRightOfFirst(v_center, v_up_right);

    run->runFullLayout();
    writeVisual();

    EXPECT_OUTCOME_OK(checkLeftOf(box(v_center), box(v_up_left)));
    EXPECT_OUTCOME_OK(checkLeftOf(box(v_center), box(v_down_left)));
    EXPECT_OUTCOME_OK(checkRightOf(box(v_center), box(v_up_right)));
    EXPECT_OUTCOME_OK(checkRightOf(box(v_center), box(v_down_right)));
    EXPECT_OUTCOME_OK(checkLeftOf(box(v_up_right), box(v_up_left)));
}

TEST_F(GraphKiwi_Test, KiwiLinearConstraintPartialInset) {
    VertexID v_center     = getGraph()->addVertex("v_center");
    VertexID v_up_left    = getGraph()->addVertex("v_up_left");
    VertexID v_up_right   = getGraph()->addVertex("v_up_right");
    VertexID v_down_left  = getGraph()->addVertex("v_down_left");
    VertexID v_down_right = getGraph()->addVertex("v_down_right");
    VertexID rg_id        = getGraph()->addVertex("rg");

    hstd::SPtr<kw::KiwiGroup> root = kw::KiwiGroup::newRootGraph(run);
    run->setRootGroupAttribute(rg_id, root);


    double inset = 10.0;
    double size  = 50.0;

    root->addVertex(addNesting(rg_id, v_center), Size(size, size));
    root->addVertex(addNesting(rg_id, v_up_left), Size(size, size));
    root->addVertex(addNesting(rg_id, v_up_right), Size(size, size));
    root->addVertex(addNesting(rg_id, v_down_left), Size(size, size));
    root->addVertex(addNesting(rg_id, v_down_right), Size(size, size));

    auto add_inset = [&](VertexID const&   relative,
                         kiwi_ir::RectAttr fixed_anchor,
                         kiwi_ir::RectAttr relative_anchor,
                         double            relative_inset) {
        auto c = root->addConstraint<kw::LinearConstraint>(root);
        c->finalize(
            c->use(v_center, fixed_anchor),
            kiwi_ir::Relation::EQ,
            c->use(relative, relative_anchor) + relative_inset);
    };


    // clang-format off
    add_inset(v_up_left,    kiwi_ir::RectAttr::TOP,    kiwi_ir::RectAttr::BOTTOM, -inset);
    add_inset(v_up_left,    kiwi_ir::RectAttr::LEFT,   kiwi_ir::RectAttr::RIGHT,  -inset);
    add_inset(v_up_right,   kiwi_ir::RectAttr::TOP,    kiwi_ir::RectAttr::BOTTOM, -inset);
    add_inset(v_up_right,   kiwi_ir::RectAttr::RIGHT,  kiwi_ir::RectAttr::LEFT,   inset);
    add_inset(v_down_left,  kiwi_ir::RectAttr::BOTTOM, kiwi_ir::RectAttr::TOP,    inset);
    add_inset(v_down_left,  kiwi_ir::RectAttr::LEFT,   kiwi_ir::RectAttr::RIGHT,  -inset);
    add_inset(v_down_right, kiwi_ir::RectAttr::BOTTOM, kiwi_ir::RectAttr::TOP,    inset);
    add_inset(v_down_right, kiwi_ir::RectAttr::RIGHT,  kiwi_ir::RectAttr::LEFT,   inset);
    // clang-format on

    run->runFullLayout();
    writeVisual();

    double line_percent    = (inset / size) * 100.0;
    double overlap_percent = (inset * inset) / (size * size) * 100.0;

    EXPECT_OUTCOME_OK(checkPartiallyLeft(box(v_center), box(v_up_left), line_percent));
    EXPECT_OUTCOME_OK(checkPartiallyLeft(box(v_center), box(v_down_left), line_percent));
    EXPECT_OUTCOME_OK(checkPartiallyRight(box(v_center), box(v_up_right), line_percent));
    EXPECT_OUTCOME_OK(
        checkPartiallyRight(box(v_center), box(v_down_right), line_percent));
    EXPECT_OUTCOME_OK(checkPartiallyLeft(box(v_up_right), box(v_up_left), line_percent));
    EXPECT_OUTCOME_OK(
        checkPartiallyCovers(box(v_center), box(v_up_right), overlap_percent));
    EXPECT_OUTCOME_OK(
        checkPartiallyCovers(box(v_center), box(v_up_left), overlap_percent));
    EXPECT_OUTCOME_OK(
        checkPartiallyCovers(box(v_center), box(v_down_left), overlap_percent));
    EXPECT_OUTCOME_OK(
        checkPartiallyCovers(box(v_center), box(v_down_right), overlap_percent));
}


TEST_F(GraphKiwi_Test, KiwiAlign) {
    VertexID v1    = getGraph()->addVertex("v1");
    VertexID v2    = getGraph()->addVertex("v2");
    VertexID v3    = getGraph()->addVertex("v3");
    VertexID v4    = getGraph()->addVertex("v4");
    VertexID rg_id = getGraph()->addVertex("rg");

    hstd::SPtr<kw::KiwiGroup> root = kw::KiwiGroup::newRootGraph(run);
    run->setRootGroupAttribute(rg_id, root);

    root->addVertex(addNesting(rg_id, v1), Size(50, 50));
    root->addVertex(addNesting(rg_id, v2), Size(60, 60));
    root->addVertex(addNesting(rg_id, v3), Size(70, 70));
    root->addVertex(addNesting(rg_id, v4), Size(80, 80));

    root->addConstraint<kw::AlignConstraint>(root)
        ->useVerticalAxis()
        ->addAlignVertex(v1)
        ->addAlignVertex(v2);

    root->addConstraint<kw::AlignConstraint>(root)
        ->useHorizontalAxis()
        ->addAlignVertex(v1)
        ->addAlignVertex(v4);

    run->runFullLayout();
    writeVisual();

    EXPECT_OUTCOME_OK(checkAlignedHorizontally(box(v1), box(v4)));
    EXPECT_OUTCOME_OK(checkAlignedVertically(box(v1), box(v2)));
}

TEST_F(GraphKiwi_Test, KiwiSeparateMultiSeparate) {
    VertexID rg_id = getGraph()->addVertex("rg");
    VertexID g1    = getGraph()->addVertex("g1");
    VertexID g2    = getGraph()->addVertex("g2");
    VertexID g3    = getGraph()->addVertex("g3");
    VertexID g4    = getGraph()->addVertex("g4");
    VertexID g5    = getGraph()->addVertex("g5");
    VertexID g6    = getGraph()->addVertex("g6");
    VertexID g7    = getGraph()->addVertex("g7");
    VertexID g8    = getGraph()->addVertex("g8");

    hstd::SPtr<kw::KiwiGroup> root = kw::KiwiGroup::newRootGraph(run);
    run->setRootGroupAttribute(rg_id, root);

    root->addVertex(addNesting(rg_id, g1), Size(30, 30));
    root->addVertex(addNesting(rg_id, g2), Size(30, 30));
    root->addVertex(addNesting(rg_id, g3), Size(30, 30));
    root->addVertex(addNesting(rg_id, g4), Size(30, 30));
    root->addVertex(addNesting(rg_id, g5), Size(30, 30));
    root->addVertex(addNesting(rg_id, g6), Size(30, 30));
    root->addVertex(addNesting(rg_id, g7), Size(30, 30));
    root->addVertex(addNesting(rg_id, g8), Size(30, 30));

    auto e_g1_g5 = addEdge(g1, g5, "e_g1_g5");
    auto e_g2_g6 = addEdge(g2, g6, "e_g2_g6");
    auto e_g3_g7 = addEdge(g3, g7, "e_g3_g7");
    auto e_g4_g8 = addEdge(g4, g8, "e_g4_g8");
    auto e_g5_g6 = addEdge(g5, g6, "e_g5_g6");
    auto e_g6_g7 = addEdge(g6, g7, "e_g6_g7");
    auto e_g7_g8 = addEdge(g7, g8, "e_g7_g8");

    root->addEdge(e_g1_g5);
    root->addEdge(e_g2_g6);
    root->addEdge(e_g3_g7);
    root->addEdge(e_g4_g8);
    root->addEdge(e_g5_g6);
    root->addEdge(e_g6_g7);
    root->addEdge(e_g7_g8);

    root->addConstraint<kw::SeparateConstraint>(root)
        ->separateVertically()
        ->setSeparationDistance(40)
        ->addLeftVertex(g1)
        ->addLeftVertex(g2)
        ->addLeftVertex(g3)
        ->addLeftVertex(g4)
        ->addRightVertex(g5)
        ->addRightVertex(g6)
        ->addRightVertex(g7)
        ->addRightVertex(g8);

    root->addConstraint<kw::MultiSeparateConstraint>(root)
        ->separateHorizontally()
        ->setSeparationDistance(60)
        ->addFullLane({g1, g5})
        ->addFullLane({g2, g6})
        ->addFullLane({g3, g7})
        ->addFullLane({g4, g8});

    run->runFullLayout();
    writeVisual();
}


class GraphKiwi_BoolParamTest
    : public GraphKiwi_Test
    , public testing::WithParamInterface<bool> {};

TEST_P(GraphKiwi_BoolParamTest, KiwiAlign_Offset) {
    VertexID v1    = getGraph()->addVertex("v1");
    VertexID v2    = getGraph()->addVertex("v2");
    VertexID v3    = getGraph()->addVertex("v3");
    VertexID rg_id = getGraph()->addVertex("rg");

    hstd::SPtr<kw::KiwiGroup> root = kw::KiwiGroup::newRootGraph(run);
    run->setRootGroupAttribute(rg_id, root);

    root->addVertex(addNesting(rg_id, v1), Size(50, 50));
    root->addVertex(addNesting(rg_id, v2), Size(60, 60));
    root->addVertex(addNesting(rg_id, v3), Size(70, 70));

    bool const is_vertical = GetParam();
    auto       c           = root->addConstraint<kw::AlignConstraint>(root);

    if (is_vertical) {
        c->useVerticalAxis();
    } else {
        c->useHorizontalAxis();
    }

    c->addAlignVertex(v1, std::nullopt, 0)
        ->addAlignVertex(v2, std::nullopt, 50)
        ->addAlignVertex(v3, std::nullopt, 100);

    run->runFullLayout();
    writeVisual();

    auto offset = is_vertical ? geometry::Point{50, 0} : geometry::Point{0, 50};

    if (is_vertical) {
        EXPECT_OUTCOME_OK(
            checkAlignedVertically(box(v1).center(), box(v2).center() - offset));
        EXPECT_OUTCOME_OK(
            checkAlignedVertically(box(v2).center(), box(v3).center() - offset));
    } else {
        EXPECT_OUTCOME_OK(
            checkAlignedHorizontally(box(v1).center(), box(v2).center() - offset));
        EXPECT_OUTCOME_OK(
            checkAlignedHorizontally(box(v2).center(), box(v3).center() - offset));
    }
}

TEST_P(GraphKiwi_BoolParamTest, SeparationConstraintAlign) {
    VertexID v1    = getGraph()->addVertex("v1");
    VertexID v2    = getGraph()->addVertex("v2");
    VertexID v3    = getGraph()->addVertex("v3");
    VertexID v4    = getGraph()->addVertex("v4");
    VertexID rg_id = getGraph()->addVertex("rg");

    hstd::SPtr<kw::KiwiGroup> root = kw::KiwiGroup::newRootGraph(run);
    run->setRootGroupAttribute(rg_id, root);

    root->addVertex(addNesting(rg_id, v1), Size(50, 50));
    root->addVertex(addNesting(rg_id, v2), Size(60, 60));
    root->addVertex(addNesting(rg_id, v3), Size(70, 70));
    root->addVertex(addNesting(rg_id, v4), Size(50, 50));

    bool const is_vertical = GetParam();
    auto       c           = root->addConstraint<kw::SeparateConstraint>(root);

    if (is_vertical) {
        c->separateVertically();
    } else {
        c->separateHorizontally();
    }

    c->setSeparationDistance(90)
        ->addLeftVertex(v1)
        ->addLeftVertex(v2)
        ->addRightVertex(v3)
        ->addRightVertex(v4);

    run->runFullLayout();
    writeVisual();

    auto v1_center = box(v1).center();
    auto v2_center = box(v2).center();
    auto v3_center = box(v3).center();
    auto v4_center = box(v4).center();

    if (is_vertical) {
        EXPECT_OUTCOME_OK(checkAlignedHorizontally(v1_center, v2_center));
        EXPECT_OUTCOME_OK(checkAlignedHorizontally(v3_center, v4_center));
        EXPECT_NEAR(v1_center.y() + 90, v4_center.y(), 0.005);
        EXPECT_NEAR(v2_center.y() + 90, v3_center.y(), 0.005);
    } else {
        EXPECT_OUTCOME_OK(checkAlignedVertically(v1_center, v2_center));
        EXPECT_OUTCOME_OK(checkAlignedVertically(v3_center, v4_center));
        EXPECT_NEAR(v1_center.x() + 90, v4_center.x(), 0.005);
        EXPECT_NEAR(v2_center.x() + 90, v3_center.x(), 0.005);
    }
}

INSTANTIATE_TEST_SUITE_P(
    BoolCases,
    GraphKiwi_BoolParamTest,
    testing::Values(false, true));

TEST_F(GraphKiwi_Test, MultiSeparationConstraint) {
    VertexID rg_id = getGraph()->addVertex("rg");

    hstd::Vec<VertexIDVec> grid;
    int                    size = 4;

    for (int row = 0; row < size; ++row) {
        VertexIDVec row_ids;
        for (int col = 0; col < size; ++col) {
            row_ids.push_back(getGraph()->addVertex(hstd::fmt("v_{}_{}", row, col)));
        }
        grid.push_back(row_ids);
    }

    hstd::SPtr<kw::KiwiGroup> root = kw::KiwiGroup::newRootGraph(run);
    run->setRootGroupAttribute(rg_id, root);

    for (auto const& row : grid) {
        for (auto const& col : row) {
            root->addVertex(addNesting(rg_id, col), Size(50, 50));
        }
    }

    auto sep1 = root->addConstraint<kw::MultiSeparateConstraint>(root)
                    ->setSeparationDistance(90)
                    ->separateVertically();

    auto sep2 = root->addConstraint<kw::MultiSeparateConstraint>(root)
                    ->setSeparationDistance(90)
                    ->separateHorizontally();

    hstd::Vec<VertexIDVec> grid_T = hstd::rv::iota(0, size)
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
    writeVisual();

    auto get_c = [&](VertexID const& id) -> geometry::Point {
        return run->getVisual(id).computeBounds().center();
    };

    for (auto const& row : grid) {
        for (auto const& col : row | hstd::rv::sliding(2)) {
            EXPECT_OUTCOME_OK(checkAlignedHorizontally(get_c(col[0]), get_c(col[1])));
        }
    }

    for (auto const& col : grid_T) {
        for (auto const& row : col | hstd::rv::sliding(2)) {
            EXPECT_OUTCOME_OK(checkAlignedVertically(get_c(row[0]), get_c(row[1])));
        }
    }
}
