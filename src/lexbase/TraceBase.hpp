#pragma once

import std;
import std;
import std;

import std.stdlib.Filesystem;
import std.stdlib.ColText;

struct OperationsTracer {
    bool trace         = false;
    bool traceToFile   = false;
    bool traceToBuffer = false;
    OperationsTracer() {}
    OperationsTracer(fs::path const& info) { setTraceFile(info); }

    SPtr<std::ostream> stream;
    void               setTraceFile(fs::path const& outfile);
    ColStream          getStream();
    void               endStream(ColStream& stream);
};
