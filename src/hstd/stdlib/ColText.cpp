#include <hstd/stdlib/ColText.hpp>

QString ansiEsc(const TermColorFg8Bit& col) {
    if ((u8)col <= 7) { // Regular colors
        return ansiEsc(ord(col) + 30);
    } else if ((u8)col <= 15) { // Bright colors
        return ansiEsc(ord(col) + 30 + 60);
    } else { // Full colors
        return ESC_PREFIX "38;5;" + QString::number((u8)col) + "m";
    }
}

QString ansiEsc(const TermColorBg8Bit& col) {
    if ((u8)col <= 7) {
        return ansiEsc(ord(col) + 40);
    } else if ((u8)col <= 15) {
        return ansiEsc(ord(col) + 40 + 60);
    } else {
        return ESC_PREFIX "48;5;" + QString::number((u8)col) + "m";
    };
}

QString ansiEsc(const Style& style, const bool& open) {
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

QString to_string(const ColRune& rune, const bool& color) {
    QString result;
    if (color) {
        result += ansiDiff(ColStyle{}, rune.style);
        result += rune.rune;
        result += ansiEsc(0);
    } else {
        result = rune.rune;
    }
    return result;
}

QString to_colored_string(const Vec<ColRune>& runes, const bool& color) {
    QString result;
    if (color) {
        auto prev = ColStyle();
        for (const auto& rune : runes) {
            result += ansiDiff(prev, rune.style);
            result += to_string(rune.rune);
            prev = rune.style;
        }

        if (!isDefault(prev.fg) || !isDefault(prev.bg)
            || 0 < prev.style.size()) {
            result += ansiEsc(0);
        }
    } else {
        for (const auto rune : runes) {
            result += rune.rune;
        }
    }
    return result;
}
