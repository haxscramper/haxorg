#include <hstd/stdlib/Ptrs.hpp>
#include <lexbase/AstDiff.hpp>
#include <gtest/gtest.h>

using namespace diff;


struct TestNode : SharedPtrApi<TestNode> {
    Vec<TestNode::Ptr> subnodes;
    std::string        value;
    int                kind = 0;
    TestNode(int kind, std::string const& value, Vec<TestNode::Ptr> sub)
        : kind(kind), subnodes(sub), value(value) {}
};

TestNode::Ptr n(
    int                kind,
    std::string const& val,
    Vec<TestNode::Ptr> subnodes = {}) {
    return TestNode::shared(kind, val, subnodes);
}

using TestSyntaxTree = SyntaxTree<TestNode*, std::string>;
using TestWalker     = TestSyntaxTree::WalkParameters<TestNode::Ptr>;
using TestDiff       = ASTDiff<TestNode*, std::string>;
using TestOptions    = ComparisonOptions<TestNode*, std::string>;

TestWalker getTestWalker() {
    return TestWalker{
        .getSubnodeAt = [](CR<TestNode::Ptr> node, int pos)
            -> CR<TestNode::Ptr> { return node->subnodes.at(pos); },
        .getSubnodeNumber = [](CR<TestNode::Ptr> node) -> int {
            return node->subnodes.size();
        },
        .getSubnodeId = [](CR<TestNode::Ptr> node) -> TestNode* {
            return node.get();
        },
    };
}

TestOptions getTestOptions() {
    return TestOptions{
        .getNodeValueImpl = [](TestNode* id) -> std::string const& {
            return id->value;
        },
        .getNodeKindImpl = [](TestNode* id) { return id->kind; },
        .isMatchingAllowedImpl =
            [](TestNode* id1, TestNode* id2) {
                return id1->kind == id2->kind;
            }};
}

struct DiffBuilder {
    SPtr<TestSyntaxTree> srcSyntax;
    SPtr<TestSyntaxTree> dstSyntax;
    SPtr<TestDiff>       diff;
    TestNode::Ptr        src;
    TestNode::Ptr        dst;

    DiffBuilder(
        TestNode::Ptr      src,
        TestNode::Ptr      dst,
        TestOptions const& Options)
        : src(src), dst(dst) {
        srcSyntax         = std::make_shared<TestSyntaxTree>(Options);
        dstSyntax         = std::make_shared<TestSyntaxTree>(Options);
        TestWalker walker = getTestWalker();
        srcSyntax->FromNode(src, walker);
        dstSyntax->FromNode(dst, walker);
        diff = std::make_shared<TestDiff>(*srcSyntax, *dstSyntax, Options);
    }
};

using ChKind = TestDiff::Change::Kind;

TEST(AstDiff, BaselineApi) {
    {
        DiffBuilder builder(n(0, "same"), n(0, "same"), getTestOptions());
        auto        changes = builder.diff->getAllChanges(false);
        EXPECT_EQ(changes.size(), 1);
        TestDiff::Change ch0 = changes.at(0);
        EXPECT_EQ(ch0.getKind(), ChKind::None);
        EXPECT_EQ(ch0.getSrcValue(), std::string("same"));
        EXPECT_EQ(ch0.getDstValue(), std::string("same"));
        EXPECT_EQ(ch0.getBaseDstChain().at(0)->value, "same");
        EXPECT_EQ(ch0.getBaseSrcChain().at(0)->value, "same");
        auto dstPath = ch0.getDstPath();
        auto srcPath = ch0.getSrcPath();
        EXPECT_TRUE(dstPath.at(0).isRoot());
        EXPECT_TRUE(srcPath.at(0).isRoot());
    }
    {
        DiffBuilder builder(
            n(0, "first"), n(0, "second"), getTestOptions());
        auto changes = builder.diff->getAllChanges(false);
        EXPECT_EQ(changes.size(), 1);
        TestDiff::Change ch0 = changes.at(0);
        EXPECT_EQ(ch0.getKind(), ChKind::Update);
        EXPECT_EQ(ch0.getSrcValue(), "first");
        EXPECT_EQ(ch0.getDstValue(), "second");
    }
    {
        DiffBuilder builder(
            n(0, "0"), n(0, "0", {n(1, "1")}), getTestOptions());
        auto changes = builder.diff->getAllChanges(false);
        EXPECT_EQ(changes.size(), 2);
        TestDiff::Change ch0 = changes.at(0);
        EXPECT_EQ(ch0.getKind(), ChKind::None);
        TestDiff::Change ch1 = changes.at(1);
        EXPECT_EQ(ch1.getKind(), ChKind::Insert);
        EXPECT_EQ(ch1.getInsert().to.position, 0);
        EXPECT_EQ(ch1.getInsert().to.under, NodeId(0));
        auto dstPath = ch1.getDstPath();
        EXPECT_EQ(dstPath.size(), 2);
        EXPECT_TRUE(dstPath.at(0).isRoot());
        EXPECT_EQ(dstPath.at(1).under, NodeId(0));
        EXPECT_EQ(dstPath.at(1).position, 0);
        EXPECT_EQ(
            builder.dstSyntax->getNodeValue(
                builder.dstSyntax->getNode(dstPath.back())),
            "1");
    }
}

