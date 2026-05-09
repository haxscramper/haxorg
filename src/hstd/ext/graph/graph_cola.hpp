#pragma once

#include <hstd/ext/graph/graph_base.hpp>
#include <hstd/ext/graph/adaptagrams_common.hpp>
#include <libdialect/hola.h>
#include <hstd/ext/bimap_wrap.hpp>
#include <hstd/stdlib/algorithms.hpp>
#include <hstd/ext/logger.hpp>

namespace hstd::ext::graph {

template <
    typename TDerivedGroup,
    typename TVertexAttribute,
    typename TEdgeAttribute>
struct GroupSharedCtxBase {
    using VertexAttrMap = hstd::
        UnorderedMap<VertexID, hstd::SPtr<TVertexAttribute>>;
    using EdgeAttrMap = hstd::
        UnorderedMap<EdgeID, hstd::SPtr<TEdgeAttribute>>;
    using GroupMap = hstd::
        UnorderedMap<VertexID, hstd::SPtr<TDerivedGroup>>;

    hstd::SPtr<layout::LayoutRun> run;
};

template <
    typename TDerivedGroup,
    typename TVertexAttribute,
    typename TEdgeAttribute>
struct GroupLocalCtxBase {
    hstd::Str name;
};

template <
    typename TDerivedGroup,
    typename TVertexAttribute,
    typename TEdgeAttribute>
concept GroupConcept = requires(
    std::shared_ptr<typename TDerivedGroup::SharedCtx> const& sharedCtx,
    hstd::Str const&                                          str) {
    typename TDerivedGroup::SharedCtx;
    typename TDerivedGroup::LocalCtx;
    &TDerivedGroup::newRootGraph;
    &TDerivedGroup::shared;
    &TDerivedGroup::local;
    TDerivedGroup(sharedCtx, str);
};

template <
    typename TDerivedGroup,
    typename TVertexAttribute,
    typename TEdgeAttribute>
struct GroupBase : public CRTP_this_method<TDerivedGroup> {
    using CRTP_this_method<TDerivedGroup>::_this;

    using SharedCtx = GroupSharedCtxBase<
        TDerivedGroup,
        TVertexAttribute,
        TEdgeAttribute>;

    auto&       get_shared_ctx() { return _this()->shared; }
    auto const& get_shared_ctx() const { return _this()->shared; }
    auto&       get_local_ctx() { return _this()->local; }
    auto const& get_local_ctx() const { return _this()->local; }
    auto&       get_run() { return _this()->shared->run; }
    auto const& get_run() const { return _this()->shared->run; }

    std::string getStableId() const {
        return hstd::fmt(
            "{}-{}",
            hstd::value_metadata<TDerivedGroup>::typeName(),
            get_local_ctx().name);
    }
};

template <
    typename TDerivedGroup,
    typename TVertexAttribute,
    typename TEdgeAttribute>
struct APIBundle {
    using Group = GroupBase<
        TDerivedGroup,
        TVertexAttribute,
        TEdgeAttribute>;

    using SharedCtxBase = GroupSharedCtxBase<
        TDerivedGroup,
        TVertexAttribute,
        TEdgeAttribute>;

    using LocalCtxBase = GroupLocalCtxBase<
        TDerivedGroup,
        TVertexAttribute,
        TEdgeAttribute>;
};

}; // namespace hstd::ext::graph

/// \brief Adapter for the adaptagrams COLA constraint-based layout.
namespace hstd::ext::graph::cst {

enum class [[refl]] GraphDimension
{
    XDIM  = 0,
    YDIM  = 1,
    UNSET = 2,
};

BOOST_DESCRIBE_ENUM(GraphDimension, XDIM, YDIM, UNSET);


class ColaVertexAttribute : public layout::IVertexVisualAttribute {
  public:
    geometry::Rect rect;
    ColaVertexAttribute(geometry::Rect const& rect) : rect{rect} {}
};

class ColaEdgeAttribute : public layout::IEdgeVisualAttribute {};

class ColaRectTracker {
  public:
    hstd::ext::Unordered1to1Bimap<VertexID, int> rectMap;
    hstd::Vec<hstd::SPtr<vpsc::Rectangle>>       rectStore;
    DESC_FIELDS(ColaRectTracker, (rectMap, rectStore));

