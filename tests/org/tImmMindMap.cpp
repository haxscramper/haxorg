/// \file Immutable AST mind map tests


#include "tOrgTestCommon.hpp"
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/MapFormatter.hpp>


struct ImmMapApi : ImmOrgApiTestBase {
    org::graph::MapConfig::Ptr     conf;
    org::graph::MapGraphState::Ptr graph;

    ImmMapApi()
        : conf{org::graph::MapConfig::shared()} //
    {}

    void initGraph(std::shared_ptr<org::imm::ImmAstContext> const& ast) {
        graph = org::graph::MapGraphState::FromAstContext(ast);
    }

    void addNodeRec(
        std::shared_ptr<org::imm::ImmAstContext> const& ast,
        CR<imm::ImmAdapter>                             node) {
        graph->addNodeRec(ast, node, conf);
    }

    void writeGraphviz(CR<fs::path> name) {
        hstd::ext::Graphviz gvc;
        auto                gv = graph->graph->toGraphviz(start);
        gvc.renderToFile(name, gv);
    }

    void setGraphTrace(CR<fs::path> name) { conf->dbg.setTraceFile(name); }
};


TEST_F(ImmMapApi, AddNode) {
    auto n1 = testParseString("* subtree");

    auto store = imm::ImmAstContext::init_start_context();
    auto conf  = org::graph::MapConfig ::shared();
    conf->dbg.setTraceFile(getDebugFile("ImmMapApi_AddNode.txt"));
    imm::ImmAstVersion v1 = store->addRoot(n1);
    auto               s1 = org::graph::MapGraphState::shared(v1.context);
    EXPECT_EQ(s1->graph->nodeCount(), 0);
    s1->addNode(v1.getRootAdapter(), conf);
    EXPECT_EQ(s1->graph->nodeCount(), 1);

    hstd::ext::Graphviz gvc;
    auto                gv = s1->graph->toGraphviz(v1.context);
    gvc.renderToFile(getDebugFile("MapS2.png"), gv);
}

TEST_F(ImmMapApi, AddNodeWithLinks) {
    Str text{R"(
Paragraph [[id:subtree-id]]

* Subtree
  :properties:
  :id: subtree-id
  :end:
)"_ss};

    auto n1 = testParseString(text);

    auto store = imm::ImmAstContext ::init_start_context();
    auto conf  = org::graph::MapConfig ::shared();
    conf->dbg.setTraceFile(getDebugFile("log"));
    store->debug->setTraceFile(conf->dbg.getTraceFile());
    imm::ImmAstVersion v1   = store->addRoot(n1);
    auto               root = v1.getRootAdapter();

    auto s1 = org::graph::MapGraphState::FromAstContext(v1.context);

    EXPECT_EQ(s1->graph->nodeCount(), 0);
    EXPECT_EQ(s1->graph->edgeCount(), 0);
    EXPECT_EQ(s1->unresolved.size(), 0);

    conf->dbg.message("add first node");
    {
        auto __scope = conf->dbg.scopeLevel();
        auto par     = root.at(1);
        s1->addNode(par, conf);
        EXPECT_EQ(par->getKind(), OrgSemKind::Paragraph);
        EXPECT_EQ(s1->graph->nodeCount(), 1);
        EXPECT_EQ(s1->graph->edgeCount(), 0);
        ASSERT_EQ(s1->unresolved.size(), 1);
        EXPECT_EQ(*s1->unresolved.begin(), par.uniq());
    }

    conf->dbg.message("add second node");
    {
        auto __scope = conf->dbg.scopeLevel();
        s1->addNode(root.at(3), conf);
        EXPECT_EQ(s1->graph->nodeCount(), 2);
        EXPECT_EQ(s1->graph->edgeCount(), 1);
        EXPECT_EQ(s1->unresolved.size(), 0);
    }

    hstd::ext::Graphviz gvc;
    auto                gv = s1->graph->toGraphviz(v1.context);
    gvc.renderToFile(getDebugFile("AddNodeWithLinks.png"), gv);
}


