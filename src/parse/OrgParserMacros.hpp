#pragma once

import std.wrappers.perfetto_aux;
#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#ifdef USE_PERFETTO
#    define __perf_trace(name) TRACE_EVENT("parsing", name)
#else
#    define __perf_trace(_)
#endif

#define __INIT_REPORT(__subname, __lex)                                   \
    (Report{                                                              \
        .location = __CURRENT_FILE_PATH__,                                \
        .line     = __LINE__,                                             \
        .subname  = __subname,                                            \
        .lex      = &__lex,                                               \
    })

#define __trace2(__subname, __lex)                                        \
    if (TraceState) {                                                     \
        Report rep = __INIT_REPORT(__subname, __lex);                     \
        rep.kind   = ReportKind::EnterParse;                              \
        rep.name   = __func__;                                            \
        report(rep);                                                      \
    }                                                                     \
                                                                          \
    finally CONCAT(close, __COUNTER__) = finally::init<Str>(              \
        ([&](CR<Str> name) {                                              \
            if (TraceState) {                                             \
                Report rep = __INIT_REPORT(__subname, __lex);             \
                rep.kind   = ReportKind::LeaveParse;                      \
                rep.name   = name;                                        \
                report(rep);                                              \
            }                                                             \
        }),                                                               \
        Str(__func__));


#define __trace1(__subname) __trace2(__subname, lex)
#define __trace0() __trace2(std::nullopt, lex)

#define __trace(...)                                                      \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__trace, __VA_ARGS__)(__VA_ARGS__),             \
        BOOST_PP_EMPTY())


#define __print2(__text, __lex)                                           \
    if (TraceState) {                                                     \
        report(Report{                                                    \
            .kind     = ReportKind::Print,                                \
            .location = __CURRENT_FILE_PATH__,                            \
            .line     = __LINE__,                                         \
            .subname  = __text,                                           \
            .lex      = __lex,                                            \
        });                                                               \
    }

#define __print1(__text) __print2(__text, &lex)

#define __print(...)                                                      \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__print, __VA_ARGS__)(__VA_ARGS__),             \
        BOOST_PP_EMPTY())


#define __end2(__subname, __lex)                                          \
    OrgId CONCAT(tmpNode, __LINE__) = end();                              \
    if (TraceState) {                                                     \
        Report rep = __INIT_REPORT(__subname, __lex);                     \
        rep.kind   = ReportKind::EndNode;                                 \
        rep.node   = CONCAT(tmpNode, __LINE__);                           \
        report(rep);                                                      \
    }


#define __end1(__subname) __end2(__subname, lex)
#define __end0() __end2(std::nullopt, lex);

#define __end(...)                                                        \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__end, __VA_ARGS__)(__VA_ARGS__),               \
        BOOST_PP_EMPTY())

#define __end_return(...)                                                 \
    __end(__VA_ARGS__);                                                   \
    return CONCAT(tmpNode, __LINE__);

#define __start3(__node, __subname, __lex)                                  \
    if (TraceState) {                                                       \
        OrgId  CONCAT(tmpNode, __LINE__) = start(__node);                   \
        Report rep                       = __INIT_REPORT(__subname, __lex); \
        rep.kind                         = ReportKind::StartNode;           \
        rep.node                         = CONCAT(tmpNode, __LINE__);       \
        report(rep);                                                        \
    } else {                                                                \
        (void)start(__node);                                                \
    }


#define __start2(__node, __subname) __start3(__node, __subname, lex)
#define __start1(__node) __start3(__node, std::nullopt, lex);

#define __start(...)                                                      \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__start, __VA_ARGS__)(__VA_ARGS__),             \
        BOOST_PP_EMPTY())


#define __token3(__node, __subname, __lex)                                \
    if (TraceState) {                                                     \
        Report rep = __INIT_REPORT(__subname, __lex);                     \
        rep.kind   = ReportKind::AddToken;                                \
        rep.node   = __node;                                              \
        report(rep);                                                      \
    }

#define __token2(__node, __subname) __token3(__node, __subname, lex)
#define __token1(__node) __token3(__node, std::nullopt, lex);

#define __token(...)                                                      \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__token, __VA_ARGS__)(__VA_ARGS__),             \
        BOOST_PP_EMPTY())


#define __skip(__lex, __kind)                                             \
    if (TraceState) {                                                     \
        if (!at(__lex, __kind)) {                                         \
            __print(                                                      \
                "!! $#: Expected token '$#' $# but got '$#'"              \
                % to_string_vec(                                          \
                    __LINE__, __kind, getLocMsg(__lex), __lex.kind()));   \
        }                                                                 \
    }                                                                     \
    skip(__lex, __kind);
