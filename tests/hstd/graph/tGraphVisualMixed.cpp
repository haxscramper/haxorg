#include "../t_graph_tests_common.hpp"
#include <hstd/stdlib/Ranges.hpp>

struct GraphMixed_Test : public GraphUtils_Test {};

double            size = 20;
Size              rect{size, size};
geometry::Padding pad{12};

TEST_F(GraphMixed_Test, MultiAlgoritmLayered) {
    auto kiwi_root_id  = addVertex("kiwi_root");
    auto kiwi_sub1_id  = addVertex("kiwi_sub1");
    auto dot_sub1_id   = addVertex("dot_sub1");
    auto circo_sub2_id = addVertex("circo_sub2");
    auto dot_sub2_id   = addVertex("dot_sub2");

    // main cola wrapper
    hstd::SPtr<kw::KiwiGroup> kiwi_root = kw::KiwiGroup::newRootGraph(run, "kiwi_root");

    run->setRootGroupAttribute(kiwi_root_id, kiwi_root);

    // sidebar dot layout
    hstd::SPtr<gv::GraphGroup> dot_sub1 = gv::GraphGroup::newRootGraph(run, "dot_sub1");

    auto dot_sub1_id_nesting = addNesting(kiwi_root_id, dot_sub1_id);
    run->setNestedGroupAttribute(dot_sub1_id_nesting, dot_sub1);

    auto l1 = addVertex("l1");
    auto l2 = addVertex("l2");
    auto l3 = addVertex("l3");
    auto l4 = addVertex("l4");
    auto l5 = addVertex("l5");
    auto l6 = addVertex("l6");
    auto l7 = addVertex("l7");

    dot_sub1->addVertex(addNesting(dot_sub1_id, l1))->setFixedPointWH(rect);
    dot_sub1->addVertex(addNesting(dot_sub1_id, l2))->setFixedPointWH(rect);
    dot_sub1->addVertex(addNesting(dot_sub1_id, l3))->setFixedPointWH(rect);
    dot_sub1->addVertex(addNesting(dot_sub1_id, l4))->setFixedPointWH(rect);
    dot_sub1->addVertex(addNesting(dot_sub1_id, l5))->setFixedPointWH(rect);
    dot_sub1->addVertex(addNesting(dot_sub1_id, l6))->setFixedPointWH(rect);
    dot_sub1->addVertex(addNesting(dot_sub1_id, l7))->setFixedPointWH(rect);

    auto e_l1_l2 = addEdge(l1, l2, "e_l1_l2");
    auto e_l2_l3 = addEdge(l2, l3, "e_l2_l3");
    auto e_l3_l4 = addEdge(l3, l4, "e_l3_l4");
    auto e_l4_l5 = addEdge(l4, l5, "e_l4_l5");
    auto e_l5_l6 = addEdge(l5, l6, "e_l5_l6");
    auto e_l6_l7 = addEdge(l6, l7, "e_l6_l7");

    dot_sub1->addEdge(e_l1_l2);
    dot_sub1->addEdge(e_l2_l3);
    dot_sub1->addEdge(e_l3_l4);
    dot_sub1->addEdge(e_l4_l5);
    dot_sub1->addEdge(e_l5_l6);
    dot_sub1->addEdge(e_l6_l7);

    dot_sub1->setOuterPadding(pad);

    // intermediate cola layout
    hstd::SPtr<kw::KiwiGroup> kiwi_sub1 = kw::KiwiGroup::newRootGraph(run, "kiwi_sub1");

    auto kiwi_sub1_id_nesting = addNesting(kiwi_root_id, kiwi_sub1_id);
    run->setNestedGroupAttribute(kiwi_sub1_id_nesting, kiwi_sub1);

    auto g1 = addVertex("g1");
    auto g2 = addVertex("g2");
    auto g3 = addVertex("g3");
    auto g4 = addVertex("g4");
    auto g5 = addVertex("g5");
    auto g6 = addVertex("g6");
    auto g7 = addVertex("g7");
    auto g8 = addVertex("g8");

    kiwi_sub1->addVertex(addNesting(kiwi_sub1_id, g1), rect);
    kiwi_sub1->addVertex(addNesting(kiwi_sub1_id, g2), rect);
    kiwi_sub1->addVertex(addNesting(kiwi_sub1_id, g3), rect);
    kiwi_sub1->addVertex(addNesting(kiwi_sub1_id, g4), rect);
    kiwi_sub1->addVertex(addNesting(kiwi_sub1_id, g5), rect);
    kiwi_sub1->addVertex(addNesting(kiwi_sub1_id, g6), rect);
    kiwi_sub1->addVertex(addNesting(kiwi_sub1_id, g7), rect);
    kiwi_sub1->addVertex(addNesting(kiwi_sub1_id, g8), rect);

    auto e_g1_g5 = addEdge(g1, g5, "e_g1_g5");
    auto e_g2_g6 = addEdge(g2, g6, "e_g2_g6");
    auto e_g3_g7 = addEdge(g3, g7, "e_g3_g7");
    auto e_g4_g8 = addEdge(g4, g8, "e_g4_g8");
    auto e_g5_g6 = addEdge(g5, g6, "e_g5_g6");
    auto e_g6_g7 = addEdge(g6, g7, "e_g6_g7");
    auto e_g7_g8 = addEdge(g7, g8, "e_g7_g8");

    kiwi_sub1->addEdge(e_g1_g5);
    kiwi_sub1->addEdge(e_g2_g6);
    kiwi_sub1->addEdge(e_g3_g7);
    kiwi_sub1->addEdge(e_g4_g8);
    kiwi_sub1->addEdge(e_g5_g6);
    kiwi_sub1->addEdge(e_g6_g7);
    kiwi_sub1->addEdge(e_g7_g8);

    kiwi_sub1->addConstraint<kw::SeparateConstraint>(kiwi_sub1)
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

    kiwi_sub1->addConstraint<kw::MultiSeparateConstraint>(kiwi_sub1)
        ->separateHorizontally()
        ->setSeparationDistance(60)
        ->addFullLane({g1, g5})
        ->addFullLane({g2, g6})
        ->addFullLane({g3, g7})
        ->addFullLane({g4, g8});


    // circo layout sub-group
    hstd::SPtr<gv::GraphGroup> circo_sub2 = gv::GraphGroup::newRootGraph(
        run, "circo_sub2");

    circo_sub2->getAlgorithm<gv::Layout>()->layout = gv::LayoutType::Circo;
    circo_sub2->setOuterPadding(geometry::Padding{5});

    auto circo_sub2_id_nesting = addNesting(kiwi_sub1_id, circo_sub2_id);
    run->setNestedGroupAttribute(circo_sub2_id_nesting, circo_sub2);

    auto c1 = addVertex("c1");
    auto c2 = addVertex("c2");
    auto c3 = addVertex("c3");
    auto c4 = addVertex("c4");
    auto c5 = addVertex("c5");
    auto c6 = addVertex("c6");
    auto c7 = addVertex("c7");
    auto c8 = addVertex("c8");

    circo_sub2->addVertex(addNesting(circo_sub2_id, c1))->setFixedPointWH(rect);
    circo_sub2->addVertex(addNesting(circo_sub2_id, c2))->setFixedPointWH(rect);
    circo_sub2->addVertex(addNesting(circo_sub2_id, c3))->setFixedPointWH(rect);
    circo_sub2->addVertex(addNesting(circo_sub2_id, c4))->setFixedPointWH(rect);
    circo_sub2->addVertex(addNesting(circo_sub2_id, c5))->setFixedPointWH(rect);
    circo_sub2->addVertex(addNesting(circo_sub2_id, c6))->setFixedPointWH(rect);
    circo_sub2->addVertex(addNesting(circo_sub2_id, c7))->setFixedPointWH(rect);
    circo_sub2->addVertex(addNesting(circo_sub2_id, c8))->setFixedPointWH(rect);

    auto e_c1_c2 = addEdge(c1, c2, "e_c1_c2");
    auto e_c2_c3 = addEdge(c2, c3, "e_c2_c3");
    auto e_c3_c4 = addEdge(c3, c4, "e_c3_c4");
    auto e_c4_c5 = addEdge(c4, c5, "e_c4_c5");
    auto e_c5_c6 = addEdge(c5, c6, "e_c5_c6");
    auto e_c6_c7 = addEdge(c6, c7, "e_c6_c7");
    auto e_c7_c8 = addEdge(c7, c8, "e_c7_c8");
    auto e_c8_c1 = addEdge(c8, c1, "e_c8_c1");

    circo_sub2->addEdge(e_c1_c2);
    circo_sub2->addEdge(e_c2_c3);
    circo_sub2->addEdge(e_c3_c4);
    circo_sub2->addEdge(e_c4_c5);
    circo_sub2->addEdge(e_c5_c6);
    circo_sub2->addEdge(e_c6_c7);
    circo_sub2->addEdge(e_c7_c8);
    circo_sub2->addEdge(e_c8_c1);

    // innermost dot group layout sub-group
    hstd::SPtr<gv::GraphGroup> dot_sub2 = gv::GraphGroup::newRootGraph(run, "dot_sub2");

    dot_sub2->setOuterPadding(geometry::Padding{5});

    auto dot_sub2_id_nesting = addNesting(kiwi_sub1_id, dot_sub2_id);
    run->setNestedGroupAttribute(dot_sub2_id_nesting, dot_sub2);

    auto d1 = addVertex("d1");
    auto d2 = addVertex("d2");
    auto d3 = addVertex("d3");
    auto d4 = addVertex("d4");

    dot_sub2->addVertex(addNesting(dot_sub2_id, d1))->setFixedPointWH(rect);
    dot_sub2->addVertex(addNesting(dot_sub2_id, d2))->setFixedPointWH(rect);
    dot_sub2->addVertex(addNesting(dot_sub2_id, d3))->setFixedPointWH(rect);
    dot_sub2->addVertex(addNesting(dot_sub2_id, d4))->setFixedPointWH(rect);

    auto e_d1_d2 = addEdge(d1, d2, "e_d1_d2");
    auto e_d1_d3 = addEdge(d1, d3, "e_d1_d3");
    auto e_d2_d4 = addEdge(d2, d4, "e_d2_d4");
    auto e_d3_d4 = addEdge(d3, d4, "e_d3_d4");

    dot_sub2->addEdge(e_d1_d2);
    dot_sub2->addEdge(e_d1_d3);
    dot_sub2->addEdge(e_d2_d4);
    dot_sub2->addEdge(e_d3_d4);

    auto ex1  = addEdge(circo_sub2_id, dot_sub2_id, "ex1");
    auto ex2  = addEdge(c3, d1, "ex2");
    auto ex3  = addEdge(c7, g1, "ex3");
    auto ex4  = addEdge(c6, g2, "ex4");
    auto ex5  = addEdge(c2, g3, "ex5");
    auto ex6  = addEdge(dot_sub2_id, kiwi_sub1_id, "ex6");
    auto ex7  = addEdge(dot_sub2_id, dot_sub1_id, "ex7");
    auto ex8  = addEdge(d3, l2, "ex8");
    auto ex9  = addEdge(g8, l6, "ex9");
    auto ex10 = addEdge(g7, l7, "ex10");
    auto ex11 = addEdge(g6, l5, "ex11");

    run->addUnboundEdge(ex1);
    run->addUnboundEdge(ex2);
    run->addUnboundEdge(ex3);
    run->addUnboundEdge(ex4);
    run->addUnboundEdge(ex5);
    run->addUnboundEdge(ex6);
    run->addUnboundEdge(ex7);
    run->addUnboundEdge(ex8);
    run->addUnboundEdge(ex9);
    run->addUnboundEdge(ex10);
    run->addUnboundEdge(ex11);

    // Adding the vertex to the kiwi group explicitly, see
    // [[kw/layout/reuse-existing-vertices]]. Otherwise linear constraint
    // would not have access to the rectangle for the expression
    // construction.
    kiwi_sub1->addVertex(dot_sub2_id_nesting);
    kiwi_sub1->addVertex(circo_sub2_id_nesting);
    kiwi_sub1->addConstraint<kw::LinearConstraint>(kiwi_root)->setSecondLeftOfFirst(
        dot_sub2_id, circo_sub2_id);

    kiwi_sub1->addConstraint<kw::LinearConstraint>(kiwi_root)->setSecondBelowFirst(
        circo_sub2_id, g1);

    {
        auto under_nodes = kiwi_sub1->addConstraint<kw::LinearConstraint>(kiwi_root);
        under_nodes->finalize(
            under_nodes->use(g1, kiwi_ir::RectAttr::LEFT),
            kiwi_ir::Relation::EQ,
            under_nodes->use(circo_sub2_id, kiwi_ir::RectAttr::LEFT));
    }

    kiwi_root->addVertex(kiwi_sub1_id_nesting);
    kiwi_root->addVertex(dot_sub1_id_nesting);
    kiwi_root->addConstraint<kw::LinearConstraint>(kiwi_root)->setSecondRightOfFirst(
        kiwi_sub1_id, dot_sub1_id);

    run->runFullLayout();

    hstd::writeFile(getDebugFile("repr.txt"), run->treeRepr().toString(false));

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());

    // the final graph looks like an absolute shit with the edge routing,
    // but the rectangles are properly fixed in place.
    EXPECT_OUTCOME_OK(checkBelow(box(circo_sub2_id), box(g2)));
    EXPECT_OUTCOME_OK(checkBelow(box(circo_sub2_id), box(g6)));
    EXPECT_OUTCOME_OK(checkBelow(box(g1), box(g5)));
    EXPECT_OUTCOME_OK(checkBelow(box(g1), box(g6)));
    EXPECT_OUTCOME_OK(checkRightOf(box(g1), box(g2)));
    EXPECT_OUTCOME_OK(checkRightOf(box(g1), box(g3)));
    EXPECT_OUTCOME_OK(checkRightOf(box(g1), box(g4)));
    EXPECT_OUTCOME_OK(checkRightOf(box(g1), box(g8)));

    EXPECT_OUTCOME_OK(checkBelow(box(l1), box(l2)));
    EXPECT_OUTCOME_OK(checkBelow(box(l1), box(l7)));
    EXPECT_OUTCOME_OK(checkBelow(box(d1), box(d2)));

    EXPECT_OUTCOME_OK(checkRightOf(box(circo_sub2_id), box(dot_sub2_id)));
    EXPECT_OUTCOME_OK(checkFullyCovers(box(kiwi_sub1_id), box(circo_sub2_id)));
    EXPECT_OUTCOME_OK(checkPartiallyCovers(box(circo_sub2_id), box(dot_sub2_id), 0.0));
    EXPECT_OUTCOME_OK(checkPartiallyCovers(box(dot_sub2_id), box(dot_sub1_id), 0.0));
}

