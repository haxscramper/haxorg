#pragma once

#include <optional>
#include <iostream>

template <typename T>
using Opt = std::optional<T>;

template <typename T>
std::ostream& operator<<(std::ostream& os, Opt<T> const& value) {
    if (value.has_value()) {
        return os << "some(" << value.value() << ")";
    } else {
        return os << "none()";
    }
}
