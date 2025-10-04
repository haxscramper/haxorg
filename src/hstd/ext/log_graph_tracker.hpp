#pragma once

#if ORG_USE_QT
#    include <QObject>
#endif

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <stack>
#include <hstd/ext/graphviz.hpp>
#include <hstd/ext/logger.hpp>

#if ORG_USE_QT
#    include <QDebug>
#    include <QBuffer>
#endif

namespace hstd {
#if ORG_USE_QT
std::string descObjectPtr(QObject* obj);
#endif

template <typename T>
    requires std::is_class_v<T>
std::string descObjectPtr(T* obj) {
    return hstd::fmt(
        "{} 0x{:X}",
        hstd::demangle(typeid(obj).name()),
        reinterpret_cast<uintptr_t>(obj));
}

template <typename T>
    requires std::is_class_v<T>
std::string descObjectPtr(T const* obj) {
    return descObjectPtr(const_cast<T*>(obj));
}

template <typename T>
std::string descObjectPtr(T* obj) {
    return hstd::fmt("0x{:X}", reinterpret_cast<uintptr_t>(obj));
}


template <typename T>
std::string descObjectPtr(std::shared_ptr<T> const& ptr) {
    return descObjectPtr(ptr.get());
}

template <typename T>
std::string descObjectPtr(std::shared_ptr<T const> const& ptr) {
    return descObjectPtr(ptr.get());
}

template <typename T, typename Deleter = std::default_delete<T>>
std::string descObjectPtr(std::unique_ptr<T, Deleter> const& ptr) {
    return descObjectPtr(ptr.get());
}

template <typename T, typename Deleter = std::default_delete<T>>
std::string descObjectPtr(std::unique_ptr<T const, Deleter> const& ptr) {
    return descObjectPtr(ptr.get());
}
} // namespace hstd

namespace hstd::log {


struct log_graph_processor {
    virtual ~log_graph_processor() = default;

    struct callsite {
        int         line;
        char const* function;
        char const* file;

        static callsite this_callsite(
            int         line     = __builtin_LINE(),
            char const* function = __builtin_FUNCTION(),
            char const* file     = __builtin_FILE()) {
            return callsite{line, function, file};
        }

        DESC_FIELDS(callsite, (line, function, file));
        callsite(int line, char const* function, char const* file)
            : line{line}, function{function}, file{file} {}
    };

    struct tracked_info {
        callsite loc;
        DESC_FIELDS(tracked_info, (loc));
        tracked_info(callsite const& loc) : loc{loc} {}
    };

    struct function_info : public tracked_info {
        std::string                                 name;
        hstd::Vec<hstd::Pair<hstd::Str, hstd::Str>> args;
        BOOST_DESCRIBE_STRUCT(function_info, (tracked_info), (name, args));
        function_info(
            std::string const&                                 name,
            hstd::Vec<hstd::Pair<hstd::Str, hstd::Str>> const& args,
            callsite const&                                    loc)
            : tracked_info{loc}, name{name}, args{args} {}
    };

#if ORG_USE_QT
    struct signal_emit_info : public function_info {
        QObject const* sender;
        BOOST_DESCRIBE_STRUCT(
            signal_emit_info,
            (tracked_info),
            (name, sender, args));

        signal_emit_info(QObject const* sender, function_info const& func)
            : function_info{func}, sender{sender} {}
    };


    struct slot_trigger_info : public function_info {
        QObject const* sender;
        QObject const* receiver;
        BOOST_DESCRIBE_STRUCT(
            slot_trigger_info,
            (function_info),
            (sender, receiver));

        slot_trigger_info(
            QObject const*       sender,
            QObject const*       receiver,
            function_info const& func_info)
            : function_info{func_info.name, func_info.args, func_info.loc}
            , sender{sender}
            , receiver{receiver} {}
    };
#endif


    struct scope_info : public tracked_info {
        std::string name;
        BOOST_DESCRIBE_STRUCT(scope_info, (tracked_info), (name));
        scope_info(std::string const& name, callsite const& loc)
            : tracked_info{loc}, name{name} {}
    };

