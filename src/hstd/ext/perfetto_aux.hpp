#pragma once

#ifdef ORG_USE_PERFETTO

#    include <perfetto/perfetto.h>
#    include <filesystem>

std::unique_ptr<perfetto::TracingSession> StartTracing();
std::unique_ptr<perfetto::TracingSession> StartProcessTracing(
    std::string const& procesName);

void InitializePerfetto();
void StopTracing(
    std::unique_ptr<perfetto::TracingSession> tracing_session,
    std::filesystem::path const&              out_path);

std::string StopTracing();

#    define __perf_trace(c, n, ...)                                       \
        TRACE_EVENT(c, n __VA_OPT__(, ) __VA_ARGS__)
#    define __perf_trace_begin(c, ...)                                    \
        TRACE_EVENT_BEGIN(c __VA_OPT__(, ) __VA_ARGS__)
#    define __perf_trace_end(c, ...)                                      \
        TRACE_EVENT_END(c __VA_OPT__(, ) __VA_ARGS__)
#else
#    define __perf_trace(c, n, ...)
#    define __perf_trace_begin(c, ...)
#    define __perf_trace_end(c, ...)
#endif
