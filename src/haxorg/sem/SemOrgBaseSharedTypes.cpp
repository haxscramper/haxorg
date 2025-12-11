#include <haxorg/sem/SemOrgBaseSharedTypes.hpp>


std::format_context::iterator std::formatter<OrgTokenKind>::format(
    OrgTokenKind const&  p,
    std::format_context& ctx) const {
    std::formatter<std::string> fmt;
    return fmt.format(hstd::enum_serde<OrgTokenKind>::to_string(p), ctx);
}
