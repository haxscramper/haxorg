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


// The set of track event categories that the example is using.
PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("lexing").SetDescription("Lexing"),
    perfetto::Category("parsing").SetDescription("Parsing"),
    perfetto::Category("cli").SetDescription("CLI"),
    perfetto::Category("convert").SetDescription("Convert"));


#    define __perf_trace(category, message) TRACE_EVENT(category, message)

#else
#    define __perf_trace(category, message, ...)

#endif
