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
    Black = 1, ///< black
    Red,       ///< red
    Green,     ///< green
    Yellow,    ///< yellow
    Blue,      ///< blue
    Magenta,   ///< magenta
    Cyan,      ///< cyan
    White,     ///< white
    EightBit,  ///< 256-color (not supported, see `enableTrueColors`
               ///< instead.)
    Default    ///< default terminal foreground color
};

template <>
struct value_domain<TermColorBg8Bit>
    : value_domain_ungapped<
          TermColorBg8Bit,
          TermColorBg8Bit::Black,
          TermColorBg8Bit::Default> {};


enum class TermColorFg8Bit : u8
{
    Black = 1, ///< black
    Red,       ///< red
    Green,     ///< green
    Yellow,    ///< yellow
    Blue,      ///< blue
    Magenta,   ///< magenta
    Cyan,      ///< cyan
    White,     ///< white
    EightBit,  ///< 256-color (not supported, see `enableTrueColors`
               ///< instead.)
    Default    ///< default terminal foreground color
};

template <>
struct value_domain<TermColorFg8Bit>
    : value_domain_ungapped<
          TermColorFg8Bit,
          TermColorFg8Bit::Black,
          TermColorFg8Bit::Default> {};

enum class Style : u8
{
    Bright = 1,   ///< bright text
    Dim,          ///< dim text
    Italic,       ///< italic (or reverse on terminals not supporting)
    Underscore,   ///< underscored text
    Blink,        ///< blinking/bold text
    BlinkRapid,   ///< rapid blinking/bold text (not widely supported)
    Reverse,      ///< reverse
    Hidden,       ///< hidden text
    Strikethrough ///< strikethrough
};

template <>
struct value_domain<Style>
    : value_domain_ungapped<Style, Style::Bright, Style::Strikethrough> {};


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

    bool operator==(CR<ColStyle> other) const {
        return fg == other.fg && bg == other.bg && style == other.style;
    }

    bool operator!=(CR<ColStyle> other) const { return !(*this == other); }

    // clang-format off
    ColStyle& red() { fg = TermColorFg8Bit::Red; return *this; }
    ColStyle& blue() { fg = TermColorFg8Bit::Blue; return *this; }
    ColStyle& green() { fg = TermColorFg8Bit::Green; return *this; }
    ColStyle& yellow() { fg = TermColorFg8Bit::Yellow; return *this; }
    ColStyle& cyan() { fg = TermColorFg8Bit::Cyan; return *this; }
    ColStyle& magenta() { fg = TermColorFg8Bit::Magenta; return *this; }
    ColStyle& white() { fg = TermColorFg8Bit::White; return *this; }
    // clang-format on
};


#define ESC_PREFIX "\033["

struct ColRune;
struct ColText;

/*! Create ansi escape sequence with given code */
inline std::string ansiEsc(int code) {
    return ESC_PREFIX + std::to_string(code) + "m";
}


/*! Create ansi escape sequence with given terminal color */
std::string ansiEsc(const TermColorFg8Bit& col);

/*! Create ansi escape sequence with given terminal color */
std::string ansiEsc(const TermColorBg8Bit& col);

/// Create ansi escape sequence with given style. `open` controls whether
/// styling sequence is used for open or for close
std::string ansiEsc(const Style& style, const bool& open);

/// Generate ansi escape sequences to transition from style `s1` to style
/// `s2`
Str ansiDiff(const ColStyle& s1, const ColStyle& s2);


/// Convert colored rune to regular std::string, with ansi escape
/// sequences. `color` controls whether styling is going to be applied or
/// not.
std::string to_string(const ColRune& rune, const bool& color = true);

/// Convert sequence of colored runes to the std::string, with ansi escape
/// sequences in. `color` controls whether styling is going to be applied
/// or not.
std::string to_colored_string(
    const Vec<ColRune>& runes,
    const bool&         color = true);


/// NOTE yes, I know it is very inefficient, but it is not a HPC solution
/// in any case, so I'm trading current development productivity (not
/// spending time on a more efficient range-based solution) over runtime
/// performance. The API must stay the same in any case, so improved
/// version can be implemented in the future.
struct ColRune {
    Str      rune  = " ";
    ColStyle style = ColStyle{};
    inline ColRune(Str rune = " ", CR<ColStyle> style = ColStyle{})
        : rune(rune), style(style) {}

    ColRune operator+(ColStyle const& other) const {
        return ColRune(rune, this->style + other);
    }

    bool operator==(ColRune const& other) const {
        return rune == other.rune && style == other.style;
    }

