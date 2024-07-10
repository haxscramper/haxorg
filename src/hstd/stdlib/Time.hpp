#pragma once

#include <absl/time/clock.h>
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
    DECL_DESCRIBED_ENUM(Format, ISO8601, OrgFormat);

    absl::Time          time;
    Opt<absl::TimeZone> zone;
    Alignment           align;
    BOOST_DESCRIBE_CLASS(UserTime, (), (time, zone, align), (), ());

    [[refl]] UserTimeBreakdown getBreakdown() const;
    [[refl]] std::string       format() const;
    std::string                format(Format kind) const;
};


template <>
struct std::formatter<absl::Time> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const absl::Time& p, FormatContext& ctx) const {
        return fmt_ctx(
            absl::FormatTime("%Y-%m-%d %H:%M:%S", p, absl::TimeZone{}),
            ctx);
    }
};

template <>
struct std::formatter<absl::TimeZone> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const absl::TimeZone& p, FormatContext& ctx) const {
        return fmt_ctx(absl::FormatTime("%z", absl::Now(), p), ctx);
    }
};
