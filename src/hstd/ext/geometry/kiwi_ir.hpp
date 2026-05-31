#pragma once

#include <exception>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Xml.hpp>
#include <hstd/system/reflection.hpp>
#include <kiwi/constraint.h>
#include <kiwi/expression.h>
#include <kiwi/solver.h>
#include <kiwi/symbolics.h>
#include <kiwi/variable.h>

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

double      kiwi_value(Strength strength);
Axis        anchor_axis(Anchor anchor);
std::string axis_color(Axis axis);

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
    std::string           rect_id;
    std::optional<double> x0;
    std::optional<double> y0;
    std::optional<double> width0;
    std::optional<double> height0;
    kiwi::Variable        x;
    kiwi::Variable        y;
    kiwi::Variable        width;
    kiwi::Variable        height;

    Rect(
        std::string           rect_id,
        std::optional<double> x0      = std::nullopt,
        std::optional<double> y0      = std::nullopt,
        std::optional<double> width0  = std::nullopt,
        std::optional<double> height0 = std::nullopt);

    Expr expr(RectAttr name) const;
    Expr anchor_expr(Anchor anchor) const;
};

struct EdgeDesc {
    std::string src;
    std::string dst;
    std::string label;
    std::string color;
};

class ConstraintBase {
  public:
    Strength strength;

    explicit ConstraintBase(Strength strength = Strength::REQUIRED);
    virtual ~ConstraintBase() = default;

    virtual std::vector<kiwi::Constraint> build(
        std::unordered_map<std::string, Rect> const& rects) const = 0;
    virtual std::vector<EdgeDesc> describe_edges() const          = 0;
    virtual std::string           getRepr() const                 = 0;
};

struct ConstraintEntry {
    std::variant<std::string, hstd::SPtr<ConstraintBase>> source;
    std::vector<kiwi::Constraint>                         lowered;
};

std::string describe_constraint_source(
    std::variant<std::string, hstd::SPtr<ConstraintBase>> const& source);

class ConstraintVerificationError : public std::exception {
  public:
    std::variant<std::string, hstd::SPtr<ConstraintBase>> failing_source;
    std::vector<std::variant<std::string, hstd::SPtr<ConstraintBase>>>
                conflicting_sources;
    std::string message;

    ConstraintVerificationError(
        std::variant<std::string, hstd::SPtr<ConstraintBase>>
            failing_source,
        std::vector<std::variant<std::string, hstd::SPtr<ConstraintBase>>>
            conflicting_sources);

    char const* what() const noexcept override;
};

struct AlignItem {
    std::string rect_id;
    double      offset = 0.0;
};

class AlignConstraint : public ConstraintBase {
  public:
    Anchor                 anchor;
    std::vector<AlignItem> items;

    AlignConstraint(
        Anchor                 anchor,
        std::vector<AlignItem> items,
        Strength               strength = Strength::REQUIRED);

    std::vector<kiwi::Constraint> build(
        std::unordered_map<std::string, Rect> const& rects) const override;
    std::vector<EdgeDesc> describe_edges() const override;
    std::string           getRepr() const override;
};

class SeparateConstraint : public ConstraintBase {
  public:
    std::string first_rect_id;
    Anchor      first_anchor;
    std::string second_rect_id;
    Anchor      second_anchor;
    double      offset;

    SeparateConstraint(
        std::string first_rect_id,
        Anchor      first_anchor,
        std::string second_rect_id,
        Anchor      second_anchor,
        double      offset,
        Strength    strength = Strength::REQUIRED);

    std::vector<kiwi::Constraint> build(
        std::unordered_map<std::string, Rect> const& rects) const override;
    std::vector<EdgeDesc> describe_edges() const override;
    std::string           getRepr() const override;
};

class MultiSeparateConstraint : public ConstraintBase {
  public:
    std::vector<std::vector<std::string>> groups;
    Anchor                                anchor;
    double                                step;

    MultiSeparateConstraint(
        std::vector<std::vector<std::string>> groups,
        Anchor                                anchor,
        double                                step,
        Strength strength = Strength::REQUIRED);

    std::vector<kiwi::Constraint> build(
        std::unordered_map<std::string, Rect> const& rects) const override;
    std::vector<EdgeDesc> describe_edges() const override;
    std::string           getRepr() const override;
};

