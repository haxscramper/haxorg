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
    store.addRoot(R"(
* Tree1
** Tree2
)"_ss);

    graph.addFullStore();

    Vec<OrgGraph::VDesc> nodes = gen_view(graph.nodes()) | rs::to<Vec>();
    QCOMPARE_EQ(nodes.size(), 3);
}

Pair<SPtr<OrgStore>, SPtr<OrgGraph>> build_graph(CR<Str> text) {
    auto store = std::make_shared<OrgStore>();
    auto graph = std::make_shared<OrgGraph>(store.get());
    store->addRoot(text);
    graph->addFullStore();
    return std::make_pair(store, graph);
}

#define QCOMPARE_OP2_IMPL(lhs, rhs, op, opId)                             \
    do {                                                                  \
        if (![](auto&& qt_lhs_arg, auto&& qt_rhs_arg) {                   \
                bool success = std::forward<decltype(qt_lhs_arg)>(        \
                    qt_lhs_arg)                                           \
                    op std::forward<decltype(qt_rhs_arg)>(qt_rhs_arg);    \
                return QTest::reportResult(                               \
                    success,                                              \
                    [&qt_lhs_arg] {                                       \
                        return qstrdup(fmt1(qt_lhs_arg).c_str());         \
                    },                                                    \
                    [&qt_rhs_arg] {                                       \
                        return qstrdup(fmt1(qt_rhs_arg).c_str());         \
                    },                                                    \
                    #lhs,                                                 \
                    #rhs,                                                 \
                    QTest::ComparisonOperation::opId,                     \
                    __FILE__,                                             \
                    __LINE__);                                            \
            }(lhs, rhs)) {                                                \
            return;                                                       \
        }                                                                 \
    } while (false)

#define QCOMPARE_EQ2(computed, baseline)                                  \
    QCOMPARE_OP2_IMPL(computed, baseline, ==, Equal)
#define QCOMPARE_NE2(computed, baseline)                                  \
    QCOMPARE_OP2_IMPL(computed, baseline, !=, NotEqual)
#define QCOMPARE_LT2(computed, baseline)                                  \
    QCOMPARE_OP2_IMPL(computed, baseline, <, LessThan)
#define QCOMPARE_LE2(computed, baseline)                                  \
    QCOMPARE_OP2_IMPL(computed, baseline, <=, LessThanOrEqual)
#define QCOMPARE_GT2(computed, baseline)                                  \
    QCOMPARE_OP2_IMPL(computed, baseline, >, GreaterThan)
#define QCOMPARE_GE2(computed, baseline)                                  \
    QCOMPARE_OP_IMPL(computed, baseline, >=, GreaterThanOrEqual)


void TestMindMap::testGraphConstructionSubtreeId1() {
    auto [store, graph] = build_graph(R"(
Paragraph [[id:subtree-id]]

* Subtree
  :properties:
  :id: subtree-id
  :end:
)"_ss);

    auto r = store->getRoot(0);
    QCOMPARE_EQ(r->subnodes.size(), 2);
    QCOMPARE_EQ(r->at(0)->subnodes.size(), 0);
    QCOMPARE_EQ(r->at(1)->subnodes.size(), 0);

    QCOMPARE_EQ(graph->numNodes(), 3);
    QVERIFY(graph->hasEdge(r->id(0), r->id(1)));
    QCOMPARE_EQ(
        graph->out_edge0(r->id(0), r->id(1)).kind,
        OrgGraphEdge::Kind::SubtreeId);
    QVERIFY(graph->unresolved.empty());
}

void TestMindMap::testGraphConstructionFootnoteId() {
    auto [store, graph] = build_graph(R"(
Paragraph [fn:target]

[fn:target] Description
)");


    auto r = store->getRoot(0);

    QCOMPARE_EQ(r->subnodes.size(), 2);
    QCOMPARE_EQ(graph->numNodes(), 3);
    QVERIFY(graph->unresolved.empty());
    QVERIFY(graph->hasEdge(r->id(0), r->id(1)));
    QCOMPARE_EQ(
        graph->out_edge0(r->id(0), r->id(1)).kind,
        OrgGraphEdge::Kind::Footnote);
}

Str getFullMindMapText() {
    Vec<Str> text{
        // 0
        R"(
* Mind map nodes are made from subtrees
)",
        // 0.0
        R"(
** Subtrees can be nested for clustering
   :PROPERTIES:
   :ID:       c468e9c7-7422-4b17-8ccb-53575f186fe0
   :END:
)",
        // 0.1
        R"(
** More than one subtree can exist in cluster
)",
        // 0.1.0
        R"(
Tree  description, maybe  on multiple  lines.
Can include  [[id:c468e9c7-7422-4b17-8ccb-53575f186fe0][links]] to  other trees.
Links are attached to specific [[id:6d6d6689-d9da-418d-9f91-1c8c4428e5af][rows]] in the text
so it is easier to track which part of the
description refers to the [[id:9879fed7-f0a4-44bd-bf56-983279afc622][other]] tree
)",
        // 0.1.1 -- main list node
        // 0.1.1.0 -- first list item node
        R"(- )",
        // 0.1.1.0.0
        R"(when [[id:c468e9c7-7422-4b17-8ccb-53575f186fe0][link]] :: Description lists can be used for annotated links

)",
        // 0.1.1.0.1
        R"(  Multiple paragraphs attached to link
)",
        // 0.1.2
        R"(
used in description list it's placed as annotation to the graph node.
Description can take multiple lines[fn:lines-20].
)",
        // 0.1.3
        R"(