TEST_F(ImmMapApi, SubtreeBacklinks) {
    Str text1{R"(
* Subtree1
  :properties:
  :id: subtree-1
  :end:

#+attr_list: :attached subtree
- [[id:subtree-2]] :: Forward link
)"_ss};

    Str text2{R"(
* Subtree2
  :properties:
  :id: subtree-2
  :end:

#+attr_list: :attached subtree
- [[id:subtree-1]] :: Backlink
)"_ss};

    auto n1 = testParseString(text1);
    auto n2 = testParseString(text2);

    auto store = imm::ImmAstContext::init_start_context();
    auto conf  = org::graph::MapConfig ::shared();
    conf->dbg.setTraceFile(getDebugFile("SubtreeBacklinks_log.txt"));

    imm::ImmAstVersion v2 = store->addRoot(n1);
    imm::ImmAstVersion v3 = v2.context->addRoot(n2);


    auto s1 = org::graph::MapGraphState::shared(v3.context);

    EXPECT_EQ(s1->graph->nodeCount(), 0);
    EXPECT_EQ(s1->graph->edgeCount(), 0);
    EXPECT_EQ(s1->unresolved.size(), 0);

    s1->addNode(v2.getRootAdapter().at(1), conf);
    EXPECT_EQ(s1->graph->nodeCount(), 1);
    EXPECT_EQ(s1->graph->edgeCount(), 0);
    EXPECT_EQ(s1->unresolved.size(), 1);

    s1->addNode(v3.getRootAdapter().at(1), conf);
    EXPECT_EQ(s1->graph->nodeCount(), 2);
    EXPECT_EQ(s1->graph->edgeCount(), 2);
    EXPECT_EQ(s1->unresolved.size(), 0);

    hstd::ext::Graphviz gvc;
    auto                gv = s1->graph->toGraphviz(v3.context);
    gvc.renderToFile(getDebugFile("SubtreeBacklinks.png"), gv);
}

TEST_F(ImmMapApi, RadioTargetsForward) {
    Str text{R"(
<<<radio>>> target paragraph

radio user paragraph
)"_ss};

    auto n1 = testParseString(text);

    auto store = imm::ImmAstContext ::init_start_context();
    auto conf  = org::graph::MapConfig ::shared();
    conf->dbg.setTraceFile(getDebugFile("log"));
    store->debug->setTraceFile(conf->dbg.getTraceFile());
    imm::ImmAstVersion v1   = store->addRoot(n1);
    auto               root = v1.getRootAdapter();

    auto s1 = org::graph::MapGraphState::FromAstContext(v1.context);

    EXPECT_EQ(s1->graph->nodeCount(), 0);
    EXPECT_EQ(s1->graph->edgeCount(), 0);
    EXPECT_EQ(s1->unresolved.size(), 0);

    conf->dbg.message("add first node");
    {
        auto __scope = conf->dbg.scopeLevel();
        auto par     = root.at(1);
        s1->addNode(par, conf);
        EXPECT_EQ(par->getKind(), OrgSemKind::Paragraph);
        EXPECT_EQ(s1->graph->nodeCount(), 1);
        EXPECT_EQ(s1->graph->edgeCount(), 0);
        ASSERT_EQ(s1->unresolved.size(), 0);
    }

    conf->dbg.message("add second node");
    {
        auto __scope = conf->dbg.scopeLevel();
        s1->addNode(root.at(3), conf);
        EXPECT_EQ(s1->graph->nodeCount(), 2);
        EXPECT_EQ(s1->graph->edgeCount(), 1);
        EXPECT_EQ(s1->unresolved.size(), 0);
    }

    hstd::ext::Graphviz gvc;
    auto                gv = s1->graph->toGraphviz(v1.context);
    gvc.renderToFile(getDebugFile("RadioTargetsForward.png"), gv);
}

