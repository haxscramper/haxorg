/// \file Immutable AST mind map tests


#include "tOrgTestCommon.hpp"
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/MapFormatter.hpp>


struct ImmMapApi : ImmOrgApiTestBase {
    org::graph::MapConfig::Ptr     conf;
    org::graph::MapGraphState::Ptr state;
    imm::ImmAstContext::Ptr        store;
    hstd::Vec<imm::ImmAstVersion>  versions;

    ImmMapApi()
        : conf{org::graph::MapConfig::shared()}
        , store{imm::ImmAstContext::init_start_context()} //
    {}

    imm::ImmAstVersion const& getVersion() const {
        return versions.back();
    }

    hstd::Vec<imm::ImmAdapter> getRootAdapters() const {
        return versions
             | hstd::rv::transform([](imm::ImmAstVersion const& v) {
                   return v.getRootAdapter();
               })
             | hstd::rs::to<hstd::Vec>();
    }

    org::graph::MapGraph::Ptr getGraph() const {
        hstd::logic_assertion_check_not_nil(state);
        hstd::logic_assertion_check_not_nil(state->graph);
        return state->graph;
    }

    org::graph::MapGraphState::Ptr getState() const { return state; }

    void init_with(org::sem::SemId<org::sem::Org> const& node) {
        versions = {store->addRoot(node)};
        state = org::graph::MapGraphState::shared(versions.back().context);
        setGraphTraceFile(getDebugFile("graph.log"));
        setImmContextTraceFile(getDebugFile("imm.log"));
        getGraph()->message("init done");
    }

    void init_with(
        hstd::Vec<org::sem::SemId<org::sem::Org>> const& nodes) {
        versions = {store->addRoot(nodes.front())};
        for (auto const& n : nodes.at(slice(1, 1_B))) {
            versions.push_back(versions.back().context->addRoot(n));
        }
        state = org::graph::MapGraphState::shared(versions.back().context);
        setGraphTraceFile(getDebugFile("graph.log"));
        setImmContextTraceFile(getDebugFile("imm.log"));
        getGraph()->message("init done");
    }

    void initGraph(std::shared_ptr<org::imm::ImmAstContext> const& ast) {
        state = org::graph::MapGraphState::FromAstContext(ast);
    }

    void addNodeRec(
        std::shared_ptr<org::imm::ImmAstContext> const& ast,
        imm::ImmAdapter const&                          node) {
        state->addNodeRec(ast, node, conf);
    }

    void writeGraphviz() { writeGraphviz(getDebugFile("graph.png")); }

    auto getGraphviz() {
        graph::MapGraph::GvConfig gvc{};
        auto gv = gvc.toGraphviz(versions.back().context, getGraph());
        return gv;
    }

    void writeGraphviz(fs::path const& name) {
        auto gv = getGraphviz();
        gv->render(name);
    }

    void setGraphTraceFile(fs::path const& name) {
        getGraph()->traceStructured = true;
        getGraph()->setTraceFile(name);
    }

    void setImmContextTraceFile(fs::path const& name) {
        store->debug->traceStructured = true;
        store->debug->setTraceFile(name);
    }

    fs::path getTraceFile() { return getGraph()->traceFile.value(); }
};


TEST_F(ImmMapApi, AddNode) {
    init_with(testParseString("* subtree"));
    EXPECT_EQ(getGraph()->getVertexCount(), 0);
    getState()->addNode(getVersion().getRootAdapter(), conf);
    EXPECT_EQ(getGraph()->getVertexCount(), 1);

    writeGraphviz();
}

