#pragma once

#include <hstd/ext/geometry/kiwi_ir.hpp>
#include <hstd/ext/graph/base/graph_base.hpp>
#include <hstd/ext/graph/visual/adaptagrams_common.hpp>
#include <hstd/ext/graph/visual/graph_avoid.hpp>
#include <hstd/ext/graph/visual/graph_visual.hpp>
#include <hstd/stdlib/algorithms.hpp>

namespace hstd::ext::graph::kw {

class KiwiVertexAttribute : public layout::IVertexVisualAttribute {
  public:
    std::string getRepr() const override { return "KiwiVertexAttribute"; }

    void writeSerial(proto::IAttribute* out, IGraph const* graph)
        const override {
        logic_todo_impl();
    }

    void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) override {
        logic_todo_impl();
    }

    KiwiVertexAttribute* setRectWidth(hstd::Opt<double> width) {
        rect.width0 = width;
        return this;
    }

    KiwiVertexAttribute* setRectHeight(hstd::Opt<double> height) {
        rect.height0 = height;
        return this;
    }

    KiwiVertexAttribute* setRectX(hstd::Opt<double> x) {
        rect.x0 = x;
        return this;
    }

    KiwiVertexAttribute* setRectY(hstd::Opt<double> y) {
        rect.y0 = y;
        return this;
    }

    // FIXME: <<kiwi-rectangle-id-knowledge-direction>> The rectangle
    // object must have access to the stable ID at the construction time,
    // meaning the kiwi vertex attribute must know which ID it is
    // associated with -- even though the information is not stored in a
    // way that can be used to retrieve it back. This breaks the DOD logic
    // which requires individual objects to be completely oblivious of its
    // placement in the mapping/collection. I'm not going to work on fixing
    // this now, because it would require significant rework of the
    // `geometry::Rect` constructor, hiding the width variable field and
    // insetad exposing `getWidth(Str const& id)` that would construct it
    // as needed.
    kiwi_ir::Rect rect;
    explicit KiwiVertexAttribute(kiwi_ir::Rect const& rect) : rect{rect} {}
};

class KiwiEdgeAttribute : public layout::IEdgeVisualAttribute {
  public:
    std::string getRepr() const override { return "KiwiEdgeAttribute"; }
    void        writeSerial(proto::IAttribute* out, IGraph const* graph)
        const override {
        logic_todo_impl();
    }
    void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) override {
        logic_todo_impl();
    }
};

class KiwiConstraint;
class AlignConstraint;
class SeparateConstraint;
class MultiSeparateConstraint;

class KiwiGroup
    : public layout::IGroupVisualAttribute
    , public std::enable_shared_from_this<KiwiGroup> {
  public:
    struct SharedCtx {
        hstd::SPtr<layout::LayoutRun> run;
    };

    struct LocalCtx {
        hstd::Str name;
    };

    std::string getRepr() const override { return "KiwiGroup"; }
    void        writeSerial(proto::IAttribute* out, IGraph const* graph)
        const override {
        logic_todo_impl();
    }
    void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) override {
        logic_todo_impl();
    }

    hstd::SPtr<SharedCtx>        shared;
    LocalCtx                     local;
    hstd::Opt<geometry::Padding> outerPadding;

    KiwiGroup(hstd::SPtr<SharedCtx> const& ctx, hstd::Str const& name)
        : layout::IGroupVisualAttribute{ctx->run}
        , shared{ctx}
        , local{.name = name} {}

    hstd::SPtr<layout::LayoutRun> const& getRun() const {
        return shared->run;
    }

    std::string getStableId() const override {
        return hstd::fmt("KiwiGroup-{}", local.name);
    }

    void setOuterPadding(geometry::Padding const& pad) override {
        outerPadding = pad;
    }

    hstd::Opt<geometry::Padding> getOuterPadding() const override {
        return outerPadding;
    }

    /// \brief add vertex to the kiwi group without specifying any
    /// width/rect elements.
    hstd::SPtr<KiwiVertexAttribute> addVertex(EdgeID const& edge);

    hstd::SPtr<KiwiVertexAttribute> addVertex(
        EdgeID const&         edge,
        geometry::Rect const& size);

    hstd::SPtr<KiwiVertexAttribute> addVertex(
        EdgeID const&         edge,
        geometry::Size const& size) {
        return addVertex(
            edge, geometry::Rect(0, 0, size.width(), size.height()));
    }

    hstd::SPtr<KiwiEdgeAttribute> addEdge(EdgeID const& id) {
        auto res = std::make_shared<KiwiEdgeAttribute>();
        getRun()->setEdgeAttribute(id, res);
        return res;
    }

    hstd::SPtr<KiwiGroup> addNewNativeSubgroup(EdgeID const& edge) {
        auto res = std::make_shared<KiwiGroup>(
            shared, hstd::fmt("kiwi_{}", edge));
        getRun()->setNestedGroupAttribute(edge, res);
        return res;
    }

    static hstd::SPtr<KiwiGroup> newRootGraph(
        hstd::SPtr<layout::LayoutRun> run,
        Str const&                    name = "root");
};