TEST_F(ImmMapApi, RadioTargetsInverse) {
    Str text{R"(
radio user paragraph

<<<radio>>> target paragraph
)"_ss};

    auto n1 = testParseString(text);

    auto store = imm::ImmAstContext ::init_start_context();
    auto conf  = org::graph::MapConfig ::shared();
    conf->dbg.setTraceFile(getDebugFile("log"));
    store->debug->setTraceFile(conf->dbg.getTraceFile());
    imm::ImmAstVersion v1   = store->addRoot(n1);
    auto               root = v1.getRootAdapter();

    auto s1 = org::graph::MapGraphState::FromAstContext(v1.context);

    EXPECT_EQ(s1->graph->nodeCount(), 0);
    EXPECT_EQ(s1->graph->edgeCount(), 0);
    EXPECT_EQ(s1->unresolved.size(), 0);

    conf->dbg.message("add first node");
    {
        auto __scope = conf->dbg.scopeLevel();
        auto par     = root.at(1);
        s1->addNode(par, conf);
        EXPECT_EQ(par->getKind(), OrgSemKind::Paragraph);
        EXPECT_EQ(s1->graph->nodeCount(), 1);
        EXPECT_EQ(s1->graph->edgeCount(), 0);
        // radio link tracking is finalized by the time the immutable AST
        // context is constructed, even though the graph node with radio
        // target has not been added to the graph yet, the unresolve link
        // is registered.
        ASSERT_EQ(s1->unresolved.size(), 1);
    }

    conf->dbg.message("add second node");
    {
        auto __scope = conf->dbg.scopeLevel();
        s1->addNode(root.at(3), conf);
        EXPECT_EQ(s1->graph->nodeCount(), 2);
        EXPECT_EQ(s1->graph->edgeCount(), 1);
        EXPECT_EQ(s1->unresolved.size(), 0);
    }

    hstd::ext::Graphviz gvc;
    auto                gv = s1->graph->toGraphviz(v1.context);
    gvc.renderToFile(getDebugFile("RadioTargetsForward.png"), gv);
}

TEST_F(ImmMapApi, RadioTargetAliases) {
    Str text{R"(
* Subtree with item description
  :properties:
  :radio_id: alias1
  :radio_id: alias2
  :radio_id: human-readable alias
  :end:

* Other subtree

alias1 is a thing

alias2 is a thing

also known as a human-readable alias
)"_ss};

    auto init = getInitialVersion(text);
    auto root = init.getRootAdapter();
    initGraph(init.context);
    writeTreeRepr(root, getDebugFile("repr.txt"));
    writeTreeRepr(
        parseContext->parseString(text, "<test>"),
        getDebugFile("repr.yaml"));
    setGraphTrace(getDebugFile("graph_trace.log"));
    setTraceFile(getDebugFile("imm_trace.log"));
    addNodeRec(init.context, root);
    writeGraphviz(getDebugFile("RadioTargetAliases.png"));

    imm::ImmAdapter t1         = root.at(1);
    imm::ImmAdapter t2         = root.at(2);
    imm::ImmAdapter par_alias1 = t2.at(0);
    imm::ImmAdapter par_alias2 = t2.at(2);
    imm::ImmAdapter par_human  = t2.at(4);

    EXPECT_TRUE(graph->graph->hasEdge(par_alias1.uniq(), t1.uniq()));
    EXPECT_TRUE(graph->graph->hasEdge(par_alias2.uniq(), t1.uniq()));
    EXPECT_TRUE(graph->graph->hasEdge(par_human.uniq(), t1.uniq()));
}

Str getFullMindMapText() {
    Vec<Str> text{
        R"(
* Mind map nodes are made from subtrees
)",
        R"(
** Subtrees can be nested for clustering
   :PROPERTIES:
   :ID:       c468e9c7-7422-4b17-8ccb-53575f186fe0
   :END:
)",
        R"(
** More than one subtree can exist in cluster
)",
        R"(
Tree  description, maybe  on multiple  lines.
Can include  [[id:c468e9c7-7422-4b17-8ccb-53575f186fe0][links]] to  other trees.
Links are attached to specific [[id:6d6d6689-d9da-418d-9f91-1c8c4428e5af][rows]] in the text
so it is easier to track which part of the
description refers to the [[id:9879fed7-f0a4-44bd-bf56-983279afc622][other]] tree
)",
        R"(- )",
        R"(when [[id:c468e9c7-7422-4b17-8ccb-53575f186fe0][link]] :: Description lists can be used for annotated links

)",
        R"(  Multiple paragraphs attached to link
)",
        R"(
used in description list it's placed as annotation to the graph node.
Description can take multiple lines[fn:lines-20].
)",
        R"(
[fn:lines-20]  Footnotes  are placed  into  separate  nodes. You  can  have
nested[fn:nested-23]
)",
        R"(
[fn:nested-23] footnotes
)",
        R"(
** Extra entries
   :PROPERTIES:
   :ID:       6d6d6689-d9da-418d-9f91-1c8c4428e5af
   :END:
)",
        R"(
Parent subtrees can contain some things.
)",
        R"(
* Several clusters can exist
)",
        R"(
Nested subtrees
Multiline [[id:6d6d6689-d9da-418d-9f91-1c8c4428e5af][Extra entries]]
)",
        R"(
** With multiple nodes
   :PROPERTIES:
   :ID:       9879fed7-f0a4-44bd-bf56-983279afc622
   :END:
)",
        R"(
