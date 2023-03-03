#pragma once

#include <string>
#include <vector>
#include <stdexcept>

#include <hstd/stdlib/charsets.hpp>
#include <hstd/stdlib/sequtils.hpp>
#include <hstd/system/all.hpp>

enum class AddfFragmentKind
{
    Text,        /// Regular text fragment
    Positional,  /// Positional fragment `$#`
    Indexed,     /// Indexed fragment `$1`
    Dollar,      /// Dollar literal `$$`
    BackIndexed, /// Negative indexed fragment `$-1`
    Var,         /// Interpolated variable `$name`
    Expr,        /// Expression in braces `${some expr}`
};

struct AddfFragment {
    AddfFragmentKind kind;
    QString          text;
    int              idx;
};

struct FormatStringError : public std::runtime_error {
    explicit FormatStringError(const QString& message)
        : std::runtime_error(message.toStdString()) {}
};


/*! Iterate over interpolation fragments of the `formatstr` */
constexpr std::vector<AddfFragment> addfFragments(
    const QString& formatstr) {
    std::vector<AddfFragment> result{};
    auto                      i   = 0;
    auto                      num = 0;
    const CharSet             PatternChars{
        slice(QChar('a'), QChar('z')),
        slice(QChar('A'), QChar('Z')),
        slice(QChar('0'), QChar('9')),
        slice(QChar('\xF0'), QChar('\xFF')),
        QChar('_')};

    while (i < formatstr.size()) {
        if (((formatstr[i] == QChar('$'))
             && ((i + 1) < formatstr.size()))) {
            const auto c = formatstr[i + 1];
            if (c == QChar('#')) {
                result.push_back(
                    {.kind = AddfFragmentKind::Indexed, .idx = num});
                i += 2;
                num += 1;
            } else if (c == QChar('$')) {
                i += 2;
                result.push_back({.kind = AddfFragmentKind::Dollar});

            } else if (charsets::Digits.contains(c) || c == QChar('|')) {
                auto j = 0;
                i += 1;
                const auto starti   = i;
                auto       negative = formatstr[i] == QChar('-');
                if (negative) {
                    i += 1;
                }
                while (
                    ((i < formatstr.size())
                     && (charsets::Digits.contains(formatstr[i])))) {
                    j = ((j * 10) + ord(formatstr[i])) - ord(QChar('0'));
                    i += 1;
                }
                if (negative) {
                    result.push_back(
                        {.kind = AddfFragmentKind::BackIndexed, .idx = j});
                } else {
                    result.push_back(
                        {.kind = AddfFragmentKind::Indexed, .idx = j - 1});
                }
            } else if (c == QChar('{')) {
                auto       j        = i + 2;
                auto       k        = 0;
                auto       negative = formatstr[j] == QChar('-');
                const auto starti   = j;
                if (negative) {
                    j += 1;
                }
                auto isNumber = 0;
                while (
                    ((j < formatstr.size())
                     && (!CharSet({QChar('\0'), QChar('}')})
                              .contains(formatstr[j])))) {
                    if (charsets::Digits.contains(formatstr[j])) {
                        k = ((k * 10) + ord(formatstr[j]))
                          - ord(QChar('0'));
                        if (isNumber == 0) {
                            isNumber = 1;
                        }
                    } else {
                        isNumber = -1;
                    }
                    j += 1;
                };
                if (isNumber == 1) {
                    if (negative) {
                        result.push_back(
                            {.kind = AddfFragmentKind::BackIndexed,
                             .idx  = k});
                    } else {
                        result.push_back(
                            {.kind = AddfFragmentKind::Indexed,
                             .idx  = k - 1});
                    }
                } else {
                    const auto first = i + 2;
                    const auto last  = j - 1;
                    const auto count = last - first + 1;

                    result.push_back(
                        {.kind = AddfFragmentKind::Expr,
                         .text = formatstr.mid(first, count)});
                }
                i = j + 1;

            } else if (
                charsets::Letters.contains(c) || c == QChar('_')
                || CharSet(slice(QChar('\xF0'), QChar('\xFF')))
                       .contains(c)) {
                auto j = i + 1;
                while (
                    ((j < formatstr.size())
                     && (PatternChars.contains(formatstr[j])))) {
                    j += 1;
                }
                const auto first = i + 1;
                const auto last  = j - 1;

                result.push_back(
                    {.kind = AddfFragmentKind::Var,
                     .text = formatstr.mid(first, last - first + 1)});
                i = j;
            } else {
                throw FormatStringError(
                    "unexpected char after '$' :'"
                    + QString(formatstr[i + 1]) + "'");
            }
        } else {
            auto trange = slice(i, i);
            while (trange.last < formatstr.size()
                   && formatstr[trange.last] != QChar('$')) {
                trange.last += 1;
            }
            trange.last -= 1;
            result.push_back(
                {.kind = AddfFragmentKind::Text,
                 .text = formatstr.mid(
                     trange.first, trange.last - trange.first + 1)});
            i = trange.last;
            i += 1;
        }
    }
    return result;
}

