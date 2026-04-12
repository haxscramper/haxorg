// hstd_geometry_test.cpp
#include <hstd/ext/hstd_geometry_test.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <algorithm>
#include <cmath>
#include <limits>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/stringize.hpp>

namespace hstd::ext::geometry {
namespace detail {

using Segment = bg::model::segment<Point>;

struct PathSegment {
    Segment     seg;
    std::size_t commandIndex;
    std::size_t pieceIndex;
};

constexpr int FAIL_CHECK_LABEL_WIDTH = 30;

struct FailVerbatimLine {
    std::string line;
};

struct FailVerbatimKV {
    std::string key;
    std::string value;
};

namespace detail {

inline void fail_check_append(
    std::string&            result,
    char const*             name,
    FailVerbatimLine const& v) {
    result += v.line;
    result += "\n";
}

inline void fail_check_append(
    std::string&          result,
    char const*           name,
    FailVerbatimKV const& v) {
    result += hstd::fmt(
        "{:<{}} = {}\n", v.key, FAIL_CHECK_LABEL_WIDTH, v.value);
}

template <typename T>
void fail_check_append(
    std::string& result,
    char const*  name,
    T const&     value) {
    result += hstd::fmt(
        "{:<{}} = {}\n", name, FAIL_CHECK_LABEL_WIDTH, value);
}

} // namespace detail

inline std::string fail_check_format(char const* error_name) {
    return hstd::fmt(
        "{:<{}} = {}\n", "error", FAIL_CHECK_LABEL_WIDTH, error_name);
}

template <typename... Args>
std::string fail_check_format(
    char const*                        error_name,
    std::initializer_list<const char*> names,
    Args const&... args) {
    std::string result  = fail_check_format(error_name);
    auto        name_it = names.begin();
    (detail::fail_check_append(result, *name_it++, args), ...);
    return result;
}

#define FAIL_CHECK_NAME(r, data, i, elem) BOOST_PP_STRINGIZE(elem),

#define FAIL_CHECK_VAL(r, data, i, elem) elem,

#define FAIL_CHECK_WITH_ARGS(error_name, ...)                             \
    boost::outcome_v2::failure(                                           \
        GeometryError::init(fail_check_format(                            \
            error_name,                                                   \
            {BOOST_PP_SEQ_FOR_EACH_I(                                     \
                FAIL_CHECK_NAME,                                          \
                _,                                                        \
                BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))},                  \
            BOOST_PP_SEQ_FOR_EACH_I(                                      \
                FAIL_CHECK_VAL,                                           \
                _,                                                        \
                BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))))

#define FAIL_CHECK_NO_ARGS(error_name)                                    \
    boost::outcome_v2::failure(                                           \
        GeometryError::init(fail_check_format(error_name)))

#define FAIL_CHECK_DISPATCH(error_name, ...)                              \
    BOOST_PP_IF(                                                          \
        BOOST_PP_EQUAL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), 1),           \
        FAIL_CHECK_NO_ARGS,                                               \
        FAIL_CHECK_WITH_ARGS)                                             \
    (error_name, ##__VA_ARGS__)

#define FAIL_CHECK(...) FAIL_CHECK_DISPATCH(__VA_ARGS__, )


static double rectWidth(Rect const& r) {
    return bg::get<bg::max_corner, 0>(r) - bg::get<bg::min_corner, 0>(r);
}

static double rectHeight(Rect const& r) {
    return bg::get<bg::max_corner, 1>(r) - bg::get<bg::min_corner, 1>(r);
}

static double rectArea(Rect const& r) {
    return std::max(0.0, rectWidth(r)) * std::max(0.0, rectHeight(r));
}

static double overlapLen1D(
    double aMin,
    double aMax,
    double bMin,
    double bMax) {
    return std::max(0.0, std::min(aMax, bMax) - std::max(aMin, bMin));
}

static double overlapArea(Rect const& a, Rect const& b) {
    double x = overlapLen1D(
        bg::get<bg::min_corner, 0>(a),
        bg::get<bg::max_corner, 0>(a),
        bg::get<bg::min_corner, 0>(b),
        bg::get<bg::max_corner, 0>(b));
    double y = overlapLen1D(
        bg::get<bg::min_corner, 1>(a),
        bg::get<bg::max_corner, 1>(a),
        bg::get<bg::min_corner, 1>(b),
        bg::get<bg::max_corner, 1>(b));
    return x * y;
}

static double overlapPercent(double overlap, double full) {
    if (full <= 0.0) { return 0.0; }
    return std::clamp((overlap / full) * 100.0, 0.0, 100.0);
}

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
    if (path.commands.empty()) { return FAIL_CHECK("path is empty"); }

    if (path.commands.front().type != Path::CommandType::MoveTo) {
        return boost::outcome_v2::failure(makeError(
            R"(
error        = path must start with MoveTo
firstCommand = {}
)",
            path.commands.front()));
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
            return boost::outcome_v2::failure(makeError(
                R"(
error        = command has no current point
commandIndex = {}
command      = {}
)",
                i,
                cmd));
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
        return boost::outcome_v2::failure(makeError(
            R"(
error = path has no drawable segments
path  = {}
)",
            path));
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

    return failCheck(
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
        second);
}