** And even nested
)",
        R"(
*** Clusters
)",
        R"(
*** And nodes
)",
        R"(
*** Intercluster links are possible
)",
        R"(
[[id:c468e9c7-7422-4b17-8ccb-53575f186fe0][Annotation for the target subtree]]
[[id:XXSDASD][Unresolved subtree]]
)",
        "- ",
        "Regular list element\n",
        "- ",
        "Two items in a list\n",
    };
    return join("", text);
}

using osk = OrgSemKind;

TEST_F(ImmMapApi, SubtreeFullMap) {
    auto n = testParseString(getFullMindMapText());

    auto store = imm::ImmAstContext::init_start_context();

    imm::ImmAstVersion v2 = store->addRoot(n);
    auto s1 = org::graph::MapGraphState::FromAstContext(v2.context);
    imm::ImmAdapter file = v2.getRootAdapter();

    EXPECT_EQ(file.at(1)->getKind(), osk::Subtree);
    auto node_s10  = file.at(Vec{1, 0});
    auto node_p110 = file.at({1, 1, 0});
    auto node_s12  = file.at(Vec{1, 2});
    EXPECT_EQ(node_s10->getKind(), osk::Subtree);
    EXPECT_EQ(
        node_s10.as<imm::ImmSubtree>()->treeId->value(),
        "c468e9c7-7422-4b17-8ccb-53575f186fe0");

    EXPECT_EQ(node_s12->getKind(), osk::Subtree);
    EXPECT_EQ(
        node_s12.as<imm::ImmSubtree>()->treeId->value(),
        "6d6d6689-d9da-418d-9f91-1c8c4428e5af");


    auto conf = org::graph::MapConfig ::shared();
    conf->dbg.setTraceFile(getDebugFile("conf"));
    s1->addNodeRec(v2.context, v2.getRootAdapter(), conf);

    EXPECT_TRUE(s1->graph->hasEdge(node_p110.uniq(), node_s12.uniq()));
    EXPECT_TRUE(s1->graph->hasEdge(node_p110.uniq(), node_s10.uniq()));

    hstd::ext::Graphviz gvc;
    auto                gv = s1->graph->toGraphviz(v2.context);
    gv.setRankDirection(hstd::ext::Graphviz::Graph::RankDirection::LR);
    gvc.writeFile("/tmp/SubtreeFullMap.dot", gv);
    gvc.renderToFile("/tmp/SubtreeFullMap.png", gv);
}

Str getSubtreeBlockText() {
    return Str{R"str(
* Subtree 1
  :properties:
  :id: subtree_1
  :end:

#+attr_list: :attached subtree
- [[id:subtree_2]] :: Describe link to subtree 2
- [[internal_1]] :: Describe link to internal

<<internal_1>> Internal paragraph [fn:footnote_1]

#+begin_comment :attach above
Comment for the paragraph content above
#+end_comment

[fn:footnote_1] Definition of the footnote 1

Second paragraph [fn:footnote_2]

[fn:footnote_2] Footnote 2 [fn:recursive_1]

[fn:recursive_1] Recursive footnote 1 [fn:recursive_2]

[fn:recursive_2] Recursive footnote 2

* Subtree 2
  :properties:
  :id: subtree_2
  :end:

- [[id:subtree_2]] :: Standalone description list targeting subtree
- [[id:subtree_1]] :: Targeting subtree one
- [[internal_1]] :: Targeting standalone paragraph 1
- [[named-paragraph-one]] :: Targeting named paragraph

#+name: named-paragraph-one
Paragraph with name annotations
)str"};
}

struct DocItem {
    imm::ImmAdapter id;
    DESC_FIELDS(DocItem, (id));
};

struct DocBlock {
    Vec<DocItem>  items;
    Vec<DocBlock> nested;
    DESC_FIELDS(DocBlock, (items, nested));
};

DocBlock fromAst(imm::ImmAdapter const& id) {
    SemSet Skip{OrgSemKind::Newline};

    DocBlock result;
    switch (id->getKind()) {
        case OrgSemKind::Document: {
            for (auto const& sub : id.sub()) {
                if (!Skip.contains(sub->getKind())) {
                    result.nested.push_back(fromAst(sub));
                }
            }
            break;
        }
        case OrgSemKind::Subtree: {
            result.items.push_back(DocItem{.id = id});
            for (auto const& sub : id.sub()) {
                if (!Skip.contains(sub->getKind())) {
                    result.nested.push_back(fromAst(sub));
                }
            }
            break;
        }

        default: {
            if (!org::graph::isAttachedDescriptionList(id)) {
                result.items.push_back(DocItem{.id = id});
            }

            break;
        }
    }

    return result;
}

