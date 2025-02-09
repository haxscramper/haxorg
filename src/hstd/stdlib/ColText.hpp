#pragma once

#include <hstd/system/basic_typedefs.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/system/reflection.hpp>


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

BOOST_DESCRIBE_ENUM(
    TermColorBg8Bit,
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    EightBit,
    Default);

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

BOOST_DESCRIBE_ENUM(
    TermColorFg8Bit,
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    EightBit,
    Default);

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

BOOST_DESCRIBE_ENUM(
    Style,
    Bright,
    Dim,
    Italic,
    Underscore,
    Blink,
    BlinkRapid,
    Reverse,
    Hidden,
    Strikethrough);

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

    DESC_FIELDS(ColStyle, (fg, bg, style));
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

std::string to_colored_html(const Vec<ColRune>& runes);


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

    DESC_FIELDS(ColRune, (rune, style));
};

template <>
struct std::formatter<ColRune> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const ColRune& p, FormatContext& ctx) const {
        fmt_ctx("{", ctx);
        fmt_ctx(p.rune, ctx);
        if (p.style.fg != (TermColorFg8Bit)0) {
            fmt_ctx(":fg", ctx);
            fmt_ctx(p.style.fg, ctx);
        }

        if (p.style.bg != (TermColorBg8Bit)0) {
            fmt_ctx(":bg", ctx);
            fmt_ctx(p.style.bg, ctx);
        }

        for (auto const& it : p.style.style) {
            fmt_ctx(":", ctx);
            fmt_ctx(it, ctx);
        }

        return fmt_ctx("}", ctx);
    }
};

struct ColText : Vec<ColRune> {
    using Base = Vec<ColRune>;
    using Base::append;

    std::string toString(bool colored = true) const {
        return to_colored_string(*this, colored);
    }

    std::string toHtml() const { return to_colored_html(*this); }

    ColText& withStyle(CR<ColStyle> style) {
        for (auto& ch : *this) { ch.style = style; }
        return *this;
    }

    ColText() = default;
    ColText(CR<ColStyle> style, CR<std::string> text);

    ColText(CR<std::string> text) : ColText(ColStyle{}, text) {}
    ColText(Span<ColRune> text) : Vec<ColRune>{text} {}

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

template <>
struct std::formatter<ColText> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const ColText& p, FormatContext& ctx) const {
        return std::formatter<Vec<ColRune>>{}.format(p, ctx);
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
    bool          colored  = true;
    int           position = 0;


    CR<ColText> getBuffer() const {
        return *static_cast<ColText const*>(this);
    }

    ColStream() : buffered(true) {};
    ColStream(std::ostream& os) : ostream(&os), buffered(false) {}

    finally_std style_scope() {
        return finally_std{
            [this, start = active]() { this->active = start; }};
    }

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
    /// \brief Split text into lines, write first one without indentation,
    /// write others with the indentation
    void write_indented_after_first(Str const& text, int indent);
};


inline StreamState::StreamState(ColStream& stream) : stream(stream) {
    start = stream.active;
}

inline StreamState::~StreamState() { stream.active = start; }


inline ColStream& ColStream::indent(int level) {
    write(ColText(ColStyle{}, repeat(" ", level)));
    return *this;
}


// clang-format off
inline ColStream& operator<<(ColStream& os, ColStream& value) { return os; }
inline ColStream& operator<<(ColStream& os, ColStyle const& value) { os.active = value; return os; }
inline ColStream& operator<<(ColStream& os, TermColorFg8Bit const& value) { return os << os.active + ColStyle(value); }
inline ColStream& operator<<(ColStream& os, TermColorBg8Bit const& value) { return os << os.active + ColStyle(value); }
inline ColStream& operator<<(ColStream& os, Style const& value) { return os << os.active + ColStyle(value); }
inline ColStream& operator<<(ColStream& os, char const& value) { os.write(ColText(os.active, value)); return os; }
inline ColStream& operator<<(ColStream& os, i8 const& value) { os.write(ColText(os.active, std::to_string(value))); return os; }
inline ColStream& operator<<(ColStream& os, u8 const& value) { os.write(ColText(os.active, std::to_string(value))); return os; }
inline ColStream& operator<<(ColStream& os, u16 const& value) { os.write(ColText(os.active, std::to_string(value))); return os; }
inline ColStream& operator<<(ColStream& os, i16 const& value) { os.write(ColText(os.active, std::to_string(value))); return os; }
inline ColStream& operator<<(ColStream& os, u32 const& value) { os.write(ColText(os.active, std::to_string(value))); return os; }
inline ColStream& operator<<(ColStream& os, i32 const& value) { os.write(ColText(os.active, std::to_string(value))); return os; }
inline ColStream& operator<<(ColStream& os, u64 const& value) { os.write(ColText(os.active, std::to_string(value))); return os; }
inline ColStream& operator<<(ColStream& os, i64 const& value) { os.write(ColText(os.active, std::to_string(value))); return os; }
inline ColStream& operator<<(ColStream& os, float const& value) { os.write(ColText(os.active, std::to_string(value))); return os; }
inline ColStream& operator<<(ColStream& os, std::string const& value) { os.write(ColText(os.active, value)); return os; }
inline ColStream& operator<<(ColStream& os, std::string_view value) { os.write(ColText(os.active, std::string{value})); return os; }
inline ColStream& operator<<(ColStream& os, char const* value) { os.write(ColText(os.active, std::string{value})); return os; }
inline ColStream& operator<<(ColStream& os, ColText const& value) { os.write(value); return os; }
inline ColStream& operator<<(ColStream& os, ColRune const& value) { os.write(value); return os; }
inline ColText operator+(CR<ColText> text, CR<ColText> other) { ColStream s; s << text << other; return s.getBuffer(); }
// clang-format on

