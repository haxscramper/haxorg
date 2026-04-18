#if false
#    include <adaptagrams/adaptagrams_ir.hpp>
#    include <hstd/stdlib/Ranges.hpp>
#    include <hstd/stdlib/Enumerate.hpp>
#    include <hstd/stdlib/Set.hpp>
#    include <hstd/stdlib/Json.hpp>
#    include <hstd/stdlib/Debug.hpp>

#    include <libcola/output_svg.h>
#    include <libtopology/orthogonal_topology.h>
#    include <libavoid/libavoid.h>
#    include <libdialect/hola.h>
#    include <libdialect/opts.h>
#    include <hstd/stdlib/JsonSerde.hpp>

using namespace hstd;
using namespace hstd::ext;

template <>
struct std::formatter<Avoid::Point> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(Avoid::Point const& p, FormatContext& ctx) const {
        return fmt_ctx(fmt("({:.2f}, {:.2f})", p.x, p.y), ctx);
    }
};

template <>
struct std::formatter<Avoid::Box> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(Avoid::Box const& p, FormatContext& ctx) const {
        return fmt_ctx(
            fmt("[{}+{:.2f}/{:.2f}]", p.min, p.width(), p.height()), ctx);
    }
};

namespace {


char const* original_subgraph_nodes_prop = "original_nodes";
char const* original_subgraph_path_prop  = "original_path";
char const* original_subgraph_index      = "original_index";
char const* source_index_prop            = "source_index";
char const* target_index_prop            = "target_index";






} // namespace


GraphNodeConstraint::Res GraphNodeConstraint::FixedRelative::toCola(

}

bool GraphLayoutIR::Subgraph::isEmpty() const {
    return nodes.empty() && rs::all_of(subgraphs, [](Subgraph const& s) {
               return s.isEmpty();
           });
}

void GraphLayoutIR::validate() {
    for (auto const& e : enumerator(edges)) {
        for (auto const& it :
             Vec<int>{e.value().source, e.value().target}) {
            if (!(it < rectangles.size())) {
                throw std::logic_error(
                    fmt("Edge {} point is out of range for rectangles: "
                        "[{}] out of {} rects",
                        e.index(),
                        it,
                        rectangles.size()));
            }
        }
    }
}

void GraphLayoutIR::ColaResult::writeSvg(Str const& path) {
    auto e //
        = edges | rv::transform([](EdgeData const& e) -> Pair<uint, uint> {
              return std::make_pair(
                  static_cast<uint>(e.edge.source),
                  static_cast<uint>(e.edge.target));
          })
        | rs::to<std::vector>();
    OutputFile output(rectPointers, e, nullptr, path);
    output.rects = true;
    output.generate();
}


