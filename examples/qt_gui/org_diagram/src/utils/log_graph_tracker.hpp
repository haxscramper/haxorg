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
std::string formatToString(const T& value) {
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
        return formatToString(value);
    }
};

#endif

struct log_graph_processor {
    virtual ~log_graph_processor() = default;
    virtual void track_function_start(
        std::string const& function_name,
        int                line,
        char const*        function,
        char const*        file)
        = 0;
    virtual void track_function_end(
        std::string const& function_name,
        int                line,
        char const*        function,
        char const*        file)
        = 0;

    virtual void track_signal_emit(
        QObject const*                  _this,
        std::string const&              signal_name,
        std::vector<std::string> const& args,
        int                             line,
        char const*                     function,
        char const*                     file)
        = 0;
    virtual void track_slot_trigger(
        QObject const*                  _this,
        std::string const&              slot_name,
        std::vector<std::string> const& args,
        int                             line,
        char const*                     function,
        char const*                     file)
        = 0;

    virtual void track_scope_enter(
        std::string const& scope_name,
        int                line,
        char const*        function,
        char const*        file)
        = 0;
    virtual void track_scope_exit(
        std::string const& scope_name,
        int                line,
        char const*        function,
        char const*        file)
        = 0;
    virtual void track_started(int line, char const* function, char const* file) = 0;
    virtual void track_ended(int line, char const* function, char const* file) = 0;
    virtual void track_named_text(
        std::string const& key,
        std::string const& value,
        int                line,
        char const*        function,
        char const*        file)
        = 0;
    virtual void track_named_jump(
        std::string const& description,
        int                line,
        char const*        function,
        char const*        file)
        = 0;

    virtual void track_qobject(
        QObject const* _this,
        int            line,
        char const*    function,
        char const*    file)
        = 0;

    virtual void track_connect(
        QObject const*     emitter,
        std::string const& signal,
        QObject const*     receiver,
        std::string const& slot,
        int                line,
        char const*        function,
        char const*        file)
        = 0;
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
        char const* file     = __builtin_FILE());

    void end_tracing(
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION(),
        char const* file     = __builtin_FILE());

    void notify_function_start(
        std::string const& function_name,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE());

    void notify_function_end(
        std::string const& function_name,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE());


    void notify_scope_enter(
        std::string const& scope_name,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE());

    void notify_scope_exit(
        std::string const& scope_name,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE());

    void notify_named_text(
        std::string const& key,
        std::string const& value,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE());

    void notify_named_jump(
        std::string const& description,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE());

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

