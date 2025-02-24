#include <hstd/stdlib/Ptrs.hpp>
#include <haxorg/lexbase/AstDiff.hpp>
#include <gtest/gtest.h>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/test/org_parse_aux.hpp>
#include <haxorg/sem/SemAstDiff.hpp>

using namespace hstd::ext::diff;
using namespace hstd;
using namespace org::sem;
using namespace hstd::ext;
using namespace org;


struct TestNode : SharedPtrApi<TestNode> {
    Vec<TestNode::Ptr> subnodes;
    std::string        value;
    int                kind = 0;
    TestNode(int kind, std::string const& value, Vec<TestNode::Ptr> sub)
        : kind(kind), subnodes(sub), value(value) {}
};

TestNode::Ptr n(
    std::string const& val,
    int                kind,
    Vec<TestNode::Ptr> subnodes = {}) {
    return TestNode::shared(kind, val, subnodes);
}

struct TestNodeStore : NodeStore {
    TestNode* root;

    using value_type = std::string;
    using node_type  = TestNode;

    TestNodeStore(TestNode* root) : root{root} {}

    std::string const& getNodeValue(NodeStore::Id const& id) {
        return id.ToPtr<TestNode>()->value;
    }

    virtual int getSubnodeCount(const Id& id) override {
        return id.ToPtr<TestNode>()->subnodes.size();
    }

    virtual Id getSubnodeAt(const Id& node, int index) override {
        return NodeStore::Id::FromPtr(
            node.ToPtr<TestNode>()->subnodes.at(index).get());
    }

    virtual Id getRoot() override { return NodeStore::Id::FromPtr(root); }

    virtual ASTNodeKind getNodeKind(const Id& node) const override {
        return node.ToPtr<TestNode>()->kind;
    }

    Func<ColText(CR<NodeStore::Id>)> getToStr() {
        return [](CR<NodeStore::Id> arg) -> ColText {
            return std::format("{}", arg.ToPtr<TestNode>()->value);
        };
    }
};


struct TestDiffBuilder {
    SPtr<SyntaxTree>    srcSyntax;
    SPtr<SyntaxTree>    dstSyntax;
    SPtr<ASTDiff>       diff;
    TestNode::Ptr       src;
    TestNode::Ptr       dst;
    SPtr<TestNodeStore> srcStore;
    SPtr<TestNodeStore> dstStore;

    static ComparisonOptions getOptions() {
        return ComparisonOptions{
            .getUpdateCost = [](diff::Node const& Src,
                                diff::Node const& Dst) -> double {
                return 1;
            },
            .areValuesEqual = [](diff::Node const& Src,
                                 diff::Node const& Dst) -> bool {
                return Src.getStore<TestNodeStore>()->getNodeValue(
                           Src.ASTNode)
                    == Dst.getStore<TestNodeStore>()->getNodeValue(
                        Dst.ASTNode);
            },
            .isMatchingAllowed = [](diff::Node const& Src,
                                    diff::Node const& Dst) -> bool {
                return Src.getNodeKind() == Dst.getNodeKind();
            },
        };
    }


    TestDiffBuilder(
        TestNode::Ptr            src,
        TestNode::Ptr            dst,
        ComparisonOptions const& Options)
        : src(src), dst(dst) {
        srcSyntax = std::make_shared<SyntaxTree>(Options);
        dstSyntax = std::make_shared<SyntaxTree>(Options);
        srcStore  = std::make_shared<TestNodeStore>(src.get());
        dstStore  = std::make_shared<TestNodeStore>(dst.get());
        srcSyntax->FromNode(srcStore.get());
        dstSyntax->FromNode(dstStore.get());
        diff = std::make_shared<ASTDiff>(*srcSyntax, *dstSyntax, Options);
    }
};

using ChKind = ASTDiff::Change::Kind;

