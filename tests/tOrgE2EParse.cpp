#include "common.hpp"
#include "org_parse_aux.hpp"
#include <gtest/gtest.h>

#include <parse/OrgParser.hpp>
#include <parse/OrgTokenizer.hpp>
#include <gtest/gtest.h>

#include <lexbase/AstSpec.hpp>
#include <lexbase/AstDiff.hpp>
#include <lexbase/AstGraph.hpp>
#include <lexbase/NodeTest.hpp>

#include <hstd/stdlib/diffs.hpp>

#include <hstd/stdlib/Filesystem.hpp>

template <
    /// Node kind
    typename N,
    /// Token kind
    typename K,
    /// Node value kind
    typename Val>
diff::ComparisonOptions<NodeId<N, K>, Val> nodeAdapterComparisonOptions(
    /// Map DOD node ID to the node object
    Func<CR<Node<N, K>>(NodeId<N, K>)> getNode,
    /// Map DOD node value from node object
    Func<CR<Val>(NodeId<N, K>)> getValue) {
    return {
        .getNodeValueImpl =
            [getValue](NodeId<N, K> id) { return getValue(id); },
        .getNodeKindImpl =
            [getNode](NodeId<N, K> id) {
                return static_cast<int>(getNode(id).kind);
            }};
}

TEST(TestFiles, Spec) {
    auto       file = (__CURRENT_FILE_DIR__ / "spec.yaml");
    YAML::Node spec = YAML::LoadFile(file.toStdString());
    ParseSpec  parsed(spec, file);
}

TEST(SimpleNodeConversion, SingleHashTagToken) {
    MockFull p;
    p.run("#test", &T::lexText, &P::parseHashTag);
    EXPECT_EQ(p.n(0).kind, org::HashTag);
    EXPECT_EQ(p.n(1).kind, org::RawText);
}

TEST(SimpleNodeConversion, DoubleHashTag) {
    MockFull p;
    p.run("#test##a", &T::lexText, &P::parseHashTag);
    EXPECT_EQ(p.k(0), org::HashTag);
    EXPECT_EQ(p.k(1), org::RawText);
    EXPECT_EQ(p.s(1), "#test");
    QString     buf;
    QTextStream ss{&buf};
    ss << "start validation output" << Qt::endl;
    ss << spec.validateSelf(p.a(0)) << "\n";
    ss << spec.validateSub(p.a(0), 0) << "\n";
    ss << spec.getSingleSubnodeIdx(p.a(0), OrgSpecName::Head);
    spec.getSingleSubnodeIdx(org::HashTag, OrgSpecName::Head);
    spec.getMultipleSubnode(p.a(0), OrgSpecName::Head);
    spec.fieldName(p.a(0), 0);

    spec.isSingleField(p.a(0), 0);
    spec.fieldDoc(p.a(0), 0);
}

TEST(SimpleNodeConversion, NestedHashTag) {
    MockFull p;
    p.run("#test##[a, b]", &T::lexText, &P::parseHashTag);
    auto node = yamlRepr(p.a(0));
    yamlRepr(p.nodes);
    yamlRepr(p.tokens);
    QString     buf;
    QTextStream ss{&buf};
    ss << "yaml node\n" << yamlRepr(spec, p.a(0)) << "\nend yaml node\n";
    ss << "json node\n" << jsonRepr(spec, p.a(0)) << "\nend json node\n";
    ss << "flat repr\n" << jsonRepr(p.nodes) << "\nend flat nodes\n";
    ss << "token repr\n" << jsonRepr(p.tokens) << "\nend flat tokens\n";
    ss << "yaml node\n" << yamlRepr(p.a(0)) << "\nend yaml node\n";
    ss << "flat repr\n" << yamlRepr(p.nodes) << "\nend flat nodes\n";
    ss << "token repr\n" << yamlRepr(p.tokens) << "\nend flat tokens\n";

    // qcout << buf << Qt::endl;
    // auto hash = sem::OrgConverter{}.convertHashTag(nullptr, p.a(0));
}

TEST(SimpleNodeConversion, DiffCompilation) {
    MockFull p;
    p.run("#test##[a, b]", &T::lexText, &P::parseHashTag);
    auto cmp = nodeAdapterComparisonOptions<
        OrgNodeKind,
        OrgTokenKind,
        Str>(
        [&p](OrgId id) -> OrgNode { return p.nodes.at(id); },
        [&p](OrgId id) -> Str { return p.nodes.strVal(id); });
}

