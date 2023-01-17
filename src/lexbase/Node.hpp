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

    int getExtent() const { return std::get<int>(value); }

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

    std::span<Token<K>> at(HSlice<IdT, IdT> slice) {
        assert(slice.first.getStoreIdx() == slice.last.getStoreIdx());
        nodes.at(slice(slice.first.getIndex(), slice.last.getIndex()));
    }

    Node<N, K>& at(IdT id) { return nodes.at(id); }

    NodeT& subnode(IdT id, int index) { auto& node = nodes.at(id); }

    class iterator {
      private:
        IdT        id;
        NodeGroup* group;

      public:
        typedef std::forward_iterator_tag iterator_category;
        typedef IdT                       value_type;
        typedef IdT*                      pointer;
        typedef IdT&                      reference;
        typedef std::ptrdiff_t            difference_type;

        iterator(IdT _id, NodeGroup* _group) : id(_id), group(_group) {}

        IdT operator*() { return id; }

        iterator& operator++() {
            ++id;
            return *this;
        }

        bool operator!=(const iterator& other) {
            return this->id != other.id;
        }
    };

    iterator begin(IdT start) { return iterator(start, this); }
    iterator end(IdT last) { return iterator(++last, this); }
};
