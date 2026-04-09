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
