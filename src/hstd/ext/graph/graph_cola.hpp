#pragma once

#include <hstd/ext/graph/graph_base.hpp>
#include <hstd/ext/graph/adaptagrams_common.hpp>
#include <libdialect/hola.h>

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
struct GroupBase : public CRTP_this_method<TDerivedGroup> {
    using CRTP_this_method<TDerivedGroup>::_this;

    using SharedCtx = GroupSharedCtxBase<
        TDerivedGroup,
        TVertexAttribute,
        TEdgeAttribute>;

    SharedCtx::VertexAttrMap& nodeAttributes() {
        return _this()->shared->nodeAttributes;
    }

    SharedCtx::EdgeAttrMap& edgeAttributes() {
        return _this()->shared->edgeAttributes;
    }

    SharedCtx::GroupMap& groups() { return _this()->shared->groups; }

    std::string getStableId() const {
        return hstd::fmt("cola-group-{}", _this()->local.name);
    }

    hstd::Vec<VertexID> getVertices() const {
        return hstd::Vec<VertexID>{
            _this()->local.directVertices.begin(),
            _this()->local.directVertices.end()};
    }

    hstd::Vec<EdgeID> getEdges() const {
        return hstd::Vec<EdgeID>{
            _this()->local.directEdges.begin(),
            _this()->local.directEdges.end()};
    }

    hstd::SPtr<TVertexAttribute> addVertex(
        VertexID const&                                   id,
        hstd::SPtr<layout::IVertexVisualAttribute> const& attr) {
        LOGIC_ASSERTION_CHECK_FMT(
            !_this()->nodeAttributes().contains(id),
            "Canot add vertex ID {} to the graph group {}, it is already "
            "added to another group",
            id,
            getStableId());

        auto vatr = std::dynamic_pointer_cast<TVertexAttribute>(attr);
        LOGIC_ASSERTION_CHECK_FMT(
            vatr != nullptr,
            "Graph groups expects attributes derived from the {}, but "
            "attr has dynamic type of {}",
            hstd::value_metadata<TVertexAttribute>::typeName(),
            typeid(attr.get()).name());

        hstd::logic_assertion_check_not_nil(_this()->shared->run);
        auto vertex = _this()->shared->run->getVertex(id);
        hstd::logic_assertion_check_not_nil(vertex);

        const_cast<IVertex*>(vertex)->addAttribute(attr);
        nodeAttributes().insert_or_assign(id, vatr);
        _this()->local.directVertices.insert(id);
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
    geometry::Rect rect;
    ColaVertexAttribute(geometry::Rect const& rect) : rect{rect} {}
};

class ColaEdgeAttribute : public layout::IEdgeVisualAttribute {};

class ColaGroup
    : public layout::IGroup
    , public GroupBase<ColaGroup, ColaVertexAttribute, ColaEdgeAttribute> {
  public:
    using API = APIBundle<
        ColaGroup,
        ColaVertexAttribute,
        ColaEdgeAttribute>;

    struct SharedCtx : public API::SharedCtxBase {
        hstd::UnorderedMap<VertexID, int>      rectMap;
        hstd::Vec<hstd::SPtr<vpsc::Rectangle>> rectStore;
        vpsc::Rectangles                       rectangles;
        DESC_FIELDS(SharedCtx, (rectMap, rectStore));

        int addVertex(VertexID const& id, geometry::Rect const& rect) {
            int result = rectStore.size();
            rectStore.push_back(
                std::make_shared<vpsc::Rectangle>(
                    rect.min_x(),
                    rect.max_x(),
                    rect.min_y(),
                    rect.max_y()));
            rectangles.push_back(rectStore.at(result).get());
            return result;
        }

        bool hasRect(VertexID const& id) const {
            return rectMap.contains(id);
        }

        hstd::SPtr<vpsc::Rectangle> getRect(VertexID const& id) const {
            return rectStore.at(rectMap.at(id));
        }
    };


    struct LocalCtx : public API::LocalCtxBase {};

    ColaGroup(hstd::SPtr<SharedCtx> const& ctx, hstd::Str const& name)
        : layout::IGroup{ctx->run}, shared{ctx}, local{{.name = name}} {}

    hstd::SPtr<SharedCtx> shared;
    LocalCtx              local;

    void addExistingSubgroup(layout::GroupID const&) override;

    void addVertex(
        VertexID const&                                   id,
        hstd::SPtr<layout::IVertexVisualAttribute> const& attr) override {
        auto vatr = API::Group::addVertex(id, attr);
    }
};


class ColaConstraint : public layout::IConstraint {
    hstd::Vec<VertexID>   vertices;
    hstd::SPtr<ColaGroup> group;

  public:
    ColaConstraint(hstd::SPtr<ColaGroup> const& group) : group{group} {}

    virtual hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> getCola()
        const;
    virtual std::string getRepr() const {
        std::string res;
        for (auto const& c : getCola()) {
            res += "\n";
            res += c->toString();
        }
        return res;
    }

    void addVertex(VertexID const& id) override { vertices.push_back(id); }
    hstd::Vec<VertexID> getAllVertices() const override {
        return vertices;
    }
};


class AlignConstraint : public ColaConstraint {
  public:
    struct [[refl]] Spec {
        [[refl]] Opt<double> fixPos = std::nullopt; ///< ??? wtf
        [[refl]] double      offset = 0.0; ///< Offset from the axis
        DESC_FIELDS(Spec, (fixPos, offset));
    };

    hstd::UnorderedMap<VertexID, Spec> vertices;

    [[refl]] GraphDimension dimension; ///< Which axist to align on
    DESC_FIELDS(AlignConstraint, (vertices, dimension));


    hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> getCola()
        const override;
};

class SeparateConstraint : public ColaConstraint {
  public:
    [[refl]] AlignConstraint left;
    [[refl]] AlignConstraint right;
    [[refl]] double          separationDistance = 1.0;
    [[refl]] bool            isExactSeparation  = false;
    [[refl]] GraphDimension  dimension; ///< Which axis to partition
                                        ///< nodes
    DESC_FIELDS(
        SeparateConstraint,
        (left, right, separationDistance, isExactSeparation, dimension));

    hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> getCola()
        const override;
};

class MultiSeparateConstraint : public ColaConstraint {
  public:
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
    [[refl]] bool fixedPosition = false;
    DESC_FIELDS(FixedRelativeConstraint, (fixedPosition));

    hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> getCola()
        const override;
};

class PageBoundaryConstraint : public ColaConstraint {
  public:
    [[refl]] geometry::Rect rect;
    [[refl]] double         weight = 100.0;
    DESC_FIELDS(PageBoundaryConstraint, (rect, weight));

    hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> getCola()
        const override;
};

class ColaLayoutAlgorithm : layout::IPlacementAlgorithm {
    Result runSingleLayout(layout::GroupID const& group) override;
};

} // namespace hstd::ext::graph::cst
