#include <gtest/gtest.h>
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>
#include <libcola/output_svg.h>

TEST(GraphUtils, LibcolaApi) {
    std::vector<std::pair<unsigned, unsigned>> edges{
        {0, 1},
        {1, 2},
        {2, 3},
    };

    double                        width  = 100;
    double                        height = 100;
    std::vector<vpsc::Rectangle*> rectangles;

    for (unsigned i = 0; i < edges.size() + 1; i++) {
        double x = i * 10;
        double y = i * 10;
        rectangles.push_back(new vpsc::Rectangle(x, x + 5, y, y + 5));
    }

    cola::CompoundConstraints ccs;

    cola::AlignmentConstraint align_on_x{vpsc::XDIM};
    ccs.push_back(&align_on_x);
    align_on_x.addShape(0, 0);
    align_on_x.addShape(1, 0);

    cola::AlignmentConstraint align_on_y{vpsc::YDIM};
    ccs.push_back(&align_on_y);
    align_on_y.addShape(1, 0);
    align_on_y.addShape(3, 0);

    cola::ConstrainedFDLayout alg2(rectangles, edges, width / 2);
    alg2.setConstraints(ccs);
    alg2.run();

    OutputFile output(
        rectangles, edges, nullptr, "/tmp/testLibcolaApi1.svg");
    output.rects = true;
    output.generate();

    for (auto r : rectangles) { delete r; }
}

TEST(GraphUtils, LibcolaRaw1) {
    using namespace Avoid;
    Router  router_it{PolyLineRouting | OrthogonalRouting};
    Router* router = &router_it;
    router->setRoutingPenalty((PenaltyType)0, 50);
    router->setRoutingPenalty((PenaltyType)1, 0);
    router->setRoutingPenalty((PenaltyType)2, 400);
    router->setRoutingPenalty((PenaltyType)3, 4000);
    router->setRoutingPenalty((PenaltyType)4, 110);
    router->setRoutingParameter(idealNudgingDistance, 25);

    Polygon poly143407352(4);
    poly143407352.ps[0] = Point(5810, 4340);
    poly143407352.ps[1] = Point(5810, 5035);
    poly143407352.ps[2] = Point(5450, 5035);
    poly143407352.ps[3] = Point(5450, 4340);
    new ShapeRef(router, poly143407352, 143407352);

    Polygon poly124950386(4);
    poly124950386.ps[0] = Point(4900, 4090);
    poly124950386.ps[1] = Point(4900, 4785);
    poly124950386.ps[2] = Point(4540, 4785);
    poly124950386.ps[3] = Point(4540, 4090);
    new ShapeRef(router, poly124950386, 124950386);

    ConnRef* connRef373967044 = new ConnRef(router, 373967044);
    ConnEnd  srcPt373967044(Point(4890, 4250), 8);
    connRef373967044->setSourceEndpoint(srcPt373967044);
    ConnEnd dstPt373967044(Point(5460, 4500), 4);
    connRef373967044->setDestEndpoint(dstPt373967044);
    connRef373967044->setRoutingType((ConnType)2);

    ConnRef* connRef681881486 = new ConnRef(router, 681881486);
    ConnEnd  srcPt681881486(Point(4890, 4325), 8);
    connRef681881486->setSourceEndpoint(srcPt681881486);
    ConnEnd dstPt681881486(Point(5460, 4575), 4);
    connRef681881486->setDestEndpoint(dstPt681881486);
    connRef681881486->setRoutingType((ConnType)2);

    ConnRef* connRef829752 = new ConnRef(router, 829752);
    ConnEnd  srcPt829752(Point(4890, 4400), 8);
    connRef829752->setSourceEndpoint(srcPt829752);
    ConnEnd dstPt829752(Point(5460, 4650), 4);
    connRef829752->setDestEndpoint(dstPt829752);
    connRef829752->setRoutingType((ConnType)2);

    router->processTransaction();
    router->outputDiagramText("/tmp/orthordering-01");
    router->outputInstanceToSVG("/tmp/orthordering-01");
}

