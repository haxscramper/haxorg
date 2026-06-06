#pragma once

#include "hstd/stdlib/Map.hpp"
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

template <>
struct std::formatter<kiwi::Variable> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        kiwi::Variable const& p,
        FormatContext&        ctx) const {
        return ::hstd::fmt_ctx(p.name(), ctx);
    }
};

template <>
struct std::formatter<kiwi::Term> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(kiwi::Term const& p, FormatContext& ctx)
        const {
        return ::hstd::fmt_ctx(p.variable(), ctx);
    }
};


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

Str tree_repr(kiwi::Constraint const& c, int indent = 0);
Str tree_repr(Vec<kiwi::Constraint> const& c, int indent = 0);


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

using RectMap = hstd::UnorderedMap<Str, Rect>;

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

    virtual Vec<kiwi::Constraint> build(RectMap const& rects) const = 0;
    virtual Vec<EdgeDesc>         describe_edges() const            = 0;
    virtual Str                   getRepr(
        hstd::Opt<RectMap> const& rects = std::nullopt) const = 0;
};

struct ConstraintEntry {
    std::variant<Str, hstd::SPtr<ConstraintBase>> source;
    Vec<kiwi::Constraint>                         lowered;
};

Str describe_constraint_source(
    std::variant<Str, hstd::SPtr<ConstraintBase>> const& source);

class ConstraintVerificationError
    : public hstd::CRTP_hexception<ConstraintVerificationError> {
  public:
    std::variant<Str, hstd::SPtr<ConstraintBase>>      failing_source;
    Vec<std::variant<Str, hstd::SPtr<ConstraintBase>>> conflicting_sources;
    Str                                                message_buf;

    ConstraintVerificationError(
        std::variant<Str, hstd::SPtr<ConstraintBase>> failing_source,
        Vec<std::variant<Str, hstd::SPtr<ConstraintBase>>>
            conflicting_sources);

    char const* message() const noexcept override;
};

struct AlignSpec {
    /// \brief The anchor line (e.g., LEFT, RIGHT, TOP) used to align the
    /// rectangles.
    Anchor anchor;
    double offset = 0.0;
};

struct AlignItem {
    Str       rect_id;
    AlignSpec spec;
};

/// \brief Aligns multiple rectangles by a common anchor line.
/// \details Creates equality constraints: for i>0,
/// anchor_expr(rects[i]) - offset_i == anchor_expr(rects[0]) - offset_0.
/// All constraints use the specified strength.
///
/// The first item serves as the reference; subsequent items are aligned to
/// it.
class AlignConstraint : public ConstraintBase {
  public:
    /// \brief List of rectangles with optional offsets; the first item is
    /// the reference.
    Vec<AlignItem> items;

    AlignConstraint(
        Vec<AlignItem> items,
        Strength       strength = Strength::REQUIRED);

    Vec<kiwi::Constraint> build(RectMap const& rects) const override;
    Vec<EdgeDesc>         describe_edges() const override;
    Str                   getRepr(
        hstd::Opt<RectMap> const& rects = std::nullopt) const override;
};

/// \brief Separate constraint creates to lanes of shapes (with one or more
/// shape per lane) and then arranges so the lanes would have a fixed
/// distance between them. Each lane is managed by the align constraint, so
/// it is possible to offset the individual shapes relative to the lane.
///
/// \details Creates a single equality constraint:
/// anchor_expr(first_rect, first_anchor)
///  == anchor_expr(second_rect, second_anchor) + offset.
class SeparateConstraint : public ConstraintBase {
  public:
    // TODO: Replace direct usage of the basic ID with the Align
    /// \brief ID of the first rectangle.
    Str first_rect_id;
    /// \brief Anchor on the first rectangle.
    Anchor first_anchor;
    /// \brief ID of the second rectangle.
    Str second_rect_id;
    /// \brief Anchor on the second rectangle.
    Anchor second_anchor;
    /// \brief Distance between the two anchors; can be positive or
    /// negative.
    double offset;

    SeparateConstraint(
        Str      first_rect_id,
        Anchor   first_anchor,
        Str      second_rect_id,
        Anchor   second_anchor,
        double   offset,
        Strength strength = Strength::REQUIRED);

    Vec<kiwi::Constraint> build(RectMap const& rects) const override;
    Vec<EdgeDesc>         describe_edges() const override;
    Str                   getRepr(
        hstd::Opt<RectMap> const& rects = std::nullopt) const override;
};

