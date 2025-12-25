#pragma once


#ifdef ORG_USE_PERFETTO

#    include <hstd/ext/perfetto_aux.hpp>

PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("sym").SetDescription(
        "Symbol processing performance"),
    perfetto::Category("main").SetDescription("Top execution steps")
    //
);

#endif
