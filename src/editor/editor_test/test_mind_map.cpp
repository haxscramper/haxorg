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

#include <QMetaMethod>
#include <QCoreApplication>
#include <QObject>
#include <QDebug>
#include <QMetaMethod>
#include <QMetaObject>

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

        // graph.state.debug = true;
        auto n0 = graph.getNodeInsert(store.getBox0({0}));
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

void TestMindMap::testGraphConstructionLoose_end_origin() {
    auto text = R"(
Paragraph [fn:target1]

Paragraph [fn:target2]
)"_ss;


    OrgStore s;
    s.addRoot(text);
    Graph graph{&s, nullptr};

    auto b0 = s.getBox0({0});
    auto b1 = s.getBox0({1});
    graph.addBox(b0);
    QCOMPARE_EQ(graph.state.unresolved.size(), 1);
    QCOMPARE_EQ(graph.state.boxToVertex.size(), 1);
    QCOMPARE_EQ(graph.getNodeProp(b0).unresolved.size(), 1);
    QCOMPARE_EQ(
        graph.getNodeProp(b0).unresolved.at(0).link->getFootnote().target,
        "target1");

    graph.addBox(b1);
    QCOMPARE_EQ(graph.state.unresolved.size(), 2);
    QCOMPARE_EQ(graph.state.boxToVertex.size(), 2);
    QCOMPARE_EQ(graph.getNodeProp(b1).unresolved.size(), 1);
    QCOMPARE_EQ(
        graph.getNodeProp(b1).unresolved.at(0).link->getFootnote().target,
        "target2");

    graph.deleteBox(b0);
    QCOMPARE_EQ(graph.state.unresolved.size(), 1);
    QCOMPARE_EQ(graph.state.boxToVertex.size(), 1);

    graph.addBox(b0);
    QCOMPARE_EQ(graph.state.unresolved.size(), 2);
    QCOMPARE_EQ(graph.state.boxToVertex.size(), 2);
    QCOMPARE_EQ(graph.getNodeProp(b1).unresolved.size(), 1);
    QCOMPARE_EQ(
        graph.getNodeProp(b1).unresolved.at(0).link->getFootnote().target,
        "target2");
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
        // 1.2.2
        R"(
*** Intercluster links are possible
)",
        // 1.2.2.0
        R"(
[[id:c468e9c7-7422-4b17-8ccb-53575f186fe0][Annotation for the target subtree]]
[[id:XXSDASD][Unresolved subtree]]
)",
        // 1.2.2.1
        // 1.2.2.1.0
        "- ",
        // 1.2.2.1.0.0
        "Regular list element\n",
        // 1.2.2.1.1
        "- ",
        // 1.2.2.1.1.0
        "Two items in a list\n",
    };
    return join("", text);
}

Str getSubtreeTestText() {
    return R"(
* Title

** Introduction
This document demonstrates various Org-mode elements and internal linking.

** Section 1
:PROPERTIES:
:ID: section-1
:END:

Some introductory text for Section 1.[fn:1]

*** Subsection 1.1
:PROPERTIES:
:ID: subsection-1.1
:END:

Detailed information for Subsection 1.1.

- Item 1
- Item 2
- Item 3

[fn:1] Footnote for Section 1.

*** Subsection 1.2
:PROPERTIES:
:ID: subsection-1.2
:END:

Detailed information for Subsection 1.2. More details in [[id:subsection-1.1]].

- Item A
  - Subitem A1
  - Subitem A2
- Item B

** Section 2
:PROPERTIES:
:ID: section-2
:END:

Text for Section 2 with a footnote reference.[fn:2]

*** Subsection 2.1
:PROPERTIES:
:ID: subsection-2.1
:END:

Details for Subsection 2.1. See [[id:section-2]].

- Task 1
  - Subtask 1a
  - Subtask 1b
- Task 2

[fn:2] Footnote for Section 2.

*** Subsection 2.2
:PROPERTIES:
:ID: subsection-2.2
:END:

Information for Subsection 2.2, referring to [[id:section-1]].

** Section 3
:PROPERTIES:
:ID: section-3
:END:

Discussion in Section 3. See notes in [[id:subsection-2.2]].[fn:3]

*** Subsection 3.1
:PROPERTIES:
:ID: subsection-3.1
:END:

Content for Subsection 3.1. Reference to [[id:section-3]].

- Point 1
- Point 2
- Point 3

[fn:3] Footnote for Section 3.

*** Subsection 3.2
:PROPERTIES:
:ID: subsection-3.2
:END:

Details for Subsection 3.2. Linking back to [[id:subsection-3.1]].

- Item X
  - Subitem X1
  - Subitem X2
- Item Y

** Section 4
:PROPERTIES:
:ID: section-4
:END:

Text for Section 4 with a footnote.[fn:4]

*** Subsection 4.1
:PROPERTIES:
:ID: subsection-4.1
:END:

Description for Subsection 4.1, see [[id:section-4]].

- List item 1
  - Nested item 1a
  - Nested item 1b
- List item 2

[fn:4] Footnote for Section 4.

*** Subsection 4.2
:PROPERTIES:
:ID: subsection-4.2
:END:

Content for Subsection 4.2. Refer to [[id:subsection-4.1]].

- Element A
  - Detail A1
  - Detail A2
- Element B

** Section 5
:PROPERTIES:
:ID: section-5
:END:

Information in Section 5, referencing [[id:subsection-4.2]].[fn:5]

*** Subsection 5.1
:PROPERTIES:
:ID: subsection-5.1
:END:

Content for Subsection 5.1. Check details in [[id:section-5]].

- Task X
  - Step X1
  - Step X2
- Task Y

[fn:5] Footnote for Section 5.

*** Subsection 5.2
:PROPERTIES:
:ID: subsection-5.2
:END:

Details for Subsection 5.2. Reference to [[id:subsection-5.1]].

- Point A
  - Subpoint A1
  - Subpoint A2
- Point B

** Conclusion
Summary and final notes. Refer to [[id:section-5]] for more information.
)";
}

