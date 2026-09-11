#include <hstd/ext/geometry/hstd_geometry_test_ir.hpp>

#if ORG_BUILD_WITH_PROTOBUF

#    include <hstd/ext/geometry/hstd_geometry_serde.hpp>
#    include <hstd/stdlib/Formatter.hpp>

#    include <unordered_map>
#    include <utility>

namespace hstd::ext::geometry {
namespace {

constexpr double DEFAULT_RTOL = 1e-5;
constexpr double DEFAULT_ATOL = 1e-8;

using ElementIndex = std::unordered_map<std::string, GeometryElementShape const*>;

GeometryCheckResult failure(std::string const& message) {
    return boost::outcome_v2::failure(GeometryError::init(message));
}

template <typename Message>
double getRtol(Message const& message) {
    return message.has_rtol() ? message.rtol() : DEFAULT_RTOL;
}

template <typename Message>
double getAtol(Message const& message) {
    return message.has_atol() ? message.atol() : DEFAULT_ATOL;
}

template <typename Message>
double getTolerance(Message const& message) {
    return message.has_tolerance() ? message.tolerance() : 0.0;
}

DistanceCheck getDistanceCheck(proto::GeometryDistanceCheck value) {
    switch (value) {
        case proto::DISTANCE_BOTH: return DistanceCheck::Both;

        case proto::DISTANCE_X_ONLY: return DistanceCheck::XOnly;

        case proto::DISTANCE_Y_ONLY: return DistanceCheck::YOnly;
    }

    throw std::logic_error(
        hstd::fmt("Unhandled GeometryDistanceCheck value {}", static_cast<int>(value)));
}

GeometryElementListResult readElements(
    google::protobuf::RepeatedPtrField<proto::GeometryElement> const& input) {
    GeometryElementList result;
    result.reserve(input.size());

    std::unordered_map<std::string, std::size_t> ids;

    for (int index = 0; index < input.size(); ++index) {
        auto const& element = input.Get(index);

        if (element.id().empty()) {
            return boost::outcome_v2::failure(
                GeometryError::init(
                    hstd::fmt("Geometry element at index {} has an empty ID", index)));
        }

        if (auto const it = ids.find(element.id()); it != ids.end()) {
            return boost::outcome_v2::failure(
                GeometryError::init(
                    hstd::fmt(
                        "Duplicate geometry element ID '{}' at indices {} and {}",
                        element.id(),
                        it->second,
                        index)));
        }

        ids.emplace(element.id(), index);

        GeometryElement converted;
        converted.id = element.id();

        switch (element.shape_case()) {
            case proto::GeometryElement::kRect:
                converted.shape = hstd::serde::read_serde<proto::Rect, Rect>(
                    element.rect());
                break;

            case proto::GeometryElement::kPoint:
                converted.shape = hstd::serde::read_serde<proto::Point, Point>(
                    element.point());
                break;

            case proto::GeometryElement::kPath:
                converted.shape = hstd::serde::read_serde<proto::Path, Path>(
                    element.path());
                break;

            case proto::GeometryElement::SHAPE_NOT_SET:
                return boost::outcome_v2::failure(
                    GeometryError::init(
                        hstd::fmt(
                            "Geometry element '{}' does not define a shape",
                            element.id())));
        }

        result.push_back(std::move(converted));
    }

    return result;
}

ElementIndex makeElementIndex(GeometryElementList const& elements) {
    ElementIndex result;
    result.reserve(elements.size());

    for (auto const& element : elements) { result.emplace(element.id, &element.shape); }

    return result;
}

Point anchorPoint(Rect const& bounds, proto::GeometryAnchor anchor) {
    auto rect = hstd::serde::write_serde<proto::Rect>(bounds);

    double x = rect.x();
    double y = rect.y();

    switch (anchor) {
        case proto::UPPER_LEFT: break;

        case proto::UPPER_CENTER: x += rect.width() / 2.0; break;

        case proto::UPPER_RIGHT: x += rect.width(); break;

        case proto::CENTER_LEFT: y += rect.height() / 2.0; break;

        case proto::CENTER:
            x += rect.width() / 2.0;
            y += rect.height() / 2.0;
            break;

        case proto::CENTER_RIGHT:
            x += rect.width();
            y += rect.height() / 2.0;
            break;

        case proto::LOWER_LEFT: y += rect.height(); break;

        case proto::LOWER_CENTER:
            x += rect.width() / 2.0;
            y += rect.height();
            break;

        case proto::LOWER_RIGHT:
            x += rect.width();
            y += rect.height();
            break;

        case proto::WHOLE_SHAPE:
            throw std::logic_error("WHOLE_SHAPE cannot be converted to an anchor point");
    }

    proto::Point point;
    point.set_x(x);
    point.set_y(y);
    return hstd::serde::read_serde<proto::Point, Point>(point);
}

boost::outcome_v2::result<GeometryElementShape, GeometryError> resolveElement(
    ElementIndex const&              elements,
    proto::GeometryElementRef const& reference) {
    auto const it = elements.find(reference.id());

    if (it == elements.end()) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt("Unknown geometry element ID '{}'", reference.id())));
    }

    if (reference.anchor() == proto::WHOLE_SHAPE) { return *it->second; }

    auto bounds = std::visit(
        [](auto const& shape) { return detail::boundsOf(shape); }, *it->second);

    if (!bounds) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                hstd::fmt(
                    "Failed to compute bounds for geometry element '{}': {}",
                    reference.id(),
                    bounds.error().message())));
    }

    return GeometryElementShape{anchorPoint(bounds.value(), reference.anchor())};
}

