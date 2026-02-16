#pragma once

#include <hstd/ext/perfetto_aux.hpp>

#ifdef ORG_BUILD_WITH_PERFETTO

PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("gui").SetDescription("Gui"),
    perfetto::Category("model").SetDescription(
        "Data model construction, update etc. "));

#endif
