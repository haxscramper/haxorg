#include "test_mind_map.hpp"

#include <editor/editor_lib/mind_map/org_graph_layout.hpp>


#include <QRect>
#include <QEvent>
#include <QMetaMethod>
#include <QMetaObject>
#include <QDebug>
#include <QObject>
#include <QCoreApplication>

#include <hstd/stdlib/Ranges.hpp>
#include <editor/editor_lib/mind_map/org_graph_model.hpp>
#include <editor/editor_lib/mind_map/org_graph_scene.hpp>

using namespace org::mind_map;

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


void TestMindMap::testLibcolaRaw1() {
    using namespace Avoid;
    Router  router_it{PolyLineRouting | OrthogonalRouting};
    Router* router = &router_it;
    router->setRoutingPenalty((PenaltyType)0, 50);
    router->setRoutingPenalty((PenaltyType)1, 0);
    router->setRoutingPenalty((PenaltyType)2, 400);
    router->setRoutingPenalty((PenaltyType)3, 4000);
    router->setRoutingPenalty((PenaltyType)4, 110);
    router->setRoutingParameter(idealNudgingDistance, 25);

    Polygon poly143407352(4);
    poly143407352.ps[0] = Point(5810, 4340);
    poly143407352.ps[1] = Point(5810, 5035);
    poly143407352.ps[2] = Point(5450, 5035);
    poly143407352.ps[3] = Point(5450, 4340);
    new ShapeRef(router, poly143407352, 143407352);

    Polygon poly124950386(4);
    poly124950386.ps[0] = Point(4900, 4090);
    poly124950386.ps[1] = Point(4900, 4785);
    poly124950386.ps[2] = Point(4540, 4785);
    poly124950386.ps[3] = Point(4540, 4090);
    new ShapeRef(router, poly124950386, 124950386);

    ConnRef* connRef373967044 = new ConnRef(router, 373967044);
    ConnEnd  srcPt373967044(Point(4890, 4250), 8);
    connRef373967044->setSourceEndpoint(srcPt373967044);
    ConnEnd dstPt373967044(Point(5460, 4500), 4);
    connRef373967044->setDestEndpoint(dstPt373967044);
    connRef373967044->setRoutingType((ConnType)2);

    ConnRef* connRef681881486 = new ConnRef(router, 681881486);
    ConnEnd  srcPt681881486(Point(4890, 4325), 8);
    connRef681881486->setSourceEndpoint(srcPt681881486);
    ConnEnd dstPt681881486(Point(5460, 4575), 4);
    connRef681881486->setDestEndpoint(dstPt681881486);
    connRef681881486->setRoutingType((ConnType)2);

    ConnRef* connRef829752 = new ConnRef(router, 829752);
    ConnEnd  srcPt829752(Point(4890, 4400), 8);
    connRef829752->setSourceEndpoint(srcPt829752);
    ConnEnd dstPt829752(Point(5460, 4650), 4);
    connRef829752->setDestEndpoint(dstPt829752);
    connRef829752->setRoutingType((ConnType)2);

    router->processTransaction();
    router->outputDiagramText("/tmp/orthordering-01");
    router->outputInstanceToSVG("/tmp/orthordering-01");
}

void TestMindMap::testLibcolaRaw2() {
    using namespace Avoid;
    Router  router_it{Avoid::OrthogonalRouting};
    Router* router = &router_it;

    ShapeRef* shapeRef0;
    ShapeRef* shapeRef1;
    ShapeRef* shapeRef2;

    auto pin_for_shape = [](ShapeRef* shape, int pinClass) {
        new ShapeConnectionPin(
            shape,
            pinClass,
            Avoid::ATTACH_POS_CENTRE,
            Avoid::ATTACH_POS_CENTRE,
            true,
            0,
            Avoid::ConnDirNone);
    };

    { // Edge routing works with already positioned elements
        {
            auto polygon  = Polygon(4);
            polygon.ps[0] = Point(-10.3237, -3.46733);
            polygon.ps[1] = Point(-5.32374, -3.46733);
            polygon.ps[2] = Point(-5.32374, -8.46733);
            polygon.ps[3] = Point(-10.3237, -8.46733);

            shapeRef1 = new ShapeRef(router, polygon, 1);
        }

        {
            auto polygon  = Polygon(4);
            polygon.ps[0] = Point(-56.6515, 15.3407);
            polygon.ps[1] = Point(-51.6515, 15.3407);
            polygon.ps[2] = Point(-51.6515, 10.3407);
            polygon.ps[3] = Point(-56.6515, 10.3407);

            shapeRef0 = new ShapeRef(router, polygon, 1);
        }

        {
            auto polygon  = Polygon(4);
            polygon.ps[0] = Point(-17.1994, 46.0577);
            polygon.ps[1] = Point(-12.1994, 46.0577);
            polygon.ps[2] = Point(-12.1994, 41.0577);
            polygon.ps[3] = Point(-17.1994, 41.0577);

            shapeRef2 = new ShapeRef(router, polygon, 2);
        }
    }

    // each shape can have a number of pins. Pins connected by the same
    // edge must share the same class ID.
    {
        // Shape 0 has two pins, connecting for edge 0 and edge 1.
        pin_for_shape(shapeRef0, 1);
        pin_for_shape(shapeRef0, 2);

        pin_for_shape(shapeRef1, 2);
        pin_for_shape(shapeRef1, 3);

        pin_for_shape(shapeRef2, 3);
        pin_for_shape(shapeRef2, 1);
    }

    {
        { // Edge 0, connecting first pin of shape 0 to the pin of shape 1
            ConnEnd source{shapeRef0, 2};
            ConnEnd target{shapeRef1, 2};
            auto    conn = new ConnRef(router, source, target);
            conn->setRoutingType(ConnType::ConnType_Orthogonal);
        }
        {
            ConnEnd source{shapeRef1, 3};
            ConnEnd target{shapeRef2, 3};
            auto    conn = new ConnRef(router, source, target);
            conn->setRoutingType(ConnType::ConnType_Orthogonal);
        }

        {
            ConnEnd source{shapeRef2, 1};
            ConnEnd target{shapeRef0, 1};
            auto    conn = new ConnRef(router, source, target);
            conn->setRoutingType(ConnType::ConnType_Orthogonal);
        }
    }

    router->processTransaction();
    router->outputInstanceToSVG("/tmp/testLibcolaRaw2");
}