GeometryCheckResult checkRightOfBounds(
    Rect const& first,
    Rect const& second) {
    double firstLeft   = bg::get<bg::min_corner, 0>(first);
    double secondRight = bg::get<bg::max_corner, 0>(second);

    if (secondRight <= firstLeft) { return boost::outcome_v2::success(); }

    return failCheck(
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
        second);
}

GeometryCheckResult checkAboveBounds(
    Rect const& first,
    Rect const& second) {
    double firstBottom = bg::get<bg::max_corner, 1>(first);
    double secondTop   = bg::get<bg::min_corner, 1>(second);

    if (firstBottom <= secondTop) { return boost::outcome_v2::success(); }

    return failCheck(
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
        second);
}

GeometryCheckResult checkPartiallyAboveBounds(
    Rect const& fixed,
    Rect const& relative,
    double      maxUnderPercent) {
    if (maxUnderPercent < 0.0 || maxUnderPercent > 100.0) {
        return failCheck(
            R"(
check           = partially-above-bounds
error           = maxUnderPercent must be in [0, 100]
maxUnderPercent = {}
)",
            maxUnderPercent);
    }

    double lineY       = bg::get<bg::min_corner, 1>(fixed);
    double relativeTop = bg::get<bg::min_corner, 1>(relative);
    double relativeBot = bg::get<bg::max_corner, 1>(relative);
    double relHeight   = std::max(0.0, relativeBot - relativeTop);

    double underLen = 0.0;
    if (lineY <= relativeTop) {
        underLen = relHeight;
    } else if (relativeBot <= lineY) {
        underLen = 0.0;
    } else {
        underLen = relativeBot - lineY;
    }

    double underPercent = relHeight == 0.0
                            ? (lineY <= relativeTop ? 100.0 : 0.0)
                            : (underLen / relHeight) * 100.0;

    if (underPercent <= maxUnderPercent) {
        return boost::outcome_v2::success();
    }

    return failCheck(
        R"(
check                   = partially-above-bounds
lineY                   = {}
relativeTop             = {}
relativeBottom          = {}
relativeHeight          = {}
relativeUnderLine       = {}
relativeUnderLinePct    = {:.2f}
allowedUnderLinePctMax  = {:.2f}
fixed                   = {}
relative                = {}
)",
        lineY,
        relativeTop,
        relativeBot,
        relHeight,
        underLen,
        underPercent,
        maxUnderPercent,
        fixed,
        relative);
}

GeometryCheckResult checkBelowBounds(
    Rect const& first,
    Rect const& second) {
    double firstTop     = bg::get<bg::min_corner, 1>(first);
    double secondBottom = bg::get<bg::max_corner, 1>(second);

    if (secondBottom <= firstTop) { return boost::outcome_v2::success(); }

    return failCheck(
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
        second);
}

GeometryCheckResult checkFullyCoversBounds(
    Rect const& main,
    Rect const& nested) {
    double mainLeft   = bg::get<bg::min_corner, 0>(main);
    double mainTop    = bg::get<bg::min_corner, 1>(main);
    double mainRight  = bg::get<bg::max_corner, 0>(main);
    double mainBottom = bg::get<bg::max_corner, 1>(main);

    double nestedLeft   = bg::get<bg::min_corner, 0>(nested);
    double nestedTop    = bg::get<bg::min_corner, 1>(nested);
    double nestedRight  = bg::get<bg::max_corner, 0>(nested);
    double nestedBottom = bg::get<bg::max_corner, 1>(nested);

    bool covers =                     //
        mainLeft <= nestedLeft        //
        && mainTop <= nestedTop       //
        && nestedRight <= mainRight   //
        && nestedBottom <= mainBottom //
        ;

    if (covers) { return boost::outcome_v2::success(); }

    double interArea    = overlapArea(main, nested);
    double mainArea     = rectArea(main);
    double nestedArea   = rectArea(nested);
    double mainByNested = overlapPercent(interArea, mainArea);
    double nestedByMain = overlapPercent(interArea, nestedArea);

    return failCheck(
        R"(
check                         = fully-covers-bounds
mainLeft                      = {}
mainTop                       = {}
mainRight                     = {}
mainBottom                    = {}
nestedLeft                    = {}
nestedTop                     = {}
nestedRight                   = {}
nestedBottom                  = {}
overlapArea                   = {}
mainArea                      = {}
nestedArea                    = {}
main overlapped by nested by  = {:.2f}%
nested overlapped by main by  = {:.2f}%
main                          = {}
nested                        = {}
)",
        mainLeft,
        mainTop,
        mainRight,
        mainBottom,
        nestedLeft,
        nestedTop,
        nestedRight,
        nestedBottom,
        interArea,
        mainArea,
        nestedArea,
        mainByNested,
        nestedByMain,
        main,
        nested);
}