TEST(AstDiff, BaselineApi) {
    {
        TestDiffBuilder b(
            n("same", 0), n("same", 0), TestDiffBuilder::getOptions());
        auto changes = b.diff->getAllChanges(false);
        EXPECT_EQ(changes.size(), 1);
        ASTDiff::Change ch0 = changes.at(0);
        EXPECT_EQ(ch0.getKind(), ChKind::None);
        EXPECT_EQ(ch0.getSrcValue(b.srcStore.get()), std::string("same"));
        EXPECT_EQ(ch0.getDstValue(b.dstStore.get()), std::string("same"));
        EXPECT_EQ(
            b.dstStore->getNodeValue(ch0.getBaseDstChain().at(0)), "same");
        EXPECT_EQ(
            b.srcStore->getNodeValue(ch0.getBaseSrcChain().at(0)), "same");
        auto dstPath = ch0.getDstPath();
        auto srcPath = ch0.getSrcPath();
        EXPECT_TRUE(dstPath.at(0).isRoot());
        EXPECT_TRUE(srcPath.at(0).isRoot());
    }
    {
        TestDiffBuilder b(
            n("first", 0), n("second", 0), TestDiffBuilder::getOptions());
        auto changes = b.diff->getAllChanges(false);
        EXPECT_EQ(changes.size(), 1);
        ASTDiff::Change ch0 = changes.at(0);
        EXPECT_EQ(ch0.getKind(), ChKind::Update);
        EXPECT_EQ(ch0.getSrcValue(b.srcStore.get()), "first");
        EXPECT_EQ(ch0.getDstValue(b.dstStore.get()), "second");
    }
    {
        TestDiffBuilder builder(
            n("0", 0),
            n("0", 0, {n("1", 1)}),
            TestDiffBuilder::getOptions());
        auto changes = builder.diff->getAllChanges(false);
        EXPECT_EQ(changes.size(), 2);
        ASTDiff::Change ch0 = changes.at(0);
        EXPECT_EQ(ch0.getKind(), ChKind::None);
        ASTDiff::Change ch1 = changes.at(1);
        EXPECT_EQ(ch1.getKind(), ChKind::Insert);
        EXPECT_EQ(ch1.getInsert().to.position, 0);
        EXPECT_EQ(ch1.getInsert().to.under, NodeIdx(0));
        auto dstPath = ch1.getDstPath();
        EXPECT_EQ(dstPath.size(), 2);
        EXPECT_TRUE(dstPath.at(0).isRoot());
        EXPECT_EQ(dstPath.at(1).under, NodeIdx(0));
        EXPECT_EQ(dstPath.at(1).position, 0);
        EXPECT_EQ(
            builder.srcStore->getNodeValue(
                builder.dstSyntax->getNode(dstPath.back()).ASTNode),
            "1");
    }
}

TEST(AstDiff, GreedyTopDown) {
    auto opts             = TestDiffBuilder::getOptions();
    opts.firstPass        = ComparisonOptions::FirstPassKind::Greedy;
    opts.StopAfterTopDown = true;
    {
        TestDiffBuilder builder(n("0", 0), n("0", 0), opts);
        auto            changes = builder.diff->getAllChanges(false);
    }
}

TEST(AstDiff, PointerBasedNodes) {
    auto src = n(
        "",
        6,
        {
            n("",
              8,
              {n("**", 18),
               n("CLI", 39),
               n("", 3),
               n("", 55, {n("tools", 69)}),
               n("", 3),
               n("", 3),
               n("", 3),
               n("", 94, {n("", 3), n("", 3)}),
               n("",
                 6,
                 {n("",
                    55,
                    {n("Nested", 69), n(" ", 67), n("content", 69)})})}),
        });

    auto dst = n(
        "",
        6,
        {n("",
           8,
           {n("**", 18),
            n("CLI", 39),
            n("", 3),
            n("", 55, {n("tools", 69)}),
            n("", 3),
            n("", 3),
            n("", 3),
            n("", 94, {n("", 3), n("", 3)}),
            n("",
              6,
              {n("",
                 55,
                 {n("Nested", 69), n(" ", 67), n("content", 69)})})})});

    auto SrcStore = std::make_shared<TestNodeStore>(src.get());
    auto DstStore = std::make_shared<TestNodeStore>(dst.get());

    ComparisonOptions Options = TestDiffBuilder::getOptions();

    SyntaxTree SrcTree{Options};
    SrcTree.FromNode(SrcStore.get());
    SyntaxTree DstTree{Options};
    DstTree.FromNode(DstStore.get());

    ASTDiff Diff{SrcTree, DstTree, Options};


    ColStream os;
    printMapping(
        os,
        Diff,
        SrcTree,
        DstTree,
        SrcStore->getToStr(),
        DstStore->getToStr());

    writeDebugFile(os.getBuffer().toString(false), "txt");
}