enum class hshow_verbosity : u8
{
    Minimal,
    Normal,
    Verbose,
    DataDump,
};

BOOST_DESCRIBE_ENUM(hshow_verbosity, Minimal, Normal, Verbose, DataDump);

#define hshow_flag_list(__impl, __sep)                                    \
    __impl(colored) __sep __impl(show_list_index)                         \
    __sep                 __impl(unicode_newlines)                        \
    __sep                 __impl(with_ranges)                             \
    __sep                 __impl(spell_empty_string)                      \
    __sep                 __impl(use_bin)                                 \
    __sep                 __impl(use_decimal)                             \
    __sep                 __impl(use_hex)                                 \
    __sep                 __impl(trim_prefix_zeros)                       \
    __sep                 __impl(split_numbers)                           \
    __sep                 __impl(use_commas)                              \
    __sep                 __impl(use_quotes)                              \
    __sep                 __impl(use_ascii)                               \
    __sep                 __impl(string_as_array)


enum class hshow_flag : u8
{
#define __ident(a) a
#define __comma ,
    hshow_flag_list(__ident, __comma)
#undef __ident
#undef __comma
};


BOOST_DESCRIBE_ENUM_BEGIN(hshow_flag)
#define __ident(a) BOOST_DESCRIBE_ENUM_ENTRY(hshow_flag, a)
#define __nop
hshow_flag_list(__ident, __nop)
#undef __ident
#undef __nop
    BOOST_DESCRIBE_ENUM_END(hshow_flag);


struct hshow_opts {
    IntSet<hshow_flag> flags = IntSet<hshow_flag>{
        hshow_flag::colored,
        hshow_flag::show_list_index,
        hshow_flag::spell_empty_string,
        hshow_flag::use_commas,
        hshow_flag::use_quotes,
        hshow_flag::trim_prefix_zeros,
    };

    int  indent      = 0;
    int  max_depth   = 120;
    int  max_len     = 320;
    bool quoteIdents = false; /// Add quotes around stings that are valid
                              /// identifirers
    hshow_verbosity verbosity = hshow_verbosity::Normal;

#define __flag_method(a)                                                  \
    hshow_opts& with_##a(bool set) { return cond(hshow_flag::a, set); }   \
    bool        get_##a() const { return flags.contains(hshow_flag::a); }
#define __nop

    hshow_flag_list(__flag_method, __nop)

#undef __flag_method
#undef __nop
        ;

    hshow_opts& cond(hshow_flag flag, bool doAdd) {
        if (doAdd) {
            flags.incl(flag);
        } else {
            flags.excl(flag);
        }
        return *this;
    }
    hshow_opts& incl(hshow_flag flag) {
        flags.incl(flag);
        return *this;
    }
    hshow_opts& excl(hshow_flag flag) {
        flags.excl(flag);
        return *this;
    }
    hshow_opts& with(IntSet<hshow_flag> flag) {
        flags = flag;
        return *this;
    }
};

// aux template to allow partial template specialization with concept
// constraints
template <typename T, typename Aux = int>
struct hshow {};

template <StdFormattable T>
struct hshow_std_format {
    static void format(ColStream& s, CR<T> value, CR<hshow_opts> opts) {
        s << std::format("{}", value);
    }
};


template <typename T>
ColText hshow1(CR<T> value, CR<hshow_opts> opts = hshow_opts{}) {
    ColStream s;
    hshow<T>::format(s, value, opts);
    return s.getBuffer();
}


template <typename T>
void hshow_ctx(ColStream& os, CR<T> value, CR<hshow_opts> opts) {
    hshow<T>::format(os, value, opts);
}

template <typename T>
struct hshow_integral_type {
    static void format(ColStream& s, CR<T> value, CR<hshow_opts> opts) {
        s << s.blue();
        if (opts.get_use_hex()) {
            s << std::format("{:X}", value);
        } else if (opts.get_use_bin()) {
            s << std::format("{:B}", value);
        } else {
            s << std::format("{}", value);
        }
        s << s.end();
    }
};

