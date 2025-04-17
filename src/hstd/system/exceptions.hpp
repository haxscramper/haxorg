#pragma once

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <hstd/system/aux_utils.hpp>
#include <format>
#if !ORG_EMCC_BUILD
#    include <cpptrace.hpp>
#endif
#include <sstream>

namespace hstd {

template <typename Derived>
struct CRTP_hexception
    :
#if ORG_EMCC_BUILD
    std::exception
#else
    cpptrace::lazy_exception
#endif
    , CRTP_this_method<Derived> {
    std::string msg;
    int         line;
    char const* function;
    char const* file;
#if !ORG_EMCC_BUILD
    cpptrace::stacktrace eager;
#endif

    static Derived init(
        std::string const& msg,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE()) {
        auto result = Derived{};
#if !ORG_EMCC_BUILD
        result.eager = cpptrace::generate_trace();
#endif
        result.msg      = msg;
        result.line     = line;
        result.file     = file;
        result.function = function;
        return result;
    }


  public:
#if ORG_EMCC_BUILD
    virtual const char* what() const noexcept override {
        return strdup(
            std::format("{} at {}:{} in {}", msg, file, line, function)
                .c_str());
    }
#else
    virtual cpptrace::stacktrace const& trace() const noexcept override {
        return eager;
    }

    virtual const char* message() const noexcept override {
        return strdup(
            std::format("{} at {}:{} in {}", msg, file, line, function)
                .c_str());
    }
#endif
};


struct logic_assertion_error : CRTP_hexception<logic_assertion_error> {};
struct logic_unreachable_error : CRTP_hexception<logic_assertion_error> {};
struct out_of_range_error : CRTP_hexception<out_of_range_error> {};


#define LOGIC_ASSERTION_CHECK(expr, message_fmt, ...)                     \
    if (!(expr)) {                                                        \
        throw ::hstd::logic_assertion_error::init(::hstd::fmt(            \
            "{}: {}",                                                     \
            #expr,                                                        \
            ::hstd::fmt(message_fmt __VA_OPT__(, ) __VA_ARGS__)));        \
    }

#define logic_todo_impl() throw hstd::logic_assertion_error::init("TODO");


inline void assert_has_idx(int size, int wanted, std::string failure) {
    if (!(wanted < size)) { throw std::range_error(failure); }
}

struct GetterError : CRTP_hexception<GetterError> {};
struct KeyError : CRTP_hexception<KeyError> {};
struct LogicError : CRTP_hexception<LogicError> {};
struct UnexpectedKindError : CRTP_hexception<UnexpectedKindError> {};
struct RangeError : CRTP_hexception<RangeError> {};

} // namespace hstd
