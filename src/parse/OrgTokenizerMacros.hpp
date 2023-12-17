#pragma once


#define __INIT_REPORT(__subname, __str)                                   \
    (::OrgTokenizer::Report{                                              \
        .location = __CURRENT_FILE_PATH__,                                \
        .line     = __LINE__,                                             \
        .subname  = __subname,                                            \
        .lex      = &lex,                                                 \
    })

#define __print2(__text, __str)                                           \
    if (TraceState) {                                                     \
        report(::OrgTokenizer::Report{                                    \
            .kind     = ReportKind::Print,                                \
            .location = __CURRENT_FILE_PATH__,                            \
            .line     = __LINE__,                                         \
            .subname  = __text,                                           \
        });                                                               \
    }

#define __print1(__text) __print2(__text, &str)

#define __print(...)                                                      \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__print, __VA_ARGS__)(__VA_ARGS__),             \
        BOOST_PP_EMPTY())


#define __trace2(__subname, __str)                                        \
    if (TraceState) {                                                     \
        ::OrgTokenizer::Report rep = __INIT_REPORT(__subname, __str);     \
        rep.kind                   = ::OrgTokenizer::ReportKind::Enter;   \
        rep.name                   = __func__;                            \
        report(rep);                                                      \
    }                                                                     \
                                                                          \
    finally CONCAT(close, __COUNTER__) = finally::init<Str>(              \
        ([&](CR<Str> name) {                                              \
            if (TraceState) {                                             \
                ::OrgTokenizer::Report rep = __INIT_REPORT(               \
                    __subname, __str);                                    \
                rep.kind = ::OrgTokenizer::ReportKind::Leave;             \
                rep.name = name;                                          \
                report(rep);                                              \
            }                                                             \
        }),                                                               \
        Str(__func__));


#define __push_rep()                                                      \
    ::OrgTokenizer::Report {                                              \
        .line = __LINE__, .kind = ::OrgTokenizer::ReportKind::Push,       \
        .location = __CURRENT_FILE_PATH__                                 \
    }

#define __push2(token, __is_buffered)                                     \
    if (TraceState) {                                                     \
        Report rep      = __INIT_REPORT(std::nullopt, str);               \
        rep.kind        = ::OrgTokenizer::ReportKind::Push;               \
        rep.tok         = token;                                          \
        auto id         = push(token);                                    \
        rep.id          = id;                                             \
        rep.addBuffered = __is_buffered;                                  \
        report(rep);                                                      \
    } else {                                                              \
        push(token);                                                      \
    }

#define __push1(token) __push2(token, false);

#define __push(...)                                                       \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__push, __VA_ARGS__)(__VA_ARGS__),              \
        BOOST_PP_EMPTY())

#define __trace1(__subname) __trace2(__subname, str)
#define __trace0() __trace2(std::nullopt, str)


#define __trace(...)                                                      \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__trace, __VA_ARGS__)(__VA_ARGS__),             \
        BOOST_PP_EMPTY())


#define __report_error(err)                                               \
    if (TraceState) {                                                     \
        ::OrgTokenizer::Report rep = ::OrgTokenizer::Report({             \
            .line  = __LINE__,                                            \
            .kind  = ReportKind::Error,                                   \
            .name  = __func__,                                            \
            .error = err,                                                 \
        });                                                               \
        report(rep);                                                      \
    }


#define __report_and_throw(expr)                                          \
    {                                                                     \
        auto __err = TokenizerError(expr);                                \
        if (locationResolver) {                                           \
            PosStr str{__err.getView(), __err.getPos()};                  \
            __err.setLoc(locationResolver(str));                          \
        } else {                                                          \
            qFatal("Missing location resolver");                          \
        }                                                                 \
                                                                          \
        __report_error(__err);                                            \
        throw __err;                                                      \
    }


#define __start(str) startGroup(str);
#define __end(str) endGroup(str);

#define __fail_group(err)                                                 \
    auto tok = error(err);                                                \
    __report_error(err);                                                  \
    __push(tok);                                                          \
    __end(str);


#define EMPTY()

#ifdef USE_PERFETTO
#    define __perf_trace(name) TRACE_EVENT("lexing", name)
#else
#    define __perf_trace(a)
#endif
