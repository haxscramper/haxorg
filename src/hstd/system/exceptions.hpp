#pragma once

#include <stdexcept>
#include <QString>

inline void assert_has_idx(int size, int wanted, std::string failure) {
    if (!(wanted < size)) {
        throw std::range_error(failure);
    }
}

struct GetterError : public std::runtime_error {
    explicit inline GetterError(const QString& message)
        : std::runtime_error(message.toStdString()) {}
};

struct KeyError : public std::runtime_error {
    explicit KeyError(const QString& message)
        : std::runtime_error(message.toStdString()) {}
};


struct LogicError : public std::logic_error {
    explicit inline LogicError(const QString& message)
        : std::logic_error(message.toStdString()) {}
};

struct UnexpectedKindError : public LogicError {
    explicit inline UnexpectedKindError(const QString& message)
        : LogicError(message) {}
};

struct RangeError : public std::range_error {
    explicit RangeError(const QString& message)
        : std::range_error(message.toStdString()) {}
};


struct OutOfRangeError : public std::out_of_range {
    explicit OutOfRangeError(const QString& message)
        : std::out_of_range(message.toStdString()) {}
};