class KiwiVertexLayoutAttribute : public layout::IVertexLayoutAttribute {
  public:
    std::string getRepr() const override {
        return "KiwiVertexLayoutAttribute";
    }

    void writeSerial(proto::IAttribute* out, IGraph const* graph)
        const override {
        logic_todo_impl();
    }

    void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) override {
        logic_todo_impl();
    }

    geometry::Rect rect;
    std::string    text;

    KiwiVertexLayoutAttribute(geometry::Rect rect, std::string text = "")
        : rect{rect}, text{text} {}

    Rect getBBox() const override { return rect; }

    visual::VisGroup getVisual(VertexID const& selfId) const override {
        visual::VisGroup res;
        auto             bb = getBBox();
        res.offset          = bb.upper_left();
        res.elements.push_back(
            visual::VisElement{visual::VisElement::RectShape{
                getBBox().move(-bb.upper_left())}});
        res.elements.push_back(
            visual::VisElement::FromText(
                text.empty() ? hstd::fmt("{}", selfId) : text));
        res.custom.setAttr(
            "inkscape:label", hstd::fmt("KIWI VERTEX:{}", selfId));
        return res;
    }
};

class KiwiGroupLayoutAttribute : public layout::IGroupLayoutAttribute {
  public:
    std::string getRepr() const override {
        return "KiwiGroupLayoutAttribute";
    }

    void writeSerial(proto::IAttribute* out, IGraph const* graph)
        const override {
        logic_todo_impl();
    }

    void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) override {
        logic_todo_impl();
    }

    visual::VisGroup getVisual(VertexID const& id) const override;

    Rect                  rect;
    hstd::SPtr<KiwiGroup> group;

    KiwiGroupLayoutAttribute(Rect rect, hstd::SPtr<KiwiGroup> group)
        : rect{rect}, group{group} {}

    Rect getBBox() const override { return rect; }
    void setBBox(geometry::Rect const& _rect) override { rect = _rect; }
};

class KiwiConstraint : public layout::IConstraint {
  protected:
    hstd::SPtr<layout::LayoutRun> run;
    kiwi_ir::Strength             strength = kiwi_ir::Strength::REQUIRED;

    Str rectId(VertexID const& id) const {
        return run->getVertex(id)->getStableId();
    }

  public:
    explicit KiwiConstraint(hstd::SPtr<KiwiGroup> const& group)
        : run(group->getRun()) {}
    explicit KiwiConstraint(hstd::SPtr<layout::LayoutRun> const& run)
        : run(run) {}

    virtual hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> getKiwi()
        const = 0;

    KiwiConstraint* setStrength(kiwi_ir::Strength strength) {
        this->strength = strength;
        return this;
    }

    virtual std::string getRepr() const { return "KiwiConstraint"; }
};

class ParentWrapConstraint : public KiwiConstraint {
    VertexID          parent;
    VertexIDVec       nested;
    geometry::Padding pad;

  public:
    ParentWrapConstraint(
        hstd::SPtr<KiwiGroup> const& group,
        VertexID const&              parent)
        : KiwiConstraint{group}, parent{parent} {}

    ParentWrapConstraint* setPadding(geometry::Padding const& pad) {
        this->pad = pad;
        return this;
    }

    ParentWrapConstraint* addVertex(VertexID const& id) {
        nested.push_back(id);
        return this;
    }

    hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> getKiwi()
        const override;

    VertexIDVec getAllVertices() const override {
        return nested + VertexIDVec{parent};
    }
};

class RelativeConstraint : public KiwiConstraint {
  public:
    hstd::Vec<VertexID> getAllVertices() const override {
        return {fixed.id, relative.id};
    }