    struct named_text_info : public tracked_info {
        std::string key;
        std::string value;
        BOOST_DESCRIBE_STRUCT(
            named_text_info,
            (tracked_info),
            (key, value));

        named_text_info(
            std::string const& key,
            std::string const& value,
            callsite const&    loc)
            : tracked_info{loc}, key{key}, value{value} {}
    };


    struct named_jump_info : public tracked_info {
        std::string description;
        BOOST_DESCRIBE_STRUCT(
            named_jump_info,
            (tracked_info),
            (description));
        named_jump_info(std::string const& name, callsite const& loc)
            : tracked_info{loc}, description{name} {}
    };


#if ORG_USE_QT
    struct qobject_info : public tracked_info {
        QObject const* object;
        BOOST_DESCRIBE_STRUCT(qobject_info, (tracked_info), (object));
        qobject_info(QObject const* name, callsite const& loc)
            : tracked_info{loc}, object{name} {}
    };


    struct connect_info : public tracked_info {
        QObject const* sender;
        std::string    signal;
        QObject const* receiver;
        std::string    slot;
        BOOST_DESCRIBE_STRUCT(
            connect_info,
            (tracked_info),
            (sender, signal, receiver, slot));
        connect_info(
            QObject const*     name,
            std::string const& signal,
            QObject const*     receiver,
            std::string const& slot,
            callsite const&    loc)
            : tracked_info{loc}
            , sender{name}
            , signal{signal}
            , receiver{receiver}
            , slot{slot} {}
    };
#endif

    virtual void track_function_start(function_info const& info) = 0;
    virtual void track_function_end(function_info const& info)   = 0;

    virtual void track_scope_enter(scope_info const& info)     = 0;
    virtual void track_scope_exit(scope_info const& info)      = 0;
    virtual void track_started(tracked_info const& info)       = 0;
    virtual void track_ended(tracked_info const& info)         = 0;
    virtual void track_named_text(named_text_info const& info) = 0;
    virtual void track_named_jump(named_jump_info const& info) = 0;

#if ORG_USE_QT
    virtual void track_signal_emit(signal_emit_info const& info)   = 0;
    virtual void track_slot_trigger(slot_trigger_info const& info) = 0;
    virtual void track_qobject(qobject_info const& info)           = 0;
    virtual void track_connect(connect_info const& info)           = 0;
#endif
};

struct log_graph_tracker {
    void add_processor(
        std::shared_ptr<log_graph_processor> processor,
        int                                  line = __builtin_LINE(),
        char const* function                      = __builtin_FUNCTION(),
        char const* file                          = __builtin_FILE());

    void start_tracing(
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION(),
        char const* file     = __builtin_FILE()) {
        start_tracing(
            log_graph_processor::tracked_info(
                log_graph_processor::callsite(line, function, file)));
    }

    void end_tracing(
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION(),
        char const* file     = __builtin_FILE()) {
        end_tracing(
            log_graph_processor::tracked_info(
                log_graph_processor::callsite(line, function, file)));
    }

    void start_tracing(log_graph_processor::tracked_info const& info);
    void end_tracing(log_graph_processor::tracked_info const& info);

    void notify_function_start(
        log_graph_processor::function_info const& info);

    void notify_function_end(
        log_graph_processor::function_info const& info);

    void notify_scope_enter(log_graph_processor::scope_info const& info);

    void notify_scope_exit(log_graph_processor::scope_info const& info);

    void notify_named_text(
        log_graph_processor::named_text_info const& info);

    void notify_named_jump(
        log_graph_processor::named_jump_info const& info);

    template <typename T, typename... Args>
    void format_args_aux(
        hstd::Vec<std::string>& res,
        T const&                value,
        Args&&... args) {
        res.push_back(hstd::log::log_value_formatter<T>{}.format(value));
        format_args_aux(res, std::forward<Args>(args)...);
    }