TEST(AstDiff, GreedyTopDown) {
    auto opts             = getTestOptions();
    opts.firstPass        = TestOptions::FirstPassKind::Greedy;
    opts.StopAfterTopDown = true;
    {
        DiffBuilder builder(n(0, "0"), n(0, "0"), opts);
        auto        changes = builder.diff->getAllChanges(false);
    }
}

TEST(AstDiff, PointerBasedNodes) {
    struct RealNode {
        std::string   value;
        int           kind;
        Vec<RealNode> sub;

        using IdT  = RealNode*;
        using ValT = std::string;

        TreeMirror<IdT, ValT> toMirror() {
            Vec<TreeMirror<IdT, ValT>> subMirror;
            for (auto& it : sub) {
                subMirror.push_back(it.toMirror());
            }
            return TreeMirror<IdT, ValT>{this, subMirror};
        }
    };

    using IdT  = RealNode::IdT;
    using ValT = RealNode::ValT;

    Func<Str(CR<ValT>)> toStr = [](CR<ValT> arg) -> Str {
        return std::format("{}", arg);
    };

    auto src = RealNode{
        "",
        6,
        {RealNode{
             "",
             8,
             {RealNode{"**", 18},
              RealNode{"CLI", 39},
              RealNode{"", 3},
              RealNode{"", 55, {RealNode{"tools", 69}}},
              RealNode{"", 3},
              RealNode{"", 3},
              RealNode{"", 3},
              RealNode{"", 94, {RealNode{"", 3}, RealNode{"", 3}}},
              RealNode{"", 6, {}}}},
         RealNode{
             "",
             55,
             {RealNode{"Nested", 69},
              RealNode{" ", 67},
              RealNode{"content", 69}}}}};

    auto dst = RealNode{
        "",
        6,
        {RealNode{
            "",
            8,
            {RealNode{"**", 18},
             RealNode{"CLI", 39},
             RealNode{"", 3},
             RealNode{"", 55, {RealNode{"tools", 69}}},
             RealNode{"", 3},
             RealNode{"", 3},
             RealNode{"", 3},
             RealNode{"", 94, {RealNode{"", 3}, RealNode{"", 3}}},
             RealNode{
                 "",
                 6,
                 {RealNode{
                     "",
                     55,
                     {RealNode{"Nested", 69},
                      RealNode{" ", 67},
                      RealNode{"content", 69}}}}}}}}};

    auto Src = src.toMirror();
    auto Dst = dst.toMirror();

    ComparisonOptions<IdT, ValT> Options{
        .getNodeValueImpl = [](IdT id) { return id->value; },
        .getNodeKindImpl  = [](IdT id) { return id->kind; },
        .isMatchingAllowedImpl =
            [](IdT id1, IdT id2) { return id1->kind == id2->kind; }};

    SyntaxTree<IdT, ValT>::WalkParameters<TreeMirror<IdT, ValT>> walk{
        .getSubnodeAt     = diff::getSubnodeAtTreeMirror<IdT, ValT>,
        .getSubnodeNumber = diff::getSubnodeNumberTreeMirror<IdT, ValT>,
        .getSubnodeId     = diff::getSubnodeIdTreeMirror<IdT, ValT>,
    };

    SyntaxTree<IdT, ValT> SrcTree{Options};
    SrcTree.FromNode<TreeMirror<IdT, ValT>>(Src, walk);
    SyntaxTree<IdT, ValT> DstTree{Options};
    DstTree.FromNode(Dst, walk);

    ASTDiff<IdT, ValT> Diff{SrcTree, DstTree, Options};


    std::stringstream os;
    for (diff::NodeId Dst : DstTree) {
        diff::NodeId Src = Diff.getMapped(DstTree, Dst);
        if (Src.isValid()) {
            os << "Match [\033[33m";
            printNode(os, SrcTree, Src, toStr);
            os << "\033[0m] to [\033[33m";
            printNode(os, DstTree, Dst, toStr);
            os << "\033[0m] ";
        } else {
            os << "Dst to [\033[32m";
            printNode(os, DstTree, Dst, toStr);
            os << "\033[0m] ";
        }

        printDstChange(os, Diff, SrcTree, DstTree, Dst, toStr);
        os << "\n";
    }
}

