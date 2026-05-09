#include "graph_cola.hpp"
#include "hstd/ext/logger.hpp"
#include "hstd/stdlib/Debug.hpp"
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>

using namespace hstd::ext::graph;
using namespace hstd::ext;
using namespace hstd::ext::visual;

vpsc::Dim toVpsc(cst::GraphDimension dim) {
    switch (dim) {
        case cst::GraphDimension::XDIM: return vpsc::Dim::XDIM;
        case cst::GraphDimension::YDIM: return vpsc::Dim::YDIM;
        case cst::GraphDimension::UNSET: return vpsc::Dim::UNSET;
    }
}

namespace {
struct unsatisifed_validation_state {
    cola::UnsatisfiableConstraintInfos                       unsatX;
    cola::UnsatisfiableConstraintInfos                       unsatY;
    hstd::UnorderedMap<hstd::u64, hstd::Pair<VertexID, int>> cc_index;
    hstd::SPtr<layout::LayoutRun>                            run;
    hstd::SPtr<cst::ColaGroup>                               rootGroup;

    void validate_unsatisfied() {
        std::string             unsatisfied_debug;
        hstd::UnorderedSet<int> failed;
        auto mark_unsatisified = [&](std::string const& dimension,
                                     cola::UnsatisfiableConstraintInfo*
                                         info) {
            if (cc_index.contains((hstd::u64)info->cc)) {

                auto [group_id, constraint_idx] = cc_index.at(
                    (hstd::u64)info->cc);
                if (failed.contains(constraint_idx)) {
                    return;
                } else {
                    failed.incl(constraint_idx);
                }

                unsatisfied_debug += hstd::fmt(
                    "\nConstraint at index {} in group {} created cola "
                    "constraint\n  {},\nwhich could not be satisfied in "
                    "{}-dim for vertices\n{}\n{}.",
                    constraint_idx,
                    run->getGroup(group_id)->getStableId(),
                    info->cc->toString(),
                    dimension,
                    hstd::own_view(run->getGroup(group_id)
                                       ->constraints.at(constraint_idx)
                                       ->getAllVertices())
                        | hstd::rv::transform(
                            [&](VertexID const& id) -> std::string {
                                return hstd::fmt(
                                    "- {} rect {}",
                                    run->getDebug(id),
                                    rootGroup->get_shared_ctx()
                                        ->getVertexIdx(id),
                                    adapt::to_hstd(
                                        *rootGroup->get_shared_ctx()
                                             ->getRect(id)));
                            })
                        | hstd::rv_intersperse_newline_join,
                    info->toString());
            } else {
                unsatisfied_debug += hstd::fmt("\n{}", info->toString());
            }
        };

        for (auto info : unsatX) {
            if (info != nullptr) { mark_unsatisified("X", info); }
        }
        for (auto info : unsatY) {
            if (info != nullptr) { mark_unsatisified("Y", info); }
        }

        if (!unsatisfied_debug.empty()) {
            run->message(unsatisfied_debug);
            // throw layout::layout_error::init(unsatisfied_debug);
        }
    };
};

struct single_layout_run_state {
    hstd::SPtr<cst::ColaGroup>            rootGroup;
    hstd::SPtr<cst::ColaGroup::SharedCtx> ctx;

    hstd::UnorderedMap<VertexID, hstd::SPtr<vpsc::Rectangle>>
        sub_group_rectangles;

    std::vector<vpsc::Rectangle*> layout_rects;
    hstd::SPtr<layout::LayoutRun> run;
    VertexID                      root_id;

    single_layout_run_state(
        VertexID const&               root_id,
        hstd::SPtr<layout::LayoutRun> run)
        : run{run}, root_id{root_id} {
        rootGroup    = run->getGroup<cst::ColaGroup>(root_id);
        ctx          = rootGroup->shared;
        layout_rects = ctx->getAllRectanglesSorted();
    }