Str getNestedFootnoteText() {
    return R"(
* Main Title

This is the main paragraph with a reference to a footnote.[fn:1]

[fn:1] This is the first footnote, which itself contains another footnote reference.[fn:2]

[fn:2] This is the second footnote, nested within the first footnote. It also contains a nested footnote.[fn:3]

[fn:3] This is the third footnote, nested within the second footnote. It also contains yet another nested footnote.[fn:4]

[fn:4] This is the fourth footnote, nested within the third footnote. It refers back to the main paragraph.

This is another paragraph in the main text with a footnote reference.[fn:5]

[fn:5] This is a footnote for the second paragraph, containing another nested footnote.[fn:6]

[fn:6] This is a nested footnote within the second paragraph's footnote. It also has a nested footnote.[fn:7]

[fn:7] This is another level of nested footnote. It contains one more nested footnote.[fn:8]

[fn:8] This is the deepest nested footnote in this sequence.

This is yet another paragraph in the main text with a footnote reference.[fn:9]

[fn:9] This is the footnote for the third paragraph. It contains a nested footnote.[fn:10]

[fn:10] This is the nested footnote within the third paragraph's footnote. It has another nested footnote.[fn:11]

[fn:11] Another level of nested footnote. It contains one more nested footnote.[fn:12]

[fn:12] The fourth level of nested footnote in this sequence.

Final paragraph in the main text with a footnote reference.[fn:13]

[fn:13] Footnote for the final paragraph. It contains a nested footnote.[fn:14]

[fn:14] Nested footnote within the final paragraph's footnote. It has another nested footnote.[fn:15]

[fn:15] Another level of nested footnote. It contains one more nested footnote.[fn:16]

[fn:16] The deepest nested footnote in this sequence, referring back to the main text.
)";
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
    proxy.setNewLayout();
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

/// \brief Common boilerplate to set the graph rendering scene
///
/// Default scene bench structure does not have graph filtering logic,
/// tests that need to add it, do so through `setSourceModel` etc.
struct SceneBench {
    SPtr<OrgStore>         store;
    SPtr<Graph>            graph;
    SPtr<GraphLayoutProxy> proxy;
    OrgGraphView*          view;
    SPtr<QMainWindow>      window;

    /// \brief Different graph layout algorithms generate differently sized
    /// bounding boxes for graph, even if nothing else has changed. This is
    /// used to readjust the window size to fit the whole graph scene.
    void adjustWindow() {
        window->resize(proxy->currentLayout.bbox.size().grownBy(
            QMargins(20, 20, 20, 20)));
    }

    void initWindow() {
        window = std::make_shared<QMainWindow>();
        window->show();
        window->raise();
        window->activateWindow();
    }

    void initProxy() {
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
    }

