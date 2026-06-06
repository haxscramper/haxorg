#include "kiwi_ir.hpp"

#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <hstd/ext/graph/visual/graph_graphviz.hpp>
#include <hstd/stdlib/Enumerate.hpp>

namespace hstd::ext ::kiwi_ir {

double kiwi_value(Strength strength) {
    switch (strength) {
        case Strength::REQUIRED: return kiwi::strength::required;
        case Strength::STRONG: return kiwi::strength::strong;
        case Strength::MEDIUM: return kiwi::strength::medium;
        case Strength::WEAK: return kiwi::strength::weak;
    }
    throw std::runtime_error("Unknown strength");
}

Axis anchor_axis(Anchor anchor) {
    if (anchor == Anchor::LEFT || anchor == Anchor::HCENTER
        || anchor == Anchor::RIGHT) {
        return Axis::X;
    } else {
        return Axis::Y;
    }
}

Str axis_color(Axis axis) {
    if (axis == Axis::X) {
        return "red";
    } else {
        return "blue";
    }
}


Expr::Expr(std::shared_ptr<Node const> node) : node(std::move(node)) {}

std::shared_ptr<Expr::Node const> Expr::make_constant(double value) {
    Node n;
    n.kind     = Node::Kind::Constant;
    n.constant = value;
    return std::make_shared<Node>(std::move(n));
}

std::shared_ptr<Expr::Node const> Expr::make_variable(
    kiwi::Variable const& value) {
    Node n;
    n.kind     = Node::Kind::Variable;
    n.variable = value;
    return std::make_shared<Node>(std::move(n));
}

std::shared_ptr<Expr::Node const> Expr::make_kiwi_expr(
    kiwi::Expression const& value) {
    Node n;
    n.kind      = Node::Kind::KiwiExpression;
    n.kiwi_expr = value;
    return std::make_shared<Node>(std::move(n));
}

std::shared_ptr<Expr::Node const> Expr::make_unary(
    Node::Kind                  kind,
    std::shared_ptr<Node const> lhs) {
    Node n;
    n.kind = kind;
    n.lhs  = std::move(lhs);
    return std::make_shared<Node>(std::move(n));
}

std::shared_ptr<Expr::Node const> Expr::make_binary(
    Node::Kind                  kind,
    std::shared_ptr<Node const> lhs,
    std::shared_ptr<Node const> rhs) {
    Node n;
    n.kind = kind;
    n.lhs  = std::move(lhs);
    n.rhs  = std::move(rhs);
    return std::make_shared<Node>(std::move(n));
}

Expr::Expr(double value) : node(make_constant(value)) {}
Expr::Expr(kiwi::Variable const& value) : node(make_variable(value)) {}
Expr::Expr(kiwi::Expression const& value) : node(make_kiwi_expr(value)) {}

Expr Expr::operator+(Expr const& other) const {
    return Expr(make_binary(Node::Kind::Add, node, other.node));
}

Expr Expr::operator-(Expr const& other) const {
    return Expr(make_binary(Node::Kind::Sub, node, other.node));
}

Expr Expr::operator*(double other) const {
    return Expr(make_binary(Node::Kind::Mul, node, make_constant(other)));
}

Expr Expr::operator-() const {
    return Expr(make_unary(Node::Kind::Neg, node));
}

Expr Expr::operator*(Expr const& other) const {
    return Expr(make_binary(Node::Kind::Mul, node, other.node));
}

Constraint Expr::operator==(Expr const& other) const {
    return Constraint(*this, other, kiwi::RelationalOperator::OP_EQ);
}

Constraint Expr::operator<=(Expr const& other) const {
    return Constraint(*this, other, kiwi::RelationalOperator::OP_LE);
}

Constraint Expr::operator>=(Expr const& other) const {
    return Constraint(*this, other, kiwi::RelationalOperator::OP_GE);
}

Constraint::Constraint(
    Expr const&              lhs,
    Expr const&              rhs,
    kiwi::RelationalOperator op)
    : lhs(lhs), rhs(rhs), op(op) {}

kiwi::Expression Constraint::fold_expr(
    std::shared_ptr<Expr::Node const> const& node) {
    using Kind = Expr::Node::Kind;
    switch (node->kind) {
        case Kind::Constant: return kiwi::Expression(node->constant);
        case Kind::Variable: return kiwi::Expression(*node->variable);
        case Kind::KiwiExpression: return *node->kiwi_expr;
        case Kind::Add: return fold_expr(node->lhs) + fold_expr(node->rhs);
        case Kind::Sub: return fold_expr(node->lhs) - fold_expr(node->rhs);
        case Kind::Neg: return -fold_expr(node->lhs);
        case Kind::Mul: {
            kiwi::Expression left  = fold_expr(node->lhs);
            kiwi::Expression right = fold_expr(node->rhs);

            bool left_const  = left.terms().empty();
            bool right_const = right.terms().empty();

            if (left_const && right_const) {
                return kiwi::Expression(
                    left.constant() * right.constant());
            } else if (left_const) {
                return right * left.constant();
            } else if (right_const) {
                return left * right.constant();
            }

            throw std::runtime_error(
                "Kiwi supports only linear expressions");
        }
    }

    throw std::runtime_error("Invalid expression node");
}

kiwi::Constraint Constraint::to_kiwi(hstd::Opt<double> str) const {
    kiwi::Expression left  = fold_expr(lhs.node);
    kiwi::Expression right = fold_expr(rhs.node);

    auto s = strength ? strength : str;

    switch (op) {
        case kiwi::RelationalOperator::OP_EQ:
            return s ? left == right | s.value() : left == right;
        case kiwi::RelationalOperator::OP_LE:
            return s ? left <= right | s.value() : left <= right;
        case kiwi::RelationalOperator::OP_GE:
            return s ? right <= left | s.value() : right <= left;
    }

    throw std::runtime_error("Invalid relational operator");
}

Expr operator+(double left, Expr const& right) {
    return Expr(left) + right;
}

Expr operator-(double left, Expr const& right) {
    return Expr(left) - right;
}

Expr operator*(double left, Expr const& right) { return right * left; }

Rect::Rect(
    Str         rect_id,
    Opt<double> x0,
    Opt<double> y0,
    Opt<double> width0,
    Opt<double> height0)
    : rect_id(std::move(rect_id))
    , x0(x0)
    , y0(y0)
    , width0(width0)
    , height0(height0)
    , x(std::format("{}.x", this->rect_id))
    , y(std::format("{}.y", this->rect_id))
    , width(std::format("{}.width", this->rect_id))
    , height(std::format("{}.height", this->rect_id)) {}

Expr Rect::expr(RectAttr name) const {
    switch (name) {
        case RectAttr::X: return Expr(x);
        case RectAttr::Y: return Expr(y);
        case RectAttr::WIDTH: return Expr(width);
        case RectAttr::HEIGHT: return Expr(height);
        case RectAttr::LEFT:
            return Expr(x);
            // TODO: See [[kiwi-arbitrary-anchor-positions]]
        case RectAttr::HCENTER: return Expr(x) + 0.5 * Expr(width);
        case RectAttr::RIGHT: return Expr(x) + Expr(width);
        case RectAttr::TOP: return Expr(y);
        case RectAttr::VCENTER: return Expr(y) + 0.5 * Expr(height);
        case RectAttr::BOTTOM: return Expr(y) + Expr(height);
    }
    throw std::runtime_error("Invalid RectAttr");
}

Expr Rect::anchor_expr(Anchor anchor) const {
    switch (anchor) {
        case Anchor::LEFT: return expr(RectAttr::LEFT);
        case Anchor::HCENTER: return expr(RectAttr::HCENTER);
        case Anchor::RIGHT: return expr(RectAttr::RIGHT);
        case Anchor::TOP: return expr(RectAttr::TOP);
        case Anchor::VCENTER: return expr(RectAttr::VCENTER);
        case Anchor::BOTTOM: return expr(RectAttr::BOTTOM);
        default: throw std::runtime_error("Invalid Anchor");
    }
}

ConstraintBase::ConstraintBase(Strength strength) : strength(strength) {}

Vec<Str> ConstraintBase::getBuildRepr(
    hstd::Opt<RectMap> const& rects) const {
    Vec<Str> joined;
    if (rects) {
        for (auto const& c : build(rects.value())) {
            joined.append(flat_repr(c).split("\n"));
        }
    }
    return joined;
}

AlignConstraint::AlignConstraint(Vec<AlignItem> items, Strength strength)
    : ConstraintBase(strength), items(std::move(items)) {}

Vec<kiwi_ir::Constraint> AlignConstraint::build(
    RectMap const& rects) const {
    if (items.size() < 2) {
        throw std::runtime_error(
            "AlignConstraint requires at least 2 items");
    }
    auto const& base = items[0];
    Expr base_expr   = rects.at(base.rect_id).anchor_expr(base.spec.anchor)
                     - base.spec.offset;
    Vec<kiwi_ir::Constraint> result;
    for (int i = 1; i < items.size(); ++i) {
        auto const& item = items[i];
        Expr expr = rects.at(item.rect_id).anchor_expr(item.spec.anchor)
                  - item.spec.offset;
        result.push_back((expr == base_expr) | kiwi_value(strength));
    }
    return result;
}

Vec<EdgeDesc> AlignConstraint::describe_edges() const {
    Vec<EdgeDesc> edges;
    Str           base = items[0].rect_id;
    for (int i = 1; i < items.size(); ++i) {
        auto const& item = items[i];
        edges.push_back(
            EdgeDesc{
                base,
                item.rect_id,
                std::format("align:{}", item.spec.anchor),
                anchor_axis(item.spec.anchor)});
    }
    return edges;
}

Str AlignConstraint::getRepr(hstd::Opt<RectMap> const& rects) const {
    Vec<Str> joined;
    joined.push_back(hstd::fmt("AlignConstraint strength={}", strength));
    for (auto const& item : items) {
        joined.push_back(
            std::format(
                "  {} {} ({:+g})",
                item.rect_id,
                item.spec.anchor,
                item.spec.offset));
    }

    joined.append(getBuildRepr(rects));

    return hstd::join("\n", joined);
}

SeparateConstraint::SeparateConstraint(
    Str      first_rect_id,
    Anchor   first_anchor,
    Str      second_rect_id,
    Anchor   second_anchor,
    double   offset,
    Strength strength)
    : ConstraintBase(strength)
    , first_rect_id(std::move(first_rect_id))
    , first_anchor(first_anchor)
    , second_rect_id(std::move(second_rect_id))
    , second_anchor(second_anchor)
    , offset(offset) {}

Vec<kiwi_ir::Constraint> SeparateConstraint::build(
    RectMap const& rects) const {
    Expr first  = rects.at(first_rect_id).anchor_expr(first_anchor);
    Expr second = rects.at(second_rect_id).anchor_expr(second_anchor);
    kiwi_ir::Constraint c = (first == (second + offset))
                          | kiwi_value(strength);
    return {c};
}

Vec<EdgeDesc> SeparateConstraint::describe_edges() const {
    return {EdgeDesc{
        second_rect_id,
        first_rect_id,
        std::format(
            "separate:{}->{}+{}", second_anchor, first_anchor, offset),
        anchor_axis(first_anchor)}};
}

Str SeparateConstraint::getRepr(hstd::Opt<RectMap> const& rects) const {
    return std::format(
        "SeparateConstraint({}.{} == {}.{} + {:g}, strength={})",
        first_rect_id,
        first_anchor,
        second_rect_id,
        second_anchor,
        offset,
        strength);
}

MultiSeparateConstraint::MultiSeparateConstraint(
    Vec<Vec<Str>> groups,
    Anchor        anchor,
    double        step,
    Strength      strength)
    : ConstraintBase(strength)
    , groups(std::move(groups))
    , anchor(anchor)
    , step(step) {}

Vec<kiwi_ir::Constraint> MultiSeparateConstraint::build(
    RectMap const& rects) const {
    Vec<kiwi_ir::Constraint> constraints;
    for (int idx = 0; idx + 1 < groups.size(); ++idx) {
        auto const& g1 = groups[idx];
        auto const& g2 = groups[idx + 1];
        if (g1.empty() || g2.empty()) { continue; }
        if (g1.size() != g2.size()) {
            throw std::runtime_error(
                "MultiSeparateConstraint requires corresponding group "
                "sizes");
        }
        for (int i = 0; i < g1.size(); ++i) {
            auto const& a      = g1[i];
            auto const& b      = g2[i];
            Expr        expr_a = rects.at(b).anchor_expr(anchor);
            Expr        expr_b = rects.at(a).anchor_expr(anchor);
            constraints.push_back(
                (expr_a == (expr_b + step)) | kiwi_value(strength));
        }
    }
    return constraints;
}

Vec<EdgeDesc> MultiSeparateConstraint::describe_edges() const {
    Vec<EdgeDesc> edges;
    for (int idx = 0; idx + 1 < groups.size(); ++idx) {
        auto const& g1    = groups[idx];
        auto const& g2    = groups[idx + 1];
        int         count = std::min(g1.size(), g2.size());
        for (int i = 0; i < count; ++i) {
            edges.push_back(
                EdgeDesc{
                    g1[i],
                    g2[i],
                    std::format("multi-separate:{}+{:g}", anchor, step),
                    anchor_axis(anchor)});
        }
    }
    return edges;
}

Str MultiSeparateConstraint::getRepr(
    hstd::Opt<RectMap> const& rects) const {
    std::ostringstream out;
    out << "[";
    for (int i = 0; i < groups.size(); ++i) {
        out << "[";
        for (int j = 0; j < groups[i].size(); ++j) {
            out << groups[i][j];
            if (j + 1 < groups[i].size()) { out << ", "; }
        }
        out << "]";
        if (i + 1 < groups.size()) { out << ", "; }
    }
    out << "]";
    return std::format(
        "MultiSeparateConstraint(anchor={}, step={:g}, groups={}, "
        "strength={})",
        anchor,
        step,
        out.str(),
        strength);
}

ParentWrapConstraint::ParentWrapConstraint(
    Str                      parent_rect_id,
    Vec<Str>                 nested_rect_ids,
    geometry::Padding const& pad,
    Strength                 strength)
    : ConstraintBase(strength)
    , parent_rect_id(std::move(parent_rect_id))
    , nested_rect_ids(std::move(nested_rect_ids))
    , pad{pad} {}

Vec<kiwi_ir::Constraint> ParentWrapConstraint::build(
    RectMap const& rects) const {
    if (nested_rect_ids.empty()) { return {}; }

    Rect const&              parent = rects.at(parent_rect_id);
    Vec<kiwi_ir::Constraint> constraints;

    Vec<Expr> left_exprs;
    Vec<Expr> top_exprs;
    Vec<Expr> right_exprs;
    Vec<Expr> bottom_exprs;

    for (auto const& nested_id : nested_rect_ids) {
        left_exprs.push_back(
            rects.at(nested_id).anchor_expr(Anchor::LEFT));
        top_exprs.push_back(rects.at(nested_id).anchor_expr(Anchor::TOP));
        right_exprs.push_back(
            rects.at(nested_id).anchor_expr(Anchor::RIGHT));
        bottom_exprs.push_back(
            rects.at(nested_id).anchor_expr(Anchor::BOTTOM));
    }

    for (auto const& nested_left : left_exprs) {
        constraints.push_back(
            (parent.anchor_expr(Anchor::LEFT) <= (nested_left - pad.left))
            | kiwi_value(strength));
    }

    for (auto const& nested_top : top_exprs) {
        constraints.push_back(
            (parent.anchor_expr(Anchor::TOP) <= (nested_top - pad.top))
            | kiwi_value(strength));
    }

    for (auto const& nested_right : right_exprs) {
        constraints.push_back(
            ((nested_right + pad.right)
             <= parent.anchor_expr(Anchor::RIGHT))
            | kiwi_value(strength));
    }

    for (auto const& nested_bottom : bottom_exprs) {
        constraints.push_back(
            ((nested_bottom + pad.bottom)
             <= parent.anchor_expr(Anchor::BOTTOM))
            | kiwi_value(strength));
    }

    constraints.push_back(
        (parent.anchor_expr(Anchor::LEFT) == (left_exprs[0] - pad.left))
        | kiwi_value(strength));
    constraints.push_back(
        (parent.anchor_expr(Anchor::TOP) == (top_exprs[0] - pad.top))
        | kiwi_value(strength));
    constraints.push_back(
        (parent.anchor_expr(Anchor::RIGHT)
         == (right_exprs[right_exprs.size() - 1] + pad.right))
        | kiwi_value(strength));
    constraints.push_back(
        (parent.anchor_expr(Anchor::BOTTOM)
         == (bottom_exprs[bottom_exprs.size() - 1] + pad.bottom))
        | kiwi_value(strength));

    return constraints;
}

Vec<EdgeDesc> ParentWrapConstraint::describe_edges() const {
    Vec<EdgeDesc> edges;
    for (auto const& nested_id : nested_rect_ids) {
        edges.push_back(
            EdgeDesc{nested_id, parent_rect_id, "wrap-parent-x", Axis::X});
        edges.push_back(
            EdgeDesc{nested_id, parent_rect_id, "wrap-parent-y", Axis::Y});
    }
    return edges;
}

Str ParentWrapConstraint::getRepr(hstd::Opt<RectMap> const& rects) const {
    std::ostringstream nested;
    nested << "[";
    for (int i = 0; i < nested_rect_ids.size(); ++i) {
        nested << nested_rect_ids[i];
        if (i + 1 < nested_rect_ids.size()) { nested << ", "; }
    }
    nested << "]";
    return std::format(
        "ParentWrapConstraint(parent={}, nested={}, padding={}, "
        "strength={})",
        parent_rect_id,
        nested.str(),
        pad,
        strength);
}

RelativeConstraint::RelativeConstraint(
    Str              relative_rect_id,
    Str              parent_rect_id,
    RelDimensionSpec x_dim,
    RelDimensionSpec y_dim,
    AnchorSpec       anchor_relative,
    AnchorSpec       anchor_fixed,
    Strength         strength)
    : ConstraintBase(strength)
    , relative_rect_id(std::move(relative_rect_id))
    , fixed_rect_id(std::move(parent_rect_id))
    , x_dim(x_dim)
    , y_dim(y_dim)
    , anchor_relative(anchor_relative)
    , anchor_fixed(anchor_fixed) {}

Vec<kiwi_ir::Constraint> RelativeConstraint::build(
    RectMap const& rects) const {
    Rect const&              rel = rects.at(relative_rect_id);
    Rect const&              fix = rects.at(fixed_rect_id);
    Vec<kiwi_ir::Constraint> constraints;

    if (x_dim.size_factor.has_value()) {
        constraints.push_back(
            (rel.expr(RectAttr::WIDTH)
             == (fix.expr(RectAttr::WIDTH) * x_dim.size_factor.value()))
            | kiwi_value(strength));
    }

    if (y_dim.size_factor.has_value()) {
        constraints.push_back(
            (rel.expr(RectAttr::HEIGHT)
             // TODO: See [[configurable-offset-comparison-directions]]
             == (fix.expr(RectAttr::HEIGHT) * y_dim.size_factor.value()))
            | kiwi_value(strength));
    }

    if (x_dim.relative_offset) {
        constraints.push_back(
            (rel.anchor_expr(anchor_relative.x)
             == (fix.anchor_expr(anchor_fixed.x)
                 // TODO: NOTE: It would be better to create another IR to
                 // store the expression in a more inspect-able manner and
                 // defer the conversion to KIWI until the very last
                 // moment. The expression would have a more tree-like
                 // structure to capture all additional structureal
                 // information and simplify the debugging.
                 + (x_dim.relative_offset.value()
                    * fix.expr(RectAttr::WIDTH))
                 + x_dim.absolute_offset))
            | kiwi_value(strength));

    } else {
        constraints.push_back(
            (rel.anchor_expr(anchor_relative.x)
             == (fix.anchor_expr(anchor_fixed.x) + x_dim.absolute_offset))
            | kiwi_value(strength));
    }

    if (y_dim.relative_offset) {
        constraints.push_back(
            (rel.anchor_expr(anchor_relative.y)
             == (fix.anchor_expr(anchor_fixed.y)
                 + (y_dim.relative_offset.value()
                    * fix.expr(RectAttr::HEIGHT))
                 + y_dim.absolute_offset))
            | kiwi_value(strength));
    } else {
        constraints.push_back(
            (rel.anchor_expr(anchor_relative.y)
             == (fix.anchor_expr(anchor_fixed.y) + y_dim.absolute_offset))
            | kiwi_value(strength));
    }


    return constraints;
}

Vec<EdgeDesc> RelativeConstraint::describe_edges() const {
    // FIXME: Update the edge description for relative constraint based on
    // the relative element positions.
    Vec<EdgeDesc> edges = {
        EdgeDesc{fixed_rect_id, relative_rect_id, "relative-x", Axis::X},
        EdgeDesc{fixed_rect_id, relative_rect_id, "relative-y", Axis::Y},
    };

    // if (x_factor.has_value()) {
    //     edges.push_back(
    //         EdgeDesc{
    //             fixed_rect_id, relative_rect_id, "relative-width",
    //             "red"});
    // }

    // if (y_factor.has_value()) {
    //     edges.push_back(
    //         EdgeDesc{
    //             fixed_rect_id,
    //             relative_rect_id,
    //             "relative-height",
    //             "blue"});
    // }

    return edges;
}

Str RelativeConstraint::getRepr(hstd::Opt<RectMap> const& rects) const {
    // FIXME: implement repr for relative constraint.
    Vec<Str> joined;
    joined.push_back(
        hstd::fmt(
            "RelativeConstraint fixed:{} relative:{}",
            fixed_rect_id,
            relative_rect_id));

    joined.push_back(hstd::fmt("  x_dim           {}", x_dim));
    joined.push_back(hstd::fmt("  y_dim           {}", y_dim));
    joined.push_back(hstd::fmt("  anchor_fixed    {}", anchor_fixed));
    joined.push_back(hstd::fmt("  anchor_relative {}", anchor_relative));
    joined.append(getBuildRepr(rects));

    return hstd::join("\n", joined);

    // Str wf = x_factor.has_value() ? std::format("{:g}",
    // x_factor.value())
    //                               : "None";
    // Str hf = y_factor.has_value() ? std::format("{:g}",
    // y_factor.value())
    //                               : "None";
    // return std::format(
    //     "nestedRelativeToParentConstraint(nested={}, parent={}, "
    //     "width_factor={}, height_factor={}, x={}->{}{:+g},
    //     y={}->{}{:+g}, " "strength={})", relative_rect_id,
    //     fixed_rect_id,
    //     wf,
    //     hf,
    //     nested_x_anchor,
    //     x_anchor,
    //     x_offset,
    //     nested_y_anchor,
    //     y_anchor,
    //     y_offset,
    //     strength);
}

EvenGapConstraint::EvenGapConstraint(
    Vec<Str> rect_ids,
    Axis     axis,
    Anchor   anchor,
    Strength strength)
    : ConstraintBase(strength)
    , rect_ids(std::move(rect_ids))
    , axis(axis)
    , anchor(anchor) {}

Vec<kiwi_ir::Constraint> EvenGapConstraint::build(
    RectMap const& rects) const {
    if (rect_ids.size() < 3) { return {}; }
    Vec<kiwi_ir::Constraint> constraints;
    for (int i = 1; i + 1 < rect_ids.size(); ++i) {
        Expr a = rects.at(rect_ids[i - 1]).anchor_expr(anchor);
        Expr b = rects.at(rect_ids[i]).anchor_expr(anchor);
        Expr c = rects.at(rect_ids[i + 1]).anchor_expr(anchor);
        constraints.push_back(
            (((b - a) - (c - b)) == 0) | kiwi_value(strength));
    }
    return constraints;
}

Vec<EdgeDesc> EvenGapConstraint::describe_edges() const {
    Vec<EdgeDesc> result;
    for (int i = 0; i + 1 < rect_ids.size(); ++i) {
        result.push_back(
            EdgeDesc{
                rect_ids[i],
                rect_ids[i + 1],
                std::format("even-gap:{}", anchor),
                axis});
    }
    return result;
}

Str EvenGapConstraint::getRepr(hstd::Opt<RectMap> const& rects) const {
    std::ostringstream out;
    out << "[";
    for (int i = 0; i < rect_ids.size(); ++i) {
        out << rect_ids[i];
        if (i + 1 < rect_ids.size()) { out << ", "; }
    }
    out << "]";
    return std::format(
        "EvenGapConstraint(rect_ids={}, axis={}, anchor={}, strength={})",
        out.str(),
        axis,
        anchor,
        strength);
}

EqualSizeConstraint::EqualSizeConstraint(
    Str      rect_a_id,
    Str      rect_b_id,
    bool     match_width,
    bool     match_height,
    Strength strength)
    : ConstraintBase(strength)
    , rect_a_id(std::move(rect_a_id))
    , rect_b_id(std::move(rect_b_id))
    , match_width(match_width)
    , match_height(match_height) {}

Vec<kiwi_ir::Constraint> EqualSizeConstraint::build(
    RectMap const& rects) const {
    Rect const&              a = rects.at(rect_a_id);
    Rect const&              b = rects.at(rect_b_id);
    Vec<kiwi_ir::Constraint> constraints;
    if (match_width) {
        constraints.push_back(
            (a.expr(RectAttr::WIDTH) == b.expr(RectAttr::WIDTH))
            | kiwi_value(strength));
    }
    if (match_height) {
        constraints.push_back(
            (a.expr(RectAttr::HEIGHT) == b.expr(RectAttr::HEIGHT))
            | kiwi_value(strength));
    }
    return constraints;
}

Vec<EdgeDesc> EqualSizeConstraint::describe_edges() const {
    Vec<EdgeDesc> edges;
    if (match_width) {
        edges.push_back(
            EdgeDesc{rect_a_id, rect_b_id, "equal-size:width", Axis::X});
    }
    if (match_height) {
        edges.push_back(
            EdgeDesc{rect_a_id, rect_b_id, "equal-size:height", Axis::Y});
    }
    return edges;
}

Str EqualSizeConstraint::getRepr(hstd::Opt<RectMap> const& rects) const {
    return std::format(
        "EqualSizeConstraint(a={}, b={}, match_width={}, match_height={}, "
        "strength={})",
        rect_a_id,
        rect_b_id,
        match_width,
        match_height,
        strength);
}

LinearConstraint::LinearConstraint(
    Expr     left,
    Relation relation,
    Expr     right,
    Strength strength)
    : ConstraintBase(strength)
    , left(std::move(left))
    , relation(relation)
    , right(std::move(right)) {}

Vec<kiwi_ir::Constraint> LinearConstraint::build(RectMap const&) const {
    kiwi_ir::Constraint c = (left == right) | kiwi_value(strength);
    if (relation == Relation::EQ) {
        c = (left == right) | kiwi_value(strength);
    } else if (relation == Relation::LE) {
        c = (left <= right) | kiwi_value(strength);
    } else if (relation == Relation::GE) {
        c = (right <= left) | kiwi_value(strength);
    } else {
        throw std::runtime_error("Invalid relation");
    }
    return {c};
}

Vec<EdgeDesc> LinearConstraint::describe_edges() const { return {}; }

Str LinearConstraint::getRepr(hstd::Opt<RectMap> const& rects) const {
    Str rel = relation == Relation::EQ
                ? "=="
                : (relation == Relation::LE ? "<=" : ">=");
    return std::format(
        "LinearConstraint({} ..., strength={})", rel, strength);
}

Layout::Layout(
    Vec<Rect>                       rects,
    Vec<hstd::SPtr<ConstraintBase>> constraints)
    : constraints(std::move(constraints)) {
    for (auto& rect : rects) { this->rects.emplace(rect.rect_id, rect); }
}

RectMap Layout::solve() {
    kiwi::Solver solver;

    for (auto& [rect_id, rect] : rects) {
        solver.addConstraint(((Expr(0) <= rect.expr(RectAttr::WIDTH)))
                                 .to_kiwi(kiwi::strength::required));
        solver.addConstraint(((Expr(0) <= rect.expr(RectAttr::HEIGHT)))
                                 .to_kiwi(kiwi::strength::required));

        if (rect.x0.has_value()) {
            solver.addConstraint(
                (rect.expr(RectAttr::X) == rect.x0.value())
                    .to_kiwi(kiwi::strength::required));
        }
        if (rect.y0.has_value()) {
            solver.addConstraint(
                (rect.expr(RectAttr::Y) == rect.y0.value())
                    .to_kiwi(kiwi::strength::required));
        }
        if (rect.width0.has_value()) {
            solver.addConstraint(
                (rect.expr(RectAttr::WIDTH) == rect.width0.value())
                    .to_kiwi(kiwi::strength::required));
        }
        if (rect.height0.has_value()) {
            solver.addConstraint(
                (rect.expr(RectAttr::HEIGHT) == rect.height0.value())
                    .to_kiwi(kiwi::strength::required));
        }
    }

    for (auto const& item : constraints) {
        for (auto const& c : item->build(rects)) {
            solver.addConstraint(c.to_kiwi());
        }
    }

    solver.updateVariables();
    return rects;
}

namespace {
namespace bg = boost::geometry;
Vec<std::pair<Str, Rect>> sort_rectangles_for_svg(
    Vec<std::pair<Str, Rect>> const& items) {

    using Graph = boost::
        adjacency_list<boost::vecS, boost::vecS, boost::directedS>;
    using Vertex = boost::graph_traits<Graph>::vertex_descriptor;

    auto to_box = [](Rect const& g) -> geometry::Rect {
        return geometry::Rect{
            geometry::Point{g.x.value(), g.y.value()},
            geometry::Point{
                g.x.value() + g.width.value(),
                g.y.value() + g.height.value()}};
    };

    auto area = [](Rect const& g) -> double {
        return g.width.value() * g.height.value();
    };

    auto overlap_area = [&](Rect const& a, Rect const& b) -> double {
        geometry::Rect out;
        bg::intersection(to_box(a), to_box(b), out);
        return bg::area(out);
    };

    auto contains = [&](Rect const& outer, Rect const& inner) -> bool {
        return bg::covered_by(to_box(inner), to_box(outer));
    };

    auto top  = [](Rect const& g) { return g.y.value(); };
    auto left = [](Rect const& g) { return g.x.value(); };

    auto prefer_before = [&](int lhs, int rhs) -> bool {
        Rect const& a = items[lhs].second;
        Rect const& b = items[rhs].second;

        if (area(a) != area(b)) { return area(a) > area(b); }
        if (top(a) != top(b)) { return top(a) < top(b); }
        if (left(a) != left(b)) { return left(a) < left(b); }
        return items[lhs].first < items[rhs].first;
    };

    Graph g(items.size());

    for (int i = 0; i < items.size(); ++i) {
        Rect const& ri = items[i].second;

        for (int j = i + 1; j < items.size(); ++j) {
            Rect const& rj = items[j].second;

            double const ov = overlap_area(ri, rj);
            if (ov <= 0) { continue; }

            bool const i_contains_j = contains(ri, rj);
            bool const j_contains_i = contains(rj, ri);

            if (i_contains_j && !j_contains_i) {
                boost::add_edge(
                    static_cast<Vertex>(i), static_cast<Vertex>(j), g);
                continue;
            }

            if (j_contains_i && !i_contains_j) {
                boost::add_edge(
                    static_cast<Vertex>(j), static_cast<Vertex>(i), g);
                continue;
            }

            if (prefer_before(i, j)) {
                boost::add_edge(
                    static_cast<Vertex>(i), static_cast<Vertex>(j), g);
            } else {
                boost::add_edge(
                    static_cast<Vertex>(j), static_cast<Vertex>(i), g);
            }
        }
    }

    Vec<Vertex> topo;
    try {
        boost::topological_sort(g, std::back_inserter(topo));
    } catch (boost::not_a_dag const&) {
        Vec<int> idx(items.size());
        for (int i = 0; i < items.size(); ++i) { idx[i] = i; }

        std::ranges::sort(idx, [&](int lhs, int rhs) {
            return prefer_before(lhs, rhs);
        });

        Vec<std::pair<Str, Rect>> result;
        result.reserve(items.size());
        for (int i : idx) { result.push_back(items[i]); }
        return result;
    }

    std::ranges::reverse(topo);

    Vec<std::pair<Str, Rect>> result;
    result.reserve(items.size());
    for (Vertex v : topo) { result.push_back(items[static_cast<int>(v)]); }

    return result;
}
} // namespace

hstd::XmlNode Layout::to_svg(Str const& title) {
    auto   solved = solve();
    double max_x  = solved.empty() ? 100.0 : 0.0;
    double max_y  = solved.empty() ? 100.0 : 0.0;

    if (!solved.empty()) {
        for (auto const& [rect_id, g] : solved) {
            max_x = std::max(max_x, g.x.value() + g.width.value());
            max_y = std::max(max_y, g.y.value() + g.height.value());
        }
    }

    hstd::XmlNode svg("svg");
    svg.set_attr("xmlns", "http://www.w3.org/2000/svg");
    svg.set_attr("width", max_x + 40);
    svg.set_attr("height", max_y + 40);

    hstd::XmlNode bg("rect");
    bg.set_attr("x", 0);
    bg.set_attr("y", 0);
    bg.set_attr("width", max_x + 40);
    bg.set_attr("height", max_y + 40);
    bg.set_attr("fill", "white");
    svg.push_back(std::move(bg));

    hstd::XmlNode titleNode("text");
    titleNode.set_attr("x", 10);
    titleNode.set_attr("y", 18);
    titleNode.set_attr("fill", "black");
    titleNode.set_attr("font-size", "14px");
    titleNode.set_text(title);
    svg.push_back(std::move(titleNode));

    Vec<Str> colors = {
        "#ffcccc", "#ccffcc", "#ccccff", "#fff0cc", "#f0ccff", "#ccfff7"};

    int idx = 0;

    Vec<std::pair<Str, Rect>> items{solved.begin(), solved.end()};
    auto                      ordered = sort_rectangles_for_svg(items);

    for (auto const& [rect_id, g] : ordered) {
        Str color = colors[idx % colors.size()];

        hstd::XmlNode rectNode("rect");
        rectNode.set_attr("x", g.x.value() + 20);
        rectNode.set_attr("y", g.y.value() + 20);
        rectNode.set_attr("width", g.width.value());
        rectNode.set_attr("height", g.height.value());
        rectNode.set_attr("fill", color);
        rectNode.set_attr("stroke", "black");
        svg.push_back(std::move(rectNode));

        hstd::XmlNode textNode("text");
        textNode.set_attr("x", g.x.value() + 24);
        textNode.set_attr("y", g.y.value() + 36);
        textNode.set_attr("fill", "black");
        textNode.set_attr("font-size", "12px");
        textNode.set_text(rect_id);
        svg.push_back(std::move(textNode));

        ++idx;
    }

    return svg;
}

void Layout::to_graphviz(hstd::fs::path const& path) {
    std::filesystem::create_directories(path.parent_path());

    auto result = graph::gv::GraphGroup::newStandaloneRootGraph("G");
    std::unordered_map<Str, hstd::SPtr<graph::gv::NodeAttribute>>
        rectNodes;

    for (auto const& [rect_id, rect] : rects) {
        auto node = result->node(std::format("rect-{}", rect_id));
        hstd::Vec<Str> rect_info;
        rect_info.push_back(rect_id);
        if (rect.x0) {
            rect_info.push_back(hstd::fmt("  x0 {}", rect.x0.value()));
        }

        if (rect.y0) {
            rect_info.push_back(hstd::fmt("  y0 {}", rect.y0.value()));
        }

        if (rect.width0) {
            rect_info.push_back(
                hstd::fmt("  width0  {}", rect.width0.value()));
        }

        if (rect.height0) {
            rect_info.push_back(
                hstd::fmt("  height0 {}", rect.height0.value()));
        }

        node->setLabel(hstd::join("\n", rect_info));
        node->setNodeShape(graph::gv::NodeShape::rectangle);
        rectNodes.emplace(rect_id, node);
    }

    for (int idx = 0; idx < constraints.size(); ++idx) {
        auto const& constraint = constraints[idx];
        Str         cid        = std::format("constraint-{}", idx);
        auto        cnode      = result->node(cid);
        cnode->setLabel(constraint->getRepr(rects));
        cnode->setNodeShape(graph::gv::NodeShape::rectangle);

        for (auto const& edge : constraint->describe_edges()) {
            auto e1 = result->edge(*rectNodes.at(edge.src), *cnode);
            e1->setLabel(edge.label);
            e1->setColor(axis_color(edge.axis));

            auto e2 = result->edge(*cnode, *rectNodes.at(edge.dst));
            e2->setColor(axis_color(edge.axis));
        }
    }

    result->render(path);
}

Vec<ConstraintEntry> Layout::build_constraint_entries() const {
    Vec<ConstraintEntry> entries;

    for (auto const& [rect_id, rect] : rects) {
        entries.push_back(
            ConstraintEntry{
                std::format("Rect({}).width >= 0", rect.rect_id),
                {(Expr(0) <= rect.expr(RectAttr::WIDTH))
                 | kiwi::strength::required},
            });
        entries.push_back(
            ConstraintEntry{
                std::format("Rect({}).height >= 0", rect.rect_id),
                {(Expr(0) <= rect.expr(RectAttr::HEIGHT))
                 | kiwi::strength::required},
            });

        if (rect.x0.has_value()) {
            entries.push_back(
                ConstraintEntry{
                    std::format(
                        "Rect({}).x == {:g}",
                        rect.rect_id,
                        rect.x0.value()),
                    {(rect.expr(RectAttr::X) == rect.x0.value())
                     | kiwi::strength::required},
                });
        }
        if (rect.y0.has_value()) {
            entries.push_back(
                ConstraintEntry{
                    std::format(
                        "Rect({}).y == {:g}",
                        rect.rect_id,
                        rect.y0.value()),
                    {(rect.expr(RectAttr::Y) == rect.y0.value())
                     | kiwi::strength::required},
                });
        }
        if (rect.width0.has_value()) {
            entries.push_back(
                ConstraintEntry{
                    std::format(
                        "Rect({}).width == {:g}",
                        rect.rect_id,
                        rect.width0.value()),
                    {(rect.expr(RectAttr::WIDTH) == rect.width0.value())
                     | kiwi::strength::required},
                });
        }
        if (rect.height0.has_value()) {
            entries.push_back(
                ConstraintEntry{
                    std::format(
                        "Rect({}).height == {:g}",
                        rect.rect_id,
                        rect.height0.value()),
                    {(rect.expr(RectAttr::HEIGHT) == rect.height0.value())
                     | kiwi::strength::required},
                });
        }
    }

    for (auto const& item : constraints) {
        entries.push_back(ConstraintEntry{item, item->build(rects)});
    }

    return entries;
}

hstd::Result<std::monostate, Layout::LoweredFailureDescr> Layout::
    is_satisfiable(Vec<ConstraintEntry> const& entries) const {
    kiwi::Solver solver;
    try {
        for (int entry_idx = 0; entry_idx < entries.size(); ++entry_idx) {
            auto const& entry = entries.at(entry_idx);
            for (int lowered_idx = 0; lowered_idx < entry.lowered.size();
                 ++lowered_idx) {
                solver.addConstraint(
                    entry.lowered.at(lowered_idx).to_kiwi());
            }
        }
    } catch (kiwi::UnsatisfiableConstraint const&) {
        return LoweredFailureDescr{
            .entry_idx   = 0,
            .lowered_idx = 0,
        };
    }
    return std::monostate{};
}

Vec<Layout::ConstraintFailure> Layout::minimal_conflict_set(
    Vec<ConstraintEntry> const& active_entries,
    ConstraintEntry const&      failing_entry) const {
    auto make_trial = [&](Vec<ConstraintEntry> const& conflict,
                          int skip_idx) -> Vec<ConstraintEntry> {
        Vec<ConstraintEntry> trial;
        for (int idx = 0; idx < conflict.size(); ++idx) {
            if (idx != skip_idx) { trial.push_back(conflict.at(idx)); }
        }
        trial.push_back(failing_entry);
        return trial;
    };

    auto single_failure =
        [&](ConstraintEntry const& entry) -> hstd::Opt<ConstraintFailure> {
        auto sat = is_satisfiable({entry});
        if (!sat.has_error()) {
            return std::nullopt;
        } else {
            auto const& descr = sat.assume_error();
            return ConstraintFailure{
                .entry = entry,
                .desc =
                LoweredFailureDescr{
                    .entry_idx   = 0,
                    .lowered_idx = descr.lowered_idx,
                },
            };
        }
    };

    if (auto fail = single_failure(failing_entry)) { return {}; }

    Vec<ConstraintEntry> conflict = active_entries;
    int                  idx      = 0;
    while (idx < conflict.size()) {
        Vec<ConstraintEntry> trial = make_trial(conflict, idx);
        if (!is_satisfiable(trial).has_value()) {
            Vec<ConstraintEntry> reduced;
            for (int j = 0; j < conflict.size(); ++j) {
                if (j != idx) { reduced.push_back(conflict.at(j)); }
            }
            conflict = std::move(reduced);
        } else {
            ++idx;
        }
    }

    Vec<ConstraintFailure> result;
    for (int entry_idx = 0; entry_idx < conflict.size(); ++entry_idx) {
        Vec<ConstraintEntry> trial;
        for (int idx = 0; idx < conflict.size(); ++idx) {
            trial.push_back(conflict.at(idx));
        }
        trial.push_back(failing_entry);

        auto sat = is_satisfiable(trial);
        result.push_back(
            ConstraintFailure{
                .entry = conflict.at(entry_idx),
                .desc  = //
                sat.has_value()
                    ? std::nullopt
                    : hstd::Opt<LoweredFailureDescr>(LoweredFailureDescr{
                          .entry_idx   = sat.assume_error().entry_idx,
                          .lowered_idx = sat.assume_error().lowered_idx,
                      }),
            });
    }

    return result;
}

void Layout::verify_constraints() {
    Vec<ConstraintEntry> entries = build_constraint_entries();
    kiwi::Solver         solver;
    Vec<ConstraintEntry> active_entries;

    auto describe_constraint_source =
        [&](std::variant<Str, hstd::SPtr<ConstraintBase>> const& source)
        -> Str {
        if (std::holds_alternative<Str>(source)) {
            return std::get<Str>(source);
        } else {
            return std::get<hstd::SPtr<ConstraintBase>>(source)->getRepr();
        }
    };

    for (auto const& entry : entries) {
        try {
            for (auto const& lowered : entry.lowered) {
                solver.addConstraint(lowered.to_kiwi());
            }
        } catch (kiwi::UnsatisfiableConstraint const&) {
            auto conflicts = minimal_conflict_set(active_entries, entry);
            Vec<Str> lines;
            lines.push_back("Unsatisfiable layout constraints detected.");
            lines.push_back(
                std::format(
                    "Failing constraint: {}",
                    describe_constraint_source(entry.source)));
            if (conflicts.empty()) {
                lines.push_back(
                    "The failing constraint is internally inconsistent.");
            } else {
                lines.push_back("Conflicts with:");
                for (auto const& src : conflicts) {
                    lines.push_back(
                        std::format(
                            "  - {}",
                            describe_constraint_source(src.entry.source)));
                    if (src.desc.has_value()) {
                        lines.push_back(
                            std::format(
                                "    - first conflict detected when "
                                "adding lowered element {}",
                                tree_repr(
                                    entries.at(src.desc->entry_idx)
                                        .lowered.at(src.desc->lowered_idx),
                                    6)));
                    }
                }
            }

            lines.push_back("");
            throw ConstraintVerificationError::init(
                hstd::join("\n", lines));
        }
        active_entries.push_back(entry);
    }
}

namespace {

void repr_impl(
    hstd::ColStream&        os,
    kiwi::Expression const& e,
    int                     indent) {

    int var_size = 8;
    for (auto const& t : e.terms()) {
        var_size = std::max<int>(var_size, t.variable().name().size());
    }

    for (auto const& t : hstd::enumerator(e.terms())) {
        os.newline();
        os.indent(indent);
        os << hstd::fmt(
            "{:<{}} {}",
            t.value().variable(),
            var_size,
            t.value().coefficient());
    }
}

void repr_impl(
    hstd::ColStream&        os,
    kiwi::Constraint const& c,
    int                     indent) {
    switch (c.op()) {
        case kiwi::RelationalOperator::OP_EQ: os << "EQ"; break;
        case kiwi::RelationalOperator::OP_GE: os << "GE"; break;
        case kiwi::RelationalOperator::OP_LE: os << "LE"; break;
    }

    repr_impl(os, c.expression(), 1);
}


void repr_impl(hstd::ColStream& os, Expr::Node const& n, int indent) {
    os.newline();
    os.indent(indent);

    using Kind = Expr::Node::Kind;
    switch (n.kind) {
        case Kind::Constant:
            os << hstd::fmt("Const({})", n.constant);
            break;

        case Kind::Variable:
            os << hstd::fmt("Var({})", n.variable->name());
            break;

        case Kind::KiwiExpression: {
            os << "KiwiExpr";
            int var_size = 8;
            for (auto const& t : n.kiwi_expr->terms()) {
                var_size = std::max<int>(
                    var_size, t.variable().name().size());
            }

            for (auto const& t : hstd::enumerator(n.kiwi_expr->terms())) {
                os.newline();
                os.indent(indent + 1);
                os << hstd::fmt(
                    "{:<{}} {}",
                    t.value().variable(),
                    var_size,
                    t.value().coefficient());
            }

            os.newline();
            os.indent(indent + 1);
            os << hstd::fmt("const {}", n.kiwi_expr->constant());
            break;
        }

        case Kind::Add:
            os << "Add";
            repr_impl(os, *n.lhs, indent + 1);
            repr_impl(os, *n.rhs, indent + 1);
            break;

        case Kind::Sub:
            os << "Sub";
            repr_impl(os, *n.lhs, indent + 1);
            repr_impl(os, *n.rhs, indent + 1);
            break;

        case Kind::Mul:
            os << "Mul";
            repr_impl(os, *n.lhs, indent + 1);
            repr_impl(os, *n.rhs, indent + 1);
            break;

        case Kind::Neg:
            os << "Neg";
            repr_impl(os, *n.lhs, indent + 1);
            break;
    }
}

void repr_impl(hstd::ColStream& os, Constraint const& c, int indent) {
    os.newline();
    os.indent(indent);

    switch (c.op) {
        case kiwi::RelationalOperator::OP_EQ:
            os << "Constraint(EQ)";
            break;
        case kiwi::RelationalOperator::OP_LE:
            os << "Constraint(LE)";
            break;
        case kiwi::RelationalOperator::OP_GE:
            os << "Constraint(GE)";
            break;
    }

    repr_impl(os, *c.lhs.node, indent + 1);
    repr_impl(os, *c.rhs.node, indent + 1);
}


enum class Prec : int
{
    Add   = 1,
    Mul   = 2,
    Unary = 3,
    Atom  = 4
};

static std::string wrap_if(bool cond, std::string const& s) {
    return cond ? "(" + s + ")" : s;
}

static bool is_zero(double v) { return std::abs(v) < 1e-12; }
static bool is_one(double v) { return std::abs(v - 1.0) < 1e-12; }

struct LinearForm {
    double                        constant = 0.0;
    std::map<std::string, double> terms;
};

static void add_scaled(LinearForm& dst, LinearForm const& src, double k) {
    dst.constant += src.constant * k;
    for (auto const& [name, coef] : src.terms) {
        dst.terms[name] += coef * k;
    }
}

static LinearForm scale(LinearForm const& src, double k) {
    LinearForm out;
    add_scaled(out, src, k);
    return out;
}

static bool has_vars(LinearForm const& f) { return !f.terms.empty(); }

static std::string render_affine(LinearForm const& f) {
    std::string out;
    bool        first = true;

    auto append_signed = [&](bool neg, std::string const& body) {
        if (first) {
            if (neg) { out += "-"; }
            out += body;
            first = false;
        } else {
            out += neg ? " - " : " + ";
            out += body;
        }
    };

    for (auto const& [name, coef] : f.terms) {
        if (is_zero(coef)) { continue; }
        bool   neg = coef < 0.0;
        double a   = std::abs(coef);

        if (is_one(a)) {
            append_signed(neg, name);
        } else {
            append_signed(neg, hstd::fmt("{}{}", a, name));
        }
    }

    if (!is_zero(f.constant) || first) {
        bool   neg = f.constant < 0.0;
        double a   = std::abs(f.constant);
        append_signed(neg, hstd::fmt("{}", a));
    }

    return out;
}

static LinearForm to_linear(Expr::Node const& n) {
    using Kind = Expr::Node::Kind;
    switch (n.kind) {
        case Kind::Constant: {
            LinearForm out;
            out.constant = n.constant;
            return out;
        }
        case Kind::Variable: {
            LinearForm out;
            out.terms[n.variable->name()] = 1.0;
            return out;
        }
        case Kind::KiwiExpression: {
            LinearForm out;
            out.constant = n.kiwi_expr->constant();
            for (auto const& t : n.kiwi_expr->terms()) {
                out.terms[t.variable().name()] += t.coefficient();
            }
            return out;
        }
        case Kind::Add: {
            LinearForm l = to_linear(*n.lhs);
            LinearForm r = to_linear(*n.rhs);
            add_scaled(l, r, 1.0);
            return l;
        }
        case Kind::Sub: {
            LinearForm l = to_linear(*n.lhs);
            LinearForm r = to_linear(*n.rhs);
            add_scaled(l, r, -1.0);
            return l;
        }
        case Kind::Neg: {
            return scale(to_linear(*n.lhs), -1.0);
        }
        case Kind::Mul: {
            LinearForm l = to_linear(*n.lhs);
            LinearForm r = to_linear(*n.rhs);

            if (has_vars(l) && has_vars(r)) {
                throw std::runtime_error(
                    "flat_repr(full_flatten=true): non-linear "
                    "multiplication");
            }

            if (has_vars(l)) { return scale(l, r.constant); }
            if (has_vars(r)) { return scale(r, l.constant); }

            LinearForm out;
            out.constant = l.constant * r.constant;
            return out;
        }
    }

    throw std::runtime_error("unreachable");
}

static int precedence(Expr::Node const& n) {
    using Kind = Expr::Node::Kind;
    switch (n.kind) {
        case Kind::Add:
        case Kind::Sub: return static_cast<int>(Prec::Add);
        case Kind::Mul: return static_cast<int>(Prec::Mul);
        case Kind::Neg: return static_cast<int>(Prec::Unary);
        case Kind::Constant:
        case Kind::Variable:
        case Kind::KiwiExpression: return static_cast<int>(Prec::Atom);
    }
    return static_cast<int>(Prec::Atom);
}

static void collect_add_terms(
    Expr::Node const&                               n,
    int                                             sign,
    std::vector<std::pair<int, Expr::Node const*>>& out) {
    using Kind = Expr::Node::Kind;
    switch (n.kind) {
        case Kind::Add:
            collect_add_terms(*n.lhs, sign, out);
            collect_add_terms(*n.rhs, sign, out);
            break;
        case Kind::Sub:
            collect_add_terms(*n.lhs, sign, out);
            collect_add_terms(*n.rhs, -sign, out);
            break;
        case Kind::Neg: collect_add_terms(*n.lhs, -sign, out); break;
        default: out.push_back({sign, &n}); break;
    }
}

static std::string flat_repr_impl(
    Expr::Node const& n,
    int               parent_prec,
    bool              full_flatten);

static std::string render_kiwi_expr(Expr::Node const& n) {
    LinearForm f;
    f.constant = n.kiwi_expr->constant();
    for (auto const& t : n.kiwi_expr->terms()) {
        f.terms[t.variable().name()] += t.coefficient();
    }
    return render_affine(f);
}

static std::string flat_repr_impl(
    Expr::Node const& n,
    int               parent_prec,
    bool              full_flatten) {
    using Kind = Expr::Node::Kind;

    if (full_flatten) { return render_affine(to_linear(n)); }

    switch (n.kind) {
        case Kind::Constant: return hstd::fmt("{}", n.constant);
        case Kind::Variable: return n.variable->name();
        case Kind::KiwiExpression: return render_kiwi_expr(n);

        case Kind::Neg: {
            auto inner = flat_repr_impl(
                *n.lhs, static_cast<int>(Prec::Unary), false);
            bool need_paren = precedence(*n.lhs)
                            < static_cast<int>(Prec::Unary);
            auto out        = "-" + wrap_if(need_paren, inner);
            return wrap_if(
                static_cast<int>(Prec::Unary) < parent_prec, out);
        }

        case Kind::Mul: {
            auto l = flat_repr_impl(
                *n.lhs, static_cast<int>(Prec::Mul), false);
            auto r = flat_repr_impl(
                *n.rhs, static_cast<int>(Prec::Mul), false);

            bool lp = precedence(*n.lhs) < static_cast<int>(Prec::Mul);
            bool rp = precedence(*n.rhs) < static_cast<int>(Prec::Mul);

            auto out = wrap_if(lp, l) + " * " + wrap_if(rp, r);
            return wrap_if(static_cast<int>(Prec::Mul) < parent_prec, out);
        }

        case Kind::Add:
        case Kind::Sub: {
            std::vector<std::pair<int, Expr::Node const*>> terms;
            collect_add_terms(n, 1, terms);

            std::string out;
            bool        first = true;

            for (auto const& [sign, ptr] : terms) {
                if (ptr->kind == Kind::Constant) {
                    double v = sign * ptr->constant;
                    if (first) {
                        out += hstd::fmt("{}", v);
                        first = false;
                    } else if (v < 0.0) {
                        out += hstd::fmt(" - {}", -v);
                    } else {
                        out += hstd::fmt(" + {}", v);
                    }
                    continue;
                }

                auto body = flat_repr_impl(
                    *ptr, static_cast<int>(Prec::Add), false);

                if (first) {
                    if (sign < 0) { out += "-"; }
                    out += body;
                    first = false;
                } else {
                    out += (sign < 0) ? " - " : " + ";
                    out += body;
                }
            }

            return wrap_if(static_cast<int>(Prec::Add) < parent_prec, out);
        }
    }

    throw std::runtime_error("unreachable");
}

} // namespace

Str tree_repr(kiwi::Expression const& c, int indent) {
    hstd::ColStream os;
    repr_impl(os, c, indent);
    return os.toString(false);
}

Str tree_repr(kiwi::Constraint const& c, int indent) {
    hstd::ColStream os;
    repr_impl(os, c, indent);
    return os.toString(false);
}

Str tree_repr(Vec<kiwi::Constraint> const& c, int indent) {
    hstd::ColStream os;
    for (auto const& sub_c : c) { repr_impl(os, sub_c, indent); }
    return os.toString(false);
}

Anchor get_anchor(Axis axis, AnchorAxisRelative rel) {
    switch (rel) {
        case AnchorAxisRelative::MIN_POS:
            return axis == Axis::X ? Anchor::LEFT : Anchor::TOP;
        case AnchorAxisRelative::MID_POS:
            return axis == Axis::X ? Anchor::HCENTER : Anchor::VCENTER;
        case AnchorAxisRelative::MAX_POS:
            return axis == Axis::X ? Anchor::RIGHT : Anchor::BOTTOM;
    }
}


Str tree_repr(Expr const& c, int indent) {
    hstd::ColStream os;
    repr_impl(os, *c.node, indent);
    return os.toString(false);
}

Str tree_repr(Constraint const& c, int indent) {
    hstd::ColStream os;
    repr_impl(os, c, indent);
    return os.toString(false);
}

Str tree_repr(Vec<Constraint> const& c, int indent) {
    hstd::ColStream os;
    for (auto const& sub_c : c) { repr_impl(os, sub_c, indent); }
    return os.toString(false);
}

Str flat_repr(Expr const& n, bool full_flatten) {
    return flat_repr_impl(*n.node, 0, full_flatten);
}

Str flat_repr(Constraint const& c, bool full_flatten) {
    Str op;
    switch (c.op) {
        case kiwi::RelationalOperator::OP_EQ: op = "=="; break;
        case kiwi::RelationalOperator::OP_LE: op = "<="; break;
        case kiwi::RelationalOperator::OP_GE: op = ">="; break;
    }

    return hstd::fmt(
        "{} {} {}",
        flat_repr(c.lhs, full_flatten),
        op,
        flat_repr(c.rhs, full_flatten));
}


} // namespace hstd::ext::kiwi_ir