template <typename Arg1, typename Arg2, typename Fn>
GeometryCheckResult runOp(
    ElementIndex const& elements,
    Arg1 const&         arg1,
    Arg2 const&         arg2,
    Fn&&                fn) {
    auto first = resolveElement(elements, arg1);
    if (!first) { return boost::outcome_v2::failure(first.error()); }

    auto second = resolveElement(elements, arg2);
    if (!second) { return boost::outcome_v2::failure(second.error()); }

    return std::visit(std::forward<Fn>(fn), first.value(), second.value());
}

GeometryCheckResult runCheck(
    ElementIndex const&         elements,
    proto::GeometryCheck const& check) {
    switch (check.check_case()) {
        case proto::GeometryCheck::kIntersects:
            return runOp(
                elements,
                check.intersects().first(),
                check.intersects().second(),
                [](auto const& first, auto const& second) {
                    return checkIntersects(first, second);
                });

        case proto::GeometryCheck::kLeftOf: {
            auto const& args = check.left_of();
            return runOp(
                elements,
                args.stationary(),
                args.relative(),
                [&](auto const& stationary, auto const& relative) {
                    return checkLeftOf(
                        stationary, relative, getRtol(args), getAtol(args));
                });
        }

        case proto::GeometryCheck::kRightOf: {
            auto const& args = check.right_of();
            return runOp(
                elements,
                args.stationary(),
                args.relative(),
                [&](auto const& stationary, auto const& relative) {
                    return checkRightOf(
                        stationary, relative, getRtol(args), getAtol(args));
                });
        }

        case proto::GeometryCheck::kAbove: {
            auto const& args = check.above();
            return runOp(
                elements,
                args.stationary(),
                args.relative(),
                [&](auto const& stationary, auto const& relative) {
                    return checkAbove(stationary, relative, getRtol(args), getAtol(args));
                });
        }

        case proto::GeometryCheck::kBelow: {
            auto const& args = check.below();
            return runOp(
                elements,
                args.stationary(),
                args.relative(),
                [&](auto const& stationary, auto const& relative) {
                    return checkBelow(stationary, relative, getRtol(args), getAtol(args));
                });
        }

        case proto::GeometryCheck::kPartiallyAbove: {
            auto const& args = check.partially_above();
            return runOp(
                elements,
                args.stationary(),
                args.relative(),
                [&](auto const& stationary, auto const& relative) {
                    return checkPartiallyAbove(
                        stationary,
                        relative,
                        args.max_under_percent(),
                        getRtol(args),
                        getAtol(args));
                });
        }

        case proto::GeometryCheck::kPartiallyBelow: {
            auto const& args = check.partially_below();
            return runOp(
                elements,
                args.stationary(),
                args.relative(),
                [&](auto const& stationary, auto const& relative) {
                    return checkPartiallyBelow(
                        stationary,
                        relative,
                        args.max_over_percent(),
                        getRtol(args),
                        getAtol(args));
                });
        }

        case proto::GeometryCheck::kPartiallyLeft: {
            auto const& args = check.partially_left();
            return runOp(
                elements,
                args.stationary(),
                args.relative(),
                [&](auto const& stationary, auto const& relative) {
                    return checkPartiallyLeft(
                        stationary,
                        relative,
                        args.max_over_percent(),
                        getRtol(args),
                        getAtol(args));
                });
        }

        case proto::GeometryCheck::kPartiallyRight: {
            auto const& args = check.partially_right();
            return runOp(
                elements,
                args.stationary(),
                args.relative(),
                [&](auto const& stationary, auto const& relative) {
                    return checkPartiallyRight(
                        stationary,
                        relative,
                        args.max_over_percent(),
                        getRtol(args),
                        getAtol(args));
                });
        }

        case proto::GeometryCheck::kFullyCovers: {
            auto const& args = check.fully_covers();
            return runOp(
                elements,
                args.main(),
                args.nested(),
                [&](auto const& first, auto const& second) {
                    return checkFullyCovers(first, second, getRtol(args), getAtol(args));
                });
        }

        case proto::GeometryCheck::kPartiallyCovers: {
            auto const& args = check.partially_covers();
            return runOp(
                elements,
                args.main(),
                args.nested(),
                [&](auto const& first, auto const& second) {
                    return checkPartiallyCovers(
                        first,
                        second,
                        args.overlap_percent(),
                        getRtol(args),
                        getAtol(args));
                });
        }

        case proto::GeometryCheck::kAlignedHorizontally: {
            auto const& args = check.aligned_horizontally();
            return runOp(
                elements,
                args.first(),
                args.second(),
                [&](auto const& first, auto const& second) {
                    return checkAlignedHorizontally(
                        first, second, getTolerance(args), getRtol(args), getAtol(args));
                });
        }

        case proto::GeometryCheck::kAlignedVertically: {
            auto const& args = check.aligned_vertically();
            return runOp(
                elements,
                args.first(),
                args.second(),
                [&](auto const& first, auto const& second) {
                    return checkAlignedVertically(
                        first, second, getTolerance(args), getRtol(args), getAtol(args));
                });
        }

        case proto::GeometryCheck::kMinDistance: {
            auto const& args = check.min_distance();
            return runOp(
                elements,
                args.first(),
                args.second(),
                [&](auto const& first, auto const& second) {
                    return checkMinDistance(
                        first,
                        second,
                        args.min_distance(),
                        getDistanceCheck(args.distance_check()),
                        getRtol(args),
                        getAtol(args));
                });
        }

        case proto::GeometryCheck::kMaxDistance: {
            auto const& args = check.max_distance();
            return runOp(
                elements,
                args.first(),
                args.second(),
                [&](auto const& first, auto const& second) {
                    return checkMaxDistance(
                        first,
                        second,
                        args.max_distance(),
                        getDistanceCheck(args.distance_check()),
                        getRtol(args),
                        getAtol(args));
                });
        }

        case proto::GeometryCheck::kDistance: {
            auto const& args = check.distance();
            return runOp(
                elements,
                args.first(),
                args.second(),
                [&](auto const& first, auto const& second) {
                    return checkDistance(
                        first,
                        second,
                        args.distance(),
                        getDistanceCheck(args.distance_check()),
                        getRtol(args),
                        getAtol(args));
                });
        }

        case proto::GeometryCheck::kSameSize: {
            auto const& args = check.same_size();
            return runOp(
                elements,
                args.first(),
                args.second(),
                [&](auto const& first, auto const& second) {
                    return checkSameSize(
                        first, second, getTolerance(args), getRtol(args), getAtol(args));
                });
        }

        case proto::GeometryCheck::kSameWidth: {
            auto const& args = check.same_width();
            return runOp(
                elements,
                args.first(),
                args.second(),
                [&](auto const& first, auto const& second) {
                    return checkSameWidth(
                        first, second, getTolerance(args), getRtol(args), getAtol(args));
                });
        }

        case proto::GeometryCheck::kSameHeight: {
            auto const& args = check.same_height();
            return runOp(
                elements,
                args.first(),
                args.second(),
                [&](auto const& first, auto const& second) {
                    return checkSameHeight(
                        first, second, getTolerance(args), getRtol(args), getAtol(args));
                });
        }

        case proto::GeometryCheck::kEquidistant: {
            auto const& args = check.equidistant();

            hstd::Vec<Rect> bounds;
            bounds.reserve(args.elements_size());

            for (auto const& reference : args.elements()) {
                auto shape = resolveElement(elements, reference);
                if (!shape) { return boost::outcome_v2::failure(shape.error()); }

                auto itemBounds = std::visit(
                    [](auto const& item) { return detail::boundsOf(item); },
                    shape.value());

                if (!itemBounds) {
                    return boost::outcome_v2::failure(itemBounds.error());
                }

                bounds.push_back(itemBounds.value());
            }

            return detail::checkEquidistantBounds(bounds, getTolerance(args));
        }

        case proto::GeometryCheck::CHECK_NOT_SET:
            return failure("Geometry check does not define a check kind");
    }

    return failure("Unhandled geometry check kind");
}