#define HSLOG_TRACKED_EMIT(__tracker, method, ...)                        \
    __tracker->notify_signal_emit(                                        \
        this, #method, __tracker->format_args(__VA_ARGS__));              \
    emit method(__VA_ARGS__);

#define HSLOG_TRACKED_SLOT(__tracker, method, ...)                        \
    auto BOOST_PP_CAT(__scope, __COUNTER__) = __tracker->track_slot(      \
        this, #method, __tracker->format_args(__VA_ARGS__));

#define HSLOG_TRACKED_FUNCTION(__tracker, method)                         \
    auto BOOST_PP_CAT(__scope, __COUNTER__) = __tracker->track_function(  \
        #method);

#if HAXORG_LOGGER_SUPPORT_QT

    void notify_signal_emit(
        QObject const*                  _this,
        std::string const&              signal_name,
        std::vector<std::string> const& args,
        int                             line     = __builtin_LINE(),
        char const*                     function = __builtin_FUNCTION(),
        char const*                     file     = __builtin_FILE());

    void notify_slot_trigger(
        QObject const*                  _this,
        std::string const&              slot_name,
        std::vector<std::string> const& args,
        int                             line     = __builtin_LINE(),
        char const*                     function = __builtin_FUNCTION(),
        char const*                     file     = __builtin_FILE());

    void track_qobject(
        QObject const* _this,
        int            line     = __builtin_LINE(),
        char const*    function = __builtin_FUNCTION(),
        char const*    file     = __builtin_FILE());


    template <typename T>
    static T const* get_ptr(T const* p) {
        return p;
    }

    template <typename T>
    static T const* get_ptr(std::shared_ptr<T> const& p) {
        return p.get();
    }

    template <typename Q>
    auto track_qobject_pass(
        auto        _this,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION(),
        char const* file     = __builtin_FILE()) {
        track_qobject(get_ptr(_this), line, function, file);
        return _this;
    }

    void track_connect(
        QObject const*     emitter,
        std::string const& signal,
        QObject const*     receiver,
        std::string const& slot,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE());


    hstd::finally_std track_slot(
        const QObject*                  _this,
        std::string const&              description,
        std::vector<std::string> const& args,
        int                             line     = __builtin_LINE(),
        char const*                     function = __builtin_FUNCTION(),
        char const*                     file     = __builtin_FILE());

#    define HSLOG_TRACKED_CONNECT(                                        \
        _tracker, _sender, _signal, _receiver, _slot)                     \
        _tracker->track_connect(_sender, #_signal, _receiver, #_slot);    \
        QObject::connect(_sender, _signal, _receiver, _slot);

#    define HSLOG_TRACKED_OBJECT(_tracker, _object)                       \
        _tracker->track_qobject_pass(_object);

#endif


    hstd::finally_std track_function(
        std::string const& description,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE());

    hstd::finally_std track_scope(
        std::string const& description,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE());

  private:
    bool TraceState = false;

    std::vector<std::shared_ptr<log_graph_processor>> processors{};
};

struct call_info {
    std::string jump_description{};
    int         count{1};
};

struct node_info {
    std::string              name{};
    bool                     is_cluster{false};
    std::vector<std::string> children{};
};

struct graphviz_processor : public log_graph_processor {
    void track_function_start(
        std::string const& function_name,
        int                line,
        char const*        function,
        char const*        file) override;

    void track_function_end(
        std::string const& function_name,
        int                line,
        char const*        function,
        char const*        file) override;

    void track_scope_enter(
        std::string const& scope_name,
        int                line,
        char const*        function,
        char const*        file) override;

    void track_scope_exit(
        std::string const& scope_name,
        int                line,
        char const*        function,
        char const*        file) override;

    void track_started(int line, char const* function, char const* file)
        override;

    void track_ended(int line, char const* function, char const* file)
        override {}

    void track_named_text(
        std::string const& key,
        std::string const& value,
        int                line,
        char const*        function,
        char const*        file) override {}

    void track_named_jump(
        std::string const& description,
        int                line,
        char const*        function,
        char const*        file) override;

#if HAXORG_LOGGER_SUPPORT_QT
    void track_signal_emit(
        const QObject*                  _this,
        std::string const&              signal_name,
        std::vector<std::string> const& args,
        int                             line,
        char const*                     function,
        char const*                     file) override;

    void track_slot_trigger(
        const QObject*                  _this,
        std::string const&              slot_name,
        std::vector<std::string> const& args,
        int                             line,
        char const*                     function,
        char const*                     file) override;

    void track_qobject(
        const QObject* _this,
        int            line,
        const char*    function,
        const char*    file) override {}

    void track_connect(
        const QObject*     emitter,
        const std::string& signal,
        const QObject*     receiver,
        const std::string& slot,
        int                line,
        const char*        function,
        const char*        file) override {}
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
    void track_function_start(
        std::string const& function_name,
        int                line,
        char const*        function,
        char const*        file) override;

    void track_function_end(
        std::string const& function_name,
        int                line,
        char const*        function,
        char const*        file) override;


    void track_scope_enter(
        std::string const& scope_name,
        int                line,
        char const*        function,
        char const*        file) override;

    void track_scope_exit(
        std::string const& scope_name,
        int                line,
        char const*        function,
        char const*        file) override;

    void track_started(int line, char const* function, char const* file)
        override;

    void track_ended(int line, char const* function, char const* file)
        override;

    void track_named_text(
        std::string const& key,
        std::string const& value,
        int                line,
        char const*        function,
        char const*        file) override;

    void track_named_jump(
        std::string const& description,
        int                line,
        char const*        function,
        char const*        file) override;

#if HAXORG_LOGGER_SUPPORT_QT
    void track_signal_emit(
        QObject const*                  _this,
        std::string const&              signal_name,
        std::vector<std::string> const& args,
        int                             line,
        char const*                     function,
        char const*                     file) override;

    void track_slot_trigger(
        QObject const*                  _this,
        std::string const&              slot_name,
        std::vector<std::string> const& args,
        int                             line,
        char const*                     function,
        char const*                     file) override;

    void track_qobject(
        const QObject* _this,
        int            line,
        const char*    function,
        const char*    file) override;

    void track_connect(
        const QObject*     emitter,
        const std::string& signal,
        const QObject*     receiver,
        const std::string& slot,
        int                line,
        const char*        function,
        const char*        file) override;
#endif
};
} // namespace hstd::log
