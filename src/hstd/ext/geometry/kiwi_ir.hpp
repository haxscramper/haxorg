#pragma once

#include <exception>
#include <optional>
#include <unordered_map>
#include <variant>

#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Xml.hpp>
#include <hstd/system/reflection.hpp>
#include <kiwi/constraint.h>
#include <kiwi/expression.h>
#include <kiwi/solver.h>
#include <kiwi/symbolics.h>
#include <kiwi/variable.h>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/ext/geometry/hstd_geometry.hpp>

namespace hstd::ext::kiwi_ir {

DECL_DESCRIBED_ENUM_STANDALONE(Axis, X, Y);
DECL_DESCRIBED_ENUM_STANDALONE(
    Anchor,
    LEFT,
    HCENTER,
    RIGHT,
    TOP,
    VCENTER,
    BOTTOM);
DECL_DESCRIBED_ENUM_STANDALONE(
    RectAttr,
    X,
    Y,
    WIDTH,
    HEIGHT,
    LEFT,
    HCENTER,
    RIGHT,
    TOP,
    VCENTER,
    BOTTOM);
DECL_DESCRIBED_ENUM_STANDALONE(Relation, EQ, LE, GE);
DECL_DESCRIBED_ENUM_STANDALONE(Strength, REQUIRED, STRONG, MEDIUM, WEAK);

double kiwi_value(Strength strength);
Axis   anchor_axis(Anchor anchor);
Str    axis_color(Axis axis);

class Expr {
  public:
    kiwi::Expression value;

    Expr(double value);
    Expr(kiwi::Variable const& value);
    Expr(kiwi::Expression const& value);

    kiwi::Expression const& to_kiwi() const;

    Expr operator+(Expr const& other) const;
    Expr operator-(Expr const& other) const;
    Expr operator*(double other) const;
    Expr operator-() const;

    Expr operator*(Expr const& other) const;
};

Expr operator+(double left, Expr const& right);
Expr operator-(double left, Expr const& right);
Expr operator*(double left, Expr const& right);

struct Rect {
    Str            rect_id;
    Opt<double>    x0;
    Opt<double>    y0;
    Opt<double>    width0;
    Opt<double>    height0;
    kiwi::Variable x;
    kiwi::Variable y;
    kiwi::Variable width;
    kiwi::Variable height;

    Rect(
        Str         rect_id,
        Opt<double> x0      = std::nullopt,
        Opt<double> y0      = std::nullopt,
        Opt<double> width0  = std::nullopt,
        Opt<double> height0 = std::nullopt);

    Expr expr(RectAttr name) const;
    Expr anchor_expr(Anchor anchor) const;

    geometry::Rect getGeometry() const {
        return geometry::Rect(
            x.value(), y.value(), width.value(), height.value());
    }
};

struct EdgeDesc {
    Str src;
    Str dst;
    Str label;
    Str color;
};

class ConstraintBase {
  public:
    Strength strength;

    explicit ConstraintBase(Strength strength = Strength::REQUIRED);
    virtual ~ConstraintBase() = default;

    virtual Vec<kiwi::Constraint> build(
        std::unordered_map<Str, Rect> const& rects) const = 0;
    virtual Vec<EdgeDesc> describe_edges() const          = 0;
    virtual Str           getRepr() const                 = 0;
};

struct ConstraintEntry {
    std::variant<Str, hstd::SPtr<ConstraintBase>> source;
    Vec<kiwi::Constraint>                         lowered;
};

Str describe_constraint_source(
    std::variant<Str, hstd::SPtr<ConstraintBase>> const& source);

class ConstraintVerificationError : public std::exception {
  public:
    std::variant<Str, hstd::SPtr<ConstraintBase>>      failing_source;
    Vec<std::variant<Str, hstd::SPtr<ConstraintBase>>> conflicting_sources;
    Str                                                message;

    ConstraintVerificationError(
        std::variant<Str, hstd::SPtr<ConstraintBase>> failing_source,
        Vec<std::variant<Str, hstd::SPtr<ConstraintBase>>>
            conflicting_sources);

    char const* what() const noexcept override;
};

struct AlignItem {
    Str    rect_id;
    double offset = 0.0;
};

class AlignConstraint : public ConstraintBase {
  public:
    Anchor         anchor;
    Vec<AlignItem> items;

    AlignConstraint(
        Anchor         anchor,
        Vec<AlignItem> items,
        Strength       strength = Strength::REQUIRED);

    Vec<kiwi::Constraint> build(
        std::unordered_map<Str, Rect> const& rects) const override;
    Vec<EdgeDesc> describe_edges() const override;
    Str           getRepr() const override;
};

class SeparateConstraint : public ConstraintBase {
  public:
    Str    first_rect_id;
    Anchor first_anchor;
    Str    second_rect_id;
    Anchor second_anchor;
    double offset;

    SeparateConstraint(
        Str      first_rect_id,
        Anchor   first_anchor,
        Str      second_rect_id,
        Anchor   second_anchor,
        double   offset,
        Strength strength = Strength::REQUIRED);

