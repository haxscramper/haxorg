#pragma once

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
    using NodeT = Node<N, K>;
    using IdT   = NodeId<N, K>;

    dod::Store<IdT, NodeT> nodes;

    Vec<IdT> pendingTrees;

    [[nodiscard]] IdT token(CR<NodeT> node) { return nodes.add(node); }
    [[nodiscard]] IdT startTree(CR<NodeT> node) {
        auto res = nodes.add(node);
        pendingTrees.push_back(res);
        return res;
    }

    void endTree() {
        auto start = pendingTrees.pop_back_v();
        nodes.at(start).extend(distance(start, nodes.back()));
    }


    Node<N, K>&    at(IdT id) { return nodes.at(id); }
    CR<Node<N, K>> at(IdT id) const { return nodes.at(id); }


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

    Pair<iterator, iterator> subnodesOf(IdT node) const {
        return {begin(node + 1), end(node + at(node).getExtent())};
    }

    Slice<IdT> allSubnodesOf(IdT node) const {
        return {node + 1, node + at(node).getExtent()};
    }

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

    int size(IdT node) const {
        auto [begin, end] = subnodesOf(node);
        int result        = 0;
        for (; begin != end; ++begin) {
            ++result;
        }
        return result;
    }

    IdT subnode(IdT node, int index) {
        auto [begin, end] = subnodesOf(node);
        for (int i = 0; i < index; ++i) {
            ++begin;
        }
        return *begin;
    }
};
