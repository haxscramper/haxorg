#pragma once

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <hstd/system/aux_utils.hpp>
#include <format>
#include <cpptrace.hpp>
#include <sstream>

template <typename Derived>
struct CRTP_hexception
    : cpptrace::lazy_exception
    , CRTP_this_method<Derived> {
    std::string          msg;
    int                  line;
    char const*          function;
    char const*          file;
    cpptrace::stacktrace eager;

    static Derived init(
        std::string const& msg,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE()) {
        auto result     = Derived{};
        result.eager    = cpptrace::generate_trace();
        result.msg      = msg;
        result.line     = line;
        result.file     = file;
        result.function = function;
        return result;
    }


  public:
    virtual cpptrace::stacktrace const& trace() const noexcept override {
        return eager;
    }

    virtual const char* message() const noexcept override {
        return strdup(
            std::format("{} at {}:{} in {}", msg, file, line, function)
                .c_str());
    }
};


struct logic_assertion_error : CRTP_hexception<logic_assertion_error> {};
struct logic_unreachable_error : CRTP_hexception<logic_assertion_error> {};


#define LOGIC_ASSERTION_CHECK(expr, message_fmt, ...)                     \
    if (!(expr)) {                                                        \
        throw logic_assertion_error::init(                                \
            fmt("{}: {}",                                                 \
                #expr,                                                    \
                fmt(message_fmt __VA_OPT__(, ) __VA_ARGS__)));            \
    }

#define logic_todo_impl() throw logic_assertion_error::init("TODO");


inline void assert_has_idx(int size, int wanted, std::string failure) {
    if (!(wanted < size)) { throw std::range_error(failure); }
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