GraphLayoutIR::GraphvizResult GraphLayoutIR::doGraphvizLayout(
    Graphviz             gvc,
    Graphviz::LayoutType layout) {

    GraphvizResult result{
        .graph{graphName},
        .graphviz_size_scaling = graphviz_size_scaling,
        .gvc{gvc},
    };


    result.graph.setRankDirection(Graphviz::Graph::RankDirection::LR);

    // Add node to a specified subgraph
    auto add_node = [&](Graphviz::Graph& graph,
                        int              index) -> Graphviz::Node {
        GraphSize const& r    = rectangles.at(index);
        auto             node = graph.node(fmt1(index));
        // default DPI used by graphviz to convert from
        // inches.
        node.setHeight(r.height() / float(graphviz_size_scaling));
        node.setWidth(r.width() / float(graphviz_size_scaling));
        node.setAttr("index", index);
        node.setAttr("fixedsize", true);
        node.setAttr("original_height", r.height());
        node.setAttr("original_width", r.width());
        node.setShape(Graphviz::Node::Shape::rectangle);
        node.setLabel("");
        return node;
    };

    UnorderedSet<int> nodes_in_clusters;

    {
        auto aux = [&](this auto&& self, Subgraph const& sub) -> void {
            for (int node : sub.nodes) { nodes_in_clusters.incl(node); }
            for (auto const& s : sub.subgraphs) { self(s); }
        };

        for (auto const& g : subgraphs) { aux(g); }
    }

    Vec<Opt<Graphviz::Node>> nodes;
    nodes.resize(this->rectangles.size());

    for (auto const& it : enumerator(this->rectangles)) {
        if (!nodes_in_clusters.contains(it.index())) {
            nodes.at(it.index()) = add_node(result.graph, it.index());
        }
    }

    using NodeSet     = UnorderedSet<int>;
    using SubgraphSet = Pair<NodeSet, Graphviz::Graph>;

    // Store mapping subgraph node sets to the newly created subgraphs for
    // label node creation later on. Label node should be in subgraph that
    // is closest to the original source-target nodes. This is done to
    // avoid extraneous edges and labels on the edge of the graph.
    Vec<SubgraphSet> added_subgraphs;
    {
        // Deafult fallback 'sub' graph that contains all nodes, so 'which
        // subgraph' search down the line always succeeds.
        NodeSet allNodes{};
        for (int i : slice(0, rectangles.size() - 1)) { allNodes.incl(i); }
        added_subgraphs.push_back({allNodes, result.graph});
    }

    {
        int subgraph_counter = 0;

        Func<Vec<int>(Graphviz::Graph&, Subgraph const&, CVec<int>)> aux;

        aux = [&](Graphviz::Graph& parent,
                  Subgraph const&  sub,
                  CVec<int>        path) -> Vec<int> {
            auto out_graph = parent.newSubgraph(
                fmt("cluster_{}",
                    sub.graphName.empty() ? Str(fmt1(subgraph_counter))
                                          : sub.graphName));

            if (sub.internalMargin) {
                out_graph.setAttr("margin", sub.internalMargin.value());
            }


            out_graph.setAttr(original_subgraph_index, subgraph_counter);

            ++subgraph_counter;

            out_graph.setAttr(
                original_subgraph_path_prop, to_json_eval(path).dump());
            out_graph.setAttr(
                original_subgraph_nodes_prop,
                to_json_eval(sub.nodes).dump());

            for (int node : sub.nodes) {
                nodes.at(node) = add_node(out_graph, node);
            }

            Vec<int> nodes = sub.nodes;
            for (auto const& s : enumerator(sub.subgraphs)) {
                Vec<int> sub_nodes = aux(
                    out_graph, s.value(), path + Vec<int>{s.index()});
                nodes.append(sub_nodes);
            }

            added_subgraphs.push_back(
                std::make_pair(
                    NodeSet{nodes.begin(), nodes.end()}, out_graph));

            return nodes;
        };

        for (auto const& g : enumerator(subgraphs)) {
            aux(result.graph, g.value(), Vec<int>{g.index()});
        }
    }

    // Get most fitting (smallest size) subgraph that contains all nodes
    // from the expected set.
    auto get_subgraph_containers = [&](NodeSet node) -> Vec<SubgraphSet> {
        Vec<SubgraphSet> result;
        for (auto const& it : added_subgraphs) {
            if (rs::all_of(
                    node, [&](int n) { return it.first.contains(n); })) {
                result.push_back(it);
            }
        }

        rs::sort(
            result, [](SubgraphSet const& lhs, SubgraphSet const& rhs) {
                return lhs.first.size() < rhs.first.size();
            });

        return result;
    };

    for (auto const& e : this->edges) {
        auto init_targets = [&]<typename T>(T& in) {
            in.setAttr(source_index_prop, e.source);
            in.setAttr(target_index_prop, e.target);
        };

        // If there is a label size for an edge, split the line in two
        // parts and insert an intermediate node in between, so large
        // labels will not overlap with the graph structure later on.
        if (edgeLabels.contains(e)) {
            GraphSize const& r = edgeLabels.at(e);

            auto target_graph = //
                get_subgraph_containers({e.source, e.target}).at(0).second;

            // TODO choose which graph/subgraph to add node to based on the
            // subgraphs for source/target, implement this as a
            // `getCommonSubgraph(int n1, int n2)`
            auto node = target_graph.node(
                fmt("{}_{}", e.source, e.target));

            node.setHeight(r.height() / float(graphviz_size_scaling));
            node.setWidth(r.width() / float(graphviz_size_scaling));
            node.setAttr("is_edge_label", true);
            node.setAttr("fixedsize", true);
            init_targets(node);

            node.setShape(Graphviz::Node::Shape::rectangle);
            node.setLabel("");

            // `----<pre_label>----[node]----<post_label>----`

            auto pre_label = target_graph.edge(
                nodes.at(e.source).value(), node);
            init_targets(pre_label);
            pre_label.setAttr("headport", "w"_ss);

            auto post_label = target_graph.edge(
                node, nodes.at(e.target).value());
            init_targets(post_label);
            post_label.setAttr("tailport", "e"_ss);

        } else {
            auto edge = result.graph.edge(
                nodes.at(e.source).value(), nodes.at(e.target).value());
            init_targets(edge);
        }
    }

    gvc.createLayout(result.graph, layout);

    return result;
}

