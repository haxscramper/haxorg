#pragma once

#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Func.hpp>

#include <hstd/stdlib/dod_base.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/ColText.hpp>

#include <haxorg/lexbase/Token.hpp>
#include <format>

#include <variant>

namespace org::parse {

template <typename N, typename K, typename V, typename M>
struct Node;

template <
    typename N,
    typename K,
    typename V,
    typename M,
    typename IdBase   = hstd::u64,
    typename MaskType = IdBase>
struct NodeId
    : hstd::dod::
          Id<IdBase, MaskType, std::integral_constant<MaskType, 16>> {
    using base_type = hstd::dod::
        Id<IdBase, MaskType, std::integral_constant<MaskType, 16>>;
    using value_type = Node<N, K, V, M>;
    static auto Nil() -> NodeId { return FromValue(0); };
    static auto FromValue(IdBase arg) -> NodeId {
        NodeId<N, K, V, M> res{IdBase{}};
        res.setValue(arg);
        return res;
    }

    auto operator==(NodeId<N, K, V, M, IdBase> other) const -> bool {
        return this->getValue() == other.getValue();
    }

    MaskType getStoreIdx() const { return this->getMask(); }

    explicit NodeId(IdBase arg) : base_type(arg) {}
    NodeId(base_type arg) : base_type(arg) {}
};


template <typename N, typename K, typename V, typename M>
struct Node {
    N                                   kind;
    std::variant<int, TokenId<K, V>, M> value;

    Node(N _kind, TokenId<K, V> const& token)
        : kind(_kind), value(token) {}
    Node(N _kind, int extent = 0) : kind(_kind), value(extent) {}
    Node(N _kind, M mono) : kind(_kind), value(mono) {}

    static inline Node Mono(N _kind) { return Node(_kind, M()); }

    bool isMono() const { return std::holds_alternative<M>(value); }

    bool isTerminal() const {
        return std::holds_alternative<TokenId<K, V>>(value);
    }

    bool isNonTerminal() const {
        return std::holds_alternative<int>(value);
    }

    void extend(int extent) {
        LOGIC_ASSERTION_CHECK(isNonTerminal(), "");
        LOGIC_ASSERTION_CHECK(0 <= extent, "");
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

    M const& getMono() const { return std::get<M>(value); }

    /// \brief Check if the *non-terminal* node has zero extent.
    /// Terminal/Mono nodes return 'true'.
    bool isEmpty() const { return isNonTerminal() && getExtent() == 0; }

    /// \brief Return inclusive slice of all subnodes. NOTE: Because the
    /// `slice<T>()` is always inclusive, this function does not support
    /// returning empty list directly and instead outputs a nullopt value.
    hstd::Opt<hstd::Slice<NodeId<N, K, V, M>>> nestedNodes(
        NodeId<N, K, V, M> selfId) const {
        LOGIC_ASSERTION_CHECK(
            isNonTerminal(),
            "Node {} of kind {} does not have nested nodes",
            selfId,
            kind);

        if (isEmpty()) {
            return std::nullopt;
        } else {
            return hstd::slice(selfId + 1, selfId + getExtent());
        }
    }

    bool operator==(Node<N, K, V, M> const& other) const {
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

template <typename N, typename K, typename V, typename M>
struct NodeGroup;

} // namespace org::parse


template <typename N, typename K, typename IdBase, typename MaskType>
struct hstd::value_domain<org::parse::NodeId<N, K, IdBase, MaskType>> {
    using ID = org::parse::NodeId<N, K, IdBase, MaskType>;
    static ID succ(ID id) {
        ++id;
        return id;
    }
};


template <typename N, typename K, typename V, typename M>
struct std::formatter<org::parse::NodeId<N, K, V, M>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        const org::parse::NodeId<N, K, V, M>& p,
        FormatContext&                        ctx) const {
        std::formatter<std::string> fmt;
        return fmt.format(
            p.format(std::format(
                "NodeId<{}>", hstd::demangle(typeid(N).name()))),
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
        return hstd::fmt_ctx("<std::monostate>", ctx);
    }
};

template <typename N, typename K, typename V, typename M>
struct std::formatter<org::parse::Node<N, K, V, M>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const org::parse::Node<N, K, V, M>& p, FormatContext& ctx)
        const {
        hstd::fmt_ctx("{", ctx);
        hstd::fmt_ctx(p.kind, ctx);
        if (p.isTerminal()) {
            hstd::fmt_ctx(p.getToken(), ctx);
        } else {
            hstd::fmt_ctx(p.getExtent(), ctx);
        }

        return hstd::fmt_ctx("}", ctx);
    }
};
