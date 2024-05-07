#include "test_mind_map.hpp"

#include <libcola/cola.h>
#include <libcola/output_svg.h>
#include <QRect>
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/wrappers/graphviz.hpp>
#include <editor/editor_lib/org_graph_model.hpp>

struct GraphConstraint {
    struct Align {
        struct Spec {
            int         node;
            Opt<double> fixPos = std::nullopt;
            double      offset = 0.0;
        };

        Vec<Spec> nodes;
        vpsc::Dim dimension;
        DESC_FIELDS(Align, (nodes, dimension));

        SPtr<cola::CompoundConstraint> toCola() const {
            auto result = std::make_shared<cola::AlignmentConstraint>(
                dimension);

            for (auto const& spec : nodes) {
                result->addShape(spec.node, spec.offset);
                if (spec.fixPos) { result->fixPos(*spec.fixPos); }
            }

            return result;
        }
    };

    SPtr<cola::CompoundConstraint> toCola() const {
        return std::visit(
            [](auto const& spec) { return spec.toCola(); }, data);
    }

    SUB_VARIANTS(Kind, Data, data, getKind, Align);
    Data data;

    GraphConstraint(CR<Data> data) : data(data) {};
};

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


struct GraphLayoutIR {
    using IrEdge = Pair<int, int>;
    Vec<QRect>           rectangles;
    Vec<IrEdge>          edges;
    Vec<GraphConstraint> constraints;
    double               width     = 100;
    double               height    = 100;
    Str                  graphName = "G";

    void validate() {
        for (auto const& e : enumerator(edges)) {
            for (auto const& it :
                 Vec<int>{e.value().first, e.value().second}) {
                Q_ASSERT_X(
                    it < rectangles.size(),
                    "validate",
                    fmt("Edge {} point is out of range for rectangles: "
                        "[{}] out of {} rects",
                        e.index(),
                        it,
                        rectangles.size()));
            }
        }
    }

    struct Result {
        Vec<QRect>                      fixed;
        UnorderedMap<IrEdge, QPolygonF> lines;
    };

    struct GraphvizResult {
        Graphviz::Graph graph;
        Graphviz        gvc;

        void writeSvg(CR<Str> path) {
            gvc.writeFile(path, graph, Graphviz::RenderFormat::SVG);
        }

        void writeXDot(CR<Str> path) {
            gvc.writeFile(path, graph, Graphviz::RenderFormat::XDOT);
        }

        Result convert() {
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
    };

