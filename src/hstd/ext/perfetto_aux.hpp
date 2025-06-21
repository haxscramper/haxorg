#pragma once

// clang-format off
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

#elif ORG_USE_TRACY

#    pragma clang diagnostic ignored "-Wmacro-redefined"
#    define TRACY_ENABLE
#    include <tracy/Tracy.hpp>

inline consteval int __tracy_string_length(std::string_view str) {
    return str.size();
}

template <typename Zone>
void __tracy_zone_text(Zone& zone, std::string const& text) {
    zone.Text(text.c_str(), text.size());
}

#define __perf_trace_impl(__varname, n, ...)                               \
    ZoneNamed(__varname, true);                                            \
    ZoneTextV(__varname, n, __tracy_string_length(n)); \
    TRACY_ZONE_VARS(__varname, __VA_ARGS__);

#define TRACY_ZONE_VARS(varname, ...) TRACY_ZONE_VARS_EVAL(__tracy_TRACY_ZONE_VARS_IMPL(varname, __VA_ARGS__))
#define TRACY_ZONE_VARS_EVAL(...) __VA_ARGS__

#define __tracy_TRACY_ZONE_VARS_IMPL(varname, a1, a2, ...) \
    ; __tracy_zone_variable(varname, #a1, a2); __VA_OPT__(__tracy_TRACY_ZONE_VARS_IMPL2(varname, __VA_ARGS__))
#define __tracy_TRACY_ZONE_VARS_IMPL2(varname, a1, a2, ...) \
    ; __tracy_zone_variable(varname, #a1, a2); __VA_OPT__(__tracy_TRACY_ZONE_VARS_IMPL3(varname, __VA_ARGS__))
#define __tracy_TRACY_ZONE_VARS_IMPL3(varname, a1, a2, ...) \
    ; __tracy_zone_variable(varname, #a1, a2); __VA_OPT__(__tracy_TRACY_ZONE_VARS_IMPL4(varname, __VA_ARGS__))
#define __tracy_TRACY_ZONE_VARS_IMPL4(varname, a1, a2, ...) \
    ; __tracy_zone_variable(varname, #a1, a2); __VA_OPT__(__tracy_TRACY_ZONE_VARS_IMPL5(varname, __VA_ARGS__))
#define __tracy_TRACY_ZONE_VARS_IMPL5(varname, a1, a2, ...) \
    ; __tracy_zone_variable(varname, #a1, a2); __VA_OPT__(__tracy_TRACY_ZONE_VARS_IMPL6(varname, __VA_ARGS__))
#define __tracy_TRACY_ZONE_VARS_IMPL6(varname, a1, a2, ...) \
    ; __tracy_zone_variable(varname, #a1, a2); __VA_OPT__(__tracy_TRACY_ZONE_VARS_IMPL7(varname, __VA_ARGS__))
#define __tracy_TRACY_ZONE_VARS_IMPL7(varname, a1, a2, ...) \
    ; __tracy_zone_variable(varname, #a1, a2); __VA_OPT__(__tracy_TRACY_ZONE_VARS_IMPL8(varname, __VA_ARGS__))
#define __tracy_TRACY_ZONE_VARS_IMPL8(varname, a1, a2, ...) \
    ; __tracy_zone_variable(varname, #a1, a2);



#else
#    define __perf_trace(c, n, ...)
#    define __perf_trace_begin(c, ...)
#    define __perf_trace_end(c, ...)
#endif

// clang-format on
