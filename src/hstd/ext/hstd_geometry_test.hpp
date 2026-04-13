#pragma once

#include <hstd/ext/hstd_geometry.hpp>
#include <hstd/ext/hstd_visual.hpp>
#include <hstd/stdlib/Outcome.hpp>
#include <boost/outcome/result.hpp>
#include <hstd/stdlib/Exception.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <utility>

namespace hstd::ext::geometry {

struct GeometryError : hstd::CRTP_hexception<GeometryError> {};

using GeometryCheckResult = boost::outcome_v2::result<void, GeometryError>;

namespace detail {
constexpr int FAIL_CHECK_LABEL_WIDTH = 30;

struct FailVerbatimLine {
    std::string line;
};

struct FailVerbatimKV {
    std::string key;
    std::string value;
};

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


inline std::string fail_check_format(char const* error_name) {
    return hstd::fmt(
        "\n{:<{}} = {}\n", "error", FAIL_CHECK_LABEL_WIDTH, error_name);
}

template <typename... Args>
std::string fail_check_format(
    char const*                        error_name,
    std::initializer_list<const char*> names,
    Args const&... args) {
    std::string result = ::hstd::ext::geometry::detail::fail_check_format(
        error_name);
    auto name_it = names.begin();
    (detail::fail_check_append(result, *name_it++, args), ...);
    return result;
}

#define __HSTD_GEOMETRY_FAIL_CHECK_NAME(r, data, i, elem)                 \
    BOOST_PP_STRINGIZE(elem),

#define __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS(error_name, ...)             \
    boost::outcome_v2::failure(                                           \
        GeometryError::init(                                              \
            ::hstd::ext::geometry::detail::fail_check_format(             \
                error_name,                                               \
                {BOOST_PP_SEQ_FOR_EACH_I(                                 \
                    __HSTD_GEOMETRY_FAIL_CHECK_NAME,                      \
                    _,                                                    \
                    BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))},              \
                __VA_ARGS__)))

#define __HSTD_GEOMETRY_FAIL_CHECK_NO_ARGS(error_name)                    \
    boost::outcome_v2::failure(                                           \
        GeometryError::init(                                              \
            ::hstd::ext::geometry::detail::fail_check_format(             \
                error_name)))

#define __HSTD_GEOMETRY_FAIL_CHECK_PICK(                                  \
    _1,                                                                   \
    _2,                                                                   \
    _3,                                                                   \
    _4,                                                                   \
    _5,                                                                   \
    _6,                                                                   \
    _7,                                                                   \
    _8,                                                                   \
    _9,                                                                   \
    _10,                                                                  \
    _11,                                                                  \
    _12,                                                                  \
    _13,                                                                  \
    _14,                                                                  \
    _15,                                                                  \
    _16,                                                                  \
    _17,                                                                  \
    _18,                                                                  \
    N,                                                                    \
    ...)                                                                  \
    N

/// \brief Builds a formatted GeometryError failure result from an error
/// label and optional key/value payload arguments.
#define HSDT_GEOMETRY_FAIL_CHECK(...)                                     \
    __HSTD_GEOMETRY_FAIL_CHECK_PICK(                                      \
        __VA_ARGS__,                                                      \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_WITH_ARGS,                             \
        __HSTD_GEOMETRY_FAIL_CHECK_NO_ARGS)                               \
    (__VA_ARGS__)

} // namespace detail

/// \brief Checks whether two points intersect by exact coordinate
/// equality.
GeometryCheckResult checkIntersects(
    Point const& first,
    Point const& second);

/// \brief Checks whether a point lies inside or on the boundary of a
/// rectangle.
GeometryCheckResult checkIntersects(Point const& point, Rect const& rect);

/// \brief Checks whether a point lies inside or on the boundary of a
/// rectangle.
GeometryCheckResult checkIntersects(Rect const& rect, Point const& point);

/// \brief Checks whether a point intersects any drawable segment of a
/// path.
GeometryCheckResult checkIntersects(Point const& point, Path const& path);

