#include "hstd_geometry.hpp"

using namespace hstd::ext::geometry;

Rect hstd::JsonSerde<Rect>::from_json(json const& j) {
    return Rect(
        JsonSerde<Point>::from_json(j.at("min")),
        JsonSerde<Point>::from_json(j.at("max")));
}

json hstd::JsonSerde<Rect>::to_json(ext::geometry::Rect const& box) {
    return json::object({
        {"min", JsonSerde<Point>::to_json(box.min_corner())},
        {"max", JsonSerde<Point>::to_json(box.max_corner())},
    });
}

Size hstd::JsonSerde<Size>::from_json(json const& j) {
    return Size(
        j.contains("width") ? j["width"].get<float>() : -1,
        j.contains("height") ? j["height"].get<float>() : -1);
}

json hstd::JsonSerde<Size>::to_json(ext::geometry::Size const& size) {
    return json::object(
        {{"width", size.width()}, {"height", size.height()}});
}

Point hstd::JsonSerde<Point>::from_json(json const& j) {
    return Point(
        j.contains("x") ? j["x"].get<float>() : -1,
        j.contains("y") ? j["y"].get<float>() : -1);
}

json hstd::JsonSerde<Point>::to_json(ext::geometry::Point const& point) {
    return json::object({{"x", point.x()}, {"y", point.y()}});
}

Path& Path::addPolyline(std::vector<Point> const& points) {
    if (points.empty()) { return *this; }

    moveTo(points.front());
    for (std::size_t i = 1; i < points.size(); ++i) { lineTo(points[i]); }
    return *this;
}

Point Path::currentPosition() const {
    Point current{0, 0};
    Point subpathStart{0, 0};
    bool  haveCurrent = false;

    for (auto const& cmd : commands) {
        switch (cmd.type) {
            case CommandType::MoveTo:
                current      = cmd.p1;
                subpathStart = cmd.p1;
                haveCurrent  = true;
                break;

            case CommandType::LineTo:
                current     = cmd.p1;
                haveCurrent = true;
                break;

            case CommandType::QuadTo:
                current     = cmd.p2;
                haveCurrent = true;
                break;

            case CommandType::CubicTo:
                current     = cmd.p3;
                haveCurrent = true;
                break;

            case CommandType::CloseSubpath:
                if (haveCurrent) { current = subpathStart; }
                break;
        }
    }

    return current;
}