    int getVertexIdx(VertexID const& id) const {
        return rectMap.at_right(id);
    }

    std::pair<int, int> getEdgeIdx(
        EdgeID const&                 id,
        hstd::SPtr<layout::LayoutRun> run) const {
        return {
            getVertexIdx(run->graph->getSource(id)),
            getVertexIdx(run->graph->getTarget(id)),
        };
    }

    int addVertex(VertexID const& id, geometry::Rect const& rect) {
        int result = rectStore.size();
        rectStore.push_back(
            std::make_shared<vpsc::Rectangle>(
                rect.min_x(), rect.max_x(), rect.min_y(), rect.max_y()));

        HSLOG_DEBUG("Adding vertex {} rect {}", id, rect);
        rectMap.add_unique(id, result);
        return result;
    }

    bool hasRect(VertexID const& id) const {
        return rectMap.contains_left(id);
    }

    hstd::SPtr<vpsc::Rectangle> getRect(VertexID const& id) const {
        LOGIC_ASSERTION_CHECK_FMT(
            rectMap.contains_left(id), "rect map is missing ID {}", id);

        return rectStore.at(rectMap.at_right(id));
    }

    VertexIDVec getAllVertexIDsSorted() const {
        VertexIDVec res;
        for (auto const& [rect, _] : enumerate(rectStore)) {
            res.push_back(rectMap.at_left(rect));
        }
        return res;
    }


    /// \brief Get all rectangles for the problem in a consistent
    /// sorting order.
    ///
    /// \warning This method will sort the vertices based on their IDs.
    /// This function should onyl be called after all the vertex
    /// elements are inserted **in the layout problem** the list of
    /// vertex rectangles is shared globally across all cola groups on
    /// the same layer.
    std::vector<vpsc::Rectangle*> getAllRectanglesSorted() const {
        std::vector<vpsc::Rectangle*> res;
        for (auto const& rect : rectStore) { res.push_back(rect.get()); }
        return res;
    }

    /// \brief Get all shape IDs in the problem. Sorting order matches
    /// \ref getAllRectanglesSorted
    std::vector<unsigned> getAllShapeIdsSorted() const {
        std::vector<unsigned> res;
        for (int i = 0; i < rectStore.size(); ++i) { res.push_back(i); }
        return res;
    }
};

class FixedRelativeConstraint;
class LockPositionConstraint;
class MultiSeparateConstraint;
class SeparateConstraint;
class AlignConstraint;

class ColaGroup
    : public layout::IGroupVisualAttribute
    , public GroupBase<ColaGroup, ColaVertexAttribute, ColaEdgeAttribute>
    , public std::enable_shared_from_this<ColaGroup> {
  public:
    hstd::Opt<geometry::Padding> outerPadding;

    void setOuterPadding(geometry::Padding const& pad) override {
        outerPadding = pad;
    }

    hstd::Opt<geometry::Padding> getOuterPadding() const override {
        return outerPadding;
    }

    using Base = layout::IGroupVisualAttribute;
    using API  = APIBundle<
        ColaGroup,
        ColaVertexAttribute,
        ColaEdgeAttribute>;

    struct SharedCtx
        : public API::SharedCtxBase
        , public ColaRectTracker {};

    struct LocalCtx : public API::LocalCtxBase {};

    ColaGroup(hstd::SPtr<SharedCtx> const& ctx, hstd::Str const& name)
        : layout::IGroupVisualAttribute{ctx->run}
        , shared{ctx}
        , local{{.name = name}} {}

    hstd::SPtr<SharedCtx> shared;
    LocalCtx              local;

    hstd::SPtr<ColaVertexAttribute> addVertex(
        VertexID const&       parent,
        VertexID const&       id,
        geometry::Rect const& size) {
        auto vattr  = std::make_shared<ColaVertexAttribute>(size);
        std::ignore = get_run()->addNestedVertex(parent, id, vattr);
        shared->addVertex(id, size);
        return vattr;
    }

    hstd::SPtr<ColaVertexAttribute> addVertex(
        VertexID const&       parent,
        VertexID const&       id,
        geometry::Size const& size) {
        return addVertex(
            parent, id, geometry::Rect(0, 0, size.width(), size.height()));
    }


    hstd::SPtr<ColaEdgeAttribute> addEdge(EdgeID const& id) {
        auto res = std::make_shared<ColaEdgeAttribute>();
        get_run()->addEdge(id, res);
        return res;
    }

    std::string getStableId() const override {
        return API::Group::getStableId();
    }

    hstd::SPtr<ColaGroup> addNewNativeSubgroup(
        VertexID const& parent,
        VertexID const& id) {
        auto res = std::make_shared<ColaGroup>(
            shared, hstd::fmt("cola_{}", id));
        std::ignore = run->addNestedGroup(parent, id, res);
        return res;
    }

    static hstd::SPtr<cst::ColaGroup> newRootGraph(
        hstd::SPtr<layout::LayoutRun> run,
        const Str&                    name = "root");
};

static_assert(
    GroupConcept<ColaGroup, ColaVertexAttribute, ColaEdgeAttribute>,
    "Cola group and related types");

class ColaVertexLayoutAttribute : public layout::IVertexLayoutAttribute {
  public:
    geometry::Rect rect;
    std::string    text;
    ColaVertexLayoutAttribute(geometry::Rect rect, std::string text = "")
        : rect{rect}, text{text} {}

