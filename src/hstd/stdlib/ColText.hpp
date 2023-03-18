#pragma once

#include <hstd/system/basic_typedefs.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Array.hpp>

#include <locale>
#include <codecvt>

struct TermColorBgFull {
    u8 color;
};

struct TermColorFgFull {
    u8 color;
};

enum class TermColorBg8Bit : u8
{
    Black = 1, /// black
    Red,       /// red
    Green,     /// green
    Yellow,    /// yellow
    Blue,      /// blue
    Magenta,   /// magenta
    Cyan,      /// cyan
    White,     /// white
    EightBit,  /// 256-color (not supported, see `enableTrueColors`
               /// instead.)
    Default    /// default terminal foreground color
};

template <>
inline TermColorBg8Bit low() {
    return TermColorBg8Bit::Black;
}

template <>
inline TermColorBg8Bit high() {
    return TermColorBg8Bit::Default;
}

enum class TermColorFg8Bit : u8
{
    Black = 1, /// black
    Red,       /// red
    Green,     /// green
    Yellow,    /// yellow
    Blue,      /// blue
    Magenta,   /// magenta
    Cyan,      /// cyan
    White,     /// white
    EightBit,  /// 256-color (not supported, see `enableTrueColors`
               /// instead.)
    Default    /// default terminal foreground color
};

template <>
inline TermColorFg8Bit low() {
    return TermColorFg8Bit::Black;
}

template <>
inline TermColorFg8Bit high() {
    return TermColorFg8Bit::Default;
}

enum class Style : u8
{
    Bright = 1,   //! bright text
    Dim,          //! dim text
    Italic,       //! italic (or reverse on terminals not supporting)
    Underscore,   //! underscored text
    Blink,        //! blinking/bold text
    BlinkRapid,   //! rapid blinking/bold text (not widely supported)
    Reverse,      //! reverse
    Hidden,       //! hidden text
    Strikethrough //! strikethrough
};

template <>
inline Style low() {
    return Style::Bright;
}
template <>
inline Style high() {
    return Style::Strikethrough;
}

inline bool isDefault(TermColorFg8Bit bg) { return (u8)bg == 0; }
inline bool isDefault(TermColorBg8Bit bg) { return (u8)bg == 0; }


struct ColStyle {
    TermColorFg8Bit fg = (TermColorFg8Bit)0; /*!Foreground color */
    TermColorBg8Bit bg = (TermColorBg8Bit)0; /*!Background */
    IntSet<Style> style; /*!Other styling options (italic, underline, dim,
                         bright etc.) */

    inline ColStyle() {}
    inline ColStyle(TermColorFg8Bit fg) : fg(fg) {}
    inline ColStyle(TermColorBg8Bit bg) : bg(bg) {}
    inline ColStyle(Style _style) : style(IntSet<Style>{_style}) {}

    void operator+=(CR<ColStyle> other) {
        style = style + other.style;
        fg    = isDefault(fg) ? other.fg : fg;
        bg    = isDefault(bg) ? other.bg : bg;
    }

    ColStyle operator+(CR<ColStyle> other) const {
        ColStyle result = *this;
        result += other;
        return result;
    }
};


#define ESC_PREFIX "\033["

struct ColRune;
struct ColText;

/*! Create ansi escape sequence with given code */
inline QString ansiEsc(int code) {
    return ESC_PREFIX + QString::number(code) + "m";
}


/*! Create ansi escape sequence with given terminal color */
QString ansiEsc(const TermColorFg8Bit& col);

/*! Create ansi escape sequence with given terminal color */
QString ansiEsc(const TermColorBg8Bit& col);

/// Create ansi escape sequence with given style. `open` controls whether
/// styling sequence is used for open or for close
QString ansiEsc(const Style& style, const bool& open);

/// Generate ansi escape sequences to transition from style `s1` to style
/// `s2`
Str ansiDiff(const ColStyle& s1, const ColStyle& s2);


/// Convert colored rune to regular QString, with ansi escape
/// sequences. `color` controls whether styling is going to be applied or
/// not.
QString to_string(const ColRune& rune, const bool& color = true);

