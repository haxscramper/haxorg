#include <haxorg/parse/OrgTypes.hpp>
#include <haxorg/parse/OrgParserTypes.hpp>
#include <hstd/stdlib/Formatter.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>

#include <haxorg/lexbase/Node.cpp>
#include <hstd/stdlib/OptFormatter.hpp>

namespace org::parse {
template class NodeGroup<OrgNodeKind, OrgTokenKind, OrgFill, OrgNodeMono>;


} // namespace org::parse

std::string org::fieldname_to_code(std::string_view str) {
    constexpr char chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    constexpr int  base    = sizeof(chars) - 1;

    uint64_t hash = 14695981039346656037ULL;
    for (char c : str) {
        hash ^= static_cast<uint64_t>(c);
        hash *= 1099511628211ULL;
    }

    std::string result{};
    result.reserve(4);
    for (int i = 0; i < 4; ++i) {
        result += chars[hash % base];
        hash /= base;
    }

    return result;
}
