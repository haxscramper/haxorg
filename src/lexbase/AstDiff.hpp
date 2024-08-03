#pragma once

#include <hstd/system/string_convert.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/system/generator.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Func.hpp>
#include <absl/log/check.h>
#include <hstd/stdlib/ColText.hpp>

#include <iostream>
#include <cassert>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <limits>
#include <functional>


#define COUT std::cout << "[\033[33m" << __LINE__ << "\033[0m] "

namespace diff {
template <int Idx, typename... Args>
void writeIfIndex(std::ostream& os, std::variant<Args...> const& var) {
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
struct NodeIdx {
  private:
    static constexpr int InvalidNodeOffset = -1;

  public:
    int Offset; /// Offset in the postorder iteratio
    inline NodeIdx() : Offset(InvalidNodeOffset) {}
    inline NodeIdx(int Offset) : Offset(Offset) {}

    inline          operator int() const { return Offset; }
    inline NodeIdx& operator++() { return ++Offset, *this; }
    inline NodeIdx& operator--() { return --Offset, *this; }
    /// Support defining iterators on NodeIdx.
    inline NodeIdx& operator*() { return *this; }
    inline bool     isValid() const { return Offset != InvalidNodeOffset; }
    inline bool isInvalid() const { return Offset == InvalidNodeOffset; }

    inline void assertValid(std::string const& msg) const {
        if (isInvalid()) {
            throw std::domain_error(
                "non-valid (-1) node found for " + msg);
        }
    }
};


struct ASTNodeKind {
    int value = 0;
    ASTNodeKind(int kind) : value(kind) {}
    bool operator==(ASTNodeKind const& other) const {
        return value == other.value;
    }
};

struct NodeStore {
    struct Id {
        i64 id = -1;

        template <typename T>
        static Id FromPtr(T const* value) {
            return Id{.id = reinterpret_cast<i64>(value)};
        }

        template <typename T>
        T* ToPtr() {
            return static_cast<T*>(id);
        }

        template <typename T>
        T const* ToPtr() const {
            return reinterpret_cast<T const*>(
                static_cast<std::intptr_t>(id));
        }
    };

    virtual int getSubnodeCount(Id const& id)           = 0;
    virtual Id  getSubnodeAt(Id const& node, int index) = 0;
    virtual Id  getRoot()                               = 0;


    virtual ASTNodeKind getNodeKind(Id const& node) const = 0;
    virtual bool isMatchingAllowed(Id const& src, Id const& dst) const {
        return getNodeKind(src) == getNodeKind(dst);
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

    void link(NodeIdx Src, NodeIdx Dst) {
        SrcToDst[Src] = Dst;
        DstToSrc[Dst] = Src;
    }

    NodeIdx getDst(NodeIdx Src) const { return SrcToDst[Src]; }
    NodeIdx getSrc(NodeIdx Dst) const { return DstToSrc[Dst]; }
    bool    hasSrc(NodeIdx Src) const { return getDst(Src).isValid(); }
    bool    hasDst(NodeIdx Dst) const { return getSrc(Dst).isValid(); }

  private:
    Vec<NodeIdx> SrcToDst;
    Vec<NodeIdx> DstToSrc;
};

enum class ChangeKind
{
    None,
    Delete, ///< (Src): delete node Src.
    Update, ///< (Src, Dst): update the value of node Src to match Dst.
    Insert, ///< (Src, Dst, Pos): insert Src as child of Dst at offset Pos.
    Move,   ///< (Src, Dst, Pos): move Src to be a child of Dst at offset
            ///< Pos.
    UpdateMove ///< Same as Move plus Update.
};

BOOST_DESCRIBE_ENUM(
    ChangeKind,
    None,
    Delete,
    Update,
    Insert,
    Move,
    UpdateMove);


struct Node;

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

    enum class FirstPassKind
    {
        TopDown,
        Greedy,
    };

    FirstPassKind firstPass = FirstPassKind::TopDown;
    Func<bool(const Node& N1, const Node& N2)>   isMatchingAllowed;
    Func<bool(Node const& src, Node const& dst)> areValuesEqual;
};


/// \brief Represents an AST node, alongside some additional information.
///
/// Single node of the original AST
struct Node {
    NodeIdx       Parent              = NodeIdx{};
    NodeIdx       LeftMostDescendant  = NodeIdx{};
    NodeIdx       RightMostDescendant = NodeIdx{};
    int           Depth               = 0;
    int           Height              = 0;
    int           Shift               = 0;
    NodeStore::Id ASTNode             = NodeStore::Id{};
    Vec<NodeIdx>  Subnodes            = {};
    ChangeKind    Change              = ChangeKind::None;
    NodeStore*    store               = nullptr;

    Node(NodeStore* store) : store{store} {}

    ASTNodeKind getNodeKind() const { return store->getNodeKind(ASTNode); }
    bool        isLeaf() const { return Subnodes.empty(); }

    template <typename T>
    T* getStore() const {
        auto res = dynamic_cast<T*>(store);
        CHECK(res != nullptr);
        return res;
    }
};
} // namespace diff

template <>
struct std::formatter<diff::NodeIdx> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const diff::NodeIdx& p, FormatContext& ctx) const {
        return fmt_ctx(p.Offset, ctx);
    }
};


