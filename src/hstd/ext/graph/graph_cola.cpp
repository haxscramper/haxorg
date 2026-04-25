#include "graph_cola.hpp"
#include "hstd/ext/logger.hpp"
#include "hstd/stdlib/Debug.hpp"
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>

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
    hstd::logic_assertion_check_not_nil(router);

    auto rootGroup = std::dynamic_pointer_cast<ColaGroup>(
        run->getGroup(root_id));
    auto ctx = rootGroup->shared;


    hstd::UnorderedMap<layout::GroupID, hstd::SPtr<vpsc::Rectangle>>
        sub_group_rectangles;

    std::vector<vpsc::Rectangle*> vertices = ctx->getAllRectanglesSorted();

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

    for (auto const& [idx, rect] : enumerate(vertices)) {
        run->message(hstd::fmt("rect {}: {}", idx, *rect));
    }

    cola::ConstrainedFDLayout alg2(
        vertices,
        hstd::own_view(rootGroup->edgeAttributes().keys())
            | rv::transform(
                [&](EdgeID const& id) -> Pair<unsigned, unsigned> {
                    return ctx->getEdgeIdx(id, ctx->run);
                })
            | rs::to<std::vector>(),
        60);

    hstd::Vec<hstd::SPtr<cola::CompoundConstraint>> ccs_s;
    std::vector<cola::CompoundConstraint*>          ccs;

    auto aux_constraints = [&](this auto&&            self,
                               layout::GroupID const& id) -> void {
        auto group = run->getGroup(id);
        for (auto const& constraint : group->constraints) {
            auto cola_cs = std::dynamic_pointer_cast<cst::ColaConstraint>(
                constraint);
            hstd::logic_assertion_check_not_nil(cola_cs);
            ccs_s.append(cola_cs->getCola());
            ccs.push_back(ccs_s.back().get());
            run->message(hstd::fmt("constraint {}", cola_cs->getRepr()));
        }

        for (auto const& sub : group->subGroups) { self(sub); }
    };

    aux_constraints(root_id);
    alg2.setConstraints(ccs);
    alg2.setAvoidNodeOverlaps(true);

    cola::UnsatisfiableConstraintInfos*
        unsatX = new cola::UnsatisfiableConstraintInfos();
    cola::UnsatisfiableConstraintInfos*
        unsatY = new cola::UnsatisfiableConstraintInfos();
    alg2.setUnsatisfiableConstraintInfo(unsatX, unsatY);

    alg2.run();

    for (auto info : *unsatX) {
        std::cout << "X-dim unsatisfied: " << info->toString()
                  << std::endl;
    }
    for (auto info : *unsatY) {
        std::cout << "Y-dim unsatisfied: " << info->toString()
                  << std::endl;
    }

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
                auto rect = ctx->getRect(vert);
                run->message(
                    hstd::fmt("vert {} placed at {}", vert, *rect));

                result.vertices.insert_or_assign(
                    vert,
                    std::make_shared<ColaVertexLayoutAttribute>(
                        adapt::to_hstd(*rect)));
            }
        }
    };

    aux_layout(root_id, std::nullopt);

    router->run                    = run;
    router->rects                  = rootGroup->shared.get();
    router->group                  = rootGroup.get();
    router->intermediate_placement = &result;
    auto layoutPorts               = router->routeEdges();


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

    hstd::logic_assertion_check_not_nil(result);
    hstd::logic_assertion_check_not_nil(left_constraint);
    hstd::logic_assertion_check_not_nil(right_constraint);
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
    return hstd::own_view(group->nodeAttributes().keys())
         | rv::transform([&](VertexID const& id) {
               return group->shared->getRect(id).get();
           })
         | rs::to<std::vector>();
}

