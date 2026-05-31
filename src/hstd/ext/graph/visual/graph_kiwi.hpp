#pragma once

#include <hstd/ext/geometry/kiwi_ir.hpp>
#include <hstd/ext/graph/base/graph_base.hpp>
#include <hstd/ext/graph/visual/adaptagrams_common.hpp>
#include <hstd/ext/graph/visual/graph_avoid.hpp>
#include <hstd/ext/graph/visual/graph_visual.hpp>
#include <hstd/stdlib/algorithms.hpp>

namespace hstd::ext::graph::kw {

enum class [[refl]] GraphDimension
{
    XDIM  = 0,
    YDIM  = 1,
    UNSET = 2,
};

BOOST_DESCRIBE_ENUM(GraphDimension, XDIM, YDIM, UNSET);

class KiwiVertexAttribute : public layout::IVertexVisualAttribute {
  public:
    std::string getRepr() const override { return "KiwiVertexAttribute"; }
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

    geometry::Rect rect;
    explicit KiwiVertexAttribute(geometry::Rect const& rect)
        : rect{rect} {}
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

    hstd::SPtr<KiwiVertexAttribute> addVertex(
        EdgeID const&         edge,
        geometry::Rect const& size) {
        auto id    = getRun()->getGraph()->getTarget(edge);
        auto vattr = std::make_shared<KiwiVertexAttribute>(size);
        getRun()->setNestedVertexAttribute(edge, vattr);
        return vattr;
    }

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
    virtual std::string getRepr() const { return "KiwiConstraint"; }
};

class AlignConstraint : public KiwiConstraint {
  public:
    DECL_DESCRIBED_ENUM(AxisAlign, Center, Top, Bottom, Left, Right);

    struct [[refl]] Spec {
        [[refl]] Opt<double> fixPos = std::nullopt;
        [[refl]] AxisAlign   align  = AxisAlign::Center;
        [[refl]] double      offset = 0.0;
        DESC_FIELDS(Spec, (fixPos, align, offset));
    };

    hstd::UnorderedMap<VertexID, Spec> vertices;
    [[refl]] GraphDimension            dimension = GraphDimension::UNSET;
    DESC_FIELDS(AlignConstraint, (vertices, dimension));

    using KiwiConstraint::KiwiConstraint;

    VertexIDVec getAllVertices() const override { return vertices.keys(); }

    std::string getRepr() const override {
        return hstd::fmt("align {}", getAllVertices());
    }

    AlignConstraint* addAlignVertex(
        VertexID const&   id,
        AxisAlign         align  = AxisAlign::Center,
        double            offset = 0,
        hstd::Opt<double> fixPos = std::nullopt) {
        vertices.insert_or_assign(
            id,
            Spec{
                .fixPos = fixPos,
                .align  = align,
                .offset = offset,
            });
        return this;
    }

    AlignConstraint* useVerticalAxis() {
        dimension = GraphDimension::XDIM;
        return this;
    }

    AlignConstraint* useHorizontalAxis() {
        dimension = GraphDimension::YDIM;
        return this;
    }

    hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> getKiwi()
        const override;
};

class SeparateConstraint : public KiwiConstraint {
  public:
    [[refl]] AlignConstraint left;
    [[refl]] AlignConstraint right;
    [[refl]] double          separationDistance = 1.0;
    [[refl]] bool            isExactSeparation  = false;
    [[refl]] GraphDimension  dimension          = GraphDimension::UNSET;
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

    SeparateConstraint* separateHorizontally() {
        dimension = GraphDimension::XDIM;
        left.useVerticalAxis();
        right.useVerticalAxis();
        return this;
    }

    SeparateConstraint* separateVertically() {
        dimension = GraphDimension::YDIM;
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
        VertexID const& id,
        AlignConstraint::AxisAlign
                          align  = AlignConstraint::AxisAlign::Center,
        double            offset = 0,
        hstd::Opt<double> fixPos = std::nullopt) {
        left.addAlignVertex(id, align, offset, fixPos);
        return this;
    }

    SeparateConstraint* addLeftVertex(VertexIDVec const& id) {
        for (auto const& i : id) { addLeftVertex(i); }
        return this;
    }

    SeparateConstraint* addRightVertex(VertexIDVec const& id) {
        for (auto const& i : id) { addRightVertex(i); }
        return this;
    }

    SeparateConstraint* addRightVertex(
        VertexID const& id,
        AlignConstraint::AxisAlign
                          align  = AlignConstraint::AxisAlign::Center,
        double            offset = 0,
        hstd::Opt<double> fixPos = std::nullopt) {
        right.addAlignVertex(id, align, offset, fixPos);
        return this;
    }

    hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> getKiwi()
        const override;
};

class MultiSeparateConstraint : public KiwiConstraint {
  public:
    [[refl]] hstd::Vec<AlignConstraint> lines;
    [[refl]] GraphDimension             dimension = GraphDimension::XDIM;
    [[refl]] double                     separationDistance = 0.0;
    [[refl]] bool                       isExactSeparation  = false;
    DESC_FIELDS(
        MultiSeparateConstraint,
        (lines, dimension, separationDistance, isExactSeparation));

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

    MultiSeparateConstraint* setIsExactSeparation(bool exact) {
        this->isExactSeparation = exact;
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

    MultiSeparateConstraint* addAlignVertex(
        VertexID const& id,
        int             lane,
        AlignConstraint::AxisAlign
                          align  = AlignConstraint::AxisAlign::Center,
        double            offset = 0,
        hstd::Opt<double> fixPos = std::nullopt) {
        LOGIC_ASSERTION_CHECK_FMT(
            lines.has(lane),
            "Cannot insert vertext to lane {}, call `addLane()` to match "
            "the lane count",
            lane);
        lines.at(lane).addAlignVertex(id, align, offset, fixPos);
        return this;
    }

    MultiSeparateConstraint* addFullLane(VertexIDVec const& vertices) {
        addLane();
        for (auto const& vert : vertices) {
            lines.back().addAlignVertex(vert);
        }
        return this;
    }

    MultiSeparateConstraint* separateHorizontally() {
        dimension = GraphDimension::XDIM;
        for (auto& lane : lines) { lane.useVerticalAxis(); }
        return this;
    }

    MultiSeparateConstraint* separateVertically() {
        dimension = GraphDimension::YDIM;
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
