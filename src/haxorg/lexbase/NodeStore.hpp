#pragma once

#include "Node.hpp"
#include "TokenStore.hpp"

namespace org::parse {

template <typename N, typename K, typename V, typename M>
struct NodeGroup {
    /// \brief Typedef for convenience
    using NodeT = Node<N, K, V, M>;

    /// \brief Typedef for DOD store API operations
    using Id = NodeId<N, K, V, M>;

    hstd::dod::Store<Id, NodeT> nodes;
    TokenGroup<K, V>*           tokens;

    int size() const { return nodes.size(); }

    V const& val(Id id) const {
        LOGIC_ASSERTION_CHECK(tokens != nullptr, "");
        LOGIC_ASSERTION_CHECK(
            at(id).isTerminal(),
            "ID:{} {}({})",
            id.getUnmasked(),
            at(id).kind,
            at(id).value);
        return tokens->at(at(id).getToken()).value;
    }

    NodeGroup(TokenGroup<K, V>* _tokens = nullptr) : tokens(_tokens) {}

    hstd::Vec<Id> pendingTrees;

    int treeDepth() const { return pendingTrees.size(); }

    /// \brief Add token node to the list of nodes
    Id token(NodeT const& node) { return nodes.add(node); }
    /// \brief Create new token node
    Id token(N node, TokenId<K, V> tok) {
        return nodes.add(Node<N, K, V, M>(node, tok));
    }

    /// \brief Add one nonterminal node to the store and push its ID into
    /// the opening stack
    ///
    /// This method is used to create nested tree structure in the manner
    /// that closely maps implicit stack created by AST construction
    /// functions (in parser etc.). The parent node is created using
    /// `startTree()`, subnodes are added to it (in case of linearized AST
    /// representation there is no direct 'add' operation, elements are
    /// just pushed to the subtree) and then tree is 'finalized' using
    /// endTree() call.
    ///
    /// For example of the tree construction see tNode.cpp test, relevant
    /// snippet:
    ///
    /// \snippet tNode.cpp nested tree construction
    Id startTree(NodeT const& node) {
        auto res = nodes.add(node);
        pendingTrees.push_back(res);
        return res;
    }

    /// \brief Pop one pending tree and close it using distance from the
    /// start to the current node position as the full node extent.
    ///
    /// \note Used in conjunction with startTree(), see the documentation
    /// above.
    ///
    /// \returns ID of the closed node
    Id endTree(
        int offset = 0 /// Offset for extending closed subnode
    );

    Id failTree(Node<N, K, V, M> replacement);
    /// \brief Remove all nodes starting from a position `id`
    void removeTail(Id id);

    Node<N, K, V, M> const& lastPending() const {
        return nodes.at(pendingTrees.back());
    }

    /// \brief Return reference to the node *object* at specified ID
    Node<N, K, V, M>&       at(Id id) { return nodes.at(id); }
    Node<N, K, V, M> const& at(Id id) const { return nodes.at(id); }
    Token<K, V>&            at(TokenId<K, V> id) {
        LOGIC_ASSERTION_CHECK(tokens != nullptr, "");
        return tokens->at(id);
    }

    Token<K, V> const& at(TokenId<K, V> id) const {
        LOGIC_ASSERTION_CHECK(tokens != nullptr, "");
        return tokens->at(id);
    }


    class iterator {
      public:
        Id               id;
        NodeGroup const* group;

      public:
        typedef std::forward_iterator_tag iterator_category;
        typedef Id                        value_type;
        typedef Id*                       pointer;
        typedef Id&                       reference;
        typedef std::ptrdiff_t            difference_type;

        iterator(Id _id, NodeGroup const* _group)
            : id(_id), group(_group) {}

        Id operator*() const {
            check();
            return id;
        }

        void check() const {
            LOGIC_ASSERTION_CHECK(
                !id.isNil() && id.getIndex() < group->size(),
                "CHeck node id iterator {} < {}",
                id.getIndex(),
                group->size());
        }

        iterator& operator++() {
            LOGIC_ASSERTION_CHECK(group->nodes.contains(id), "");
            int        extent = group->at(id).getExtent();
            const auto start  = id;
            id                = id + extent + 1;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return this->id != other.id;
        }
    };

    iterator begin(Id start) const;
    iterator end(Id last) const;

    /// \brief Get pair of start/end iterators for traversing content of
    /// the subnodes
    ///
    /// Returns two iterators that can be used in the regular for loop,
    /// ```cpp
    /// auto [begin, end] = group.subnodesOf(root);
    /// for (; begin != end; ++begin) {
    ///     call_(*begin);
    /// }
    /// ```
    hstd::Opt<hstd::Pair<iterator, iterator>> subnodesOf(Id node) const;

    /// \brief Get ID slice over all subnodes that are places 'in' a
    /// specific node. For nodes without any nested elements returns empty
    /// option as `Slice` type is not intended to provde 'zero-size' ranges
    /// -- it always has the first and the last element, in some cases they
    /// might be equal, but that's all
    hstd::Opt<hstd::Slice<Id>> allSubnodesOf(Id node) const;

    /// \brief Get closest left node that contains \arg node in its full
    /// extent.
    Id parent(Id node) const;

    /// \brief Get number of direct subnodes
    int size(Id node) const;

    /// \brief Get id of the Nth subnode
    Id subnode(Id node, int index) const;

    struct TreeReprConf {
        bool withTokenMask  = false;
        bool withTreeMask   = false;
        bool withTreeId     = true;
        bool withSubnodeIdx = true;
        bool flushEach      = false;
        bool withExt        = true;

        enum class WritePos
        {
            LineStart,
            AfterKind,
            LineEnd,
        };

        struct WriteParams {
            hstd::ColStream& os;
            Id               current;
            WritePos         pos;
            hstd::Opt<int>   subnodeIdx;
            int              level;
            hstd::Opt<Id>    parent;
        };

        hstd::Func<void(WriteParams const& params)> customWrite;
    };

    void lispRepr(
        std::ostream&       os,
        Id                  node,
        TreeReprConf const& conf = TreeReprConf()) const;


    void treeRepr(
        hstd::ColStream&    os,
        Id                  node,
        int                 level,
        TreeReprConf const& conf       = TreeReprConf(),
        int                 subnodeIdx = 0,
        hstd::Opt<Id>       parent     = std::nullopt) const;

    std::string treeRepr(
        Id                  node,
        TreeReprConf const& conf = TreeReprConf()) const;
};

} // namespace org::parse
