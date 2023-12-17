#pragma once

import hstd.system.string_convert;
import hstd.stdlib.ColText;

#include <absl/log/log.h>

void setMessageStream(std::ostream& stream);


#define _dbg(expr)                                                        \
    ([](auto const& it) {                                                 \
        DLOG(INFO) << (#expr) << " = ⦃" << it << "⦄";                     \
        return it;                                                        \
    }((expr)))
