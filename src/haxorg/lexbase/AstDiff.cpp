#include "AstDiff.hpp"

using namespace hstd::ext::diff;
using namespace hstd;

/// Sets Height, Parent and Subnodes for each node.
struct PreorderVisitor {
    int id    = 0;
    int Depth = 0;

    NodeIdx     Parent;
    SyntaxTree& Tree;
    NodeStore*  store;

    PreorderVisitor(SyntaxTree& Tree, NodeStore* store)
        : Tree(Tree), store(store) {}

    std::tuple<NodeIdx, NodeIdx> PreTraverse(NodeStore::Id const& node) {
        NodeIdx MyId = id;
        Tree.Nodes.emplace_back(store);
        hstd::ext::diff::Node& N = Tree.getMutableNode(MyId);
        N.Parent                 = Parent;
        N.Depth                  = Depth;
        N.ASTNode                = node;

        if (Parent.isValid()) {
            hstd::ext::diff::Node& P = Tree.getMutableNode(Parent);
            P.Subnodes.push_back(MyId);
        }

        Parent = MyId;
        ++id;
        ++Depth;
        return std::make_tuple(MyId, Tree.getNode(MyId).Parent);
    }

    void PostTraverse(std::tuple<NodeIdx, NodeIdx> State) {
        NodeIdx MyId, PreviousParent;
        std::tie(MyId, PreviousParent) = State;
        assert(
            MyId.isValid() && "Expecting to only traverse valid nodes.");
        Parent = PreviousParent;
        --Depth;
        hstd::ext::diff::Node& N = Tree.getMutableNode(MyId);
        N.RightMostDescendant    = id - 1;
        assert(
            N.RightMostDescendant >= 0
            && N.RightMostDescendant < Tree.getSize()
            && "Rightmost descendant must be a valid tree node.");
        if (N.isLeaf()) { Tree.Leaves.push_back(MyId); }
        N.Height = 1;
        for (NodeIdx Subnode : N.Subnodes) {
            N.Height = std::max(
                N.Height, 1 + Tree.getNode(Subnode).Height);
        }
    }

    void Traverse(NodeStore::Id node) {
        auto SavedState = PreTraverse(node);
        for (int i = 0; i < store->getSubnodeCount(node); ++i) {
            Traverse(store->getSubnodeAt(node, i));
        }
        PostTraverse(SavedState);
    }
};


Vec<NodeIdx> hstd::ext::diff::getSubtreeBfs(
    const SyntaxTree& Tree,
    NodeIdx           Root) {
    Vec<NodeIdx> Ids;
    size_t       Expanded = 0;
    Ids.push_back(Root);
    while (Expanded < Ids.size()) {
        for (NodeIdx Subnode : Tree.getNode(Ids[Expanded++]).Subnodes) {
            Ids.push_back(Subnode);
        }
    }
    return Ids;
}

Vec<NodeIdx> hstd::ext::diff::getSubtreePostorder(
    const SyntaxTree& Tree,
    NodeIdx           Root) {
    Vec<NodeIdx>        Postorder;
    Func<void(NodeIdx)> Traverse = [&](NodeIdx id) {
        const diff::Node& N = Tree.getNode(id);
        for (NodeIdx Subnode : N.Subnodes) { Traverse(Subnode); }
        Postorder.push_back(id);
    };
    Traverse(Root);
    return Postorder;
}


void hstd::ext::diff::ASTDiff::computeChangeKinds(Mapping& M) {
    for (NodeIdx const& Id1 : src) {
        if (!M.hasSrc(Id1)) {
            src.getMutableNode(Id1).Change = ChangeKind::Delete;
            src.getMutableNode(Id1).Shift -= 1;
        }
    }
    for (NodeIdx const& Id2 : dst) {
        if (!M.hasDst(Id2)) {
            dst.getMutableNode(Id2).Change = ChangeKind::Insert;
            dst.getMutableNode(Id2).Shift -= 1;
        }
    }
    for (NodeIdx const& Id1 : src.NodesBfs) {
        NodeIdx Id2 = M.getDst(Id1);
        if (Id2.isInvalid()) { continue; }
        if (!haveSameParents(M, Id1, Id2)
            || src.findPositionInParent(Id1, true)
                   != dst.findPositionInParent(Id2, true)) {
            src.getMutableNode(Id1).Shift -= 1;
            dst.getMutableNode(Id2).Shift -= 1;
        }
    }
    for (NodeIdx const& Id2 : dst.NodesBfs) {
        NodeIdx Id1 = M.getSrc(Id2);
        if (Id1.isInvalid()) { continue; }
        Node& N1 = src.getMutableNode(Id1);
        Node& N2 = dst.getMutableNode(Id2);
        if (Id1.isInvalid()) { continue; }
        if (!haveSameParents(M, Id1, Id2)
            || src.findPositionInParent(Id1, true)
                   != dst.findPositionInParent(Id2, true)) {
            N1.Change = N2.Change = ChangeKind::Move;
        }

        if (!Options.areValuesEqual(N1, N2)) {
            N2.Change = (N1.Change == ChangeKind::Move ? ChangeKind::UpdateMove : ChangeKind::Update);
            N1.Change = N2.Change;
        }
    }
}

