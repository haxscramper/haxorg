#pragma once

#include <hstd/stdlib/Str.hpp>

#include <hstd/stdlib/dod_base.hpp>

#include <lexbase/Token.hpp>

#include <variant>

template <typename N, typename K>
struct Node;

template <
    typename N,
    typename K,
    typename IdBase   = u64,
    typename MaskType = IdBase>
struct [[nodiscard]] NodeId
    : dod::Id<IdBase, MaskType, std::integral_constant<MaskType, 16>> {
    using value_type = Node<N, K>;
    static auto Nil() -> NodeId { return FromValue(0); };
    static auto FromValue(IdBase arg) -> NodeId {
        NodeId<N, K> res{IdBase{}};
        res.setValue(arg);
        return res;
    }

    auto operator==(NodeId<N, K, IdBase> other) const -> bool {
        return this->getValue() == other.getValue();
    }

    MaskType getStoreIdx() const { return this->getMask(); }

    explicit NodeId(IdBase arg)
        : dod::Id<IdBase, MaskType, std::integral_constant<MaskType, 16>>(
            arg) {}
};

template <typename N, typename K>
std::ostream& operator<<(std::ostream& os, NodeId<N, K> const& value) {
    return value.streamTo(
        os, std::string("NodeId<") + demangle(typeid(N).name()) + ">");
}

template <typename N, typename K>
struct Node {
    N                             kind;
    std::variant<int, TokenId<K>> value;

    Node(N _kind, CR<TokenId<K>> token) : kind(_kind), value(token) {}
    Node(N _kind, int extent = 0) : kind(_kind), value(extent) {}

    bool isTerminal() const {
        return std::holds_alternative<TokenId<K>>(value);
    }

    bool isNonTerminal() const {
        return std::holds_alternative<int>(value);
    }

    void extend(int extent) {
        assert(isNonTerminal());
        value = extent;
    }

    int getExtent() const {
        if (isTerminal()) {
            return 0;
        } else {
            return std::get<int>(value);
        }
    }

    TokenId<K> getToken() const { return std::get<TokenId<K>>(value); }

    Slice<NodeId<N, K>> nestedNodes(NodeId<N, K> selfId) const {
        assert(isNonTerminal());
        return slice(selfId + 1, selfId + getExtent());
    }
};

template <typename N, typename K>
struct NodeGroup {
    /// \brief Typedef for convenience
    using NodeT = Node<N, K>;
    /// \brief Typedef for convenience
    using IdT = NodeId<N, K>;

    /// \brief Typedef for DOD store API operations
    using id_type = NodeId<N, K>;

    dod::Store<IdT, NodeT> nodes;
    TokenGroup<K>*         tokens;

    NodeGroup(TokenGroup<K>* _tokens) : tokens(_tokens) {}

    Vec<IdT> pendingTrees;

    /// \brief Add token node to the list of nodes
    [[nodiscard]] IdT token(CR<NodeT> node) { return nodes.add(node); }
    /// \brief Create new token node
    [[nodiscard]] IdT token(N node, TokenId<K> tok) {
        return nodes.add(Node<N, K>(node, tok));
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
    [[nodiscard]] IdT startTree(CR<NodeT> node) {
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
    IdT endTree(
        int offset = 0 /// Offset for extending closed subnode
    ) {
        auto start = pendingTrees.pop_back_v();
        nodes.at(start).extend(distance(start, nodes.back()) + offset);
        return start;
    }

    /// \brief Return reference to the node *object* at specified ID
    Node<N, K>&    at(IdT id) { return nodes.at(id); }
    CR<Node<N, K>> at(IdT id) const { return nodes.at(id); }
    Token<K>&      at(TokenId<K> id) { return tokens->at(id); }
    CR<Token<K>>   at(TokenId<K> id) const { return tokens->at(id); }


    class iterator {
      private:
        IdT           id;
        CP<NodeGroup> group;

      public:
        typedef std::forward_iterator_tag iterator_category;
        typedef IdT                       value_type;
        typedef IdT*                      pointer;
        typedef IdT&                      reference;
        typedef std::ptrdiff_t            difference_type;

        iterator(IdT _id, CP<NodeGroup> _group) : id(_id), group(_group) {}

        IdT operator*() { return id; }

        iterator& operator++() {
            id = id + group->at(id).getExtent() + 1;
            return *this;
        }

        bool operator!=(const iterator& other) {
            return this->id != other.id;
        }
    };

    iterator begin(IdT start) const { return iterator(start, this); }
    iterator end(IdT last) const { return iterator(++last, this); }

    /// \brief Get pair of start/end iterators for traversing content of
    /// the subnodes
    Pair<iterator, iterator> subnodesOf(IdT node) const {
        return {begin(node + 1), end(node + at(node).getExtent())};
    }

    /// \brief Get ID slice over all subnodes that are places 'in' a
    /// specific node.
    Slice<IdT> allSubnodesOf(IdT node) const {
        return {node + 1, node + at(node).getExtent()};
    }

    /// \brief Get closest left node that contains \arg node in its full
    /// extent.
    IdT parent(IdT node) const {
        IdT parent = node;
        --parent;
        while (!parent.isNil()) {
            auto extent = allSubnodesOf(parent);
            if (extent.contains(node)) {
                return parent;
            } else {
                --parent;
            }
        }

        return IdT::Nil();
    }

    /// \brief Get number of direct subnodes
    int size(IdT node) const {
        auto [begin, end] = subnodesOf(node);
        int result        = 0;
        for (; begin != end; ++begin) {
            ++result;
        }
        return result;
    }

    /// \brief Get id of the Nth subnode
    IdT subnode(IdT node, int index) {
        auto [begin, end] = subnodesOf(node);
        for (int i = 0; i < index; ++i) {
            ++begin;
        }
        return *begin;
    }

    struct TreeReprConf {
        bool        withTokenMask = false;
        bool        withTreeMask  = false;
        const char* fullBase      = nullptr;
    };

    void treeRepr(
        std::ostream&    os,
        IdT              node,
        int              level,
        CR<TreeReprConf> conf = TreeReprConf()) {
        if (conf.withTreeMask) {
            os << right_aligned(to_string(node.getMask()), 2) << ":";
        }

        os << left_aligned(to_string(node.getUnmasked()), 4) << " ";
        os << Str::repeat("  ", level);
        os << to_string(at(node).kind);
        if (at(node).isTerminal()) {
            auto tok = at(node).getToken();
            os << " #";
            tok.streamTo(os, "", conf.withTokenMask);
            os << " ";
            os << at(tok);
            if (conf.fullBase != nullptr && at(tok).hasData()) {
                os << " ";
                auto start = std::distance(
                    conf.fullBase, at(tok).text.data());
                os << start;
                os << "..";
                os << start + at(tok).text.size() - 1;
            }
        } else {
            auto [begin, end] = subnodesOf(node);
            for (; begin != end; ++begin) {
                os << "\n";
                treeRepr(os, *begin, level + 1, conf);
            }
        }
    }
};
