#include "../t_graph_tests_common.hpp"

struct GraphAdaptagramsRaw_Test : public GraphUtils_Test {};


TEST_F(GraphAdaptagramsRaw_Test, LibcolaRaw1) {
    // Expected shape for the visualization
    //     rect_width
    //    ├───────────┤
    // 0,0┌───────────┐
    //    │           │
    //    │           ├──────────┐
    //    │           │          │
    //    │           │          │
    //    │           ├───────┐  │
    //    │           │       │  │
    //    │           │       │  │
    //    │           ├────┐  │  │
    //    │           │    │  │  │
    //    │           │    │  │  │    650,350┌────────────┐
    //    └───────────┘    │  │  │           │            │
    //                     │  │  └───────────┤            │
    //                     │  │              │            │
    //                     │  │              │            │
    //                     │  └──────────────┤            │
    //                     │                 │            │
    //                     │                 │            │
    //                     └─────────────────┤            │
    //                                       │            │
    //                                       └────────────┘


    Avoid::Router router_it{
        Avoid::PolyLineRouting | Avoid::OrthogonalRouting};
    Avoid::Router* router = &router_it;
    router->setRoutingPenalty(Avoid::RoutingParameter::segmentPenalty, 50);
    router->setRoutingPenalty(Avoid::RoutingParameter::anglePenalty, 0);
    router->setRoutingPenalty(
        Avoid::RoutingParameter::crossingPenalty, 400);
    router->setRoutingPenalty(
        Avoid::RoutingParameter::clusterCrossingPenalty, 4000);
    router->setRoutingPenalty(
        Avoid::RoutingParameter::fixedSharedPathPenalty, 110);
    router->setRoutingParameter(Avoid::idealNudgingDistance, 25);

    double right_rect_x = 650;
    double right_rect_y = 350;
    // Use non-zero inset to move the connection edges slightly inside of
    // the shape so libavoid does not consider them free-floating (if this
    // happens the start/end segment of edge can run perfectly flush along
    // the rectangle boundary).
    //
    // Alternative solutions to enforce edges orthogonal to the rect side
    // - Boundary Inflation: Use
    //   `router->setRoutingParameter(Avoid::shapeBufferDistance, 5);`
    //   This globally inflates the routing obstacles so points on the
    //   visual edge are treated as being inside the routing boundary,
    //   enforcing the direction flags.
    // - Shape Connection Pins: Instead of using absolute free-floating
    //   coordinates, attach the connections using
    //   `Avoid::ShapeConnectionPin`. This natively
    //   forces perpendicular exits from the shape's edges without relying
    //   on coordinate math.
    double inset = 0.001;
    // with inset 0 the shape will be
    // ┌──────────────┐
    // │              │
    // │              │
    // │              │
    // │              │
    // │              ├──────────────────────────┐
    // │              ├──────────────────────────┤
    // │              │                          │
    // │              ├──────────────────────────┤
    // └──────────────┘                          │
    //                                           │
    //                                           ├──────────────┐
    //                                           │              │
    //                                           │              │
    //                                           │              │
    //                                           │              │
    //                                           │              │
    //                                           └──────────────┘

    double rect_width     = 300;
    double rect_height    = 700;
    double connector_step = 60;
    // right rectangle
    Avoid::Polygon poly4(4);
    poly4.ps[0] = Avoid::Point(right_rect_x + rect_width, right_rect_y);
    poly4.ps[1] = Avoid::Point(
        right_rect_x + rect_width, right_rect_y + rect_height);
    poly4.ps[2] = Avoid::Point(right_rect_x, right_rect_y + rect_height);
    poly4.ps[3] = Avoid::Point(right_rect_x, right_rect_y);
    new Avoid::ShapeRef(router, poly4, /*id=*/4);

    // left rectangle
    Avoid::Polygon poly5(4);
    poly5.ps[0] = Avoid::Point(rect_width, 0);
    poly5.ps[1] = Avoid::Point(rect_width, rect_height);
    poly5.ps[2] = Avoid::Point(0, rect_height);
    poly5.ps[3] = Avoid::Point(0, 0);
    new Avoid::ShapeRef(router, poly5, /*id=*/5);

    // first edge
    Avoid::ConnRef* connRef1 = new Avoid::ConnRef(router, /*id=*/1);
    Avoid::ConnEnd  srcPt1(
        Avoid::Point(rect_width - inset, connector_step * 2),
        Avoid::ConnDirRight);
    connRef1->setSourceEndpoint(srcPt1);
    Avoid::ConnEnd dstPt1(
        Avoid::Point(
            right_rect_x + inset, right_rect_y + connector_step * 2),
        Avoid::ConnDirLeft);
    connRef1->setDestEndpoint(dstPt1);
    connRef1->setRoutingType(Avoid::ConnType::ConnType_Orthogonal);

    // second edge
    Avoid::ConnRef* connRef2 = new Avoid::ConnRef(router, /*id=*/2);
    Avoid::ConnEnd  srcPt2(
        Avoid::Point(rect_width - inset, connector_step * 3),
        Avoid::ConnDirRight);
    connRef2->setSourceEndpoint(srcPt2);
    Avoid::ConnEnd dstPt2(
        Avoid::Point(
            right_rect_x + inset, right_rect_y + connector_step * 3),
        Avoid::ConnDirLeft);
    connRef2->setDestEndpoint(dstPt2);
    connRef2->setRoutingType(Avoid::ConnType::ConnType_Orthogonal);

    // third edge
    Avoid::ConnRef* connRef3 = new Avoid::ConnRef(router, /*id=*/3);
    Avoid::ConnEnd  srcPt3(
        Avoid::Point(rect_width - inset, connector_step * 4),
        Avoid::ConnDirRight);
    connRef3->setSourceEndpoint(srcPt3);
    Avoid::ConnEnd dstPt3(
        Avoid::Point(
            right_rect_x + inset, right_rect_y + connector_step * 4),
        Avoid::ConnDirLeft);
    connRef3->setDestEndpoint(dstPt3);
    connRef3->setRoutingType(Avoid::ConnType::ConnType_Orthogonal);

    router->processTransaction();

    auto path1 = adapt::to_hstd_path(connRef1->displayRoute());
    auto path2 = adapt::to_hstd_path(connRef2->displayRoute());
    auto path3 = adapt::to_hstd_path(connRef3->displayRoute());

    using namespace visual;

    VisGroup result;
    for (auto const& group : hstd::as_vec(path1, path2, path3)) {
        result.elements.push_back(
            VisElement{VisElement::PathShape{group}});
    }

    auto rect_right = adapt::to_hstd_rect(poly4);
    auto rect_left  = adapt::to_hstd_rect(poly5);

    result.elements.push_back(
        VisElement{VisElement::RectShape{rect_right}});
    result.elements.push_back(
        VisElement{VisElement::RectShape{rect_left}});

    hstd::writeFile(
        getDebugFile("result.svg"),
        toSvg({result}, /*debug=*/false).to_string());

    EXPECT_OUTCOME_OK(
        checkLeftOf(/*stationary=*/rect_right, /*relative=*/rect_left));

    EXPECT_OUTCOME_OK(checkPartiallyAbove(
        /*stationary=*/rect_right, /*relative=*/rect_left, 70));
}


