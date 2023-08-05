#pragma once

#include <hstd/system/string_convert.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/system/generator.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Func.hpp>


#include <iostream>
#include <cassert>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <limits>
#include <functional>
#include <memory>
#include <optional>
#include <vector>


#define COUT std::cout << "[\033[33m" << __LINE__ << "\033[0m] "

namespace diff {
template <int Idx, typename... Args>
void writeIfIndex(QTextStream& os, std::variant<Args...> const& var) {
    if constexpr (Idx == 0) {
        os << Idx << " " << std::get<Idx>(var);
    } else {
        if (var.index() == Idx) {
            os << Idx << " " << std::get<Idx>(var);
        } else {
            writeIfIndex<Idx - 1>(os, var);
        }
    }
}

/// \brief Within a tree, this identifies a node by its preorder offset.
///
/// Internally this is an index into a flat structure that holds syntax
/// tree nodes. Access to the target node is performed via vector indexing.
struct NodeId {
  private:
    static constexpr int InvalidNodeOffset = -1;

  public:
    int Offset; /// Offset in the postorder iteratio
    inline NodeId() : Offset(InvalidNodeOffset) {}
    inline NodeId(int Offset) : Offset(Offset) {}

    inline operator int() const { return Offset; }
    inline NodeId& operator++() { return ++Offset, *this; }
    inline NodeId& operator--() { return --Offset, *this; }
    /// Support defining iterators on NodeId.
    inline NodeId& operator*() { return *this; }
    inline bool    isValid() const { return Offset != InvalidNodeOffset; }
    inline bool isInvalid() const { return Offset == InvalidNodeOffset; }

    inline void assertValid(std::string const& msg) const {
        if (isInvalid()) {
            throw std::domain_error(
                "non-valid (-1) node found for " + msg);
        }
    }
};

class Mapping {
  public:
    Mapping()                           = default;
    Mapping(Mapping&& Other)            = default;
    Mapping& operator=(Mapping&& Other) = default;

    Mapping(size_t Size) {
        SrcToDst.resize(Size);
        DstToSrc.resize(Size);
    }

    void link(NodeId Src, NodeId Dst) {
        SrcToDst[Src] = Dst;
        DstToSrc[Dst] = Src;
    }

    NodeId getDst(NodeId Src) const { return SrcToDst[Src]; }
    NodeId getSrc(NodeId Dst) const { return DstToSrc[Dst]; }
    bool   hasSrc(NodeId Src) const { return getDst(Src).isValid(); }
    bool   hasDst(NodeId Dst) const { return getSrc(Dst).isValid(); }

  private:
    Vec<NodeId> SrcToDst;
    Vec<NodeId> DstToSrc;
};

enum class ChangeKind
{
    None,
    Delete, //! (Src): delete node Src.
    Update, //! (Src, Dst): update the value of node Src to match Dst.
    Insert, //! (Src, Dst, Pos): insert Src as child of Dst at offset Pos.
    Move, //! (Src, Dst, Pos): move Src to be a child of Dst at offset Pos.
    UpdateMove //! Same as Move plus Update.
};

BOOST_DESCRIBE_ENUM(
    ChangeKind,
    None,
    Delete,
    Update,
    Insert,
    Move,
    UpdateMove);

struct ASTNodeKind {
    int value = 0;
    ASTNodeKind(int kind) : value(kind) {}
    bool operator==(ASTNodeKind const& other) const {
        return value == other.value;
    }
};


template <typename Id, typename Val>
struct Node;

template <typename Id, typename Val>
struct ComparisonOptions {
    /// During top-down matching, only consider nodes of at least this
    /// height.
    int MinHeight = 2;
    /// During bottom-up matching, match only nodes with at least this
    /// value as the ratio of their common descendants.
    double MinSimilarity = 0.5;
    /// Whenever two subtrees are matched in the bottom-up phase, the
    /// optimal mapping is computed, unless the size of either subtrees
    /// exceeds this.
    int  MaxSize          = 100;
    bool StopAfterTopDown = false;
    /// \brief Get node value from specified ID
    Func<Val(Id)> getNodeValueImpl;
    /// \brief Get node kind in integer form (usually static cast of enum
    /// to int)
    Func<int(Id)> getNodeKindImpl;
    /// \brief Can node with these IDs be matched together? Callback can be
    /// empty
    Func<bool(Id, Id)> isMatchingAllowedImpl;
    /// Returns false if the nodes should never be matched.
    bool isMatchingAllowed(
        const Node<Id, Val>& N1,
        const Node<Id, Val>& N2) const {
        if (isMatchingAllowedImpl
            && isMatchingAllowedImpl(N1.ASTNode, N2.ASTNode)) {
            return true;
        } else {
            return N1.getNodeKind(*this) == N2.getNodeKind(*this);
        }
    }

    Val getNodeValue(Id id) const { return getNodeValueImpl(id); }
    int getNodeKind(Id id) const { return getNodeKindImpl(id); }
};


/// \brief Temporary container for transitioning the original AST structure
/// to the SyntaxTree form.
template <typename Id, typename Val>
struct TreeMirror {
    Id id; /// Identifier value that can be used to get back the original
           /// node information

