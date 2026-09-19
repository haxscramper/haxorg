#include "hstd_geometry.hpp"
#include <hstd/stdlib/Formatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/strutils.hpp>

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
        j.contains("width") ? j["width"].get<double>() : -1,
        j.contains("height") ? j["height"].get<double>() : -1);
}

json hstd::JsonSerde<Size>::to_json(ext::geometry::Size const& size) {
    return json::object({{"width", size.width()}, {"height", size.height()}});
}

Point hstd::JsonSerde<Point>::from_json(json const& j) {
    return Point(
        j.contains("x") ? j["x"].get<double>() : -1,
        j.contains("y") ? j["y"].get<double>() : -1);
}

json hstd::JsonSerde<Point>::to_json(ext::geometry::Point const& point) {
    return json::object({{"x", point.x()}, {"y", point.y()}});
}

Polygon hstd::JsonSerde<Polygon>::from_json(json const& j) {
    Polygon res;
    for (auto const& it : j) { res.push_back(JsonSerde<Point>::from_json(it)); }
    return res;
}

json hstd::JsonSerde<Polygon>::to_json(ext::geometry::Polygon const& point) {
    json result = json::array();
    for (auto const& p : point) { result.push_back(JsonSerde<Point>::to_json(p)); }
    return result;
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

fmt::format_context::iterator fmt::formatter<hstd::ext::geometry::Point>::format(
    hstd::ext::geometry::Point const& p,
    fmt::format_context&              ctx) const {
    return hstd::fmt_ctx(
        hstd::fmt(
            "Point({}, {})", hstd::format_number(p.x()), hstd::format_number(p.y())),
        ctx);
}
fmt::format_context::iterator fmt::formatter<hstd::ext::geometry::Size>::format(
    hstd::ext::geometry::Size const& p,
    fmt::format_context&             ctx) const {
    return hstd::fmt_ctx(
        hstd::fmt("Size(width={}, height={})", p.width(), p.height()), ctx);
}

fmt::context::iterator fmt::formatter<hstd::ext::geometry::Rect>::format(
    hstd::ext::geometry::Rect const& b,
    format_context&                  ctx) const {
    return hstd::fmt_ctx(
        hstd::fmt(
            "Rect({}, {}, {})",
            b.min_corner(),
            hstd::format_number(b.width()),
            hstd::format_number(b.height())),
        ctx);
}

hstd::fmt_iter fmt::formatter<hstd::ext::geometry::Path>::format(
    hstd::ext::geometry::Path const& p,
    fmt::format_context&             ctx) const {
    return hstd::fmt_ctx(hstd::fmt("Path(commands={})", p.commands), ctx);
}

hstd::fmt_iter fmt::formatter<hstd::ext::geometry::Polygon>::format(
    hstd::ext::geometry::Polygon const& b,
    format_context&                     ctx) const {
    return hstd::fmt_ctx(
        hstd::fmt("Polygon(points={})", hstd::Vec<Point>{b.begin(), b.end()}), ctx);
}
