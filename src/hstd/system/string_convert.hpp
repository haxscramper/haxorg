#pragma once

#include <iostream>
#include <string>
#include <sstream>

template <typename T>
concept StringStreamable = requires(T value, std::ostream& os) {
    { os << value } -> std::same_as<std::ostream&>;
};

template <typename T>
std::string to_string(CR<T> value) requires StringStreamable<T> {
    std::stringstream os;
    os << value;
    return os.str();
}

template <typename T>
concept StringConvertible = requires(T value) {
    { to_string(value) } -> std::same_as<std::string>;
};