    struct VertexRef {
        VertexID            id     = VertexID::Nil();
        kiwi_ir::AnchorSpec anchor = kiwi_ir::AnchorSpec::UpperLeft();
    };

    VertexRef fixed;
    VertexRef relative;

    kiwi_ir::RelDimensionSpec x_dim;
    kiwi_ir::RelDimensionSpec y_dim;

    RelativeConstraint* setRelativeOffset(
        hstd::Opt<double> x,
        hstd::Opt<double> y) {
        x_dim.relative_offset = x;
        y_dim.relative_offset = y;
        return this;
    }

    RelativeConstraint* setRelativeSize(
        hstd::Opt<double> x,
        hstd::Opt<double> y) {
        x_dim.size_factor = x;
        y_dim.size_factor = y;
        return this;
    }

    RelativeConstraint* setAbsoluteOffset(double x, double y) {
        x_dim.absolute_offset = x;
        y_dim.absolute_offset = y;
        return this;
    }

    RelativeConstraint(
        hstd::SPtr<KiwiGroup> const& group,
        VertexRef const&             fixed,
        VertexRef const&             relative)
        : KiwiConstraint{group}, fixed{fixed}, relative{relative} {}

    RelativeConstraint(
        hstd::SPtr<KiwiGroup> const& group,
        VertexID const&              fixed,
        VertexID const&              relative)
        : KiwiConstraint{group}
        , fixed{VertexRef{fixed}}
        , relative{VertexRef{relative}} {}

    hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> getKiwi()
        const override;
};

class EvenGapConstraint : public KiwiConstraint {
    VertexIDVec vertices;

  public:
    hstd::Vec<VertexID> getAllVertices() const override {
        return vertices;
    }

    kiwi_ir::Anchor anchor;
    kiwi_ir::Axis   axis = kiwi_ir::Axis::X;

    EvenGapConstraint* spaceHorizontally() {
        axis = kiwi_ir::Axis::X;
        return this;
    }

    EvenGapConstraint* addVertex(VertexID const& id) {
        vertices.push_back(id);
        return this;
    }

    EvenGapConstraint(hstd::SPtr<KiwiGroup> const& group)
        : KiwiConstraint{group} {}

    hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> getKiwi()
        const override;
};


class EqualSizeConstraint : public KiwiConstraint {
    VertexID vert_a;
    VertexID vert_b;
    bool     match_width  = false;
    bool     match_height = false;

  public:
    hstd::Vec<VertexID> getAllVertices() const override {
        return {vert_a, vert_b};
    }

    EqualSizeConstraint* matchWidth(bool match = true) {
        this->match_width = match;
        return this;
    }

    EqualSizeConstraint* matchHeight(bool match = true) {
        this->match_height = match;
        return this;
    }

    EqualSizeConstraint(
        hstd::SPtr<KiwiGroup> const& group,
        VertexID                     a,
        VertexID                     b)
        : KiwiConstraint{group}, vert_a{a}, vert_b{b} {}

    hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> getKiwi()
        const override;
};

class LinearConstraint : public KiwiConstraint {
    VertexIDSet vertices;
    // optional to allow deferred construction, all fields are required to
    // build the final constraint.
    hstd::Opt<kiwi_ir::Expr> lhs;
    hstd::Opt<kiwi_ir::Expr> rhs;
    kiwi_ir::Relation        rel;

  public:
    kiwi_ir::Expr use(VertexID const& id, kiwi_ir::RectAttr attr) {
        vertices.incl(id);
        return run->getVertex(id)
            ->getUniqueAttribute<KiwiVertexAttribute>(run->getDebug(id))
            ->rect.expr(attr);
    }

    Str use(VertexID const& id) {
        vertices.incl(id);
        return rectId(id);
    }

    hstd::Vec<VertexID> getAllVertices() const override {
        return vertices.items();
    }

    void finalize(
        kiwi_ir::Expr const& lhs,
        kiwi_ir::Relation    rel,
        kiwi_ir::Expr const& rhs) {
        LOGIC_ASSERTION_CHECK(!this->lhs.has_value(), "");
        LOGIC_ASSERTION_CHECK(!this->rhs.has_value(), "");
        this->rel = rel;
        this->lhs = lhs;
        this->rhs = rhs;
    }

    LinearConstraint* setSecondLeftOfFirst(
        VertexID fixed,
        VertexID relative) {
        finalize(
            use(fixed, kiwi_ir::RectAttr::LEFT),
            kiwi_ir::Relation::LE,
            use(relative, kiwi_ir::RectAttr::RIGHT));
        return this;
    }

