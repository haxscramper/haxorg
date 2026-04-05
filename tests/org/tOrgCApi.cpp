/// \brief Tests for the C API

#if ORG_BUILD_WRAPPERS_C
#    include <hstd/stdlib/OptFormatter.hpp>
#    include <hstd/stdlib/VariantFormatter.hpp>
#    include <hstd/stdlib/VecFormatter.hpp>
#    include <hstd/stdlib/PairFormatter.hpp>
#    include <hstd/stdlib/MapFormatter.hpp>
#    include "tOrgTestCommon.hpp"
#    include <wrappers/c/haxorg_c.h>


TEST(OrgCApi, TestSimpleParsing) {
    OrgContext ctx;
    auto parse_context = haxorg_create_ParseContext_ParseContextDefault(
        &ctx);

    ASSERT_TRUE(parse_context.data.data != nullptr);

    haxorg_StdString input_string = haxorg_create_StdString_ConstChar(
        &ctx, R"(*bold input*)");

    haxorg_StdString source_name = haxorg_create_StdString_ConstChar(
        &ctx, "<test>");

    haxorg_SemIdOfOrg parsed_node = haxorg_ParseContext_parseString(
        &ctx, parse_context, input_string, source_name);

    haxorg_StdOptional first_item = haxorg_SemIdOfOrg_getIndex(
        &ctx, parsed_node, 0);

    haxorg_destroy_SemIdOfOrg(&ctx, &parsed_node);
}

#endif
