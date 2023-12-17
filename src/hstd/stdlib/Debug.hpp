#pragma once

import std.system.string_convert;
import std.stdlib.ColText;

#include <absl/log/log.h>
import std;
import std;

void setMessageStream(std::ostream& stream);


#define _dbg(expr)                                                        \
    ([](auto const& it) {                                                 \
        DLOG(INFO) << (#expr) << " = ⦃" << it << "⦄";                     \
        return it;                                                        \
    }((expr)))
