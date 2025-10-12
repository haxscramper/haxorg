#pragma once

#if ORG_EMCC_BUILD

#    define HSLOG_TRACE(__cat, ...)
#    define HSLOG_DEBUG(__cat, ...)
#    define HSLOG_INFO(__cat, ...)
#    define HSLOG_WARNING(__cat, ...)
#    define HSLOG_ERROR(__cat, ...)
#    define HSLOG_FATAL(__cat, ...)
#    define HSLOG_SINK_SCOPE()
#    define HSLOG_NOSINK_SCOPE()
#    define HSLOG_TRACE_STACKTRACE(__cat, __severity)

#else
#    include <boost/log/attributes/mutable_constant.hpp>
#    include <boost/log/sinks/basic_sink_frontend.hpp>
#    include <boost/preprocessor.hpp>
#    include <hstd/stdlib/Func.hpp>
#    include <hstd/stdlib/Json.hpp>
#    include <hstd/stdlib/Opt.hpp>
#    include <hstd/stdlib/Str.hpp>
#    include <hstd/system/reflection.hpp>
#    include <hstd/system/macros.hpp>
#    include <stack>

#    include <hstd/stdlib/Set.hpp>
#    include <boost/log/core.hpp>
#    include <boost/log/sinks/sink.hpp>
#    include <hstd/stdlib/TraceBase.hpp>
#    include <hstd/stdlib/ContainerAPI.hpp>

#    if ORG_USE_QT
#        include <QDebug>
#        include <QBuffer>
#    endif

namespace hstd::log {

template <typename T>
struct log_value_formatter {};

#    if ORG_USE_QT
template <typename T>
concept QDebugFormattable = requires(QDebug debug, const T& value) {
    debug << value;
};

template <QDebugFormattable T>
std::string formatQtToString(const T& value) {
    QBuffer buffer{};
    buffer.open(QIODevice::WriteOnly);
    QDebug debug{&buffer};
    debug.nospace().noquote() << value;
    buffer.close();
    return buffer.data().toStdString();
}

template <typename T>
concept OnlyQDebugFormattable = QDebugFormattable<T>
                             && !hstd::StdFormattable<T>;

template <OnlyQDebugFormattable T>
struct log_value_formatter<T> {
    static std::string format(T const& value) {
        return formatQtToString(value);
    }
};
#    endif

template <>
struct log_value_formatter<hstd::ColText> {
    static std::string format(hstd::ColText const& value) {
        return value.toString(false);
    }
};

template <typename T>
concept has_log_value_formatter = requires(const T& value) {
    {
        hstd::log::log_value_formatter<T>{}.format(value)
    } -> std::convertible_to<std::string>;
};

template <typename T>
std::string format_single_argument(const T& value) {
    if constexpr (has_log_value_formatter<T>) {
        return hstd::log::log_value_formatter<T>{}.format(value);
    } else if constexpr (hstd::StdFormattable<T>) {
        return std::format("{}", value);
    } else {
        return "<type unformattable>";
    }
}

template <typename... Args>
using LogFormatStr = std::format_string<std::conditional_t<
    hstd::log::has_log_value_formatter<std::decay_t<Args>>,
    std::string,
    std::conditional_t<
        hstd::StdFormattable<std::decay_t<Args>>,
        Args,
        std::string>>...>;

template <typename T>
auto format_logger_argument1(T const& arg) {
    if constexpr (hstd::log::has_log_value_formatter<
                      std::decay_t<decltype(arg)>>) {
        return hstd::log::log_value_formatter<
                   std::decay_t<decltype(arg)>>{}
            .format(arg);
    } else if constexpr (hstd::StdFormattable<
                             std::decay_t<decltype(arg)>>) {
        return arg;
    } else {
        return std::string{"<type unformattable>"};
    }
}

template <typename... Args>
std::string format_logger_arguments(
    LogFormatStr<Args...> __fmt,
    const Args&... args) {
    auto formatted_args = std::make_tuple(
        format_logger_argument1<Args>(args)...);
    return std::apply(
        [&__fmt](auto&... args_ref) {
            return std::vformat(
                __fmt.get(), std::make_format_args(args_ref...));
        },
        formatted_args);
}


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


#    define HSLOG_SINK_FACTORY(impl)                                      \
        ::hstd::log::log_sink_mutable_factory<__COUNTER__>(impl)


sink_ptr            init_file_sink(hstd::Str const& log_file_name);
void                push_sink(sink_ptr const& sink);
hstd::Opt<sink_ptr> get_last_sink();
hstd::Vec<sink_ptr> get_sink_list();


/// \brief remove all sink backends from the logger
void clear_sink_backends();

struct log_category {
    std::string category;
    log_category() = default;
    explicit log_category(std::string const& category)
        : category{category} {}

