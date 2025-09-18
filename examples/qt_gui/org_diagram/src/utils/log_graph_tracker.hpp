#pragma once

#include <qobject.h>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <stack>
#include <hstd/ext/graphviz.hpp>

#if HAXORG_LOGGER_SUPPORT_QT
#    include <QDebug>
#    include <QBuffer>
#endif

namespace hstd {
std::string descObjectPtr(QObject* obj);
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
} // namespace hstd

namespace hstd::log {

template <typename T, typename Other = std::monostate>
struct log_value_formatter {
    static std::string format(T const& value) {
        return hstd::value_metadata<T>::typeName() + " not formattable";
    }
};

template <hstd::StdFormattable T>
struct log_value_formatter<T> {
    static std::string format(T const& value) { return hstd::fmt1(value); }
};

#if HAXORG_LOGGER_SUPPORT_QT
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

#endif

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
        std::string name;
        BOOST_DESCRIBE_STRUCT(function_info, (tracked_info), (name));
        function_info(std::string const& name, callsite const& loc)
            : tracked_info{loc}, name{name} {}
    };

    struct signal_emit_info : public tracked_info {
        std::string              name;
        QObject const*           sender;
        std::vector<std::string> args;
        BOOST_DESCRIBE_STRUCT(
            signal_emit_info,
            (tracked_info),
            (name, sender, args));

        signal_emit_info(
            QObject const*                  sender,
            std::string const&              name,
            std::vector<std::string> const& args,
            callsite const&                 loc)
            : tracked_info{loc}, name{name}, args{args}, sender{sender} {}
    };


    struct slot_trigger_info : public tracked_info {
        std::string              name;
        QObject const*           sender;
        QObject const*           receiver;
        std::vector<std::string> args;
        BOOST_DESCRIBE_STRUCT(
            slot_trigger_info,
            (tracked_info),
            (name, sender, receiver, args));

        slot_trigger_info(
            QObject const*                  sender,
            QObject const*                  receiver,
            std::string const&              name,
            std::vector<std::string> const& args,
            callsite const&                 loc)
            : tracked_info{loc}
            , name{name}
            , args{args}
            , sender{sender}
            , receiver{receiver} {}
    };


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

    virtual void track_function_start(function_info const& info)   = 0;
    virtual void track_function_end(function_info const& info)     = 0;
    virtual void track_signal_emit(signal_emit_info const& info)   = 0;
    virtual void track_slot_trigger(slot_trigger_info const& info) = 0;
    virtual void track_scope_enter(scope_info const& info)         = 0;
    virtual void track_scope_exit(scope_info const& info)          = 0;
    virtual void track_started(tracked_info const& info)           = 0;
    virtual void track_ended(tracked_info const& info)             = 0;
    virtual void track_named_text(named_text_info const& info)     = 0;
    virtual void track_named_jump(named_jump_info const& info)     = 0;
    virtual void track_qobject(qobject_info const& info)           = 0;
    virtual void track_connect(connect_info const& info)           = 0;
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
        start_tracing(log_graph_processor::tracked_info(
            log_graph_processor::callsite(line, function, file)));
    }

    void end_tracing(
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION(),
        char const* file     = __builtin_FILE()) {
        end_tracing(log_graph_processor::tracked_info(
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
        std::vector<std::string>& res,
        T const&                  value,
        Args&&... args) {
        res.push_back(hstd::log::log_value_formatter<T>::format(value));
        format_args_aux(res, std::forward<Args>(args)...);
    }

    void format_args_aux(std::vector<std::string>& res) {}

    template <typename... Args>
    std::vector<std::string> format_args(Args&&... args) {
        std::vector<std::string> res;
        format_args_aux(res, std::forward<Args>(args)...);
        return res;
    }


#if HAXORG_LOGGER_SUPPORT_QT

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


#define HSLOG_TRACKED_EMIT(__tracker, method, ...)                        \
    __tracker->notify_signal_emit(                                        \
        ::hstd::log::log_graph_processor::signal_emit_info(               \
            this,                                                         \
            #method,                                                      \
            __tracker->format_args(__VA_ARGS__),                          \
            ::hstd::log::log_graph_processor::callsite::                  \
                this_callsite()));                                        \
    emit method(__VA_ARGS__);

#define HSLOG_TRACKED_SLOT(__tracker, method, ...)                        \
    auto BOOST_PP_CAT(__scope, __COUNTER__) = __tracker->track_slot(      \
        ::hstd::log::log_graph_processor::slot_trigger_info(              \
            this,                                                         \
            sender(),                                                     \
            #method,                                                      \
            __tracker->format_args(__VA_ARGS__),                          \
            ::hstd::log::log_graph_processor::callsite::                  \
                this_callsite()));

#define HSLOG_TRACKED_FUNCTION(__tracker, method)                         \
    auto BOOST_PP_CAT(__scope, __COUNTER__) = __tracker->track_function(  \
        ::hstd::log::log_graph_processor::function_info(                  \
            #method,                                                      \
            ::hstd::log::log_graph_processor::callsite::                  \
                this_callsite()));

#if HAXORG_LOGGER_SUPPORT_QT

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


#if HAXORG_LOGGER_SUPPORT_QT
struct SignalDebugger : public QObject {
    Q_OBJECT

  private:
    QObject*                                      targetObject;
    std::vector<QMetaObject::Connection>          connections;
    std::shared_ptr<hstd::log::log_graph_tracker> tracker;

  public:
    explicit SignalDebugger(
        std::shared_ptr<hstd::log::log_graph_tracker> tracker,
        QObject*                                      sender,
        QObject*                                      parent = nullptr)
        : QObject{parent}, targetObject{sender}, tracker{tracker} {
        connectToAllSignals();
    }

    ~SignalDebugger() { disconnectAll(); }

  private:
    void                     connectToAllSignals();
    void                     connectToSignal(const QMetaMethod& signal);
    void                     disconnectAll();
    std::vector<std::string> formatParameterInfo(
        const QMetaMethod& method);

  private slots:
    void onSignalTriggered();

  public:
    void setEnabled(bool enabled) {
        if (enabled) {
            connectToAllSignals();
        } else {
            disconnectAll();
        }
    }
};

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

#if HAXORG_LOGGER_SUPPORT_QT
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

#if HAXORG_LOGGER_SUPPORT_QT
    void track_signal_emit(signal_emit_info const& info) override;
    void track_slot_trigger(slot_trigger_info const& info) override;
    void track_qobject(qobject_info const& info) override;
    void track_connect(connect_info const& info) override;
#endif
};
} // namespace hstd::log