TEST_F(GraphAdaptagramsRaw_Test, LibcolaRaw2) {
    //                             ┌────────────┐
    //                             │            │
    //                         ┌───┤            │
    // ┌───────────────────┐   │   │            │
    // │ ┌────────────┐    │   │   │            │
    // │ │            │    └───┼───┤            │
    // └─┤            │        │   └────────────┘
    //   │            │        │
    // ┌─┤            │        │
    // │ │            │        │
    // │ └────────────┘        │   ┌────────────┐
    // │                       │   │            │
    // └───────────────────────┼───┤            │
    //                         │   │            │
    //                         └───┤            │
    //                             │            │
    //                             └────────────┘
    Avoid::Router  router_it{Avoid::OrthogonalRouting};
    Avoid::Router* router = &router_it;
    router->setRoutingParameter(Avoid::idealNudgingDistance, 4);
    router->setRoutingOption(
        Avoid::nudgeOrthogonalSegmentsConnectedToShapes, true);
    router->setRoutingOption(
        Avoid::improveHyperedgeRoutesMovingJunctions, true);
    router->setRoutingOption(
        Avoid::penaliseOrthogonalSharedPathsAtConnEnds, true);
    // buffer distance is mandatory for sane routing, otherwise most of the
    // edges will run perfectly flush against the rectangles.
    router->setRoutingParameter(Avoid::shapeBufferDistance, 10);

    auto pin_for_shape =
        // Y position is mandatory, if connection points overlap with each
        // other the whole edge automatically collapses to the straight
        // line between the start and end shape centers. Setting nudge
        // distance does not affect it in any way.
        [](Avoid::ShapeRef* shape, int pinClass, double yPos) {
            new Avoid::ShapeConnectionPin(
                shape,
                pinClass,
                Avoid::ATTACH_POS_LEFT,
                yPos,
                /*proportional=*/true,
                /*insideOffset=*/0,
                /*visDirs=*/Avoid::ConnDirLeft);
        };

    auto add_rect =
        [&](double x,
            double y) -> std::pair<Avoid::ShapeRef*, Avoid::Rectangle> {
        double w = 100;
        double h = 100;

        auto polygon = Avoid::Rectangle(
            Avoid::Point(x, y), Avoid::Point(x + w, y + h));

        auto ref = new Avoid::ShapeRef(router, polygon);

        return {ref, polygon};
    };

    // Edge routing works with already positioned elements
    auto [shapeRef0, polygon0] = add_rect(-100, 100);
    auto [shapeRef1, polygon1] = add_rect(-500, 150);
    auto [shapeRef2, polygon2] = add_rect(-170, 460);

    // each shape can have a number of pins. Pins connected by the same
    // edge must share the same class ID.
    // Shape 0 has two pins, connecting for edge 0 and edge 1.
    pin_for_shape(shapeRef0, 1, 0.25);
    pin_for_shape(shapeRef0, 2, 0.75);

    pin_for_shape(shapeRef1, 2, 0.25);
    pin_for_shape(shapeRef1, 3, 0.75);

    pin_for_shape(shapeRef2, 3, 0.25);
    pin_for_shape(shapeRef2, 1, 0.75);

    // Edge 0, connecting first pin of shape 0 to the pin of shape 1
    auto conn01 = new Avoid::ConnRef(
        router,
        Avoid::ConnEnd{shapeRef0, 2},
        Avoid::ConnEnd{shapeRef1, 2});
    conn01->setRoutingType(Avoid::ConnType::ConnType_Orthogonal);

    auto conn12 = new Avoid::ConnRef(
        router,
        Avoid::ConnEnd{shapeRef1, 3},
        Avoid::ConnEnd{shapeRef2, 3});
    conn12->setRoutingType(Avoid::ConnType::ConnType_Orthogonal);

    auto conn20 = new Avoid::ConnRef(
        router,
        Avoid::ConnEnd{shapeRef2, 1},
        Avoid::ConnEnd{shapeRef0, 1});
    conn20->setRoutingType(Avoid::ConnType::ConnType_Orthogonal);

    router->processTransaction();

    visual::VisGroup result;
    adapt::add_rect(result, polygon0);
    adapt::add_rect(result, polygon1);
    adapt::add_rect(result, polygon2);

    adapt::add_path(result, conn01->displayRoute());
    adapt::add_path(result, conn12->displayRoute());
    adapt::add_path(result, conn20->displayRoute());

    hstd::writeFile(
        getDebugFile("result.svg"),
        visual::toSvg({result}, /*debug=*/false).to_string());

    router->outputInstanceToSVG("/tmp/testLibcolaRaw2");
}