/// Convert sequence of colored runes to the QString, with ansi escape
/// sequences in. `color` controls whether styling is going to be applied
/// or not.
QString to_colored_string(
    const Vec<ColRune>& runes,
    const bool&         color = true);


/// NOTE yes, I know it is very inefficient, but it is not a HPC solution
/// in any case, so I'm trading current development productivity (not
/// spending time on a more efficient range-based solution) over runtime
/// performance. The API must stay the same in any case, so improved
/// version can be implemented in the future.
struct ColRune {
    QChar    rune = U' ';
    ColStyle style;
    inline ColRune(char ch) : rune(ch) {}
    inline ColRune(CR<ColStyle> style, QChar rune)
        : rune(rune), style(style) {}
};

struct ColText : Vec<ColRune> {
    using Base = Vec<ColRune>;
    using Base::append;

    QString toString(bool colored = true) {
        return to_colored_string(*this, colored);
    }

    ColText() = default;
    ColText(CR<ColStyle> style, CR<QString> text) {
        for (const auto& ch : text) {
            push_back(ColRune(style, ch));
        }
    }

    ColText(CR<QString> text) : ColText(ColStyle{}, text) {}

    ColText(CR<ColStyle> style, QChar text)
        : Vec<ColRune>({ColRune(style, text)}) {}


    template <typename T>
    explicit ColText(CR<T> it) : ColText(ColStyle{}, to_string(it)) {}

    template <typename T>
    explicit ColText(CR<ColStyle> style, CR<T> it)
        : ColText(style, to_string(it)) {}

    inline ColText operator<<=(int n) const { return leftAligned(n); }
    inline ColText operator>>=(int n) const { return rightAligned(n); }

    inline void append(int repeat, ColRune c) {
        for (int i = 0; i < repeat; ++i) {
            push_back(c);
        }
    }

    inline ColText rightAligned(int n, ColRune c = ColRune{' '}) const {
        ColText res;
        if (size() < n) {
            res.append(n - size(), c);
        }
        res.append(*this);
        return res;
    }

    inline ColText leftAligned(int n, ColRune c = ColRune{' '}) const {
        auto s = *this;
        while (s.size() < n) {
            s.push_back(c);
        }
        return s;
    }
};

inline QTextStream& operator<<(QTextStream& os, ColText const& value) {
    return os << to_colored_string(value, true);
}


using ColRuneLine = Vec<ColRune>;
using ColRuneGrid = Vec<ColRuneLine>;

template <typename T>
concept ColModifier = IsAnyOf<
    std::remove_cvref<T>,
    TermColorBg8Bit,
    TermColorFg8Bit,
    IntSet<Style>,
    Style,
    ColStyle>;

struct ColStream;
struct StreamState {
    ColStream& stream;
    ColStyle   start;
    StreamState(ColStream& stream);
    ~StreamState();
};

struct ColStream : public ColText {
    QTextStream* ostream = nullptr;
    bool         buffered;
    bool         colored = true;

    CR<ColText> getBuffer() const {
        return *static_cast<ColText const*>(this);
    }

    ColStream() : buffered(true){};
    ColStream(QTextStream& os) : ostream(&os), buffered(false) {}

    // clang-format off
    ColStream& red() { active.fg = TermColorFg8Bit::Red; return *this; }
    ColStream& blue() { active.fg = TermColorFg8Bit::Blue; return *this; }
    ColStream& green() { active.fg = TermColorFg8Bit::Green; return *this; }
    ColStream& yellow() { active.fg = TermColorFg8Bit::Yellow; return *this; }
    ColStream& cyan() { active.fg = TermColorFg8Bit::Cyan; return *this; }
    ColStream& magenta() { active.fg = TermColorFg8Bit::Magenta; return *this; }
    ColStream& white() { active.fg = TermColorFg8Bit::White; return *this; }
    // clang-format on

    ColStyle    active;
    ColStream&  indent(int level);
    ColStyle    end() const { return ColStyle{}; }
    StreamState snap() { return StreamState(*this); }
    void        write(ColText const& text) {
        if (buffered) {
            append(text);
        } else {
            (*ostream) << to_colored_string(text, colored);
        }
    }
};


