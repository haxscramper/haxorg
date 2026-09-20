#include <hstd/geometry/hstd_geometry_test_ir.hpp>

#if ORG_BUILD_WITH_PROTOBUF
#    pragma clang diagnostic error "-Wswitch"

#    include <hstd/geometry/hstd_geometry_serde.hpp>
#    include <hstd/stdlib/formatting/Formatter.hpp>

#    include <hstd/stdlib/algorithms/strutils.hpp>
#    include <sstream>
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
        CASE_PROTO_ENUM_SENTINEL(proto::GeometryDistanceCheck);
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

    std::unordered_map<std::string, int> ids;

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
    ExpressionValue                                  value;
    std::string                                      name;
    std::string                                      op_name;
    std::vector<std::pair<std::string, std::string>> fields;
    std::vector<EvaluatedExpression>                 sub_expressions;
};

struct GeometryErrorTree {
    std::string                                      name;
    std::string                                      message;
    std::vector<std::pair<std::string, std::string>> fields;
    std::vector<EvaluatedExpression>                 expressions;
    std::vector<GeometryErrorTree>                   nested;
    std::vector<std::string>                         notes;
};

EvaluatedExpression named(std::string name, EvaluatedExpression expression) {
    expression.name = std::move(name);
    return expression;
}

GeometryErrorTree named(std::string name, GeometryErrorTree error) {
    error.name = std::move(name);
    return error;
}


using ExpressionResult = hstd::Result<EvaluatedExpression, GeometryError>;

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

std::string formatExpressionTree(EvaluatedExpression const& expression, int indent) {
    std::stringstream out;
    std::string const pad(indent, ' ');
    std::string const field_pad(indent + 4, ' ');

    out << pad << expression.op_name;

    for (auto const& [name, value] : expression.fields) {
        out << "\n" << field_pad << name << " = " << value;
    }

    out << "\n" << field_pad << "value = " << format_expression_value(expression.value);

    for (auto const& nested : expression.sub_expressions) {
        out << "\n"
            << field_pad << nested.name << " =\n"
            << formatExpressionTree(nested, indent + 8);
    }

    return out.str();
}

std::string formatExpressionTree(EvaluatedExpression const& expression) {
    return formatExpressionTree(expression, 0);
}

std::string formatErrorTree(GeometryErrorTree const& error, int indent) {
    std::stringstream out;
    std::string const pad(indent, ' ');
    std::string const field_pad(indent + 4, ' ');

    out << pad << error.message;

    for (auto const& [name, value] : error.fields) {
        out << "\n" << field_pad << name << " = " << value;
    }

    for (auto const& note : error.notes) { out << "\n" << field_pad << note; }

    for (auto const& expression : error.expressions) {
        out << "\n"
            << field_pad << expression.name << " =\n"
            << formatExpressionTree(expression, indent + 8);
    }

    for (auto const& nested : error.nested) {
        out << "\n"
            << field_pad << nested.name << ":\n"
            << formatErrorTree(nested, indent + 8);
    }

    return out.str();
}

GeometryError makeError(GeometryErrorTree const& tree) {
    return GeometryError::init(formatErrorTree(tree, 0) + "\n");
}

ExpressionResult expressionFailure(GeometryErrorTree const& tree) {
    return boost::outcome_v2::failure(makeError(tree));
}

hstd::Result<Rect, GeometryError> expressionBounds(ExpressionValue const& value) {
    return std::visit(
        [](auto const& item) -> hstd::Result<Rect, GeometryError> {
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
        CASE_PROTO_ENUM_SENTINEL(proto::GeometryPointAnchor);
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
        CASE_PROTO_ENUM_SENTINEL(proto::GeometrySideAnchor);
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
            GeometryErrorTree{
                .message = fmt::format(
                    "Cannot evaluate `{}` element reference", operation),
                .fields = {{operand, expression.ShortDebugString()}},
                .nested = {named(
                    "nested error",
                    GeometryErrorTree{
                        .message = result.error().message(),
                    })},
            });
    }

    return result;
}

