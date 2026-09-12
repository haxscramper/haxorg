#include <hstd/ext/geometry/hstd_geometry_test_ir.hpp>

#if ORG_BUILD_WITH_PROTOBUF

#    include <hstd/ext/geometry/hstd_geometry_serde.hpp>
#    include <hstd/stdlib/Formatter.hpp>

#    include <hstd/stdlib/strutils.hpp>
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
                converted.shape = hstd::serde::read_serde<Rect>(element.rect());
                break;

            case proto::GeometryElement::kPoint:
                converted.shape = hstd::serde::read_serde<Point>(element.point());
                break;

            case proto::GeometryElement::kPath:
                converted.shape = hstd::serde::read_serde<Path>(element.path());
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


using ExpressionValue = std::variant<double, Rect, Point, Path>;

struct EvaluatedExpression {
    ExpressionValue value;
    std::string     tree;
};

using ExpressionResult = boost::outcome_v2::result<EvaluatedExpression, GeometryError>;

std::string format_expression_type(ExpressionValue const& value) {
    return std::visit(
        [](auto const& item) -> std::string {
            using Value = std::decay_t<decltype(item)>;

            if constexpr (std::is_same_v<Value, double>) {
                return "scalar";
            } else if constexpr (std::is_same_v<Value, Rect>) {
                return "rectangle";
            } else if constexpr (std::is_same_v<Value, Point>) {
                return "point";
            } else {
                return "path";
            }
        },
        value);
}

std::string format_expression_value(ExpressionValue const& value) {
    return std::visit(
        [](auto const& item) -> std::string {
            using Value = std::decay_t<decltype(item)>;

            if constexpr (std::is_same_v<Value, double>) {
                return fmt::format("{}", item);
            } else if constexpr (std::is_same_v<Value, Rect>) {
                return hstd::serde::write_serde<proto::Rect>(item).ShortDebugString();
            } else if constexpr (std::is_same_v<Value, Point>) {
                return hstd::serde::write_serde<proto::Point>(item).ShortDebugString();
            } else {
                return hstd::serde::write_serde<proto::Path>(item).ShortDebugString();
            }
        },
        value);
}

std::string evaluatedValue(EvaluatedExpression const& value) {
    return fmt::format(
        "{}: {}",
        format_expression_type(value.value),
        format_expression_value(value.value));
}

ExpressionResult expressionFailure(std::string const& message) {
    return boost::outcome_v2::failure(GeometryError::init(message));
}

boost::outcome_v2::result<Rect, GeometryError> expressionBounds(
    ExpressionValue const& value) {
    return std::visit(
        [](auto const& item) -> boost::outcome_v2::result<Rect, GeometryError> {
            using Value = std::decay_t<decltype(item)>;

            if constexpr (std::is_same_v<Value, double>) {
                return boost::outcome_v2::failure(
                    GeometryError::init("Cannot compute bounds of a scalar expression"));
            } else {
                return detail::boundsOf(item);
            }
        },
        value);
}

Point pointAnchor(Rect const& bounds, proto::GeometryPointAnchor anchor) {
    auto rect = hstd::serde::write_serde<proto::Rect>(bounds);

    double left    = rect.x();
    double right   = rect.x() + rect.width();
    double upper   = rect.y();
    double lower   = rect.y() + rect.height();
    double centerX = left + rect.width() / 2.0;
    double centerY = upper + rect.height() / 2.0;

    switch (anchor) {
        case proto::POINT_ANCHOR_UPPER_LEFT: return Point(left, upper);
        case proto::POINT_ANCHOR_UPPER_CENTER: return Point(centerX, upper);
        case proto::POINT_ANCHOR_UPPER_RIGHT: return Point(right, upper);
        case proto::POINT_ANCHOR_CENTER_LEFT: return Point(left, centerY);
        case proto::POINT_ANCHOR_CENTER: return Point(centerX, centerY);
        case proto::POINT_ANCHOR_CENTER_RIGHT: return Point(right, centerY);
        case proto::POINT_ANCHOR_LOWER_LEFT: return Point(left, lower);
        case proto::POINT_ANCHOR_LOWER_CENTER: return Point(centerX, lower);
        case proto::POINT_ANCHOR_LOWER_RIGHT: return Point(right, lower);
    }

    throw std::logic_error(
        fmt::format("Unhandled GeometryPointAnchor value {}", static_cast<int>(anchor)));
}

