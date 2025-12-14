#pragma once

#include <cctz/civil_time.h>
#include <cctz/time_zone.h>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/system/aux_utils.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Opt.hpp>


#pragma clang diagnostic ignored "-Wunknown-attributes"

namespace hstd {

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

    bool operator==(UserTimeBreakdown const& other) const {
        return year == other.year     //
            && month == other.month   //
            && day == other.day       //
            && hour == other.hour     //
            && second == other.second //
            && zone == other.zone;
    }
};

struct [[refl]] UserTime {
    DECL_DESCRIBED_ENUM(Alignment, Year, Month, Day, Hour, Minute, Second);
    DECL_DESCRIBED_ENUM(Format, ISO8601, OrgFormat);

    cctz::civil_second   time;
    Opt<cctz::time_zone> zone;
    Alignment            align;
    BOOST_DESCRIBE_CLASS(UserTime, (), (time, zone, align), (), ());

    [[refl]] UserTimeBreakdown getBreakdown() const;
    [[refl]] std::string       format() const;
    std::string                format(Format kind) const;

    bool operator==(UserTime const& it) const;

    [[refl]] int64_t getTimeDeltaSeconds(UserTime const& other) const;
    [[refl]] int64_t toUnixTimestamp() const;
};

} // namespace hstd

template <>
struct std::hash<hstd::UserTime> {
    std::size_t operator()(hstd::UserTime const& it) const noexcept;
};


template <>
struct std::formatter<cctz::civil_second> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        const cctz::civil_second& p,
        FormatContext&            ctx) const;
};

template <>
struct std::formatter<cctz::time_zone> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        const cctz::time_zone& p,
        FormatContext&         ctx) const;
};