TEST_F(GraphAdaptagramsRaw_Test, LibavoidRaw1) {
    auto router = std::make_shared<Avoid::Router>(
        Avoid::PolyLineRouting | Avoid::OrthogonalRouting);
    router->setRoutingParameter(
        Avoid::RoutingParameter::segmentPenalty, 50);
    router->setRoutingParameter(Avoid::RoutingParameter::anglePenalty, 0);
    router->setRoutingParameter(
        Avoid::RoutingParameter::crossingPenalty, 0);
    router->setRoutingParameter(
        Avoid::RoutingParameter::clusterCrossingPenalty, 4000);
    router->setRoutingParameter(
        Avoid::RoutingParameter::fixedSharedPathPenalty, 0);
    router->setRoutingParameter(
        Avoid::RoutingParameter::portDirectionPenalty, 100);
    router->setRoutingParameter(
        Avoid::RoutingParameter::shapeBufferDistance, 0);
    router->setRoutingParameter(
        Avoid::RoutingParameter::idealNudgingDistance, 4);
    router->setRoutingOption(
        Avoid::RoutingOption::nudgeOrthogonalSegmentsConnectedToShapes,
        true);
    router->setRoutingOption(
        Avoid::RoutingOption::improveHyperedgeRoutesMovingJunctions, true);
    router->setRoutingOption(
        Avoid::RoutingOption::penaliseOrthogonalSharedPathsAtConnEnds,
        false);
    router->setRoutingOption(
        Avoid::RoutingOption::nudgeOrthogonalTouchingColinearSegments,
        false);

    double rectMaxX       = -250;
    double rectMinX       = -300;
    double rectConnectorX = rectMaxX - 1;
    double rectSize       = 20;

    std::vector<Avoid::Checkpoint> checkpoints{
        Avoid::Checkpoint{
            Avoid::Point{-250, 785},
            Avoid::ConnDirFlag::ConnDirAll,
            Avoid::ConnDirFlag::ConnDirAll,
        },
        Avoid::Checkpoint{
            Avoid::Point{500, 500},
            Avoid::ConnDirFlag::ConnDirAll,
            Avoid::ConnDirFlag::ConnDirAll,
        },
        Avoid::Checkpoint{
            Avoid::Point{400, 400},
            Avoid::ConnDirFlag::ConnDirAll,
            Avoid::ConnDirFlag::ConnDirAll,
        },
        Avoid::Checkpoint{
            Avoid::Point{400, 240},
            Avoid::ConnDirFlag::ConnDirAll,
            Avoid::ConnDirFlag::ConnDirAll,
        },
    };


    Avoid::ConnEnd dstPt(
        Avoid::Point(160, 240), Avoid::ConnDirFlag::ConnDirRight);


    auto add_rect = [&](double x, double y, double w, double h)
        -> std::pair<Avoid::ShapeRef*, Avoid::Rectangle> {
        auto polygon = Avoid::Rectangle(
            Avoid::Point(x, y), Avoid::Point(x + w, y + h));

        auto ref = new Avoid::ShapeRef(router.get(), polygon);

        return {ref, polygon};
    };

    auto add_left_box = [&](double rectY, int connId, uint shapeRefId)
        -> std::pair<Avoid::ConnRef*, Avoid::ShapeRef*> {
        Avoid::Polygon poly(4);
        poly.ps[0] = Avoid::Point{rectMaxX, rectY};
        poly.ps[1] = Avoid::Point{rectMaxX, rectY + rectSize};
        poly.ps[2] = Avoid::Point{rectMinX, rectY + rectSize};
        poly.ps[3] = Avoid::Point{rectMinX, rectY};
        auto shape = new Avoid::ShapeRef{router.get(), poly, shapeRefId};
        Avoid::ConnRef* conn = new Avoid::ConnRef(router.get(), connId);
        Avoid::ConnEnd  srcPt(
            Avoid::Point(rectConnectorX, rectY + rectSize / 2), 8);
        conn->setSourceEndpoint(srcPt);
        conn->setDestEndpoint(dstPt);
        conn->setRoutingType(Avoid::ConnType::ConnType_Orthogonal);
        conn->setRoutingCheckpoints(checkpoints);
        return {conn, shape};
    };

    int id                    = 0;
    auto [conn1, left_shape1] = add_left_box(380, id + 1, id + 2);
    id += 2;
    auto [conn2, left_shape2] = add_left_box(530, id + 1, id + 2);
    id += 2;
    auto [conn3, left_shape3] = add_left_box(600, id + 1, id + 2);
    id += 2;
    auto [conn4, left_shape4] = add_left_box(670, id + 1, id + 2);
    id += 2;
    auto [conn5, left_shape5] = add_left_box(900, id + 1, id + 2);

    auto [_1, dest]      = add_rect(120, 200, 60, 80);
    auto [_2, obstacle1] = add_rect(-120, 450, 60, 220);
    auto [_3, obstacle2] = add_rect(-120, 100, 60, 50);

    router->processTransaction();

    visual::VisGroup result;

    adapt::add_rect(result, dest);
    adapt::add_rect(result, obstacle1);
    adapt::add_rect(result, obstacle2);
    adapt::add_path(result, conn1->displayRoute());
    adapt::add_path(result, conn2->displayRoute());
    adapt::add_path(result, conn3->displayRoute());
    adapt::add_path(result, conn4->displayRoute());
    adapt::add_path(result, conn5->displayRoute());
    adapt::add_rect(result, left_shape1->routingPolygon());
    adapt::add_rect(result, left_shape2->routingPolygon());
    adapt::add_rect(result, left_shape3->routingPolygon());
    adapt::add_rect(result, left_shape4->routingPolygon());
    adapt::add_rect(result, left_shape5->routingPolygon());
    adapt::add_checkpoint(result, checkpoints.at(0));
    adapt::add_checkpoint(result, checkpoints.at(1));
    adapt::add_checkpoint(result, checkpoints.at(2));
    adapt::add_checkpoint(result, checkpoints.at(3));

    hstd::writeFile(
        getDebugFile("result.svg"),
        visual::toSvg({result}, /*debug=*/false).to_string());
}