    void format_args_aux(hstd::Vec<hstd::Str>& res) {}

    template <typename... Args>
    hstd::Vec<hstd::Str> format_args(Args&&... args) {
        hstd::Vec<hstd::Str> res;
        format_args_aux(res, std::forward<Args>(args)...);
        return res;
    }

    template <typename... Args>
    hstd::Vec<hstd::Pair<hstd::Str, hstd::Str>> format_args_with_vars(
        const hstd::Vec<hstd::Str>& names,
        const Args&... args) {
        hstd::Vec<hstd::Pair<hstd::Str, hstd::Str>> result;
        auto format_var = [](const auto& var) -> std::string {
            using VarType = std::decay_t<decltype(var)>;
            if constexpr (hstd::log::has_log_value_formatter<VarType>) {
                return hstd::log::log_value_formatter<VarType>{}.format(
                    var);
            } else if constexpr (hstd::StdFormattable<VarType>) {
                return std::format("{}", var);
            } else {
                return hstd::Str{"<type unformattable>"};
            }
        };

        auto values = std::vector<std::string>{format_var(args)...};
        for (size_t i = 0; i < names.size(); ++i) {
            result.push_back(
                hstd::Pair<hstd::Str, hstd::Str>{names[i], values[i]});
        }
        return result;
    }


#if ORG_USE_QT

    void notify_signal_emit(
        log_graph_processor::signal_emit_info const& info);

    void notify_slot_trigger(
        log_graph_processor::slot_trigger_info const& info);

    void notify_qobject(log_graph_processor::qobject_info const& info);


    template <typename T>
    static T const* get_ptr(T const* p) {
        return p;
    }

    template <typename T>
    static T const* get_ptr(std::shared_ptr<T> const& p) {
        return p.get();
    }

    auto track_qobject_pass(
        auto const&                          _this,
        log_graph_processor::callsite const& loc) {
        notify_qobject(
            log_graph_processor::qobject_info(get_ptr(_this), loc));
        return _this;
    }

    void notify_connect(log_graph_processor::connect_info const& info);


    hstd::finally_std track_slot(
        log_graph_processor::slot_trigger_info const& info);

#endif


    hstd::finally_std track_function(
        log_graph_processor::function_info const& info);

    hstd::finally_std track_scope(
        log_graph_processor::scope_info const& info);

    bool TraceState = false;