    Rect getBBox() const override { return rect; }

    visual::VisGroup getVisual(VertexID const& selfId) const override {
        visual::VisGroup res;
        res.elements.push_back(
            visual::VisElement{visual::VisElement::RectShape{getBBox()}});
        res.elements.push_back(
            visual::VisElement::FromText(
                text.empty() ? hstd::fmt("{}", selfId) : text,
                getBBox().upper_left()));
        res.custom.setAttr(
            "inkscape:label", hstd::fmt("COLA VERTEX:{}", selfId));
        return res;
    }
};

class ColaEdgeLayoutAttribute : public layout::IEdgeLayoutAttribute {
  public:
    geometry::Path path;
    ColaEdgeLayoutAttribute(geometry::Path const& path) : path{path} {}
    Path getPath() const override { return path; }
};

class ColaGroupLayoutAttribute : public layout::IGroupLayoutAttribute {
  public:
    visual::VisGroup getVisual(VertexID const& id) const override;

    Rect                  rect;
    hstd::SPtr<ColaGroup> group;

    ColaGroupLayoutAttribute(Rect rect, hstd::SPtr<ColaGroup> group)
        : rect{rect}, group{group} {}

    virtual Rect getBBox() const override { return rect; }
    void setBBox(geometry::Rect const& _rect) override { rect = _rect; }
};


class ColaConstraint : public layout::IConstraint {
  protected:
    hstd::SPtr<ColaGroup> group;

  public:
    using ConstraintPtr = hstd::SPtr<::cola::CompoundConstraint>;
    ColaConstraint(hstd::SPtr<ColaGroup> const& group) : group{group} {}

    virtual hstd::Vec<ConstraintPtr> getCola() const = 0;

    virtual std::string getRepr() const;

    /// \brief Get rectangles associated with this specific constraint
    std::vector<vpsc::Rectangle*> getRectangles() const;
    /// \brief Get shape IDs associated with this specific constraint
    std::vector<unsigned int> getRectangleIndices() const;

    /// \copydoc ColaGroup::SharedCtx::getAllRectanglesSorted
    std::vector<vpsc::Rectangle*> getAllRectanglesSorted() const {
        return group->shared->getAllRectanglesSorted();
    }

    /// \copydoc ColaGroup::SharedCtx::getAllShapeIdsSorted
    std::vector<unsigned> getAllShapeIdsSorted() const {
        return group->shared->getAllShapeIdsSorted();
    }