ExpressionResult evaluateShape(
    ElementIndex const&                          elements,
    proto::GeometryElementRef::Ref::Shape const& expression) {
    auto const iterator = elements.find(expression.id());

    if (iterator == elements.end()) {
        return expressionFailure(
            GeometryErrorTree{
                .message = "Cannot evaluate `Shape` element reference",
                .fields  = {{"id", fmt::format("'{}'", expression.id())}},
                .notes   = {"No geometry element with this ID exists."},
            });
    }

    auto value = std::visit(
        [](auto ptr) { return ExpressionValue{ptr}; }, *iterator->second);

    return EvaluatedExpression{
        .value   = std::move(value),
        .op_name = "Shape",
        .fields  = {{"id", expression.id()}},
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
            GeometryErrorTree{
                              .message = "Cannot evaluate `Anchor` element reference",
                              .fields  = {
                                              {"ref", expression.ref().ShortDebugString()},
                                              {"evaluated-to", evaluatedValue(nested.value())},
                                              },
                              .expressions = {named("ref", nested.value())},
                              .notes       = {"Expected a point, rectangle, or path expression."},
                              });
    }

    switch (expression.kind_case()) {
        case proto::GeometryElementRef::Ref::Anchor::kPoint: {
            Point value = pointAnchor(bounds.value(), expression.point());

            return EvaluatedExpression{
                .value           = value,
                .op_name         = "Anchor",
                .fields          = {{"point", pointAnchorName(expression.point())}},
                .sub_expressions = {named("ref", nested.value())},
            };
        }

        case proto::GeometryElementRef::Ref::Anchor::kSide: {
            Path value = sideAnchor(bounds.value(), expression.side());

            return EvaluatedExpression{
                .value           = value,
                .op_name         = "Anchor",
                .fields          = {{"side", sideAnchorName(expression.side())}},
                .sub_expressions = {named("ref", nested.value())},
            };
        }

        case proto::GeometryElementRef::Ref::Anchor::KIND_NOT_SET:
            return expressionFailure(
                GeometryErrorTree{
                                  .message = "Cannot evaluate `Anchor` element reference",
                                  .fields  = {
                                                  {"ref", expression.ref().ShortDebugString()},
                                                  {"evaluated-to", evaluatedValue(nested.value())},
                                                  },
                                  .expressions = {named("ref", nested.value())},
                                  .notes       = {"The anchor kind is not set."},
                                  });
    }

    return expressionFailure(
        GeometryErrorTree{
            .message = fmt::format(
                "Cannot evaluate `Anchor` element reference with kind {}",
                static_cast<int>(expression.kind_case())),
        });
}

ExpressionResult evaluateBBox(
    ElementIndex const&                         elements,
    proto::GeometryElementRef::Ref::BBox const& expression) {
    if (expression.refs().empty()) {
        return expressionFailure(
            GeometryErrorTree{
                .message = "Cannot evaluate `BBox` element reference",
                .notes   = {"No operands were provided."},
            });
    }

    double minX = std::numeric_limits<double>::infinity();
    double minY = std::numeric_limits<double>::infinity();
    double maxX = -std::numeric_limits<double>::infinity();
    double maxY = -std::numeric_limits<double>::infinity();

    std::vector<EvaluatedExpression> refs;

    for (int index = 0; index < expression.refs_size(); ++index) {
        auto const& operand = expression.refs(index);
        auto        value   = evaluateNested(
            elements, operand, "BBox", fmt::format("refs[{}]", index));

        if (!value) { return boost::outcome_v2::failure(value.error()); }

        auto bounds = expressionBounds(value.value().value);

        if (!bounds) {
            return expressionFailure(
                GeometryErrorTree{
                    .message = "Cannot evaluate `BBox` element reference",
                    .fields
                    = {{fmt::format("refs[{}]", index), operand.ShortDebugString()},
                       {"evaluated-to", evaluatedValue(value.value())}},
                    .expressions = {named(fmt::format("refs[{}]", index), value.value())},
                    .notes       = {"Expected a point, rectangle, or path expression."},
                });
        }

        auto rect = hstd::serde::write_serde<proto::Rect>(bounds.value());

        minX = std::min(minX, rect.x());
        minY = std::min(minY, rect.y());
        maxX = std::max(maxX, rect.x() + rect.width());
        maxY = std::max(maxY, rect.y() + rect.height());

        refs.push_back(named(fmt::format("refs[{}]", index), value.value()));
    }

    Rect value = Rect::FromUpperLeftWH(minX, minY, maxX - minX, maxY - minY);

    return EvaluatedExpression{
        .value           = value,
        .op_name         = "BBox",
        .sub_expressions = std::move(refs),
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
            GeometryErrorTree{
                .message = "Cannot evaluate `Interpolate` element reference",
                .fields
                = {{"start", expression.start().ShortDebugString()},
                   {"start-evaluated-to", evaluatedValue(start.value())},
                   {"end", expression.end().ShortDebugString()},
                   {"end-evaluated-to", evaluatedValue(end.value())}},
                .expressions = {named("start", start.value()), named("end", end.value())},
                .notes       = {"Expected two point expressions."},
            });
    }

    auto   startProto = hstd::serde::write_serde<proto::Point>(*startPoint);
    auto   endProto   = hstd::serde::write_serde<proto::Point>(*endPoint);
    double bias       = expression.has_bias() ? expression.bias() : 0.5;

    Point value = Point(
        startProto.x() + (endProto.x() - startProto.x()) * bias,
        startProto.y() + (endProto.y() - startProto.y()) * bias);

    return EvaluatedExpression{
        .value           = value,
        .op_name         = "Interpolate",
        .fields          = {{"bias", fmt::format("{}", bias)}},
        .sub_expressions = {named("start", start.value()), named("end", end.value())},
    };
}

