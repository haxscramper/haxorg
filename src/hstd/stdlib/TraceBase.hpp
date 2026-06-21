#pragma once
#pragma clang diagnostic ignored "-Wunknown-attributes"


#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/system/reflection.hpp>

namespace hstd {

struct OperationsMsg {
    Opt<std::string>      msg;
    char const*           file     = nullptr;
    char const*           function = nullptr;
    int                   line     = 0;
    int                   column   = 0;
    int                   level    = 0;
    std::shared_ptr<json> metadata = nullptr;

    void use_stacktrace_as_msg();

    DESC_FIELDS(OperationsMsg, (msg, file, function, line, column, metadata));
};

struct OperationsTracer;

struct [[refl]] OperationsTracer {
    [[refl]] bool              TraceState      = false;
    [[refl]] bool              traceToFile     = false;
    [[refl]] bool              traceToBuffer   = false;
    [[refl]] bool              traceStructured = false;
    [[refl]] bool              traceColored    = true;
    [[refl]] mutable int       activeLevel     = 0;
    hstd::Opt<fs::path>        traceFile;
    [[refl]] std::string       traceBuffer;
    mutable SPtr<std::ostream> stream;


    void begin_scope_event(
        Opt<std::string> const& value    = std::nullopt,
        char const*             function = __builtin_FUNCTION(),
        int                     line     = __builtin_LINE(),
        char const*             file     = __builtin_FILE()) const;

    void end_scope_event(
        Opt<std::string> const& value    = std::nullopt,
        char const*             function = __builtin_FUNCTION(),
        int                     line     = __builtin_LINE(),
        char const*             file     = __builtin_FILE()) const;

    template <typename... _Args>
    [[nodiscard]] inline std::string fmt_message(
        fmt::format_string<_Args...> __fmt,
        _Args&&... __args) const {
        if (TraceState) {
            auto store = fmt::make_format_args(__args...);
            return fmt::vformat(__fmt.get(), fmt::format_args(store));
        } else {
            return "";
        }
    }

    DESC_FIELDS(
        OperationsTracer,
        (TraceState,
         traceBuffer,
         traceToFile,
         traceToBuffer,
         traceStructured,
         traceColored));

    struct ScopeHandle {
        OperationsTracer* tracer;
        void              start(
            Opt<std::string> const& value    = std::nullopt,
            char const*             function = __builtin_FUNCTION(),
            int                     line     = __builtin_LINE(),
            char const*             file     = __builtin_FILE());

        void end(
            Opt<std::string> const& value    = std::nullopt,
            char const*             function = __builtin_FUNCTION(),
            int                     line     = __builtin_LINE(),
            char const*             file     = __builtin_FILE());

        ~ScopeHandle() {
            if (tracer != nullptr) { end(std::nullopt, nullptr, -1, nullptr); }
        }
    };

    ScopeHandle begin_scope_nop() const { return ScopeHandle{nullptr}; }

    ScopeHandle begin_scope(
        Opt<std::string> const& value    = std::nullopt,
        char const*             function = __builtin_FUNCTION(),
        int                     line     = __builtin_LINE(),
        char const*             file     = __builtin_FILE()) const;


    finally_std scopeTrace(bool state);
    OperationsTracer() {}
    OperationsTracer(fs::path const& info) { setTraceFile(info); }

    SPtr<std::ostream>  getTraceFile();
    hstd::Opt<fs::path> getTraceFileDir() const;

    hstd::fs::path getAdjacentToTraceFile(hstd::Str const& suffix) const;

    void writeToTraceFile(
        hstd::fs::path const& path,
        hstd::Str const&      text,
        bool                  with_message = true,
        char const*           function     = __builtin_FUNCTION(),
        int                   line         = __builtin_LINE(),
        char const*           file         = __builtin_FILE()) const;

    void writeAdjacentToTraceFile(
        hstd::Str const& suffix,
        hstd::Str const& text,
        bool             with_message = true,
        char const*      function     = __builtin_FUNCTION(),
        int              line         = __builtin_LINE(),
        char const*      file         = __builtin_FILE()) const;


    void      setTraceFile(SPtr<std::ostream> stream);
    void      setTraceFile(fs::path const& outfile, bool overwrite = true);
    ColStream getStream() const;
    void      endStream(ColStream& stream) const;
    void      message(OperationsMsg const& value) const;
    void      stacktraceMessage() const;

    /// \brief Helper method for reflection
    [[refl]] void setTraceFileStr(std::string const& outfile, bool overwrite) {
        setTraceFile(outfile, overwrite);
    }

    [[refl]] void sendMessage(
        std::string const& value,
        std::string const& function,
        int                line,
        std::string const& file) const {
        message(value, function.c_str(), line, file.c_str());
    }

    void message(
        std::string const& value,
        char const*        function = __builtin_FUNCTION(),
        int                line     = __builtin_LINE(),
        char const*        file     = __builtin_FILE()) const;
};


namespace {
inline bool __is_trace_state(hstd::OperationsTracer const& t) { return t.TraceState; }
inline bool __is_trace_state(hstd::OperationsTracer const* t) { return t->TraceState; }
inline bool __is_trace_state(hstd::SPtr<hstd::OperationsTracer> const& t) {
    return t->TraceState;
}
} // namespace

#define OP_TRACER_MESSAGE(__tracer, __format, ...)                                       \
    if (::hstd::__is_trace_state(__tracer)) {                                            \
        __tracer->message(__tracer->fmt_message(__format __VA_OPT__(, ) __VA_ARGS__));   \
    }

#define OP_TRACER_MESSAGE_SCOPE_HANDLE(__tracer, __format, ...)                          \
    ::hstd::__is_trace_state(__tracer) ? __tracer->begin_scope(__tracer->fmt_message(    \
                                             __format __VA_OPT__(, ) __VA_ARGS__))       \
                                       : __tracer->begin_scope();

#define OP_TRACER_MESSAGE_SCOPE(__tracer, __format, ...)                                 \
    auto BOOST_PP_CAT(__scope, __COUNTER__) = OP_TRACER_MESSAGE_SCOPE_HANDLE(            \
        __tracer, __format __VA_OPT__(, ) __VA_ARGS__);

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

    Derived& with_location(int const& line, char const* function, char const* file) {
        report.line     = line;
        report.function = function;
        report.file     = file;
        return *_this();
    }
};

} // namespace hstd
