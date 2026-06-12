#pragma once

#include <hstd/stdlib/TraceBaseStructuredLog.hpp>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include <imgui.h>

using namespace hstd::log::record;
using namespace hstd;

using EventId = int;

class TraceLogViewer {
  public:
    struct EventHierarchy {
        using NestedGetter = std::function<Vec<EventId>(EventId)>;

        Vec<EventId> roots;
        NestedGetter nestedGetter;

        Vec<EventId> get_nested_events(EventId id) const {
            return nestedGetter ? nestedGetter(id) : Vec<EventId>{};
        }
    };

    TraceLogViewer();

    void set_events(Vec<TraceEvent> events);
    void clear();
    void draw();

    int  size() const;
    bool empty() const;

    EventHierarchy const& get_hierarchy() const;

  private:
    struct EventLink {
        EventId           id;
        TraceEvent const* event;
    };

    struct EventRecord {
        EventId           id;
        TraceEvent const* event;
        int               nesting_level;
        Vec<EventId>      nested_events;
    };

    struct RenderColumns {
        float nesting = 120.0f;
        float name    = 200.0f;
        float message = 260.0f;
        float source  = 260.0f;
    };

  private:
    Vec<TraceEvent>                  events;
    Vec<EventRecord>                 records;
    std::unordered_map<EventId, int> record_index;
    Vec<EventId>                     root_events;
    RenderColumns                    columns;

  private:
    void rebuild();
    void build_event_hierarchy();
    void build_record_index();

    EventRecord const& get_record(EventId id) const;
    TraceEvent const&  get_event(EventId id) const;
    Vec<EventId>       get_nested_events_impl(EventId id) const;

    bool is_begin_event(TraceEvent const& event) const;
    bool is_end_event(TraceEvent const& event) const;
    bool is_instant_event(TraceEvent const& event) const;

    TraceEventBase const&  get_base(TraceEvent const& event) const;
    CommonEventArgs const& get_args(TraceEvent const& event) const;

    std::string format_name(TraceEvent const& event) const;
    std::string format_message(TraceEvent const& event) const;
    std::string format_source(TraceEvent const& event) const;
    std::string format_event_kind(TraceEvent const& event) const;
    std::string format_scope_offset(int nesting_level) const;

    void draw_event_row_recursive(EventId id);
    void draw_event_row(EventRecord const& record, bool has_nested, bool* open_state);
    void draw_event_state(EventRecord const& record);
    void draw_structured_value(StructuredValue const& value, char const* label = nullptr);
    void draw_variables_state(VariablesState const& variables);
};
