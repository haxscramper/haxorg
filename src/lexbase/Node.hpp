#pragma once

#include <hstd/stdlib/dod_base.hpp>
#include <lexbase/Token.hpp>
#include <variant>

template <typename K>
struct Node;

template <typename N, typename IdBase = u64, typename MaskType = IdBase>
struct [[nodiscard]] NodeId
    : dod::Id<IdBase, MaskType, std::integral_constant<MaskType, 16>> {
    using value_type = Node<N>;
    static auto Nil() -> NodeId { return FromValue(0); };
    static auto FromValue(IdBase arg) -> NodeId<N> {
        NodeId<N> res{IdBase{}};
        res.setValue(arg);
        return res;
    }
    auto operator==(NodeId<K, IdBase> other) const -> bool {
        return this->getValue() == other.getValue();
    }
    MaskType getStoreIdx() const { return this->getMask(); }

    explicit NodeId(IdBase arg)
        : dod::Id<IdBase, MaskType, std::integral_constant<MaskType, 16>>(
            arg) {}
};

template <typename N, typename K>
struct Node {
    N                                   kind;
    std::variant<NodeId<N>, TokenId<K>> value;

    bool isTerminal() const {
        return std::holds_alternative<TokenId<K>>(value);
    }

    bool isNonTerminal() const {
        return std::holds_alternative<NodeId<N>>(value);
    }

    void extend(NodeId<N> id) {
        assert(isNonTerminal());
        value = id;
    }
};

template <typename N, typename K>
struct NodeGroup {
    using NodeT = Node<N, K>;
    using IdT   = NodeId<N>;

    dod::store<IdT, NodeT> nodes;
    IdT                    push(CR<NodeT> node) { return nodes.add(node); }

    std::span<Token<K>> at(HSlice<IdT, IdT> slice) {
        assert(slice.first.getStoreIdx() == slice.last.getStoreIdx());
        nodes.at(slice(slice.first.getIndex(), slice.last.getIndex()));
    }

    NodeT& subnode(IdT id, int index) { auto& node = nodes.at(id); }
};
