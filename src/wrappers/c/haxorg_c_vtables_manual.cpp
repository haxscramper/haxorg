#include "haxorg_c_vtables_manual.hpp"

haxorg_StdString haxorg_create_StdString_ConstChar(
    char const* text,
    OrgContext* ctx) {
    return c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(
        +[](char const* value) -> std::string {
            return std::string{value};
        },
        ctx,
        text);
}
