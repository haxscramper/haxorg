#pragma once

#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/sinks/basic_sink_frontend.hpp>
#include <boost/preprocessor.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/system/macros.hpp>
#include <stack>

#include <hstd/stdlib/Set.hpp>
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


using sink_ptr = boost::shared_ptr<boost::log::sinks::basic_sink_frontend>;

class log_sink_scope {
  public:
    log_sink_scope();
    ~log_sink_scope();
    log_sink_scope(log_sink_scope const&)            = delete;
    log_sink_scope& operator=(log_sink_scope const&) = delete;

    log_sink_scope(log_sink_scope&& other) noexcept {
        other.moved           = true;
        this->previous_sinks_ = std::move(other.previous_sinks_);
    };

    log_sink_scope& operator=(log_sink_scope&& other) noexcept {
        other.moved           = true;
        this->previous_sinks_ = std::move(other.previous_sinks_);
        return *this;
    };

    log_sink_scope& drop_current_sinks();

  private:
    bool                 moved = false;
    std::stack<sink_ptr> previous_sinks_;
};

template <int Unique, typename Generator>
sink_ptr log_sink_mutable_factory(Generator&& gen) {
    static Generator mutable_state{std::forward<Generator>(gen)};
    return mutable_state();
}


#define OLOG_SINK_FACTORY(impl)                                           \
    ::org_logging::log_sink_mutable_factory<__COUNTER__>(impl)

sink_ptr      init_file_sink(Str const& log_file_name);
void          push_sink(sink_ptr const& sink);
Opt<sink_ptr> get_last_sink();
Vec<sink_ptr> get_sink_list();


/// \brief remove all sink backends from the logger
void clear_sink_backends();


struct log_record {
    struct log_data {
        Str            message;
        int            line = 0;
        char const*    file = nullptr;
        Str            category;
        severity_level severity     = severity_level::trace;
        char const*    function     = nullptr;
        Opt<int>       depth        = std::nullopt;
        Vec<Str>       source_scope = {};
        Opt<Str>       source_id    = std::nullopt;
        Opt<json>      metadata     = std::nullopt;
        DESC_FIELDS(
            log_data,
            (message,
             line,
             file,
             category,
             severity,
             function,
             depth,
             source_scope,
             source_id,
             metadata));

        std::size_t hash() const;
        // log_data();
    };

    std::size_t hash() const { return data.hash(); }

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
    log_record& source_scope_add(Str const& scope);
    log_record& source_id(Str const& id);
    log_record& metadata(json const& metadata);
    log_record& metadata(Str const& field, json const& value);
    log_record& maybe_space();

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

using log_filter_cb = Func<bool(log_record const&)>;

sink_ptr set_sink_filter(sink_ptr, log_filter_cb filter);


#define OLOG_SINK_FACTORY_SCOPED(generator)                               \
    ::org_logging::log_sink_scoped_factory<__COUNTER__>(generator)

template <int Unique, typename Generator>
log_sink_scope log_sink_scoped_factory(Generator&& gen) {
    sink_ptr       sink = log_sink_mutable_factory<Unique>(std::move(gen));
    log_sink_scope scope;
    push_sink(sink);
    return std::move(scope);
}


struct log_builder {
    using Finalizer        = Func<void(log_builder&)>;
    bool       is_released = false;
    Finalizer  finalizer;
    log_record rec;

    std::size_t hash() const { return rec.hash(); }

