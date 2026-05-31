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

namespace hstd::ext::kiwi_ir {

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

Expr::Expr(double value) : value(value) {}

Expr::Expr(kiwi::Variable const& value) : value(value) {}

Expr::Expr(kiwi::Expression const& value) : value(value) {}

kiwi::Expression const& Expr::to_kiwi() const { return value; }

Expr Expr::operator+(Expr const& other) const {
    return Expr(value + other.value);
}

Expr Expr::operator-(Expr const& other) const {
    return Expr(value - other.value);
}

Expr Expr::operator*(double other) const { return Expr(value * other); }

Expr Expr::operator-() const { return Expr(-value); }

Expr Expr::operator*(Expr const& other) const {
    throw std::runtime_error(
        std::format(
            "Kiwi supports only linear expressions: {} * {}",
            value.constant(),
            other.value.constant()));
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
    if (name == RectAttr::X) { return Expr(x); }
    if (name == RectAttr::Y) { return Expr(y); }
    if (name == RectAttr::WIDTH) { return Expr(width); }
    if (name == RectAttr::HEIGHT) { return Expr(height); }
    if (name == RectAttr::LEFT) { return Expr(x); }
    if (name == RectAttr::HCENTER) { return Expr(x) + 0.5 * Expr(width); }
    if (name == RectAttr::RIGHT) { return Expr(x) + Expr(width); }
    if (name == RectAttr::TOP) { return Expr(y); }
    if (name == RectAttr::VCENTER) { return Expr(y) + 0.5 * Expr(height); }
    if (name == RectAttr::BOTTOM) { return Expr(y) + Expr(height); }
    throw std::runtime_error("Invalid RectAttr");
}

Expr Rect::anchor_expr(Anchor anchor) const {
    if (anchor == Anchor::LEFT) { return expr(RectAttr::LEFT); }
    if (anchor == Anchor::HCENTER) { return expr(RectAttr::HCENTER); }
    if (anchor == Anchor::RIGHT) { return expr(RectAttr::RIGHT); }
    if (anchor == Anchor::TOP) { return expr(RectAttr::TOP); }
    if (anchor == Anchor::VCENTER) { return expr(RectAttr::VCENTER); }
    if (anchor == Anchor::BOTTOM) { return expr(RectAttr::BOTTOM); }
    throw std::runtime_error("Invalid Anchor");
}

ConstraintBase::ConstraintBase(Strength strength) : strength(strength) {}

Str describe_constraint_source(
    std::variant<Str, hstd::SPtr<ConstraintBase>> const& source) {
    if (std::holds_alternative<Str>(source)) {
        return std::get<Str>(source);
    } else {
        return std::get<hstd::SPtr<ConstraintBase>>(source)->getRepr();
    }
}

ConstraintVerificationError::ConstraintVerificationError(
    std::variant<Str, hstd::SPtr<ConstraintBase>>      failing_source,
    Vec<std::variant<Str, hstd::SPtr<ConstraintBase>>> conflicting_sources)
    : failing_source(std::move(failing_source))
    , conflicting_sources(std::move(conflicting_sources)) {
    Vec<Str> lines;
    lines.push_back("Unsatisfiable layout constraints detected.");
    lines.push_back(
        std::format(
            "Failing constraint: {}",
            describe_constraint_source(this->failing_source)));
    if (!this->conflicting_sources.empty()) {
        lines.push_back("Conflicts with:");
        for (auto const& src : this->conflicting_sources) {
            lines.push_back(
                std::format("  - {}", describe_constraint_source(src)));
        }
    } else {
        lines.push_back(
            "The failing constraint is internally inconsistent.");
    }

    std::ostringstream out;
    for (int i = 0; i < lines.size(); ++i) {
        out << lines[i];
        if (i + 1 < lines.size()) { out << '\n'; }
    }
    message = out.str();
}

char const* ConstraintVerificationError::what() const noexcept {
    return message.c_str();
}

AlignConstraint::AlignConstraint(
    Anchor         anchor,
    Vec<AlignItem> items,
    Strength       strength)
    : ConstraintBase(strength), anchor(anchor), items(std::move(items)) {}

Vec<kiwi::Constraint> AlignConstraint::build(
    std::unordered_map<Str, Rect> const& rects) const {
    if (items.size() < 2) {
        throw std::runtime_error(
            "AlignConstraint requires at least 2 items");
    }
    auto const& base      = items[0];
    Expr        base_expr = rects.at(base.rect_id).anchor_expr(anchor)
                          - base.offset;
    Vec<kiwi::Constraint> result;
    for (int i = 1; i < items.size(); ++i) {
        auto const& item = items[i];
        Expr        expr = rects.at(item.rect_id).anchor_expr(anchor)
                         - item.offset;
        result.push_back(
            (expr.to_kiwi() == base_expr.to_kiwi())
            | kiwi_value(strength));
    }
    return result;
}

Vec<EdgeDesc> AlignConstraint::describe_edges() const {
    Str           color = axis_color(anchor_axis(anchor));
    Vec<EdgeDesc> edges;
    Str           base = items[0].rect_id;
    for (int i = 1; i < items.size(); ++i) {
        auto const& item = items[i];
        edges.push_back(
            EdgeDesc{
                base,
                item.rect_id,
                std::format("align:{}", anchor),
                color});
    }
    return edges;
}

Str AlignConstraint::getRepr() const {
    Vec<Str> joined;
    for (auto const& item : items) {
        if (item.offset == 0.0) {
            joined.push_back(item.rect_id);
        } else {
            joined.push_back(
                std::format("{}({:+g})", item.rect_id, item.offset));
        }
    }

    std::ostringstream out;
    for (int i = 0; i < joined.size(); ++i) {
        out << joined[i];
        if (i + 1 < joined.size()) { out << ", "; }
    }

    return std::format(
        "AlignConstraint(anchor={}, items=[{}], strength={})",
        anchor,
        out.str(),
        strength);
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

Vec<kiwi::Constraint> SeparateConstraint::build(
    std::unordered_map<Str, Rect> const& rects) const {
    Expr first  = rects.at(first_rect_id).anchor_expr(first_anchor);
    Expr second = rects.at(second_rect_id).anchor_expr(second_anchor);
    kiwi::Constraint c = (first.to_kiwi() == (second + offset).to_kiwi())
                       | kiwi_value(strength);
    return {c};
}

Vec<EdgeDesc> SeparateConstraint::describe_edges() const {
    Str color = axis_color(anchor_axis(first_anchor));
    return {EdgeDesc{
        second_rect_id,
        first_rect_id,
        std::format(
            "separate:{}->{}+{}", second_anchor, first_anchor, offset),
        color}};
}

Str SeparateConstraint::getRepr() const {
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

Vec<kiwi::Constraint> MultiSeparateConstraint::build(
    std::unordered_map<Str, Rect> const& rects) const {
    Vec<kiwi::Constraint> constraints;
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
                (expr_a.to_kiwi() == (expr_b + step).to_kiwi())
                | kiwi_value(strength));
        }
    }
    return constraints;
}

