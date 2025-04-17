#pragma once
#include <format>

namespace hstd {
struct BackwardsIndex {
    int value;

    bool operator==(BackwardsIndex const& i) const {
        return value == i.value;
    }

    bool operator!=(BackwardsIndex const& i) const {
        return value != i.value;
    }

    bool operator<(BackwardsIndex const& i) const {
        return i.value < value;
    }

    bool operator<=(BackwardsIndex const& i) const {
        return i.value <= value;
    }

    bool operator>(BackwardsIndex const& i) const {
        return i.value > value;
    }

    bool operator>=(BackwardsIndex const& i) const {
        return i.value >= value;
    }
};

inline BackwardsIndex backIndex(int value) {
    return BackwardsIndex{.value = value};
}


} // namespace hstd

template <>
struct std::formatter<hstd::BackwardsIndex> : std::formatter<std::string> {
    using FmtType = hstd::BackwardsIndex;
    template <typename FormatContext>
    FormatContext::iterator format(FmtType const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        return fmt.format("^" + std::to_string(p.value), ctx);
    }
};

inline hstd::BackwardsIndex operator""_B(unsigned long long int value) {
    return hstd::backIndex(value);
}
