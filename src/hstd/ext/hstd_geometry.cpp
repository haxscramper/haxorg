#include "hstd_geometry.hpp"

using namespace hstd::ext::geometry;

json hstd::JsonSerde<BezierCurve>::to_json(
    ext::geometry::BezierCurve const& curve) {
    json points = json::array();
    for (auto const& point : curve.controlPoints) {
        points.push_back(JsonSerde<Point>::to_json(point));
    }
    return json::object({{"controlPoints", points}});
}

BezierCurve hstd::JsonSerde<BezierCurve>::from_json(json const& j) {
    BezierCurve curve;
    for (auto const& point : j.at("controlPoints")) {
        curve.controlPoints.push_back(JsonSerde<Point>::from_json(point));
    }
    return curve;
}

SegmentedLine hstd::JsonSerde<SegmentedLine>::from_json(json const& j) {
    SegmentedLine line;
    for (auto const& point : j) {
        line.push_back(JsonSerde<Point>::from_json(point));
    }
    return line;
}

json hstd::JsonSerde<SegmentedLine>::to_json(
    ext::geometry::SegmentedLine const& line) {
    json result = json::array();
    for (auto const& point : line) {
        result.push_back(JsonSerde<Point>::to_json(point));
    }
    return result;
}

Segment hstd::JsonSerde<Segment>::from_json(json const& j) {
    return Segment(
        JsonSerde<Point>::from_json(j.at("start")),
        JsonSerde<Point>::from_json(j.at("end")));
}

json hstd::JsonSerde<Segment>::to_json(
    ext::geometry::Segment const& segment) {
    return json::object({
        {"start", JsonSerde<Point>::to_json(segment.first)},
        {"end", JsonSerde<Point>::to_json(segment.second)},
    });
}

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
        j.contains("width") ? j["width"].get<int>() : -1,
        j.contains("height") ? j["height"].get<int>() : -1);
}

json hstd::JsonSerde<Size>::to_json(ext::geometry::Size const& size) {
    return json::object(
        {{"width", size.width()}, {"height", size.height()}});
}

Point hstd::JsonSerde<Point>::from_json(json const& j) {
    return Point(
        j.contains("x") ? j["x"].get<int>() : -1,
        j.contains("y") ? j["y"].get<int>() : -1);
}

json hstd::JsonSerde<Point>::to_json(ext::geometry::Point const& point) {
    return json::object({{"x", point.x()}, {"y", point.y()}});
}
