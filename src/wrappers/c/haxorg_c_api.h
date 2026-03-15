#pragma once

#define HAXORG_C_API_LINKAGE extern "C"

struct OrgContext {};
struct haxorg_shared_ptr_payload {
    void* data;
};

struct haxorg_ptr_payload {
    void* data;
};

struct haxorg_StdString {};
struct haxorg_SemId {};
struct haxorg_HstdVec {};
struct haxorg_HstdStr {};
struct haxorg_HstdOpt {};
struct haxorg_StdOptional {};
struct haxorg_HstdUnorderedMap {};
struct haxorg_ImmVec {};