template <>
struct std::formatter<diff::NodeStore::Id> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const diff::NodeStore::Id& p, FormatContext& ctx) const {
        return fmt_ctx(p.id, ctx);
    }
};

template <>
struct std::formatter<diff::Node> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const diff::Node& p, FormatContext& ctx) {
        return std::format(
            "<H: {}, D: {}, S: {}, P: {}, L: {}, R: {}>",
            p.Height,
            p.Depth,
            p.Shift,
            p.Parent,
            p.LeftMostDescendant,
            p.RightMostDescendant);
    }
};


namespace diff {

class SyntaxTree;

Vec<NodeIdx> getSubtreeBfs(const SyntaxTree& Tree, NodeIdx Root);
Vec<NodeIdx> getSubtreePostorder(const SyntaxTree& Tree, NodeIdx Root);


/// SyntaxTree objects represent subtrees of the AST.
///
/// There are only two instances of the SyntaxTree class during comparison
/// - destination and source. Structure is not recursive in tiself -
/// subnodes are determined based on the Node::Subnodes field which
/// explicitly stores list of subnode ids.
class SyntaxTree {
  public:
    SyntaxTree(SyntaxTree&& Other) = default;
    ~SyntaxTree()                  = default;
    using PreorderIterator         = NodeIdx;

    ComparisonOptions const& getOpts() const { return opts; }

  public:
    SyntaxTree(ComparisonOptions const& _opts) {}

    /// Constructs a tree from an AST node using provided accessor
    /// callbacks
    void FromNode(NodeStore* store);
    /// Nodes in preorder.
    Vec<Node>    Nodes;
    Vec<NodeIdx> Leaves;
    /// Maps preorder indices to postorder ones.
    Vec<int>          PostorderIds;
    Vec<NodeIdx>      NodesBfs;
    int               getSize() const { return Nodes.size(); }
    NodeIdx           getRootId() const { return 0; }
    PreorderIterator  begin() const { return getRootId(); }
    PreorderIterator  end() const { return getSize(); }
    ComparisonOptions opts;

    NodeStore::Id getStoreId(NodeIdx idx) const {
        return getNode(idx).ASTNode;
    }

    Node const& getNode(NodeIdx id) const { return Nodes.at(id.Offset); }
    NodeIdx     getParent(NodeIdx id) const { return getNode(id).Parent; }

    struct PathElement {
        /// Parent node to index into -- set to 'invalid' for root nodes
        NodeIdx under;
        /// Position for the `under` node indexing
        int  position;
        bool isRoot() const { return under.isInvalid() && position == -1; }
    };

    Node const& getNode(PathElement const& path) {
        return getNode(getNode(path.under).Subnodes.at(path.position));
    }

    Node& getMutableNode(NodeIdx id) { return Nodes[id]; }

    /// \brief Iterate over all node IDs that are present in the syntax
    /// tree
    generator<NodeIdx> nodeIds() {
        for (int i = 0; i < Nodes.size(); ++i) { co_yield NodeIdx(i); }
    }

    /// \brief Check if the node ID falls in a range of nodes that is
    /// stored in this syntax tree
    bool isValidNodeIdx(NodeIdx id) const {
        return 0 <= id && id < getSize();
    }

    /// \brief Add node value objet to the syntax tree node list
    void addNode(Node& N) { Nodes.push_back(N); }

    int getNumberOfDescendants(NodeIdx id) const {
        return getNode(id).RightMostDescendant - id + 1;
    }