inline StreamState::StreamState(ColStream& stream) : stream(stream) {
    start = stream.active;
}

inline StreamState::~StreamState() { stream.active = start; }


inline ColStream& ColStream::indent(int level) {
    append(ColText(ColStyle{}, repeat(" ", level)));
    return *this;
}

inline ColStream& operator<<(ColStream& os, ColStream& value) {
    return os;
}

inline ColStream& operator<<(ColStream& os, ColStyle const& value) {
    os.active = value;
    return os;
}

inline ColStream& operator<<(ColStream& os, TermColorFg8Bit const& value) {
    return os << os.active + ColStyle(value);
}

inline ColStream& operator<<(ColStream& os, TermColorBg8Bit const& value) {
    return os << os.active + ColStyle(value);
}

inline ColStream& operator<<(ColStream& os, Style const& value) {
    return os << os.active + ColStyle(value);
}

inline ColStream& operator<<(ColStream& os, QChar const& value) {
    os.write(ColText(os.active, value));
    return os;
}

inline ColStream& operator<<(ColStream& os, QString const& value) {
    os.write(ColText(os.active, value));
    return os;
}

inline ColStream& operator<<(ColStream& os, ColText const& value) {
    os.append(value);
    return os;
}


template <typename T>
ColStream& operator<<(ColStream& os, CR<T> const& value)
    requires StringStreamable<T>
{
    QString     out;
    QTextStream string{&out};
    string << value;
    return os << out;
}

template <typename T>
ColText operator+(CR<ColText> text, CR<T> other) {
    ColStream s;
    s << text << other;
    return s.getBuffer();
}


template <typename T>
ColText operator+(CR<T> other, CR<ColText> text) {
    ColStream s;
    s << other << text;
    return s.getBuffer();
}

enum class HDisplayVerbosity : u8
{
    Minimal,
    Normal,
    Verbose,
    DataDump,
};

enum class HDisplayFlag : u8
{
    Colored,
    PositionIndexed,
    PathIndexed,
    UnicodeNewlines,
    UnicodePPrint,
    WithRanges,
    SpellEmptyStrings,
    UseBin,
    UseDecimal,
    UseHex,
    TrimPrefixZeros,
    SplitNumbers,
    UseCommas,
    UseQuotes
};

template <>
inline HDisplayFlag low() {
    return HDisplayFlag ::Colored;
}
template <>
inline HDisplayFlag high() {
    return HDisplayFlag ::UseQuotes;
}

struct HDisplayOpts {
    IntSet<HDisplayFlag> flags = IntSet<HDisplayFlag>{
        HDisplayFlag::Colored,
        HDisplayFlag::PositionIndexed,
        HDisplayFlag::SpellEmptyStrings,
        HDisplayFlag::UseCommas,
        HDisplayFlag::UseQuotes,
        HDisplayFlag::TrimPrefixZeros};
    int  indent      = 0;
    int  maxDepth    = 120;
    int  maxLen      = 30;
    bool quoteIdents = false; /// Add quotes around stings that are valid
                              /// identifirers
    bool              newlineBeforeMulti = true;
    HDisplayVerbosity verbosity          = HDisplayVerbosity::Normal;
    bool              dropPrefix         = false;


    HDisplayOpts& cond(HDisplayFlag flag, bool doAdd) {
        if (doAdd) {
            flags.incl(flag);
        } else {
            flags.excl(flag);
        }
        return *this;
    }
    HDisplayOpts& incl(HDisplayFlag flag) {
        flags.incl(flag);
        return *this;
    }
    HDisplayOpts& excl(HDisplayFlag flag) {
        flags.excl(flag);
        return *this;
    }
    HDisplayOpts& with(IntSet<HDisplayFlag> flag) {
        flags = flag;
        return *this;
    }
};

template <typename T>
ColStream& hshow(
    ColStream&       s,
    CR<T>            value,
    CR<HDisplayOpts> opts = HDisplayOpts{});

template <StringConvertible T>
ColStream& hshow(
    ColStream&       s,
    CR<T>            value,
    CR<HDisplayOpts> opts = HDisplayOpts{}) {
    return s << to_string(value);
}


