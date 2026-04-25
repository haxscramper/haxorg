#pragma once

#include <hstd/ext/graph/graph_base.hpp>
#include <hstd/ext/graph/adaptagrams_common.hpp>
#include <libdialect/hola.h>
#include <hstd/ext/bimap_wrap.hpp>
#include <hstd/stdlib/algorithms.hpp>

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
        UnorderedMap<layout::GroupID, hstd::SPtr<TDerivedGroup>>;

    hstd::SPtr<layout::LayoutRun> run;
    VertexAttrMap                 nodeAttributes;
    EdgeAttrMap                   edgeAttributes;
    GroupMap                      groups;
};

template <
    typename TDerivedGroup,
    typename TVertexAttribute,
    typename TEdgeAttribute>
struct GroupLocalCtxBase {
    hstd::Str                    name;
    hstd::UnorderedSet<VertexID> directVertices;
    hstd::UnorderedSet<EdgeID>   directEdges;
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

    SharedCtx::VertexAttrMap& nodeAttributes() {
        return get_shared_ctx()->nodeAttributes;
    }

    SharedCtx::EdgeAttrMap& edgeAttributes() {
        return get_shared_ctx()->edgeAttributes;
    }

    SharedCtx::GroupMap& groups() { return get_shared_ctx()->groups; }

    std::string getStableId() const {
        return hstd::fmt("cola-group-{}", get_local_ctx().name);
    }

    hstd::Vec<VertexID> getVertices() const {
        return hstd::Vec<VertexID>{
            get_local_ctx().directVertices.begin(),
            get_local_ctx().directVertices.end()};
    }

    hstd::Vec<EdgeID> getEdges() const {
        return hstd::Vec<EdgeID>{
            get_local_ctx().directEdges.begin(),
            get_local_ctx().directEdges.end()};
    }

    hstd::SPtr<TVertexAttribute> addVertex(
        VertexID const&                                   id,
        hstd::SPtr<layout::IVertexVisualAttribute> const& attr) {
        LOGIC_ASSERTION_CHECK_FMT(
            !nodeAttributes().contains(id),
            "Canot add vertex ID {} to the graph group {}, it is already "
            "added to {} group",
            id,
            getStableId(),
            get_local_ctx().directVertices.contains(id) ? "this"
                                                        : "other");

        auto vatr = std::dynamic_pointer_cast<TVertexAttribute>(attr);
        LOGIC_ASSERTION_CHECK_FMT(
            vatr != nullptr,
            "Graph groups expects attributes of type {}, but "
            "attr has dynamic type of {}",
            hstd::value_metadata<TVertexAttribute>::typeName(),
            typeid(attr.get()).name());

        hstd::logic_assertion_check_not_nil(get_run());
        auto vertex = get_run()->getVertex(id);
        hstd::logic_assertion_check_not_nil(vertex);

        const_cast<IVertex*>(vertex)->addAttribute(attr);
        nodeAttributes().insert_or_assign(id, vatr);
        get_local_ctx().directVertices.insert(id);
        return vatr;
    }

    layout::GroupID addNewNativeSubgroup(
        hstd::SPtr<TDerivedGroup> const& subgroup) {
        auto result = get_run()->addGroup(subgroup);

        groups().insert_or_assign(
            result,
            std::dynamic_pointer_cast<TDerivedGroup>(
                get_run()->getGroup(result)));

        _this()->subGroups.insert(result);

        return result;
    }

    hstd::SPtr<TEdgeAttribute> addEdge(
        EdgeID const&                                   id,
        hstd::SPtr<layout::IEdgeVisualAttribute> const& attr) {

        LOGIC_ASSERTION_CHECK_FMT(
            !edgeAttributes().contains(id),
            "Canot add edge ID {} to the graph group '{}', it is already "
            "added to {} group",
            id,
            getStableId(),
            get_local_ctx().directEdges.contains(id) ? "this" : "other");

        auto vatr = std::dynamic_pointer_cast<TEdgeAttribute>(attr);

        LOGIC_ASSERTION_CHECK_FMT(
            vatr != nullptr,
            "Graph groups expects attributes of type {}, but "
            "attr has dynamic type of {}",
            hstd::value_metadata<TEdgeAttribute>::typeName(),
            typeid(attr.get()).name());

        auto e = const_cast<IEdge*>(_this()->shared->run->getEdge(id));

        LOGIC_ASSERTION_CHECK_FMT(
            nodeAttributes().contains(e->getSource()),
            "{}",
            e->getSource());

        LOGIC_ASSERTION_CHECK_FMT(
            nodeAttributes().contains(e->getTarget()),
            "{}",
            e->getTarget());

        _this()->shared->run->message(
            hstd::fmt(
                "add edge {} ({} -> {}) to group '{}'",
                id,
                e->getSource(),
                e->getTarget(),
                getStableId()));

        e->addAttribute(attr);

        edgeAttributes().insert_or_assign(id, vatr);
        _this()->local.directEdges.insert(id);
        return vatr;
    }

