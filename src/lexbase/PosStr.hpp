#pragma once

#include <type_traits>
#include <variant>
#include <concepts>
#include <string>
#include <functional>
#include <memory>
#include <cassert>

#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Vec.hpp>

#include <hstd/stdlib/sequtils.hpp>
#include <hstd/stdlib/charsets.hpp>
#include <hstd/stdlib/strformat.hpp>

#include <lexbase/Token.hpp>
#include <lexbase/Errors.hpp>

/// Type constraint for types that can be passed into base methods of the
/// positional string checking such as `.at()` or `.skip()` as well as all
/// helper methods for better skipping such as `skipZeroOrMore`
template <typename S>
concept PosStrCheckable = (                                 //
    std::convertible_to<std::remove_cvref_t<S>, char>       //
    || std::convertible_to<std::remove_cvref_t<S>, CharSet> //
    || std::convertible_to<std::remove_cvref_t<S>, std::string>);


/// \brief Resolve relative location in the string view span into an
/// absolute line/column value
struct LocationResolver {
    /// \brief Pointer to the absolute base of the string being processed
    const char* absBase;

    /// \brief Get line and column information using absolute position in
    /// the string
    LineCol getLineCol(int pos) {
        // IMPLEMENT
        return {0, 0};
    }

    /// \brief  Get line and column using base of the string view and
    /// position inside of the view
    LineCol getLineCol(const char* base, int pos) {
        return getLineCol(pos);
    }
};

/// \brief String wrapper with tracked position
struct PosStr {
    /// \brief Resolve absolute position to specific line and column
    std::shared_ptr<LocationResolver> resolver;

    struct SliceStartData {
        int pos;
    };

    /// \brief Pending slice content
    Vec<SliceStartData> slices;
    /// \brief Underlying string view
    std::string_view view;
    /// \brief Absolute offset from the start of string view
    int pos = 0;


    /// \brief Consturct stirng using base view and starting position in
    /// the view
    PosStr(std::string_view inView, int inPos = 0)
        : view(inView), pos(inPos) {}

    /// \brief Consturct positional stirng using start view data and size
    /// of the string
    PosStr(const char* data, int count, int inPos = 0)
        : view(data, count), pos(inPos) {}

    /// \brief Consturct positional stirng using start view data and size
    /// of the string
    PosStr(std::string const& str, int inPos = 0)
        : view(str.data(), str.size()), pos(inPos) {}

    /// \brief Convert underlying view to the string
    Str toStr() const { return Str(view); }
    /// \brief Get size of hte underlying view
    int size() const { return view.size(); }

    std::string_view getOffsetView(int ahead = 0) const {
        return std::string_view(
            view.data() + pos + ahead, view.size() - (pos + ahead));
    }

    /// \brief Create new positional string using \arg s slice to cut into
    /// underlying view.
    template <typename A, typename B>
    PosStr at(CR<HSlice<A, B>> s, bool checkRange = true) const {
        const auto base         = getOffsetView();
        const auto [start, end] = getSpan(size(), s, checkRange);
        return PosStr(base.data() + start, end - start + 1);
    }

    template <typename A, typename B>
    PosStr operator[](CR<HSlice<A, B>> s) const {
#ifdef DEBUG
        return at(s, true);
#else
        return at(s, false);
#endif
    }

    /// \brief Push new pending slice starting at the current position
    void pushSlice() { slices.push_back({pos}); }
    /// \brief Get current position in slice
    int getPos() const { return pos; }
    /// \brief Assign new position in slice
    void setPos(int _pos) { pos = _pos; }

    /// \brief User callback to advance string position
    using AdvanceCb = std::function<void(PosStr&)>;
    /// \brief Slice pop offset parameters
    struct Offset {
        /// \brief Offset popped slice start by N characters
        int start;
        /// \brief Offset popped slice end by N characters
        int end;
        Offset(int _start = 0, int _end = 0) : start(_start), end(_end) {}
    };


    /// \brief Complete view with given offset parameters
    std::string_view completeView(
        CR<SliceStartData> slice,
        Offset             offset = Offset()) const {
        return std::string_view(
            view.data() + slice.pos + offset.start,
            pos - slice.pos + offset.end);
    }

    /// \brief Create new positional substring
    PosStr sliceBetween(int start, int end) const {
        return PosStr{
            std::string_view(view.data() + start, end - start + 1)};
    }

    /// \brief Create fake token starting with the current position
    template <typename K>
    Token<K> fakeTok(K kind, Offset offset = Offset()) {
        return Token(kind, pos);
    }

