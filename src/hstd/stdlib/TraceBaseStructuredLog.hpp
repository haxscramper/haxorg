#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/JsonUse.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/Pair.hpp>

namespace hstd::log::record {
using StrOrInt      = Variant<Str, int>;
using JsonPrimitive = Variant<Str, int, float, bool, std::nullptr_t>;
using JsonValue     = json;
using JsonObject    = UnorderedMap<Str, JsonValue>;

/// \brief Base trace model configuration carrier.
struct TraceBaseModel {
    DESC_FIELDS(TraceBaseModel, ());
};

/// \brief Source descriptor.
struct Source {
    /// \brief Human-readable source name.
    Opt<Str> name;
    /// \brief Filesystem path or logical source path.
    Opt<Str> path;

    DESC_FIELDS(Source, (name, path));
};

/// \brief Structured value descriptor.
struct StructuredValue {
    /// \brief Short textual representation suitable for compact display.
    Opt<Str> shortRepr;
    /// \brief Stable identifier for this value.
    Opt<Str> valueId;

    struct Scalar {
        DESC_FIELDS(Scalar, ());
    };

    struct List {
        Vec<StructuredValue> values;
        DESC_FIELDS(List, (values));
    };

    struct MapPair {
        std::shared_ptr<StructuredValue> key;
        std::shared_ptr<StructuredValue> value;
        DESC_FIELDS(MapPair, (key, value));
    };

    struct Map {
        Vec<MapPair> pairs;
        DESC_FIELDS(Map, (pairs));
    };

    struct Field {
        Str                         name;
        hstd::SPtr<StructuredValue> value;
        DESC_FIELDS(Field, (name, value));
    };

    struct Object {
        Str        type;
        Vec<Field> fields;
        DESC_FIELDS(Object, (type, fields));
    };

    struct Enum {
        int index;
        Str value;
        DESC_FIELDS(Enum, (index, value));
    };

    SUB_VARIANTS(
        Kind,
        Data,
        data,
        getKind,
        List,
        Scalar,
        Map,
        Object,
        Enum);

    Data data;

    DESC_FIELDS(StructuredValue, (shortRepr, valueId, data));
};

/// \brief Debugger variable entry.
struct Variable {
    /// \brief Variable name.
    Str name;
    /// \brief Structured value description.
    StructuredValue value;
    /// \brief Declared or inferred type name.
    Opt<Str> type;


    DESC_FIELDS(Variable, (name, value, type));
};

/// \brief Variable collection snapshot.
struct VariablesState {
    /// \brief Variables captured for a state snapshot.
    Vec<Variable> variables;

    DESC_FIELDS(VariablesState, (variables));
};

/// \brief Scope snapshot.
struct ScopeState {
    /// \brief Scope name.
    Str            name;
    VariablesState variables;
    /// \brief Associated source.
    Opt<Source> source;
    /// \brief 1-based starting line.
    Opt<int> line;
    /// \brief 1-based starting column.
    Opt<int> column;
    /// \brief 1-based ending line.
    Opt<int> endLine;
    /// \brief 1-based ending column.
    Opt<int> endColumn;

    DESC_FIELDS(
        ScopeState,
        (name, source, line, column, endLine, endColumn));
};

/// \brief Scope collection snapshot.
struct ScopesState {
    /// \brief Scopes captured for a frame/event.
    Vec<ScopeState> scopes;

    DESC_FIELDS(ScopesState, (scopes));
};

/// \brief Debug stack frame.
struct DebugStackFrame {
    /// \brief Stable frame identifier.
    int id;
    /// \brief Human-readable frame name.
    Str name;
    /// \brief Source file information.
    Opt<Source> source;
    /// \brief 1-based frame line.
    int line;
    /// \brief 1-based frame column.
    int column;
    /// \brief 1-based ending line.
    Opt<int> endLine;
    /// \brief 1-based ending column.
    Opt<int> endColumn;
    /// \brief Optional instruction pointer reference.
    Opt<Str> instructionPointerReference;
    /// \brief Optional module identifier.
    Opt<StrOrInt> moduleId;
    /// \brief UI presentation hint.
    /// \warning Allowed values: normal, label, subtle.
    Opt<Str> presentationHint;

