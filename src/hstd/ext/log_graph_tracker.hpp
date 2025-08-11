#pragma once

#include <vector>
#include <memory>
#include <string>
#include <mutex>
#include <atomic>
#include <unordered_map>
#include <stack>

namespace hstd::log {

struct log_graph_processor {
    virtual ~log_graph_processor() = default;
    virtual void track_function_start(std::string const& function_name) = 0;
    virtual void track_function_end(std::string const& function_name) = 0;
    virtual void track_signal_emit(
        std::string const&              signal_name,
        std::vector<std::string> const& args)
        = 0;
    virtual void track_slot_trigger(
        std::string const&              slot_name,
        std::vector<std::string> const& args)
        = 0;
    virtual void track_scope_enter(std::string const& scope_name) = 0;
    virtual void track_scope_exit(std::string const& scope_name)  = 0;
    virtual void track_started()                                  = 0;
    virtual void track_ended()                                    = 0;
    virtual void track_named_text(std::string const& key, std::string const& value) = 0;
    virtual void track_named_jump(std::string const& description) = 0;
};

struct log_graph_tracker {
    static log_graph_tracker& instance() {
        static log_graph_tracker inst{};
        return inst;
    }

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

    void notify_signal_emit(
        std::string const&              signal_name,
        std::vector<std::string> const& args,
        int                             line     = __builtin_LINE(),
        char const*                     function = __builtin_FUNCTION(),
        char const*                     file     = __builtin_FILE());

    void notify_slot_trigger(
        std::string const&              slot_name,
        std::vector<std::string> const& args,
        int                             line     = __builtin_LINE(),
        char const*                     function = __builtin_FUNCTION(),
        char const*                     file     = __builtin_FILE());

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

  private:
    std::mutex                                        mutex{};
    std::atomic<bool>                                 tracing{false};
    std::vector<std::shared_ptr<log_graph_processor>> processors{};
};

struct function_tracker {
    function_tracker(std::string const& name) : function_name{name} {
        log_graph_tracker::instance().notify_function_start(function_name);
    }

    ~function_tracker() {
        log_graph_tracker::instance().notify_function_end(function_name);
    }

  private:
    std::string function_name;
};

struct scope_tracker {
    scope_tracker(std::string const& name) : scope_name{name} {
        log_graph_tracker::instance().notify_scope_enter(scope_name);
    }

    ~scope_tracker() {
        log_graph_tracker::instance().notify_scope_exit(scope_name);
    }

  private:
    std::string scope_name;
};

#define HSLOG_GRAPH_TRACK_FUNCTION(functionName)                          \
    function_tracker _func_tracker { #functionName }

#define HSLOG_GRAPH_TRACK_SCOPE(scopeName)                                \
    scope_tracker _scope_tracker { scopeName }

#define HSLOG_GRAPH_TRACK_SIGNAL(signalName, ...)                         \
    do {                                                                  \
        std::vector<std::string> args{};                                  \
        ((args.push_back(std::format("{}", __VA_ARGS__))), ...);          \
        log_graph_tracker::instance().notify_signal_emit(                 \
            #signalName, args);                                           \
    } while (0)

#define HSLOG_GRAPH_TRACK_SLOT(slotName, ...)                             \
    do {                                                                  \
        std::vector<std::string> args{};                                  \
        ((args.push_back(std::format("{}", __VA_ARGS__))), ...);          \
        log_graph_tracker::instance().notify_slot_trigger(                \
            #slotName, args);                                             \
    } while (0)

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
    void track_function_start(std::string const& function_name) override;

    void track_function_end(std::string const& function_name) override;

    void track_signal_emit(
        std::string const&              signal_name,
        std::vector<std::string> const& args) override;

    void track_slot_trigger(
        std::string const&              slot_name,
        std::vector<std::string> const& args) override;

    void track_scope_enter(std::string const& scope_name) override;

    void track_scope_exit(std::string const& scope_name) override;

    void track_started() override;

    void track_ended() override {}

    void track_named_text(std::string const& key, std::string const& value)
        override {}

    void track_named_jump(std::string const& description) override;

    void write_graphviz(std::string const& filename);

  private:
    std::stack<std::string>                    call_stack{};
    std::unordered_map<std::string, node_info> nodes{};
    std::unordered_map<std::string, call_info> edges{};
    std::string                                pending_jump{};

    std::string get_parent();

    void add_edge(std::string const& from, std::string const& to);
};
} // namespace hstd::log
