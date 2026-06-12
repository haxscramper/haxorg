#include "graph_avoid.hpp"

#if ORG_BUILD_WITH_ADAPTAGRAMS

#    include <hstd/stdlib/Ranges.hpp>
#    include <hstd/ext/geometry/hstd_geometry.hpp>
#    include <hstd/ext/geometry/hstd_visual.hpp>

using APL = hstd::ext::graph::cst::AvoidPortLayoutAttribute;
using namespace hstd::ext::graph;
using namespace hstd;
using namespace hstd::ext;

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

    if (!(0 <= xOffset && xOffset <= 1) || !(0 <= yOffset && yOffset <= 1)) {
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

void add_ports(
    layout::LayoutRun*                          run,
    EdgeIDSet const&                            edge_set,
    VertexIDSet const&                          vertex_set,
    hstd::SPtr<cst::AvoidPortCollection> const& lp) {
    auto __ports = run->begin_scope("add ports");
    for (auto const& eid : edge_set) {
        auto s_pid = lp->addPort(run->getGraph()->getSource(eid), eid, true);
        auto e_pid = lp->addPort(run->getGraph()->getTarget(eid), eid, false);
        run->message(hstd::fmt("added ports {} {}", s_pid, e_pid));
        auto s_port = lp->getMPort(s_pid);
        auto e_port = lp->getMPort(e_pid);
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
    __ports.end();

    for (auto const& vert : vertex_set) {
        auto ports = hstd::own_view(lp->getPortsForVertex(vert))
                   | rv::transform(
                         [&](PortID pid) -> IPort* { return lp->getMPort(pid); })
                   | rs::to<hstd::Vec>;

        rs::sort(ports, {}, [](IPort* port) {
            return port->getUniqueAttribute<APL>()->visibility;
        });

        for (auto group : ports | rv::chunk_by([](IPort* lhs, IPort* rhs) {
                              return lhs->getUniqueAttribute<APL>()->visibility
                                  == rhs->getUniqueAttribute<APL>()->visibility;
                          })) {
            for (auto const& [idx, port] : enumerate(group)) {
                auto attr                          = port->getUniqueAttribute<APL>();
                auto [xOffset, yOffset, direction] = get_port_offsets(
                    attr->visibility, idx, group.size(), std::nullopt);
                attr->xOffset   = xOffset;
                attr->yOffset   = yOffset;
                attr->placement = APL::Placement::Proportional;
            }
        }
    }
}


//                       [32       24       16       8
unsigned int EdgeMask = 0b01000000'00000000'00000000'00000000;
unsigned int VertMask = 0b10000000'00000000'00000000'00000000;
unsigned int PortMask = 0b11000000'00000000'00000000'00000000;

template <typename ID>
auto get_id_proxy(ID id, hstd::UnorderedMap<EdgeID::id_base_type, unsigned int>& id_map)
    -> unsigned int {
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


auto get_shape(
    VertexID                                                vid,
    cst::AvoidRouterAlgorithm*                              algo,
    hstd::UnorderedMap<EdgeID::id_base_type, unsigned int>& id_map) -> Avoid::ShapeRef* {
    if (!algo->shapes.contains(vid)) {
        auto             rect = algo->rects.at(vid);
        Avoid::Rectangle poly = adapt::to_avoid(rect);

        algo->shapes.insert_or_assign(
            vid,
            new Avoid::ShapeRef(algo->router.get(), poly, get_id_proxy(vid, id_map)));

        algo->run->message(hstd::fmt("for {} crated rect {}", vid, rect));
    }

    return algo->shapes.at(vid);
};

auto get_shape_point(
    VertexID const&                                         id,
    double                                                  xOffset,
    double                                                  yOffset,
    cst::AvoidRouterAlgorithm*                              algo,
    hstd::UnorderedMap<EdgeID::id_base_type, unsigned int>& id_map) -> geometry::Point {
    auto s    = get_shape(id, algo, id_map);
    auto bbox = s->polygon().offsetBoundingBox(0);
    return {
        bbox.min.x + bbox.width() * xOffset,
        bbox.min.y + bbox.height() * yOffset,
    };
};

void connect_edge_pins(
    cst::AvoidRouterAlgorithm*                              algo,
    hstd::UnorderedMap<EdgeID::id_base_type, unsigned int>& id_map,
    hstd::SPtr<cst::AvoidPortCollection> const&             lp) {

    for (auto const& eid : algo->edge_set) {
        auto eid_avoid = get_id_proxy(eid, id_map);
        algo->run->message(hstd::fmt("for edge ID {} avoid eid {}", eid, eid_avoid));
        auto __scope = algo->run->begin_scope();

        auto source = algo->run->getGraph()->getSource(eid);
        auto target = algo->run->getGraph()->getTarget(eid);

        auto s_pid  = lp->getSourcePort(source, eid);
        auto t_pid  = lp->getTargetPort(target, eid);
        auto s_attr = lp->getPort(s_pid)->getUniqueAttribute<APL>();
        auto t_attr = lp->getPort(t_pid)->getUniqueAttribute<APL>();

        // connection references are owned abd deleted by the router, no
        // `delete` is necessary to match the `new`.
        auto conn = new Avoid::ConnRef(algo->router.get(), eid_avoid);

        algo->connections.insert_or_assign(eid, conn);

        s_attr->pin = new Avoid::ShapeConnectionPin(
            get_shape(source, algo, id_map),
            eid_avoid,
            s_attr->xOffset,
            s_attr->yOffset,
            /*proportional=*/true,
            /*insideOffset=*/0,
            /*visDirs=*/map_direction(s_attr->visibility));

        t_attr->pin = new Avoid::ShapeConnectionPin(
            get_shape(target, algo, id_map),
            eid_avoid,
            t_attr->xOffset,
            t_attr->yOffset,
            /*proportional=*/true,
            /*insideOffset=*/0,
            /*visDirs=*/map_direction(t_attr->visibility));

        s_attr->connection = Avoid::ConnEnd{get_shape(source, algo, id_map), eid_avoid};
        t_attr->connection = Avoid::ConnEnd{get_shape(target, algo, id_map), eid_avoid};

        conn->setSourceEndpoint(s_attr->connection);
        conn->setDestEndpoint(t_attr->connection);
        conn->setRoutingType(Avoid::ConnType_Orthogonal);
    }
}

void write_layout_state(
    cst::AvoidRouterAlgorithm*               algo,
    cst::AvoidRouterAlgorithm::Result const& layout_res,
    hstd::Str const&                         suffix = "") {
    visual::VisGroup res;
    auto             __scope = algo->run->begin_scope("rectangle placement");
    for (auto const& [id, rect] : algo->rects) {
        res.add(
            visual::VisGroup::FromRectAndText(
                rect, algo->run->getGraph()->getVertex(id)->getStableId()));
    }

    for (auto const& [id, edge] : layout_res.edges) { res.add(edge->getVisual(id)); }

    static int write_state = 0;
    algo->run->writeAdjacentToTraceFile(
        hstd::fmt(
            "edge_routing_{}_{}{}.svg", algo->routing_run_name, ++write_state, suffix),
        ext::visual::toSvg({res}, true).to_string());
}

} // namespace


hstd::ext::graph::cst::AvoidRouterAlgorithm::Result hstd::ext::graph::cst::
    AvoidRouterAlgorithm::routeEdges() {
    auto __scope = run->begin_scope("route edges");
    hstd::logic_assertion_check_not_nil(run);

    Result res;
    res.layoutPorts = std::make_shared<AvoidPortCollection>();

    auto lp = res.layoutPorts;

    add_ports(run, edge_set, vertex_set, lp);
    write_layout_state(this, res);

    router = std::make_shared<Avoid::Router>(Avoid::OrthogonalRouting);
    if (shapeBufferDistance) {
        router->setRoutingParameter(
            Avoid::shapeBufferDistance, shapeBufferDistance.value());
    }

    hstd::UnorderedMap<EdgeID::id_base_type, unsigned int> id_map;

    connect_edge_pins(this, id_map, lp);

    router->processTransaction();

    for (auto const& eid : edge_set) {
        auto source = run->getGraph()->getSource(eid);
        auto target = run->getGraph()->getTarget(eid);

        auto s_attr = lp->getPort(lp->getSourcePort(source, eid))
                          ->getUniqueAttribute<APL>();
        auto t_attr = lp->getPort(lp->getTargetPort(target, eid))
                          ->getUniqueAttribute<APL>();

        auto s_point = get_shape_point(
            source, s_attr->xOffset, s_attr->yOffset, this, id_map);
        auto t_point = get_shape_point(
            target, t_attr->xOffset, t_attr->yOffset, this, id_map);

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
        res.edges.insert_or_assign(eid, std::make_shared<AvoidEdgeLayoutAttribute>(path));
    }

    write_layout_state(this, res, "_with_edges");

    return res;
}
#endif
