#include <haxorg/sem/SemOrgBaseSharedTypes.hpp>

// clang-format off
std::format_context::iterator std::formatter<OrgTokenKind>::format(OrgTokenKind const& p, std::format_context& ctx) const {
    return std::formatter<std::string>{}.format(hstd::enum_serde<OrgTokenKind>::to_string(p), ctx);
}

std::format_context::iterator std::formatter<OrgSemKind>::format(OrgSemKind const& p, std::format_context& ctx) const {
    return std::formatter<std::string>{}.format(hstd::enum_serde<OrgSemKind>::to_string(p), ctx);
}

std::format_context::iterator std::formatter<OrgNodeKind>::format(OrgNodeKind const& p, std::format_context& ctx) const {
    return std::formatter<std::string>{}.format(hstd::enum_serde<OrgNodeKind>::to_string(p), ctx);
}

hstd::back_inserter_string_format_context::iterator std::formatter<OrgTokenKind>::format(OrgTokenKind const& p, hstd::back_inserter_string_format_context& ctx) const {
    return std::formatter<std::string>{}.format(hstd::enum_serde<OrgTokenKind>::to_string(p), ctx);
}

hstd::back_inserter_string_format_context::iterator std::formatter<OrgSemKind>::format(OrgSemKind const& p, hstd::back_inserter_string_format_context& ctx) const {
    return std::formatter<std::string>{}.format(hstd::enum_serde<OrgSemKind>::to_string(p), ctx);
}

hstd::back_inserter_string_format_context::iterator std::formatter<OrgNodeKind>::format(OrgNodeKind const& p, hstd::back_inserter_string_format_context& ctx) const {
    return std::formatter<std::string>{}.format(hstd::enum_serde<OrgNodeKind>::to_string(p), ctx);
}
// clang-format on
