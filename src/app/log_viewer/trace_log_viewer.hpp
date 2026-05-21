#pragma once

#include <algorithm>
#include <cstddef>
#include <format>
#include <functional>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

#include <imgui.h>

namespace trace_log_viewer {

using EventId = std::size_t;

class TraceLogViewer {
  public:
    struct EventHierarchy {
        using NestedGetter = std::function<std::vector<EventId>(EventId)>;

        std::vector<EventId> roots;
        NestedGetter         nestedGetter;

        [[nodiscard]] std::vector<EventId> get_nested_events(
            EventId id) const {
            return nestedGetter ? nestedGetter(id)
                                : std::vector<EventId>{};
        }
    };

    TraceLogViewer();

    void set_events(std::vector<TraceEvent> events);
    void clear();
    void draw();

    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] bool        empty() const;

    [[nodiscard]] EventHierarchy const& get_hierarchy() const;

  private:
    struct EventLink {
        EventId           id;
        TraceEvent const* event;
    };

    struct EventRecord {
        EventId              id;
        TraceEvent const*    event;
        std::size_t          nesting_level;
        std::vector<EventId> nested_events;
    };

    struct RenderColumns {
        float nesting = 120.0f;
        float name    = 200.0f;
        float message = 260.0f;
        float source  = 260.0f;
    };

  private:
    std::vector<TraceEvent>                  events_;
    std::vector<EventRecord>                 records_;
    std::unordered_map<EventId, std::size_t> record_index_;
    std::vector<EventId>                     root_events_;
    RenderColumns                            columns_;

  private:
    void rebuild();
    void build_event_hierarchy();
    void build_record_index();

    [[nodiscard]] EventRecord const&   get_record(EventId id) const;
    [[nodiscard]] TraceEvent const&    get_event(EventId id) const;
    [[nodiscard]] std::vector<EventId> get_nested_events_impl(
        EventId id) const;

    [[nodiscard]] bool is_begin_event(TraceEvent const& event) const;
    [[nodiscard]] bool is_end_event(TraceEvent const& event) const;
    [[nodiscard]] bool is_instant_event(TraceEvent const& event) const;

    [[nodiscard]] TraceEventBase const& get_base(
        TraceEvent const& event) const;
    [[nodiscard]] StackTraceEventBase const* get_stack_base(
        TraceEvent const& event) const;
    [[nodiscard]] CommonEventArgs const& get_args(
        TraceEvent const& event) const;

    [[nodiscard]] std::string format_name(TraceEvent const& event) const;
    [[nodiscard]] std::string format_message(
        TraceEvent const& event) const;
    [[nodiscard]] std::string format_source(TraceEvent const& event) const;
    [[nodiscard]] std::string format_event_kind(
        TraceEvent const& event) const;
    [[nodiscard]] std::string format_scope_offset(
        std::size_t nesting_level) const;

    void draw_event_row_recursive(EventId id);
    void draw_event_row(
        EventRecord const& record,
        bool               has_nested,
        bool*              open_state);
    void draw_event_state(EventRecord const& record);
    void draw_structured_value(
        StructuredValue const& value,
        char const*            label = nullptr);
    void draw_variables_state(VariablesState const& variables);
};

} // namespace trace_log_viewer
