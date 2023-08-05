#include "org_parse_aux.hpp"

#include <lexbase/AstDiff.hpp>
#include <gtest/gtest.h>

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
        std::variant<int, double, QString> value;
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