void addAll(
    org::graph::MapGraphState::Ptr const& state,
    DocBlock const&                       block,
    org::graph::MapConfig::Ptr            conf) {
    for (auto const& it : block.items) { state->addNode(it.id, conf); }

    for (auto const& it : block.nested) { addAll(state, it, conf); }
}

TEST_F(ImmMapApi, SubtreeBlockMap) {
    auto n = testParseString(getSubtreeBlockText());
    org::exportToTreeFile(
        n,
        getDebugFile("sem_tree.txt"),
        org::OrgTreeExportOpts{
            .withColor = false,
        });


    auto store = imm::ImmAstContext::init_start_context();
    store->debug->setTraceFile(getDebugFile("store"));
    imm::ImmAstVersion v    = store->addRoot(n);
    imm::ImmAdapter    root = v.getRootAdapter();

    writeTreeRepr(
        root,
        getDebugFile("imm_path.txt"),
        imm::ImmAdapter::TreeReprConf{
            .withAuxFields = true,
        });


    writeTreeRepr(
        root,
        getDebugFile("imm_tree.txt"),
        imm::ImmAdapter::TreeReprConf{
            .withReflFields = true,
            .withAuxFields  = true,
        });


    auto conf = org::graph::MapConfig ::shared();
    conf->dbg.setTraceFile(getDebugFile("graph"));
    auto     state = org::graph::MapGraphState::FromAstContext(v.context);
    DocBlock doc   = fromAst(root);
    addAll(state, doc, conf);

    imm::ImmAdapter comment   = root.at({1, 3});
    imm::ImmAdapter par_above = root.at({1, 1});
    EXPECT_EQ(comment->getKind(), OrgSemKind::BlockComment);
    EXPECT_EQ(par_above->getKind(), OrgSemKind::Paragraph);

    state->graph->addEdge(
        org::graph::MapEdge{
            .source = org::graph::MapNode{par_above.uniq()},
            .target = org::graph::MapNode{comment.uniq()}},
        org::graph::MapEdgeProp{});

    hstd::ext::Graphviz gvc;
    auto                gv = state->graph->toGraphviz(v.context);
    // gv.setRankDirection(Graphviz::Graph::RankDirection::LR);
    gvc.writeFile(getDebugFile("map.dot"), gv);
    gvc.renderToFile(getDebugFile("map.png"), gv);

    // org::eachSubnodeRec(root, [](org::ImmAdapter const& it) {
    //     if (SemSet{
    //             OrgSemKind::Subtree,
    //             OrgSemKind::Paragraph,
    //             OrgSemKind::List}
    //             .contains(it->getKind())) {
    //         std::cout << getSelfTest(it).toBase() << std::endl;
    //     }
    // });

    auto List_1         = root.at(1).at(0);
    auto List_2         = root.at(2).at(0);
    auto Paragraph_10   = root.at(1).at(9);
    auto Paragraph_11   = root.at(1).at(11);
    auto Paragraph_12   = root.at(1).at(13);
    auto Paragraph_14   = root.at(2).at(0).at(0).at(0);
    auto Paragraph_16   = root.at(2).at(0).at(1).at(0);
    auto Paragraph_17   = root.at(2).at(0).at(2).at(0);
    auto Paragraph_19   = root.at(2).at(0).at(3).at(0);
    auto Paragraph_20   = root.at(2).at(1);
    auto Paragraph_3    = root.at(1).at(0).at(0).at(0);
    auto Paragraph_5    = root.at(1).at(0).at(1).at(0);
    auto Paragraph_6    = root.at(1).at(1);
    auto Paragraph_7    = root.at(1).at(3).at(0);
    auto Paragraph_8    = root.at(1).at(5);
    auto Paragraph_9    = root.at(1).at(7);
    auto Subtree_1      = root.at(1);
    auto Subtree_2      = root.at(2);
    auto BlockComment_1 = root.at(1).at(3);

    EXPECT_EQ(List_1->getKind(), OrgSemKind::List);
    EXPECT_EQ(List_2->getKind(), OrgSemKind::List);
    EXPECT_EQ(Paragraph_10->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_11->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_12->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_14->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_16->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_17->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_19->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_20->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_3->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_5->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_6->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_7->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_8->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_9->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Subtree_1->getKind(), OrgSemKind::Subtree);
    EXPECT_EQ(Subtree_2->getKind(), OrgSemKind::Subtree);
    EXPECT_EQ(BlockComment_1->getKind(), OrgSemKind::BlockComment);

    EXPECT_EQ(
        (imm::flatWords(Paragraph_20)),
        (Vec<Str>{"Paragraph", "with", "name", "annotations"}));

    EXPECT_EQ(
        (imm::flatWords(Paragraph_6)),
        (Vec<Str>{"Internal", "paragraph"}));


    EXPECT_EQ(
        (imm::flatWords(Paragraph_9)), (Vec<Str>{"Second", "paragraph"}));

    EXPECT_EQ((imm::flatWords(Paragraph_10)), (Vec<Str>{"Footnote", "2"}));

    EXPECT_EQ(
        (imm::flatWords(Paragraph_11)),
        (Vec<Str>{"Recursive", "footnote", "1"}));

    EXPECT_EQ(
        (imm::flatWords(Paragraph_12)),
        (Vec<Str>{"Recursive", "footnote", "2"}));


    EXPECT_EQ(
        (imm::flatWords(Subtree_1.as<imm::ImmSubtree>().getTitle())),
        (Vec<Str>{"Subtree", "1"}));

    EXPECT_EQ(
        (imm::flatWords(Subtree_2.as<imm::ImmSubtree>().getTitle())),
        (Vec<Str>{"Subtree", "2"}));

    auto& g = state->graph;

    g->hasEdge(List_2, Paragraph_20);
    g->hasEdge(List_2, Subtree_1);
    g->hasEdge(List_2, Subtree_2);
    g->hasEdge(List_2, Paragraph_6);
    g->hasEdge(Subtree_1, Subtree_2);
    g->hasEdge(Subtree_1, Paragraph_6);
    g->hasEdge(Paragraph_6, BlockComment_1);
    g->hasEdge(Paragraph_9, Paragraph_10);
    g->hasEdge(Paragraph_10, Paragraph_11);
    g->hasEdge(Paragraph_11, Paragraph_12);
}