Vec<EdgeDesc> MultiSeparateConstraint::describe_edges() const {
    Str           color = axis_color(anchor_axis(anchor));
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
                    color});
        }
    }
    return edges;
}

Str MultiSeparateConstraint::getRepr() const {
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
    Str      parent_rect_id,
    Vec<Str> child_rect_ids,
    double   padding_left,
    double   padding_top,
    double   padding_right,
    double   padding_bottom,
    Strength strength)
    : ConstraintBase(strength)
    , parent_rect_id(std::move(parent_rect_id))
    , child_rect_ids(std::move(child_rect_ids))
    , padding_left(padding_left)
    , padding_top(padding_top)
    , padding_right(padding_right)
    , padding_bottom(padding_bottom) {}

Vec<kiwi::Constraint> ParentWrapConstraint::build(
    std::unordered_map<Str, Rect> const& rects) const {
    if (child_rect_ids.empty()) { return {}; }

    Rect const&           parent = rects.at(parent_rect_id);
    Vec<kiwi::Constraint> constraints;

    Vec<Expr> left_exprs;
    Vec<Expr> top_exprs;
    Vec<Expr> right_exprs;
    Vec<Expr> bottom_exprs;

    for (auto const& child_id : child_rect_ids) {
        left_exprs.push_back(rects.at(child_id).anchor_expr(Anchor::LEFT));
        top_exprs.push_back(rects.at(child_id).anchor_expr(Anchor::TOP));
        right_exprs.push_back(
            rects.at(child_id).anchor_expr(Anchor::RIGHT));
        bottom_exprs.push_back(
            rects.at(child_id).anchor_expr(Anchor::BOTTOM));
    }

    for (auto const& child_left : left_exprs) {
        constraints.push_back(
            (parent.anchor_expr(Anchor::LEFT).to_kiwi()
             <= (child_left - padding_left).to_kiwi())
            | kiwi_value(strength));
    }

    for (auto const& child_top : top_exprs) {
        constraints.push_back(
            (parent.anchor_expr(Anchor::TOP).to_kiwi()
             <= (child_top - padding_top).to_kiwi())
            | kiwi_value(strength));
    }

    for (auto const& child_right : right_exprs) {
        constraints.push_back(
            ((child_right + padding_right).to_kiwi()
             <= parent.anchor_expr(Anchor::RIGHT).to_kiwi())
            | kiwi_value(strength));
    }

    for (auto const& child_bottom : bottom_exprs) {
        constraints.push_back(
            ((child_bottom + padding_bottom).to_kiwi()
             <= parent.anchor_expr(Anchor::BOTTOM).to_kiwi())
            | kiwi_value(strength));
    }

    constraints.push_back(
        (parent.anchor_expr(Anchor::LEFT).to_kiwi()
         == (left_exprs[0] - padding_left).to_kiwi())
        | kiwi_value(strength));
    constraints.push_back(
        (parent.anchor_expr(Anchor::TOP).to_kiwi()
         == (top_exprs[0] - padding_top).to_kiwi())
        | kiwi_value(strength));
    constraints.push_back(
        (parent.anchor_expr(Anchor::RIGHT).to_kiwi()
         == (right_exprs[right_exprs.size() - 1] + padding_right)
                .to_kiwi())
        | kiwi_value(strength));
    constraints.push_back(
        (parent.anchor_expr(Anchor::BOTTOM).to_kiwi()
         == (bottom_exprs[bottom_exprs.size() - 1] + padding_bottom)
                .to_kiwi())
        | kiwi_value(strength));

    return constraints;
}

