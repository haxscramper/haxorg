#pragma once

#include <hstd/stdlib/dod_base.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/strformat.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/RangeTree.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <format>

#include <lexbase/Errors.hpp>

template <typename K, typename V>
struct Token;


template <
    typename K,
    typename V,
    typename IdBase   = u64,
    typename MaskType = IdBase>
struct [[nodiscard]] TokenId
    : dod::Id<IdBase, MaskType, std::integral_constant<MaskType, 16>> {
    using value_type = Token<K, V>;
    static auto Nil() -> TokenId { return FromValue(0); };
    static auto FromValue(IdBase arg) -> TokenId<K, V> {
        TokenId<K, V> res{IdBase{}};
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

template <typename K, typename V>
struct std::formatter<TokenId<K, V>> : std::formatter<std::string> {
    template <typename FormatContext>
    typename FormatContext::iterator format(
        const TokenId<K, V>& p,
        FormatContext&       ctx) {
        std::formatter<std::string> fmt;
        return fmt.format(p.format(demangle(typeid(K).name())), ctx);
    }
};


/// Generic token containing minimal required information: span of text and
/// tag. Line/Column information can be computed on the as-needed basis
/// from the base string.
template <typename K, typename V>
struct Token {
    using id_type = TokenId<K, V>;
    K kind; /// Specific kind of the token
    V value;

    Token() = default;
    Token(K kind) : kind(kind) {}
    Token(K kind, V value) : kind(kind), value(value) {}
    V&       operator->() { return this->value; }
    V const& operator->() const { return this->value; }
};


template <StdFormattable K, typename V>
struct std::formatter<Token<K, V>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const Token<K, V>& p, FormatContext& ctx) {
        std::formatter<std::string> fmt;
        fmt.format("Token<", ctx);
        fmt.format(p.kind, ctx);
        fmt.format(">(", ctx);
        fmt.format(p.value, ctx);
        return fmt.format(")", ctx);
    }
};


template <typename K, typename V>
struct TokenGroup {
    dod::Store<TokenId<K, V>, Token<K, V>> tokens;
    Opt<std::string_view>                  base;

    TokenGroup(Opt<std::string_view> base = std::nullopt) : base(base) {}
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

    int  size() const { return tokens.size(); }
    void resize(int size, Token<K> const& value = Token<K>()) {
        tokens.resize(size, value);
    }

    Slice<int> toAbsolute(std::string_view view) const {
        if (base.has_value()) {
            auto main = base.value();
            assert(is_within_memory_block<char>(
                view.data(), main.data(), main.size()));
            int offset = static_cast<int>(
                pointer_distance(main.data(), view.data()));
            return slice<int>(
                offset, static_cast<int>(offset + view.size()));
        }
    }
};

template <StringConvertible K>
struct std::formatter<TokenGroup<K>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const TokenGroup<K>& p, FormatContext& ctx) {
        std::string res;
        for (const auto& [idx, tok] : tokens.tokens.pairs()) {
            res += std::format("{:<16} | {}\n", idx, *tok);
        }
        return res;
    }
};


template <StringConvertible K>
struct std::formatter<TokenGroup<K>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const TokenGroup<K>& p, FormatContext& ctx) {
        std::string res;
        for (const auto& [idx, tok] : tokens.tokens.pairs()) {
            res std::format("{:<16} | {}\n", idx, *tok);
        }
        return res;
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
    Vec<Vec<Token<K>>*> buffer;
    /// \brief Set new active buffer pointer
    void setBuffer(Vec<Token<K>>* _buffer) { buffer.push_back(_buffer); }
    void clearBuffer() { buffer.pop_back(); }
    /// \brief Get reference to token with specified ID
    Token<K>& at(TokenId<K> id) { return out->at(id); }
    /// \brief Get ID of the last token
    TokenId<K> back() const { return out->tokens.back(); }
    int        size() const { return out->size(); }
    void       resize(int size, Token<K> value = Token<K>()) {
        out->resize(size, value);
    }

    /// \name Add new token element to the list
    ///
    /// \returns ID of the new token or Nil if element is added to the
    /// buffer instead.
    ///
    /// \warning Returns nil IDs or empty list with active buffer!
    ///@{
    TokenId<K> push(CR<Token<K>> tok) {
        if (buffer.empty()) {
            return out->add(tok);
        } else {
            buffer.back()->push_back(tok);
            return TokenId<K>::Nil();
        }
    }

    Vec<TokenId<K>> push(CR<std::span<Token<K>>> tok) {
        if (buffer.empty()) {
            return out->add(tok);
        } else {
            buffer.back()->append(tok);
            return Vec<TokenId<K>>();
        }
    }

    Vec<TokenId<K>> push(CR<Vec<Token<K>>> tok) {
        if (buffer.empty()) {
            return out->add(tok);
        } else {
            buffer.back()->append(tok);
            return Vec<TokenId<K>>();
        }
    }
    ///@}
};

template <typename K>
struct LexerCommon {
  public:
    TokenGroup<K>* in;
    TokenId<K>     pos;
    LexerCommon(TokenGroup<K>* _in, TokenId<K> startPos = TokenId<K>(0))
        : in(_in), pos(startPos) {}

