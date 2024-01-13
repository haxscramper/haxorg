#pragma once

#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/ColText.hpp>

struct OperationsTracer {
    bool TraceState    = false;
    bool traceToFile   = false;
    bool traceToBuffer = false;
    OperationsTracer() {}
    OperationsTracer(fs::path const& info) { setTraceFile(info); }

    SPtr<std::ostream> stream;
    void               setTraceFile(fs::path const& outfile);
    ColStream          getStream();
    void               endStream(ColStream& stream);
};


struct OperationsMsg {
    Opt<std::string> msg;
    char const*      file     = nullptr;
    char const*      function = nullptr;
    int              line     = 0;
    int              column   = 0;
    std::string      name;
};

template <typename Msg>
struct OperationsMsgBulder {
    Msg report;

    OperationsMsgBulder<Msg>& with_msg(Str const& msg) {
        report.msg = msg;
        return *this;
    }

    OperationsMsgBulder<Msg>& with_name(Str const& name) {
        report.name = name;
        return *this;
    }

    OperationsMsgBulder<Msg>& with_line(int const& line) {
        report.line = line;
        return *this;
    }

    OperationsMsgBulder<Msg>& with_location(
        int const&  line,
        char const* function,
        char const* file) {
        report.line     = line;
        report.function = function;
        report.file     = file;
        return *this;
    }
};