    void extend_layout_rectangles_with_sub_groups(
        VertexID const&            aux_group_id,
        hstd::Opt<VertexID> const& parent_group_id) {
        auto group = run->getGroup(aux_group_id);
        if (group->hasAlgorithm() && aux_group_id != root_id) {
            auto parentGroup = run->getGroup<cst::ColaGroup>(
                parent_group_id.value());

            auto recursiveBBox = run->getLayout(aux_group_id)->getBBox();

            if (auto pad = group->getOuterPadding()) {
                recursiveBBox = recursiveBBox.withOuterPadding(
                    pad.value());
            }

            auto rect = std::make_shared<vpsc::Rectangle>(
                recursiveBBox.min_x(),
                recursiveBBox.max_x(),
                recursiveBBox.min_y(),
                recursiveBBox.max_y());

            run->message(
                hstd::fmt(
                    "group '{}' has layout algorithm set with bounding "
                    "box {} (base bbox {})",
                    group->getStableId(),
                    recursiveBBox,
                    run->getLayout(aux_group_id)->getBBox()));

            sub_group_rectangles.insert_or_assign(aux_group_id, rect);
            layout_rects.push_back(rect.get());
        } else {
            for (auto const& sub : run->getSubGroups(aux_group_id)) {
                extend_layout_rectangles_with_sub_groups(
                    sub, aux_group_id);
            }
        }
    }


    std::vector<cola::Edge> edges;
    std::vector<double>     edgeLenOverride;
    void                    collect_edge_len_override_parameters(
        cst::ColaLayoutAlgorithm const* algo) {
        for (EdgeID const& id : run->getDirectlyNestedEdges(root_id)) {
            edges.push_back(ctx->getEdgeIdx(id, ctx->run));
            if (!algo->idealEdgeLength.empty()) {
                if (auto len = algo->idealEdgeLength.get(id)) {
                    edgeLenOverride.push_back(len.value());
                } else {
                    edgeLenOverride.push_back(algo->commonIdealEdgeLength);
                }
            }
        }
    }


    hstd::Vec<hstd::SPtr<cola::CompoundConstraint>> ccs_s;
    hstd::Vec<cola::CompoundConstraint*>            ccs;
    cola::Locks                                     locks;

    void recursively_collect_constraints(
        VertexID const&               id,
        unsatisifed_validation_state& validation_state) {
        char const* _fname  = "constraints";
        auto        __scope = run->scopeLevelMsg(
            hstd::fmt("recursively collect on {}", run->getDebug(id)),
            _fname);
        auto group = run->getGroup(id);
        for (auto const& [ir_idx, constraint] :
             enumerate(group->constraints)) {
            auto cola_cs = std::dynamic_pointer_cast<cst::ColaConstraint>(
                constraint);
            if (auto lock_cs = std::dynamic_pointer_cast<
                    cst::LockPositionConstraint>(cola_cs)) {
                locks.push_back(lock_cs->getLock());
            } else {
                hstd::logic_assertion_check_not_nil(cola_cs);
                auto new_ccs = cola_cs->getCola();

                if (auto cola_al = std::dynamic_pointer_cast<
                        cst::FixedRelativeConstraint>(cola_cs)) {
                    run->message("found fixed relative");
                    VertexIDVec vert        = cola_al->getAllVertices();
                    auto        base_vertex = layout_rects.at(
                        rootGroup->get_shared_ctx()->getVertexIdx(
                            vert.at(0)));
                    for (VertexID const& rel_vertex :
                         vert.at(slice(1, 1_B))) {
                        auto rel_rect = layout_rects.at(
                            rootGroup->get_shared_ctx()->getVertexIdx(
                                rel_vertex));
                        double dx = rel_rect->getMinX()
                                  - base_vertex->getMinX()
                                  + cola_al->shapes.at(rel_vertex).x();
                        double dy = rel_rect->getMinY()
                                  - base_vertex->getMinY()
                                  + cola_al->shapes.at(rel_vertex).y();

                        run->message(
                            hstd::fmt(
                                "moving rect for {} by {} {}",
                                rel_vertex,
                                dx,
                                dy),
                            _fname);

                        rel_rect->offset(dx, dy);
                    }
                }

                ccs_s.append(new_ccs);
                for (auto const& s : new_ccs) {
                    ccs.push_back(s.get());
                    validation_state.cc_index.insert_or_assign(
                        (hstd::u64)s.get(),
                        hstd::Pair<VertexID, int>{id, ir_idx});
                }
            }

            run->message(
                hstd::fmt("constraint {}", cola_cs->getRepr()), _fname);
        }

        for (auto const& sub : run->getSubGroups(id)) {
            recursively_collect_constraints(sub, validation_state);
        }
    }


