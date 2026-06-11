#include "graph_kiwi.hpp"

#if ORG_BUILD_WITH_KIWI

#    include <hstd/stdlib/Ranges.hpp>

using namespace hstd::ext::graph;
using namespace hstd::ext;
using namespace hstd::ext::visual;

namespace {

kiwi_ir::Anchor toCenterAnchor(kiwi_ir::Axis d) {
    switch (d) {
        case kiwi_ir::Axis::X: return kiwi_ir::Anchor::HCENTER;
        case kiwi_ir::Axis::Y: return kiwi_ir::Anchor::VCENTER;
    }
    std::unreachable();
}


struct single_layout_run_state {
    hstd::SPtr<layout::LayoutRun> run;
    VertexID                      root_id;
    hstd::SPtr<kw::KiwiGroup>     root_group;

    std::unordered_map<VertexID, geometry::Rect> absolute_rects;
    std::unordered_map<VertexID, geometry::Rect> bbox_map;
    std::unordered_set<VertexID>                 solver_nodes;

    hstd::Vec<kiwi_ir::Rect>                       kiwi_rects;
    hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> kiwi_constraints;
    layout::IPlacementAlgorithm::Result            result;

    single_layout_run_state(
        VertexID const&               root_id,
        hstd::SPtr<layout::LayoutRun> run)
        : run{run}
        , root_id{root_id}
        , root_group{run->getGroup<kw::KiwiGroup>(root_id)} {}

    hstd::Str rect_id(VertexID const& id) const {
        return run->getVertex(id)->getStableId();
    }

    void collect_solver_nodes(VertexID const& id) {
        auto group = run->getGroup<layout::IGroupVisualAttribute>(id);
        if (group->hasAlgorithm() && id != root_id) {
            auto rect = run->getLayout(id)->getBBox();
            if (auto pad = group->getOuterPadding()) {
                rect = rect.withOuterPadding(pad.value());
            }
            solver_nodes.insert(id);
            // <<kw/layout/reuse-existing-vertices>>
            if (auto kiwi_attr = run->getVertex(id)
                                     ->getOptionalAttribute<
                                         kw::KiwiVertexAttribute>()) {
                kiwi_attr.value()->setRectWidth(rect.width());
                kiwi_attr.value()->setRectHeight(rect.height());
                kiwi_rects.push_back(kiwi_attr.value()->rect);
            } else {
                kiwi_rects.push_back(
                    kiwi_ir::Rect(
                        rect_id(id),
                        // sub-group placement is controlled by the current
                        // single layout run, so any x/y coordinates from
                        // the sub-layout runs would only interfere here.
                        std::nullopt,
                        std::nullopt,
                        rect.width(),
                        rect.height()));
            }

            return;
        }

        for (auto const& vert : run->getDirectVertices(id)) {
            if (run->isGroupVertex(vert)) { continue; }
            auto attr = run->getVertexVisualAttribute<
                kw::KiwiVertexAttribute>(vert);
            solver_nodes.insert(vert);
            kiwi_rects.push_back(attr->rect);
        }

        for (auto const& sub : run->getSubGroups(id)) {
            collect_solver_nodes(sub);
        }
    }

    void collect_constraints(VertexID const& id) {
        auto group = run->getGroup<layout::IGroupVisualAttribute>(id);
        if (group->hasAlgorithm() && id != root_id) { return; }

        for (auto const& constraint : group->constraints) {
            auto kwc = std::dynamic_pointer_cast<kw::KiwiConstraint>(
                constraint);
            hstd::logic_assertion_check_not_nil(kwc);
            kiwi_constraints.append(kwc->getKiwi());
        }

        for (auto const& sub : run->getSubGroups(id)) {
            collect_constraints(sub);
        }
    }

    void run_solver() {
        kiwi_ir::Layout layout(kiwi_rects, kiwi_constraints);

        static int kiwi_run_counter = 0;
        if (run->TraceState) {
            layout.to_graphviz(run->getAdjacentToTraceFile(
                std::format(
                    "kiwi_solver_run_{}.png",
                    hstd::fmt1(kiwi_run_counter))));
        }


        layout.verify_constraints();
        auto solved = layout.solve();

        if (run->TraceState) {
            run->writeAdjacentToTraceFile(
                std::format(
                    "kiwi_solver_run_{}.svg",
                    hstd::fmt1(kiwi_run_counter)),
                layout.to_svg(hstd::fmt1(kiwi_run_counter)).to_string(2));
        }
        ++kiwi_run_counter;

        for (auto const& id : solver_nodes) {
            absolute_rects.insert_or_assign(
                id, solved.at(rect_id(id)).getGeometry());
        }
    }

