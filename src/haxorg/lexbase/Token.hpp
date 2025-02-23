#pragma once

#include <hstd/stdlib/dod_base.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/strformat.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Debug.hpp>
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

    Token() = default;
    Token(K kind) : kind(kind) {}
    Token(K kind, V value) : kind(kind), value(value) {}
    V*       operator->() { return &this->value; }
    V const* operator->() const { return &this->value; }
};


template <typename K, typename V>
struct TokenGroup {
    using TokenT         = Token<K, V>;
    using IdT            = TokenId<K, V>;
    using StoreT         = hstd::dod::Store<IdT, TokenT>;
    using iterator       = typename StoreT::ContentT::iterator;
    using const_iterator = typename StoreT::ContentT::const_iterator;

    StoreT   tokens;
    iterator begin() { return tokens.content.begin(); }
    iterator end() { return tokens.content.end(); }
    iterator rbegin() { return tokens.content.rbegin(); }
    iterator rend() { return tokens.content.rend(); }
    iterator pos_iterator(IdT id) { return begin() + id.getIndex(); }
    iterator rpos_iterator(IdT id) {
        return rbegin() + (tokens.content().size() - id.getIndex() - 1);
    }

    const_iterator begin() const { return tokens.content.begin(); }
    const_iterator end() const { return tokens.content.end(); }
    const_iterator rbegin() const { return tokens.content.rbegin(); }
    const_iterator rend() const { return tokens.content.rend(); }
    const_iterator pos_iterator(IdT id) const {
        return begin() + id.getIndex();
    }
    const_iterator rpos_iterator(IdT id) const {
        return rbegin() + (tokens.content().size() - id.getIndex() - 1);
    }


    TokenGroup() {}
    TokenId<K, V> add(TokenT const& tok) { return tokens.add(tok); }

    hstd::Vec<IdT> add(hstd::Vec<TokenT> const& tok) {
        hstd::Vec<IdT> result;
        for (const auto& t : tok) { result.push_back(tokens.add(t)); }
        return result;
    }

    hstd::Vec<IdT> add(std::span<TokenT> const& tok) {
        hstd::Vec<IdT> result;
        for (const auto& t : tok) { result.push_back(tokens.add(t)); }
        return result;
    }


    TokenT& at(IdT pos) { return tokens.at(pos); }

    std::span<TokenT> at(hstd::HSlice<IdT, IdT> slice) {
        assert(slice.first.getStoreIdx() == slice.last.getStoreIdx());
        tokens.at(slice(slice.first.getIndex(), slice.last.getIndex()));
    }

    int  size() const { return tokens.size(); }
    void resize(int size, TokenT const& value = TokenT()) {
        tokens.resize(size, value);
    }
};


template <typename K, typename V>
struct TokenStore {
    hstd::Vec<TokenGroup<K, V>> groups;
    Token<K, V>&                at(TokenId<K, V> id) {
        return groups.at(id.getStoreIdx());
    }

    std::span<Token<K, V>> at(
        hstd::HSlice<TokenId<K, V>, TokenId<K, V>> slice) {
        assert(slice.first.getStoreIdx() == slice.last.getStoreIdx());
        groups.at(slice.first.getStoreIdx()).at(slice);
    }
};

template <typename K, typename V>
struct Tokenizer {
    TokenGroup<K, V>* out;
    Tokenizer(TokenGroup<K, V>* _out) : out(_out) {}
    hstd::Vec<hstd::Vec<Token<K, V>>*> buffer;
    void                               clearBuffer() { buffer.pop_back(); }
    /// \brief Get reference to token with specified ID
    Token<K, V>& at(TokenId<K, V> id) { return out->at(id); }
    /// \brief Get ID of the last token
    TokenId<K, V> back() const { return out->tokens.back(); }
    int           size() const { return out->size(); }
    void          resize(int size, Token<K, V> value = Token<K, V>()) {
        out->resize(size, value);
    }

    /// \name Add new token element to the list
    ///
    /// \returns ID of the new token or Nil if element is added to the
    /// buffer instead.
    ///
    /// \warning Returns nil IDs or empty list with active buffer!
    ///@{
    TokenId<K, V> push(Token<K, V> const& tok) {
        if (buffer.empty()) {
            return out->add(tok);
        } else {
            buffer.back()->push_back(tok);
            return TokenId<K, V>::Nil();
        }
    }

    hstd::Vec<TokenId<K, V>> push(std::span<Token<K, V>> const& tok) {
        if (buffer.empty()) {
            return out->add(tok);
        } else {
            buffer.back()->append(tok);
            return Vec<TokenId<K, V>>();
        }
    }

