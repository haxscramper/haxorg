#include "haxorg_c.h"
#include "haxorg_c_api.h"
#include "haxorg_c_utils.hpp"
#include "haxorg_c_vtables_manual.hpp"

using namespace org::bind;

haxorg_StdString haxorg_create_StdString_ConstChar(
    OrgContext* ctx,
    char const* text) {
    return c::execute_cpp<haxorg_StdString>(
        +[](char const* value) -> std::string {
            return std::string{value};
        },
        ctx,
        text);
}
