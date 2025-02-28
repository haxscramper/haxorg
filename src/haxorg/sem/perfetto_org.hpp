#pragma once

#include <hstd/ext/perfetto_aux.hpp>

#ifdef ORG_USE_PERFETTO
// The set of track event categories that the example is using.
PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("lexing").SetDescription("Lexing"),
    perfetto::Category("parsing").SetDescription("Parsing"),
    perfetto::Category("cli").SetDescription("CLI"),
    perfetto::Category("imm").SetDescription("Immutable AST operations"),
    perfetto::Category("mmpa").SetDescription("Mind map operations"),
    perfetto::Category("convert").SetDescription("Convert"));

#endif
