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
    ASSERT_FALSE(ctx.has_error);

    // parse, get Document node at root level
    haxorg_SemIdOfOrg parsed_node = haxorg_ParseContext_parseString(
        &ctx, parse_context, input_string, source_name);
    ASSERT_FALSE(ctx.has_error);

    // Access element at index 0, the text should be paragraph
    haxorg_StdOptional first_item = haxorg_SemIdOfOrg_getIndex(
        &ctx, parsed_node, 0);
    ASSERT_FALSE(ctx.has_error);

    // Unpack optional value for the paragraph
    haxorg_ptr_payload first_item_node = haxorg_StdOptional_value(
        &ctx, first_item);
    ASSERT_FALSE(ctx.has_error);
    haxorg_SemIdOfOrg stmt_node{.data = first_item_node};

    haxorg_OrgSemKind node_kind = haxorg_SemIdOfOrg_getNodeKind_const(
        &ctx, stmt_node);

    EXPECT_EQ(node_kind, haxorg_OrgSemKind::Paragraph);

    haxorg_destroy_SemIdOfOrg(&ctx, &parsed_node);
}

#endif