    LinearConstraint* setSecondRightOfFirst(
        VertexID fixed,
        VertexID relative) {
        finalize(
            use(fixed, kiwi_ir::RectAttr::RIGHT),
            kiwi_ir::Relation::LE,
            use(relative, kiwi_ir::RectAttr::LEFT));
        return this;
    }

    LinearConstraint* setSecondBelowFirst(
        VertexID fixed,
        VertexID relative) {
        finalize(
            use(fixed, kiwi_ir::RectAttr::BOTTOM),
            kiwi_ir::Relation::LE,
            use(relative, kiwi_ir::RectAttr::TOP));
        return this;
    }

    LinearConstraint* setSecondAboveFirst(
        VertexID fixed,
        VertexID relative) {
        finalize(
            use(fixed, kiwi_ir::RectAttr::TOP),
            kiwi_ir::Relation::LE,
            use(relative, kiwi_ir::RectAttr::BOTTOM));
        return this;
    }


    LinearConstraint(hstd::SPtr<KiwiGroup> const& group)
        : KiwiConstraint{group} {}

    hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> getKiwi()
        const override;
};

class AlignConstraint : public KiwiConstraint {
  public:
    void writeSerial(proto::IConstraint* out, IGraph const* graph)
        const override {
        logic_todo_impl();
    }

    void readSerial(proto::IConstraint const* in, IGraph const* graph)
        override {
        logic_todo_impl();
    }

    DECL_DESCRIBED_ENUM(AxisAlign, Center, Top, Bottom, Left, Right);

    hstd::UnorderedMap<VertexID, kiwi_ir::AlignSpec> vertices;
    /// Which axis to partition nodes
    kiwi_ir::Axis dimension = kiwi_ir::Axis::X;
    DESC_FIELDS(AlignConstraint, (vertices, dimension));

    using KiwiConstraint::KiwiConstraint;

    VertexIDVec getAllVertices() const override { return vertices.keys(); }

    std::string getRepr() const override {
        return hstd::fmt("align {}", getAllVertices());
    }

    AlignConstraint* addAlignVertex(
        VertexID const&            id,
        hstd::Opt<kiwi_ir::Anchor> align  = std::nullopt,
        double                     offset = 0);

    AlignConstraint* useVerticalAxis() {
        dimension = kiwi_ir::Axis::X;
        return this;
    }

    AlignConstraint* useHorizontalAxis() {
        dimension = kiwi_ir::Axis::Y;
        return this;
    }

    hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> getKiwi()
        const override;
};

// TODO: Simplify implementation of the constraint: it should be trivially
// convertible to the kiwi_ir constraint intead of managing its own
// sub-structure of the layouts. The `separateHorizontally` was ported into
// the higher-level constraint because the align constraints require more
// annoying logic to change the axis direction. That should also be
// addressed. Ultimately all high-level graph-based constraints should act
// as a thin wrappers around kiwi_ir.
//
// This should be doen before writing protobuf description for the kiwi
// layout specification.
class SeparateConstraint : public KiwiConstraint {
  public:
    /// \brief The first lane to align
    AlignConstraint left;
    /// \brief Second lane to align
    AlignConstraint right;
    double          separationDistance = 1.0;
    bool            isExactSeparation  = false;
    kiwi_ir::Axis   dimension          = kiwi_ir::Axis::X;
    DESC_FIELDS(
        SeparateConstraint,
        (left, right, separationDistance, isExactSeparation, dimension));

    explicit SeparateConstraint(hstd::SPtr<KiwiGroup> const& group)
        : KiwiConstraint(group), left(group), right(group) {}

    VertexIDVec getAllVertices() const override {
        return left.getAllVertices() + right.getAllVertices();
    }

    std::string getRepr() const override {
        return hstd::fmt(
            "separate {} <> {}", left.getRepr(), right.getRepr());
    }

    /// \brief The lanes are placed vertically, with the separation
    /// distance configuring the X-offset between the lanes.
    SeparateConstraint* separateHorizontally() {
        dimension = kiwi_ir::Axis::X;
        left.useVerticalAxis();
        right.useVerticalAxis();
        return this;
    }

    /// \brief The lanes are placed horizontally, with the separation
    /// distance configuring the Y-offset between the lanes.
    SeparateConstraint* separateVertically() {
        dimension = kiwi_ir::Axis::Y;
        left.useHorizontalAxis();
        right.useHorizontalAxis();
        return this;
    }