TEST_F(ImmMapApi, AddNodeWithLinks) {
    Str text{R"(
Paragraph [[id:subtree-id]]

* Subtree
  :properties:
  :id: subtree-id
  :end:
)"_ss};

    init_with(testParseString(text));
    auto root = getVersion().getRootAdapter();
    EXPECT_EQ(getGraph()->getVertexCount(), 0);
    EXPECT_EQ(getGraph()->getSummedEdgeCount(), 0);
    EXPECT_EQ(getState()->unresolved.size(), 0);

    getGraph()->message("add first node");
    auto v1 = hstd::ext::graph::VertexID::Nil();
    {
        auto __scope = getGraph()->begin_scope();
        auto par     = root.at(1);

        auto init_prop = conf->getInitialNodeProp(state.get(), par);
        ASSERT_EQ(init_prop->unresolved.size(), 1);
        ASSERT_TRUE(init_prop->unresolved.at(0).isLink());

        v1 = getState()->addNode(par, conf);

        ASSERT_EQ(
            getGraph()
                ->getVertex(v1)
                ->getUniqueAttribute<org::graph::MapNodeProp>()
                ->unresolved.size(),
            1);

        EXPECT_EQ(par->getKind(), OrgSemKind::Paragraph);
        EXPECT_EQ(getGraph()->getVertexCount(), 1);
        EXPECT_EQ(getGraph()->getSummedEdgeCount(), 0);
        ASSERT_EQ(getState()->unresolved.size(), 1);
        // EXPECT_EQ(getState()->unresolved.items().at(0), par.uniq());
    }

    getGraph()->message("add second node");
    {
        auto __scope = getGraph()->begin_scope();
        getState()->addNode(root.at(3), conf);
        EXPECT_EQ(getGraph()->getVertexCount(), 2);
        ASSERT_EQ(
            getGraph()
                ->getVertex(v1)
                ->getUniqueAttribute<org::graph::MapNodeProp>()
                ->unresolved.size(),
            0);

        EXPECT_EQ(getState()->unresolved.size(), 0);
        EXPECT_EQ(getGraph()->getSummedEdgeCount(), 1);
        EXPECT_EQ(getGraph()->getEdges().size(), 1);
    }

    writeGraphviz();
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

    init_with({
        testParseString(text1),
        testParseString(text2),
    });

    getGraph()->setTraceFile(getDebugFile("SubtreeBacklinks_log.txt"));
    EXPECT_EQ(getGraph()->getVertexCount(), 2);
    EXPECT_EQ(getGraph()->getSummedEdgeCount(), 2);
    EXPECT_EQ(getState()->unresolved.size(), 0);

    writeGraphviz();
}

TEST_F(ImmMapApi, RadioTargetsForward) {
    Str text{R"(
<<<radio>>> target paragraph

radio user paragraph
)"_ss};

    auto n1 = testParseString(text);

    auto store = imm::ImmAstContext ::init_start_context();
    auto conf  = org::graph::MapConfig ::shared();
    getGraph()->setTraceFile(getDebugFile("log"));
    store->debug->setTraceFile(getGraph()->getTraceFile());
    imm::ImmAstVersion v1   = store->addRoot(n1);
    auto               root = v1.getRootAdapter();

    auto s1 = org::graph::MapGraphState::FromAstContext(v1.context);

    EXPECT_EQ(getGraph()->getVertexCount(), 0);
    EXPECT_EQ(getGraph()->getSummedEdgeCount(), 0);
    EXPECT_EQ(s1->unresolved.size(), 0);

    getGraph()->message("add first node");
    {
        auto __scope = getGraph()->begin_scope();
        auto par     = root.at(1);
        s1->addNode(par, conf);
        EXPECT_EQ(par->getKind(), OrgSemKind::Paragraph);
        EXPECT_EQ(getGraph()->getVertexCount(), 1);
        EXPECT_EQ(getGraph()->getSummedEdgeCount(), 0);
        ASSERT_EQ(s1->unresolved.size(), 0);
    }

    getGraph()->message("add second node");
    {
        auto __scope = getGraph()->begin_scope();
        s1->addNode(root.at(3), conf);
        EXPECT_EQ(getGraph()->getVertexCount(), 2);
        EXPECT_EQ(getGraph()->getSummedEdgeCount(), 1);
        EXPECT_EQ(s1->unresolved.size(), 0);
    }

    writeGraphviz();
}