    // clang-format off
    template <typename Self> inline auto&& maybe_space(this Self&& self) { if (!self.is_released) { self.rec.maybe_space(); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& function(this Self&& self, char const* func) { if (!self.is_released) { self.rec.function(func); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& message(this Self&& self, int const& msg) { if (!self.is_released) { self.rec.message(msg); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& message(this Self&& self, Str const& msg) { if (!self.is_released) { self.rec.message(msg); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& message(this Self&& self, char const* msg) { if (!self.is_released) { self.rec.message(msg); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& line(this Self&& self, int l) { if (!self.is_released) { self.rec.line(l); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& file(this Self&& self, char const* f) { if (!self.is_released) { self.rec.file(f); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& category(this Self&& self, Str const& cat) { if (!self.is_released) { self.rec.category(cat); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& severity(this Self&& self, severity_level l) { if (!self.is_released) { self.rec.severity(l); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& depth(this Self&& self, int depth) { if (!self.is_released) { self.rec.depth(depth); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& source_scope(this Self&& self, Vec<Str> const& scope) { if (!self.is_released) { self.rec.source_scope(scope); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& source_scope_add(this Self&& self, Str const& scope) { if (!self.is_released) { self.rec.source_scope_add(scope); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& source_id(this Self&& self, Str const& id) { if (!self.is_released) { self.rec.source_id(id); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& metadata(this Self&& self, json const& id) { if (!self.is_released) { self.rec.metadata(id); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& metadata(this Self&& self, Str const& key, json const& id) { if (!self.is_released) { self.rec.metadata(key, id); } return std::forward<Self>(self); }
    // clang-format on

    template <typename Self>
    inline auto&& set_finalizer(this Self&& self, Finalizer const& msg) {
        self.finalizer = msg;
        return std::forward<Self>(self);
    }

    template <typename Self>
    inline auto&& escape_message(this Self&& self, Str const& msg) {
        if (!self.is_released) { self.rec.message(escape_literal(msg)); }
        return std::forward<Self>(self);
    }

    log_builder() = default;

    log_builder(const log_builder&)            = delete;
    log_builder& operator=(const log_builder&) = delete;

    log_builder(log_builder&& other) {
        this->rec         = std::move(other.rec);
        other.is_released = true;
    }

    log_builder& operator=(log_builder&& other) {
        this->rec         = std::move(other.rec);
        other.is_released = true;
        return *this;
    }

    log_record get_record() {
        is_released = true;
        return rec;
    }

    template <typename Self, typename... _Args>
    inline auto&& fmt_message(
        this Self&&                  self,
        std::format_string<_Args...> __fmt,
        _Args&&... __args) {
        if (!self.is_released) {
            self.rec.fmt_message(__fmt, std::forward<_Args>(__args)...);
        }
        return std::forward<Self>(self);
    }

    template <typename Self>
    inline auto&& set_callsite(
        this Self&& self,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION(),
        char const* file     = __builtin_FILE()) {
        return self.line(line).file(file).function(function);
    }

    ~log_builder();
};

class log_scoped_depth_attr {
    int depth;

  public:
    static log_scoped_depth_attr& instance() {
        static log_scoped_depth_attr st;
        return st;
    }

    int get_depth() const { return depth; }

    struct raii {
        friend log_scoped_depth_attr;
        raii() { ++log_scoped_depth_attr::instance().depth; }
        ~raii() { --log_scoped_depth_attr::instance().depth; }
    };
};

#define OLOG_DEPTH_SCOPE()                                                \
    ::org_logging::log_scoped_depth_attr::raii {}

#define OLOG_DEPTH_SCOPE_ANON()                                           \
    auto BOOST_PP_CAT(__scope, __COUNTER__) = OLOG_DEPTH_SCOPE();

/// \brief Create a finalizer that can use a mutable generator object as a
/// filter on the callsite.
template <int Unique, typename Generator>
log_builder::Finalizer log_builder_get_mutable_finalizer_filter(
    Generator gen,
    bool      reset = false) {
    // `log_builder_mutable_finalizer<123123>([state = Create{}]( ... {});`
    // instantiating this function with unique identifier and generator
    // type will create a new thread-local static instance of the
    // generator.
    static Generator mutable_state{std::forward<Generator>(gen)};

    // It should be possible to reset the finalizer state and create a new
    // one.
    if (reset) {
        mutable_state.~Generator();
        new (&mutable_state) Generator(std::forward<Generator>(gen));
    }

    // Return a finalizer callback to be used in the log record. Each time
    // the record is finalized, it can access the mutable state.
    return [](log_builder& rec) {
        // Mutable state acts as a filter, if it returns 'true', then the
        // record is accepted, otherwise the finalizer discards the record
        // data in the destructor, without submitting it.
        if (mutable_state(rec)) { rec.rec.end(); }
    };
}

/// \brief Create log message finalizer that will filter out duplicate
/// messages
template <int Unique>
log_builder::Finalizer log_builder_get_mutable_finalizer_filter_unique_records(
    bool reset = false) {
    return log_builder_get_mutable_finalizer_filter<Unique>(
        [hash_state = UnorderedSet<std::size_t>{}](
            log_builder const& rec) mutable -> bool {
            auto h = rec.hash();
            if (hash_state.contains(h)) {
                return false;
            } else {
                hash_state.incl(h);
                return true;
            }
        },
        reset);
}

#define OLOG_UNIQUE_VALUE_FILTER_FINALIZER(__reset)                       \
    ::org_logging::                                                       \
        log_builder_get_mutable_finalizer_filter_unique_records<          \
            __COUNTER__>(__reset)

template <int Unique>
log_builder::Finalizer log_builder_get_mutable_finalizer_filter_changed_value(
    bool reset = false) {
    return log_builder_get_mutable_finalizer_filter<Unique>(
        [last_state = std::size_t{}](log_builder const& rec) mutable {
            auto h = rec.hash();
            if (h == last_state) {
                return false;
            } else {
                last_state = h;
                return true;
            }
        },
        reset);
}

#define OLOG_CHANGED_VALUE_FILTER_FINALIZER(__reset)                      \
    ::org_logging::                                                       \
        log_builder_get_mutable_finalizer_filter_changed_value<           \
            __COUNTER__>(__reset)

bool is_log_accepted(Str const& category, severity_level level);

} // namespace org_logging

#define __ORG_LOG_MESSAGE(_1, _2, arg) .message((arg))

#define __ORG_LOG_ALL_ARGS(...)                                           \
    BOOST_PP_SEQ_FOR_EACH(                                                \
        __ORG_LOG_MESSAGE, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#define OLOG_BUILDER()                                                    \
    ::org_logging::log_builder {}

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
        .severity(::org_logging::severity_level::__severity)

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

template <>
struct std::hash<org_logging::log_record> {
    std::size_t operator()(
        org_logging::log_record const& it) const noexcept {
        return it.hash();
    }
};

template <>
struct std::hash<org_logging::log_record::log_data> {
    std::size_t operator()(
        org_logging::log_record::log_data const& it) const noexcept {
        return it.hash();
    }
};
