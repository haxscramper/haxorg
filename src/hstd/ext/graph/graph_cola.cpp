#include "graph_cola.hpp"
#include <hstd/stdlib/Ranges.hpp>

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
            auto rect      = geometry::Rect(
                vpsc_rect->getMinX(),
                vpsc_rect->getMinY(),
                vpsc_rect->getMaxX() - vpsc_rect->getMinX(),
                vpsc_rect->getMaxY() - vpsc_rect->getMinY());

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
        }
    };

    aux(root_id, std::nullopt);


    return result;
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
