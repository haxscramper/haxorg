#pragma once

#include <hstd/stdlib/Variant.hpp>
#include <hstd/system/aux_utils.hpp>
#include <absl/time/civil_time.h>
#include <absl/time/time.h>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Opt.hpp>

struct [[refl]] UserTimeBreakdown {
    [[refl]] Opt<int>         year;
    [[refl]] Opt<int>         month;
    [[refl]] Opt<int>         day;
    [[refl]] Opt<int>         hour;
    [[refl]] Opt<int>         minute;
    [[refl]] Opt<int>         second;
    [[refl]] Opt<std::string> zone;

    BOOST_DESCRIBE_CLASS(
        UserTimeBreakdown,
        (),
        (year, month, day, hour, minute, second, zone),
        (),
        ());
};

struct [[refl]] UserTime {
    DECL_DESCRIBED_ENUM(Alignment, Year, Month, Day, Hour, Minute, Second);

    absl::Time          time;
    Opt<absl::TimeZone> zone;
    Alignment           align;
    BOOST_DESCRIBE_CLASS(UserTime, (), (time, zone, align), (), ());

    [[refl]] UserTimeBreakdown getBreakdown() const;
    [[refl]] std::string       format() const;
};
