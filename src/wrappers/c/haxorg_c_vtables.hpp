/* clang-format off */
#pragma once
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
struct haxorg_HstdUnorderedMap_vtable {};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<haxorg_ptr_payload, haxorg_ptr_payload>, haxorg_HstdUnorderedMap_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdUnorderedMap_vtable const* get_vtable();
};

struct haxorg_ImmMapOfHaxorg_ptr_payloadHaxorg_ptr_payload_vtable {};

template <>
struct org::bind::c::VTable<hstd::ext::ImmMap<haxorg_ptr_payload, haxorg_ptr_payload>, haxorg_ImmMapOfHaxorg_ptr_payloadHaxorg_ptr_payload_vtable> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdOpt get_const(OrgContext* org_context, haxorg_ImmMapOfHaxorg_ptr_payloadHaxorg_ptr_payload self, haxorg_Haxorg_ptr_payload key);
  static bool contains_const(OrgContext* org_context, haxorg_ImmMapOfHaxorg_ptr_payloadHaxorg_ptr_payload self, haxorg_Haxorg_ptr_payload key);
  static haxorg_HstdVecOfHaxorg_ptr_payload keys_const(OrgContext* org_context, haxorg_ImmMapOfHaxorg_ptr_payloadHaxorg_ptr_payload self);
  static haxorg_ImmMapOfHaxorg_ptr_payloadHaxorg_ptr_payload_vtable const* get_vtable();
};

/* clang-format on */
