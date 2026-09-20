#pragma once

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <hstd_cpp_lib/stdlib/containers/Vec.hpp>
#include <hstd_cpp_lib/stdlib/formatting/Formatter.hpp>
#include <hstd_cpp_lib/stdlib/serde/Json.hpp>
#include <hstd_cpp_lib/stdlib/serde/JsonUse.hpp>
#include <hstd_cpp_lib/system/macros.hpp>
#include <hstd_cpp_lib/system/reflection.hpp>
#include <vector>


namespace hstd::ext::geometry {

struct Padding {
    double top    = 0;
    double bottom = 0;
    double left   = 0;
    double right  = 0;

    Padding(double top, double bottom, double left, double right)
        : top{top}, bottom{bottom}, left{left}, right{right} {}

    Padding(double uniform)
        : top{uniform}, bottom{uniform}, left{uniform}, right{uniform} {}

    Padding() {}

    double getTop() const { return top; }
    double getBottom() const { return bottom; }
    double getLeft() const { return left; }
    double getRight() const { return right; }
    double getWidth() const { return getLeft() + getRight(); }
    double getHeight() const { return getTop() + getBottom(); }

    Padding& setTop(double top) {
        this->top = top;
        return *this;
    }

    Padding& setBottom(double bottom) {
        this->bottom = bottom;
        return *this;
    }

    Padding& setLeft(double left) {
        this->left = left;
        return *this;
    }

    Padding& setRight(double right) {
        this->right = right;
        return *this;
    }

    DESC_FIELDS(Padding, (top, bottom, left, right));
};

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

    Point operator+(Point const& rhs) const {
        Point lhs = *this;
        lhs += rhs;
        return lhs;
    }

    Point operator-(Point const& rhs) const {
        Point lhs = *this;
        lhs -= rhs;
        return lhs;
    }

    Point operator*(double scalar) const {
        Point lhs = *this;
        lhs *= scalar;
        return lhs;
    }

    Point operator/(double scalar) const {
        Point lhs = *this;
        lhs /= scalar;
        return lhs;
    }

    bool operator==(Point const& b) const {
        return this->x() == b.x() && this->y() == b.y();
    }

    bool operator!=(Point const& b) const { return !(*this == b); }
};


struct Size : public Point {
    using Point::Point;
    double width() const { return this->x(); }
    double height() const { return this->y(); }

    Size operator/(double other) const { return Size(x() / other, y() / other); }

    Size operator*(double other) const { return Size(x() * other, y() * other); }
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
    : indexed_access<model::box<hstd::ext::geometry::Point>, Corner, Dimension> {};

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
    static double get(hstd::ext::geometry::Point const& p) { return p.x(); }
    static void   set(hstd::ext::geometry::Point& p, double const& value) { p.x(value); }
};

template <>
struct access<hstd::ext::geometry::Point, 1> {
    static double get(hstd::ext::geometry::Point const& p) { return p.y(); }
    static void   set(hstd::ext::geometry::Point& p, double const& value) { p.y(value); }
};

} // namespace boost::geometry::traits


