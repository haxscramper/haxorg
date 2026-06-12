#if ORG_BUILD_WITH_ELK
#    include "graph_elk.hpp"

#    include <unordered_set>
#    include <hstd/ext/logger.hpp>
#    include <hstd/stdlib/JsonSerde.hpp>
#    include <hstd/ext/bimap_wrap.hpp>
#    include <hstd/stdlib/Ranges.hpp>
#    include <src/hstd/ext/graph/visual/graph_elk.pb.h>
#    include <hstd/ext/geometry/hstd_visual_serde.hpp>
#    include <hstd/ext/geometry/hstd_geometry_serde.hpp>


using namespace hstd;
using namespace hstd::ext;
using namespace hstd::ext::graph;

void elk::validate(elk::GraphElkLayoutData const& graph) {
    std::unordered_set<hstd::Str> node_ids;
    std::unordered_set<hstd::Str> port_ids;
    std::unordered_set<hstd::Str> edge_ids;

    std::function<void(NodeElkLayoutData const&)> collect_node_ids =
        [&](NodeElkLayoutData const& node) {
            if (node.id.empty()) { throw hstd::runtime_error::init("Empty node ID"); }

            if (node_ids.contains(node.id)) {
                throw hstd::runtime_error::init(
                    std::format("Duplicate node id: '{}'", node.id));
            }
            node_ids.insert(node.id);

            for (const auto& port : node.ports) {
                if (port_ids.contains(port.id)) {
                    throw hstd::runtime_error::init(
                        std::format("Duplicate port id: '{}'", node.id));
                }
                port_ids.insert(port.id);
            }

            for (const auto& child : node.children) { collect_node_ids(child); }
        };

    for (const auto& node : graph.children) { collect_node_ids(node); }

    for (const auto& port : graph.ports) {
        if (port_ids.contains(port.id)) {
            throw hstd::runtime_error::init(
                std::format("Duplicate port id: '{}'", port.id));
        }
        port_ids.insert(port.id);
    }

    std::function<void(std::optional<std::vector<ElkEdgeData>> const&)> validate_edges =
        [&](std::optional<std::vector<ElkEdgeData>> const& edges) {
            if (!edges) { return; }

            for (const auto& edge : *edges) {
                if (edge.id.empty()) { throw hstd::runtime_error::init("Empty edge ID"); }
                if (edge_ids.contains(edge.id)) {
                    throw hstd::runtime_error::init(
                        std::format("Duplicate edge id: '{}'", edge.id));
                }
                edge_ids.insert(edge.id);

                if (edge.source && !node_ids.contains(*edge.source)
                    && !port_ids.contains(*edge.source)) {
                    throw hstd::runtime_error::init(
                        std::format(
                            "Edge '{}' references unknown source: '{}'",
                            edge.id,
                            *edge.source));
                }

                if (edge.target && !node_ids.contains(*edge.target)
                    && !port_ids.contains(*edge.target)) {
                    throw hstd::runtime_error::init(
                        std::format(
                            "Edge '{}' references unknown target: '{}'",
                            edge.id,
                            *edge.target));
                }

                if (edge.sourcePort && !port_ids.contains(*edge.sourcePort)) {
                    throw hstd::runtime_error::init(
                        std::format(
                            "Edge '{}' references unknown source port: "
                            "'{}'",
                            edge.id,
                            *edge.sourcePort));
                }

                if (edge.targetPort && !port_ids.contains(*edge.targetPort)) {
                    throw hstd::runtime_error::init(
                        std::format(
                            "Edge '{}' references unknown target port: "
                            "'{}'",
                            edge.id,
                            *edge.targetPort));
                }

                for (const auto& source : edge.sources) {
                    if (!node_ids.contains(source) && !port_ids.contains(source)) {
                        throw hstd::runtime_error::init(
                            std::format(
                                "Edge '{}' references unknown source: "
                                "'{}'",
                                edge.id,
                                source));
                    }
                }

                for (const auto& target : edge.targets) {
                    if (!node_ids.contains(target) && !port_ids.contains(target)) {
                        throw hstd::runtime_error::init(
                            std::format(
                                "Edge '{}' references unknown target: "
                                "'{}'",
                                edge.id,
                                target));
                    }
                }
            }
        };

    validate_edges(graph.edges);

    std::function<void(NodeElkLayoutData const&)> validate_node_edges =
        [&](NodeElkLayoutData const& node) {
            validate_edges(node.edges);
            for (const auto& child : node.children) { validate_node_edges(child); }
        };

    for (const auto& node : graph.children) { validate_node_edges(node); }
}


std::string elk::ElkLayoutAlgorithm::Manager::layoutDiagram(
    std::string const& graphJson) {
    LOGIC_ASSERTION_CHECK(
        elkEngine->isInitialized(),
        "Initialization failed earlier, cannot execute layout");

    return elkEngine->performLayout(graphJson);
}

