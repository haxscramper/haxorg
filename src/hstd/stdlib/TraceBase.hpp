#pragma once
#pragma clang diagnostic ignored "-Wunknown-attributes"


#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <hstd/system/reflection.hpp>
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

struct OperationsTracer;

struct [[refl]] OperationsTracer {
    [[refl]] bool TraceState      = false;
    [[refl]] bool traceToFile     = false;
    [[refl]] bool traceToBuffer   = false;
    [[refl]] bool traceStructured = false;
    [[refl]] bool traceColored    = true;
    [[refl]] int  activeLevel     = 0;

    [[refl]] std::string traceBuffer;

    DESC_FIELDS(
        OperationsTracer,
        (TraceState,
         traceBuffer,
         traceToFile,
         traceToBuffer,
         traceStructured,
         traceColored));

    finally_std scopeLevel() const;
    finally_std scopeTrace(bool state);

    OperationsTracer() {}
    OperationsTracer(fs::path const& info) { setTraceFile(info); }

    SPtr<std::ostream> stream;

    SPtr<std::ostream> getTraceFile();
    void               setTraceFile(SPtr<std::ostream> stream);
    void      setTraceFile(fs::path const& outfile, bool overwrite = true);
    ColStream getStream() const;
    void      endStream(ColStream& stream) const;
    void      message(OperationsMsg const& value) const;

    /// \brief Helper method for reflection
    [[refl]] void setTraceFileStr(
        std::string const& outfile,
        bool               overwrite) {
        setTraceFile(outfile, overwrite);
    }

    [[refl]] void sendMessage(
        std::string const& value,
        std::string const& function,
        int                line,
        std::string const& file) {
        message(value, function.c_str(), line, file.c_str());
    }

    void message(
        std::string const& value,
        char const*        function = __builtin_FUNCTION(),
        int                line     = __builtin_LINE(),
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
