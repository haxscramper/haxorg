#pragma once

#include <types/enums.hpp>
namespace org_impl {
#include <autogen_enum_help.hpp>
}

#include <hstd/system/reflection.hpp>

template <>
struct enum_serde<OrgCommandKind> {
    static inline QString to_string(OrgCommandKind k) {
        return org_impl::to_string(k);
    }
};

template <>
struct enum_serde<OrgSpecName> {
    static inline QString to_string(OrgSpecName k) {
        return org_impl::to_string(k);
    }
};

template <>
struct enum_serde<OrgNodeKind> {
    static inline QString to_string(OrgNodeKind node) {
        return org_impl::to_string(node);
    }

    static inline std::optional<OrgNodeKind> from_string(
        QString const& str) {
        std::string tmp = str.toStdString();
        return org_impl::OrgNodeKind_from_string(tmp.c_str());
    }
};

template <>
struct enum_serde<OrgTokenKind> {
    static inline QString to_string(OrgNodeKind node) {
        return org_impl::to_string(node);
    }

    static inline std::optional<OrgTokenKind> from_string(
        QString const& str) {
        std::string tmp = str.toStdString();
        return org_impl::OrgTokenKind_from_string(tmp.c_str());
    }
};