    DESC_FIELDS(
        DebugStackFrame,
        (id,
         name,
         source,
         line,
         column,
         endLine,
         endColumn,
         instructionPointerReference,
         moduleId,
         presentationHint));
};

/// \brief Debug stack trace payload.
struct DebugStackTrace {
    /// \brief Captured stack frames.
    Vec<DebugStackFrame> stackFrames;
    /// \brief Total available frame count.
    Opt<int> totalFrames;

    DESC_FIELDS(DebugStackTrace, (stackFrames, totalFrames));
};

/// \brief Object reference descriptor.
struct ObjectReference {
    /// \brief Referenced object identifier.
    StrOrInt id_ref;
    /// \brief Optional disambiguating scope.
    Opt<Str> scope;

    DESC_FIELDS(ObjectReference, (id_ref, scope));
};

/// \brief Snapshot payload overrides.
struct SnapshotPayload {
    /// \brief Optional category override.
    Opt<Str> cat;
    /// \brief Optional base type name.
    Opt<Str> base_type;

    DESC_FIELDS(SnapshotPayload, (cat, base_type));
};

/// \brief Event state payload.
struct TraceEventState {
    Opt<StructuredValue> value;
    Opt<VariablesState>  variables;
    Opt<ScopesState>     scopes;
    Opt<DebugStackTrace> stackTrace;
    Opt<Source>          source;

    DESC_FIELDS(
        TraceEventState,
        (value, variables, scopes, stackTrace, source));
};

/// \brief Common event arguments.
struct CommonEventArgs {
    /// \brief Structured custom program state payload.
    Opt<TraceEventState> state;

    Str      file;
    Str      function;
    int      line;
    Opt<Str> message;

    DESC_FIELDS(CommonEventArgs, (state, file, function, line, message));
};

/// \brief Object snapshot arguments.
struct ObjectSnapshotArgs {
    /// \brief Structured custom program state payload.
    Opt<TraceEventState> state;
    /// \brief Arbitrary JSON-compatible object snapshot payload.
    UnorderedMap<Str, JsonValue> snapshot;

    DESC_FIELDS(ObjectSnapshotArgs, (state, snapshot));
};

/// \brief process_name metadata args.
struct MetadataProcessNameArgs {
    /// \brief Structured custom program state payload.
    Opt<TraceEventState> state;
    /// \brief Display name.
    Str name;

    DESC_FIELDS(MetadataProcessNameArgs, (state, name));
};

/// \brief process_labels metadata args.
struct MetadataProcessLabelsArgs {
    /// \brief Structured custom program state payload.
    Opt<TraceEventState> state;
    /// \brief Labels string.
    Str labels;

    DESC_FIELDS(MetadataProcessLabelsArgs, (state, labels));
};

/// \brief Sort-index metadata args.
struct MetadataSortIndexArgs {
    /// \brief Structured custom program state payload.
    Opt<TraceEventState> state;
    /// \brief Relative sort order.
    int sort_index;

    DESC_FIELDS(MetadataSortIndexArgs, (state, sort_index));
};

/// \brief thread_name metadata args.
struct MetadataThreadNameArgs {
    /// \brief Structured custom program state payload.
    Opt<TraceEventState> state;
    /// \brief Display name.
    Str name;

    DESC_FIELDS(MetadataThreadNameArgs, (state, name));
};

/// \brief Clock sync arguments.
struct ClockSyncArgs {
    /// \brief Structured custom program state payload.
    Opt<TraceEventState> state;
    /// \brief Sync marker identifier.
    Str sync_id;
    /// \brief Issuer-domain sync timestamp in microseconds.
    Opt<double> issue_ts;

