#pragma once

#include <hstd/ext/hstd_geometry.hpp>
#include <hstd/ext/hstd_visual.hpp>
#include <hstd/stdlib/Outcome.hpp>
#include <boost/outcome/result.hpp>
#include <hstd/stdlib/Exception.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>

namespace hstd::ext::geometry {

struct GeometryError : hstd::CRTP_hexception<GeometryError> {};

using GeometryCheckResult = boost::outcome_v2::result<void, GeometryError>;

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
GeometryCheckResult checkBelow(L const& first, R const& second);

template <typename L, typename R>
GeometryCheckResult checkFullyCovers(L const& first, R const& second);
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
GeometryCheckResult checkBelowBounds(
    Rect const& first,
    Rect const& second);
GeometryCheckResult checkFullyCoversBounds(
    Rect const& first,
    Rect const& second);
} // namespace detail

template <typename L, typename R>
GeometryCheckResult checkLeftOf(L const& first, R const& second) {
    auto fb = detail::boundsOf(first);
    if (!fb) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
error  = failed to compute first bounds
reason = {}
)",
                    fb.error().message())));
    }

    auto sb = detail::boundsOf(second);
    if (!sb) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
error  = failed to compute second bounds
reason = {}
)",
                    sb.error().message())));
    }

    auto r = detail::checkLeftOfBounds(fb.value(), sb.value());
    if (!r) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
check  = left-of
first  = {}
second = {}
reason = {}
)",
                    first,
                    second,
                    r.error().message())));
    }

    return boost::outcome_v2::success();
}

template <typename L, typename R>
GeometryCheckResult checkRightOf(L const& first, R const& second) {
    auto fb = detail::boundsOf(first);
    if (!fb) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
error  = failed to compute first bounds
reason = {}
)",
                    fb.error().message())));
    }

    auto sb = detail::boundsOf(second);
    if (!sb) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
error  = failed to compute second bounds
reason = {}
)",
                    sb.error().message())));
    }

    auto r = detail::checkRightOfBounds(fb.value(), sb.value());
    if (!r) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
check  = right-of
first  = {}
second = {}
reason = {}
)",
                    first,
                    second,
                    r.error().message())));
    }

    return boost::outcome_v2::success();
}

template <typename L, typename R>
GeometryCheckResult checkAbove(L const& first, R const& second) {
    auto fb = detail::boundsOf(first);
    if (!fb) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
error  = failed to compute first bounds
reason = {}
)",
                    fb.error().message())));
    }

    auto sb = detail::boundsOf(second);
    if (!sb) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
error  = failed to compute second bounds
reason = {}
)",
                    sb.error().message())));
    }

    auto r = detail::checkAboveBounds(fb.value(), sb.value());
    if (!r) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
check  = above
first  = {}
second = {}
reason = {}
)",
                    first,
                    second,
                    r.error().message())));
    }

    return boost::outcome_v2::success();
}

template <typename L, typename R>
GeometryCheckResult checkBelow(L const& first, R const& second) {
    auto fb = detail::boundsOf(first);
    if (!fb) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
error  = failed to compute first bounds
reason = {}
)",
                    fb.error().message())));
    }

    auto sb = detail::boundsOf(second);
    if (!sb) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
error  = failed to compute second bounds
reason = {}
)",
                    sb.error().message())));
    }

    auto r = detail::checkBelowBounds(fb.value(), sb.value());
    if (!r) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
check  = below
first  = {}
second = {}
reason = {}
)",
                    first,
                    second,
                    r.error().message())));
    }

    return boost::outcome_v2::success();
}

template <typename L, typename R>
GeometryCheckResult checkFullyCovers(L const& first, R const& second) {
    auto fb = detail::boundsOf(first);
    if (!fb) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
error  = failed to compute first bounds
reason = {}
)",
                    fb.error().message())));
    }

    auto sb = detail::boundsOf(second);
    if (!sb) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
error  = failed to compute second bounds
reason = {}
)",
                    sb.error().message())));
    }

    auto r = detail::checkFullyCoversBounds(fb.value(), sb.value());
    if (!r) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    R"(
check  = fully-covers
first  = {}
second = {}
reason = {}
)",
                    first,
                    second,
                    r.error().message())));
    }

    return boost::outcome_v2::success();
}
} // namespace hstd::ext::geometry