Mapping hstd::ext::diff::ASTDiff::greedyMatchTopDown() const {
    Mapping                      M(src.getSize() + dst.getSize());
    Func<void(NodeIdx, NodeIdx)> aux;
    aux = [&](NodeIdx srcId, NodeIdx dstId) {
        auto const& srcNode = src.getNode(srcId);
        auto const& dstNode = dst.getNode(dstId);
        if (srcNode.isLeaf() || dstNode.isLeaf()) {
            M.link(srcId, dstId);
        } else {
            for (int i = 0;
                 i < std::min(
                     srcNode.Subnodes.size(), dstNode.Subnodes.size());
                 ++i) {
                aux(srcNode.Subnodes.at(i), dstNode.Subnodes.at(i));
            }
        }
    };

    return M;
}

Mapping hstd::ext::diff::ASTDiff::matchTopDown() const {
    PriorityList L1(src);
    PriorityList L2(dst);
    Mapping      M(src.getSize() + dst.getSize());
    L1.push(src.getRootId());
    L2.push(dst.getRootId());
    int Max1, Max2;
    // until subtree of necessary height hasn't been reached
    while (std::min(Max1 = L1.peekMax(), Max2 = L2.peekMax())
           > Options.MinHeight) {
        // if two top subtrees don't have equal height
        if (Max1 > Max2) {
            // insert all nodes from tallest subforest
            for (NodeIdx const& id : L1.pop()) { L1.open(id); }
        } else if (Max2 > Max1) {
            for (NodeIdx const& id : L2.pop()) { L2.open(id); }
        } else {
            // otherwise get two subforest of equal height
            Vec<NodeIdx> H1, H2;
            H1 = L1.pop();
            H2 = L2.pop();
            // for each combination of Therese is these forests
            for (NodeIdx const& Id1 : H1) {
                for (NodeIdx const& Id2 : H2) {
                    // if pair of trees is isomorphic
                    if (identical(Id1, Id2) && !M.hasSrc(Id1)
                        && !M.hasDst(Id2)) {
                        for (int I = 0,
                                 E = src.getNumberOfDescendants(Id1);
                             I < E;
                             ++I) {
                            M.link(Id1 + I, Id2 + I);
                        }
                    }
                }
            }
            // so we basically determine if there is any isomorphic
            // mapping between either (1) roots two highest subforests
            // or (2) root and subnodes of a root in other tree


            for (NodeIdx const& Id1 : H1) {
                // if there is unmatched forest root in first forest
                if (!M.hasSrc(Id1)) {
                    // insert it's subnodes
                    L1.open(Id1);
                }
            }
            for (NodeIdx const& Id2 : H2) {
                // do the same for other forest
                if (!M.hasDst(Id2)) { L2.open(Id2); }
            }
        }
    }
    return M;
}

