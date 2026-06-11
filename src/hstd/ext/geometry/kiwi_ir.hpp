#pragma once

#include "hstd/stdlib/Map.hpp"
#include "hstd/stdlib/Outcome.hpp"
#include <optional>
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
#include <src/hstd/ext/geometry/kiwi_ir.pb.h>

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

// TODO: API should allow for arbitrary relative anchors instead of a fixed
// set of constaints. The "anchor" enum should be broken down into the
// tuple Axis+AnchorAxisRelative, with the AnchorAxisRelative just being a
// convenient shorthand for the `[0, 1]` range of values.
// <<kiwi-arbitrary-anchor-positions>>
DECL_DESCRIBED_ENUM_STANDALONE(
    Anchor,
    LEFT,
    HCENTER,
    RIGHT,
    TOP,
    VCENTER,
    BOTTOM);

DECL_DESCRIBED_ENUM_STANDALONE(
    AnchorAxisRelative,
    MIN_POS,
    MID_POS,
    MAX_POS);

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
Anchor get_anchor(Axis axis, AnchorAxisRelative rel);

Str tree_repr(kiwi::Expression const& c, int indent = 0);
Str tree_repr(kiwi::Constraint const& c, int indent = 0);
Str tree_repr(Vec<kiwi::Constraint> const& c, int indent = 0);

struct AnchorSpec {
  public:
    Anchor const x;
    Anchor const y;

    AnchorSpec(Anchor x = Anchor::LEFT, Anchor y = Anchor::TOP)
        : x{x}, y{y} {
        LOGIC_ASSERTION_CHECK_FMT(anchor_axis(x) == Axis::X, "{}", x);
        LOGIC_ASSERTION_CHECK_FMT(anchor_axis(y) == Axis::Y, "{}", y);
    }

    static AnchorSpec UpperLeft() {
        return AnchorSpec(Anchor::LEFT, Anchor::TOP);
    }

    static AnchorSpec LowerRight() {
        return AnchorSpec(Anchor::RIGHT, Anchor::BOTTOM);
    }

    static AnchorSpec CenterCenter() {
        return AnchorSpec(Anchor::HCENTER, Anchor::VCENTER);
    }

    void writeSerial(htsd::ext::kiwi_ir::proto::AnchorSpec* anc) const {
        anc->set_x(static_cast<::htsd::ext::kiwi_ir::proto::Anchor>(x));
        anc->set_y(static_cast<::htsd::ext::kiwi_ir::proto::Anchor>(y));
    }

    DESC_FIELDS(AnchorSpec, (x, y));
};

struct RectSpec2Side {
    Str    rect_id;
    Anchor min_anchor;
    Anchor max_anchor;

    DESC_FIELDS(RectSpec2Side, (rect_id, min_anchor, max_anchor));

    RectSpec2Side() {}
    RectSpec2Side(Str str, Anchor min, Anchor max)
        : rect_id{str}, min_anchor{min}, max_anchor{max} {}

    static RectSpec2Side HorizontalRectBounds(Str const& str) {
        return RectSpec2Side(str, Anchor::LEFT, Anchor::RIGHT);
    }

    static RectSpec2Side VerticalRectBounds(Str const& str) {
        return RectSpec2Side(str, Anchor::TOP, Anchor::BOTTOM);
    }
};

struct RectSpec1Side {
    Str    rect_id;
    Anchor anchor;

    DESC_FIELDS(RectSpec1Side, (rect_id, anchor));

    static RectSpec1Side Left(Str const& id) {
        return RectSpec1Side(id, Anchor::LEFT);
    }

    static RectSpec1Side Right(Str const& id) {
        return RectSpec1Side(id, Anchor::RIGHT);
    }

    static RectSpec1Side Top(Str const& id) {
        return RectSpec1Side(id, Anchor::TOP);
    }

    static RectSpec1Side Bottom(Str const& id) {
        return RectSpec1Side(id, Anchor::BOTTOM);
    }

    RectSpec1Side() {}
    RectSpec1Side(Str str, Anchor anchor) : rect_id{str}, anchor{anchor} {}
};

class Constraint;

class Expr {
  public:
    Expr(double value);
    Expr(kiwi::Variable const& value);
    Expr(kiwi::Expression const& value);