    bool operator==(log_category const& other) const {
        return category == other.category;
    }

    DESC_FIELDS(log_category, (category));
};

struct log_record {
    struct log_data {
        hstd::Str            message;
        int                  line = 0;
        char const*          file = nullptr;
        log_category         category;
        severity_level       severity     = severity_level::trace;
        char const*          function     = nullptr;
        hstd::Opt<int>       depth        = std::nullopt;
        hstd::Vec<hstd::Str> source_scope = {};
        hstd::Opt<hstd::Str> source_id    = std::nullopt;
        hstd::Opt<json>      metadata     = std::nullopt;
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

        bool operator==(log_data const& other) const;
    };

    std::size_t hash() const { return data.hash(); }
    bool        operator==(log_record const& other) const {
        return data == other.data;
    }

    static log_record from_operations(hstd::OperationsMsg const& msg);

    template <typename... Args>
    static log_record from_log_fmt_macro(
        char const*           function,
        char const*           file,
        int                   line,
        severity_level        severity,
        log_category const&   category,
        LogFormatStr<Args...> fmt,
        Args&&... args) {
        log_record rec;
        auto       formatted_args = std::make_tuple(
            format_logger_argument1<Args>(args)...);
        rec.line(line)
            .severity(severity)
            .category(category)
            .function(function)
            .message(std::apply(
                [&fmt](auto&... args_ref) {
                    return std::vformat(
                        fmt.get(), std::make_format_args(args_ref...));
                },
                formatted_args));
        return rec;
    }

    template <typename... Args>
    static log_record from_log_fmt_macro(
        char const*           function,
        char const*           file,
        int                   line,
        severity_level        severity,
        LogFormatStr<Args...> fmt,
        Args&&... args) {
        log_record rec;
        auto       formatted_args = std::make_tuple(
            format_logger_argument1<Args>(args)...);
        rec.line(line).severity(severity).function(function).message(
            std::apply(
                [&fmt](auto&... args_ref) {
                    return std::vformat(
                        fmt.get(), std::make_format_args(args_ref...));
                },
                formatted_args));
        return rec;
    }

    static log_record from_macro_args(
        log_category const& category,
        severity_level      severity,
        int                 line     = __builtin_LINE(),
        char const*         function = __builtin_FUNCTION(),
        char const*         file     = __builtin_FILE()) {
        return log_record{}
            .severity(severity)
            .category(category)
            .line(line)
            .function(function)
            .file(file);
    }

    log_data data;

    log_record& prepend_message(std::string const& message);
    log_record& function(char const* func);
    log_record& message(int const& msg);
    log_record& message(hstd::Str const& msg);
    log_record& message(char const* msg);
    log_record& line(int l);
    log_record& file(char const* f);
    log_record& category(log_category const& cat);
    log_record& severity(severity_level l);
    log_record& depth(int depth);
    log_record& source_scope(hstd::Vec<hstd::Str> const& scope);
    log_record& source_scope_add(hstd::Str const& scope);
    log_record& source_id(hstd::Str const& id);
    log_record& metadata(json const& metadata);
    log_record& metadata(hstd::Str const& field, json const& value);
    log_record& maybe_space();

