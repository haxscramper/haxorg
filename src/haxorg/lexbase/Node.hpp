#pragma once

#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Func.hpp>

#include <hstd/stdlib/dod_base.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <filesystem>
#include <absl/log/check.h>

#include <haxorg/lexbase/Token.hpp>
#include <format>

#include <variant>
#include <absl/log/check.h>

template <typename N, typename K, typename V>
struct Node;

template <
    typename N,
    typename K,
    typename V,
    typename IdBase   = u64,
    typename MaskType = IdBase>
struct [[nodiscard]] NodeId
    : dod::Id<IdBase, MaskType, std::integral_constant<MaskType, 16>> {
    using value_type = Node<N, K, V>;
    static auto Nil() -> NodeId { return FromValue(0); };
    static auto FromValue(IdBase arg) -> NodeId {
        NodeId<N, K, V> res{IdBase{}};
        res.setValue(arg);
        return res;
    }

    auto operator==(NodeId<N, K, V, IdBase> other) const -> bool {
        return this->getValue() == other.getValue();
    }

    MaskType getStoreIdx() const { return this->getMask(); }

    explicit NodeId(IdBase arg)
        : dod::Id<IdBase, MaskType, std::integral_constant<MaskType, 16>>(
              arg) {}
};


template <typename N, typename K, typename IdBase, typename MaskType>
struct value_domain<NodeId<N, K, IdBase, MaskType>> {
    using ID = NodeId<N, K, IdBase, MaskType>;
    static ID succ(ID id) {
        ++id;
        return id;
    }
};


template <typename N, typename K, typename V>
struct std::formatter<NodeId<N, K, V>> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        const NodeId<N, K, V>& p,
        FormatContext&         ctx) const {
        std::formatter<std::string> fmt;
        return fmt.format(
            p.format(
                std::format("NodeId<{}>", demangle(typeid(N).name()))),
            ctx);
    }
};


template <>
struct std::formatter<std::monostate> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        const std::monostate& p,
        FormatContext&        ctx) const {
        std::formatter<std::string> fmt;
        return fmt_ctx("<std::monostate>", ctx);
    }
};

template <typename N, typename K, typename V>
struct Node {
    N                                                kind;
    std::variant<int, TokenId<K, V>, std::monostate> value;

    Node(N _kind, CR<TokenId<K, V>> token) : kind(_kind), value(token) {}
    Node(N _kind, int extent = 0) : kind(_kind), value(extent) {}
    Node(N _kind, std::monostate mono) : kind(_kind), value(mono) {}

    static inline Node Mono(N _kind) {
        return Node(_kind, std::monostate());
    }

    bool isMono() const {
        return std::holds_alternative<std::monostate>(value);
    }

    bool isTerminal() const {
        return std::holds_alternative<TokenId<K, V>>(value);
    }

    bool isNonTerminal() const {
        return std::holds_alternative<int>(value);
    }

    void extend(int extent) {
        CHECK(isNonTerminal());
        CHECK(0 <= extent);
        value = extent;
    }


    /// \brief Get full size of the node, including itself and nested
    /// content.
    int getFullSize() const {
        if (isTerminal() || isMono()) {
            return 1;
        } else {
            return std::get<int>(value) + 1;
        }
    }

    /// \brief Return number of subnodes. Terminal/mono nodes return 0.
    int getExtent() const {
        if (isTerminal() || isMono()) {
            return 0;
        } else {
            return std::get<int>(value);
        }
    }

    /// \brief Return token value for the terminal node
    TokenId<K, V> getToken() const {
        return std::get<TokenId<K, V>>(value);
    }

    /// \brief Check if the *non-terminal* node has zero extent.
    /// Terminal/Mono nodes return 'true'.
    bool isEmpty() const { return isNonTerminal() && getExtent() == 0; }

    /// \brief Return inclusive slice of all subnodes. NOTE: Because the
    /// `slice<T>()` is always inclusive, this function does not support
    /// returning empty list directly and instead outputs a nullopt value.
    Opt<Slice<NodeId<N, K, V>>> nestedNodes(NodeId<N, K, V> selfId) const {
        CHECK(isNonTerminal());
        if (isEmpty()) {
            return std::nullopt;
        } else {
            return slice(selfId + 1, selfId + getExtent());
        }
    }

