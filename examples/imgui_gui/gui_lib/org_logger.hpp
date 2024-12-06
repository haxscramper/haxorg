#pragma once

#include <boost/preprocessor.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/system/macros.hpp>
#include <stack>

#include <boost/log/core.hpp>
#include <boost/log/sinks/sink.hpp>

namespace org_logging {

enum class severity_level
{
    trace,
    debug,
    info,
    warning,
    error,
    fatal
};

BOOST_DESCRIBE_ENUM(
    severity_level,
    trace,
    debug,
    info,
    warning,
    error,
    fatal);


using sink_ptr = boost::shared_ptr<boost::log::sinks::sink>;

class log_sink_scope {
  public:
    log_sink_scope();
    ~log_sink_scope();

    log_sink_scope& drop_current_sinks();

  private:
    std::stack<sink_ptr> previous_sinks_;
};

template <int Unique, typename Generator>
sink_ptr log_sink_mutable_factory(Generator&& gen) {
    static Generator mutable_state{std::forward<Generator>(gen)};
    return mutable_state();
}


#define OLOG_SINK_FACTORY(impl)                                           \
    ::org_logging::log_sink_mutable_factory<__COUNTER__>(impl)


sink_ptr init_file_sink(Str const& log_file_name);
void     push_sink(sink_ptr const& sink);

#define OLOG_SINK_FACTORY_SCOPED(impl)                                    \
    ::org_logging::log_sink_scoped_factory<__COUNTER__>(impl)

template <int Unique, typename Generator>
log_sink_scope log_sink_scoped_factory(Generator&& gen) {
    sink_ptr       sink = log_sink_mutable_factory<Unique>(std::move(gen));
    log_sink_scope scope;
    push_sink(sink);
    return scope;
}

/// \brief remove all sink backends from the logger
void clear_sink_backends();


struct log_record {
    struct log_data {
        Str            message;
        int            line;
        char const*    file;
        Str            category;
        severity_level level;
        char const*    function;
        int            depth;
        Vec<Str>       source_scope;
        Opt<Str>       source_id;
        DESC_FIELDS(
            log_data,
            (message,
             line,
             file,
             category,
             level,
             function,
             depth,
             source_scope,
             source_id));
    };

    log_data data;

    log_record& function(char const* func);
    log_record& message(int const& msg);
    log_record& message(Str const& msg);
    log_record& message(char const* msg);
    log_record& line(int l);
    log_record& file(char const* f);
    log_record& category(Str const& cat);
    log_record& severity(severity_level l);
    log_record& depth(int depth);
    log_record& source_scope(Vec<Str> const& scope);
    log_record& source_id(Str const& id);

    log_record& set_callsite(
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION(),
        char const* file     = __builtin_FILE()) {
        return this->line(line).file(file).function(function);
    }

    template <typename... _Args>
    inline log_record& fmt_message(
        std::format_string<_Args...> __fmt,
        _Args&&... __args) {
        data.message += std::vformat(
            __fmt.get(), std::make_format_args(__args...));
        return *this;
    }

    void end();
    DESC_FIELDS(log_record, (data));
};

struct log_builder : public log_record {
    ~log_builder() { end(); }
};

bool is_log_accepted(Str const& category, severity_level level);

} // namespace org_logging

#define __ORG_LOG_MESSAGE(_1, _2, arg) .message((arg))

#define __ORG_LOG_ALL_ARGS(...)                                           \
    BOOST_PP_SEQ_FOR_EACH(                                                \
        __ORG_LOG_MESSAGE, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#define __ORG_LOG_IMPL(__cat, __severity, ...)                            \
    if (::org_logging::is_log_accepted(                                   \
            __cat, ::org_logging::severity_level::__severity)) {          \
        OLOG_INIT(__cat, __severity)                                      \
        __ORG_LOG_ALL_ARGS(__VA_ARGS__).end();                            \
    }

#define OLOG_INIT(__cat, __severity)                                      \
    ::org_logging::log_record{}                                           \
        .file(__FILE__)                                                   \
        .line(__LINE__)                                                   \
        .category(__cat)                                                  \
        .function(__FUNCTION__)                                           \
        .level(::org_logging::severity_level::__severity)

#define OLOG_TRACE(__cat, ...) __ORG_LOG_IMPL(__cat, trace, __VA_ARGS__)
#define OLOG_DEBUG(__cat, ...) __ORG_LOG_IMPL(__cat, debug, __VA_ARGS__)
#define OLOG_INFO(__cat, ...) __ORG_LOG_IMPL(__cat, info, __VA_ARGS__)
#define OLOG_WARNING(__cat, ...)                                          \
    __ORG_LOG_IMPL(__cat, warning, __VA_ARGS__)
#define OLOG_ERROR(__cat, ...) __ORG_LOG_IMPL(__cat, error, __VA_ARGS__)
#define OLOG_FATAL(__cat, ...) __ORG_LOG_IMPL(__cat, fatal, __VA_ARGS__)

#define OLOG_SINK_SCOPE() ::org_logging::log_sink_scope()
/// \brief Create logging sink scope and clear all the current sink state
#define OLOG_NOSINK_SCOPE() OLOG_SINK_SCOPE().drop_current_sinks()

// clang-format off
constexpr ::org_logging::severity_level  ol_trace   = ::org_logging::severity_level::trace;
constexpr ::org_logging::severity_level  ol_info    = ::org_logging::severity_level::info;
constexpr ::org_logging::severity_level  ol_debug   = ::org_logging::severity_level::debug;
constexpr ::org_logging::severity_level  ol_warning = ::org_logging::severity_level::warning;
constexpr ::org_logging::severity_level  ol_error   = ::org_logging::severity_level::error;
constexpr ::org_logging::severity_level  ol_fatal   = ::org_logging::severity_level::fatal;
// clang-format on
