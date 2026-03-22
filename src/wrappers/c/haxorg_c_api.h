#pragma once

#include <stdint.h>

#define HAXORG_C_API_LINKAGE extern "C"

struct OrgContext {
    // FIXME: temporary, using type that C can understand, need to switch
    // to the proper std::string later.
    int  has_error;
    char error_msg[256];
};

struct haxorg_ptr_payload {
    void* data;
};

struct haxorg_builtin_vtable {};

struct haxorg_StdString;

struct haxorg_StdString_vtable {
    int (*size)(haxorg_StdString, OrgContext*);
    char const* (*data)(haxorg_StdString, OrgContext*);
};

struct haxorg_StdString {
    haxorg_StdString_vtable const* vtable;
    haxorg_ptr_payload             data;
};
struct haxorg_SemId_vtable {};
struct haxorg_SemId {
    haxorg_SemId_vtable const* vtable;
    haxorg_ptr_payload         data;
};
struct haxorg_HstdVec;
struct haxorg_HstdVec_vtable {
    int (*size)(haxorg_HstdVec const*, OrgContext*);
};
struct haxorg_HstdVec {
    haxorg_HstdVec_vtable const* vtable;
    haxorg_ptr_payload           data;
};
struct haxorg_HstdStr {};
struct haxorg_HstdOpt {};
struct haxorg_StdOptional {};
struct haxorg_HstdUnorderedMap {};
struct haxorg_ImmVec {};
struct haxorg_HstdUnorderedSet {};
struct haxorg_immer_flex_vector {};
struct haxorg_HstdIntSet {};


HAXORG_C_API_LINKAGE haxorg_StdString
    haxorg_create_StdString_ConstChar(char const* text, OrgContext* ctx);
