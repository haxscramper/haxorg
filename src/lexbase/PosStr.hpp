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

#include <hstd/stdlib/ColText.hpp>

#include <hstd/stdlib/sequtils.hpp>
#include <hstd/stdlib/charsets.hpp>
#include <hstd/stdlib/strformat.hpp>

#include <lexbase/Token.hpp>
#include <lexbase/Errors.hpp>
#include <QDebug>

/// Type constraint for types that can be passed into base methods of the
/// positional string checking such as `.at()` or `.skip()` as well as all
/// helper methods for better skipping such as `skipZeroOrMore`
template <typename S>
concept PosStrCheckable = (                                 //
    std::convertible_to<std::remove_cvref_t<S>, QChar>      //
    || std::convertible_to<std::remove_cvref_t<S>, CharSet> //
    || std::convertible_to<std::remove_cvref_t<S>, QString>);


/// \brief String wrapper with tracked position
struct PosStr {
    /// \brief Resolve absolute position to specific line and column
    struct PrintParams {
        int  maxTokens      = 10;
        bool withPos        = true;
        bool withEnd        = true;
        bool withColor      = true;
        int  startOffset    = 0;
        bool withSeparation = true;
    };


    void    print(ColStream& os, CR<PrintParams> params) const;
    void    print() const;
    void    print(ColStream& os) const;
    void    print(QTextStream& os, CR<PrintParams> params) const;
    void    print(CR<PrintParams> params) const;
    QString printToString(bool colored = false) const;
    QString printToString(PrintParams params, bool colored = false) const;

    struct SliceStartData {
        int pos;
    };

    /// \brief Pending slice content
    Vec<SliceStartData> slices;
    /// \brief Underlying string view
    QStringView view;
    /// \brief Absolute offset from the start of string view
    int pos = 0;


    /// \brief Consturct stirng using base view and starting position in
    /// the view
    PosStr(QStringView inView, int inPos = 0);

    /// \brief Consturct positional stirng using start view data and size
    /// of the string
    PosStr(const QChar* data, int count, int inPos = 0);

    /// \brief Consturct positional stirng using start view data and size
    /// of the string
    PosStr(QString const& str, int inPos = 0);

    /// \brief Convert underlying view to the string
    Str toStr() const;
    /// \brief Get size of hte underlying view
    int size() const;

    QStringView getOffsetView(int ahead = 0) const;

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
    void pushSlice();
    /// \brief Get current position in slice
    int getPos() const;
    /// \brief Assign new position in slice
    void setPos(int _pos);

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
    QStringView completeView(
        CR<SliceStartData> slice,
        Offset             offset = Offset()) const;

    /// \brief Create new positional substring
    PosStr sliceBetween(int start, int end) const;

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
    PosStr popSlice(Offset offset = {});


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

    PosStr slice(AdvanceCb cb, Offset offset = Offset());

    /// \brief Any chars left in the underlying view
    bool hasNext(int shift = 1) const;

    /// \brief Retract \arg count characters back
    void back(int count = 1);

    /// \brief Advance \arg count characters forward
    void next(int count = 1);

    /// \brief Get character at current position + \arg offset
    QChar get(int offset = 0) const;

    /// \brief No new characters left
    bool finished() const;
    /// \brief At the start of underlying view
    bool atStart() const;
    /// \brief Has exactly one character left
    bool beforeEnd() const;

    /// \brief Get current character and advance one step forward
    QChar pop();


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

    LineCol getLineCol();

    using CheckableSkip = Variant<CharSet, QString, QChar>;

    /// Skip \arg count steps  ahead if character at \arg offset is equal
    /// to \arg expected
    void skip(QChar expected, int offset = 0, int steps = 1);
    void skip(QString expected, int offset = 0);
    void skip(CR<CharSet> expected, int offset = 0, int steps = 1);
    void skipAny(CR<CheckableSkip> expected, int offset = 0);

    /// Check if the current position (with given \arg offset) contains
    /// expected character.
    bool at(QChar expected, int offset = 0) const;
    bool at(CR<CharSet> expected, int offset = 0) const;
    bool at(CR<QString> expected, int offset = 0) const;
    bool atAny(CR<CheckableSkip> expected, int offset = 0) const;


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

    void space(bool requireOne = false);

    void skipTo(const PosStrCheckable auto& item) {
        while (!finished() && !at(item)) {
            next();
        }
    }

    void skipBefore(const PosStrCheckable auto& item) {
        while (!finished() && !at(item, 1)) {
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
    bool isEmptyLine();

    /// Skip to the end of current line. After parsing cursor is positioned
    /// on the last character in the string, or closest newline.
    void skipToEOL();
    /// Skip to the start of the next line. After parsing cursor is
    /// positioning on the first character after the newline.
    void skipToNextLine();

    void skipToEOF();
    void skipPastEOF();
    void skipToSOF();

    /// Skip past the end of the line - that is, for `111\n2222` put cursor
    /// at the first `2` on the second line.
    void skipPastEOL();


    /*! If string is positioned on the empty line skip it, and return
    `true`. Otherwise return `false` */
    bool trySkipEmptyLine();
    /// Skip any number of horizontal whitespaces starting from the current
    /// position and return a number of spaces skipped.
    int skipIndent(const int& maxIndent = INT_MAX);

    void skipBeforeEOL();

    QString getAhead(Slice<int> slice) const;
    bool    hasAhead(
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
    int getIndent() const;
    int getColumn() const;

    bool hasMoreIndent(int const& indent, bool const& exactIndent = false)
        const;

    void skipIdent(CharSet const& chars = charsets::IdentChars);

    /// Create new QChar('unexpected character') error at the current
    /// string parsing position.
    UnexpectedCharError makeUnexpected(
        CR<QString> expected, //< What we expected to find?
        CR<QString> parsing   //< Description of the thing we are
                              // parsing at the moment
    );
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

void skipBalancedSlice(PosStr& str, CR<BalancedSkipArgs> args);

inline void skipBalancedSlice(PosStr& str, QChar open, QChar close) {
    skipBalancedSlice(
        str, {.openChars = CharSet{open}, .closeChars = CharSet{close}});
}

inline void skipPastEOF(PosStr& str) { str.skipPastEOF(); }
inline void skipPastEOL(PosStr& str) { str.skipPastEOL(); }
inline void skipToEOL(PosStr& str) { str.skipToEOL(); }
inline void skipCount(PosStr& str, int count) { str.next(count); }
inline void skipBefore(PosStr& str, QChar item) { str.skipBefore(item); }
inline void skipTo(PosStr& str, QChar item) { str.skipTo(item); }
inline void skipOne(PosStr& str, QChar item) { str.skip(item); }
inline void skipZeroOrMore(PosStr& str, QChar item) {
    str.skipZeroOrMore(item);
}
inline void skipOneOrMore(PosStr& str, QChar item) {
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

void skipStringLit(PosStr& str);

void skipDigit(Ref<PosStr> str);

inline QDebug operator<<(QDebug os, PosStr const& value) {
    QString     str;
    QTextStream stream{&str};
    ColStream   col{stream};
    value.print(col, {.withEnd = false});
    QDebugStateSaver saver{os};
    os.noquote() << str;
    return os;
}