    Vec<TreeMirror<Id, Val>> subnodes; /// List of the subnodes
};

template <typename Id, typename Val>
CR<TreeMirror<Id, Val>> getSubnodeAtTreeMirror(
    CR<TreeMirror<Id, Val>> tree,
    int                     index) {
    return tree.subnodes.at(index);
}

template <typename Id, typename Val>
int getSubnodeNumberTreeMirror(CR<TreeMirror<Id, Val>> tree) {
    return tree.subnodes.size();
}

template <typename Id, typename Val>
Id getSubnodeIdTreeMirror(CR<TreeMirror<Id, Val>> tree) {
    return tree.id;
}


/// \brief Represents an AST node, alongside some additional information.
///
/// Single node of the original AST
template <typename Id, typename Val>
struct Node {
    NodeId      Parent              = NodeId();
    NodeId      LeftMostDescendant  = NodeId();
    NodeId      RightMostDescendant = NodeId();
    int         Depth               = 0;
    int         Height              = 0;
    int         Shift               = 0;
    Id          ASTNode  = Id(); /// Reference to the original AST node
    Vec<NodeId> Subnodes = {};   /// Explicit list of the subnode IDS
    ChangeKind  Change   = ChangeKind::None;

    ASTNodeKind getNodeKind(
        ComparisonOptions<Id, Val> const& _opts) const {
        return _opts.getNodeKind(ASTNode);
    }

    bool isLeaf() const { return Subnodes.empty(); }
};

inline QTextStream& operator<<(QTextStream& os, NodeId id) {
    os << id.Offset;
    return os;
}

template <typename Id, typename Val>
QTextStream& operator<<(QTextStream& os, Node<Id, Val> const& node) {
    os << "{H:" << node.Height << ", D:" << node.Depth
       << ", S:" << node.Shift << ", P:" << node.Parent
       << ", L:" << node.LeftMostDescendant
       << ", R:" << node.RightMostDescendant << "}";
    return os;
}


/// SyntaxTree objects represent subtrees of the AST.
///
/// There are only two instances of the SyntaxTree class during comparison
/// - destination and source. Structure is not recursive in tiself -
/// subnodes are determined based on the Node::Subnodes field which
/// explicitly stores list of subnode ids.
template <typename Id, typename Val>
class SyntaxTree {
  public:
    SyntaxTree(SyntaxTree<Id, Val>&& Other) = default;
    ~SyntaxTree()                           = default;
    using PreorderIterator                  = NodeId;

    ComparisonOptions<Id, Val> const& getOpts() const { return opts; }

  public:
    SyntaxTree(ComparisonOptions<Id, Val> const& opts);
    template <typename InNode>
    struct WalkParameters {
        /// Get subnode at position
        Func<CR<InNode>(CR<InNode>, int)> getSubnodeAt;
        /// Get number of subnodes for input node
        Func<int(CR<InNode>)> getSubnodeNumber;
        /// Get ID for subnode
        Func<Id(CR<InNode>)> getSubnodeId;
    };

    /// Constructs a tree from an AST node using provided accessor
    /// callbacks
    template <typename InNode>
    void FromNode(InNode const& N, CR<WalkParameters<InNode>> walk);
    /// Nodes in preorder.
    Vec<Node<Id, Val>> Nodes;
    Vec<NodeId>        Leaves;
    /// Maps preorder indices to postorder ones.
    Vec<int>                   PostorderIds;
    Vec<NodeId>                NodesBfs;
    int                        getSize() const { return Nodes.size(); }
    NodeId                     getRootId() const { return 0; }
    PreorderIterator           begin() const { return getRootId(); }
    PreorderIterator           end() const { return getSize(); }
    ComparisonOptions<Id, Val> opts;

    Node<Id, Val> const& getNode(NodeId id) const {
        return Nodes.at(id.Offset);
    }
    NodeId getParent(NodeId id) { return getNode(id).Parent; }

    Vec<NodeId> getParentIdChain(NodeId id, bool withSelf = true) {
        Vec<NodeId> result;

        if (withSelf) {
            result.push_back(id);
        }

        NodeId parent = getParent(id);
        while (parent.isValid()) {
            result.push_back(parent);
            parent = getParent(parent);
        }

        std::reverse(result.begin(), result.end());

        return result;
    }

    Vec<Id> getBaseIdChain(NodeId node, bool withSelf) {
        Vec<Id> result;
        for (auto const& node : getParentIdChain(node, withSelf)) {
            result.push_back(getNode(node).ASTNode);
        }
        return result;
    }

    Node<Id, Val>& getMutableNode(NodeId id) { return Nodes[id]; }

    generator<NodeId> nodeIds() {
        for (int i = 0; i < Nodes.size(); ++i) {
            co_yield NodeId(i);
        }
    }

    bool isValidNodeId(NodeId id) const {
        return 0 <= id && id < getSize();
    }

    void addNode(Node<Id, Val>& N) { Nodes.push_back(N); }

    int getNumberOfDescendants(NodeId id) const {
        return getNode(id).RightMostDescendant - id + 1;
    }

    bool isInSubtree(NodeId id, NodeId SubtreeRoot) const {
        return SubtreeRoot <= id
            && id <= getNode(SubtreeRoot).RightMostDescendant;
    }

    int findPositionInParent(NodeId id, bool Shifted = false) const {
        NodeId Parent = getNode(id).Parent;
        if (Parent.isInvalid()) {
            return 0;
        }
        const auto& Siblings = getNode(Parent).Subnodes;
        int         Position = 0;
        for (int I = 0, E = Siblings.size(); I < E; ++I) {
            if (Shifted) {
                Position += getNode(Siblings[I]).Shift;
            }
            if (Siblings[I] == id) {
                Position += I;
                return Position;
            }
        }

        assert(false && "Node not found in parent's children.");
    }

    /// Serialize the node attributes to a string representation. This
    /// should uniquely distinguish nodes of the same kind. Note that this
    /// function just returns a representation of the node value, not
    /// considering descendants.
    Val getNodeValue(NodeId id) const { return getNodeValue(getNode(id)); }
    int getNodeKind(NodeId id) const { return getNodeKind(getNode(id)); }