namespace hstd::ext::geometry {


struct Path {
    DECL_DESCRIBED_ENUM(CommandType, MoveTo, LineTo, QuadTo, CubicTo, CloseSubpath);

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
    template <typename Cmd, typename Fn>
        requires std::same_as<std::remove_const_t<Cmd>, Command>
    static void forEachUsedPoint(Cmd& cmd, Fn&& fn) {
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
    static Path FromPolyline(hstd::Vec<Point> const& points) {
        Path result;
        for (int i = 0; i < points.size(); ++i) {
            if (i == 0) {
                result.moveTo(points.at(i));
            } else {
                result.lineTo(points.at(i));
            }
        }

        return result;
    }

    double lengthAsMultiline() const {
        double               res = 0;
        std::optional<Point> prev_point;
        for (auto const& cmd : commands) {
            forEachUsedPoint(cmd, [&](Point const& point) {
                if (prev_point.has_value()) {
                    res += (point - prev_point.value()).length();
                }
                prev_point = point;
            });
        }

        return res;
    }


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

    Path& lineTo(Point const& to) {
        commands.push_back(Command::lineTo(to));
        return *this;
    }

    Path& quadTo(Point const& control, Point const& to) {
        commands.push_back(Command::quadTo(control, to));
        return *this;
    }

    Path& cubicTo(Point const& control1, Point const& control2, Point const& to) {
        commands.push_back(Command::cubicTo(control1, control2, to));
        return *this;
    }


    Path& closeSubpath() {
        commands.push_back(Command::closeSubpath());
        return *this;
    }

    Path& addPolyline(std::vector<Point> const& points);

    Point currentPosition() const;
};

} // namespace hstd::ext::geometry


namespace hstd::ext::geometry {

struct Polygon : public bg::model::polygon<Point> {
    using base_t = bg::model::polygon<Point>;
    using base_t::base_t;

    auto begin() const { return base_t::outer().begin(); }
    auto end() const { return base_t::outer().end(); }
    auto begin() { return base_t::outer().begin(); }
    auto end() { return base_t::outer().end(); }

    void push_back(Point const& p) { bg::append(*this, p); }

    bool empty() const { return bg::is_empty(*this); }

    Polygon& operator*=(double factor) {
        bg::for_each_point(*this, [factor](Point& p) {
            bg::set<0>(p, bg::get<0>(p) * factor);
            bg::set<1>(p, bg::get<1>(p) * factor);
        });
        return *this;
    }

    Polygon& operator/=(double factor) { return (*this *= (1.0 / factor)); }

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
    Rect(Point const& min, Point const& max) : box(min, max) {}


    Rect withOuterPadding(Padding const& pad) const {
        return Rect{
            x() - pad.getLeft(),
            y() - pad.getTop(),
            width() + pad.getLeft() + pad.getRight(),
            height() + pad.getTop() + pad.getBottom()};
    }

    Rect withInnerPadding(Padding const& pad) const {
        return Rect{
            x() + pad.getLeft(),
            y() + pad.getTop(),
            width() - pad.getLeft() - pad.getRight(),
            height() - pad.getTop() - pad.getBottom()};
    }

    static Rect FromCenterWH(Point const& center, double w, double h) {
        return Rect(center.x() - w / 2, center.y() - h / 2, w, h);
    }

    static Rect FromSize(Size const& s) { return Rect(0, 0, s.width(), s.height()); }

    static Rect FromUpperLeftWH(Point const& ul, double w, double h) {
        return Rect(ul.x(), ul.y(), w, h);
    }

    static Rect FromUpperLeftWH(double x, double y, double w, double h) {
        return Rect(x, y, w, h);
    }

    double min_x() const { return bg::get<bg::min_corner, 0>(*this); }
    double max_x() const { return bg::get<bg::max_corner, 0>(*this); }
    double min_y() const { return bg::get<bg::min_corner, 1>(*this); }
    double max_y() const { return bg::get<bg::max_corner, 1>(*this); }
    double x() const { return bg::get<bg::min_corner, 0>(*this); }
    double y() const { return bg::get<bg::min_corner, 1>(*this); }
    double center_x() const { return x() + width() / 2; }
    double center_y() const { return y() + height() / 2; }

    Point upper_left() const { return Point(min_x(), min_y()); }
    Point lower_right() const { return Point(max_x(), max_y()); }
    Point center() const { return Point{center_x(), center_y()}; }

    Rect move(Point const& other) const {
        return Rect::FromUpperLeftWH(this->upper_left() + other, width(), height());
    }


    double width() const {
        return bg::get<bg::max_corner, 0>(*this) - bg::get<bg::min_corner, 0>(*this);
    }

    double height() const {
        return bg::get<bg::max_corner, 1>(*this) - bg::get<bg::min_corner, 1>(*this);
    }