TEST_F(GraphMixed_Test, TrivialNestingLayoutSwitch) {
    auto r1_id   = addVertex("r1_id");
    auto r2_id   = addVertex("r2_id");
    auto r3_id   = addVertex("r3_id");
    auto r4_id   = addVertex("r4_id");
    auto r5_id   = addVertex("r5_id");
    auto node_id = addVertex("node");

    hstd::SPtr<kw::KiwiGroup> r1 = kw::KiwiGroup::newRootGraph(run, "r1");
    r1->setOuterPadding(pad);

    hstd::SPtr<kw::KiwiGroup> r2 = kw::KiwiGroup::newRootGraph(run, "r2");
    r2->setOuterPadding(pad);

    hstd::SPtr<kw::KiwiGroup> r3 = kw::KiwiGroup::newRootGraph(run, "r3");
    r3->setOuterPadding(pad);

    hstd::SPtr<kw::KiwiGroup> r4 = kw::KiwiGroup::newRootGraph(run, "r4");
    r4->setOuterPadding(pad);

    hstd::SPtr<kw::KiwiGroup> r5 = kw::KiwiGroup::newRootGraph(run, "r5");
    r5->setOuterPadding(pad);

    run->setRootGroupAttribute(r1_id, r1);
    run->setNestedGroupAttribute(addNesting(r1_id, r2_id), r2);
    run->setNestedGroupAttribute(addNesting(r2_id, r3_id), r3);
    run->setNestedGroupAttribute(addNesting(r3_id, r4_id), r4);
    run->setNestedGroupAttribute(addNesting(r4_id, r5_id), r5);

    r5->addVertex(addNesting(r5_id, node_id), rect);

    run->runFullLayout();

    hstd::writeFile(getDebugFile("repr.txt"), run->treeRepr().toString(false));

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
}
