#pragma once


#ifdef ORG_BUILD_WITH_PERFETTO

#    include <hstd/ext/perfetto_aux.hpp>

PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("sym").SetDescription(
        "Symbol processing performance"),
    perfetto::Category("main").SetDescription("Top execution steps"),
    perfetto::Category("llvm").SetDescription("LLVM code execution time"),
    perfetto::Category("sql").SetDescription("SQLite data insertion"),
    perfetto::Category("transform").SetDescription("Data transform time"),
    //
);

#endif