struct OrgDiffBuilder : org::algo::OrgNodeDiff {
    org::test::MockFull srcParse;
    org::test::MockFull dstParse;


    sem::SemId<sem::Document> setOrg(std::string const& text, bool isSrc) {
        auto mock = isSrc ? &srcParse : &dstParse;
        mock->run(text);
        sem::OrgConverter converter{};
        return converter.toDocument(
            org::parse::OrgAdapter(&mock->nodes, org::parse::OrgId(0)));
    }

    sem::SemId<sem::Document> setSrc(std::string const& text) {
        return setOrg(text, true);
    }

    sem::SemId<sem::Document> setDst(std::string const& text) {
        return setOrg(text, false);
    }
};

TEST(AstDiff, OrgOneWord) {
    OrgDiffBuilder builder{};
    auto           Src = builder.setSrc("word");
    auto           Dst = builder.setDst("word");
    builder.setDiffTrees(Src, Dst, builder.getOptions());
    auto changes = builder.diff->getAllChanges();
    EXPECT_TRUE(changes.empty());
}


TEST(AstDiff, OrgChangedWord) {
    OrgDiffBuilder builder{};
    auto           Src = builder.setSrc("word1");
    auto           Dst = builder.setDst("word2");
    builder.setDiffTrees(Src, Dst, builder.getOptions());
    auto changes = builder.diff->getAllChanges();
    EXPECT_EQ(changes.size(), 1);
    auto ch0 = changes.at(0);
    EXPECT_EQ(builder.getSrc(ch0.src)->getKind(), OrgSemKind::Word);
    EXPECT_EQ(builder.getDst(ch0.dst)->getKind(), OrgSemKind::Word);

    EXPECT_EQ(builder.getSrcT<sem::Word>(ch0.src)->text, "word1");
    EXPECT_EQ(builder.getDstT<sem::Word>(ch0.dst)->text, "word2");
}

TEST(AstDiff, OrgChangeNestedWord) {
    OrgDiffBuilder builder{};
    auto           Src = builder.setSrc("*word1*");
    auto           Dst = builder.setDst("*word2*");
    builder.setDiffTrees(Src, Dst, builder.getOptions());
    auto changes    = builder.diff->getAllChanges();
    auto change_fmt = builder.formatDiff();
    writeDebugFile(
        change_fmt.toString(false), "txt", true, "OrgChangeNestedWord");

    EXPECT_EQ(changes.size(), 1);
    auto ch0 = changes.at(0);
    EXPECT_EQ(builder.getSrc(ch0.src)->getKind(), OrgSemKind::Word);
    EXPECT_EQ(builder.getDst(ch0.dst)->getKind(), OrgSemKind::Word);

    EXPECT_EQ(builder.getSrcT<sem::Word>(ch0.src)->text, "word1");
    EXPECT_EQ(builder.getDstT<sem::Word>(ch0.dst)->text, "word2");
}

TEST(AstDiff, OrgChangeDeeplyNestedWord) {
    OrgDiffBuilder builder{};

    auto Src = builder.setSrc(R"(
* Subtree1
** Subtree2
*** Subtree3

#+begin_center
word1
#+end_center
)");

    auto Dst = builder.setDst(R"(
* Subtree1
** Subtree2
*** Subtree3

#+begin_center
word2
#+end_center
)");

    builder.setDiffTrees(Src, Dst, builder.getOptions());
    auto changes    = builder.diff->getAllChanges();
    auto change_fmt = builder.formatDiff();
    writeDebugFile(
        change_fmt.toString(false),
        "txt",
        true,
        "OrgChangeDeeplyNestedWord");

    EXPECT_EQ(changes.size(), 1);
    auto ch0 = changes.at(0);
    EXPECT_EQ(builder.getSrc(ch0.src)->getKind(), OrgSemKind::Word);
    EXPECT_EQ(builder.getDst(ch0.dst)->getKind(), OrgSemKind::Word);

    EXPECT_EQ(builder.getSrcT<sem::Word>(ch0.src)->text, "word1");
    EXPECT_EQ(builder.getDstT<sem::Word>(ch0.dst)->text, "word2");
}
