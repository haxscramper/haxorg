#pragma once

#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <hstd/system/reflection.hpp>
#include <absl/log/log.h>
#include <absl/log/initialize.h>
#include <absl/log/internal/globals.h>
#include <hstd/stdlib/Json.hpp>

namespace hstd {

struct OperationsMsg {
    Opt<std::string> msg;
    char const*      file     = nullptr;
    char const*      function = nullptr;
    int              line     = 0;
    int              column   = 0;
    int              level    = 0;
    json             metadata = json{};

    void use_stacktrace_as_msg();

    DESC_FIELDS(
        OperationsMsg,
        (msg, file, function, line, column, metadata));
};

struct OperationsScope {
    bool* TraceState  = nullptr;
    int   activeLevel = 0;

    finally_std scopeLevel() const;
    finally_std scopeTrace(bool state);
};

struct OperationsTracer;

struct OperationsTracerSink : public absl::LogSink {
    OperationsTracer const* tracer;
    OperationsScope const*  scope;

    void Send(const absl::LogEntry& entry) override;
};

struct OperationsTracer {
    bool        TraceState       = false;
    bool        traceToFile      = false;
    bool        traceToBuffer    = false;
    bool        traceStructured  = false;
    bool        traceColored     = true;
    bool        collectingAbseil = false;
    std::string traceBuffer;

    OperationsTracer() {}
    OperationsTracer(fs::path const& info) { setTraceFile(info); }

    SPtr<std::ostream> stream;

    SPtr<std::ostream> getTraceFile();
    void               setTraceFile(SPtr<std::ostream> stream);
    void               setTraceFile(fs::path const& outfile);
    ColStream          getStream() const;
    void               endStream(ColStream& stream) const;
    void               message(OperationsMsg const& value) const;
    finally_std        collectAbslLogs(
               OperationsScope const* scope = nullptr) const;

    void message(
        std::string const& value,
        int                level    = 0,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE()) const;
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

} // namespace hstd