void hstd::ext::diff::ASTDiff::matchBottomUp(Mapping& M) const {
    Vec<NodeIdx> Postorder = getSubtreePostorder(src, src.getRootId());
    // for all nodes in left, if node itself is not matched, but
    // has any children matched
    for (NodeIdx const& Id1 : Postorder) {
        if (Id1 == src.getRootId() && !M.hasSrc(src.getRootId())
            && !M.hasDst(dst.getRootId())) {
            if (isMatchingPossible(src.getRootId(), dst.getRootId())) {
                M.link(src.getRootId(), dst.getRootId());
                addOptimalMapping(M, src.getRootId(), dst.getRootId());
            }
            break;
        }

        bool        Matched = M.hasSrc(Id1);
        const Node& N1      = src.getNode(Id1);

        bool MatchedSubnodes = std::any_of(
            N1.Subnodes.begin(), N1.Subnodes.end(), [&](NodeIdx Subnode) {
                return M.hasSrc(Subnode);
            });

        //  if it is a valid candidate and matches criteria for
        // minimum number of shares subnodes
        if (Matched || !MatchedSubnodes) { continue; }
        NodeIdx Id2 = findCandidate(M, Id1);
        if (Id2.isValid()) {
            // add node to mapping
            M.link(Id1, Id2);
            // if max of number of subnodes does not exceed threshold
            addOptimalMapping(M, Id1, Id2);
        }
    }
}

NodeIdx hstd::ext::diff::ASTDiff::findCandidate(
    const Mapping& M,
    NodeIdx        Id1) const {
    NodeIdx Candidate;
    double  HighestSimilarity = 0.0;
    for (NodeIdx const& Id2 : dst) {
        if (!isMatchingPossible(Id1, Id2)) { continue; }
        if (M.hasDst(Id2)) { continue; }
        double Similarity = getJaccardSimilarity(M, Id1, Id2);
        if (Similarity >= Options.MinSimilarity
            && Similarity > HighestSimilarity) {
            HighestSimilarity = Similarity;
            Candidate         = Id2;
        }
    }
    return Candidate;
}

double ASTDiff::getJaccardSimilarity(
    const Mapping& M,
    NodeIdx        Id1,
    NodeIdx        Id2) const {
    int         CommonDescendants = 0;
    const Node& N1                = src.getNode(Id1);
    // Count the common descendants, excluding the subtree root.
    for (NodeIdx Src = Id1 + 1; Src <= N1.RightMostDescendant; ++Src) {
        NodeIdx Dst = M.getDst(Src);
        CommonDescendants += int(
            Dst.isValid() && dst.isInSubtree(Dst, Id2));
    }
    // We need to subtract 1 to get the number of descendants excluding the
    // root.
    double Denominator = src.getNumberOfDescendants(Id1) - 1
                       + dst.getNumberOfDescendants(Id2) - 1
                       - CommonDescendants;
    // CommonDescendants is less than the size of one subtree.
    assert(Denominator >= 0 && "Expected non-negative denominator.");
    if (Denominator == 0) { return 0; }
    return CommonDescendants / Denominator;
}

void ASTDiff::addOptimalMapping(Mapping& M, NodeIdx Id1, NodeIdx Id2)
    const {
    if (std::max(
            src.getNumberOfDescendants(Id1),
            dst.getNumberOfDescendants(Id2))
        > Options.MaxSize) {
        return;
    }
    ZhangShashaMatcher Matcher{Options, *this, src, dst, Id1, Id2};
    Vec<std::pair<NodeIdx, NodeIdx>> R = Matcher.getMatchingNodes();
    // COUT << R << "\n";
    for (const auto& Tuple : R) {
        NodeIdx Src = Tuple.first;
        NodeIdx Dst = Tuple.second;
        if (!M.hasSrc(Src) && !M.hasDst(Dst)) { M.link(Src, Dst); }
    }
}

bool ASTDiff::identical(NodeIdx Id1, NodeIdx Id2) const {
    const Node& N1 = src.getNode(Id1);
    const Node& N2 = dst.getNode(Id2);
    if (N1.Subnodes.size() != N2.Subnodes.size()
        || !isMatchingPossible(Id1, Id2)
        || !Options.areValuesEqual(N1, N2)) {
        return false;
    }
    for (size_t id = 0, E = N1.Subnodes.size(); id < E; ++id) {
        if (!identical(N1.Subnodes[id], N2.Subnodes[id])) { return false; }
    }
    return true;
}

