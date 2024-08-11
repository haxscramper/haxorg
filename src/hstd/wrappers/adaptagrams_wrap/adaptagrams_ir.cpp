#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <hstd/stdlib/Set.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Debug.hpp>

#include <libcola/output_svg.h>
#include <libavoid/libavoid.h>
#include <libdialect/hola.h>
#include <libdialect/opts.h>

namespace {

vpsc::Dim toVpsc(GraphDimension dim) {
    switch (dim) {
        case GraphDimension::XDIM: return vpsc::Dim::XDIM;
        case GraphDimension::YDIM: return vpsc::Dim::YDIM;
        case GraphDimension::UNSET: return vpsc::Dim::UNSET;
    }
}

const char* original_subgraph_nodes_prop = "original_nodes";
const char* original_subgraph_path_prop  = "original_path";
const char* original_subgraph_index      = "original_index";
const char* source_index_prop            = "source_index";
const char* target_index_prop            = "target_index";

/// \brief Convert grapvhiz coordinate system (y up) to the qt coordinates
/// (y down). `height` is the vertical size of the main graph bounding box.
GraphPoint toGvPoint(pointf p, int height) {
    return GraphPoint(p.x, height - p.y);
}

/// \brief Get bounding gox for the nested subtraph
GraphRect getSubgraphBBox(CR<Graphviz::Graph> g, CR<GraphRect> bbox) {
    boxf      rect = g.info()->bb;
    GraphRect res{};
    res.setBottomLeft(toGvPoint(rect.LL, bbox.height));
    res.setTopRight(toGvPoint(rect.UR, bbox.height));
    return res;
}

GraphRect getGraphBBox(CR<Graphviz::Graph> g) {
    boxf rect = g.info()->bb;

    // +----[UR]
    // |       |
    // [LL]----+

    auto res = GraphRect(0, 0, rect.UR.x, rect.UR.y);
    return res;
}

std::string getEdgePropertiesAsString(
    CR<Graphviz::Graph> graph,
    CR<Graphviz::Edge>  edge) {
    std::stringstream ss;
    Agsym_t*          sym;
    char*             value;

    for (sym = agnxtattr(graph.graph, AGEDGE, NULL); sym;
         sym = agnxtattr(graph.graph, AGEDGE, sym)) {
        value = agxget(edge.edge_, sym);
        if (value) { ss << sym->name << " = " << value << ", "; }
    }
    std::string result = ss.str();
    if (!result.empty()) {
        result.pop_back();
        result.pop_back();
    }
    return result;
}

std::string getGraphPropertiesAsString(CR<Graphviz::Graph> graph) {
    std::stringstream ss;
    Agsym_t*          sym;
    char*             value;

    for (sym = agnxtattr(graph.graph, AGRAPH, NULL); sym;
         sym = agnxtattr(graph.graph, AGRAPH, sym)) {
        value = agget(graph.graph, sym->name);
        if (value) { ss << sym->name << " = " << value << ", "; }
    }
    std::string result = ss.str();
    if (!result.empty()) {
        result.pop_back();
        result.pop_back();
    }
    return result;
}

std::string getNodePropertiesAsString(
    CR<Graphviz::Graph> graph,
    CR<Graphviz::Node>  node) {
    std::stringstream ss;
    Agsym_t*          sym;
    char*             value;

    for (sym = agnxtattr(graph.graph, AGNODE, NULL); sym;
         sym = agnxtattr(graph.graph, AGNODE, sym)) {
        value = agxget(node.node, sym);
        if (value) { ss << sym->name << " = " << value << ", "; }
    }

    std::string result = ss.str();
    if (!result.empty()) {
        result.pop_back();
        result.pop_back();
    }

    return result;
}

GraphRect getNodeRectangle(
    CR<Graphviz::Graph> g,
    CR<Graphviz::Node>  node,
    int                 scaling,
    CR<GraphRect>       bbox) {
    double width  = node.info()->width * scaling;
    double height = node.info()->height * scaling;
    double x      = node.info()->coord.x;
    double y      = bbox.height - node.info()->coord.y;
    int    x1     = std::round(x - width / 2);
    int    y1     = std::round(y - height / 2);
    auto   result = GraphRect(
        std::round(x1),
        std::round(y1),
        std::round(width),
        std::round(height));

    return result;
}

GraphPath getEdgeSpline(
    CR<Graphviz::Edge> edge,
    int                scaling,
    CR<GraphRect>      bbox) {
    GraphPath path;
    splines*  spl = edge.info()->spl;
    path.bezier   = true;
    int height    = bbox.height;
    if ((spl->list != 0) && (spl->list->size % 3 == 1)) {
        bezier bez = spl->list[0];
        if (bez.sflag) {
            path.startPoint = toGvPoint(bez.sp, height);
            path.point(toGvPoint(bez.list[0], height));
        } else {
            path.point(toGvPoint(bez.list[0], height));
        }

        for (int i = 1; i < bez.size; i += 3) {
            path.point(toGvPoint(bez.list[i], height));
            path.point(toGvPoint(bez.list[i + 1], height));
            path.point(toGvPoint(bez.list[i + 2], height));
        }

        if (bez.eflag) { path.point(toGvPoint(bez.ep, height)); }
    }
    return path;
}
} // namespace


