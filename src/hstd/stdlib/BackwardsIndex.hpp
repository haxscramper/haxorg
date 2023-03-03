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

inline QTextStream& operator<<(
    QTextStream&          os,
    BackwardsIndex const& value) {
    return os << "^" << QString::number(value.value);
}
