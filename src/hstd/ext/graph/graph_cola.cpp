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
                    return ctx->getEdgeIdx(id, ctx->run);
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

    AvoidRouterAlgorithm router;

    router.run                    = run;
    router.rects                  = rootGroup->shared.get();
    router.group                  = rootGroup.get();
    router.intermediate_placement = &result;
    auto layoutPorts              = router.routeEdges();

    for (auto const& [eid, conn_ref] : router.connections) {
        result.edges.insert_or_assign(
            eid,
            std::make_shared<ColaEdgeLayoutAttribute>(
                adapt::to_hstd_path(conn_ref->displayRoute())));
    }

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

using APL = hstd::ext::graph::cst::AvoidPortLayoutAttribute;

namespace {
std::tuple<float, float, Avoid::ConnDirFlags> get_port_offsets(
    APL::VisibilityDirection portDirection,
    int                      portIdx,
    int                      portListSize,
    hstd::Opt<double>        relative) {
    // Overlapping shape connection pins cause router to
    // arrange the edges incorrectly. Only one of the connected
    // edges ends up being routed, everything else is drawn as
    // a straight line. I could not find a configuration option
    // to addres this, so instead I'm explicitly spreading out
    // the connector offsets. Specific value of 0.02 was chosen
    // to make ports appear "close" together, but ultimately it
    // does not matter if it is something like 0.000001.
    float portNudge //
        = 0.02 * (portIdx - static_cast<float>(portListSize / 2));

    float xOffset = Avoid::ATTACH_POS_CENTRE;
    float yOffset = Avoid::ATTACH_POS_CENTRE;

    Avoid::ConnDirFlags connDir = Avoid::ConnDirNone;

    switch (portDirection) {
        case APL::VisibilityDirection::Top: {
            yOffset = Avoid::ATTACH_POS_TOP;
            if (relative) {
                xOffset = relative.value();
            } else {
                xOffset = Avoid::ATTACH_POS_CENTRE + portNudge;
            }
            connDir = Avoid::ConnDirUp;
            break;
        }

        case APL::VisibilityDirection::Bottom: {
            yOffset = Avoid::ATTACH_POS_BOTTOM;
            if (relative) {
                xOffset = relative.value();
            } else {
                xOffset = Avoid::ATTACH_POS_CENTRE + portNudge;
            }
            connDir = Avoid::ConnDirDown;
            break;
        }

        case APL::VisibilityDirection::Left: {
            if (relative) {
                yOffset = relative.value();
            } else {
                yOffset = Avoid::ATTACH_POS_CENTRE + portNudge;
            }
            xOffset = Avoid::ATTACH_POS_LEFT;
            connDir = Avoid::ConnDirLeft;
            break;
        }

        case APL::VisibilityDirection::Right: {
            if (relative) {
                yOffset = relative.value();
            } else {
                yOffset = Avoid::ATTACH_POS_CENTRE + portNudge;
            }
            xOffset = Avoid::ATTACH_POS_RIGHT;
            connDir = Avoid::ConnDirRight;
            break;
        }
    }

    if (!(0 <= xOffset && xOffset <= 1)
        || !(0 <= yOffset && yOffset <= 1)) {
        throw hstd::logic_assertion_error::init(
            hstd::fmt(
                "xOffset:{} yOffset:{}, port-idx:{}, "
                "port-list-size:{} port-nudge:{} mult:{}",
                xOffset,
                yOffset,
                portIdx,
                portListSize / 2,
                portNudge,
                portIdx - (portListSize / 2)));
    }

    return {xOffset, yOffset, connDir};
}
} // namespace


