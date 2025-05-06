#include "Time.hpp"

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