    geometry::Rect collect_bbox(VertexID const& id) {
        auto group = run->getGroup<layout::IGroupVisualAttribute>(id);
        if (group->hasAlgorithm() && id != root_id) {
            auto rect = absolute_rects.at(id);
            bbox_map.insert_or_assign(id, rect);
            return rect;
        }

        auto bbox = geometry::Rect::FromLimitBoundaries();

        for (auto const& sub : run->getSubGroups(id)) {
            bbox.extend(collect_bbox(sub));
        }

        for (auto const& vert : run->getDirectVertices(id)) {
            if (run->isGroupVertex(vert)) { continue; }
            bbox.extend(absolute_rects.at(vert));
        }

        bbox_map.insert_or_assign(id, bbox);
        return bbox;
    }

    void collect_relative_positions(VertexID const& id) {
        auto group_bbox = bbox_map.at(id);
        auto offset     = -group_bbox.upper_left();

        for (auto const& vert : run->getDirectVertices(id)) {
            if (run->isGroupVertex(vert)) { continue; }
            auto rect = absolute_rects.at(vert).move(offset);
            result.vertices.insert_or_assign(
                vert,
                std::make_shared<kw::KiwiVertexLayoutAttribute>(
                    rect,
                    run->getGraph()->getVertex(vert)->getStableId()));
        }

        for (auto const& sub : run->getSubGroups(id)) {
            auto sub_bbox_abs = bbox_map.at(sub);
            auto sub_bbox_rel = sub_bbox_abs.move(offset);
            auto sub_group = run->getGroup<layout::IGroupVisualAttribute>(
                sub);

            if (sub_group->hasAlgorithm() && sub != root_id) {
                auto prev = run->getLayout<layout::IGroupLayoutAttribute>(
                    sub);
                if (auto pad = sub_group->getOuterPadding()) {
                    sub_bbox_rel = sub_bbox_rel.withInnerPadding(
                        pad.value());
                }
                prev->setBBox(sub_bbox_rel);
                result.vertices.insert_or_assign(sub, prev);
            } else {
                collect_relative_positions(sub);
                result.vertices.insert_or_assign(
                    sub,
                    std::make_shared<kw::KiwiGroupLayoutAttribute>(
                        sub_bbox_rel, run->getGroup<kw::KiwiGroup>(sub)));
            }
        }
    }

    void execute_edge_placement(kw::KiwiLayoutAlgorithm* algo) {
        auto r = algo->router;
        r->run = run.get();

        for (auto const& [vertex, attr] : result.vertices) {
            r->rects.insert_or_assign(vertex, attr->getBBox());
        }

        r->edge_set   = run->getLayoutLayerNestedEdges(root_id);
        r->vertex_set = run->getDirectVertices(root_id);
        auto res      = r->routeEdges();
        for (auto const& [edge, attr] : res.edges) {
            result.edges.insert_or_assign(edge, attr);
        }
    }
};

} // namespace

hstd::SPtr<kw::KiwiVertexAttribute> kw::KiwiGroup::addVertex(
    EdgeID const& edge) {
    auto id    = getRun()->getGraph()->getTarget(edge);
    auto vattr = std::make_shared<KiwiVertexAttribute>(
        kiwi_ir::Rect{run->getVertex(id)->getStableId()});

    getRun()->setNestedVertexAttribute(edge, vattr);
    return vattr;
}

hstd::SPtr<kw::KiwiVertexAttribute> kw::KiwiGroup::addVertex(
    EdgeID const&         edge,
    geometry::Rect const& size) {
    auto id = getRun()->getGraph()->getTarget(edge);

    auto vattr = std::make_shared<KiwiVertexAttribute>(kiwi_ir::Rect{
        // TODO: See [[kiwi-rectangle-id-knowledge-direction]]
        run->getVertex(id)->getStableId(),
        // TODO: Only set constraint on the rectangle position
        // if there is a constraint for it, by default
        // rectangles don't have fixed positions.
        std::nullopt,
        std::nullopt,
        size.width(),
        size.height(),
    });

    getRun()->setNestedVertexAttribute(edge, vattr);
    return vattr;
}