/// \brief Checks whether a point intersects any drawable segment of a
/// path.
GeometryCheckResult checkIntersects(Path const& path, Point const& point);

/// \brief Checks whether a rectangle intersects any drawable segment of a
/// path.
GeometryCheckResult checkIntersects(Rect const& rect, Path const& path);

/// \brief Checks whether a rectangle intersects any drawable segment of a
/// path.
GeometryCheckResult checkIntersects(Path const& path, Rect const& rect);

/// \brief Checks whether any segments of two paths intersect.
GeometryCheckResult checkIntersects(Path const& first, Path const& second);

/// \brief Checks whether relative is fully on the left side of stationary.
template <typename L, typename R>
GeometryCheckResult checkLeftOf(
    L const& stationary,
    R const& relative,
    double   rtol = 1e-5,
    double   atol = 1e-8);

/// \brief Checks whether relative is fully on the right side of
/// stationary.
template <typename L, typename R>
GeometryCheckResult checkRightOf(
    L const& stationary,
    R const& relative,
    double   rtol = 1e-5,
    double   atol = 1e-8);

/// \brief Checks whether relative is fully above stationary.
template <typename L, typename R>
GeometryCheckResult checkAbove(
    L const& stationary,
    R const& relative,
    double   rtol = 1e-5,
    double   atol = 1e-8);

/// \brief Checks whether relative is above stationary allowing limited
/// underflow. The allowed portion under stationary is controlled by
/// maxUnderPercent.
template <typename L, typename R>
GeometryCheckResult checkPartiallyAbove(
    L const& stationary,
    R const& relative,
    double   maxUnderPercent,
    double   rtol = 1e-5,
    double   atol = 1e-8);

/// \brief Checks whether relative is below stationary allowing limited
/// overflow. The allowed portion above stationary is controlled by
/// maxOverPercent.
template <typename L, typename R>
GeometryCheckResult checkPartiallyBelow(
    L const& stationary,
    R const& relative,
    double   maxOverPercent,
    double   rtol = 1e-5,
    double   atol = 1e-8);

/// \brief Checks whether relative is left of stationary allowing limited
/// overflow. The allowed portion to the right of stationary is controlled
/// by maxOverPercent.
template <typename L, typename R>
GeometryCheckResult checkPartiallyLeft(
    L const& stationary,
    R const& relative,
    double   maxOverPercent,
    double   rtol = 1e-5,
    double   atol = 1e-8);

/// \brief Checks whether relative is right of stationary allowing limited
/// overflow. The allowed portion to the left of stationary is controlled
/// by maxOverPercent.
template <typename L, typename R>
GeometryCheckResult checkPartiallyRight(
    L const& stationary,
    R const& relative,
    double   maxOverPercent,
    double   rtol = 1e-5,
    double   atol = 1e-8);

/// \brief Checks whether relative is fully below stationary.
template <typename L, typename R>
GeometryCheckResult checkBelow(
    L const& stationary,
    R const& relative,
    double   rtol = 1e-5,
    double   atol = 1e-8);

/// \brief Checks whether the first shape fully covers the second shape
/// bounds.
template <typename L, typename R>
GeometryCheckResult checkFullyCovers(
    L const& first,
    R const& second,
    double   rtol = 1e-5,
    double   atol = 1e-8);

/// \brief Checks whether two shapes are horizontally center-aligned.
template <typename L, typename R>
GeometryCheckResult checkAlignedHorizontally(
    L const& first,
    R const& second,
    double   tolerance = 0.0,
    double   rtol      = 1e-5,
    double   atol      = 1e-8);

/// \brief Checks whether two shapes are vertically center-aligned.
template <typename L, typename R>
GeometryCheckResult checkAlignedVertically(
    L const& first,
    R const& second,
    double   tolerance = 0.0,
    double   rtol      = 1e-5,
    double   atol      = 1e-8);

/// \brief Checks whether the minimal distance between two shapes is large
/// enough.
template <typename L, typename R>
GeometryCheckResult checkMinDistance(
    L const& first,
    R const& second,
    double   minDistance,
    double   rtol = 1e-5,
    double   atol = 1e-8);