GraphLayoutIR::Result GraphLayoutIR::HolaResult::convert() {
    Result res;
    for (auto const& e : this->edges) {
        GraphPath path;
        for (auto const& p : e.second->getRoutePoints()) {
            path.point(p.x, p.y);
        }
        res.lines[e.first] = Edge{.paths = {path}};
    }

    for (auto const& n : this->nodes) {
        auto b = n->getBoundingBox();
        res.fixed.push_back(GraphRect(b.x, b.y, b.w(), b.h()));
    }

    return res;
}


Vec<SPtr<cola::CompoundConstraint>> GraphLayoutIR::ColaResult::
    setupConstraints(
        Vec<GraphSize> const&           rectangles,
        Vec<GraphNodeConstraint> const& constraints) {
    baseRectangles.reserve(rectangles.size());
    for (auto const& r : rectangles) {
        baseRectangles.push_back(
            vpsc::Rectangle(0, r.width(), 0, r.height()));
    }

    rectPointers                                    //
        = baseRectangles                            //
        | rv::transform([](auto& r) { return &r; }) //
        | rs::to<Vec>();

    return constraints //
         | rv::transform([&](GraphNodeConstraint const& c) {
               return c.toCola(rectPointers);
           })
         | rv::join //
         | rs::to<Vec>();
}

struct PortData {
    uint        pinId;
    float       xOffset;
    float       yOffset;
    Opt<double> checkpoint;
    Opt<double> relativeOffset;

    GraphEdgeConstraint::Port  port;
    Avoid::ShapeConnectionPin* pin = nullptr;
    DESC_FIELDS(
        PortData,
        (pinId, pin, xOffset, yOffset, port, checkpoint, relativeOffset));
};

template <>
struct std::formatter<Avoid::ShapeConnectionPin*>
    : std_format_ptr_as_hex<Avoid::ShapeConnectionPin> {
    template <typename FormatContext>
    auto format(Avoid::ShapeConnectionPin* p, FormatContext& ctx) const {
        if (p == nullptr) {
            return fmt_ctx("nullptr", ctx);
        } else {
            return fmt_ctx(fmt("ids:{}", p->ids()), ctx);
        }
    }
};

struct ShapeTarget {
    int bundle;
    int shape;
    DESC_FIELDS(ShapeTarget, (bundle, shape));
    bool operator==(ShapeTarget const& other) const {
        return bundle == other.bundle && shape == other.shape;
    }
};

template <>
struct std::hash<ShapeTarget> {
    std::size_t operator()(ShapeTarget const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.bundle);
        hax_hash_combine(result, it.shape);
        return result;
    }
};


struct ShapePorts {
    UnorderedMap<
        GraphEdgeConstraint::Port,
        UnorderedMap<ShapeTarget, PortData>>
             ports;
    PortData getPort(
        GraphEdgeConstraint::Port port,
        ShapeTarget               targetShape) const {
        return ports.at(port).at(targetShape);
    }
    DESC_FIELDS(ShapePorts, (ports));
};