GraphLayoutIR init_graph(
    CVec<Pair<int, int>> edges,
    QSize                size = QSize(5, 5)) {
    int           max_node = 0;
    GraphLayoutIR ir;
    ir.edges = edges;
    for (auto const& e : edges) {
        max_node = std::max(max_node, std::max(e.first, e.second));
    }

    for (int i = 0; i <= max_node; ++i) { ir.rectangles.push_back(size); }

    return ir;
}

using C = GraphConstraint;

void TestMindMap::testLibcolaIr1() {
    GraphLayoutIR ir;
    ir.edges.push_back({0, 1});
    ir.edges.push_back({1, 2});
    ir.edges.push_back({2, 3});

    ir.rectangles.push_back(QSize(5, 5));
    ir.rectangles.push_back(QSize(5, 5));
    ir.rectangles.push_back(QSize(5, 5));
    ir.rectangles.push_back(QSize(5, 5));


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

void TestMindMap::testLibcolaIr2() {
    auto ir = init_graph(
        {
            {0, 1},
            {1, 2},
            {2, 0},
            {3, 0},
            {4, 0},
            {2, 3},
            {3, 4},
            {4, 5},
        },
        QSize(60, 60));

    ir.width  = 400;
    ir.height = 400;

    auto lyt = ir.doColaLayout();
    lyt.writeSvg("/tmp/testLibcolaIr2.svg");
    auto conv = lyt.convert();

    lyt.router->outputInstanceToSVG("/tmp/testLibcolaIr2_router");
    lyt.router->outputDiagramText("/tmp/testLibcolaIr2_router");
    QVERIFY(!conv.lines.at({0, 1}).paths.at(0).isEmpty());
}

void TestMindMap::testHolaIr1() {
    auto ir = init_graph(
        {
            {0, 1},
            {1, 2},
            {2, 0},
            {3, 0},
            {4, 0},
            {2, 3},
            {3, 4},
            {4, 5},
        },
        QSize(60, 60));

    auto lyt = ir.doHolaLayout();
    writeFile("/tmp/testHolaIr1.svg", lyt.graph->writeSvg());
    auto conv = lyt.convert();
    QVERIFY(!conv.lines.at({0, 1}).paths.at(0).isEmpty());
}

void TestMindMap::testGraphvizIr1() {
    GraphLayoutIR ir;
    Graphviz      gvc;
    ir.edges.push_back({0, 1});
    ir.edges.push_back({1, 2});
    ir.edges.push_back({2, 3});

    ir.rectangles.push_back(QSize(5, 5));
    ir.rectangles.push_back(QSize(5, 5));
    ir.rectangles.push_back(QSize(20, 20));
    ir.rectangles.push_back(QSize(20, 20));
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

void TestMindMap::testGraphvizIrClusters() {
    GraphLayoutIR ir;
    Graphviz      gvc;

    auto edge = [&](int source, int target) {
        ir.edges.push_back({source, target});
    };

    for (int i = 0; i <= 10; ++i) {
        ir.rectangles.push_back(QSize(10, 10));
    }

    using S = GraphLayoutIR::Subgraph;


    edge(0, 2);
    edge(2, 1);
    edge(1, 8);
    edge(8, 3);
    edge(3, 4);
    edge(4, 6);
    edge(3, 6);
    edge(8, 5);
    edge(5, 9);
    edge(9, 10);
    edge(10, 7);
    edge(7, 5);

    ir.subgraphs.push_back(
        S{.nodes     = {}, // No nodes in the first cluster,
          .subgraphs = {
              S{.nodes = {3, 4, 6}},
              S{.nodes = {5, 9, 7, 10}},
          }});

    auto lyt = ir.doGraphvizLayout(gvc);
    lyt.writeSvg("/tmp/testGraphvizIrClusters.svg");
    lyt.writeXDot("/tmp/testGraphvizIrClusters.xdot");
    auto c = lyt.convert();

    QCOMPARE_EQ2(c.subgraphPaths.size(), 3);
    QCOMPARE_EQ2(c.subgraphs.size(), 1);
    QCOMPARE_EQ2(c.subgraphs.at(0).subgraphs.size(), 2);
    QCOMPARE_EQ2(c.getSubgraph({0}).subgraphs.size(), 2);
    QCOMPARE_EQ2(c.getSubgraph({0, 0}).subgraphs.size(), 0);
    QCOMPARE_EQ2(c.getSubgraph({0, 1}).subgraphs.size(), 0);
    QCOMPARE_EQ2(c.subgraphPaths.at(0), Vec<int>{0});
    QCOMPARE_EQ2(c.subgraphPaths.at(1), (Vec<int>{0, 0}));
    QCOMPARE_EQ2(c.subgraphPaths.at(2), (Vec<int>{0, 1}));
    QVERIFY(c.getSubgraph({0}).bbox.contains(c.getSubgraph({0, 0}).bbox));
    QVERIFY(c.getSubgraph({0}).bbox.contains(c.getSubgraph({0, 1}).bbox));
}

void TestMindMap::testGraphConstruction() {
    OrgStore store;
    Graph    graph{&store, nullptr};
    graph.connectStore();
    store.addRoot(R"(
* Tree1
** Tree2
)"_ss);


    QCOMPARE_EQ(graph.state.nodes.size(), 3);
}

Pair<SPtr<OrgStore>, SPtr<Graph>> build_graph(CR<Str> text) {
    auto store = std::make_shared<OrgStore>();
    auto graph = std::make_shared<Graph>(store.get(), nullptr);
    graph->connectStore();
    store->addRoot(text);
    return std::make_pair(store, graph);
}

void TestMindMap::testGraphConstructionSubtreeId1() {
    Str text{R"(
Paragraph [[id:subtree-id]]

* Subtree
  :properties:
  :id: subtree-id
  :end:
)"_ss};

    {
        OrgStore store;
        Graph    graph{&store, nullptr};
        store.addRoot(text);

        // First time paragraph is added to the graph it has an unresolved
        // outgoing link
        auto paragraph_edits = graph.getNodeInsert(store.getBox0({0}));

        // The tree has no links, but has a single subtree ID.
        auto subtree_edits1 = graph.getNodeInsert(store.getBox0({1}));

        // Integrating first paragraph into the graph structure pushes the
        // link into part of the mutable state
        graph.addBox(store.getBox0({0}));
        QCOMPARE_EQ(graph.numNodes(), 1);
        QCOMPARE_EQ(graph.numEdges(), 0);
        QCOMPARE_EQ(graph.state.unresolved.size(), 1);

        // Adding the tree now will correctly resolve the link targets
        auto subtree_edits2 = graph.getNodeInsert(store.getBox0({1}));

        // Integrating the second tree cleans up the unresolved mutable
        // state
        graph.addBox(store.getBox0({1}));
        QCOMPARE_EQ(graph.state.unresolved.size(), 0);
    }


    {
        auto [store, graph] = build_graph(text);

        auto edits = graph->getNodeInsert(store->getRoot(0)->at(0)->boxId);


        auto r = store->getRoot(0);
        QCOMPARE_EQ(r->subnodes.size(), 2);
        QCOMPARE_EQ(r->at(0)->subnodes.size(), 0);
        QCOMPARE_EQ(r->at(1)->subnodes.size(), 0);

        QCOMPARE_EQ(graph->numNodes(), 3);
        QCOMPARE_EQ(graph->numEdges(), 1);
        QVERIFY(graph->hasEdge(r->id(0), r->id(1)));
        QVERIFY(graph->state.unresolved.empty());
    }
}

void TestMindMap::testGraphConstructionFootnoteId() {
    auto [store, graph] = build_graph(R"(
Paragraph [fn:target]

[fn:target] Description
)");


    auto r = store->getRoot(0);

    QCOMPARE_EQ(r->subnodes.size(), 2);
    QCOMPARE_EQ(graph->numNodes(), 3);
    QVERIFY(graph->state.unresolved.empty());
    QVERIFY(graph->hasEdge(r->id(0), r->id(1)));
}

void TestMindMap::testGraphConstructionMultipleLinks_footnote1() {
    auto [store, graph] = build_graph(R"(
Paragraph [fn:target1] [fn:target2]

[fn:target1] Description

[fn:target2] Description
)");

    auto r = store->getRoot(0);

    QCOMPARE_EQ(r->subnodes.size(), 3);
    QCOMPARE_EQ(graph->numNodes(), 4);
    QCOMPARE_EQ(graph->numEdges(), 2);
    QCOMPARE_EQ(graph->out_edges(r->id(0)).size(), 2);
    QCOMPARE_EQ(graph->in_edges(r->id(1)).size(), 1);
    QCOMPARE_EQ(graph->in_edges(r->id(2)).size(), 1);
}

void TestMindMap::testGraphConstructionMultipleLinks_footnote2() {
    auto text = R"(
[fn:target1] Description

Paragraph [fn:target1] [fn:target2]

[fn:target2] Description
)"_ss;


    {
        OrgStore s;
        s.addRoot(text);
        Graph graph{&s, nullptr};

        { // dry run adding all nodes in the graph. `getNodeInsert` returns
          // an IR representation of the node where all links present are
          // marked as 'unresolved'
            auto n0 = graph.getNodeInsert(s.getBox0({0}));
            QCOMPARE_EQ(n0->unresolved.size(), 0);
            auto n1 = graph.getNodeInsert(s.getBox0({1}));
            QCOMPARE_EQ(n1->unresolved.size(), 2);
            auto n2 = graph.getNodeInsert(s.getBox0({2}));
            QCOMPARE_EQ(n2->unresolved.size(), 0);
        }

        // Add the first box with footnote definition
        graph.addBox(s.getBox0({0}));
        QCOMPARE_EQ(graph.numNodes(), 1);
        QCOMPARE_EQ(graph.numEdges(), 0);
        QCOMPARE_EQ(graph.state.unresolved.size(), 0);

        { // Dry run second node insertion
            auto n1 = graph.getNodeInsert(s.getBox0({1}));
            QVERIFY(n1.has_value());
            // "get node insert" does not resolve the links, so the result
            // will stay the same
            QCOMPARE_EQ(n1->unresolved.size(), 2);
            // 'get unresolved' splits the block of unresolved links into
            // an updated graph node value and a list of resolved nodes.
            auto n1edit = graph.state.getUnresolvedEdits(n1.value());
            // Can resolve link targeting the first paragraph
            QCOMPARE_EQ(n1edit.resolved.size(), 1);
            QCOMPARE_EQ(n1edit.resolved.at(0).target, s.getBox0({0}));
            // Second paragraph link still cannot be resolved
            QCOMPARE_EQ(n1edit.node.unresolved.size(), 1);
        }

        // Add the second box with outgoing links
        graph.addBox(s.getBox0({1}));
        {
            // It must resolve one link in the paragraph, the other one
            // stays the same
            QCOMPARE_EQ(
                graph.getNodeProp(s.getBox0({1})).unresolved.size(), 1);
            QVERIFY(graph.hasEdge(s.getBox0({1}), s.getBox0({0})));
        }


        QCOMPARE_EQ(graph.numNodes(), 2);
        // The first link must be resolved by this time, the graph has
        // target information
        QCOMPARE_EQ(graph.numEdges(), 1);
        QCOMPARE_EQ(graph.state.unresolved.size(), 1);
        QCOMPARE_EQ(
            graph.getNodeProp(s.getBox0({0})).unresolved.size(), 0);
        QCOMPARE_EQ(
            graph.getNodeProp(s.getBox0({1})).unresolved.size(), 1);


        graph.addBox(s.getBox0({2}));
        QCOMPARE_EQ(graph.numNodes(), 3);
        QCOMPARE_EQ(graph.numEdges(), 2);
        QCOMPARE_EQ(graph.state.unresolved.size(), 0);
        QCOMPARE_EQ(
            graph.getNodeProp(s.getBox0({1})).unresolved.size(), 0);
        QVERIFY(graph.hasEdge(s.getBox0({1}), s.getBox0({0})));
        QVERIFY(graph.hasEdge(s.getBox0({1}), s.getBox0({2})));
    }

    // Test with bulk addition
    {
        OrgStore s;
        s.addRoot(text);
        Graph graph{&s, nullptr};
        graph.addFullStore();

        QCOMPARE_EQ(graph.numNodes(), 4);
        QCOMPARE_EQ(graph.numEdges(), 2);
        QCOMPARE_EQ(graph.in_edges(s.getBox0({0})).size(), 1);
        QCOMPARE_EQ(graph.out_edges(s.getBox0({1})).size(), 2);
        QCOMPARE_EQ(graph.in_edges(s.getBox0({2})).size(), 1);
    }

    // Test with signal-based element add
    {
        OrgStore s;
        Graph    graph{&s, nullptr};
        graph.connectStore();
        s.addRoot(text);

        QCOMPARE_EQ(graph.numNodes(), 4);
        QCOMPARE_EQ(graph.numEdges(), 2);
        QCOMPARE_EQ(graph.in_edges(s.getBox0({0})).size(), 1);
        QCOMPARE_EQ(graph.out_edges(s.getBox0({1})).size(), 2);
        QCOMPARE_EQ(graph.in_edges(s.getBox0({2})).size(), 1);
    }
}

void TestMindMap::testGraphConstructionSubtree_description_lists() {
    Str text{R"(
* Subtree1
  :properties:
  :id: subtree-1
  :end:

- [[id:subtree-2]] :: Forward link

* Subtree2
  :properties:
  :id: subtree-2
  :end:

- [[id:subtree-1]] :: Backlink

)"};


    {
        OrgStore store;
        store.addRoot(text);
        auto r = store.getRoot(0);
        writeFile(
            "/tmp/testGraphConstructionSubtree_description_lists.txt",
            ExporterTree::treeRepr(store.getBoxedNode(r->boxId))
                .toString(false));

        auto count = [](this auto&&  self,
                        OrgTreeNode* node) -> Vec<sem::SemId<sem::Org>> {
            Vec<sem::SemId<sem::Org>> result{node->getBoxedNode()};
            for (auto const& sub : node->subnodes) {
                result.append(self(sub.get()));
            }
            return result;
        };

        // List items and paragraphs are stored as separate boxed nodes.
        auto res = count(r);
        QCOMPARE_EQ2(res.at(0)->getKind(), osk::Document);
        QCOMPARE_EQ2(res.at(1)->getKind(), osk::Subtree);
        QCOMPARE_EQ2(res.at(2)->getKind(), osk::List);
        QCOMPARE_EQ2(res.at(3)->getKind(), osk::ListItem);
        QCOMPARE_EQ2(res.at(4)->getKind(), osk::Paragraph);
        QCOMPARE_EQ2(res.at(5)->getKind(), osk::Subtree);
        QCOMPARE_EQ2(res.at(6)->getKind(), osk::List);
        QCOMPARE_EQ2(res.at(7)->getKind(), osk::ListItem);
        QCOMPARE_EQ2(res.at(8)->getKind(), osk::Paragraph);

        QCOMPARE_EQ(res.size(), 9);
    }

    {
        OrgStore store;
        Graph    graph{&store, nullptr};
        store.addRoot(text);

        graph.state.debug = true;
        auto n0           = graph.getNodeInsert(store.getBox0({0}));
        QVERIFY(n0.has_value());
        QCOMPARE_EQ(n0->unresolved.size(), 1);

        auto n1 = graph.getNodeInsert(store.getBox0({1}));
        QVERIFY(n1.has_value());
        QCOMPARE_EQ(n1->unresolved.size(), 1);

        graph.addBox(store.getBox0({0}));
        QCOMPARE_EQ(graph.numNodes(), 1);
        QCOMPARE_EQ(graph.numEdges(), 0);
        QCOMPARE_EQ(
            graph.getNodeProp(store.getBox0({0})).unresolved.size(), 1);

        graph.addBox(store.getBox0({1}));
        QCOMPARE_EQ(graph.numNodes(), 2);
        QCOMPARE_EQ(
            graph.getNodeProp(store.getBox0({0})).unresolved.size(), 0);
        QCOMPARE_EQ(
            graph.getNodeProp(store.getBox0({1})).unresolved.size(), 0);
        QCOMPARE_EQ(graph.numEdges(), 2);
    }

    {
        OrgStore store;
        Graph    graph{&store, nullptr};

        store.addRoot(text);
        auto r = store.getRoot(0);

        QCOMPARE_EQ2(r->getBoxedNode()->getKind(), osk::Document);
        QCOMPARE_EQ2(r->subnodes.size(), 2);
        QCOMPARE_EQ2(r->at(0)->getBoxedNode()->getKind(), osk::Subtree);
        QCOMPARE_EQ2(r->at(1)->getBoxedNode()->getKind(), osk::Subtree);

        QCOMPARE_EQ2(r->at(0)->subnodes.size(), 1);
        QCOMPARE_EQ2(r->at({0, 0})->getBoxedNode()->getKind(), osk::List);
        QCOMPARE_EQ2(
            r->at({0, 0, 0})->getBoxedNode()->getKind(), osk::ListItem);
        QCOMPARE_EQ2(
            r->at({0, 0, 0, 0})->getBoxedNode()->getKind(),
            osk::Paragraph);

        QCOMPARE_EQ2(r->at(1)->subnodes.size(), 1);
        QCOMPARE_EQ2(r->at({1, 0})->getBoxedNode()->getKind(), osk::List);
        QCOMPARE_EQ2(
            r->at({1, 0, 0})->getBoxedNode()->getKind(), osk::ListItem);
        QCOMPARE_EQ2(
            r->at({1, 0, 0, 0})->getBoxedNode()->getKind(),
            osk::Paragraph);

        QVERIFY(graph.getNodeInsert(store.getBox0({0})).has_value());
        QVERIFY(!graph.getNodeInsert(store.getBox0({0, 0})).has_value());
        QVERIFY(
            !graph.getNodeInsert(store.getBox0({0, 0, 0})).has_value());
        QVERIFY(
            !graph.getNodeInsert(store.getBox0({0, 0, 0, 0})).has_value());
        QVERIFY(graph.getNodeInsert(store.getBox0({1})).has_value());
        QVERIFY(!graph.getNodeInsert(store.getBox0({1, 0})).has_value());
        QVERIFY(
            !graph.getNodeInsert(store.getBox0({1, 0, 0})).has_value());
        QVERIFY(
            !graph.getNodeInsert(store.getBox0({1, 0, 0, 0})).has_value());

        graph.addFullStore();

        QCOMPARE_EQ2(r->subnodes.size(), 2);
        QCOMPARE_EQ2(graph.numNodes(), 3);
        QCOMPARE_EQ2(graph.numEdges(), 2);
        QCOMPARE_EQ2(graph.out_edges(store.getBox0({0})).size(), 1);
        QCOMPARE_EQ2(graph.in_edges(store.getBox0({0})).size(), 1);
        QCOMPARE_EQ2(graph.out_edges(store.getBox0({1})).size(), 1);
        QCOMPARE_EQ2(graph.in_edges(store.getBox0({1})).size(), 1);
    }
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
[[id:c468e9c7-7422-4b17-8ccb-53575f186fe0][Annotation for the target subtree]]
[[id:XXSDASD][Unresolved subtree]]
)",
        // 1.2.1.1
        R"(
- Regular list element
- Two items in a list
)",
    };
    return join("", text);
}

