#pragma once

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
    Type&       get##Type() { return std::get<Type>(fieldName); }         \
    Type const& get##Type() const { return std::get<Type>(fieldName); }

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
    static EnumName kindGetterName(CR<VariantName> __input) {             \
        return std::visit(                                                \
            overloaded{FOR_EACH_CALL_WITH_PASS(                           \
                __SUB_VARIANT_KIND_LAMBDA, (EnumName), __VA_ARGS__)},     \
            __input);                                                     \
    }                                                                     \
    EnumName kindGetterName() const { return kindGetterName(fieldName); } \
    using variant_enum_type = EnumName;                                   \
    using variant_data_type = VariantName;


template <typename T>
concept IsSubVariantType = requires() {
    typename T::variant_enum_type;
    typename T::variant_data_type;
};


#define __DECL_FIELDS_define_field_aux(first, second, third)              \
    __unpack_pars first second = third;

#define __DECL_FIELDS_per_field(class_bases_bases, field)                 \
    __DECL_FIELDS_define_field(field)

#define __DECL_FIELDS_get_field_name_aux(a, fieldName, d) fieldName
#define __DECL_FIELDS_get_field_name(_, arg)                              \
    , __DECL_FIELDS_get_field_name_aux arg
#define __DECL_FIELDS_drop_leading_comma(first, ...) __VA_ARGS__

#define __DECL_FIELDS_define_field(arg) __DECL_FIELDS_define_field_aux arg
#define __DECL_FIELDS_define_field_only(_, arg)                           \
    __DECL_FIELDS_define_field_aux arg

#define __DECL_FIELDS_pass_args_field_aux(_1, fieldname, _3)              \
    fieldname(args.fieldname),
#define __DECL_FIELDS_pass_args_field(_, arg)                             \
    __DECL_FIELDS_pass_args_field_aux arg

#define EMPTY()

#define DECL_FIELDS(classname, bases, ...)                                \
    FOR_EACH_CALL_WITH_PASS(                                              \
        __DECL_FIELDS_per_field, (classname, bases), __VA_ARGS__)         \
                                                                          \
    BOOST_DESCRIBE_CLASS(                                                 \
        classname,                                                        \
        bases, /* Expand teh list of fields and leave only the the name   \
                  of the field to be passed to the public members of the  \
                  boost describe */                                       \
        (      /* < Extra wrapping paren, __get_field_name leaves out the \
                    a,b,c,d,e list*/                                      \
         __DECL_FIELDS_drop_leading_comma EMPTY()(                        \
             EXPAND(FOR_EACH_CALL_WITH_PASS(                              \
                 __DECL_FIELDS_get_field_name,                            \
                 () /* < Nothing to pass around */,                       \
                 __VA_ARGS__)))),                                         \
        () /* For simplicity reasons, sem nodes have public fields and no \
              protected/private members */                                \
        ,                                                                 \
        ());

#define DESC_FIELDS(classname, ...) \
    BOOST_DESCRIBE_CLASS(classname (), (__VA_ARGS__), (), (), ())