    hstd::Vec<TokenId<K, V>> push(hstd::CVec<Token<K, V>> tok) {
        if (buffer.empty()) {
            return out->add(tok);
        } else {
            buffer.back()->append(tok);
            return Vec<TokenId<K, V>>();
        }
    }
    ///@}
};

template <typename K, typename V>
struct LexerCommon {
  public:
    TokenGroup<K, V>*      in;
    TokenId<K, V>          pos;
    hstd::Opt<Token<K, V>> lastToken;
    LexerCommon(
        TokenGroup<K, V>* _in,
        TokenId<K, V>     startPos = TokenId<K, V>(0))
        : in(_in), pos(startPos) {}

    K            kind(int offset = 0) const { return tok(offset).kind; }
    Token<K, V>& tok(TokenId<K, V> id) { return in->at(id); }
    Token<K, V> const& tok(TokenId<K, V> id) const { return in->at(id); }
    Token<K, V> const& tok(int offset = 0) const {
        return in->at(get(offset));
    }
    TokenId<K, V> get(int offset = 0) const { return pos + offset; }
    V const&      val(int offset = 0) const { return tok(offset).value; }
    V&            val(int offset = 0) { return in->at(get(offset)).value; }

    hstd::Opt<hstd::CRw<Token<K, V>>> opt(int offset = 0) {
        if (hasNext(offset)) {
            return tok(offset);
        } else {
            return std::nullopt;
        }
    }

    using iterator       = typename TokenGroup<K, V>::iterator;
    using const_iterator = typename TokenGroup<K, V>::const_iterator;

    iterator       begin() { return in->pos_iterator(this->pos); }
    iterator       end() { return in->end(); }
    const_iterator begin() const { return in->pos_iterator(this->pos); }
    const_iterator end() const { return in->end(); }

    struct WholeTmp {
        LexerCommon<K, V>*       _this;
        hstd::Opt<TokenId<K, V>> currentPos;

        LexerCommon<K, V>*       __this() { return _this; }
        LexerCommon<K, V> const* __this() const { return _this; }

        /// Get iterator to the first token in sequence, ignoring lexer
        /// offsets
        iterator       begin() { return __this()->in->begin(); }
        const_iterator begin() const { return __this()->in->begin(); }
        /// Get iterator to the final end of the token, same as lexer base
        /// end()
        iterator       end() { return __this()->end(); }
        const_iterator end() const { return __this()->end(); }
        /// Get iterator pointing to the current token (if the lexer moves
        /// it will change)
        iterator current() {
            if (__this()->finished()) {
                return end();
            } else {
                return __this()->in->pos_iterator(
                    currentPos ? *currentPos : __this()->pos);
            }
        }

        const_iterator current() const {
            if (__this()->finished()) {
                return end();
            } else {
                return __this()->in->pos_iterator(
                    currentPos ? *currentPos : __this()->pos);
            }
        }

        iterator       rbegin() { return __this()->in->rbegin(); }
        const iterator rbegin() const { return __this()->in->rbegin(); }

        iterator       rend() { return __this()->in->rend(); }
        const_iterator rend() const { return __this()->in->rend(); }

        iterator rcurrent() {
            return __this()->in->rpos_iterator(
                currentPos ? *currentPos : _this->pos);
        }

        const iterator rcurrent() const {
            return __this()->in->rpos_iterator(
                currentPos ? *currentPos : _this->pos);
        }

        hstd::rs::subrange<iterator> range() {
            return hstd::rs::subrange(begin(), end());
        }

        hstd::rs::subrange<const_iterator> range() const {
            return hstd::rs::subrange(begin(), end());
        }

        hstd::rs::subrange<iterator> range_current() {
            return hstd::rs::subrange(current(), end());
        }

        hstd::rs::subrange<const_iterator> range_current() const {
            return hstd::rs::subrange(current(), end());
        }

        hstd::rs::subrange<iterator> rrange() {
            return hstd::rs::subrange(rbegin(), rend());
        }

        hstd::rs::subrange<const_iterator> rrange() const {
            return hstd::rs::subrange(rbegin(), rend());
        }
    };

    /// Get temporary access range for the whole sequence of tokens
    WholeTmp whole() { return WholeTmp{this}; }
    /// Return access to the 'whole' range that will not change when the
    /// lexer moves around.
    WholeTmp whole_fixed() { return WholeTmp{this, pos}; }

    struct PrintParams {
        int  maxTokens   = 10;
        int  startOffset = 0;
        bool withPos     = true;
        bool withColor   = true;
        bool withOffsets = false;
    };