  private:
    std::vector<std::shared_ptr<log_graph_processor>> processors{};
};

#define HSLOG_VARNAMES_TO_ARG_VECTOR(__tracker, ...)                      \
    __tracker->format_args_with_vars(                                     \
        {__VA_OPT__(#__VA_ARGS__)} __VA_OPT__(, ) __VA_ARGS__)

#define HSLOG_TRACKED_EMIT(__tracker, method, ...)                        \
    __tracker->notify_signal_emit(                                        \
        ::hstd::log::log_graph_processor::signal_emit_info(               \
            this,                                                         \
            ::hstd::log::log_graph_processor::function_info(              \
                #method,                                                  \
                HSLOG_VARNAMES_TO_ARG_VECTOR(__tracker, __VA_ARGS__),     \
                ::hstd::log::log_graph_processor::callsite::              \
                    this_callsite())));                                   \
    emit method(__VA_ARGS__);

#define HSLOG_TRACKED_SLOT(__tracker, method, ...)                        \
    auto BOOST_PP_CAT(__scope, __COUNTER__) = __tracker->track_slot(      \
        ::hstd::log::log_graph_processor::slot_trigger_info(              \
            sender(),                                                     \
            this,                                                         \
            ::hstd::log::log_graph_processor::function_info(              \
                #method,                                                  \
                HSLOG_VARNAMES_TO_ARG_VECTOR(__tracker, __VA_ARGS__),     \
                ::hstd::log::log_graph_processor::callsite::              \
                    this_callsite())));


#define HSLOG_TRACKED_FUNCTION(__tracker, method, ...)                    \
    auto BOOST_PP_CAT(__scope, __COUNTER__) = __tracker->track_function(  \
        ::hstd::log::log_graph_processor::function_info(                  \
            #method,                                                      \
            HSLOG_VARNAMES_TO_ARG_VECTOR(__tracker, __VA_ARGS__),         \
            ::hstd::log::log_graph_processor::callsite::                  \
                this_callsite()));

#define HSLOG_TRACKED_SCOPE(__tracker, description)                       \
    auto BOOST_PP_CAT(__scope, __COUNTER__) = __tracker->track_scope(     \
        ::hstd::log::log_graph_processor::scope_info(                     \
            description,                                                  \
            ::hstd::log::log_graph_processor::callsite::                  \
                this_callsite()));

#define HSLOG_TRACKED_JUMP(__tracker, description)                        \
    __tracker->notify_named_jump(                                         \
        ::hstd::log::log_graph_processor::named_jump_info(                \
            description,                                                  \
            ::hstd::log::log_graph_processor::callsite::                  \
                this_callsite()));


#if ORG_USE_QT

#    define HSLOG_TRACKED_CONNECT(                                        \
        _tracker, _sender, _signal, _receiver, _slot, ...)                \
        _tracker->notify_connect(                                         \
            ::hstd::log::log_graph_processor::connect_info(               \
                _sender,                                                  \
                #_signal,                                                 \
                _receiver,                                                \
                #_slot,                                                   \
                ::hstd::log::log_graph_processor::callsite::              \
                    this_callsite()));                                    \
        QObject::connect(                                                 \
            _sender,                                                      \
            _signal,                                                      \
            _receiver,                                                    \
            _slot __VA_OPT__(, ) __VA_ARGS__);

#    define HSLOG_TRACKED_OBJECT(_tracker, _object)                       \
        _tracker->track_qobject_pass(                                     \
            _object,                                                      \
            ::hstd::log::log_graph_processor::callsite::this_callsite());

#endif

struct graphviz_processor : public log_graph_processor {
    struct call_info {
        std::string jump_description{};
        int         count{1};
    };

    struct node_info {
        std::string              name{};
        bool                     is_cluster{false};
        std::vector<std::string> children{};
        bool                     is_slot{false};
        bool                     is_signal{false};
        bool                     is_scope{false};
    };

    void track_function_start(function_info const& info) override;
    void track_function_end(function_info const& info) override;
    void track_scope_enter(scope_info const& info) override;
    void track_scope_exit(scope_info const& info) override;
    void track_started(tracked_info const& info) override;
    void track_ended(tracked_info const& info) override {}
    void track_named_text(named_text_info const& info) override {}
    void track_named_jump(named_jump_info const& info) override;

#if ORG_USE_QT
    void track_signal_emit(signal_emit_info const& info) override;
    void track_slot_trigger(slot_trigger_info const& info) override;
    void track_qobject(qobject_info const& info) override {}
    void track_connect(connect_info const& info) override {}
#endif

    hstd::ext::Graphviz::Graph get_graphviz();

  private:
    std::stack<std::string>                    call_stack{};
    std::unordered_map<std::string, node_info> nodes{};
    std::unordered_map<std::string, call_info> edges{};
    std::string                                pending_jump{};

    std::string get_parent();

    void add_edge(std::string const& from, std::string const& to);
};

struct logger_processor : public log_graph_processor {
    void track_function_start(function_info const& info) override;
    void track_function_end(function_info const& info) override;
    void track_scope_enter(scope_info const& info) override;
    void track_scope_exit(scope_info const& info) override;
    void track_started(tracked_info const& info) override;
    void track_ended(tracked_info const& info) override;
    void track_named_text(named_text_info const& info) override;
    void track_named_jump(named_jump_info const& info) override;

#if ORG_USE_QT
    void track_signal_emit(signal_emit_info const& info) override;
    void track_slot_trigger(slot_trigger_info const& info) override;
    void track_qobject(qobject_info const& info) override;
    void track_connect(connect_info const& info) override;
#endif
};
} // namespace hstd::log
