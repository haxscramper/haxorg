#pragma once

struct BackwardsIndex {
    int value;
};

inline BackwardsIndex backIndex(int value) {
    return BackwardsIndex{.value = value};
}

inline BackwardsIndex operator"" _B(unsigned long long int value) {
    return backIndex(value);
}
