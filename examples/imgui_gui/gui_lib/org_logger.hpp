#pragma once

#include <boost/preprocessor.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/system/macros.hpp>
#include <stack>

#include <boost/log/core.hpp>
#include <boost/log/sinks/sink.hpp>

namespace org_logging {

using sink_ptr = boost::shared_ptr<boost::log::sinks::sink>;

class log_sink_scope {
  public:
    log_sink_scope();
    ~log_sink_scope();

    log_sink_scope& drop_current_sinks();

  private:
    std::stack<sink_ptr> previous_sinks_;
};

void add_file_sink(Str const& log_file_name);

/// \brief remove all sink backends from the logger
void clear_sink_backends();

DECL_DESCRIBED_ENUM_STANDALONE(
    severity_level,
    trace,
    debug,
    info,
    warning,
    error,
    fatal);

struct log_record {
    struct log_data {
        Str            message;
        int            line;
        char const*    file;
        Str            category;
        severity_level level;
        char const*    function;
        DESC_FIELDS(
            log_data,
            (message, line, file, category, level, function));
    };

    log_data data;

    log_record& function(Str const& func);
    log_record& message(int const& msg);
    log_record& message(Str const& msg);
    log_record& message(char const* msg);
    log_record& line(int l);
    log_record& file(char const* f);
    log_record& category(Str const& cat);
    log_record& level(severity_level l);

    template <typename... _Args>
    inline log_record& fmt_message(
        std::format_string<_Args...> __fmt,
        _Args&&... __args) {
        data.message += std::vformat(
            __fmt.get(), std::make_format_args(__args...));
        return *this;
    }

    void end();
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
