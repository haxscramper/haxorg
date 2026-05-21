// trace_log_viewer.cpp
#include "trace_log_viewer.hpp"

#include <optional>

namespace trace_log_viewer {

TraceLogViewer::TraceLogViewer() = default;

void TraceLogViewer::set_events(std::vector<TraceEvent> events) {
    events_ = std::move(events);
    rebuild();
}

void TraceLogViewer::clear() {
    events_.clear();
    records_.clear();
    record_index_.clear();
    root_events_.clear();
}

std::size_t TraceLogViewer::size() const { return events_.size(); }

bool TraceLogViewer::empty() const { return events_.empty(); }

auto TraceLogViewer::get_hierarchy() const -> EventHierarchy const& {
    static EventHierarchy hierarchy;
    hierarchy.roots        = root_events_;
    hierarchy.nestedGetter = [this](EventId id) {
        return get_nested_events_impl(id);
    };
    return hierarchy;
}

void TraceLogViewer::draw() {
    if (empty()) {
        ImGui::TextUnformatted("No trace events");
        return;
    }

    ImGuiTableFlags flags = ImGuiTableFlags_BordersInnerV
                          | ImGuiTableFlags_RowBg
                          | ImGuiTableFlags_Resizable
                          | ImGuiTableFlags_ScrollY;

    if (ImGui::BeginTable("trace_log_table", 4, flags)) {
        ImGui::TableSetupColumn(
            "nesting", ImGuiTableColumnFlags_WidthFixed, columns_.nesting);
        ImGui::TableSetupColumn(
            "name", ImGuiTableColumnFlags_WidthStretch, columns_.name);
        ImGui::TableSetupColumn(
            "message",
            ImGuiTableColumnFlags_WidthStretch,
            columns_.message);
        ImGui::TableSetupColumn(
            "source", ImGuiTableColumnFlags_WidthStretch, columns_.source);

        for (EventId id : root_events_) { draw_event_row_recursive(id); }

        columns_.nesting = ImGui::TableGetColumnWidth(0);
        columns_.name    = ImGui::TableGetColumnWidth(1);
        columns_.message = ImGui::TableGetColumnWidth(2);
        columns_.source  = ImGui::TableGetColumnWidth(3);

        ImGui::EndTable();
    }
}

void TraceLogViewer::rebuild() {
    records_.clear();
    record_index_.clear();
    root_events_.clear();

    build_event_hierarchy();
    build_record_index();
}

void TraceLogViewer::build_record_index() {
    record_index_.clear();
    for (std::size_t i = 0; i < records_.size(); ++i) {
        record_index_.insert({records_[i].id, i});
    }
}

void TraceLogViewer::build_event_hierarchy() {
    struct OpenFrame {
        EventId     id;
        std::string name;
    };

    std::vector<OpenFrame> open_stack;

    records_.reserve(events_.size());

    for (std::size_t i = 0; i < events_.size(); ++i) {
        EventId     id    = i;
        auto const& event = events_[i];

        EventRecord record{
            .id            = id,
            .event         = &event,
            .nesting_level = open_stack.size(),
            .nested_events = {},
        };

        records_.push_back(record);

        if (!open_stack.empty()) {
            records_[open_stack.back().id].nested_events.push_back(id);
        } else {
            root_events_.push_back(id);
        }

        if (is_begin_event(event)) {
            open_stack.push_back(
                OpenFrame{
                    .id   = id,
                    .name = format_name(event),
                });
        } else if (is_end_event(event)) {
            if (!open_stack.empty()) { open_stack.pop_back(); }
        }
    }
}

auto TraceLogViewer::get_record(EventId id) const -> EventRecord const& {
    return records_.at(record_index_.at(id));
}

TraceEvent const& TraceLogViewer::get_event(EventId id) const {
    return *get_record(id).event;
}

std::vector<EventId> TraceLogViewer::get_nested_events_impl(
    EventId id) const {
    return get_record(id).nested_events;
}

bool TraceLogViewer::is_begin_event(TraceEvent const& event) const {
    return std::visit(
        [](auto const& value) {
            return std::decay_t<decltype(value)>::ph == 'B';
        },
        event);
}

bool TraceLogViewer::is_end_event(TraceEvent const& event) const {
    return std::visit(
        [](auto const& value) {
            return std::decay_t<decltype(value)>::ph == 'E';
        },
        event);
}

bool TraceLogViewer::is_instant_event(TraceEvent const& event) const {
    return std::visit(
        [](auto const& value) {
            return std::decay_t<decltype(value)>::ph == 'I';
        },
        event);
}

TraceEventBase const& TraceLogViewer::get_base(
    TraceEvent const& event) const {
    return std::visit(
        [](auto const& value) -> TraceEventBase const& { return value; },
        event);
}

StackTraceEventBase const* TraceLogViewer::get_stack_base(
    TraceEvent const& event) const {
    return std::visit(
        [](auto const& value) -> StackTraceEventBase const* {
            return &value;
        },
        event);
}

CommonEventArgs const& TraceLogViewer::get_args(
    TraceEvent const& event) const {
    return get_base(event).args;
}

std::string TraceLogViewer::format_name(TraceEvent const& event) const {
    auto const& base = get_base(event);
    if (base.name) {
        return std::format(
            "{} [{}]", *base.name, format_event_kind(event));
    } else {
        return std::format("[{}]", format_event_kind(event));
    }
}

std::string TraceLogViewer::format_message(TraceEvent const& event) const {
    auto const& args = get_args(event);

    if (args.message && !args.message->empty()) {
        return *args.message;
    } else {
        return {};
    }
}

std::string TraceLogViewer::format_source(TraceEvent const& event) const {
    auto const& args = get_args(event);
    return std::format("{}:{} {}", args.file, args.line, args.function);
}

std::string TraceLogViewer::format_event_kind(
    TraceEvent const& event) const {
    if (is_begin_event(event)) {
        return "Begin";
    } else if (is_end_event(event)) {
        return "End";
    } else {
        return "Instant";
    }
}

std::string TraceLogViewer::format_scope_offset(
    std::size_t nesting_level) const {
    return std::format("{}", nesting_level);
}

void TraceLogViewer::draw_event_row_recursive(EventId id) {
    auto const& record     = get_record(id);
    bool const  has_nested = !record.nested_events.empty();
    bool        open       = true;

    draw_event_row(record, has_nested, &open);

    if (!open) { return; }

    draw_event_state(record);

    for (EventId nested : record.nested_events) {
        draw_event_row_recursive(nested);
    }
}

void TraceLogViewer::draw_event_row(
    EventRecord const& record,
    bool               has_nested,
    bool*              open_state) {

    TraceEvent const& event = *record.event;
    std::string const label = std::format("##event_row_{}", record.id);

    ImGui::TableNextRow();
    ImGui::PushID(static_cast<int>(record.id));

    ImGui::TableSetColumnIndex(0);

    if (has_nested) {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAllColumns
                                 | ImGuiTreeNodeFlags_AllowOverlap
                                 | ImGuiTreeNodeFlags_FramePadding;
        *open_state              = ImGui::TreeNodeEx(
            label.c_str(),
            flags,
            "%s",
            format_scope_offset(record.nesting_level).c_str());
    } else {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAllColumns
                                 | ImGuiTreeNodeFlags_Leaf
                                 | ImGuiTreeNodeFlags_NoTreePushOnOpen
                                 | ImGuiTreeNodeFlags_Bullet
                                 | ImGuiTreeNodeFlags_FramePadding;
        ImGui::TreeNodeEx(
            label.c_str(),
            flags,
            "%s",
            format_scope_offset(record.nesting_level).c_str());
        *open_state = true;
    }

    ImGui::TableSetColumnIndex(1);
    ImGui::TextUnformatted(format_name(event).c_str());

    ImGui::TableSetColumnIndex(2);
    ImGui::TextUnformatted(format_message(event).c_str());

    ImGui::TableSetColumnIndex(3);
    ImGui::TextUnformatted(format_source(event).c_str());

    if (has_nested && *open_state) { ImGui::TreePop(); }

    ImGui::PopID();
}

void TraceLogViewer::draw_event_state(EventRecord const& record) {
    auto const& args = get_args(*record.event);
    if (!args.state) { return; }

    auto const& state = *args.state;

    if (state.value) {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Indent(record.nesting_level * 12.0f);
        draw_structured_value(*state.value, "value");
        ImGui::Unindent(record.nesting_level * 12.0f);
    }

    if (state.variables) {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Indent(record.nesting_level * 12.0f);
        draw_variables_state(*state.variables);
        ImGui::Unindent(record.nesting_level * 12.0f);
    }
}

void TraceLogViewer::draw_structured_value(
    StructuredValue const& value,
    char const*            label) {
    std::string node_label;

    if (label) {
        if (value.shortRepr) {
            node_label = std::format("{}: {}", label, *value.shortRepr);
        } else {
            node_label = std::format("{}", label);
        }
    } else if (value.shortRepr) {
        node_label = *value.shortRepr;
    } else {
        node_label = "value";
    }

    std::visit(
        overloaded{
            [&](StructuredValue::Scalar const&) {
                ImGui::TextUnformatted(node_label.c_str());
            },
            [&](StructuredValue::Enum const& data) {
                ImGui::TextUnformatted(
                    std::format(
                        "{} = {} ({})", node_label, data.value, data.index)
                        .c_str());
            },
            [&](StructuredValue::List const& data) {
                if (ImGui::TreeNode(node_label.c_str())) {
                    for (std::size_t i = 0; i < data.values.size(); ++i) {
                        draw_structured_value(
                            data.values[i],
                            std::format("[{}]", i).c_str());
                    }
                    ImGui::TreePop();
                }
            },
            [&](StructuredValue::Map const& data) {
                if (ImGui::TreeNode(node_label.c_str())) {
                    for (std::size_t i = 0; i < data.pairs.size(); ++i) {
                        auto const& pair = data.pairs[i];
                        if (ImGui::TreeNode(
                                std::format("pair {}", i).c_str())) {
                            if (pair.key) {
                                draw_structured_value(*pair.key, "key");
                            }
                            if (pair.value) {
                                draw_structured_value(
                                    *pair.value, "value");
                            }
                            ImGui::TreePop();
                        }
                    }
                    ImGui::TreePop();
                }
            },
            [&](StructuredValue::Object const& data) {
                std::string object_label = std::format(
                    "{} <{}>", node_label, data.type);
                if (ImGui::TreeNode(object_label.c_str())) {
                    for (auto const& field : data.fields) {
                        if (field.value) {
                            draw_structured_value(
                                *field.value, field.name.c_str());
                        }
                    }
                    ImGui::TreePop();
                }
            }},
        value.data);
}

void TraceLogViewer::draw_variables_state(
    VariablesState const& variables) {
    if (ImGui::TreeNode(
            std::format("variables ({})", variables.variables.size())
                .c_str())) {
        for (auto const& variable : variables.variables) {
            std::string label = variable.type ? std::format(
                                                    "{}: {}",
                                                    variable.name,
                                                    *variable.type)
                                              : variable.name;
            draw_structured_value(variable.value, label.c_str());
        }
        ImGui::TreePop();
    }
}

} // namespace trace_log_viewer