TEST(GraphUtils, LibcolaRaw2) {
    using namespace Avoid;
    Router  router_it{Avoid::OrthogonalRouting};
    Router* router = &router_it;

    ShapeRef* shapeRef0;
    ShapeRef* shapeRef1;
    ShapeRef* shapeRef2;

    auto pin_for_shape = [](ShapeRef* shape, int pinClass) {
        new ShapeConnectionPin(
            shape,
            pinClass,
            Avoid::ATTACH_POS_CENTRE,
            Avoid::ATTACH_POS_CENTRE,
            true,
            0,
            Avoid::ConnDirNone);
    };

    { // Edge routing works with already positioned elements
        {
            auto polygon  = Polygon(4);
            polygon.ps[0] = Point(-10.3237, -3.46733);
            polygon.ps[1] = Point(-5.32374, -3.46733);
            polygon.ps[2] = Point(-5.32374, -8.46733);
            polygon.ps[3] = Point(-10.3237, -8.46733);

            shapeRef1 = new ShapeRef(router, polygon, 1);
        }

        {
            auto polygon  = Polygon(4);
            polygon.ps[0] = Point(-56.6515, 15.3407);
            polygon.ps[1] = Point(-51.6515, 15.3407);
            polygon.ps[2] = Point(-51.6515, 10.3407);
            polygon.ps[3] = Point(-56.6515, 10.3407);

            shapeRef0 = new ShapeRef(router, polygon, 1);
        }

        {
            auto polygon  = Polygon(4);
            polygon.ps[0] = Point(-17.1994, 46.0577);
            polygon.ps[1] = Point(-12.1994, 46.0577);
            polygon.ps[2] = Point(-12.1994, 41.0577);
            polygon.ps[3] = Point(-17.1994, 41.0577);

            shapeRef2 = new ShapeRef(router, polygon, 2);
        }
    }

    // each shape can have a number of pins. Pins connected by the same
    // edge must share the same class ID.
    {
        // Shape 0 has two pins, connecting for edge 0 and edge 1.
        pin_for_shape(shapeRef0, 1);
        pin_for_shape(shapeRef0, 2);

        pin_for_shape(shapeRef1, 2);
        pin_for_shape(shapeRef1, 3);

        pin_for_shape(shapeRef2, 3);
        pin_for_shape(shapeRef2, 1);
    }

    {
        { // Edge 0, connecting first pin of shape 0 to the pin of shape 1
            ConnEnd source{shapeRef0, 2};
            ConnEnd target{shapeRef1, 2};
            auto    conn = new ConnRef(router, source, target);
            conn->setRoutingType(ConnType::ConnType_Orthogonal);
        }
        {
            ConnEnd source{shapeRef1, 3};
            ConnEnd target{shapeRef2, 3};
            auto    conn = new ConnRef(router, source, target);
            conn->setRoutingType(ConnType::ConnType_Orthogonal);
        }

        {
            ConnEnd source{shapeRef2, 1};
            ConnEnd target{shapeRef0, 1};
            auto    conn = new ConnRef(router, source, target);
            conn->setRoutingType(ConnType::ConnType_Orthogonal);
        }
    }

    router->processTransaction();
    router->outputInstanceToSVG("/tmp/testLibcolaRaw2");
}

GraphLayoutIR init_graph(
    CVec<GraphEdge> edges,
    GraphSize       size = GraphSize(5, 5)) {
    int           max_node = 0;
    GraphLayoutIR ir;
    ir.edges = edges;
    for (auto const& e : edges) {
        max_node = std::max(max_node, std::max(e.source, e.target));
    }

    for (int i = 0; i <= max_node; ++i) { ir.rectangles.push_back(size); }

    return ir;
}

using C = GraphNodeConstraint;

TEST(GraphUtils, LibcolaIr1) {
    GraphLayoutIR ir;
    ir.edges.push_back({0, 1});
    ir.edges.push_back({1, 2});
    ir.edges.push_back({2, 3});

    ir.rectangles.push_back(GraphSize(5, 5));
    ir.rectangles.push_back(GraphSize(5, 5));
    ir.rectangles.push_back(GraphSize(5, 5));
    ir.rectangles.push_back(GraphSize(5, 5));


    ir.nodeConstraints.push_back(C{C::Align{
        .nodes = {C::Align::Spec{.node = 0}, C::Align::Spec{.node = 1}},
        .dimension = GraphDimension::XDIM,
    }});

    ir.nodeConstraints.push_back(C{C::Align{
        .nodes = {C::Align::Spec{.node = 1}, C::Align::Spec{.node = 3}},
        .dimension = GraphDimension::YDIM,
    }});

    auto lyt = ir.doColaLayout();
    lyt.writeSvg("/tmp/testLibcolaIr1.svg");
    lyt.convert();
}

TEST(GraphUtils, LibcolaIr2) {
    auto ir = init_graph(
        {
            {0, 1},
            {1, 2},
            {2, 0},
            {3, 0},
            {4, 0},
            {2, 3},
            {3, 4},
            {4, 5},
        },
        GraphSize(60, 60));

    ir.width  = 400;
    ir.height = 400;

    auto lyt = ir.doColaLayout();
    lyt.writeSvg("/tmp/testLibcolaIr2.svg");
    auto conv = lyt.convert();

    lyt.router->outputInstanceToSVG("/tmp/testLibcolaIr2_router");
    lyt.router->outputDiagramText("/tmp/testLibcolaIr2_router");
    EXPECT_TRUE(!conv.lines.at({0, 1}).paths.at(0).points.empty());
}