Path sideAnchor(Rect const& bounds, proto::GeometrySideAnchor anchor) {
    Point ul = pointAnchor(bounds, proto::POINT_ANCHOR_UPPER_LEFT);
    Point ur = pointAnchor(bounds, proto::POINT_ANCHOR_UPPER_RIGHT);
    Point ll = pointAnchor(bounds, proto::POINT_ANCHOR_LOWER_LEFT);
    Point lr = pointAnchor(bounds, proto::POINT_ANCHOR_LOWER_RIGHT);

    switch (anchor) {
        case proto::SIDE_ANCHOR_UPPER: return Path::FromPolyline({ul, ur});
        case proto::SIDE_ANCHOR_RIGHT: return Path::FromPolyline({ur, lr});
        case proto::SIDE_ANCHOR_LOWER: return Path::FromPolyline({ll, lr});
        case proto::SIDE_ANCHOR_LEFT: return Path::FromPolyline({ul, ll});
    }

    throw std::logic_error(
        fmt::format("Unhandled GeometrySideAnchor value {}", static_cast<int>(anchor)));
}

std::string pointAnchorName(proto::GeometryPointAnchor anchor) {
    return proto::GeometryPointAnchor_Name(anchor);
}

std::string sideAnchorName(proto::GeometrySideAnchor anchor) {
    return proto::GeometrySideAnchor_Name(anchor);
}

std::string measureName(proto::GeometryMeasureKind kind) {
    return proto::GeometryMeasureKind_Name(kind);
}

std::string mathName(proto::GeometryMathOp op) { return proto::GeometryMathOp_Name(op); }

ExpressionResult evaluateExpression(
    ElementIndex const&                   elements,
    proto::GeometryElementRef::Ref const& expression);

ExpressionResult evaluateNested(
    ElementIndex const&                   elements,
    proto::GeometryElementRef::Ref const& expression,
    std::string const&                    operation,
    std::string const&                    operand) {
    auto result = evaluateExpression(elements, expression);

    if (!result) {
        return expressionFailure(
            fmt::format(
                "Cannot evaluate `{}` element reference:\n"
                "    {} = {}\n"
                "\n"
                "{}",
                operation,
                operand,
                expression.ShortDebugString(),
                hstd::indent(result.error().message(), 4)));
    }

    return result;
}

ExpressionResult evaluateShape(
    ElementIndex const&                          elements,
    proto::GeometryElementRef::Ref::Shape const& expression) {
    auto const iterator = elements.find(expression.id());

    if (iterator == elements.end()) {
        return expressionFailure(
            fmt::format(
                "Cannot evaluate `Shape` element reference:\n"
                "    id = '{}'\n"
                "\n"
                "No geometry element with this ID exists.",
                expression.id()));
    }

    auto value = std::visit(
        [](auto ptr) { return ExpressionValue{ptr}; }, *iterator->second);

    return EvaluatedExpression{
        .value = std::move(value),
        .tree  = fmt::format(
            "Shape\n"
            "    id = {}\n"
            "    value = {}",
            expression.id(),
            format_expression_value(value)),
    };
}

