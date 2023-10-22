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
};
