#pragma once

#include <memory>
#include <fstream>
#include <string>

#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/ColText.hpp>

struct OperationsTracer {
    bool trace         = false;
    bool traceToFile   = false;
    bool traceToBuffer = false;
    OperationsTracer() {}
    OperationsTracer(fs::path const& info) { setTraceFile(info); }

    SPtr<fs::path>     file;
    SPtr<std::ostream> stream;
    void               setTraceFile(fs::path const& outfile);
    ColStream          getStream();
    void               endStream(ColStream& stream);
};
