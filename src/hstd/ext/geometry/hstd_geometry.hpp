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

struct Point : public bg::model::d2::point_xy<double> {
    using bg::model::d2::point_xy<double>::point_xy;

    Point& operator+=(Point const& other) {
        this->x(this->x() + other.x());
        this->y(this->y() + other.y());
        return *this;
    }

    Point& operator-=(Point const& other) {
        this->x(this->x() - other.x());
        this->y(this->y() - other.y());
        return *this;
    }

    Point& operator*=(double scalar) {
        this->x(this->x() * scalar);
        this->y(this->y() * scalar);
        return *this;
    }

    Point& operator/=(double scalar) {
        this->x(this->x() / scalar);
        this->y(this->y() / scalar);
        return *this;
    }

    Point operator-() const { return Point(-this->x(), -this->y()); }

    double dot(Point const& other) const {
        return this->x() * other.x() + this->y() * other.y();
    }

    double cross(Point const& other) const {
        return this->x() * other.y() - this->y() * other.x();
    }

    double squared_length() const {
        return this->x() * this->x() + this->y() * this->y();
    }

    double length() const { return std::sqrt(squared_length()); }

    friend Point operator+(Point lhs, Point const& rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Point operator-(Point lhs, Point const& rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend Point operator*(Point lhs, double scalar) {
        lhs *= scalar;
        return lhs;
    }

    friend Point operator*(double scalar, Point rhs) {
        rhs *= scalar;
        return rhs;
    }

    friend Point operator/(Point lhs, double scalar) {
        lhs /= scalar;
        return lhs;
    }

    friend bool operator==(Point const& a, Point const& b) {
        return a.x() == b.x() && a.y() == b.y();
    }

    friend bool operator!=(Point const& a, Point const& b) {
        return !(a == b);
    }
};


struct Rect;
} // namespace hstd::ext::geometry

namespace boost::geometry::traits {

template <>
struct tag<hstd::ext::geometry::Rect> {
    using type = box_tag;
};

template <>
struct point_type<hstd::ext::geometry::Rect> {
    using type = hstd::ext::geometry::Point;
};


template <std::size_t Corner, std::size_t Dimension>
struct indexed_access<hstd::ext::geometry::Rect, Corner, Dimension>
    : indexed_access<
          model::box<hstd::ext::geometry::Point>,
          Corner,
          Dimension> {};

template <>
struct tag<hstd::ext::geometry::Point> {
    using type = point_tag;
};

template <>
struct coordinate_type<hstd::ext::geometry::Point> {
    using type = double;
};

template <>
struct coordinate_system<hstd::ext::geometry::Point> {
    using type = boost::geometry::cs::cartesian;
};

template <>
struct dimension<hstd::ext::geometry::Point> : boost::mpl::int_<2> {};

template <>
struct access<hstd::ext::geometry::Point, 0> {
    static double get(hstd::ext::geometry::Point const& p) {
        return p.x();
    }
    static void set(hstd::ext::geometry::Point& p, double const& value) {
        p.x(value);
    }
};

template <>
struct access<hstd::ext::geometry::Point, 1> {
    static double get(hstd::ext::geometry::Point const& p) {
        return p.y();
    }
    static void set(hstd::ext::geometry::Point& p, double const& value) {
        p.y(value);
    }
};

} // namespace boost::geometry::traits

namespace hstd::ext::geometry {

struct Polygon : public bg::model::polygon<Point> {
    using base_t = bg::model::polygon<Point>;
    using base_t::base_t;

    auto begin() const { return base_t::outer().begin(); }
    auto end() const { return base_t::outer().end(); }
    auto begin() { return base_t::outer().begin(); }
    auto end() { return base_t::outer().end(); }

    void push_back(Point const& p) { bg::append(*this, p); }

    Polygon& operator*=(double factor) {
        bg::for_each_point(*this, [factor](Point& p) {
            bg::set<0>(p, bg::get<0>(p) * factor);
            bg::set<1>(p, bg::get<1>(p) * factor);
        });
        return *this;
    }

    Polygon& operator/=(double factor) {
        return (*this *= (1.0 / factor));
    }