ExpressionResult evaluateAnchor(
    ElementIndex const&                           elements,
    proto::GeometryElementRef::Ref::Anchor const& expression) {
    auto nested = evaluateNested(elements, expression.ref(), "Anchor", "ref");

    if (!nested) { return boost::outcome_v2::failure(nested.error()); }

    auto bounds = expressionBounds(nested.value().value);

    if (!bounds) {
        return expressionFailure(
            fmt::format(
                "Cannot evaluate `Anchor` element reference:\n"
                "    ref = {}\n"
                "        evaluated to {}\n"
                "\n"
                "    Expected a point, rectangle, or path expression.\n"
                "\n"
                "{}",
                expression.ref().ShortDebugString(),
                evaluatedValue(nested.value()),
                hstd::indent(nested.value().tree, 4)));
    }

    switch (expression.kind_case()) {
        case proto::GeometryElementRef::Ref::Anchor::kPoint: {
            Point value = pointAnchor(bounds.value(), expression.point());

            return EvaluatedExpression{
                .value = value,
                .tree  = fmt::format(
                    "Anchor\n"
                    "    point = {}\n"
                    "    value = {}\n"
                    "    ref =\n"
                    "{}",
                    pointAnchorName(expression.point()),
                    format_expression_value(value),
                    hstd::indent(nested.value().tree, 8)),
            };
        }

        case proto::GeometryElementRef::Ref::Anchor::kSide: {
            Path value = sideAnchor(bounds.value(), expression.side());

            return EvaluatedExpression{
                .value = value,
                .tree  = fmt::format(
                    "Anchor\n"
                    "    side = {}\n"
                    "    value = {}\n"
                    "    ref =\n"
                    "{}",
                    sideAnchorName(expression.side()),
                    format_expression_value(value),
                    hstd::indent(nested.value().tree, 8)),
            };
        }

        case proto::GeometryElementRef::Ref::Anchor::KIND_NOT_SET:
            return expressionFailure(
                fmt::format(
                    "Cannot evaluate `Anchor` element reference:\n"
                    "    ref = {}\n"
                    "        evaluated to {}\n"
                    "\n"
                    "    The anchor kind is not set.",
                    expression.ref().ShortDebugString(),
                    evaluatedValue(nested.value())));
    }

    return expressionFailure(
        fmt::format(
            "Cannot evaluate `Anchor` element reference with kind {}.",
            static_cast<int>(expression.kind_case())));
}

ExpressionResult evaluateBBox(
    ElementIndex const&                         elements,
    proto::GeometryElementRef::Ref::BBox const& expression) {
    if (expression.refs().empty()) {
        return expressionFailure(
            "Cannot evaluate `BBox` element reference: no operands were provided.");
    }

    double minX = std::numeric_limits<double>::infinity();
    double minY = std::numeric_limits<double>::infinity();
    double maxX = -std::numeric_limits<double>::infinity();
    double maxY = -std::numeric_limits<double>::infinity();

    std::string tree = "BBox\n    refs =";

    for (int index = 0; index < expression.refs_size(); ++index) {
        auto const& operand = expression.refs(index);
        auto        value   = evaluateNested(
            elements, operand, "BBox", fmt::format("refs[{}]", index));

        if (!value) { return boost::outcome_v2::failure(value.error()); }

        auto bounds = expressionBounds(value.value().value);

        if (!bounds) {
            return expressionFailure(
                fmt::format(
                    "Cannot evaluate `BBox` element reference:\n"
                    "    refs[{}] = {}\n"
                    "        evaluated to {}\n"
                    "\n"
                    "    Expected a point, rectangle, or path expression.\n"
                    "\n"
                    "{}",
                    index,
                    operand.ShortDebugString(),
                    evaluatedValue(value.value()),
                    hstd::indent(value.value().tree, 4)));
        }

        auto rect = hstd::serde::write_serde<proto::Rect>(bounds.value());

        minX = std::min(minX, rect.x());
        minY = std::min(minY, rect.y());
        maxX = std::max(maxX, rect.x() + rect.width());
        maxY = std::max(maxY, rect.y() + rect.height());

        tree += fmt::format(
            "\n        [{}] =\n{}", index, hstd::indent(value.value().tree, 12));
    }

    Rect value = Rect::FromUpperLeftWH(minX, minY, maxX - minX, maxY - minY);

    tree += fmt::format("\n    value = {}", format_expression_value(value));

    return EvaluatedExpression{
        .value = value,
        .tree  = std::move(tree),
    };
}