    Size size() const { return Size{width(), height()}; }

    Rect operator/(double other) const {
        return Rect(x() / other, y() / other, width() / other, height() / other);
    }

    Rect operator+(Point const& p) const {
        return Rect(x() + p.x(), y() + p.y(), width(), height());
    }

    Rect operator*(double other) const {
        return Rect(x() * other, y() * other, width() * other, height() * other);
    }

    static Rect FromCornerPoints(
        double _min_x,
        double _max_x,
        double _min_y,
        double _max_y) {
        return Rect(_min_x, _min_y, _max_x - _min_x, _max_y - _min_y);
    }

    /// \brief create rectangle from the maximum double numeric limits.
    /// Useful for the `extend()` later, as a starting rectangle shape.
    static Rect FromLimitBoundaries() {
        return FromCornerPoints(
            std::numeric_limits<double>::max(),
            std::numeric_limits<double>::lowest(),
            std::numeric_limits<double>::max(),
            std::numeric_limits<double>::lowest());
    }


    inline void extend(Point const& point) {
        int _min_x = std::min(min_x(), point.x());
        int _max_x = std::max(max_x(), point.x());
        int _min_y = std::min(min_y(), point.y());
        int _max_y = std::max(max_y(), point.y());
        *this      = Rect(_min_x, _min_y, _max_x - _min_x, _max_y - _min_y);
    }

