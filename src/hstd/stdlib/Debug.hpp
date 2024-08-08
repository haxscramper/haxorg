#pragma once

#include <hstd/system/string_convert.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <boost/preprocessor.hpp>

#include <absl/log/log.h>
#include <string>
#include <iostream>



void setMessageStream(std::ostream& stream);


#define _dbg(expr)                                                        \
    ([](auto const& it) {                                                 \
        DLOG(INFO) << (#expr) << " = ⦃" << it << "⦄";                     \
        return it;                                                        \
    }((expr)))

#define _dfmt_impl(_1, _2, arg)                                           \
    << " " << BOOST_PP_STRINGIZE(arg) << fmt(" = ⦃{}⦄", arg)


#define _dfmt(...)                                                        \
    DLOG(INFO) << "]" BOOST_PP_SEQ_FOR_EACH(                              \
        _dfmt_impl, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__));
