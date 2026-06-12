#include "TraceBaseStructuredLog.hpp"

#include <chrono>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/VariantSerde.hpp>
#include <hstd/stdlib/MapSerde.hpp>
#include <hstd/stdlib/OptSerde.hpp>
#include <hstd/stdlib/Pair.hpp>

void hstd::log::record::TraceEventBase::init_ids() {
    if (!pid) { pid = static_cast<int>(::getpid()); }

    if (!tid) {
#ifdef SYS_gettid
        tid = static_cast<int>(::syscall(SYS_gettid));
#else
        tid = pid;
#endif
    }

    if (!ts || !tts) {
        using namespace std::chrono;
        auto now = steady_clock::now().time_since_epoch();
        auto us  = duration_cast<microseconds>(now).count();

        if (!ts) { ts = static_cast<double>(us); }
        if (!tts) { tts = static_cast<double>(us); }
    }
}

void hstd::log::record::TraceEventBase::init_location(
    char const* function,
    int         line,
    char const* file) {
    if (file) { args.file = file; }
    if (line != -1) { args.line = line; }
    if (function) { args.function = function; }
}


template <typename T>
json hstd::log::record::format_event_to_json(T const& value) {
    json resul  = hstd::JsonSerdeDescribedRecordBaseEx<T>::to_json(value);
    resul["ph"] = hstd::fmt1(value.ph);
    return resul;
}

template <typename T>
T hstd::log::record::load_event_from_json(json const& event) {
    return hstd::JsonSerde<T>::from_json(event);
}

namespace {

template <typename Variant, std::size_t... Is>
Variant event_from_json_impl(json const& j, std::index_sequence<Is...>) {
    const char ph = j.at("ph").get<std::string>().at(0);

    Variant result;
    bool    matched = false;

    (
        [&] {
            using T = std::variant_alternative_t<Is, Variant>;
            if (!matched && T::ph == ph) {
                result  = Variant{hstd::log::record::load_event_from_json<T>(j)};
                matched = true;
            }
        }(),
        ...);

    if (!matched) { throw std::runtime_error("unknown event ph"); }

    return result;
}

template <typename Variant>
Variant event_from_json(json const& j) {
    return event_from_json_impl<Variant>(
        j, std::make_index_sequence<std::variant_size_v<Variant>>{});
}
} // namespace

hstd::log::record::TraceEvent hstd::log::record::load_event_variant_from_json(
    json const& event) {
    return event_from_json<TraceEvent>(event);
}


#define __define(_T)                                                                     \
    template json hstd::log::record::format_event_to_json<hstd::log::record::_T>(        \
        hstd::log::record::_T const&);

ALL_TRACE_EVENT_TYPES(__define)
