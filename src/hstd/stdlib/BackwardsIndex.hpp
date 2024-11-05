#pragma once
#include <format>

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

inline BackwardsIndex operator"" _B(unsigned long long int value) {
    return backIndex(value);
}


template <>
struct std::formatter<BackwardsIndex> : std::formatter<std::string> {
    using FmtType = BackwardsIndex;
    template <typename FormatContext>
    FormatContext::iterator format(FmtType const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        return fmt.format("^" + std::to_string(p.value), ctx);
    }
};