ExpressionResult evaluateInterpolate(
    ElementIndex const&                                elements,
    proto::GeometryElementRef::Ref::Interpolate const& expression) {
    auto start = evaluateNested(elements, expression.start(), "Interpolate", "start");

    if (!start) { return boost::outcome_v2::failure(start.error()); }

    auto end = evaluateNested(elements, expression.end(), "Interpolate", "end");

    if (!end) { return boost::outcome_v2::failure(end.error()); }

    auto startPoint = std::get_if<Point>(&start.value().value);
    auto endPoint   = std::get_if<Point>(&end.value().value);

    if (startPoint == nullptr || endPoint == nullptr) {
        return expressionFailure(
            fmt::format(
                "Cannot evaluate `Interpolate` element reference:\n"
                "    start = {}\n"
                "        evaluated to {}\n"
                "    end = {}\n"
                "        evaluated to {}\n"
                "\n"
                "    Expected two point expressions.\n"
                "\n"
                "start evaluation:\n"
                "{}\n"
                "end evaluation:\n"
                "{}",
                expression.start().ShortDebugString(),
                evaluatedValue(start.value()),
                expression.end().ShortDebugString(),
                evaluatedValue(end.value()),
                hstd::indent(start.value().tree, 4),
                hstd::indent(end.value().tree, 4)));
    }

    auto   startProto = hstd::serde::write_serde<proto::Point>(*startPoint);
    auto   endProto   = hstd::serde::write_serde<proto::Point>(*endPoint);
    double bias       = expression.has_bias() ? expression.bias() : 0.5;

    Point value = Point(
        startProto.x() + (endProto.x() - startProto.x()) * bias,
        startProto.y() + (endProto.y() - startProto.y()) * bias);

    return EvaluatedExpression{
        .value = value,
        .tree  = fmt::format(
            "Interpolate\n"
            "    bias = {}\n"
            "    value = {}\n"
            "    start =\n"
            "{}\n"
            "    end =\n"
            "{}",
            bias,
            format_expression_value(value),
            hstd::indent(start.value().tree, 8),
            hstd::indent(end.value().tree, 8)),
    };
}

ExpressionResult evaluatePath(
    ElementIndex const&                                   elements,
    proto::GeometryElementRef::Ref::PathExpression const& expression) {
    if (expression.points_size() < 2) {
        return expressionFailure(
            fmt::format(
                "Cannot evaluate `Path` element reference: expected at least "
                "two point expressions, received {}.",
                expression.points_size()));
    }

    hstd::Vec<Point> points;
    points.reserve(expression.points_size());

    std::string tree = "Path\n    points =";

    for (int index = 0; index < expression.points_size(); ++index) {
        auto const& operand = expression.points(index);
        auto        value   = evaluateNested(
            elements, operand, "Path", fmt::format("points[{}]", index));

        if (!value) { return boost::outcome_v2::failure(value.error()); }

        auto point = std::get_if<Point>(&value.value().value);

        if (point == nullptr) {
            return expressionFailure(
                fmt::format(
                    "Cannot evaluate `Path` element reference:\n"
                    "    points[{}] = {}\n"
                    "        evaluated to {}\n"
                    "\n"
                    "    Expected a point expression.\n"
                    "\n"
                    "{}",
                    index,
                    operand.ShortDebugString(),
                    evaluatedValue(value.value()),
                    hstd::indent(value.value().tree, 4)));
        }

        points.push_back(*point);

        tree += fmt::format(
            "\n        [{}] =\n{}", index, hstd::indent(value.value().tree, 12));
    }

    Path value = Path::FromPolyline(points);
    tree += fmt::format("\n    value = {}", format_expression_value(value));

    return EvaluatedExpression{
        .value = value,
        .tree  = std::move(tree),
    };
}

