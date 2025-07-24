#pragma once

#include <hstd/system/string_convert.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <boost/preprocessor.hpp>
#include <hstd/system/exceptions.hpp>
#include <hstd/system/basic_templates.hpp>

#include <iostream>

void setMessageStream(std::ostream& stream);

#define __fmt_location()                                                  \
    std::format("{}:{} {}", __FILE__, __LINE__, __FUNCTION__)

#define _dbg(expr)                                                        \
    ([](auto const& it, char const* __base_function) {                    \
        std::cerr << __fmt_location()                                     \
                  << ::hstd::fmt(                                         \
                         "@{} {} = ⦃{}⦄", __base_function, #expr, it)     \
                  << std::endl;                                           \
        return it;                                                        \
    }((expr), __FUNCTION__))

#define _dfmt_impl(_1, _2, arg)                                           \
    << " " << BOOST_PP_STRINGIZE(arg) << ::hstd::fmt(" = ⦃{}⦄", arg)


/// \brief Print values to string `<expr1> = ⦃<value1>⦄ <expr2> =
/// ⦃<value2>⦄ ...`
#define _dfmt(...)                                                        \
    std::cerr << __fmt_location() BOOST_PP_SEQ_FOR_EACH(                  \
        _dfmt_impl, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))             \
              << std::endl;

#define _dfmt_expr_impl(_1, _2, arg)                                      \
    +std::string{" "} + BOOST_PP_STRINGIZE(arg) + fmt(" = ⦃{}⦄", arg)


/// \brief Format all values to string `<expr1> = ⦃<value1>⦄ <expr2> =
/// ⦃<value2>⦄ ...`
#define _dfmt_expr(...)                                                   \
    (__fmt_location() BOOST_PP_SEQ_FOR_EACH(                              \
        _dfmt_expr_impl, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))

namespace hstd {
template <typename T>
void logic_assertion_check_not_nil(
    T const*    ptr,
    int         line     = __builtin_LINE(),
    char const* function = __builtin_FUNCTION(),
    char const* file     = __builtin_FILE()) {
    if (hstd::value_metadata<T const*>::isNil(ptr)) {
        throw ::hstd::logic_assertion_error::init(
            ::hstd::fmt(
                "Expected non-nullptr value for type {}",
                hstd::value_metadata<T>::typeName()),
            line,
            function,
            file);
    }
}

template <typename T>
void logic_assertion_check_not_nil(std::unique_ptr<T> const& p) {
    return logic_assertion_check_not_nil(p.get());
}

template <typename T>
void logic_assertion_check_not_nil(std::shared_ptr<T> const& p) {
    return logic_assertion_check_not_nil(p.get());
}

template <typename T>
void logic_assertion_check_not_nil(std::weak_ptr<T> const& p) {
    return logic_assertion_check_not_nil(p.lock().get());
}

template <typename T>
void logic_assertion_check_not_nil(
    T const&    ptr,
    int         line     = __builtin_LINE(),
    char const* function = __builtin_FUNCTION(),
    char const* file     = __builtin_FILE()) {
    if (hstd::value_metadata<T>::isNil(ptr)) {
        throw ::hstd::logic_assertion_error::init(
            ::hstd::fmt(
                "Expected non-nil value for type {}",
                hstd::value_metadata<T>::typeName()),
            line,
            function,
            file);
    }
}
} // namespace hstd
