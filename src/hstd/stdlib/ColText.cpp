#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/ColTextSerde.hpp>
#include <hstd/stdlib/ColTextHShow.hpp>

using namespace hstd;

std::string hstd::ansiEsc(const TermColorFg8Bit& col) {
    if ((u8)col <= 7) { // Regular colors
        return ansiEsc(value_domain<TermColorFg8Bit>::ord(col) + 30);
    } else if ((u8)col <= 15) { // Bright colors
        return ansiEsc(value_domain<TermColorFg8Bit>::ord(col) + 30 + 60);
    } else { // Full colors
        return ESC_PREFIX "38;5;" + std::to_string((u8)col) + "m";
    }
}

std::string hstd::ansiEsc(const TermColorBg8Bit& col) {
    if ((u8)col <= 7) {
        return ansiEsc(value_domain<TermColorBg8Bit>::ord(col) + 40);
    } else if ((u8)col <= 15) {
        return ansiEsc(value_domain<TermColorBg8Bit>::ord(col) + 40 + 60);
    } else {
        return ESC_PREFIX "48;5;" + std::to_string((u8)col) + "m";
    };
}

std::string hstd::ansiEsc(const Style& style, const bool& open) {
    const auto diff = open ? 0 : 20;
    switch (style) {
        case Style::Bright: return ansiEsc(1 + diff);
        case Style::Dim: return ansiEsc(2 + diff);
        case Style::Italic: return ansiEsc(3 + diff);
        case Style::Underscore: return ansiEsc(4 + diff);
        case Style::Blink: return ansiEsc(5 + diff);
        case Style::BlinkRapid: return ansiEsc(6 + diff);
        case Style::Reverse: return ansiEsc(7 + diff);
        case Style::Hidden: return ansiEsc(8 + diff);
        case Style::Strikethrough: return ansiEsc(9 + diff);
        default: return "";
    }
}

Str hstd::ansiDiff(const ColStyle& s1, const ColStyle& s2) {
    Str result;
    if (s2.fg != s1.fg) {
        if (isDefault(s2.fg)) {
            result += ansiEsc(39);
        } else {
            result += ansiEsc(s2.fg);
        }
    }

    if (s2.bg != s1.bg) {
        if (isDefault(s2.bg)) {
            result += ansiEsc(49);
        } else {
            result += ansiEsc(s2.bg);
        }
    }

    for (const auto style : s1.style - s2.style) {
        result += ansiEsc(style, false);
    }

    for (const auto style : s2.style - s1.style) {
        result += ansiEsc(style, true);
    }

    return result;
}

std::string hstd::to_string(const ColRune& rune, const bool& color) {
    std::string result;
    if (color) {
        result += ansiDiff(ColStyle{}, rune.style);
        result += rune.rune;
        result += ansiEsc(0);
    } else {
        result = rune.rune;
    }
    return result;
}

std::string hstd::to_colored_string(
    const Vec<ColRune>& runes,
    const bool&         color) {
    std::string result;
    if (color) {
        auto prev = ColStyle();
        for (const auto& rune : runes) {
            result += ansiDiff(prev, rune.style);
            result += rune.rune;
            prev = rune.style;
        }

        if (!isDefault(prev.fg) || !isDefault(prev.bg)
            || 0 < prev.style.size()) {
            result += ansiEsc(0);
        }
    } else {
        for (const auto& rune : runes) { result += rune.rune; }
    }
    return result;
}

