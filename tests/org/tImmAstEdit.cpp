#include "tOrgTestCommon.hpp"
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>


struct ImmOrgApiEdit : ImmOrgApiTestBase {};

Vec<int> getDfsSubtreeLevels(imm::ImmAdapter n) {
    Vec<int>                    result;
    Func<void(imm::ImmAdapter)> aux;
    aux = [&](imm::ImmAdapter n) {
        if (auto tree = n.asOpt<imm::ImmSubtree>()) {
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
    imm::ImmAstVersion v1 = getInitialVersion(getSubtreeDash());

    {
        auto root = v1.getRootAdapter();
        writeFile(
            "/tmp/SubtreePromotion_repr.txt",
            root.treeRepr().toString(false));
    }

    Vec<int> path{0, 1, 0};

    imm::ImmAstVersion v2 = v1.getEditVersion(
        [&](imm::ImmAstContext::Ptr ast,
            imm::ImmAstEditContext& ctx) -> imm::ImmAstReplaceGroup {
            auto root  = v1.getRootAdapter();
            auto s3010 = root.at(path);
            EXPECT_EQ(s3010->getKind(), OrgSemKind::Subtree);
            EXPECT_EQ(s3010->as<imm::ImmSubtree>()->level, 3);
            return demoteSubtree(
                s3010, imm::SubtreeMove::ForceLevels, ctx);
        });

    imm::ImmAdapter::TreeReprConf conf{.withAuxFields = true};

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
        EXPECT_EQ(s3010->as<imm::ImmSubtree>()->level, 3);
        auto levels = getDfsSubtreeLevels(r);
        EXPECT_EQ(levels, (Vec<int>{1, 2, 3, 3, 2, 3}));
    }

    {
        auto r     = v2.getRootAdapter();
        auto s3010 = r.at(path);
        EXPECT_EQ(s3010->getKind(), OrgSemKind::Subtree);
        EXPECT_EQ(s3010->as<imm::ImmSubtree>()->level, 4);
        auto levels = getDfsSubtreeLevels(r);
        EXPECT_EQ(levels, (Vec<int>{1, 2, 3, 3, 2, 4}));
    }
}


TEST_F(ImmOrgApiEdit, RecursiveSubtreeDemote_OneNested) {
    setTraceFile(getDebugFile("trace.txt"));
    imm::ImmAstVersion v1 = getInitialVersion(getSubtreeDash());
    writeTreeRepr(v1.getRootAdapter(), getDebugFile("repr_v1.txt"));

    imm::ImmAstVersion v2 = v1.getEditVersion(
        [&](imm::ImmAstContext::Ptr ast,
            imm::ImmAstEditContext& ctx) -> imm::ImmAstReplaceGroup {
            auto root = v1.getRootAdapter();
            auto s201 = root.at(Vec{0, 1});
            EXPECT_EQ(s201->getKind(), OrgSemKind::Subtree);
            EXPECT_EQ(s201->as<imm::ImmSubtree>()->level, 2);
            return demoteSubtree(s201, imm::SubtreeMove::ForceLevels, ctx);
        });

    writeGvHistory({v1, v2}, "v1_v2");

    auto r = v2.getRootAdapter();
    writeTreeRepr(r, getDebugFile("repr_v2.txt"));
    auto s201 = r.at(Vec{0, 0, 2});
    EXPECT_EQ(s201->getKind(), OrgSemKind::Subtree);
    EXPECT_EQ(s201->as<imm::ImmSubtree>()->level, 3);
    auto s3010 = r.at({0, 0, 2, 0});
    EXPECT_EQ(s3010->getKind(), OrgSemKind::Subtree);
    EXPECT_EQ(s3010->as<imm::ImmSubtree>()->level, 4);
    auto levels = getDfsSubtreeLevels(r);
    EXPECT_EQ(levels, (Vec<int>{1, 2, 3, 3, 3, 4}));
}

TEST_F(ImmOrgApiEdit, RecursiveSubtreeDemote_All) {
    setTraceFile(getDebugFile("trace.txt"));
    imm::ImmAstVersion v1 = getInitialVersion(getSubtreeDash());

    imm::ImmAstVersion v2 = v1.getEditVersion(
        [&](imm::ImmAstContext::Ptr ast,
            imm::ImmAstEditContext& ctx) -> imm::ImmAstReplaceGroup {
            auto root = v1.getRootAdapter();
            auto s1   = root.at(0);
            return demoteSubtree(s1, imm::SubtreeMove::ForceLevels, ctx);
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
    imm::ImmAstVersion v1 = getInitialVersion(getSubtreeDash());

    auto demotePath = [&](imm::ImmAstVersion v,
                          CVec<int>          path) -> imm::ImmAstVersion {
        return v.getEditVersion(
            [&](imm::ImmAstContext::Ptr ast,
                imm::ImmAstEditContext& ctx) -> imm::ImmAstReplaceGroup {
                auto root = v.getRootAdapter();
                auto s1   = root.at(path);
                return demoteSubtree(
                    s1, imm::SubtreeMove::ForceLevels, ctx);
            });
    };

    imm::ImmAstVersion v2 = demotePath(v1, {0, 0, 1});

    {
        auto r = v2.getRootAdapter();

        writeTreeRepr(v1.getRootAdapter(), getDebugFile("repr_v1.txt"));
        writeTreeRepr(v2.getRootAdapter(), getDebugFile("repr_v2.txt"));
        writeGvHistory({v1, v2}, "v1_v2");

        EXPECT_EQ(getDfsSubtreeLevels(r), (Vec<int>{1, 2, 3, 4, 2, 3}));

        Vec<int> p0000 = {0, 0, 0, 0};
        Vec<int> p000  = {0, 0, 0};
        Vec<int> p00   = {0, 0};
        Vec<int> p0    = {0};


        EXPECT_TRUE(r.at(p0000).is(OrgSemKind::Subtree));
        EXPECT_EQ(r.at(p0000).as<imm::ImmSubtree>()->level, 4);
        EXPECT_EQ(r.at(p0000).getParent().value().id, r.at(p000).id);
        EXPECT_EQ(r.at(p000).at(0).id, r.at(p0000).id);

        EXPECT_EQ(r.at(p000).as<imm::ImmSubtree>()->level, 3);
        EXPECT_EQ(r.at(p000).getParent().value().id, r.at(p00).id);
        EXPECT_EQ(r.at(p00).at(0).id, r.at(p000).id);

        EXPECT_EQ(r.at(p00).as<imm::ImmSubtree>()->level, 2);
        EXPECT_EQ(r.at(p0).at(0).id, r.at(p00).id);
    }

    imm::ImmAstVersion v3 = demotePath(v2, {0, 1});
    writeTreeRepr(v3.getRootAdapter(), getDebugFile("repr_v3.txt"));
    imm::ImmAstVersion v4 = demotePath(v3, {0, 0, 1});
    writeTreeRepr(v4.getRootAdapter(), getDebugFile("repr_v4.txt"));
    imm::ImmAstVersion v5 = demotePath(v4, {0, 0, 0, 1});
    writeTreeRepr(v5.getRootAdapter(), getDebugFile("repr_v5.txt"));
    writeGvHistory(
        {v1, v2, v3, v4, v5},
        "v_final",
        imm::ImmAstGraphvizConf{
            .withAuxNodes      = true,
            .withEditHistory   = false,
            .withEpochClusters = false,
        });

    {
        auto r = v5.getRootAdapter();
        EXPECT_TRUE(
            r.at({0, 0, 0, 0, 0, 0}).isSubnodeOf(r.at({0, 0, 0, 0, 0})));
        EXPECT_EQ(
            r.at({0, 0, 0, 0, 0, 0}).as<imm::ImmSubtree>()->level, 6);
        EXPECT_EQ(
            r.at({0, 0, 0, 0, 0, 0}).as<imm::ImmSubtree>()->level, 6);
        EXPECT_EQ(r.at({0, 0, 0, 0, 0}).as<imm::ImmSubtree>()->level, 5);
        EXPECT_EQ(r.at({0, 0, 0, 0}).as<imm::ImmSubtree>()->level, 4);
        EXPECT_EQ(r.at({0, 0, 0}).as<imm::ImmSubtree>()->level, 3);
    }
}

TEST_F(ImmOrgApiEdit, PhysicalDemote) {
    setTraceFile(getDebugFile("trace.txt"));
    imm::ImmAstVersion v1 = getInitialVersion(getSubtreeDash());
    writeTreeRepr(v1.getRootAdapter(), getDebugFile("repr_v1.txt"));

    imm::ImmAstVersion v2 = v1.getEditVersion(
        [&](imm::ImmAstContext::Ptr ast,
            imm::ImmAstEditContext& ctx) -> imm::ImmAstReplaceGroup {
            auto root = v1.getRootAdapter();
            auto s1   = root.at(Vec{0, 0});
            return demoteSubtree(s1, imm::SubtreeMove::Physical, ctx);
        });

    writeGvHistory({v1, v2}, "v1_v2");
    writeTreeRepr(v2.getRootAdapter(), getDebugFile("repr_v2.txt"));

    EXPECT_EQ(
        getDfsSubtreeLevels(v1.getRootAdapter()),
        (Vec<int>{1, 2, 3, 3, 2, 3}));

    EXPECT_EQ(
        getDfsSubtreeLevels(v2.getRootAdapter()),
        (Vec<int>{1, 3, 3, 3, 2, 3}));
}

TEST_F(ImmOrgApiEdit, ResetTitle) {
    setTraceFile(getDebugFile("trace.txt"));
    imm::ImmAstVersion v1 = getInitialVersion("* subtree");
    writeTreeRepr(v1.getRootAdapter(), getDebugFile("repr_v1.txt"));

    imm::ImmAstVersion v2 = v1.getEditVersion(
        [&](imm::ImmAstContext::Ptr ast,
            imm::ImmAstEditContext& ctx) -> imm::ImmAstReplaceGroup {
            return ctx.store().updateNode<imm::ImmSubtree>(
                v1.getRootAdapter().at(0), ctx, [&](imm::ImmSubtree tree) {
                    tree.title = ctx->add(
                                        org::asOneNode(org::parseString(
                                            "replaced", "<replaced>")),
                                        ctx)
                                     .as<imm::ImmParagraph>();
                    return tree;
                });
        });

    writeGvHistory({v1, v2}, "v1_v2");
    writeTreeRepr(v2.getRootAdapter(), getDebugFile("repr_v2.txt"));

    {
        auto tree = v1.getRootAdapter().at(0).as<imm::ImmSubtree>();
        EXPECT_EQ(
            tree.pass(tree->title).at(0).as<imm::ImmWord>()->text,
            "subtree");
    }

    {
        auto tree = v2.getRootAdapter().at(0).as<imm::ImmSubtree>();
        EXPECT_EQ(
            tree.pass(tree->title).at(0).as<imm::ImmWord>()->text,
            "replaced");
    }
}

TEST_F(ImmOrgApiEdit, MoveSubnodes) {
    setTraceFile(getDebugFile("trace.txt"));
    imm::ImmAstVersion v1 = getInitialVersion("zero one two three");

    auto move =
        [&](int position, int offset, bool bounded) -> imm::ImmAstVersion {
        return v1.getEditVersion(
            [&](imm::ImmAstContext::Ptr ast,
                imm::ImmAstEditContext& ctx) -> imm::ImmAstReplaceGroup {
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

    Func<Vec<Str>(imm::ImmAdapter const&)> flat;
    flat = [&](imm::ImmAdapter const& it) -> Vec<Str> {
        Vec<Str> result;
        if (auto i = it.asOpt<imm::ImmWord>(); i) {
            result.push_back(i.value()->text);
        } else if (auto i = it.asOpt<imm::ImmSpace>(); i) {
            result.push_back(i.value()->text);
        } else {
            for (auto const& sub : it.sub()) { result.append(flat(sub)); }
        }

        return result;
    };

    writeGvHistory({v1}, "graph_v1");

    imm::ImmAstVersion v2 = move(0, 2, true);
    imm::ImmAstVersion v3 = move(0, 4, true);
    imm::ImmAstVersion v4 = move(2, -2, true);

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
