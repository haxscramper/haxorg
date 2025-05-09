#include "Time.hpp"
#include <absl/hash/hash.h>

using namespace hstd;

UserTimeBreakdown UserTime::getBreakdown() const {
    UserTimeBreakdown result;
    absl::CivilSecond sec = absl::TimeZone{}.At(time).cs;

    switch (align) {
        case Alignment::Second: {
            result.second = sec.second();
            [[fallthrough]];
        }
        case Alignment::Minute: {
            result.minute = sec.minute();
            [[fallthrough]];
        }
        case Alignment::Hour: {
            result.hour = sec.hour();
            [[fallthrough]];
        }
        case Alignment::Day: {
            result.day = sec.day();
            [[fallthrough]];
        }
        case Alignment::Month: {
            result.month = sec.month();
            [[fallthrough]];
        }
        case Alignment::Year: result.year = sec.year();
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

    if (kind == Format::OrgFormat) {
        if (zone) {
            int offset  = zone->At(absl::UnixEpoch()).offset / 60;
            int hours   = offset / 60;
            int minutes = offset % 60;

            if (minutes == 0) {
                format += fmt(" {:+03}", hours);
            } else {
                format += fmt(" {:+05}", offset);
            }
        }
    } else {
        if (zone) { format += " %z"; }
    }

    std::string result = zone ? absl::FormatTime(format, time, *zone)
                              : absl::FormatTime(
                                    format, time, absl::TimeZone{});

    return result;
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
            result, absl::Hash<absl::TimeZone>{}(*it.zone));
    }
    hstd::hax_hash_combine(result, absl::Hash<absl::Time>{}(it.time));
    return result;
}
