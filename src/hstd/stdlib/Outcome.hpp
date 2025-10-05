#pragma once

#include <boost/outcome.hpp>
#include <hstd/stdlib/Exception.hpp>
#include <hstd/system/macros.hpp>


namespace hstd {


/// \brief Macro to handle std::optional - converts to outcome::result
#define BOOST_OUTCOME_TRY_OPTIONAL(var, optional_expr, error_msg)         \
    auto BOOST_OUTCOME_UNIQUE_NAME = (optional_expr);                     \
    if (!BOOST_OUTCOME_UNIQUE_NAME.has_value()) {                         \
        return ::hstd::outcome::failure(error_msg);                       \
    }                                                                     \
    auto const& var = std::move(BOOST_OUTCOME_UNIQUE_NAME.value());

/// \brief Macro to handle is<X>() + get<X>() pattern
#define BOOST_OUTCOME_TRY_VALIDATE_GET(                                   \
    var, obj, check_method, get_method, error_msg)                        \
    if (!(obj).check_method()) {                                          \
        return ::hstd::outcome::failure(error_msg);                       \
    }                                                                     \
    auto const& var = (obj).get_method();

/// \brief Alternative macro if get_method() doesn't return optional
#define BOOST_OUTCOME_TRY_VALIDATE_GET_DIRECT(                            \
    var, obj, check_method, get_method, error_msg)                        \
    if (!(obj).check_method()) {                                          \
        return ::hstd::outcome::failure(error_msg);                       \
    }                                                                     \
    auto const& var = (obj).get_method();


#define BOOST_OUTCOME_TRY_SUB_VARIANT(var, obj, variant_name)             \
    BOOST_OUTCOME_TRY_VALIDATE_GET(                                       \
        var,                                                              \
        obj,                                                              \
        is##variant_name,                                                 \
        get##variant_name,                                                \
        hstd::fmt(                                                        \
            "Expected sub variant '{}' but got '{}'",                     \
            #variant_name,                                                \
            obj.sub_variant_get_kind()))


namespace outcome = BOOST_OUTCOME_V2_NAMESPACE;

struct described_predicate_error {
    int         line;
    char const* function;
    char const* file;
    std::string text;

    ::hstd::logic_assertion_error as_exception(char const* expr) {
        return ::hstd::logic_assertion_error::init(
            ::hstd::fmt("{}: {}", expr, text), line, function, file);
    }

    static described_predicate_error init(
        std::string const& message,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE()) {
        return described_predicate_error{line, function, file, message};
    }
};

using described_predicate_result = outcome::
    result<bool, described_predicate_error>;

#define LOGIC_ASSERTION_CHECK_DESCRIBED(expr)                             \
    if (::hstd::described_predicate_result tmp = expr; !(tmp)) {          \
        throw tmp.error().as_exception(#expr);                            \
    }

} // namespace hstd