    Polygon& operator+=(Point const& delta) {
        const double dx = bg::get<0>(delta);
        const double dy = bg::get<1>(delta);

        bg::for_each_point(*this, [dx, dy](Point& p) {
            bg::set<0>(p, bg::get<0>(p) + dx);
            bg::set<1>(p, bg::get<1>(p) + dy);
        });
        return *this;
    }

    Polygon& operator-=(Point const& delta) {
        const double dx = bg::get<0>(delta);
        const double dy = bg::get<1>(delta);

        bg::for_each_point(*this, [dx, dy](Point& p) {
            bg::set<0>(p, bg::get<0>(p) - dx);
            bg::set<1>(p, bg::get<1>(p) - dy);
        });
        return *this;
    }

    Polygon operator*(double factor) const {
        Polygon copy = *this;
        copy *= factor;
        return copy;
    }

    Polygon operator/(double factor) const {
        Polygon copy = *this;
        copy /= factor;
        return copy;
    }

    Polygon operator+(Point const& delta) const {
        Polygon copy = *this;
        copy += delta;
        return copy;
    }

    Polygon operator-(Point const& delta) const {
        Polygon copy = *this;
        copy -= delta;
        return copy;
    }
};


} // namespace hstd::ext::geometry

namespace boost::geometry::traits {
template <>
struct tag<hstd::ext::geometry::Polygon> {
    using type = polygon_tag;
};

template <>
struct ring_const_type<hstd::ext::geometry::Polygon> {
    using type = hstd::ext::geometry::Polygon::ring_type const&;
};

template <>
struct ring_mutable_type<hstd::ext::geometry::Polygon> {
    using type = hstd::ext::geometry::Polygon::ring_type&;
};

template <>
struct interior_const_type<hstd::ext::geometry::Polygon> {
    using type = hstd::ext::geometry::Polygon::inner_container_type const&;
};

template <>
struct interior_mutable_type<hstd::ext::geometry::Polygon> {
    using type = hstd::ext::geometry::Polygon::inner_container_type&;
};

template <>
struct exterior_ring<hstd::ext::geometry::Polygon> {
    static hstd::ext::geometry::Polygon::ring_type& get(
        hstd::ext::geometry::Polygon& poly) {
        return poly.outer();
    }

    static hstd::ext::geometry::Polygon::ring_type const& get(
        hstd::ext::geometry::Polygon const& poly) {
        return poly.outer();
    }
};

template <>
struct interior_rings<hstd::ext::geometry::Polygon> {
    static hstd::ext::geometry::Polygon::inner_container_type& get(
        hstd::ext::geometry::Polygon& poly) {
        return poly.inners();
    }

    static hstd::ext::geometry::Polygon::inner_container_type const& get(
        hstd::ext::geometry::Polygon const& poly) {
        return poly.inners();
    }
};
} // namespace boost::geometry::traits

namespace hstd::ext::geometry {

struct Rect : bg::model::box<Point> {
    using box = bg::model::box<Point>;
    using box::box;

    Rect() : box(Point(0, 0), Point(0, 0)) {}
    Rect(double x, double y, double w, double h)
        : box(Point(x, y), Point(x + w, y + h)) {}

    static Rect FromCenterWH(Point const& center, double w, double h) {
        return Rect(center.x() - w / 2, center.y() - h / 2, w, h);
    }

    double min_x() const { return bg::get<bg::min_corner, 0>(*this); }
    double max_x() const { return bg::get<bg::max_corner, 0>(*this); }
    double min_y() const { return bg::get<bg::min_corner, 1>(*this); }
    double max_y() const { return bg::get<bg::max_corner, 1>(*this); }

    double x() const { return bg::get<bg::min_corner, 0>(*this); }
    double y() const { return bg::get<bg::min_corner, 1>(*this); }
    double width() const {
        return bg::get<bg::max_corner, 0>(*this)
             - bg::get<bg::min_corner, 0>(*this);
    }
    double height() const {
        return bg::get<bg::max_corner, 1>(*this)
             - bg::get<bg::min_corner, 1>(*this);
    }

