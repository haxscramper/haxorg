#pragma once

import std.system.string_convert;
import std.stdlib.ColText;

#include <absl/log/log.h>
#include <string>
#include <iostream>

void setMessageStream(std::ostream& stream);


#define _dbg(expr)                                                        \
    ([](auto const& it) {                                                 \
        DLOG(INFO) << (#expr) << " = ⦃" << it << "⦄";                     \
        return it;                                                        \
    }((expr)))