    DESC_FIELDS(ClockSyncArgs, (state, sync_id, issue_ts));
};

/// \brief Identifier-linking arguments.
struct LinkingIdArgs {
    /// \brief Structured custom program state payload.
    Opt<TraceEventState> state;
    /// \brief Linked identifier.
    StrOrInt linked_id;

    DESC_FIELDS(LinkingIdArgs, (state, linked_id));
};

/// \brief Duration stack fields.
struct DurationStackFields {
    /// \brief Stack frame identifier in top-level stackFrames.
    Opt<StrOrInt> sf;
    /// \brief Raw call stack root-to-leaf.
    Opt<Vec<Str>> stack;
    /// \warning Only one of sf or stack may be provided.

    DESC_FIELDS(DurationStackFields, (sf, stack));
};

/// \brief Complete-event stack fields.
struct CompleteStackFields {
    /// \brief Stack frame identifier in top-level stackFrames.
    Opt<StrOrInt> sf;
    /// \brief Raw call stack root-to-leaf.
    Opt<Vec<Str>> stack;
    /// \brief End stack frame identifier.
    Opt<StrOrInt> esf;
    /// \brief Raw end call stack root-to-leaf.
    Opt<Vec<Str>> estack;
    /// \warning Only one of sf or stack may be provided.
    /// \warning Only one of esf or estack may be provided.

    DESC_FIELDS(CompleteStackFields, (sf, stack, esf, estack));
};

/// \brief Explicitly scoped identifier.
struct ExplicitId {
    /// \brief Process-local identifier.
    Opt<StrOrInt> local;
    /// \brief Globally scoped identifier.
    Opt<StrOrInt> global;
    /// \warning Exactly one of local or global must be provided.

    DESC_FIELDS(ExplicitId, (local, global));
};


/// \brief Generic trace event base payload.
struct TraceEventBase {
    /// \brief Event name.
    Opt<Str> name;
    /// \brief Log event categories.
    Vec<Str> cat;
    /// \brief Timestamp in microseconds.
    Opt<double> ts;
    /// \brief Thread timestamp in microseconds.
    Opt<double> tts;
    /// \brief Process identifier.
    Opt<int> pid;
    /// \brief Thread identifier.
    Opt<int> tid;
    /// \brief Trace-viewer color name.
    Opt<Str> cname;
    /// \brief Primary identifier.
    Opt<StrOrInt> id;
    /// \brief Disambiguating scope.
    Opt<Str> scope;
    /// \brief Flow end bind point.
    Opt<Str> bp;
    /// \brief Explicitly scoped identifier.
    Opt<ExplicitId> id2;
    /// \brief Structured args.
    CommonEventArgs args;

    void init_ids();
    void init_location(
        char const* function = __builtin_FUNCTION(),
        int         line     = __builtin_LINE(),
        char const* file     = __builtin_FILE());

    BOOST_DESCRIBE_CLASS(
        TraceEventBase,
        (),
        (name, cat, ts, tts, pid, tid, cname, id, scope, bp, args, id2),
        (),
        ());
};

/// \brief Shared stack payload for stack-capable events.
struct StackTraceEventBase {
    /// \brief Optional stack frame id.
    Opt<StrOrInt> sf;
    /// \brief Optional raw stack.
    Opt<Vec<Str>> stack;