Vec<std::pair<NodeIdx, NodeIdx>> ZhangShashaMatcher::getMatchingNodes() {
    Vec<std::pair<NodeIdx, NodeIdx>>       Matches;
    Vec<std::pair<SubNodeIdx, SubNodeIdx>> TreePairs;
    computeTreeDist();
    bool RootNodePair = true;
    TreePairs.emplace_back(
        SubNodeIdx(S1.getSize()), SubNodeIdx(S2.getSize()));

    // COUT << "SRC: " << DiffImpl.src.Nodes << "\n";
    // COUT << "DST: " << DiffImpl.dst.Nodes << "\n";

    while (!TreePairs.empty()) {
        SubNodeIdx LastRow, LastCol, FirstRow, FirstCol, Row, Col;
        std::tie(LastRow, LastCol) = TreePairs.back();
        TreePairs.pop_back();
        if (!RootNodePair) { computeForestDist(LastRow, LastCol); }

        RootNodePair = false;
        FirstRow     = S1.getLeftMostDescendant(LastRow);
        FirstCol     = S2.getLeftMostDescendant(LastCol);
        Row          = LastRow;
        Col          = LastCol;
        while (Row > FirstRow || Col > FirstCol) {
            // COUT << "rowcol " << Row << " " << Col << "\n";
            // COUT << ForestDist << "\n";
            if (Row > FirstRow
                && ForestDist[Row - 1][Col] + 1 == ForestDist[Row][Col]) {
                // COUT << "Dec col\n";
                --Row;
            } else if (
                Col > FirstCol
                && ForestDist[Row][Col - 1] + 1 == ForestDist[Row][Col]) {
                // COUT << "Dec row\n";
                --Col;
            } else {
                SubNodeIdx LMD1 = S1.getLeftMostDescendant(Row);
                SubNodeIdx LMD2 = S2.getLeftMostDescendant(Col);
                // COUT << "> " << LMD1 << " " << LMD2 << " " << Row
                //      << " " << Col << "\n";
                if (LMD1 == S1.getLeftMostDescendant(LastRow)
                    && LMD2 == S2.getLeftMostDescendant(LastCol)) {
                    // COUT << "ROOT IDS " << S1.RootIds << " "
                    //      << S2.RootIds << " Row " << Row << " Col "
                    //      << Col << "\n";
                    NodeIdx Id1 = S1.getIdInRoot(Row);
                    NodeIdx Id2 = S2.getIdInRoot(Col);
                    auto    n1  = DiffImpl.src.getNode(Id1);
                    auto    n2  = DiffImpl.dst.getNode(Id2);
                    // COUT << "CMP " << Id1 << " (" << n1 << ") " <<
                    // Id2
                    //      << " (" << n2 << ") can be matched "
                    //      << n1.getNodeKind(DiffImpl.src.getOpts())
                    //      << " "
                    //      << n2.getNodeKind(DiffImpl.dst.getOpts())
                    //      << " "
                    //      << (DiffImpl.isMatchingPossible(Id1, Id2)
                    //              ? "true"
                    //              : "false")
                    //      << "\n";
                    assert(
                        DiffImpl.isMatchingPossible(Id1, Id2)
                        && "These nodes must not be matched.");
                    Matches.emplace_back(Id1, Id2);
                    --Row;
                    --Col;
                } else {
                    TreePairs.emplace_back(Row, Col);
                    Row = LMD1;
                    Col = LMD2;
                }
            }
        }
    }
    return Matches;
}

void ZhangShashaMatcher::computeForestDist(
    SubNodeIdx Id1,
    SubNodeIdx Id2) {
    assert(Id1 > 0 && Id2 > 0 && "Expecting offsets greater than 0.");
    SubNodeIdx LMD1        = S1.getLeftMostDescendant(Id1);
    SubNodeIdx LMD2        = S2.getLeftMostDescendant(Id2);
    ForestDist[LMD1][LMD2] = 0;
    for (SubNodeIdx D1 = LMD1 + 1; D1 <= Id1; ++D1) {
        ForestDist[D1][LMD2] = ForestDist[D1 - 1][LMD2]
                             + opts.DeletionCost;
        for (SubNodeIdx D2 = LMD2 + 1; D2 <= Id2; ++D2) {
            ForestDist[LMD1][D2] = ForestDist[LMD1][D2 - 1]
                                 + opts.InsertionCost;
            SubNodeIdx DLMD1 = S1.getLeftMostDescendant(D1);
            SubNodeIdx DLMD2 = S2.getLeftMostDescendant(D2);
            if (DLMD1 == LMD1 && DLMD2 == LMD2) {
                double UpdateCost  = getUpdateCost(D1, D2);
                ForestDist[D1][D2] = std::min(
                    {ForestDist[D1 - 1][D2] + opts.DeletionCost,
                     ForestDist[D1][D2 - 1] + opts.InsertionCost,
                     ForestDist[D1 - 1][D2 - 1] + UpdateCost});
                TreeDist[D1][D2] = ForestDist[D1][D2];
            } else {
                ForestDist[D1][D2] = std::min(
                    {ForestDist[D1 - 1][D2] + opts.DeletionCost,
                     ForestDist[D1][D2 - 1] + opts.InsertionCost,
                     ForestDist[DLMD1][DLMD2] + TreeDist[D1][D2]});
            }
        }
    }
    // std::cout << "---- " << Id1 << " " << Id2 << "\n";
    // for (const auto& r : ForestDist) {
    //     std::cout << r << "\n";
    // }
}

