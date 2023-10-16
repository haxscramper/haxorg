#pragma once

#include <hstd/system/string_convert.hpp>

struct BackwardsIndex {
    int value;
};

inline BackwardsIndex backIndex(int value) {
    return BackwardsIndex{.value = value};
}

inline BackwardsIndex operator"" _B(unsigned long long int value) {
    return backIndex(value);
}

inline std::ostream& operator<<(
    std::ostream&          os,
    BackwardsIndex const& value) {
    return os << "^" << std::string::number(value.value);
}
