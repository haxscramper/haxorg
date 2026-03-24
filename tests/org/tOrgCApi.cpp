/// \brief Tests for the C API

#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/PairFormatter.hpp>
#include <hstd/stdlib/MapFormatter.hpp>
#include "tOrgTestCommon.hpp"
#include <wrappers/c/haxorg_c.h>


TEST(OrgCApi, TestSimpleParsing) {
    OrgContext ctx;
    auto parse_context = haxorg_create_ParseContext_ParseContextDefault(
        &ctx);

    ASSERT_TRUE(parse_context.vtable != nullptr);
    ASSERT_TRUE(parse_context.data.data != nullptr);

    haxorg_StdString input_string = haxorg_create_StdString_ConstChar(
        &ctx, R"(*bold input*)");

    haxorg_StdString source_name = haxorg_create_StdString_ConstChar(
        &ctx, "<test>");

    ASSERT_TRUE(parse_context.vtable->parseString != nullptr);

    haxorg_SemId parsed_node = parse_context.vtable->parseString(
        &ctx, parse_context, input_string, source_name);

    haxorg_destroy_SemId(&ctx, &parsed_node);
}