    /// \brief Check if given ID is a subtree of a given root
    bool isInSubtree(NodeIdx id, NodeIdx SubtreeRoot) const {
        return SubtreeRoot <= id
            && id <= getNode(SubtreeRoot).RightMostDescendant;
    }

    /// \brief Get full list of the node's ancestors. Iteration starts with
    /// the current node or it's direct ancestor and moves upwards.
    Vec<NodeIdx> getParentIdChain(
        NodeIdx id,
        bool    withSelf = true /// Include the node in the list
    ) const {
        Vec<NodeIdx> result;

        if (withSelf) { result.push_back(id); }

        NodeIdx parent = getParent(id);
        while (parent.isValid()) {
            result.push_back(parent);
            parent = getParent(parent);
        }
        return result;
    }


    /// \brief Return node ID that uniquely identifes a given node starting
    /// from the root base
    Vec<PathElement> getNodePath(NodeIdx node) const {
        Vec<NodeIdx>     parents = getParentIdChain(node, true);
        Vec<PathElement> result;

        for (int i = 1; i < parents.size(); ++i) {
            result.push_back(PathElement{
                .under    = parents.at(i),
                .position = findPositionInParent(parents[i - 1]),
            });
        }

        result.push_back(PathElement{.under = NodeIdx(), .position = -1});

        std::reverse(result.begin(), result.end());

        return result;
    }

    Vec<NodeStore::Id> getBaseParentIdChain(NodeIdx node, bool withSelf)
        const {
        Vec<NodeStore::Id> result;
        for (auto const& node : getParentIdChain(node, withSelf)) {
            result.push_back(getNode(node).ASTNode);
        }
        return result;
    }

    int findPositionInParent(NodeIdx id, bool Shifted = false) const {
        NodeIdx Parent = getNode(id).Parent;
        if (Parent.isInvalid()) { return 0; }
        const auto& Siblings = getNode(Parent).Subnodes;
        int         Position = 0;
        for (int I = 0, E = Siblings.size(); I < E; ++I) {
            if (Shifted) { Position += getNode(Siblings[I]).Shift; }
            if (Siblings[I] == id) {
                Position += I;
                return Position;
            }
        }

        assert(false && "Node not found in parent's children.");
    }


  private:
    void initTree() {
        setLeftMostDescendants();
        int PostorderId = 0;
        PostorderIds.resize(getSize());
        Func<void(NodeIdx)> PostorderTraverse = [&](NodeIdx id) {
            for (NodeIdx Subnode : getNode(id).Subnodes) {
                PostorderTraverse(Subnode);
            }
            PostorderIds[id] = PostorderId;
            ++PostorderId;
        };
        PostorderTraverse(getRootId());
        NodesBfs = getSubtreeBfs(*this, getRootId());
    }

    void setLeftMostDescendants() {
        for (NodeIdx Leaf : Leaves) {
            getMutableNode(Leaf).LeftMostDescendant = Leaf;
            NodeIdx Parent, Cur = Leaf;
            while ((Parent = getNode(Cur).Parent).isValid()
                   && getNode(Parent).Subnodes[0] == Cur) {
                Cur                                    = Parent;
                getMutableNode(Cur).LeftMostDescendant = Leaf;
            }
        }
    }
};


class ASTDiff {
  public:
    ~ASTDiff() = default;

  public:
    struct Change {
        struct MovePoint {
            /// Insert the node under a specified original tree
            NodeIdx under = NodeIdx{};
            /// Insert the node on specified position
            int position = 0;
            MovePoint() {};
            MovePoint(NodeIdx const& under, int position)
                : under{under}, position{position} {};
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

        NodeIdx  src;
        NodeIdx  dst;
        ASTDiff* diff;
        Data     data;

        Change() {}
        Change(CR<Data> data, ASTDiff* diff, NodeIdx src, NodeIdx dst)
            : src(src), dst(dst), diff(diff), data(data) {}


        // clang-format off
        Vec<NodeIdx> getSrcChain(bool withSelf = true) const { return diff->src.getParentIdChain(src, withSelf); }
        Vec<NodeIdx> getDstChain(bool withSelf = true) const { return diff->src.getParentIdChain(src, withSelf); }
        Vec<SyntaxTree::PathElement> getSrcPath() const { return diff->src.getNodePath(src); }
        Vec<SyntaxTree::PathElement> getDstPath() const { return diff->dst.getNodePath(dst); }
        Vec<NodeStore::Id> getBaseSrcChain(bool withSelf = true) const { return diff->src.getBaseParentIdChain(src, withSelf); }
        Vec<NodeStore::Id> getBaseDstChain(bool withSelf = true) const { return diff->dst.getBaseParentIdChain(dst, withSelf); }
        // clang-format on