    hstd::UnorderedMap<VertexID, geometry::Rect> bbox_map;
    void collect_absolute_bounding_box_positions(VertexID const& id) {
        char const* _fname  = "absolute-bbox";
        auto        __scope = run->scopeLevelMsg(
            hstd::fmt("absolute bounding box on {}", run->getDebug(id)),
            _fname);

        auto group = run->getGroup(id);
        if (group->hasAlgorithm() && id != root_id) {
            auto const& prev_attribute = run->getLayout(id);
            auto        prev_cast      = std::dynamic_pointer_cast<
                cst::ColaGroupLayoutAttribute>(prev_attribute);
            auto vpsc_rect = sub_group_rectangles.at(id);
            auto rect      = adapt::to_hstd(*vpsc_rect);
            run->message(
                hstd::fmt("{} rect is {}", run->getDebug(id), rect),
                _fname);
            // if (auto pad = group->getOuterPadding()) {
            //     rect = rect.withInnerPadding(pad.value());
            //     run->message(
            //         hstd::fmt(
            //             "has padding {} added inner {}",
            //             pad.value(),
            //             rect));
            // }

            bbox_map.insert_or_assign(id, rect);

        } else {
            auto bbox = geometry::Rect::FromLimitBoundaries();
            for (auto const& group_id : run->getSubGroups(id)) {
                collect_absolute_bounding_box_positions(group_id);
                run->message(
                    hstd::fmt(
                        "{} extend with {}", id, bbox_map.at(group_id)),
                    _fname);
                bbox.extend(bbox_map.at(group_id));
            }

            for (auto const& vert : run->getDirectVertices(id)) {
                auto rect = ctx->getRect(vert);
                bbox.extend(adapt::to_hstd(*rect));
                run->message(
                    hstd::fmt(
                        "{} extend with {}", id, adapt::to_hstd(*rect)),
                    _fname);
            }

            run->message(hstd::fmt("final {}", bbox), _fname);
            bbox_map.insert_or_assign(id, bbox);
        }
    }


    layout::IPlacementAlgorithm::Result result;
    void collect_nodes_and_sub_groups_relative_positions(
        VertexID const&        id,
        geometry::Point const& rel_offset) {
        char const* _fname  = "relative-pos";
        auto        __scope = run->scopeLevelMsg(
            hstd::fmt(
                "relative position on {} offset {}",
                run->getDebug(id),
                rel_offset),
            _fname);

        auto group = run->getGroup(id);
        if (group->hasAlgorithm() && id != root_id) {
            auto const& prev_attribute = run->getLayout<
                layout::IGroupLayoutAttribute>(id);
            auto prev_cast = std::dynamic_pointer_cast<
                cst::ColaGroupLayoutAttribute>(prev_attribute);
            auto vpsc_rect = sub_group_rectangles.at(id);
            auto rect      = adapt::to_hstd(*vpsc_rect);
            if (auto pad = group->getOuterPadding()) {
                rect = rect.withInnerPadding(pad.value());
            }

            rect = rect.move(rel_offset);
            prev_attribute->setBBox(rect);
            run->message(hstd::fmt("content bbox {}", rect), _fname);

            result.vertices.insert_or_assign(id, prev_attribute);
        } else {
            auto group_bbox = bbox_map.at(id);
            auto __scope    = run->scopeLevelMsg(
                hstd::fmt("parent bbox {}", group_bbox), _fname);

            auto const& offset_to_zero_coords = -group_bbox.upper_left();

            for (auto const& subgroup_id : run->getSubGroups(id)) {
                auto sub_rel_offset = offset_to_zero_coords;
                auto subgroup_bbox  = bbox_map.at(subgroup_id);
                run->message(
                    hstd::fmt(
                        "this bbox {} rel offset {}",
                        subgroup_bbox,
                        sub_rel_offset),
                    _fname);

                subgroup_bbox = subgroup_bbox.move(sub_rel_offset);

                run->message(
                    hstd::fmt("after move {}", subgroup_bbox), _fname);

                if (run->getGroup<layout::IGroupVisualAttribute>(
                           subgroup_id)
                        ->hasAlgorithm()) {
                    collect_nodes_and_sub_groups_relative_positions(
                        subgroup_id, sub_rel_offset);
                } else {
                    result.vertices.insert_or_assign(
                        subgroup_id,
                        std::make_shared<cst::ColaGroupLayoutAttribute>(
                            subgroup_bbox,
                            run->getGroup<cst::ColaGroup>(subgroup_id)));
                }
            }

            for (auto const& vert : run->getDirectVertices(id)) {
                auto rect = adapt::to_hstd(*ctx->getRect(vert))
                                .move(offset_to_zero_coords);

                result.vertices.insert_or_assign(
                    vert,
                    std::make_shared<cst::ColaVertexLayoutAttribute>(
                        rect,
                        run->getGraph()->getVertex(vert)->getStableId()));
            }
        }
    }