template <>
inline ColStream& hshow(
    ColStream&       os,
    CR<Str>          value,
    CR<HDisplayOpts> opts) {
    bool first = true;
    if (opts.flags.contains(HDisplayFlag::UseQuotes)) {
        for (Str const& it : visibleUnicodeName(value)) {
            if (!first) {
                os << " ";
            }
            first = false;
            os << Str("'") + it + Str("'");
        }
    } else {
        for (const auto& it : visibleUnicodeName(value)) {
            os << it;
        }
    }

    return os;
}

template <>
inline ColStream& hshow(
    ColStream&       os,
    CR<QStringView>  value,
    CR<HDisplayOpts> opts) {
    if (value.data() == nullptr) {
        return os << os.red() << "nil" << os.end();
    } else {
        return hshow(os, Str(to_string(value)), opts);
    }
}


template <StringConvertible T>
ColText hshow(CR<T> value, CR<HDisplayOpts> opts = HDisplayOpts{}) {
    ColStream out;
    hshow(out, value, opts);
    return out.getBuffer();
}


template <typename T>
ColText join(CR<ColText> separator, CR<T> container) {
    ColStream out;
    bool      first = true;
    for (const auto& item : container) {
        if (!first) {
            out << separator;
        }
        first = false;
        out << item;
    }
    return out.getBuffer();
}

#if false

/*!Convert foreground color to human-readble representation */
QString operator<<(QTextStream& os, const TermColorFg8Bit& fg) {
    os << fg;
    QString result = QString::number(static_cast<u8>(fg));
    if (static_cast<u8>(fg) < 15) {
        result.append((
            (R"(($1))")
            % (toStr(ForegroundColor((
                (low(ForegroundColor).uint8) + (static_cast<u8>(fg))))))));
    }
    return result;
}

/*!Convert background color to human-readable representation */
QString operator<<(QTextStream& os, const TermColorBg8Bit& bg) {
    QString result;
    result = toStr(static_cast<u8>(bg));
    if (((static_cast<u8>(bg)) < (15))) {
        result.append((
            (R"(($1))")
            % (toStr(BackgroundColor((
                (low(BackgroundColor).uint8) + (static_cast<u8>(bg))))))));
    }
    return result;
}

/*!Color equality comparison */
bool operator==(
    const((TermColorBg8Bit) | (TermColorFg8Bit))
        & a const((TermColorBg8Bit) | (TermColorFg8Bit)) & b, ) {
    bool result;
    ((a.uint8) == (b.uint8));
    return result;
}

/*! Convert `std/terminal.BackgroundColor` to terminal background color */
TermColorBg8Bit termColor(const BackgroundColor& bg) {
    TermColorBg8Bit result;
    if (((bg) != (bgDefault))) {
        result = TermColorBg8Bit(
            ((static_cast<u8>(bg)) - (low(BackgroundColor).uint8)));
    }
    return result;
}

/*!Convert `std/terminal.ForegroundColor` to terminal foreground color */
TermColorFg8Bit termColor(const ForegroundColor& bg) {
    TermColorFg8Bit result;
    if (bg != fgDefault) {
        result = TermColorFg8Bit(
            ((static_cast<u8>(bg)) - (low(ForegroundColor).uint8)));
    }
    return result;
}

/*!Compare for equality with `std/terminal` color */
bool operator==(const TermColorFg8Bit& f1, const ForegroundColor& f2) {
    bool result;
    ((termColor(f2)) == (f1));
    return result;
};

/*!Compare for equality with `std/terminal` color */
bool operator==(const TermColorBg8Bit& f1, const BackgroundColor& f2) {
    bool result;
    ((termColor(f2)) == (f1));
    return result;
}

/*!Initialize color style with given options */
ColStyle initColStyle(
    const ForegroundColor& fg    = fgDefault,
    const BackgroundColor& bg    = bgDefault,
    const set<Style>&      style = {}) {
    ColStyle result;
    ColStyle{
        .fg    = fg.termColor,
        .bg    = bg.termColor,
        .style = style,
    };
    return result;
}

