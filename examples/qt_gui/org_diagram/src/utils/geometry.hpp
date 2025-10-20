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
