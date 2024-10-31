#pragma once
#include <hstd/system/aux_utils.hpp>
#include <hstd/stdlib/Str.hpp>

template <typename Derived>
struct CRTP_hexception
    : std::exception
    , CRTP_this_method<Derived> {
    Str         msg;
    int         line;
    char const* function;
    char const* file;

    static Derived init(
        Str const&  msg,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION(),
        char const* file     = __builtin_FILE()) {
        auto result     = Derived{};
        result.msg      = msg;
        result.line     = line;
        result.file     = file;
        result.function = function;
        return result;
    }


  public:
    virtual const char* what() const noexcept override {
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
            fmt("{}: {}",                                                  \
                #expr,                                                    \
                fmt(message_fmt __VA_OPT__(, ) __VA_ARGS__)));            \
    }

#define logic_todo_impl() throw logic_assertion_error::init("TODO");