TEST(AstDiff, PointerBasedNodesWithVariants) {
    struct RealNode {
        std::variant<int, double, std::string> value;
        Vec<RealNode>                          sub;
    };

    auto src = RealNode{
        "toplevel", {RealNode{1}, RealNode{1.2}, RealNode{"subnode"}}};

    auto dst = RealNode{
        "toplevel", {RealNode{22}, RealNode{1.2}, RealNode{"subnode'"}}};

    using IdT  = RealNode*;
    using ValT = decltype(src.value);


    Func<Str(CR<ValT>)> toStr = [](CR<ValT> arg) -> Str {
        return std::format("{}", arg);
    };

    auto Src = TreeMirror<IdT, ValT>{
        &src,
        {TreeMirror<IdT, ValT>{&src.sub[0]},
         TreeMirror<IdT, ValT>{&src.sub[1]}}};

    auto Dst = TreeMirror<IdT, ValT>{
        &dst,
        {TreeMirror<IdT, ValT>{&dst.sub[0]},
         TreeMirror<IdT, ValT>{&dst.sub[1]},
         TreeMirror<IdT, ValT>{&dst.sub[2]}}};

    ComparisonOptions<IdT, ValT> Options{
        .getNodeValueImpl = [](IdT id) { return id->value; },
        .getNodeKindImpl  = [](IdT id) { return 0; }};

    SyntaxTree<IdT, ValT>::WalkParameters<TreeMirror<IdT, ValT>> walk{
        .getSubnodeAt     = diff::getSubnodeAtTreeMirror<IdT, ValT>,
        .getSubnodeNumber = diff::getSubnodeNumberTreeMirror<IdT, ValT>,
        .getSubnodeId     = diff::getSubnodeIdTreeMirror<IdT, ValT>,
    };

    SyntaxTree<IdT, ValT> SrcTree{Options};
    SrcTree.FromNode<TreeMirror<IdT, ValT>>(Src, walk);
    SyntaxTree<IdT, ValT> DstTree{Options};
    DstTree.FromNode(Dst, walk);

    ASTDiff<IdT, ValT> Diff{SrcTree, DstTree, Options};

    std::stringstream os;
    for (diff::NodeId Dst : DstTree) {
        diff::NodeId Src = Diff.getMapped(DstTree, Dst);
        if (Src.isValid()) {
            os << "Match ";
            printNode(os, SrcTree, Src, toStr);
            os << " to ";
            printNode(os, DstTree, Dst, toStr);
            os << "\n";
        }

        printDstChange(os, Diff, SrcTree, DstTree, Dst, toStr);
    }
}