    Vec<kiwi::Constraint> build(
        std::unordered_map<Str, Rect> const& rects) const override;
    Vec<EdgeDesc> describe_edges() const override;
    Str           getRepr() const override;
};

class MultiSeparateConstraint : public ConstraintBase {
  public:
    Vec<Vec<Str>> groups;
    Anchor        anchor;
    double        step;

    MultiSeparateConstraint(
        Vec<Vec<Str>> groups,
        Anchor        anchor,
        double        step,
        Strength      strength = Strength::REQUIRED);

    Vec<kiwi::Constraint> build(
        std::unordered_map<Str, Rect> const& rects) const override;
    Vec<EdgeDesc> describe_edges() const override;
    Str           getRepr() const override;
};

class ParentWrapConstraint : public ConstraintBase {
  public:
    Str      parent_rect_id;
    Vec<Str> child_rect_ids;
    double   padding_left;
    double   padding_top;
    double   padding_right;
    double   padding_bottom;

    ParentWrapConstraint(
        Str      parent_rect_id,
        Vec<Str> child_rect_ids,
        double   padding_left   = 0.0,
        double   padding_top    = 0.0,
        double   padding_right  = 0.0,
        double   padding_bottom = 0.0,
        Strength strength       = Strength::REQUIRED);

    Vec<kiwi::Constraint> build(
        std::unordered_map<Str, Rect> const& rects) const override;
    Vec<EdgeDesc> describe_edges() const override;
    Str           getRepr() const override;
};

class ChildRelativeToParentConstraint : public ConstraintBase {
  public:
    Str         child_rect_id;
    Str         parent_rect_id;
    Opt<double> width_factor;
    Opt<double> height_factor;
    Anchor      x_anchor;
    Anchor      y_anchor;
    double      x_offset;
    double      y_offset;
    Anchor      child_x_anchor;
    Anchor      child_y_anchor;

    ChildRelativeToParentConstraint(
        Str         child_rect_id,
        Str         parent_rect_id,
        Opt<double> width_factor   = std::nullopt,
        Opt<double> height_factor  = std::nullopt,
        Anchor      x_anchor       = Anchor::LEFT,
        Anchor      y_anchor       = Anchor::TOP,
        double      x_offset       = 0.0,
        double      y_offset       = 0.0,
        Anchor      child_x_anchor = Anchor::LEFT,
        Anchor      child_y_anchor = Anchor::TOP,
        Strength    strength       = Strength::REQUIRED);

    Vec<kiwi::Constraint> build(
        std::unordered_map<Str, Rect> const& rects) const override;
    Vec<EdgeDesc> describe_edges() const override;
    Str           getRepr() const override;
};

class EvenGapConstraint : public ConstraintBase {
  public:
    Vec<Str> rect_ids;
    Axis     axis;
    Anchor   anchor;

    EvenGapConstraint(
        Vec<Str> rect_ids,
        Axis     axis,
        Anchor   anchor,
        Strength strength = Strength::REQUIRED);

    Vec<kiwi::Constraint> build(
        std::unordered_map<Str, Rect> const& rects) const override;
    Vec<EdgeDesc> describe_edges() const override;
    Str           getRepr() const override;
};

class EqualSizeConstraint : public ConstraintBase {
  public:
    Str  rect_a_id;
    Str  rect_b_id;
    bool match_width;
    bool match_height;

    EqualSizeConstraint(
        Str      rect_a_id,
        Str      rect_b_id,
        bool     match_width  = false,
        bool     match_height = false,
        Strength strength     = Strength::REQUIRED);

    Vec<kiwi::Constraint> build(
        std::unordered_map<Str, Rect> const& rects) const override;
    Vec<EdgeDesc> describe_edges() const override;
    Str           getRepr() const override;
};

class LinearConstraint : public ConstraintBase {
  public:
    Expr     left;
    Relation relation;
    Expr     right;

    LinearConstraint(
        Expr     left,
        Relation relation,
        Expr     right,
        Strength strength = Strength::REQUIRED);

    Vec<kiwi::Constraint> build(
        std::unordered_map<Str, Rect> const& rects) const override;
    Vec<EdgeDesc> describe_edges() const override;
    Str           getRepr() const override;
};

class Layout {
  public:
    std::unordered_map<Str, Rect>   rects;
    Vec<hstd::SPtr<ConstraintBase>> constraints;

    Layout(Vec<Rect> rects, Vec<hstd::SPtr<ConstraintBase>> constraints);

    std::unordered_map<Str, Rect> solve();
    void to_svg(hstd::fs::path const& path, Str const& title = "layout");
    void to_graphviz(hstd::fs::path const& path);
    void verify_constraints();

  private:
    Vec<ConstraintEntry> build_constraint_entries() const;
    bool is_satisfiable(Vec<ConstraintEntry> const& entries) const;
    Vec<ConstraintEntry> minimal_conflict_set(
        Vec<ConstraintEntry> const& active_entries,
        ConstraintEntry const&      failing_entry) const;
};

} // namespace hstd::ext::kiwi_ir
