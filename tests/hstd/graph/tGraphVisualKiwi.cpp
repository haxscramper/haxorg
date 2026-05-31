#include "../t_graph_tests_common.hpp"
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/ext/graph/visual/graph_kiwi.hpp>

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

    EXPECT_NEAR(run->getLayout(v1)->getBBox().width(), 5, 0.005);
    EXPECT_NEAR(run->getLayout(v1)->getBBox().height(), 5, 0.005);
    EXPECT_NEAR(run->getLayout(v2)->getBBox().width(), 6, 0.005);
    EXPECT_NEAR(run->getLayout(v2)->getBBox().height(), 6, 0.005);
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

    EXPECT_OUTCOME_OK(
        checkAlignedHorizontally(run->getVisual(v1), run->getVisual(v4)));
    EXPECT_OUTCOME_OK(
        checkAlignedVertically(run->getVisual(v1), run->getVisual(v2)));
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
    auto       c = root->addConstraint<kw::AlignConstraint>(root);

    if (is_vertical) {
        c->useVerticalAxis();
    } else {
        c->useHorizontalAxis();
    }

    c->addAlignVertex(v1, kw::AlignConstraint::AxisAlign::Center, 0)
        ->addAlignVertex(v2, kw::AlignConstraint::AxisAlign::Center, 50)
        ->addAlignVertex(v3, kw::AlignConstraint::AxisAlign::Center, 100);

    run->runFullLayout();

    auto offset = is_vertical ? geometry::Point{50, 0}
                              : geometry::Point{0, 50};

    if (is_vertical) {
        EXPECT_OUTCOME_OK(checkAlignedVertically(
            run->getVisual(v1).computeBounds().center(),
            run->getVisual(v2).computeBounds().center() - offset));
        EXPECT_OUTCOME_OK(checkAlignedVertically(
            run->getVisual(v2).computeBounds().center(),
            run->getVisual(v3).computeBounds().center() - offset));
    } else {
        EXPECT_OUTCOME_OK(checkAlignedHorizontally(
            run->getVisual(v1).computeBounds().center(),
            run->getVisual(v2).computeBounds().center() - offset));
        EXPECT_OUTCOME_OK(checkAlignedHorizontally(
            run->getVisual(v2).computeBounds().center(),
            run->getVisual(v3).computeBounds().center() - offset));
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
    auto       c = root->addConstraint<kw::SeparateConstraint>(root);

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

    auto v1_center = run->getVisual(v1).computeBounds().center();
    auto v2_center = run->getVisual(v2).computeBounds().center();
    auto v3_center = run->getVisual(v3).computeBounds().center();
    auto v4_center = run->getVisual(v4).computeBounds().center();

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
            row_ids.push_back(
                getGraph()->addVertex(hstd::fmt("v_{}_{}", row, col)));
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
                    ->separateVertically()
                    ->setIsExactSeparation(true);

    auto sep2 = root->addConstraint<kw::MultiSeparateConstraint>(root)
                    ->setSeparationDistance(90)
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

    auto get_c = [&](VertexID const& id) -> geometry::Point {
        return run->getVisual(id).computeBounds().center();
    };

    for (auto const& row : grid) {
        for (auto const& col : row | hstd::rv::sliding(2)) {
            EXPECT_OUTCOME_OK(
                checkAlignedHorizontally(get_c(col[0]), get_c(col[1])));
        }
    }

    for (auto const& col : grid_T) {
        for (auto const& row : col | hstd::rv::sliding(2)) {
            EXPECT_OUTCOME_OK(
                checkAlignedVertically(get_c(row[0]), get_c(row[1])));
        }
    }
}