hstd::SPtr<kw::KiwiGroup> kw::KiwiGroup::newRootGraph(
    hstd::SPtr<layout::LayoutRun> run,
    Str const&                    name) {
    auto result = std::make_shared<KiwiGroup>(
        std::make_shared<SharedCtx>(SharedCtx{.run = run}), name);
    result->algorithm = std::make_shared<KiwiLayoutAlgorithm>(run);
    return result;
}

kw::AlignConstraint* kw::AlignConstraint::addAlignVertex(
    VertexID const&            id,
    hstd::Opt<kiwi_ir::Anchor> align,
    double                     offset) {
    if (align) {
        if (dimension == kiwi_ir::Axis::X) {
            LOGIC_ASSERTION_CHECK_FMT(
                align == kiwi_ir::Anchor::LEFT
                    || align == kiwi_ir::Anchor::RIGHT
                    || align == kiwi_ir::Anchor::HCENTER,
                "cannot use anchor {} with align constraint {}",
                align,
                dimension);
        } else {
            LOGIC_ASSERTION_CHECK_FMT(
                align == kiwi_ir::Anchor::TOP
                    || align == kiwi_ir::Anchor::BOTTOM
                    || align == kiwi_ir::Anchor::VCENTER,
                "cannot use anchor {} with align constraint {}",
                align,
                dimension);
        }
    }
    vertices.insert_or_assign(
        id,
        kiwi_ir::AlignSpec{
            .anchor = align.value_or(
                dimension == kiwi_ir::Axis::X ? kiwi_ir::Anchor::HCENTER
                                              : kiwi_ir::Anchor::VCENTER),
            .offset = offset,
        });
    return this;
}

hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> kw::AlignConstraint::
    getKiwi() const {
    if (vertices.empty()) {
        throw layout::layout_error::init(
            "AlignConstraint expects vertices");
    }

    hstd::Vec<kiwi_ir::AlignItem> items;
    for (auto const& [id, spec] : vertices) {
        items.push_back(
            kiwi_ir::AlignItem{.rect_id = rectId(id), .spec = spec});
    }

    return {std::make_shared<kiwi_ir::AlignConstraint>(
        items, kiwi_ir::Strength::REQUIRED)};
}

hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> kw::SeparateConstraint::
    getKiwi() const {
    if (left.vertices.empty() || right.vertices.empty()) {
        throw layout::layout_error::init(
            "SeparateConstraint expects both lanes to be non-empty");
    }

    hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> res;
    res.append(left.getKiwi());
    res.append(right.getKiwi());

    auto left_first  = left.getAllVertices().front();
    auto right_first = right.getAllVertices().front();
    auto anchor      = toCenterAnchor(dimension);

    res.push_back(
        std::make_shared<kiwi_ir::SeparateConstraint>(
            kiwi_ir::RectSpec1Side(rectId(right_first), anchor),
            kiwi_ir::RectSpec1Side(rectId(left_first), anchor),
            separationDistance,
            kiwi_ir::Strength::REQUIRED));

    return res;
}

hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> kw::
    MultiSeparateConstraint::getKiwi() const {
    if (lines.size() < 2) {
        throw layout::layout_error::init(
            "MultiSeparateConstraint expects at least two lanes");
    }

    hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> res;
    hstd::Vec<hstd::Vec<kiwi_ir::RectSpec1Side>>   groups;

    for (auto const& lane : lines) {
        if (lane.dimension != dimension) {
            throw layout::layout_error::init(
                "MultiSeparateConstraint dimension mismatch");
        }
        res.append(lane.getKiwi());
        hstd::Vec<kiwi_ir::RectSpec1Side> lane_ids;
        for (auto const& id : lane.getAllVertices()) {
            lane_ids.push_back(
                kiwi_ir::RectSpec1Side(
                    rectId(id), toCenterAnchor(dimension)));
        }
        groups.push_back(lane_ids);
    }

    res.push_back(
        std::make_shared<kiwi_ir::MultiSeparateConstraint>(
            groups, separationDistance, kiwi_ir::Strength::REQUIRED));

    return res;
}