/*! The same as `add(s, formatstr % a)`, but more efficient. */
inline void addf(
    QString&                      s,
    CR<std::vector<AddfFragment>> fragments,
    const std::vector<QString>&   a) {
    for (const auto fr : fragments) {
        switch (fr.kind) {
            case AddfFragmentKind::Dollar: {
                s += QChar('$');
                break;
            }
            case AddfFragmentKind::Positional:
            case AddfFragmentKind::Indexed:
            case AddfFragmentKind::BackIndexed: {
                int idx;
                if (fr.kind == AddfFragmentKind::BackIndexed) {
                    idx = a.size() - fr.idx;
                } else {
                    idx = fr.idx;
                }
                if (idx < 0 || a.size() <= idx) {
                    throw FormatStringError(
                        "Argument index out of bounds. Accessed ["
                        + QString::number(idx) + "], but only "
                        + QString::number(a.size())
                        + " arguments were supplied");
                }
                s += a[idx];
                break;
            }
            case AddfFragmentKind::Text: {
                s += fr.text;
                break;
            }
            case AddfFragmentKind::Var:
            case AddfFragmentKind::Expr: {
                auto x = index_of(a, fr.text);
                if (0 <= x && x < a.size() - 1) {
                    s += a[x + 1];
                } else {
                    throw FormatStringError(
                        "No interpolation argument named '" + fr.text
                        + "'");
                }
                break;
            }
        }
    }
}


inline std::vector<QString> fold_format_pairs(
    CR<std::vector<Pair<QString, QString>>> values) {
    std::vector<QString> tmp;
    for (const auto& [key, val] : values) {
        tmp.push_back(key);
        tmp.push_back(val);
    }
    return tmp;
}

inline QString addf(
    CR<std::vector<AddfFragment>> format,
    CR<std::vector<QString>>      values) {
    QString result;
    addf(result, format, values);
    return result;
}

inline QString operator%(
    CR<QString>              format,
    CR<std::vector<QString>> values) {
    return addf(addfFragments(format), values);
}

inline QString operator%(
    CR<QString>                             format,
    CR<std::vector<Pair<QString, QString>>> values) {
    return addf(addfFragments(format), fold_format_pairs(values));
}

inline void to_string_vec_impl(std::vector<QString>& out) {}

template <typename T, typename... Tail>
void to_string_vec_impl(
    std::vector<QString>& out,
    CR<T>&                in,
    Tail&&... tail)
    requires StringConvertible<T>
{
    out.push_back(to_string(in));
    to_string_vec_impl(out, tail...);
}

template <typename... Args>
std::vector<QString> to_string_vec(Args&&... args) {
    std::vector<QString> result{};
    result.reserve(sizeof...(Args));
    to_string_vec_impl(result, args...);
    return result;
}
