#pragma once

#define __INIT_REPORT(__subname, __str)                                   \
    (::OrgTokenizer::Report{                                              \
        OperationsMsg{.file = __FILE__, .line = __LINE__},                \
        .subname = __subname,                                             \
        .lex     = &lex,                                                  \
    })

#define __print2(__text, __str)                                           \
    if (TraceState) {                                                     \
        report(::OrgTokenizer::Report{                                    \
            .kind    = ReportKind::Print,                                 \
            .file    = __FILE__,                                          \
            .line    = __LINE__,                                          \
            .subname = __text,                                            \
            .name    = __FUNCTION__,                                      \
        });                                                               \
    }

#define __print1(__text) __print2(__text, &str)

#define __print(...)                                                      \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__print, __VA_ARGS__)(__VA_ARGS__),             \
        BOOST_PP_EMPTY())


#define __push_rep()                                                      \
    ::OrgTokenizer::Report {                                              \
        .line = __LINE__, .kind = ::OrgTokenizer::ReportKind::Push,       \
        .file = __FILE__,                                                 \
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

#ifdef ORG_USE_PERFETTO
#    define __perf_trace(name) TRACE_EVENT("lexing", name)
#else
#    define __perf_trace(a)
#endif
