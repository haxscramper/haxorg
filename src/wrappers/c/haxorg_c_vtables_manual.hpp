#pragma once

#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>

namespace org::bind::c {

template <typename T, typename CVtable>
struct VTable<std::shared_ptr<T>, CVtable> : public VTable<T, CVtable> {};

template <typename T, typename CVtable>
struct VTable<org::sem::SemId<T>, CVtable> {
    static CVtable const* get_vtable() {
        static CVtable vtable{};
        return &vtable;
    }
};

template <typename T, typename CVtable>
struct VTable<hstd::Vec<T>, CVtable> {
    static haxorg_HstdVec_vtable const* get_vtable() {
        using Self = VTable<hstd::Vec<T>, CVtable>;
        static haxorg_HstdVec_vtable data{
            .size = &Self::size,
        };
        return &data;
    }

    static int size(const haxorg_HstdVec* self, OrgContext* ctx) {
        return org::bind::c::execute_cpp<int, haxorg_builtin_vtable>(
            &hstd::Vec<T>::size, self, ctx);
    }

    static void const* back(const haxorg_HstdVec* self, OrgContext* ctx) {
        return org::bind::c::
            execute_cpp<void const*, haxorg_builtin_vtable>(
                &hstd::Vec<T>::back, self, ctx);
    }

    static void const* at(
        const haxorg_HstdVec* self,
        size_t                index,
        OrgContext*           ctx) {
        return org::bind::c::
            execute_cpp<void const*, haxorg_builtin_vtable>(
                &hstd::Vec<T>::at, self, index, ctx);
    }

    static void pop_back(haxorg_HstdVec* self, OrgContext* ctx) {
        return org::bind::c::execute_cpp(&hstd::Vec<T>::at, ctx);
    }

    static void destroy(haxorg_HstdVec* self, OrgContext* ctx) {
        return execute_destroy<hstd::Vec<T>>(self);
    }
};

template <>
struct VTable<haxorg_StdString, haxorg_StdString_vtable> {
    using Type  = haxorg_StdString;
    using VType = haxorg_StdString_vtable;
    using Self  = VTable<Type, VType>;
    static VType const* get_vtable() {
        static VType vtable{
            .size = &Self::size,
            .data = &Self::data,
        };
        return &vtable;
    }

    static char const* data(Type self, OrgContext* ctx) {
        return execute_cpp<char const*, haxorg_builtin_vtable>(
            static_cast<char const* (std::string ::*)() const>(
                &std::string::data),
            ctx,
            self);
    }

    static int size(Type self, OrgContext* ctx) {
        return execute_cpp<int, haxorg_builtin_vtable>(
            &std::string::size, ctx, self);
    }
};

} // namespace org::bind::c

using namespace org::bind;


HAXORG_C_API_LINKAGE haxorg_StdString
    haxorg_create_StdString_ConstChar(char const* text, OrgContext* ctx) {
    return c::execute_cpp<haxorg_StdString, haxorg_StdString_vtable>(
        +[](char const* value) -> std::string {
            return std::string{value};
        },
        ctx,
        text);
}
