#include "../t_graph_tests_common.hpp"
#include <hstd/stdlib/Ranges.hpp>

struct GraphMixed_Test : public GraphUtils_Test {};

double            size = 20;
Size              rect{size, size};
geometry::Padding pad{12};

TEST_F(GraphMixed_Test, MultiAlgoritmLayered) {
    auto cola_root_id  = addVertex("cola_root");
    auto cola_sub1_id  = addVertex("cola_sub1");
    auto dot_sub1_id   = addVertex("dot_sub1");
    auto circo_sub2_id = addVertex("circo_sub2");
    auto dot_sub2_id   = addVertex("dot_sub2");

    // main cola wrapper
    hstd::SPtr<cst::ColaGroup> cola_root = cst::ColaGroup::newRootGraph(
        run, "cola_root");

    run->addRootGroup(cola_root_id, cola_root);

    // sidebar dot layout
    hstd::SPtr<gv::GraphGroup> dot_sub1 = gv::GraphGroup::newRootGraph(
        run, "dot_sub1");

    std::ignore = run->addNestedGroup(cola_root_id, dot_sub1_id, dot_sub1);

    auto l1 = addVertex("l1");
    auto l2 = addVertex("l2");
    auto l3 = addVertex("l3");
    auto l4 = addVertex("l4");
    auto l5 = addVertex("l5");
    auto l6 = addVertex("l6");
    auto l7 = addVertex("l7");

    dot_sub1->addVertex(dot_sub1_id, l1)->setFixedPointWH(rect);
    dot_sub1->addVertex(dot_sub1_id, l2)->setFixedPointWH(rect);
    dot_sub1->addVertex(dot_sub1_id, l3)->setFixedPointWH(rect);
    dot_sub1->addVertex(dot_sub1_id, l4)->setFixedPointWH(rect);
    dot_sub1->addVertex(dot_sub1_id, l5)->setFixedPointWH(rect);
    dot_sub1->addVertex(dot_sub1_id, l6)->setFixedPointWH(rect);
    dot_sub1->addVertex(dot_sub1_id, l7)->setFixedPointWH(rect);

    auto e_l1_l2 = graph->addEdge(l1, l2);
    auto e_l2_l3 = graph->addEdge(l2, l3);
    auto e_l3_l4 = graph->addEdge(l3, l4);
    auto e_l4_l5 = graph->addEdge(l4, l5);
    auto e_l5_l6 = graph->addEdge(l5, l6);
    auto e_l6_l7 = graph->addEdge(l6, l7);

    dot_sub1->addEdge(e_l1_l2);
    dot_sub1->addEdge(e_l2_l3);
    dot_sub1->addEdge(e_l3_l4);
    dot_sub1->addEdge(e_l4_l5);
    dot_sub1->addEdge(e_l5_l6);
    dot_sub1->addEdge(e_l6_l7);

    dot_sub1->setOuterPadding(pad);

    // intermediate cola layout
    hstd::SPtr<cst::ColaGroup> cola_sub1 = cst::ColaGroup::newRootGraph(
        run, "cola_sub1");

    std::ignore = run->addNestedGroup(
        cola_root_id, cola_sub1_id, cola_sub1);

    auto g1 = addVertex("g1");
    auto g2 = addVertex("g2");
    auto g3 = addVertex("g3");
    auto g4 = addVertex("g4");
    auto g5 = addVertex("g5");
    auto g6 = addVertex("g6");
    auto g7 = addVertex("g7");
    auto g8 = addVertex("g8");

    cola_sub1->addVertex(cola_sub1_id, g1, rect);
    cola_sub1->addVertex(cola_sub1_id, g2, rect);
    cola_sub1->addVertex(cola_sub1_id, g3, rect);
    cola_sub1->addVertex(cola_sub1_id, g4, rect);
    cola_sub1->addVertex(cola_sub1_id, g5, rect);
    cola_sub1->addVertex(cola_sub1_id, g6, rect);
    cola_sub1->addVertex(cola_sub1_id, g7, rect);
    cola_sub1->addVertex(cola_sub1_id, g8, rect);

    auto e_g1_g5 = graph->addEdge(g1, g5);
    auto e_g2_g6 = graph->addEdge(g2, g6);
    auto e_g3_g7 = graph->addEdge(g3, g7);
    auto e_g4_g8 = graph->addEdge(g4, g8);
    auto e_g5_g6 = graph->addEdge(g5, g6);
    auto e_g6_g7 = graph->addEdge(g6, g7);
    auto e_g7_g8 = graph->addEdge(g7, g8);

    cola_sub1->addEdge(e_g1_g5);
    cola_sub1->addEdge(e_g2_g6);
    cola_sub1->addEdge(e_g3_g7);
    cola_sub1->addEdge(e_g4_g8);
    cola_sub1->addEdge(e_g5_g6);
    cola_sub1->addEdge(e_g6_g7);
    cola_sub1->addEdge(e_g7_g8);

    // cola_sub1->addConstraint<cst::SeparateConstraint>(cola_sub1)
    //     ->separateVertically()
    //     ->setSeparationDistance(40)
    //     ->addLeftVertex(g1)
    //     ->addLeftVertex(g2)
    //     ->addLeftVertex(g3)
    //     ->addLeftVertex(g4)
    //     ->addRightVertex(g5)
    //     ->addRightVertex(g6)
    //     ->addRightVertex(g7)
    //     ->addRightVertex(g8);

    // circo layout sub-group
    hstd::SPtr<gv::GraphGroup> circo_sub2 = gv::GraphGroup::newRootGraph(
        run, "circo_sub2");

    circo_sub2->getAlgorithm<gv::Layout>()->layout = gv::LayoutType::Circo;
    circo_sub2->setOuterPadding(geometry::Padding{5});

    std::ignore = run->addNestedGroup(
        cola_sub1_id, circo_sub2_id, circo_sub2);

    auto c1 = addVertex("c1");
    auto c2 = addVertex("c2");
    auto c3 = addVertex("c3");
    auto c4 = addVertex("c4");
    auto c5 = addVertex("c5");
    auto c6 = addVertex("c6");
    auto c7 = addVertex("c7");
    auto c8 = addVertex("c8");

    circo_sub2->addVertex(circo_sub2_id, c1)->setFixedPointWH(rect);
    circo_sub2->addVertex(circo_sub2_id, c2)->setFixedPointWH(rect);
    circo_sub2->addVertex(circo_sub2_id, c3)->setFixedPointWH(rect);
    circo_sub2->addVertex(circo_sub2_id, c4)->setFixedPointWH(rect);
    circo_sub2->addVertex(circo_sub2_id, c5)->setFixedPointWH(rect);
    circo_sub2->addVertex(circo_sub2_id, c6)->setFixedPointWH(rect);
    circo_sub2->addVertex(circo_sub2_id, c7)->setFixedPointWH(rect);
    circo_sub2->addVertex(circo_sub2_id, c8)->setFixedPointWH(rect);

    auto e_c1_c2 = graph->addEdge(c1, c2);
    auto e_c2_c3 = graph->addEdge(c2, c3);
    auto e_c3_c4 = graph->addEdge(c3, c4);
    auto e_c4_c5 = graph->addEdge(c4, c5);
    auto e_c5_c6 = graph->addEdge(c5, c6);
    auto e_c6_c7 = graph->addEdge(c6, c7);
    auto e_c7_c8 = graph->addEdge(c7, c8);
    auto e_c8_c1 = graph->addEdge(c8, c1);

    circo_sub2->addEdge(e_c1_c2);
    circo_sub2->addEdge(e_c2_c3);
    circo_sub2->addEdge(e_c3_c4);
    circo_sub2->addEdge(e_c4_c5);
    circo_sub2->addEdge(e_c5_c6);
    circo_sub2->addEdge(e_c6_c7);
    circo_sub2->addEdge(e_c7_c8);
    circo_sub2->addEdge(e_c8_c1);

    // innermost dot group layout sub-group
    hstd::SPtr<gv::GraphGroup> dot_sub2 = gv::GraphGroup::newRootGraph(
        run, "dot_sub2");

    dot_sub2->setOuterPadding(geometry::Padding{5});

    std::ignore = run->addNestedGroup(cola_sub1_id, dot_sub2_id, dot_sub2);

    auto d1 = addVertex("d1");
    auto d2 = addVertex("d2");
    auto d3 = addVertex("d3");
    auto d4 = addVertex("d4");

    dot_sub2->addVertex(dot_sub2_id, d1)->setFixedPointWH(rect);
    dot_sub2->addVertex(dot_sub2_id, d2)->setFixedPointWH(rect);
    dot_sub2->addVertex(dot_sub2_id, d3)->setFixedPointWH(rect);
    dot_sub2->addVertex(dot_sub2_id, d4)->setFixedPointWH(rect);

    auto e_d1_d2 = graph->addEdge(d1, d2);
    auto e_d1_d3 = graph->addEdge(d1, d3);
    auto e_d2_d4 = graph->addEdge(d2, d4);
    auto e_d3_d4 = graph->addEdge(d3, d4);

    dot_sub2->addEdge(e_d1_d2);
    dot_sub2->addEdge(e_d1_d3);
    dot_sub2->addEdge(e_d2_d4);
    dot_sub2->addEdge(e_d3_d4);

    run->runFullLayout();

    auto ex1  = graph->addEdge(circo_sub2_id, dot_sub2_id);
    auto ex2  = graph->addEdge(c3, d1);
    auto ex3  = graph->addEdge(c7, g1);
    auto ex4  = graph->addEdge(c6, g2);
    auto ex5  = graph->addEdge(c2, g3);
    auto ex6  = graph->addEdge(dot_sub2_id, cola_sub1_id);
    auto ex7  = graph->addEdge(dot_sub2_id, dot_sub1_id);
    auto ex8  = graph->addEdge(d3, l2);
    auto ex9  = graph->addEdge(g8, l6);
    auto ex10 = graph->addEdge(g7, l7);
    auto ex11 = graph->addEdge(g6, l5);

    hstd::writeFile(
        getDebugFile("repr.txt"), run->treeRepr().toString(false));

    auto const& res = run->result;

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
}