TEST_F(ImmMapApi, Doc1Graph) {
    __perf_trace("imm", "run test");
    fs::path file = fs::path{std::getenv("HOME")}
                  / std::string{"tmp/doc_graph->org"};

    if (!fs::exists(file)) { return; }
    auto n = testParseString(readFile(file));

    auto               store = imm::ImmAstContext::init_start_context();
    imm::ImmAstVersion v     = store->addRoot(n);
    // return;

    // writeTreeRepr(
    //     v.getRootAdapter(),
    //     "imm.txt",
    //     org::ImmAdapter::TreeReprConf{
    //         .withReflFields = true,
    //         .withAuxFields  = true,
    //     });

    {
        int count = 0;
        __perf_trace("imm", "iterate each sem node");
        org::eachSubnodeRec(n, [&](sem::OrgArg) { ++count; });
    }

    {
        int count = 0;
        __perf_trace("imm", "iterate each node with path");
        org::eachSubnodeRec(
            v.getRootAdapter(), true, [&](imm::ImmAdapter const&) {
                ++count;
            });
    }

    {
        int count = 0;
        __perf_trace("imm", "iterate each node without path");
        org::eachSubnodeRec(
            v.getRootAdapter(), false, [&](imm::ImmAdapter const&) {
                ++count;
            });
    }

    imm::ImmAdapter root = v.getRootAdapter();

    auto                      conf = org::graph::MapConfig::shared();
    org::graph::MapGraphState state{v.context};
    state.addNodeRec(v.context, root, conf);

    hstd::ext::Graphviz            gvc;
    org::graph::MapGraph::GvConfig gvConf;
    gvConf.acceptNode = [&](org::graph::MapNode const& node) {
        return 0 < state.graph->inDegree(node)
            || 0 < state.graph->outDegree(node);
    };
    auto gv = state.graph->toGraphviz(v.context, gvConf);
    gvc.writeFile(getDebugFile("map.dot"), gv);
    gvc.renderToFile(
        getDebugFile("map.png"),
        gv,
        hstd::ext::Graphviz::RenderFormat::PNG,
        hstd::ext::Graphviz::LayoutType::Sfdp);
}

