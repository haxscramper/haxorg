#include <editor/editor_lib/org_graph_layout.hpp>

constexpr float graphviz_size_scaling = 12;


QRect getNodeRectangle(CR<Graphviz::Graph> g, CR<Graphviz::Node> node) {
    auto   pos    = node.getAttr<Str>("pos").value().split(",");
    double width  = node.getWidth().value() * graphviz_size_scaling;
    double height = node.getHeight().value() * graphviz_size_scaling;
    double x      = pos.at(0).toDouble();
    double y      = pos.at(1).toDouble();
    int    x1     = static_cast<int>(x - width / 2);
    int    y1     = static_cast<int>(y - height / 2);
    return QRect(x1, y1, width, height);
}

QPolygonF getEdgeSpline(CR<Graphviz::Edge> edge) {
    auto posString = QString::fromStdString(
        edge.getAttr<Str>("pos").value());
    QPolygonF   polygon;
    QStringList points = posString.split(' ', Qt::SkipEmptyParts);
    for (const QString& point : points) {
        if (point.contains(',')) {
            QStringList coords = point.split(',');
            double      x      = coords[0].toDouble();
            double      y      = coords[1].toDouble();
            polygon << QPointF(x, y);
        }
    }
    return polygon;
}


GraphLayoutIR::GraphvizResult GraphLayoutIR::doGraphvizLayout(
    Graphviz             gvc,
    Graphviz::LayoutType layout) {
    GraphvizResult      result{.graph{graphName}, .gvc{gvc}};
    int                 nodeCounter = 0;
    Vec<Graphviz::Node> nodes //
        = this->rectangles
        | rv::transform([&](CR<QRect> r) -> Graphviz::Node {
              auto node = result.graph.node(fmt1(nodeCounter));
              // default DPI used by graphviz to convert from
              // inches.
              node.setHeight(r.height() / graphviz_size_scaling);
              node.setWidth(r.width() / graphviz_size_scaling);
              node.setAttr("index", nodeCounter);
              node.setAttr("fixedsize", true);
              node.setShape(Graphviz::Node::Shape::rectangle);
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

GraphLayoutIR::Result GraphLayoutIR::GraphvizResult::convert() {
    Result res;
    res.fixed.resize(graph.nodeCount());

    graph.eachNode([&](CR<Graphviz::Node> node) {
        res.fixed.at(node.getAttr<int>("index").value()) = getNodeRectangle(
            graph, node);
    });

    graph.eachEdge([&](CR<Graphviz::Edge> edge) {
        res.lines.insert_or_assign(
            std::make_pair(
                edge.getAttr<int>("source_index").value(),
                edge.getAttr<int>("target_index").value()),
            getEdgeSpline(edge));
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
