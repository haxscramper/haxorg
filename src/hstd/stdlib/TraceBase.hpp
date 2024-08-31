#pragma once

#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <hstd/system/reflection.hpp>

struct OperationsMsg {
    Opt<std::string> msg;
    char const*      file     = nullptr;
    char const*      function = nullptr;
    int              line     = 0;
    int              column   = 0;
    int              level    = 0;
    DESC_FIELDS(OperationsMsg, (msg, file, function, line, column));
};


struct OperationsTracer {
    bool        TraceState      = false;
    bool        traceToFile     = false;
    bool        traceToBuffer   = false;
    bool        traceStructured = false;
    bool        traceColored    = true;
    std::string traceBuffer;

    OperationsTracer() {}
    OperationsTracer(fs::path const& info) { setTraceFile(info); }

    SPtr<std::ostream> stream;

    void      setTraceFile(fs::path const& outfile);
    ColStream getStream();
    void      endStream(ColStream& stream);
    void      message(OperationsMsg const& value);

    void message(
        std::string const& value,
        int                level    = 0,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE());
};


template <typename Derived, typename Msg>
struct OperationsMsgBulder : CRTP_this_method<Derived> {
    using CRTP_this_method<Derived>::_this;
    Msg report;

    Derived& with_msg(std::string const& msg) {
        report.msg = msg;
        return *_this();
    }

    Derived& with_msg(Opt<std::string> const& msg) {
        report.msg = msg;
        return *_this();
    }

    Derived& with_function(char const* function) {
        report.function = function;
        return *_this();
    }

    Derived& with_line(int const& line) {
        report.line = line;
        return *_this();
    }

    Derived& with_location(
        int const&  line,
        char const* function,
        char const* file) {
        report.line     = line;
        report.function = function;
        report.file     = file;
        return *_this();
    }
};