    using TokenFormatCb = hstd::Func<
        void(hstd::ColStream&, Token<K, V> const&)>;

    void print(
        hstd::ColStream&   os,
        TokenFormatCb      format,
        PrintParams const& params) const {
        if (params.withPos) {
            if (pos.isNil()) {
                os << "#" << os.red() << "nil" << os.end();
            } else {
                os << hstd::fmt("#{}/{}", pos.getIndex(), in->size());
            }
        }

        if (finished()) {
            os << os.red() << " finished" << os.end();
        } else {
            for (int i = params.startOffset;
                 i < params.maxTokens && hasNext(i);
                 ++i) {
                const auto& t = tok(i);
                if (os.colored) {
                    os << " "
                       << styledUnicodeMapping(
                              std::format("{}", t.kind),
                              hstd::AsciiStyle::Italic);
                } else {
                    os << " " << std::format("{}", t.kind);
                }
                format(os, t);
            }
        }
    }


    std::string printToString(TokenFormatCb format, bool colored = false)
        const {
        return printToString(PrintParams{}, format, colored);
    }

    std::string printToString(
        PrintParams   params,
        TokenFormatCb format,
        bool          colored = false) const {
        std::stringstream stream;
        hstd::ColStream   out{stream};
        out.colored = colored;
        print(out, format, params);
        return stream.str();
    }

    TokenId<K, V> pop() {
        TokenId<K, V> result = pos;
        next();
        return result;
    }


    TokenId<K, V> pop(hstd::IntSet<K> kind) {
        TokenId<K, V> result = get();
        skip(kind);
        return result;
    }

    TokenId<K, V> pop(K kind) {
        TokenId<K, V> result = get();
        skip(kind);
        return result;
    }

    hstd::Vec<TokenId<K, V>> pop(int count) {
        assert(0 <= count);
        hstd::Vec<TokenId<K, V>> result;
        for (int i = 0; i < count; ++i) { result.push_back(pop()); }
        return result;
    }

    bool at(K kind, int offset = 0) const {
        return hasNext(offset) && tok(offset).kind == kind;
    }


    bool at(hstd::CVec<K> kind, int offset = 0) const {
        if (!hasNext(offset)) {
            return false;
        } else {
            for (const auto& [idx, kind] : enumerate(kind)) {
                if (!hasNext(idx + offset)
                    || tok(idx + offset).kind != kind) {
                    return false;
                }
            }
            return true;
        }
    }

    bool can_search(K kind) { return !finished() && !at(kind); }
    bool can_search(hstd::IntSet<K> kind) {
        return !finished() && !at(kind);
    }
    bool can_search(hstd::Vec<K> kind) { return !finished() && !at(kind); }

    bool at(hstd::IntSet<K> kind, int offset = 0) const {
        return hasNext(offset) && kind.contains(tok(offset).kind);
    }

    template <typename Target>
    int find(hstd::IntSet<K> const& skip, Target const& target) const {
        int offset = 0;
        while (at(skip, offset)) { ++offset; }

        if (at(target, offset)) {
            return offset;
        } else {
            return -1;
        }
    }

    bool ahead(hstd::IntSet<K> const& skip, hstd::Vec<K> const& target)
        const {
        return find(skip, target) != -1;
    }

    bool ahead(hstd::IntSet<K> const& skip, hstd::IntSet<K> const& target)
        const {
        return find(skip, target) != -1;
    }

    bool ahead(K const& skip, K const& target) const {
        return find(hstd::IntSet<K>{skip}, hstd::IntSet<K>{target}) != -1;
    }

    /// Check if the lexer is positioned on the appropriate token kind
    /// (and lexeme value if it is supplied). Raise exception if the
    /// token does not match and return true otherwise.
    template <typename T>
    bool expect(T kind)
        requires hstd::IsAnyOf<std::remove_cvref_t<T>, K, hstd::IntSet<K>>
    {
        if (at(kind)) {
            return true;
        } else if (finished()) {
            throw UnexpectedEndError(hstd::fmt(
                "Unexpected end encountered while trying to skip {} token "
                "at index {}",
                kind,
                pos.getIndex()));

        } else {
            throw UnexpectedCharError(
                hstd::fmt(
                    "Expected '{}' but found '{}' at index {}: {}",
                    kind,
                    this->kind(),
                    pos.getIndex(),
                    this->tok(pos)),
                pos.getIndex());
        }
    }

    template <typename T>
    void skip(T kind)
        requires hstd::IsAnyOf<std::remove_cvref_t<T>, K, hstd::IntSet<K>>
    {
        if (expect(kind)) { next(); }
    }

