#include "tOrgTestCommon.hpp"
#include <hstd/stdlib/TimeReflVisitor.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/MapFormatter.hpp>

struct ImmOrgApi : ImmOrgApiTestBase {};

TEST_F(ImmOrgApi, StoreNode) {
    auto node          = testParseString(R"(
** ~pyhaxorg~
    CLOSED: [2024-06-22 Sat 22:00:27 +04]
    :PROPERTIES:
    :CREATED:  [2023-07-30 Sun 20:51:39 +04]
    :END:

=pybind11= python module exposing the org-mode AST for scripting. intern intern intern intern
)");
    auto s0            = imm::ImmAstContext::init_start_context();
    auto [store, root] = s0->addRoot(node);
    ColStream os;
    store->format(os);
    writeFile("/tmp/StoreNode.txt", os.getBuffer().toString(false));
}


TEST_F(ImmOrgApi, RountripImmutableAst) {
    std::string file       = (__CURRENT_FILE_DIR__ / "corpus/org/all.org");
    std::string source     = readFile(fs::path(file));
    auto        store      = imm::ImmAstContext::init_start_context();
    sem::SemId  write_node = testParseString(source);
    imm::ImmAstVersion v1  = store->addRoot(write_node);
    sem::SemId         read_node = v1.context->get(v1.getRoot());

    Vec<compare_report> out;

    reporting_comparator<sem::SemId<sem::Org>>::compare(
        write_node, read_node, out, {});
    show_compare_reports(out);
}

TEST_F(ImmOrgApi, ImmutableMindMapFromDirectory) {
    std::string file = (__CURRENT_FILE_DIR__ / "corpus/mind_map_directory");
    LOGIC_ASSERTION_CHECK_FMT(fs::exists(file), "{}", file);
    auto store = imm::ImmAstContext::init_start_context();
    auto node  = parseContext->parseDirectory(file);
    ASSERT_TRUE(node.has_value());
    auto version = store->addRoot(node.value());
    auto state   = org::graph::MapGraphState::FromAstContext(
        version.getContext());

    auto conf = org::graph::MapConfig::shared();
    state->addNodeRec(
        version.getContext(), version.getRootAdapter(), conf);
}

TEST_F(ImmOrgApi, ImmAstFieldIteration) {
    auto store = imm::ImmAstContext::init_start_context();
    for (auto const& k : sliceT<OrgSemKind>()) {
        if (k != OrgSemKind::NoNode) {
            switch_node_nullptr(k, [&]<typename N>(N*) {
                N                         tmp{};
                ReflRecursiveVisitContext ctx;
                Vec<imm::ImmReflPathBase> paths;
                reflVisitAll<N>(
                    tmp,
                    imm::ImmReflPathBase{},
                    ctx,
                    [&]<typename T>(
                        imm::ImmReflPathBase const& path, T const& value) {
                        paths.push_back(path);
                    });
            });
        }
    }
}


TEST_F(ImmOrgApi, ItearteParentNodes) {
    setTraceFile(getDebugFile("trace.txt"));
    start->currentTrack->isTrackingParent = [](imm::ImmAdapter const&) {
        return true;
    };


    auto start_node   = testParseString("word0 word2 word4");
    auto replace_node = testParseString("wordXX").at(0).at(0);
    auto v1           = start->init(start_node);
    auto r            = v1.getRootAdapter();
    auto doc_id       = r;
    auto par_id       = doc_id.at(0);
    auto space_id     = par_id.at(1);

    writeTreeRepr(r, getDebugFile("repr.txt"));

    EXPECT_EQ(space_id->getKind(), OrgSemKind::Space);
    {
        imm::ImmParentIdVec parents = v1.context->getParentIds(
            space_id.id);
        EXPECT_EQ(parents.size(), 1);
        EXPECT_TRUE(parents.contains(par_id.id));
        EXPECT_EQ(parents.size(), 1);
    }

    {
        imm::ParentPathMap parents = v1.context->getParentsFor(
            space_id.id);
        EXPECT_EQ(parents.size(), 1);
        EXPECT_TRUE(parents.contains(par_id.id));
        EXPECT_EQ(parents.at(par_id.id).size(), 2);
        EXPECT_EQ(
            parents.at(par_id.id).at(0).path.at(0).getFieldName().name,
            imm::ImmReflFieldId::FromTypeField(&imm::ImmOrg::subnodes));
        EXPECT_EQ(
            parents.at(par_id.id).at(0).path.at(1).getIndex().index, 1);
        EXPECT_EQ(
            parents.at(par_id.id).at(1).path.at(0).getFieldName().name,
            imm::ImmReflFieldId::FromTypeField(&imm::ImmOrg::subnodes));
        EXPECT_EQ(
            parents.at(par_id.id).at(1).path.at(1).getIndex().index, 3);
    }


    {
        Vec<imm::ImmUniqId> paths = v1.context->getPathsFor(space_id.id);
        EXPECT_EQ(paths.size(), 2);
        auto const& p0 = paths.at(0);
        auto const& p1 = paths.at(1);
        EXPECT_EQ(p0.path.root, doc_id.id);
        EXPECT_EQ(p1.path.root, doc_id.id);
    }
}

