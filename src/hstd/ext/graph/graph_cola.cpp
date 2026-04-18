#include "graph_cola.hpp"
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/stdlib/Enumerate.hpp>

using namespace hstd::ext::graph;

vpsc::Dim toVpsc(cst::GraphDimension dim) {
    switch (dim) {
        case cst::GraphDimension::XDIM: return vpsc::Dim::XDIM;
        case cst::GraphDimension::YDIM: return vpsc::Dim::YDIM;
        case cst::GraphDimension::UNSET: return vpsc::Dim::UNSET;
    }
}


layout::IPlacementAlgorithm::Result hstd::ext::graph::cst::
    ColaLayoutAlgorithm::runSingleLayout(layout::GroupID const& root_id) {
    run->message("running single layout for cst::ColaLayoutAlgorithm");
    auto __scope = run->scopeLevel();

    auto rootGroup = std::dynamic_pointer_cast<ColaGroup>(
        run->getGroup(root_id));
    auto ctx = rootGroup->shared;


    hstd::Vec<hstd::SPtr<cola::CompoundConstraint>> ccs_s;
    std::vector<cola::CompoundConstraint*>          ccs;

    hstd::UnorderedMap<layout::GroupID, hstd::SPtr<vpsc::Rectangle>>
        sub_group_rectangles;

    std::vector<vpsc::Rectangle*> vertices //
        = hstd::own_view(rootGroup->nodeAttributes().keys())
        | rv::transform(
              [&](VertexID const& id) { return ctx->getRect(id).get(); })
        | rs::to<std::vector>();

    auto aux = [&](this auto&&                       self,
                   layout::GroupID const&            id,
                   hstd::Opt<layout::GroupID> const& parent) -> void {
        auto group = run->getGroup(id);
        if (group->hasAlgorithm() && id != root_id) {
            auto parentGroup = std::dynamic_pointer_cast<ColaGroup>(
                run->getGroup(parent.value()));
            run->message(
                hstd::fmt(
                    "group '{}' has layout algorithm set",
                    group->getStableId()));
            auto recursiveBBox = run->getLayout(id)->getPointsBBox();
            auto rect          = std::make_shared<vpsc::Rectangle>(
                recursiveBBox.min_x(),
                recursiveBBox.max_x(),
                recursiveBBox.min_y(),
                recursiveBBox.max_y());

            sub_group_rectangles.insert_or_assign(id, rect);
            vertices.push_back(rect.get());
        } else {
            for (auto const& sub : group->subGroups) { self(sub, id); }
        }
    };

    aux(root_id, std::nullopt);

    auto aux_constraints = [&](this auto&&            self,
                               layout::GroupID const& id) -> void {
        for (auto const& constraint : rootGroup->constraints) {
            auto cola_cs = std::dynamic_pointer_cast<cst::ColaConstraint>(
                constraint);
            ccs_s.append(cola_cs->getCola());
        }

        auto group = run->getGroup(id);
        for (auto const& sub : group->subGroups) { self(sub); }
    };

    aux_constraints(root_id);

    cola::ConstrainedFDLayout alg2(
        vertices,
        hstd::own_view(rootGroup->edgeAttributes().keys())
            | rv::transform(
                [&](EdgeID const& id) -> Pair<unsigned, unsigned> {
                    return ctx->getEdgeIdx(id);
                })
            | rs::to<std::vector>(),
        60);


    alg2.setConstraints(ccs);
    alg2.run();


    layout::IPlacementAlgorithm::Result result;

    geometry::Rect bbox = Rect::FromLimitBoundaries();

    auto aux_layout =
        [&](this auto&&                       self,
            layout::GroupID const&            id,
            hstd::Opt<layout::GroupID> const& parent) -> void {
        auto group = run->getGroup(id);
        if (group->hasAlgorithm() && id != root_id) {
            auto const& prev_attribute = run->getLayout(id);
            auto        prev_cast      = std::dynamic_pointer_cast<
                ColaGroupLayoutAttribute>(prev_attribute);
            auto vpsc_rect = sub_group_rectangles.at(id);
            auto rect      = adapt::to_hstd(*vpsc_rect);
            bbox.extend(rect);

            if (prev_attribute) {
                run->message("previous attribute was a graphviz layout");
                result.groups.insert_or_assign(
                    id,
                    std::make_shared<ColaGroupLayoutAttribute>(
                        rect, prev_cast->group));
            } else {
                // FIXME: Is the `rootGroup` appropriate here, or I need to
                // get the parent group based on the `parent` field if it
                // is present.
                run->message(
                    hstd::fmt(
                        "previous attribute was {}",
                        typeid(prev_cast.get()).name()));
                result.groups.insert_or_assign(
                    id,
                    std::make_shared<ColaGroupLayoutAttribute>(
                        rect, rootGroup));
            }

        } else {
            for (auto const& sub : group->subGroups) { self(sub, id); }

            for (auto const& vert : group->getVertices()) {
                result.vertices.insert_or_assign(
                    vert,
                    std::make_shared<ColaVertexLayoutAttribute>(
                        adapt::to_hstd(*ctx->getRect(vert))));
            }
        }
    };

    aux_layout(root_id, std::nullopt);

    result.groups.insert_or_assign(
        root_id,
        std::make_shared<ColaGroupLayoutAttribute>(bbox, rootGroup));


    return result;
}