    inline void extend(Rect const& other) {
        int _min_x = std::min(min_x(), other.min_x());
        int _max_x = std::max(max_x(), other.max_x());
        int _min_y = std::min(min_y(), other.min_y());
        int _max_y = std::max(max_y(), other.max_y());
        *this      = Rect(_min_x, _min_y, _max_x - _min_x, _max_y - _min_y);
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

namespace hstd::ext::geometry::tagged {

template <typename T>
concept IsGeometryTag = requires {
    requires T::is_tagged_geometry_tag;
    requires std::same_as<decltype(T::is_tagged_geometry_tag), const bool>;
};

template <IsGeometryTag Tag>
struct TaggedScalar;

template <IsGeometryTag Tag>
struct TaggedRect;

template <IsGeometryTag Tag>
struct TaggedPadding;

template <IsGeometryTag Tag>
struct TaggedPoint;

template <IsGeometryTag SourceTag, IsGeometryTag TargetTag>
struct TaggedValueConverter;

template <IsGeometryTag Tag>
struct TaggedPath;

template <IsGeometryTag Tag>
struct TaggedPolygon;


template <IsGeometryTag Tag>
struct TaggedSize;

template <IsGeometryTag SourceTag, IsGeometryTag TargetTag>
struct TaggedValueConverterBase {
    using CONV  = TaggedValueConverter<SourceTag, TargetTag>;
    using POINT = TaggedPoint<SourceTag>;
    static TaggedRect<TargetTag> convert(TaggedRect<SourceTag> const& s) {
        return TaggedRect<TargetTag>{
            CONV::convert(s.x()),
            CONV::convert(s.y()),
            CONV::convert(s.width()),
            CONV::convert(s.height()),
        };
    }

    static TaggedPadding<TargetTag> convert(TaggedPadding<SourceTag> const& s) {
        return TaggedPadding<TargetTag>{
            CONV::convert(s.getTop()),
            CONV::convert(s.getBottom()),
            CONV::convert(s.getLeft()),
            CONV::convert(s.getRight()),
        };
    }

    static TaggedPoint<TargetTag> convert(POINT const& s) {
        return TaggedPoint<TargetTag>{
            CONV::convert(s.x()),
            CONV::convert(s.y()),
        };
    }

    static TaggedPoint<TargetTag> convert(TaggedSize<SourceTag> const& s) {
        return TaggedPoint<TargetTag>{
            CONV::convert(s.width()),
            CONV::convert(s.height()),
        };
    }


    static TaggedPolygon<TargetTag> convert(TaggedPolygon<SourceTag> const& s) {
        TaggedPolygon<TargetTag> result;

        for (auto const& p : s.getPoints()) { result.push_back(CONV::convert(p)); }

        return result;
    }

    static TaggedPath<TargetTag> convert(TaggedPath<SourceTag> const& s) {
        TaggedPath<TargetTag> result;
        for (auto const& cmd : s.getCommands()) {
            switch (cmd.getType()) {
                case Path::CommandType::MoveTo:
                    result.moveTo(CONV::convert(cmd.getP1()));
                    break;
                case Path::CommandType::LineTo:
                    result.lineTo(CONV::convert(cmd.getP1()));
                    break;
                case Path::CommandType::QuadTo:
                    result.quadTo(CONV::convert(cmd.getP1()), CONV::convert(cmd.getP2()));
                    break;
                case Path::CommandType::CubicTo:
                    result.cubicTo(
                        CONV::convert(cmd.getP1()),
                        CONV::convert(cmd.getP2()),
                        CONV::convert(cmd.getP3()));
                    break;
                case Path::CommandType::CloseSubpath: result.closeSubpath(); break;
            }
        }
        return result;
    }
};

template <IsGeometryTag SourceTag, IsGeometryTag TargetTag>
struct TaggedValueConverter {};

template <IsGeometryTag Tag>
struct TaggedScalar {
  private:
    double value;

  public:
    TaggedScalar() {}
    explicit TaggedScalar(double value) : value{value} {}
    explicit TaggedScalar(int value) : value{static_cast<double>(value)} {}

    using TS = TaggedScalar<Tag>;

    // TS operator/(TS other) const { return TS{value / other.value}; }
    TS operator-(TS other) const { return TS{value - other.value}; }
    TS operator-() const { return TS{-value}; }
    TS operator+(TS other) const { return TS{value + other.value}; }
    // TS operator*(TS other) const { return TS{value * other.value}; }

    // TS& operator/=(double other) {
    //     value /= other;
    //     return *this;
    // }

    TS& operator-=(TS other) {
        value -= other.value;
        return *this;
    }

    TS& operator+=(TS other) {
        value += other.value;
        return *this;
    }

    // TS& operator*=(TS other) {
    //     value *= other.value;
    //     return *this;
    // }

    TS     round() const { return TS{std::round(value)}; }
    double getUnsizedValue() const { return value; }

    template <IsGeometryTag TagOther>
    TaggedScalar<TagOther> toOtherTag() const {
        return TaggedValueConverter<Tag, TagOther>::convert(*this);
    }
};

template <IsGeometryTag Tag>
struct TaggedSize : private hstd::ext::geometry::Size {
    using TS   = TaggedScalar<Tag>;
    using THIS = TaggedSize<Tag>;
    using BASE = hstd::ext::geometry::Size;

    TaggedSize()                  = default;
    TaggedSize(THIS const& other) = default;

    static THIS FromValue(double x, double y) { return THIS{TS{x}, TS{y}}; }

    hstd::ext::geometry::Size getUnsizedValue() const { return *this; }

    explicit TaggedSize(hstd::ext::geometry::Size const& base)
        : hstd::ext::geometry::Size{base} {}

    explicit TaggedSize(TS x, TS y)
        : hstd::ext::geometry::Size{x.getUnsizedValue(), y.getUnsizedValue()} {}

    template <IsGeometryTag TagOther>
    TaggedSize<TagOther> toOtherTag() const {
        return TaggedValueConverter<Tag, TagOther>::convert(*this);
    }

    TS width() const { return TS{BASE::width()}; }
    TS height() const { return TS{BASE::height()}; }
};


template <IsGeometryTag Tag>
struct TaggedPoint : private hstd::ext::geometry::Point {
    using TS   = TaggedScalar<Tag>;
    using THIS = TaggedPoint<Tag>;
    using BASE = hstd::ext::geometry::Point;

    TaggedPoint()                  = default;
    TaggedPoint(THIS const& other) = default;

    hstd::ext::geometry::Point getUnsizedValue() const { return *this; }

    explicit TaggedPoint(hstd::ext::geometry::Point const& base)
        : hstd::ext::geometry::Point{base} {}

    static THIS FromValue(double x, double y) { return THIS{TS{x}, TS{y}}; }

    explicit TaggedPoint(TS x, TS y)
        : hstd::ext::geometry::Point{x.getUnsizedValue(), y.getUnsizedValue()} {}

    template <IsGeometryTag TagOther>
    TaggedPoint<TagOther> toOtherTag() const {
        return TaggedValueConverter<Tag, TagOther>::convert(*this);
    }

    TS   x() const { return TS{BASE::x()}; }
    TS   y() const { return TS{BASE::y()}; }
    THIS operator-() const { return THIS{BASE::operator-()}; }

    THIS operator-(THIS const& other) const { return THIS{BASE::operator-(other)}; }
    THIS operator+(THIS const& other) const { return THIS{BASE::operator+(other)}; }

    THIS& operator-=(THIS const& other) {
        BASE::operator-=(other);
        return *this;
    }

    THIS& operator+=(THIS const& other) {
        BASE::operator+=(other);
        return *this;
    }

    TS length() const { return TS{BASE::length()}; }
};

template <IsGeometryTag Tag>
struct TaggedPath : private hstd::ext::geometry::Path {
    using TS   = TaggedScalar<Tag>;
    using TP   = TaggedPoint<Tag>;
    using THIS = TaggedPath<Tag>;
    using BASE = hstd::ext::geometry::Path;

    TaggedPath()                  = default;
    TaggedPath(THIS const& other) = default;

    hstd::ext::geometry::Path getUnsizedValue() const { return *this; }

    explicit TaggedPath(hstd::ext::geometry::Path const& base)
        : hstd::ext::geometry::Path{base} {}

    explicit TaggedPath(TS x, TS y)
        : hstd::ext::geometry::Path{x.getUnsizedValue(), y.getUnsizedValue()} {}

    template <IsGeometryTag TagOther>
    TaggedPath<TagOther> toOtherTag() const {
        return TaggedValueConverter<Tag, TagOther>::convert(*this);
    }

    THIS operator-(TP const& p) const {
        return THIS{BASE::operator-(p.getUnsizedValue())};
    }

    THIS operator+(TP const& p) const {
        return THIS{BASE::operator+(p.getUnsizedValue())};
    }

    struct CommandRef {
        BASE::Command const* ref;
        CommandType          getType() const { return ref->type; }
        TP                   getP1() const { return TP{ref->p1}; }
        TP                   getP2() const { return TP{ref->p2}; }
        TP                   getP3() const { return TP{ref->p3}; }
    };

    std::vector<CommandRef> getCommands() const {
        std::vector<CommandRef> res;
        for (int i = 0; i < commands.size(); ++i) {
            res.push_back(CommandRef{&commands.at(i)});
        }
        return res;
    }

    THIS& closeSubpath() {
        BASE::closeSubpath();
        return *this;
    }

    THIS& lineTo(TP const& to) {
        BASE::lineTo(to.getUnsizedValue());
        return *this;
    }

    THIS& moveTo(TP const& to) {
        BASE::moveTo(to.getUnsizedValue());
        return *this;
    }

    THIS& quadTo(TP const& control, TP const& to) {
        BASE::quadTo(control.getUnsizedValue(), to.getUnsizedValue());
        return *this;
    }

    THIS& cubicTo(TP const& control1, TP const& control2, TP const& to) {
        BASE::cubicTo(
            control1.getUnsizedValue(), control2.getUnsizedValue(), to.getUnsizedValue());
        return *this;
    }

    bool empty() const { return BASE::empty(); }
};

template <IsGeometryTag Tag>
struct TaggedPolygon : private hstd::ext::geometry::Polygon {
    using TS   = TaggedScalar<Tag>;
    using TP   = TaggedPoint<Tag>;
    using THIS = TaggedPolygon<Tag>;
    using BASE = hstd::ext::geometry::Polygon;

    TaggedPolygon()                  = default;
    TaggedPolygon(THIS const& other) = default;

    hstd::ext::geometry::Polygon getUnsizedValue() const { return *this; }

    explicit TaggedPolygon(hstd::ext::geometry::Polygon const& base)
        : hstd::ext::geometry::Polygon{base} {}

    explicit TaggedPolygon(TS x, TS y)
        : hstd::ext::geometry::Polygon{x.getUnsizedValue(), y.getUnsizedValue()} {}

    template <typename TagOther>
    TaggedPolygon<TagOther> toOtherTag() const {
        return TaggedValueConverter<Tag, TagOther>::convert(*this);
    }

    bool empty() const { return BASE::empty(); }

    void push_back(TP const& p) { BASE::push_back(p.getUnsizedValue()); }

    hstd::Vec<TP> getPoints() const {
        hstd::Vec<TP> res;
        for (auto const& value : *this) { res.push_back(TP{value}); }
        return res;
    }
};


template <IsGeometryTag Tag>
struct TaggedRect : private hstd::ext::geometry::Rect {
    using TS   = TaggedScalar<Tag>;
    using TP   = TaggedPoint<Tag>;
    using THIS = TaggedRect<Tag>;
    using BASE = hstd::ext::geometry::Rect;

    TaggedRect(THIS const& other) = default;

    hstd::ext::geometry::Rect getUnsizedValue() const { return *this; }

    explicit TaggedRect(hstd::ext::geometry::Rect const& base)
        : hstd::ext::geometry::Rect{base} {}

    explicit TaggedRect(TS x, TS y, TS width, TS height)
        : hstd::ext::geometry::Rect{
              x.getUnsizedValue(),
              y.getUnsizedValue(),
              width.getUnsizedValue(),
              height.getUnsizedValue()} {}

    template <IsGeometryTag TagOther>
    TaggedRect<TagOther> toOtherTag() const {
        return TaggedValueConverter<Tag, TagOther>::convert(*this);
    }

    TS min_x() const { return TS{BASE::min_x()}; }
    TS max_x() const { return TS{BASE::max_x()}; }
    TS min_y() const { return TS{BASE::min_y()}; }
    TS max_y() const { return TS{BASE::max_y()}; }
    TS x() const { return TS{BASE::x()}; }
    TS y() const { return TS{BASE::y()}; }
    TS center_x() const { return TS{BASE::center_x()}; }
    TS center_y() const { return TS{BASE::center_y()}; }
    TS width() const { return TS{BASE::width()}; }
    TS height() const { return TS{BASE::height()}; }

    TP upper_left() const { return TP{BASE::upper_left()}; }
    TP lower_right() const { return TP{BASE::lower_right()}; }
    TP center() const { return TP{BASE::center()}; }

    THIS move(TP const& other) const { return THIS{BASE::move(other.getUnsizedValue())}; }
};

template <IsGeometryTag Tag>
struct TaggedPadding : private hstd::ext::geometry::Padding {
    using TS   = TaggedScalar<Tag>;
    using THIS = TaggedPadding<Tag>;
    using BASE = hstd::ext::geometry::Padding;

    TaggedPadding(THIS const& other) = default;

    hstd::ext::geometry::Padding getUnsizedValue() const { return *this; }

    explicit TaggedPadding(hstd::ext::geometry::Padding const& base)
        : hstd::ext::geometry::Padding{base} {}

    explicit TaggedPadding(TS top, TS bottom, TS left, TS right)
        : hstd::ext::geometry::Padding{
              top.getUnsizedValue(),
              bottom.getUnsizedValue(),
              left.getUnsizedValue(),
              right.getUnsizedValue()} {}

    TS getTop() const { return TS{top}; }
    TS getBottom() const { return TS{bottom}; }
    TS getLeft() const { return TS{left}; }
    TS getRight() const { return TS{right}; }
    TS getWidth() const { return getLeft() + getRight(); }
    TS getHeight() const { return getTop() + getBottom(); }

    template <typename TagOther>
    TaggedPadding<TagOther> toOtherTag() const {
        return TaggedValueConverter<Tag, TagOther>::convert(*this);
    }
};

} // namespace hstd::ext::geometry::tagged

template <typename Tag>
struct fmt::formatter<hstd::ext::geometry::tagged::TaggedRect<Tag>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(
        hstd::ext::geometry::tagged::TaggedRect<Tag> const& p,
        fmt::format_context&                                ctx) const {
        return hstd::fmt_ctx(p.getUnsizedValue(), ctx);
    }
};

template <typename Tag>
struct fmt::formatter<hstd::ext::geometry::tagged::TaggedPolygon<Tag>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(
        hstd::ext::geometry::tagged::TaggedPolygon<Tag> const& p,
        fmt::format_context&                                   ctx) const {
        return hstd::fmt_ctx(p.getUnsizedValue(), ctx);
    }
};

template <typename Tag>
struct fmt::formatter<hstd::ext::geometry::tagged::TaggedScalar<Tag>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(
        hstd::ext::geometry::tagged::TaggedScalar<Tag> const& p,
        fmt::format_context&                                  ctx) const {
        return hstd::fmt_ctx(p.getUnsizedValue(), ctx);
    }
};

template <typename Tag>
struct fmt::formatter<hstd::ext::geometry::tagged::TaggedPadding<Tag>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(
        hstd::ext::geometry::tagged::TaggedPadding<Tag> const& p,
        fmt::format_context&                                   ctx) const {
        return hstd::fmt_ctx(p.getUnsizedValue(), ctx);
    }
};