/// \brief Positions groups of rectangles with a fixed step between
/// corresponding elements of consecutive groups.
/// \details The elements are arranged in groups along axis, and then
/// the axes are separated relative to each other.
class MultiSeparateConstraint : public ConstraintBase {
  public:
    /// \brief Groups of rectangle IDs, each group set apart by step.
    Vec<Vec<Str>> groups;
    /// \brief Anchor used for measuring distances between groups.
    Anchor anchor;
    /// \brief Fixed distance between corresponding rectangles of
    /// consecutive groups.
    double step;

    MultiSeparateConstraint(
        Vec<Vec<Str>> groups,
        Anchor        anchor,
        double        step,
        Strength      strength = Strength::REQUIRED);

    Vec<kiwi::Constraint> build(RectMap const& rects) const override;
    Vec<EdgeDesc>         describe_edges() const override;
    Str                   getRepr(
        hstd::Opt<RectMap> const& rects = std::nullopt) const override;
};

/// \brief Ensure the "parent" rectangle fully covers the nested IDs.
/// \details Creates constraints that ensure each nested rectangle is
/// within the parent with given padding:
/// - left <= nested_left - padding_left
/// - top <= nested_top - padding_top
/// - right >= nested_right + padding_right
/// - bottom >= nested_bottom + padding_bottom
/// Also pins parent edges to the first/last nested edges with padding:
/// parent.left = first_nested.left - padding_left,
/// parent.top = first_nested.top - padding_top,
/// parent.right = last_nested.right + padding_right,
/// parent.bottom = last_nested.bottom + padding_bottom.
class ParentWrapConstraint : public ConstraintBase {
  public:
    /// \brief The rectangle that wraps its children.
    Str parent_rect_id;
    /// \brief IDs of rectangles that should be inside the parent.
    Vec<Str> nested_rect_ids;
    /// \brief Minimum distance from parent left edge to children's left
    /// edges.
    double padding_left;
    /// \brief Minimum distance from parent top edge to children's top
    /// edges.
    double padding_top;
    /// \brief Minimum distance from children's right edges to parent right
    /// edge.
    double padding_right;
    /// \brief Minimum distance from children's bottom edges to parent
    /// bottom edge.
    double padding_bottom;

    ParentWrapConstraint(
        Str      parent_rect_id,
        Vec<Str> nested_rect_ids,
        double   padding_left   = 0.0,
        double   padding_top    = 0.0,
        double   padding_right  = 0.0,
        double   padding_bottom = 0.0,
        Strength strength       = Strength::REQUIRED);

    Vec<kiwi::Constraint> build(RectMap const& rects) const override;
    Vec<EdgeDesc>         describe_edges() const override;
    Str                   getRepr(
        hstd::Opt<RectMap> const& rects = std::nullopt) const override;
};

/// \brief Constrain the nested rectangle position in relation to the
/// parent rectangle.
/// \details Creates constraints:
/// - if width_factor provided, child.width = parent.width * width_factor
/// - if height_factor provided, child.height = parent.height *
/// height_factor
/// - child.nested_x_anchor = parent.x_anchor + x_offset
/// - child.nested_y_anchor = parent.y_anchor + y_offset
/// All with specified strength.
class RelativeConstraint : public ConstraintBase {
  public:
    /// \brief ID of the child rectangle.
    Str nested_rect_id;
    /// \brief ID of the parent rectangle used for reference.
    Str parent_rect_id;
    /// \brief Optional factor to scale child width relative to parent.
    Opt<double> width_factor;
    /// \brief Optional factor to scale child height relative to parent.
    Opt<double> height_factor;
    /// \brief Anchor on the parent for the X coordinate.
    Anchor x_anchor;
    /// \brief Anchor on the parent for the Y coordinate.
    Anchor y_anchor;
    /// \brief Offset in the X direction from the parent anchor.
    double x_offset;
    /// \brief Offset in the Y direction from the parent anchor.
    double y_offset;
    /// \brief Anchor on the child that is aligned to parent x_anchor +
    /// x_offset.
    Anchor nested_x_anchor;
    /// \brief Anchor on the child that is aligned to parent y_anchor +
    /// y_offset.
    Anchor nested_y_anchor;