void TestMindMap::testFullMindMapGraph() {
    auto [store, graph] = build_graph(getFullMindMapText());
    auto r              = store->getRoot(0);

    // qDebug().noquote() <<
    graph->toGraphviz();

    QCOMPARE_EQ2(graph->state.unresolved.size(), 1);
    QCOMPARE_EQ2(store->getBoxedNode(r->id(0))->getKind(), osk::Subtree);
    QCOMPARE_EQ2(
        store->getBoxedNode(r->id({0, 0}))->getKind(), osk::Subtree);
    QCOMPARE_EQ2(
        store->getBoxedNode(r->id({0, 1}))->getKind(), osk::Subtree);
    QCOMPARE_EQ2(
        store->getBoxedNode(r->id({0, 1, 0}))->getKind(), osk::Paragraph);

    // Description list with annotations for links
    // List itself is also a part of the node structure
    QCOMPARE_EQ2(
        store->getBoxedNode(r->id({0, 1, 1}))->getKind(), osk::List);
    // List contains one or more nested list items
    QCOMPARE_EQ2(
        store->getBoxedNode(r->id({0, 1, 1, 0}))->getKind(),
        osk::ListItem);

    // And then the list item is subdivided into individual paragraphs
    QCOMPARE_EQ2(
        store->getBoxedNode(r->id({0, 1, 1, 0, 0}))->getKind(),
        osk::Paragraph);
    QCOMPARE_EQ2(
        store->getBoxedNode(r->id({0, 1, 1, 0, 1}))->getKind(),
        osk::Paragraph);

    QCOMPARE_EQ2(
        store->getBoxedNode(r->id({0, 1, 2}))->getKind(), osk::Paragraph);
    QCOMPARE_EQ2(
        store->getBoxedNode(r->id({0, 1, 3}))->getKind(),
        osk::AnnotatedParagraph);
    QCOMPARE_EQ2(
        store->getBoxedNode(r->id({0, 1, 4}))->getKind(),
        osk::AnnotatedParagraph);
    QCOMPARE_EQ2(store->getBoxedNode(r->id(1))->getKind(), osk::Subtree);

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
                .link.description.value()),
        "links");
    QCOMPARE_EQ(
        str(graph->out_edge0(r->id(par_010), r->id({0, 2}))
                .link.description.value()),
        "rows");
    QCOMPARE_EQ(
        str(graph->out_edge0(r->id(par_010), r->id({1, 1}))
                .link.description.value()),
        "other");

    writeFile("/tmp/testFullMindMapGraph.dot", graph->toGraphviz());

    QCOMPARE_EQ(graph->in_edges(r->id({0, 2})).size(), 2);
    {
        auto desc = graph->out_edge0(r->id({0, 1}), r->id({0, 0}))
                        .link.description.value();
        auto desc_str = str(desc);
        QVERIFY(desc_str.contains(
            "Description lists can be used for annotated links"));
        QVERIFY(desc_str.contains("Multiple paragraphs attached to link"));
    }

    {
        Vec<Str> node_text //
            = graph->state.nodes | rv::transform([&](VDesc desc) -> Str {
                  auto node = store->nodeWithoutNested(
                      graph->getNodeProp(desc).box);
                  return str(node);
              })
            | rs::to<Vec>();

        Vec<Str> edge_text //
            = graph->state.edges
            | rv::transform([&](EDesc desc) -> Opt<Str> {
                  if (graph->getEdgeProp(desc).link.description) {
                      return str(
                          *graph->getEdgeProp(desc).link.description);
                  } else {
                      return std::nullopt;
                  }
              })
            | drop_if_nullopt() //
            | unpack_optional() //
            | rs::to<Vec>();

        auto get_idx = [](CVec<Str> list, CR<Str> str) -> int {
            auto it = rs::find_if(
                list, [&](CR<Str> item) { return item.contains(str); });

            return it == list.end() ? -1 : std::distance(list.begin(), it);
        };

        std::stringstream os;
        for (auto const& it : node_text) { os << "NODE " << it << "\n"; }
        for (auto const& it : edge_text) { os << "EDGE " << it << "\n"; }
        auto  dbg_str = os.str();
        char* dbg     = dbg_str.data();


        // clang-format off
        QVERIFY2(get_idx(node_text, "Mind map nodes are made from subtrees") != -1, dbg);

        // Annotation in the description list items are moved into the edge properties and
        // are not stored as separate nodes in graph.
        int list_desc_index = get_idx(edge_text, "Description lists can be used for annotated links");
        QVERIFY2(list_desc_index != -1, dbg);
        QVERIFY2(edge_text.at(list_desc_index).contains("Multiple paragraphs attached to link"), dbg);
        QVERIFY2(get_idx(node_text, "Description lists can be used for annotated links") == -1, dbg);
        QVERIFY2(get_idx(node_text, "Multiple paragraphs attached to link") == -1, dbg);

        // clang-format on
    }
}