    /// \brief Pop last slice into a token object
    template <typename K>
    Token<K> popTok(K kind, Offset offset = Offset()) {
        return Token(kind, completeView(slices.pop_back_v(), offset));
    }

    /// \brief Pop pending slice into new positional substring
    PosStr popSlice(Offset offset = {}) {
        auto slice = slices.pop_back_v();
        return PosStr(completeView(slice, offset));
    }


    /// \brief User callback implemented as a regular function
    template <typename... Args>
    using AdvanceHandler = void(PosStr&, Args...);

    template <typename K, typename... Args>
    Token<K> tok(
        K                       kind,
        Offset                  offset,
        AdvanceHandler<Args...> cb,
        Args&&... args) {
        pushSlice();
        cb(*this, std::forward<Args>(args)...);
        return popTok(kind, offset);
    }

    template <typename... Args>
    PosStr slice(
        Offset                  offset,
        AdvanceHandler<Args...> cb,
        Args&&... args) {
        pushSlice();
        cb(*this, std::forward<Args>(args)...);
        return popSlice(offset);
    }

    template <typename K, typename... Args>
    Token<K> tok(K kind, AdvanceHandler<Args...> cb, Args&&... args) {
        pushSlice();
        cb(*this, std::forward<Args>(args)...);
        return popTok(kind);
    }

    template <typename... Args>
    PosStr slice(AdvanceHandler<Args...> cb, Args&&... args) {
        pushSlice();
        cb(*this, std::forward<Args>(args)...);
        return popSlice();
    }


    template <typename K>
    Token<K> tok(K kind, AdvanceCb cb, Offset offset = Offset()) {
        pushSlice();
        cb(*this);
        return popTok(kind, offset);
    }

    PosStr slice(AdvanceCb cb, Offset offset = Offset()) {
        pushSlice();
        cb(*this);
        return popSlice(offset);
    }

    /// \brief Any chars left in the underlying view
    bool hasNext(int shift = 1) const { return pos < view.size(); }

    /// \brief Retract \arg count characters back
    void back(int count = 1) {
        for (int i = 0; i < count; ++i) {
            --pos;
        }
    }

    /// \brief Advance \arg count characters forward
    void next(int count = 1) {
        for (int i = 0; i < count; ++i) {
            ++pos;
        }
    }

    /// \brief Get character at current position + \arg offset
    char get(int offset = 0) const {
        char result = '\0';
        if (pos + offset < view.size()) {
            result = view[pos + offset];
        }
        return result;
    }

    /// \brief No new characters left
    bool finished() const { return get() == '\0'; }
    /// \brief At the start of underlying view
    bool atStart() const { return pos == 0; }
    /// \brief Has exactly one character left
    bool beforeEnd() const { return !hasNext(1); }

    /// \brief Get current character and advance one step forward
    char pop() {
        char result = get();
        next();
        return result;
    }

    /// Check if the current position (with given \arg offset) contains
    /// expected character.
    bool at(char expected, int offset = 0) const {
        return get(offset) == expected;
    }

    bool at(CR<CharSet> expected, int offset = 0) const {
        return expected.contains(get(offset));
    }

    bool at(CR<std::string> expected, int offset = 0) const {
        for (const auto& [idx, ch] : enumerate(expected)) {
            if (get(offset + idx) != ch) {
                return false;
            }
        }
        return true;
    }

    int getSkip(const PosStrCheckable auto& item) const {
        int skip = 0;
        while (hasNext(skip)) {
            if (at(item, skip)) {
                return skip;
            } else {
                ++skip;
            }
        }
        return -1;
    }

    LineCol getLineCol() { return resolver->getLineCol(view.data(), pos); }

    void skip(char expected, int offset = 0, int count = 1) {
        if (get(offset) == expected) {
            next(count);
        } else {
            auto loc = getLineCol();
            throw UnexpectedCharError(
                "Unexpected character encountered during lexing: found "
                "'$#' but expected '$#' on $#:$#"
                    % to_string_vec(
                        get(offset), expected, loc.line, loc.column),
                loc);
        }
    }

    void skip(std::string expected) {
        if (at(expected)) {
            next(expected.size());
        } else {
            auto loc = getLineCol();
            throw UnexpectedCharError(
                "Unexpected character encountered during lexing: found "
                "'$#' but expected '$#' on $#:$#"
                    % to_string_vec(get(), expected, loc.line, loc.column),
                loc);
        }
    }

