#include "tOrgTestCommon.hpp"

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
    auto s0            = org::ImmAstContext::init_start_context();
    auto [store, root] = s0->addRoot(node);
    ColStream os;
    store->format(os);
    writeFile("/tmp/StoreNode.txt", os.getBuffer().toString(false));
}


TEST_F(ImmOrgApi, RountripImmutableAst) {
    std::string file       = (__CURRENT_FILE_DIR__ / "corpus/org/all.org");
    std::string source     = readFile(fs::path(file));
    auto        store      = org::ImmAstContext::init_start_context();
    sem::SemId  write_node = testParseString(source);
    org::ImmAstVersion v1  = store->addRoot(write_node);
    sem::SemId         read_node = v1.context->get(v1.getRoot());

    Vec<compare_report> out;

    reporting_comparator<sem::SemId<sem::Org>>::compare(
        write_node, read_node, out, {});
    show_compare_reports(out);
}


TEST_F(ImmOrgApi, ImmAstFieldIteration) {
    auto store = org::ImmAstContext::init_start_context();
    for (auto const& k : sliceT<OrgSemKind>()) {
        if (k != OrgSemKind::None) {
            switch_node_nullptr(k, [&]<typename N>(N*) {
                N                         tmp{};
                ReflRecursiveVisitContext ctx;
                Vec<org::ImmReflPathBase> paths;
                reflVisitAll<N>(
                    tmp,
                    org::ImmReflPathBase{},
                    ctx,
                    [&]<typename T>(
                        org::ImmReflPathBase const& path, T const& value) {
                        paths.push_back(path);
                    });
            });
        }
    }
}


TEST_F(ImmOrgApi, ItearteParentNodes) {
    setTraceFile(getDebugFile("trace.txt"));
    start->currentTrack->isTrackingParent = [](org::ImmAdapter const&) {
        return true;
    };


    auto start_node   = testParseString("word0 word2 word4");
    auto replace_node = testParseString("wordXX").at(0).at(0);
    auto v1           = start->init(start_node);
    auto r            = v1.getRootAdapter();
    auto doc_id       = r;
    auto par_id       = doc_id.at(0);
    auto space_id     = par_id.at(1);

    EXPECT_EQ(space_id->getKind(), OrgSemKind::Space);
    {
        org::ImmParentIdVec parents = v1.context->getParentIds(
            space_id.id);
        EXPECT_EQ(parents.size(), 1);
        EXPECT_TRUE(parents.contains(par_id.id));
        EXPECT_EQ(parents.size(), 1);
    }

    {
        org::ParentPathMap parents = v1.context->getParentsFor(
            space_id.id);
        EXPECT_EQ(parents.size(), 1);
        EXPECT_TRUE(parents.contains(par_id.id));
        EXPECT_EQ(parents.at(par_id.id).size(), 2);
        EXPECT_EQ(
            parents.at(par_id.id).at(0).path.at(0).getFieldName().name,
            org::ImmReflFieldId::FromTypeField(&org::ImmOrg::subnodes));
        EXPECT_EQ(
            parents.at(par_id.id).at(0).path.at(1).getIndex().index, 1);
        EXPECT_EQ(
            parents.at(par_id.id).at(1).path.at(0).getFieldName().name,
            org::ImmReflFieldId::FromTypeField(&org::ImmOrg::subnodes));
        EXPECT_EQ(
            parents.at(par_id.id).at(1).path.at(1).getIndex().index, 3);
    }


    {
        Vec<org::ImmUniqId> paths = v1.context->getPathsFor(space_id.id);
        EXPECT_EQ(paths.size(), 2);
        auto const& p0 = paths.at(0);
        auto const& p1 = paths.at(1);
        EXPECT_EQ(p0.path.root, doc_id.id);
        EXPECT_EQ(p1.path.root, doc_id.id);
    }
}