    Expr operator+(Expr const& other) const;
    Expr operator-(Expr const& other) const;
    Expr operator*(double other) const;
    Expr operator-() const;
    Expr operator*(Expr const& other) const;

    Constraint operator==(Expr const& other) const;
    Constraint operator<=(Expr const& other) const;
    Constraint operator>=(Expr const& other) const;

    struct Node {
        enum class Kind
        {
            Constant,
            Variable,
            KiwiExpression,
            Add,
            Sub,
            Mul,
            Neg
        };

        Kind                            kind;
        double                          constant = 0.0;
        std::optional<kiwi::Variable>   variable;
        std::optional<kiwi::Expression> kiwi_expr;
        std::shared_ptr<Node>           lhs;
        std::shared_ptr<Node>           rhs;
        int                             origin_line     = -1;
        char const*                     origin_function = nullptr;

        void writeSerial(
            ::htsd::ext::kiwi_ir::proto::Expr::Node* n) const {
            if (lhs) { lhs->writeSerial(n->mutable_lhs()); }
            if (rhs) { rhs->writeSerial(n->mutable_rhs()); }
            n->set_constant(constant);
            n->set_kind(
                static_cast<::htsd::ext::kiwi_ir::proto::Expr::Node::Kind>(
                    kind));
            n->set_variable(variable->name());
        }
    };

    std::shared_ptr<Node> node;

    Expr& loc(
        char const* function = __builtin_FUNCTION(),
        int         line     = __builtin_LINE()) {
        node->origin_line     = line;
        node->origin_function = function;
        return *this;
    }

    void writeSerial(::htsd::ext::kiwi_ir::proto::Expr* e) const {}

  private:
    explicit Expr(std::shared_ptr<Node> node);

    static std::shared_ptr<Node> make_constant(double value);
    static std::shared_ptr<Node> make_variable(
        kiwi::Variable const& value);
    static std::shared_ptr<Node> make_kiwi_expr(
        kiwi::Expression const& value);
    static std::shared_ptr<Node> make_unary(
        Node::Kind            kind,
        std::shared_ptr<Node> lhs);
    static std::shared_ptr<Node> make_binary(
        Node::Kind            kind,
        std::shared_ptr<Node> lhs,
        std::shared_ptr<Node> rhs);

    friend class Constraint;
    friend Str tree_repr(Expr const& c, int indent);
};

class Constraint {
  public:
    Constraint(
        Expr const&              lhs,
        Expr const&              rhs,
        kiwi::RelationalOperator op);

    kiwi::Constraint to_kiwi(hstd::Opt<double> str = std::nullopt) const;

    Constraint& operator|(double str) {
        this->strength = str;
        return *this;
    }

    Expr                     lhs;
    Expr                     rhs;
    kiwi::RelationalOperator op;
    hstd::Opt<double>        strength;

    int         origin_line     = -1;
    char const* origin_function = nullptr;

    Constraint& loc(
        char const* function = __builtin_FUNCTION(),
        int         line     = __builtin_LINE()) {
        origin_line     = line;
        origin_function = function;
        return *this;
    }

  private:
    static kiwi::Expression fold_expr(
        std::shared_ptr<Expr::Node const> const& node);
};


Expr operator+(double left, Expr const& right);
Expr operator-(double left, Expr const& right);
Expr operator*(double left, Expr const& right);

Str tree_repr(Expr const& c, int indent = 0);
Str tree_repr(Constraint const& c, int indent = 0);
Str tree_repr(Vec<Constraint> const& c, int indent = 0);
Str flat_repr(Expr const& n, bool full_flatten = false);
Str flat_repr(Constraint const& c, bool full_flatten = false);

struct Rect {
    Str         rect_id;
    Opt<double> x0;
    Opt<double> y0;
    Opt<double> width0;
    Opt<double> height0;
    // NOTE: See [[kiwi-rectangle-id-knowledge-direction]]
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
    Str            rect_id;
    Str            label;
    Axis           axis;
    hstd::Opt<Str> color;
};

class ConstraintBase {
  public:
    Strength strength;

    explicit ConstraintBase(Strength strength = Strength::REQUIRED);
    virtual ~ConstraintBase() = default;

