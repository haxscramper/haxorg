#include <editor/editor_lib/org_graph_layout.hpp>
#include <editor/editor_lib/app_utils.hpp>
#include <QPainterPath>
#include <hstd/stdlib/Set.hpp>


QPoint toGvPoint(pointf p, int height) {
    return QPoint(p.x, height - p.y);
}

QRect getSubgraphBBox(CR<Graphviz::Graph> g, CR<QRect> bbox) {
    boxf  rect = g.info()->bb;
    QRect res{};
    res.setBottomLeft(toGvPoint(rect.LL, bbox.height()));
    res.setTopRight(toGvPoint(rect.UR, bbox.height()));
    Q_ASSERT(res.isValid());
    return res;
}

QRect getGraphBBox(CR<Graphviz::Graph> g) {
    boxf rect = g.info()->bb;

    // +----[UR]
    // |       |
    // [LL]----+

    auto res = QRect(0, 0, rect.UR.x, rect.UR.y);

    Q_ASSERT(res.isValid());
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

QRect getNodeRectangle(
    CR<Graphviz::Graph> g,
    CR<Graphviz::Node>  node,
    int                 scaling,
    CR<QRect>           bbox) {
    double width  = node.info()->width * scaling;
    double height = node.info()->height * scaling;
    double x      = node.info()->coord.x;
    double y      = bbox.height() - node.info()->coord.y;
    int    x1     = std::round(x - width / 2);
    int    y1     = std::round(y - height / 2);
    auto   result = QRect(
        std::round(x1),
        std::round(y1),
        std::round(width),
        std::round(height));

    return result;
}

QPainterPath getEdgeSpline(
    CR<Graphviz::Edge> edge,
    int                scaling,
    CR<QRect>          bbox) {
    splines*     spl = edge.info()->spl;
    QPainterPath path;
    int          height = bbox.height();
    if ((spl->list != 0) && (spl->list->size % 3 == 1)) {
        bezier bez = spl->list[0];
        if (bez.sflag) {
            path.moveTo(toGvPoint(bez.sp, height));
            path.lineTo(toGvPoint(bez.list[0], height));
        } else {
            path.moveTo(toGvPoint(bez.list[0], height));
        }

        for (int i = 1; i < bez.size; i += 3) {
            path.cubicTo(
                toGvPoint(bez.list[i], height),
                toGvPoint(bez.list[i + 1], height),
                toGvPoint(bez.list[i + 2], height));
        }

        if (bez.eflag) { path.lineTo(toGvPoint(bez.ep, height)); }
    }
    return path;
}

namespace {
const char* original_subgraph_nodes_prop = "original_nodes";
const char* original_subgraph_path_prop  = "original_path";
const char* original_subgraph_index      = "original_index";
} // namespace

GraphLayoutIR::GraphvizResult GraphLayoutIR::doGraphvizLayout(
    Graphviz             gvc,
    Graphviz::LayoutType layout) {

    GraphvizResult result{
        .graph{graphName},
        .graphviz_size_scaling = graphviz_size_scaling,
        .gvc{gvc},
    };

    result.graph.setRankDirection(Graphviz::Graph::RankDirection::LR);

    auto add_node = [&](Graphviz::Graph& graph,
                        int              index) -> Graphviz::Node {
        CR<QRect> r    = rectangles.at(index);
        auto      node = graph.node(fmt1(index));
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

    {
        Vec<Graphviz::Graph> added_subgraphs;

        int subgraph_counter = 0;

        Func<void(Graphviz::Graph&, Subgraph const&, CVec<int>)> aux;

        aux = [&](Graphviz::Graph& parent,
                  Subgraph const&  sub,
                  CVec<int>        path) -> void {
            auto out_graph = parent.newSubgraph(
                fmt("cluster_{}",
                    sub.graphName.empty() ? Str(fmt1(subgraph_counter))
                                          : sub.graphName));
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

            for (auto const& s : enumerator(sub.subgraphs)) {
                aux(out_graph, s.value(), path + Vec<int>{s.index()});
            }
        };

        for (auto const& g : enumerator(subgraphs)) {
            aux(result.graph, g.value(), Vec<int>{g.index()});
        }
    }

    Vec<Graphviz::Edge> //
        edges = this->edges
              | rv::transform([&](CR<Pair<int, int>> e) -> Graphviz::Edge {
                    auto edge = result.graph.edge(
                        nodes.at(e.first).value(),
                        nodes.at(e.second).value());
                    edge.setAttr("source_index", e.first);
                    edge.setAttr("target_index", e.second);
                    return edge;
                })
              | rs::to<Vec>();

    gvc.createLayout(result.graph, layout);

    return result;
}

GraphLayoutIR::ColaResult GraphLayoutIR::doColaLayout() {
    validate();
    ColaResult                ir;
    cola::CompoundConstraints ccs;

    auto constraints        //
        = this->constraints //
        | rv::transform([](CR<GraphConstraint> c) { return c.toCola(); })
        | rs::to<Vec>();

    for (auto const& c : constraints) { ccs.push_back(c.get()); }

    ir.baseRectangles.reserve(rectangles.size());
    for (auto const& r : rectangles) {
        ir.baseRectangles.push_back(
            vpsc::Rectangle(r.left(), r.right(), r.top(), r.bottom()));
    }

    ir.rectPointers                                 //
        = ir.baseRectangles                         //
        | rv::transform([](auto& r) { return &r; }) //
        | rs::to<Vec>();

    ir.edges //
        = edges
        | rv::transform([](auto const& i) -> Pair<unsigned, unsigned> {
              return std::make_pair<unsigned>(i.first, i.second);
          })
        | rs::to<Vec>();

    cola::ConstrainedFDLayout alg2(ir.rectPointers, ir.edges, width / 2);

    alg2.setConstraints(ccs);
    alg2.run();

    return ir;
}

GraphLayoutIR::Result GraphLayoutIR::GraphvizResult::convert() {
    Result res;
    res.fixed.resize(graph.nodeCount());

    res.bbox = getGraphBBox(graph);
    Q_ASSERT(res.bbox.size() != QSize(0, 0));

    graph.eachNode([&](CR<Graphviz::Node> node) {
        res.fixed.at(node.getAttr<int>("index").value()) = getNodeRectangle(
            graph, node, graphviz_size_scaling, res.bbox);
    });

    graph.eachEdge([&](CR<Graphviz::Edge> edge) {
        res.lines.insert_or_assign(
            std::make_pair(
                edge.getAttr<int>("source_index").value(),
                edge.getAttr<int>("target_index").value()),
            getEdgeSpline(edge, graphviz_size_scaling, res.bbox));
    });

    auto mut_at = []<typename T>(Vec<T>& list, int idx) -> T& {
        if (!list.has(idx)) { list.resize(idx + 1); }
        return list.at(idx);
    };

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
                mut_at(out_parent.subgraphs, path.front()),
                in_subgraph,
                path[slice(1, 1_B)]);
        }
    };

    Func<void(CR<Graphviz::Graph>)> rec_subgraph;
    rec_subgraph = [&](CR<Graphviz::Graph> g) {
        auto original_path = from_json_eval<Vec<int>>(json::parse(
            g.getAttr<Str>(original_subgraph_path_prop).value().toBase()));

        int original_index = g.getAttr<int>(original_subgraph_index)
                                 .value();


        mut_at(res.subgraphPaths, original_index) = original_path;

        set_graph(
            mut_at(res.subgraphs, original_path.front()),
            g,
            original_path[slice(1, 1_B)]);

        g.eachSubgraph(rec_subgraph);
    };

    graph.eachSubgraph(rec_subgraph);

    return res;
}

GraphLayoutIR::Result GraphLayoutIR::ColaResult::convert() {
    Result res;

    res.fixed //
        = baseRectangles | rv::transform([](CR<vpsc::Rectangle> r) {
              return QRect(
                  r.getMinX(),               // top left x
                  r.getMaxY(),               // top left y
                  r.getMaxX() - r.getMinX(), // width
                  r.getMaxY() - r.getMinY()  // height
              );
          })
        | rs::to<Vec>();

    return res;
}
