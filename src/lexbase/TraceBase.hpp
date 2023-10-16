#pragma once

#include <memory>
#include <fstream>
#include <string>
#include <QFile>
#include <filesystem>

#include <hstd/stdlib/ColText.hpp>

struct OperationsTracer {
    bool trace         = false;
    bool traceToFile   = false;
    bool traceToBuffer = false;
    OperationsTracer() {}
    OperationsTracer(QFileInfo const& info) { setTraceFile(info); }

    SPtr<QFile>        file;
    SPtr<std::ostream> stream;
    void               setTraceFile(QFileInfo const& outfile);
    ColStream          getStream();
    void               endStream(ColStream& stream);
};
