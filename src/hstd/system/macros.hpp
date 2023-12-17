#pragma once

#include <boost/describe.hpp>

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

#pragma once

#define CONCAT(a, b) CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a##b


#define __ploc()                                                          \
    std::cout << __FILE__ << ":" << __LINE__ << " at " << __func__        \
              << std::endl;



// clang-format off

// They thought 52 arguments would be enough for anyone ...
// This abomination is for cases where enum has more than 52 arguments. It overrides the 
// existing implementation from boost::describe, but follows the same pattern.              

#define BOOST_DESCRIBE_PP_FOR_EACH_0(F, a)
#define BOOST_DESCRIBE_PP_FOR_EACH_1(F, a, x) BOOST_DESCRIBE_PP_CALL(F, a, x)
#define BOOST_DESCRIBE_PP_FOR_EACH_2(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_1(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_3(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_2(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_4(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_3(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_5(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_4(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_6(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_5(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_7(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_6(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_8(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_7(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_9(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_8(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_10(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_9(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_11(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_10(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_12(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_11(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_13(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_12(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_14(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_13(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_15(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_14(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_16(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_15(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_17(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_16(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_18(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_17(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_19(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_18(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_20(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_19(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_21(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_20(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_22(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_21(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_23(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_22(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_24(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_23(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_25(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_24(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_26(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_25(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_27(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_26(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_28(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_27(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_29(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_28(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_30(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_29(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_31(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_30(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_32(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_31(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_33(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_32(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_34(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_33(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_35(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_34(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_36(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_35(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_37(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_36(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_38(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_37(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_39(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_38(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_40(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_39(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_41(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_40(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_42(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_41(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_43(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_42(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_44(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_43(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_45(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_44(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_46(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_45(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_47(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_46(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_48(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_47(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_49(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_48(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_50(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_49(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_51(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_50(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_52(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_51(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_53(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_52(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_54(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_53(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_55(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_54(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_56(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_55(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_57(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_56(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_58(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_57(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_59(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_58(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_60(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_59(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_61(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_60(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_62(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_61(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_63(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_62(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_64(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_63(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_65(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_64(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_66(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_65(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_67(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_66(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_68(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_67(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_69(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_68(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_70(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_69(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_71(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_70(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_72(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_71(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_73(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_72(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_74(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_73(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_75(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_74(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_76(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_75(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_77(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_76(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_78(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_77(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_79(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_78(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_80(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_79(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_81(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_80(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_82(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_81(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_83(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_82(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_84(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_83(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_85(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_84(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_86(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_85(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_87(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_86(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_88(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_87(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_89(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_88(F, a, __VA_ARGS__))

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmacro-redefined"

#define BOOST_DESCRIBE_PP_FE_EXTRACT(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _77, _76, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, V, ...) V