void TestMindMap::testQtGraphModel1() {
    auto [store, graph] = build_graph(R"(
Paragraph [[id:subtree-id]]

* Subtree
  :properties:
  :id: subtree-id
  :end:
)");

    printModelTree(
        graph.get(), QModelIndex(), store_index_printer(store.get()))
        .toString();

    GraphLayoutProxy proxy{
        store.get(),
        GraphLayoutProxy::LayoutConfig{
            .getNodeSize = [](QModelIndex const&) -> QSize {
                return QSize(20, 20);
            },
        },
        nullptr,
    };

    proxy.setSourceModel(graph.get());
    proxy.updateCurrentLayout();
}

void debugModel(
    QAbstractItemModel* model,
    OrgStore*           store,
    Opt<Str>            path             = std::nullopt,
    bool                ignoreExceptions = false) {
    Str text = printModelTree(
                   model,
                   QModelIndex(),
                   store_index_printer(store),
                   ignoreExceptions)
                   .toString(!path.has_value());
    if (path) {
        writeFile(fs::path{path->toBase()}, text);
        qDebug().noquote() << "Wrote tree to" << path.value();
    } else {
        std::cout << text << std::endl;
    }
}

struct SceneBench {
    SPtr<OrgStore>         store;
    SPtr<Graph>            graph;
    SPtr<GraphLayoutProxy> proxy;
    OrgGraphView*          view;
    SPtr<QMainWindow>      window;

