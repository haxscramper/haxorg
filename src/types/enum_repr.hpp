#pragma once

#include <types/enums.hpp>
namespace org_impl {
#include <autogen_enum_help.hpp>
}

#include <hstd/system/reflection.hpp>

inline QString to_string(OrgTokenKind k) { return org_impl::to_string(k); }
inline QString to_string(OrgNodeKind k) { return org_impl::to_string(k); }
inline QString to_string(OrgSpecName k) { return org_impl::to_string(k); }

inline QString to_string(OrgCommandKind k) {
    return org_impl::to_string(k);
}

template <>
inline std::optional<OrgNodeKind> string_to_enum(QString const& str) {
    std::string tmp = str.toStdString();
    return org_impl::OrgNodeKind_from_string(tmp.c_str());
}


template <>
inline std::optional<OrgTokenKind> string_to_enum(QString const& str) {
    std::string tmp = str.toStdString();
    return org_impl::OrgTokenKind_from_string(tmp.c_str());
}