    BOOST_DESCRIBE_CLASS(StackTraceEventBase, (), (sf, stack), (), ());
};

/// \brief Duration begin event.
struct DurationBeginEvent
    : TraceEventBase
    , StackTraceEventBase {
    /// \brief Duration-begin phase.
    static constexpr char ph = 'B';

    BOOST_DESCRIBE_CLASS(
        DurationBeginEvent,
        (TraceEventBase, StackTraceEventBase),
        (args),
        (),
        ());
};

/// \brief Duration end event.
struct DurationEndEvent
    : TraceEventBase
    , StackTraceEventBase {
    /// \brief Duration-end phase.
    static constexpr char ph = 'E';

    BOOST_DESCRIBE_CLASS(
        DurationEndEvent,
        (TraceEventBase, StackTraceEventBase),
        (args),
        (),
        ());
};

/// \brief Complete duration event.
struct CompleteEvent
    : TraceEventBase
    , StackTraceEventBase {
    /// \brief Complete-event phase.
    static constexpr char ph = 'X';
    /// \brief Duration in microseconds.
    double dur;
    /// \brief Optional thread duration in microseconds.
    Opt<double> tdur;
    /// \brief Optional end stack frame id.
    Opt<StrOrInt> esf;
    /// \brief Optional raw end stack.
    Opt<Vec<Str>> estack;

    BOOST_DESCRIBE_CLASS(
        CompleteEvent,
        (TraceEventBase, StackTraceEventBase),
        (dur, tdur, esf, estack),
        (),
        ());
};

/// \brief Instant event.
struct InstantEvent
    : TraceEventBase
    , StackTraceEventBase {
    static constexpr char ph = 'I';
    /// \brief Instant scope.
    /// \warning Allowed values: g, p, t.
    Opt<Str> s;

    BOOST_DESCRIBE_CLASS(
        InstantEvent,
        (TraceEventBase, StackTraceEventBase),
        (ph, s),
        (),
        ());
};

/// \brief Counter event.
struct CounterEvent : TraceEventBase {
    /// \brief Counter phase.
    static constexpr char ph = 'C';
    /// \brief Counter values/payload.
    UnorderedMap<Str, JsonValue> args;

    BOOST_DESCRIBE_CLASS(CounterEvent, (TraceEventBase), (args), (), ());
};

/// \brief Async event.
struct AsyncEventBase : TraceEventBase {
    /// \brief Async identifier.
    StrOrInt id;

    BOOST_DESCRIBE_CLASS(AsyncEventBase, (TraceEventBase), (id), (), ());
};

struct AsyncEventStart : AsyncEventBase {
    static constexpr char ph = 'b';
    BOOST_DESCRIBE_CLASS(AsyncEventStart, (AsyncEventBase), (ph), (), ());
};

struct AsyncEventStep : AsyncEventBase {
    static constexpr char ph = 'n';
    BOOST_DESCRIBE_CLASS(AsyncEventStep, (AsyncEventBase), (ph), (), ());
};

struct AsyncEventEnd : AsyncEventBase {
    static constexpr char ph = 'e';
    BOOST_DESCRIBE_CLASS(AsyncEventEnd, (AsyncEventBase), (ph), (), ());
};

/// \brief Flow event.
struct FlowEventBase : TraceEventBase {
    /// \brief Flow identifier.
    StrOrInt id;

    BOOST_DESCRIBE_CLASS(FlowEventBase, (TraceEventBase), (id), (), ());
};

struct FlowEventStart : FlowEventBase {
    static constexpr char ph = 's';
    BOOST_DESCRIBE_CLASS(FlowEventStart, (FlowEventBase), (ph), (), ());
};

struct FlowEventStep : FlowEventBase {
    static constexpr char ph = 't';
    BOOST_DESCRIBE_CLASS(FlowEventStep, (FlowEventBase), (ph), (), ());
};

struct FlowEventEnd : FlowEventBase {
    static constexpr char ph = 'f';
    BOOST_DESCRIBE_CLASS(FlowEventEnd, (FlowEventBase), (ph), (), ());
};


/// \brief Sample event.
struct SampleEvent
    : TraceEventBase
    , StackTraceEventBase {
    /// \brief Sample phase.
    static constexpr char ph = 'P';

    BOOST_DESCRIBE_CLASS(
        SampleEvent,
        (TraceEventBase, StackTraceEventBase),
        (args),
        (),
        ());
};

/// \brief Object created event.
struct ObjectCreatedEvent : TraceEventBase {
    /// \brief Object-created phase.
    static constexpr char ph = 'N';
    /// \brief Object identifier.
    StrOrInt id;
    /// \brief Lifecycle args, typically null.
    Opt<json> args;