class ParentWrapConstraint : public ConstraintBase {
  public:
    std::string              parent_rect_id;
    std::vector<std::string> child_rect_ids;
    double                   padding_left;
    double                   padding_top;
    double                   padding_right;
    double                   padding_bottom;

    ParentWrapConstraint(
        std::string              parent_rect_id,
        std::vector<std::string> child_rect_ids,
        double                   padding_left   = 0.0,
        double                   padding_top    = 0.0,
        double                   padding_right  = 0.0,
        double                   padding_bottom = 0.0,
        Strength                 strength       = Strength::REQUIRED);

    std::vector<kiwi::Constraint> build(
        std::unordered_map<std::string, Rect> const& rects) const override;
    std::vector<EdgeDesc> describe_edges() const override;
    std::string           getRepr() const override;
};

class ChildRelativeToParentConstraint : public ConstraintBase {
  public:
    std::string           child_rect_id;
    std::string           parent_rect_id;
    std::optional<double> width_factor;
    std::optional<double> height_factor;
    Anchor                x_anchor;
    Anchor                y_anchor;
    double                x_offset;
    double                y_offset;
    Anchor                child_x_anchor;
    Anchor                child_y_anchor;

    ChildRelativeToParentConstraint(
        std::string           child_rect_id,
        std::string           parent_rect_id,
        std::optional<double> width_factor   = std::nullopt,
        std::optional<double> height_factor  = std::nullopt,
        Anchor                x_anchor       = Anchor::LEFT,
        Anchor                y_anchor       = Anchor::TOP,
        double                x_offset       = 0.0,
        double                y_offset       = 0.0,
        Anchor                child_x_anchor = Anchor::LEFT,
        Anchor                child_y_anchor = Anchor::TOP,
        Strength              strength       = Strength::REQUIRED);

    std::vector<kiwi::Constraint> build(
        std::unordered_map<std::string, Rect> const& rects) const override;
    std::vector<EdgeDesc> describe_edges() const override;
    std::string           getRepr() const override;
};

class EvenGapConstraint : public ConstraintBase {
  public:
    std::vector<std::string> rect_ids;
    Axis                     axis;
    Anchor                   anchor;

    EvenGapConstraint(
        std::vector<std::string> rect_ids,
        Axis                     axis,
        Anchor                   anchor,
        Strength                 strength = Strength::REQUIRED);

    std::vector<kiwi::Constraint> build(
        std::unordered_map<std::string, Rect> const& rects) const override;
    std::vector<EdgeDesc> describe_edges() const override;
    std::string           getRepr() const override;
};

class EqualSizeConstraint : public ConstraintBase {
  public:
    std::string rect_a_id;
    std::string rect_b_id;
    bool        match_width;
    bool        match_height;

    EqualSizeConstraint(
        std::string rect_a_id,
        std::string rect_b_id,
        bool        match_width  = false,
        bool        match_height = false,
        Strength    strength     = Strength::REQUIRED);

    std::vector<kiwi::Constraint> build(
        std::unordered_map<std::string, Rect> const& rects) const override;
    std::vector<EdgeDesc> describe_edges() const override;
    std::string           getRepr() const override;
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

    std::vector<kiwi::Constraint> build(
        std::unordered_map<std::string, Rect> const& rects) const override;
    std::vector<EdgeDesc> describe_edges() const override;
    std::string           getRepr() const override;
};

class Layout {
  public:
    std::unordered_map<std::string, Rect>   rects;
    std::vector<hstd::SPtr<ConstraintBase>> constraints;

    Layout(
        std::vector<Rect>                       rects,
        std::vector<hstd::SPtr<ConstraintBase>> constraints);

    std::unordered_map<std::string, Rect> solve();
    void                                  to_svg(
        hstd::fs::path const& path,
        std::string const&    title = "layout");
    void to_graphviz(hstd::fs::path const& path);
    void verify_constraints();

  private:
    std::vector<ConstraintEntry> build_constraint_entries() const;
    bool is_satisfiable(std::vector<ConstraintEntry> const& entries) const;
    std::vector<ConstraintEntry> minimal_conflict_set(
        std::vector<ConstraintEntry> const& active_entries,
        ConstraintEntry const&              failing_entry) const;
};

} // namespace hstd::ext::kiwi_ir