double measuredValue(ExpressionValue const& value, proto::GeometryMeasureKind kind) {
    if (kind == proto::MEASURE_LENGTH) {
        return std::visit(
            [](auto const& item) -> double {
                using Value = std::decay_t<decltype(item)>;

                if constexpr (std::is_same_v<Value, double>) {
                    return std::abs(item);
                } else if constexpr (std::is_same_v<Value, Point>) {
                    return 0.0;
                } else if constexpr (std::is_same_v<Value, Rect>) {
                    auto rect = hstd::serde::write_serde<proto::Rect>(item);
                    return 2.0 * (rect.width() + rect.height());
                } else {
                    return item.lengthAsMultiline();
                }
            },
            value);
    }

    auto bounds = expressionBounds(value).value();
    auto rect   = hstd::serde::write_serde<proto::Rect>(bounds);

    switch (kind) {
        case proto::MEASURE_MIN_X: return rect.x();
        case proto::MEASURE_MAX_X: return rect.x() + rect.width();
        case proto::MEASURE_MIN_Y: return rect.y();
        case proto::MEASURE_MAX_Y: return rect.y() + rect.height();
        case proto::MEASURE_AREA: return rect.width() * rect.height();
        case proto::MEASURE_WIDTH: return rect.width();
        case proto::MEASURE_HEIGHT: return rect.height();
        case proto::MEASURE_LENGTH: break;
    }

    throw std::logic_error(
        fmt::format("Unhandled GeometryMeasureKind value {}", static_cast<int>(kind)));
}

ExpressionResult evaluateMeasure(
    ElementIndex const&                            elements,
    proto::GeometryElementRef::Ref::Measure const& expression) {
    auto operand = evaluateNested(elements, expression.ref(), "Measure", "ref");

    if (!operand) { return boost::outcome_v2::failure(operand.error()); }

    if (std::holds_alternative<double>(operand.value().value)
        && expression.kind() != proto::MEASURE_LENGTH) {
        return expressionFailure(
            fmt::format(
                "Cannot evaluate `Measure` element reference:\n"
                "    kind = {}\n"
                "    ref = {}\n"
                "        evaluated to {}\n"
                "\n"
                "    This measure requires a geometry expression.\n"
                "\n"
                "{}",
                measureName(expression.kind()),
                expression.ref().ShortDebugString(),
                evaluatedValue(operand.value()),
                hstd::indent(operand.value().tree, 4)));
    }

    double value = measuredValue(operand.value().value, expression.kind());

    return EvaluatedExpression{
        .value = value,
        .tree  = fmt::format(
            "Measure\n"
            "    kind = {}\n"
            "    value = {}\n"
            "    ref =\n"
            "{}",
            measureName(expression.kind()),
            value,
            hstd::indent(operand.value().tree, 8)),
    };
}

Point addPoints(Point const& lhs, Point const& rhs) {
    auto left  = hstd::serde::write_serde<proto::Point>(lhs);
    auto right = hstd::serde::write_serde<proto::Point>(rhs);

    return Point(left.x() + right.x(), left.y() + right.y());
}

Point subtractPoints(Point const& lhs, Point const& rhs) {
    auto left  = hstd::serde::write_serde<proto::Point>(lhs);
    auto right = hstd::serde::write_serde<proto::Point>(rhs);

    return Point(left.x() - right.x(), left.y() - right.y());
}

Point scalePoint(Point const& point, double scalar) {
    auto value = hstd::serde::write_serde<proto::Point>(point);

    return Point(value.x() * scalar, value.y() * scalar);
}

Rect translateRect(Rect const& rect, Point const& offset) {
    auto value = hstd::serde::write_serde<proto::Rect>(rect);
    auto point = hstd::serde::write_serde<proto::Point>(offset);

    return Rect::FromUpperLeftWH(
        value.x() + point.x(), value.y() + point.y(), value.width(), value.height());
}

Path translatePath(Path const& path, Point const& offset) { return path + offset; }