TEST_F(ImmOrgApi, RadioLinkDetection) {
    setTraceFile(getDebugFile("trace.log"));
    org::ImmAstVersion init = getInitialVersion(R"(
<<<radiotarget>>> Paragraph with radio links

Other paragraph mentions radiotarget
)");

    org::ImmAdapter root = init.getRootAdapter();
    writeTreeRepr(root, "repr.txt");

    org::ImmAdapter par1 = root.at(1);
    EXPECT_EQ(par1.getKind(), OrgSemKind::Paragraph);
    org::ImmAdapter radio = par1.at(0);
    EXPECT_EQ(radio.getKind(), OrgSemKind::RadioTarget);
    org::ImmAdapter par2 = root.at(3);
    EXPECT_EQ(par2.getKind(), OrgSemKind::Paragraph);
    Vec<org::ImmSubnodeGroup> grouped = org::getSubnodeGroups(par2);
    EXPECT_EQ(grouped.size(), 7);
    EXPECT_TRUE(grouped.at(0).isSingle());
    EXPECT_TRUE(grouped.at(6).isRadioTarget());
    EXPECT_EQ(grouped.at(6).getRadioTarget().target, radio.id);
}


TEST_F(ImmOrgApi, RadioLinkDetectionForSubtree) {
    setTraceFile(getDebugFile("trace.log"));
    org::ImmAstVersion init = getInitialVersion(R"(
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

    org::ImmAdapter root = init.getRootAdapter();
    writeTreeRepr(root, "repr.txt");
    org::ImmAdapter t1 = root.at(1);
    EXPECT_EQ(t1.getKind(), OrgSemKind::Subtree);
    org::ImmAdapter t2 = root.at(2);
    EXPECT_EQ(t2.getKind(), OrgSemKind::Subtree);

    org::ImmAdapterT<org::ImmSubtree>
        treeAdapter = t1.as<org::ImmSubtree>();

    Vec<sem::NamedProperty> radioAliases = treeAdapter.getProperties(
        "radio_id");

    EXPECT_EQ(radioAliases.size(), 3);
    EXPECT_EQ(radioAliases.at(0).getRadioId().words, Vec<Str>{"alias1"});
    EXPECT_EQ(radioAliases.at(1).getRadioId().words, Vec<Str>{"alias2"});
    EXPECT_EQ(
        radioAliases.at(2).getRadioId().words,
        (Vec<Str>{"human-readable", "alias"}));

    org::ImmAdapter par_alias1 = t2.at(0);
    org::ImmAdapter par_alias2 = t2.at(2);
    org::ImmAdapter par_human  = t2.at(4);

    EXPECT_EQ(par_alias1.getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(par_alias2.getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(par_human.getKind(), OrgSemKind::Paragraph);

    auto group_alias1 = org::getSubnodeGroups(par_alias1);
    EXPECT_EQ(group_alias1.size(), 7);
    EXPECT_TRUE(group_alias1.at(0).isRadioTarget());
    EXPECT_EQ(group_alias1.at(0).getRadioTarget().target, t1.id);

    auto group_alias2 = org::getSubnodeGroups(par_alias2);
    EXPECT_EQ(group_alias2.size(), 7);
    EXPECT_TRUE(group_alias2.at(0).isRadioTarget());
    EXPECT_EQ(group_alias2.at(0).getRadioTarget().target, t1.id);

    auto group_human = org::getSubnodeGroups(par_human);
    EXPECT_EQ(group_human.size(), 9);
    EXPECT_TRUE(group_human.at(1_B).isRadioTarget());
    EXPECT_EQ(group_human.at(1_B).getRadioTarget().target, t1.id);
}

TEST_F(ImmOrgApi, ReplaceSubnodeAtPath) {
    setTraceFile(getDebugFile("trace.txt"));
    start->currentTrack->isTrackingParent = [](org::ImmAdapter const&) {
        return true;
    };


    sem::SemId<sem::Org> start_node = testParseString("word0 word2 word4");
    sem::SemId<sem::Org> replace_node = testParseString("wordXX").at(0).at(
        0);

    org::ImmAstVersion      version1     = start->init(start_node);
    org::ImmAstContext::Ptr store        = version1.context;
    org::ImmAdapter         paragraph    = version1.getRootAdapter().at(0);
    org::ImmAstEditContext  ctx          = store->getEditContext();
    auto                    __absl_scope = ctx.collectAbslLogs();
    auto                    word_xx      = store->add(replace_node, ctx);
    auto                    version2     = store->finishEdit(
        ctx,
        ctx.store().cascadeUpdate(
            version1.getRootAdapter(),
            setSubnode(paragraph, word_xx, 2, ctx),
            ctx));

    auto        store2 = version2.context;
    auto const& c = gen_view(version2.epoch.replaced.allReplacements())
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

    auto const& doc1 = doc1_id.value<org::ImmDocument>();
    auto const& doc2 = doc2_id.value<org::ImmDocument>();
    auto const& par1 = par1_id.value<org::ImmParagraph>();
    auto const& par2 = par2_id.value<org::ImmParagraph>();

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

    EXPECT_EQ(word0_id.value<org::ImmWord>().text, "word0");
    EXPECT_EQ(word2_id.value<org::ImmWord>().text, "word2");
    EXPECT_EQ(word4_id.value<org::ImmWord>().text, "word4");

    auto gv = org::toGraphviz(
        {version1, version2},
        org::ImmAstGraphvizConf{
            .skippedKinds = SemSet{OrgSemKind::Space},
        });

    Graphviz gvc;
    gvc.renderToFile("/tmp/ReplaceSubnodeAtPath.png", gv);
    gvc.writeFile("/tmp/ReplaceSubnodeAtPath.dot", gv);
}


struct ImmOrgApiEdit : ImmOrgApiTestBase {};

Vec<int> getDfsSubtreeLevels(org::ImmAdapter n) {
    Vec<int>                    result;
    Func<void(org::ImmAdapter)> aux;
    aux = [&](org::ImmAdapter n) {
        if (auto tree = n.asOpt<org::ImmSubtree>()) {
            result.push_back(tree.value()->level);
        }
        for (auto const& it : n.sub()) { aux(it); }
    };
    aux(n);
    return result;
}


Str getSubtreeDash() {
    // 0     * s1
    // 0.0   ** s200
    // 0.0.0 *** s3000
    // 0.0.1 *** s3001
    // 0.1   ** s201
    // 0.1.0 *** s3010
    return R"(* s1
** s200
*** s3000
*** s3001
** s201
*** s3010
)";
}

TEST_F(ImmOrgApiEdit, LeafSubtreeDemote) {
    setTraceFile(getDebugFile("trace.txt"));
    org::ImmAstVersion v1 = getInitialVersion(getSubtreeDash());

    {
        auto root = v1.getRootAdapter();
        writeFile(
            "/tmp/SubtreePromotion_repr.txt",
            root.treeRepr().toString(false));
    }

    Vec<int> path{0, 1, 0};

    org::ImmAstVersion v2 = v1.getEditVersion(
        [&](org::ImmAstContext::Ptr ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            auto root  = v1.getRootAdapter();
            auto s3010 = root.at(path);
            EXPECT_EQ(s3010->getKind(), OrgSemKind::Subtree);
            EXPECT_EQ(s3010->as<org::ImmSubtree>()->level, 3);
            return demoteSubtree(
                s3010, org::SubtreeMove::ForceLevels, ctx);
        });

    org::ImmAdapter::TreeReprConf conf{.withAuxFields = true};

    writeFile(
        getDebugFile("repr_v1.txt"),
        v1.getRootAdapter().treeRepr(conf).toString(false));

    writeFile(
        getDebugFile("repr_v2.txt"),
        v2.getRootAdapter().treeRepr(conf).toString(false));

    ColStream os;
    start->format(os);
    writeFile(getDebugFile("store.txt"), os.getBuffer().toString(false));
    writeGvHistory({v1, v2}, "v1_v2");

    {
        auto r     = v1.getRootAdapter();
        auto s3010 = r.at(path);
        EXPECT_EQ(s3010->getKind(), OrgSemKind::Subtree);
        EXPECT_EQ(s3010->as<org::ImmSubtree>()->level, 3);
        auto levels = getDfsSubtreeLevels(r);
        EXPECT_EQ(levels, (Vec<int>{1, 2, 3, 3, 2, 3}));
    }

    {
        auto r     = v2.getRootAdapter();
        auto s3010 = r.at(path);
        EXPECT_EQ(s3010->getKind(), OrgSemKind::Subtree);
        EXPECT_EQ(s3010->as<org::ImmSubtree>()->level, 4);
        auto levels = getDfsSubtreeLevels(r);
        EXPECT_EQ(levels, (Vec<int>{1, 2, 3, 3, 2, 4}));
    }
}


TEST_F(ImmOrgApiEdit, RecursiveSubtreeDemote_OneNested) {
    setTraceFile(getDebugFile("trace.txt"));
    org::ImmAstVersion v1 = getInitialVersion(getSubtreeDash());
    writeTreeRepr(v1.getRootAdapter(), "repr_v1.txt");

    org::ImmAstVersion v2 = v1.getEditVersion(
        [&](org::ImmAstContext::Ptr ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            auto root = v1.getRootAdapter();
            auto s201 = root.at(Vec{0, 1});
            EXPECT_EQ(s201->getKind(), OrgSemKind::Subtree);
            EXPECT_EQ(s201->as<org::ImmSubtree>()->level, 2);
            return demoteSubtree(s201, org::SubtreeMove::ForceLevels, ctx);
        });

    writeGvHistory({v1, v2}, "v1_v2");

    auto r = v2.getRootAdapter();
    writeTreeRepr(r, "repr_v2.txt");
    auto s201 = r.at(Vec{0, 0, 2});
    EXPECT_EQ(s201->getKind(), OrgSemKind::Subtree);
    EXPECT_EQ(s201->as<org::ImmSubtree>()->level, 3);
    auto s3010 = r.at({0, 0, 2, 0});
    EXPECT_EQ(s3010->getKind(), OrgSemKind::Subtree);
    EXPECT_EQ(s3010->as<org::ImmSubtree>()->level, 4);
    auto levels = getDfsSubtreeLevels(r);
    EXPECT_EQ(levels, (Vec<int>{1, 2, 3, 3, 3, 4}));
}

TEST_F(ImmOrgApiEdit, RecursiveSubtreeDemote_All) {
    setTraceFile(getDebugFile("trace.txt"));
    org::ImmAstVersion v1 = getInitialVersion(getSubtreeDash());

    org::ImmAstVersion v2 = v1.getEditVersion(
        [&](org::ImmAstContext::Ptr ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            auto root = v1.getRootAdapter();
            auto s1   = root.at(0);
            return demoteSubtree(s1, org::SubtreeMove::ForceLevels, ctx);
        });

    writeGvHistory({v1, v2}, "v1_v2");

    EXPECT_EQ(
        getDfsSubtreeLevels(v1.getRootAdapter()),
        (Vec<int>{1, 2, 3, 3, 2, 3}));

    EXPECT_EQ(
        getDfsSubtreeLevels(v2.getRootAdapter()),
        (Vec<int>{2, 3, 4, 4, 3, 4}));
}

TEST_F(ImmOrgApiEdit, RecursiveSubtreeDemote_WithParentChange) {
    setTraceFile(getDebugFile("trace.txt"));
    org::ImmAstVersion v1 = getInitialVersion(getSubtreeDash());

    auto demotePath = [&](org::ImmAstVersion v,
                          CVec<int>          path) -> org::ImmAstVersion {
        return v.getEditVersion(
            [&](org::ImmAstContext::Ptr ast,
                org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
                auto root = v.getRootAdapter();
                auto s1   = root.at(path);
                return demoteSubtree(
                    s1, org::SubtreeMove::ForceLevels, ctx);
            });
    };

    org::ImmAstVersion v2 = demotePath(v1, {0, 0, 1});

    {
        auto r = v2.getRootAdapter();

        writeTreeRepr(v1.getRootAdapter(), "repr_v1.txt");
        writeTreeRepr(v2.getRootAdapter(), "repr_v2.txt");
        writeGvHistory({v1, v2}, "v1_v2");

        EXPECT_EQ(getDfsSubtreeLevels(r), (Vec<int>{1, 2, 3, 4, 2, 3}));

        Vec<int> p0000 = {0, 0, 0, 0};
        Vec<int> p000  = {0, 0, 0};
        Vec<int> p00   = {0, 0};
        Vec<int> p0    = {0};


        EXPECT_TRUE(r.at(p0000).is(OrgSemKind::Subtree));
        EXPECT_EQ(r.at(p0000).as<org::ImmSubtree>()->level, 4);
        EXPECT_EQ(r.at(p0000).getParent().value().id, r.at(p000).id);
        EXPECT_EQ(r.at(p000).at(0).id, r.at(p0000).id);

        EXPECT_EQ(r.at(p000).as<org::ImmSubtree>()->level, 3);
        EXPECT_EQ(r.at(p000).getParent().value().id, r.at(p00).id);
        EXPECT_EQ(r.at(p00).at(0).id, r.at(p000).id);

        EXPECT_EQ(r.at(p00).as<org::ImmSubtree>()->level, 2);
        EXPECT_EQ(r.at(p0).at(0).id, r.at(p00).id);
    }

    org::ImmAstVersion v3 = demotePath(v2, {0, 1});
    writeTreeRepr(v3.getRootAdapter(), "repr_v3.txt");
    org::ImmAstVersion v4 = demotePath(v3, {0, 0, 1});
    writeTreeRepr(v4.getRootAdapter(), "repr_v4.txt");
    org::ImmAstVersion v5 = demotePath(v4, {0, 0, 0, 1});
    writeTreeRepr(v5.getRootAdapter(), "repr_v5.txt");
    writeGvHistory(
        {v1, v2, v3, v4, v5},
        "v_final",
        org::ImmAstGraphvizConf{
            .withAuxNodes      = true,
            .withEditHistory   = false,
            .withEpochClusters = false,
        });

    {
        auto r = v5.getRootAdapter();
        EXPECT_TRUE(
            r.at({0, 0, 0, 0, 0, 0}).isSubnodeOf(r.at({0, 0, 0, 0, 0})));
        EXPECT_EQ(
            r.at({0, 0, 0, 0, 0, 0}).as<org::ImmSubtree>()->level, 6);
        EXPECT_EQ(
            r.at({0, 0, 0, 0, 0, 0}).as<org::ImmSubtree>()->level, 6);
        EXPECT_EQ(r.at({0, 0, 0, 0, 0}).as<org::ImmSubtree>()->level, 5);
        EXPECT_EQ(r.at({0, 0, 0, 0}).as<org::ImmSubtree>()->level, 4);
        EXPECT_EQ(r.at({0, 0, 0}).as<org::ImmSubtree>()->level, 3);
    }
}

TEST_F(ImmOrgApiEdit, PhysicalDemote) {
    setTraceFile(getDebugFile("trace.txt"));
    org::ImmAstVersion v1 = getInitialVersion(getSubtreeDash());
    writeTreeRepr(v1.getRootAdapter(), "repr_v1.txt");

    org::ImmAstVersion v2 = v1.getEditVersion(
        [&](org::ImmAstContext::Ptr ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            auto root = v1.getRootAdapter();
            auto s1   = root.at(Vec{0, 0});
            return demoteSubtree(s1, org::SubtreeMove::Physical, ctx);
        });

    writeGvHistory({v1, v2}, "v1_v2");
    writeTreeRepr(v2.getRootAdapter(), "repr_v2.txt");

    EXPECT_EQ(
        getDfsSubtreeLevels(v1.getRootAdapter()),
        (Vec<int>{1, 2, 3, 3, 2, 3}));

    EXPECT_EQ(
        getDfsSubtreeLevels(v2.getRootAdapter()),
        (Vec<int>{1, 3, 3, 3, 2, 3}));
}

TEST_F(ImmOrgApiEdit, ResetTitle) {
    setTraceFile(getDebugFile("trace.txt"));
    org::ImmAstVersion v1 = getInitialVersion("* subtree");
    writeTreeRepr(v1.getRootAdapter(), "repr_v1.txt");

    org::ImmAstVersion v2 = v1.getEditVersion(
        [&](org::ImmAstContext::Ptr ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            return ctx.store().updateNode<org::ImmSubtree>(
                v1.getRootAdapter().at(0), ctx, [&](org::ImmSubtree tree) {
                    tree.title = ctx->add(
                                        sem::asOneNode(
                                            sem::parseString("replaced")),
                                        ctx)
                                     .as<org::ImmParagraph>();
                    return tree;
                });
        });

    writeGvHistory({v1, v2}, "v1_v2");
    writeTreeRepr(v2.getRootAdapter(), "repr_v2.txt");

    {
        auto tree = v1.getRootAdapter().at(0).as<org::ImmSubtree>();
        EXPECT_EQ(
            tree.pass(tree->title).at(0).as<org::ImmWord>()->text,
            "subtree");
    }

    {
        auto tree = v2.getRootAdapter().at(0).as<org::ImmSubtree>();
        EXPECT_EQ(
            tree.pass(tree->title).at(0).as<org::ImmWord>()->text,
            "replaced");
    }
}

TEST_F(ImmOrgApiEdit, MoveSubnodes) {
    setTraceFile(getDebugFile("trace.txt"));
    org::ImmAstVersion v1 = getInitialVersion("zero one two three");

    auto move =
        [&](int position, int offset, bool bounded) -> org::ImmAstVersion {
        return v1.getEditVersion(
            [&](org::ImmAstContext::Ptr ast,
                org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
                auto update = moveSubnode(
                    v1.getRootAdapter().at(0),
                    position,
                    offset,
                    ctx,
                    bounded);
                if (update) {
                    return *update;
                } else {
                    return {};
                }
            });
    };

    Func<Vec<Str>(org::ImmAdapter const&)> flat;
    flat = [&](org::ImmAdapter const& it) -> Vec<Str> {
        Vec<Str> result;
        if (auto i = it.asOpt<org::ImmWord>(); i) {
            result.push_back(i.value()->text);
        } else if (auto i = it.asOpt<org::ImmSpace>(); i) {
            result.push_back(i.value()->text);
        } else {
            for (auto const& sub : it.sub()) { result.append(flat(sub)); }
        }

        return result;
    };

    writeGvHistory({v1}, "graph_v1");

    org::ImmAstVersion v2 = move(0, 2, true);
    org::ImmAstVersion v3 = move(0, 4, true);
    org::ImmAstVersion v4 = move(2, -2, true);

    writeGvHistory({v1, v2, v3, v4}, "graph");
    EXPECT_EQ(
        flat(v1.getRootAdapter()),
        (Vec<Str>{"zero", " ", "one", " ", "two", " ", "three"}));
    EXPECT_EQ(
        flat(v2.getRootAdapter()),
        (Vec<Str>{" ", "one", "zero", " ", "two", " ", "three"}));
    EXPECT_EQ(
        flat(v3.getRootAdapter()),
        (Vec<Str>{" ", "one", " ", "two", "zero", " ", "three"}));
    EXPECT_EQ(
        flat(v4.getRootAdapter()),
        (Vec<Str>{"one", "zero", " ", " ", "two", " ", "three"}));
}

struct ImmOrgApiAppModel : ImmOrgApiTestBase {
    struct Row {
        org::ImmAdapter nameOrigin;
        std::string     name;
        org::ImmAdapter storyEventOrigin;
        std::string     storyEvent;
        Vec<Row>        nested;
        DESC_FIELDS(
            Row,
            (nameOrigin, name, storyEventOrigin, storyEvent, nested));
    };

    Row buildRow(org::ImmAdapterT<org::ImmSubtree> tree) {
        Row result;
        result.name       = join(" ", flatWords(tree.getTitle()));
        result.nameOrigin = tree.getTitle();
        for (auto const& sub : tree.subAs<org::ImmList>()) {
            if (sub.isDescriptionList()) {
                for (auto const& item : sub.subAs<org::ImmListItem>()) {
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

        for (auto const& sub : tree.subAs<org::ImmSubtree>()) {
            result.nested.push_back(buildRow(sub));
        }

        return result;
    }

    Vec<Row> buildRows(org::ImmAdapter root) {
        Vec<Row> result;
        for (auto const& tree : root.subAs<org::ImmSubtree>()) {
            result.push_back(buildRow(tree));
        }

        return result;
    }
};

TEST_F(ImmOrgApiAppModel, CreateModel) {
    org::ImmAstVersion v1 = getInitialVersion(R"(
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
    org::ImmAstVersion v1 = getInitialVersion(R"(
* Entry 1
** Subtree 2
- =story_event= :: Description
)");

    Vec<Row> rows1 = buildRows(v1.getRootAdapter());
    writeTreeRepr(v1.getRootAdapter(), "v1.txt");
    {
        EXPECT_EQ(rows1.size(), 1);
        EXPECT_EQ(rows1.at(0).nested.size(), 1);
        EXPECT_EQ(rows1.at(0).name, "Entry 1");
        EXPECT_EQ(rows1.at(0).nested.at(0).name, "Subtree 2");
        EXPECT_EQ(rows1.at(0).nested.at(0).storyEvent, "Description");
    }

    org::ImmAstVersion v2 = v1.getEditVersion(
        [&](org::ImmAstContext::Ptr ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            auto                    t2 = rows1.at(0).nested.at(0);
            org::ImmAstReplaceGroup result;
            result.incl(org::replaceNode(
                t2.nameOrigin,
                ast->add(
                    sem::asOneNode(sem::parseString("New title")), ctx),
                ctx));
            result.incl(org::replaceNode(
                t2.storyEventOrigin,
                ast->add(
                    sem::asOneNode(
                        sem::parseString("New story event description")),
                    ctx),
                ctx));
            return result;
        });

    writeTreeRepr(v2.getRootAdapter(), "v2.txt");
    writeGvHistory(
        {v1, v2},
        "graph.png",
        org::ImmAstGraphvizConf{
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
    org::OrgDocumentSelector selector;
    selector.searchAnyKind({OrgSemKind::Word}, true);

    auto words = selector.getMatches(node.getRootAdapter());

    EXPECT_EQ(words.size(), 1);
    EXPECT_EQ(words.at(0)->getKind(), OrgSemKind::Word);
    EXPECT_EQ(words.at(0).as<org::ImmWord>()->text, "bold");
}

TEST_F(ImmOrgDocumentSelector, GetMultipleMatchingNodesByKind) {
    auto                     node = getInitialVersion("word *bold*");
    org::OrgDocumentSelector selector;
    selector.searchAnyKind({OrgSemKind::Word}, true);

    auto words = selector.getMatches(node.getRootAdapter());

    EXPECT_EQ(words.size(), 2);
    EXPECT_EQ(words.at(0).as<org::ImmWord>()->text, "word");
    EXPECT_EQ(words.at(1).as<org::ImmWord>()->text, "bold");
}

TEST_F(ImmOrgDocumentSelector, GetDirectlyNestedNode) {
    auto                     node = getInitialVersion("word *bold*");
    org::OrgDocumentSelector selector;
    selector.searchAnyKind(
        {OrgSemKind::Bold}, false, selector.linkDirectSubnode());
    selector.searchAnyKind({OrgSemKind::Word}, true);

    auto words = selector.getMatches(node.getRootAdapter());

    EXPECT_EQ(words.size(), 1);
    EXPECT_EQ(words.at(0)->getKind(), OrgSemKind::Word);
    EXPECT_EQ(words.at(0).as<org::ImmWord>()->text, "bold");
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
        org::OrgDocumentSelector selector;
        selector.setTraceFile(getDebugFile("title_search_1"));
        selector.searchSubtreePlaintextTitle({"Title1"}, true);

        auto title1 = selector.getMatches(doc.getRootAdapter());
        EXPECT_EQ(title1.size(), 1);
        EXPECT_EQ(title1.at(0)->getKind(), OrgSemKind::Subtree);
    }

    if (true) {
        org::OrgDocumentSelector selector;
        selector.setTraceFile(getDebugFile("title_search_2"));
        selector.searchSubtreePlaintextTitle(
            {"Subtitle2"}, false, selector.linkIndirectSubnode());
        selector.searchAnyKind({OrgSemKind::Word}, true);

        auto words = selector.getMatches(doc.getRootAdapter());
        EXPECT_EQ(words.size(), 5) << fmt1(words);
        // Subtree nodes are added as targets in the post-order DFS
        // traversal over all 'nested' elements. First the words in subtree
        // are collected.
        EXPECT_EQ(words.at(0).as<org::ImmWord>()->text, "Paragraph");
        EXPECT_EQ(words.at(1).as<org::ImmWord>()->text, "under");
        EXPECT_EQ(words.at(2).as<org::ImmWord>()->text, "subtitle");
        EXPECT_EQ(words.at(3).as<org::ImmWord>()->text, "2");
        // Then visitation gets to the subtree title itself. Nested fields
        // for each node are iterated starting from the base's fields and
        // then to the concrete type -- also in the DFS order.
        EXPECT_EQ(
            words.at(4).as<org::ImmWord>()->text->toBase(), "Subtitle2");
    }

    if (true) {
        org::OrgDocumentSelector selector;
        selector.setTraceFile(getDebugFile("title_search_3"));
        selector.searchSubtreePlaintextTitle(
            {"Subtitle2"},
            false,
            selector.linkField(org::ImmReflFieldId::FromTypeField(
                &org::ImmOrg::subnodes)));
        selector.searchAnyKind({OrgSemKind::Word}, true);

        auto words = selector.getMatches(doc.getRootAdapter());
        EXPECT_EQ(words.size(), 4);
        // Subtree nodes are added as targets in the post-order DFS
        // traversal over all 'nested' elements. First the words in subtree
        // are collected.
        EXPECT_EQ(words.at(0).as<org::ImmWord>()->text, "Paragraph");
        EXPECT_EQ(words.at(1).as<org::ImmWord>()->text, "under");
        EXPECT_EQ(words.at(2).as<org::ImmWord>()->text, "subtitle");
        EXPECT_EQ(words.at(3).as<org::ImmWord>()->text, "2");
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

    org::OrgDocumentSelector selector;
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

    org::OrgDocumentSelector      selector;
    UnorderedMap<OrgSemKind, int> counts;

    selector.searchPredicate(
        [&](org::ImmAdapter const& node) -> org::OrgSelectorResult {
            ++counts[node->getKind()];
            return org::OrgSelectorResult{
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

    org::OrgDocumentSelector selector;
    selector.searchAnyKind(
        {OrgSemKind::Subtree}, true, selector.linkIndirectSubnode());

    selector.searchAnyKind({OrgSemKind::Subtree}, false);

    Vec<org::ImmAdapter> subtrees = selector.getMatches(
        doc.getRootAdapter());

    EXPECT_EQ(subtrees.size(), 3);
    auto titles = subtrees
                | rv::transform([](org::ImmAdapter const& id) -> Vec<Str> {
                      return flatWords(id.at(
                          org::ImmReflFieldId::FromTypeField<
                              org::ImmSubtree>(&org::ImmSubtree::title)));
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
        org::OrgDocumentSelector selector;
        selector.searchAnyKind(
            {OrgSemKind::Subtree},
            true,
            selector.linkField(org::ImmReflFieldId::FromTypeField(
                &org::ImmSubtree::title)));
        selector.searchAnyKind({OrgSemKind::Time}, false);
        auto subtrees = selector.getMatches(doc.getRootAdapter());
        EXPECT_EQ(subtrees.size(), 1);
    }

    {
        org::OrgDocumentSelector selector;
        selector.searchAnyKind(
            {OrgSemKind::Subtree}, true, selector.linkIndirectSubnode());
        selector.searchAnyKind({OrgSemKind::Time}, false);
        auto subtrees = selector.getMatches(doc.getRootAdapter());
        EXPECT_EQ(subtrees.size(), 2);
    }
}
