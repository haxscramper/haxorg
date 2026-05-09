#include "../t_graph_tests_common.hpp"
#include <hstd/stdlib/Ranges.hpp>

struct GraphMixed_Test : public GraphUtils_Test {};

TEST_F(GraphMixed_Test, MultiAlgoritmLayered) {
    double size = 20;
    Size   rect{size, size};

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

    auto e_l1_l2 = graph->addEdge(l1, l2);
    auto e_l2_l3 = graph->addEdge(l2, l3);
    auto e_l3_l4 = graph->addEdge(l3, l4);
    auto e_l4_l5 = graph->addEdge(l4, l5);
    auto e_l5_l6 = graph->addEdge(l5, l6);
    auto e_l6_l7 = graph->addEdge(l6, l7);

    dot_sub1->setOuterPadding(geometry::Padding{5});

    // intermediate cola layout
    hstd::SPtr<cst::ColaGroup> cola_sub1 = cst::ColaGroup::newRootGraph(
        run, "cola_sub1");

    std::ignore = run->addNestedGroup(
        cola_root_id, cola_sub1_id, cola_sub1);

    // circo layout sub-group
    hstd::SPtr<gv::GraphGroup> circo_sub2 = gv::GraphGroup::newRootGraph(
        run, "circo_sub2");

    circo_sub2->getAlgorithm<gv::Layout>()->layout = gv::LayoutType::Circo;
    circo_sub2->setOuterPadding(geometry::Padding{5});

    std::ignore = run->addNestedGroup(
        cola_root_id, circo_sub2_id, circo_sub2);

    auto c1 = addVertex("c1");
    auto c2 = addVertex("c2");
    auto c3 = addVertex("c3");
    auto c4 = addVertex("c4");
    auto c5 = addVertex("c5");
    auto c6 = addVertex("c6");
    auto c7 = addVertex("c7");
    auto c8 = addVertex("c8");

    auto e_c1_c2 = graph->addEdge(c1, c2);
    auto e_c2_c3 = graph->addEdge(c2, c3);
    auto e_c3_c4 = graph->addEdge(c3, c4);
    auto e_c4_c5 = graph->addEdge(c4, c5);
    auto e_c5_c6 = graph->addEdge(c5, c6);
    auto e_c6_c7 = graph->addEdge(c6, c7);
    auto e_c7_c8 = graph->addEdge(c7, c8);
    auto e_c8_c1 = graph->addEdge(c8, c1);

    circo_sub2->addVertex(circo_sub2_id, c1)->setFixedPointWH(rect);
    circo_sub2->addVertex(circo_sub2_id, c2)->setFixedPointWH(rect);
    circo_sub2->addVertex(circo_sub2_id, c3)->setFixedPointWH(rect);
    circo_sub2->addVertex(circo_sub2_id, c4)->setFixedPointWH(rect);
    circo_sub2->addVertex(circo_sub2_id, c5)->setFixedPointWH(rect);
    circo_sub2->addVertex(circo_sub2_id, c6)->setFixedPointWH(rect);
    circo_sub2->addVertex(circo_sub2_id, c7)->setFixedPointWH(rect);
    circo_sub2->addVertex(circo_sub2_id, c8)->setFixedPointWH(rect);

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

    std::ignore = run->addNestedGroup(cola_root_id, dot_sub2_id, dot_sub2);

    auto d1 = addVertex("d1");
    auto d2 = addVertex("d2");
    auto d3 = addVertex("d3");
    auto d4 = addVertex("d4");

    auto e_d1_d2 = graph->addEdge(d1, d2);
    auto e_d1_d3 = graph->addEdge(d1, d3);

    auto e_d2_d4 = graph->addEdge(d2, d4);
    auto e_d3_d4 = graph->addEdge(d3, d4);

    dot_sub2->addVertex(dot_sub2_id, d1)->setFixedPointWH(rect);
    dot_sub2->addVertex(dot_sub2_id, d2)->setFixedPointWH(rect);
    dot_sub2->addVertex(dot_sub2_id, d3)->setFixedPointWH(rect);
    dot_sub2->addVertex(dot_sub2_id, d4)->setFixedPointWH(rect);

    dot_sub2->addEdge(e_d1_d2);
    dot_sub2->addEdge(e_d1_d3);
    dot_sub2->addEdge(e_d2_d4);
    dot_sub2->addEdge(e_d3_d4);

    run->runFullLayout();

    auto const& res = run->result;

    auto visual = run->getVisual();
    hstd::writeFile(
        getDebugFile("result.svg"),
        hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
}