    Val getNodeValue(const Node<Id, Val>& Node) const {
        return opts.getNodeValue(Node.ASTNode);
    }

    int getNodeKind(const Node<Id, Val>& Node) const {
        return opts.getNodeKind(Node.ASTNode);
    }

  private:
    void initTree() {
        setLeftMostDescendants();
        int PostorderId = 0;
        PostorderIds.resize(getSize());
        Func<void(NodeId)> PostorderTraverse = [&](NodeId id) {
            for (NodeId Subnode : getNode(id).Subnodes) {
                PostorderTraverse(Subnode);
            }
            PostorderIds[id] = PostorderId;
            ++PostorderId;
        };
        PostorderTraverse(getRootId());
        NodesBfs = getSubtreeBfs<Id, Val>(*this, getRootId());
    }

    void setLeftMostDescendants() {
        for (NodeId Leaf : Leaves) {
            getMutableNode(Leaf).LeftMostDescendant = Leaf;
            NodeId Parent, Cur = Leaf;
            while ((Parent = getNode(Cur).Parent).isValid()
                   && getNode(Parent).Subnodes[0] == Cur) {
                Cur                                    = Parent;
                getMutableNode(Cur).LeftMostDescendant = Leaf;
            }
        }
    }
};


template <typename Id, typename Val>
class ASTDiff {
  public:
    ~ASTDiff() = default;

  public:
    struct Change {
        struct MovePoint {
            /// Insert the node under a specified original tree
            NodeId under;
            /// Insert the node on specified position
            int position = 0;
        };

        struct Insert {
            MovePoint to;
        };

        struct Move {
            MovePoint from;
            MovePoint to;
            bool      update = false;
        };

        struct Update {};
        struct None {};
        struct Delete {};

        SUB_VARIANTS(
            Kind,
            Data,
            data,
            getKind,
            Insert,
            Move,
            Update,
            None,
            Delete);

        NodeId   src;
        NodeId   dst;
        ASTDiff* diff;
        Data     data;

        Change() {}
        Change(CR<Data> data, ASTDiff* diff, NodeId src, NodeId dst)
            : src(src), dst(dst), diff(diff), data(data) {}

        Val getSrcValue() const {
            Q_ASSERT(src.isValid());
            return diff->src.getNodeValue(src);
        }

        Val getDstValue() const {
            Q_ASSERT(dst.isValid());
            return diff->dst.getNodeValue(dst);
        }

        int getSrcKind() const {
            Q_ASSERT(src.isValid());
            return diff->dst.getNodeKind(dst);
        }

        int getDstKind() const {
            Q_ASSERT(dst.isValid());
            return diff->src.getNodeKind(src);
        }
    };


    SyntaxTree<Id, Val>& src;
    SyntaxTree<Id, Val>& dst;

    Mapping TheMapping;
    ASTDiff(
        SyntaxTree<Id, Val>&              src,
        SyntaxTree<Id, Val>&              dst,
        const ComparisonOptions<Id, Val>& Options)
        : src(src), dst(dst), Options(Options) {
        computeMapping();
        computeChangeKinds(TheMapping);
    }

    Change getChange(NodeId srcNode, NodeId dstNode, bool fromDst) {
        Change result;

        Node<Id, Val> const& node = fromDst ? dst.getNode(dstNode)
                                            : src.getNode(srcNode);
        switch (node.Change) {
            case ChangeKind::Delete: {
                result.data = typename Change::Delete();
                break;
            }

            case ChangeKind::None: {
                result.data = typename Change::None{};
                break;
            }

            case ChangeKind::Update: {
                result.data = typename Change::Update{};
                break;
            }

            case ChangeKind::UpdateMove:
            case ChangeKind::Move: {
                result.data = typename Change::Move{
                    .update = node.Change == ChangeKind::Update,
                    .from   = {
                        .under    = src.getNode(srcNode).Parent,
                        .position = src.findPositionInParent(srcNode, true),
                    },
                    .to     = {
                        .under    = dst.getNode(dstNode).Parent,
                        .position = dst.findPositionInParent(dstNode, true),
                    },
                };
                break;
            }

            case ChangeKind::Insert: {
                result.data = typename Change::Insert{
                    .to = {
                        .under    = node.Parent,
                        .position = //
                        fromDst ? dst.findPositionInParent(dstNode)
                                : src.findPositionInParent(srcNode),
                    }};
                break;
            }
        }

        result.src  = srcNode;
        result.dst  = dstNode;
        result.diff = this;

        return result;
    }

    Change getChangeFromDst(NodeId dst) {
        return getChange(TheMapping.getSrc(dst), dst, true);
    }

    Change getChangeFromSrc(NodeId src) {
        return getChange(src, TheMapping.getDst(src), false);
    }

    Vec<Change> getAllChanges() {
        Vec<Change> result;
        for (NodeId const& dstNode : dst.nodeIds()) {
            result.push_back(getChangeFromDst(dstNode));
        }

        for (NodeId const& srcNode : src.nodeIds()) {
            if (this->src.getNode(srcNode).Change == ChangeKind::Delete) {
                result.push_back(getChangeFromSrc(srcNode));
            }
        }

        return result;
    }

    /// Matches nodes one-by-one based on their similarity.
    void computeMapping() {
        TheMapping = matchTopDown();
        if (Options.StopAfterTopDown) {
            return;
        }
        matchBottomUp(TheMapping);
    }