layout::IPlacementAlgorithm::Result kw::KiwiLayoutAlgorithm::
    runSingleLayout(VertexID const& root_id) {
    OP_TRACER_MESSAGE_SCOPE(
        run,
        "running single layout for kw::KiwiLayoutAlgorithm {}",
        run->getDebug(root_id));

    hstd::logic_assertion_check_not_nil(router);

    single_layout_run_state state(root_id, run);
    state.collect_solver_nodes(root_id);
    state.collect_constraints(root_id);
    state.run_solver();
    state.collect_bbox(root_id);
    state.collect_relative_positions(root_id);
    state.execute_edge_placement(this);

    auto root_bbox = state.bbox_map.at(root_id).move(
        geometry::Point{} - state.bbox_map.at(root_id).upper_left());

    state.result.vertices.insert_or_assign(
        root_id,
        std::make_shared<kw::KiwiGroupLayoutAttribute>(
            root_bbox, state.root_group));

    return state.result;
}

hstd::ext::visual::VisGroup kw::KiwiGroupLayoutAttribute::getVisual(
    VertexID const& id) const {
    using namespace visual;
    VisGroup res{};
    res.offset = this->rect.upper_left();

    visual::VisElement::RectShape rect_shape;
    rect_shape.geometry = Rect(
        0, 0, this->rect.width(), this->rect.height());
    rect_shape.pen = visual::VisPen{
        .color = visual::VisColor{128, 128, 128, 255},
        .width = 1.0f,
        .style = visual::VisPen::LineStyle::Dash,
    };

    visual::VisElement rectElem;
    rectElem.data = rect_shape;
    res.elements.push_back(rectElem);

    res.elements.push_back(
        visual::VisElement::FromText(
            hstd::fmt("GROUP:{}", group->local.name),
            geometry::Point(0, 0)));

    res.custom.setAttr(
        "inkscape:label", hstd::fmt("KIWI GROUP:{}", group->local.name));

    return res;
}

hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> kw::ParentWrapConstraint::
    getKiwi() const {
    if (nested.empty()) {
        throw layout::layout_error::init(
            "ParentWrapContraint expects vertices");
    }

    return {
        std::make_shared<kiwi_ir::ParentWrapConstraint>(
            rectId(parent),
            nested | rv::transform([this](VertexID const& id) -> Str {
                return rectId(id);
            }) | rs::to<Vec>(),
            pad,
            strength),
    };
}

hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> kw::RelativeConstraint::
    getKiwi() const {
    return {
        std::make_shared<kiwi_ir::RelativeConstraint>(
            /*nested_rect_id=*/rectId(fixed.id),
            /*parent_rect_id=*/rectId(relative.id),
            /*x_dim=*/x_dim,
            /*y_dim=*/y_dim,
            /*anchor_fixed=*/fixed.anchor,
            /*anchor_relative=*/relative.anchor,
            /*strength=*/strength),
    };
}

hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> kw::EvenGapConstraint::
    getKiwi() const {
    return {
        std::make_shared<kiwi_ir::EvenGapConstraint>(
            vertices
                | rv::transform(
                    [this](VertexID const& id) -> kiwi_ir::RectSpec2Side {
                        return axis == kiwi_ir::Axis::X
                                 ? kiwi_ir::RectSpec2Side::
                                       HorizontalRectBounds(rectId(id))
                                 : kiwi_ir::RectSpec2Side::
                                       VerticalRectBounds(rectId(id));
                    })
                | rs::to<Vec>(),
            /*strength=*/strength),
    };
}

hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> kw::EqualSizeConstraint::
    getKiwi() const {
    return {
        std::make_shared<kiwi_ir::EqualSizeConstraint>(
            rectId(vert_a),
            rectId(vert_b),
            match_width,
            match_height,
            /*strength=*/strength),
    };
}

hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> kw::LinearConstraint::
    getKiwi() const {
    return {
        std::make_shared<kiwi_ir::LinearConstraint>(
            lhs.value(),
            rel,
            rhs.value(),
            /*strength=*/strength),
    };
}

#endif
