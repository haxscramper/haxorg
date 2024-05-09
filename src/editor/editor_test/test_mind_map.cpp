#include "test_mind_map.hpp"

#include <editor/editor_lib/org_graph_layout.hpp>


#include <QRect>
#include <hstd/stdlib/Ranges.hpp>
#include <editor/editor_lib/org_graph_model.hpp>
#include <editor/editor_lib/org_graph_scene.hpp>

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

    // qDebug().noquote() <<
    graph->toGraphviz();

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
        Vec<Str> node_text //
            = gen_view(graph->nodes())
            | rv::transform([&](OrgGraph::VDesc desc) -> Str {
                  auto node = store->nodeWithoutNested(
                      graph->node(desc).box);
                  return str(node);
              })
            | rs::to<Vec>();

        Vec<Str> edge_text //
            = gen_view(graph->edges())
            | rv::transform([&](OrgGraph::EDesc desc) -> Opt<Str> {
                  if (graph->edge(desc).description) {
                      return str(*graph->edge(desc).description);
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

    OrgGraphModel model{graph.get(), nullptr};
    printModelTree(&model, QModelIndex(), store_index_printer(store.get()))
        .toString();

    OrgGraphLayoutProxy proxy{};
    proxy.setSourceModel(&model);
    proxy.updateCurrentLayout();
}

struct SceneBench {
    SPtr<OrgStore>            store;
    SPtr<OrgGraph>            graph;
    SPtr<OrgGraphModel>       model;
    SPtr<OrgGraphLayoutProxy> proxy;
    OrgGraphView*             view;
    SPtr<QMainWindow>         window;

    SceneBench(CR<Str> text) {
        window = std::make_shared<QMainWindow>();
        window->show();
        window->raise();
        window->activateWindow();

        auto [store, graph] = build_graph(text);
        this->store         = store;
        this->graph         = graph;

        model = std::make_shared<OrgGraphModel>(graph.get(), nullptr);

        proxy = std::make_shared<OrgGraphLayoutProxy>();
        proxy->setSourceModel(model.get());
        proxy->updateCurrentLayout();
        view = new OrgGraphView(proxy.get(), store.get(), window.get());


        window->setContentsMargins(0, 0, 0, 0);
        window->setCentralWidget(view);

        QSize const& box = proxy->currentLayout.bbox.size();
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

    void debugModel() {
        std::cout << printModelTree(
                         model.get(),
                         QModelIndex(),
                         store_index_printer(store.get()))
                         .toString()
                  << std::endl;
    }

    void debugProxy() {
        std::cout << printModelTree(
                         proxy.get(),
                         QModelIndex(),
                         store_index_printer(store.get()))
                         .toString()
                  << std::endl;
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
    // b.debugProxy();
    auto const& lyt = std::get<GraphLayoutIR::GraphvizResult>(
        b.proxy->currentLayout.original);

    lyt.writeSvg("/tmp/testQtGraphSceneFullMindMap.svg");
    lyt.writeXDot("/tmp/testQtGraphSceneFullMindMap.xdot");

    save_screenshot(b.window.get(), "/tmp/full_mind_map_screenshot.png");
}