void SyntaxTree::FromNode(NodeStore* store) {
    PreorderVisitor PreorderWalker(*this, store);
    PreorderWalker.Traverse(store->getRoot());
    initTree();
}

void hstd::ext::diff::printDstChange(
    ColStream&                       os,
    const ASTDiff&                   Diff,
    const SyntaxTree&                SrcTree,
    const SyntaxTree&                DstTree,
    NodeIdx                          Dst,
    Func<ColText(CR<NodeStore::Id>)> FormatSrcTreeValue,
    Func<ColText(CR<NodeStore::Id>)> FormatDstTreeValue) {
    const diff::Node& DstNode = DstTree.getNode(Dst);
    NodeIdx           Src     = Diff.getMapped(DstTree, Dst);
    switch (DstNode.Change) {
        case ChangeKind::None: {
            os << "Unchanged";
            break;
        }
        case ChangeKind::Delete: {
            assert(false && "The destination tree can't have deletions.");
            break;
        }
        case ChangeKind::Update: {
            os << "Update ";
            os << FormatSrcTreeValue(SrcTree.getNode(Src).ASTNode);
            os << " to ";
            os << FormatDstTreeValue(DstTree.getNode(Dst).ASTNode);
            break;
        }
        case ChangeKind::Insert: [[fallthrough]];
        case ChangeKind::Move: [[fallthrough]];
        case ChangeKind::UpdateMove: {
            if (DstNode.Change == ChangeKind::Insert) {
                os << "Insert";
            } else if (DstNode.Change == ChangeKind::Move) {
                os << "Move";
            } else if (DstNode.Change == ChangeKind::UpdateMove) {
                os << "Update and Move";
            }
            os << " [" << os.yellow();
            os << FormatDstTreeValue(DstTree.getNode(Dst).ASTNode);
            os << os.end() << "] into [" << os.yellow();
            os << FormatDstTreeValue(
                DstTree.getNode(DstNode.Parent).ASTNode);
            os << os.end() << "] at " << DstTree.findPositionInParent(Dst);
            break;
        }
    }
}

void hstd::ext::diff::printNode(
    ColStream&                       os,
    const SyntaxTree&                Tree,
    NodeIdx                          id,
    Func<ColText(CR<NodeStore::Id>)> ValoStr) {
    if (id.isInvalid()) {
        os << "None";
    } else {
        os << "(" << id << "): '";
        os << Tree.getNode(id).getNodeKind().value;
        os << "' '" << ValoStr(Tree.getNode(id).ASTNode) << "'";
    }
}


void hstd::ext::diff::printMapping(
    ColStream&                       os,
    ASTDiff const&                   Diff,
    SyntaxTree const&                SrcTree,
    SyntaxTree const&                DstTree,
    Func<ColText(CR<NodeStore::Id>)> FormatSrcTreeValue,
    Func<ColText(CR<NodeStore::Id>)> FormatDstTreeValue) {

    for (NodeIdx Dst : DstTree) {
        NodeIdx Src = Diff.getMapped(DstTree, Dst);
        if (Src.isValid()) {
            os << "Match [" << os.yellow();
            printNode(os, SrcTree, Src, FormatSrcTreeValue);
            os << os.end() << "] to [" << os.yellow();
            printNode(os, DstTree, Dst, FormatDstTreeValue);
            os << os.end() << "] ";
        } else {
            os << "Dst to [" << os.blue();
            printNode(os, DstTree, Dst, FormatDstTreeValue);
            os << os.end() << "] ";
        }

        printDstChange(
            os,
            Diff,
            SrcTree,
            DstTree,
            Dst,
            FormatSrcTreeValue,
            FormatDstTreeValue);

        os << "\n";
    }
}
