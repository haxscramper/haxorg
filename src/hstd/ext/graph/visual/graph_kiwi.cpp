#include "graph_kiwi.hpp"

using namespace hstd::ext::graph;
using namespace hstd::ext;
using namespace hstd::ext::visual;

namespace {

kiwi_ir::Anchor toCenterAnchor(kw::GraphDimension d) {
    switch (d) {
        case kw::GraphDimension::XDIM: return kiwi_ir::Anchor::HCENTER;
        case kw::GraphDimension::YDIM: return kiwi_ir::Anchor::VCENTER;
        case kw::GraphDimension::UNSET:
            throw layout::layout_error::init(
                "Unset dimension in constraint");
    }
    std::unreachable();
}

kiwi_ir::Anchor toAlignAnchor(
    kw::GraphDimension             d,
    kw::AlignConstraint::AxisAlign align) {
    using AxisAlign = kw::AlignConstraint::AxisAlign;
    if (d == kw::GraphDimension::XDIM) {
        switch (align) {
            case AxisAlign::Center: return kiwi_ir::Anchor::HCENTER;
            case AxisAlign::Left: return kiwi_ir::Anchor::LEFT;
            case AxisAlign::Right: return kiwi_ir::Anchor::RIGHT;
            case AxisAlign::Top:
            case AxisAlign::Bottom:
                throw layout::layout_error::init(
                    "Top/Bottom align can only be used in YDIM");
        }
    } else if (d == kw::GraphDimension::YDIM) {
        switch (align) {
            case AxisAlign::Center: return kiwi_ir::Anchor::VCENTER;
            case AxisAlign::Top: return kiwi_ir::Anchor::TOP;
            case AxisAlign::Bottom: return kiwi_ir::Anchor::BOTTOM;
            case AxisAlign::Left:
            case AxisAlign::Right:
                throw layout::layout_error::init(
                    "Left/Right align can only be used in XDIM");
        }
    } else {
        throw layout::layout_error::init(
            "Unset dimension in align constraint");
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
            kiwi_rects.push_back(
                kiwi_ir::Rect(
                    rect_id(id),
                    rect.x(),
                    rect.y(),
                    rect.width(),
                    rect.height()));
            return;
        }

        for (auto const& vert : run->getDirectVertices(id)) {
            if (run->isGroupVertex(vert)) { continue; }
            auto attr = run->getVertexVisualAttribute<
                kw::KiwiVertexAttribute>(vert);
            solver_nodes.insert(vert);
            kiwi_rects.push_back(
                kiwi_ir::Rect(
                    rect_id(vert),
                    // TODO: Only set constraint on the rectangle position
                    // if there is a constraint for it, by default
                    // rectangles don't have fixed positions.
                    std::nullopt,
                    std::nullopt,
                    attr->rect.width(),
                    attr->rect.height()));
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
        layout.verify_constraints();
        auto solved = layout.solve();
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

hstd::SPtr<kw::KiwiGroup> kw::KiwiGroup::newRootGraph(
    hstd::SPtr<layout::LayoutRun> run,
    Str const&                    name) {
    auto result = std::make_shared<KiwiGroup>(
        std::make_shared<SharedCtx>(SharedCtx{.run = run}), name);
    result->algorithm = std::make_shared<KiwiLayoutAlgorithm>(run);
    return result;
}

hstd::Vec<hstd::SPtr<kiwi_ir::ConstraintBase>> kw::AlignConstraint::
    getKiwi() const {
    if (vertices.empty()) {
        throw layout::layout_error::init(
            "AlignConstraint expects vertices");
    }

    auto                          anchor = kiwi_ir::Anchor::HCENTER;
    hstd::Vec<kiwi_ir::AlignItem> items;
    for (auto const& [id, spec] : vertices) {
        anchor = toAlignAnchor(dimension, spec.align);
        items.push_back(
            kiwi_ir::AlignItem{
                .rect_id = rectId(id), .offset = spec.offset});
    }

    return {std::make_shared<kiwi_ir::AlignConstraint>(
        anchor, items, kiwi_ir::Strength::REQUIRED)};
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
            rectId(right_first),
            anchor,
            rectId(left_first),
            anchor,
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
    hstd::Vec<hstd::Vec<Str>>                      groups;

    for (auto const& lane : lines) {
        if (lane.dimension != dimension) {
            throw layout::layout_error::init(
                "MultiSeparateConstraint dimension mismatch");
        }
        res.append(lane.getKiwi());
        hstd::Vec<Str> lane_ids;
        for (auto const& id : lane.getAllVertices()) {
            lane_ids.push_back(rectId(id));
        }
        groups.push_back(lane_ids);
    }

    res.push_back(
        std::make_shared<kiwi_ir::MultiSeparateConstraint>(
            groups,
            toCenterAnchor(dimension),
            separationDistance,
            kiwi_ir::Strength::REQUIRED));

    return res;
}

layout::IPlacementAlgorithm::Result kw::KiwiLayoutAlgorithm::
    runSingleLayout(VertexID const& root_id) {
    auto __scope = run->begin_scope(
        hstd::fmt(
            "running single layout for kw::KiwiLayoutAlgorithm {}",
            run->getDebug(root_id)));

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