/*!Convert to style with only foreground option set */
ColStyle colStyle(const ForegroundColor& fg) {
    ColStyle result;
    ColStyle{
        .fg = fg.termColor,
    };
    return result;
}

/*!Convert to style with only background option set */
ColStyle colStyle(const BackgroundColor& bg) {
    ColStyle result;

    ;
    ColStyle{
        .bg = bg.termColor,
    };
    return result;
};

ColStyle colStyle(const TermColorFg8Bit& fg) {
    ColStyle result;
    /*!Convert to style with only foreground color set
     */
    ;
    ColStyle{
        .fg = fg,
    };
    return result;
};

ColStyle colStyle(const TermColorBg8Bit& bg) {
    ColStyle result;
    /*!Convert to style with only background color set
     */
    ;
    ColStyle{
        .bg = bg,
    };
    return result;
};

ColStyle colStyle(const set<Style>& style) {
    ColStyle result;
    /*!Convert to style with given set of styling options
     */
    ;
    ColStyle{
        .style = style,
    };
    return result;
};

ColStyle colStyle(const Style& style) {
    ColStyle result;
    /*!Convert to style with single styling option set
     */
    ;
    ColStyle{
        .style = {style},
    };
    return result;
};

ColStyle colStyle(const ColStyle& style) {
    ColStyle result;
    /*!Passthrough proc, used to simplify mapping of the `ColModifier`
    typeclass to the `ColStyle` object.
    */
    ;
    style;
    return result;
};

ColRune default(const typedesc<ColRune>& rune) {
    ColRune result;
    /*!Default value of the colored rune
     */
    ;
    ColRune{
        .style = initColStyle(),
    };
    return result;
};

ColStyle default(const typedesc<ColStyle>& style) {
    ColStyle result;
    /*!Default value of the color style
     */
    ;
    ColStyle{
        .fg = fgDefault.termColor(),
        .bg = bgDefault.termColor(),
    };
    return result;
};

Rune uc(const static<Str>& s) {
    Rune result;
    /*!Create single unicode rune from QString literal - `uc"⮰"`
     */
    ;
    runeAt(s, 0);
    return result;
};

bool isDefault(const((TermColorFg8Bit) | (TermColorBg8Bit)) & col) {
    bool result;
    /*!Check if foreground or background color have default value
     */
    ;
    ((col.uint8) == (0));
    return result;
};

void operator+=(ColStyle& s1, const ColStyle& s2) {
    /*!Merge two styling optons, overriding target if the source has
    non-default value for background or foreground colors
    */
    ;
    s1.style = ((s1.style) + (s2.style));
    ;
    s1.fg = else { s2.fg.isDefault() }
    else {
        s2.fg;
    };
    ;
    s1.bg = else { s2.bg.isDefault() }
    else {
        s2.bg;
    };
    ;
};

ColStyle operator+(const ColStyle& s1 const ColStyle& s2, ) {
    ColStyle result;
    /*!Merge two styles. Second one overrides colors if they are
     * non-default.
     */
    ;
    result = s1;
    ;
    ((result) += (s2));
    return result;
};

ColStyle operator+(
    const ColModifier&                a,
    const /* distinct */ ColModifier& b) {
    ColStyle result;
    /*!Merge two color modifiers and generate color style
    (`fgRed+{styleUnderline}`)
    */
    ;
    ((colStyle(a)) + (colStyle(b)));
    return result;
};

ColRune toColRune(const Rune& rune, const ColStyle& style) {
    ColRune result;
    /*!Convert colered rune to styled one with `style`
     */
    ;
    ColRune{
        .rune  = rune,
        .style = style,
    };
    return result;
};

ColText toColText(
    const Str&      text,
    const ColStyle& style = default(ColStyle)) {
    ColText result;
    /*!Convert text colored one using given style
     */
    ;
    for (const auto rune : runes(text)) {
        result.append(toColRune(rune, style));
    };
    return result;
};

ColText operator+(const Str& text, const ColModifier& style) {
    ColText result;
    /*!Convert text colored one using given style
     */
    ;
    toColText(text, colStyle(style));
    return result;
};