    BOOST_DESCRIBE_CLASS(
        ObjectCreatedEvent,
        (TraceEventBase),
        (id),
        (),
        ());
};

/// \brief Object snapshot event.
struct ObjectSnapshotEvent : TraceEventBase {
    /// \brief Object-snapshot phase.
    static constexpr char ph = 'O';
    /// \brief Object identifier.
    StrOrInt id;
    /// \brief Snapshot args.
    ObjectSnapshotArgs args;

    BOOST_DESCRIBE_CLASS(
        ObjectSnapshotEvent,
        (TraceEventBase),
        (id),
        (),
        ());
};

/// \brief Object destroyed event.
struct ObjectDestroyedEvent : TraceEventBase {
    /// \brief Object-destroyed phase.
    static constexpr char ph = 'D';
    /// \brief Object identifier.
    StrOrInt id;
    /// \brief Lifecycle args, typically null.
    Opt<json> args;

    BOOST_DESCRIBE_CLASS(
        ObjectDestroyedEvent,
        (TraceEventBase),
        (id),
        (),
        ());
};

/// \brief process_name metadata event.
struct MetadataProcessNameEvent : TraceEventBase {
    /// \brief Metadata phase.
    static constexpr char ph = 'M';
    /// \brief Metadata event name.
    /// \warning Must be process_name.
    Str name;
    /// \brief Referenced process id.
    int pid;
    /// \brief Typed metadata args.
    MetadataProcessNameArgs args;

    BOOST_DESCRIBE_CLASS(
        MetadataProcessNameEvent,
        (TraceEventBase),
        (name, pid),
        (),
        ());
};

/// \brief process_labels metadata event.
struct MetadataProcessLabelsEvent : TraceEventBase {
    /// \brief Metadata phase.
    static constexpr char ph = 'M';
    /// \brief Metadata event name.
    /// \warning Must be process_labels.
    Str name;
    /// \brief Referenced process id.
    int pid;
    /// \brief Typed metadata args.
    MetadataProcessLabelsArgs args;

    BOOST_DESCRIBE_CLASS(
        MetadataProcessLabelsEvent,
        (TraceEventBase),
        (name, pid),
        (),
        ());
};

/// \brief process_sort_index metadata event.
struct MetadataProcessSortIndexEvent : TraceEventBase {
    /// \brief Metadata phase.
    static constexpr char ph = 'M';
    /// \brief Metadata event name.
    /// \warning Must be process_sort_index.
    Str name;
    /// \brief Referenced process id.
    int pid;
    /// \brief Typed metadata args.
    MetadataSortIndexArgs args;

    BOOST_DESCRIBE_CLASS(
        MetadataProcessSortIndexEvent,
        (TraceEventBase),
        (name, pid),
        (),
        ());
};

/// \brief thread_name metadata event.
struct MetadataThreadNameEvent : TraceEventBase {
    /// \brief Metadata phase.
    static constexpr char ph = 'M';
    /// \brief Metadata event name.
    /// \warning Must be thread_name.
    Str name;
    /// \brief Referenced process id.
    int pid;
    /// \brief Referenced thread id.
    int tid;
    /// \brief Typed metadata args.
    MetadataThreadNameArgs args;

    BOOST_DESCRIBE_CLASS(
        MetadataThreadNameEvent,
        (TraceEventBase),
        (name, pid, tid),
        (),
        ());
};

/// \brief thread_sort_index metadata event.
struct MetadataThreadSortIndexEvent : TraceEventBase {
    /// \brief Metadata phase.
    static constexpr char ph = 'M';
    /// \brief Metadata event name.
    /// \warning Must be thread_sort_index.
    Str name;
    /// \brief Referenced process id.
    int pid;
    /// \brief Referenced thread id.
    int tid;
    /// \brief Typed metadata args.
    MetadataSortIndexArgs args;