TEST(SimpleNodeConversion, GraphRepr) {
    MockFull p;
    p.run("#test##[a, b]", &T::lexText, &P::parseHashTag);
    auto g = graphRepr(&p.nodes, OrgId(0));

    std::stringstream os;
    boost::write_graphviz(
        os,
        g,
        [&g,
         &p](std::ostream& os, VertDesc<OrgNodeKind, OrgTokenKind> vert) {
            os << "[label=\"" << to_string(p.nodes.at(g[vert].id).kind)
               << "\"]";
        });
}

TEST(SimpleNodeConversion, LCSCompile) {
    Vec<int> first{1, 2, 3};
    Vec<int> second{1, 2, 3};
    auto     res = longestCommonSubsequence<int>(
        first,
        second,
        [](CR<int> lhs, CR<int> rhs) { return lhs == rhs; },
        [](CR<int> lhs, CR<int> rhs) {
            if (lhs == rhs) {
                return 1;
            } else {
                return 0;
            }
        });
    // You may want to add test conditions to check the results.
}

TEST(SimpleNodeConversion, MyersDiffCompile) {
    Vec<int> first{1, 2, 3};
    Vec<int> second{1, 2, 3};
    auto res = myersDiff<int>(first, second, [](CR<int> lhs, CR<int> rhs) {
        return lhs == rhs;
    });
    // You may want to add test conditions to check the results.
}

TEST(Algorithms, Partitioning) {
    Vec<int> it{1, 1, 2, 2, 3, 3, 4, 4, 3};
    auto     spans = partition<int, int>(
        it, [](CR<int> v) -> int { return v; });
    EXPECT_EQ(spans.size(), 5);
    EXPECT_EQ(spans[0].size(), 2);
    EXPECT_EQ(spans[1].size(), 2);
    EXPECT_EQ(spans[1_B].size(), 1);
}

TEST(Algorithms, PartitioningEmptyVector) {
    Vec<int> input;
    auto     result = partition<int, int>(
        input, [](CR<int> i) { return i % 2 == 0; });
    EXPECT_TRUE(result.empty());
}

TEST(Algorithms, PartitioningSingleElementVector) {
    Vec<int> input  = {1};
    auto     result = partition<int, int>(
        input, [](CR<int> i) { return i % 2 == 0; });
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], input);
}

TEST(Algorithms, PartitioningOddEvenNumbers) {
    Vec<int> input  = {1, 2, 3, 4, 5};
    auto     result = partition<int, int>(
        input, [](CR<int> i) { return i % 2 == 0; });
    EXPECT_EQ(result.size(), 5);
    EXPECT_EQ(result[0], Vec<int>({1}));
    EXPECT_EQ(result[1], Vec<int>({2}));
}

TEST(Algorithms, PartitioningPositiveNegativeNumbers) {
    Vec<int> input  = {-1, -2, 3, 4, -5};
    auto     result = partition<int, int>(
        input, [](CR<int> i) { return 0 <= i; });
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], Vec<int>({-1, -2}));
    EXPECT_EQ(result[1], Vec<int>({3, 4}));
    EXPECT_EQ(result[2], Vec<int>({-5}));
}


using namespace diff;


TEST(AstDiff, PointerBasedNodes) {
    struct RealNode {
        QString       value;
        int           kind;
        Vec<RealNode> sub;

        using IdT  = RealNode*;
        using ValT = QString;

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
        return to_string(arg);
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


    QString     buf;
    QTextStream os{&buf};
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
        swl::variant<int, double, QString> value;
        Vec<RealNode>                      sub;
    };

    auto src = RealNode{
        "toplevel", {RealNode{1}, RealNode{1.2}, RealNode{"subnode"}}};

    auto dst = RealNode{
        "toplevel", {RealNode{22}, RealNode{1.2}, RealNode{"subnode'"}}};

    using IdT  = RealNode*;
    using ValT = decltype(src.value);


    Func<Str(CR<ValT>)> toStr = [](CR<ValT> arg) -> Str {
        return variant_to_string(arg);
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

    QString     buf;
    QTextStream os{&buf};
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
