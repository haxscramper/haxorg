#pragma once

#include <hstd/stdlib/dod_base.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/strformat.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Func.hpp>
#include <format>
#include <hstd/stdlib/Opt.hpp>

#include <haxorg/lexbase/Errors.hpp>
#include <hstd/stdlib/Ranges.hpp>

namespace org::parse {

template <typename K, typename V>
struct Token;


template <
    typename K,
    typename V,
    typename IdBase   = hstd::u64,
    typename MaskType = IdBase>
struct TokenId
    : hstd::dod::
          Id<IdBase, MaskType, std::integral_constant<MaskType, 16>> {
    using base_type = hstd::dod::
        Id<IdBase, MaskType, std::integral_constant<MaskType, 16>>;
    using value_type = Token<K, V>;
    static auto Nil() -> TokenId { return FromValue(0); };
    static auto FromValue(IdBase arg) -> TokenId<K, V> {
        TokenId<K, V> res{IdBase{}};
        res.setValue(arg);
        return res;
    }

    auto operator==(TokenId<K, V, IdBase> other) const -> bool {
        return this->getValue() == other.getValue();
    }

    MaskType getStoreIdx() const { return this->getMask(); }

    explicit TokenId(IdBase arg) : base_type(arg) {}
    TokenId(base_type arg) : base_type(arg) {}
};


/// Generic token containing minimal required information: span of text and
/// tag. Line/Column information can be computed on the as-needed basis
/// from the base string.
template <typename K, typename V>
struct Token {
    using id_type = TokenId<K, V>;
    K kind; /// Specific kind of the token
    V value;

    DESC_FIELDS(Token, (kind, value));

    Token() = default;
    Token(K kind) : kind(kind) {}
    Token(K kind, V value) : kind(kind), value(value) {}
    V*       operator->() { return &this->value; }
    V const* operator->() const { return &this->value; }
};



} // namespace org::parse



template <hstd::StdFormattable K, typename V>
struct std::formatter<org::parse::Token<K, V>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        org::parse::Token<K, V> const& p,
        FormatContext&                 ctx) const {
        std::formatter<std::string> fmt;
        fmt.format("Token<", ctx);
        std::formatter<K>{}.format(p.kind, ctx);
        fmt.format(">(", ctx);
        std::formatter<V>{}.format(p.value, ctx);
        return fmt.format(")", ctx);
    }
};


template <typename K, typename V>
struct std::formatter<org::parse::TokenId<K, V>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    typename FormatContext::iterator format(
        const org::parse::TokenId<K, V>& p,
        FormatContext&                   ctx) const {
        std::formatter<std::string> fmt;
        return fmt.format(p.format(hstd::demangle(typeid(K).name())), ctx);
    }
};