    void addExistingSubgroup(layout::GroupID const& id) {
        LOGIC_ASSERTION_CHECK_FMT(
            !_this()->subGroups.contains(id),
            "Group already contains subgroup with ID {}",
            id);

        _this()->subGroups.insert(id);
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
            getVertexIdx(run->graph->getEdge(id)->getSource()),
            getVertexIdx(run->graph->getEdge(id)->getTarget()),
        };
    }

    int addVertex(VertexID const& id, geometry::Rect const& rect) {
        int result = rectStore.size();
        rectStore.push_back(
            std::make_shared<vpsc::Rectangle>(
                rect.min_x(), rect.max_x(), rect.min_y(), rect.max_y()));
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

class ColaGroup
    : public layout::IGroup
    , public GroupBase<ColaGroup, ColaVertexAttribute, ColaEdgeAttribute> {
  public:
    using API = APIBundle<
        ColaGroup,
        ColaVertexAttribute,
        ColaEdgeAttribute>;

    struct SharedCtx
        : public API::SharedCtxBase
        , public ColaRectTracker {};

    struct LocalCtx : public API::LocalCtxBase {};

    ColaGroup(hstd::SPtr<SharedCtx> const& ctx, hstd::Str const& name)
        : layout::IGroup{ctx->run}, shared{ctx}, local{{.name = name}} {}

    hstd::SPtr<SharedCtx> shared;
    LocalCtx              local;

    void addExistingSubgroup(layout::GroupID const& id) override {
        API::Group::addExistingSubgroup(id);
    }

    void addVertex(
        VertexID const&                                   id,
        hstd::SPtr<layout::IVertexVisualAttribute> const& attr) override {
        auto vatr = API::Group::addVertex(id, attr);
        shared->addVertex(id, vatr->rect);
    }

    hstd::SPtr<ColaVertexAttribute> addVertex(
        VertexID const&       id,
        geometry::Rect const& size) {
        auto vattr = std::make_shared<ColaVertexAttribute>(size);
        addVertex(id, vattr);
        return vattr;
    }

    hstd::SPtr<ColaVertexAttribute> addVertex(
        VertexID const&       id,
        geometry::Size const& size) {
        return addVertex(
            id, geometry::Rect(0, 0, size.width(), size.height()));
    }

    hstd::SPtr<ColaEdgeAttribute> addEdge(EdgeID const& id) {
        auto res = std::make_shared<ColaEdgeAttribute>();
        addEdge(id, res);
        return res;
    }

    std::string getStableId() const override {
        return API::Group::getStableId();
    }

    hstd::Vec<VertexID> getVertices() const override {
        return API::Group::getVertices();
    }

    hstd::Vec<EdgeID> getEdges() const override {
        return API::Group::getEdges();
    }

    void addEdge(
        EdgeID const&                                   id,
        hstd::SPtr<layout::IEdgeVisualAttribute> const& attr) override {
        API::Group::addEdge(id, attr);
    }

    layout::GroupID addNewNativeSubgroup() override {
        return API::Group::addNewNativeSubgroup(
            std::make_shared<ColaGroup>(
                shared, hstd::fmt("cola_{}", run->groups.getNextId())));
    }

    static layout::GroupID newRootGraph(hstd::SPtr<layout::LayoutRun> run);
};

static_assert(
    GroupConcept<ColaGroup, ColaVertexAttribute, ColaEdgeAttribute>,
    "Cola group and related types");

class ColaVertexLayoutAttribute : public layout::IVertexLayoutAttribute {
  public:
    geometry::Rect rect;
    ColaVertexLayoutAttribute(geometry::Rect rect) : rect{rect} {}

    Rect getBBox() const override { return rect; }
};

class ColaEdgeLayoutAttribute : public layout::IEdgeLayoutAttribute {
  public:
    geometry::Path path;
    ColaEdgeLayoutAttribute(geometry::Path const& path) : path{path} {}
    Path getPath() const override { return path; }
};

class ColaGroupLayoutAttribute : public layout::IGroupLayoutAttribute {
  public:
    visual::VisGroup getVisual(layout::GroupID const& id) const override;

    Rect                  rect;
    hstd::SPtr<ColaGroup> group;

    ColaGroupLayoutAttribute(Rect rect, hstd::SPtr<ColaGroup> group)
        : rect{rect}, group{group} {}

    virtual Rect getPointsBBox() const override { return rect; }
};


class ColaConstraint : public layout::IConstraint {
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


class AlignConstraint : public ColaConstraint {
  public:
    using ColaConstraint::ColaConstraint;
    struct [[refl]] Spec {
        [[refl]] Opt<double> fixPos = std::nullopt; ///< ??? wtf
        [[refl]] double      offset = 0.0; ///< Offset from the axis
        DESC_FIELDS(Spec, (fixPos, offset));
    };

    hstd::UnorderedMap<VertexID, Spec> vertices;

    std::string getRepr() const override {
        return hstd::fmt("align [{}]", getAllVertices());
    }


    [[refl]] GraphDimension dimension; ///< Which axist to align on
    DESC_FIELDS(AlignConstraint, (vertices, dimension));


    hstd::Vec<VertexID> getAllVertices() const override {
        return vertices.keys();
    }

    AlignConstraint* addAlignVertex(
        VertexID const&   id,
        double            offset = 0,
        hstd::Opt<double> fixPos = std::nullopt) {
        vertices.insert_or_assign(
            id, Spec{.fixPos = fixPos, .offset = offset});
        return this;
    }

    AlignConstraint* useX() {
        dimension = GraphDimension::XDIM;
        return this;
    }

    AlignConstraint* useY() {
        dimension = GraphDimension::YDIM;
        return this;
    }


    /// \note Align constraint returns vector with single elements, so the
    /// `getCola().at(0)` usage in the separate and multi-separate
    /// constraints are safe and not dropping anything.
    hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> getCola()
        const override;
};

class SeparateConstraint : public ColaConstraint {
  public:
    hstd::Vec<VertexID> getAllVertices() const override {
        return left.getAllVertices() + right.getAllVertices();
    }

    using ColaConstraint::ColaConstraint;
    [[refl]] AlignConstraint left;
    [[refl]] AlignConstraint right;
    [[refl]] double          separationDistance = 1.0;
    [[refl]] bool            isExactSeparation  = false;
    [[refl]] GraphDimension  dimension; ///< Which axis to partition
                                        ///< nodes
    DESC_FIELDS(
        SeparateConstraint,
        (left, right, separationDistance, isExactSeparation, dimension));

    std::string getRepr() const override {
        return hstd::fmt(
            "separate {} <> {}", left.getRepr(), right.getRepr());
    }

    hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> getCola()
        const override;

    SeparateConstraint* separateVertically() {
        dimension = GraphDimension::XDIM;
        left.useX();
        right.useX();
        return this;
    }

    SeparateConstraint* separateHorizontally() {
        dimension = GraphDimension::YDIM;
        left.useY();
        right.useY();
        return this;
    }


    SeparateConstraint* setSeparationDistance(double distance) {
        this->separationDistance = distance;
        return this;
    }

    SeparateConstraint* setIsExactSeparation(double distance) {
        this->isExactSeparation = distance;
        return this;
    }

    SeparateConstraint* addLeftVertex(
        VertexID const&   id,
        double            offset = 0,
        hstd::Opt<double> fixPos = std::nullopt) {
        left.addAlignVertex(id, offset, fixPos);
        return this;
    }

    SeparateConstraint* addRightVertex(
        VertexID const&   id,
        double            offset = 0,
        hstd::Opt<double> fixPos = std::nullopt) {
        right.addAlignVertex(id, offset, fixPos);
        return this;
    }

    SeparateConstraint(hstd::SPtr<ColaGroup> const& group)
        : ColaConstraint{group}, left{group}, right{group} {}
};

class MultiSeparateConstraint : public ColaConstraint {
  public:
    using ColaConstraint::ColaConstraint;
    [[refl]] hstd::Vec<AlignConstraint>      lines;
    [[refl]] hstd::Vec<hstd::Pair<int, int>> alignPairs;
    [[refl]] GraphDimension                  dimension;
    [[refl]] double                          separationDistance;
    [[refl]] bool                            isExactSeparation;

    DESC_FIELDS(
        MultiSeparateConstraint,
        (lines,
         alignPairs,
         dimension,
         separationDistance,
         isExactSeparation));

    hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> getCola()
        const override;
};

class FixedRelativeConstraint : public ColaConstraint {
  public:
    using ColaConstraint::ColaConstraint;
    [[refl]] bool fixedPosition = false;
    DESC_FIELDS(FixedRelativeConstraint, (fixedPosition));

    hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> getCola()
        const override;
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
    layout::IGroup const*                group;
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
    Result runSingleLayout(layout::GroupID const& group) override;

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