/// \brief Checks whether the minimal distance between two shapes stays
/// below a limit.
template <typename L, typename R>
GeometryCheckResult checkMaxDistance(
    L const& first,
    R const& second,
    double   maxDistance,
    double   rtol = 1e-5,
    double   atol = 1e-8);

/// \brief Checks whether two shapes have matching width and height.
template <typename L, typename R>
GeometryCheckResult checkSameSize(
    L const& first,
    R const& second,
    double   tolerance = 0.0,
    double   rtol      = 1e-5,
    double   atol      = 1e-8);

/// \brief Checks whether two shapes have matching widths.
template <typename L, typename R>
GeometryCheckResult checkSameWidth(
    L const& first,
    R const& second,
    double   tolerance = 0.0,
    double   rtol      = 1e-5,
    double   atol      = 1e-8);

/// \brief Checks whether two shapes have matching heights.
template <typename L, typename R>
GeometryCheckResult checkSameHeight(
    L const& first,
    R const& second,
    double   tolerance = 0.0,
    double   rtol      = 1e-5,
    double   atol      = 1e-8);

/// \brief Checks whether a sequence of shapes is evenly spaced along one
/// axis.
template <typename T>
GeometryCheckResult checkEquidistant(
    hstd::Vec<T> const& values,
    double              tolerance = 0.0);
} // namespace hstd::ext::geometry