namespace {
SPtr<Avoid::Router> init_router() {
    if (true) {
        auto result = std::make_shared<Avoid::Router>(
            Avoid::OrthogonalRouting);

        result->setRoutingParameter((Avoid::RoutingParameter)0, 50);
        result->setRoutingParameter((Avoid::RoutingParameter)1, 0);
        result->setRoutingParameter((Avoid::RoutingParameter)2, 0);
        result->setRoutingParameter((Avoid::RoutingParameter)3, 4000);
        result->setRoutingParameter((Avoid::RoutingParameter)4, 0);
        result->setRoutingParameter((Avoid::RoutingParameter)5, 100);
        result->setRoutingParameter((Avoid::RoutingParameter)6, 0);
        result->setRoutingParameter((Avoid::RoutingParameter)7, 4);
        result->setRoutingOption((Avoid::RoutingOption)0, false);
        result->setRoutingOption((Avoid::RoutingOption)1, true);
        result->setRoutingOption((Avoid::RoutingOption)2, false);
        result->setRoutingOption((Avoid::RoutingOption)3, false);
        return result;
    } else {
        auto result = std::make_shared<Avoid::Router>(
            Avoid::OrthogonalRouting | Avoid::PolyLineRouting);

        result->setRoutingPenalty(
            Avoid::RoutingParameter::segmentPenalty, 50);
        result->setRoutingPenalty(
            Avoid::RoutingParameter::anglePenalty, 0);
        result->setRoutingPenalty(
            Avoid::RoutingParameter::crossingPenalty, 0);
        result->setRoutingPenalty(
            Avoid::RoutingParameter::clusterCrossingPenalty, 4000);
        result->setRoutingPenalty(
            Avoid::RoutingParameter::fixedSharedPathPenalty, 110);

        result->setRoutingOption(
            Avoid::nudgeOrthogonalSegmentsConnectedToShapes, true);
        result->setRoutingOption(
            Avoid::nudgeSharedPathsWithCommonEndPoint, true);
        return result;
    }
}

void add_rectangles(
    cola::RootCluster&         rootCluster,
    GraphLayoutIR::ColaResult& ir,
    Vec<GraphEdge> const&      edges,
    cola::VariableIDMap&       idMap,
    Vec<Avoid::ShapeRef*>&     shapes) {
    uint shapeRefID = edges.size() + ir.baseRectangles.size() + 2;
    for (auto const& it : enumerator(ir.baseRectangles)) {
        ++shapeRefID;
        rootCluster.addChildNode(it.index());
        vpsc::Rectangle const& r    = it.value();
        auto                   poly = Avoid::Polygon{4};
        poly.setPoint(0, Avoid::Point{r.getMinX(), r.getMaxY()});
        poly.setPoint(1, Avoid::Point{r.getMaxX(), r.getMaxY()});
        poly.setPoint(2, Avoid::Point{r.getMaxX(), r.getMinY()});
        poly.setPoint(3, Avoid::Point{r.getMinX(), r.getMinY()});
        auto shape = new Avoid::ShapeRef{
            ir.router.get(), poly, shapeRefID};
        idMap.addMappingForVariable(it.index(), shapeRefID);
        shapes.push_back(shape);
    }
}

auto getPortDirections(GraphLayoutIR* ir, GraphEdge const& edge)
    -> Pair<GraphEdgeConstraint::Port, GraphEdgeConstraint::Port> {
    auto c = ir->edgeConstraints.get(edge);

    return {
        c ? c->sourcePort : GraphEdgeConstraint::Port::Default,
        c ? c->targetPort : GraphEdgeConstraint::Port::Default,
    };
}

std::tuple<float, float, Avoid::ConnDirFlags> get_port_offsets(
    GraphEdgeConstraint::Port portDirection,
    int                       portIdx,
    int                       portListSize,
    Opt<double>               relative) {
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
        case GraphEdgeConstraint::Port::North: {
            yOffset = Avoid::ATTACH_POS_TOP;
            if (relative) {
                xOffset = relative.value();
            } else {
                xOffset = Avoid::ATTACH_POS_CENTRE + portNudge;
            }
            connDir = Avoid::ConnDirUp;
            break;
        }

        case GraphEdgeConstraint::Port::South: {
            yOffset = Avoid::ATTACH_POS_BOTTOM;
            if (relative) {
                xOffset = relative.value();
            } else {
                xOffset = Avoid::ATTACH_POS_CENTRE + portNudge;
            }
            connDir = Avoid::ConnDirDown;
            break;
        }

        case GraphEdgeConstraint::Port::West: {
            if (relative) {
                yOffset = relative.value();
            } else {
                yOffset = Avoid::ATTACH_POS_CENTRE + portNudge;
            }
            xOffset = Avoid::ATTACH_POS_LEFT;
            connDir = Avoid::ConnDirLeft;
            break;
        }

        case GraphEdgeConstraint::Port::East: {
            if (relative) {
                yOffset = relative.value();
            } else {
                yOffset = Avoid::ATTACH_POS_CENTRE + portNudge;
            }
            xOffset = Avoid::ATTACH_POS_RIGHT;
            connDir = Avoid::ConnDirRight;
            break;
        }

        case GraphEdgeConstraint::Port::Center: {
            yOffset = Avoid::ATTACH_POS_CENTRE + portNudge;
            xOffset = Avoid::ATTACH_POS_CENTRE;
            connDir = Avoid::ConnDirNone;
            break;
        }

        case GraphEdgeConstraint::Port::Default: {
            break;
        }
    }