GeometryCheckResult checkAlignedHorizontallyBounds(
    Rect const& first,
    Rect const& second,
    double      tolerance) {
    double firstCy  = (bg::get<bg::min_corner, 1>(first)
                       + bg::get<bg::max_corner, 1>(first))
                    * 0.5;
    double secondCy = (bg::get<bg::min_corner, 1>(second)
                       + bg::get<bg::max_corner, 1>(second))
                    * 0.5;
    double delta    = std::abs(firstCy - secondCy);

    if (delta <= tolerance) { return boost::outcome_v2::success(); }

    return failCheck(
        R"(
check      = aligned-horizontally-bounds
firstCy    = {}
secondCy   = {}
delta      = {}
tolerance  = {}
first      = {}
second     = {}
)",
        firstCy,
        secondCy,
        delta,
        tolerance,
        first,
        second);
}

GeometryCheckResult checkAlignedVerticallyBounds(
    Rect const& first,
    Rect const& second,
    double      tolerance) {
    double firstCx  = (bg::get<bg::min_corner, 0>(first)
                       + bg::get<bg::max_corner, 0>(first))
                    * 0.5;
    double secondCx = (bg::get<bg::min_corner, 0>(second)
                       + bg::get<bg::max_corner, 0>(second))
                    * 0.5;
    double delta    = std::abs(firstCx - secondCx);

    if (delta <= tolerance) { return boost::outcome_v2::success(); }

    return failCheck(
        R"(
check      = aligned-vertically-bounds
firstCx    = {}
secondCx   = {}
delta      = {}
tolerance  = {}
first      = {}
second     = {}
)",
        firstCx,
        secondCx,
        delta,
        tolerance,
        first,
        second);
}

GeometryCheckResult checkMinDistanceBounds(
    Rect const& first,
    Rect const& second,
    double      minDistance) {
    double d = bg::distance(first, second);
    if (minDistance <= d) { return boost::outcome_v2::success(); }

    return failCheck(
        R"(
check       = min-distance-bounds
distance    = {}
minDistance = {}
first       = {}
second      = {}
)",
        d,
        minDistance,
        first,
        second);
}

GeometryCheckResult checkMaxDistanceBounds(
    Rect const& first,
    Rect const& second,
    double      maxDistance) {
    double d = bg::distance(first, second);
    if (d <= maxDistance) { return boost::outcome_v2::success(); }

    return failCheck(
        R"(
check       = max-distance-bounds
distance    = {}
maxDistance = {}
first       = {}
second      = {}
)",
        d,
        maxDistance,
        first,
        second);
}

GeometryCheckResult checkSameWidthBounds(
    Rect const& first,
    Rect const& second,
    double      tolerance) {
    double fw = rectWidth(first);
    double sw = rectWidth(second);
    double d  = std::abs(fw - sw);

    if (d <= tolerance) { return boost::outcome_v2::success(); }

    return failCheck(
        R"(
check     = same-width-bounds
firstW    = {}
secondW   = {}
delta     = {}
tolerance = {}
first     = {}
second    = {}
)",
        fw,
        sw,
        d,
        tolerance,
        first,
        second);
}

GeometryCheckResult checkSameHeightBounds(
    Rect const& first,
    Rect const& second,
    double      tolerance) {
    double fh = rectHeight(first);
    double sh = rectHeight(second);
    double d  = std::abs(fh - sh);

    if (d <= tolerance) { return boost::outcome_v2::success(); }

    return failCheck(
        R"(
check     = same-height-bounds
firstH    = {}
secondH   = {}
delta     = {}
tolerance = {}
first     = {}
second    = {}
)",
        fh,
        sh,
        d,
        tolerance,
        first,
        second);
}

GeometryCheckResult checkSameSizeBounds(
    Rect const& first,
    Rect const& second,
    double      tolerance) {
    auto w = checkSameWidthBounds(first, second, tolerance);
    if (!w) { return w; }

    auto h = checkSameHeightBounds(first, second, tolerance);
    if (!h) { return h; }

    return boost::outcome_v2::success();
}