struct TestGraph {
    org::graph::MapGraph::Ptr g;
    Vec<org::graph::MapNode>  nodes;
};

TestGraph create_test_graph() {
    auto g = org::graph::MapGraph::shared();

    auto n0 = imm::ImmUniqId{imm::ImmId::FromValue(0)};
    auto n1 = imm::ImmUniqId{imm::ImmId::FromValue(1)};
    auto n2 = imm::ImmUniqId{imm::ImmId::FromValue(2)};

    g->addNode(n0);
    g->addNode(n1);
    g->addNode(n2);

    g->addEdge(org::graph::MapEdge{n0, n1});
    g->addEdge(org::graph::MapEdge{n1, n2});
    g->addEdge(org::graph::MapEdge{n2, n0});

    return TestGraph{
        .g     = g,
        .nodes = {n0, n1, n2},
    };
}


TEST(ImmMapGraphApi, VertexCount) {
    auto g            = create_test_graph();
    auto num_vertices = boost::num_vertices(*g.g);
    EXPECT_EQ(num_vertices, 3);
}

TEST(ImmMapGraphApi, EdgeCount) {
    auto g         = create_test_graph();
    auto num_edges = boost::num_edges(*g.g);
    EXPECT_EQ(num_edges, 3);
}

TEST(ImmMapGraphApi, Vertices) {
    auto g                = create_test_graph();
    auto [v_begin, v_end] = boost::vertices(*g.g);
    std::vector<org::graph::MapNode> vertices(v_begin, v_end);
    std::sort(vertices.begin(), vertices.end());

    EXPECT_EQ(vertices.size(), 3);
}

TEST(ImmMapGraphApi, Edges) {
    auto g                = create_test_graph();
    auto [e_begin, e_end] = boost::edges(*g.g);
    std::vector<org::graph::MapEdge> edges(e_begin, e_end);

    EXPECT_EQ(edges.size(), 3);
    EXPECT_NE(
        std::find(
            edges.begin(),
            edges.end(),
            org::graph::MapEdge{g.nodes.at(0), g.nodes.at(1)}),
        edges.end());
    EXPECT_NE(
        std::find(
            edges.begin(),
            edges.end(),
            org::graph::MapEdge{g.nodes.at(1), g.nodes.at(2)}),
        edges.end());
    EXPECT_NE(
        std::find(
            edges.begin(),
            edges.end(),
            org::graph::MapEdge{g.nodes.at(2), g.nodes.at(0)}),
        edges.end());
}

TEST(ImmMapGraphApi, AdjacentVertices) {
    auto g                    = create_test_graph();
    auto [adj_begin, adj_end] = boost::adjacent_vertices(
        g.nodes.at(0), *g.g);

    std::vector<org::graph::MapNode> adjacent_vertices(adj_begin, adj_end);

    EXPECT_EQ(adjacent_vertices.size(), 2);
    EXPECT_EQ(adjacent_vertices[0], g.nodes.at(1));
    EXPECT_EQ(adjacent_vertices[1], g.nodes.at(2));
}

TEST(ImmMapGraphApi, OutDegree) {
    auto g          = create_test_graph();
    auto out_degree = boost::out_degree(g.nodes.at(0), *g.g);
    EXPECT_EQ(out_degree, 1);
}

TEST(ImmMapGraphApi, EdgeIterators) {
    auto g = create_test_graph();
    {
        auto [oe_begin, oe_end] = boost::out_edges(g.nodes.at(0), *g.g);
        std::vector<org::graph::MapEdge> out_edges(oe_begin, oe_end);

        EXPECT_EQ(out_edges.size(), 1);
        EXPECT_EQ(
            out_edges[0],
            (org::graph::MapEdge{g.nodes.at(0), g.nodes.at(1)}));
    }

    {
        auto [ie_begin, ie_end] = boost::in_edges(g.nodes.at(0), *g.g);
        std::vector<org::graph::MapEdge> in_edges(ie_begin, ie_end);

        EXPECT_EQ(in_edges.size(), 1);
        EXPECT_EQ(
            in_edges[0],
            (org::graph::MapEdge{g.nodes.at(2), g.nodes.at(0)}));
    }
}

TEST(ImmMapGraphApi, AdjacencyIteration) {
    auto g = create_test_graph();
    EXPECT_EQ(g.g->adjNodes(g.nodes.at(0)).size(), 2);
}

