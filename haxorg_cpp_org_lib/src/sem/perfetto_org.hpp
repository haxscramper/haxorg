#pragma once

#include <hstd_cpp_lib/ext/perfetto_aux.hpp>

#if ORG_BUILD_WITH_PERFETTO
// The set of track event categories that the example is using.
PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("lexing").SetDescription("Initial lexing run"),
    perfetto::Category("tokens").SetDescription("Recombine tokens"),
    perfetto::Category("parsing").SetDescription("Parsing"),
    perfetto::Category("cli").SetDescription("CLI"),
    perfetto::Category("imm").SetDescription("Immutable AST operations"),
    perfetto::Category("graph").SetDescription("Mind map operations"),
    perfetto::Category("convert").SetDescription("Convert"),
    perfetto::Category("api").SetDescription("Higher-level API functions"));

#endif