ExpressionResult evaluatePath(
    ElementIndex const&                                   elements,
    proto::GeometryElementRef::Ref::PathExpression const& expression) {
    if (expression.points_size() < 2) {
        return expressionFailure(
            GeometryErrorTree{
                              .message = "Cannot evaluate `Path` element reference",
                              .notes   = {
                                  fmt::format(
                                      "Expected at least two point expressions, received {}.",
                                      expression.points_size()),
                                  },
                              });
    }

    hstd::Vec<Point> points;
    points.reserve(expression.points_size());

    std::vector<EvaluatedExpression> operands;

    for (int index = 0; index < expression.points_size(); ++index) {
        auto const& operand = expression.points(index);
        auto        value   = evaluateNested(
            elements, operand, "Path", fmt::format("points[{}]", index));

        if (!value) { return boost::outcome_v2::failure(value.error()); }

        auto point = std::get_if<Point>(&value.value().value);

        if (point == nullptr) {
            return expressionFailure(
                GeometryErrorTree{
                    .message = "Cannot evaluate `Path` element reference",
                    .fields
                    = {{fmt::format("points[{}]", index), operand.ShortDebugString()},
                       {"evaluated-to", evaluatedValue(value.value())}},
                    .expressions = {named(
                        fmt::format("points[{}]", index), value.value())},
                    .notes       = {"Expected a point expression."},
                });
        }

        points.push_back(*point);
        operands.push_back(named(fmt::format("points[{}]", index), value.value()));
    }

    Path value = Path::FromPolyline(points);

    return EvaluatedExpression{
        .value           = value,
        .op_name         = "Path",
        .sub_expressions = std::move(operands),
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
        CASE_PROTO_ENUM_SENTINEL(proto::GeometryMeasureKind);
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
            GeometryErrorTree{
                              .message = "Cannot evaluate `Measure` element reference",
                              .fields  = {
                                              {"kind", measureName(expression.kind())},
                                              {"ref", expression.ref().ShortDebugString()},
                                              {"evaluated-to", evaluatedValue(operand.value())},
                                              },
                              .expressions = {named("ref", operand.value())},
                              .notes       = {"This measure requires a geometry expression."},
                              });
    }

    double value = measuredValue(operand.value().value, expression.kind());

    return EvaluatedExpression{
        .value           = value,
        .op_name         = "Measure",
        .fields          = {{"kind", measureName(expression.kind())}},
        .sub_expressions = {named("ref", operand.value())},
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
        GeometryErrorTree{
            .message = "Cannot evaluate `Math` element reference",
            .fields
            = {{"op", mathName(expression.op())},
               {"lhs", expression.lhs().ShortDebugString()},
               {"lhs-evaluated-to", evaluatedValue(lhs)},
               {"rhs", expression.rhs().ShortDebugString()},
               {"rhs-evaluated-to", evaluatedValue(rhs)}},
            .expressions = {named("lhs", lhs), named("rhs", rhs)},
            .notes       = {reason},
        });
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
        CASE_PROTO_ENUM_SENTINEL(proto::GeometryMathOp);
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
        .value           = result,
        .op_name         = "Math",
        .fields          = {{"op", mathName(expression.op())}},
        .sub_expressions = {named("lhs", lhs), named("rhs", rhs)},
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
                .value   = value,
                .op_name = "ScalarLiteral",
            };
        }

        case proto::GeometryElementRef::Ref::kPoint: {
            Point value = Point(expression.point().x(), expression.point().y());

            return EvaluatedExpression{
                                       .value   = value,
                                       .op_name = "PointLiteral",
                                       .fields  = {
                                           {"x", fmt::format("{}", expression.point().x())},
                                           {"y", fmt::format("{}", expression.point().y())},
                                           },
                                       };
        }

        case proto::GeometryElementRef::Ref::KIND_NOT_SET:
            return expressionFailure(
                GeometryErrorTree{
                    .message = "Cannot evaluate geometry element reference",
                    .fields  = {{"expression", expression.ShortDebugString()}},
                    .notes   = {"The expression kind is not set."},
                });
    }

    return expressionFailure(
        GeometryErrorTree{
                          .message = "Cannot evaluate geometry element reference",
                          .fields  = {
                                      {"expression", expression.ShortDebugString()},
                                      {"kind", fmt::format("{}", static_cast<int>(expression.kind_case()))},
                                      },
                          .notes = {"Unhandled expression kind."},
                          });
}