    log_record& as_trace();
    log_record& as_debug();
    log_record& as_info();
    log_record& as_warning();
    log_record& as_error();
    log_record& as_fatal();

    /// \brief Use stacktace information as a log record message
    log_record& fmt_stacktrace();

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

/// \brief If the scoped code section runs more than one time, sink will
/// produce log file showing difference between two runs in diff format.
struct log_differential_sink_factory {
    hstd::Vec<log_record>  prev_run;
    hstd::Vec<std::string> prev_run_format;
    hstd::Str              outfile;
    sink_ptr               operator()();
    bool                   ignoreDepth = false;

    log_differential_sink_factory& ignore_depth(bool ignore) {
        ignoreDepth = ignore;
        return *this;
    }

    log_differential_sink_factory(std::string const& path)
        : outfile{path} {};
};


using log_filter_cb = hstd::Func<bool(log_record const&)>;

sink_ptr set_sink_filter(sink_ptr, log_filter_cb filter);


#    define HSLOG_SINK_FACTORY_SCOPED(generator)                          \
        ::hstd::log::log_sink_scoped_factory<__COUNTER__>(generator)

template <int Unique, typename Generator>
log_sink_scope log_sink_scoped_factory(Generator&& gen) {
    sink_ptr       sink = log_sink_mutable_factory<Unique>(std::move(gen));
    log_sink_scope scope;
    push_sink(sink);
    return std::move(scope);
}


struct log_builder {
    using Finalizer        = hstd::Func<void(log_builder&)>;
    bool       is_released = false;
    Finalizer  finalizer;
    log_record rec;

    std::size_t hash() const { return rec.hash(); }