    void execute_edge_placement(cst::ColaLayoutAlgorithm* algo) {
        auto __scope        = run->scopeLevelMsg(__PRETTY_FUNCTION__);
        algo->router->run   = run;
        algo->router->rects = rootGroup->shared.get();
        algo->router->group = rootGroup.get();
        algo->router->intermediate_placement = &result;
        algo->router->root_group             = root_id;
        auto layoutPorts                     = algo->router->routeEdges();
    }
};


} // namespace

layout::IPlacementAlgorithm::Result hstd::ext::graph::cst::
    ColaLayoutAlgorithm::runSingleLayout(VertexID const& root_id) {
    auto __scope = run->scopeLevelMsg(
        hstd::fmt(
            "running single layout for cst::ColaLayoutAlgorithm {}",
            run->getDebug(root_id)));
    hstd::logic_assertion_check_not_nil(router);

    single_layout_run_state run_state(root_id, run);

    run_state.extend_layout_rectangles_with_sub_groups(
        root_id, std::nullopt);

    run_state.collect_edge_len_override_parameters(this);

    unsatisifed_validation_state validation_state;
    validation_state.run       = run;
    validation_state.rootGroup = run_state.rootGroup;


    run_state.recursively_collect_constraints(root_id, validation_state);

    cola::ConstrainedFDLayout alg2(
        /*rs=*/run_state.layout_rects,
        /*es=*/run_state.edges,
        /*idealLength=*/commonIdealEdgeLength,
        /*eLengths=*/run_state.edgeLenOverride,
        /*doneTest=*/nullptr,
        /*preIteration=*/run_state.locks.empty()
            ? nullptr
            : new cola::PreIteration(run_state.locks));

    run->message(
        hstd::fmt(
            "collected {} constraints, {} edges, {} rects, {} locks for "
            "layout run",
            run_state.ccs.size(),
            run_state.edges.size(),
            run_state.layout_rects.size(),
            run_state.locks.size()));

    for (auto const& r : run_state.layout_rects) {
        run->message(hstd::fmt("r {}", adapt::to_hstd(*r)));
    }

    alg2.setUnsatisfiableConstraintInfo(
        &validation_state.unsatX, &validation_state.unsatY);

    run->message("set constraints");
    alg2.setConstraints(run_state.ccs);
    run->message("avoid overlaps");
    alg2.setAvoidNodeOverlaps(true);
    run->message("make feasible");
    alg2.makeFeasible();
    validation_state.validate_unsatisfied();
    run->message("run main");
    alg2.run();
    validation_state.validate_unsatisfied();

    {
        VisGroup res;
        auto     __scope = run->scopeLevelMsg("rectangle placement");
        for (auto const& id : run->getDirectVertices(root_id).items()) {
            res.add(
                VisGroup::FromRectAndText(
                    adapt::to_hstd(run_state.ctx->getRect(id)),
                    hstd::fmt("VERTEX {}", id)));
        }

        for (auto const& [id, rect] : run_state.sub_group_rectangles) {
            res.add(
                VisGroup::FromRectAndText(
                    adapt::to_hstd(rect), hstd::fmt("GROUP {}", id)));
        }

        run->writeAdjacentToTraceFile(
            hstd::fmt(
                "single_layout_of_{}.svg",
                run->getGraph()->getVertex(root_id)->getStableId()),
            ext::visual::toSvg({res}, true).to_string());
    }

    run_state.collect_absolute_bounding_box_positions(root_id);
    {
        auto __scope = run->scopeLevelMsg("collected bounding box");
        for (auto const& [key, value] : run_state.bbox_map) {
            run->message(hstd::fmt("{} -> {}", key, value));
        }
    }

    run_state.collect_nodes_and_sub_groups_relative_positions(
        root_id, geometry::Point{});

    run_state.execute_edge_placement(this);

    auto root_bbox = run_state.bbox_map.at(root_id);
    auto root_rel  = root_bbox.move(
        geometry::Point{} - root_bbox.upper_left());

    run_state.result.vertices.insert_or_assign(
        root_id,
        std::make_shared<ColaGroupLayoutAttribute>(
            root_rel, run_state.rootGroup));

    return run_state.result;
}

