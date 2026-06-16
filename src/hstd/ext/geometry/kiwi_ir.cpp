#include "kiwi_ir.hpp"
#if ORG_BUILD_WITH_KIWI

#    include "hstd/stdlib/Debug.hpp"

#    include <algorithm>
#    include <filesystem>
#    include <sstream>
#    include <stdexcept>

#    include <boost/geometry.hpp>
#    include <boost/geometry/geometries/box.hpp>
#    include <boost/geometry/geometries/point.hpp>
#    include <boost/graph/adjacency_list.hpp>
#    include <boost/graph/topological_sort.hpp>
#    include <hstd/ext/graph/visual/graph_graphviz.hpp>
#    include <hstd/stdlib/Enumerate.hpp>
#    include <hstd/stdlib/Ranges.hpp>

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
    if (anchor == Anchor::LEFT || anchor == Anchor::HCENTER || anchor == Anchor::RIGHT) {
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


Expr::Expr(std::shared_ptr<Node> node) : node(std::move(node)) {}

std::shared_ptr<Expr::Node> Expr::make_constant(double value) {
    Node n;
    n.kind     = Node::Kind::Constant;
    n.constant = value;
    return std::make_shared<Node>(std::move(n));
}

std::shared_ptr<Expr::Node> Expr::make_variable(kiwi::Variable const& value) {
    Node n;
    n.kind     = Node::Kind::Variable;
    n.variable = value;
    return std::make_shared<Node>(std::move(n));
}

std::shared_ptr<Expr::Node> Expr::make_kiwi_expr(kiwi::Expression const& value) {
    Node n;
    n.kind      = Node::Kind::KiwiExpression;
    n.kiwi_expr = value;
    return std::make_shared<Node>(std::move(n));
}

std::shared_ptr<Expr::Node> Expr::make_unary(Node::Kind kind, std::shared_ptr<Node> lhs) {
    Node n;
    n.kind = kind;
    n.lhs  = std::move(lhs);
    return std::make_shared<Node>(std::move(n));
}

std::shared_ptr<Expr::Node> Expr::make_binary(
    Node::Kind            kind,
    std::shared_ptr<Node> lhs,
    std::shared_ptr<Node> rhs) {
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

Expr Expr::operator-() const { return Expr(make_unary(Node::Kind::Neg, node)); }

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

Constraint::Constraint(Expr const& lhs, Expr const& rhs, kiwi::RelationalOperator op)
    : lhs(lhs), rhs(rhs), op(op) {}

kiwi::Expression Constraint::fold_expr(std::shared_ptr<Expr::Node const> const& node) {
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
                return kiwi::Expression(left.constant() * right.constant());
            } else if (left_const) {
                return right * left.constant();
            } else if (right_const) {
                return left * right.constant();
            }

            throw std::runtime_error("Kiwi supports only linear expressions");
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

Expr operator+(double left, Expr const& right) { return Expr(left) + right; }

Expr operator-(double left, Expr const& right) { return Expr(left) - right; }

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
    , x(fmt::format("{}.x", this->rect_id))
    , y(fmt::format("{}.y", this->rect_id))
    , width(fmt::format("{}.width", this->rect_id))
    , height(fmt::format("{}.height", this->rect_id)) {}

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

namespace {
const bool verbose_build_repr = false;
}

Vec<Str> ConstraintBase::getBuildRepr(hstd::Opt<RectMap> const& rects) const {
    Vec<Str> joined;
    if (rects) {
        for (auto const& c : build(rects.value())) {
            if (verbose_build_repr) {
                joined.append(split(tree_repr(c), "\n"));
            } else {
                joined.append(split(flat_repr(c), "\n"));
            }
        }
    }
    return joined;
}

AlignConstraint::AlignConstraint(Vec<AlignItem> items, Strength strength)
    : ConstraintBase(strength), items(std::move(items)) {}

Vec<kiwi_ir::Constraint> AlignConstraint::build(RectMap const& rects) const {
    if (items.size() < 2) {
        throw std::runtime_error("AlignConstraint requires at least 2 items");
    }
    auto const& base      = items[0];
    Expr        base_expr = rects.at(base.rect_id).anchor_expr(base.spec.anchor)
                          - base.spec.offset;
    Vec<kiwi_ir::Constraint> result;
    for (int i = 1; i < items.size(); ++i) {
        auto const& item = items[i];
        Expr        expr = rects.at(item.rect_id).anchor_expr(item.spec.anchor)
                         - item.spec.offset;
        result.push_back((expr == base_expr) | kiwi_value(strength));
    }
    return result;
}

Vec<EdgeDesc> AlignConstraint::describe_edges() const {
    Vec<EdgeDesc> edges;
    for (auto const& item : items) {
        edges.push_back(
            EdgeDesc{
                item.rect_id,
                fmt::format("align:{}", item.spec.anchor),
                anchor_axis(item.spec.anchor)});
    }
    return edges;
}

Str AlignConstraint::getRepr(hstd::Opt<RectMap> const& rects) const {
    Vec<Str> joined;
    joined.push_back(hstd::fmt("AlignConstraint strength={}", strength));
    for (auto const& item : items) {
        joined.push_back(
            fmt::format(
                "  {} {} ({:+g})", item.rect_id, item.spec.anchor, item.spec.offset));
    }

    joined.append(getBuildRepr(rects));

    return hstd::join("\n", joined);
}

SeparateConstraint::SeparateConstraint(
    RectSpec1Side const& rect_a,
    RectSpec1Side const& rect_b,
    double               offset,
    Strength             strength)
    : ConstraintBase(strength), rect_a(rect_a), rect_b(rect_b), offset(offset) {}

Vec<kiwi_ir::Constraint> SeparateConstraint::build(RectMap const& rects) const {
    Expr                first  = rects.at(rect_a.rect_id).anchor_expr(rect_a.anchor);
    Expr                second = rects.at(rect_b.rect_id).anchor_expr(rect_b.anchor);
    kiwi_ir::Constraint c      = (first == (second + offset)) | kiwi_value(strength);
    return {c};
}

Vec<EdgeDesc> SeparateConstraint::describe_edges() const {
    return {
        EdgeDesc{
            rect_b.rect_id,
            fmt::format("separate:{}->{}+{}", rect_b.anchor, rect_b.anchor, offset),
            anchor_axis(rect_b.anchor),
        },
        EdgeDesc{
            rect_a.rect_id,
            fmt::format("separate:{}->{}+{}", rect_b.anchor, rect_a.anchor, offset),
            anchor_axis(rect_a.anchor),
        },
    };
}

Str SeparateConstraint::getRepr(hstd::Opt<RectMap> const& rects) const {
    return fmt::format(
        "SeparateConstraint({}.{} == {}.{} + {:g}, strength={})",
        rect_a.rect_id,
        rect_a.anchor,
        rect_b.rect_id,
        rect_b.anchor,
        offset,
        strength);
}

MultiSeparateConstraint::MultiSeparateConstraint(
    Vec<Vec<RectSpec1Side>> groups,
    double                  step,
    Strength                strength)
    : ConstraintBase(strength), groups(std::move(groups)), step(step) {
    hstd::UnorderedMap<Str, Pair<int, int>> s;
    for (auto const& [idx, lane] : hstd::enumerate(groups)) {
        for (auto const& [item_idx, item] : hstd::enumerate(lane)) {
            if (auto prev = s.get(item.rect_id)) {
                throw hstd::invalid_argument::init(
                    hstd::fmt(
                        "Multi-separate constraint cannot reuse vertex ID "
                        "across multiple lanes or multiple times in "
                        "the same row. Rect ID '{}' has already been "
                        "encountered at [{}][{}] and was reused at "
                        "[{}][{}]",
                        item.rect_id,
                        prev->first,
                        prev->second,
                        idx,
                        item_idx));
            }

            s.insert_or_assign(item.rect_id, Pair<int, int>{idx, item_idx});
        }
    }
}

Vec<kiwi_ir::Constraint> MultiSeparateConstraint::build(RectMap const& rects) const {
    Vec<kiwi_ir::Constraint> constraints;
    for (auto const& [g1, g2] : groups | hstd::rv_sliding_tuple2) {
        if (g1.empty() || g2.empty()) {
            throw hstd::runtime_error::init(
                "MultiSeparateConstraint requires at least one element in "
                "each group");
        }

        Expr expr_a //
            = rects.at(g1[0].rect_id).anchor_expr(g1[0].anchor).loc();
        Expr expr_b //
            = rects.at(g2[0].rect_id).anchor_expr(g2[0].anchor).loc();

        // align anchor positions on the individual rectangles.
        // ┌────┐     ┌────┐
        // │ a  │     │ b  │
        // └────┘     └────┘
        // ▲          ▲
        // └──────────┘
        //  a + step = b
        constraints.push_back(((expr_a + step) == expr_b).loc() | kiwi_value(strength));
    }

    for (auto const& g : groups) {
        for (auto const& [g_prev, g_next] : g | hstd::rv_sliding_tuple2) {
            // align individual elements in the stack.
            //
            //         │
            // ┌───────┼───┐
            // │g_prev │   │
            // └───────┼───┘
            //         │
            //         ▲
            //         ▼
            //         │
            // ┌───────┼───┐
            // │g_next │   │
            // └───────┼───┘
            //         │
            Expr expr_g_prev //
                = rects.at(g_prev.rect_id).anchor_expr(g_prev.anchor);
            Expr expr_g_next //
                = rects.at(g_next.rect_id).anchor_expr(g_next.anchor);
            constraints.push_back(
                (expr_g_prev == expr_g_next).loc() | kiwi_value(strength));
        }
    }

    return constraints;
}

Vec<EdgeDesc> MultiSeparateConstraint::describe_edges() const {
    Vec<EdgeDesc> edges;
    for (int idx = 0; idx + 1 < groups.size(); ++idx) {
        for (auto const& rect : groups[idx]) {
            edges.push_back(
                EdgeDesc{
                    rect.rect_id,
                    fmt::format("multi-separate:{}+{:g}", rect.anchor, step),
                    anchor_axis(rect.anchor)});
        }
    }
    return edges;
}

Str MultiSeparateConstraint::getRepr(hstd::Opt<RectMap> const& rects) const {
    std::ostringstream out;
    Vec<Vec<Str>>      g_fmt;
    for (int i = 0; i < groups.size(); ++i) {
        g_fmt.push_back({hstd::fmt("GR {}", i)});
        for (int j = 0; j < groups[i].size(); ++j) {
            g_fmt.back().push_back(
                hstd::fmt("{} {}", groups[i][j].rect_id, groups[i][j].anchor));
        }
    }

    Vec<Str> joined;
    joined.push_back(
        fmt::format("MultiSeparateConstraint(step={:g} strength={})", step, strength));

    auto     t_1   = Str{hstd::format_table(g_fmt, " => ", "")};
    auto     ind   = hstd::indent(t_1, 2);
    Vec<Str> table = split(ind, '\n');
    joined.append(table);
    joined.append(getBuildRepr(rects));

    return hstd::join("\n", joined);
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

Vec<kiwi_ir::Constraint> ParentWrapConstraint::build(RectMap const& rects) const {
    if (nested_rect_ids.empty()) { return {}; }

    Rect const&              parent = rects.at(parent_rect_id);
    Vec<kiwi_ir::Constraint> constraints;

    Vec<Expr> left_exprs;
    Vec<Expr> top_exprs;
    Vec<Expr> right_exprs;
    Vec<Expr> bottom_exprs;

    for (auto const& nested_id : nested_rect_ids) {
        left_exprs.push_back(rects.at(nested_id).anchor_expr(Anchor::LEFT));
        top_exprs.push_back(rects.at(nested_id).anchor_expr(Anchor::TOP));
        right_exprs.push_back(rects.at(nested_id).anchor_expr(Anchor::RIGHT));
        bottom_exprs.push_back(rects.at(nested_id).anchor_expr(Anchor::BOTTOM));
    }

    for (auto const& nested_left : left_exprs) {
        constraints.push_back(
            (parent.anchor_expr(Anchor::LEFT) <= (nested_left - pad.left)).loc()
            | kiwi_value(strength));
    }

    for (auto const& nested_top : top_exprs) {
        constraints.push_back(
            (parent.anchor_expr(Anchor::TOP) <= (nested_top - pad.top)).loc()
            | kiwi_value(strength));
    }

    for (auto const& nested_right : right_exprs) {
        constraints.push_back(
            ((nested_right + pad.right) <= parent.anchor_expr(Anchor::RIGHT)).loc()
            | kiwi_value(strength));
    }

    for (auto const& nested_bottom : bottom_exprs) {
        constraints.push_back(
            ((nested_bottom + pad.bottom) <= parent.anchor_expr(Anchor::BOTTOM)).loc()
            | kiwi_value(strength));
    }

    constraints.push_back(
        (parent.anchor_expr(Anchor::LEFT) == (left_exprs[0] - pad.left)).loc()
        | kiwi_value(strength));
    constraints.push_back(
        (parent.anchor_expr(Anchor::TOP) == (top_exprs[0] - pad.top)).loc()
        | kiwi_value(strength));
    constraints.push_back(
        (parent.anchor_expr(Anchor::RIGHT)
         == (right_exprs[right_exprs.size() - 1] + pad.right))
            .loc()
        | kiwi_value(strength));
    constraints.push_back(
        (parent.anchor_expr(Anchor::BOTTOM)
         == (bottom_exprs[bottom_exprs.size() - 1] + pad.bottom))
            .loc()
        | kiwi_value(strength));

    return constraints;
}

Vec<EdgeDesc> ParentWrapConstraint::describe_edges() const {
    Vec<EdgeDesc> edges;
    edges.push_back(EdgeDesc{parent_rect_id, "wrap-parent-x", Axis::X});
    edges.push_back(EdgeDesc{parent_rect_id, "wrap-parent-y", Axis::Y});
    for (auto const& nested_id : nested_rect_ids) {
        edges.push_back(EdgeDesc{nested_id, "wrap-parent-x", Axis::X});
        edges.push_back(EdgeDesc{nested_id, "wrap-parent-y", Axis::Y});
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
    return fmt::format(
        "ParentWrapConstraint(parent={}, nested={}, padding={}, "
        "strength={})",
        parent_rect_id,
        nested.str(),
        pad,
        strength);
}

RelativeConstraint::RelativeConstraint(
    Str              parent_rect_id,
    Str              relative_rect_id,
    RelDimensionSpec x_dim,
    RelDimensionSpec y_dim,
    AnchorSpec       anchor_fixed,
    AnchorSpec       anchor_relative,
    Strength         strength)
    : ConstraintBase(strength)
    , relative_rect_id(std::move(relative_rect_id))
    , fixed_rect_id(std::move(parent_rect_id))
    , x_dim(x_dim)
    , y_dim(y_dim)
    , anchor_relative(anchor_relative)
    , anchor_fixed(anchor_fixed) {}

Vec<kiwi_ir::Constraint> RelativeConstraint::build(RectMap const& rects) const {
    Rect const&              rel = rects.at(relative_rect_id);
    Rect const&              fix = rects.at(fixed_rect_id);
    Vec<kiwi_ir::Constraint> constraints;

    if (x_dim.size_factor.has_value()) {
        constraints.push_back(
            (rel.expr(RectAttr::WIDTH)
             == (fix.expr(RectAttr::WIDTH) * x_dim.size_factor.value()))
                .loc()
            | kiwi_value(strength));
    }

    if (y_dim.size_factor.has_value()) {
        constraints.push_back(
            (rel.expr(RectAttr::HEIGHT)
             // TODO: See [[configurable-offset-comparison-directions]]
             == (fix.expr(RectAttr::HEIGHT) * y_dim.size_factor.value()))
                .loc()
            | kiwi_value(strength));
    }

    if (x_dim.relative_offset) {
        constraints.push_back(
            (rel.anchor_expr(anchor_relative.x)
             == (fix.anchor_expr(anchor_fixed.x)
                 + (x_dim.relative_offset.value() * fix.expr(RectAttr::WIDTH))
                 + x_dim.absolute_offset))
                .loc()
            | kiwi_value(strength));

    } else {
        constraints.push_back(
            (rel.anchor_expr(anchor_relative.x)
             == (fix.anchor_expr(anchor_fixed.x) + x_dim.absolute_offset))
                .loc()
            | kiwi_value(strength));
    }

    if (y_dim.relative_offset) {
        constraints.push_back(
            (rel.anchor_expr(anchor_relative.y)
             == (fix.anchor_expr(anchor_fixed.y)
                 + (y_dim.relative_offset.value() * fix.expr(RectAttr::HEIGHT))
                 + y_dim.absolute_offset))
                .loc()
            | kiwi_value(strength));
    } else {
        constraints.push_back(
            (rel.anchor_expr(anchor_relative.y)
             == (fix.anchor_expr(anchor_fixed.y) + y_dim.absolute_offset))
                .loc()
            | kiwi_value(strength));
    }


    return constraints;
}

Vec<EdgeDesc> RelativeConstraint::describe_edges() const {
    Vec<EdgeDesc> edges = {
        EdgeDesc{fixed_rect_id, "fixed-x", Axis::X},
        EdgeDesc{fixed_rect_id, "fixed-y", Axis::Y},
        EdgeDesc{relative_rect_id, "relative-x", Axis::X},
        EdgeDesc{relative_rect_id, "relative-y", Axis::Y},
    };


    return edges;
}

Str RelativeConstraint::getRepr(hstd::Opt<RectMap> const& rects) const {
    // FIXME: implement repr for relative constraint.
    Vec<Str> joined;
    joined.push_back(
        hstd::fmt(
            "RelativeConstraint fixed:{} relative:{}", fixed_rect_id, relative_rect_id));

    joined.push_back(hstd::fmt("  x_dim           {}", x_dim));
    joined.push_back(hstd::fmt("  y_dim           {}", y_dim));
    joined.push_back(hstd::fmt("  anchor_fixed    {}", anchor_fixed));
    joined.push_back(hstd::fmt("  anchor_relative {}", anchor_relative));
    joined.append(getBuildRepr(rects));

    return hstd::join("\n", joined);

    // Str wf = x_factor.has_value() ? fmt::format("{:g}",
    // x_factor.value())
    //                               : "None";
    // Str hf = y_factor.has_value() ? fmt::format("{:g}",
    // y_factor.value())
    //                               : "None";
    // return fmt::format(
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


EvenGapConstraint::EvenGapConstraint(Vec<RectSpec2Side> rects_spec, Strength strength)
    : ConstraintBase(strength), rects_spec(std::move(rects_spec)) {
    for (auto const& spec : this->rects_spec) {
        if (anchor_axis(spec.min_anchor) != anchor_axis(spec.max_anchor)) {
            throw hstd::invalid_argument::init(
                fmt::format(
                    "EvenGapConstraint: min/max anchors of '{}' are on "
                    "different axes "
                    "({} vs {})",
                    spec.rect_id,
                    spec.min_anchor,
                    spec.max_anchor));
        }
    }

    if (!this->rects_spec.empty()) {
        Axis common_axis = anchor_axis(this->rects_spec.front().min_anchor);
        for (auto const& spec : this->rects_spec) {
            if (anchor_axis(spec.min_anchor) != common_axis) {
                throw hstd::invalid_argument::init(
                    fmt::format(
                        "EvenGapConstraint: mixed axes are not allowed, "
                        "'{}' has axis {} "
                        "while expected {}",
                        spec.rect_id,
                        anchor_axis(spec.min_anchor),
                        common_axis));
            }
        }
    }
}

Vec<kiwi_ir::Constraint> EvenGapConstraint::build(RectMap const& rects) const {
    if (rects_spec.size() < 3) { return {}; }

    Vec<kiwi_ir::Constraint> constraints;
    for (auto const& [prev, curr, next] : hstd::rv_sliding_tuple3(rects_spec)) {
        Expr prev_max //
            = rects.at(prev.rect_id).anchor_expr(prev.max_anchor);
        Expr curr_min //
            = rects.at(curr.rect_id).anchor_expr(curr.min_anchor);
        Expr curr_max //
            = rects.at(curr.rect_id).anchor_expr(curr.max_anchor);
        Expr next_min //
            = rects.at(next.rect_id).anchor_expr(next.min_anchor);

        constraints.push_back(
            ((curr_min - prev_max) == (next_min - curr_max)).loc()
            | kiwi_value(strength));
    }

    return constraints;
}

Vec<EdgeDesc> EvenGapConstraint::describe_edges() const {
    Vec<EdgeDesc> result;
    for (auto const& g : rects_spec) {
        result.push_back(
            EdgeDesc{
                g.rect_id,
                fmt::format("even-gap:{}->{}", g.max_anchor, g.min_anchor),
                anchor_axis(g.max_anchor)});
    }
    return result;
}

Str EvenGapConstraint::getRepr(hstd::Opt<RectMap> const& rects) const {
    Vec<Str> joined;

    joined.push_back(fmt::format("EvenGapConstraint(strength={})", strength));

    for (int i = 0; i < rects_spec.size(); ++i) {
        RectSpec2Side const& s = rects_spec[i];
        joined.push_back(
            fmt::format(
                "  id={}, min={}, max={}", s.rect_id, s.min_anchor, s.max_anchor));
    }

    joined.append(getBuildRepr(rects));
    return hstd::join("\n", joined);
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

Vec<kiwi_ir::Constraint> EqualSizeConstraint::build(RectMap const& rects) const {
    Rect const&              a = rects.at(rect_a_id);
    Rect const&              b = rects.at(rect_b_id);
    Vec<kiwi_ir::Constraint> constraints;
    if (match_width) {
        constraints.push_back(
            (a.expr(RectAttr::WIDTH) == b.expr(RectAttr::WIDTH)).loc()
            | kiwi_value(strength));
    }
    if (match_height) {
        constraints.push_back(
            (a.expr(RectAttr::HEIGHT) == b.expr(RectAttr::HEIGHT)).loc()
            | kiwi_value(strength));
    }
    return constraints;
}

Vec<EdgeDesc> EqualSizeConstraint::describe_edges() const {
    Vec<EdgeDesc> edges;
    if (match_width) {
        edges.push_back(EdgeDesc{rect_b_id, "equal-size:width", Axis::X});
        edges.push_back(EdgeDesc{rect_a_id, "equal-size:width", Axis::X});
    }
    if (match_height) {
        edges.push_back(EdgeDesc{rect_b_id, "equal-size:height", Axis::Y});
        edges.push_back(EdgeDesc{rect_a_id, "equal-size:height", Axis::Y});
    }
    return edges;
}

Str EqualSizeConstraint::getRepr(hstd::Opt<RectMap> const& rects) const {
    return fmt::format(
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
        c = (left == right).loc() | kiwi_value(strength);
    } else if (relation == Relation::LE) {
        c = (left <= right).loc() | kiwi_value(strength);
    } else if (relation == Relation::GE) {
        c = (right <= left).loc() | kiwi_value(strength);
    } else {
        throw std::runtime_error("Invalid relation");
    }
    return {c};
}

Vec<EdgeDesc> LinearConstraint::describe_edges() const { return {}; }

Str LinearConstraint::getRepr(hstd::Opt<RectMap> const& rects) const {
    Str rel = relation == Relation::EQ ? "==" : (relation == Relation::LE ? "<=" : ">=");
    Vec<Str> joined;
    joined.push_back(fmt::format("LinearConstraint({} ..., strength={})", rel, strength));

    joined.append(getBuildRepr(rects));

    return hstd::join("\n", joined);
}

Layout::Layout(Vec<Rect> rects, Vec<hstd::SPtr<ConstraintBase>> constraints)
    : constraints(std::move(constraints)) {
    for (auto& rect : rects) { this->rects.emplace(rect.rect_id, rect); }
}

RectMap Layout::solve() {
    kiwi::Solver solver;

    for (auto& [rect_id, rect] : rects) {
        solver.addConstraint(((Expr(0) <= rect.expr(RectAttr::WIDTH)))
                                 .loc()
                                 .to_kiwi(kiwi::strength::required));
        solver.addConstraint(((Expr(0) <= rect.expr(RectAttr::HEIGHT)))
                                 .loc()
                                 .to_kiwi(kiwi::strength::required));

        if (rect.x0.has_value()) {
            solver.addConstraint((rect.expr(RectAttr::X) == rect.x0.value())
                                     .loc()
                                     .to_kiwi(kiwi::strength::required));
        }
        if (rect.y0.has_value()) {
            solver.addConstraint((rect.expr(RectAttr::Y) == rect.y0.value())
                                     .loc()
                                     .to_kiwi(kiwi::strength::required));
        }
        if (rect.width0.has_value()) {
            solver.addConstraint((rect.expr(RectAttr::WIDTH) == rect.width0.value())
                                     .loc()
                                     .to_kiwi(kiwi::strength::required));
        }
        if (rect.height0.has_value()) {
            solver.addConstraint((rect.expr(RectAttr::HEIGHT) == rect.height0.value())
                                     .loc()
                                     .to_kiwi(kiwi::strength::required));
        }
    }

    for (auto const& item : constraints) {
        for (auto const& c : item->build(rects)) { solver.addConstraint(c.to_kiwi()); }
    }

    solver.updateVariables();
    return rects;
}

namespace {
namespace bg = boost::geometry;
Vec<std::pair<Str, Rect>> sort_rectangles_for_svg(
    Vec<std::pair<Str, Rect>> const& items) {

    using Graph  = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS>;
    using Vertex = boost::graph_traits<Graph>::vertex_descriptor;

    auto to_box = [](Rect const& g) -> geometry::Rect {
        return geometry::Rect{
            geometry::Point{g.x.value(), g.y.value()},
            geometry::Point{
                g.x.value() + g.width.value(), g.y.value() + g.height.value()}};
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
                boost::add_edge(static_cast<Vertex>(i), static_cast<Vertex>(j), g);
                continue;
            }

            if (j_contains_i && !i_contains_j) {
                boost::add_edge(static_cast<Vertex>(j), static_cast<Vertex>(i), g);
                continue;
            }

            if (prefer_before(i, j)) {
                boost::add_edge(static_cast<Vertex>(i), static_cast<Vertex>(j), g);
            } else {
                boost::add_edge(static_cast<Vertex>(j), static_cast<Vertex>(i), g);
            }
        }
    }

    Vec<Vertex> topo;
    try {
        boost::topological_sort(g, std::back_inserter(topo));
    } catch (boost::not_a_dag const&) {
        Vec<int> idx(items.size());
        for (int i = 0; i < items.size(); ++i) { idx[i] = i; }

        std::ranges::sort(idx, [&](int lhs, int rhs) { return prefer_before(lhs, rhs); });

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

    Vec<Str> colors = {"#ffcccc", "#ccffcc", "#ccccff", "#fff0cc", "#f0ccff", "#ccfff7"};

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
    result->setRankDirection(graph::gv::RankDirection::LR);
    std::unordered_map<Pair<Str, Axis>, hstd::SPtr<graph::gv::NodeAttribute>> rectNodes;

    auto cluster_x = result->newSubgraph("x_constraint");
    auto cluster_y = result->newSubgraph("y_constraint");

    for (auto const& axis : as_vec(Axis::X, Axis::Y)) {
        for (auto const& [rect_id, rect] : rects) {
            auto node = //
                (axis == Axis::X ? cluster_x : cluster_y)
                    ->node(fmt::format("rect-{}-{}", rect_id, axis));

            hstd::Vec<Str> rect_info;
            rect_info.push_back(hstd::fmt("{} {}", rect_id, axis));
            if (rect.x0) { rect_info.push_back(hstd::fmt("  x0 {}", rect.x0.value())); }

            if (rect.y0) { rect_info.push_back(hstd::fmt("  y0 {}", rect.y0.value())); }

            if (rect.width0) {
                rect_info.push_back(hstd::fmt("  width0  {}", rect.width0.value()));
            }

            if (rect.height0) {
                rect_info.push_back(hstd::fmt("  height0 {}", rect.height0.value()));
            }

            node->setLabel(hstd::join("\n", rect_info));
            node->setNodeShape(graph::gv::NodeShape::rectangle);
            rectNodes.insert_or_assign({rect_id, axis}, node);
        }
    }

    auto cluster_center = result->newSubgraph("center_constraint");
    cluster_center->setRank(graph::gv::Rank::same);

    for (int idx = 0; idx < constraints.size(); ++idx) {
        auto const& constraint = constraints[idx];
        Str         cid        = fmt::format("constraint-{}", idx);
        auto        cnode      = cluster_center->node(cid);
        cnode->setLabel(constraint->getRepr(rects));
        cnode->setNodeShape(graph::gv::NodeShape::rectangle);

        for (auto const& edge : constraint->describe_edges()) {
            auto constraint_to_rect_edge = //
                edge.axis == Axis::X
                    ? result->edge(*cnode, *rectNodes.at({edge.rect_id, edge.axis}))
                    : result->edge(*rectNodes.at({edge.rect_id, edge.axis}), *cnode);

            if (edge.axis == Axis::Y) {
                constraint_to_rect_edge->setEdgeDir(graph::gv::EdgeDir::back);
            }

            constraint_to_rect_edge->setColor(axis_color(edge.axis));
            if (!edge.label.empty()) { constraint_to_rect_edge->setLabel(edge.label); }
        }
    }

    result->render(path);
}

Vec<ConstraintEntry> Layout::build_constraint_entries() const {
    Vec<ConstraintEntry> entries;

    for (auto const& [rect_id, rect] : rects) {
        entries.push_back(
            ConstraintEntry{
                fmt::format("Rect({}).width >= 0", rect.rect_id),
                {(Expr(0) <= rect.expr(RectAttr::WIDTH)) | kiwi::strength::required},
            });
        entries.push_back(
            ConstraintEntry{
                fmt::format("Rect({}).height >= 0", rect.rect_id),
                {(Expr(0) <= rect.expr(RectAttr::HEIGHT)) | kiwi::strength::required},
            });

        if (rect.x0.has_value()) {
            entries.push_back(
                ConstraintEntry{
                    fmt::format("Rect({}).x == {:g}", rect.rect_id, rect.x0.value()),
                    {(rect.expr(RectAttr::X) == rect.x0.value())
                     | kiwi::strength::required},
                });
        }
        if (rect.y0.has_value()) {
            entries.push_back(
                ConstraintEntry{
                    fmt::format("Rect({}).y == {:g}", rect.rect_id, rect.y0.value()),
                    {(rect.expr(RectAttr::Y) == rect.y0.value())
                     | kiwi::strength::required},
                });
        }
        if (rect.width0.has_value()) {
            entries.push_back(
                ConstraintEntry{
                    fmt::format(
                        "Rect({}).width == {:g}", rect.rect_id, rect.width0.value()),
                    {(rect.expr(RectAttr::WIDTH) == rect.width0.value())
                     | kiwi::strength::required},
                });
        }
        if (rect.height0.has_value()) {
            entries.push_back(
                ConstraintEntry{
                    fmt::format(
                        "Rect({}).height == {:g}", rect.rect_id, rect.height0.value()),
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

struct SatisfyFail {
    Vec<ConstraintEntry> preceding;
    int                  failing;
};

struct ConstraintFailure {
    ConstraintEntry        entry;
    hstd::Opt<SatisfyFail> desc;
};


namespace {
hstd::Result<std::monostate, SatisfyFail> is_satisfiable(
    Vec<ConstraintEntry> const& entries) {
    kiwi::Solver solver;

    Vec<ConstraintEntry> preceding;
    for (int eidx = 0; eidx < entries.size(); ++eidx) {
        auto const& entry = entries.at(eidx);
        preceding.push_back(entry);
        for (int lidx = 0; lidx < entry.lowered.size(); ++lidx) {
            try {
                solver.addConstraint(entry.lowered.at(lidx).to_kiwi());
            } catch (kiwi::UnsatisfiableConstraint const&) {
                return SatisfyFail{preceding, lidx};
            }
        }
    }

    return std::monostate{};
}

struct ConflictSet {
    Vec<ConstraintFailure> failures;
};

ConflictSet minimal_conflict_set(
    Vec<ConstraintEntry> const& active_entries,
    ConstraintEntry const&      failing_entry) {
    auto make_trial = [&](Vec<ConstraintEntry> const& conflict,
                          int                         skip_idx) -> Vec<ConstraintEntry> {
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
        if (sat.has_error()) {
            return ConstraintFailure{
                .entry = entry,
                .desc  = sat.assume_error(),
            };
        } else {
            return std::nullopt;
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

    ConflictSet result;
    for (int entry_idx = 0; entry_idx < conflict.size(); ++entry_idx) {
        Vec<ConstraintEntry> trial;
        for (int idx = 0; idx < conflict.size(); ++idx) {
            trial.push_back(conflict.at(idx));
        }
        trial.push_back(failing_entry);

        auto sat = is_satisfiable(trial);
        result.failures.push_back(
            ConstraintFailure{
                .entry = conflict.at(entry_idx),
                .desc  = //
                sat.has_error() ? std::make_optional(sat.assume_error()) : std::nullopt,
            });
    }

    return result;
}
} // namespace

void Layout::verify_constraints() {
    Vec<ConstraintEntry> entries = build_constraint_entries();
    kiwi::Solver         solver;
    Vec<ConstraintEntry> active_entries;

    auto describe_constraint_source =
        [&](std::variant<Str, hstd::SPtr<ConstraintBase>> const& source) -> Str {
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
            auto            conflicts = minimal_conflict_set(active_entries, entry);
            hstd::ColStream os;
            // NOTE: primary candidate for tree-like data representation
            // optimization. [[f69705c4-9013-4919-a540-3c473bbadbaf]]
            os << "Unsatisfiable layout constraints detected.\n";
            os << fmt::format(
                "Failing constraint: {}\n", describe_constraint_source(entry.source));

            auto describe_failure = [&](SatisfyFail const& fail) {
                if (1 < fail.preceding.size()) {
                    os.indent(4);
                    os << "- preceding constraints OK\n";
                } else {
                    os << "- no preceding constraints\n";
                }

                for (auto const& it : hstd::enumerator(fail.preceding)) {
                    os.indent(6);
                    os << "- ";
                    os.write_indented_after_first(
                        describe_constraint_source(it.value().source), 8);
                    os.newline();

                    auto write_lowered = [&](hstd::Span<kiwi_ir::Constraint> const& c) {
                        for (auto const& sub : c) {
                            os.indent(8);
                            os << "- ";
                            os.write_indented_after_first(flat_repr(sub), 10);
                            os.newline();
                        }
                    };

                    if (it.is_last()) {
                        if (0 < fail.failing) {
                            write_lowered(
                                it.value().lowered.at(hstd::slice(0, fail.failing - 1)));
                        }
                    } else {
                        write_lowered(it.value().lowered.toSpan());
                    }
                }

                os << fmt::format(
                    "    - first conflict detected when "
                    "adding lowered element {}\n",
                    flat_repr(fail.preceding.back().lowered.at(fail.failing)));
            };

            if (conflicts.failures.empty()) {
                os << "The failing constraint is internally "
                      "inconsistent.\n";

                auto sat_fail = is_satisfiable({entry});
                describe_failure(sat_fail.assume_error());
            } else {
                os << "Conflicts with:\n";
                for (auto const& src : conflicts.failures) {
                    os << fmt::format(
                        "  - {}\n", describe_constraint_source(src.entry.source));
                    describe_failure(src.desc.value());
                }
            }

            os.newline();
            throw ConstraintVerificationError::init(os.toString(false));
        }
        active_entries.push_back(entry);
    }
}


} // namespace hstd::ext::kiwi_ir

#endif