    unsigned getShapeId(VertexID const& id) const {
        return group->shared->getVertexIdx(id);
    }
};


/// \brief Place the shapes along the horizontal or vertical line with
/// some offset.
class AlignConstraint : public ColaConstraint {
  public:
    using ColaConstraint::ColaConstraint;

    /// \brief How to align each individual shape to the line. Center will
    /// put the shape centerpoint on the line, others will stick the shape
    /// edges. Top/bottom is compatible with the horizontal align,
    /// left/right is with the vertical, and the center is compatible with
    /// all.
    DECL_DESCRIBED_ENUM(AxisAlign, Center, Top, Bottom, Left, Right);

    /// \brief How each individual shape is going to be added to the list
    struct [[refl]] Spec {
        /// \brief Set the expected X/Y-value of the alignment line (not a
        /// hard requirement, but the line will tend to gravitate towards
        /// it).
        [[refl]] Opt<double> fixPos = std::nullopt;
        /// \brief Which anchor to use for alignment of the shapes
        [[refl]] AxisAlign align = AxisAlign::Center;
        /// Offset from the axis on the line orthogonal to the axis.
        [[refl]] double offset = 0.0;
        DESC_FIELDS(Spec, (fixPos, align, offset));
    };

    /// \brief List of vertices to place in the constraint
    hstd::UnorderedMap<VertexID, Spec> vertices;
    /// Which axist to align on
    [[refl]] GraphDimension dimension;
    DESC_FIELDS(AlignConstraint, (vertices, dimension));

    std::string getRepr() const override {
        return hstd::fmt(
            "align {} rects {}", getAllVertices(), getRectangleIndices());
    }

    VertexIDVec getAllVertices() const override { return vertices.keys(); }

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

    /// \brief Align all shapes vertically
    AlignConstraint* useVerticalAxis() {
        dimension = GraphDimension::XDIM;
        return this;
    }

    /// \brief Align all shapes horizontally
    AlignConstraint* useHorizontalAxis() {
        dimension = GraphDimension::YDIM;
        return this;
    }


    /// \note Align constraint returns vector with single elements, so the
    /// `getCola().at(0)` usage in the separate and multi-separate
    /// constraints are safe and not dropping anything.
    hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> getCola()
        const override;
};

/// \brief Separate constraint creates to lanes of shapes (with one or more
/// shape per lane) and then arranges so the lanes would have a fixed
/// distance between them. Each lane is managed by the align constraint, so
/// it is possible to offset the individual shapes relative to the lane.
class SeparateConstraint : public ColaConstraint {
  public:
    VertexIDVec getAllVertices() const override {
        return left.getAllVertices() + right.getAllVertices();
    }

    using ColaConstraint::ColaConstraint;
    /// \brief The first lane to align
    [[refl]] AlignConstraint left;
    /// \brief Second lane to align
    [[refl]] AlignConstraint right;
    [[refl]] double          separationDistance = 1.0;
    [[refl]] bool            isExactSeparation  = false;
    /// Which axis to partition nodes
    [[refl]] GraphDimension dimension;
    DESC_FIELDS(
        SeparateConstraint,
        (left, right, separationDistance, isExactSeparation, dimension));

    std::string getRepr() const override {
        return hstd::fmt(
            "separate {} <> {}", left.getRepr(), right.getRepr());
    }

    hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> getCola()
        const override;

    /// \brief The lanes are placed vertically, with the separation
    /// distance configuring the X-offset between the lanes.
    SeparateConstraint* separateHorizontally() {
        dimension = GraphDimension::XDIM;
        left.useVerticalAxis();
        right.useVerticalAxis();
        return this;
    }

    /// \brief The lanes are placed horizontally, with the separation
    /// distance configuring the Y-offset between the lanes.
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

    /// \brief Add vertex to the first alignment lane.
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