    virtual Vec<kiwi_ir::Constraint> build(RectMap const& rects) const = 0;
    virtual Vec<EdgeDesc>            describe_edges() const            = 0;

    Vec<Str> getBuildRepr(hstd::Opt<RectMap> const& rects) const;

    virtual Str getRepr(
        hstd::Opt<RectMap> const& rects = std::nullopt) const = 0;
};

struct ConstraintEntry {
    std::variant<Str, hstd::SPtr<ConstraintBase>> source;
    Vec<kiwi_ir::Constraint>                      lowered;
};

Str describe_constraint_source(
    std::variant<Str, hstd::SPtr<ConstraintBase>> const& source);

class ConstraintVerificationError
    : public hstd::CRTP_hexception<ConstraintVerificationError> {};

struct AlignSpec {
    /// \brief The anchor line (e.g., LEFT, RIGHT, TOP) used to align the
    /// rectangles.
    Anchor anchor;
    double offset = 0.0;

    void writeSerial(::htsd::ext::kiwi_ir::proto::AlignSpec* as) const {
        as->set_anchor(
            static_cast<::htsd::ext::kiwi_ir::proto::Anchor>(anchor));
        as->set_offset(offset);
    }
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

    Vec<kiwi_ir::Constraint> build(RectMap const& rects) const override;
    Vec<EdgeDesc>            describe_edges() const override;
    Str                      getRepr(
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
    RectSpec1Side rect_a;
    RectSpec1Side rect_b;
    double        offset;

    SeparateConstraint(
        RectSpec1Side const& rect_a,
        RectSpec1Side const& rect_b,
        double               offset,
        Strength             strength = Strength::REQUIRED);

    Vec<kiwi_ir::Constraint> build(RectMap const& rects) const override;
    Vec<EdgeDesc>            describe_edges() const override;
    Str                      getRepr(
        hstd::Opt<RectMap> const& rects = std::nullopt) const override;
};

/// \brief Positions groups of rectangles with a fixed step between
/// corresponding elements of consecutive groups.
/// \details The elements are arranged in groups along axis, and then
/// the axes are separated relative to each other.
class MultiSeparateConstraint : public ConstraintBase {
  public:
    /// \brief Groups of rectangle IDs, each group set apart by step.
    Vec<Vec<RectSpec1Side>> groups;
    /// \brief Fixed distance between corresponding rectangles of
    /// consecutive groups.
    double step;

    MultiSeparateConstraint(
        Vec<Vec<RectSpec1Side>> groups,
        double                  step,
        Strength                strength = Strength::REQUIRED);

    Vec<kiwi_ir::Constraint> build(RectMap const& rects) const override;
    Vec<EdgeDesc>            describe_edges() const override;
    Str                      getRepr(
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
    /// \brief The rectangle that wraps its nestedren.
    Str parent_rect_id;
    /// \brief IDs of rectangles that should be inside the parent.
    Vec<Str> nested_rect_ids;
    /// \brief Minimum distance from the parent's edges to the nested
    /// elements.
    geometry::Padding pad;

    ParentWrapConstraint(
        Str                      parent_rect_id,
        Vec<Str>                 nested_rect_ids,
        geometry::Padding const& pad      = geometry::Padding(),
        Strength                 strength = Strength::REQUIRED);

    Vec<kiwi_ir::Constraint> build(RectMap const& rects) const override;
    Vec<EdgeDesc>            describe_edges() const override;
    Str                      getRepr(
        hstd::Opt<RectMap> const& rects = std::nullopt) const override;
};


// QUESTION: Split this structure into the "offset" and "size" parts?
struct RelDimensionSpec {
    /// \brief Optional factor to scale nested width/height relative to
    /// fixed rectangle.
    Opt<double> size_factor = std::nullopt;
    /// \brief Optional factor to configure position of the element
    /// relative to the fixed entry.
    Opt<double> relative_offset = std::nullopt;
    // TODO: Ideally, all of these coordinates must be specified in a
    // way where user could control the exact relation generated from
    // the variable. Instead of specifying the absolute offset as
    // strictly equal to some value, it might be possible to instead
    // specify the relative offset as "no closer than" or "no farther
    // than" to allow more space for the other constraints in the
    // problem. For now it is good enough, but this change should be
    // handled before the final branch is merged.
    // <<configurable-offset-comparison-directions>>
    /// \brief Offset of the nested element compared to the target
    double absolute_offset = 0.0;
    DESC_FIELDS(
        RelDimensionSpec,
        (size_factor, relative_offset, absolute_offset));

