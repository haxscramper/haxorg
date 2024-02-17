#pragma once

#include <hstd/stdlib/Variant.hpp>
#include <hstd/system/aux_utils.hpp>
#include <absl/time/civil_time.h>
#include <absl/time/time.h>
#include <hstd/stdlib/Str.hpp>

struct UserTime {
    DECL_DESCRIBED_ENUM(Alignment, Year, Month, Day, Hour, Minute, Second);
    Str toString() const { return absl::FormatTime(time, zone); }

    absl::Time     time;
    absl::TimeZone zone;
    Alignment      align;
    BOOST_DESCRIBE_CLASS(UserTime, (), (time, zone, align), (), ());

    std::string format() const {
        std::string format;
        switch (align) {
            case Alignment::Year: format = "%Y"; break;
            case Alignment::Month: format = "%Y-%m"; break;
            case Alignment::Day: format = "%Y-%m-%d"; break;
            case Alignment::Hour: format = "%Y-%m-%d %H"; break;
            case Alignment::Minute: format = "%Y-%m-%d %H:%M"; break;
            case Alignment::Second: format = "%Y-%m-%d %H:%M:%S"; break;
        }
        format += " %z";

        return absl::FormatTime(format, time, zone);
    }
};