    /// \brief Add vertex to the second alignment lane.
    SeparateConstraint* addRightVertex(
        VertexID const& id,
        AlignConstraint::AxisAlign
                          align  = AlignConstraint::AxisAlign::Center,
        double            offset = 0,
        hstd::Opt<double> fixPos = std::nullopt) {
        right.addAlignVertex(id, align, offset, fixPos);
        return this;
    }

    SeparateConstraint(hstd::SPtr<ColaGroup> const& group)
        : ColaConstraint{group}, left{group}, right{group} {}
};

/// \brief Create multiple lanes of aligned widgets, with each line offset
/// by a fixed margin.
class MultiSeparateConstraint : public ColaConstraint {
  public:
    VertexIDVec getAllVertices() const override {
        VertexIDVec res;
        for (auto const& align : lines) {
            res.append(align.getAllVertices());
        }
        return res;
    }

    using ColaConstraint::ColaConstraint;
    [[refl]] hstd::Vec<AlignConstraint> lines;
    [[refl]] GraphDimension             dimension = GraphDimension::XDIM;
    [[refl]] double                     separationDistance;
    [[refl]] bool                       isExactSeparation;


    MultiSeparateConstraint* setSeparationDistance(double distance) {
        this->separationDistance = distance;
        return this;
    }

    MultiSeparateConstraint* setIsExactSeparation(double distance) {
        this->isExactSeparation = distance;
        return this;
    }

    /// \brief Add single lane
    MultiSeparateConstraint* addLane() {
        auto align      = AlignConstraint{group};
        align.dimension = dimension;
        lines.push_back(align);
        return this;
    }

    int getLaneCount() const { return lines.size(); }

    /// \brief Add multiple lanes
    MultiSeparateConstraint* addMultiLane(int count) {
        for (int i = 0; i < count; ++i) { addLane(); }
        return this;
    }

    /// \brief Add a vertex to the *existing* lane, with specified offset
    /// parameters.
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

    /// \brief Add a fully new lane with the fixed set of vertices.
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


    DESC_FIELDS(
        MultiSeparateConstraint,
        (lines, dimension, separationDistance, isExactSeparation));

    hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> getCola()
        const override;
};

class FixedRelativeConstraint : public ColaConstraint {
  public:
    using ColaConstraint::ColaConstraint;
    [[refl]] bool fixedPosition = false;
    [[refl]] hstd::UnorderedMap<VertexID, geometry::Point> shapes;
    DESC_FIELDS(FixedRelativeConstraint, (fixedPosition, shapes));

    FixedRelativeConstraint(hstd::SPtr<ColaGroup> const& group)
        : ColaConstraint{group} {}

    hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> getCola()
        const override;

    FixedRelativeConstraint* addVertex(
        VertexID const&        id,
        geometry::Point const& p) {
        shapes.insert_or_assign(id, p);
        return this;
    }

    VertexIDVec getAllVertices() const override {
        return hstd::sorted(shapes.keys());
    }
};

class LockPositionConstraint : public ColaConstraint {
  public:
    hstd::Vec<ConstraintPtr> getCola() const override {
        // Lock constraints are arranged using pre-iteration lock instead
        // of the compound constraints.
        return {};
    }

    cola::Lock getLock() const {
        return cola::Lock(
            group->shared->getVertexIdx(vertex),
            position.x(),
            position.y());
    }

    VertexIDVec getAllVertices() const override { return {vertex}; }

    using ColaConstraint::ColaConstraint;
    [[refl]] geometry::Point position;
    VertexID                 vertex = VertexID::Nil();

    LockPositionConstraint* setVertex(VertexID const& id) {
        vertex = id;
        return this;
    }

    LockPositionConstraint* setPosition(geometry::Point const& id) {
        position = id;
        return this;
    }
};

class PageBoundaryConstraint : public ColaConstraint {
  public:
    using ColaConstraint::ColaConstraint;
    [[refl]] geometry::Rect rect;
    [[refl]] double         weight = 100.0;
    DESC_FIELDS(PageBoundaryConstraint, (rect, weight));

    hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> getCola()
        const override;
};

class AvoidPort : public IPort {
  public:
    std::size_t getHash() const override { return 0; }