    /// Compute Change for each node based on similarity.
    void computeChangeKinds(Mapping& M);
    /// Returns the ID of the node that is mapped to the given node in
    /// SourceTree.
    NodeId getMapped(const SyntaxTree<Id, Val>& Tree, NodeId id) const {
        if (&Tree == &src) {
            return TheMapping.getDst(id);
        }
        assert(&Tree == &dst && "Invalid tree.");
        return TheMapping.getSrc(id);
    }

  private:
    /// Returns true if the two subtrees are isomorphic to each other.
    bool identical(NodeId Id1, NodeId Id2) const;
    /// Returns false if the nodes must not be mached.
    bool isMatchingPossible(NodeId Id1, NodeId Id2) const {
        return Options.isMatchingAllowed(
            src.getNode(Id1), dst.getNode(Id2));
    }
    /// Returns true if the nodes' parents are matched.
    bool haveSameParents(const Mapping& M, NodeId Id1, NodeId Id2) const {
        NodeId P1 = src.getNode(Id1).Parent;
        NodeId P2 = dst.getNode(Id2).Parent;
        return (P1.isInvalid() && P2.isInvalid())
            || (P1.isValid() && P2.isValid() && M.getDst(P1) == P2);
    }
    /// Uses an optimal albeit slow algorithm to compute a mapping
    /// between two subtrees, but only if both have fewer nodes than
    /// MaxSize.
    void addOptimalMapping(Mapping& M, NodeId Id1, NodeId Id2) const;
    /// Computes the ratio of common descendants between the two nodes.
    /// Descendants are only considered to be equal when they are mapped in
    /// M.
    double getJaccardSimilarity(const Mapping& M, NodeId Id1, NodeId Id2)
        const;
    /// Returns the node that has the highest degree of similarity.
    NodeId findCandidate(const Mapping& M, NodeId Id1) const;
    /// Returns a mapping of identical subtrees.
    Mapping matchTopDown() const;
    /// Tries to match any yet unmapped nodes, in a bottom-up fashion.
    void                              matchBottomUp(Mapping& M) const;
    const ComparisonOptions<Id, Val>& Options;
    template <typename Id_, typename Val_>
    friend class ZhangShashaMatcher;
};

/// Sets Height, Parent and Subnodes for each node.
template <typename Id, typename Val, typename InNode>
struct PreorderVisitor {
    int id    = 0;
    int Depth = 0;

    NodeId               Parent;
    SyntaxTree<Id, Val>& Tree;

    typename SyntaxTree<Id, Val>::template WalkParameters<InNode> walk;

    PreorderVisitor(
        SyntaxTree<Id, Val>& Tree,
        CR<typename SyntaxTree<Id, Val>::template WalkParameters<InNode>>
            walk)
        : Tree(Tree), walk(walk) {}

    std::tuple<NodeId, NodeId> PreTraverse(InNode const& node) {
        NodeId MyId = id;
        Tree.Nodes.emplace_back();
        Node<Id, Val>& N = Tree.getMutableNode(MyId);
        N.Parent         = Parent;
        N.Depth          = Depth;
        N.ASTNode        = walk.getSubnodeId(node);

        if (Parent.isValid()) {
            Node<Id, Val>& P = Tree.getMutableNode(Parent);
            P.Subnodes.push_back(MyId);
        }

        Parent = MyId;
        ++id;
        ++Depth;
        return std::make_tuple(MyId, Tree.getNode(MyId).Parent);
    }

    void PostTraverse(std::tuple<NodeId, NodeId> State) {
        NodeId MyId, PreviousParent;
        std::tie(MyId, PreviousParent) = State;
        assert(
            MyId.isValid() && "Expecting to only traverse valid nodes.");
        Parent = PreviousParent;
        --Depth;
        Node<Id, Val>& N      = Tree.getMutableNode(MyId);
        N.RightMostDescendant = id - 1;
        assert(
            N.RightMostDescendant >= 0
            && N.RightMostDescendant < Tree.getSize()
            && "Rightmost descendant must be a valid tree node.");
        if (N.isLeaf()) {
            Tree.Leaves.push_back(MyId);
        }
        N.Height = 1;
        for (NodeId Subnode : N.Subnodes) {
            N.Height = std::max(
                N.Height, 1 + Tree.getNode(Subnode).Height);
        }
    }

