#pragma once

#include <types/enums.hpp>
namespace org_impl {
#include <autogen_enum_help.hpp>
}

#include <hstd/system/reflection.hpp>

inline std::string to_string(OrgTokenKind k) {
    return org_impl::to_string(k);
}

inline std::string to_string(OrgNodeKind k) {
    return org_impl::to_string(k);
}

template <>
inline std::optional<OrgNodeKind> string_to_enum(std::string const& str) {
    return org_impl::OrgNodeKind_from_string(str.c_str());
}


template <>
inline std::optional<OrgTokenKind> string_to_enum(std::string const& str) {
    return org_impl::OrgTokenKind_from_string(str.c_str());
}