ExpressionResult invalidMath(
    proto::GeometryElementRef::Ref::Math const& expression,
    EvaluatedExpression const&                  lhs,
    EvaluatedExpression const&                  rhs,
    std::string const&                          reason) {
    return expressionFailure(
        fmt::format(
            "Cannot evaluate `Math` element reference:\n"
            "    op = {}\n"
            "    lhs = {}\n"
            "        evaluated to {}\n"
            "    rhs = {}\n"
            "        evaluated to {}\n"
            "\n"
            "    {}\n"
            "\n"
            "lhs evaluation:\n"
            "{}\n"
            "rhs evaluation:\n"
            "{}",
            mathName(expression.op()),
            expression.lhs().ShortDebugString(),
            evaluatedValue(lhs),
            expression.rhs().ShortDebugString(),
            evaluatedValue(rhs),
            reason,
            hstd::indent(lhs.tree, 4),
            hstd::indent(rhs.tree, 4)));
}

ExpressionResult applyMath(
    proto::GeometryElementRef::Ref::Math const& expression,
    EvaluatedExpression const&                  lhs,
    EvaluatedExpression const&                  rhs) {
    auto scalar_l = std::get_if<double>(&lhs.value);
    auto scalar_r = std::get_if<double>(&rhs.value);
    auto point_l  = std::get_if<Point>(&lhs.value);
    auto point_r  = std::get_if<Point>(&rhs.value);
    auto rect_l   = std::get_if<Rect>(&lhs.value);
    auto rect_r   = std::get_if<Rect>(&rhs.value);
    auto path_l   = std::get_if<Path>(&lhs.value);
    auto path_r   = std::get_if<Path>(&rhs.value);

    ExpressionValue result;

    switch (expression.op()) {
        case proto::MATH_ADD:
            if (scalar_l && scalar_r) {
                result = *scalar_l + *scalar_r;
            } else if (point_l && point_r) {
                result = addPoints(*point_l, *point_r);
            } else if (rect_l && point_r) {
                result = *rect_l + *point_r;
            } else if (point_l && rect_r) {
                result = *rect_r + *point_l;
            } else if (path_l && point_r) {
                result = translatePath(*path_l, *point_r);
            } else if (point_l && path_r) {
                result = translatePath(*path_r, *point_l);
            } else {
                return invalidMath(
                    expression,
                    lhs,
                    rhs,
                    "Addition supports scalar + scalar, point + point, "
                    "and geometry + point.");
            }
            break;

        case proto::MATH_SUB:
            if (scalar_l && scalar_r) {
                result = *scalar_l - *scalar_r;
            } else if (point_l && point_r) {
                result = subtractPoints(*point_l, *point_r);
            } else if (rect_l && point_r) {
                result = translateRect(*rect_l, scalePoint(*point_r, -1.0));
            } else if (path_l && point_r) {
                result = translatePath(*path_l, scalePoint(*point_r, -1.0));
            } else {
                return invalidMath(
                    expression,
                    lhs,
                    rhs,
                    "Subtraction supports scalar - scalar, point - point, "
                    "and geometry - point.");
            }
            break;

        case proto::MATH_MUL:
            if (scalar_l && scalar_r) {
                result = *scalar_l * *scalar_r;
            } else if (point_l && scalar_r) {
                result = scalePoint(*point_l, *scalar_r);
            } else if (scalar_l && point_r) {
                result = scalePoint(*point_r, *scalar_l);
            } else if (rect_l && scalar_r) {
                result = *rect_l * *scalar_r;
            } else if (scalar_l && rect_r) {
                result = *rect_r * *scalar_l;
            } else if (path_l && scalar_r) {
                result = *path_l * *scalar_r;
            } else if (scalar_l && path_r) {
                result = *path_r * *scalar_l;
            } else {
                return invalidMath(
                    expression,
                    lhs,
                    rhs,
                    "Multiplication supports scalar * scalar and "
                    "geometry * scalar.");
            }
            break;

        case proto::MATH_DIV:
            if (scalar_r == nullptr) {
                return invalidMath(
                    expression, lhs, rhs, "Division requires a scalar right operand.");
            }

            if (*scalar_r == 0.0) {
                return invalidMath(
                    expression, lhs, rhs, "Division by zero is not defined.");
            }

            if (scalar_l) {
                result = *scalar_l / *scalar_r;
            } else if (point_l) {
                result = *point_l / *scalar_r;
            } else if (rect_l) {
                result = *rect_l / *scalar_r;
            } else if (path_l) {
                result = *path_l / *scalar_r;
            } else {
                return invalidMath(
                    expression,
                    lhs,
                    rhs,
                    "Division requires a scalar or geometry left operand.");
            }
            break;
    }

    return EvaluatedExpression{
        .value = result,
        .tree  = fmt::format(
            "Math\n"
            "    op = {}\n"
            "    value = {}\n"
            "    lhs =\n"
            "{}\n"
            "    rhs =\n"
            "{}",
            mathName(expression.op()),
            format_expression_value(result),
            hstd::indent(lhs.tree, 8),
            hstd::indent(rhs.tree, 8)),
    };
}

