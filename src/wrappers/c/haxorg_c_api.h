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
    int (*size)(OrgContext*, haxorg_StdString);
    char const* (*data)(OrgContext*, haxorg_StdString);
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
    int (*size)(OrgContext*, haxorg_HstdVec);
};
struct haxorg_HstdVec {
    haxorg_HstdVec_vtable const* vtable;
    haxorg_ptr_payload           data;
};
struct haxorg_HstdStr_vtable {};
struct haxorg_HstdStr {
    haxorg_HstdStr_vtable const* vtable;
    haxorg_ptr_payload           data;
};
struct haxorg_HstdOpt_vtable {};
struct haxorg_HstdOpt {
    haxorg_HstdOpt_vtable const* vtable;
    haxorg_ptr_payload           data;
};
struct haxorg_StdOptional_vtable {};
struct haxorg_StdOptional {
    haxorg_StdOptional_vtable const* vtable;
    haxorg_ptr_payload               data;
};
struct haxorg_HstdUnorderedMap_vtable {};
struct haxorg_HstdUnorderedMap {
    haxorg_HstdUnorderedMap_vtable const* vtable;
    haxorg_ptr_payload                    data;
};
struct haxorg_ImmVec_vtable {};
struct haxorg_ImmVec {
    haxorg_ImmVec_vtable const* vtable;
    haxorg_ptr_payload          data;
};
struct haxorg_HstdUnorderedSet_vtable {};
struct haxorg_HstdUnorderedSet {
    haxorg_HstdUnorderedSet_vtable const* vtable;
    haxorg_ptr_payload                    data;
};
struct haxorg_immer_flex_vector_vtable {};
struct haxorg_immer_flex_vector {
    haxorg_immer_flex_vector_vtable const* vtable;
    haxorg_ptr_payload                     data;
};
struct haxorg_HstdIntSet_vtable {};
struct haxorg_HstdIntSet {
    haxorg_HstdIntSet_vtable const* vtable;
    haxorg_ptr_payload              data;
};


HAXORG_C_API_LINKAGE haxorg_StdString
    haxorg_create_StdString_ConstChar(char const* text, OrgContext* ctx);
