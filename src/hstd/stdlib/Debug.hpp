#pragma once

#include <hstd/system/string_convert.hpp>
#include <hstd/stdlib/ColText.hpp>

#include <absl/log/log.h>
#include <string>
#include <iostream>

void setMessageStream(std::ostream& stream);


#define _dbg(expr)                                                        \
    ([](auto const& it) {                                                 \
        DLOG(INFO) << (#expr) << " = ⦃" << it << "⦄";                     \
        return it;                                                        \
    }((expr)))
