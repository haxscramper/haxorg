#include <haxorg_cpp_org_lib/api/ParseContext.hpp>

int main() {
    auto ctx  = org::parse::ParseContext ::shared();
    auto node = ctx->parseString("*bold*", "<test>");
    LOGIC_ASSERTION_CHECK_FMT(
        node.getKind() == OrgSemKind::Document,
        "Expected string to parse as document, got {}",
        node.getKind());
}