    SceneBench(CR<Str> text) {
        window = std::make_shared<QMainWindow>();
        window->show();
        window->raise();
        window->activateWindow();

        auto [store, graph] = build_graph(text);
        this->store         = store;
        this->graph         = graph;

        proxy = std::make_shared<GraphLayoutProxy>(
            store.get(),
            GraphLayoutProxy::LayoutConfig{
                .getNodeSize =
                    [&](QModelIndex const& index) {
                        return view->getNodeSize(index);
                    },
                .getEdgeLabelSize =
                    [&](QModelIndex const& index) {
                        return view->getNodeSize(index);
                    },
            },
            nullptr);

        proxy->setSourceModel(graph.get());
        view = new OrgGraphView(proxy.get(), store.get(), window.get());

        view->setStyleSheet("OrgGraphView { border: none; }");
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setContentsMargins(0, 0, 0, 0);

        window->setContentsMargins(0, 0, 0, 0);
        window->setCentralWidget(view);
        proxy->updateCurrentLayout();
        view->rebuildScene();

        QSize box = proxy->currentLayout.bbox.size();
        box       = box.grownBy(QMargins(20, 20, 20, 20));
        window->resize(box);
        QTest::qWait(100);
        Q_ASSERT(QTest::qWaitForWindowActive(window.get()));
        Q_ASSERT_X(
            window->size() == box,
            "init bench",
            fmt("{} != {}",
                qdebug_to_str(window->size()),
                qdebug_to_str(box)));
    }

