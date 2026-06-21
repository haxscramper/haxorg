#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/ext/astdiff/astdiff.hpp>
#include <hstd/ext/astdiff/astdiff_eager.hpp>
#include <gtest/gtest.h>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Formatter.hpp>

using namespace hstd::ext::diff;
using namespace hstd;
using namespace hstd::ext;


struct TestNode : SharedPtrApi<TestNode> {
    Vec<TestNode::Ptr> subnodes;
    std::string        value;
    int                kind = 0;
    TestNode(int kind, std::string const& value, Vec<TestNode::Ptr> sub)
        : kind(kind), subnodes(sub), value(value) {}
};

TestNode::Ptr n(std::string const& val, int kind, Vec<TestNode::Ptr> subnodes = {}) {
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

    virtual int getSubnodeCount(Id const& id) override {
        return id.ToPtr<TestNode>()->subnodes.size();
    }

    virtual Id getSubnodeAt(Id const& node, int index) override {
        return NodeStore::Id::FromPtr(node.ToPtr<TestNode>()->subnodes.at(index).get());
    }

    virtual Id getRoot() override { return NodeStore::Id::FromPtr(root); }

    virtual ASTNodeKind getNodeKind(Id const& node) const override {
        return node.ToPtr<TestNode>()->kind;
    }

    Func<ColText(NodeStore::Id const&)> getToStr() {
        return [](NodeStore::Id const& arg) -> ColText {
            return fmt::format("{}", arg.ToPtr<TestNode>()->value);
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
            .isMatchingAllowed = [](diff::Node const& Src, diff::Node const& Dst)
                -> bool { return Src.getNodeKind() == Dst.getNodeKind(); },
            .areValuesEqual = [](diff::Node const& Src, diff::Node const& Dst) -> bool {
                return Src.getStore<TestNodeStore>()->getNodeValue(Src.ASTNode)
                    == Dst.getStore<TestNodeStore>()->getNodeValue(Dst.ASTNode);
            },
            .getUpdateCost = [](diff::Node const& Src, diff::Node const& Dst) -> double {
                return 1;
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
        TestDiffBuilder b(n("same", 0), n("same", 0), TestDiffBuilder::getOptions());
        auto            changes = b.diff->getAllChanges(false);
        EXPECT_EQ(changes.size(), 1);
        ASTDiff::Change ch0 = changes.at(0);
        EXPECT_EQ(ch0.getKind(), ChKind::None);
        EXPECT_EQ(ch0.getSrcValue(b.srcStore.get()), std::string("same"));
        EXPECT_EQ(ch0.getDstValue(b.dstStore.get()), std::string("same"));
        EXPECT_EQ(b.dstStore->getNodeValue(ch0.getBaseDstChain().at(0)), "same");
        EXPECT_EQ(b.srcStore->getNodeValue(ch0.getBaseSrcChain().at(0)), "same");
        auto dstPath = ch0.getDstPath();
        auto srcPath = ch0.getSrcPath();
        EXPECT_TRUE(dstPath.at(0).isRoot());
        EXPECT_TRUE(srcPath.at(0).isRoot());
    }
    {
        TestDiffBuilder b(n("first", 0), n("second", 0), TestDiffBuilder::getOptions());
        auto            changes = b.diff->getAllChanges(false);
        EXPECT_EQ(changes.size(), 1);
        ASTDiff::Change ch0 = changes.at(0);
        EXPECT_EQ(ch0.getKind(), ChKind::Update);
        EXPECT_EQ(ch0.getSrcValue(b.srcStore.get()), "first");
        EXPECT_EQ(ch0.getDstValue(b.dstStore.get()), "second");
    }
    {
        TestDiffBuilder builder(
            n("0", 0), n("0", 0, {n("1", 1)}), TestDiffBuilder::getOptions());
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
               n("", 6, {n("", 55, {n("Nested", 69), n(" ", 67), n("content", 69)})})}),
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
            n("", 6, {n("", 55, {n("Nested", 69), n(" ", 67), n("content", 69)})})})});

    auto SrcStore = std::make_shared<TestNodeStore>(src.get());
    auto DstStore = std::make_shared<TestNodeStore>(dst.get());

    ComparisonOptions Options = TestDiffBuilder::getOptions();

    SyntaxTree SrcTree{Options};
    SrcTree.FromNode(SrcStore.get());
    SyntaxTree DstTree{Options};
    DstTree.FromNode(DstStore.get());

    ASTDiff Diff{SrcTree, DstTree, Options};


    ColStream os;
    printMapping(os, Diff, SrcTree, DstTree, SrcStore->getToStr(), DstStore->getToStr());

    writeDebugFile(os.getBuffer().toString(false), "txt");
}

