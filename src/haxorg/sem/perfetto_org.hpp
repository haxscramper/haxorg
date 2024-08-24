#pragma once

#include <hstd/wrappers/hstd_extra/perfetto_aux.hpp>

// The set of track event categories that the example is using.
PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("lexing").SetDescription("Lexing"),
    perfetto::Category("parsing").SetDescription("Parsing"),
    perfetto::Category("cli").SetDescription("CLI"),
    perfetto::Category("convert").SetDescription("Convert"));