    void debugModel(CR<Opt<Str>> path = std::nullopt) {
        ::debugModel(graph.get(), store.get(), path);
    }

    void debugProxy(Opt<Str> path = std::nullopt) {
        ::debugModel(proxy.get(), store.get(), path);
    }
};

void TestMindMap::testQtGraphScene1() {
    SceneBench b{R"(
Paragraph [[id:subtree-id]]

* Subtree
  :properties:
  :id: subtree-id
  :end:
)"};

    save_screenshot("/tmp/graph_screenshot.png");
}

void TestMindMap::testQtGraphSceneFullMindMap() {
    SceneBench b{getFullMindMapText()};
    save_screenshot(
        b.window.get(), "/tmp/full_mind_map_screenshot_pre_filter.png", 2);

    GraphFilterProxy pre_layout_filter{};

    pre_layout_filter.accept_edge = [](EDesc edge) { return true; };

    pre_layout_filter.accept_node = [&](VDesc node) {
        auto sem_node = b.graph->getNodeSem(node);
        return !SemSet{osk::ListItem, osk::List, osk::Document}.contains(
            sem_node->getKind());
    };

    pre_layout_filter.setSourceModel(b.graph.get());
    b.proxy->setSourceModel(&pre_layout_filter);
    b.proxy->updateCurrentLayout();
    b.view->setModel(b.proxy.get());
    b.view->rebuildScene();

    b.window->resize(b.proxy->currentLayout.bbox.size().grownBy(
        QMargins(100, 100, 100, 100)));

    save_screenshot(
        b.window.get(), "/tmp/full_mind_map_screenshot.png", 2);

    pre_layout_filter.setObjectName("pre_layout_filter");
    b.graph->setObjectName("base_graph");
    b.proxy->setObjectName("layout_proxy");
    b.proxy->config.clusterSubtrees = true;
    b.proxy->config.getSubgraphMargin =
        [](QModelIndex const& index) -> Opt<int> { return 15; };
    b.proxy->updateCurrentLayout();
    b.view->rebuildScene();

    b.window->resize(b.proxy->currentLayout.bbox.size().grownBy(
        QMargins(100, 100, 100, 100)));

    ::debugModel(
        b.graph.get(),
        b.store.get(),
        "/tmp/testQtGraphSceneFullMindMap_filter_graph.txt");


    ::debugModel(
        &pre_layout_filter,
        b.store.get(),
        "/tmp/testQtGraphSceneFullMindMap_filter_pre_layout.txt");

    ::debugModel(
        b.proxy.get(),
        b.store.get(),
        "/tmp/testQtGraphSceneFullMindMap_filter_layout_proxy.txt",
        true);

    {

        auto const& lyt = std::get<GraphLayoutIR::GraphvizResult>(
            b.proxy->currentLayout.original);

        lyt.writeSvg("/tmp/testQtGraphSceneFullMindMap_cluster.svg");
        lyt.writeXDot("/tmp/testQtGraphSceneFullMindMap_cluster.xdot");
    }

    save_screenshot(
        b.window.get(), "/tmp/full_mind_map_screenshot_clusters.png", 2);
}