Vec<EdgeDesc> ParentWrapConstraint::describe_edges() const {
    Vec<EdgeDesc> edges;
    for (auto const& child_id : child_rect_ids) {
        edges.push_back(
            EdgeDesc{child_id, parent_rect_id, "wrap-parent-x", "red"});
        edges.push_back(
            EdgeDesc{child_id, parent_rect_id, "wrap-parent-y", "blue"});
    }
    return edges;
}

Str ParentWrapConstraint::getRepr() const {
    std::ostringstream children;
    children << "[";
    for (int i = 0; i < child_rect_ids.size(); ++i) {
        children << child_rect_ids[i];
        if (i + 1 < child_rect_ids.size()) { children << ", "; }
    }
    children << "]";
    return std::format(
        "ParentWrapConstraint(parent={}, children={}, padding=({:g}, "
        "{:g}, {:g}, {:g}), strength={})",
        parent_rect_id,
        children.str(),
        padding_left,
        padding_top,
        padding_right,
        padding_bottom,
        strength);
}

ChildRelativeToParentConstraint::ChildRelativeToParentConstraint(
    Str         child_rect_id,
    Str         parent_rect_id,
    Opt<double> width_factor,
    Opt<double> height_factor,
    Anchor      x_anchor,
    Anchor      y_anchor,
    double      x_offset,
    double      y_offset,
    Anchor      child_x_anchor,
    Anchor      child_y_anchor,
    Strength    strength)
    : ConstraintBase(strength)
    , child_rect_id(std::move(child_rect_id))
    , parent_rect_id(std::move(parent_rect_id))
    , width_factor(width_factor)
    , height_factor(height_factor)
    , x_anchor(x_anchor)
    , y_anchor(y_anchor)
    , x_offset(x_offset)
    , y_offset(y_offset)
    , child_x_anchor(child_x_anchor)
    , child_y_anchor(child_y_anchor) {}

