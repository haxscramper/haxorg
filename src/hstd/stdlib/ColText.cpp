#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/stdlib/strutils.hpp>

std::string ansiEsc(const TermColorFg8Bit& col) {
    if ((u8)col <= 7) { // Regular colors
        return ansiEsc(value_domain<TermColorFg8Bit>::ord(col) + 30);
    } else if ((u8)col <= 15) { // Bright colors
        return ansiEsc(value_domain<TermColorFg8Bit>::ord(col) + 30 + 60);
    } else { // Full colors
        return ESC_PREFIX "38;5;" + std::to_string((u8)col) + "m";
    }
}

std::string ansiEsc(const TermColorBg8Bit& col) {
    if ((u8)col <= 7) {
        return ansiEsc(value_domain<TermColorBg8Bit>::ord(col) + 40);
    } else if ((u8)col <= 15) {
        return ansiEsc(value_domain<TermColorBg8Bit>::ord(col) + 40 + 60);
    } else {
        return ESC_PREFIX "48;5;" + std::to_string((u8)col) + "m";
    };
}

std::string ansiEsc(const Style& style, const bool& open) {
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

Str ansiDiff(const ColStyle& s1, const ColStyle& s2) {
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

std::string to_string(const ColRune& rune, const bool& color) {
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

std::string to_colored_string(
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

void ColStream::flush() {
    if (!buffered) { ostream->flush(); }
}

void ColStream::write(const ColRune& text) {
    position += 1;
    if (buffered) {
        append(text);
    } else {
        (*ostream) << to_colored_string({text}, colored);
    }
}

void ColStream::write(const ColText& text) {
    position += text.size();
    if (buffered) {
        append(text);
    } else {
        CHECK(ostream != nullptr);
        (*ostream) << to_colored_string(text, colored);
    }
}

void ColStream::write_indented_after_first(const Str& text, int indent) {
    auto lines = text.split('\n');
    write(ColText{lines.at(0)});
    for (int i = 1; i < lines.size(); ++i) {
        write(ColText{"\n"});
        write(ColText{Str{' '}.repeated(indent)});
        write(ColText{lines.at(i)});
    }
}

void hshow<std::string_view>::format(
    ColStream&           os,
    CR<std::string_view> value,
    CR<hshow_opts>       opts) {
    if (value.data() == nullptr) {
        os << "nil";
    } else {
        bool first = true;
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
        os.end();
    }
}

ColText::ColText(CR<ColStyle> style, CR<std::string> text) {
    for (const auto& ch : rune_chunks(text)) {
        push_back(ColRune(ch, style));
    }
}