TEST_F(GraphMixed_Test, TrivialNestingLayoutSwitch) {
    auto r1_id   = addVertex("r1_id");
    auto r2_id   = addVertex("r2_id");
    auto r3_id   = addVertex("r3_id");
    auto r4_id   = addVertex("r4_id");
    auto r5_id   = addVertex("r5_id");
    auto node_id = addVertex("node");

    hstd::SPtr<cst::ColaGroup> r1 = cst::ColaGroup::newRootGraph(
        run, "r1");
    r1->setOuterPadding(pad);

    hstd::SPtr<cst::ColaGroup> r2 = cst::ColaGroup::newRootGraph(
        run, "r2");
    r2->setOuterPadding(pad);

    hstd::SPtr<cst::ColaGroup> r3 = cst::ColaGroup::newRootGraph(
        run, "r3");
    r3->setOuterPadding(pad);

    hstd::SPtr<cst::ColaGroup> r4 = cst::ColaGroup::newRootGraph(
        run, "r4");
    r4->setOuterPadding(pad);

    hstd::SPtr<cst::ColaGroup> r5 = cst::ColaGroup::newRootGraph(
        run, "r5");
    r5->setOuterPadding(pad);

    run->addRootGroup(r1_id, r1);
    std::ignore = run->addNestedGroup(r1_id, r2_id, r2);
    std::ignore = run->addNestedGroup(r2_id, r3_id, r3);
    std::ignore = run->addNestedGroup(r3_id, r4_id, r4);
    std::ignore = run->addNestedGroup(r4_id, r5_id, r5);

    r5->addVertex(r5_id, node_id, rect);

    run->runFullLayout();

    hstd::writeFile(
        getDebugFile("repr.txt"), run->treeRepr().toString(false));

    auto const& res = run->result;

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
}
