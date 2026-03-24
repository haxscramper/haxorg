#pragma once

#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>

#include <wrappers/c/haxorg_c_vtables.hpp>

namespace org::bind::c {

template <typename T, typename CVtable>
struct VTable<std::shared_ptr<T>, CVtable> : public VTable<T, CVtable> {};

template <typename T, typename CVtable>
struct VTable<T const&, CVtable> : public VTable<T, CVtable> {};

template <typename T, typename CVtable>
struct VTable<T&, CVtable> : public VTable<T, CVtable> {};

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

    static int size(OrgContext* ctx, haxorg_HstdVec self) {
        return org::bind::c::execute_cpp<int, haxorg_builtin_vtable>(
            &hstd::Vec<T>::size, ctx, self);
    }

    static void const* back(const haxorg_HstdVec* self, OrgContext* ctx) {
        return org::bind::c::
            execute_cpp<void const*, haxorg_builtin_vtable>(
                &hstd::Vec<T>::back, ctx, self);
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
struct VTable<std::string, haxorg_StdString_vtable> {
    using Type  = haxorg_StdString;
    using VType = haxorg_StdString_vtable;
    using Self  = VTable<std::string, VType>;
    static VType const* get_vtable() {
        static VType vtable{
            .size = &Self::size,
            .data = &Self::data,
        };
        return &vtable;
    }

    static char const* data(OrgContext* ctx, Type self) {
        return execute_cpp<char const*, haxorg_builtin_vtable>(
            static_cast<char const* (std::string ::*)() const>(
                &std::string::data),
            ctx,
            self);
    }

    static int size(OrgContext* ctx, Type self) {
        return execute_cpp<int, haxorg_builtin_vtable>(
            &std::string::size, ctx, self);
    }
};

template <>
struct VTable<hstd::Str, haxorg_HstdStr_vtable> {
    using Type  = haxorg_HstdStr;
    using VType = haxorg_HstdStr_vtable;
    using Self  = VTable<hstd::Str, VType>;
    static VType const* get_vtable() {
        static VType vtable{};
        return &vtable;
    }
};

template <typename T>
struct VTable<std::optional<T>, haxorg_StdOptional_vtable> {
    using Type  = haxorg_StdOptional;
    using VType = haxorg_StdOptional_vtable;
    using Self  = VTable<std::optional<T>, VType>;
    static VType const* get_vtable() {
        static VType vtable{};
        return &vtable;
    }
};

template <typename T>
struct VTable<std::optional<T>, haxorg_HstdOpt_vtable> {
    using Type  = haxorg_HstdOpt;
    using VType = haxorg_HstdOpt_vtable;
    using Self  = VTable<std::optional<T>, VType>;
    static VType const* get_vtable() {
        static VType vtable{};
        return &vtable;
    }
};


template <typename T>
struct VTable<immer::flex_vector<T>, haxorg_immer_flex_vector_vtable> {
    using Type  = haxorg_immer_flex_vector;
    using VType = haxorg_immer_flex_vector_vtable;
    using Self  = VTable<immer::flex_vector<T>, VType>;
    static VType const* get_vtable() {
        static VType vtable{};
        return &vtable;
    }
};


} // namespace org::bind::c

using namespace org::bind;


HAXORG_C_API_LINKAGE haxorg_StdString
    haxorg_create_StdString_ConstChar(char const* text, OrgContext* ctx);
