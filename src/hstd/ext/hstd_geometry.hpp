#pragma once

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <hstd/stdlib/Formatter.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/JsonUse.hpp>
#include <vector>
#include <hstd/system/reflection.hpp>
#include <hstd/system/macros.hpp>


namespace hstd::ext::geometry {
namespace bg = boost::geometry;

using Point = bg::model::d2::point_xy<float>;

struct Rect;
} // namespace hstd::ext::geometry

namespace boost::geometry::traits {

template <>
struct tag<hstd::ext::geometry::Rect>
    : tag<model::box<hstd::ext::geometry::Point>> {};

template <>
struct point_type<hstd::ext::geometry::Rect>
    : point_type<model::box<hstd::ext::geometry::Point>> {};

template <std::size_t Corner, std::size_t Dimension>
struct indexed_access<hstd::ext::geometry::Rect, Corner, Dimension>
    : indexed_access<
          model::box<hstd::ext::geometry::Point>,
          Corner,
          Dimension> {};

} // namespace boost::geometry::traits

namespace hstd::ext::geometry {

struct Rect : bg::model::box<Point> {
    using box = bg::model::box<Point>;
    using box::box;

    Rect() : box(Point(0, 0), Point(0, 0)) {}
    Rect(float x, float y, float w, float h)
        : box(Point(x, y), Point(x + w, y + h)) {}

    float x() const { return bg::get<bg::min_corner, 0>(*this); }
    float y() const { return bg::get<bg::min_corner, 1>(*this); }
    float width() const {
        return bg::get<bg::max_corner, 0>(*this)
             - bg::get<bg::min_corner, 0>(*this);
    }
    float height() const {
        return bg::get<bg::max_corner, 1>(*this)
             - bg::get<bg::min_corner, 1>(*this);
    }
};

} // namespace hstd::ext::geometry


namespace hstd::ext::geometry {

struct Size : public Point {
    using Point::Point;
    float width() const { return this->x(); }
    float height() const { return this->y(); }
};

struct Path {
    DECL_DESCRIBED_ENUM(
        CommandType,
        MoveTo,
        LineTo,
        QuadTo,
        CubicTo,
        CloseSubpath);

    struct Command {
        CommandType type;
        Point       p1;
        Point       p2;
        Point       p3;

        DESC_FIELDS(Command, (type, p1, p2, p3));

        static Command moveTo(Point const& to) {
            return Command{.type = CommandType::MoveTo, .p1 = to};
        }

        static Command lineTo(Point const& to) {
            return Command{.type = CommandType::LineTo, .p1 = to};
        }

        static Command quadTo(Point const& control, Point const& to) {
            return Command{
                .type = CommandType::QuadTo,
                .p1   = control,
                .p2   = to,
            };
        }

        static Command cubicTo(
            Point const& control1,
            Point const& control2,
            Point const& to) {
            return Command{
                .type = CommandType::CubicTo,
                .p1   = control1,
                .p2   = control2,
                .p3   = to,
            };
        }

        static Command closeSubpath() {
            return Command{.type = CommandType::CloseSubpath};
        }
    };

    std::vector<Command> commands;

    DESC_FIELDS(Path, (commands));

    bool empty() const { return commands.empty(); }

    Path& moveTo(Point const& to) {
        commands.push_back(Command::moveTo(to));
        return *this;
    }

    Path& moveTo(float x, float y) { return moveTo(Point{x, y}); }

    Path& lineTo(Point const& to) {
        commands.push_back(Command::lineTo(to));
        return *this;
    }

    Path& lineTo(float x, float y) { return lineTo(Point{x, y}); }

    Path& quadTo(Point const& control, Point const& to) {
        commands.push_back(Command::quadTo(control, to));
        return *this;
    }

    Path& quadTo(float cx, float cy, float x, float y) {
        return quadTo(Point{cx, cy}, Point{x, y});
    }

    Path& cubicTo(
        Point const& control1,
        Point const& control2,
        Point const& to) {
        commands.push_back(Command::cubicTo(control1, control2, to));
        return *this;
    }

    Path& cubicTo(
        float c1x,
        float c1y,
        float c2x,
        float c2y,
        float x,
        float y) {
        return cubicTo(Point{c1x, c1y}, Point{c2x, c2y}, Point{x, y});
    }

    Path& closeSubpath() {
        commands.push_back(Command::closeSubpath());
        return *this;
    }

    Path& addPolyline(std::vector<Point> const& points);

    Point currentPosition() const;
};

} // namespace hstd::ext::geometry

template <>
struct std::formatter<hstd::ext::geometry::Path>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(hstd::ext::geometry::Path const& p, FormatContext& ctx)
        const {
        return hstd::fmt_ctx(
            hstd::fmt("Path(commands={})", p.commands.size()), ctx);
    }
};


template <>
struct std::formatter<hstd::ext::geometry::Point>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(hstd::ext::geometry::Point const& p, FormatContext& ctx)
        const {
        return hstd::fmt_ctx(
            hstd::fmt("Point(x={}, y={})", p.x(), p.y()), ctx);
    }
};

template <>
struct std::formatter<hstd::ext::geometry::Path::Command>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(
        hstd::ext::geometry::Path::Command const& cmd,
        FormatContext&                            ctx) const {
        using CommandType = hstd::ext::geometry::Path::CommandType;
        switch (cmd.type) {
            case CommandType::MoveTo:
                return hstd::fmt_ctx(
                    hstd::fmt("{}(to={})", cmd.type, cmd.p1), ctx);
            case CommandType::LineTo:
                return hstd::fmt_ctx(
                    hstd::fmt("{}(to={})", cmd.type, cmd.p1), ctx);
            case CommandType::QuadTo:
                return hstd::fmt_ctx(
                    hstd::fmt(
                        "{}(control={}, to={})", cmd.type, cmd.p1, cmd.p2),
                    ctx);
            case CommandType::CubicTo:
                return hstd::fmt_ctx(
                    hstd::fmt(
                        "{}(control1={}, control2={}, to={})",
                        cmd.type,
                        cmd.p1,
                        cmd.p2,
                        cmd.p3),
                    ctx);
            case CommandType::CloseSubpath:
                return hstd::fmt_ctx(hstd::fmt("{}()", cmd.type), ctx);
        }
    }
};

template <>
struct std::formatter<hstd::ext::geometry::Size>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(hstd::ext::geometry::Size const& p, FormatContext& ctx)
        const {
        return hstd::fmt_ctx(
            hstd::fmt("Size(width={}, height={})", p.width(), p.height()),
            ctx);
    }
};


template <>
struct std::formatter<hstd::ext::geometry::Rect>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(hstd::ext::geometry::Rect const& b, FormatContext& ctx)
        const {
        return hstd::fmt_ctx(
            hstd::fmt(
                "Box(min={}, max={})", b.min_corner(), b.max_corner()),
            ctx);
    }
};


namespace hstd {
template <>
struct JsonSerde<hstd::ext::geometry::Point> {
    static json to_json(hstd::ext::geometry::Point const& point);
    static hstd::ext::geometry::Point from_json(json const& j);
};

template <>
struct JsonSerde<hstd::ext::geometry::Size> {
    static json to_json(hstd::ext::geometry::Size const& size);
    static hstd::ext::geometry::Size from_json(json const& j);
};

template <>
struct JsonSerde<hstd::ext::geometry::Rect> {
    static json to_json(hstd::ext::geometry::Rect const& box);
    static hstd::ext::geometry::Rect from_json(json const& j);
};


} // namespace hstd
