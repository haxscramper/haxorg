#include "Time.hpp"

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
std::string UserTime::format() const {
    std::string format;
    switch (align) {
        case Alignment::Year: format = "%Y"; break;
        case Alignment::Month: format = "%Y-%m"; break;
        case Alignment::Day: format = "%Y-%m-%d"; break;
        case Alignment::Hour: format = "%Y-%m-%d %H"; break;
        case Alignment::Minute: format = "%Y-%m-%d %H:%M"; break;
        case Alignment::Second: format = "%Y-%m-%d %H:%M:%S"; break;
    }

    if (zone) { format += " %z"; }

    std::string result = zone ? absl::FormatTime(format, time, *zone)
                              : absl::FormatTime(
                                    format, time, absl::TimeZone{});

    return result;
}