Vec<kiwi::Constraint> ChildRelativeToParentConstraint::build(
    std::unordered_map<Str, Rect> const& rects) const {
    Rect const&           child  = rects.at(child_rect_id);
    Rect const&           parent = rects.at(parent_rect_id);
    Vec<kiwi::Constraint> constraints;

    if (width_factor.has_value()) {
        constraints.push_back(
            (child.expr(RectAttr::WIDTH).to_kiwi()
             == (parent.expr(RectAttr::WIDTH) * width_factor.value())
                    .to_kiwi())
            | kiwi_value(strength));
    }
    if (height_factor.has_value()) {
        constraints.push_back(
            (child.expr(RectAttr::HEIGHT).to_kiwi()
             == (parent.expr(RectAttr::HEIGHT) * height_factor.value())
                    .to_kiwi())
            | kiwi_value(strength));
    }

    constraints.push_back(
        (child.anchor_expr(child_x_anchor).to_kiwi()
         == (parent.anchor_expr(x_anchor) + x_offset).to_kiwi())
        | kiwi_value(strength));
    constraints.push_back(
        (child.anchor_expr(child_y_anchor).to_kiwi()
         == (parent.anchor_expr(y_anchor) + y_offset).to_kiwi())
        | kiwi_value(strength));

    return constraints;
}

Vec<EdgeDesc> ChildRelativeToParentConstraint::describe_edges() const {
    Vec<EdgeDesc> edges = {
        EdgeDesc{parent_rect_id, child_rect_id, "child-relative-x", "red"},
        EdgeDesc{
            parent_rect_id, child_rect_id, "child-relative-y", "blue"},
    };
    if (width_factor.has_value()) {
        edges.push_back(
            EdgeDesc{
                parent_rect_id,
                child_rect_id,
                "child-relative-width",
                "red"});
    }
    if (height_factor.has_value()) {
        edges.push_back(
            EdgeDesc{
                parent_rect_id,
                child_rect_id,
                "child-relative-height",
                "blue"});
    }
    return edges;
}

