#include <iostream>

#include <libavoid/libavoid.h>

int main() {
    Avoid::Router router(Avoid::PolyLineRouting);

    Avoid::Rectangle obstacle(Avoid::Point(40.0, -20.0), Avoid::Point(60.0, 20.0));

    new Avoid::ShapeRef(&router, obstacle, 1);

    auto* connector = new Avoid::ConnRef(
        &router,
        Avoid::ConnEnd(Avoid::Point(0.0, 0.0)),
        Avoid::ConnEnd(Avoid::Point(100.0, 0.0)),
        2);

    connector->setRoutingType(Avoid::ConnType_PolyLine);
    router.processTransaction();

    if (connector->displayRoute().size() < 3) {
        std::cerr << "Expected a route bending around the obstacle\n";
        return 1;
    }

    return 0;
}
