#pragma once

#ifdef USE_PERFETTO

#    include <perfetto.h>
#    include <QFileInfo>


// The set of track event categories that the example is using.
PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("lexing").SetDescription("Lexing"),
    perfetto::Category("parsing").SetDescription("Parsing"),
    perfetto::Category("cli").SetDescription("CLI"),
    perfetto::Category("convert").SetDescription("Convert"));


std::unique_ptr<perfetto::TracingSession> StartTracing();


void InitializePerfetto();
void StopTracing(
    std::unique_ptr<perfetto::TracingSession> tracing_session);

#endif