Str ChildRelativeToParentConstraint::getRepr() const {
    Str wf = width_factor.has_value()
               ? std::format("{:g}", width_factor.value())
               : "None";
    Str hf = height_factor.has_value()
               ? std::format("{:g}", height_factor.value())
               : "None";
    return std::format(
        "ChildRelativeToParentConstraint(child={}, parent={}, "
        "width_factor={}, height_factor={}, x={}->{}{:+g}, y={}->{}{:+g}, "
        "strength={})",
        child_rect_id,
        parent_rect_id,
        wf,
        hf,
        child_x_anchor,
        x_anchor,
        x_offset,
        child_y_anchor,
        y_anchor,
        y_offset,
        strength);
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

Vec<kiwi::Constraint> EvenGapConstraint::build(
    std::unordered_map<Str, Rect> const& rects) const {
    if (rect_ids.size() < 3) { return {}; }
    Vec<kiwi::Constraint> constraints;
    for (int i = 1; i + 1 < rect_ids.size(); ++i) {
        Expr a = rects.at(rect_ids[i - 1]).anchor_expr(anchor);
        Expr b = rects.at(rect_ids[i]).anchor_expr(anchor);
        Expr c = rects.at(rect_ids[i + 1]).anchor_expr(anchor);
        constraints.push_back(
            (((b - a) - (c - b)).to_kiwi() == 0) | kiwi_value(strength));
    }
    return constraints;
}

Vec<EdgeDesc> EvenGapConstraint::describe_edges() const {
    Str           color = axis_color(axis);
    Vec<EdgeDesc> result;
    for (int i = 0; i + 1 < rect_ids.size(); ++i) {
        result.push_back(
            EdgeDesc{
                rect_ids[i],
                rect_ids[i + 1],
                std::format("even-gap:{}", anchor),
                color});
    }
    return result;
}

Str EvenGapConstraint::getRepr() const {
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

Vec<kiwi::Constraint> EqualSizeConstraint::build(
    std::unordered_map<Str, Rect> const& rects) const {
    Rect const&           a = rects.at(rect_a_id);
    Rect const&           b = rects.at(rect_b_id);
    Vec<kiwi::Constraint> constraints;
    if (match_width) {
        constraints.push_back(
            (a.expr(RectAttr::WIDTH).to_kiwi()
             == b.expr(RectAttr::WIDTH).to_kiwi())
            | kiwi_value(strength));
    }
    if (match_height) {
        constraints.push_back(
            (a.expr(RectAttr::HEIGHT).to_kiwi()
             == b.expr(RectAttr::HEIGHT).to_kiwi())
            | kiwi_value(strength));
    }
    return constraints;
}

Vec<EdgeDesc> EqualSizeConstraint::describe_edges() const {
    Vec<EdgeDesc> edges;
    if (match_width) {
        edges.push_back(
            EdgeDesc{rect_a_id, rect_b_id, "equal-size:width", "red"});
    }
    if (match_height) {
        edges.push_back(
            EdgeDesc{rect_a_id, rect_b_id, "equal-size:height", "blue"});
    }
    return edges;
}

Str EqualSizeConstraint::getRepr() const {
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

Vec<kiwi::Constraint> LinearConstraint::build(
    std::unordered_map<Str, Rect> const&) const {
    kiwi::Constraint c = (left.to_kiwi() == right.to_kiwi())
                       | kiwi_value(strength);
    if (relation == Relation::EQ) {
        c = (left.to_kiwi() == right.to_kiwi()) | kiwi_value(strength);
    } else if (relation == Relation::LE) {
        c = (left.to_kiwi() <= right.to_kiwi()) | kiwi_value(strength);
    } else if (relation == Relation::GE) {
        c = (right.to_kiwi() <= left.to_kiwi()) | kiwi_value(strength);
    } else {
        throw std::runtime_error("Invalid relation");
    }
    return {c};
}

Vec<EdgeDesc> LinearConstraint::describe_edges() const { return {}; }

Str LinearConstraint::getRepr() const {
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

std::unordered_map<Str, Rect> Layout::solve() {
    kiwi::Solver solver;

    for (auto& [rect_id, rect] : rects) {
        solver.addConstraint(
            (0 <= rect.expr(RectAttr::WIDTH).to_kiwi())
            | kiwi::strength::required);
        solver.addConstraint(
            (0 <= rect.expr(RectAttr::HEIGHT).to_kiwi())
            | kiwi::strength::required);

        if (rect.x0.has_value()) {
            solver.addConstraint(
                (rect.expr(RectAttr::X).to_kiwi() == rect.x0.value())
                | kiwi::strength::required);
        }
        if (rect.y0.has_value()) {
            solver.addConstraint(
                (rect.expr(RectAttr::Y).to_kiwi() == rect.y0.value())
                | kiwi::strength::required);
        }
        if (rect.width0.has_value()) {
            solver.addConstraint(
                (rect.expr(RectAttr::WIDTH).to_kiwi()
                 == rect.width0.value())
                | kiwi::strength::required);
        }
        if (rect.height0.has_value()) {
            solver.addConstraint(
                (rect.expr(RectAttr::HEIGHT).to_kiwi()
                 == rect.height0.value())
                | kiwi::strength::required);
        }
    }

    for (auto const& item : constraints) {
        for (auto const& c : item->build(rects)) {
            solver.addConstraint(c);
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

void Layout::to_svg(hstd::fs::path const& path, Str const& title) {
    std::filesystem::create_directories(path.parent_path());

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

    std::ofstream os(path);
    os << svg.to_string(2);
}

void Layout::to_graphviz(hstd::fs::path const& path) {
    std::filesystem::create_directories(path.parent_path());

    auto result = graph::gv::GraphGroup::newStandaloneRootGraph("G");
    std::unordered_map<Str, hstd::SPtr<graph::gv::NodeAttribute>>
        rectNodes;

    for (auto const& [rect_id, rect] : rects) {
        auto node = result->node(std::format("rect-{}", rect_id));
        node->setLabel(rect_id);
        rectNodes.emplace(rect_id, node);
    }

    for (int idx = 0; idx < constraints.size(); ++idx) {
        auto const& constraint = constraints[idx];
        Str         cid        = std::format("constraint-{}", idx);
        auto        cnode      = result->node(cid);
        cnode->setLabel(constraint->getRepr());

        for (auto const& edge : constraint->describe_edges()) {
            auto e1 = result->edge(*rectNodes.at(edge.src), *cnode);
            e1->setLabel(edge.label);
            e1->setColor(edge.color);

            auto e2 = result->edge(*cnode, *rectNodes.at(edge.dst));
            e2->setColor(edge.color);
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
                {(0 <= rect.expr(RectAttr::WIDTH).to_kiwi())
                 | kiwi::strength::required},
            });
        entries.push_back(
            ConstraintEntry{
                std::format("Rect({}).height >= 0", rect.rect_id),
                {(0 <= rect.expr(RectAttr::HEIGHT).to_kiwi())
                 | kiwi::strength::required},
            });

        if (rect.x0.has_value()) {
            entries.push_back(
                ConstraintEntry{
                    std::format(
                        "Rect({}).x == {:g}",
                        rect.rect_id,
                        rect.x0.value()),
                    {(rect.expr(RectAttr::X).to_kiwi() == rect.x0.value())
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
                    {(rect.expr(RectAttr::Y).to_kiwi() == rect.y0.value())
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
                    {(rect.expr(RectAttr::WIDTH).to_kiwi()
                      == rect.width0.value())
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
                    {(rect.expr(RectAttr::HEIGHT).to_kiwi()
                      == rect.height0.value())
                     | kiwi::strength::required},
                });
        }
    }

    for (auto const& item : constraints) {
        entries.push_back(ConstraintEntry{item, item->build(rects)});
    }

    return entries;
}

bool Layout::is_satisfiable(Vec<ConstraintEntry> const& entries) const {
    kiwi::Solver solver;
    try {
        for (auto const& entry : entries) {
            for (auto const& lowered : entry.lowered) {
                solver.addConstraint(lowered);
            }
        }
    } catch (kiwi::UnsatisfiableConstraint const&) { return false; }
    return true;
}

Vec<ConstraintEntry> Layout::minimal_conflict_set(
    Vec<ConstraintEntry> const& active_entries,
    ConstraintEntry const&      failing_entry) const {
    if (!is_satisfiable({failing_entry})) { return {}; }

    Vec<ConstraintEntry> conflict = active_entries;
    int                  idx      = 0;
    while (idx < conflict.size()) {
        ConstraintEntry const& candidate = conflict[idx];
        Vec<ConstraintEntry>   trial;
        for (auto const& entry : conflict) {
            if (&entry != &candidate) { trial.push_back(entry); }
        }
        trial.push_back(failing_entry);
        if (!is_satisfiable(trial)) {
            Vec<ConstraintEntry> reduced;
            for (auto const& entry : conflict) {
                if (&entry != &candidate) { reduced.push_back(entry); }
            }
            conflict = std::move(reduced);
        } else {
            ++idx;
        }
    }
    return conflict;
}

void Layout::verify_constraints() {
    Vec<ConstraintEntry> entries = build_constraint_entries();
    kiwi::Solver         solver;
    Vec<ConstraintEntry> active_entries;

    for (auto const& entry : entries) {
        try {
            for (auto const& lowered : entry.lowered) {
                solver.addConstraint(lowered);
            }
        } catch (kiwi::UnsatisfiableConstraint const&) {
            auto conflicts = minimal_conflict_set(active_entries, entry);
            Vec<std::variant<Str, hstd::SPtr<ConstraintBase>>> sources;
            for (auto const& c : conflicts) {
                sources.push_back(c.source);
            }
            throw ConstraintVerificationError(entry.source, sources);
        }
        active_entries.push_back(entry);
    }
}

} // namespace hstd::ext::kiwi_ir
