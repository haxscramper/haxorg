#include <gtest/gtest.h>
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>
#include <libcola/output_svg.h>

using namespace hstd::ext;
using namespace hstd;

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

TEST(GraphUtils, LibavoidRaw1) {
    using namespace Avoid;
    Router* router = new Router(PolyLineRouting | OrthogonalRouting);
    router->setRoutingParameter((RoutingParameter)0, 50);
    router->setRoutingParameter((RoutingParameter)1, 0);
    router->setRoutingParameter((RoutingParameter)2, 0);
    router->setRoutingParameter((RoutingParameter)3, 4000);
    router->setRoutingParameter((RoutingParameter)4, 0);
    router->setRoutingParameter((RoutingParameter)5, 100);
    router->setRoutingParameter((RoutingParameter)6, 0);
    router->setRoutingParameter((RoutingParameter)7, 4);
    router->setRoutingOption((RoutingOption)0, true);
    router->setRoutingOption((RoutingOption)1, true);
    router->setRoutingOption((RoutingOption)2, false);
    router->setRoutingOption((RoutingOption)3, false);

    double rectMaxX       = -264;
    double rectMinX       = -296;
    double rectConnectorX = rectMaxX - 1;
    double rectSize       = 20;

    std::vector<Checkpoint> checkpoints{
        Checkpoint{
            Point{-242, 782},
            ConnDirFlag::ConnDirAll,
            ConnDirFlag::ConnDirAll,
        },
        Checkpoint{
            Point{500, 500},
            ConnDirFlag::ConnDirAll,
            ConnDirFlag::ConnDirAll,
        },
        Checkpoint{
            Point{400, 400},
            ConnDirFlag::ConnDirAll,
            ConnDirFlag::ConnDirAll,
        },
        Checkpoint{
            Point{400, 240},
            ConnDirFlag::ConnDirAll,
            ConnDirFlag::ConnDirAll,
        },
    };


    ConnEnd dstPt(Point(160, 240), ConnDirFlag::ConnDirRight);

    auto add_left_box = [&](double rectY, int connId, uint shapeRefId) {
        Polygon poly(4);
        poly.ps[0] = Point{rectMaxX, rectY};
        poly.ps[1] = Point{rectMaxX, rectY + rectSize};
        poly.ps[2] = Point{rectMinX, rectY + rectSize};
        poly.ps[3] = Point{rectMinX, rectY};
        new ShapeRef{router, poly, shapeRefId};
        ConnRef* conn = new ConnRef(router, connId);
        ConnEnd  srcPt(Point(rectConnectorX, rectY + rectSize / 2), 8);
        conn->setSourceEndpoint(srcPt);
        conn->setDestEndpoint(dstPt);
        conn->setRoutingType(ConnType::ConnType_Orthogonal);
        conn->setRoutingCheckpoints(checkpoints);
    };

    int id = 0;
    add_left_box(376, id + 1, id + 2);
    id += 2;
    add_left_box(526, id + 1, id + 2);
    id += 2;
    add_left_box(601, id + 1, id + 2);
    id += 2;
    add_left_box(676, id + 1, id + 2);
    id += 2;
    add_left_box(900, id + 1, id + 2);

    {
        Polygon dest(4);
        dest.ps[0] = Point(180, 200);
        dest.ps[1] = Point(180, 280);
        dest.ps[2] = Point(120, 280);
        dest.ps[3] = Point(120, 200);
        new ShapeRef(router, dest, 42);
    }

    {
        Polygon obstacle(4);
        obstacle.ps[0] = Point(-120, 690);
        obstacle.ps[1] = Point(-120, 830);
        obstacle.ps[2] = Point(-180, 830);
        obstacle.ps[3] = Point(-180, 690);
        new ShapeRef(router, obstacle, 59);
    }

    {
        Polygon obstacle(4);
        obstacle.ps[0] = Point(-120, 100);
        obstacle.ps[1] = Point(-120, 250);
        obstacle.ps[2] = Point(-180, 250);
        obstacle.ps[3] = Point(-180, 100);
        new ShapeRef(router, obstacle, 60);
    }


    router->processTransaction();
    router->outputInstanceToSVG("/tmp/nudgingSkipsCheckpoint02");

    delete router;
}

