#include "kiwi_ir.hpp"

#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <sstream>
#include <stdexcept>

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

std::string axis_color(Axis axis) {
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
    std::string           rect_id,
    std::optional<double> x0,
    std::optional<double> y0,
    std::optional<double> width0,
    std::optional<double> height0)
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

std::string describe_constraint_source(
    std::variant<std::string, hstd::SPtr<ConstraintBase>> const& source) {
    if (std::holds_alternative<std::string>(source)) {
        return std::get<std::string>(source);
    } else {
        return std::get<hstd::SPtr<ConstraintBase>>(source)->getRepr();
    }
}

ConstraintVerificationError::ConstraintVerificationError(
    std::variant<std::string, hstd::SPtr<ConstraintBase>> failing_source,
    std::vector<std::variant<std::string, hstd::SPtr<ConstraintBase>>>
        conflicting_sources)
    : failing_source(std::move(failing_source))
    , conflicting_sources(std::move(conflicting_sources)) {
    std::vector<std::string> lines;
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
    for (size_t i = 0; i < lines.size(); ++i) {
        out << lines[i];
        if (i + 1 < lines.size()) { out << '\n'; }
    }
    message = out.str();
}

char const* ConstraintVerificationError::what() const noexcept {
    return message.c_str();
}

AlignConstraint::AlignConstraint(
    Anchor                 anchor,
    std::vector<AlignItem> items,
    Strength               strength)
    : ConstraintBase(strength), anchor(anchor), items(std::move(items)) {}

std::vector<kiwi::Constraint> AlignConstraint::build(
    std::unordered_map<std::string, Rect> const& rects) const {
    if (items.size() < 2) {
        throw std::runtime_error(
            "AlignConstraint requires at least 2 items");
    }
    auto const& base      = items[0];
    Expr        base_expr = rects.at(base.rect_id).anchor_expr(anchor)
                          - base.offset;
    std::vector<kiwi::Constraint> result;
    for (size_t i = 1; i < items.size(); ++i) {
        auto const& item = items[i];
        Expr        expr = rects.at(item.rect_id).anchor_expr(anchor)
                         - item.offset;
        result.push_back(
            (expr.to_kiwi() == base_expr.to_kiwi())
            | kiwi_value(strength));
    }
    return result;
}