void TestMindMap::testMindMapNodeAdd1() {
    OrgStore store;
    Graph    graph{&store, nullptr};
    graph.connectStore();
    auto node = sem::parseString(R"(
* Subtree
* Second subtree
)");

    QSignalSpy store_spy{&store, &OrgStore::boxAdded};
    QSignalSpy graph_spy{&graph, &Graph::nodeAdded};

    Vec<OrgBoxId> added;
    QObject::connect(&store, &OrgStore::boxAdded, [&](OrgBoxId id) {
        added.push_back(id);
    });

    store.addRoot(node);
    QCOMPARE_EQ(added.size(), 3);
    QCOMPARE_EQ(store_spy.count(), 3);
    QCOMPARE_EQ(graph_spy.count(), 3);
}

void TestMindMap::testMindMapNodeAddRemoveAdd() {
    OrgStore store;
    Graph    graph{&store, nullptr};
    Str      text{R"(
* Subtree1
  :properties:
  :id: subtree-1
  :end:

- [[id:subtree-2]] :: Forward link

* Subtree2
  :properties:
  :id: subtree-2
  :end:

- [[id:subtree-1]] :: Backlink

)"};

    store.addRoot(text);

    auto b0 = store.getBox0({0});
    auto b1 = store.getBox0({1});

    graph.addBox(b0);
    QCOMPARE_EQ(graph.numNodes(), 1);
    QCOMPARE_EQ(graph.numEdges(), 0);
    QCOMPARE_EQ(graph.getNodeProp(b0).unresolved.size(), 1);
    QVERIFY(graph.state.unresolved.contains(b0));
    QCOMPARE_EQ(graph.state.nodes.size(), 1);
    QCOMPARE_EQ(graph.state.edges.size(), 0);


    { // pre-existing mappings should have stable vertex IDs so old boxes
      // would point to the same graph elements/properties
        auto v0 = graph.getBoxDesc(b0);
        graph.addBox(b1);
        QCOMPARE_EQ(v0, graph.getBoxDesc(b0));
    }

    QCOMPARE_EQ(graph.numNodes(), 2);
    QCOMPARE_EQ(graph.numEdges(), 2);
    QCOMPARE_EQ(graph.getNodeProp(b1).unresolved.size(), 0);
    QCOMPARE_EQ(graph.getNodeProp(b0).unresolved.size(), 0);
    QCOMPARE_EQ(graph.in_edges(b0).size(), 1);
    QCOMPARE_EQ(graph.in_edges(b1).size(), 1);
    QCOMPARE_EQ(graph.state.unresolved.size(), 0);
    QCOMPARE_EQ(graph.state.nodes.size(), 2);
    QCOMPARE_EQ(graph.state.edges.size(), 2);

    // adding second box closes all unresolved state for all nodes
    QVERIFY(!graph.state.unresolved.contains(b1));
    QVERIFY(!graph.state.unresolved.contains(b0));

    QCOMPARE_EQ(
        graph.getEdgeProp(b0, b1).link.link->getId().text, "subtree-2");
    QCOMPARE_EQ(
        graph.getEdgeProp(b1, b0).link.link->getId().text, "subtree-1");

    graph.deleteBox(b0);
    // Deleting box removes a node and all associated in/out edges.
    QCOMPARE_EQ(graph.numNodes(), 1);
    QCOMPARE_EQ(graph.numEdges(), 0);
    QCOMPARE_EQ(graph.state.nodes.size(), 1);
    QCOMPARE_EQ(graph.state.edges.size(), 0);
    // Node pointing back to the subtree-1 is now unresolved again
    QCOMPARE_EQ(graph.getNodeProp(b1).unresolved.size(), 1);
    // Details about unresolved link are put in the graph property, box ID
    // is also stored in the full unresolved list.
    QCOMPARE_EQ(graph.state.unresolved.size(), 1);
    QVERIFY(graph.state.unresolved.contains(b1));
    QVERIFY(!graph.state.unresolved.contains(b0));

    // moving link from resolved back to unresolved should not mess up
    // ordering etc.
    QCOMPARE_EQ(
        graph.getNodeProp(b1).unresolved.at(0).link->getId().text,
        "subtree-1");

    // Box->vertex mapping is updated.
    QVERIFY(!graph.state.boxToVertex.contains(b0));
    QVERIFY(graph.state.boxToVertex.contains(b1));

    { // NOTE: This test is an example of clunkiness of the current design.
      // There is no clean way to dry run the node insertion with the
      // information node itself provides. `addBox` will insert all the
      // required elements and then it will resolve all targets.

        auto n0 = graph.getNodeInsert(b0);
        QCOMPARE_EQ(n0->unresolved.size(), 1);
        QCOMPARE_EQ(n0->unresolved.at(0).link->getId().text, "subtree-2");

        // Dry run of the data insertion with unchanged graph mappings
        auto n0_edit = graph.state.getUnresolvedEdits(n0.value());
        // Subtree1 has one unresolved link that will find the subtree-2
        // target
        QCOMPARE_EQ(n0_edit.node.unresolved.size(), 0);
        QCOMPARE_EQ(n0_edit.resolved.size(), 1);
        auto n0_link = n0_edit.resolved.at(0);
        // Getting edits does not change the existing unresolved state
        QCOMPARE_EQ(graph.state.unresolved.size(), 1);
        QCOMPARE_EQ2(n0_link.source, b0);
        QCOMPARE_EQ2(n0_link.target, b1);
        QCOMPARE_EQ(n0_link.link.link->getId().text, "subtree-2");
    }

    graph.state.debug = true;
    graph.addBox(b0);
    QCOMPARE_EQ(graph.state.nodes.size(), 2);
    QCOMPARE_EQ(graph.state.edges.size(), 2);
    QCOMPARE_EQ(graph.numNodes(), 2);
    QCOMPARE_EQ(graph.numEdges(), 2);
    QCOMPARE_EQ(graph.getNodeProp(b1).unresolved.size(), 0);
    QCOMPARE_EQ(graph.getNodeProp(b0).unresolved.size(), 0);
    QCOMPARE_EQ(graph.state.unresolved.size(), 0);
}