elk::GraphElkLayoutData elk::ElkLayoutAlgorithm::Manager::layoutDiagram(
    elk::GraphElkLayoutData const&       graph,
    hstd::SPtr<layout::LayoutRun> const& run) {
    json       serial  = hstd::to_json_eval(graph);
    static int counter = 0;
    run->writeAdjacentToTraceFile(
        hstd::fmt("pre_validate_dump_{}.json", counter), serial.dump(2));
    elk::validate(graph);
    std::string tmp    = serial.dump();
    auto        layout = layoutDiagram(tmp);
    auto        parsed = json::parse(layout);
    run->writeAdjacentToTraceFile(
        hstd::fmt("post_layout_dump_{}.json", counter), parsed.dump(2));
    return hstd::from_json_eval<elk::GraphElkLayoutData>(parsed);
}

namespace {

struct State {
    hstd::SPtr<layout::LayoutRun>                      run;
    hstd::ext::Unordered1to1Bimap<hstd::Str, VertexID> v_id_map;
    hstd::ext::Unordered1to1Bimap<hstd::Str, EdgeID>   e_id_map;
    hstd::ext::Unordered1to1Bimap<hstd::Str, PortID>   p_id_map;
    layout::LayoutRun::EdgeIteration                   iter;

    State(hstd::SPtr<layout::LayoutRun> const& run) : run{run}, iter{run.get()} {}

    PortID get_port_id(hstd::Str const& id) const { return p_id_map.at_right(id); }

    VertexID get_vertex_id(hstd::Str const& id) const { return v_id_map.at_right(id); }

    EdgeID get_edge_id(hstd::Str const& id) const { return e_id_map.at_right(id); }

    PortIDSet get_ports(VertexID const& vert) const {
        return run->getPorts()->getPortsForVertex(vert);
    }

    /// \brief return the ID of the entry the edge will connect to: port or
    /// vertex directly.
    hstd::Str get_connecting_id(VertexID const& v, EdgeID const& e, bool is_start) {
        if (run->getPorts()->hasPortConnection(v, e, is_start)) {
            return get_id(run->getPorts()->getPortForConnection(v, e, is_start));
        } else {
            return get_id(v);
        }
    }

    hstd::Str get_id(PortID const& id) {
        if (!p_id_map.contains_right(id)) {
            auto id_text = run->getGraph()->getPort(id)->getStableId();
            p_id_map.add_unique(id_text, id);
        }
        return p_id_map.at_left(id);
    }

    hstd::Str get_id(VertexID const& id) {
        if (!v_id_map.contains_right(id)) {
            auto id_text = run->getGraph()->getVertex(id)->getStableId();
            v_id_map.add_unique(id_text, id);
        }
        return v_id_map.at_left(id);
    }

    hstd::Str get_id(EdgeID const& id) {
        if (!e_id_map.contains_right(id)) {
            auto id_text = run->getGraph()->getEdge(id)->getStableId();
            e_id_map.add_unique(id_text, id);
        }
        return e_id_map.at_left(id);
    }
};

elk::ElkEdgeData gen_edge_structure(
    hstd::SPtr<layout::LayoutRun> const& run,
    EdgeID const&                        edge,
    State&                               id_map) {
    auto res    = *run->getEdgeVisualAttribute<elk::ElkEdgeVisualAttribute>(edge);
    res.id      = id_map.get_id(edge);
    res.sources = {
        id_map.get_connecting_id(run->getGraph()->getSource(edge), edge, true)};
    res.targets = {
        id_map.get_connecting_id(run->getGraph()->getTarget(edge), edge, false)};
    run->message(hstd::fmt("add edge {}", run->getDebug(edge)));
    return res;
}

elk::ElkPortData gen_port_structure(
    hstd::SPtr<layout::LayoutRun> const& run,
    PortID const&                        port,
    State&                               id_map) {
    auto res = *run->getPortVisualAttribute<elk::ElkPortVisualAttribute>(port);
    res.id   = id_map.get_id(port);
    run->message(hstd::fmt("add port {}", run->getDebug(port)));
    return res;
}

elk::NodeElkLayoutData gen_node_structure(
    hstd::SPtr<layout::LayoutRun> const& run,
    State&                               id_map,
    VertexID const&                      id,
    hstd::Opt<VertexID> const&           parent);

elk::NodeElkLayoutData gen_subgroup_node_structure(
    hstd::SPtr<layout::LayoutRun> const& run,
    State&                               id_map,
    VertexID const&                      id,
    hstd::Opt<VertexID> const&           parent) {
    auto __scope  = run->begin_scope(hstd::fmt("node structure for {}", id));
    auto group    = run->getGroup(id);
    auto gv_group = hstd::validated_dynamic_cast<elk::ElkGroupVisualAttribute>(group);
    LOGIC_ASSERTION_CHECK(
        gv_group != nullptr,
        "Nested subgroup without layout algorithm must be an "
        "instance of gv::GroupVisual");

    elk::NodeElkLayoutData res;
    res.id = id_map.get_id(id);
    for (auto const& sub : run->getSubGroups(id)) {
        res.children.push_back(gen_node_structure(run, id_map, sub, id));
    }

    for (auto const& node : run->getDirectVertices(id)) {
        res.children.push_back(gen_node_structure(run, id_map, node, id));
    }

    for (auto const& edge : id_map.iter.getEdgesForGroup(id)) {
        res.edges.push_back(gen_edge_structure(run, edge, id_map));
    }

    return res;
}

elk::NodeElkLayoutData gen_node_structure(
    hstd::SPtr<layout::LayoutRun> const& run,
    State&                               id_map,
    VertexID const&                      id,
    hstd::Opt<VertexID> const&           parent) {
    elk::NodeElkLayoutData res;
    if (run->isGroupVertex(id)) {
        auto group = run->getGroup(id);

        if (group->hasAlgorithm()) {
            run->message(
                hstd::fmt("group '{}' has layout algorithm set", group->getStableId()));
            auto recursiveBBox = run->getLayout(id)->getBBox();


            res.id = id_map.get_id(id);
            res.setSize(recursiveBBox.width(), recursiveBBox.height());
        } else {
            res = gen_subgroup_node_structure(run, id_map, id, parent);
        }
    } else {
        res    = *run->getVertexVisualAttribute<elk::ElkNodeVisualAttribute>(id);
        res.id = id_map.get_id(id);
    }

    for (auto const& port : id_map.get_ports(id)) {
        res.ports.push_back(gen_port_structure(run, port, id_map));
    }

    return res;
};
} // namespace

