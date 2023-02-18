#pragma once

#include <hstd/stdlib/dod_base.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/strformat.hpp>
#include <hstd/stdlib/strutils.hpp>

#include <lexbase/Errors.hpp>

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

    Str strVal() const {
        if (hasData()) {
            return Str(text.data(), text.size());
        } else {
            return "";
        }
    }

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

    int size() const { return tokens.size(); }
};

template <StringConvertible K>
std::ostream& operator<<(std::ostream& os, TokenGroup<K> const& tokens) {
    for (const auto& [idx, tok] : tokens.tokens.pairs()) {
        os << left_aligned(to_string(idx), 16) << " | " << *tok << "\n";
    }
    return os;
}


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
    /// \brief Set new active buffer pointer
    void setBuffer(Vec<Token<K>>* _buffer) { buffer = _buffer; }
    void clearBuffer() { buffer = nullptr; }
    /// \brief Get reference to token with specified ID
    Token<K>& at(TokenId<K> id) { return out->at(id); }
    /// \brief Get ID of the last token
    TokenId<K> back() const { return out->tokens.back(); }

    /// \name Add new token element to the list
    ///
    /// \returns ID of the new token or Nil if element is added to the
    /// buffer instead.
    ///
    /// \warning Returns nil IDs or empty list with active buffer!
    ///@{
    TokenId<K> push(CR<Token<K>> tok) {
        if (buffer != nullptr) {
            buffer->push_back(tok);
            return TokenId<K>::Nil();
        } else {
            return out->add(tok);
        }
    }

    Vec<TokenId<K>> push(CR<std::span<Token<K>>> tok) {
        if (buffer != nullptr) {
            buffer->append(tok);
            return Vec<TokenId<K>>();
        } else {
            return out->add(tok);
        }
    }

    Vec<TokenId<K>> push(CR<Vec<Token<K>>> tok) {
        if (buffer != nullptr) {
            buffer->append(tok);
            return Vec<TokenId<K>>();
        } else {
            return out->add(tok);
        }
    }
    ///@}
};

template <typename K>
struct LexerCommon {
  public:
    TokenGroup<K>* in;
    TokenId<K>     pos;
    LexerCommon(TokenGroup<K>* _in) : in(_in), pos(TokenId<K>(0)) {}

    K   kind(int offset = 0) const { return tok(offset).kind; }
    Str strVal(int offset = 0) const {
        return in->at(get(offset)).strVal();
    }
    CR<Token<K>> tok(int offset = 0) const { return in->at(get(offset)); }
    TokenId<K>   get(int offset = 0) const { return pos + offset; }
    TokenId<K>   pop() {
        TokenId<K> result = pos;
        next();
        return result;
    }


    TokenId<K> pop(IntSet<K> kind) {
        TokenId<K> result = get();
        skip(kind);
        return result;
    }

    TokenId<K> pop(K kind) {
        TokenId<K> result = get();
        skip(kind);
        return result;
    }

    Vec<TokenId<K>> pop(int count) {
        assert(0 <= count);
        Vec<TokenId<K>> result;
        for (int i = 0; i < count; ++i) {
            result.push_back(pop());
        }
        return result;
    }

    bool at(K kind, int offset = 0) const {
        return hasNext(offset) && tok(offset).kind == kind;
    }


    bool at(Vec<K> kind, int offset = 0) const {
        if (!hasNext(offset)) {
            return false;
        } else {
            for (const auto& [idx, kind] : enumerate(kind)) {
                if (tok(idx + offset).kind != kind) {
                    return false;
                }
            }
            return true;
        }
    }

    bool at(IntSet<K> kind, int offset = 0) const {
        return hasNext(offset) && kind.contains(tok(offset).kind);
    }

    int find(CR<IntSet<K>> skip, CR<IntSet<K>> target) const {
        int offset = 0;
        while (at(skip, offset)) {
            ++offset;
        }

        if (at(target, offset)) {
            return offset;
        } else {
            return -1;
        }
    }