std::vector<unsigned> cst::ColaConstraint::getRectangleIndices() const {
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
                hstd::fmt(
                    "multi-aling line {} has dimension {} but the main "
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

Avoid::ConnDirFlags map_direction(APL::VisibilityDirection portDirection) {
    switch (portDirection) {
        case APL::VisibilityDirection::Top: return Avoid::ConnDirUp;
        case APL::VisibilityDirection::Bottom: return Avoid::ConnDirDown;
        case APL::VisibilityDirection::Left: return Avoid::ConnDirLeft;
        case APL::VisibilityDirection::Right: return Avoid::ConnDirRight;
    }
}

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
        e_port->addAttribute(e_port_attr);
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

    //                       [32       24       16       8
    unsigned int EdgeMask = 0b01000000'00000000'00000000'00000000;
    unsigned int VertMask = 0b10000000'00000000'00000000'00000000;
    unsigned int PortMask = 0b11000000'00000000'00000000'00000000;
    hstd::UnorderedMap<EdgeID::id_base_type, unsigned int> id_map;

    auto id_proxy = [&]<typename ID>(ID id) -> unsigned int {
        hstd::u64 id_value = id.getValue();
        if (!id_map.contains(id_value)) {
            unsigned int res = id_map.size();
            if constexpr (std::is_same_v<ID, EdgeID>) {
                res |= EdgeMask;
            } else if constexpr (std::is_same_v<ID, VertexID>) {
                res |= VertMask;
            } else if constexpr (std::is_same_v<ID, PortID>) {
                res |= PortMask;
            }

            id_map.insert_or_assign(id_value, res);
        }

        return id_map.at(id_value);
    };

    auto get_shape = [&](VertexID vid) -> Avoid::ShapeRef* {
        if (!shapes.contains(vid)) {
            auto rect = intermediate_placement->vertices.at(vid)
                            ->getBBox();
            Avoid::Rectangle poly = adapt::to_avoid(rect);

            shapes.insert_or_assign(
                vid,
                new Avoid::ShapeRef(router.get(), poly, id_proxy(vid)));

            run->message(hstd::fmt("for {} crated rect {}", vid, rect));
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
        auto eid_avoid = id_proxy(eid);
        run->message(
            hstd::fmt("for edge ID {} avoid eid {}", eid, eid_avoid));
        auto __scope = run->scopeLevel();

        auto edge = run->graph->getEdge(eid);

        auto s_pid  = lp->getSourcePort(edge->getSource(), eid);
        auto t_pid  = lp->getTargetPort(edge->getTarget(), eid);
        auto s_attr = lp->getPort(s_pid)->getUniqueAttribute<APL>();
        auto t_attr = lp->getPort(t_pid)->getUniqueAttribute<APL>();

        // connection references are owned abd deleted by the router, no
        // `delete` is necessary to match the `new`.
        auto conn = new Avoid::ConnRef(router.get(), eid_avoid);

        connections.insert_or_assign(eid, conn);

        s_attr->pin = new Avoid::ShapeConnectionPin(
            get_shape(edge->getSource()),
            eid_avoid,
            s_attr->xOffset,
            s_attr->yOffset,
            /*proportional=*/true,
            /*insideOffset=*/0,
            /*visDirs=*/map_direction(s_attr->visibility));

        t_attr->pin = new Avoid::ShapeConnectionPin(
            get_shape(edge->getTarget()),
            eid_avoid,
            t_attr->xOffset,
            t_attr->yOffset,
            /*proportional=*/true,
            /*insideOffset=*/0,
            /*visDirs=*/map_direction(t_attr->visibility));

        s_attr->connection = Avoid::ConnEnd{
            get_shape(edge->getSource()), eid_avoid};
        t_attr->connection = Avoid::ConnEnd{
            get_shape(edge->getTarget()), eid_avoid};

        conn->setSourceEndpoint(s_attr->connection);
        conn->setDestEndpoint(t_attr->connection);
        conn->setRoutingType(Avoid::ConnType_Orthogonal);
    }

    router->processTransaction();

    for (auto const& eid : group->getEdges()) {
        run->message(hstd::fmt("rebuilding placement"));
        auto edge   = run->graph->getEdge(eid);
        auto s_attr = lp->getPort(
                            lp->getSourcePort(edge->getSource(), eid))
                          ->getUniqueAttribute<APL>();
        auto t_attr = lp->getPort(
                            lp->getTargetPort(edge->getTarget(), eid))
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

    for (auto const& [eid, conn_ref] : connections) {
        auto path = adapt::to_hstd_path(conn_ref->displayRoute());
        run->message(hstd::fmt("eid {} path {} path", eid, path));
        intermediate_placement->edges.insert_or_assign(
            eid, std::make_shared<ColaEdgeLayoutAttribute>(path));
    }

    return res;
}


struct ColaConstraintDebug {
    struct Constraint {
        struct Point {
            hstd::ext::geometry::Point pos;
            int                        rectOrigin;
            DESC_FIELDS(Point, (pos, rectOrigin));
        };

        static void write_2_point(
            hstd::ColStream& os,
            Point const&     p1,
            Point const&     p2) {
            if (int(p1.pos.x()) == int(p2.pos.x())) {
                os << hstd::fmt(
                    "x:{} y:{}-{}", p1.pos.x(), p1.pos.y(), p2.pos.y());
            } else if (int(p1.pos.y()) == int(p2.pos.y())) {
                os << hstd::fmt(
                    "x:{}-{} y:{}", p1.pos.x(), p2.pos.x(), p1.pos.y());
            } else {
                os << hstd::fmt(
                    "x:{}-{} y:{}-{}",
                    p1.pos.x(),
                    p2.pos.x(),
                    p1.pos.y(),
                    p2.pos.y());
            }

            if (p1.rectOrigin != p2.rectOrigin) {
                os << hstd::fmt(" <{}><{}>", p1.rectOrigin, p2.rectOrigin);
            } else {
                os << hstd::fmt(" <{}>", p1.rectOrigin);
            }
        };


        struct Offset {
            hstd::ext::geometry::Point offset;
            Point                      start;
            bool                       isEmpty() const {
                return int(offset.x()) == 0 && int(offset.y()) == 0;
            }
            DESC_FIELDS(Offset, (offset, start));

            void toString(hstd::ColStream& os) const {
                if (int(offset.x()) == 0) {
                    os << hstd::fmt("{}->+{}y", start, offset.y());
                } else if (int(offset.y()) == 0) {
                    os << hstd::fmt("{}->+{}x", start, offset.x());
                } else {
                    os << hstd::fmt("{}->+{}", start, offset);
                }
            };
        };

        struct RectPosition {
            hstd::ext::geometry::Point pos;
            int                        rect;
            DESC_FIELDS(RectPosition, (pos, rect));
        };

        struct Align {
            Point                 start;
            Point                 end;
            hstd::Vec<Offset>     offsets;
            std::vector<unsigned> rects;
            std::string           repr;
            DESC_FIELDS(Align, (start, end, offsets, rects, repr));

            hstd::ColText toString() const {
                hstd::ColStream os;
                toString(os, 0);
                return os.getBuffer();
            }

            void toString(hstd::ColStream& os, int depth) const {
                os.indent(depth * 2);
                os << hstd::fmt("Align {} ", rects);
                write_2_point(os, start, end);
                auto existing_offsets //
                    = offsets
                    | hstd::rv::filter(
                          hstd::get_method_filter(&Offset::isEmpty))
                    | hstd::rs::to<hstd::Vec>();

                if (existing_offsets.size() == 1) {
                    os << " ";
                    existing_offsets.front().toString(os);
                } else {
                    for (auto const& o : existing_offsets) {
                        os << "\n";
                        os.indent(2 * (depth + 1));
                        o.toString(os);
                    }
                }
            };
        };

        struct Separate {
            Align               left;
            Align               right;
            Offset              offset;
            cst::GraphDimension dimension;
            std::string         repr;
            DESC_FIELDS(Separate, (left, right, offset, dimension, repr));
        };

        SUB_VARIANTS(
            Kind,
            Data,
            data,
            getKind,
            Align,
            Separate,
            RectPosition);
        Data data;
        DESC_FIELDS(Constraint, (data));

        void toString(hstd::ColStream& os) const {
            using C = Constraint;
            if (isAlign()) {
                getAlign().toString(os, 0);
            } else if (isSeparate()) {
                auto const& s = getSeparate();
                os << "Sep ";
                s.offset.toString(os);
                os << "\n";
                s.left.toString(os, 1);
                os << "\n";
                s.right.toString(os, 1);
            }
        }

        hstd::ColText toString() const {
            hstd::ColStream os;
            toString(os);
            return os.getBuffer();
        }
    };

    hstd::ColText toString() const {
        hstd::ColStream os;
        toString(os);
        return os.getBuffer();
    }

    void toString(hstd::ColStream& os) const {
        for (auto const& c : constraints) {
            os << "\n";
            c.toString(os);
        }
    }

    hstd::Vec<Constraint> constraints;
    DESC_FIELDS(ColaConstraintDebug, (constraints));
};


hstd::ext::visual::VisGroup hstd::ext::graph::cst::
    ColaGroupLayoutAttribute::getVisual(layout::GroupID const& id) const {
    using C = ColaConstraintDebug::Constraint;
    using namespace visual;
    VisGroup res{};
    auto     add_align_line = [&](cst::AlignConstraint const& a) {
        bool           x = a.dimension == GraphDimension::XDIM;
        Vec<C::Point>  centers;
        Vec<C::Offset> offsets;
        for (auto const& vert : a.getAllVertices()) {
            auto const& spec    = a.vertices.at(vert);
            int         rectIdx = group->shared->getVertexIdx(vert);
            Rect rect = adapt::to_hstd(*group->shared->getRect(vert));
            Point
                offset = (x ? Point(spec.offset, 0) : Point(0, spec.offset));
            centers.push_back(C::Point{rect.center() - offset, rectIdx});
            offsets.push_back(
                C::Offset{
                    .offset = -offset,
                    .start  = C::Point{rect.center()},
                });
        }

        rs::sort(centers, [&](C::Point const& lhs, C::Point const& rhs) {
            return x ? (lhs.pos.y() < rhs.pos.y())
                     : (lhs.pos.x() < rhs.pos.x());
        });

        C::Point start = centers.at(0);
        C::Point end   = centers.at(1_B);
        // HSLOG_DEBUG_FMT1(a);
        // HSLOG_DEBUG_FMT1(a.getRectangleIndices());

        return C::Align{
            .start   = start,
            .end     = end,
            .offsets = offsets,
            .rects   = a.getRectangleIndices(),
            .repr    = a.getRepr(),
        };
    };

    hstd::Vec<C> cst_list;
    for (auto const& c : group->constraints) {
        if (auto align = std::dynamic_pointer_cast<AlignConstraint>(c)) {
            cst_list.push_back(C{add_align_line(*align)});
        } else if (
            auto s = std::dynamic_pointer_cast<SeparateConstraint>(c)) {
            auto left  = add_align_line(s->left);
            auto right = add_align_line(s->right);

            Point offset = //
                s->dimension == GraphDimension::XDIM
                    ? Point(right.start.pos.x() - left.start.pos.x(), 0)
                    : Point(0, right.start.pos.y() - left.start.pos.y());

            C::Offset offsetSpec{
                .offset = offset,
                .start  = left.start,
            };

            C::Separate sep{
                .left      = left,
                .right     = right,
                .offset    = offsetSpec,
                .dimension = s->dimension,
                .repr      = s->getRepr(),
            };

            cst_list.push_back(C{sep});
            break;
        }
    }

    auto red_pen   = VisPen{.color = VisColor{.r = 255}};
    auto green_pen = VisPen{.color = VisColor{.g = 255}};
    for (auto const& c : cst_list) {
        auto draw_align_line = [&](C::Align const& al,
                                   VisPen const&   c_pen) {
            auto el = VisElement::FromLine(
                al.start.pos, al.end.pos, c_pen);
            el.comment.push_back(al.repr);
            res.elements.push_back(el);
            res.elements.push_back(
                VisElement::FromPoint(al.start.pos, 2, c_pen));
            res.elements.push_back(
                VisElement::FromPoint(al.end.pos, 2, c_pen));
        };

        switch (c.getKind()) {
            case C::Kind::Align: {
                draw_align_line(c.getAlign(), red_pen);
                break;
            }
            case C::Kind::Separate: {
                auto const& s = c.getSeparate();
                draw_align_line(s.left, green_pen);
                draw_align_line(s.right, green_pen);

                auto const left_x = std::min(
                    s.left.start.pos.x(), s.left.end.pos.x());
                auto const right_x = std::min(
                    s.right.start.pos.x(), s.right.end.pos.x());
                auto const left_y = std::min(
                    s.left.start.pos.y(), s.left.end.pos.y());
                auto const right_y = std::min(
                    s.right.start.pos.y(), s.right.end.pos.y());

                auto const corner_x = std::min(left_x, right_x);
                auto const corner_y = std::min(left_y, right_y);

                auto horizontal_line = VisElement::FromLine(
                    geometry::Point(corner_x, corner_y),
                    geometry::Point(std::max(left_x, right_x), corner_y),
                    green_pen);

                auto vertical_line = VisElement::FromLine(
                    geometry::Point(corner_x, corner_y),
                    geometry::Point(corner_x, std::max(left_y, right_y)),
                    green_pen);

                if (s.dimension == GraphDimension::XDIM) {
                    vertical_line.getLineShape()
                        .pen.style = VisPen::LineStyle::Dash;
                } else {
                    horizontal_line.getLineShape()
                        .pen.style = VisPen::LineStyle::Dash;
                }

                vertical_line.comment.push_back(
                    hstd::fmt(
                        "vertical {}--{}", s.left.rects, s.right.rects));

                res.elements.push_back(horizontal_line);
                res.elements.push_back(vertical_line);
                break;
            }
            default: {
            }
        }
    }


    return res;
}
