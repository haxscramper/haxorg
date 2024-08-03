#include <hstd/stdlib/Ptrs.hpp>
#include <lexbase/AstDiff.hpp>
#include <gtest/gtest.h>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <sem/SemOrg.hpp>
#include <test/org_parse_aux.hpp>


using namespace diff;


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

    writeDebugFile(os.getBuffer().toString(false), "txt", "", true);
}


struct OrgNodeStore : NodeStore {
    sem::SemId<sem::Org> root;

    using value_type = Opt<Str>;
    using node_type  = TestNode;

    OrgNodeStore(sem::SemId<sem::Org> root) : root{root} {}

    Opt<Str> getNodeValue(NodeStore::Id const& id) {
        auto node = get(id);
        if (auto leaf = node->dyn_cast<sem::Leaf>()) {
            return leaf->text;
        } else {
            return std::nullopt;
        }
    }

    sem::Org const* get(Id const& id) const {
        return id.ToPtr<sem::Org>();
    }

    virtual int getSubnodeCount(const Id& id) override {
        return get(id)->subnodes.size();
    }

    virtual Id getSubnodeAt(const Id& node, int index) override {
        return NodeStore::Id::FromPtr(get(node)->subnodes.at(index).get());
    }

    virtual Id getRoot() override {
        return NodeStore::Id::FromPtr(root.get());
    }

    virtual ASTNodeKind getNodeKind(const Id& node) const override {
        return static_cast<int>(get(node)->getKind());
    }
};


struct OrgDiffBuilder {
    SPtr<SyntaxTree>          srcSyntax;
    SPtr<SyntaxTree>          dstSyntax;
    SPtr<ASTDiff>             diff;
    sem::SemId<sem::Document> src;
    sem::SemId<sem::Document> dst;
    SPtr<OrgNodeStore>        srcStore;
    SPtr<OrgNodeStore>        dstStore;
    MockFull                  srcParse;
    MockFull                  dstParse;

    sem::SemId<sem::Document> setOrg(std::string const& text, bool isSrc) {
        auto mock = isSrc ? &srcParse : &dstParse;
        mock->run(text);
        sem::OrgConverter converter{};
        return converter.toDocument(OrgAdapter(&mock->nodes, OrgId(0)));
    }

    sem::SemId<sem::Document> setSrc(std::string const& text) {
        return setOrg(text, true);
    }

    sem::SemId<sem::Document> setDst(std::string const& text) {
        return setOrg(text, false);
    }

    ComparisonOptions getOptions() {
        return ComparisonOptions{
            .areValuesEqual = [](diff::Node const& Src,
                                 diff::Node const& Dst) -> bool {
                return Src.getStore<OrgNodeStore>()->getNodeValue(
                           Src.ASTNode)
                    == Dst.getStore<OrgNodeStore>()->getNodeValue(
                        Dst.ASTNode);
            },
            .isMatchingAllowed = [](diff::Node const& Src,
                                    diff::Node const& Dst) -> bool {
                auto SrcKind = static_cast<OrgSemKind>(
                    Src.getNodeKind().value);
                auto DstKind = static_cast<OrgSemKind>(
                    Dst.getNodeKind().value);
                SemSet LeafKinds{
                    OrgSemKind::Word,
                    OrgSemKind::BigIdent,
                    OrgSemKind::Punctuation,
                    OrgSemKind::Escaped,
                    OrgSemKind::Newline,
                    OrgSemKind::Empty,
                };
                if (SrcKind == DstKind) {
                    return true;
                } else {
                    return LeafKinds.contains(SrcKind)
                        && LeafKinds.contains(DstKind);
                }
            },
        };
    }

    void setDiffTrees(
        sem::SemId<sem::Document> const& src,
        sem::SemId<sem::Document> const& dst,
        ComparisonOptions const&         Options) {
        this->src = src;
        this->dst = dst;
        srcSyntax = std::make_shared<SyntaxTree>(Options);
        dstSyntax = std::make_shared<SyntaxTree>(Options);
        srcStore  = std::make_shared<OrgNodeStore>(src.asOrg());
        dstStore  = std::make_shared<OrgNodeStore>(dst.asOrg());
        srcSyntax->FromNode(srcStore.get());
        dstSyntax->FromNode(dstStore.get());
        diff = std::make_shared<ASTDiff>(*srcSyntax, *dstSyntax, Options);
    }
};

TEST(AstDiff, OrgWordDocument) {
    OrgDiffBuilder builder{};
    auto           Src = builder.setSrc("word");
    auto           Dst = builder.setDst("word");
    builder.setDiffTrees(Src, Dst, builder.getOptions());
    auto changes = builder.diff->getAllChanges(false);
}
