#pragma once

#include <stdexcept>
#include <string>

inline void assert_has_idx(int size, int wanted, std::string failure) {
    if (!(wanted < size)) {
        throw std::range_error(failure);
    }
}

struct GetterError : public std::runtime_error {
    explicit inline GetterError(const std::string& message)
        : std::runtime_error(message) {}
};

struct LogicError : public std::logic_error {
    explicit inline LogicError(const std::string& message)
        : std::logic_error(message) {}
};

struct UnexpectedKindError : public LogicError {
    explicit inline UnexpectedKindError(const std::string& message)
        : LogicError(message) {}
};