#define BOOST_DESCRIBE_PP_FOR_EACH(F, ...) \
    BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_FE_EXTRACT(__VA_ARGS__, \
    BOOST_DESCRIBE_PP_FOR_EACH_89, \
    BOOST_DESCRIBE_PP_FOR_EACH_88, \
    BOOST_DESCRIBE_PP_FOR_EACH_87, \
    BOOST_DESCRIBE_PP_FOR_EACH_86, \
    BOOST_DESCRIBE_PP_FOR_EACH_85, \
    BOOST_DESCRIBE_PP_FOR_EACH_84, \
    BOOST_DESCRIBE_PP_FOR_EACH_83, \
    BOOST_DESCRIBE_PP_FOR_EACH_82, \
    BOOST_DESCRIBE_PP_FOR_EACH_81, \
    BOOST_DESCRIBE_PP_FOR_EACH_80, \
    BOOST_DESCRIBE_PP_FOR_EACH_79, \
    BOOST_DESCRIBE_PP_FOR_EACH_78, \
    BOOST_DESCRIBE_PP_FOR_EACH_77, \
    BOOST_DESCRIBE_PP_FOR_EACH_76, \
    BOOST_DESCRIBE_PP_FOR_EACH_75, \
    BOOST_DESCRIBE_PP_FOR_EACH_74, \
    BOOST_DESCRIBE_PP_FOR_EACH_73, \
    BOOST_DESCRIBE_PP_FOR_EACH_72, \
    BOOST_DESCRIBE_PP_FOR_EACH_71, \
    BOOST_DESCRIBE_PP_FOR_EACH_70, \
    BOOST_DESCRIBE_PP_FOR_EACH_69, \
    BOOST_DESCRIBE_PP_FOR_EACH_68, \
    BOOST_DESCRIBE_PP_FOR_EACH_67, \
    BOOST_DESCRIBE_PP_FOR_EACH_66, \
    BOOST_DESCRIBE_PP_FOR_EACH_65, \
    BOOST_DESCRIBE_PP_FOR_EACH_64, \
    BOOST_DESCRIBE_PP_FOR_EACH_63, \
    BOOST_DESCRIBE_PP_FOR_EACH_62, \
    BOOST_DESCRIBE_PP_FOR_EACH_61, \
    BOOST_DESCRIBE_PP_FOR_EACH_60, \
    BOOST_DESCRIBE_PP_FOR_EACH_59, \
    BOOST_DESCRIBE_PP_FOR_EACH_58, \
    BOOST_DESCRIBE_PP_FOR_EACH_57, \
    BOOST_DESCRIBE_PP_FOR_EACH_56, \
    BOOST_DESCRIBE_PP_FOR_EACH_55, \
    BOOST_DESCRIBE_PP_FOR_EACH_54, \
    BOOST_DESCRIBE_PP_FOR_EACH_53, \
    BOOST_DESCRIBE_PP_FOR_EACH_52, \
    BOOST_DESCRIBE_PP_FOR_EACH_51, \
    BOOST_DESCRIBE_PP_FOR_EACH_50, \
    BOOST_DESCRIBE_PP_FOR_EACH_49, \
    BOOST_DESCRIBE_PP_FOR_EACH_48, \
    BOOST_DESCRIBE_PP_FOR_EACH_47, \
    BOOST_DESCRIBE_PP_FOR_EACH_46, \
    BOOST_DESCRIBE_PP_FOR_EACH_45, \
    BOOST_DESCRIBE_PP_FOR_EACH_44, \
    BOOST_DESCRIBE_PP_FOR_EACH_43, \
    BOOST_DESCRIBE_PP_FOR_EACH_42, \
    BOOST_DESCRIBE_PP_FOR_EACH_41, \
    BOOST_DESCRIBE_PP_FOR_EACH_40, \
    BOOST_DESCRIBE_PP_FOR_EACH_39, \
    BOOST_DESCRIBE_PP_FOR_EACH_38, \
    BOOST_DESCRIBE_PP_FOR_EACH_37, \
    BOOST_DESCRIBE_PP_FOR_EACH_36, \
    BOOST_DESCRIBE_PP_FOR_EACH_35, \
    BOOST_DESCRIBE_PP_FOR_EACH_34, \
    BOOST_DESCRIBE_PP_FOR_EACH_33, \
    BOOST_DESCRIBE_PP_FOR_EACH_32, \
    BOOST_DESCRIBE_PP_FOR_EACH_31, \
    BOOST_DESCRIBE_PP_FOR_EACH_30, \
    BOOST_DESCRIBE_PP_FOR_EACH_29, \
    BOOST_DESCRIBE_PP_FOR_EACH_28, \
    BOOST_DESCRIBE_PP_FOR_EACH_27, \
    BOOST_DESCRIBE_PP_FOR_EACH_26, \
    BOOST_DESCRIBE_PP_FOR_EACH_25, \
    BOOST_DESCRIBE_PP_FOR_EACH_24, \
    BOOST_DESCRIBE_PP_FOR_EACH_23, \
    BOOST_DESCRIBE_PP_FOR_EACH_22, \
    BOOST_DESCRIBE_PP_FOR_EACH_21, \
    BOOST_DESCRIBE_PP_FOR_EACH_20, \
    BOOST_DESCRIBE_PP_FOR_EACH_19, \
    BOOST_DESCRIBE_PP_FOR_EACH_18, \
    BOOST_DESCRIBE_PP_FOR_EACH_17, \
    BOOST_DESCRIBE_PP_FOR_EACH_16, \
    BOOST_DESCRIBE_PP_FOR_EACH_15, \
    BOOST_DESCRIBE_PP_FOR_EACH_14, \
    BOOST_DESCRIBE_PP_FOR_EACH_13, \
    BOOST_DESCRIBE_PP_FOR_EACH_12, \
    BOOST_DESCRIBE_PP_FOR_EACH_11, \
    BOOST_DESCRIBE_PP_FOR_EACH_10, \
    BOOST_DESCRIBE_PP_FOR_EACH_9, \
    BOOST_DESCRIBE_PP_FOR_EACH_8, \
    BOOST_DESCRIBE_PP_FOR_EACH_7, \
    BOOST_DESCRIBE_PP_FOR_EACH_6, \
    BOOST_DESCRIBE_PP_FOR_EACH_5, \
    BOOST_DESCRIBE_PP_FOR_EACH_4, \
    BOOST_DESCRIBE_PP_FOR_EACH_3, \
    BOOST_DESCRIBE_PP_FOR_EACH_2, \
    BOOST_DESCRIBE_PP_FOR_EACH_1, \
    BOOST_DESCRIBE_PP_FOR_EACH_0))(F, __VA_ARGS__))

#pragma clang diagnostic pop
// clang-format on