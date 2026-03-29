/* clang-format off */
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_utils.hpp>
#include <wrappers/c/haxorg_c_vtables.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
haxorg_HstdMap_vtable const* org::bind::c::VTable<hstd::UnorderedMap<haxorg_ptr_payload, haxorg_ptr_payload>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::UnorderedMap<haxorg_ptr_payload, haxorg_ptr_payload>>;
  static haxorg_HstdMap_vtable const vtable{};
  return &vtable;
}
haxorg_HstdOpt org::bind::c::VTable<hstd::ext::ImmMap<haxorg_ptr_payload, haxorg_ptr_payload>>::get_const(OrgContext* org_context, haxorg_ImmMap self, haxorg_ptr_payload const& key) {
  return org::bind::c::execute_cpp<haxorg_HstdOpt, haxorg_HstdOpt_vtable>(static_cast<hstd::Opt<haxorg_ptr_payload>(hstd::ext::ImmMap<haxorg_ptr_payload, haxorg_ptr_payload>::*)(haxorg_ptr_payload const&) const>(&hstd::ext::ImmMap<haxorg_ptr_payload, haxorg_ptr_payload>::get), org_context, self, key);
}
bool org::bind::c::VTable<hstd::ext::ImmMap<haxorg_ptr_payload, haxorg_ptr_payload>>::contains_const(OrgContext* org_context, haxorg_ImmMap self, haxorg_ptr_payload const& key) {
  return org::bind::c::execute_cpp<bool, haxorg_builtin_vtable>(static_cast<bool(hstd::ext::ImmMap<haxorg_ptr_payload, haxorg_ptr_payload>::*)(haxorg_ptr_payload const&) const>(&hstd::ext::ImmMap<haxorg_ptr_payload, haxorg_ptr_payload>::contains), org_context, self, key);
}
haxorg_HstdVecOfHaxorg_ptr_payload org::bind::c::VTable<hstd::ext::ImmMap<haxorg_ptr_payload, haxorg_ptr_payload>>::keys_const(OrgContext* org_context, haxorg_ImmMap self) {
  return org::bind::c::execute_cpp<haxorg_HstdVecOfHaxorg_ptr_payload, haxorg_HstdVecOfHaxorg_ptr_payload_vtable>(static_cast<hstd::Vec<haxorg_ptr_payload>(hstd::ext::ImmMap<haxorg_ptr_payload, haxorg_ptr_payload>::*)() const>(&hstd::ext::ImmMap<haxorg_ptr_payload, haxorg_ptr_payload>::keys), org_context, self);
}
haxorg_ImmMap_vtable const* org::bind::c::VTable<hstd::ext::ImmMap<haxorg_ptr_payload, haxorg_ptr_payload>>::get_vtable() {
  using Self = org::bind::c::VTable<hstd::ext::ImmMap<haxorg_ptr_payload, haxorg_ptr_payload>>;
  static haxorg_ImmMap_vtable const vtable{.get_const = &Self::get_const,
                                           .contains_const = &Self::contains_const,
                                           .keys_const = &Self::keys_const,};
  return &vtable;
}
/* clang-format on */
