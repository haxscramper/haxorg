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
        "{:<{}} = {}\n", "error", FAIL_CHECK_LABEL_WIDTH, error_name);
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
    N,                                                                    \
    ...)                                                                  \
    N

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
        __HSTD_GEOMETRY_FAIL_CHECK_NO_ARGS)                               \
    (__VA_ARGS__)

} // namespace detail

GeometryCheckResult checkIntersects(
    Point const& first,
    Point const& second);

GeometryCheckResult checkIntersects(Point const& point, Rect const& rect);

GeometryCheckResult checkIntersects(Rect const& rect, Point const& point);

GeometryCheckResult checkIntersects(Point const& point, Path const& path);

GeometryCheckResult checkIntersects(Path const& path, Point const& point);

GeometryCheckResult checkIntersects(Rect const& rect, Path const& path);

GeometryCheckResult checkIntersects(Path const& path, Rect const& rect);

GeometryCheckResult checkIntersects(Path const& first, Path const& second);

template <typename L, typename R>
GeometryCheckResult checkLeftOf(L const& first, R const& second);

template <typename L, typename R>
GeometryCheckResult checkRightOf(L const& first, R const& second);

template <typename L, typename R>
GeometryCheckResult checkAbove(L const& first, R const& second);

template <typename L, typename R>
GeometryCheckResult checkPartiallyAbove(
    L const& first,
    R const& second,
    double   maxUnderPercent);

template <typename L, typename R>
GeometryCheckResult checkBelow(L const& first, R const& second);

template <typename L, typename R>
GeometryCheckResult checkFullyCovers(L const& first, R const& second);

template <typename L, typename R>
GeometryCheckResult checkAlignedHorizontally(
    L const& first,
    R const& second,
    double   tolerance = 0.0);

template <typename L, typename R>
GeometryCheckResult checkAlignedVertically(
    L const& first,
    R const& second,
    double   tolerance = 0.0);

template <typename L, typename R>
GeometryCheckResult checkMinDistance(
    L const& first,
    R const& second,
    double   minDistance);

template <typename L, typename R>
GeometryCheckResult checkMaxDistance(
    L const& first,
    R const& second,
    double   maxDistance);

template <typename L, typename R>
GeometryCheckResult checkSameSize(
    L const& first,
    R const& second,
    double   tolerance = 0.0);

template <typename L, typename R>
GeometryCheckResult checkSameWidth(
    L const& first,
    R const& second,
    double   tolerance = 0.0);

template <typename L, typename R>
GeometryCheckResult checkSameHeight(
    L const& first,
    R const& second,
    double   tolerance = 0.0);

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

GeometryCheckResult checkLeftOfBounds(
    Rect const& first,
    Rect const& second);
GeometryCheckResult checkRightOfBounds(
    Rect const& first,
    Rect const& second);
GeometryCheckResult checkAboveBounds(
    Rect const& first,
    Rect const& second);
GeometryCheckResult checkPartiallyAboveBounds(
    Rect const& fixed,
    Rect const& relative,
    double      maxUnderPercent);
GeometryCheckResult checkBelowBounds(
    Rect const& first,
    Rect const& second);
GeometryCheckResult checkFullyCoversBounds(
    Rect const& first,
    Rect const& second);

GeometryCheckResult checkAlignedHorizontallyBounds(
    Rect const& first,
    Rect const& second,
    double      tolerance);
GeometryCheckResult checkAlignedVerticallyBounds(
    Rect const& first,
    Rect const& second,
    double      tolerance);
GeometryCheckResult checkMinDistanceBounds(
    Rect const& first,
    Rect const& second,
    double      minDistance);
GeometryCheckResult checkMaxDistanceBounds(
    Rect const& first,
    Rect const& second,
    double      maxDistance);
GeometryCheckResult checkSameSizeBounds(
    Rect const& first,
    Rect const& second,
    double      tolerance);
GeometryCheckResult checkSameWidthBounds(
    Rect const& first,
    Rect const& second,
    double      tolerance);
GeometryCheckResult checkSameHeightBounds(
    Rect const& first,
    Rect const& second,
    double      tolerance);
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
            "general-error",
            checkName,
            first,
            second,
            r.error().message());
    }

    return boost::outcome_v2::success();
}

} // namespace detail