ExpressionResult evaluateMath(
    ElementIndex const&                         elements,
    proto::GeometryElementRef::Ref::Math const& expression) {
    auto lhs = evaluateNested(elements, expression.lhs(), "Math", "lhs");

    if (!lhs) { return boost::outcome_v2::failure(lhs.error()); }

    auto rhs = evaluateNested(elements, expression.rhs(), "Math", "rhs");

    if (!rhs) { return boost::outcome_v2::failure(rhs.error()); }

    return applyMath(expression, lhs.value(), rhs.value());
}

ExpressionResult evaluateExpression(
    ElementIndex const&                   elements,
    proto::GeometryElementRef::Ref const& expression) {
    switch (expression.kind_case()) {
        case proto::GeometryElementRef::Ref::kShape:
            return evaluateShape(elements, expression.shape());

        case proto::GeometryElementRef::Ref::kAnchor:
            return evaluateAnchor(elements, expression.anchor());

        case proto::GeometryElementRef::Ref::kBbox:
            return evaluateBBox(elements, expression.bbox());

        case proto::GeometryElementRef::Ref::kInterpolate:
            return evaluateInterpolate(elements, expression.interpolate());

        case proto::GeometryElementRef::Ref::kPath:
            return evaluatePath(elements, expression.path());

        case proto::GeometryElementRef::Ref::kMeasure:
            return evaluateMeasure(elements, expression.measure());

        case proto::GeometryElementRef::Ref::kMath:
            return evaluateMath(elements, expression.math());

        case proto::GeometryElementRef::Ref::kScalar: {
            double value = expression.scalar().value();

            return EvaluatedExpression{
                .value = value,
                .tree  = fmt::format(
                    "ScalarLiteral\n"
                    "    value = {}",
                    value),
            };
        }

        case proto::GeometryElementRef::Ref::kPoint: {
            Point value = Point(expression.point().x(), expression.point().y());

            return EvaluatedExpression{
                .value = value,
                .tree  = fmt::format(
                    "PointLiteral\n"
                    "    x = {}\n"
                    "    y = {}\n"
                    "    value = {}",
                    expression.point().x(),
                    expression.point().y(),
                    format_expression_value(value)),
            };
        }

        case proto::GeometryElementRef::Ref::KIND_NOT_SET:
            return expressionFailure(
                fmt::format(
                    "Cannot evaluate geometry element reference `{}`: "
                    "the expression kind is not set.",
                    expression.ShortDebugString()));
    }

    return expressionFailure(
        fmt::format(
            "Cannot evaluate geometry element reference `{}`: "
            "unhandled expression kind {}.",
            expression.ShortDebugString(),
            static_cast<int>(expression.kind_case())));
}

boost::outcome_v2::result<GeometryElementShape, GeometryError> expressionGeometry(
    EvaluatedExpression const& expression) {
    return std::visit(
        [&](auto const& value)
            -> boost::outcome_v2::result<GeometryElementShape, GeometryError> {
            using Value = std::decay_t<decltype(value)>;

            if constexpr (std::is_same_v<Value, double>) {
                return boost::outcome_v2::failure(
                    GeometryError::init(
                        fmt::format(
                            "Geometry element reference evaluated to scalar "
                            "`{}` where a point, rectangle, or path was required.\n"
                            "\n"
                            "{}",
                            value,
                            expression.tree)));
            } else {
                return GeometryElementShape{value};
            }
        },
        expression.value);
}

