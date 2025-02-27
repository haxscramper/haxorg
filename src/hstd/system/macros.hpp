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

/// \internal Generate getter methods for SUB_VARIANTS
#define __SUB_VARIANT_GETTER(fieldName, Type)                             \
    Type& get##Type() {                                                   \
        return ::hstd::                                                   \
            get_sub_variant<Type, std::remove_cvref_t<decltype(*this)>>(  \
                fieldName);                                               \
    }                                                                     \
                                                                          \
    Type const& get##Type() const {                                       \
        return ::hstd::                                                   \
            get_sub_variant<Type, std::remove_cvref_t<decltype(*this)>>(  \
                fieldName);                                               \
    }                                                                     \
                                                                          \
    bool is##Type() const {                                               \
        return std::holds_alternative<Type>(fieldName);                   \
    }

/// \internal Generate kind getter lambda for SUB_VARIANTS
#define __SUB_VARIANT_KIND_LAMBDA(EnumName, Type)                         \
    [](Type const&) -> EnumName { return EnumName::Type; },

/// \brief Declare enum \arg Name with all it's fields and pass them to
/// BOOST_DESCRIBE_NESTED_ENUM to generate reflection information.
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

/// \brief Helper macro for better API when working with discriminant
/// objects.
///
/// \arg EnumName name of the enumeration that is defined to list possible
///      variant values
/// \arg VariantName Name of the variant type for wrapping
///      all results
/// \arg fieldName Name of the field that is used to store
///      variant value for a type
/// \arg kindGetterName name of the method for getting kind from the field.
///      Also defines static function that can be used to access the kind
///      of the raw variant value.
///
/// \snippet sem/SemOrg.hpp declare variant field for subtree properties
///
/// This will generate `getKind()` and `static getKind(Data const&)`
/// methods, define `Data` as `std::variant<Ordered, ...>` and implement
/// `getOrdered()`, `getTrigger()` etc. for all provided types
#define SUB_VARIANTS(                                                     \
    EnumName, VariantName, fieldName, kindGetterName, ...)                \
    DECL_DESCRIBED_ENUM(EnumName, __VA_ARGS__)                            \
    using VariantName = std::variant<__VA_ARGS__>;                        \
    FOR_EACH_CALL_WITH_PASS(                                              \
        __SUB_VARIANT_GETTER, (fieldName), __VA_ARGS__)                   \
    static EnumName kindGetterName(VariantName const& __input) {          \
        return std::visit(                                                \
            ::hstd::overloaded{FOR_EACH_CALL_WITH_PASS(                   \
                __SUB_VARIANT_KIND_LAMBDA, (EnumName), __VA_ARGS__)},     \
            __input);                                                     \
    }                                                                     \
    EnumName kindGetterName() const { return kindGetterName(fieldName); } \
    using variant_enum_type = EnumName;                                   \
    using variant_data_type = VariantName;                                \
    EnumName sub_variant_get_kind() const { return kindGetterName(); }    \
    VariantName const& sub_variant_get_data() const { return fieldName; } \
    char const*        sub_variant_get_name() const { return #fieldName; }


#define DESC_FIELDS(classname, arg)                                       \
    BOOST_DESCRIBE_CLASS(classname, (), arg, (), ())


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
    BOOST_PP_EXPAND(BOOST_PP_TUPLE_REM() BOOST_PP_IF(                     \
        IS_EMPTY_TUPLE(__VisitorTemplateArgs),                            \
        (),                                                               \
        (template <BOOST_PP_TUPLE_REM() __VisitorTemplateArgs>)))         \
    BOOST_PP_TUPLE_REM()                                                  \
    __VisitorResultType __VisitorTypename<                                \
        BOOST_PP_TUPLE_REM() __VisitorTypeSpecification>::                \
        __VisitorMethodName(                                              \
            BOOST_PP_TUPLE_REM() __VisitorTypeSpecification const& arg,   \
            BOOST_PP_TUPLE_REM() __VisitorSharedArgs)

/// ```
/// #define IMM_TREE_REPR_IMPL(__TemplateArgs, __VisitorTypeSpecification)   \
///    DEFINE_VISITOR_BASE_ALL(                                              \
///        /*Typename=*/ImmTreeReprVisitor,                                  \
///        /*TemplateArgs=*/__TemplateArgs,                                  \
///        /*SharedArgs=*/(ColStream & os, ImmTreeReprContext const& ctx),   \
///        /*TypeSpecification=*/__VisitorTypeSpecification,                 \
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