hstd::Result<GeometryElementShape, GeometryError> expressionGeometry(
    EvaluatedExpression const& expression) {
    return std::visit(
        [&](auto const& value) -> hstd::Result<GeometryElementShape, GeometryError> {
            using Value = std::decay_t<decltype(value)>;

            if constexpr (std::is_same_v<Value, double>) {
                return boost::outcome_v2::failure(makeError(
                    GeometryErrorTree{
                        .message = fmt::format(
                            "Geometry element reference evaluated to scalar "
                            "`{}` where a point, rectangle, or path was required",
                            value),
                        .expressions = {named("expression", expression)},
                    }));
            } else {
                return GeometryElementShape{value};
            }
        },
        expression.value);
}

hstd::Result<EvaluatedExpression, GeometryError> expressionGeometry(
    ElementIndex const&              elements,
    proto::GeometryElementRef const& ref) {
    if (!ref.has_expr()) {
        return makeError(
            GeometryErrorTree{
                .message = "Cannot evaluate geometry operand",
                .fields  = {{"operand", ref.ShortDebugString()}},
                .notes   = {"The expression is not set."},
            });
    }

    return evaluateExpression(elements, ref.expr());
}

template <typename Shape>
hstd::Result<std::pair<Shape, EvaluatedExpression>, GeometryError> expressionGeometryType(
    ElementIndex const&              elements,
    proto::GeometryElementRef const& ref) {
    BOOST_OUTCOME_TRY(auto result, expressionGeometry(elements, ref));
    if (std::holds_alternative<Shape>(result.value)) {
        return {std::get<Shape>(result.value), result};
    } else {
        return makeError(
            GeometryErrorTree{
                .message = hstd::fmt(
                    "Cannot evaluate geometry operand to expected type {} got {}",
                    hstd::value_metadata<Shape>::typeName(),
                    hstd::variant_rutime_type_name(result.value)),
                .fields = {{"operand", ref.ShortDebugString()}},
                .notes  = {"The expression type does not match."},
            });
    }
}


