#include <editor/editor_lib/org_graph_layout.hpp>
#include <editor/editor_lib/app_utils.hpp>


QRect getGraphBBox(CR<Graphviz::Graph> g) {
    boxf rect = g.info()->bb;

    // +----[UR]
    // |       |
    // [LL]----+

    return QRect(
        rect.LL.x,
        -rect.UR.y,
        rect.UR.x - rect.LL.x,
        rect.LL.y - rect.UR.y);
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
    int    x1     = static_cast<int>(x - width / 2);
    int    y1     = static_cast<int>(y - height / 2);
    auto   result = QRect(x1, y1, width, height);
    return result;
}

QPolygonF getEdgeSpline(
    CR<Graphviz::Edge> edge,
    int                scaling,
    CR<QRect>          bbox) {
    QPolygonF   polygon;
    Ppolyline_t points = edge.info()->path;
    for (int i = 0; i < points.pn; ++i) {
        Ppoint_t point = points.ps[i];
        polygon << QPointF(point.x, bbox.height() - point.y);
    }
    return polygon;
}


GraphLayoutIR::GraphvizResult GraphLayoutIR::doGraphvizLayout(
    Graphviz             gvc,
    Graphviz::LayoutType layout) {

    GraphvizResult result{
        .graph{graphName},
        .graphviz_size_scaling = graphviz_size_scaling,
    };

    int                 nodeCounter = 0;
    Vec<Graphviz::Node> nodes //
        = this->rectangles
        | rv::transform([&](CR<QRect> r) -> Graphviz::Node {
              auto node = result.graph.node(fmt1(nodeCounter));
              // default DPI used by graphviz to convert from
              // inches.
              node.setHeight(r.height() / float(graphviz_size_scaling));
              node.setWidth(r.width() / float(graphviz_size_scaling));
              node.setAttr("index", nodeCounter);
              node.setAttr("fixedsize", true);
              node.setAttr("original_height", r.height());
              node.setAttr("original_width", r.width());
              node.setShape(Graphviz::Node::Shape::rectangle);
              node.setLabel("");
              ++nodeCounter;
              return node;
          })
        | rs::to<Vec>();

    Vec<Graphviz::Edge> //
        edges = this->edges
              | rv::transform([&](CR<Pair<int, int>> e) -> Graphviz::Edge {
                    auto edge = result.graph.edge(
                        nodes.at(e.first), nodes.at(e.second));
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


QRect computeBoundingBox(GraphLayoutIR::Result const& result) {
    QRect boundingBox;

    for (const QRect& rect : result.fixed) {
        boundingBox = boundingBox.united(rect);
    }

    for (const auto& pair : result.lines) {
        boundingBox = boundingBox.united(
            pair.second.boundingRect().toRect());
    }

    return boundingBox;
}

GraphLayoutIR::Result GraphLayoutIR::GraphvizResult::convert() {
    Result res;
    res.fixed.resize(graph.nodeCount());

    res.bbox = computeBoundingBox(res);

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
