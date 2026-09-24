#pragma once

#ifndef HSTD_CPP_BUILD_WITH_PERFETTO
#    error HSTD_CPP_BUILD_WITH_PERFETTO must be explicitly defined as 0 or 1 for the hstd::hstd_cpp_lib serde header.
#endif

// clang-format off
#if HSTD_CPP_BUILD_WITH_PERFETTO

#    include <perfetto.h>
#    include <filesystem>

std::unique_ptr<perfetto::TracingSession> StartTracing();
std::unique_ptr<perfetto::TracingSession> StartProcessTracing(
    std::string const& procesName);

void InitializePerfetto();
void StopTracing(
    std::unique_ptr<perfetto::TracingSession> tracing_session,
    std::filesystem::path const&              out_path);

std::string StopTracing();

#define __perfetto_STRINGIFY_EVEN(...) __perfetto_STRINGIFY_EVEN_EVAL(__perfetto_STRINGIFY_EVEN_IMPL(__VA_ARGS__))
#define __perfetto_STRINGIFY_EVEN_EVAL(...) __VA_ARGS__

#define __perfetto_STRINGIFY_EVEN_IMPL(a1, a2, ...) #a1, a2 __VA_OPT__(, __perfetto_STRINGIFY_EVEN_IMPL2(__VA_ARGS__))
#define __perfetto_STRINGIFY_EVEN_IMPL2(a1, a2, ...) #a1, a2 __VA_OPT__(, __perfetto_STRINGIFY_EVEN_IMPL3(__VA_ARGS__))
#define __perfetto_STRINGIFY_EVEN_IMPL3(a1, a2, ...) #a1, a2 __VA_OPT__(, __perfetto_STRINGIFY_EVEN_IMPL4(__VA_ARGS__))
#define __perfetto_STRINGIFY_EVEN_IMPL4(a1, a2, ...) #a1, a2 __VA_OPT__(, __perfetto_STRINGIFY_EVEN_IMPL5(__VA_ARGS__))
#define __perfetto_STRINGIFY_EVEN_IMPL5(a1, a2, ...) #a1, a2 __VA_OPT__(, __perfetto_STRINGIFY_EVEN_IMPL6(__VA_ARGS__))
#define __perfetto_STRINGIFY_EVEN_IMPL6(a1, a2, ...) #a1, a2 __VA_OPT__(, __perfetto_STRINGIFY_EVEN_IMPL7(__VA_ARGS__))
#define __perfetto_STRINGIFY_EVEN_IMPL7(a1, a2, ...) #a1, a2 __VA_OPT__(, __perfetto_STRINGIFY_EVEN_IMPL8(__VA_ARGS__))
#define __perfetto_STRINGIFY_EVEN_IMPL8(a1, a2, ...) #a1, a2

#define __perf_trace(c, n, ...) TRACE_EVENT(c, n __VA_OPT__(, __perfetto_STRINGIFY_EVEN(__VA_ARGS__)))


#    define __perf_trace_begin(c, ...)                                    \
        TRACE_EVENT_BEGIN(c __VA_OPT__(, ) __VA_ARGS__)
#    define __perf_trace_end(c, ...)                                      \
        TRACE_EVENT_END(c __VA_OPT__(, ) __VA_ARGS__)

#else
#    define TRACE_COUNTER(...)
#    define __perf_trace(c, n, ...)
#    define __perf_trace_begin(c, ...)
#    define __perf_trace_end(c, ...)
#endif

// clang-format on