hstd::ext::graph::layout::IPlacementAlgorithm::Result hstd::ext::graph::elk::
    ElkLayoutAlgorithm::runSingleLayout(VertexID const& root_id) {
    GraphElkLayoutData full_graph;
    full_graph.x             = this->x;
    full_graph.y             = this->y;
    full_graph.width         = this->width;
    full_graph.height        = this->height;
    full_graph.layoutOptions = this->layoutOptions;

    State id_map{run};

    {
        run->message("collecting nodes for the ELK layout");
        auto sub_group = gen_subgroup_node_structure(run, id_map, root_id, std::nullopt);
        full_graph.edges    = sub_group.edges;
        full_graph.children = sub_group.children;
        id_map.iter.validateLeftoverEdges();
    }

    Result res;

    GraphElkLayoutData post_layout = manager->layoutDiagram(full_graph, run);

    auto aux_edge = [&](ElkEdgeData const& node) {
        EdgeID id = id_map.get_edge_id(node.id);
        run->message(hstd::fmt("aux edge {}", run->getDebug(id)));
        auto lyt                        = std::make_shared<ElkEdgeLayoutAttribute>();
        static_cast<ElkEdgeData&>(*lyt) = node;
        lyt->validate();
        res.edges.insert_or_assign(id, lyt);
    };

    auto aux_port = [&](ElkPortData const& port) {
        PortID id = id_map.get_port_id(port.id);
        run->message(hstd::fmt("aux port {} using {}", run->getDebug(id), port));
        auto lyt                        = std::make_shared<ElkPortLayoutAttribute>();
        static_cast<ElkPortData&>(*lyt) = port;
        res.ports.insert_or_assign(id, lyt);
    };

    auto aux_node = [&](this auto&& self, NodeElkLayoutData const& node) -> void {
        VertexID id = id_map.get_vertex_id(node.id);

        if (run->isGroupVertex(id)) {
            auto lyt = std::make_shared<ElkGroupLayoutAttribute>();
            static_cast<NodeElkLayoutData&>(*lyt) = node;
            lyt->validate();
            res.vertices.insert_or_assign(id, lyt);

            rs::for_each(node.children, self);
            rs::for_each(node.edges, aux_edge);
            rs::for_each(node.ports, aux_port);
        } else {
            auto lyt = std::make_shared<ElkNodeLayoutAttribute>(run);
            static_cast<NodeElkLayoutData&>(*lyt) = node;
            lyt->validate();
            res.vertices.insert_or_assign(id, lyt);
            rs::for_each(node.ports, aux_port);
        }
    };

    rs::for_each(post_layout.children, aux_node);
    rs::for_each(post_layout.edges, aux_edge);
    rs::for_each(post_layout.ports, aux_port);

    auto lyt    = std::make_shared<ElkGroupLayoutAttribute>();
    lyt->x      = post_layout.x.value_or(0);
    lyt->y      = post_layout.x.value_or(0);
    lyt->width  = post_layout.width.value();
    lyt->height = post_layout.height.value();
    res.vertices.insert_or_assign(root_id, lyt);

    return res;
}

hstd::SPtr<elk::ElkGroupVisualAttribute> hstd::ext::graph::elk::ElkGroupVisualAttribute::
    newRootGraph(hstd::SPtr<layout::LayoutRun> run, hstd::Str const& name) {

    auto result = std::make_shared<elk::ElkGroupVisualAttribute>(
        std::make_shared<elk::ElkGroupVisualAttribute::SharedCtx>(run), name);

    auto algo = std::make_shared<elk::ElkLayoutAlgorithm>(
        run, std::make_shared<ElkLayoutAlgorithm::Manager>());

    algo->layoutOptions.set("org.eclipse.elk.hierarchyHandling", "INCLUDE_CHILDREN");

    result->algorithm = algo;


    return result;
}