    Rect operator/(double other) const {
        return Rect(
            x() / other, y() / other, width() / other, height() / other);
    }

    Rect operator*(double other) const {
        return Rect(
            x() * other, y() * other, width() * other, height() * other);
    }
};
} // namespace hstd::ext::geometry

namespace boost::geometry::traits {


template <std::size_t Dimension>
struct indexed_access<hstd::ext::geometry::Rect, min_corner, Dimension> {
    static double get(hstd::ext::geometry::Rect const& b) {
        return boost::geometry::get<min_corner, Dimension>(
            static_cast<hstd::ext::geometry::Rect::box const&>(b));
    }

    static void set(hstd::ext::geometry::Rect& b, double const& value) {
        boost::geometry::set<min_corner, Dimension>(
            static_cast<hstd::ext::geometry::Rect::box&>(b), value);
    }
};

template <std::size_t Dimension>
struct indexed_access<hstd::ext::geometry::Rect, max_corner, Dimension> {
    static double get(hstd::ext::geometry::Rect const& b) {
        return boost::geometry::get<max_corner, Dimension>(
            static_cast<hstd::ext::geometry::Rect::box const&>(b));
    }

    static void set(hstd::ext::geometry::Rect& b, double const& value) {
        boost::geometry::set<max_corner, Dimension>(
            static_cast<hstd::ext::geometry::Rect::box&>(b), value);
    }
};

} // namespace boost::geometry::traits


namespace hstd::ext::geometry {

struct Size : public Point {
    using Point::Point;
    double width() const { return this->x(); }
    double height() const { return this->y(); }

    Size operator/(double other) const {
        return Size(x() / other, y() / other);
    }

    Size operator*(double other) const {
        return Size(x() * other, y() * other);
    }
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

  private:
    template <typename Fn>
    static void forEachUsedPoint(Command& cmd, Fn&& fn) {
        switch (cmd.type) {
            case CommandType::MoveTo:
            case CommandType::LineTo: fn(cmd.p1); break;
            case CommandType::QuadTo:
                fn(cmd.p1);
                fn(cmd.p2);
                break;
            case CommandType::CubicTo:
                fn(cmd.p1);
                fn(cmd.p2);
                fn(cmd.p3);
                break;
            case CommandType::CloseSubpath: break;
        }
    }

  public:
    Path operator*(double v) const {
        Path out = *this;
        for (auto& cmd : out.commands) {
            forEachUsedPoint(cmd, [&](Point& p) { p *= v; });
        }
        return out;
    }

    Path operator/(double v) const {
        Path out = *this;
        for (auto& cmd : out.commands) {
            forEachUsedPoint(cmd, [&](Point& p) { p /= v; });
        }
        return out;
    }

    Path operator+(Point const& v) const {
        Path out = *this;
        for (auto& cmd : out.commands) {
            forEachUsedPoint(cmd, [&](Point& p) { p += v; });
        }
        return out;
    }

    Path operator-(Point const& v) const {
        Path out = *this;
        for (auto& cmd : out.commands) {
            forEachUsedPoint(cmd, [&](Point& p) { p -= v; });
        }
        return out;
    }


    DESC_FIELDS(Path, (commands));

    bool empty() const { return commands.empty(); }

    Path& moveTo(Point const& to) {
        commands.push_back(Command::moveTo(to));
        return *this;
    }

    Path& moveTo(double x, double y) { return moveTo(Point{x, y}); }

    Path& lineTo(Point const& to) {
        commands.push_back(Command::lineTo(to));
        return *this;
    }

    Path& lineTo(double x, double y) { return lineTo(Point{x, y}); }

    Path& quadTo(Point const& control, Point const& to) {
        commands.push_back(Command::quadTo(control, to));
        return *this;
    }

    Path& quadTo(double cx, double cy, double x, double y) {
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
        double c1x,
        double c1y,
        double c2x,
        double c2y,
        double x,
        double y) {
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

template <>
struct JsonSerde<hstd::ext::geometry::Polygon> {
    static json to_json(hstd::ext::geometry::Polygon const& box);
    static hstd::ext::geometry::Polygon from_json(json const& j);
};

} // namespace hstd
