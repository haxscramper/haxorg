#include "haxorg_c.h"
#include "haxorg_c_utils.hpp"
#include "haxorg_c_vtables_manual.hpp"

using namespace org::bind;

template <>
struct c::VTable<haxorg_StdString, haxorg_StdString_vtable> {
    using Type  = haxorg_StdString;
    using VType = haxorg_StdString_vtable;
    using Self  = c::VTable<Type, VType>;
    static VType const* get_vtable() {
        static VType vtable{
            .data = &Self::data,
            .size = &Self::size,
        };
        return &vtable;
    }

    static char const* data(Type self, OrgContext* ctx) {
        return c::execute_cpp<char const*, haxorg_builtin_vtable>(
            static_cast<char const* (std::string ::*)() const>(
                &std::string::data),
            ctx,
            self);
    }

    static int size(Type self, OrgContext* ctx) {
        return c::execute_cpp<int, haxorg_builtin_vtable>(
            &std::string::size, ctx, self);
    }
};

HAXORG_C_API_LINKAGE haxorg_StdString
    haxorg_create_StdString_ConstChar(char const* text, OrgContext* ctx) {
    return c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(
        +[](char const* value) -> std::string {
            return std::string{value};
        },
        ctx,
        text);
}