    SeparateConstraint* setSeparationDistance(double distance) {
        this->separationDistance = distance;
        return this;
    }

    SeparateConstraint* setIsExactSeparation(bool exact) {
        this->isExactSeparation = exact;
        return this;
    }

    SeparateConstraint* addLeftVertex(
        VertexID const&            id,
        hstd::Opt<kiwi_ir::Anchor> align  = std::nullopt,
        double                     offset = 0) {
        left.addAlignVertex(id, align, offset);
        return this;
    }

    /// \brief Add vertex to the first alignment lane.
    SeparateConstraint* addLeftVertex(VertexIDVec const& id) {
        for (auto const& i : id) { addLeftVertex(i); }
        return this;
    }

    SeparateConstraint* addRightVertex(VertexIDVec const& id) {
        for (auto const& i : id) { addRightVertex(i); }
        return this;
    }

    /// \brief Add vertex to the second alignment lane.
    SeparateConstraint* addRightVertex(
        VertexID const&            id,
        hstd::Opt<kiwi_ir::Anchor> align  = std::nullopt,
        double                     offset = 0) {
        right.addAlignVertex(id, align, offset);
        return this;
    }

    hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> getKiwi()
        const override;
};

class MultiSeparateConstraint : public KiwiConstraint {
  public:
    hstd::Vec<AlignConstraint> lines;
    kiwi_ir::Axis              dimension          = kiwi_ir::Axis::X;
    double                     separationDistance = 0.0;
    DESC_FIELDS(
        MultiSeparateConstraint,
        (lines, dimension, separationDistance));

    using KiwiConstraint::KiwiConstraint;

    VertexIDVec getAllVertices() const override {
        VertexIDVec res;
        for (auto const& align : lines) {
            res.append(align.getAllVertices());
        }
        return res;
    }

    MultiSeparateConstraint* setSeparationDistance(double distance) {
        this->separationDistance = distance;
        return this;
    }

    MultiSeparateConstraint* addLane() {
        auto align      = AlignConstraint(run);
        align.dimension = dimension;
        lines.push_back(align);
        return this;
    }

    int getLaneCount() const { return lines.size(); }

    MultiSeparateConstraint* addMultiLane(int count) {
        for (int i = 0; i < count; ++i) { addLane(); }
        return this;
    }

    /// \brief Add a vertex to the *existing* lane, with specified offset
    /// parameters.
    MultiSeparateConstraint* addAlignVertex(
        VertexID const&            id,
        int                        lane,
        hstd::Opt<kiwi_ir::Anchor> align  = std::nullopt,
        double                     offset = 0) {
        LOGIC_ASSERTION_CHECK_FMT(
            lines.has(lane),
            "Cannot insert vertext to lane {}, call `addLane()` to match "
            "the lane count",
            lane);
        lines.at(lane).addAlignVertex(id, align, offset);
        return this;
    }

    /// \brief Add a fully new lane with the fixed set of vertices.
    MultiSeparateConstraint* addFullLane(VertexIDVec const& vertices) {
        addLane();
        for (auto const& vert : vertices) {
            lines.back().addAlignVertex(vert);
        }
        return this;
    }

    MultiSeparateConstraint* separateHorizontally() {
        dimension = kiwi_ir::Axis::X;
        for (auto& lane : lines) { lane.useVerticalAxis(); }
        return this;
    }

    MultiSeparateConstraint* separateVertically() {
        dimension = kiwi_ir::Axis::Y;
        for (auto& lane : lines) { lane.useHorizontalAxis(); }
        return this;
    }

    hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> getKiwi()
        const override;
};


class KiwiLayoutAlgorithm : public layout::IPlacementAlgorithm {
  public:
    std::shared_ptr<cst::AvoidRouterAlgorithm> router;

    Result runSingleLayout(VertexID const& group) override;

    KiwiLayoutAlgorithm(
        hstd::SPtr<layout::LayoutRun>              run,
        std::shared_ptr<cst::AvoidRouterAlgorithm> _router = nullptr)
        : layout::IPlacementAlgorithm{run} {
        if (_router == nullptr) {
            router = std::make_shared<cst::AvoidRouterAlgorithm>();
        } else {
            router = _router;
        }
    }
};

} // namespace hstd::ext::graph::kw
