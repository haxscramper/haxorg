#include "strformat.hpp"
#include <hstd/stdlib/Debug.hpp>

void addf(
    std::string&                      s,
    CR<std::vector<AddfFragment>> fragments,
    const std::vector<std::string>&   a) {
    for (const auto& fr : fragments) {
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
                        + std::string::number(idx) + "], but only "
                        + std::string::number(a.size())
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
                if (x < 0) {
                    throw FormatStringError(
                        "No interpolation argument named '" + fr.text
                        + "'");
                } else if (!(x + 1 < a.size())) {
                    throw FormatStringError(
                        "Interpolation argument '" + fr.text
                        + "' is not followed by any values and cannot be inserted");
                } else {
                    s += a[x + 1];
                }
                break;
            }
        }
    }
}

std::vector<AddfFragment> addfFragments(const std::string& formatstr) {
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
        if (formatstr[i] == QChar('$') && (i + 1) < formatstr.size()) {
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
                    j = ((j * 10) + value_domain<QChar>::ord(formatstr[i]))
                      - value_domain<QChar>::ord(QChar('0'));
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
                        k = ((k * 10)
                             + value_domain<QChar>::ord(formatstr[j]))
                          - value_domain<QChar>::ord(QChar('0'));
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
                while (j < formatstr.size()
                       && PatternChars.contains(formatstr[j])) {
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
                    + std::string(formatstr[i + 1]) + "'");
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