    bool operator==(CR<Node<N, K, V>> other) const {
        if (isTerminal() == other.isTerminal()) {
            return (this->kind == other.kind)
                && (this->value == other.value);
        } else if (isMono() == other.isMono()) {
            return this->kind == other.kind;
        } else {
            return false;
        }
    }
};

template <typename N, typename K, typename V>
struct NodeGroup {
    /// \brief Typedef for convenience
    using NodeT = Node<N, K, V>;

    /// \brief Typedef for DOD store API operations
    using Id = NodeId<N, K, V>;

    dod::Store<Id, NodeT> nodes;
    TokenGroup<K, V>*     tokens;

    int size() const { return nodes.size(); }

    V const& val(Id id) const {
        CHECK(notNil(tokens));
        CHECK(at(id).isTerminal()) << fmt(
            "ID:{} {}({})", id.getUnmasked(), at(id).kind, at(id).value);
        return tokens->at(at(id).getToken()).value;
    }

    NodeGroup(TokenGroup<K, V>* _tokens = nullptr) : tokens(_tokens) {}

    Vec<Id> pendingTrees;

    int treeDepth() const { return pendingTrees.size(); }

    /// \brief Add token node to the list of nodes
    [[nodiscard]] Id token(CR<NodeT> node) { return nodes.add(node); }
    /// \brief Create new token node
    [[nodiscard]] Id token(N node, TokenId<K, V> tok) {
        return nodes.add(Node<N, K, V>(node, tok));
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
    [[nodiscard]] Id startTree(CR<NodeT> node) {
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

    Id   failTree(Node<N, K, V> replacement);
    /// \brief Remove all nodes starting from a position `id`
    void removeTail(Id id);

    CR<Node<N, K, V>> lastPending() const {
        return nodes.at(pendingTrees.back());
    }

    /// \brief Return reference to the node *object* at specified ID
    Node<N, K, V>&    at(Id id) { return nodes.at(id); }
    CR<Node<N, K, V>> at(Id id) const { return nodes.at(id); }
    Token<K, V>&      at(TokenId<K, V> id) {
        assert(notNil(tokens));
        return tokens->at(id);
    }

    CR<Token<K, V>> at(TokenId<K, V> id) const {
        assert(notNil(tokens));
        return tokens->at(id);
    }


    class iterator {
      public:
        Id            id;
        CP<NodeGroup> group;

      public:
        typedef std::forward_iterator_tag iterator_category;
        typedef Id                        value_type;
        typedef Id*                       pointer;
        typedef Id&                       reference;
        typedef std::ptrdiff_t            difference_type;

        iterator(Id _id, CP<NodeGroup> _group) : id(_id), group(_group) {}

        Id operator*() const {
            check();
            return id;
        }

        void check() const {
            CHECK(!id.isNil() && id.getIndex() < group->size())
                << "Check node id iterator"
                << ("$# < $#"
                    % to_string_vec(id.getIndex(), group->size()));
        }

        iterator& operator++() {
            CHECK(group->nodes.contains(id));
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
    Opt<Pair<iterator, iterator>> subnodesOf(Id node) const;

    /// \brief Get ID slice over all subnodes that are places 'in' a
    /// specific node. For nodes without any nested elements returns empty
    /// option as `Slice` type is not intended to provde 'zero-size' ranges
    /// -- it always has the first and the last element, in some cases they
    /// might be equal, but that's all
    Opt<Slice<Id>> allSubnodesOf(Id node) const;

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
            ColStream& os;
            Id         current;
            WritePos   pos;
            Opt<int>   subnodeIdx;
            int        level;
            Opt<Id>    parent;
        };

        Func<void(WriteParams const& params)> customWrite;
    };

    void lispRepr(
        std::ostream&    os,
        Id               node,
        CR<TreeReprConf> conf = TreeReprConf()) const;


    void treeRepr(
        ColStream&       os,
        Id               node,
        int              level,
        CR<TreeReprConf> conf       = TreeReprConf(),
        int              subnodeIdx = 0,
        Opt<Id>          parent     = std::nullopt) const;

    std::string treeRepr(Id node, CR<TreeReprConf> conf = TreeReprConf())
        const;
};


template <typename N, typename K, typename V>
struct std::formatter<Node<N, K, V>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const Node<N, K, V>& p, FormatContext& ctx) const {
        fmt_ctx("{", ctx);
        fmt_ctx(p.kind, ctx);
        if (p.isTerminal()) {
            fmt_ctx(p.getToken(), ctx);
        } else {
            fmt_ctx(p.getExtent(), ctx);
        }

