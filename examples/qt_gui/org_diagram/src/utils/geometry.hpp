#pragma once

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <hstd/stdlib/Json.hpp>

namespace bg = boost::geometry;

using Point = bg::model::d2::point_xy<int>;

struct Size : public Point {
    using Point::Point;
    int width() const { return this->x(); }
    int height() const { return this->y(); }
};

template <>
struct std::formatter<Size> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const Size& p, FormatContext& ctx) const {
        return hstd::fmt_ctx(
            hstd::fmt("Size(width={}, height={}", p.width(), p.height()),
            ctx);
    }
};

template <>
struct std::formatter<Point> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const Point& p, FormatContext& ctx) const {
        return hstd::fmt_ctx(
            hstd::fmt("Point(x={}, y={}", p.x(), p.y()), ctx);
    }
};


namespace hstd {
template <>
struct JsonSerde<Point> {
    static json to_json(Point const& point) {
        return json::object({{"x", point.x()}, {"y", point.y()}});
    }

    static Point from_json(json const& j) {
        return Point(j["x"].get<int>(), j["y"].get<int>());
    }
};

template <>
struct JsonSerde<Size> {
    static json to_json(Size const& size) {
        return json::object(
            {{"width", size.width()}, {"height", size.height()}});
    }

    static Size from_json(json const& j) {
        return Size(j["width"].get<int>(), j["height"].get<int>());
    }
};
} // namespace hstd