    bool operator!=(ColRune const& other) const {
        return !(*this == other);
    }
};

struct ColText : Vec<ColRune> {
    using Base = Vec<ColRune>;
    using Base::append;

    std::string toString(bool colored = true) const {
        return to_colored_string(*this, colored);
    }

    ColText& withStyle(CR<ColStyle> style) {
        for (auto& ch : *this) { ch.style = style; }
        return *this;
    }

    ColText() = default;
    ColText(CR<ColStyle> style, CR<std::string> text);

    ColText(CR<std::string> text) : ColText(ColStyle{}, text) {}

    ColText(CR<ColStyle> style, char text)
        : Vec<ColRune>({ColRune(text, style)}) {}


    inline ColText operator<<=(int n) const { return leftAligned(n); }
    inline ColText operator>>=(int n) const { return rightAligned(n); }

    inline void append(int repeat, ColRune c) {
        for (int i = 0; i < repeat; ++i) { push_back(c); }
    }

    inline void append(ColRune c) { push_back(c); }

    inline ColText rightAligned(int n, ColRune c = ColRune{' '}) const {
        ColText res;
        if (size() < n) { res.append(n - size(), c); }
        res.append(*this);
        return res;
    }

    inline ColText leftAligned(int n, ColRune c = ColRune{' '}) const {
        auto s = *this;
        while (s.size() < n) { s.push_back(c); }
        return s;
    }
};

template <typename CharT>
struct std::formatter<ColText, CharT>
    : std::formatter<std::string, CharT> {
    using FmtType = ColText;
    template <typename FormatContext>
    typename FormatContext::iterator format(
        FmtType const& p,
        FormatContext& ctx) {
        std::formatter<std::string, CharT> fmt;
        return fmt.format(to_colored_string(p, true), ctx);
    }
};


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
    std::ostream* ostream = nullptr;
    bool          buffered;
    bool          colored = true;


    CR<ColText> getBuffer() const {
        return *static_cast<ColText const*>(this);
    }

    ColStream() : buffered(true) {};
    ColStream(std::ostream& os) : ostream(&os), buffered(false) {}

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
    void        flush();
    void        write(ColRune const& text);
    void        write(ColText const& text);
};


inline StreamState::StreamState(ColStream& stream) : stream(stream) {
    start = stream.active;
}

inline StreamState::~StreamState() { stream.active = start; }


inline ColStream& ColStream::indent(int level) {
    write(ColText(ColStyle{}, repeat(" ", level)));
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

inline ColStream& operator<<(ColStream& os, char const& value) {
    os.write(ColText(os.active, value));
    return os;
}

inline ColStream& operator<<(ColStream& os, std::string const& value) {
    os.write(ColText(os.active, value));
    return os;
}

inline ColStream& operator<<(ColStream& os, ColText const& value) {
    os.write(value);
    return os;
}

inline ColStream& operator<<(ColStream& os, ColRune const& value) {
    os.write(value);
    return os;
}


inline ColText operator+(CR<ColText> text, CR<ColText> other) {
    ColStream s;
    s << text << other;
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
    UseQuotes,
    UseAscii
};

template <>
struct value_domain<HDisplayFlag>
    : value_domain_ungapped<
          HDisplayFlag,
          HDisplayFlag::Colored,
          HDisplayFlag::UseQuotes> {};

struct HDisplayOpts {
    IntSet<HDisplayFlag> flags = IntSet<HDisplayFlag>{
        HDisplayFlag::Colored,
        HDisplayFlag::PositionIndexed,
        HDisplayFlag::SpellEmptyStrings,
        HDisplayFlag::UseCommas,
        HDisplayFlag::UseQuotes,
        HDisplayFlag::TrimPrefixZeros,
    };

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

template <StdFormattable T>
ColStream& hshow(
    ColStream&       s,
    CR<T>            value,
    CR<HDisplayOpts> opts = HDisplayOpts{}) {
    return s << std::format("{}", value);
}


template <>
ColStream& hshow(ColStream& os, CR<Str> value, CR<HDisplayOpts> opts);

template <>
inline ColStream& hshow(
    ColStream&           os,
    CR<std::string_view> value,
    CR<HDisplayOpts>     opts) {
    if (value.data() == nullptr) {
        return os << os.red() << "nil" << os.end();
    } else {
        return hshow(os, Str(value), opts);
    }
}


template <StdFormattable T>
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
        if (!first) { out << separator; }
        first = false;
        out << item;
    }
    return out.getBuffer();
}