namespace {
void addPinsForShape(Avoid::ShapeRef* shape, int pinsPerSide) {
    for (int i = 0; i < pinsPerSide; ++i) {
        double t = static_cast<double>(i + 1)
                 / static_cast<double>(pinsPerSide + 1);

        new Avoid::ShapeConnectionPin(
            shape, 1, t, 0.0, true, 0.0, Avoid::ConnDirUp);
        new Avoid::ShapeConnectionPin(
            shape, 1, 1.0, t, true, 0.0, Avoid::ConnDirRight);
        new Avoid::ShapeConnectionPin(
            shape, 1, t, 1.0, true, 0.0, Avoid::ConnDirDown);
        new Avoid::ShapeConnectionPin(
            shape, 1, 0.0, t, true, 0.0, Avoid::ConnDirLeft);
    }
}

Avoid::Polygon rectToPolygon(vpsc::Rectangle const* rect) {
    Avoid::Polygon poly(4);
    poly.ps[0] = Avoid::Point(rect->getMinX(), rect->getMinY());
    poly.ps[1] = Avoid::Point(rect->getMaxX(), rect->getMinY());
    poly.ps[2] = Avoid::Point(rect->getMaxX(), rect->getMaxY());
    poly.ps[3] = Avoid::Point(rect->getMinX(), rect->getMaxY());
    return poly;
}
} // namespace
