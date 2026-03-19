#pragma once

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

struct haxorg_StdString {};
struct haxorg_SemId {};
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

typedef char               int8_t;
typedef unsigned char      uint8_t;
typedef short              int16_t;
typedef unsigned short     uint16_t;
typedef int                int32_t;
typedef unsigned int       uint32_t;
typedef long long          int64_t;
typedef unsigned long long uint64_t;