        template <typename Store>
        Store::value_type getSrcValue(Store* store) const {
            CHECK(src.isValid());
            return store->getNodeValue(diff->src.getStoreId(src));
        }

        template <typename Store>
        Store::value_type getDstValue(Store* store) const {
            CHECK(dst.isValid());
            return store->getNodeValue(diff->dst.getStoreId(dst));
        }
    };


    SyntaxTree& src;
    SyntaxTree& dst;

    Mapping TheMapping;
    ASTDiff(
        SyntaxTree&              src,
        SyntaxTree&              dst,
        const ComparisonOptions& Options)
        : src(src), dst(dst), Options(Options) {
        computeMapping();
        computeChangeKinds(TheMapping);
    }

    Change getChange(NodeIdx srcNode, NodeIdx dstNode, bool fromDst) {
        Change result;

        Node const& node = fromDst ? dst.getNode(dstNode)
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
                    .from   = Change::MovePoint{
                         src.getNode(srcNode).Parent,
                         src.findPositionInParent(srcNode, true),
                    },
                    .to     = Change::MovePoint{
                        dst.getNode(dstNode).Parent,
                        dst.findPositionInParent(dstNode, true),
                    },
                };
                break;
            }

            case ChangeKind::Insert: {
                result.data = typename Change::Insert{
                    .to = Change::MovePoint{
                        node.Parent,
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

    Change getChangeFromDst(NodeIdx dst) {
        return getChange(TheMapping.getSrc(dst), dst, true);
    }

    Change getChangeFromSrc(NodeIdx src) {
        return getChange(src, TheMapping.getDst(src), false);
    }

    /// \brief Get list of all changes for a diff
    Vec<Change> getAllChanges(
        bool skipNone = true /// Skip 'none' changes -- direct mappings
                             /// with no modifications
    ) {
        Vec<Change> result;
        for (NodeIdx const& dstNode : dst.nodeIds()) {
            if (!skipNone
                || this->dst.getNode(dstNode).Change != ChangeKind::None) {
                result.push_back(getChangeFromDst(dstNode));
            }
        }

        for (NodeIdx const& srcNode : src.nodeIds()) {
            if (this->src.getNode(srcNode).Change == ChangeKind::Delete) {
                result.push_back(getChangeFromSrc(srcNode));
            }
        }

        return result;
    }

    /// \brief Matches nodes one-by-one based on their similarity.
    void computeMapping() {
        using Pass = ComparisonOptions::FirstPassKind;
        switch (Options.firstPass) {
            case Pass::TopDown: TheMapping = matchTopDown(); break;
            case Pass::Greedy: TheMapping = greedyMatchTopDown(); break;
        }

        if (Options.StopAfterTopDown) {
            return;
        } else {
            matchBottomUp(TheMapping);
        }
    }

    /// \brief Compute Change for each node based on similarity.
    void computeChangeKinds(Mapping& M);

    /// \brief Returns the ID of the node that is mapped to the given node
    /// in SourceTree.
    NodeIdx getMapped(const SyntaxTree& Tree, NodeIdx id) const {
        if (&Tree == &src) { return TheMapping.getDst(id); }
        assert(&Tree == &dst && "Invalid tree.");
        return TheMapping.getSrc(id);
    }

  private:
    /// \brief Returns true if the two subtrees are isomorphic to each
    /// other.
    bool identical(NodeIdx Id1, NodeIdx Id2) const;

    /// \brief Returns false if the nodes must not be mached.
    bool isMatchingPossible(NodeIdx Id1, NodeIdx Id2) const {
        return Options.isMatchingAllowed(
            src.getNode(Id1), dst.getNode(Id2));
    }

    /// \brief Returns true if the nodes' parents are matched.
    bool haveSameParents(const Mapping& M, NodeIdx Id1, NodeIdx Id2)
        const {
        NodeIdx P1 = src.getNode(Id1).Parent;
        NodeIdx P2 = dst.getNode(Id2).Parent;
        return (P1.isInvalid() && P2.isInvalid())
            || (P1.isValid() && P2.isValid() && M.getDst(P1) == P2);
    }

    /// \brief Uses an optimal albeit slow algorithm to compute a mapping
    /// between two subtrees, but only if both have fewer nodes than
    /// MaxSize.
    void addOptimalMapping(Mapping& M, NodeIdx Id1, NodeIdx Id2) const;
    /// \brief Computes the ratio of common descendants between the two
    /// nodes. Descendants are only considered to be equal when they are
    /// mapped in M.
    double getJaccardSimilarity(const Mapping& M, NodeIdx Id1, NodeIdx Id2)
        const;
    /// \brief Returns the node that has the highest degree of similarity.
    NodeIdx findCandidate(const Mapping& M, NodeIdx Id1) const;
    /// \brief Returns a mapping of identical subtrees.
    Mapping matchTopDown() const;
    Mapping greedyMatchTopDown() const;

    /// \brief Tries to match any yet unmapped nodes, in a bottom-up
    /// fashion.
    void                     matchBottomUp(Mapping& M) const;
    const ComparisonOptions& Options;
    friend class ZhangShashaMatcher;
};


/// \brief Identifies a node in a subtree by its postorder offset, starting
/// at 1.
struct SubNodeIdx {
    int Id = 0;
    explicit SubNodeIdx(int Id) : Id(Id) {}
    explicit SubNodeIdx() = default;
    operator int() const { return Id; }
    SubNodeIdx& operator++() { return ++Id, *this; }
    SubNodeIdx& operator--() { return --Id, *this; }
    SubNodeIdx  operator+(int Other) const {
        return SubNodeIdx(Id + Other);
    }
};


class Subtree {
  public:
    /// The parent tree.
    const SyntaxTree& Tree;
    /// Maps SubNodeIdxs to original ids.
    Vec<NodeIdx> RootIds;
    /// Maps subtree nodes to their leftmost descendants wtihin the
    /// subtree.
    Vec<SubNodeIdx> LeftMostDescendants;

  public:
    Vec<SubNodeIdx> KeyRoots;
    Subtree(const SyntaxTree& Tree, NodeIdx SubtreeRoot) : Tree(Tree) {
        RootIds       = getSubtreePostorder(Tree, SubtreeRoot);
        int NumLeaves = setLeftMostDescendants();
        computeKeyRoots(NumLeaves);
    }

    int getSize() const { return RootIds.size(); }

    NodeIdx getIdInRoot(SubNodeIdx id) const {
        assert(id > 0 && id <= getSize() && "Invalid subtree node index.");
        return RootIds[id - 1];
    }

    const Node& getNode(SubNodeIdx id) const {
        return Tree.getNode(getIdInRoot(id));
    }

    SubNodeIdx getLeftMostDescendant(SubNodeIdx id) const {
        assert(id > 0 && id <= getSize() && "Invalid subtree node index.");
        return LeftMostDescendants[id - 1];
    }
    /// Returns the postorder index of the leftmost descendant in the
    /// subtree.
    NodeIdx getPostorderOffset() const {
        return Tree.PostorderIds[getIdInRoot(SubNodeIdx(1))];
    }

  private:
    /// Returns the number of leafs in the subtree.
    int setLeftMostDescendants() {
        int NumLeaves = 0;
        LeftMostDescendants.resize(getSize());
        for (int I = 0; I < getSize(); ++I) {
            SubNodeIdx  SI(I + 1);
            const Node& N = getNode(SI);
            NumLeaves += N.isLeaf();
            assert(
                I == Tree.PostorderIds[getIdInRoot(SI)] -
                         getPostorderOffset() &&
                "Postorder traversal in subtree should correspond to "
                "traversal in the root tree by a constant offset.");
            LeftMostDescendants[I] = SubNodeIdx(
                Tree.PostorderIds[N.LeftMostDescendant]
                - getPostorderOffset());
        }
        return NumLeaves;
    }

    void computeKeyRoots(int Leaves) {
        KeyRoots.resize(Leaves);
        std::unordered_set<int> Visited;
        int                     K = Leaves - 1;
        for (SubNodeIdx I(getSize()); I > 0; --I) {
            SubNodeIdx LeftDesc = getLeftMostDescendant(I);
            if (0 < Visited.count(LeftDesc)) { continue; }
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
class ZhangShashaMatcher {
    const ASTDiff&   DiffImpl;
    Subtree          S1;
    Subtree          S2;
    Vec<Vec<double>> TreeDist, ForestDist;

  public:
    ZhangShashaMatcher(
        const ASTDiff&    DiffImpl,
        const SyntaxTree& src,
        const SyntaxTree& dst,
        NodeIdx           Id1,
        NodeIdx           Id2)
        : DiffImpl(DiffImpl), S1(src, Id1), S2(dst, Id2) {

        TreeDist.resize(size_t(S1.getSize()) + 1);
        ForestDist.resize(size_t(S1.getSize()) + 1);

        for (int I = 0, E = S1.getSize() + 1; I < E; ++I) {
            TreeDist[I].resize(size_t(S2.getSize()) + 1);
            ForestDist[I].resize(size_t(S2.getSize()) + 1);
        }
    }

    Vec<std::pair<NodeIdx, NodeIdx>> getMatchingNodes();

  private:
    /// We use a simple cost model for edit actions, which seems good
    /// enough. Simple cost model for edit actions. This seems to make the
    /// matching algorithm perform reasonably well. The values range
    /// between 0 and 1, or infinity if this edit action should always be
    /// avoided.
    double DeletionCost  = 1;
    double InsertionCost = 1;
    double UpdateCost    = 1;

    double getUpdateCost(
        ComparisonOptions const& opts,
        SubNodeIdx               Id1,
        SubNodeIdx               Id2) {
        if (!DiffImpl.isMatchingPossible(
                S1.getIdInRoot(Id1), S2.getIdInRoot(Id2))) {
            return std::numeric_limits<double>::max();
        } else {
            if (opts.areValuesEqual(S1.getNode(Id1), S2.getNode(Id2))) {
                return 0;
            } else {
                /// IMPLEMENT weighted node update cost that accounts for
                /// the value similarity
                return UpdateCost;
            }
        }
    }

    void computeTreeDist() {
        for (SubNodeIdx Id1 : S1.KeyRoots) {
            for (SubNodeIdx Id2 : S2.KeyRoots) {
                computeForestDist(Id1, Id2);
            }
        }
    }

    void computeForestDist(SubNodeIdx Id1, SubNodeIdx Id2);
};

// Compares nodes by their depth.
struct HeightLess {
    const SyntaxTree& Tree;
    HeightLess(const SyntaxTree& Tree) : Tree(Tree) {}
    bool operator()(NodeIdx Id1, NodeIdx Id2) const {
        return Tree.getNode(Id1).Height < Tree.getNode(Id2).Height;
    }
};

// Priority queue for nodes, sorted descendingly by their height.
class PriorityList {
    const SyntaxTree&                                      Tree;
    HeightLess                                             Cmp;
    Vec<NodeIdx>                                           Container;
    std::priority_queue<NodeIdx, Vec<NodeIdx>, HeightLess> List;

  public:
    PriorityList(const SyntaxTree& Tree)
        : Tree(Tree), Cmp(Tree), List(Cmp, Container) {}
    void         push(NodeIdx id) { List.push(id); }
    Vec<NodeIdx> pop() {
        int          Max = peekMax();
        Vec<NodeIdx> Result;
        if (Max == 0) { return Result; }
        while (peekMax() == Max) {
            Result.push_back(List.top());
            List.pop();
        }
        // TODO this is here to get a stable output, not a good heuristic
        std::sort(Result.begin(), Result.end());
        return Result;
    }


    int peekMax() const {
        if (List.empty()) { return 0; }
        return Tree.getNode(List.top()).Height;
    }

    /// \brief add all subnodes in the input list
    void open(NodeIdx id) {
        for (NodeIdx Subnode : Tree.getNode(id).Subnodes) {
            push(Subnode);
        }
    }
};


void printNode(
    ColStream&                       os,
    SyntaxTree const&                Tree,
    NodeIdx                          id,
    Func<ColText(CR<NodeStore::Id>)> ValoStr);


void printDstChange(
    ColStream&                       OS,
    ASTDiff const&                   Diff,
    SyntaxTree const&                SrcTree,
    SyntaxTree const&                DstTree,
    NodeIdx                          Dst,
    Func<ColText(CR<NodeStore::Id>)> FormatSrcTreeValue,
    Func<ColText(CR<NodeStore::Id>)> FormatDstTreeValue);

void printMapping(
    ColStream&                       os,
    ASTDiff const&                   Diff,
    SyntaxTree const&                SrcTree,
    SyntaxTree const&                DstTree,
    Func<ColText(CR<NodeStore::Id>)> FormatSrcTreeValue,
    Func<ColText(CR<NodeStore::Id>)> FormatDstTreeValue);
} // namespace diff