    void initView() {
        view = new OrgGraphView(proxy.get(), store.get(), window.get());

        view->setStyleSheet("OrgGraphView { border: none; }");
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setContentsMargins(0, 0, 0, 0);

        window->setContentsMargins(0, 0, 0, 0);
        window->setCentralWidget(view);
        proxy->connectModel();
        proxy->setNewLayout();
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

    SceneBench() { initWindow(); }

    /// \brief Build scene bench using already constructed graph and store.
    SceneBench(SPtr<OrgStore> in_store, SPtr<Graph> in_graph) {
        initWindow();

        this->store = in_store;
        this->graph = in_graph;

        initProxy();
        initView();
    }

    /// \brief Build scene bench using text, create a new store and a new
    /// graph in the bench
    SceneBench(CR<Str> text) {
        initWindow();

        auto [store, graph] = build_graph(text);
        this->store         = store;
        this->graph         = graph;

        initProxy();
        initView();
    }

    /// \brief Dump the tree representation of the base graph model into
    /// stdout or in the provided file, if not nullopt
    void debugModel(CR<Opt<Str>> path = std::nullopt) {
        ::debugModel(graph.get(), store.get(), path);
    }

    /// \brief Dump the graph layout proxy model to the stdout/file
    void debugProxy(Opt<Str> path = std::nullopt) {
        ::debugModel(proxy.get(), store.get(), path);
    }
};

/// \brief Initial sanity check for the graph structure
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

void TestMindMap::testLargeSubtreeGraph() {
    SceneBench b{getSubtreeTestText()};
    save_screenshot(b.window.get(), "/tmp/testLargeSubtreeGraph.png", 2);
    b.proxy->config.clusterSubtrees = true;
    b.proxy->resetLayoutData();
    b.adjustWindow();
    save_screenshot(
        b.window.get(), "/tmp/testLargeSubtreeGraph_clustered.png", 2);
}

void TestMindMap::testNestedFootnotesGraph() {
    SceneBench b{getNestedFootnoteText()};
    save_screenshot(
        b.window.get(), "/tmp/testNestedFootnotesGraph.png", 2);
}


/// \brief Find list of all graphics items that have a given rectangle in
/// their own bounding rect, and return then sorted on their area.
///
/// Used mainly for testing, getting overlapping clusters.
Vec<OrgGraphElementItem*> getFullyOverlappingItems(
    OrgGraphView* scene,
    const QRectF& rect) {

    Vec<OrgGraphElementItem*> matchingItems;

    for (OrgGraphElementItem* item : scene->graphItems()) {
        if (GraphIndex{item->index}.getKind()
            == OrgGraphElementKind::Subgraph) {
            auto bb = item->boundingRect();
            /* qDebug().noquote()
                 <<*/
            auto str = fmt(
                "rect:{} bbox:{} contains:{} points:{} neq:{} "
                "index:{}\nprint:{}",
                qdebug_to_str(rect),
                qdebug_to_str(item->sceneBoundingRect()),
                bb.contains(rect.topLeft()),
                fmt("{}-{} {}-{}",
                    bb.topLeft(),
                    bb.bottomRight(),
                    rect.topLeft(),
                    rect.bottomRight()),
                bb != rect,
                qdebug_to_str(item->index),
                printIndex(item->index).toString(false));
        }

        if (item->boundingRect().contains(rect)
            // Exclude the item itself
            && item->boundingRect() != rect) {
            matchingItems.push_back(item);
        }
    }

    std::sort(
        matchingItems.begin(),
        matchingItems.end(),
        [](OrgGraphElementItem* a, OrgGraphElementItem* b) {
            return a->boundingRect().width() * a->boundingRect().height()
                 < b->boundingRect().width() * b->boundingRect().height();
        });

    return matchingItems;
}

/// \brief Get all graph elements that are placed in a give rectangle,
/// excluding one that has exactly the same rectangle.
Vec<OrgGraphElementItem*> getItemsInRect(
    OrgGraphView* scene,
    QRectF const& rect) {
    Vec<OrgGraphElementItem*> result;
    for (OrgGraphElementItem* item : scene->graphItems()) {
        if (rect.contains(item->boundingRect())
            && item->boundingRect() != rect) {
            result.push_back(item);
        }
    }
    return result;
}

void TestMindMap::testQtGraphSceneFullMindMap() {
    SceneBench b{getFullMindMapText()};
    save_screenshot(
        b.window.get(), "/tmp/full_mind_map_screenshot_pre_filter.png", 2);

    GraphFilterProxy pre_layout_filter{};

    pre_layout_filter.accept_edge = [](EDesc edge) { return true; };

    // Omit list item nodes, list elemenst and the parent document from the
    // graph.
    pre_layout_filter.accept_node = [&](VDesc node) {
        auto sem_node = b.graph->getNodeSem(node);
        return !SemSet{osk::ListItem, osk::List, osk::Document}.contains(
            sem_node->getKind());
    };

    // Debug function to dump the full tree structure
    auto dump_all = [&](CR<Str> suffix) {
        ::debugModel(
            b.graph.get(),
            b.store.get(),
            "/tmp/testQtGraphSceneFullMindMap_filter_graph_"_ss + suffix
                + ".txt"_ss);


        ::debugModel(
            &pre_layout_filter,
            b.store.get(),
            "/tmp/testQtGraphSceneFullMindMap_filter_pre_layout_"_ss
                + suffix + ".txt"_ss);

        ::debugModel(
            b.proxy.get(),
            b.store.get(),
            "/tmp/testQtGraphSceneFullMindMap_filter_layout_proxy_"_ss
                + suffix + ".txt"_ss,
            true);
    };

    b.view->rebuildScene();

    pre_layout_filter.setSourceModel(b.graph.get());
    b.proxy->setSourceModel(&pre_layout_filter);
    b.proxy->resetLayoutData();
    // dump_all("1");
    b.view->setModel(b.proxy.get());
    b.view->rebuildScene();

    b.adjustWindow();

    save_screenshot(
        b.window.get(), "/tmp/full_mind_map_screenshot.png", 2);

    pre_layout_filter.setObjectName("pre_layout_filter");
    b.graph->setObjectName("base_graph");
    b.proxy->setObjectName("layout_proxy");

    // With clustering disabled, proxy layout will generate the same number
    // of elements as the base graph
    QCOMPARE_EQ(b.view->graphItems().size(), pre_layout_filter.rowCount());
    QCOMPARE_EQ(b.view->graphItems().size(), pre_layout_filter.rowCount());

    b.proxy->config.clusterSubtrees = true;
    b.proxy->config.getSubgraphMargin =
        [](QModelIndex const& index) -> Opt<int> { return 15; };
    b.proxy->resetLayoutData();

    // If clustering is disabled, the view will have more elements
    QCOMPARE_EQ(b.view->graphItems().size(), b.proxy->rowCount());
    QCOMPARE_LT(pre_layout_filter.rowCount(), b.view->graphItems().size());

    b.adjustWindow();


    {

        auto const& lyt = std::get<GraphLayoutIR::GraphvizResult>(
            b.proxy->currentLayout.original);

        lyt.writeSvg("/tmp/testQtGraphSceneFullMindMap_cluster.svg");
        lyt.writeXDot("/tmp/testQtGraphSceneFullMindMap_cluster.xdot");
    }

    save_screenshot(
        b.window.get(), "/tmp/full_mind_map_screenshot_clusters.png", 2);

    auto get_node_boxes =
        [](CVec<OrgGraphElementItem*> items) -> Vec<OrgBoxId> {
        return items //
             | rv::filter([](OrgGraphElementItem const* it) {
                   return GraphIndex{it->index}.getKind()
                       == OrgGraphElementKind::Node;
               })
             | rv::transform([](OrgGraphElementItem const* it) {
                   return GraphIndex{it->index}.getBox();
               })
             | rs::to<Vec>();
    };

    // Check subgraph and node placement.

    { // "More than one subtree can exist in cluster" -- 5 surrounding
      // nodes, 2 links.
        // Find 'target' node and search for surrounding clusters around it
        auto box  = b.store->getBox0({0, 1});
        auto item = b.view
                        ->graphItemForIndex(
                            b.graph->index(b.graph->getBoxIndex(box)))
                        .value();

        dump_all("dbg");
        auto clusters = getFullyOverlappingItems(
            b.view, item->boundingRect());


        QCOMPARE_EQ(clusters.size(), 2);
        QVERIFY(clusters.at(1)->boundingRect().contains(
            clusters.at(0)->boundingRect()));
        {
            auto adjacent = getItemsInRect(
                b.view, clusters.at(0)->boundingRect());

            for (auto const& cl : adjacent) {
                // qDebug().noquote() <<
                // printIndex(cl->index).toString(false);
            }

            Vec<OrgBoxId> boxes = get_node_boxes(adjacent);

            QCOMPARE_EQ(boxes.size(), 5);
            QVERIFY(boxes.contains(b.store->getBox0({0, 1})));
            QVERIFY(boxes.contains(b.store->getBox0({0, 1, 0})));
            // 0.1.1 is a description list item that is used to form an
            // edge between subtrees
            QVERIFY(!boxes.contains(b.store->getBox0({0, 1, 1})));
            QVERIFY(boxes.contains(b.store->getBox0({0, 1, 2})));
            QVERIFY(boxes.contains(b.store->getBox0({0, 1, 3})));
            QVERIFY(boxes.contains(b.store->getBox0({0, 1, 4})));
        }
    }

    { // "Two items in a list"
        auto box  = b.store->getBox0({1, 2, 2});
        auto item = b.view
                        ->graphItemForIndex(
                            b.graph->index(b.graph->getBoxIndex(box)))
                        .value();

        auto clusters = getFullyOverlappingItems(
            b.view, item->boundingRect());

        QCOMPARE_EQ(clusters.size(), 3);

        Vec<OrgBoxId> cluster_0{
            // Subtree node
            b.store->getBox0({1, 2, 2}),
            // Standalone paragraph
            b.store->getBox0({1, 2, 2, 0}),
            // paragraphs from list items
            b.store->getBox0({1, 2, 2, 1, 0, 0}),
            b.store->getBox0({1, 2, 2, 1, 1, 0}),
        };

        Vec<OrgBoxId> cluster_1{
            b.store->getBox0({1, 2}),
            b.store->getBox0({1, 2, 0}),
            b.store->getBox0({1, 2, 1}),
        };

        Vec<OrgBoxId> cluster_2{
            b.store->getBox0({1}),
            b.store->getBox0({1, 0}),
            b.store->getBox0({1, 1}),
        };

        // 3 nested clusters, check each one in sequence, surrounding
        // clusters must contain all their inner elements.

        {
            auto adjacent = getItemsInRect(
                b.view, clusters.at(0)->boundingRect());

            Vec<OrgBoxId> boxes = get_node_boxes(adjacent);

            QCOMPARE_EQ(boxes.size(), 4);
            for (auto const& it : cluster_0) {
                QVERIFY(boxes.contains(it));
            }
        }

        {
            auto adjacent = getItemsInRect(
                b.view, clusters.at(1)->boundingRect());

            Vec<OrgBoxId> boxes = get_node_boxes(adjacent);

            QCOMPARE_EQ(boxes.size(), 7);

            for (auto const& it : cluster_0) {
                QVERIFY(boxes.contains(it));
            }

            for (auto const& it : cluster_1) {
                QVERIFY(boxes.contains(it));
            }
        }


        {
            auto adjacent = getItemsInRect(
                b.view, clusters.at(2)->boundingRect());

            Vec<OrgBoxId> boxes = get_node_boxes(adjacent);

            QCOMPARE_EQ(boxes.size(), 10);

            for (auto const& it : cluster_0) {
                QVERIFY(boxes.contains(it));
            }

            for (auto const& it : cluster_1) {
                QVERIFY(boxes.contains(it));
            }

            for (auto const& it : cluster_2) {
                QVERIFY(boxes.contains(it));
            }
        }
    }
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

    // graph.state.debug = true;
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

            QVERIFY(graph.state.boxToVertex.contains(store.getBox0({0})));
            QVERIFY(graph.state.boxToVertex.contains(store.getBox0({1})));

            // graph.state.debug  = true;
            auto new_paragraph = store.update<sem::Paragraph>(
                paragraph_box, [&](sem::Paragraph& prev) {
                    prev = *new_text.getAs<sem::Paragraph>();
                });

            _qfmt(
                "box0:{} box1:{}", store.getBox0({0}), store.getBox0({1}));
            QCOMPARE_EQ2(new_paragraph, store.getBox0({0}));
            QVERIFY(graph.state.boxToVertex.contains(store.getBox0({0})));
            QVERIFY(graph.state.boxToVertex.contains(store.getBox0({1})));
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


void TestMindMap::testRowModelSignals() {
    using R = AbstractItemModelSignalListener::Record;
    using K = R::Kind;
    Str text{R"(
Paragraph [[id:subtree-id]]

* Subtree
  :properties:
  :id: subtree-id
  :end:
)"};

    OrgStore store;
    store.addRoot(text);
    auto  b0 = store.getBox0({0});
    auto  b1 = store.getBox0({1});
    Graph g{&store, nullptr};

    AbstractItemModelSignalListener l{&g};

    {
        g.addBox(b0);
        auto rows = l.popRecordsT<R::RowsInserted>();
        QCOMPARE_EQ(rows.size(), 1);
        QCOMPARE_EQ(rows.at(0).first, 0);
        QCOMPARE_EQ(rows.at(0).last, 0);
        QCOMPARE_EQ(g.rowCount(), 1);
    }

    l.clear();

    {
        g.addBox(b1);
        QCOMPARE_EQ(g.rowCount(), 3);
        auto rows = l.popRecordsT<R::RowsInserted>();
        QCOMPARE_EQ(rows.size(), 2);
        QCOMPARE_EQ(rows.at(0).first, 1);
        QCOMPARE_EQ(rows.at(1).first, 2);
        QCOMPARE_EQ(rows.at(1).last, 2);
        QCOMPARE_EQ(l.countT<R::RowsRemoved>(), 0);
        QCOMPARE_EQ(l.countT<R::LayoutChanged>(), 1);
        QCOMPARE_LT(
            l.indexOf(K::LayoutAboutToBeChanged),
            l.indexOf(K::LayoutChanged));
    }

    l.clear();

    {
        g.deleteBox(b0);
        QCOMPARE_EQ(g.rowCount(), 1);
        auto rows = l.popRecordsT<R::RowsRemoved>();
        QCOMPARE_EQ(rows.size(), 2);
        // First signal edge removal
        QCOMPARE_EQ(rows.at(0).first, 2);
        // Then signal node removal
        QCOMPARE_EQ(rows.at(1).first, 0);
    }

    l.clear();

    {
        g.deleteBox(b1);
        auto rows = l.popRecordsT<R::RowsRemoved>();
        QCOMPARE_EQ(rows.size(), 1);
    }
}

/// \brief Graph layout emits row insert/remove signals when elements are
/// added. This test checks for consistency in the generated indices.
void TestMindMap::testGraphLayoutRowConsistency() {
    using R = AbstractItemModelSignalListener::Record;
    using K = R::Kind;


    Str text{R"(
Paragraph [fn:target1] [fn:target2]

[fn:target1] Description

[fn:target2] Description
)"};

    OrgStore store;
    Graph    graph{&store, nullptr};
    graph.connectStore();
    store.addRoot(text);
    graph.setObjectName("graph");

    auto doc = store.getBox0({});
    auto b0  = store.getBox0({0});
    auto b1  = store.getBox0({1});
    auto b2  = store.getBox0({2});

    AbstractItemModelSignalListener l{&graph};
    Vec<R>                          stored_events;

    // Simplified test representation of the graph model. When rows are
    // added or removed in the graph, the test will replay captured signals
    // on this modeled variant and then check for consistency.
    Vec<Str> rows;
    auto     apply_events = [&]() {
        stored_events.append(l.records);
        Str msg;

        for (auto const& r : stored_events) {
            switch (r.getKind()) {
                    // Ignore these to clean up debug output
                case K::RowsAboutToBeInserted:
                case K::RowsAboutToBeRemoved:
                case K::LayoutChanged:
                case K::LayoutAboutToBeChanged: break;
                default: msg += r.toString(); msg += "\n";
            }
        }

        int change_delta = 0;

        for (auto const& e : l.records) {
            switch (e.getKind()) {
                case K::RowsRemoved: {
                    auto const& rm = e.getRowsRemoved();
                    rows.erase(
                        rows.begin() + rm.first,
                        rows.begin() + rm.last + 1);
                    int count_removed = (rm.last - rm.first + 1);
                    change_delta -= count_removed;
                    // _qfmt("count_removed:{}", count_removed);
                    break;
                }
                case K::RowsInserted: {
                    auto const& ins = e.getRowsInserted();
                    for (int i = ins.first; i <= ins.last; ++i) {
                        if (i <= rows.size()) {
                            rows.insert(
                                rows.begin() + i,
                                qdebug_to_str(graph.index(i, 0)));
                        } else {
                            throw std::logic_error(
                                fmt("Cannot insert element at index {}, "
                                        "modeled rows size:{} change delta so "
                                        "far:{}\n{}",
                                    i,
                                    rows.size(),
                                    change_delta,
                                    msg));
                        }
                    }
                    int count_added = (ins.last - ins.first + 1);
                    change_delta += count_added;
                    // _qfmt("count_added:{}", count_added);
                    break;
                }
                default: {
                }
            }
        }


        if (graph.rowCount() != rows.size()) {
            throw std::logic_error(
                fmt("graph row count:{} modeled row count:{} delta:{}\n{}",
                    graph.rowCount(),
                    rows.size(),
                    change_delta,
                    msg));
        }

        for (int i = 0; i < graph.rowCount(); ++i) {
            auto       index = graph.index(i);
            GraphIndex gi{index};
            gi.debug();
        }

        // _qfmt("rows:{}", rows);

        l.clear();
    };

    for (int i = 0; i < graph.rowCount(); ++i) {
        rows.push_back(qdebug_to_str(graph.index(i)));
    }

    // _qfmt("row size:{}", rows.size());
    // graph.state.debug = true;
    // _qfmt("rows:{}", rows);
    graph.deleteBox(doc);
    apply_events();
    graph.deleteBox(b0);
    apply_events();
    graph.addBox(b0);
    apply_events();
    graph.deleteBox(b1);
    apply_events();
    graph.deleteBox(b2);
    apply_events();
    graph.addBox(b1);
    apply_events();
    graph.addBox(b2);
}

void TestMindMap::testGraphLayoutFilterSignals() {
    Str text{R"(
Paragraph [fn:target1] [fn:target2]

[fn:target1] Description

[fn:target2] Description
)"};

    OrgStore store;
    Graph    graph{&store, nullptr};
    graph.connectStore();
    store.addRoot(text);
    GraphFilterProxy pre_layout_filter{};
    graph.setObjectName("graph");
    pre_layout_filter.setObjectName("filter");
    pre_layout_filter.accept_edge = [](EDesc edge) { return true; };
    pre_layout_filter.accept_node = [&](VDesc node) { return true; };
    pre_layout_filter.setSourceModel(&graph);

    AbstractItemModelSignalListener graph_events{&graph};
    AbstractItemModelSignalListener filter_events{&pre_layout_filter};
    graph_events.setObjectName("graph_events");
    filter_events.setObjectName("filter_events");

    auto doc = store.getBox0({});
    auto b0  = store.getBox0({0});
    auto b1  = store.getBox0({1});
    auto b2  = store.getBox0({2});

    using R = AbstractItemModelSignalListener::Record;
    using K = R::Kind;

    auto compare_content = [&]() {
        for (int i = 0;
             i < std::max<int>(
                 graph.rowCount(), pre_layout_filter.rowCount());
             ++i) {
            auto       graph_index = graph.index(i);
            GraphIndex gi1{graph_index};

            auto       filter_index = pre_layout_filter.index(i, 0);
            GraphIndex gi2{filter_index};
            QCOMPARE_EQ(gi1.debug(), gi2.debug());
        }
    };

    auto do_check = [&]() {
        // compare_signals();
        compare_content();
    };

    graph.deleteBox(doc);
    do_check();
    graph.deleteBox(b0);
    do_check();
    graph.addBox(b0);
    do_check();
    graph.deleteBox(b1);
    do_check();
    graph.deleteBox(b2);
    do_check();
    graph.addBox(b1);
    do_check();
    graph.addBox(b2);
}

DECL_DESCRIBED_ENUM_STANDALONE(ProxyOrder, None, PreLayout, PostLayout);

/// \brief Changes in the underlying graph structure should be
/// automatically propagated to the graph view, with default graph and with
/// any order of the pre/post layout filtering.
void TestMindMap::testGraphLayoutUpdateSignals() {
    using R = AbstractItemModelSignalListener::Record;
    using K = R::Kind;

    Str text{R"(
Paragraph [fn:target1] [fn:target2]

[fn:target1] Description

[fn:target2] Description
)"};

    struct Run {
        QPixmap                pixmap;
        SPtr<SceneBench>       bench;
        SPtr<GraphFilterProxy> filter;
    };

    Run run_no_proxy;
    Run run_pre_layout;
    Run run_post_layout;

    for (ProxyOrder use_proxy : Vec<ProxyOrder>{
             ProxyOrder::None,
             // Pre layout filtering removes elements before the graph and
             // then proxy arranges everything.
             ProxyOrder::PreLayout,
             // Post layout filtering would leave all the nodes in right
             // places, but might leave "holes" in the graph if some
             // elements were filtered out
             ProxyOrder::PostLayout,
         }) {

        Run run;
        run.bench     = std::make_shared<SceneBench>(text);
        run.filter    = std::make_shared<GraphFilterProxy>();
        SceneBench& b = *run.bench.get();

        GraphFilterProxy& pre_layout_filter = *run.filter.get();
        // Testing signal propagation here, so the filters automatically
        // accept all elements
        pre_layout_filter.accept_edge = [](EDesc edge) { return true; };
        pre_layout_filter.accept_node = [](VDesc node) { return true; };

        b.proxy->setObjectName("layout_proxy");
        b.view->setObjectName("view");
        b.graph->setObjectName("graph");
        pre_layout_filter.setObjectName("filter");
        pre_layout_filter.setSourceModel(b.graph.get());

        switch (use_proxy) {
            case ProxyOrder::None: break;
            case ProxyOrder::PreLayout: {
                b.proxy->setSourceModel(&pre_layout_filter);
                b.proxy->resetLayoutData();
                b.view->setModel(b.proxy.get());
                break;
            }
            case ProxyOrder::PostLayout: {
                pre_layout_filter.setSourceModel(b.proxy.get());
                b.view->setModel(&pre_layout_filter);
                break;
            }
        }

        auto shot = make_shot(
            b.window.get(), "testGraphLayoutUpdateSignals");

        QCOMPARE_EQ(b.graph->numNodes(), 4);
        QCOMPARE_EQ(b.graph->numEdges(), 2);
        QCOMPARE_EQ(b.view->graphItems().size(), 6);
        auto validate_filter = [&]() {
            QCOMPARE_EQ(b.view->graphItems().size(), b.graph->rowCount());
        };

        AbstractItemModelSignalListener l{b.proxy->sourceModel()};
        AbstractItemModelSignalListener dbg{b.graph.get()};
        validate_filter();

        auto doc = b.store->getBox0({});
        auto b0  = b.store->getBox0({0});
        auto b1  = b.store->getBox0({1});
        auto b2  = b.store->getBox0({2});


        // Remove root doc to clean up the graph render a bit
        b.graph->deleteBox(doc);
        QCOMPARE_EQ(l.count(K::RowsRemoved), 1);
        l.clear();

        validate_filter();
        auto without_doc_root = shot("drop_doc");

        {
            b.graph->deleteBox(b0);
            // Node + 2 outgoing links
            QCOMPARE_EQ(l.count(K::RowsRemoved), 3);
            l.clear();
            validate_filter();
        }
        {
            b.graph->addBox(b0);
            QCOMPARE_EQ(l.count(K::RowsInserted), 2);
            l.clear();
            validate_filter();
        }
        {
            b.graph->deleteBox(b1);
            QCOMPARE_EQ(l.count(K::RowsRemoved), 2);
            l.clear();
            validate_filter();
        }
        {
            b.graph->deleteBox(b2);
            QCOMPARE_EQ(l.count(K::RowsRemoved), 2);
            l.clear();
            validate_filter();
        }
        {
            b.graph->addBox(b1);
            QCOMPARE_EQ(l.count(K::RowsInserted), 2);
            l.clear();
            validate_filter();
        }
        {
            b.graph->addBox(b2);
            QCOMPARE_EQ(l.count(K::RowsInserted), 2);
            l.clear();
            validate_filter();
        }
        auto after_readding_everything = shot("add_targets_back");
        QCOMPARE_EQ(
            without_doc_root.toImage(),
            after_readding_everything.toImage());

        run.pixmap = after_readding_everything;

        switch (use_proxy) {
            case ProxyOrder::None: run_no_proxy = run; break;
            case ProxyOrder::PreLayout: run_pre_layout = run; break;
            case ProxyOrder::PostLayout: run_post_layout = run; break;
        }
    }

    // All final elements should have the same visual result, number of
    // graph elements and representations of the graph elements.
    QCOMPARE_EQ(
        run_no_proxy.pixmap.toImage(), run_pre_layout.pixmap.toImage());
    QCOMPARE_EQ(
        run_no_proxy.pixmap.toImage(), run_post_layout.pixmap.toImage());

    for (int row = 0; row < run_no_proxy.bench->graph->rowCount(); ++row) {
        auto no_proxy_item //
            = run_no_proxy.bench->view
                  ->graphItemForIndex(
                      run_no_proxy.bench->graph->index(row))
                  .value();
        auto pre_layout_item //
            = run_pre_layout.bench->view
                  ->graphItemForIndex(
                      run_pre_layout.bench->graph->index(row))
                  .value();
        auto post_layout_item //
            = run_post_layout.bench->view
                  ->graphItemForIndex(
                      run_post_layout.bench->graph->index(row))
                  .value();

        QCOMPARE_EQ(
            no_proxy_item->boundingRect(),
            pre_layout_item->boundingRect());
        QCOMPARE_EQ(
            no_proxy_item->boundingRect(),
            post_layout_item->boundingRect());
    }
}


/// \brief Run over all supported graphviz algorithms.
void TestMindMap::testGraphvizLayoutAlgorithms() {
    SceneBench b{getFullMindMapText()};
    auto shot = make_shot(b.window.get(), "testGraphvizLayoutAlgorithms");

    for (auto const& it : sliceT<Graphviz::LayoutType>()) {
        b.proxy->config.graphvizLayout = it;
        b.proxy->resetLayoutData();
        b.adjustWindow();
        shot(fmt1(it));
    }
}

/// \brief Graph construction works with the whole store at the same time
/// and tracks node relations across different tree root.
void TestMindMap::testMultiRootGraphConstruction() {
    OrgStore store;
    Graph    graph{&store, nullptr};
    graph.connectStore();
    store.addRoot(R"(
* Subtree1
  :properties:
  :id: subtree-1
  :end:

- [[id:subtree-2]] :: Forward link
)"_ss);

    store.addRoot(R"(
* Subtree2
  :properties:
  :id: subtree-2
  :end:

- [[id:subtree-1]] :: Backlink
)"_ss);

    auto r0 = store.getRoot(0);
    auto r1 = store.getRoot(1);

    QVERIFY(graph.hasEdge(r0->id(0), r1->id(0)));
}

/// \brief Run multiple layout views for the same base graph
void TestMindMap::testMultiViewGraphConstruction() {
    auto [store, graph] = build_graph(getFullMindMapText());
    SceneBench dot_layout{store, graph};
    SceneBench neato_layout{store, graph};
    SceneBench fdp_layout{store, graph};

    dot_layout.proxy->config.graphvizLayout   = Graphviz::LayoutType::Dot;
    neato_layout.proxy->config.graphvizLayout = Graphviz::LayoutType::
        Neato;
    fdp_layout.proxy->config.graphvizLayout = Graphviz::LayoutType::Fdp;

    dot_layout.proxy->resetLayoutData();
    neato_layout.proxy->resetLayoutData();
    fdp_layout.proxy->resetLayoutData();

    QCOMPARE_EQ(dot_layout.view->graphItems().size(), graph->rowCount());
    QCOMPARE_EQ(neato_layout.view->graphItems().size(), graph->rowCount());
    QCOMPARE_EQ(fdp_layout.view->graphItems().size(), graph->rowCount());

    auto idx1       = graph->index(0);
    auto idx1_dot   = dot_layout.view->graphItemForIndex(idx1);
    auto idx1_neato = neato_layout.view->graphItemForIndex(idx1);
    auto idx1_fdp   = neato_layout.view->graphItemForIndex(idx1);
    QVERIFY(idx1_dot.has_value());
    QVERIFY(idx1_neato.has_value());
    QVERIFY(idx1_fdp.has_value());

    // Check if the constructed view really does have some elements
    // structured differently.
    QCOMPARE_NE(
        (**idx1_dot).boundingRect(), (**idx1_neato).boundingRect());
    QCOMPARE_EQ(
        (**idx1_dot).boundingRect().size(),
        (**idx1_neato).boundingRect().size());
}

void TestMindMap::testTreeEditingApiReaction() {
    using R = AbstractItemModelSignalListener::Record;
    using K = R::Kind;

    SceneBench b{R"(
* Subtree1
  :properties:
  :id: subtree-id1
  :end:

* Subtree2
  :properties:
  :id: subtree-id2
  :end:
)"};

    QCOMPARE_EQ(b.graph->numNodes(), 3);
    QCOMPARE_EQ(b.graph->numEdges(), 0);


    auto b0 = b.store->getBox0({0});
    auto b1 = b.store->getBox0({1});
    auto t1 = b.store->getOrgTree(b0);
    auto r  = b.store->getRoot(0);

    AbstractItemModelSignalListener l{b.graph.get()};
    l.printOnTrigger = true;

    qDebug().noquote() << r->treeRepr().toString(false);
    b.graph->state.debug = true;
    b.debugModel();

    QCOMPARE_EQ(l.count(K::RowsInserted), 0);

    UPtr<OrgTreeNode> new_root = b.store->toRoot(
        sem::parseString("Paragraph [[id:subtree-id2]]")->at(0));

    QCOMPARE_EQ(l.count(K::RowsInserted), 2);

    t1->apply(t1->getInsertFirstUnder(), std::move(new_root));

    qDebug().noquote() << r->treeRepr().toString(false);
    b.debugModel();

    QCOMPARE_EQ(b.graph->numNodes(), 4);
    QCOMPARE_EQ(b.graph->numEdges(), 1);
    QVERIFY(b.graph->hasEdge(b.store->getBox0({0, 0}), b1));
}