    void trySkip(K kind) {
        if (at(kind)) { next(); }
    }

    bool finished() const { return !hasNext(0); }
    /// \brief Can advance for at least \arg offset tokens
    virtual bool hasNext(int offset = 1) const = 0;
    /// \brief Advance by \arg offset tokens
    virtual void next(int offset = 1) = 0;

    virtual TokenId<K, V> getPos() const { return pos; }
    virtual void          setPos(TokenId<K, V> id) { this->pos = id; }

    int find(K kind) {
        int offset = 0;
        while (hasNext(offset)) {
            if (at(kind, offset)) {
                return offset;
            } else {
                ++offset;
            }
        }
        if (!hasNext(offset)) { return -1; }
    }

    hstd::Vec<TokenId<K, V>> getInside(
        hstd::IntSet<K> const& start,
        hstd::IntSet<K> const& finish) {
        hstd::Vec<TokenId<K, V>> result;
        int                      count = 0;
        while (start.contains(kind())) { next(); }
        count++;
        while (0 < count && !finished()) {
            if (!finished() && start.contains(kind())) {
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


/// \brief Lexer specialization for iterating over fixed sequence of IDs
template <typename K, typename V>
struct SubLexer : public LexerCommon<K, V> {
    // FIXME without this annotation public fields of the base class are
    // not not accessible. I don't think this is caused by the shadowing
    // issue, but aside from that I don't really know.
    using LexerCommon<K, V>::pos;

    int                      subPos = 0;
    hstd::Vec<TokenId<K, V>> tokens;


    bool empty() const { return tokens.empty(); }
    bool hasNext(int offset = 1) const override {
        auto idx = subPos + offset;
        return !pos.isNil() && (0 <= idx) && (idx < tokens.size());
    }

    void add(TokenId<K, V> const& tok) { tokens.push_back(tok); }
    void start() { pos = tokens.at(0); }

    void setPos(TokenId<K, V> id) override {
        int foundPos = tokens.indexOf(id);
        if (foundPos == -1) {
            throw std::range_error(
                "Sub-lexer does have a token with a specified token id");
        }

        subPos = foundPos;
        pos    = tokens.at(subPos);
    }

    void next(int offset = 1) override {
        // TODO boundary checking
        if (hasNext(offset)) {
            this->lastToken = this->tok();
            subPos += offset;
            pos = tokens.at(subPos);
        } else {
            subPos += offset;
            pos = TokenId<K, V>::Nil();
        }
    }

    SubLexer(LexerCommon<K, V> const& in) : LexerCommon<K, V>(in.in) {}

    SubLexer(TokenGroup<K, V>* in, hstd::Vec<TokenId<K, V>> const& _tokens)
        : LexerCommon<K, V>(
              in,
              _tokens.empty() ? TokenId<K, V>::Nil() : _tokens.at(0))
        , tokens(_tokens) {}
};


/// \brief Lexer specialization for iterating over all tokens in the token
/// group
template <typename K, typename V>
struct Lexer : public LexerCommon<K, V> {
    using LexerCommon<K, V>::pos;
    using LexerCommon<K, V>::in;

    void next(int offset = 1) override {
        if (hasNext(offset)) {
            this->lastToken = this->tok();
            pos             = pos + offset;
        } else {
            pos = TokenId<K, V>::Nil();
        }
    }

    bool hasNext(int offset = 1) const override {
        if (pos.isNil() || (pos + offset).isNil()) {
            return false;
        } else {
            auto idx = (pos + offset).getIndex();
            return (0 <= idx) && (idx < in->size());
        }
    }

    Lexer(TokenGroup<K, V>* in) : LexerCommon<K, V>(in) {}
};

} // namespace org::parse

template <hstd::StdFormattable K, hstd::StdFormattable V>
struct std::formatter<org::parse::TokenGroup<K, V>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(
        const org::parse::TokenGroup<K, V>& p,
        FormatContext&                      ctx) {
        std::formatter<std::string> fmt;
        for (const auto& [idx, tok] : p.tokens.pairs()) {
            fmt.format(std::format("{:<16}", idx), ctx);
            fmt.format(" | ", ctx);
            fmt.format(*tok, ctx);
            fmt.format("\n", ctx);
        }

        return fmt.format("", ctx);
    }
};


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

template <typename K, typename V>
struct std::formatter<org::parse::LexerCommon<K, V>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        const org::parse::LexerCommon<K, V>& p,
        FormatContext&                       ctx) const {
        return ::hstd::fmt_ctx(
            p.printToString(
                [](hstd::ColStream&, org::parse::Token<K, V> const&) {}),
            ctx);
    }
};
