#pragma once

#include <hstd/stdlib/charsets.hpp>
#include <hstd/system/generator.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Vec.hpp>


template <typename T>
QTextStream& join(QTextStream& os, CR<QString> sep, generator<T>& list) {
    int index = 0;
    for (const auto& it : list) {
        if (0 < index) {
            os << sep;
        }
        os << to_string(it);
        ++index;
    }
    return os;
}

template <typename T>
QTextStream& join(QTextStream& os, CR<QString> sep, generator<T>&& list) {
    auto tmp = std::move(list);
    return join(os, sep, tmp);
}


template <typename T>
QString join(CR<QString> sep, generator<T>& list) {
    QString     out;
    QTextStream os{&out};
    join(os, sep, list);
    return out;
}


template <typename T>
QString join(CR<QString> sep, generator<T>&& list) {
    auto tmp = std::move(list);
    join(sep, tmp);
}

/// Get visible name of the character.
Pair<QChar, QString> visibleName(QChar ch);
Str indent(CR<Str> str, int spaces, char space = ' ', Str prefix = "");

Vec<Str> visibleUnicodeName(QString str);
Vec<Str> split_keep_separator(const Str& str, CharSet sep = {QChar(' ')});
Str      strip(CR<Str> string, CR<CharSet> leading, CR<CharSet> trailing);
Vec<Str> split(CR<Str> str, QChar ch);
QString  right_aligned(CR<QString> str, int n, QChar c = ' ');
QString  left_aligned(CR<QString> str, int n, QChar c = ' ');
Str      normalize(CR<Str> in);
Str      repeat(CR<Str> str, int count);

enum class AsciiStyle
{
    Regular             = 0,
    Inverted            = 1,
    Fraktur             = 2,
    BoldFraktur         = 3,
    DoubleStruck        = 4,
    Bold                = 5,
    Italic              = 6,
    BoldItalic          = 7,
    Script              = 8,
    BoldScript          = 9,
    SansSerif           = 10,
    BoldSansSerif       = 11,
    ItalicSansSerif     = 12,
    ItalicBoldSansSerif = 13,
    Monospace           = 14
};


QString styledUnicodeMapping(QChar ch, AsciiStyle style);
QString styledUnicodeMapping(QString const& str, AsciiStyle style);

inline const char* strdup(QString const& str) {
    return strdup(str.toStdString().c_str());
}