template <typename Tag>
struct fmt::formatter<hstd::ext::geometry::tagged::TaggedPoint<Tag>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(
        hstd::ext::geometry::tagged::TaggedPoint<Tag> const& p,
        fmt::format_context&                                 ctx) const {
        return hstd::fmt_ctx(p.getUnsizedValue(), ctx);
    }
};

template <>
struct fmt::formatter<hstd::ext::geometry::Path> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(hstd::ext::geometry::Path const& p, fmt::format_context& ctx)
        const;
};


template <>
struct fmt::formatter<hstd::ext::geometry::Point> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(hstd::ext::geometry::Point const& p, fmt::format_context& ctx)
        const;
};

template <>
struct fmt::formatter<hstd::ext::geometry::Size> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(hstd::ext::geometry::Size const& p, fmt::format_context& ctx)
        const;
};


template <>
struct fmt::formatter<hstd::ext::geometry::Rect> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(hstd::ext::geometry::Rect const& b, fmt::format_context& ctx)
        const;
};

template <>
struct fmt::formatter<hstd::ext::geometry::Polygon> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(hstd::ext::geometry::Polygon const& b, fmt::format_context& ctx)
        const;
};

namespace hstd {
template <>
struct JsonSerde<hstd::ext::geometry::Point> {
    static json                       to_json(hstd::ext::geometry::Point const& point);
    static hstd::ext::geometry::Point from_json(json const& j);
};

template <>
struct JsonSerde<hstd::ext::geometry::Size> {
    static json                      to_json(hstd::ext::geometry::Size const& size);
    static hstd::ext::geometry::Size from_json(json const& j);
};

template <>
struct JsonSerde<hstd::ext::geometry::Rect> {
    static json                      to_json(hstd::ext::geometry::Rect const& box);
    static hstd::ext::geometry::Rect from_json(json const& j);
};

template <>
struct JsonSerde<hstd::ext::geometry::Polygon> {
    static json                         to_json(hstd::ext::geometry::Polygon const& box);
    static hstd::ext::geometry::Polygon from_json(json const& j);
};

} // namespace hstd