GeometryCheckResult appendContext(
    GeometryCheckResult         result,
    proto::GeometryCheck const& check,
    std::size_t                 checkIndex) {
    if (result) { return result; }

    return boost::outcome_v2::failure(
        GeometryError::init(
            result.error().message()
            + hstd::fmt(
                "\ncheck-index                    = {}\n"
                "check-id                       = {}\n"
                "check-spec                     = {}",
                checkIndex,
                check.id(),
                check.ShortDebugString())));
}

} // namespace

GeometryElementListResult geometryElements(proto::GeometryValidationSpec const& spec) {
    return readElements(spec.elements());
}

GeometryValidationErrors validateGeometry(
    GeometryElementListResult const&                                  elements,
    ::google::protobuf::RepeatedPtrField<proto::GeometryCheck> const& checks) {
    GeometryValidationErrors errors;
    if (!elements) {
        proto::GeometryCheck context;

        GeometryValidationError error{
            .checkIndex = 0,
            .checkId    = {},
            .check      = std::move(context),
            .result     = boost::outcome_v2::failure(elements.error()),
        };

        errors.push_back(std::move(error));
        return errors;
    }

    auto index = makeElementIndex(elements.value());

    for (int checkIndex = 0; checkIndex < checks.size(); ++checkIndex) {
        auto const& check  = checks.at(checkIndex);
        auto        result = runCheck(index, check);

        if (!result) {
            GeometryValidationError error{
                .checkIndex = static_cast<std::size_t>(checkIndex),
                .checkId    = check.id(),
                .check      = check,
                .result     = appendContext(
                    std::move(result), check, static_cast<std::size_t>(checkIndex)),
            };

            errors.push_back(std::move(error));
        }
    }

    return errors;
}


GeometryValidationErrors validateGeometry(proto::GeometryValidationSpec const& spec) {
    auto elements = geometryElements(spec);
    return validateGeometry(elements, spec.checks());
}


} // namespace hstd::ext::geometry

#endif