template <typename L, typename R>
GeometryCheckResult checkLeftOf(L const& first, R const& second) {
    return detail::runBinaryBoundsCheck(
        "left-of", first, second, [](Rect const& a, Rect const& b) {
            return detail::checkLeftOfBounds(a, b);
        });
}

template <typename L, typename R>
GeometryCheckResult checkRightOf(L const& first, R const& second) {
    return detail::runBinaryBoundsCheck(
        "right-of", first, second, [](Rect const& a, Rect const& b) {
            return detail::checkRightOfBounds(a, b);
        });
}

template <typename L, typename R>
GeometryCheckResult checkAbove(L const& first, R const& second) {
    return detail::runBinaryBoundsCheck(
        "above", first, second, [](Rect const& a, Rect const& b) {
            return detail::checkAboveBounds(a, b);
        });
}

template <typename L, typename R>
GeometryCheckResult checkPartiallyAbove(
    L const& first,
    R const& second,
    double   maxUnderPercent) {
    return detail::runBinaryBoundsCheck(
        "partially-above",
        first,
        second,
        [maxUnderPercent](Rect const& a, Rect const& b) {
            return detail::checkPartiallyAboveBounds(
                a, b, maxUnderPercent);
        });
}

template <typename L, typename R>
GeometryCheckResult checkBelow(L const& first, R const& second) {
    return detail::runBinaryBoundsCheck(
        "below", first, second, [](Rect const& a, Rect const& b) {
            return detail::checkBelowBounds(a, b);
        });
}

template <typename L, typename R>
GeometryCheckResult checkFullyCovers(L const& first, R const& second) {
    return detail::runBinaryBoundsCheck(
        "fully-covers", first, second, [](Rect const& a, Rect const& b) {
            return detail::checkFullyCoversBounds(a, b);
        });
}

template <typename L, typename R>
GeometryCheckResult checkAlignedHorizontally(
    L const& first,
    R const& second,
    double   tolerance) {
    return detail::runBinaryBoundsCheck(
        "aligned-horizontally",
        first,
        second,
        [tolerance](Rect const& a, Rect const& b) {
            return detail::checkAlignedHorizontallyBounds(a, b, tolerance);
        });
}

template <typename L, typename R>
GeometryCheckResult checkAlignedVertically(
    L const& first,
    R const& second,
    double   tolerance) {
    return detail::runBinaryBoundsCheck(
        "aligned-vertically",
        first,
        second,
        [tolerance](Rect const& a, Rect const& b) {
            return detail::checkAlignedVerticallyBounds(a, b, tolerance);
        });
}

template <typename L, typename R>
GeometryCheckResult checkMinDistance(
    L const& first,
    R const& second,
    double   minDistance) {
    return detail::runBinaryBoundsCheck(
        "min-distance",
        first,
        second,
        [minDistance](Rect const& a, Rect const& b) {
            return detail::checkMinDistanceBounds(a, b, minDistance);
        });
}

template <typename L, typename R>
GeometryCheckResult checkMaxDistance(
    L const& first,
    R const& second,
    double   maxDistance) {
    return detail::runBinaryBoundsCheck(
        "max-distance",
        first,
        second,
        [maxDistance](Rect const& a, Rect const& b) {
            return detail::checkMaxDistanceBounds(a, b, maxDistance);
        });
}

template <typename L, typename R>
GeometryCheckResult checkSameSize(
    L const& first,
    R const& second,
    double   tolerance) {
    return detail::runBinaryBoundsCheck(
        "same-size",
        first,
        second,
        [tolerance](Rect const& a, Rect const& b) {
            return detail::checkSameSizeBounds(a, b, tolerance);
        });
}

template <typename L, typename R>
GeometryCheckResult checkSameWidth(
    L const& first,
    R const& second,
    double   tolerance) {
    return detail::runBinaryBoundsCheck(
        "same-width",
        first,
        second,
        [tolerance](Rect const& a, Rect const& b) {
            return detail::checkSameWidthBounds(a, b, tolerance);
        });
}

template <typename L, typename R>
GeometryCheckResult checkSameHeight(
    L const& first,
    R const& second,
    double   tolerance) {
    return detail::runBinaryBoundsCheck(
        "same-height",
        first,
        second,
        [tolerance](Rect const& a, Rect const& b) {
            return detail::checkSameHeightBounds(a, b, tolerance);
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