json hstd::to_formatting_json(const Vec<ColRune>& runes) {
    json result;
    result["ansi_format"]  = to_colored_string(runes, true);
    result["plain_format"] = to_colored_string(runes, false);

    json data_format = json::array();
    if (runes.empty()) {
        result["data_format"] = data_format;
        return result;
    }

    auto prev = ColStyle{};
    Str  current_text;

    for (int i = 0; i < runes.size(); ++i) {
        const auto& rune = runes.at(i);

        if (rune.style.fg != prev.fg || rune.style.bg != prev.bg
            || rune.style.style != prev.style) {
            if (!current_text.empty()) {
                json chunk;
                chunk["text"] = current_text;
                if (!isDefault(prev.fg)) {
                    chunk["fg"] = static_cast<u8>(prev.fg);
                }
                if (!isDefault(prev.bg)) {
                    chunk["bg"] = static_cast<u8>(prev.bg);
                }
                if (prev.style.size() > 0) {
                    json style_array = json::array();
                    for (const auto& style : prev.style) {
                        style_array.push_back(static_cast<u8>(style));
                    }
                    chunk["style"] = style_array;
                }
                data_format.push_back(chunk);
                current_text.clear();
            }
            prev = rune.style;
        }

        current_text += rune.rune;
    }

    if (!current_text.empty()) {
        json chunk;
        chunk["text"] = current_text;
        if (!isDefault(prev.fg)) {
            chunk["fg"] = static_cast<u8>(prev.fg);
        }
        if (!isDefault(prev.bg)) {
            chunk["bg"] = static_cast<u8>(prev.bg);
        }
        if (prev.style.size() > 0) {
            json style_array = json::array();
            for (const auto& style : prev.style) {
                style_array.push_back(static_cast<u8>(style));
            }
            chunk["style"] = style_array;
        }
        data_format.push_back(chunk);
    }

    result["data_format"] = data_format;
    return result;
}

void hstd::ColStream::flush() {
    if (!buffered) { ostream->flush(); }
}

void hstd::ColStream::write(const ColRune& text) {
    position += 1;
    if (buffered) {
        append(text);
    } else {
        (*ostream) << to_colored_string({text}, colored);
    }
}

void hstd::ColStream::write(const ColText& text) {
    position += text.size();
    if (buffered) {
        append(text);
    } else {
        LOGIC_ASSERTION_CHECK(ostream != nullptr, "");
        (*ostream) << to_colored_string(text, colored);
    }
}

void ColStream::write_indented_after_first(const Str& text, int indent) {
    auto lines = text.split('\n');
    if (lines.has(0)) { write(ColText{lines.at(0)}); }
    for (int i = 1; i < lines.size(); ++i) {
        write(ColText{"\n"});
        write(ColText{Str{' '}.repeated(indent)});
        write(ColText{lines.at(i)});
    }
}


void ColStream::write_indented_after_first(
    const Vec<ColText>& text,
    int                 indent) {
    if (text.has(0)) { write(ColText{text.at(0)}); }
    for (int i = 1; i < text.size(); ++i) {
        write(ColText{"\n"});
        write(ColText{Str{' '}.repeated(indent)});
        write(text.at(i));
    }
}

void ColStream::write_indented_after_first(
    const ColText& text,
    int            indent) {
    write_indented_after_first(text.split("\n"), indent);
}


void hstd::hshow<std::string_view>::format(
    ColStream&           os,
    CR<std::string_view> value,
    CR<hshow_opts>       opts) {
    if (value.data() == nullptr) {
        os << "nil";
    } else {
        auto __scope = os.style_scope();
        bool first   = true;
        os.yellow();
        std::string open_quote  = opts.get_use_ascii() ? "'" : "«";
        std::string close_quote = opts.get_use_ascii() ? "'" : "»";

        if (opts.get_string_as_array()) {
            if (opts.get_use_quotes()) {
                for (Str const& it :
                     visibleUnicodeName(value, !opts.get_use_ascii())) {
                    if (!first) { os << " "; }
                    first = false;
                    os << std::format(
                        "{}{}{}", open_quote, it, close_quote);
                }
            } else {
                for (const auto& it :
                     visibleUnicodeName(value, !opts.get_use_ascii())) {
                    os << it;
                }
            }
        } else {
            if (opts.get_use_quotes()) { os << open_quote; }

            if (opts.get_use_ascii()) {
                if (opts.get_unicode_newlines()) {
                    for (auto const& c : value) {
                        if (c == '\n') {
                            os << visibleName(c).first;
                        } else {
                            os << c;
                        }
                    }
                } else {
                    os << value;
                }
            } else {
                for (const auto& it : visibleUnicodeName(value, true)) {
                    os << it;
                }
            }

            if (opts.get_use_quotes()) { os << close_quote; }
        }
    }
}

ColText& ColText::withStyle(CR<ColStyle> style) {
    for (auto& ch : *this) { ch.style = style; }
    return *this;
}