TEST_F(ImmMapApi, RadioTargetsInverse) {
    Str text{R"(
radio user paragraph

<<<radio>>> target paragraph
)"_ss};

    auto n1 = testParseString(text);

    auto store = imm::ImmAstContext ::init_start_context();
    auto conf  = org::graph::MapConfig ::shared();
    setGraphTraceFile(getDebugFile("log"));
    store->debug->setTraceFile(getTraceFile());
    imm::ImmAstVersion v1   = store->addRoot(n1);
    auto               root = v1.getRootAdapter();

    auto s1 = org::graph::MapGraphState::FromAstContext(v1.context);

    EXPECT_EQ(getGraph()->getVertexCount(), 0);
    EXPECT_EQ(getGraph()->getSummedEdgeCount(), 0);
    EXPECT_EQ(s1->unresolved.size(), 0);

    getGraph()->message("add first node");
    {
        auto __scope = getGraph()->begin_scope();
        auto par     = root.at(1);
        s1->addNode(par, conf);
        EXPECT_EQ(par->getKind(), OrgSemKind::Paragraph);
        EXPECT_EQ(getGraph()->getVertexCount(), 1);
        EXPECT_EQ(getGraph()->getSummedEdgeCount(), 0);
        // radio link tracking is finalized by the time the immutable AST
        // context is constructed, even though the graph node with radio
        // target has not been added to the graph yet, the unresolve link
        // is registered.
        ASSERT_EQ(s1->unresolved.size(), 1);
    }

    getGraph()->message("add second node");
    {
        auto __scope = getGraph()->begin_scope();
        s1->addNode(root.at(3), conf);
        EXPECT_EQ(getGraph()->getVertexCount(), 2);
        EXPECT_EQ(getGraph()->getSummedEdgeCount(), 1);
        EXPECT_EQ(s1->unresolved.size(), 0);
    }

    writeGraphviz();
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
    setGraphTraceFile(getDebugFile("graph_trace.log"));
    addNodeRec(init.context, root);
    writeGraphviz(getDebugFile("RadioTargetAliases.png"));

    imm::ImmAdapter t1         = root.at(1);
    imm::ImmAdapter t2         = root.at(2);
    imm::ImmAdapter par_alias1 = t2.at(0);
    imm::ImmAdapter par_alias2 = t2.at(2);
    imm::ImmAdapter par_human  = t2.at(4);

    EXPECT_TRUE(state->graph->hasEdge(par_alias1.uniq(), t1.uniq()));
    EXPECT_TRUE(state->graph->hasEdge(par_alias2.uniq(), t1.uniq()));
    EXPECT_TRUE(state->graph->hasEdge(par_human.uniq(), t1.uniq()));
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
    getGraph()->setTraceFile(getDebugFile("conf"));
    s1->addNodeRec(v2.context, v2.getRootAdapter(), conf);

    EXPECT_TRUE(getGraph()->hasEdge(node_p110.uniq(), node_s12.uniq()));
    EXPECT_TRUE(getGraph()->hasEdge(node_p110.uniq(), node_s10.uniq()));


    auto gv = getGraphviz();
    gv->setRankDirection(
        hstd::ext::graph::gv::GraphGroup::RankDirection::LR);
    gv->render("/tmp/SubtreeFullMap.dot");
    gv->render("/tmp/SubtreeFullMap.png");
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
            if (!org::imm::isAttachedDescriptionList(id)) {
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
    imm::ImmAdapter root = getVersion().getRootAdapter();
    init_with(n);

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

    DocBlock doc = fromAst(root);
    addAll(state, doc, conf);

    imm::ImmAdapter comment   = root.at({1, 3});
    imm::ImmAdapter par_above = root.at({1, 1});
    EXPECT_EQ(comment->getKind(), OrgSemKind::BlockComment);
    EXPECT_EQ(par_above->getKind(), OrgSemKind::Paragraph);

    // state->graph->addEdge(
    //     org::graph::MapEdge{
    //         .source = org::graph::MapNode{par_above.uniq()},
    //         .target = org::graph::MapNode{comment.uniq()}},
    //     org::graph::MapEdgeProp{});

    auto gv = getGraphviz();
    // gv.setRankDirection(Graphviz::Graph::RankDirection::LR);
    gv->render(getDebugFile("map.dot"));
    gv->render(getDebugFile("map.png"));

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

    auto g = getGraph();

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

    // org::graph::MapGraph::GvConfig gvConf;
    // // gvConf.acceptNode = [&](org::graph::MapNode const& node) {
    // //     return 0 < state.graph->inDegree(node)
    // //         || 0 < state.graph->outDegree(node);
    // // };
    // auto gv = state.graph->toGraphviz(v.context, gvConf);
    // gv->render(getDebugFile("map.dot"));
    // gv->render(
    //     getDebugFile("map.png"),
    //     hstd::ext::graph::gv::LayoutType::Sfdp);
    writeGraphviz();
}