layout::GroupID cst::ColaGroup::newRootGraph(
    hstd::SPtr<layout::LayoutRun> run) {
    auto result = std::make_shared<ColaGroup>(
        std::make_shared<SharedCtx>(API::SharedCtxBase{
            .run = run,
        }),
        hstd::Str{"root"});

    result->algorithm = std::make_shared<ColaLayoutAlgorithm>(run);
    auto id           = run->addRootGroup(result);
    result->groups().insert_or_assign(id, result);
    return id;
}


hstd::Vec<hstd::SPtr<cola::CompoundConstraint>> hstd::ext::graph::cst::
    SeparateConstraint::getCola() const {
    auto left_constraint  = left.getCola().at(0);
    auto right_constraint = right.getCola().at(0);
    if (dimension != left.dimension || dimension != right.dimension) {
        throw std::logic_error(fmt(
            "separation constraint alignments must have the same "
            "dimension. Separation has dimension {}, left: {}, right:{}",
            this->dimension,
            left.dimension,
            right.dimension));
    }

    auto result = std::make_shared<cola::SeparationConstraint>(
        toVpsc(dimension),
        dynamic_cast<cola::AlignmentConstraint*>(left_constraint.get()),
        dynamic_cast<cola::AlignmentConstraint*>(right_constraint.get()),
        separationDistance,
        isExactSeparation);

    return {result, left_constraint, right_constraint};
}


hstd::Vec<hstd::SPtr<cola::CompoundConstraint>> cst::
    FixedRelativeConstraint::getCola() const {
    return {std::make_shared<cola::FixedRelativeConstraint>(
        getAllRectanglesSorted(), getAllShapeIdsSorted(), fixedPosition)};
}


hstd::Vec<hstd::SPtr<cola::CompoundConstraint>> cst::AlignConstraint::
    getCola() const {
    auto result = std::make_shared<cola::AlignmentConstraint>(
        toVpsc(dimension));

    for (auto const& [vertexId, spec] : vertices) {
        result->addShape(getShapeId(vertexId), spec.offset);
        if (spec.fixPos) { result->fixPos(*spec.fixPos); }
    }

    return {result};
}


std::string hstd::ext::graph::cst::ColaConstraint::getRepr() const {
    return std::string{"["}
         + (own_view(getCola()) //
            | rv::transform(
                [](hstd::SPtr<cola::CompoundConstraint> const& it) {
                    return it->toString();
                })
            | rv::intersperse(", ") //
            | rv::join              //
            | rs::to<std::string>())
         + std::string{"]"};
}

std::vector<vpsc::Rectangle*> hstd::ext::graph::cst::ColaConstraint::
    getRectangles() const {
    return hstd::own_view(group->nodeAttributes().keys())
         | rv::transform([&](VertexID const& id) {
               return group->shared->getRect(id).get();
           })
         | rs::to<std::vector>();
}

std::vector<unsigned> cst::ColaConstraint::getShapeIds() const {
    return hstd::own_view(group->nodeAttributes().keys())
         | rv::transform([&](VertexID const& id) -> unsigned {
               return group->shared->getVertexIdx(id);
           })
         | rs::to<std::vector>();
}


hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> hstd::ext::graph::cst::
    MultiSeparateConstraint::getCola() const {
    Vec<ConstraintPtr> result;
    for (auto const& [idx, line] : enumerate(lines)) {
        if (line.dimension != this->dimension) {
            throw std::logic_error(
                fmt("multi-aling line {} has dimension {} but the main "
                    "multi-align has dimension {} -- align dimensions "
                    "must match",
                    idx,
                    line.dimension,
                    this->dimension));
        }

        result.push_back(line.getCola().at(0));
    }

    auto sep = std::make_shared<cola::MultiSeparationConstraint>(
        toVpsc(dimension), separationDistance, isExactSeparation);

    LOGIC_ASSERTION_CHECK(sep.get() != nullptr, "");

    for (auto const& it : hstd::enumerator(alignPairs)) {
        auto const& src = it.value().first;
        auto const& dst = it.value().second;
        if (!(src < result.size() && dst < result.size())) {
            throw std::range_error(fmt(
                "multi separate pair {} src/dst are out of range: dst:{}, "
                "src:{} line-count:{}",
                it.index(),
                src,
                dst,
                result.size()));
        }

        sep->addAlignmentPair(
            dynamic_cast<cola::AlignmentConstraint*>(result.at(src).get()),
            dynamic_cast<cola::AlignmentConstraint*>(result.at(dst).get())
            //
        );
    }

    result.push_back(sep);

    return result;
}

hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> hstd::ext::graph::cst::
    PageBoundaryConstraint::getCola() const {
    auto result = std::make_shared<cola::PageBoundaryConstraints>(
        rect.min_x(), rect.max_x(), rect.min_y(), rect.max_y(), weight);

    for (auto const& [idx, rect] : enumerate(getAllRectanglesSorted())) {
        result->addShape(idx, rect->height() / 2, rect->width() / 2);
    }

    return {result};
}
