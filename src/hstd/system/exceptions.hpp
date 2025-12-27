#pragma once


#include <cstring>
#include <stdexcept>
#include <string>
#include <hstd/system/aux_utils.hpp>
#if !ORG_EMCC_BUILD
#    include <cpptrace.hpp>
#endif

namespace hstd {

template <
    typename Derived,
#if ORG_EMCC_BUILD
    typename BaseException = std::exception
#else
    typename BaseException = cpptrace::lazy_exception
#endif
    >
struct CRTP_hexception
    : BaseException
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
    const char* get_fmt_message() const noexcept {
        std::string result = msg;
        result += " at ";
        result += file;
        result += ":";
        result += std::to_string(line);
        result += " in ";
        result += function;
        return strdup(result.c_str());
    }

#if ORG_EMCC_BUILD
    virtual const char* what() const noexcept override {
        return get_fmt_message();
    }
#else
    virtual cpptrace::stacktrace const& trace() const noexcept override {
        return eager;
    }

    virtual const char* message() const noexcept override {
        return get_fmt_message();
    }
#endif
};

struct invalid_argument : CRTP_hexception<invalid_argument> {};

struct logic_error : CRTP_hexception<logic_error> {};
struct logic_assertion_error
    : CRTP_hexception<logic_assertion_error, logic_error> {};
struct logic_unreachable_error
    : CRTP_hexception<logic_unreachable_error, logic_error> {};

struct range_error : CRTP_hexception<range_error> {};

struct runtime_error : CRTP_hexception<runtime_error> {};

struct domain_error : CRTP_hexception<domain_error> {};

struct getter_error : CRTP_hexception<getter_error, invalid_argument> {};
struct key_error : CRTP_hexception<key_error, invalid_argument> {};
struct unexpected_kind_error
    : CRTP_hexception<unexpected_kind_error, domain_error> {};

#define LOGIC_ASSERTION_CHECK_FMT(expr, message_fmt, ...)                 \
    if (!(expr)) {                                                        \
        throw ::hstd::logic_assertion_error::init(::hstd::fmt(            \
            "{}: {}",                                                     \
            #expr,                                                        \
            ::hstd::fmt(message_fmt __VA_OPT__(, ) __VA_ARGS__)));        \
    }

#define LOGIC_ASSERTION_CHECK(expr, __message)                            \
    if (!(expr)) {                                                        \
        throw ::hstd::logic_assertion_error::init(                        \
            std::string{#expr ": "} + std::string{__message});            \
    }

#define logic_todo_impl() throw hstd::logic_assertion_error::init("TODO");


inline void assert_has_idx(int size, int wanted, std::string failure) {
    if (!(wanted < size)) { throw std::range_error(failure); }
}
} // namespace hstd