    if (!(0 <= xOffset && xOffset <= 1)
        || !(0 <= yOffset && yOffset <= 1)) {
        throw logic_assertion_error::init(
            fmt("xOffset:{} yOffset:{}, port-idx:{}, "
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

UnorderedMap<int, ShapePorts> init_shape_ports(
    GraphLayoutIR*               ir,
    Vec<GraphEdge> const&        edges,
    Vec<Avoid::ShapeRef*> const& shapes) {
    UnorderedMap<int, ShapePorts> shapePorts;

    uint connectionPinClassID = 1;
    for (auto const& edge : edges) {
        uint sourceClass              = ++connectionPinClassID;
        uint targetClass              = ++connectionPinClassID;
        auto [sourcePort, targetPort] = getPortDirections(ir, edge);

        auto c = ir->edgeConstraints.get(edge);

        shapePorts[edge.source].ports[sourcePort][ShapeTarget{
            .shape  = edge.target,
            .bundle = edge.bundle,
        }] = PortData{
            .pinId          = sourceClass,
            .port           = sourcePort,
            .checkpoint     = c ? c->sourceCheckpoint : Opt<double>{},
            .relativeOffset = c ? c->sourceOffset : Opt<double>{},
        };

        shapePorts[edge.target].ports[targetPort][ShapeTarget{
            .shape  = edge.source,
            .bundle = edge.bundle,
        }] = PortData{
            .pinId          = targetClass,
            .port           = targetPort,
            .checkpoint     = c ? c->targetCheckpoint : Opt<double>{},
            .relativeOffset = c ? c->targetOffset : Opt<double>{},
        };
    }

    for (auto& [sourceShape, shape] : shapePorts) {
        for (auto& [portDirection, portList] : shape.ports) {
            int portIdx = 0;
            for (auto& [targetShape, port] : portList) {
                auto [xOffset, yOffset, connDir] = get_port_offsets(
                    portDirection,
                    portIdx,
                    portList.size(),
                    port.relativeOffset);

                port.xOffset = xOffset;
                port.yOffset = yOffset;
                port.pin     = new Avoid::ShapeConnectionPin{
                    shapes.at(sourceShape),
                    static_cast<uint>(port.pinId),
                    xOffset,
                    yOffset,
                    true,
                    0,
                    connDir,
                };
                ++portIdx;
            }
        }
    }

    return shapePorts;
}

} // namespace

GraphLayoutIR::ColaResult GraphLayoutIR::doColaLayout() {
    validate();
    ColaResult                ir{.baseIr = this};
    cola::CompoundConstraints ccs;

    Vec<SPtr<cola::CompoundConstraint>> constraints = ir.setupConstraints(
        rectangles, this->nodeConstraints);

    for (auto const& c : constraints) { ccs.push_back(c.get()); }

    cola::ConstrainedFDLayout alg2(
        ir.rectPointers,
        edges
            | rv::transform([](auto const& i) -> Pair<unsigned, unsigned> {
                  return std::make_pair<unsigned>(i.source, i.target);
              })
            | rs::to<std::vector>(),
        60);

    alg2.setConstraints(ccs);
    alg2.run();

    ir.router = init_router();

    Vec<Avoid::ShapeRef*> shapes;
    cola::VariableIDMap   idMap;
    cola::RootCluster     rootCluster{};
    add_rectangles(rootCluster, ir, edges, idMap, shapes);

    UnorderedMap<int, ShapePorts> shapePorts = init_shape_ports(
        this, edges, shapes);


    auto edge_checkpoint = [](Avoid::ShapeRef* shape,
                              PortData const&  port) -> Opt<Avoid::Point> {
        if (!port.checkpoint) { return std::nullopt; }
        auto box = shape->routingBox();

        Avoid::Point result{
            box.min.x + box.width() * port.xOffset,
            box.min.y + box.height() * port.yOffset,
        };

        double offset = port.checkpoint.value();

        switch (port.port) {
            case GraphEdgeConstraint::Port::West: {
                result.x -= offset;
                break;
            }
            case GraphEdgeConstraint::Port::East: {
                result.x += offset;
                break;
            }
            case GraphEdgeConstraint::Port::North: {
                result.y -= offset;
                break;
            }
            case GraphEdgeConstraint::Port::South: {
                result.y += offset;
                break;
            }
            case GraphEdgeConstraint::Port::Center:
            case GraphEdgeConstraint::Port::Default: {
                return std::nullopt;
            }
        }

        return result;
    };

    uint connectionID = edges.size() + 1;
    for (auto const& edge : edges) {
        auto [sourceDirection, targetDirection] = getPortDirections(
            this, edge);

        PortData sourcePort //
            = shapePorts.at(edge.source)
                  .getPort(
                      sourceDirection,
                      ShapeTarget{
                          .shape  = edge.target,
                          .bundle = edge.bundle,
                      });

        PortData targetPort //
            = shapePorts.at(edge.target)
                  .getPort(
                      targetDirection,
                      ShapeTarget{
                          .shape  = edge.source,
                          .bundle = edge.bundle,
                      });

        Avoid::ConnEnd sourceEnd{shapes.at(edge.source), sourcePort.pinId};
        Avoid::ConnEnd targetEnd{shapes.at(edge.target), targetPort.pinId};

        auto conn = new Avoid::ConnRef{
            ir.router.get(),
            sourceEnd,
            targetEnd,
            ++connectionID,
        };


        std::vector<Avoid::Checkpoint> checkpoints;

        if (auto srcCheckpoint = edge_checkpoint(
                shapes.at(edge.source), sourcePort);
            srcCheckpoint) {
            checkpoints.push_back(srcCheckpoint.value());
        }

        if (auto dstCheckpoint = edge_checkpoint(
                shapes.at(edge.target), targetPort);
            dstCheckpoint) {
            checkpoints.push_back(dstCheckpoint.value());
        }

        if (!checkpoints.empty()) {
            conn->setRoutingCheckpoints(checkpoints);
        }

        conn->setRoutingType(Avoid::ConnType::ConnType_Orthogonal);


        ColaResult::EdgeData route{
            .edge       = edge,
            .connection = conn,
        };

        ir.edges.push_back(route);
    }

    topology::AvoidTopologyAddon topologyAddon{
        ir.rectPointers, ccs, &rootCluster, idMap};

    if (!edges.empty()) {
        // ir.router->setRoutingParameter(Avoid::segmentPenalty, 50);
        ir.router->setRoutingOption(
            Avoid::nudgeOrthogonalSegmentsConnectedToShapes, true);
        ir.router->processTransaction();
    }

    return ir;
}


GraphLayoutIR::Result GraphLayoutIR::GraphvizResult::convert() {
    Result res;
    res.bbox = getGraphBBox(graph);
    LOGIC_ASSERTION_CHECK(res.bbox.size() != GraphSize(0, 0), "");



    auto set_graph = [&](this auto&&            self,
                         Result::Subgraph&      out_parent,
                         Graphviz::Graph const& in_subgraph,
                         Span<int>              path) -> void {
        if (path.empty()) {
            std::string str //
                = in_subgraph.getAttr<Str>(original_subgraph_nodes_prop)
                      .value()
                      .toBase();

            auto original_nodes = from_json_eval<Vec<int>>(
                json::parse(str));
            out_parent.bbox = getSubgraphBBox(in_subgraph, res.bbox);
        } else {
            self(
                out_parent.subgraphs.resize_at(path.front()),
                in_subgraph,
                path[slice(1, 1_B)]);
        }
    };

    Func<void(Graphviz::Graph const&)> rec_subgraph;
    rec_subgraph = [&](Graphviz::Graph const& g) {
        auto original_path = from_json_eval<Vec<int>>(json::parse(
            g.getAttr<Str>(original_subgraph_path_prop).value().toBase()));

        int original_index //
            = g.getAttr<int>(original_subgraph_index).value();

        res.subgraphPaths.resize_at(original_index) = original_path;

        set_graph(
            res.subgraphs.resize_at(original_path.front()),
            g,
            original_path[slice(1, 1_B)]);

        g.eachSubgraph(rec_subgraph);
    };

    graph.eachSubgraph(rec_subgraph);

    return res;
}

GraphLayoutIR::Result GraphLayoutIR::ColaResult::convert() {
    Result res;

    res.fixed            //
        = baseRectangles //
        | rv::transform([](vpsc::Rectangle const& r) {
              return GraphRect(
                  r.getMinX(),               // top left x
                  r.getMinY(),               // top left y
                  r.getMaxX() - r.getMinX(), // width
                  r.getMaxY() - r.getMinY()  // height
              );
          })
        | rs::to<Vec>();

    double x_min = std::numeric_limits<double>::max();
    double x_max = std::numeric_limits<double>::min();
    double y_min = std::numeric_limits<double>::max();
    double y_max = std::numeric_limits<double>::min();

    auto register_point = [&](double x, double y) {
        x_min = std::min(x_min, x);
        x_max = std::max(x_max, x);
        y_min = std::min(y_min, y);
        y_max = std::max(y_max, y);
    };

    res.bbox.height = 0;
    res.bbox.width  = 0;
    for (auto const& rect : res.fixed) {
        register_point(rect.left, rect.top);
        register_point(rect.left + rect.width, rect.top + rect.height);
    }

    for (auto const& edge : edges) {
        Avoid::PolyLine const& route = edge.connection->displayRoute();
        for (auto const& p : route.ps) { register_point(p.x, p.y); }
    }

    res.bbox.left   = x_min - baseIr->leftBBoxMargin;
    res.bbox.top    = y_min - baseIr->topBBoxMargin;
    res.bbox.width  = x_max - x_min
                    + (baseIr->leftBBoxMargin + baseIr->rightBBoxMargin);
    res.bbox.height = y_max - y_min
                    + (baseIr->topBBoxMargin + baseIr->bottomBBoxMargin);
    double x_offset = -res.bbox.left;
    double y_offset = -res.bbox.top;

    for (auto& rect : res.fixed) {
        rect.left += x_offset;
        rect.top += y_offset;
    }

    for (auto const& edge : edges) {
        GraphPath              path;
        Avoid::PolyLine const& route = edge.connection->displayRoute();
        for (auto const& p : route.ps) {
            path.point(p.x + x_offset, p.y + y_offset);
        }
        res.lines[edge.edge] = Edge{.paths = {path}};
    }

    res.bbox.left += x_offset;
    res.bbox.top += y_offset;

    return res;
}


#endif
