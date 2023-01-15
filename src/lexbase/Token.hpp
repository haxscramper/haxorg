#pragma once

#include <hstd/stdlib/dod_base.hpp>

template <typename K>
struct Token;

template <typename K, typename IdBase = int>
struct [[nodiscard]] TokenId : dod::Id<int> {
    using value_type = Token<K>;
    static auto Nil() -> TokenId { return FromValue(0); };
    static auto FromValue(IdBase arg) -> TokenId<K> {
        TokenId<K> res{IdBase{}};
        res.setValue(arg);
        return res;
    }
    auto operator==(TokenId<K> other) const -> bool {
        return getValue() == other.getValue();
    }
    explicit TokenId(IdBase arg) : dod::Id<IdBase>(arg) {}
};

/// Generic token containing minimal required information: span of text and
/// tag. Line/Column information can be computed on the as-needed basis
/// from the base string.
template <typename K>
struct Token {
    using id_type = TokenId<K>;
    K                kind; /// Specific kind of the token
    std::string_view text; /// Token view on the base input text

    Token() = default;
    Token(K _kind, std::string_view _text) : kind(_kind), text(_text) {}
    Token(K _kind, int offset) : kind(_kind), text(nullptr, offset) {}

    /// Check if token text is a view over real data
    bool hasData() const { return text.data() != nullptr; }
    /// Return character count for the token. If it does not contain any
    /// data return 0.
    int size() const {
        if (hasData()) {
            return text.size();
        } else {
            return 0;
        }
    }


    /// Return offset from the starting point of the string. If token does
    /// not have real data, return faked position (`.size()` of the text)
    /// instead. \warning This function is intended to be used with real
    /// starting point of the view that was used in the originating
    /// positional string and so the behavior with 'fake' token is going to
    /// be invalid when used with any other position in the string.
    std::size_t offsetFrom(const char* start) const {
        if (hasData()) {
            return std::distance(text.data(), start);
        } else {
            return text.size();
        }
    }
};


template <StringConvertible K>
std::ostream& operator<<(std::ostream& os, Token<K> const& value) {
    os << "Token<" << to_string(value.kind) << ">(" << value.text << ")";
    return os;
}
