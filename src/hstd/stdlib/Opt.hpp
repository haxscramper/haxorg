#pragma once

#include <optional>
#include <QTextStream>

template <typename T>
using Opt = std::optional<T>;

template <typename T>
QTextStream& operator<<(QTextStream& os, Opt<T> const& value) {
    if (value.has_value()) {
        return os << "some(" << value.value() << ")";
    } else {
        return os << "none()";
    }
}