ColRune operator+(const char& ch, const ColModifier& style) {
    ColRune result;
    /*!Convert character to colored rune with given style
     */
    ;
    toColRune(Rune(ch), colStyle(style));
    return result;
};

ColRune operator+(const Rune& r, const ColModifier& style) {
    ColRune result;
    /*!Convert rune to colored one with given style modifier
     */
    ;
    toColRune(r, colStyle(style));
    return result;
};

void setStyle(
    ColText& text,
    const ColStyle& new,
    const bool& override = true) {
    /*!Set style for all runes in text, optionally overriding non-defaulted
    values (or resetting them completely)
    */
    ;
    for (const auto ch : mitems(text.runes)) {
        if (override) {
            ch.style.fg = new.fg;
            ;
            ch.style.bg = new.bg;
            ;
            ch.style.style = new.style;
            ;
        } else {
            if (isDefault(ch.style.fg)) {
                ch.style.fg = new.fg;
                ;
            };
            if (isDefault(ch.style.bg)) {
                ch.style.bg = new.bg;
                ;
            };
            for (const auto s : new.style) {
                ch.style.style.incl(s);
            };
        };
    };
};

ColText operator+(const ColText& text, const ColModifier& style) {
    ColText result;
    /*!Apply styling options to colored text
     */
    ;
    result = text;
    ;
    result.setStyle(colStyle(style), false);
    return result;
};

ColText toColText(const ColText& text) {
    ColText result;
    /*!Passthrough implementation of converter to colored text
     */
    ;
    text;
    return result;
};

ColText toColText(const ColRune& rune) {
    ColText result;
    /*!Convert single rune to colored text
     */
    ;
    ColText { .runes = (@({rune})), };
    return result;
};

ColText clt(const Str& str) {
    ColText result;
    /*!Shorthand to construct colored text QString with default value
    (`clt"default"`)
    */
    ;
    ((str) + (default(ColStyle)));
    return result;
};

ColText clt(const char& ch) {
    ColText result;
    /*!Shorthand to construct colored text with single character
     */
    ;
    toColText(((ch) + (default(ColStyle))));
    return result;
};

ColRune clr(const char& ch) {
    ColRune result;
    /*!Construct colored rune with default styling
     */
    ;
    ((ch) + (default(ColStyle)));
    return result;
};

bool isNewline(const ColRune& rune) {
    bool result;
    /*!Check if rune is a newline rune
     */
    ;
    ((rune.rune) == (Rune(int('\n'))));
    return result;
};

ColText toLower(const ColText& text) {
    ColText result;
    /*!Convert colored text to lowercase
     */
    ;
    result = text;
    ;
    for (const auto rune : mitems(result.runes)) {
        rune.rune = toLower(rune.rune);
        ;
    };
    return result;
};

ColText toUpper(const ColText& text) {
    ColText result;
    /*!Convert colored text to uppercase
     */
    ;
    result = text;
    ;
    for (const auto rune : mitems(result.runes)) {
        rune.rune = toUpper(rune.rune);
        ;
    };
    return result;
};

/*! Align colored text left, using padding rune to fill in missing elements
 */
ColText alignLeft(
    const ColText& text,
    const int&     length,
    const ColRune& padding = clr(' ')) {
    ColText result;
    result = text;
    if (((result.len) < (length))) {
        result.runes.append(padding.repeat(((length) - (result.len))));
    }
    return result;
};

/*! Center colored text, using padding rune to fill in missing elements */
ColText alignCenter(
    const ColText& text,
    const int&     length,
    const ColRune& padding = clr(' ')) {
    ColText result;
    if (result.len() < length) {
        const auto diff  = ((length) - (text.len()));
        const auto left  = ((diff)div(2));
        const auto right = ((diff) - (left));
        result.runes.append(padding.repeat(left));
        result.append(text.runes);
        result.runes.append(padding.repeat(right));
    }
    return result;
}

/*!Align colored text right, using padding rune to fill in missing elements
 */