hstd::ext::visual::VisGroup hstd::ext::graph::elk::ElkGroupLayoutAttribute::getVisual(
    VertexID const& id) const {
    visual::VisGroup res;

    res.offset = geometry::Point{x.value(), y.value()};

    res.custom.setAttr("inkscape:label", hstd::fmt("ELK GROUP:{}", id));

    {
        visual::VisElement::RectShape rect;
        rect.geometry = Rect(0, 0, width.value(), height.value());
        rect.pen      = visual::VisPen{
            .color = visual::VisColor{128, 128, 128, 255},
            .width = 1.0f,
            .style = visual::VisPen::LineStyle::Dash,
        };

        visual::VisElement rectElem;
        rectElem.data = rect;
        res.elements.push_back(rectElem);
    }

    return res;
}


namespace hstd::serde {

template <>
struct proto_serde<
    hstd::ext::graph::elk::proto::Options,
    hstd::ext::graph::elk::Options> {
    static void write(
        hstd::ext::graph::elk::proto::Options* out,
        hstd::ext::graph::elk::Options const&  in) {
        json_to_value(in.data, out->mutable_data());
    }

    static void read(
        hstd::ext::graph::elk::proto::Options const& in,
        hstd::ext::graph::elk::Options*              out) {
        out->data = value_to_json(in.data());
    }
};

template <>
struct proto_serde<
    hstd::ext::graph::elk::proto::PortProperties,
    hstd::ext::graph::elk::PortProperties> {
    static void write(
        hstd::ext::graph::elk::proto::PortProperties* out,
        hstd::ext::graph::elk::PortProperties const&  in) {
        if (in.port.has_value()) { json_to_value(*in.port, out->mutable_port()); }
        if (in.portConstraints.has_value()) {
            out->set_port_constraints(*in.portConstraints);
        }
        if (in.portAlignment.has_value()) { out->set_port_alignment(*in.portAlignment); }
        if (in.allowNonFlowPortsToSwitchSides.has_value()) {
            out->set_allow_non_flow_ports_to_switch_sides(
                *in.allowNonFlowPortsToSwitchSides);
        }
    }

    static void read(
        hstd::ext::graph::elk::proto::PortProperties const& in,
        hstd::ext::graph::elk::PortProperties*              out) {
        if (in.has_port()) {
            out->port = value_to_json(in.port());
        } else {
            out->port.reset();
        }
        if (in.has_port_constraints()) {
            out->portConstraints = in.port_constraints();
        } else {
            out->portConstraints.reset();
        }
        if (in.has_port_alignment()) {
            out->portAlignment = in.port_alignment();
        } else {
            out->portAlignment.reset();
        }
        if (in.has_allow_non_flow_ports_to_switch_sides()) {
            out->allowNonFlowPortsToSwitchSides = in.allow_non_flow_ports_to_switch_sides();
        } else {
            out->allowNonFlowPortsToSwitchSides.reset();
        }
    }
};

template <>
struct proto_serde<
    hstd::ext::graph::elk::proto::NodeProperties,
    hstd::ext::graph::elk::NodeProperties> {
    static void write(
        hstd::ext::graph::elk::proto::NodeProperties* out,
        hstd::ext::graph::elk::NodeProperties const&  in) {
        if (in.portConstraints.has_value()) {
            out->set_port_constraints(*in.portConstraints);
        }
        if (in.portAlignment.has_value()) { out->set_port_alignment(*in.portAlignment); }
    }

    static void read(
        hstd::ext::graph::elk::proto::NodeProperties const& in,
        hstd::ext::graph::elk::NodeProperties*              out) {
        if (in.has_port_constraints()) {
            out->portConstraints = in.port_constraints();
        } else {
            out->portConstraints.reset();
        }
        if (in.has_port_alignment()) {
            out->portAlignment = in.port_alignment();
        } else {
            out->portAlignment.reset();
        }
    }
};

template <>
struct proto_serde<hstd::ext::graph::elk::proto::Label, hstd::ext::graph::elk::Label> {
    static void write(
        hstd::ext::graph::elk::proto::Label* out,
        hstd::ext::graph::elk::Label const&  in) {
        if (in.id.has_value()) { out->set_id(*in.id); }
        if (in.x.has_value()) { out->set_x(*in.x); }
        if (in.y.has_value()) { out->set_y(*in.y); }
        if (in.width.has_value()) { out->set_width(*in.width); }
        if (in.height.has_value()) { out->set_height(*in.height); }
        if (in.text.has_value()) { out->set_text(*in.text); }

        for (auto const& it : in.labels) { write_serde(out->add_labels(), it); }

        write_serde(out->mutable_layout_options(), in.layoutOptions);
    }