    void Traverse(CR<InNode> node) {
        auto SavedState = PreTraverse(node);
        for (int i = 0; i < walk.getSubnodeNumber(node); ++i) {
            Traverse(walk.getSubnodeAt(node, i));
        }
        PostTraverse(SavedState);
    }
};

template <typename Id, typename Val>
SyntaxTree<Id, Val>::SyntaxTree(ComparisonOptions<Id, Val> const& _opts)
    : opts(_opts) {}

template <typename Id, typename Val>
template <typename InNode>
void SyntaxTree<Id, Val>::FromNode(
    InNode const&                                   N,
    CR<SyntaxTree<Id, Val>::WalkParameters<InNode>> walk) {
    PreorderVisitor<Id, Val, InNode> PreorderWalker(*this, walk);
    PreorderWalker.Traverse(N);
    initTree();
}

template <typename Id, typename Val>
static Vec<NodeId> getSubtreePostorder(
    const SyntaxTree<Id, Val>& Tree,
    NodeId                     Root) {
    Vec<NodeId>        Postorder;
    Func<void(NodeId)> Traverse = [&](NodeId id) {
        const Node<Id, Val>& N = Tree.getNode(id);
        for (NodeId Subnode : N.Subnodes) {
            Traverse(Subnode);
        }
        Postorder.push_back(id);
    };
    Traverse(Root);
    return Postorder;
}

template <typename Id, typename Val>
static Vec<NodeId> getSubtreeBfs(
    const SyntaxTree<Id, Val>& Tree,
    NodeId                     Root) {
    Vec<NodeId> Ids;
    size_t      Expanded = 0;
    Ids.push_back(Root);
    while (Expanded < Ids.size()) {
        for (NodeId Subnode : Tree.getNode(Ids[Expanded++]).Subnodes) {
            Ids.push_back(Subnode);
        }
    }
    return Ids;
}


/// \brief Identifies a node in a subtree by its postorder offset, starting
/// at 1.
struct SubNodeId {
    int Id = 0;
    explicit SubNodeId(int Id) : Id(Id) {}
    explicit SubNodeId() = default;
    operator int() const { return Id; }
    SubNodeId& operator++() { return ++Id, *this; }
    SubNodeId& operator--() { return --Id, *this; }
    SubNodeId  operator+(int Other) const { return SubNodeId(Id + Other); }
};


template <typename Id, typename Val>
class Subtree {
  public:
    /// The parent tree.
    const SyntaxTree<Id, Val>& Tree;
    /// Maps SubNodeIds to original ids.
    Vec<NodeId> RootIds;
    /// Maps subtree nodes to their leftmost descendants wtihin the
    /// subtree.
    Vec<SubNodeId> LeftMostDescendants;

  public:
    Vec<SubNodeId> KeyRoots;
    Subtree(const SyntaxTree<Id, Val>& Tree, NodeId SubtreeRoot)
        : Tree(Tree) {
        RootIds       = getSubtreePostorder<Id, Val>(Tree, SubtreeRoot);
        int NumLeaves = setLeftMostDescendants();
        computeKeyRoots(NumLeaves);
    }

    int getSize() const { return RootIds.size(); }

    NodeId getIdInRoot(SubNodeId id) const {
        assert(id > 0 && id <= getSize() && "Invalid subtree node index.");
        return RootIds[id - 1];
    }

    const Node<Id, Val>& getNode(SubNodeId id) const {
        return Tree.getNode(getIdInRoot(id));
    }

    SubNodeId getLeftMostDescendant(SubNodeId id) const {
        assert(id > 0 && id <= getSize() && "Invalid subtree node index.");
        return LeftMostDescendants[id - 1];
    }
    /// Returns the postorder index of the leftmost descendant in the
    /// subtree.
    NodeId getPostorderOffset() const {
        return Tree.PostorderIds[getIdInRoot(SubNodeId(1))];
    }

    Val getNodeValue(SubNodeId id) const {
        return Tree.getNodeValue(getIdInRoot(id));
    }

  private:
    /// Returns the number of leafs in the subtree.
    int setLeftMostDescendants() {
        int NumLeaves = 0;
        LeftMostDescendants.resize(getSize());
        for (int I = 0; I < getSize(); ++I) {
            SubNodeId            SI(I + 1);
            const Node<Id, Val>& N = getNode(SI);
            NumLeaves += N.isLeaf();
            assert(
                I == Tree.PostorderIds[getIdInRoot(SI)] -
                         getPostorderOffset() &&
                "Postorder traversal in subtree should correspond to "
                "traversal in the root tree by a constant offset.");
            LeftMostDescendants[I] = SubNodeId(
                Tree.PostorderIds[N.LeftMostDescendant]
                - getPostorderOffset());
        }
        return NumLeaves;
    }

    void computeKeyRoots(int Leaves) {
        KeyRoots.resize(Leaves);
        std::unordered_set<int> Visited;
        int                     K = Leaves - 1;
        for (SubNodeId I(getSize()); I > 0; --I) {
            SubNodeId LeftDesc = getLeftMostDescendant(I);
            if (0 < Visited.count(LeftDesc)) {
                continue;
            }
            assert(K >= 0 && "K should be non-negative");
            KeyRoots[K] = I;
            Visited.insert(LeftDesc);
            --K;
        }
    }
};

/// Implementation of Zhang and Shasha's Algorithm for tree edit distance.
/// Computes an optimal mapping between two trees using only
/// insertion, deletion and update as edit actions (similar to the
/// Levenshtein distance).
template <typename Id, typename Val>
class ZhangShashaMatcher {
    const ASTDiff<Id, Val>& DiffImpl;
    Subtree<Id, Val>        S1;
    Subtree<Id, Val>        S2;
    Vec<Vec<double>>        TreeDist, ForestDist;

  public:
    ZhangShashaMatcher(
        const ASTDiff<Id, Val>&    DiffImpl,
        const SyntaxTree<Id, Val>& src,
        const SyntaxTree<Id, Val>& dst,
        NodeId                     Id1,
        NodeId                     Id2)
        : DiffImpl(DiffImpl), S1(src, Id1), S2(dst, Id2) {

        TreeDist.resize(size_t(S1.getSize()) + 1);
        ForestDist.resize(size_t(S1.getSize()) + 1);

        for (int I = 0, E = S1.getSize() + 1; I < E; ++I) {
            TreeDist[I].resize(size_t(S2.getSize()) + 1);
            ForestDist[I].resize(size_t(S2.getSize()) + 1);
        }
    }