GraphConstraint::Res GraphConstraint::FixedRelative::toCola(
    const std::vector<vpsc::Rectangle*>& allRects) const {
    return std::make_shared<cola::FixedRelativeConstraint>(
        allRects,
        nodes //
            | rv::transform([](int i) { return static_cast<unsigned>(i); })
            | rs::to<std::vector>(),
        fixedPosition);
}

bool GraphLayoutIR::Subgraph::isEmpty() const {
    return nodes.empty() && rs::all_of(subgraphs, [](CR<Subgraph> s) {
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

void GraphLayoutIR::ColaResult::writeSvg(CR<Str> path) {
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
        CR<GraphSize> r    = rectangles.at(index);
        auto          node = graph.node(fmt1(index));
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

            added_subgraphs.push_back(std::make_pair(
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

        rs::sort(result, [](CR<SubgraphSet> lhs, CR<SubgraphSet> rhs) {
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
            CR<GraphSize> r = edgeLabels.at(e);

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

GraphLayoutIR::HolaResult GraphLayoutIR::doHolaLayout() {
    HolaResult res;
    res.graph = std::make_shared<dialect::Graph>();

    for (auto const& rect : rectangles) {
        auto node = dialect::Node::allocate();
        node->setDims(rect.width(), rect.height());
        res.graph->addNode(node);
        res.nodes.push_back(node);
    }

    for (auto const& pair : edges) {
        auto edge = dialect::Edge::allocate(
            res.nodes.at(pair.source), res.nodes.at(pair.target));
        res.graph->addEdge(edge);
        res.edges[pair] = edge;
    }

    dialect::HolaOpts opts;
    opts.routingScalar_crossingPenalty = 20;
    dialect::doHOLA(*res.graph, opts);
    return res;
};

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
        const Vec<GraphSize>&       rectangles,
        const Vec<GraphConstraint>& constraints) {
    baseRectangles.reserve(rectangles.size());
    for (auto const& r : rectangles) {
        baseRectangles.push_back(
            vpsc::Rectangle(0, r.width(), 0, r.width()));
    }

    rectPointers                                    //
        = baseRectangles                            //
        | rv::transform([](auto& r) { return &r; }) //
        | rs::to<Vec>();

    return constraints //
         | rv::transform([&](CR<GraphConstraint> c) {
               return c.toCola(rectPointers);
           })
         | rv::join //
         | rs::to<Vec>();
}


GraphLayoutIR::ColaResult GraphLayoutIR::doColaLayout() {
    validate();
    ColaResult                ir;
    cola::CompoundConstraints ccs;

    Vec<SPtr<cola::CompoundConstraint>> constraints = ir.setupConstraints(
        rectangles, this->constraints);

    for (auto const& c : constraints) { ccs.push_back(c.get()); }

    cola::ConstrainedFDLayout alg2(
        ir.rectPointers,
        edges
            | rv::transform([](auto const& i) -> Pair<unsigned, unsigned> {
                  return std::make_pair<unsigned>(i.source, i.target);
              })
            | rs::to<std::vector>(),
        width / 2);

    alg2.setConstraints(ccs);
    // alg2.setAvoidNodeOverlaps(true);
    alg2.run();


    ir.router = std::make_shared<Avoid::Router>(Avoid::OrthogonalRouting);
    ir.router->setRoutingPenalty(
        Avoid::RoutingParameter::segmentPenalty, 50);
    ir.router->setRoutingPenalty(Avoid::RoutingParameter::anglePenalty, 0);
    ir.router->setRoutingPenalty(
        Avoid::RoutingParameter::crossingPenalty, 400);
    ir.router->setRoutingPenalty(
        Avoid::RoutingParameter::clusterCrossingPenalty, 4000);
    ir.router->setRoutingPenalty(
        Avoid::RoutingParameter::fixedSharedPathPenalty, 110);

    // class ID


    Vec<Avoid::ShapeRef*> shapes;

    for (auto const& it : enumerator(ir.baseRectangles)) {
        auto const& r    = it.value();
        auto        poly = Avoid::Polygon{4};
        poly.setPoint(0, Avoid::Point{r.getMinX(), r.getMaxY()});
        poly.setPoint(1, Avoid::Point{r.getMaxX(), r.getMaxY()});
        poly.setPoint(2, Avoid::Point{r.getMaxX(), r.getMinY()});
        poly.setPoint(3, Avoid::Point{r.getMinX(), r.getMinY()});
        shapes.push_back(new Avoid::ShapeRef{ir.router.get(), poly});
    }

    auto pin_for_shape = [](Avoid::ShapeRef* shape, int pinClass) {
        return new Avoid::ShapeConnectionPin{
            shape,
            static_cast<uint>(pinClass),
            Avoid::ATTACH_POS_CENTRE,
            Avoid::ATTACH_POS_CENTRE,
            true,
            0,
            Avoid::ConnDirNone,
        };
    };

    unsigned int connectionPinClassID = 1;
    for (auto const& edge : edges) {
        ++connectionPinClassID;
        pin_for_shape(shapes.at(edge.source), connectionPinClassID);
        pin_for_shape(shapes.at(edge.target), connectionPinClassID);

        Avoid::ConnEnd sourceEnd{
            shapes.at(edge.source), connectionPinClassID};
        Avoid::ConnEnd targetEnd{
            shapes.at(edge.target), connectionPinClassID};
        auto conn = new Avoid::ConnRef{
            ir.router.get(), sourceEnd, targetEnd};
        conn->setRoutingType(Avoid::ConnType::ConnType_Orthogonal);

        ColaResult::EdgeData route{
            .edge       = edge,
            .connection = conn,
        };

        ir.edges.push_back(route);
    }


    ir.router->processTransaction();

    return ir;
}


GraphLayoutIR::Result GraphLayoutIR::GraphvizResult::convert() {
    Result res;
    res.bbox = getGraphBBox(graph);
    CHECK(res.bbox.size() != GraphSize(0, 0));

    // 'each node' iterates over all nodes at once, including ones places
    // in a subgraph
    graph.eachNode([&](CR<Graphviz::Node> node) {
        // 'edge label' nodes do not correspond to any specific rectangle
        // and are instead pushed out to edge properties.
        if (auto prop = node.getAttr<bool>("is_edge_label");
            prop.has_value() && *prop) {
            auto key = GraphEdge{
                .source = node.getAttr<int>(source_index_prop).value(),
                .target = node.getAttr<int>(target_index_prop).value(),
            };

            res.lines[key].labelRect = getNodeRectangle(
                graph, node, graphviz_size_scaling, res.bbox);

        } else {
            // assign to a specific index to match original rectangle.
            res.fixed.resize_at(node.getAttr<int>("index").value()) = getNodeRectangle(
                graph, node, graphviz_size_scaling, res.bbox);
        }
    });

    graph.eachEdge([&](CR<Graphviz::Edge> edge) {
        auto key = GraphEdge{
            .source = edge.getAttr<int>(source_index_prop).value(),
            .target = edge.getAttr<int>(target_index_prop).value(),
        };

        // Push back instead of assignment to collect all pieces of
        // multi-element edges with label nodes.
        res.lines[key].paths.push_back(
            getEdgeSpline(edge, graphviz_size_scaling, res.bbox));
    });

    auto set_graph = [&](this auto&&         self,
                         Result::Subgraph&   out_parent,
                         CR<Graphviz::Graph> in_subgraph,
                         Span<int>           path) -> void {
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

    Func<void(CR<Graphviz::Graph>)> rec_subgraph;
    rec_subgraph = [&](CR<Graphviz::Graph> g) {
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
        | rv::transform([](CR<vpsc::Rectangle> r) {
              return GraphRect(
                  r.getMinX(),               // top left x
                  r.getMaxY(),               // top left y
                  r.getMaxX() - r.getMinX(), // width
                  r.getMaxY() - r.getMinY()  // height
              );
          })
        | rs::to<Vec>();

    res.bbox.height = 0;
    res.bbox.width  = 0;
    for (auto const& rect : res.fixed) {
        GraphPoint upperLeft{rect.left, rect.top};
        GraphPoint lowerRight{
            rect.left + rect.width, rect.top + rect.height};

        res.bbox.extend(upperLeft);
        res.bbox.extend(lowerRight);
    }

    for (auto const& edge : edges) {
        GraphPath              path;
        Avoid::PolyLine const& route = edge.connection->displayRoute();
        for (auto const& p : route.ps) {
            path.point(p.x, p.y);
            res.bbox.extend(GraphPoint{
                static_cast<int>(p.x),
                static_cast<int>(p.y),
            });
        }
        res.lines[edge.edge] = Edge{.paths = {path}};
    }

    return res;
}

GraphConstraint::Res GraphConstraint::Align::toCola() const {
    auto result = std::make_shared<cola::AlignmentConstraint>(
        toVpsc(dimension));

    for (auto const& spec : nodes) {
        result->addShape(spec.node, spec.offset);
        if (spec.fixPos) { result->fixPos(*spec.fixPos); }
    }

    return result;
}

Vec<GraphConstraint::Res> GraphConstraint::Separate::toCola() const {
    auto left_constraint  = left.toCola();
    auto right_constraint = right.toCola();
    auto result           = std::make_shared<cola::SeparationConstraint>(
        toVpsc(dimension),
        dynamic_cast<cola::AlignmentConstraint*>(left_constraint.get()),
        dynamic_cast<cola::AlignmentConstraint*>(right_constraint.get()),
        separationDistance,
        isExactSeparation);

    return {result, left_constraint, right_constraint};
}

namespace {
std::string joinCola(Vec<GraphConstraint::Res> const& args) {
    return std::string{"["}
         + (args //
            | rv::transform([](GraphConstraint::Res const& it) {
                  return it->toString();
              })
            | rv::intersperse(", ") //
            | rv::join              //
            | rs::to<std::string>())
         + std::string{"]"};
}
} // namespace

std::string GraphLayoutIR::doColaStrFormat() {
    ColaResult                          ir;
    Vec<SPtr<cola::CompoundConstraint>> constraints = ir.setupConstraints(
        rectangles, this->constraints);
    return joinCola(constraints);
}

std::string GraphConstraint::Separate::toColaString() const {
    return joinCola(toCola());
}

std::string GraphConstraint::MultiSeparate::toColaString() const {
    return joinCola(toCola());
}

std::string GraphConstraint::toColaString(
    const std::vector<vpsc::Rectangle*>& allRects) const {
    return joinCola(toCola(allRects));
}


Vec<GraphConstraint::Res> GraphConstraint::MultiSeparate::toCola() const {
    Vec<Res> result;
    for (auto const& line : lines) { result.push_back(line.toCola()); }

    auto sep = std::make_shared<cola::MultiSeparationConstraint>(
        toVpsc(dimension), separationDistance, isExactSeparation);

    for (auto [pair1, pair2] : alignPairs) {
        sep->addAlignmentPair(
            dynamic_cast<cola::AlignmentConstraint*>(
                result.at(pair1).get()),
            dynamic_cast<cola::AlignmentConstraint*>(
                result.at(pair2).get()));
    }

    result.push_back(sep);

    return result;
}


Vec<GraphConstraint::Res> GraphConstraint::toCola(
    const std::vector<vpsc::Rectangle*>& allRects) const {
    return std::visit(
        overloaded{
            [&](FixedRelative const& fixed) -> Vec<Res> {
                return {fixed.toCola(allRects)};
            },
            [&](Align const& align) -> Vec<Res> {
                return {align.toCola()};
            },
            [&](MultiSeparate const& sep) -> Vec<Res> {
                return sep.toCola();
            },
            [&](PageBoundary const& sep) -> Vec<Res> {
                return {sep.toCola()};
            },
            [&](Separate const& sep) -> Vec<Res> { return sep.toCola(); },
            [&](Empty const& sep) -> Vec<Res> { return {}; },
        },
        data);
}


GraphConstraint::Res GraphConstraint::PageBoundary::toCola() const {
    return std::make_shared<cola::PageBoundaryConstraints>(
        rect.left,
        rect.left + rect.width,
        rect.top + rect.height,
        rect.top,
        weight);
}

void GraphRect::extend(const GraphPoint& point) {
    int min_x = std::min(left, point.x);
    int max_x = std::max(left + width, point.x);
    int min_y = std::min(top, point.y);
    int max_y = std::max(top + height, point.y);
    left      = min_x;
    top       = min_y;
    height    = max_y - min_y;
    width     = max_x - min_x;
}