    GraphvizResult doGraphvizLayout(
        Graphviz             gvc,
        Graphviz::LayoutType layout = Graphviz::LayoutType::Dot) {
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
                  | rv::transform(
                        [&](CR<Pair<int, int>> e) -> Graphviz::Edge {
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

    /// Intermediate layout representation storage
    struct ColaResult {
        Vec<vpsc::Rectangle>          baseRectangles;
        Vec<vpsc::Rectangle*>         rectPointers;
        Vec<Pair<unsigned, unsigned>> edges;

        Result convert() {
            Result res;

            res.fixed //
                = baseRectangles
                | rv::transform([](CR<vpsc::Rectangle> r) {
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

        void writeSvg(CR<Str> path) {
            OutputFile output(rectPointers, edges, nullptr, path);
            output.rects = true;
            output.generate();
        }
    };

    ColaResult doColaLayout() {
        validate();
        ColaResult                ir;
        cola::CompoundConstraints ccs;

        auto constraints        //
            = this->constraints //
            | rv::transform(
                  [](CR<GraphConstraint> c) { return c.toCola(); })
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

        cola::ConstrainedFDLayout alg2(
            ir.rectPointers, ir.edges, width / 2);

        alg2.setConstraints(ccs);
        alg2.run();

        return ir;
    }
};

void TestMindMap::testLibcolaApi1() {
    std::vector<std::pair<unsigned, unsigned>> edges{
        {0, 1},
        {1, 2},
        {2, 3},
    };

    double                        width  = 100;
    double                        height = 100;
    std::vector<vpsc::Rectangle*> rectangles;

    for (unsigned i = 0; i < edges.size() + 1; i++) {
        double x = i * 10;
        double y = i * 10;
        rectangles.push_back(new vpsc::Rectangle(x, x + 5, y, y + 5));
    }

    cola::CompoundConstraints ccs;

    cola::AlignmentConstraint align_on_x{vpsc::XDIM};
    ccs.push_back(&align_on_x);
    align_on_x.addShape(0, 0);
    align_on_x.addShape(1, 0);

    cola::AlignmentConstraint align_on_y{vpsc::YDIM};
    ccs.push_back(&align_on_y);
    align_on_y.addShape(1, 0);
    align_on_y.addShape(3, 0);

    cola::ConstrainedFDLayout alg2(rectangles, edges, width / 2);
    alg2.setConstraints(ccs);
    alg2.run();

    OutputFile output(
        rectangles, edges, nullptr, "/tmp/testLibcolaApi1.svg");
    output.rects = true;
    output.generate();

    for (auto r : rectangles) { delete r; }
}

void TestMindMap::testLibcolaIr1() {
    GraphLayoutIR ir;
    ir.edges.push_back({0, 1});
    ir.edges.push_back({1, 2});
    ir.edges.push_back({2, 3});

    ir.rectangles.push_back(QRect(0, 0, 5, 5));
    ir.rectangles.push_back(QRect(5, 5, 5, 5));
    ir.rectangles.push_back(QRect(10, 10, 5, 5));
    ir.rectangles.push_back(QRect(15, 15, 5, 5));

    using C = GraphConstraint;

    ir.constraints.push_back(C{C::Align{
        .nodes = {C::Align::Spec{.node = 0}, C::Align::Spec{.node = 1}},
        .dimension = vpsc::XDIM,
    }});

    ir.constraints.push_back(C{C::Align{
        .nodes = {C::Align::Spec{.node = 1}, C::Align::Spec{.node = 3}},
        .dimension = vpsc::YDIM,
    }});

    auto lyt = ir.doColaLayout();
    lyt.writeSvg("/tmp/testLibcolaIr1.svg");
    lyt.convert();
}

void TestMindMap::testGraphvizIr1() {
    GraphLayoutIR ir;
    Graphviz      gvc;
    ir.edges.push_back({0, 1});
    ir.edges.push_back({1, 2});
    ir.edges.push_back({2, 3});

    ir.rectangles.push_back(QRect(0, 0, 5, 5));
    ir.rectangles.push_back(QRect(5, 5, 5, 5));
    ir.rectangles.push_back(QRect(10, 10, 20, 20));
    ir.rectangles.push_back(QRect(15, 15, 20, 20));
    auto lyt = ir.doGraphvizLayout(gvc);
    lyt.writeSvg("/tmp/testGraphvizIr1.svg");
    lyt.writeXDot("/tmp/testGraphvizIr1.xdot");
    auto converted = lyt.convert();
    QCOMPARE_EQ(converted.fixed.size(), 4);

    QCOMPARE_EQ(converted.fixed.at(0).width(), 5);
    QCOMPARE_EQ(converted.fixed.at(0).height(), 5);

    QCOMPARE_EQ(converted.fixed.at(1).width(), 5);
    QCOMPARE_EQ(converted.fixed.at(1).height(), 5);

    QCOMPARE_EQ(converted.fixed.at(2).width(), 20);
    QCOMPARE_EQ(converted.fixed.at(2).height(), 20);

    QCOMPARE_EQ(converted.fixed.at(3).width(), 20);
    QCOMPARE_EQ(converted.fixed.at(3).height(), 20);

    QCOMPARE_EQ(converted.lines.size(), 3);
}

void TestMindMap::testGraphConstruction() {
    OrgStore store;
    OrgGraph graph{&store};
    auto     root = store.addRoot(R"(
* Tree1
** Tree2
)"_ss);

    graph.addFullStore();

    Vec<OrgGraph::VDesc> nodes = gen_view(graph.nodes()) | rs::to<Vec>();
    QCOMPARE_EQ(nodes.size(), 3);
}