[fn:lines-20]  Footnotes  are placed  into  separate  nodes. You  can  have
nested[fn:nested-23]
)",
        // 0.1.4
        R"(
[fn:nested-23] footnotes
)",
        // 0.2
        R"(
** Extra entries
   :PROPERTIES:
   :ID:       6d6d6689-d9da-418d-9f91-1c8c4428e5af
   :END:
)",
        // 0.2.0
        R"(
Parent subtrees can contain some things.
)",
        // 1
        R"(
* Several clusters can exist
)",
        // 1.0
        R"(
Nested subtrees
Multiline [[id:6d6d6689-d9da-418d-9f91-1c8c4428e5af][Extra entries]]
)",
        // 1.1
        R"(
** With multiple nodes
   :PROPERTIES:
   :ID:       9879fed7-f0a4-44bd-bf56-983279afc622
   :END:
)",
        // 1.2
        R"(
** And even nested
)",
        // 1.2.0
        R"(
*** Clusters
)",
        // 1.2.1
        R"(
*** And nodes
)",
        // 1.2.1
        R"(
*** Intercluster links are possible
)",
        // 1.2.1.0
        R"(
[[id:c468e9c7-7422-4b17-8ccb-53575f186fe0][Subtrees can be nested for clustering]]
[[id:XXSDASD][Unresolved subtree]]
)",
    };
    return join("", text);
}

void TestMindMap::testFullMindMapGraph() {
    auto [store, graph] = build_graph(getFullMindMapText());
    auto r              = store->getRoot(0);

    qDebug().noquote() << graph->toGraphviz();

    QCOMPARE_EQ2(graph->unresolved.size(), 1);
    QCOMPARE_EQ2(store->node(r->id(0))->getKind(), osk::Subtree);
    QCOMPARE_EQ2(store->node(r->id({0, 0}))->getKind(), osk::Subtree);
    QCOMPARE_EQ2(store->node(r->id({0, 1}))->getKind(), osk::Subtree);
    QCOMPARE_EQ2(store->node(r->id({0, 1, 0}))->getKind(), osk::Paragraph);

    // Description list with annotations for links
    // List itself is also a part of the node structure
    QCOMPARE_EQ2(store->node(r->id({0, 1, 1}))->getKind(), osk::List);
    // List contains one or more nested list items
    QCOMPARE_EQ2(
        store->node(r->id({0, 1, 1, 0}))->getKind(), osk::ListItem);

    // And then the list item is subdivided into individual paragraphs
    QCOMPARE_EQ2(
        store->node(r->id({0, 1, 1, 0, 0}))->getKind(), osk::Paragraph);
    QCOMPARE_EQ2(
        store->node(r->id({0, 1, 1, 0, 1}))->getKind(), osk::Paragraph);

    QCOMPARE_EQ2(store->node(r->id({0, 1, 2}))->getKind(), osk::Paragraph);
    QCOMPARE_EQ2(
        store->node(r->id({0, 1, 3}))->getKind(), osk::AnnotatedParagraph);
    QCOMPARE_EQ2(
        store->node(r->id({0, 1, 4}))->getKind(), osk::AnnotatedParagraph);
    QCOMPARE_EQ2(store->node(r->id(1))->getKind(), osk::Subtree);

    // Link from the paragraph using `lines-20` to the footnote definition
    QVERIFY(graph->hasEdge(r->id({0, 1, 2}), r->id({0, 1, 3})));
    // The footnote definition in turn can refer to another footnote
    // definition of its own
    QVERIFY(graph->hasEdge(r->id({0, 1, 3}), r->id({0, 1, 4})));

    // First paragraph has three named links to subtrees before and after
    // itself
    Vec<int> par_010{0, 1, 0};
    QVERIFY(graph->hasEdge(r->id(par_010), r->id({0, 0})));
    QVERIFY(graph->hasEdge(r->id(par_010), r->id({0, 2})));
    QVERIFY(graph->hasEdge(r->id(par_010), r->id({1, 1})));

    QCOMPARE_EQ(
        str(graph->out_edge0(r->id(par_010), r->id({0, 0}))
                .description.value()),
        "links");
    QCOMPARE_EQ(
        str(graph->out_edge0(r->id(par_010), r->id({0, 2}))
                .description.value()),
        "rows");
    QCOMPARE_EQ(
        str(graph->out_edge0(r->id(par_010), r->id({1, 1}))
                .description.value()),
        "other");

    QCOMPARE_EQ(graph->in_edges(r->id({0, 2})).size(), 2);
    {
        auto desc = graph->out_edge0(r->id({0, 1, 1, 0}), r->id({0, 0}))
                        .description.value();
        auto desc_str = str(desc);
        QVERIFY(desc_str.contains(
            "Description lists can be used for annotated links"));
        QVERIFY(desc_str.contains("Multiple paragraphs attached to link"));
    }

    {
        auto node_text //
            = gen_view(graph->nodes())
            | rv::transform([&](OrgGraph::VDesc desc) -> Str {
                  auto node = store->nodeWithoutNested(
                      graph->node(desc).box);
                  return str(node);
              })
            | rs::to<Vec>();

        auto get_idx = [&](CR<Str> str) -> int {
            auto it = rs::find_if(node_text, [&](CR<Str> item) {
                return item.contains(str);
            });

            return it == node_text.end()
                     ? -1
                     : std::distance(node_text.begin(), it);
        };

        for (auto const& it : node_text) { qDebug() << it; }

        QVERIFY(get_idx("Mind map nodes are made from subtrees") != -1);
    }
}