    void skip(CR<CharSet> expected, int offset = 0, int steps = 1) {
        if (expected.contains(get(offset))) {
            next(steps);
        } else {
            auto loc = getLineCol();
            throw UnexpectedCharError(
                "Unexpected character encountered during lexing: fonud "
                "'$#' but expected any of (char set) '$#' on $#:$#"
                    % to_string_vec(
                        get(offset), expected, loc.line, loc.column),
                loc);
        }
    }


    bool trySkip(const PosStrCheckable auto& item) {
        if (at(item)) {
            next();
            return true;
        } else {
            return false;
        }
    }

    void skipZeroOrMore(const PosStrCheckable auto& item) {
        while (at(item)) {
            next();
        }
    }

    void skipOneOrMore(const PosStrCheckable auto& item) {
        skip(item);
        skipZeroOrMore(item);
    }

    void space(bool requireOne = false) {
        if (requireOne) {
            skip(' ');
        }
        skipZeroOrMore(charsets::HorizontalSpace);
    }

    void skipTo(const PosStrCheckable auto& item) {
        while (!at(item)) {
            next();
        }
    }

    void skipBefore(const PosStrCheckable auto& item) {
        while (!at(item, 1)) {
            next();
        }
    }

    void skipPast(const PosStrCheckable auto& item) {
        while (at(item)) {
            next();
        }
    }

    /*!Check string is positioned on the empty line - `\n____\n` where `_`
    is any horizontal space character. Check can be executed at any
    position on the line.
    */
    bool isEmptyLine() {
        auto before = 0;
        while (at(charsets::HorizontalSpace, before)) {
            --before;
        }

        if (!at(before)) {
            return false;
        }

        auto after = 0;
        while (at(charsets::HorizontalSpace, after)) {
            ++after;
        }
        if (!at(after)) {
            return false;
        }
        return true;
    }

    /// Skip to the end of current line. After parsing cursor is positioned
    /// on the last character in the string, or closest newline.
    void skipToEOL() { skipTo(charsets::Newline); }

    void skipToEOF() { assert(false && "IMPLEMENT"); }
    void skipPastEOF() {
        skipToEOF();
        next();
    }
    void skipToSOF() { assert(false && "IMPLEMENT"); }

    /// Skip past the end of the line - that is, for `111\n2222` put cursor
    /// at the first `2` on the second line.
    void skipPastEOL() { skipPast(charsets::Newline); }

    /*! If string is positioned on the empty line skip it, and return
    `true`. Otherwise return `false` */
    bool trySkipEmptyLine() {
        bool result = isEmptyLine();
        if (result) {
            skipPastEOL();
        }
        return result;
    }

    /// Skip any number of horizontal whitespaces starting from the current
    /// position and return a number of spaces skipped.
    int skipIndent(const int& maxIndent = INT_MAX) {
        int result;
        while (at(charsets::HorizontalSpace)) {
            ++result;
            next();
            if (maxIndent <= result) {
                break;
            }
        }
        return result;
    }

    void skipBeforeEOL() { skipBefore(charsets::Newline); }

    bool hasAhead(
        const PosStrCheckable auto& item,
        int                         maxLimit = INT_MAX) {
        bool result;
        int  pos = 0;
        while (hasNext(pos) && pos < maxLimit) {
            if (at(item, pos)) {
                return true;
            }
            ++pos;
        };
        return false;
    }

    /// Get number of horizontal spaces starting from the current position.
    /// NOTE: if string is positioned on the newline or any other vertical
    /// space indentation is considered to be zero. `"\n____text" -> 0`,
    /// but `"____test" -> 4`
    int getIndent() const {
        int result;
        while (at(charsets::HorizontalSpace, result)) {
            ++result;
        }
        return result;
    }

    int getColumn() const {
        int result;
        int offset = 0;
        while (0 <= offset && !at('\n', offset)) {
            ++result;
            --offset;
        }

        return result;
    }

    bool hasMoreIndent(const int& indent, const bool& exactIndent = false)
        const {
        bool result;
        int  foundIndent = 0;
        while (at(charsets::HorizontalSpace, foundIndent)) {
            ++foundIndent;
            if (indent <= foundIndent) {
                break;
            }
        }

        if (foundIndent == indent) {
            return true;
        } else if (foundIndent <= indent) {
            return false;
        } else {
            return !exactIndent
                || at(charsets::HorizontalSpace, foundIndent);
        }
        return result;
    }


    void skipIdent(const CharSet& chars = charsets::IdentChars) {
        skipZeroOrMore(chars);
    }

