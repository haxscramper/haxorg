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
    void*       data;
    void const* vtable;
};

struct haxorg_StdString {
    haxorg_ptr_payload data;
};

struct haxorg_HstdUnorderedSet {
    haxorg_ptr_payload data;
};

struct haxorg_immer_flex_vector {
    haxorg_ptr_payload data;
};

typedef haxorg_immer_flex_vector haxorg_ImmVec;
struct haxorg_HstdIntSet {
    haxorg_ptr_payload data;
};


HAXORG_C_API_LINKAGE haxorg_StdString
    haxorg_create_StdString_ConstChar(OrgContext* ctx, char const* text);