TEST(GraphUtils, tHolaIr1) {
    auto ir = init_graph(
        {
            {0, 1},
            {1, 2},
            {2, 0},
            {3, 0},
            {4, 0},
            {2, 3},
            {3, 4},
            {4, 5},
        },
        GraphSize(60, 60));

    auto lyt = ir.doHolaLayout();
    writeFile("/tmp/testHolaIr1.svg", lyt.graph->writeSvg());
    auto conv = lyt.convert();
    EXPECT_TRUE(!conv.lines.at({0, 1}).paths.at(0).points.empty());
}

TEST(GraphUtils, GraphvizIr1) {
    GraphLayoutIR ir;
    Graphviz      gvc;
    ir.edges.push_back({0, 1});
    ir.edges.push_back({1, 2});
    ir.edges.push_back({2, 3});

    ir.rectangles.push_back(GraphSize(5, 5));
    ir.rectangles.push_back(GraphSize(5, 5));
    ir.rectangles.push_back(GraphSize(20, 20));
    ir.rectangles.push_back(GraphSize(20, 20));
    auto lyt = ir.doGraphvizLayout(gvc);
    lyt.writeSvg("/tmp/testGraphvizIr1.svg");
    lyt.writeXDot("/tmp/testGraphvizIr1.xdot");
    auto converted = lyt.convert();
    EXPECT_EQ(converted.fixed.size(), 4);

    EXPECT_EQ(converted.fixed.at(0).width, 5);
    EXPECT_EQ(converted.fixed.at(0).height, 5);

    EXPECT_EQ(converted.fixed.at(1).width, 5);
    EXPECT_EQ(converted.fixed.at(1).height, 5);

    EXPECT_EQ(converted.fixed.at(2).width, 20);
    EXPECT_EQ(converted.fixed.at(2).height, 20);

    EXPECT_EQ(converted.fixed.at(3).width, 20);
    EXPECT_EQ(converted.fixed.at(3).height, 20);

    EXPECT_EQ(converted.lines.size(), 3);
}

TEST(GraphUtils, GraphvizIrClusters) {
    GraphLayoutIR ir;
    Graphviz      gvc;

    auto edge = [&](int source, int target) {
        ir.edges.push_back({source, target});
    };

    for (int i = 0; i <= 10; ++i) {
        ir.rectangles.push_back(GraphSize(10, 10));
    }

    using S = GraphLayoutIR::Subgraph;


    edge(0, 2);
    edge(2, 1);
    edge(1, 8);
    edge(8, 3);
    edge(3, 4);
    edge(4, 6);
    edge(3, 6);
    edge(8, 5);
    edge(5, 9);
    edge(9, 10);
    edge(10, 7);
    edge(7, 5);

    ir.subgraphs.push_back(
        S{.nodes     = {}, // No nodes in the first cluster,
          .subgraphs = {
              S{.nodes = {3, 4, 6}},
              S{.nodes = {5, 9, 7, 10}},
          }});

    auto lyt = ir.doGraphvizLayout(gvc);
    lyt.writeSvg("/tmp/testGraphvizIrClusters.svg");
    lyt.writeXDot("/tmp/testGraphvizIrClusters.xdot");
    auto c = lyt.convert();

    EXPECT_EQ(c.subgraphPaths.size(), 3);
    EXPECT_EQ(c.subgraphs.size(), 1);
    EXPECT_EQ(c.subgraphs.at(0).subgraphs.size(), 2);
    EXPECT_EQ(c.getSubgraph({0}).subgraphs.size(), 2);
    EXPECT_EQ(c.getSubgraph({0, 0}).subgraphs.size(), 0);
    EXPECT_EQ(c.getSubgraph({0, 1}).subgraphs.size(), 0);
    EXPECT_EQ(c.subgraphPaths.at(0), Vec<int>{0});
    EXPECT_EQ(c.subgraphPaths.at(1), (Vec<int>{0, 0}));
    EXPECT_EQ(c.subgraphPaths.at(2), (Vec<int>{0, 1}));
    // QEXPECT_TRUE(toQRect(c.getSubgraph({0}).bbox)
    //                  .contains(toQRect(c.getSubgraph({0, 0}).bbox)));
    // QEXPECT_TRUE(toQRect(c.getSubgraph({0}).bbox)
    //                  .contains(toQRect(c.getSubgraph({0, 1}).bbox)));
}