template <typename Arg1, typename Arg2, typename Fn>
GeometryCheckResult runOp(
    ElementIndex const& elements,
    Arg1 const&         _arg1,
    Arg2 const&         _arg2,
    Fn&&                function) {

    BOOST_OUTCOME_TRY(auto arg1, expressionGeometry(elements, _arg1));
    BOOST_OUTCOME_TRY(auto arg2, expressionGeometry(elements, _arg2));

    auto result = std::visit(std::forward<Fn>(function), arg1.value, arg2.value);

    if (result) { return result; }

    return boost::outcome_v2::failure(makeError(
        GeometryErrorTree{
            .message = result.error().message(),
            .fields
            = {{"first", format_expression_value(arg1.value)},
               {"second", format_expression_value(arg2.value)}},
            .expressions = {named("first", arg1), named("second", arg2)},
        }));
}

template <typename Func>
struct OnlyGeometry {
    Func cb;

    GeometryCheckResult operator()(double, double) const {
        return failure("scalar-scalar not supported");
    }

    GeometryCheckResult operator()(double, auto const&) const {
        return failure("scalar-shape not supported");
    }

    GeometryCheckResult operator()(auto const&, double) const {
        return failure("shape-scalar not supported");
    }

    GeometryCheckResult operator()(
        GeometryElementShape const& arg1,
        GeometryElementShape const& arg2) const {
        return std::visit(cb, arg1, arg2);
    }
};


