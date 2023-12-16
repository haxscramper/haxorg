module;

#include <stdexcept>
#include <string>

export module hstd.system.exceptions;

export {
inline void assert_has_idx(int size, int wanted, std::string failure) {
    if (!(wanted < size)) {
        throw std::range_error(failure);
    }
}

struct GetterError : public std::runtime_error {
    explicit inline GetterError(const std::string& message)
        : std::runtime_error(message) {}
};

struct KeyError : public std::runtime_error {
    explicit KeyError(const std::string& message)
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

struct RangeError : public std::range_error {
    explicit RangeError(const std::string& message)
        : std::range_error(message) {}
};


struct OutOfRangeError : public std::out_of_range {
    explicit OutOfRangeError(const std::string& message)
        : std::out_of_range(message) {}
};
}