template <DescribedRecord R>
struct hshow_described_record {
    static void format(ColStream& s, CR<R> value, CR<hshow_opts> opts) {
        bool first = true;
        s << "{";
        for_each_field_value_with_bases(
            value, [&](char const* name, auto const& value) {
                if (!first) { s << ", "; }
                s << ".";
                s.cyan();
                s << name;
                s.end();
                s << " = ";
                hshow_ctx(s, value, opts);
                first = false;
            });
        s << "}";
    }
};

template <DescribedEnum E>
struct hshow_described_enum {
    static void format(ColStream& s, E value, CR<hshow_opts> opts) {
        char const* string = boost::describe::enum_to_string(
            value, nullptr);
        if (string == nullptr) {
            s.red();
            s << fmt("{} (invalid)", std::to_underlying(value));
            s.end();
        } else {
            s.green();
            s << string;
            s.end();
        }
    }
};

template <typename T>
struct hshow_indexed_list {
    static void format(ColStream& s, CR<T> value, CR<hshow_opts> opts) {
        int idx = 0;
        s << "[";
        for (auto const& it : value) {
            if (idx != 0) {
                if (opts.get_use_commas()) {
                    s << ", ";
                } else {
                    s << " ";
                }
            }

            if (opts.get_show_list_index()) { s << fmt("[{}]:", idx); }

            hshow_ctx(s, it, opts);
            ++idx;
        }
        s << "]";
    }
};

template <typename T>
struct hshow_unordered_set {
    static void format(ColStream& s, CR<T> value, CR<hshow_opts> opts) {
        int idx = 0;
        s << "{";
        for (auto const& it : value) {
            if (idx != 0) {
                if (opts.get_use_commas()) {
                    s << ", ";
                } else {
                    s << " ";
                }
            }

            hshow_ctx(s, it, opts);
            ++idx;
        }
        s << "}";
    }
};

template <typename T>
struct hshow_key_value_pairs {
    static void format(ColStream& s, CR<T> value, CR<hshow_opts> opts) {
        int idx = 0;
        s << "{";
        for (auto const& [key, value] : value) {
            if (idx != 0) {
                if (opts.get_use_commas()) {
                    s << ", ";
                } else {
                    s << " ";
                }
            }

            hshow_ctx(s, key, opts);
            s << ": ";
            hshow_ctx(s, value, opts);
            ++idx;
        }
        s << "}";
    }
};

// clang-format off
template <> struct hshow<char> : public hshow_std_format<char> {};
template <> struct hshow<i8> : public hshow_integral_type<i8> {};
template <> struct hshow<u8> : public hshow_integral_type<u8> {};
template <> struct hshow<i16> : public hshow_integral_type<i16> {};
template <> struct hshow<u16> : public hshow_integral_type<u16> {};
template <> struct hshow<i32> : public hshow_integral_type<i32> {};
template <> struct hshow<u32> : public hshow_integral_type<u32> {};
template <> struct hshow<i64> : public hshow_integral_type<i64> {};
template <> struct hshow<u64> : public hshow_integral_type<u64> {};
template <DescribedRecord R> struct hshow<R> : public hshow_described_record<R> {};
template <DescribedEnum E> struct hshow<E> : public hshow_described_enum<E> {};
template <typename T> struct hshow<Vec<T>> : public hshow_indexed_list<Vec<T>> {};
template <typename T> struct hshow<std::vector<T>> : public hshow_indexed_list<std::vector<T>> {};
template <typename T, int Size> struct hshow<SmallVec<T, Size>> : public hshow_indexed_list<SmallVec<T, Size>> {};
template <typename T> struct hshow<IntSet<T>> : public hshow_unordered_set<IntSet<T>> {};
// clang-format on


template <>
struct hshow<std::string_view> {
    static void format(
        ColStream&           os,
        CR<std::string_view> value,
        CR<hshow_opts>       opts);
};

template <>
struct hshow<char const*> {
    static void format(
        ColStream&     os,
        char const*    value,
        CR<hshow_opts> opts) {
        hshow<std::string_view>::format(os, value, opts);
    }
};

template <>
struct hshow<std::string> {
    static void format(
        ColStream&      os,
        CR<std::string> value,
        CR<hshow_opts>  opts) {
        hshow<std::string_view>::format(os, value, opts);
    }
};

template <>
struct hshow<Str> {
    static void format(ColStream& os, CR<Str> value, CR<hshow_opts> opts) {
        hshow<std::string_view>::format(os, value.toBase(), opts);
    }
};


template <>
struct hshow<char*> {
    static void format(ColStream& os, char* value, CR<hshow_opts> opts) {
        hshow<std::string_view>::format(os, value, opts);
    }
};

template <int N>
struct hshow<char[N]> {
    static void format(
        ColStream&     os,
        char const*    value,
        CR<hshow_opts> opts) {
        hshow<std::string_view>::format(os, value, opts);
    }
};

template <int N>
struct hshow<char const[N]> {
    static void format(
        ColStream&     os,
        char const     value[N],
        CR<hshow_opts> opts) {
        hshow<std::string_view>::format(os, value, opts);
    }
};


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