    bool ahead(CR<IntSet<K>> skip, CR<IntSet<K>> target) const {
        return find(skip, target) != -1;
    }


    template <typename T>
    void skip(T kind, CR<Str> str = "")
        requires IsAnyOf<std::remove_cvref_t<T>, K, IntSet<K>>
    {
        if (at(kind) && (str.empty() || strVal() == str)) {
            next();

        } else if (finished()) {
            throw UnexpectedEndError(
                "Unexpected end encountered while trying to skip $#"
                    % to_string_vec(kind),
                pos.getIndex());

        } else {
            if (str.empty()) {
                throw UnexpectedCharError(
                    "Expected '$#' but found '$#'"
                        % to_string_vec(kind, str, this->kind(), strVal()),
                    pos.getIndex());
            } else {
                throw UnexpectedCharError(
                    "Expected '$#' with value '$#' but found '$#' with "
                    "value '$#'"
                        % to_string_vec(kind, str, this->kind(), strVal()),
                    pos.getIndex());
            }
        }
    }

    void trySkip(K kind) {
        if (at(kind)) {
            next();
        }
    }

    bool finished() const { return !hasNext(0); }
    /// \brief Can advance for at least \arg offset tokens
    virtual bool hasNext(int offset = 1) const = 0;
    /// \brief Advance by \arg offset tokens
    virtual void next(int offset = 1) = 0;

    int find(K kind) {
        int offset = 0;
        while (hasNext(offset)) {
            if (at(kind, offset)) {
                return offset;
            } else {
                ++offset;
            }
        }
        if (!hasNext(offset)) {
            return -1;
        }
    }

    Vec<TokenId<K>> getInside(IntSet<K> start, IntSet<K> finish) {
        Vec<TokenId<K>> result;
        int             count = 0;
        while (start.contains(kind())) {
            next();
        }
        count++;

        while (0 < count) {
            if (start.contains(kind())) {
                while (start.contains(kind())) {
                    if (0 < count) {
                        result.push_back(pop());
                    } else {
                        next();
                    }
                }
                count++;
            } else if (finish.contains(kind())) {
                while (!finished() && finish.contains(kind())) {
                    if (1 < count) {
                        result.push_back(pop());
                    } else {
                        next();
                    }
                }
                count--;
            } else {
                result.push_back(pop());
            }
        }
        return result;
    }
};

template <typename K>
std::ostream& operator<<(std::ostream& os, LexerCommon<K> const& value) {
    for (int i = 0; i < 10; ++i) {
        if (value.hasNext(i)) {
            if (0 < i) {
                os << " ";
            }
            os << value.get(i);
        }
    }
    return os;
}

/// \brief Lexer specialization for iterating over fixed sequence of IDs
template <typename K>
struct SubLexer : public LexerCommon<K> {
    // FIXME without this annotation public fields of the base class are
    // not not accessible. I don't think this is caused by the shadowing
    // issue, but aside from that I don't really know.
    using LexerCommon<K>::pos;

    int             subPos = 0;
    Vec<TokenId<K>> tokens;

    bool hasNext(int offset = 1) const override {
        return subPos + offset < tokens.size();
    }

    void next(int offset = 1) override {
        // TODO boundary checking
        subPos += offset;
        pos = tokens[subPos];
    }

    SubLexer(TokenGroup<K>* in, Vec<TokenId<K>> _tokens)
        : LexerCommon<K>(in), tokens(_tokens) {}
};


/// \brief Lexer specialization for iterating over all tokens in the token
/// group
template <typename K>
struct Lexer : public LexerCommon<K> {
    using LexerCommon<K>::pos;
    using LexerCommon<K>::in;

    void next(int offset = 1) override { pos = pos + offset; }
    bool hasNext(int offset = 1) const override {
        return (pos + offset).getIndex() < in->size();
    }

    Lexer(TokenGroup<K>* in) : LexerCommon<K>(in) {}
};

template <typename K>
inline SubLexer<K> splinter(
    LexerCommon<K>&        lex,
    const Vec<TokenId<K>>& ids) {
    return SubLexer<K>(lex.in, ids);
}
