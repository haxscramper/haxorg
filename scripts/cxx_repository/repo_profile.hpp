#pragma once

#include <hstd/ext/perfetto_aux.hpp>

#ifdef ORG_USE_PERFETTO

PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("repo").SetDescription("Read data in"));

#endif