hstd::ColText::ColText(CR<ColStyle> style, CR<std::string> text) {
    for (const auto& ch : rune_chunks(text)) {
        push_back(ColRune(ch, style));
    }
}

void ColText::append(int repeat, ColRune c) {
    for (int i = 0; i < repeat; ++i) { push_back(c); }
}

void ColText::append(ColRune c) { push_back(c); }

ColText ColText::rightAligned(int n, ColRune c) const {
    ColText res;
    if (size() < n) { res.append(n - size(), c); }
    res.append(*this);
    return res;
}

ColText ColText::leftAligned(int n, ColRune c) const {
    auto s = *this;
    while (s.size() < n) { s.push_back(c); }
    return s;
}

hstd::Vec<ColText> ColText::split(const Str& delimiter) const {
    hstd::Vec<ColText> result;
    ColText            current;

    for (int i = 0; i < size(); ++i) {
        if (at(i).rune == delimiter) {
            result.push_back(current);
            current.clear();
        } else {
            current.push_back(at(i));
        }
    }

    result.push_back(current);
    return result;
}

namespace {
std::string toHtmlColor(TermColorFg8Bit color) {
    switch (color) {
        case TermColorFg8Bit::Black: return "black";
        case TermColorFg8Bit::Red: return "#800000";
        case TermColorFg8Bit::Green: return "#008000";
        case TermColorFg8Bit::Yellow: return "#808000";
        case TermColorFg8Bit::Blue: return "#000080";
        case TermColorFg8Bit::Magenta: return "#800080";
        case TermColorFg8Bit::Cyan: return "#008080";
        case TermColorFg8Bit::White: return "c0c0c0";
        default: return "inherit"; // For default or unsupported cases
    }
}
} // namespace

std::string hstd::to_colored_html(const Vec<ColRune>& runes) {
    std::string result;
    auto        prev = ColStyle();
    for (const auto& rune : runes) {
        const auto& s1 = prev;
        const auto& s2 = rune.style;
        std::string open_tags, close_tags;

        if (s2.fg != s1.fg) {
            if (!isDefault(s1.fg)) { close_tags += "</font>"; }
            if (!isDefault(s2.fg)) {
                open_tags += std::format(
                    "<font color=\"{}\">", toHtmlColor(s2.fg));
            }
        }

        for (const auto& style : s1.style - s2.style) {
            if (style == Style::Bright) { close_tags += "</b>"; }
            if (style == Style::Italic) { close_tags += "</i>"; }
            if (style == Style::Underscore) { close_tags += "</u>"; }
            if (style == Style::Strikethrough) { close_tags += "</s>"; }
        }

        for (const auto& style : s2.style - s1.style) {
            if (style == Style::Bright) { open_tags += "<b>"; }
            if (style == Style::Italic) { open_tags += "<i>"; }
            if (style == Style::Underscore) { open_tags += "<u>"; }
            if (style == Style::Strikethrough) { open_tags += "<s>"; }
        }

        result += close_tags + open_tags + rune.rune.toBase();
        prev = s2;
    }

    if (!isDefault(prev.fg)) { result += "</font>"; }
    for (const auto& style : prev.style) {
        if (style == Style::Bright) { result += "</b>"; }
        if (style == Style::Italic) { result += "</i>"; }
        if (style == Style::Underscore) { result += "</u>"; }
        if (style == Style::Strikethrough) { result += "</s>"; }
    }

    return result;
}

hshow_opts& hshow_opts::cond(hshow_flag flag, bool doAdd) {
    if (doAdd) {
        flags.incl(flag);
    } else {
        flags.excl(flag);
    }
    return *this;
}

hshow_opts& hshow_opts::incl(hshow_flag flag) {
    flags.incl(flag);
    return *this;
}

hshow_opts& hshow_opts::excl(hshow_flag flag) {
    flags.excl(flag);
    return *this;
}

hshow_opts& hshow_opts::with(IntSet<hshow_flag> flag) {
    flags = flag;
    return *this;
}

ColRune& ColRune::dbg_origin(
    bool        enabled,
    int         line,
    const char* function) {
    if (enabled) { this->rune += hstd::fmt("{}:{}", function, line); }
    return *this;
}