std::vector<EdgeDesc> AlignConstraint::describe_edges() const {
    std::string           color = axis_color(anchor_axis(anchor));
    std::vector<EdgeDesc> edges;
    std::string           base = items[0].rect_id;
    for (size_t i = 1; i < items.size(); ++i) {
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

std::string AlignConstraint::getRepr() const {
    std::vector<std::string> joined;
    for (auto const& item : items) {
        if (item.offset == 0.0) {
            joined.push_back(item.rect_id);
        } else {
            joined.push_back(
                std::format("{}({:+g})", item.rect_id, item.offset));
        }
    }

    std::ostringstream out;
    for (size_t i = 0; i < joined.size(); ++i) {
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
    std::string first_rect_id,
    Anchor      first_anchor,
    std::string second_rect_id,
    Anchor      second_anchor,
    double      offset,
    Strength    strength)
    : ConstraintBase(strength)
    , first_rect_id(std::move(first_rect_id))
    , first_anchor(first_anchor)
    , second_rect_id(std::move(second_rect_id))
    , second_anchor(second_anchor)
    , offset(offset) {}

std::vector<kiwi::Constraint> SeparateConstraint::build(
    std::unordered_map<std::string, Rect> const& rects) const {
    Expr first  = rects.at(first_rect_id).anchor_expr(first_anchor);
    Expr second = rects.at(second_rect_id).anchor_expr(second_anchor);
    kiwi::Constraint c = (first.to_kiwi() == (second + offset).to_kiwi())
                       | kiwi_value(strength);
    return {c};
}

std::vector<EdgeDesc> SeparateConstraint::describe_edges() const {
    std::string color = axis_color(anchor_axis(first_anchor));
    return {EdgeDesc{
        second_rect_id,
        first_rect_id,
        std::format(
            "separate:{}->{}+{}", second_anchor, first_anchor, offset),
        color}};
}

std::string SeparateConstraint::getRepr() const {
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
    std::vector<std::vector<std::string>> groups,
    Anchor                                anchor,
    double                                step,
    Strength                              strength)
    : ConstraintBase(strength)
    , groups(std::move(groups))
    , anchor(anchor)
    , step(step) {}

std::vector<kiwi::Constraint> MultiSeparateConstraint::build(
    std::unordered_map<std::string, Rect> const& rects) const {
    std::vector<kiwi::Constraint> constraints;
    for (size_t idx = 0; idx + 1 < groups.size(); ++idx) {
        auto const& g1 = groups[idx];
        auto const& g2 = groups[idx + 1];
        if (g1.empty() || g2.empty()) { continue; }
        if (g1.size() != g2.size()) {
            throw std::runtime_error(
                "MultiSeparateConstraint requires corresponding group "
                "sizes");
        }
        for (size_t i = 0; i < g1.size(); ++i) {
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

std::vector<EdgeDesc> MultiSeparateConstraint::describe_edges() const {
    std::string           color = axis_color(anchor_axis(anchor));
    std::vector<EdgeDesc> edges;
    for (size_t idx = 0; idx + 1 < groups.size(); ++idx) {
        auto const& g1    = groups[idx];
        auto const& g2    = groups[idx + 1];
        size_t      count = std::min(g1.size(), g2.size());
        for (size_t i = 0; i < count; ++i) {
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

std::string MultiSeparateConstraint::getRepr() const {
    std::ostringstream out;
    out << "[";
    for (size_t i = 0; i < groups.size(); ++i) {
        out << "[";
        for (size_t j = 0; j < groups[i].size(); ++j) {
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
    std::string              parent_rect_id,
    std::vector<std::string> child_rect_ids,
    double                   padding_left,
    double                   padding_top,
    double                   padding_right,
    double                   padding_bottom,
    Strength                 strength)
    : ConstraintBase(strength)
    , parent_rect_id(std::move(parent_rect_id))
    , child_rect_ids(std::move(child_rect_ids))
    , padding_left(padding_left)
    , padding_top(padding_top)
    , padding_right(padding_right)
    , padding_bottom(padding_bottom) {}

std::vector<kiwi::Constraint> ParentWrapConstraint::build(
    std::unordered_map<std::string, Rect> const& rects) const {
    if (child_rect_ids.empty()) { return {}; }

    Rect const&                   parent = rects.at(parent_rect_id);
    std::vector<kiwi::Constraint> constraints;

    std::vector<Expr> left_exprs;
    std::vector<Expr> top_exprs;
    std::vector<Expr> right_exprs;
    std::vector<Expr> bottom_exprs;

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

std::vector<EdgeDesc> ParentWrapConstraint::describe_edges() const {
    std::vector<EdgeDesc> edges;
    for (auto const& child_id : child_rect_ids) {
        edges.push_back(
            EdgeDesc{child_id, parent_rect_id, "wrap-parent-x", "red"});
        edges.push_back(
            EdgeDesc{child_id, parent_rect_id, "wrap-parent-y", "blue"});
    }
    return edges;
}

std::string ParentWrapConstraint::getRepr() const {
    std::ostringstream children;
    children << "[";
    for (size_t i = 0; i < child_rect_ids.size(); ++i) {
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
    std::string           child_rect_id,
    std::string           parent_rect_id,
    std::optional<double> width_factor,
    std::optional<double> height_factor,
    Anchor                x_anchor,
    Anchor                y_anchor,
    double                x_offset,
    double                y_offset,
    Anchor                child_x_anchor,
    Anchor                child_y_anchor,
    Strength              strength)
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

std::vector<kiwi::Constraint> ChildRelativeToParentConstraint::build(
    std::unordered_map<std::string, Rect> const& rects) const {
    Rect const&                   child  = rects.at(child_rect_id);
    Rect const&                   parent = rects.at(parent_rect_id);
    std::vector<kiwi::Constraint> constraints;

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

std::vector<EdgeDesc> ChildRelativeToParentConstraint::describe_edges()
    const {
    std::vector<EdgeDesc> edges = {
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

std::string ChildRelativeToParentConstraint::getRepr() const {
    std::string wf = width_factor.has_value()
                       ? std::format("{:g}", width_factor.value())
                       : "None";
    std::string hf = height_factor.has_value()
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
    std::vector<std::string> rect_ids,
    Axis                     axis,
    Anchor                   anchor,
    Strength                 strength)
    : ConstraintBase(strength)
    , rect_ids(std::move(rect_ids))
    , axis(axis)
    , anchor(anchor) {}

std::vector<kiwi::Constraint> EvenGapConstraint::build(
    std::unordered_map<std::string, Rect> const& rects) const {
    if (rect_ids.size() < 3) { return {}; }
    std::vector<kiwi::Constraint> constraints;
    for (size_t i = 1; i + 1 < rect_ids.size(); ++i) {
        Expr a = rects.at(rect_ids[i - 1]).anchor_expr(anchor);
        Expr b = rects.at(rect_ids[i]).anchor_expr(anchor);
        Expr c = rects.at(rect_ids[i + 1]).anchor_expr(anchor);
        constraints.push_back(
            (((b - a) - (c - b)).to_kiwi() == 0) | kiwi_value(strength));
    }
    return constraints;
}

std::vector<EdgeDesc> EvenGapConstraint::describe_edges() const {
    std::string           color = axis_color(axis);
    std::vector<EdgeDesc> result;
    for (size_t i = 0; i + 1 < rect_ids.size(); ++i) {
        result.push_back(
            EdgeDesc{
                rect_ids[i],
                rect_ids[i + 1],
                std::format("even-gap:{}", anchor),
                color});
    }
    return result;
}

std::string EvenGapConstraint::getRepr() const {
    std::ostringstream out;
    out << "[";
    for (size_t i = 0; i < rect_ids.size(); ++i) {
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
    std::string rect_a_id,
    std::string rect_b_id,
    bool        match_width,
    bool        match_height,
    Strength    strength)
    : ConstraintBase(strength)
    , rect_a_id(std::move(rect_a_id))
    , rect_b_id(std::move(rect_b_id))
    , match_width(match_width)
    , match_height(match_height) {}

std::vector<kiwi::Constraint> EqualSizeConstraint::build(
    std::unordered_map<std::string, Rect> const& rects) const {
    Rect const&                   a = rects.at(rect_a_id);
    Rect const&                   b = rects.at(rect_b_id);
    std::vector<kiwi::Constraint> constraints;
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

std::vector<EdgeDesc> EqualSizeConstraint::describe_edges() const {
    std::vector<EdgeDesc> edges;
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

std::string EqualSizeConstraint::getRepr() const {
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

std::vector<kiwi::Constraint> LinearConstraint::build(
    std::unordered_map<std::string, Rect> const&) const {
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

std::vector<EdgeDesc> LinearConstraint::describe_edges() const {
    return {};
}

std::string LinearConstraint::getRepr() const {
    std::string rel = relation == Relation::EQ
                        ? "=="
                        : (relation == Relation::LE ? "<=" : ">=");
    return std::format(
        "LinearConstraint({} ..., strength={})", rel, strength);
}

Layout::Layout(
    std::vector<Rect>                       rects,
    std::vector<hstd::SPtr<ConstraintBase>> constraints)
    : constraints(std::move(constraints)) {
    for (auto& rect : rects) { this->rects.emplace(rect.rect_id, rect); }
}

std::unordered_map<std::string, Rect> Layout::solve() {
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

void Layout::to_svg(hstd::fs::path const& path, std::string const& title) {
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

    std::vector<std::string> colors = {
        "#ffcccc", "#ccffcc", "#ccccff", "#fff0cc", "#f0ccff", "#ccfff7"};

    size_t idx = 0;
    for (auto const& [rect_id, g] : solved) {
        std::string color = colors[idx % colors.size()];

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
    std::unordered_map<std::string, hstd::SPtr<graph::gv::NodeAttribute>>
        rectNodes;

    for (auto const& [rect_id, rect] : rects) {
        auto node = result->node(std::format("rect-{}", rect_id));
        node->setLabel(rect_id);
        rectNodes.emplace(rect_id, node);
    }

    for (size_t idx = 0; idx < constraints.size(); ++idx) {
        auto const& constraint = constraints[idx];
        std::string cid        = std::format("constraint-{}", idx);
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

std::vector<ConstraintEntry> Layout::build_constraint_entries() const {
    std::vector<ConstraintEntry> entries;

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

bool Layout::is_satisfiable(
    std::vector<ConstraintEntry> const& entries) const {
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

std::vector<ConstraintEntry> Layout::minimal_conflict_set(
    std::vector<ConstraintEntry> const& active_entries,
    ConstraintEntry const&              failing_entry) const {
    if (!is_satisfiable({failing_entry})) { return {}; }

    std::vector<ConstraintEntry> conflict = active_entries;
    size_t                       idx      = 0;
    while (idx < conflict.size()) {
        ConstraintEntry const&       candidate = conflict[idx];
        std::vector<ConstraintEntry> trial;
        for (auto const& entry : conflict) {
            if (&entry != &candidate) { trial.push_back(entry); }
        }
        trial.push_back(failing_entry);
        if (!is_satisfiable(trial)) {
            std::vector<ConstraintEntry> reduced;
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
    std::vector<ConstraintEntry> entries = build_constraint_entries();
    kiwi::Solver                 solver;
    std::vector<ConstraintEntry> active_entries;

    for (auto const& entry : entries) {
        try {
            for (auto const& lowered : entry.lowered) {
                solver.addConstraint(lowered);
            }
        } catch (kiwi::UnsatisfiableConstraint const&) {
            auto conflicts = minimal_conflict_set(active_entries, entry);
            std::vector<
                std::variant<std::string, hstd::SPtr<ConstraintBase>>>
                sources;
            for (auto const& c : conflicts) {
                sources.push_back(c.source);
            }
            throw ConstraintVerificationError(entry.source, sources);
        }
        active_entries.push_back(entry);
    }
}

} // namespace hstd::ext::kiwi_ir