template <typename Func>
OnlyGeometry<Func> wrap_geometry(Func const& cb) {
    return OnlyGeometry<Func>{cb};
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
                wrap_geometry([](auto const& first, auto const& second) {
                    return checkIntersects(first, second);
                }));

        case proto::GeometryCheck::kLeftOf: {
            auto const& args = check.left_of();
            return runOp(
                elements,
                args.stationary(),
                args.relative(),
                wrap_geometry([&](auto const& stationary, auto const& relative) {
                    return checkLeftOf(
                        stationary, relative, getRtol(args), getAtol(args));
                }));
        }

        case proto::GeometryCheck::kRightOf: {
            auto const& args = check.right_of();
            return runOp(
                elements,
                args.stationary(),
                args.relative(),
                wrap_geometry([&](auto const& stationary, auto const& relative) {
                    return checkRightOf(
                        stationary, relative, getRtol(args), getAtol(args));
                }));
        }

        case proto::GeometryCheck::kAbove: {
            auto const& args = check.above();
            return runOp(
                elements,
                args.stationary(),
                args.relative(),
                wrap_geometry([&](auto const& stationary, auto const& relative) {
                    return checkAbove(stationary, relative, getRtol(args), getAtol(args));
                }));
        }

        case proto::GeometryCheck::kBelow: {
            auto const& args = check.below();
            return runOp(
                elements,
                args.stationary(),
                args.relative(),
                wrap_geometry([&](auto const& stationary, auto const& relative) {
                    return checkBelow(stationary, relative, getRtol(args), getAtol(args));
                }));
        }

        case proto::GeometryCheck::kPartiallyAbove: {
            auto const& args = check.partially_above();
            return runOp(
                elements,
                args.stationary(),
                args.relative(),
                wrap_geometry([&](auto const& stationary, auto const& relative) {
                    return checkPartiallyAbove(
                        stationary,
                        relative,
                        args.max_under_percent(),
                        getRtol(args),
                        getAtol(args));
                }));
        }

        case proto::GeometryCheck::kPartiallyBelow: {
            auto const& args = check.partially_below();
            return runOp(
                elements,
                args.stationary(),
                args.relative(),
                wrap_geometry([&](auto const& stationary, auto const& relative) {
                    return checkPartiallyBelow(
                        stationary,
                        relative,
                        args.max_over_percent(),
                        getRtol(args),
                        getAtol(args));
                }));
        }

        case proto::GeometryCheck::kPartiallyLeft: {
            auto const& args = check.partially_left();
            return runOp(
                elements,
                args.stationary(),
                args.relative(),
                wrap_geometry([&](auto const& stationary, auto const& relative) {
                    return checkPartiallyLeft(
                        stationary,
                        relative,
                        args.max_over_percent(),
                        getRtol(args),
                        getAtol(args));
                }));
        }

        case proto::GeometryCheck::kPartiallyRight: {
            auto const& args = check.partially_right();
            return runOp(
                elements,
                args.stationary(),
                args.relative(),
                wrap_geometry([&](auto const& stationary, auto const& relative) {
                    return checkPartiallyRight(
                        stationary,
                        relative,
                        args.max_over_percent(),
                        getRtol(args),
                        getAtol(args));
                }));
        }

        case proto::GeometryCheck::kFullyCovers: {
            auto const& args = check.fully_covers();
            return runOp(
                elements,
                args.main(),
                args.nested(),
                wrap_geometry([&](auto const& first, auto const& second) {
                    return checkFullyCovers(first, second, getRtol(args), getAtol(args));
                }));
        }

        case proto::GeometryCheck::kPartiallyCovers: {
            auto const& args = check.partially_covers();
            return runOp(
                elements,
                args.main(),
                args.nested(),
                wrap_geometry([&](auto const& first, auto const& second) {
                    return checkPartiallyCovers(
                        first,
                        second,
                        args.overlap_percent(),
                        getRtol(args),
                        getAtol(args));
                }));
        }

        case proto::GeometryCheck::kAlignedHorizontally: {
            auto const& args = check.aligned_horizontally();
            return runOp(
                elements,
                args.first(),
                args.second(),
                wrap_geometry([&](auto const& first, auto const& second) {
                    return checkAlignedHorizontally(
                        first, second, getTolerance(args), getRtol(args), getAtol(args));
                }));
        }

        case proto::GeometryCheck::kAlignedVertically: {
            auto const& args = check.aligned_vertically();
            return runOp(
                elements,
                args.first(),
                args.second(),
                wrap_geometry([&](auto const& first, auto const& second) {
                    return checkAlignedVertically(
                        first, second, getTolerance(args), getRtol(args), getAtol(args));
                }));
        }

        case proto::GeometryCheck::kMinDistance: {
            auto const& args = check.min_distance();
            return runOp(
                elements,
                args.first(),
                args.second(),
                wrap_geometry([&](auto const& first, auto const& second) {
                    return checkMinDistance(
                        first,
                        second,
                        args.min_distance(),
                        getDistanceCheck(args.distance_check()),
                        getRtol(args),
                        getAtol(args));
                }));
        }

        case proto::GeometryCheck::kMaxDistance: {
            auto const& args = check.max_distance();
            return runOp(
                elements,
                args.first(),
                args.second(),
                wrap_geometry([&](auto const& first, auto const& second) {
                    return checkMaxDistance(
                        first,
                        second,
                        args.max_distance(),
                        getDistanceCheck(args.distance_check()),
                        getRtol(args),
                        getAtol(args));
                }));
        }

        case proto::GeometryCheck::kDistance: {
            auto const& args = check.distance();
            return runOp(
                elements,
                args.first(),
                args.second(),
                wrap_geometry([&](auto const& first, auto const& second) {
                    return checkDistance(
                        first,
                        second,
                        args.distance(),
                        getDistanceCheck(args.distance_check()),
                        getRtol(args),
                        getAtol(args));
                }));
        }

        case proto::GeometryCheck::kRelScalar: {
            auto const& args = check.rel_scalar();
            BOOST_OUTCOME_TRY(
                auto lhs, expressionGeometryType<double>(elements, args.lhs()));
            BOOST_OUTCOME_TRY(
                auto rhs, expressionGeometryType<double>(elements, args.rhs()));

            bool close = hstd::isclose(
                lhs.first, rhs.first, getRtol(args), getAtol(args));

            switch (args.rel()) {
                CASE_PROTO_ENUM_SENTINEL(proto::GeometryMathRel);
                case proto::MATH_EQ: {
                    if (close) { return boost::outcome_v2::success(); }
                    break;
                }

                case proto::MATH_LESS: {
                    if (lhs.first < rhs.first) { return boost::outcome_v2::success(); }
                    break;
                }


                case proto::MATH_GREATER: {
                    if (lhs.first > rhs.first) { return boost::outcome_v2::success(); }
                    break;
                }

                case proto::MATH_LESS_OR_EQUAL: {
                    if (lhs.first < rhs.first || close) {
                        return boost::outcome_v2::success();
                    }
                    break;
                }


                case proto::MATH_GREATER_OR_EQUAL: {
                    if (lhs.first > rhs.first || close) {
                        return boost::outcome_v2::success();
                    }
                    break;
                }
            }


            return makeError(
                GeometryErrorTree{
                    .message = hstd::fmt("Binary math predicate failed"),
                    .fields
                    = {{"op", proto::GeometryMathRel_Name(args.rel())},
                       {"lhs", hstd::fmt("{}", lhs.first)},
                       {"rhs", hstd::fmt("{}", rhs.first)},
                       {"rtol", hstd::fmt("{}", getRtol(args))},
                       {"atol", hstd::fmt("{}", getAtol(args))}},
                    .expressions = {
                        named("lhs", lhs.second),
                        named("rhs", rhs.second),
                    }});
        }

        case proto::GeometryCheck::kSameSize: {
            auto const& args = check.same_size();
            return runOp(
                elements,
                args.first(),
                args.second(),
                wrap_geometry([&](auto const& first, auto const& second) {
                    return checkSameSize(
                        first, second, getTolerance(args), getRtol(args), getAtol(args));
                }));
        }

        case proto::GeometryCheck::kSameWidth: {
            auto const& args = check.same_width();
            return runOp(
                elements,
                args.first(),
                args.second(),
                wrap_geometry([&](auto const& first, auto const& second) {
                    return checkSameWidth(
                        first, second, getTolerance(args), getRtol(args), getAtol(args));
                }));
        }

        case proto::GeometryCheck::kSameHeight: {
            auto const& args = check.same_height();
            return runOp(
                elements,
                args.first(),
                args.second(),
                wrap_geometry([&](auto const& first, auto const& second) {
                    return checkSameHeight(
                        first, second, getTolerance(args), getRtol(args), getAtol(args));
                }));
        }

        case proto::GeometryCheck::kEquidistant: {
            auto const& args = check.equidistant();

            hstd::Vec<Rect>                  bounds;
            std::vector<EvaluatedExpression> trees;
            bounds.reserve(args.elements_size());
            trees.reserve(args.elements_size());

            for (int index = 0; index < args.elements_size(); ++index) {
                auto const& reference = args.elements(index);

                if (!reference.has_expr()) {
                    return boost::outcome_v2::failure(makeError(
                        GeometryErrorTree{
                            .message = fmt::format(
                                "Cannot evaluate equidistant operand {}", index),
                            .fields = {{"operand", reference.ShortDebugString()}},
                            .notes  = {"The expression is not set."},
                        }));
                }

                auto expression = evaluateExpression(elements, reference.expr());

                if (!expression) {
                    return boost::outcome_v2::failure(expression.error());
                }

                auto itemBounds = expressionBounds(expression.value().value);

                if (!itemBounds) {
                    return boost::outcome_v2::failure(makeError(
                        GeometryErrorTree{
                            .message = fmt::format(
                                "Cannot evaluate equidistant operand {}", index),
                            .fields
                            = {{"operand", reference.ShortDebugString()},
                               {"evaluated-to", evaluatedValue(expression.value())}},
                            .expressions = {named(
                                fmt::format("elements[{}]", index), expression.value())},
                            .notes = {"Expected a point, rectangle, or path expression."},
                        }));
                }

                bounds.push_back(itemBounds.value());
                trees.push_back(
                    named(fmt::format("elements[{}]", index), expression.value()));
            }

            auto result = detail::checkEquidistantBounds(bounds, getTolerance(args));

            if (result) { return result; }

            return boost::outcome_v2::failure(makeError(
                GeometryErrorTree{
                    .message     = result.error().message(),
                    .expressions = std::move(trees),
                }));
        }


        case proto::GeometryCheck::CHECK_NOT_SET:
            return failure("Geometry check does not define a check kind");
    }

    return failure("Unhandled geometry check kind");
}

GeometryCheckResult appendContext(
    GeometryCheckResult         result,
    proto::GeometryCheck const& check,
    int                         checkIndex) {
    if (result) { return result; }

    return boost::outcome_v2::failure(
        makeError(
            GeometryErrorTree{
                              .message = result.error().message(),
                              .fields  = {
                                  {"check-index", fmt::format("{}", checkIndex)},
                                  {"check-id", check.id()},
                                  {"check-spec", check.ShortDebugString()},
                                  },
                              }));
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
                .result     = appendContext(std::move(result), check, checkIndex),
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