    /// Create new 'unexpected character' error at the current string
    /// parsing position.
    UnexpectedCharError makeUnexpected(
        CR<std::string> expected, //< What we expected to find?
        CR<std::string> parsing   //< Description of the thing we are
                                  // parsing at the moment
    ) {
        auto loc = getLineCol();
        return UnexpectedCharError(
            "Unexpected character encountered during lexing: found '$#' "
            "but expected $# while parsing on $#:$#"
                % to_string_vec(
                    get(), expected, parsing, loc.line, loc.column),
            loc);
    }
};


struct BalancedSkipArgs {
    const CharSet& openChars;
    const CharSet& closeChars;
    const CharSet& endChars = charsets::Newline;
    const bool&    doRaise  = true;
    /// Allow use of `\` character to escape special characters
    const bool& allowEscape = true;
    /// whether opening brace had already been skipped by the wrapping
    /// lexer logic. Can be used to provide custom handling for the
    /// opening element. Together with `consumeLast` allow for a fully
    /// custom handling of the outermost wrapping braces.
    const bool& skippedStart = false;
    /// what to do with the wrapping tokens of a balanced range. By
    /// default they are also skipped, but if lexer needs to handle
    /// this case separately you can set this argument to false.
    const bool& consumeLast = true;
};

inline void skipBalancedSlice(PosStr& str, CR<BalancedSkipArgs> args) {
    auto fullCount = args.skippedStart ? 1 : 0;
    int  count[sizeof(char) * 8];
    while (str.hasNext()) {
        if (args.allowEscape && str.at('\\')) {
            str.next();
            str.next();
        } else if (str.at(args.openChars)) {
            ++fullCount;
            ++count[ord(str.pop())];
        } else if (str.at(args.closeChars)) {
            --fullCount;
            if ((0 < fullCount) || args.consumeLast) {
                --count[ord(str.pop())];
            }
            if (fullCount == 0) {
                return;
            }
        } else if (str.at(args.endChars)) {
            if (0 < fullCount) {
                if (args.doRaise) {
                    throw str.makeUnexpected(
                        "balanced opening/closing pair",
                        "balanced opening/closing pair");
                } else {
                    return;
                }
            } else {
                return;
            }
        } else {
            str.next();
        }
    }
    if (0 < fullCount && args.doRaise) {
        throw str.makeUnexpected(
            "balanced opening/closing pair",
            "balanced opening/closing pair");
    }
}

inline void skipBalancedSlice(PosStr& str, char open, char close) {
    skipBalancedSlice(
        str, {.openChars = CharSet{open}, .closeChars = CharSet{close}});
}

inline void skipPastEOF(PosStr& str) { assert(false && "IMPLEMENT"); }
inline void skipPastEOL(PosStr& str) { str.skipPastEOL(); }
inline void skipToEOL(PosStr& str) { str.skipToEOL(); }
inline void skipCount(PosStr& str, int count) { str.next(count); }
inline void skipBefore(PosStr& str, char item) { str.skipBefore(item); }
inline void skipTo(PosStr& str, char item) { str.skipTo(item); }
inline void skipOne(PosStr& str, char item) { str.skip(item); }
inline void skipZeroOrMore(PosStr& str, char item) {
    str.skipZeroOrMore(item);
}
inline void skipOneOrMore(PosStr& str, char item) {
    str.skipOneOrMore(item);
}

void skipBefore(PosStr& str, const PosStrCheckable auto& item) {
    str.skipBefore(item);
}
void skipOneOrMore(PosStr& str, const PosStrCheckable auto& item) {
    str.skipOneOrMore(item);
}
void skipZeroOrMore(PosStr& str, const PosStrCheckable auto& item) {
    str.skipZeroOrMore(item);
}
void skipTo(PosStr& str, const PosStrCheckable auto& item) {
    str.skipTo(item);
}
void skipPast(PosStr& str, const PosStrCheckable auto& item) {
    str.skipPast(item);
}
void skipOne(PosStr& str, const PosStrCheckable auto& item) {
    str.skip(item);
}

inline void skipStringLit(PosStr& str) {
    auto found = false;
    str.next();
    while (!found) {
        found = str.at('"') && !str.at('\\', -1);
        str.next();
    }
}

inline void skipDigit(Ref<PosStr> str) {
    if (str.at('-')) {
        str.next();
    }
    if (str.at("0x")) {
        str.next(2);
        str.skip(charsets::HexDigits);
        str.skipZeroOrMore(charsets::HexDigits + CharSet{'_'});
    } else if (str.at("0b")) {
        str.next(2);
        str.skip(CharSet{'0', '1'});
        str.skipZeroOrMore(CharSet{'0', '1'});
    } else {
        str.skip(charsets::Digits);
        str.skipZeroOrMore(charsets::Digits + CharSet{'_', '.'});
    }
}
