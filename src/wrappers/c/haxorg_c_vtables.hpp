/* clang-format off */
#pragma once
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
struct haxorg_HstdMap_vtable {};

template <>
struct org::bind::c::VTable<hstd::UnorderedMap<haxorg_ptr_payload, haxorg_ptr_payload>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_HstdMap_vtable const* get_vtable();
};

struct haxorg_ImmMap_vtable {};

template <>
struct org::bind::c::VTable<hstd::ext::ImmMap<haxorg_ptr_payload, haxorg_ptr_payload>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Opt get_const(OrgContext* org_context, haxorg_ImmMap self, haxorg_ptr_payload const& key);
  static bool contains_const(OrgContext* org_context, haxorg_ImmMap self, haxorg_ptr_payload const& key);
  static haxorg_HstdVecOfHaxorg_ptr_payload keys_const(OrgContext* org_context, haxorg_ImmMap self);
  static haxorg_ImmMap_vtable const* get_vtable();
};

struct haxorg_Opt_vtable {};

template <>
struct org::bind::c::VTable<hstd::Opt<haxorg_ptr_payload>> {
  BOOST_DESCRIBE_CLASS(VTable, (), (), (), ());
  static haxorg_Opt_vtable const* get_vtable();
};

/* clang-format on */