    void writeSerial(
        ::htsd::ext::kiwi_ir::proto::RelDimensionSpec* rd) const {
        if (size_factor.has_value()) {
            rd->set_size_factor(size_factor.value());
        }

        if (relative_offset.has_value()) {
            rd->set_relative_offset(relative_offset.value());
        }

        rd->set_absolute_offset(absolute_offset);
    }
};

/// \brief Constrain the nested rectangle position in relation to the
/// parent rectangle.
///
/// \details Creates constraints:
///
/// - if x_factor provided, nested.width = parent.width * x_factor
/// - if y_factor provided, nested.height = parent.height * y_factor
/// - nested.nested_x_anchor = parent.x_anchor + x_offset
/// - nested.nested_y_anchor = parent.y_anchor + y_offset
///
/// All with specified strength.
class RelativeConstraint : public ConstraintBase {
  public:
    /// \brief ID of the nested rectangle.
    Str relative_rect_id;
    /// \brief ID of the parent rectangle used for reference.
    Str fixed_rect_id;

    RelDimensionSpec x_dim;
    RelDimensionSpec y_dim;
    AnchorSpec       anchor_fixed;
    AnchorSpec       anchor_relative;

    // FIXME: The constructor API is brittle and hard to reason about, the
    // default constructor for RelAnchorSpec must have two different
    // parameter sets to work correctly. Need to come up with a better
    // design here.
    RelativeConstraint(
        Str              parent_rect_id,
        Str              nested_rect_id,
        RelDimensionSpec x_dim,
        RelDimensionSpec y_dim,
        AnchorSpec       anchor_fixed    = AnchorSpec::UpperLeft(),
        AnchorSpec       anchor_relative = AnchorSpec::UpperLeft(),
        Strength         strength        = Strength::REQUIRED);

    Vec<kiwi_ir::Constraint> build(RectMap const& rects) const override;
    Vec<EdgeDesc>            describe_edges() const override;
    Str                      getRepr(
        hstd::Opt<RectMap> const& rects = std::nullopt) const override;
};

/// \brief Equalizes the gaps between consecutive rectangles using
/// per-rectangle boundary anchors.
///
/// \details For each sliding 3-tuple of rectangle bounds
/// (spec[i-1], spec[i], spec[i+1]), this constraint enforces:
/// (pos(spec[i].min_anchor) - pos(spec[i-1].max_anchor))
/// ==
/// (pos(spec[i+1].min_anchor) - pos(spec[i].max_anchor)).
///
/// This means the free space between neighboring rectangles is equalized,
/// where each rectangle can provide its own boundary anchors.
///
/// \note No absolute gap size is imposed; only equality between adjacent
/// gaps is enforced. For fixed-size spacing, use \ref
/// MultiSeparateConstraint.
class EvenGapConstraint : public ConstraintBase {
  public:
    /// \brief Ordered list of per-rectangle boundary specifications.
    Vec<RectSpec2Side> rects_spec;

    EvenGapConstraint(
        Vec<RectSpec2Side> rects_spec,
        Strength           strength = Strength::REQUIRED);

    Vec<kiwi_ir::Constraint> build(RectMap const& rects) const override;
    Vec<EdgeDesc>            describe_edges() const override;
    Str                      getRepr(
        hstd::Opt<RectMap> const& rects = std::nullopt) const override;
};

/// \brief Ensure the width/height between two rectangles is matched.
///
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

    Vec<kiwi_ir::Constraint> build(RectMap const& rects) const override;
    Vec<EdgeDesc>            describe_edges() const override;
    Str                      getRepr(
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

    Vec<kiwi_ir::Constraint> build(RectMap const& rects) const override;
    Vec<EdgeDesc>            describe_edges() const override;
    Str                      getRepr(
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
};

} // namespace hstd::ext::kiwi_ir
