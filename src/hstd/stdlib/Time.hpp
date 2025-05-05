#pragma once

#include <cctz/civil_time.h>
#include <cctz/time_zone.h>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/system/aux_utils.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/reflection_visitor.hpp>

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
};


template <typename Tag>
struct ReflVisitor<cctz::civil_second, Tag>
    : ReflVisitorLeafType<cctz::civil_second, Tag> {};

template <typename Tag>
struct ReflVisitor<cctz::time_zone, Tag>
    : ReflVisitorLeafType<cctz::time_zone, Tag> {};

} // namespace hstd

template <>
struct std::hash<hstd::UserTime> {
    std::size_t operator()(hstd::UserTime const& it) const noexcept;
};


template <>
struct std::formatter<cctz::civil_second> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const cctz::civil_second& p, FormatContext& ctx) const {
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
};

template <>
struct std::formatter<cctz::time_zone> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const cctz::time_zone& p, FormatContext& ctx) const {
        // Format the time zone by its name
        std::string formatted = p.name();

        // Alternatively, you could include the current offset information
        // Get current time
        auto now = std::chrono::system_clock::now();
        auto tp  = cctz::convert(
            std::chrono::time_point_cast<std::chrono::seconds>(now),
            cctz::utc_time_zone());


        // Get time zone info
        auto info = p.lookup(tp);

        // Calculate offset in hours and minutes
        int total_minutes = info.trans.time_since_epoch().count() / 60;
        int hours         = total_minutes / 60;
        int minutes       = std::abs(total_minutes % 60);

        // Format with name and offset
        formatted = std::format(
            "{} (UTC{:+03d}:{:02d})", p.name(), hours, minutes);

        return std::formatter<std::string>::format(formatted, ctx);
    }
};