TEST_F(ImmOrgApi, RadioLinkDetection) {
    setTraceFile(getDebugFile("trace.log"));
    imm::ImmAstVersion init = getInitialVersion(R"(
<<<radiotarget>>> Paragraph with radio links

Other paragraph mentions radiotarget
)");

    imm::ImmAdapter root = init.getRootAdapter();
    writeTreeRepr(root, getDebugFile("repr.txt"));

    imm::ImmAdapter par1 = root.at(1);
    EXPECT_EQ(par1.getKind(), OrgSemKind::Paragraph);
    imm::ImmAdapter radio = par1.at(0);
    EXPECT_EQ(radio.getKind(), OrgSemKind::RadioTarget);
    imm::ImmAdapter par2 = root.at(3);
    EXPECT_EQ(par2.getKind(), OrgSemKind::Paragraph);
    Vec<imm::ImmSubnodeGroup> grouped = imm::getSubnodeGroups(
        init.context, par2);
    EXPECT_EQ(grouped.size(), 7);
    EXPECT_TRUE(grouped.at(0).isSingle());
    EXPECT_TRUE(grouped.at(6).isRadioTarget());
    EXPECT_EQ(grouped.at(6).getRadioTarget().target, radio.id);
}

TEST_F(ImmOrgApi, HashtagDefinitionTracking) {
    setTraceFile(getDebugFile("trace.log"));
    imm::ImmAstVersion init = getInitialVersion(
        R"(
* Subtree with item description
  :properties:
  :hashtag_def: #hashtag1
  :hashtag_def: #nested##[alias1,alias2]
  :end:

Mention #hashtag1 and #nested##alias1 with #nested##alias2

)",
        getDebugFile());

    imm::ImmAdapter root = init.getRootAdapter();
    writeTreeRepr(root, getDebugFile("repr.txt"));
    imm::ImmAdapter t1 = root.at(1);
    EXPECT_EQ(t1.getKind(), OrgSemKind::Subtree);
    imm::ImmAdapter par = t1.at(0);
    EXPECT_EQ2(par.getKind(), OrgSemKind::Paragraph);

    auto group = imm::getSubnodeGroups(init.context, par);

    EXPECT_TRUE(group.at(2).isTrackedHashtag());
    EXPECT_TRUE(group.at(6).isTrackedHashtag());
    EXPECT_TRUE(group.at(10).isTrackedHashtag());
    auto t2  = group.at(2).getTrackedHashtag();
    auto t6  = group.at(6).getTrackedHashtag();
    auto t10 = group.at(10).getTrackedHashtag();

    EXPECT_EQ2(t2.targets.size(), 1);
    EXPECT_EQ2(t2.targets.begin()->second, t1.id);
    EXPECT_EQ2(t2.targets.begin()->first, sem::HashTagFlat{{"hashtag1"}});
    EXPECT_EQ2(t6.targets.size(), 1);
    EXPECT_EQ2(t6.targets.begin()->second, t1.id);
    EXPECT_EQ2(
        t6.targets.begin()->first,
        (sem::HashTagFlat{{"nested", "alias1"}}));
    EXPECT_EQ2(t10.targets.size(), 1);
    EXPECT_EQ2(t10.targets.begin()->second, t1.id);
    EXPECT_EQ2(
        t10.targets.begin()->first,
        (sem::HashTagFlat{{"nested", "alias2"}}));
}