hstd::SPtr<cst::ColaGroup> cst::ColaGroup::newRootGraph(
    hstd::SPtr<layout::LayoutRun> run,
    Str const&                    name) {
    auto result = std::make_shared<ColaGroup>(
        std::make_shared<SharedCtx>(API::SharedCtxBase{
            .run = run,
        }),
        name);

    result->algorithm = std::make_shared<ColaLayoutAlgorithm>(run);
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

    hstd::logic_assertion_check_not_nil(result);
    hstd::logic_assertion_check_not_nil(left_constraint);
    hstd::logic_assertion_check_not_nil(right_constraint);
    return {result, left_constraint, right_constraint};
}


hstd::Vec<hstd::SPtr<cola::CompoundConstraint>> cst::
    FixedRelativeConstraint::getCola() const {
    if (shapes.size() < 2) {
        throw hstd::ext::graph::layout::layout_error::init(
            "Fixed relative constraint must have at least 2 shapes "
            "specified");
    }

    return {std::make_shared<cola::FixedRelativeConstraint>(
        getAllRectanglesSorted(), getRectangleIndices(), fixedPosition)};
}

hstd::Vec<hstd::SPtr<cola::CompoundConstraint>> cst::AlignConstraint::
    getCola() const {
    auto result = std::make_shared<cola::AlignmentConstraint>(
        toVpsc(dimension));

    auto getAxisOffset = [&](VertexID    vertexId,
                             Spec const& spec) -> double {
        auto const& rect = *group->shared->getRect(vertexId);

        switch (spec.align) {
            case AxisAlign::Center: {
                return spec.offset;
            }

            case AxisAlign::Left: {
                if (dimension != GraphDimension::XDIM) {
                    throw layout::layout_error::init(
                        hstd::fmt(
                            "AlignConstraint axis mismatch: vertex {} "
                            "uses Left for {} constraint",
                            vertexId,
                            dimension));
                }
                return spec.offset - rect.width() / 2.0;
            }

            case AxisAlign::Right: {
                if (dimension != GraphDimension::XDIM) {
                    throw layout::layout_error::init(
                        hstd::fmt(
                            "AlignConstraint axis mismatch: vertex {} "
                            "uses Right for {} constraint",
                            vertexId,
                            dimension));
                }
                return spec.offset + rect.width() / 2.0;
            }

            case AxisAlign::Top: {
                if (dimension != GraphDimension::YDIM) {
                    throw layout::layout_error::init(
                        hstd::fmt(
                            "AlignConstraint axis mismatch: vertex {} "
                            "uses Top for {} constraint",
                            vertexId,
                            dimension));
                }
                return spec.offset - rect.height() / 2.0;
            }

            case AxisAlign::Bottom: {
                if (dimension != GraphDimension::YDIM) {
                    throw layout::layout_error::init(
                        hstd::fmt(
                            "AlignConstraint axis mismatch: vertex {} "
                            "uses Bottom for {} constraint",
                            vertexId,
                            dimension));
                }
                return spec.offset + rect.height() / 2.0;
            }
        }

        std::unreachable();
    };

    for (auto const& [vertexId, spec] : vertices) {
        result->addShape(
            getShapeId(vertexId), getAxisOffset(vertexId, spec));
        if (spec.fixPos) { result->fixPos(*spec.fixPos); }
    }

    return {result};
}