    bool isEqual(IGraphObjectBase const* other) const override {
        return true;
    }

    std::string getRepr() const override { return ""; }

    hstd::Vec<hstd::SPtr<IAttribute>> attrs;

    hstd::Vec<hstd::SPtr<IAttribute>> getAttributes() const override {
        return attrs;
    }

    void addAttribute(hstd::SPtr<IAttribute> const& attr) override {
        attrs.push_back(attr);
    }

    void setAttributes(
        hstd::Vec<hstd::SPtr<IAttribute>> const& attrs) override {
        this->attrs = attrs;
    }
};

class AvoidPortVisualAttribute : public layout::IPortVisualAttribute {
  public:
    DECL_DESCRIBED_ENUM(VisibilityDirection, Left, Right, Top, Bottom);
    VisibilityDirection visibility;
    hstd::Opt<double>   edgeOffset;
};

class AvoidPortLayoutAttribute : public layout::IPortLayoutAttribute {
  public:
    Rect getBBox() const override {
        return Rect::FromCenterWH(Point(xOffset, yOffset), width, height);
    }

    visual::VisGroup getVisual(PortID const& id) const override {
        visual::VisGroup res;
        res.elements.push_back(
            visual::VisElement{visual::VisElement::RectShape{getBBox()}});
        return res;
    }

    DECL_DESCRIBED_ENUM(Placement, Unspecified, Proportional, Absolute);
    using VisibilityDirection = AvoidPortVisualAttribute::
        VisibilityDirection;
    VisibilityDirection visibility;
    Placement           placement;
    double              xOffset;
    double              yOffset;
    double              width  = 1;
    double              height = 1;

    Avoid::ConnEnd             connection;
    Avoid::ShapeConnectionPin* pin;
};


class AvoidPortCollection : public IPortCollection {
    hstd::UnorderedIncrementalStore<PortID, AvoidPort> portStore;

  public:
    PortCollectionID getCategory() const override {
        return hstd::ext::graph::PortCollectionID(
            hstd::hash_bits<15>(typeid(this).hash_code()));
    }

    const IPort* getPort(PortID pid) const override {
        return &portStore.at(pid);
    }

    PortID addPort(VertexID vertex, EdgeID edge, bool is_start) {
        auto id = portStore.add(AvoidPort{});
        IPortCollection::addPort(vertex, edge, is_start, id);
        return id;
    }
};

class AvoidRouterAlgorithm {
  public:
    /// \brief put a fake buffer around each shape so the edges would not
    /// run perfectly flush against the nodes.
    hstd::Opt<int>                       shapeBufferDistance = 1;
    ColaRectTracker*                     rects;
    layout::IGroupVisualAttribute const* group;
    VertexID                             root_group = VertexID::Nil();
    hstd::SPtr<layout::LayoutRun>        run;
    layout::IPlacementAlgorithm::Result* intermediate_placement;

    hstd::UnorderedMap<VertexID, Avoid::ShapeRef*> shapes;
    hstd::UnorderedMap<EdgeID, Avoid::ConnRef*>    connections;
    hstd::SPtr<Avoid::Router>                      router;

    struct Result {
        hstd::SPtr<AvoidPortCollection> layoutPorts;
    };

    Result routeEdges();
};

class ColaLayoutAlgorithm : public layout::IPlacementAlgorithm {
  public:
    std::shared_ptr<AvoidRouterAlgorithm> router;
    double                                commonIdealEdgeLength = 60;
    hstd::UnorderedMap<EdgeID, double>    idealEdgeLength;
    Result runSingleLayout(VertexID const& group) override;

    ColaLayoutAlgorithm(
        hstd::SPtr<layout::LayoutRun>         run,
        std::shared_ptr<AvoidRouterAlgorithm> _router = nullptr)
        : layout::IPlacementAlgorithm{run} {
        if (_router == nullptr) {
            router = std::make_shared<AvoidRouterAlgorithm>();
        } else {
            router = _router;
        }
    }
};

} // namespace hstd::ext::graph::cst