    BOOST_DESCRIBE_CLASS(
        MetadataThreadSortIndexEvent,
        (TraceEventBase),
        (name, pid, tid),
        (),
        ());
};

/// \brief Generic metadata event.
struct GenericMetadataEvent : TraceEventBase {
    /// \brief Metadata phase.
    static constexpr char ph = 'M';
    /// \brief Metadata event name.
    Str name;
    /// \brief Generic metadata args.
    Opt<UnorderedMap<Str, JsonValue>> args;

    BOOST_DESCRIBE_CLASS(
        GenericMetadataEvent,
        (TraceEventBase),
        (name),
        (),
        ());
};

/// \brief Global memory dump event.
struct GlobalMemoryDumpEvent : TraceEventBase {
    /// \brief Global-memory-dump phase.
    static constexpr char ph = 'V';
    /// \brief Dump identifier.
    StrOrInt id;
    /// \brief Dump payload.
    UnorderedMap<Str, JsonValue> args;

    BOOST_DESCRIBE_CLASS(
        GlobalMemoryDumpEvent,
        (TraceEventBase),
        (id),
        (),
        ());
};

/// \brief Process memory dump event.
struct ProcessMemoryDumpEvent : TraceEventBase {
    /// \brief Process-memory-dump phase.
    static constexpr char ph = 'v';
    /// \brief Process id.
    int pid;
    /// \brief Dump identifier.
    StrOrInt id;
    /// \brief Dump payload.
    UnorderedMap<Str, JsonValue> args;

    BOOST_DESCRIBE_CLASS(
        ProcessMemoryDumpEvent,
        (TraceEventBase),
        (pid, id),
        (),
        ());
};

/// \brief Mark event.
struct MarkEvent : TraceEventBase {
    /// \brief Mark phase.
    static constexpr char ph = 'R';

    BOOST_DESCRIBE_CLASS(MarkEvent, (TraceEventBase), (args), (), ());
};

/// \brief Clock synchronization event.
struct ClockSyncEvent : TraceEventBase {
    /// \brief Clock-sync phase.
    static constexpr char ph = 'c';
    /// \brief Event name.
    /// \warning Must be clock_sync.
    Str name;
    /// \brief Clock sync args.
    ClockSyncArgs args;

    BOOST_DESCRIBE_CLASS(ClockSyncEvent, (TraceEventBase), (name), (), ());
};

/// \brief Context-enter event.
struct ContextEnterEvent : TraceEventBase {
    /// \brief Context-enter phase.
    static constexpr char ph = '(';
    /// \brief Context identifier.
    StrOrInt id;

    BOOST_DESCRIBE_CLASS(
        ContextEnterEvent,
        (TraceEventBase),
        (id),
        (),
        ());
};

/// \brief Context-leave event.
struct ContextLeaveEvent : TraceEventBase {
    /// \brief Context-leave phase.
    static constexpr char ph = ')';
    /// \brief Context identifier.
    StrOrInt id;

    BOOST_DESCRIBE_CLASS(
        ContextLeaveEvent,
        (TraceEventBase),
        (id),
        (),
        ());
};

/// \brief Identifier-linking event.
struct LinkingIdEvent : TraceEventBase {
    /// \brief Identifier-linking phase.
    static constexpr char ph = '=';
    /// \brief Primary identifier.
    StrOrInt id;
    /// \brief Linking args.
    LinkingIdArgs args;

