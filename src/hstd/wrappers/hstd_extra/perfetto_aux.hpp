#pragma once

#include <perfetto.h>
#include <filesystem>

std::unique_ptr<perfetto::TracingSession> StartTracing();
std::unique_ptr<perfetto::TracingSession> StartProcessTracing(
    std::string const& procesName);

void InitializePerfetto();
void StopTracing(
    std::unique_ptr<perfetto::TracingSession> tracing_session,
    std::filesystem::path const&              out_path);


#ifdef ORG_USE_PERFETTO

#    define __perf_trace(category, message) TRACE_EVENT(category, message)

#else
#    define __perf_trace(category, message, ...)

#endif