    Str strVal(int offset = 0) const {
        return in->at(get(offset)).strVal();
    }

    K            kind(int offset = 0) const { return tok(offset).kind; }
    Token<K>&    tok(TokenId<K> id) { return in->at(id); }
    CR<Token<K>> tok(TokenId<K> id) const { return in->at(id); }
    CR<Token<K>> tok(int offset = 0) const { return in->at(get(offset)); }
    TokenId<K>   get(int offset = 0) const { return pos + offset; }

    struct PrintParams {
        int  maxTokens   = 10;
        int  startOffset = 0;
        bool withPos     = true;
        bool withColor   = true;
        bool withOffsets = false;
    };

    void print(ColStream& os, CR<PrintParams> params) const {
        if (params.withPos) {
            if (pos.isNil()) {
                os << "#" << os.red() << "nil" << os.end();
            } else {
                os << "#" << pos.getIndex() << "/" << in->size();
            }
        }

        if (finished()) {
            os << os.red() << " finished" << os.end();
        } else {
            for (int i = params.startOffset;
                 i < params.maxTokens && hasNext(i);
                 ++i) {
                const auto& t = tok(i);
                os << " "
                   << styledUnicodeMapping(
                          to_string(t.kind), AsciiStyle::Italic);
                if (t.hasData()) {
                    os << " '";
                    hshow(
                        os,
                        t.getText(),
                        HDisplayOpts().excl(HDisplayFlag::UseQuotes));
                    os << "'";
                } else {
                    if (params.withOffsets) {
                        os << " " << os.cyan() << t.getOffset()
                           << os.end();
                    }
                }
            }
        }
    }


    std::string printToString(bool colored = false) const {
        return printToString(PrintParams{}, colored);
    }

    std::string printToString(PrintParams params, bool colored = false)
        const {
        std::string  result;
        std::ostream stream{&result};
        ColStream    out{stream};
        out.colored = colored;
        print(out, params);
        return result;
    }

    TokenId<K> pop() {
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

    bool ahead(CR<K> skip, CR<K> target) const {
        return find(IntSet<K>{skip}, IntSet<K>{target}) != -1;
    }

    /// Check if the lexer is positioned on the appropriate token kind
    /// (and lexeme value if it is supplied). Raise exception if the
    /// token does not match and return true otherwise.
    template <typename T>
    bool expect(T kind, CR<Str> str = "")
        requires IsAnyOf<std::remove_cvref_t<T>, K, IntSet<K>>
    {
        if (at(kind) && (str.empty() || strVal() == str)) {
            return true;
        } else if (finished()) {
            throw UnexpectedEndError(
                "Unexpected end encountered while trying to skip $# token "
                "at index $#"
                    % to_string_vec(kind, pos.getIndex()),
                pos.getIndex());

        } else {
            if (str.empty()) {
                throw UnexpectedCharError(
                    "Expected '$#' but found '$#' at index $#"
                        % to_string_vec(
                            kind, this->kind(), pos.getIndex()),
                    pos.getIndex());
            } else {
                throw UnexpectedCharError(
                    "Expected '$#' with value '$#' but found '$#' with "
                    "value '$#' at index $#"
                        % to_string_vec(
                            kind,
                            str,
                            this->kind(),
                            strVal(),
                            pos.getIndex()),
                    pos.getIndex());
            }
        }
    }

    template <typename T>
    void skip(T kind, CR<Str> str = "")
        requires IsAnyOf<std::remove_cvref_t<T>, K, IntSet<K>>
    {
        if (expect(kind, str)) {
            next();
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
                    // TODO identical to the inner loop -- implement unit
                    // test to get coverage for this case to make sure this
                    // can be safely removed.
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
struct std::formatter<LexerCommon<K>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const LexerCommon<K>& p, FormatContext& ctx) {
        return p.printToString();
    }
};


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
        auto idx = subPos + offset;
        return !pos.isNil() && (0 <= idx) && (idx < tokens.size());
    }

    void next(int offset = 1) override {
        // TODO boundary checking
        if (hasNext(offset)) {
            subPos += offset;
            pos = tokens.at(subPos);
        } else {
            subPos += offset;
            pos = TokenId<K>::Nil();
        }
    }

    SubLexer(TokenGroup<K>* in, Vec<TokenId<K>> _tokens)
        : LexerCommon<K>(in, _tokens.at(0)), tokens(_tokens) {}
};


/// \brief Lexer specialization for iterating over all tokens in the token
/// group
template <typename K>
struct Lexer : public LexerCommon<K> {
    using LexerCommon<K>::pos;
    using LexerCommon<K>::in;

    void next(int offset = 1) override {
        if (hasNext(offset)) {
            pos = pos + offset;
        } else {
            pos = TokenId<K>::Nil();
        }
    }

    bool hasNext(int offset = 1) const override {
        if (pos.isNil()) {
            return false;
        } else {
            auto idx = (pos + offset).getIndex();
            return (0 <= idx) && (idx < in->size());
        }
    }

    Lexer(TokenGroup<K>* in) : LexerCommon<K>(in) {}
};