namespace hstd::ext::geometry {
namespace detail {

boost::outcome_v2::result<Rect, GeometryError> boundsOf(Rect const& value);
boost::outcome_v2::result<Rect, GeometryError> boundsOf(
    Point const& value);
boost::outcome_v2::result<Rect, GeometryError> boundsOf(Path const& value);
boost::outcome_v2::result<Rect, GeometryError> boundsOf(
    visual::VisGroup const& value);
boost::outcome_v2::result<Rect, GeometryError> boundsOf(
    hstd::Vec<visual::VisGroup> const& value);

GeometryCheckResult checkPartiallyAboveBounds(
    Rect const& stationary,
    Rect const& relative,
    double      maxUnderPercent,
    double      rtol = 1e-5,
    double      atol = 1e-8);
GeometryCheckResult checkPartiallyBelowBounds(
    Rect const& stationary,
    Rect const& relative,
    double      maxOverPercent,
    double      rtol = 1e-5,
    double      atol = 1e-8);
GeometryCheckResult checkPartiallyLeftBounds(
    Rect const& stationary,
    Rect const& relative,
    double      maxOverPercent,
    double      rtol = 1e-5,
    double      atol = 1e-8);
GeometryCheckResult checkPartiallyRightBounds(
    Rect const& stationary,
    Rect const& relative,
    double      maxOverPercent,
    double      rtol = 1e-5,
    double      atol = 1e-8);
GeometryCheckResult checkFullyCoversBounds(
    Rect const& first,
    Rect const& second,
    double      rtol = 1e-5,
    double      atol = 1e-8);
GeometryCheckResult checkAlignedHorizontallyBounds(
    Rect const& first,
    Rect const& second,
    double      tolerance,
    double      rtol = 1e-5,
    double      atol = 1e-8);
GeometryCheckResult checkAlignedVerticallyBounds(
    Rect const& first,
    Rect const& second,
    double      tolerance,
    double      rtol = 1e-5,
    double      atol = 1e-8);
GeometryCheckResult checkMinDistanceBounds(
    Rect const& first,
    Rect const& second,
    double      minDistance,
    double      rtol = 1e-5,
    double      atol = 1e-8);
GeometryCheckResult checkMaxDistanceBounds(
    Rect const& first,
    Rect const& second,
    double      maxDistance,
    double      rtol = 1e-5,
    double      atol = 1e-8);
GeometryCheckResult checkSameSizeBounds(
    Rect const& first,
    Rect const& second,
    double      tolerance,
    double      rtol = 1e-5,
    double      atol = 1e-8);
GeometryCheckResult checkSameWidthBounds(
    Rect const& first,
    Rect const& second,
    double      tolerance,
    double      rtol = 1e-5,
    double      atol = 1e-8);
GeometryCheckResult checkSameHeightBounds(
    Rect const& first,
    Rect const& second,
    double      tolerance,
    double      rtol = 1e-5,
    double      atol = 1e-8);
GeometryCheckResult checkEquidistantBounds(
    hstd::Vec<Rect> const& items,
    double                 tolerance);

template <typename L, typename R, typename Fn>
GeometryCheckResult runBinaryBoundsCheck(
    char const* checkName,
    L const&    first,
    R const&    second,
    Fn&&        fn) {
    auto fb = boundsOf(first);
    if (!fb) {
        return HSDT_GEOMETRY_FAIL_CHECK(
            R"(failed to compute first bounds)",
            checkName,
            fb.error().message());
    }

    auto sb = boundsOf(second);
    if (!sb) {
        return HSDT_GEOMETRY_FAIL_CHECK(
            R"(failed to compute second bounds)",
            checkName,
            sb.error().message());
    }

    auto r = std::forward<Fn>(fn)(fb.value(), sb.value());
    if (!r) {
        return HSDT_GEOMETRY_FAIL_CHECK(
            "general-error", checkName, r.error().message());
    }

    return boost::outcome_v2::success();
}

} // namespace detail

template <typename L, typename R>
GeometryCheckResult checkLeftOf(
    L const& stationary,
    R const& relative,
    double   rtol,
    double   atol) {
    return checkPartiallyLeft(stationary, relative, 0.0, rtol, atol);
}

template <typename L, typename R>
GeometryCheckResult checkRightOf(
    L const& stationary,
    R const& relative,
    double   rtol,
    double   atol) {
    return checkPartiallyRight(stationary, relative, 0.0, rtol, atol);
}

template <typename L, typename R>
GeometryCheckResult checkAbove(
    L const& stationary,
    R const& relative,
    double   rtol,
    double   atol) {
    return checkPartiallyAbove(stationary, relative, 0.0, rtol, atol);
}

template <typename L, typename R>
GeometryCheckResult checkPartiallyAbove(
    L const& stationary,
    R const& relative,
    double   maxUnderPercent,
    double   rtol,
    double   atol) {
    return detail::runBinaryBoundsCheck(
        "partially-above",
        stationary,
        relative,
        [&](Rect const& a, Rect const& b) {
            return detail::checkPartiallyAboveBounds(
                a, b, maxUnderPercent, rtol, atol);
        });
}

template <typename L, typename R>
GeometryCheckResult checkPartiallyBelow(
    L const& stationary,
    R const& relative,
    double   maxOverPercent,
    double   rtol,
    double   atol) {
    return detail::runBinaryBoundsCheck(
        "partially-below",
        stationary,
        relative,
        [&](Rect const& a, Rect const& b) {
            return detail::checkPartiallyBelowBounds(
                a, b, maxOverPercent, rtol, atol);
        });
}

template <typename L, typename R>
GeometryCheckResult checkPartiallyLeft(
    L const& stationary,
    R const& relative,
    double   maxOverPercent,
    double   rtol,
    double   atol) {
    return detail::runBinaryBoundsCheck(
        "partially-left",
        stationary,
        relative,
        [&](Rect const& a, Rect const& b) {
            return detail::checkPartiallyLeftBounds(
                a, b, maxOverPercent, rtol, atol);
        });
}

template <typename L, typename R>
GeometryCheckResult checkPartiallyRight(
    L const& stationary,
    R const& relative,
    double   maxOverPercent,
    double   rtol,
    double   atol) {
    return detail::runBinaryBoundsCheck(
        "partially-right",
        stationary,
        relative,
        [&](Rect const& a, Rect const& b) {
            return detail::checkPartiallyRightBounds(
                a, b, maxOverPercent, rtol, atol);
        });
}

template <typename L, typename R>
GeometryCheckResult checkBelow(
    L const& stationary,
    R const& relative,
    double   rtol,
    double   atol) {
    return checkPartiallyBelow(stationary, relative, 0.0, rtol, atol);
}

template <typename L, typename R>
GeometryCheckResult checkFullyCovers(
    L const& main,
    R const& nested,
    double   rtol,
    double   atol) {
    return detail::runBinaryBoundsCheck(
        "fully-covers", main, nested, [&](Rect const& a, Rect const& b) {
            return detail::checkFullyCoversBounds(a, b, rtol, atol);
        });
}

template <typename L, typename R>
GeometryCheckResult checkAlignedHorizontally(
    L const& first,
    R const& second,
    double   tolerance,
    double   rtol,
    double   atol) {
    return detail::runBinaryBoundsCheck(
        "aligned-horizontally",
        first,
        second,
        [&](Rect const& a, Rect const& b) {
            return detail::checkAlignedHorizontallyBounds(
                a, b, tolerance, rtol, atol);
        });
}

template <typename L, typename R>
GeometryCheckResult checkAlignedVertically(
    L const& first,
    R const& second,
    double   tolerance,
    double   rtol,
    double   atol) {
    return detail::runBinaryBoundsCheck(
        "aligned-vertically",
        first,
        second,
        [&](Rect const& a, Rect const& b) {
            return detail::checkAlignedVerticallyBounds(
                a, b, tolerance, rtol, atol);
        });
}

template <typename L, typename R>
GeometryCheckResult checkMinDistance(
    L const& first,
    R const& second,
    double   minDistance,
    double   rtol,
    double   atol) {
    return detail::runBinaryBoundsCheck(
        "min-distance", first, second, [&](Rect const& a, Rect const& b) {
            return detail::checkMinDistanceBounds(
                a, b, minDistance, rtol, atol);
        });
}

template <typename L, typename R>
GeometryCheckResult checkMaxDistance(
    L const& first,
    R const& second,
    double   maxDistance,
    double   rtol,
    double   atol) {
    return detail::runBinaryBoundsCheck(
        "max-distance", first, second, [&](Rect const& a, Rect const& b) {
            return detail::checkMaxDistanceBounds(
                a, b, maxDistance, rtol, atol);
        });
}

template <typename L, typename R>
GeometryCheckResult checkSameSize(
    L const& first,
    R const& second,
    double   tolerance,
    double   rtol,
    double   atol) {
    return detail::runBinaryBoundsCheck(
        "same-size", first, second, [&](Rect const& a, Rect const& b) {
            return detail::checkSameSizeBounds(
                a, b, tolerance, rtol, atol);
        });
}

template <typename L, typename R>
GeometryCheckResult checkSameWidth(
    L const& first,
    R const& second,
    double   tolerance,
    double   rtol,
    double   atol) {
    return detail::runBinaryBoundsCheck(
        "same-width", first, second, [&](Rect const& a, Rect const& b) {
            return detail::checkSameWidthBounds(
                a, b, tolerance, rtol, atol);
        });
}

template <typename L, typename R>
GeometryCheckResult checkSameHeight(
    L const& first,
    R const& second,
    double   tolerance,
    double   rtol,
    double   atol) {
    return detail::runBinaryBoundsCheck(
        "same-height", first, second, [&](Rect const& a, Rect const& b) {
            return detail::checkSameHeightBounds(
                a, b, tolerance, rtol, atol);
        });
}

template <typename T>
GeometryCheckResult checkEquidistant(
    hstd::Vec<T> const& values,
    double              tolerance) {
    hstd::Vec<Rect> bounds;
    bounds.reserve(values.size());

    for (auto const& value : values) {
        auto b = detail::boundsOf(value);
        if (!b) {
            return HSDT_GEOMETRY_FAIL_CHECK(
                R"(equidistant failed to compute bounds)",
                b.error().message());
        }
        bounds.push_back(b.value());
    }

    auto r = detail::checkEquidistantBounds(bounds, tolerance);
    if (!r) {
        return HSDT_GEOMETRY_FAIL_CHECK(
            R"(equidistant)", values, r.error().message());
    }

    return boost::outcome_v2::success();
}

} // namespace hstd::ext::geometry