    static void read(
        hstd::ext::graph::elk::proto::Label const& in,
        hstd::ext::graph::elk::Label*              out) {
        if (in.has_id()) {
            out->id = in.id();
        } else {
            out->id.reset();
        }
        if (in.has_x()) {
            out->x = in.x();
        } else {
            out->x.reset();
        }
        if (in.has_y()) {
            out->y = in.y();
        } else {
            out->y.reset();
        }
        if (in.has_width()) {
            out->width = in.width();
        } else {
            out->width.reset();
        }
        if (in.has_height()) {
            out->height = in.height();
        } else {
            out->height.reset();
        }
        if (in.has_text()) {
            out->text = in.text();
        } else {
            out->text.reset();
        }

        out->labels.clear();
        for (auto const& it : in.labels()) {
            hstd::ext::graph::elk::Label value;
            read_serde(it, &value);
            out->labels.push_back(value);
        }

        read_serde(in.layout_options(), &out->layoutOptions);
    }
};

template <>
struct proto_serde<
    hstd::ext::graph::elk::proto::ElkPortData,
    hstd::ext::graph::elk::ElkPortData> {
    static void write(
        hstd::ext::graph::elk::proto::ElkPortData* out,
        hstd::ext::graph::elk::ElkPortData const&  in) {
        out->set_id(in.id);
        if (in.x.has_value()) { out->set_x(*in.x); }
        if (in.y.has_value()) { out->set_y(*in.y); }
        if (in.width.has_value()) { out->set_width(*in.width); }
        if (in.height.has_value()) { out->set_height(*in.height); }

        for (auto const& it : in.labels) { write_serde(out->add_labels(), it); }

        if (in.properties.has_value()) {
            write_serde(out->mutable_properties(), *in.properties);
        }
        write_serde(out->mutable_layout_options(), in.layoutOptions);
    }

    static void read(
        hstd::ext::graph::elk::proto::ElkPortData const& in,
        hstd::ext::graph::elk::ElkPortData*              out) {
        out->id = in.id();
        if (in.has_x()) {
            out->x = in.x();
        } else {
            out->x.reset();
        }
        if (in.has_y()) {
            out->y = in.y();
        } else {
            out->y.reset();
        }
        if (in.has_width()) {
            out->width = in.width();
        } else {
            out->width.reset();
        }
        if (in.has_height()) {
            out->height = in.height();
        } else {
            out->height.reset();
        }

        out->labels.clear();
        for (auto const& it : in.labels()) {
            hstd::ext::graph::elk::Label value;
            read_serde(it, &value);
            out->labels.push_back(value);
        }

        if (in.has_properties()) {
            hstd::ext::graph::elk::PortProperties value;
            read_serde(in.properties(), &value);
            out->properties = value;
        } else {
            out->properties.reset();
        }

        read_serde(in.layout_options(), &out->layoutOptions);
    }
};

template <>
struct proto_serde<
    hstd::ext::graph::elk::proto::EdgeSection,
    hstd::ext::graph::elk::EdgeSection> {
    static void write(
        hstd::ext::graph::elk::proto::EdgeSection* out,
        hstd::ext::graph::elk::EdgeSection const&  in) {
        if (in.id.has_value()) { out->set_id(*in.id); }
        write_serde(out->mutable_start_point(), in.startPoint);
        write_serde(out->mutable_end_point(), in.endPoint);

        for (auto const& it : in.bendPoints) { write_serde(out->add_bend_points(), it); }
        if (in.incomingShape.has_value()) { out->set_incoming_shape(*in.incomingShape); }
        if (in.outgoingShape.has_value()) { out->set_outgoing_shape(*in.outgoingShape); }
        for (auto const& it : in.incomingSections) { out->add_incoming_sections(it); }
        for (auto const& it : in.outgoingSections) { out->add_outgoing_sections(it); }
    }

    static void read(
        hstd::ext::graph::elk::proto::EdgeSection const& in,
        hstd::ext::graph::elk::EdgeSection*              out) {
        if (in.has_id()) {
            out->id = in.id();
        } else {
            out->id.reset();
        }

        read_serde(in.start_point(), &out->startPoint);
        read_serde(in.end_point(), &out->endPoint);

        out->bendPoints.clear();
        for (auto const& it : in.bend_points()) {
            hstd::ext::graph::Point value;
            read_serde(it, &value);
            out->bendPoints.push_back(value);
        }

        if (in.has_incoming_shape()) {
            out->incomingShape = in.incoming_shape();
        } else {
            out->incomingShape.reset();
        }
        if (in.has_outgoing_shape()) {
            out->outgoingShape = in.outgoing_shape();
        } else {
            out->outgoingShape.reset();
        }

        out->incomingSections.clear();
        for (auto const& it : in.incoming_sections()) {
            out->incomingSections.push_back(it);
        }

        out->outgoingSections.clear();
        for (auto const& it : in.outgoing_sections()) {
            out->outgoingSections.push_back(it);
        }
    }
};

template <>
struct proto_serde<
    hstd::ext::graph::elk::proto::ElkEdgeData,
    hstd::ext::graph::elk::ElkEdgeData> {
    static void write(
        hstd::ext::graph::elk::proto::ElkEdgeData* out,
        hstd::ext::graph::elk::ElkEdgeData const&  in) {
        out->set_id(in.id);
        if (in.source.has_value()) { out->set_source(*in.source); }
        if (in.sourcePort.has_value()) { out->set_source_port(*in.sourcePort); }
        if (in.target.has_value()) { out->set_target(*in.target); }
        if (in.targetPort.has_value()) { out->set_target_port(*in.targetPort); }

        for (auto const& it : in.sources) { out->add_sources(it); }
        for (auto const& it : in.targets) { out->add_targets(it); }
        for (auto const& it : in.sections) { write_serde(out->add_sections(), it); }
        for (auto const& it : in.labels) { write_serde(out->add_labels(), it); }
        for (auto const& it : in.junctionPoints) {
            write_serde(out->add_junction_points(), it);
        }

        write_serde(out->mutable_layout_options(), in.layoutOptions);
    }

    static void read(
        hstd::ext::graph::elk::proto::ElkEdgeData const& in,
        hstd::ext::graph::elk::ElkEdgeData*              out) {
        out->id = in.id();
        if (in.has_source()) {
            out->source = in.source();
        } else {
            out->source.reset();
        }
        if (in.has_source_port()) {
            out->sourcePort = in.source_port();
        } else {
            out->sourcePort.reset();
        }
        if (in.has_target()) {
            out->target = in.target();
        } else {
            out->target.reset();
        }
        if (in.has_target_port()) {
            out->targetPort = in.target_port();
        } else {
            out->targetPort.reset();
        }

        out->sources.clear();
        for (auto const& it : in.sources()) { out->sources.push_back(it); }

        out->targets.clear();
        for (auto const& it : in.targets()) { out->targets.push_back(it); }

        out->sections.clear();
        for (auto const& it : in.sections()) {
            hstd::ext::graph::elk::EdgeSection value;
            read_serde(it, &value);
            out->sections.push_back(value);
        }

        out->labels.clear();
        for (auto const& it : in.labels()) {
            hstd::ext::graph::elk::Label value;
            read_serde(it, &value);
            out->labels.push_back(value);
        }

        out->junctionPoints.clear();
        for (auto const& it : in.junction_points()) {
            hstd::ext::graph::Point value;
            read_serde(it, &value);
            out->junctionPoints.push_back(value);
        }

        read_serde(in.layout_options(), &out->layoutOptions);
    }
};

template <>
struct proto_serde<
    hstd::ext::graph::elk::proto::NodeElkLayoutData,
    hstd::ext::graph::elk::NodeElkLayoutData> {
    static void write(
        hstd::ext::graph::elk::proto::NodeElkLayoutData* out,
        hstd::ext::graph::elk::NodeElkLayoutData const&  in) {
        out->set_id(in.id);
        if (in.x.has_value()) { out->set_x(*in.x); }
        if (in.y.has_value()) { out->set_y(*in.y); }
        if (in.width.has_value()) { out->set_width(*in.width); }
        if (in.height.has_value()) { out->set_height(*in.height); }
        if (in.type.has_value()) { out->set_type(*in.type); }

        for (auto const& it : in.ports) { write_serde(out->add_ports(), it); }
        for (auto const& it : in.labels) { write_serde(out->add_labels(), it); }
        for (auto const& it : in.children) { write_serde(out->add_children(), it); }
        for (auto const& it : in.edges) { write_serde(out->add_edges(), it); }

        if (in.properties.has_value()) {
            write_serde(out->mutable_properties(), *in.properties);
        }
        write_serde(out->mutable_layout_options(), in.layoutOptions);
    }

    static void read(
        hstd::ext::graph::elk::proto::NodeElkLayoutData const& in,
        hstd::ext::graph::elk::NodeElkLayoutData*              out) {
        out->id = in.id();
        if (in.has_x()) {
            out->x = in.x();
        } else {
            out->x.reset();
        }
        if (in.has_y()) {
            out->y = in.y();
        } else {
            out->y.reset();
        }
        if (in.has_width()) {
            out->width = in.width();
        } else {
            out->width.reset();
        }
        if (in.has_height()) {
            out->height = in.height();
        } else {
            out->height.reset();
        }
        if (in.has_type()) {
            out->type = in.type();
        } else {
            out->type.reset();
        }

        out->ports.clear();
        for (auto const& it : in.ports()) {
            hstd::ext::graph::elk::ElkPortData value;
            read_serde(it, &value);
            out->ports.push_back(value);
        }

        out->labels.clear();
        for (auto const& it : in.labels()) {
            hstd::ext::graph::elk::Label value;
            read_serde(it, &value);
            out->labels.push_back(value);
        }

        out->children.clear();
        for (auto const& it : in.children()) {
            hstd::ext::graph::elk::NodeElkLayoutData value;
            read_serde(it, &value);
            out->children.push_back(value);
        }

        out->edges.clear();
        for (auto const& it : in.edges()) {
            hstd::ext::graph::elk::ElkEdgeData value;
            read_serde(it, &value);
            out->edges.push_back(value);
        }

        if (in.has_properties()) {
            hstd::ext::graph::elk::NodeProperties value;
            read_serde(in.properties(), &value);
            out->properties = value;
        } else {
            out->properties.reset();
        }

        read_serde(in.layout_options(), &out->layoutOptions);
    }
};

template <>
struct proto_serde<
    hstd::ext::graph::elk::proto::GraphElkLayoutData,
    hstd::ext::graph::elk::GraphElkLayoutData> {
    static void write(
        hstd::ext::graph::elk::proto::GraphElkLayoutData* out,
        hstd::ext::graph::elk::GraphElkLayoutData const&  in) {
        out->set_id(in.id);
        if (in.x.has_value()) { out->set_x(*in.x); }
        if (in.y.has_value()) { out->set_y(*in.y); }
        if (in.width.has_value()) { out->set_width(*in.width); }
        if (in.height.has_value()) { out->set_height(*in.height); }

        write_serde(out->mutable_layout_options(), in.layoutOptions);
        for (auto const& it : in.children) { write_serde(out->add_children(), it); }
        for (auto const& it : in.edges) { write_serde(out->add_edges(), it); }
        for (auto const& it : in.ports) { write_serde(out->add_ports(), it); }
        for (auto const& it : in.labels) { write_serde(out->add_labels(), it); }
    }

    static void read(
        hstd::ext::graph::elk::proto::GraphElkLayoutData const& in,
        hstd::ext::graph::elk::GraphElkLayoutData*              out) {
        out->id = in.id();
        if (in.has_x()) {
            out->x = in.x();
        } else {
            out->x.reset();
        }
        if (in.has_y()) {
            out->y = in.y();
        } else {
            out->y.reset();
        }
        if (in.has_width()) {
            out->width = in.width();
        } else {
            out->width.reset();
        }
        if (in.has_height()) {
            out->height = in.height();
        } else {
            out->height.reset();
        }

        read_serde(in.layout_options(), &out->layoutOptions);

        out->children.clear();
        for (auto const& it : in.children()) {
            hstd::ext::graph::elk::NodeElkLayoutData value;
            read_serde(it, &value);
            out->children.push_back(value);
        }

        out->edges.clear();
        for (auto const& it : in.edges()) {
            hstd::ext::graph::elk::ElkEdgeData value;
            read_serde(it, &value);
            out->edges.push_back(value);
        }

        out->ports.clear();
        for (auto const& it : in.ports()) {
            hstd::ext::graph::elk::ElkPortData value;
            read_serde(it, &value);
            out->ports.push_back(value);
        }

        out->labels.clear();
        for (auto const& it : in.labels()) {
            hstd::ext::graph::elk::Label value;
            read_serde(it, &value);
            out->labels.push_back(value);
        }
    }
};

} // namespace hstd::serde