        return fmt_ctx("}", ctx);
    }
};


/// \brief Node adapter for more convenient access operations on the tree
template <typename N, typename K, typename V>
struct NodeAdapter {
    NodeGroup<N, K, V> const* group;
    NodeId<N, K, V>           id;

    N    getKind() const { return group->at(id).kind; }
    bool empty() const { return size() == 0; }
    int  size() const { return group->size(id); }
    /// \brief Check if node adapter is default-constructed and does not
    /// contain pointers to the underlying content.
    bool isNil() const {
        return group == nullptr && id == NodeId<N, K, V>::Nil();
    }

    V const& val() const { return group->val(id); }
    N        kind() const { return group->at(id).kind; }
    bool     isTerminal() const { return group->at(id).isTerminal(); }
    bool     isMono() const { return group->at(id).isMono(); }
    bool isNonTerminal() const { return group->at(id).isNonTerminal(); }

    CR<Node<N, K, V>> get() const { return group->at(id); }


    NodeAdapter<N, K, V>(
        NodeGroup<N, K, V> const* group,
        NodeId<N, K, V>           id)
        : group(group), id(id) {
        CHECK(group->nodes.contains(id));
    }

    NodeAdapter() : group(nullptr), id(NodeId<N, K, V>::Nil()) {}

    // FIXME temporary workaround until I figure out how to properly fix
    // invalid index genenerated by the tree sweep in parser in certain
    // cases. At the moment it is not fully clear what is causing creation
    // of a separate node group.
    bool isValid() const {
        return !id.isNil() && id.getIndex() < group->size();
    }

    NodeAdapter<N, K, V> at(int index) const {
        return {group, group->subnode(id, index)};
    }

    NodeAdapter<N, K, V> operator[](int index) const {
        return {group, group->subnode(id, index)};
    }


    void treeRepr(
        ColStream&                                    os,
        int                                           level = 0,
        CR<typename NodeGroup<N, K, V>::TreeReprConf> conf =
            typename NodeGroup<N, K, V>::TreeReprConf()) const {
        group->treeRepr(os, id, level, conf);
    }

    std::string treeRepr(bool colored = true) const {
        std::stringstream buffer;
        ColStream         text{buffer};
        text.colored = colored;
        treeRepr(text);
        return buffer.str();
    }

    generator<NodeAdapter<N, K, V>> items() {
        for (int i = 0; i < group->size(id); ++i) {
            co_yield this->operator[](i);
        }
    }

    template <typename H, typename L>
    Vec<NodeAdapter<N, K, V>> at(HSlice<H, L> range) {
        Vec<NodeAdapter<N, K, V>> result;
        const auto [start, end] = getSpan(group->size(id), range, true);
        for (const auto& i : slice(start, end)) {
            result.push_back(this->operator[](i));
        }
        return result;
    }

    class iterator {
      private:
        typename NodeGroup<N, K, V>::iterator iter;

      public:
        typedef std::forward_iterator_tag iterator_category;
        typedef NodeAdapter<N, K, V>      value_type;
        typedef NodeAdapter<N, K, V>*     pointer;
        typedef NodeAdapter<N, K, V>&     reference;
        typedef std::ptrdiff_t            difference_type;

        iterator(typename NodeGroup<N, K, V>::iterator iter)
            : iter(iter) {}

        NodeAdapter<N, K, V> operator*() const {
            return NodeAdapter<N, K, V>(iter.group, iter.id);
        }

        iterator& operator++() {
            // increment current iterator state
            ++iter;
            return *this;
        }

        bool operator!=(const iterator& other) {
            // implement iterator inequality comparison
            return this->iter != other.iter;
        }
    };

    iterator begin() {
        if ((id + 1).getIndex() < group->size()) {
            return iterator(group->begin(id + 1));
        } else {
            return end();
        }
    }

    iterator end() {
        return iterator(group->end(id + group->at(id).getExtent()));
    }

    iterator begin() const {
        if ((id + 1).getIndex() < group->size()) {
            return iterator(group->begin(id + 1));
        } else {
            return end();
        }
    }

    iterator end() const {
        return iterator(group->end(id + group->at(id).getExtent()));
    }
};
