#pragma once
#include <format>

struct BackwardsIndex {
    int value;
};

inline BackwardsIndex backIndex(int value) {
    return BackwardsIndex{.value = value};
}

inline BackwardsIndex operator"" _B(unsigned long long int value) {
    return backIndex(value);
}


template <>
struct std::formatter<BackwardsIndex> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const BackwardsIndex& p, FormatContext& ctx) {
        return std::formatter<std::string>::format(
            "^" + std::to_string(p.value), ctx);
    }
};