TEST(GraphUtils, LibcolaRaw3) {
    using namespace Avoid;
    std::vector<std::pair<unsigned, unsigned>> edges{
        {0, 1},
        {1, 2},
        {2, 3},
    };

    double mult  = 10;
    double width = 100 * mult;

    std::vector<vpsc::Rectangle*> rectangles;

    for (unsigned i = 0; i < 4; i++) {
        double x = i * 10 * mult;
        double y = i * 10 * mult;
        rectangles.push_back(
            new vpsc::Rectangle(x, x + 10 * mult, y, y + 10 * mult));
    }

    cola::CompoundConstraints ccs;

    cola::AlignmentConstraint align_on_x1{vpsc::XDIM};
    ccs.push_back(&align_on_x1);
    align_on_x1.addShape(0, 0);
    align_on_x1.addShape(1, 0);

    cola::AlignmentConstraint align_on_x2{vpsc::XDIM};
    ccs.push_back(&align_on_x2);
    align_on_x2.addShape(2, 0);

    cola::AlignmentConstraint align_on_x3{vpsc::XDIM};
    ccs.push_back(&align_on_x3);
    align_on_x3.addShape(3, 0);

    cola::MultiSeparationConstraint separate{vpsc::XDIM};
    ccs.push_back(&separate);
    separate.setSeparation(50 * mult);
    separate.addAlignmentPair(&align_on_x1, &align_on_x2);
    separate.addAlignmentPair(&align_on_x2, &align_on_x3);


    cola::ConstrainedFDLayout alg2(rectangles, edges, width / 2);
    alg2.setConstraints(ccs);
    alg2.run();

    Router* router = new Router(OrthogonalRouting);
    router->setRoutingPenalty((PenaltyType)0, 50);
    router->setRoutingOption(
        nudgeOrthogonalSegmentsConnectedToShapes, true);
    router->setRoutingOption(
        nudgeOrthogonalTouchingColinearSegments, true);

    auto r = [&](int idx) -> vpsc::Rectangle& {
        return *rectangles.at(idx);
    };

    Rectangle shapeRect1(
        Point(r(0).getMinX(), r(0).getMinY()),
        Point(r(0).getMaxX(), r(0).getMaxY()));

    ShapeRef* shapeRef1 = new ShapeRef{router, shapeRect1, 1};

    Rectangle shapeRect2(
        Point(r(1).getMinX(), r(1).getMinY()),
        Point(r(1).getMaxX(), r(1).getMaxY()));
    ShapeRef* shapeRef2 = new ShapeRef{router, shapeRect2, 2};

    Rectangle shapeRect3(
        Point(r(2).getMinX(), r(2).getMinY()),
        Point(r(2).getMaxX(), r(2).getMaxY()));

    ShapeRef* shapeRef3 = new ShapeRef{router, shapeRect3, 3};

    Rectangle shapeRect4(
        Point(r(3).getMinX(), r(3).getMinY()),
        Point(r(3).getMaxX(), r(3).getMaxY()));

    ShapeRef* shapeRef4 = new ShapeRef{router, shapeRect4, 4};

    uint ID_1_1 = 1;
    uint ID_2_1 = 2;
    uint ID_4_1 = 4;
    uint ID_3_1 = 5;
    uint ID_3_2 = 6;
    uint ID_3_3 = 7;

    uint ID_common = 8;

    double dMin = 0.0;
    double dMid = 0.5;
    double dMax = 1.0;

    // 1 -> 3 target pin
    new ShapeConnectionPin{
        shapeRef3, ID_3_1, dMin, dMid + 0.02, true, 0, ConnDirLeft};

    // 2 -> 3 target pin
    new ShapeConnectionPin{
        shapeRef3, ID_3_2, dMin, dMid, true, 0, ConnDirLeft};

    // 3 -> 4 source pin
    new ShapeConnectionPin{
        shapeRef3, ID_3_3, dMax, dMid, true, 0, ConnDirRight};

    // 1 -> 3 source pin
    new ShapeConnectionPin{
        shapeRef1, ID_1_1, dMid, dMax, true, 0.0, ConnDirDown};

    // 2 -> 3 source pin
    new ShapeConnectionPin{
        shapeRef2, ID_2_1, dMid, dMax, true, 0.0, ConnDirDown};

    // 3 -> 4 target pin
    new ShapeConnectionPin{
        shapeRef4, ID_4_1, dMin, dMid, true, 0.0, ConnDirLeft};

    new ConnRef{
        router,
        ConnEnd{shapeRef2, ID_2_1},
        ConnEnd{shapeRef3, ID_3_2},
    };

    new ConnRef{
        router,
        ConnEnd{shapeRef1, ID_1_1},
        ConnEnd{shapeRef3, ID_3_1},
    };

    new ConnRef{
        router,
        ConnEnd{shapeRef3, ID_3_3},
        ConnEnd{shapeRef4, ID_4_1},
    };


    router->processTransaction();
    router->outputInstanceToSVG("/tmp/LibcolaRaw3");
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
        .nodes
        = {GraphNodeConstraint::Align::Spec{.node = 0},
           GraphNodeConstraint::Align::Spec{.node = 1}},
        .dimension = GraphDimension::XDIM,
    }});

    ir.nodeConstraints.push_back(C{C::Align{
        .nodes
        = {GraphNodeConstraint::Align::Spec{.node = 1},
           GraphNodeConstraint::Align::Spec{.node = 3}},
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

TEST(GraphUtils, LibcolaIr3) {
    GraphLayoutIR ir;

    ir.edges = {
        GraphEdge{.source = 0, .target = 3},
        GraphEdge{.source = 1, .target = 4},
        GraphEdge{.source = 1, .target = 5},
        GraphEdge{.source = 1, .target = 6},
        GraphEdge{.source = 2, .target = 7},
        GraphEdge{.source = 3, .target = 8},
        GraphEdge{.source = 4, .target = 8},
        GraphEdge{.source = 4, .target = 9},
        GraphEdge{.source = 5, .target = 9},
        GraphEdge{.source = 6, .target = 9},
        GraphEdge{.source = 6, .target = 10},
        GraphEdge{.source = 7, .target = 9},
        GraphEdge{.source = 7, .target = 11},
    };

    auto& ec = ir.edgeConstraints;
    using P  = GraphEdgeConstraint::Port;
    // ec[GraphEdge{.source = }]

    ec[{.source = 7, .target = 9}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 6, .target = 10}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 6, .target = 9}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 4, .target = 9}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 1, .target = 6}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 3, .target = 8}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 1, .target = 5}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 7, .target = 11}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 4, .target = 8}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 2, .target = 7}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 1, .target = 4}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 5, .target = 9}] = GraphEdgeConstraint{
        .sourcePort = P::East, .targetPort = P::West};
    ec[{.source = 0, .target = 3}] = GraphEdgeConstraint{
        .sourcePort       = P::East,
        .targetPort       = P::West,
        .targetCheckpoint = 20,
    };


    using C   = GraphNodeConstraint;
    auto ydim = GraphDimension::YDIM;
    auto xdim = GraphDimension::XDIM;

    ir.nodeConstraints = {
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 0}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 1}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 1}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 2}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 3}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 4}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 4}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 5}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 5}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 6}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 6}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 7}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 8}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 9}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left              = C::
                Align{.dimension = ydim, .nodes = {C::Align::Spec{.node = 9}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 10}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = ydim,
            .isExactSeparation = true,
            .left = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 10}}},
            .right = {.dimension = ydim, .nodes = {C::Align::Spec{.node = 11}}},
            .separationDistance = 75.0}},
        C{C::Separate{
            .dimension         = xdim,
            .isExactSeparation = true,
            .left
            = {.dimension = xdim,
               .nodes
               = {C::Align::Spec{.node = 0},
                  C::Align::
                      Spec{.node = 1},
                  C::Align::
                      Spec{.node = 2}}},
            .right
            = {.dimension = xdim,
               .nodes
               = {C::Align::Spec{.node = 3},
                  C::Align::
                      Spec{.node = 4},
                  C::Align::
                      Spec{.node = 5},
                  C::Align::
                      Spec{.node = 6},
                  C::Align::
                      Spec{.node = 7}}},
            .separationDistance = 125.0}},
        C{C::Separate{
            .dimension         = xdim,
            .isExactSeparation = true,
            .left
            = {.dimension = xdim,
               .nodes
               = {C::Align::Spec{.node = 3},
                  C::Align::
                      Spec{.node = 4},
                  C::Align::
                      Spec{.node = 5},
                  C::Align::
                      Spec{.node = 6},
                  C::Align::
                      Spec{.node = 7}}},
            .right
            = {.dimension = xdim,
               .nodes
               = {C::Align::Spec{.node = 8},
                  C::Align::
                      Spec{.node = 9},
                  C::Align::
                      Spec{.node = 10},
                  C::Align::
                      Spec{.node = 11}}},
            .separationDistance = 125.0}}};

    ir.rectangles = {
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
        GraphSize{.h = 25.0, .w = 75.0},
    };

    ir.height = 10000;
    ir.width  = 10000;

    auto lyt = ir.doColaLayout();
    lyt.writeSvg("/tmp/testLibcolaIr3.svg");
    auto conv = lyt.convert();

    lyt.router->outputInstanceToSVG("/tmp/testLibcolaIr3_router");
    lyt.router->outputDiagramText("/tmp/testLibcolaIr3_router");
}

