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
std::vector<AddfFragment> addfFragments(const QString& formatstr);

/*! The same as `add(s, formatstr % a)`, but more efficient. */
void addf(
    QString&                      s,
    CR<std::vector<AddfFragment>> fragments,
    const std::vector<QString>&   a);


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
