#pragma once

#include <types/enums.hpp>
namespace org_impl {
#include <autogen_enum_help.hpp>
}

#include <hstd/system/string_convert.hpp>

inline std::string to_string(OrgTokenKind k) {
    return org_impl::to_string(k);
}

inline std::string to_string(OrgNodeKind k) {
    return org_impl::to_string(k);
}
