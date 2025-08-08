#include "Time.hpp"
#include <hstd/stdlib/Debug.hpp>

using namespace hstd;

UserTimeBreakdown UserTime::getBreakdown() const {
    UserTimeBreakdown result;
    cctz::time_zone   tz = zone ? *zone : cctz::utc_time_zone();

    switch (align) {
        case Alignment::Second: {
            result.second = time.second();
            [[fallthrough]];
        }
        case Alignment::Minute: {
            result.minute = time.minute();
            [[fallthrough]];
        }
        case Alignment::Hour: {
            result.hour = time.hour();
            [[fallthrough]];
        }
        case Alignment::Day: {
            result.day = time.day();
            [[fallthrough]];
        }
        case Alignment::Month: {
            result.month = time.month();
            [[fallthrough]];
        }
        case Alignment::Year: result.year = time.year();
    }

    if (zone) { result.zone = zone->name(); }

    return result;
}

std::string UserTime::format() const { return format(Format::ISO8601); }

std::string UserTime::format(Format kind) const {
    std::string format;
    switch (align) {
        case Alignment::Year: format = "%Y"; break;
        case Alignment::Month: format = "%Y-%m"; break;
        default: format = "%Y-%m-%d"; break;
    }

    // if (kind == Format::OrgFormat) { format += " %a"; }

    switch (align) {
        case Alignment::Hour: format += " %H"; break;
        case Alignment::Minute: format += " %H:%M"; break;
        case Alignment::Second: format += " %H:%M:%S"; break;
        default:
    }

    cctz::time_zone tz = zone ? *zone : cctz::utc_time_zone();

    if (kind == Format::OrgFormat) {
        if (zone) {
            auto info    = tz.lookup(cctz::convert(
                cctz::civil_second(1970, 1, 1, 0, 0, 0),
                cctz::utc_time_zone()));
            int  offset  = info.offset / 60;
            int  hours   = offset / 60;
            int  minutes = offset % 60;

            if (minutes == 0) {
                format += fmt(" {:+03}", hours);
            } else {
                format += fmt(" {:+05}", offset);
            }
        }
    } else {
        if (zone) { format += " %z"; }
    }

    return cctz::format(format, cctz::convert(time, tz), tz);
}

bool UserTime::operator==(const UserTime& it) const {
    bool result = true;
    result &= this->time == it.time;
    result &= this->zone == it.zone;
    result &= this->align == it.align;
    return result;
}

int64_t UserTime::getTimeDeltaSeconds(const UserTime& other) const {
    auto this_zone  = zone.value_or(cctz::utc_time_zone());
    auto other_zone = other.zone.value_or(cctz::utc_time_zone());

    auto this_absolute  = cctz::convert(time, this_zone);
    auto other_absolute = cctz::convert(other.time, other_zone);

    return std::chrono::duration_cast<std::chrono::seconds>(
               this_absolute - other_absolute)
        .count();
}

int64_t UserTime::toUnixTimestamp() const {
    auto time_zone     = zone.value_or(cctz::utc_time_zone());
    auto absolute_time = cctz::convert(time, time_zone);

    auto unix_epoch           = std::chrono::system_clock::from_time_t(0);
    auto duration_since_epoch = absolute_time - unix_epoch;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(
                       duration_since_epoch)
                       .count();

    constexpr int64_t unix_min = -2147483648LL;
    constexpr int64_t unix_max = 2147483647LL;

    if (seconds < unix_min || unix_max < seconds) {
        throw std::out_of_range(std::format(
            "Time {} is outside unix timestamp range", seconds));
    }

    return seconds;
}

std::size_t std::hash<UserTime>::operator()(
    const UserTime& it) const noexcept {
    std::size_t result = 0;
    hstd::hax_hash_combine(result, it.align);
    if (it.zone) {
        hstd::hax_hash_combine(
            result, std::hash<std::string>{}(it.zone->name()));
    }
    hstd::hax_hash_combine(result, it.time.year());
    hstd::hax_hash_combine(result, it.time.month());
    hstd::hax_hash_combine(result, it.time.day());
    hstd::hax_hash_combine(result, it.time.hour());
    hstd::hax_hash_combine(result, it.time.minute());
    hstd::hax_hash_combine(result, it.time.second());
    return result;
}

template <typename FormatContext>
FormatContext::iterator std::formatter<cctz::time_zone>::format(
    const cctz::time_zone& p,
    FormatContext&         ctx) const {
    return fmt_ctx(p.name(), ctx);
}

template <typename FormatContext>
FormatContext::iterator std::formatter<cctz::civil_second>::format(
    const cctz::civil_second& p,
    FormatContext&            ctx) const {
    return hstd::fmt_ctx(
        std::format(
            "{:04}-{:02}-{:02} {:02}:{:02}:{:02}",
            p.year(),
            p.month(),
            p.day(),
            p.hour(),
            p.minute(),
            p.second()),
        ctx);
}

template std::format_context::iterator std::formatter<cctz::civil_second>::
    format(const cctz::civil_second&, std::format_context&) const;

template std::format_context::iterator std::formatter<
    cctz::time_zone,
    char>::format(const cctz::time_zone&, std::format_context&) const;