    // clang-format off
    template <typename Self> inline auto&& maybe_space(this Self&& self) { if (!self.is_released) { self.rec.maybe_space(); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& function(this Self&& self, char const* func) { if (!self.is_released) { self.rec.function(func); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& message(this Self&& self, int const& msg) { if (!self.is_released) { self.rec.message(msg); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& message(this Self&& self, hstd::Str const& msg) { if (!self.is_released) { self.rec.message(msg); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& message(this Self&& self, char const* msg) { if (!self.is_released) { self.rec.message(msg); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& line(this Self&& self, int l) { if (!self.is_released) { self.rec.line(l); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& file(this Self&& self, char const* f) { if (!self.is_released) { self.rec.file(f); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& category(this Self&& self,hstd:: Str const& cat) { if (!self.is_released) { self.rec.category(cat); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& severity(this Self&& self, severity_level l) { if (!self.is_released) { self.rec.severity(l); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& depth(this Self&& self, int depth) { if (!self.is_released) { self.rec.depth(depth); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& source_scope(this Self&& self, hstd::Vec<hstd::Str> const& scope) { if (!self.is_released) { self.rec.source_scope(scope); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& source_scope_add(this Self&& self, hstd::Str const& scope) { if (!self.is_released) { self.rec.source_scope_add(scope); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& source_id(this Self&& self, hstd::Str const& id) { if (!self.is_released) { self.rec.source_id(id); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& metadata(this Self&& self, json const& id) { if (!self.is_released) { self.rec.metadata(id); } return std::forward<Self>(self); }
    template <typename Self> inline auto&& metadata(this Self&& self, hstd::Str const& key, json const& id) { if (!self.is_released) { self.rec.metadata(key, id); } return std::forward<Self>(self); }
    // clang-format on

    template <typename Self>
    inline auto&& set_finalizer(this Self&& self, Finalizer const& msg) {
        self.finalizer = msg;
        return std::forward<Self>(self);
    }

    template <typename Self>
    inline auto&& escape_message(this Self&& self, hstd::Str const& msg) {
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

struct log_scoped_depth_attr {
    int                           depth;
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

#    define HSLOG_DEPTH_SCOPE()                                           \
        ::hstd::log::log_scoped_depth_attr::raii {}

#    define HSLOG_DEPTH_SCOPE_ANON()                                      \
        auto BOOST_PP_CAT(__scope, __COUNTER__) = HSLOG_DEPTH_SCOPE();

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
        [hash_state = hstd::UnorderedSet<std::size_t>{}](
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

#    define HSLOG_UNIQUE_VALUE_FILTER_FINALIZER(__reset)                  \
        ::hstd::log::                                                     \
            log_builder_get_mutable_finalizer_filter_unique_records<      \
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

#    define HSLOG_CHANGED_VALUE_FILTER_FINALIZER(__reset)                 \
        ::hstd::log::                                                     \
            log_builder_get_mutable_finalizer_filter_changed_value<       \
                __COUNTER__>(__reset)

bool is_log_accepted(severity_level level);

// clang-format off
constexpr ::hstd::log::severity_level  l_trace   = ::hstd::log::severity_level::trace;
constexpr ::hstd::log::severity_level  l_info    = ::hstd::log::severity_level::info;
constexpr ::hstd::log::severity_level  l_debug   = ::hstd::log::severity_level::debug;
constexpr ::hstd::log::severity_level  l_warning = ::hstd::log::severity_level::warning;
constexpr ::hstd::log::severity_level  l_error   = ::hstd::log::severity_level::error;
constexpr ::hstd::log::severity_level  l_fatal   = ::hstd::log::severity_level::fatal;
// clang-format on

template <typename Collection>
hstd::log::log_record log_sequential_collection(
    Collection const& items,
    int               line     = __builtin_LINE(),
    char const*       function = __builtin_FUNCTION(),
    char const*       file     = __builtin_FILE()) {
    auto res = ::hstd::log::log_record{}.set_callsite(
        line, function, file);
    res.fmt_message(
        "{} with {} items:",
        hstd::value_metadata<Collection>::typeName(),
        items.size());
    SequentialContainerAdapter<Collection> container{&items};
    for (int i = 0; i < items.size(); ++i) {
        res.fmt_message(
            "\n[{}]: {}", i, format_logger_argument1(items.at(i)));
    }
    return res;
}

template <typename Collection>
hstd::log::log_record log_associative_collection(
    Collection const& items,
    int               line     = __builtin_LINE(),
    char const*       function = __builtin_FUNCTION(),
    char const*       file     = __builtin_FILE()) {
    auto res = ::hstd::log::log_record{}.set_callsite(
        line, function, file);
    res.fmt_message(
        "{} with {} items:",
        hstd::value_metadata<Collection>::typeName(),
        items.size());
    AssociativeContainerAdapter<Collection> container{&items};

    auto keys = container.keys();

    if constexpr (std::equality_comparable<decltype(keys.at(0))>) {
        std::sort(keys.begin(), keys.end());
    }

    for (auto const& key : keys) {
        res.fmt_message(
            "\n[{}]: {}", key, format_logger_argument1(items.at(key)));
    }
    return res;
}

} // namespace hstd::log

#    define __ORG_LOG_MESSAGE(_1, _2, arg) .message((arg))

#    define __ORG_LOG_ALL_ARGS(...)                                       \
        BOOST_PP_SEQ_FOR_EACH(                                            \
            __ORG_LOG_MESSAGE, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#    define HSLOG_BUILDER()                                               \
        ::hstd::log::log_builder {}

#    define __ORG_LOG_IMPL(__severity, ...)                               \
        if (::hstd::log::is_log_accepted(                                 \
                ::hstd::log::severity_level::__severity)) {               \
            ::hstd::log::log_record::from_log_fmt_macro(                  \
                __FUNCTION__,                                             \
                __FILE__,                                                 \
                __LINE__,                                                 \
                ::hstd::log::severity_level::__severity,                  \
                __VA_ARGS__)                                              \
                .end();                                                   \
        }

#    define HSLOG_INIT(__severity)                                        \
        ::hstd::log::log_record{}                                         \
            .file(__FILE__)                                               \
            .line(__LINE__)                                               \
            .function(__FUNCTION__)                                       \
            .severity(::hstd::log::severity_level::__severity)

#    define HSLOG_TRACE_STACKTRACE(__cat, __severity)                     \
        if (::hstd::log::is_log_accepted(                                 \
                ::hstd::log::severity_level::__severity)) {               \
            HSLOG_INIT(__cat, __severity).fmt_stacktrace().end();         \
        }

#    define HSLOG_TRACE(...) __ORG_LOG_IMPL(trace, __VA_ARGS__)
#    define HSLOG_DEBUG(...) __ORG_LOG_IMPL(debug, __VA_ARGS__)
#    define HSLOG_INFO(...) __ORG_LOG_IMPL(info, __VA_ARGS__)
#    define HSLOG_WARNING(...) __ORG_LOG_IMPL(warning, __VA_ARGS__)
#    define HSLOG_ERROR(...) __ORG_LOG_IMPL(error, __VA_ARGS__)
#    define HSLOG_FATAL(...) __ORG_LOG_IMPL(fatal, __VA_ARGS__)

#    define HSLOG_DEBUG_FMT_STRINGIZE_EACH_impl(_1, _2, arg)              \
        BOOST_PP_STRINGIZE(arg),

#    define HSLOG_DEBUG_FMT_STRINGIZE_EACH(...)                           \
        BOOST_PP_SEQ_FOR_EACH(                                            \
            HSLOG_DEBUG_FMT_STRINGIZE_EACH_impl,                          \
            _,                                                            \
            BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

namespace hstd::log {
template <typename... Args>
std::string __HSLOG_DEBUG_FMT_EXPR_IMPL_impl(
    std::vector<std::string> argNames,
    Args&&... args) {
    std::string result;
    auto        values = std::make_tuple(std::forward<Args>(args)...);

    auto format_arg = [&](int index, const auto& value) {
        if (index > 0) { result += " "; }
        result += hstd::fmt(
            "{} = ⦃{}⦄",
            argNames.at(index),
            hstd::fmt1(::hstd::log::format_logger_argument1(value)));
    };

    int index = 0;
    std::apply(
        [&](const auto&... vals) { ((format_arg(index++, vals)), ...); },
        values);

    return result;
}
} // namespace hstd::log

#    define HSLOG_DEBUG_FMT_EXPR_IMPL(...)                                \
        ::hstd::log::__HSLOG_DEBUG_FMT_EXPR_IMPL_impl(                    \
            {HSLOG_DEBUG_FMT_STRINGIZE_EACH(__VA_ARGS__)}, __VA_ARGS__)

#    define HSLOG_DEBUG_FMT(...)                                          \
        HSLOG_DEBUG("{}", HSLOG_DEBUG_FMT_EXPR_IMPL(__VA_ARGS__));

#    define HSLOG_DEBUG_FMT1(value) HSLOG_DEBUG("{} = {}", #value, value);
#    define HSLOG_SINK_SCOPE() ::hstd::log::log_sink_scope()
/// \brief Create logging sink scope and clear all the current sink state
#    define HSLOG_NOSINK_SCOPE() HSLOG_SINK_SCOPE().drop_current_sinks()


#    define HSLOG_RECORD_FIELD "record"
#    define HSLOG_SCOPE_DEPTH_FIELD "CommonDepth"
#    define HSLOG_TIMESTAMP_FIELD "TimeStamp"


template <>
struct std::hash<hstd::log::log_record> {
    std::size_t operator()(
        hstd::log::log_record const& it) const noexcept {
        return it.hash();
    }
};

template <>
struct std::hash<hstd::log::log_record::log_data> {
    std::size_t operator()(
        hstd::log::log_record::log_data const& it) const noexcept {
        return it.hash();
    }
};

#endif


template <>
struct std::hash<hstd::log::log_category> {
    std::size_t operator()(
        hstd::log::log_category const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.category);
        return result;
    }
};
