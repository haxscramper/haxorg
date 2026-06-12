#pragma once

#include <concepts>
#define PARENS ()

#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define __unpack_pars(...) __VA_ARGS__
#define __macro_aux(macro, pass, ...)                                     \
    macro(__unpack_pars pass, __VA_ARGS__)


#define __FOR_EACH_HELPER(macro, pass, a1, ...)                           \
    __macro_aux(macro, pass, a1)                                          \
        __VA_OPT__(__FOR_EACH_AGAIN PARENS(macro, pass, __VA_ARGS__))

#define __FOR_EACH_AGAIN() __FOR_EACH_HELPER

#define FOR_EACH_CALL_WITH_PASS(macro, pass, ...)                         \
    __VA_OPT__(EXPAND(__FOR_EACH_HELPER(macro, pass, __VA_ARGS__)))


/// \brief Utility method to list fields for class.
///
/// `DESC_FIELDS(<class-name>, (<field1>, <field2>, ...)`
#define DESC_FIELDS(classname, arg)                                       \
    BOOST_DESCRIBE_CLASS(classname, (), arg, (), ())

/// \brief Declare enum \arg Name with all it's fields and pass them to
/// BOOST_DESCRIBE_NESTED_ENUM to generate reflection information.
///
/// `DECL_DESCRIBED_ENUM(EnumName, F1, F2)`, will declare an `num class
/// EnumName` with the specified fields.
///
/// To declare enum outside of the class, use \ref
/// DECL_DESCRIBED_ENUM_STANDALONE with the same API.
#define DECL_DESCRIBED_ENUM(Name, ...)                                    \
    enum class Name : unsigned short int                                  \
    {                                                                     \
        __VA_ARGS__                                                       \
    };                                                                    \
    BOOST_DESCRIBE_NESTED_ENUM(Name, __VA_ARGS__);

/// \brief Declare enum \arg Name with all it's fields and pass them to
/// BOOST_DESCRIBE_NESTED_ENUM to generate reflection information.
#define DECL_DESCRIBED_ENUM_STANDALONE(Name, ...)                         \
    enum class Name                                                       \
    {                                                                     \
        __VA_ARGS__                                                       \
    };                                                                    \
    BOOST_DESCRIBE_ENUM(Name, __VA_ARGS__);


#define DEFINE_VISITOR_BASE_STRUCT(                                       \
    __VisitorTypename,                                                    \
    __VisitorTemplateArgs,                                                \
    __VisitorSharedArgs,                                                  \
    __VisitorTypeSpecification,                                           \
    __VisitorResultType,                                                  \
    __VisitorMethodName)                                                  \
                                                                          \
    template <BOOST_PP_TUPLE_REM() __VisitorTemplateArgs>                 \
    struct __VisitorTypename<BOOST_PP_TUPLE_REM()                         \
                                 __VisitorTypeSpecification> {            \
        static BOOST_PP_TUPLE_REM() __VisitorResultType                   \
            __VisitorMethodName(                                          \
                BOOST_PP_TUPLE_REM()                                      \
                    __VisitorTypeSpecification const& arg,                \
                BOOST_PP_TUPLE_REM() __VisitorSharedArgs);                \
    };

#define IS_EMPTY_TUPLE(tuple)                                             \
    BOOST_PP_IS_EMPTY(BOOST_PP_TUPLE_ELEM(0, tuple))

#define DEFINE_VISITOR_BASE_METHOD_SIGNATURE(                             \
    __VisitorTypename,                                                    \
    __VisitorTemplateArgs,                                                \
    __VisitorSharedArgs,                                                  \
    __VisitorTypeSpecification,                                           \
    __VisitorResultType,                                                  \
    __VisitorMethodName)                                                  \
                                                                          \
    BOOST_PP_EXPAND(                                                      \
        BOOST_PP_TUPLE_REM() BOOST_PP_IF(                                 \
            IS_EMPTY_TUPLE(__VisitorTemplateArgs),                        \
            (),                                                           \
            (template <BOOST_PP_TUPLE_REM() __VisitorTemplateArgs>)))     \
    BOOST_PP_TUPLE_REM()                                                  \
    __VisitorResultType __VisitorTypename<                                \
        BOOST_PP_TUPLE_REM() __VisitorTypeSpecification>::                \
        __VisitorMethodName(                                              \
            BOOST_PP_TUPLE_REM() __VisitorTypeSpecification const& arg,   \
            BOOST_PP_TUPLE_REM() __VisitorSharedArgs)

/// ```
/// #define IMM_TREE_REPR_IMPL(__TemplateArgs, __VisitorTypeSpecification)   \
///    DEFINE_VISITOR_BASE_ALL( \
///        /*Typename=*/ImmTreeReprVisitor, \
///        /*TemplateArgs=*/__TemplateArgs, \
///        /*SharedArgs=*/(ColStream & os, ImmTreeReprContext const& ctx),
///        \
///        /*TypeSpecification=*/__VisitorTypeSpecification, \
///        /*ResultType=*/(void))
/// ```

#define DEFINE_VISITOR_BASE_ALL(                                          \
    __VisitorTypename,                                                    \
    __VisitorTemplateArgs,                                                \
    __VisitorSharedArgs,                                                  \
    __VisitorTypeSpecification,                                           \
    __VisitorResultType,                                                  \
    __VisitorMethodName)                                                  \
                                                                          \
    DEFINE_VISITOR_BASE_STRUCT(                                           \
        __VisitorTypename,                                                \
        __VisitorTemplateArgs,                                            \
        __VisitorSharedArgs,                                              \
        __VisitorTypeSpecification,                                       \
        __VisitorResultType,                                              \
        __VisitorMethodName)                                              \
                                                                          \
    DEFINE_VISITOR_BASE_METHOD_SIGNATURE(                                 \
        __VisitorTypename,                                                \
        __VisitorTemplateArgs,                                            \
        __VisitorSharedArgs,                                              \
        __VisitorTypeSpecification,                                       \
        __VisitorResultType,                                              \
        __VisitorMethodName)