ColText alignRight(
    const ColText& text,
    const int&     length,
    const ColRune& padding = clr(' ')) {
    ColText result;
    if (text.size() < length) {
        result.runes.append(padding.repeat(length - text.size()));
    }
    result.runes.append(text.runes);
    return result;
}

bool operator==(const ColRune& rune, const char& ch) {
    bool result;
    /*!Compare rune for equality with regular character
     */
    ;
    ((rune.rune) == (Rune(int(ch))));
    return result;
};

bool hasNewline(const ColText& text) {
    bool result;
    /*!Check if colored text has any newlines
     */
    ;
    for (const auto rune : text.runes) {
        if (isNewline(rune)) {
            return true;
            ;
        };
    };
    return result;
};

bool hasOnlyTailNewline(const ColText& text) {
    bool result;
    /*!Check if colored text has only trailing newlines and no in-body ones
     */
    ;

    auto onTail = true;
    ;
    ;
    result = true;
    ;
    for (const auto rune : ritems(text)) {
        if (isNewline(rune)) {
            if ((!(onTail))) {
                return false;
                ;
            };
        } else {
            onTail = false;
            ;
        };
    };
    return result;
};

void newline(ColText& text) {
    /*!Append newline to the colored text
     */
    ;
    text.runes.append(((uc(R"(\n)")) + (default(ColStyle))));
};

Vec<ColRuneLine> lines(const ColText& text) {
    Vec<ColRuneLine> result{};
    /*!Iterate over lines of the colored text
     */
    ;

    ColRuneLine buf;
    ;
    ;
    for (const auto rune : text.runes) {
        if (rune.isNewline) {
            result.push_back(buf);
            buf.setLen(0);
        } else {
            buf.append(rune);
        };
    };
    if (((buf.len()) > (0))) {
        result.push_back(buf);
    };
    return result;
};

int width(const ColText& text) {
    int result;
    /*!Get maximum width (line length) of the colored text
     */
    ;

    auto buf = 0;
    ;
    ;
    for (const auto rune : text.runes) {
        if (rune.isNewline) {
            result = max(buf, result);
            ;
            buf = 0;
            ;
        } else {
            += buf;
        };
    };
    if (((buf) > (0))) {
        return buf;
        ;
    };
    return result;
};

void add(ColText& colored, const ColText& other) {
    /*!Add one colored text block to another
     */
    ;
    colored.runes.append(other.runes);
};

void add(ColText& colored, const ColRuneLine& other) {
    /*!Add colored rune line (sequence of runes) to colored text
     */
    ;
    colored.runes.append(other);
};

void add(ColText& colored, const ColRune& rune) {
    /*!Add colored rune to the text
     */
    ;
    colored.runes.append(rune);
};

void add(ColText& colored, const((QString) | (char)) & ch) {
    /*!Add QString or character with default style to colored text,
     */
    ;
    colored.append(((ch) + (default(ColStyle))));
};

ColText indent(
    const ColText& str,
    const int&     count,
    const int&     indentAfter = -1,
    const ColText& indent      = clt(R"( )"),
    const ColText& prefix      = clt(R"()")) {
    ColText result;
    /*!Indent colored text lines by `count` repetitions of the `indent`
    text. Add `prefix` before each line.

    - `indentAfter` - first line to start applying indentation after
      (defaults to `-1`, so indentation is applied to the whole text). Can
      be used to allow `[header, line, line]` text to be easily processed
    */
    ;

    auto idx = 0;
    ;
    ;
    for (const auto line : lines(str)) {
        if (((idx) <= (indentAfter))) {
            result.append(line);
        } else {
            result.newline();
            for (int _ = 0; _ < ((count) - (prefix.len())); ++i) {
                result.append(indent);
            };
            result.append(prefix);
            result.append(line);
        };
        += idx;
    };
    return result;
};

ColText join(const Vec<ColText>& text, const ColText& sep) {
    ColText result;

    auto first = true;
    ;
    ;
    for (const auto item : text) {
        if ((!(first))) {
            result.append(sep);
        };
        first = false;
        ;
        result.append(item);
    };
    return result;
};