void TestMindMap::testMindMapSignals1() {
    OrgStore store;
    Graph    graph{&store, nullptr};
    graph.connectStore();
    auto node = sem::parseString(R"(
Paragraph [[id:subtree-id]]

* Subtree
  :properties:
  :id: subtree-id
  :end:
)");

    {
        QSignalSpy store_spy{&store, &OrgStore::boxAdded};
        QSignalSpy graph_spy{&graph, &Graph::edgeAdded};

        store.addRoot(node);

        QCOMPARE_EQ(store_spy.count(), 3);
        QCOMPARE_EQ(graph_spy.count(), 1);
        auto subtree_box   = store.getRoot(0)->at(1)->boxId;
        auto paragraph_box = store.getRoot(0)->at(0)->boxId;

        QCOMPARE_EQ(graph.in_edges(subtree_box).size(), 1);
        QCOMPARE_EQ(graph.out_edges(paragraph_box).size(), 1);
    }

    {
        QSignalSpy node_update_spy{&graph, &Graph::nodeUpdated};
        QSignalSpy edge_remove_spy{&graph, &Graph::edgeRemoved};

        {
            OrgBoxId paragraph_box = store.roots.at(0)->at(0)->boxId;
            QCOMPARE_EQ(
                store.getBoxedNode(paragraph_box)->getKind(),
                osk::Paragraph);
            auto new_text = sem::parseString("Paragraph without edge")
                                ->at(0);
            QCOMPARE_EQ(new_text->getKind(), osk::Paragraph);
            store.update<sem::Paragraph>(
                paragraph_box, [&](sem::Paragraph& prev) {
                    prev = *new_text.getAs<sem::Paragraph>();
                });
        }

        {
            auto subtree_box   = store.getRoot(0)->at(1)->boxId;
            auto paragraph_box = store.getRoot(0)->at(0)->boxId;

            QCOMPARE_EQ(edge_remove_spy.count(), 1);
            QCOMPARE_EQ(graph.in_edges(subtree_box).size(), 0);
            QCOMPARE_EQ(graph.out_edges(paragraph_box).size(), 0);
        }
    }
}
