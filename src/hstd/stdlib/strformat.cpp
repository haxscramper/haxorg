#include "strformat.hpp"
#include <hstd/stdlib/Slice.hpp>

void addf(
    std::string&                    s,
    CR<std::vector<AddfFragment>>   fragments,
    const std::vector<std::string>& a) {
    for (const auto& fr : fragments) {
        switch (fr.kind) {
            case AddfFragmentKind::Dollar: {
                s += '$';
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
                        + std::to_string(idx) + "], but only "
                        + std::to_string(a.size())
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

    while (i < formatstr.size()) {
        if (formatstr[i] == '$' && (i + 1) < formatstr.size()) {
            const auto c = formatstr[i + 1];
            if (c == '#') {
                result.push_back(
                    {.kind = AddfFragmentKind::Indexed, .idx = num});
                i += 2;
                num += 1;
            } else if (c == '$') {
                i += 2;
                result.push_back({.kind = AddfFragmentKind::Dollar});

            } else if (std::isdigit(c) || c == '|') {
                auto j = 0;
                i += 1;
                const auto starti   = i;
                auto       negative = formatstr[i] == '-';
                if (negative) {
                    i += 1;
                }
                while (
                    ((i < formatstr.size())
                     && (std::isdigit(formatstr[i])))) {
                    j = ((j * 10) + value_domain<char>::ord(formatstr[i]))
                      - value_domain<char>::ord('0');
                    i += 1;
                }
                if (negative) {
                    result.push_back(
                        {.kind = AddfFragmentKind::BackIndexed, .idx = j});
                } else {
                    result.push_back(
                        {.kind = AddfFragmentKind::Indexed, .idx = j - 1});
                }
            } else if (c == '{') {
                auto       j        = i + 2;
                auto       k        = 0;
                auto       negative = formatstr[j] == '-';
                const auto starti   = j;
                if (negative) {
                    j += 1;
                }
                auto isNumber = 0;
                while (
                    ((j < formatstr.size())
                     && (!(formatstr[j] == '\0' || formatstr[j] == '}')))) {
                    if (std::isdigit(formatstr[j])) {
                        k = ((k * 10)
                             + value_domain<char>::ord(formatstr[j]))
                          - value_domain<char>::ord('0');
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
                         .text = formatstr.substr(first, count)});
                }
                i = j + 1;

            } else if (std::isalnum(c) || c == '_') {
                auto j = i + 1;
                while (j < formatstr.size()
                       && (std::isalnum(formatstr[j])
                           || formatstr[j] == '_')) {
                    j += 1;
                }

                const auto first = i + 1;
                const auto last  = j - 1;

                result.push_back(
                    {.kind = AddfFragmentKind::Var,
                     .text = formatstr.substr(first, last - first + 1)});
                i = j;
            } else {
                throw FormatStringError(
                    "unexpected char after '$' :'"
                    + std::string(1, formatstr[i + 1]) + "'");
            }
        } else {
            auto trange = slice(i, i);
            while (trange.last < formatstr.size()
                   && formatstr[trange.last] != '$') {
                trange.last += 1;
            }
            trange.last -= 1;
            result.push_back(
                {.kind = AddfFragmentKind::Text,
                 .text = formatstr.substr(
                     trange.first, trange.last - trange.first + 1)});
            i = trange.last;
            i += 1;
        }
    }
    return result;
}