GeometryCheckResult checkEquidistantBounds(
    hstd::Vec<Rect> const& items,
    double                 tolerance) {
    if (items.size() < 3) {
        return failCheck(
            R"(
check = equidistant-bounds
error = need at least three shapes
count = {}
)",
            items.size());
    }

    hstd::Vec<double> cx;
    hstd::Vec<double> cy;
    cx.reserve(items.size());
    cy.reserve(items.size());

    for (Rect const& r : items) {
        cx.push_back(
            (bg::get<bg::min_corner, 0>(r) + bg::get<bg::max_corner, 0>(r))
            * 0.5);
        cy.push_back(
            (bg::get<bg::min_corner, 1>(r) + bg::get<bg::max_corner, 1>(r))
            * 0.5);
    }

    auto spread = [](hstd::Vec<double> const& v) {
        auto [mnIt, mxIt] = std::minmax_element(v.begin(), v.end());
        return *mxIt - *mnIt;
    };

    bool              useHorizontalAxis = spread(cy) <= spread(cx);
    hstd::Vec<double> axis              = useHorizontalAxis ? cx : cy;
    std::sort(axis.begin(), axis.end());

    hstd::Vec<double> spacing;
    spacing.reserve(axis.size() - 1);
    for (std::size_t i = 1; i < axis.size(); ++i) {
        spacing.push_back(axis.at(i) - axis.at(i - 1));
    }

    double expected = spacing.front();
    for (double s : spacing) {
        if (std::abs(s - expected) > tolerance) {
            return failCheck(
                R"(
check      = equidistant-bounds
axis       = {}
spacing    = {}
expected   = {}
tolerance  = {}
)",
                useHorizontalAxis ? "horizontal" : "vertical",
                spacing,
                expected,
                tolerance);
        }
    }

    return boost::outcome_v2::success();
}

boost::outcome_v2::result<Rect, GeometryError> boundsOf(
    visual::VisGroup const& value) {
    return value.computeBounds();
}

boost::outcome_v2::result<Rect, GeometryError> boundsOf(
    hstd::Vec<visual::VisGroup> const& value) {
    return visual::computeBounds(value);
}

} // namespace detail

GeometryCheckResult checkIntersects(
    Point const& first,
    Point const& second) {
    if (first.x() == second.x() && first.y() == second.y()) {
        return boost::outcome_v2::success();
    }

    return detail::failCheck(
        R"(
check  = point-point-intersects
first  = {}
second = {}
)",
        first,
        second);
}

GeometryCheckResult checkIntersects(Point const& point, Rect const& rect) {
    if (bg::covered_by(point, rect)) {
        return boost::outcome_v2::success();
    }

    return detail::failCheck(
        R"(
check = point-rect-intersects
point = {}
rect  = {}
)",
        point,
        rect);
}

GeometryCheckResult checkIntersects(Rect const& rect, Point const& point) {
    return checkIntersects(point, rect);
}

GeometryCheckResult checkIntersects(Point const& point, Path const& path) {
    auto segs = detail::flattenPath(path);
    if (!segs) {
        return detail::failCheck(
            R"(
check  = point-path-intersects
error  = cannot flatten path
reason = {}
)",
            segs.error().message());
    }

    for (auto const& s : segs.value()) {
        if (bg::distance(point, s.seg) == 0.0) {
            return boost::outcome_v2::success();
        }
    }

    return detail::failCheck(
        R"(
check = point-path-intersects
point = {}
path  = {}
)",
        point,
        path);
}

GeometryCheckResult checkIntersects(Path const& path, Point const& point) {
    return checkIntersects(point, path);
}

GeometryCheckResult checkIntersects(Rect const& rect, Path const& path) {
    auto segs = detail::flattenPath(path);
    if (!segs) {
        return detail::failCheck(
            R"(
check  = rect-path-intersects
error  = cannot flatten path
reason = {}
)",
            segs.error().message());
    }

    for (auto const& s : segs.value()) {
        if (bg::intersects(s.seg, rect)) {
            return boost::outcome_v2::success();
        }
    }

    return detail::failCheck(
        R"(
check = rect-path-intersects
rect  = {}
path  = {}
)",
        rect,
        path);
}

GeometryCheckResult checkIntersects(Path const& path, Rect const& rect) {
    return checkIntersects(rect, path);
}

GeometryCheckResult checkIntersects(
    Path const& first,
    Path const& second) {
    auto a = detail::flattenPath(first);
    if (!a) {
        return detail::failCheck(
            R"(
check  = path-path-intersects
error  = cannot flatten first path
reason = {}
)",
            a.error().message());
    }

    auto b = detail::flattenPath(second);
    if (!b) {
        return detail::failCheck(
            R"(
check  = path-path-intersects
error  = cannot flatten second path
reason = {}
)",
            b.error().message());
    }

    for (auto const& sa : a.value()) {
        for (auto const& sb : b.value()) {
            if (bg::intersects(sa.seg, sb.seg)) {
                return boost::outcome_v2::success();
            }
        }
    }

    return detail::failCheck(
        R"(
check  = path-path-intersects
first  = {}
second = {}
)",
        first,
        second);
}

} // namespace hstd::ext::geometry
