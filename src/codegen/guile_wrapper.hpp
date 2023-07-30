#pragma once

extern "C" {
#include <libguile.h>
}

#include <string>
#include <functional>
#include <iostream>
#include <boost/mp11.hpp>
#include <boost/describe.hpp>

#include <hstd/system/macros.hpp>
#include <hstd/system/reflection.hpp>

#include <fmt/core.h>

namespace guile {

DECL_DESCRIBED_ENUM_STANDALONE(
    ValueKind,
    TrueLiteral,
    FalseLiteral,
    Integer,
    Real,
    Complex,
    Char,
    String,
    Symbol,
    Vector,
    List,
    Alist,
    Plist,
    GoopsInstance,
    Unspecified,
    Procedure,
    Port,
    Promise,
    HashTable,
    ByteVector,
    Struct,
    Unknown);


void        init();
SCM         eval(const std::string& code);
SCM         eval_file(const std::string& filename);
ValueKind   get_value_kind(SCM obj);
void        print(SCM obj, std::ostream& out, std::string indent = "");
bool        is_plist(SCM list);
bool        is_alist(SCM list);
void        iterate_plist(SCM list, std::function<void(SCM, SCM)> lambda);
std::string to_string(SCM value);

struct base_msg : std::exception {
    std::string text;
    const char* what() const noexcept override {
        return strdup(text.c_str());
    }
};

struct unexpected_variant : base_msg {
    unexpected_variant(std::string const& where, std::string const& kind) {
        text = fmt::format(
            "Could not decode variant with discriminant selector '{}' at "
            "{}",
            kind,
            where);
    }
};

struct missing_field : base_msg {
    missing_field(std::string const& where, SCM field) {
        text = fmt::format(
            "Could not get field '{}' from {}", to_string(field), where);
    }
};

struct decode_error : base_msg {
    decode_error(std::string const& where, SCM got) {
        text = fmt::format(
            "Unexpected value '{}' of kind {} was found while {}",
            to_string(got),
            enum_serde<ValueKind>::to_string(get_value_kind(got))
                .toStdString(),
            where);
    }
};


template <typename T>
struct convert;

SCM get_field(SCM node, char const* field);

template <typename T>
inline void visit_field(T& result, SCM node, char const* field) {
    ::guile::convert<T>::decode(result, get_field(node, field));
}

template <>
struct convert<int> {
    static void decode(int& result, SCM value) {
        if (scm_is_number(value)) {
            result = scm_to_int(value);
        } else {
            throw decode_error("parsing 'int' type", value);
        }
    }
};

template <>
struct convert<bool> {
    static void decode(bool& result, SCM value) {
        result = scm_is_true(value);
    }
};


template <typename T>
concept DescribedRecord = boost::describe::has_describe_members<
                              std::remove_cvref_t<T>>::value
                       && boost::describe::has_describe_bases<
                              std::remove_cvref_t<T>>::value;

// Type trait to check if a type is a specialization of std::variant
template <class T>
struct is_variant : std::false_type {};

template <class... Args>
struct is_variant<std::variant<Args...>> : std::true_type {};

// The concept uses the type trait after removing cv-ref qualifiers
template <typename T>
concept IsVariant = is_variant<std::remove_cvref_t<T>>::value;

template <IsVariant T, typename CRTP_Derived>
struct variant_convert {
    static std::string get_kind(
        SCM         value,
        char const* kindField = "kind") {
        SCM kind = get_field(value, kindField);
        return to_string(kind);
    }

    static void decode(T& result, SCM value) {
        CRTP_Derived::init(result, value);
        std::visit(
            [&](auto& variant) {
                ::guile::convert<typename std::remove_cvref_t<
                    decltype(variant)>>::decode(variant, value);
                return 0;
            },
            result);
    }
};


template <DescribedRecord T>
struct convert<T> {
    static void decode(T& result, SCM value) {
        using Bd = boost::describe::
            describe_bases<T, boost::describe::mod_any_access>;
        using Md = boost::describe::
            describe_members<T, boost::describe::mod_any_access>;
        mp_for_each<Md>([&](auto const& field) {
            ::guile::visit_field(result.*field.pointer, value, field.name);
        });
    }
};


} // namespace guile


std::ostream& operator<<(std::ostream& os, SCM scm);
