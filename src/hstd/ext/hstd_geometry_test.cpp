#include <hstd/ext/hstd_geometry_test.hpp>
#include <boost/geometry/geometries/segment.hpp>

namespace hstd::ext::geometry {
namespace detail {

using Segment = bg::model::segment<Point>;

struct PathSegment {
    Segment     seg;
    std::size_t commandIndex;
    std::size_t pieceIndex;
};

static Point quadAt(
    Point const& p0,
    Point const& p1,
    Point const& p2,
    double       t) {
    double u = 1.0 - t;
    return Point(
        u * u * p0.x() + 2.0 * u * t * p1.x() + t * t * p2.x(),
        u * u * p0.y() + 2.0 * u * t * p1.y() + t * t * p2.y());
}

static Point cubicAt(
    Point const& p0,
    Point const& p1,
    Point const& p2,
    Point const& p3,
    double       t) {
    double u  = 1.0 - t;
    double uu = u * u;
    double tt = t * t;
    return Point(
        uu * u * p0.x() + 3.0 * uu * t * p1.x() + 3.0 * u * tt * p2.x()
            + tt * t * p3.x(),
        uu * u * p0.y() + 3.0 * uu * t * p1.y() + 3.0 * u * tt * p2.y()
            + tt * t * p3.y());
}

static boost::outcome_v2::result<std::vector<PathSegment>, GeometryError> flattenPath(
    Path const& path) {
    if (path.commands.empty()) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                R"(
error = path is empty
)"));
    }

    if (path.commands.front().type != Path::CommandType::MoveTo) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
error        = path must start with MoveTo
firstCommand = {}
)",
                    path.commands.front())));
    }

    constexpr int steps = 24;

    std::vector<PathSegment> segments;
    bool                     hasCurrent = false;
    Point                    current;
    Point                    subpathStart;

    for (std::size_t i = 0; i < path.commands.size(); ++i) {
        auto const& cmd = path.commands.at(i);

        if (cmd.type == Path::CommandType::MoveTo) {
            current      = cmd.p1;
            subpathStart = cmd.p1;
            hasCurrent   = true;
            continue;
        }

        if (!hasCurrent) {
            return boost::outcome_v2::failure(
                GeometryError::init(
                    hstd::fmt(
                        R"(
error        = command has no current point
commandIndex = {}
command      = {}
)",
                        i,
                        cmd)));
        }

        if (cmd.type == Path::CommandType::LineTo) {
            segments.push_back(
                PathSegment{
                    .seg          = Segment(current, cmd.p1),
                    .commandIndex = i,
                    .pieceIndex   = 0,
                });
            current = cmd.p1;
            continue;
        }

        if (cmd.type == Path::CommandType::QuadTo) {
            Point prev = current;
            for (int s = 1; s <= steps; ++s) {
                double t    = static_cast<double>(s)
                            / static_cast<double>(steps);
                Point  next = quadAt(current, cmd.p1, cmd.p2, t);
                segments.push_back(
                    PathSegment{
                        .seg          = Segment(prev, next),
                        .commandIndex = i,
                        .pieceIndex   = static_cast<std::size_t>(s),
                    });
                prev = next;
            }
            current = cmd.p2;
            continue;
        }

        if (cmd.type == Path::CommandType::CubicTo) {
            Point prev = current;
            for (int s = 1; s <= steps; ++s) {
                double t    = static_cast<double>(s)
                            / static_cast<double>(steps);
                Point  next = cubicAt(current, cmd.p1, cmd.p2, cmd.p3, t);
                segments.push_back(
                    PathSegment{
                        .seg          = Segment(prev, next),
                        .commandIndex = i,
                        .pieceIndex   = static_cast<std::size_t>(s),
                    });
                prev = next;
            }
            current = cmd.p3;
            continue;
        }

        if (cmd.type == Path::CommandType::CloseSubpath) {
            segments.push_back(
                PathSegment{
                    .seg          = Segment(current, subpathStart),
                    .commandIndex = i,
                    .pieceIndex   = 0,
                });
            current = subpathStart;
            continue;
        }
    }

    if (segments.empty()) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
