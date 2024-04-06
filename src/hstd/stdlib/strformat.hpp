#pragma once

#include <string>
#include <vector>
#include <stdexcept>

#include <hstd/stdlib/sequtils.hpp>
#include <hstd/system/all.hpp>

enum class AddfFragmentKind
{
    Text,        ///< Regular text fragment
    Positional,  ///< Positional fragment `$#`
    Indexed,     ///< Indexed fragment `$1`
    Dollar,      ///< Dollar literal `$$`
    BackIndexed, ///< Negative indexed fragment `$-1`
    Var,         ///< Interpolated variable `$name`
    Expr,        ///< Expression in braces `${some expr}`
};

struct AddfFragment {
    AddfFragmentKind kind;
    std::string      text;
    int              idx = 0;
};

struct FormatStringError : public std::runtime_error {
    explicit FormatStringError(const std::string& message)
        : std::runtime_error(message) {}
};


/*! Iterate over interpolation fragments of the `formatstr` */
std::vector<AddfFragment> addfFragments(const std::string& formatstr);

/*! The same as `add(s, formatstr % a)`, but more efficient. */
void addf(
    std::string&                    s,
    CR<std::vector<AddfFragment>>   fragments,
    const std::vector<std::string>& a);


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
    requires StdFormattable<T>
{
    out.push_back(std::format("{}", in));
    to_string_vec_impl(out, tail...);
}

template <typename... Args>
std::vector<std::string> to_string_vec(Args&&... args) {
    std::vector<std::string> result{};
    result.reserve(sizeof...(Args));
    to_string_vec_impl(result, args...);
    return result;
}