    Vec<std::pair<NodeId, NodeId>> getMatchingNodes() {
        Vec<std::pair<NodeId, NodeId>>       Matches;
        Vec<std::pair<SubNodeId, SubNodeId>> TreePairs;
        computeTreeDist();
        bool RootNodePair = true;
        TreePairs.emplace_back(
            SubNodeId(S1.getSize()), SubNodeId(S2.getSize()));

        // COUT << "SRC: " << DiffImpl.src.Nodes << "\n";
        // COUT << "DST: " << DiffImpl.dst.Nodes << "\n";

        while (!TreePairs.empty()) {
            SubNodeId LastRow, LastCol, FirstRow, FirstCol, Row, Col;
            std::tie(LastRow, LastCol) = TreePairs.back();
            TreePairs.pop_back();
            if (!RootNodePair) {
                computeForestDist(LastRow, LastCol);
            }

            RootNodePair = false;
            FirstRow     = S1.getLeftMostDescendant(LastRow);
            FirstCol     = S2.getLeftMostDescendant(LastCol);
            Row          = LastRow;
            Col          = LastCol;
            while (Row > FirstRow || Col > FirstCol) {
                // COUT << "rowcol " << Row << " " << Col << "\n";
                // COUT << ForestDist << "\n";
                if (Row > FirstRow
                    && ForestDist[Row - 1][Col] + 1
                           == ForestDist[Row][Col]) {
                    // COUT << "Dec col\n";
                    --Row;
                } else if (
                    Col > FirstCol
                    && ForestDist[Row][Col - 1] + 1
                           == ForestDist[Row][Col]) {
                    // COUT << "Dec row\n";
                    --Col;
                } else {
                    SubNodeId LMD1 = S1.getLeftMostDescendant(Row);
                    SubNodeId LMD2 = S2.getLeftMostDescendant(Col);
                    // COUT << "> " << LMD1 << " " << LMD2 << " " << Row
                    //      << " " << Col << "\n";
                    if (LMD1 == S1.getLeftMostDescendant(LastRow)
                        && LMD2 == S2.getLeftMostDescendant(LastCol)) {
                        // COUT << "ROOT IDS " << S1.RootIds << " "
                        //      << S2.RootIds << " Row " << Row << " Col "
                        //      << Col << "\n";
                        NodeId Id1 = S1.getIdInRoot(Row);
                        NodeId Id2 = S2.getIdInRoot(Col);
                        auto   n1  = DiffImpl.src.getNode(Id1);
                        auto   n2  = DiffImpl.dst.getNode(Id2);
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

  private:
    /// We use a simple cost model for edit actions, which seems good
    /// enough. Simple cost model for edit actions. This seems to make the
    /// matching algorithm perform reasonably well. The values range
    /// between 0 and 1, or infinity if this edit action should always be
    /// avoided.
    double DeletionCost  = 1;
    double InsertionCost = 1;
    double UpdateCost    = 1;

    double getUpdateCost(SubNodeId Id1, SubNodeId Id2) {
        if (!DiffImpl.isMatchingPossible(
                S1.getIdInRoot(Id1), S2.getIdInRoot(Id2))) {
            return std::numeric_limits<double>::max();
        } else {
            if (S1.getNodeValue(Id1) == S2.getNodeValue(Id2)) {
                return 0;
            } else {
                /// IMPLEMENT weighted node update cost that accounts for
                /// the value similarity
                return UpdateCost;
            }
        }
    }

    void computeTreeDist() {
        for (SubNodeId Id1 : S1.KeyRoots) {
            for (SubNodeId Id2 : S2.KeyRoots) {
                computeForestDist(Id1, Id2);
            }
        }
    }

    void computeForestDist(SubNodeId Id1, SubNodeId Id2) {
        assert(Id1 > 0 && Id2 > 0 && "Expecting offsets greater than 0.");
        SubNodeId LMD1         = S1.getLeftMostDescendant(Id1);
        SubNodeId LMD2         = S2.getLeftMostDescendant(Id2);
        ForestDist[LMD1][LMD2] = 0;
        for (SubNodeId D1 = LMD1 + 1; D1 <= Id1; ++D1) {
            ForestDist[D1][LMD2] = ForestDist[D1 - 1][LMD2] + DeletionCost;
            for (SubNodeId D2 = LMD2 + 1; D2 <= Id2; ++D2) {
                ForestDist[LMD1][D2] = ForestDist[LMD1][D2 - 1]
                                     + InsertionCost;
                SubNodeId DLMD1 = S1.getLeftMostDescendant(D1);
                SubNodeId DLMD2 = S2.getLeftMostDescendant(D2);
                if (DLMD1 == LMD1 && DLMD2 == LMD2) {
                    double UpdateCost  = getUpdateCost(D1, D2);
                    ForestDist[D1][D2] = std::min(
                        {ForestDist[D1 - 1][D2] + DeletionCost,
                         ForestDist[D1][D2 - 1] + InsertionCost,
                         ForestDist[D1 - 1][D2 - 1] + UpdateCost});
                    TreeDist[D1][D2] = ForestDist[D1][D2];
                } else {
                    ForestDist[D1][D2] = std::min(
                        {ForestDist[D1 - 1][D2] + DeletionCost,
                         ForestDist[D1][D2 - 1] + InsertionCost,
                         ForestDist[DLMD1][DLMD2] + TreeDist[D1][D2]});
                }
            }
        }
        // std::cout << "---- " << Id1 << " " << Id2 << "\n";
        // for (const auto& r : ForestDist) {
        //     std::cout << r << "\n";
        // }
    }
};

// Compares nodes by their depth.
template <typename Id, typename Val>
struct HeightLess {
    const SyntaxTree<Id, Val>& Tree;
    HeightLess(const SyntaxTree<Id, Val>& Tree) : Tree(Tree) {}
    bool operator()(NodeId Id1, NodeId Id2) const {
        return Tree.getNode(Id1).Height < Tree.getNode(Id2).Height;
    }
};

// Priority queue for nodes, sorted descendingly by their height.
template <typename Id, typename Val>
class PriorityList {
    const SyntaxTree<Id, Val>& Tree;
    HeightLess<Id, Val>        Cmp;
    Vec<NodeId>                Container;
    std::priority_queue<NodeId, Vec<NodeId>, HeightLess<Id, Val>> List;

  public:
    PriorityList(const SyntaxTree<Id, Val>& Tree)
        : Tree(Tree), Cmp(Tree), List(Cmp, Container) {}
    void        push(NodeId id) { List.push(id); }
    Vec<NodeId> pop() {
        int         Max = peekMax();
        Vec<NodeId> Result;
        if (Max == 0) {
            return Result;
        }
        while (peekMax() == Max) {
            Result.push_back(List.top());
            List.pop();
        }
        // TODO this is here to get a stable output, not a good heuristic
        std::sort(Result.begin(), Result.end());
        return Result;
    }


    int peekMax() const {
        if (List.empty()) {
            return 0;
        }
        return Tree.getNode(List.top()).Height;
    }

    /// \brief add all subnodes in the input list
    void open(NodeId id) {
        for (NodeId Subnode : Tree.getNode(id).Subnodes) {
            push(Subnode);
        }
    }
};


template <typename Id, typename Val>
bool ASTDiff<Id, Val>::identical(NodeId Id1, NodeId Id2) const {
    const Node<Id, Val>& N1 = src.getNode(Id1);
    const Node<Id, Val>& N2 = dst.getNode(Id2);
    if (N1.Subnodes.size() != N2.Subnodes.size()
        || !isMatchingPossible(Id1, Id2)
        || src.getNodeValue(Id1) != dst.getNodeValue(Id2)) {
        return false;
    }
    for (size_t id = 0, E = N1.Subnodes.size(); id < E; ++id) {
        if (!identical(N1.Subnodes[id], N2.Subnodes[id])) {
            return false;
        }
    }
    return true;
}


template <typename Id, typename Val>
void ASTDiff<Id, Val>::addOptimalMapping(
    Mapping& M,
    NodeId   Id1,
    NodeId   Id2) const {
    if (std::max(
            src.getNumberOfDescendants(Id1),
            dst.getNumberOfDescendants(Id2))
        > Options.MaxSize) {
        return;
    }
    ZhangShashaMatcher<Id, Val>    Matcher(*this, src, dst, Id1, Id2);
    Vec<std::pair<NodeId, NodeId>> R = Matcher.getMatchingNodes();
    // COUT << R << "\n";
    for (const auto& Tuple : R) {
        NodeId Src = Tuple.first;
        NodeId Dst = Tuple.second;
        if (!M.hasSrc(Src) && !M.hasDst(Dst)) {
            M.link(Src, Dst);
        }
    }
}

template <typename Id, typename Val>
double ASTDiff<Id, Val>::getJaccardSimilarity(
    const Mapping& M,
    NodeId         Id1,
    NodeId         Id2) const {
    int                  CommonDescendants = 0;
    const Node<Id, Val>& N1                = src.getNode(Id1);
    // Count the common descendants, excluding the subtree root.
    for (NodeId Src = Id1 + 1; Src <= N1.RightMostDescendant; ++Src) {
        NodeId Dst = M.getDst(Src);
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
    if (Denominator == 0) {
        return 0;
    }
    return CommonDescendants / Denominator;
}


template <typename Id, typename Val>
NodeId ASTDiff<Id, Val>::findCandidate(const Mapping& M, NodeId Id1)
    const {
    NodeId Candidate;
    double HighestSimilarity = 0.0;
    for (NodeId const& Id2 : dst) {
        if (!isMatchingPossible(Id1, Id2)) {
            continue;
        }
        if (M.hasDst(Id2)) {
            continue;
        }
        double Similarity = getJaccardSimilarity(M, Id1, Id2);
        if (Similarity >= Options.MinSimilarity
            && Similarity > HighestSimilarity) {
            HighestSimilarity = Similarity;
            Candidate         = Id2;
        }
    }
    return Candidate;
}


template <typename Id, typename Val>
void ASTDiff<Id, Val>::matchBottomUp(Mapping& M) const {
    Vec<NodeId> Postorder = getSubtreePostorder<Id, Val>(
        src, src.getRootId());
    // for all nodes in left, if node itself is not matched, but
    // has any children matched
    for (NodeId const& Id1 : Postorder) {
        if (Id1 == src.getRootId() && !M.hasSrc(src.getRootId())
            && !M.hasDst(dst.getRootId())) {
            if (isMatchingPossible(src.getRootId(), dst.getRootId())) {
                M.link(src.getRootId(), dst.getRootId());
                addOptimalMapping(M, src.getRootId(), dst.getRootId());
            }
            break;
        }

        bool                 Matched = M.hasSrc(Id1);
        const Node<Id, Val>& N1      = src.getNode(Id1);

        bool MatchedSubnodes = std::any_of(
            N1.Subnodes.begin(), N1.Subnodes.end(), [&](NodeId Subnode) {
                return M.hasSrc(Subnode);
            });

        //  if it is a valid candidate and matches criteria for
        // minimum number of shares subnodes
        if (Matched || !MatchedSubnodes) {
            continue;
        }
        NodeId Id2 = findCandidate(M, Id1);
        if (Id2.isValid()) {
            // add node to mapping
            M.link(Id1, Id2);
            // if max of number of subnodes does not exceed threshold
            addOptimalMapping(M, Id1, Id2);
        }
    }
}


template <typename Id, typename Val>
Mapping ASTDiff<Id, Val>::matchTopDown() const {
    PriorityList<Id, Val> L1(src);
    PriorityList<Id, Val> L2(dst);
    Mapping               M(src.getSize() + dst.getSize());
    L1.push(src.getRootId());
    L2.push(dst.getRootId());
    int Max1, Max2;
    // until subtree of necessary height hasn't been reached
    while (std::min(Max1 = L1.peekMax(), Max2 = L2.peekMax())
           > Options.MinHeight) {
        // if two top subtrees don't have equal height
        if (Max1 > Max2) {
            // insert all nodes from tallest subforest
            for (NodeId const& id : L1.pop()) {
                L1.open(id);
            }
        } else if (Max2 > Max1) {
            for (NodeId const& id : L2.pop()) {
                L2.open(id);
            }
        } else {
            // otherwise get two subforest of equal height
            Vec<NodeId> H1, H2;
            H1 = L1.pop();
            H2 = L2.pop();
            // for each combination of Therese is these forests
            for (NodeId const& Id1 : H1) {
                for (NodeId const& Id2 : H2) {
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


            for (NodeId const& Id1 : H1) {
                // if there is unmatched forest root in first forest
                if (!M.hasSrc(Id1)) {
                    // insert it's subnodes
                    L1.open(Id1);
                }
            }
            for (NodeId const& Id2 : H2) {
                // do the same for other forest
                if (!M.hasDst(Id2)) {
                    L2.open(Id2);
                }
            }
        }
    }
    return M;
}


template <typename Id, typename Val>
void ASTDiff<Id, Val>::computeChangeKinds(Mapping& M) {
    for (NodeId const& Id1 : src) {
        if (!M.hasSrc(Id1)) {
            src.getMutableNode(Id1).Change = ChangeKind::Delete;
            src.getMutableNode(Id1).Shift -= 1;
        }
    }
    for (NodeId const& Id2 : dst) {
        if (!M.hasDst(Id2)) {
            dst.getMutableNode(Id2).Change = ChangeKind::Insert;
            dst.getMutableNode(Id2).Shift -= 1;
        }
    }
    for (NodeId const& Id1 : src.NodesBfs) {
        NodeId Id2 = M.getDst(Id1);
        if (Id2.isInvalid()) {
            continue;
        }
        if (!haveSameParents(M, Id1, Id2)
            || src.findPositionInParent(Id1, true)
                   != dst.findPositionInParent(Id2, true)) {
            src.getMutableNode(Id1).Shift -= 1;
            dst.getMutableNode(Id2).Shift -= 1;
        }
    }
    for (NodeId const& Id2 : dst.NodesBfs) {
        NodeId Id1 = M.getSrc(Id2);
        if (Id1.isInvalid()) {
            continue;
        }
        Node<Id, Val>& N1 = src.getMutableNode(Id1);
        Node<Id, Val>& N2 = dst.getMutableNode(Id2);
        if (Id1.isInvalid()) {
            continue;
        }
        if (!haveSameParents(M, Id1, Id2)
            || src.findPositionInParent(Id1, true)
                   != dst.findPositionInParent(Id2, true)) {
            N1.Change = N2.Change = ChangeKind::Move;
        }

        if (src.getNodeValue(Id1) != dst.getNodeValue(Id2)) {
            N2.Change = (N1.Change == ChangeKind::Move ? ChangeKind::UpdateMove : ChangeKind::Update);
            N1.Change = N2.Change;
        }
    }
}


template <typename Id, typename Val>
static void printNode(
    QTextStream&         OS,
    SyntaxTree<Id, Val>& Tree,
    NodeId               id,
    Func<Str(CR<Val>)>   ValoStr) {
    if (id.isInvalid()) {
        OS << "None";
    } else {
        OS << "(" << id << "): '";
        OS << Tree.getNode(id).getNodeKind(Tree.getOpts()).value;
        OS << "' '" << ValoStr(Tree.getNodeValue(id)) << "'";
    }
}


template <typename Id, typename Val>
static void printDstChange(
    QTextStream&         OS,
    ASTDiff<Id, Val>&    Diff,
    SyntaxTree<Id, Val>& SrcTree,
    SyntaxTree<Id, Val>& DstTree,
    NodeId               Dst,
    Func<Str(CR<Val>)>   ValoStr) {
    const Node<Id, Val>& DstNode = DstTree.getNode(Dst);
    NodeId               Src     = Diff.getMapped(DstTree, Dst);
    switch (DstNode.Change) {
        case ChangeKind::None: {
            break;
        }
        case ChangeKind::Delete: {
            assert(false && "The destination tree can't have deletions.");
        }
        case ChangeKind::Update: {
            OS << "Update ";
            OS << ValoStr(SrcTree.getNodeValue(Src));
            OS << " to " << ValoStr(DstTree.getNodeValue(Dst));
            break;
        }
        case ChangeKind::Insert:
        case ChangeKind::Move:
        case ChangeKind::UpdateMove: {
            if (DstNode.Change == ChangeKind::Insert) {
                OS << "Insert";
            } else if (DstNode.Change == ChangeKind::Move) {
                OS << "Move";
            } else if (DstNode.Change == ChangeKind::UpdateMove) {
                OS << "Update and Move";
            }
            OS << " [\033[32m";
            OS << ValoStr(DstTree.getNodeValue(Dst));
            OS << "\033[0m] into [\033[31m";
            OS << ValoStr(DstTree.getNodeValue(DstNode.Parent));
            OS << "\033[0m] at " << DstTree.findPositionInParent(Dst);
            break;
        }
    }
}
} // namespace diff