TEST_F(ImmOrgApi, RadioLinkDetectionForSubtree) {
    setTraceFile(getDebugFile("trace.log"));
    imm::ImmAstVersion init = getInitialVersion(R"(
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
)");

    imm::ImmAdapter root = init.getRootAdapter();
    writeTreeRepr(root, getDebugFile("repr.txt"));
    imm::ImmAdapter t1 = root.at(1);
    EXPECT_EQ(t1.getKind(), OrgSemKind::Subtree);
    imm::ImmAdapter t2 = root.at(2);
    EXPECT_EQ(t2.getKind(), OrgSemKind::Subtree);

    imm::ImmAdapterT<imm::ImmSubtree>
        treeAdapter = t1.as<imm::ImmSubtree>();

    Vec<sem::NamedProperty> radioAliases = treeAdapter.getProperties(
        "radio_id");

    EXPECT_EQ(radioAliases.size(), 3);
    EXPECT_EQ(radioAliases.at(0).getRadioId().words, Vec<Str>{"alias1"});
    EXPECT_EQ(radioAliases.at(1).getRadioId().words, Vec<Str>{"alias2"});
    EXPECT_EQ(
        radioAliases.at(2).getRadioId().words,
        (Vec<Str>{"human-readable", "alias"}));

    imm::ImmAdapter par_alias1 = t2.at(0);
    imm::ImmAdapter par_alias2 = t2.at(2);
    imm::ImmAdapter par_human  = t2.at(4);

    EXPECT_EQ(par_alias1.getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(par_alias2.getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(par_human.getKind(), OrgSemKind::Paragraph);

    auto group_alias1 = imm::getSubnodeGroups(init.context, par_alias1);
    EXPECT_EQ(group_alias1.size(), 7);
    EXPECT_TRUE(group_alias1.at(0).isRadioTarget());
    EXPECT_EQ(group_alias1.at(0).getRadioTarget().target, t1.id);

    auto group_alias2 = imm::getSubnodeGroups(init.context, par_alias2);
    EXPECT_EQ(group_alias2.size(), 7);
    EXPECT_TRUE(group_alias2.at(0).isRadioTarget());
    EXPECT_EQ(group_alias2.at(0).getRadioTarget().target, t1.id);

    auto group_human = imm::getSubnodeGroups(init.context, par_human);
    EXPECT_EQ(group_human.size(), 9);
    EXPECT_TRUE(group_human.at(1_B).isRadioTarget());
    EXPECT_EQ(group_human.at(1_B).getRadioTarget().target, t1.id);
}

TEST_F(ImmOrgApi, ReplaceSubnodeAtPath) {
    setTraceFile(getDebugFile("trace.txt"));
    start->currentTrack->isTrackingParent = [](imm::ImmAdapter const&) {
        return true;
    };


    sem::SemId<sem::Org> start_node = testParseString("word0 word2 word4");
    sem::SemId<sem::Org> replace_node = testParseString("wordXX").at(0).at(
        0);

    imm::ImmAstVersion      version1  = start->init(start_node);
    imm::ImmAstContext::Ptr store     = version1.context;
    imm::ImmAdapter         paragraph = version1.getRootAdapter().at(0);
    imm::ImmAstEditContext  ctx       = store->getEditContext();
    auto                    word_xx   = store->add(replace_node, ctx);
    auto                    version2  = store->finishEdit(
        ctx,
        ctx.store().cascadeUpdate(
            version1.getRootAdapter(),
            setSubnode(paragraph, word_xx, 2, ctx),
            ctx));

    auto        store2 = version2.context;
    auto const& c = gen_view(version2.epoch->replaced.allReplacements())
                  | rs::to<Vec>();

    auto const& doc1_id = ctx->adapt(c.at(0).original.value());
    auto const& doc2_id = ctx->adapt(c.at(0).replaced);
    auto const& par1_id = ctx->adapt(c.at(1).original.value());
    auto const& par2_id = ctx->adapt(c.at(1).replaced);

    EXPECT_EQ(doc1_id->getKind(), OrgSemKind::Document);
    EXPECT_EQ(doc2_id->getKind(), OrgSemKind::Document);

    EXPECT_EQ(doc1_id.id.getNodeIndex(), 1);
    EXPECT_EQ(doc2_id.id.getNodeIndex(), 2);

    EXPECT_EQ(par1_id->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(par2_id->getKind(), OrgSemKind::Paragraph);

    EXPECT_EQ(par1_id.id.getNodeIndex(), 1);
    EXPECT_EQ(par2_id.id.getNodeIndex(), 2);

    auto const& doc1 = doc1_id.value<imm::ImmDocument>();
    auto const& doc2 = doc2_id.value<imm::ImmDocument>();
    auto const& par1 = par1_id.value<imm::ImmParagraph>();
    auto const& par2 = par2_id.value<imm::ImmParagraph>();

    EXPECT_EQ(doc1.subnodes.size(), 1);
    EXPECT_EQ(doc1.indexOf(par1_id.id), 0);

    EXPECT_EQ(doc2.subnodes.size(), 1);
    EXPECT_EQ(doc2.indexOf(par2_id.id), 0);


    auto space_id = par1_id.at(1);
    auto word0_id = par1_id.at(0);
    auto word2_id = par1_id.at(2);
    auto word4_id = par1_id.at(4);

    EXPECT_EQ(space_id, par1_id.at(3));
    EXPECT_EQ(space_id, par2_id.at(1));
    EXPECT_EQ(space_id, par2_id.at(3));

    EXPECT_TRUE(store2->currentTrack->isParentOf(par2_id.id, space_id.id));
    {
        auto parents = store->currentTrack->getParentIds(space_id.id);
        EXPECT_EQ(parents.size(), 1);
        EXPECT_EQ(parents.at(0), par1_id.id);
    }

    {
        auto parents = store2->currentTrack->getParentIds(space_id.id);
        EXPECT_EQ(parents.size(), 1);
        EXPECT_EQ(parents.at(0), par2_id.id);
    }


    EXPECT_EQ(word0_id->getKind(), OrgSemKind::Word);
    EXPECT_EQ(word2_id->getKind(), OrgSemKind::Word);
    EXPECT_EQ(word4_id->getKind(), OrgSemKind::Word);

    EXPECT_EQ(word0_id.value<imm::ImmWord>().text, "word0");
    EXPECT_EQ(word2_id.value<imm::ImmWord>().text, "word2");
    EXPECT_EQ(word4_id.value<imm::ImmWord>().text, "word4");

    auto gv = imm::toGraphviz(
        {version1, version2},
        imm::ImmAstGraphvizConf{
            .skippedKinds = SemSet{OrgSemKind::Space},
        });

    hstd::ext::Graphviz gvc;
    gvc.renderToFile("/tmp/ReplaceSubnodeAtPath.png", gv);
    gvc.writeFile("/tmp/ReplaceSubnodeAtPath.dot", gv);
}


struct ImmOrgApiAppModel : ImmOrgApiTestBase {
    struct Row {
        imm::ImmAdapter nameOrigin;
        std::string     name;
        imm::ImmAdapter storyEventOrigin;
        std::string     storyEvent;
        Vec<Row>        nested;
        DESC_FIELDS(
            Row,
            (nameOrigin, name, storyEventOrigin, storyEvent, nested));
    };

    Row buildRow(imm::ImmAdapterT<imm::ImmSubtree> tree) {
        Row result;
        result.name       = join(" ", flatWords(tree.getTitle()));
        result.nameOrigin = tree.getTitle();
        for (auto const& sub : tree.subAs<imm::ImmList>()) {
            if (sub.isDescriptionList()) {
                for (auto const& item : sub.subAs<imm::ImmListItem>()) {
                    auto flat = flatWords(item.getHeader().value());
                    for (auto const& word : flat) {
                        if (word == "story_event") {
                            result.storyEventOrigin = item.at(0);
                            result.storyEvent       = join(
                                " ", flatWords(item.at(0)));
                        }
                    }
                }
            }
        }

        for (auto const& sub : tree.subAs<imm::ImmSubtree>()) {
            result.nested.push_back(buildRow(sub));
        }

        return result;
    }

    Vec<Row> buildRows(imm::ImmAdapter root) {
        Vec<Row> result;
        for (auto const& tree : root.subAs<imm::ImmSubtree>()) {
            result.push_back(buildRow(tree));
        }

        return result;
    }
};

TEST_F(ImmOrgApiAppModel, CreateModel) {
    imm::ImmAstVersion v1 = getInitialVersion(R"(
* Entry 1
** Subtree 2

- =story_event= :: Description

** Subtree 3
)");

    Vec<Row> rows = buildRows(v1.getRootAdapter());
    EXPECT_EQ(rows.size(), 1);
    EXPECT_EQ(rows.at(0).nested.size(), 2);
    EXPECT_EQ(rows.at(0).name, "Entry 1");
    EXPECT_EQ(rows.at(0).nested.at(0).name, "Subtree 2");
    EXPECT_EQ(rows.at(0).nested.at(0).storyEvent, "Description");
}

TEST_F(ImmOrgApiAppModel, EditModel) {
    setTraceFile(getDebugFile("trace.txt"));
    imm::ImmAstVersion v1 = getInitialVersion(R"(
* Entry 1
** Subtree 2
- =story_event= :: Description
)");

    Vec<Row> rows1 = buildRows(v1.getRootAdapter());
    writeTreeRepr(v1.getRootAdapter(), getDebugFile("v1.txt"));
    {
        EXPECT_EQ(rows1.size(), 1);
        EXPECT_EQ(rows1.at(0).nested.size(), 1);
        EXPECT_EQ(rows1.at(0).name, "Entry 1");
        EXPECT_EQ(rows1.at(0).nested.at(0).name, "Subtree 2");
        EXPECT_EQ(rows1.at(0).nested.at(0).storyEvent, "Description");
    }

    imm::ImmAstVersion v2 = v1.getEditVersion(
        [&](imm::ImmAstContext::Ptr ast,
            imm::ImmAstEditContext& ctx) -> imm::ImmAstReplaceGroup {
            auto                    t2 = rows1.at(0).nested.at(0);
            imm::ImmAstReplaceGroup result;
            result.incl(
                imm::replaceNode(
                    t2.nameOrigin,
                    ast->add(
                        org::asOneNode(parseContext->parseString(
                            "New title", "<test-1>")),
                        ctx),
                    ctx));
            result.incl(
                imm::replaceNode(
                    t2.storyEventOrigin,
                    ast->add(
                        org::asOneNode(parseContext->parseString(
                            "New story event description", "<test-2>")),
                        ctx),
                    ctx));
            return result;
        });

    writeTreeRepr(v2.getRootAdapter(), getDebugFile("v2.txt"));
    writeGvHistory(
        {v1, v2},
        "graph.png",
        imm::ImmAstGraphvizConf{
            .withAuxNodes    = true,
            .withEditHistory = false,
        });
    {
        Vec<Row> rows2 = buildRows(v2.getRootAdapter());
        EXPECT_EQ(rows2.size(), 1);
        EXPECT_EQ(rows2.at(0).nested.size(), 1);
        EXPECT_EQ(rows2.at(0).name, "Entry 1");
        EXPECT_EQ(rows2.at(0).nested.at(0).name, "New title");
        EXPECT_EQ(
            rows2.at(0).nested.at(0).storyEvent,
            "New story event description");
    }
}


struct ImmOrgDocumentSelector : public ImmOrgApiTestBase {};

TEST_F(ImmOrgDocumentSelector, GetMatchingNodeByKind) {
    auto                     node = getInitialVersion("bold");
    imm::OrgDocumentSelector selector;
    selector.searchAnyKind({OrgSemKind::Word}, true);

    auto words = selector.getMatches(node.getRootAdapter());

    EXPECT_EQ(words.size(), 1);
    EXPECT_EQ(words.at(0)->getKind(), OrgSemKind::Word);
    EXPECT_EQ(words.at(0).as<imm::ImmWord>()->text, "bold");
}

TEST_F(ImmOrgDocumentSelector, GetMultipleMatchingNodesByKind) {
    auto                     node = getInitialVersion("word *bold*");
    imm::OrgDocumentSelector selector;
    selector.searchAnyKind({OrgSemKind::Word}, true);

    auto words = selector.getMatches(node.getRootAdapter());

    EXPECT_EQ(words.size(), 2);
    EXPECT_EQ(words.at(0).as<imm::ImmWord>()->text, "word");
    EXPECT_EQ(words.at(1).as<imm::ImmWord>()->text, "bold");
}

TEST_F(ImmOrgDocumentSelector, GetDirectlyNestedNode) {
    auto                     node = getInitialVersion("word *bold*");
    imm::OrgDocumentSelector selector;
    selector.searchAnyKind(
        {OrgSemKind::Bold}, false, selector.linkDirectSubnode());
    selector.searchAnyKind({OrgSemKind::Word}, true);

    auto words = selector.getMatches(node.getRootAdapter());

    EXPECT_EQ(words.size(), 1);
    EXPECT_EQ(words.at(0)->getKind(), OrgSemKind::Word);
    EXPECT_EQ(words.at(0).as<imm::ImmWord>()->text, "bold");
}

TEST_F(ImmOrgDocumentSelector, GetSubtreeByTitle) {
    auto doc = getInitialVersion(R"(
* Title1
** Subtitle1
** Subtitle2

Paragraph under subtitle 2

* Multi-part title
)");

    if (true) {
        imm::OrgDocumentSelector selector;
        selector.setTraceFile(getDebugFile("title_search_1"));
        selector.searchSubtreePlaintextTitle({"Title1"}, true);

        auto title1 = selector.getMatches(doc.getRootAdapter());
        EXPECT_EQ(title1.size(), 1);
        EXPECT_EQ(title1.at(0)->getKind(), OrgSemKind::Subtree);
    }

    if (true) {
        imm::OrgDocumentSelector selector;
        selector.setTraceFile(getDebugFile("title_search_2"));
        selector.searchSubtreePlaintextTitle(
            {"Subtitle2"}, false, selector.linkIndirectSubnode());
        selector.searchAnyKind({OrgSemKind::Word}, true);

        auto words = selector.getMatches(doc.getRootAdapter());
        EXPECT_EQ(words.size(), 5);
        // Subtree nodes are added as targets in the post-order DFS
        // traversal over all 'nested' elements. First the words in subtree
        // are collected.
        EXPECT_EQ(words.at(0).as<imm::ImmWord>()->text, "Paragraph");
        EXPECT_EQ(words.at(1).as<imm::ImmWord>()->text, "under");
        EXPECT_EQ(words.at(2).as<imm::ImmWord>()->text, "subtitle");
        EXPECT_EQ(words.at(3).as<imm::ImmWord>()->text, "2");
        // Then visitation gets to the subtree title itself. Nested fields
        // for each node are iterated starting from the base's fields and
        // then to the concrete type -- also in the DFS order.
        EXPECT_EQ(
            words.at(4).as<imm::ImmWord>()->text->toBase(), "Subtitle2");
    }

    if (true) {
        imm::OrgDocumentSelector selector;
        selector.setTraceFile(getDebugFile("title_search_3"));
        selector.searchSubtreePlaintextTitle(
            {"Subtitle2"},
            false,
            selector.linkField(
                imm::ImmReflFieldId::FromTypeField(
                    &imm::ImmOrg::subnodes)));
        selector.searchAnyKind({OrgSemKind::Word}, true);

        auto words = selector.getMatches(doc.getRootAdapter());
        EXPECT_EQ(words.size(), 4);
        // Subtree nodes are added as targets in the post-order DFS
        // traversal over all 'nested' elements. First the words in subtree
        // are collected.
        EXPECT_EQ(words.at(0).as<imm::ImmWord>()->text, "Paragraph");
        EXPECT_EQ(words.at(1).as<imm::ImmWord>()->text, "under");
        EXPECT_EQ(words.at(2).as<imm::ImmWord>()->text, "subtitle");
        EXPECT_EQ(words.at(3).as<imm::ImmWord>()->text, "2");
    }
}

TEST_F(ImmOrgDocumentSelector, GetSubtreeAtPath) {
    auto node = getInitialVersion(R"(
* Title1
** Subtitle1
Content1
** Subtitle2
Content2
* Title2
)");

    imm::OrgDocumentSelector selector;
    selector.searchSubtreePlaintextTitle(
        {"Title1"}, false, selector.linkIndirectSubnode());
    selector.searchSubtreePlaintextTitle({"Subtitle1"}, true);
    auto matches = selector.getMatches(node.getRootAdapter());
    EXPECT_EQ(matches.size(), 1);
}

TEST_F(ImmOrgDocumentSelector, EarlyVisitExit) {
    auto node = getInitialVersion(R"(
*** Content
Subnode
** Other content
First
*** Nested subtree
)");

    imm::OrgDocumentSelector      selector;
    UnorderedMap<OrgSemKind, int> counts;

    selector.searchPredicate(
        [&](imm::ImmAdapter const& node) -> imm::OrgSelectorResult {
            ++counts[node->getKind()];
            return imm::OrgSelectorResult{
                .isMatching     = node->is(OrgSemKind::Subtree),
                .tryNestedNodes = !node->is(OrgSemKind::Subtree),
            };
        },
        false);

    selector.getMatches(node.getRootAdapter());

    EXPECT_EQ(counts.at(OrgSemKind::Subtree), 2);
    EXPECT_EQ(counts.at(OrgSemKind::Document), 1);
    EXPECT_EQ(counts.get(OrgSemKind::Word), std::nullopt);
}

TEST_F(ImmOrgDocumentSelector, NonLeafSubtrees) {
    auto doc = getInitialVersion(R"(
* s1
** s2
* s3
*** s4
* s5
* s6
** s7
)");

    imm::OrgDocumentSelector selector;
    selector.searchAnyKind(
        {OrgSemKind::Subtree}, true, selector.linkIndirectSubnode());

    selector.searchAnyKind({OrgSemKind::Subtree}, false);

    Vec<imm::ImmAdapter> subtrees = selector.getMatches(
        doc.getRootAdapter());

    EXPECT_EQ(subtrees.size(), 3);
    auto titles = subtrees
                | rv::transform([](imm::ImmAdapter const& id) -> Vec<Str> {
                      return flatWords(id.at(
                          imm::ImmReflFieldId::FromTypeField<
                              imm::ImmSubtree>(&imm::ImmSubtree::title)));
                  })
                | rs::to<Vec>();

    std::sort(titles.begin(), titles.end());
    EXPECT_EQ(titles.at(0), Vec<Str>{"s1"});
    EXPECT_EQ(titles.at(1), Vec<Str>{"s3"});
    EXPECT_EQ(titles.at(2), Vec<Str>{"s6"});
}

TEST_F(ImmOrgDocumentSelector, SubtreesWithDateInTitleAndBody) {
    auto doc = getInitialVersion(R"(
* [2024-02-12] In title
* In description
[2024-02-12]
)");

    {
        imm::OrgDocumentSelector selector;
        selector.searchAnyKind(
            {OrgSemKind::Subtree},
            true,
            selector.linkField(
                imm::ImmReflFieldId::FromTypeField(
                    &imm::ImmSubtree::title)));
        selector.searchAnyKind({OrgSemKind::Time}, false);
        auto subtrees = selector.getMatches(doc.getRootAdapter());
        EXPECT_EQ(subtrees.size(), 1);
    }

    {
        imm::OrgDocumentSelector selector;
        selector.searchAnyKind(
            {OrgSemKind::Subtree}, true, selector.linkIndirectSubnode());
        selector.searchAnyKind({OrgSemKind::Time}, false);
        auto subtrees = selector.getMatches(doc.getRootAdapter());
        EXPECT_EQ(subtrees.size(), 2);
    }
}
