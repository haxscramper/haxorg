#pragma once
#include <fmt/base.h>
#pragma clang diagnostic ignored "-Wunknown-attributes"

namespace hstd {
struct [[refl]] BackwardsIndex {
    [[refl]] int value;

    bool operator==(BackwardsIndex const& i) const { return value == i.value; }

    bool operator!=(BackwardsIndex const& i) const { return value != i.value; }

    bool operator<(BackwardsIndex const& i) const { return i.value < value; }

    bool operator<=(BackwardsIndex const& i) const { return i.value <= value; }

    bool operator>(BackwardsIndex const& i) const { return i.value > value; }

    bool operator>=(BackwardsIndex const& i) const { return value <= i.value; }
};

inline BackwardsIndex backIndex(int value) { return BackwardsIndex{.value = value}; }


} // namespace hstd

template <>
struct fmt::formatter<hstd::BackwardsIndex> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }

    using FmtType = hstd::BackwardsIndex;
    fmt::format_context::iterator format(FmtType const& p, fmt::format_context& ctx)
        const {
        fmt::format_to(ctx.out(), "^");
        return fmt::format_to(ctx.out(), "{}", p.value);
    }
};

inline hstd::BackwardsIndex operator""_B(unsigned long long int value) {
    return hstd::backIndex(value);
}