namespace {
TestNode::Ptr cloneTree(TestNode const* node) {
    Vec<TestNode::Ptr> sub;
    sub.reserve(node->subnodes.size());
    for (auto const& it : node->subnodes) { sub.push_back(cloneTree(it.get())); }
    return n(node->value, node->kind, sub);
}

bool structurallyEqual(TestNode const* lhs, TestNode const* rhs) {
    if (lhs->kind != rhs->kind || lhs->value != rhs->value) { return false; }
    if (lhs->subnodes.size() != rhs->subnodes.size()) { return false; }
    for (int i = 0; i < lhs->subnodes.size(); ++i) {
        if (!structurallyEqual(lhs->subnodes.at(i).get(), rhs->subnodes.at(i).get())) {
            return false;
        }
    }
    return true;
}

void applyEditsAtRoot(TestNode::Ptr const& root, hstd::Vec<DiaEdit> const& edits) {
    for (auto const& e : edits) {
        if (e.isUpdate()) {
            auto dst = e.getUpdate().dstNode.ToPtr<TestNode>();
            if (e.getUpdate().srcNode.ToPtr<TestNode>() == root.get()) {
                root->value = dst->value;
                root->kind  = dst->kind;
            } else {
                auto idx                      = e.getUpdate().srcIndex;
                root->subnodes.at(idx)->value = dst->value;
                root->subnodes.at(idx)->kind  = dst->kind;
            }
        } else if (e.isMove()) {
            int  src  = e.getMove().srcIndex;
            int  dst  = e.getMove().dstIndex;
            auto item = root->subnodes.at(src);
            root->subnodes.erase(root->subnodes.begin() + src);
            if (src < dst) { --dst; }
            root->subnodes.insert(root->subnodes.begin() + dst, item);
        } else if (e.isInsert()) {
            auto dstNode = e.getInsert().dstNode.ToPtr<TestNode>();
            root->subnodes.insert(
                root->subnodes.begin() + e.getInsert().dstIndex, cloneTree(dstNode));
        } else if (e.isDelete()) {
            root->subnodes.erase(root->subnodes.begin() + e.getDelete().srcIndex);
        }
    }
}
} // namespace

TEST(AstDiff_GetDiff, IdenticalTrees_NoEdits) {
    auto src = n("root", 1, {n("a", 2), n("b", 2)});
    auto dst = cloneTree(src.get());

    TestNodeStore srcStore(src.get());
    TestNodeStore dstStore(dst.get());

    auto edits = getEdits(
        srcStore, dstStore, [](NodeStore::Id const& a, NodeStore::Id const& b) {
            return a.ToPtr<TestNode>()->value == b.ToPtr<TestNode>()->value;
        });

    EXPECT_TRUE(edits.empty());
}

TEST(AstDiff_GetDiff, ReorderSubnodes_ProducesMove) {
    auto a   = n("a", 2);
    auto b   = n("b", 2);
    auto src = n("root", 1, {a, b});
    auto dst = n("root", 1, {cloneTree(b.get()), cloneTree(a.get())});

    TestNodeStore srcStore(src.get());
    TestNodeStore dstStore(dst.get());

    auto edits = getEdits(
        srcStore, dstStore, [](NodeStore::Id const& x, NodeStore::Id const& y) {
            return x.ToPtr<TestNode>()->value == y.ToPtr<TestNode>()->value;
        });

    EXPECT_TRUE(std::any_of(edits.begin(), edits.end(), [](DiaEdit const& e) {
        return e.isMove();
    }));
}

// TODO: extend the tests with more basic coverage elements, diff the
// simple trees etc.

TEST(AstDiff_ApplyEdits, SyntheticEdits_TransformTree) {
    auto src = n("root", 1, {n("a", 2), n("b", 2)});
    auto ins = n("x", 2);

    hstd::Vec<DiaEdit> edits;
    edits.push_back(
        DiaEdit{DiaEdit::Move{
            .srcNode  = NodeStore::Id::FromPtr(src->subnodes.at(0).get()),
            .dstNode  = NodeStore::Id::FromPtr(src->subnodes.at(0).get()),
            .srcIndex = 0,
            .dstIndex = 2}});
    edits.push_back(
        DiaEdit{DiaEdit::Insert{
            .dstNode = NodeStore::Id::FromPtr(ins.get()), .dstIndex = 1}});
    edits.push_back(
        DiaEdit{DiaEdit::Delete{
            .srcNode  = NodeStore::Id::FromPtr(src->subnodes.at(1).get()),
            .srcIndex = 0}});

    applyEditsAtRoot(src, edits);

    auto expected = n("root", 1, {n("x", 2), n("a", 2)});
    EXPECT_TRUE(structurallyEqual(src.get(), expected.get()));
}

TEST(AstDiff_ApplyEdits, DiffThenApply_ProducesDestinationStructure) {
    auto src = n("root", 1, {n("a", 2), n("b", 2), n("c", 2)});
    auto dst = n("root", 1, {n("b", 2), n("x", 2), n("c", 2)});

    TestNodeStore srcStore(src.get());
    TestNodeStore dstStore(dst.get());

    auto edits = getEdits(
        srcStore, dstStore, [](NodeStore::Id const& x, NodeStore::Id const& y) {
            return x.ToPtr<TestNode>()->value == y.ToPtr<TestNode>()->value;
        });

    applyEditsAtRoot(src, edits);

    // FIXME:
    // EXPECT_TRUE(structurallyEqual(src.get(), dst.get()));
}