std::string hstd::ext::graph::cst::ColaConstraint::getRepr() const {
    std::string head;
    head += hstd::fmt("{} vertices", getAllVertices().size());
    for (auto const& vert : getAllVertices()) {
        head += hstd::fmt(
            "\nvert {} maps to idx {}",
            vert,
            group->shared->getVertexIdx(vert));
    }

    return head;
}

std::vector<vpsc::Rectangle*> hstd::ext::graph::cst::ColaConstraint::
    getRectangles() const {
    return hstd::own_view(getAllVertices())
         | rv::transform([&](VertexID const& id) {
               return group->shared->getRect(id).get();
           })
         | rs::to<std::vector>();
}

std::vector<unsigned> cst::ColaConstraint::getRectangleIndices() const {
    return hstd::own_view(getAllVertices())
         | rv::transform([&](VertexID const& id) -> unsigned {
               return group->shared->getVertexIdx(id);
           })
         | rs::to<std::vector>();
}


hstd::Vec<hstd::SPtr<::cola::CompoundConstraint>> hstd::ext::graph::cst::
    MultiSeparateConstraint::getCola() const {
    Vec<ConstraintPtr> result;

    if (lines.size() < 2) {
        throw hstd::ext::graph::layout::layout_error::init(
            "Multi-separate constraint expects at least two lanes for "
            "alignment");
    }

    for (auto const& [idx, line] : enumerate(lines)) {
        if (line.dimension != this->dimension) {
            throw hstd::ext::graph::layout::layout_error::init(
                hstd::fmt(
                    "multi-aling line {} has dimension {} but the main "
                    "multi-align has dimension {} -- align dimensions "
                    "must match",
                    idx,
                    line.dimension,
                    this->dimension));
        }

        auto align = line.getCola().at(0);
        hstd::logic_assertion_check_not_nil(align);
        result.push_back(align);
    }

    auto sep = std::make_shared<cola::MultiSeparationConstraint>(
        toVpsc(dimension), separationDistance, isExactSeparation);

    LOGIC_ASSERTION_CHECK(sep.get() != nullptr, "");

    for (auto const& [src, dst] : rv::zip(
             rv::iota(0, lines.size() - 1), rv::iota(1, lines.size()))) {
        auto al1 = dynamic_cast<cola::AlignmentConstraint*>(
            result.at(src).get());
        auto al2 = dynamic_cast<cola::AlignmentConstraint*>(
            result.at(dst).get());
        hstd::logic_assertion_check_not_nil(al1);
        hstd::logic_assertion_check_not_nil(al2);

        sep->addAlignmentPair(al1, al2);
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


namespace {
struct DebugPoint {
    hstd::ext::geometry::Point pos;
    int                        rectOrigin;

    double x() const { return pos.x(); }
    double y() const { return pos.y(); }
};

struct DebugOffset {
    hstd::ext::geometry::Point offset;
    DebugPoint                 start;

    bool isEmpty() const {
        return int(offset.x()) == 0 && int(offset.y()) == 0;
    }
};

struct AlignDebugInfo {
    hstd::Vec<DebugOffset>      offsets;
    hstd::Vec<DebugPoint>       centers;
    std::string                 repr;
    cst::AlignConstraint const* orig;

    DebugPoint const& start() const { return centers.front(); }
    DebugPoint const& end() const { return centers.back(); }
};

static std::string writeTwoPoint(
    DebugPoint const& p1,
    DebugPoint const& p2) {
    std::string out;
    if (int(p1.x()) == int(p2.x())) {
        out += hstd::fmt(
            "x:{:.3f} y:{:.3f}-{:.3f}", p1.x(), p1.y(), p2.y());
    } else if (int(p1.y()) == int(p2.y())) {
        out += hstd::fmt(
            "x:{:.3f}-{:.3f} y:{:.3f}", p1.x(), p2.x(), p1.y());
    } else {
        out += hstd::fmt(
            "x:{:.3f}-{:.3f} y:{:.3f}-{:.3f}",
            p1.x(),
            p2.x(),
            p1.y(),
            p2.y());
    }

    if (p1.rectOrigin != p2.rectOrigin) {
        out += hstd::fmt(" <{}><{}>", p1.rectOrigin, p2.rectOrigin);
    } else {
        out += hstd::fmt(" <{}>", p1.rectOrigin);
    }

    return out;
}

static std::string writeOffset(DebugOffset const& o) {
    if (int(o.offset.x()) == 0) {
        return hstd::fmt("{}->+{:.3f}y", o.start.pos, o.offset.y());
    } else if (int(o.offset.y()) == 0) {
        return hstd::fmt("{}->+{:.3f}x", o.start.pos, o.offset.x());
    } else {
        return hstd::fmt("{}->+{}", o.start.pos, o.offset);
    }
}

static std::string getAlignComment(AlignDebugInfo const& a) {
    std::string out;
    out += hstd::fmt("align {} ", a.orig->getAllVertices());
    out += writeTwoPoint(a.start(), a.end());

    hstd::Vec<DebugOffset> non_empty;
    for (auto const& o : a.offsets) {
        if (!o.isEmpty()) { non_empty.push_back(o); }
    }

    if (non_empty.size() == 1) {
        out += " ";
        out += writeOffset(non_empty.front());
    } else {
        for (auto const& o : non_empty) {
            out += "\n  ";
            out += writeOffset(o);
        }
    }

    return out;
}


AlignDebugInfo buildAlign(
    cst::AlignConstraint const&       a,
    hstd::SPtr<cst::ColaGroup> const& group) {
    bool                   x = a.dimension == cst::GraphDimension::XDIM;
    hstd::Vec<DebugPoint>  centers;
    hstd::Vec<DebugOffset> offsets;

    for (auto const& vert : a.getAllVertices()) {
        auto const& spec    = a.vertices.at(vert);
        int         rectIdx = group->shared->getVertexIdx(vert);
        Rect        rect    = group->run->getRelativeBBox(vert);

        geometry::Point axisOffset = x ? geometry::Point(spec.offset, 0)
                                       : geometry::Point(0, spec.offset);

        centers.push_back(
            DebugPoint{
                .pos        = rect.center() - axisOffset,
                .rectOrigin = rectIdx,
            });

        offsets.push_back(DebugOffset{
                .offset = -axisOffset,
                .start =
                    DebugPoint{
                        .pos        = rect.center(),
                        .rectOrigin = rectIdx,
                    },
            });
    }

    hstd::rs::sort(
        centers, [&](DebugPoint const& lhs, DebugPoint const& rhs) {
            return x ? (lhs.y() < rhs.y()) : (lhs.x() < rhs.x());
        });

    return AlignDebugInfo{
        .offsets = offsets,
        .centers = centers,
        .repr    = a.getRepr(),
        .orig    = &a,
    };
};


auto const red_pen          = VisPen{.color = VisColor{.r = 255}};
auto const green_pen        = VisPen{.color = VisColor{.g = 255}};
auto const medium_green_pen = VisPen{.color = VisColor{.g = 127}};
auto const purple_pen       = VisPen{
    .color = VisColor{.r = 128, .g = 0, .b = 128}};

VisGroup getAlignVisualGroup(AlignDebugInfo const& al, VisPen const& pen) {
    auto sub_align = VisGroup{};
    sub_align.custom.addComment(getAlignComment(al));
    auto line = VisElement::FromLine(al.start().pos, al.end().pos, pen);
    sub_align.elements.push_back(std::move(line));

    for (auto const& c : al.centers) {
        auto p = VisElement::FromPoint(c.pos, 2, pen);
        sub_align.elements.push_back(std::move(p));
    }

    for (auto const& c : al.offsets) {
        if (c.offset != c.start.pos) {
            sub_align.elements.push_back(
                VisElement::FromLine(
                    c.start.pos, c.start.pos + c.offset, purple_pen));
        }
    }

    return sub_align;
}

VisGroup getSeparateVisualGroup(
    hstd::SPtr<cst::SeparateConstraint> const& s,
    hstd::SPtr<cst::ColaGroup> const&          group) {
    AlignDebugInfo left  = buildAlign(s->left, group);
    AlignDebugInfo right = buildAlign(s->right, group);

    VisGroup        sub_sep;
    geometry::Point sepOffset //
        = s->dimension == cst::GraphDimension::XDIM
            ? geometry::Point(right.start().x() - left.start().x(), 0)
            : geometry::Point(0, right.start().y() - left.start().y());

    DebugOffset offsetSpec{
        .offset = sepOffset,
        .start  = left.start(),
    };

    sub_sep.subgroups.push_back(getAlignVisualGroup(left, green_pen));
    sub_sep.subgroups.push_back(getAlignVisualGroup(right, green_pen));

    auto const left_x  = std::min(left.start().x(), left.end().x());
    auto const right_x = std::min(right.start().x(), right.end().x());
    auto const left_y  = std::min(left.start().y(), left.end().y());
    auto const right_y = std::min(right.start().y(), right.end().y());

    auto const corner_x = std::min(left_x, right_x);
    auto const corner_y = std::min(left_y, right_y);

    auto horizontal_line = VisElement::FromLine(
        geometry::Point(corner_x, corner_y),
        geometry::Point(std::max(left_x, right_x), corner_y),
        medium_green_pen);

    auto vertical_line = VisElement::FromLine(
        geometry::Point(corner_x, corner_y),
        geometry::Point(corner_x, std::max(left_y, right_y)),
        medium_green_pen);

    if (s->dimension == cst::GraphDimension::XDIM) {
        vertical_line.getLineShape().pen.style = VisPen::LineStyle::Dash;
    } else {
        horizontal_line.getLineShape().pen.style = VisPen::LineStyle::Dash;
    }

    sub_sep.elements.push_back(std::move(horizontal_line));
    sub_sep.elements.push_back(std::move(vertical_line));
    sub_sep.custom.addComment(s->getRepr());

    return sub_sep;
}
} // namespace


hstd::ext::visual::VisGroup hstd::ext::graph::cst::
    ColaGroupLayoutAttribute::getVisual(VertexID const& id) const {
    using namespace visual;
    VisGroup res{};
    res.offset = this->rect.upper_left();

    {
        visual::VisElement::RectShape rect;
        rect.geometry = Rect(
            0, 0, this->rect.width(), this->rect.height());
        rect.pen = visual::VisPen{
            .color = visual::VisColor{128, 128, 128, 255},
            .width = 1.0f,
            .style = visual::VisPen::LineStyle::Dash,
        };
        rect.pen.style = visual::VisPen::LineStyle::Dash;

        visual::VisElement rectElem;
        rectElem.custom.addComment(
            hstd::fmt("graphviz group visual '{}'", group->local.name));
        rectElem.data = rect;
        res.elements.push_back(rectElem);
    }


    res.elements.push_back(
        visual::VisElement::FromText(
            hstd::fmt("GROUP:{}", group->local.name),
            geometry::Point(0, 0)));

    res.custom.setAttr(
        "inkscape:label", hstd::fmt("COLA GROUP:{}", group->local.name));

    for (auto const& c : group->constraints) {
        if (auto align = std::dynamic_pointer_cast<AlignConstraint>(c)) {
            AlignDebugInfo al = buildAlign(*align, group);
            res.subgroups.push_back(getAlignVisualGroup(al, red_pen));
        } else if (
            auto s = std::dynamic_pointer_cast<SeparateConstraint>(c)) {
            res.subgroups.push_back(getSeparateVisualGroup(s, group));
            break;
        }
    }

    return res;
}
