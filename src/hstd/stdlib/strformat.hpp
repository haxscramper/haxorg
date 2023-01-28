#pragma once

#include <string>
#include <vector>
#include <stdexcept>

#include <hstd/stdlib/charsets.hpp>
#include <hstd/stdlib/sequtils.hpp>
#include <hstd/system/all.hpp>

enum AddfFragmentKind
{
    addfText,        /// Regular text fragment
    addfPositional,  /// Positional fragment `$#`
    addfIndexed,     /// Indexed fragment `$1`
    addfDollar,      /// Dollar literal `$$`
    addfBackIndexed, /// Negative indexed fragment `$-1`
    addfVar,         /// Interpolated variable `$name`
    addfExpr,        /// Expression in braces `${some expr}`
};

struct AddfFragment {
    AddfFragmentKind kind;
    std::string      text;
    int              idx;
};

struct FormatStringError : public std::runtime_error {
    explicit FormatStringError(const std::string& message)
        : std::runtime_error(message) {}
};


/*! Iterate over interpolation fragments of the `formatstr` */
constexpr std::vector<AddfFragment> addfFragments(
    const std::string& formatstr) {
    std::vector<AddfFragment> result{};
    auto                      i   = 0;
    auto                      num = 0;
    const CharSet             PatternChars{
        slice('a', 'z'),
        slice('A', 'Z'),
        slice('0', '9'),
        slice('\xF0', '\xFF'),
        '_'};

    while (i < formatstr.size()) {
        if (((formatstr[i] == '$') && ((i + 1) < formatstr.size()))) {
            const auto c = formatstr[i + 1];
            if (c == '#') {
                result.push_back({.kind = addfIndexed, .idx = num});
                i += 2;
                num += 1;
            } else if (c == '$') {
                i += 2;
                result.push_back({.kind = addfDollar});

            } else if (charsets::Digits.contains(c) || c == '|') {
                auto j = 0;
                i += 1;
                const auto starti   = i;
                auto       negative = formatstr[i] == '-';
                if (negative) {
                    i += 1;
                }
                while (
                    ((i < formatstr.size())
                     && (charsets::Digits.contains(formatstr[i])))) {
                    j = ((j * 10) + ord(formatstr[i])) - ord('0');
                    i += 1;
                }
                if (negative) {
                    result.push_back({.kind = addfBackIndexed, .idx = j});
                } else {
                    result.push_back({.kind = addfIndexed, .idx = j - 1});
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
                     && (!IntSet<char>({'\0', '}'})
                              .contains(formatstr[j])))) {
                    if (charsets::Digits.contains(formatstr[j])) {
                        k = ((k * 10) + ord(formatstr[j])) - ord('0');
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
                            {.kind = addfBackIndexed, .idx = k});
                    } else {
                        result.push_back(
                            {.kind = addfIndexed, .idx = k - 1});
                    }
                } else {
                    const auto first = i + 2;
                    const auto last  = j - 1;
                    const auto count = last - first + 1;

                    result.push_back(
                        {.kind = addfExpr,
                         .text = formatstr.substr(first, count)});
                }
                i = j + 1;

            } else if (
                charsets::Letters.contains(c) || c == '_'
                || IntSet<char>(slice('\xF0', '\xFF')).contains(c)) {
                auto j = i + 1;
                while (
                    ((j < formatstr.size())
                     && (PatternChars.contains(formatstr[j])))) {
                    j += 1;
                }
                const auto first = i + 1;
                const auto last  = j - 1;

                result.push_back(
                    {.kind = addfVar,
                     .text = formatstr.substr(first, last - first + 1)});
                i = j;
            } else {
                throw FormatStringError(
                    "unexpected char after '$' :'"
                    + std::string(1, formatstr[i + 1]) + "'");
            }
        } else {
            auto trange = slice(i, i);
            while (
                ((trange.last < formatstr.size())
                 && (formatstr[trange.last] != '$'))) {
                trange.last += 1;
            }
            trange.last -= 1;
            result.push_back(
                {.kind = addfText,
                 .text = formatstr.substr(
                     trange.first, trange.last - trange.first + 1)});
            i = trange.last;
            i += 1;
        }
    }
    return result;
}

/*! The same as `add(s, formatstr % a)`, but more efficient. */
inline void addf(
    std::string&                    s,
    CR<std::vector<AddfFragment>>   fragments,
    const std::vector<std::string>& a) {
    for (const auto fr : fragments) {
        switch (fr.kind) {
            case addfDollar: {
                s += '$';
                break;
            }
            case addfPositional:
            case addfIndexed:
            case addfBackIndexed: {
                int idx;
                if ((fr.kind) == (addfBackIndexed)) {
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
            case addfText: {
                s += fr.text;
                break;
            }
            case addfVar:
            case addfExpr: {
                auto x = index_of(a, fr.text);
                if ((0 <= x) && (x < (a.size() - 1))) {
                    s += a[x + 1];
                } else {
                    throw FormatStringError(
                        "No interpolation argument named '" + fr.text
                        + "'");
                };
                break;
            }
        };
    };
}


inline std::vector<std::string> fold_format_pairs(
    CR<std::vector<Pair<std::string, std::string>>> values) {
    std::vector<std::string> tmp;
    for (const auto& [key, val] : values) {
        tmp.push_back(key);
        tmp.push_back(val);
    }
    return tmp;
}

inline std::string addf(
    CR<std::vector<AddfFragment>> format,
    CR<std::vector<std::string>>  values) {
    std::string result;
    addf(result, format, values);
    return result;
}

inline std::string operator%(
    CR<std::string>              format,
    CR<std::vector<std::string>> values) {
    return addf(addfFragments(format), values);
}

inline std::string operator%(
    CR<std::string>                                 format,
    CR<std::vector<Pair<std::string, std::string>>> values) {
    return addf(addfFragments(format), fold_format_pairs(values));
}

inline void to_string_vec_impl(std::vector<std::string>& out) {}

template <typename T, typename... Tail>
void to_string_vec_impl(
    std::vector<std::string>& out,
    CR<T>&                    in,
    Tail&&... tail)
    requires StringConvertible<T>
{
    out.push_back(to_string(in));
    to_string_vec_impl(out, tail...);
}

template <typename... Args>
std::vector<std::string> to_string_vec(Args&&... args) {
    std::vector<std::string> result{};
    result.reserve(sizeof...(Args));
    to_string_vec_impl(result, args...);
    return result;
}