TEST(ImmMapGraphApi, SourceAndTarget) {
    auto                g = create_test_graph();
    org::graph::MapEdge e{g.nodes.at(0), g.nodes.at(1)};
    auto                src = boost::source(e, *g.g);
    auto                tgt = boost::target(e, *g.g);

    EXPECT_EQ(src, g.nodes.at(0));
    EXPECT_EQ(tgt, g.nodes.at(1));
}

TEST(ImmMapGraphApi, BoostPropertyWriter) {
    auto n = testParseString(getFullMindMapText());

    auto               store = imm::ImmAstContext ::init_start_context();
    auto               conf  = org::graph::MapConfig::shared();
    imm::ImmAstVersion v2    = store->addRoot(n);
    imm::ImmAdapter    file  = v2.getRootAdapter();
    auto s1 = org::graph::MapGraphState::FromAstContext(v2.context);
    s1->addNodeRec(v2.context, file, conf);

    std::stringstream os;

    auto dp = org::graph::toGraphvizDynamicProperties(*s1->graph);

    write_graphviz_dp(os, *s1->graph, dp);

    writeFile("/tmp/BoostPropertyWriter.dot", os.str());
}

TEST(ImmMapGraphApi, BoostVisitors) {
    auto n = testParseString(getFullMindMapText());
    using namespace org;
    using namespace org::graph;

    auto               store = imm::ImmAstContext::init_start_context();
    auto               conf  = org::graph::MapConfig::shared();
    imm::ImmAstVersion v2    = store->addRoot(n);
    imm::ImmAdapter    file  = v2.getRootAdapter();
    auto s1 = org::graph::MapGraphState::FromAstContext(v2.context);
    s1->addNodeRec(v2.context, file, conf);

    UnorderedMap<MapNode, int> forwardBfsExamineOrder;
    UnorderedMap<MapNode, int> undirectedBfsExamineOrder;
    UnorderedMap<MapNode, int> forwardDfsDiscoverOrder;

    org::graph::bfs_visit(
        *s1->graph,
        MapNode{file.at({1, 1, 0}).uniq()},
        hstd::ext::boost_lambda_bfs_visitor<MapGraph>{}.set_examine_vertex(
            [&, index = 0](CR<MapNode> n, CR<MapGraph>) mutable {
                forwardBfsExamineOrder.insert_or_assign(n, index);
                ++index;
            }));

    org::graph::bfs_visit(
        MapGraphUndirected{s1->graph},
        MapNode{file.at({1, 1, 0}).uniq()},
        hstd::ext::boost_lambda_bfs_visitor<MapGraphUndirected>{}
            .set_examine_vertex(
                [&, index = 0](
                    CR<MapNode> n, CR<MapGraphUndirected>) mutable {
                    undirectedBfsExamineOrder.insert_or_assign(n, index);
                    ++index;
                }));

    org::graph::dfs_visit(
        *s1->graph,
        MapNode{file.at({1, 1, 0}).uniq()},
        hstd::ext::boost_lambda_dfs_visitor<MapGraph>{}
            .set_discover_vertex(
                [&, index = 0](CR<MapNode> n, CR<MapGraph>) mutable {
                    forwardDfsDiscoverOrder.insert_or_assign(n, index);
                    ++index;
                }));

    hstd::ext::Graphviz gvc;
    MapGraph::GvConfig  gvConf;

    gvConf.getNodeLabel =
        [&](imm::ImmAdapter const& adapter,
            MapNodeProp const& prop) -> hstd::ext::Graphviz::Node::Record {
        auto res = MapGraph::GvConfig::getDefaultNodeLabel(adapter, prop);
        MapNode node{adapter.uniq()};
        if (auto forward = forwardBfsExamineOrder.get(node)) {
            res.setEscaped("Forward BFS examine #", fmt1(forward.value()));
        }

        if (auto undirected = undirectedBfsExamineOrder.get(node)) {
            res.setEscaped(
                "Undirected BFS examine #", fmt1(undirected.value()));
        }

        if (auto forward = forwardDfsDiscoverOrder.get(node)) {
            res.setEscaped(
                "Forward DFS discover #", fmt1(forward.value()));
        }
        return res;
    };

    auto gv = s1->graph->toGraphviz(v2.context, gvConf);
    gv.setRankDirection(hstd::ext::Graphviz::Graph::RankDirection::LR);
    gvc.writeFile(getDebugFile("BoostVisitors.dot"), gv);
    gvc.renderToFile(getDebugFile("BoostVisitors.png"), gv);
}
