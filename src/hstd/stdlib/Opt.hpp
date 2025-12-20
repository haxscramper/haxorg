#pragma once

#include <optional>
#include <hstd/stdlib/Exception.hpp>

namespace hstd {

template <typename T>
using Opt = std::optional<T>;


struct nullopt_optional_err : CRTP_hexception<nullopt_optional_err> {};

template <typename T>
T opt_value(
    CR<Opt<T>>  opt,
    CR<Str>     msg,
    int         line     = __builtin_LINE(),
    char const* function = __builtin_FUNCTION(),
    char const* file     = __builtin_FILE()) {
    if (opt) {
        return *opt;
    } else {
        throw nullopt_optional_err::init(
            "cannot unpack nullopt value "_ss + msg, line, function, file);
    }
}

template <
    typename T,
    typename F,
    typename Res = std::invoke_result<T(int)>::type>
Opt<Res> opt_map(CR<Opt<T>> opt, CR<F> cb) {
    if (opt) {
        return cb(*opt);
    } else {
        return std::nullopt;
    }
}

} // namespace hstd


