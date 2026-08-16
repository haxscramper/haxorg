#pragma once
#pragma clang diagnostic ignored "-Wunknown-attributes"


#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/system/reflection.hpp>

#include <span>

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
  public:
    struct ScopeFilter {
        struct FilterComponent {
            struct Positive {
                std::string segment;
                DESC_FIELDS(Positive, (segment));
            };
            struct Negative {
                std::string segment;
                DESC_FIELDS(Negative, (segment));
            };
            struct Any {
                DESC_FIELDS(Any, ());
            };
            struct AnyVarargs {
                DESC_FIELDS(AnyVarargs, ())
            };

            SUB_VARIANTS(Kind, Data, data, getKind, Positive, Negative, Any, AnyVarargs);
            Data data;
            DESC_FIELDS(FilterComponent, (data));
        };

        using List = std::vector<std::vector<FilterComponent>>;

        /// \brief Replace the filter list. Negative is only allowed as the
        /// first component of a pattern (gitignore-style `!` prefix).
        void setFilters(List const& filters);

        /// \brief Check whether a scope (list of segments) passes the filters.
        bool enabled(std::vector<std::string> const& scope) const;

        DECL_DESCRIBED_ENUM(Decision, Hide, Show);

        struct Pattern {
            bool                         negated = false;
            std::vector<FilterComponent> body;
            DESC_FIELDS(Pattern, (negated, body));
        };

        std::vector<Pattern> patterns;

        DESC_FIELDS(ScopeFilter, (patterns));

        static bool matchBody(
            std::span<const FilterComponent> pat,
            std::span<const std::string>     segs);
        Decision decide(std::span<const std::string> segs) const;
    };

  private:
    mutable int                      activeLevel = 0;
    mutable std::vector<std::string> activeScopes;
    mutable bool                     scopeEnabled = true;
    ScopeFilter                      scopeFilter;
    mutable bool                     TraceState = false;

  public:
    [[refl]] bool              traceToFile     = false;
    [[refl]] bool              traceToBuffer   = false;
    [[refl]] bool              traceStructured = false;
    [[refl]] bool              traceColored    = true;
    hstd::Opt<fs::path>        traceFile;
    [[refl]] std::string       traceBuffer;
    mutable SPtr<std::ostream> stream;

    void incLevel() const;
    void decLevel() const;
    int  getLevel() const;
    void addScope(std::string const& scope) const;
    void popScope(std::string const& scope) const;
    bool getTraceState() const { return TraceState; }
    void setTraceState(bool value) const { TraceState = value; }

    std::vector<std::string> const& getScope() const;

    void setScopeFilters(ScopeFilter::List const& filters);

    bool canTrace() const { return TraceState && scopeEnabled; }

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
        if (canTrace()) {
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
        Opt<std::string>  scope_name = std::nullopt;
        void              start(
            Opt<std::string> const& value      = std::nullopt,
            Opt<std::string> const& scope_name = std::nullopt,
            char const*             function   = __builtin_FUNCTION(),
            int                     line       = __builtin_LINE(),
            char const*             file       = __builtin_FILE());

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
        Opt<std::string> const& value      = std::nullopt,
        Opt<std::string> const& scope_name = std::nullopt,
        char const*             function   = __builtin_FUNCTION(),
        int                     line       = __builtin_LINE(),
        char const*             file       = __builtin_FILE()) const;

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


namespace tracer_detail {
inline hstd::OperationsTracer const* __get_tracer_obj(hstd::OperationsTracer const* t) {
    return t;
}
inline hstd::OperationsTracer const* __get_tracer_obj(hstd::OperationsTracer const& t) {
    return &t;
}
inline hstd::OperationsTracer const* __get_tracer_obj(
    hstd::SPtr<hstd::OperationsTracer> const& t) {
    return t.get();
}
inline bool __can_trace(hstd::OperationsTracer const& t) { return t.canTrace(); }
inline bool __can_trace(hstd::OperationsTracer const* t) { return t->canTrace(); }
inline bool __can_trace(hstd::SPtr<hstd::OperationsTracer> const& t) {
    return t->canTrace();
}
} // namespace tracer_detail

#define OP_TRACER_MESSAGE(__tracer, __format, ...)                                       \
    if (::hstd::tracer_detail::__can_trace(__tracer)) {                                  \
        ::hstd::tracer_detail::__get_tracer_obj(__tracer)->message(                      \
            ::hstd::tracer_detail::__get_tracer_obj(__tracer)->fmt_message(              \
                __format __VA_OPT__(, ) __VA_ARGS__));                                   \
    }

#define OP_TRACER_MESSAGE_SCOPE_HANDLE(__tracer, __format, ...)                          \
    ::hstd::tracer_detail::__can_trace(__tracer)                                         \
        ? ::hstd::tracer_detail::__get_tracer_obj(__tracer)->begin_scope(                \
              ::hstd::tracer_detail::__get_tracer_obj(__tracer)->fmt_message(            \
                  __format __VA_OPT__(, ) __VA_ARGS__))                                  \
        : ::hstd::tracer_detail::__get_tracer_obj(__tracer)->begin_scope();

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