ColText stripLines(
    const ColText&   text,
    const bool&      leading = false,
    const bool&      trails  = true,
    const set<char>& chars   = {' '}) {
    ColText result;
    /*!Strip character from each line in text
     */
    ;

    auto idx = 0;
    ;
    ;
    for (const auto line : lines(text)) {

        auto start = 0;
        ;
        ;
        if (leading) {
            while (
                ((((((int(line[start].rune)) <= (ord(high(char)))))
                   && (((char(line[start].rune))in(chars)))))
                 && (((start) < (high(line)))))) {
                += start;
            };
        };

        auto final = high(line);
        ;
        ;
        if (trails) {
            while (
                ((((((int(line[final].rune)) <= (ord(high(char)))))
                   && (((char(line[final].rune))in(chars)))))
                 && (((0) < (final))))) {
                -= final;
            };
        };
        if (((((((start) == (final)))
               && (((int(line[final].rune)) <= (ord(high(char)))))))
             && (((char(line[final].rune))in(chars))))) {
            if (((idx) > (0))) {
                result.append(clt(R"(\n)"));
            };
        } else {
            if (((idx) > (0))) {
                result.append(clt(R"(\n)"));
            };
            result.append(line[rangeIncl(start, final)]);
        };
        += idx;
    };
    return result;
};

ColText operator&(const ColText& t1, const ColText& t2) {
    ColText result;
    /*!Concatenate two colored text blocks
     */
    ;
    result = t1;
    ;
    result.runes.append(t2.runes);
    return result;
};

ColText operator&(const ColText& t1, const Str& t2) {
    ColText result;
    /*!Concatenate colored text and regular QString (with default
     * style)
     */
    ;
    result = t1;
    ;
    result.append(clt(t2));
    return result;
};

ColText operator&(const Str& t1, const ColText& t2) {
    ColText result;
    /*!Concatenate colored text and regular QString (with default
     * style)
     */
    ;
    result = toColText(t1);
    ;
    result.append(t2);
    return result;
};

uint8 code(const TermColorFg8Bit& col) {
    uint8 result;
    /*!Get ansi code for the 16-color foreground terminal color
     */
    ;
    ((col.uint8) + (low(ForegroundColor).uint8));
    return result;
};

uint8 code(const TermColorBg8Bit& col) {
    uint8 result;
    /*!Get ansi code for the 16-color background terminal color
     */
    ;
    ((col.uint8) + (low(BackgroundColor).uint8));
    return result;
};

QString lispRepr(const ColRune& rune) {
    QString result;
    (&(R"(({rune.rune} :fg {rune.style.fg} :bg {rune.style.bg} :style {rune.style.style}))"));
    return result;
};

QString lispRepr(const ColText& rune) {
    QString result;
    result = R"(()";
    ;
    for (const auto [idx, rune] : rune.runes) {
        if (((0) < (idx))) {
            result.append(R"(\n )");
        };
        result.append(lispRepr(rune));
    };
    ((result) &= (R"())"));
    return result;
};

QString toQString(const ColText& text, const bool& color = true) {
    QString result;
    /*!Convert colored text to QString with ansi escape sequences
     */
    ;
    toQString(text.runes, color);
    return result;
};

void addf(
    ColText&                           text,
    const Str&                         formatstr,
    const varargs<ColText, toColText>& colored) {
    for (const auto fr : addfFragments(formatstr)) {
        switch (fr.kind) {
            case addfDollar: {
                text.append(R"($)");
                break;
            }
            case addfText: {
                text.append(fr.text);
                break;
            }
            case addfVar:
            case addfExpr: {
                assert(
                    false,
                    R"(var/expr formatting is not supported for colored text yet)");
                break;
            }
            case addfPositional:
            case addfIndexed:
            case addfBackIndexed: {
                const auto idx = else { (fr.kind == addfBackIndexed) }
                else {
                    fr.idx;
                }
                assert(0 <= idx && idx < colored.size());
                text.append(colored[idx]);
                break;
            }
        }
    }
}

/*!Shorthand for colored text interpolation */
ColText operator%(
    const Str&                format,
    const openArray<ColText>& interpolate) {
    ColText result;
    result.addf(format, interpolate);
    return result;
}

#endif
