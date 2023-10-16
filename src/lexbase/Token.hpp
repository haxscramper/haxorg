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
    K kind; /// Specific kind of the token
    /// Token view on the base input text or offset position in case the
    /// token is not attached to real data (fake token).
    Variant<int, std::stringView> text;

    Token() = default;
    /// \brief Create token that points to the real string data
    Token(K _kind, std::stringView _text) : kind(_kind), text(_text) {}
    /// \brief Create fake token that is positioned at some point in the
    /// base string.
    Token(K _kind, int offset = 0) : kind(_kind), text(offset) {}

    Str strVal() const {
        if (hasData()) {
            return Str(getText().data(), getText().size());
        } else {
            return "";
        }
    }

    /// \brief Check if token has any offset information
    bool hasOffset() const { return std::holds_alternative<int>(text); }
    /// \brief Check if token text is a view over real data
    bool hasData() const {
        return std::holds_alternative<std::stringView>(text);
    }
    int              getOffset() const { return std::get<int>(text); }
    std::stringView& getText() { return std::get<std::stringView>(text); }
    std::stringView const& getText() const {
        return std::get<std::stringView>(text);
    }
    /// Return character count for the token. If it does not contain any
    /// data return 0.
    int size() const {
        if (hasData()) {
            return getText().size();
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
            return std::distance(getText().data(), start);
        } else {
            return getText().size();
        }
    }
};


template <StringConvertible K>
std::ostream& operator<<(std::ostream& os, Token<K> const& value) {
    os << "Token<" << to_string(value.kind) << ">(";
    if (value.hasData()) {
        os << escape_literal(to_string(value.getText()));
    } else if (value.hasOffset()) {
        os << "offset:" << value.getOffset();
    } else {
        os << "?";
    }
    return os << ")";
}


template <typename K>
struct TokenGroup {
    dod::Store<TokenId<K>, Token<K>> tokens;
    Opt<std::stringView>             base;

    TokenGroup(Opt<std::stringView> base = std::nullopt) : base(base) {}
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

    Slice<int> toAbsolute(std::stringView view) const {
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
std::ostream& operator<<(std::ostream& os, LexerCommon<K> const& value) {
    return os << value.printToString();
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

struct LineColInfo {
    UnorderedMap<Slice<int>, int> lines;
    RangeTree<int>                lineRanges;

    int whichLine(int pos) const {
        auto range = lineRanges.query(pos);
        if (range.has_value() && lines.contains(range.value())) {
            return lines.at(range.value());
        } else {
            return -1;
        }
    }

    int whichColumn(int pos) const {
        auto range = lineRanges.query(pos);
        if (range.has_value()) {
            return pos - range.value().first;
        } else {
            return -1;
        }
    }

    Opt<Slice<int>> whichRange(int pos) { return lineRanges.query(pos); }

    LineColInfo() = default;
    LineColInfo(std::string const& text) {
        Vec<Slice<int>> slices;
        int             start = 0;
        for (int i = 0; i < text.size(); ++i) {
            if (text.at(i) == '\n') {
                slices.push_back(slice(start, i));
                start = i + 1;
            }
        }

        if (start != text.size()) {
            slices.push_back(slice1<int>(start, text.size() - 1));
        }

        for (int line = 0; line < slices.size(); ++line) {
            lines[slices.at(line)] = line;
        }

        lineRanges = RangeTree<int>(slices);
    }
};

template <typename K>
QDebug operator<<(QDebug os, LexerCommon<K> const& value) {
    std::string  str;
    std::ostream stream{&str};
    ColStream    col{stream};
    using P = typename LexerCommon<K>::PrintParams;
    value.print(col, P{});
    QDebugStateSaver saver{os};
    os.noquote() << str;
    return os;
}