boost::outcome_v2::result<GeometryElementShape, GeometryError> resolveElement(
    ElementIndex const&              elements,
    proto::GeometryElementRef const& reference) {
    if (!reference.has_expr()) {
        return boost::outcome_v2::failure(
            GeometryError::init(
                fmt::format(
                    "Cannot resolve geometry element reference `{}`: "
                    "the expression is not set.",
                    reference.ShortDebugString())));
    }

    auto evaluated = evaluateExpression(elements, reference.expr());

    if (!evaluated) { return boost::outcome_v2::failure(evaluated.error()); }

    return expressionGeometry(evaluated.value());
}

template <typename Arg1, typename Arg2, typename Fn>
GeometryCheckResult runOp(
    ElementIndex const& elements,
    Arg1 const&         arg1,
    Arg2 const&         arg2,
    Fn&&                function) {
    if (!arg1.has_expr()) {
        return failure(
            fmt::format(
                "Cannot evaluate first geometry operand `{}`: "
                "the expression is not set.",
                arg1.ShortDebugString()));
    }

    if (!arg2.has_expr()) {
        return failure(
            fmt::format(
                "Cannot evaluate second geometry operand `{}`: "
                "the expression is not set.",
                arg2.ShortDebugString()));
    }

    auto firstExpression = evaluateExpression(elements, arg1.expr());

    if (!firstExpression) { return boost::outcome_v2::failure(firstExpression.error()); }

    auto secondExpression = evaluateExpression(elements, arg2.expr());

    if (!secondExpression) {
        return boost::outcome_v2::failure(secondExpression.error());
    }

    auto first = expressionGeometry(firstExpression.value());

    if (!first) { return boost::outcome_v2::failure(first.error()); }

    auto second = expressionGeometry(secondExpression.value());

    if (!second) { return boost::outcome_v2::failure(second.error()); }

    auto result = std::visit(std::forward<Fn>(function), first.value(), second.value());

    if (result) { return result; }

    return boost::outcome_v2::failure(
        GeometryError::init(
            fmt::format(
                "{}\n"
                "first = {}\n"
                "{}\n"
                "second = {}\n"
                "{}",
                result.error().message(),
                format_expression_value(firstExpression.value().value),
                hstd::indent(firstExpression.value().tree, 4),
                format_expression_value(secondExpression.value().value),
                hstd::indent(secondExpression.value().tree, 4))));
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

            hstd::Vec<Rect>        bounds;
            hstd::Vec<std::string> trees;
            bounds.reserve(args.elements_size());
            trees.reserve(args.elements_size());

            for (int index = 0; index < args.elements_size(); ++index) {
                auto const& reference = args.elements(index);

                if (!reference.has_expr()) {
                    return failure(
                        fmt::format(
                            "Cannot evaluate equidistant operand {} `{}`: "
                            "the expression is not set.",
                            index,
                            reference.ShortDebugString()));
                }

                auto expression = evaluateExpression(elements, reference.expr());

                if (!expression) {
                    return boost::outcome_v2::failure(expression.error());
                }

                auto itemBounds = expressionBounds(expression.value().value);

                if (!itemBounds) {
                    return failure(
                        fmt::format(
                            "Cannot evaluate equidistant operand {} `{}`:\n"
                            "    evaluated to {}\n"
                            "\n"
                            "    Expected a point, rectangle, or path expression.\n"
                            "\n"
                            "{}",
                            index,
                            reference.ShortDebugString(),
                            evaluatedValue(expression.value()),
                            hstd::indent(expression.value().tree, 4)));
                }

                bounds.push_back(itemBounds.value());
                trees.push_back(expression.value().tree);
            }

            auto result = detail::checkEquidistantBounds(bounds, getTolerance(args));

            if (result) { return result; }

            std::string context = result.error().message();

            for (int index = 0; index < static_cast<int>(trees.size()); ++index) {
                context += fmt::format(
                    "\nelements[{}] =\n{}", index, hstd::indent(trees.at(index), 4));
            }

            return failure(context);
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