error = path has no drawable segments
path  = {}
)",
                    path)));
    }

    return segments;
}

boost::outcome_v2::result<Rect, GeometryError> boundsOf(
    Rect const& value) {
    return value;
}

boost::outcome_v2::result<Rect, GeometryError> boundsOf(
    Point const& value) {
    return Rect(value.x(), value.y(), 0.0, 0.0);
}

boost::outcome_v2::result<Rect, GeometryError> boundsOf(
    Path const& value) {
    auto segs = flattenPath(value);
    if (!segs) { return boost::outcome_v2::failure(segs.error()); }

    double minX = std::numeric_limits<double>::infinity();
    double minY = std::numeric_limits<double>::infinity();
    double maxX = -std::numeric_limits<double>::infinity();
    double maxY = -std::numeric_limits<double>::infinity();

    for (auto const& it : segs.value()) {
        auto const& a = it.seg.first;
        auto const& b = it.seg.second;

        minX = std::min(minX, std::min(a.x(), b.x()));
        minY = std::min(minY, std::min(a.y(), b.y()));
        maxX = std::max(maxX, std::max(a.x(), b.x()));
        maxY = std::max(maxY, std::max(a.y(), b.y()));
    }

    return Rect(minX, minY, maxX - minX, maxY - minY);
}

GeometryCheckResult checkLeftOfBounds(
    Rect const& first,
    Rect const& second) {
    double firstRight = bg::get<bg::max_corner, 0>(first);
    double secondLeft = bg::get<bg::min_corner, 0>(second);

    if (firstRight <= secondLeft) { return boost::outcome_v2::success(); }

    return boost::outcome_v2::failure(
        GeometryError::init(
            hstd::fmt(
                R"(
check      = left-of-bounds
firstRight = {}
secondLeft = {}
first      = {}
second     = {}
)",
                firstRight,
                secondLeft,
                first,
                second)));
}

GeometryCheckResult checkRightOfBounds(
    Rect const& first,
    Rect const& second) {
    double firstLeft   = bg::get<bg::min_corner, 0>(first);
    double secondRight = bg::get<bg::max_corner, 0>(second);

    if (secondRight <= firstLeft) { return boost::outcome_v2::success(); }

    return boost::outcome_v2::failure(
        GeometryError::init(
            hstd::fmt(
                R"(
check       = right-of-bounds
firstLeft   = {}
secondRight = {}
first       = {}
second      = {}
)",
                firstLeft,
                secondRight,
                first,
                second)));
}

GeometryCheckResult checkAboveBounds(
    Rect const& first,
    Rect const& second) {
    double firstBottom = bg::get<bg::max_corner, 1>(first);
    double secondTop   = bg::get<bg::min_corner, 1>(second);

    if (firstBottom <= secondTop) { return boost::outcome_v2::success(); }

    return boost::outcome_v2::failure(
        GeometryError::init(
            hstd::fmt(
                R"(
check       = above-bounds
firstBottom = {}
secondTop   = {}
first       = {}
second      = {}
)",
                firstBottom,
                secondTop,
                first,
                second)));
}

GeometryCheckResult checkBelowBounds(
    Rect const& first,
    Rect const& second) {
    double firstTop     = bg::get<bg::min_corner, 1>(first);
    double secondBottom = bg::get<bg::max_corner, 1>(second);

    if (secondBottom <= firstTop) { return boost::outcome_v2::success(); }

    return boost::outcome_v2::failure(
        GeometryError::init(
            hstd::fmt(
                R"(
check        = below-bounds
firstTop     = {}
secondBottom = {}
first        = {}
second       = {}
)",
                firstTop,
                secondBottom,
                first,
                second)));
}