namespace hstd::ext::graph::elk {
namespace {

template <typename Payload>
Payload unpack_attr_payload(::hstd::ext::graph::proto::IAttribute const* in) {
    Payload payload;
    if (!in->payload().UnpackTo(&payload)) {
        throw std::logic_error("Failed to unpack attribute payload");
    }
    return payload;
}

} // namespace

#    if ORG_BUILD_WITH_PROTOBUF
void ElkPortVisualAttribute::writeSerial(
    ::hstd::ext::graph::proto::IAttribute* out,
    IGraph const*) const {
    hstd::ext::graph::elk::proto::ElkPortVisualAttributePayload load;
    load.mutable_base();
    hstd::serde::write_serde(load.mutable_data(), static_cast<ElkPortData const&>(*this));
    out->mutable_payload()->PackFrom(load);
}

void ElkPortVisualAttribute::readSerial(
    ::hstd::ext::graph::proto::IAttribute const* in,
    IGraph const*,
    IGraphSerialReaderFactory*,
    IAttributeObject const*) {
    auto load = unpack_attr_payload<
        hstd::ext::graph::elk::proto::ElkPortVisualAttributePayload>(in);
    hstd::serde::read_serde(load.data(), static_cast<ElkPortData*>(this));
}

void ElkPortLayoutAttribute::writeSerial(
    ::hstd::ext::graph::proto::IAttribute* out,
    IGraph const*) const {
    hstd::ext::graph::elk::proto::ElkPortLayoutAttributePayload load;
    hstd::serde::write_serde(load.mutable_base()->mutable_bbox(), getBBox());
    hstd::serde::write_serde(
        load.mutable_base()->mutable_group(), getVisual(PortID::Nil()));
    hstd::serde::write_serde(load.mutable_data(), static_cast<ElkPortData const&>(*this));
    out->mutable_payload()->PackFrom(load);
}

void ElkPortLayoutAttribute::readSerial(
    ::hstd::ext::graph::proto::IAttribute const* in,
    IGraph const*,
    IGraphSerialReaderFactory*,
    IAttributeObject const*) {
    auto load = unpack_attr_payload<
        hstd::ext::graph::elk::proto::ElkPortLayoutAttributePayload>(in);
    hstd::serde::read_serde(load.data(), static_cast<ElkPortData*>(this));
}

void ElkEdgeVisualAttribute::writeSerial(
    ::hstd::ext::graph::proto::IAttribute* out,
    IGraph const*) const {
    hstd::ext::graph::elk::proto::ElkEdgeVisualAttributePayload load;
    load.mutable_base();
    hstd::serde::write_serde(load.mutable_data(), static_cast<ElkEdgeData const&>(*this));
    out->mutable_payload()->PackFrom(load);
}

void ElkEdgeVisualAttribute::readSerial(
    ::hstd::ext::graph::proto::IAttribute const* in,
    IGraph const*,
    IGraphSerialReaderFactory*,
    IAttributeObject const*) {
    auto load = unpack_attr_payload<
        hstd::ext::graph::elk::proto::ElkEdgeVisualAttributePayload>(in);
    hstd::serde::read_serde(load.data(), static_cast<ElkEdgeData*>(this));
}

void ElkEdgeLayoutAttribute::writeSerial(
    ::hstd::ext::graph::proto::IAttribute* out,
    IGraph const*) const {
    hstd::ext::graph::elk::proto::ElkEdgeLayoutAttributePayload load;
    hstd::serde::write_serde(
        load.mutable_base()->mutable_group(), getVisual(EdgeID::Nil()));
    hstd::serde::write_serde(load.mutable_base()->mutable_path(), getPath());
    hstd::serde::write_serde(load.mutable_data(), static_cast<ElkEdgeData const&>(*this));
    out->mutable_payload()->PackFrom(load);
}

void ElkEdgeLayoutAttribute::readSerial(
    ::hstd::ext::graph::proto::IAttribute const* in,
    IGraph const*,
    IGraphSerialReaderFactory*,
    IAttributeObject const*) {
    auto load = unpack_attr_payload<
        hstd::ext::graph::elk::proto::ElkEdgeLayoutAttributePayload>(in);
    hstd::serde::read_serde(load.data(), static_cast<ElkEdgeData*>(this));
}

void ElkNodeVisualAttribute::writeSerial(
    ::hstd::ext::graph::proto::IAttribute* out,
    IGraph const*) const {
    hstd::ext::graph::elk::proto::ElkNodeVisualAttributePayload load;
    load.mutable_base();
    hstd::serde::write_serde(
        load.mutable_data(), static_cast<NodeElkLayoutData const&>(*this));
    out->mutable_payload()->PackFrom(load);
}

void ElkNodeVisualAttribute::readSerial(
    ::hstd::ext::graph::proto::IAttribute const* in,
    IGraph const*,
    IGraphSerialReaderFactory*,
    IAttributeObject const*) {
    auto load = unpack_attr_payload<
        hstd::ext::graph::elk::proto::ElkNodeVisualAttributePayload>(in);
    hstd::serde::read_serde(load.data(), static_cast<NodeElkLayoutData*>(this));
}

void ElkGroupVisualAttribute::writeSerial(
    ::hstd::ext::graph::proto::IAttribute* out,
    IGraph const*) const {
    hstd::ext::graph::elk::proto::ElkGroupVisualAttributePayload load;
    hstd::serde::write_serde(
        load.mutable_data(), static_cast<NodeElkLayoutData const&>(*this));

    hstd::ext::graph::elk::proto::NodeElkLayoutData algorithm;
    hstd::serde::write_serde(&algorithm, static_cast<NodeElkLayoutData const&>(*this));
    load.mutable_base()->mutable_algorithm_payload()->PackFrom(algorithm);

    out->mutable_payload()->PackFrom(load);
}

void ElkGroupVisualAttribute::readSerial(
    ::hstd::ext::graph::proto::IAttribute const* in,
    IGraph const*,
    IGraphSerialReaderFactory*,
    IAttributeObject const*) {
    auto load = unpack_attr_payload<
        hstd::ext::graph::elk::proto::ElkGroupVisualAttributePayload>(in);
    hstd::serde::read_serde(load.data(), static_cast<NodeElkLayoutData*>(this));
}

void ElkNodeLayoutAttribute::writeSerial(
    ::hstd::ext::graph::proto::IAttribute* out,
    IGraph const*) const {
    hstd::ext::graph::elk::proto::ElkNodeLayoutAttributePayload load;
    hstd::serde::write_serde(load.mutable_base()->mutable_bbox(), getBBox());
    hstd::serde::write_serde(
        load.mutable_base()->mutable_group(), getVisual(VertexID::Nil()));
    hstd::serde::write_serde(
        load.mutable_data(), static_cast<NodeElkLayoutData const&>(*this));
    out->mutable_payload()->PackFrom(load);
}

void ElkNodeLayoutAttribute::readSerial(
    ::hstd::ext::graph::proto::IAttribute const* in,
    IGraph const*,
    IGraphSerialReaderFactory*,
    IAttributeObject const*) {
    auto load = unpack_attr_payload<
        hstd::ext::graph::elk::proto::ElkNodeLayoutAttributePayload>(in);
    hstd::serde::read_serde(load.data(), static_cast<NodeElkLayoutData*>(this));
}

void ElkGroupLayoutAttribute::writeSerial(
    ::hstd::ext::graph::proto::IAttribute* out,
    IGraph const*) const {
    hstd::ext::graph::elk::proto::ElkGroupLayoutAttributePayload load;
    hstd::serde::write_serde(load.mutable_base()->mutable_bbox(), getBBox());
    hstd::serde::write_serde(
        load.mutable_base()->mutable_group(), getVisual(VertexID::Nil()));
    hstd::serde::write_serde(
        load.mutable_data(), static_cast<NodeElkLayoutData const&>(*this));
    out->mutable_payload()->PackFrom(load);
}

void ElkGroupLayoutAttribute::readSerial(
    ::hstd::ext::graph::proto::IAttribute const* in,
    IGraph const*,
    IGraphSerialReaderFactory*,
    IAttributeObject const*) {
    auto load = unpack_attr_payload<
        hstd::ext::graph::elk::proto::ElkGroupLayoutAttributePayload>(in);
    hstd::serde::read_serde(load.data(), static_cast<NodeElkLayoutData*>(this));

    geometry::Rect bbox_value;
    hstd::serde::read_serde(load.base().bbox(), &bbox_value);
    bbox = bbox_value;
}

#    endif

} // namespace hstd::ext::graph::elk


#endif
