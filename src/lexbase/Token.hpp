#pragma once

#include <hstd/stdlib/dod_base.hpp>
#include <hstd/stdlib/IntSet.hpp>

template <typename K>
struct Token;

template <typename K, typename IdBase = u64, typename MaskType = IdBase>
struct [[nodiscard]] TokenId
    : dod::Id<IdBase, MaskType, std::integral_constant<MaskType, 16>> {
    using value_type = Token<K>;
    static auto Nil() -> TokenId { return FromValue(0); };
    static auto FromValue(IdBase arg) -> TokenId<K> {
        TokenId<K> res{IdBase{}};
        res.setValue(arg);
        return res;
    }
    auto operator==(TokenId<K, IdBase> other) const -> bool {
        return this->getValue() == other.getValue();
    }
    MaskType getStoreIdx() const { return this->getMask(); }

    explicit TokenId(IdBase arg)
        : dod::Id<IdBase, MaskType, std::integral_constant<MaskType, 16>>(
            arg) {}
};

template <typename K>
std::ostream& operator<<(std::ostream& os, TokenId<K> const& value) {
    return value.streamTo(os, demangle(typeid(K).name()));
}

/// Generic token containing minimal required information: span of text and
/// tag. Line/Column information can be computed on the as-needed basis
/// from the base string.
template <typename K>
struct Token {
    using id_type = TokenId<K>;
    K                kind; /// Specific kind of the token
    std::string_view text; /// Token view on the base input text

    Token() = default;
    /// \brief Create token that points to the real string data
    Token(K _kind, std::string_view _text) : kind(_kind), text(_text) {}
    /// \brief Create fake token that is positioned at some point in the
    /// base string.
    ///
    /// \note Default offset parameter is -1 which creates token that is
    /// completely detached from any real position.
    Token(K _kind, int offset = -1) : kind(_kind), text(nullptr, offset) {}

    /// \brief Check if token has any offset information
    bool hasOffset() const { return hasData() || text.size() != -1; }
    /// \brief Check if token text is a view over real data
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
    os << "Token<" << to_string(value.kind) << ">(";
    if (value.hasData()) {
        os << escape_literal(to_string(value.text));
    } else if (value.hasOffset()) {
        os << "offset:" << value.text.size();
    } else {
        os << "?";
    }
    return os << ")";
}


template <typename K>
struct TokenGroup {
    dod::Store<TokenId<K>, Token<K>> tokens;

    TokenGroup() {}

    TokenId<K> add(CR<Token<K>> tok) { return tokens.add(tok); }

    Vec<TokenId<K>> add(CR<Vec<Token<K>>> tok) {
        Vec<TokenId<K>> result;
        for (const auto& t : tok) {
            result.push_back(tokens.add(t));
        }
        return result;
    }

    Vec<TokenId<K>> add(CR<std::span<Token<K>>> tok) {
        Vec<TokenId<K>> result;
        for (const auto& t : tok) {
            result.push_back(tokens.add(t));
        }
        return result;
    }


    Token<K>& at(TokenId<K> pos) { return tokens.at(pos); }

    std::span<Token<K>> at(HSlice<TokenId<K>, TokenId<K>> slice) {
        assert(slice.first.getStoreIdx() == slice.last.getStoreIdx());
        tokens.at(slice(slice.first.getIndex(), slice.last.getIndex()));
    }
};

template <typename K>
struct TokenStore {
    Vec<TokenGroup<K>> groups;
    Token<K>& at(TokenId<K> id) { return groups.at(id.getStoreIdx()); }

    std::span<Token<K>> at(HSlice<TokenId<K>, TokenId<K>> slice) {
        assert(slice.first.getStoreIdx() == slice.last.getStoreIdx());
        groups.at(slice.first.getStoreIdx()).at(slice);
    }
};

template <typename K>
struct Tokenizer {
    TokenGroup<K>* out;
    Tokenizer(TokenGroup<K>* _out) : out(_out) {}
    Vec<Token<K>>* buffer = nullptr;
    void           setBuffer(Vec<Token<K>>* _buffer) { buffer = _buffer; }
    void           clearBuffer() { buffer = nullptr; }

    void push(CR<Token<K>> tok) {
        if (buffer != nullptr) {
            buffer->push_back(tok);
        } else {
            (void)out->add(tok);
        }
    }

    void push(CR<std::span<Token<K>>> tok) {
        if (buffer != nullptr) {
            buffer->append(tok);
        } else {
            out->add(tok);
        }
    }

    void push(CR<Vec<Token<K>>> tok) {
        if (buffer != nullptr) {
            buffer->append(tok);
        } else {
            out->add(tok);
        }
    }
};

template <typename K>
struct Lexer {
    TokenGroup<K>* in;
    Lexer(TokenGroup<K>* _in) : in(_in), pos(TokenId<K>(0)) {}
    TokenId<K> pos;

    CR<Token<K>> tok(int offset = 0) const { return in->at(get(offset)); }
    TokenId<K>   get(int offset = 0) const { return pos + offset; }
    TokenId<K>   pop() {
          TokenId<K> result = pos;
          next();
          return result;
    }

    bool at(K kind, int offset = 0) const {
        return tok(offset).kind == kind;
    }

    void next(int offset = 1) { pos = pos + offset; }

    bool at(Vec<K> kind, int offset = 0) const {
        for (const auto& [idx, kind] : enumerate(kind)) {
            if (tok(idx + offset).kind != kind) {
                return false;
            }
        }
        return true;
    }

    bool at(IntSet<K> kind, int offset = 0) const {
        return kind.contains(tok(offset).kind);
    }

    void skip(K kind) {
        if (at(kind)) {
            next();
        } else {
            assert(false && "TODO");
        }
    }
};
