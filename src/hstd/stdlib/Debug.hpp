#pragma once

#include <hstd/system/string_convert.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <boost/preprocessor.hpp>

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
