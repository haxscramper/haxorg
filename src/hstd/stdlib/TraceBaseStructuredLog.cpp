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

#define __define(_T)                                                      \
    template json                                                         \
        hstd::log::record::format_event_to_json<hstd::log::record::_T>(   \
            hstd::log::record::_T const&);

ALL_TRACE_EVENT_TYPES(__define)