hstd::ext::graph::cst::AvoidRouterAlgorithm::Result hstd::ext::graph::cst::
    AvoidRouterAlgorithm::routeEdges() {
    hstd::logic_assertion_check_not_nil(rects);
    hstd::logic_assertion_check_not_nil(run);
    hstd::logic_assertion_check_not_nil(group);
    hstd::logic_assertion_check_not_nil(intermediate_placement);

    Result res;
    res.layoutPorts = std::make_shared<AvoidPortCollection>();

    auto lp = res.layoutPorts;

    for (auto const& eid : group->getEdges()) {
        auto edge = run->graph->getEdge(eid);
        hstd::logic_assertion_check_not_nil(edge);
        auto s_pid = lp->addPort(edge->getSource(), eid, true);
        auto e_pid = lp->addPort(edge->getTarget(), eid, false);
        run->message(hstd::fmt("added ports {} {}", s_pid, e_pid));
        auto s_port = lp->getmPort(s_pid);
        auto e_port = lp->getmPort(e_pid);
        hstd::logic_assertion_check_not_nil(s_port);
        hstd::logic_assertion_check_not_nil(e_port);

        auto s_port_attr        = std::make_shared<APL>();
        s_port_attr->visibility = APL::VisibilityDirection::Left;
        s_port_attr->placement  = APL::Placement::Unspecified;
        s_port->addAttribute(s_port_attr);

        auto e_port_attr        = std::make_shared<APL>();
        e_port_attr->visibility = APL::VisibilityDirection::Right;
        e_port_attr->placement  = APL::Placement::Unspecified;
        e_port->addAttribute(s_port_attr);
    }

    for (auto const& vert : group->getVertices()) {
        auto ports = hstd::own_view(lp->getPortsForVertex(vert))
                   | rv::transform([&](PortID pid) -> IPort* {
                         return lp->getmPort(pid);
                     })
                   | rs::to<hstd::Vec>;

        rs::sort(ports, {}, [](IPort* port) {
            return port->getUniqueAttribute<APL>()->visibility;
        });

        for (auto group :
             ports | rv::chunk_by([](IPort* lhs, IPort* rhs) {
                 return lhs->getUniqueAttribute<APL>()->visibility
                     == rhs->getUniqueAttribute<APL>()->visibility;
             })) {
            for (auto const& [idx, port] : enumerate(group)) {
                auto attr = port->getUniqueAttribute<APL>();
                auto [xOffset, yOffset, direction] = get_port_offsets(
                    attr->visibility, idx, group.size(), std::nullopt);
                attr->xOffset   = xOffset;
                attr->yOffset   = yOffset;
                attr->placement = APL::Placement::Proportional;
            }
        }
    }

    router = std::make_shared<Avoid::Router>(Avoid::OrthogonalRouting);
    if (shapeBufferDistance) {
        router->setRoutingParameter(
            Avoid::shapeBufferDistance, shapeBufferDistance.value());
    }


    auto get_shape = [&](VertexID vid) -> Avoid::ShapeRef* {
        if (!shapes.contains(vid)) {
            auto rect = intermediate_placement->vertices.at(vid)
                            ->getBBox();
            Avoid::Rectangle poly = adapt::to_avoid(rect);

            shapes.insert_or_assign(
                vid,
                new Avoid::ShapeRef(router.get(), poly, vid.getValue()));
        }

        return shapes.at(vid);
    };

    auto get_shape_point = [&](VertexID const& id,
                               double          xOffset,
                               double yOffset) -> geometry::Point {
        auto s    = get_shape(id);
        auto bbox = s->polygon().offsetBoundingBox(0);
        return {
            bbox.min.x + bbox.width() * xOffset,
            bbox.min.y + bbox.height() * yOffset,
        };
    };

    for (auto const& eid : group->getEdges()) {
        auto edge = run->graph->getEdge(eid);

        auto s_attr = lp->getPort(edge->getSource())
                          ->getUniqueAttribute<APL>();
        auto t_attr = lp->getPort(edge->getTarget())
                          ->getUniqueAttribute<APL>();

        // connection references are owned abd deleted by the router, no
        // `delete` is necessary to match the `new`.
        auto conn = new Avoid::ConnRef(router.get(), eid.getValue());

        connections.insert_or_assign(eid, conn);

        s_attr->connection = Avoid::ConnEnd{
            adapt::to_avoid(get_shape_point(
                edge->getSource(), s_attr->xOffset, s_attr->yOffset))};

        t_attr->connection = Avoid::ConnEnd{
            adapt::to_avoid(get_shape_point(
                edge->getTarget(), t_attr->xOffset, t_attr->yOffset))};

        conn->setSourceEndpoint(s_attr->connection);
        conn->setDestEndpoint(t_attr->connection);
        conn->setRoutingType(Avoid::ConnType_Orthogonal);
    }

    router->processTransaction();

    for (auto const& eid : group->getEdges()) {
        auto edge   = run->graph->getEdge(eid);
        auto s_attr = lp->getPort(edge->getSource())
                          ->getUniqueAttribute<APL>();
        auto t_attr = lp->getPort(edge->getTarget())
                          ->getUniqueAttribute<APL>();

        auto s_point = get_shape_point(
            edge->getSource(), s_attr->xOffset, s_attr->yOffset);
        auto t_point = get_shape_point(
            edge->getTarget(), t_attr->xOffset, t_attr->yOffset);

        s_attr->xOffset   = s_point.x();
        s_attr->yOffset   = s_point.y();
        s_attr->placement = APL::Placement::Absolute;
        t_attr->xOffset   = t_point.x();
        t_attr->yOffset   = t_point.y();
        t_attr->placement = APL::Placement::Absolute;
    }

    return res;
}