GeometryCheckResult checkFullyCoversBounds(
    Rect const& first,
    Rect const& second) {
    double firstLeft   = bg::get<bg::min_corner, 0>(first);
    double firstTop    = bg::get<bg::min_corner, 1>(first);
    double firstRight  = bg::get<bg::max_corner, 0>(first);
    double firstBottom = bg::get<bg::max_corner, 1>(first);

    double secondLeft   = bg::get<bg::min_corner, 0>(second);
    double secondTop    = bg::get<bg::min_corner, 1>(second);
    double secondRight  = bg::get<bg::max_corner, 0>(second);
    double secondBottom = bg::get<bg::max_corner, 1>(second);

    bool covers = firstLeft <= secondLeft && firstTop <= secondTop
               && secondRight <= firstRight && secondBottom <= firstBottom;

    if (covers) { return boost::outcome_v2::success(); }

    return boost::outcome_v2::failure(
        GeometryError::init(
            hstd::fmt(
                R"(
check        = fully-covers-bounds
firstLeft    = {}
firstTop     = {}
firstRight   = {}
firstBottom  = {}
secondLeft   = {}
secondTop    = {}
secondRight  = {}
secondBottom = {}
first        = {}
second       = {}
)",
                firstLeft,
                firstTop,
                firstRight,
                firstBottom,
                secondLeft,
                secondTop,
                secondRight,
                secondBottom,
                first,
                second)));
}

} // namespace detail

GeometryCheckResult checkIntersects(
    Point const& first,
    Point const& second) {
    if (first.x() == second.x() && first.y() == second.y()) {
        return boost::outcome_v2::success();
    }

    return boost::outcome_v2::failure(
        GeometryError::init(
            hstd::fmt(
                R"(
check  = point-point-intersects
first  = {}
second = {}
)",
                first,
                second)));
}

GeometryCheckResult checkIntersects(Point const& point, Rect const& rect) {
    if (bg::covered_by(point, rect)) {
        return boost::outcome_v2::success();
    }

    return boost::outcome_v2::failure(
        GeometryError::init(
            hstd::fmt(
                R"(
check = point-rect-intersects
point = {}
rect  = {}
)",
                point,
                rect)));
}

GeometryCheckResult checkIntersects(Rect const& rect, Point const& point) {
    return checkIntersects(point, rect);
}

GeometryCheckResult checkIntersects(Point const& point, Path const& path) {
    auto segs = detail::flattenPath(path);
    if (!segs) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
check  = point-path-intersects
error  = cannot flatten path
reason = {}
)",
                    segs.error().message())));
    }

    for (auto const& s : segs.value()) {
        double d = bg::distance(point, s.seg);
        if (d == 0.0) { return boost::outcome_v2::success(); }
    }

    return boost::outcome_v2::failure(
        GeometryError::init(
            hstd::fmt(
                R"(
check = point-path-intersects
point = {}
path  = {}
)",
                point,
                path)));
}

GeometryCheckResult checkIntersects(Path const& path, Point const& point) {
    return checkIntersects(point, path);
}

GeometryCheckResult checkIntersects(Rect const& rect, Path const& path) {
    auto segs = detail::flattenPath(path);
    if (!segs) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
check  = rect-path-intersects
error  = cannot flatten path
reason = {}
)",
                    segs.error().message())));
    }

    for (auto const& s : segs.value()) {
        if (bg::intersects(s.seg, rect)) {
            return boost::outcome_v2::success();
        }
    }

    return boost::outcome_v2::failure(
        GeometryError::init(
            hstd::fmt(
                R"(
check = rect-path-intersects
rect  = {}
path  = {}
)",
                rect,
                path)));
}

GeometryCheckResult checkIntersects(Path const& path, Rect const& rect) {
    return checkIntersects(rect, path);
}

GeometryCheckResult checkIntersects(
    Path const& first,
    Path const& second) {
    auto a = detail::flattenPath(first);
    if (!a) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
check  = path-path-intersects
error  = cannot flatten first path
reason = {}
)",
                    a.error().message())));
    }

    auto b = detail::flattenPath(second);
    if (!b) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
check  = path-path-intersects
error  = cannot flatten second path
reason = {}
)",
                    b.error().message())));
    }

    for (auto const& sa : a.value()) {
        for (auto const& sb : b.value()) {
            if (bg::intersects(sa.seg, sb.seg)) {
                return boost::outcome_v2::success();
            }
        }
    }

    return boost::outcome_v2::failure(
        GeometryError::init(
            hstd::fmt(
                R"(
check  = path-path-intersects
first  = {}
second = {}
)",
                first,
                second)));
}

} // namespace hstd::ext::geometry