    BOOST_DESCRIBE_CLASS(LinkingIdEvent, (TraceEventBase), (id), (), ());
};

#define ALL_TRACE_EVENT_TYPES(__IMPL)                                     \
    __IMPL(DurationBeginEvent)                                            \
    __IMPL(DurationEndEvent)                                              \
    __IMPL(CompleteEvent)                                                 \
    __IMPL(InstantEvent)                                                  \
    __IMPL(CounterEvent)                                                  \
    __IMPL(AsyncEventStart)                                               \
    __IMPL(AsyncEventStep)                                                \
    __IMPL(AsyncEventEnd)                                                 \
    __IMPL(FlowEventStart)                                                \
    __IMPL(FlowEventStep)                                                 \
    __IMPL(FlowEventEnd)                                                  \
    __IMPL(SampleEvent)                                                   \
    __IMPL(ObjectCreatedEvent)                                            \
    __IMPL(ObjectSnapshotEvent)                                           \
    __IMPL(ObjectDestroyedEvent)                                          \
    __IMPL(MetadataProcessNameEvent)                                      \
    __IMPL(MetadataProcessLabelsEvent)                                    \
    __IMPL(MetadataProcessSortIndexEvent)                                 \
    __IMPL(MetadataThreadNameEvent)                                       \
    __IMPL(MetadataThreadSortIndexEvent)                                  \
    __IMPL(GenericMetadataEvent)                                          \
    __IMPL(GlobalMemoryDumpEvent)                                         \
    __IMPL(ProcessMemoryDumpEvent)                                        \
    __IMPL(MarkEvent)                                                     \
    __IMPL(ClockSyncEvent)                                                \
    __IMPL(ContextEnterEvent)                                             \
    __IMPL(ContextLeaveEvent)                                             \
    __IMPL(LinkingIdEvent)

#define COMMA
#define SKIP_FIRST_ARG_AUX(op, ...) __VA_ARGS__
#define SKIP_FIRST_ARG(op, ...) SKIP_FIRST_ARG_AUX(op)

#define ALL_TRACE_EVENT_TYPES_CSV(__CMD)                                  \
    SKIP_FIRST_ARG(ALL_TRACE_EVENT_TYPES(__CMD))

#define __id(A) , A

/// \brief Union of all trace event variants.
using TraceEvent = Variant<ALL_TRACE_EVENT_TYPES_CSV(__id)>;

#undef __id


/// \brief Top-level stack frame definition.
struct TraceStackFrame {
    /// \brief Frame category/module.
    Str category;
    /// \brief Frame/function name.
    Str name;
    /// \brief Parent frame identifier.
    Opt<StrOrInt> parent;

    DESC_FIELDS(TraceStackFrame, (category, name, parent));
};

/// \brief Global sampling record.
struct GlobalSample {
    /// \brief CPU index.
    Opt<int> cpu;
    /// \brief Thread identifier.
    int tid;
    /// \brief Sample timestamp in microseconds.
    double ts;
    /// \brief Sample source/counter name.
    Str name;
    /// \brief Root stack frame identifier.
    StrOrInt sf;
    /// \brief Sample weight/value.
    double weight;

    DESC_FIELDS(GlobalSample, (cpu, tid, ts, name, sf, weight));
};

/// \brief Top-level trace log.
struct TraceLog {
    /// \brief Trace event sequence.
    Vec<TraceEvent> traceEvents;
    /// \brief Preferred display time unit.
    /// \warning Allowed values: ms, ns.
    Opt<Str> displayTimeUnit;
    /// \brief Embedded system trace payload.
    Opt<Str> systemTraceEvents;
    /// \brief Embedded power trace payload.
    Opt<Str> powerTraceAsString;
    /// \brief Stack frame dictionary.
    Opt<UnorderedMap<StrOrInt, TraceStackFrame>> stackFrames;
    /// \brief Global sampling records.
    Opt<Vec<GlobalSample>> samples;
    /// \brief Controller-origin trace payload key.
    Opt<Str> controllerTraceDataKey;

    DESC_FIELDS(
        TraceLog,
        (traceEvents,
         displayTimeUnit,
         systemTraceEvents,
         powerTraceAsString,
         stackFrames,
         samples,
         controllerTraceDataKey));
};


template <typename T>
json format_event_to_json(T const& value);

template <typename T>
T load_event_from_json(json const& event);

TraceEvent load_event_variant_from_json(json const& event);

} // namespace hstd::log::record