TEST(GraphUtils, LibcolaIrMultiEdge) {
    GraphLayoutIR ir;

    ir.edges = {
        GraphEdge{.source = 0, .target = 1, .bundle = 0},
        GraphEdge{.source = 0, .target = 1, .bundle = 1},
        GraphEdge{.source = 0, .target = 1, .bundle = 2},
        GraphEdge{.source = 0, .target = 1, .bundle = 3},
    };

    auto& ec    = ir.edgeConstraints;
    using P     = GraphEdgeConstraint::Port;
    float shift = 0.2f;
    // ec[GraphEdge{.source = }]


    ec[GraphEdge{
        .source = 0,
        .target = 1,
        .bundle = 0,
    }] = GraphEdgeConstraint{
        .sourcePort       = P::East,
        .targetPort       = P::West,
        .sourceOffset     = 0.1f + shift * 0,
        .targetOffset     = 0.9f - shift * 0,
        .sourceCheckpoint = 30,
        .targetCheckpoint = 30,
    };

    ec[GraphEdge{
        .source = 0,
        .target = 1,
        .bundle = 1,
    }] = GraphEdgeConstraint{
        .sourcePort   = P::East,
        .targetPort   = P::West,
        .sourceOffset = 0.1f + shift * 1,
        .targetOffset = 0.9f - shift * 1,
    };

    ec[GraphEdge{
        .source = 0,
        .target = 1,
        .bundle = 2,
    }] = GraphEdgeConstraint{
        .sourcePort   = P::East,
        .targetPort   = P::West,
        .sourceOffset = 0.1f + shift * 2,
        .targetOffset = 0.9f - shift * 2,
    };

    ec[GraphEdge{
        .source = 0,
        .target = 1,
        .bundle = 3,
    }] = GraphEdgeConstraint{
        .sourcePort   = P::East,
        .targetPort   = P::West,
        .sourceOffset = 0.1f + shift * 3,
        .targetOffset = 0.9f - shift * 3,
    };


    using C   = GraphNodeConstraint;
    auto ydim = GraphDimension::YDIM;
    auto xdim = GraphDimension::XDIM;

    ir.nodeConstraints = {
        C{C::Separate{
            .dimension         = xdim,
            .isExactSeparation = true,
            .left = {.dimension = xdim, .nodes = {C::Align::Spec{.node = 0}}},
            .right = {.dimension = xdim, .nodes = {C::Align::Spec{.node = 1}}},
            .separationDistance = 200.0}},
    };

    ir.rectangles = {
        GraphSize{.h = 100.0, .w = 25.0},
        GraphSize{.h = 100.0, .w = 25.0},
    };

    ir.height = 10000;
    ir.width  = 10000;

    auto lyt = ir.doColaLayout();
    lyt.writeSvg("/tmp/LibcolaIrMultiEdge.svg");
    auto conv = lyt.convert();

    lyt.router->outputInstanceToSVG("/tmp/LibcolaIrMultiEdge_router");
    lyt.router->outputDiagramText("/tmp/LibcolaIrMultiEdge_router");
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