    RelativeConstraint(
        Str         nested_rect_id,
        Str         parent_rect_id,
        Opt<double> width_factor    = std::nullopt,
        Opt<double> height_factor   = std::nullopt,
        Anchor      x_anchor        = Anchor::LEFT,
        Anchor      y_anchor        = Anchor::TOP,
        double      x_offset        = 0.0,
        double      y_offset        = 0.0,
        Anchor      nested_x_anchor = Anchor::LEFT,
        Anchor      nested_y_anchor = Anchor::TOP,
        Strength    strength        = Strength::REQUIRED);

    Vec<kiwi::Constraint> build(RectMap const& rects) const override;
    Vec<EdgeDesc>         describe_edges() const override;
    Str                   getRepr(
        hstd::Opt<RectMap> const& rects = std::nullopt) const override;
};

/// \brief The distance between the diagram elements is equal along the x/y
/// axis.
/// \details Creates constraints for a sliding 3-tuple:
/// (rect[i-1], rect[i], rect[i+1]) such that the gap between
/// rect[i] and rect[i-1] equals the gap between rect[i+1] and rect[i]:
/// (anchor_expr(rect[i]) - anchor_expr(rect[i-1]))
/// == (anchor_expr(rect[i+1]) - anchor_expr(rect[i])).
///
/// \note The distance is not fixed to some specified amount, but only
/// equalized among the several elements. For fixed gap placement use \ref
/// MultiSeparateConstraint constraint.
class EvenGapConstraint : public ConstraintBase {
  public:
    /// \brief Ordered list of rectangle IDs.
    Vec<Str> rect_ids;
    /// \brief Axis along which gaps are equalized (X or Y).
    Axis axis;
    /// \brief The anchor point used for measuring positions.
    Anchor anchor;

    EvenGapConstraint(
        Vec<Str> rect_ids,
        Axis     axis,
        Anchor   anchor,
        Strength strength = Strength::REQUIRED);

    Vec<kiwi::Constraint> build(RectMap const& rects) const override;
    Vec<EdgeDesc>         describe_edges() const override;
    Str                   getRepr(
        hstd::Opt<RectMap> const& rects = std::nullopt) const override;
};

/// \brief Ensure the width/height between two rectangles is matched.
/// \details If match_width: creates constraint
/// rect_a.width == rect_b.width.
/// If match_height: rect_a.height == rect_b.height.
class EqualSizeConstraint : public ConstraintBase {
  public:
    /// \brief ID of the first rectangle.
    Str rect_a_id;
    /// \brief ID of the second rectangle.
    Str rect_b_id;
    /// \brief If true, constrains widths to be equal.
    bool match_width;
    /// \brief If true, constrains heights to be equal.
    bool match_height;

    EqualSizeConstraint(
        Str      rect_a_id,
        Str      rect_b_id,
        bool     match_width  = false,
        bool     match_height = false,
        Strength strength     = Strength::REQUIRED);

    Vec<kiwi::Constraint> build(RectMap const& rects) const override;
    Vec<EdgeDesc>         describe_edges() const override;
    Str                   getRepr(
        hstd::Opt<RectMap> const& rects = std::nullopt) const override;
};

/// \brief Free-form constraint between different elements on the graph.
/// \details Creates a single kiwi::Constraint using left and right
/// expressions with the given relation and strength.
class LinearConstraint : public ConstraintBase {
  public:
    /// \brief Left-hand side expression.
    Expr left;
    /// \brief Relation: EQ, LE, GE.
    Relation relation;
    /// \brief Right-hand side expression.
    Expr right;

    LinearConstraint(
        Expr     left,
        Relation relation,
        Expr     right,
        Strength strength = Strength::REQUIRED);

    Vec<kiwi::Constraint> build(RectMap const& rects) const override;
    Vec<EdgeDesc>         describe_edges() const override;
    Str                   getRepr(
        hstd::Opt<RectMap> const& rects = std::nullopt) const override;
};

class Layout {
  public:
    RectMap                         rects;
    Vec<hstd::SPtr<ConstraintBase>> constraints;

    Layout(Vec<Rect> rects, Vec<hstd::SPtr<ConstraintBase>> constraints);

    RectMap       solve();
    hstd::XmlNode to_svg(Str const& title = "layout");
    void          to_graphviz(hstd::fs::path const& path);
    void          verify_constraints();

  private:
    Vec<ConstraintEntry> build_constraint_entries() const;
    bool is_satisfiable(Vec<ConstraintEntry> const& entries) const;
    Vec<ConstraintEntry> minimal_conflict_set(
        Vec<ConstraintEntry> const& active_entries,
        ConstraintEntry const&      failing_entry) const;
};

} // namespace hstd::ext::kiwi_ir
